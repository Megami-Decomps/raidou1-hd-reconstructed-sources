#include "types.h"
#include "sdf_vu0.h"
#include "sdfmath.h"
#include "sdfquat.h"
#include "sdfvu0.h"

// macros
// 0x2265ce0: sdfQuaternion_t V2Q(const sdfVector4_t *src)
static inline sdfQuaternion_t V2Q(const sdfVector4_t *src) {
  sdfQuaternion_t result;

  result.x = src->x;
  result.y = src->y;
  result.z = src->z;
  result.w = src->w;
  return result;
}

// 0x2265cf0: sdfVector4_t Q2V(const sdfQuaternion_t *src)
static inline sdfVector4_t Q2V(const sdfQuaternion_t *src) {
  sdfVector4_t result;

  result.x = src->x;
  result.y = src->y;
  result.z = src->z;
  result.w = src->w;
  return result;
}

// 0x2266010: f32 SDF_QUAT_INNERPRODUCT(void)
static inline f32 SDF_QUAT_INNERPRODUCT(void) {
  float32x2_t *static_fields;
  int32x2_t v3;
  int32x2_t v4;
  f32 result;

  v3.n64_u64[0] = vmul_f32(static_fields[3], static_fields[5]).n64_u64[0];
  v4.n64_u64[0] = vmul_f32(static_fields[2], static_fields[4]).n64_u64[0];
  LODWORD(result) = vadd_f32(vdup_lane_s32(v3, 1), vadd_f32(v3, vadd_f32(v4, vdup_lane_s32(v4, 1)))).n64_u32[0];
  return result;
}

// 0x2265d00
void Mult(void) {
  int8x16_t v1;
  int8x16_t v2;
  float32x4_t v6;
  float32x4_t v7;
  float32x4_t v8;
  float32x4_t v9;
  float32x4_t v10;
  int32x4_t v11;
  float32x4_t v12;
  float32x4_t v13;
  int8x16_t v14;
  float32x4_t v15;
  int8x16_t v16;

  v1.n128_u32[0] = LODWORD(vct_A.x);
  v2.n128_u64[0] = *(u64 *)&vct_A.y;
  v6 = vmulq_n_f32(vct_B, vct_A.w);
  v7 = vextq_s8(vextq_s8(v1, v1, 4u), v2, 0xCu);
  v7.n128_u32[3] = v7.n128_u32[0];
  v8 = vmulq_f32(v7, vextq_s8(vdupq_laneq_s32(vct_B, 3), vct_B, 4u));
  v9 = vaddq_f32(v6, v8);
  v10 = vsubq_f32(v6, v8);
  v11 = vuzp2q_s32(v2, vzip1q_s32(v2, v2));
  v12 = v11;
  v12.n128_u32[1] = v1.n128_u32[0];
  v12.n128_u32[3] = v11.n128_u32[2];
  v13 = vct_B;
  v13.n128_u32[3] = HIDWORD(*(u64 *)&vct_B.x);
  vct_B.n128_u32[3] = *(u64 *)&vct_B.z;
  v14 = vmulq_f32(v12, v13);
  v15 = vaddq_f32(v9, vuzp2q_s32(vextq_s8(v14, v14, 4u), v14));
  v15.n128_u32[3] = vsubq_f32(v10, v14).n128_u32[3];
  v10.n128_u64[0] = v2.n128_u64[0];
  v10.n128_u64[1] = __PAIR64__(v2.n128_u32[1], v1.n128_u32[0]);
  v16 = vmulq_f32(v10, vct_B);
  vct_A = (struct sdfVector4_t)vsubq_f32(v15, vzip2q_s32(vzip1q_s32(v16, vextq_s8(v16, v16, 0xCu)), v16));
}

// 0x2265df0
void Inverse(void) {
  f32 v3;
  sdfQuaternion_t v4;

  v4 = Inverse((sdfQuaternion_t)vct_A, 0);
  v3 = (f32)(vct_A.w * vct_A.w)
     + (f32)((f32)(vct_A.z * vct_A.z) + (f32)((f32)(vct_A.x * vct_A.x) + (f32)(vct_A.y * vct_A.y)));
  vct_A.x = v4.x / v3;
  vct_A.y = v4.y / v3;
  vct_A.z = v4.z / v3;
  vct_A.w = v4.w / v3;
}

// 0x2265ea0
void Normalize(void) {
  struct sdfVector4_t vct_A_local;
  int8x16_t v4;
  int32x2_t v5;
  float32x4_t zeroVector_local;

  vct_A_local = vct_A;
  v4 = vmulq_f32((float32x4_t)vct_A_local, (float32x4_t)vct_A_local);
  v5.n64_u64[0] = vadd_f32(vdup_laneq_s32(v4, 3), vadd_f32((float32x2_t)vextq_s8(v4, v4, 8u).n128_u64[0], vadd_f32((float32x2_t)v4.n128_u64[0], vdup_lane_s32((int32x2_t)v4.n128_u64[0], 1)))).n64_u64[0];
  v5.n64_f32[0] = sqrtf(v5.n64_f32[0]);
  if (v5.n64_f32[0] <= 0.00001)
  {
    zeroVector_local = zeroVector;
  }
  else
  {
    zeroVector_local = vdivq_f32((float32x4_t)vct_A_local, vdupq_lane_s32(v5, 0));
  }
  vct_A = (struct sdfVector4_t)zeroVector_local;
}

