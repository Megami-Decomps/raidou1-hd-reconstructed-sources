#pragma once
#include "types.h"

typedef struct info_box info_box;

struct info_box {
    s32 num;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    u32 color;
    char *parent;
    char *name;
    bool update;
    u32 count;
    bool reSort;
};
