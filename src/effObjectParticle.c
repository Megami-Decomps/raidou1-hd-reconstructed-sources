#include "types.h"
#include "EFFBEHAVIOR_TYPE.h"
#include "effbehavior.h"
#include "effmodel.h"
#include "effobjectparticle.h"
#include "effparts.h"
#include "effpartslist.h"
#include "mdl.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "sdfsystem.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct effBehavior_Params_Basic_t effBehavior_Params_Basic_t;
typedef struct effObjectParticle_Parts_t effObjectParticle_Parts_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct opcHandle_t opcHandle_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;

static void PartsInit(opcHandle_t *hParticle, effObjectParticle_Parts_t *pParts);
static void PartsCalc(opcHandle_t *hParticle, effObjectParticle_Parts_t *pParts, s32 frame);
static opcHandle_t *Create(u32 number);
static opcHandle_t *ParamsCreate(effBehavior_Params_Basic_t *pParams);
static void BehaviorSet(opcHandle_t *hParticle, EFFBEHAVIOR_TYPE type, effBehavior_Params_Basic_t *pParams);
static void ModelSet(opcHandle_t *hParticle, void *pPB);
static sdfModelRootNode_t *ModelGet(opcHandle_t *hParticle);
static void PartsListSet(opcHandle_t *hParticle, void *pEPL);
static void Calc(opcHandle_t *hParticle);
static void Draw(opcHandle_t *hParticle);

// 0x197b290
static void PartsInit(opcHandle_t *hParticle, effObjectParticle_Parts_t *pParts) {
  f32 w;
  effObjectParticles_Params_t *param;
  f32 x;
  f32 y;
  f32 z;
  f32 *p_x;
  f32 v15;
  s64 v16;
  effObjectParticles_Params_t *v17;
  f32 rotate;

  w = zeroVector.w;
  param = hParticle->param;
  if (param->random)
  {
    x = (loc_197D470)(0, pParts);
    y = (loc_197D470)(0);
    z = (loc_197D470)(0);
    goto LABEL_7;
  }
  else
  {
    x = param->axis.x;
    y = param->axis.y;
    z = param->axis.z;
LABEL_7:
    goto LABEL_8;
  }
LABEL_8:
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  sub_1949110(0);
  v15 = vct_A.z;
  v16 = *(u64 *)&vct_A.x;
  v17 = hParticle->param;
  *(u64 *)&pParts->axis.x = v16;
  pParts->axis.z = v15;
  rotate = v17->rotate;
  pParts->rotate_s = rotate * (loc_197D1B0)(0, v17->rotate_r);
  pParts->rotate = (loc_197D320)(0) * 6.2831855;
}

// 0x197b470
static void PartsCalc(opcHandle_t *hParticle, effObjectParticle_Parts_t *pParts, s32 frame) {
  f32 z;
  f32 x;
  f32 y;
  f32 rotate_a;
  f32 rotate;
  f32 rotate_s;
  f32 v15;

  z = pParts->axis.z;
  x = pParts->axis.x;
  y = pParts->axis.y;
  rotate_a = hParticle->param->rotate_a;
  rotate = pParts->rotate;
  rotate_s = pParts->rotate_s;
  v15 = (f32)(rotate_s * (f32)frame) + (f32)((f32)((f32)(rotate_a * (f32)frame) * (f32)frame) * 0.5);
  if (v15 < 0.0)
    v15 = 0.0;
  sub_197D860(&mtx_A, 0, rotate + v15, x, y, z, 0.0);
}

// 0x197b5e0
static opcHandle_t *Create(u32 number) {
  opcHandle_t *v3;

  v3 = Allocate(opcHandle_t);
  v3->number = number;
  *(u32 *)&v3->scale = 1065353216;
  v3->hModel = 0;
  v3->abgr = oneVector;
  v3->pEarlyModel = 0;
  v3->hBehavior = 0;
  v3->phPartsList = 0;
  *(u32 *)&v3->state = 1;
  return v3;
}

