#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessFunc_t Process(dds3ProcessID_t *id);
void TextDraw(s32 panelNo, s32 TextPosX, s32 TextPosY, s32 TextSizeW, s32 TextSizeH, const sdfColor_t *col, char *str);
void StatusNakamaParaDebug(s8 *level, s16 *status_now, s16 *status_Back, s16 BaseStatus, s32 *MaxHP, s32 *HP, s16 pItem, s32 ChrID, s32 Bonus);
void StatusPlayerParaDebug(s16 *status_now, s16 *status_back, s32 ChrID);
void SetHP(s32 *HP, s32 maxHP);
