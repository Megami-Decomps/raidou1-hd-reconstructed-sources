#include "types.h"
#include "sdf3d.h"
#include "sdf_prim.h"
#include "sdf_vu0.h"
#include "sdfbase.h"
#include "sdfmodel.h"

typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfModelDef_t sdfModelDef_t;
typedef struct sdfModelDrawEnv_t sdfModelDrawEnv_t;
typedef struct sdfModelExtraChunkMarkPos_t sdfModelExtraChunkMarkPos_t;
typedef struct sdfModelNode_t sdfModelNode_t;
typedef struct sdfModelOt_t sdfModelOt_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;

static sdfModelRootNode_t *MakeRoot(sdfModelDef_t *aModelData, void *modelObj);

// 0x225fed0
sdfModelRootNode_t *sdfModelRootNew(void *modelObj) {
  Il2CppObject *Component_object;
  sdfModelRootNode_t *result;
  void **p_monitor;
  sdfModelRootNode_t *v6;
  _OWORD *v7;
  __int128 v9;
  __int128 v10;
  __int128 v11;
  sdfVector4_t *v13;
  s32 v14;
  sdfVector4_t *v15;
  s32 v16;
  struct sdfVector4_t v19;
  s32 v20;

  Component_object = GetComponent_object_(modelObj);
  if (!op_Equality(Component_object, 0, 0))
  {
    p_monitor = &Component_object[2].monitor;
    result = (sdfModelRootNode_t *)Component_object[2].monitor;
    if (result)
      return result;
LABEL_9:
    v6 = Allocate(sdfModelRootNode_t);
    v7 = &v6->tm;
    v9 = *(_OWORD *)&identityMatrix.m02;
    v10 = *(_OWORD *)&identityMatrix.m03;
    v11 = *(_OWORD *)&identityMatrix.m01;
    *v7 = *(_OWORD *)&identityMatrix.m00;
    v7[1] = v11;
    v7[2] = v9;
    v7[3] = v10;
    v13 = &v6->rotate;
    *v13 = vf00;
    v14 = (u8)byte_5755EF6;
    vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
    if (v14)
    {
      v15 = &v6->scale;
      goto LABEL_17;
    }
    else
    {
      v15 = &v6->scale;
LABEL_17:
      v16 = (u8)byte_5756171;
      *v15 = vct_A;
      if (v16)
      {
LABEL_18:
        v6->ditherAlpha = 0;
        *(u32 *)&v6->dissolve = 0;
        v6->color = oneVector;
        v19 = oneVector;
        v6->modelObj = Component_object;
        v6->color_chroma = v19;
        Component_object[2].monitor = v6;
        return (sdfModelRootNode_t *)Component_object[2].monitor;
      }
LABEL_27:
      goto LABEL_18;
    }
    v20 = (u8)byte_5756171;
    *v15 = vct_A;
    if (v20)
      goto LABEL_18;
    goto LABEL_27;
  }
  SetActive(modelObj, 1, 0);
  Component_object = AddComponent_object_(modelObj);
  p_monitor = &Component_object[2].monitor;
  result = (sdfModelRootNode_t *)Component_object[2].monitor;
  if (!result)
    goto LABEL_9;
  return result;
}

// 0x2260230
void sdfModelRootFree(sdfModelRootNode_t *aRoot) {
  void *p_modelObj;
  void *modelObj;
  sdfModelNodeList_t *nodeList;
  Il2CppObject *Component_object;
  bool v7;
  void *gameObject;
  bool v10;

  if (!aRoot)
    return;
  p_modelObj = &aRoot->modelObj;
  modelObj = aRoot->modelObj;
  if (!op_Inequality(aRoot->modelObj, 0, 0))
    goto LABEL_6;
  Component_object = GetComponent_object_(p_modelObj);
  v7 = op_Equality(Component_object, 0, 0);
  gameObject = p_modelObj;
  if (!v7)
    goto LABEL_11;
  goto LABEL_9000;
  if (!v10)
  {
LABEL_11:
LABEL_12:
    Destroy_61007920(gameObject, 0);
    p_modelObj = 0;
    nodeList = aRoot->nodeList;
    if (nodeList)
      goto LABEL_7;
    return;
  }
LABEL_9000:
  gameObject = get_gameObject(gameObject, 0);
  goto LABEL_12;
LABEL_6:
  nodeList = aRoot->nodeList;
  if (nodeList)
LABEL_7:
    _Free(nodeList);
}

