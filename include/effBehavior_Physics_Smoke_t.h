#pragma once
#include "types.h"

typedef struct effBehavior_Physics_Smoke_t effBehavior_Physics_Smoke_t;

struct effBehavior_Physics_Smoke_t {
    f32 b_scale_r;
    f32 b_rotate;
    f32 b_rotate_r;
    sdfVector4_t up;
    sdfVector4_t dir;
    f32 radian;
    f32 old_sin;
    f32 amplitude;
    f32 amplitude_s;
    f32 amplitude_p;
    f32 speed;
};
