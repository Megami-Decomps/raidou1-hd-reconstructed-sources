#pragma once
#include "types.h"
#include "ATR.h"
#include "ATRB.h"
#include "BSTF.h"
#include "EFFID.h"
#include "EFFPAC_ST.h"
#include "SBTLEFF_BEDTYPE.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"

typedef enum {
    DAMAGEON = 1,
    YUKAON = 2,
    DAMAGERGB = 4,
    YUKARGB = 8,
} EFFDMG;

typedef struct EFFPDATA_WORK EFFPDATA_WORK;
typedef struct SBTLEFFDMG_TBL SBTLEFFDMG_TBL;
typedef struct SBTLEFF_DELLISTWORK SBTLEFF_DELLISTWORK;
typedef struct SBTLEFF_LISTWORK SBTLEFF_LISTWORK;
typedef struct SBTLEFF_PACDATAWORK SBTLEFF_PACDATAWORK;
typedef struct SBTLEFF_WORK SBTLEFF_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SBTL_HITEFF SBTL_HITEFF;

struct SBTLEFFDMG_TBL {
    EFFDMG flg;
    s16 d_eplno;
    s16 y_eplno;
    u8 dr;
    u8 dg;
    u8 db;
    u8 yr;
    u8 yg;
    u8 yb;
};

extern SBTLEFFDMG_TBL *dmg_tbldata_p;
extern SBTLEFFDMG_TBL *dmg_tbldata;
extern ATR *swordAtrTbl;
extern ATRB *swordAtrbTbl;
extern BSTF *swordBstTbl;
extern EFFID *swordEffIdTbl;
extern sdfVector4_t *swordEffClrTbl;
extern sdfVector4_t swordEffDefaultClr;

