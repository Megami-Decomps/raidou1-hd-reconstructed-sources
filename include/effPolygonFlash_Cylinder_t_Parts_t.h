#pragma once
#include "types.h"

typedef struct effPolygonFlash_Cylinder_t_Parts_t effPolygonFlash_Cylinder_t_Parts_t;

struct effPolygonFlash_Cylinder_t_Parts_t {
    s32 frame;
    f32 speed;
    f32 rotate;
    f32 radian;
    f32 length[2];
    f32 radius;
    f32 radius_s;
    f32 width_in;
    f32 width_out[2];
};
