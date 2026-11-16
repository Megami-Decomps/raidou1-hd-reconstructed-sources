"""Hex-Rays "Show casts" output: drop casts that only restate a type, fold Unity accessors.

Runs on the raw body, before type names are mapped, so every type is still Hex-Rays text.
"""

from __future__ import annotations

import re
from collections.abc import Iterable, Iterator
from decimal import Decimal

_PRIM_WORD = (
    r"__int\d+|_?[A-Z]{1,2}WORD|_BYTE|_BOOL|int\d+_t|uint\d+_t|intptr_t|uintptr_t|size_t"
    r"|float|double|int|char|short|long|bool|void|_UNKNOWN|float\d+x\d+_t|u?int\d+x\d+_t|[su]\d+|f32|f64"
)
_QUAL = r"(?:(?:const|struct|unsigned|signed|volatile) )*"
_PTR_TYPE = rf"{_QUAL}[A-Za-z_]\w*(?: ?\*)+"
_BARE_TYPE = rf"{_QUAL}(?:{_PRIM_WORD})"
_FN_PTR_TYPE = r"[A-Za-z_][\w ]*? ?\(__fastcall \*+\)\([^()]*\)"
_CAST = re.compile(
    rf"(?<![\w\]])\(({_FN_PTR_TYPE}|{_PTR_TYPE}|{_BARE_TYPE})\)(?=[\w(*&~!\-+])"
)
_DECL = re.compile(
    rf"(?m)^[ \t]+({_QUAL}[A-Za-z_]\w*)((?: ?\*)*) ?(\w+)(?:\[\d+\])?(?: = [^;]*)?;"
)
_PRIM_TYPE = re.compile(rf"^{_QUAL}(?:{_PRIM_WORD})$")
_GENERIC_POINTEE = re.compile(
    r"^(?:Il2CppObject|Il2CppClass|Il2CppType|MethodInfo(?:_\d+)?|Il2CppArray|_UNKNOWN)$"
)
_RUNTIME_TYPE = re.compile(r"^(?:System|Mono|UnityEngine|Unity|TMPro|Il2Cpp)_\w+_(?:o|array)$")
_BITS = {
    "char": 8, "_BYTE": 8, "short": 16, "_WORD": 16, "int": 32, "unsigned": 32, "_DWORD": 32,
    "long long": 64, "_QWORD": 64,
}
_WIDE_INT = re.compile(r"^(?:unsigned )?(?:__int64|_QWORD|u64|s64|intptr_t|uintptr_t|size_t)$")
_KEYWORDS = frozenset({"if", "while", "for", "switch", "return", "sizeof", "else", "case"})


def _norm(t: str) -> str:
    """Comparable form of a type: no qualifiers or spaces, `_o` suffix dropped."""
    t = re.sub(r"\b(?:const|struct|volatile)\b", "", t)
    stars = t.count("*")
    base = re.sub(r"\s+", " ", t.replace("*", " ")).strip()
    base = {
        "unsigned __int8": "_BYTE", "unsigned __int16": "_WORD", "unsigned __int32": "_DWORD",
        "unsigned __int64": "_QWORD", "__int8": "char", "__int16": "short", "__int32": "int",
        "__int64": "long long", "unsigned int": "unsigned", "uint8_t": "_BYTE",
        "uint16_t": "_WORD", "uint32_t": "_DWORD", "uint64_t": "_QWORD", "int32_t": "int",
        "int64_t": "long long", "int16_t": "short", "int8_t": "char", "u8": "_BYTE",
        "u16": "_WORD", "u32": "_DWORD", "u64": "_QWORD", "s8": "char", "s16": "short",
        "s32": "int", "s64": "long long",
    }.get(base, base)
    if base.endswith("_o"):
        base = base[:-2]
    return base + "*" * stars


def _match_paren(b: str, i: int) -> int:
    depth = 0
    for j in range(i, len(b)):
        if b[j] == "(":
            depth += 1
        elif b[j] == ")":
            depth -= 1
            if depth == 0:
                return j
    return -1


_TOKEN = re.compile(r"\w+(?:::\w+)*(?:\.\d+)?")
_MEMBER = re.compile(r"(?:->|\.)[A-Za-z_]\w*")


def _skip_operand(b: str, i: int) -> int:
    """End of the unary expression starting at `i` (its postfix chain included)."""
    n = len(b)
    while i < n and b[i] in "*&-!~+ ":
        i += 1
    if i < n and b[i] == "(":
        close = _match_paren(b, i)
        if close < 0:
            return -1
        inner = _CAST.match(b, i)
        if inner and inner.end() == close + 1:
            return _skip_operand(b, close + 1)
        i = close + 1
    elif m := _TOKEN.match(b, i):
        i = m.end()
    else:
        return -1
    while i < n:
        if b[i] == "[" or (b[i] == "(" and b[i - 1] not in " ,"):
            close = _close_bracket(b, i)
            if close < 0:
                return -1
            i = close + 1
        elif m := _MEMBER.match(b, i):
            i = m.end()
        else:
            break
    return i