// 0x2266090
f32 InnerProduct(void) {
  float32x2_t *static_fields;
  int32x2_t v3;
  int32x2_t v4;
  f32 result;

  v3.n64_u64[0] = vmul_f32(static_fields[3], static_fields[5]).n64_u64[0];
  v4.n64_u64[0] = vmul_f32(static_fields[2], static_fields[4]).n64_u64[0];
  LODWORD(result) = vadd_f32(vdup_lane_s32(v3, 1), vadd_f32(v3, vadd_f32(v4, vdup_lane_s32(v4, 1)))).n64_u32[0];
  return result;
}

// 0x2266110
void FromRotation(f32 aAngle) {
  f32 v3;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;

  v3 = (f32)(aAngle * 0.5) * 0.15915494;
  v4 = (s32)v3;
  if (v3 == INFINITY)
    v4 = -2147500000.0;
  v5 = v3 - v4;
  v6 = -1.0;
  if (v5 <= 0.5)
  {
    v7 = -1.0;
    if (v5 >= -0.5)
      goto LABEL_10;
    v6 = 1.0;
  }
  else
  {
    v7 = -1.0;
  }
  v5 = v5 + v6;
LABEL_10:
  v8 = -0.5 - v5;
  if (v5 >= -0.25)
    v8 = v5;
  if (v5 > 0.25)
    v9 = 0.5 - v5;
  else
    v9 = v8;
  v10 = v9 * 4.0;
  v11 = v10 * (f32)(v10 * v10);
  v12 = (f32)(v10 * v10) * (f32)((f32)(v10 * v10) * v11);
  v13 = (f32)(v10 * v10) * v12;
  v14 = (f32)((f32)(v10 * 1.5708) + (f32)(v11 * -0.6459637)) + (f32)((f32)((f32)(v10 * v10) * v11) * 0.07968968);
  v15 = v12 * -0.0046737655;
  v16 = v14 + v15;
  v17 = v13 * 0.00015148419;
  v19 = v16 + v17;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v19);
  v20 = (f32)((f32)(aAngle * 0.5) + 1.5708) * 0.15915494;
  v21 = (s32)v20;
  if (v20 == INFINITY)
    v21 = -2147500000.0;
  v22 = v20 - v21;
  if (v22 <= 0.5)
  {
    v23 = -0.5;
    if (v22 < -0.5)
      v22 = v22 + 1.0;
  }
  else
  {
    v22 = v22 + v7;
    v23 = -0.5;
  }
  if (v22 <= 0.25)
  {
    if (v22 < -0.25)
      v22 = v23 - v22;
  }
  else
  {
    v22 = 0.5 - v22;
  }
  v24 = v22 * 4.0;
  vct_A.w = (f32)((f32)((f32)((f32)(v24 * 1.5708) + (f32)((f32)(v24 * (f32)(v24 * v24)) * -0.6459637)) + (f32)((f32)((f32)(v24 * v24) * (f32)(v24 * (f32)(v24 * v24))) * 0.07968968)) + (f32)((f32)((f32)(v24 * v24) * (f32)((f32)(v24 * v24) * (f32)(v24 * (f32)(v24 * v24)))) * -0.0046737655))
                                     + (f32)((f32)((f32)(v24 * v24) * (f32)((f32)(v24 * v24) * (f32)((f32)(v24 * v24) * (f32)(v24 * (f32)(v24 * v24))))) * 0.00015148419);
}

// 0x2266410
void FromRotation_B(f32 aAngle) {
  f32 v3;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;

  v3 = (f32)(aAngle * 0.5) * 0.15915494;
  v4 = (s32)v3;
  if (v3 == INFINITY)
    v4 = -2147500000.0;
  v5 = v3 - v4;
  v6 = -1.0;
  if (v5 <= 0.5)
  {
    v7 = -1.0;
    if (v5 >= -0.5)
      goto LABEL_10;
    v6 = 1.0;
  }
  else
  {
    v7 = -1.0;
  }
  v5 = v5 + v6;
LABEL_10:
  v8 = -0.5 - v5;
  if (v5 >= -0.25)
    v8 = v5;
  if (v5 > 0.25)
    v9 = 0.5 - v5;
  else
    v9 = v8;
  v10 = v9 * 4.0;
  v11 = v10 * (f32)(v10 * v10);
  v12 = (f32)(v10 * v10) * (f32)((f32)(v10 * v10) * v11);
  v13 = (f32)(v10 * v10) * v12;
  v14 = (f32)((f32)(v10 * 1.5708) + (f32)(v11 * -0.6459637)) + (f32)((f32)((f32)(v10 * v10) * v11) * 0.07968968);
  v15 = v12 * -0.0046737655;
  v16 = v14 + v15;
  v17 = v13 * 0.00015148419;
  v19 = v16 + v17;
  vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v19);
  v20 = (f32)((f32)(aAngle * 0.5) + 1.5708) * 0.15915494;
  v21 = (s32)v20;
  if (v20 == INFINITY)
    v21 = -2147500000.0;
  v22 = v20 - v21;
  if (v22 <= 0.5)
  {
    v23 = -0.5;
    if (v22 < -0.5)
      v22 = v22 + 1.0;
  }
  else
  {
    v22 = v22 + v7;
    v23 = -0.5;
  }
  if (v22 <= 0.25)
  {
    if (v22 < -0.25)
      v22 = v23 - v22;
  }
  else
  {
    v22 = 0.5 - v22;
  }
  v24 = v22 * 4.0;
  vct_B.w = (f32)((f32)((f32)((f32)(v24 * 1.5708) + (f32)((f32)(v24 * (f32)(v24 * v24)) * -0.6459637)) + (f32)((f32)((f32)(v24 * v24) * (f32)(v24 * (f32)(v24 * v24))) * 0.07968968)) + (f32)((f32)((f32)(v24 * v24) * (f32)((f32)(v24 * v24) * (f32)(v24 * (f32)(v24 * v24)))) * -0.0046737655))
                                     + (f32)((f32)((f32)(v24 * v24) * (f32)((f32)(v24 * v24) * (f32)((f32)(v24 * v24) * (f32)(v24 * (f32)(v24 * v24))))) * 0.00015148419);
}

