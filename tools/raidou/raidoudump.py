"""Reconstruct C headers and module sources from Il2CppDumper output for Raidou HD."""

from __future__ import annotations

import argparse
import json
import re
from collections import Counter
from collections.abc import Iterable
from dataclasses import dataclass, field
from pathlib import Path

from raidou import dumpcs, families, hexrays
from raidou.layout import Layout
from raidou.smt3index import Smt3Index
from raidou.smt3index import load as load_smt3
from raidou.typemap import (
    COMMON_BODY,
    COMMON_HEADER,
    IL2CPP_TYPE_TO_DECOMP_TYPE,
    MATH_PROVIDED,
    PRIMITIVE,
    STDINT_TYPE_TO_DECOMP_TYPE,
    UNITY_TO_SDF_TYPE,
    pointer_depth,
)

# Top-level namespace tokens of the .NET/Unity/IL2CPP runtime and third-party libraries.
RUNTIME: frozenset[str] = frozenset(
    {"System", "Mono", "Microsoft", "UnityEngine", "UnityEngineInternal", "Unity", "TMPro",
     "Il2Cpp", "I18N", "Locale", "SR", "Newtonsoft", "nn", "CriWare", "Cinemachine",
     "MagicaCloth", "DynamicBone"}
)

# Header for data types of a sub-namespace (`Project.Kernel` -> kernel.h).
NS_HEADERS: dict[str, str] = {
    "Kernel": "kernel.h",
    "libsdf": "libsdf.h",
    "Basic": "basic.h",
    "Field": "field.h",
    "Field_EnemySymbol": "fieldEnemySymbol.h",
    "File": "file.h",
    "Graphics": "graphics.h",
}

_WRAPPERS = ("_StaticFields", "_Fields", "_VTable", "_RGCTXs", "_o", "_c")

# C#-only methods with no place in a native-C game: constructors, property/event accessors,
# operators and Object/interface/iterator/delegate members.
_CSHARP_METHOD = re.compile(
    r"^(?:\.c?ctor|get_|set_|add_|remove_|op_|<)"
    r"|^(?:Equals|GetHashCode|ToString|Finalize|Dispose|MemberwiseClone|GetType|Clone|CompareTo"
    r"|MoveNext|GetEnumerator|Reset|Invoke|BeginInvoke|EndInvoke|DynamicInvoke)$"
    r"|[.<]"  # explicit interface implementation, generic method
)

_JUNK_NAME = re.compile(r"[<>`|]|__c\b|DisplayClass|PrivateImplementationDetails|Anonymous")

# --- il2cpp.h ------------------------------------------------------------


@dataclass(frozen=True)
class Block:
    name: str
    base: str | None
    members: list[str]


_BLOCK_START = re.compile(r"^struct (\w+)(?: : (\w+))? \{$")
_MEMBER = re.compile(r"^(?:struct\s+)?([A-Za-z_]\w*)\s*([*\s]*)\s*([A-Za-z_]\w*)\s*;$")


def parse_blocks(lines: Iterable[str]) -> dict[str, Block]:
    """Every ``struct NAME [: BASE] {`` definition in Il2CppDumper's ``il2cpp.h``."""
    blocks: dict[str, Block] = {}
    cur: tuple[str, str | None] | None = None
    members: list[str] = []
    for raw in lines:
        line = raw.rstrip("\r\n")
        if cur is None:
            if (m := _BLOCK_START.match(line)) is not None:
                cur, members = (m.group(1), m.group(2)), []
        elif line.startswith("};"):
            blocks[cur[0]] = Block(cur[0], cur[1], members)
            cur = None
        elif (s := line.strip()) and not s.startswith("/"):
            members.append(s)
    return blocks


# --- type catalog -----------------------------------------------------------


@dataclass
class TypeInfo:
    cname: str  # il2cpp name: Project_Kernel_dds3ProcessID_t
    ns: str  # namespace token: "Kernel", "Field_EnemySymbol", "" for Project itself
    kind: str  # module, struct, enum, delegate, define
    clean: str
    root: str  # cname of the outermost enclosing type (itself when top-level)
    td: dumpcs.TypeDef
    file: str = ""
    header: str | None = None  # header known to hold this type (from SMT3 or the namespace)
    port: bool = False  # a port class kept only for its struct


def _ns_token(namespace: str) -> str:
    """``Project.Field.EnemySymbol`` -> ``Field_EnemySymbol``; ``Project`` -> ``""``."""
    rest = namespace.rsplit("Project.", 1)[1] if "Project." in namespace else ""
    return rest.replace(".", "_")


def _is_csharp_method(name: str) -> bool:
    return bool(_CSHARP_METHOD.search(name))


def _classify(td: dumpcs.TypeDef, blocks: dict[str, Block], cname: str) -> str | None:
    if td.kind == "interface":
        return None
    if td.kind == "enum":
        return "enum"
    if td.base in ("MulticastDelegate", "System.MulticastDelegate"):
        return "delegate"
    if any(not _is_csharp_method(m.name) for m in td.methods) or any(
        f.static for f in td.fields
    ):
        return "module"
    if _instance_members(cname, blocks):
        return "struct"
    return "define" if td.consts else None


def _instance_members(cname: str, blocks: dict[str, Block]) -> list[str]:
    """Instance field lines of ``cname``, with game base classes flattened in first."""
    b = blocks.get(f"{cname}_Fields")
    if b is None:
        return []
    inherited: list[str] = []
    if b.base and b.base.startswith("Project_"):
        inherited = _instance_members(b.base[: -len("_Fields")], blocks)
    return inherited + b.members


def build_catalog(types: list[dumpcs.TypeDef], blocks: dict[str, Block]) -> dict[str, TypeInfo]:
    """Every game (``Project.*``) type that is emitted, keyed by il2cpp name."""
    names = {_strip_wrapper(n) for n in blocks}
    top_ns: dict[str, list[str]] = {}
    for td in types:
        if td.namespace:
            top_ns.setdefault(td.name, []).append(td.namespace)
    cat: dict[str, TypeInfo] = {}
    for td in types:
        if _JUNK_NAME.search(td.name):
            continue
        namespace = td.namespace
        if not namespace:  # nested: the namespace is the outermost type's
            cands = [n for n in top_ns.get(td.name.split(".")[0], []) if n.startswith("Project")]
            hits = [n for n in cands if _cname(n, td.name) in names]
            namespace = (hits or cands or [""])[0]
        if namespace != "Project" and not namespace.startswith("Project."):
            continue
        cname = _cname(namespace, td.name)
        kind = _classify(td, blocks, cname)
        if kind is None:
            continue
        root = _cname(namespace, td.name.split(".")[0])
        cat[cname] = TypeInfo(cname, _ns_token(namespace), kind, "", root, td)
    _assign_clean_names(cat)
    return cat


def _cname(namespace: str, dotted: str) -> str:
    return re.sub(r"\W", "_", f"{namespace}.{dotted}")


def _assign_clean_names(cat: dict[str, TypeInfo]) -> None:
    """The innermost name, unless two types share it; then the dotted path, then the
    namespace too."""
    short = Counter(t.td.name.split(".")[-1] for t in cat.values())
    for t in cat.values():
        leaf = t.td.name.split(".")[-1]
        t.clean = leaf if short[leaf] == 1 else t.td.name.replace(".", "_")
    full = Counter(t.clean for t in cat.values())
    for t in cat.values():
        if full[t.clean] > 1 and t.ns:
            t.clean = f"{t.ns}_{t.clean}"
    # A trailing `_` only avoided a clash in C#; drop it when the bare name is free.
    taken = {t.clean for t in cat.values()}
    for t in cat.values():
        bare = t.clean.rstrip("_")
        if bare != t.clean and bare and bare not in taken:
            taken.add(bare)
            t.clean = bare