// 0x22603b0
sdfModelNode_t *sdfModelSearchNode(sdfModelRootNode_t *aRoot, u32 aId) {
  sdfModelNodeList_t *nodeList;
  sdfModelNode_t *v6;
  void *transform;
  void *v9;
  void *v10;

  nodeList = aRoot->nodeList;
  if (aId >= (s64)nodeList->count)
    return 0;
  v6 = nodeList->items[aId];
  if (!v6)
    return v6;
  transform = v6->transform;
  if (!op_Equality(v6->transform, 0, 0))
    return v6;
  v9 = get_transform(aRoot->modelObj, 0);
  v10 = Find(v9, "dummy_base", 0);
  if (!op_Inequality(v10, 0, 0))
    return v6;
  v6->transform = v10;
  return v6;
}

// 0x2260520
static sdfModelRootNode_t *MakeRoot(sdfModelDef_t *aModelData, void *modelObj) {
  sdfModelRootNode_t *v4;
  sdfModelExtraChunk_t *extraData;
  sdfModelRootNode_t *v6;
  sdfModelNodeList_t *v8;

  v4 = sdfModelRootNew(modelObj);
  extraData = aModelData->extraData;
  v6 = v4;
  v4->extraData = extraData;
  v8 = SetNodeList(v6->modelObj, aModelData->extraData->ndnm);
  v6->nodeList = v8;
  return v6;
}

// 0x2260c10
sdfModelRootNode_t *sdfModelMake(sdfModelDef_t *aModelData, void *modelObj) {
    return 0;
}

// 0x2260c70
sdfModelRootNode_t *sdfModelMake_2(sdfModelDef_t *aModelData) {
  Il2CppObject *prefab;
  Il2CppObject *v4;
  sdfModelRootNode_t *v6;
  sdfModelExtraChunk_t *extraData;
  sdfModelRootNode_t *v8;
  sdfModelNodeList_t *v10;

  prefab = aModelData->prefab;
  v4 = Instantiate_object_(prefab);
  v6 = sdfModelRootNew(v4);
  extraData = aModelData->extraData;
  v8 = v6;
  v6->extraData = extraData;
  v10 = SetNodeList(v8->modelObj, aModelData->extraData->ndnm);
  v8->nodeList = v10;
  return v8;
}

// 0x2260de0
s32 sdfModelGetNodeIndexByName(sdfModelRootNode_t *aRoot, char *aName) {
  char *ndnm;
  s64 v5;

  ndnm = aRoot->extraData->ndnm;
  if (!ndnm || SLODWORD(ndnm->max_length) < 1)
    return -1;
  v5 = 0;
  while (!Equals_54828784(ndnm[v5], aName, 0))
  {
    if (++v5 >= SLODWORD(ndnm->max_length))
      return -1;
  }
  return v5;
}

// 0x2260ea0
char *sdfModelGetNodeName(sdfModelRootNode_t *aRoot, s32 aIndex) {
  char *ndnm;

  if ((aIndex & 0x80000000) == 0 && (ndnm = aRoot->extraData->ndnm) != 0 && SLODWORD(ndnm->max_length) >= aIndex)
  {
    return ndnm[aIndex];
  }
  else
  {
    return Empty;
  }
}

// 0x2260f30
void sdfModelEvalTm(sdfModelRootNode_t *aRoot) {
  ;
}