// 0x2266710
void ToMatrix(void) {
  __int128 v3;
  __int128 v4;
  sdfMatrix4_t v5;

  Rotate(&v5, (sdfQuaternion_t)vct_A, 0);
  v3 = *(_OWORD *)&v5.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v5.m00;
  *(_OWORD *)&mtx_A.m01 = v3;
  v4 = *(_OWORD *)&v5.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v5.m02;
  *(_OWORD *)&mtx_A.m03 = v4;
}

// 0x22667a0
void FromEulerXYZ(f32 aRotateX, f32 aRotateY, f32 aRotateZ) {
  f32 v7;
  f32 v8;
  f32 v9;
  s32 v10;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  s32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  s32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  float32x2_t v48;
  f32 v49;
  f32 v50;
  float32x2_t v51;
  f32 v52;
  float32x2_t v53;
  float32x2_t v54;
  f32 v55;
  float32x2_t v56;
  float32x2_t v61;
  float32x2_t v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  float32x2_t v71;
  float32x2_t v72;
  float32x2_t v73;
  float32x2_t v74;
  float32x2_t v75;
  float32x2_t v76;
  float32x2_t v77;
  float32x2_t v78;
  float32x2_t v79;
  int8x8_t v80;
  float32x2_t v81;
  float32x2_t v82;
  float32x2_t v83;
  float32x2_t v84;
  float32x2_t v85;
  int8x8_t v86;
  float32x2_t v87;
  float32x2_t v88;
  int32x4_t v89;
  float32x4_t v90;
  int32x4_t v91;
  int32x4_t v92;
  float32x4_t v93;
  float32x4_t v94;
  float32x4_t v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;

  v7 = -aRotateX;
  if (aRotateX >= -3.1415927)
  {
    if (aRotateX <= 3.1415927)
      goto LABEL_10;
    v8 = aRotateX / -6.2831855;
    v9 = (f32)((s32)(f32)(aRotateX / -6.2831855) - 1) * 6.2831855;
    *(f32 *)&v10 = 13493038000.0;
  }
  else
  {
    v8 = aRotateX / -6.2831855;
    v9 = (f32)((s32)(f32)(aRotateX / -6.2831855) + 1) * 6.2831855;
    *(f32 *)&v10 = -13493038000.0;
  }
  _ZF = v8 == INFINITY;
  v12 = *(f32 *)&v10;
  if (!_ZF)
    v12 = v9;
  v7 = v7 - v12;
LABEL_10:
  v13 = v7 * 0.5;
  v14 = (f32)((f32)(v7 * 0.5) + 1.5708) * 0.15915494;
  v15 = (s32)v14;
  if (v14 == INFINITY)
    v15 = -2147500000.0;
  v16 = -1.0;
  v17 = v14 - v15;
  if ((f32)(v14 - v15) <= 0.5)
  {
    if (v17 < -0.5)
      v17 = v17 + 1.0;
  }
  else
  {
    v17 = v17 + -1.0;
  }
  if (v17 <= 0.25)
  {
    if (v17 < -0.25)
      v17 = -0.5 - v17;
  }
  else
  {
    v17 = 0.5 - v17;
  }
  v98 = v17;
  v18 = v13 * 0.15915494;
  v19 = (s32)v18;
  if (v18 == INFINITY)
    v19 = -2147500000.0;
  v20 = v18 - v19;
  if (v20 <= 0.5)
  {
    if (v20 < -0.5)
      v20 = v20 + 1.0;
  }
  else
  {
    v20 = v20 + -1.0;
  }
  if (v20 <= 0.25)
  {
    if (v20 < -0.25)
      v20 = -0.5 - v20;
  }
  else
  {
    v20 = 0.5 - v20;
  }
  v21 = -aRotateY;
  v97 = v20;
  if (aRotateY >= -3.1415927)
  {
    if (aRotateY <= 3.1415927)
      goto LABEL_37;
    v22 = aRotateY / -6.2831855;
    v23 = (f32)((s32)(f32)(aRotateY / -6.2831855) - 1) * 6.2831855;
    *(f32 *)&v24 = 13493038000.0;
  }
  else
  {
    v22 = aRotateY / -6.2831855;
    v23 = (f32)((s32)(f32)(aRotateY / -6.2831855) + 1) * 6.2831855;
    *(f32 *)&v24 = -13493038000.0;
  }
  _ZF = v22 == INFINITY;
  v25 = *(f32 *)&v24;
  if (!_ZF)
    v25 = v23;
  v21 = v21 - v25;
LABEL_37:
  v26 = v21 * 0.5;
  v27 = (f32)(v26 + 1.5708) * 0.15915494;
  v28 = (s32)v27;
  if (v27 == INFINITY)
    v28 = -2147500000.0;
  v29 = v27 - v28;
  if ((f32)(v27 - v28) <= 0.5)
  {
    if (v29 < -0.5)
      v29 = v29 + 1.0;
  }
  else
  {
    v29 = v29 + -1.0;
  }
  if (v29 <= 0.25)
  {
    if (v29 < -0.25)
      v29 = -0.5 - v29;
  }
  else
  {
    v29 = 0.5 - v29;
  }
  v30 = v26 * 0.15915494;
  v31 = (s32)v30;
  if (v30 == INFINITY)
    v31 = -2147500000.0;
  v32 = v30 - v31;
  if ((f32)(v30 - v31) <= 0.5)
  {
    if (v32 < -0.5)
      v32 = v32 + 1.0;
  }
  else
  {
    v32 = v32 + -1.0;
  }
  if (v32 <= 0.25)
  {
    if (v32 < -0.25)
      v32 = -0.5 - v32;
  }
  else
  {
    v32 = 0.5 - v32;
  }
  v33 = -aRotateZ;
  if (aRotateZ >= -3.1415927)
  {
    if (aRotateZ <= 3.1415927)
      goto LABEL_64;
    v34 = aRotateZ / -6.2831855;
    v35 = (f32)((s32)(f32)(aRotateZ / -6.2831855) - 1) * 6.2831855;
    *(f32 *)&v36 = 13493038000.0;
  }
  else
  {
    v34 = aRotateZ / -6.2831855;
    v35 = (f32)((s32)(f32)(aRotateZ / -6.2831855) + 1) * 6.2831855;
    *(f32 *)&v36 = -13493038000.0;
  }
  _ZF = v34 == INFINITY;
  v37 = *(f32 *)&v36;
  if (!_ZF)
    v37 = v35;
  v33 = v33 - v37;
LABEL_64:
  v38 = v33 * 0.5;
  v39 = (f32)(v38 + 1.5708) * 0.15915494;
  v40 = (s32)v39;
  if (v39 == INFINITY)
    v40 = -2147500000.0;
  v41 = v39 - v40;
  if ((f32)(v39 - v40) <= 0.5)
  {
    if (v41 < -0.5)
      v41 = v41 + 1.0;
  }
  else
  {
    v41 = v41 + -1.0;
  }
  if (v41 <= 0.25)
  {
    if (v41 < -0.25)
      v41 = -0.5 - v41;
  }
  else
  {
    v41 = 0.5 - v41;
  }
  v42 = v38 * 0.15915494;
  v96 = v41;
  v43 = (s32)v42;
  if (v42 == INFINITY)
    v43 = -2147500000.0;
  v44 = v42 - v43;
  if (v44 <= 0.5)
  {
    if (v44 >= -0.5)
      goto LABEL_80;
    v16 = 1.0;
  }
  v44 = v44 + v16;
LABEL_80:
  v45 = -0.5 - v44;
  if (v44 >= -0.25)
    v45 = v44;
  if (v44 > 0.25)
    v46 = 0.5 - v44;
  else
    v46 = v45;
  v99 = v32;
  v32 = v99;
  v48.n64_u64[0] = vdup_n_s32(0x3FC90FDAu).n64_u64[0];
  v49 = v29 * 4.0;
  v50 = v46 * 4.0;
  v51.n64_u64[0] = vdup_n_s32(0x3F255DE1u).n64_u64[0];
  v52 = v49 * v49;
  v53.n64_u64[0] = vdup_n_s32(0x3DA33458u).n64_u64[0];
  v54.n64_u64[0] = vdup_n_s32(0x3B992663u).n64_u64[0];
  v55 = (f32)((f32)((f32)((f32)((f32)(v29 * 4.0) * 1.5708) - (f32)((f32)(v49 * (f32)(v49 * v49)) * 0.6459637)) + (f32)((f32)(v52 * (f32)(v49 * (f32)(v49 * v49))) * 0.07968968)) - (f32)((f32)(v52 * (f32)(v52 * (f32)(v49 * (f32)(v49 * v49)))) * 0.0046737655))
      + (f32)((f32)(v52 * (f32)(v52 * (f32)(v52 * (f32)(v49 * (f32)(v49 * v49))))) * 0.00015148419);
  v56.n64_u64[0] = vdup_n_s32(0x391ED7BAu).n64_u64[0];
  __asm { FMOV            V4.2S, #4.0 }
  v61.n64_u64[0] = vmul_f32((float32x2_t)__PAIR64__(LODWORD(v32), LODWORD(v96)), _D4).n64_u64[0];
  v62.n64_u64[0] = vmul_f32((float32x2_t)__PAIR64__(LODWORD(v98), LODWORD(v97)), _D4).n64_u64[0];
  v63 = v50 * v50;
  v64 = v50 * (f32)(v50 * v50);
  v65 = v64 * 0.6459637;
  v66 = v63 * v64;
  v67 = (f32)((f32)(v46 * 4.0) * 1.5708) - v65;
  v68 = v66 * 0.07968968;
  v69 = v63 * v66;
  v70 = (f32)(v67 + v68) - (f32)(v69 * 0.0046737655);
  v71.n64_u64[0] = vmul_f32(v61, v61).n64_u64[0];
  v72.n64_u64[0] = vmul_f32(v61, v48).n64_u64[0];
  v73.n64_u64[0] = vmul_f32(v62, v48).n64_u64[0];
  v74.n64_u64[0] = vmul_f32(v61, v71).n64_u64[0];
  v75.n64_u64[0] = vmul_f32(v74, v51).n64_u64[0];
  v76.n64_u64[0] = vmul_f32(v74, v71).n64_u64[0];
  v77.n64_u64[0] = vsub_f32(v72, v75).n64_u64[0];
  v78.n64_u64[0] = vmul_f32(v76, v53).n64_u64[0];
  v79.n64_u64[0] = vmul_f32(v76, v71).n64_u64[0];
  v80.n64_u64[0] = vadd_f32(vsub_f32(vadd_f32(v77, v78), vmul_f32(v79, v54)), vmul_f32(vmul_f32(v71, v79), v56)).n64_u64[0];
  v81.n64_u64[0] = vmul_f32(v62, v62).n64_u64[0];
  v82.n64_u64[0] = vmul_f32(v62, v81).n64_u64[0];
  v83.n64_u64[0] = vmul_f32(v82, v51).n64_u64[0];
  v84.n64_u64[0] = vmul_f32(v82, v81).n64_u64[0];
  v85.n64_u64[0] = vsub_f32(v73, v83).n64_u64[0];
  v86.n64_u64[0] = vmul_f32(v84, v53).n64_u64[0];
  v87.n64_u64[0] = vmul_f32(v84, v81).n64_u64[0];
  v88.n64_u64[0] = vsub_f32(vadd_f32(v85, v86), vmul_f32(v87, v54)).n64_u64[0];
  v86.n64_u32[0] = vdup_lane_s32(v80, 1).n64_u32[0];
  v86.n64_f32[1] = v55;
  v89.n128_u64[0] = vadd_f32(v88, vmul_f32(vmul_f32(v81, v87), v56)).n64_u64[0];
  v90.n128_u64[0] = v89.n128_u64[0];
  v91.n128_u64[0] = vmul_n_f32(v86, v70 + (f32)((f32)(v63 * v69) * 0.00015148419)).n64_u64[0];
  v90.n128_u64[1] = v89.n128_u64[0];
  v92 = vrev64q_s32(v91);
  v89.n128_u64[1] = v89.n128_u64[0];
  v93 = vzip1q_s32(v91, v92);
  v92.n128_u64[0] = vmul_f32(v80, vext_s8(v86, v80, 4u)).n64_u64[0];
  v94 = vmulq_f32(vrev64q_s32(v89), v93);
  v95 = vmulq_f32(v90, vzip1q_s32(v92, vrev64q_s32(v92)));
  vct_A = (struct sdfVector4_t)vtrn2q_s32(vrev64q_s32(vaddq_f32(v95, v94)), vsubq_f32(v95, v94));
}

// 0x2266f20
void FromEuler(f32 aRotateX, f32 aRotateY, f32 aRotateZ) {
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  float32x2_t v30;
  f32 v31;
  f32 v32;
  float32x2_t v33;
  f32 v34;
  float32x2_t v35;
  float32x2_t v36;
  f32 v37;
  float32x2_t v38;
  float32x2_t v44;
  float32x2_t v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  float32x2_t v54;
  float32x2_t v55;
  float32x2_t v56;
  float32x2_t v57;
  float32x2_t v58;
  float32x2_t v59;
  float32x2_t v60;
  float32x2_t v61;
  float32x2_t v62;
  int8x8_t v63;
  float32x2_t v64;
  float32x2_t v65;
  float32x2_t v66;
  float32x2_t v67;
  float32x2_t v68;
  int8x8_t v69;
  float32x2_t v70;
  float32x2_t v71;
  int32x4_t v72;
  float32x4_t v73;
  int32x4_t v74;
  int32x4_t v75;
  float32x4_t v76;
  float32x4_t v77;
  float32x4_t v78;
  f32 v79;
  f32 v80;
  f32 v81;
  f32 v82;

  v7 = (f32)((f32)(aRotateX * -0.5) + 1.5708) * 0.15915494;
  v8 = (s32)v7;
  if (v7 == INFINITY)
    v8 = -2147500000.0;
  v9 = -1.0;
  v10 = v7 - v8;
  if ((f32)(v7 - v8) <= 0.5)
  {
    if (v10 < -0.5)
      v10 = v10 + 1.0;
  }
  else
  {
    v10 = v10 + -1.0;
  }
  if (v10 <= 0.25)
  {
    if (v10 < -0.25)
      v10 = -0.5 - v10;
  }
  else
  {
    v10 = 0.5 - v10;
  }
  v81 = v10;
  v11 = (f32)(aRotateX * -0.5) * 0.15915494;
  v12 = (s32)v11;
  if (v11 == INFINITY)
    v12 = -2147500000.0;
  v13 = v11 - v12;
  if (v13 <= 0.5)
  {
    if (v13 < -0.5)
      v13 = v13 + 1.0;
  }
  else
  {
    v13 = v13 + -1.0;
  }
  if (v13 <= 0.25)
  {
    if (v13 < -0.25)
      v13 = -0.5 - v13;
  }
  else
  {
    v13 = 0.5 - v13;
  }
  v14 = aRotateY * -0.5;
  v80 = v13;
  v15 = (f32)((f32)(aRotateY * -0.5) + 1.5708) * 0.15915494;
  v16 = (s32)v15;
  if (v15 == INFINITY)
    v16 = -2147500000.0;
  v17 = v15 - v16;
  if ((f32)(v15 - v16) <= 0.5)
  {
    if (v17 < -0.5)
      v17 = v17 + 1.0;
  }
  else
  {
    v17 = v17 + -1.0;
  }
  if (v17 <= 0.25)
  {
    if (v17 < -0.25)
      v17 = -0.5 - v17;
  }
  else
  {
    v17 = 0.5 - v17;
  }
  v18 = v14 * 0.15915494;
  v19 = (s32)v18;
  if (v18 == INFINITY)
    v19 = -2147500000.0;
  v20 = v18 - v19;
  if ((f32)(v18 - v19) <= 0.5)
  {
    if (v20 < -0.5)
      v20 = v20 + 1.0;
  }
  else
  {
    v20 = v20 + -1.0;
  }
  if (v20 <= 0.25)
  {
    if (v20 < -0.25)
      v20 = -0.5 - v20;
  }
  else
  {
    v20 = 0.5 - v20;
  }
  v21 = (f32)((f32)(aRotateZ * -0.5) + 1.5708) * 0.15915494;
  v22 = (s32)v21;
  if (v21 == INFINITY)
    v22 = -2147500000.0;
  v23 = v21 - v22;
  if ((f32)(v21 - v22) <= 0.5)
  {
    if (v23 < -0.5)
      v23 = v23 + 1.0;
  }
  else
  {
    v23 = v23 + -1.0;
  }
  if (v23 <= 0.25)
  {
    if (v23 < -0.25)
      v23 = -0.5 - v23;
  }
  else
  {
    v23 = 0.5 - v23;
  }
  v24 = (f32)(aRotateZ * -0.5) * 0.15915494;
  v79 = v23;
  v25 = (s32)v24;
  if (v24 == INFINITY)
    v25 = -2147500000.0;
  v26 = v24 - v25;
  if (v26 <= 0.5)
  {
    if (v26 >= -0.5)
      goto LABEL_59;
    v9 = 1.0;
  }
  v26 = v26 + v9;
LABEL_59:
  v27 = -0.5 - v26;
  if (v26 >= -0.25)
    v27 = v26;
  if (v26 > 0.25)
    v28 = 0.5 - v26;
  else
    v28 = v27;
  v82 = v20;
  v20 = v82;
  v30.n64_u64[0] = vdup_n_s32(0x3FC90FDAu).n64_u64[0];
  v31 = v17 * 4.0;
  v32 = v28 * 4.0;
  v33.n64_u64[0] = vdup_n_s32(0x3F255DE1u).n64_u64[0];
  v34 = v31 * v31;
  v35.n64_u64[0] = vdup_n_s32(0x3DA33458u).n64_u64[0];
  v36.n64_u64[0] = vdup_n_s32(0x3B992663u).n64_u64[0];
  v37 = (f32)((f32)((f32)((f32)((f32)(v17 * 4.0) * 1.5708) - (f32)((f32)(v31 * (f32)(v31 * v31)) * 0.6459637)) + (f32)((f32)(v34 * (f32)(v31 * (f32)(v31 * v31))) * 0.07968968)) - (f32)((f32)(v34 * (f32)(v34 * (f32)(v31 * (f32)(v31 * v31)))) * 0.0046737655))
      + (f32)((f32)(v34 * (f32)(v34 * (f32)(v34 * (f32)(v31 * (f32)(v31 * v31))))) * 0.00015148419);
  v38.n64_u64[0] = vdup_n_s32(0x391ED7BAu).n64_u64[0];
  __asm { FMOV            V4.2S, #4.0 }
  v44.n64_u64[0] = vmul_f32((float32x2_t)__PAIR64__(LODWORD(v20), LODWORD(v79)), _D4).n64_u64[0];
  v45.n64_u64[0] = vmul_f32((float32x2_t)__PAIR64__(LODWORD(v81), LODWORD(v80)), _D4).n64_u64[0];
  v46 = v32 * v32;
  v47 = v32 * (f32)(v32 * v32);
  v48 = v47 * 0.6459637;
  v49 = v46 * v47;
  v50 = (f32)((f32)(v28 * 4.0) * 1.5708) - v48;
  v51 = v49 * 0.07968968;
  v52 = v46 * v49;
  v53 = (f32)(v50 + v51) - (f32)(v52 * 0.0046737655);
  v54.n64_u64[0] = vmul_f32(v44, v44).n64_u64[0];
  v55.n64_u64[0] = vmul_f32(v44, v30).n64_u64[0];
  v56.n64_u64[0] = vmul_f32(v45, v30).n64_u64[0];
  v57.n64_u64[0] = vmul_f32(v44, v54).n64_u64[0];
  v58.n64_u64[0] = vmul_f32(v57, v33).n64_u64[0];
  v59.n64_u64[0] = vmul_f32(v57, v54).n64_u64[0];
  v60.n64_u64[0] = vsub_f32(v55, v58).n64_u64[0];
  v61.n64_u64[0] = vmul_f32(v59, v35).n64_u64[0];
  v62.n64_u64[0] = vmul_f32(v59, v54).n64_u64[0];
  v63.n64_u64[0] = vadd_f32(vsub_f32(vadd_f32(v60, v61), vmul_f32(v62, v36)), vmul_f32(vmul_f32(v54, v62), v38)).n64_u64[0];
  v64.n64_u64[0] = vmul_f32(v45, v45).n64_u64[0];
  v65.n64_u64[0] = vmul_f32(v45, v64).n64_u64[0];
  v66.n64_u64[0] = vmul_f32(v65, v33).n64_u64[0];
  v67.n64_u64[0] = vmul_f32(v65, v64).n64_u64[0];
  v68.n64_u64[0] = vsub_f32(v56, v66).n64_u64[0];
  v69.n64_u64[0] = vmul_f32(v67, v35).n64_u64[0];
  v70.n64_u64[0] = vmul_f32(v67, v64).n64_u64[0];
  v71.n64_u64[0] = vsub_f32(vadd_f32(v68, v69), vmul_f32(v70, v36)).n64_u64[0];
  v69.n64_u32[0] = vdup_lane_s32(v63, 1).n64_u32[0];
  v69.n64_f32[1] = v37;
  v72.n128_u64[0] = vadd_f32(v71, vmul_f32(vmul_f32(v64, v70), v38)).n64_u64[0];
  v73.n128_u64[0] = v72.n128_u64[0];
  v74.n128_u64[0] = vmul_n_f32(v69, v53 + (f32)((f32)(v46 * v52) * 0.00015148419)).n64_u64[0];
  v73.n128_u64[1] = v72.n128_u64[0];
  v75 = vrev64q_s32(v74);
  v72.n128_u64[1] = v72.n128_u64[0];
  v76 = vzip1q_s32(v74, v75);
  v75.n128_u64[0] = vmul_f32(v63, vext_s8(v69, v63, 4u)).n64_u64[0];
  v77 = vmulq_f32(vrev64q_s32(v72), v76);
  v78 = vmulq_f32(v73, vzip1q_s32(v75, vrev64q_s32(v75)));
  vct_A = (struct sdfVector4_t)vtrn2q_s32(vrev64q_s32(vaddq_f32(v78, v77)), vsubq_f32(v78, v77));
}

// 0x2267480
void LookAt(f32 aFrontX, f32 aFrontZ) {
  f32 *p_x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  __int128 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v29;
  f32 v31;
  f32 v32;
  Il2CppMethodPointer virtualMethodPointer;
  f32 v34;

  p_x = &vf00.x;
  v8 = p_x[6];
  v9 = p_x[4];
  if (aFrontZ >= 0.0)
    v10 = p_x[5];
  else
    v10 = -p_x[5];
  v11 = (f32)(v9 * v9) + (f32)(v8 * v8);
  if (v11 < 0.000001)
  {
    if (v10 < 0.0)
    {
      v15 = xmmword_3D05F80;
LABEL_30:
      vct_A = (struct sdfVector4_t)v15;
      return;
    }
    v15 = xmmword_3D00750;
    goto LABEL_30;
  }
  v16 = sqrtf(v11);
  v34 = aFrontX;
  v17 = v16 + sqrtf((f32)(v10 * v10) + v11);
  v18 = sqrtf((f32)(v10 * v10) + (f32)(v17 * v17));
  v19 = 1.0 / v18;
  v21 = v10 * v19;
  v22 = v17 * v19;
  v23 = 1.0;
  vct_A.x = v21;
  vct_A.y = 0.0;
  vct_A.z = 0.0;
  vct_A.w = v22;
  v25 = v34 - (f32)(v9 * (f32)(1.0 / v16));
  v26 = (f32)(v8 * (f32)(1.0 / v16)) + aFrontZ;
  v27 = (f32)(v25 * v25) + (f32)(v26 * v26);
  if (v27 < 0.000001)
  {
    v29 = 0.0;
    goto LABEL_35;
  }
  v31 = sqrtf(v27);
  v32 = 1.0 / v31;
  v29 = v26 * v32;
  v23 = v25 * v32;
LABEL_35:
  virtualMethodPointer = *((MethodInfo *)SDF_VU0 + 2).virtualMethodPointer;
  *((f32 *)virtualMethodPointer + 9) = v23;
  *((f32 *)virtualMethodPointer + 11) = v29;
  *((u32 *)virtualMethodPointer + 8) = 0;
  *((u32 *)virtualMethodPointer + 10) = 0;
  Mult();
}

// 0x2267880
void Slerp(f32 aRatio) {
  int32x2_t v5;
  int32x2_t v6;
  f32 v7;
  float32x4_t v8;
  f32 v9;
  f32 v10;
  f32 v11;
  s32 v12;
  f32 *sdfSinTable_local;
  s32 max_length;
  u32 v15;
  s32 v16;
  f32 v17;
  s32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v62;

  v5.n64_u64[0] = vmul_f32(*(float32x2_t *)&vct_A.x, (float32x2_t)vct_B.n128_u64[0]).n64_u64[0];
  v6.n64_u64[0] = vmul_f32(*(float32x2_t *)&vct_A.z, (float32x2_t)vextq_s8(vct_B, vct_B, 8u).n128_u64[0]).n64_u64[0];
  v7 = vadd_f32(vdup_lane_s32(v6, 1), vadd_f32(v6, vadd_f32(v5, vdup_lane_s32(v5, 1)))).n64_f32[0];
  if (v7 >= 0.0)
  {
    v60 = v7;
    v7 = v60;
    v8 = vct_B;
  }
  else
  {
    v59 = v7;
    v7 = v59;
    v7 = -v7;
    v8 = vnegq_f32(vct_B);
  }
  vct_C = (struct sdfVector4_t)v8;
  v9 = 1.0 - aRatio;
  if (v7 < 0.999)
  {
    v10 = -v7;
    v11 = 0.0;
    if (v7 >= 0.0)
      v10 = v7;
    if (v10 >= 1.0)
      goto LABEL_30;
    v12 = 0;
    sdfSinTable_local = sdfSinTable;
    max_length = sdfSinTable_local->max_length;
    do
    {
      v15 = max_length + v12;
      v16 = (max_length + v12) >> 1;
      v17 = sdfSinTable_local[v16];
      v18 = v16;
      if (v17 <= v10)
      {
        v12 = v16 + 1;
        v18 = max_length;
      }
      max_length = v18;
    }
    while (v12 < v18);
    v19 = 0.0;
    if (v15 >= 2)
      v19 = *((f32 *)&sdfSinTable_local->max_length + ((s64)(s32)v15 >> 1) + 1);
    v11 = (f32)(1.0 - (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfSinTable_local->max_length)) * (f32)v16) + (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfSinTable_local->max_length)) * (f32)(v10 - v19)) / (f32)(v17 - v19))))
        * 1.5708;
