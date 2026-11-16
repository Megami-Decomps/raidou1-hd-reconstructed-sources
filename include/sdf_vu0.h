#pragma once
#include "types.h"

#define colorRatio128 0.0078125
#define colorRatio255 0.003921569

extern sdfVector4_t vf00;
extern sdfVector4_t vct_A;
extern sdfVector4_t vct_B;
extern sdfVector4_t vct_C;
extern sdfMatrix4_t mtx_A;
extern sdfMatrix4_t mtx_B;
extern sdfMatrix4_t mtx_C;

// macros
// 0x226a000: void LOADMATRIX(sdfMatrix4_t *aMatrix)
#define LOADMATRIX(aMatrix) do { \
    _OWORD *p_x; \
    __int128 v5; \
    __int128 v6; \
    __int128 v7; \
    __int128 v8; \
    v5 = *(_OWORD *)&aMatrix->m00; \
    v6 = *(_OWORD *)&aMatrix->m01; \
    v7 = *(_OWORD *)&aMatrix->m02; \
    v8 = *(_OWORD *)&aMatrix->m03; \
    p_x = &vf00.x; \
    p_x[4] = v5; \
    p_x[5] = v6; \
    p_x[6] = v7; \
    p_x[7] = v8; \
} while (0)

// 0x226a090: void STOREMATRIX(sdfMatrix4_t *aMatrix)
#define STOREMATRIX(aMatrix) do { \
    _OWORD *p_x; \
    __int128 v5; \
    __int128 v6; \
    __int128 v7; \
    p_x = &vf00.x; \
    v5 = p_x[5]; \
    v6 = p_x[6]; \
    v7 = p_x[7]; \
    *(_OWORD *)&aMatrix->m00 = p_x[4]; \
    *(_OWORD *)&aMatrix->m01 = v5; \
    *(_OWORD *)&aMatrix->m02 = v6; \
    *(_OWORD *)&aMatrix->m03 = v7; \
} while (0)

// 0x226a110: void LOADMATRIX_B(sdfMatrix4_t *aMatrix)
#define LOADMATRIX_B(aMatrix) do { \
    _OWORD *p_x; \
    __int128 v5; \
    __int128 v6; \
    __int128 v7; \
    __int128 v8; \
    v5 = *(_OWORD *)&aMatrix->m00; \
    v6 = *(_OWORD *)&aMatrix->m01; \
    v7 = *(_OWORD *)&aMatrix->m02; \
    v8 = *(_OWORD *)&aMatrix->m03; \
    p_x = &vf00.x; \
    p_x[8] = v5; \
    p_x[9] = v6; \
    p_x[10] = v7; \
    p_x[11] = v8; \
} while (0)

// 0x226a1a0: void STOREMATRIX_B(sdfMatrix4_t *aMatrix)
#define STOREMATRIX_B(aMatrix) do { \
    _OWORD *p_x; \
    __int128 v5; \
    __int128 v6; \
    __int128 v7; \
    p_x = &vf00.x; \
    v5 = p_x[9]; \
    v6 = p_x[10]; \
    v7 = p_x[11]; \
    *(_OWORD *)&aMatrix->m00 = p_x[8]; \
    *(_OWORD *)&aMatrix->m01 = v5; \
    *(_OWORD *)&aMatrix->m02 = v6; \
    *(_OWORD *)&aMatrix->m03 = v7; \
} while (0)

// 0x226a220: void LOADMATRIX_C(sdfMatrix4_t *aMatrix)
#define LOADMATRIX_C(aMatrix) do { \
    _OWORD *p_x; \
    __int128 v5; \
    __int128 v6; \
    __int128 v7; \
    __int128 v8; \
    v5 = *(_OWORD *)&aMatrix->m00; \
    v6 = *(_OWORD *)&aMatrix->m01; \
    v7 = *(_OWORD *)&aMatrix->m02; \
    v8 = *(_OWORD *)&aMatrix->m03; \
    p_x = &vf00.x; \
    p_x[12] = v5; \
    p_x[13] = v6; \
    p_x[14] = v7; \
    p_x[15] = v8; \
} while (0)

// 0x226a2b0: void STOREMATRIX_C(sdfMatrix4_t *aMatrix)
#define STOREMATRIX_C(aMatrix) do { \
    _OWORD *p_x; \
    __int128 v5; \
    __int128 v6; \
    __int128 v7; \
    p_x = &vf00.x; \
    v5 = p_x[13]; \
    v6 = p_x[14]; \
    v7 = p_x[15]; \
    *(_OWORD *)&aMatrix->m00 = p_x[12]; \
    *(_OWORD *)&aMatrix->m01 = v5; \
    *(_OWORD *)&aMatrix->m02 = v6; \
    *(_OWORD *)&aMatrix->m03 = v7; \
} while (0)

// 0x226a330: void COPYMATRIX_A_TO_B(void)
#define COPYMATRIX_A_TO_B() do { \
    _OWORD *p_x; \
    __int128 v3; \
    __int128 v4; \
    p_x = &vf00.x; \
    v3 = p_x[5]; \
    p_x[8] = p_x[4]; \
    p_x[9] = v3; \
    v4 = p_x[7]; \
    p_x[10] = p_x[6]; \
    p_x[11] = v4; \
} while (0)

// 0x226a3a0: void COPYMATRIX_A_TO_C(void)
#define COPYMATRIX_A_TO_C() do { \
    _OWORD *p_x; \
    __int128 v3; \
    __int128 v4; \
    p_x = &vf00.x; \
    v3 = p_x[5]; \
    p_x[12] = p_x[4]; \
    p_x[13] = v3; \
    v4 = p_x[7]; \
    p_x[14] = p_x[6]; \
    p_x[15] = v4; \
} while (0)