def _close_bracket(b: str, i: int) -> int:
    depth = 0
    for j in range(i, len(b)):
        if b[j] in "([":
            depth += 1
        elif b[j] in ")]":
            depth -= 1
            if depth == 0:
                return j
    return -1


def declared_types(b: str, params: list[tuple[str, str]] | None = None) -> dict[str, str]:
    """Local and parameter name -> normalised declared type."""
    out: dict[str, str] = {}
    for t, name in params or []:
        if name:
            out[name] = _norm(t)
    for m in _DECL.finditer(b):
        out[m.group(3)] = _norm(m.group(1) + m.group(2))
    return out


def _is_generic(t: str) -> bool:
    """A cast target that carries no type information of its own (raw integers, void, char)."""
    base = re.sub(r"\b(?:const|struct|volatile)\b|\*", "", t).strip()
    return bool(
        _PRIM_TYPE.match(base) or _GENERIC_POINTEE.match(base) or _RUNTIME_TYPE.match(base)
    )


def _context(b: str, start: int, end: int) -> str:
    """`arg`, `assign` (`=`/return), `deref` or `expr` for a cast spanning b[start:end]."""
    j = start - 1
    while j >= 0 and b[j] in " \t\n":
        j -= 1
    left = b[j] if j >= 0 else ""
    k = end
    while k < len(b) and b[k] in " \t\n":
        k += 1
    right = b[k] if k < len(b) else ""
    if left == "*" and (j == 0 or not re.match(r"[\w)\]]", b[j - 1].strip() or " ")):
        return "deref"
    if left == "&":
        return "expr"
    if left == "=" and j > 0 and b[j - 1] in "=!":
        return "cmp"
    if left == "=" and (j == 0 or b[j - 1] not in "=!<>"):
        return "assign" if right in ";," else "expr"
    if b[max(0, j - 5) : j + 1].endswith("return") and right == ";":
        return "assign"
    if (right == "=" and b[k : k + 2] == "==") or (right == "!" and b[k : k + 2] == "!="):
        return "cmp"
    if right not in ",);":
        return "expr"
    if left == ",":
        return "arg"
    if left == "(" and j > 0 and (b[j - 1].isalnum() or b[j - 1] == "_"):
        word = re.search(r"(\w+)$", b[max(0, j - 12) : j])
        return "arg" if word and word.group(1) not in _KEYWORDS else "expr"
    return "expr"


def _assign_target(b: str, start: int) -> str | None:
    m = re.search(r"(?m)^[ \t]*(\w+) = $", b[max(0, start - 80) : start])
    return m.group(1) if m else None


def _keep(
    b: str, m: re.Match[str], start: int, end: int, decl: dict[str, str]
) -> bool:
    t = m.group(1)
    operand = b[m.end() : end].strip()
    nt = _norm(t)
    if re.fullmatch(r"\w+", operand) and decl.get(operand) == nt:
        return False
    ctx = _context(b, start, end)
    if "__fastcall" in t:
        return False
    if ctx == "deref" or ctx == "expr":
        return True
    pointer = "*" in t
    if ctx == "assign":
        target = _assign_target(b, start)
        if target and decl.get(target) == nt:
            return False
    if not (pointer or _WIDE_INT.match(t)):
        if ctx not in ("assign", "arg"):
            return True
        if not _PRIM_TYPE.match(t):
            return False
        width = _BITS.get(nt)
        return width is None or width != _BITS.get(decl.get(operand, ""))
    if ctx == "cmp":
        return not pointer
    return ctx == "expr" or (ctx == "assign" and not _is_generic(t))


def strip_casts(b: str, decl: dict[str, str]) -> str:
    """Drop casts that restate the operand's declared type, a callee or assignment target
    type, or a call through a function-pointer cast. Width-changing casts stay."""
    cuts: list[tuple[int, int]] = []
    chain_start, chain_end = -1, -1
    for m in _CAST.finditer(b):
        end = _skip_operand(b, m.end())
        if m.start() != chain_end:
            chain_start = m.start()
        chain_end = m.end()
        if end >= 0 and not _keep(b, m, chain_start, end, decl):
            cuts.append((m.start(), m.end()))
    out: list[str] = []
    pos = 0
    for start, stop in cuts:
        out.append(b[pos:start])
        pos = stop
    out.append(b[pos:])
    return "".join(out)


_VECTOR_FIELDS = {"Vector2": "xy", "Vector3": "xyz", "Vector4": "xyzw"}
_ACCESSOR = re.compile(r"\bUnityEngine_(Vector[234]|Matrix4x4)__(get|set)_Item_impl\(")
_SIMPLE_PLACE = re.compile(r"^&?(?:\(\*\w+\)|\w+)(?:(?:->|\.)[A-Za-z_]\w*|\[[^\[\]]*\])*$")
_TRAILING_COMPONENT = re.compile(r"\.(?:fields\.)?[xyzw]$")
_ARG_CAST = re.compile(r"^\(UnityEngine_\w+_o \*\)")


