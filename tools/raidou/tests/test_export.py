"""Raidou export bodies: class-init and metadata guards, labels, static members by offset."""
# pyright: reportPrivateUsage=false

from pathlib import Path

from raidou import hexrays
from raidou.layout import Layout
from raidou.raidoudump import Block

_FIXTURES = Path(__file__).parent / "fixtures"


def _export(name: str) -> list[str]:
    return (_FIXTURES / f"export_{name}.c").read_text().splitlines()


def _body(name: str) -> tuple[str, str]:
    """(cleaned body, approximation reason) of the single function in a fixture."""
    bodies, reasons = hexrays.clean_bodies(
        _export(name), static_member=_member, type_name=lambda t: t.removeprefix("Project_"),
        object_member=_LAYOUT.members_at,
    )
    ((fn, body),) = bodies.items()
    return body, reasons.get(fn, "")


_LAYOUT = Layout(
    {
        "Project_Kernel_dds3KernelCore_StaticFields": Block(
            "Project_Kernel_dds3KernelCore_StaticFields",
            None,
            ["struct Project_Kernel_dds3ProcessID_t_o* startinglistf;", "uint16_t pad;",
             "uint16_t mode;", "struct UnityEngine_Vector4_o col;"],
        ),
        "UnityEngine_Vector4_o": Block(
            "UnityEngine_Vector4_o", None, ["struct UnityEngine_Vector4_Fields fields;"]
        ),
        "UnityEngine_Vector4_Fields": Block(
            "UnityEngine_Vector4_Fields", None, ["float x;", "float y;", "float z;", "float w;"]
        ),
        "System_Single_array": Block(
            "System_Single_array", None,
            ["Il2CppObject obj;", "Il2CppArrayBounds *bounds;",
             "il2cpp_array_size_t max_length;", "float m_Items[65535];"],
        ),
        "UnityEngine_Vector4_array": Block(
            "UnityEngine_Vector4_array", None,
            ["Il2CppObject obj;", "Il2CppArrayBounds *bounds;",
             "il2cpp_array_size_t max_length;", "struct UnityEngine_Vector4_o m_Items[65535];"],
        ),
        "Project_Kernel_dds3ProcessID_t_o": Block(
            "Project_Kernel_dds3ProcessID_t_o", None,
            ["Project_Kernel_dds3ProcessID_t_c *klass;", "void *monitor;",
             "Project_Kernel_dds3ProcessID_t_Fields fields;"],
        ),
        "Project_Kernel_dds3ProcessID_t_Fields": Block(
            "Project_Kernel_dds3ProcessID_t_Fields", None,
            ["struct System_String_o* name;", "int32_t nameHash;", "uint32_t flag;",
             "int32_t priority;", "uint32_t starttime;", "uint32_t runtime;", "int32_t id;",
             "int32_t starttimer;", "int32_t shutdowntimer;",
             "struct Project_Kernel_dds3ProcessFunc_t_o* processfunc;",
             "struct Project_Kernel_shutdownfuncDelegate_o* shutdownfunc;",
             "Il2CppObject* workdata;", "struct Project_Kernel_dds3ProcessID_t_o* next;",
             "struct Project_Kernel_dds3ProcessID_t_o* prev;",
             "struct UnityEngine_Vector4_o col;", "float scale;",
             "struct System_Int32_array* list;"],
        ),
    }
)


def _member(cls: str, offset: int, width: int | None) -> str | None:
    return _LAYOUT.member_at(f"{cls}_StaticFields", offset, width)


def test_definitions_and_addresses() -> None:
    src = ["void __fastcall X__f(const MethodInfo *method);", *_export("SearchProcessPriority")]
    funcs = list(hexrays.iter_functions(src))
    assert [(n, a) for n, a, _s, _b in funcs] == [
        ("Project_Kernel_dds3KernelCore__SearchProcessPriority", 0x2286EA0)
    ]
    assert funcs[0][3][-1] == "  return result;"


