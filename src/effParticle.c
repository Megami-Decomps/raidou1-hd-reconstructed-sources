#include "types.h"
#include "EFFBEHAVIOR_TYPE.h"
#include "dds3billboard.h"
#include "eff.h"
#include "effbehavior.h"
#include "effcachetexlist.h"
#include "effoption.h"
#include "effparticle.h"
#include "effparts.h"
#include "effpartslist.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct ctexlHandle_t_Resource ctexlHandle_t_Resource;
typedef struct effBehavior_Params_Basic_t effBehavior_Params_Basic_t;
typedef struct effCacheTexList_Anim_t effCacheTexList_Anim_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct plistHandle_t_Resource plistHandle_t_Resource;
typedef struct ptcHandle_t ptcHandle_t;

static effCacheTexList_Anim_t *temp_effCacheTexList_Anim_t;

static ptcHandle_t *Create(u32 number);
static ptcHandle_t *ParamsCreate(effBehavior_Params_Basic_t *pParams);
static void BehaviorSet(ptcHandle_t *hParticle, EFFBEHAVIOR_TYPE type, effBehavior_Params_Basic_t *pParams);
static void BillboardGeneralSet(ptcHandle_t *hParticle, u32 index);
static void BillboardSet(ptcHandle_t *hParticle, DDS3BILLBOARD type, void *resrc);
static void PartsSet(ptcHandle_t *hParticle, Standard *pEP);
static void PartsListSet(ptcHandle_t *hParticle, plistHandle_t_Resource *pEPL);
static void Calc(ptcHandle_t *hParticle);
static void Draw(ptcHandle_t *hParticle);
static void CacheTexSet(ptcHandle_t *hParticle, ctexlHandle_t_Resource *pTLP);

// 0x197e130
static ptcHandle_t *Create(u32 number) {
  ptcHandle_t *v3;

  v3 = Allocate(ptcHandle_t);
  v3->number = number;
  *(u32 *)&v3->scale = 1065353216;
  v3->hBehavior = 0;
  v3->abgr = oneVector;
  v3->hBillboard = 0;
  v3->phParts = 0;
  v3->phPartsList = 0;
  v3->state = 1;
  return v3;
}

// 0x197e230
static ptcHandle_t *ParamsCreate(effBehavior_Params_Basic_t *pParams) {
  effBehavior_EmitterParams_t *emitter;
  u32 life;
  u32 count;
  u32 v7;

  emitter = pParams->emitter;
  life = emitter->life;
  if (!life)
  {
    life = pParams->life;
    count = emitter->count;
    goto LABEL_4;
  }
  count = emitter->count;
LABEL_4:
  if (count * life >= 0x12C)
    v7 = 300;
  else
    v7 = count * life;
  return Create(v7);
}

