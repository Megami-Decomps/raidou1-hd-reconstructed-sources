#pragma once
#include "types.h"

extern f32 sdfSinTable[128];

f32 sdfDivSqrt(f32 aBase, f32 aValue);
f32 sdfSin(f32 aRadius);
f32 sdfCos(f32 aRadius);
f32 sdfAtan(f32 aX);
f32 sdfAtan2(f32 aY, f32 aX);
f32 sdfAcos(f32 aX);
f32 sdfClipAngleValuePI(f32 aValue);
sdfVector3_t sdfMultiply(void *mtx, const sdfVector3_t *vct);
sdfVector3_t sdfTransposeMultiply(void *mtx, const sdfVector3_t *vct);
void Init(void *list);
