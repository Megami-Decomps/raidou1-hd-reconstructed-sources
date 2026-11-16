#pragma once
#include "types.h"
#include "BST.h"
#include "SBTLUNIT_MOTION.h"
#include "SKLID.h"
#include "libsdf.h"

typedef enum {
    sBtlPlayer_PADREAD_PRESS = 1,
    sBtlPlayer_PADREAD_TRIG = 2,
    sBtlPlayer_PADREAD_REPT = 4,
} sBtlPlayer_PADREAD;

typedef enum {
    SBTLPLAYER_VTYPE_GUN = 0,
    SBTLPLAYER_VTYPE_SWORD = 1,
    SBTLPLAYER_VTYPE_KAITEN = 2,
    SBTLPLAYER_VTYPE_TUKI = 3,
    SBTLPLAYER_VTYPE_GUARD = 4,
    SBTLPLAYER_VTYPE_ONLYD = 5,
    SBTLPLAYER_VTYPE_NORMALD = 6,
    SBTLPLAYER_VTYPE_HUTTOBI = 7,
    SBTLPLAYER_VTYPE_DOWN = 8,
    SBTLPLAYER_VTYPE_STONEDEAD = 9,
    SBTLPLAYER_VTYPE_DEAD = 10,
    SBTLPLAYER_VTYPE_MAX = 11,
} SBTLPLAYER_VTYPE;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern SDF_PADMAP regist_shortcut;
extern s32 torimochi_cnt;
extern s32 torimochi_get;
extern f32 torimochi_spd;

