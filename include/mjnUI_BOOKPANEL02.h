#pragma once
#include "types.h"

typedef struct ScrollText_New ScrollText_New;
typedef struct mjnUI_BOOKPANEL02 mjnUI_BOOKPANEL02;
typedef struct mjnUI_TextSet mjnUI_TextSet;

struct ScrollText_New {
    mjnUI_TextSet *messageText;
};

struct mjnUI_BOOKPANEL02 {
    ScrollText_New *message;
    s32 topLineNum;
};
