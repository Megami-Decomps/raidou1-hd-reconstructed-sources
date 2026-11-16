#pragma once
#include "types.h"

typedef struct SDF_GS_ALPHA SDF_GS_ALPHA;
typedef struct Standard Standard;
typedef struct effBlurFilter_Params_Basic_t effBlurFilter_Params_Basic_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct efilterHandle_t efilterHandle_t;

struct efilterHandle_t {
    effOption *option;
    sdfVector4_t pos;
    SDF_GS_ALPHA *blend;
    sdfVector4_t abgr;
    f32 scale;
    s32 frame;
    void *pHandle;
    effBlurFilter_Params_Basic_t *pParams;
    u16 TexType;
};

efilterHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
efilterHandle_t *Copy(effPartsHandle_t *handle);
void Draw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
void effSetDirectColorMode(f32 _R, f32 _G, f32 _B, f32 _A);
void effClearDirectColorMode(void);
