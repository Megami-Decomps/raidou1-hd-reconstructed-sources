"""Hex-Rays export recovery: array sizes, call graph, body cleaning."""
# pyright: reportPrivateUsage=false

from pathlib import Path

from raidou import hexrays

_CTOR_C = """\
void __fastcall Project_dds3UnitStatus_t___ctor(Project_dds3UnitStatus_t_o *this, int *m)
{
  this->fields.rpoints = il2cpp::NewSpecific(byte___TypeInfo, 4u);
  this->fields.regists = il2cpp::NewSpecific(sbyte___TypeInfo, 8u);
  this->fields.actors = il2cpp::NewSpecific(Project_dds3Basic_t___TypeInfo, 3u);
  this->fields.dynamic = il2cpp::NewSpecific(byte___TypeInfo, 0);
}
void __fastcall beast_aisyo___cctor(const MethodInfo *m)
{
  v1 = il2cpp::NewSpecific(byte___TypeInfo, 0xDD1u);
  beast_aisyo_TypeInfo->static_fields->tbl = v1;
}
void __fastcall Project_scrHeader_t___ctor(
        Project_scrHeader_t_o *this,
        System_Byte_array *dat,
        const MethodInfo *method)
{
  this->fields.names = il2cpp::NewSpecific(sbyte___TypeInfo, 16u);
}
"""


_MULTILINE_C = """\
void __fastcall Project_w_t___ctor(Project_w_t_o *this, const MethodInfo *m)
{
  this->fields.wide = il2cpp::NewSpecific(
                        byte___TypeInfo,
                        7u);
}
void __fastcall wide_cc___cctor(const MethodInfo *m)
{
  v9 = il2cpp::NewSpecific(
         int___TypeInfo,
         5u);
  wide_cc_TypeInfo->static_fields->widetbl = v9;
}
"""


_BODIES = """\
void __fastcall fldMain__fldSetUnit(const MethodInfo *method)
{
  if ( x )
    ScrTraceCode__CodeFunc_Add(a, b);
  v3 = il2cpp::NewSpecific(byte___TypeInfo, 4u);
  fldMain__fldChk();
  ScrTraceCode__CodeFunc_Add(c, d);
}
void __fastcall System_String___ctor(System_String_o *this, const MethodInfo *method)
{
  fldMain__fldChk();
}
"""


_SIMPLE_FN = """\
int32_t __fastcall datCalc__datGetParam(Project_datUnitWork_t_o *work, const MethodInfo *method)
{
  int32_t BaseParam; // w0
  if ( (byte_3F5A210 & 1) == 0 )
  {
    il2cpp::InitializeMethodMetadata(0x40DDu);
    byte_3F5A210 = 1;
  }
  BaseParam = datCalc__datGetBaseParam(work, 3, method);
  return work->fields.level + BaseParam;
}
"""


def test_array_sizes_multiline_signature() -> None:
    # Regression: the receiver `_o *this` param sits on its own line, so the struct context
    # must be picked up there, not only when it shares the __fastcall line.
    s = hexrays.array_sizes(_CTOR_C.splitlines())
    assert s[("Project_scrHeader_t", "names")] == (16, True)


def test_array_sizes_instance_and_static() -> None:
    s = hexrays.array_sizes(_CTOR_C.splitlines())
    assert s[("Project_dds3UnitStatus_t", "rpoints")] == (4, True)  # byte -> value
    assert s[("Project_dds3UnitStatus_t", "regists")] == (8, True)  # sbyte -> value
    assert s[("Project_dds3UnitStatus_t", "actors")] == (3, False)  # class -> reference
    assert s[("beast_aisyo", "tbl")] == (0xDD1, True)  # static, hex, via local var
    assert ("Project_dds3UnitStatus_t", "dynamic") not in s  # size 0 -> skipped


def test_array_sizes_multiline_newspecific() -> None:
    # Hex-Rays wraps long allocations across physical lines; the scanner joins them.
    s = hexrays.array_sizes(_MULTILINE_C.splitlines())
    assert s[("Project_w_t", "wide")] == (7, True)  # multi-line instance alloc
    assert s[("wide_cc", "widetbl")] == (5, True)  # multi-line static via local var


