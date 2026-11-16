#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern s32 gCompareCount;

dds3ProcessID_t *nmeStart(u32 type);
void nmeFinish(dds3ProcessID_t *proc);
s32 nmeGetCompareCount(void);
