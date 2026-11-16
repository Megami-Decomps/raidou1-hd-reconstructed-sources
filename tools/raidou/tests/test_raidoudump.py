"""Catalog, routing, rendering and naming over the fixture snippets."""
# pyright: reportPrivateUsage=false

import json
import shutil
from pathlib import Path

from raidou import dumpcs, raidoudump, smt3index
from raidou.raidoudump import Function, TypeInfo
from raidou.smt3index import Smt3Index

FIXTURES = Path(__file__).parent / "fixtures"


def _blocks() -> dict[str, raidoudump.Block]:
    with (FIXTURES / "il2cpp_snippet.h").open(encoding="utf-8") as fh:
        return raidoudump.parse_blocks(fh)


def _types_cs() -> list[dumpcs.TypeDef]:
    with (FIXTURES / "dump_snippet.cs").open(encoding="utf-8") as fh:
        return dumpcs.parse(fh)


def _methods() -> list[dict[str, object]]:
    script = json.loads((FIXTURES / "script_snippet.json").read_text(encoding="utf-8"))
    return script["ScriptMethod"]


def _build() -> raidoudump.Build:
    return raidoudump.build(_blocks(), _types_cs(), _methods())


def _by_clean(b: raidoudump.Build) -> dict[str, TypeInfo]:
    return {t.clean: t for t in b.cat.values()}


def test_parse_blocks_base() -> None:
    blocks = _blocks()
    vp = blocks["Project_libsdf_sdf3DViewportPacket_t_Fields"]
    assert vp.base == "Project_libsdf_sdfGrPacketHeader_t_Fields"
    assert vp.members == [
        "struct Project_libsdf_sdfCamera_o* cameraObject;",
        "struct Project_libsdf_sdf3DViewportPacket_t_o* traceSrc;",
    ]


def test_catalog_kinds() -> None:
    cat = _by_clean(_build())
    kinds = {name: t.kind for name, t in cat.items()}
    assert kinds["dds3KernelCore"] == "module"
    assert kinds["dds3ProcessID_t"] == "struct"
    assert kinds["DDS3_PRIORITY"] == "enum"
    assert kinds["dds3ProcessFunc_t"] == "delegate"
    assert kinds["SKIL176"] == "define"
    # instance methods make a port class; nothing kept refers to this one
    assert "sdf3DViewportPacket_t" not in kinds
    assert cat["Save_t"].ns == "" and cat["Save_t"].root == "Project_fld"


def test_routing() -> None:
    cat = _by_clean(_build())
    files = {name: t.file for name, t in cat.items()}
    assert files["dds3KernelCore"] == "dds3KernelCore.c"
    assert files["dds3ProcessID_t"] == "kernel.h"
    assert files["DDS3_PRIORITY"] == "kernel.h"
    assert files["Save_t"] == "fld.c"  # nested in a module, used only there
    assert files["SKIL176"] == "defines.h"  # unreferenced top-level constant group
    assert files["BOOK_CMDTYPE"] == "enums.h"  # unreferenced top-level enum


def test_instance_and_csharp_methods_dropped() -> None:
    b = _build()
    files = {f.linker: f.file for f in b.funcs}
    assert "Project.libsdf.sdf3DViewportPacket_t$$SetTrace" not in files
    assert "Project.SKIL176$$.ctor" not in files


def test_base_class_flattened() -> None:
    blocks = _blocks()
    types = raidoudump.Types(raidoudump.build_catalog(_types_cs(), blocks))
    members = raidoudump._instance_members("Project_libsdf_sdf3DViewportPacket_t", blocks)
    assert [raidoudump.rewrite_member(m, types)[0] for m in members] == [
        "sdfGrPacketHeader_t *next;",
        "s32 ctxt;",
        "void *cameraObject;",
        "sdf3DViewportPacket_t *traceSrc;",
    ]


def test_enum_restored_on_field_and_delegate_typedef() -> None:
    b = _build()
    model = b.files["kernel.h"]
    members = dict(model.structs)["dds3ProcessID_t"]
    assert "DDS3_PRIORITY priority;" in members
    assert "dds3ProcessFunc_t processfunc;" in members  # delegate typedef is the pointer
    assert "void *workdata;" in members  # opaque runtime value
    assert dict(model.delegates)["dds3ProcessFunc_t"] == (
        "typedef void *(*dds3ProcessFunc_t)(dds3ProcessID_t *UnnamedParameter);"
    )
    assert dict(model.enums)["DDS3_PRIORITY"][-1] == ("USERPROC", "1000")


