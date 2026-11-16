#pragma once
#include "types.h"

typedef struct MJNVISUALCLASS MJNVISUALCLASS;

struct MJNVISUALCLASS {
    s32 id;
    f32 posDist;
    f32 cameraTargetHeight;
    f32 cameraEyeDist;
    f32 scale;
};
