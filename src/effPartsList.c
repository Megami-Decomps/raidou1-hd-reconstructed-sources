#include "types.h"
#include "eff.h"
#include "effparts.h"
#include "effpartslist.h"
#include "effpartslist_ground.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct effPartsListItemParams_t effPartsListItemParams_t;
typedef struct effPartsListItem_t effPartsListItem_t;
typedef struct effPartsListPose_t effPartsListPose_t;
typedef struct plistHandle_t plistHandle_t;
typedef struct plistHandle_t_Resource plistHandle_t_Resource;

static void ParamsInit(effPartsListItemParams_t *pParams);
static void ItemLink(plistHandle_t *hPartsList, effPartsListItem_t *pItem);
static effPartsListItem_t *ItemNew(void);
static void ItemDelete(effPartsListItem_t *pItem);
static void PosePosBillboard(effPartsListPose_t *pPose, sdfVector4_t *pPos);
static void PoseRotBillboard(effPartsListPose_t *pPose, sdfVector4_t *pRot);

// 0x19a1510
void effPartsPoseInit(effPartsListPose_t *pPose) {
  effPartsListPose_t *p_fields;
  sdfVector4_t *p_origin;
  sdfVector4_t *p_pos;
  s32 v9;
  _BOOL4 v10;
  s32 v12;

  p_fields = &pPose->fields;
  p_fields->posBase = vf00;
  p_origin = &pPose->origin;
  v9 = (u8)byte_5756282;
  *p_origin = vf00;
  if (v9)
  {
    p_pos = &pPose->pos;
    goto LABEL_17;
  }
  else
  {
    p_pos = &pPose->pos;
    goto LABEL_17;
  }
  goto LABEL_19;
LABEL_17:
  v10 = 0;
  goto LABEL_20;
LABEL_19:
  v10 = byte_5756282 == 0;
LABEL_20:
  *p_pos = vf00;
  pPose->pos.y = -5.0;
  pPose->pos.x = -pPose->pos.x;
  v12 = (u8)byte_5756171;
  pPose->scl = 1.0;
  pPose->sclBase = 1.0;
  pPose->rot = vf00;
  pPose->flag = 128;
  pPose->abgr = oneVector;
}

// 0x19a1750
static void ParamsInit(effPartsListItemParams_t *pParams) {
  pParams->dirPtrR = 0;
  *(u16 *)&pParams->dirPtrH = 8;
  *(u64 *)&pParams->start = 0x100000000LL;
  effPartsPoseInit(pParams->pose);
}

// 0x19a1770
static void ItemLink(plistHandle_t *hPartsList, effPartsListItem_t *pItem) {
  effPartsListItem_t *pLink;
  effPartsListItem_t *p_pLink;
  effPartsListItem_t *v7;

  pItem->prev = 0;
  p_pLink = &hPartsList->pLink;
  pLink = hPartsList->pLink;
  if (pLink)
  {
    pLink->prev = pItem;
    v7 = p_pLink;
    pItem->next = p_pLink;
  }
  else
  {
    hPartsList->pLinkTail = pItem;
    v7 = 0;
    pItem->next = 0;
  }
  hPartsList->pLink = pItem;
  ++hPartsList->number;
}

// 0x19a1810
plistHandle_t *effPartsNew(effPartsListPose_t *pose) {
  plistHandle_t *v3;
  f32 sclBase;
  effPartsListPose_t *v7;

  v3 = (plistHandle_t *)Allocate(plistHandle_t);
  _ctor(v3, 0);
  effPartsPoseInit(v3->pose);
  v3->pose->posBase = pose->posBase;
  v3->pose->origin = pose->posBase;
  sclBase = pose->sclBase;
  v7 = v3->pose;
  v7->flag = pose->flag;
  v7->sclBase = sclBase;
  return v3;
}

