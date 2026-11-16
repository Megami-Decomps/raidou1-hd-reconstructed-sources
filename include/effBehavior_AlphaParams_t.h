#pragma once
#include "types.h"
#include "TNEFFECT_BLEND.h"

typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;

struct effBehavior_AlphaParams_t {
    f32 transparency;
    TNEFFECT_BLEND blend;
    f32 fadeInRate;
    f32 fadeOutRate;
};
