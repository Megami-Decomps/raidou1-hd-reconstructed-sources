#include "types.h"
#include "EFFBEHAVIOR_TYPE.h"
#include "TNEFFECT_BLEND.h"
#include "dds3billboard.h"
#include "eff.h"
#include "effbehavior.h"
#include "effpolygontrack.h"
#include "sdf_vu0.h"
#include "sdfbase.h"
#include "sdfdraw.h"
#include "sdfquat.h"
#include "sdfsystem.h"
#include "sdfvsync.h"

#define EFFPOLYGON_TRACK_MAX 100
#define EFFPOLYGON_BZTP_SIZE 3
#define EFFPOLYGON_BZTP_H_POINT_MAX 5

typedef struct Standard Standard;
typedef struct effBehavior_Params_Basic_t effBehavior_Params_Basic_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonTrackMesh effPolygonTrackMesh;
typedef struct effPolygonTrackMesh_Source effPolygonTrackMesh_Source;
typedef struct effPolygonTrack_Params_t effPolygonTrack_Params_t;
typedef struct poltHandle_t poltHandle_t;
typedef struct ptbzHandle_t ptbzHandle_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;

struct effPolygonTrackMesh_Source {
    s32 pp;
    s32 vp;
    s32 ip;
    sdfVector4_t vc_i;
    sdfVector4_t vc_ia;
    sdfVector4_t vc_o;
    sdfVector4_t vc_oa;
    sdfVector3_t dir;
    f32 width;
    sdfVector4_t abgr;
    s32 current;
    s32 count;
};

void *bztpFaceIndex;
static void *bztpHeadFaceIndex;
static sdfDrawTag_t *pptbzDrawTag;
static sdfVector4_t **_v;

static poltHandle_t *Create(u32 number);
static poltHandle_t *ParamsCreate(effBehavior_Params_Basic_t *pParams);
static void ResourceCopy(poltHandle_t *hDest, poltHandle_t *hSrc);
static void PolygonSet(poltHandle_t *hPolygon, EFFBEHAVIOR_TYPE type, effPolygonTrack_Params_t *pParams);
static void BehaviorSet(poltHandle_t *hPolygon, EFFBEHAVIOR_TYPE type, effBehavior_Params_Basic_t *pParams);
static void BillboardGeneralSet(poltHandle_t *hPolygon, u32 index);
static void BillboardSet(poltHandle_t *hPolygon, DDS3BILLBOARD type, void *resrc);
static void Calc(effPartsHandle_t *handle);
static void Draw(effPartsHandle_t *handle);
static ptbzHandle_t *BezierCreate(u32 face, u32 split);
static void BezierDelete(ptbzHandle_t *hPolygon);
static void BezierReset(ptbzHandle_t *hPolygon);
static void BezierVertexGet(ptbzHandle_t *hPolygon, void *pVertex, s32 frame);
static void BezierVertexSetSub(ptbzHandle_t *hPolygon, void *pVertex);
static void BezierVertexSet(ptbzHandle_t *hPolygon, void *pVertex);
static void BezierVertexBegin(const sdfMatrix4_t *pMatrix, effPolygonTrackMesh *pMesh);
static bool BezierVertexDraw(ptbzHandle_t *hPolygon, const sdfVector4_t *abgr, effPolygonTrackMesh_Source *source);
static void BezierVertexEnd(poltHandle_t *hPolygon, TNEFFECT_BLEND blend);

// 0x1991aa0
static poltHandle_t *Create(u32 number) {
  poltHandle_t *v3;

  v3 = Allocate(poltHandle_t);
  v3->number = number;
  *(u32 *)&v3->scale = 1065353216;
  v3->phPolyList = 0;
  v3->abgr = oneVector;
  v3->hBehavior = 0;
  return v3;
}

// 0x1991b80
static poltHandle_t *ParamsCreate(effBehavior_Params_Basic_t *pParams) {
  effBehavior_EmitterParams_t *emitter;
  u32 *p_life;
  u32 life;
  u32 count;
  u32 v7;
  u32 v8;

  emitter = pParams->emitter;
  life = emitter->life;
  count = emitter->count;
  p_life = &emitter->life;
  if (!life)
    p_life = &pParams->life;
  v7 = *p_life;
  if (v7 * count >= 0x64)
    v8 = 100;
  else
    v8 = v7 * count;
  return Create(v8);
}

// 0x1991c10
poltHandle_t *PartsCreate(Standard *pParts) {
  u16 type;
  Standard *klass;
  s64 naturalAligment;
  u8 *v8;
  sdfBinary *v9;
  effPolygonTrack_Params_t *v10;
  effBehavior_Params_Basic_t *Params;
  effBehavior_EmitterParams_t *emitter;
  u32 *p_life;
  u32 life;
  u32 count;
  u32 v18;
  u32 v19;
  poltHandle_t *v20;
  u16 v21;
  bhvrHandle_t *hBehavior;
  bhvrHandle_t *v24;
  void *pData;

  type = pParts->param->type;
  klass = pParts->klass;
  if (pParts->klass->_2.naturalAligment < (u32)naturalAligment)
    goto LABEL_10;
  goto LABEL_9;
  if (pParts->klass->_2.naturalAligment < (u32)naturalAligment)
  {
LABEL_10:
    v8 = 0;
    goto LABEL_11;
  }
LABEL_9:
  if (klass->_2.typeHierarchy[naturalAligment - 1] != Project_effParts_t_Resource_Common)
    goto LABEL_10;
  pData = pParts->param->pData;
  v8 = pData[1].klass;
LABEL_11:
  v9 = Allocate(sdfBinary);
  _ctor_36176832(v9, v8, 0);
  v10 = Allocate(effPolygonTrack_Params_t);
  _ctor_26812080(v10, v9);
  Params = effCreateParams(type, v9);
  emitter = Params->emitter;
  life = emitter->life;
  count = emitter->count;
  p_life = &emitter->life;
  if (!life)
    p_life = &Params->life;
  v18 = *p_life;
  if (v18 * count >= 0x64)
    v19 = 100;
  else
    v19 = v18 * count;
  v20 = Create(v19);
  PolygonSet(v20, v21, v10);
  hBehavior = v20->hBehavior;
  if (hBehavior)
    Delete(hBehavior);
  v24 = effCreate(type, v20->number, Params);
  v20->hBehavior = v24;
  return v20;
}

