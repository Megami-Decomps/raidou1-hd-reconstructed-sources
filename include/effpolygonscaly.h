#pragma once
#include "types.h"

typedef enum {
    EFFPOLYGON_SCALY_TYPE_NON = 0,
    EFFPOLYGON_SCALY_TYPE_CYLINDER = 1,
    EFFPOLYGON_SCALY_TYPE_P_SMOKE = 2,
    EFFPOLYGON_SCALY_TYPE_P_SPIRAL = 3,
    EFFPOLYGON_SCALY_TYPE_SPHERE = 4,
    EFFPOLYGON_SCALY_TYPE_MAX = 5,
} EFFPOLYGON_SCALY_TYPE;

typedef struct Standard Standard;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonScaly_Basic_t effPolygonScaly_Basic_t;
typedef struct effPolygonScaly_Basic_t_Parts_Basic_t effPolygonScaly_Basic_t_Parts_Basic_t;
typedef struct effPolygonScaly_Params_Basic_t effPolygonScaly_Params_Basic_t;
typedef struct pscalyHandle_t pscalyHandle_t;
typedef struct splistHandle_t splistHandle_t;

struct pscalyHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    EFFPOLYGON_SCALY_TYPE type;
    effPolygonScaly_Basic_t *pHandle;
    effPolygonScaly_Params_Basic_t *pParams;
};

struct effPolygonScaly_Params_Basic_t {
    u32 number;
};

struct effPolygonScaly_Basic_t_Parts_Basic_t {
    s32 frame;
};

struct effPolygonScaly_Basic_t {
    effPolygonScaly_Basic_t_Parts_Basic_t *pParts;
    splistHandle_t *hPList;
};

pscalyHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
pscalyHandle_t *Copy(effPartsHandle_t *handle);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
void Init(void);
