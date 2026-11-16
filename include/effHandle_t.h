#pragma once
#include "types.h"
#include "dds3effect.h"

typedef struct effHandle_t effHandle_t;

struct effHandle_t {
    DDS3EFFECT major;
    u32 minor;
    void *pwork;
    f32 version;
};
