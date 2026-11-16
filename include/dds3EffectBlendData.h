#pragma once
#include "types.h"

typedef struct SDF_GS_ALPHA SDF_GS_ALPHA;
typedef struct dds3EffectBlendData dds3EffectBlendData;

struct dds3EffectBlendData {
    s32 src;
    SDF_GS_ALPHA *data;
};
