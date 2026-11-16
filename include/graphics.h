#pragma once
#include "types.h"

typedef struct CommonMesh_MeshEditPCU_Form CommonMesh_MeshEditPCU_Form;
typedef struct CommonMesh_MeshEditPC_Form CommonMesh_MeshEditPC_Form;
typedef struct MeshEdit MeshEdit;
typedef struct MeshEditPC MeshEditPC;
typedef struct MeshEditPCU MeshEditPCU;
typedef struct Sub Sub;

struct Sub {
    s32 vertexPoint;
    s32 vertexCount;
    s32 indexPoint;
    s32 indexCount;
};

struct MeshEdit {
    void *body;
    void *dataArray;
    void *data;
    void *index;
    Sub *sub;
    void *bounds;
    s32 vertexCount;
    s32 indexCount;
};

struct CommonMesh_MeshEditPCU_Form {
    sdfVector3_t position;
    sdfColor32_t color;
    sdfVector2_t uv;
};

struct MeshEditPCU {
    void *body;
    void *dataArray;
    void *data;
    void *index;
    Sub *sub;
    void *bounds;
    s32 vertexCount;
    s32 indexCount;
    CommonMesh_MeshEditPCU_Form work;
    void *vertex;
    void *boundsJob;
    bool isWorking;
};

struct CommonMesh_MeshEditPC_Form {
    sdfVector3_t position;
    sdfColor32_t color;
};

struct MeshEditPC {
    void *body;
    void *dataArray;
    void *data;
    void *index;
    Sub *sub;
    void *bounds;
    s32 vertexCount;
    s32 indexCount;
    CommonMesh_MeshEditPC_Form work;
    void *vertex;
    void *boundsJob;
    bool isWorking;
};
