#pragma once
#include "types.h"

typedef struct CHARAICONCLASS CHARAICONCLASS;
typedef struct RANKOBJPARENT RANKOBJPARENT;
typedef struct Win_men Win_men;
typedef struct Win_men_bar Win_men_bar;
typedef struct mjnUI_TextSet mjnUI_TextSet;

struct Win_men {
    mjnUI_TextSet *title;
    mjnUI_TextSet *raido;
    Win_men_bar *NarumiOrNakama;
    Win_men_bar *nakama01;
    Win_men_bar *nakama02;
};

struct Win_men_bar {
    CHARAICONCLASS *icon;
    mjnUI_TextSet *text;
    RANKOBJPARENT *rank;
};
