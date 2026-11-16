"""File families, macros, linkage, prefixes and port classes over the family fixtures
(``sbtl``/``SBTL``/``SBTL_``/``sBtl``, ``dds3KernelDraw``, ``EventBg : MonoBehaviour``)."""
# pyright: reportPrivateUsage=false

import json
import shutil
from pathlib import Path

from raidou import dumpcs, families, raidoudump
from raidou.raidoudump import Function, TypeInfo
from raidou.smt3index import Smt3Index

FIXTURES = Path(__file__).parent / "fixtures" / "families"
SMT3 = Smt3Index({"DDS3_FADETYPE": "kernel.h"}, {}, {"dds3KernelDraw.c": ["dds3InitDrawEnv"]})
PS2 = frozenset({"dds3SetQuake"})


def _types_cs() -> list[dumpcs.TypeDef]:
    with (FIXTURES / "dump_snippet.cs").open(encoding="utf-8") as fh:
        return dumpcs.parse(fh)


def _build() -> raidoudump.Build:
    with (FIXTURES / "il2cpp_snippet.h").open(encoding="utf-8") as fh:
        blocks = raidoudump.parse_blocks(fh)
    script = json.loads((FIXTURES / "script_snippet.json").read_text(encoding="utf-8"))
    b = raidoudump.build(blocks, _types_cs(), script["ScriptMethod"], SMT3)
    raidoudump.restore_prefixes(b.funcs, SMT3, PS2, b.fams.systems())
    raidoudump.name_functions(b.funcs)
    return b


def _by_method(b: raidoudump.Build) -> dict[str, Function]:
    return {f.linker.split(".")[-1]: f for f in b.funcs}


# --- name rules -------------------------------------------------------------------


def test_caps_and_macro_names() -> None:
    assert families.is_caps("SBTL_") and families.is_caps("SDF_VU0")
    assert not families.is_caps("sBtl") and not families.is_caps("_")
    for name in ("DEG_RAD", "GET_PER_SRCtoDES", "GET_360toSIN", "ACTAIFLGMASK", "AI_GET_STEPn"):
        assert families.is_macro_name(name), name
    for name in ("LimitRange", "BS_MUNAKA_Init_Imad", "DLC_ItemInit", "TIPS_ALLProcess", "M_InitScene"):
        assert not families.is_macro_name(name), name


def test_family_key() -> None:
    keys = {families.family_key(n) for n in ("sBtl", "SBTL", "SBTL_", "sbtl")}
    assert keys == {"sbtl"}


def test_camel_prefixes_and_fit() -> None:
    assert families.camel_prefixes("dds3KernelDraw") == [
        ("dds3", "Kernel"), ("dds3Kernel", "Draw"), ("dds3KernelDraw", None)
    ]
    assert families.prefix_fits("dds3KernelDraw", "dds3", "FadeIn")
    assert not families.prefix_fits("dds3KernelDraw", "dds3", "KernelInit")
    assert families.prefix_fits("dds3KernelDraw", "dds3", "Kernels")  # another word
    assert families.prefix_fits("ButtonGuide", "Button", "GuideInit", strict=False)
    assert not families.prefix_fits("ButtonGuide", "Button", "GuideInit")
    assert not families.prefix_fits("sndManager", "SndPtnTest", "Process", strict=False)
    assert not families.prefix_fits("dds3KernelDraw", "dds3", "lower")


def test_system_prefix() -> None:
    systems = {"sbtl", "evt"}
    assert families.system_prefix("sBtlDraw", systems) == "sBtl"
    assert families.system_prefix("evtSky", systems) == "evt"
    assert families.system_prefix("dds3KernelDraw", systems) == "dds3"
    assert families.system_prefix("sBtl", systems) is None  # `s` is too short
    assert families.system_prefix("ButtonGuide", systems) is None


# --- families and macros ------------------------------------------------------------------