// 0x1992180
poltHandle_t *effSPartsCreate(Standard *pParts) {
  poltHandle_t *v6;
  s64 naturalAligment;
  effPartsData_t *data;
  void *pData;
  s32 type;
  poltHandle_t *v14;
  u16 v15;
  u32 klass;

  v6 = PartsCreate(pParts);
  if (!pParts)
    goto LABEL_13;
  goto LABEL_11;
  if (!pParts)
  {
LABEL_13:
    v6->matType = pParts->data->type;
    return v6;
  }
LABEL_11:
  if (pParts->klass->_2.naturalAligment < (u32)naturalAligment || pParts->klass->_2.typeHierarchy[naturalAligment - 1] != Standard)
  {
    goto LABEL_13;
  }
  data = pParts->data;
  pData = data->pData;
  type = data->type;
  v6->matType = type;
  if (!pData)
    return v6;
  if (type == 4)
  {
    klass = pData[1].klass;
    BillboardGeneralSet(v6, klass);
    return v6;
  }
  else
  {
    if (type == 2)
    {
      pData = *(void *)((pData->klass->vtable._5_GetExtUnits.methodPtr)(pData, pData->klass->vtable._5_GetExtUnits.method) + 32);
      v14 = v6;
      v15 = 1;
    }
    else
    {
      if (type != 1)
        return v6;
      v14 = v6;
      v15 = 0;
    }
    BillboardSet(v14, v15, pData);
    return v6;
  }
}

// 0x19925c0
void Delete(effPartsHandle_t *handle) {
  void *klass;
  effOption *option;
  s64 v6;
  bhvrHandle_t *monitor;
  effOption *v9;
  void *p_fields;
  effOption *v11;
  void *gameObject;
  s32 v13;

  klass = handle[3].klass;
  if (klass)
  {
    dds3BillboardDelete(klass);
  }
  option = handle[2].option;
  if (option)
  {
    v6 = *(u64 *)&option->adjustRGBA.x;
    if ((s32)v6 >= 1)
    {
      v13 = 0;
      do
      {
        v6 = *(u64 *)&option->adjustRGBA.x;
        ++v13;
      }
      while (v13 < (s32)v6);
    }
  }
  monitor = handle[3].monitor;
  if (monitor)
    Delete(monitor);
  v11 = handle[3].option;
  p_fields = &handle[3].fields;
  v9 = v11;
  if (v11)
  {
    gameObject = get_gameObject(v9[1].klass, 0);
    DestroyImmediate_61008224(gameObject, 0);
    Destroy(p_fields);
    p_fields = 0;
  }
}

// 0x1992770
poltHandle_t *Copy(effPartsHandle_t *handle) {
  effBehavior_Params_Basic_t *v4;
  effBehavior_EmitterParams_t *emitter;
  u32 *p_life;
  u32 life;
  u32 count;
  u32 v9;
  u32 v10;
  poltHandle_t *v11;
  u16 v12;
  u16 v14;
  bhvrHandle_t *hBehavior;
  bhvrHandle_t *v16;

  v4 = *((effBehavior_Params_Basic_t *)handle[3].monitor + 8);
  emitter = v4->emitter;
  life = emitter->life;
  count = emitter->count;
  p_life = &emitter->life;
  if (!life)
    p_life = &v4->life;
  v9 = *p_life;
  if (v9 * count >= 0x64)
    v10 = 100;
  else
    v10 = v9 * count;
  v11 = Create(v10);
  PolygonSet(v11, v12, handle[2].monitor);
  v14 = *((u16 *)handle[3].monitor + 8);
  hBehavior = v11->hBehavior;
  if (hBehavior)
    Delete(hBehavior);
  v16 = effCreate(v14, v11->number, v4);
  v11->hBehavior = v16;
  return v11;
}

// 0x19928f0
poltHandle_t *effSCopy(effPartsHandle_t *handle) {
  poltHandle_t *v4;

  v4 = Copy(handle);
  ResourceCopy(v4, handle);
  return v4;
}

// 0x19929b0
static void ResourceCopy(poltHandle_t *hDest, poltHandle_t *hSrc) {
  u32 matType;
  bool v6;
  s32 v7;
  void *hBillboard;
  void *v10;
  dds3Billboard_Basic_t *v11;
  bhvrHandle_t *hBehavior;
  dds3Billboard_Basic_t *v13;
  s32 blend;

  matType = hSrc->matType;
  v6 = matType > 4;
  v7 = (1 << matType) & 0x16;
  if (!v6 && v7 != 0)
  {
    hBillboard = hDest->hBillboard;
    if (hBillboard)
    {
      dds3BillboardDelete(hBillboard);
    }
    v10 = hSrc->hBillboard;
    v11 = dds3BillboardCopy(v10);
    hDest->hBillboard = v11;
    hBehavior = hDest->hBehavior;
    if (hBehavior)
    {
      v13 = hDest->hBillboard;
      blend = hBehavior->pParams->alpha->blend;
      dds3BillboardSetBlend(v13, blend);
    }
  }
  hDest->matType = hSrc->matType;
}

// 0x1991f60
static void PolygonSet(poltHandle_t *hPolygon, EFFBEHAVIOR_TYPE type, effPolygonTrack_Params_t *pParams) {
  u32 number;
  ptbzHandle_t *phPolyList;
  il2cpp_array_size_t max_length;
  s32 v10;
  ptbzHandle_t *v11;
  s64 v13;
  s32 v14;
  Il2CppClass **v15;
  ptbzHandle_t *v16;
  u32 length;
  u32 split;
  ptbzHandle_t *v19;

  hPolygon->param = pParams;
  number = hPolygon->number;
  if (number)
  {
    phPolyList = hPolygon->phPolyList;
    if (phPolyList)
    {
      max_length = phPolyList->max_length;
      if ((s32)max_length >= 1)
      {
        v10 = 0;
        do
        {
          max_length = phPolyList->max_length;
          ++v10;
        }
        while (v10 < (s32)max_length);
        number = hPolygon->number;
      }
    }
    v11 = NewSpecific(ptbzHandle_t, number);
    hPolygon->phPolyList = v11;
    if (hPolygon->number)
    {
      v13 = 0;
      v14 = 1;
      do
      {
        v16 = hPolygon->phPolyList;
        length = pParams->length;
        split = pParams->split;
        v19 = BezierCreate(length, split);
        v15 = &v16->obj.klass + v13;
        v15[4] = v19;
        v13 = v14++;
      }
      while (v13 < hPolygon->number);
    }
  }
}

// 0x1992120
static void BehaviorSet(poltHandle_t *hPolygon, EFFBEHAVIOR_TYPE type, effBehavior_Params_Basic_t *pParams) {
  bhvrHandle_t *hBehavior;
  bhvrHandle_t *p_hBehavior;
  bhvrHandle_t *v9;

  p_hBehavior = &hPolygon->hBehavior;
  hBehavior = hPolygon->hBehavior;
  if (hBehavior)
    Delete(hBehavior);
  v9 = effCreate(type, hPolygon->number, pParams);
  hPolygon->hBehavior = v9;
}

