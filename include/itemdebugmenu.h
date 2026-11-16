#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessFunc_t Process(dds3ProcessID_t *id);
void TextDraw(s32 panelNo, s32 TextPosX, s32 TextPosY, s32 TextSizeW, s32 TextSizeH, const sdfColor_t *col, char *str);
