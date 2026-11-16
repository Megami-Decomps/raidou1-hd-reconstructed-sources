#pragma once
#include "types.h"

typedef enum {
    PMD_FLAG_STOP = 1,
    PMD_FLAG_LOAD1 = 2,
    PMD_FLAG_LOAD2 = 4,
    PMD_FLAG_DATAOK = 8,
    PMD_FLAG_LOAD3 = 16,
    PMD_FLAG_LOADS = 32,
    PMD_FLAG_LOADD = 64,
    PMD_FLAG_LOADV = 128,
} PMD_FLAG;
