"""Recover array sizes, call graph and cleaned bodies from a Hex-Rays "Export to C" file."""

from __future__ import annotations

import re
from collections import Counter
from collections.abc import Callable, Iterable, Iterator

from raidou.casts import (
    declared_types,
    drop_all_casts,
    expand_exponents,
    fold_accessors,
    join_wrapped,
    shorten_int_literals,
    strip_casts,
)
from raidou.layout import ARRAY_HEADER
from raidou.typemap import (
    IL2CPP_TYPE_TO_DECOMP_TYPE,
    STDINT_TYPE_TO_DECOMP_TYPE,
    UNITY_TO_SDF_TYPE,
    VALUE_TYPES,
    pointer_depth,
)

# A raw parameter or local type (`Project_X_o **`) -> (clean text, pointer depth, whether the
# prototype drops a pointer level there).
CType = Callable[[str], tuple[str, int, bool]]


def plain_ctype(expr: str) -> tuple[str, int, bool]:
    """`CType` without a type catalog: runtime and Unity math names map, game names stay."""
    expr = expr.replace("const ", "").replace("struct ", "").replace("__struct_ptr", "")
    stars = expr.count("*")
    tok = expr.replace("*", "").strip()
    arrays = 0
    while tok.endswith("_array"):
        tok, arrays = tok[: -len("_array")], arrays + 1
    obj = tok.endswith("_o") or tok == "Il2CppObject"
    base = tok.removesuffix("_o")
    text = (
        IL2CPP_TYPE_TO_DECOMP_TYPE.get(base) or UNITY_TO_SDF_TYPE.get(base)
        or STDINT_TYPE_TO_DECOMP_TYPE.get(base) or base
    )
    text, n = pointer_depth(text, stars, arrays, obj=obj, param=True)
    return text, n, not arrays and stars == 2 and n == 1

_DEF_HEADER = re.compile(r"(\w+)\(")
_ADDR_SEP = re.compile(r"^//----- \(0*([0-9A-Fa-f]+)\)")


def iter_functions(lines: Iterable[str]) -> Iterator[tuple[str, int | None, str, list[str]]]:
    """(name, address, signature, body lines) for each definition in the export.

    A definition follows a `//----- (ADDR)` separator or carries `__fastcall`; a header that
    ends in `;` is a prototype. A column-0 `}` closes the body (nested braces are indented).
    """
    state = "top"
    addr: int | None = None
    name, sig, body = "", list[str](), list[str]()
    for raw in lines:
        line = raw.rstrip("\n")
        s = line.strip()
        if state == "top":
            if m := _ADDR_SEP.match(line):
                addr = int(m.group(1), 16)
                continue
            if not s or s.startswith("//"):
                continue
            if (addr is not None or "__fastcall" in line) and not s.endswith(";") and (
                d := _DEF_HEADER.search(line)
            ):
                name, sig, state = d.group(1), [s], "sig"
                if s.endswith("{"):
                    body, state = [], "body"
            else:
                addr = None
        elif state == "sig":
            sig.append(s)
            if s.endswith(";"):
                state, addr = "top", None
            elif s.endswith("{"):
                body, state = [], "body"
        elif line.startswith("}"):
            yield name, addr, " ".join(sig), body
            state, addr = "top", None
        else:
            body.append(line)


def _inline_symbol_locals(b: str) -> str:
    """Substitute locals that only ever hold a GOT symbol or its value.

    `v8 = &X_TypeInfo;` assigned once: `*v8` -> `X_TypeInfo`, other uses -> `&X_TypeInfo`.
    `v10 = (_QWORD **)X_TypeInfo;` on every assignment: uses become `X_TypeInfo`, indexing
    keeps the declared element type (`v10[23]` -> `*((_QWORD **)X_TypeInfo + 23)`).
    """
    for m in list(re.finditer(r"(?m)^[ \t]*(v\d+) = &(\w+);[ \t]*\n", b)):
        v, sym = m.group(1), m.group(2)
        if len(re.findall(rf"(?<![\w.>]){v} =[^=]|&{v}\b|\b{v}(?:\+\+|--)", b)) != 1:
            continue
        b = b.replace(m.group(0), "", 1)
        b = re.sub(rf"\*{v}\b(?!; //)", sym, b)
        b = re.sub(rf"(?<![\w.>]){v}\b(?!; //)", f"&{sym}", b)
    b = re.sub(r"\*&(?=[A-Za-z_])", "", b)
    for v in dict.fromkeys(re.findall(r"(?m)^[ \t]*(v\d+) = (?:\([^()]*\))?\w+_TypeInfo;", b)):
        rhs = set(re.findall(rf"(?<![\w.>]){v} =[^=;]*;", b))
        syms = {re.sub(r"^.*?(\w+_TypeInfo);$", r"\1", r) for r in rhs}
        decl = re.search(rf"(?m)^[ \t]+([^\n;=]*?) ?{v}; //", b)
        if len(syms) != 1 or decl is None or not all(r.endswith("_TypeInfo;") for r in rhs):
            continue
        sym, ptr = syms.pop(), decl.group(1).strip()
        b = re.sub(rf"(?m)^[ \t]*{v} = [^\n]*_TypeInfo;[ \t]*\n", "", b)
        if "*" not in ptr:  # an integer copy of the class pointer: keep the cast
            b = re.sub(rf"(?<![\w.>]){v}\b(?!; //)", f"({ptr}){sym}", b)
            continue
        b = re.sub(rf"(?<![\w.>]){v}\[(\d+)\]", rf"*(({ptr}){sym} + \1)", b)
        b = re.sub(rf"\*{v}\b(?!; //)", f"*({ptr}){sym}", b)
        b = re.sub(rf"(?<![\w.>]){v}\b(?!; //)", sym, b)
    return b


_BARE_ALLOC = re.compile(r"(?m)^([ \t]*)(il2cpp::(?:NewSpecific|Allocate)\([^\n]*\));[ \t]*$")


def _recover_alloc_results(b: str) -> str:
    """`NewSpecific(t, 4); ... f = v10;` with `v10` never assigned -> `v10 = NewSpecific(...)`.
    Hex-Rays typed the helper as returning void, so its result shows up as a stray register."""
    for m in reversed(list(_BARE_ALLOC.finditer(b))):
        for nxt in re.finditer(r"(?m)^[^\n]* = (v\d+);[ \t]*$", b[m.end() :]):
            v = nxt.group(1)
            if re.search(rf"(?m)^[ \t]*{v} =[^=]", b):
                break
            b = f"{b[: m.start()]}{m.group(1)}{v} = {m.group(2)};{b[m.end() :]}"
            break
    return b


# Static member lookup: (class cname, byte offset, access width or None) -> member path.
StaticMember = Callable[[str, int, "int | None"], "str | None"]

_WIDTH = {
    "_BYTE": 1, "char": 1, "bool": 1, "__int8": 1, "int8_t": 1, "uint8_t": 1,
    "_WORD": 2, "short": 2, "__int16": 2, "int16_t": 2, "uint16_t": 2,
    "_DWORD": 4, "int": 4, "float": 4, "__int32": 4, "int32_t": 4, "uint32_t": 4,
    "_QWORD": 8, "__int64": 8, "double": 8, "int64_t": 8, "uint64_t": 8, "_OWORD": 16,
}
_STATIC_LOCAL = re.compile(r"(?m)^[ \t]*(v\d+) = (\w+_TypeInfo->static_fields);[ \t]*\n")
_STATIC_AT = re.compile(
    r"(\*?)\((?:const )?(?:unsigned )?([A-Za-z_][\w ]*?) ?\*(\**)\)"
    r"\((\w+)_TypeInfo->static_fields \+ (\d+)(?:LL)?\)"
)
_STATIC_FIRST = re.compile(
    r"(?<![\w)\]])\*(?:\((?:const )?(?:unsigned )?([A-Za-z_][\w ]*?) ?\*(\**)\))?"
    r"(\w+)_TypeInfo->static_fields\b(?! \+)(?!->)"
)


def _substitute_static_locals(b: str) -> str:
    """`v63 = X_TypeInfo->static_fields; *(T *)(v63 + 8)` -> `*(T *)(X_TypeInfo->... + 8)`
    when every load of the local reads the same block and it is used only as an address."""
    for m in list(_STATIC_LOCAL.finditer(b)):
        v, rhs = m.group(1), m.group(2)
        loads = set(re.findall(rf"(?m)^[ \t]*{v} = ([^\n]*);[ \t]*$", b))
        if loads != {rhs} or re.search(rf"\b{v}->", b):
            continue
        b = re.sub(rf"(?m)^[ \t]*(?:{v} = [^\n]*|[A-Za-z_][\w ]*\**[ \t]*{v});[^\n]*\n", "", b)
        b = re.sub(rf"(?<![\w.>]){v}\b", rhs, b)
    return b


