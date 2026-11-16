#include "types.h"
#include "dds3billboard.h"
#include "dds3effect.h"
#include "dds3kerneldraw.h"
#include "effstat.h"
#include "mdl.h"
#include "mdleffect.h"
#include "model.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"

typedef struct dds3ModelEffectCtrlr_t dds3ModelEffectCtrlr_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct mdlEffectResrcItem_t mdlEffectResrcItem_t;
typedef struct mdlEffectResrcList_t mdlEffectResrcList_t;
typedef struct mdlEffectResrc_IPU_t mdlEffectResrc_IPU_t;
typedef struct pibChunkItem_t pibChunkItem_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;

static void DeleteResrc_IPU(mdlEffectResrc_IPU_t *ipu);
static void StartResrc_IPU(mdlEffectResrc_IPU_t *ipu);
static dds3ModelEffectCtrlr_t *CreateCtrlr(dds3ModelHandle_t *aHandle, dds3ModelEffectType aType, s32 aPlayGroup);
static void *Dup_D3P(mdlEffectResrcItem_t *efcResPtr);
static mdlEffectResrcItem_t *GetResrc(dds3ModelHandle_t *handle, s32 effectIndex);
static void Create_P2A_D3P(dds3ModelHandle_t *aHandle, pibChunkItem_t *aData, s32 aPlayGroup, dds3ModelEffectType aType, void *aDupFunc);
static void Create_IPU(dds3ModelHandle_t *aHandle, pibChunkItem_t *aData, s32 aPlayGroup);
static void Draw_IPU(dds3ModelEffectCtrlr_t *effect);
static void Create(dds3ModelHandle_t *aHandle, pibChunkItem_t *aData, s32 aPlayGroup);
static void P2A_D3P_GetPos(sdfModelRootNode_t *model, dds3ModelEffectCtrlr_t *effect, sdfVector4_t *vect);

// 0x1d64470
void mdlEffectCreateResrc_D3P(mdlEffectResrcList_t *listPtr, void *data) {
  s64 count;
  Il2CppClass **v6;
  Il2CppClass *v8;
  effHandle_t *v9;

  count = listPtr->count;
  v6 = &listPtr->items->obj.klass + count;
  listPtr->count = count + 1;
  v8 = v6[4];
  v8->_1.name = (&xmmword_0 + 1);
  v9 = dds3EffectLoad(data);
  v8->_1.namespaze = v9;
}

// 0x1d64510
void mdlEffectCreateResrc_IPU(mdlEffectResrcList_t *listPtr, void *data) {
  s64 count;
  Il2CppClass **v6;
  Il2CppClass *v8;
  mdlEffectResrc_IPU_t *v9;
  mdlEffectResrc_IPU_t *p_fields;

  count = listPtr->count;
  v6 = &listPtr->items->obj.klass + count;
  listPtr->count = count + 1;
  v8 = v6[4];
  v9 = Allocate(mdlEffectResrc_IPU_t);
  _ctor(v9, 0);
  if (!data)
  {
    v9->data = 0;
    p_fields = &v9->fields;
  }
  v8->_1.namespaze = v9;
  v8->_1.name = (&xmmword_0 + 3);
}

// 0x1d64630
static void DeleteResrc_IPU(mdlEffectResrc_IPU_t *ipu) {
  void *decoder;

  if (ipu->playing)
  {
    decoder = ipu->decoder;
    if (!op_Inequality(ipu->decoder, 0, 0))
      return;
    goto LABEL_6;
    if (op_Inequality(decoder, 0, 0))
LABEL_6:
      Stop(ipu->decoder, 0);
  }
}

// 0x1d646d0
static void StartResrc_IPU(mdlEffectResrc_IPU_t *ipu) {
  if (!ipu->playing)
  {
    ipu->playing = 1;
    Play(ipu->decoder, 0);
  }
}

