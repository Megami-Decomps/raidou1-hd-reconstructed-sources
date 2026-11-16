#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_CameraMoveDt S_CameraMoveDt;
typedef struct S_PosMove S_PosMove;

extern s32 gEnemyNum;
extern bool gEndPosReset;
extern bool gEnd_BS_MUNAKA_Init_Imad_Restart;
extern SBTLUNIT_WORK *wk_BS_MUNAKA_Init_Imad_Restart;
extern bool gEnd_BS_MUNAKA_Init_Imad_Kotei;
extern S_PosMove *g_aCamMoveJizenTyuugi;
extern S_PosMove *g_aTgtMoveJizenTyuugi;
extern S_CameraMoveDt *g_CamMovJizenTyuugi;
extern void *bloomCtrl;
extern s32 gStartWaitCnt;

s32 sBtlPlayerRSpiritInit(SBTLUNIT_WORK *wk);
void sBtlPlayerBgnWaitALL_Spirit(SBTLUNIT_WORK *wk, bool is_setuma);
void sBtlPlayerClrAllUnit_HitBack(void);
void sBtlPlayerSetEnemyPos(s32 _NewPosMode);
void sBtlPlayerResetEnemyPos(void);
void sBtlPlayerPushAllPosRotDispHit(void);
void sBtlPlayerPopAllPosRotDispHit(void);
void sBtlPlayerResetPlayerPosRot_Start(void);
void sBtlPlayerResetPlayerPosRot_Start_Boss(s32 _Pattern);
void sBtlPlayerResetEnemyPosRot_Start(void);
void sBtlPlayerResetCamera_Start(void);
void sBtlPlayerPopAllDispHit(void);
void sBtlPlayerSetEnemyDrawOnOff(bool _OnOff);
void sBtlPlayerSetNakamaDrawOnOff(bool _OnOff);
void sBtlPlayerSetEnemyNakamaDrawOnOff_ShadowBugPos(void);
void sBtlPlayerSetEnemyHPDrawOnOff(bool _OnOff);
void sBtlPlayerSetNakamaHPDrawOnOff(bool _OnOff);
void sBtlPlayerSetTateHit(SBTLUNIT_WORK *pTgt);
void sBtlPlayerSetTateHitEnemy(void);
bool sBtlPlayerChkAll_EnemySummonW(void);
bool sBtlPlayerDirectDmg(void);
void sBtlPlayerPlayer_Bad_Push(SBTLUNIT_WORK *wk);
void sBtlPlayerPlayer_Bad_Pop(SBTLUNIT_WORK *wk);
void sBtlPlayerScrWarp_MutekiOff_And_Push(void);
void sBtlPlayerScrWarp_Muteki_Pop(void);
void sBtlPlayerSP_BS_MUNAKA_Init_Imad_Restart(void);
void sBtlPlayerSP_BS_MUNAKA_Init_Imad_Kotei_Restart(void);
bool sBtlPlayerCheckRSpirit(void);
bool sBtlPlayerCheckRSpiritEnd(void);
bool sBtlPlayerCheckRSpirit_Start(void);
void sBtlPlayerEndRSpiritProc(void);
s32 sBtlPlayerRSpiritProc(SBTLUNIT_WORK *wk, s16 mode);