// 0x19a18b0
static effPartsListItem_t *ItemNew(void) {
  effPartsListItem_t *v1;
  effPartsListItemParams_t *param;
  effPartsListPose_t *pose;

  v1 = (effPartsListItem_t *)Allocate(effPartsListItem_t);
  _ctor(v1, 0);
  param = v1->param;
  param->dirPtrR = 0;
  pose = param->pose;
  *(u16 *)&param->dirPtrH = 8;
  *(u64 *)&param->start = 0x100000000LL;
  effPartsPoseInit(pose);
  return v1;
}

// 0x19a1930
static void ItemDelete(effPartsListItem_t *pItem) {
  ;
}

// 0x19a1940
plistHandle_t *Create(plistHandle_t_Resource *pPartsListData) {
  effPartsListPose_t *pose;
  plistHandle_t *v4;
  f32 sclBase;
  effPartsListPose_t *v8;
  effPartsListItem_t_Resource *items;
  s64 v10;
  effPartsListItemParams_t *v11;
  char *name;
  effPartsListItem_t_Resource *v14;
  effPartsListItem_t *v15;
  effPartsListItemParams_t *param;
  effPartsListPose_t *v17;
  Standard *parts;
  Standard *klass;
  u32 naturalAligment;
  s64 v22;
  s64 v23;
  Il2CppClass **typeHierarchy;
  void *v25;
  void *v26;
  void *v27;
  effPartsData_t *v28;
  u32 v29;
  u16 v30;
  effOption_Resource *monitor;
  effPartsData_t *v32;
  effParts_t *v33;
  effPartsListItemParams_t *v34;
  u32 version;
  effPartsListItem_t *pLinkTail;
  u32 v37;
  bool v38;
  effParts_t *hParts;

  pose = pPartsListData->pose;
  v4 = (plistHandle_t *)Allocate(plistHandle_t);
  _ctor(v4, 0);
  effPartsPoseInit(v4->pose);
  v4->pose->posBase = pose->posBase;
  v4->pose->origin = pose->posBase;
  sclBase = pose->sclBase;
  v8 = v4->pose;
  items = pPartsListData->items;
  v8->flag = pose->flag;
  v8->sclBase = sclBase;
  if (SLODWORD(items->max_length) >= 1)
  {
    v10 = 0;
    while (1)
    {
      v14 = items[v10];
      v15 = Allocate(effPartsListItem_t);
      _ctor(v15, 0);
      param = v15->param;
      v17 = param->pose;
      *(u64 *)&param->start = 0x100000000LL;
      *(u16 *)&param->dirPtrH = 8;
      param->dirPtrR = 0;
      effPartsPoseInit(v17);
      parts = v14->parts;
      klass = parts->klass;
      naturalAligment = parts->klass->_2.naturalAligment;
      if (naturalAligment >= (u32)v22 && (Project_effParts_t_Resource_Copy_c *)klass->_2.typeHierarchy[v22 - 1] == Project_effParts_t_Resource_Copy)
      {
        version = parts->version;
        pLinkTail = v4->pLinkTail;
        if (version && pLinkTail)
        {
          v37 = version - 1;
          do
          {
            pLinkTail = pLinkTail->prev;
            if (pLinkTail)
              v38 = v37 == 0;
            else
              v38 = 1;
            --v37;
          }
          while (!v38);
        }
        hParts = pLinkTail->hParts;
        v33 = Copy(hParts);
        goto LABEL_28;
      }
      if (naturalAligment < (u32)v23)
        break;
      typeHierarchy = klass->_2.typeHierarchy;
      if (typeHierarchy[v23 - 1] != Standard)
        goto LABEL_15;
LABEL_25:
      v33 = Create(parts, 0);
LABEL_28:
      v15->hParts = v33;
      v34 = v14->param;
      v11 = Allocate(effPartsListItemParams_t);
      _ctor_26764336(v11, v34, 0);
      v15->param = v11;
      name = v14->name;
      v15->name = name;
      ItemLink(v4, v15);
      if (++v10 >= SLODWORD(items->max_length))
        goto LABEL_41;
    }
    typeHierarchy = klass->_2.typeHierarchy;
LABEL_15:
      v25 = v14->parts;
    else
      v25 = 0;
    v26 = items[*(u32 *)&v25[1].Project_libsdf_sdfResourceUnit_Fields]->parts;
    if (v26 && v26->klass->_2.naturalAligment >= (u32)v23)
    {
      if (v26->klass->_2.typeHierarchy[v23 - 1] == Standard)
        v27 = items[*(u32 *)&v25[1].Project_libsdf_sdfResourceUnit_Fields]->parts;
      else
        v27 = 0;
    }
    else
    {
      v27 = 0;
    }
    parts = Allocate(Standard);
    _ctor(parts, 0);
    v28 = v25[1].klass;
    v29 = *(u32 *)&v25->Project_libsdf_sdfResourceUnit_Fields;
    parts->param = v28;
    v30 = *((u16 *)&v25->fields + 2);
    parts->version = v29;
    parts->categ = v30;
    monitor = v25[1].monitor;
    parts->option = monitor;
    v32 = *(effPartsData_t *)&v27[1].Project_libsdf_sdfResourceUnit_Fields;
    parts->data = v32;
    goto LABEL_25;
  }
LABEL_41:
  effPartsCreateFinish(v4);
  return v4;
}