// 0x197e2d0
ptcHandle_t *PartsCreate(Standard *pParts) {
  u16 type;
  Standard *klass;
  s64 naturalAligment;
  u8 *v8;
  sdfBinary *v9;
  effBehavior_Params_Basic_t *Params;
  effBehavior_EmitterParams_t *emitter;
  u32 life;
  u32 count;
  u32 v16;
  ptcHandle_t *v17;
  effOption_Resource *option;
  effOption *v19;
  bhvrHandle_t *hBehavior;
  bhvrHandle_t *v21;
  s64 v24;
  effPartsData_t *data;
  void *v26;
  ptcHandle_t *v27;
  u16 v28;
  void *pData;
  s64 v31;
  u32 v32;
  s64 v34;
  s64 v36;
  s64 v37;
  ctexlHandle_t *hCTexList;
  ctexlHandle_t *v39;

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
  Params = effCreateParams(type, v9);
  emitter = Params->emitter;
  life = emitter->life;
  if (!life)
  {
    life = Params->life;
    count = emitter->count;
    goto LABEL_15;
  }
  count = emitter->count;
LABEL_15:
  if (count * life >= 0x12C)
    v16 = 300;
  else
    v16 = count * life;
  v17 = Create(v16);
  option = pParts->option;
  v19 = effGet(option);
  v17->option = v19;
  hBehavior = v17->hBehavior;
  if (hBehavior)
    Delete(hBehavior);
  v21 = effCreate(type, v17->number, Params);
  v17->hBehavior = v21;
  if (pParts->klass->_2.naturalAligment >= (u32)v24 && (Standard *)pParts->klass->_2.typeHierarchy[v24 - 1] == Standard)
  {
    data = pParts->data;
    v26 = data->pData;
    if (v26)
    {
      switch (data->type)
      {
        case 1u:
          v27 = v17;
          v28 = 0;
          goto LABEL_42;
        case 2u:
          v26 = *(void *)((v26->klass->vtable._5_GetExtUnits.methodPtr)(v26, v26->klass->vtable._5_GetExtUnits.method) + 32);
          v27 = v17;
          v28 = 1;
LABEL_42:
          BillboardSet(v27, v28, v26);
          break;
        case 4u:
          if (v26->klass->_2.naturalAligment < (u32)v31 || v26->klass->_2.typeHierarchy[v31 - 1] != Project_effPartsData_t_General)
          {
            goto LABEL_71;
          }
          v32 = v26[1].klass;
          BillboardGeneralSet(v17, v32);
          break;
        case 5u:
          v26 = *(void *)((v26->klass->vtable._5_GetExtUnits.methodPtr)(v26, v26->klass->vtable._5_GetExtUnits.method) + 32);
          if (v26)
          {
            if (v26->klass->_2.naturalAligment < (u32)v34 || v26->klass->_2.typeHierarchy[v34 - 1] != Standard)
            {
              goto LABEL_71;
            }
          }
          PartsSet(v17, v26);
          break;
        case 6u:
          v26 = *(void *)((v26->klass->vtable._5_GetExtUnits.methodPtr)(v26, v26->klass->vtable._5_GetExtUnits.method) + 32);
          if (v26)
          {
            if (v26->klass->_2.naturalAligment < (u32)v36 || v26->klass->_2.typeHierarchy[v36 - 1] != plistHandle_t_Resource)
            {
              goto LABEL_71;
            }
          }
          PartsListSet(v17, v26);
          break;
        case 7u:
          v26 = *(void *)((v26->klass->vtable._5_GetExtUnits.methodPtr)(v26, v26->klass->vtable._5_GetExtUnits.method) + 32);
          if (v26)
          {
            if (v26->klass->_2.naturalAligment < (u32)v37 || v26->klass->_2.typeHierarchy[v37 - 1] != ctexlHandle_t_Resource)
            {
LABEL_71:
            }
          }
          hCTexList = v17->hCTexList;
          if (hCTexList)
            effCacheTexDelete(hCTexList);
          v39 = effCacheTexCreate(v26);
          v17->hCTexList = v39;
          break;
        default:
          break;
      }
      v17->matType = pParts->data->type;
    }
  }
  return v17;
}

// 0x197f030
void Delete(effPartsHandle_t *handle) {
  void *monitor;
  effOption *option;
  s64 v6;
  effParts_t *v7;
  effPartsHandle_t *klass;
  s64 v9;
  ctexlHandle_t *v10;
  effOption *v11;
  void *p_fields;
  void *gameObject;
  effPartsHandle_t *v14;

  monitor = handle[2].monitor;
  if (monitor)
  {
    dds3BillboardDelete(monitor);
  }
  option = handle[2].option;
  if (option)
  {
    if (SLODWORD(option->adjustRGBA.x) >= 1)
    {
      v6 = 0;
      do
      {
        v7 = *((effParts_t *)&option->adjustRGBA.z + v6);
        Delete(v7);
        ++v6;
      }
      while (v6 < SLODWORD(option->adjustRGBA.x));
    }
    handle[2].option = 0;
  }
  klass = handle[3].klass;
  if (klass)
  {
    if (SLODWORD(klass->_1.namespaze) >= 1)
    {
      v9 = 0;
      do
        effPartsDelete(*((void *)&klass->_1.byval_arg.data + v9++));
      while (v9 < SLODWORD(klass->_1.namespaze));
    }
    handle[3].klass = 0;
  }
  v10 = handle[3].monitor;
  if (v10)
    effCacheTexDelete(v10);
  p_fields = &handle[3].fields;
  v11 = handle[3].option;
  if (v11)
  {
    gameObject = get_gameObject(v11[1].klass, 0);
    DestroyImmediate_61008224(gameObject, 0);
    Destroy(p_fields);
    p_fields = 0;
  }
  v14 = handle[4].klass;
  if (v14)
    Delete(v14);
}

