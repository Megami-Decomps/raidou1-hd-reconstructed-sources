#pragma once
#include "types.h"

typedef struct MeshEditPC MeshEditPC;
typedef struct effPolygonCrackMeshF effPolygonCrackMeshF;
typedef struct effPolygonCrackMeshF_VertexJob effPolygonCrackMeshF_VertexJob;
typedef struct effPolygonCrack_Normal_t_Parts_t effPolygonCrack_Normal_t_Parts_t;
typedef struct effPolygonCrack_Parts_Flash_t effPolygonCrack_Parts_Flash_t;
typedef struct fplistHandle_t fplistHandle_t;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;

struct effPolygonCrack_Parts_Flash_t {
    f32 width_r;
    f32 length;
    u32 frame;
};

struct effPolygonCrack_Normal_t_Parts_t {
    effPolygonCrack_Parts_Flash_t *pFlash;
    effPolygonCrackMeshF *pFlashMesh;
    fplistHandle_t *hFlashPList;
    s32 point;
    void *pVertex;
};

struct effPolygonCrackMeshF_VertexJob {
    void *vertex;
    void *offset;
    void *source;
    void *position;
    void *abgr_base;
    s32 interval;
    f32 length;
    f32 length_f;
    sdfVector4_t abgr_in;
    sdfVector4_t abgr_out;
    f32 w_in;
    f32 w_out;
    f32 w_r;
    f32 rotate;
    f32 rotate_a_h;
};

struct effPolygonCrackMeshF {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    sdfMesh_IndexJob indexJob;
    void *position;
    void *color;
    MeshEditPC *edit;
    s32 count;
    effPolygonCrackMeshF_VertexJob vertexJob;
    void *source;
};
