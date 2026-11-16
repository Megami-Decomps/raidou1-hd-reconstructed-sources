#pragma once
#include "types.h"

typedef enum {
    EFFBF_XY_NORMAL = 0,
    EFFBF_XY_I4 = 1,
} EFFBF_XY;

extern f32 EFF_BLURVAL;

f32 effBlurGetBlurValid(void);
void effBlurSetBlurValid(f32 val);
