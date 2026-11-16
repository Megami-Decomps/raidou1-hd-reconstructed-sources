#pragma once
#include "types.h"

typedef struct effBehavior_Physics_Spiral_t effBehavior_Physics_Spiral_t;

struct effBehavior_Physics_Spiral_t {
    f32 b_scale_r;
    f32 b_rotate;
    f32 b_rotate_r;
    sdfVector4_t pos;
    sdfVector4_t q;
    f32 height;
    f32 radius;
    f32 radius_s;
    f32 radian;
    f32 rotate;
    f32 up;
};
