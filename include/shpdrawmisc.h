#pragma once
#include "types.h"

typedef enum {
    BREAK_MAX = 128,
    PRT_DIFF_FRAME = 16,
} SHPDRAWMISC;

typedef struct sdfIVector2_t sdfIVector2_t;

void shpDrawBezierCurveWide(s32 a_x0, s32 a_y0, s32 a_x1, s32 a_y1, s32 a_xt, s32 a_yt, u32 a_z, s32 a_div, s32 a_num, u32 a_col, f32 a_w);
void shpDrawStraightLineWide(sdfIVector2_t *a_pPos, u32 a_z, s32 a_div, s32 a_top, s32 a_num, u32 a_col, s32 a_alphaType, f32 a_w);
void shpDrawParticleDiffusion(s32 a_x, s32 a_y, u32 a_z, u32 a_col, f32 a_w, s32 a_cnt);
void shpDrawStraightBreakLineWide(sdfIVector2_t *a_pPos, u32 a_z, s32 a_div, s32 a_top, s32 a_num, u32 a_col, f32 a_w);
