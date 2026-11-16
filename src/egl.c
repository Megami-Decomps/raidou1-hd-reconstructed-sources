#include "types.h"
#include "dds3kerneldraw.h"
#include "egl.h"
#include "fld.h"
#include "kernel.h"
#include "sdfdraw.h"
#include "sdfmat.h"
#include "sdfprim.h"
#include "sdfsystem.h"
#include "sdftex.h"
#include "sdfvsync.h"

typedef struct JobData JobData;
typedef struct SDF_GS_ALPHA SDF_GS_ALPHA;
typedef struct SDF_GS_TEST SDF_GS_TEST;
typedef struct sdfGrOt_t sdfGrOt_t;

s32 OT_Offset;
sdfGrOt_t *currentOt;
static void *mesh;
static void *mesh2D;
static JobData *data;
static SDF_GS_ALPHA *alphaTbl;

static void *GetMaterial(bool isEffect);
static void SetJob(void);

// 0x22a31b0
void eglInit(void) {
  ;
}

// 0x22a31c0
void eglSetOt(DDS3_OT ot) {
  sdfGrOt_t *v6;

  OT_Offset = ot;
  v6 = Ot[ot];
  currentOt = v6;
}

// 0x22a32a0
void eglLinkTest(SDF_GS_TEST *test) {
  sdfDrawTag_t *v5;
  void *v6;

  if (drawSkip)
    return;
  v5 = sdfPrimAllocDrawTag();
  v6 = Allocate(Project_libsdf_sdfPrimTestPacket_t);
  _ctor(v6, 0);
  v6->test = test;
  sdfDrawTagLink(v5, v6);
  sdfDrawTagLinkOt(currentOt, v5);
}

// 0x22a3410
void eglLinkAlpha(s32 mode) {
  sdfDrawTag_t *v5;
  void *v6;
  SDF_GS_ALPHA *v8;

  if (drawSkip)
    return;
  v5 = sdfPrimAllocDrawTag();
  v6 = Allocate(Project_libsdf_sdfPrimAlphaPacket_t);
  _ctor(v6, 0);
  if (SLODWORD(alphaTbl->max_length) <= mode)
    mode = 0;
  v8 = alphaTbl[mode];
  v6->alpha = v8;
  sdfDrawTagLink(v5, v6);
  sdfDrawTagLinkOt(currentOt, v5);
}

// 0x22a35d0
void eglLinkSpriteF(f32 x, f32 y, f32 w, f32 h, s32 u, s32 v, s32 uw, s32 vh, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3, void *th) {
  s32 rgba;
  s32 v19;
  s32 v20;
  s32 v21;
  u32 v27;
  s32 v28;
  u32 v29;
  s32 v30;
  u32 v31;
  u32 v32;
  u32 v33;
  void *v34;
  f32 v36;
  f32 v37;
  f32 v39;
  void *m_ListData;
  s64 v41;
  f32 v42;
  s32 v43;
  f32 v44;
  s32 v45;
  f32 v47;
  s32 v48;
  f32 v49;
  u32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  CommonMesh_MeshEditPCU_Form value;
  sdfVector3_t VertexPos_36166560;
  sdfVector3_t v60;
  sdfVector3_t v61;
  sdfVector3_t v62;

  rgba = rgba3->rgba;
  v19 = rgba2->rgba;
  v20 = rgba1->rgba;
  v21 = rgba0->rgba;
  if (drawSkip)
    return;
  v57 = rgba;
  v55 = v20;
  v56 = v19;
  v27 = vcvts_n_s32_f32(y, 3u) + 30976;
  if ((f32)(y * 8.0) == INFINITY)
    v28 = -2147452672;
  else
    v28 = v27;
  v29 = vcvts_n_s32_f32(x, 4u) + 28672;
  if ((f32)(x * 16.0) == INFINITY)
    v30 = -2147454976;
  else
    v30 = v29;
  v31 = vcvts_n_s32_f32(w, 4u);
  if ((f32)(w * 16.0) == INFINITY)
    v32 = 0x80000000;
  else
    v32 = v31;
  v33 = vcvts_n_s32_f32(h, 3u);
  if ((f32)(h * 8.0) == INFINITY)
    v33 = 0x80000000;
  v54 = v33;
  v34 = th;
  v36 = sdfTexScale(v34);
  v37 = (v34->klass->vtable._5_get_width.methodPtr)(v34, v34->klass->vtable._5_get_width.method);
  v39 = v36
      / (f32)(v34->klass->vtable._7_get_height.methodPtr)(v34, v34->klass->vtable._7_get_height.method);
  m_ListData = data->vertexPCU.m_ListData;
  v41 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__get_Length__ + 4);
  if ((*(u16 *)(v41 + 309) & 1) == 0)
    sub_42269C(v41);
  v42 = v36 / v37;
  eglAddMeshSquareIdx(m_ListData->m_length);
  v43 = uw + u;
  v44 = v42 * (f32)u;
  v45 = v32 + v30;
  VertexPos_36166560 = GetVertexPos_36166560(v30, v28, 0);
  value.position = VertexPos_36166560;
  value.color.rgba = v21;
  *(f32 *)&value.color.r = v44;
  value.uv.x = 1.0 - (f32)(v39 * (f32)v);
  v47 = v42 * (f32)v43;
  v48 = v54 + v28;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  v60 = GetVertexPos_36166560(v45, v28, 0);
  value.position = v60;
  *(f32 *)&value.color.r = v47;
  value.uv.x = 1.0 - (f32)(v39 * (f32)v);
  value.color.rgba = v55;
  v49 = v39 * (f32)(uw + v);
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  v61 = GetVertexPos_36166560(v30, v48, 0);
  value.position = v61;
  value.color.rgba = v56;
  *(f32 *)&value.color.r = v44;
  value.uv.x = 1.0 - v49;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  v62 = GetVertexPos_36166560(v45, v48, 0);
  value.position = v62;
  *(f32 *)&value.color.r = v47;
  value.uv.x = 1.0 - v49;
  value.color.rgba = v57;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  (mesh->klass->vtable._7_SetTexture.methodPtr)(mesh, v34, mesh->klass->vtable._7_SetTexture.method);
  SetRange_36166880(mesh2D, 0xFFFFFFu, 0);
}

