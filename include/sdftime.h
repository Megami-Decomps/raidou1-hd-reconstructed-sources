#pragma once
#include "types.h"
#include "libsdf.h"

typedef struct sdfTime_t sdfTime_t;

extern u8 GetDelay;

SDF_TIME Get(sdfTime_t *aTime);
