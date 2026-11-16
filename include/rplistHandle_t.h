#pragma once
#include "types.h"
#include "TNEFFECT_BLEND.h"

typedef struct MeshEditPC MeshEditPC;
typedef struct effPolygonRingMesh effPolygonRingMesh;
typedef struct effPolygonRingMesh_VertexJob effPolygonRingMesh_VertexJob;
typedef struct rplistHandle_t rplistHandle_t;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;

struct rplistHandle_t {
    TNEFFECT_BLEND blend;
    sdfVector4_t abgr;
    s32 point;
    bool zTest;
    effPolygonRingMesh *pMesh;
};

struct effPolygonRingMesh_VertexJob {
    void *vertex;
    void *position;
    void *radius;
    sdfColor32_t abgr0;
    sdfColor32_t abgr1_2;
    sdfColor32_t abgr3;
};

struct effPolygonRingMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    MeshEditPC *edit;
    effPolygonRingMesh_VertexJob vertexJob;
    sdfMesh_IndexJob indexJob;
    void *position;
    void *radius;
};
