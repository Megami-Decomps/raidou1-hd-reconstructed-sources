#pragma once
#include "types.h"

void sdfTexFree(void *aHandle);
void sdfTexFreeDelayed(void *aHandle);
void *sdfTexSet(void *unit);
f32 sdfTexScale(void *tex);
f32 sdfTexScaleMulF4(void *tex);
f32 sdfTexScaleDivF4(void *tex);
