#pragma once
#include "types.h"

typedef struct Work_IPU Work_IPU;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;

struct Work_IPU {
    dds3ModelHandle_t *mdlHandle;
    u32 startFrame;
};