def test_enum_restored_on_param() -> None:
    cat = raidoudump.build_catalog(_types_cs(), _blocks())
    types = raidoudump.Types(cat)
    meth = dumpcs.Method("SetPri", True, True, 0x10, [("DDS3_PRIORITY", "pri")])
    sig = "void Project_Kernel_dds3KernelCore__SetPri (int32_t pri, const MethodInfo* method);"
    parsed = raidoudump.parse_signature(sig, types, meth, cat["Project_Kernel_dds3KernelCore"])
    assert parsed is not None
    ret, params, refs = parsed
    assert (ret, params) == ("void", [("DDS3_PRIORITY", "pri")])
    assert refs == {"Project_Kernel_DDS3_PRIORITY"}


def test_const_value() -> None:
    assert raidoudump._const_value("float", "0,6") == "0.6"
    assert raidoudump._const_value("bool", "True") == "1"
    assert raidoudump._const_value("int", "-3") == "-3"


# --- naming -------------------------------------------------------------------


def _owner(name: str, root: str | None = None) -> TypeInfo:
    td = dumpcs.TypeDef("Project", name, "class", None, 0)
    cname = f"Project_{name.replace('.', '_')}"
    return TypeInfo(cname, "", "module", name.split(".")[-1], root or cname, td)


def _func(
    method: str, owner: TypeInfo, file: str, addr: int, *, public: bool = True, order: int = 0
) -> Function:
    f = Function(
        addr, f"Project.{owner.td.name}$${method}", "", owner, method, "void", [], set(),
        order, public,
    )
    f.file = file
    return f


def test_restore_prefixes_rule1_same_module() -> None:
    core = _owner("dds3KernelCore")
    idx = Smt3Index({}, {}, {"dds3KernelCore.c": ["dds3AddProcessList", "dds3Init", "Init"]})
    add = _func("AddProcessList", core, "dds3KernelCore.c", 1, public=False)
    pub = _func("Init", core, "dds3KernelCore.c", 2)
    raidoudump.restore_prefixes([add, pub], idx)
    assert (pub.display, pub.flag) == ("dds3Init", "R")
    assert (add.display, add.flag) == ("AddProcessList", "")  # private: a local, stays bare


def test_restore_prefixes_rule1_needs_class_prefix() -> None:
    snd = _owner("sndManager")
    idx = Smt3Index({}, {}, {"sndManager.c": ["SndPtnTestProcess", "sndPtnInit"]})
    fs = [_func("Process", snd, "sndManager.c", 1), _func("PtnInit", snd, "sndManager.c", 2)]
    raidoudump.restore_prefixes(fs, idx)
    # not SndPtnTestProcess: SndPtnTest is no prefix of sndManager
    assert [(f.display, f.flag) for f in fs] == [("sndProcess", "I"), ("sndPtnInit", "R")]


def test_restore_prefixes_rule2_global_and_ps2() -> None:
    draw = _owner("dds3KernelDraw")
    idx = Smt3Index({}, {}, {
        "dds3Misc.c": ["dds3FadeIn", "dds3KernelDrawStart", "dds3KernelInit"],
        "evt.c": ["dds3Held"],
    })
    fs = [
        _func("FadeIn", draw, "dds3KernelDraw.c", 1),
        _func("SetQuake", draw, "dds3KernelDraw.c", 2),
        _func("Init", draw, "dds3KernelDraw.c", 3),
        _func("Start", draw, "dds3KernelDraw.c", 4),
        _func("KernelInit", draw, "dds3KernelDraw.c", 5),  # dds3+Kernel...: the port took more
    ]
    raidoudump.restore_prefixes(fs, idx, frozenset({"dds3SetQuake"}))
    assert [(f.display, f.flag) for f in fs] == [
        ("dds3FadeIn", "R"),
        ("dds3SetQuake", "R"),  # PS2 name
        ("dds3KernelInit", "R"),
        ("dds3KernelDrawStart", "R"),  # longest prefix
        ("KernelInit", ""),
    ]


def test_restore_prefixes_rule3_inferred() -> None:
    draw = _owner("dds3KernelDraw")
    sky = _owner("evtSky")
    idx = Smt3Index({}, {}, {"dds3KernelDraw.c": ["dds3FadeIn", "Bare"]})
    fs = [
        _func("FadeIn", draw, "dds3KernelDraw.c", 1),
        _func("BistaIn", draw, "dds3KernelDraw.c", 2),
        _func("SetFinish", draw, "dds3KernelDraw.c", 3, public=False),
        _func("Bare", draw, "dds3KernelDraw.c", 4),  # SMT3 has it bare
        _func("PsBare", draw, "dds3KernelDraw.c", 5),  # PS2 has it bare
        _func("KernelX", draw, "dds3KernelDraw.c", 6),  # starts with the next class word
        _func("lower", draw, "dds3KernelDraw.c", 7),  # no camel boundary
        _func("Draw", sky, "evtSky.c", 8),
    ]
    raidoudump.restore_prefixes(fs, idx, frozenset({"PsBare"}), frozenset({"evt"}))
    assert [(f.display, f.flag) for f in fs] == [
        ("dds3FadeIn", "R"),
        ("dds3BistaIn", "I"),
        ("SetFinish", ""),
        ("Bare", ""),
        ("PsBare", ""),
        ("KernelX", ""),
        ("lower", ""),
        ("evtDraw", "I"),  # evt is a game module
    ]


