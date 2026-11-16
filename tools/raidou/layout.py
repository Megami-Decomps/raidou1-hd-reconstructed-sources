"""Member offsets of the il2cpp.h structs, for naming raw `base + offset` accesses."""

from __future__ import annotations

import re
from collections.abc import Mapping, Sequence
from typing import Protocol

PRIMITIVES = {
    "bool": 1, "char": 1, "int8_t": 1, "uint8_t": 1,
    "int16_t": 2, "uint16_t": 2, "wchar_t": 2, "char16_t": 2, "Il2CppChar": 2,
    "int32_t": 4, "uint32_t": 4, "int": 4, "float": 4,
    "int64_t": 8, "uint64_t": 8, "double": 8,
    "il2cpp_array_size_t": 8, "intptr_t": 8, "uintptr_t": 8, "size_t": 8,
}
POINTER_SIZE = 8
ARRAY_HEADER = 32  # Il2CppObject, bounds and max_length before an array's m_Items

_MEMBER = re.compile(
    r"^(?:const |struct |volatile )*([A-Za-z_]\w*)\s*((?:\*\s*)*)([A-Za-z_]\w*)\s*(?:\[(\d+)\])?;$"
)


class StructDef(Protocol):
    @property
    def base(self) -> str | None: ...
    @property
    def members(self) -> Sequence[str]: ...


class Layout:
    """Offsets and sizes of struct members, resolving bases and nested structs on demand."""

    def __init__(self, structs: Mapping[str, StructDef]) -> None:
        self._structs = structs
        self._sizes: dict[str, tuple[int, int]] = {}
        self._flat: dict[str, list[tuple[int, str, int, str]]] = {}
        self._resolving: set[str] = set()

    def size_align(self, type_name: str) -> tuple[int, int]:
        if (prim := PRIMITIVES.get(type_name)) is not None:
            return (prim, prim)
        if type_name in self._sizes:
            return self._sizes[type_name]
        if type_name not in self._structs or type_name in self._resolving:
            return (POINTER_SIZE, POINTER_SIZE)  # opaque: only ever behind a pointer
        self._resolving.add(type_name)
        _, size, align = self._walk(type_name)
        self._resolving.discard(type_name)
        self._sizes[type_name] = (size, align)
        return (size, align)

    def flat(self, name: str) -> list[tuple[int, str, int, str]]:
        """(offset, member path, size, type) for every member, nested ones after their parent."""
        if name not in self._flat:
            self._flat[name] = self._walk(name)[0] if name in self._structs else []
        return self._flat[name]

    def member_at(self, name: str, offset: int, width: int | None = None) -> str | None:
        """The member starting at `offset`; with `width`, the outermost one of that size."""
        hits = self.members_at(name, offset)
        if width is not None:
            sized = [path for path, size, _ in hits if size == width]
            return sized[0] if sized else None
        return hits[0][0] if hits else None

    def members_at(self, name: str, offset: int) -> list[tuple[str, int, str]]:
        """(path, size, type) of the members starting at `offset`, outermost first. The type
        is the member's declared one (`int32_t`, `System_String_o*`, `int32_t[4]`). In an
        IL2CPP array (`X_array`) the members are the elements, `m_Items[k]`."""
        elem = self._array_element(name)
        if elem is None:
            return [(path, size, t) for off, path, size, t in self.flat(name) if off == offset]
        etype, esize = elem
        k, rest = divmod(offset - ARRAY_HEADER, esize)
        if k < 0:
            return []
        item = f"m_Items[{k}]"
        inner = [] if "*" in etype else self.members_at(etype, rest)
        return [(item, esize, etype)] * (rest == 0) + [(f"{item}.{p}", n, t) for p, n, t in inner]

    def _array_element(self, name: str) -> tuple[str, int] | None:
        """(element type, element size) of an IL2CPP array struct, else None."""
        s = self._structs.get(name) if name.endswith("_array") else None
        m = _MEMBER.match(s.members[-1]) if s is not None and s.members else None
        if m is None or m.group(3) != "m_Items":
            return None
        stars = "*" * m.group(2).count("*")
        size = POINTER_SIZE if stars else self.size_align(m.group(1))[0]
        return f"{m.group(1)}{stars}", size

    def _walk(self, name: str) -> tuple[list[tuple[int, str, int, str]], int, int]:
        s = self._structs[name]
        out: list[tuple[int, str, int, str]] = []
        pos, align = 0, 1
        if s.base and s.base in self._structs and s.base not in self._resolving:
            self._resolving.add(s.base)
            out, pos, align = self._walk(s.base)
            self._resolving.discard(s.base)
        for line in s.members:
            m = _MEMBER.match(line)
            if m is None:
                continue
            type_name, member = m.group(1), m.group(3)
            count = int(m.group(4) or 1)
            size, member_align = (
                (POINTER_SIZE, POINTER_SIZE) if m.group(2).strip() else self.size_align(type_name)
            )
            pos = (pos + member_align - 1) // member_align * member_align
            stars = "*" * m.group(2).count("*")
            array = f"[{count}]" if m.group(4) else ""
            out.append((pos, member, size * count, f"{type_name}{stars}{array}"))
            if not stars and type_name in self._structs:
                for off, path, sub, t in self.flat(type_name):
                    out.append((pos + off, f"{member}.{path}", sub, t))
            pos += size * count
            align = max(align, member_align)
        return out, (pos + align - 1) // align * align, align
