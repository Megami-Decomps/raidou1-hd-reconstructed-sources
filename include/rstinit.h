#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

extern dds3ProcessID_t *gGlobalPID;
extern s32 gGlobalFlag;
extern void *gGlobalReward;
extern char *textAssetName;
extern s32 gRstMapLoad;
extern s32 gRstMapLoadTime;
extern s32 gRstMapReturn_XFade;
extern s32 gRstMapReturn_LvUp;
extern s8 *rstRankUpKudaAddNumTbl;
extern s32 gGlobalDlcNo;
extern s32 gGlobalEncNo;

void rstLoadLocalizeText(void);
dds3ProcessFunc_t rstResultStartWaitProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstResultLoadWaitProcess(dds3ProcessID_t *PID);
s32 rstLoadMapResource(s32 RetType);
s32 rstMapReturnChkXFade(void *pData);
void *InitBgCore(sprHandle_t *pSpr);
void *InitBG(void);
void rstDestroyBG(void *pBG);
void rstEndNext(void *pData);
void rstCalcGift(void *pData, bool _item);
void rstDevilGiftCalc(void *_pData, s32 _stockNo, bool _item);
s32 rstCalcRankUp(void *pData);
void rstPreCalcUnit(void *pData);
void *Init(void *pReward);
s32 rstCheckTaiitsu(void);
dds3ProcessID_t *ProcessStart(void);
void ProcessEnd(void);
s32 ProcessCheck(void);
void rstSetReward(void *pReward);
void rstSetEncountDlcID(s32 _dlcID);
s32 rstGetEncountDlcID(void);
void rstSetEncountNo(s32 EncountNo);
s32 rstGetGlobalEncountNo(void);
void rstSetFlag(s32 Flag);
s32 rstCheckFlag(s32 Flag);
void rstResultStart(void);
s32 rstResultFadeCheck(void);
sdatPlayerUnitWork_t *rstGetPlayerUnit(void);
s32 rstGetGiftItem(s32 StockIndex);
s32 rstGetGiftItemNums(s32 StockIndex);
s32 rstCheckRankUp(void);
