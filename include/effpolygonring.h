#pragma once
#include "types.h"

typedef enum {
    EFFPOLYGON_RING_TYPE_NON = 0,
    EFFPOLYGON_RING_TYPE_NORMAL = 1,
    EFFPOLYGON_RING_TYPE_TRACK = 2,
    EFFPOLYGON_RING_TYPE_CIRCLE = 3,
    EFFPOLYGON_RING_TYPE_MAX = 4,
} EFFPOLYGON_RING_TYPE;

typedef struct Standard Standard;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonRing_Basic_t effPolygonRing_Basic_t;
typedef struct effPolygonRing_Params_Basic_t effPolygonRing_Params_Basic_t;
typedef struct pringHandle_t pringHandle_t;
typedef struct rplistHandle_t rplistHandle_t;

struct pringHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    EFFPOLYGON_RING_TYPE type;
    effPolygonRing_Basic_t *pHandle;
    effPolygonRing_Params_Basic_t *pParams;
};

struct effPolygonRing_Basic_t {
    rplistHandle_t *hPList;
};

pringHandle_t *HandleCreate(EFFPOLYGON_RING_TYPE type);
pringHandle_t *Create(u16 type, u8 *pParams);
pringHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
pringHandle_t *Copy(effPartsHandle_t *handle);
void Calc(pringHandle_t *hPolygon);
void Draw(pringHandle_t *hPolygon);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