def _name_static_members(b: str, member: StaticMember) -> str:
    """`*(_DWORD *)(X_TypeInfo->static_fields + 660)` -> `X_TypeInfo->static_fields->flags`."""

    def at(m: re.Match[str]) -> str:
        width = 8 if m.group(3) else _WIDTH.get(m.group(2))
        name = member(m.group(4), int(m.group(5)), width if m.group(1) else None)
        if name is None:
            return m.group(0)
        ref = f"{m.group(4)}_TypeInfo->static_fields->{name}"
        return ref if m.group(1) else f"&{ref}"

    def first(m: re.Match[str]) -> str:
        width = None if m.group(1) is None else 8 if m.group(2) else _WIDTH.get(m.group(1))
        name = member(m.group(3), 0, width)
        return f"{m.group(3)}_TypeInfo->static_fields->{name}" if name else m.group(0)

    return _STATIC_FIRST.sub(first, _STATIC_AT.sub(at, b))


def normalize(b: str, static_member: StaticMember | None = None) -> str:
    """Inline class pointer locals, name static members by offset, reattach allocations."""
    b = join_wrapped(b)
    if "_TypeInfo" in b:
        b = _inline_symbol_locals(b)
        if "->static_fields" in b:
            b = _substitute_static_locals(b)
            if static_member is not None:
                b = _name_static_members(b, static_member)
    return _recover_alloc_results(b)


# Object layout lookup: (struct name, byte offset) -> (path, size, type) of the members that
# start there, outermost first (`Layout.members_at`).
ObjectMember = Callable[[str, int], "list[tuple[str, int, str]]"]

_ALLOC_LOCAL = re.compile(r"(?m)^[ \t]*(v\d+) = (?:j_)?il2cpp::Allocate\((\w+)_TypeInfo\);[ \t]*$")
_ACCESS_TYPE = r"(?:(?:const|struct|unsigned|signed|volatile) )*[A-Za-z_]\w*(?: ?\*)*?"
_INT_PRIMS = {
    "bool": False, "char": True, "int8_t": True, "uint8_t": False, "int16_t": True,
    "uint16_t": False, "wchar_t": False, "char16_t": False, "Il2CppChar": False,
    "int32_t": True, "uint32_t": False, "int": True, "int64_t": True, "uint64_t": False,
    "il2cpp_array_size_t": False, "intptr_t": True, "uintptr_t": False, "size_t": False,
}


def _kind(t: str, size: int | None = None) -> tuple[str, int | None, bool | None, str]:
    """(kind, width, signed, base) of a C type; kind is int, float, ptr, array or struct and
    `signed` is None for Hex-Rays' signless `_DWORD` and friends."""
    t = re.sub(r"\b(?:const|struct|volatile) ", "", t).strip()
    if "[" in t:
        return ("array", size, None, t)
    if "*" in t:
        return ("ptr", 8, None, re.sub(r"\s+", "", t[: t.rindex("*")]))
    if t in ("float", "double"):
        return ("float", 4 if t == "float" else 8, None, t)
    unsigned = t.startswith("unsigned ")
    base = t.removeprefix("unsigned ").removeprefix("signed ")
    if base in _WIDTH and base not in ("float", "double"):
        signed = None if base.startswith("_") else not unsigned and _INT_PRIMS.get(base, True)
        return ("int", _WIDTH[base], signed, base)
    if base in _INT_PRIMS:
        return ("int", size, _INT_PRIMS[base], base)
    return ("struct", size, None, base.removesuffix("_o"))


def _field_ref(v: str, t: str, members: list[tuple[str, int, str]], off: int, ctx: str) -> str:
    """`*(t *)(v + off)` spelled through the member at `off`: plain when the types agree, a
    value cast when only the type changes, a reinterpretation when the bits do."""
    if not members:
        return f"*({t} *)((char *){v} + {off})"
    acc = _kind(t)
    convertible = None
    for path, size, mtype in members:
        mem = _kind(mtype, size)
        if acc[1] != mem[1] and acc[0] != "struct":
            continue
        same = acc[0] == mem[0] and (
            (acc[0] == "int" and (acc[2] is None or mem[2] is None or acc[2] == mem[2]))
            or (acc[0] in ("ptr", "struct") and acc[3] == mem[3])
            or acc[0] == "float"
        )
        if same:
            return f"{v}->{path}"
        if convertible is None and {acc[0], mem[0]} <= {"int", "ptr"}:
            convertible = path
    if convertible is not None and ctx != "update":
        return f"{v}->{convertible}" if ctx == "store" else f"({t}){v}->{convertible}"
    return f"*({t} *)&{v}->{members[0][0]}"


_UPDATE = re.compile(r"\s*(?:(?:[-+*/%&|^]|<<|>>)=|\+\+|--)")
_STORE = re.compile(r"\s*=(?!=)")
_RAW_DEREF = re.compile(rf"\*\(({_ACCESS_TYPE}) ?\*\)\((v\d+) \+ (\d+)(?:LL)?\)")
_RAW_ADDR = re.compile(rf"\(({_ACCESS_TYPE}) ?\*\)\((v\d+) \+ (\d+)(?:LL)?\)")
# After a cast (`*(T *)v + 8`) the operand is no longer the local.
_RAW_SUM = re.compile(r"()(?<![\w.>)\0])(v\d+) \+ (\d+)(?:LL)?\b")
_LOCAL_WRITE = re.compile(
    r"(?<![\w.>*])(v\d+)\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|&(v\d+)\b"
    r"|\b(v\d+)(?:\+\+|--)|(?:\+\+|--)(v\d+)\b"
)
_LOCAL_ARITH = re.compile(
    r"(?<![\w.>)\0])(v\d+)\s*(?:[-+*/%&|^](?![>=])|<<|>>)"
    r"|[\w)\]]\s*(?:[-+*/%&|^]|<<|>>)\s*(v\d+)\b"
)


_RAW_INDEX = re.compile(
    rf"\*\(({_ACCESS_TYPE}) ?\*\)\((v\d+) \+ (?:(\d+)(?:LL)? \* )?(\w+) \+ (\d+)(?:LL)?\)"
)


def _context(a: re.Match[str]) -> str:
    """How the dereference `a` is used: `update` (`+=`, `++`), `store` or `load`."""
    rest, lead = a.string[a.end() :], a.string[max(0, a.start() - 2) : a.start()]
    if _UPDATE.match(rest) or lead in ("++", "--"):
        return "update"
    return "store" if _STORE.match(rest) else "load"


def _name_raw_offsets(b: str, typed: dict[str, str], member: ObjectMember) -> str:
    """Raw `(v + N)` accesses of the locals in `typed` (local -> struct) through members,
    each rewritten use marked with a leading NUL."""

    def members(v: str, off: int) -> list[tuple[str, int, str]]:
        return [x for x in member(typed[v], off) if x[0] != "fields"]

    def deref(a: re.Match[str]) -> str:
        v = a.group(2)
        if v not in typed:
            return a.group(0)
        off = int(a.group(3))
        return _field_ref(f"\0{v}", a.group(1), members(v, off), off, _context(a))

    def address(a: re.Match[str]) -> str:
        v = a.group(2)
        if v not in typed:
            return a.group(0)
        off = int(a.group(3))
        found = members(v, off)
        place = f"&\0{v}->{found[0][0]}" if found else f"(char *)\0{v} + {off}"
        return f"({a.group(1)} *){place}" if a.group(1) else f"(__int64){place}"

    def index(a: re.Match[str]) -> str:
        v, scale = a.group(2), int(a.group(3) or 1)
        first = member(typed[v], ARRAY_HEADER) if v in typed else []
        elem = [x for x in first if x[0] == "m_Items[0]"]
        if not elem or elem[0][1] != scale or int(a.group(5)) != ARRAY_HEADER:
            return a.group(0)
        item = [(f"m_Items[{a.group(4)}]", elem[0][1], elem[0][2])]
        return _field_ref(f"\0{v}", a.group(1), item, 0, _context(a))

    b = _RAW_INDEX.sub(index, b)
    b = _RAW_DEREF.sub(deref, b)
    b = _RAW_ADDR.sub(address, b)
    return _RAW_SUM.sub(address, b)


