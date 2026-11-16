#include "types.h"
#include "TNEFFECT_BLEND.h"
#include "eff.h"
#include "sdf_vu0.h"
#include "sdfdraw.h"

#define ap 0.5

typedef struct SDF_GS_ALPHA SDF_GS_ALPHA;
typedef struct SDF_GS_TEST SDF_GS_TEST;
typedef struct sdf3DScreenParam_t sdf3DScreenParam_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;

s32 camID;
sdfGrOt_t **pOt_Table;
static SDF_GS_ALPHA *alphaTable;
ScreenParamFunc *ScreenParam;
CameraObjectFunc *cameraObject;
CameraTMFunc *CameraTM;
CameraTargetPosFunc *CameraTargetPos;
CameraEyePosFunc *CameraEyePos;
CameraUpVectorFunc *CameraUpVector;
static sdfVector4_t alpha;

// 0x1997670
sdfGrOt_t *effOtGet(TNEFFECT_BLEND blend) {
  return pOt_Table[camID][blend];
}

// 0x199e3b0
sdf3DScreenParam_t *effGetSelScreenParam(void) {
  ScreenParamFunc v2;

  v2 = ScreenParam[camID];
  return ((sdf3DScreenParam_t *(intptr_t, intptr_t))v2->invoke_impl)(v2->method_code, v2->method);
}

// 0x199e430
void *effGetSelCameraObject(void) {
  CameraObjectFunc v2;

  v2 = cameraObject[camID];
  return ((void *(intptr_t, intptr_t))v2->invoke_impl)(v2->method_code, v2->method);
}

// 0x199e4b0
sdfMatrix4_t effGetSelCameraTM(void) {
  CameraTMFunc v4;
  sdfMatrix4_t *result;
  __int128 v6;
  __int128 v7;
  _OWORD v8[4];

  v4 = CameraTM[camID];
  result = ((sdfMatrix4_t *(_OWORD *__return_ptr, intptr_t, intptr_t))v4->invoke_impl)(v8, v4->method_code, v4->method);
  v6 = v8[1];
  *(_OWORD *)&retstr->m00 = v8[0];
  *(_OWORD *)&retstr->m01 = v6;
  v7 = v8[3];
  *(_OWORD *)&retstr->m02 = v8[2];
  *(_OWORD *)&retstr->m03 = v7;
  return result;
}

// 0x199e550
sdfVector4_t effGetSelCameraTargetPos(void) {
  CameraTargetPosFunc v2;

  v2 = CameraTargetPos[camID];
  return (v2->invoke_impl)(v2->method_code, v2->method);
}

// 0x199e5d0
sdfVector4_t effGetSelCameraEyePos(void) {
  CameraEyePosFunc v2;

  v2 = CameraEyePos[camID];
  return (v2->invoke_impl)(v2->method_code, v2->method);
}

// 0x199e650
sdfVector4_t effGetSelCameraUpVector(void) {
  CameraUpVectorFunc v2;

  v2 = CameraUpVector[camID];
  return (v2->invoke_impl)(v2->method_code, v2->method);
}

// 0x199e6d0
bool effScreenOffsetClipGet(void) {
  ScreenParamFunc v3;
  s64 v4;
  CameraEyePosFunc v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 *p_x;
  f32 *v17;
  f32 z;
  f32 x;
  f32 y;
  CameraTMFunc v26;
  s32 v28;
  long f64 *v29;
  __int128 v30;
  long f64 v31;
  __int128 v32;
  u64 v36;
  long f64 *v38;
  __int128 v40;
  long f64 v41;
  __int128 v42;
  struct sdfVector4_t v47;
  struct sdfVector4_t v48;
  long f64 v52;
  long f64 v53;
  sdfMatrix4_t v58;
  sdfMatrix4_t v59;
  sdfVector4_t v60;
  sdfMatrix4_t v61;

  v3 = ScreenParam[camID];
  v4 = (v3->invoke_impl)(v3->method_code, v3->method);
  vct_C = vct_A;
  v7 = CameraEyePos[camID];
  v8 = (v7->invoke_impl)(v7->method_code, v7->method);
  v10 = v9;
  v12 = v11;
  v14 = v13;
  p_x = &vf00.x;
  p_x[8] = v8;
  p_x[9] = v10;
  p_x[10] = v12;
  p_x[11] = v14;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v17 = &vf00.x;
  z = v17[6];
  x = v17[4];
  y = v17[5];
  if (sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z)) <= 16.0)
    return 0;
  sub_1949110(0);
  vct_B = vct_A;
  v26 = CameraTM[camID];
  (v26->invoke_impl)(&v59, v26->method_code, v26->method);
  v61 = v59;
  v28 = (u8)byte_575642E;
  mtx_A = v61;
  if (v28)
  {
    goto LABEL_29;
  }
  else
  {
    goto LABEL_29;
  }
