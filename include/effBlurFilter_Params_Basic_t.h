#pragma once
#include "types.h"

typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effBehavior_SR_Params_t effBehavior_SR_Params_t;
typedef struct effBlurFilter_Params_Basic_t effBlurFilter_Params_Basic_t;

struct effBlurFilter_Params_Basic_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    effBehavior_SR_Params_t *scale;
    effBehavior_SR_Params_t *rotate;
    effBehavior_SR_Params_t *area;
    u32 life;
    bool mode;
};
