#pragma once
#include "types.h"

typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effPolygonRing_Params_Basic_t effPolygonRing_Params_Basic_t;

struct effPolygonRing_Params_Basic_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    u32 split;
    bool zTest;
    f32 radius;
    u32 abgr_e_in;
    u32 abgr_c;
    u32 abgr_e_out;
    f32 width_e_in;
    f32 width_c;
    f32 width_e_out;
    f32 speed;
    f32 accele;
    bool converge;
};