// 0x1d646f0
mdlEffectResrcList_t *mdlEffectResrcListNew(s32 initCapa) {
  mdlEffectResrcList_t *v3;

  v3 = (mdlEffectResrcList_t *)Allocate(mdlEffectResrcList_t);
  _ctor(v3, initCapa, 4, 0);
  return v3;
}

// 0x1d64760
void mdlEffectResrcListFree(mdlEffectResrcList_t *efcResList) {
  s64 v3;
  mdlEffectResrcItem_t *v4;
  u32 type;
  void *handle;
  s64 naturalAligment;
  void *klass;
  s64 v9;

  if (efcResList)
  {
    if (efcResList->count >= 1)
    {
      v3 = 0;
      while (1)
      {
        v4 = efcResList->items[v3];
        type = v4->type;
        if (type != 3)
          break;
        handle = v4->handle;
        if (handle)
        {
          if (handle->klass->_2.naturalAligment < (u32)naturalAligment || handle->klass->_2.typeHierarchy[naturalAligment - 1] != mdlEffectResrc_IPU_t)
          {
LABEL_30:
          }
        }
        if (BYTE1(handle[1].monitor))
        {
          klass = handle[2].klass;
          if (op_Inequality(handle[2].klass, 0, 0))
            goto LABEL_27;
          goto LABEL_9000;
          if (op_Inequality(klass, 0, 0))
LABEL_27:
            Stop(handle[2].klass, 0);
LABEL_9000:
        }
LABEL_7:
        if (++v3 >= efcResList->count)
          goto LABEL_28;
      }
      if (type != 1)
        goto LABEL_7;
      handle = v4->handle;
      if (!handle)
        goto LABEL_6;
      goto LABEL_9001;
      if (!handle)
      {
LABEL_6:
        Delete(handle);
        goto LABEL_7;
      }
LABEL_9001:
      if (handle->klass->_2.naturalAligment < (u32)v9 || handle->klass->_2.typeHierarchy[v9 - 1] != effHandle_t)
      {
        goto LABEL_30;
      }
      goto LABEL_6;
    }
LABEL_28:
    _Free(efcResList);
  }
}

// 0x1d64990
static dds3ModelEffectCtrlr_t *CreateCtrlr(dds3ModelHandle_t *aHandle, dds3ModelEffectType aType, s32 aPlayGroup) {
  s16 v4;
  dds3ModelEffectCtrlr_t *v7;
  dds3ModelEffectCtrlr_t *p_effects;
  dds3ModelEffectCtrlr_t *effects;

  v4 = aPlayGroup;
  v7 = (dds3ModelEffectCtrlr_t *)Allocate(dds3ModelEffectCtrlr_t);
  _ctor(v7, 0);
  effects = aHandle->effects;
  p_effects = &aHandle->effects;
  v7->type = aType;
  v7->playGroup = v4;
  v7->next = effects;
  p_effects = v7;
  return v7;
}

// 0x1d64a30
static void *Dup_D3P(mdlEffectResrcItem_t *efcResPtr) {
  effHandle_t *handle;
  void *result;

  handle = efcResPtr->handle;
  if (!handle)
  result = (void *)dds3EffectCopy(handle);
  ++efcResPtr->count;
  return result;
}

// 0x1d64b10
static mdlEffectResrcItem_t *GetResrc(dds3ModelHandle_t *handle, s32 effectIndex) {
  mdlEffectResrcList_t *effectResrcList;
  mdlEffectResrcItem_t *v4;

  effectResrcList = handle->resrc->effectResrcList;
  if (!effectResrcList || effectResrcList->count <= effectIndex)
    return 0;
  v4 = effectResrcList->items[effectIndex];
  if (v4->handle)
    return v4;
  else
    return 0;
}