// 0x19924c0
static void BillboardGeneralSet(poltHandle_t *hPolygon, u32 index) {
  void *hBillboard;
  dds3Billboard_Basic_t *v6;
  bhvrHandle_t *hBehavior;
  dds3Billboard_Basic_t *v8;
  s32 blend;

  hBillboard = hPolygon->hBillboard;
  if (hBillboard)
  {
    dds3BillboardDelete(hBillboard);
  }
  v6 = dds3BillboardGeneralCreate(index);
  hPolygon->hBillboard = v6;
  hBehavior = hPolygon->hBehavior;
  if (hBehavior)
  {
    v8 = hPolygon->hBillboard;
    blend = hBehavior->pParams->alpha->blend;
    dds3BillboardSetBlend(v8, blend);
  }
}

// 0x19923c0
static void BillboardSet(poltHandle_t *hPolygon, DDS3BILLBOARD type, void *resrc) {
  void *hBillboard;
  dds3Billboard_Basic_t *v8;
  bhvrHandle_t *hBehavior;
  dds3Billboard_Basic_t *v10;
  s32 blend;

  hBillboard = hPolygon->hBillboard;
  if (hBillboard)
  {
    dds3BillboardDelete(hBillboard);
  }
  v8 = dds3BillboardCreate(type, resrc);
  hPolygon->hBillboard = v8;
  hBehavior = hPolygon->hBehavior;
  if (hBehavior)
  {
    v10 = hPolygon->hBillboard;
    blend = hBehavior->pParams->alpha->blend;
    dds3BillboardSetBlend(v10, blend);
  }
}

// 0x1992d00
static void Calc(effPartsHandle_t *handle) {
  effPolygonTrackMesh *v4;
  void *v5;
  MeshEditPC *v6;
  void *transform;
  void *v9;
  effOption *option;
  const MethodInfo_306D140 *v11;
  const MethodInfo_3013120 *v12;
  effOption *v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s64 v17;
  u64 v18;
  f32 v19;
  float32x4_t *v20;
  float32x4_t *v21;
  f32 v22;
  f32 v23;
  float32x4_t v24;
  float32x4_t v25;
  bool v26;
  float32x4_t v27;
  float32x4_t v28;
  s64 v29;
  f32 v30;
  const MethodInfo_3014390 *v31;
  s32 v32;
  s64 v33;
  s64 v34;
  void *v35;
  __int128 v36;
  __int128 v37;
  __int128 v38;
  __int128 v39;
  s32 v40;
  bhvrHandle_t *monitor;
  __int128 v46;
  __int128 v47;
  _OWORD v48[2];
  __int128 v49;
  __int128 v50;
  Unity_Collections_NativeArray_effPolygonTrackMesh_Source__o v51;
  Unity_Collections_NativeArray_Vector3__o v52;
  Unity_Collections_NativeArray_Vector3__o v53;

  if (!handle[3].option)
  {
    v4 = Allocate(effPolygonTrackMesh);
    _ctor(v4, 0);
    v5 = Make("effect", 0);
    v6 = Allocate(MeshEditPC);
    _ctor(v6, 0);
    transform = get_transform(v5, 0);
    v9 = get_transform(hook, 0);
    SetParent_61042560(transform, v9, 0, 0);
    (v5->klass[1]._1.declaringType)(v5, v6, v5->klass[1]._1.parent);
    SetOption(v5, handle->option, 0);
    SetAutoHide(v5, 1, 0);
    v4->mesh = v5;
    v4->edit = v6;
    option = handle[2].option;
    v48[0] = 0u;
    v51.m_Buffer = v48;
    *(u64 *)&v51.m_Length = LODWORD(option->adjustRGBA.x);
    __ctor(v51, 4, 0, Method_Unity_Collections_NativeArray_effPolygonTrackMesh_Source___ctor__, v11);
    *(_OWORD *)&v4->source = v48[0];
    if (v4->source.m_Length < 1)
    {
      *(u64 *)&v52.m_Length = 0;
    }
    else
    {
      v13 = handle[2].option;
      v14 = 0;
      v52.m_Length = 0;
      v15 = 4;
      do
      {
        v16 = 8 * v15;
        v17 = v15 - 3;
        ++v15;
        v18 = 1431655766 * SHIDWORD((*(effOption **)((char *)&v13->klass + v16))->_1.namespaze);
        v19 = (s32)(HIDWORD(v18) + (v18 >> 63) + 1);
        v20 = *(float32x4_t **)(*((u64 *)handle[2].monitor + 3) + 16);
        v21 = *(float32x4_t **)(*((u64 *)handle[2].monitor + 3) + 24);
        v22 = 1.0 / v19;
        if (v22 <= 1.0)
          v23 = v22;
        else
          v23 = 1.0;
        v24 = v21[1];
        v25 = v21[2];
        v26 = v22 < 0.0;
        v27 = vsubq_f32(v20[1], v24);
        v28 = vsubq_f32(v20[2], v25);
        v29 = (u64)v4->source.m_Buffer + v14;
        *(float32x4_t *)(v29 + 12) = v24;
        *(float32x4_t *)(v29 + 44) = v25;
        *(u32 *)v29 = v52.m_Length;
        v14 += 116;
        if (v26)
          v30 = 0.0;
        else
          v30 = v23;
        *(float32x4_t *)(v29 + 28) = vsubq_f32(vaddq_f32(v24, vmulq_n_f32(v27, v30)), v24);
        *(float32x4_t *)(v29 + 60) = vsubq_f32(vaddq_f32(v25, vmulq_n_f32(v28, v30)), v25);
        v13 = handle[2].option;
        *(u64 *)&v52.m_Length = (u32)(HIDWORD((*(effOption **)((char *)&v13->klass + v16))->_1.namespaze) + v52.m_Length);
      }
      while (v17 < v4->source.m_Length);
    }
    v48[0] = 0u;
    v52.m_Buffer = v48;
    __ctor(v52, 4, 0, Method_Unity_Collections_NativeArray_Vector3___ctor__, v12);
    v32 = v4->source.m_Length;
    *(_OWORD *)&v4->position = v48[0];
    if (v32 >= 1)
    {
      v33 = 0;
      v34 = 0;
      do
      {
        v53.m_Buffer = &v4->position;
        *(u64 *)&v53.m_Length = *(u32 *)((u64)v4->source.m_Buffer + v33);
        v35 = *((void *)&handle[2].option->adjustRGBA.z + v34);
        v35[3] = _GetSubArray(v53, v35[1].m_AllocatorLabel, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v31);
        ++v34;
        v33 += 116;
      }
      while (v34 < v4->source.m_Length);
    }
    v36 = *(_OWORD *)&v4->source;
    v48[0] = *(_OWORD *)&v4->vertexJob;
    v48[1] = v36;
    v38 = *(_OWORD *)&v4->vertexJob.abgr;
    v39 = *(_OWORD *)&v4->indexJob;
    v49 = *(_OWORD *)&v4->position;
    v37 = v49;
    v50 = v38;
    *(_OWORD *)&v4->vertexJob.source = v36;
    *(_OWORD *)&v4->vertexJob.position = v37;
    v40 = *(u32 *)((char *)v4 + 196);
    v46 = v39;
    v47 = v36;
    v4->indexJob.size = 3;
    *(u32 *)((char *)v4 + 196) = v40;
    *(_OWORD *)&v4->indexJob = v46;
    *(_OWORD *)&v4->indexJob.source = v47;
    v4->indexJob.table = bztpFaceIndex;
    v4->indexJob.head = bztpHeadFaceIndex;
    handle[3].option = (effOption *)v4;
  }
  monitor = handle[3].monitor;
  if (monitor)
    effCalc(monitor);
}

