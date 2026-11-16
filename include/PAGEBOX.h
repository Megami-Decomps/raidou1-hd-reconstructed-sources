#pragma once
#include "types.h"

typedef struct PAGEBOX PAGEBOX;
typedef struct tipsUI_TextSet tipsUI_TextSet;

struct PAGEBOX {
    tipsUI_TextSet *MaxPage;
    tipsUI_TextSet *NowPage;
};
