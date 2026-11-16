#pragma once
#include "types.h"

typedef struct SBTLANIM_HOKAN SBTLANIM_HOKAN;

struct SBTLANIM_HOKAN {
    s32 type;
    f32 o_div;
    f32 o_val;
    f32 i_ttime;
    f32 i_rtime;
    f32 i_accele;
    f32 i_speed;
    f32 i_val;
};
