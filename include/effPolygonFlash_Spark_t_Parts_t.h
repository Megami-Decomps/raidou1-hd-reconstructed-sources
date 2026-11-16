#pragma once
#include "types.h"

typedef struct effPolygonFlash_Spark_t_Parts_t effPolygonFlash_Spark_t_Parts_t;

struct effPolygonFlash_Spark_t_Parts_t {
    s32 frame;
    f32 speed;
    f32 radian;
    f32 radius[2];
    f32 radius_s;
    f32 width_in;
};