// 0x1993150
static void Draw(effPartsHandle_t *handle) {
  const MethodInfo_3013120 *v2;
  poltHandle_t *v5;
  s64 v6;
  bhvrHandle_t *monitor;
  __int128 v10;
  __int128 v11;
  sdfVector4_t v13;
  _OWORD *p_x;
  __int128 v16;
  __int128 v17;
  __int128 v19;
  _OWORD *v20;
  __int128 v22;
  f32 *v24;
  f32 *v29;
  effOption *option;
  const MethodInfo_3013510 *v31;
  s64 v32;
  s32 v33;
  s32 vertexCount;
  struct sdfVector4_t abgr;
  s64 v36;
  __int128 v37;
  __int128 v38;
  __int128 v39;
  __int128 v40;
  s64 v41;
  effPosture_t *v42;
  __int128 v43;
  __int128 v44;
  __int128 v45;
  s32 v46;
  f32 v47;
  f32 v48;
  s32 indexCount;
  f32 v50;
  f32 v51;
  s32 frame;
  s32 current;
  s32 v54;
  struct sdfVector4_t v55;
  f32 z;
  f32 y;
  f32 x;
  ptbzHandle_t *v59;
  s32 v60;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 scale;
  f32 v88;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 *v97;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 *v101;
  f32 *v102;
  f32 *v103;
  s64 v104;
  s32 count;
  MeshEditPC *edit;
  s32 v118;
  void *v119;
  effPartsHandle_t *klass;
  s64 klass_low;
  f32 v122;
  __int128 v124;
  __int128 v125;
  __int128 v126;
  s32 v127;
  s64 v128;
  s64 v129;
  sdfVector4_t *v131;
  u32 v132;
  f32 v134;
  f32 v135;
  f32 v136;
  f32 w;
  _OWORD *v140;
  __int128 v141;
  __int128 v142;
  s64 v143;
  s32 v144;
  void *v145;
  s64 v146;
  float32x4_t v147;
  f32 v148;
  f32 v149;
  __int128 v151;
  _OWORD *v152;
  __int128 v153;
  struct sdfVector4_t v154;
  long f64 v158;
  long f64 v159;
  s64 v160;
  f32 v161;
  f32 v162;
  f32 v163;
  float32x4_t v168;
  struct sdfVector4_t v169;
  struct sdfVector4_t v170;
  effPartsHandle_t *v173;
  sdfVector4_t v174;
  struct sdfVector4_t v175;
  sdfVector4_t v176;
  sdfMatrix4_t v181;
  sdfVector4_t v182;
  sdfVector4_t v183;
  __int128 v184;
  __int128 v185;
  __int128 v186;
  __int128 v187;
  __int128 v188;
  __int128 v189;
  __int128 v190;
  __int128 v191;
  sdfVector4_t pRot;
  sdfVector4_t pPos;
  sdfMatrix4_t v194;
  f32 *v195;
  s64 v196;
  sdfMatrix4_t v197;
  sdfMatrix4_t v198;
  Unity_Collections_NativeArray_Vector3__o v199;
  Unity_Collections_NativeArray_Vector3__o v200;
  Unity_Collections_NativeArray_Vector3__o v201;
  sdfVector4_t SelCameraEyePos;
  sdfVector4_t v203;
  sdfVector4_t v204;
  sdfVector4_t v206;
  sdfVector4_t v207;

  v195 = 0;
  v196 = 0;
  *(u64 *)&pPos.x = 0;
  *(u64 *)&pPos.z = 0;
  *(u64 *)&pRot.x = 0;
  *(u64 *)&pRot.z = 0;
  *(u64 *)&v183.x = 0;
  *(u64 *)&v183.z = 0;
  *(u64 *)&v182.x = 0;
  *(u64 *)&v182.z = 0;
  v184 = 0u;
  v185 = 0u;
  v186 = 0u;
  v187 = 0u;
  v188 = 0u;
  v189 = 0u;
  v190 = 0u;
  v191 = 0u;
  memset(&v194, 0, sizeof(v194));
  v173 = handle;
  if (!handle[3].option)
    return;
  v199.m_Buffer = &v195;
  *(u64 *)&v199.m_Length = 3;
  v5 = handle;
  v168 = *(float32x4_t *)((char *)&handle[1].klass + 4);
  v6 = *((u64 *)handle[3].monitor + 7);
  __ctor(v199, 2, 0, Method_Unity_Collections_NativeArray_Vector3___ctor__, v2);
  monitor = handle[3].monitor;
  if ((monitor->flag & 1) != 0)
  {
    effEmitterRotateGet(monitor, &pRot);
    effEmitterPositionGet(handle[3].monitor, &pPos);
    v174 = pRot;
    vct_A = v174;
    ToMatrix();
    v13 = pPos;
    vct_A = v13;
    vct_A.w = 1.0;
    SetRow(&mtx_A, 3, vct_A, 0);
    p_x = &vf00.x;
    v16 = p_x[5];
    *(_OWORD *)&v194.m00 = p_x[4];
    *(_OWORD *)&v194.m01 = v16;
    v17 = p_x[7];
    *(_OWORD *)&v194.m02 = p_x[6];
    *(_OWORD *)&v194.m03 = v17;
    goto LABEL_25;
  }
  v10 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&v194.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&v194.m01 = v10;
  v11 = *(_OWORD *)&identityMatrix.m03;
  *(_OWORD *)&v194.m02 = *(_OWORD *)&identityMatrix.m02;
  *(_OWORD *)&v194.m03 = v11;
LABEL_25:
  v19 = *(_OWORD *)&v194.m01;
  v20 = &vf00.x;
  v20[4] = *(_OWORD *)&v194.m00;
  v20[5] = v19;
  v22 = *(_OWORD *)&v194.m03;
  v20[6] = *(_OWORD *)&v194.m02;
  v20[7] = v22;
  SelCameraEyePos = effGetSelCameraEyePos();
  *(f32 *)&v159 = SelCameraEyePos.x;
  v24 = &vf00.x;
  v24[4] = SelCameraEyePos.x;
  v24[5] = SelCameraEyePos.y;
  v24[6] = SelCameraEyePos.z;
  v24[7] = SelCameraEyePos.w;
  sub_1996630(0, v159);
  get_transpose(&v198, &mtx_A, 0);
  v197 = v198;
  v203 = op_Multiply_60923920(&v197, vct_A, 0);
  vct_A = v203;
  v160 = v6;
  v29 = &vf00.x;
  option = handle[3].option;
  v162 = v29[5];
  v163 = v29[4];
  v161 = v29[6];
  v181 = v194;
  BezierVertexBegin(&v181, option);
  if (LODWORD(handle[1].klass))
  {
    v32 = 0;
    v33 = 1;
    do
    {
      v41 = (s64)v5->pMesh->source.m_Buffer + 116 * v32;
      v42 = v5->hBehavior->pPosture[v32];
      v43 = *(_OWORD *)(v41 + 28);
      v44 = *(_OWORD *)(v41 + 44);
      v45 = *(_OWORD *)(v41 + 60);
      v46 = *(u32 *)v41;
      v47 = *(f32 *)(v41 + 76);
      v48 = *(f32 *)(v41 + 80);
      indexCount = *(u32 *)(v41 + 8);
      v51 = *(f32 *)(v41 + 84);
      v50 = *(f32 *)(v41 + 88);
      frame = v42->frame;
      current = *(u32 *)(v41 + 108);
      v54 = *(u32 *)(v41 + 112);
      v188 = *(_OWORD *)(v41 + 12);
      v189 = v43;
      v55 = *(sdfVector4_t *)(v41 + 92);
      v190 = v44;
      v191 = v45;
      if (frame == -2)
      {
        vertexCount = -1;
        abgr = v55;
        goto LABEL_41;
      }
      z = v42->pos.z;
      x = v42->pos.x;
      y = v42->pos.y;
      v59 = v5->phPolyList[v32];
      v175 = v55;
      if (frame)
      {
        if (frame < 0)
          goto LABEL_88;
      }
      {
        *(u64 *)&v59->count = 0;
      }
      else
      {
        v60 = v42->frame;
        *(u64 *)&v59->count = 0;
        if (v60 < 0)
          goto LABEL_88;
      }
      if (!get_STOP(0))
      {
        v62 = v59->top.x;
        v63 = v59->top.y;
        v64 = v59->top.z;
        v66 = v62 - x;
        v67 = v63 - y;
        v68 = v64 - z;
        v69 = sqrtf((f32)(v68 * v68) + (f32)((f32)(v66 * v66) + (f32)(v67 * v67)));
        if (v69 <= 0.00001)
        {
          v47 = zeroVector.x;
          v48 = zeroVector.y;
          v51 = zeroVector.z;
        }
        else
        {
          v47 = v66 / v69;
          v48 = v67 / v69;
          v51 = v68 / v69;
        }
        v71 = v163 - x;
        v72 = v162 - y;
        v73 = v161 - z;
        v74 = sqrtf((f32)(v73 * v73) + (f32)((f32)(v71 * v71) + (f32)(v72 * v72)));
        if (v74 <= 0.00001)
        {
          v75 = zeroVector.x;
          v76 = zeroVector.y;
          v77 = zeroVector.z;
        }
        else
        {
          v75 = v71 / v74;
          v76 = v72 / v74;
          v77 = v73 / v74;
        }
        v79 = (f32)((f32)((f32)((f32)(v51 * v77) + (f32)((f32)(v47 * v75) + (f32)(v48 * v76))) * 1.5708) + 1.5708)
            * 0.15915494;
        v80 = (s32)v79;
        if (v79 == INFINITY)
          v80 = -2147500000.0;
        v81 = v79 - v80;
        if (v81 > 0.5)
        {
          v82 = -1.0;
          goto LABEL_72;
        }
        if (v81 < -0.5)
        {
          v82 = 1.0;
LABEL_72:
          v81 = v81 + v82;
        }
        if (v81 > 0.25)
        {
          v83 = 0.5;
          goto LABEL_77;
        }
        if (v81 < -0.25)
        {
          v83 = -0.5;
LABEL_77:
          v81 = v83 - v81;
        }
        v84 = v81 * 4.0;
        v85 = sqrtf(sqrtf((f32)((f32)((f32)((f32)(v84 * 1.5708) + (f32)((f32)(v84 * (f32)(v84 * v84)) * -0.6459637)) + (f32)((f32)((f32)(v84 * v84) * (f32)(v84 * (f32)(v84 * v84))) * 0.07968968)) + (f32)((f32)((f32)(v84 * v84) * (f32)((f32)(v84 * v84) * (f32)(v84 * (f32)(v84 * v84)))) * -0.0046737655)) + (f32)((f32)((f32)(v84 * v84) * (f32)((f32)(v84 * v84) * (f32)((f32)(v84 * v84) * (f32)(v84 * (f32)(v84 * v84))))) * 0.00015148419)));
        scale = v42->scale;
        v88 = (f32)(v51 * v76) - (f32)(v48 * v77);
        v89 = (f32)(v47 * v77) - (f32)(v51 * v75);
        v90 = (f32)(v48 * v75) - (f32)(v47 * v76);
        v91 = sqrtf((f32)(v90 * v90) + (f32)((f32)(v88 * v88) + (f32)(v89 * v89)));
        if (v91 <= 0.00001)
        {
          v95 = scale;
          scale = v95;
          v92 = zeroVector.x;
          v93 = zeroVector.y;
          v94 = zeroVector.z;
        }
        else
        {
          v92 = v88 / v91;
          v93 = v89 / v91;
          v94 = v90 / v91;
        }
        v50 = v85 * scale;
        v97 = v195;
        v98 = v50 * v92;
        v99 = v50 * v93;
        v100 = v50 * v94;
        *v195 = x - v98;
        v97[1] = y - v99;
        v97[2] = z - v100;
        v101 = v195;
        v195[3] = x;
        v101[4] = y;
        v101[5] = z;
        v102 = v195;
        v195[6] = x + v98;
        v102[7] = y + v99;
        v102[8] = z + v100;
        v103 = v195;
        v104 = v196;
        v201.m_Buffer = v103;
        *(u64 *)&v201.m_Length = v104;
        BezierVertexSet(v59, v201);
        v5 = v173;
        goto LABEL_88;
      }
LABEL_88:
      v59->top.x = x;
      v59->top.y = y;
      v59->top.z = z;
      abgr = v42->abgr;
      if (abgr.w != 0.0)
        goto LABEL_92;
      goto LABEL_9003;
      if (v169.w != 0.0)
      {
LABEL_92:
        count = v59->count;
        if (count < 6)
        {
          vertexCount = -1;
          abgr = v175;
        }
        else
        {
          current = v59->current;
          edit = v5->pMesh->edit;
          vertexCount = edit->vertexCount;
          indexCount = edit->indexCount;
          edit->vertexCount = vertexCount + count + 5;
          v170 = abgr;
          abgr = v170;
          v54 = count;
          edit->indexCount = indexCount
                                  + 4 * count
                                  + bztpHeadFaceIndex.m_Length
                                  - 12;
        }
        goto LABEL_41;
      }
LABEL_9003:
      abgr = v175;
      vertexCount = -1;
LABEL_41:
      v36 = (s64)v5->pMesh->source.m_Buffer + 116 * v32;
      v37 = v188;
      v38 = v189;
      v32 = v33++;
      *(u32 *)v36 = v46;
      *(u32 *)(v36 + 4) = vertexCount;
      *(_OWORD *)(v36 + 12) = v37;
      *(u32 *)(v36 + 8) = indexCount;
      *(_OWORD *)(v36 + 28) = v38;
      *(f32 *)(v36 + 76) = v47;
      v39 = v190;
      v40 = v191;
      *(f32 *)(v36 + 80) = v48;
      *(f32 *)(v36 + 84) = v51;
      *(f32 *)(v36 + 88) = v50;
      *(u32 *)(v36 + 108) = current;
      *(u32 *)(v36 + 112) = v54;
      *(sdfVector4_t *)(v36 + 92) = abgr;
      *(_OWORD *)(v36 + 60) = v40;
      *(_OWORD *)(v36 + 44) = v39;
    }
    while (v32 < v5->number);
  }
  v200.m_Buffer = &v195;
  *(u64 *)&v200.m_Length = Method_Unity_Collections_NativeArray_Vector3__Dispose__;
  _Dispose(v200, v31);
  v118 = *(u32 *)(*(u64 *)(v160 + 32) + 20);
  BezierVertexEnd(v5, v118);
  if (!v5->matType)
    return;
  v119 = Allocate(Project_effPolygonTrack___c__DisplayClass16_0);
  klass = v173[3].klass;
  klass_low = LODWORD(v173[1].klass);
  v119->hBillboard = klass;
  v122 = *((f32 *)v173[2].monitor + 8);
  v124 = *(_OWORD *)&identityMatrix.m01;
  v184 = *(_OWORD *)&identityMatrix.m00;
  v185 = v124;
  v125 = *(_OWORD *)&identityMatrix.m02;
  v126 = *(_OWORD *)&identityMatrix.m03;
  v127 = *((u32 *)v173[3].monitor + 7);
  v119->pPosture = 0;
  v128 = &v119->pPosture;
  v186 = v125;
  v187 = v126;
  v129 = 0;
  v119->pos = zeroVector;
  v131 = &v119->pos;
  v119->scale = zeroVector;
  v119->abgr = zeroVector;
  v132 = LOWORD(v173[2].klass);
  if (v132 > 4)
  {
    if ((v127 & 1) != 0)
      goto LABEL_112;
  }
  else
  {
    if (((1 << v132) & 0x16) != 0)
    {
      v129 = Allocate(System_Action);
      _ctor(v129, v119, Method_Project_effPolygonTrack___c__DisplayClass16_0__Draw_g__DrawTex_0__, 0);
    }
    if ((v127 & 1) != 0)
    {
LABEL_112:
      effEmitterRotateGet(v173[3].monitor, &v183);
      effEmitterPositionGet(v173[3].monitor, &v182);
      v176 = v183;
      vct_A = v176;
      ToMatrix();
      v134 = v182.x;
      v135 = v182.y;
      v136 = v182.z;
      w = v182.w;
      v206.x = v134;
      v206.y = v135;
      v206.z = v136;
      v206.w = w;
      SetRow(&mtx_A, 3, v206, 0);
      v140 = &vf00.x;
      v141 = v140[5];
      v184 = v140[4];
      v185 = v141;
      v142 = v140[7];
      v186 = v140[6];
      v187 = v142;
      goto LABEL_120;
    }
  }
LABEL_120:
  if ((u32)klass_low)
  {
    v143 = 0;
    v144 = 1;
    while (1)
    {
      v145 = *(void **)(*((u64 *)v173[3].monitor + 5) + 8 * v143 + 32);
      *(u64 *)v128 = v145;
      v146 = *(u64 *)v128;
      if ((*(u32 *)(*(u64 *)v128 + 32) & 0x80000000) != 0)
        goto LABEL_124;
      v147 = vmulq_f32(v168, *(float32x4_t *)(v146 + 36));
      *(float32x4_t *)&v119->abgr = v147;
      if (v147.n128_f32[3] <= 0.0)
        goto LABEL_124;
      v148 = *(f32 *)(v146 + 52);
      v119->scale.z = v122;
      *(u32 *)&v119->scale.w = 0;
      v149 = v122 * v148;
      v119->scale.x = v149;
      v119->scale.y = v149;
      *v131 = *(sdfVector4_t *)(v146 + 16);
      if ((v127 & 1) != 0)
        break;
LABEL_123:
      (*(v129 + 24))(*(u64 *)(v129 + 64), *(u64 *)(v129 + 40));
LABEL_124:
      v143 = v144++;
      if (v143 >= klass_low)
        return;
    }
    v151 = v185;
    v152 = &vf00.x;
    v152[4] = v184;
    v152[5] = v151;
    v153 = v187;
    v152[6] = v186;
    v152[7] = v153;
    v154 = *(sdfVector4_t *)(*(u64 *)v128 + 16);
    vct_A = v154;
    vct_A.w = 1.0;
    get_transpose(&v198, &mtx_A, 0);
    v207 = vct_A;
    v197 = v198;
    v204 = op_Multiply_60923920(&v197, v207, 0);
    vct_A = v204;
    *v131 = vct_A;
    goto LABEL_123;
  }
}