LABEL_30:
    v20 = -v11;
    if (v7 >= 0.0)
      v20 = v11;
    v21 = v20 * 0.15915494;
    v22 = (s32)(v20 * 0.15915494);
    if ((f32)(v20 * 0.15915494) == INFINITY)
      v22 = -2147500000.0;
    v23 = (f32)(v9 * v20) * 0.15915494;
    v24 = (f32)(v21 - v22) + 1.0;
    v25 = (f32)(v21 - v22) + -1.0;
    if ((f32)(v21 - v22) >= -0.5)
      v24 = v21 - v22;
    if ((f32)(v21 - v22) <= 0.5)
      v25 = v24;
    v26 = -0.5 - v25;
    if (v25 >= -0.25)
      v26 = v25;
    if (v25 > 0.25)
      v26 = 0.5 - v25;
    if (v23 == INFINITY)
      v27 = -2147500000.0;
    else
      v27 = (s32)v23;
    v28 = v23 - v27;
    v29 = v28 + 1.0;
    if (v28 >= -0.5)
      v29 = v28;
    if (v28 > 0.5)
      v30 = v28 + -1.0;
    else
      v30 = v29;
    v31 = -0.5 - v30;
    if (v30 >= -0.25)
      v31 = v30;
    v32 = v26 * 4.0;
    if (v30 > 0.25)
      v31 = 0.5 - v30;
    v33 = v31 * 4.0;
    v34 = v32 * v32;
    v35 = v32 * 1.5708;
    v36 = v32 * (f32)(v32 * v32);
    v37 = v36 * -0.6459637;
    v38 = v34 * v36;
    v39 = v38 * 0.07968968;
    v40 = v34 * v38;
    v41 = v33 * 1.5708;
    v42 = v40 * -0.0046737655;
    v43 = (f32)(v34 * v40) * 0.00015148419;
    v44 = v33 * v33;
    v45 = (f32)((f32)(v35 + v37) + v39) + v42;
    v46 = v33 * (f32)(v33 * v33);
    v47 = v46 * -0.6459637;
    v48 = v44 * v46;
    v49 = v48 * 0.07968968;
    v50 = v44 * v48;
    v51 = v44 * v50;
    v52 = (f32)((f32)(v41 + v47) + v49) + (f32)(v50 * -0.0046737655);
    v53 = (f32)(v20 * aRatio) * 0.15915494;
    v54 = (s32)v53;
    if (v53 == INFINITY)
      v54 = -2147500000.0;
    v55 = v53 - v54;
    if (v55 <= 0.5)
    {
      if (v55 < -0.5)
        v55 = v55 + 1.0;
    }
    else
    {
      v55 = v55 + -1.0;
    }
    v56 = v45 + v43;
    if (v55 <= 0.25)
    {
      if (v55 < -0.25)
        v55 = -0.5 - v55;
    }
    else
    {
      v55 = 0.5 - v55;
    }
    v57 = v55 * 4.0;
    v9 = (f32)(v52 + (f32)(v51 * 0.00015148419)) / v56;
    v58 = v57 * v57;
    aRatio = (f32)((f32)((f32)((f32)((f32)((f32)(v55 * 4.0) * 1.5708) + (f32)((f32)(v57 * (f32)(v57 * v57)) * -0.6459637)) + (f32)((f32)((f32)(v57 * v57) * (f32)(v57 * (f32)(v57 * v57))) * 0.07968968)) + (f32)((f32)(v58 * (f32)(v58 * (f32)(v57 * (f32)(v57 * v57)))) * -0.0046737655)) + (f32)((f32)(v58 * (f32)(v58 * (f32)(v58 * (f32)(v57 * (f32)(v57 * v57))))) * 0.00015148419))
           / v56;
  }
  v62 = v9;
  v9 = v62;
  vct_A = (struct sdfVector4_t)vaddq_f32(vmulq_n_f32((float32x4_t)vct_A, v9), vmulq_n_f32((float32x4_t)vct_C, aRatio));
  Normalize();
}

