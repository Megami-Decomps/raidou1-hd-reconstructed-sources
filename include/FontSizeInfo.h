#pragma once
#include "types.h"

typedef struct FontSizeInfo FontSizeInfo;

struct FontSizeInfo {
    bool font_size_auto;
    bool font_raito;
    f32 font_size;
    s32 character;
    s32 line;
    s32 word;
    s32 paragraph;
    f32 offy;
};
