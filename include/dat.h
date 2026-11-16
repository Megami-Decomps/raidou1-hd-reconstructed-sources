#pragma once
#include "types.h"
#include "SKLID.h"

typedef enum {
    dvl1Combi1 = 0,
    dvl1Combi2 = 1,
    dvl2Combi1 = 2,
    dvl2Combi2 = 3,
} CombiSetting;

typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct __BTLAICHKWK __BTLAICHKWK;
typedef struct __BTLAITBLWK __BTLAITBLWK;
typedef struct datCalcBase_t datCalcBase_t;
typedef struct datCalcMakka_t datCalcMakka_t;
typedef struct datDevilAI_t datDevilAI_t;
typedef struct datEncountBGBG_t datEncountBGBG_t;
typedef struct datEncountBG_t datEncountBG_t;
typedef struct datEncountCheck_t datEncountCheck_t;
typedef struct datEncountFld_t datEncountFld_t;
typedef struct datEncountPack_t datEncountPack_t;
typedef struct datEncountRare_t datEncountRare_t;
typedef struct datEncountRitu_t datEncountRitu_t;
typedef struct datEncountTbl_t datEncountTbl_t;
typedef struct datEncount_t datEncount_t;
typedef struct datFldHuntGenDvTbl_t datFldHuntGenDvTbl_t;
typedef struct datFldHuntTbl_t datFldHuntTbl_t;
typedef struct datItem_t datItem_t;
typedef struct datLinkageSkillList_t datLinkageSkillList_t;
typedef struct datLinkageSkillVisual_t datLinkageSkillVisual_t;
typedef struct datLinkageSkill_t datLinkageSkill_t;
typedef struct datNormalSkillVisual_t datNormalSkillVisual_t;
typedef struct datNormalSkill_t datNormalSkill_t;
typedef struct datPlayerAttackGun_t datPlayerAttackGun_t;
typedef struct datSkill_t datSkill_t;
typedef struct datSpecialSkill_t datSpecialSkill_t;
typedef struct datTakaraSagasiI_t datTakaraSagasiI_t;
typedef struct datTakaraSagasiT_t datTakaraSagasiT_t;
typedef struct datTakaraSagasi_t datTakaraSagasi_t;
typedef struct datUnitCamera_t datUnitCamera_t;
typedef struct datUnitMotEnd_t datUnitMotEnd_t;
typedef struct datUnitMotHokan_t datUnitMotHokan_t;
typedef struct datUnitMotionSE_t datUnitMotionSE_t;
typedef struct datUnitMotion_t datUnitMotion_t;
typedef struct datUnitSe_t datUnitSe_t;
typedef struct datUnitVisual_t datUnitVisual_t;
typedef struct datUnitWork_t datUnitWork_t;
typedef struct dds3GlobalWork_t dds3GlobalWork_t;
typedef struct sdatLvUpPlayerParamUp_t sdatLvUpPlayerParamUp_t;
typedef struct sdatLvUpPlayerRankUp_t sdatLvUpPlayerRankUp_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct __BTLAICHKWK {
    u32 check[3];
    u8 table_no[8];
};

struct __BTLAITBLWK {
    u8 probability;
    u16 skillid;
    u32 targetcode;
};

struct datDevilAI_t {
    u8 escape_flag;
    u16 scriptid;
    __BTLAICHKWK *aichk[3];
    __BTLAITBLWK *aitable[7];
    u16 deadscriptid;
    u16 deadeventno;
};

struct datCalcMakka_t {
    s8 level;
    f32 ratio;
};

struct datCalcBase_t {
    f32 maxMG[99];
    f32 maxSP[99];
    f32 hunt[8];
    f32 fear[11];
    f32 hitBUTURI[99];
    f32 hitMAGIC[99];
    f32 critical[99];
    s32 gunBad[32];
    s32 item[14];
    f32 preemptive[7];
    u8 expLevel;
    f32 expRatio;
    f32 apTurn[16];
    datCalcMakka_t *makkaLevel[10];
    f32 *apLevel[31];
};

struct datUnitMotEnd_t {
    s16 type;
    s16 frame;
};

struct datUnitMotHokan_t {
    s16 bframe;
    s16 hframe;
};

struct datUnitMotion_t {
    s16 movetype;
    u16 actframe;
    datUnitMotEnd_t *end;
    f32 motionsp;
    f32 atarisize;
    datUnitMotHokan_t *hokan;
};

