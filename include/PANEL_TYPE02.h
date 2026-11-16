#pragma once
#include "types.h"

typedef struct PANEL_TYPE02 PANEL_TYPE02;
typedef struct RAWIMGSet RAWIMGSet;
typedef struct tipsUI_IMGSet tipsUI_IMGSet;
typedef struct tipsUI_TextSet tipsUI_TextSet;

struct PANEL_TYPE02 {
    tipsUI_TextSet *message;
    tipsUI_IMGSet *image;
    RAWIMGSet *rawimage;
    s32 topLineNum;
    void *TDAM;
};
