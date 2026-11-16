#pragma once
#include "types.h"
#include "SBTLPLAYER_MENUTYPE.h"
#include "SBTLPNL_MENU.h"
#include "SKLID.h"
#include "kernel.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sprHandle_t sprHandle_t;

bool sBtlCheckLiveTarget(SBTLUNIT_WORK *wk);
void Init(void);
bool sBtlDeleteMainPanel(void);
bool sBtlMainProc(void);
void sBtlResetMidashiAnim(s8 flg);
bool sBtlCheckSelectAnim(void);
void sBtlSetSelectAnim(s8 flg);
void sBtlResetSelectAnim(s8 flg);
bool sBtlMainDraw(void);
bool sBtlMainDraw2(void);
bool sBtlSetLoadPanelData(void);
bool sBtlCheckLoadFlg(void);
bool sBtlCheckLoadData(void);
void sBtlDrawSprite(s32 x, s32 y, s32 alpha, sprHandle_t *handle, s32 sprno);
void sBtlDrawSprite_RGBA2(s32 x, s32 y, u32 *rgba, sprHandle_t *handle, s32 sprno, DDS3_OT ot);
bool sBtlResetSummonPanel(SBTLPLAYER_MENUTYPE menutype);
s32 sBtlGetMenuStatus(void);
void sBtlResetMenuPara(void);
void sBtlCancelMenuPara(void);
bool sBtlSetMenuPara(SBTLPNL_MENU mode, s32 stock_id, SKLID skillid, s32 itemid, s32 targetid, s32 smnid);
