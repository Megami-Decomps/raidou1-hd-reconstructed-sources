#pragma once
#include "types.h"

void InitializeWordwrap(void *text);
char *ConvertNBSP(char *text);
char *Convert(char *text, bool spc, s32 SetLine, f32 SetWidth);
