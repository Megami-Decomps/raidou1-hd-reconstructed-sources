"""Parse Il2CppDumper's ``dump.cs``: type kinds, namespaces, fields, constants and methods."""

from __future__ import annotations

import re
from collections.abc import Iterable
from dataclasses import dataclass, field

_NAMESPACE = re.compile(r"^// Namespace: (.*)$")
_TYPE = re.compile(
    r"^(?:(?:public|private|protected|internal|static|sealed|abstract|readonly|ref|unsafe)\s+)*"
    r"(class|struct|enum|interface)\s+((?:[^\s<]|<[^>]*>)+)"
    r"(?:\s*:\s*([^/]+?))?\s*// TypeDefIndex: (\d+)$"
)
_MODIFIERS = frozenset(
    {"public", "private", "protected", "internal", "static", "readonly", "const", "volatile",
     "new", "override", "virtual", "abstract", "sealed", "extern", "unsafe", "fixed"}
)
_FIELD = re.compile(r"^\t(.+?) (\w+)(?: = (.*))?;(?: // 0x[0-9A-Fa-f]+)?$")
_METHOD = re.compile(r"^\t(.+?) ([^\s(]+)\((.*)\)(?: \{ \})?;?$")
_TOP_COMMA = re.compile(r",(?![^<]*>)")  # a comma outside generic brackets
_RVA = re.compile(r"^\t// RVA: (0x[0-9A-Fa-f]+|-1)")


@dataclass
class Field:
    name: str
    type: str  # C# type as written, e.g. "byte[]", "fld.Save_t"
    static: bool
    public: bool = True


@dataclass
class Method:
    name: str
    static: bool
    public: bool
    rva: int | None
    params: list[tuple[str, str]]  # (C# type, name); `ref`/`out` kept in the type
    ret: str = ""  # C# return type


@dataclass
class TypeDef:
    namespace: str  # "" for a nested type (dump.cs leaves it blank)
    name: str  # dotted for nesting: "fld.Save_t"
    kind: str  # class, struct, enum, interface
    base: str | None
    index: int
    public: bool = True
    fields: list[Field] = field(default_factory=list[Field])
    consts: list[tuple[str, str, str]] = field(default_factory=list[tuple[str, str, str]])
    methods: list[Method] = field(default_factory=list[Method])


def _split_params(text: str) -> list[tuple[str, str]]:
    """Split a C# parameter list on top-level commas into ``(type, name)`` pairs."""
    out: list[tuple[str, str]] = []
    depth, cur = 0, ""
    for ch in text + ",":
        if ch in "<[(":
            depth += 1
        elif ch in ">])":
            depth -= 1
        if ch == "," and depth == 0:
            p = cur.strip()
            cur = ""
            if not p:
                continue
            p = p.split(" = ", 1)[0]  # default value
            ptype, _, pname = p.rpartition(" ")
            out.append((ptype, pname))
        else:
            cur += ch
    return out


def _split_mods(decl: str) -> tuple[set[str], str]:
    words = decl.split(" ")
    mods: set[str] = set()
    while words and words[0] in _MODIFIERS:
        mods.add(words.pop(0))
    return mods, " ".join(words)


def parse(lines: Iterable[str]) -> list[TypeDef]:
    """Every type definition in ``dump.cs``, in file order."""
    types: list[TypeDef] = []
    ns = ""
    cur: TypeDef | None = None
    rva: int | None = None
    section = ""
    for raw in lines:
        line = raw.rstrip("\r\n")
        if cur is None:
            if m := _NAMESPACE.match(line):
                ns = m.group(1).strip()
            elif m := _TYPE.match(line):
                base = _TOP_COMMA.split(m.group(3))[0].strip() if m.group(3) else None
                public = line.startswith("public ")
                cur = TypeDef(ns, m.group(2), m.group(1), base, int(m.group(4)), public)
                section = ""
            continue
        if line == "}":
            types.append(cur)
            cur = None
            continue
        if line.startswith("\t// "):
            if m := _RVA.match(line):
                rva = None if m.group(1) == "-1" else int(m.group(1), 16)
            elif line.strip() in ("// Fields", "// Properties", "// Methods"):
                section = line.strip()[3:]
            continue
        if not line.startswith("\t") or line.startswith("\t["):
            continue
        if section == "Fields":
            fm = _FIELD.match(line)
            if fm is None:
                continue
            mods, ftype = _split_mods(fm.group(1))
            if "const" in mods and fm.group(3) is not None:
                cur.consts.append((fm.group(2), ftype, fm.group(3)))
            elif ftype:
                cur.fields.append(Field(fm.group(2), ftype, "static" in mods, "public" in mods))
        elif section == "Methods" and (mm := _METHOD.match(line)):
            mods, ret = _split_mods(mm.group(1))
            cur.methods.append(
                Method(
                    mm.group(2), "static" in mods, "public" in mods, rva,
                    _split_params(mm.group(3)), ret,
                )
            )
            rva = None
    return types
