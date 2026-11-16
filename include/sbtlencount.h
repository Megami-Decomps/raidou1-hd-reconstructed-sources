#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SB_ENCOUNT1 SB_ENCOUNT1;
typedef struct SB_ENCOUNTPAC SB_ENCOUNTPAC;
typedef struct SB_GENERATOR_WORK SB_GENERATOR_WORK;
typedef struct SB_RNDENCPAC SB_RNDENCPAC;
typedef struct SB_RNDENC_DEVILINFO SB_RNDENC_DEVILINFO;
typedef struct datRndEncRitu_t datRndEncRitu_t;
typedef struct datRndEncTbl_t datRndEncTbl_t;

struct SB_RNDENCPAC {
    datRndEncTbl_t *rndenctbl[3];
};

struct SB_GENERATOR_WORK {
    s32 use;
    s16 zan_cnt;
    s16 type_d_sommon_flg;
    s32 wait;
    SB_ENCOUNT1 *penc;
};

extern s32 g_pac_id;
extern s32 g_rndenc1_map;
extern s32 g_rndenc1_floor;
extern u32 encountcnt;
extern s32 datRndEncBase;
extern s32 encmax;
extern SB_GENERATOR_WORK *sb_gen_work;
extern s32 sb_gen_d_flag;
extern bool sb_gen_e_zenmetu;

void sBtlInitEncountPac(void *tbl, s32 dlc_no);
void sBtlInitEncountPacDlc(s32 dlc_no);
SB_ENCOUNTPAC *sBtlGetEncountPac(s32 dlc_no);
s32 sBtlGetDlcMapNo(void);
void sBtlInitRndEncPac(void *tbl, s32 dlc_no);
void sBtlInitRndEncPacDlc(s32 dlc_no);
SB_RNDENCPAC *sBtlGetRndEncPac(s32 dlc_no);
datRndEncTbl_t *sBtlGetRndEncTbl_t(s32 id, s32 tbl);
bool sBtlSetGeneratorData(s32 encountno);
bool sBtlGetPointData(s32 pointID, sdfVector4_t *pos, sdfVector4_t *rot);
void sBtlSetExPos(const sdfVector4_t *pos, const sdfVector4_t *rot);
bool sBtlSetEncountPacData(s32 encountpac_no);
SBTLUNIT_WORK *sBtlSetEncountData(s32 devil, s32 posid, s32 groupID, s32 exflg);
SBTLUNIT_WORK *sBtlSetEncountData2(s32 devil, s32 posid, s32 groupID, s32 exflg);
SBTLUNIT_WORK *sBtlSetEncountData3(s32 devil, s32 posid, s32 groupID, s32 exflg);
SBTLUNIT_WORK *sBtlSetEncountData4(s32 devil, s32 posid, s32 groupID, s32 exflg);
void sBtlSetactcounter(SBTLUNIT_WORK *wk);
bool sBtlClearGeneratorWork(void);
void sBtlGeneratorD_On(s32 group);
bool sBtlCheckGeneratorGroupID(s32 group);
bool sBtlCheckGeneratorGroupID2(s32 group);
bool sBtlCheckGenerator_ND(void);
bool sBtlCheckGenerator_D(void);
bool sBtlCheckGeneratorAll(void);
void sBtlSetGeneCam(s16 posID);
bool sBtlGeneratorProc(void);
s32 sBtlGetRndEncJoken(s32 id);
s32 sBtlGetRndEncType(s32 id, s32 nakama);
void sBtlResetRndEncType(void);
s32 sBtlGetRndEncMax(s32 id);
s32 sBtlGetRndEncCnt(void);
s32 sBtlRndEncCalc(s32 id, f32 length);
s32 sBtlRndEncCalc_Symbol(s32 id, s32 *_map, s32 *_floor);
datRndEncRitu_t *sBtlRndEncCalc_Symbol2(s32 dlcIndex, s32 packIndex, s32 tableIndex, s32 *encountIndex);
s32 sBtlCheckRndEncLevel(s32 tbl);
s32 sBtlGetLevelAverage(s32 encountno);
void sBtlResetRndEncCount(void);
void sBtlSetRndEncTopPriorityMap_Symbol(s32 map, s32 floor);
void sBtlRndEncTopPriorityMap(s32 *map, s32 *floor);
void sBtlGetDevilInfo(s32 id, SB_RNDENC_DEVILINFO *pDevilInfo);
s32 sBtlGetEncountDevil1_Lv(s32 encountno);
s32 sBtlGetEncountDevilMaxLv(s32 encountno, s32 dlcID);
s32 sBtlGetDevilNum(s32 id, s32 devilid);
s32 sBtlChkUnkui(s32 id);
s32 sBtlGetMusiEncountID(s32 rnd_encid);
s32 sBtlRndEncCalcKirestu(s32 id, f32 length);
