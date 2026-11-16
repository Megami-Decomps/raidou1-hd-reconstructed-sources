#pragma once
#include "types.h"

typedef struct PANEL_TYPE01 PANEL_TYPE01;
typedef struct tipsUI_TextSet tipsUI_TextSet;

struct PANEL_TYPE01 {
    tipsUI_TextSet *message;
    s32 topLineNum;
    void *TDAM;
};