// 0x22a3f20
void LinkSpriteF(f32 x, f32 y, f32 w, f32 h, s32 u, s32 v, s32 uw, s32 vh, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2, const sdfVector4_t *rgba3, void *th) {
  f32 z;
  f32 v15;
  void *v16;
  int8x16_t v22;
  int8x8_t v23;
  int8x8_t v24;
  int8x8_t v25;
  int8x8_t v26;
  u64 v27;
  u64 v28;
  int8x16_t v29;
  int8x16_t v30;
  u64 v31;
  int8x16_t v32;
  u64 v33;
  int8x16_t v34;
  uint64x2_t v35;
  uint64x2_t v36;
  uint64x2_t v37;
  uint64x2_t v38;
  sdfColor32_t v39;
  sdfColor32_t v40;
  sdfColor32_t v41;
  sdfColor32_t v42;
  f32 v43;
  f32 v44;
  s64 v49;
  s64 v50;

  v44 = rgba0->w;
  v43 = rgba0->y;
  z = rgba0->z;
  v15 = rgba0->x;
  v16 = *(void *)&rgba1->x;
  v22.n128_u64[0] = 255;
  v22.n128_u64[1] = 255;
  v23.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(HIDWORD(th), HIDWORD()), 7u).n64_u64[0];
  v24.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(rgba3->y), LODWORD(rgba3->w)), 7u).n64_u64[0];
  v25.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(HIDWORD(v49), HIDWORD(v50)), 7u).n64_u64[0];
  v26.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(v43), LODWORD(v44)), 7u).n64_u64[0];
  v27 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(HIDWORD(th), HIDWORD()), (float32x2_t)0x4300000043000000LL)), v23, v23).n64_u64[0];
  v28 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(HIDWORD(v49), HIDWORD(v50)), (float32x2_t)0x4300000043000000LL)), v25, v25).n64_u64[0];
  v29.n128_u64[0] = (u32)v27;
  v29.n128_u64[1] = HIDWORD(v27);
  v30 = v29;
  v31 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(rgba3->y), LODWORD(rgba3->w)), (float32x2_t)0x4300000043000000LL)), v24, v24).n64_u64[0];
  v29.n128_u64[0] = (u32)v28;
  v29.n128_u64[1] = HIDWORD(v28);
  v32 = v29;
  v33 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(v43), LODWORD(v44)), (float32x2_t)0x4300000043000000LL)), v26, v26).n64_u64[0];
  v29.n128_u64[0] = (u32)v31;
  v29.n128_u64[1] = HIDWORD(v31);
  v34 = v29;
  v29.n128_u64[0] = (u32)v33;
  v29.n128_u64[1] = HIDWORD(v33);
  v35 = vshlq_u64(vandq_s8(v30, v22), (uint64x2_t)xmmword_3D00760);
  v36 = vshlq_u64(vandq_s8(v32, v22), (uint64x2_t)xmmword_3D00760);
  v37 = vshlq_u64(vandq_s8(v34, v22), (uint64x2_t)xmmword_3D00760);
  v38 = vshlq_u64(vandq_s8(v29, v22), (uint64x2_t)xmmword_3D00760);
  v39 = (sdfColor32_t)(v36.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(*(f32 *)&v50, 7u) << 16) | (u8)vcvts_n_s32_f32(*(f32 *)&v49, 7u) | v36.n128_u64[1]);
  v40 = (sdfColor32_t)(v35.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(*(f32 *)&7u) << 16) | (u8)vcvts_n_s32_f32(*(f32 *)&th, 7u) | v35.n128_u64[1]);
  v41 = (sdfColor32_t)(v37.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(rgba3->z, 7u) << 16) | (u8)vcvts_n_s32_f32(rgba3->x, 7u) | v37.n128_u64[1]);
  v42 = (sdfColor32_t)(v38.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(z, 7u) << 16) | (u8)vcvts_n_s32_f32(v15, 7u) | v38.n128_u64[1]);
  eglLinkSpriteF(x, y, w, h, u, v, uw, vh, v42, v41, v40, v39, v16, *(const MethodInfo **)&rgba3->z);
}

// 0x22a4210
void LinkSpriteF_2(f32 x, f32 y, f32 w, f32 h, s32 u, s32 v, s32 uw, s32 vh, u32 rgba0, u32 rgba1, u32 rgba2, u32 rgba3, void *th) {
  eglLinkSpriteF(x, y, w, h, u, v, uw, vh, (sdfColor32_t)rgba0, (sdfColor32_t)rgba1, (sdfColor32_t)rgba2, (sdfColor32_t)rgba3, th);
}

// 0x22a4340
void eglLinkSprite4F(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, s32 u, s32 v, s32 uw, s32 vh, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3, void *th) {
  s32 rgba;
  s32 v27;
  s32 v28;
  s32 v29;
  void *v35;
  f32 v37;
  f32 v38;
  f32 v40;
  void *m_ListData;
  s64 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  s32 v46;
  u32 v47;
  s32 v48;
  u32 v49;
  s32 v50;
  f32 v51;
  s32 v52;
  u32 v54;
  s32 v55;
  u32 v56;
  s32 v57;
  f32 v59;
  u32 v61;
  s32 v62;
  u32 v63;
  s32 v64;
  u32 v67;
  s32 v68;
  u32 v69;
  s32 v70;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  CommonMesh_MeshEditPCU_Form value;
  sdfVector3_t VertexPos_36166560;
  sdfVector3_t v81;
  sdfVector3_t v82;
  sdfVector3_t v83;

  rgba = rgba3->rgba;
  v27 = rgba2->rgba;
  v28 = rgba1->rgba;
  v29 = rgba0->rgba;
  if (drawSkip)
    return;
  v35 = th;
  v75 = x2;
  v76 = y2;
  v77 = x3;
  v78 = y3;
  v74 = y1;
  v37 = sdfTexScale(v35);
  v38 = (v35->klass->vtable._5_get_width.methodPtr)(v35, v35->klass->vtable._5_get_width.method);
  v40 = v37
      / (f32)(v35->klass->vtable._7_get_height.methodPtr)(v35, v35->klass->vtable._7_get_height.method);
  m_ListData = data->vertexPCU.m_ListData;
  v42 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__get_Length__ + 4);
  if ((*(u16 *)(v42 + 309) & 1) == 0)
    sub_42269C(v42);
  v72 = v40;
  v43 = v37 / v38;
  eglAddMeshSquareIdx(m_ListData->m_length);
  v44 = 1.0 - (f32)(v40 * (f32)v);
  v45 = v43 * (f32)u;
  v46 = uw + u;
  v47 = vcvts_n_s32_f32(x0, 4u) + 28672;
  if ((f32)(x0 * 16.0) == INFINITY)
    v48 = -2147454976;
  else
    v48 = v47;
  v49 = vcvts_n_s32_f32(y0, 3u) + 30976;
  if ((f32)(y0 * 8.0) == INFINITY)
    v50 = -2147452672;
  else
    v50 = v49;
  VertexPos_36166560 = GetVertexPos_36166560(v48, v50, 0);
  v51 = v46;
  value.position = VertexPos_36166560;
  v52 = uw + v;
  value.color.rgba = v29;
  *(f32 *)&value.color.r = v45;
  value.uv.x = v44;
  v73 = v45;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  v54 = vcvts_n_s32_f32(x1, 4u) + 28672;
  if ((f32)(x1 * 16.0) == INFINITY)
    v55 = -2147454976;
  else
    v55 = v54;
  v56 = vcvts_n_s32_f32(v74, 3u) + 30976;
  if ((f32)(v74 * 8.0) == INFINITY)
    v57 = -2147452672;
  else
    v57 = v56;
  v81 = GetVertexPos_36166560(v55, v57, 0);
  v59 = v72 * (f32)v52;
  value.position = v81;
  value.color.rgba = v28;
  *(f32 *)&value.color.r = v43 * v51;
  value.uv.x = v44;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  v61 = vcvts_n_s32_f32(v75, 4u) + 28672;
  if ((f32)(v75 * 16.0) == INFINITY)
    v62 = -2147454976;
  else
    v62 = v61;
  v63 = vcvts_n_s32_f32(v76, 3u) + 30976;
  if ((f32)(v76 * 8.0) == INFINITY)
    v64 = -2147452672;
  else
    v64 = v63;
  v82 = GetVertexPos_36166560(v62, v64, 0);
  value.position = v82;
  value.color.rgba = v27;
  *(f32 *)&value.color.r = v73;
  value.uv.x = 1.0 - v59;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  v67 = vcvts_n_s32_f32(v77, 4u) + 28672;
  if ((f32)(v77 * 16.0) == INFINITY)
    v68 = -2147454976;
  else
    v68 = v67;
  v69 = vcvts_n_s32_f32(v78, 3u) + 30976;
  if ((f32)(v78 * 8.0) == INFINITY)
    v70 = -2147452672;
  else
    v70 = v69;
  v83 = GetVertexPos_36166560(v68, v70, 0);
  value.position = v83;
  *(f32 *)&value.color.r = v43 * v51;
  value.uv.x = 1.0 - v59;
  value.color.rgba = rgba;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data->vertexPCU, &value);
  (mesh->klass->vtable._7_SetTexture.methodPtr)(mesh, v35, mesh->klass->vtable._7_SetTexture.method);
  SetRange_36166880(mesh2D, 0xFFFFFFu, 0);
}