// 0x2260f40
void sdfModelOtInit(sdfModelOt_t *aModelOt, sdfGrOt_t *aOt0, sdfGrOt_t *aOt1, sdfGrOt_t *aOt2, sdfGrOt_t *aOt3) {
  Il2CppObject *v11;
  Il2CppClass *v12;
  sdfGrOt_t *ot;
  sdfGrOt_t *v14;
  sdfGrOt_t *v16;

  v11 = Allocate(sdfModelOt_t);
  v12 = NewSpecific(sdfGrOt_t, 4u);
  v11[1].klass = v12;
  _ctor(v11, 0);
  aModelOt = (sdfModelOt_t *)v11;
  ot = aModelOt->ot;
  ot[0] = aOt0;
  v14 = aModelOt->ot;
  v16[3] = aOt3;
  aOt0->renderQueue = 2100;
  aOt1->renderQueue = 3100;
  aOt2->renderQueue = 3100;
  aOt3->renderQueue = 3100;
}

// 0x2261170
void sdfModelLinkOt(sdfModelOt_t *aOt, sdfModelRootNode_t *aRoot) {
  sdf3DLightParallelPacket_t *light;
  sdf3DLightParallelPacket_t *p_light;
  sdf3DFogPacket_t *p_fog;
  void *gameObject;
  sdfGrOt_t *ot;
  sdf3DLightParallelPacket_t *v10;
  void *v15;
  void *transform;
  f32 *p_x;
  void *v19;
  void *v20;
  s64 v21;
  s64 v22;
  u64 *v23;
  s64 v24;
  u64 *v25;
  s64 v26;
  u64 *v27;
  u64 *v28;
  sdfMatrix4_t v29;
  sdfMatrix4_t v30;
  sdfVector4_t Row;
  sdfVector3_t v32;
  sdfQuaternion_t rotation;

  p_light = &aRoot->light;
  light = aRoot->light;
  memset(&v30, 0, sizeof(v30));
  if (light)
    goto LABEL_3;
  goto LABEL_9000;
  if (v10)
  {
LABEL_3:
    p_fog = &aRoot->fog;
    if (aRoot->fog)
      goto LABEL_4;
    goto LABEL_11;
  }
LABEL_9000:
  p_light = LightDefault;
  p_fog = &aRoot->fog;
  if (aRoot->fog)
  {
LABEL_4:
    gameObject = get_gameObject(aRoot->modelObj, 0);
    if (get_isStatic(gameObject, 0))
      goto LABEL_5;
    goto LABEL_14;
  }
LABEL_11:
  p_fog = FogDefault;
  v15 = get_gameObject(aRoot->modelObj, 0);
  if (get_isStatic(v15, 0))
  {
LABEL_5:
    ot = aOt->ot;
    if (SLODWORD(ot->max_length) < 1)
      return;
    goto LABEL_20;
  }
LABEL_14:
  transform = get_transform(aRoot->modelObj, 0);
  Row = GetRow(&aRoot->tm, 3, 0);
  p_x = &modVec.x;
  v32.y = Row.y * p_x[7];
  v32.x = Row.x * p_x[6];
  v32.z = Row.z * p_x[8];
  set_localPosition(transform, v32, 0);
  v19 = get_transform(aRoot->modelObj, 0);
  get_transpose(&v29, &aRoot->tm, 0);
  v30 = v29;
  rotation = get_rotation(&v30, 0);
  set_localRotation(v19, rotation, 0);
  v20 = get_transform(aRoot->modelObj, 0);
  set_localScale(v20, *(sdfVector3_t *)&aRoot->scale.x, 0);
  ot = aOt->ot;
  if (SLODWORD(ot->max_length) >= 1)
  {
LABEL_20:
    v21 = 4;
    do
    {
      v23 = *((u64 **)&aRoot->modelObj->drawTag->obj.klass + v21);
      if (v23 && v23[3])
      {
        v24 = *((u64 *)&ot->obj.klass + v21);
        v26 = *(u64 *)(v24 + 32);
        v25 = (v24 + 32);
        v27 = (v26 + 16);
        if (v26)
          v28 = v27;
        else
          v28 = v25 - 1;
        *v28 = v23;
        *v25 = v23;
        ot = aOt->ot;
      }
      v22 = v21 - 3;
      ++v21;
    }
    while (v22 < SLODWORD(ot->max_length));
  }
}

