#include "types.h"
#include "effmodel.h"
#include "effpolygoncrack.h"
#include "mdl.h"
#include "sdf_vu0.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct crackHandle_t crackHandle_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonCrack_Basic_t effPolygonCrack_Basic_t;
typedef struct effPolygonCrack_Params_Basic_t effPolygonCrack_Params_Basic_t;
typedef struct sdfBinary sdfBinary;

typedef effPolygonCrack_Basic_t *(*effPolygonCrack_CreateFunc)(sdfBinary *binParams, dds3ModelHandle_t *hHelper, effPolygonCrack_Params_Basic_t *refParams);

static effPolygonCrack_CreateFunc *effPolygonCrackTypeTable[2];

static crackHandle_t *Create(u16 type, u8 *pParams, void *pPB);

// 0x19866a0
static crackHandle_t *Create(u16 type, u8 *pParams, void *pPB) {
  crackHandle_t *v7;
  sdfVector4_t *v11;
  sdfVector4_t *v12;
  sdfVector4_t *p_vf00;
  dds3ModelHandle_t *v16;
  effPolygonCrack_CreateFunc v18;
  sdfBinary *v19;
  void *v20;

  v7 = Allocate(crackHandle_t);
  v7->frame = 0;
  v7->type = type;
  *(u32 *)&v7->scale = 1065353216;
  v7->abgr = oneVector;
  v11 = &v7->pos;
  goto LABEL_8;
LABEL_14:
  p_vf00 = &vf00;
  *v12 = *p_vf00;
  goto LABEL_15;
LABEL_8:
  *v11 = vf00;
  v12 = &v7->rot;
  goto LABEL_14;
LABEL_15:
  if (!op_Inequality(pPB, 0, 0))
    return v7;
  v16 = effHandleCreate(pPB);
  v7->hHelper = v16;
  v18 = effPolygonCrackTypeTable[type];
  v19 = Allocate(sdfBinary);
  _ctor_36176832(v19, pParams, 0);
  v20 = (v18->invoke_impl)(v18->method_code, v19, v7->hHelper, &v7->pParams, v18->method);
  v7->pHandle = v20;
  (*(*(u64 *)v7->pHandle + 408))((u64)v7->pHandle, v7, *(u64 *)(*(u64 *)v7->pHandle + 416));
  return v7;
}

// 0x19869a0
crackHandle_t *PartsCreate(Standard *pParts) {
  s64 naturalAligment;
  u8 *klass;
  void *pData;
  void *v8;
  s64 v9;
  u16 type;
  s64 v12;

  if (!pParts)
    goto LABEL_11;
  if (pParts->klass->_2.naturalAligment >= (u32)naturalAligment && (Project_effParts_t_Resource_Common_c *)pParts->klass->_2.typeHierarchy[naturalAligment - 1] == Project_effParts_t_Resource_Common)
  {
    pData = pParts->param->pData;
    if (pData)
    {
      if (pData->klass->_2.naturalAligment < (u32)v12 || pData->klass->_2.typeHierarchy[v12 - 1] != Project_effPartsData_t_Default)
      {
LABEL_24:
      }
    }
    klass = pData[1].klass;
    goto LABEL_13;
  }
LABEL_11:
  klass = 0;
LABEL_13:
  pData = (pParts->data->pData->klass->vtable._4_GetExtResource.methodPtr)(pParts->data->pData, pParts->data->pData->klass->vtable._4_GetExtResource.method);
  v8 = pData;
  if (pData)
  {
    if (pData->klass->_2.naturalAligment < (u32)v9 || pData->klass->_2.typeHierarchy[v9 - 1] != Project_libsdf_sdfResource)
    {
      goto LABEL_24;
    }
  }
  type = pParts->param->type;
  return Create(type, klass, v8);
}

// 0x1986ba0
void Delete(effPartsHandle_t *handle) {
  (*(handle[4].klass->_1.image + 55))(handle[4].klass, *((u64 *)handle[4].klass->_1.image + 56));
  effHandleFree(handle[3].option);
}

// 0x1986c40
crackHandle_t *Copy(effPartsHandle_t *handle) {
  s32 monitor;
  crackHandle_t *v6;
  effOption *option;
  u16 MajorNum;
  s32 MinorNum;
  dds3ModelHandle_t *v10;
  effPolygonCrack_Params_Basic_t *v11;
  effPolygonCrack_CreateFunc v12;
  effPolygonCrack_Basic_t *v13;

  monitor = handle[3].monitor;
  v6 = Create(monitor, 0, 0);
  option = handle[3].option;
  MajorNum = mdlGetMajorNum(option);
  MinorNum = mdlGetMinorNum(handle[3].option);
  v10 = mdlLoad(MajorNum, MinorNum);
  v6->hHelper = v10;
  Init(v6->hHelper, 0);
  v11 = handle[4].monitor;
  v6->pParams = v11;
  v12 = effPolygonCrackTypeTable[v6->type];
  v13 = (v12->invoke_impl)(v12->method_code, 0, v6->hHelper, &v6->pParams, v12->method);
  v6->pHandle = v13;
  (v6->pHandle->klass->vtable._6_Init.methodPtr)(v6->pHandle, v6, v6->pHandle->klass->vtable._6_Init.method);
  return v6;
}

// 0x1986e90
void CalcAndDraw(effPartsHandle_t *handle) {
  if (get_STOP(0) && HIDWORD(handle[3].klass))
  {
    goto LABEL_9;
  }
  else
  {
    (*(handle[4].klass->_1.image + 57))(handle[4].klass, handle, *((u64 *)handle[4].klass->_1.image + 58));
    ++HIDWORD(handle[3].klass);
LABEL_9:
    goto LABEL_10;
  }
LABEL_10:
  if (drawSkip)
    return;
  (*(handle[4].klass->_1.image + 59))(handle[4].klass, handle, *((u64 *)handle[4].klass->_1.image + 60));
  return;
}

// 0x1987000
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

// 0x19870b0
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

// 0x1987160
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

// 0x1987210
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].monitor = scale;
}
