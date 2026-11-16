#pragma once
#include "types.h"

typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_Blur_Params_t effBehavior_Blur_Params_t;
typedef struct effBehavior_EmitterParams_t effBehavior_EmitterParams_t;
typedef struct effBehavior_Params_Basic_t effBehavior_Params_Basic_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effBehavior_SR_Params_t effBehavior_SR_Params_t;

struct effBehavior_EmitterParams_t {
    sdfVector4_t pos;
    sdfVector4_t rot;
    u32 life;
    u32 count;
    f32 count_r;
};

struct effBehavior_Blur_Params_t {
    u32 length;
    u32 accurate;
};

struct effBehavior_Params_Basic_t {
    effBehavior_EmitterParams_t *emitter;
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    effBehavior_SR_Params_t *scale;
    effBehavior_SR_Params_t *rotate;
    u32 life;
    bool offset;
    bool random;
    effBehavior_Blur_Params_t *blur;
};
