"""Carve small real snippets of the Il2CppDumper output into test fixtures."""
import json, re, sys
from pathlib import Path
inp = Path(sys.argv[1]); out = Path(sys.argv[2])
CS_TYPES = {  # (namespace, decl name) -> max body lines kept
    ("Project.Kernel", "dds3KernelCore"): 40, ("Project.Kernel", "dds3ProcessID_t"): 99,
    ("Project.Kernel", "DDS3_PRIORITY"): 8, ("Project.Kernel", "dds3ProcessFunc_t"): 99,
    ("Project.Kernel", "shutdownfuncDelegate"): 99,
    ("Project.libsdf", "sdfGrPacketHeader_t"): 99, ("Project.libsdf", "sdf3DViewportPacket_t"): 99,
    ("Project", "fld"): 12, ("", "fld.Save_t"): 99, ("Project", "SKIL176"): 99,
    ("Project", "LoadMark"): 99,
}
lines = (inp / "dump.cs").read_text(encoding="utf-8").split("\n")
cs_out = []
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
            end = lines.index("}", j)
            body = lines[j + 2 : end]
            keep = body[: CS_TYPES[key]]
            if len(keep) < len(body):  # cut at a blank line so no RVA comment dangles
                while keep and keep[-1].strip():
                    keep.pop()
            cs_out += [lines[i], lines[j], "{"] + keep + ["}", ""]
            i = end
    i += 1
(out / "dump_snippet.cs").write_text("\n".join(cs_out), encoding="utf-8")
want = set()
for ns, name in CS_TYPES:
    c = re.sub(r"\W", "_", f"{ns or 'Project'}.{name}")
    want |= {f"{c}_Fields", f"{c}_StaticFields"}
h = (inp / "il2cpp.h").read_text(encoding="utf-8").split("\n")
h_out = []
i = 0
while i < len(h):
    m = re.match(r"^struct (\w+)(?: : \w+)? \{$", h[i])
    if m and m.group(1) in want:
        end = h.index("};", i)
        body = h[i + 1 : end][:14]
        h_out += [h[i]] + body + ["};"]
        i = end
    i += 1
(out / "il2cpp_snippet.h").write_text("\n".join(h_out) + "\n", encoding="utf-8")
script = json.loads((inp / "script.json").read_text(encoding="utf-8"))
classes = {(f"{ns}.{n}" if ns else f"Project.{n}") for ns, n in CS_TYPES}
meths = [m for m in script["ScriptMethod"] if m["Name"].split("$$")[0] in classes]
kc = [m for m in meths if "dds3KernelCore$$" in m["Name"]][:12]
meths = [m for m in meths if "dds3KernelCore$$" not in m["Name"] and "fld$$" not in m["Name"]] + kc
meths += [m for m in script["ScriptMethod"] if m["Name"].startswith("Project.fld$$")][:4]
for m in meths:
    m.pop("TypeSignature", None)
strings = script["ScriptString"][:3]
(out / "script_snippet.json").write_text(
    json.dumps({"ScriptMethod": meths, "ScriptString": strings}, indent=1), encoding="utf-8")
print(len(cs_out), len(h_out), len(meths))