def assign_headers(cat: dict[str, TypeInfo], smt3: Smt3Index | None) -> None:
    """Find the header known to hold each type: the SMT3 header defining the same name, else
    the namespace header."""
    for t in cat.values():
        hdr = None
        if smt3 is not None:
            hdr = smt3.header_of_type(t.clean)
            if hdr is None and t.kind == "define":
                hdr = smt3.header_of_macros([c[0] for c in t.td.consts])
        if hdr is None and t.ns:
            hdr = NS_HEADERS.get(t.ns, f"{t.ns[:1].lower()}{t.ns[1:]}.h")
        t.header = hdr


def _leaf(t: TypeInfo) -> str:
    return t.td.name.split(".")[-1]


def _game_statics(td: dumpcs.TypeDef) -> list[dumpcs.Method]:
    return [m for m in td.methods if m.static and not _is_csharp_method(m.name)]


# --- families ---------------------------------------------------------------------


@dataclass
class Family:
    key: str  # lowercase class name without the trailing `_`
    members: list[TypeInfo]  # top-level types
    primary: TypeInfo | None  # module whose .c also holds the family's globals
    header: str | None  # <key>.h: public prototypes, externs, macros, ALLCAPS defines/enums


class Families:
    """Top-level game types grouped by case-insensitive name (``sBtl``, ``SBTL``, ``SBTL_``,
    ``sbtl``), and where each family's code goes."""

    def __init__(self, cat: dict[str, TypeInfo]) -> None:
        self.cat = cat
        groups: dict[str, list[TypeInfo]] = {}
        for t in cat.values():
            if t.root == t.cname:
                groups.setdefault(families.family_key(t.td.name), []).append(t)
        self.by_key: dict[str, Family] = {}
        for key, ms in groups.items():
            mods = [t for t in ms if t.kind == "module"]
            code = [t for t in mods if not families.is_caps(t.td.name) and _game_statics(t.td)]
            primary = max(code, key=lambda t: (len(_game_statics(t.td)), t.td.name), default=None)
            header = f"{key}.h" if mods or len(ms) > 1 else None
            self.by_key[key] = Family(key, ms, primary, header)

    def key_of(self, t: TypeInfo) -> str:
        root = self.cat.get(t.root)
        return families.family_key((root or t).td.name.split(".")[0])

    def header_of(self, t: TypeInfo) -> str | None:
        fam = self.by_key.get(self.key_of(t))
        return fam.header if fam is not None else None

    def code_file(self, t: TypeInfo) -> str:
        """A module's .c: its outermost enclosing module's, else its own. An ALLCAPS class or a
        class without functions shares the family's main module's .c."""
        root = self.cat.get(t.root)
        owner = root if root is not None and root.kind == "module" else t
        fam = self.by_key.get(self.key_of(owner))
        bare = families.is_caps(owner.td.name) or not _game_statics(owner.td)
        if bare and fam is not None and fam.primary is not None:
            return f"{fam.primary.clean}.c"
        return f"{owner.clean}.c"

    def systems(self) -> frozenset[str]:
        """Family keys with a module: the C systems a module prefix can name."""
        return frozenset(
            k for k, f in self.by_key.items() if any(t.kind == "module" for t in f.members)
        )


# --- type resolution --------------------------------------------------------


@dataclass(frozen=True)
class Resolved:
    text: str  # clean C type token
    ref: str | None  # cname of a referenced game type, else None
    opaque: bool = False  # an unknown runtime type, only usable through a pointer


def _strip_wrapper(token: str) -> str:
    for suf in _WRAPPERS:
        if token.endswith(suf) and len(token) > len(suf):
            return token[: -len(suf)]
    return token


class Types:
    """Resolves il2cpp type tokens and C# type names against the catalog."""

    def __init__(self, cat: dict[str, TypeInfo]) -> None:
        self.cat = cat
        self.by_dotted: dict[str, list[TypeInfo]] = {}
        for t in cat.values():
            parts = t.td.name.split(".")
            for k in range(len(parts)):  # `Save_t`, `fld.Save_t`
                self.by_dotted.setdefault(".".join(parts[k:]), []).append(t)

    def resolve(self, token: str) -> Resolved:
        """A bare il2cpp type token (no ``struct``/pointer/``_array``) to a clean C type."""
        token = _strip_wrapper(token)
        if PRIMITIVE.match(token):
            return Resolved(STDINT_TYPE_TO_DECOMP_TYPE.get(token, token), None)
        if (t := self.cat.get(token)) is not None:
            if t.clean in MATH_PROVIDED:
                return Resolved(t.clean, None)
            return Resolved(t.clean, token)
        if token in IL2CPP_TYPE_TO_DECOMP_TYPE:
            return Resolved(IL2CPP_TYPE_TO_DECOMP_TYPE[token], None)
        if token in UNITY_TO_SDF_TYPE:
            return Resolved(UNITY_TO_SDF_TYPE[token], None)
        return Resolved("void", None, True)  # runtime, library, generic or compiler-made

    def name(self, token: str) -> str:
        """Clean spelling of a game or Unity math type name found in a body, else the token."""
        base = _strip_wrapper(token)
        if (t := self.cat.get(base)) is not None:
            return t.clean
        return UNITY_TO_SDF_TYPE.get(base, token)

    def param_ctype(self, expr: str) -> tuple[str, int, bool]:
        """A raw parameter or local type to ``(text, pointer depth, lost a level)``."""
        text, n, _ref, lost = _clean_ctype(expr, self, param=True)
        return text, n, lost

    def cs_enum(self, cs_type: str, near: TypeInfo | None) -> TypeInfo | None:
        """The game enum a C# type name denotes, preferring the namespace of ``near``."""
        cs_type = cs_type.removeprefix("ref ").removeprefix("out ").removeprefix("in ")
        cands = [t for t in self.by_dotted.get(cs_type, []) if t.kind == "enum"]
        if len(cands) > 1 and near is not None:
            cands = [t for t in cands if t.ns == near.ns] or cands
        return cands[0] if len(cands) == 1 else None

    def is_delegate(self, cname: str | None) -> bool:
        return cname is not None and (t := self.cat.get(cname)) is not None and (
            t.kind == "delegate"
        )


_INT_TYPES = frozenset({"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64"})


def rewrite_member(
    line: str,
    types: Types,
    *,
    owner: TypeInfo | None = None,
    cs_fields: dict[str, str] | None = None,
    sizes: hexrays.ArraySizes | None = None,
) -> tuple[str, set[str]]:
    """Rewrite one il2cpp member line to clean C. Returns ``(line, referenced cnames)``."""
    m = _MEMBER.match(line)
    if not m:
        return (line, set())
    type_tok, stars, name = m.group(1), m.group(2).count("*"), m.group(3)
    depth = 0
    while type_tok.endswith("_array"):
        type_tok = type_tok[: -len("_array")]
        depth += 1
    r = types.resolve(type_tok)
    # il2cpp.h spells an enum field as its underlying integer; dump.cs keeps the enum.
    cs_type = (cs_fields or {}).get(name)
    e = types.cs_enum(cs_type, owner) if cs_type and not depth and not stars else None
    if e is not None and r.text in _INT_TYPES:
        r = Resolved(e.clean, e.cname)
    if types.is_delegate(r.ref) and stars:  # the typedef is already a function pointer
        stars -= 1
    if r.opaque and not stars and not depth:  # an unknown value type: keep it a word wide
        stars = 1
    refs = {r.ref} if r.ref else set[str]()
    recovered = sizes.get((owner.cname, name)) if sizes and owner else None
    if depth == 1 and recovered is not None:
        count, is_value = recovered
        return (f"{r.text}{' ' if is_value else ' *'}{name}[{count}];", refs)
    if depth >= 2 and recovered is not None:
        return (f"{r.text} {'*' * (depth - 1)}{name}[{recovered[0]}];", refs)
    if depth:
        # No recoverable count: a pointer keeps the field one word wide and later offsets hold.
        return (f"{r.text} {'*' * depth}{name};", refs)
    return (f"{r.text} {'*' * stars}{name};" if stars else f"{r.text} {name};", refs)


