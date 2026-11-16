#pragma once
#include "types.h"

typedef struct mapLightParam_t mapLightParam_t;

struct mapLightParam_t {
    sdfVector4_t dir0;
    f32 col0[3];
    u32 rgb0;
    sdfVector4_t dir1;
    f32 col1[3];
    u32 rgb1;
    sdfVector4_t dir2;
    f32 col2[3];
    u32 rgb2;
    f32 cola[3];
    u32 rgba;
    f32 bloom_enable;
    f32 Threshold_enable;
    f32 Threshold_value;
    f32 Intensity_enable;
    f32 Intensity_value;
    f32 Scatter_enable;
    f32 Scatter_value;
    f32 Tint_enable;
    f32 Tint_value[4];
    f32 Clamp_enable;
    f32 Clamp_value;
    f32 HighQualityFiltering_enable;
};