// 0x226a410: void COPYMATRIX_B_TO_A(void)
#define COPYMATRIX_B_TO_A() do { \
    _OWORD *p_x; \
    __int128 v3; \
    __int128 v4; \
    p_x = &vf00.x; \
    v3 = p_x[9]; \
    p_x[4] = p_x[8]; \
    p_x[5] = v3; \
    v4 = p_x[11]; \
    p_x[6] = p_x[10]; \
    p_x[7] = v4; \
} while (0)

// 0x226a480: void COPYMATRIX_B_TO_C(void)
#define COPYMATRIX_B_TO_C() do { \
    _OWORD *p_x; \
    __int128 v3; \
    __int128 v4; \
    p_x = &vf00.x; \
    v3 = p_x[5]; \
    p_x[12] = p_x[4]; \
    p_x[13] = v3; \
    v4 = p_x[7]; \
    p_x[14] = p_x[6]; \
    p_x[15] = v4; \
} while (0)

// 0x226a4f0: void COPYMATRIX_C_TO_A(void)
#define COPYMATRIX_C_TO_A() do { \
    _OWORD *p_x; \
    __int128 v3; \
    __int128 v4; \
    p_x = &vf00.x; \
    v3 = p_x[13]; \
    p_x[4] = p_x[12]; \
    p_x[5] = v3; \
    v4 = p_x[15]; \
    p_x[6] = p_x[14]; \
    p_x[7] = v4; \
} while (0)

// 0x226a560: void COPYMATRIX_C_TO_B(void)
#define COPYMATRIX_C_TO_B() do { \
    _OWORD *p_x; \
    __int128 v3; \
    __int128 v4; \
    p_x = &vf00.x; \
    v3 = p_x[13]; \
    p_x[8] = p_x[12]; \
    p_x[9] = v3; \
    v4 = p_x[15]; \
    p_x[10] = p_x[14]; \
    p_x[11] = v4; \
} while (0)

// 0x226a5d0: void LOADIDENTITY(void)
#define LOADIDENTITY() do { \
    mtx_A = identityMatrix; \
} while (0)

// 0x226a680: void LOADIDENTITY_B(void)
#define LOADIDENTITY_B() do { \
    mtx_B = identityMatrix; \
} while (0)

// 0x226a730: void STOREIDENTITY(sdfMatrix4_t *aMatrix)
#define STOREIDENTITY(aMatrix) do { \
    __int128 v4; \
    __int128 v5; \
    __int128 v6; \
    v4 = *(_OWORD *)&identityMatrix.m01; \
    v5 = *(_OWORD *)&identityMatrix.m02; \
    v6 = *(_OWORD *)&identityMatrix.m03; \
    *(_OWORD *)&aMatrix->m00 = *(_OWORD *)&identityMatrix.m00; \
    *(_OWORD *)&aMatrix->m01 = v4; \
    *(_OWORD *)&aMatrix->m02 = v5; \
    *(_OWORD *)&aMatrix->m03 = v6; \
} while (0)

// 0x226a790: void TRANSLATE(void)
#define TRANSLATE() do { \
    sdfMatrix4_t v2; \
    sdfMatrix4_t v3; \
    sdfVector4_t v5; \
    get_transpose(&v3, &mtx_A, 0); \
    v2 = v3; \
    v5 = op_Multiply_60923920(&v2, vct_A, 0); \
    SetRow(&mtx_A, 3, v5, 0); \
} while (0)

// 0x226a850: void TRANSLATE_XYZ(void)
#define TRANSLATE_XYZ() do { \
    f32 x; \
    f32 y; \
    f32 z; \
    sdfMatrix4_t v6; \
    sdfMatrix4_t v7; \
    sdfVector4_t v8; \
    sdfVector4_t v9; \
    x = vct_A.x; \
    y = vct_A.y; \
    z = vct_A.z; \
    get_transpose(&v7, &mtx_A, 0); \
    v8.w = 1.0; \
    v8.z = z; \
    v6 = v7; \
    v8.x = x; \
    v8.y = y; \
    v9 = op_Multiply_60923920(&v6, v8, 0); \
    SetRow(&mtx_A, 3, v9, 0); \
} while (0)

// 0x226a920: void TRANSMATRIX(void)
#define TRANSMATRIX() do { \
    sdfMatrix4_t *p_mtx_A; \
    f32 Item_60922080; \
    sdfMatrix4_t *v4; \
    f32 v5; \
    sdfMatrix4_t *v6; \
    f32 v7; \
    p_mtx_A = &mtx_A; \
    Item_60922080 = get_Item_60922080(p_mtx_A, 3, 0); \
    set_Item_60922352(p_mtx_A, 3, Item_60922080 + vct_A.x, 0); \
    v4 = &mtx_A; \
    v5 = get_Item_60922080(v4, 7, 0); \
    set_Item_60922352(v4, 7, v5 + vct_A.y, 0); \
    v6 = &mtx_A; \
    v7 = get_Item_60922080(v6, 11, 0); \
    set_Item_60922352(v6, 11, v7 + vct_A.z, 0); \
} while (0)

// 0x226aa30: void SCALE(void)
#define SCALE() do { \
    f32 w; \
    sdfVector4_t Row; \
    sdfVector4_t v4; \
    sub_197D730(0); \
    Row = GetRow(&mtx_A, 3, 0); \
    w = vct_A.w; \
    v4.x = Row.x * w; \
    v4.y = Row.y * w; \
    v4.z = Row.z * w; \
    v4.w = Row.w * w; \
    SetRow(&mtx_A, 3, v4, 0); \
} while (0)

