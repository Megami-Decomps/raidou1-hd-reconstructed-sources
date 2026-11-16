#pragma once
#include "types.h"

typedef struct CHARAICONCLASS CHARAICONCLASS;
typedef struct RankBar RankBar;
typedef struct Ranking Ranking;
typedef struct mjnUI_TextSet mjnUI_TextSet;

struct RankBar {
    mjnUI_TextSet *name;
    mjnUI_TextSet *num_l;
    mjnUI_TextSet *num_m;
    mjnUI_TextSet *num_r;
    CHARAICONCLASS *icon;
};

struct Ranking {
    mjnUI_TextSet *title;
    RankBar *ranking[4];
};
