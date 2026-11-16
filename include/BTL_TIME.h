#pragma once
#include "types.h"

typedef enum {
    BTL_TIME_NONE = 0,
    BTL_TIME_BTLEND = 1,
    BTL_TIME_RUNAWAY = 2,
    BTL_TIME_MAPBACK = 3,
    BTL_TIME_CONTINUE = 4,
} BTL_TIME;