def test_lost_allocation_result_is_reattached() -> None:
    text = "  il2cpp::NewSpecific(int___TypeInfo, 4);\n  this->fields.OfsX = v10;\n  v10 = 0;"
    assert "v10 = il2cpp::NewSpecific" not in hexrays._recover_alloc_results(text)
    text = "  il2cpp::NewSpecific(int___TypeInfo, 4);\n  this->fields.OfsX = v10;"
    assert hexrays._recover_alloc_results(text) == (
        "  v10 = il2cpp::NewSpecific(int___TypeInfo, 4);\n  this->fields.OfsX = v10;"
    )


def test_array_size_from_a_constructor() -> None:
    sizes = hexrays.array_sizes(_export("VISUALDATA_WORK_ctor"))
    assert sizes == {("Project_VISUALDATA_WORK", "mwk"): (48, False)}


def test_static_members_named_from_offsets() -> None:
    text = (
        "  *(_WORD *)(Project_Kernel_dds3KernelCore_TypeInfo->static_fields + 10) = 1;\n"
        "  *(float *)(Project_Kernel_dds3KernelCore_TypeInfo->static_fields + 16) = 2.0;\n"
        "  *(_DWORD *)(Project_Kernel_dds3KernelCore_TypeInfo->static_fields + 9) = 3;\n"
        "  f((T *)(Project_Kernel_dds3KernelCore_TypeInfo->static_fields + 12));\n"
        "  p = *Project_Kernel_dds3KernelCore_TypeInfo->static_fields;\n"
    )
    out = hexrays._name_static_members(text, _member)
    sf = "Project_Kernel_dds3KernelCore_TypeInfo->static_fields->"
    assert f"{sf}mode = 1;" in out
    assert f"{sf}col.fields.y = 2.0;" in out
    assert "static_fields + 9) = 3;" in out  # no member starts there
    assert f"f(&{sf}col);" in out
    assert f"p = {sf}startinglistf;" in out


def test_search_keeps_the_label_the_initialised_path_jumps_to() -> None:
    body, _ = _body("SearchProcessPriority")
    assert body.startswith("  Kernel_dds3ProcessID_t *result;\n\n  result = startinglistf;\n")
    assert body.count("while (result->priority != priority)") == 2
    assert "LABEL_6:\n  result = runninglistf;" in body
    for junk in ("byte_", "cctor", "TypeInfo", "v3", "Initialize", "LABEL_3", "LABEL_4"):
        assert junk not in body, junk


def test_start_process_has_no_jump_into_a_dropped_arm() -> None:
    body, reason = _body("StartProcess")
    assert reason == ""
    assert "LABEL" not in body and "goto" not in body
    assert "    if (!v15->starttimer)\n    {\n      DeleteProcessList(v15);" in body
    assert body.count("AddProcessList(v15);") == 2


def test_allocated_object_is_typed_and_its_fields_named() -> None:
    body, _ = _body("StartProcess")
    assert body.startswith("  Kernel_dds3ProcessID_t *v15;")
    assert "\n  v15 = Allocate(Kernel_dds3ProcessID_t);\n  if (v15)\n" in body
    for line in ("v15->name = namestr;", "v15->starttimer = starttimer;",
                 "v15->workdata = data;", "v15->flag = v15->flag & 0xFFFFFFF0 | 2;",
                 "return v15;"):
        assert line in body, line
    assert "(v15 + " not in body and "_ctor" not in body


_PID = "Project_Kernel_dds3ProcessID_t"


def _typed(lines: str) -> str:
    raw = (
        f"  __int64 v3; // x19\n\n  v3 = j_il2cpp::Allocate({_PID}_TypeInfo);\n"
        f"  System_Object___ctor((Il2CppObject *)v3, nullptr);\n{lines}"
    )
    return hexrays._type_alloc_locals(hexrays._drop_default_ctors(raw), _LAYOUT.members_at)


