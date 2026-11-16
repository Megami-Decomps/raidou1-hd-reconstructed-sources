#pragma once
#include "types.h"

typedef struct dds3EffectBlendData dds3EffectBlendData;
typedef struct dds3Effect_ParallelBlur_t dds3Effect_ParallelBlur_t;
typedef struct sdfIVector2_t sdfIVector2_t;

struct dds3Effect_ParallelBlur_t {
    sdfVector4_t abgr;
    f32 direction;
    f32 power;
    sdfIVector2_t center;
    sdfIVector2_t *xy[2];
    dds3EffectBlendData *_blend;
};
