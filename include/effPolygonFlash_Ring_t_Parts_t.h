#pragma once
#include "types.h"

typedef struct effPolygonFlash_Ring_t_Parts_t effPolygonFlash_Ring_t_Parts_t;

struct effPolygonFlash_Ring_t_Parts_t {
    s32 frame;
    f32 radian;
    f32 rotate;
    f32 length;
    f32 length_s;
    f32 radius;
    f32 radius_s;
    f32 spread;
    f32 spread_s;
    f32 width_in;
    f32 width_out;
};
