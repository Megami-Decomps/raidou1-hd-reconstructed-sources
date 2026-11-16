"""Carve the fixtures of the family, macro, linkage, prefix and port-class rules.

    python3 carve_family_fixtures.py inputs raidou/tests/fixtures/families
"""
import json
import re
import sys
from pathlib import Path

# (namespace, decl name) -> member names kept (None: all). Members are fields and methods.
CS_TYPES: dict[tuple[str, str], set[str] | None] = {
    ("Project", "SBTL"): {"HAVESKILL_NUM", "MTION_DEFSPD", "GETITEMPARA_LOW", "PRINTF"},
    ("Project", "SBTL_"): None,
    ("Project", "SBTL_ACTAIFLG"): None,
    ("Project", "sbtl"): {"wk", "main_data", "frame_cnt"},
    ("Project", "sBtl"): {"dbg_encount_bk", "battleMap", "ret_field_scene", "ROULETTE_TOP",
                          "DEG_RAD", "LimitRange", "Init", "Start", "Exit2Set", "Exit2"},
    ("Project", "SBATTLE_WORK"): {"step"},
    ("Project", "SBTLMAIN_DATA"): {"pos", "encountno", "ClassCopy", "Clone"},
    ("Project", "EventBg"): None,
    ("Project", "NEGO2"): None,
    ("Project", "NEGO2_"): {"value__", "REQ_MONEY"},
    ("Project.Kernel", "dds3KernelDraw"): {"Ot", "QuakeFlag", "fadetype", "finishBrightness",
                                           "InitDrawEnv", "SetFinish", "DrawEnvPush", "SetQuake",
                                           "FadeTypeSet"},
    ("", "dds3KernelDraw.DDS3_DRAW_BISTA"): None,
    ("", "dds3KernelDraw.FIL_t"): None,
    ("Project.Kernel", "DDS3_FADETYPE"): None,
    ("UnityEngine", "MonoBehaviour"): set(),
}
_NAME = re.compile(r"\b(\w+)(?: = [^;]*)?;(?: // 0x[0-9A-F]+)?$|\b([^\s(]+)\(")


def _member_name(line: str) -> str | None:
    m = _NAME.search(line)
    return (m.group(1) or m.group(2)) if m else None


def _full(ns: str, name: str) -> str:
    """The linker class name; nested types here all sit in Project.Kernel."""
    return f"{ns or 'Project.Kernel'}.{name}"


def carve_cs(lines: list[str]) -> list[str]:
    out: list[str] = []
    i = 0
    while i < len(lines):
        m = re.match(r"^// Namespace: (.*)$", lines[i])
        if m and i + 1 < len(lines):
            j = i + 1
            while lines[j].startswith("["):
                j += 1
            d = re.search(r"(?:class|struct|enum|interface) (\S+)", lines[j])
            key = (m.group(1).strip(), d.group(1) if d else "")
            if key in CS_TYPES:
                keep = CS_TYPES[key]
                end = lines.index("}", j)
                body = lines[j + 2 : end]
                kept: list[str] = []
                pending: list[str] = []  # attribute and RVA lines before a method
                for ln in body:
                    s = ln.strip()
                    if s.startswith(("// RVA", "[")):
                        pending.append(ln)
                        continue
                    if s.startswith("// ") or not s:
                        kept += [ln] if s.startswith("// ") else []
                        pending = []
                        continue
                    name = _member_name(s)
                    if keep is None or name in keep or name in (".ctor", ".cctor"):
                        kept += pending + [ln]
                    pending = []
                out += [lines[i], lines[j], "{"] + kept + ["}", ""]
                i = end
        i += 1
    return out


def carve_h(h: list[str]) -> list[str]:
    want: dict[str, set[str] | None] = {}
    for (ns, name), keep in CS_TYPES.items():
        c = re.sub(r"\W", "_", _full(ns, name))
        for suf in ("_Fields", "_StaticFields"):
            want[c + suf] = keep
    out: list[str] = []
    i = 0
    while i < len(h):
        m = re.match(r"^struct (\w+)(?: : \w+)? \{$", h[i])
        if m and m.group(1) in want:
            keep = want[m.group(1)]
            end = h.index("};", i)
            body = [ln for ln in h[i + 1 : end]
                    if keep is None or (n := re.search(r"(\w+);$", ln)) and n.group(1) in keep]
            out += [h[i]] + body + ["};"]
            i = end
        i += 1
    return out


def main() -> None:
    inp, out = Path(sys.argv[1]), Path(sys.argv[2])
    out.mkdir(parents=True, exist_ok=True)
    cs = carve_cs((inp / "dump.cs").read_text(encoding="utf-8").split("\n"))
    (out / "dump_snippet.cs").write_text("\n".join(cs), encoding="utf-8")
    h = carve_h((inp / "il2cpp.h").read_text(encoding="utf-8").split("\n"))
    (out / "il2cpp_snippet.h").write_text("\n".join(h) + "\n", encoding="utf-8")
    script = json.loads((inp / "script.json").read_text(encoding="utf-8"))
    classes = {_full(ns, name): keep for (ns, name), keep in CS_TYPES.items()}
    meths = []
    for m in script["ScriptMethod"]:
        cls, _, method = m["Name"].partition("$$")
        if cls in classes and (classes[cls] is None or method in (classes[cls] or set())):
            m.pop("TypeSignature", None)
            meths.append(m)
    (out / "script_snippet.json").write_text(
        json.dumps({"ScriptMethod": meths, "ScriptString": []}, indent=1), encoding="utf-8")
    print(len(cs), len(h), len(meths))


if __name__ == "__main__":
    main()