// 0x19a1dc0
void effPartsCreateFinish(plistHandle_t *hPartsList) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v13;
  sdfVector4_t v14;

  x = vf00.x;
  y = vf00.y;
  v13.y = y;
  z = vf00.z;
  w = vf00.w;
  v13.w = w;
  v13.x = vf00.x;
  v13.z = z;
  effPartsPositionSet(hPartsList, v13);
  v14.x = x;
  v14.y = y;
  v14.z = z;
  v14.w = w;
  effPartsRotateSet(hPartsList, v14);
  effPartsScaleSet(hPartsList, 1.0);
  ColorSet(hPartsList, oneVector);
}

// 0x19a2ff0
plistHandle_t *effPartsCreateD3P(u16 type, void *pPartsListData) {
  plistHandle_t_Resource *v3;

  v3 = pPartsListData;
  return Create(v3, pPartsListData);
}

// 0x19a3070
void effPartsDraw(void *handle) {
  Project_dds3EffectHandle_t_c *klass;
  u64 *monitor;
  s32 monitor_high;
  s64 v9;
  effPartsListPose_t *v10;
  u32 flag;
  struct sdfVector4_t v13;
  struct sdfVector4_t v15;
  effParts_t *v18;
  f32 *p_x;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  effParts_t *v29;
  effParts_t *v30;
  f32 v31;
  f32 v33;
  struct sdfVector4_t v34;
  sdfVector4_t v35;
  sdfVector4_t v40;
  sdfVector4_t pPos;
  __int128 v42;
  sdfVector4_t pRot;
  sdfVector4_t v44;
  sdfVector4_t v45;

  *(u64 *)&pRot.x = 0;
  *(u64 *)&pRot.z = 0;
  v42 = 0u;
  *(u64 *)&pPos.x = 0;
  *(u64 *)&pPos.z = 0;
  *(u64 *)&v40.x = 0;
  *(u64 *)&v40.z = 0;
  klass = handle[1].klass;
  if (((s64)klass->_1.typeMetadataHandle & 0x60) != 0)
  {
    v42 = *(_OWORD *)((char *)&klass->_1.element_class + 4);
    PoseRotBillboard(klass, &pRot);
    effPartsRotateSet(handle, pRot);
    *(_OWORD *)((char *)&handle[1].klass->_1.element_class + 4) = v42;
    klass = handle[1].klass;
  }
  monitor = handle[2].monitor;
  if (monitor)
  {
    monitor_high = HIDWORD(handle[1].monitor);
    v33 = *((f32 *)&klass->_1.declaringType + 1) * *((f32 *)&klass->_1.typeMetadataHandle + 1);
    while (1)
    {
      v9 = monitor[2];
      if (monitor_high >= *(u32 *)(v9 + 24) && (*(u8 *)(v9 + 28) & 2) == 0)
        break;
LABEL_11:
      monitor = monitor[7];
      if (!monitor)
        goto LABEL_76;
    }
    v10 = *(effPartsListPose_t *)(v9 + 16);
    flag = v10->flag;
    if ((flag & 0x18) == 0)
    {
LABEL_36:
      if ((flag & 0x60) != 0)
      {
        PoseRotBillboard(v10, &v40);
        x = v40.x;
        y = v40.y;
        z = v40.z;
        w = v40.w;
        v29 = monitor[3];
        v45.x = x;
        v45.y = y;
        v45.z = z;
        v45.w = w;
        RotateSet(v29, v45);
      }
      v30 = monitor[3];
      Draw(v30, 0);
      goto LABEL_11;
    }
    PosePosBillboard(v10, &pPos);
    v34 = *(sdfVector4_t *)((char *)&handle[1].klass->_1.element_class + 4);
    vct_A = v34;
    ToMatrix();
    v13 = *(sdfVector4_t *)((char *)&handle[1].klass->_1.this_arg + 4);
    vct_A = v13;
    v15 = *(sdfVector4_t *)&handle[1].klass->_1.name;
    vct_B = v15;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    if ((*(u8 *)(*(u64 *)(monitor[2] + 16) + 104) & 4) == 0)
    {
      v35 = pPos;
      goto LABEL_26;
    }
    v31 = Y;
    vct_A.y = v31;
    v35 = pPos;
LABEL_26:
    vct_B = v35;
    if ((*(u8 *)(*(u64 *)(monitor[2] + 16) + 104) & 0x80) == 0)
    {
      goto LABEL_30;
    }
    vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v33);
LABEL_30:
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v18 = monitor[3];
    p_x = &vf00.x;
    v21 = p_x[4];
    v22 = p_x[5];
    v23 = p_x[6];
    v24 = p_x[7];
    v44.x = v21;
    v44.y = v22;
    v44.z = v23;
    v44.w = v24;
    PositionSet(v18, v44);
    v10 = *(effPartsListPose_t *)(monitor[2] + 16);
    flag = v10->flag;
    goto LABEL_36;
  }
