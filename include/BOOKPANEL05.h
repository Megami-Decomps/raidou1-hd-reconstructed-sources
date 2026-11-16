#pragma once
#include "types.h"

typedef struct BOOKPANEL05 BOOKPANEL05;
typedef struct DitectiveBookUI_ARROW DitectiveBookUI_ARROW;
typedef struct DitectiveBookUI_IMGSet DitectiveBookUI_IMGSet;

struct BOOKPANEL05 {
    DitectiveBookUI_IMGSet *imgData;
    DitectiveBookUI_ARROW *arrow_l;
    DitectiveBookUI_ARROW *arrow_r;
};