void sBtlAddHitEff(SBTLEFF_WORK *pEffWork);
void sBtlDltHitEff(SBTLEFF_WORK *pEffWork);
void sBtlSetEffectData(SBTLEFF_WORK *ewk, SBTLUNIT_WORK *wk, SKLID sklid, s32 workID, SBTLEFF_BEDTYPE type, s32 no, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime);
s32 sBtlGetEffectData_Num(s32 id);
EFFPDATA_WORK *sBtlGetEffectData(s32 id, s32 no);
SBTLEFF_PACDATAWORK *sBtlGetEffectPacData(s32 id, s32 no);
void sBtlBS14_CLEAR_Pos(SBTLUNIT_WORK *wk, SBTLEFF_WORK *ewk, sdfVector4_t *p);
bool sBtlCheckDeleteEffect(SBTLEFF_WORK *wk);
bool sBtlCheckCancelEffect(SKLID skillID);
bool sBtlCheckStopEffect(SBTLEFF_WORK *wk);
bool sBtlSetEffectColor_Race(SBTLEFF_WORK *wk, SBTLUNIT_WORK *wklock);
s32 sBtlCheckSABFile(SKLID sklid);
bool sBtlHDloadChk(SKLID sklid);
s32 sBtlCheckDisp_Helper(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlLoadEffectData_Player_pData(s32 point, void *pData);
bool EffFunc_SUMMON(SBTLEFF_WORK *wk);
bool EffFunc_SUMMON_E(SBTLEFF_WORK *wk);
bool EffFunc_Hanyou(SBTLEFF_WORK *wk);
bool EffFunc_TateBg(SBTLEFF_WORK *wk);
bool sBtlCheckBEDType(SBTLEFF_BEDTYPE cmp, SBTLEFF_BEDTYPE in);
bool sBtlOnDataLoadInit_Pac1(void);
bool sBtlOnDataLoadInit(void);
bool sBtlLoadEffectData_Decode(SBTLUNIT_WORK *wk);
bool sBtlLoadEffectData_Decode_FastLoad_Nakama(SBTLUNIT_WORK *wklock);
bool sBtlInitLoadPlayerOnMemData(void);
bool sBtlLoadEndCheck_PlayerOnMemData(void);
bool sBtlLoadPlayerOnMemData(void);
bool sBtlDeleteOnData(s32 flg);
SBTLEFF_LISTWORK *sBtlCreateEffList(void);
SBTLEFF_WORK *sBtlGetEffWork(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, s32 id, s32 no);
f32 sBtlGetDmgEffScale(SBTLUNIT_WORK *wk);
void sBtlSetDmgEffShinad(SBTLEFF_WORK *pEff, SBTLUNIT_WORK *pUnit, s32 Type);
SBTLEFF_WORK *sBtlCreateEff(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, EFFID effectid, s32 starttime, const sdfVector4_t *defpos, u32 rgba, s8 flg, f32 _Pow, SKLID _Skill);
bool sBtlCheckSABData(SBTLEFF_WORK *wk);
bool sBtlCheckEffectData(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime);
bool sBtlCheckEffectData_GunMode2(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime);
bool sBtlCheckEffectData_SeOnly(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime);
bool SetDamageProc(SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wk, SKLID sklid, const sdfVector4_t *ppos);
void AddSerialID2(void);
s32 sBtlGetEffectSerialID2_Now(void);
bool sBtlDeleteEffectData_SerialID2(SBTLEFF_LISTWORK *lwk, s32 serialID2);
bool sBtlSetDecAlpha_SerialID2(SBTLEFF_LISTWORK *lwk, s32 serialID2, s32 alpha);
bool sBtlDeleteEffectData_SkillID(SBTLEFF_LISTWORK *lwk, SKLID skillid);
bool sBtlForceDelete_SPID(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID skillid);
bool sBtlDeleteEffectData_SkillIDType(SBTLEFF_LISTWORK *lwk, SKLID skillid, SBTLEFF_BEDTYPE type);
bool sBtlDeleteEffectData_SkillIDTypeUnit(SBTLEFF_LISTWORK *lwk, SKLID skillid, SBTLEFF_BEDTYPE type, s32 unitID);
bool sBtlEff_DeleteEffectData_EffID(SBTLEFF_LISTWORK *lwk, EFFID effid);
s16 sBtlGetStartTime_Damage(void);
void sBtlClearStartTime_Damage(void);
s32 sBtlGetEffTime(EFFID id);
bool sBtlListProc(SBTLEFF_LISTWORK *lwk);
bool Draw(void);
SBTLEFF_WORK *sBtlGetEffectWork_ID(SBTLEFF_LISTWORK *lwk, s32 eListID);
s32 sBtlGetEffectStat_ID(SBTLEFF_LISTWORK *lwk, s32 eListID);
bool sBtlForceDelete_ID(SBTLEFF_LISTWORK *lwk, s32 eListID);
bool sBtlForceDelete_ID_Acter(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, EFFID effectid);
bool sBtlForceDelete_ID_Summon(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk);
bool sBtlForceDelete_ID_SummonFR(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk);
bool sBtlForceDelete_ID_Return(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk);
bool sBtlFadeOut_BadStatusEffect(SBTLUNIT_WORK *wk, s32 alpha);
bool sBtlSetDecAlpha_SerialID(SBTLEFF_LISTWORK *lwk, s32 serialID, s32 alpha);
bool sBtlForceDelete_SerialID(SBTLEFF_LISTWORK *lwk, s32 serialID);
bool sBtlForceDelete_SkillFlag(u32 flg);
bool sBtlForceDelete_SkillFlag_Acter(SBTLUNIT_WORK *wk, u32 flg);
bool sBtlForceDelete_SkillID_Acter(SBTLUNIT_WORK *wk, SKLID skillid);
void sBtlForceDeleteAll(s32 flag);
void sBtlForceDeleteAll_TimeStopSkill(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wk2);
bool sBtlForceReset(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk);
bool sBtlForceReset_Tatari(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk);
bool sBtlForceResetDecAlpha(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, s32 alpha);
bool sBtlReleaseEff(SBTLEFF_LISTWORK *lwk, bool flg);
bool sBtlDeleteEffList(SBTLEFF_LISTWORK *lwk);
s32 sBtlGetNumOfEffect_SAB(SBTLEFF_LISTWORK *lwk, SBTLEFF_BEDTYPE BEDtype, SBTLUNIT_SIDE side);
bool sBtlSearchEffect_SAB(SBTLEFF_LISTWORK *lwk, SKLID BEDsklid, SBTLEFF_BEDTYPE BEDtype);
bool sBtlSearchEffect_SAB_Acter(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID BEDsklid, s32 BEDtype);
bool sBtlSearchEffect_ID(SBTLEFF_LISTWORK *lwk, EFFID effectid);
bool sBtlSearchEffect_WorkID(SBTLEFF_LISTWORK *lwk, s32 workid);
bool sBtlInitEffectWork(void);
bool sBtlCheckLoadEnd_EffectWork(void);
SBTLEFF_DELLISTWORK *sBtlCreateDelList(void);
bool sBtlCheckDelWork_Request(SBTLEFF_DELLISTWORK *lwk, s32 GroupID);
bool sBtlSearchDelWork_Side(SBTLEFF_DELLISTWORK *lwk, SBTLUNIT_SIDE side);
bool sBtlCreateDelWork(SBTLEFF_DELLISTWORK *lwk, SKLID skillid, SBTLUNIT_SIDE side, s32 GroupID);
bool sBtlDelProc(SBTLEFF_DELLISTWORK *lwk);
bool sBtlReleaseDelList(SBTLEFF_DELLISTWORK *lwk, u8 flg);
bool sBtlDeleteDelList(SBTLEFF_DELLISTWORK *lwk);
bool sBtlDeleteHaveSkill_EffectWork(SBTLUNIT_WORK *wk);
bool sBtlForceDelete_EffectWork_ID(SKLID id, s8 flg);
bool sBtlForceDelete_EffectWork(s8 flg);
void sBtlClearEffPacWork(s32 index);
s32 sBtlSearchEffectData(SKLID skillid);
s32 sBtlSearchEffectData_Blank(SKLID skillid);
s32 sBtlSearchEffectDataCnt(void);
bool sBtlLoadEffectData_IDMask(SKLID id, EFFPAC_ST flg);
bool sBtlLoadEffectData_ID(SKLID id);
bool sBtlLoadEffectData_Nakama(SBTLUNIT_WORK *wk);
bool sBtlLoadEffectData(SBTLUNIT_WORK *wk);
bool sBtlSetSummonEffect_Nakama(SBTLUNIT_WORK *wk, s8 flg);
bool sBtlSetReturnEffect_Nakama(SBTLUNIT_WORK *wk, s8 flg);
SBTLEFFDMG_TBL *sBtlGetEffDamagetbl(s32 major, s32 minor);
bool sBtlCheckYukaDamageEffect(SBTLUNIT_WORK *wk, SKLID sklid, u16 htype, s32 time, s8 type, const sdfVector4_t *_HitPos, SBTLUNIT_WORK *acter);
bool sBtlDeleteEffectData_EffListID(SBTLEFF_LISTWORK *lwk, s32 effListID);
void sBtlOutHitEff(SBTL_HITEFF *pHitEff);
bool sBtlDeleteEffectDataType(SBTLEFF_LISTWORK *lwk, SBTLEFF_BEDTYPE type);
bool sBtlSetColor_SummonEffect(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *unit);
