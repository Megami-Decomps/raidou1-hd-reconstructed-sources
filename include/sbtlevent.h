#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

void sBtlCheckTutorialEnd(void);
void sBtlTutorialEndNakamaChack(void);
void sBtlInitTutorial(void);
void sBtlCheckBattleWin(void);
void sBtlCheckBattleLose(void);
bool sBtlCheckTutorialBattle(void);
bool sBtlEvent_CheckRain(void);
bool sBtlEvent_LoadEventScript(void);
bool sBtlEvent_DeleteEventScript(void);
bool sBtlEvent_SetCharacterProc(s32 negoid);
u8 *sBtlGetEventMes(s16 eventno);
bool sBtlEvent_NegoProc(u8 *adr, s32 no);
bool sBtlMessageProc(u8 *adr, s32 no, SBTLUNIT_WORK *wk, s32 flg);
bool EventProc(void);
bool sBtlChkEvent(void);
bool sBtlLoadHuuma_MesData(void);
s32 sBtlEventChkMemory(s16 eventno);
void sBtlEventSetMemory(s16 eventno);