def test_call_graph_extraction() -> None:
    valid = frozenset({"ScrTraceCode__CodeFunc_Add", "fldMain__fldChk"})
    g = hexrays.call_graph(_BODIES.splitlines(), valid)
    # only valid callees, deduped, in first-seen order; il2cpp:: and keywords ignored
    assert g["fldMain__fldSetUnit"] == ["ScrTraceCode__CodeFunc_Add", "fldMain__fldChk"]


def test_clean_bodies_strips_boilerplate() -> None:
    bodies, reasons = hexrays.clean_bodies(_SIMPLE_FN.splitlines())
    body = bodies["datCalc__datGetParam"]
    assert "InitializeMethodMetadata" not in body  # metadata guard gone
    assert "MethodInfo" not in body and "byte_3F5A210" not in body
    assert "datGetBaseParam(work, 3)" in body  # method-context arg + name mangling stripped
    assert "work->level" in body  # ->fields. collapsed
    assert not reasons  # this one is simple


def test_clean_bodies_static_fields_and_reason() -> None:
    fn = (
        "void __fastcall dds3__Init(const MethodInfo *method)\n{\n"
        "  v3->static_fields->DDS3_GBWK = 0;\n"
        "  sub_8FC2C0(v3);\n}\n"  # sub_ helper -> complex
    )
    bodies, reasons = hexrays.clean_bodies(fn.splitlines())
    assert "DDS3_GBWK = 0;" in bodies["dds3__Init"]  # body kept even though tangled
    assert reasons["dds3__Init"] == "inlined sub_ helper(s)"  # recorded as a caveat


def test_clean_body_strips_typeinfo_and_metadata_variants() -> None:
    # the `if (byte & 1) == 0 { InitMeta(); }` variant (no `byte = 1`) + dead TypeInfo lines
    fn = (
        "int __fastcall m__f(const MethodInfo *x)\n{\n"
        "  dds3GlobalWork_c *dds3GlobalWork_TypeInfo;\n"
        "  if ( (byte_3F5A20B & 1) == 0 )\n  {\n"
        "    il2cpp::InitializeMethodMetadata(0x40ABu);\n  }\n"
        "  dds3GlobalWork_TypeInfo = ::dds3GlobalWork_TypeInfo;\n"
        "  return dds3GlobalWork_TypeInfo->static_fields->GBWK->fields.hp;\n}\n"
    )
    bodies, _ = hexrays.clean_bodies(fn.splitlines())
    body = bodies["m__f"]
    assert "InitializeMethodMetadata" not in body
    assert "_TypeInfo" not in body
    assert "return GBWK->hp;" in body  # static_fields + ->fields. collapsed


def test_entangled_metadata_is_flagged_not_dropped() -> None:
    # a cctor guard wrapping real code: the body is kept, the risk is noted
    fn = (
        "void __fastcall m__g(const MethodInfo *x)\n{\n"
        "  if ( v5 && !v3->_2.cctor_finished )\n  {\n"
        "    il2cpp::TypeInitializer(v3, x);\n"
        "    GBWK->static_fields->hp = v7;\n  }\n"
        "  else\n  {\n    GBWK->hp = v7;\n  }\n}\n"
    )
    bodies, reasons = hexrays.clean_bodies(fn.splitlines())
    assert "m__g" in bodies  # body kept: it still carries the real assignments
    assert "woven" in reasons["m__g"] or "unbalanced" in reasons["m__g"]


def test_static_fields_global_collapses() -> None:
    fn = "int __fastcall m__f(const MethodInfo *x)\n{\n  return v3->static_fields->DDS3_GBWK;\n}\n"
    bodies, _ = hexrays.clean_bodies(fn.splitlines())
    assert bodies["m__f"] == "  return DDS3_GBWK;"


