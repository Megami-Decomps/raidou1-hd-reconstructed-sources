#include "types.h"
#include "effpolygonscaly.h"
#include "effpolygonscalylist.h"
#include "sdf_vu0.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonScaly_Basic_t effPolygonScaly_Basic_t;
typedef struct effPolygonScaly_Params_Basic_t effPolygonScaly_Params_Basic_t;
typedef struct pscalyHandle_t pscalyHandle_t;
typedef struct sdfBinary sdfBinary;

typedef effPolygonScaly_Basic_t *(*effPolygonScaly_CreateFunc)(sdfBinary *binParams, effPolygonScaly_Params_Basic_t *refParams);

static effPolygonScaly_CreateFunc *effPolygonScalyTypeTable[5];

static pscalyHandle_t *HandleCreate(EFFPOLYGON_SCALY_TYPE type);
static pscalyHandle_t *Create(u16 type, u8 *pParams);

// 0x198c2c0
static pscalyHandle_t *HandleCreate(EFFPOLYGON_SCALY_TYPE type) {
  pscalyHandle_t *v3;
  sdfVector4_t *v7;

  v3 = Allocate(pscalyHandle_t);
  v3->frame = 0;
  v3->type = type;
  *(u32 *)&v3->scale = 1065353216;
  v3->abgr = oneVector;
  v7 = &v3->pos;
  *v7 = vf00;
  v3->rot = vf00;
  return v3;
}

// 0x198c460
static pscalyHandle_t *Create(u16 type, u8 *pParams) {
  pscalyHandle_t *v5;
  effPolygonScaly_CreateFunc v6;
  sdfBinary *v7;
  effPolygonScaly_Basic_t *v8;

  v5 = HandleCreate(type, pParams);
  v6 = effPolygonScalyTypeTable[type];
  v7 = Allocate(sdfBinary);
  _ctor_36176832(v7, pParams, 0);
  v8 = (v6->invoke_impl)(v6->method_code, v7, &v5->pParams, v6->method);
  v5->pHandle = v8;
  (v5->pHandle->klass->vtable._6_Init.methodPtr)(v5->pHandle, v5, v5->pHandle->klass->vtable._6_Init.method);
  return v5;
}

// 0x198c560
pscalyHandle_t *PartsCreate(Standard *pParts) {
  s64 naturalAligment;
  u8 *klass;
  u16 type;
  void *pData;

  if (!pParts)
    goto LABEL_11;
  goto LABEL_9;
  if (!pParts)
  {
LABEL_11:
    klass = 0;
    goto LABEL_12;
  }
LABEL_9:
  if (pParts->klass->_2.naturalAligment < (u32)naturalAligment || pParts->klass->_2.typeHierarchy[naturalAligment - 1] != Project_effParts_t_Resource_Common)
  {
    goto LABEL_11;
  }
  pData = pParts->param->pData;
  klass = pData[1].klass;
LABEL_12:
  type = pParts->param->type;
  return Create(type, klass);
}

// 0x198c6e0
void Delete(effPartsHandle_t *handle) {
  (handle[3].option->klass[1]._1.generic_class)(handle[3].option, handle[3].option->klass[1]._1.typeMetadataHandle);
}

// 0x198c770
pscalyHandle_t *Copy(effPartsHandle_t *handle) {
  u32 monitor;
  pscalyHandle_t *v5;
  effPartsHandle_t *klass;
  pscalyHandle_t *v7;
  effPolygonScaly_Basic_t *v8;

  monitor = handle[3].monitor;
  v5 = HandleCreate(monitor);
  klass = handle[4].klass;
  v7 = v5;
  v5->pParams = (effPolygonScaly_Params_Basic_t *)klass;
  v8 = (handle[3].option->klass[1]._1.declaringType)(handle[3].option, handle, handle[3].option->klass[1]._1.parent);
  v7->pHandle = v8;
  (v7->pHandle->klass->vtable._6_Init.methodPtr)(v7->pHandle, v7, v7->pHandle->klass->vtable._6_Init.method);
  return v7;
}

// 0x198c910
void CalcAndDraw(effPartsHandle_t *handle) {
  if (get_STOP(0))
  {
    goto LABEL_8;
  }
  else
  {
    (handle[3].option->klass[1]._1.interopData)(handle[3].option, handle, handle[3].option->klass[1]._1.klass);
    ++HIDWORD(handle[3].klass);
LABEL_8:
    goto LABEL_9;
  }
LABEL_9:
  if (drawSkip)
    return;
  (handle[3].option->klass[1]._1.fields)(handle[3].option, handle, handle[3].option->klass[1]._1.events);
  return;
}

// 0x198ca80
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
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

// 0x198cb30
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
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

// 0x198cbe0
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
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

// 0x198cc90
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].monitor = scale;
}

// 0x198cd20
void Init(void) {
  effPolygonScalyInit();
}