// 0x1d64b50
static void Create_P2A_D3P(dds3ModelHandle_t *aHandle, pibChunkItem_t *aData, s32 aPlayGroup, dds3ModelEffectType aType, void *aDupFunc) {
  s16 v7;
  mdlEffectResrcList_t *effectResrcList;
  mdlEffectResrcItem_t *v12;
  s32 klass_high;
  sdfModelRootNode_t *modelRoot;
  s32 v16;
  s32 v17;
  dds3ModelEffectCtrlr_t *p_effects;
  dds3ModelEffectCtrlr_t *v19;
  dds3ModelEffectCtrlr_t *v20;
  s64 v21;
  void *v22;
  sdfModelExtraChunkMarkPos_t *v23;
  sdfModelExtraChunkMarkPos_t *v24;

  v7 = aPlayGroup;
  effectResrcList = aHandle->resrc->effectResrcList;
  if (effectResrcList && effectResrcList->count > WORD1(aData[1].klass))
  {
    v12 = effectResrcList->items[WORD1(aData[1].klass)];
    if (v12 && v12->handle != 0)
    {
      klass_high = HIDWORD(aData[1].klass);
      modelRoot = aHandle->modelRoot;
      v16 = *((u32 *)&aData->fields + 1);
      LOWORD(v17) = aData[1].klass;
      p_effects = &aHandle->effects;
      do
      {
        v23 = sdfModelSearchMarkPosData(modelRoot, v16);
        if (v23)
        {
          v24 = v23;
          v19 = Allocate(dds3ModelEffectCtrlr_t);
          _ctor(v19, 0);
          v20 = p_effects;
          v19->playGroup = v7;
          v19->type = aType;
          v19->next = v20;
          p_effects = v19;
          v21 = Allocate(Work_P2A_D3P);
          v22 = (aDupFunc->invoke_impl)(aDupFunc->method_code, v12, aDupFunc->method);
          v19->handle = v22;
          v19->work = (void *)v21;
          *(u64 *)(v21 + 16) = v12;
          *(u64 *)(v21 + 24) = v24;
          v21 += 24;
          *(u32 *)(v21 + 8) = klass_high;
        }
        ++v16;
        v17 = (u16)(v17 - 1);
      }
      while (v17);
    }
  }
}

// 0x1d64d80
static void Create_IPU(dds3ModelHandle_t *aHandle, pibChunkItem_t *aData, s32 aPlayGroup) {
  s16 v4;
  mdlEffectResrcList_t *effectResrcList;
  mdlEffectResrcItem_t *v9;
  void *handle;
  sdfModelRootNode_t *modelRoot;
  sdfModelNode_t *items;
  s32 NodeIndexByName;
  void *gameObject;
  Il2CppObject *v17;
  dds3ModelEffectCtrlr_t *v18;
  dds3ModelEffectCtrlr_t *effects;
  s64 v20;

  v4 = aPlayGroup;
  effectResrcList = aHandle->resrc->effectResrcList;
  if (effectResrcList && effectResrcList->count > HIWORD(aData[1].klass))
  {
    v9 = effectResrcList->items[HIWORD(aData[1].klass)];
    handle = v9->handle;
    if (v9 && handle != 0)
    {
      if (!LOBYTE(handle[1].monitor))
      {
        modelRoot = aHandle->modelRoot;
        items = modelRoot->nodeList->items;
        NodeIndexByName = sdfModelGetNodeIndexByName(modelRoot, *(char **)&handle[1].klass->_1.byval_arg.bits);
        gameObject = get_gameObject(items[NodeIndexByName]->transform, 0);
        v17 = AddComponent_object_(gameObject);
        Set(v17, handle[1].klass->_1.byval_arg.data, BYTE5(aData[1].klass) != 0, 0);
        handle[2].klass = (Project_dds3EffectHandle_t_c *)v17;
        LOBYTE(handle[1].monitor) = 1;
        v18 = Allocate(dds3ModelEffectCtrlr_t);
        _ctor(v18, 0);
        v18->playGroup = v4;
        effects = aHandle->effects;
        v18->type = 3;
        v18->next = effects;
        aHandle->effects = v18;
        v20 = Allocate(Work_IPU);
        v18->handle = handle;
        v18->work = (void *)v20;
        *(u64 *)(v20 + 16) = aHandle;
        v20 += 16;
        *(u32 *)(v20 + 8) = aData[1].klass;
      }
    }
  }
}

