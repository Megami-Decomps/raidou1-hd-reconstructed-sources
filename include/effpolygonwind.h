#pragma once
#include "types.h"

typedef enum {
    EFFPOLYGON_WIND_TYPE_NON = 0,
    EFFPOLYGON_WIND_TYPE_SPIRAL = 1,
    EFFPOLYGON_WIND_TYPE_CYLINDER = 2,
    EFFPOLYGON_WIND_TYPE_SPHERE = 3,
    EFFPOLYGON_WIND_TYPE_XxCYLINDER_REV = 4,
    EFFPOLYGON_WIND_TYPE_MAX = 5,
} EFFPOLYGON_WIND_TYPE;

typedef struct Standard Standard;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonWind_Basic_t effPolygonWind_Basic_t;
typedef struct effPolygonWind_Basic_t_Parts_Basic_t effPolygonWind_Basic_t_Parts_Basic_t;
typedef struct effPolygonWind_Params_Basic_t effPolygonWind_Params_Basic_t;
typedef struct pwindHandle_t pwindHandle_t;
typedef struct wplistHandle_t wplistHandle_t;

struct pwindHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    EFFPOLYGON_WIND_TYPE type;
    effPolygonWind_Basic_t *pHandle;
    effPolygonWind_Params_Basic_t *pParams;
};

struct effPolygonWind_Basic_t_Parts_Basic_t {
    s32 frame;
    sdfVector4_t abgr;
    f32 radius;
    f32 radius_s;
    f32 rotate;
    f32 radian;
    f32 width;
    f32 length;
    f32 v;
};

struct effPolygonWind_Basic_t {
    effPolygonWind_Basic_t_Parts_Basic_t *pParts;
    wplistHandle_t *hPList;
};

pwindHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
pwindHandle_t *Copy(effPartsHandle_t *handle);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
void Init(void);