// 0x1994ec0
void CalcAndDraw(effPartsHandle_t *handle) {
  if (!get_STOP(0))
  {
    Calc(handle);
LABEL_8:
    goto LABEL_9;
  }
  goto LABEL_8;
LABEL_9:
  if (drawSkip)
    return;
  Draw();
}

// 0x1995070
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfVector4_t v9;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  v9.z = z;
  v9.w = w;
  v9.x = x;
  v9.y = y;
  effEmitterPositionSet(handle[3].monitor, v9);
}

// 0x1995130
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfVector4_t v9;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  v9.z = z;
  v9.w = w;
  v9.x = x;
  v9.y = y;
  effEmitterRotateSet(handle[3].monitor, v9);
}

// 0x19951f0
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *((f32 *)&handle[1].monitor + 1) = z;
  *(f32 *)&handle[1].option = w;
  *((f32 *)&handle[1].klass + 1) = x;
  *(f32 *)&handle[1].monitor = y;
}

// 0x19952a0
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *((f32 *)&handle[1].option + 1) = scale;
  ScaleSet(handle[3].monitor, scale);
}

// 0x1992ac0
static ptbzHandle_t *BezierCreate(u32 face, u32 split) {
  ptbzHandle_t *v5;
  sdfVector4_t **v8;
  s64 v11;
  s64 i;
  Il2CppClass *v13;
  sdfVector4_t **v;

  v5 = Allocate(ptbzHandle_t);
  *(u64 *)&v5->count = 0;
  v5->split = split;
  v5->point = 3 * face * split + 3;
  if (_v)
    return v5;
  v8 = NewSpecific(UnityEngine_Vector4__, 3u);
  _v = v8;
  v11 = 0;
  for (i = 32; ; i += 8)
  {
    v = _v;
    if (v11 >= SLODWORD(v->max_length))
      break;
    v = _v;
    v13 = NewSpecific(sdfVector4_t, 4u);
    *(Il2CppClass **)((char *)&v->obj.klass + i) = v13;
    ++v11;
  }
  return v5;
}

