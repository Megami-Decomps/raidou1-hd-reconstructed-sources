#pragma once
#include "types.h"

typedef struct Crack_t Crack_t;
typedef struct Flash_t Flash_t;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effPolygonCrack_Params_Basic_t effPolygonCrack_Params_Basic_t;

struct Crack_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    bool show;
    sdfColor32_t abgr_in;
    sdfColor32_t abgr_out;
    f32 speed;
    f32 scale;
    f32 width;
};

struct Flash_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    bool show;
    bool type;
    s32 wait;
    sdfVector4_t abgr_in;
    sdfVector4_t abgr_out;
    f32 width_in;
    f32 width_out;
    f32 width_r;
    f32 length;
    f32 length_r;
    s32 length_f;
    u32 interval;
    f32 rotate;
    f32 rotate_a;
};

struct effPolygonCrack_Params_Basic_t {
    Crack_t *crack;
    Flash_t *flash;
    bool zTest;
};