def test_clean_body_maps_plain_c_spellings() -> None:
    fn = "void __fastcall m__f(const MethodInfo *x)\n{\n  unsigned int a;\n  int b;\n  a = b;\n}\n"
    body = hexrays.clean_bodies(fn.splitlines())[0]["m__f"]
    assert "u32 a;" in body  # plain `unsigned int` -> u32 (not `unsigned s32`)
    assert "s32 b;" in body


def test_clean_body_calls_follow_display_map() -> None:
    fn = "void __fastcall A__f(const MethodInfo *m)\n{\n  A_x_t__Set();\n  B__g();\n}\n"
    names = {"A_x_t__Set": "A_x_t__Set", "B__g": "g"}  # first kept full, second stripped
    bodies, _ = hexrays.clean_bodies(fn.splitlines(), names)
    body = bodies["A__f"]
    assert "A_x_t__Set();" in body  # same-file collision -> full name preserved
    assert "  g();" in body  # unambiguous -> stripped


def test_clean_body_drops_unused_local_declarations() -> None:
    fn = (
        "void __fastcall m__f(const MethodInfo *x)\n{\n"
        "  s64 v1;\n"
        "  dds3TitleMain_c *v2;\n"
        "  s32 keep;\n"
        "  keep = 5;\n"
        "  GBWK = keep;\n}\n"
    )
    body = hexrays.clean_bodies(fn.splitlines())[0]["m__f"]
    assert "v1" not in body  # declared once, never used
    assert "v2" not in body
    assert "s32 keep;" in body  # used -> kept


def test_clean_body_reconciles_call_arity() -> None:
    fn = (
        "void __fastcall m__f(const MethodInfo *x)\n{\n"
        "  sdfTexFree(handle, 0);\n"     # proto arity 1, trailing 0 = MethodInfo
        "  p2sdPlaySE(0, 0);\n"          # first 0 real, second is context
        "  p2sdPlaySE(0);\n"             # already correct, untouched
        "  AddComponent(obj, Method_Foo);\n}\n"  # Method_ literal dropped regardless of arity
    )
    arity = {"sdfTexFree": 1, "p2sdPlaySE": 1}
    body = hexrays.clean_bodies(fn.splitlines(), None, arity)[0]["m__f"]
    assert "sdfTexFree(handle);" in body
    assert "p2sdPlaySE(0);" in body
    assert "p2sdPlaySE(0, 0)" not in body
    assert "AddComponent(obj);" in body


def test_function_addresses_from_separators() -> None:
    src = [
        "//----- (0000000000FFB9B0) ----------------------------------------------------",
        "void __fastcall dds3TitleMain__dds3TitleInit(dds3TitleMain_o *this, int32_t mode)",
        "{",
        "  return;",
        "}",
        "//----- (00000000000002D0) ----------------------------------------------------",
        "int64_t __fastcall B__bar(const MethodInfo *m)",
        "{",
        "  return 0;",
        "}",
    ]
    assert hexrays.function_addresses(src) == {
        "dds3TitleMain__dds3TitleInit": 0xFFB9B0,
        "B__bar": 0x2D0,
    }


def test_collapse_hoisted_static_fields_local() -> None:
    # Hex-Rays lifts the class pointer into a local; the global must collapse the same way
    # it does for the inline `X->static_fields->G` form.
    body = """{
  struct ButtonGuide_StaticFields *v10;

  v10 = ButtonGuide->static_fields;
  startTime = v10->startTime;
  return v10->waitTime;
}"""
    out = hexrays._collapse_static_field_locals(body)
    assert "static_fields" not in out
    assert "startTime = startTime;" in out
    assert "return waitTime;" in out


def test_resolve_string_literals() -> None:
    strings = {4529: "kan", 12: 'say "hi"\n'}
    body = "  v5 = StringLiteral_4529;\n  f(StringLiteral_12);\n  g(StringLiteral_99);"
    out = hexrays._resolve_string_literals(body, strings)
    assert 'v5 = "kan";' in out
    assert 'f("say \\"hi\\"\\n");' in out       # quotes and newlines escaped
    assert "g(StringLiteral_99);" in out          # unknown index is left alone


