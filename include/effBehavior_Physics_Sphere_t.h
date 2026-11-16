#pragma once
#include "types.h"

typedef struct effBehavior_Physics_Sphere_t effBehavior_Physics_Sphere_t;

struct effBehavior_Physics_Sphere_t {
    f32 b_scale_r;
    f32 b_rotate;
    f32 b_rotate_r;
    sdfVector4_t pos;
    f32 rot[2];
    f32 radius;
    f32 radius_s;
    f32 rotate;
    f32 radian;
    f32 height;
};