LABEL_29:
  v29 = (long f64 *)&vf00.x;
  v30 = *((_OWORD *)v29 + 5);
  v29[8] = v29[4];
  *((_OWORD *)v29 + 9) = v30;
  v31 = v29[6];
  v32 = *((_OWORD *)v29 + 7);
  v29[10] = v31;
  *((_OWORD *)v29 + 11) = v32;
  sub_1996630(0, v31);
  vct_A = GetRow(&mtx_A, 2, 0);
  sub_1949110(0);
  v36 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  if ((f32)(*((f32 *)&v36 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v36)) > 0.25)
  {
    vct_A = vct_C;
    v38 = (long f64 *)&vf00.x;
    v40 = *((_OWORD *)v38 + 9);
    v38[4] = v38[8];
    *((_OWORD *)v38 + 5) = v40;
    v41 = v38[10];
    v42 = *((_OWORD *)v38 + 11);
    v38[6] = v41;
    *((_OWORD *)v38 + 7) = v42;
    sub_19636F0(v4 + 56, 0, v41);
    vct_A.w = 1.0;
    get_transpose(&v59, &mtx_A, 0);
    v58 = v59;
    v60 = op_Multiply_60923920(&v58, vct_A, 0);
    vct_A.x = v60.x * (f32)(1.0 / v60.w);
    vct_A.y = v60.y * (f32)(1.0 / v60.w);
    vct_A.z = v60.z * (f32)(1.0 / v60.w);
    vct_A.w = 1.0 / v60.w;
    v47 = *(sdfVector4_t *)(v4 + 120);
    vct_B = v47;
    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v48 = *(sdfVector4_t *)(v4 + 136);
    vct_B = v48;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    return 1;
  }
  return 0;
}

// 0x199c110
f32 effScreenAreaGet(f32 area) {
  CameraEyePosFunc v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 *p_x;
  CameraUpVectorFunc v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 *v31;
  int32x2_t v33;
  int32x2_t v34;
  float32x2_t v35;
  float32x2_t v36;
  int32x4_t v38;
  f32 x;
  f32 y;
  f32 v43;
  f32 v44;
  struct sdfVector4_t v50;

  if (!effScreenOffsetClipGet())
    return 0.0;
  v50 = vct_A;
  vct_C = vct_A;
  v11 = CameraEyePos[camID];
  v12 = (v11->invoke_impl)(v11->method_code, v11->method);
  v14 = v13;
  v16 = v15;
  v18 = v17;
  p_x = &vf00.x;
  p_x[8] = v12;
  p_x[9] = v14;
  p_x[10] = v16;
  p_x[11] = v18;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v22 = CameraUpVector[camID];
  v23 = (v22->invoke_impl)(v22->method_code, v22->method);
  v25 = v24;
  v27 = v26;
  v29 = v28;
  v31 = &vf00.x;
  v31[8] = v23;
  v31[9] = v25;
  v31[10] = v27;
  v31[11] = v29;
  v33.n64_u64[0] = *(u64 *)&vct_B.y;
  v34.n64_u64[0] = *(u64 *)&vct_A.y;
  v35.n64_u32[0] = vdup_lane_s32(v33, 1).n64_u32[0];
  v36.n64_u32[0] = vdup_lane_s32(v34, 1).n64_u32[0];
  v35.n64_u32[1] = LODWORD(vct_B.x);
  v36.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v36.n64_f32[1] * v33.n64_f32[0]) - (f32)(v35.n64_f32[1] * v34.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v34, v35), vmul_f32(v36, v33));
  sub_1949110(0);
  v38 = vzip1q_s32((int32x4_t)LODWORD(area), (int32x4_t)LODWORD(area));
  v38.n128_f32[2] = area;
  vct_B = (struct sdfVector4_t)v38;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_B = vct_C;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  if (effScreenOffsetClipGet())
  {
    x = vct_A.x;
    y = vct_A.y;
    v43 = v50.y;
    v44 = y - v43;
    vct_A = v50;
    return sqrtf((f32)((f32)(x - v50.x) * (f32)(x - v50.x)) + (f32)(v44 * v44));
  }
  return 0.0;
}

