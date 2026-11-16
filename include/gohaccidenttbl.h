#pragma once
#include "types.h"
#include "EMParam.h"
#include "SKLID.h"

typedef struct gohAccidentDevilTbl gohAccidentDevilTbl;
typedef struct gohAccidentFactorTbl gohAccidentFactorTbl;

struct gohAccidentFactorTbl {
    s16 iFactor;
    s16 iRate;
};

struct gohAccidentDevilTbl {
    u8 uDevilNo;
    s8 iDiamondChk;
    u16 uGold;
};

extern gohAccidentDevilTbl *s_BlankTbl;
extern gohAccidentFactorTbl *s_RequestItemTbl1;
extern gohAccidentFactorTbl *s_RequestItemTbl2;
extern gohAccidentFactorTbl *s_RequestItemTbl3;
extern s16 *s_LuckRateMajinTbl;
extern s16 *s_LuckRateToshidensetsuTbl;
extern gohAccidentDevilTbl *s_MajinTbl;
extern gohAccidentDevilTbl *s_ToshidenTbl;
extern gohAccidentDevilTbl *s_SlimeTbl;
extern SKLID *s_aiOmoideSkillTbl;
extern s16 *gohAccidentDevil;
extern EMParam *eParamTblAge8;
extern EMParam *eParamTblAge;
extern f32 *cntParaTbl;
extern f32 **parCntTbl;
extern f32 **hpCntTbl;