// 0x2267de0
void Lerp(f32 aRatio) {
  int32x2_t v6;
  int32x2_t v7;

  v6.n64_u64[0] = vmul_f32(*(float32x2_t *)&vct_A.x, (float32x2_t)vct_B.n128_u64[0]).n64_u64[0];
  v7.n64_u64[0] = vmul_f32(*(float32x2_t *)&vct_A.z, (float32x2_t)vextq_s8(vct_B, vct_B, 8u).n128_u64[0]).n64_u64[0];
  if (vadd_f32(vdup_lane_s32(v7, 1), vadd_f32(v7, vadd_f32(v6, vdup_lane_s32(v6, 1)))).n64_f32[0] >= 0.0)
  {
    vct_C = vct_B;
    goto LABEL_15;
  }
  else
  {
    vct_C = (struct sdfVector4_t)vnegq_f32(vct_B);
  }
LABEL_15:
  vct_A = (struct sdfVector4_t)vaddq_f32(vmulq_n_f32((float32x4_t)vct_A, 1.0 - aRatio), vmulq_n_f32((float32x4_t)vct_C, aRatio));
  Normalize();
}

// 0x2267f50
f32 EulerAngleAxisY(void) {
  __int128 v4;
  __int128 v5;
  _OWORD *p_m00;
  __int128 v7;
  __int128 v8;
  __int128 v9;
  s64 v12;
  long f64 v14;
  sdfMatrix4_t v16;
  sdfMatrix4_t v17;
  sdfMatrix4_t v18;
  sdfVector4_t Row;
  sdfVector4_t v20;

  Rotate(&v18, (sdfQuaternion_t)vct_A, 0);
  v4 = *(_OWORD *)&v18.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v18.m00;
  *(_OWORD *)&mtx_A.m01 = v4;
  v5 = *(_OWORD *)&v18.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v18.m02;
  *(_OWORD *)&mtx_A.m03 = v5;
  p_m00 = &IdentityMatrix.m00;
  v7 = p_m00[2];
  v8 = p_m00[3];
  v9 = p_m00[1];
  *(_OWORD *)&v16.m00 = *p_m00;
  *(_OWORD *)&v16.m01 = v9;
  *(_OWORD *)&v16.m02 = v7;
  *(_OWORD *)&v16.m03 = v8;
  Row = GetRow(&v16, 0, 0);
  vct_A = Row;
  vct_A.w = 0.0;
  get_transpose(&v18, &mtx_A, 0);
  v17 = v18;
  v20 = op_Multiply_60923920(&v17, vct_A, 0);
  vct_A = v20;
  v14 = sub_18E6660(0, v12);
  return *(f32 *)&v14;
}
