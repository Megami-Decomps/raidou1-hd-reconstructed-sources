"""Hex-Rays "Show casts" output; snippets from the SMT3 HD export, renamed to Raidou's style."""
# pyright: reportPrivateUsage=false

from __future__ import annotations

from raidou import hexrays
from raidou.casts import declared_types, fold_accessors, shorten_int_literals, strip_casts


def _strip_ns(token: str) -> str:
    return token.removeprefix("Project_")


def _strip(body: str, params: list[tuple[str, str]] | None = None) -> str:
    return strip_casts(body, declared_types(body, params))


def test_deref_casts_keep_the_access_width() -> None:
    body = "  *((_DWORD *)v5 + 6) = aMinor;\n  v7 = *(_QWORD *)(p_image[23] + 40LL);\n"
    assert _strip(body) == body


def test_cast_restating_a_declared_type_is_dropped() -> None:
    body = "  _DWORD *v9; // x21\n  _DWORD *v5; // x0\n\n  *((_DWORD *)v9 + 6) = *(_DWORD *)v5;\n"
    out = _strip(body)
    assert "*(v9 + 6) = *v5;" in out or "*((_DWORD *)v9 + 6)" not in out
    assert "(_DWORD *)v5" not in out and "(_DWORD *)v9" not in out


def test_pointer_and_wide_casts_in_calls_and_assignments_are_dropped() -> None:
    body = (
        "  v5 = j_il2cpp::Allocate((unsigned __int64)Project_mdlLoadingTag_t_TypeInfo);\n"
        "  System_Object___ctor((Il2CppObject *)v5, 0);\n"
        "  Il2CppExceptionWrapper::ctor((__int64)v8, 0, 0);\n"
        "  v3 = (Il2CppObject *)System_String__Concat((System_String_o *)StringLiteral_4528, v2, 0);\n"
    )
    out = _strip(body)
    assert "Allocate(Project_mdlLoadingTag_t_TypeInfo)" in out
    assert "ctor(v5, 0)" in out and "ctor(v8, 0, 0)" in out
    assert "v3 = System_String__Concat(StringLiteral_4528, v2, 0);" in out


def test_width_changing_casts_stay() -> None:
    body = (
        "  if ( (unsigned int)SP >= LODWORD(StackType->max_length) )\n"
        "    v53 = (float)vmovl_s16(v48).n128_i32[0] * 0.5;\n"
        "  *(_QWORD *)&v5->prevcommand = 0xFFFFFFFF00000000LL;\n"
    )
    assert _strip(body) == body


def test_function_pointer_call_casts_are_dropped() -> None:
    body = (
        "  v3 = (char *)((__int64 (__fastcall *)(char *, const MethodInfo *))"
        "id->klass->vtable._3_ToString.methodPtr)(id, id->klass->vtable._3_ToString.method);\n"
    )
    out = _strip(body)
    assert "__fastcall" not in out
    assert out.startswith("  v3 = (id->klass->vtable._3_ToString.methodPtr)(id, ")


def test_nested_casts_drop_together() -> None:
    assert _strip("  f((unsigned __int64)(char *)x);\n") == "  f(x);\n"


def test_assignment_to_a_declared_pointer_drops_the_class_cast() -> None:
    body = "  Foo_o *v3; // x0\n\n  v3 = (Foo_o *)sub_8DB0C0(a, 0);\n  this->Blur = (Bar_o *)v3;\n"
    out = _strip(body)
    assert "v3 = sub_8DB0C0(a, 0);" in out
    assert "this->Blur = (Bar_o *)v3;" in out


def test_vector_accessors_fold_to_members() -> None:
    body = (
        "  Item_impl = UnityEngine_Vector3__get_Item_impl(&v118, 0);\n"
        "  UnityEngine_Vector4__set_Item_impl(&v22, 3, Item_impl + (float)(v10 * 950.0));\n"
        "  return 1.0 / UnityEngine_Matrix4x4__get_Item_impl(&v5, 0, 2);\n"
        "  UnityEngine_Matrix4x4__set_Item_impl(p, 1, 2, 4.0);\n"
    )
    out = fold_accessors(body)
    assert "Item_impl = v118.x;" in out
    assert "v22.w = Item_impl + (float)(v10 * 950.0);" in out
    assert "1.0 / v5.m02;" in out
    assert "p->m12 = 4.0;" in out


def test_vector_accessors_with_variable_index_or_odd_place_stay() -> None:
    body = (
        "  UnityEngine_Vector2__set_Item_impl(\n"
        "    (UnityEngine_Vector2_o *)&this->fields.m_TotalMinSize.fields.y, 0, v12);\n"
        "  x = UnityEngine_Vector2__get_Item_impl(&v, axis);\n"
        "  y = UnityEngine_Vector2__get_Item_impl(&v, 2);\n"
    )
    assert fold_accessors(body) == body


def test_long_long_suffix_dropped_only_when_it_fits() -> None:
    assert shorten_int_literals("a[8LL * i + 32LL] = 0xFFFFFFFF00000000LL;") == (
        "a[8 * i + 32] = 0xFFFFFFFF00000000LL;"
    )
    assert shorten_int_literals("x = 0x2AuLL;") == "x = 0x2Au;"


