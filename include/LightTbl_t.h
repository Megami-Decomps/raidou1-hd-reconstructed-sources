#pragma once
#include "types.h"

typedef struct BloomSetting BloomSetting;
typedef struct LightTbl_t LightTbl_t;

struct LightTbl_t {
    f32 _dir0[3];
    f32 _col0[3];
    f32 _dir1[3];
    f32 _col1[3];
    f32 _dir2[3];
    f32 _col2[3];
    f32 _cola[3];
    BloomSetting *bloomSetting;
};

struct BloomSetting {
    f32 _bloom_enable;
    f32 _Threshold_enable;
    f32 _Threshold_value;
    f32 _Intensity_enable;
    f32 _Intensity_value;
    f32 _Scatter_enable;
    f32 _Scatter_value;
    f32 _Tint_enable;
    f32 _Tint_value[4];
    f32 _Clamp_enable;
    f32 _Clamp_value;
    f32 _HighQualityFiltering_enable;
};