LABEL_76:
  if (!get_STOP(0))
    ++HIDWORD(handle[1].monitor);
}

// 0x19a42b0
void effPartsDelete(void *handle) {
  void *monitor;
  void *v5;
  effParts_t *v6;

  monitor = handle[2].monitor;
  if (monitor)
  {
    do
    {
      v5 = *((void **)monitor + 7);
      if ((*((u8 *)monitor + 40) & 1) == 0)
      {
        v6 = *((effParts_t *)monitor + 3);
        Delete(v6);
      }
      monitor = v5;
    }
    while (v5);
  }
}

// 0x19a4390
plistHandle_t *Copy(void *handle) {
  u64 *monitor;
  Project_dds3EffectHandle_t_c *klass;
  plistHandle_t *v7;
  effPartsListPose_t *pose;
  f32 v11;
  Project_dds3EffectHandle_t_c *v12;
  effPartsListItemParams_t *v13;
  effPartsListItem_t *v15;
  effPartsListItemParams_t *param;
  effPartsListPose_t *v17;
  effParts_t *v19;
  effParts_t *v20;
  effPartsListItemParams_t *v21;

  monitor = handle[2].monitor;
  klass = handle[1].klass;
  v7 = (plistHandle_t *)Allocate(plistHandle_t);
  _ctor(v7, 0);
  effPartsPoseInit(v7->pose);
  v7->pose->posBase = *(sdfVector4_t *)&klass->_1.name;
  v7->pose->origin = *(sdfVector4_t *)&klass->_1.name;
  pose = v7->pose;
  v11 = *((f32 *)&klass->_1.typeMetadataHandle + 1);
  pose->flag = (u32)klass->_1.typeMetadataHandle;
  v12 = handle[1].klass;
  pose->sclBase = v11;
  for (pose->origin = (struct sdfVector4_t)v12->_1.byval_arg; monitor; monitor = (u64 *)monitor[7])
  {
    v15 = Allocate(effPartsListItem_t);
    _ctor(v15, 0);
    param = v15->param;
    v17 = param->pose;
    *(u64 *)&param->start = 0x100000000LL;
    *(u16 *)&param->dirPtrH = 8;
    param->dirPtrR = 0;
    effPartsPoseInit(v17);
    v19 = monitor[3];
    v20 = Copy(v19);
    v15->hParts = v20;
    v21 = monitor[2];
    v13 = Allocate(effPartsListItemParams_t);
    _ctor_26764336(v13, v21, 0);
    v15->param = v13;
    ItemLink(v7, v15);
  }
  effPartsCreateFinish(v7);
  return v7;
}

