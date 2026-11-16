#pragma once
#include "types.h"

typedef struct tipsUI_BOOKPANEL02 tipsUI_BOOKPANEL02;
typedef struct tipsUI_ScrollText tipsUI_ScrollText;
typedef struct tipsUI_TextSet tipsUI_TextSet;

struct tipsUI_ScrollText {
    tipsUI_TextSet *messageText;
};

struct tipsUI_BOOKPANEL02 {
    tipsUI_ScrollText *message;
    s32 topLineNum;
};