void sBtlSummonMenuProc(SBTLUNIT_WORK *wk);
void sBtlResetColorFlag(void);
void Init(void);
void sBtlReady_BattleSpriteCtrl(void);
void sBtlAwDeleteAll(void);
void sBtlBattleVictoryStart(void);
void sBtlBattleEnd(void);
bool sBtlCheckMove_BadStatus(SBTLUNIT_WORK *wk);
void sBtlCombSklTrophyUpdate(void);
bool sBtlCheckMove(SBTLUNIT_WORK *wk);
bool sBtlCheckIsDamage(SBTLUNIT_WORK *wk);
bool sBtlCheckIsMenuNg(SBTLUNIT_WORK *wk);
bool sBtlCheckTame(SBTLUNIT_WORK *wk);
void sBtlResetDamage_TameStart(SBTLUNIT_WORK *wk);
SKLID *sBtlGetCombSkill(SBTLUNIT_WORK *pUnit);
bool sBtlBstShugouCheck(BST _bst);
void sBtlSetVibe(SBTLPLAYER_VTYPE mode);
s32 sBtlGetPlayerID(void);
SBTLUNIT_WORK *sBtlGetPlayerUnit(s32 id);
bool sBtlCheckPad(void);
bool sBtlResetAction(SBTLUNIT_WORK *wk);
void sBtlResetAction_FO_Eve(SBTLUNIT_WORK *wk, bool _animNoChange);
bool sBtlStopAction(void);
bool sBtlActiveAction(void);
void sBtlResetATKEffect(void);
void sBtlSetNSTOP(void);
void sBtlResetNSTOP(void);
void sBtlResetCharge(SBTLUNIT_WORK *wk, bool _Immed);
void sBtlResetHitBack(SBTLUNIT_WORK *wk);
bool sBtlR1_IsNaked(void);
bool sBtlIsMoveBtn(SBTLUNIT_WORK *wk);
bool sBtlIsBattleKey(SDF_PADMAP key, sBtlPlayer_PADREAD read);
void sBtlSetCameraLockOnTgtUpdate(void);
bool sBtlSetNextTarget(SBTLUNIT_WORK *wk);
bool sBtlSetNextTargetUD(SBTLUNIT_WORK *wk, s32 _UD);
bool sBtlSetNextTargetLR(SBTLUNIT_WORK *wk, s32 _LR);
bool sBtlSetGazeOffTarget(SBTLUNIT_WORK *wk);
bool sBtlSetNextTarget_RS(SBTLUNIT_WORK *wk);
bool sBtlSetNextTarget_Setsuma(SBTLUNIT_WORK *wk);
void sBtlInitSurprise(void);
void sBtlAddSurprise(SBTLUNIT_WORK *wkEnemy);
s32 sBtlGetSurprise_ListID(SBTLUNIT_WORK *wkPlayer);
void sBtlResetCombine(void);
void sBtlSetFirstAtk(SKLID sklid);
void sBtlSetEscapeFlag(void);
s32 sBtlEscapeCheck(void);
bool sBtlDrawEscapeGauge(s32 x, s32 y);
void sBtlGuardHit(SBTLUNIT_WORK *wk, bool _DownHit);
void sBtlInitGun(void);
void sBtlChangeGunMode(SBTLUNIT_WORK *wk);
void sBtlStartGunMode(SBTLUNIT_WORK *wk);
void sBtlResetGunMode(SBTLUNIT_WORK *wk, bool _SetEndMotion);
void sBtlResetGunMode_Eve(void);
void sBtlSetGunMode_Fire(SBTLUNIT_WORK *wk);
bool sBtlGetGunMode_Camera(f32 *_SlideNml, f32 *_TgtZoomNml, f32 *_Dir);
s32 sBtlGetRapidNum_Par(void);
void sBtlSetRapidNum_Max(void);
void sBtlSetInfinite(s32 _Cnt);
void sBtlDrawGunRapid(void);
void sBtlCancelGunLockOn(void);
s32 sBtlGetGunLockOn_TgtNum(void);
void sBtlGetGunLockOn_TgtID(SBTLUNIT_WORK *wk, s32 *_TgtID);
void sBtlSetGunLockOn_Done(SBTLUNIT_WORK *wk);
void sBtlSetGunLockOn_EnemyDead_Done(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wkEnemy);
void sBtlResetGunLockOn_TgtPushPop(void);
void sBtlSetGunLockOn_TgtPush(s32 _EnemyListID);
s32 sBtlGetGunLockOn_TgtPop(void);
void sBtlSetGunLockOn_1st(SBTLUNIT_WORK *wk);
bool sBtlCheckGunMode(void);
bool sBtlCheckGunMode2(void);
s32 sBtlNormalProc_Huuma(SBTLUNIT_WORK *wk, s32 flg);
s32 sBtlNormalProc_Huuma_ActionPause(SBTLUNIT_WORK *wk, s32 flg);
bool sBtlSetHuumaData(SBTLUNIT_WORK *wk);
void sBtlSetHuumaMissItemFlagOff(SBTLUNIT_WORK *_actWk);
bool sBtlIsHuuma(void);
s32 sBtlGetHuuma_Camera(void);
void sBtlPushAllDisp(SBTLUNIT_WORK *wk);
void sBtlPopAllDisp(SBTLUNIT_WORK *wk);
void sBtlHuumaRangeCircleProc(SBTLUNIT_WORK *wk);
void sBtlGetHuuma_CameraParam(f32 *_TgtX, f32 *_TgtY, f32 *_TgtZ, f32 *_CamX, f32 *_CamY, f32 *_CamZ, f32 *_Fovy, f32 *_UpV);
void sBtlJumpStart(SBTLUNIT_WORK *wk);
void sBtlJump3Start(SBTLUNIT_WORK *wk);
void sBtlJumpHAtk1Start(SBTLUNIT_WORK *wk);
bool sBtlJumpProc_Eve(void);
f32 sBtlGetRotate_Jump(SBTLUNIT_WORK *wk, const sdfVector4_t *pos);
f32 sBtlGetJumpMoveSpeed(SBTLUNIT_WORK *wk);
f32 sBtlGetJumpY(SBTLUNIT_WORK *wk);
f32 sBtlGetJumpY_SkillSt(SBTLUNIT_WORK *wk);
bool sBtlChkNowJump(SBTLUNIT_WORK *wk);
bool sBtlChkNowJump_NotAtk(SBTLUNIT_WORK *wk);
bool sBtlChkNowJump_OrAtk(SBTLUNIT_WORK *wk);
bool sBtlChkNowJumpOver(SBTLUNIT_WORK *wk, f32 _OverY);
bool sBtlChkNowJumpAfter(SBTLUNIT_WORK *wk);
bool sBtlChkReJump(SBTLUNIT_WORK *wk);
void sBtlResetJump(SBTLUNIT_WORK *wk);
void sBtlKaihiInit(SBTLUNIT_WORK *wk);
bool sBtlChkKaihiMawari(SBTLUNIT_WORK *wkEnemy);
bool sBtlSummonKey(SBTLUNIT_WORK *wk);
bool sBtlSetSummonFunc(SBTLUNIT_WORK *wk);
bool sBtlSetReturn(SBTLUNIT_WORK *wk, s32 _SwitchReturnMode);
bool sBtlResetColor(u32 abgr);
void sBtlSetMenuItemList(void);
bool sBtlCheckBit(u32 data, s32 bit);
void sBtlSetBit(u32 *data, s32 bit);
s32 sBtlGetkuisibariBit(SKLID _sklID);
bool sBtlCheckKuisibari(SKLID _sklID);
void sBtlSetKuisibari(SKLID _sklID);
void sBtlResetBit(u32 *data, s32 bit);
void sBtlRaidouWazaCoolTimeInit(void);
void sBtlRaidouWazaCoolTimeUpdate(void);
bool sBtlIsRaidouWazaCoolTime(s32 index);
void sBtlRaidouWazaCoolTimeClr(s32 index);
void sBtlInitSetsuma(void);
void sBtlSetSetsuma_SkillStart(SBTLUNIT_WORK *wk, SKLID skillid);
void sBtlSetSetsuma_SkillHit(SBTLUNIT_WORK *wk, SKLID skillid);
void sBtlSetSetsuma_BS_LASTB3_Hirumi(SBTLUNIT_WORK *wk);
void sBtlSetSetsuma_PlayerDamage(SBTLUNIT_WORK *wk);
void sBtlSetSetsuma_PlayerGuard(SBTLUNIT_WORK *wk);
void sBtlSetSetsuma_EnemyUse(SBTLUNIT_WORK *wkEnemy);
bool sBtlChkSetsuma_Just(s32 *_Frame, SKLID _skillid);
void sBtlResetSetsuma_BossTalk(SBTLUNIT_WORK *wk);
void sBtlSetEnemySetsumaStopTime(s32 _Time);
SKLID sBtlInputChkSetsuma(SBTLUNIT_WORK *wk);
bool sBtlCheckSetsuma(void);
bool sBtlCheckSetsumaEnd(void);
bool sBtlCheckSetsuma_Kaya(f32 *_X, f32 *_Y, f32 *_Z);
void sBtlBeginSetsuma_EX(SBTLUNIT_WORK *wk);
void sBtlSetDevilID_EnemyDrawOnOff(s32 _DevilID, bool _OnOff);
void sBtlSetTargetEnemyDrawOnOff(SBTLUNIT_WORK *wk, bool _OnOff);
void sBtlSetTargetEnemyPosRot(SBTLUNIT_WORK *wk, f32 _X, f32 _Y, f32 _Z, f32 _Dir);
void sBtlSetDevilID_EnemyRot(s32 _DevilID, f32 _Dir);
void sBtlSetTargetEnemyMotion(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION _MotionID);
void sBtlSetTargetEnemyTheWorld(SBTLUNIT_WORK *wk, bool _OnOff);
void sBtlSetTargetEnemyTheWorld2(SBTLUNIT_WORK *wk, bool _OnOff);
void sBtlSetDevilID_EnemyTheWorld(s32 _DevilID, bool _OnOff);
bool sBtlChkEnemyPosReset(f32 *_X, f32 *_Y, f32 *_Z);
void sBtlSetSetsuma_DofEnd(SBTLUNIT_WORK *wk);
void sBtlSetsuma_MagWaitDone(void);
bool sBtlGetSetsumaCamMv(SBTLUNIT_WORK *wk, f32 *_TX, f32 *_TY, f32 *_TZ, f32 *_CX, f32 *_CY, f32 *_CZ, f32 *_Fov, f32 *_UpV, f32 *_AngleX, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos);
void sBtlReset_SupportAction_Shugou(SBTLUNIT_WORK *wk);
bool sBtlStlsSet(s32 index);
void sBtlShugouKaijyo(void);
void sBtlNakamaWarpReset(void);
void sBtlReset_SupportAction_Shugou2(SBTLUNIT_WORK *wkNakama);
void sBtlSetSummonVoice(s32 devilid);
void sBtlInitAutoTaget(void);
void sBtlSetAutoTagetDamage(SBTLUNIT_WORK *wk_player, SBTLUNIT_WORK *wk_enemy);
void sBtlResetAutoTaget(SBTLUNIT_WORK *wk_player, s32 old_targetID);
void sBtlUpdateAutoTaget(SBTLUNIT_WORK *wk_player);
bool sBtlGetRandomTarget(SBTLUNIT_WORK *wk, s32 flg, bool bNewTgt);
s32 sBtlGetNearTarget_Random(SBTLUNIT_WORK *wk, const sdfVector4_t *a_rot, f32 area_r, f32 rad0, f32 rad1, s8 flg);
s32 sBtlGetNearTarget2(SBTLUNIT_WORK *wk, f32 dir, f32 area_r, f32 dirLR, s8 flg);
s32 sBtlGetCameraTgtSelect1Score(SBTLUNIT_WORK *wk);
s32 sBtlGetEnemyDeadTgtSelect1Score(SBTLUNIT_WORK *wk);
s32 sBtlGetNearTargetScore(SBTLUNIT_WORK *wk, f32 pdir, f32 sdir, f32 _KeyLength, bool _UseDone);
s32 sBtlGetNearTarget_CameraLockOn2(SBTLUNIT_WORK *wk, s32 _Mode);
s32 sBtlGetNearTarget_CameraLockOn3(SBTLUNIT_WORK *wk);
s32 sBtlGetHpLowTarget(SBTLUNIT_WORK *wk);
s32 sBtlGetHpLowTarget_BS_ITIMOK(SBTLUNIT_WORK *wk);
s32 sBtlGetFrontTarget(SBTLUNIT_WORK *wk, s32 _DevilID);
f32 sBtlGetTargetLen(SBTLUNIT_WORK *wk);
bool sBtlChkSpace(SBTLUNIT_WORK *wk);
void sBtlSetPlayerDir_ToTarget(SBTLUNIT_WORK *wk);
