#pragma once
#include "types.h"

typedef struct info_poly info_poly;

struct info_poly {
    s32 num;
    sdfVector3_t *pos;
    u32 col0;
    s32 type;
    char *parent;
    char *name;
    bool update;
    u32 count;
};
