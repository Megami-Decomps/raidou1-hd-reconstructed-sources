#pragma once
#include "types.h"

typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effPolygonFlash_Params_ScatterTex_t effPolygonFlash_Params_ScatterTex_t;

struct effPolygonFlash_Params_ScatterTex_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    u32 number;
    effBehavior_AlphaParams_t *alpha_p;
    u32 life_p;
    u32 refresh;
    bool loop;
    bool random;
    bool zTest;
    bool converge;
    sdfVector4_t abgr_in;
    sdfVector4_t abgr_out;
    f32 width_in;
    f32 width_r;
    f32 length;
    f32 length_r;
    f32 radius_s;
    f32 radius_s_r;
    f32 radius_e;
    f32 radius_e_r;
    f32 spread;
    f32 spread_r;
    f32 speed;
    f32 speed_r;
    f32 accele;
};
