#pragma once
#include "types.h"
#include "EFFPARTS_DATA.h"

typedef struct MeshEditPC MeshEditPC;
typedef struct Param Param;
typedef struct Standard Standard;
typedef struct bhvrHandle_t bhvrHandle_t;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonTrackMesh effPolygonTrackMesh;
typedef struct effPolygonTrackMesh_IndexJob effPolygonTrackMesh_IndexJob;
typedef struct effPolygonTrackMesh_VertexJob effPolygonTrackMesh_VertexJob;
typedef struct effPolygonTrack_Params_t effPolygonTrack_Params_t;
typedef struct effPolygonTrack_VCParams_t effPolygonTrack_VCParams_t;
typedef struct poltHandle_t poltHandle_t;
typedef struct ptbzHandle_t ptbzHandle_t;

struct Param {
    sdfVector4_t _in;
    sdfVector4_t _out;
};

struct effPolygonTrack_VCParams_t {
    Param *start;
    Param *end;
};

struct effPolygonTrack_Params_t {
    u32 length;
    u32 split;
    effPolygonTrack_VCParams_t *vc;
    f32 scale_base;
};

struct poltHandle_t {
    effOption *option;
    u32 number;
    sdfVector4_t abgr;
    f32 scale;
    EFFPARTS_DATA matType;
    effPolygonTrack_Params_t *param;
    ptbzHandle_t *phPolyList;
    dds3Billboard_Basic_t *hBillboard;
    bhvrHandle_t *hBehavior;
    effPolygonTrackMesh *pMesh;
};

struct ptbzHandle_t {
    sdfVector3_t top;
    s32 point;
    s32 count;
    s32 current;
    s32 split;
    void *pVertex;
};

struct effPolygonTrackMesh_VertexJob {
    void *vertex;
    void *source;
    void *position;
    sdfVector4_t abgr;
};

struct effPolygonTrackMesh_IndexJob {
    void *index;
    void *source;
    void *table;
    void *head;
    s32 size;
};

struct effPolygonTrackMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPC *edit;
    s32 count;
    effPolygonTrackMesh_VertexJob vertexJob;
    effPolygonTrackMesh_IndexJob indexJob;
    void *source;
    void *position;
};

extern void *bztpFaceIndex;

poltHandle_t *PartsCreate(Standard *pParts);
poltHandle_t *effSPartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
poltHandle_t *Copy(effPartsHandle_t *handle);
poltHandle_t *effSCopy(effPartsHandle_t *handle);
void CalcAndDraw(effPartsHandle_t *handle);
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos);
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot);
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr);
void ScaleSet(effPartsHandle_t *handle, f32 scale);
