#pragma once
#include "types.h"
#include "mjnUI_Mode.h"

typedef struct PANEL PANEL;
typedef struct PANELTextSet PANELTextSet;
typedef struct mjnUI_ARROW mjnUI_ARROW;
typedef struct mjnUI_ARROW_IMAGE mjnUI_ARROW_IMAGE;
typedef struct mjnUI_ScrollText mjnUI_ScrollText;

struct mjnUI_ARROW {
    mjnUI_ARROW_IMAGE *img_arraw;
};

struct PANELTextSet {
    void *TMProUGUI;
    mjnUI_Mode mode;
};

struct mjnUI_ScrollText {
    PANELTextSet *messageText;
};

struct PANEL {
    mjnUI_ScrollText *message;
    mjnUI_ARROW *arrow_u;
    mjnUI_ARROW *arrow_d;
    mjnUI_ARROW *arrow_l;
    mjnUI_ARROW *arrow_r;
    s32 topLineNum;
    void *TDAM;
};
