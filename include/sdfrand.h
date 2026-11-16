#pragma once
#include "types.h"

typedef struct sdfRandCB_t sdfRandCB_t;

extern sdfRandCB_t *sdfDefaultRandCB;

u32 sdfGet(sdfRandCB_t *aCB);
f32 sdfGetFloat(sdfRandCB_t *aCB);
u32 sdfGetInt(sdfRandCB_t *aCB, u32 aLimit);
void Init(sdfRandCB_t *aCB, u32 aSeed);
void sdfInitByTime(sdfRandCB_t *aCB);