// 0x197f340
ptcHandle_t *Copy(effPartsHandle_t *handle) {
  effBehavior_Params_Basic_t *element_class;
  effBehavior_EmitterParams_t *emitter;
  u32 life;
  u32 count;
  u32 v9;
  ptcHandle_t *v10;
  bhvrHandle_t *hBehavior;
  u16 name;
  bhvrHandle_t *v13;

  element_class = handle[4].klass->_1.element_class;
  emitter = element_class->emitter;
  life = emitter->life;
  if (!life)
  {
    life = element_class->life;
    count = emitter->count;
    goto LABEL_10;
  }
  count = emitter->count;
LABEL_10:
  if (count * life >= 0x12C)
    v9 = 300;
  else
    v9 = count * life;
  v10 = Create(v9);
  hBehavior = v10->hBehavior;
  name = handle[4].klass->_1.name;
  if (hBehavior)
    Delete(hBehavior);
  v13 = effCreate(name, v10->number, element_class);
  v10->hBehavior = v13;
  ResourceCopy(v10, handle);
  return v10;
}

// 0x197f4d0
void ResourceCopy(effPartsHandle_t *dstHandle, effPartsHandle_t *srcHandle) {
  void *monitor;
  void *v9;
  dds3Billboard_Basic_t *v10;
  effPartsHandle_t *klass;
  dds3Billboard_Basic_t *v12;
  s32 v13;
  s64 namespaze_low;
  effPartsHandle_t *p_fields;
  effOption *option;
  s64 v17;
  effParts_t *v18;
  s64 v19;
  effPartsHandle_t *v20;
  effPartsHandle_t *v21;
  s64 v22;
  effPartsHandle_t *v23;
  s64 v24;
  s32 v25;
  void **v26;
  effPartsHandle_t *v27;
  plistHandle_t *v28;
  plistHandle_t *v29;
  ctexlHandle_t *v30;
  effOption *v31;
  void *v32;
  void *gameObject;
  ctexlHandle_t *v34;
  effOption *v35;
  s64 v37;
  s32 v38;
  s64 v39;
  effOption *v40;
  effParts_t *v41;
  effParts_t *v42;

  switch (LOWORD(srcHandle[2].klass))
  {
    case 1:
    case 2:
    case 4:
    case 9:
    case 0xA:
      monitor = dstHandle[2].monitor;
      if (monitor)
      {
        dds3BillboardDelete(monitor);
      }
      v9 = srcHandle[2].monitor;
      v10 = dds3BillboardCopy(v9);
      dstHandle[2].monitor = v10;
      klass = dstHandle[4].klass;
      if (klass)
      {
        v12 = dstHandle[2].monitor;
        v13 = *(u32 *)(*(u64 *)(*(u64 *)&klass->_1.this_arg.bits + 32) + 20);
        dds3BillboardSetBlend(v12, v13);
      }
      goto LABEL_45;
    case 5:
    case 0xB:
      namespaze_low = LODWORD(srcHandle[4].klass->_1.namespaze);
      if (!(u32)namespaze_low)
        return;
      p_fields = &dstHandle[2].fields;
      option = dstHandle[2].option;
      if (option)
      {
        if (SLODWORD(option->adjustRGBA.x) >= 1)
        {
          v17 = 0;
          do
          {
            v18 = *((effParts_t *)&option->adjustRGBA.z + v17);
            Delete(v18);
            ++v17;
          }
          while (v17 < SLODWORD(option->adjustRGBA.x));
        }
        p_fields->option = 0;
      }
      v35 = NewSpecific(effParts_t, namespaze_low);
      p_fields->option = v35;
      v37 = 0;
      v38 = 1;
      break;
    case 6:
      v19 = LODWORD(srcHandle[4].klass->_1.namespaze);
      if (!(u32)v19)
        return;
      v20 = dstHandle + 3;
      v21 = dstHandle[3].klass;
      if (v21)
      {
        if (SLODWORD(v21->_1.namespaze) >= 1)
        {
          v22 = 0;
          do
            effPartsDelete(*((void *)&v21->_1.byval_arg.data + v22++));
          while (v22 < SLODWORD(v21->_1.namespaze));
        }
        v20->klass = 0;
      }
      v23 = NewSpecific(plistHandle_t, v19);
      v20->klass = v23;
      v24 = 0;
      v25 = 1;
      do
      {
        v27 = v20->klass;
        v28 = Copy(srcHandle[3].klass->_1.byval_arg.data);
        v29 = v28;
        if (v28)
          QueryInterface(v28, *((void **)v27->_1.image + 8));
        v26 = &v27->_1.image + v24;
        v26[4] = v29;
        v24 = v25++;
      }
      while (v24 < v19);
LABEL_45:
      LOWORD(dstHandle[2].klass) = srcHandle[2].klass;
      return;
    case 7:
      v30 = dstHandle[3].monitor;
      if (v30)
        effCacheTexDelete(v30);
      v32 = &dstHandle[3].fields;
      v31 = dstHandle[3].option;
      if (v31)
      {
        gameObject = get_gameObject(v31[1].klass, 0);
        DestroyImmediate_61008224(gameObject, 0);
        Destroy(v32);
        v32 = 0;
      }
      v34 = Copy(srcHandle[3].monitor);
      dstHandle[3].monitor = v34;
      goto LABEL_45;
    default:
      goto LABEL_45;
  }
  while (1)
  {
    v40 = p_fields->option;
    v41 = *(effParts_t *)&srcHandle[2].option->adjustRGBA.z;
    v42 = Copy(*(effParts_t *)&srcHandle[2].option->adjustRGBA.z);
    if (!v42)
    v39 = (s64)v40 + 8 * v37;
    *(u64 *)(v39 + 32) = v42;
    v37 = v38++;
    if (v37 >= namespaze_low)
      goto LABEL_45;
  }
}

