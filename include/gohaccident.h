#pragma once
#include "types.h"
#include "gohAccidentKN.h"
#include "gohAccidentLR.h"

typedef enum {
    gohAccidentTN_NON = 0,
    gohAccidentTN_MAJIN = 1,
    gohAccidentTN_MAGATSU = 2,
    gohAccidentTN_BLANK = 3,
    gohAccidentTN_PARAM = 4,
    gohAccidentTN_OMOIDE = 5,
    gohAccidentTN_OMOIDE_WAKU = 6,
    gohAccidentTN_NORMAL = 7,
    gohAccidentTN_NORMAL_PAR = 8,
} gohAccidentTN;

typedef enum {
    EMRK_NONE = 0,
    EMRK_NORMAL = 1,
    EMRK_DOUZOKU = 2,
    EMRK_SEIREI_UP = 3,
    EMRK_SEIREI_DN = 4,
    EMRK_MITAMA = 5,
    EMRK_SP = 6,
} EMRaceKind;

typedef struct CMAccident CMAccident;

struct CMAccident {
    gohAccidentKN m_eKind;
    gohAccidentTN m_eForceAccident;
    bool m_bLimitFlag;
    bool m_bProhibitFlag;
    s8 m_iTypeCnt;
    s8 m_iHeroLevel;
    s8 m_iMoonAge;
    s8 m_iItemCnt;
    s8 m_iReqItemCnt;
    s32 m_iCombineCnt;
    gohAccidentLR m_eLuckRank;
    EMRaceKind m_eRaceKind;
    s16 m_iNormalDevilNo;
    s16 m_iCreateDevilNo;
    s32 m_iInvestibleFund;
    bool m_bInvestibleDiamond;
    s8 m_iTypeValParam;
    s8 m_iTypeValValue;
    s16 m_iTypeValSkill;
    gohAccidentTN *m_aeType[4];
    s16 m_aItem[8];
    s16 m_aReqItem[8];
    bool m_state;
    s8 m_iMoonAge16;
    bool m_setEnd;
};

extern CMAccident *s_pcInst;

void gohCreateInstance(void);
void gohDestroyInstance(void);
void gohClear(void);
void gohSetForceAccident(gohAccidentTN eNo);
void gohSetCombineCnt(s32 iCnt);
void gohSetMoonAge(s32 iMoonAge);
void gohSetMoonAge16(s32 iMoonAge);
void gohSetHeroLevel(s32 iLevel);
void gohSetLuckRank(gohAccidentLR eRank);
s32 gohRequestItemCnt(void);
s32 gohRequestItemNo(void);
bool gohPresentItem(bool bGetItem);
gohAccidentKN gohGetKindNo(void);
bool gohDecide(void);
s32 gohGetTypeCnt(void);
bool gohGetEndFlag(void);
gohAccidentTN gohGetTypeNo(s32 idx);
s32 gohGetTypeVal(s32 iNo);
s32 gohGetCreateDevilNo(void);
void gohDebugMajinDead(void);