// 0x197b6d0
static opcHandle_t *ParamsCreate(effBehavior_Params_Basic_t *pParams) {
  u32 count;
  u32 life;
  u32 v4;
  u32 v5;
  u32 v7;

  life = pParams->emitter->life;
  count = pParams->emitter->count;
  if (life)
  {
    v4 = life * count;
    if (v4 >= 0x12C)
      v5 = 300;
    else
      v5 = v4;
  }
  else
  {
    v7 = pParams->life * count;
    if (v7 >= 0x12C)
      v5 = 300;
    else
      v5 = v7;
  }
  return Create(v5);
}

// 0x197b710
opcHandle_t *PartsCreate(Standard *pParts) {
  u16 type;
  u8 *v4;
  sdfBinary *v5;
  effObjectParticles_Params_t *v6;
  effBehavior_Params_Basic_t *Params;
  effBehavior_Params_Basic_t *v10;
  u32 life;
  u32 v12;
  opcHandle_t *v13;
  void *v15;
  s32 v16;
  void *v17;
  s64 v20;

  type = pParts->param->type;
  v4 = effParamsGet(pParts);
  v5 = Allocate(sdfBinary);
  _ctor_36176832(v5, v4, 0);
  v6 = Allocate(effObjectParticles_Params_t);
  _ctor_26730496(v6, v5, 0);
  Params = effCreateParams(type, v5);
  v10 = Params;
  life = Params->emitter->life;
  if (!life)
    life = Params->life;
  if (life * Params->emitter->count >= 0x12C)
    v12 = 300;
  else
    v12 = life * Params->emitter->count;
  v13 = Create(v12);
  v13->param = v6;
  BehaviorSet(v13, type, v10);
  v15 = effDataGet(pParts);
  if (v15)
  {
    v16 = pParts->data->type;
    if (v16 == 6)
    {
      v20 = (v15->klass->vtable._5_GetExtUnits.methodPtr)(v15, v15->klass->vtable._5_GetExtUnits.method);
      PartsListSet(v13, *(void *)(v20 + 32));
    }
    else if (v16 == 3)
    {
      v17 = (v15->klass->vtable._4_GetExtResource.methodPtr)(v15, v15->klass->vtable._4_GetExtResource.method);
      ModelSet(v13, v17);
    }
    v13->matType = pParts->data->type;
  }
  return v13;
}

// 0x197bd80
void Delete(effPartsHandle_t *handle) {
  effOption *option;
  effPartsHandle_t *klass;
  s64 v6;
  void *monitor;
  s64 v8;
  effPartsHandle_t *v9;
  effPartsHandle_t *v10;

  option = handle[2].option;
  if (option)
  {
    mdlSetLight(option, 0);
    Free(option);
  }
  klass = handle[3].klass;
  if (klass)
  {
    if (SLODWORD(klass->_1.namespaze) >= 1)
    {
      v6 = 0;
      do
        sdfModelRootFree(*((sdfModelRootNode_t *)&klass->_1.byval_arg.data + v6++));
      while (v6 < SLODWORD(klass->_1.namespaze));
    }
    handle[3].klass = 0;
  }
  monitor = handle[3].monitor;
  if (monitor)
  {
    if (*((s32 *)monitor + 6) >= 1)
    {
      v8 = 0;
      do
        effPartsDelete(monitor[v8++ + 4]);
      while (v8 < *((s32 *)monitor + 6));
    }
    handle[3].monitor = 0;
  }
  v10 = handle[4].klass;
  v9 = handle + 4;
  if (v10)
  {
    v9->klass = 0;
  }
}

// 0x197bf30
opcHandle_t *Copy(effPartsHandle_t *handle) {
  effBehavior_Params_Basic_t *v4;
  u32 life;
  u32 v6;
  opcHandle_t *v7;
  effObjectParticles_Params_t *monitor;
  effObjectParticles_Params_t *v9;

  v4 = *(effBehavior_Params_Basic_t *)&handle[3].option[1].adjustRGBA.x;
  life = v4->emitter->life;
  if (!life)
    life = v4->life;
  if (life * v4->emitter->count >= 0x12C)
    v6 = 300;
  else
    v6 = life * v4->emitter->count;
  v7 = Create(v6);
  monitor = handle[2].monitor;
  v9 = Allocate(effObjectParticles_Params_t);
  _ctor_26730672(v9, monitor, 0);
  v7->param = v9;
  BehaviorSet(v7, handle[3].option->FieldOt, v4);
  ResourceCopy(v7, handle);
  return v7;
}

