#include "types.h"
#include "EFFPARTS_CTG.h"
#include "effoption.h"
#include "effparts.h"

#define EFFPARTS_VERSION 200

typedef struct Standard Standard;
typedef struct effPartsFuncTable_t effPartsFuncTable_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effParts_t effParts_t;

typedef effPartsHandle_t *(*effPartsHandle_t_CreateFunc)(Standard *param);
typedef void (*effPartsHandle_t_DrawFunc)(effPartsHandle_t *param);
typedef void (*effPartsHandle_t_DeleteFunc)(effPartsHandle_t *param);
typedef effPartsHandle_t *(*effPartsHandle_t_CopyFunc)(effPartsHandle_t *param);
typedef void (*ResetFunc)(effPartsHandle_t *param);
typedef void (*PositionFunc)(effPartsHandle_t *param, const sdfVector4_t *pos);
typedef void (*RotateFunc)(effPartsHandle_t *param, const sdfVector4_t *rot);
typedef void (*ScaleFunc)(effPartsHandle_t *param, f32 scale);
typedef void (*ColorFunc)(effPartsHandle_t *param, const sdfVector4_t *abgr);

struct effPartsFuncTable_t {
    effPartsHandle_t_CreateFunc Create;
    effPartsHandle_t_DrawFunc Draw;
    effPartsHandle_t_DeleteFunc Delete;
    effPartsHandle_t_CopyFunc Copy;
    ResetFunc Reset;
    PositionFunc Position;
    RotateFunc Rotate;
    ScaleFunc Scale;
    ColorFunc Color;
};

static effPartsFuncTable_t *defaultTable;
static effPartsFuncTable_t *effPartsFuncTable;

static effParts_t *New(EFFPARTS_CTG categ);
static effPartsHandle_t *DefaultCreate(Standard *pParts);
static void DefaultDelete(effPartsHandle_t *hPolygon);
static effPartsHandle_t *DefaultCopy(effPartsHandle_t *hPolygon);
static void DefaultReset(effPartsHandle_t *hPolygon);
static void DefaultDraw(effPartsHandle_t *hPolygon);
static void DefaultPosition(effPartsHandle_t *hPolygon, const sdfVector4_t *pPos);
static void DefaultRotate(effPartsHandle_t *hPolygon, const sdfVector4_t *pRot);
static void DefaultScale(effPartsHandle_t *hPolygon, f32 scale);
static void DefaultColor(effPartsHandle_t *hPolygon, const sdfVector4_t *abgr);

// 0x19812d0
static effParts_t *New(EFFPARTS_CTG categ) {
  effParts_t *v3;

  v3 = (effParts_t *)Allocate(effParts_t);
  _ctor(v3);
  v3->categ = categ;
  v3->version = 200;
  return v3;
}

// 0x197e880
u8 *effParamsGet(void *hParts) {
  s64 naturalAligment;
  u8 **namespaze;

  if (!hParts)
    return 0;
  if (hParts->klass->_2.naturalAligment < (u32)naturalAligment || hParts->klass->_2.typeHierarchy[naturalAligment - 1] != Project_effParts_t_Resource_Common)
  {
    return 0;
  }
  namespaze = hParts[1].klass->_1.namespaze;
  return namespaze[2];
}

// 0x197e9c0
void *effDataGet(void *hParts) {
  {
    return *(void *)(*(u64 *)&hParts[1].Project_libsdf_sdfResourceUnit_Fields + 24);
  }
  else
  {
    return 0;
  }
}

// 0x197fac0
effParts_t *Create(Standard *pData) {
  s64 categ;
  effParts_t *v5;
  effPartsData_t *param;
  effPartsData_t *data;
  effPartsHandle_t_CreateFunc Create;
  effPartsHandle_t *v10;
  effPartsHandle_t *pHandle;
  effOption *p_option;
  effOption *option;
  effOption_Resource *v15;
  effOption *v16;

  categ = pData->categ;
  v5 = (effParts_t *)Allocate(effParts_t);
  _ctor(v5);
  param = pData->param;
  v5->categ = categ;
  data = v5->data;
  v5->param->type = param->type;
  v5->version = 200;
  data->type = pData->data->type;
  Create = effPartsFuncTable[categ]->Create;
  v10 = (Create->invoke_impl)(Create->method_code, pData, Create->method);
  v5->pHandle = v10;
  pHandle = v5->pHandle;
  if (!pHandle)
    return v5;
  option = pHandle->option;
  p_option = &pHandle->option;
  if (option)
    return v5;
  v15 = pData->option;
  v16 = effGet(v15);
  p_option = v16;
  return v5;
}

// 0x19813e0
static effPartsHandle_t *DefaultCreate(Standard *pParts) {
  Il2CppObject *v2;

  v2 = Allocate(effPartsHandle_t);
  _ctor(v2, 0);
  return (effPartsHandle_t *)v2;
}