_NEW_ARRAY_LOCAL = re.compile(
    r"(?m)^[ \t]*(v\d+) = il2cpp::NewSpecific\((\w+?)___TypeInfo, (?:0x[0-9A-Fa-f]+|\d+)u?\);"
)
_POINTER_LOAD = re.compile(r"(?m)^[ \t]*(v\d+) = \*\(_QWORD \*\)\((v\d+) \+ (\d+)(?:LL)?\);")
# C# keyword element names in `NewSpecific(int___TypeInfo, n)` -> the array struct's base
_CS_KEYWORD = {
    "int": "System_Int32", "uint": "System_UInt32", "short": "System_Int16",
    "ushort": "System_UInt16", "byte": "System_Byte", "sbyte": "System_SByte",
    "long": "System_Int64", "ulong": "System_UInt64", "float": "System_Single",
    "double": "System_Double", "bool": "System_Boolean", "char": "System_Char",
    "string": "System_String", "object": "System_Object",
}


def _type_alloc_locals(b: str, member: ObjectMember) -> str:
    """`__int64 v; v = Allocate(X); *(_DWORD *)(v + 48)` -> `X_o *v; ... v->fields.f`.

    Hex-Rays leaves the allocator's result an integer. A local holding only that object (or
    a `NewSpecific` array, or an object pointer loaded from a member of one) gets its type,
    and its raw offsets name the members. A local that is reassigned, has its address taken
    or takes part in arithmetic stays as it is.
    """
    sources: dict[str, set[str]] = {}
    count: Counter[str] = Counter()
    for m in _ALLOC_LOCAL.finditer(b):
        sources.setdefault(m.group(1), set()).add(f"{m.group(2)}_o")
        count[m.group(1)] += 1
    for m in _NEW_ARRAY_LOCAL.finditer(b):
        elem = _CS_KEYWORD.get(m.group(2), m.group(2))
        sources.setdefault(m.group(1), set()).add(f"{elem}_array")
        count[m.group(1)] += 1
    if not sources:
        return b
    writes = Counter(next(g for g in m.groups() if g) for m in _LOCAL_WRITE.finditer(b))
    declared = set(re.findall(r"(?m)^[ \t]+__int64 (v\d+);", b))

    def eligible(v: str, types: set[str]) -> str | None:
        (t, *more) = sorted(types)
        ok = not more and writes[v] == count[v] and v in declared
        return t if ok and (member(t, 16) or member(t, ARRAY_HEADER)) else None

    typed = {v: t for v, ts in sources.items() if (t := eligible(v, ts))}
    loads = list(_POINTER_LOAD.finditer(b))
    while True:  # object pointers loaded from members of typed locals
        found: dict[str, set[str]] = {}
        n: Counter[str] = Counter()
        for m in loads:
            v, base = m.group(1), m.group(2)
            if v in typed or v in sources or base not in typed:
                continue
            hits = [t for p, _, t in member(typed[base], int(m.group(3))) if p != "fields"]
            target = hits[0].replace("struct ", "").strip() if hits else ""
            found.setdefault(v, set()).add(target[:-1] if target.endswith("*") else "")
            n[v] += 1
        new = {
            v: t for v, ts in found.items()
            if writes[v] == n[v] and v in declared and len(ts) == 1
            and (t := next(iter(ts))) and member(t, 16)
        }
        if not new:
            break
        typed |= new
    out = b
    while typed:
        out = _name_raw_offsets(b, typed, member)
        bad = {g for m in _LOCAL_ARITH.finditer(out) for g in m.groups() if g in typed}
        if not bad:
            break
        typed = {v: t for v, t in typed.items() if v not in bad}
    if not typed:
        return b
    for v, struct in typed.items():
        out = re.sub(rf"(?m)^([ \t]+)__int64 {v};", rf"\1{struct} *{v};", out, count=1)
    return out.replace("\0", "")


_CTOR_AFTER_ALLOC = re.compile(
    r"(?m)^([ \t]*(v\d+) = (?:j_)?il2cpp::Allocate\(\w+\);[ \t]*\n)"
    r"[ \t]*(\w+___ctor)\((?:\([^()]*\))?\2, (?:nullptr|0)\);[ \t]*\n"
)


def _drop_default_ctors(b: str, default: frozenset[str] = frozenset()) -> str:
    """Drop the constructor call right after an allocation when it does nothing: the
    `System_Object___ctor` or a class constructor that only calls it (`default_ctors`)."""

    noop = default | {"System_Object___ctor"}
    return _CTOR_AFTER_ALLOC.sub(lambda m: m.group(1) if m.group(3) in noop else m.group(0), b)


def default_ctors(lines: Iterable[str]) -> frozenset[str]:
    """Constructors (`X___ctor`) whose body only calls `System_Object___ctor`."""
    out: set[str] = set()
    for name, _addr, _sig, body in iter_functions(lines):
        if not name.endswith("___ctor"):
            continue
        stmts = [s.strip() for s in body if s.strip() and not _DECL_COMMENT.match(s)]
        if all(s.startswith("System_Object___ctor(") for s in stmts):
            out.add(name)
    return frozenset(out)


_DECL_COMMENT = re.compile(r"^[ \t]*(?://|[A-Za-z_][\w ]*[ *]+\w+; //)")


# Array-size recovery from the transpiled .c constructors:
#   this->fields.<f>            = il2cpp::NewSpecific(<elem>___TypeInfo, <N>u);   (instance)
#   <Class>_TypeInfo->static_fields->.<f> = <v>;  <v> = NewSpecific(...);         (static)
_THIS_PARAM = re.compile(r"(\w+)_o \*this\b")
_NEWSPEC = re.compile(r"il2cpp::NewSpecific\(\s*(\w+)___TypeInfo,\s*(0x[0-9A-Fa-f]+|\d+)u?\s*\)")
_VAR_ALLOC = re.compile(r"^(\w+) = il2cpp::NewSpecific\(")
_THIS_FIELD = re.compile(r"^this->fields\.(\w+) = (.+);$")
_STATIC_FIELD = re.compile(r"^(\w+)_TypeInfo->static_fields->(\w+) = (.+);$")

# (struct-or-class base, field) -> (element count, element-is-value-type)
ArraySizes = dict[tuple[str, str], tuple[int, bool]]


def _rhs_alloc(rhs: str, var_alloc: dict[str, tuple[str, int]]) -> tuple[str, int] | None:
    m = _NEWSPEC.search(rhs)
    if m:
        return (m.group(1), int(m.group(2), 0))
    return var_alloc.get(rhs.strip())


def array_sizes(lines: Iterable[str], static_member: StaticMember | None = None) -> ArraySizes:
    """Recover fixed array element counts from constructor ``NewSpecific()`` allocations."""
    sizes: ArraySizes = {}
    for _name, _addr, sig, body in iter_functions(lines):
        text = "\n".join(body)
        if "NewSpecific" not in text:
            continue
        tp = _THIS_PARAM.search(sig)
        cur_struct = tp.group(1) if tp else None
        var_alloc: dict[str, tuple[str, int]] = {}
        for raw in normalize(text, static_member).split("\n"):
            line = raw.strip()
            if "NewSpecific" in line or "static_fields" in line or line.startswith("this->"):
                line = drop_all_casts(line)
            if line.startswith("this->fields."):
                fm = _THIS_FIELD.match(line)
                if cur_struct and fm and (alloc := _rhs_alloc(fm.group(2), var_alloc)):
                    elem, n = alloc
                    if n:
                        sizes[cur_struct, fm.group(1)] = (n, elem in VALUE_TYPES)
            elif "_TypeInfo->static_fields->" in line:
                sm = _STATIC_FIELD.match(line)
                if sm and (alloc := _rhs_alloc(sm.group(3), var_alloc)):
                    elem, n = alloc
                    if n:
                        sizes[sm.group(1), sm.group(2)] = (n, elem in VALUE_TYPES)
            elif (am := _VAR_ALLOC.match(line)) and (nm := _NEWSPEC.search(line)):
                var_alloc[am.group(1)] = (nm.group(1), int(nm.group(2), 0))
    return sizes


_CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")


def function_addresses(lines: Iterable[str]) -> dict[str, int]:
    """``{function name: address}`` from the ``//----- (ADDR) ----`` separators."""
    out: dict[str, int] = {}
    for name, addr, _sig, _body in iter_functions(lines):
        if addr is not None:
            out.setdefault(name, addr)
    return out