struct datUnitVisual_t {
    sdfVector4_t center;
    f32 formscale;
    f32 addz;
    f32 formsize;
    f32 formheight;
    f32 oneshotr;
    f32 allshotr;
    u16 shadowsize;
    u16 badframe;
    datUnitMotion_t *motion[29];
};

struct datUnitCamera_t {
    sdfVector4_t center;
    f32 radius;
    f32 height;
};

struct datUnitSe_t {
    s16 no;
    u16 frame;
};

struct datUnitMotionSE_t {
    datUnitSe_t *se[29];
};

struct datEncount_t {
    s8 esc;
    u8 item;
    u8 itemcnt;
    u16 serial;
    u16 devil[11];
    u16 stageid;
    u16 areaid;
    u16 flag;
    u8 maxparty;
    u8 maxcall;
    u16 btlsound;
    u16 event;
};

struct datEncountCheck_t {
    u32 check[3];
    u8 table_no[8];
};

struct datEncountRitu_t {
    u16 encountid;
    u16 ritu;
    s8 sensei;
    u8 renzokuritu;
};

struct datEncountTbl_t {
    s32 normalritu;
    datEncountRitu_t *ritu[20];
};

struct datEncountPack_t {
    u16 stageid;
    u16 areaid;
    u16 btlsound;
    datEncountCheck_t *enccheck;
    datEncountTbl_t *enctable[4];
};

struct datEncountRare_t {
    s16 fld;
    s16 flag;
    s16 par;
    s16 pack;
};

struct datEncountBGBG_t {
    s32 bg0;
    s16 flg1;
    s16 bg1;
    s16 flg2;
    s16 bg2;
};

struct datEncountBG_t {
    s32 fld;
    datEncountBGBG_t *bg[64];
};

struct datFldHuntGenDvTbl_t {
    s32 Num;
    s8 Point[8];
    s32 Ap;
};

struct datFldHuntTbl_t {
    s16 Field;
    s16 Area;
    s32 GenMax;
    s32 Time;
    s16 EncountID;
    s16 Mitama;
    datFldHuntGenDvTbl_t *Dv[16];
};

struct datSkill_t {
    s8 skillattr;
    s8 type;
};

struct datNormalSkill_t {
    u8 flag;
    u8 use;
    u8 koukatype;
    u8 costtype;
    u16 cost;
    u16 costbase;
    u8 targettype;
    u8 targetarea;
    u8 targetrule;
    u8 targetrandom;
    u16 untargetbadstat;
    u16 targetprog;
    u8 hittype;
    u8 hitratio;
    u16 hitprog;
    u8 targetcntmin;
    u8 targetcntmax;
    u16 hptype;
    s16 hpn;
    u16 mptype;
    s16 mpn;
    s16 hpbase;
    s16 mpbase;
    u16 minus;
    u8 badtype;
    u8 badratio;
    u16 badstatus;
    u32 hojotype;
    s8 hojopoint;
    u8 huntratio;
    u16 countertype;
    u32 program;
    s16 criticalratio;
    s16 damagemax;
};

struct datLinkageSkill_t {
    u32 combi[3];
    s8 gauge;
    u16 flag;
};

struct datLinkageSkillList_t {
    s16 skillID[16];
};

struct datNormalSkillVisual_t {
    u8 motion;
    u8 animetype;
    u8 hansya;
    u8 hatudo;
    u16 bedno;
    sdfVector4_t light;
    u32 filter;
    u16 camera;
};

struct datLinkageSkillVisual_t {
    u8 cut23_mot;
    u16 formation;
    u8 atari_mot[3];
};

struct datSpecialSkill_t {
    f32 f;
    s16 a;
    s16 b;
};

struct datItem_t {
    u8 use;
    u8 flag;
    u16 skillid;
    u32 price;
};

struct datPlayerAttackGun_t {
    s16 power;
    u8 hitratio;
    u8 critical;
    f32 badratio;
    u8 targettype;
    u8 targetarea;
    u8 targetrule;
    u8 targetrandom;
    u16 untargetbadstat;
    u8 gun_min;
    u8 gun_max;
    u8 gun_frame;
    u8 attack_cnt;
    u8 attack_frame;
};

struct datTakaraSagasiI_t {
    u16 item;
    u16 par;
};

struct datTakaraSagasiT_t {
    u32 flag;
    datTakaraSagasiI_t *itemtbl[8];
};

