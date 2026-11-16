#pragma once
#include "types.h"

typedef struct SBTLVISUAL_DATA SBTLVISUAL_DATA;

struct SBTLVISUAL_DATA {
    sdfVector4_t center;
    sdfVector4_t rot;
    f32 hit_area_r;
    f32 width;
    f32 height;
    f32 e_width;
    f32 e_height;
    s16 dummy1;
    s16 dummy2;
};