def is_unity_class_member(line: str) -> bool:
    """A reference to a UnityEngine class (GameObject, Texture2D, ...): the remaster added these
    to records that have no such member on the PS2. Math types map to ``sdf*`` and stay."""
    m = _MEMBER.match(line)
    if m is None or "*" not in m.group(2):
        return False
    tok = re.sub(r"(?:_array|_o)+$", "", m.group(1))
    return tok.startswith("UnityEngine_") and tok not in UNITY_TO_SDF_TYPE


def _empty_derived(cname: str, blocks: dict[str, Block], cat: dict[str, TypeInfo]) -> str | None:
    """The base struct of a class that derives from a game struct and adds no fields."""
    b = blocks.get(f"{cname}_Fields")
    if b is None or b.members or not b.base:
        return None
    base = cat.get(b.base.removesuffix("_Fields"))
    return base.cname if base is not None and base.kind == "struct" else None


# --- functions ---------------------------------------------------------------


@dataclass
class Function:
    address: int
    linker: str  # Project.Kernel.dds3KernelCore$$AddProcessList
    mangled: str  # Project_Kernel_dds3KernelCore__AddProcessList
    owner: TypeInfo
    method: str  # AddProcessList
    ret: str
    params: list[tuple[str, str]]  # (clean type, name)
    refs: set[str]
    order: int  # declaration order in dump.cs, else a large number
    public: bool
    macro: bool = False  # an ALLCAPS function-like macro the port turned into a method
    file: str = ""  # where it is defined: a .c, or a header's macro section
    header: str | None = None  # header with its prototype (public functions)
    display: str = ""
    flag: str = ""  # symbols.txt: R prefix from SMT3/PS2, I inferred prefix, M macro
    dropped: tuple[bool, ...] = ()  # per parameter: the prototype dropped a pointer level


_SIGNATURE = re.compile(r"^(.+?)\s*\b(\w+) \((.*)\);$")


def _clean_ctype(
    expr: str, types: Types, *, param: bool = False
) -> tuple[str, int, str | None, bool]:
    """A C type expression to (base type, pointer depth, referenced cname, lost a level).

    A parameter ``T_o **`` (a class by reference) loses a level, except for a delegate, whose
    typedef is already the pointer.
    """
    expr = expr.replace("const ", "").replace("struct ", "").replace("__struct_ptr", "")
    stars = expr.count("*")
    tok = expr.replace("*", "").strip()
    arrays = 0
    while tok.endswith("_array"):
        tok = tok[: -len("_array")]
        arrays += 1
    r = types.resolve(tok)
    delegate = types.is_delegate(r.ref)
    obj = (tok.endswith("_o") or tok == "Il2CppObject") and not delegate
    text, n = pointer_depth(r.text, stars, arrays, obj=obj, param=param)
    lost = not arrays and stars == 2 and n == 1
    if delegate and n:
        n -= 1
    if r.opaque and not n:
        n = 1
    return text, n, r.ref, lost


def _ptr(text: str, n: int) -> str:
    return f"{text} {'*' * n}" if n else text


def parse_signature(
    sig: str, types: Types, cs_method: dumpcs.Method | None = None, owner: TypeInfo | None = None
) -> tuple[str, list[tuple[str, str]], set[str]] | None:
    """An Il2CppDumper C signature to ``(return, [(type, name)], referenced cnames)``.

    The ``MethodInfo`` context is dropped; ``__this`` becomes ``this``. Integer parameters
    that dump.cs types as an enum get the enum back. A class by reference (``T_o **``) is
    ``T *``; a Unity math value is ``const sdfT_t *``.
    """
    m = _SIGNATURE.match(sig.strip())
    if m is None:
        return None
    refs: set[str] = set()
    rtext, rstars, rref, _ = _clean_ctype(m.group(1), types)
    e = types.cs_enum(cs_method.ret, owner) if cs_method and cs_method.ret else None
    if e is not None and rtext in _INT_TYPES and not rstars:
        rtext, rref = e.clean, e.cname
    if rref:
        refs.add(rref)
    params: list[tuple[str, str]] = []
    raw_params = [p.strip() for p in _split_top(m.group(3))]
    cs_params = cs_method.params if cs_method else []
    explicit = [p for p in raw_params if "MethodInfo" not in p and not p.endswith(" __this")]
    enum_ok = len(explicit) == len(cs_params)
    i = 0
    for p in raw_params:
        if not p or "MethodInfo" in p:
            continue
        ptype, _, pname = p.rpartition(" ")
        text, n, ref, _ = _clean_ctype(ptype, types, param=True)
        if pname == "__this":
            pname = "this"
        else:
            e = types.cs_enum(cs_params[i][0], owner) if enum_ok else None
            if e is not None and text in _INT_TYPES and not n:
                text, ref = e.clean, e.cname
            i += 1
        params.append((_ptr(text, n), pname))
        if ref:
            refs.add(ref)
    return _ptr(rtext, rstars), params, refs


def _split_top(text: str) -> list[str]:
    out: list[str] = []
    depth, cur = 0, ""
    for ch in text:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def dropped_slots(sig: str, types: Types) -> tuple[bool, ...]:
    """Per parameter of a C signature (``MethodInfo`` excluded): its prototype dropped a level."""
    m = _SIGNATURE.match(sig.strip())
    if m is None:
        return ()
    params = [p.strip() for p in _split_top(m.group(3))]
    return tuple(
        _clean_ctype(p.rpartition(" ")[0], types, param=True)[3]
        for p in params
        if p and "MethodInfo" not in p
    )


def _sig_text(params: list[tuple[str, str]]) -> str:
    if not params:
        return "void"
    return ", ".join(f"{t}{'' if t.endswith('*') else ' '}{n}" for t, n in params)


def _type_chain_public(t: TypeInfo, cat: dict[str, TypeInfo]) -> bool:
    """``t`` and every class enclosing it are public."""
    parts = t.td.name.split(".")
    base = t.cname[: len(t.cname) - len(re.sub(r"\W", "_", t.td.name))]
    for k in range(1, len(parts) + 1):
        enc = cat.get(base + re.sub(r"\W", "_", ".".join(parts[:k])))
        if enc is not None and not enc.td.public:
            return False
    return True


def collect_functions(
    script_methods: list[dict[str, object]],
    cat: dict[str, TypeInfo],
    types: Types,
    *,
    instance: bool = False,
) -> list[Function]:
    """Every static game function of a module from script.json ``ScriptMethod`` (and its
    instance methods with ``instance``)."""
    cs: dict[tuple[str, str, int | None], tuple[int, dumpcs.Method]] = {}
    for t in cat.values():
        for i, meth in enumerate(t.td.methods):
            cs.setdefault((t.cname, meth.name, meth.rva), (i, meth))
    out: list[Function] = []
    for sm in script_methods:
        linker = str(sm["Name"])
        cls, sep, method = linker.partition("$$")
        if not sep or _is_csharp_method(method) or _JUNK_NAME.search(cls):
            continue
        owner = cat.get(re.sub(r"\W", "_", cls))
        if owner is None or owner.kind != "module":
            continue
        addr = int(str(sm["Address"]))
        order, meth = cs.get((owner.cname, method, addr), (1 << 30, None))
        sig = str(sm["Signature"])
        is_instance = not meth.static if meth is not None else " __this" in sig
        if is_instance and not instance:
            continue
        parsed = parse_signature(sig, types, meth, owner)
        if parsed is None:
            continue
        ret, params, refs = parsed
        mangled = sig.split(" (", 1)[0].split()[-1]
        public = (meth is None or meth.public) and _type_chain_public(owner, cat)
        macro = families.is_caps(_leaf(owner)) or families.is_macro_name(method)
        f = Function(addr, linker, mangled, owner, method, ret, params, refs, order, public, macro)
        f.dropped = dropped_slots(sig, types)
        out.append(f)
    return out