// 0x19a1f10
void effPartsPositionSet(void *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  Project_dds3EffectHandle_t_c *klass;
  u64 *monitor;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 *p_x;
  s64 v25;
  s32 v28;
  f32 *v31;
  effParts_t *v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  struct sdfVector4_t v41;
  struct sdfVector4_t v42;
  sdfMatrix4_t v44;
  sdfMatrix4_t v45;
  sdfVector4_t v46;
  sdfVector4_t v47;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  klass = handle[1].klass;
  monitor = handle[2].monitor;
  *((f32 *)&klass->_1.this_arg.data + 1) = x;
  *(f32 *)&klass->_1.this_arg.bits = y;
  v11 = *((f32 *)&klass->_1.declaringType + 1);
  v12 = *((f32 *)&klass->_1.typeMetadataHandle + 1);
  *((f32 *)&klass->_1.this_arg.bits + 1) = z;
  *(f32 *)&klass->_1.element_class = w;
  v38 = v12;
  v39 = v11;
  v13 = *(f32 *)&klass->_1.name;
  v14 = *((f32 *)&klass->_1.name + 1);
  v15 = *(f32 *)&klass->_1.namespaze;
  v16 = *((f32 *)&klass->_1.namespaze + 1);
  v41 = *(sdfVector4_t *)((char *)&handle[1].klass->_1.element_class + 4);
  vct_A = v41;
  ToMatrix();
  if (!monitor)
    return;
  goto LABEL_18;
  if (monitor)
  {
LABEL_18:
    v19 = x + v13;
    v20 = y + v14;
    v21 = z + v15;
    v22 = w + v16;
    v40 = v39 * v38;
    do
    {
      p_x = &vf00.x;
      p_x[4] = v19;
      p_x[5] = v20;
      p_x[6] = v21;
      p_x[7] = v22;
      v25 = *(u64 *)(monitor[2] + 16);
      if ((*(u8 *)(v25 + 104) & 4) == 0)
      {
        v42 = *(sdfVector4_t *)(v25 + 52);
        goto LABEL_25;
      }
      v37 = Y;
      vct_A.y = v37;
      v42 = *(sdfVector4_t *)(*(u64 *)(monitor[2] + 16) + 52);
LABEL_25:
      vct_B = v42;
      if ((*(u8 *)(*(u64 *)(monitor[2] + 16) + 104) & 0x80) == 0)
      {
        goto LABEL_29;
      }
      vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v40);
LABEL_29:
      v28 = (u8)byte_5756433;
      if (v28)
      {
        goto LABEL_33;
      }
      else
      {
        goto LABEL_33;
      }
LABEL_33:
      vct_B.w = 0.0;
      get_transpose(&v45, &mtx_A, 0);
      *(_OWORD *)&v44.m00 = *(_OWORD *)&v45.m00;
      *(_OWORD *)&v44.m01 = *(_OWORD *)&v45.m01;
      *(_OWORD *)&v44.m02 = *(_OWORD *)&v45.m02;
      *(_OWORD *)&v44.m03 = *(_OWORD *)&v45.m03;
      v46 = op_Multiply_60923920(&v44, vct_B, 0);
      vct_B = v46;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v31 = &vf00.x;
      v32 = monitor[3];
      v33 = v31[4];
      v34 = v31[5];
      v35 = v31[6];
      v36 = v31[7];
      v47.x = v33;
      v47.y = v34;
      v47.z = v35;
      v47.w = v36;
      PositionSet(v32, v47);
      monitor = monitor[7];
    }
    while (monitor);
  }
}

