#pragma once
#include "types.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct tagJMS_CAMERA_WK tagJMS_CAMERA_WK;

struct tagJMS_CAMERA_WK {
    dds3Basic_t *camera;
    f32 transX;
    f32 transY;
    f32 ratio;
    s32 count;
    s32 frame;
    s32 updateType;
};
