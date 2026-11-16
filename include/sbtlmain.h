#pragma once
#include "types.h"
#include "MODELTYPE.h"

typedef enum {
    SBTLMAIN_SCENE_LOADEND = 1,
    SBTLMAIN_PLAYER_PAD = 2,
    SBTLMAIN_EFFONMEM_LOADEND = 4,
    SBTLMAIN_EXIT = 8,
    SBTLMAIN_SCENE_EXIT = 16,
    SBTLMAIN_PLAYERDEAD = 32,
    SBTLMAIN_SCENE_STOP = 64,
    SBTLMAIN_SUMMON_NEGO = 128,
    SBTLMAIN_LIGHT_BACKUP = 256,
    SBTLMAIN_GENE_OFF = 512,
    SBTLMAIN_EVENT = 1024,
    SBTLMAIN_PANEL_LOAD = 2048,
    SBTLMAIN_NEGOW_LOAD = 4096,
    SBTLMAIN_NEGOW_LOADEND = 8192,
    SBTLMAIN_CALLOFF = 16384,
    SBTLMAIN_PLAYERINIT = 32768,
    SBTLMAIN_PLAYERSET = 65536,
    SBTLMAIN_SABLOAD = 131072,
    SBTLMAIN_SHUGOU = 262144,
    SBTLMAIN_TARGETSEL = 524288,
    SBTLMAIN_MODELLOAD = 1048576,
    SBTLMAIN_SCENE_OFF = 2097152,
    SBTLMAIN_ESCAPE = 4194304,
    SBTLMAIN_EXITFLG = 8388608,
    SBTLMAIN_ESCAPEEND = 16777216,
    SBTLMAIN_ALLHITOFF = 33554432,
    SBTLMAIN_UNITPAD = 67108864,
    SBTLMAIN_SCENE_EFFSTOP = 134217728,
    SBTLMAIN_EVTLOADEND = 268435456,
    SBTLMAIN_DEVILSELOAD = 536870912,
    SBTLMAIN_R1MENUOFF = 1073741824,
    SBTLMAIN_BEFORE_BTL = 2147483648,
} SBTLMAIN;

typedef struct RED_GUAGE RED_GUAGE;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

bool sBtlCheckStartBattle(void);
bool sBtlChkBossEventStart(void);
bool sBtlChkBossEventStart_EnemySummonWait(void);
bool sBtlCheckSummon(s32 idx);
void sBtlInitEffect(void);
bool sBtlInitPlayerData(void);
sdatPlayerUnitWork_t *sBtlGetPlayerData(void);
sdatUnitWork_t *sBtlGetStockUnitData(s32 id);
bool sBtlSetData_Unit_Stock(SBTLUNIT_WORK *wk, s32 stock);
bool sBtlGetData_Stock_Unit(SBTLUNIT_WORK *wk, s32 stock);
bool sBtlCheckLive(sdatUnitWork_t *unit);
bool sBtlCheckSelect(sdatUnitWork_t *unit);
bool sBtlCheckStockPara(sdatUnitWork_t *unit);
bool sBtlSetMapFade(s32 frame, u32 abgr, s16 mode);
bool sBtlMapFadeProc(void);
bool sBtlSetMapFade_H(s32 frame, u32 abgr, s16 mode);
bool sBtlMapFadeProc_H(void);
bool sBtlSetSetsumaPadStop(s32 sttime, s32 cmpcnt, f32 _SlowMotionSpeed);
bool sBtlProcSetsumaPadStop(void);
bool sBtlIsSetsumaPadStop(void);
void sBtlEndSetsumaPadStop(void);
bool sBtlSetEnemyLastDeadStop(s32 sttime, s32 cmpcnt, f32 _SlowMotionSpeedPlayer, f32 _SlowMotionSpeedEnemy);
bool sBtlProcEnemyLastDeadStop(void);
bool sBtlIsEnemyLastDeadStop(void);
bool sBtlSetHitStop(s32 sttime, s32 cmpcnt);
bool sBtlProcHitStop(void);
s32 sBtlSearchPacData(MODELTYPE major, s32 minor, s32 devilid);
s32 sBtlSearchPacData2(MODELTYPE major, s32 minor, s32 devilid);
bool sBtlSetPacData_MHT(MODELTYPE major, s32 minor, s32 devilid, void *pData, s32 size);
bool sBtlSetPacData_AT3(MODELTYPE major, s32 minor, s32 devilid, void *pData, s32 size);
bool sBtlSetPacData_motionSE(MODELTYPE major, s32 minor, s32 devilid, void *pData, s32 size);
void sBtlPacData_Init(void);
void sBtlPacData_Free(void);
void sBtlPacData_FreeIndex(MODELTYPE major, s32 minor, s32 devilid);
s32 sBtlCheckEndEscape(void);
s32 sBtlCheckEndTimeUp(void);
SBTLUNIT_WORK *sBtlGetNakama(s8 idx);
SBTLUNIT_WORK *sBtlGetNakama_FastLoad(s8 idx);
SBTLUNIT_WORK *sBtlGetNakama2(s8 idx);
SBTLUNIT_WORK *sBtlGetPChara(void);
s32 sBtlGetSmnNo(SBTLUNIT_WORK *pUnit);
void sBtlInitRedGg(RED_GUAGE *pRedGg, s32 hp);
void sBtlDrawRedGg(s32 x, s32 y, RED_GUAGE *pRedGg, s32 hp, s32 maxhp);
void sBtlMain_Now_Omikuji_Draw(s32 alpha);
bool sBtlCheckLastEnemyDead(SBTLUNIT_WORK *wk);
