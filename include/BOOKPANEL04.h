#pragma once
#include "types.h"

typedef struct BOOKPANEL04 BOOKPANEL04;
typedef struct DitectiveBookUI_ARROW DitectiveBookUI_ARROW;
typedef struct DitectiveBookUI_IMGSet DitectiveBookUI_IMGSet;
typedef struct DitectiveBookUI_RawIMGSet DitectiveBookUI_RawIMGSet;
typedef struct DitectiveBookUI_ScrollText DitectiveBookUI_ScrollText;

struct BOOKPANEL04 {
    DitectiveBookUI_ScrollText *message;
    DitectiveBookUI_IMGSet *imgData;
    DitectiveBookUI_RawIMGSet *R_imgData;
    DitectiveBookUI_ARROW *arrow_u;
    DitectiveBookUI_ARROW *arrow_d;
    DitectiveBookUI_ARROW *arrow_l;
    DitectiveBookUI_ARROW *arrow_r;
    s32 topLineNum;
    void *TDAM;
};
