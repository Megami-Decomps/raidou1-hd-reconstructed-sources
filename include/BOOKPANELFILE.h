#pragma once
#include "types.h"

typedef struct BOOKPANELFILE BOOKPANELFILE;
typedef struct DitectiveBookUI_ARROW DitectiveBookUI_ARROW;
typedef struct DitectiveBookUI_ScrollText DitectiveBookUI_ScrollText;

struct BOOKPANELFILE {
    DitectiveBookUI_ScrollText *message;
    DitectiveBookUI_ARROW *arrow_u;
    DitectiveBookUI_ARROW *arrow_d;
    DitectiveBookUI_ARROW *arrow_l;
    DitectiveBookUI_ARROW *arrow_r;
    s32 topLineNum;
    void *TDAM;
};