def _place(this: str) -> str | None:
    """`&v` -> `v.`, `p` -> `p->`; None if the argument is not a plain place."""
    this = _ARG_CAST.sub("", this.strip())
    if _TRAILING_COMPONENT.search(this) or not _SIMPLE_PLACE.match(this):
        return None
    if this.startswith("&"):
        return this[1:] + "."
    return this + "->"


def fold_accessors(b: str) -> str:
    """`Vector4__get_Item_impl(&v, 1)` -> `v.y`; a set statement becomes an assignment.
    Matrix4x4 uses `m{row}{col}`. Variable indexes stay calls."""
    for m in reversed(list(_ACCESSOR.finditer(b))):
        close = _match_paren(b, m.end() - 1)
        if close < 0:
            continue
        args = _split(b[m.end() : close])
        kind, op = m.group(1), m.group(2)
        n_idx = 2 if kind == "Matrix4x4" else 1
        if len(args) != 1 + n_idx + (op == "set"):
            continue
        place = _place(args[0])
        idx = args[1 : 1 + n_idx]
        if place is None or not all(re.fullmatch(r"\d", i) for i in idx):
            continue
        nums = [int(i) for i in idx]
        if kind == "Matrix4x4":
            if max(nums) > 3:
                continue
            field = f"m{nums[0]}{nums[1]}"
        elif nums[0] < len(_VECTOR_FIELDS[kind]):
            field = _VECTOR_FIELDS[kind][nums[0]]
        else:
            continue
        ref = place + field
        if op == "get":
            b = b[: m.start()] + ref + b[close + 1 :]
            continue
        head = b[: m.start()]
        if head[head.rfind("\n") + 1 :].strip() == "" and b[close + 1 :].startswith(";"):
            b = f"{head}{ref} = {args[-1]}{b[close + 1 :]}"
    return b


def _split(inner: str) -> list[str]:
    out: list[str] = []
    depth, start = 0, 0
    for i, ch in enumerate(inner):
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif ch == "," and depth == 0:
            out.append(inner[start:i])
            start = i + 1
    out.append(inner[start:])
    return [a.strip() for a in out] if inner.strip() else []


_LL_LITERAL = re.compile(r"\b(0x[0-9A-Fa-f]+|\d+)(u?)LL\b")


def shorten_int_literals(b: str) -> str:
    """`40LL` -> `40`, `0x10uLL` -> `0x10u` when the value fits 32 bits."""

    def sub(m: re.Match[str]) -> str:
        value = int(m.group(1), 0)
        if value < (1 << (32 if m.group(2) else 31)):
            return m.group(1) + m.group(2)
        return m.group(0)

    return _LL_LITERAL.sub(sub, b)


_EXPONENT = re.compile(r"(?<![\w.])(-?\d+(?:\.\d+)?)e([+-]\d+)\b")


def expand_exponents(b: str) -> str:
    """`2e+01` -> `20.0`, `1.5e-05` -> `0.000015`; the float hook prints round-trip digits."""

    def sub(m: re.Match[str]) -> str:
        exp = int(m.group(2))
        if not -6 <= exp <= 15:
            return m.group(0)
        text = format(Decimal(m.group(0)), "f")
        return text if "." in text else text + ".0"

    return _EXPONENT.sub(sub, b)


def join_wrapped(b: str) -> str:
    """Join a statement Hex-Rays wrapped over several lines (unclosed parenthesis)."""
    out: list[str] = []
    parts: list[str] = []
    for line in b.split("\n"):
        parts.append(line if not parts else line.strip())
        text = "".join(p if p.endswith("(") or i == len(parts) - 1 else p + " "
                       for i, p in enumerate(parts))
        if _paren_depth(text) <= 0 or len(parts) > 30:
            if _paren_depth(text) > 0:
                out.extend(parts)
            else:
                out.append(text)
            parts = []
    out.extend(parts)
    return "\n".join(out)


def _paren_depth(line: str) -> int:
    depth, quote = 0, False
    for i, ch in enumerate(line):
        if quote:
            quote = not (ch == '"' and line[i - 1] != "\\")
        elif ch == '"':
            quote = True
        elif ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif ch == "/" and line[i : i + 2] == "//":
            break
    return depth


def drop_all_casts(line: str) -> str:
    """Remove every cast from one line, for pattern matching that ignores types."""
    return shorten_int_literals(_CAST.sub("", line))


def iter_statements(lines: Iterable[str]) -> Iterator[str]:
    """Source lines with wrapped statements joined and casts removed, for crosscheck scripts."""
    parts: list[str] = []
    for raw in lines:
        parts.append(raw.rstrip("\n") if not parts else raw.strip())
        text = "".join(p if p.endswith("(") else p + " " for p in parts[:-1]) + parts[-1]
        if _paren_depth(text) > 0 and len(parts) <= 30:
            continue
        yield drop_all_casts(text) + "\n"
        parts = []
