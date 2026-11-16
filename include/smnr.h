#pragma once
#include "types.h"

extern u32 Getrandstate;
extern u32 Getrandper;

u16 GetRand(u16 mod);
s32 GetIntervalRand(s32 min, s32 max);
u16 GetPercentage(void);
