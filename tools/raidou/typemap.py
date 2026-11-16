"""Type tables shared by the dump reader and the Hex-Rays body cleaner."""

from __future__ import annotations

import re

# C primitives already present verbatim in the dump.
PRIMITIVE = re.compile(
    r"^(?:u?int(?:8|16|32|64)_t|u?intptr_t|size_t|float|double|bool|char|void)$"
)

# System.* value types -> decomp-friendly C (s8/u32/f32/..., see types.h).
# System_String/_Object resolve through their pointer.
IL2CPP_TYPE_TO_DECOMP_TYPE: dict[str, str] = {
    "System_SByte": "s8",
    "System_Byte": "u8",
    "System_Int16": "s16",
    "System_UInt16": "u16",
    "System_Int32": "s32",
    "System_UInt32": "u32",
    "System_Int64": "s64",
    "System_UInt64": "u64",
    "System_Single": "f32",
    "System_Double": "f64",
    "System_Boolean": "bool",
    "System_Char": "u16",
    "System_IntPtr": "intptr_t",
    "System_UIntPtr": "uintptr_t",
    "System_String": "char",  # a string reference is char*; the member's own * remains
    "System_Object": "void",
    "Il2CppObject": "void",
}

# Fixed-width C primitives already in the dump -> the same decomp aliases.
STDINT_TYPE_TO_DECOMP_TYPE: dict[str, str] = {
    "int8_t": "s8", "uint8_t": "u8",
    "int16_t": "s16", "uint16_t": "u16",
    "int32_t": "s32", "uint32_t": "u32",
    "int64_t": "s64", "uint64_t": "u64",
    "float": "f32", "double": "f64",
}

# The port replaced the game's math types with UnityEngine ones; map them back to inferred
# original sdf names (concrete typedefs in types.h). Best-guess reconstructions.
UNITY_TO_SDF_TYPE: dict[str, str] = {
    "UnityEngine_Vector2": "sdfVector2_t",
    "UnityEngine_Vector3": "sdfVector3_t",
    "UnityEngine_Vector4": "sdfVector4_t",
    "UnityEngine_Quaternion": "sdfQuaternion_t",
    "UnityEngine_Matrix4x4": "sdfMatrix4_t",
    "UnityEngine_Color": "sdfColor_t",
    "UnityEngine_Color32": "sdfColor32_t",
}

# IL2CPP array element TypeInfo names that are value types (stored inline); the rest are
# reference types (arrays of pointers). Distinguishes `elem name[N]` from `elem *name[N]`.
VALUE_TYPES: frozenset[str] = frozenset(
    {
        "byte", "sbyte", "short", "ushort", "int", "uint", "long", "ulong",
        "char", "float", "double", "bool", "intptr", "uintptr",
        "UnityEngine_Vector2", "UnityEngine_Vector3", "UnityEngine_Vector4",
        "UnityEngine_Quaternion", "UnityEngine_Matrix4x4",
        "UnityEngine_Color", "UnityEngine_Color32",
    }
)

# Names types.h defines concretely. A real `_H_` type with one of these names (e.g.
# libsdf's sdfMatrix4_t, which wraps the Unity matrix) is skipped to avoid a duplicate
# definition, and such names are never forward-declared.
MATH_PROVIDED: frozenset[str] = frozenset(UNITY_TO_SDF_TYPE.values())

COMMON_HEADER = "types.h"

COMMON_BODY = """\
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

#define UNKNOWN_ARRAY_SIZE 1
#define UNKNOWN_DEFINE_VALUE 0

typedef struct { f32 x, y; } sdfVector2_t;
typedef struct { f32 x, y, z; } sdfVector3_t;
typedef struct { f32 x, y, z, w; } sdfVector4_t;
typedef struct { f32 x, y, z, w; } sdfQuaternion_t;
typedef struct { f32 m[16]; } sdfMatrix4_t;
typedef struct { f32 r, g, b, a; } sdfColor_t;
typedef struct { u8 r, g, b, a; } sdfColor32_t;
"""


def pointer_depth(
    text: str, stars: int, arrays: int, *, obj: bool = False, param: bool = False
) -> tuple[str, int]:
    """``(text, pointer depth)``. An `_array` level is one pointer. For a parameter, an object
    (``obj``: ``T_o``, ``Il2CppObject``) by reference is ``T *``, a Unity math value ``const T *``.
    """
    if arrays:
        return text, max(stars, 1) + arrays - 1
    if param and stars == 0 and obj and text in MATH_PROVIDED:
        return f"const {text}", 1
    if param and stars == 2 and obj and text != "char":
        return text, 1
    return text, stars