// 0x22a4a30
void LinkSprite4F(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, s32 u, s32 v, s32 uw, s32 vh, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2, const sdfVector4_t *rgba3, void *th) {
  void *v18;
  int8x16_t v24;
  int8x8_t v25;
  int8x8_t v26;
  int8x8_t v27;
  int8x8_t v28;
  u64 v29;
  u64 v30;
  u64 v31;
  int8x16_t v32;
  int8x16_t v33;
  int8x16_t v34;
  u64 v35;
  uint64x2_t v36;
  uint64x2_t v37;
  uint64x2_t v38;
  uint64x2_t v39;
  sdfColor32_t v40;
  sdfColor32_t v41;
  sdfColor32_t v42;
  sdfColor32_t v43;
  s64 v52;
  s64 v53;

  v18 = *(void *)&rgba0->x;
  v24.n128_u64[0] = 255;
  v24.n128_u64[1] = 255;
  v25.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(rgba3->y), LODWORD(rgba3->w)), 7u).n64_u64[0];
  v26.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(HIDWORD(th), HIDWORD()), 7u).n64_u64[0];
  v27.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(HIDWORD(v52), HIDWORD(v53)), 7u).n64_u64[0];
  v28.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(rgba2->y), LODWORD(rgba2->w)), 7u).n64_u64[0];
  v29 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(HIDWORD(th), HIDWORD()), (float32x2_t)0x4300000043000000LL)), v26, v26).n64_u64[0];
  v30 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(HIDWORD(v52), HIDWORD(v53)), (float32x2_t)0x4300000043000000LL)), v27, v27).n64_u64[0];
  v31 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(rgba3->y), LODWORD(rgba3->w)), (float32x2_t)0x4300000043000000LL)), v25, v25).n64_u64[0];
  v32.n128_u64[0] = (u32)v29;
  v32.n128_u64[1] = HIDWORD(v29);
  v33 = v32;
  v32.n128_u64[0] = (u32)v30;
  v32.n128_u64[1] = HIDWORD(v30);
  v34 = v32;
  v35 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(rgba2->y), LODWORD(rgba2->w)), (float32x2_t)0x4300000043000000LL)), v28, v28).n64_u64[0];
  v32.n128_u64[0] = (u32)v31;
  v32.n128_u64[1] = HIDWORD(v31);
  v36 = vshlq_u64(vandq_s8(v33, v24), (uint64x2_t)xmmword_3D00760);
  v37 = vshlq_u64(vandq_s8(v34, v24), (uint64x2_t)xmmword_3D00760);
  v38 = vshlq_u64(vandq_s8(v32, v24), (uint64x2_t)xmmword_3D00760);
  v32.n128_u64[0] = (u32)v35;
  v32.n128_u64[1] = HIDWORD(v35);
  v39 = vshlq_u64(vandq_s8(v32, v24), (uint64x2_t)xmmword_3D00760);
  v40 = (sdfColor32_t)(v37.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(*(f32 *)&v53, 7u) << 16) | (u8)vcvts_n_s32_f32(*(f32 *)&v52, 7u) | v37.n128_u64[1]);
  v41 = (sdfColor32_t)(v36.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(*(f32 *)&7u) << 16) | (u8)vcvts_n_s32_f32(*(f32 *)&th, 7u) | v36.n128_u64[1]);
  v42 = (sdfColor32_t)(v38.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(rgba3->z, 7u) << 16) | (u8)vcvts_n_s32_f32(rgba3->x, 7u) | v38.n128_u64[1]);
  v43 = (sdfColor32_t)(v39.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(rgba2->z, 7u) << 16) | (u8)vcvts_n_s32_f32(rgba2->x, 7u) | v39.n128_u64[1]);
  eglLinkSprite4F(x0, y0, x1, y1, x2, y2, x3, y3, u, v, uw, vh, v43, v42, v41, v40, v18, *(const MethodInfo **)&rgba2->z);
}

// 0x22a4d30
void LinkSprite4F_2(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, s32 u, s32 v, s32 uw, s32 vh, u32 rgba0, u32 rgba1, u32 rgba2, u32 rgba3, void *th) {
  eglLinkSprite4F(x0, y0, x1, y1, x2, y2, x3, y3, u, v, uw, vh, (sdfColor32_t)rgba0, (sdfColor32_t)rgba1, (sdfColor32_t)rgba2, (sdfColor32_t)rgba3, th);
}