def test_restore_prefixes_skips_taken_names_and_macros() -> None:
    draw = _owner("dds3KernelDraw")
    other = _owner("other")
    fs = [
        _func("Init", draw, "dds3KernelDraw.c", 1),
        _func("dds3Init", other, "other.c", 2),
        _func("DEG_RAD", draw, "dds3KernelDraw.c", 3),
    ]
    fs[2].macro = True
    raidoudump.restore_prefixes(fs, None, frozenset(), frozenset({"dds3"}))
    assert [(f.display, f.flag) for f in fs] == [
        ("Init", ""), ("dds3Init", ""), ("DEG_RAD", "M")
    ]


def test_restore_prefixes_drops_collision_suffix() -> None:
    file_ = _owner("file")
    fs = [
        _func("pacHandleFree_", file_, "file.c", 1),
        _func("Load_", file_, "file.c", 2),
        _func("Load", file_, "file.c", 3),
    ]
    raidoudump.restore_prefixes(fs, None)
    assert [f.display for f in fs] == ["pacHandleFree", "Load_", "Load"]


def test_name_functions_overloads_and_nested_clash() -> None:
    mod = _owner("fld")
    nested = _owner("fld.Save_t", root=mod.cname)
    a = _func("Load", mod, "fld.c", 0x20, order=0)
    b = _func("Load", mod, "fld.c", 0x10, order=1)
    c = _func("Copy", mod, "fld.c", 0x30)
    d = _func("Copy", nested, "fld.c", 0x40)
    fs = [a, b, c, d]
    raidoudump.restore_prefixes(fs, None)
    raidoudump.name_functions(fs)
    assert [f.display for f in fs] == ["Load", "Load_2", "Copy", "Save_t_Copy"]


def test_symbol_map_flags() -> None:
    core = _owner("dds3KernelCore")
    f = _func("Init", core, "dds3KernelCore.c", 0x22847A0)
    f.display, f.flag = "dds3Init", "R"
    g = _func("PadEi", core, "dds3KernelCore.c", 0x2285410)
    g.display = "PadEi"
    h = _func("Pad", core, "dds3KernelCore.c", 0x2285420)
    h.display, h.flag = "dds3Pad", "I"
    m = _func("DEG", core, "dds3kernelcore.h", 0x2285430)
    m.display, m.flag = "DEG", "M"
    rows = [r for r in raidoudump.symbol_map([g, f, m, h]).splitlines() if not r.startswith("#")]
    assert rows == [
        "0x022847a0  dds3Init  dds3KernelCore.c  Project.dds3KernelCore$$Init  R",
        "0x02285410  PadEi  dds3KernelCore.c  Project.dds3KernelCore$$PadEi",
        "0x02285420  dds3Pad  dds3KernelCore.c  Project.dds3KernelCore$$Pad  I",
        "0x02285430  DEG  dds3kernelcore.h  Project.dds3KernelCore$$DEG  M",
    ]


def test_scan_header() -> None:
    text = "#define FOO 1\ntypedef enum {\n    A = 0,\n} E_t;\nstruct S_t {\n    s32 x;\n};\n"
    assert smt3index.scan_header(text) == (["E_t", "S_t"], ["FOO"])


# --- end to end -----------------------------------------------------------------