def test_family_members_share_header_and_code_file() -> None:
    b = _build()
    fam = b.fams.by_key["sbtl"]
    assert {t.td.name for t in fam.members} == {"SBTL", "SBTL_", "sBtl", "sbtl"}
    assert fam.header == "sbtl.h" and fam.primary is not None and fam.primary.clean == "sBtl"
    hdr = b.files["sbtl.h"]
    assert [n for n, _ in hdr.defines] == ["SBTL"]  # ALLCAPS constants
    assert [n for n, _ in hdr.enums] == ["SBTL_ACTAIFLG"]  # only ACTAIFLGMASK uses it
    # sbtl has statics only: defined in sBtl.c, declared in sbtl.h
    assert "u32 frame_cnt;" in hdr.externs
    assert ("u32 frame_cnt;", True) in dict(b.files["sBtl.c"].statics)["sbtl"]
    assert "sbtl.c" not in b.files or b.files["sbtl.c"].empty()


def test_macros() -> None:
    b = _build()
    fs = _by_method(b)
    assert (fs["SBTL$$GETITEMPARA_LOW"].file, fs["SBTL$$GETITEMPARA_LOW"].flag) == ("sbtl.h", "M")
    assert fs["SBTL_$$ACTAIFLGMASK"].file == "sbtl.h"
    assert fs["sBtl$$DEG_RAD"].file == "sBtl.c"  # ALLCAPS method of a module
    assert fs["SBTL_$$ACTAIFLGMASK"].ret == "SBTL_ACTAIFLG"  # return enum from dump.cs
    assert all(f.header is None for f in fs.values() if f.macro)
    hdr = raidoudump.render_file("sbtl.h", b.files["sbtl.h"], b)
    assert "// macros\n// 0x18f06d0: s32 GETITEMPARA_LOW(s32 ipara)\n" in hdr
    assert "#define GETITEMPARA_LOW(ipara) (0)" in hdr
    assert "#define PRINTF(p) ((void)0)" in hdr
    assert "GETITEMPARA_LOW(s32" not in hdr.replace("// 0x18f06d0: s32 GETITEMPARA_LOW(s32", "")


def test_macro_from_body() -> None:
    b = _build()
    deg = _by_method(b)["sBtl$$DEG_RAD"]
    enums = frozenset[str]()
    assert raidoudump.render_macro(deg, [], enums, "    return x * 0.017453292;").endswith(
        "#define DEG_RAD(x) (x * 0.017453292)"
    )
    printf = _by_method(b)["SBTL$$PRINTF"]
    assert raidoudump.render_macro(printf, [], enums, "    puts(p);\n    puts(p);").endswith(
        "#define PRINTF(p) do { \\\n    puts(p); \\\n    puts(p); \\\n} while (0)"
    )
    tangled = raidoudump.render_macro(deg, [], enums, "    f32 y = x;\n    return y;")
    assert "static inline f32 DEG_RAD(f32 x) {" in tangled


def test_collision_suffix_kept_when_bare_name_taken() -> None:
    b = _build()
    cleans = {t.clean for t in b.cat.values()}
    assert {"NEGO2", "NEGO2_", "SBTL", "SBTL_"} <= cleans
    assert b.cat["Project_NEGO2_"].file == "nego2.h"  # a family of two enums


def test_collision_suffix_dropped_when_free() -> None:
    td = dumpcs.TypeDef("Project", "goh_", "enum", None, 0)
    cat = {"Project_goh_": TypeInfo("Project_goh_", "", "enum", "", "Project_goh_", td)}
    raidoudump._assign_clean_names(cat)
    assert cat["Project_goh_"].clean == "goh"


# --- linkage and prefixes ---------------------------------------------------------------------


def test_linkage_from_visibility() -> None:
    b = _build()
    c = raidoudump.render_file("sBtl.c", b.files["sBtl.c"], b)
    h = raidoudump.render_file("sbtl.h", b.files["sbtl.h"], b)
    assert '#include "sbtl.h"' in c
    assert "static s32 dbg_encount_bk;" in c and "dbg_encount_bk" not in h
    assert "\nchar *ret_field_scene;" in c and "extern char *ret_field_scene;" in h
    assert "static void Exit2Set(s32 i);" in c and "static void Exit2Set(s32 i) {" in c
    assert "\nvoid Exit2(void) {" in c and "void Exit2(void);" in h
    assert "Exit2Set" not in h


