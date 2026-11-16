#pragma once
#include "types.h"

typedef enum {
    EFFPOLYGON_CRACK_TYPE_NON = 0,
    EFFPOLYGON_CRACK_TYPE_NORMAL = 1,
    EFFPOLYGON_CRACK_TYPE_MAX = 2,
} EFFPOLYGON_CRACK_TYPE;

typedef struct MeshEditPC MeshEditPC;
typedef struct Standard Standard;
typedef struct crackHandle_t crackHandle_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonCrackMesh effPolygonCrackMesh;
typedef struct effPolygonCrackMesh_VertexJob effPolygonCrackMesh_VertexJob;
typedef struct effPolygonCrack_Basic_t effPolygonCrack_Basic_t;
typedef struct effPolygonCrack_Params_Basic_t effPolygonCrack_Params_Basic_t;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;
typedef struct splistHandle_t splistHandle_t;

struct crackHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    EFFPOLYGON_CRACK_TYPE type;
    dds3ModelHandle_t *hHelper;
    effPolygonCrack_Basic_t *pHandle;
    effPolygonCrack_Params_Basic_t *pParams;
};

struct effPolygonCrack_Basic_t {
    void *pParts;
    splistHandle_t *hPList;
    effPolygonCrackMesh *pMesh;
};

struct effPolygonCrackMesh_VertexJob {
    void *vertex;
    void *position;
    s32 sideSize;
    sdfColor32_t abgr0_2;
    sdfColor32_t abgr1;
    f32 width;
    f32 rate_s;
    s32 frame;
};

struct effPolygonCrackMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPC *edit;
    s32 count;
    s32 frame;
    effPolygonCrackMesh_VertexJob vertexJob;
    sdfMesh_IndexJob indexJob;
};

crackHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
crackHandle_t *Copy(effPartsHandle_t *handle);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