def test_run_end_to_end(tmp_path: Path) -> None:
    inputs = tmp_path / "in"
    inputs.mkdir()
    shutil.copy(FIXTURES / "il2cpp_snippet.h", inputs / "il2cpp.h")
    shutil.copy(FIXTURES / "dump_snippet.cs", inputs / "dump.cs")
    shutil.copy(FIXTURES / "script_snippet.json", inputs / "script.json")
    smt3 = tmp_path / "smt3.json"
    smt3.write_text(json.dumps({
        "types": {}, "macros": {},
        "symbols": {"dds3KernelCore.c": ["dds3AddProcessList", "dds3Init"]},
    }))
    out = tmp_path / "out"
    counts = raidoudump.run(
        inputs / "il2cpp.h", inputs / "dump.cs", inputs / "script.json", out, smt3=smt3
    )
    assert counts["module"] == 2 and counts["enum"] == 2

    include = {p.name for p in (out / "include").iterdir()}
    src = {p.name for p in (out / "src").iterdir()}
    assert include == {
        "types.h", "kernel.h", "defines.h", "enums.h", "dds3kernelcore.h", "fld.h"
    }
    assert src == {"dds3KernelCore.c", "fld.c"}

    core = (out / "src" / "dds3KernelCore.c").read_text()
    assert "static dds3ProcessID_t *startinglistf;" in core
    assert "static void AddProcessList(dds3ProcessID_t *setp) {" in core
    # not in the trimmed dump.cs, so public: inferred prefix
    assert "bool dds3RunProcess(dds3ProcessID_t *pro) {\n    return 0;\n}" in core
    assert "void dds3Init(void) {" in core
    header = (out / "include" / "dds3kernelcore.h").read_text()
    assert "void dds3Init(void);" in header and "AddProcessList" not in header

    fld = (out / "src" / "fld.c").read_text()
    assert "#define TAKARA_SIZE 32" in fld
    assert "struct Save_t {" in fld
    assert "\nf32 CamKakudoY;" in fld  # public: defined here, extern in fld.h
    assert "extern f32 CamKakudoY;" in (out / "include" / "fld.h").read_text()

    symbols = (out / "symbols.txt").read_text()
    assert "0x022847a0  dds3Init  dds3KernelCore.c  Project.Kernel.dds3KernelCore$$Init  R" in (
        symbols
    )


# --- parameter types, derived structs, Unity members, shared statics -----------

_MINI_H = """\
struct Project_base_t_Fields {
	int32_t a;
	struct UnityEngine_GameObject_o* go;
	UnityEngine_Vector4_o pos;
};
struct Project_derived_t_Fields : Project_base_t_Fields {
};
struct Project_stack_u_Fields {
	int32_t i;
};
struct Project_pair_t_Fields {
	Project_stack_u_o s;
	int32_t n;
};
struct Project_a_StaticFields {
	int32_t x;
	int32_t y;
	struct UnityEngine_Texture2D_o* tex;
	struct Project_derived_t_o* d;
	struct Project_pair_t_o* p;
};
"""

_MINI_CS = """\
// Namespace: Project
public class base_t // TypeDefIndex: 1
{
	// Fields
	public int a; // 0x10
	public GameObject go; // 0x18
	public Vector4 pos; // 0x20
}

// Namespace: Project
public class derived_t : base_t // TypeDefIndex: 2
{
}

// Namespace: Project
public class stack_u // TypeDefIndex: 3
{
	// Fields
	public int i; // 0x10
}

// Namespace: Project
public class pair_t // TypeDefIndex: 4
{
	// Fields
	public stack_u s; // 0x10
	public int n; // 0x18
}

// Namespace: Project
public class cb_t : MulticastDelegate // TypeDefIndex: 5
{
	// Methods

	// RVA: 0x500 Offset: 0x500 VA: 0x500
	public virtual void Invoke() { }
}

// Namespace: Project
public class a // TypeDefIndex: 6
{
	// Fields
	private static int x; // 0x0
	private static int y; // 0x4
	private static Texture2D tex; // 0x8
	private static derived_t d; // 0x10
	private static pair_t p; // 0x18

	// Methods

	// RVA: 0x100 Offset: 0x100 VA: 0x100
	public static void Set(ref base_t p, object o, ref string s, short[] t, Vector4 v, ref cb_t cb) { }
}

// Namespace: Project
public class b // TypeDefIndex: 7
{
	// Methods

	// RVA: 0x200 Offset: 0x200 VA: 0x200
	public static void Get() { }
}
"""

_MINI_METHODS: list[dict[str, object]] = [
    {"Address": 0x100, "Name": "Project.a$$Set", "Signature": (
        "void Project_a__Set (Project_base_t_o** p, Il2CppObject** o, System_String_o** s, "
        "System_Int16_array* t, UnityEngine_Vector4_o v, Project_cb_t_o** cb, "
        "const MethodInfo* method);"
    )},
    {"Address": 0x200, "Name": "Project.b$$Get", "Signature": (
        "void Project_b__Get (const MethodInfo* method);"
    )},
    {"Address": 0x500, "Name": "Project.cb_t$$Invoke", "Signature": (
        "void Project_cb_t__Invoke (Project_cb_t_o* __this, const MethodInfo* method);"
    )},
]