// 0x197c050
void ResourceCopy(effPartsHandle_t *dstHandle, effPartsHandle_t *srcHandle) {
  s32 klass_low;
  effOption *option;
  effPartsHandle_t *v9;
  effPartsHandle_t *klass;
  s64 v11;
  effOption *v12;
  u16 MajorNum;
  s32 MinorNum;
  dds3ModelHandle_t *v15;
  effPartsHandle_t *v17;
  void **p_monitor;
  void *monitor;
  s64 v20;
  void *v21;
  char *v22;
  s64 v23;
  s64 v24;
  plistHandle_t *v25;
  plistHandle_t *v26;

  klass_low = LOWORD(srcHandle[2].klass);
  if (klass_low == 6)
  {
    p_monitor = &dstHandle[3].monitor;
    monitor = dstHandle[3].monitor;
    if (monitor)
    {
      if (*((s32 *)monitor + 6) >= 1)
      {
        v20 = 0;
        do
          effPartsDelete(monitor[v20++ + 4]);
        while (v20 < *((s32 *)monitor + 6));
      }
      *p_monitor = 0;
    }
    v21 = NewSpecific(plistHandle_t, LODWORD(srcHandle[3].option->adjustRGBA.x));
    *p_monitor = v21;
    v22 = *p_monitor;
    if (*((s32 *)*p_monitor + 6) >= 1)
    {
      v23 = 0;
      v24 = 32;
      do
      {
        v25 = Copy(*((void *)srcHandle[3].monitor + 4));
        v26 = v25;
        if (v25)
          QueryInterface(v25, *(void **)(*(u64 *)v22 + 64));
        *(u64 *)&v22[v24] = v26;
        v22 = *p_monitor;
        ++v23;
        v24 += 8;
      }
      while (v23 < *((s32 *)*p_monitor + 6));
    }
  }
  else if (klass_low == 3)
  {
    option = dstHandle[2].option;
    if (option)
    {
      mdlSetLight(option, 0);
      Free(option);
    }
    v9 = dstHandle + 3;
    klass = dstHandle[3].klass;
    if (klass)
    {
      if (SLODWORD(klass->_1.namespaze) >= 1)
      {
        v11 = 0;
        do
          sdfModelRootFree(*((sdfModelRootNode_t *)&klass->_1.byval_arg.data + v11++));
        while (v11 < SLODWORD(klass->_1.namespaze));
      }
      v9->klass = 0;
    }
    v12 = srcHandle[2].option;
    MajorNum = mdlGetMajorNum(v12);
    MinorNum = mdlGetMinorNum(v12);
    v15 = mdlLoad(MajorNum, MinorNum);
    Init();
    dstHandle[2].option = (effOption *)v15;
    v17 = NewSpecific(sdfModelRootNode_t, LODWORD(srcHandle[3].option->adjustRGBA.x));
    v9->klass = v17;
  }
  LOWORD(dstHandle[2].klass) = srcHandle[2].klass;
}

// 0x197b900
static void BehaviorSet(opcHandle_t *hParticle, EFFBEHAVIOR_TYPE type, effBehavior_Params_Basic_t *pParams) {
  bhvrHandle_t *v7;
  effObjectParticle_Parts_t *v8;
  s64 v9;
  s64 v10;
  effObjectParticle_Parts_t *v12;
  effObjectParticle_Parts_t *pParts;

  v7 = effCreate(type, hParticle->number, pParams);
  hParticle->hBehavior = v7;
  v8 = NewSpecific(effObjectParticle_Parts_t, hParticle->hBehavior->numall);
  hParticle->pParts = v8;
  if (SLODWORD(hParticle->pParts->max_length) >= 1)
  {
    v9 = 0;
    v10 = 32;
    do
    {
      v12 = Allocate(effObjectParticle_Parts_t);
      _ctor(v12, 0);
      pParts = hParticle->pParts;
      *(Il2CppClass **)((char *)&pParts->obj.klass + v10) = v12;
      PartsInit(hParticle, v12);
      ++v9;
      v10 += 8;
    }
    while (v9 < SLODWORD(hParticle->pParts->max_length));
  }
}