def place_functions(funcs: list[Function], fams: Families) -> None:
    """Set where each function is defined and declared.

    A method of an ALLCAPS class is a macro in the family header; an ALLCAPS method of a module
    is a macro in the module's .c. Other functions are defined in the module's .c and, when
    public, declared in the family header.
    """
    for f in funcs:
        hdr = fams.header_of(f.owner)
        caps_class = families.is_caps(_leaf(f.owner))
        f.file = hdr if f.macro and caps_class and hdr else fams.code_file(f.owner)
        f.header = hdr if f.public and not f.macro else None


# --- port classes -------------------------------------------------------------------


def drop_port_classes(
    cat: dict[str, TypeInfo],
    blocks: dict[str, Block],
    types_cs: list[dumpcs.TypeDef],
    script_methods: list[dict[str, object]],
) -> Counter[str]:
    """Remove the C#-only classes of the port from ``cat``.

    A class with instance methods (its own or a game base's), or deriving from a runtime class
    such as ``MonoBehaviour``, is port code. One with instance fields that kept code refers to
    stays as a plain struct (``port`` set); the rest go, with all their methods.

    Exception: a class without a base and with more than twice as many static game methods as
    instance methods (``itf``: 787 and 3) is a C module; only its instance methods go.
    """
    bases = families.BaseIndex(types_cs)
    port: set[str] = set()
    runtime: set[str] = set()
    for t in cat.values():
        if t.kind in ("enum", "delegate"):
            continue
        if families.runtime_derived(t.td, bases):
            runtime.add(t.cname)
            port.add(t.cname)
        elif families.inherits_instance_methods(t.td, bases):
            n_inst = len(families.instance_methods(t.td))
            if t.td.base or len(_game_statics(t.td)) <= 2 * n_inst:
                port.add(t.cname)
    types = Types(cat)

    def member_refs(t: TypeInfo, static: bool) -> set[str]:
        lines = _instance_members(t.cname, blocks)
        if static:
            sb = blocks.get(f"{t.cname}_StaticFields")
            lines = sb.members if sb else []
        refs: set[str] = set()
        for mem in lines:
            refs |= rewrite_member(mem, types, owner=t)[1]
        return refs

    funcs = collect_functions(script_methods, cat, types, instance=True)
    live: set[str] = set()
    for t in cat.values():
        if t.cname not in port:
            live |= member_refs(t, False) | member_refs(t, True)
    for sm in script_methods:  # delegate signatures
        cls, _, method = str(sm["Name"]).partition("$$")
        if method == "Invoke" and (d := cat.get(re.sub(r"\W", "_", cls))) is not None:
            parsed = parse_signature(str(sm["Signature"]), types)
            if d.kind == "delegate" and parsed is not None:
                live |= parsed[2]
    static = {(f.linker, f.address) for f in collect_functions(script_methods, cat, types)}
    instance = {(f.linker, f.address) for f in funcs} - static
    for f in funcs:
        if f.owner.cname not in port and (f.linker, f.address) not in instance:
            live |= f.refs
    kept: set[str] = set()
    changed = True
    while changed:
        changed = False
        for c in sorted(port - runtime - kept):
            if c in live and _instance_members(c, blocks):
                kept.add(c)
                live |= member_refs(cat[c], False)
                changed = True
    counts: Counter[str] = Counter()
    counts["port class"] = len(port)
    counts["port class kept as struct"] = len(kept)
    counts["port class dropped"] = len(port) - len(kept)
    counts["port method dropped"] = sum(
        1 for f in funcs if f.owner.cname in port or (f.linker, f.address) in instance
    )
    for c in port:
        if c in kept:
            cat[c].kind, cat[c].port = "struct", True
        else:
            del cat[c]
    return counts


# --- naming ------------------------------------------------------------------------


def _strip_collision_suffix(funcs: list[Function]) -> None:
    """A trailing `_` only avoided a clash in C#: drop it when no function of the same file
    has the bare name."""
    names: dict[str, set[str]] = {}
    for f in funcs:
        names.setdefault(f.file, set()).add(f.method)
    for f in funcs:
        bare = f.method.rstrip("_")
        if bare != f.method and bare and bare not in names[f.file]:
            f.display = bare


def restore_prefixes(
    funcs: list[Function],
    smt3: Smt3Index | None,
    ps2: frozenset[str] = frozenset(),
    systems: frozenset[str] = frozenset(),
) -> None:
    """Name each function, putting back the C module prefix ``P`` the port dropped.

    Only public, non-macro functions of a module ``X.c`` get one, and ``P`` must be a run of
    leading camel words of ``X`` (see ``families.prefix_fits``). In order:

    1. SMT3 ``X.c`` has ``P+M`` (flag R);
    2. ``P+M`` is any SMT3 symbol or a Raidou PS2 name, ``M`` not starting with the class word
       after ``P``; the longest ``P`` wins (flag R);
    3. the module's system prefix: its most common ``P`` from 1-2, else
       ``families.system_prefix`` (flag I), unless SMT3 ``X.c`` or PS2 has ``M`` bare.

    Rules 2 and 3 skip a name another function holds.
    """
    for f in funcs:
        f.display, f.flag = f.method, "M" if f.macro else ""
    _strip_collision_suffix(funcs)
    if smt3 is None and not ps2 and not systems:
        return
    symbols = smt3.symbols if smt3 is not None else {}
    known = {s for syms in symbols.values() for s in syms} | ps2
    by_file: dict[str, list[Function]] = {}
    for f in funcs:
        if f.file.endswith(".c"):
            by_file.setdefault(f.file, []).append(f)
    taken = {f.display for f in funcs} | {f.method for f in funcs}
    used: dict[str, Counter[str]] = {file: Counter() for file in by_file}

    def give(f: Function, prefix: str, flag: str) -> None:
        f.display, f.flag = prefix + f.display, flag
        taken.add(f.display)
        used[f.file][prefix] += 1

    def open_(fs: list[Function]) -> list[Function]:
        return [f for f in fs if f.public and not f.macro and not f.flag]

    for file, fs in by_file.items():  # 1: same module in SMT3
        cls = Path(file).stem
        syms = set(symbols.get(file, []))
        methods = {f.display for f in fs}
        claim: dict[str, tuple[str, str]] = {}  # SMT3 symbol -> (method, prefix), longest method
        for sym in syms - methods:
            for m in methods:
                longer = sym not in claim or len(m) > len(claim[sym][0])
                if longer and sym.endswith(m) and len(sym) > len(m):
                    claim[sym] = (m, sym[: -len(m)])
        by_method: dict[str, list[str]] = {}
        for m, p in claim.values():
            if families.prefix_fits(cls, p, m, strict=False):
                by_method.setdefault(m, []).append(p)
        for f in open_(fs):
            if ps := by_method.get(f.display):
                give(f, max(ps, key=len), "R")
    for file, fs in by_file.items():  # 2: anywhere in SMT3 or PS2
        cls = Path(file).stem
        for f in open_(fs):
            cands = [
                p for p, _ in families.camel_prefixes(cls)
                if p + f.display in known and p + f.display not in taken
                and families.prefix_fits(cls, p, f.display)
            ]
            if cands:
                give(f, max(cands, key=len), "R")
    for file, fs in by_file.items():  # 3: the module's system prefix
        cls = Path(file).stem
        bare = set(symbols.get(file, [])) | ps2
        common = used[file].most_common(1)
        p = common[0][0] if common else families.system_prefix(cls, systems)
        if p is None:
            continue
        for f in open_(fs):
            name = p + f.display
            if (
                f.display not in bare and name not in taken
                and families.prefix_fits(cls, p, f.display)
            ):
                give(f, p, "I")