// 0x226aad0: void SCALE_XYZ(void)
#define SCALE_XYZ() do { \
    f32 x; \
    f32 y; \
    f32 z; \
    sdfVector4_t Row; \
    sdfVector4_t v9; \
    sdfVector4_t v10; \
    sdfVector4_t v11; \
    sdfVector4_t v12; \
    sdfVector4_t v13; \
    Row = GetRow(&mtx_A, 0, 0); \
    x = vct_A.x; \
    v11.x = Row.x * x; \
    v11.y = Row.y * x; \
    v11.z = Row.z * x; \
    v11.w = Row.w * x; \
    SetRow(&mtx_A, 0, v11, 0); \
    v9 = GetRow(&mtx_A, 1, 0); \
    y = vct_A.y; \
    v12.x = v9.x * y; \
    v12.y = v9.y * y; \
    v12.z = v9.z * y; \
    v12.w = v9.w * y; \
    SetRow(&mtx_A, 1, v12, 0); \
    v10 = GetRow(&mtx_A, 2, 0); \
    z = vct_A.z; \
    v13.x = v10.x * z; \
    v13.y = v10.y * z; \
    v13.z = v10.z * z; \
    v13.w = v10.w * z; \
    SetRow(&mtx_A, 2, v13, 0); \
} while (0)

// 0x226abf0: void SCALE_XYZ_REV(void)
#define SCALE_XYZ_REV() do { \
    sdfMatrix4_t *static_fields; \
    f32 m01; \
    f32 m11; \
    f32 m21; \
    sdfVector4_t Row; \
    sdfVector4_t v7; \
    sdfVector4_t v8; \
    sdfVector4_t v9; \
    sdfVector4_t v10; \
    sdfVector4_t v11; \
    Row = GetRow(static_fields + 1, 0, 0); \
    v9.w = Row.w; \
    v9.x = m01 * Row.x; \
    v9.y = m11 * Row.y; \
    v9.z = m21 * Row.z; \
    SetRow(&mtx_A, 0, v9, 0); \
    v7 = GetRow(&mtx_A, 1, 0); \
    v10.w = v7.w; \
    v10.x = m01 * v7.x; \
    v10.y = m11 * v7.y; \
    v10.z = m21 * v7.z; \
    SetRow(&mtx_A, 1, v10, 0); \
    v8 = GetRow(&mtx_A, 2, 0); \
    v11.w = v8.w; \
    v11.x = m01 * v8.x; \
    v11.z = m21 * v8.z; \
    v11.y = m11 * v8.y; \
    SetRow(&mtx_A, 2, v11, 0); \
} while (0)

// 0x226ad10: void LOADVECTOR(const sdfVector4_t *p)
#define LOADVECTOR(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    f32 *p_x; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    p_x = &vf00.x; \
    p_x[6] = z; \
    p_x[7] = w; \
    p_x[4] = x; \
    p_x[5] = y; \
} while (0)

// 0x226ada0: void STOREVECTOR(sdfVector4_t *p)
#define STOREVECTOR(p) do { \
    *p = vct_A; \
} while (0)

// 0x226ae10: void LOADVECTOR_B(const sdfVector4_t *p)
#define LOADVECTOR_B(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    f32 *p_x; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    p_x = &vf00.x; \
    p_x[10] = z; \
    p_x[11] = w; \
    p_x[8] = x; \
    p_x[9] = y; \
} while (0)

// 0x226aea0: void STOREVECTOR_B(sdfVector4_t *p)
#define STOREVECTOR_B(p) do { \
    *p = vct_B; \
} while (0)

// 0x226af10: void LOADVECTOR_C(const sdfVector4_t *p)
#define LOADVECTOR_C(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    f32 *p_x; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    p_x = &vf00.x; \
    p_x[14] = z; \
    p_x[15] = w; \
    p_x[12] = x; \
    p_x[13] = y; \
} while (0)

// 0x226afa0: void STOREVECTOR_C(sdfVector4_t *p)
#define STOREVECTOR_C(p) do { \
    *p = vct_C; \
} while (0)

// 0x226b010: void LOADIDENTITYVECTOR(void)
static inline void LOADIDENTITYVECTOR(void) {
  vct_A = vf00;
  return;
}

// 0x226b0a0: void LOADIDENTITYVECTOR_B(void)
static inline void LOADIDENTITYVECTOR_B(void) {
  vct_A = vf00;
  return;
}

// 0x226b130: void LOADIDENTITYVECTOR_C(void)
static inline void LOADIDENTITYVECTOR_C(void) {
  vct_A = vf00;
  return;
}

// 0x226b1c0: void STOREIDENTITYVECTOR(sdfVector4_t *p)
#define STOREIDENTITYVECTOR(p) do { \
    *p = vf00; \
} while (0)

// 0x226b230: void VECTOR_W_SET_ONE(void)
static inline void VECTOR_W_SET_ONE(void) {
  vct_A.w = 1.0;
  return;
}

// 0x226b2c0: void VECTOR_W_SET_ZERO(void)
static inline void VECTOR_W_SET_ZERO(void) {
  vct_A.w = 0.0;
  return;
}

// 0x226b340: f32 GETVECTOR_X(void)
#define GETVECTOR_X() (vct_A.x)

// 0x226b3c0: f32 GETVECTOR_Y(void)
#define GETVECTOR_Y() (vct_A.y)

// 0x226b440: f32 GETVECTOR_Z(void)
#define GETVECTOR_Z() (vct_A.z)

// 0x226b4c0: f32 GETVECTOR_W(void)
#define GETVECTOR_W() (vct_A.w)

