#pragma once
#include "types.h"

void sdfPadControl(void);
void sdfPadSetAct0(s32 pad, s32 value);
void sdfPadSetAct1(s32 pad, s32 value);
void sdfPadSetAct(s32 pad, s32 value0, s32 value1);
void sdfPadInitManager(void);