def test_resolve_string_literals_without_metadata() -> None:
    body = "  v5 = StringLiteral_4529;"
    assert hexrays._resolve_string_literals(body, None) == body


def test_collapse_static_fields_address_of_form() -> None:
    body = "{\n  p = &v2->static_fields;\n  return p->alpha;\n}"
    out = hexrays._collapse_static_field_locals(body)
    assert "static_fields" not in out
    assert "return alpha;" in out


def test_guard_dropped_when_its_only_statement_was_scaffolding() -> None:
    # `if (...)` with no braces whose single statement is IL2CPP scaffolding: deleting the
    # statement would leave the guard covering the next line, so the guard goes too.
    fn = (
        "void __fastcall m__f(const MethodInfo *x)\n{\n"
        "  if ( (byte_3F5A20B & 1) == 0 )\n"
        "    il2cpp::InitializeMethodMetadata(0x4B58u);\n"
        "  v5 = ready();\n}\n"
    )
    bodies, _ = hexrays.clean_bodies(fn.splitlines())
    body = bodies["m__f"]
    assert "byte_3F5A20B" not in body  # guard gone with its scaffolding body
    assert "v5 = ready();" in body     # the following statement is untouched


def test_real_braceless_body_survives() -> None:
    fn = (
        "void __fastcall m__f(const MethodInfo *x)\n{\n"
        "  if ( ready )\n"
        "    v5 = 1;\n"
        "  return v5;\n}\n"
    )
    body = hexrays.clean_bodies(fn.splitlines())[0]["m__f"]
    assert "if ( ready )" in body or "if (ready)" in body
    assert "v5 = 1;" in body


def test_local_named_static_fields_does_not_eat_the_inline_form() -> None:
    # Hex-Rays often names the hoisted local `static_fields` itself. Substituting it away
    # must not also strip the inline `X->static_fields->G`, which belongs to the other pass.
    fn = (
        "void __fastcall t__Init(const MethodInfo *x)\n{\n"
        "  dds3TitleMain_TypeInfo->static_fields->MovieSkipflag = 1;\n"
        "  static_fields = v8->static_fields;\n"
        "  if ( static_fields->titleStartInitflag )\n    v = 1;\n}\n"
    )
    body = hexrays.clean_bodies(fn.splitlines())[0]["t__Init"]
    assert "MovieSkipflag = 1;" in body       # inline form -> bare global
    assert "dds3TitleMain->" not in body      # not left as a member access
    assert "titleStartInitflag" in body       # hoisted local -> bare global
    assert "static_fields" not in body


def test_unbalanced_body_falls_back_to_a_stub() -> None:
    # A strip that leaves the braces unbalanced would not parse and would swallow the rest
    # of the file, so that one case still degrades to the call-graph stub.
    fn = (
        "void __fastcall m__f(const MethodInfo *x)\n{\n"
        "  if ( v1 )\n  {\n    il2cpp::TypeInitializer(v3, x);\n"
        "  v9 = 1;\n}\n"
    )
    bodies, reasons = hexrays.clean_bodies(fn.splitlines())
    assert "m__f" not in bodies
    assert "unbalanced" in reasons["m__f"]


def test_clean_body_strips_namespace_from_type_names() -> None:
    fn = (
        "void __fastcall Project_Kernel_dds3KernelCore__Init(const MethodInfo *method)\n{\n"
        "  Project_Kernel_dds3ProcessID_t_o *p;\n"
        "  p = 0;\n"
        "  Project_Kernel_dds3KernelCore__AddProcessList(p, 0);\n}\n"
    )
    names = {"Project_Kernel_dds3KernelCore__AddProcessList": "AddProcessList"}
    clean = {"Project_Kernel_dds3ProcessID_t_o": "dds3ProcessID_t"}
    bodies, _ = hexrays.clean_bodies(
        fn.splitlines(), names, {"AddProcessList": 1}, None, lambda t: clean.get(t, t)
    )
    body = bodies["Project_Kernel_dds3KernelCore__Init"]
    assert "dds3ProcessID_t *p;" in body
    assert "AddProcessList(p);" in body