def test_field_access_that_changes_type_keeps_the_reinterpretation() -> None:
    out = _typed(
        "  *(_QWORD *)(v3 + 24) = 0;\n"  # nameHash and flag in one store
        "  *(_DWORD *)(v3 + 112) = 1065353216;\n"  # a float written as its bits
        "  *(float *)(v3 + 100) = 2.0;\n"  # col.y
        "  x = *(_DWORD *)(*(_QWORD *)(v3 + 120) + 4LL * i + 32);\n"
        "  *(_QWORD *)(v3 + 80) = v8;\n"
        "  ++*(_DWORD *)(v3 + 36);\n"
        "  f((void *)(v3 + 16), v3 + 48);\n"
        "  y = *(unsigned int *)(v3 + 32);\n"
    )
    assert out.startswith(f"  {_PID}_o *v3; // x19\n\n  v3 = j_il2cpp::Allocate(")
    assert "System_Object___ctor" not in out
    for line in (
        "  *(_QWORD *)&v3->fields.nameHash = 0;",
        "  *(_DWORD *)&v3->fields.scale = 1065353216;",
        "  v3->fields.col.fields.y = 2.0;",
        "  x = *(_DWORD *)((_QWORD)v3->fields.list + 4LL * i + 32);",
        "  v3->fields.next = v8;",
        "  ++v3->fields.starttime;",
        "  f((void *)&v3->fields.name, (__int64)&v3->fields.starttimer);",
        "  y = (unsigned int)v3->fields.priority;",
    ):
        assert line in out, line


def test_allocation_local_with_other_uses_stays_raw() -> None:
    reused = "  *(_DWORD *)(v3 + 48) = 1;\n  v3 = sub_10(v3);\n"
    assert "__int64 v3;" in _typed(reused)
    arith = "  *(_DWORD *)(v3 + 48) = 1;\n  v4 = v3 + v5;\n"
    assert "__int64 v3;" in _typed(arith)
    odd = "  *(_DWORD *)(v3 + 50) = 1;\n  *(_DWORD *)(v3 + 48) = 1;\n"
    out = _typed(odd)
    assert "*(_DWORD *)((char *)v3 + 50) = 1;" in out and "v3->fields.starttimer = 1;" in out


def test_destroy_message_folds_the_twin_jump() -> None:
    body, reason = _body("DestroyMessage")
    assert reason == ""
    assert body == (
        "  if ((gMsgID & 0x80000000) == 0)\n  {\n    MesMngRelease(gMsgID, 0);\n"
        "    gMsgID = -1;\n    *(u16 *)&gMsgFlag = 0;\n    return 1;\n  }\n  return 0;"
    )


def test_braceless_guards_fold_to_the_initialised_path() -> None:
    raw = (
        "  if ( !X_TypeInfo->_2.cctor_finished )\n    goto LABEL_5;\n"
        "  if ( v1->_2.cctor_finished )\n    goto LABEL_6;\n"
        "  if ( (byte_57 & 1) == 0 )\n    return 1;\n"
        "  return 2;\nLABEL_5:\n  return 3;\nLABEL_6:\n  return 4;\n"
    )
    assert hexrays._fold_guard_ifs(raw) == (
        "  goto LABEL_6;\n  return 2;\nLABEL_5:\n  return 3;\nLABEL_6:\n  return 4;\n"
    )


def test_unreachable_statements_and_orphan_labels_go() -> None:
    raw = (
        "  goto LABEL_3;\n  a = 1;\n  if ( b )\n  {\n    c = 2;\n  }\nLABEL_3:\n  d = 3;\n"
        "  if ( e )\n    return 1;\n  f = 4;\n  return 0;\n  g = 5;\n"
    )
    assert hexrays._drop_unreachable(raw) == (
        "  d = 3;\n  if ( e )\n    return 1;\n  f = 4;\n  return 0;\n"
    )


