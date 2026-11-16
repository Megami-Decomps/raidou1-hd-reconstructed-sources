#pragma once
#include "types.h"

typedef struct effPolygonFlashMesh effPolygonFlashMesh;
typedef struct sdfMesh_IndexJob sdfMesh_IndexJob;

struct effPolygonFlashMesh {
    void *jobHandle;
    bool isAlive;
    void *mesh;
    sdfMesh_IndexJob indexJob;
    void *position;
    void *color;
};
