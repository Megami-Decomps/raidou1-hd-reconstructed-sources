#pragma once
#include "types.h"

void sdfMemInit(void);
bool sdfMemCheckRelease(void);
void sdfMemResourcesRelease(void);
void sdfMemRelease(void);
void Release(s32 generation);
void sdfMemSetAllocated(void);
s64 sdfMemGetDifference(void);
void sdfMemSetFunc(void *func);