def test_dds3_kernel_draw_prefixes() -> None:
    b = _build()
    names = {f.method: (f.display, f.flag) for f in b.funcs if "dds3KernelDraw$$" in f.linker}
    assert names == {
        "InitDrawEnv": ("dds3InitDrawEnv", "R"),  # SMT3 same module
        "SetQuake": ("dds3SetQuake", "R"),  # PS2 name
        "DrawEnvPush": ("dds3DrawEnvPush", "I"),  # the module's system prefix
        "SetFinish": ("SetFinish", ""),  # private
        "FadeTypeSet": ("FadeTypeSet", ""),  # private
    }
    hdr = raidoudump.render_file("dds3kerneldraw.h", b.files["dds3kerneldraw.h"], b)
    assert "void dds3DrawEnvPush(void);" in hdr and "SetFinish" not in hdr
    assert "#define TOTAL 128" in hdr  # constants of the nested ALLCAPS class DDS3_DRAW_BISTA


# --- port classes ---------------------------------------------------------------------------


def test_port_classes() -> None:
    b = _build()
    assert "Project_EventBg" not in b.cat  # MonoBehaviour
    assert not any("EventBg" in f.linker for f in b.funcs)
    data = b.cat["Project_SBTLMAIN_DATA"]  # has ClassCopy/Clone, but sbtl.main_data uses it
    assert (data.kind, data.port) == ("struct", True)
    assert not any("SBTLMAIN_DATA$$" in f.linker for f in b.funcs)
    assert dict(b.files["sbtl.h"].structs)["SBTLMAIN_DATA"] == [
        "sdfVector4_t pos;", "s32 encountno;"
    ]
    assert "void *battleMap;" in dict(b.files["sBtl.c"].statics)["sBtl"][1]  # dropped type
    assert b.counts["port class dropped"] == 1 and b.counts["port class kept as struct"] == 1
    assert b.counts["port method dropped"] == 4  # EventBg 3, ClassCopy (Clone is C#-only)


def test_mostly_static_class_is_a_module() -> None:
    td = dumpcs.TypeDef("Project", "itf", "class", None, 0)
    td.methods = [dumpcs.Method(f"S{i}", True, True, None, []) for i in range(3)]
    td.methods.append(dumpcs.Method("frInit", False, True, None, []))
    t = TypeInfo("Project_itf", "", "module", "itf", "Project_itf", td)
    cat = {t.cname: t}
    counts = raidoudump.drop_port_classes(cat, {}, [td], [])
    assert "Project_itf" in cat and counts["port class"] == 0


# --- end to end --------------------------------------------------------------------------------


def test_run_families_end_to_end(tmp_path: Path) -> None:
    inputs = tmp_path / "in"
    inputs.mkdir()
    shutil.copy(FIXTURES / "il2cpp_snippet.h", inputs / "il2cpp.h")
    shutil.copy(FIXTURES / "dump_snippet.cs", inputs / "dump.cs")
    shutil.copy(FIXTURES / "script_snippet.json", inputs / "script.json")
    smt3 = tmp_path / "smt3.json"
    smt3.write_text(json.dumps({"types": SMT3.types, "macros": {}, "symbols": SMT3.symbols}))
    ps2 = tmp_path / "ps2_names.txt"
    ps2.write_text("00100000 dds3SetQuake\n00100010 sub_100010\n")
    out = tmp_path / "out"
    counts = raidoudump.run(
        inputs / "il2cpp.h", inputs / "dump.cs", inputs / "script.json", out,
        smt3=smt3, ps2_names=ps2,
    )
    assert counts["function R"] == 2 and counts["function I"] == 1 and counts["function M"] == 4
    assert {p.name for p in (out / "src").iterdir()} == {"sBtl.c", "dds3KernelDraw.c"}
    assert {p.name for p in (out / "include").iterdir()} == {
        "types.h", "kernel.h", "sbtl.h", "nego2.h", "dds3kerneldraw.h"
    }
    symbols = (out / "symbols.txt").read_text()
    assert "0x01ec1700  DEG_RAD  sBtl.c  Project.sBtl$$DEG_RAD  M" in symbols
    assert "dds3DrawEnvPush  dds3KernelDraw.c  Project.Kernel.dds3KernelDraw$$DrawEnvPush  I" in (
        symbols
    )