def call_graph(lines: Iterable[str], valid: frozenset[str]) -> dict[str, list[str]]:
    """Map each function to the ``valid`` game functions it calls, in first-seen order."""
    graph: dict[str, list[str]] = {}
    for name, _addr, _sig, body in iter_functions(lines):
        calls = graph.setdefault(name, [])
        seen: set[str] = set()
        for line in body:
            for c in _CALL.finditer(line):
                callee = c.group(1)
                if callee != name and callee in valid and callee not in seen:
                    seen.add(callee)
                    calls.append(callee)
    return graph


_STATIC_DIRECT = re.compile(r"\b(\w+)_TypeInfo->static_fields->(\w+)")
_STATIC_LOCAL_BASE = re.compile(r"\b(\w+) = &?(\w+)_TypeInfo->static_fields;")
_TYPEINFO_LOCAL = re.compile(r"\b(\w+) = (\w+)_TypeInfo;")
_VIA_TYPEINFO = re.compile(r"\b(\w+)->static_fields->(\w+)")
_VIA_BASE = re.compile(r"\b(\w+)->(\w+)")


def static_field_uses(
    lines: Iterable[str], static_member: StaticMember | None = None
) -> set[tuple[str, str, str]]:
    """``(function, class, field)`` for each static field a function touches, including
    through a local holding the class pointer or its static block.
    """
    uses: set[tuple[str, str, str]] = set()
    for cur, _addr, _sig, body in iter_functions(lines):
        bases: dict[str, str] = {}
        infos: dict[str, str] = {}
        if static_member is not None and any("static_fields +" in ln for ln in body):
            body = normalize("\n".join(body), static_member).split("\n")
        for raw in body:
            if "_TypeInfo" in raw:
                for m in _STATIC_DIRECT.finditer(raw):
                    uses.add((cur, m.group(1), m.group(2)))
                if (m := _STATIC_LOCAL_BASE.search(raw)) is not None:
                    bases[m.group(1)] = m.group(2)
                elif (m := _TYPEINFO_LOCAL.search(raw)) is not None:
                    infos[m.group(1)] = m.group(2)
            if infos and "static_fields" in raw:
                for m in _VIA_TYPEINFO.finditer(raw):
                    if m.group(1) in infos:
                        uses.add((cur, infos[m.group(1)], m.group(2)))
            if bases:
                for m in _VIA_BASE.finditer(raw):
                    if m.group(1) in bases:
                        uses.add((cur, bases[m.group(1)], m.group(2)))
    return uses


# --- parameters that lose a pointer level -------------------------------------------


def _split_params(args: str) -> list[tuple[str, str]]:
    """A raw parameter list as (type, name) pairs, without the MethodInfo."""
    out: list[tuple[str, str]] = []
    for raw in args.split(","):
        p = raw.replace("__struct_ptr", "").strip()
        if not p or p == "void" or "MethodInfo" in p:
            continue
        pm = _PARAM_NAME.match(p)
        out.append((pm.group(1), pm.group(2)) if pm else (p, ""))
    return out


_PARAM_NAME = re.compile(r"^(.*[ *])(\w+)$")
_OBJ_PTR = re.compile(r"(?:\bstruct )?\b(\w+_o)\b ?(\*+)")
_ARG_ADDR = re.compile(r"^&\s*[A-Za-z_]\w*$")


def _type_text(t: tuple[str, int, bool]) -> str:
    return f"{t[0]} {'*' * t[1]}"


def _clean_object_types(b: str, ctype: CType) -> tuple[str, set[str]]:
    """Map raw `X_o *` / `X_o **` types in a body to prototype types; also return the names
    of locals declared `X_o **` (they lose a level, like such parameters).
    """
    dropped: set[str] = set()

    def sub(m: re.Match[str]) -> str:
        t = ctype(f"{m.group(1)} {m.group(2)}")
        if t[2] and (tail := re.match(r"\s*(\w+)\s*[;,=)]", b[m.end() :])):
            dropped.add(tail.group(1))
        return _type_text(t)

    return _OBJ_PTR.sub(sub, b), dropped


def deref_dropped(b: str, names: Iterable[str]) -> str:
    """`(*p)->f` / `*p` -> `p->f` / `p` for names that lost a pointer level."""
    for v in names:
        e = re.escape(v)
        b = re.sub(rf"(?<![\w)\]])\(\*{e}\)", v, b)
        b = re.sub(rf"(?<![\w)\]] )(?<![\w)\]])\*{e}\b(?!\s*->)", v, b)
    return b


def _call_arg_spans(text: str, start: int) -> tuple[list[tuple[int, int]], int] | None:
    """Top-level argument spans of the call whose `(` precedes `start`, and the index of `)`."""
    depth, a = 0, start
    spans: list[tuple[int, int]] = []
    for i in range(start, len(text)):
        c = text[i]
        if c in "([":
            depth += 1
        elif c in ")]":
            if depth == 0:
                if c != ")":
                    return None
                spans.append((a, i))
                return spans, i
            depth -= 1
        elif c == "," and depth == 0:
            spans.append((a, i))
            a = i + 1
    return None


def drop_address_args(b: str, slots: dict[str, tuple[bool, ...]]) -> str:
    """`f(&v)` -> `f(v)` where f's prototype dropped a level in that slot."""
    edits: list[tuple[int, int, str]] = []
    for m in re.finditer(r"\b([A-Za-z_]\w*)\(", b):
        flags = slots.get(m.group(1))
        found = _call_arg_spans(b, m.end()) if flags else None
        if not flags or found is None:
            continue
        for i, (x, y) in enumerate(found[0]):
            arg = b[x:y]
            if i < len(flags) and flags[i] and _ARG_ADDR.match(arg.strip()):
                lead = " " if arg.startswith(" ") else ""
                edits.append((x, y, lead + arg.strip()[1:].lstrip()))
    for x, y, text in sorted(edits, reverse=True):
        b = b[:x] + text + b[y:]
    return b


def _value_params_to_pointers(b: str, names: Iterable[str]) -> str:
    """`pos.x` -> `pos->x` for a Unity math parameter the prototype passes as a pointer."""
    for v in names:
        b = re.sub(rf"(?<![\w.>]){re.escape(v)}\.(?=[A-Za-z_])", f"{v}->", b)
    return b


# Deterministic IL2CPP-boilerplate strip, turning a Hex-Rays body into readable pseudo-C.
_META_GUARD = re.compile(
    r"\n[ \t]*if \( \(byte_[0-9A-F]+ & 1\) == 0 \)\n[ \t]*\{"
    r"\n(?:[ \t]*il2cpp::InitializeMethodMetadata\([^\n]*\);\n)*[ \t]*byte_[0-9A-F]+ = 1;\n[ \t]*\}"
)
# The braceless forms. `_strip_typeinit_blocks` cuts the braced one by counting braces: a
# non-greedy regex stops at a nested `}` and leaves the body unbalanced.
_TYPEINIT = re.compile(
    r"\n[ \t]*if \([^\n]*cctor_finished \)\n[ \t]*il2cpp::TypeInitializer\([^\n]*\);"
    r"|\n[ \t]*il2cpp::TypeInitializer\([^\n]*\);"
)
_TYPEINIT_GUARD = re.compile(
    r"\n([ \t]*)if \((?:[^\n]*cctor_finished| \(byte_[0-9A-F]+ & 1\) [!=]= 0| !?byte_[0-9A-F]+) \)"
    r"\n[ \t]*\{"
)


def _guard_inverted(line: str) -> bool:
    """True when the guard's first arm runs on the already-initialised path."""
    if "cctor_finished" in line:
        return not re.search(r"!\S*cctor_finished", line)
    return not re.search(r"!byte_|== 0", line)


_LABEL_DEF = re.compile(r"(?m)^[ \t]*(LABEL_\d+):")
_LABEL_REF = re.compile(r"\bLABEL_\d+\b")
_ELSE = re.compile(r"\s*else\b")
_GOTO = re.compile(r"\bgoto (LABEL_\d+);")


def _match_brace(b: str, i: int) -> int:
    """Index of the `}` closing the `{` at `i`, or -1."""
    depth = 0
    for j in range(i, len(b)):
        if b[j] == "{":
            depth += 1
        elif b[j] == "}":
            depth -= 1
            if depth == 0:
                return j
    return -1


_SIMPLE_STMT = re.compile(r'(?:[^;"{]|"(?:[^"\\\n]|\\.)*")*;')


_STMT_LEAD = re.compile(r"\s*(?:LABEL_\d+:\s*)*")


