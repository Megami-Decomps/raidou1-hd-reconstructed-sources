#pragma once
#include "types.h"

typedef enum {
    NODRAW = 0,
    NOSELECT = 1,
} GOH_EVEDVL_TYPE;

typedef struct gohEventDevil_t gohEventDevil_t;

struct gohEventDevil_t {
    u32 Flag;
    u32 DevilID;
    GOH_EVEDVL_TYPE Type;
};
