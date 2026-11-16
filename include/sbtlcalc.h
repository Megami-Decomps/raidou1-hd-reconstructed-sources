#pragma once
#include "types.h"
#include "AUTO.h"
#include "BST.h"
#include "BSTF.h"
#include "ITM.h"
#include "SBTLACTION_ST.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"

typedef enum {
    SBTL_MOON_0 = 0,
    SBTL_MOON_1 = 1,
    SBTL_MOON_2 = 2,
    SBTL_MOON_3 = 3,
    SBTL_MOON_4 = 4,
    SBTL_MOON_5 = 5,
    SBTL_MOON_6 = 6,
    SBTL_MOON_7 = 7,
    SBTL_MOON_8 = 8,
} SBTL_MOON;

typedef struct SBTLAISYO_DATAWORK SBTLAISYO_DATAWORK;
typedef struct SBTLCALC_DMGWORK SBTLCALC_DMGWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLSKL_KAJA_WORK SBTLSKL_KAJA_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct TEXCOLOR_WORK TEXCOLOR_WORK;
typedef struct sdatParaWork_t sdatParaWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct TEXCOLOR_WORK {
    f32 ratio;
    s32 mr;
    s32 mg;
    s32 mb;
    f32 rim_r;
    f32 rim_g;
    f32 rim_b;
    f32 rim_p;
    s8 flg;
};

struct SBTLCALC_DMGWORK {
    s16 alevel;
    s32 aatk;
    s32 atec;
    f32 ahp;
    f32 amaxhp;
    s32 gun_power;
    s32 sword_power;
    s16 tlevel;
    s32 tdef;
    s32 ttec;
    s32 tvit;
    s32 tluck;
    f32 thp;
    f32 tmaxhp;
    s16 n0;
    f32 n1;
    f32 damage_per;
    u8 side;
    SBTLAISYO_DATAWORK *aisyo_tbl;
};

extern SBTLAISYO_DATAWORK *aisyo_tbldata[544];
extern TEXCOLOR_WORK *bstcolor_tbldata;
extern TEXCOLOR_WORK *bstcolor_tbldata_raidou;