def _stmt_end(b: str, i: int) -> int:
    """End (exclusive) of the statement starting at `i`, braced or braceless; -1 if unclear."""
    m = _STMT_LEAD.match(b, i)
    assert m is not None
    i = m.end()
    if b.startswith("{", i):
        j = _match_brace(b, i)
        return j + 1 if j >= 0 else -1
    head = re.compile(r"(?:if|for|while|switch)\s*\(").match(b, i)
    if head is None:
        j = _SIMPLE_STMT.match(b, i)
        return j.end() if j else -1
    depth, k = 1, head.end()
    while k < len(b) and depth:
        depth += (b[k] == "(") - (b[k] == ")")
        k += 1
    end = _stmt_end(b, k)
    if end > 0 and head.group(0).startswith("if"):
        em = _ELSE.match(b, end)
        if em is not None:
            return _stmt_end(b, em.end())
    return end


def _arm_signature(text: str) -> tuple[str, list[str], list[str]]:
    """Arm text without scaffolding, braces, comments and whitespace; the labels it defines
    (numbered by position in the signature, so renamed twins compare equal); its goto targets.
    """
    lines = (re.sub(r"[ \t]*//.*$", "", ln) for ln in text.split("\n"))
    body = "\n".join(ln for ln in lines if not _JUNK_LINE.search(ln))
    labels = _LABEL_DEF.findall(body)
    targets = _GOTO.findall(body)
    canon = {n: f"@{k}" for k, n in enumerate(labels)}
    body = _LABEL_REF.sub(lambda m: canon.get(m.group(0), m.group(0)), body)
    return re.sub(r"[\s{}]+", "", body), labels, targets


def _twin_arms(a: str, b: str, renames: dict[str, str]) -> bool:
    """True when the two arms of a class-init guard are tail-duplicated copies; their labels
    are recorded as renames so jumps into the dropped copy land in the kept one."""
    sa, la, _ = _arm_signature(a)
    sb, lb, _ = _arm_signature(b)
    if sa != sb or len(la) != len(lb):
        return False
    renames.update({y: x for x, y in zip(la, lb, strict=True) if x != y})
    return True


def _shift_left(text: str, indent: int) -> str:
    """Dedent a block's lines so its shallowest line sits at `indent`."""
    lines = text.split("\n")
    depths = [len(ln) - len(ln.lstrip()) for ln in lines if ln.strip() and not _LABEL_DEF.match(ln)]
    delta = min(depths, default=indent) - indent
    if delta <= 0:
        return text
    return "\n".join(ln[delta:] if ln[:delta].strip() == "" else ln for ln in lines)


def _unwrap_typeinit(b: str, renames: dict[str, str], skips: list[int]) -> str:
    out: list[str] = []
    pos = 0
    while (m := _TYPEINIT_GUARD.search(b, pos)) is not None:
        guard_line = b[m.start() + 1 : b.index("\n", m.start() + 1)]
        i = b.index("{", m.start())
        j = _match_brace(b, i)
        if j < 0:
            break
        inverted = _guard_inverted(guard_line)
        a_text = _unwrap_typeinit(b[i + 1 : j], renames, skips)
        end = j + 1
        keep, dead = a_text, ""
        em = _ELSE.match(b, j + 1)
        e_end = _stmt_end(b, em.end()) if em is not None else -1
        if em is not None and e_end > 0:
            b_stmt = b[em.end() : e_end].strip()
            b_text = b_stmt[1:-1] if b_stmt.startswith("{") else f"\n{m.group(1)}  {b_stmt}"
            b_text = _unwrap_typeinit(b_text, renames, skips)
            end = e_end
            if not _twin_arms(a_text, b_text, renames):
                keep, dead = (a_text, b_text) if inverted else (b_text, a_text)
        head = b[pos : m.start()]
        last = ("".join(out) + head).rstrip().rsplit("\n", 1)[-1]
        nested = last.endswith("else") or _BRACELESS_CTRL.match(last) is not None
        indent = m.group(1) + ("  " if nested else "")
        keep = _shift_left(keep.rstrip(), len(indent)) if keep.strip() else ""
        if _LABEL_DEF.search(dead):
            # Code elsewhere may jump into the dead arm: keep it behind a jump over it.
            skips.append(len(skips))
            label = f"LABEL_{_SKIP_BASE + skips[-1]}"
            dead = _shift_left(dead.rstrip(), len(indent))
            keep = f"{keep}\n{indent}goto {label};{dead}\n{label}:"
        if keep and nested:
            keep = f"\n{m.group(1)}{{{keep}\n{m.group(1)}}}"
        out.append(head + keep)
        pos = end
    out.append(b[pos:])
    return "".join(out)


# Labels made for jumps over a dead guard arm, numbered clear of Hex-Rays' own.
_SKIP_BASE = 9000


def _strip_typeinit_blocks(b: str) -> str:
    """Replace each `if (!cctor_finished) { init; A } [else B]` by A. B repeats A and goes;
    when the two differ B is kept instead. The inverted guard keeps no arm: its fall-through
    code follows it.
    """
    renames: dict[str, str] = {}
    b = _unwrap_typeinit(b, renames, [])
    if renames:
        b = _LABEL_REF.sub(lambda m: renames.get(m.group(0), m.group(0)), b)
    return b


# A body too tangled for a naive strip: an inlined unnamed helper, or irreducible control
# flow the cleaner could not remove. Reported by `clean_bodies`, but still emitted.
_COMPLEX = re.compile(r"\bsub_[0-9A-Fa-f]+|\bgoto\b|\bLABEL_")

# Whole-line IL2CPP scaffolding to delete (metadata init, cctor/type-info, exception throws).
# The class-TypeInfo pointer is dead once `x->static_fields->G` collapses to `G`, so its
# decl/assignments go; the element TypeInfo inside NewSpecific/Allocate is kept but cleaned.
_JUNK_LINE = re.compile(
    r"InitializeMethodMetadata|TypeInitializer|cctor_finished|_TypeInfo->_"
    r"|\*\w+_TypeInfo;|\w+_TypeInfo = |= :*\w+_TypeInfo;"
    r"|Il2CppExceptionWrapper|\b(?!Project_)\w*Exception\w*\(|::Throw|Codegen"
    r"|const MethodInfo \*\w+;|byte_[0-9A-F]+ = 1;|WriteBarrier\("
    r"|QueryInterface\([^\n]*->_1\.element_class\)"  # array-store covariance check
)
# `goto LABEL_n;` / `LABEL_n:` are control flow, not scaffolding: deleting them takes whole
# branches with them (a braceless `if (!dlc) goto LABEL_14;` loses its condition).

_CTRL_LINE = re.compile(r"(?m)^[ \t]*(?:if|while)[ \t]*\(.*\)[ \t]*\n")


_WOVEN_TYPEINIT = re.compile(
    r"(?m)^([ \t]*)if \( (.*&& !\S*cctor_finished) \)\n[ \t]*il2cpp::TypeInitializer\([^\n]*\);\n"
)


def _unweave_typeinit(m: re.Match[str]) -> str:
    """`if (a && f() && !X->cctor_finished) TypeInitializer(X);` -> `if (a) f();`: the class
    counts as initialised, but the calls in the other terms still run."""
    terms = _top_split(m.group(2), "&&")
    if "||" in m.group(2) or not terms[-1].startswith("!") or len(terms) < 2:
        return m.group(0)
    return _emptied_if(m.group(1), " && ".join(terms[:-1]))


def _drop_junk_guards(b: str) -> str:
    """Drop an `if` on a scaffolding check (array-store or cast check) whose body only jumps
    to the throw: deleting just the condition line would make the jump unconditional. A
    check guarding real code loses only its condition line later."""
    for m in reversed(list(_CTRL_LINE.finditer(b))):
        line = m.group(0)
        if "cctor_finished" in line or not _JUNK_LINE.search(line):
            continue
        end = _stmt_end(b, m.end())
        if end > 0 and _GOTO_ONLY.fullmatch(b[m.end() : end]):
            b = b[: m.start()] + b[end + b.startswith("\n", end) :]
    return b


_GOTO_ONLY = re.compile(r"\s*(?:\{\s*)?goto LABEL_\d+;(?:\s*\})?")


# A control statement with no `{`: its body is the single next statement, so deleting that
# statement as scaffolding leaves the guard standing over unrelated code.
_BRACELESS_CTRL = re.compile(
    r"^[ \t]*(?:\}[ \t]*)?(?:else[ \t]+)?(?:if|for|while)[ \t]*\(.*\)[ \t]*$"
)

