#pragma once
#include "types.h"
#include "TNEFFECT_BLEND.h"

typedef struct MeshEditPCM MeshEditPCM;
typedef struct effPolygonScalyMesh effPolygonScalyMesh;
typedef struct effPolygonScalyMesh_VertexJob effPolygonScalyMesh_VertexJob;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;
typedef struct splistHandle_t splistHandle_t;

struct splistHandle_t {
    u32 number;
    TNEFFECT_BLEND blend;
    sdfVector4_t abgr;
    s32 point;
    s32 face;
    effPolygonScalyMesh *pMesh;
};

struct effPolygonScalyMesh_VertexJob {
    void *vertex;
    void *source;
    void *offset;
    s32 sideSize;
    s32 vertexSize;
    f32 base_u;
    f32 base_v;
};

struct effPolygonScalyMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPCM *edit;
    s32 count;
    effPolygonScalyMesh_VertexJob vertexJob;
    sdfMesh_IndexJob indexJob;
    void *source;
    void *offset;
    s32 vertexSize;
    s32 indexSize;
};
