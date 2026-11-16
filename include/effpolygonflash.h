#pragma once
#include "types.h"

typedef enum {
    EFFPOLYGON_FLASH_TYPE_NON = 0,
    EFFPOLYGON_FLASH_TYPE_RADIATE = 1,
    EFFPOLYGON_FLASH_TYPE_SPARK = 2,
    EFFPOLYGON_FLASH_TYPE_CYLINDER = 3,
    EFFPOLYGON_FLASH_TYPE_RADIATE_TEX = 4,
    EFFPOLYGON_FLASH_TYPE_SPARK_TEX = 5,
    EFFPOLYGON_FLASH_TYPE_RING_TEX = 6,
    EFFPOLYGON_FLASH_TYPE_RING = 7,
    EFFPOLYGON_FLASH_TYPE_SCATTER_TEX = 8,
    EFFPOLYGON_FLASH_TYPE_MAX = 9,
} EFFPOLYGON_FLASH_TYPE;

typedef struct Standard Standard;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonFlash_Basic_t effPolygonFlash_Basic_t;
typedef struct effPolygonFlash_Basic_t_Parts_Basic_t effPolygonFlash_Basic_t_Parts_Basic_t;
typedef struct effPolygonFlash_Params_Basic_t effPolygonFlash_Params_Basic_t;
typedef struct fplistHandle_t fplistHandle_t;
typedef struct pflashHandle_t pflashHandle_t;

struct pflashHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    EFFPOLYGON_FLASH_TYPE type;
    effPolygonFlash_Basic_t *pHandle;
    effPolygonFlash_Params_Basic_t *pParams;
};

struct effPolygonFlash_Params_Basic_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    u32 number;
    effBehavior_AlphaParams_t *alpha_p;
    u32 life_p;
    u32 refresh;
    bool loop;
    bool random;
    bool zTest;
    bool converge;
};

struct effPolygonFlash_Basic_t_Parts_Basic_t {
    s32 frame;
};

struct effPolygonFlash_Basic_t {
    effPolygonFlash_Basic_t_Parts_Basic_t *pParts;
    fplistHandle_t *hPList;
};

pflashHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
pflashHandle_t *Copy(effPartsHandle_t *handle);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
void Init(void);
