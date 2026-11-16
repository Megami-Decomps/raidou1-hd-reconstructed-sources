#pragma once
#include "types.h"

typedef struct tipsUI_PANELTITLE tipsUI_PANELTITLE;
typedef struct tipsUI_TextSet tipsUI_TextSet;

struct tipsUI_PANELTITLE {
    tipsUI_TextSet *text;
    void *stxt;
};
