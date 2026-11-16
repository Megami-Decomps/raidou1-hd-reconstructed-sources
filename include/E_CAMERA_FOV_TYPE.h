#pragma once
#include "types.h"

typedef enum {
    E_CAMERA_FOV_TYPE_Non = 0,
    E_CAMERA_FOV_TYPE_Set = 1,
    E_CAMERA_FOV_TYPE_LineAS = 2,
    E_CAMERA_FOV_TYPE_LineS = 4,
    E_CAMERA_FOV_TYPE_Line = 8,
    E_CAMERA_FOV_TYPE_End = 16,
} E_CAMERA_FOV_TYPE;