// 0x226b540: void SETVECTOR_X(f32 v)
static inline void SETVECTOR_X(f32 v) {
  vct_A.x = v;
  return;
}

// 0x226b5d0: void SETVECTOR_Y(f32 v)
static inline void SETVECTOR_Y(f32 v) {
  vct_A.y = v;
  return;
}

// 0x226b660: void SETVECTOR_Z(f32 v)
static inline void SETVECTOR_Z(f32 v) {
  vct_A.z = v;
  return;
}

// 0x226b6f0: void SETVECTOR_W(f32 v)
static inline void SETVECTOR_W(f32 v) {
  vct_A.w = v;
  return;
}

// 0x226b780: void LOADVECTOR_XYZ(const sdfVector4_t *p)
#define LOADVECTOR_XYZ(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    f32 *p_x; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    p_x = &vf00.x; \
    p_x[4] = x; \
    p_x[5] = y; \
    p_x[6] = z; \
    p_x[7] = w; \
    vct_A.w = 0.0; \
} while (0)

// 0x226b810: void LOADVECTOR_XYZ_B(const sdfVector4_t *p)
#define LOADVECTOR_XYZ_B(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    f32 *p_x; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    p_x = &vf00.x; \
    p_x[8] = x; \
    p_x[9] = y; \
    p_x[10] = z; \
    p_x[11] = w; \
    vct_B.w = 0.0; \
} while (0)

// 0x226b8a0: void LOADVECTOR_UNALIGN(const sdfVector4_t *p)
#define LOADVECTOR_UNALIGN(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    f32 *p_x; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    p_x = &vf00.x; \
    p_x[6] = z; \
    p_x[7] = w; \
    p_x[4] = x; \
    p_x[5] = y; \
} while (0)

// 0x226b930: void LOADVECTOR_UNALIGN_B(const sdfVector4_t *p)
#define LOADVECTOR_UNALIGN_B(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    f32 *p_x; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    p_x = &vf00.x; \
    p_x[10] = z; \
    p_x[11] = w; \
    p_x[8] = x; \
    p_x[9] = y; \
} while (0)

// 0x226b9c0: void LOADSHORTVECTOR(s32 p)
#define LOADSHORTVECTOR(p) do { \
    ; \
} while (0)

// 0x226b9d0: void LOADSHORTVECTOR_B(s32 p)
#define LOADSHORTVECTOR_B(p) do { \
    ; \
} while (0)

// 0x226b9e0: void LOADVECTOR_MTXCOL(const sdfMatrix4_t *p, s32 index)
#define LOADVECTOR_MTXCOL(p, index) do { \
    sdfVector4_t Column; \
    Column = GetColumn(p, index, 0); \
    vct_A = Column; \
} while (0)

// 0x226ba80: void LOADVECTOR_MTXCOL_B(const sdfMatrix4_t *p, s32 index)
#define LOADVECTOR_MTXCOL_B(p, index) do { \
    sdfVector4_t Column; \
    Column = GetColumn(p, index, 0); \
    vct_B = Column; \
} while (0)

// 0x226bb20: void ITOF0(void)
#define ITOF0() do { \
    ; \
} while (0)

// 0x226bb30: void ITOF0_B(void)
#define ITOF0_B() do { \
    ; \
} while (0)

// 0x226bb40: void ITOF4(void)
#define ITOF4() do { \
    ; \
} while (0)

// 0x226bb50: void ITOF4_B(void)
#define ITOF4_B() do { \
    ; \
} while (0)

// 0x226bb60: void ITOF12(void)
#define ITOF12() do { \
    ; \
} while (0)

// 0x226bb70: void ITOF12_B(void)
#define ITOF12_B() do { \
    ; \
} while (0)

// 0x226bb80: void ITOF15(void)
#define ITOF15() do { \
    ; \
} while (0)

// 0x226bb90: void ITOF15_B(void)
#define ITOF15_B() do { \
    ; \
} while (0)

// 0x226bba0: void FTOI0(void)
#define FTOI0() do { \
    ; \
} while (0)

// 0x226bbb0: void FTOI0_B(void)
#define FTOI0_B() do { \
    ; \
} while (0)

// 0x226bbc0: void FTOI4(void)
#define FTOI4() do { \
    ; \
} while (0)

// 0x226bbd0: void FTOI4_B(void)
#define FTOI4_B() do { \
    ; \
} while (0)

// 0x226bbe0: void FTOI12(void)
#define FTOI12() do { \
    ; \
} while (0)

// 0x226bbf0: void FTOI12_B(void)
#define FTOI12_B() do { \
    ; \
} while (0)

// 0x226bc00: void FTOI15(void)
#define FTOI15() do { \
    ; \
} while (0)

// 0x226bc10: void FTOI15_B(void)
#define FTOI15_B() do { \
    ; \
} while (0)

// 0x226bc20: void COPYVECTOR(sdfVector4_t *dst, const sdfVector4_t *src)
#define COPYVECTOR(dst, src) do { \
    *dst = src; \
} while (0)

// 0x226bc40: void COPYVECTOR_A_TO_B(void)
static inline void COPYVECTOR_A_TO_B(void) {
  vct_B = vct_A;
  return;
}

// 0x226bcd0: void COPYVECTOR_A_TO_C(void)
static inline void COPYVECTOR_A_TO_C(void) {
  vct_C = vct_A;
  return;
}

// 0x226bd60: void COPYVECTOR_B_TO_A(void)
static inline void COPYVECTOR_B_TO_A(void) {
  vct_A = vct_B;
  return;
}

// 0x226bdf0: void COPYVECTOR_B_TO_C(void)
static inline void COPYVECTOR_B_TO_C(void) {
  vct_C = vct_B;
  return;
}

