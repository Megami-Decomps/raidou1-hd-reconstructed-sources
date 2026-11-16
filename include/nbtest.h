#pragma once
#include "types.h"

typedef struct bDrawText bDrawText;

void PreBtlMenuObj(s32 idx);
void btlDrawTagLink(bDrawText *setText, bDrawText *dt, s32 idx);
bDrawText *btlDevPrintf(s32 aX, s32 aY, s32 aZ, s32 color, char *aStr, s32 f);
void SetBtlMenuObj(s32 idx);
void deleteBtlMenuObj(s32 idx);
