#pragma once
#include "types.h"

typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effPolygonThunder_Params_Basic_t effPolygonThunder_Params_Basic_t;

struct effPolygonThunder_Params_Basic_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    u32 number;
    u32 split;
    u32 wait;
    f32 refraction;
    f32 refraction_r;
    u32 wave;
    f32 wave_h;
    f32 curve;
    f32 curve_r;
    bool zTest;
    effBehavior_AlphaParams_t *alpha_p;
    sdfVector4_t abgr_c;
    sdfVector4_t abgr_b;
    sdfVector4_t abgr_e;
    f32 width_c;
    f32 width_e;
    f32 length;
};