def _mini() -> raidoudump.Build:
    blocks = raidoudump.parse_blocks(_MINI_H.splitlines())
    return raidoudump.build(blocks, dumpcs.parse(_MINI_CS.splitlines()), _MINI_METHODS)


def _render(b: raidoudump.Build, file: str) -> str:
    return raidoudump.render_file(file, b.files[file], b)


def test_param_types_follow_the_original_c() -> None:
    b = _mini()
    f = next(f for f in b.funcs if f.method == "Set")
    assert f.params == [
        ("base_t *", "p"),  # class by reference: one pointer
        ("void *", "o"),
        ("char **", "s"),  # a string by reference stays a pointer to one
        ("s16 *", "t"),  # managed array: one pointer to its elements
        ("const sdfVector4_t *", "v"),
        ("cb_t *", "cb"),  # a delegate's typedef is already the pointer
    ]
    assert f.dropped == (True, True, False, False, False, False)


def test_display_slots_skip_conflicts_and_plain_signatures() -> None:
    b = _mini()
    f, g = sorted(b.funcs, key=lambda f: f.address)
    f.display, g.display = "F", "G"
    assert raidoudump.display_slots([f, g]) == {"F": f.dropped}
    g.display, g.dropped = "F", (False,)
    assert raidoudump.display_slots([f, g]) == {}


def test_derived_struct_without_fields_is_a_typedef_of_its_base() -> None:
    b = _mini()
    assert b.alias == {"derived_t": "base_t"}
    out = _render(b, b.cat["Project_derived_t"].file)
    assert "typedef struct base_t derived_t;" in out
    assert "struct derived_t {" not in out


def test_unity_class_members_dropped_math_kept() -> None:
    b = _mini()
    base = _render(b, b.cat["Project_base_t"].file)
    assert "go;" not in base and "sdfVector4_t pos;" in base
    assert "tex" not in _render(b, b.cat["Project_a"].file)


def test_u_type_is_a_union_and_by_value_member_comes_first() -> None:
    b = _mini()
    file = b.cat["Project_pair_t"].file
    model = b.files[file]
    model.structs.sort(key=lambda s: s[0] != "pair_t")  # user first: order must be fixed
    assert b.cat["Project_stack_u"].file == file
    out = _render(b, file)
    assert out.index("union stack_u {") < out.index("struct pair_t {")
    assert "typedef union stack_u stack_u;" in out


def test_static_touched_from_another_file_becomes_extern_global() -> None:
    b = _mini()
    named = {f.mangled: f for f in b.funcs}
    uses = {("Project_b__Get", "Project_a", "x"), ("Project_a__Set", "Project_a", "y")}
    assert raidoudump.share_statics(b, uses, named) == 1
    a_c = _render(b, b.cat["Project_a"].file)
    assert "\ns32 x;" in a_c and "static s32 y;" in a_c
    hdr = b.fams.header_of(b.cat["Project_a"])
    assert hdr is not None and "extern s32 x;" in _render(b, hdr)
    assert f'#include "{hdr}"' in _render(b, b.cat["Project_b"].file)


def test_load_array_lengths(tmp_path: Path) -> None:
    p = tmp_path / "array_lengths.json"
    assert raidoudump.load_array_lengths(p) == {}
    p.write_text(json.dumps({"Project_fld": {"tbl": [12, True]}}))
    assert raidoudump.load_array_lengths(p) == {("Project_fld", "tbl"): (12, True)}


def test_enum_members_that_clash_take_the_enum_name() -> None:
    a = raidoudump._FileModel(enums=[("BOOK_CMDFLAG", [("NONE", "0"), ("MOVELOCK", "2")])])
    b = raidoudump._FileModel(
        enums=[("BOOK_CMDSTAT", [("NONE", "0"), ("BOOK_CMDSTAT_NEXT", "2")]),
               ("BTL_SIDE", [("_3D", "0"), ("AGI", "1")]),
               ("PAD", [("UP", "1")])],
        defines=[("sBtl", [("AGI", "2")])],
    )
    assert raidoudump.unique_enum_members({"a.h": a, "b.h": b}, {"UP2"}) == 3
    assert a.enums == [("BOOK_CMDFLAG", [("BOOK_CMDFLAG_NONE", "0"), ("BOOK_CMDFLAG_MOVELOCK", "2")])]
    assert b.enums == [
        ("BOOK_CMDSTAT", [("BOOK_CMDSTAT_NONE", "0"), ("BOOK_CMDSTAT_NEXT", "2")]),
        ("BTL_SIDE", [("BTL_SIDE_3D", "0"), ("BTL_SIDE_AGI", "1")]),
        ("PAD", [("UP", "1")]),
    ]
