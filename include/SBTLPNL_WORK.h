#pragma once
#include "types.h"

typedef struct SBTLPNL_WORK SBTLPNL_WORK;

struct SBTLPNL_WORK {
    s16 mode;
    s16 mode1;
    s32 alpha;
    s32 acounter;
    s32 counter;
    s32 x;
    s32 y;
    s32 ofs_x;
    s32 ofs_y;
    s32 sprno;
    f32 scaleX;
    f32 scaleY;
};
