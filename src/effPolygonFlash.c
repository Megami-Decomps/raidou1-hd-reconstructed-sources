#include "types.h"
#include "effpolygonflash.h"
#include "effpolygonflashlist.h"
#include "sdf_vu0.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonFlash_Basic_t effPolygonFlash_Basic_t;
typedef struct effPolygonFlash_Params_Basic_t effPolygonFlash_Params_Basic_t;
typedef struct pflashHandle_t pflashHandle_t;
typedef struct sdfBinary sdfBinary;

typedef effPolygonFlash_Basic_t *(*effPolygonFlash_CreateFunc)(sdfBinary *binParams, void *pTex, effPolygonFlash_Params_Basic_t *refParams);

static effPolygonFlash_CreateFunc *effPolygonFlashTypeTable[9];

static pflashHandle_t *HandleCreate(EFFPOLYGON_FLASH_TYPE type);
static pflashHandle_t *Create(u16 type, u8 *pParams, void *pTex);

// 0x1987b40
static pflashHandle_t *HandleCreate(EFFPOLYGON_FLASH_TYPE type) {
  pflashHandle_t *v3;
  sdfVector4_t *v7;

  v3 = Allocate(pflashHandle_t);
  v3->frame = 0;
  v3->type = type;
  *(u32 *)&v3->scale = 1065353216;
  v3->abgr = oneVector;
  v7 = &v3->pos;
  *v7 = vf00;
  v3->rot = vf00;
  return v3;
}

// 0x1987ce0
static pflashHandle_t *Create(u16 type, u8 *pParams, void *pTex) {
  pflashHandle_t *v7;
  effPolygonFlash_CreateFunc v8;
  sdfBinary *v9;
  effPolygonFlash_Basic_t *v10;

  v7 = HandleCreate(type, pParams);
  v8 = effPolygonFlashTypeTable[type];
  v9 = Allocate(sdfBinary);
  _ctor_36176832(v9, pParams, 0);
  v10 = (v8->invoke_impl)(v8->method_code, v9, pTex, &v7->pParams, v8->method);
  v7->pHandle = v10;
  (v7->pHandle->klass->vtable._7_Init.methodPtr)(v7->pHandle, v7, v7->pHandle->klass->vtable._7_Init.method);
  return v7;
}

// 0x1987de0
pflashHandle_t *PartsCreate(Standard *pParts) {
  s64 naturalAligment;
  void *pData;
  s64 v7;
  void *v8;
  Standard *klass;
  s64 v12;
  u8 *v13;
  u16 type;
  s64 v16;

  if (!pParts)
    goto LABEL_11;
  if (pParts->klass->_2.naturalAligment >= (u32)naturalAligment && (Standard *)pParts->klass->_2.typeHierarchy[naturalAligment - 1] == Standard)
  {
    pData = pParts->data->pData;
    if (pParts->data->type == 1)
      goto LABEL_12;
LABEL_18:
    v8 = 0;
LABEL_19:
    klass = pParts->klass;
    if (pParts->klass->_2.naturalAligment < (u32)v12)
      goto LABEL_25;
    goto LABEL_24;
  }
LABEL_11:
  pData = 0;
  if (pParts->data->type != 1)
    goto LABEL_18;
LABEL_12:
  if (pData)
  {
    if (pData->klass->_2.naturalAligment < (u32)v7 || pData->klass->_2.typeHierarchy[v7 - 1] != Project_libsdf_sdfResourceUnit_Texture)
    {
      goto LABEL_33;
    }
  }
  v8 = pData[1].klass;
  goto LABEL_19;
  if (pParts->klass->_2.naturalAligment < (u32)v12)
  {
LABEL_25:
    v13 = 0;
    goto LABEL_26;
  }
LABEL_24:
  if (klass->_2.typeHierarchy[v12 - 1] != Project_effParts_t_Resource_Common)
    goto LABEL_25;
  pData = pParts->param->pData;
  if (pData)
  {
    if (pData->klass->_2.naturalAligment < (u32)v16 || pData->klass->_2.typeHierarchy[v16 - 1] != Project_effPartsData_t_Default)
    {
LABEL_33:
    }
  }
  v13 = pData[1].klass;
LABEL_26:
  type = pParts->param->type;
  return Create(type, v13, v8);
}

// 0x1988070
void Delete(effPartsHandle_t *handle) {
  (handle[3].option->klass[1]._1.generic_class)(handle[3].option, handle[3].option->klass[1]._1.typeMetadataHandle);
}

// 0x1988100
pflashHandle_t *Copy(effPartsHandle_t *handle) {
  u32 monitor;
  pflashHandle_t *v5;
  effPartsHandle_t *klass;
  pflashHandle_t *v7;
  effPolygonFlash_Basic_t *v8;

  monitor = handle[3].monitor;
  v5 = HandleCreate(monitor);
  klass = handle[4].klass;
  v7 = v5;
  v5->pParams = (effPolygonFlash_Params_Basic_t *)klass;
  v8 = (handle[3].option->klass[1]._1.declaringType)(handle[3].option, handle, handle[3].option->klass[1]._1.parent);
  v7->pHandle = v8;
  (v7->pHandle->klass->vtable._7_Init.methodPtr)(v7->pHandle, v7, v7->pHandle->klass->vtable._7_Init.method);
  return v7;
}

// 0x19882a0
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
  (handle[3].option->klass[1]._2.unity_user_data)(handle[3].option, handle, *(u64 *)&handle[3].option->klass[1]._2.initializationExceptionGCHandle);
  return;
}

// 0x1988410
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

// 0x19884c0
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

// 0x1988570
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

// 0x1988620
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].monitor = scale;
}

// 0x19886b0
void Init(void) {
  effPolygonFlashInit();
}