// 0x22a4e90
void eglLinkBoxZ(s32 x, s32 y, s32 w, s32 h, s32 z, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3) {
  s32 rgba;
  s32 v11;
  s32 v20;
  s32 v21;
  s32 v22;
  void *m_ListData;
  s64 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v29;
  CommonMesh_MeshEditPC_Form value;
  sdfColor32_t v36;
  sdfVector3_t VertexPos_36166560;
  sdfVector3_t v38;
  sdfVector3_t v39;
  sdfVector3_t v40;

  v36 = rgba2;
  rgba = rgba1->rgba;
  v11 = rgba0->rgba;
  if (drawSkip)
    return;
  v20 = w + x;
  v21 = 16 * x + 28672;
  v22 = 8 * y + 30976;
  m_ListData = data->vertexPC.m_ListData;
  v24 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__get_Length__ + 4);
  if ((*(u16 *)(v24 + 309) & 1) == 0)
    sub_42269C(v24);
  v25 = 16 * v20;
  eglAddMeshSquareIdx(m_ListData->m_length);
  v26 = v25 + 28672;
  VertexPos_36166560 = GetVertexPos_36166560(v21, v22, 0);
  v27 = h + y;
  value.position = VertexPos_36166560;
  value.color.rgba = v11;
  v29 = 8 * v27 + 30976;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  v38 = GetVertexPos_36166560(v26, v22, 0);
  value.position = v38;
  value.color.rgba = rgba;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  v39 = GetVertexPos_36166560(v21, v29, 0);
  value.position = v39;
  value.color.rgba = v36.rgba;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  v40 = GetVertexPos_36166560(v26, v29, 0);
  value.position = v40;
  value.color.rgba = rgba3->rgba;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  SetRange_36166880(mesh2D, z, 0);
}

// 0x22a5340
void eglLinkBox(s32 x, s32 y, s32 w, s32 h, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3) {
  u32 rgba;
  u32 v10;
  u32 v11;
  u32 v12;

  rgba = rgba3->rgba;
  v10 = rgba2->rgba;
  v11 = rgba1->rgba;
  v12 = rgba0->rgba;
  eglLinkBoxZ(x, y, w, h, 0xFFFFFF, (sdfColor32_t)v12, (sdfColor32_t)v11, (sdfColor32_t)v10, (sdfColor32_t)rgba);
}

// 0x22a5410
void LinkBox(s32 x, s32 y, s32 w, s32 h, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2, const sdfVector4_t *rgba3) {
  f32 v9;
  f32 z;
  f32 v11;
  f32 v12;
  int8x16_t v20;
  int8x8_t v21;
  int8x8_t v22;
  int8x8_t v23;
  u64 v24;
  u64 v25;
  int8x16_t v26;
  int8x16_t v27;
  u64 v28;
  uint64x2_t v29;
  uint64x2_t v30;
  uint64x2_t v31;
  uint64x2_t v32;
  sdfColor32_t v33;
  sdfColor32_t v34;
  uint64x2_t v35;
  sdfColor32_t v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  s64 v43;
  s64 v44;

  v38 = rgba1->w;
  v9 = rgba0->x;
  v37 = rgba1->y;
  v40 = rgba0->w;
  z = rgba1->z;
  v11 = rgba1->x;
  v39 = rgba0->y;
  v12 = rgba0->z;
  v20.n128_u64[0] = 255;
  v20.n128_u64[1] = 255;
  v21.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(v37), LODWORD(v38)), 7u).n64_u64[0];
  v22.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(HIDWORD(v43), HIDWORD(v44)), 7u).n64_u64[0];
  v23.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(HIDWORD(), HIDWORD()), 7u).n64_u64[0];
  v24 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(HIDWORD(v43), HIDWORD(v44)), (float32x2_t)0x4300000043000000LL)), v22, v22).n64_u64[0];
  v25 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(HIDWORD(), HIDWORD()), (float32x2_t)0x4300000043000000LL)), v23, v23).n64_u64[0];
  v26.n128_u64[0] = (u32)v24;
  v26.n128_u64[1] = HIDWORD(v24);
  v27 = v26;
  v26.n128_u64[0] = (u32)v25;
  v26.n128_u64[1] = HIDWORD(v25);
  v28 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(v37), LODWORD(v38)), (float32x2_t)0x4300000043000000LL)), v21, v21).n64_u64[0];
  v29 = vandq_s8(v26, v20);
  v26.n128_u64[0] = (u32)v28;
  v26.n128_u64[1] = HIDWORD(v28);
  v30 = vshlq_u64(vandq_s8(v27, v20), (uint64x2_t)xmmword_3D00760);
  v31 = vshlq_u64(v29, (uint64x2_t)xmmword_3D00760);
  v32 = vshlq_u64(vandq_s8(v26, v20), (uint64x2_t)xmmword_3D00760);
  v33 = (sdfColor32_t)(v31.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(*(f32 *)&7u) << 16) | (u8)vcvts_n_s32_f32(*(f32 *)&7u) | v31.n128_u64[1]);
  methoda = (v30.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(*(f32 *)&v44, 7u) << 16) | (u8)vcvts_n_s32_f32(*(f32 *)&v43, 7u) | v30.n128_u64[1]);
  v31.n128_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(v39), LODWORD(v40)), 7u).n64_u64[0];
  v34 = (sdfColor32_t)(v32.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(z, 7u) << 16) | (u8)vcvts_n_s32_f32(v11, 7u) | v32.n128_u64[1]);
  v30.n128_u64[0] = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(v39), LODWORD(v40)), (float32x2_t)0x4300000043000000LL)), (int8x8_t)v31.n128_u64[0], (int8x8_t)v31.n128_u64[0]).n64_u64[0];
  v26.n128_u64[0] = v30.n128_u32[0];
  v26.n128_u64[1] = v30.n128_u32[1];
  v35 = vshlq_u64(vandq_s8(v26, v20), (uint64x2_t)xmmword_3D00760);
  v36 = (sdfColor32_t)(v35.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(v12, 7u) << 16) | (u8)vcvts_n_s32_f32(v9, 7u) | v35.n128_u64[1]);
  eglLinkBoxZ(x, y, w, h, 0xFFFFFF, v36, v34, v33, (sdfColor32_t)v42);
}

// 0x22a5740
void eglLinkTri(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2) {
  s32 rgba;
  s32 v11;
  void *m_ListData;
  s64 v22;
  CommonMesh_MeshEditPC_Form v28;
  sdfVector3_t VertexPos_36166560;
  sdfVector3_t v30;
  sdfVector3_t v31;

  rgba = rgba1->rgba;
  v11 = rgba0->rgba;
  if (drawSkip)
    return;
  m_ListData = data->vertexPC.m_ListData;
  v22 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__get_Length__ + 4);
  if ((*(u16 *)(v22 + 309) & 1) == 0)
    sub_42269C(v22);
  eglAddMeshTriangleIdx(m_ListData->m_length);
  VertexPos_36166560 = GetVertexPos_36166560(16 * x0 + 28672, 8 * y0 + 30976, 0);
  v28.position = VertexPos_36166560;
  v28.color.rgba = v11;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &v28);
  v30 = GetVertexPos_36166560(16 * x1 + 28672, 8 * y1 + 30976, 0);
  v28.position = v30;
  v28.color.rgba = rgba;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &v28);
  v31 = GetVertexPos_36166560(16 * x2 + 28672, 8 * y2 + 30976, 0);
  v28.position = v31;
  v28.color.rgba = rgba2->rgba;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &v28);
  SetRange_36166880(mesh2D, 0xFFFFFFu, 0);
}

