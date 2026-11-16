#pragma once
#include "types.h"

typedef enum {
    SHP_SORT_INIT = 0,
    SHP_SORT_BUY = 1,
    SHP_SORT_SELL = 2,
    SHP_SORT_END = 3,
} SHP_SORT;

typedef struct tagSHP_WK tagSHP_WK;

extern tagSHP_WK *wk;
extern bool g_bGuideOff;

void shpSetWork(tagSHP_WK *a_pWork);
s8 shpUpdateBuy(void);
s8 shpUpdateSell(void);
s8 shpUpdateTrade(void);
s8 shpUpdateOrder(void);
s8 shpUpdateEnter(void);
s8 shpUpdateLeaveKonnouya(void);
s8 shpUpdateLeaveMilkHall(void);
s8 shpUpdateLeave(void);
void shpTalkTitleSet(s32 num, s32 type);
s8 shpUpdateTalk(void);
s8 shpUpdateNews(void);
s8 shpUpdateGoma(void);
s8 shpUpdateDBOOK(void);
void chkpDatscr(void);
void shpSortMenu(s16 **_nowList, s32 _num, SHP_SORT _sort);
void shpSortSetting(SHP_SORT _sort);
void shpSortFunc_Buy(void);
void shpSortFunc_Sell(void);
