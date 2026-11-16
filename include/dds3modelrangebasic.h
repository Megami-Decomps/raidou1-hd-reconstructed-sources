#pragma once
#include "types.h"

typedef struct dds3Basic_t dds3Basic_t;

bool dds3ModelRangeBasicConstructor(dds3Basic_t *pBasic);
s32 dds3ModelRangeBasicDestructor(dds3Basic_t *pBasic);
void dds3ModelRangeBasicSetBlockID(dds3Basic_t *aPtr, s32 blockID);
s32 dds3ModelRangeBasicGetBlockID(s32 resID);
