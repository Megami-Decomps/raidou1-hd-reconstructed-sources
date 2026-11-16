#pragma once
#include "types.h"

typedef struct effPolygonThunderMesh_SideSrc effPolygonThunderMesh_SideSrc;

struct effPolygonThunderMesh_SideSrc {
    sdfVector3_t dir;
    f32 length;
    f32 alpha_e;
    f32 alpha_b;
    f32 alpha_c;
};
