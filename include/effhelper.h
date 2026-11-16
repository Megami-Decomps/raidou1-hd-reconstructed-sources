#pragma once
#include "types.h"

typedef struct Standard Standard;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effHelper_Params_t effHelper_Params_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct ehlpHandle_t ehlpHandle_t;
typedef struct plistHandle_t plistHandle_t;

struct effHelper_Params_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    f32 speed;
};

struct ehlpHandle_t {
    effOption *option;
    u32 number;
    s32 frame;
    effHelper_Params_t *pParams;
    plistHandle_t *phPartsList;
    dds3ModelHandle_t *hModel;
};

ehlpHandle_t *Create(Standard *pParts);
void Delete(effPartsHandle_t *handle);
ehlpHandle_t *Copy(effPartsHandle_t *handle);
void effResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src);
void Draw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
