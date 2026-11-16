#pragma once
#include "types.h"

typedef struct tagSHP_DRAW_WK tagSHP_DRAW_WK;

extern tagSHP_DRAW_WK *wk;

void shpBackParam(s32 a_alphaType, s32 a_u0, s32 a_v0, s32 a_u1, s32 a_v1, u32 a_col);
void shpItemListTest(s32 a_acttype, s32 a_topno, s32 a_drwno, s32 a_lstmax, s32 a_drwmax, s32 a_selnum, s32 a_selmax, s32 a_yen, s32 a_mag, s32 a_trade, f32 a_alphaRate);
void knyDrawKeyHelp(s32 a_type, f32 a_alphaRate);
void nwdDrawKeyHelp(s32 a_type, f32 a_alphaRate);
void shpRootCursor(s32 a_x, s32 a_y);
void shpRootCursorInit(void);
void shpResetRootLine(void);
bool shpCheckRootLineMax(void);
void shpCursorLine(s32 a_shopType, s32 a_menuNo);
void shpRootLine(s32 a_x, s32 a_y);
void shpRootCursorSelect(s32 a_x, s32 a_y);
void shpBackSpr(s32 a_shopType, f32 a_alphaRate1, f32 a_alphaRate2);
void shpCommandHelp(s32 a_cmdID, u8 a_alphaRate);
void shpRootMenuTitle(s32 a_shoptype);
void shpLoadFile(s32 a_shopType);
void Init(void);
void shpEnd(void);