// 0x1992760
static void BezierDelete(ptbzHandle_t *hPolygon) {
  ;
}

// 0x19946a0
static void BezierReset(ptbzHandle_t *hPolygon) {
  *(u64 *)&hPolygon->count = 0;
}

// 0x1995340
static void BezierVertexGet(ptbzHandle_t *hPolygon, void *pVertex, s32 frame) {
  const MethodInfo_3014390 *v4;
  s32 current;
  s32 v9;
  Unity_Collections_NativeArray_Vector3__o v10;

  current = hPolygon->current;
  v9 = -3 * (frame + hPolygon->split * (frame - 1));
  *(u64 *)&v10.m_Length = (u32)(v9 + current);
  if (v9 + current < 0)
    *(u64 *)&v10.m_Length = (u32)(hPolygon->point + v10.m_Length);
  v10.m_Buffer = &hPolygon->pVertex;
  *(void *)pVertex = _GetSubArray(v10, 3, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v4);
}

// 0x19953d0
static void BezierVertexSetSub(ptbzHandle_t *hPolygon, void *pVertex) {
  const MethodInfo_3014390 *v3;
  s32 v6;
  s32 count;
  s32 point;
  Unity_Collections_NativeArray_Vector3__o v9;

  *(u64 *)&v9.m_Length = (u32)hPolygon->current;
  v9.m_Buffer = &hPolygon->pVertex;
  *(void *)pVertex = _GetSubArray(v9, 3, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v3);
  v6 = hPolygon->current + 3;
  point = hPolygon->point;
  count = hPolygon->count;
  if (v6 >= point)
    v6 = 0;
  hPolygon->current = v6;
  if (count < point)
    hPolygon->count = count + 3;
}

