#pragma once
#include "types.h"

typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagRST_GROWTH_WORK tagRST_GROWTH_WORK;

extern s32 jimusyo_return_yen[50];
extern bool Report_LimitOver;
extern tagRST_GROWTH_WORK *talk_wk;
extern bool repeat;
extern sdfVector4_t map_cut_over2_cpos;
extern sdfVector4_t map_cut_over2_tpos;

s32 fldGetHojiID(char **pName);
sdfVector4_t fldGetMAP_CUT_OVERSET_Cam(void);
sdfVector4_t fldGetMAP_CUT_OVERSET_Tgt(void);
s32 fldGetFastTravelPrice(s32 mapID, u32 gotoIdx);
void fldWaitSet(void);
void fldRepeatSet(void);
void fldReportMsgInit(void);
void fldReportMsgEnd(sdatUnitWork_t *pWork);
void fldReportZeniget(sdatUnitWork_t *pWork, void *ZenigetList, void *EraseList, s32 *gold);
void fldReportHiroemon(sdatUnitWork_t *pWork, void *HiroemonList, void *EraseList, s32 *ItemID, s32 *count);
void fldReportGift(sdatUnitWork_t *pWork, void *GiftList, void *EraseList, s32 *ItemID, s32 *count);
void fldReportTakumi(sdatUnitWork_t *pWork, void *TakumiList, void *EraseList);