// 0x19a2550
void effPartsRotateSet(plistHandle_t *hPartsList, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  effPartsListPose_t *pose;
  sdfVector4_t *p_rot;
  struct sdfVector4_t origin;
  effPartsListPose_t *v18;
  sdfVector4_t *p_posBase;
  effPartsListItem_t *pLinkTail;
  effParts_t *hParts;
  f32 *v24;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  struct sdfVector4_t rot;
  struct sdfVector4_t v34;
  sdfMatrix4_t v35;
  sdfMatrix4_t v36;
  sdfVector4_t v37;
  sdfVector4_t v39;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  pose = hPartsList->pose;
  p_rot = &pose->rot;
  *p_rot = vct_A;
  rot = hPartsList->pose->rot;
  ToMatrix();
  origin = hPartsList->pose->origin;
  vct_A = origin;
  vct_A.w = 0.0;
  get_transpose(&v36, &mtx_A, 0);
  v35 = v36;
  v37 = op_Multiply_60923920(&v35, vct_A, 0);
  vct_A = v37;
  v18 = hPartsList->pose;
  p_posBase = &v18->posBase;
  goto LABEL_13;
  while (1)
  {
LABEL_29:
    v34 = pLinkTail->param->pose->rot;
    vct_A = v34;
    vct_B = rot;
    Mult();
    hParts = pLinkTail->hParts;
    v24 = &vf00.x;
    v26 = v24[4];
    v27 = v24[5];
    v28 = v24[6];
    v29 = v24[7];
    v39.x = v26;
    v39.y = v27;
    v39.z = v28;
    v39.w = v29;
    RotateSet(hParts, v39);
    pLinkTail = pLinkTail->prev;
    if (!pLinkTail)
      goto LABEL_46;
  }
LABEL_13:
  *p_posBase = vct_A;
  pLinkTail = hPartsList->pLinkTail;
  if (pLinkTail)
    goto LABEL_29;
LABEL_46:
  effPartsPositionSet(hPartsList, hPartsList->pose->pos);
}

// 0x19a29c0
void effPartsScaleSet(void *handle, f32 scale) {
  Project_dds3EffectHandle_t_c *klass;
  u64 *monitor;
  s64 v8;
  effParts_t *v9;
  f32 v10;
  f32 v11;
  struct sdfVector4_t v13;
  s64 v14;
  effParts_t *v16;
  f32 *p_x;
  f32 x;
  f32 v20;
  f32 z;
  f32 w;
  struct sdfVector4_t v25;
  struct sdfVector4_t v26;
  f32 v29;
  sdfVector4_t v30;

  klass = handle[1].klass;
  *((f32 *)&klass->_1.declaringType + 1) = scale;
  monitor = handle[2].monitor;
  if (monitor)
  {
    v29 = *((f32 *)&klass->_1.typeMetadataHandle + 1) * scale;
    do
    {
      v8 = monitor[2];
      v9 = monitor[3];
      v10 = *(f32 *)(*(u64 *)(v8 + 16) + 84);
      if ((*(u8 *)(v8 + 28) & 1) != 0)
        v11 = v29;
      else
        v11 = 1.0;
      ScaleSet(v9, v10 * v11);
      if ((*(u8 *)(*(u64 *)(monitor[2] + 16) + 104) & 0x80) == 0)
        goto LABEL_9;
      v25 = *(sdfVector4_t *)((char *)&handle[1].klass->_1.this_arg + 4);
      vct_A = v25;
      v13 = *(sdfVector4_t *)&handle[1].klass->_1.name;
      vct_B = v13;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v14 = *(u64 *)(monitor[2] + 16);
      if ((*(u8 *)(v14 + 104) & 4) == 0)
      {
        v26 = *(sdfVector4_t *)(v14 + 52);
        goto LABEL_25;
      }
      vct_A.y = Y;
      v26 = *(sdfVector4_t *)(*(u64 *)(monitor[2] + 16) + 52);
LABEL_25:
      vct_B = v26;
      vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v29);
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v16 = monitor[3];
      p_x = &vf00.x;
      x = p_x[4];
      v20 = p_x[5];
      z = p_x[6];
      w = p_x[7];
      v30.x = x;
      v30.y = v20;
      v30.z = z;
      v30.w = w;
      PositionSet(v16, v30);
LABEL_9:
      monitor = monitor[7];
    }
    while (monitor);
  }
}