// 0x22a5cf0
void LinkTri(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2) {
  f32 x;
  f32 z;
  f32 v12;
  f32 v13;
  int8x16_t v22;
  int8x8_t v23;
  int8x8_t v24;
  int8x8_t v25;
  u64 v26;
  u64 v27;
  int8x16_t v28;
  int8x16_t v29;
  u64 v30;
  uint64x2_t v31;
  uint64x2_t v32;
  uint64x2_t v33;
  uint64x2_t v34;
  sdfColor32_t v35;
  sdfColor32_t v36;
  f32 y;
  f32 v38;
  f32 v39;
  f32 w;

  w = rgba1->w;
  x = rgba0->x;
  y = rgba1->y;
  v39 = rgba0->w;
  z = rgba1->z;
  v12 = rgba1->x;
  v38 = rgba0->y;
  v13 = rgba0->z;
  v22.n128_u64[0] = 255;
  v22.n128_u64[1] = 255;
  v23.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(y), LODWORD(w)), 7u).n64_u64[0];
  v24.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(LODWORD(v38), LODWORD(v39)), 7u).n64_u64[0];
  v25.n64_u64[0] = vcvt_n_s32_f32((float32x2_t)__PAIR64__(HIDWORD(), HIDWORD()), 7u).n64_u64[0];
  v26 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(y), LODWORD(w)), (float32x2_t)0x4300000043000000LL)), v23, v23).n64_u64[0];
  v27 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(LODWORD(v38), LODWORD(v39)), (float32x2_t)0x4300000043000000LL)), v24, v24).n64_u64[0];
  v28.n128_u64[0] = (u32)v26;
  v28.n128_u64[1] = HIDWORD(v26);
  v29 = v28;
  v28.n128_u64[0] = (u32)v27;
  v28.n128_u64[1] = HIDWORD(v27);
  v30 = vbsl_s8(vcltz_f32(vmul_f32((float32x2_t)__PAIR64__(HIDWORD(), HIDWORD()), (float32x2_t)0x4300000043000000LL)), v25, v25).n64_u64[0];
  v31 = vandq_s8(v28, v22);
  v28.n128_u64[0] = (u32)v30;
  v28.n128_u64[1] = HIDWORD(v30);
  v32 = vshlq_u64(vandq_s8(v29, v22), (uint64x2_t)xmmword_3D00760);
  v33 = vshlq_u64(v31, (uint64x2_t)xmmword_3D00760);
  v34 = vshlq_u64(vandq_s8(v28, v22), (uint64x2_t)xmmword_3D00760);
  v35 = (sdfColor32_t)(v32.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(z, 7u) << 16) | (u8)vcvts_n_s32_f32(v12, 7u) | v32.n128_u64[1]);
  v36 = (sdfColor32_t)(v33.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(v13, 7u) << 16) | (u8)vcvts_n_s32_f32(x, 7u) | v33.n128_u64[1]);
  eglLinkTri(x0, y0, x1, y1, x2, y2, v36, v35, (sdfColor32_t)(v34.n128_u64[0] | ((u64)(u8)vcvts_n_s32_f32(*(f32 *)&7u) << 16) | (u8)vcvts_n_s32_f32(*(f32 *)&7u) | v34.n128_u64[1]));
}

// 0x22a5f60
void eglLinkMaru2D(s32 cx, s32 cy, s32 fr, const sdfColor32_t *in_rgba, const sdfColor32_t *out_rgba) {
  s32 rgba;
  s32 v7;
  u32 v14;
  void *m_ListData;
  s64 v17;
  u16 v18;
  s32 v19;
  s32 v20;
  f32 v21;
  s32 i;
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
  s32 v38;
  bool v39;
  f32 v40;
  s32 v41;
  s32 v42;
  void *v46;
  void *v47;
  s64 v48;
  s32 m_length;
  s16 v50;
  s32 v51;
  s64 v52;
  u16 v53;
  u16 v54[2];
  u16 v55;
  CommonMesh_MeshEditPC_Form value;
  sdfVector3_t VertexPos_36166560;
  sdfVector3_t v58;

  rgba = out_rgba->rgba;
  v7 = in_rgba->rgba;
  *(u64 *)&value.position.x = 0;
  *(u64 *)&value.position.z = 0;
  v53 = 0;
  goto LABEL_3;
  if (v14)
  {
LABEL_3:
    goto LABEL_4;
  }
LABEL_4:
  if (drawSkip)
    return;
  m_ListData = data->vertexPC.m_ListData;
  v17 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__get_Length__ + 4);
  if ((*(u16 *)(v17 + 309) & 1) == 0)
    sub_42269C(v17);
  v18 = LOWORD(m_ListData->m_length) + 1;
  v54[0] = m_ListData->m_length;
  v55 = v18;
  v19 = 16 * cx + 28672;
  v20 = 8 * cy + 30976;
  v21 = fr;
  VertexPos_36166560 = GetVertexPos_36166560(v19, v20, 0);
  value.color.rgba = v7;
  value.position.x = VertexPos_36166560.x;
  value.position.y = VertexPos_36166560.y;
  value.position.z = VertexPos_36166560.z;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  value.color.rgba = rgba;
  for (i = 0; i != 360; i += 10)
  {
    v25 = RAD((f32)i);
    v26 = (s32)(v25 * 0.15915494);
    if ((f32)(v25 * 0.15915494) == INFINITY)
      v26 = -2147500000.0;
    v27 = (f32)(v25 * 0.15915494) - v26;
    v28 = v27 + 1.0;
    if (v27 >= -0.5)
      v28 = v27;
    if (v27 > 0.5)
      v29 = v27 + -1.0;
    else
      v29 = v28;
    v30 = -0.5 - v29;
    if (v29 >= -0.25)
      v30 = v29;
    if (v29 > 0.25)
      v31 = 0.5 - v29;
    else
      v31 = v30;
    v32 = (f32)(v25 + 1.5708) * 0.15915494;
    v33 = (s32)v32;
    if (v32 == INFINITY)
      v33 = -2147500000.0;
    v34 = v32 - v33;
    if ((f32)(v32 - v33) <= 0.5)
    {
      if (v34 < -0.5)
        v34 = v34 + 1.0;
    }
    else
    {
      v34 = v34 + -1.0;
    }
    if (v34 <= 0.25)
    {
      if (v34 < -0.25)
        v34 = -0.5 - v34;
    }
    else
    {
      v34 = 0.5 - v34;
    }
    v35 = v31 * 4.0;
    v36 = v34 * 4.0;
    v37 = (f32)((f32)((f32)((f32)((f32)((f32)(v31 * 4.0) * 1.5708) + (f32)((f32)(v35 * (f32)(v35 * v35)) * -0.6459637)) + (f32)((f32)((f32)(v35 * v35) * (f32)(v35 * (f32)(v35 * v35))) * 0.07968968)) + (f32)((f32)((f32)(v35 * v35) * (f32)((f32)(v35 * v35) * (f32)(v35 * (f32)(v35 * v35)))) * -0.0046737655)) + (f32)((f32)((f32)(v35 * v35) * (f32)((f32)(v35 * v35) * (f32)((f32)(v35 * v35) * (f32)(v35 * (f32)(v35 * v35))))) * 0.00015148419))
        * v21;
    v38 = 16 * (s32)v37;
    v39 = v37 == INFINITY;
    v40 = (f32)((f32)((f32)((f32)((f32)((f32)(v34 * 4.0) * 1.5708) + (f32)((f32)(v36 * (f32)(v36 * v36)) * -0.6459637)) + (f32)((f32)((f32)(v36 * v36) * (f32)(v36 * (f32)(v36 * v36))) * 0.07968968)) + (f32)((f32)((f32)(v36 * v36) * (f32)((f32)(v36 * v36) * (f32)(v36 * (f32)(v36 * v36)))) * -0.0046737655)) + (f32)((f32)((f32)(v36 * v36) * (f32)((f32)(v36 * v36) * (f32)((f32)(v36 * v36) * (f32)(v36 * (f32)(v36 * v36))))) * 0.00015148419))
        * v21;
    if (v39)
      v38 = 0;
    v41 = v38 + v19;
    v42 = 8 * (s32)v40;
    if (v40 == INFINITY)
      v42 = 0;
    v58 = GetVertexPos_36166560(v41, v42 + v20, 0);
    value.position = v58;
    _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
    v53 = v55++;
    _Add((Unity_Collections_NativeList_ushort__o)&data->index, &v53);
    _Add((Unity_Collections_NativeList_ushort__o)&data->index, v54);
    _Add((Unity_Collections_NativeList_ushort__o)&data->index, &v55);
  }
  v46 = data->index.m_ListData;
  v47 = v46;
  v48 = *((u64 *)Method_Unity_Collections_NativeList_ushort__get_Length__ + 4);
  if ((*(u16 *)(v48 + 309) & 1) == 0)
  {
    sub_42269C(v48);
    v47 = data->index.m_ListData;
  }
  m_length = v46->m_length;
  v50 = v54[0] + 1;
  v51 = m_length - 1;
  ++v54[0];
  v52 = *((u64 *)Method_Unity_Collections_NativeList_ushort__set_Item__ + 4);
  if ((*(u8 *)(v52 + 309) & 1) == 0)
    sub_42269C(v52);
  *((u16 *)v47->Ptr + v51) = v50;
  SetRange_36166880(mesh2D, 0xFFFFFFu, 0);
}

