#pragma once
#include "types.h"

typedef struct PAGECHANGEGUIDE PAGECHANGEGUIDE;
typedef struct keyboardButton keyboardButton;
typedef struct tipsUI_IMGSet tipsUI_IMGSet;

struct PAGECHANGEGUIDE {
    tipsUI_IMGSet *img_stick;
    tipsUI_IMGSet *img_button;
    keyboardButton *keyBoardObj;
};
