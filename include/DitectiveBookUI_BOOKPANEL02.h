#pragma once
#include "types.h"

typedef struct DitectiveBookUI_ARROW DitectiveBookUI_ARROW;
typedef struct DitectiveBookUI_BOOKPANEL02 DitectiveBookUI_BOOKPANEL02;
typedef struct DitectiveBookUI_ScrollText DitectiveBookUI_ScrollText;

struct DitectiveBookUI_BOOKPANEL02 {
    DitectiveBookUI_ScrollText *message;
    DitectiveBookUI_ARROW *arrow_u;
    DitectiveBookUI_ARROW *arrow_d;
    DitectiveBookUI_ARROW *arrow_l;
    DitectiveBookUI_ARROW *arrow_r;
    s32 topLineNum;
    void *TDAM;
};
