"""Index the SMT3 reconstruction: which header defines each type and macro, and the function
names in each module.

    python -m raidou.smt3index ~/projects/smt3hd-reconstructed-sources > smt3_index.json
"""

from __future__ import annotations

import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path

_STRUCT = re.compile(r"^struct (\w+) \{$")
_ENUM_END = re.compile(r"^\} (\w+);$")
_DEFINE = re.compile(r"^#define (\w+)")
_SYMBOL = re.compile(r"^0x[0-9a-f]+  (\w+)  (\S+\.c)")


@dataclass(frozen=True)
class Smt3Index:
    types: dict[str, str]  # struct/enum name -> header
    macros: dict[str, str]  # #define name -> header
    symbols: dict[str, list[str]]  # module .c -> function names

    def header_of_type(self, name: str) -> str | None:
        return self.types.get(name)

    def header_of_macros(self, names: list[str]) -> str | None:
        for n in names:
            if (h := self.macros.get(n)) is not None:
                return h
        return None


def scan_header(text: str) -> tuple[list[str], list[str]]:
    """``(types, macros)`` defined in one generated SMT3 header."""
    types: list[str] = []
    macros: list[str] = []
    in_enum = False
    for line in text.split("\n"):
        if line == "typedef enum {":
            in_enum = True
        elif in_enum and (m := _ENUM_END.match(line)):
            types.append(m.group(1))
            in_enum = False
        elif m := _STRUCT.match(line):
            types.append(m.group(1))
        elif m := _DEFINE.match(line):
            macros.append(m.group(1))
    return types, macros


def build(repo: Path) -> Smt3Index:
    types: dict[str, str] = {}
    macros: dict[str, str] = {}
    for h in sorted((repo / "include").glob("*.h")):
        if h.name == "types.h":  # the shared math typedefs, provided here too
            continue
        ts, ms = scan_header(h.read_text(encoding="utf-8"))
        for t in ts:
            types.setdefault(t, h.name)
        for m in ms:
            macros.setdefault(m, h.name)
    symbols: dict[str, list[str]] = {}
    sym_path = repo / "symbols.txt"
    if sym_path.is_file():
        for line in sym_path.read_text(encoding="utf-8").split("\n"):
            if m := _SYMBOL.match(line):
                symbols.setdefault(m.group(2), []).append(m.group(1))
    return Smt3Index(types, macros, symbols)


def load(path: Path) -> Smt3Index:
    """Read a JSON snapshot, or index a checkout of the SMT3 repo directly."""
    if path.is_dir():
        return build(path)
    raw = json.loads(path.read_text(encoding="utf-8"))
    return Smt3Index(raw["types"], raw["macros"], raw["symbols"])


def main() -> int:
    idx = build(Path(sys.argv[1]))
    json.dump(
        {"types": idx.types, "macros": idx.macros, "symbols": idx.symbols},
        sys.stdout, indent=0, sort_keys=True,
    )
    print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
