#pragma once
#include "types.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"

#define MAJORNO 7
#define ANIMMAX 40
#define HITTYPE_SPHERE 0
#define HITTYPE_CYLINDER 1
#define HITTYPE_RING 2
#define ANIMST_INIT 0
#define ANIMST_PROC 1
#define ANIMST_PROC_IN 2
#define ANIMST_PROC_WAIT 3
#define ANIMST_PROC_OUT 4
#define ANIMST_END 5
#define ANIMST_EXIT 6
#define HITST_NONE 0
#define HITST_PROC 1
#define HITST_END 2

typedef struct SBTLDMG_ANIMWORK SBTLDMG_ANIMWORK;
typedef struct SBTLDMG_HITLISTWORK SBTLDMG_HITLISTWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLDMG_LISTWORK SBTLDMG_LISTWORK;
typedef struct SBTLEFF_WORK SBTLEFF_WORK;
typedef struct SBTLSKILLHIT_POSWORK SBTLSKILLHIT_POSWORK;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLSKILL_TBL SBTLSKILL_TBL;
typedef struct SBTLSKLHIT_PACDATAWORK SBTLSKLHIT_PACDATAWORK;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct SBTLSKILL_TBL {
    u16 type;
    u16 area;
    s32 mp;
    s32 mag;
    s32 starttime;
    s32 lifetime;
    s32 loopcnt;
    s32 looptime;
    s8 targetflg;
    u16 area_type;
    u32 flg;
    f32 dis;
    f32 area_r;
    f32 rad;
    f32 rad_area;
    u32 attr_flg;
    f32 hitbk_cnt;
    f32 hitbk_rate;
};

extern SBTLUNIT_WORK *playerhit;