def test_clean_body_with_casts_matches_the_old_export() -> None:
    raw = (
        "  _DWORD *v9; // x21\n  unsigned __int64 *v5; // x20\n\n"
        "  v5 = j_il2cpp::Allocate((unsigned __int64)Project_mdlLoadingTag_t_TypeInfo);\n"
        "  *((_DWORD *)v5 + 6) = aMinor;\n"
        "  v9 = *(_DWORD **)(p_image[23] + 40LL);\n"
        "  Il2CppExceptionWrapper::ctor((__int64)v5, 0, 0);\n"
        '  Log((Il2CppObject *)StringLiteral_4527, 0);\n'
    )
    out = hexrays._clean_body(
        raw, strings={4527: "Achievement#Initialize"}, type_name=_strip_ns
    )
    assert "Allocate(mdlLoadingTag_t)" in out
    assert "*((u32 *)v5 + 6) = aMinor;" in out
    assert "v9 = *(u32 **)(p_image[23] + 40);" in out
    assert 'Log("Achievement#Initialize", 0);' in out
    assert "Exception" not in out


def test_float_exponents_are_written_out() -> None:
    from raidou.casts import expand_exponents

    assert expand_exponents("sub(&v22, -2e+01, 1.5e-05, 1e+20, 6.0);") == (
        "sub(&v22, -20.0, 0.000015, 1e+20, 6.0);"
    )


def test_wrapped_statements_are_joined() -> None:
    from raidou.casts import join_wrapped

    raw = "  if ( a(1, 0)\n    && !b(2, 0) )\n  {\n    f(x,\n      y);\n  }"
    assert join_wrapped(raw) == "  if ( a(1, 0) && !b(2, 0) )\n  {\n    f(x, y);\n  }"
    assert join_wrapped("  g(\n    x);") == "  g(x);"


def test_pointer_casts_in_comparisons_are_dropped() -> None:
    body = "  if ( (Foo_c *)klass->hierarchy[d - 1] != Foo_t )\n"
    assert _strip(body) == "  if ( klass->hierarchy[d - 1] != Foo_t )\n"


def test_trailing_orphan_label_and_stale_method_info_arg_are_dropped() -> None:
    out = hexrays._clean_body("  if ( !p )\n    return;\nLABEL_10:\n")
    assert "LABEL_10" not in out
    fixed = hexrays._fix_call_arity(
        "x = PopInt(pwork, *(const MethodInfo **)&type);", {"PopInt": 1}
    )
    assert fixed == "x = PopInt(pwork);"


def test_array_sizes_see_through_casts() -> None:
    lines = [
        "void __fastcall X__ctor(Project_dds3UnitStatus_t_o *this, const MethodInfo *method)",
        "{",
        "  v5 = (struct System_Byte_array *)il2cpp::NewSpecific((__int64)byte___TypeInfo, 4u);",
        "  this->fields.rpoints = (struct System_Byte_array *)v5;",
        "  beast_aisyo_TypeInfo->static_fields->tbl = (struct System_Byte_array *)il2cpp::NewSpecific(",
        "    (__int64)byte___TypeInfo,",
        "    0xDD1uLL);",
        "}",
    ]
    s = hexrays.array_sizes(lines)
    assert s[("Project_dds3UnitStatus_t", "rpoints")] == (4, True)
    assert s[("beast_aisyo", "tbl")] == (0xDD1, True)


def test_array_store_covariance_check_is_dropped() -> None:
    raw = (
        "  __int64 *Interface; // x0\n\n"
        "  v7 = (System_Object_array *)il2cpp::NewSpecific((__int64)object___TypeInfo, 4u);\n"
        "  Interface = (__int64 *)StringLiteral_22112;\n"
        "  if ( StringLiteral_22112 )\n"
        "  {\n"
        "    Interface = il2cpp::QueryInterface((__int64 *)StringLiteral_22112, "
        "(__int64)v7->obj.klass->_1.element_class);\n"
        "    if ( !Interface )\n"
        "    {\n"
        "      v37 = il2cpp::ThrowArrayTypeMismatchException(0);\n"
        "      Il2CppExceptionWrapper::ctor((__int64)v37, 0, 0);\n"
        "    }\n"
        "  }\n"
        "  v7->m_Items[0] = StringLiteral_22112;\n"
    )
    out = hexrays._clean_body(raw)
    assert "Interface" not in out and "if (" not in out
    assert "v7[0] = StringLiteral_22112;" in out


def test_single_statement_cast_check_block_is_dropped() -> None:
    raw = (
        "  if ( v23 )\n  {\n    v23 = il2cpp::QueryInterface(v23, *(_QWORD *)(*(_QWORD *)blendpow + 64LL));\n"
        "    if ( !v23 )\n    {\n      Il2CppExceptionWrapper::ctor((__int64)v9, 0, 0);\n    }\n  }\n"
        "  blendpow[1] = v24;\n"
    )
    assert hexrays._clean_body(raw) == "  blendpow[1] = v24;"
