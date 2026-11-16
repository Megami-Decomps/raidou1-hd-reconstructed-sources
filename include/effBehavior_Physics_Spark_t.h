#pragma once
#include "types.h"

typedef struct effBehavior_Physics_Spark_t effBehavior_Physics_Spark_t;

struct effBehavior_Physics_Spark_t {
    f32 b_scale_r;
    f32 b_rotate;
    f32 b_rotate_r;
    sdfVector4_t dir;
    f32 speed;
};