// 0x22a6500
void eglLinkPoly4(const sdfVector3_t *pos0, const sdfVector3_t *pos1, const sdfVector3_t *pos2, const sdfVector3_t *pos3, const sdfColor32_t *col0, const sdfColor32_t *col1, const sdfColor32_t *col2, const sdfColor32_t *col3) {
  f32 z;
  f32 v10;
  s32 rgba;
  s32 v12;
  f32 v13;
  f32 v14;
  s64 v15;
  s64 v16;
  float32x2_t *static_fields;
  f32 v19;
  float32x2_t v20;
  float32x2_t *v22;
  f32 v23;
  float32x2_t v24;
  float32x2_t *v26;
  f32 v27;
  float32x2_t v28;
  float32x2_t *v30;
  f32 v31;
  float32x2_t v32;
  f32 v35;
  f32 v36;
  f32 y;
  f32 x;
  CommonMesh_MeshEditPC_Form value;
  float32x2_t v40;
  f32 v41;

  y = pos1->y;
  x = pos1->x;
  z = pos1->z;
  v35 = pos0->y;
  v10 = pos0->z;
  rgba = col1->rgba;
  v36 = pos0->x;
  v12 = col0->rgba;
  v13 = pos3->z;
  v14 = pos3->x;
  if (*(u8 *)(*(u64 *)(*(u64 *)&pos3->x + 184) + 16))
    return;
  v15 = *(u64 *)(*(u64 *)(*(u64 *)(*(u64 *)&pos3->x + 184) + 32) + 56);
  v16 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__get_Length__ + 4);
  if ((*(u16 *)(v16 + 309) & 1) == 0)
    sub_42269C(v16);
  eglAddMeshSquareIdx(*(u32 *)(v15 + 8), *(const MethodInfo **)&pos3->z);
  v19 = v10 * static_fields[4].n64_f32[0];
  v20.n64_u64[0] = vmul_f32((float32x2_t)__PAIR64__(LODWORD(v35), LODWORD(v36)), static_fields[3]).n64_u64[0];
  *(float32x2_t *)&value.position.x = v20;
  value.position.z = v19;
  *(f32 *)&value.color.rgba = v14;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  v23 = z * v22[4].n64_f32[0];
  v24.n64_u64[0] = vmul_f32((float32x2_t)__PAIR64__(LODWORD(y), LODWORD(x)), v22[3]).n64_u64[0];
  *(float32x2_t *)&value.position.x = v24;
  value.position.z = v23;
  *(f32 *)&value.color.rgba = v13;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  v27 = pos2->z * v26[4].n64_f32[0];
  v28.n64_u64[0] = vmul_f32(*(float32x2_t *)&pos2->x, v26[3]).n64_u64[0];
  *(float32x2_t *)&value.position.x = v28;
  value.position.z = v27;
  value.color.rgba = v12;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
  v31 = v41 * v30[4].n64_f32[0];
  v32.n64_u64[0] = vmul_f32(v40, v30[3]).n64_u64[0];
  *(float32x2_t *)&value.position.x = v32;
  value.position.z = v31;
  value.color.rgba = rgba;
  _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&data->vertexPC, &value);
}

// 0x22a69a0
void eglLinkPoly42(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 x3, f32 y3, f32 z3, u32 col0, u32 col1, u32 col2, u32 col3) {
  sdfColor32_t v17;
  sdfVector3_t v30;
  sdfVector3_t z2a;
  sdfVector3_t v32;
  sdfVector3_t v33;

  v30.x = x1;
  v30.y = y1;
  v30.z = z1;
  v33.y = y0;
  v33.z = z0;
  *(u64 *)&v32.x = col0;
  LODWORD(v32.z) = col1;
  z2a.z = z2;
  *(u64 *)&z2a.x = __PAIR64__(LODWORD(y2), LODWORD(x2));
  v33.x = x0;
  eglLinkPoly4(v33, v30, z2a, v32, (sdfColor32_t)col2, (sdfColor32_t)col3, (sdfColor32_t)v17);
}