# --- class-init guards, shadowed globals, call args, array headers --------
# These body fixtures are SMT3 Hex-Rays output with names in Raidou form; test_export.py
# holds the Raidou export fixtures.

_FIXTURES = Path(__file__).parent / "fixtures"


def _clean(raw: str, names: dict[str, str] | None = None, arity: dict[str, int] | None = None) -> str:
    fn = "void __fastcall m__f(const MethodInfo *x)\n{\n" + raw.rstrip("\n") + "\n}\n"
    return hexrays.clean_bodies(fn.splitlines(), names, arity)[0]["m__f"]


def _fixture_body(name: str) -> str:
    return (_FIXTURES / f"body_{name}.c").read_text()


def test_guard_arms_keep_real_statements_and_drop_duplicate_else() -> None:
    body = _clean(_fixture_body("RunPcmKouka"))
    assert "else" not in body
    assert body.count("p2sdStatusSE_Dead(0)") == 1
    assert "return;" in body


def test_guard_arms_that_differ_keep_the_second() -> None:
    raw = (
        "  int32_t a;\n"
        "  if ( !T_TypeInfo->_2.cctor_finished )\n"
        "  {\n    il2cpp::TypeInitializer(T_TypeInfo);\n    a = 1;\n  }\n"
        "  else\n  {\n    a = 2;\n  }\n  return a;\n"
    )
    body = _clean(raw)
    assert "a = 2;" in body and "a = 1;" not in body
    assert "else" not in body


def test_guard_without_else_keeps_the_arm_body() -> None:
    raw = (
        "  int32_t a;\n"
        "  if ( !T_TypeInfo->_2.cctor_finished )\n"
        "  {\n    il2cpp::TypeInitializer(T_TypeInfo);\n    a = 1;\n  }\n  return a;\n"
    )
    assert _clean(raw) == "  s32 a;\n  a = 1;\n  return a;"


def test_shadowing_local_assigned_elsewhere_is_renamed() -> None:
    body = _clean(_fixture_body("nbCameraBoss_BSARI2_Cut1_Run"))
    assert "BSARI_Cut1_Rate = BSARI_Cut1_Rate * 0.985;" in body
    assert "BSARI_Cut1_Rate_local = BSARI_Cut1_Rate;" not in body  # dead: only read once
    raw = (
        "  float G; // s8\n  float v;\n"
        "  X_TypeInfo->static_fields->G = 1.0;\n"
        "  G = 2.0;\n  v = X_TypeInfo->static_fields->G;\n  f(G, v);\n"
    )
    out = _clean(raw)
    assert "f32 G_local;" in out and "G_local = 2.0;" in out
    assert "G = 1.0;" in out and "f(G_local, v)" in out


def test_call_arity_splits_arguments_at_top_level_commas() -> None:
    arity = {"nbSetMesMakka": 2, "COPYVECTOR": 2, "inner": 1, "outer": 1}
    raw = (
        "  nbSetMesMakka(flowmsg->m_Items[ekucyo], (*n)->requestdata, 0);\n"
        "  Project_SDF_VU0__COPYVECTOR(&(*form)->pos, basic->poseset->pos, 0);\n"
        "  outer(inner(a, 0), 0);\n"
    )
    body = _clean(raw, None, arity)
    assert "nbSetMesMakka(flowmsg[ekucyo], (*n)->requestdata);" in body
    assert "COPYVECTOR(&(*form)->pos, basic->poseset->pos);" in body
    assert "outer(inner(a));" in body


def test_array_header_indexing_and_array_locals() -> None:
    raw = (
        "  struct System_Int32_array *v5;\n"
        "  v5 = x->m_Items[i];\n"
        "  return FlagHistory->m_Items[v6]->f;\n"
    )
    body = _clean(raw)
    assert "s32 *v5;" in body
    assert "v5 = x[i];" in body
    assert "FlagHistory[v6]->f" in body