// 0x197f260
void Delete(effParts_t *hParts) {
  effPartsHandle_t *pHandle;
  effPartsHandle_t_DeleteFunc Delete;
  effPartsData_t *param;
  effPartsData_t *data;

  pHandle = hParts->pHandle;
  if (pHandle)
  {
    pHandle = hParts->pHandle;
    Delete = effPartsFuncTable[hParts->categ]->Delete;
    (Delete->invoke_impl)(Delete->method_code, pHandle, Delete->method);
  }
  param = hParts->param;
  if (!param)
    goto LABEL_10;
  goto LABEL_9;
  if (param)
  {
LABEL_9:
    param->pData = 0;
  }
LABEL_10:
  data = hParts->data;
  if (data)
  {
    data->pData = 0;
  }
}

// 0x1981480
static void DefaultDelete(effPartsHandle_t *hPolygon) {
  ;
}

// 0x1981440
void effParamsDelete(effParts_t *hParts) {
  effPartsData_t *param;

  param = hParts->param;
  if (param)
  {
    param->pData = 0;
  }
}

// 0x1981460
void effDataDelete(effParts_t *hParts) {
  effPartsData_t *data;

  data = hParts->data;
  if (data)
  {
    data->pData = 0;
  }
}

// 0x197f970
effParts_t *Copy(effParts_t *hCopyParts) {
  s64 categ;
  effParts_t *v5;
  effPartsHandle_t *pHandle;
  effPartsData_t *param;
  effPartsData_t *data;
  effPartsHandle_t_CopyFunc Copy;
  effPartsHandle_t *v11;
  effPartsHandle_t *v12;
  effOption *option;

  categ = hCopyParts->categ;
  v5 = (effParts_t *)Allocate(effParts_t);
  _ctor(v5);
  pHandle = hCopyParts->pHandle;
  param = hCopyParts->param;
  v5->categ = categ;
  data = v5->data;
  v5->param->type = param->type;
  data->type = hCopyParts->data->type;
  v5->version = 200;
  Copy = effPartsFuncTable[categ]->Copy;
  v11 = (Copy->invoke_impl)(Copy->method_code, pHandle, Copy->method);
  v5->pHandle = v11;
  v12 = v5->pHandle;
  if (v12)
  {
    option = hCopyParts->pHandle->option;
    v12->option = option;
  }
  return v5;
}

// 0x1981490
static effPartsHandle_t *DefaultCopy(effPartsHandle_t *hPolygon) {
  return hPolygon;
}

// 0x19814a0
static void DefaultReset(effPartsHandle_t *hPolygon) {
  ;
}

// 0x1981090
void Draw(effParts_t *hParts) {
  effPartsHandle_t_DrawFunc Draw;

  Draw = effPartsFuncTable[hParts->categ]->Draw;
  (Draw->invoke_impl)(Draw->method_code, hParts->pHandle, Draw->method);
}

// 0x19814b0
static void DefaultDraw(effPartsHandle_t *hPolygon) {
  ;
}

// 0x1980fd0
void PositionSet(effParts_t *hParts, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  PositionFunc Position;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  Position = effPartsFuncTable[hParts->categ]->Position;
  (Position->invoke_impl)(Position->method_code, hParts->pHandle, Position->x, y, z, w);
}

// 0x19814c0
static void DefaultPosition(effPartsHandle_t *hPolygon, const sdfVector4_t *pPos) {
  ;
}

// 0x19814d0
void RotateSet(effParts_t *hParts, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  RotateFunc Rotate;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  Rotate = effPartsFuncTable[hParts->categ]->Rotate;
  (Rotate->invoke_impl)(Rotate->method_code, hParts->pHandle, Rotate->x, y, z, w);
}

// 0x1981590
static void DefaultRotate(effPartsHandle_t *hPolygon, const sdfVector4_t *pRot) {
  ;
}

// 0x1980f30
void ScaleSet(effParts_t *hParts, f32 scale) {
  ScaleFunc v6;

  v6 = effPartsFuncTable[hParts->categ]->Scale;
  (v6->invoke_impl)(v6->method_code, hParts->pHandle, v6->scale);
}

// 0x19815a0
static void DefaultScale(effPartsHandle_t *hPolygon, f32 scale) {
  ;
}

// 0x1980e70
void ColorSet(effParts_t *hParts, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  ColorFunc Color;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  Color = effPartsFuncTable[hParts->categ]->Color;
  (Color->invoke_impl)(Color->method_code, hParts->pHandle, Color->x, y, z, w);
}

// 0x19815b0
static void DefaultColor(effPartsHandle_t *hPolygon, const sdfVector4_t *abgr) {
  ;
}