// 0x1d65010
static void Draw_IPU(dds3ModelEffectCtrlr_t *effect) {
  void *handle;
  void *work;
  dds3ModelHandle_t *klass;
  void *v8;

  handle = effect->handle;
  work = effect->work;
  klass = work[1].klass;
  Draw(handle[2].klass, klass, 0);
  if (!BYTE1(handle[1].monitor))
  {
    if (mdlGetMotionFrame(klass) >= (s64)LODWORD(work[1].monitor) && !BYTE1(handle[1].monitor))
    {
      v8 = handle[2].klass;
      BYTE1(handle[1].monitor) = 1;
      Play(v8, 0);
    }
  }
}

// 0x1d65170
static void Create(dds3ModelHandle_t *aHandle, pibChunkItem_t *aData, s32 aPlayGroup) {
  u32 type;
  void *v8;

  type = aData->type;
  if (type == 5)
  {
    Create_IPU(aHandle, aData, aPlayGroup);
  }
  else if (type == 2)
  {
    v8 = Allocate(System_Func_mdlEffectResrcItem_t__dds3EffectHandle_t_);
    object____ctor(v8, 0, Method_Project_mdlEffect_Dup_D3P__, 0);
    Create_P2A_D3P(aHandle, aData, aPlayGroup, 1u, v8);
  }
}

// 0x1d65250
void mdlEffectGen(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aPlayGroup) {
  pibHeaderChunk_t *effectData;
  pibChunk_t *chunk;
  s64 max_length;
  pibChunk_t *i;
  pibChunkItem_t *item;
  s64 v11;

  effectData = aHandle->resrc->effectData;
  if (effectData)
  {
    chunk = effectData->chunk;
    if ((s32)chunk->max_length >= 1)
    {
      max_length = (u32)chunk->max_length;
      for (i = chunk; i->group != aGroup; ++i)
      {
        if (!--max_length)
          return;
      }
      item = i->item;
      if (SLODWORD(item->max_length) >= 1)
      {
        v11 = 0;
        do
          Create(aHandle, item[v11++], aPlayGroup);
        while (v11 < SLODWORD(item->max_length));
      }
    }
  }
}

// 0x1d65310
void mdlFree(dds3ModelEffectCtrlr_t *aCtrlr) {
  void *handle;

  if (aCtrlr->type == 1)
  {
    handle = aCtrlr->handle;
    if (!handle)
      goto LABEL_11;
    goto LABEL_9000;
    if (!handle)
    {
LABEL_11:
      Delete(handle);
      return;
    }
LABEL_9000:
    goto LABEL_11;
  }
}

// 0x1d653e0
void mdlEffectStop(dds3ModelHandle_t *aHandle, s32 aPlayGroup) {
  dds3ModelEffectCtrlr_t *effects;
  dds3ModelEffectCtrlr_t *p_effects;
  dds3ModelEffectCtrlr_t *v6;
  dds3ModelEffectCtrlr_t *p_next;
  dds3ModelEffectCtrlr_t *next;

  p_effects = &aHandle->effects;
  effects = aHandle->effects;
  if (effects)
  {
    v6 = 0;
    do
    {
      while (1)
      {
        next = effects->next;
        if (effects->playGroup == aPlayGroup)
          break;
        v6 = effects;
        effects = effects->next;
        if (!next)
          return;
      }
      mdlFree(effects);
      if (v6)
        p_next = &v6->next;
      else
        p_next = p_effects;
      p_next = next;
      effects = next;
    }
    while (next);
  }
}

