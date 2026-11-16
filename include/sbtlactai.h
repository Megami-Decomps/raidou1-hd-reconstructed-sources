#pragma once
#include "types.h"
#include "SBTLUNIT_SIDE.h"
#include "SBTL_ACTAIMODE.h"
#include "SKLID.h"

#define DEFTIME -1
#define HITPER 1

typedef enum {
    PEAICODE_NONE = 0,
    PEAICODE_WAIT = 1,
    PEAICODE_MOVEF = 2,
    PEAICODE_CTION = 3,
    PEAICODE_CTACT = 4,
    PEAICODE_SEARCH = 5,
    PEAICODE_BWAIT = 6,
    PEAICODE_LOOP = 7,
    PEAICODE_USEAITBL = 8,
    PEAICODE_USESKL = 9,
    PEAICODE_DATAEXIT = 10,
    PEAICODE_DATAJMP = 11,
    PEAICODE_USEHSKL = 12,
    PEAICODE_TUISEKI = 13,
    PEAICODE_TUISEKIH = 14,
    PEAICODE_P_ESCAPE = 15,
    PEAICODE_SENKAI = 16,
    PEAICODE_TOSSHIN = 17,
    PEAICODE_BSTWAIT = 18,
    PEAICODE_EQJMP = 19,
    PEAICODE_CHASE = 20,
    PEAICODE_RNDWAIT = 21,
    PEAICODE_PATTBLJMP = 22,
    PEAICODE_GUARD = 23,
    PEAICODE_FLG = 24,
    PEAICODE_P_WARP = 25,
    PEAICODE_CLEARTIME = 26,
    PEAICODE_CNTUP = 27,
    PEAICODE_CNTCLR = 28,
    PEAICODE_ROULETTE = 29,
    PEAICODE_CTVALUE = 30,
    PEAICODE_WAIT_C = 31,
    PEAICODE_RNDWAIT_C = 32,
    PEAICODE_SHILD_ZERO = 33,
    PEAICODE_SHILD_SET = 34,
    PEAICODE_SHINSENKAI = 35,
} PEAICODE;

typedef enum {
    PAITARGET_NONE = 0,
    PAITARGET_PLAYER = 1,
    PAITARGET_USER = 2,
    PAITARGET_ENEMY = 3,
    PAITARGET_ENEMY_NM = 4,
    PAITARGET_EQTARGET = 5,
    PAITARGET_SELF = 6,
    PAITARGET_HEITO = 7,
    PAITARGET_RND_P = 8,
    PAITARGET_NEAR_P = 9,
    PAITARGET_HPMAX_P = 10,
    PAITARGET_HPLESS_P = 11,
    PAITARGET_NAKAMA1 = 12,
    PAITARGET_NAKAMA2 = 13,
    PAITARGET_EQTARGETHP = 14,
} PAITARGET;

typedef struct AIACT_TBL AIACT_TBL;
typedef struct AICHK_WORK AICHK_WORK;
typedef struct AITBLDATA_WORK AITBLDATA_WORK;
typedef struct SBTLACTAI_WORK SBTLACTAI_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sdfBinary sdfBinary;

typedef s32 (*CheckFuncTblDelegate)(SBTLUNIT_WORK *wk, s32 arg, s32 idx);
typedef bool (*sBtlActAI_EAIInit_FuncDelegate)(SBTLUNIT_WORK *UnnamedParameter);
typedef bool (*sBtlActAI_EAIProc_FuncDelegate)(SBTLUNIT_WORK *UnnamedParameter);
typedef bool (*sBtlActAI_AAIInit_FuncDelegate)(SBTLUNIT_WORK *UnnamedParameter);
typedef bool (*sBtlActAI_AAIProc_FuncDelegate)(SBTLUNIT_WORK *UnnamedParameter);

struct AIACT_TBL {
    s32 per;
    s32 sklid;
    s32 targetid;
};

struct AICHK_WORK {
    u32 code[3];
    s8 jmptbl[8];
};

struct AITBLDATA_WORK {
    s32 scr_no;
    AICHK_WORK *act[2];
    AIACT_TBL *acttbl;
    s32 *pat_tbl;
};

