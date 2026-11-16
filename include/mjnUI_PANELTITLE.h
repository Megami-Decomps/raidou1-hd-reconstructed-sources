#pragma once
#include "types.h"

typedef struct mjnUI_PANELTITLE mjnUI_PANELTITLE;
typedef struct mjnUI_TextSet mjnUI_TextSet;

struct mjnUI_PANELTITLE {
    mjnUI_TextSet *text;
    void *scrollCtrler;
};