def test_twin_arms_keep_one_copy() -> None:
    raw = (
        "bool __fastcall Project_ctn__CheckWait(Project_ctnCitizen_t_o *c, const MethodInfo *method)\n"
        "{\n"
        "  struct Project_ctnWork_t_o *Work; // x8\n\n"
        "  if ( Project_ctn_TypeInfo->_2.cctor_finished )\n  {\n"
        "    Work = Project_ctn_TypeInfo->static_fields->Work;\n"
        "    if ( Work->fields.mapID != 2 )\n      return 0;\n  }\n"
        "  else\n  {\n    il2cpp::TypeInitializer(Project_ctn_TypeInfo);\n"
        "    Work = Project_ctn_TypeInfo->static_fields->Work;\n"
        "    if ( Work->fields.mapID != 2 )\n      return 0;\n  }\n"
        "  return 1;\n}\n"
    )
    bodies, reasons = hexrays.clean_bodies(raw.splitlines())
    assert bodies["Project_ctn__CheckWait"] == "  if (Work->mapID != 2)\n    return 0;\n  return 1;"
    assert not reasons


def test_jump_into_a_dropped_label_is_reported() -> None:
    assert hexrays._complexity("  goto LABEL_3;\n  return;") == "goto into dropped label"
    assert hexrays._complexity("  goto LABEL_3;\nLABEL_3:\n  return;") == "goto control flow"


def test_negate_inverts_simple_conditions() -> None:
    assert hexrays._negate("v3 != -1") == "v3 == -1"
    assert hexrays._negate("!map") == "map"
    assert hexrays._negate("!(a & 1)") == "a & 1"
    assert hexrays._negate("a->b") == "!a->b"
    assert hexrays._negate("a && b") == "!(a && b)"
    assert hexrays._negate("f(a == b)") == "!f(a == b)"
    assert hexrays._negate("(x & 4) != 0") == "(x & 4) == 0"


def test_goto_over_statements_becomes_an_if() -> None:
    raw = (
        "  if (map)\n    goto LABEL_3;\n  return 0;\nLABEL_3:\n"
        "  if (v3 != -1)\n    goto LABEL_4;\n  v3 = f();\n  g(v3);\nLABEL_4:\n  return v3;\n"
    )
    assert hexrays._drop_unreachable(raw) == (
        "  if (!map)\n    return 0;\n"
        "  if (v3 == -1)\n  {\n    v3 = f();\n    g(v3);\n  }\n  return v3;\n"
    )


def test_array_store_check_goes_with_its_jump() -> None:
    raw = (
        "void __fastcall X__f(Il2CppObject *v54, const MethodInfo *method)\n{\n"
        "  if ( v54 )\n  {\n"
        "    if ( !il2cpp::QueryInterface(v54, v50->klass->_1.element_class) )\n"
        "      goto LABEL_24;\n  }\n"
        "  v50->fields.m_Material = v54;\n  g(v54);\n  return;\n"
        "  if ( v54 )\n  {\n    {\nLABEL_24:\n      il2cpp::ThrowArrayTypeMismatchException();\n    }\n  }\n"
        "}\n"
    )
    bodies, reasons = hexrays.clean_bodies(raw.splitlines())
    assert bodies["X__f"] == "  v50->m_Material = v54;\n  g(v54);\n  return;"
    assert not reasons


def test_condition_of_an_emptied_if_is_kept() -> None:
    body, reason = _body("NEFMODE_Func_Exitok")
    assert reason == ""
    assert (
        "    if (!CHECK_TRIG(4097, 1, 0))\n    {\n      if (!CHECK_TRIG2(4096, 0))\n        return 1;\n"
    ) in body
    assert "\n\n    {" not in body


def test_emptied_if_keeps_its_calls() -> None:
    assert hexrays._strip_empty_ifs("  if (f(1))\n  {\n  }\n  g();\n") == "  f(1);\n  g();\n"
    assert hexrays._strip_empty_ifs("  if (!f(1))\n  {\n  }\n") == "  f(1);\n"
    assert hexrays._strip_empty_ifs("  if (a && f(1))\n  {\n  }\n") == "  if (a)\n    f(1);\n"
    assert hexrays._strip_empty_ifs("  if (a > 1)\n  {\n  }\n  g();\n") == "  g();\n"
    assert hexrays._strip_empty_ifs("  if (a)\n  {\n  }\n  else\n    g();\n") == (
        "  if (!a)\n    g();\n"
    )


