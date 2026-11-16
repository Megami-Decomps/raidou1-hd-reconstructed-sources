#pragma once
#include "types.h"

typedef struct Standard Standard;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effModel_Params_t effModel_Params_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct emdlHandle_t emdlHandle_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;

struct effModel_Params_t {
    f32 scale;
};

struct emdlHandle_t {
    effOption *option;
    effModel_Params_t *param;
    dds3ModelHandle_t *handle;
    sdf3DLightParallelPacket_t *pLightPacket;
    u32 flag;
    u32 index_motion;
};

void Init(dds3ModelHandle_t *hModel);
dds3ModelHandle_t *effHandleCreate(void *pData);
void effHandleFree(dds3ModelHandle_t *hModel);
dds3ModelHandle_t *effHandleCopy(dds3ModelHandle_t *hSrc);
emdlHandle_t *Create(Standard *pParts);
void Delete(effPartsHandle_t *handle);
emdlHandle_t *Copy(effPartsHandle_t *handle);
void ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src);
void Draw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
emdlHandle_t *effCreate2(Standard *pParts);
emdlHandle_t *effCopy2(effPartsHandle_t *handle);
void effResourceCopy2(effPartsHandle_t *dst, effPartsHandle_t *src);
void effReset2(effPartsHandle_t *handle);
