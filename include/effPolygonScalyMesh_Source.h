#pragma once
#include "types.h"

typedef struct effPolygonScalyMesh_Source effPolygonScalyMesh_Source;

struct effPolygonScalyMesh_Source {
    sdfVector4_t abgr;
    f32 scale_uv;
    f32 rotate;
    f32 radius;
    sdfVector3_t width;
    f32 height;
    f32 length;
    f32 u;
    f32 v;
};
