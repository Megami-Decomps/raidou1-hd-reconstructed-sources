#pragma once
#include "types.h"
#include "EFFPARTICLE_STATE.h"
#include "EFFPARTS_DATA.h"

#define MAX 300

typedef struct MeshJobD MeshJobD;
typedef struct Standard Standard;
typedef struct bhvrHandle_t bhvrHandle_t;
typedef struct ctexlHandle_t ctexlHandle_t;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effParts_t effParts_t;
typedef struct plistHandle_t plistHandle_t;
typedef struct ptcHandle_t ptcHandle_t;

struct ptcHandle_t {
    effOption *option;
    u32 number;
    sdfVector4_t abgr;
    f32 scale;
    EFFPARTS_DATA matType;
    dds3Billboard_Basic_t *hBillboard;
    effParts_t *phParts;
    plistHandle_t *phPartsList;
    ctexlHandle_t *hCTexList;
    MeshJobD *pMesh;
    bhvrHandle_t *hBehavior;
    EFFPARTICLE_STATE state;
};

ptcHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
ptcHandle_t *Copy(effPartsHandle_t *handle);
void ResourceCopy(effPartsHandle_t *dstHandle, effPartsHandle_t *srcHandle);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