struct datTakaraSagasi_t {
    u32 flag;
    datTakaraSagasiT_t *tbl[4];
};

extern datUnitWork_t *PlayerUnitWork;
extern u32 *AtmaAisyo;
extern u32 *HumanAisyo;
extern datUnitVisual_t *PlayerVisual;
extern datUnitMotionSE_t *PlayerMotSE;
extern datPlayerAttackGun_t *PlayerAttackGun;
extern datUnitVisual_t *DevilVisual;
extern datDevilAI_t *DevilAI;
extern datUnitMotionSE_t *DevilMotSE;
extern u32 *datDevilAisyo;
extern datUnitCamera_t *datDevilCamera;
extern datEncount_t *Encount;
extern datEncountFld_t *EncountFld;
extern datEncountPack_t *EncountPack;
extern datEncountRare_t *EncountRare;
extern datEncountBG_t *EncountBG;
extern datFldHuntTbl_t *FldHuntTbl;
extern datSkill_t *Skill;
extern datNormalSkill_t *NormalSkill;
extern datLinkageSkill_t *LinkageSkill;
extern datLinkageSkillList_t *LinkageSkillList;
extern datSpecialSkill_t *SpecialSkill;
extern datNormalSkillVisual_t *NormalSkillVisual;
extern datLinkageSkillVisual_t *LinkageSkillVisual;
extern datItem_t *Item;
extern datCalcBase_t *CalcBase;
extern u8 *PlayerName;
extern u8 *DevilName;
extern u8 *AtmaName;
extern u8 *AtmaAisyoName;
extern u8 *DevilAisyoName;
extern u8 *ItemName;
extern u8 *RaceName;
extern u8 *SkillName;
extern u8 *MahenName;
extern u8 *MashoName;
extern u8 *SkillHelp;
extern u8 *ItemHelp;
extern u8 *ActionMiscHelp;
extern u8 *JyokyoHelp;
extern char *ai_scr;
extern char *calc_scr;
extern s32 datEncountBase;
extern datTakaraSagasi_t *TakaraSagasi;
extern u8 *HeartsHelp;
extern u8 *PlayerRaceName;
extern u8 *HeartsName;
extern void *sdatLvUpDevilGiftTbl;
extern void *sdatLvUpDevilGiftTbl_DLC;
extern s32 sdatLvUpDevilGiftSize;
extern s32 sdatLvUpDevilParamUpSize;
extern sdatLvUpPlayerParamUp_t *sdatLvUpPlayerParamUp;
extern s32 sdatLvUpPlayerParamUpSize;
extern sdatLvUpPlayerRankUp_t *sdatLvUpPlayerRankUp;
extern s32 sdatLvUpPlayerRankUpSize;
extern s32 gohDevilParamSize;
extern u16 *gohSameDevils;
extern s32 gohSameDevilsSize;
extern void *gohKarteWakuSetting;
extern s16 *s_aSummonerRankTbl;
extern dds3GlobalWork_t *GBWK;
extern s32 gb_btltime;
extern s32 gb_btlaitime;

