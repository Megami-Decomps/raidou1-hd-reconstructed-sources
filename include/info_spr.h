#pragma once
#include "types.h"

typedef struct info_spr info_spr;

struct info_spr {
    s32 num;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 sprNum;
    bool hRev;
    bool wRev;
    u32 color;
    char *parent;
    char *name;
    bool update;
    u32 count;
    bool reSort;
};
