#pragma once
#include "types.h"

typedef enum {
    CMP_MODE_NONE = -1,
    CMP_MODE_NORMAL = 0,
    CMP_MODE_LOAD = 1,
    CMP_MODE_TITLE = 2,
    CMP_MODE_END = 3,
    CMP_MODE_NUM = 4,
} CMP_MODE;