// 0x197e960
static void BehaviorSet(ptcHandle_t *hParticle, EFFBEHAVIOR_TYPE type, effBehavior_Params_Basic_t *pParams) {
  bhvrHandle_t *hBehavior;
  bhvrHandle_t *p_hBehavior;
  bhvrHandle_t *v9;

  p_hBehavior = &hParticle->hBehavior;
  hBehavior = hParticle->hBehavior;
  if (hBehavior)
    Delete(hBehavior);
  v9 = effCreate(type, hParticle->number, pParams);
  hParticle->hBehavior = v9;
}

// 0x197eb60
static void BillboardGeneralSet(ptcHandle_t *hParticle, u32 index) {
  void *hBillboard;
  dds3Billboard_Basic_t *v6;
  dds3Billboard_Basic_t *v7;
  effOption *option;
  bhvrHandle_t *hBehavior;
  dds3Billboard_Basic_t *v10;
  s32 blend;

  hBillboard = hParticle->hBillboard;
  if (hBillboard)
  {
    dds3BillboardDelete(hBillboard);
  }
  v6 = dds3BillboardGeneralCreate(index);
  hParticle->hBillboard = v6;
  v7 = hParticle->hBillboard;
  option = hParticle->option;
  v7->option = option;
  hBehavior = hParticle->hBehavior;
  if (hBehavior)
  {
    v10 = hParticle->hBillboard;
    blend = hBehavior->pParams->alpha->blend;
    dds3BillboardSetBlend(v10, blend);
  }
}

// 0x197ea50
static void BillboardSet(ptcHandle_t *hParticle, DDS3BILLBOARD type, void *resrc) {
  void *hBillboard;
  dds3Billboard_Basic_t *v8;
  dds3Billboard_Basic_t *v9;
  effOption *option;
  bhvrHandle_t *hBehavior;
  dds3Billboard_Basic_t *v12;
  s32 blend;

  hBillboard = hParticle->hBillboard;
  if (hBillboard)
  {
    dds3BillboardDelete(hBillboard);
  }
  v8 = dds3BillboardCreate(type, resrc);
  hParticle->hBillboard = v8;
  v9 = hParticle->hBillboard;
  option = hParticle->option;
  v9->option = option;
  hBehavior = hParticle->hBehavior;
  if (hBehavior)
  {
    v12 = hParticle->hBillboard;
    blend = hBehavior->pParams->alpha->blend;
    dds3BillboardSetBlend(v12, blend);
  }
}