// 0x2261450
void sdfModelLinkOt_PosOnly(sdfModelRootNode_t *aRoot) {
  sdf3DLightParallelPacket_t *p_light;
  sdf3DFogPacket_t *p_fog;
  void *gameObject;
  void *v10;
  void *transform;
  f32 *p_x;
  void *v14;
  void *v15;
  sdfMatrix4_t v16;
  sdfMatrix4_t v17;
  sdfVector4_t Row;
  sdfVector3_t v19;
  sdfQuaternion_t rotation;

  p_light = &aRoot->light;
  if (aRoot->light)
  {
    p_fog = &aRoot->fog;
    if (aRoot->fog)
      goto LABEL_4;
    goto LABEL_10;
  }
  p_light = LightDefault;
  p_fog = &aRoot->fog;
  if (aRoot->fog)
  {
LABEL_4:
    gameObject = get_gameObject(aRoot->modelObj, 0);
    if (get_isStatic(gameObject, 0))
      return;
    goto LABEL_13;
  }
LABEL_10:
  p_fog = FogDefault;
  v10 = get_gameObject(aRoot->modelObj, 0);
  if (!get_isStatic(v10, 0))
  {
LABEL_13:
    transform = get_transform(aRoot->modelObj, 0);
    Row = GetRow(&aRoot->tm, 3, 0);
    p_x = &modVec.x;
    v19.y = Row.y * p_x[7];
    v19.x = Row.x * p_x[6];
    v19.z = Row.z * p_x[8];
    set_localPosition(transform, v19, 0);
    v14 = get_transform(aRoot->modelObj, 0);
    get_transpose(&v16, &aRoot->tm, 0);
    v17 = v16;
    rotation = get_rotation(&v17, 0);
    set_localRotation(v14, rotation, 0);
    v15 = get_transform(aRoot->modelObj, 0);
    set_localScale(v15, *(sdfVector3_t *)&aRoot->scale.x, 0);
  }
}

// 0x2261650
void sdfModelSetDrawEnv(sdfModelDrawEnv_t *aEnv) {
  sdfPrimTransPacket_t *transPacket;
  void **p_OPAQUE_TEST_ELEM;
  void *v6;
  sdfPrimTransPacket_t *v8;
  sdfPrimTransPacket_t *v12;
  sdfPrimTransPacket_t *v16;
  Set *set;
  s64 v21;
  void **p_transPacket;
  u64 *v23;
  void *v24;
  u64 *v25;
  u64 *v26;
  u64 *v27;

  transPacket = aEnv->set[0].transPacket;
  p_OPAQUE_TEST_ELEM = &OPAQUE_TEST_ELEM;
  v6 = *p_OPAQUE_TEST_ELEM;
  transPacket->test = (SDF_GS_TEST *)*p_OPAQUE_TEST_ELEM;
  transPacket->alpha = OPAQUE_ALPHA_ELEM;
  v8 = aEnv->set[1].transPacket;
  v8->test = SEMITRANS_TEST_ELEM;
  v8->alpha = SEMITRANS_ALPHA_ELEM;
  v12 = aEnv->set[2].transPacket;
  v12->test = ADDTRANS_TEST_ELEM;
  v12->alpha = ADDTRANS_ALPHA_ELEM;
  v16 = aEnv->set[3].transPacket;
  v16->test = SUBTRANS_TEST_ELEM;
  v16->alpha = SUBTRANS_ALPHA_ELEM;
  set = aEnv->set;
  if (SLODWORD(set->max_length) >= 1)
  {
    v21 = 0;
    p_transPacket = &set[0].transPacket;
    do
    {
      v23 = *(p_transPacket - 1);
      v24 = *p_transPacket;
      v23[2] = 0;
      v23[3] = 0;
      v25 = v23 + 3;
      v23[4] = 0;
      v26 = v23 + 4;
      if (*v26)
        v27 = (*v26 + 16);
      else
        v27 = v25;
      *v27 = v24;
      *v26 = v24;
      ++v21;
      p_transPacket += 2;
    }
    while (v21 < SLODWORD(set->max_length));
  }
}