void sBtlDeleteShild(SBTLUNIT_WORK *wk, SKLID sklid, s32 del_raito);
u32 sBtlWeakShildActive(SBTLUNIT_WORK *wk, u32 attr, s32 acterID, SKLID sklid);
s32 sBtlGetWeakShildCount(SBTLUNIT_WORK *wk);
bool sBtlCheckBadStatus_Color(SBTLUNIT_WORK *wk, BST badstno);
bool sBtlSetBadStatus_Color(SBTLUNIT_WORK *wk, BST badstno);
void sBtlReetBadStatus_Color(SBTLUNIT_WORK *wk);
void sBtlSetBadStatusAction(SBTLUNIT_WORK *wk, SBTLACTION_ST st, s32 cnt);
void sBtlCheckBadStatus_Weak(SBTLUNIT_WORK *wk, SKLID sklid, SBTLSKILLP_TBL *ptbl, s32 acterID);
void sBtlSetHstatusWeak(SBTLUNIT_WORK *wk);
void sBtlSetHstatusWeakOld(SBTLUNIT_WORK *wk);
void sBtlResetItemPara(sdatUnitWork_t *unit);
bool sBtlAutoRec(SBTLUNIT_WORK *wk, s32 para);
bool sBtlCheckBadStatus_BossSkill(SKLID sklid);
void sBtlCheckD3POff(SBTLUNIT_WORK *wk, BST bstno);
s32 CalcItem_Battle(SBTLUNIT_WORK *wklock, sdatUnitWork_t *unit, s32 itemid);
bool sBtlCheckBadStatus_WeakNumber(SBTLUNIT_WORK *wk, BST bstno);
bool sBtlSetAutoSkill_GBID(sdatUnitWork_t *unit, AUTO autono, SKLID sklId);
s32 sBtlGetDamage_ATK(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_C_ATK1(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_C_GUN(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_GUN(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_C_MAGIC(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_MAGIC(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_NHP(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_REC_P(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s8 flg);
s32 sBtlGetDamage_ATK_MG(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_Slip(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID skillid, s32 damage, SBTLUNIT_SIDE side);
s32 sBtlGetDamage_Barrier(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID sklid);
s32 sBtlGetDamage_The_W(SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID);
s32 sBtlGetDamage_Tadan(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID skillid, s32 damage, s32 actID);
s32 sBtlGetDamage_ParaUP(SBTLUNIT_WORK *unit, SKLID skillid);
s32 sBtlGetDamage_I_REC_K(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s8 flg);
s32 sBtlGetDamage_I_REC_P(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s8 flg);
s32 sBtlGetDamage_I_REC_PARA(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamege_I_EXP(sdatUnitWork_t *unit, ITM _itmID);
s32 sBtlGetDamage_P_STR(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid);
s32 sBtlGetDamage_P_VIT(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid);
s32 sBtlGetDamage_P_TEC(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid);
s32 sBtlGetDamage_P_LUCK(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid);
s32 sBtlGetDamage_CHUUSEI(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlGetDamage_ITEMFLG(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid);
s32 sBtlGetDamage_Escape(sdatUnitWork_t *unit);
bool sBtlResetUnit(SBTLUNIT_WORK *wklock, s32 bstno);
bool sBtlCheckJyuso_GB(void);
bool sBtlCheckItemCost_GBWK(s32 itemid, s32 flg);
bool sBtlCheckItemCost(s32 itemid, s32 flg);
void sBtlSetWeakBit(s32 devilid);
bool sBtlCheckItemMember_Dead(s32 index);
bool sBtlCheckItemMember(s32 index);
void sBtlSetBadStatus(sdatUnitWork_t *unit, s32 bstno);
s32 sBtlUpdateBadStatusNo(s32 bstno);
void sBtlSetBadStatusRand(sdatUnitWork_t *unit, SKLID sklid);
s32 CalcItem(sdatUnitWork_t *unit, s32 itemid);
void sBtlResetItemFlg(sdatUnitWork_t *unit);
s32 sBtlCheckDrink(void);
bool sBtlCheckItemCount(sdatUnitWork_t *unit);
bool sBtlCheckHaveskill_Atk(sdatUnitWork_t *unit);
bool sBtlCheckHaveskill_Magic(sdatUnitWork_t *unit);
bool sBtlCheckHaveskill_Rec(sdatUnitWork_t *unit);
bool sBtlCheckAutoSkill(sdatUnitWork_t *unit, s8 flg);
bool sBtlCheckAutoSkill_Enemy(SBTLUNIT_WORK *wk);
bool sBtlSetAutoSkill(SBTLUNIT_WORK *wk);
bool sBtlSetRaidouKuisibari(SBTLUNIT_WORK *wk);
bool sBtlSetAutoSkill_GB(sdatUnitWork_t *unit);
bool sBtlSetAutoSkill_ID(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlResetAutoSkill(sdatUnitWork_t *unit);
bool sBtlGetSpiritSkillChk(SKLID sklid);
AUTO sBtlGetAutoSkillPara(SKLID sklid, s16 *para1, s16 *para2);
SKLID sBtlGetAutoSkill_ID(sdatUnitWork_t *unit, s32 id);
bool sBtlCheckAutoSkill_ActerDamage_ID(SKLID sklid);
bool sBtlCheckAutoSkill_TargetDamage_ID(SKLID sklid);
bool sBtlCheckAutoSkill_ActerDamage(AUTO autono);
bool sBtlCheckAutoSkill_TargetDamage(AUTO autono);
bool sBtlCheckAutoSkill_Action(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 attr);
s32 CalcAutoSkill(sdatUnitWork_t *unit, AUTO autono, s32 damage, SKLID skillid, s32 para1, s32 para2);
s32 sBtlGetDropMoney(sdatUnitWork_t *unit, s32 gold);
bool sBtlCheckMoon(SBTL_MOON moon);
s32 sBtlGetSkillCost(sdatUnitWork_t *a_pUnit, SKLID a_skillid);
s32 sBtlGetMagCost(sdatUnitWork_t *player, sdatUnitWork_t *unit, s32 devilid);
bool sBtlCheckUseSkill(SBTLUNIT_WORK *wk, SKLID sklid);
bool sBtlCheckMagCost_GB(sdatUnitWork_t *player, sdatUnitWork_t *unit, s32 devilid, s8 flg);
bool sBtlCheckMagCost(sdatUnitWork_t *unit, s32 devilid, s8 flg);
bool sBtlCheckCost2(SBTLUNIT_WORK *wk, SKLID sklid, s32 flg);
bool sBtlCheckCost(SBTLUNIT_WORK *wk, s32 flg);
bool sBtlCheckCost_SkillID(SBTLUNIT_WORK *wk, SKLID skillid, s32 flg);
void sBtlDecVice(SBTLUNIT_WORK *wk, s32 vice);
void sBtlDecMag(s32 mag);
s32 sBtlPerDecMag(s32 per);
void sBtlAddMag(s32 mag);
void sBtlDecHP(SBTLUNIT_WORK *wk, s32 para);
void sBtlDecMP(SBTLUNIT_WORK *wk, s32 para);
void sBtlDecItem_GBWK(s32 itemid);
void sBtlDecItem(s32 index, s32 itemid);
void sBtlSetGunNum(s32 para);
void sBtlDecGunNum(s32 para);
s32 sBtlGetGun_Num(void);
SBTLAISYO_DATAWORK *sBtlGetAisyotbl(s32 id);
bool sBtlCheckAttrFlg(s32 id, u32 attr, u32 attrnum);
s32 sBtlGetAttr(u32 attr);
u32 sBtlCheckAisyo_Old(SBTLAISYO_DATAWORK *aisyo_tbl, u32 attr);
u32 sBtlCheckAisyoEx(SBTLUNIT_WORK *a_pUnit, u32 a_SkillAttr, s32 *a_pHanshaType);
bool sBtlGetParameter_Rsc(SBTLUNIT_WORK *wk, sdatParaWork_t *para);
s32 sBtlCheckRecoverData(sdatUnitWork_t *unit, s32 para, s32 flg, bool revival);
s32 sBtlCheckKuishibari(SBTLUNIT_WORK *wk, s32 para);
bool sBtlKuisibariBstChk(BST bstno);
bool sBtlKuisibariChk(SBTLUNIT_WORK *_wk);
bool sBtlNakamaKuisibariChk(SBTLUNIT_WORK *_wk);
bool sBtlCheckNakamaKuisibari(SBTLUNIT_WORK *_wk, SKLID _sklID);
void sBtlSetNakamaKuisibari(SBTLUNIT_WORK *_wk, SKLID _sklID);
bool sBtlSeikatuChk(void);
bool sBtlSeikatuUseChk(void);
bool sBtlCheckSpecialDamage_Stop(SBTLUNIT_WORK *wk);
bool CalcBtlMagicStatus(SBTLUNIT_WORK *wk);
bool sBtlCheckBadStatus_Return(s32 idx);
BST sBtlGetBadStatus(sdatUnitWork_t *unit);
bool sBtlIsKoufun(sdatUnitWork_t *unit);
bool CalcBadStatus(SBTLUNIT_WORK *wk);
void sBtlKudaHuuinCheck(void);
void sBtlKudaHuuin_AllOn(bool _InfTime);
void sBtlKudaHuuin_AllOff(void);
bool sBtlResetBadStatus_GB(sdatUnitWork_t *unit, BSTF flg);
bool sBtlResetBadStatus(SBTLUNIT_WORK *wk, BSTF flg);
s32 sBtlGetBadStatus_Attr(BST bstno);
void sBtlCheckResetBadStatus(SBTLUNIT_WORK *wk);
s32 sBtlCheckBadStatus(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *wk, SKLID sklid, s32 flg);
bool sBtlCanWeakBstAttach(SBTLUNIT_WORK *wk, BST bstno);
bool sBtlCheckBadStatus_Number(u32 badstatus, s32 bstno, SBTLUNIT_WORK *wk);
void sBtlSetBadStatus_Effect(SBTLUNIT_WORK *wk, BST bstno);
bool sBtlSetBadStatus_No(SBTLUNIT_WORK *wk, SKLID sklid, BST badstno, s32 flg, s32 acterID);
TEXCOLOR_WORK *sBtlGetBSTColortbl(SBTLUNIT_WORK *wk, BST badstno);
bool sBtlCheckBadStatus_Hit(SBTLAISYO_DATAWORK *aisyo_tbl, s32 aluck, sdatUnitWork_t *unit, s32 tluck, SKLID skillid, BST bstno, s32 attr, u8 side, sdatUnitWork_t *atkunit);
s32 sBtlGetDamage_GB(sdatUnitWork_t *acter, sdatUnitWork_t *target, SKLID skillid);
void sBtlKudaDmg(s8 kuda, s32 *pDmg);
void sBtlFullMoonDmg(s32 *pDmg, SBTLUNIT_WORK *pAtkr);
void sBtlZokuseiDmg(s32 *pDmg, SBTLUNIT_WORK *pTgt, s32 attr);
s32 sBtlGetDamage(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *target, SBTLDMG_HITWORK *hwk, SKLID skillid, u32 attr, bool calc_only);
bool sBtlIsDamageCorrection(SBTLUNIT_WORK *wk);
void sBtlResetBattlePara(SBTLUNIT_WORK *wk, s32 index);
void sBtlGetPlayerTec_ParaUp(sdatUnitWork_t *unit, sdatParaWork_t *data);
void sBtlCheckBattlePara(SBTLUNIT_WORK *wk);
void CalcAisyo(SBTLUNIT_WORK *wk);
void sBtlKudanAisyo(SBTLUNIT_WORK *wk);
s32 sBtlGetDamage_MRecover(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl);
s32 sBtlCheckRegistKaja(SBTLSKL_KAJA_WORK *a_pKaja, SBTLSKILLP_TBL *a_pSkill);
bool sBtlCheckRegistKajaMaxNewAI(SBTLSKL_KAJA_WORK *a_pKaja, SBTLSKILLP_TBL *a_pSkill);
bool sBtlRegistKaja(SBTLUNIT_WORK *wk, SBTLSKL_KAJA_WORK *a_pKaja, SBTLSKILLP_TBL *a_pSkill);
s32 sBtlGetViceLevel(s32 vice);
s32 sBtlGetViceLevelValue(s32 lvl);
bool sBtlIsUseVice(SBTLUNIT_WORK *wk, SKLID sklId);
void sBtlUseVice(SBTLUNIT_WORK *wk, s32 use_cost);
void sBtlRecalcAisyoMember(SBTLUNIT_WORK *wk);