// 0x1d65460
static void P2A_D3P_GetPos(sdfModelRootNode_t *model, dds3ModelEffectCtrlr_t *effect, sdfVector4_t *vect) {
  void *work;
  void *monitor;
  sdfModelNode_t *v10;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  struct sdfVector4_t CameraEyePos_local;
  f32 v23;
  sdfMatrix4_t v29;
  sdfMatrix4_t v30;
  sdfMatrix4_t v31;
  sdfVector4_t v32;
  sdfMatrix4_t v33;

  work = effect->work;
  monitor = work[1].monitor;
  v10 = sdfModelSearchNode(model, *((u32 *)monitor + 4));
  get_tm(&v29, v10, 0);
  v33 = v29;
  mtx_A = v33;
  v12 = *((f32 *)monitor + 8);
  v13 = *((f32 *)monitor + 9);
  v14 = *((f32 *)monitor + 7);
  v15 = -v13;
  vct_A.x = v14;
  vct_A.y = v15;
  vct_A.z = v12;
  vct_A.w = 0.0;
  vct_A.w = 1.0;
  get_transpose(&v31, &mtx_A, 0);
  v30 = v31;
  v32 = op_Multiply_60923920(&v30, vct_A, 0);
  vct_A = v32;
  vct_B = vct_A;
  CameraEyePos_local = CameraEyePos;
  vct_C = CameraEyePos_local;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_C);
  sub_1949110(0);
  v23 = *(f32 *)&work[2].klass;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v23);
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  *vect = vct_A;
}

// 0x1d65920
void mdlLink(dds3ModelHandle_t *aHandle, dds3ModelEffectCtrlr_t *aEffect) {
  sdfModelRootNode_t *modelRoot;
  f32 speed;
  s32 v8;
  u32 type;
  effHandle_t *handle;
  s64 v12;
  f32 w;
  f32 z;
  sdfVector4_t v15;
  sdfVector4_t v16;

  modelRoot = aHandle->modelRoot;
  speed = aHandle->motionCtrlr->speed;
  *(u64 *)&v15.x = 0;
  *(u64 *)&v15.z = 0;
  if (speed == 0.0 && !aHandle->IsMdlEffect_NonStop)
  {
    effStartEffectStop();
    v8 = 1;
    type = aEffect->type;
    if (type != 3)
    {
LABEL_6:
      if (type == 1)
      {
        handle = aEffect->handle;
        P2A_D3P_GetPos(modelRoot, aEffect, &v15);
        v12 = *(u64 *)&v15.x;
        z = v15.z;
        w = v15.w;
        *(u64 *)&v16.x = v12;
        v16.z = z;
        v16.w = w;
        dds3EffectSetPosition(handle, v16);
        dds3EffectDraw(handle);
      }
      if (v8)
        goto LABEL_14;
      return;
    }
  }
  else
  {
    v8 = 0;
    type = aEffect->type;
    if (type != 3)
      goto LABEL_6;
  }
  Draw_IPU(aEffect);
  if (v8)
LABEL_14:
    effStopEffectStop();
}

// 0x1d65ab0
void mdlEffectSetColorSub(dds3ModelHandle_t *aHandle, dds3ModelEffectCtrlr_t *aEffect, const sdfVector4_t *aColor) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u32 type;
  void *v10;
  void *handle;
  sdfVector4_t v13;
  sdfVector4_t v14;

  w = aColor->w;
  z = aColor->z;
  y = aColor->y;
  x = aColor->x;
  type = aEffect->type;
  if (type == 1)
  {
    handle = aEffect->handle;
    if (!handle)
      goto LABEL_15;
    goto LABEL_9000;
    if (!handle)
    {
LABEL_15:
      v14.z = z;
      v14.w = w;
      v14.x = x;
      v14.y = y;
      SetRGBA(handle, v14);
      return;
    }
LABEL_9000:
    goto LABEL_15;
  }
  if (!type)
  {
    v10 = aEffect->handle;
    v13.z = z;
    v13.w = w;
    v13.x = x;
    v13.y = y;
    SetRGBA(v10, v13);
  }
}

// 0x1d65c10
void mdlEffectSetScaleSub(dds3ModelHandle_t *aHandle, dds3ModelEffectCtrlr_t *aEffect, f32 scale) {
  effHandle_t *handle;

  handle = aEffect->handle;
  if (!handle)
  dds3EffectSetScale(handle, scale);
}
