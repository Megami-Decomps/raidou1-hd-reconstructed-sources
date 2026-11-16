#pragma once
#include "types.h"

typedef struct PAGEOBJCLASS PAGEOBJCLASS;
typedef struct TIPSPANEL TIPSPANEL;
typedef struct tipsUI_TextSet tipsUI_TextSet;

struct PAGEOBJCLASS {
    tipsUI_TextSet *num_max;
    tipsUI_TextSet *num_now;
};

struct TIPSPANEL {
    tipsUI_TextSet *titleText;
    PAGEOBJCLASS *page;
    void *stxt;
};