def name_functions(funcs: list[Function]) -> None:
    """Make display names unique per file: overloads get ``_2``, ``_3``; methods of nested
    classes that clash with another class's get the class name as a prefix."""
    by_name: dict[tuple[str, str], list[Function]] = {}
    for f in funcs:
        by_name.setdefault((f.file, f.display), []).append(f)
    for fs in by_name.values():
        if len({f.owner.cname for f in fs}) > 1:
            for f in fs:
                if f.owner.cname != f.owner.root:
                    f.display = f"{f.owner.clean}_{f.display}"
    taken: set[tuple[str, str]] = set()
    for f in sorted(funcs, key=lambda f: (f.file, f.order, f.address)):
        base, n = f.display, 1
        while (f.file, f.display) in taken:
            n += 1
            f.display = f"{base}_{n}"
        taken.add((f.file, f.display))


# --- routing -------------------------------------------------------------------


@dataclass
class _FileModel:
    structs: list[tuple[str, list[str]]] = field(default_factory=list[tuple[str, list[str]]])
    enums: list[tuple[str, list[tuple[str, str]]]] = field(
        default_factory=list[tuple[str, list[tuple[str, str]]]]
    )
    delegates: list[tuple[str, str]] = field(default_factory=list[tuple[str, str]])
    # (owner, [(member line, public)]): definitions in a .c
    statics: list[tuple[str, list[tuple[str, bool]]]] = field(
        default_factory=list[tuple[str, list[tuple[str, bool]]]]
    )
    externs: list[str] = field(default_factory=list[str])  # member lines declared extern
    defines: list[tuple[str, list[tuple[str, str]]]] = field(
        default_factory=list[tuple[str, list[tuple[str, str]]]]
    )
    funcs: list[Function] = field(default_factory=list[Function])  # defined here
    protos: list[Function] = field(default_factory=list[Function])  # declared here (headers)
    macros: list[Function] = field(default_factory=list[Function])
    aliases: list[str] = field(default_factory=list[str])  # structs defined as a typedef of a base
    header: str | None = None  # a .c's own family header
    includes: set[str] = field(default_factory=set[str])  # headers of shared statics used here
    refs: set[str] = field(default_factory=set[str])  # cnames referenced
    defined: set[str] = field(default_factory=set[str])  # cnames defined here

    def empty(self) -> bool:
        return not (
            self.structs or self.enums or self.delegates or self.statics or self.externs
            or self.defines or self.funcs or self.protos or self.macros or self.aliases
        )


# Unreferenced top-level enums and constant groups of the root namespace share a header.
_UNREFERENCED_HEADER: dict[str, str] = {"enum": "enums.h", "define": "defines.h"}


def _header_name(clean: str) -> str:
    return f"{clean}.h"


def route_types(
    cat: dict[str, TypeInfo],
    refs_by_unit: dict[str, set[str]],
    fams: Families | None = None,
) -> None:
    """Set ``file`` on every catalog type.

    Modules go to their code file. A data type (struct, enum, delegate, constant group) goes to
    its family header (a top-level type whose family has a module or several members), else
    the SMT3 header defining the same name, else its namespace header, else (nested in a
    module) that module's .c or family header, else the one file referencing it (a .c and its
    own header count as the header), else (an unreferenced top-level enum or constant group)
    ``enums.h`` or ``defines.h``, else ``<Type>.h``.
    """
    fams = fams or Families(cat)
    pending: list[TypeInfo] = []
    own_header: dict[str, str] = {}
    for t in cat.values():
        if t.kind == "module":
            t.file = fams.code_file(t)
            if (h := fams.header_of(t)) is not None:
                own_header.setdefault(t.file, h)
            continue
        fam = fams.by_key.get(fams.key_of(t))
        if t.root == t.cname and fam is not None and fam.header is not None:
            t.file = fam.header
        elif t.header is not None:
            t.file = t.header
        else:
            t.file = _header_name(t.clean)
            pending.append(t)
    referenced_by: dict[str, set[str]] = {}
    for unit, refs in refs_by_unit.items():
        for r in refs:
            if r != unit:
                referenced_by.setdefault(r, set()).add(unit)

    def unit_file(u: str) -> str:
        return u if u.endswith((".c", ".h")) else cat[u].file

    for _ in range(20):
        changed = False
        for t in pending:
            users = {unit_file(u) for u in referenced_by.get(t.cname, set())}
            users = {own_header[u] if own_header.get(u) in users else u for u in users}
            root = cat.get(t.root)
            if root is not None and root is not t and root.kind == "module":
                rootc = fams.code_file(root)
                new = rootc if users <= {rootc} else fams.header_of(root) or rootc[:-2] + ".h"
            elif len(users) == 1:
                new = next(iter(users))
            elif not users and t.root == t.cname and t.kind in _UNREFERENCED_HEADER:
                new = _UNREFERENCED_HEADER[t.kind]
            else:
                new = _header_name(t.clean)
            if new != t.file:
                t.file, changed = new, True
        if not changed:
            break
    # One spelling per header on a case-insensitive file system, the family's if any.
    spellings: dict[str, set[str]] = {}
    for f in [t.file for t in cat.values()] + [f.header for f in fams.by_key.values() if f.header]:
        if f.endswith(".h"):
            spellings.setdefault(f.lower(), set()).add(f)
    canon = {n: min(ns, key=lambda n: (n != n.lower(), n)) for ns in spellings.values() for n in ns}
    for t in cat.values():
        t.file = canon.get(t.file, t.file)


# --- building ----------------------------------------------------------------


_FLOAT_CS = frozenset({"float", "double", "decimal", "Single", "Double"})


def _const_value(cs_type: str, value: str) -> str:
    """A dump.cs constant initializer as C."""
    v = value.strip()
    if cs_type in _FLOAT_CS:
        return v.replace(",", ".")  # dumped under a comma-decimal locale
    if cs_type == "bool":
        return {"True": "1", "False": "0"}.get(v, v)
    return v


def _consts(t: TypeInfo) -> list[tuple[str, str]]:
    return [(n, _const_value(ct, v)) for n, ct, v in t.td.consts]


def _delegate_typedef(
    t: TypeInfo, invoke: dict[str, str], types: Types
) -> tuple[str, set[str]]:
    sig = invoke.get(t.cname)
    parsed = parse_signature(sig, types) if sig else None
    if parsed is None:
        return f"typedef void (*{t.clean})(void);", set()
    ret, params, refs = parsed
    params = [(ty, n) for ty, n in params if n != "this"]
    if ret == t.clean:  # returns its own type, which C cannot spell
        ret = "void *"
    sep = "" if ret.endswith("*") else " "
    return f"typedef {ret}{sep}(*{t.clean})({_sig_text(params)});", refs - {t.cname}


@dataclass
class Build:
    files: dict[str, _FileModel]
    cat: dict[str, TypeInfo]
    funcs: list[Function]
    counts: Counter[str]  # emitted declarations by kind
    fams: Families
    alias: dict[str, str] = field(default_factory=dict[str, str])  # clean name -> base's