// 0x197ba50
static void ModelSet(opcHandle_t *hParticle, void *pPB) {
  dds3ModelHandle_t *hModel;
  sdfModelRootNode_t *pEarlyModel;
  s64 v7;
  dds3ModelHandle_t *v8;
  sdfModelRootNode_t *v9;

  hModel = hParticle->hModel;
  if (hModel)
  {
    mdlSetLight(hModel, 0);
    Free(hModel);
    hParticle->hModel = 0;
  }
  pEarlyModel = hParticle->pEarlyModel;
  if (pEarlyModel)
  {
    if (SLODWORD(pEarlyModel->max_length) >= 1)
    {
      v7 = 0;
      do
        sdfModelRootFree(pEarlyModel[v7++]);
      while (v7 < SLODWORD(pEarlyModel->max_length));
    }
    hParticle->pEarlyModel = 0;
  }
  v8 = effHandleCreate(pPB);
  hParticle->hModel = v8;
  v9 = NewSpecific(sdfModelRootNode_t, hParticle->hBehavior->numall);
  hParticle->pEarlyModel = v9;
}

// 0x197c390
static sdfModelRootNode_t *ModelGet(opcHandle_t *hParticle) {
  bhvrHandle_t *hBehavior;
  s64 numall;
  effPosture_t *pPosture;
  s64 v6;
  s32 v7;
  Il2CppClass **v8;
  sdfModelRootNode_t *v9;
  sdfModelRootNode_t *_36047984;
  void *transform;
  void *v14;

  hBehavior = hParticle->hBehavior;
  numall = hBehavior->numall;
  if ((u32)numall)
  {
    pPosture = hBehavior->pPosture;
    v6 = 0;
    v7 = 1;
    while (1)
    {
      if (pPosture[v6]->frame < 0)
      {
        v8 = &hParticle->pEarlyModel->obj.klass + v6;
        v9 = (sdfModelRootNode_t *)v8[4];
        if (v9)
          break;
      }
      v6 = v7++;
      if (v6 >= numall)
        goto LABEL_9;
    }
    v8[4] = 0;
    return v9;
  }
  else
  {
LABEL_9:
    _36047984 = sdfModelMake_2(hParticle->hModel->resrc->modelDefPtr);
    transform = get_transform(_36047984->modelObj, 0);
    v14 = get_transform(hook, 0);
    SetParent(transform, v14, 0);
    return _36047984;
  }
}

// 0x197bbb0
static void PartsListSet(opcHandle_t *hParticle, void *pEPL) {
  plistHandle_t **p_phPartsList;
  plistHandle_t *phPartsList;
  s64 v7;
  plistHandle_t *v8;
  plistHandle_t *v9;
  plistHandle_t *v11;
  plistHandle_t *v12;
  void *v13;
  s64 v14;
  s64 i;
  plistHandle_t *v16;
  void *v17;

  p_phPartsList = &hParticle->phPartsList;
  phPartsList = hParticle->phPartsList;
  if (phPartsList)
  {
    if (SLODWORD(phPartsList->max_length) >= 1)
    {
      v7 = 0;
      do
        effPartsDelete(phPartsList[v7++]);
      while (v7 < SLODWORD(phPartsList->max_length));
    }
    *p_phPartsList = 0;
  }
  v8 = NewSpecific(plistHandle_t, hParticle->hBehavior->numall);
  hParticle->phPartsList = v8;
  v9 = hParticle->phPartsList;
  v11 = Create(pEPL, 0);
  v12 = v11;
  v9[0] = v12;
  v13 = *p_phPartsList;
  if (SLODWORD((*p_phPartsList)->max_length) >= 2)
  {
    v14 = 1;
    for (i = 5; ; ++i)
    {
      v16 = Copy(v13[4]);
      v17 = v16;
      if (v16)
      {
        if (!QueryInterface(v16, v13[4].klass))
          break;
      }
      v13[i] = v17;
      v13 = *p_phPartsList;
      if (++v14 >= SLODWORD((*p_phPartsList)->max_length))
        return;
    }
  }
}

