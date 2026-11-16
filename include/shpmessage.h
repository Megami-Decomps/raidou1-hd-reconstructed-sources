#pragma once
#include "types.h"

s32 shpLinkData(u8 *a_pDatScr);
void shpStartScript(s32 a_procedureNo);
void shpNewsStartScript(void);
void shpOrderStartScript(s32 a_stockID, s32 a_itemID);
void shpEnterStartScript(s32 a_shopType);
bool shpCheckScript(void);
void shpMsgInit(void);
void shpMsgEnd(void);
