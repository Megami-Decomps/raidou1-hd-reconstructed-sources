#pragma once
#include "types.h"
#include "libsdf.h"

void sdfThCreate(void *aStartFunc, SDF_TH_PRIO aPrio);
void *sdfThSleep(s32 aCycle);
void sdfThInit(void);