// 0x22a6ae0
static void *GetMaterial(bool isEffect) {
  JUMPOUT(0x2255180);
}

// 0x22a6b80
void *eglNewMesh3D(bool isEffect) {
  char **v6;
  void *Material;
  void *_36130064;
  void *transform;
  void *v11;

  if (isEffect)
    v6 = &"effect";
  else
    v6 = &"standard";
  Material = GetMaterial(Instance, *v6, 0);
  _36130064 = Make_36130064(Material, 0);
  transform = get_transform(_36130064, 0);
  v11 = get_transform(hook, 0);
  SetParent_61042560(transform, v11, 0, 0);
  SetAutoHide(_36130064, 1, 0);
  return (void *)_36130064;
}

// 0x22a6d30
void *eglNewMesh2D(bool isEffect) {
  char **v6;
  void *Material;
  void *_36165888;
  void *transform;
  void *v12;

  if (isEffect)
    v6 = &"effect";
  else
    v6 = &"standard";
  Material = GetMaterial(Instance, *v6, 0);
  _36165888 = Make_36165888(Material, 0);
  SetFloat_60816992(Material, ID_Cull, 2.0, 0);
  transform = get_transform(_36165888, 0);
  v12 = get_transform(hook, 0);
  SetParent_61042560(transform, v12, 0, 0);
  SetAutoHide(_36165888, 1, 0);
  return (void *)_36165888;
}

// 0x22a6f20
void eglDelMesh(void *mesh) {
  void *v4;
  void *v6;
  void *v7;
  void *gameObject;

  v4 = mesh;
  if (!op_Inequality(v4, 0, 0))
    return;
  v6 = mesh;
  v7 = mesh;
  if (!!op_Equality(v7, v6, 0))
  {
    Destroy(data);
    data = 0;
    mesh2D = 0;
    mesh = 0;
  }
  gameObject = get_gameObject(mesh, 0);
  DestroyImmediate_61008224(gameObject, 0);
  mesh = 0;
}

// 0x22a7100
void DelMesh(void *mesh) {
  void *mesha;

  mesha = mesh;
  eglDelMesh(mesha);
  mesh = 0;
}

// 0x22a7180
void eglLinkMesh(void *mesh) {
  sdfDrawTag_t *v3;
  void *v8;
  s64 naturalAligment;
  void *p_mesh2D;
  void *v12;
  JobData *v13;

  v3 = sdfPrimAllocDrawTag();
  sdfDrawTagLink(v3, mesh->packet);
  sdfDrawTagLinkOt(currentOt, v3);
  eglCloseMesh();
  v8 = 0;
  if (mesh->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (mesh->klass->_2.typeHierarchy[naturalAligment - 1] == Project_libsdf_sdfScreenMesh)
      v8 = mesh;
    else
      v8 = 0;
  }
  mesh2D = (void *)v8;
  p_mesh2D = &mesh2D;
  if (mesh->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (mesh->klass->_2.typeHierarchy[naturalAligment - 1] == Project_libsdf_sdfScreenMesh)
      v12 = mesh;
    else
      v12 = 0;
  }
  else
  {
    v12 = 0;
  }
  v13 = Allocate(JobData);
  _ctor(v13);
  data = v13;
}

// 0x22a2ba0
void eglCloseMesh(void) {
  if (op_Inequality(mesh, 0, 0))
    goto LABEL_5;
  return;
  if (op_Inequality(mesh, 0, 0))
  {
LABEL_5:
    if (drawSkip)
    {
      Destroy(*((void *)*((MethodInfo *)egl + 2).virtualMethodPointer + 4));
      goto LABEL_13;
    }
    SetJob();
LABEL_13:
    data = 0;
    mesh2D = 0;
    mesh = 0;
  }
}

// 0x22a73f0
static void SetJob(void) {
  bool v4;
  MeshEdit *edit;
  MeshEdit *klass;
  s64 v9;
  void *v10;
  s32 v11;
  s32 m_length;
  JobData *data_local;
  void *m_ListData;
  s64 v20;
  MeshEditPC *v22;
  void *v23;
  s64 v24;
  void *v27;
  MeshEditPCU *v28;
  MeshEdit *v32;
  u64 *v33;
  void *v34;
  s64 v35;
  MeshEdit *v36;
  char v37;
  void *m_Buffer;
  s64 v41;
  void *v44;
  s64 jobGroup;
  s64 v48;
  MeshEdit *v50;
  s64 v51;
  MeshEdit *v53;
  s32 vertexCount;
  MeshEdit *v56;
  JobData *v58;
  s64 v59;
  void *v60;
  s32 v61;
  s32 v65;
  JobData *v66;
  struct Unity_Collections_NativeArray_T__o index;
  u8 value[24];
  s64 v70;
  s64 v71;
  Project_Kernel_egl_Job_ushort__o v72;
  u16 v73[2];
  Unity_Collections_NativeArray_T__o v74;
  Unity_Collections_NativeArray_T__o v75;
  Unity_Jobs_JobHandle_o v76;
  Unity_Collections_NativeArray_T__o v77;
  Unity_Jobs_JobHandle_o v78;
  Unity_Jobs_JobHandle_o v79;
  Unity_Jobs_JobHandle_o v80;
  Unity_Jobs_JobHandle_o v81;
  Unity_Jobs_JobHandle_o v82;
  Unity_Jobs_JobHandle_o v83;
  Unity_Jobs_JobHandle_o v84;

  v70 = 0;
  v71 = 0;
  memset(value, 0, sizeof(value));
  v73[0] = 0;
  v4 = op_Inequality(mesh2D, 0, 0);
  edit = mesh->edit;
  {
    m_ListData = data->vertexPCU.m_ListData;
    v20 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__get_Length__ + 4);
    if ((*(u16 *)(v20 + 309) & 1) == 0)
      sub_42269C(v20);
    v11 = 1;
    m_length = m_ListData->m_length;
LABEL_13:
    if (mesh->edit)
      goto LABEL_14;
LABEL_28:
    if (m_length < 1)
    {
      v23 = data->vertexPCU.m_ListData;
      v24 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__get_Length__ + 4);
      if ((*(u16 *)(v24 + 309) & 1) == 0)
        sub_42269C(v24);
      m_length = v23->m_length;
      if (!m_length)
      {
        Destroy(data);
        return;
      }
      v27 = mesh;
      v28 = Allocate(MeshEditPCU);
      _ctor(v28, 0);
      (v27->klass->vtable._9_SetEdit.methodPtr)(v27, v28, v27->klass->vtable._9_SetEdit.method);
      v11 = 1;
      if (!v4)
      {
LABEL_44:
        goto LABEL_46;
      }
    }
    else
    {
      v22 = Allocate(MeshEditPC);
      _ctor(v22, 0);
      (mesh->klass->vtable._9_SetEdit.methodPtr)(mesh, v22, mesh->klass->vtable._9_SetEdit.method);
      if (!v4)
        goto LABEL_44;
    }
    SetPoint(mesh2D, 0, 0, 0);
    goto LABEL_44;
  }
  else
  {
    v9 = *((u64 *)Method_Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__get_Length__ + 4);
    v10 = data->vertexPC.m_ListData;
    if ((*(u16 *)(v9 + 309) & 1) == 0)
      sub_42269C(v9);
    v11 = 0;
    m_length = v10->m_length;
    goto LABEL_13;
  }
  if (!mesh->edit)
    goto LABEL_28;