def build(
    blocks: dict[str, Block],
    types_cs: list[dumpcs.TypeDef],
    script_methods: list[dict[str, object]],
    smt3: Smt3Index | None = None,
    sizes: hexrays.ArraySizes | None = None,
) -> Build:
    """Catalog, route and render-ready models for every emitted file."""
    cat = build_catalog(types_cs, blocks)
    counts = drop_port_classes(cat, blocks, types_cs, script_methods)
    _assign_clean_names(cat)
    assign_headers(cat, smt3)
    fams = Families(cat)
    types = Types(cat)
    funcs = collect_functions(script_methods, cat, types)
    place_functions(funcs, fams)
    invoke = {
        re.sub(r"\W", "_", str(sm["Name"]).split("$$")[0]): str(sm["Signature"])
        for sm in script_methods
        if str(sm["Name"]).endswith("$$Invoke")
    }

    # Render every type's members first: routing needs what each unit references.
    inst_of: dict[str, list[str]] = {}
    stat_of: dict[str, list[tuple[str, bool]]] = {}
    unit_refs: dict[str, set[str]] = {}
    delegate_text: dict[str, str] = {}
    alias: dict[str, str] = {}

    def unit(t: TypeInfo) -> str:
        return fams.code_file(t) if t.kind == "module" else t.cname

    for t in cat.values():
        refs = unit_refs.setdefault(unit(t), set())
        cs_fields = {f.name: f.type for f in t.td.fields}
        public = {f.name: f.public for f in t.td.fields}
        if t.kind == "struct" and (base := _empty_derived(t.cname, blocks, cat)) is not None:
            alias[t.clean] = cat[base].clean  # same layout: a typedef of the base
            refs.add(base)
            continue
        if t.kind in ("module", "struct"):
            inst: list[str] = []
            for mem in _instance_members(t.cname, blocks):
                if is_unity_class_member(mem):
                    continue
                line, r = rewrite_member(mem, types, owner=t, cs_fields=cs_fields, sizes=sizes)
                inst.append(line)
                refs |= r
            inst_of[t.cname] = inst
            sblock = blocks.get(f"{t.cname}_StaticFields")
            if t.kind == "module" and sblock is not None:
                stat: list[tuple[str, bool]] = []
                hdr = fams.header_of(t)
                for mem in sblock.members:
                    if is_unity_class_member(mem):
                        continue
                    line, r = rewrite_member(
                        mem, types, owner=t, cs_fields=cs_fields, sizes=sizes
                    )
                    m = _MEMBER.match(mem)
                    pub = public.get(m.group(3), False) if m else False
                    stat.append((line, pub))
                    refs |= r
                    if pub and hdr is not None:
                        unit_refs.setdefault(hdr, set()).update(r)
                stat_of[t.cname] = stat
        elif t.kind == "delegate":
            delegate_text[t.cname], r = _delegate_typedef(t, invoke, types)
            refs |= r
    for f in funcs:
        unit_refs.setdefault(f.file, set()).update(f.refs)
        if f.header is not None:
            unit_refs.setdefault(f.header, set()).update(f.refs)
    route_types(cat, unit_refs, fams)

    files: dict[str, _FileModel] = {}
    for t in cat.values():
        model = files.setdefault(t.file, _FileModel())
        model.defined.add(t.cname)
        if t.kind == "enum":
            model.enums.append((t.clean, _consts(t)))
            continue
        if t.kind == "delegate":
            model.delegates.append((t.clean, delegate_text[t.cname]))
            model.refs |= unit_refs.get(unit(t), set())
            continue
        hdr = fams.header_of(t) if t.kind == "module" else None
        if t.clean in alias:
            model.aliases.append(t.clean)
        if t.td.consts and not t.port:
            caps = t.kind == "module" and families.is_caps(_leaf(t)) and hdr is not None
            dest = files.setdefault(hdr, _FileModel()) if caps and hdr else model
            dest.defines.append((t.clean, _consts(t)))
        if inst_of.get(t.cname):
            model.structs.append((t.clean, inst_of[t.cname]))
        stat = stat_of.get(t.cname, [])
        if stat:
            model.statics.append((t.clean, stat))
            pub = [line for line, p in stat if p]
            if pub and hdr is not None:
                files.setdefault(hdr, _FileModel()).externs += pub
                files[hdr].refs |= unit_refs.get(hdr, set())
        model.refs |= unit_refs.get(unit(t), set())
    for f in funcs:
        model = files.setdefault(f.file, _FileModel())
        (model.macros if f.macro else model.funcs).append(f)
        model.refs |= f.refs
        if f.header is not None:
            files.setdefault(f.header, _FileModel()).protos.append(f)
            files[f.header].refs |= f.refs
    for file, model in files.items():
        if file.endswith(".c"):
            owners = [f.owner for f in model.funcs] + [
                t for t in cat.values() if t.kind == "module" and t.file == file
            ]
            hdrs = [h for o in owners if (h := fams.header_of(o)) is not None]
            model.header = hdrs[0] if hdrs else None
    for t in cat.values():
        counts[t.kind] += 1
    counts["function"] = sum(1 for f in funcs if not f.macro)
    counts["macro"] = sum(1 for f in funcs if f.macro)
    counts["struct alias"] = len(alias)
    return Build(files, cat, funcs, counts, fams, alias)


# --- rendering -----------------------------------------------------------------


def _macro_line(name: str, value: str) -> str:
    return f"#define {name} {value}"


def _proto(f: Function) -> str:
    sep = "" if f.ret.endswith("*") else " "
    return f"{f.ret}{sep}{f.display}({_sig_text(f.params)})"


def _fake_value(t: str, enums: frozenset[str]) -> str:
    """A zero value of type ``t``: 0 for scalars, pointers and enums, else a compound literal."""
    t = t.strip()
    if t.endswith("*") or PRIMITIVE.match(t) or t in _SCALARS or t in enums:
        return "0"
    return f"({t}){{0}}"


_SCALARS = frozenset(
    {"void", "bool", "char", "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32",
     "f64", "intptr_t", "uintptr_t", "size_t"}
)


def _source_order(f: Function) -> tuple[int, int, int]:
    return (f.owner.td.index, f.order, f.address)


def _static(f: Function) -> str:
    return "" if f.public else "static "


def _stub(
    f: Function, callees: list[Function], enums: frozenset[str]
) -> str:
    """A body made of the call graph: one ``callee(zeros);`` per edge, then a return."""
    body = "".join(f"    {_call(c, enums)};\n" for c in callees)
    tail = "" if f.ret == "void" else f"    return {_fake_value(f.ret, enums)};\n"
    return f"{_static(f)}{_proto(f)} {{\n{body}{tail}}}"


def _call(c: Function, enums: frozenset[str]) -> str:
    return f"{c.display}({', '.join(_fake_value(t, enums) for t, _ in c.params)})"


def _macro_params(f: Function) -> str:
    return ", ".join(n for _, n in f.params if n != "this")


def render_macro(
    f: Function, callees: list[Function], enums: frozenset[str], body: str | None = None
) -> str:
    """A function-like ``#define``. A Hex-Rays body becomes ``(expr)`` when it is one
    ``return``, ``do { ... } while (0)`` when it returns nothing, else a ``static inline``
    function. A stub is the call graph as a comma expression."""
    head = f"// {f.address:#x}: {_proto(f)}"
    name = f"{f.display}({_macro_params(f)})"
    if body is not None:
        lines = [ln.strip() for ln in body.strip().split("\n") if ln.strip()]
        if len(lines) == 1 and lines[0].startswith("return ") and lines[0].endswith(";"):
            return f"{head}\n#define {name} ({lines[0][len('return ') : -1]})"
        if f.ret == "void" and not any("return" in ln or "//" in ln for ln in lines):
            inner = "".join(f"    {ln} \\\n" for ln in lines)
            return f"{head}\n#define {name} do {{ \\\n{inner}}} while (0)"
        return f"{head}\nstatic inline {_proto(f)} {{\n{body}\n}}"
    parts = [_call(c, enums) for c in callees]
    parts.append("(void)0" if f.ret == "void" else _fake_value(f.ret, enums))
    return f"{head}\n#define {name} ({', '.join(parts)})"


def _tag_kind(name: str) -> str:
    """`_u` types are PS2 unions, laid out as overlapping members."""
    return "union" if name.endswith("_u") else "struct"


_VALUE_MEMBER = re.compile(r"^(?:const )?(\w+) \w+(?:\[[^\]]*\])*;")


