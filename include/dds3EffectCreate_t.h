#pragma once
#include "types.h"

typedef struct dds3EffectCreate_t dds3EffectCreate_t;

struct dds3EffectCreate_t {
    u32 size;
    void *modFunc;
};
