"""Name-based rules of the C code base the port kept: file families, macros and port classes."""

from __future__ import annotations

import re
from collections.abc import Iterable

from raidou import dumpcs

_CAPS_PART = re.compile(r"^(?:[A-Z0-9]{2}|[A-Z0-9]$)")


def is_caps(name: str) -> bool:
    """An ALLCAPS class name (``SBTL``, ``SDF_VU0``): a letter and no lowercase."""
    return bool(re.search(r"[A-Z]", name)) and not re.search(r"[a-z]", name)


def is_macro_name(name: str) -> bool:
    """A method named like a C macro: ALLCAPS, or ALLCAPS words with at most two lowercase
    letters (``GET_PER_SRCtoDES``), but not ``BS_MUNAKA_Init``."""
    if not re.search(r"[A-Z]", name) or len(re.findall(r"[a-z]", name)) > 2:
        return False
    return all(_CAPS_PART.match(p) for p in name.split("_") if p)


def family_key(name: str) -> str:
    """``sBtl``, ``SBTL``, ``SBTL_`` and ``sbtl`` share the key ``sbtl``."""
    return name.lower().rstrip("_") or name.lower()


# --- camel-case words -----------------------------------------------------------

_WORD = re.compile(r"_*(?:[a-z0-9]+|[A-Z][a-z0-9]*)|_+$")


def camel_prefixes(name: str) -> list[tuple[str, str | None]]:
    """Each run of leading camel-case words of ``name`` with the word after it:
    ``dds3KernelDraw`` -> ``("dds3", "Kernel"), ("dds3Kernel", "Draw"), ("dds3KernelDraw", None)``.
    """
    words = _WORD.findall(name)
    out: list[tuple[str, str | None]] = []
    acc = ""
    for i, w in enumerate(words):
        acc += w
        out.append((acc, words[i + 1] if i + 1 < len(words) else None))
    return out


def starts_with_word(text: str, word: str) -> bool:
    """``text`` begins with the whole camel-case word ``word`` (``DrawFade`` with ``Draw``,
    not ``Drawing``)."""
    return text.startswith(word) and (
        len(text) == len(word) or not text[len(word)].islower()
    )


def camel_split_ok(prefix: str, method: str) -> bool:
    """``prefix|method`` splits on a camel-case boundary: the prefix starts with a letter and
    ends in a lowercase letter or digit, the method starts uppercase."""
    return bool(re.match(r"^[A-Za-z][A-Za-z0-9_]*[a-z0-9]$", prefix)) and method[:1].isupper()


def prefix_fits(cls: str, prefix: str, method: str, *, strict: bool = True) -> bool:
    """``prefix + method`` could be what the port shortened to ``method`` in class ``cls``.

    The port stripped the longest run of leading camel-case words shared by the function and
    the class, so ``prefix`` is such a run of ``cls`` and (``strict``) ``method`` does not
    begin with the class word after it.
    """
    if not camel_split_ok(prefix, method):
        return False
    for p, nxt in camel_prefixes(cls):
        if p == prefix:
            return not strict or nxt is None or not starts_with_word(method, nxt)
    return False


def system_prefix(cls: str, systems: Iterable[str]) -> str | None:
    """The C system prefix of module ``cls`` when SMT3 shows none: the longest proper run of
    leading camel words that names another game module or family (``sBtlDraw`` -> ``sBtl``),
    else the leading lowercase and digit run of two or more characters (``dds3``)."""
    known = {s.lower() for s in systems}
    runs = [p for p, nxt in camel_prefixes(cls) if nxt is not None and len(p) >= 2]
    for p in reversed(runs):
        if p.lower() in known and camel_split_ok(p, "X"):
            return p
    m = re.match(r"^[a-z0-9]+", cls)
    return m.group(0) if m and len(m.group(0)) >= 2 else None


# --- port classes -----------------------------------------------------------------

# Base classes that are not C# runtime types a C struct could have come from.
_PLAIN_BASES = frozenset({"object", "Object", "ValueType", "Enum", "MulticastDelegate"})


def instance_methods(td: dumpcs.TypeDef) -> list[dumpcs.Method]:
    """Methods with a ``this`` receiver, other than constructors."""
    return [m for m in td.methods if not m.static and not m.name.startswith(".")]


def _strip_generic(name: str) -> str:
    return re.sub(r"<.*", "", name.removeprefix("global::"))


class BaseIndex:
    """Looks up the declaration of a base class named in ``dump.cs``."""

    def __init__(self, types: Iterable[dumpcs.TypeDef]) -> None:
        self.by_name: dict[str, list[dumpcs.TypeDef]] = {}
        for td in types:
            short = _strip_generic(td.name)
            self.by_name.setdefault(short, []).append(td)
            if td.namespace:
                self.by_name.setdefault(f"{td.namespace}.{short}", []).append(td)

    def lookup(self, base: str) -> dumpcs.TypeDef | None:
        cands = self.by_name.get(_strip_generic(base), [])
        classes = [c for c in cands if c.kind != "interface"]
        return (classes or cands or [None])[0]


def is_game_namespace(ns: str) -> bool:
    return ns == "Project" or ns.startswith("Project.") or ns == ""


def runtime_derived(td: dumpcs.TypeDef, bases: BaseIndex) -> bool:
    """``td`` derives, through any chain of game classes, from a runtime class such as
    ``MonoBehaviour`` or ``ScriptableObject``."""
    seen: set[int] = set()
    cur = td
    while cur.base and id(cur) not in seen:
        seen.add(id(cur))
        name = _strip_generic(cur.base)
        if name in _PLAIN_BASES or name.endswith(".MulticastDelegate"):
            return False
        nxt = bases.lookup(name)
        if nxt is None:
            return False
        if nxt.kind == "interface":
            return False
        if not is_game_namespace(nxt.namespace):
            return True
        cur = nxt
    return False


def inherits_instance_methods(td: dumpcs.TypeDef, bases: BaseIndex) -> bool:
    """``td`` or a game base class of it has instance methods."""
    seen: set[int] = set()
    cur: dumpcs.TypeDef | None = td
    while cur is not None and id(cur) not in seen:
        seen.add(id(cur))
        if instance_methods(cur):
            return True
        if not cur.base:
            return False
        cur = bases.lookup(cur.base)
        if cur is not None and (cur.kind == "interface" or not is_game_namespace(cur.namespace)):
            return False
    return False
