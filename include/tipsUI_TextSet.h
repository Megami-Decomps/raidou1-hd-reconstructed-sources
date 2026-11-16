#pragma once
#include "types.h"

typedef enum {
    tipsUI_Mode_NORMAL = 0,
    tipsUI_Mode_SELECT = 1,
    tipsUI_Mode_NON = 2,
} tipsUI_Mode;

typedef struct tipsUI_TextSet tipsUI_TextSet;

struct tipsUI_TextSet {
    void *TMProUGUI;
    tipsUI_Mode mode;
};