// 0x19a46c0
void effPartsColorSet(void *handle, u32 abgr) {
  sdfVector4_t v5;

  v5.x = (f32)(u8)abgr * 0.0078125;
  *(float32x2_t *)&v5.y = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(abgr), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL);
  v5.w = (f32)HIBYTE(abgr) * 0.0078125;
  ColorSet(handle, v5);
}

// 0x19a2ec0
void ColorSet(void *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *klass;
  u64 *i;
  effParts_t *v11;
  f32 *v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  sdfVector4_t v17;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  klass = handle[1].klass;
  klass[22] = x;
  klass[23] = y;
  klass[24] = z;
  klass[25] = w;
  for (i = handle[2].monitor; i; i = (u64 *)i[7])
  {
    v11 = i[3];
    v12 = *(f32 **)(i[2] + 16);
    v13 = v12[22];
    v14 = v12[23];
    v15 = v12[24];
    v16 = v12[25];
    v17.x = x * v13;
    v17.y = y * v14;
    v17.z = z * v15;
    v17.w = w * v16;
    ColorSet(v11, v17);
  }
}

// 0x19a4770
void effPartsRotateMatrixSet(void *handle, const sdfMatrix4_t *pMatrix) {
  __int128 v5;
  __int128 v7;
  sdfMatrix4_t v11;
  sdfMatrix4_t v12;

  v5 = *(_OWORD *)&pMatrix->m01;
  *(_OWORD *)&v12.m00 = *(_OWORD *)&pMatrix->m00;
  *(_OWORD *)&v12.m01 = v5;
  v7 = *(_OWORD *)&pMatrix->m03;
  *(_OWORD *)&v12.m02 = *(_OWORD *)&pMatrix->m02;
  *(_OWORD *)&v12.m03 = v7;
  v11 = v12;
  effMatrixToQuat(&v11);
  if (!handle)
  effPartsRotateSet(handle, vct_A);
}

// 0x19a1d40
void effPartsItemParamsSet(effPartsListItem_t *pItem, effPartsListItemParams_t *pParams) {
  effPartsListItemParams_t *v5;

  v5 = Allocate(effPartsListItemParams_t);
  _ctor_26764336(v5, pParams, 0);
  pItem->param = v5;
}

// 0x19a1d10
effPartsListItem_t *effPartsItemGet(plistHandle_t *hPartsList, u32 index) {
  effPartsListItem_t *result;
  bool v4;
  u32 v5;
  bool v6;

  result = hPartsList->pLinkTail;
  if (result)
    v4 = index == 0;
  else
    v4 = 1;
  if (!v4)
  {
    v5 = index - 1;
    do
    {
      result = result->prev;
      if (result)
        v6 = v5 == 0;
      else
        v6 = 1;
      --v5;
    }
    while (!v6);
  }
  return result;
}

