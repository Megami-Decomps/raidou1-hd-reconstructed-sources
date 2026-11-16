#include "types.h"
#include "effpolygonthunder.h"
#include "sdf_vu0.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonThunder_Basic_t effPolygonThunder_Basic_t;
typedef struct effPolygonThunder_Params_Basic_t effPolygonThunder_Params_Basic_t;
typedef struct ptndHandle_t ptndHandle_t;
typedef struct sdfBinary sdfBinary;

typedef effPolygonThunder_Basic_t *(*effPolygonThunder_CreateFunc)(sdfBinary *binParams, effPolygonThunder_Params_Basic_t *refParams);

static effPolygonThunder_CreateFunc *effPolygonThunderTypeTable[4];

static ptndHandle_t *Create(EFFPOLYGON_THUNDER_TYPE type, u8 *pParams);

// 0x1990600
static ptndHandle_t *Create(EFFPOLYGON_THUNDER_TYPE type, u8 *pParams) {
  ptndHandle_t *v5;
  sdfVector4_t *v9;
  sdfVector4_t *v10;
  effPolygonThunder_CreateFunc v14;
  sdfBinary *v15;
  void *v16;

  v5 = Allocate(ptndHandle_t);
  v5->frame = 0;
  v5->type = type;
  *(u32 *)&v5->scale = 1065353216;
  v5->abgr = oneVector;
  v9 = &v5->pos;
  *v9 = vf00;
  v10 = &v5->rot;
  *v10 = vf00;
  if (!pParams)
    return v5;
  v14 = effPolygonThunderTypeTable[type];
  v15 = Allocate(sdfBinary);
  _ctor_36176832(v15, pParams, 0);
  v16 = (v14->invoke_impl)(v14->method_code, v15, &v5->pParams, v14->method);
  v5->pHandle = v16;
  (*(*(u64 *)v5->pHandle + 408))((u64)v5->pHandle, v5, *(u64 *)(*(u64 *)v5->pHandle + 416));
  return v5;
}

// 0x1990880
ptndHandle_t *PartsCreate(Standard *pParts) {
  s64 naturalAligment;
  u8 *klass;
  u32 type;
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

// 0x1990a00
void Delete(effPartsHandle_t *handle) {
  (handle[3].option->klass[1]._1.declaringType)(handle[3].option, handle[3].option->klass[1]._1.parent);
}

// 0x1990a90
ptndHandle_t *Copy(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;
  u32 monitor;
  ptndHandle_t *v7;
  effPolygonThunder_Basic_t *v8;
  effPolygonThunder_Basic_t *p_pHandle;

  klass = handle[4].klass;
  monitor = handle[3].monitor;
  v7 = Create(monitor, 0);
  v7->pParams = (effPolygonThunder_Params_Basic_t *)klass;
  v8 = (handle[3].option->klass[1]._1.image)(handle[3].option, handle[3].option->klass[1]._1.gc_desc);
  v7->pHandle = v8;
  p_pHandle = &v7->pHandle;
  (p_pHandle->klass->vtable._8_Create.methodPtr)(p_pHandle, klass, p_pHandle->klass->vtable._8_Create.method);
  (p_pHandle->klass->vtable._6_unknown.methodPtr)(p_pHandle, v7, p_pHandle->klass->vtable._6_unknown.method);
  return v7;
}

// 0x1990c50
void Calc(ptndHandle_t *hPolygon) {
  (hPolygon->pHandle->klass->vtable._10_Calc.methodPtr)(hPolygon->pHandle, hPolygon, hPolygon->pHandle->klass->vtable._10_Calc.method);
  ++hPolygon->frame;
}

// 0x1990c90
void Draw(ptndHandle_t *hPolygon) {
  (hPolygon->pHandle->klass->vtable._18_Draw.methodPtr)(hPolygon->pHandle, hPolygon, hPolygon->pHandle->klass->vtable._18_Draw.method);
}

// 0x1990cb0
void CalcAndDraw(effPartsHandle_t *handle) {
  if (get_STOP(0))
  {
    goto LABEL_8;
  }
  else
  {
    (handle[3].option->klass[1]._1.generic_class)(handle[3].option, handle, handle[3].option->klass[1]._1.typeMetadataHandle);
    ++HIDWORD(handle[3].klass);
LABEL_8:
    goto LABEL_9;
  }
LABEL_9:
  if (drawSkip)
    return;
}

// 0x1990e60
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

// 0x1990f10
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

// 0x1990fc0
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

// 0x1991070
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].monitor = scale;
}
