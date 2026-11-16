#pragma once
#include "types.h"

typedef struct effPolygonWind_Sphere_t_Parts_t effPolygonWind_Sphere_t_Parts_t;

struct effPolygonWind_Sphere_t_Parts_t {
    s32 frame;
    sdfVector4_t abgr;
    f32 radius;
    f32 radius_s;
    f32 rotate;
    f32 radian;
    f32 width;
    f32 length;
    f32 v;
    f32 rot[2];
};
