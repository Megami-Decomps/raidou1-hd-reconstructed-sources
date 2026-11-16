#pragma once
#include "types.h"
#include "BSTF.h"
#include "SKLID.h"

typedef struct SBTLAISYO_DATAWORK SBTLAISYO_DATAWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SklItemGuage SklItemGuage;
typedef struct sdatParaWork_t sdatParaWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct SklItemGuage {
    SKLID sklId;
    s32 bookCnt;
};

struct sdatUnitWork_t {
    u32 flag;
    s8 raceid;
    s16 devilid;
    s8 level;
    s8 seikaku;
    s8 dummy0;
    s16 chuusei_high;
    s16 chuusei;
    s16 vice;
    s32 exp;
    sdatParaWork_t *now;
    sdatParaWork_t *backup;
    sdatParaWork_t *pitem;
    sdatParaWork_t *pbtl;
    sdatParaWork_t *huuma;
    sdatParaWork_t *accident;
    sdatParaWork_t *surpriseParam;
    sdatParaWork_t *over;
    SKLID *haveskill[17];
    SKLID *battleskill[8];
    SKLID *combSkill[2];
    SKLID *sousaSkill[2];
    s8 autoskill[17];
    BSTF badstatus;
    s16 badst_cnt;
    s16 badst_cnt2;
    s16 badst_cnt3;
    BSTF koufunst;
    s16 koufun_cnt;
    s16 autost_cnt;
    s16 autost_cnt2;
    u32 itemstatus;
    s16 itemst_cnt;
    s16 itemst_cnt2;
    SBTLAISYO_DATAWORK *aisyo;
    s16 talkskill;
    SKLID *aOmoideSkill[8];
    SKLID *aRsvSkl[3];
    s8 aOmoideSkillMaster[16];
    s16 iOmoideSkillCnt;
    bool bChuuseiDrink;
    bool bOmoideLearned[2];
    bool bChuuseiMax;
    void *nativeSkillList;
    s32 nativeSkillSetCnt;
    s32 restoreMoney;
    bool cmbTblErrorType[8];
    s32 newSklCnt;
    SKLID *newSklDrwOff[3];
    u32 uniq_code;
    SklItemGuage *sklItemGuages[65];
    bool geturei_vice_flag;
    s32 prevSkill;
    s32 prevTarget;
    SBTLUNIT_WORK *prevTgtUnit;
    void *DevilReportStok;
    s32 decisionGift;
    s8 TakaraCnt;
    s8 ZeniCnt;
    s8 TakumiCnt;
};
