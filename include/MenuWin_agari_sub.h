#pragma once
#include "types.h"

typedef struct BarTextSet BarTextSet;
typedef struct MenuWin_agari_sub MenuWin_agari_sub;
typedef struct RANKOBJPARENT RANKOBJPARENT;
typedef struct SPRITEICONCLASS SPRITEICONCLASS;
typedef struct mjnUI_TextSet mjnUI_TextSet;

struct MenuWin_agari_sub {
    mjnUI_TextSet *name;
    BarTextSet *possP;
    BarTextSet *fluctuationP;
    BarTextSet *resultP;
    SPRITEICONCLASS *icon;
    RANKOBJPARENT *rank;
    s32 devilID;
    char *devilName;
};
