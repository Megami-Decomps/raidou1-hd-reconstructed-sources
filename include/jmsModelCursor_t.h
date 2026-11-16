#pragma once
#include "types.h"

typedef struct jmsModelCursor_t jmsModelCursor_t;

struct jmsModelCursor_t {
    s32 Timer;
    s32 Fade;
    s32 AlphaRate;
    s32 SelIndex;
};