// 0x226be80: void COPYVECTOR_C_TO_A(void)
static inline void COPYVECTOR_C_TO_A(void) {
  vct_A = vct_C;
  return;
}

// 0x226bf10: void COPYVECTOR_C_TO_B(void)
static inline void COPYVECTOR_C_TO_B(void) {
  vct_B = vct_C;
  return;
}

// 0x226bfa0: void SWAPVECTOR_A_B(void)
#define SWAPVECTOR_A_B() do { \
    vct_A = vct_B; \
    vct_B = vct_A; \
} while (0)

// 0x226c010: void SWAPVECTOR_A_C(void)
#define SWAPVECTOR_A_C() do { \
    vct_A = vct_C; \
    vct_C = vct_A; \
} while (0)

// 0x226c090: void SWAPVECTOR_B_C(void)
#define SWAPVECTOR_B_C() do { \
    vct_B = vct_C; \
    vct_C = vct_B; \
} while (0)

// 0x226c100: void ADDVECTOR(void)
#define ADDVECTOR() do { \
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B); \
} while (0)

// 0x226c170: void ADDVECTOR_A_C(void)
#define ADDVECTOR_A_C() do { \
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_C); \
} while (0)

// 0x226c1e0: void ADDVECTOR_B_A(void)
#define ADDVECTOR_B_A() do { \
    vct_B = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_B, (float32x4_t)vct_A); \
} while (0)

// 0x226c250: void ADDVECTOR_C_A(void)
#define ADDVECTOR_C_A() do { \
    vct_C = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_C, (float32x4_t)vct_A); \
} while (0)

// 0x226c2c0: void ADDVECTOR_B_C(void)
#define ADDVECTOR_B_C() do { \
    vct_B = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_B, (float32x4_t)vct_C); \
} while (0)

// 0x226c330: void SUBVECTOR(void)
#define SUBVECTOR() do { \
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B); \
} while (0)

// 0x226c3a0: void SUBVECTOR_A_C(void)
#define SUBVECTOR_A_C() do { \
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_C); \
} while (0)

// 0x226c410: void SUBVECTOR_B_A(void)
#define SUBVECTOR_B_A() do { \
    vct_B = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_B, (float32x4_t)vct_A); \
} while (0)

// 0x226c480: void SUBVECTOR_C_A(void)
#define SUBVECTOR_C_A() do { \
    vct_C = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_C, (float32x4_t)vct_A); \
} while (0)

// 0x226c4f0: void SUBVECTOR_B_C(void)
#define SUBVECTOR_B_C() do { \
    vct_B = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_B, (float32x4_t)vct_C); \
} while (0)

// 0x226c560: void MULVECTOR(void)
#define MULVECTOR() do { \
    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B); \
} while (0)

// 0x226c5d0: void SCALEVECTOR(f32 v)
#define SCALEVECTOR(v) do { \
    f32 v3; \
    f32 v4; \
    v3 = v; \
    v = v3; \
    v4 = v; \
    v = v4; \
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v); \
} while (0)

// 0x226c650: void SCALEVECTOR_B(f32 v)
#define SCALEVECTOR_B(v) do { \
    f32 v3; \
    f32 v4; \
    v3 = v; \
    v = v3; \
    v4 = v; \
    v = v4; \
    vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v); \
} while (0)

// 0x226c6d0: void SCALEVECTOR_A_AND_B(f32 v)
#define SCALEVECTOR_A_AND_B(v) do { \
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v); \
    vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v); \
} while (0)

// 0x226c7f0: void NEGVECTOR_XYZ(void)
#define NEGVECTOR_XYZ() do { \
    float32x2_t *static_fields; \
    static_fields[2].n64_u64[0] = vneg_f32(static_fields[2]).n64_u64[0]; \
    static_fields[3].n64_f32[0] = -static_fields[3].n64_f32[0]; \
} while (0)

// 0x226c860: void NEGVECTOR_XYZ_B(void)
#define NEGVECTOR_XYZ_B() do { \
    float32x2_t *static_fields; \
    static_fields[4].n64_u64[0] = vneg_f32(static_fields[4]).n64_u64[0]; \
    static_fields[5].n64_f32[0] = -static_fields[5].n64_f32[0]; \
} while (0)

// 0x226c8d0: void NEGVECTOR_XYZ_C(void)
#define NEGVECTOR_XYZ_C() do { \
    float32x2_t *static_fields; \
    static_fields[6].n64_u64[0] = vneg_f32(static_fields[6]).n64_u64[0]; \
    static_fields[7].n64_f32[0] = -static_fields[7].n64_f32[0]; \
} while (0)

// 0x226c940: void APPLYMATRIX(void)
#define APPLYMATRIX() do { \
    sdfMatrix4_t v2; \
    sdfMatrix4_t v3; \
    get_transpose(&v3, &mtx_A, 0); \
    v2 = v3; \
    vct_A = op_Multiply_60923920(&v2, vct_A, 0); \
} while (0)

// 0x226c9f0: void APPLYMATRIX_B(void)
#define APPLYMATRIX_B() do { \
    sdfMatrix4_t v2; \
    sdfMatrix4_t v3; \
    get_transpose(&v3, &mtx_A, 0); \
    *(_OWORD *)&v2.m00 = *(_OWORD *)&v3.m00; \
    *(_OWORD *)&v2.m01 = *(_OWORD *)&v3.m01; \
    *(_OWORD *)&v2.m02 = *(_OWORD *)&v3.m02; \
    *(_OWORD *)&v2.m03 = *(_OWORD *)&v3.m03; \
    vct_B = op_Multiply_60923920(&v2, vct_B, 0); \
} while (0)