LABEL_14:
  if (m_length)
    goto LABEL_44;
  if (v11)
  {
    data_local = data;
    v70 = 0;
    v71 = 0;
    *(u64 *)&value[16] = 0;
    _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPCU_Form__o)&data_local->vertexPCU, &value[16]);
  }
  else
  {
    v66 = data;
    *(u64 *)value = 0;
    *(u64 *)&value[8] = 0;
    _Add((Unity_Collections_NativeList_CommonMesh_MeshEditPC_Form__o)&v66->vertexPC, value);
  }
  v73[0] = 0;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, v73);
  v73[0] = 0;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, v73);
  v73[0] = 0;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, v73);
  m_length = 1;
LABEL_46:
  v32 = mesh->edit;
  v33 = Method_Unity_Collections_NativeList_ushort__get_Length__;
  v32->vertexCount = m_length;
  v34 = data->index.m_ListData;
  v35 = v33[4];
  if ((*(u8 *)(v35 + 309) & 1) != 0)
  {
    v32->indexCount = v34->m_length;
    if (!v4)
      goto LABEL_48;
LABEL_64:
    v53 = mesh->edit;
    vertexCount = v53->vertexCount;
    v56 = mesh->edit;
    v65 = marker.m_Length;
    v53->vertexCount = v65 + vertexCount;
    v56->indexCount += v65;
    goto LABEL_49;
  }
  sub_42269C(v35);
  v32->indexCount = v34->m_length;
  if (v4)
    goto LABEL_64;
LABEL_48:
LABEL_49:
  v36 = mesh->edit;
  v37 = (v36->klass->vtable._4_unknown.methodPtr)(v36, v36->klass->vtable._4_unknown.method);
  if ((v37 & 1) != 0)
  {
    v74 = _op_Implicit((Unity_Collections_NativeList_T__o)data->index.m_ListData);
    m_Buffer = v74.m_Buffer;
    v41 = *(u64 *)&v74.m_Length;
    index = (struct Unity_Collections_NativeArray_T__o)mesh->edit->index;
    if (v11)
    {
      v75 = _op_Implicit((Unity_Collections_NativeList_T__o)data->vertexPCU.m_ListData);
      v44 = mesh->edit;
      {
        v82.jobGroup = 0;
        *(u64 *)&v82.version = 0;
        v72.dst = v44[8];
        v72.src = v75;
        v76 = Schedule_egl_Job_CommonMesh_MeshEditPCU_Form__(&v72, m_length, 0, v82);
        jobGroup = v76.jobGroup;
        v48 = *(u64 *)&v76.version;
        if (!v4)
          goto LABEL_59;
        goto LABEL_77;
      }
    }
    else
    {
      v77 = _op_Implicit((Unity_Collections_NativeList_T__o)data->vertexPC.m_ListData);
      v44 = mesh->edit;
      {
        v83.jobGroup = 0;
        *(u64 *)&v83.version = 0;
        v72.dst = *(void *)((char *)v44 + 120);
        v72.src = v77;
        v78 = Schedule_egl_Job_CommonMesh_MeshEditPC_Form__(&v72, m_length, 0, v83);
        jobGroup = v78.jobGroup;
        v48 = *(u64 *)&v78.version;
        if (!v4)
        {
LABEL_59:
          v50 = mesh->edit;
          jobGroup = (v50->klass->vtable._8_unknown.methodPtr)(v50, jobGroup, v48, v50->klass->vtable._8_unknown.method);
          v48 = v51;
          goto LABEL_81;
        }
LABEL_77:
        SetMarker(mesh2D, 0);
LABEL_81:
        v58 = data;
        v59 = *((u64 *)Method_Unity_Collections_NativeList_ushort__get_Length__ + 4);
        v60 = v58->index.m_ListData;
        if ((*(u16 *)(v59 + 309) & 1) == 0)
          sub_42269C(v59);
        v61 = v60->m_length;
        v84.jobGroup = 0;
        *(u64 *)&v84.version = 0;
        v72.dst = index;
        v72.src.m_Buffer = m_Buffer;
        *(u64 *)&v72.src.m_Length = v41;
        v81 = Schedule_egl_Job_ushort__(&v72, v61, 0, v84);
        v79.jobGroup = jobGroup;
        *(u64 *)&v79.version = v48;
        v80 = CombineDependencies(v79, v81, 0);
        data->jobHandle = v80;
        v80.jobGroup = (u64)data;
        *(u64 *)&v80.version = mesh->edit;
        *(u64 *)(v80.jobGroup + 40) = *(u64 *)&v80.version;
        Add(Instance, data, 0);
        return;
      }
    }
  }
  Destroy(data);
}

// 0x22a3b60
sdfVector4_t eglGetMeshSquareUV(s32 u, s32 v, s32 uw, s32 vh, void *th) {
  f32 v11;
  f32 v12;
  f32 v13;
  sdfVector4_t result;

  v11 = sdfTexScale(th);
  v12 = v11
      / (f32)(th->klass->vtable._5_get_width.methodPtr)(th, th->klass->vtable._5_get_width.method);
  v13 = v11
      / (f32)(th->klass->vtable._7_get_height.methodPtr)(th, th->klass->vtable._7_get_height.method);
  result.z = v12 * (f32)(uw + u);
  result.y = 1.0 - (f32)(v13 * (f32)v);
  result.w = 1.0 - (f32)(v13 * (f32)(vh + v));
  result.x = v12 * (f32)u;
  return result;
}

// 0x22a5aa0
void eglAddMeshTriangleIdx(u16 count) {
  u16 value[2];
  u16 v8;

  if (drawSkip)
    return;
  value[0] = count;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, value);
  v8 = count + 2;
  value[0] = count + 1;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, value);
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, &v8);
}

// 0x22a3c60
void eglAddMeshSquareIdx(u16 count) {
  u16 value[2];
  u16 v8;

  if (drawSkip)
    return;
  value[0] = count;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, value);
  value[0] = count + 1;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, value);
  value[0] = count + 2;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, value);
  value[0] = count + 3;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, value);
  v8 = count + 1;
  value[0] = count + 2;
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, value);
  _Add((Unity_Collections_NativeList_ushort__o)&data->index, &v8);
}
