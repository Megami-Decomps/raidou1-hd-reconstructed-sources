#pragma once
#include "types.h"

typedef struct physicsHandle_t physicsHandle_t;

struct physicsHandle_t {
    sdfVector4_t pos;
    sdfVector4_t dir;
    s32 frame;
    sdfVector4_t color;
    f32 scale;
    f32 rot;
    void *val_f;
};