def _by_value_order(structs: list[tuple[str, list[str]]]) -> list[tuple[str, list[str]]]:
    """Order structs so one embedded by value (or as an array element) precedes its user."""
    by_name = dict(structs)
    out: list[tuple[str, list[str]]] = []
    seen: set[str] = set()

    def visit(name: str) -> None:
        if name in seen:
            return
        seen.add(name)
        for line in by_name[name]:
            m = _VALUE_MEMBER.match(line)
            if m and m.group(1) in by_name and m.group(1) != name:
                visit(m.group(1))
        out.append((name, by_name[name]))

    for name, _members in structs:
        visit(name)
    return out


def _emitted(b: Build, file: str) -> bool:
    return file in b.files and not b.files[file].empty()


def render_file(
    file: str,
    model: _FileModel,
    b: Build,
    graph: dict[int, list[Function]] | None = None,
    bodies: dict[int, str] | None = None,
) -> str:
    cat = b.cat
    is_header = file.endswith(".h")
    enums = frozenset(t.clean for t in cat.values() if t.kind == "enum")
    callees = {f.address: (graph or {}).get(f.address, []) for f in model.funcs + model.macros}
    # Public callees are declared in their headers; others need a prototype here.
    includes: set[str] = set()
    if model.header is not None and _emitted(b, model.header):
        includes.add(model.header)
    includes |= {h for h in model.includes if _emitted(b, h)}
    local_protos: dict[str, Function] = {}
    refs = set(model.refs)
    for cs in callees.values():
        for c in cs:
            if c.file == file:
                continue
            if c.header is not None and _emitted(b, c.header):
                includes.add(c.header)
            elif c.macro and c.file.endswith(".h"):
                includes.add(c.file)
            elif not c.macro:
                local_protos.setdefault(c.display, c)
                refs |= c.refs
    # Enums and delegate typedefs cannot be forward-declared: include the header defining
    # each one used here. Structs are forward-declared.
    tags: set[str] = set()
    for r in refs | model.defined:
        t = cat.get(r)
        if t is None:
            continue
        if t.kind in ("enum", "delegate"):
            if t.file != file and t.file.endswith(".h"):
                includes.add(t.file)
        elif t.kind in ("struct", "module") and t.clean not in MATH_PROVIDED and (
            r in refs or any(name == t.clean for name, _ in model.structs)
        ):
            tags.add(t.clean)
    tags |= set(model.aliases)
    includes.discard(file)
    out: list[str] = []
    if is_header:
        out.append("#pragma once")
    out.append(f'#include "{COMMON_HEADER}"')
    out += [f'#include "{inc}"' for inc in sorted(includes)]
    out.append("")
    for _owner, macros in model.defines:
        out += [_macro_line(n, v) for n, v in macros]
        out.append("")
    for name, members in model.enums:
        out.append("typedef enum {")
        out += [f"    {m} = {v}," for m, v in members]
        out += [f"}} {name};", ""]
    if tags:
        for t in sorted(tags):
            tag = b.alias.get(t, t)
            out.append(f"typedef {_tag_kind(tag)} {tag} {t};")
        out.append("")
    for _name, text in model.delegates:
        out += [text]
    if model.delegates:
        out.append("")
    for name, members in _by_value_order(model.structs):
        out.append(f"{_tag_kind(name)} {name} {{")
        out += [f"    {m}" for m in members]
        out += ["};", ""]
    if model.externs:
        out += [f"extern {m}" for m in model.externs]
        out.append("")
    for _owner, members in model.statics:
        out += [f"{'' if pub else 'static '}{m}" for m, pub in members]
        out.append("")
    protos = [f"{_proto(f)};" for f in sorted(model.protos, key=_source_order)]
    funcs = sorted(model.funcs, key=_source_order)
    protos += [f"static {_proto(f)};" for f in funcs if not f.public]
    protos += [f"{_proto(c)};" for c in local_protos.values()]
    if protos:
        out += protos
        out.append("")
    if model.macros:
        out.append("// macros")
        for f in sorted(model.macros, key=_source_order):
            body = bodies.get(f.address) if bodies else None
            out += [render_macro(f, callees[f.address], enums, body), ""]
    for f in funcs:
        out.append(f"// {f.address:#x}")
        if bodies and f.address in bodies:
            out.append(f"{_static(f)}{_proto(f)} {{\n{bodies[f.address]}\n}}")
        else:
            out.append(_stub(f, callees[f.address], enums))
        out.append("")
    return "\n".join(out).rstrip() + "\n"


_FLAG_NOTES = (
    "# R: C module prefix restored from SMT3 or the Raidou PS2 names",
    "# I: C module prefix inferred from the module's system prefix",
    "# M: function-like macro (an ALLCAPS method)",
)


def symbol_map(funcs: list[Function]) -> str:
    """Every emitted function by address: ``<address>  <symbol>  <source>  <linker>  [R|I|M]``."""
    rows = sorted(funcs, key=lambda f: f.address)
    out = [
        "# Raidou HD reconstructed sources: function address map",
        f"# {len(rows)} functions, ordered by binary address",
        *_FLAG_NOTES,
        "# address     symbol  source  linker-name  [flag]",
    ]
    out += [
        f"{f.address:#010x}  {f.display}  {f.file}  {f.linker}{'  ' + f.flag if f.flag else ''}"
        for f in rows
    ]
    return "\n".join(out) + "\n"


# --- driver ------------------------------------------------------------------


def load_ps2_names(path: Path) -> frozenset[str]:
    """Function names of the Raidou PS2 IDB, one ``<hex address> <name>`` per line."""
    names: set[str] = set()
    for line in path.read_text(encoding="utf-8").split("\n"):
        parts = line.split()
        if len(parts) == 2 and not parts[1].startswith(("sub_", "nullsub_", "j_")):
            names.add(parts[1])
    return frozenset(names)


def load_array_lengths(path: Path) -> hexrays.ArraySizes:
    """Array counts observed at runtime, ``{cname: {field: [count, is_value]}}``, if present."""
    if not path.is_file():
        return {}
    raw: dict[str, dict[str, list[object]]] = json.loads(path.read_text(encoding="utf-8"))
    return {
        (cname, member): (int(str(v[0])), bool(v[1]))
        for cname, members in raw.items()
        for member, v in members.items()
    }


def _string_literals(script: dict[str, list[dict[str, object]]]) -> dict[int, str]:
    """``StringLiteral_<n>`` -> text: ``n`` is the 1-based index into ``ScriptString``."""
    return {i: str(s["Value"]) for i, s in enumerate(script.get("ScriptString", []), 1)}


def run(
    il2cpp_h: Path,
    dump_cs: Path,
    script_json: Path,
    outdir: Path,
    *,
    smt3: Path | None = None,
    only: set[str] | None = None,
    source_c: Path | None = None,
    clean_body: bool = False,
    ps2_names: Path | None = None,
) -> Counter[str]:
    """Generate ``include/*.h``, ``src/*.c`` and ``symbols.txt`` under ``outdir``."""
    with il2cpp_h.open(encoding="utf-8", errors="replace") as fh:
        blocks = parse_blocks(fh)
    with dump_cs.open(encoding="utf-8", errors="replace") as fh:
        types_cs = dumpcs.parse(fh)
    script = json.loads(script_json.read_text(encoding="utf-8"))
    index = load_smt3(smt3) if smt3 is not None else None
    # Constructor counts win; runtime observations only fill in what they did not resolve.
    sizes = load_array_lengths(il2cpp_h.parent / "array_lengths.json")
    layout = Layout(blocks)

    def static_member(cls: str, offset: int, width: int | None) -> str | None:
        return layout.member_at(f"{cls}_StaticFields", offset, width)

    if source_c is not None:
        with source_c.open(encoding="utf-8", errors="replace") as fh:
            sizes |= hexrays.array_sizes(fh, static_member)
    b = build(blocks, types_cs, script["ScriptMethod"], index, sizes)
    ps2 = load_ps2_names(ps2_names) if ps2_names is not None else frozenset[str]()
    restore_prefixes(b.funcs, index, ps2, b.fams.systems())
    name_functions(b.funcs)
    b.counts["enum prefixed"] = unique_enum_members(b.files, (f.display for f in b.funcs))
    for f in b.funcs:
        b.counts[f"function {f.flag}" if f.flag else "function bare"] += 1

    graph: dict[int, list[Function]] | None = None
    bodies: dict[int, str] | None = None
    if source_c is not None:
        graph, bodies = _from_source(
            source_c, b, _string_literals(script), clean_body, static_member, layout.members_at
        )

    include_dir, src_dir = outdir / "include", outdir / "src"
    include_dir.mkdir(parents=True, exist_ok=True)
    src_dir.mkdir(parents=True, exist_ok=True)
    (include_dir / COMMON_HEADER).write_text(COMMON_BODY, encoding="utf-8")
    for file, model in b.files.items():
        if only is not None and file.rsplit(".", 1)[0] not in only:
            continue
        if model.empty():
            continue
        dest = (include_dir if file.endswith(".h") else src_dir) / file
        dest.write_text(render_file(file, model, b, graph, bodies), encoding="utf-8")
    if only is None:
        (outdir / "symbols.txt").write_text(symbol_map(b.funcs), encoding="utf-8")
    return b.counts