// 0x197c550
static void Calc(opcHandle_t *hParticle) {
  bhvrHandle_t *hBehavior;
  bhvrHandle_t *v6;
  s64 v7;
  s32 v8;
  s32 matType;

  hBehavior = hParticle->hBehavior;
  if (hBehavior)
  {
    Calc(hBehavior->pParams);
    v6 = hParticle->hBehavior;
    ++hBehavior->frame;
    if (v6->numall)
    {
      v7 = 0;
      v8 = 1;
      do
      {
        if (!v6->pPosture[v7]->frame)
        {
          matType = hParticle->matType;
          if (matType == 6)
          {
            Reset(hParticle->phPartsList[v7], 0);
          }
          else if (matType == 3)
          {
            PartsInit(hParticle, hParticle->pParts[v7]);
          }
        }
        v6 = hParticle->hBehavior;
        v7 = v8++;
      }
      while (v7 < v6->numall);
    }
  }
}

// 0x197c620
static void Draw(opcHandle_t *hParticle) {
  void *v3;
  s64 v4;
  f32 v5;
  s64 v6;
  s32 v7;
  f32 v8;
  sdfVector4_t *v9;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s64 v17;
  sdfVector4_t *v19;
  opcHandle_t *v20;
  s32 v21;
  intptr_t *v22;
  s64 v23;
  s64 v24;
  s64 v25;
  opcHandle_t *v26;
  void *v27;
  s64 v28;
  struct sdfVector4_t v30;
  struct sdfVector4_t v33;
  struct sdfMatrix4_t identityMatrix_local;
  sdfMatrix4_t v37;
  sdfMatrix4_t v38;
  sdfVector4_t v39;
  sdfVector4_t v40;

  v3 = Allocate(Project_effObjectParticle___c__DisplayClass15_0);
  v3->hParticle = hParticle;
  v4 = &v3->hParticle;
  v5 = 1.0;
  v6 = *(u64 *)(*(u64 *)v4 + 88);
  v7 = *(u32 *)(v6 + 28);
  identityMatrix_local = identityMatrix;
  if (!*(u8 *)(*(u64 *)(*(u64 *)v4 + 56) + 48) || (v8 = *(f32 *)(*(u64 *)v4 + 44), v8 == 0.0))
  {
    if ((v7 & 1) == 0)
      goto LABEL_16;
LABEL_8:
    v9 = *(sdfVector4_t *)(*(u64 *)(v6 + 56) + 16);
    x = v9[1].x;
    y = v9[1].y;
    z = v9[1].z;
    w = v9[1].w;
    v33 = v9[2];
    vct_A = v33;
    ToMatrix();
    v40.x = x;
    v40.y = y;
    v40.z = z;
    v40.w = w;
    SetRow(&mtx_A, 3, v40, 0);
    identityMatrix_local = mtx_A;
    goto LABEL_16;
  }
  v5 = 1.0 / v8;
  if ((v7 & 1) != 0)
    goto LABEL_8;
LABEL_16:
  v3->pPosture = 0;
  v17 = &v3->pPosture;
  v3->abgr = zeroVector;
  v3->pos = zeroVector;
  v19 = &v3->pos;
  v20 = v3->hParticle;
  *(u32 *)&v3->scale = 0;
  v3->i = 0;
  v21 = v20->matType;
  if (v21 != 3)
  {
    if (v21 == 6)
    {
      v22 = &Method_Project_effObjectParticle___c__DisplayClass15_0__Draw_g__DrawEPL_1__;
      goto LABEL_22;
    }
    v23 = 0;
    v24 = v3->i;
    v25 = *(u64 *)((u64)v3->hParticle + 88);
    if (v24 >= *(u32 *)(v25 + 24))
      return;
    while (1)
    {
LABEL_29:
      v27 = *(void **)(*(u64 *)(v25 + 40) + 8 * v24 + 32);
      *(u64 *)v17 = v27;
      v28 = *(u64 *)v17;
      if ((*(u32 *)(*(u64 *)v17 + 32) & 0x80000000) != 0)
        goto LABEL_28;
      *(float32x4_t *)&v3->abgr = vmulq_f32(*(float32x4_t *)(v28 + 36), *(float32x4_t *)((u64)v3->hParticle + 28));
      *v19 = *(sdfVector4_t *)(v28 + 16);
      v3->scale = v5 * *(f32 *)(v28 + 52);
      if ((v7 & 1) != 0)
        break;
LABEL_27:
      (*(v23 + 24))(*(u64 *)(v23 + 64), *(u64 *)(v23 + 40));
LABEL_28:
      LODWORD(v24) = v3->i + 1;
      v26 = v3->hParticle;
      v3->i = v24;
      v24 = (s32)v24;
      v25 = v26->hBehavior;
      if ((s32)v24 >= (s64)*(u32 *)(v25 + 24))
        return;
    }
    mtx_A = identityMatrix_local;
    v30 = *v19;
    vct_A = v30;
    vct_A.w = 1.0;
    get_transpose(&v38, &mtx_A, 0);
    v37 = v38;
    v39 = op_Multiply_60923920(&v37, vct_A, 0);
    vct_A = v39;
    *v19 = vct_A;
    goto LABEL_27;
  }
  v22 = &Method_Project_effObjectParticle___c__DisplayClass15_0__Draw_g__DrawPB_0__;
LABEL_22:
  v23 = Allocate(System_Action);
  _ctor(v23, v3, *v22, 0);
  v24 = v3->i;
  v25 = *(u64 *)((u64)v3->hParticle + 88);
  if (v24 < *(u32 *)(v25 + 24))
    goto LABEL_29;
}

