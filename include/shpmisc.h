#pragma once
#include "types.h"

void shpPoint3To2(f32 x3, f32 y3, f32 z3, f32 *x2, f32 *y2);
s32 knyGetGoodPoint(void);
void knySetGoodPoint(s32 a_point);
s32 knyGetGoodRank(void);
void knyAddGoodPoint(s32 a_add);
void knyCtrlGoodRank(s8 a_mode);
s32 nwdGetGoodPoint(void);
void nwdSetGoodPoint(s32 a_point);
s32 nwdGetGoodRank(void);
void nwdAddGoodPoint(s32 a_add);
void nwdCtrlGoodRank(s8 a_mode);
void shpAddGoodPointBuy(s32 a_price);
void shpAddGoodPointSell(s32 a_price);
void shpAddGoodPointOrder(s32 a_price);
void shpAddGoodPointTrade(s32 a_price);
s32 knyGetPriceBuy(s32 a_itemNo);
s32 knyGetPriceSell(s32 a_itemNo);
s32 nwdGetPriceOrder(s32 a_itemNo);
s32 nwdGetMagTrade(s32 a_stockNo);
s8 knyChkArrivalChapter(void);
s8 nwdChkArrivalChapter(void);
s8 knyChkArrivalRank(s32 a_rank_new, s32 a_rank_old);
s8 nwdChkArrivalRank(s32 a_rank_new, s32 a_rank_old);
s32 shpSetItemList(s32 a_listtype, s32 a_listmax, s16 **a_pList, bool _bo);
bool shpChkNewArrival(s32 a_itemID, s32 a_acttype);