def unique_enum_members(files: dict[str, _FileModel], taken: Iterable[str]) -> int:
    """Prefix the members of an enum with its name when one of them is also another enum's
    member, a define or a name in `taken`: C has one namespace for them. Returns the number
    of enums renamed."""
    seen = Counter(m for model in files.values() for _, ms in model.enums for m, _ in ms)
    seen.update(n for model in files.values() for _, ds in model.defines for n, _ in ds)
    seen.update({n: 2 for n in [*taken, "NULL"]})
    renamed = 0
    for model in files.values():
        for i, (name, members) in enumerate(model.enums):
            if all(seen[m] < 2 for m, _ in members):
                continue
            pre = f"{name}_"
            model.enums[i] = (name, [
                (m if m.startswith(pre) else pre + re.sub(r"^_(?=\d)", "", m), v)
                for m, v in members
            ])
            renamed += 1
    return renamed


def display_slots(funcs: Iterable[Function]) -> dict[str, tuple[bool, ...]]:
    """Dropped-level flags by display name; a name shared by functions that disagree is left out."""
    out: dict[str, tuple[bool, ...]] = {}
    conflict: set[str] = set()
    for f in funcs:
        if f.display in out and out[f.display] != f.dropped:
            conflict.add(f.display)
        out[f.display] = f.dropped
    return {d: flags for d, flags in out.items() if d not in conflict and any(flags)}


def _member_name(line: str) -> str:
    m = re.search(r"(\w+)(?:\[[^\]]*\])?;$", line)
    return m.group(1) if m else ""


def share_statics(
    b: Build, uses: Iterable[tuple[str, str, str]], named: dict[str, Function]
) -> int:
    """Make a private module static that a function in another file touches a global declared
    ``extern`` in the module's family header. Returns how many statics changed."""
    by_clean = {t.clean: t.cname for t in b.cat.values()}
    changed = 0
    for fn, cls, fld in sorted(uses):
        user, owner = named.get(fn), b.cat.get(cls)
        if user is None or owner is None or owner.kind != "module" or user.file == owner.file:
            continue
        hdr = b.fams.header_of(owner)
        model = b.files.get(owner.file)
        if hdr is None or model is None:
            continue
        for name, members in model.statics:
            if name != owner.clean:
                continue
            for i, (line, pub) in enumerate(members):
                if not pub and _member_name(line) == fld:
                    members[i] = (line, True)
                    header = b.files.setdefault(hdr, _FileModel())
                    header.externs.append(line)
                    if (ref := by_clean.get(line.split()[0])) is not None:
                        header.refs.add(ref)
                    changed += 1
        if hdr != user.file:
            b.files.setdefault(user.file, _FileModel()).includes.add(hdr)
    return changed


def _from_source(
    source_c: Path,
    b: Build,
    strings: dict[int, str],
    clean_body: bool,
    static_member: hexrays.StaticMember | None = None,
    object_member: hexrays.ObjectMember | None = None,
) -> tuple[dict[int, list[Function]], dict[int, str] | None]:
    """Call graph and (optionally) cleaned bodies from a Hex-Rays export, keyed by address.

    Names in the export are joined to functions through its ``//----- (ADDR)`` separators,
    so overloads (which share a mangled name) still resolve. Module statics another file
    touches become globals (`share_statics`).
    """
    with source_c.open(encoding="utf-8", errors="replace") as fh:
        addr_of = hexrays.function_addresses(fh)
    by_addr = {f.address: f for f in b.funcs}
    named = {n: by_addr[a] for n, a in addr_of.items() if a in by_addr}
    with source_c.open(encoding="utf-8", errors="replace") as fh:
        raw_graph = hexrays.call_graph(fh, frozenset(named))
    graph = {
        named[n].address: [named[c] for c in cs] for n, cs in raw_graph.items() if n in named
    }
    with source_c.open(encoding="utf-8", errors="replace") as fh:
        uses = hexrays.static_field_uses(fh, static_member)
    b.counts["static made global"] = share_statics(b, uses, named)
    if not clean_body:
        return graph, None
    names = {n: f.display for n, f in named.items()}
    arity: dict[str, int] = {}
    for f in b.funcs:
        arity.setdefault(f.display, len(f.params))
    types = Types(b.cat)
    with source_c.open(encoding="utf-8", errors="replace") as fh:
        ctors = hexrays.default_ctors(fh)
    with source_c.open(encoding="utf-8", errors="replace") as fh:
        raw_bodies, reasons = hexrays.clean_bodies(
            fh, names, arity, strings, types.name, display_slots(b.funcs), types.param_ctype,
            static_member, object_member, ctors,
        )
    bodies = {named[n].address: body for n, body in raw_bodies.items() if n in named}
    flagged = {named[n].address: r for n, r in reasons.items() if n in named}
    exported = {f.address for f in named.values()}
    for f in b.funcs:
        if f.address not in exported:
            b.counts["body stub: not in export"] += 1
        elif f.address not in bodies:
            b.counts["body stub: unbalanced braces"] += 1
        elif f.address in flagged:
            b.counts[f"body approximate: {flagged[f.address]}"] += 1
        else:
            b.counts["body clean"] += 1
    return graph, bodies


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("inputs", type=Path, help="directory holding il2cpp.h, dump.cs, script.json")
    ap.add_argument("-o", "--outdir", type=Path, required=True, help="output directory")
    ap.add_argument(
        "--smt3", type=Path,
        help="SMT3 index JSON (or SMT3 repo checkout) for header routing and name prefixes",
    )
    ap.add_argument(
        "--ps2-names", type=Path,
        help="Raidou PS2 function names (`<hex address> <name>` lines) as prefix evidence",
    )
    ap.add_argument("--only", help="comma-separated file basenames to emit (e.g. kernel,libsdf)")
    ap.add_argument("--stats", action="store_true", help="print emitted declaration counts")
    ap.add_argument("--source", type=Path, help="Hex-Rays .c export: array sizes, call graph")
    ap.add_argument(
        "--bodies", action="store_true", help="emit cleaned bodies from --source (else stubs)"
    )
    args = ap.parse_args(argv)
    only = set(args.only.split(",")) if args.only else None
    d: Path = args.inputs
    counts = run(
        d / "il2cpp.h", d / "dump.cs", d / "script.json", args.outdir, smt3=args.smt3,
        only=only, source_c=args.source, clean_body=args.bodies, ps2_names=args.ps2_names,
    )
    if args.stats:
        for kind, count in counts.most_common():
            print(f"  {count:6} {kind}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