// 0x197ec70
static void PartsSet(ptcHandle_t *hParticle, Standard *pEP) {
  effParts_t **p_phParts;
  effParts_t *v6;
  effParts_t *phParts;
  s64 max_length_low;
  s64 v9;
  effParts_t *v10;
  effParts_t *v11;
  effParts_t *v13;
  effParts_t *v14;
  s32 v17;
  s64 i;
  Il2CppClass **v19;
  effParts_t *v20;
  effParts_t *v21;
  effParts_t *v22;

  phParts = hParticle->phParts;
  p_phParts = &hParticle->phParts;
  v6 = phParts;
  max_length_low = LODWORD(p_phParts[4]->max_length);
  if (phParts)
  {
    if (SLODWORD(v6->max_length) >= 1)
    {
      v9 = 0;
      do
      {
        v10 = v6[v9];
        Delete(v10);
        ++v9;
      }
      while (v9 < SLODWORD(v6->max_length));
    }
    *p_phParts = 0;
  }
  if (!(u32)max_length_low)
    return;
  v11 = NewSpecific(effParts_t, max_length_low);
  *p_phParts = v11;
  v13 = *p_phParts;
  v14 = Create(pEP);
  v13[0] = v14;
  if ((u32)max_length_low >= 2)
  {
    v17 = 2;
    for (i = 1; i < max_length_low; i = v17++)
    {
      v20 = *p_phParts;
      v21 = (*p_phParts)[0];
      v22 = Copy((*p_phParts)[0]);
      if (!v22)
      v19 = &v20->obj.klass + i;
      v19[4] = v22;
    }
  }
}

// 0x197ee70
static void PartsListSet(ptcHandle_t *hParticle, plistHandle_t_Resource *pEPL) {
  plistHandle_t **p_phPartsList;
  plistHandle_t *v6;
  plistHandle_t *phPartsList;
  s64 max_length_low;
  s64 v9;
  plistHandle_t *v10;
  plistHandle_t *v11;
  plistHandle_t *v12;
  plistHandle_t *v13;
  s32 v14;
  s64 v15;
  Il2CppClass **v16;
  plistHandle_t *v17;
  plistHandle_t *v18;
  plistHandle_t *v19;

  phPartsList = hParticle->phPartsList;
  p_phPartsList = &hParticle->phPartsList;
  v6 = phPartsList;
  max_length_low = LODWORD(p_phPartsList[3]->max_length);
  if (phPartsList)
  {
    if (SLODWORD(v6->max_length) >= 1)
    {
      v9 = 0;
      do
        effPartsDelete(v6[v9++]);
      while (v9 < SLODWORD(v6->max_length));
    }
    *p_phPartsList = 0;
  }
  if ((u32)max_length_low)
  {
    v10 = NewSpecific(plistHandle_t, max_length_low);
    *p_phPartsList = v10;
    v11 = *p_phPartsList;
    v12 = Create(pEPL, 0);
    v13 = v12;
    v11[0] = v13;
    if ((u32)max_length_low >= 2)
    {
      v14 = 2;
      v15 = 1;
      while (1)
      {
        v17 = *p_phPartsList;
        v18 = Copy((*p_phPartsList)[0]);
        v19 = v18;
        if (v18)
        {
            break;
        }
        v16 = &v17->obj.klass + v15;
        v16[4] = v19;
        v15 = v14++;
        if (v15 >= max_length_low)
          return;
      }
    }
  }
}

// 0x197fc60
static void Calc(ptcHandle_t *hParticle) {
  bhvrHandle_t *hBehavior;

  hBehavior = hParticle->hBehavior;
  if (hBehavior)
    effCalc(hBehavior);
}

