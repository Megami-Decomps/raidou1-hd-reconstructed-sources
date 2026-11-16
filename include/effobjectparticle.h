#pragma once
#include "types.h"
#include "EFFPARTICLE_STATE.h"
#include "EFFPARTS_DATA.h"

typedef enum {
    IGNORESTOP = 1,
} EFFOPRT_FLAG;

typedef struct Standard Standard;
typedef struct bhvrHandle_t bhvrHandle_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effObjectParticle_Parts_t effObjectParticle_Parts_t;
typedef struct effObjectParticles_Params_t effObjectParticles_Params_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct opcHandle_t opcHandle_t;
typedef struct plistHandle_t plistHandle_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;

struct effObjectParticles_Params_t {
    u8 random;
    sdfVector4_t axis;
    f32 rotate;
    f32 rotate_r;
    f32 rotate_a;
    bool scale_obj;
};

struct opcHandle_t {
    effOption *option;
    u32 number;
    sdfVector4_t abgr;
    f32 scale;
    EFFPARTS_DATA matType;
    effObjectParticles_Params_t *param;
    dds3ModelHandle_t *hModel;
    sdfModelRootNode_t *pEarlyModel;
    plistHandle_t *phPartsList;
    bhvrHandle_t *hBehavior;
    effObjectParticle_Parts_t *pParts;
    EFFPARTICLE_STATE state;
    EFFOPRT_FLAG flags;
};

struct effObjectParticle_Parts_t {
    sdfVector4_t axis;
    f32 rotate;
    f32 rotate_s;
};

opcHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
opcHandle_t *Copy(effPartsHandle_t *handle);
void ResourceCopy(effPartsHandle_t *dstHandle, effPartsHandle_t *srcHandle);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