// 0x199f090
sdfVector4_t effHermitianSpline(sdfVector4_t *pVertex, f32 percentage) {
  f32 z;
  f32 v7;
  float32x2_t v8;
  float32x2_t v9;
  float32x2_t v10;
  f32 v11;
  f32 v12;
  f32 v13;
  float32x2_t v14;
  float32x2_t v15;
  float32x2_t *static_fields;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  float32x2_t v26;
  sdfVector4_t result;

  z = pVertex[1].z;
  v7 = pVertex[0].z;
  v8.n64_u64[0] = *(u64 *)&pVertex[1].x;
  v9.n64_u64[0] = *(u64 *)&pVertex[0].x;
  v10.n64_u64[0] = *(u64 *)&pVertex[2].x;
  v11 = pVertex[2].z;
  v12 = pVertex[1].z;
  v13 = pVertex[2].z;
  v14.n64_u64[0] = *(u64 *)&pVertex[2].x;
  v15.n64_u64[0] = *(u64 *)&pVertex[1].x;
  v17 = (f32)(percentage * percentage) * percentage;
  v18 = (f32)(percentage * percentage) * 3.0;
  v19 = (f32)((f32)(v17 + v17) - v18) + 1.0;
  v20 = v17 - (f32)(percentage * percentage);
  v21 = v17 - (f32)((f32)(percentage * percentage) + (f32)(percentage * percentage));
  v22 = v18 - (f32)(v17 + v17);
  v23 = v21 + percentage;
  result.z = (f32)(v22 * v13)
                  + (f32)((f32)((f32)(v23 * (f32)((f32)((f32)(z - v7) + (f32)(v11 - z)) * static_fields[10].n64_f32[0])) + (f32)(v19 * v12)) + (f32)(v20 * (f32)(static_fields[10].n64_f32[0] * (f32)((f32)(v13 - v12) + (f32)(pVertex[3].z - v13)))));
  result.w = 0.0;
  v26.n64_u64[0] = vadd_f32(vmul_n_f32(v14, v22), vadd_f32(vadd_f32(vmul_n_f32(vmul_f32(vadd_f32(vsub_f32(v8, v9), vsub_f32(v10, v8)), static_fields[9]), v23), vmul_n_f32(v15, v19)), vmul_n_f32(vmul_f32(static_fields[9], vadd_f32(vsub_f32(v14, v15), vsub_f32(*(float32x2_t *)&pVertex[3].x, v14))), v20))).n64_u64[0];
  LODWORD(result.y) = v26.n64_u32[1];
  result.x = v26.n64_f32[0];
  return result;
}

