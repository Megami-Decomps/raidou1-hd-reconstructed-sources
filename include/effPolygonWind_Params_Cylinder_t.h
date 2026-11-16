#pragma once
#include "types.h"

typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effPolygonWind_Params_Cylinder_t effPolygonWind_Params_Cylinder_t;

struct effPolygonWind_Params_Cylinder_t {
    effBehavior_RGBParams_t *rgb;
    effBehavior_AlphaParams_t *alpha;
    u32 life;
    u32 number;
    effBehavior_RGBParams_t *rgb_p;
    effBehavior_AlphaParams_t *alpha_p;
    effBehavior_AlphaParams_t *fade_p;
    u32 life_p;
    u32 refresh;
    bool loop;
    u32 split;
    f32 repeat_u;
    f32 repeat_u_r;
    f32 repeat_v;
    f32 repeat_v_r;
    f32 move_u;
    f32 move_v;
    f32 length;
    f32 length_r;
    f32 width;
    f32 width_r;
    bool random;
    bool zTest;
    f32 radius_s;
    f32 radius_s_r;
    f32 radius_e;
    f32 radius_e_r;
    f32 rotate;
    f32 rotate_r;
    f32 accele;
    f32 height;
    f32 speed;
    f32 speed_r;
    f32 gravity;
    f32 curve_r;
    f32 curve_p;
    f32 curve;
};
