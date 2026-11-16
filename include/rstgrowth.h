#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct _LvUpSkl _LvUpSkl;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagRST_GROWTH_WORK tagRST_GROWTH_WORK;

struct _LvUpSkl {
    s32 nmlSkl[3];
    s32 nmlSklPos[3];
    bool ofcSkl[3];
    s32 memSkl[2];
    bool bGetMemSkl[2];
    bool ofcMemSkl[2];
};

extern char *rstAssetKey;
extern dds3ProcessID_t *g_mainPID;
extern sdatPlayerUnitWork_t *g_pSrc;
extern sdatPlayerUnitWork_t *g_pDst;
extern sdatUnitWork_t *g_pUnitSrc;
extern sdatUnitWork_t *g_pUnitDst;
extern s32 g_plyLevelUpNum;
extern s32 g_plyRankUpNum;
extern s32 *g_dvlLevelUpNum;
extern s8 *g_dvlCyuuseiMax;
extern SKLID *g_learnCombSkillID;
extern SKLID *g_learnAutoSkillID;
extern bool g_bEndFadeOut;
extern bool g_bEndBgmLoad;
extern s32 s_nowhp;
extern bool *s_bRegistMemSkill;
extern _LvUpSkl *g_aLvUpSkl;
extern s32 *s_arrLoyaltyBonusType;
extern s32 g_newSklCnt;
extern s32 rstGrowthSeqDevil_i;
extern s32 rstGrowthSeqDevil_j;

s32 rstGetNmlSklNum(_LvUpSkl *pLvUpSkl);
s32 rstGetMemSklNum(_LvUpSkl *pLvUpSkl);
s32 rstChkGrowthNextDevil(s32 a_startStockNo);
void rstCallProcEnd(tagRST_GROWTH_WORK *wk);
void rstRelease(tagRST_GROWTH_WORK *wk);
dds3ProcessID_t *rstGetGiftMsgPID(void);
void rstSetFlagPlayBgm(void);
bool rstChkFlagPlayBgm(void);
bool rstSetLvUpSkl(s32 i, s32 *pTmp);
void rstInit(tagRST_GROWTH_WORK *wk, bool _talk);
dds3ProcessID_t *rstProcessStart(void);
dds3ProcessID_t *rstCmpItemGrowthStart(void);
void rstProcessEnd(void);
bool rstProcessCheck(void);