_HEXRAYS_TYPE_TO_DECOMP_TYPE = [
    ("unsigned __int64", "u64"), ("unsigned __int32", "u32"),
    ("unsigned __int16", "u16"), ("unsigned __int8", "u8"),
    ("__int64", "s64"), ("__int32", "s32"), ("__int16", "s16"),
    ("__int8", "s8"), ("_QWORD", "u64"), ("_DWORD", "u32"),
    ("_WORD", "u16"), ("_BYTE", "u8"), ("_BOOL", "bool"),
]

_BASIC_C_TYPE_TO_DECOMP_TYPE = [
    ("unsigned int", "u32"), ("unsigned short", "u16"), ("unsigned char", "u8"),
    ("signed char", "s8"), ("int", "s32"), ("short", "s16"),
]

# Hex-Rays often lifts the class pointer into a local (`v = X->static_fields;`) instead of
# writing `X->static_fields->G` inline, which the inline collapse below cannot see.
_STATIC_BASE_LOCAL = re.compile(r"(?m)^[ \t]*(\w+) = &?[\w>.\-]+->static_fields;[ \t]*$\n?")

_STRING_LITERAL_REF = re.compile(r"\bStringLiteral_(\d+)\b")


def _c_string(text: str) -> str:
    """Render metadata text as a C string literal."""
    out = text.replace("\\", "\\\\").replace('"', '\\"')
    out = out.replace("\n", "\\n").replace("\r", "\\r").replace("\t", "\\t")
    return f'"{out}"'


def _resolve_string_literals(b: str, strings: dict[int, str] | None) -> str:
    """`StringLiteral_4529` -> the text it names, or the placeholder if it is unmapped."""
    if not strings:
        return b
    def sub(m: re.Match[str]) -> str:
        text = strings.get(int(m.group(1)))
        return _c_string(text) if text is not None else m.group(0)
    return _STRING_LITERAL_REF.sub(sub, b)


def _collapse_static_field_locals(b: str) -> str:
    """`v = X->static_fields; ... v->G` -> `G`. Runs after the inline collapse; the `->`
    lookbehind stops it eating `X->static_fields->G` when the local is named `static_fields`.
    """
    while (m := _STATIC_BASE_LOCAL.search(b)) is not None:
        local = re.escape(m.group(1))
        b = b[: m.start()] + b[m.end() :]
        b = re.sub(rf"(?<![>\w]){local}->", "", b)
    return b


_ARRAY_LOCAL = re.compile(r"\b(?:struct )?(\w+?_array) \*")
_RAW_DECL = re.compile(r"(?m)^[ \t]+[A-Za-z_][\w ]*?[ \t*]+(\w+)(?:\[\d+\])?;[ \t]*//[^\n]*$")


def _unshadow_globals(b: str) -> str:
    """Fix a local named after the global it was loaded from (`G = X->static_fields->G`).

    The static collapse would make every use of the local a use of the global, or leave
    writes aimed at an uninitialised local. A local that is only ever a copy of the global
    is dropped; any other local is renamed `G_local`.
    """
    bases = _STATIC_BASE_LOCAL.findall(b)
    path = r"(?:[\w>.\-]+->static_fields" + "".join(f"|\\b{re.escape(v)}" for v in bases) + r")"
    globals_ = set(re.findall(r"->static_fields->(\w+)", b))
    for v in bases:
        globals_.update(re.findall(rf"\b{re.escape(v)}->(\w+)", b))
    for m in _RAW_DECL.finditer(b):
        name = m.group(1)
        g = re.escape(name)
        if name not in globals_:
            continue
        local = rf"(?<![\w>.]){g}\b"
        copy = re.compile(rf"(?m)^[ \t]*{g} = (?:\([^)]*\))?{path}->{g};[ \t]*$")
        rest = copy.sub("", b.replace(m.group(0), ""))
        impure = re.search(
            rf"(?:{local}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|{local}\s*(?:\+\+|--)|(?:\+\+|--|&){g}\b)",
            rest,
        )
        if impure is None:
            b = b.replace(m.group(0) + "\n", "", 1)
        else:
            b = re.sub(local, f"{name}_local", b)
    return b


_ORPHAN_LABEL = re.compile(r"(?m)^[ \t]*(LABEL_\d+):[ \t]*(?:\n|\Z)")


def _drop_orphan_labels(b: str) -> str:
    """Remove `LABEL_n:` lines no `goto` reaches."""
    targets = set(_GOTO.findall(b))
    return _ORPHAN_LABEL.sub(lambda m: m.group(0) if m.group(1) in targets else "", b)


_GUARD_IF = re.compile(
    r"(?m)^([ \t]*)if \( "
    r"(?:(!?)\S*cctor_finished|\(byte_[0-9A-F]+ & 1\) ([!=])= 0|(!?)byte_[0-9A-F]+) \)[ \t]*\n"
)


_FOLD_SKIP_BASE = 9500
_FOLD_SKIP = re.compile(r"(?m)^LABEL_95\d\d:")


def _fold_guard_ifs(b: str) -> str:
    """`if (X->cctor_finished) S` -> `S`, `if (!X->cctor_finished) S` -> nothing: the class
    and its metadata are taken as initialised. Braceless guards only; braced ones are unwrapped.
    """
    for m in reversed(list(_GUARD_IF.finditer(b))):
        if b[m.end() :].lstrip().startswith("{"):
            continue
        end = _stmt_end(b, m.end())
        if end < 0:
            continue
        if m.group(2) or m.group(3) == "=" or m.group(4):
            stmt = b[m.end() : end]
            if _LABEL_DEF.search(stmt):  # reached by a jump: keep it behind a jump over it
                label = f"LABEL_{_FOLD_SKIP_BASE + len(_FOLD_SKIP.findall(b))}"
                stmt = f"{m.group(1)}goto {label};\n{stmt}\n{label}:"
                b = b[: m.start()] + stmt + b[end:]
            else:
                b = b[: m.start()] + b[end + b.startswith("\n", end) :]
        else:
            b = b[: m.start()] + _shift_left(b[m.end() : end], len(m.group(1))) + b[end:]
    return b


_JUMP = re.compile(r"(?m)^([ \t]*)(?:return\b[^;\n]*|goto LABEL_\d+|break|continue);[ \t]*$")
_NOT_STMT = re.compile(r"\s*(?:\}|LABEL_\d+:|case\b|default\b|do\b|else\b|\Z)")


_JUMP_INTO_TWIN = re.compile(
    r"(?m)^([ \t]*)if \((.*)\)\n[ \t]*goto (LABEL_\d+);\n\1((?:return\b[^;\n]*|goto LABEL_\d+));\n"
    r"\1if \(\2\)\n\1\{\n\3:\n"
)


def _merge_jump_into_twin(b: str) -> str:
    """`if (c) goto L; T; if (c) { L: X } T` -> `if (c) { X } T`, where T is a jump and the
    code after the block repeats it (or T is `goto M` and `M:` follows the block)."""
    for m in reversed(list(_JUMP_INTO_TWIN.finditer(b))):
        close = _match_brace(b, m.end() - len(m.group(3)) - 4)
        if close < 0 or len(re.findall(rf"\bgoto {m.group(3)};", b)) != 1:
            continue
        after = b[close + 1 :].lstrip()
        tail = m.group(4)
        target = tail.removeprefix("goto ")
        repeats = after.startswith(f"{tail};")
        if not (repeats or (tail != target and after.startswith(f"{target}:"))):
            continue
        twin = f"{m.group(1)}if ({m.group(2)})\n{m.group(1)}{{\n"
        b = b[: m.start()] + twin + b[m.end() :]
    return b


_INVERSE = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
_TOP_OP = re.compile(r"&&|\|\||[=!<>]=|(?<![<>-])[<>](?![<>=])|\?")


def _negate(cond: str) -> str:
    """`!c`, with a single top-level comparison inverted and `!x` unwrapped."""
    cond = cond.strip()
    depth, ops = 0, list[re.Match[str]]()
    for i, ch in enumerate(cond):
        depth += (ch in "([") - (ch in ")]")
        if depth == 0 and (op := _TOP_OP.match(cond, i)) and op.start() == i:
            ops.append(op)
    if len(ops) == 1 and ops[0].group(0) in _INVERSE and not cond.startswith("!"):
        o = ops[0]
        return f"{cond[: o.start()]}{_INVERSE[o.group(0)]}{cond[o.end() :]}"
    if not ops and cond.startswith("!") and not cond.startswith("!="):
        inner = cond[1:]
        if re.fullmatch(r"\w+(?:(?:->|\.)\w+)*", inner) or (
            inner.startswith("(") and _match_paren(inner, 0) == len(inner) - 1
        ):
            return inner[1:-1] if inner.startswith("(") else inner
    if not ops:
        return f"!{cond}"
    return f"!({cond})"


