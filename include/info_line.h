#pragma once
#include "types.h"

typedef struct info_line info_line;

struct info_line {
    s32 num;
    sdfVector3_t *pos;
    u32 color;
    s32 size;
    char *parent;
    char *name;
    bool update;
    u32 count;
};
