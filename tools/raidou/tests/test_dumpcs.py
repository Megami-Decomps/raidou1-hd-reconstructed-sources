"""dump.cs parsing."""

from pathlib import Path

from raidou import dumpcs

FIXTURES = Path(__file__).parent / "fixtures"


def _types() -> dict[str, dumpcs.TypeDef]:
    with (FIXTURES / "dump_snippet.cs").open(encoding="utf-8") as fh:
        return {t.name: t for t in dumpcs.parse(fh)}


def test_nested_type_has_empty_namespace() -> None:
    save = _types()["fld.Save_t"]
    assert save.namespace == ""
    assert save.kind == "class"
    assert [f.name for f in save.fields][:3] == ["takara", "tmnltype", "tmnlid"]
    assert save.fields[0].type == "byte[]"


def test_consts_static_fields_and_methods() -> None:
    fld = _types()["fld"]
    assert fld.namespace == "Project"
    assert fld.consts == [
        ("MAPOBJCLEAR_MAX", "int", "64"),
        ("MAPTAKARA_MAX", "int", "256"),
        ("TAKARA_SIZE", "int", "32"),
    ]
    assert [(f.name, f.type, f.static) for f in fld.fields] == [
        ("CamTableIdx", "int", True),
        ("CamKakudoY", "float", True),
    ]
    (m,) = fld.methods
    assert (m.name, m.static, m.public, m.rva, m.params) == (
        "CallFieldResult", True, True, 0x1A3B820, []
    )


def test_method_visibility_params_and_base() -> None:
    types = _types()
    core = types["dds3KernelCore"]
    add = next(m for m in core.methods if m.name == "AddProcessList")
    assert (add.public, add.static, add.rva) == (False, True, 0x2284BF0)
    assert add.params == [("dds3ProcessID_t", "setp")]
    assert types["sdf3DViewportPacket_t"].base == "sdfGrPacketHeader_t"
    assert types["dds3ProcessFunc_t"].base == "MulticastDelegate"


def test_enum_members_are_consts() -> None:
    pri = _types()["DDS3_PRIORITY"]
    assert pri.kind == "enum"
    assert pri.consts[0] == ("KERNELPROC", "DDS3_PRIORITY", "0")
    assert pri.consts[-1] == ("USERPROC", "DDS3_PRIORITY", "1000")


def test_generic_names_with_spaces() -> None:
    text = """\
// Namespace: Project
public class Holder<T, U> : Base<int, string> // TypeDefIndex: 7
{
\t// Fields
\tprivate Dictionary<int, string> map; // 0x10

\t// Methods

\t// RVA: 0x10 Offset: 0x10 VA: 0x10
\tpublic void Put(Dictionary<int, string> d, ref int n = 0) { }
}
"""
    (t,) = dumpcs.parse(text.splitlines())
    assert t.name == "Holder<T, U>"
    assert t.base == "Base<int, string>"
    assert t.fields[0].type == "Dictionary<int, string>"
    assert t.methods[0].params == [("Dictionary<int, string>", "d"), ("ref int", "n")]