// 0x19946b0
static void BezierVertexSet(ptbzHandle_t *hPolygon, void *pVertex) {
  const MethodInfo_3014390 *v3;
  s64 v4;
  char *m_Buffer;
  s32 split;
  s32 count;
  s32 v9;
  s32 v10;
  s32 v11;
  f32 v12;
  f32 v13;
  s32 current;
  f32 v15;
  char *v16;
  f32 v17;
  float32x2_t v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  char *v23;
  s32 v24;
  s32 v25;
  s32 point;
  s32 v27;
  char *v28;
  s64 v29;
  s64 v30;
  s64 v31;
  s32 v32;
  s64 v33;
  s64 v34;
  s32 v35;
  s64 v36;
  char *v37;
  s64 v38;
  s32 v39;
  s64 v40;
  s32 v41;
  s64 v42;
  sdfVector4_t **v;
  f32 v45;
  f32 *v46;
  s32 v47;
  s32 v48;
  s32 v49;
  sdfVector4_t *v53;
  sdfVector4_t *v57;
  sdfVector4_t *v59;
  s64 v62;
  s32 v63;
  Unity_Collections_NativeArray_Vector3__o v64;
  Unity_Collections_NativeArray_T__o v65;
  Unity_Collections_NativeArray_Vector3__o v66;
  Unity_Collections_NativeArray_Vector3__o v67;
  Unity_Collections_NativeArray_Vector3__o v68;
  Unity_Collections_NativeArray_Vector3__o v69;
  Unity_Collections_NativeArray_T__o SubArray;
  sdfVector4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;

  v4 = *(u64 *)&pVertex.m_Length;
  m_Buffer = pVertex.m_Buffer;
  split = hPolygon->split;
  count = hPolygon->count;
  if (split > 1 || count >= 1)
  {
    v63 = split - 1;
    v12 = split;
    v13 = 1.0;
    current = hPolygon->current;
    *(u64 *)&v66.m_Length = (u32)(current - 3);
    if (current - 3 < 0)
      *(u64 *)&v66.m_Length = (u32)(hPolygon->point + v66.m_Length);
    v66.m_Buffer = &hPolygon->pVertex;
    v15 = v13 / v12;
    v16 = _GetSubArray(v66, 3, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v3).m_Buffer;
    if (count < 6 * split)
    {
      if (v63 < 1)
        goto LABEL_5;
      v17 = 0.0;
      {
LABEL_28:
        *(u64 *)&v67.m_Length = (u32)hPolygon->current;
        v67.m_Buffer = &hPolygon->pVertex;
        v23 = _GetSubArray(v67, 3, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v3).m_Buffer;
        v24 = hPolygon->current + 3;
        point = hPolygon->point;
        v25 = hPolygon->count;
        if (v24 >= point)
          v24 = 0;
        hPolygon->current = v24;
        if (v25 < point)
          hPolygon->count = v25 + 3;
        v17 = v15 + v17;
        --split;
        v18.n64_u64[0] = vsub_f32(*(float32x2_t *)m_Buffer, *(float32x2_t *)v16).n64_u64[0];
        if (v17 <= v13)
          v19 = v17;
        else
          v19 = v13;
        if (v17 < 0.0)
          v19 = 0.0;
        v20 = *((f32 *)v16 + 2) + (f32)(v19 * (f32)(*((f32 *)m_Buffer + 2) - *((f32 *)v16 + 2)));
        *(float32x2_t *)v23 = vadd_f32(*(float32x2_t *)v16, vmul_n_f32(v18, v19));
        *((f32 *)v23 + 2) = v20;
        v21 = *((f32 *)v16 + 5) + (f32)(v19 * (f32)(*((f32 *)m_Buffer + 5) - *((f32 *)v16 + 5)));
        *(float32x2_t *)(v23 + 12) = vadd_f32(*(float32x2_t *)(v16 + 12), vmul_n_f32(vsub_f32(*(float32x2_t *)(m_Buffer + 12), *(float32x2_t *)(v16 + 12)), v19));
        *((f32 *)v23 + 5) = v21;
        v22 = *((f32 *)v16 + 8) + (f32)(v19 * (f32)(*((f32 *)m_Buffer + 8) - *((f32 *)v16 + 8)));
        *((float32x2_t *)v23 + 3) = vadd_f32(*(float32x2_t *)(v16 + 24), vmul_n_f32(vsub_f32(*(float32x2_t *)(m_Buffer + 24), *(float32x2_t *)(v16 + 24)), v19));
        *((f32 *)v23 + 8) = v22;
        if (split <= 1)
          goto LABEL_5;
      }
      goto LABEL_28;
    }
    v62 = v4;
    v27 = -3 * hPolygon->split + hPolygon->current;
    *(u64 *)&v68.m_Length = (u32)(v27 - 6);
    if (v27 - 6 < 0)
      *(u64 *)&v68.m_Length = (u32)(hPolygon->point + v68.m_Length);
    v68.m_Buffer = &hPolygon->pVertex;
    v28 = _GetSubArray(v68, 3, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v3).m_Buffer;
    v29 = 0;
    v30 = 4;
    while (1)
    {
      v = _v;
      if (v30 - 4 >= SLODWORD(v->max_length))
        break;
      v = _v;
      v31 = 8 * v30;
      v32 = *(u32 *)&v16[v29 + 8];
      v33 = *(u64 *)&v16[v29];
      ++v30;
      v34 = *(s64 *)((char *)&v->obj.klass + v31);
      *(u32 *)(v34 + 44) = 0;
      *(u64 *)(v34 + 32) = v33;
      *(u32 *)(v34 + 40) = v32;
      v35 = *(u32 *)&v28[v29 + 8];
      v36 = *(u64 *)&v28[v29];
      v37 = &m_Buffer[v29];
      v29 += 12;
      v38 = *(s64 *)((char *)&_v->obj.klass + v31);
      *(u64 *)(v38 + 48) = v36;
      *(u32 *)(v38 + 56) = v35;
      *(u32 *)(v38 + 60) = 0;
      v39 = *((u32 *)v37 + 2);
      v40 = *(s64 *)((char *)&_v->obj.klass + v31);
      *(u64 *)(v40 + 64) = *(u64 *)v37;
      *(u32 *)(v40 + 72) = v39;
      *(u32 *)(v40 + 76) = 0;
      v41 = *((u32 *)v37 + 2);
      v42 = *(s64 *)((char *)&_v->obj.klass + v31);
      *(u64 *)(v42 + 80) = *(u64 *)v37;
      *(u32 *)(v42 + 88) = v41;
      *(u32 *)(v42 + 92) = 0;
    }
    v4 = v62;
    if (v63 < 1)
      goto LABEL_5;
    v45 = 0.0;
    {
LABEL_52:
      *(u64 *)&v69.m_Length = (u32)hPolygon->current;
      v69.m_Buffer = &hPolygon->pVertex;
      v46 = _GetSubArray(v69, 3, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v3).m_Buffer;
      v47 = hPolygon->current + 3;
      v49 = hPolygon->point;
      v48 = hPolygon->count;
      if (v47 >= v49)
        v47 = 0;
      hPolygon->current = v47;
      if (v48 < v49)
      {
        hPolygon->count = v48 + 3;
        v53 = _v[0];
        goto LABEL_57;
      }
      else
      {
      }
      v53 = _v[0];
LABEL_57:
      v45 = v15 + v45;
      v72 = effHermitianSpline(v53, v45);
      *v46 = v72.x;
      v46[1] = v72.y;
      v46[2] = v72.z;
      v57 = _v[1];
      v73 = effHermitianSpline(v57, v45);
      v46[3] = v73.x;
      v46[4] = v73.y;
      v46[5] = v73.z;
      v59 = _v[2];
      v71 = effHermitianSpline(v59, v45);
      --split;
      v46[6] = v71.x;
      v46[7] = v71.y;
      v46[8] = v71.z;
      if (split <= 1)
        goto LABEL_5;
    }
    goto LABEL_52;
  }
LABEL_5:
  v64.m_Buffer = &hPolygon->pVertex;
  *(u64 *)&v64.m_Length = (u32)hPolygon->current;
  SubArray = _GetSubArray(v64, 3, Method_Unity_Collections_NativeArray_Vector3__GetSubArray__, v3);
  v9 = hPolygon->current + 3;
  v11 = hPolygon->point;
  v10 = hPolygon->count;
  if (v9 >= v11)
    v9 = 0;
  hPolygon->current = v9;
  if (v10 < v11)
    hPolygon->count = v10 + 3;
  v65.m_Buffer = m_Buffer;
  *(u64 *)&v65.m_Length = v4;
  _Copy_50413344(v65, 0, SubArray, 0, 3);
}

