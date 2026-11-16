#include "types.h"
#include "effbattleonly.h"
#include "effparts.h"
#include "sbtl.h"
#include "sdf_vu0.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct bonlyHandle_t bonlyHandle_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct sdfBinary sdfBinary;

typedef void *(*NewFunc)(sdfBinary *binParams, void *refParams);

static NewFunc *effBattleOnlyTypeTable[14];

static bonlyHandle_t *HandleCreate(EFFBATTLEONLY_TYPE type, sdfBinary *pParams);
static void *DefaultNew(sdfBinary *binParams, void *refParams);
static bonlyHandle_t *Create(u16 type, sdfBinary *pParams, void *pData);
static void Calc(bonlyHandle_t *hBtlOnly);
static void Draw(bonlyHandle_t *hBtlOnly);

// 0x1967a10
static bonlyHandle_t *HandleCreate(EFFBATTLEONLY_TYPE type, sdfBinary *pParams) {
  bonlyHandle_t *v5;
  sdfVector4_t *v9;
  sdfVector4_t *v10;
  NewFunc v14;
  void *v15;

  v5 = Allocate(bonlyHandle_t);
  v5->frame = 0;
  v5->type = type;
  *(u32 *)&v5->scale = 1065353216;
  v5->abgr = oneVector;
  v9 = &v5->pos;
  *v9 = vf00;
  v10 = &v5->rot;
  *v10 = vf00;
  v14 = effBattleOnlyTypeTable[type];
  v15 = (v14->invoke_impl)(v14->method_code, pParams, &v5->pParams, v14->method);
  v5->pHandle = v15;
  return v5;
}

// 0x1967c50
static void *DefaultNew(sdfBinary *binParams, void *refParams) {
  Il2CppObject *v4;
  void *v5;

  v4 = Allocate(Project_effBattleOnly_Params_Basic_t);
  _ctor(v4, 0);
  refParams = (void *)v4;
  v5 = (void *)Allocate(Project_effBattleOnly_Basic_t);
  _ctor(v5, 0);
  return v5;
}

// 0x1967d00
static bonlyHandle_t *Create(u16 type, sdfBinary *pParams, void *pData) {
  bonlyHandle_t *v7;

  v7 = HandleCreate(type, pParams);
  if (!CheckRun())
    return v7;
  (v7->pHandle->klass->vtable._5_Create.methodPtr)(v7->pHandle, pParams, pData, v7->pHandle->klass->vtable._5_Create.method);
  (v7->pHandle->klass->vtable._4_Init.methodPtr)(v7->pHandle, v7, v7->pHandle->klass->vtable._4_Init.method);
  return v7;
}

// 0x1967e00
bonlyHandle_t *effPartsCreate(Standard *pParts) {
  u8 *v3;
  void *v4;
  u16 type;
  sdfBinary *v6;

  v3 = effParamsGet(pParts);
  v4 = effDataGet(pParts);
  type = pParts->param->type;
  v6 = Allocate(sdfBinary);
  _ctor_36176832(v6, v3, 0);
  return Create(type, v6, v4);
}

// 0x1967ef0
void effDelete(effPartsHandle_t *handle) {
  if (CheckRun())
    (handle[3].option->klass[1]._1.byval_arg.data)(handle[3].option, *(u64 *)&handle[3].option->klass[1]._1.byval_arg.bits);
}

// 0x1967fc0
bonlyHandle_t *Copy(effPartsHandle_t *handle) {
  u32 monitor;
  bonlyHandle_t *v6;
  void *v7;

  monitor = handle[3].monitor;
  v6 = HandleCreate(monitor, 0);
  v7 = (*(handle[4].klass->_1.image + 47))(handle[4].klass, *((u64 *)handle[4].klass->_1.image + 48));
  v6->pParams = v7;
  (v6->pHandle->klass->vtable._7_Copy.methodPtr)(v6->pHandle, handle, v6->pHandle->klass->vtable._7_Copy.method);
  (v6->pHandle->klass->vtable._4_Init.methodPtr)(v6->pHandle, v6, v6->pHandle->klass->vtable._4_Init.method);
  return v6;
}

// 0x19681a0
static void Calc(bonlyHandle_t *hBtlOnly) {
  (hBtlOnly->pHandle->klass->vtable._8_Calc.methodPtr)(hBtlOnly->pHandle, hBtlOnly, hBtlOnly->pHandle->klass->vtable._8_Calc.method);
  if ((wk->status & 0x8000000) != 0)
    return;
  ++hBtlOnly->frame;
  return;
}

// 0x1968250
static void Draw(bonlyHandle_t *hBtlOnly) {
  (hBtlOnly->pHandle->klass->vtable._9_Draw.methodPtr)(hBtlOnly->pHandle, hBtlOnly, hBtlOnly->pHandle->klass->vtable._9_Draw.method);
}

// 0x1968270
void effCalcAndDraw(effPartsHandle_t *handle) {
  if (!CheckRun())
    return;
  (handle[3].option->klass[1]._1.element_class)(handle[3].option, handle, handle[3].option->klass[1]._1.castClass);
  if ((wk->status & 0x8000000) != 0)
  {
    goto LABEL_16;
  }
  ++HIDWORD(handle[3].klass);
LABEL_16:
  if (drawSkip)
    return;
  (handle[3].option->klass[1]._1.declaringType)(handle[3].option, handle, handle[3].option->klass[1]._1.parent);
}

// 0x19684c0
void effPositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  *(f32 *)&handle[1].monitor = z;
  *((f32 *)&handle[1].monitor + 1) = w;
  *(f32 *)&handle[1].klass = x;
  *((f32 *)&handle[1].klass + 1) = y;
}

// 0x1968570
void effRotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  *(f32 *)&handle[2].klass = z;
  *((f32 *)&handle[2].klass + 1) = w;
  *(f32 *)&handle[1].option = x;
  *((f32 *)&handle[1].option + 1) = y;
}

// 0x1968620
void effColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *((f32 *)&handle[2].option + 1) = z;
  *(f32 *)&handle[3].klass = w;
  *((f32 *)&handle[2].monitor + 1) = x;
  *(f32 *)&handle[2].option = y;
}

// 0x19686d0
void effScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].monitor = scale;
}
