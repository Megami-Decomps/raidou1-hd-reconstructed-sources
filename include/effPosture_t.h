#pragma once
#include "types.h"

typedef struct effPosture_t effPosture_t;

struct effPosture_t {
    sdfVector4_t pos;
    s32 frame;
    sdfVector4_t abgr;
    f32 scale;
    f32 rotate;
};