def test_static_field_uses_follow_locals() -> None:
    lines = """\
void __fastcall Project_dds3TitleMain__dds3Titlemain(const MethodInfo *method)
{
      v22 = Project_dds3KernelDraw_TypeInfo;
      v22->static_fields->dds3BackColor = 0x80000000;
      v5 = &Project_GlobalData_TypeInfo->static_fields;
      v6 = Project_GlobalData_TypeInfo->static_fields;
      x = v6->GBWK;
}
""".splitlines()
    uses = hexrays.static_field_uses(lines)
    fn = "Project_dds3TitleMain__dds3Titlemain"
    assert (fn, "Project_dds3KernelDraw", "dds3BackColor") in uses
    assert (fn, "Project_GlobalData", "GBWK") in uses


# --- pointer levels dropped from `X_o **` parameters ----------------------

_KOUKA_SIG = (
    "void __fastcall Project_nbKoukaProcess__RunPcmKouka(\n"
    "        Project_nbKoukaProcessData_t_o **k,\n"
    "        Project_nbKoukaPacket_t_o **p,\n"
    "        const MethodInfo *method)"
)
_CAMERA_SIG = (
    "int32_t __fastcall Project_nbCameraBoss__nbCameraBoss_BSARI2_Cut1_Run(\n"
    "        Project_nbCamera_t_o **pNbCamera,\n"
    "        const MethodInfo *method)"
)


def _strip_ns(token: str) -> str:
    return token.removeprefix("Project_")


def _clean_sig(sig: str, name: str, slots: dict[str, tuple[bool, ...]] | None = None) -> str:
    fn = sig + "\n{\n" + _fixture_body(name).rstrip("\n") + "\n}\n"
    bodies = hexrays.clean_bodies(fn.splitlines(), None, None, None, _strip_ns, slots)[0]
    return bodies[sig.split("(")[0].split()[-1]]


def test_plain_ctype() -> None:
    assert hexrays.plain_ctype("Project_X_o **") == ("Project_X", 1, True)
    assert hexrays.plain_ctype("Il2CppObject **") == ("void", 1, True)
    assert hexrays.plain_ctype("System_String_o **") == ("char", 2, False)
    assert hexrays.plain_ctype("System_Int16_array *") == ("s16", 1, False)
    assert hexrays.plain_ctype("UnityEngine_Vector4_o") == ("const sdfVector4_t", 1, False)


def test_dropped_param_loses_deref() -> None:
    body = _clean_sig(_KOUKA_SIG, "RunPcmKouka")
    assert "(*k)" not in body and "(*p)" not in body
    assert "k->data->flag" in body and "p->type == 36" in body
    assert "i = p->data1->i" in body


def test_camera_body_agrees_with_prototype() -> None:
    slots = {"effBTLModelGetMarkPosition2": (True, False)}
    body = _clean_sig(_CAMERA_SIG, "nbCameraBoss_BSARI2_Cut1_Run", slots)
    assert "&pNbCamera->target" in body and "(*pNbCamera)" not in body
    assert "v6 = pNbCamera;" in body
    assert "effBTLModelGetMarkPosition2(pFormation, 1u" in body
    assert "_o " not in body and "nbFormation_t *pFormation" in body
    assert "  nbCamera_t *v6;" in body


def test_deref_and_address_args() -> None:
    b = hexrays.deref_dropped("g(p, (*p)->a, *p, a * p);", ["p"])
    assert b == "g(p, p->a, p, a * p);"
    assert hexrays.deref_dropped("Init(*p);", ["p"]) == "Init(p);"
    assert hexrays.drop_address_args("f(&x, &y, &z->q);", {"f": (True, False, True)}) == (
        "f(x, &y, &z->q);"
    )


def test_unity_math_param_is_used_through_the_pointer() -> None:
    fn = (
        "void __fastcall Project_m__f(UnityEngine_Vector4_o pos, const MethodInfo *method)\n{\n"
        "  float x;\n  x = pos.fields.x + pos.fields.y;\n  g(x);\n}\n"
    )
    body = hexrays.clean_bodies(fn.splitlines())[0]["Project_m__f"]
    assert "x = pos->x + pos->y;" in body