def test_default_constructors_after_an_allocation_go() -> None:
    ctors = hexrays.default_ctors([
        "void __fastcall Project_A___ctor(Project_A_o *this, const MethodInfo *method)", "{",
        "  System_Object___ctor((Il2CppObject *)this, 0LL);", "}",
        "void __fastcall Project_B___ctor(Project_B_o *this, const MethodInfo *method)", "{",
        "  this->fields.x = 1;", "  System_Object___ctor((Il2CppObject *)this, 0LL);", "}",
    ])
    assert ctors == frozenset({"Project_A___ctor"})
    raw = (
        "  v3 = j_il2cpp::Allocate(Project_A_TypeInfo);\n"
        "  Project_A___ctor((Project_A_o *)v3, nullptr);\n"
        "  v4 = j_il2cpp::Allocate(Project_B_TypeInfo);\n"
        "  Project_B___ctor((Project_B_o *)v4, nullptr);\n"
        "  Project_A___ctor((Project_A_o *)v4, nullptr);\n"
    )
    assert hexrays._drop_default_ctors(raw, ctors) == (
        "  v3 = j_il2cpp::Allocate(Project_A_TypeInfo);\n"
        "  v4 = j_il2cpp::Allocate(Project_B_TypeInfo);\n"
        "  Project_B___ctor((Project_B_o *)v4, nullptr);\n"
        "  Project_A___ctor((Project_A_o *)v4, nullptr);\n"
    )


def test_class_init_woven_into_a_condition_keeps_its_calls() -> None:
    raw = (
        "void __fastcall X__f(const MethodInfo *method)\n{\n"
        "  if ( m && Project_JMS__ITEMIDX(m, nullptr) != -1 && !Project_dat_TypeInfo->_2.cctor_finished )\n"
        "    il2cpp::TypeInitializer(Project_dat_TypeInfo);\n"
        "  if ( k == 2 && !Project_dat_TypeInfo->_2.cctor_finished )\n"
        "    il2cpp::TypeInitializer(Project_dat_TypeInfo);\n"
        "  Project_Book__CheckMenuBit_Exception(1, nullptr);\n"
        "  il2cpp::ThrowInvalidCastException(v3);\n"
        "  g();\n}\n"
    )
    bodies, _ = hexrays.clean_bodies(raw.splitlines())
    assert bodies["X__f"] == (
        "  if (m)\n    ITEMIDX(m, 0);\n  CheckMenuBit_Exception(1, 0);\n  g();"
    )


def test_array_layout_names_elements() -> None:
    assert _LAYOUT.members_at("System_Single_array", 36) == [("m_Items[1]", 4, "float")]
    assert _LAYOUT.members_at("System_Single_array", 16) == []
    assert _LAYOUT.members_at("UnityEngine_Vector4_array", 52) == [
        ("m_Items[1].fields.y", 4, "float")
    ]


def test_new_array_local_is_typed_and_indexed() -> None:
    raw = (
        "  __int64 v4; // x0\n  __int64 v5; // x1\n\n"
        "  v4 = il2cpp::NewSpecific(float___TypeInfo, 2u);\n"
        "  *(float *)(v4 + 32) = 1.0;\n  *(float *)(v4 + 36) = x;\n"
        "  y = *(float *)(v4 + 4LL * i + 32);\n  *(_DWORD *)(v4 + 32) = 0;\n"
        f"  v3 = j_il2cpp::Allocate({_PID}_TypeInfo);\n"
        "  v5 = *(_QWORD *)(v3 + 80);\n  *(_DWORD *)(v5 + 48) = 1;\n"
    )
    out = hexrays._type_alloc_locals("  __int64 v3; // x2\n" + raw, _LAYOUT.members_at)
    for line in (
        "  System_Single_array *v4; // x0", f"  {_PID}_o *v5; // x1",
        "  v4->m_Items[0] = 1.0;", "  v4->m_Items[1] = x;", "  y = v4->m_Items[i];",
        "  *(_DWORD *)&v4->m_Items[0] = 0;", "  v5->fields.starttimer = 1;",
    ):
        assert line in out, line