void sBtlClearStaticPar(void);
s32 sBtlGetAddMag(s32 baseVal);
void sBtlSetAddMag(SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag);
void sBtlSetAddMag_Setsuma(SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag);
void sBtlSetAddMag_Setsuma_D(SBTLUNIT_WORK *a_pUnitTgt);
void sBtlSetAddMagAisyo(SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag);
void sBtlSetAddMagWeakAttack(SBTLUNIT_WORK *a_pUnitAct, SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag, SKLID _skl);
SBTLDMG_LISTWORK *sBtlCreateAnimList(void);
void sBtlCalcAnim_DmgNumPos(SBTLUNIT_WORK *wk, s32 mode, sdfVector4_t *pos);
bool sBtlCreateAnim_Unit(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *atk_wk, s32 damage, s16 time, s32 mode, SKLID sklid);
bool sBtlReleaseAnim_ID(SBTLDMG_LISTWORK *lwk, s32 id);
s32 sBtlRegistAnimList(SBTLDMG_LISTWORK *lwk, SBTLDMG_ANIMWORK *wk);
bool sBtlDeleteAnimList(SBTLDMG_LISTWORK *wk);
bool sBtlAnimListClr(void);
bool sBtlAnimListProc(void);
bool sBtlDrawAnimList(void);
void sBtlChangePosToDevil(s32 devilid);
SBTLDMG_HITLISTWORK *sBtlCreateHitList(void);
bool sBtlLoadAttackHitData_Decode(SBTLUNIT_WORK *wk);
bool sBtlSearchAttackHitData_Copy(SBTLUNIT_WORK *wk);
s32 sBtlSearchAttackHitData_Num(SBTLUNIT_WORK *wk);
bool sBtlLoadAttackHitData_pData(s32 index, void *pData);
bool sBtlInitLoadAttackHitData_pData(void);
bool sBtlForceDelete_AttackHitData(void);
bool sBtlLoadAttackHitData(SBTLUNIT_WORK *wk, s32 id, void *ppData);
bool sBtlDeleteAttackHitData(SBTLUNIT_WORK *wk);
void sBtlDltHit_by_UnitSkl(SBTLDMG_HITLISTWORK *lwk, s32 unitID, SKLID sklID);
s32 sBtlCreateHitC_New(SBTLDMG_HITLISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLEFF_WORK *ewk, s32 acterID, SKLID skillid, SBTLSKILLP_TBL *tbl, SBTLSKILLHIT_TBL *hittbl, SBTLSKLHIT_PACDATAWORK *pwk, SBTLUNIT_SIDE acterside, s32 serialID2);
bool sBtlCreateHitC_None(SBTLDMG_HITLISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLUNIT_WORK *acter, SBTLDMG_HITWORK *twk, SKLID skillid, SBTLSKILLP_TBL *tbl, const sdfVector4_t *pos, s32 serialID2);
void sBtlAddSerialID2(void);
bool sBtlSetApos12(const sdfVector4_t *startpos, const sdfVector4_t *endpos, const sdfVector4_t *rot, SBTLSKILLHIT_TBL *hittbl, sdfVector4_t *apos1, sdfVector4_t *apos2);
bool sBtlResetHitPos_XYZ(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, sdfVector4_t *rot, u16 tbltype);
bool sBtlSetHitPos_XYZ(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, sdfVector4_t *rot, u16 tbltype);
bool sBtlSetHitPos(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, sdfVector4_t *rot, sdfVector4_t *rott, u16 tbltype);
bool sBtlGetHit_OnlyEndPos(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_TBL *hittbl, SBTLSKILLHIT_POSWORK *pwk_st, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, u16 tbltype);
bool sBtlSetHitEndPos(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_TBL *hittbl, SBTLSKILLHIT_POSWORK *pwk_st, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, u16 tbltype);
SBTLDMG_HITWORK *sBtlSearchHit_SerialID(SBTLDMG_HITLISTWORK *lwk, s32 serialID);
s32 sBtlGetKaraburiNum(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *hwk);
void sBtlUnsetKaraburi(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *hwk);
bool sBtlClearHitC(SBTLDMG_HITLISTWORK *lwk, SBTLUNIT_WORK *wk);
void sBtlResetIdouPara(SBTLDMG_HITWORK *hwk);
bool sBtlHitCProc_Idou(SBTLDMG_HITLISTWORK *lwk);
bool sBtlHitCProc(SBTLDMG_HITLISTWORK *lwk);
bool sBtlCheckActDamage(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SKLID skillid);
void sBtlDecHp(SBTLUNIT_WORK *wk, s32 damage, SKLID skillid);
SBTLUNIT_WORK *sBtlCheckHitArea_Single(SBTLDMG_HITWORK *wk);
bool sBtlCheckGround(SBTLDMG_HITWORK *hwk, s32 hitflg);
bool sBtlSetHit(SBTLDMG_HITWORK *wk, SBTLUNIT_WORK *wklock, s32 *hitflg);
bool SetColor_PNL(u32 abgr);
bool ResetColor_PNL(u32 abgr);
bool sBtlDrawAttachEPL(SBTLDMG_HITLISTWORK *lwk);
bool sBtlReleaseHitC_List(SBTLDMG_HITLISTWORK *lwk, u8 flg);
bool sBtlDeleteHitList(SBTLDMG_HITLISTWORK *wk);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Normal(SBTLUNIT_WORK *wk, SKLID skillid);
bool sBtlCheckTargetList_csr(SBTLUNIT_WORK *wk, SKLID skillid);
bool sBtlCreateTargetList_csr(SBTLUNIT_WORK *wk, SKLID skillid);
bool CreateTargetList(SBTLDMG_HITWORK *twk, SKLID skillid);
bool sBtlCheckMutekiTime(SBTLUNIT_WORK *wk, SKLID skillid, u32 flg);
bool sBtlCheckHitArea(SBTLDMG_HITWORK *wk, SBTLUNIT_WORK *wklock);
bool sBtlCHitFunc_ATTACK(SBTLUNIT_WORK *wk, SBTLEFF_WORK *ewk, SBTLDMG_HITWORK *twk, SBTLSKILL_TBL *tbl);
SBTLUNIT_SIDE sBtlGetSide(SBTLUNIT_WORK *wk, u16 area, SBTLUNIT_SIDE acterside, u8 *flg);
bool CheckDamageTarget(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SKLID skillid);
bool sBtlCheckPlayerDead(void);
bool sBtlCheckDamageTarget_Skilltbl(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID skillid, s32 flg);
bool sBtlSearchDMG_Unit(SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *wk);
bool sBtlSetEntryUnitList_Hit(SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *wklock);
SBTLUNIT_WORK *sBtlCheckALLSkill(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlCheckHitHelp(SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *wklock);
bool sBtlSetDeadDamageEx(SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr, bool *a_pbDamage, f32 *a_pRate);
void sBtlSetDeleteKaja(SBTLUNIT_WORK *wklock, SKLID skillid);
void sBtlDeleteBuffAll(SBTLUNIT_WORK *wklock);
void sBtlDeleteDeBuffAll(SBTLUNIT_WORK *wklock);
void sBtlSetKudaDamage(s32 Damage);
bool sBtlDamageProc(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s8 guardflg);
bool sBtlContinuousSe(SBTLUNIT_WORK *_wk, SKLID _sklID);
bool sBtlCheckAttr_ATK(SBTLDMG_HITWORK *hwk, s32 attr);
s32 sBtlIsAura(SBTLUNIT_WORK *pBtlUnit, s32 kindFlg);
s32 sBtlUpdateDamageKaja(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *target, SKLID skillid, s32 damage);
s32 sBtlGetCalcDamageEx(SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SKLID skillid, s32 attr, s32 damage, bool *a_pbGuard, bool *a_pbCritical);
s32 sBtlGetCalcDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 acterID, SBTLDMG_HITWORK *hwk, s32 attr);
bool sBtlSetReflectDamage(SBTLUNIT_WORK *target, SBTLDMG_HITWORK *hwk);
s32 GetDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 acterID, SBTLDMG_HITWORK *hwk, s32 attr, bool _SE_PLAY);
u16 sBtlSetDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 damage, s32 acterID);
bool sBtlSetDamageProc(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr);
sdfVector4_t sBtlGetHitEffectPos(SKLID sklid, SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *acter);
bool sBtlGetHitUnit_Muki(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *acter);
bool sBtlSetHitback(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, u32 attr);
bool sBtlSetDamageBounce(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, u32 attr);
bool sBtlSetStoneDeadDamageProc(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr);
void sBtlSetDeadWeak(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, u32 attr);
bool sBtlSetDeadDamageProc(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr);
void sBtlSetInvalidDamage(SBTLUNIT_WORK *wk);
bool sBtlSetMukouDamage(SBTLUNIT_WORK *wk, u32 attr);
void sBtlSetAbsorbDamage(SBTLUNIT_WORK *wk, s32 damage, s32 addMag);
void sBtlSetOnlyDamage(SBTLUNIT_WORK *wk, s32 damage, SBTLDMG_HITWORK *hwk);
void sBtlSetNormalDamage(SBTLUNIT_WORK *wk, s32 damage, u32 attr, SBTLDMG_HITWORK *hwk);
void sBtlSetHuttobiDamage(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr);
void sBtlSetBomDamage(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr);
void sBtlSetDyingDamage(SBTLUNIT_WORK *wk, SKLID sklid, s32 damage, u32 attr, s32 acterID);
void sBtlDmg_BossDYING(SBTLUNIT_WORK *wk);
void sBtlSetStoneDeadDamage(SBTLUNIT_WORK *wk, s32 damage);
bool CheckAutoSkill(SBTLUNIT_WORK *wk);
bool sBtlIsEnemyLastOne(SBTLUNIT_WORK *wk);
bool sBtlSetDeadDamage(SBTLUNIT_WORK *wk, s32 damage, SKLID _SklId);
void sBtlSetSpecialDamage(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SKLID skillid, s32 damage);
void sBtlSetSpecialDamage_DamageOnly(SBTLUNIT_WORK *wk);
void sBtlSetDamage_L_EnemyAll(void);
bool sBtlDevilCheck_YASO(s32 id);
void sBtlWeakShildProc(SBTLUNIT_WORK *wk);
bool sBtlIsNoke(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *atkWk, u32 *attr);
bool sBtlIsSetuma(void);
void sBtlSetumaClear(void);
bool sBtlIsSetumaActive(void);
void sBtlNewHirumiMotion(SBTLUNIT_WORK *wk, s32 bframe);
void sBtlWinceProc(SBTLUNIT_WORK *wk);
void sBtlWinceDamage(SBTLUNIT_WORK *atkWk, SBTLUNIT_WORK *defWk, SBTLDMG_HITWORK *hwk);
void sBtlSetWinceStop(SBTLUNIT_WORK *wk, bool flag);
void sBtlSetWince_Full(SBTLUNIT_WORK *wk);
bool sBtlSetSuperArmor(SBTLUNIT_WORK *wk, SKLID skillid, s32 val);
void sBtlClrSuperArmor(SBTLUNIT_WORK *wk);
void sBtlClrSuperArmor2(SBTLUNIT_WORK *wk);
void sBtlProcSuperArmor(SBTLUNIT_WORK *wk);
