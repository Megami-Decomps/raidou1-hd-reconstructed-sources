#pragma once
#include "types.h"

typedef enum {
    SBTLBOSSEVENT_START = 0,
    SBTLBOSSEVENT_MAG1 = 1,
    SBTLBOSSEVENT_MAG2 = 2,
    SBTLBOSSEVENT_MAG3 = 3,
    SBTLBOSSEVENT_DEAD = 4,
    SBTLBOSSEVENT_LOSE = 5,
    SBTLBOSSEVENT_DYING = 6,
    SBTLBOSSEVENT_TIME = 7,
    SBTLBOSSEVENT_SUMMON = 8,
    SBTLBOSSEVENT_RESTART = 9,
    SBTLBOSSEVENT_RDYING = 10,
    SBTLBOSSEVENT_MUNAK = 11,
} SBTLBOSSEVENT;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern f32 *sbBossRaidouPos[10];
extern bool preMenuEvent;

s32 sBtlEffect(void);
s32 sBtlEffectPreMenu(void);
s32 sBtlTips(void);
s32 BattleRestart_Effect(void);
s32 BattleMag_Effect(void);
s32 BattleDead_Effect(void);
s32 BattleTime_Effect(void);
s32 BattleSummon_Effect(void);
s32 BattleLose_Effect(void);
s32 BattleRaidoDying_Effect(void);
s32 BattleDying_Effect(void);
s32 BattleDyingSinado1_Effect(void);
s32 BattleStartApo_Effect(void);
s32 sBtlTalkEvent(void);
s32 sBtlCheck(SBTLUNIT_WORK *unit, SBTLBOSSEVENT type, s16 skillid);
bool sBtlCheck_Start_EnemySummonWait(SBTLUNIT_WORK *unit);
s32 sBtlCheck_StartLoad(void);
void sBtlProcessStart(SBTLBOSSEVENT type, s16 eventno);
bool sBtlProcessCheck(void);
bool sBtlCheckDeadEventMag(SBTLUNIT_WORK *a_pBtlUnit);
void datLoadTable(void);
