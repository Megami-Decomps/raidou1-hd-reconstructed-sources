#pragma once
#include "types.h"

typedef enum {
    NCSTS_NONE = 0,
    NCSTS_INIT = 1,
    NCSTS_READW = 2,
    NCSTS_MOTION = 3,
    NCSTS_IN = 4,
    NCSTS_WAIT = 5,
    NCSTS_OUT = 6,
    NCSTS_END = 7,
} NCSTS;