extern AITBLDATA_WORK *ai_tbldata2;
extern CheckFuncTblDelegate *CheckFuncTbl;
extern sBtlActAI_EAIInit_FuncDelegate *EAIInit_Func;
extern sBtlActAI_EAIProc_FuncDelegate *EAIProc_Func;
extern sBtlActAI_AAIInit_FuncDelegate *sBtlActAI_AAIInit_Func;
extern sBtlActAI_AAIProc_FuncDelegate *sBtlActAI_AAIProc_Func;

void sBtlInitAIdata(sdfBinary *head_bin, s32 dlc_no);
void sBtlInitAIdataDLC(s32 dlc_no);
bool sBtlGotoAtkPos(SBTLUNIT_WORK *wk, bool bRinchi);
bool sBtlNakamaGoalChk(SBTLUNIT_WORK *wk);
s32 sBtlSetAIData(SBTLUNIT_WORK *wk, PEAICODE code, s32 arg, s32 codet, s32 arg2);
bool sBtlCheckCodeArg(PEAICODE code);
SBTLUNIT_WORK *sBtlCheckCharmTarget(SBTLUNIT_WORK *wk);
SBTLUNIT_SIDE sBtlGetCharmSide(SBTLUNIT_WORK *wk, SBTLUNIT_SIDE side);
bool sBtlCheckCrossUnit_HIT(SBTLUNIT_WORK *wk, const sdfVector4_t *ppos);
bool sBtlCheckEquationProc(SBTLUNIT_WORK *wk);
SBTLUNIT_WORK *sBtlGetWarpUnit_ID(SBTLUNIT_WORK *wk);
void sBtlSetWalk(SBTLUNIT_WORK *wk, f32 length);
bool sBtlCheckWapIN(SBTLUNIT_WORK *wk);
s32 sBtlGetLockID(SBTLUNIT_WORK *wk);
void sBtlSetLockID(SBTLUNIT_WORK *wk, s32 lockid);
void sBtlSetTargetID(SBTLUNIT_WORK *wk, s32 targetd);
bool sBtlPrivAreaCheck(SBTLUNIT_WORK *wk, s32 flg);
bool sBtlCheckSearchEnemy(SBTLUNIT_WORK *wk, s32 id, s8 mode);
bool sBtlSetSearchEnemyMode(SBTLUNIT_WORK *wk, s32 targetid);
bool sBtlCheckSide(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock);
bool sBtlGetEscapePoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area);
bool sBtlGetWarpPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area);
bool sBtlGetFukinPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area);
sdfVector4_t sBtlGetFixFormationPos(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wkPc, const sdfVector4_t *tgtPos, s32 area);
bool sBtlGetNWarpPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, const sdfVector4_t *tgtpos, sdfVector4_t *pos, s32 area);
bool sBtlGetSenkaiPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area);
bool sBtlGetShinSenkaiPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area);
void sBtlSetAAIData(SBTLUNIT_WORK *wk);
bool sBtlCheckMapHit(const sdfVector4_t *pos0, const sdfVector4_t *ppos, f32 dis);
bool sBtlCheckResetDataflg(PEAICODE code);
bool sBtlCheckUserUnit(SBTLUNIT_WORK *wk);
void sBtlSetNoMP(SBTLUNIT_WORK *wk);
bool sBtlCheckPadMode(SBTLUNIT_WORK *wk);
void sBtlResetNakamaAction(SBTLUNIT_WORK *wk);
bool sBtlCheckHITCheck_Char(SBTLUNIT_WORK *wk);
bool sBtlEnemyAI(SBTLUNIT_WORK *wk);
bool sBtlEAIInit_Dummy(SBTLUNIT_WORK *wk);
bool sBtlEAIInit_None(SBTLUNIT_WORK *wk);
bool sBtlEAIInit_Summon(SBTLUNIT_WORK *wk);
bool sBtlEAIInit_BtlInit(SBTLUNIT_WORK *wk);
bool sBtlEAIInit_BtlWait(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Dummy(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Wait(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Movef(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Guard(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Ctact(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Search(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Chase(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Escape(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_Summonw(SBTLUNIT_WORK *wk);
bool sBtlEAIProc_BtlAI(SBTLUNIT_WORK *wk);
bool sBtlSetGroupAction(SBTLUNIT_WORK *wk, s32 targetid, u32 mode, s8 flg);
bool sBtlMVSupport(SBTLUNIT_WORK *wk);
bool sBtlCheckHit_HitHelper(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock);
void sBtlForceAddBtlNum(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock);
void sBtlAddBtlNum(SBTLUNIT_WORK *wk);
void sBtlDecBtlNum(SBTLUNIT_WORK *wk);
void sBtlDecBtlNum_Mine(s32 id);
bool sBtlSetNormalAction(SBTLUNIT_WORK *wk, SBTL_ACTAIMODE type, s8 flg, s32 time, sdfVector4_t *pos);
bool sBtlGetMovePos_MapHit(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, f32 dis, f32 deg, s32 flg);
bool sBtlGetMovePos_MapHit_Nakama(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, f32 dis, f32 deg, s32 flg, s32 nakama);
bool sBtlGetMovePos_MapHit_2(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, const sdfVector4_t *pos, f32 dis, f32 deg, s32 flg);
bool sBtlAAIProc(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_None(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_Free(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Escape(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Kaihi(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Wait(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Sabato(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_GardeT(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Renkei(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Comb_E(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Comb_R(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_Return(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_Attack(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_BAttack(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_Skl_S(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_SUMMON(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_N_GuardH(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_SAttack(SBTLUNIT_WORK *wk);
bool sBtlAAIInit_TurnMV(SBTLUNIT_WORK *wk);
void sBtlResetMode(SBTLUNIT_WORK *wk);
void sBtlResetAAI(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_None(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_Free(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Wait(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Sabato(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Renkei(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Comb_E(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Comb_R(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Return(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Escape(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_Kaihi(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_GardeT(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_Attack(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_BAttack(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_TurnMV(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_Skl_S(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_Skl_SMV(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_Skl_SRT(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_SUMMON(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_N_GuardH(SBTLUNIT_WORK *wk);
bool sBtlAAIProc_SAttack(SBTLUNIT_WORK *wk);
s32 sBtlMawariChk(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pTgt);
bool sBtlWarpDevilChk(s32 devilId);
bool sBtlNakamaGaolChk_Sub(SBTLUNIT_WORK *wk);
bool sBtlNakamaGoalChk2(SBTLUNIT_WORK *wk);
void sBtlACTAIFLG_Clr(SBTLUNIT_WORK *wk);
SBTLACTAI_WORK *sBtlCreate(void);
bool sBtlDelete(SBTLACTAI_WORK *wk);
bool sBtlProc(SBTLUNIT_WORK *wk);
AITBLDATA_WORK *sBtlGetAITBL(s32 devilid, SBTLUNIT_WORK *wk);
s32 sBtlGetAIPatternData(SBTLUNIT_WORK *unit, s32 id, s32 p1, s32 p2);
bool sBtlSetSkillData_AI(SBTLUNIT_WORK *wk, SKLID skillid);
bool sBtlCheckEquation(SBTLUNIT_WORK *wk);
bool sBtlCheckChkskl(SBTLUNIT_WORK *wk, s32 sklid);
void sBtlSetChkskl(SBTLUNIT_WORK *wk, s32 sklid);
void SetChkskl(SBTLUNIT_WORK *wk, SKLID sklid);
void sBtlResetChkskl(SBTLUNIT_WORK *wk, s32 sklid);
bool sBtlCheckUseskl(SBTLUNIT_WORK *wk, s32 sklid);
void sBtlSetUseskl(SBTLUNIT_WORK *wk, s32 sklid);
void SetUseskl(SBTLUNIT_WORK *wk, SKLID sklid);
void sBtlResetUseskl(SBTLUNIT_WORK *wk, s32 sklid);
bool sBtlCheckMeshiyose(SBTLUNIT_WORK *wk);
s32 sBtlGetEnemyNum(void);
bool sBtlUseTableDataProc(SBTLUNIT_WORK *wk);
s32 sBtlGetUseTable_Target(SBTLUNIT_WORK *wk, PAITARGET code, s32 arg);
s32 sBtlCheckEnemyTarget(SBTLUNIT_WORK *wk, s32 id);
bool sBtlResetAIPattern(SBTLUNIT_WORK *wk, s32 mode);
bool sBtlEAIProc_BtlWait(SBTLUNIT_WORK *wk);
