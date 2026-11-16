#pragma once
#include "types.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct tagJMS_MODEL_CB tagJMS_MODEL_CB;

struct tagJMS_MODEL_CB {
    dds3Basic_t *unit;
    s32 stat;
    s32 idx;
    sdfIVector2_t curpos;
};