// 0x226caa0: void APPLYMATRIX_XYZ1(void)
#define APPLYMATRIX_XYZ1() do { \
    sdfMatrix4_t v3; \
    sdfMatrix4_t v4; \
    vct_A.w = 1.0; \
    get_transpose(&v4, &mtx_A, 0); \
    v3 = v4; \
    vct_A = op_Multiply_60923920(&v3, vct_A, 0); \
} while (0)

// 0x226cb60: void APPLYMATRIX_XYZ1_B(void)
#define APPLYMATRIX_XYZ1_B() do { \
    sdfMatrix4_t v3; \
    sdfMatrix4_t v4; \
    vct_B.w = 1.0; \
    get_transpose(&v4, &mtx_A, 0); \
    *(_OWORD *)&v3.m00 = *(_OWORD *)&v4.m00; \
    *(_OWORD *)&v3.m01 = *(_OWORD *)&v4.m01; \
    *(_OWORD *)&v3.m02 = *(_OWORD *)&v4.m02; \
    *(_OWORD *)&v3.m03 = *(_OWORD *)&v4.m03; \
    vct_B = op_Multiply_60923920(&v3, vct_B, 0); \
} while (0)

// 0x226cc20: void APPLYMATRIX_XYZ(void)
#define APPLYMATRIX_XYZ() do { \
    sdfMatrix4_t v3; \
    sdfMatrix4_t v4; \
    vct_A.w = 0.0; \
    get_transpose(&v4, &mtx_A, 0); \
    v3 = v4; \
    vct_A = op_Multiply_60923920(&v3, vct_A, 0); \
} while (0)

// 0x226ccd0: void APPLYMATRIX_XYZ_B(void)
#define APPLYMATRIX_XYZ_B() do { \
    sdfMatrix4_t v3; \
    sdfMatrix4_t v4; \
    vct_B.w = 0.0; \
    get_transpose(&v4, &mtx_A, 0); \
    *(_OWORD *)&v3.m00 = *(_OWORD *)&v4.m00; \
    *(_OWORD *)&v3.m01 = *(_OWORD *)&v4.m01; \
    *(_OWORD *)&v3.m02 = *(_OWORD *)&v4.m02; \
    *(_OWORD *)&v3.m03 = *(_OWORD *)&v4.m03; \
    vct_B = op_Multiply_60923920(&v3, vct_B, 0); \
} while (0)

// 0x226cd80: void PERSVECTOR(void)
#define PERSVECTOR() do { \
    sdfMatrix4_t v4; \
    sdfMatrix4_t v5; \
    sdfVector4_t v6; \
    vct_A.w = 1.0; \
    get_transpose(&v5, &mtx_A, 0); \
    v4 = v5; \
    v6 = op_Multiply_60923920(&v4, vct_A, 0); \
    vct_A.x = v6.x * (f32)(1.0 / v6.w); \
    vct_A.y = v6.y * (f32)(1.0 / v6.w); \
    vct_A.z = v6.z * (f32)(1.0 / v6.w); \
    vct_A.w = 1.0 / v6.w; \
} while (0)

// 0x226ce50: f32 INNERPRODUCT(void)
static inline f32 INNERPRODUCT(void) {
  u64 v3;

  v3 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return *((f32 *)&v3 + 1)
       + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v3);
}

// 0x226ced0: void OUTERPRODUCT(void)
#define OUTERPRODUCT() do { \
    int32x2_t v3; \
    int32x2_t v4; \
    float32x2_t v5; \
    float32x2_t v6; \
    v3.n64_u64[0] = *(u64 *)&vct_B.y; \
    v4.n64_u64[0] = *(u64 *)&vct_A.y; \
    v5.n64_u32[0] = vdup_lane_s32(v3, 1).n64_u32[0]; \
    v6.n64_u32[0] = vdup_lane_s32(v4, 1).n64_u32[0]; \
    v5.n64_u32[1] = LODWORD(vct_B.x); \
    v6.n64_u32[1] = LODWORD(vct_A.x); \
    vct_A.z = (f32)(v6.n64_f32[1] * v3.n64_f32[0]) - (f32)(v5.n64_f32[1] * v4.n64_f32[0]); \
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v4, v5), vmul_f32(v6, v3)); \
} while (0)

// 0x226cf70: void NORMALIZE(void)
#define NORMALIZE() do { \
    int32x2_t v1; \
    float32x2_t *static_fields; \
    float32x2_t v4; \
    f32 z; \
    float32x2_t v7; \
    f32 v8; \
    float32x2_t v9; \
    float32x2_t *v12; \
    v4.n64_u64[0] = static_fields[2].n64_u64[0]; \
    z = static_fields[3].n64_f32[0]; \
    v1.n64_f32[0] = sqrtf((f32)(z * z) + vaddv_f32(vmul_f32(v4, v4))); \
    if (v1.n64_f32[0] <= 0.00001) \
    { \
    v9.n64_u64[0] = *(u64 *)&zeroVector.x; \
    v8 = zeroVector.z; \
    } \
    else \
    { \
    v7.n64_u64[0] = vdup_lane_s32(v1, 0).n64_u64[0]; \
    v8 = z / v1.n64_f32[0]; \
    v9.n64_u64[0] = vdiv_f32(v4, v7).n64_u64[0]; \
    } \
    v12[2].n64_u64[0] = v9.n64_u64[0]; \
    v12[3].n64_f32[0] = v8; \
} while (0)

// 0x226d0d0: f32 GETLENGTH(void)
static inline f32 GETLENGTH(void) {
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;

  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  return sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
}