// 0x197cc00
void CalcAndDraw(effPartsHandle_t *handle) {
  if ((WORD1(handle[4].monitor) & 1) != 0 || !get_STOP(0))
  {
    Calc(handle);
LABEL_9:
    goto LABEL_10;
  }
  else
  {
    goto LABEL_9;
  }
LABEL_10:
  if (drawSkip)
    return;
  Draw();
  return;
}

// 0x197cd50
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *v9;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  v9 = *(f32 **)(*(u64 *)&handle[3].option[1].FieldOt + 16);
  v9[6] = z;
  v9[7] = w;
  v9[4] = x;
  v9[5] = y;
}

// 0x197ce00
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *v9;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  v9 = *(f32 **)(*(u64 *)&handle[3].option[1].FieldOt + 16);
  v9[10] = z;
  v9[11] = w;
  v9[8] = x;
  v9[9] = y;
}

// 0x197ceb0
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

// 0x197cf60
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  effOption *option;
  u64 *v6;
  s64 v7;
  s64 v8;
  float32x2_t v9;
  u64 *v10;
  s64 v11;
  s64 v12;
  s64 v13;
  u64 *v14;
  s64 v15;
  s64 v16;
  s64 v17;
  f32 v18;

  v18 = scale;
  scale = v18;
  option = handle[3].option;
  *((f32 *)&handle[1].option + 1) = scale;
  v6 = *(u64 **)&option[1].FieldOt;
  v7 = *(u64 *)(*(u64 *)&option[1].adjustRGBA.x + 40);
  v8 = v6[5];
  v9.n64_u64[0] = *(u64 *)(v7 + 20);
  v10 = *(u64 **)(v7 + 40);
  v11 = v10[4];
  v12 = v10[5];
  v13 = v10[6];
  *(float32x2_t *)(v8 + 20) = vmul_n_f32(v9, scale);
  v14 = *(u64 **)(v8 + 40);
  v9.n64_u32[0] = *(u32 *)(v11 + 20);
  v15 = v14[4];
  v16 = v14[5];
  v17 = v14[6];
  *(f32 *)(v15 + 20) = v9.n64_f32[0] * scale;
  *(f32 *)(v16 + 20) = *(f32 *)(v12 + 20) * scale;
  *(f32 *)(v17 + 20) = *(f32 *)(v13 + 20) * scale;
  (*(*v6 + 472))(v6, option, *(u64 *)(*v6 + 480));
}
