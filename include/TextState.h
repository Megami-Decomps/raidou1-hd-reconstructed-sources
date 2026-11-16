#pragma once
#include "types.h"

typedef enum {
    TextState_NORMAL = 0,
    TextState_NO_DECIDE = 1,
    TextState_ON_CURSOR = 2,
    TextState_ON_CURSOR_NO_DECIDE = 3,
} TextState;
