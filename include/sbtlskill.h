#pragma once
#include "types.h"
#include "SBTLUNIT_MOTION.h"
#include "SKLID.h"

typedef enum {
    SBTLEFFECT_FLG_NONE = 0,
    SBTLEFFECT_FLG_PROGRAM = 1,
    SBTLEFFECT_FLG_RANDOM = 2,
    SBTLEFFECT_FLG_HITMHT = 4,
    SBTLEFFECT_FLG_C_PLAYER = 16,
    SBTLEFFECT_FLG_C_NAKAMA = 32,
    SBTLEFFECT_FLG_MSTOP = 64,
    SBTLEFFECT_FLG_DMGEFFON = 128,
    SBTLEFFECT_FLG_CPYUSERPOS = 256,
    SBTLEFFECT_FLG_NOFUKAEFF = 512,
} SBTLEFFECT_FLG;

typedef struct SBTLAUTO_TBL SBTLAUTO_TBL;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLSKLVISUAL_TBL SBTLSKLVISUAL_TBL;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct SBTLSKLVISUAL_TBL {
    SBTLUNIT_MOTION motionno;
    SBTLUNIT_MOTION motionno2;
    SKLID h_effectno;
    s16 SABno;
    SBTLEFFECT_FLG flg;
};

extern SBTLSKILLP_TBL *tbldata[1600];
extern SBTLSKLVISUAL_TBL *visualtbldata;
extern SBTLAUTO_TBL *autotbldata;

SKLID sBtlGetExeSkill(SKLID sklid, s32 *pSklid1);
SKLID GetExeSkill(SKLID sklid);
bool sBtlCheckHaveSkill(SBTLUNIT_WORK *wk, SKLID sklid);
SBTLSKILLP_TBL *sBtlGetSkilltbl(SKLID skillid);
SBTLSKLVISUAL_TBL *sBtlGetSklVisualTbl(SKLID sklid);
bool sBtlSetSkill_MotionData(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlSetSkill_EffectData(SBTLUNIT_WORK *wk, SKLID sklid, bool r_kaja);
bool sBtlSetHatData(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlSetSkillData(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlSetSkillData_EffectOnly(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlCheckMHTData(SBTLUNIT_WORK *wk, SKLID sklid);
void sBtlKettouProc(void);
