#pragma once
#include "types.h"

typedef struct tipsUI_MENU_BAR tipsUI_MENU_BAR;
typedef struct tipsUI_TextSet tipsUI_TextSet;

struct tipsUI_MENU_BAR {
    tipsUI_TextSet *messageParent;
    tipsUI_TextSet *messageChild;
    void *scrolltextParent;
    void *scrolltextChild;
};
