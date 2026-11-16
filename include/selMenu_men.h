#pragma once
#include "types.h"

typedef struct CHARAICONCLASS CHARAICONCLASS;
typedef struct RANKOBJPARENT RANKOBJPARENT;
typedef struct mjnUI_TextSet mjnUI_TextSet;
typedef struct selMenu_men selMenu_men;

struct selMenu_men {
    mjnUI_TextSet *name;
    RANKOBJPARENT *rank;
    CHARAICONCLASS *icon;
    s32 ID;
    s32 IDListNum;
};