// 0x1994470
static void BezierVertexBegin(const sdfMatrix4_t *pMatrix, effPolygonTrackMesh *pMesh) {
  sdfDrawTag_t *v5;
  void *transform;
  f32 *p_x;
  void *v11;
  void *v12;
  sdfMatrix4_t v14;
  sdfMatrix4_t v15;
  sdfMatrix4_t v16;
  sdfVector3_t lossyScale;
  sdfVector4_t Row;
  sdfVector3_t v19;
  sdfVector3_t v20;
  sdfQuaternion_t rotation;

  memset(&v16, 0, sizeof(v16));
  v5 = Allocate(sdfDrawTag_t);
  _ctor(v5, 0);
  pptbzDrawTag = v5;
  sdfDrawTagInit(pptbzDrawTag);
  sdfDrawTagLink(pptbzDrawTag, pMesh->mesh->packet);
  transform = get_transform(pMesh->mesh, 0);
  Row = GetRow(pMatrix, 3, 0);
  p_x = &modVec.x;
  v19.y = Row.y * p_x[7];
  v19.x = Row.x * p_x[6];
  v19.z = Row.z * p_x[8];
  set_localPosition(transform, v19, 0);
  v11 = get_transform(pMesh->mesh, 0);
  get_transpose(&v15, pMatrix, 0);
  v16 = v15;
  rotation = get_rotation(&v16, 0);
  set_localRotation(v11, rotation, 0);
  v12 = get_transform(pMesh->mesh, 0);
  get_transpose(&v14, pMatrix, 0);
  v16 = v14;
  lossyScale = get_lossyScale(&v16, 0);
  v20.y = lossyScale.y * modPos.y;
  v20.x = lossyScale.x * modPos.x;
  v20.z = lossyScale.z * modPos.z;
  set_localScale(v12, v20, 0);
  *(u64 *)&pMesh->edit->vertexCount = 0;
}

// 0x1994d60
static bool BezierVertexDraw(ptbzHandle_t *hPolygon, const sdfVector4_t *abgr, effPolygonTrackMesh_Source *source) {
  if (abgr->w == 0.0 || hPolygon->count < 6)
    return 0;
  source->abgr = abgr;
  *(int32x2_t *)&source->current = vrev64_s32(*(int32x2_t *)&hPolygon->count);
  return 1;
}

// 0x1994da0
static void BezierVertexEnd(poltHandle_t *hPolygon, TNEFFECT_BLEND blend) {
  sdfGrOt_t *v5;

  if (hPolygon->pMesh->edit->vertexCount >= 1)
  {
    if (!get_STOP(0))
    {
      hPolygon->pMesh->vertexJob.abgr = hPolygon->abgr;
      (hPolygon->pMesh->klass->vtable._5_PreUpdate.methodPtr)(hPolygon->pMesh, hPolygon->pMesh->klass->vtable._5_PreUpdate.method);
    }
    v5 = effOtGet(blend);
    sdfDrawTagLinkOt(v5, pptbzDrawTag);
  }
  pptbzDrawTag = 0;
}