_GOTO_OVER = re.compile(r"(?m)^([ \t]*)if \((.*)\)\n\1[ \t]+goto (LABEL_\d+);\n")


def _goto_over_to_if(b: str) -> str:
    """`if (c) goto L; S...; L:` -> `if (!c) { S... }` when nothing else jumps to L."""
    for m in reversed(list(_GOTO_OVER.finditer(b))):
        ind, label = m.group(1), m.group(3)
        if len(re.findall(rf"\bgoto {label};", b)) != 1:
            continue
        pos, stmts = m.end(), list[str]()
        while True:
            lead = re.compile(r"\s*").match(b, pos)
            assert lead is not None
            if b.startswith(f"{label}:", lead.end()):
                break
            line_start = b.rfind("\n", 0, lead.end()) + 1
            if _NOT_STMT.match(b, pos) or b[line_start : lead.end()] != ind:
                stmts = []
                break
            end = _stmt_end(b, pos)
            if end < 0 or _LABEL_DEF.search(b[pos:end]):
                stmts = []
                break
            stmts.append(b[lead.end() : end])
            pos = end
        if not stmts:
            continue
        inner = f"\n{ind}".join(stmts).replace("\n", "\n  ")
        cond = _negate(m.group(2))
        if len(stmts) == 1 and "\n" not in stmts[0]:
            new = f"{ind}if ({cond})\n{ind}  {inner}"
        else:
            new = f"{ind}if ({cond})\n{ind}{{\n{ind}  {inner}\n{ind}}}"
        b = b[: m.start()] + new + b[pos:]
    return b


def _drop_unreachable(b: str) -> str:
    """Delete statements after an unconditional jump up to the next label or block end, and
    `goto L;` straight before `L:`; then labels left without a `goto`, until nothing changes."""
    while True:
        new = b
        for m in reversed(list(_JUMP.finditer(new))):
            prev = new[: m.start()].rstrip().rsplit("\n", 1)[-1]
            if _BRACELESS_CTRL.match(prev) or prev.strip() in ("else", "} else"):
                continue
            pos = m.end()
            while _NOT_STMT.match(new, pos) is None:
                end = _stmt_end(new, pos)
                if end < 0 or _LABEL_DEF.search(new[pos:end]):
                    break
                new = new[:pos] + new[end:]
        new = re.sub(
            r"(?m)^[ \t]*goto (LABEL_\d+);[ \t]*\n(?=(?:[ \t]*\n|LABEL_\d+:\n)*?\1:)", "", new
        )
        new = _goto_over_to_if(_merge_jump_into_twin(new))
        new = _drop_orphan_labels(new)
        if new == b:
            return b
        b = new


_INTERFACE_ASSIGN = re.compile(r"(?m)^[ \t]*Interface = [^\n]*;\n")
_CAST_CHECK = re.compile(
    r"(?m)^([ \t]*)if \([^\n]*\)\n\1\{\n\1[ \t]+\w+ = QueryInterface\([^\n]*\);\n\1\}\n"
)


def _drop_dead_interface(b: str) -> str:
    """Remove the `Interface = v;` copies left once the covariance check is gone."""
    b = _CAST_CHECK.sub("", b + "\n").rstrip("\n")
    rest = _INTERFACE_ASSIGN.sub("", b)
    if re.search(r"\bInterface\b", rest.replace("Interface;", "")):
        return b
    return rest


_EMPTY_BLOCK = re.compile(r"(?m)^[ \t]*\{[ \t\n]*\}[ \t]*(?:\n|\Z)")


def _drop_bare_block(m: re.Match[str]) -> str:
    """An empty `{ }` that is a statement of its own, not the body of a control statement."""
    prev = m.string[: m.start()].rstrip().rsplit("\n", 1)[-1].strip()
    return m.group(0) if prev.endswith((")", "else", "do")) else ""


_EMPTY_IF = re.compile(
    r"(?m)^([ \t]*)(else )?if \((.*)\)[ \t\n]*\{[ \t\n]*\}(?:([ \t\n]*else\b)|[ \t]*\n?)"
)
_CALL_NAME = re.compile(r"\b(?!(?:sizeof|if|while|for|switch|return)\()[A-Za-z_]\w*\(")


def _top_split(cond: str, op: str) -> list[str]:
    """`cond` split at the top-level `op` (`&&`), outside parentheses."""
    parts, depth, start, i = list[str](), 0, 0, 0
    while i < len(cond):
        depth += (cond[i] in "([") - (cond[i] in ")]")
        if depth == 0 and cond.startswith(op, i):
            parts.append(cond[start:i].strip())
            start = i = i + len(op)
            continue
        i += 1
    return [*parts, cond[start:].strip()]


def _outer_calls(text: str) -> list[str]:
    """The calls in `text` that are not arguments of another call, left to right."""
    calls, pos = list[str](), 0
    while (m := _CALL_NAME.search(text, pos)) is not None:
        close = _match_paren(text, m.end() - 1)
        if close < 0:
            break
        calls.append(text[m.start() : close + 1])
        pos = close + 1
    return calls


def _emptied_if(ind: str, cond: str) -> str:
    """What is left of `if (cond) {}`: the calls in `cond`, under the `&&` terms before them."""
    parts = _top_split(cond, "&&")
    if not _CALL_NAME.search(cond):
        return ""
    if "||" in cond or any(_CALL_NAME.search(p) for p in parts[:-1]):
        return f"{ind}{cond};\n"
    calls = _outer_calls(parts[-1])
    if len(parts) == 1:
        return "".join(f"{ind}{c};\n" for c in calls)
    head = f"{ind}if ({' && '.join(parts[:-1])})\n"
    if len(calls) == 1:
        return f"{head}{ind}  {calls[0]};\n"
    return head + f"{ind}{{\n" + "".join(f"{ind}  {c};\n" for c in calls) + f"{ind}}}\n"


def _drop_empty_if(m: re.Match[str]) -> str:
    """`if (c) {} else S` -> `if (!c) S`; `if (c) {}` -> the calls in `c`, if any."""
    ind, chained, cond, has_else = m.group(1), m.group(2), m.group(3).strip(), m.group(4)
    if has_else:
        return f"{ind}{chained or ''}if ({_negate(cond)})"
    kept = _emptied_if(ind + "  " if chained else ind, cond)
    if chained:
        return f"{ind}else\n{ind}{{\n{kept}{ind}}}\n" if kept else ""
    return kept


def _strip_empty_ifs(b: str) -> str:
    """Remove `if (cond) {}` guards left after their metadata/throw body was deleted."""
    for _ in range(6):
        new = _EMPTY_IF.sub(_drop_empty_if, b)
        new = _EMPTY_BLOCK.sub(_drop_bare_block, new)
        if new == b:
            return b
        b = new
    return b


_LOCAL_DECL = re.compile(
    r"^[ \t]+(?:struct[ \t]+)?[A-Za-z_]\w*(?:[ \t]+\**|\**[ \t]+)"
    r"([A-Za-z_]\w*)(?:\[[^\]]*\])?;[ \t]*$"
)
_DECL_KEYWORDS = frozenset(
    {"return", "break", "continue", "goto", "case", "else", "do", "while", "for",
     "if", "switch", "typedef"}
)

def _drop_unused_locals(b: str) -> str:
    """Remove local declarations (`TYPE name;`, no initializer) never referenced again."""
    uses: Counter[str] = Counter(re.findall(r"[A-Za-z_]\w*", b))
    kept: list[str] = []
    for ln in b.split("\n"):
        m = _LOCAL_DECL.match(ln)
        if m and ln.split()[0] not in _DECL_KEYWORDS and uses[m.group(1)] <= 1:
            continue  # declared once, never used
        kept.append(ln)
    return "\n".join(kept)


def _split_args(inner: str) -> list[str]:
    """Split a call's argument text at top-level commas."""
    args: list[str] = []
    depth, start, quote = 0, 0, False
    for i, ch in enumerate(inner):
        if quote:
            quote = not (ch == '"' and inner[i - 1] != "\\")
        elif ch == '"':
            quote = True
        elif ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif ch == "," and depth == 0:
            args.append(inner[start:i].strip())
            start = i + 1
    tail = inner[start:].strip()
    if tail or args:
        args.append(tail)
    return args


