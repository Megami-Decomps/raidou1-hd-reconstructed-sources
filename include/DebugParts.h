#pragma once
#include "types.h"

typedef enum {
    PARTS_TEXT = 0,
    PARTS_PANEL = 1,
    PARTS_MAX = 2,
} PARTS;

typedef struct DebugParts DebugParts;

struct DebugParts {
    PARTS parts;
    f32 x;
    f32 y;
    f32 w;
    f32 h;
    char *text;
    sdfColor_t col;
    s32 fontSize;
};
