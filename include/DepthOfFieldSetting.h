#pragma once
#include "types.h"

typedef struct DepthOfFieldSetting DepthOfFieldSetting;

struct DepthOfFieldSetting {
    DepthOfFieldSetting *hokanData;
    bool active;
    bool modeEnable;
    s32 modeValue;
    bool startEnable;
    f32 startValue;
    bool endEnable;
    f32 endValue;
    bool maxRadiusEnable;
    f32 maxRadiusValue;
    bool highQualityFilterringEnable;
    bool highQualityFilterringValue;
    bool focusDistanceEnable;
    f32 focusDistanceValue;
    bool focalLengthEnable;
    f32 focalLengthValue;
    bool apertureEnable;
    f32 apertureValue;
    bool bladeCountEnable;
    s32 bladeCountValue;
    bool bladeCurvatureEnable;
    f32 bladeCurvatureValue;
    bool bladeRotationEnable;
    f32 bladeRotationValue;
};