def _match_paren(b: str, i: int) -> int:
    """Index of the `)` closing the `(` at `i`, or -1. Skips string literals."""
    depth, quote = 0, False
    for j in range(i, len(b)):
        ch = b[j]
        if quote:
            quote = not (ch == '"' and b[j - 1] != "\\")
        elif ch == '"':
            quote = True
        elif ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                return j
    return -1


_CALL_OPEN = re.compile(r"\b([A-Za-z_]\w*)\(")
_STALE_ARG = re.compile(r"0|\*?&?[A-Za-z_]\w*|\*\(const MethodInfo \*\*\)&\w+")


def _fix_call_arity(b: str, arity: dict[str, int]) -> str:
    """Drop the trailing IL2CPP context arg the cleaned prototypes already shed.

    A call one arg past its callee's arity loses the tail when it is that context (``0``,
    ``Method_*`` or a bare name). Innermost calls go first, so offsets to the left stay valid.
    """
    for m in reversed(list(_CALL_OPEN.finditer(b))):
        n = arity.get(m.group(1))
        if n is None:
            continue
        close = _match_paren(b, m.end() - 1)
        if close < 0:
            continue
        args = _split_args(b[m.end() : close])
        if len(args) == n + 1 and _STALE_ARG.fullmatch(args[-1]):
            b = b[: m.end()] + ", ".join(args[:-1]) + b[close:]
    return b


def _clean_body(
    body: str,
    names: dict[str, str] | None = None,
    arity: dict[str, int] | None = None,
    strings: dict[int, str] | None = None,
    type_name: Callable[[str], str] | None = None,
    signature: str = "",
    slots: dict[str, tuple[bool, ...]] | None = None,
    ctype: CType = plain_ctype,
    static_member: StaticMember | None = None,
    object_member: ObjectMember | None = None,
    default_ctors: frozenset[str] = frozenset(),
) -> str:
    sig_args = signature[signature.find("(") + 1 : signature.rfind(")")]
    params = _split_params(sig_args)
    b = normalize(body, static_member).replace("nullptr", "0")  # C, as in SMT3's sources
    b = _drop_default_ctors(b, default_ctors)
    if object_member is not None:
        b = _type_alloc_locals(b, object_member)
    b = strip_casts(b, declared_types(b, params))
    b = expand_exponents(shorten_int_literals(fold_accessors(b)))
    b = _unshadow_globals(b)
    b = _META_GUARD.sub("", b)
    b = _strip_typeinit_blocks(b)
    b = _fold_guard_ifs(b)
    b = _WOVEN_TYPEINIT.sub(_unweave_typeinit, b)
    b = _TYPEINIT.sub("", b)
    b = _drop_junk_guards(b)
    temps = set(re.findall(r"const MethodInfo \*(\w+);", b)) | {"method"}
    kept: list[str] = []
    for raw in b.split("\n"):
        ln = re.sub(r"[ \t]*//.*$", "", raw)
        if not _JUNK_LINE.search(ln):
            kept.append(ln)
            continue
        # The deleted line was the single statement under a braceless guard, so the guard
        # now covers whatever follows. Drop it too, and repeat for a nested chain.
        while kept and _BRACELESS_CTRL.match(kept[-1]):
            kept.pop()
    b = "\n".join(kept)
    for t in temps:
        b = re.sub(rf",\s*{re.escape(t)}\b", "", b)
        b = re.sub(rf"\b{re.escape(t)}\s*,\s*", "", b)
        b = re.sub(rf"\(\s*{re.escape(t)}\s*\)", "()", b)
    b = re.sub(r"\bj_(?=[A-Za-z_])", "", b)  # Hex-Rays jump-thunk prefix (j_Allocate -> Allocate)
    b = b.replace("il2cpp::", "").replace("->fields.", "->").replace(".fields.", ".")
    b = _resolve_string_literals(b, strings)
    b = re.sub(r"\b\w+->static_fields->", "", b)  # `x->static_fields->G` is a global `G`
    b = _collapse_static_field_locals(b)

    def _call(m: re.Match[str]) -> str:
        full = m.group(1)
        return (names or {}).get(full, full.split("__", 1)[1]) + "("

    b = re.sub(r"\b([A-Za-z_]\w*__\w+)\(", _call, b)
    b = b.replace("___TypeInfo", "").replace("_TypeInfo", "")  # NewSpecific(int, 6u) etc.
    b, lost = _clean_object_types(b, ctype)
    lost |= {n for t, n in params if n and ctype(t)[2]}
    b = deref_dropped(b, lost)
    b = _value_params_to_pointers(
        b, [n for t, n in params if n and ctype(t)[0].startswith("const ")]
    )
    if slots:
        b = drop_address_args(b, slots)
    b = b.replace("->m_Items[", "[")  # array header: X->m_Items[i] is X[i]
    b = re.sub(r"->m_Items\b", "", b)
    b = _ARRAY_LOCAL.sub(lambda m: _type_text(ctype(m.group(1) + " *")), b)
    if type_name is not None:  # game names lose their namespace, Unity math types map to sdf
        b = re.sub(r"\b(?:Project|UnityEngine)_\w+", lambda m: type_name(m.group(0)), b)
    for type, c in _HEXRAYS_TYPE_TO_DECOMP_TYPE:
        b = re.sub(rf"\b{re.escape(type)}\b", c, b)
    for type, d in STDINT_TYPE_TO_DECOMP_TYPE.items():
        b = re.sub(rf"\b{type}\b", d, b)
    for type, d in _BASIC_C_TYPE_TO_DECOMP_TYPE:
        b = re.sub(rf"\b{type}\b", d, b)
    b = re.sub(r"\( +", "(", b)  # remove extra parenthesis padding
    b = re.sub(r" +\)", ")", b)
    b = re.sub(r"(?m)^[ \t]*(\w+) = \1;[ \t]*$\n?", "", b)  # dead self-assignments
    b = re.sub(r",\s*Method_\w+\s*\)", ")", b)  # trailing MethodInfo literal the proto drops
    b = re.sub(r"\(\s*Method_\w+\s*\)", "()", b)
    if arity:
        b = _fix_call_arity(b, arity)
    b = _strip_empty_ifs(b)
    b = _strip_empty_ifs(_drop_dead_interface(b))
    b = _strip_empty_ifs(_drop_unreachable(b))
    b = _drop_unused_locals(b)
    b = re.sub(r"\n[ \t]*\n(?:[ \t]*\n)+", "\n\n", b)
    return b.strip("\n")


def _complexity(cleaned: str) -> str:
    """Why a body is too tangled to reconstruct; empty string means reconstruct it."""
    if set(_GOTO.findall(cleaned)) - set(_LABEL_DEF.findall(cleaned)):
        return "goto into dropped label"
    if m := _COMPLEX.search(cleaned):
        return "inlined sub_ helper(s)" if m.group(0).startswith("sub_") else "goto control flow"
    if cleaned.count("{") != cleaned.count("}"):
        return "unbalanced control flow"
    if len(re.findall(r"\belse\b", cleaned)) > len(re.findall(r"\bif\b", cleaned)):
        return "metadata woven into control flow"
    return "too many statements" if cleaned.count("\n") > 200 else ""


def clean_bodies(
    lines: Iterable[str],
    names: dict[str, str] | None = None,
    arity: dict[str, int] | None = None,
    strings: dict[int, str] | None = None,
    type_name: Callable[[str], str] | None = None,
    slots: dict[str, tuple[bool, ...]] | None = None,
    ctype: CType = plain_ctype,
    static_member: StaticMember | None = None,
    object_member: ObjectMember | None = None,
    default_ctors: frozenset[str] = frozenset(),
) -> tuple[dict[str, str], dict[str, str]]:
    """Reconstruct bodies from the .c; return (bodies, reason-the-body-is-approximate).

    ``slots``: per callee display name, the parameters whose prototype dropped a pointer level.
    """
    bodies: dict[str, str] = {}
    reasons: dict[str, str] = {}
    for cur, _addr, sig, buf in iter_functions(lines):
        cleaned = _clean_body(
            "\n".join(buf), names, arity, strings, type_name, sig, slots, ctype, static_member,
            object_member, default_ctors,
        )
        # Even a tangled body carries arithmetic, constants and field offsets a stub throws
        # away. Only a brace-unbalanced one is dropped: it would not parse and would
        # swallow the rest of the file.
        if reason := _complexity(cleaned):
            reasons[cur] = reason
        if cleaned.count("{") == cleaned.count("}"):
            bodies[cur] = cleaned
    return bodies, reasons
