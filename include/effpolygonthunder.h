#pragma once
#include "types.h"

typedef enum {
    EFFPOLYGON_THUNDER_TYPE_NON = 0,
    EFFPOLYGON_THUNDER_TYPE_POINT2 = 1,
    EFFPOLYGON_THUNDER_TYPE_XxRADIATE = 2,
    EFFPOLYGON_THUNDER_TYPE_BUG = 3,
    EFFPOLYGON_THUNDER_TYPE_MAX = 4,
} EFFPOLYGON_THUNDER_TYPE;

typedef struct MeshEditPC MeshEditPC;
typedef struct Standard Standard;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonThunderMesh effPolygonThunderMesh;
typedef struct effPolygonThunderMesh_VertexJob effPolygonThunderMesh_VertexJob;
typedef struct effPolygonThunder_Basic_t effPolygonThunder_Basic_t;
typedef struct effPolygonThunder_Basic_t_Parts_Basic_t effPolygonThunder_Basic_t_Parts_Basic_t;
typedef struct effPolygonThunder_Params_Basic_t effPolygonThunder_Params_Basic_t;
typedef struct ptndHandle_t ptndHandle_t;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;
typedef struct tplistHandle_t tplistHandle_t;

struct ptndHandle_t {
    effOption *option;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scale;
    sdfVector4_t abgr;
    s32 frame;
    EFFPOLYGON_THUNDER_TYPE type;
    effPolygonThunder_Basic_t *pHandle;
    effPolygonThunder_Params_Basic_t *pParams;
};

struct effPolygonThunder_Basic_t_Parts_Basic_t {
    tplistHandle_t *hPList;
    s32 frame;
    f32 alpha;
};

struct effPolygonThunder_Basic_t {
    effPolygonThunder_Basic_t_Parts_Basic_t *pParts;
    effPolygonThunderMesh *pMesh;
    f32 notch;
    f32 waveRand;
    f32 radian;
    f32 height;
    f32 length;
    sdfVector4_t look;
    sdfVector4_t dir;
    sdfVector4_t axis;
};

struct effPolygonThunderMesh_VertexJob {
    void *vertex;
    void *source;
    void *sideSrc;
    void *refAdd;
    void *offset;
    s32 sideSize;
    s32 vertexSize;
    sdfColor32_t abgr_e;
    sdfColor32_t abgr_b;
    sdfColor32_t abgr_c;
    f32 width_c;
    f32 width_e;
};

struct effPolygonThunderMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPC *edit;
    s32 count;
    effPolygonThunderMesh_VertexJob vertexJob;
    sdfMesh_IndexJob indexJob;
    void *source;
    void *sideSrc;
    void *refAdd;
    void *offset;
    s32 sideSize;
    s32 vertexSize;
    s32 indexSize;
};

ptndHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
ptndHandle_t *Copy(effPartsHandle_t *handle);
void Calc(ptndHandle_t *hPolygon);
void Draw(ptndHandle_t *hPolygon);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