// 0x2261b00
void sdfModelDrawEnvLinkOt(sdfModelOt_t *aOt, sdfModelDrawEnv_t *aEnv) {
  sdfGrOt_t *ot;
  s64 v6;
  s64 v7;
  sdfDrawTag_t *v8;
  sdfGrOt_t *v9;
  sdfDrawTag_t *p_tagHead;
  sdfDrawTag_t *tagHead;

  if (aOt)
  {
    ot = aOt->ot;
    if (SLODWORD(ot->max_length) >= 1)
    {
      v6 = 0;
      v7 = 32;
      do
      {
        v8 = *(sdfDrawTag_t *)((char *)&aEnv->set->obj.klass + v7);
        if (v8->tail)
        {
          v9 = ot[v6];
          p_tagHead = &v9->tagHead;
          tagHead = v9->tagHead;
          if (!tagHead)
          {
            v9->tagTail = v8;
          }
          v8->next = tagHead;
          p_tagHead = v8;
          ot = aOt->ot;
        }
        ++v6;
        v7 += 16;
      }
      while (v6 < SLODWORD(ot->max_length));
    }
  }
}

// 0x2261bd0
s32 sdfModelGetMarkPosCount(sdfModelRootNode_t *aRoot) {
  return aRoot->extraData->mpos->max_length;
}

// 0x2261be0
void sdfModelMakeMarkPosMatrix(sdfModelRootNode_t *aRoot, sdfModelExtraChunkMarkPos_t *aMark) {
  u32 nodeId;
  sdfModelNode_t *v6;
  f32 x;
  f32 y;
  f32 z;
  f32 v11;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  float32x2_t *v19;
  f32 v20;
  int32x2_t v23;
  int32x2_t v24;
  float32x2_t v25;
  float32x2_t v26;
  f32 v28;
  f32 v29;
  f32 v30;
  long f64 v33;
  sdfMatrix4_t v35;
  __int128 v36;
  __int128 v37;
  __int128 v38;
  __int128 v39;
  sdfVector4_t v40;

  nodeId = aMark->nodeId;
  v36 = 0u;
  v37 = 0u;
  v38 = 0u;
  v39 = 0u;
  v6 = sdfModelSearchNode(aRoot, nodeId);
  x = aMark->forward.x;
  y = aMark->forward.y;
  z = aMark->forward.z;
  v11 = -z;
  vct_A.x = x;
  vct_A.y = v11;
  vct_A.z = y;
  vct_A.w = 0.0;
  SetRow(&mtx_A, 2, vct_A, 0);
  vct_B = vct_A;
  v14 = aMark->up.y;
  v15 = aMark->up.z;
  v16 = aMark->up.x;
  v17 = -v15;
  vct_A.x = v16;
  vct_A.y = v17;
  vct_A.z = v14;
  vct_A.w = 0.0;
  v20 = -v19[3].n64_f32[0];
  v19[2].n64_u64[0] = vneg_f32(v19[2]).n64_u64[0];
  v19[3].n64_f32[0] = v20;
  SetRow(&mtx_A, 1, vct_A, 0);
  v23.n64_u64[0] = *(u64 *)&vct_B.y;
  v24.n64_u64[0] = *(u64 *)&vct_A.y;
  v25.n64_u32[0] = vdup_lane_s32(v23, 1).n64_u32[0];
  v26.n64_u32[0] = vdup_lane_s32(v24, 1).n64_u32[0];
  v25.n64_u32[1] = LODWORD(vct_B.x);
  v26.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v26.n64_f32[1] * v23.n64_f32[0]) - (f32)(v25.n64_f32[1] * v24.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v24, v25), vmul_f32(v26, v23));
  sub_1949110(0);
  SetRow(&mtx_A, 0, vct_A, 0);
  v28 = aMark->pos.y;
  v29 = aMark->pos.z;
  v30 = aMark->pos.x;
  v40.x = v30;
  v40.y = -v29;
  v40.z = v28;
  v40.w = 1.0;
  SetRow(&mtx_A, 3, v40, 0);
  get_tm(&v35, v6);
  v36 = *(_OWORD *)&v35.m00;
  v37 = *(_OWORD *)&v35.m01;
  v33 = *(long f64 *)&v35.m02;
  v38 = *(_OWORD *)&v35.m02;
  v39 = *(_OWORD *)&v35.m03;
  sub_19636F0(&v36, 0, v33);
}