// 0x226d1d0: void INTERPOLATE(f32 rate)
#define INTERPOLATE(rate) do { \
    f32 v4; \
    v4 = 1.0; \
    if (rate <= 1.0) \
    v4 = rate; \
    if (rate < 0.0) \
    v4 = 0.0; \
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, vmulq_n_f32(vsubq_f32((float32x4_t)vct_B, (float32x4_t)vct_A), v4)); \
} while (0)

// 0x226d260: void SET_ROW0(void)
#define SET_ROW0() do { \
    SetRow(&mtx_A, 0, vct_A, 0); \
} while (0)

// 0x226d2d0: void SET_ROW1(void)
#define SET_ROW1() do { \
    SetRow(&mtx_A, 1, vct_A, 0); \
} while (0)

// 0x226d340: void SET_ROW2(void)
#define SET_ROW2() do { \
    SetRow(&mtx_A, 2, vct_A, 0); \
} while (0)

// 0x226d3b0: void SET_ROW3(void)
#define SET_ROW3() do { \
    SetRow(&mtx_A, 3, vct_A, 0); \
} while (0)

// 0x226d420: void GET_ROW0(void)
#define GET_ROW0() do { \
    vct_A = GetRow(&mtx_A, 0, 0); \
} while (0)

// 0x226d4a0: void GET_ROW1(void)
#define GET_ROW1() do { \
    vct_A = GetRow(&mtx_A, 1, 0); \
} while (0)

// 0x226d520: void GET_ROW2(void)
#define GET_ROW2() do { \
    vct_A = GetRow(&mtx_A, 2, 0); \
} while (0)

// 0x226d5a0: void GET_ROW3(void)
#define GET_ROW3() do { \
    vct_A = GetRow(&mtx_A, 3, 0); \
} while (0)

// 0x226d620: void LOAD_ROW0(const sdfVector4_t *p)
#define LOAD_ROW0(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    sdfVector4_t v7; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    v7.z = z; \
    v7.w = w; \
    v7.x = x; \
    v7.y = y; \
    SetRow(&mtx_A, 0, v7, 0); \
} while (0)

// 0x226d6c0: void LOAD_ROW1(const sdfVector4_t *p)
#define LOAD_ROW1(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    sdfVector4_t v7; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    v7.z = z; \
    v7.w = w; \
    v7.x = x; \
    v7.y = y; \
    SetRow(&mtx_A, 1, v7, 0); \
} while (0)

// 0x226d760: void LOAD_ROW2(const sdfVector4_t *p)
#define LOAD_ROW2(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    sdfVector4_t v7; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    v7.z = z; \
    v7.w = w; \
    v7.x = x; \
    v7.y = y; \
    SetRow(&mtx_A, 2, v7, 0); \
} while (0)

// 0x226d800: void LOAD_ROW3(const sdfVector4_t *p)
#define LOAD_ROW3(p) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    sdfVector4_t v7; \
    w = p->w; \
    z = p->z; \
    y = p->y; \
    x = p->x; \
    v7.z = z; \
    v7.w = w; \
    v7.x = x; \
    v7.y = y; \
    SetRow(&mtx_A, 3, v7, 0); \
} while (0)

// 0x226d8a0: void MATRIX_ROW3_W_SET_ONE(void)
#define MATRIX_ROW3_W_SET_ONE() do { \
    set_Item_60922352(&mtx_A, 15, 1.0, 0); \
} while (0)

// 0x226d910: void STORE_ROW0(sdfVector4_t *p)
#define STORE_ROW0(p) do { \
    *p = GetRow(&mtx_A, 0, 0); \
} while (0)

// 0x226d990: void STORE_ROW1(sdfVector4_t *p)
#define STORE_ROW1(p) do { \
    *p = GetRow(&mtx_A, 1, 0); \
} while (0)

// 0x226da20: void STORE_ROW2(sdfVector4_t *p)
#define STORE_ROW2(p) do { \
    *p = GetRow(&mtx_A, 2, 0); \
} while (0)

// 0x226dab0: void STORE_ROW3(sdfVector4_t *p)
#define STORE_ROW3(p) do { \
    *p = GetRow(&mtx_A, 3, 0); \
} while (0)

// 0x226db40: void RESET_ROW3(void)
#define RESET_ROW3() do { \
    SetRow(&mtx_A, 3, vf00, 0); \
} while (0)

// 0x226dbb0: void ZEROVECTOR_W(void)
static inline void ZEROVECTOR_W(void) {
  vct_A.w = 0.0;
  return;
}

// 0x226dc80: void SETSCALE1VECTOR(void)
#define SETSCALE1VECTOR() do { \
    vct_A = (struct sdfVector4_t)xmmword_3D06BB0; \
} while (0)

// 0x226dcf0: void dds3ColorItoF(u32 rgba)
#define dds3ColorItoF(rgba) do { \
    int8x16_t v2; \
    int8x16_t v5; \
    uint32x4_t v6; \
    float32x4_t v7; \
    v2.n128_u32[0] = rgba; \
    v5.n128_u64[0] = 0xFF000000FFLL; \
    v5.n128_u64[1] = 0xFF000000FFLL; \
    v2.n128_u32[1] = rgba >> 8; \
    v2.n128_u32[2] = HIWORD(rgba); \
    v6 = vandq_s8(v2, v5); \
    v6.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(rgba), 0x18u).n128_u32[3]; \
    v7.n128_u64[0] = 0x3C0000003C000000LL; \
    v7.n128_u64[1] = 0x3C0000003C000000LL; \
    vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v6), v7); \
} while (0)

