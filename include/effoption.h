#pragma once
#include "types.h"

typedef enum {
    FieldOt = 0,
    ColorAdjust = 1,
    AdjustRGBA = 2,
} effOption_Resource_TYPE;

typedef struct effOption effOption;
typedef struct effOption_Resource effOption_Resource;

struct effOption_Resource {
    effOption_Resource_TYPE type;
    f32 *param;
};

effOption *effGet(effOption_Resource *resrc);