// 0x2262260
void sdfModelMakeMarkPos(sdfModelRootNode_t *aRoot, sdfModelExtraChunkMarkPos_t *aMark) {
  sdfModelNode_t *v5;
  f32 x;
  f32 y;
  f32 z;
  sdfMatrix4_t v12;
  sdfMatrix4_t v13;
  sdfMatrix4_t v14;
  sdfVector3_t v15;
  sdfVector3_t v16;

  v5 = sdfModelSearchNode(aRoot, aMark->nodeId);
  x = aMark->pos.x;
  y = aMark->pos.y;
  z = aMark->pos.z;
  get_tm(&v13, v5);
  v14 = v13;
  get_transpose(&v12, &v14, 0);
  v14 = v12;
  v16.y = -z;
  v16.z = y;
  v16.x = x;
  v15 = MultiplyPoint3x4(&v14, v16, 0);
  *(sdfVector3_t *)&vct_A.x = v15;
  vct_A.w = 0.0;
}

// 0x22623d0
sdfModelExtraChunkMarkPos_t *sdfModelSearchMarkPosData(sdfModelRootNode_t *aRoot, s32 aId) {
  sdfModelExtraChunkMarkPos_t *mpos;
  s64 max_length;
  sdfModelExtraChunkMarkPos_t *i;
  sdfModelExtraChunkMarkPos_t *result;

  mpos = aRoot->extraData->mpos;
  if ((s32)mpos->max_length < 1)
    return 0;
  max_length = (u32)mpos->max_length;
  for (i = mpos; ; ++i)
  {
    result = i;
    if (i->id == aId)
      break;
    if (!--max_length)
      return 0;
  }
  return result;
}

// 0x2262420
bool sdfModelGetMarkPosMatrix(sdfModelRootNode_t *aRoot, s32 aId) {
  sdfModelExtraChunkMarkPos_t *mpos;
  s64 max_length;
  sdfModelExtraChunkMarkPos_t *i;

  mpos = aRoot->extraData->mpos;
  if ((s32)mpos->max_length < 1)
    return 0;
  max_length = (u32)mpos->max_length;
  for (i = mpos; i->id != aId; ++i)
  {
    if (!--max_length)
      return 0;
  }
  sdfModelMakeMarkPosMatrix(aRoot, i);
  return 1;
}

// 0x2262480
bool sdfModelGetMarkPos(sdfModelRootNode_t *aRoot, s32 aId) {
  sdfModelExtraChunkMarkPos_t *mpos;
  s64 max_length;
  sdfModelExtraChunkMarkPos_t *i;

  mpos = aRoot->extraData->mpos;
  if ((s32)mpos->max_length < 1)
    return 0;
  max_length = (u32)mpos->max_length;
  for (i = mpos; i->id != aId; ++i)
  {
    if (!--max_length)
      return 0;
  }
  sdfModelMakeMarkPos(aRoot, i);
  return 1;
}

// 0x22624e0
s32 sdfModelGetUniqueID(sdfModelRootNode_t *aRoot) {
  return aRoot->extraData->uniq;
}
