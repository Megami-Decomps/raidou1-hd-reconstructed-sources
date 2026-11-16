#pragma once
#include "types.h"

typedef enum {
    EFFPAC_ST_LOADEND = 1,
    EFFPAC_ST_RELOAD = 2,
    EFFPAC_ST_ONMEM = 4,
    EFFPAC_ST_DECODE = 8,
    EFFPAC_ST_DECON = 16,
    EFFPAC_ST_ONMEM_N = 32,
} EFFPAC_ST;