// 0x19a3b90
static void PosePosBillboard(effPartsListPose_t *pPose, sdfVector4_t *pPos) {
  u32 flag;
  f32 w;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  CameraEyePosFunc v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 *v24;
  CameraTargetPosFunc v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 *v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  sdfVector4_t *p_pos;
  f32 v47;
  struct sdfVector4_t pos;

  flag = pPose->flag;
  if ((flag & 0x18) == 0)
  {
    p_pos = &pPose->pos;
    goto LABEL_38;
  }
  flag = pPose->flag;
  pos = pPose->pos;
  w = zeroVector.w;
  vct_A = pos;
  if ((flag & 0x10) == 0)
    goto LABEL_10;
  vct_A.y = 0.0;
LABEL_11:
  goto LABEL_12;
LABEL_10:
  goto LABEL_11;
LABEL_12:
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v15 = CameraEyePos[camID];
  v16 = (v15->invoke_impl)(v15->method_code, v15->method);
  v18 = v17;
  v20 = v19;
  v22 = v21;
  v24 = &vf00.x;
  v24[4] = v16;
  v24[5] = v18;
  v24[6] = v20;
  v24[7] = v22;
  v26 = CameraTargetPos[camID];
  v27 = (v26->invoke_impl)(v26->method_code, v26->method);
  v29 = v28;
  v31 = v30;
  v33 = v32;
  v35 = &vf00.x;
  v35[8] = v27;
  v35[9] = v29;
  v35[10] = v31;
  v35[11] = v33;
  v36 = x * x;
  v37 = y * y;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  if ((flag & 0x10) == 0)
  {
    v38 = v36 + v37;
    v39 = z * z;
    goto LABEL_28;
  }
  vct_A.y = 0.0;
  v38 = v36 + v37;
  v39 = z * z;
LABEL_28:
  v40 = v38 + v39;
  sub_1949110(0);
  v41 = sqrtf(v40);
  vct_B.x = v41;
  vct_B.y = v41;
  vct_B.z = v41;
  vct_B.w = w;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  if ((flag & 0x10) == 0)
    goto LABEL_33;
  v47 = pPose->pos.y;
  vct_A.y = v47;
LABEL_34:
  goto LABEL_35;
LABEL_33:
  goto LABEL_34;
LABEL_35:
  p_pos = &vct_A;
LABEL_38:
  *pPos = *p_pos;
}

// 0x19a36c0
static void PoseRotBillboard(effPartsListPose_t *pPose, sdfVector4_t *pRot) {
  CameraEyePosFunc v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 *p_x;
  CameraTargetPosFunc v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 *v26;
  long f64 v27;
  f32 y;
  f32 v31;
  f32 v32;
  sdfVector4_t *p_vct_A;
  struct sdfVector4_t rot;

  if ((pPose->flag & 0x60) != 0)
  {
    v6 = CameraEyePos[camID];
    v7 = (v6->invoke_impl)(v6->method_code, v6->method);
    v9 = v8;
    v11 = v10;
    v13 = v12;
    p_x = &vf00.x;
    p_x[4] = v7;
    p_x[5] = v9;
    p_x[6] = v11;
    p_x[7] = v13;
    v17 = CameraTargetPos[camID];
    v18 = (v17->invoke_impl)(v17->method_code, v17->method);
    v20 = v19;
    v22 = v21;
    v24 = v23;
    v26 = &vf00.x;
    v26[8] = v18;
    v26[9] = v20;
    v26[10] = v22;
    v26[11] = v24;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    *(f32 *)&v27 = vct_A.x;
    y = vct_A.y;
    v31 = sub_188E410(v27);
    if ((pPose->flag & 0x40) == 0)
    {
      v32 = sub_188E3F0(-y);
      FromEuler(-v32, v31, 0.0);
LABEL_29:
      p_vct_A = &vct_A;
      goto LABEL_32;
    }
    FromEuler(0.0, v31, 0.0);
    vct_B = vct_A;
    rot = pPose->rot;
    vct_A = rot;
    Mult();
    goto LABEL_29;
  }
  p_vct_A = &pPose->rot;
LABEL_32:
  *pRot = *p_vct_A;
}
