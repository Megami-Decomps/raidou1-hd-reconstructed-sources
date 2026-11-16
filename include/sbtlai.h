#pragma once
#include "types.h"
#include "SKLID.h"

#define STAT_NONE 0
#define STAT_INIT 1
#define STAT_PROC 2
#define STAT_SUMMON 3
#define STAT_GUARD 4
#define MODE_FREE 0
#define MODE_ATTACK 1
#define MODE_SKL_S 2
#define MODE_SKL_SMV 3
#define MODE_SUMMON 4
#define MODE_RETURN 5
#define MODE_SATTACK 6
#define MODE_BATTACK 7
#define MODE_SKL_SRT 8
#define MODE_TURNMV 9
#define MODE_N_ESCAPE 11
#define MODE_N_WAIT 12
#define MODE_N_KAIHI 13
#define MODE_N_SABATO 14
#define MODE_N_GARDET 15
#define MODE_N_RENKEI 16
#define MODE_N_GUARDH 17
#define MODE_N_RETURN 18
#define MODE_N_COMB_E 19
#define MODE_N_COMB_R 20
#define ST_MEIREI 1
#define ST_MEIREIBK 8
#define ST_MEIREI_S 16
#define ST_CMND_ON 2
#define ST_CMND_AI 4

typedef struct SBTLAI_WORK SBTLAI_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

bool sBtlCheckScriptData(s32 devilid, SBTLUNIT_WORK *wk);
SBTLAI_WORK *Create(void);
bool Delete(SBTLAI_WORK *wk);
s32 sBtlSetByct(SBTLUNIT_WORK *wk, s32 cnt, s32 mode);
void sBtlProc_YoyakuEndChk(SBTLUNIT_WORK *wk);
void sBtlProc_YoyakuEnd(SBTLUNIT_WORK *wk);
bool sBtlYasoAI(void);
bool Proc(SBTLUNIT_WORK *wk);
void sBtlSetAIWkStat(SBTLUNIT_WORK *wk, s32 stat);
bool sBtlSetAIMode(SBTLUNIT_WORK *wk);
bool sBtlProcScript(SBTLUNIT_WORK *wk);
bool sBtlCheckSkillEquation(SBTLUNIT_WORK *wk, s16 adr, SKLID skillid);
bool sBtlCheckTargetEquation(SBTLUNIT_WORK *wk);
bool sBtlAI_SetSeikaku_Action(SBTLUNIT_WORK *wk);
bool sBtlGetTargetUnit(SBTLUNIT_WORK *wk);