// 0x197fc80
static void Draw(ptcHandle_t *hParticle) {
  void *v3;
  s64 v4;
  s64 v5;
  void **p_temp_effCacheTexList_Anim_t;
  void *v8;
  void *v9;
  void *v10;
  ptcHandle_t *v11;
  __int128 v13;
  __int128 v14;
  s32 v15;
  float32x4_t v16;
  s64 v17;
  s64 v18;
  sdfVector4_t *v20;
  ptcHandle_t *v22;
  void *v23;
  intptr_t *v24;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  _OWORD *p_x;
  __int128 v33;
  __int128 v34;
  s64 v35;
  void *v36;
  s64 v37;
  float32x4_t v38;
  s32 v39;
  __int128 v41;
  _OWORD *v42;
  __int128 v43;
  struct sdfVector4_t v44;
  s64 v47;
  ptcHandle_t *v48;
  void *v49;
  MeshJobD *v50;
  void *v51;
  s32 v52;
  MeshJobD *v53;
  s32 v54;
  sdfGrOt_t *v55;
  sdfVector4_t v56;
  float32x4_t v59;
  sdfVector4_t pPos;
  sdfVector4_t pRot;
  __int128 v62;
  __int128 v63;
  __int128 v64;
  __int128 v65;
  sdfMatrix4_t v66;
  sdfMatrix4_t v67;
  sdfVector4_t v68;
  sdfVector4_t v69;

  *(u64 *)&pRot.x = 0;
  *(u64 *)&pRot.z = 0;
  *(u64 *)&pPos.x = 0;
  *(u64 *)&pPos.z = 0;
  v3 = Allocate(Project_effParticle___c__DisplayClass14_0);
  v3->hParticle = hParticle;
  v4 = &v3->hParticle;
  v5 = *(u32 *)(*(u64 *)((u64)v3->hParticle + 96) + 24);
  if ((u32)v5)
  {
    *(_OWORD *)&v3->directBill.scale = 0u;
    *(_OWORD *)&v3->directBill.abgr.y = 0u;
    *(_OWORD *)&v3->directBill.hTex = 0u;
    *(_OWORD *)&v3->directBill.mesh = 0u;
    *(_OWORD *)&v3->directBill = 0u;
    p_temp_effCacheTexList_Anim_t = &temp_effCacheTexList_Anim_t;
    v8 = *p_temp_effCacheTexList_Anim_t;
    v3->CTexAnim = *p_temp_effCacheTexList_Anim_t;
    v3->pOt = 0;
    v9 = *(void **)((u64)v3->hParticle + 56);
    v3->hBillboard = v9;
    v10 = *(void **)((u64)v3->hParticle + 80);
    v3->hCTexList = v10;
    v11 = v3->hParticle;
    v13 = *(_OWORD *)&identityMatrix.m01;
    v62 = *(_OWORD *)&identityMatrix.m00;
    v63 = v13;
    v14 = *(_OWORD *)&identityMatrix.m03;
    v15 = *(u32 *)((u64)v11->hBehavior + 28);
    v64 = *(_OWORD *)&identityMatrix.m02;
    v65 = v14;
    v16 = *(float32x4_t *)&v11->abgr;
    v3->pPosture = 0;
    v17 = &v3->pPosture;
    v59 = v16;
    v18 = 0;
    v3->pos = zeroVector;
    v20 = &v3->pos;
    v3->scale = zeroVector;
    v22 = v3->hParticle;
    v3->i = 0;
    v3->abgr = zeroVector;
    switch (v22->matType)
    {
      case 1:
      case 2:
      case 4:
      case 9:
      case 0xA:
        v23 = Allocate(System_Action);
        v18 = v23;
        v24 = &Method_Project_effParticle___c__DisplayClass14_0__Draw_g__DrawTex_0__;
        goto LABEL_14;
      case 5:
      case 0xB:
        v23 = Allocate(System_Action);
        v18 = v23;
        v24 = &Method_Project_effParticle___c__DisplayClass14_0__Draw_g__DrawEP_1__;
        goto LABEL_14;
      case 6:
        v23 = Allocate(System_Action);
        v18 = v23;
        v24 = &Method_Project_effParticle___c__DisplayClass14_0__Draw_g__DrawEPL_2__;
LABEL_14:
        _ctor(v23, v3, *v24, 0);
        goto LABEL_15;
      case 7:
        v18 = Allocate(System_Action);
        _ctor(v18, v3, Method_Project_effParticle___c__DisplayClass14_0__Draw_g__DrawTLP_3__, 0);
        v48 = v3->hParticle;
        v51 = v48->pMesh;
        v50 = &v48->pMesh;
        v49 = v51;
        if (!v51)
        {
          v52 = *(u32 *)((u64)v3->hCTexList + 40);
          v53 = dds3BillboardDirectInit(v5, v52);
          v50 = v53;
          SetOption(*(void *)(*(u64 *)(*(u64 *)v4 + 88) + 40), *(effOption *)(*(u64 *)v4 + 16), 0);
          v49 = *(void **)(*(u64 *)v4 + 88);
        }
        v3->directBill.mesh = v49;
        v3->directBill.count = v5;
        v3->directBill.frame = -1;
        v54 = *(u32 *)(*(u64 *)(*(u64 *)(*(u64 *)((u64)v3->hParticle + 96) + 56) + 32) + 20);
        v55 = effOtGet(v54);
        v3->pOt = v55;
        if ((v15 & 1) == 0)
          goto LABEL_24;
        goto LABEL_16;
      default:
LABEL_15:
        if ((v15 & 1) == 0)
          goto LABEL_24;
LABEL_16:
        effEmitterRotateGet(*(bhvrHandle_t *)(*(u64 *)v4 + 96), &pRot);
        effEmitterPositionGet(*(bhvrHandle_t *)(*(u64 *)v4 + 96), &pPos);
        v56 = pRot;
        vct_A = v56;
        ToMatrix();
        x = pPos.x;
        y = pPos.y;
        z = pPos.z;
        w = pPos.w;
        v69.x = x;
        v69.y = y;
        v69.z = z;
        v69.w = w;
        SetRow(&mtx_A, 3, v69, 0);
        p_x = &vf00.x;
        v33 = p_x[5];
        v62 = p_x[4];
        v63 = v33;
        v34 = p_x[7];
        v64 = p_x[6];
        v65 = v34;
LABEL_24:
        v35 = v3->i;
        if (v35 < v5)
        {
          while (1)
          {
            v36 = *(void **)(*(u64 *)(*(u64 *)(*(u64 *)v4 + 96) + 40) + 8 * v35 + 32);
            *(u64 *)v17 = v36;
            v37 = *(u64 *)v17;
            if ((*(u32 *)(*(u64 *)v17 + 32) & 0x80000000) != 0)
              goto LABEL_28;
            v38 = vmulq_f32(v59, *(float32x4_t *)(v37 + 36));
            *(float32x4_t *)&v3->abgr = v38;
            if (v38.n128_f32[3] <= 0.0)
              goto LABEL_28;
            *v20 = *(sdfVector4_t *)(v37 + 16);
            v39 = *(u32 *)(v37 + 52);
            *(u64 *)&v3->scale.z = 1065353216;
            *(u32 *)&v3->scale = v39;
            *(u32 *)&v3->scale.y = v39;
            if ((v15 & 1) != 0)
              break;
LABEL_27:
            (*(v18 + 24))(*(u64 *)(v18 + 64), *(u64 *)(v18 + 40));
LABEL_28:
            LODWORD(v35) = v3->i + 1;
            v3->i = v35;
            v35 = (s32)v35;
            if ((s32)v35 >= v5)
              goto LABEL_51;
          }
          v41 = v63;
          v42 = &vf00.x;
          v42[4] = v62;
          v42[5] = v41;
          v43 = v65;
          v42[6] = v64;
          v42[7] = v43;
          v44 = *(sdfVector4_t *)(*(u64 *)v17 + 16);
          vct_A = v44;
          vct_A.w = 1.0;
          get_transpose(&v67, &mtx_A, 0);
          v66 = v67;
          v68 = op_Multiply_60923920(&v66, vct_A, 0);
          vct_A = v68;
          *v20 = vct_A;
          goto LABEL_27;
        }
LABEL_51:
        v47 = *(u64 *)(*(u64 *)v4 + 88);
        if (v47)
          (*(*(u64 *)v47 + 392))(v47, *(u64 *)(*(u64 *)v47 + 400));
        break;
    }
  }
}

// 0x197efe0
static void CacheTexSet(ptcHandle_t *hParticle, ctexlHandle_t_Resource *pTLP) {
  ctexlHandle_t *hCTexList;
  ctexlHandle_t *p_hCTexList;
  ctexlHandle_t *v6;

  p_hCTexList = &hParticle->hCTexList;
  hCTexList = hParticle->hCTexList;
  if (hCTexList)
    effCacheTexDelete(hCTexList);
  v6 = effCacheTexCreate(pTLP);
  p_hCTexList = v6;
}

// 0x1980540
void CalcAndDraw(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;

  if (!get_STOP(0))
  {
    klass = handle[4].klass;
    if (klass)
      effCalc(klass);
  }
  if (drawSkip)
    return;
  Draw();
}

// 0x19806d0
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
  effEmitterPositionSet(handle[4].klass, v9);
}

// 0x1980790
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
  effEmitterRotateSet(handle[4].klass, v9);
}

// 0x1980850
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

// 0x1980900
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *((f32 *)&handle[1].option + 1) = scale;
  ScaleSet(handle[4].klass, scale);
}