// 0x199f220
void effMatrixToQuat(const sdfMatrix4_t *pMatrix) {
  f32 Item_60922080;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  _BOOL4 v8;
  f32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  f32 v15;
  s32 v16;
  f32 v17;
  f32 v18;
  f32 x;
  f32 w;
  f32 *v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 *p_z;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 *p_y;
  f32 v34;
  f32 v35;
  f32 *v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  void *v43;
  void *v44;
  char *v45;
  void *v46;
  u8 v47[4];
  f32 z;
  f32 y;
  f32 v50;

  Item_60922080 = get_Item_60922080(pMatrix, 0, 0);
  v4 = get_Item_60922080(pMatrix, 5, 0);
  v5 = get_Item_60922080(pMatrix, 10, 0);
  v6 = (f32)((f32)(Item_60922080 + v4) + v5) + get_Item_60922080(pMatrix, 15, 0);
  if (v6 >= 1.0)
  {
    v23 = sqrtf(v6);
    v24 = v23 + v23;
    w = (f32)(v23 + v23) * -0.25;
    v25 = get_Item_60922080(pMatrix, 9, 0);
    v50 = (f32)(v25 - get_Item_60922080(pMatrix, 6, 0)) / v24;
    v26 = get_Item_60922080(pMatrix, 2, 0);
    y = (f32)(v26 - get_Item_60922080(pMatrix, 8, 0)) / v24;
    v27 = get_Item_60922080(pMatrix, 4, 0);
    z = (f32)(v27 - get_Item_60922080(pMatrix, 1, 0)) / v24;
  }
  else
  {
    v7 = get_Item_60922080(pMatrix, 0, 0);
    v8 = v7 <= get_Item_60922080(pMatrix, 5, 0);
    v9 = get_Item_60922080(pMatrix, 10, 0);
    if (v9 <= get_Item_60922080(pMatrix, v8 | (4 * v8), 0))
      v10 = v8;
    else
      v10 = 2;
    v11 = 4 * v10;
    if ((u32)(v10 + 1) < 3)
      v12 = v10 + 1;
    else
      v12 = v10 - 2;
    if ((u32)(v12 + 1) < 3)
      v13 = v12 + 1;
    else
      v13 = v12 - 2;
    v14 = 4 * v12;
    v15 = get_Item_60922080(pMatrix, 5 * v10, 0);
    v16 = 4 * v13;
    v17 = get_Item_60922080(pMatrix, 5 * v12, 0);
    v18 = (f32)((f32)(v15 - v17) - get_Item_60922080(pMatrix, 5 * v13, 0)) + 1.0;
    x = zeroVector.x;
    y = zeroVector.y;
    v50 = x;
    w = zeroVector.w;
    z = zeroVector.z;
    if (v18 != 0.0)
    {
      v28 = sqrtf(v18);
      if (v10)
      {
        if (v10 == 2)
          p_z = &z;
        else
          p_z = &y;
      }
      else
      {
        p_z = &v50;
      }
      v30 = v28 + v28;
      *p_z = (f32)(v28 + v28) * 0.25;
      v31 = get_Item_60922080(pMatrix, v12 + v11, 0);
      v32 = get_Item_60922080(pMatrix, v14 + v10, 0);
      p_y = &v50;
      switch (v12)
      {
        case 0:
          break;
        case 1:
          p_y = &y;
          break;
        case 2:
          p_y = &z;
          break;
        case 3:
          p_y = v47;
          break;
        default:
LABEL_46:
          v43 = InitializedMetadata(&System_IndexOutOfRangeException);
          v44 = Allocate(v43);
          v45 = InitializedMetadata(&"Invalid Vector4 index!");
          v46 = InitializedMetadata(&Method_UnityEngine_Vector4_set_Item__);
      }
      *p_y = (f32)(v31 + v32) / v30;
      v34 = get_Item_60922080(pMatrix, v13 + v11, 0);
      v35 = get_Item_60922080(pMatrix, v16 + v10, 0);
      v36 = &v50;
      switch (v13)
      {
        case 0:
          goto LABEL_38;
        case 1:
          v36 = &y;
          goto LABEL_38;
        case 2:
          v36 = &z;
          goto LABEL_38;
        case 3:
          v36 = v47;
LABEL_38:
          *v36 = (f32)(v34 + v35) / v30;
          v37 = get_Item_60922080(pMatrix, v16 + v12, 0);
          w = (f32)-(f32)(v37 - get_Item_60922080(pMatrix, v13 + v14, 0)) / v30;
          goto LABEL_39;
        default:
          goto LABEL_46;
      }
    }
    if (v10)
    {
      if (v10 == 2)
        v22 = &z;
      else
        v22 = &y;
    }
    else
    {
      v22 = &v50;
    }
    *v22 = 1.0;
  }
LABEL_39:
  v38 = z;
  v40 = y;
  v39 = v50;
  vct_A.x = v39;
  vct_A.y = v40;
  vct_A.z = v38;
  vct_A.w = w;
}

// 0x19976f0
void effZTestOff(sdfDrawTag_t *drawTag, bool sw) {
  void *v5;
  void **p_SET_10AADD11;
  void *v8;

  if (sw)
    return;
  v5 = Allocate(Project_libsdf_sdfPrimTestPacket_t);
  _ctor(v5, 0);
  p_SET_10AADD11 = &SET_10AADD11;
  v8 = *p_SET_10AADD11;
  v5->test = (SDF_GS_TEST *)*p_SET_10AADD11;
  sdfDrawTagLink(drawTag, v5);
}

// 0x19977c0
void effZTestOn(sdfDrawTag_t *drawTag, bool sw) {
  void *v5;

  if (!sw)
    return;
  v5 = Allocate(Project_libsdf_sdfPrimTestPacket_t);
  _ctor(v5, 0);
  v5->test = SET_10AADD12;
  sdfDrawTagLink(drawTag, v5);
}

// 0x199f720
void effSetAlphaPacket(sdfDrawTag_t *drawTag, TNEFFECT_BLEND blend) {
  void *v5;
  SDF_GS_ALPHA *v7;

  v5 = Allocate(Project_libsdf_sdfPrimAlphaPacket_t);
  _ctor(v5, 0);
  v7 = alphaTable[blend];
  v5->alpha = v7;
  sdfDrawTagLink(drawTag, v5);
}

// 0x199f7e0
void effSetTestAlphaPacket(sdfDrawTag_t *drawTag, SDF_GS_TEST *test, SDF_GS_ALPHA *alpha) {
  sdfPrimTransPacket_t *v7;

  v7 = Allocate(sdfPrimTransPacket_t);
  _ctor(v7, 0);
  v7->test = test;
  v7->alpha = alpha;
  sdfDrawTagLink(drawTag, v7);
}
