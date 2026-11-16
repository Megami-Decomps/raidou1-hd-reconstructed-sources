#pragma once
#include "types.h"

typedef struct sBtlMenuCharList_t sBtlMenuCharList_t;

struct sBtlMenuCharList_t {
    u32 pageFlag[4];
    s32 selectPageId;
    s32 step;
    f32 alphaRate;
};
