#pragma once
#include "types.h"
#include "GaugeType.h"
#include "SKLID.h"

typedef struct SBTLEXP_LISTWORK SBTLEXP_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sdatUnitWork_t sdatUnitWork_t;

extern s32 *riritutbl_e;
extern GaugeType *vice_gage_type;

s32 sBtlGetRiritutbl_n(SBTLUNIT_WORK *wk, s32 mode);
s32 sBtlCalcWeakTime(SBTLUNIT_WORK *wk, s32 iKouchoku);
s32 sBtlCalcHuumaW(SBTLUNIT_WORK *wk, s32 gage_w);
GaugeType sBtlCalcHuumaType(SBTLUNIT_WORK *wk);
void sBtlCheckDropItem_Limit(void *reward, s32 item_cnt);
SBTLEXP_LISTWORK *sBtlCreateEXPList(void);
void sBtlInitDropWork(void);
void sBtlGetAutoSkillPoint(void);
void sBtlGetChuuseiPoint(void);
s32 sBtlGetSpecialExp(void);
s32 sBtlGetSpecialMoney(void);
s32 sBtlGetExp_ChkMemSkl(s32 a_exp, sdatUnitWork_t *a_pUnit);
s32 sBtlGetChuusei_ChkMemSkl(s32 a_chuusei, sdatUnitWork_t *a_pUnit);
void sBtlCheckDropItem(void *a_pReward);
bool sBtlCheckGetExpUnit(sdatUnitWork_t *unit);
void sBtlCheckDrop(void);
void sBtlCheckDrop_Normal(SBTLUNIT_WORK *wk);
s32 sBtlGetExpHosei(s32 getexp);
void DecVice(SBTLEXP_LISTWORK *lwk, s32 para);
void sBtlSetVicePara(SBTLEXP_LISTWORK *lwk, s32 para);
void sBtlResetVicePara(SBTLEXP_LISTWORK *lwk);
s32 GetViceLevel(void);
bool sBtlSetRiritu(SBTLEXP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID, u16 mode);
bool sBtlSetRirituNakamaHD(SBTLEXP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID, u16 mode);
void sBtlViceAddNakamaHD(SBTLUNIT_WORK *wk, s32 add, s16 min, s16 max);
void sBtlSpiritWazaAdd(s32 add, s32 min, s32 max);
s32 sBtlGetSpiritWazaLevel(void);
void sBtlClrSpiritWaza(void);
void sBtlSpiritAddDirect(SBTLUNIT_WORK *wk, s32 mode);
void sBtlRwazaSpiritAdd(void);
void sBtlSetumaSpiritAdd(s32 mode);
void sBtlRecoverSpiritAdd(SBTLUNIT_WORK *wk, s32 mode, SKLID sklid);
void sBtlKofunSpiritAdd(SBTLUNIT_WORK *wk, s32 mode, SKLID sklid);
bool sBtlIsSpiritWaza(void);
bool sBtlIsSpiritWazaAndEnemyLive(void);
void sBtlEnemyViceInit(void);
void sBtlNakamaViceInit(SBTLUNIT_WORK *_unit);
bool sBtlSetRirituEnemyHD(SBTLEXP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID, s32 mode);
void sBtlEnemyViceKoufun(s32 oldlevel, s32 nowlevel);
void sBtlViceAddEnemyHD(SBTLUNIT_WORK *wk, s32 add, s16 min, s16 max);
bool Proc(SBTLEXP_LISTWORK *lwk);
bool sBtlDraw(SBTLEXP_LISTWORK *lwk);
bool sBtlReleaseEXP_List(SBTLEXP_LISTWORK *lwk, u8 flg);
bool sBtlDeleteEXPList(SBTLEXP_LISTWORK *lwk);