// 0x226dd90: sdfVector4_t GetColorItoF(u32 rgba, f32 ratio)
static inline sdfVector4_t GetColorItoF(u32 rgba, f32 ratio) {
  f32 v3;
  sdfVector4_t result;

  v3 = 1.0 / ratio;
  result.x = (f32)(1.0 / ratio) * (f32)(u8)rgba;
  result.y = v3 * (f32)BYTE1(rgba);
  result.z = v3 * (f32)BYTE2(rgba);
  result.w = (f32)HIBYTE(rgba) * 0.0078125;
  return result;
}

// 0x226ddd0: f32 GetAlphaItoF(u32 rgba)
#define GetAlphaItoF(rgba) ((f32)HIBYTE(rgba) * 0.0078125)

// 0x226ddf0: u32 dds3ColorFtoI(f32 ratio)
static inline u32 dds3ColorFtoI(f32 ratio) {
  f32 w;
  u32 v5;
  bool v6;
  u32 v7;
  f32 v8;
  s32 v9;
  u32 v10;
  float32x2_t v11;
  int32x2_t v12;
  int32x2_t v13;
  uint32x2_t v14;
  u64 v15;
  f32 v17;
  f32 v18;

  v17 = ratio;
  ratio = v17;
  v18 = ratio;
  ratio = v18;
  w = vct_A.w;
  v5 = vcvts_n_s32_f32(w, 7u);
  v6 = (f32)(w * 128.0) < 0.0;
  v7 = vcvts_n_u32_f32(w, 7u);
  v8 = vct_A.x * ratio;
  v9 = v8;
  if (!v6)
    v5 = v7;
  v10 = v8;
  v6 = v8 < 0.0;
  v11.n64_u64[0] = vmul_n_f32(*(float32x2_t *)&vct_A.y, ratio).n64_u64[0];
  v12.n64_u64[0] = vcltz_f32(v11).n64_u64[0];
  v13.n64_u64[0] = vcvt_s32_f32(v11).n64_u64[0];
  v14.n64_u64[0] = vcvt_u32_f32(v11).n64_u64[0];
  if (v6)
    LOBYTE(v10) = v9;
  v15 = vand_s8(vshl_u32(vbsl_s8(v12, v13, v14), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  return (u8)v10 | (v5 << 24) | v15 | HIDWORD(v15);
}

// 0x226dee0: u32 GetColorFtoI(const sdfVector4_t *rgba, f32 ratio)
static inline u32 GetColorFtoI(const sdfVector4_t *rgba, f32 ratio) {
  u32 v3;
  u32 v4;
  f32 v5;
  f32 z;
  u32 v7;
  s32 v8;
  bool v9;
  float32x2_t v10;
  int32x2_t v11;
  int32x2_t v12;
  uint32x2_t v13;
  u64 v14;

  v3 = vcvts_n_s32_f32(rgba->w, 7u);
  v4 = vcvts_n_u32_f32(rgba->w, 7u);
  v5 = rgba->x * ratio;
  z = rgba->z;
  v7 = v5;
  if ((f32)(rgba->w * 128.0) >= 0.0)
    v3 = v4;
  v8 = v5;
  v9 = v5 < 0.0;
  v10.n64_u64[0] = vmul_n_f32(*(float32x2_t *)&rgba->y, ratio).n64_u64[0];
  v11.n64_u64[0] = vcltz_f32(v10).n64_u64[0];
  v12.n64_u64[0] = vcvt_s32_f32(v10).n64_u64[0];
  v13.n64_u64[0] = vcvt_u32_f32(v10).n64_u64[0];
  if (!v9)
    LOBYTE(v8) = v7;
  v14 = vand_s8(vshl_u32(vbsl_s8(v11, v12, v13), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  return (u8)v8 | (v3 << 24) | v14 | HIDWORD(v14);
}

// 0x226df60: u32 GetAplhaFtoI(f32 a)
static inline u32 GetAplhaFtoI(f32 a) {
  u32 v2;
  u32 v3;

  v2 = vcvts_n_s32_f32(a, 7u);
  v3 = vcvts_n_u32_f32(a, 7u);
  if ((f32)(a * 128.0) >= 0.0)
    v2 = v3;
  return v2 << 24;
}

// 0x226df80: sdfColor32_t GetColorIto32(u32 rgba)
static inline sdfColor32_t GetColorIto32(u32 rgba) {
  sdfColor32_t result;

  result.rgba = rgba;
  return result;
}

// 0x226df90: f32 GetAlphaIto32(u32 rgba)
#define GetAlphaIto32(rgba) ((f32)HIBYTE(rgba))

// 0x226dfa0: sdfColor32_t GetColorFto32(const sdfVector4_t *rgba)
static inline sdfColor32_t GetColorFto32(const sdfVector4_t *rgba) {
  f32 y;
  float32x2_t v3;
  int8x8_t v4;
  u64 v5;

  y = rgba->y;
  v3.n64_u64[0] = vmul_f32(*(float32x2_t *)&rgba->w, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v4.n64_u64[0] = vcvt_n_s32_f32(*(float32x2_t *)&rgba->w, 7u).n64_u64[0];
  v5 = vshl_u32(vand_s8(vbsl_s8(vcltz_f32(v3), v4, v4), (int8x8_t)0xFF000000FFLL), (uint32x2_t)0x800000018LL).n64_u64[0];
  return (sdfColor32_t)((u32)v5 | ((u8)vcvts_n_s32_f32(rgba->z, 7u) << 16) | (u8)vcvts_n_s32_f32(rgba->x, 7u) | HIDWORD(v5));
}

// 0x226e010: u8 GetAlphaFto32(f32 a)
#define GetAlphaFto32(a) (vcvts_n_s32_f32(a, 7u))
