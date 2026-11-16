#pragma once
#include "types.h"

typedef struct info_msg info_msg;

struct info_msg {
    s32 num;
    s32 x;
    s32 y;
    char *text;
    u32 color;
    char *parent;
    char *name;
    bool update;
    u32 count;
};
