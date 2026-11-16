#pragma once
#include "types.h"

typedef struct SBTLDMG_ANIMWORK SBTLDMG_ANIMWORK;

struct SBTLDMG_ANIMWORK {
    sdfVector4_t pos;
    s16 ID;
    s16 st;
    u32 rgba;
    u32 rgba2;
    s32 counter;
    s32 counter_pos;
    s32 dmg;
    s32 dmg_anm;
    s32 dmg_anm_add;
    s32 rgbano;
    s16 time;
    s16 cmptime;
    f32 scale;
    s32 Atk_ListID;
    s32 Dmg_ListID;
    s32 side;
    s32 minor;
    s32 uniq_code;
    s32 type;
    s32 dispmode;
};
