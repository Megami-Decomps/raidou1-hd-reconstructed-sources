#pragma once
#include "types.h"
#include "TNEFFECT_BLEND.h"

typedef struct MeshEditPCU MeshEditPCU;
typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct effPolygonWindMesh effPolygonWindMesh;
typedef struct effPolygonWindMesh_VertexJob effPolygonWindMesh_VertexJob;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;
typedef struct wplistHandle_t wplistHandle_t;

struct wplistHandle_t {
    u32 number;
    TNEFFECT_BLEND blend;
    sdfVector4_t abgr;
    s32 point;
    s32 face;
    bool zTest;
    effCtexHandle_t *hCacheTex;
    effPolygonWindMesh *pMesh;
};

struct effPolygonWindMesh_VertexJob {
    void *vertex;
    void *offset;
    void *source;
    void *sideSrc;
    void *alpha;
    s32 sideSize;
    s32 vertexSize;
    f32 u_add;
    f32 repeat_v;
};

struct effPolygonWindMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPCU *edit;
    s32 count;
    effPolygonWindMesh_VertexJob vertexJob;
    sdfMesh_IndexJob indexJob;
    void *source;
    void *sideSrc;
    void *offset;
    s32 sideSize;
    s32 vertexSize;
    s32 indexSize;
};
