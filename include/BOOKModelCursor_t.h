#pragma once
#include "types.h"

typedef struct BOOKModelCursor_t BOOKModelCursor_t;

struct BOOKModelCursor_t {
    s32 Timer;
    s32 Fade;
    s32 AlphaRate;
    s32 SelIndex;
};
