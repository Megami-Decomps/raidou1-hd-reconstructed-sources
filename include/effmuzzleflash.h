#pragma once
#include "types.h"

typedef struct Standard Standard;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct effMuzzleFlash_Params_t effMuzzleFlash_Params_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct mzfHandle_t mzfHandle_t;

struct effMuzzleFlash_Params_t {
    f32 scale_h;
    f32 scale_w;
};

struct mzfHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    effMuzzleFlash_Params_t *param;
    dds3Billboard_Basic_t *hBillboard;
};

mzfHandle_t *Create(Standard *pParts);
void Delete(effPartsHandle_t *handle);
mzfHandle_t *Copy(effPartsHandle_t *handle);
void ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src);
void Draw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
