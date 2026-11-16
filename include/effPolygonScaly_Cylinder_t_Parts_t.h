#pragma once
#include "types.h"

typedef struct effPolygonScaly_Cylinder_t_Parts_t effPolygonScaly_Cylinder_t_Parts_t;

struct effPolygonScaly_Cylinder_t_Parts_t {
    s32 frame;
    sdfVector4_t abgr;
    f32 radius;
    f32 radius_s;
    f32 speed;
    f32 height;
    f32 rotate;
    f32 radian;
    f32 width;
    f32 length;
    f32 u;
    f32 v;
};