void datInitPlayer(void);
s32 datGetPlayerParam(s32 id);
void datSetPlayerParam(s32 id, s32 nums);
s32 datGetStockDevilID(s32 Index);
u32 datGetStockUniqCode(s32 Index);
void datDlcNoneCheck(void);
s32 datAdjustStock(bool _stack);
s32 datGetEmptyStockCnt(void);
s32 datGetEmptyStock(void);
s32 datCheckSameDevil(s32 DevilID);
void *datGetSameStockIndexList(s32 _devilID);
s32 datGetStockDevilIndex(s32 DevilID, u32 UniqCode);
s32 datGetStockAliveDevilNum(void);
s32 datGetStockDevilNums(bool dlc);
s32 datGetStockReprtStok(void);
DEVILDATA_WORK *datGetDevilFormat(s32 iDevilID);
s32 datGetKudaRace(s32 DevilID);
s32 datCheckSkillType(SKLID SkillID);
bool datCheckSkillPhysicDamage(SKLID SkillID);
bool datCheckSkillMagicDamage(SKLID SkillID);
bool datCheckSkillGunDamage(SKLID SkillID);
SKLID datGetDefaultSkill(s32 DevilID, s32 SkillType);
s32 datCheckHaveSkill(sdatUnitWork_t *pUnit, SKLID SkillID);
s32 datCheckHaveSkillCnt(sdatUnitWork_t *pUnit);
s32 datCheckRsvSkillCnt(sdatUnitWork_t *pUnit);
s32 datCheckSkillEnable(sdatUnitWork_t *pUnit, SKLID SkillID);
s32 datGetSkillCopyIndex(s32 SkillType);
void datReplaceHaveSkill(sdatUnitWork_t *pUnit);
s32 datAddSkill(sdatUnitWork_t *pUnit, SKLID SkillID);
void datCreateDevilUnitEx(s32 DevilID, s32 SkillMode, sdatUnitWork_t *pUnit, s32 uniqCode);
void datCreateDevilUnit(s32 DevilID, sdatUnitWork_t *pUnit);
s32 datAddCheckDevilUnit(sdatUnitWork_t *pUnit);
s32 datAddDevilUnit(sdatUnitWork_t *pUnit);
s32 datAddDevilEx(s32 DevilID, s32 SkillMode);
s32 datAddDevil(s32 DevilID);
s32 datDelDevil(s32 DevilID, u32 UniqCode);
void datNewCombiSkilAutoSet(sdatUnitWork_t *_unit);
void datCombiSkilAutoSet(sdatUnitWork_t *_unit, SKLID _skl);
SKLID datGetCombiSkillSetting(CombiSetting _setting);
SKLID datGetDvlCombiSetting(sdatUnitWork_t *_unit, s32 _index);
void datLoadLevelUpTable(void);
void datLoadGohmadenTable(void);
s32 datGetPlayerExp(s32 Level);
s32 datGetPlayerLevelUpNums(sdatPlayerUnitWork_t *pUnit);
s32 datGetPlayerMaxHP(sdatUnitWork_t *pParam);
void datGetPlayerOnceLevelUpParam(sdatPlayerUnitWork_t *pUnit, s32 Level);
s32 datGetPlayerLevelUpParam(sdatPlayerUnitWork_t *pDstUnit, sdatPlayerUnitWork_t *pSrcUnit);
void datGetPlayerLevelUpUnit(sdatPlayerUnitWork_t *pDstUnit, sdatPlayerUnitWork_t *pSrcUnit);
s32 datGetDevilExp(s32 DevilID, s32 Level);
s32 datGetDevilLevelUpNums(sdatUnitWork_t *pUnit);
s32 datGetDevilMaxHP(sdatUnitWork_t *pUnit, sdatPlayerUnitWork_t *_player);
s32 datGetDevilMaxMP(sdatUnitWork_t *pUnit);
void datGetDevilOnceLevelUpParam(sdatUnitWork_t *pUnit);
s32 datGetDevilLevelUpParam(sdatUnitWork_t *pDstUnit, sdatUnitWork_t *pSrcUnit);
void datGetDevilLevelUpUnit(sdatUnitWork_t *pDstUnit, sdatUnitWork_t *pSrcUnit);
void datCalcDevilMaxParCheck(sdatUnitWork_t *pUnit);
void datDvlParaUpdate(sdatPlayerUnitWork_t *player);
void datCalcNowParam(sdatUnitWork_t *pUnit, s32 SwordID, sdatPlayerUnitWork_t *_player);
s32 datGetSword4Param(s32 SwordID, s32 Type);
s32 datGetSwordParamHP(s32 SwordID);
s32 datGetSwordAisyoEx(s32 SwordID);
s32 datGetSwordAisyo(void);
u32 datCheckStrongSwordDevil(s32 DevilID);
s32 datCheckStrongSwordAttack(s32 SwordID);
s32 datSetPlayerUnitSword(sdatPlayerUnitWork_t *pUnit, s32 SwordID, sdatUnitWork_t *pDevil);
s32 datSetPlayerSword(s32 SwordID, sdatUnitWork_t *pDevil);
bool datCheckDying(sdatUnitWork_t *pUnit);
void datAddMoney(s32 add);
bool datCheckMoney(s32 money);
bool datCheckEventItem(s32 id);
s32 datCalcGetItemNum(s32 id);
void datAddItem(s32 id, s32 num);
bool datCheckItem(s32 id, s32 num);
s32 datGetItemNum(s32 id);
s32 datGetItemMaxNum(s32 id);
void datAddMag(s32 add);
bool datCheckMag(s32 num);
void datPartyRecovery(void);
void datPartyDevilRecovery(s32 devilid);
s32 datGetTotalCyuusei(sdatUnitWork_t *pUnit);
void datAddTotalCyuusei(sdatUnitWork_t *pUnit, s32 Val);
void datPartyDamageMap(s32 mode);
bool datCheckBadPartyMap(s32 bad);
void datResetBadStat(sdatUnitWork_t *pWork, u32 badstat);
s32 datDebtFromGouto(s32 money);
u32 datGetSummonerRank(void);
bool datChkCard(s16 devilid);
void datSetCard(s16 devilid);
void datAddStock(s32 nums);
void datSetSummonerRank(u32 uRank);
s32 datGetSummonerRankNum(void);
void datCalcLuckParam(void);
s32 datSklDrawMaxCnt(sdatUnitWork_t *pWork);
s32 datSklItmDrawMaxCnt(sdatUnitWork_t *pWork);
bool datOmoideSkillGetMaster(sdatUnitWork_t *pWork, SKLID uSkillNo);
bool datSwordSklGetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo);
bool datSpiritSkillGetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo);
bool datRaidouSkillGetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo);
bool datOmoideSkillHaveSkill(sdatUnitWork_t *pWork, SKLID uSkillNo);
bool datSpiritSkillHaveSkill(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo);
void datOmoideSkillSetMaster(sdatUnitWork_t *pWork, SKLID uSkillNo, bool bFlag);
s8 *datOmoideSkillDelOfcSkl(sdatUnitWork_t *_unit);
void datSpiritSkillSetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo, bool bFlag);
void datRaidouSkillSetMaster(sdatPlayerUnitWork_t *pWork, SKLID uSkillNo, bool bFlag);
s32 datSpiritSkillGetCount(sdatPlayerUnitWork_t *pWork);
s32 datRaidouSkillGetCount(sdatPlayerUnitWork_t *pWork);
s32 datOmoideSkillSetCnt(sdatUnitWork_t *pWork);
s32 datOmoideSkillGetCount(sdatUnitWork_t *pWork);
bool datOmoideSkillIsComplete(sdatUnitWork_t *pWork);
bool datSpiritSkillIsComplete(sdatPlayerUnitWork_t *pWork);
bool datRaidouSkillIsComplete(sdatPlayerUnitWork_t *pWork);
s32 datRaidouSkillIsRegCnt(sdatPlayerUnitWork_t *pWork);
bool datChkSpiritSkl(SKLID _sklID);
bool datChkKeisyouSkl(s32 _devilID, SKLID _skl);
SKLID *datRemoveOfcSkl(SKLID **_sklList, void *_itemList);
void datRemoveNoneSkl(SKLID **_sklList);
void *datRcvSklNoneIndex(sdatUnitWork_t *_unit);
void datGetTmpSklDelHaveSkl(sdatUnitWork_t *_pUnit);
void datGetTmpDelOmoideSkl(sdatUnitWork_t *_pUnit);
s32 datCalcEnemyToNakamaID(s32 enemyID);
s32 datFieldGetAutoSkillNum(s32 skillid);
bool datFieldChkDevilAutoSkill(s32 devilid, s32 skillid);
s32 datGetPlayerStance(void);
s32 datGetPlayerStanceNum(void);
void datAddPlayerStance(s32 num);
bool datCheckItemFull(s32 id);
void datCalcMagMaxPlayerUnit(sdatPlayerUnitWork_t *pUnit);
void datCalcMagMax(void);
s32 datCommand_GET_DEVIL_NUMS(void);
s32 datCommand_GET_DEVIL_ID(void);
s32 datCommand_GET_LIVE_DEVIL_NUMS(void);
s32 datCommand_GET_LIVE_DEVIL_ID(void);
s32 datCommand_CHK_DEVIL_SKILL(void);
s32 datCommand_DEVIL_IN(void);
s32 datCommand_DEVIL_OUT(void);
s32 datCommand_STOCK_DEVIL_OUT(void);
s32 datCommand_DEVIL_OUT_AFTER(void);
s32 datCommand_GET_STOCK_MAX(void);
s32 datCommand_GET_INC_STOCK(void);
s32 datCommand_INC_STOCK(void);
s32 datCommand_DEBT_FROM_GOUTO(void);
s32 datCommand_GET_SUMMONERRANK_NUM(void);
void datGlobalWorkInit(void);
void datGlobalWorkDestroy(void);
void datGlobalWorkUserInit2(s32 mode);
