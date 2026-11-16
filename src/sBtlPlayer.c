#include "types.h"
#include "BST.h"
#include "SBTLMAIN_MODE.h"
#include "SBTLUNIT_MOTION.h"
#include "SKLID.h"
#include "achievement.h"
#include "aw_bullet.h"
#include "aw_bulletmuzzle.h"
#include "aw_camlockon.h"
#include "aw_guncylinder.h"
#include "aw_guntarget.h"
#include "aw_hitlight.h"
#include "aw_jump.h"
#include "aw_jumpattack2l.h"
#include "aw_mag.h"
#include "aw_rangecircle.h"
#include "aw_sbattle.h"
#include "aw_setsuma1.h"
#include "aw_setsuma2.h"
#include "aw_shockwave1.h"
#include "aw_slash.h"
#include "aw_tame.h"
#include "aw_tamemax.h"
#include "aw_xatkpad.h"
#include "bsflow.h"
#include "cfg.h"
#include "cmpomoide.h"
#include "configgame.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3basic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3padmanager.h"
#include "dds3unitobjectbasic.h"
#include "dds3vrf.h"
#include "dds3worldbasic.h"
#include "effstat.h"
#include "evtbit.h"
#include "fld.h"
#include "itf.h"
#include "libsdf.h"
#include "mdl.h"
#include "movie.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtldmg.h"
#include "sbtldraw.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlexp.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlpanel.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_ground.h"
#include "sbtlplayer_gunshot.h"
#include "sbtlplayer_jigenkiri.h"
#include "sbtlplayer_kaiten.h"
#include "sbtlplayer_magic.h"
#include "sbtlplayer_magic2.h"
#include "sbtlplayer_magic3.h"
#include "sbtlplayer_magic4.h"
#include "sbtlplayer_magic5.h"
#include "sbtlplayer_magic6.h"
#include "sbtlplayer_sddash.h"
#include "sbtlplayer_sdshot.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayerex.h"
#include "sbtlplayerfoot.h"
#include "sbtlplayertbl.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtltalk.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "sdfsound.h"
#include "slmain.h"
#include "smnr.h"
#include "sndmanager.h"

#define SBTLPNL_LISTNUM 6
#define SBTLMENU_OFFCOLOR 2153799776
#define SBTLMENU_DEFCOLOR 2155905152
#define SBTLPLAYER_ANLOGCNT 20
#define SBTLPLAYER_ANLOGRESET 20
#define SBTLPLAYER_SORDEND 4
#define SBTLPLAYER_MAGWAZA_COST 5
#define SBTLPLAYER_HCOMBO_MAGCOST 1
#define SBTLHUUMA_ZOOM_P 1.6
#define D_SDCHG_CNT 30
#define D_LCCHG_CNT 30
#define D_AXCHG_CNT 30
#define D_GUNCHG_CNT2 6
#define D_GUNCHG_CNT2F 3
#define D_GUNTARGET_MAX 6
#define D_COMBO_LONG_CNT 15
#define D_BSTEP_LONG_CNT 15
#define D_CAMTGTSEL_CNT 11
#define RAPID_MAX 36
#define RAPID_CNT 600

typedef enum {
    E_KeyCancel_E_SKLID_TUKI = 0,
    E_KeyCancel_E_SKLID_MAWASIKERI = 1,
    E_KeyCancel_E_SKLID_OIUCHI = 2,
    E_KeyCancel_E_SKLID_RELOAD = 3,
    E_KeyCancel_E_SKLID_GUN = 4,
    E_KeyCancel_E_SKLID_TYUSHYOT = 5,
    E_KeyCancel_E_SKLID_DAISHYOT = 6,
    E_KeyCancel_E_SKLID_GUN_TYUSHYOT = 7,
    E_KeyCancel_E_SKLID_GUN_DAISHYOT = 8,
    E_KeyCancel_E_SKLID_SD_COMBI1 = 9,
    E_KeyCancel_E_SKLID_LC_COMBI1 = 10,
    E_KeyCancel_E_SKLID_AX_COMBI1 = 11,
    E_KeyCancel_E_SKLID_HADAKA1 = 12,
    E_KeyCancel_E_SKLID_HADAKA2 = 13,
    E_KeyCancel_E_SKLID_HADAKA3 = 14,
    E_KeyCancel_E_SKLID_SD_HCOMBO_T5 = 15,
    E_KeyCancel_E_SKLID_LC_HCOMBO_T5 = 16,
    E_KeyCancel_E_SKLID_AX_HCOMBO_T4 = 17,
    E_KeyCancel_E_SKLID_SD_HCOMBO_S1 = 18,
    E_KeyCancel_E_SKLID_SD_HCOMBO_S2 = 19,
    E_KeyCancel_E_SKLID_SD_HCOMBO_S3 = 20,
    E_KeyCancel_E_SKLID_SD_HCOMBO_S4 = 21,
    E_KeyCancel_E_SKLID_SD_HCOMBO_S5 = 22,
    E_KeyCancel_E_SKLID_SD_HCOMBO_L1 = 23,
    E_KeyCancel_E_SKLID_SD_HCOMBO_L2 = 24,
    E_KeyCancel_E_SKLID_SD_HCOMBO_L3 = 25,
    E_KeyCancel_E_SKLID_SD_HCOMBO_L4 = 26,
    E_KeyCancel_E_SKLID_SD_HCOMBO_L5 = 27,
    E_KeyCancel_E_SKLID_LC_HCOMBO_1 = 28,
    E_KeyCancel_E_SKLID_LC_HCOMBO_2 = 29,
    E_KeyCancel_E_SKLID_LC_HCOMBO_3 = 30,
    E_KeyCancel_E_SKLID_LC_HCOMBO_4 = 31,
    E_KeyCancel_E_SKLID_LC_HCOMBO_5 = 32,
    E_KeyCancel_E_SKLID_AX_HCOMBO_S1 = 33,
    E_KeyCancel_E_SKLID_AX_HCOMBO_S2 = 34,
    E_KeyCancel_E_SKLID_AX_HCOMBO_S3 = 35,
    E_KeyCancel_E_SKLID_AX_HCOMBO_S4 = 36,
    E_KeyCancel_E_SKLID_AX_HCOMBO_L1 = 37,
    E_KeyCancel_E_SKLID_AX_HCOMBO_L2 = 38,
    E_KeyCancel_E_SKLID_AX_HCOMBO_L3 = 39,
    E_KeyCancel_E_SKLID_AX_HCOMBO_L4 = 40,
    E_KeyCancel_E_SKLID_JUMPATK1 = 41,
    E_KeyCancel_E_SKLID_JUMPATK2 = 42,
    E_KeyCancel_E_SKLID_JUMPATK2A = 43,
    E_KeyCancel_E_SKLID_APPROACH = 44,
    E_KeyCancel_E_SKLID_APPROACHATK = 45,
    E_KeyCancel_E_SKLID_APPROACH_ED = 46,
    E_KeyCancel_E_SKLID_SCOMBO1 = 47,
    E_KeyCancel_E_SKLID_SCOMBO2 = 48,
    E_KeyCancel_E_SKLID_SCOMBO3 = 49,
    E_KeyCancel_E_SKLID_SCOMBO4 = 50,
    E_KeyCancel_E_SKLID_SCOMBO5 = 51,
    E_KeyCancel_E_SKLID_SCOMBO1A = 52,
    E_KeyCancel_E_SKLID_JUMPHATK1 = 53,
    E_KeyCancel_E_SKLID_JUMPHATK1L = 54,
    E_KeyCancel_NUM = 55,
    E_KeyCancel_NONE = -1,
} E_KeyCancel;

typedef struct P_JUMP_t P_JUMP_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_KeyCancel S_KeyCancel;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;

typedef bool (*SummonMenuFuncDelegate)(SBTLUNIT_WORK *wk, s32 mode);

struct S_KeyCancel {
    s32 keyBgn;
    s32 ComboBgn;
    s32 MoveCancelBgn;
    s32 KaihiCancelBgn;
    s32 GunCancelBgn;
    s32 GuardCancelBgn;
    s32 SwordCancelBgn;
    s32 RsCancelBgn;
    s32 ChargeCancelBgn;
    SKLID SkillL;
    SKLID SkillH;
    SKLID SkillG;
};

struct P_JUMP_t {
    bool Use;
    bool Pause;
    s32 Step;
    f32 StepTime;
    bool StepBoolA;
    f32 InputTime;
    f32 Time;
    f32 Y;
    f32 SpeedRise;
    f32 SpeedRise2;
    f32 SpeedRise3;
    f32 SpeedFall;
    f32 SpeedMove;
    bool HighJump;
    f32 PeakY;
    SKLID NextSkill;
    s32 NextSkillRS;
    s32 RetStep;
    bool ReJumpInput;
    bool Jump3Use;
    f32 SkillStY;
};

static SummonMenuFuncDelegate *SummonMenuFunc0[1];
static SummonMenuFuncDelegate *SummonMenuFunc1;
static SummonMenuFuncDelegate *SummonMenuFunc2;
static SummonMenuFuncDelegate *SummonMenuFunc3;
static SummonMenuFuncDelegate *SummonMenuFunc4;
static SummonMenuFuncDelegate *SummonMenuFunc5;
static SummonMenuFuncDelegate *SummonMenuFunc6;
static s32 sBtlPlayer_R1R2NoInput;
static bool gSpriteInitDone;
static bool gNowDebugTest;
static SKLID *combSkill;
SDF_PADMAP regist_shortcut;
static s32 gOldCursor_targetUID;
static bool g1StDone;
static s32 *gSelectTarget_SortListID;
static f32 *gSelectTarget_SortLR;
static f32 *gSelectTarget_SortLen;
static s32 gSelectTarget_SortNum;
static s32 gSelectTarget_SortNowIdx;
static s32 *gSurpriseTarget_SortListID;
static s32 gSurpriseTarget_SortNum;
static s32 gOldTargetListID;
static SKLID *g_aRaidouSkill;
static S_KeyCancel *aKeyCancel;
static s32 gGunModeStep;
static s32 gGunModeCnt;
static f32 gGunModeTime;
static f32 gGunModeAnimTime;
static f32 gGunMode_SlideNml;
static f32 gGunMode_TgtZoomNml;
static f32 gGunMode_Dir;
static bool gGunInfinite;
static s32 gGunInfiniteCnt;
static f32 huuma_hossei;
static f32 huuma_ada_jo;
static s32 huuma_def_time;
static s32 gCamPost_Step;
static s32 gCamPost_Cnt;
static s32 gCamPost_R0L1;
static f32 gCamPost_TgtGoalX;
static f32 gCamPost_TgtGoalY;
static f32 gCamPost_TgtGoalZ;
static f32 gCamPost_CamGoalX;
static f32 gCamPost_CamGoalY;
static f32 gCamPost_CamGoalZ;
static f32 gCamPost_TgtNowX;
static f32 gCamPost_TgtNowY;
static f32 gCamPost_TgtNowZ;
static f32 gCamPost_CamNowX;
static f32 gCamPost_CamNowY;
static f32 gCamPost_CamNowZ;
static f32 gCam_Fovy_Now;
static f32 gCam_UpV_Now;
static f32 gVignetteOw_intensity_Now;
static f32 gFilmGrainOw_intensity_Now;
static f32 gChromaticAberrationOw_intensity_Now;
static f32 gBloom_threshold_Bk;
static f32 gBloom_intensity_Bk;
static f32 gBloom_scatter_Bk;
static f32 gBloom_threshold_Now;
static f32 gBloom_intensity_Now;
static f32 gBloom_scatter_Now;
static f32 gBloom_threshold_Max;
static f32 gBloom_intensity_Max;
static f32 gBloom_scatter_Max;
static bool huuma_auto;
static s32 gYorosiku_DevilID;
static bool gYorosiku_SmgLoad;
static bool gNowActionPause;
static bool HuumaGageOff;
static s32 HuumaTimeLimit;
static s32 *gageTbl;
static P_JUMP_t *gJump;
static bool gNext_bRR;
static bool gNext_bComboSRU;
static bool gNext_bRaiSkill_RU;
static bool gNext_bRaiSkill_RL;
static bool gNext_bRaiSkill_RD;
static bool gBk_targetID_Use;
static s32 gBk_targetID;
s32 torimochi_cnt;
s32 torimochi_get;
f32 torimochi_spd;
static bool gKaihi_BackStep;
static f32 gKaihiTotalModelen;
static s32 gHomingMode;
static s32 gHomingCnt;
static bool gHomingSeDone;
static s32 gSetsumaIdx;
static bool gTargetMagWait;
static f32 gTargetMagX;
static f32 gTargetMagY;
static f32 gTargetMagZ;
static f32 gKayaCnt;
static f32 gKayaCameraCutID;
static f32 gKayaEnemyPosX;
static f32 gKayaEnemyPosZ;
static s32 gKayaUnitID;
static bool gLastDead;
static bool gDeadEvent;
static bool gDeadEventUse;
static s32 gStep;
static s32 gStepCnt;
static f32 gStepTime;
static s32 gEnemyStopTime;
static f32 gJustFrame;
static f32 gJustFrameEx;
static s32 gSummonMode;
static s32 gSummonDevilID;
static s32 gSummonIdx;
static s32 gSummonStep;
static s32 gSummonStepFrame;
static s32 gAutoTgt_NextID;
static s32 gAutoTgt_NextCnt;
static s32 gAutoTgt_LastDmgID;
static s32 gAutoTgt_LastDmgCnt;

static bool CheckSummonTarget(SBTLUNIT_WORK *wk);
static bool SummonMenuFunc_Open00(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_00(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_10(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_20(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_30(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_40(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_50(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_60(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool SummonMenuFunc_70(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static void sBtlPlayer_CommPad_Clear(void);
static void sBtlPlayer_CommPad(void);
static bool sBtlPlayer_Pad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic);
static void PlayerAllSync(SBTLUNIT_WORK *wk);
static void SBTLMAIN_MODE_STOP_Task(SBTLUNIT_WORK *wk);
static s32 CheckAction_Raidou(SBTLUNIT_WORK *wk);
static bool CheckMoveAction(SBTLUNIT_WORK *wk);
static bool CheckGuard(SBTLUNIT_WORK *wk);
static bool CheckKaihi(SBTLUNIT_WORK *wk);
static bool Reset_SupportAction(SBTLUNIT_WORK *wk);
static bool Check_SupportAction(SBTLUNIT_WORK *wk);
static void SetNakamaSkillAct(s32 summonidx);
static f32 CheckAutoSkill_Escape(f32 per0);
static bool SetColor(u32 abgr);
static f32 GetAnlogKey(SBTLUNIT_WORK *wk, sdfVector4_t *direction);
static bool Sord1Proc_New(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode);
static bool R1_HuumaBtn(void);
static bool RegistShortCutBtn(void);
static bool shortCutBtnCHECK(void);
static bool IsGunMode(void);
static bool IsSWAZA_AdvanceCheck(void);
static bool IsLookChgR_Push(void);
static bool IsRaidouWazaKey(SDF_PADMAP key, SDF_PADMAP chk_key);
static bool Is2PressKey(SDF_PADMAP key, SDF_PADMAP chk_key1, SDF_PADMAP chk_key2);
static bool IsTgtKey(SDF_PADMAP key, SDF_PADMAP chk_key);
static bool IsEnemyAllDead(void);
static void InitCameraLockOn(void);
static void Check_SupportAction_CameraLockOn(SBTLUNIT_WORK *wk);
static bool ChkAllDeath(void);
static bool ChkAllEnemySummon(void);
static s32 GetSummonIndex(s32 summonindex);
static bool CheckAction_Nakama(SBTLUNIT_WORK *wk, s32 summonindex);
static bool CheckStop_BadStatus(SBTLUNIT_WORK *wk);
static SKLID GetSklId_Length(SKLID sklid);
static bool ChkFirstAtkLen(SKLID sklid);
static void SetFirstAtk_Core(SKLID sklid);
static void SetMagCost(SBTLUNIT_WORK *wk, SKLID sklid);
static bool CancelSystem(bool *_ComboDone);
static bool EscapeGauge(SBTLUNIT_WORK *wk);
static bool EscapeGauge_FadeOut(SBTLUNIT_WORK *wk);
static s32 GuardInit(SBTLUNIT_WORK *wk);
static s32 GuardProc(SBTLUNIT_WORK *wk, s16 mode);
static bool SetGunPlayerHit(SBTLUNIT_WORK *wk);
static void SetGunPlayerDir(SBTLUNIT_WORK *wk);
static void UpdateGunRapid(SBTLUNIT_WORK *wk);
static void ProcGunMode(SBTLUNIT_WORK *wk);
static bool CheckHuumaMes(void);
static void SetHuumaMiss(SBTLUNIT_WORK *wk, s16 flg);
static bool CheckHuuma_Moon(SBTLUNIT_WORK *wk);
static bool CheckHuuma2(SBTLUNIT_WORK *wk);
static s32 CheckHuuma(SBTLUNIT_WORK *wk);
static bool CheckHuuma_ChkNowNakamaDead(void);
static s32 HuumaProc(SBTLUNIT_WORK *wk);
static bool HuumaMitama(s32 devilid);
static bool FalseHuuma(SBTLUNIT_WORK *wk);
static void HuumaGetItemInit(SBTLUNIT_WORK *wklock);
static bool DlcMitama(void);
static bool HuumaGetItemCalc(SBTLUNIT_WORK *wklock);
static void MagAddUnitHeight(SBTLUNIT_WORK *wkEnemy, s32 _Var, s32 _Par);
static bool ChkHuuma_PlayerInputOk(SBTLUNIT_WORK *wk);
static void CalcCamPost_Init(void);
static void CalcCamPost_StepSet(s32 _Step);
static void CalcCamPost_TgtPos(SBTLUNIT_WORK *wkPlayer, SBTLUNIT_WORK *wkEnemy, f32 *_TgtX, f32 *_TgtY, f32 *_TgtZ);
static void CalcCamPost_Update(void);
static void ResetPost(void);
static void InitJump(void);
static s32 NormalProc_Jump(SBTLUNIT_WORK *wk, s32 flg, s32 keyflg);
static bool JumpProc_Jump(SBTLUNIT_WORK *wk);
static bool ComboProc_Jump(SBTLUNIT_WORK *wk);
static bool ChkKeyPressJump(void);
static void JumpVoice(SBTLUNIT_WORK *wk);
static void JumpCalc_Move(SBTLUNIT_WORK *wk, f32 _DirLR);
static void JumpCalc(SBTLUNIT_WORK *wk);
static s32 JumpProc(SBTLUNIT_WORK *wk);
static void JumpAtk1Start(SBTLUNIT_WORK *wk);
static s32 JumpAtk1Proc(SBTLUNIT_WORK *wk);
static void JumpAtk2Start(SBTLUNIT_WORK *wk);
static void JumpAtk2Start_From_APPROACHATK(SBTLUNIT_WORK *wk);
static s32 JumpAtk2Proc(SBTLUNIT_WORK *wk);
static void JumpHAtkStart(SBTLUNIT_WORK *wk);
static s32 JumpHAtkProc(SBTLUNIT_WORK *wk);
static s32 NormalProc_Kaihi(SBTLUNIT_WORK *wk, s32 flg, s32 keyflg);
static bool ReStart_Kaihi(SBTLUNIT_WORK *wk);
static bool SetKaihiMawari(SBTLUNIT_WORK *wk, s32 _targetID, f32 _DirRange, f32 _KeyDir2);
static void KaihiInit_Sub(SBTLUNIT_WORK *wk, s32 mode);
static s32 KaihiProc(SBTLUNIT_WORK *wk);
static s32 KaihiProc_ZENTEN(SBTLUNIT_WORK *wk);
static s32 KaihiProc_BACKSTEP(SBTLUNIT_WORK *wk);
static s32 MawariProc(SBTLUNIT_WORK *wk);
static bool IsPlanMenuOpen(s32 index);
static s32 UseItemProc(SBTLUNIT_WORK *wk);
static void SetSummonMenu(s32 mode);
static f32 Cadd(f32 now, f32 add);
static f32 GetAnlogKeyToDir(SBTLUNIT_WORK *wk, f32 *dir);
static f32 GetAnlogKeyToVecAndDir(SBTLUNIT_WORK *wk, sdfVector4_t *vec, f32 *dir);
static s32 NormalProc(SBTLUNIT_WORK *wk);
static bool nakamamode_UnitPad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic);
static s32 NormalProc_Nakama(SBTLUNIT_WORK *wk);
static s32 AtkProc_Nakama(SBTLUNIT_WORK *wk);
static s32 SklProc_Nakama(SBTLUNIT_WORK *wk);
static void KaihiInit_Nakama(SBTLUNIT_WORK *wk);
static s32 KaihiProc_Nakama(SBTLUNIT_WORK *wk);
static s32 GuardProc_Nakama(SBTLUNIT_WORK *wk, s16 mode);
static void CalcSetsuma(SBTLUNIT_WORK *wk);
static void SetTargetMagPos(SBTLUNIT_WORK *wk, bool _HelperUse);
static void BeginSetsuma(SBTLUNIT_WORK *wk);
static void SetSetsuma_Dof_SETSUMA1_R(SBTLUNIT_WORK *wk);
static bool Chk_Unit_Unit_Hit(SBTLUNIT_WORK *wk);
static void FinishSetsuma(SBTLUNIT_WORK *wk);
static void EndSetsuma(SBTLUNIT_WORK *wk);
static s32 SetsumaProc(SBTLUNIT_WORK *wk);
static bool UpdateSetsuma(SBTLUNIT_WORK *wk);
static void Check_SupportAction_Shugou(SBTLUNIT_WORK *wk);
static void StlsClr(s32 index);
static bool StlsEndChk(s32 index);
static bool ShugouKaijyoSub(SBTLUNIT_WORK *wklock);
static s32 CheckNowNSWARP(s32 index);
static void Check_Stls(SBTLUNIT_WORK *wklock);
static s32 SummonInit(SBTLUNIT_WORK *wk, s32 _SummonMode, s32 _SummonIdx, s32 _SummonDevilID);
static SBTLUNIT_WORK *GetSummonNakama(s32 ctrlSmnIdx);
static s32 SummonProc(SBTLUNIT_WORK *wk);
static void DecideTarget(bool bFirst, SKLID _Old_skillid);
u32 GetDevilSE(s32 devilID, s32 motionID);

// 0x1f6c4a0
void sBtlSummonMenuProc(SBTLUNIT_WORK *wk) {
  u32 v4;
  SummonMenuFuncDelegate SummonMenuFunc0_local;
  SBATTLE_WORK *v13;
  SummonMenuFuncDelegate v14;

  v4 = wk->menutype - 1;
  switch (v4)
  {
    case 0u:
      SummonMenuFunc0_local = SummonMenuFunc0;
      goto LABEL_36;
    case 1u:
      SummonMenuFunc0_local = SummonMenuFunc1;
      goto LABEL_36;
    case 2u:
      SummonMenuFunc0_local = SummonMenuFunc2;
      goto LABEL_36;
    case 3u:
      SummonMenuFunc0_local = SummonMenuFunc3;
      goto LABEL_36;
    case 4u:
      SummonMenuFunc0_local = SummonMenuFunc4;
      goto LABEL_36;
    case 5u:
      SummonMenuFunc0_local = SummonMenuFunc5;
      goto LABEL_36;
    case 6u:
      SummonMenuFunc0_local = SummonMenuFunc6;
LABEL_36:
      v13 = wk;
      v14 = SummonMenuFunc0_local[v13->sgstat[0]];
      (v14->invoke_impl)(v14->method_code, wk, (u32)v13->mode, v14->method);
      break;
    default:
      return;
  }
}

// 0x1f6c730
static bool CheckSummonTarget(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v4;
  SBATTLE_WORK *v6;
  u32 stock_mask;
  s32 macter_csr;
  s32 v10;
  s32 magcost;
  SBATTLE_WORK *v12;

  StockUnitData = sBtlGetStockUnitData(wk->macter_csr);
  if (!StockUnitData)
    return (char)StockUnitData;
  v4 = StockUnitData;
  if ((sBtlGetBadStatus(StockUnitData) & 0xFFFFFFFE) == 0x10)
    goto LABEL_25;
  v6 = wk;
  stock_mask = v6->stock_mask;
  macter_csr = v6->macter_csr;
  if (((stock_mask >> macter_csr) & 1) == 0)
  {
    v10 = wk->stock_id[wk->macter_csr];
    magcost = sBtlGetDevilData(v10, -1)->magcost;
    v12 = wk;
    if (v12->getmag + v12->mag < magcost)
      goto LABEL_25;
    v12 = wk;
    if (v12->member_num >= 1)
      goto LABEL_25;
  }
  LOBYTE(StockUnitData) = 1;
  return (char)StockUnitData;
LABEL_25:
  LOBYTE(StockUnitData) = 0;
  return (char)StockUnitData;
}

// 0x1f6c960
static bool SummonMenuFunc_Open00(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  bool result;
  s32 *p_macter_csr;
  s32 *v9;
  SBATTLE_WORK *v11;
  s8 v12;
  s64 macter_csr;
  s32 v14;
  s32 v15;
  sdatUnitWork_t *StockUnitData;
  s32 v18;

  if (wk->sgstat[1])
    return 1;
  if (CHECK_REP2(4101))
  {
    p_macter_csr = &wk->macter_csr;
    sBtlParaAdd(p_macter_csr, 1, 5, 0);
    goto LABEL_14;
  }
  if (CHECK_REP2(4100))
  {
    v9 = &wk->macter_csr;
    sBtlParaDec(v9, 1, 5);
LABEL_14:
    sBtlPlaySE(0);
    return 1;
  }
  if (CHECK_TRIG(4097, 1))
  {
    sBtlCancelMenuPara();
    return 1;
  }
  else
  {
    if (!CHECK_TRIG(4096, 1))
      return 1;
    v11 = wk;
    switch (v11->macter_csr)
    {
      case 0:
        if (sBtlCheckSummonUnit())
          return 1;
        sBtlPlaySE(8u);
        sBtlResetSummonPanel(2);
        v12 = 0;
        goto LABEL_42;
      case 1:
        macter_csr = 1;
        v15 = v11->stock_id[macter_csr];
        sBtlGetDevilData(v15, -1);
        if (sBtlCheckSummonUnit_Exist(0) == 2)
          return 1;
        StockUnitData = sBtlGetStockUnitData(wk->macter_csr);
        v18 = wk->stock_id[wk->macter_csr];
        if (!sBtlCheckMagCost(StockUnitData, v18, 0))
          return 1;
        sBtlPlaySE(8u);
        v14 = 3;
        goto LABEL_70;
      case 2:
        if (sBtlCheckSummonUnit_Exist(0) == 2)
          return 1;
        sBtlPlaySE(8u);
        sBtlResetSummonPanel(5);
        v12 = 2;
LABEL_42:
        sBtlSetSelectAnim(v12);
        return 1;
      case 3:
        v11 = wk;
        if (v11->itemList->num < 1)
          return 1;
        sBtlPlaySE(8u);
        v14 = 6;
        goto LABEL_70;
      case 4:
        v11 = wk;
        if (v11->bulletList->num < 1)
          return 1;
        sBtlPlaySE(8u);
        v14 = 7;
LABEL_70:
        sBtlResetSummonPanel(v14);
        sBtlSetSelectAnim(0);
        wk->macter_csr = 0;
        result = 1;
        break;
      case 5:
        sBtlSetMenuPara(11, -1, -1, -1, -1, 0);
        result = 1;
        break;
      default:
        return 1;
    }
  }
  return result;
}

// 0x1f6cee0
static bool SummonMenuFunc_00(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  SBATTLE_WORK *v6;
  s32 *p_macter_csr;
  s32 stock_num;
  SBATTLE_WORK *v11;
  s32 *v12;
  s32 v13;

  if (wk->sgstat[1])
    return 1;
  if (CHECK_REP(4101, 1))
  {
    v6 = wk;
    p_macter_csr = &v6->macter_csr;
    stock_num = v6->stock_num;
    sBtlParaAdd(p_macter_csr, 1, stock_num - 1, 0);
    goto LABEL_14;
  }
  if (CHECK_REP(4100, 1))
  {
    v11 = wk;
    v12 = &v11->macter_csr;
    v13 = v11->stock_num;
    sBtlParaDec(v12, 1, v13 - 1);
LABEL_14:
    sBtlPlaySE(0);
    return 1;
  }
  if (CHECK_TRIG(4097, 1))
  {
    sBtlPlaySE(8u);
    sBtlResetSummonPanel(1);
    sBtlSetSelectAnim(0);
    wk->macter_csr = 0;
    return 1;
  }
  else
  {
    if (!CHECK_TRIG(4096, 1))
      return 1;
    if (!CheckSummonTarget(sBtlPlayer))
      return 1;
    sBtlPlaySE(8u);
    sBtlSetSelectAnim(2);
    *(u32 *)wk->sgstat = 1;
    return 1;
  }
}

// 0x1f6d1d0
static bool SummonMenuFunc_10(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  if (wk->sgstat[1])
    return 1;
  if (!sBtlCheckSelectAnim())
    return 0;
  sBtlSetMenuPara(1, wk->macter_csr, -1, -1, -1, 0);
  return 1;
}

// 0x1f6d2d0
static bool SummonMenuFunc_20(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  SBATTLE_WORK *v4;
  s32 v5;
  s16 *sgstat;

  v4 = wk;
  v5 = (u16)v4->sgstat[1];
  if (v5 == 1)
  {
    v4 = wk;
    sBtlSetMenuPara(8, v4->summonindex[0], -1, -1, -1, 0);
    return 1;
  }
  if (v5)
    return 1;
  if (!sBtlCheckSelectAnim())
    return 0;
  sgstat = wk->sgstat;
  ++sgstat[1];
  return 1;
}

// 0x1f6d400
static bool SummonMenuFunc_30(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  SBATTLE_WORK *v4;
  s16 *gstat;
  u32 v6;
  SBTLUNIT_WORK *Nakama;
  s8 v9;
  SBATTLE_WORK *v11;
  s32 *stock_useskillp;
  s64 v13;
  s32 stock_skillnum;
  SBATTLE_WORK *v17;
  SBTLUNIT_LISTWORK *v18;
  s32 tgt_csr;
  SBTLUNIT_WORK *v20;
  SBATTLE_WORK *v22;
  s32 *v23;
  s64 v24;
  s32 v25;
  SBATTLE_WORK *v27;
  SBTLUNIT_LISTWORK *tgtList;
  u32 v30;
  SBTLUNIT_LISTWORK *p_tgtList;
  SBTLUNIT_WORK *v33;
  s32 ListID;
  SBATTLE_WORK *v37;
  SBTLUNIT_LISTWORK *UnitList;
  SBTLUNIT_WORK *v39;
  s32 v40;
  SBATTLE_WORK *v42;
  s16 *v44;
  SBATTLE_WORK *v47;
  s32 *p_tgt_csr;
  s32 count;
  SBATTLE_WORK *v51;
  s64 v52;
  SBTLUNIT_LISTWORK *v53;
  SBTLUNIT_LISTWORK *v54;
  SBATTLE_WORK *v57;
  s32 *v58;
  s32 v59;
  s16 *v61;

  v4 = wk;
  gstat = v4->gstat;
  v6 = gstat[1];
  if (v6 > 3)
    return 1;
  switch (v6)
  {
    case 0u:
      gstat = wk->gstat;
      ++gstat[1];
      Nakama = sBtlGetNakama(0);
      sBtlGetSkillMenu(Nakama, 0x1000u);
      v9 = 0;
      goto LABEL_13;
    case 1u:
      if (CHECK_REP(4100, 1))
      {
        v11 = wk;
        stock_useskillp = v11->stock_useskillp;
        v13 = v11->summonindex[0];
        stock_skillnum = v11->stock_skillnum;
        sBtlParaDec(&stock_useskillp[v13], 1, stock_skillnum - 1);
        goto LABEL_21;
      }
      if (CHECK_REP(4101, 1))
      {
        v22 = wk;
        v23 = v22->stock_useskillp;
        v24 = v22->summonindex[0];
        v25 = v22->stock_skillnum;
        sBtlParaAdd(&v23[v24], 1, v25 - 1, 0);
LABEL_21:
        sBtlPlaySE(0);
        return 1;
      }
      if (CHECK_TRIG(4096, 1))
      {
        v37 = wk;
        UnitList = sBtlCreateUnitList(48);
        v37->tgtList = UnitList;
        v39 = sBtlGetNakama(0);
        v40 = wk->stock_useskill[wk->stock_useskillp[wk->summonindex[0]]];
        if (sBtlCreateTargetList_csr(v39, v40))
        {
          sBtlPlaySE(8u);
          v42 = wk;
          v44 = v42->gstat;
          v42->tgt_csr = 0;
          ++v44[1];
          sBtlResetColorFlag();
        }
        else
        {
          v61 = wk->gstat;
          v61[1] += 2;
          sBtlPlaySE(8u);
        }
        v9 = 3;
LABEL_13:
        sBtlSetSelectAnim(v9);
        return 1;
      }
      else
      {
        if (!CHECK_TRIG(4097, 1))
          return 1;
        sBtlPlaySE(8u);
        sBtlResetSummonPanel(3);
        sBtlSetSelectAnim(0);
        wk->macter_csr = 0;
        return 1;
      }
    case 2u:
      v4 = wk;
      v4->status |= 0x80000u;
      if (CHECK_TRIG(4096, 1))
      {
        sBtlPlaySE(8u);
        v17 = wk;
        ++v17->gstat[1];
LABEL_50:
        v17->status &= ~0x80000u;
        return 1;
      }
      if (CHECK_TRIG(4097, 1))
      {
        v27 = wk;
        tgtList = v27->tgtList;
        --v27->gstat[1];
        if (!v30)
        sBtlDeleteUnitList(tgtList, 0);
        p_tgtList = &wk->tgtList;
        p_tgtList = 0;
        sBtlResetColorFlag();
        sBtlSetSelectAnim(0);
        v17 = wk;
        goto LABEL_50;
      }
      if (CHECK_REP(4100, 1))
      {
        v47 = wk;
        p_tgt_csr = &v47->tgt_csr;
        count = v47->tgtList->count;
        sBtlParaDec(p_tgt_csr, 1, count - 1);
        sBtlPlaySE(0);
      }
      else
      {
        if (!CHECK_REP(4101, 1))
          return 1;
        v57 = wk;
        v58 = &v57->tgt_csr;
        v59 = v57->tgtList->count;
        sBtlParaAdd(v58, 1, v59 - 1, 0);
        sBtlPlaySE(0);
      }
      sBtlResetColorFlag();
      return 1;
    case 3u:
      v4 = wk;
      v18 = v4->tgtList;
      tgt_csr = v4->tgt_csr;
      v20 = sBtlSearchUnit_ID(v18, tgt_csr);
      if (v20)
      {
        v33 = v20;
        if (sBtlCheckDamageTarget(v20))
          goto LABEL_54;
      }
      ListID = -1;
      goto LABEL_86;
LABEL_54:
      ListID = v33->ListID;
LABEL_86:
      wk->tgt_ListID[wk->summonindex[0]] = ListID;
      v51 = wk;
      v52 = v51->summonindex[0];
      sBtlSetMenuPara(2, v51->summonindex[0], v51->stock_useskill[v51->stock_useskillp[v52]], -1, -1, v51->tgt_ListID[v52]);
      v53 = wk->tgtList;
      sBtlDeleteUnitList(v53, 0);
      v54 = &wk->tgtList;
      v54 = 0;
      return 1;
    default:
      return 1;
  }
}

// 0x1f6de80
static bool SummonMenuFunc_40(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  SBATTLE_WORK *v6;
  s32 num;
  s16 *gstat;
  s32 v9;
  s32 *p_macter_csr;
  SBATTLE_WORK *v16;
  s32 *v18;
  SBATTLE_WORK *v21;

  v6 = wk;
  if (v6->bulletList->num >= 6)
    num = 6;
  else
    num = v6->bulletList->num;
  v6 = wk;
  gstat = v6->gstat;
  v9 = gstat[1];
  if (v9 == 2)
    return 1;
  if (v9 != 1)
  {
    if (!gstat[1])
    {
      gstat = wk->gstat;
      ++gstat[1];
      sBtlSetSelectAnim(0);
      return 1;
    }
    RestartBattle();
    sBtlRestart_Scene();
    sBtlResetAction(wk);
    v16 = wk;
    *(u32 *)v16->sgstat = 0;
    v16->menutype = 0;
    sBtlResetMidashiAnim(0);
    return 1;
  }
  if (CHECK_REP(4100, 1))
  {
    p_macter_csr = &wk->macter_csr;
    sBtlParaDec(p_macter_csr, 1, num - 1);
    goto LABEL_24;
  }
  if (CHECK_REP(4101, 1))
  {
    v18 = &wk->macter_csr;
    sBtlParaAdd(v18, 1, num - 1, 0);
LABEL_24:
    sBtlPlaySE(0);
    return 1;
  }
  if (CHECK_TRIG(4096, 1))
  {
    v21 = wk;
    ++v21->gstat[1];
    sBtlSetMenuPara(10, -1, -1, v21->bulletList->data[v21->macter_csr]->id, -1, 0);
    return 1;
  }
  else
  {
    if (!CHECK_TRIG(4097, 1))
      return 1;
    sBtlPlaySE(8u);
    sBtlResetSummonPanel(1);
    sBtlSetSelectAnim(0);
    wk->macter_csr = 3;
    return 1;
  }
}

// 0x1f6e490
static bool SummonMenuFunc_50(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  SBATTLE_WORK *v6;
  s32 *p_macter_csr;
  s32 stock_num;
  SBATTLE_WORK *v11;
  s32 *v12;
  s32 v13;

  if (wk->sgstat[1])
    return 1;
  if (CHECK_REP(4101, 1))
  {
    v6 = wk;
    p_macter_csr = &v6->macter_csr;
    stock_num = v6->stock_num;
    sBtlParaAdd(p_macter_csr, 1, stock_num - 1, 0);
    goto LABEL_14;
  }
  if (CHECK_REP(4100, 1))
  {
    v11 = wk;
    v12 = &v11->macter_csr;
    v13 = v11->stock_num;
    sBtlParaDec(v12, 1, v13 - 1);
LABEL_14:
    sBtlPlaySE(0);
    return 1;
  }
  if (CHECK_TRIG(4097, 1))
  {
    sBtlPlaySE(8u);
    sBtlResetSummonPanel(1);
    sBtlSetSelectAnim(0);
    wk->macter_csr = 1;
    return 1;
  }
  else
  {
    if (!CHECK_TRIG(4096, 1))
      return 1;
    if (wk->macter_csr)
    {
      sBtlPlaySE(8u);
      sBtlSetSelectAnim(2);
      *(u32 *)wk->sgstat = 1;
      return 1;
    }
    else
    {
      sBtlPlaySE(8u);
      sBtlResetSummonPanel(4);
      sBtlSetSelectAnim(0);
      wk->macter_csr = 0;
      return 1;
    }
  }
}

// 0x1f6e7d0
static bool SummonMenuFunc_60(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  void *v3;
  SBATTLE_WORK *v5;
  s32 v6;
  s16 *sgstat;

  v3 = NewSpecific(SBTLPNL_MENU, 5u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__765A5196FA05FDEC28A3AE3AEC5DD9A7EB92985958548A37745169C2DD06496C, 0);
  v5 = wk;
  v6 = (u16)v5->sgstat[1];
  if (v6 == 1)
  {
    v5 = wk;
    sBtlSetMenuPara(*((u32 *)&v3[2].klass + v5->macter_csr), v5->summonindex[0], -1, -1, -1, 0);
    return 1;
  }
  if (v6)
    return 1;
  if (!sBtlCheckSelectAnim())
    return 0;
  sgstat = wk->sgstat;
  ++sgstat[1];
  return 1;
}

// 0x1f6e950
static bool SummonMenuFunc_70(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  SBATTLE_WORK *v6;
  s32 num;
  s16 *gstat;
  SBATTLE_WORK *v12;
  s32 *p_macter_csr;
  SBATTLE_WORK *v17;
  s32 itemid;
  SBTLITEM_TBL *Itemtbl;
  s32 sklid;
  SBTLACTION_WORK *actwk;
  s16 *v26;
  s32 *v29;
  SBATTLE_WORK *v31;
  SBTLUNIT_LISTWORK *tgtList;
  u32 v34;
  SBTLUNIT_LISTWORK *p_tgtList;
  u16 side;
  SBATTLE_WORK *v40;
  SBATTLE_WORK *v42;
  s32 *p_tgt_csr;
  s32 count;
  SBATTLE_WORK *v47;
  s32 *v48;
  s32 v49;

  v6 = wk;
  if (v6->itemList->num >= 6)
    num = 6;
  else
    num = v6->itemList->num;
  v6 = wk;
  gstat = v6->gstat;
  switch (gstat[1])
  {
    case 0:
      gstat = wk->gstat;
      ++gstat[1];
      sBtlSetSelectAnim(0);
      return 1;
    case 1:
      if (CHECK_REP(4100, 1))
      {
        p_macter_csr = &wk->macter_csr;
        sBtlParaDec(p_macter_csr, 1, num - 1);
        goto LABEL_31;
      }
      if (CHECK_REP(4101, 1))
      {
        v29 = &wk->macter_csr;
        sBtlParaAdd(v29, 1, num - 1, 0);
LABEL_31:
        sBtlPlaySE(0);
        return 1;
      }
      if (!CHECK_TRIG(4096, 1))
      {
        if (!CHECK_TRIG(4097, 1))
          return 1;
        sBtlPlaySE(8u);
        sBtlResetSummonPanel(1);
        sBtlSetSelectAnim(0);
        wk->macter_csr = 3;
        return 1;
      }
      side = sBtlGetItemtbl(wk->itemList->data[wk->macter_csr]->id)->side;
      if ((side & 0x2000) == 0 && (side & 0x5000) != 0)
      {
        v40 = wk;
        v40->gstat[1] = 3;
        v40->panelwk->data[0]->itemid = v40->itemList->data[v40->macter_csr]->id;
        return 1;
      }
      return 1;
    case 2:
      v6 = wk;
      v6->status |= 0x80000u;
      if (CHECK_TRIG(4096, 1))
      {
        sBtlPlaySE(8u);
        v17 = wk;
        ++v17->gstat[1];
LABEL_79:
        v17->status &= ~0x80000u;
        return 1;
      }
      if (CHECK_TRIG(4097, 1))
      {
        v31 = wk;
        tgtList = v31->tgtList;
        --v31->gstat[1];
        if (!v34)
        sBtlDeleteUnitList(tgtList, 0);
        p_tgtList = &wk->tgtList;
        p_tgtList = 0;
        sBtlResetColorFlag();
        sBtlSetSelectAnim(0);
        v17 = wk;
        goto LABEL_79;
      }
      if (CHECK_REP(4100, 1))
      {
        v42 = wk;
        p_tgt_csr = &v42->tgt_csr;
        count = v42->tgtList->count;
        sBtlParaDec(p_tgt_csr, 1, count - 1);
        sBtlPlaySE(0);
      }
      else
      {
        if (!CHECK_REP(4101, 1))
          return 1;
        v47 = wk;
        v48 = &v47->tgt_csr;
        v49 = v47->tgtList->count;
        sBtlParaAdd(v48, 1, v49 - 1, 0);
        sBtlPlaySE(0);
      }
LABEL_113:
      sBtlResetColorFlag();
      return 1;
    case 3:
      v6 = wk;
      sBtlGetItemtbl(v6->panelwk->data[0]->itemid);
      goto LABEL_54;
    case 4:
      v6 = wk;
      itemid = v6->panelwk->data[0]->itemid;
      wk->actaiwk->targetID = v6->playerID;
      sBtlCheckItemCost(itemid, 1);
      sBtlCheckItemCost_GBWK(itemid, 1);
      Itemtbl = sBtlGetItemtbl(itemid);
      sBtlGetSkilltbl(Itemtbl->sklid);
      sBtlStatusBitOn(wk, 0x10u);
      sklid = Itemtbl->sklid;
      sBtlSetUseSkill(wk, sklid, 0);
      sBtlReleaseItemList(wk->itemList);
LABEL_54:
      ++wk->gstat[1];
      return 1;
    case 5:
      actwk = wk->actwk;
      if (actwk->status == 37 && actwk->action_flg != 1)
        return 1;
      sBtlStatusBitOff(wk, 0xFFFFFFEF);
      v26 = wk->gstat;
      ++v26[1];
      goto LABEL_113;
    default:
      RestartBattle();
      sBtlRestart_Scene();
      sBtlResetAction(wk);
      v12 = wk;
      *(u32 *)v12->sgstat = 0;
      v12->menutype = 0;
      sBtlResetMidashiAnim(0);
      return 1;
  }
}

// 0x1f6dd40
void sBtlResetColorFlag(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v5;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (!pUnit)
      goto LABEL_4;
    v5 = sBtlCheckDamageTarget(pUnit);
    if (!v5)
      goto LABEL_4;
    pUnit->vstatus &= ~0x100u;
LABEL_4:
    ++v1;
  }
}

// 0x1f6f2d0
void Init(void) {
  s64 v3;
  __int128 v5;
  SBATTLE_WORK *wk_local;
  s32 *p_CameraTgtSelect_Cnt;
  s32 *p_AttackBtn_NgTime;

  InitBattle();
  sBtlPlayerInit();
  v3 = *((u64 *)*((MethodInfo *)sBtlPlayer + 2).virtualMethodPointer + 43);
  *(u16 *)(v3 + 16) = 0;
  *(u32 *)(v3 + 32) = 0;
  *(u64 *)(v3 + 20) = 0;
  *(u8 *)(v3 + 28) = 0;
  InitCameraLockOn();
  *(u64 *)&v5 = 0xFFFFFFFFLL;
  *((u64 *)&v5 + 1) = 0xFFFFFFFFLL;
  *(_OWORD *)((char *)*((const MethodInfo *)sBtlPlayer + 2).virtualMethodPointer + 484) = v5;
  sBtlInitGun();
  sBtlInitSetsuma();
  sBtlPlayerRSdDash_Init();
  wk_local = wk;
  p_CameraTgtSelect_Cnt = &wk_local->CameraTgtSelect_Cnt;
  wk_local->KaihiSetsuma = 0;
  p_AttackBtn_NgTime = &wk_local->AttackBtn_NgTime;
  wk_local->bCameraGazeOffToOn_Press = 0;
  wk_local->bHuumaCancel = 0;
  wk_local->XAtkGouto1 = 0;
  wk_local->ComboMotRetryUse = 0;
  wk_local->huuma_weakicon = 0;
  *(u64 *)p_CameraTgtSelect_Cnt = 0;
  *(u64 *)p_AttackBtn_NgTime = 3;
  gSpriteInitDone = 0;
}

// 0x1f6f8a0
void sBtlReady_BattleSpriteCtrl(void) {
  if (!dds3SearchProcessName("sbattle"))
    return;
  Add(0);
}

// 0x1f6f980
void sBtlAwDeleteAll(void) {
  DeleteAll();
}

// 0x1f6f9f0
void sBtlBattleVictoryStart(void) {
  DeleteAll();
}

// 0x1f6fac0
void sBtlBattleEnd(void) {
  DeleteAll();
}

// 0x1f6fb90
static void sBtlPlayer_CommPad_Clear(void) {
  SBATTLE_WORK *wk_local;

  wk_local = wk;
  wk_local->bSpiritSkill = 0;
  wk_local->bCameraGazeOff = 0;
  *(u32 *)&wk_local->bCameraTgtSelect1 = 0;
  *(u16 *)&wk_local->bCameraTgtSelectR = 0;
  *(u64 *)&wk_local->bChgAx = 0;
  *(u64 *)&wk_local->bGunMode = 0;
  *(u64 *)&wk_local->bRU = 0;
}

// 0x1f6fc10
static void sBtlPlayer_CommPad(void) {
  SBATTLE_WORK *wk_local;
  SBATTLE_WORK *v15;
  SBATTLE_WORK *v19;
  SBATTLE_WORK *v26;
  SBATTLE_WORK *v31;
  bool v39;
  bool IsSceanStop;
  SBATTLE_WORK *v44;
  s32 bCameraTgtSelect1Cnt;
  bool v47;
  SBATTLE_WORK *v49;
  bool IsBattleKey;
  SBATTLE_WORK *v51;
  s32 v52;
  SBATTLE_WORK *v53;
  u32 v54;
  SBATTLE_WORK *v55;
  s32 CameraTgtSelect_Cnt;
  SBATTLE_WORK *v57;
  bool v68;
  u32 v70;
  SBATTLE_WORK *v71;
  SBATTLE_WORK *v73;

  wk_local = wk;
  wk_local->bSpiritSkill = 0;
  wk_local->bCameraGazeOff = 0;
  *(u32 *)&wk_local->bCameraTgtSelect1 = 0;
  *(u16 *)&wk_local->bCameraTgtSelectR = 0;
  *(u64 *)&wk_local->bChgAx = 0;
  *(u64 *)&wk_local->bGunMode = 0;
  *(u64 *)&wk_local->bRU = 0;
  if (!sBtlIsBattleKey(4121, 2))
    goto LABEL_10;
  if (wk->battlemode == 1)
    goto LABEL_10;
  goto LABEL_26;
  if (wk->battlemode == 1)
  {
LABEL_10:
    goto LABEL_11;
  }
LABEL_26:
  sBtlBS_LASTB1_Action_Req();
  wk->bRU = 1;
LABEL_11:
  if (!sBtlIsBattleKey(4120, 2))
    goto LABEL_17;
  if (wk->mode == 12)
  {
    goto LABEL_17;
  }
  sBtlBS_LASTB1_Action_Req();
  wk->bRR = 1;
LABEL_17:
  if (!wk->bAssistAttackBtn)
    goto LABEL_61;
  if (!sBtlIsBattleKey(4121, 1))
  {
LABEL_40:
    goto LABEL_41;
  }
  v15 = wk;
  if (v15->battlemode == 1)
    goto LABEL_40;
  v15 = wk;
  v15->bRU_Assist = 1;
LABEL_41:
  if (!sBtlIsBattleKey(4120, 1))
  {
LABEL_61:
    goto LABEL_62;
  }
  v19 = wk;
  if (v19->mode == 12)
    goto LABEL_61;
  v19 = wk;
  v19->bRR_Assist = 1;
LABEL_62:
  if (IsSWAZA_AdvanceCheck())
  {
LABEL_104:
    goto LABEL_105;
  }
  if (!sBtlIsBattleKey(4170, 2))
  {
LABEL_79:
    goto LABEL_80;
  }
  v26 = wk;
  if (v26->mode == 12)
    goto LABEL_79;
  v26 = wk;
  v26->bJump = 1;
LABEL_80:
  if (!sBtlIsBattleKey(4170, 1))
  {
LABEL_98:
    goto LABEL_99;
  }
  v31 = wk;
  if (v31->mode == 12)
    goto LABEL_98;
  v31 = wk;
  v31->bJump2 = 1;
LABEL_99:
  if (!!sBtlIsBattleKey(4124, 2))
  {
    wk->bKaihi = 1;
    if (!sBtlIsBattleKey(4155, 1))
      goto LABEL_104;
    goto LABEL_116;
  }
  if (!sBtlIsBattleKey(4155, 1))
    goto LABEL_104;
LABEL_116:
  wk->bGuard = 1;
LABEL_105:
  v39 = IsSceanStop();
  if (v39)
    goto LABEL_180;
  if (wk->kaiwaflg)
    goto LABEL_180;
  v44 = wk;
  if (v44->battlemode == 1)
    goto LABEL_180;
  v44 = wk;
  bCameraTgtSelect1Cnt = v44->bCameraTgtSelect1Cnt;
  if (bCameraTgtSelect1Cnt >= 1)
  {
    v44 = wk;
    bCameraTgtSelect1Cnt = v44->bCameraTgtSelect1Cnt;
    v44->bCameraTgtSelect1Cnt = bCameraTgtSelect1Cnt - 1;
  }
  if (!wk->bCameraGazeOffToOn_Press)
  {
    IsBattleKey = sBtlIsBattleKey(4125, 1);
    if (IsBattleKey)
      goto LABEL_150;
    v55 = wk;
    CameraTgtSelect_Cnt = v55->CameraTgtSelect_Cnt;
    if (CameraTgtSelect_Cnt >= 11)
    {
      if (!v54)
      {
        v55 = wk;
      }
      if (v55->bCameraTgtSelectUse)
        goto LABEL_176;
    }
    else
    {
      if (!v54)
      {
        v55 = wk;
        CameraTgtSelect_Cnt = v55->CameraTgtSelect_Cnt;
      }
      if (CameraTgtSelect_Cnt < 1)
        goto LABEL_176;
    }
    v55 = wk;
    v55->bCameraTgtSelect1 = 1;
LABEL_176:
    v49 = wk;
    goto LABEL_179;
  }
  v47 = sBtlIsBattleKey(4125, 1);
  if (!v47)
  {
    v49 = wk;
    v49->bCameraGazeOffToOn_Press = 0;
LABEL_179:
    v49->CameraTgtSelect_Cnt = 0;
    goto LABEL_180;
  }
LABEL_150:
  v51 = wk;
  v52 = v51->CameraTgtSelect_Cnt;
  if (v52 <= 10)
  {
    v51 = wk;
    v52 = v51->CameraTgtSelect_Cnt;
    v51->CameraTgtSelect_Cnt = v52 + 1;
LABEL_154:
    v53 = wk;
    if (v53->CameraTgtSelect_Cnt < 11)
      goto LABEL_180;
    goto LABEL_160;
  }
  {
    goto LABEL_154;
  }
  v53 = wk;
  if (v53->CameraTgtSelect_Cnt < 11)
    goto LABEL_180;
LABEL_160:
  v53 = wk;
  v53->bCameraTgtSelect2 = 1;
LABEL_180:
  v57 = wk;
  if (!v57->bCameraTgtSelect2)
  {
    v57->bCameraTgtSelectUse = 0;
    goto LABEL_217;
  }
  if (sBtlIsBattleKey(4185, 2))
    goto LABEL_184;
  goto LABEL_193;
  if (!sBtlIsBattleKey(4185, 2))
  {
LABEL_193:
    if (sBtlIsBattleKey(4183, 2))
    {
      wk->bCameraTgtSelectR = 1;
      goto LABEL_217;
    }
    if (sBtlIsBattleKey(4182, 2))
    {
      wk->bCameraTgtSelectU = 1;
      goto LABEL_217;
    }
    if (sBtlIsBattleKey(4184, 2))
    {
      wk->bCameraTgtSelectD = 1;
      goto LABEL_217;
    }
    goto LABEL_217;
  }
LABEL_184:
  wk->bCameraTgtSelectL = 1;
LABEL_217:
  v68 = sBtlIsBattleKey(4126, 2);
  if (v68)
  {
    v71 = wk;
    v71->bCameraGazeOff = 1;
    v71->bCameraGazeOffToOn_Press = 0;
  }
  else
  {
    if (v70)
    {
      if (!wk->CameraGazeOff)
        return;
    }
    else
    {
      if (!wk->CameraGazeOff)
        return;
    }
    if (sBtlIsBattleKey(4125, 2))
    {
      v73 = wk;
      v73->bCameraGazeOff = 1;
      v73->bCameraGazeOffToOn_Press = 1;
      *(u32 *)&v73->bCameraTgtSelect1 = 0;
      *(u16 *)&v73->bCameraTgtSelectR = 0;
      *(u64 *)&v73->CameraTgtSelect_Cnt = 0;
    }
  }
}

// 0x1f725b0
static bool sBtlPlayer_Pad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic) {
  u32 v6;
  dds3Basic_t *ActiveScene;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v13;
  SBATTLE_WORK *v15;
  u32 status;
  bool IsSceanStop;
  void *Instance;
  SBATTLE_WORK *v19;
  f32 PlayerBtlStartDir;
  long f64 v21;
  long f64 v22;
  s32 encountno;
  f32 v25;
  s32 v26;
  f32 v27;
  s32 v28;
  f32 x;
  s32 v31;
  f32 z;
  f32 v33;
  f32 y;
  f32 w;
  f32 v36;
  long f64 v37;
  long f64 v38;
  s32 mode;
  s32 v48;
  s32 v49;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBATTLE_WORK *v55;
  SBATTLE_WORK *v57;
  s32 v61;
  s32 JumpAfterCnt;
  bool v63;
  SBATTLE_WORK *v65;
  SBATTLE_WORK *v68;
  s32 v69;
  s32 v71;
  dds3ModelHandle_t *v72;
  SBATTLE_WORK *v74;
  s32 v75;
  bool v76;
  s32 spirit_enemy;
  s32 ViceLevel;
  SBATTLE_WORK *v79;
  s32 v80;
  s32 v81;
  SBATTLE_WORK *v82;
  s32 vice1stKoufun;
  s32 v84;
  f32 v85;
  f32 v87;
  f32 v88;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  SBATTLE_WORK *v94;
  u32 v95;
  SBTLUNIT_WORK *Nakama2;
  SBTLEFF_WORK *Eff;
  SBATTLE_WORK *v99;
  SBTLEFF_WORK *sword_eff;
  SBTLEFF_WORK *p_sword_eff;
  SBTLEFF_LISTWORK *effList;
  SBATTLE_WORK *v104;
  s32 v106;
  u32 v107;
  s32 v108;
  bool IsBattleKey;
  SBATTLE_WORK *v114;
  u32 v115;
  bool v116;
  SBATTLE_WORK *v117;
  _BOOL4 ComboLRU_StartOk;
  u32 v119;
  bool v120;
  u32 v121;
  SBATTLE_WORK *v122;
  s32 ComboLRU_Cnt;
  SBATTLE_WORK *v124;
  s32 v125;
  s32 motionno;
  dds3ModelHandle_t *hModel;
  SBATTLE_WORK *v130;
  u32 v134;
  s32 next_motionID;
  u32 v138;
  SBATTLE_WORK *v139;
  SBATTLE_WORK *v142;
  bool v145;
  u32 v147;
  SBATTLE_WORK *v148;
  s32 chargeSdCnt;
  bool v153;
  SBATTLE_WORK *v154;
  s32 v155;
  SBATTLE_WORK *v156;
  SBATTLE_WORK *v157;
  u32 v158;
  SBATTLE_WORK *v159;
  s32 v160;
  SBATTLE_WORK *v161;
  s32 v162;
  f32 v163;
  f32 v164;
  f32 v165;
  f32 v166;
  SBATTLE_WORK *v167;
  f32 chargeSdCnt2;
  f32 v169;
  dds3ModelHandle_t *v170;
  f32 v171;
  bool v174;
  u32 v176;
  SBATTLE_WORK *v177;
  s32 v178;
  u32 v179;
  SBATTLE_WORK *v180;
  s32 chargeLcCnt;
  SBATTLE_WORK *v182;
  s32 v183;
  f32 v184;
  f32 v185;
  f32 v186;
  f32 v187;
  SBATTLE_WORK *v188;
  f32 chargeLcCnt2;
  f32 v190;
  dds3ModelHandle_t *v191;
  f32 v192;
  bool v194;
  u32 v196;
  SBATTLE_WORK *v197;
  s32 chargeAxCnt;
  u32 v199;
  SBATTLE_WORK *v200;
  s32 v201;
  SBATTLE_WORK *v202;
  s32 v203;
  f32 v204;
  f32 v205;
  f32 v206;
  f32 v207;
  SBATTLE_WORK *v208;
  f32 chargeAxCnt2;
  f32 v210;
  dds3ModelHandle_t *v211;
  f32 v212;
  SBATTLE_WORK *v214;
  SBATTLE_WORK *v216;
  SBATTLE_WORK *v218;
  dds3ModelHandle_t *v219;
  bool SpiritSkillChk;
  SBATTLE_WORK *v226;
  s32 GunLockOnNum;
  _BOOL4 v228;
  u32 v229;
  SBATTLE_WORK *v234;
  SBATTLE_WORK *v235;
  SBATTLE_WORK *v236;
  s32 v237;
  bool v238;
  SBATTLE_WORK *v239;
  s32 v240;
  SBATTLE_WORK *v244;
  s32 hstatus;
  s32 v248;
  bool v273;
  SBATTLE_WORK *v276;
  bool v277;
  s32 v280;
  SBATTLE_WORK *v281;
  SBATTLE_WORK *v287;
  u32 v288;
  s32 v289;
  s16 v294;
  s32 v300;
  s32 v307;
  s32 v308;
  s32 v316;
  s32 v318;
  dds3ModelHandle_t *v320;
  SBATTLE_WORK *v323;
  s32 v325;
  s32 v326;
  s32 v327;
  s32 v328;
  s32 v329;
  s32 cmstatus;
  f32 v331;
  f32 v332;
  f32 AnlogKey;
  f32 v337;
  s16 *p_anlog_cnt;
  SBATTLE_WORK *v343;
  s32 anlog_cnt;
  s32 v345;
  dds3ModelHandle_t *v346;
  s32 v348;
  s32 v349;
  s32 v351;
  dds3ModelHandle_t *v352;
  s32 v353;
  f32 v354;
  f32 m_BlendTree2DX;
  f32 v356;
  dds3ModelHandle_t *v357;
  f32 MotionFrameF;
  f32 v359;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 hp;
  s32 v364;
  dds3ModelHandle_t *v365;
  f32 v366;
  f32 v367;
  f32 v368;
  f32 v369;
  s32 v370;
  u32 v371;
  f32 m_BlendTree1D;
  f32 v373;
  dds3ModelHandle_t *v374;
  f32 v375;
  s32 v376;
  f32 v377;
  f32 v378;
  f32 v379;
  f32 v380;
  f32 v381;
  f32 v382;
  f32 v383;
  f32 v384;
  sdatUnitWork_t *v385;
  s32 v386;
  f32 m_BlendTree2DY;
  f32 v388;
  f32 v389;
  f32 v391;
  f32 v392;
  s32 v393;
  f32 v395;
  f32 v397;
  f32 v399;
  f32 v400;
  f32 v401;
  s32 v403;
  s32 v404;
  s32 v405;
  dds3ModelHandle_t *v406;
  dds3ModelHandle_t *v407;
  dds3ModelHandle_t *v409;
  s32 v410;
  unsigned __int128 v415;
  s64 v416;
  s64 v417;
  sdfVector4_t v418;
  sdfVector4_t v419;
  sdfVector4_t v420;
  sdfVector4_t v421;

  v416 = 0;
  v417 = 0;
  v415 = 0u;
  goto LABEL_3;
  if (v6)
  {
LABEL_3:
    goto LABEL_4;
  }
LABEL_4:
  if (!drawEnd)
    goto LABEL_173;
  if ((wk->status & 2) == 0)
    goto LABEL_173;
  ActiveScene = dds3GetActiveScene();
  if (ActiveScene)
  {
    if (!wk)
      goto LABEL_173;
    UnitMng = wk->UnitMng;
    if (!UnitMng)
      goto LABEL_173;
    UnitMng = wk->UnitMng;
    playerID = wk->playerID;
    v13 = sBtlSearchUnit_ID(UnitMng, playerID);
    v15 = wk;
    status = v15->status;
    v15->bIsNoMoveBad = 0;
    if ((status & 0x10000) == 0)
    {
LABEL_172:
      PlayerAllSync(v13);
      goto LABEL_173;
    }
    v15 = wk;
    status = v15->status;
    if ((status & 8) != 0)
      goto LABEL_173;
    v15 = wk;
    if (v15->AttackBtn_NgTime >= 1)
    {
      IsSceanStop = IsSceanStop();
      if (!IsSceanStop)
      {
        --wk->AttackBtn_NgTime;
      }
    }
    if (wk->huuma_weakicon)
    {
      Instance = get_Instance(0);
      BackIconState(Instance, 0);
      wk->huuma_weakicon = 0;
    }
    if (!((LODWORD(v13->pos.x) & 0x7FFFFFFFu) <= 0x7F800000 && (LODWORD(v13->pos.z) & 0x7FFFFFFFu) < 0x7F800001))
    {
      v19 = wk;
      *(u64 *)&v13->pos.x = *(u64 *)&v19->PlayerBtlStartPosX;
      v13->pos.z = v19->PlayerBtlStartPosZ;
      PlayerBtlStartDir = v19->PlayerBtlStartDir;
      v13->mv_rotbk = PlayerBtlStartDir;
      FromEuler(0.0, PlayerBtlStartDir * 0.017453292, 0.0);
      *(__n128 *)&v22 = sub_1B335A0(&v13->rot, 0, v21);
      sub_1B335A0(&v13->rotbk, 0, v22);
      encountno = wk->encountno;
      if (encountno <= 46)
        goto LABEL_60;
      goto LABEL_65;
    }
    encountno = wk->encountno;
    if (encountno <= 46)
    {
LABEL_60:
      if (encountno != 34)
      {
        if (encountno != 46)
          goto LABEL_100;
LABEL_82:
        if (IsSceanStop())
          goto LABEL_100;
        if (wk->mode != 1)
          goto LABEL_100;
        x = v13->pos.x;
        v31 = -999309312;
        if (x < -959.0 || (v31 = 1148174336, x > 959.0))
          LODWORD(v13->pos.x) = v31;
        v28 = 1157570560;
        z = v13->pos.z;
        if (z >= 2041.0)
        {
          v28 = 1165455360;
          if (z <= 3959.0)
            goto LABEL_100;
        }
        goto LABEL_99;
      }
LABEL_67:
      if (IsSceanStop())
        goto LABEL_100;
      if (wk->mode != 1)
      {
LABEL_100:
        v13->mv_spd.z = 0.0;
        v13->mv_spd.x = 0.0;
        v33 = v13->pos.x;
        y = v13->pos.y;
        v13->mv_rot = 0.0;
        v36 = v13->pos.z;
        w = v13->pos.w;
        *(__n128 *)&v37 = sub_1B332C0(0, v33, y, v36, w);
        *(__n128 *)&v38 = sub_1B335A0(&v416, 0, v37);
        sub_1B335A0(&v13->nextpos, 0, v38);
        if (!IsSceanStop())
          goto LABEL_146;
        if ((wk->status4 & 0x800000) == 0)
        {
          goto LABEL_108;
        }
        sBtlResetSetsuma_BossTalk(v13);
LABEL_108:
        mode = wk->mode;
        if (mode == 5)
          goto LABEL_146;
        mode = wk->mode;
        if (mode != 13)
        {
          mode = wk->mode;
          if (mode != 6)
          {
            mode = wk->mode;
            if (mode != 2)
            {
              if (!sBtlCheckSetsuma())
              {
                if (!CheckHuumaMes())
                {
                  if ((wk->status4 & 0x800000) == 0)
                  {
                    if (sBtlIsSetsumaPadStop())
                    {
                      if (sBtlIsBattleKey(4181, 1))
                      {
                        if (sBtlChkSceneEnemyLive())
                        {
                          v48 = sBtlInputChkSetsuma(v13);
                          if (v48)
                          {
                            v49 = v48;
                            sBtlSetFirstAtk(v49);
                            goto LABEL_173;
                          }
                        }
                      }
                      PlayerAllSync(v13);
                    }
                    EscapeGauge_FadeOut(v13);
                    if ((wk->status & 0x400) == 0)
                      goto LABEL_173;
                    sBtlResetGunMode_Eve();
                    goto LABEL_173;
                  }
                }
              }
            }
          }
        }
LABEL_146:
        para = v13->para;
        BadStatus = sBtlGetBadStatus(para);
        Reset_SupportAction(v13);
        v55 = wk;
        if ((v55->status2 & 0x20000000) == 0)
        {
          if (v13->actwk->status == 42)
          {
            v55 = wk;
            if (v55->chargeSdCnt)
            {
              Del(0, 0);
              AW_TameDel(0);
            }
            if (wk->chargeLcCnt)
            {
              Del(0, 0);
              AW_TameDel(0);
            }
            if (wk->chargeAxCnt)
            {
              Del(0, 0);
              AW_TameDel(0);
            }
            v57 = wk;
            *(u64 *)&v57->chargeAxCnt = 0;
            *(_OWORD *)&v57->chargeSdCnt = 0u;
            DeleteAll();
            sBtlResetGunMode(v13, 0);
            goto LABEL_172;
          }
          if (sBtlChkNowJump(sBtlPlayer))
          {
            v61 = 60;
          }
          else
          {
            JumpAfterCnt = v13->JumpAfterCnt;
            v63 = __OFSUB__(JumpAfterCnt, 1);
            v61 = JumpAfterCnt - 1;
            if (v61 < 0 != v63)
              goto LABEL_181;
          }
          v13->JumpAfterCnt = v61;
LABEL_181:
          if (!sBtlCheckMove_BadStatus(v13))
          {
            v65 = wk;
            v65->bIsNoMoveBad = 1;
            if (v65->mode == 1)
            {
              v65 = wk;
              if (v65->battlemode == 1)
              {
                if (BadStatus > 0xD || ((1 << BadStatus) & 0x3080) == 0 || v13->motionno == 2)
                  goto LABEL_322;
                goto LABEL_319;
              }
              if (BadStatus - 12 >= 2)
              {
                if (BadStatus == 6)
                {
                  motionno = v13->motionno;
                  if (motionno == 138)
                  {
                    hModel = v13->hModel;
                    if (mdlGetMotionFrameF(hModel) < 15.0)
                    {
                      if (!sBtlCheckMotionEnd(v13))
                        goto LABEL_322;
                    }
                  }
                  else
                  {
                    next_motionID = v13->next_motionID;
                    if (motionno != 139 && next_motionID != 138)
                    {
                      v108 = 138;
                      if (v138)
                        goto LABEL_321;
                      goto LABEL_320;
                    }
                    if (!v138)
                    if (!sBtlCheckLoopMotion(v13, next_motionID))
                      goto LABEL_322;
                  }
                  v108 = 139;
                  goto LABEL_321;
                }
                if (BadStatus != 7)
                  goto LABEL_322;
              }
              v71 = v13->motionno;
              if (v71 == 128)
              {
                v72 = v13->hModel;
                if (mdlGetMotionFrameF(v72) >= 15.0)
                  goto LABEL_319;
                if (sBtlCheckMotionEnd(v13))
                  goto LABEL_319;
              }
              else
              {
                v106 = v13->next_motionID;
                if (v71 != 2 && v106 != 128)
                {
                  v108 = 128;
                  if (!v107)
                    goto LABEL_320;
                  goto LABEL_321;
                }
                if (!v107)
                if (sBtlCheckLoopMotion(v13, v106))
                {
LABEL_319:
                  v108 = 2;
LABEL_320:
LABEL_321:
                  sBtlSetMotion(v13, v108, 0, 0, 0);
                }
              }
LABEL_322:
              sBtlPlayer_CommPad();
              Check_SupportAction_CameraLockOn(v13);
              if (!wk->chargeSdCnt)
              {
LABEL_326:
                if (wk->chargeLcCnt)
                {
                  Del(0, 0);
                  AW_TameDel(0);
                }
                if (wk->chargeAxCnt)
                {
                  Del(0, 0);
                  AW_TameDel(0);
                }
                v130 = wk;
                *(u64 *)&v130->chargeAxCnt = 0;
                *(_OWORD *)&v130->chargeSdCnt = 0u;
                DeleteAll();
                sBtlResetGunMode(v13, 0);
                PlayerAllSync(v13);
                if (wk->mode == 5)
                {
                  if (!v134)
                  SBTLMAIN_MODE_STOP_Task(v13);
                }
                else
                {
                  if (!v134)
                  sBtlSummonKey(v13);
                }
                goto LABEL_173;
              }
              Del(0, 0);
              AW_TameDel(0);
              goto LABEL_326;
            }
          }
          if (IsSceanStop())
          {
LABEL_244:
            if (EscapeGauge(v13))
              goto LABEL_1113;
            v85 = (loc_1FBC910)(0);
            v87 = v85;
            v89 = v88;
            v91 = v90;
            v93 = v92;
            v94 = wk;
            if (v94->sword_eff_step)
            {
              v94 = wk;
              if (!v94->sword_eff)
              {
                if (!v95)
                {
                  v94 = wk;
                }
                effList = v94->effList;
                v104 = v94;
                v418.x = v87;
                v418.y = v89;
                v418.z = v91;
                v418.w = v93;
                Eff = sBtlCreateEff(effList, v13, swordEffIdTbl[3 * v104->sword_eff_kind - 1 + v104->sword_eff_step], 0, v418, 0x80808080, 0, 1.0, 0);
                p_sword_eff = &v94->sword_eff;
                v94->sword_eff = Eff;
                goto LABEL_270;
              }
              if (!v95)
              {
                v94 = wk;
              }
              Nakama2 = sBtlGetNakama2(v94->sword_eff_nakama);
              if (!Nakama2 || !Nakama2->enchantcnt)
              {
                Eff = 0;
                v99 = wk;
                sword_eff = v99->sword_eff;
                p_sword_eff = &v99->sword_eff;
                v99->sword_eff_step = 0;
                sword_eff->st = 5;
                v99->sword_eff = 0;
LABEL_270:
              }
            }
            sBtlPlayer_CommPad();
            IsBattleKey = sBtlIsBattleKey(4181, 1);
            if (IsBattleKey)
            {
              wk->bSetsuma = 1;
LABEL_277:
              v114 = wk;
              if (v114->bAssistAttackBtn)
                goto LABEL_627;
              goto LABEL_281;
            }
            {
              goto LABEL_277;
            }
            v114 = wk;
            if (v114->bAssistAttackBtn)
              goto LABEL_627;
LABEL_281:
            v114 = wk;
            v115 = v114->mode;
            if (v115 <= 0x21 && ((1 << v115) & 0x3EFE8C008LL) != 0)
            {
              v114 = wk;
              if (!v114->cmbSkl->bRun)
              {
                v114 = wk;
                if (!v114->sklProc->bRun)
                {
                  v116 = IsSceanStop();
                  if (!v116)
                  {
                    v117 = wk;
                    if (!v117->kaiwaflg)
                    {
                      v117 = wk;
                      ComboLRU_StartOk = v117->ComboLRU_StartOk;
                      if (ComboLRU_StartOk)
                      {
                        if (!v119)
                        v120 = sBtlIsBattleKey(4121, 1);
                        if (v120)
                        {
                          if (v121)
                          {
                            v122 = wk;
                            ComboLRU_Cnt = v122->ComboLRU_Cnt;
                            if (ComboLRU_Cnt > 14)
                              goto LABEL_305;
                          }
                          else
                          {
                            v122 = wk;
                            ComboLRU_Cnt = v122->ComboLRU_Cnt;
                            if (ComboLRU_Cnt > 14)
                            {
LABEL_305:
                              goto LABEL_306;
                            }
                          }
                          v122 = wk;
                          ComboLRU_Cnt = v122->ComboLRU_Cnt;
                          v122->ComboLRU_Cnt = ComboLRU_Cnt + 1;
LABEL_306:
                          v124 = wk;
                          v125 = v124->ComboLRU_Cnt;
                          if (v125 < 1)
                            goto LABEL_431;
                          goto LABEL_425;
                          if (v125 < 1)
                          {
LABEL_431:
                            v157 = wk;
                            if (v157->ComboLRU_Cnt >= 15)
                            {
                              v157 = wk;
                              v157->bComboLRU = 1;
                            }
                            goto LABEL_355;
                          }
LABEL_425:
                          v124 = wk;
                          v125 = v124->ComboLRU_Cnt;
                          if (v125 <= 14)
                          {
                            v124 = wk;
                            v124->bComboSRU_NowChk = 1;
                          }
                          goto LABEL_431;
                        }
                        v154 = wk;
                        v155 = v154->ComboLRU_Cnt;
                        if (v155 >= 1)
                        {
                          v154 = wk;
                          v155 = v154->ComboLRU_Cnt;
                          if (v155 <= 14)
                          {
                            v154 = wk;
                            *(u16 *)&v154->bComboSRU = 257;
                          }
                        }
                        v156 = wk;
                        v156->ComboLRU_Cnt = 0;
                        v156->bComboLRU = 0;
                      }
                      else
                      {
                        if (!v119)
                        v153 = sBtlIsBattleKey(4121, 1);
                        if (!v153)
                        {
                          wk->ComboLRU_StartOk = 1;
                        }
                      }
                    }
                  }
                }
              }
            }
            else
            {
              v114 = wk;
              v114->ComboLRU_StartOk = 0;
              v114->ComboLRU_Cnt = 0;
            }
LABEL_355:
            v139 = wk;
            if (v139->cmbSkl->bRun)
              goto LABEL_627;
            v139 = wk;
            if (v139->sklProc->bRun)
              goto LABEL_627;
            if (IsSceanStop())
              goto LABEL_627;
            v142 = wk;
            if (v142->kaiwaflg)
              goto LABEL_627;
            v142 = wk;
            if (v142->mode != 1)
              goto LABEL_627;
            if (!sBtlCheckTame(v13))
              goto LABEL_627;
            if (sBtlDat()->m_type == 1)
            {
              v145 = sBtlIsBattleKey(4121, 1);
              if (v145)
              {
                if (v147)
                {
                  if (wk->chargeSdCnt)
                    goto LABEL_379;
                }
                else
                {
                  if (wk->chargeSdCnt)
                  {
LABEL_379:
                    goto LABEL_380;
                  }
                }
                sBtlResetDamage_TameStart(v13);
LABEL_380:
                if (wk->chargeSdCnt == 10)
                {
                  Add(0, 0);
                  goto LABEL_468;
                }
                v148 = wk;
                chargeSdCnt = v148->chargeSdCnt;
                if (chargeSdCnt <= 29)
                  goto LABEL_469;
                goto LABEL_475;
LABEL_468:
                v148 = wk;
                chargeSdCnt = v148->chargeSdCnt;
                if (chargeSdCnt <= 29)
                {
LABEL_469:
                  v148 = wk;
                  chargeSdCnt = v148->chargeSdCnt;
                  v162 = chargeSdCnt + 1;
                  v148->chargeSdCnt = v162;
                  if (v162 == 30)
                  {
                    AW_TameAdd();
                    v163 = v13->pos.x;
                    v164 = v13->pos.y;
                    v166 = v13->pos.z;
                    v165 = v13->pos.w;
                    v419.x = v163;
                    v419.y = v164;
                    v419.z = v166;
                    v419.w = v165;
                    sBtlPlay3DSE(0x10074u, v419);
                  }
                }
LABEL_475:
                v167 = wk;
                if (v167->chargeSdCnt >= 30)
                {
                  v167 = wk;
                  chargeSdCnt2 = v167->chargeSdCnt2;
                  if (chargeSdCnt2 < 1.0)
                  {
                    v167 = wk;
                    chargeSdCnt2 = v167->chargeSdCnt2;
                    v169 = chargeSdCnt2 + 0.1;
                    v167->chargeSdCnt2 = v169;
                    if (v169 > 1.0)
                    {
                      v167 = wk;
                      v167->chargeSdCnt2 = 1.0;
                    }
                  }
                }
                v170 = v13->hModel;
                if (v170)
                {
                  v171 = wk->chargeSdCnt2;
                  mdlSetMotionBlendTree1D(v170, v171);
                }
                goto LABEL_493;
              }
              v159 = wk;
              v160 = v159->chargeSdCnt;
              if (v160 >= 30)
              {
                if (!v158)
                {
                  v159 = wk;
                }
                v159->bChgSd = 1;
              }
              else
              {
                if (!v158)
                {
                  v159 = wk;
                  v160 = v159->chargeSdCnt;
                }
                if (v160 >= 1)
                {
                  v159 = wk;
                  v159->bChgSd0 = 1;
                }
              }
              v161 = wk;
              if (v161->chargeSdCnt)
              {
                v161 = wk;
                v161->bRU = 1;
              }
              if (wk->chargeSdCnt)
              {
                Del(0, 0);
                AW_TameDel(0);
              }
              *(u64 *)&wk->chargeSdCnt = 0;
            }
LABEL_493:
            if (sBtlDat()->m_type != 2)
            {
LABEL_560:
              if (sBtlDat()->m_type != 3)
                goto LABEL_627;
              v194 = sBtlIsBattleKey(4121, 1);
              if (v194)
              {
                if (v196)
                {
                  if (wk->chargeAxCnt)
                    goto LABEL_566;
                }
                else
                {
                  if (wk->chargeAxCnt)
                  {
LABEL_566:
                    goto LABEL_567;
                  }
                }
                sBtlResetDamage_TameStart(v13);
LABEL_567:
                if (wk->chargeAxCnt == 10)
                {
                  Add(2, 0);
                  goto LABEL_602;
                }
                v197 = wk;
                chargeAxCnt = v197->chargeAxCnt;
                if (chargeAxCnt <= 29)
                  goto LABEL_603;
                goto LABEL_609;
LABEL_602:
                v197 = wk;
                chargeAxCnt = v197->chargeAxCnt;
                if (chargeAxCnt <= 29)
                {
LABEL_603:
                  v197 = wk;
                  chargeAxCnt = v197->chargeAxCnt;
                  v203 = chargeAxCnt + 1;
                  v197->chargeAxCnt = v203;
                  if (v203 == 30)
                  {
                    AW_TameAdd();
                    v204 = v13->pos.x;
                    v205 = v13->pos.y;
                    v207 = v13->pos.z;
                    v206 = v13->pos.w;
                    v421.x = v204;
                    v421.y = v205;
                    v421.z = v207;
                    v421.w = v206;
                    sBtlPlay3DSE(0x10074u, v421);
                  }
                }
LABEL_609:
                v208 = wk;
                if (v208->chargeAxCnt >= 30)
                {
                  v208 = wk;
                  chargeAxCnt2 = v208->chargeAxCnt2;
                  if (chargeAxCnt2 < 1.0)
                  {
                    v208 = wk;
                    chargeAxCnt2 = v208->chargeAxCnt2;
                    v210 = chargeAxCnt2 + 0.1;
                    v208->chargeAxCnt2 = v210;
                    if (v210 > 1.0)
                    {
                      v208 = wk;
                      v208->chargeAxCnt2 = 1.0;
                    }
                  }
                }
                v211 = v13->hModel;
                if (v211)
                {
                  v212 = wk->chargeAxCnt2;
                  mdlSetMotionBlendTree1D(v211, v212);
                }
                goto LABEL_627;
              }
              v200 = wk;
              v201 = v200->chargeAxCnt;
              if (v201 >= 30)
              {
                if (!v199)
                {
                  v200 = wk;
                }
                v200->bChgAx = 1;
              }
              else
              {
                if (!v199)
                {
                  v200 = wk;
                  v201 = v200->chargeAxCnt;
                }
                if (v201 >= 1)
                {
                  v200 = wk;
                  v200->bChgAx0 = 1;
                }
              }
              v202 = wk;
              if (v202->chargeAxCnt)
              {
                v202 = wk;
                v202->bRU = 1;
              }
              if (wk->chargeAxCnt)
              {
                Del(0, 0);
                AW_TameDel(0);
              }
              *(u64 *)&wk->chargeAxCnt = 0;
LABEL_627:
              v214 = wk;
              if (v214->chargeSdCnt)
                goto LABEL_636;
              v214 = wk;
              if (v214->chargeLcCnt)
                goto LABEL_636;
              v214 = wk;
              if (v214->chargeAxCnt)
              {
LABEL_636:
                v216 = wk;
                if (v216->cmbSkl->bRun)
                  goto LABEL_762;
                v216 = wk;
                if (v216->sklProc->bRun)
                  goto LABEL_762;
                if (IsSceanStop())
                  goto LABEL_762;
                v218 = wk;
                if (v218->kaiwaflg)
                  goto LABEL_762;
                v218 = wk;
                if (v218->mode != 1 || (v13->vstatus & 0x8000) == 0)
                {
LABEL_762:
                  v13->hstatus &= ~0x800000u;
                  if (sBtlDat()->m_type == 1)
                  {
                    if (wk->chargeSdCnt)
                      hstatus = v13->hstatus | 0x800000;
                    else
                      hstatus = v13->hstatus;
                  }
                  else
                  {
                    hstatus = v13->hstatus;
                  }
                  v13->hstatus = hstatus & 0xFEFFFFFF;
                  if (sBtlDat()->m_type == 2)
                  {
                    if (wk->chargeLcCnt)
                      v248 = v13->hstatus | 0x1000000;
                    else
                      v248 = v13->hstatus;
                  }
                  else
                  {
                    v248 = v13->hstatus;
                  }
                  v13->hstatus = v248 & 0xFDFFFFFF;
                  if (sBtlDat()->m_type == 3)
                  {
                    if (wk->chargeAxCnt)
                      v13->hstatus |= 0x2000000u;
                  }
                  if (BadStatus != 10)
                  {
                    if (!IsSWAZA_AdvanceCheck())
                    {
                      if (sBtlIsBattleKey(4177, 2))
                      {
                        if (sBtlIsRaidouWazaCoolTime(0))
                          goto LABEL_794;
                      }
                      if (wk->bRaiSkill_RU_Pause)
                      {
LABEL_794:
                        if (GBWK->player->raidouSkill[0])
                        {
                          wk->bRaiSkill_RU = 1;
                        }
                        wk->bRaiSkill_RU_Pause = 0;
                      }
                      else
                      {
                        if (sBtlIsBattleKey(4178, 2))
                        {
                          if (sBtlIsRaidouWazaCoolTime(1))
                            goto LABEL_812;
                        }
                        if (wk->bRaiSkill_RL_Pause)
                        {
LABEL_812:
                          if (GBWK->player->raidouSkill[1])
                          {
                            wk->bRaiSkill_RL = 1;
                          }
                          wk->bRaiSkill_RL_Pause = 0;
                        }
                        else
                        {
                          if (sBtlIsBattleKey(4179, 2))
                          {
                            if (sBtlIsRaidouWazaCoolTime(2))
                              goto LABEL_830;
                          }
                          if (wk->bRaiSkill_RD_Pause)
                          {
LABEL_830:
                            if (GBWK->player->raidouSkill[2])
                            {
                              wk->bRaiSkill_RD = 1;
                            }
                            wk->bRaiSkill_RD_Pause = 0;
                          }
                        }
                      }
                    }
                    if (sBtlIsBattleKey(4180, 2))
                    {
                      if (sBtlIsSpiritWazaAndEnemyLive())
                      {
                        if (CheckAction_Nakama(v13, 0))
                        {
                          wk->bSpiritSkill = 1;
                          v273 = CheckAction_Nakama(v13, 1);
                          if (v273)
                          {
                            v276 = wk;
                            v276->SpiritSkillNakamaIdx = sub_1905740(2, 0);
                          }
                          else
                          {
                            wk->SpiritSkillNakamaIdx = 0;
                          }
                          v281 = wk;
                        }
                        else
                        {
                          v277 = CheckAction_Nakama(v13, 1);
                          if (v277)
                          {
                            v280 = 1;
                            v281 = wk;
                            v281->bSpiritSkill = 1;
                          }
                          else
                          {
                            v281 = wk;
                            v281->bSpiritSkill = 1;
                            v280 = -1;
                          }
                          v281->SpiritSkillNakamaIdx = v280;
                        }
                        *(u16 *)&v281->bJump = 0;
                      }
                    }
                  }
                  CalcSetsuma(v13);
                  if (wk->cmbSkl->bRun)
                    goto LABEL_885;
LABEL_879:
                  if (!sBtlCheckSetsuma())
                  {
                    sBtlHuumaRangeCircleProc(v13);
                  }
LABEL_885:
                  v287 = wk;
                  if (v287->mode == 12)
                  {
                    goto LABEL_888;
                  }
                  v287 = wk;
                  HuumaGageOff(v287->bsc, 0, 0);
LABEL_888:
                  v288 = wk->mode - 1;
                  if (v288 > 0x20)
                  {
LABEL_942:
                    v289 = 0;
                    goto LABEL_1021;
                  }
                  v289 = 2;
                  switch (v288)
                  {
                    case 0u:
                      if (sBtlSummonKey(v13))
                        goto LABEL_942;
                      Check_SupportAction(v13);
                      if (wk->mode != 1)
                        goto LABEL_1021;
                      v300 = NormalProc(v13);
LABEL_1020:
                      v289 = v300;
LABEL_1021:
                      if (!sBtlCheckMove(v13) && v289 != 3 && v13->actwk->status != 9)
                      {
                        goto LABEL_1090;
                      }
                      if (v289 != 2)
                      {
                        if (v289 != 1)
                        {
                          if (v289)
                            goto LABEL_1090;
                          v13->m_BlendTree1D = 0.0;
                          *(u64 *)&v13->m_BlendTree2DX = 0;
                          if (wk->battlemode == 1)
                          {
                            v316 = v13->next_motionID;
                            if (!sBtlCheckLoopMotion(v13, v316))
                              goto LABEL_1038;
LABEL_1035:
                            v318 = 0;
LABEL_1037:
                            sBtlSetMotion(v13, v318, 0, 0, 0);
LABEL_1038:
                            wk->walk_counter = 0;
                            goto LABEL_1090;
                          }
                          if ((v13->vstatus & 0x8000) != 0)
                          {
                            v345 = v13->motionno;
                            if ((u32)(v345 - 79) >= 4)
                            {
                              if (v345 == 76)
                                goto LABEL_1038;
                              if (v345 != 77)
                              {
                                v318 = 77;
                                goto LABEL_1037;
                              }
                              if (!sBtlCheckMotionEnd(v13))
                                goto LABEL_1038;
                            }
                            v318 = 76;
                            goto LABEL_1037;
                          }
                          v326 = v13->hstatus;
                          if ((v326 & 0x800000) != 0 || (v326 & 0x1000000) != 0)
                          {
                            v327 = v13->motionno;
                          }
                          else
                          {
                            v327 = v13->motionno;
                            if ((v326 & 0x2000000) == 0)
                            {
                              if (v327 > 131)
                              {
                                if (v327 == 132)
                                {
                                  v318 = 136;
                                  goto LABEL_1037;
                                }
                                if (v327 == 136)
                                {
                                  v352 = v13->hModel;
                                  if (mdlGetMotionFrameF(v352) < 41.0)
                                    goto LABEL_1038;
                                  goto LABEL_1035;
                                }
                              }
                              else
                              {
                                if ((u32)(v327 - 55) < 2)
                                {
                                  v318 = 57;
                                  goto LABEL_1037;
                                }
                                if (v327 == 57)
                                {
                                  v357 = v13->hModel;
                                  MotionFrameF = mdlGetMotionFrameF(v357);
                                  v359 = 29.5;
LABEL_1185:
                                  if (MotionFrameF < v359)
                                  {
                                    if (!sBtlCheckMotionEnd(v13))
                                      goto LABEL_1038;
                                  }
                                  goto LABEL_1035;
                                }
                              }
                              if (BadStatus == 9 || BadStatus == 22)
                                goto LABEL_1199;
                              v385 = v13->para;
                              if (sBtlIsKoufun(v385) || BadStatus == 16)
                              {
LABEL_1199:
                                now = v13->para->now;
                                hp = now->hp;
                                maxhp = now->maxhp;
                                v364 = v13->motionno;
                                if ((f32)((f32)hp / (f32)maxhp) >= 0.26)
                                {
                                  if (v364 > 43)
                                  {
                                    switch (v364)
                                    {
                                      case 128:
                                        goto LABEL_1270;
                                      case 129:
                                        v406 = v13->hModel;
                                        MotionFrameF = mdlGetMotionFrameF(v406);
                                        v359 = 20.0;
                                        goto LABEL_1185;
                                      case 130:
                                      case 131:
                                      case 132:
                                      case 133:
                                      case 134:
                                      case 135:
                                      case 136:
                                      case 137:
                                      case 138:
                                        goto LABEL_1343;
                                      case 139:
                                        v318 = 140;
                                        goto LABEL_1037;
                                      case 140:
                                        v407 = v13->hModel;
                                        MotionFrameF = mdlGetMotionFrameF(v407);
                                        v359 = 13.0;
                                        goto LABEL_1185;
                                      default:
                                        if (v364 != 44)
                                          goto LABEL_1343;
                                        v318 = 118;
                                        goto LABEL_1037;
                                    }
                                  }
                                  switch (v364)
                                  {
                                    case 2:
LABEL_1270:
                                      v318 = 129;
                                      goto LABEL_1037;
                                    case 11:
                                      v318 = 112;
                                      goto LABEL_1037;
                                    case 43:
                                      v318 = 115;
                                      goto LABEL_1037;
                                    default:
LABEL_1343:
                                      if ((u32)(v364 - 178) > 0xFFFFFFF5 || (u32)(v364 - 184) > 0xFFFFFFFA)
                                      {
                                        goto LABEL_1038;
                                      }
                                      v405 = v13->next_motionID;
                                      if (!sBtlCheckLoopMotion(v13, v405))
                                        goto LABEL_1038;
                                      if (v13->motionno == 130)
                                        v318 = 130;
                                      else
                                        v318 = 0;
                                      goto LABEL_1037;
                                  }
                                  goto LABEL_1036;
                                }
                                if (v364 == 2)
                                  goto LABEL_1329;
                              }
                              else
                              {
                                if ((BadStatus | 2) == 0xA)
                                {
                                  v386 = v13->motionno;
                                  if (v386 > 137)
                                  {
                                    if (v386 == 138)
                                    {
                                      v409 = v13->hModel;
                                      if (mdlGetMotionFrameF(v409) < 15.0)
                                      {
                                        if (!sBtlCheckMotionEnd(v13))
                                          goto LABEL_1038;
                                      }
                                    }
                                    else
                                    {
                                      if (v386 != 139)
                                        goto LABEL_1372;
                                      v404 = v13->next_motionID;
                                      if (!sBtlCheckLoopMotion(v13, v404))
                                        goto LABEL_1038;
                                    }
                                    v318 = 139;
                                    goto LABEL_1037;
                                  }
                                  if (v386 == 2)
                                    goto LABEL_1038;
                                  if (v386 != 128)
                                  {
LABEL_1372:
                                    v410 = v13->next_motionID;
                                    if (!sBtlCheckLoopMotion(v13, v410))
                                      goto LABEL_1038;
                                    v318 = 138;
                                    goto LABEL_1037;
                                  }
                                  goto LABEL_1202;
                                }
                                v364 = v13->motionno;
                                if (v364 == 2)
                                {
LABEL_1329:
                                  v403 = v13->next_motionID;
                                  if (!sBtlCheckLoopMotion(v13, v403))
                                    goto LABEL_1038;
                                  goto LABEL_1332;
                                }
                              }
                              if (v364 != 128)
                              {
                                v393 = v13->next_motionID;
                                if (!sBtlCheckLoopMotion(v13, v393))
                                  goto LABEL_1038;
                                v318 = 128;
                                goto LABEL_1037;
                              }
LABEL_1202:
                              v365 = v13->hModel;
                              if (mdlGetMotionFrameF(v365) < 15.0)
                              {
                                if (!sBtlCheckMotionEnd(v13))
                                  goto LABEL_1038;
                              }
LABEL_1332:
                              v318 = 2;
                              goto LABEL_1037;
                            }
                          }
                          switch (v327)
                          {
                            case '8':
                              v346 = v13->hModel;
                              if (mdlGetMotionFrameF(v346) < 7.5)
                              {
                                if (!sBtlCheckMotionEnd(v13))
                                  goto LABEL_1038;
                              }
                              break;
                            case '7':
                              goto LABEL_1038;
                            case '6':
                              break;
                            default:
                              v318 = 56;
                              goto LABEL_1037;
                          }
                          v318 = 55;
                          goto LABEL_1037;
LABEL_1036:
                          goto LABEL_1037;
                        }
                        v323 = wk;
                        if (v323->battlemode == 1)
                        {
                          v13->cmstatus = 0;
                          v325 = 5;
LABEL_1055:
                          sBtlSetMotion(v13, v325, 0, 0, 0);
                          goto LABEL_1090;
                        }
                        v328 = v13->hstatus;
                        if ((v328 & 0x800000) == 0 && (v328 & 0x1000000) == 0 && (v328 & 0x2000000) == 0)
                        {
                          if ((v13->vstatus & 0x8000) == 0)
                          {
                            v323 = wk;
                            if (!v323->CameraLockOn || (v13->hstatus & 0x100000) == 0)
                            {
                              v329 = v13->motionno;
                              if ((u32)(v329 - 103) > 0x1F)
                                goto LABEL_1224;
                              if (((1 << (v329 - 103)) & 0xC000000D) != 0)
                              {
                                cmstatus = v13->cmstatus;
                                if ((cmstatus & 2) != 0)
                                {
                                  v13->cmstatus = cmstatus & 0xFFFFFFFD;
LABEL_1192:
                                  v325 = 108;
                                  goto LABEL_1055;
                                }
                                if ((cmstatus & 0x20) != 0)
                                {
                                  m_BlendTree1D = v13->m_BlendTree1D;
                                  v13->cmstatus = cmstatus & 0xFFFFFFDF;
                                  v13->m_BlendTree1DFlg = 1;
                                  v373 = m_BlendTree1D + 0.1;
                                  if (v373 > 1.0)
                                    v373 = 1.0;
                                  v13->m_BlendTree1D = v373;
                                  if (v329 != 105)
                                    goto LABEL_1320;
                                  goto LABEL_1246;
                                }
                                if ((cmstatus & 0x40) != 0)
                                {
                                  v383 = v13->m_BlendTree1D;
                                  v13->cmstatus = cmstatus & 0xFFFFFFBF;
                                  v13->m_BlendTree1DFlg = 1;
                                  v384 = v383 + -0.1;
                                  if (v384 < -1.0)
                                    v384 = -1.0;
                                  v13->m_BlendTree1D = v384;
                                  if (v329 != 106)
                                    goto LABEL_1320;
                                  goto LABEL_1246;
                                }
                                if ((cmstatus & 0x80) == 0)
                                {
                                  if ((cmstatus & 0x100) == 0)
                                  {
                                    if ((cmstatus & 0x200) != 0)
                                    {
                                      v331 = v13->m_BlendTree1D;
                                      v13->cmstatus = cmstatus & 0xFFFFFDFF;
                                      v13->m_BlendTree1DFlg = 1;
                                      v332 = v331 + -0.1;
                                      if (v332 < -1.0)
                                        v332 = -1.0;
                                      v13->m_BlendTree1D = v332;
                                      if (v329 != 134)
                                        goto LABEL_1320;
                                      goto LABEL_1246;
                                    }
                                    goto LABEL_1258;
                                  }
                                  v399 = v13->m_BlendTree1D;
                                  v13->cmstatus = cmstatus & 0xFFFFFEFF;
                                  v13->m_BlendTree1DFlg = 1;
                                  v400 = v399 + 0.1;
                                  if (v400 > 1.0)
                                    v400 = 1.0;
                                  v13->m_BlendTree1D = v400;
                                  if (v329 != 133)
                                    goto LABEL_1320;
LABEL_1246:
                                  v13->m_BlendTree2DFlg = 1;
                                  *(u64 *)&v13->m_BlendTree2DX = 0;
                                  goto LABEL_1320;
                                }
                                v391 = v13->m_BlendTree1D;
                                v13->cmstatus = cmstatus & 0xFFFFFF7F;
                                if (v391 >= -0.05)
                                {
                                  v401 = 0.0;
                                  if (v391 <= 0.05)
                                  {
LABEL_1318:
                                    v13->m_BlendTree1D = v401;
                                    goto LABEL_1319;
                                  }
                                  v392 = -0.05;
                                }
                                else
                                {
                                  v392 = 0.05;
                                }
                                v401 = v391 + v392;
                                goto LABEL_1318;
                              }
                              if (v329 != 122)
                              {
LABEL_1224:
                                v374 = v13->hModel;
                                v375 = mdlGetMotionFrameF(v374);
                                switch (v13->motionID)
                                {
                                  case 'k':
                                  case 'm':
                                    v376 = v13->cmstatus;
                                    if ((v376 & 8) != 0)
                                      goto LABEL_1286;
                                    v377 = 6.0;
                                    goto LABEL_1285;
                                  case 'l':
                                    v376 = v13->cmstatus;
                                    if ((v376 & 8) != 0)
                                      goto LABEL_1286;
                                    v377 = 8.0;
LABEL_1285:
                                    if (v375 >= v377)
                                      goto LABEL_1286;
                                    goto LABEL_1090;
                                  case 'n':
                                    goto LABEL_1090;
                                  default:
                                    v376 = v13->cmstatus;
                                    if (v13->motionno == 135 && v375 < 9.0 && (v376 & 2) == 0)
                                      goto LABEL_1090;
LABEL_1286:
                                    if ((v376 & 2) != 0)
                                    {
                                      v13->cmstatus = v376 & 0xFFFFFFFD;
                                      goto LABEL_1192;
                                    }
                                    if ((v376 & 1) != 0)
                                    {
                                      v13->cmstatus = v376 & 0xFFFFFFFE;
                                      v325 = 107;
                                    }
                                    else if ((v376 & 4) != 0)
                                    {
                                      v13->cmstatus = v376 & 0xFFFFFFFB;
                                      v325 = 109;
                                    }
                                    else if ((v376 & 8) != 0)
                                    {
                                      v13->cmstatus = v376 & 0xFFFFFFF7;
                                      v325 = 110;
                                    }
                                    else
                                    {
                                      if ((v376 & 0x80) != 0)
                                      {
                                        v371 = v376 & 0xFFFFFF7F;
                                        goto LABEL_1257;
                                      }
                                      if ((v376 & 0x400) != 0)
                                      {
                                        v13->cmstatus = v376 & 0xFFFFFBFF;
                                        v325 = 135;
                                      }
                                      else if ((v376 & 0x100) != 0)
                                      {
                                        v13->m_BlendTree1D = 0.0;
                                        v13->cmstatus = v376 & 0xFFFFFEFF;
                                        v13->m_BlendTree1DFlg = 1;
                                        v325 = 133;
                                      }
                                      else
                                      {
                                        if ((v376 & 0x200) == 0)
                                          goto LABEL_1258;
                                        v13->m_BlendTree1D = 0.0;
                                        v13->cmstatus = v376 & 0xFFFFFDFF;
                                        v13->m_BlendTree1DFlg = 1;
                                        v325 = 134;
                                      }
                                    }
                                    break;
                                }
                                goto LABEL_1055;
                              }
                              v370 = v13->cmstatus;
                              if ((v370 & 0x100) != 0)
                              {
                                v371 = v370 & 0xFFFFFEFF;
                              }
                              else
                              {
                                if ((v370 & 0x200) == 0)
                                {
LABEL_1258:
                                  v13->m_BlendTree1D = 0.0;
LABEL_1319:
                                  v13->m_BlendTree1DFlg = 1;
                                  goto LABEL_1320;
                                }
                                v371 = v370 & 0xFFFFFDFF;
                              }
LABEL_1257:
                              v13->cmstatus = v371;
                              goto LABEL_1258;
                            }
                            v353 = v13->cmstatus;
                            if ((v353 & 0x100000) == 0)
                            {
                              if ((v353 & 0x200000) == 0)
                              {
                                v354 = -1.0;
                                v13->cmstatus = 0;
                                if ((v353 & 0x800000) == 0)
                                {
                                  m_BlendTree2DX = v13->m_BlendTree2DX;
                                  if ((f32)(v13->m_BlendTree2DY + -0.1) >= -1.0)
                                    v354 = v13->m_BlendTree2DY + -0.1;
                                  v13->m_BlendTree2DY = v354;
                                  if (m_BlendTree2DX >= -0.2)
                                  {
                                    v395 = 0.0;
                                    if (m_BlendTree2DX <= 0.2)
                                    {
LABEL_1302:
                                      v13->m_BlendTree2DX = v395;
                                      v13->m_BlendTree2DFlg = 1;
                                      v325 = 122;
                                      goto LABEL_1055;
                                    }
                                    v356 = -0.2;
                                  }
                                  else
                                  {
                                    v356 = 0.2;
                                  }
                                  v395 = m_BlendTree2DX + v356;
                                  goto LABEL_1302;
                                }
                                m_BlendTree2DY = v13->m_BlendTree2DY;
                                if ((f32)(v13->m_BlendTree2DX + -0.1) >= -1.0)
                                  v354 = v13->m_BlendTree2DX + -0.1;
                                v13->m_BlendTree2DX = v354;
                                if (m_BlendTree2DY >= -0.2)
                                {
                                  v397 = 0.0;
                                  if (m_BlendTree2DY <= 0.2)
                                  {
LABEL_1308:
                                    v13->m_BlendTree2DY = v397;
                                    v13->m_BlendTree2DFlg = 1;
                                    v325 = 123;
                                    goto LABEL_1055;
                                  }
                                  v388 = -0.2;
                                }
                                else
                                {
                                  v388 = 0.2;
                                }
                                v397 = m_BlendTree2DY + v388;
                                goto LABEL_1308;
                              }
                              v378 = v13->m_BlendTree2DX;
                              v13->cmstatus = 0;
                              v379 = v378 + 0.1;
                              v380 = v13->m_BlendTree2DY;
                              if (v379 > 1.0)
                                v379 = 1.0;
                              v13->m_BlendTree2DX = v379;
                              if (v380 >= -0.2)
                              {
                                v389 = 0.0;
                                if (v380 <= 0.2)
                                {
LABEL_1266:
                                  v13->m_BlendTree2DY = v389;
                                  v13->m_BlendTree2DFlg = 1;
                                  v325 = 121;
                                  goto LABEL_1055;
                                }
                                v381 = -0.2;
                              }
                              else
                              {
                                v381 = 0.2;
                              }
                              v389 = v380 + v381;
                              goto LABEL_1266;
                            }
                            v366 = v13->m_BlendTree2DY;
                            v13->cmstatus = 0;
                            v367 = v366 + 0.1;
                            v368 = v13->m_BlendTree2DX;
                            if (v367 > 1.0)
                              v367 = 1.0;
                            v13->m_BlendTree2DY = v367;
                            if (v368 >= -0.2)
                            {
                              v382 = 0.0;
                              if (v368 <= 0.2)
                              {
LABEL_1236:
                                v13->m_BlendTree2DX = v382;
                                v13->m_BlendTree2DFlg = 1;
LABEL_1320:
                                v325 = 103;
                                goto LABEL_1055;
                              }
                              v369 = -0.2;
                            }
                            else
                            {
                              v369 = 0.2;
                            }
                            v382 = v368 + v369;
                            goto LABEL_1236;
                          }
                          v348 = v13->motionno;
                          if ((u32)(v348 - 78) < 5 || v348 == 76)
                          {
                            v349 = v13->cmstatus;
                            if ((v349 & 0x10000) == 0)
                            {
                              if ((v349 & 0x20000) != 0)
                              {
                                v351 = 80;
                                goto LABEL_1172;
                              }
                              else
                              {
                                if ((v349 & 0x80000) != 0)
                                  v351 = 82;
                                else
                                  v351 = 81;
                                goto LABEL_1172;
                              }
                              goto LABEL_1171;
                            }
                            v351 = 79;
LABEL_1171:
                          }
                          else
                          {
                            if (v348 != 77)
                            {
                              v325 = 77;
                              goto LABEL_1055;
                            }
                            if (!sBtlCheckMotionEnd(v13))
                            {
LABEL_1173:
                              v13->cmstatus = 0;
                              goto LABEL_1090;
                            }
                            v351 = 76;
                          }
LABEL_1172:
                          sBtlSetMotion(v13, v351, 0, 0, 0);
                          goto LABEL_1173;
                        }
                        if (v13->next_motionno != 54)
                        {
                          sBtlSetMotion(v13, 54, 0, 0, 0);
                          wk->sword_skillcnt = 0;
                        }
LABEL_1090:
                        PlayerAllSync(v13);
                        v415 = 0u;
                        AnlogKey = GetAnlogKey(v13, &v415);
                        v337 = AnlogKey;
                        p_anlog_cnt = &wk->anlog_cnt;
                        ++*p_anlog_cnt;
                        LimitRange_2(p_anlog_cnt, 0, 120);
                        v343 = wk;
                        anlog_cnt = v343->anlog_cnt;
                        if (anlog_cnt <= 19 && v337 > 40.0)
                          goto LABEL_1113;
                        if (v337 <= 40.0)
                          goto LABEL_1390;
                        v343 = wk;
                        LOWORD(anlog_cnt) = v343->anlog_cnt;
                        if ((s16)anlog_cnt >= 20)
                        {
                          v343 = wk;
                        }
                        else
                        {
LABEL_1390:
                          v343 = wk;
                          if (v343->anlog_cnt < 20)
                            goto LABEL_1113;
                          v343 = wk;
                          v343->anlog_cnt = 0;
                        }
                        v343->anlog_old = GetAnlogKey(v13, &v415);
LABEL_1113:
                        LOBYTE(ActiveScene) = 1;
                        return (char)ActiveScene;
                      }
                      if (v13->motionno != 137)
                        goto LABEL_1090;
                      v320 = v13->hModel;
                      if (mdlGetMotionFrameF(v320) < 8.0)
                      {
                        if (wk->huuma_st_motion_cnt < 18)
                        {
LABEL_1048:
                          ++wk->huuma_st_motion_cnt;
                          goto LABEL_1090;
                        }
                      }
                      sBtlSetMotion(v13, 132, 0, 0, 0);
                      goto LABEL_1048;
                    case 1u:
                      SummonProc(v13);
                      goto LABEL_1021;
                    case 2u:
                      Check_SupportAction(v13);
                      if (sBtlSummonKey(v13))
                        goto LABEL_942;
                      v13->vstatus |= 0x20000u;
                      Sord1Proc_New(v13, (s32)v282);
                      goto LABEL_1021;
                    case 4u:
                      SBTLMAIN_MODE_STOP_Task(v13);
                      goto LABEL_1021;
                    case 5u:
                      UseItemProc(v13);
                      goto LABEL_1021;
                    case 8u:
                      if (IsSceanStop())
                        v289 = 0;
                      else
                        v289 = 2;
                      goto LABEL_1021;
                    case 0xAu:
                      Check_SupportAction(v13);
                      GuardProc(v13, v294);
                      goto LABEL_1021;
                    case 0xBu:
                      HuumaProc(v13);
                      goto LABEL_1021;
                    case 0xCu:
                      goto LABEL_1021;
                    case 0xDu:
                      Check_SupportAction(v13);
                      if (sBtlSummonKey(v13))
                        goto LABEL_942;
                      KaihiProc(v13);
                      goto LABEL_1021;
                    case 0xEu:
                      Check_SupportAction(v13);
                      if (sBtlSummonKey(v13))
                        goto LABEL_942;
                      MawariProc(v13);
                      goto LABEL_1021;
                    case 0x10u:
                      SetsumaProc(v13);
                      goto LABEL_1021;
                    case 0x12u:
                      Check_SupportAction(v13);
                      JumpProc(v13);
                      goto LABEL_1021;
                    case 0x14u:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRKaitenProc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x15u:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRSdShotProc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x16u:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRGunShotProc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x17u:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRMagicProc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x18u:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRJigenKiriProc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x19u:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRGroundProc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x1Au:
                      Check_SupportAction(v13);
                      v307 = wk->mode;
                      v300 = sBtlPlayerRSdDashProc(v13, v307);
                      goto LABEL_1020;
                    case 0x1Bu:
                      LOWORD(v308) = 28;
                      v300 = sBtlPlayerRSpiritProc(v13, v308);
                      goto LABEL_1020;
                    case 0x1Cu:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRMagic2Proc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x1Du:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRMagic3Proc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x1Eu:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRMagic4Proc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x1Fu:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRMagic5Proc(v13, wk->mode);
                      goto LABEL_1020;
                    case 0x20u:
                      Check_SupportAction(v13);
                      v300 = sBtlPlayerRMagic6Proc(v13, wk->mode);
                      goto LABEL_1020;
                    default:
                      goto LABEL_942;
                  }
                  if (wk->cmbSkl->bRun)
                    goto LABEL_885;
                  goto LABEL_879;
                }
                v218 = wk;
                ++v218->chargeGunCnt2;
                if (v13->motionno == 77)
                {
                  v219 = v13->hModel;
                  if (mdlGetMotionFrameF(v219) < 9.0)
                  {
                    wk->chargeGunCnt2 = 0;
                  }
                }
                SpiritSkillChk = sBtlGetSpiritSkillChk(1444);
                if (SpiritSkillChk)
                {
                  v226 = wk;
                  GunLockOnNum = v226->GunLockOnNum;
                  if (v226->GunRapidNum - GunLockOnNum <= 0)
                  {
                    v228 = 0;
                  }
                  else
                  {
                    v226 = wk;
                    GunLockOnNum = v226->GunLockOnNum;
                    if (GunLockOnNum > 5)
                      goto LABEL_750;
                    v226 = wk;
                    if (v226->chargeGunCnt2 % 3 == 1)
                    {
                      v228 = SetGunPlayerHit(v13);
                    }
                    else
                    {
                      v228 = 0;
                    }
                    v236 = wk;
                    v237 = v236->GunLockOnNum;
                    if (v236->GunRapidNum - v237 >= 1)
                    {
                      v236 = wk;
                      v237 = v236->GunLockOnNum;
                      if (v237 > 5)
                      {
LABEL_742:
                        if (!v228)
                          goto LABEL_750;
LABEL_747:
                        sBtlPlaySE(0x10061u);
                        goto LABEL_750;
                      }
                      v236 = wk;
                      if (v236->chargeGunCnt2 % 3 == 1)
                      {
                        v238 = !SetGunPlayerHit(v13);
                        if (!v238)
                          v228 = 1;
                      }
                      v239 = wk;
                      v240 = v239->GunLockOnNum;
                      if (v239->GunRapidNum - v240 >= 1)
                      {
                        v239 = wk;
                        v240 = v239->GunLockOnNum;
                        if (v240 <= 5)
                        {
                          v239 = wk;
                          if (v239->chargeGunCnt2 % 3 == 1)
                          {
                            if (SetGunPlayerHit(v13))
                              v228 = 1;
                          }
                        }
                        goto LABEL_742;
                      }
                    }
                  }
                  wk->chargeGunCnt2 = 0;
                  if (!v228)
                    goto LABEL_750;
                  goto LABEL_747;
                }
                v234 = wk;
                if (v234->GunRapidNum - v234->GunLockOnNum <= 0)
                {
                  v234 = wk;
                  v234->chargeGunCnt2 = 0;
LABEL_701:
                  v235 = wk;
                  if (v235->GunLockOnNum > 5)
                    goto LABEL_750;
                  goto LABEL_708;
                }
                {
                  goto LABEL_701;
                }
                v235 = wk;
                if (v235->GunLockOnNum > 5)
                {
LABEL_750:
                  if (wk->GunLockOnNum >= 1)
                  {
                    if (sBtlIsBattleKey(4122, 2))
                    {
                      if (!sBtlR1_IsNaked())
                      {
                        v244 = wk;
                        v244->bChgGun = 1;
                        *(u64 *)&v244->chargeGunCnt = 0;
                      }
                    }
                  }
                  goto LABEL_762;
                }
LABEL_708:
                v235 = wk;
                if (v235->chargeGunCnt2 % 6 != 1)
                  goto LABEL_750;
                if (!SetGunPlayerHit(v13))
                  goto LABEL_750;
                goto LABEL_747;
              }
              if ((v13->vstatus & 0x8000) != 0)
              {
                if (!v229)
                if (sBtlIsBattleKey(4123, 1))
                {
                  if (!R1_HuumaBtn())
                    goto LABEL_636;
                }
                if (v13->motionno == 77)
                  goto LABEL_636;
              }
              else
              {
                if (!v229)
                if (!sBtlIsBattleKey(4123, 1))
                  goto LABEL_636;
                if (R1_HuumaBtn())
                  goto LABEL_636;
                if (IsSWAZA_AdvanceCheck())
                  goto LABEL_636;
              }
              wk->bGunMode = 1;
              goto LABEL_636;
            }
            v174 = sBtlIsBattleKey(4121, 1);
            if (!v174)
            {
              v180 = wk;
              chargeLcCnt = v180->chargeLcCnt;
              if (chargeLcCnt >= 30)
              {
                if (!v179)
                {
                  v180 = wk;
                }
                v180->bChgLc = 1;
              }
              else
              {
                if (!v179)
                {
                  v180 = wk;
                  chargeLcCnt = v180->chargeLcCnt;
                }
                if (chargeLcCnt >= 1)
                {
                  v180 = wk;
                  v180->bChgLc0 = 1;
                }
              }
              v182 = wk;
              if (v182->chargeLcCnt)
              {
                v182 = wk;
                v182->bRU = 1;
              }
              if (wk->chargeLcCnt)
              {
                Del(0, 0);
                AW_TameDel(0);
              }
              *(u64 *)&wk->chargeLcCnt = 0;
              goto LABEL_560;
            }
            if (v176)
            {
              if (wk->chargeLcCnt)
                goto LABEL_499;
            }
            else
            {
              if (wk->chargeLcCnt)
              {
LABEL_499:
                goto LABEL_500;
              }
            }
            sBtlResetDamage_TameStart(v13);
LABEL_500:
            if (wk->chargeLcCnt == 10)
            {
              Add(1, 0);
              goto LABEL_535;
            }
            v177 = wk;
            v178 = v177->chargeLcCnt;
            if (v178 <= 29)
              goto LABEL_536;
            goto LABEL_542;
LABEL_535:
            v177 = wk;
            v178 = v177->chargeLcCnt;
            if (v178 <= 29)
            {
LABEL_536:
              v177 = wk;
              v178 = v177->chargeLcCnt;
              v183 = v178 + 1;
              v177->chargeLcCnt = v183;
              if (v183 == 30)
              {
                AW_TameAdd();
                v184 = v13->pos.x;
                v185 = v13->pos.y;
                v187 = v13->pos.z;
                v186 = v13->pos.w;
                v420.x = v184;
                v420.y = v185;
                v420.z = v187;
                v420.w = v186;
                sBtlPlay3DSE(0x10074u, v420);
              }
            }
LABEL_542:
            v188 = wk;
            if (v188->chargeLcCnt >= 30)
            {
              v188 = wk;
              chargeLcCnt2 = v188->chargeLcCnt2;
              if (chargeLcCnt2 < 1.0)
              {
                v188 = wk;
                chargeLcCnt2 = v188->chargeLcCnt2;
                v190 = chargeLcCnt2 + 0.1;
                v188->chargeLcCnt2 = v190;
                if (v190 > 1.0)
                {
                  v188 = wk;
                  v188->chargeLcCnt2 = 1.0;
                }
              }
            }
            v191 = v13->hModel;
            if (v191)
            {
              v192 = wk->chargeLcCnt2;
              mdlSetMotionBlendTree1D(v191, v192);
            }
            goto LABEL_560;
          }
          if (sBtlGetPChara())
          {
            v68 = wk;
            v69 = v68->magUpCnt + 1;
            v68->magUpCnt = v69;
            if (v69 == 60)
            {
              v68->magUpCnt = 0;
              if (!sBtlGetSpiritSkillChk(1446))
                goto LABEL_221;
              sBtlAddMag(1);
              goto LABEL_221;
            }
          }
LABEL_221:
          v74 = wk;
          v75 = v74->viceUpCntE + 66;
          v76 = v74->viceUpCntE - 34 < 0;
          v74->viceUpCntE = v75;
          if (v76 == __OFSUB__(v75, 100))
          {
            v74 = wk;
            spirit_enemy = v74->spirit_enemy;
            ViceLevel = sBtlGetViceLevel(spirit_enemy);
            sBtlViceAddEnemyHD(0, 1, 0, 4000);
            v79 = wk;
            v80 = v79->spirit_enemy;
            v79->viceUpCntE -= 100;
            v81 = sBtlGetViceLevel(v80);
            if (ViceLevel <= 4 && v81 == 5)
            {
              wk->vice1stKoufun = 180;
            }
          }
          v82 = wk;
          vice1stKoufun = v82->vice1stKoufun;
          if (vice1stKoufun)
          {
            v82 = wk;
            vice1stKoufun = v82->vice1stKoufun;
            v84 = vice1stKoufun - 1;
            v82->vice1stKoufun = v84;
            if (v84 <= 0)
            {
              v82 = wk;
              v82->vice1stKoufun = 0;
            }
          }
          goto LABEL_244;
        }
LABEL_173:
        LOBYTE(ActiveScene) = 0;
        return (char)ActiveScene;
      }
      v25 = v13->pos.x;
      *(f32 *)&v26 = 6041.0;
      if (v25 < 6041.0 || (*(f32 *)&v26 = 8259.0, v25 > 8259.0))
      {
        v25 = *(f32 *)&v26;
        v13->pos.x = *(f32 *)&v26;
      }
      v27 = v13->pos.z;
      if (v27 >= -1859.0)
      {
        if (v27 > -341.0)
        {
          v27 = -341.0;
          v13->pos.z = -341.0;
        }
        if (v25 > 6120.0 && v25 < 6700.0)
        {
          v28 = -1006157824;
          if (v27 > -541.0)
            goto LABEL_99;
        }
      }
      else
      {
        v27 = -1859.0;
        v13->pos.z = -1859.0;
      }
      if (v25 <= 7500.0)
        goto LABEL_100;
      if (v25 >= 8180.0)
        goto LABEL_100;
      v28 = -1006157824;
      if (v27 <= -541.0)
        goto LABEL_100;
LABEL_99:
      LODWORD(v13->pos.z) = v28;
      goto LABEL_100;
    }
LABEL_65:
    if (encountno == 55)
      goto LABEL_82;
    if (encountno != 56)
      goto LABEL_100;
    goto LABEL_67;
  }
  return (char)ActiveScene;
}

// 0x1f76d30
static void PlayerAllSync(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *v5;

  sBtlPlayerMotionEff(wk);
  sBtlPlayerUpdate(wk);
  v5 = wk;
  ProcGunMode(v5);
}

// 0x1f780f0
bool sBtlCheckMove_BadStatus(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  u32 BadStatus;
  u32 v6;
  sdatUnitWork_t *para;
  char v8;

  v4 = wk;
  if ((v4->status2 & 0x20000000) == 0)
  {
    if (wk->mode == 6)
      goto LABEL_9;
    v6 = wk->actwk->status - 9;
    if (v6 >= 0x22 || ((0x202000003uLL >> v6) & 1) == 0)
    {
      para = wk->para;
      BadStatus = sBtlGetBadStatus(para);
      v8 = BadStatus - 5;
      if (BadStatus - 5 < 0xC)
        return (0xA79u >> v8) & 1;
      LOBYTE(BadStatus) = BadStatus - 21 < 2;
      return BadStatus;
    }
  }
  LOBYTE(BadStatus) = 0;
  return BadStatus;
LABEL_9:
  LOBYTE(BadStatus) = 1;
  return BadStatus;
}

// 0x1f78b90
static void SBTLMAIN_MODE_STOP_Task(SBTLUNIT_WORK *wk) {
  s32 MenuStatus;
  SBATTLE_WORK *v6;
  s64 i;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBATTLE_WORK *v12;

  MenuStatus = sBtlGetMenuStatus();
  if (MenuStatus != 2)
  {
    if (MenuStatus == 1)
    {
      sBtlSetSummonFunc(wk);
    }
    return;
  }
  RestartBattle();
  sBtlRestart_Scene();
  v6 = wk;
  v6->mode = v6->modebk;
  *(u32 *)v6->gstat = 0;
  wk->vstatus &= ~0x8000000u;
  for (i = 0; ; ++i)
  {
    v9 = wk;
    UnitMng = v9->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->hModel)
      pUnit->vstatus &= ~0x8000000u;
  }
  v9->status2 &= ~2u;
  sBtlResetMidashiAnim(0);
  sBtlResetSelectAnim(0);
  v12 = wk;
  v12->s_time = 0;
  v12->menutype = 0;
  *(u32 *)v12->sgstat = 0;
  sBtlResetColor_PNL(0x80808080);
}

// 0x1f8a640
void sBtlCombSklTrophyUpdate(void) {
  u32 combSkillCnt;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v9;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v11;
  char *v12;
  void *v15;
  Project_DefineAchievementID_string__c *v16;
  s64 v17;
  Project_DefineAchievementID_string__c **v18;
  s64 v19;
  char *v20;

  combSkillCnt = SystemWork->combSkillCnt;
  if (combSkillCnt > 0x12B)
  {
    goto LABEL_7;
  }
  SystemWork->combSkillCnt = combSkillCnt + 1;
  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v9 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    goto LABEL_22;
  goto LABEL_19;
  if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
LABEL_22:
    v11 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x16u);
    goto LABEL_24;
  }
LABEL_19:
  p_offset = &klass->_1.interfaceOffsets->offset;
  while (*(p_offset - 1) != Project_DefineAchievementID_string_)
  {
    p_offset += 2;
    if (!--v9)
      goto LABEL_22;
  }
  v11 = &klass->vtable[*(u32 *)p_offset + 22];
LABEL_24:
  v12 = (*v11)(achievementTbl_k__BackingField, *(u64 *)(v11 + 8));
  ProgressUnlock_3(v12, SystemWork->combSkillCnt, 300);
LABEL_7:
  if (SystemWork->combSkillCnt < 0x12Cu)
    return;
  v15 = _achievementTbl_k__BackingField;
  v16 = v15->klass;
  v17 = *(u16 *)&v15->klass->_2.rank;
  if (!*(u16 *)&v15->klass->_2.rank)
    goto LABEL_37;
  goto LABEL_34;
  if (!*(u16 *)&v15->klass->_2.rank)
  {
LABEL_37:
    v19 = sub_4227F4(v15, Project_DefineAchievementID_string_, 0x16u);
LABEL_39:
    v20 = (*v19)(v15, *(u64 *)(v19 + 8));
    Unlock_2(v20);
    return;
  }
LABEL_34:
  v18 = &v16->_1.interfaceOffsets->offset;
  while (*(v18 - 1) != Project_DefineAchievementID_string_)
  {
    v18 += 2;
    if (!--v17)
      goto LABEL_37;
  }
  v19 = &v16->vtable[*(u32 *)v18 + 22];
  goto LABEL_39;
}

// 0x1f8a950
static s32 CheckAction_Raidou(SBTLUNIT_WORK *wk) {
  bool v5;
  bool v7;
  SBATTLE_WORK *v10;
  SBATTLE_WORK *v14;
  SBTLUNIT_WORK *v17;
  s32 v18;
  s32 v19;
  s32 v21;
  s32 v22;
  s32 GunLockOnNum;
  u32 v30;
  SBTLUNIT_WORK *v32;

  if (wk->battlemode == 1)
  {
    v5 = sBtlCheckMove(wk);
    if (wk->actwk->status != 15)
    {
      if (!v5)
        return -1;
    }
    v10 = wk;
    if (!v10->bRR)
    {
      v10 = wk;
      if (v10->bRR_Assist)
        goto LABEL_31;
      return -1;
    }
LABEL_31:
    sBtlSetFirstAtk(164);
    return -1;
  }
  v7 = sBtlCheckMove(wk);
  if (wk->actwk->status != 15)
  {
    if (!v7)
      return -1;
  }
  sBtlClrSuperArmor(wk);
  if (!wk->bSetsuma)
  {
    goto LABEL_23;
  }
  v21 = sBtlInputChkSetsuma(wk);
  if (v21)
  {
    v22 = v21;
    sBtlSetFirstAtk(v22);
    return 1;
  }
LABEL_23:
  v14 = wk;
  if (v14->bRaiSkill_RU)
  {
    v17 = wk;
    v18 = 0;
    v19 = GBWK->player->raidouSkill[0];
LABEL_56:
    sBtlPlayerRSkillInit(v17, v19, v18);
    return -1;
  }
  v14 = wk;
  if (v14->bRaiSkill_RL)
  {
    v17 = wk;
    v18 = 1;
    v19 = GBWK->player->raidouSkill[1];
    goto LABEL_56;
  }
  v14 = wk;
  if (v14->bRaiSkill_RD)
  {
    v17 = wk;
    v18 = 2;
    v19 = GBWK->player->raidouSkill[2];
    goto LABEL_56;
  }
  v14 = wk;
  if (v14->bSpiritSkill)
  {
    sBtlPlayerRSpiritInit(wk);
    return -1;
  }
  v14 = wk;
  if (v14->bRR)
  {
LABEL_69:
    sBtlSetFirstAtk(1310);
    return -1;
  }
  v14 = wk;
  if (v14->bChgSd)
  {
    sBtlSetFirstAtk(1320);
    return 1;
  }
  v14 = wk;
  if (v14->bChgSd0)
    goto LABEL_79;
  v14 = wk;
  if (v14->bChgLc)
  {
    sBtlSetFirstAtk(1321);
    return 1;
  }
  v14 = wk;
  if (v14->bChgLc0)
    goto LABEL_91;
  v14 = wk;
  if (v14->bChgAx)
  {
    sBtlSetFirstAtk(1322);
    return 1;
  }
  v14 = wk;
  if (v14->bChgAx0)
    goto LABEL_103;
  v14 = wk;
  if (v14->bRR_Assist)
  {
    sBtlBS_LASTB1_Action_Req();
    goto LABEL_69;
  }
  v14 = wk;
  if (v14->bRU_Assist)
  {
    if (sBtlDat()->m_type == 1)
    {
LABEL_79:
      sBtlSetFirstAtk(1323);
      return 1;
    }
    if (sBtlDat()->m_type == 2)
    {
LABEL_91:
      sBtlSetFirstAtk(1333);
      return 1;
    }
    if (sBtlDat()->m_type != 3)
      return -1;
LABEL_103:
    sBtlSetFirstAtk(1339);
    return 1;
  }
  v14 = wk;
  if (v14->bGunMode)
  {
    sBtlChangeGunMode(wk);
    return -1;
  }
  else
  {
    v14 = wk;
    if (!v14->bChgGun)
      return -1;
    v14 = wk;
    GunLockOnNum = v14->GunLockOnNum;
    if (GunLockOnNum < 1)
      return -1;
    GunLockOnNum = wk->GunLockOnNum;
    switch (GunLockOnNum)
    {
      case 1:
        v30 = 65610;
        goto LABEL_137;
      case 2:
        v30 = 65611;
        goto LABEL_137;
      case 3:
        v30 = 65612;
        goto LABEL_137;
      case 4:
        v30 = 65613;
        goto LABEL_137;
      case 5:
        v30 = 65614;
        goto LABEL_137;
      case 6:
        v30 = 65615;
LABEL_137:
        sBtlPlaySE(v30);
        break;
      default:
        break;
    }
    sBtlSetFirstAtk(1296);
    sBtlSetGunMode_Fire(v32);
    return -1;
  }
}

// 0x1f8b390
static bool CheckMoveAction(SBTLUNIT_WORK *wk) {
  u32 status;

  status = wk->actwk->status;
  if (status - 9 <= 0xFFFFFFFD)
    return status - 11 < 0xFFFFFFFE && status != 34;
  return sBtlCheckMove(wk);
}

// 0x1f87c90
bool sBtlCheckMove(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  u32 status;
  dds3ModelHandle_t *v6;
  dds3ModelHandle_t *v7;
  f32 MotionFrameF;
  s32 motionno;

  if (wk->motionno == 136)
  {
    hModel = wk->hModel;
    if (mdlGetMotionFrameF(wk->hModel) <= 14.0)
      return 0;
  }
  status = wk->actwk->status;
  if (status < 3)
    return 1;
  if (status == 8)
  {
    if (wk->Action_HUTTOBI_Cnt < 6)
      return 0;
    v7 = wk->hModel;
    MotionFrameF = mdlGetMotionFrameF(v7);
    motionno = wk->motionno;
    if (motionno != 4)
    {
      if (motionno == 131)
      {
        if (MotionFrameF >= 55.0)
          return 1;
      }
      else
      {
        if (motionno != 5)
          return 0;
        if (MotionFrameF >= 107.0)
          return 1;
      }
      return sBtlCheckMotionEnd(wk);
    }
  }
  else
  {
    if (status != 7)
      return 0;
    v6 = wk->hModel;
    return mdlGetMotionFrameF(v6) >= 17.0;
  }
  return MotionFrameF >= 17.0;
}

// 0x1f8b440
bool sBtlCheckIsDamage(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  s32 motionno;

  if (wk->actwk->status - 7 > 1)
    return 0;
  if (wk->Action_HUTTOBI_Cnt < 6)
    return 1;
  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  motionno = wk->motionno;
  if (motionno == 4)
    return MotionFrameF < 17.0;
  if (motionno == 131)
  {
    if (MotionFrameF < 55.0)
      goto LABEL_11;
    return 0;
  }
  if (motionno != 5 || MotionFrameF >= 107.0)
    return 0;
LABEL_11:
  return !sBtlCheckMotionEnd(wk);
}

// 0x1f8b580
bool sBtlCheckIsMenuNg(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  s32 motionno;
  dds3ModelHandle_t *v7;
  f32 v8;
  dds3ModelHandle_t *v9;
  f32 v10;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  dds3ModelHandle_t *v13;
  f32 v14;

  v4 = wk;
  if (v4->chargeSdCnt)
    return 1;
  if (v4->chargeLcCnt)
    return 1;
  if (v4->chargeAxCnt)
    return 1;
  motionno = wk->motionno;
  if (motionno <= 146)
  {
    if (motionno == 95)
    {
      hModel = wk->hModel;
      MotionFrameF = mdlGetMotionFrameF(hModel);
      if (MotionFrameF >= 3.0 && MotionFrameF <= 6.0)
        return 1;
      if (MotionFrameF >= 15.0 && MotionFrameF <= 35.0)
        return 1;
    }
    else if (motionno == 146)
    {
      v9 = wk->hModel;
      v10 = mdlGetMotionFrameF(v9);
      if (v10 >= 9.0 && v10 <= 20.0)
        return 1;
    }
  }
  else if (motionno == 158)
  {
    v13 = wk->hModel;
    v14 = mdlGetMotionFrameF(v13);
    if (v14 >= 3.0 && v14 <= 21.0)
      return 1;
  }
  else if (motionno == 163 || motionno == 167)
  {
    v7 = wk->hModel;
    v8 = mdlGetMotionFrameF(v7);
    if (v8 >= 5.0 && v8 <= 30.0)
      return 1;
  }
  return 0;
}

// 0x1f8b860
static bool CheckGuard(SBTLUNIT_WORK *wk) {
  u32 status;
  dds3ModelHandle_t *hModel;
  dds3ModelHandle_t *v6;
  f32 MotionFrameF;
  s32 motionno;

  status = wk->actwk->status;
  if (status < 3)
    return 1;
  if (status != 8)
  {
    if (status != 7)
      return 0;
    hModel = wk->hModel;
    return mdlGetMotionFrameF(hModel) >= 17.0;
  }
  if (wk->Action_HUTTOBI_Cnt < 6)
    return 0;
  v6 = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(v6);
  motionno = wk->motionno;
  if (motionno == 4)
    return MotionFrameF >= 17.0;
  if (motionno != 131)
    return motionno == 5 && MotionFrameF >= 50.0;
  return MotionFrameF >= 49.0;
}

// 0x1f8b9a0
static bool CheckKaihi(SBTLUNIT_WORK *wk) {
  u32 status;
  dds3ModelHandle_t *hModel;
  dds3ModelHandle_t *v6;
  f32 MotionFrameF;
  s32 motionno;

  status = wk->actwk->status;
  if (status < 3)
    return 1;
  if (status != 8)
  {
    if (status != 7)
      return 0;
    hModel = wk->hModel;
    return mdlGetMotionFrameF(hModel) >= 17.0;
  }
  if (wk->Action_HUTTOBI_Cnt < 6)
    return 0;
  v6 = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(v6);
  motionno = wk->motionno;
  if (motionno == 4)
    return MotionFrameF >= 17.0;
  if (motionno != 131)
    return motionno == 5 && MotionFrameF >= 50.0;
  return MotionFrameF >= 49.0;
}

// 0x1f7a170
bool sBtlCheckTame(SBTLUNIT_WORK *wk) {
  u32 status;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  dds3ModelHandle_t *v7;
  s32 motionno;

  status = wk->actwk->status;
  if (status != 8)
  {
    if (status == 7)
    {
      hModel = wk->hModel;
      MotionFrameF = mdlGetMotionFrameF(hModel);
      return MotionFrameF >= 20.0;
    }
    return 1;
  }
  if (wk->Action_HUTTOBI_Cnt < 6)
    return 0;
  v7 = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(v7);
  motionno = wk->motionno;
  if (motionno == 4)
    return MotionFrameF >= 20.0;
  if (motionno != 131)
  {
    if (motionno == 5 && MotionFrameF < 90.0)
      goto LABEL_16;
    return 1;
  }
  if (MotionFrameF >= 49.0)
    return 1;
LABEL_16:
  return sBtlCheckMotionEnd(wk);
}

// 0x1f7a2c0
void sBtlResetDamage_TameStart(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;

  if (wk->actwk->status - 7 <= 1)
  {
    v4 = wk;
    v4->mode = 1;
    *(u32 *)v4->gstat = 0;
    sBtlResetAction(wk);
    sBtlSetAction(wk, 1, 0);
    return;
  }
}

// 0x1f77c60
static bool Reset_SupportAction(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v7;

  if (IsSceanStop())
    return 0;
  v7 = wk;
  if (v7->sklProc->bRun)
    return 0;
  if (v7->kaiwaflg)
    return 0;
  sBtlReset_SupportAction_Shugou(wk);
  return 1;
}

// 0x1f8be00
SKLID *sBtlGetCombSkill(SBTLUNIT_WORK *pUnit) {
  s32 v5;
  s64 v6;
  s64 v7;

  combSkill[0] = 0;
  combSkill[1] = 0;
  combSkill[2] = 0;
  combSkill[3] = 0;
  combSkill[4] = 0;
  combSkill[5] = 0;
  combSkill[6] = 0;
  combSkill[7] = 0;
  combSkill[8] = 0;
  combSkill[9] = 0;
  combSkill[10] = 0;
  combSkill[11] = 0;
  combSkill[12] = 0;
  combSkill[13] = 0;
  combSkill[14] = 0;
  combSkill[15] = 0;
  v5 = 0;
  v6 = 32;
  combSkill[16] = 0;
  do
  {
    if ((sBtlGetSkilltbl(*(u32 *)((char *)&pUnit->haveskill->obj.klass + v6))->type & 0x1000) != 0)
    {
      v7 = (s64)combSkill + 4 * v5++;
      *(u32 *)(v7 + 32) = *(u32 *)((char *)&pUnit->haveskill->obj.klass + v6);
    }
    v6 += 4;
  }
  while (v6 != 100);
  return combSkill;
}

// 0x1f7c000
static bool Check_SupportAction(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 status;
  SBATTLE_WORK *v18;

  v4 = wk;
  if (v4->cmbSkl->bRun)
    return 0;
  v4 = wk;
  UnitMng = v4->UnitMng;
  playerID = v4->playerID;
  para = sBtlSearchUnit_ID(UnitMng, playerID)->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus != 10)
  {
    if (sBtlIsBattleKey(4151, 2) && sBtlGetNakama(0))
    {
      SetNakamaSkillAct(0);
    }
    if (sBtlIsBattleKey(4152, 2) && sBtlGetNakama(1))
    {
      SetNakamaSkillAct(1);
    }
  }
  Check_SupportAction_CameraLockOn(wk);
  status = wk->actwk->status;
  if (status - 9 < 0xFFFFFFFE)
  {
    if (status <= 0x22 && ((1 << status) & 0x400000600LL) != 0)
      return 0;
    goto LABEL_41;
  }
  if (!sBtlCheckMove(wk))
    return 0;
LABEL_41:
  v18 = wk;
  if (v18->sklProc->bRun)
    return 0;
  v18 = wk;
  if (v18->kaiwaflg)
    return 0;
  v18 = wk;
  if ((v18->status2 & 0x20000000) != 0)
    return 0;
  if ((BadStatus & 0xFFFFFFFD) == 8)
    return 0;
  Check_SupportAction_Shugou(wk);
  return 1;
}

// 0x1f8c2f0
bool sBtlBstShugouCheck(BST _bst) {
  return (bst & 0xFFFFFFFD) == 8;
}

// 0x1f8c1a0
static void SetNakamaSkillAct(s32 summonidx) {
  s32 v5;
  s64 v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v8;
  SBTLUNIT_WORK *v9;
  SBTLAI_WORK *aiwk;
  s32 v11;
  s32 v12;

  v5 = wk->summonindex[summonidx];
  if (v5 < 0)
    return;
  v6 = (u16)v5;
  UnitMng = wk->UnitMng;
  v8 = wk->summonID[v6];
  v9 = sBtlSearchUnit_ID(UnitMng, v8);
  if (!v9)
    return;
  aiwk = v9->aiwk;
  v11 = aiwk->skillAct ^ 1;
  aiwk->skillAct = v11;
  if (v11)
    v12 = 42;
  else
    v12 = 41;
  SE(v12);
}

// 0x1f8c5e0
static f32 CheckAutoSkill_Escape(f32 per0) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (!CheckLiveTarget(pUnit))
      continue;
    if ((pUnit->side & 1) != 0)
    {
      para = pUnit->para;
      if (!sBtlChkHaveMemSkl(para, 6))
        continue;
      per0 = (f32)(per0 * (f32)pUnit->para->autost_cnt2) / 100.0;
      continue;
    }
  }
  return per0;
}

// 0x1f8c780
static bool SetColor(u32 abgr) {
  sBtlSetColor_PNL(abgr);
  return 1;
}

// 0x1f87e60
static f32 GetAnlogKey(SBTLUNIT_WORK *wk, sdfVector4_t *direction) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  f32 v7;
  f32 v8;
  f32 AnalogSensitivity;
  s32 v11;
  s32 v12;
  s32 v13;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v21;
  f32 v22;
  u32 v26;
  u32 *v28;
  f32 *v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v34;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  v7 = 0.0;
  if (IsSceanStop())
  {
    v8 = 0.0;
LABEL_29:
    goto LABEL_30;
  }
  AnalogSensitivity = fldGetAnalogSensitivity();
  if (AnalogSensitivity == INFINITY)
    v11 = 0x80000000;
  else
    v11 = AnalogSensitivity;
  v12 = 128 - v11;
  if (128 - v11 <= dds3PadGetAnalogLX(0))
  {
    v13 = v11 + 128;
    if (v13 < dds3PadGetAnalogLX(0))
      goto LABEL_84;
    if (v12 > dds3PadGetAnalogLY(0))
      goto LABEL_84;
    v8 = 0.0;
    if (v13 < dds3PadGetAnalogLY(0))
      goto LABEL_84;
    goto LABEL_29;
  }
LABEL_84:
  if ((wk->side & 0x80) == 0)
  {
    if (wk->battlemode != 3)
    {
LABEL_90:
      goto LABEL_92;
    }
    if ((wk->side & 1) == 0)
      goto LABEL_90;
  }
  if (BadStatus != 8)
  {
LABEL_92:
    v7 = (f32)dds3PadGetAnalogLX(1) + -128.0;
    v8 = -(f32)((f32)dds3PadGetAnalogLY(1) + -128.0);
    goto LABEL_29;
  }
  v7 = -(f32)((f32)dds3PadGetAnalogLX(1) + -128.0);
  v8 = (f32)dds3PadGetAnalogLY(1) + -128.0;
  goto LABEL_29;
LABEL_30:
  vct_A.x = v7;
  vct_A.y = 0.0;
  vct_A.z = v8;
  vct_A.w = 1.0;
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v21 = (f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z);
  sub_1949110(0);
  v22 = sqrtf(v21);
  if (v22 >= 48.0)
  {
LABEL_61:
    goto LABEL_62;
  }
  if ((wk->side & 0x80) != 0)
  {
    v26 = 0;
    if (BadStatus == 8)
LABEL_51:
      v26 = 0x80000000;
  }
  else
  {
    v26 = 0;
    if (wk->battlemode == 3 && (wk->side & 1) != 0 && BadStatus == 8)
      goto LABEL_51;
  }
  v28 = &vf00.x;
  v28[4] = v26;
  v28[5] = 0;
  v28[6] = v26;
  v28[7] = 1065353216;
  v29 = &vf00.x;
  v30 = v29[4];
  v31 = v29[5];
  v32 = v29[6];
  v34 = (f32)((f32)(v30 * v30) + (f32)(v31 * v31)) + (f32)(v32 * v32);
  sub_1949110(0);
  v22 = sqrtf(v34);
  goto LABEL_61;
LABEL_62:
  *direction = vct_A;
  return v22;
}

// 0x1f7fbb0
static bool Sord1Proc_New(SBTLUNIT_WORK *wk, SBTLMAIN_MODE mode) {
  s32 *p_sord_counter;
  dds3ModelHandle_t *hModel;
  SBATTLE_WORK *v12;
  SBATTLE_WORK *v15;
  SBATTLE_WORK *v17;
  SBTLACTION_WORK *actwk;
  u32 status;
  sdatUnitWork_t *para;
  u32 BadStatus;
  dds3ModelHandle_t *v26;
  s32 v27;
  s32 v28;
  bool v29;
  s32 v30;
  SBATTLE_WORK *v33;
  SBTLUNIT_WORK *v35;
  s32 v36;
  SBATTLE_WORK *v38;
  s32 v39;
  s32 use_skillid;
  SBATTLE_WORK *v43;
  s32 sord_st;
  _BOOL4 GunMotionEnd;
  SBATTLE_WORK *v49;
  SBATTLE_WORK *v51;
  sdatUnitWork_t *v52;
  u32 v53;
  dds3ModelHandle_t *v54;
  f32 MotionFrameF;
  f32 v62;
  SBATTLE_WORK *v63;
  u32 v64;
  s32 v65;
  s32 v66;
  SBATTLE_WORK *v70;
  SBATTLE_WORK *v72;
  bool ComboDone[4];

  ComboDone[0] = 0;
  p_sord_counter = &wk->sord_counter;
  ++*p_sord_counter;
  LimitRange(p_sord_counter, 0, 0x7FFF);
  sBtlGetSkilltbl(wk->actwk->use_skillid);
  if (wk->actwk->use_skillid == 1297 && !wk->GunMotionEnd)
  {
    hModel = wk->hModel;
    if (mdlGetMotionFrame(wk->hModel) > 8)
      goto LABEL_16;
    goto LABEL_9000;
    if (mdlGetMotionFrame(hModel) > 8)
    {
LABEL_16:
      wk->GunMotionEnd = 1;
      goto LABEL_17;
    }
LABEL_9000:
    if (sBtlCheckMotionEnd(wk))
      goto LABEL_16;
  }
LABEL_17:
  v12 = wk;
  if (v12->cmbSkl->bRun)
    goto LABEL_37;
  if (v12->kaiwaflg)
    goto LABEL_37;
  if (v12->sord_st)
    goto LABEL_27;
  goto LABEL_9002;
  if (wk->sord_st)
  {
LABEL_27:
    if (CancelSystem(ComboDone))
    {
      if (ComboDone[0])
      {
        v15 = wk;
        v15->mode = 1;
        *(u32 *)v15->gstat = 0;
        sBtlResetAction(wk);
LABEL_77:
        sBtlSetAction(wk, 1, 0);
        goto LABEL_79;
      }
      return 1;
    }
    goto LABEL_39;
  }
LABEL_9002:
LABEL_37:
LABEL_39:
  v17 = wk;
  switch (v17->sord_st)
  {
    case 0:
      actwk = wk->actwk;
      if ((actwk->use_skillid & 0xFFFFFFFE) != 0x510)
      {
        sBtlResetGunMode(wk, 0);
        actwk = wk->actwk;
      }
      status = actwk->status;
      wk->JumpAfterCnt = 0;
      wk->damage_ActerOfsY = 0.0;
      if (status != 9)
        goto LABEL_101;
      para = wk->para;
      BadStatus = sBtlGetBadStatus(para);
      if (BadStatus > 0xC || ((1 << BadStatus) & 0x10C0) == 0)
      {
        actwk = wk->actwk;
LABEL_101:
        use_skillid = actwk->use_skillid;
        sBtlSetUseSkill(wk, use_skillid, 0);
        sBtlSetAction(wk, 12, 0);
        v43 = wk;
        sord_st = v43->sord_st;
        v43->ComboMotRetryOldFrame = -999.0;
        v43->sord_bugfix = 0;
        v43->ComboMotRetryCnt = 0;
        v43->ComboMotRetryUse = 0;
        v43->sord_timeoutcnt = 0;
        v43->sord_st = sord_st + 1;
        wk->hstatus &= ~0x20000u;
        return 1;
      }
      wk->hstatus &= ~0x20000u;
      goto LABEL_51;
    case 1:
      v26 = wk->hModel;
      if (mdlGetMotionFrame(wk->hModel) < -5)
        return 1;
      v38 = wk;
      v39 = v38->sord_st;
      *(u64 *)&v38->sord_keybk = 0;
      v38->sord_actionf = 0;
      v38->sord_st = v39 + 1;
      sBtlCheckMHTData(wk, wk->actwk->use_skillid);
      return 1;
    case 2:
      v27 = wk->actwk->use_skillid;
      if (v27 <= 191)
      {
        if (v27 <= 55)
        {
          if (v27 <= 23)
          {
            if (v27 == 8 || v27 == 23)
              return 1;
          }
          else if ((v27 | 0x10) == 0x37)
          {
            return 1;
          }
        }
        else if ((u32)v27 <= 0x9E)
        {
          if ((u32)(v27 - 156) < 3 || (u32)(v27 - 64) < 2)
            return 1;
        }
        else if (v27 == 163 || v27 == 191)
        {
          return 1;
        }
        goto LABEL_130;
      }
      if ((u32)v27 <= 0x2E8)
      {
        if ((u32)v27 <= 0xD4)
        {
          if ((v27 | 4) == 0xD4)
            return 1;
        }
        else if ((u32)(v27 - 312) < 2 || v27 == 744)
        {
          return 1;
        }
        goto LABEL_130;
      }
      if ((u32)v27 <= 0x511)
      {
        if (v27 == 1296)
        {
          if (!sBtlGetGunLockOn_TgtNum())
          {
            v70 = wk;
            if (v70->sord_counter >= 26)
            {
              v70 = wk;
              v70->mode = 1;
              *(u32 *)v70->gstat = 0;
              sBtlResetAction(wk);
LABEL_156:
              sBtlSetAction(wk, 1, 0);
              sBtlResetJump(wk);
              if ((wk->vstatus & 0x8000) == 0)
              {
LABEL_79:
                v35 = wk;
                v36 = 0;
LABEL_80:
                sBtlSetMotion(v35, v36, 0, 0, 0);
                return 1;
              }
LABEL_179:
              v36 = 76;
              v35 = wk;
              goto LABEL_80;
            }
          }
          if (!sBtlCheckNextAction(wk))
            return 1;
          v72 = wk;
          v72->mode = 1;
          *(u32 *)v72->gstat = 0;
          goto LABEL_154;
        }
        if (v27 == 1297)
        {
          if (sBtlGetGunLockOn_TgtNum())
            return 1;
          GunMotionEnd = wk->GunMotionEnd;
          v49 = wk;
          if (!GunMotionEnd && v49->sord_counter < 9)
            return 1;
          v49 = wk;
          v49->mode = 1;
          *(u32 *)v49->gstat = 0;
          sBtlResetAction(wk);
          sBtlSetAction(wk, 1, 0);
          goto LABEL_179;
        }
        goto LABEL_130;
      }
      if (v27 == 1307 || v27 == 1316 || (u32)(v27 - 1358) >= 0xFFFFFFFC)
        return 1;
      if (v27 != 1309)
        goto LABEL_130;
      v17 = wk;
      v28 = v17->sord_timeoutcnt + 1;
      v29 = v17->sord_timeoutcnt - 60 < 0;
      v17->sord_timeoutcnt = v28;
      if (v29 != __OFSUB__(v28, 61))
      {
LABEL_130:
        v30 = 0;
        goto LABEL_131;
      }
      v17 = wk;
      v30 = 1;
      v17->sord_bugfix = 1;
LABEL_131:
      if (wk->sord_bugfix)
      {
        if (!(v30 | sBtlCheckNextAction(wk)))
          return 1;
        v51 = wk;
        v51->mode = 1;
        *(u32 *)v51->gstat = 0;
        if (wk->actwk->status == 9)
        {
          v52 = wk->para;
          v53 = sBtlGetBadStatus(v52);
          if (v53 <= 0xC && ((1 << v53) & 0x10C0) != 0)
          {
LABEL_51:
            sBtlResetAction(wk);
            sBtlResetJump(wk);
            return 1;
          }
        }
LABEL_154:
        sBtlResetAction(wk);
        goto LABEL_156;
      }
      v54 = wk->hModel;
      MotionFrameF = mdlGetMotionFrameF(v54);
      if (MotionFrameF <= 0.0)
      {
        v62 = MotionFrameF;
        v63 = wk;
        if (v63->ComboMotRetryUse)
          return 1;
        v63 = wk;
        if (v63->ComboMotRetryOldFrame == v62)
        {
          if (!v64)
          {
            v63 = wk;
          }
          v65 = v63->ComboMotRetryCnt + 1;
          v63->ComboMotRetryCnt = v65;
          if (v65 == 3)
          {
            v63 = wk;
            v63->ComboMotRetryUse = 1;
            v66 = wk->actwk->use_skillid;
            if (v66 <= 1329)
            {
              switch (v66)
              {
                case 1323:
                  v36 = 144;
                  v35 = wk;
                  goto LABEL_80;
                case 1328:
                  v36 = 149;
                  v35 = wk;
                  goto LABEL_80;
                case 1329:
                  v36 = 150;
                  v35 = wk;
                  goto LABEL_80;
              }
            }
            else
            {
              if ((u32)v66 > 0x53B)
              {
                if (v66 == 1343)
                {
                  v36 = 164;
                  v35 = wk;
                }
                else
                {
                  if (v66 != 1344)
                    return 1;
                  v36 = 165;
                  v35 = wk;
                }
                goto LABEL_80;
              }
              if (v66 == 1333)
              {
                v36 = 154;
                v35 = wk;
                goto LABEL_80;
              }
              if (v66 == 1339)
              {
                v36 = 160;
                v35 = wk;
                goto LABEL_80;
              }
            }
          }
          return 1;
        }
        if (!v64)
        {
          v63 = wk;
        }
        v63->ComboMotRetryOldFrame = v62;
        return 1;
      }
      else
      {
        wk->sord_bugfix = 1;
        return 1;
      }
    case 4:
      if (!sBtlCheckNextAction(wk))
        return 1;
      v33 = wk;
      v33->mode = 1;
      *(u32 *)v33->gstat = 0;
      sBtlResetAction(wk);
      goto LABEL_77;
    default:
      return 1;
  }
}

// 0x1f8f890
void sBtlSetVibe(SBTLPLAYER_VTYPE mode) {
  void *v3;
  u32 *v4;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;
  __int128 v9;

  v9 = xmmword_3CF90B0;
  v3 = sub_3BD9D0(int_, &v9);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__7ADEC785B5C60B2B28CA76DE8010FF661743142E486A8DE8F8868457E1644A61, 0);
  v4 = (u32 *)v3 + (s64)v3[1].klass->_1.name * mode;
  v5 = v4[8];
  v6 = v4[9];
  v7 = v4[10];
  v8 = v4[11];
  SetVibe(v5, v6, v7, v8);
}

// 0x1f8f990
s32 sBtlGetPlayerID(void) {
  s32 unitpadID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;

  if ((wk->status & 0x4000000) != 0)
  {
    unitpadID = wk->unitpadID;
    goto LABEL_14;
  }
  unitpadID = wk->playerID;
LABEL_14:
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, unitpadID);
  if (v6)
  {
    v7 = v6;
    if (sBtlCheckDamageTarget(v6))
      return unitpadID;
  }
  return wk->playerID;
}

// 0x1f8fb50
SBTLUNIT_WORK *sBtlGetPlayerUnit(s32 id) {
  SBTLUNIT_LISTWORK *UnitMng;

  UnitMng = wk->UnitMng;
  return sBtlSearchUnit_ID(UnitMng, id);
}

// 0x1f8fc20
bool sBtlCheckPad(void) {
  u32 status;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  dds3MoverBasicObjFunc_t v7;
  s32 ListID;
  SBATTLE_WORK *v10;
  u32 v12;
  SBTLUNIT_LISTWORK *v15;
  s32 unitpadID;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  dds3MoverBasicObjFunc_t v19;
  s32 v21;
  SBATTLE_WORK *v22;
  SBATTLE_WORK *v24;
  SBTLUNIT_LISTWORK *v25;
  s32 playerID;
  SBTLUNIT_WORK *v27;

  if (!wk)
    return 0;
  if (!wk->UnitMng)
    return 0;
  status = wk->status;
  if ((status & 2) != 0)
    return 0;
  if ((status & 0x4000000) == 0)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return 1;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x80) != 0 && pUnit->mode == 8)
      {
        v7 = Allocate(dds3MoverBasicObjFunc_t);
        _ctor(v7, 0, Method_Project_sBtlPlayer_sBtlPlayer_Pad__, 0);
        dds3ObjectBaseSetPadControl(&pUnit->pBasic, v7);
        ListID = pUnit->ListID;
        v10 = wk;
        v12 = v10->status;
        v10->playerID = ListID;
        v10->status = v12 | 2;
        sBtlSetScrollID(ListID);
        return 1;
      }
    }
  }
  v15 = wk->UnitMng;
  unitpadID = wk->unitpadID;
  v17 = sBtlSearchUnit_ID(v15, unitpadID);
  if (v17)
  {
    v18 = v17;
    if (sBtlCheckDamageTarget(v18))
    {
      v19 = Allocate(dds3MoverBasicObjFunc_t);
      _ctor(v19, 0, Method_Project_sBtlPlayer_nakamamode_UnitPad__, 0);
      dds3ObjectBaseSetPadControl(&v18->pBasic, v19);
      v21 = v18->ListID;
      v22 = wk;
      v22->status |= 2u;
      sBtlSetScrollID(v21);
      v24 = wk;
      v25 = v24->UnitMng;
      playerID = v24->playerID;
      v27 = sBtlSearchUnit_ID(v25, playerID);
      if (v27 && (v27->side & 0x80) != 0 && v27->mode == 8)
        dds3ObjectBaseSetPadControl(&v27->pBasic, 0);
    }
  }
  return 1;
}

// 0x1f6e290
bool sBtlResetAction(SBTLUNIT_WORK *wk) {
  s32 hstatus;
  SBTLACTAI_WORK *actaiwk;
  SBATTLE_WORK *v11;

  if ((wk->vstatus & 0x8000) != 0)
    DeleteAll();
  sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
  wk->vstatus &= 0xF77DFFFF;
  sBtlStatusBitOff(wk, 0xFFFFBEEE);
  hstatus = wk->hstatus;
  wk->IsMagAtk = 0;
  wk->motion_UseWait2 = 0;
  wk->motion_EndNoCng = 0;
  wk->hstatus = hstatus & 0xF873FBDF;
  wk->flg &= 0xFFF3F7FF;
  wk->status &= ~1u;
  FalseHuuma(wk);
  actaiwk = wk->actaiwk;
  actaiwk->targetID_Mawari = -1;
  actaiwk->status &= 0xFFFFBDFF;
  v11 = wk;
  v11->mode = 1;
  *(u32 *)v11->gstat = 0;
  v11->sord_st = 0;
  v11->sord_counter = 0;
  v11->sord_actionf = 0;
  v11->sord_bugfix = 0;
  v11->walk_counter = 0;
  v11->escape_cnt = 0;
  v11->accele_flg = 0;
  v11->accele_cnt = 0;
  v11->raido_magwaza_costnot = 0;
  wk->vstatus |= 0x80u;
  wk->actwk->gravcnt = 0;
  sBtlResetCharge(wk, 0);
  return 1;
}

// 0x1f90810
void sBtlResetAction_FO_Eve(SBTLUNIT_WORK *wk, bool _animNoChange) {
  sBtlResetJump(wk);
  sBtlResetJump_FO_Eve(wk);
  sBtlResetAction(wk);
  wk->next_motion_not_hokan = 1;
  if (!animNoChange)
  {
    sBtlSetMotion(wk, 0, 0, 0, 0);
    sBtlSetUseSkill(wk, 0, 0);
    sBtlSetAction(wk, 1, 0);
  }
}

// 0x1f90970
bool sBtlStopAction(void) {
  wk->modebk = wk->mode;
  wk->mode = 5;
  return 1;
}

// 0x1f8a480
bool sBtlActiveAction(void) {
  wk->mode = wk->modebk;
  return 1;
}

// 0x1f909e0
void sBtlResetATKEffect(void) {
  SBTLEFF_LISTWORK *effList;
  SBTLITEM_TBL *Itemtbl;

  effList = wk->effList;
  sBtlDeleteEffectData_SkillIDType(effList, 144, 1u);
  sBtlDeleteEffectData_SkillIDType(wk->effList, 1326, 1u);
  sBtlDeleteEffectData_SkillIDType(wk->effList, 1333, 1u);
  sBtlDeleteEffectData_SkillIDType(wk->effList, 1334, 1u);
  sBtlDeleteEffectData_SkillIDType(wk->effList, 1341, 1u);
  Itemtbl = sBtlGetItemtbl(wk->equipbullet);
  sBtlDeleteEffectData_SkillIDType(wk->effList, Itemtbl->sklid, 1u);
}

// 0x1f90b70
void sBtlSetNSTOP(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->hModel)
      pUnit->vstatus |= 0x8000000u;
  }
}

// 0x1f8a4f0
void sBtlResetNSTOP(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->hModel)
      pUnit->vstatus &= ~0x8000000u;
  }
}

// 0x1f90400
void sBtlResetCharge(SBTLUNIT_WORK *wk, bool _Immed) {
  bool v6;
  SBATTLE_WORK *v8;
  s32 *GunLockOnTgtID;
  s32 *GunLockOnTgtSubIdx;
  s64 i;
  char *v14;
  SBATTLE_WORK *v15;
  s32 *GunLockOnTgtPushPop;

  if ((wk->vstatus & 0x8000) == 0)
  {
    goto LABEL_4;
  }
  DeleteAll();
LABEL_4:
  if (!wk->chargeSdCnt)
    goto LABEL_6;
  goto LABEL_5;
  if (wk->chargeSdCnt)
  {
LABEL_5:
    Del(Immed, 0);
    AW_TameDel(Immed);
  }
LABEL_6:
  if (!wk->chargeLcCnt)
    goto LABEL_9;
  goto LABEL_8;
  if (wk->chargeLcCnt)
  {
LABEL_8:
    Del(Immed, 0);
    AW_TameDel(Immed);
  }
LABEL_9:
  if (!wk->chargeAxCnt)
    goto LABEL_12;
  goto LABEL_11;
  if (wk->chargeAxCnt)
  {
LABEL_11:
    v6 = Immed;
    Del(v6, 0);
    AW_TameDel(v6);
  }
LABEL_12:
  v8 = wk;
  v8->chargeSdCnt = 0;
  v8->chargeLcCnt = 0;
  v8->chargeAxCnt = 0;
  *(u64 *)&v8->chargeGunCnt = 0;
  v8->GunLockOnNum = 0;
  *(u64 *)&v8->sord_cstat = 0;
  *(u64 *)&v8->gun_cstat = 0;
  *(u64 *)&v8->bChgSd = 0;
  v8 = wk;
  GunLockOnTgtID = v8->GunLockOnTgtID;
  GunLockOnTgtID[0] = -1;
  GunLockOnTgtSubIdx = v8->GunLockOnTgtSubIdx;
  GunLockOnTgtSubIdx[0] = 0;
  GunLockOnTgtID[1] = -1;
  GunLockOnTgtSubIdx[1] = 0;
  GunLockOnTgtID[2] = -1;
  GunLockOnTgtSubIdx[2] = 0;
  GunLockOnTgtID[3] = -1;
  GunLockOnTgtSubIdx[3] = 0;
  GunLockOnTgtID[4] = -1;
  GunLockOnTgtSubIdx[4] = 0;
  GunLockOnTgtID[5] = -1;
  GunLockOnTgtSubIdx[5] = 0;
  for (i = 0; ; ++i)
  {
    v15 = wk;
    GunLockOnTgtPushPop = v15->GunLockOnTgtPushPop;
    if (i >= SLODWORD(GunLockOnTgtPushPop->max_length))
      break;
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    v14 = (char *)GunLockOnTgtPushPop + 4 * i;
    *((u32 *)v14 + 8) = -1;
  }
  wk->hstatus &= 0xFC7FFFFF;
  v15->bltUpCnt = 0;
}

// 0x1f90d10
void sBtlResetHitBack(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 status;

  if (wk)
  {
    actaiwk = wk->actaiwk;
    status = actaiwk->status;
    wk->status &= ~0x20u;
    actaiwk->status = status & 0xFFFFFFDF;
    wk->vstatus &= ~0x800u;
  }
}

// 0x1f72430
static bool R1_HuumaBtn(void) {
  return wk->mode == 12;
}

// 0x1f723c0
bool sBtlR1_IsNaked(void) {
  return wk->battlemode == 1;
}

// 0x1f90d40
bool sBtlIsMoveBtn(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v3;
  bool v4;

  v3 = wk;
  if (v3->bIsNoMoveBad)
    return 0;
  if ((wk->status4 & 0x800000) != 0)
    return 0;
  v4 = 1;
  if (dds3PadGetAnalogLX(1) < 0x40u)
    return v4;
  if (dds3PadGetAnalogLX(1) > 0xC0u)
    return v4;
  if (dds3PadGetAnalogLY(1) < 0x40u)
    return v4;
  return dds3PadGetAnalogLY(1) > 0xC0u;
}

// 0x1f90ed0
static bool RegistShortCutBtn(void) {
  if (wk->encountno == 515)
  {
    if (wk->tuto_r2_di)
      return 0;
  }
  if (CHECK_PRESS(regist_shortcut, 1))
    return evtBitCheck(9988);
  return 0;
}

// 0x1f91000
static bool shortCutBtnCHECK(void) {
  if (wk->battlemode == 3)
    return 0;
  if (get_Instance(0)->sc_pause == 2)
    return 0;
  return RegistShortCutBtn();
}

// 0x1f910e0
static bool IsGunMode(void) {
  SBTLUNIT_WORK *PChara;

  PChara = sBtlGetPChara();
  if (PChara)
    LODWORD(PChara) = BYTE1(PChara->vstatus) >> 7;
  return (char)PChara;
}

// 0x1f724a0
static bool IsSWAZA_AdvanceCheck(void) {
  SBTLUNIT_WORK *PChara;

  if (!sBtlIsBattleKey(4180, 2))
    return 0;
  PChara = sBtlGetPChara();
  if (PChara)
  {
    if ((PChara->vstatus & 0x8000) != 0)
      return 0;
  }
  if (sBtlIsSpiritWazaAndEnemyLive())
    return 1;
  return 0;
}

// 0x1f91110
static bool IsLookChgR_Push(void) {
  return CHECK_PRESS(24587, 1);
}

// 0x1f70a20
bool sBtlIsBattleKey(SDF_PADMAP key, sBtlPlayer_PADREAD read) {
  char v3;
  bool v10;
  bool result;
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v16;
  SBATTLE_WORK *v18;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  s32 v21;
  SBTLUNIT_WORK *v23;
  SBTLUNIT_WORK *v24;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v28;
  SBTLUNIT_WORK *v31;
  SBTLUNIT_WORK *v34;
  SBATTLE_WORK *v36;
  s32 NewID;
  s32 v43;
  SBTLUNIT_WORK *v47;
  SBTLUNIT_WORK *v49;
  SBTLUNIT_WORK *v51;
  SBTLUNIT_WORK *v53;

  v3 = read;
  if ((wk->status4 & 0x80000) != 0)
    return 0;
  if (sbtlplayertblCompulsion_TutoEtc(key))
    return 0;
  if (wk->AttackBtn_NgTime > 0)
    return 0;
  switch (key)
  {
    case 4120:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      if (!sBtlR1_IsNaked())
      {
        if (shortCutBtnCHECK())
          return 0;
      }
      PChara = sBtlGetPChara();
      if (PChara)
      {
        if ((PChara->vstatus & 0x8000) != 0)
          return 0;
      }
      if ((v3 & 1) != 0 && CHECK_PRESS2(20483))
        return 1;
      if ((v3 & 2) != 0 && CHECK_TRIG2(20483))
        return 1;
      return (v3 & 4) != 0 && CHECK_REP2(20483);
    case 4121:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      if (wk->battlemode == 1)
        return 0;
      if (shortCutBtnCHECK())
        return 0;
      v16 = sBtlGetPChara();
      if (v16)
      {
        if ((v16->vstatus & 0x8000) != 0)
          return 0;
      }
      if ((v3 & 1) != 0 && CHECK_PRESS2(20482))
        return 1;
      if ((v3 & 2) != 0 && CHECK_TRIG2(20482))
        goto LABEL_496;
      return (v3 & 4) != 0 && CHECK_REP2(20482);
    case 4122:
      if (!wk->bIsNoMoveBad)
      {
        if ((wk->status4 & 0x800000) == 0)
        {
          if (wk->battlemode != 1)
          {
            v10 = 0;
            if (sbtlplayertblChkNG_TutoEtc(1, 0, 4122))
              return v10;
            v18 = wk;
            UnitMng = v18->UnitMng;
            playerID = v18->playerID;
            v21 = v18->playerID;
            playerID = v21;
            if ((sBtlSearchUnit_ID(UnitMng, playerID)->vstatus & 0x8000) != 0)
            {
              if ((v3 & 1) != 0)
              {
                v10 = 1;
                if (CHECK_PRESS(20492, 1))
                  return v10;
              }
              if ((v3 & 2) != 0)
              {
                v10 = 1;
                if (CHECK_TRIG(20492, 1))
                  return v10;
              }
              if ((v3 & 4) != 0)
              {
                v10 = 1;
                if (CHECK_REP(20492, 1))
                  return v10;
              }
            }
          }
        }
      }
      return 0;
    case 4123:
      if (!wk->bIsNoMoveBad)
      {
        if ((wk->status4 & 0x800000) == 0)
        {
          if (wk->battlemode != 1)
          {
            v10 = 0;
            if (sbtlplayertblChkNG_TutoEtc(1, 0, 4123))
              return v10;
            if ((v3 & 1) != 0)
            {
              v10 = 1;
              if (CHECK_PRESS(20489, 1))
                return v10;
            }
            if ((v3 & 2) != 0)
            {
              v10 = 1;
              if (CHECK_TRIG(20489, 1))
                return v10;
            }
          }
        }
      }
      return 0;
    case 4124:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      if (wk->battlemode == 1)
        return 0;
      if (shortCutBtnCHECK())
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4124))
        return v10;
      v23 = sBtlGetPChara();
      if (v23 && (v23->vstatus & 0x8000) != 0)
        return 0;
      if ((v3 & 1) != 0 && CHECK_PRESS2(20480))
        return 1;
      if ((v3 & 2) != 0 && CHECK_TRIG2(20480))
        goto LABEL_496;
      return (v3 & 4) != 0 && CHECK_REP2(20480);
    case 4125:
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      if (wk->battlemode == 1)
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4125))
        return v10;
      if (shortCutBtnCHECK())
        return 0;
      if ((v3 & 1) != 0)
      {
        v10 = 1;
        if (CHECK_PRESS(24587, 1))
          return v10;
      }
      if ((v3 & 2) != 0)
      {
        v10 = 1;
        if (CHECK_TRIG(24587, 1))
          return v10;
      }
      return 0;
    case 4126:
      if ((wk->status4 & 0x800000) == 0)
      {
        if (wk->battlemode != 1)
        {
          v10 = 0;
          if (sbtlplayertblChkNG_TutoEtc(1, 0, 4126))
            return v10;
          v10 = 1;
          if (CHECK_TRIG(24589, 1))
            return v10;
        }
      }
      return 0;
    case 4145:
      if ((wk->status4 & 0x800000) == 0)
      {
        v10 = 0;
        if (sbtlplayertblChkNG_TutoEtc(1, 0, 4145))
          return v10;
        v24 = sBtlGetPChara();
        if (!v24 || (v24->vstatus & 0x8000) == 0)
        {
          if ((v3 & 1) != 0)
          {
            v10 = 1;
            if (CHECK_PRESS(20494, 1))
              return v10;
          }
          if ((v3 & 2) != 0)
          {
            v10 = 1;
            if (CHECK_TRIG(20494, 1))
              return v10;
          }
          if ((v3 & 4) != 0)
          {
            v10 = 1;
            if (CHECK_REP(20494, 1))
              return v10;
          }
        }
      }
      return 0;
    case 4151:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v25 = sBtlGetPChara();
      if (v25)
      {
        if ((v25->vstatus & 0x8000) != 0)
          return 0;
      }
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4151))
        return v10;
      if (wk->battlemode == 1)
        return 0;
      return !shortCutBtnCHECK()
          && !CHECK_PRESS(24587, 1)
          && CHECK_TRIG2(20486);
    case 4152:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v28 = sBtlGetPChara();
      if (v28)
      {
        if ((v28->vstatus & 0x8000) != 0)
          return 0;
      }
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4152))
        return v10;
      if (wk->battlemode == 1)
        return 0;
      return !shortCutBtnCHECK()
          && !CHECK_PRESS(24587, 1)
          && CHECK_TRIG2(20487);
    case 4153:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v31 = sBtlGetPChara();
      if (v31)
      {
        if ((v31->vstatus & 0x8000) != 0)
          return 0;
      }
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4153))
        return v10;
      return wk->battlemode != 1 && CHECK_TRIG2(20490);
    case 4155:
      if (!wk->bIsNoMoveBad)
      {
        if ((wk->status4 & 0x800000) == 0)
        {
          if (!wk->bRaiSkill_RU_Pause)
          {
            if (!wk->bRaiSkill_RL_Pause)
            {
              if (!wk->bRaiSkill_RD_Pause)
              {
                if (!shortCutBtnCHECK())
                {
                  v34 = sBtlGetPChara();
                  if (!v34 || (v34->vstatus & 0x8000) == 0)
                  {
                    v10 = 0;
                    if (sbtlplayertblChkNG_TutoEtc(1, 0, 4155))
                      return v10;
                    if ((v3 & 1) != 0)
                    {
                      v10 = 1;
                      if (CHECK_PRESS(20488, 1))
                        return v10;
                    }
                    if ((v3 & 2) != 0)
                    {
                      v10 = 1;
                      if (CHECK_TRIG(20488, 1))
                        return v10;
                    }
                    if ((v3 & 4) != 0)
                    {
                      v10 = 1;
                      if (CHECK_REP(20488, 1))
                        return v10;
                    }
                  }
                }
              }
            }
          }
        }
      }
      return 0;
    case 4160:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4160))
        return v10;
      v36 = wk;
      if (v36->battlemode == 1)
        return 0;
      v36 = wk;
      if (v36->r2ng)
        return 0;
      return RegistShortCutBtn();
    case 4166:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4166))
        return v10;
      if (wk->battlemode == 1)
        return 0;
      return shortCutBtnCHECK()
          && CHECK_TRIG2(28672);
    case 4167:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4167))
        return v10;
      if (wk->battlemode == 1)
        return 0;
      if ((v3 & 1) != 0 && CHECK_PRESS2(28672))
        return 1;
      if ((v3 & 2) != 0 && CHECK_TRIG2(28672))
        return 1;
      return (v3 & 4) != 0 && CHECK_REP2(28672);
    case 4168:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4168))
        return v10;
      if (wk->battlemode == 1)
        return 0;
      NewID = dds3PadGetNewID(28672);
      if (NewID == dds3PadGetNewID(4097))
        v43 = 4096;
      else
        v43 = 4097;
      if ((v3 & 1) != 0 && CHECK_PRESS2(v43))
        return 1;
      if ((v3 & 2) != 0 && CHECK_TRIG2(v43))
        return 1;
      return (v3 & 4) != 0 && CHECK_REP2(v43);
    case 4169:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4169))
        return v10;
      if (wk->battlemode == 1)
        return 0;
      return shortCutBtnCHECK();
    case 4170:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      if (wk->battlemode == 1)
        return 0;
      if (shortCutBtnCHECK())
        return 0;
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4170))
        return v10;
      v47 = sBtlGetPChara();
      if (v47 && (v47->vstatus & 0x8000) != 0 || CHECK_PRESS(20488, 1) || CHECK_PRESS(20489, 1))
      {
        return 0;
      }
      if (shortCutBtnCHECK())
        return 0;
      if ((v3 & 1) != 0 && CHECK_PRESS2(20481))
        return 1;
      if (((v3 & 2) == 0 || !CHECK_TRIG2(20481)) && ((v3 & 4) == 0 || !CHECK_REP2(20481)))
      {
        return 0;
      }
LABEL_496:
      result = 1;
      break;
    case 4174:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      if (wk->battlemode == 3)
        return 0;
      v49 = sBtlGetPChara();
      if (v49)
      {
        if ((v49->vstatus & 0x8000) != 0)
          return 0;
      }
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4174))
        return v10;
      return wk->battlemode != 1
          && !CHECK_PRESS(24587, 1)
          && CHECK_TRIG2(20485);
    case 4175:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      if (wk->battlemode == 3)
        return 0;
      v51 = sBtlGetPChara();
      if (v51)
      {
        if ((v51->vstatus & 0x8000) != 0)
          return 0;
      }
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4175))
        return v10;
      return wk->battlemode != 1
          && !CHECK_PRESS(24587, 1)
          && CHECK_TRIG2(20484);
    case 4176:
      if (wk->bIsNoMoveBad)
        return 0;
      if ((wk->status4 & 0x800000) != 0)
        return 0;
      v53 = sBtlGetPChara();
      if (v53)
      {
        if ((v53->vstatus & 0x8000) != 0)
          return 0;
      }
      v10 = 0;
      if (sbtlplayertblChkNG_TutoEtc(1, 0, 4176))
        return v10;
      return wk->battlemode != 1 && CHECK_TRIG2(20495);
    case 4177:
      return IsRaidouWazaKey(4177, 28674);
    case 4178:
      return IsRaidouWazaKey(4178, 28675);
    case 4179:
      return IsRaidouWazaKey(4179, 28673);
    case 4180:
      return Is2PressKey(4180, 28674, 28672);
    case 4181:
      return Is2PressKey(4181, 28675, 28673);
    case 4182:
      return IsTgtKey(4182, 24580);
    case 4183:
      return IsTgtKey(4183, 24583);
    case 4184:
      return IsTgtKey(4184, 24581);
    case 4185:
      return IsTgtKey(4185, 24582);
    default:
      return 0;
  }
  return result;
}

// 0x1f91120
static bool IsRaidouWazaKey(SDF_PADMAP key, SDF_PADMAP chk_key) {
  SBTLUNIT_WORK *PChara;

  if (wk->bIsNoMoveBad)
    return 0;
  if ((wk->status4 & 0x800000) != 0)
    return 0;
  PChara = sBtlGetPChara();
  if (PChara)
  {
    if ((PChara->vstatus & 0x8000) != 0)
      return 0;
  }
  if (!IsEnemyAllDead())
    return 0;
  if (!sbtlplayertblChkNG_TutoEtc(1, 0, key))
  {
    if (wk->battlemode != 1)
    {
      if (shortCutBtnCHECK())
      {
        if (wk->encountno != 40)
          return CHECK_TRIG2(chk_key);
        if (sBtlChkSceneEnemyLive())
          return CHECK_TRIG2(chk_key);
      }
    }
  }
  return 0;
}

// 0x1f91340
static bool Is2PressKey(SDF_PADMAP key, SDF_PADMAP chk_key1, SDF_PADMAP chk_key2) {
  SBTLUNIT_WORK *PChara;
  bool v14;

  if (wk->bIsNoMoveBad)
    return 0;
  if ((wk->status4 & 0x800000) != 0)
    return 0;
  PChara = sBtlGetPChara();
  if (PChara)
  {
    if ((PChara->vstatus & 0x8000) != 0)
      return 0;
  }
  if (!IsEnemyAllDead())
    return 0;
  if (sbtlplayertblChkNG_TutoEtc(1, 0, key))
    return 0;
  if (wk->battlemode == 1)
    return 0;
  (loc_1FBC960)(1, 0);
  if (CHECK_PRESS2(chk_key1) && CHECK_PRESS2(chk_key2))
  {
    v14 = 1;
  }
  else
  {
    v14 = 0;
  }
  (loc_1FBC960)(0, 0);
  return v14;
}

// 0x1f915a0
static bool IsTgtKey(SDF_PADMAP key, SDF_PADMAP chk_key) {
  if ((wk->status4 & 0x800000) != 0)
    return 0;
  if (sbtlplayertblChkNG_TutoEtc(1, 0, key))
    return 0;
  if (wk->battlemode == 1)
    return 0;
  if (!!shortCutBtnCHECK())
    return 0;
  if (!CHECK_TRIG2(chk_key))
    return 0;
  return CHECK_PRESS(24587, 1);
}

// 0x1f91750
static bool IsEnemyAllDead(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  bool v6;
  SBTLUNIT_WORK *pUnit;
  bool v8;

  if (!wk)
    return 0;
  if (wk->UnitMng)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      number = UnitMng->number;
      v6 = i < number;
      if (i >= number)
        return v6;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) == 0)
        continue;
      v8 = sBtlCheckExist(pUnit);
      if (!v8)
        continue;
      if (pUnit->actaiwk->mode != 9 && pUnit->mode != 4 && pUnit->para->now->hp > 0)
      {
        return v6;
      }
    }
  }
  return 0;
}

// 0x1f6f570
static void InitCameraLockOn(void) {
  SBATTLE_WORK *wk_local;

  wk_local = wk;
  *(u16 *)&wk_local->CameraLockOnNear = 0;
  *(u16 *)&wk_local->CameraGazeOff = 0;
  wk_local->CameraLockOn = 0;
  wk_local->CameraLockOnTgtID = -1;
  wk_local->CameraLockAutoNextWaitTime = 0.0;
  gOldTargetListID = -1;
  gOldCursor_targetUID = 0;
  g1StDone = 0;
  sBtlInitSurprise();
}

// 0x1f78280
static void Check_SupportAction_CameraLockOn(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  s32 battlemode;
  s32 encountno;
  s64 i;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 targetID;
  SBTLUNIT_LISTWORK *v13;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;
  SBATTLE_WORK *v17;
  SBATTLE_WORK *v19;
  SBATTLE_WORK *v21;
  SBTLUNIT_LISTWORK *v22;
  s32 playerID;
  SBATTLE_WORK *v25;
  s32 Surprise_ListID;
  SBATTLE_WORK *v31;
  u32 v34;
  SBATTLE_WORK *v38;
  s32 v39;
  SBTLUNIT_LISTWORK *v40;
  SBTLUNIT_WORK *v42;
  SBTLACTAI_WORK *actaiwk;

  v4 = wk;
  battlemode = (u16)v4->battlemode;
  v4->CameraReset = 0;
  if (battlemode == 1)
    return;
  encountno = v4->encountno;
  if (encountno == 40)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        goto LABEL_47;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) != 0 && (pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000) != 0)
      {
        v9 = wk;
        v9->bCameraGazeOff = 0;
        *(u32 *)&v9->bCameraTgtSelect1 = 0;
        *(u16 *)&v9->bCameraTgtSelectR = 0;
      }
    }
  }
  if (encountno == 34)
  {
LABEL_32:
    targetID = wk->actaiwk->targetID;
    if (targetID != -1)
    {
      targetID = wk->actaiwk->targetID;
      v13 = wk->UnitMng;
      v14 = sBtlSearchUnit_ID(v13, targetID);
      if (v14)
      {
        v15 = v14;
        if ((v14->side & 2) != 0 && (v14->vstatus & 0x10000) == 0)
        {
          if ((v14->status & 0x4000000) != 0)
            goto LABEL_44;
          if (!sBtlCheckDamageTarget(v15))
          {
LABEL_44:
            v17 = wk;
            v17->bCameraGazeOff = 0;
            *(u32 *)&v17->bCameraTgtSelect1 = 0;
            *(u16 *)&v17->bCameraTgtSelectR = 0;
          }
        }
      }
    }
    goto LABEL_47;
  }
  encountno = wk->encountno;
  if (encountno == 56)
    goto LABEL_32;
LABEL_47:
  v19 = wk;
  if (v19->enemy_zenmetu)
  {
    v19 = wk;
    if (v19->CameraGazeOff)
    {
      v21 = wk;
      v22 = v21->UnitMng;
      playerID = v21->playerID;
      if ((sBtlSearchUnit_ID(v22, playerID)->vstatus & 0x8000) != 0)
      {
        v25 = wk;
        v25->bCameraGazeOff = 0;
        *(u32 *)&v25->bCameraTgtSelect1 = 0;
        *(u16 *)&v25->bCameraTgtSelectR = 0;
      }
      goto LABEL_62;
    }
  }
LABEL_62:
  Surprise_ListID = sBtlGetSurprise_ListID(wk);
  if (Surprise_ListID != -1)
  {
    wk->actaiwk->targetID = Surprise_ListID;
    return;
  }
  v31 = wk;
  if (v31->bCameraTgtSelect1)
  {
    sBtlSetNextTarget(wk);
    sBtlResettgtCng();
    return;
  }
  v31 = wk;
  if (!v31->bCameraTgtSelect2)
  {
    v31 = wk;
    if (v31->bCameraGazeOff)
    {
      v31 = wk;
      if (v31->CameraGazeOff)
      {
        if (!v34)
        {
          v31 = wk;
        }
        v31->CameraGazeOff = 0;
        sBtlResetGazeOnOff();
        Cng();
        sBtlPlaySE(0x10061u);
        sBtlSetCameraLockOnTgtUpdate();
      }
      else
      {
        if (!v34)
        {
          v31 = wk;
        }
        v31->CameraGazeOff = 1;
        sBtlResetGazeOnOff();
        Cng3();
        sBtlPlaySE(0x10061u);
      }
    }
    v38 = wk;
    if (v38->CameraGazeOff)
    {
      sBtlSetGazeOffTarget(wk);
      return;
    }
    v39 = wk->actaiwk->targetID;
    if (v39 == -1)
      return;
    v40 = v38->UnitMng;
    v42 = sBtlSearchUnit_ID(v40, v39);
    if (!v42)
      return;
    if (v42->para->devilid == 314)
    {
      actaiwk = wk->actaiwk;
      actaiwk->targetID = sBtlGetFrontTarget(wk, 314);
    }
    return;
  }
  v31 = wk;
  if (v31->bCameraTgtSelectL)
  {
    sBtlSetNextTargetLR(wk, -1);
    goto LABEL_87;
  }
  v31 = wk;
  if (v31->bCameraTgtSelectR)
  {
    sBtlSetNextTargetLR(wk, 1);
    goto LABEL_112;
  }
  v31 = wk;
  if (v31->bCameraTgtSelectU)
  {
    sBtlSetNextTargetUD(wk, -1);
LABEL_87:
    wk->bCameraTgtSelectUse = 1;
    return;
  }
  v31 = wk;
  if (v31->bCameraTgtSelectD)
  {
    sBtlSetNextTargetUD(wk, 1);
LABEL_112:
    wk->bCameraTgtSelectUse = 1;
  }
}

// 0x1f93a00
void sBtlSetCameraLockOnTgtUpdate(void) {
  s32 PlayerID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v8;
  s32 targetID;
  s32 mode;
  _BOOL4 IsAction;
  SBTLACTAI_WORK *actaiwk;
  s32 v20;
  SBTLUNIT_LISTWORK *v22;
  SBTLUNIT_WORK *v23;
  s32 v24;
  s32 gOldTargetListID_local;
  SBTLUNIT_LISTWORK *v29;
  SBTLUNIT_WORK *v30;
  s32 v31;
  _BOOL4 v32;
  SBTLUNIT_WORK *v33;
  SBTLUNIT_LISTWORK *v36;
  s32 v37;
  bool v40;
  bool v41;
  s32 EnemyDeadTgtSelect1Score;
  s32 v47;
  SBTLACTION_WORK *v48;
  u32 v49;
  SBTLUNIT_LISTWORK *v54;
  SBTLUNIT_WORK *v55;
  bool v57;
  u32 v59;
  __int128 v60;
  s32 v61;
  SBTLUNIT_LISTWORK *v63;
  SBTLUNIT_WORK *v64;
  SBTLUNIT_WORK *v65;
  u32 status;
  s32 v67;
  s32 encountno;
  s32 UID;
  SBTLACTAI_WORK *v74;
  evtUnitHandle_t *hEveUnit;
  SBTLUNIT_WORK *v76;
  _BOOL4 v77;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  f32 x;
  f32 z;
  f32 v83;
  f32 v86;
  s32 v87;
  s64 i;
  float32x2_t *namespaze;
  f32 v92;
  f32 v93;
  f32 v94;
  SBTLACTAI_WORK *v96;
  s32 v98;
  s32 v100;
  s32 v101;
  s32 v102;
  _BOOL4 DeadEventDone;
  s32 devilid;
  f32 v105;
  f32 y;
  f32 v107;
  s32 v109;
  SBTLACTION_WORK *actwk;
  s32 use_skillid;
  f32 v113;
  f32 v114;
  f32 v115;
  s32 v116;
  sdfVector4_t v118;
  sdfVector4_t HelperPos;
  s32 v120;
  s32 v121;
  sdfVector3_t v122;
  sdfVector3_t v123;
  sdfVector3_t v124;

  *(u64 *)&HelperPos.x = 0;
  *(u64 *)&HelperPos.z = 0;
  *(u64 *)&v118.x = 0;
  *(u64 *)&v118.z = 0;
  PlayerID = sBtlGetPlayerID();
  UnitMng = wk->UnitMng;
  v8 = sBtlSearchUnit_ID(UnitMng, PlayerID);
  targetID = v8->actaiwk->targetID;
  if (wk->mode == 12)
    OffVisible();
  if ((wk->status & 0x400) != 0)
    return;
  if (sBtlIsEnemyLastDeadStop())
    goto LABEL_319;
  if (!IsSceanStop())
  {
    mode = wk->mode;
    if (mode != 5)
    {
      mode = wk->mode;
      if (mode != 6)
      {
        if (!sBtlCheckSetsuma())
        {
          if (!CheckHuumaMes())
          {
LABEL_319:
            if (wk->cmbSkl->bRun)
              return;
            sBtlUpdateAutoTaget(v8);
            if (wk->battlemode == 1)
              return;
            IsAction = IsAction(2);
            actaiwk = v8->actaiwk;
            v121 = IsAction;
            v20 = actaiwk->targetID;
            if (v20 == -1)
              goto LABEL_60;
            v22 = wk->UnitMng;
            v23 = sBtlSearchUnit_ID(v22, v20);
            if (v23)
            {
              actaiwk = v8->actaiwk;
              if (v23->mode <= 4)
                actaiwk->targetID = -1;
LABEL_60:
              v24 = actaiwk->targetID;
              gOldTargetListID_local = v24;
              if (v24 == v8->ListID)
              {
                if (wk->battlemode != 3)
                {
                  v120 = 0;
                  v31 = 0;
                  gOldTargetListID_local = -1;
                  v116 = 0;
                  v32 = 1;
                  goto LABEL_87;
                }
                gOldTargetListID_local = gOldTargetListID;
              }
              if (gOldTargetListID_local == -1)
              {
                v120 = 0;
                v31 = 0;
                v32 = 1;
                v116 = 0;
                goto LABEL_87;
              }
              v29 = wk->UnitMng;
              v30 = sBtlSearchUnit_ID(v29, gOldTargetListID_local);
              if (!v30)
              {
LABEL_77:
                v36 = wk->UnitMng;
                v37 = wk->playerID;
                if ((sBtlSearchUnit_ID(v36, v37)->vstatus & 0x8000) != 0)
                {
                  sBtlCancelGunLockOn();
                }
                v120 = 0;
                v31 = 0;
                gOldTargetListID_local = -1;
                v32 = 1;
                v116 = 1;
                goto LABEL_87;
              }
              v33 = v30;
              if ((v30->side & 2) == 0)
                goto LABEL_77;
              if ((v30->vstatus & 0x10000) == 0 && (v30->status & 0x4000000) == 0)
              {
                if (sBtlCheckDamageTarget(v33))
                {
                  v31 = 0;
                  v120 = 0;
                  v33->TgtCngDead_Cnt = 0;
                  v116 = 0;
                  v32 = gOldTargetListID_local == -1;
LABEL_132:
                  if (gOldTargetListID_local != -1)
                    goto LABEL_140;
LABEL_87:
                  v40 = ChkAllEnemySummon();
                  if (!v32)
                    goto LABEL_138;
                  v41 = v40;
                  if (sBtlGetMode() != 2)
                  {
LABEL_138:
                    if (gOldTargetListID_local == -1)
                    {
                      v57 = ChkAllDeath();
                      if (!v57 && !v116 && v31)
                      {
                        if (!v59)
                        SetTargetDead();
                        if (IsAction(5))
                          goto LABEL_224;
                        goto LABEL_152;
                      }
                      if (v59)
                        goto LABEL_222;
                      goto LABEL_221;
                    }
                    goto LABEL_139;
                  }
                  if (g1StDone)
                  {
                    if (v41)
                      goto LABEL_138;
                    EnemyDeadTgtSelect1Score = sBtlGetEnemyDeadTgtSelect1Score(v8);
                    if (EnemyDeadTgtSelect1Score == -1)
                    {
                      v47 = sBtlGetNearTarget_CameraLockOn3(v8);
LABEL_137:
                      gOldTargetListID_local = v47;
                      goto LABEL_138;
                    }
                  }
                  else
                  {
                    EnemyDeadTgtSelect1Score = sBtlGetNearTarget_CameraLockOn2(v8, 0);
                    if (EnemyDeadTgtSelect1Score == -1)
                    {
                      v47 = sBtlGetEnemyDeadTgtSelect1Score(v8);
                      goto LABEL_137;
                    }
                  }
                  gOldTargetListID_local = EnemyDeadTgtSelect1Score;
LABEL_139:
                  v116 = v31;
LABEL_140:
                  v54 = wk->UnitMng;
                  v55 = sBtlSearchUnit_ID(v54, gOldTargetListID_local);
                  if (!v55)
                    goto LABEL_219;
                  v65 = v55;
                  status = v55->actwk->status;
                  v67 = status == 40;
                  if ((v55->side & 2) != 0 && (v55->vstatus & 0x10000) == 0)
                  {
                    if (wk->encountno == 40)
                    {
                      if (status == 40)
                        v67 = 1;
                      else
                        v67 = (BYTE1(v65->status) >> 6) & 1;
                      v121 = 1;
                    }
                  }
                  if ((v65->side & 2) != 0 && (v65->vstatus & 0x10000) == 0)
                  {
                    encountno = wk->encountno;
                    if (encountno == 34)
                      goto LABEL_178;
                    encountno = wk->encountno;
                    if (encountno == 56)
                    {
LABEL_178:
                      UID = v65->UID;
                      if (gOldCursor_targetUID != UID)
                      {
                        gOldCursor_targetUID = UID;
                      }
                      v121 = 1;
                    }
                  }
                  if ((v65->side & 2) == 0 || !(v121 & 1 | (((v65->status >> 26) & 1) == 0)) || (v65->vstatus & 0x10000) != 0)
                  {
LABEL_219:
                    if (IsAction(5))
                      goto LABEL_223;
LABEL_222:
                    OffVisible();
LABEL_223:
                    if (IsAction(5))
                    {
LABEL_224:
                      *(u64 *)&v60 = 0;
                      v86 = 0.0;
                      v87 = 0;
                      for (i = 32; i != 416; i += 8)
                      {
                        namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + i))->_1.namespaze;
                        if (namespaze && (namespaze[104].n64_u8[0] & 2) != 0)
                        {
                          ++v87;
                          v86 = v86 + namespaze[20].n64_f32[1];
                          *(float32x2_t *)&v60 = vadd_f32(*(float32x2_t *)&v60, namespaze[21]);
                        }
                      }
                      v92 = (f32)(*(f32 *)&v60 / (f32)v87) + -230.0;
                      v93 = v86 / (f32)v87;
                      v94 = *((f32 *)&v60 + 1) / (f32)v87;
                      v122.x = v93;
                      v122.y = v92;
                      v122.z = v94;
                      OnVisible(v122);
                      sBtlSetCameraLockOnTgtPos(v93, v92, v94);
                      v96 = v8->actaiwk;
                      if (v96->targetID == -1)
                      {
                        v96->targetID = sBtlGetHpLowTarget(v8);
                      }
LABEL_245:
                      v98 = v8->actaiwk->targetID;
                      if (v98 != -1)
                      {
                        v98 = v8->actaiwk->targetID;
                        g1StDone = 1;
                        if (v98 != -1 && targetID != v98)
                        {
                          sBtlResetAutoTaget(v8, targetID);
                          v98 = v8->actaiwk->targetID;
                        }
                      }
                      gOldTargetListID = v98;
                      return;
                    }
LABEL_152:
                    v61 = v8->actaiwk->targetID;
                    if (v61 == -1)
                    {
                      OffVisible();
                      goto LABEL_215;
                    }
                    v63 = wk->UnitMng;
                    v64 = sBtlSearchUnit_ID(v63, v61);
                    if (!v64)
                      goto LABEL_215;
                    goto LABEL_202;
                    if (!v64)
                    {
LABEL_215:
                      sBtlSetCameraLockOnTgtNone();
                      goto LABEL_245;
                    }
LABEL_202:
                    v76 = v64;
                    if ((v64->side & 2) != 0 && v121 & 1 | (((v64->status >> 26) & 1) == 0) && (v64->vstatus & 0x10000) == 0)
                    {
                      v77 = sBtlCheckDamageTarget(v76);
                      if (((v121 | v77) & 1) != 0)
                      {
                        *(u64 *)&v118.x = 0;
                        *(u64 *)&v118.z = 0;
                        GetUnitHelperPos(v76, &v118);
                        major = v76->major;
                        minor = v76->minor;
                        VisualData = sBtlGetVisualData(major, minor);
                        x = v76->pos.x;
                        z = v76->pos.z;
                        v83 = v76->pos.y + (f32)(VisualData->nml->height * -0.5);
                        sBtlSetCameraLockOnTgtPos(x, v83, z);
                        goto LABEL_245;
                      }
                    }
                    goto LABEL_215;
LABEL_221:
                    goto LABEL_222;
                  }
                  if (((v121 | sBtlCheckDamageTarget(v65)) & 1) == 0)
                  {
                    v121 = 0;
                    goto LABEL_219;
                  }
                  v74 = v8->actaiwk;
                  if (v74->targetID != gOldTargetListID_local)
                    v74->targetID = gOldTargetListID_local;
                  hEveUnit = v65->hEveUnit;
                  *(u64 *)&HelperPos.x = 0;
                  *(u64 *)&HelperPos.z = 0;
                  if (hEveUnit)
                  {
                    sBtlGetUnitTargetPos(v65, &HelperPos);
                    goto LABEL_282;
                  }
                  devilid = (u16)v65->para->devilid;
                  if (v65->para->devilid <= 260)
                  {
                    if (devilid != 258)
                    {
LABEL_276:
                      GetUnitHelperPos(v65, &HelperPos);
                      goto LABEL_282;
                    }
                  }
                  else if (devilid != 314)
                  {
                    goto LABEL_276;
                  }
                  GetUnitHelperPos(v65, &HelperPos);
                  HelperPos.x = v8->pos.x;
LABEL_282:
                  if (v67)
                  {
LABEL_283:
                    OffVisible();
                    goto LABEL_291;
                  }
                  if (v24 == -1 || v65->para->devilid == 314)
                    goto LABEL_288;
                  if (v120)
                    goto LABEL_283;
                  if (gOldCursor_targetUID == v65->UID)
                  {
                    if (v116)
                    {
                      SetTargetDead();
                    }
                    else
                    {
                      actwk = v65->actwk;
                      if (actwk->status != 40 || (use_skillid = actwk->use_skillid, (u32)(use_skillid - 481) <= 2))
                      {
LABEL_288:
                        v105 = HelperPos.x;
                        y = HelperPos.y;
                        v107 = HelperPos.z;
                        v123.x = v105;
                        v123.y = y;
                        v123.z = v107;
                        OnVisible(v123);
                        goto LABEL_291;
                      }
                      if (use_skillid == 484 && actwk->framecnt >= 190)
                        goto LABEL_283;
                      v113 = HelperPos.x;
                      v114 = HelperPos.y;
                      v115 = HelperPos.z;
                      v124.x = v113;
                      v124.y = v114;
                      v124.z = v115;
                      SetTargetDeadSkill(v124);
                    }
                  }
                  else
                  {
                    if (wk->CameraGazeOff)
                      goto LABEL_291;
                    Cng();
                  }
LABEL_291:
                  v109 = v65->UID;
                  gOldCursor_targetUID = v109;
                  if (IsAction(5))
                    goto LABEL_224;
                  goto LABEL_152;
                }
              }
              v48 = v33->actwk;
              v49 = v48->status;
              if (v49 == 40)
              {
                if (v48->use_skillid != 492)
                  goto LABEL_123;
              }
              else if (v49 == 41 && (v33->vstatus & 0x10000) == 0)
              {
                goto LABEL_123;
              }
              if ((v33->aiwk->scrflag & 8) == 0 && !IsAction(6))
              {
                if ((v33->side & 2) == 0 || (v33->vstatus & 0x10000) != 0)
                  goto LABEL_266;
                v100 = wk->encountno;
                if (v100 == 34)
                  goto LABEL_265;
                v100 = wk->encountno;
                if (v100 == 56)
                {
LABEL_265:
                  v31 = 0;
                  v120 = 1;
                  v121 = 1;
                }
                else
                {
LABEL_266:
                  v101 = 30;
                  v102 = v33->TgtCngDead_Cnt + 1;
                  DeadEventDone = v33->DeadEventDone;
                  v33->TgtCngDead_Cnt = v102;
                  if (DeadEventDone)
                  {
                    if (v33->actwk->use_skillid == 492)
                      v101 = 30;
                    else
                      v101 = 60;
                  }
                  v31 = 1;
                  v120 = 0;
                  if (v102 > v101)
                    gOldTargetListID_local = -1;
                }
LABEL_124:
                if (sBtlCheckGunMode())
                {
                  sBtlCancelGunLockOn();
                  v116 = 0;
                  v32 = gOldTargetListID_local == -1;
                  if ((v31 & 1) != 0)
                    goto LABEL_87;
                  goto LABEL_132;
                }
                v116 = 0;
                v32 = gOldTargetListID_local == -1;
                if ((v31 & 1) != 0)
                  goto LABEL_87;
                goto LABEL_132;
              }
LABEL_123:
              v31 = 0;
              v120 = 0;
              v121 = 1;
              goto LABEL_124;
            }
            actaiwk = v8->actaiwk;
            goto LABEL_60;
          }
        }
      }
    }
  }
}

// 0x1f96560
static bool ChkAllDeath(void) {
  s64 v3;
  char *namespaze;

  if (sBtlCheckGeneratorAll())
    return 0;
  if (!!sBtlCheckGenerator_ND())
    return 0;
  v3 = 32;
  do
  {
    namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + v3))->_1.namespaze;
    if (namespaze && (namespaze[832] & 2) != 0)
    {
      if (sBtlCheckLiveTarget2(namespaze))
        return 0;
    }
    v3 += 8;
  }
  while (v3 != 416);
  return 1;
}

// 0x1f957b0
static bool ChkAllEnemySummon(void) {
  char v2;
  s64 i;
  const char *namespaze;
  const char *v6;

  v2 = 0;
  for (i = 32; i != 416; i += 8)
  {
    namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + i))->_1.namespaze;
    if (namespaze && (namespaze[832] & 2) != 0 && !namespaze[2045])
      v2 |= *((u32 *)namespaze + 93) < 5;
  }
  return v2 & 1;
}

// 0x1f91de0
bool sBtlSetNextTarget(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *v6;
  SBATTLE_WORK *v7;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLCAMERA_WORK *camera;
  s32 targetID;
  f32 x;
  f32 z;
  SBTLUNIT_WORK *v13;
  f32 v15;
  f32 v16;
  f32 PosToDir;
  SBATTLE_WORK *v19;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  s64 v22;
  SBTLUNIT_LISTWORK *v27;
  u32 v28;
  SBTLUNIT_WORK *pUnit;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 AtoB_LR;
  f32 v35;
  SBTLUNIT_LISTWORK *p_other_List2;
  s32 v40;
  s64 v41;
  s32 v43;
  s64 v44;
  SBTLUNIT_LISTWORK *v46;
  s32 v47;
  SBTLUNIT_WORK *v48;
  s32 CameraTgtSelect1Score;
  s32 v51;
  SBTLUNIT_LISTWORK *v53;
  SBTLUNIT_WORK *v54;
  s64 v55;
  SBTLUNIT_LISTWORK *v56;
  s32 v57;
  SBTLUNIT_WORK *v58;
  s64 v59;
  SBTLUNIT_LISTWORK *v60;
  s32 v61;
  SBTLUNIT_WORK *v62;
  SBTLUNIT_WORK *v63;
  s32 v66;
  SBATTLE_WORK *v68;
  SBATTLE_WORK *v72;
  SBTLUNIT_LISTWORK *v73;
  SBTLUNIT_WORK *v74;
  s32 UID;
  SBTLUNIT_WORK *v78;

  if (wk->actaiwk->targetID != -1)
  {
    other_List2 = wk->other_List2;
    if (!other_List2)
    {
LABEL_10:
      v7 = wk;
      UnitMng = v7->UnitMng;
      camera = v7->scene->camera;
      targetID = wk->actaiwk->targetID;
      x = camera->camerapos.x;
      z = camera->camerapos.z;
      v13 = sBtlSearchUnit_ID(UnitMng, targetID);
      if (v13)
      {
        v15 = v13->pos.x;
        v16 = v13->pos.z;
        goto LABEL_17;
      }
      else
      {
        v15 = wk->pos.x;
        v16 = wk->pos.z;
LABEL_17:
        PosToDir = sBtlGetPosToDir(x, z, v15, v16);
        v19 = wk;
LABEL_19:
        TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
        v19->other_List2 = TargetList_MASK;
        v22 = 0;
        *(u64 *)&gSelectTarget_SortNum = 0;
        while (1)
        {
          v27 = wk->other_List2;
          if (v22 >= v27->count)
          {
            {
              sBtlDeleteUnitList(v27, 0);
              p_other_List2 = &wk->other_List2;
              p_other_List2 = 0;
            }
            if (gSelectTarget_SortNum < 2)
              goto LABEL_158;
            v41 = 0;
            while (2)
            {
              if (v41 >= gSelectTarget_SortNum)
              {
                if (wk->bCameraTgtSelect1Cnt)
                  goto LABEL_72;
                v59 = 0;
                while (2)
                {
                  if (v59 >= gSelectTarget_SortNum)
                  {
LABEL_87:
                    CameraTgtSelect1Score = sBtlGetCameraTgtSelect1Score(wk);
                    if (CameraTgtSelect1Score == -1)
                      goto LABEL_158;
                    v66 = CameraTgtSelect1Score;
                    v68 = wk;
                    v68->CameraLockOnTgtID = v66;
                    Cng();
                    wk->actaiwk->targetID = v66;
                    v72 = wk;
                    v72->CameraLockAutoNextOn = 0;
                    v72->CameraLockAutoNextWaitTime = 0.0;
                    v72->bCameraTgtSelect1Cnt = 60;
                    v73 = v72->UnitMng;
                    v74 = sBtlSearchUnit_ID(v73, v66);
                    if (v74)
                    {
                      UID = v74->UID;
                      v74->DoneCameraTgtSelect1 = 1;
                      gOldCursor_targetUID = UID;
                    }
                    sBtlPlaySE(0x10061u);
                    if ((wk->vstatus & 0x8000) != 0)
                      sBtlCancelGunLockOn();
                    sBtlResettgtCng();
LABEL_148:
                    LOBYTE(v54) = 1;
                    return (char)v54;
                  }
                  v60 = wk->UnitMng;
                  v61 = gSelectTarget_SortListID[v59];
                  v62 = sBtlSearchUnit_ID(v60, v61);
                  if (!v62)
                    goto LABEL_119;
                  goto LABEL_9001;
                  if (!v62)
                  {
LABEL_119:
                    ++v59;
                    continue;
                  }
LABEL_9001:
                  break;
                }
                v63 = v62;
                v63->DoneCameraTgtSelect1 = v59 == gSelectTarget_SortNowIdx;
                goto LABEL_119;
LABEL_72:
                v44 = 0;
                while (2)
                {
                  if (v44 < gSelectTarget_SortNum)
                  {
                    v46 = wk->UnitMng;
                    v47 = gSelectTarget_SortListID[v44];
                    v48 = sBtlSearchUnit_ID(v46, v47);
                    if (!v48)
                      goto LABEL_73;
                    goto LABEL_9002;
                    if (!v48)
                    {
LABEL_73:
                      ++v44;
                      continue;
                    }
LABEL_9002:
                    if (!v48->DoneCameraTgtSelect1)
                    {
                      goto LABEL_87;
                    }
                    goto LABEL_73;
                  }
                  break;
                }
                v55 = 0;
                while (2)
                {
                  if (v55 >= gSelectTarget_SortNum)
                    goto LABEL_87;
                  v56 = wk->UnitMng;
                  v57 = gSelectTarget_SortListID[v55];
                  v58 = sBtlSearchUnit_ID(v56, v57);
                  if (v58)
                  {
                    if (v55 != gSelectTarget_SortNowIdx)
                      v58->DoneCameraTgtSelect1 = 0;
                  }
                  ++v55;
                  continue;
                }
              }
              v43 = wk->actaiwk->targetID;
              if (v43 == gSelectTarget_SortListID[v41])
              {
                gSelectTarget_SortNowIdx = v41;
              }
              ++v41;
              continue;
            }
          }
          if (v28)
          {
            pUnit = v27->pUnitL[v22]->pUnit;
            if (!pUnit)
              goto LABEL_23;
          }
          else
          {
            pUnit = wk->other_List2->pUnitL[v22]->pUnit;
            if (!pUnit)
              goto LABEL_23;
          }
          if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
            goto LABEL_23;
          if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0)
          {
            v30 = pUnit->pos.x;
            v31 = pUnit->pos.z;
            v32 = sBtlGetPosToDir(x, z, v30, v31);
            AtoB_LR = sBtlGetAtoB_LR(PosToDir, v32);
            v35 = AtoB_LR;
            gSelectTarget_SortListID[gSelectTarget_SortNum] = pUnit->ListID;
            gSelectTarget_SortNum = gSelectTarget_SortNum + 1;
            gSelectTarget_SortLR[gSelectTarget_SortNum] = v35;
          }
LABEL_23:
          ++v22;
        }
        goto LABEL_19;
      }
      goto LABEL_17;
    }
    sBtlDeleteUnitList(other_List2, 0);
    v6 = &wk->other_List2;
    v6 = 0;
    goto LABEL_10;
  }
  v40 = sBtlGetNearTarget_CameraLockOn3(wk);
  if (v40 == -1)
    goto LABEL_158;
  v51 = v40;
  v53 = wk->UnitMng;
  v54 = sBtlSearchUnit_ID(v53, v51);
  if (!v54)
    return (char)v54;
  v78 = v54;
  if ((v54->side & 2) != 0 && (v54->status & 0x4000000) == 0 && (v54->vstatus & 0x10000) == 0)
  {
    if (sBtlCheckDamageTarget(v78))
    {
      wk->actaiwk->targetID = v51;
      goto LABEL_148;
    }
  }
LABEL_158:
  LOBYTE(v54) = 0;
  return (char)v54;
}

// 0x1f93240
bool sBtlSetNextTargetUD(SBTLUNIT_WORK *wk, s32 _UD) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *v8;
  SBATTLE_WORK *v11;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  s64 v14;
  SBTLUNIT_LISTWORK *v18;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 z;
  f32 v23;
  f32 v24;
  f32 LenXZ;
  f32 v27;
  SBTLUNIT_LISTWORK *p_other_List2;
  s32 v31;
  s64 v32;
  s64 i;
  s64 v35;
  s64 j;
  s64 v38;
  s32 *gSelectTarget_SortListID_local;
  f32 *gSelectTarget_SortLen_local;
  s64 v41;
  s64 v42;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v46;
  s32 v48;
  SBTLUNIT_LISTWORK *v50;
  SBTLUNIT_WORK *v51;
  SBATTLE_WORK *v53;
  SBATTLE_WORK *v57;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v59;
  s32 UID;
  SBTLUNIT_WORK *v63;

  if (wk->actaiwk->targetID != -1)
  {
    other_List2 = wk->other_List2;
    if (!other_List2)
    {
LABEL_10:
      v11 = wk;
LABEL_12:
      TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
      v11->other_List2 = TargetList_MASK;
      v14 = 0;
      *(u64 *)&gSelectTarget_SortNum = 0;
      while (1)
      {
        v18 = wk->other_List2;
        if (v14 >= v18->count)
        {
          {
            sBtlDeleteUnitList(v18, 0);
            p_other_List2 = &wk->other_List2;
            p_other_List2 = 0;
          }
          if (gSelectTarget_SortNum >= 2)
            goto LABEL_49;
LABEL_108:
          LOBYTE(v51) = 0;
          return (char)v51;
LABEL_49:
          v32 = 0;
          for (i = 9; ; ++i)
          {
            v35 = gSelectTarget_SortNum - 1;
            if (v32 >= v35)
              break;
            for (j = i; ; ++j)
            {
              if (gSelectTarget_SortNum <= (s32)j - 8)
                break;
              if (gSelectTarget_SortLen[v32] > *((f32 *)&gSelectTarget_SortLen->obj.klass + j))
              {
                v38 = 4 * j;
                gSelectTarget_SortListID_local = gSelectTarget_SortListID;
                gSelectTarget_SortLen_local = gSelectTarget_SortLen;
                v41 = (s64)gSelectTarget_SortListID_local + 4 * v32;
                v42 = (s64)gSelectTarget_SortLen_local + 4 * v32;
                v43 = *((u32 *)&gSelectTarget_SortLen_local->obj.klass + j);
                v44 = *(u32 *)(v42 + 32);
                v45 = *(u32 *)(v41 + 32);
                *(u32 *)(v41 + 32) = *((u32 *)&gSelectTarget_SortListID_local->obj.klass + j);
                *(u32 *)((char *)&gSelectTarget_SortListID_local->obj.klass + v38) = v45;
                *(u32 *)(v42 + 32) = v43;
                *(u32 *)((char *)&gSelectTarget_SortLen_local->obj.klass + v38) = v44;
              }
            }
            ++v32;
          }
          if (UD == 1)
          {
            v46 = gSelectTarget_SortListID[0];
            if (v46 == -1 || wk->actaiwk->targetID == v46)
              goto LABEL_108;
          }
          else
          {
            if (UD != -1)
              goto LABEL_108;
            v35 = gSelectTarget_SortNum - 1;
            v46 = gSelectTarget_SortListID[v35];
            if (v46 == -1 || wk->actaiwk->targetID == v46)
              goto LABEL_108;
          }
          v53 = wk;
          v53->CameraLockOnTgtID = v46;
          Cng();
          wk->actaiwk->targetID = v46;
          v57 = wk;
          v57->CameraLockAutoNextOn = 0;
          v57->CameraLockAutoNextWaitTime = 0.0;
          UnitMng = v57->UnitMng;
          v59 = sBtlSearchUnit_ID(UnitMng, v46);
          if (v59)
          {
            UID = v59->UID;
            gOldCursor_targetUID = UID;
          }
          sBtlPlaySE(0x10061u);
          if ((wk->vstatus & 0x8000) != 0)
            sBtlCancelGunLockOn();
          sBtlResettgtCng();
          LOBYTE(v51) = 1;
          return (char)v51;
        }
        pUnit = v18->pUnitL[v14]->pUnit;
        if (!pUnit)
          goto LABEL_16;
        if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
          goto LABEL_16;
        if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0)
        {
          x = wk->pos.x;
          z = wk->pos.z;
          v23 = pUnit->pos.x;
          v24 = pUnit->pos.z;
          LenXZ = sBtlGetLenXZ(x, z, v23, v24);
          v27 = LenXZ;
          gSelectTarget_SortListID[gSelectTarget_SortNum] = pUnit->ListID;
          gSelectTarget_SortLen[gSelectTarget_SortNum] = v27;
          gSelectTarget_SortNum = gSelectTarget_SortNum + 1;
        }
LABEL_16:
        ++v14;
      }
      goto LABEL_12;
    }
    sBtlDeleteUnitList(other_List2, 0);
    v8 = &wk->other_List2;
    v8 = 0;
    goto LABEL_10;
  }
  v31 = sBtlGetNearTarget_CameraLockOn3(wk);
  if (v31 == -1)
    goto LABEL_108;
  v48 = v31;
  v50 = wk->UnitMng;
  v51 = sBtlSearchUnit_ID(v50, v48);
  if (!v51)
    return (char)v51;
  v63 = v51;
  if ((v51->side & 2) == 0 || (v51->status & 0x4000000) != 0 || (v51->vstatus & 0x10000) != 0)
    goto LABEL_108;
  if (!sBtlCheckDamageTarget(v63))
    goto LABEL_108;
  wk->actaiwk->targetID = v48;
  LOBYTE(v51) = 0;
  return (char)v51;
}

// 0x1f928c0
bool sBtlSetNextTargetLR(SBTLUNIT_WORK *wk, s32 _LR) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *v10;
  SBTLCAMERA_WORK *camera;
  s32 targetID;
  f32 x;
  f32 z;
  SBTLUNIT_WORK *v15;
  f32 v17;
  f32 v18;
  f32 PosToDir;
  SBATTLE_WORK *v21;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  s64 v24;
  SBTLUNIT_LISTWORK *v29;
  u32 v30;
  SBTLUNIT_WORK *pUnit;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 AtoB_LR;
  f32 v37;
  SBTLUNIT_LISTWORK *v39;
  s32 v41;
  s64 v42;
  s64 i;
  s64 j;
  s64 v46;
  f32 *v47;
  s32 *gSelectTarget_SortListID_local;
  s64 v49;
  s64 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s64 v54;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v60;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v63;
  s32 v64;
  SBATTLE_WORK *v66;
  SBATTLE_WORK *v70;
  SBTLUNIT_LISTWORK *v71;
  SBTLUNIT_WORK *v72;
  s32 UID;
  SBTLUNIT_WORK *v76;

  if (wk->actaiwk->targetID == -1)
  {
    v41 = sBtlGetNearTarget_CameraLockOn3(wk);
    if (v41 == -1)
      goto LABEL_141;
    v60 = v41;
    UnitMng = wk->UnitMng;
    v63 = sBtlSearchUnit_ID(UnitMng, v60);
    if (!v63)
      return (char)v63;
    v76 = v63;
    if ((v63->side & 2) != 0 && (v63->status & 0x4000000) == 0 && (v63->vstatus & 0x10000) == 0)
    {
      if (sBtlCheckDamageTarget(v76))
      {
        wk->actaiwk->targetID = v60;
        LOBYTE(v63) = 0;
        return (char)v63;
      }
    }
LABEL_141:
    LOBYTE(v63) = 0;
    return (char)v63;
  }
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
    goto LABEL_10;
  }
LABEL_10:
  v9 = wk;
  v10 = v9->UnitMng;
  camera = v9->scene->camera;
  targetID = wk->actaiwk->targetID;
  x = camera->camerapos.x;
  z = camera->camerapos.z;
  v15 = sBtlSearchUnit_ID(v10, targetID);
  if (v15)
  {
    v17 = v15->pos.x;
    v18 = v15->pos.z;
    goto LABEL_17;
  }
  v17 = wk->pos.x;
  v18 = wk->pos.z;
LABEL_17:
  PosToDir = sBtlGetPosToDir(x, z, v17, v18);
  v21 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v21->other_List2 = TargetList_MASK;
  v24 = 0;
  *(u64 *)&gSelectTarget_SortNum = 0;
  while (1)
  {
    v29 = wk->other_List2;
    if (v24 >= v29->count)
      break;
    if (v30)
    {
      pUnit = v29->pUnitL[v24]->pUnit;
      if (!pUnit)
        goto LABEL_23;
    }
    else
    {
      pUnit = wk->other_List2->pUnitL[v24]->pUnit;
      if (!pUnit)
        goto LABEL_23;
    }
    if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
      goto LABEL_23;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0)
    {
      v32 = pUnit->pos.x;
      v33 = pUnit->pos.z;
      v34 = sBtlGetPosToDir(x, z, v32, v33);
      AtoB_LR = sBtlGetAtoB_LR(PosToDir, v34);
      v37 = AtoB_LR;
      gSelectTarget_SortListID[gSelectTarget_SortNum] = pUnit->ListID;
      gSelectTarget_SortNum = gSelectTarget_SortNum + 1;
      gSelectTarget_SortLR[gSelectTarget_SortNum] = v37;
    }
LABEL_23:
    ++v24;
  }
  {
    sBtlDeleteUnitList(v29, 0);
    v39 = &wk->other_List2;
    v39 = 0;
  }
  if (gSelectTarget_SortNum < 2)
    goto LABEL_141;
  v42 = 0;
  for (i = 9; ; ++i)
  {
    if (v42 >= gSelectTarget_SortNum - 1)
      break;
    for (j = i; ; ++j)
    {
      if (gSelectTarget_SortNum <= (s32)j - 8)
        break;
      if (gSelectTarget_SortLR[v42] > *((f32 *)&gSelectTarget_SortLR->obj.klass + j))
      {
        v46 = 4 * j;
        gSelectTarget_SortListID_local = gSelectTarget_SortListID;
        v47 = gSelectTarget_SortLR;
        v49 = (s64)gSelectTarget_SortListID_local + 4 * v42;
        v50 = (s64)v47 + 4 * v42;
        v51 = *((u32 *)&v47->obj.klass + j);
        v52 = *(u32 *)(v50 + 32);
        v53 = *(u32 *)(v49 + 32);
        *(u32 *)(v49 + 32) = *((u32 *)&gSelectTarget_SortListID_local->obj.klass + j);
        *(u32 *)((char *)&gSelectTarget_SortListID_local->obj.klass + v46) = v53;
        *(u32 *)(v50 + 32) = v51;
        *(u32 *)((char *)&v47->obj.klass + v46) = v52;
      }
    }
    ++v42;
  }
  v54 = 0;
  while (2)
  {
    if (v54 < gSelectTarget_SortNum)
    {
      v56 = wk->actaiwk->targetID;
      if (v56 == gSelectTarget_SortListID[v54])
      {
        gSelectTarget_SortNowIdx = v54;
      }
      ++v54;
      continue;
    }
    break;
  }
  if (LR == 1)
  {
    v64 = gSelectTarget_SortNowIdx + 1;
    if (v64 >= 0)
    {
      if (v64 < gSelectTarget_SortNum)
      {
        gSelectTarget_SortNowIdx = v64;
        v58 = gSelectTarget_SortListID[v64];
        if (v58 != -1 && wk->actaiwk->targetID != v58)
          goto LABEL_118;
      }
    }
    goto LABEL_141;
  }
  if (LR != -1)
    goto LABEL_141;
  v57 = gSelectTarget_SortNowIdx - 1;
  if (v57 < 0)
    goto LABEL_141;
  if (v57 >= gSelectTarget_SortNum)
    goto LABEL_141;
  gSelectTarget_SortNowIdx = v57;
  v58 = gSelectTarget_SortListID[v57];
  if (v58 == -1 || wk->actaiwk->targetID == v58)
    goto LABEL_141;
LABEL_118:
  v66 = wk;
  v66->CameraLockOnTgtID = v58;
  Cng();
  wk->actaiwk->targetID = v58;
  v70 = wk;
  v70->CameraLockAutoNextOn = 0;
  v70->CameraLockAutoNextWaitTime = 0.0;
  v71 = v70->UnitMng;
  v72 = sBtlSearchUnit_ID(v71, v58);
  if (v72)
  {
    UID = v72->UID;
    gOldCursor_targetUID = UID;
  }
  sBtlPlaySE(0x10061u);
  if ((wk->vstatus & 0x8000) != 0)
    sBtlCancelGunLockOn();
  sBtlResettgtCng();
  LOBYTE(v63) = 1;
  return (char)v63;
}

// 0x1f94be0
bool sBtlSetGazeOffTarget(SBTLUNIT_WORK *wk) {
  s32 v4;
  SBTLACTAI_WORK *actaiwk;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v9;
  s32 v10;
  s32 v12;
  SBATTLE_WORK *v14;
  f32 x;
  f32 y;
  f32 z;
  s32 CameraTgtSelect1Score;
  s32 v21;
  SBATTLE_WORK *v23;
  SBTLUNIT_WORK *v26;
  SBTLUNIT_LISTWORK *v29;
  SBTLUNIT_WORK *v30;
  unsigned __int128 v32;

  if ((wk->vstatus & 0x8000) != 0)
  {
    actaiwk = wk->actaiwk;
    v32 = 0u;
    targetID = actaiwk->targetID;
    if (targetID != -1)
    {
      targetID = wk->actaiwk->targetID;
      UnitMng = wk->UnitMng;
      v9 = sBtlSearchUnit_ID(UnitMng, targetID);
      if (!v9)
        goto LABEL_29;
      x = v9->pos.x;
      y = v9->pos.y;
      z = v9->pos.z;
      if (sBtlChangeWorldtoScreenUnity3(x, y, z, &v32))
        goto LABEL_54;
      goto LABEL_29;
    }
LABEL_29:
    CameraTgtSelect1Score = sBtlGetCameraTgtSelect1Score(wk);
    if (CameraTgtSelect1Score == -1)
      goto LABEL_54;
    v21 = CameraTgtSelect1Score;
    if (wk->actaiwk->targetID != CameraTgtSelect1Score)
    {
      v23 = wk;
      v23->CameraLockOnTgtID = v21;
      Cng2();
      wk->actaiwk->targetID = v21;
      sBtlCancelGunLockOn();
      goto LABEL_41;
    }
    goto LABEL_54;
  }
  if (wk->actaiwk->targetID != -1)
  {
    v4 = sBtlGetCameraTgtSelect1Score(wk);
    if (v4 == -1)
      goto LABEL_54;
    v12 = v4;
    if (wk->actaiwk->targetID != v4)
    {
      v14 = wk;
      v14->CameraLockOnTgtID = v12;
      Cng2();
LABEL_24:
      wk->actaiwk->targetID = v12;
LABEL_41:
      LOBYTE(v26) = 1;
      return (char)v26;
    }
LABEL_54:
    LOBYTE(v26) = 0;
    return (char)v26;
  }
  v10 = sBtlGetNearTarget_CameraLockOn3(wk);
  if (v10 == -1)
    goto LABEL_54;
  v12 = v10;
  v29 = wk->UnitMng;
  v26 = sBtlSearchUnit_ID(v29, v12);
  if (v26)
  {
    v30 = v26;
    if ((v26->side & 2) == 0 || (v26->status & 0x4000000) != 0 || (v26->vstatus & 0x10000) != 0)
      goto LABEL_54;
    if (!sBtlCheckDamageTarget(v30))
      goto LABEL_54;
    goto LABEL_24;
  }
  return (char)v26;
}

// 0x1f96d50
bool sBtlSetNextTarget_RS(SBTLUNIT_WORK *wk) {
  s32 EnemyDeadTgtSelect1Score;

  if (wk->actaiwk->targetID != -1)
    return 1;
  EnemyDeadTgtSelect1Score = sBtlGetEnemyDeadTgtSelect1Score(wk);
  if (EnemyDeadTgtSelect1Score == -1)
    goto LABEL_8;
LABEL_10:
  wk->actaiwk->targetID = EnemyDeadTgtSelect1Score;
  return 1;
LABEL_8:
  EnemyDeadTgtSelect1Score = sBtlGetNearTarget_CameraLockOn3(wk);
  if (EnemyDeadTgtSelect1Score != -1)
    goto LABEL_10;
  return 0;
}

// 0x1f96e30
bool sBtlSetNextTarget_Setsuma(SBTLUNIT_WORK *wk) {
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 EnemyDeadTgtSelect1Score;

  targetID = wk->actaiwk->targetID;
  if (targetID == -1)
  {
    EnemyDeadTgtSelect1Score = sBtlGetEnemyDeadTgtSelect1Score(wk);
    if (EnemyDeadTgtSelect1Score != -1)
      goto LABEL_22;
    goto LABEL_21;
  }
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (sBtlCheckLiveTarget2(v6))
    return 1;
  EnemyDeadTgtSelect1Score = sBtlGetEnemyDeadTgtSelect1Score(wk);
  if (EnemyDeadTgtSelect1Score != -1)
    goto LABEL_22;
  EnemyDeadTgtSelect1Score = sBtlGetNearTarget_CameraLockOn3(wk);
  if (EnemyDeadTgtSelect1Score == -1)
    return 0;
LABEL_22:
  wk->actaiwk->targetID = EnemyDeadTgtSelect1Score;
  return 1;
LABEL_21:
  EnemyDeadTgtSelect1Score = sBtlGetNearTarget_CameraLockOn3(wk);
  if (EnemyDeadTgtSelect1Score != -1)
    goto LABEL_22;
  return 0;
}

// 0x1f91940
void sBtlInitSurprise(void) {
  s64 v2;
  char *v3;

  v2 = 0;
  gSurpriseTarget_SortNum = 0;
  while (1)
  {
    if (v2 >= SLODWORD(gSurpriseTarget_SortListID->max_length))
      break;
    v3 = (char *)gSurpriseTarget_SortListID + 4 * v2++;
    *((u32 *)v3 + 8) = 0;
  }
}

// 0x1f97000
void sBtlAddSurprise(SBTLUNIT_WORK *wkEnemy) {
  s32 devilid;
  char *v4;
  Il2CppObject *v5;

  if (wkEnemy && (wkEnemy->side & 2) != 0)
  {
    devilid = wkEnemy->para->devilid;
    v4 = sdatDevilName(devilid, 0);
    v5 = Concat_54766928("シンボル攻撃で弱点付着の1件登録 : ", v4, 0);
    Log(v5);
    gSurpriseTarget_SortListID[gSurpriseTarget_SortNum++] = wkEnemy->ListID;
  }
}

// 0x1f91ab0
s32 sBtlGetSurprise_ListID(SBTLUNIT_WORK *wkPlayer) {
  s32 ListID;
  s64 v6;
  f32 v7;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v11;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v13;
  f32 x;
  f32 z;
  f32 v16;
  f32 v17;
  f32 v18;
  char *v19;
  Il2CppObject *v20;
  s32 v22;

  ListID = -1;
  if (!gSurpriseTarget_SortNum)
    return ListID;
  if (wk->bCameraGazeOff)
  {
    gSurpriseTarget_SortNum = 0;
    return ListID;
  }
  v22 = -1;
  v6 = 0;
  v7 = 9999.0;
  while (1)
  {
    if (v6 >= gSurpriseTarget_SortNum)
      break;
    UnitMng = wk->UnitMng;
    v11 = gSurpriseTarget_SortListID[v6];
    v12 = sBtlSearchUnit_ID(UnitMng, v11);
    if (v12)
    {
      v13 = v12;
      x = v12->pos.x;
      z = v12->pos.z;
      v16 = wkPlayer->pos.x;
      v17 = wkPlayer->pos.z;
      v18 = sBtlGetLenXZ(v16, v17, x, z) - v13->actaiwk->hit_area_r;
      if (v18 < v7)
      {
        ListID = v13->ListID;
        v7 = v18;
        v22 = ListID;
      }
    }
    ++v6;
  }
  gSurpriseTarget_SortNum = 0;
  if (ListID != -1)
  {
    v19 = ToString((s32)&v22, 0);
    v20 = Concat_54766928("シンボル攻撃で弱点付着の最も近い相手 ListID:", v19, 0);
    Log(v20);
    return v22;
  }
  return ListID;
}

// 0x1f97120
void sBtlResetCombine(void) {
  wk->gunskillid = 0;
  return;
}

// 0x1f971b0
static s32 GetSummonIndex(s32 summonindex) {
  if (!sBtlGetNakama(summonindex))
    return -1;
  return wk->summonindex[summonindex];
}

// 0x1f7b0a0
static bool CheckAction_Nakama(SBTLUNIT_WORK *wk, s32 summonindex) {
  SBATTLE_WORK *v7;
  s64 v8;
  s64 v9;
  s32 v10;
  SBATTLE_WORK *v11;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v13;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;

  if (wk->actwk->status == 9)
    return 0;
  if (!CheckStop_BadStatus(wk))
    return 0;
  if (wk->member_num < 1)
    return 0;
  if (!sBtlGetNakama(summonindex))
    return 0;
  v7 = wk;
  v8 = v7->summonindex[summonindex];
  if (v8 < 0)
    return 0;
  v7 = wk;
  v9 = (u32)v8;
  v10 = v7->stock_id[(u32)v8];
  sBtlGetDevilData(v10, -1);
  v11 = wk;
  UnitMng = v11->UnitMng;
  v13 = v11->summonID[v9];
  v14 = sBtlSearchUnit_ID(UnitMng, v13);
  if (!v14)
    return 0;
  v15 = v14;
  if (!sBtlCheckDamageTarget(v15) || (u32)v15->aiwk->mode - 19 < 2)
    return 0;
  return CheckStop_BadStatus(v15);
}

// 0x1f97240
static bool CheckStop_BadStatus(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  sdatUnitWork_t *v5;
  u32 v6;
  char v7;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  v5 = wk->para;
  v6 = (0x608000u >> BadStatus) & 1;
  if (BadStatus >= 0x17)
    LOBYTE(v6) = 0;
  if (BadStatus >= 0xC)
    v7 = v6;
  else
    v7 = (0xE20u >> BadStatus) & 1;
  return (v7 | sBtlIsKoufun(v5)) & 1;
}

// 0x1f97300
static SKLID GetSklId_Length(SKLID sklid) {
  SBTLUNIT_WORK *PChara;
  f32 TargetLen;
  s32 v6;
  f32 v7;
  s32 v8;

  PChara = sBtlGetPChara();
  if (sklid == 1339)
  {
    TargetLen = sBtlGetTargetLen(PChara);
    v6 = 1343;
    v7 = 400.0;
    v8 = 1339;
    goto LABEL_15;
  }
  if (sklid == 1323)
  {
    TargetLen = sBtlGetTargetLen(PChara);
    v6 = 1328;
    v7 = 500.0;
    v8 = 1323;
    goto LABEL_15;
  }
  if (sklid != 1310)
    return sklid;
  TargetLen = sBtlGetTargetLen(PChara);
  if (TargetLen <= 800.0)
  {
    v6 = 144;
    v7 = 278.0;
    v8 = 1310;
LABEL_15:
    if (TargetLen <= v7)
      return v8;
    else
      return v6;
  }
  return 1307;
}

// 0x1f77360
void sBtlSetFirstAtk(SKLID sklid) {
  s32 v4;
  SBTLUNIT_WORK *PChara;
  s32 SklId_Length;

  if (wk->battlemode != 1)
  {
    PChara = sBtlGetPChara();
    SklId_Length = GetSklId_Length(sklid);
    sBtlSetSuperArmor(PChara, SklId_Length, 60);
    v4 = SklId_Length;
    goto LABEL_9;
  }
  v4 = sklid;
LABEL_9:
  SetFirstAtk_Core(v4);
}

// 0x1f97b00
static bool ChkFirstAtkLen(SKLID sklid) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v6;

  if (wk->battlemode == 1)
    return 0;
  PChara = sBtlGetPChara();
  if ((u32)(sklid - 1305) > 1)
    return 0;
  v6 = PChara;
  if (sBtlGetTargetLen(PChara) <= 700.0)
    return 0;
  return 1;
}

// 0x1f97610
static void SetFirstAtk_Core(SKLID sklid) {
  SBTLUNIT_WORK *PChara;
  sdatUnitWork_t *para;
  SBATTLE_WORK *wk_local;
  s32 v7;
  SBTLACTAI_WORK *actaiwk;
  SBATTLE_WORK *v13;
  s32 targetID;
  SBTLACTION_WORK *actwk;
  s32 use_skillid;
  s32 v21;
  char v22;
  void *Instance;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdfVector4_t v30;

  PChara = sBtlGetPChara();
  para = PChara->para;
  if (sBtlGetBadStatus(para) == 10)
  {
    if (sbtlplayertblChkSklNG_MAHUU(PChara, sklid))
      return;
  }
  if (sbtlplayertblChkNG_TutoEtc(0, sklid, 0))
    return;
  PChara->actwk->use_skillid = sklid;
  wk_local = wk;
  wk_local->mode = 3;
  wk_local->bHuumaCancel = 0;
  wk_local->ComboMotRetryCnt = 0;
  wk_local->ComboMotRetryUse = 0;
  *(_OWORD *)&wk_local->sword_nextskill = xmmword_3CFC010;
  if ((u32)(sklid - 1299) <= 0x14 && ((1 << (sklid - 19)) & 0x18000F) != 0)
  {
    wk_local = wk;
    wk_local->mode = 17;
  }
  sBtlResetATKEffect();
  PChara->JumpAfterCnt = 0;
  actaiwk = PChara->actaiwk;
  v13 = wk;
  PChara->status &= ~0x100u;
  PChara->flg &= ~0x800u;
  v13->sord_st = 0;
  v13->sord_bugfix = 0;
  targetID = actaiwk->targetID;
  DecideTarget(targetID == -1, v7);
  actwk = PChara->actwk;
  PChara->cmstatus = 0;
  PChara->katana_hit_cnt = 0;
  use_skillid = actwk->use_skillid;
  PChara->IsMagAtk = 0;
  if (use_skillid == 1296)
  {
    sBtlSetGunLockOn_1st(PChara);
    use_skillid = PChara->actwk->use_skillid;
    if ((use_skillid & 0xFFFFFFFE) != 0x510)
    {
LABEL_27:
      if (use_skillid != 1296)
        goto LABEL_28;
LABEL_42:
      PChara->GunMotionEnd = 0;
      goto LABEL_29;
    }
  }
  else if ((use_skillid & 0xFFFFFFFE) != 0x510)
  {
    goto LABEL_27;
  }
  sBtlSetGunLockOn_Done(PChara);
  use_skillid = PChara->actwk->use_skillid;
  if (use_skillid == 1296)
    goto LABEL_42;
LABEL_28:
LABEL_29:
  SetMagCost(PChara, use_skillid);
  v21 = PChara->actwk->use_skillid;
  if (v21 <= 1295)
  {
    if ((u32)(v21 - 669) >= 2 && v21 != 176)
    {
LABEL_50:
      if (!PChara->setsuma_rowhit_done)
        PChara->setsuma_rowhit_hirameki = 0;
      PChara->setsuma_rowhit_skillid = v21;
      PChara->setsuma_rowhit_done = 0;
      v22 = sklid - 23;
      if ((u32)(sklid - 1303) > 0xE)
        goto LABEL_65;
      goto LABEL_53;
    }
LABEL_46:
    *(u16 *)&PChara->setsuma_rowhit_done = 0;
    v22 = sklid - 23;
    if ((u32)(sklid - 1303) > 0xE)
      goto LABEL_65;
LABEL_53:
    if (((1 << v22) & 0x600F) != 0)
      goto LABEL_54;
    goto LABEL_65;
  }
  if ((u32)(v21 - 1296) < 2)
    goto LABEL_46;
  if (v21 != 1304 && (v21 != 1334 || PChara->setsuma_rowhit_skillid != 1334))
    goto LABEL_50;
  PChara->setsuma_rowhit_skillid = v21;
  v22 = sklid - 23;
  if ((u32)(sklid - 1303) <= 0xE)
    goto LABEL_53;
LABEL_65:
  sBtlResetJump(PChara);
  if (sklid == 1307)
  {
    x = PChara->pos.x;
    y = PChara->pos.y;
    z = PChara->pos.z;
    w = PChara->pos.w;
    v30.x = x;
    v30.y = y;
    v30.z = z;
    v30.w = w;
    sBtlPlay3DSE(0x1005Eu, v30);
  }
LABEL_54:
  if ((u32)(sklid - 164) > 2)
    return;
  if (wk->battlemode == 1)
  {
    Instance = get_Instance(0);
    Punch(Instance, 0);
  }
}

// 0x1f98220
static void SetMagCost(SBTLUNIT_WORK *wk, SKLID sklid) {
  bool v5;
  sdatUnitWork_t *para;
  s32 SkillCost;
  s32 v10;
  SBATTLE_WORK *v12;
  s32 v13;

  v5 = sbtlplayertblChkPlayerMagSkill(sklid);
  if (v5)
  {
    wk->raido_magwaza_costnot = 0;
    if ((sBtlGetSkilltbl(sklid)->s_type & 0x10) != 0)
    {
      para = wk->para;
      SkillCost = sBtlGetSkillCost(para, sklid);
      if (SkillCost < 1)
        return;
      v10 = SkillCost;
      v12 = wk;
      v13 = v10 << ((v12->status3 & 0x2000000) != 0);
      goto LABEL_9000;
      if (v12->mag < v13)
      {
LABEL_19:
        v12->raido_magwaza_costnot = 1;
        return;
      }
      goto LABEL_23;
LABEL_9000:
      if (v12->mag < v13)
        goto LABEL_19;
LABEL_23:
      sBtlDecMag(v13);
    }
  }
  else
  {
    wk->raido_magwaza_costnot = 0;
  }
}

// 0x1f8c7f0
static bool CancelSystem(bool *_ComboDone) {
  SBTLUNIT_WORK *PChara;
  s64 v4;
  s32 v6;
  SBTLUNIT_WORK *v9;
  s32 sword_skillcnt;
  bool IsBattleKey;
  SBATTLE_WORK *v16;
  bool v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 sword_nextskill;
  SBATTLE_WORK *v22;
  s32 v23;
  s32 ComboBgn;
  SBATTLE_WORK *v26;
  s32 v27;
  s32 v29;
  SBATTLE_WORK *v30;
  s32 v31;
  s32 keyBgn;
  SBATTLE_WORK *v36;
  s32 v40;
  s32 v41;
  SBATTLE_WORK *v42;
  s32 v43;
  SBATTLE_WORK *v44;
  s32 v45;
  s32 SkillG;
  u32 v49;
  s64 v50;
  s64 v51;
  u32 v52;
  SBATTLE_WORK *v54;
  bool IsMoveBtn;
  SBATTLE_WORK *v57;
  u32 v58;
  s32 SkillL;
  s32 v65;
  s32 v66;
  s32 *m_Items;
  s32 v76;
  SBATTLE_WORK *v77;
  s32 GuardCancelBgn;
  SBATTLE_WORK *v80;
  s32 KaihiCancelBgn;
  SBATTLE_WORK *v83;
  s32 MoveCancelBgn;
  SBATTLE_WORK *v88;
  s32 GunCancelBgn;
  SBATTLE_WORK *v93;
  s32 SwordCancelBgn;
  SBATTLE_WORK *v98;
  s32 ChargeCancelBgn;
  SBATTLE_WORK *v103;
  _BOOL4 v104;
  s32 v105;
  s32 v106;
  _BOOL4 bKaihi;
  u32 v110;
  SBATTLE_WORK *v113;
  SBATTLE_WORK *v120;
  SBATTLE_WORK *v126;
  SBATTLE_WORK *v128;
  f32 TargetLen;
  SBATTLE_WORK *v130;
  s32 v131;
  s32 v137;
  SBATTLE_WORK *v138;
  char v139;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v143;
  bool v144;
  s32 v145;
  bool v146;
  s32 v147;
  s32 v148;
  u32 v149;
  s64 v150;
  s64 v151;
  s32 RsCancelBgn;
  SBATTLE_WORK *v154;
  s32 v155;
  u32 v156;
  s32 v161;
  SBATTLE_WORK *v162;
  s32 v163;
  bool v164;
  s32 targetID;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;
  u16 major;
  s32 minor;
  f32 hit_area_r;
  f32 x;
  f32 y;
  f32 z;
  f32 v174;
  f32 v175;
  long f64 v176;
  f32 v177;
  SBATTLE_WORK *v179;
  s32 v180;
  s32 v182;
  u32 v184;
  s32 v186;
  SBTLUNIT_WORK *v187;
  s32 v188;
  f32 v189;
  u32 v190;
  SBATTLE_WORK *v191;
  SBTLACTION_WORK *actwk;
  s32 use_skillid;
  u32 v195;
  SBATTLE_WORK *v196;
  SBATTLE_WORK *v197;
  s32 v198;
  s32 v199;
  SBTLACTION_WORK *v200;
  SBTLACTION_WORK *v201;
  s32 v202;
  SBATTLE_WORK *v204;
  s32 v210;
  void *Instance;
  f32 w;
  f32 v218;
  u16 v219;
  s32 v220;
  f32 v221;
  f32 v222;
  f32 v223;
  f32 v224;
  f32 v225;
  f32 v226;
  f32 v227;
  f32 v228;
  f32 v229;
  long f64 v230;
  f32 v231;
  f32 v232;
  f32 v233;
  f32 v234;
  f32 PosToDir;
  f32 Dir180;
  long f64 v237;
  sdfVector4_t *p_rot;
  bool v244;
  SBATTLE_WORK *v246;
  bool v249;
  bool v251;
  SBATTLE_WORK *v255;
  s32 SkillH;
  bool v257;
  S_KeyCancel *v259;
  s32 v263;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v266;
  SBTLUNIT_WORK *v268;
  f32 v278;
  f32 v279;
  f32 v280;
  f32 v281;
  f32 v282;
  f32 v283;
  long f64 v284;
  f32 v293;
  f32 v294;
  s32 ID;
  s32 TgtID;
  sdfVector4_t v297;

  TgtID = 0;
  ID = 0;
  PChara = sBtlGetPChara();
  v4 = 0;
  *ComboDone = 0;
  while (1)
  {
    v6 = g_aRaidouSkill[v4];
    if (sBtlGetPChara()->actwk->use_skillid == v6)
      break;
    if (++v4 == 55)
    {
      v9 = sBtlGetPChara();
      if (sBtlGetSklVisualTbl(v9->actwk->use_skillid)->motionno == 27)
      {
        sword_skillcnt = wk->sword_skillcnt;
        if (sword_skillcnt >= 6)
        {
          sword_skillcnt = wk->sword_skillcnt;
          if (sword_skillcnt <= 39)
          {
            IsBattleKey = sBtlIsBattleKey(4122, 2);
            if (IsBattleKey)
            {
              wk->sword_nextskill = 176;
            }
          }
        }
        if (wk->sword_skillcnt >= 11)
        {
          sword_nextskill = wk->sword_nextskill;
          if (sword_nextskill)
          {
            sword_nextskill = wk->sword_nextskill;
            v20 = sword_nextskill;
            goto LABEL_47;
          }
        }
        v22 = wk;
        v23 = v22->sword_skillcnt;
        if (v23 < 40)
          goto LABEL_125;
        if (v23 > 92)
          goto LABEL_125;
        v22 = wk;
        if (!v22->sword_nextskill)
        {
          v22 = wk;
          if (v22->bGuard)
            goto LABEL_867;
          IsMoveBtn = sBtlIsMoveBtn(sBtlPlayer);
          if (IsMoveBtn)
          {
LABEL_867:
            v57 = wk;
            v57->mode = 1;
            *(u32 *)v57->gstat = 0;
            sBtlResetAction(PChara);
            sBtlSetAction(PChara, 1, 0);
            sBtlSetMotion(PChara, 0, 0, 0, 0);
            return 1;
          }
        }
LABEL_125:
        v17 = 0;
        v44 = wk;
        v45 = PChara->actwk->framecnt - PChara->beforeframe;
LABEL_128:
        v44->sword_skillcnt = v45 + 1;
        return v17;
      }
      return 0;
    }
  }
  v16 = wk;
  if (v16->bSpiritSkill)
  {
    sBtlPlayerRSpiritInit(PChara);
    return 1;
  }
  if (v16->bSetsuma)
    goto LABEL_32;
LABEL_53:
  if (!wk->bRR_Assist)
    goto LABEL_66;
  goto LABEL_61;
LABEL_32:
  v18 = sBtlInputChkSetsuma(PChara);
  if (v18)
  {
    v19 = v18;
    ClearPosLink();
    v20 = v19;
LABEL_47:
    sBtlSetFirstAtk(v20);
    return 1;
  }
  goto LABEL_53;
LABEL_61:
  ComboBgn = aKeyCancel[v4]->ComboBgn;
  v26 = wk;
  if (ComboBgn <= v26->sword_skillcnt)
  {
    v26 = wk;
    if (!v26->sword_nextskill)
    {
      sBtlBS_LASTB1_Action_Req();
    }
    v27 = 1;
    goto LABEL_68;
  }
LABEL_66:
  v27 = 0;
LABEL_68:
  if (!wk->bRU_Assist)
    goto LABEL_74;
  v29 = aKeyCancel[v4]->ComboBgn;
  v30 = wk;
  if (v29 > v30->sword_skillcnt)
  {
LABEL_74:
    v31 = 0;
    goto LABEL_76;
  }
  v30 = wk;
  if (!v30->sword_nextskill)
  {
    sBtlBS_LASTB1_Action_Req();
  }
  v31 = 1;
LABEL_76:
  keyBgn = aKeyCancel[v4]->keyBgn;
  v36 = wk;
  if (keyBgn <= v36->sword_skillcnt)
  {
    v36 = wk;
    if (!v36->sword_nextskill)
    {
      switch ((s32)v4)
      {
        case 0:
        case 1:
        case 2:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 53:
        case 54:
          v36 = wk;
          if (v27 | v36->bRR)
          {
            SkillL = aKeyCancel[v4]->SkillL;
            if (SkillL)
            {
              wk->sword_nextskill = SkillL;
              if ((u32)v4 == 41)
              {
                SkillL = wk->sword_nextskill;
                if (SkillL == 1306)
                {
                  if (sBtlGetJumpY(sBtlPlayer) >= 0.0)
                  {
                    v65 = 1310;
                    v36 = wk;
                    goto LABEL_844;
                  }
                }
              }
              break;
            }
          }
          else
          {
            v36 = wk;
            if (v31 | v36->bComboSRU)
            {
              if (aKeyCancel[v4]->SkillH)
              {
                if (sBtlDat()->m_type == 1)
                {
                  goto LABEL_232;
                }
                if (sBtlDat()->m_type == 2)
                {
                  goto LABEL_806;
                }
                if (sBtlDat()->m_type == 3)
                {
                  goto LABEL_829;
                }
              }
            }
          }
          if ((u32)v4 == 41)
          {
            if (v31 | wk->bRU)
            {
              if (sBtlGetJumpY(sBtlPlayer) < -50.0)
              {
                v65 = 1316;
                v36 = wk;
                goto LABEL_844;
              }
            }
          }
          break;
        case 4:
          v36 = wk;
          if (v36->combo_gunbeforeskill == -1)
            goto LABEL_858;
          v249 = sBtlIsBattleKey(4120, 2);
          if (!v249)
            goto LABEL_735;
          v251 = R1_HuumaBtn();
          if (v251)
            goto LABEL_735;
          v255 = wk;
          SkillH = aKeyCancel[v255->combo_gunbeforeskill]->SkillL;
          if (SkillH)
            goto LABEL_743;
LABEL_735:
          v257 = sBtlIsBattleKey(4121, 2);
          if (!v257)
            goto LABEL_858;
          v259 = aKeyCancel;
          v255 = wk;
          SkillH = v259[v255->combo_gunbeforeskill]->SkillH;
          if (SkillH)
          {
LABEL_743:
            v255 = wk;
            v255->sword_nextskill = SkillH;
          }
          else
          {
LABEL_858:
            if (sBtlIsBattleKey(4122, 2))
            {
              SkillG = aKeyCancel[v4]->SkillG;
              if (SkillG)
                goto LABEL_205;
            }
          }
          break;
        case 7:
          sBtlGetGunLockOn_TgtID(sBtlPlayer, &TgtID);
          if (TgtID != -1)
            goto LABEL_749;
          break;
        case 8:
          sBtlGetGunLockOn_TgtID(sBtlPlayer, &ID);
          v263 = ID;
          if (ID != -1)
          {
            UnitMng = wk->UnitMng;
            v266 = sBtlSearchUnit_ID(UnitMng, v263);
            if (v266)
            {
              v268 = v266;
              if ((v266->side & 2) != 0 && (v266->status & 0x4000000) == 0 && (v266->vstatus & 0x10000) == 0)
              {
                if (sBtlCheckDamageTarget(v268))
                {
LABEL_749:
                  v65 = 1297;
                  v36 = wk;
                  goto LABEL_844;
                }
              }
              sBtlSetGunLockOn_EnemyDead_Done(sBtlPlayer, v268);
            }
          }
          break;
        case 12:
          if (v27 | sBtlIsBattleKey(4120, 2))
          {
            if (!R1_HuumaBtn())
            {
              v65 = 165;
              v36 = wk;
              goto LABEL_844;
            }
          }
          break;
        case 13:
          if (v27 | sBtlIsBattleKey(4120, 2))
          {
            if (!R1_HuumaBtn())
            {
              v65 = 166;
              v36 = wk;
              goto LABEL_844;
            }
          }
          break;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
          goto LABEL_130;
        case 29:
          v36 = wk;
          if (!(v31 | v36->bComboSRU))
          {
LABEL_130:
            if (!(v27 | wk->bRR))
              goto LABEL_868;
            SkillG = aKeyCancel[v4]->SkillL;
            if (!SkillG)
            {
LABEL_868:
              if (!(v31 | wk->bComboSRU))
                break;
              SkillG = aKeyCancel[v4]->SkillH;
              if (!SkillG)
                break;
LABEL_205:
            }
            wk->sword_nextskill = SkillG;
            break;
          }
          v36 = wk;
          if (v36->sword_chaincnt <= 2)
          {
            v36 = wk;
            v65 = 1334;
          }
          else
          {
            v36 = wk;
            v65 = 1335;
          }
LABEL_844:
          v36->sword_nextskill = v65;
          break;
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
          v36 = wk;
          if (v27 | v36->bRR)
          {
            SkillG = aKeyCancel[v4]->SkillL;
            if (SkillG)
              goto LABEL_205;
          }
          if (sBtlDat()->m_type == 1)
          {
            v36 = wk;
            if (!(v31 | v36->bComboSRU))
              break;
LABEL_232:
            v36 = wk;
            v65 = 1323;
          }
          else if (sBtlDat()->m_type == 2)
          {
            v36 = wk;
            if (!(v31 | v36->bComboSRU))
              break;
LABEL_806:
            v36 = wk;
            v65 = 1333;
          }
          else
          {
            if (sBtlDat()->m_type != 3)
              break;
            v36 = wk;
            if (!(v31 | v36->bComboSRU))
              break;
LABEL_829:
            v36 = wk;
            v65 = 1339;
          }
          goto LABEL_844;
        default:
          break;
      }
    }
  }
  v40 = aKeyCancel[v4]->keyBgn;
  v41 = wk->sword_skillcnt;
  if (v40 > v41)
  {
    v41 = wk->sword_skillcnt;
    if (v41 < 5)
      goto LABEL_245;
  }
  if ((u32)v4 > 0x36 || ((1 << v4) & 0x7FEFFFFFFF8077LL) == 0)
    goto LABEL_245;
  v42 = wk;
  v43 = v42->sword_nextskill;
  if (v43 > 158)
  {
    if ((u32)v43 > 0xD0)
    {
      if ((u32)(v43 - 312) < 2 || v43 == 212 || v43 == 744)
        goto LABEL_245;
      goto LABEL_148;
    }
    v49 = v43 - 163;
    if (v49 <= 0x2D)
    {
      v50 = 1 << v49;
      v51 = 0x200010000001LL;
      goto LABEL_147;
    }
    goto LABEL_148;
  }
  if (v43 > 39)
  {
    if ((u32)(v43 - 55) <= 0xA && ((1 << (v43 - 55)) & 0x601) != 0 || (u32)(v43 - 156) < 3)
      goto LABEL_245;
    goto LABEL_148;
  }
  if ((u32)v43 <= 0x27)
  {
    v50 = 1 << v43;
    v51 = 0x8000800100LL;
LABEL_147:
    if ((v50 & v51) != 0)
      goto LABEL_245;
  }
LABEL_148:
  v42 = wk;
  if (v42->bRaiSkill_RU)
  {
    if (!v52)
    {
      v42 = wk;
    }
    v54 = v42;
    v66 = 0;
    m_Items = GBWK->player->raidouSkill;
LABEL_244:
    v76 = *m_Items;
    v54->combo_nextskill_rs_cooltimeidx = v66;
    v42->sword_nextskill = v76;
    goto LABEL_245;
  }
  if (!v52)
  {
    v42 = wk;
  }
  if (v42->bRaiSkill_RL)
  {
    if (!v58)
    {
      v42 = wk;
    }
    v54 = v42;
    v66 = 1;
    m_Items = &GBWK->player->raidouSkill[1];
    goto LABEL_244;
  }
  if (!v58)
  {
    v42 = wk;
  }
  if (v42->bRaiSkill_RD)
  {
    v42 = wk;
    v54 = v42;
    v66 = 2;
    m_Items = &GBWK->player->raidouSkill[2];
    goto LABEL_244;
  }
LABEL_245:
  v77 = wk;
  if (v77->sword_nextskill && ((u32)(v4 - 12) < 0x20 || (u32)v4 <= 0x36 && ((1 << v4) & 0x7FE00000000075LL) != 0))
  {
    v77 = wk;
    if (v77->bGuard)
    {
      v77 = wk;
      v77->sword_nextskill = 0;
    }
  }
  GuardCancelBgn = aKeyCancel[v4]->GuardCancelBgn;
  v80 = wk;
  if (GuardCancelBgn <= v80->sword_skillcnt)
  {
    v80 = wk;
    if (!v80->sword_nextskill && (u32)v4 <= 0x36 && ((1 << v4) & 0x7FEFFFFFFFF077LL) != 0)
    {
      v80 = wk;
      if (v80->bGuard)
      {
        ClearPosLink();
        GuardInit(PChara);
        return 1;
      }
    }
  }
  KaihiCancelBgn = aKeyCancel[v4]->KaihiCancelBgn;
  v83 = wk;
  if (KaihiCancelBgn <= v83->sword_skillcnt)
  {
    v83 = wk;
    if (!v83->sword_nextskill && (u32)v4 <= 0x36 && ((1 << v4) & 0x7FEFFFFFFFF07FLL) != 0)
    {
      v83 = wk;
      bKaihi = v83->bKaihi;
      if (bKaihi)
      {
        if (!v110)
        sBtlKaihiInit(PChara);
        return 1;
      }
      if (!v110)
      if (ComboProc_Jump(sBtlPlayer))
      {
        sBtlJumpStart(PChara);
        return 1;
      }
    }
  }
  MoveCancelBgn = aKeyCancel[v4]->MoveCancelBgn;
  v88 = wk;
  if (MoveCancelBgn <= v88->sword_skillcnt)
  {
    v88 = wk;
    if (!v88->sword_nextskill && (u32)v4 <= 0x36 && ((1 << v4) & 0x7FEFFFFFFFF077LL) != 0)
    {
      if (sBtlIsMoveBtn(sBtlPlayer))
        goto LABEL_370;
      v113 = wk;
      v113->bHuumaCancel = 1;
      if (!IsSceanStop())
      {
        if (sBtlNormalProc_Huuma(PChara, 0) == 2)
        {
          ClearPosLink();
          sBtlResetGunMode(PChara, 0);
          return 1;
        }
      }
    }
  }
  GunCancelBgn = aKeyCancel[v4]->GunCancelBgn;
  v93 = wk;
  if (GunCancelBgn <= v93->sword_skillcnt)
  {
    v93 = wk;
    if (!v93->sword_nextskill && (u32)v4 <= 0x36 && ((1 << v4) & 0x7FEFFFFFFF8077LL) != 0)
    {
      v93 = wk;
      if (v93->bGunMode && (PChara->vstatus & 0x8000) == 0)
      {
        if (sBtlGetJumpY(sBtlPlayer) >= -0.1)
        {
          ClearPosLink();
          v120 = wk;
          v120->mode = 1;
          *(u32 *)v120->gstat = 0;
          sBtlResetAction(PChara);
          sBtlResetJump(PChara);
          sBtlStartGunMode(PChara);
          return 1;
        }
      }
    }
  }
  SwordCancelBgn = aKeyCancel[v4]->SwordCancelBgn;
  v98 = wk;
  if (SwordCancelBgn <= v98->sword_skillcnt)
  {
    v98 = wk;
    if (!v98->sword_nextskill)
    {
      if ((u32)v4 <= 0x36)
      {
        if (((1 << v4) & 0x7FEFFFFFFF8077LL) != 0)
        {
          v98 = wk;
          if (v98->bRaiSkill_RU)
          {
            if (sBtlPlayerRSkillInit(PChara, GBWK->player->raidouSkill[0], 0))
            {
              return 1;
            }
          }
          else
          {
            v98 = wk;
            if (v98->bRaiSkill_RL)
            {
              v17 = 1;
              if (sBtlPlayerRSkillInit(PChara, GBWK->player->raidouSkill[1], 1))
              {
                return v17;
              }
            }
            else
            {
              v98 = wk;
              if (v98->bRaiSkill_RD)
              {
                if (sBtlPlayerRSkillInit(PChara, GBWK->player->raidouSkill[2], 2))
                {
                  return 1;
                }
              }
              else
              {
                v98 = wk;
                if (v27 | v98->bRR)
                {
                  switch ((s32)v4)
                  {
                    case '/':
                    case '4':
                      v20 = 1311;
                      break;
                    case '0':
                      v20 = 1312;
                      break;
                    case '1':
                      v20 = 1313;
                      break;
                    case '2':
                      v20 = 1314;
                      break;
                    default:
                      v20 = 1310;
                      break;
                  }
                  goto LABEL_47;
                }
              }
            }
          }
        }
        else if ((u32)v4 == 14)
        {
          v98 = wk;
          if (v27 | v98->bRR)
          {
            v20 = 164;
            goto LABEL_47;
          }
          goto LABEL_300;
        }
      }
      if ((u32)v4 <= 0x36 && ((1 << v4) & 0x7FAFFFFFFF8077LL) != 0)
      {
        if (sBtlDat()->m_type == 1)
        {
          if (v31 | wk->bComboSRU)
          {
            v20 = 1323;
            goto LABEL_47;
          }
        }
        else if (sBtlDat()->m_type == 2)
        {
          if (v31 | wk->bComboSRU)
          {
            v20 = 1333;
            goto LABEL_47;
          }
        }
        else if (sBtlDat()->m_type == 3)
        {
          if ((u32)(v4 - 47) > 5)
            goto LABEL_869;
          if (wk->bComboSRU_NowChk)
          {
            v244 = 0;
          }
          else
          {
LABEL_869:
            v244 = sBtlIsBattleKey(4121, 1);
          }
          v246 = wk;
          if (!v246->bAssistAttackBtn && v244)
          {
            v246 = wk;
            v17 = 1;
            v246->sord_st = 0;
            v246->sord_bugfix = 0;
            v246->sword_nextskill = 0;
            v246->ComboMotRetryCnt = 0;
            v246->ComboMotRetryUse = 0;
            *(u64 *)&v246->sword_skillcnt = 0;
            *ComboDone = 1;
            return v17;
          }
        }
      }
    }
  }
LABEL_300:
  ChargeCancelBgn = aKeyCancel[v4]->ChargeCancelBgn;
  v103 = wk;
  if (ChargeCancelBgn <= v103->sword_skillcnt)
  {
    v103 = wk;
    if (!v103->sword_nextskill)
    {
      v103 = wk;
      if (v103->bComboLRU)
      {
LABEL_370:
        ClearPosLink();
        v126 = wk;
        v126->mode = 1;
        *(u32 *)v126->gstat = 0;
        sBtlResetAction(PChara);
        sBtlResetJump(PChara);
        v17 = 1;
        sBtlSetAction(PChara, 1, 0);
        return v17;
      }
    }
  }
  switch ((s32)v4)
  {
    case ')':
      JumpAtk1Proc(PChara);
      v104 = 0;
      v105 = 0;
      v106 = 1;
      break;
    case ',':
      v128 = wk;
      if (v128->sword_skillcnt < 35)
        goto LABEL_870;
      v128 = wk;
      if (v128->sword_nextskill)
      {
LABEL_870:
        TargetLen = sBtlGetTargetLen(PChara);
        if (TargetLen >= 50.0)
        {
          if (TargetLen >= 200.0)
            goto LABEL_437;
          v128 = wk;
          if (v128->sword_nextskill)
            goto LABEL_437;
        }
        else
        {
          v128 = wk;
          if (v128->sword_nextskill)
          {
            v106 = 0;
            v105 = 0;
            v104 = 1;
            break;
          }
        }
      }
      v128 = wk;
      v106 = 0;
      v128->sword_nextskill = 1309;
      v105 = 0;
      v104 = 1;
      break;
    case '-':
      v130 = wk;
      v131 = v130->sword_skillcnt;
      if (v131 < 45)
        goto LABEL_409;
      v130 = wk;
      v131 = v130->sword_skillcnt;
      if (v131 > 60)
        goto LABEL_409;
      v130 = wk;
      if (!v130->bRR)
      {
        v130 = wk;
        if (!v130->bRR_Assist)
          goto LABEL_409;
      }
      if (!sbtlplayertblChkNG_TutoEtc(0, 1306, 0))
      {
        v106 = 0;
        v104 = 1;
        v105 = 1;
        wk->sword_nextskill = 1306;
      }
      else
      {
LABEL_409:
        v106 = 0;
        v104 = 0;
        v105 = 1;
      }
      break;
    case '.':
      if (sBtlGetTargetLen(PChara) >= 50.0)
        goto LABEL_437;
      v106 = 0;
      v105 = 0;
      v104 = wk->sword_nextskill != 0;
      break;
    default:
      if ((v4 & 0x7FFFFFFE) == 0x2A)
      {
        JumpAtk2Proc(PChara);
      }
      else if ((u32)(v4 - 55) >= 0xFFFFFFFE)
      {
        JumpHAtkProc(PChara);
      }
LABEL_437:
      v106 = 0;
      v104 = 0;
      v105 = 0;
      break;
  }
  v137 = aKeyCancel[v4]->ComboBgn;
  v138 = wk;
  if (v137 <= v138->sword_skillcnt)
  {
    v138 = wk;
    if (v138->sword_nextskill)
      v139 = 1;
    else
      v139 = v104;
    if ((v139 & 1) == 0)
    {
      v104 = 0;
      goto LABEL_471;
    }
  }
  else if (!v104)
  {
    goto LABEL_471;
  }
  para = PChara->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus == 10)
  {
    v143 = wk->sword_nextskill;
    v144 = sbtlplayertblChkSklNG_MAHUU(PChara, v143);
    if (v144)
    {
      wk->sword_nextskill = 0;
    }
  }
  v145 = wk->sword_nextskill;
  v146 = sbtlplayertblChkNG_TutoEtc(0, v145, 0);
  if (v146)
  {
    wk->sword_nextskill = 0;
  }
LABEL_471:
  v147 = wk->sword_nextskill;
  if (!v147)
    goto LABEL_485;
  v147 = wk->sword_nextskill;
  if (v147 <= 158)
  {
    if (v147 > 39)
    {
      if (((u32)(v147 - 55) > 0xA || ((1 << (v147 - 55)) & 0x601) == 0) && (u32)(v147 - 156) >= 3)
        goto LABEL_485;
      goto LABEL_496;
    }
    v148 = 0;
    if ((u32)v147 > 0x27)
      goto LABEL_497;
    v150 = 1 << v147;
    v151 = 0x8000800100LL;
  }
  else
  {
    if ((u32)v147 > 0xD0)
    {
      if ((u32)(v147 - 312) >= 2 && v147 != 744 && v147 != 212)
      {
LABEL_485:
        v148 = 0;
        goto LABEL_497;
      }
      goto LABEL_496;
    }
    v149 = v147 - 163;
    v148 = 0;
    if (v149 > 0x2D)
      goto LABEL_497;
    v150 = 1 << v149;
    v151 = 0x200010000001LL;
  }
  if ((v150 & v151) != 0)
LABEL_496:
    v148 = 1;
LABEL_497:
  RsCancelBgn = aKeyCancel[v4]->RsCancelBgn;
  v154 = wk;
  v155 = RsCancelBgn <= v154->sword_skillcnt || v104;
  if ((v148 & v155) == 1)
  {
    v154 = wk;
    if (sBtlPlayerRSkillInit(PChara, v154->sword_nextskill, v154->combo_nextskill_rs_cooltimeidx))
    {
      return 1;
    }
    wk->sword_nextskill = 0;
  }
  v156 = wk->sword_nextskill - 1320;
  if (v156 <= 0x1A)
  {
    if (((1 << v156) & 0x1FF9) != 0)
    {
      if (sBtlDat()->m_type == 1)
        goto LABEL_525;
    }
    else if (((1 << v156) & 0x7F80004) != 0)
    {
      if (sBtlDat()->m_type == 3)
        goto LABEL_525;
    }
    else if (((1 << v156) & 0x3E002) == 0 || sBtlDat()->m_type == 2)
    {
      goto LABEL_525;
    }
    wk->sword_nextskill = 0;
  }
LABEL_525:
  v161 = aKeyCancel[v4]->ComboBgn;
  v162 = wk;
  if (v161 <= v162->sword_skillcnt)
  {
    v162 = wk;
    v164 = v162->sword_nextskill == 0;
    v163 = !v104;
    if (!v164)
      v163 = 0;
  }
  else
  {
    v163 = !v104;
  }
  if (((v148 | v163) & 1) == 0)
  {
    v179 = wk;
    v180 = wk->sword_nextskill;
    v179->sword_nextskill = GetSklId_Length(v180);
    v182 = wk->sword_nextskill;
    if (v182 == 1306)
    {
      if (v105)
      {
        if (!v184)
        JumpAtk2Start_From_APPROACHATK(PChara);
LABEL_592:
        v190 = wk->sword_nextskill - 1303;
        if (v190 <= 0xE)
        {
          if (((1 << v190) & 0x600F) != 0)
          {
            goto LABEL_596;
          }
        }
        sBtlResetJump(PChara);
LABEL_596:
        v191 = wk;
        v191->sord_st = 0;
        v191->sord_bugfix = 0;
        actwk = sBtlGetPChara()->actwk;
        use_skillid = actwk->use_skillid;
        v196 = wk;
        if (use_skillid == v196->sword_nextskill)
        {
          if (!v195)
          {
            v196 = wk;
          }
          ++v196->sword_chaincnt;
        }
        else
        {
          if (!v195)
          {
            v196 = wk;
          }
          v196->sword_chaincnt = 0;
        }
        v197 = wk;
        v198 = v197->sword_nextskill;
        if ((u32)v4 != 4 || v198 != 176)
        {
          v197 = wk;
          v198 = v197->sword_nextskill;
          if (v198 == 176)
            v199 = v4;
          else
            v199 = -1;
          v197 = wk;
          v197->combo_gunbeforeskill = v199;
        }
        v200 = PChara->actwk;
        v201 = PChara->actwk;
        v200->use_skillid = wk->sword_nextskill;
        v202 = v201->use_skillid;
        sBtlSetSuperArmor(PChara, v202, 60);
        v204 = wk;
        v204->bHuumaCancel = 0;
        v204->ComboMotRetryCnt = 0;
        v204->ComboMotRetryUse = 0;
        *(u64 *)&v204->sword_nextskill = 0;
        sBtlResetATKEffect();
        if (PChara->actaiwk->targetID != -1)
        {
          goto LABEL_622;
        }
        DecideTarget(1, (s32)v205);
LABEL_622:
        if (wk->CameraGazeOff)
        {
          if ((PChara->actwk->use_skillid & 0xFFFFFFFE) == 0x510)
          {
            PChara->katana_hit_cnt = 0;
            PChara->IsMagAtk = 0;
            goto LABEL_631;
          }
        }
        sBtlSetPlayerDir_ToTarget(PChara);
        v210 = PChara->actwk->use_skillid;
        PChara->katana_hit_cnt = 0;
        PChara->IsMagAtk = 0;
        if ((v210 & 0xFFFFFFFE) != 0x510)
        {
          if (v210 == 1296)
            goto LABEL_642;
          goto LABEL_634;
        }
LABEL_631:
        sBtlSetGunLockOn_Done(PChara);
        v210 = PChara->actwk->use_skillid;
        if (v210 == 1296)
        {
LABEL_642:
          PChara->GunMotionEnd = 0;
          goto LABEL_635;
        }
LABEL_634:
LABEL_635:
        SetMagCost(PChara, v210);
        sBtlSetSetsuma_SkillStart(PChara, PChara->actwk->use_skillid);
        if (sBtlR1_IsNaked() && (u32)(PChara->actwk->use_skillid - 164) <= 2)
        {
          Instance = get_Instance(0);
          Punch(Instance, 0);
          return 1;
        }
        return 1;
      }
      if (!v184)
      JumpAtk2Start(sBtlPlayer);
      goto LABEL_592;
    }
    if (v182 == 1316)
      goto LABEL_581;
    goto LABEL_9002;
    if (wk->sword_nextskill == 1316)
    {
LABEL_581:
      JumpHAtkStart(PChara);
      goto LABEL_592;
    }
LABEL_9002:
    goto LABEL_592;
  }
  if ((u32)v4 == 53)
  {
    targetID = PChara->actaiwk->targetID;
    if (targetID == -1 || (PChara->hstatus & 0x4000) != 0)
      goto LABEL_815;
    targetID = PChara->actaiwk->targetID;
    pUnit = wk->UnitMng->pUnitL[targetID]->pUnit;
    if (!pUnit)
      goto LABEL_815;
    devilid = (u16)pUnit->para->devilid;
    if (devilid == 314 || devilid == 258)
    {
      major = PChara->major;
      minor = PChara->minor;
      hit_area_r = sBtlGetVisualData(major, minor)->hit_area_r;
      x = PChara->pos.x;
      y = PChara->pos.y;
      z = pUnit->pos.z;
      sub_1B332C0(0, x, y, z, 0.0);
      sub_1B33360(0, PChara->pos.x, PChara->pos.y, PChara->pos.z, PChara->pos.w);
      sub_1B33400(0);
      v174 = (loc_1CDE880)(0);
      if ((f32)(hit_area_r + 0.01) < v174)
      {
        if (v174 <= 20.0)
          v175 = v174;
        else
          v175 = 20.0;
        sub_1B33480(0, v175 / v174);
        *(__n128 *)&v176 = sub_1B33520(0);
        sub_1B335A0(&PChara->pos, 0, v176);
      }
      v177 = 0.0;
    }
    else
    {
      w = PChara->pos.w;
      v218 = PChara->pos.z;
      v219 = PChara->major;
      v293 = PChara->pos.y;
      v294 = PChara->pos.x;
      v220 = PChara->minor;
      v221 = sBtlGetVisualData(v219, v220)->hit_area_r;
      v222 = sBtlGetVisualData(pUnit->major, pUnit->minor)->hit_area_r;
      v223 = pUnit->pos.x;
      v224 = pUnit->pos.y;
      v226 = pUnit->pos.z;
      v225 = pUnit->pos.w;
      sub_1B332C0(0, v223, v224, v226, v225);
      sub_1B33360(0, PChara->pos.x, PChara->pos.y, PChara->pos.z, PChara->pos.w);
      sub_1B33400(0);
      v227 = (loc_1CDE880)(0);
      if ((f32)((f32)(v221 + v222) + 0.01) < v227)
      {
        if (v227 <= 20.0)
          v228 = v227;
        else
          v228 = 20.0;
        v229 = v227;
        v227 = v229;
        sub_1B33480(0, v228 / v227);
        *(__n128 *)&v230 = sub_1B33520(0);
        sub_1B335A0(&PChara->pos, 0, v230);
      }
      v297.y = v293;
      v297.x = v294;
      v297.z = v218;
      v297.w = w;
      CheckMapHit(PChara, v297);
      v231 = PChara->pos.x;
      v232 = PChara->pos.z;
      v233 = pUnit->pos.x;
      v234 = pUnit->pos.z;
      PosToDir = sBtlGetPosToDir(v231, v232, v233, v234);
      v177 = sBtlGet360(PosToDir);
    }
    Dir180 = sBtlGetDir180(v177);
    PChara->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    p_rot = &PChara->rot;
  }
  else
  {
    if (!v106)
      goto LABEL_815;
    v186 = PChara->actaiwk->targetID;
    if (v186 == -1 || (PChara->hstatus & 0x4000) != 0)
      goto LABEL_815;
    v186 = PChara->actaiwk->targetID;
    v187 = wk->UnitMng->pUnitL[v186]->pUnit;
    if (!v187)
      goto LABEL_815;
    v188 = (u16)v187->para->devilid;
    if (v188 == 314 || v188 == 258)
    {
      v189 = 0.0;
    }
    else
    {
      v278 = PChara->pos.x;
      v279 = PChara->pos.z;
      v280 = v187->pos.x;
      v281 = v187->pos.z;
      v282 = sBtlGetPosToDir(v278, v279, v280, v281);
      v189 = sBtlGet360(v282);
    }
    v283 = sBtlGetDir180(v189);
    PChara->mv_rotbk = v283;
    FromEuler(0.0, v283 * 0.017453292, 0.0);
    p_rot = &PChara->rot;
  }
  *(__n128 *)&v284 = sub_1B335A0(p_rot, 0, v237);
  sub_1B335A0(&PChara->rotbk, 0, v284);
LABEL_815:
  if (PChara->actwk->framecnt - PChara->beforeframe >= 0)
  {
    if ((PChara->hstatus & 0x4000) == 0)
    {
      v17 = 0;
      v44 = wk;
      v45 = v44->sword_skillcnt;
      goto LABEL_128;
    }
    return 0;
  }
  v17 = 0;
  wk->sword_skillcnt = 0;
  return v17;
}

// 0x1f796f0
static bool EscapeGauge(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBATTLE_WORK *v7;
  s32 mode;
  SBTLUNIT_WORK *Nakama;
  SBTLACTION_WORK *actwk;
  SBTLUNIT_WORK *v13;
  SBTLACTION_WORK *v14;
  s16 *p_escape_cnt;
  SBATTLE_WORK *v18;
  SBTLSM_LISTWORK *sysmsgList;
  f32 v24;
  f32 v26;
  u32 v27;
  SBATTLE_WORK *v29;
  f32 v30;
  f32 v31;
  f32 escapegauge_counter;
  f32 v33;
  SBATTLE_WORK *v34;
  f32 escapegauge_w;
  SBATTLE_WORK *v38;
  int8x8_t v39;
  int8x8_t *p_status;
  u64 v44;
  s64 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 level;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v58;
  f32 v60;
  SBATTLE_WORK *v61;
  s16 escape_stat;

  v4 = wk;
  if (!v4)
    return (char)v4;
  if ((v4->status & 0x1400000) == 0)
    goto LABEL_41;
  if (IsSceanStop())
    goto LABEL_41;
  if (!ChkAllDeath())
    goto LABEL_19;
LABEL_41:
  LOBYTE(v4) = 0;
  return (char)v4;
LABEL_19:
  v7 = wk;
  if (v7->cmbSkl->bRun)
    goto LABEL_41;
  v7 = wk;
  if (v7->sklProc->bRun)
    goto LABEL_41;
  v7 = wk;
  if (v7->kaiwaflg)
    goto LABEL_41;
  v7 = wk;
  if (v7->endcnt || wk->actwk->status == 34)
    goto LABEL_41;
  v7 = wk;
  mode = v7->mode;
  if (mode == 5)
    goto LABEL_41;
  v7 = wk;
  mode = v7->mode;
  if (mode == 6)
    goto LABEL_41;
  v7 = wk;
  mode = v7->mode;
  if (mode == 13)
    goto LABEL_41;
  v7 = wk;
  mode = v7->mode;
  if (mode == 9)
  {
    v7 = wk;
    if (v7->escape_cnt != 15)
      goto LABEL_59;
    goto LABEL_56;
  }
  v7 = wk;
  mode = v7->mode;
  if (mode == 16)
  {
    v7 = wk;
    if (v7->escape_cnt != 45)
      goto LABEL_59;
LABEL_56:
    dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x14u);
LABEL_59:
    LOBYTE(v4) = 0;
    ++wk->escape_cnt;
    return (char)v4;
  }
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    if (wk->actwk)
    {
      actwk = Nakama->actwk;
      if (actwk->status == 40 && actwk->use_skillid == 240)
        goto LABEL_41;
    }
  }
  v13 = sBtlGetNakama(1);
  if (v13)
  {
    if (wk->actwk)
    {
      v14 = v13->actwk;
      if (v14->status == 40 && v14->use_skillid == 240)
        goto LABEL_41;
    }
  }
  p_escape_cnt = &wk->escape_cnt;
  ++*p_escape_cnt;
  LimitRange_2(p_escape_cnt, 0, 0x7FFF);
  v18 = wk;
  switch (v18->escape_stat)
  {
    case 0:
      if (fldGb->WallEncountReturnFlag)
      {
        LOBYTE(v4) = 0;
        wk->escape_stat = 257;
      }
      else
      {
        v45 = 0;
        v46 = 0.0;
        v47 = 1.0;
        v48 = 0.0;
        level = 0.0;
        while (1)
        {
          UnitMng = wk->UnitMng;
          if (v45 >= UnitMng->number)
            break;
          UnitMng = wk->UnitMng;
          pUnit = UnitMng->pUnitL[v45]->pUnit;
          if (pUnit)
          {
            if ((pUnit->side & 2) == 0)
              goto LABEL_168;
            if (sBtlCheckDamageTarget(pUnit))
            {
              if (level < (f32)pUnit->para->level)
                level = pUnit->para->level;
            }
            else
            {
LABEL_168:
              if (sBtlCheckDamageTarget(pUnit) || (pUnit->aiwk->m_status & 0x40000) != 0)
              {
                v46 = v46 + 1.0;
                v48 = v48 + (f32)pUnit->para->level;
              }
            }
          }
          ++v45;
        }
        v53 = (f32)(v48 / v46) + 1.0;
        if (v46 <= 0.0)
          v53 = 11.0;
        v54 = (f32)((f32)((f32)(level * 1.5) - v53) + (f32)(21 - wk->para->now->luck))
            + 2.0;
        v55 = ConvLevelValue(17, v54);
        if (v55 >= 1.0)
          v47 = v55;
        wk->escapegauge_num0 = v47;
        v58 = v47 * CheckAutoSkill_Escape(1.0);
        v60 = (f32)(128.0 / (f32)(v58 * 60.0)) + (f32)(128.0 / (f32)(v58 * 60.0));
        LOBYTE(v4) = 0;
        v61 = wk;
        if (v58 <= 1.0)
          v60 = 4.266667;
        v61->escapegauge_w = 128;
        escape_stat = v61->escape_stat;
        v61->escapegauge_counter = 0.0;
        v61->escapegauge_cnt = v60;
        v61->escape_stat = escape_stat + 1;
      }
      return (char)v4;
    case 1:
      v24 = CheckAutoSkill_Escape(1.0);
      v26 = v24;
      v29 = wk;
      v30 = v26 * wk->escapegauge_num0;
      if (!v27)
      {
        v29 = wk;
      }
      v31 = (f32)(128.0 / (f32)(v30 * 60.0)) + (f32)(128.0 / (f32)(v30 * 60.0));
      if (v30 <= 1.0)
        v31 = 4.266667;
      escapegauge_counter = v29->escapegauge_counter;
      v29->escapegauge_cnt = v31;
      v33 = v31 + escapegauge_counter;
      v29->escapegauge_counter = v33;
      if (v33 < (f32)v29->escapegauge_w)
        goto LABEL_41;
      if (escape_checkflg)
        goto LABEL_41;
      v34 = wk;
      sysmsgList = v34->sysmsgList;
      escapegauge_w = v34->escapegauge_w;
      ++v34->escape_stat;
      v34->escapegauge_counter = escapegauge_w;
      goto LABEL_100;
    case 2:
      if (v18->escape_cnt == 1)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
        v38 = wk;
        if (v38->escape_cnt < 60)
          goto LABEL_150;
        goto LABEL_147;
      }
      v38 = wk;
      if (v38->escape_cnt < 60)
        goto LABEL_150;
LABEL_147:
      v38 = wk;
      ++v38->escape_stat;
LABEL_150:
      LOBYTE(v4) = 1;
      return (char)v4;
    case 3:
      if (sBtlCheckUnit_Exec())
      {
        v39.n64_u32[0] = 1073741832;
        p_status = &wk->status;
        LODWORD(v44) = vorr_s8((int8x8_t)p_status->n64_u64[0], v39).n64_u32[0];
        HIDWORD(v44) = HIDWORD(p_status->n64_u64[0]) & 0xEFFFFFFF;
        p_status->n64_u64[0] = v44;
        sBtlSetEndData();
      }
      goto LABEL_150;
    default:
      if (v18->escape_stat != 257)
        goto LABEL_41;
      v18 = wk;
      v18->escape_stat = 2;
      sysmsgList = v18->sysmsgList;
LABEL_100:
      sBtlCreateSM(sysmsgList, wk, 1, 0, 0, 120);
      wk->escape_cnt = 0;
      sBtlStatusBitOn(wk, 0x4000u);
      wk->status |= 0x1000000u;
      sBtlSetEscapeFlag();
      wk->status |= 0x40000000u;
      StopBattle();
      goto LABEL_150;
  }
}

// 0x1f9a820
void sBtlSetEscapeFlag(void) {
  s32 *EventBit;
  s32 *v4;
  _BOOL4 v5;
  s32 *v6;
  s32 *v7;

  escape_checkflg = 1;
  EventBit = GBWK->EventBit;
  EventBit[69] |= 0x80000000;
  if (wk->encountno != 482)
    return;
  v4 = GBWK->EventBit;
  v4[36] |= 0x40000000u;
  v5 = 0;
  v6 = GBWK->EventBit;
  v6[36] &= ~0x20000000u;
  v7 = GBWK->EventBit;
  v7[37] &= ~4u;
}

// 0x1f774a0
static bool EscapeGauge_FadeOut(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBATTLE_WORK *v8;
  s32 mode;
  s16 *p_escape_cnt;
  SBATTLE_WORK *v14;
  s32 escape_stat;
  SBATTLE_WORK *v16;
  s64 v17;
  int8x8_t v18;
  int8x8_t *p_status;
  u64 v23;

  v4 = wk;
  if (!v4)
    return (char)v4;
  if ((v4->status & 0x1000000) == 0)
    return 0;
  if (ChkAllDeath())
    return 0;
  v8 = wk;
  if (v8->cmbSkl->bRun)
    return 0;
  v8 = wk;
  if (v8->sklProc->bRun)
    return 0;
  v8 = wk;
  if (v8->kaiwaflg)
    return 0;
  v8 = wk;
  if (v8->endcnt)
    return 0;
  if (wk->actwk->status == 34)
    return 0;
  v8 = wk;
  mode = v8->mode;
  if (mode == 5)
    return 0;
  v8 = wk;
  mode = v8->mode;
  if (mode == 6)
    return 0;
  v8 = wk;
  mode = v8->mode;
  if (mode == 13)
    return 0;
  v8 = wk;
  mode = v8->mode;
  if (mode == 9)
  {
    if (v8->escape_cnt != 15)
      goto LABEL_50;
    goto LABEL_9000;
    if (wk->escape_cnt != 15)
    {
LABEL_50:
LABEL_51:
      ++wk->escape_cnt;
      return 0;
    }
LABEL_9000:
    dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x14u);
    goto LABEL_51;
  }
  v8 = wk;
  mode = v8->mode;
  if (mode == 16)
    return 0;
  v8 = wk;
  p_escape_cnt = &v8->escape_cnt;
  ++v8->escape_cnt;
  LimitRange_2(p_escape_cnt, 0, 0x7FFF);
  v14 = wk;
  escape_stat = (u16)v14->escape_stat;
  if (escape_stat != 3)
  {
    if (escape_stat != 2)
      return 1;
    if (v14->escape_cnt != 1)
      goto LABEL_64;
    goto LABEL_9001;
    if (wk->escape_cnt != 1)
    {
LABEL_64:
      goto LABEL_65;
    }
LABEL_9001:
    dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
LABEL_65:
    v16 = wk;
    if (v16->escape_cnt < 60)
      return 1;
    v16 = wk;
    ++v16->escape_stat;
    return 1;
  }
  if (!sBtlCheckUnit_Exec())
    return 1;
  if (wk->timeflg >= 1)
  {
    sub_1A21FE0(2239, 0, v17);
  }
  v18.n64_u32[0] = 1073741832;
  p_status = &wk->status;
  LODWORD(v23) = vorr_s8((int8x8_t)p_status->n64_u64[0], v18).n64_u32[0];
  HIDWORD(v23) = HIDWORD(p_status->n64_u64[0]) & 0xEFFFFFFF;
  p_status->n64_u64[0] = v23;
  sBtlSetEndData();
  return 1;
}

// 0x1f9aa20
s32 sBtlEscapeCheck(void) {
  SB_ENCOUNTPAC *EncountPac;

  EncountPac = sBtlGetEncountPac(-1);
  if ((EncountPac[wk->encountno]->flag & 0x10) != 0)
    return 2;
  return (wk->status >> 22) & 1;
}

// 0x1f9ab00
bool sBtlDrawEscapeGauge(s32 x, s32 y) {
  SBTLUNIT_WORK *v5;
  SBATTLE_WORK *v8;
  void *Instance;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBATTLE_WORK *v13;
  s32 mode;
  f32 escapegauge_counter;
  void *v18;
  s32 escapegauge_w;
  s32 v20;

  if (!wk)
    goto LABEL_29;
  if ((wk->status & 0x1400000) == 0)
    goto LABEL_29;
  if (IsSceanStop())
  {
    LOBYTE(v5) = 0;
    return (char)v5;
  }
  if (!ChkAllDeath())
    goto LABEL_20;
LABEL_29:
  LOBYTE(v5) = 0;
  return (char)v5;
LABEL_20:
  v8 = wk;
  if (v8->cmbSkl->bRun)
    goto LABEL_29;
  v8 = wk;
  if (v8->sklProc->bRun)
    goto LABEL_29;
  v8 = wk;
  if (v8->kaiwaflg)
    goto LABEL_29;
  v8 = wk;
  if (v8->endcnt)
  {
    Instance = get_Instance(0);
    EscapeGaugeOff(Instance, 0);
    LOBYTE(v5) = 0;
  }
  else
  {
    v8 = wk;
    UnitMng = v8->UnitMng;
    playerID = v8->playerID;
    v5 = sBtlSearchUnit_ID(UnitMng, playerID);
    if (v5)
    {
      if (v5->actwk->status == 34)
        goto LABEL_29;
      v13 = wk;
      mode = v13->mode;
      if (mode == 5)
        goto LABEL_29;
      v13 = wk;
      mode = v13->mode;
      if (mode == 6)
        goto LABEL_29;
      v13 = wk;
      mode = v13->mode;
      if (mode == 13)
        goto LABEL_29;
      v13 = wk;
      mode = v13->mode;
      if (mode == 9)
        goto LABEL_29;
      v13 = wk;
      mode = v13->mode;
      if (mode == 16)
        goto LABEL_29;
      v13 = wk;
      if ((v13->status & 8) != 0)
        goto LABEL_29;
      if (fldGb->WallEncountReturnFlag)
        goto LABEL_29;
      if (!get_Instance(0)->escapediso)
        goto LABEL_29;
      escapegauge_counter = wk->escapegauge_counter;
      v18 = get_Instance(0);
      EscapeGaugeOnOff(v18, 1, 1, 0);
      escapegauge_w = wk->escapegauge_w;
      if (escapegauge_counter == INFINITY)
        v20 = 0;
      else
        v20 = escapegauge_counter;
      sBtlEscapeGauge(v20, escapegauge_w);
      LOBYTE(v5) = 1;
    }
  }
  return (char)v5;
}

// 0x1f987a0
static s32 GuardInit(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v6;
  s32 m_type;
  s32 v14;

  wk->cmstatus = 0;
  v6 = wk;
  v6->mode = 11;
  v6->kochokuCnt = 0;
  v6->sord_bugfix = 0;
  v6->sord_counter = 0;
  v6->bHuumaCancel = 0;
  v6->ComboMotRetryCnt = 0;
  v6->ComboMotRetryUse = 0;
  *(u64 *)&v6->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  if (wk->battlemode == 1)
  {
    sBtlSetMotion(wk, 29, 0, 0, 0);
    goto LABEL_12;
  }
  m_type = sBtlDat()->m_type;
  if (m_type == 3)
  {
    if (wk->motionID == 41)
      goto LABEL_13;
    v14 = 117;
    goto LABEL_31;
  }
  if (m_type == 2)
  {
    if (wk->motionID == 40)
      goto LABEL_13;
    v14 = 114;
LABEL_31:
    sBtlSetMotion(wk, v14, 0, 0, 0);
    sBtlPlaySE(0x1000Du);
LABEL_12:
    sndVoicePlayFile("PVA01A_22D_005", 0);
    goto LABEL_13;
  }
  if (m_type == 1 && wk->motionID != 29)
  {
    v14 = 111;
    goto LABEL_31;
  }
LABEL_13:
  sBtlSetPlayerDir_ToTarget(wk);
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->setsuma_rowhit_skillid = 0;
  *(u16 *)&wk->setsuma_rowhit_done = 0;
  return 2;
}

// 0x1f808d0
static s32 GuardProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  s32 motionID;
  s32 v8;
  s32 v10;
  s32 v11;
  SBATTLE_WORK *v13;
  s32 kochokuCnt;
  s32 vstatus;
  SBATTLE_WORK *v16;
  s32 battlemode;
  SBATTLE_WORK *v18;
  SBTLUNIT_WORK *v20;
  s32 v21;
  SBATTLE_WORK *v23;
  s32 v24;
  s32 v26;
  s32 motionno;

  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  if (sBtlDat()->m_type == 1)
  {
    motionID = wk->motionID;
    if (motionID == 111)
    {
      if (MotionFrameF >= 15.5)
        goto LABEL_143;
      if (sBtlCheckMotionEnd_AnimatorNormal(wk))
      {
LABEL_143:
        sBtlSetMotion(wk, 29, 0, 0, 0);
      }
      motionID = wk->motionID;
    }
    if (motionID == 113)
    {
      if (MotionFrameF >= 25.5)
        goto LABEL_20;
      if (sBtlCheckMotionEnd_AnimatorNormal(wk))
      {
LABEL_20:
        v8 = 29;
LABEL_22:
        sBtlSetMotion(wk, v8, 0, 0, 0);
        goto LABEL_57;
      }
    }
  }
  else if (sBtlDat()->m_type == 2)
  {
    v10 = wk->motionID;
    if (v10 == 114)
    {
      if (MotionFrameF >= 15.5)
        goto LABEL_144;
      if (sBtlCheckMotionEnd_AnimatorNormal(wk))
      {
LABEL_144:
        sBtlSetMotion(wk, 40, 0, 0, 0);
      }
      v10 = wk->motionID;
    }
    if (v10 == 116)
    {
      if (MotionFrameF >= 25.5)
        goto LABEL_38;
      if (sBtlCheckMotionEnd_AnimatorNormal(wk))
      {
LABEL_38:
        v8 = 40;
        goto LABEL_22;
      }
    }
  }
  else if (sBtlDat()->m_type == 3)
  {
    v11 = wk->motionID;
    if (v11 == 117)
    {
      if (MotionFrameF >= 15.5)
        goto LABEL_145;
      if (sBtlCheckMotionEnd_AnimatorNormal(wk))
      {
LABEL_145:
        sBtlSetMotion(wk, 41, 0, 0, 0);
      }
      v11 = wk->motionID;
    }
    if (v11 == 119)
    {
      if (MotionFrameF >= 25.5)
        goto LABEL_55;
      if (sBtlCheckMotionEnd_AnimatorNormal(wk))
      {
LABEL_55:
        v8 = 41;
        goto LABEL_22;
      }
    }
  }
LABEL_57:
  v13 = wk;
  kochokuCnt = v13->kochokuCnt;
  if (kochokuCnt >= 1)
  {
    v13 = wk;
    kochokuCnt = v13->kochokuCnt;
    v13->kochokuCnt = kochokuCnt - 1;
  }
  vstatus = wk->vstatus;
  wk->status |= 0x100u;
  wk->vstatus = vstatus | 0x80;
  v16 = wk;
  battlemode = (u16)v16->battlemode;
  if (battlemode == 1)
    goto LABEL_69;
  goto LABEL_9000;
  if (battlemode == 1)
  {
LABEL_69:
    v18 = wk;
    if (v18->bGuard)
      return 2;
    if (v18->kochokuCnt)
      return 2;
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    v20 = wk;
    v21 = 0;
    goto LABEL_88;
  }
LABEL_9000:
  if (battlemode == 3)
    goto LABEL_69;
  if (v16->bGuard)
    goto LABEL_93;
  v16 = wk;
  if (!v16->kochokuCnt)
  {
    sBtlResetAction(wk);
    wk->motion_SetSkip = 1;
    sBtlSetUseSkill(wk, 0, 0);
    motionno = wk->motionno;
    if (motionno > 43)
    {
      switch (motionno)
      {
        case ',':
        case 'u':
        case 'v':
        case 'w':
          goto LABEL_125;
        case 'o':
        case 'p':
        case 'q':
          goto LABEL_131;
        case 'r':
        case 's':
        case 't':
          goto LABEL_136;
        default:
          goto LABEL_130;
      }
    }
    if (motionno == 11)
      goto LABEL_131;
    if (motionno != 43)
    {
LABEL_130:
      if (sBtlDat()->m_type == 1)
      {
LABEL_131:
        v20 = wk;
        v21 = 112;
LABEL_88:
        sBtlSetMotion(v20, v21, 0, 0, 0);
        return 2;
      }
      if (sBtlDat()->m_type != 2)
      {
        if (sBtlDat()->m_type != 3)
          return 2;
LABEL_125:
        v21 = 118;
        v20 = wk;
        goto LABEL_88;
      }
    }
LABEL_136:
    v21 = 115;
    v20 = wk;
    goto LABEL_88;
  }
LABEL_93:
  v23 = wk;
  if (v23->battlemode == 1)
    return 2;
  v23 = wk;
  if (!v23->kochokuCnt)
  {
    v23 = wk;
    if (v23->bSetsuma)
    {
      v24 = sBtlInputChkSetsuma(wk);
      if (v24)
      {
        v26 = v24;
        sBtlSetFirstAtk(v26);
        return 2;
      }
    }
  }
  if (!wk->bSpiritSkill)
    return 2;
  sBtlPlayerRSpiritInit(wk);
  return 2;
}

// 0x1f9afa0
void sBtlGuardHit(SBTLUNIT_WORK *wk, bool _DownHit) {
  SBATTLE_WORK *v6;
  s32 v7;
  char **v9;
  s32 v10;

  wk->status |= 0x100u;
  wk->vstatus |= 0x80u;
  v6 = wk;
  v6->kochokuCnt = 30;
  if (DownHit)
  {
    if (v6->battlemode == 1)
      goto LABEL_32;
    if (sBtlDat()->m_type == 1)
    {
      if (wk->motionno == 113)
        goto LABEL_32;
      v10 = 113;
    }
    else if (sBtlDat()->m_type == 2)
    {
      if (wk->motionno == 116)
        goto LABEL_32;
      v10 = 116;
    }
    else
    {
      if (sBtlDat()->m_type != 3)
        return;
      if (wk->motionno == 119)
      {
LABEL_32:
        v9 = &"PVA01A_22D_003";
        goto LABEL_34;
      }
      v10 = 119;
    }
    sBtlSetMotion(wk, v10, 0, 0, 0);
    goto LABEL_32;
  }
  v7 = sub_1905740(2, 0);
  if (v7 != 1)
  {
    if (v7)
      return;
    v9 = &"PVA01A_20A_000";
    goto LABEL_34;
  }
  v9 = &"PVA01A_23C_000";
LABEL_34:
  sndVoicePlayFile(*v9, 0);
}

// 0x1f6f690
void sBtlInitGun(void) {
  s64 i;
  char *v7;
  SBATTLE_WORK *wk_local;
  s32 *GunLockOnTgtPushPop;

  *(u64 *)&wk->GunRapidNum = (char *)&off_20 + 4;
  gGunInfiniteCnt = 0;
  *(u64 *)&gGunModeTime = 0;
  *(u64 *)&gGunMode_SlideNml = 0;
  *(u64 *)&gGunModeStep = 0;
  *(u64 *)((char *)&gGunMode_TgtZoomNml + 1) = 0;
  for (i = 0; ; ++i)
  {
    wk_local = wk;
    GunLockOnTgtPushPop = wk_local->GunLockOnTgtPushPop;
    if (i >= SLODWORD(GunLockOnTgtPushPop->max_length))
      break;
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    v7 = (char *)GunLockOnTgtPushPop + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
  *(u64 *)&wk_local->Camera_EnemyDeadNear_ListID = 0xFFFFFFFFLL;
}

// 0x1f8b220
void sBtlChangeGunMode(SBTLUNIT_WORK *wk) {
  if ((wk->vstatus & 0x8000) == 0)
  {
    sBtlStartGunMode(wk);
    return;
  }
  sBtlResetGunMode(wk, 1);
}

// 0x1f99cc0
void sBtlStartGunMode(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v6;
  SBATTLE_WORK *v8;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 v16;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 PosToDir;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 Dir180;
  sdfVector4_t *p_rot;
  sdfVector4_t v34;

  if ((wk->vstatus & 0x8000) == 0)
  {
    *(u64 *)&gGunModeTime = 0;
    *(u64 *)&gGunModeStep = 1;
    v6 = wk;
    v6->bHuumaCancel = 0;
    v6->ComboMotRetryCnt = 0;
    v6->ComboMotRetryUse = 0;
    *(u64 *)&v6->Camera_EnemyDeadNear_ListID = 0xFFFFFFFFLL;
    sBtlResetJump(wk);
    sBtlSetAction(wk, 1, 0);
    wk->vstatus |= 0x8000u;
    sBtlNoHokan();
    v8 = wk;
    if (v8->CameraLockOn)
    {
      x = wk->rot.x;
      y = wk->rot.y;
      z = wk->rot.z;
      w = wk->rot.w;
LABEL_14:
      v34.x = x;
      v34.y = y;
      v34.z = z;
      v34.w = w;
      RotToDir = sBtlGetRotToDir(v34);
      v16 = RotToDir;
      gGunMode_Dir = v16;
      Add(0);
      return;
    }
    targetID = wk->actaiwk->targetID;
    if (targetID != -1)
    {
      UnitMng = v8->UnitMng;
      v20 = sBtlSearchUnit_ID(UnitMng, targetID);
      if (v20)
      {
        v21 = v20->pos.x;
        v22 = v20->pos.z;
        v23 = wk->pos.x;
        v24 = wk->pos.z;
        PosToDir = sBtlGetPosToDir(v23, v24, v21, v22);
        goto LABEL_32;
      }
    }
    v26 = wk->pos.x;
    v27 = wk->pos.y;
    v28 = wk->pos.z;
    v29 = 360.0 - mapGetScreenDir(v26, v27, v28, 0.0);
    PosToDir = v29;
LABEL_32:
    Dir180 = sBtlGetDir180(PosToDir);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    p_rot = &wk->rot;
    *p_rot = vct_A;
    wk->rotbk = vct_A;
    x = wk->rot.x;
    y = wk->rot.y;
    z = wk->rot.z;
    w = wk->rot.w;
    goto LABEL_14;
  }
}

// 0x1f77dd0
void sBtlResetGunMode(SBTLUNIT_WORK *wk, bool _SetEndMotion) {
  s32 vstatus;
  s64 v10;
  SBATTLE_WORK *v11;
  s32 *GunLockOnTgtSubIdx;
  s64 v13;
  s32 *GunLockOnTgtDone;
  SBATTLE_WORK *v15;
  s32 *GunLockOnTgtID;
  s64 i;
  char *v19;
  SBATTLE_WORK *v20;
  s32 *GunLockOnTgtPushPop;

  vstatus = wk->vstatus;
  if ((vstatus & 0x8000) == 0)
    return;
  vstatus = wk->vstatus;
  *(u64 *)&gGunModeTime = 0;
  *(u64 *)&gGunModeStep = 30;
  wk->vstatus = vstatus & 0xFFFF7FFF;
  sBtlNoHokan();
  v10 = 8;
  v11 = wk;
  *(u64 *)&v11->chargeGunCnt = 0;
  v11->GunLockOnNum = 0;
  while (1)
  {
    v15 = wk;
    GunLockOnTgtID = v15->GunLockOnTgtID;
    if (v10 - 8 >= SLODWORD(GunLockOnTgtID->max_length))
      break;
    v15 = wk;
    GunLockOnTgtID = v15->GunLockOnTgtID;
    GunLockOnTgtSubIdx = v15->GunLockOnTgtSubIdx;
    v13 = 4 * v10++;
    GunLockOnTgtDone = v15->GunLockOnTgtDone;
    *(u32 *)((char *)&GunLockOnTgtID->obj.klass + v13) = -1;
    *(u32 *)((char *)&GunLockOnTgtSubIdx->obj.klass + v13) = 0;
    *(u32 *)((char *)&GunLockOnTgtDone->obj.klass + v13) = 0;
  }
  for (i = 0; ; ++i)
  {
    v20 = wk;
    GunLockOnTgtPushPop = v20->GunLockOnTgtPushPop;
    if (i >= SLODWORD(GunLockOnTgtPushPop->max_length))
      break;
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    v19 = (char *)GunLockOnTgtPushPop + 4 * i;
    *((u32 *)v19 + 8) = -1;
  }
  if (SetEndMotion)
    wk->cmstatus |= 0x8000u;
  v20 = wk;
  *(u64 *)&v20->Camera_EnemyDeadNear_ListID = 0xFFFFFFFFLL;
  DeleteAll();
  DeleteAll();
}

// 0x1f77ae0
void sBtlResetGunMode_Eve(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v7;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v14;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    return;
  v7 = v5;
  sBtlResetGunMode(v7, 0);
  gGunModeStep = 0;
  *(u64 *)&gGunMode_SlideNml = 0;
  x = v7->rot.x;
  y = v7->rot.y;
  z = v7->rot.z;
  w = v7->rot.w;
  v14.x = x;
  v14.y = y;
  v14.z = z;
  v14.w = w;
  gGunMode_Dir = sBtlGetRotToDir(v14);
}

// 0x1f8b2f0
void sBtlSetGunMode_Fire(SBTLUNIT_WORK *wk) {
  *(u64 *)&gGunModeTime = 0;
  *(u64 *)&gGunModeStep = 20;
  wk->hitokoto_gunuse = 1;
}

// 0x1f7a3f0
static bool SetGunPlayerHit(SBTLUNIT_WORK *wk) {
  void **v4;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  SBATTLE_WORK *v11;
  s32 targetID;
  SBTLUNIT_LISTWORK *v13;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v19;
  SBTLUNIT_WORK *v21;
  SBTLUNIT_LISTWORK *v23;
  s32 v24;
  SBTLUNIT_WORK *v25;
  s32 FrontTarget;
  f32 v27;
  f32 v28;
  u16 v29;
  f32 v30;
  s32 v31;
  V_POSITION_WORK *v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  SBATTLE_WORK *v43;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  f32 v45;
  s64 v46;
  f32 v47;
  SBTLUNIT_LISTWORK *other_List2;
  u32 v50;
  SBTLUNIT_WORK *pUnit;
  void **v52;
  f32 v53;
  u16 v54;
  s32 v55;
  V_POSITION_WORK *v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  SBTLACTAI_WORK *actaiwk;
  u32 *v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  s32 LineCircle;
  f32 v71;
  f32 v72;
  s64 v73;
  f32 LenXZ;
  f32 v75;
  f32 v76;
  s64 v77;
  f32 v78;
  SBTLUNIT_LISTWORK *p_other_List2;
  s32 *GunLockOnTgtID;
  int32x4_t v83;
  s32 v84;
  s32 v85;
  int32x4_t v86;
  uint8x8_t v87;
  s32 v88;
  s32 v89;
  f32 v91;
  f32 v92;
  u16 major;
  f32 hit_area_r;
  s32 minor;
  V_POSITION_WORK *nml;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  f32 v105;
  SBATTLE_WORK *v106;
  f32 v108;
  s32 v109;
  sdfVector4_t v110;
  sdfVector4_t v111;
  sdfVector4_t ppos;
  s64 HitZ2;
  s64 HitZ1;
  f32 ToZ;
  f32 ToX;
  sdfVector4_t v117;

  ToX = 0.0;
  ToZ = 0.0;
  HitZ2 = 0;
  HitZ1 = 0;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  *(u64 *)&v111.x = 0;
  *(u64 *)&v111.z = 0;
  *(u64 *)&v110.x = 0;
  *(u64 *)&v110.z = 0;
  if (wk->GunLockOnNum > 5)
    goto LABEL_149;
  v4 = &sBtlSub;
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v117.x = x;
  v117.y = y;
  v117.z = z;
  v117.w = w;
  RotToDir = sBtlGetRotToDir(v117);
  sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir, 2000.0, &ToX, &ToZ);
  v11 = wk;
  targetID = wk->actaiwk->targetID;
  if (!v11->CameraGazeOff)
  {
    if (targetID == -1)
      goto LABEL_149;
    UnitMng = v11->UnitMng;
    v19 = sBtlSearchUnit_ID(UnitMng, targetID);
    if (!v19)
      return (char)v19;
    v25 = v19;
    if (v19->para->devilid == 314)
    {
      FrontTarget = sBtlGetFrontTarget(wk, 314);
      if (FrontTarget != -1)
        goto LABEL_115;
    }
    else
    {
      if (sBtlCheckLiveTarget_NotHitDmg(v25) && (v25->vstatus & 0x10000) == 0)
      {
        if (sBtlCheckDamageTarget(v25) && (v25->status & 0x4000000) == 0)
        {
          v91 = v25->pos.x;
          v92 = v25->pos.z;
          major = v25->major;
          hit_area_r = v25->actaiwk->hit_area_r;
          minor = v25->minor;
          nml = sBtlGetVisualData(major, minor)->nml;
          *(u64 *)&v110.x = 0;
          *(u64 *)&v110.z = 0;
          v97 = v25->pos.z;
          v98 = v25->pos.x;
          v99 = nml->height * -0.5;
          if ((u32)(v25->para->devilid - 413) < 4)
            v99 = -180.0;
          v100 = v25->pos.y + v99;
          if (sBtlChangeWorldtoScreenUnity3(v98, v100, v97, &v110))
          {
            v101 = wk->pos.x;
            v102 = wk->pos.z;
            v103 = ToZ;
            if (hit_area_r >= 150.0)
              v104 = hit_area_r;
            else
              v104 = 150.0;
            v105 = ToX;
            LODWORD(v19) = sBtlGetLineCircle(v101, v102, v105, v103, v91, v92, v104, (f32 *)&HitZ1 + 1, &HitZ1, (f32 *)&HitZ2 + 1, &HitZ2);
            if (!(u32)v19)
              return (char)v19;
            FrontTarget = v25->ListID;
            if (FrontTarget != -1)
              goto LABEL_115;
          }
        }
      }
    }
    goto LABEL_149;
  }
  if (targetID == -1)
    goto LABEL_62;
  v13 = v11->UnitMng;
  v15 = sBtlSearchUnit_ID(v13, targetID);
  if (!v15)
    goto LABEL_62;
  v21 = v15;
  if (v15->para->devilid == 314)
  {
    v23 = wk->UnitMng;
    v24 = sBtlGetFrontTarget(wk, 314);
    v21 = sBtlSearchUnit_ID(v23, v24);
    if (!v21)
      goto LABEL_62;
  }
  if (!sBtlCheckLiveTarget_NotHitDmg(v21))
    goto LABEL_62;
  if ((v21->vstatus & 0x10000) == 0)
  {
    if (sBtlCheckDamageTarget(v21) && (v21->status & 0x4000000) == 0)
    {
      v27 = v21->pos.x;
      v28 = v21->pos.z;
      v29 = v21->major;
      v30 = v21->actaiwk->hit_area_r;
      v31 = v21->minor;
      v32 = sBtlGetVisualData(v29, v31)->nml;
      *(u64 *)&ppos.x = 0;
      *(u64 *)&ppos.z = 0;
      v33 = v21->pos.x;
      v34 = v21->pos.z;
      v35 = v32->height * -0.5;
      if ((u32)(v21->para->devilid - 413) < 4)
        v35 = -180.0;
      v36 = v21->pos.y + v35;
      if (sBtlChangeWorldtoScreenUnity3(v33, v36, v34, &ppos))
      {
        v37 = wk->pos.x;
        v38 = wk->pos.z;
        v39 = ToZ;
        if (v30 >= 150.0)
          v40 = v30;
        else
          v40 = 150.0;
        v41 = ToX;
        if (sBtlGetLineCircle(v37, v38, v41, v39, v27, v28, v40, (f32 *)&HitZ1 + 1, &HitZ1, (f32 *)&HitZ2 + 1, &HitZ2))
        {
          FrontTarget = v21->ListID;
          if (FrontTarget != -1)
            goto LABEL_115;
        }
      }
    }
  }
LABEL_62:
  v43 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v43->other_List2 = TargetList_MASK;
  v45 = 9999.0;
  v46 = 0;
  FrontTarget = -1;
  v47 = -180.0;
  while (1)
  {
    other_List2 = wk->other_List2;
    if (v46 >= other_List2->count)
      break;
    if (v50)
    {
      pUnit = other_List2->pUnitL[v46]->pUnit;
      if (!pUnit)
        goto LABEL_68;
    }
    else
    {
      pUnit = wk->other_List2->pUnitL[v46]->pUnit;
      if (!pUnit)
        goto LABEL_68;
    }
    if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
      goto LABEL_68;
    if ((pUnit->vstatus & 0x10000) == 0)
    {
      if (!sBtlCheckDamageTarget(pUnit))
        goto LABEL_68;
      if ((pUnit->status & 0x4000000) == 0 && (u32)(pUnit->para->devilid - 261) <= 0xFFFFFFFC)
      {
        v109 = FrontTarget;
        v52 = v4;
        v53 = v47;
        v54 = pUnit->major;
        v55 = pUnit->minor;
        v56 = sBtlGetVisualData(v54, v55)->nml;
        v47 = v53;
        v4 = v52;
        *(u64 *)&v111.x = 0;
        *(u64 *)&v111.z = 0;
        v57 = pUnit->pos.x;
        v58 = pUnit->pos.y;
        v59 = pUnit->pos.z;
        if ((u32)(pUnit->para->devilid - 413) >= 4)
          v60 = v56->height * -0.5;
        else
          v60 = v47;
        if (!*((u32 *)*v52 + 56))
        if (!sBtlChangeWorldtoScreenUnity3(v57, v58 + v60, v59, &v111))
        {
          FrontTarget = v109;
          goto LABEL_68;
        }
        actaiwk = pUnit->actaiwk;
        v108 = v45;
        v62 = *v52;
        v63 = pUnit->pos.x;
        v64 = pUnit->pos.z;
        v65 = wk->pos.x;
        v66 = wk->pos.z;
        v67 = ToX;
        v68 = ToZ;
        if (actaiwk->hit_area_r >= 150.0)
          v69 = actaiwk->hit_area_r;
        else
          v69 = 150.0;
        if (!v62[56])
        LineCircle = sBtlGetLineCircle(v65, v66, v67, v68, v63, v64, v69, (f32 *)&HitZ1 + 1, &HitZ1, (f32 *)&HitZ2 + 1, &HitZ2);
        FrontTarget = v109;
        if (!LineCircle)
        {
          v45 = v108;
          goto LABEL_68;
        }
        if (LineCircle == 1)
        {
          v71 = wk->pos.x;
          v72 = wk->pos.z;
          v73 = HitZ1;
          v45 = v108;
          if (!*((u32 *)*v4 + 56))
          LenXZ = sBtlGetLenXZ(v71, v72, *((f32 *)&v73 + 1), *(f32 *)&v73);
          goto LABEL_109;
        }
        v75 = wk->pos.x;
        v76 = wk->pos.z;
        v77 = HitZ1;
        v45 = v108;
        if (!*((u32 *)*v4 + 56))
        v78 = sBtlGetLenXZ(v75, v76, *((f32 *)&v77 + 1), *(f32 *)&v77);
        LenXZ = sBtlGetLenXZ(wk->pos.x, wk->pos.z, *((f32 *)&HitZ2 + 1), *(f32 *)&HitZ2);
        if (v78 >= LenXZ)
LABEL_109:
          v78 = LenXZ;
        if (v78 < v45)
        {
          FrontTarget = pUnit->ListID;
          v45 = v78;
        }
      }
    }
LABEL_68:
    ++v46;
  }
  if (v50)
  {
    goto LABEL_114;
  }
  else
  {
    other_List2 = wk->other_List2;
  }
LABEL_114:
  sBtlDeleteUnitList(other_List2, 0);
  p_other_List2 = &wk->other_List2;
  p_other_List2 = 0;
  if (FrontTarget == -1)
  {
LABEL_149:
    LOBYTE(v19) = 0;
    return (char)v19;
  }
LABEL_115:
  GunLockOnTgtID = wk->GunLockOnTgtID;
  v83 = *(int32x4_t *)GunLockOnTgtID;
  v85 = GunLockOnTgtID[4];
  v84 = GunLockOnTgtID[5];
  v86 = vandq_s8(vceqq_s32(v83, vdupq_n_s32(FrontTarget)), (int8x16_t)xmmword_3CFFD40);
  v86.n128_u32[0] = vaddvq_s32(v86) & 0xF;
  v87.n64_u64[0] = vcnt_s8((int8x8_t)v86.n128_u64[0]).n64_u64[0];
  v87.n64_u16[0] = vaddlv_u8(v87);
  v88 = v87.n64_u32[0];
  if (v85 == FrontTarget)
    v88 = v87.n64_u32[0] + 1;
  if (v84 == FrontTarget)
    v89 = v88 + 1;
  else
    v89 = v88;
  v106 = wk;
  v106->GunLockOnTgtID[v106->GunLockOnNum] = FrontTarget;
  v106->GunLockOnTgtSubIdx[v106->GunLockOnNum] = v89;
  v106->GunLockOnTgtDone[v106->GunLockOnNum++] = 0;
  Add(FrontTarget, v89, 0);
  LOBYTE(v19) = 1;
  return (char)v19;
}

// 0x1f9b220
static void SetGunPlayerDir(SBTLUNIT_WORK *wk) {
  char v3;
  SBATTLE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v9;
  _BOOL4 v10;
  s32 devilid;
  f32 x;
  f32 z;
  SBTLCAMERA_WORK *camera;
  f32 v16;
  f32 v17;
  sdfVector4_t *p_rot;
  f32 v20;
  f32 y;
  f32 v22;
  f32 w;
  f32 RotToDir;
  SBTLCAMERA_WORK *v26;
  f32 Dir180;
  SBTLUNIT_LISTWORK *v30;
  s32 v31;
  SBTLUNIT_WORK *v32;
  s32 v33;
  f32 PosToDir;
  f32 v36;
  f32 v37;
  SBTLCAMERA_WORK *v38;
  f32 v39;
  f32 v40;
  f32 v41;
  sdfVector4_t *v42;
  SBTLUNIT_LISTWORK *v44;
  s32 v45;
  SBTLUNIT_WORK *v46;
  SBTLUNIT_WORK *v47;
  SBATTLE_WORK *v49;
  sdfVector4_t *p_rotbk;
  s32 v52;
  f32 v53;
  f32 v54;
  SBTLCAMERA_WORK *v55;
  f32 v56;
  f32 v57;
  SBATTLE_WORK *v59;
  sdfVector2_t followUpAngle;
  sdfVector4_t v61;

  v3 = BYTE1(wk->vstatus);
  followUpAngle = 0;
  if (v3 < 0)
  {
    v6 = wk;
    if (v6->enemy_zenmetu)
    {
      v6 = wk;
      UnitMng = v6->UnitMng;
      targetID = wk->actaiwk->targetID;
      v9 = sBtlSearchUnit_ID(UnitMng, targetID);
      v10 = 0;
      if (v9)
      {
        devilid = (u16)v9->para->devilid;
        if (devilid != 258 && devilid != 314)
        {
          x = wk->pos.x;
          z = wk->pos.z;
          camera = wk->scene->camera;
          v16 = camera->CameraLockOnTargetPos.x;
          v17 = camera->CameraLockOnTargetPos.z;
          if (sBtlGetLenXZ(x, z, v16, v17) < 200.0)
          {
            v10 = 0;
            wk->CameraGazeOff = 1;
            goto LABEL_27;
          }
LABEL_26:
          v10 = 0;
        }
      }
LABEL_27:
      if (v10 || wk->CameraGazeOff)
      {
        v20 = wk->rot.x;
        y = wk->rot.y;
        p_rot = &wk->rot;
        v22 = wk->rot.z;
        w = wk->rot.w;
        v61.x = v20;
        v61.y = y;
        v61.z = v22;
        v61.w = w;
        RotToDir = sBtlGetRotToDir(v61);
        followUpAngle.x = RotToDir;
        followUpAngle.y = 0.0;
        v26 = wk->scene->camera;
        sBtlInputFollowUp(v26, &followUpAngle);
        Dir180 = sBtlGetDir180(followUpAngle.x);
        wk->mv_rotbk = Dir180;
        FromEuler(0.0, Dir180 * 0.017453292, 0.0);
        *p_rot = vct_A;
LABEL_81:
        p_rotbk = &wk->rotbk;
        *p_rotbk = vct_A;
        return;
      }
      if (!IsAction(15))
        goto LABEL_51;
      v30 = wk->UnitMng;
      v31 = wk->actaiwk->targetID;
      v32 = sBtlSearchUnit_ID(v30, v31);
      if (v32 && ((v33 = (u16)v32->para->devilid, v33 == 314) || v33 == 258))
      {
        PosToDir = 0.0;
      }
      else
      {
LABEL_51:
        v36 = wk->pos.x;
        v37 = wk->pos.z;
        v38 = wk->scene->camera;
        v39 = v38->CameraLockOnTargetPos.x;
        v40 = v38->CameraLockOnTargetPos.z;
        PosToDir = sBtlGetPosToDir(v36, v37, v39, v40);
      }
      v41 = sBtlGetDir180(PosToDir);
      wk->mv_rotbk = v41;
      FromEuler(0.0, v41 * 0.017453292, 0.0);
      v42 = &wk->rot;
      *v42 = vct_A;
      goto LABEL_81;
    }
    if (v6->CameraGazeOff)
      goto LABEL_26;
    v6 = wk;
    v44 = v6->UnitMng;
    v45 = wk->actaiwk->targetID;
    v46 = sBtlSearchUnit_ID(v44, v45);
    if (!v46)
      goto LABEL_75;
    v47 = v46;
    v49 = wk;
    if (v49->Camera_EnemyDeadNear_ListID == v47->ListID)
    {
      v49 = wk;
      if (v49->Camera_EnemyDeadNear_UID == v47->UID)
      {
LABEL_75:
        v10 = 1;
        goto LABEL_27;
      }
    }
    if (v47->actwk->status == 10)
    {
      v10 = 0;
      v52 = (u16)v47->para->devilid;
      if (v52 == 258 || v52 == 314)
        goto LABEL_27;
      v53 = wk->pos.x;
      v54 = wk->pos.z;
      v55 = wk->scene->camera;
      v56 = v55->CameraLockOnTargetPos.x;
      v57 = v55->CameraLockOnTargetPos.z;
      if (sBtlGetLenXZ(v53, v54, v56, v57) >= 100.0)
        goto LABEL_26;
      v10 = 1;
      v59 = wk;
      v59->Camera_EnemyDeadNear_ListID = v47->ListID;
      v59->Camera_EnemyDeadNear_UID = v47->UID;
    }
    else
    {
      if (wk->Camera_EnemyDeadNear_ListID == -1)
        goto LABEL_26;
      v10 = ((loc_1F04F20)(0) & 1) == 0;
    }
    goto LABEL_27;
  }
}

// 0x1f9b9a0
bool sBtlGetGunMode_Camera(f32 *_SlideNml, f32 *_TgtZoomNml, f32 *_Dir) {
  *SlideNml = gGunMode_SlideNml;
  *TgtZoomNml = gGunMode_TgtZoomNml;
  *Dir = gGunMode_Dir;
  return gGunModeStep != 0;
}

// 0x1f9ba40
s32 sBtlGetRapidNum_Par(void) {
  f32 v2;

  v2 = (f32)wk->GunRapidNum / 0.36;
  if (v2 >= 99.0)
    v2 = 100.0;
  if (v2 == INFINITY)
    return 0x80000000;
  else
    return (s32)v2;
}

// 0x1f9baf0
void sBtlSetRapidNum_Max(void) {
  wk->GunRapidNum = 36;
}

// 0x1f9bb60
void sBtlSetInfinite(s32 _Cnt) {
  gGunInfiniteCnt = Cnt;
  gGunInfinite = 1;
}

// 0x1f9bbd0
static void UpdateGunRapid(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  s32 v7;
  bool v8;
  s32 GunRapidNum;
  SBTLSM_LISTWORK *sysmsgList;

  if (IsSceanStop())
    return;
  v5 = wk;
  if (v5->cmbSkl->bRun)
    return;
  if (v5->GunRapidNum > 35)
  {
    v5 = wk;
    v5->GunRapidCnt = 0;
    goto LABEL_26;
  }
  v5 = wk;
  v7 = v5->GunRapidCnt + 1;
  v8 = v5->GunRapidCnt - 599 < 0;
  v5->GunRapidCnt = v7;
  if (v8 == __OFSUB__(v7, 600))
  {
    v5 = wk;
    GunRapidNum = v5->GunRapidNum;
    v5->GunRapidCnt = 0;
    GunRapidNum += 6;
    v5->GunRapidNum = GunRapidNum;
    if (GunRapidNum >= 37)
    {
      v5 = wk;
      v5->GunRapidNum = 36;
    }
  }
LABEL_26:
  if (!gGunInfinite)
    return;
  if (gGunInfiniteCnt >= 1)
  {
    gGunInfiniteCnt = gGunInfiniteCnt - 1;
  }
  if (gGunInfiniteCnt <= 0)
  {
    gGunInfinite = 0;
    sysmsgList = wk->sysmsgList;
    sBtlCreateSM(sysmsgList, wk, 62, 744, 0, 120);
  }
}

// 0x1f9bea0
void sBtlDrawGunRapid(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  s32 v6;
  s32 height;
  s64 v9;
  u64 v10;
  s64 v11;
  s32 v13;
  s32 v15;
  s32 GunRapidNum;
  f32 v17;
  u32 v19;

  if (!wk)
    return;
  if (!wk->UnitMng)
    return;
  if ((wk->status & 8) != 0)
    return;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    return;
  if ((v5->vstatus & 0x8000) != 0)
  {
    v6 = 50 * (get_width(0) / 100);
    height = get_height(0);
    v9 = 1374389535 * height;
    if (wk->GunRapidNum >= 10)
      v6 = 52 * (get_width(0) / 100);
    v10 = (u64)v9 >> 63;
    v11 = v9 >> 37;
    v13 = v11 + v10;
    v15 = 81 * v13;
    GunRapidNum = wk->GunRapidNum;
    v17 = (f32)GunRapidNum / 0.36;
    if (v17 >= 99.0)
      v17 = 100.0;
    if ((s32)v17 <= 25 || v17 == INFINITY)
      v19 = -16776961;
    else
      v19 = -1;
    GunRapidNum = wk->GunRapidNum;
    sBtlDrawNum4(v6, v15, v19, 0xFFu, GunRapidNum, 0x6Cu, 1.0, 0x1010F080u, 0.4);
    return;
  }
}

// 0x1f88620
static void ProcGunMode(SBTLUNIT_WORK *wk) {
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v14;
  f32 v15;
  s32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 v42;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v53;
  f32 v55;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v72;
  f32 v73;
  f32 v75;
  f32 v76;
  f32 v78;
  f32 v80;
  f32 v81;
  sdfVector4_t v82;
  sdfVector4_t v83;
  sdfVector4_t v84;
  sdfVector4_t v85;
  sdfVector4_t v86;
  sdfVector4_t v87;

  if (gGunModeStep > 1)
  {
    switch (gGunModeStep)
    {
      case 10:
        x = wk->rot.x;
        y = wk->rot.y;
        z = wk->rot.z;
        w = wk->rot.w;
        v85.x = x;
        v85.y = y;
        v85.z = z;
        v85.w = w;
        RotToDir = sBtlGetRotToDir(v85);
        v42 = RotToDir;
        gGunMode_Dir = v42;
        gGunMode_SlideNml = 1.0;
        break;
      case 20:
      case 22:
        v6 = wk->rot.x;
        v7 = wk->rot.y;
        v9 = wk->rot.z;
        v8 = wk->rot.w;
        v82.x = v6;
        v82.y = v7;
        v82.z = v9;
        v82.w = v8;
        v10 = sBtlGetRotToDir(v82);
        v11 = v10;
        gGunMode_Dir = v11;
        v14 = gGunModeTime + VRF_DeltaTime;
        v15 = FPS60 * 4.0;
        gGunModeTime = v14;
        if (v14 >= v15)
        {
          v16 = gGunModeStep;
          gGunModeAnimTime = 0.0;
          gGunModeStep = v16 + 1;
          goto LABEL_94;
        }
        break;
      case 21:
        v44 = wk->rot.x;
        v45 = wk->rot.y;
        v47 = wk->rot.z;
        v46 = wk->rot.w;
        v86.x = v44;
        v86.y = v45;
        v86.z = v47;
        v86.w = v46;
        v48 = sBtlGetRotToDir(v86);
        v49 = v48;
        gGunMode_Dir = v49;
        v53 = gGunModeAnimTime + VRF_DeltaTime;
        gGunModeAnimTime = v53;
        if (v53 >= FPS60)
        {
          gGunModeAnimTime = 0.0;
          v55 = gGunMode_TgtZoomNml + 0.16666667;
          gGunMode_TgtZoomNml = v55;
          if (v55 > 1.0)
          {
            gGunMode_TgtZoomNml = 1.0;
          }
        }
        v57 = gGunModeTime + VRF_DeltaTime;
        v58 = FPS60 * 6.0;
        gGunModeTime = v57;
        if (v57 > v58)
        {
          ++gGunModeStep;
          goto LABEL_94;
        }
        break;
      case 23:
        v59 = wk->rot.x;
        v60 = wk->rot.y;
        v62 = wk->rot.z;
        v61 = wk->rot.w;
        v87.x = v59;
        v87.y = v60;
        v87.z = v62;
        v87.w = v61;
        v63 = sBtlGetRotToDir(v87);
        v64 = v63;
        gGunMode_Dir = v64;
        v67 = FPS60;
        v68 = gGunModeAnimTime + VRF_DeltaTime;
        gGunModeAnimTime = v68;
        if (v68 >= v67)
        {
          v69 = gGunMode_TgtZoomNml;
          gGunModeAnimTime = 0.0;
          v70 = v69 + -0.16666667;
          gGunMode_TgtZoomNml = v70;
          if (v70 < 0.0)
          {
            gGunMode_TgtZoomNml = 0.0;
          }
        }
        v72 = gGunModeTime + VRF_DeltaTime;
        v73 = FPS60 * 6.0;
        gGunModeTime = v72;
        if (v72 >= v73)
        {
          gGunMode_TgtZoomNml = 0.0;
          goto LABEL_78;
        }
        break;
      case 30:
        v75 = FPS60;
        v76 = gGunModeAnimTime + VRF_DeltaTime;
        gGunModeAnimTime = v76;
        if (v76 >= v75)
        {
          gGunModeAnimTime = 0.0;
          v78 = gGunMode_SlideNml + -0.125;
          gGunMode_SlideNml = v78;
          if (v78 < 0.0)
          {
            gGunMode_SlideNml = 0.0;
          }
        }
        v80 = gGunModeTime + VRF_DeltaTime;
        v81 = FPS60 * 8.0;
        gGunModeTime = v80;
        if (v80 >= v81)
        {
          gGunModeStep = 0;
          goto LABEL_94;
        }
        break;
      default:
        goto LABEL_95;
    }
    goto LABEL_95;
  }
  if (gGunModeStep)
  {
    if (gGunModeStep == 1)
    {
      v17 = wk->rot.x;
      v18 = wk->rot.y;
      v20 = wk->rot.z;
      v19 = wk->rot.w;
      v83.x = v17;
      v83.y = v18;
      v83.z = v20;
      v83.w = v19;
      v21 = sBtlGetRotToDir(v83);
      v22 = v21;
      gGunMode_Dir = v22;
      v25 = FPS60;
      v26 = gGunModeAnimTime + VRF_DeltaTime;
      gGunModeAnimTime = v26;
      if (v26 >= v25)
      {
        v27 = gGunMode_SlideNml;
        gGunModeAnimTime = 0.0;
        v28 = v27 + 0.125;
        gGunMode_SlideNml = v28;
        if (v28 > 1.0)
        {
          gGunMode_SlideNml = 1.0;
        }
      }
      v30 = gGunModeTime + VRF_DeltaTime;
      v31 = FPS60 * 8.0;
      gGunModeTime = v30;
      if (v30 >= v31)
      {
        gGunMode_SlideNml = 1.0;
LABEL_78:
        gGunModeStep = 10;
LABEL_94:
        gGunModeTime = 0.0;
      }
    }
  }
  else
  {
    *(u64 *)&gGunMode_SlideNml = 0;
    v32 = wk->rot.x;
    v33 = wk->rot.y;
    v35 = wk->rot.z;
    v34 = wk->rot.w;
    v84.x = v32;
    v84.y = v33;
    v84.z = v35;
    v84.w = v34;
    v36 = sBtlGetRotToDir(v84);
    gGunMode_Dir = v36;
  }
LABEL_95:
  UpdateGunRapid(wk);
}

// 0x1f95610
void sBtlCancelGunLockOn(void) {
  s64 v2;
  s32 *GunLockOnTgtSubIdx;
  s64 v4;
  s32 *GunLockOnTgtDone;
  s32 *GunLockOnTgtID;
  s64 i;
  char *v10;
  s32 *GunLockOnTgtPushPop;

  v2 = 8;
  wk->GunLockOnNum = 0;
  while (1)
  {
    GunLockOnTgtID = wk->GunLockOnTgtID;
    if (v2 - 8 >= SLODWORD(GunLockOnTgtID->max_length))
      break;
    GunLockOnTgtID = wk->GunLockOnTgtID;
    GunLockOnTgtSubIdx = wk->GunLockOnTgtSubIdx;
    v4 = 4 * v2++;
    GunLockOnTgtDone = wk->GunLockOnTgtDone;
    *(u32 *)((char *)&GunLockOnTgtID->obj.klass + v4) = -1;
    *(u32 *)((char *)&GunLockOnTgtSubIdx->obj.klass + v4) = 0;
    *(u32 *)((char *)&GunLockOnTgtDone->obj.klass + v4) = 0;
  }
  for (i = 0; ; ++i)
  {
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    if (i >= SLODWORD(GunLockOnTgtPushPop->max_length))
      break;
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    v10 = (char *)GunLockOnTgtPushPop + 4 * i;
    *((u32 *)v10 + 8) = -1;
  }
  DeleteAll();
}

// 0x1f8f7d0
s32 sBtlGetGunLockOn_TgtNum(void) {
  s64 v2;
  s32 v3;
  s64 v4;

  v2 = 0;
  v3 = 0;
  while (1)
  {
    if (v2 >= wk->GunLockOnNum)
      break;
    v4 = (s64)wk->GunLockOnTgtDone + 4 * v2++;
    if (!*(u32 *)(v4 + 32))
      ++v3;
  }
  return v3;
}

// 0x1f98590
void sBtlGetGunLockOn_TgtID(SBTLUNIT_WORK *wk, s32 *_TgtID) {
  s64 v5;
  s32 v6;
  s64 v7;
  SBATTLE_WORK *v8;

  v5 = 0;
  v6 = -1;
  while (1)
  {
    v8 = wk;
    if (v5 >= v8->GunLockOnNum)
      break;
    v8 = wk;
    v7 = (s64)v8->GunLockOnTgtDone + 4 * v5++;
    if (!*(u32 *)(v7 + 32))
    {
      v8 = wk;
      v6 = *((u32 *)&v8->GunLockOnTgtID->max_length + v5 + 1);
      break;
    }
  }
  *TgtID = v6;
}

// 0x1f97f80
void sBtlSetGunLockOn_Done(SBTLUNIT_WORK *wk) {
  s64 v4;
  SBATTLE_WORK *v5;
  s32 *GunLockOnTgtDone;
  SBATTLE_WORK *v8;
  s32 GunRapidNum;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 v15;
  s64 v17;
  s32 v19;
  s64 ToZ;
  sdfVector4_t v21;

  ToZ = 0;
  v4 = 8;
  while (1)
  {
    v5 = wk;
    if (v4 - 8 >= v5->GunLockOnNum)
      break;
    v5 = wk;
    GunLockOnTgtDone = v5->GunLockOnTgtDone;
    if (!*((u32 *)&GunLockOnTgtDone->obj.klass + v4))
    {
      GunLockOnTgtDone = wk->GunLockOnTgtDone;
      *((u32 *)&GunLockOnTgtDone->obj.klass + v4) = 1;
      if (!gGunInfinite)
      {
        v8 = wk;
        GunRapidNum = v8->GunRapidNum;
        if (GunRapidNum >= 1)
        {
          v8 = wk;
          GunRapidNum = v8->GunRapidNum;
          v8->GunRapidNum = GunRapidNum - 1;
        }
      }
      x = wk->rot.x;
      y = wk->rot.y;
      z = wk->rot.z;
      w = wk->rot.w;
      v21.x = x;
      v21.y = y;
      v21.z = z;
      v21.w = w;
      RotToDir = sBtlGetRotToDir(v21);
      v15 = wk->pos.y + -143.0;
      sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir + 5.0, 55.0, (f32 *)&ToZ + 1, &ToZ);
      v17 = ToZ;
      Add(*((f32 *)&v17 + 1), v15, *(f32 *)&v17, RotToDir, *((u32 *)&wk->GunLockOnTgtID->obj.klass + v4), v4 - 8, 0);
      Del(*((u32 *)&wk->GunLockOnTgtID->obj.klass + v4), *((u32 *)&wk->GunLockOnTgtSubIdx->obj.klass + v4));
      v19 = *((u32 *)&wk->GunLockOnTgtID->obj.klass + v4);
      sBtlSetGunLockOn_TgtPush(v19);
      return;
    }
    ++v4;
  }
}

// 0x1f98670
void sBtlSetGunLockOn_EnemyDead_Done(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wkEnemy) {
  s64 i;
  s32 *GunLockOnTgtDone;
  s32 *GunLockOnTgtSubIdx;
  SBATTLE_WORK *v8;
  SBATTLE_WORK *v9;
  s32 *GunLockOnTgtID;

  for (i = 8; ; ++i)
  {
    v8 = wk;
    if (i - 8 >= v8->GunLockOnNum)
      break;
    if (*((u32 *)&v8->GunLockOnTgtDone->obj.klass + i))
      continue;
    v9 = wk;
    GunLockOnTgtID = v9->GunLockOnTgtID;
    if (*((u32 *)&GunLockOnTgtID->obj.klass + i) == wkEnemy->ListID)
    {
      v9 = wk;
      GunLockOnTgtID = v9->GunLockOnTgtID;
      GunLockOnTgtDone = v9->GunLockOnTgtDone;
      GunLockOnTgtSubIdx = v9->GunLockOnTgtSubIdx;
      *((u32 *)&GunLockOnTgtDone->obj.klass + i) = 1;
      Del(*((u32 *)&GunLockOnTgtID->obj.klass + i), *((u32 *)&GunLockOnTgtSubIdx->obj.klass + i));
    }
  }
}

// 0x1f90c50
void sBtlResetGunLockOn_TgtPushPop(void) {
  s64 i;
  char *v3;
  s32 *GunLockOnTgtPushPop;

  for (i = 0; ; ++i)
  {
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    if (i >= SLODWORD(GunLockOnTgtPushPop->max_length))
      break;
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    v3 = (char *)GunLockOnTgtPushPop + 4 * i;
    *((u32 *)v3 + 8) = -1;
  }
}

// 0x1f9c1f0
void sBtlSetGunLockOn_TgtPush(s32 _EnemyListID) {
  s64 v4;
  char *v5;
  s32 *GunLockOnTgtPushPop;

  v4 = 0;
  while (1)
  {
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    if (v4 >= SLODWORD(GunLockOnTgtPushPop->max_length))
      break;
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    v5 = (char *)GunLockOnTgtPushPop + 4 * v4++;
    if (*((u32 *)v5 + 8) == -1)
    {
      GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
      *((u32 *)&GunLockOnTgtPushPop->max_length + v4 + 1) = EnemyListID;
      return;
    }
  }
}

// 0x1f9c2d0
s32 sBtlGetGunLockOn_TgtPop(void) {
  s32 v2;
  s64 i;
  char *v4;
  s32 *GunLockOnTgtPushPop;
  il2cpp_array_size_t max_length;

  v2 = wk->GunLockOnTgtPushPop[0];
  if (v2 == -1)
    return -1;
  v2 = wk->GunLockOnTgtPushPop[0];
  for (i = 0; ; ++i)
  {
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    max_length = GunLockOnTgtPushPop->max_length;
    if (i >= (s32)max_length - 1)
      break;
    GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
    v4 = (char *)GunLockOnTgtPushPop + 4 * i;
    *((u32 *)v4 + 8) = *((u32 *)v4 + 9);
  }
  GunLockOnTgtPushPop = wk->GunLockOnTgtPushPop;
  max_length = GunLockOnTgtPushPop->max_length;
  *(s32 *)((char *)GunLockOnTgtPushPop + ((s64)((max_length << 32) - 0x100000000LL) >> 30)) = -1;
  return v2;
}

// 0x1f97ea0
void sBtlSetGunLockOn_1st(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 v8;
  s64 ToZ;
  sdfVector4_t v10;

  ToZ = 0;
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v10.x = x;
  v10.y = y;
  v10.z = z;
  v10.w = w;
  RotToDir = sBtlGetRotToDir(v10);
  v8 = wk->pos.y + -143.0;
  sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir + 5.0, 55.0, (f32 *)&ToZ + 1, &ToZ);
  AW_BulletAdd(*((f32 *)&ToZ + 1), v8, *(f32 *)&ToZ, RotToDir);
}

// 0x1f91a00
bool sBtlCheckGunMode(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  return BYTE1(sBtlSearchUnit_ID(UnitMng, playerID)->vstatus) >> 7;
}

// 0x1f9c420
bool sBtlCheckGunMode2(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  if ((sBtlSearchUnit_ID(UnitMng, playerID)->vstatus & 0x8000) != 0)
    return 1;
  return gGunModeStep != 0;
}

// 0x1f99690
s32 sBtlNormalProc_Huuma(SBTLUNIT_WORK *wk, s32 flg) {
  s32 v3;
  s32 v10;
  s32 v12;
  SBTLACTAI_WORK *actaiwk;
  SBATTLE_WORK *v21;
  s32 huuma_targetID;
  SBATTLE_WORK *v25;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v27;
  SBTLUNIT_WORK *v28;
  SBTLUNIT_WORK *v29;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 per;
  long f64 v39;
  f32 v40;
  long f64 v42;
  f32 v43;
  s32 level;
  SBATTLE_WORK *v46;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v51;
  SBATTLE_WORK *v54;
  SBTLDMG_HITLISTWORK *hitList;
  s32 ListID;
  s32 use_skillid;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  sdfVector4_t v66;
  sdfVector4_t v67;
  sdfVector4_t v68;
  sdfVector4_t rot;

  v3 = flg;
  if (!ChkHuuma_PlayerInputOk(wk))
    return v3;
  if (sBtlCheckGunMode2())
    return v3;
  if (sBtlIsBattleKey(4166, 1))
  {
    v10 = CheckHuuma(wk);
    if (v10 == -1)
      goto LABEL_60;
    v12 = v10;
    wk->huuma_targetID = v12;
    if (!CheckHuuma_Moon(sBtlPlayer))
      goto LABEL_60;
    if (CheckHuuma2(wk))
    {
      sBtlResetAction(wk);
      actaiwk = wk->actaiwk;
      v21 = wk;
      v21->mode = 12;
      huuma_targetID = v21->huuma_targetID;
      v21->huumastat = 0;
      v21->huumacancel = 0;
      actaiwk->targetID = huuma_targetID;
      *(u64 *)&v21->huuma_counter = 0;
      sBtlResetCharge(wk, 0);
      sBtlResetJump(wk);
      wk->cmstatus = 0;
      v25 = wk;
      UnitMng = v25->UnitMng;
      v27 = v25->huuma_targetID;
      v28 = sBtlSearchUnit_ID(UnitMng, v27);
      if (!v28)
        goto LABEL_57;
      v29 = v28;
      if (!sBtlCheckDamageTarget(v29))
        goto LABEL_57;
      rot = wk->rot;
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      per = v29->pos.x;
      v64 = wk->rot.y;
      v65 = wk->rot.x;
      v62 = wk->rot.w;
      v63 = wk->rot.z;
      rot.w = v62;
      rot.z = v63;
      rot.y = v64;
      rot.x = v65;
      v68.x = x;
      v68.y = y;
      v68.z = z;
      v68.w = w;
      *(u64 *)&v66.x = 0;
      *(f32 *)&v39 = sBtlGetRadian(v68, rot, v66, per);
      v40 = *(f32 *)&v39;
      sub_1B335A0(&wk->rot, 0, v39);
      sBtlAddUnitDeg(wk, v40);
      *(u64 *)&v67.x = 0;
      *(f32 *)&v42 = sBtlGetRadian(v29->pos, v29->rot, v67, wk->pos.x);
      v43 = *(f32 *)&v42;
      sub_1B335A0(&v29->rot, 0, v42);
      sBtlAddUnitDeg(v29, v43);
      level = v29->para->level;
      v46 = wk;
      if (v46->mag < level)
      {
        para = v29->para;
        goto LABEL_43;
      }
      v46 = wk;
      hitList = v46->hitList;
      ListID = v29->ListID;
      use_skillid = v29->actwk->use_skillid;
      sBtlDltHit_by_UnitSkl(hitList, ListID, use_skillid);
      para = v29->para;
LABEL_43:
      BadStatus = sBtlGetBadStatus(para);
      if (BadStatus != 6)
      {
        if (BadStatus != 12)
        {
LABEL_48:
          sBtlSetAction(v29, 35, 0);
          wk->motion_EndNoCng = 1;
          sBtlSetMotion(wk, 137, 0, 0, 0);
          v54 = wk;
          v54->huuma_st_motion_cnt = 0;
          StopBattle();
          sBtlStatusBitOn(wk, 0x10u);
          sBtlStatusBitOn(v29, 0x10u);
          sBtlStatusBitOn(v29, 0x4000u);
LABEL_57:
          CalcCamPost_Init();
          return 2;
        }
        v51 = 4096;
LABEL_47:
        sBtlResetBadStatus(v29, v51);
        goto LABEL_48;
      }
      v51 = 64;
      goto LABEL_47;
    }
LABEL_60:
    if ((wk->status & 0x400) != 0)
      return 2;
    return v3;
  }
  return v3;
}

// 0x1f9d5b0
s32 sBtlNormalProc_Huuma_ActionPause(SBTLUNIT_WORK *wk, s32 flg) {
  s32 result;

  gNowActionPause = 1;
  result = sBtlNormalProc_Huuma(wk, flg);
  gNowActionPause = 0;
  return result;
}

// 0x1f9d640
bool sBtlSetHuumaData(SBTLUNIT_WORK *wk) {
  s32 *huuma_devilID;
  s64 v7;
  s32 devilid;
  DEVILDATA_WORK *DevilData;

  huuma_devilID = wk->huuma_devilID;
  if (huuma_devilID[0] != -1)
  {
    if (huuma_devilID[1] != -1)
    {
      if (huuma_devilID[2] != -1)
      {
        if (huuma_devilID[3] != -1)
        {
          if (huuma_devilID[4] != -1)
          {
            if (huuma_devilID[5] != -1)
            {
              if (huuma_devilID[6] != -1)
              {
                if (huuma_devilID[7] != -1)
                {
                  if (huuma_devilID[8] != -1)
                  {
                    if (huuma_devilID[9] != -1)
                    {
                      if (huuma_devilID[10] != -1)
                      {
                        if (huuma_devilID[11] != -1)
                          return 0;
                        goto LABEL_49;
                      }
                      v7 = 10;
                      goto LABEL_57;
                    }
                    v7 = 9;
                    goto LABEL_57;
                  }
                  v7 = 8;
                  goto LABEL_57;
                }
                v7 = 7;
                goto LABEL_57;
              }
              v7 = 6;
              goto LABEL_57;
            }
            v7 = 5;
            goto LABEL_57;
          }
          v7 = 4;
          goto LABEL_57;
        }
        v7 = 3;
        goto LABEL_57;
      }
      v7 = 2;
      goto LABEL_57;
    }
    v7 = 1;
    goto LABEL_57;
  }
  v7 = 0;
  goto LABEL_57;
LABEL_49:
  v7 = 11;
LABEL_57:
  devilid = wk->para->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  wk->huuma_devilID[v7] = DevilData->huumaID;
  return 1;
}

// 0x1f76f70
static bool CheckHuumaMes(void) {
  return wk->mode == 12;
}

// 0x1f9da10
static void SetHuumaMiss(SBTLUNIT_WORK *wk, s16 flg) {
  SBATTLE_WORK *v6;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  sdfVector4_t v11;

  v6 = wk;
  v6->initHuumaMag = 0;
  v6->huumastat = 2;
  v6->huuma_counter = 0;
  v6->huumamagnone = flg;
  if (flg)
  {
    goto LABEL_8;
  }
  v11.x = 0.0;
  v11.y = 0.0;
  v11.z = 0.0;
  v11.w = 0.0;
  sBtlPlaySpecialSE(v11, 3);
LABEL_8:
  sBtlStatusBitOn(wk, 0x4000u);
  v9 = sBtlSearchUnit_ID(wk->UnitMng, wk->huuma_targetID);
  if (v9)
  {
    v10 = v9;
    sBtlStatusBitOff(v10, 0xFFFFFFEF);
  }
}

// 0x1f9db80
void sBtlSetHuumaMissItemFlagOff(SBTLUNIT_WORK *_actWk) {
  ;
}

// 0x1f9c9d0
static bool CheckHuuma_Moon(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v3;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  SBTLUNIT_WORK *v6;
  s32 devilid;
  SBATTLE_WORK *v10;
  s64 i;
  SBTLUNIT_LISTWORK *v14;
  SBTLUNIT_WORK *pUnit;

  v3 = wk;
  UnitMng = v3->UnitMng;
  huuma_targetID = v3->huuma_targetID;
  v6 = sBtlSearchUnit_ID(UnitMng, huuma_targetID);
  if (v6)
    goto LABEL_7;
  v10 = wk;
  v10->eventno = 3;
  v10->eventgstat = 0;
  v10->nego_gstat = 0;
  v10->eventListID = loc_16C;
  v10->status |= 0x400u;
LABEL_17:
  for (i = 0; ; ++i)
  {
    v14 = wk->UnitMng;
    if (i >= v14->number)
      return v6 != 0;
    pUnit = v14->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->hModel)
      pUnit->vstatus |= 0x8000000u;
  }
  goto LABEL_17;
LABEL_7:
  devilid = v6->para->devilid;
  sBtlGetDevilData(devilid, -1);
  return v6 != 0;
}

// 0x1f9cc10
static bool CheckHuuma2(SBTLUNIT_WORK *wk) {
  SB_ENCOUNTPAC *EncountPac;
  SBATTLE_WORK *v5;
  s32 huuma_targetID;
  Il2CppClass **v7;
  SBTLUNIT_LISTWORK *UnitMng;
  Il2CppClass *v9;
  SBTLUNIT_WORK *v10;
  s32 devilid;
  SBATTLE_WORK *v12;
  sdatUnitWork_t *para;
  SBTLSM_LISTWORK *sysmsgList;
  SBTLSM_LISTWORK *v17;
  SBTLUNIT_WORK *v18;
  s32 v19;
  s32 v21;
  SBTLSM_LISTWORK *v23;

  EncountPac = sBtlGetEncountPac(-1);
  v5 = wk;
  huuma_targetID = v5->huuma_targetID;
  v7 = &EncountPac->obj.klass + v5->encountno;
  UnitMng = v5->UnitMng;
  v9 = v7[4];
  v10 = sBtlSearchUnit_ID(UnitMng, huuma_targetID);
  devilid = v10->para->devilid;
  sBtlGetDevilHuumaItem(devilid);
  v12 = wk;
  if (v12->battlemode)
  {
LABEL_20:
    sysmsgList = v12->sysmsgList;
    v17 = sysmsgList;
    v18 = wk;
    v19 = 60;
LABEL_23:
    sBtlCreateSM(v17, v18, v19, 0, 0, 120);
    return 0;
LABEL_19:
    v12 = wk;
    goto LABEL_20;
  }
  para = wk->para;
  if (sBtlGetBadStatus(wk->para) == 10)
  {
    goto LABEL_19;
  }
  if ((*(u8 *)(&v9->_1.byval_arg.bits + 1) & 6) != 0 || (v10->status & 0x10000) != 0)
  {
    v23 = wk->sysmsgList;
    v19 = 74;
    v17 = v23;
    v18 = wk;
    goto LABEL_23;
  }
  sBtlGetPlayerData();
  v21 = v10->para->devilid;
  sBtlGetDevilData(v21, -1);
  return 1;
}

// 0x1f9c720
static s32 CheckHuuma(SBTLUNIT_WORK *wk) {
  s64 v3;
  s32 ListID;
  f32 v5;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 PosToDir;
  f32 AtoB_LR_ABS;
  f32 LenXZ;
  sdfVector4_t v20;

  v3 = 0;
  ListID = -1;
  v5 = 9999.0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (!pUnit)
      goto LABEL_4;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_4;
    if ((pUnit->side & 2) != 0)
    {
      x = wk->rot.x;
      y = wk->rot.y;
      z = wk->rot.z;
      w = wk->rot.w;
      v20.x = x;
      v20.y = y;
      v20.z = z;
      v20.w = w;
      RotToDir = sBtlGetRotToDir(v20);
      PosToDir = sBtlGetPosToDir(wk->pos.x, wk->pos.z, pUnit->pos.x, pUnit->pos.z);
      AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(RotToDir, PosToDir);
      LenXZ = sBtlGetLenXZ(wk->pos.x, wk->pos.z, pUnit->pos.x, pUnit->pos.z);
      if (AtoB_LR_ABS < 135.0 && LenXZ <= (f32)(pUnit->actaiwk->hit_area_r + 200.0))
      {
        if ((pUnit->status & 0x10000) == 0 && wk->actaiwk->targetID == pUnit->ListID)
        {
          if (CheckHuuma_ChkNowNakamaDead())
            return -1;
          return pUnit->ListID;
        }
        if (LenXZ < v5)
        {
          ListID = pUnit->ListID;
          v5 = LenXZ;
        }
      }
    }
LABEL_4:
    ++v3;
  }
  if (ListID == -1)
    return -1;
  if (CheckHuuma_ChkNowNakamaDead())
    return -1;
  else
    return ListID;
}

// 0x1f9db90
static bool CheckHuuma_ChkNowNakamaDead(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  u32 status;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x83) == 1)
    {
      actwk = pUnit->actwk;
      status = actwk->status;
      if (status == 40)
      {
        if (actwk->use_skillid == 240)
          return i < number;
      }
      else if (status == 10 && pUnit->mode != 6)
      {
        return i < number;
      }
    }
  }
  return i < number;
}

// 0x1f952d0
bool sBtlIsHuuma(void) {
  return wk->mode == 12;
}

// 0x1f9dcb0
s32 sBtlGetHuuma_Camera(void) {
  s32 huumastat;
  s32 result;
  s32 v9;

  huumastat = wk->huumastat;
  if (huumastat > 1027)
  {
    if ((u32)huumastat > 0x410)
    {
      if (huumastat == 1280 || (u16)huumastat == 1296 || (u16)huumastat == 1360)
        return 3;
      return 0;
    }
    if (huumastat == 1040 || huumastat == 1029)
      return 2;
    else
      return 0;
  }
  if (huumastat > 241)
  {
    if ((huumastat & 0xFFFFFFFE) == 0x100)
      return 5;
    if (huumastat == 1024)
      return 2;
    return 0;
  }
  switch (huumastat)
  {
    case 0:
      return 0;
    case 1:
    case 2:
    case 8:
      result = 1;
      break;
    case 3:
    case 9:
    case 10:
      if (wk->huumamagnone)
        v9 = -1;
      else
        v9 = -2;
      result = v9;
      break;
    case 4:
      return 2;
    case 5:
      return 3;
    case 6:
    case 7:
      result = 5;
      break;
    default:
      if ((huumastat & 0xFFFFFFFE) != 0xF0)
        return 0;
      result = 4;
      break;
  }
  return result;
}

// 0x1f9de80
void sBtlPushAllDisp(SBTLUNIT_WORK *wk) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 i;
  SBTLUNIT_LISTWORK *v8;
  SBTLUNIT_WORK *v9;
  bool v10;
  s32 ListID;
  s32 vstatus;

  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    pUnit = wk->UnitMng->pUnitL[v3]->pUnit;
    if (pUnit)
      pUnit->bOldDispOff = (pUnit->vstatus & 0x1000) != 0;
    ++v3;
  }
  for (i = 0; ; ++i)
  {
    v8 = wk->UnitMng;
    if (i >= v8->number)
      break;
    v8 = wk->UnitMng;
    v9 = v8->pUnitL[i]->pUnit;
    if (v9)
      v10 = v9 == wk;
    else
      v10 = 1;
    if (!v10)
    {
      ListID = v9->ListID;
      if (ListID == wk->huuma_targetID)
        continue;
      vstatus = v9->vstatus;
      v9->JumpOfsPos.y = 5000.0;
      v9->vstatus = vstatus | 0x1000;
      sBtlUpdateUnitJumpOfsPos(v9);
    }
  }
}

// 0x1f9e070
void sBtlPopAllDisp(SBTLUNIT_WORK *wk) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v7;
  s32 ListID;
  s32 vstatus;

  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (pUnit)
      v7 = pUnit == wk;
    else
      v7 = 1;
    if (!v7)
    {
      ListID = pUnit->ListID;
      if (ListID == wk->huuma_targetID)
        goto LABEL_5;
      vstatus = pUnit->vstatus;
      pUnit->JumpOfsPos.y = 0.0;
      pUnit->vstatus = vstatus & 0xFFFFEFFF | (pUnit->bOldDispOff << 12);
      sBtlUpdateUnitJumpOfsPos(pUnit);
    }
LABEL_5:
    ++v3;
  }
}

// 0x1f81140
static s32 HuumaProc(SBTLUNIT_WORK *wk) {
  SBTLDMG_HITWORK *v2;
  s64 v3;
  void *v4;
  u64 *v5;
  void *v6;
  u64 *v7;
  s64 v8;
  void *v9;
  u64 *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  SBATTLE_WORK *v16;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  SBTLUNIT_WORK *v19;
  SBATTLE_WORK *v21;
  s32 *p_huuma_counter;
  SBATTLE_WORK *v28;
  s32 huumastat;
  u32 v30;
  void *v31;
  s16 v34;
  SBATTLE_WORK *v36;
  s32 RandNo;
  SBATTLE_WORK *v42;
  bool SpiritSkillChk;
  f32 v47;
  s32 huuma_def_time_local;
  void *v49;
  s32 devilid;
  char *v51;
  s32 v53;
  SBATTLE_WORK *v55;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_eventprocID;
  Il2CppObject *ProcessData;
  s32 monitor_high;
  s32 v62;
  s16 v63;
  void *v64;
  u32 huumaCnt;
  dds3ModelHandle_t *hModel;
  void *v70;
  SBATTLE_WORK *v73;
  f32 v75;
  void *Instance;
  SBATTLE_WORK *v79;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v83;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v85;
  s32 *p_huuma_keycnt;
  SBTLUNIT_WORK *v89;
  s32 huuma_counter;
  s32 v92;
  u32 v93;
  SBTLSM_LISTWORK *v94;
  SBTLSM_LISTWORK *v95;
  SBTLUNIT_WORK *v96;
  s32 v97;
  SBATTLE_WORK *v99;
  void *v100;
  s32 v103;
  s32 huumaID;
  s64 v107;
  SBTLUNIT_LISTWORK *v110;
  SBTLUNIT_WORK *v111;
  dds3ModelHandle_t *v113;
  SBTLUNIT_WORK *v116;
  s32 v117;
  u32 v118;
  u32 v119;
  s32 v120;
  u32 v121;
  SBTLSM_LISTWORK *v122;
  char status_high;
  s32 v125;
  bool v126;
  s64 i;
  SBTLUNIT_LISTWORK *v129;
  SBTLUNIT_WORK *pUnit;
  SBATTLE_WORK *v131;
  SBTLUNIT_WORK *v132;
  sdatUnitWork_t *para;
  s32 level;
  s32 v135;
  s32 flag;
  sdatUnitWork_t *now;
  f32 v138;
  s32 v139;
  u64 v140;
  bool v141;
  signed s32 v142;
  bool v143;
  SBTLUNIT_WORK *v145;
  s64 v146;
  SBATTLE_WORK *v147;
  u32 v148;
  char *v149;
  void *v151;
  Project_DefineAchievementID_string__c *v152;
  s64 v153;
  Project_DefineAchievementID_string__c **v154;
  s64 v155;
  char *v156;
  void *v158;
  Project_DefineAchievementID_string__c *v159;
  s64 v160;
  Project_DefineAchievementID_string__c **v161;
  s64 v162;
  char *v163;
  SBATTLE_WORK *v164;
  SBTLSM_LISTWORK *v165;
  SBATTLE_WORK *v167;
  s32 huuma_return_cnt;
  s32 v170;
  s32 v171;
  s32 v172;
  s32 v173;
  s32 v174;
  u64 v175;
  SBATTLE_WORK *v176;
  SBATTLE_WORK *v178;
  s32 v179;
  SBATTLE_WORK *v183;
  s32 v184;
  SBATTLE_WORK *v187;
  s32 v188;
  SBATTLE_WORK *v189;
  s32 huumagauge_mag;
  SBTLSM_LISTWORK *sysmsgList;
  SBATTLE_WORK *v193;
  void *v194;
  void *v196;
  s32 ConfigGAME;
  SBATTLE_WORK *v200;
  SBATTLE_WORK *v202;
  void *v204;
  void *v206;
  u32 DevilSE;
  s32 v210;
  u32 v211;
  s32 bst_effserialID2;
  SBTLEFF_LISTWORK *effList;
  f32 v216;
  f32 v217;
  SBTLEFF_LISTWORK *v218;
  f32 w;
  f32 v220;
  SBATTLE_WORK *v224;
  SBTLUNIT_WORK *v228;
  SBTLEFF_LISTWORK *v230;
  SBATTLE_WORK *v231;
  s16 v232;
  SBATTLE_WORK *v233;
  SBATTLE_WORK *v238;
  s32 v239;
  bool v240;
  s32 *p_huumagauge_para;
  sdatUnitWork_t *v243;
  s32 *v248;
  _BOOL4 v250;
  bool IsBattleKey;
  u32 v254;
  bool v258;
  SBATTLE_WORK *v261;
  SBATTLE_WORK *v265;
  s32 huumagauge_pcnt;
  s32 *p_huumagauge_pcnt;
  s32 huumagauge_pcmpcnt;
  SBATTLE_WORK *v269;
  s32 huumagauge_ppara;
  f32 v272;
  f32 v273;
  s32 v274;
  SBATTLE_WORK *v275;
  s32 huumagauge_counter_start;
  s32 v277;
  f32 v278;
  f32 v279;
  long f64 v280;
  s64 v281;
  f32 v282;
  SBTLSM_LISTWORK *v283;
  u32 v293;
  s32 v294;
  s32 *v295;
  s32 v297;
  SBATTLE_WORK *v298;
  s32 v299;
  f32 v301;
  f32 v302;
  s32 v303;
  SBATTLE_WORK *v304;
  s32 v305;
  s32 v306;
  f32 v307;
  f32 v308;
  long f64 v309;
  s32 v310;
  SBATTLE_WORK *v313;
  s32 *p_huumagauge_cnt;
  s32 huumagauge_cmpcnt;
  SBATTLE_WORK *v317;
  s32 huumagauge_counter;
  s32 v319;
  bool v321;
  s32 huumagauge_w;
  s32 v323;
  f32 v327;
  SBATTLE_WORK *v329;
  bool ItemCalc;
  u32 v333;
  SBATTLE_WORK *v334;
  f32 itemGetWaitCount;
  SBTLSM_LISTWORK *v336;
  u32 v337;
  SBATTLE_WORK *v338;
  s32 v339;
  long f64 v340;
  f32 v341;
  f32 z;
  f32 y;
  f32 v344;
  long f64 v345;
  u32 v346;
  SBATTLE_WORK *v347;
  s32 v348;
  DEVIL_HUUMAITEM *DevilHuumaItem;
  s32 v352;
  SBTLSM_LISTWORK *v354;
  sdatPlayerUnitWork_t *PlayerData;
  s32 *huuma_devilID;
  u32 v359;
  int32x4_t v360;
  int32x4_t *v361;
  int8x16_t v362;
  int32x4_t v363;
  u32 v364;
  signed s32 v367;
  u32 v368;
  SBTLSM_LISTWORK *v371;
  s32 v372;
  SBTLSM_LISTWORK *v374;
  SBTLSM_LISTWORK *v375;
  SBTLUNIT_WORK *v376;
  s32 gageNo;
  SBTLSM_LISTWORK *v380;
  u32 v381;
  s64 v382;
  f32 v383;
  s32 v384;
  s64 v386;
  s64 SZ;
  s64 v388;
  s64 v389;
  s32 x;
  sdfVector4_t v391;
  sdfVector4_t v392;
  sdfVector4_t v393;
  sdfVector4_t v394;
  sdfVector4_t v395;

  x = 0;
  v388 = 0;
  v389 = 0;
  v386 = 0;
  SZ = 0;
  v2 = Allocate(SBTLDMG_HITWORK);
  _ctor(v2, 0);
  v3 = NewSpecific(int__, 2u);
  v4 = NewSpecific(s32, 0x14u);
  InitializeArray_55364416(v4, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__938418A950AF9D76C6E049A9E9FF058FC656650E6D515568AC1F6C45E202F3FA, 0);
  *(u64 *)(v3 + 32) = v4;
  v5 = (v3 + 32);
  v6 = NewSpecific(s32, 0x14u);
  InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__3F05BCC3864A2F596EF8F6FF9E8B349C682E9312AFB3B172658BBBE73605CE33, 0);
  *(u64 *)(v3 + 40) = v6;
  v7 = (v3 + 40);
  v8 = NewSpecific(int__, 2u);
  v9 = NewSpecific(s32, 0xCu);
  InitializeArray_55364416(v9, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__60F3568C48742A63151AA8B95F1E0FAE33565902DA2276548E53B5E3791D1A55, 0);
  *(u64 *)(v8 + 32) = v9;
  v10 = (v8 + 32);
  v11 = NewSpecific(s32, 0xCu);
  InitializeArray_55364416(v11, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__F63964076F13658C57F968A283C71B9F5800D3879E888800579C1E5F64608169, 0);
  *(u64 *)(v8 + 40) = v11;
  v12 = (v8 + 40);
  v13 = NewSpecific(s16, 0xAu);
  InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__40EB7373CDF809FE3D172801BCA590D092C1F8D27959B642A374C600414F02C9, 0);
  v14 = NewSpecific(SBTL_MOON, 9u);
  InitializeArray_55364416(v14, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__921C803ABFA6AC88F44F7AB19198E5C137D1C7183E8E6912757A6263E8DEE0A5, 0);
  v16 = wk;
  UnitMng = v16->UnitMng;
  huuma_targetID = v16->huuma_targetID;
  v19 = sBtlSearchUnit_ID(UnitMng, huuma_targetID);
  v21 = wk;
  if (v21->huumastat == 1027)
  {
    goto LABEL_9;
  }
  v21 = wk;
  ++v21->huuma_counter;
LABEL_9:
  p_huuma_counter = &wk->huuma_counter;
  LimitRange(p_huuma_counter, 0, 600);
  v28 = wk;
  huumastat = v28->huumastat;
  v30 = (u16)v28->huumastat;
  if (huumastat > 1024)
  {
    if (v30 <= 0x410)
    {
      switch (v30)
      {
        case 0x403u:
          v28 = wk;
          v75 = v28->itemGetWaitCount + VRF_DeltaTime;
          v28->itemGetWaitCount = v75;
          if (v75 <= 2.0)
            goto LABEL_626;
          v28 = wk;
          v63 = 1;
          v28->huuma_counter = 0;
          break;
        case 0x405u:
          Instance = get_Instance(0);
          if (!IsNCutIn(Instance, 0))
            goto LABEL_626;
          v63 = 1040;
          v28 = wk;
          break;
        case 0x410u:
          v28 = wk;
          if (v28->huuma_counter < 120)
            goto LABEL_626;
          goto LABEL_135;
LABEL_134:
          v28 = wk;
LABEL_135:
          v63 = 1360;
          break;
        default:
          goto LABEL_626;
      }
LABEL_136:
      v28->huumastat = v63;
      goto LABEL_626;
    }
    if (v30 > 0x501)
    {
      if (huumastat != 1296)
      {
        if (v28->huumastat == 1360)
        {
          v31 = get_Instance(0);
          if (!IsNCutIn(v31, 0))
          {
            v34 = 5;
LABEL_300:
            v131 = wk;
            v131->huumastat = v34;
            v131->huuma_counter = 0;
            goto LABEL_626;
          }
        }
        goto LABEL_626;
      }
      if (dds3SearchProcessPriority(1015))
        goto LABEL_626;
      goto LABEL_134;
    }
    if (huumastat != 1280)
    {
      if (v28->huumastat != 1281)
        goto LABEL_626;
      v49 = NewSpecific(s32, 0x14u);
      InitializeArray_55364416(v49, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__A621E9A2A17FB6E68C1615D5A033FAB8B8F992D4A118200974DFFF43121011E9, 0);
      devilid = v19->para->devilid;
      v51 = (char *)v49 + 4 * sBtlGetKucyou(devilid);
      v53 = *((u32 *)v51 + 8);
      v55 = wk;
      started = scrStartScript2(1015, huuma_success_scr, v53, 1);
      v55->eventprocID = started;
      p_eventprocID = &wk->eventprocID;
      ProcessData = dds3GetProcessData(p_eventprocID);
      monitor_high = HIDWORD(ProcessData[6].monitor);
      v62 = v19->para->devilid;
      itfMesMngSetVar(monitor_high, 0, v62, 1);
      itfPartVoiceDevilSet(v19->para->devilid);
      v63 = 1296;
      v28 = wk;
      goto LABEL_136;
    }
    if (v28->huuma_counter == 40)
      goto LABEL_139;
    goto LABEL_9000;
    if (wk->huuma_counter == 40)
    {
LABEL_139:
      sBtlPlaySE(0x10025u);
      if (wk->huuma_counter != 100)
        goto LABEL_143;
      goto LABEL_277;
LABEL_276:
      if (wk->huuma_counter != 100)
      {
LABEL_143:
        goto LABEL_144;
      }
LABEL_277:
      sndVoicePlayFile("PVA01A_20B_000", 0);
LABEL_144:
      v79 = wk;
      if (v79->huuma_counter < 120)
        goto LABEL_626;
      v79 = wk;
      v79->eventgstat = 0;
      v79->nego_gstat = 0;
      v79->eventno = 7;
      v79->eventListID = v19->ListID;
      v79->status |= 0x400u;
      for (i = 0; ; ++i)
      {
        v129 = wk->UnitMng;
        if (i >= v129->number)
          break;
        v129 = wk->UnitMng;
        pUnit = v129->pUnitL[i]->pUnit;
        if (pUnit && pUnit->hModel)
          pUnit->vstatus |= 0x8000000u;
      }
      sBtlStatusBitOn(wk, 0x10u);
      sBtlStatusBitOn(v19, 0x10u);
      v34 = 1281;
      goto LABEL_300;
    }
LABEL_9000:
    goto LABEL_276;
  }
  if ((s16)v30 > 241)
  {
    if (v30 != 256)
    {
      if (v30 == 257)
      {
        v28 = wk;
        ++v28->huuma_return_cnt;
        if (wk->motionno == 136)
        {
          hModel = wk->hModel;
          mdlGetMotionFrameF(hModel);
          if (sBtlCheckMotionEnd(wk))
          {
            wk->motion_EndNoCng = 0;
            sBtlSetMotion(wk, 0, 0, 0, 0);
          }
        }
        v70 = get_Instance(0);
        if (!DrawHuumaNakamaInfo(v70, wk->huuma_getUnit, 0))
        {
          v73 = wk;
          v73->huumastat = 6;
          MOON_IN();
        }
      }
      else if (v30 == 1024)
      {
        if (sBtlCreateWork(v19))
        {
          v36 = wk;
          if (v36->huuma_counter >= 60)
          {
            v36 = wk;
            v36->eventgstat = 0;
            v36->nego_gstat = 0;
            v36->eventno = 7;
            v36->eventListID = v19->ListID;
            v36->status |= 0x400u;
            sBtlSetNSTOP();
            sBtlStatusBitOn(wk, 0x10u);
            sBtlStatusBitOn(v19, 0x10u);
            wk->huumastat = 1029;
            RandNo = sBtlGetRandNo(35, 37, 39);
            sBtlCreateDvltk(wk->dvltkList, v19, RandNo, 0, 0);
          }
        }
      }
      goto LABEL_626;
    }
    v28 = wk;
    ++v28->huuma_return_cnt;
    v28->huumastat = 257;
    v64 = get_Instance(0);
    OpenHuumaInfo(v64, 0);
    sBtlSetHuumaData(v19);
    sBtlEntryStockData_Huuma();
    huumaCnt = SystemWork->huumaCnt;
    if (huumaCnt > 0xFD)
    {
      goto LABEL_93;
    }
    LOBYTE(huumaCnt) = SystemWork->huumaCnt;
    SystemWork->huumaCnt = huumaCnt + 1;
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v83 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
      p_offset = &klass->_1.interfaceOffsets->offset;
      while (*(p_offset - 1) != Project_DefineAchievementID_string_)
      {
        p_offset += 2;
        if (!--v83)
          goto LABEL_156;
      }
      v85 = &klass->vtable[*(u32 *)p_offset + 27];
    }
    else
    {
LABEL_156:
      v85 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Bu);
    }
    v149 = (*v85)(achievementTbl_k__BackingField, *(u64 *)(v85 + 8));
    ProgressUnlock_3(v149, SystemWork->huumaCnt, 30);
LABEL_93:
    if (!SystemWork->huumaCnt)
      goto LABEL_350;
    v151 = _achievementTbl_k__BackingField;
    v152 = v151->klass;
    v153 = *(u16 *)&v151->klass->_2.rank;
    if (*(u16 *)&v151->klass->_2.rank)
    {
      v154 = &v152->_1.interfaceOffsets->offset;
      while (*(v154 - 1) != Project_DefineAchievementID_string_)
      {
        v154 += 2;
        if (!--v153)
          goto LABEL_344;
      }
      v155 = &v152->vtable[*(u32 *)v154 + 26];
    }
    else
    {
LABEL_344:
      v155 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Au);
    }
    v156 = (*v155)(v151, *(u64 *)(v155 + 8));
    Unlock_2(v156);
LABEL_350:
    if (SystemWork->huumaCnt < 0x1Eu)
      goto LABEL_626;
    v158 = _achievementTbl_k__BackingField;
    v159 = v158->klass;
    v160 = *(u16 *)&v158->klass->_2.rank;
    if (*(u16 *)&v158->klass->_2.rank)
    {
      v161 = &v159->_1.interfaceOffsets->offset;
      while (*(v161 - 1) != Project_DefineAchievementID_string_)
      {
        v161 += 2;
        if (!--v160)
          goto LABEL_360;
      }
      v162 = &v159->vtable[*(u32 *)v161 + 27];
    }
    else
    {
LABEL_360:
      v162 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Bu);
    }
    v163 = (*v162)(v158, *(u64 *)(v162 + 8));
    Unlock_2(v163);
    goto LABEL_626;
  }
  switch (v28->huumastat)
  {
    case 0:
      HuumaGageOff = 1;
      v42 = wk;
      v42->huumagauge_para = 4;
      v42->huumagauge_ppara = 4;
      *(u32 *)&v42->huumamagnone = 0;
      SpiritSkillChk = sBtlGetSpiritSkillChk(1388);
      if (SpiritSkillChk)
      {
        v47 = huuma_ada_jo * (f32)huuma_def_time;
        huuma_def_time_local = v47;
        if (v47 == INFINITY)
          huuma_def_time_local = 0x80000000;
      }
      else
      {
        huuma_def_time_local = huuma_def_time;
      }
      HuumaTimeLimit = huuma_def_time_local;
      para = v19->para;
      now = para->now;
      level = para->level;
      flag = now->flag;
      v135 = *(u32 *)&now->raceid;
      LODWORD(now) = wk->para->level;
      v138 = (f32)((f32)flag / (f32)v135) * 10.0;
      v139 = v138;
      if ((s32)v138 >= 10)
        v139 = 10;
      v140 = v139;
      if ((s32)now >= level)
        goto LABEL_318;
      v141 = DlcMitama();
      now = wk->para;
      if (v141)
      {
        LOBYTE(now) = now->level;
        LOBYTE(level) = v19->para->level;
LABEL_318:
        v142 = ((26215 * ((char)now - (char)level)) >> 18) + ((u32)(26215 * ((char)now - (char)level)) >> 31);
        v143 = DlcMitama();
        v145 = wk;
        if (v143)
          v146 = 0;
        else
          v146 = v142;
        v147 = wk;
        v147->huumagauge_ppara += *(u32 *)(*v5 + 4 * v146 + 32);
      }
      else
      {
        v173 = 26215 * (v19->para->level - now->level);
        v174 = (v173 >> 18) + ((u32)v173 >> 31);
        v10 = v12;
        v147 = wk;
        v145 = wk;
        v147->huumagauge_para += *(u32 *)(*v7 + 4 * v174 + 32);
      }
      v175 = 0xFFFFFFFF80000000LL;
      if (v138 != INFINITY)
        v175 = v140;
      v147->huumagauge_cmpcnt = 2 * *(u32 *)(*v10 + 4 * v175 + 32);
      v176 = wk;
      v176->huumagauge_w = 128;
      v176->huumagauge_w = 2 * sBtlCalcHuumaW(v19, 128);
      v178 = wk;
      v179 = sBtlCalcHuumaType(v19);
      v178->gaugeType = v179;
      v183 = wk;
      v184 = v183->huumagauge_w - 32;
      v183->huumagauge_counter = v184;
      v183->huumagauge_counter_start = v184;
      HuumaGetItemInit(v19);
      v187 = wk;
      v187->huumagauge_cnt = 0;
      *(u64 *)&v187->huumagauge_pcnt = 0x100000000LL;
      v188 = v19->para->level;
      v187->huumagauge_mag = v188;
      if (v188 <= 0)
      {
        v187 = wk;
        v187->huumagauge_mag = 1;
LABEL_418:
        v189 = wk;
        huumagauge_mag = v189->huumagauge_mag;
        if (v189->mag - huumagauge_mag >= 0)
        {
LABEL_419:
          huumagauge_mag = wk->huumagauge_mag;
          sBtlDecMag(huumagauge_mag);
          sysmsgList = wk->sysmsgList;
          sBtlCreateSM(sysmsgList, v19, 161, 0, 0, 20);
          ++wk->huumastat;
          if (v19->hModel)
          {
            sBtlZakoWarpReset(v19);
            sBtlSetMotion(v19, 0, 0, 0, 0);
            Add_Huuma((f32)(v145->pos.x + v19->pos.x) * 0.5, -150.0, (f32)(v145->pos.z + v19->pos.z) * 0.5);
            v193 = wk;
            v193->huumastat = 8;
            v193->huuma_counter = 0;
            sBtlStatusBitOn(v145, 0x4000u);
            v194 = get_Instance(0);
            RememberIconState(v194, 0);
            sBtlPushAllDisp(v145);
            dds3StopQuake();
            DeleteAll_Skill();
            v196 = get_Instance(0);
            ClrCallMark(v196, 0);
            sBtlPlayerClrAllUnit_HitBack();
          }
          ConfigGAME = cfgGetConfigGAME(7, 0);
          if (ConfigGAME)
          {
            huuma_auto = 1;
          }
          else
          {
            huuma_auto = 0;
          }
          goto LABEL_626;
        }
LABEL_453:
        SetHuumaMiss(v145, 1);
        v202 = wk;
        v202->huumastat = 8;
        v204 = get_Instance(0);
        RememberIconState(v204, 0);
        HuumaGageOff = 0;
        sBtlPushAllDisp(v145);
        dds3StopQuake();
        v206 = get_Instance(0);
        ClrCallMark(v206, 0);
        sBtlPlayerClrAllUnit_HitBack();
        goto LABEL_626;
      }
      {
        goto LABEL_418;
      }
      v200 = wk;
      huumagauge_mag = v200->huumagauge_mag;
      if (v200->mag - huumagauge_mag >= 0)
        goto LABEL_419;
      goto LABEL_453;
    case 1:
      v28 = wk;
      p_huuma_keycnt = &v28->huuma_keycnt;
      ++v28->huuma_keycnt;
      LimitRange(p_huuma_keycnt, 0, 240);
      v89 = wk;
      if (!v19 || v19->actwk->status != 35)
      {
        v132 = wk;
        goto LABEL_304;
      }
      huuma_counter = wk->huuma_counter;
      if (huuma_counter >= 60 * HuumaTimeLimit)
      {
        v238 = wk;
        if ((v238->huuma_counter & 1) != 0)
        {
          v238 = wk;
          v239 = v238->huumagauge_cmpcnt - 1;
          v240 = v238->huumagauge_cmpcnt == 1;
          v238->huumagauge_cmpcnt = v239;
          if (v239 < 0 || v240)
          {
            v238 = wk;
            p_huumagauge_para = &v238->huumagauge_para;
            ++v238->huumagauge_para;
            LimitRange(p_huumagauge_para, 0, 60);
          }
        }
      }
      v243 = v19->para;
      if (sBtlIsKoufun(v19->para))
        goto LABEL_541;
      goto LABEL_9007;
      if (sBtlIsKoufun(v243))
      {
LABEL_541:
        v248 = &wk->huumagauge_para;
        *v248 += 100;
        LimitRange(v248, 0, 100);
        wk->huumagauge_counter += wk->huumagauge_para;
        if (!huuma_auto)
        {
LABEL_547:
          v250 = 0;
          goto LABEL_554;
        }
LABEL_551:
        v250 = wk->huuma_keycnt > 6;
LABEL_554:
        IsBattleKey = sBtlIsBattleKey(4168, 2);
        if (IsBattleKey)
        {
          if (!v254)
          SetHuumaMiss(wk, 0);
          wk->huumacancel = 1;
LABEL_695:
          v313 = wk;
          p_huumagauge_cnt = &v313->huumagauge_cnt;
          huumagauge_cmpcnt = v313->huumagauge_cmpcnt;
          ++v313->huumagauge_cnt;
          LimitRange(p_huumagauge_cnt, 0, huumagauge_cmpcnt);
          v317 = wk;
          if (v317->huumagauge_cnt >= v317->huumagauge_cmpcnt)
          {
            v317 = wk;
            huumagauge_counter = v317->huumagauge_counter;
            v317->huumagauge_cnt = 0;
            v317->huumagauge_counter = v317->huumagauge_para + huumagauge_counter;
          }
          v319 = v89->para->level;
          x = wk->huumagauge_counter;
          if (v319 >= v19->para->level)
            goto LABEL_891;
          v321 = DlcMitama();
          if (v321)
          {
LABEL_891:
            huumagauge_w = wk->huumagauge_w;
          }
          else
          {
            v323 = wk->huumagauge_w;
            huumagauge_w = v323 - 1;
          }
          LimitRange(&x, 0, huumagauge_w);
          v327 = 0.25;
          v329 = wk;
          v329->huumagauge_counter = x;
          if (v329->huuma_keycnt < 60)
            v327 = 0.5;
          v89->m_rate = v327;
          ItemCalc = HuumaGetItemCalc(v19);
          if (ItemCalc)
          {
            wk->itemGetWaitCount = 2.0;
            goto LABEL_626;
          }
          v334 = wk;
          itemGetWaitCount = v334->itemGetWaitCount;
          if (itemGetWaitCount <= 0.0)
          {
            if (!v333)
            {
              v334 = wk;
            }
            v336 = v334->sysmsgList;
            sBtlCreateSM(v336, v19, 161, 0, 1, 20);
          }
          else
          {
            if (!v333)
            {
              v334 = wk;
              itemGetWaitCount = v334->itemGetWaitCount;
            }
            v334->itemGetWaitCount = itemGetWaitCount
                                          - VRF_DeltaTime;
          }
          v338 = wk;
          v339 = v338->huumagauge_counter;
          if (v339 > 0)
          {
            if (!v337)
            {
              v338 = wk;
              v339 = v338->huumagauge_counter;
            }
            if (v339 < v338->huumagauge_w - 1)
              goto LABEL_626;
            v132 = wk;
LABEL_304:
            SetHuumaMiss(v132, 0);
            goto LABEL_626;
          }
          if (!v337)
          {
            v338 = wk;
          }
          v338->huuma_counter = 0;
          v338->huumastat = 4;
          sBtlStatusBitOn(v89, 0x4000u);
          sBtlGetUnitHelperPos(v19, 0);
          sub_1B335A0(&v19->ofspos, 0, v340);
          v341 = v19->pos.x;
          z = v19->pos.z;
          v19->ofspos.w = 1.0;
          y = v19->ofspos.y;
          v19->ofspos.x = v341;
          v19->ofspos.z = z;
          sub_1B332C0(0, v341, y, z, 1.0);
          sub_1B33360(0, v19->pos.x, v19->pos.y, v19->pos.z, v19->pos.w);
          sub_1B33400(0);
          v344 = (loc_1CDE880)(0);
          sub_1949110(0);
          sub_1B33480(0, v344);
          sub_1B33360(0, v19->pos.x, v19->pos.y, v19->pos.z, v19->pos.w);
          *(__n128 *)&v345 = sub_1B33520(0);
          sub_1B335A0(&v19->ofspos, 0, v345);
          v346 = v19->vstatus & 0xFF7FFF7F;
          v19->status &= ~0x20u;
          v19->vstatus = v346 | 0x800000;
          v395.x = 0.0;
          v395.y = 0.0;
          v395.z = 0.0;
          v395.w = 0.0;
          sBtlPlaySpecialSE(v395, 1);
          v347 = wk;
          if (v347->encountno == 515)
          {
            v347 = wk;
            v347->InfiniteSpringStop_flag = 1;
          }
          v348 = v19->para->devilid;
          DevilHuumaItem = sBtlGetDevilHuumaItem(v348);
          if ((DevilHuumaItem->gageNo & 0xFFFFFFFE) == 6)
          {
LABEL_766:
            SetHuumaMiss(v19, 0);
            v354 = wk->sysmsgList;
            sBtlCreateSM(v354, v89, 158, 0, 0, 120);
            wk->huumaMiss = 1;
            PlayerData = sBtlGetPlayerData();
            huuma_devilID = wk->huuma_devilID;
            v359 = huuma_devilID[11] != -1;
            if (huuma_devilID[10] != -1)
              ++v359;
            goto LABEL_9006;
LABEL_803:
            v367 = wk->stock_num + v359;
            if (v367 >= PlayerData->stock_max)
            {
              if (!v368)
              SetHuumaMiss(v19, 0);
              v374 = wk->sysmsgList;
              v375 = v374;
              v376 = v89;
              v372 = 8;
              goto LABEL_831;
            }
            if (!v368)
            if (DlcMitama())
            {
              SetHuumaMiss(v19, 0);
              v371 = wk->sysmsgList;
              v372 = 158;
            }
            else
            {
              gageNo = DevilHuumaItem->gageNo;
              if (gageNo != 4 && gageNo != 2)
              {
                if ((v19->status & 0x10000) == 0)
                  goto LABEL_626;
                SetHuumaMiss(v19, 0);
                v380 = wk->sysmsgList;
                v376 = wk;
                v372 = 160;
                v375 = v380;
LABEL_831:
                sBtlCreateSM(v375, v376, v372, 0, 0, 120);
                wk->huumaMiss = 1;
                goto LABEL_626;
              }
              SetHuumaMiss(v19, 0);
              v371 = wk->sysmsgList;
              v372 = 159;
            }
            v375 = v371;
            v376 = v89;
            goto LABEL_831;
LABEL_801:
            if (huuma_devilID[0] != -1)
              ++v359;
            goto LABEL_803;
LABEL_799:
            if (huuma_devilID[1] != -1)
              ++v359;
            goto LABEL_801;
LABEL_797:
            if (huuma_devilID[2] != -1)
              ++v359;
            goto LABEL_799;
LABEL_795:
            if (huuma_devilID[3] != -1)
              ++v359;
            goto LABEL_797;
LABEL_793:
            if (huuma_devilID[4] != -1)
              ++v359;
            goto LABEL_795;
LABEL_791:
            if (huuma_devilID[5] != -1)
              ++v359;
            goto LABEL_793;
LABEL_789:
            if (huuma_devilID[6] != -1)
              ++v359;
            goto LABEL_791;
LABEL_787:
            if (huuma_devilID[7] != -1)
              ++v359;
            goto LABEL_789;
LABEL_785:
            if (huuma_devilID[8] != -1)
              ++v359;
            goto LABEL_787;
LABEL_9006:
            if (huuma_devilID[9] != -1)
              ++v359;
            goto LABEL_785;
LABEL_779:
            v360.n128_u64[0] = -1;
            v360.n128_u64[1] = -1;
            v361 = wk->huuma_devilID;
            v362 = vuzp1q_s16(vceqq_s32(v361[3], v360), vceqq_s32(v361[4], v360));
            v363 = vbicq_s8((int8x16_t)xmmword_3CFFD40, vceqq_s32(v361[2], v360));
            LODWORD(v361) = vaddvq_s32(v363) & 0xF;
            v363.n128_u32[0] = (u8)vaddvq_s16(vbicq_s8((int8x16_t)xmmword_3D045F0, v362));
            v363.n128_u64[0] = vcnt_s8((int8x8_t)v363.n128_u64[0]).n64_u64[0];
            v363.n128_u16[0] = vaddlv_u8((uint8x8_t)v363.n128_u64[0]);
            v364 = v363.n128_u32[0];
            v363.n128_u32[0] = (u32)v361;
            v363.n128_u64[0] = vcnt_s8((int8x8_t)v363.n128_u64[0]).n64_u64[0];
            v363.n128_u16[0] = vaddlv_u8((uint8x8_t)v363.n128_u64[0]);
            v359 = v364 + v363.n128_u32[0];
            goto LABEL_803;
          }
          v352 = v19->para->devilid;
          if ((u32)(v352 - 409) <= 7)
          {
            goto LABEL_766;
          }
          PlayerData = sBtlGetPlayerData();
          goto LABEL_779;
        }
        if (!v254)
        v258 = sBtlIsBattleKey(4167, 2);
        if (!v258)
          goto LABEL_573;
        if (huuma_auto)
        {
LABEL_573:
          if ((v250 & sBtlIsBattleKey(4167, 1)) == 1)
          {
            v265 = wk;
            huumagauge_pcnt = v265->huumagauge_pcnt;
            v265->huuma_keycnt = 0;
            p_huumagauge_pcnt = &v265->huumagauge_pcnt;
            huumagauge_pcmpcnt = v265->huumagauge_pcmpcnt;
            v265->huumagauge_pcnt = huumagauge_pcnt + 1;
            LimitRange(p_huumagauge_pcnt, 0, huumagauge_pcmpcnt);
            v269 = wk;
            if (v269->huumagauge_pcnt >= v269->huumagauge_pcmpcnt)
            {
              v269 = wk;
              huumagauge_ppara = v269->huumagauge_ppara;
              v269->huumagauge_pcnt = 0;
              v272 = huumagauge_ppara;
              v269 = wk;
              v273 = huuma_hossei * v272;
              v274 = v273;
              if (v273 == INFINITY)
                v274 = 0x80000000;
              v269->huumagauge_counter -= v274;
              v393.x = 0.0;
              v393.y = 0.0;
              v393.z = 0.0;
              v393.w = 0.0;
              sBtlPlaySpecialSE(v393, 2);
              HuumaAnimCall(wk->bsc, 0);
              v275 = wk;
              huumagauge_counter_start = v275->huumagauge_counter_start;
              v277 = v275->huumagauge_counter;
              v386 = 0;
              SZ = 0;
              v278 = (f32)(100.0 / (f32)huumagauge_counter_start) * (f32)v277;
              v279 = 100.0 - v278;
              sBtlGetUnitHelperPos(v19, 1);
              sub_1B335A0(&v386, 0, v280);
              if (v279 < 35.0)
              {
                v281 = v386;
                v282 = *(f32 *)&SZ;
LABEL_690:
                v310 = 4;
LABEL_693:
                Add(v310, *(f32 *)&v281, *((f32 *)&v281 + 1), v282, -1, 0);
                goto LABEL_694;
              }
              if (v279 >= 65.0)
              {
                v282 = *(f32 *)&SZ;
                v281 = v386;
              }
              else
              {
                v293 = sub_1905740(100, 0);
                v282 = *(f32 *)&SZ;
                v281 = v386;
                if (v293 <= 0x31)
                  goto LABEL_690;
              }
              v310 = 5;
              goto LABEL_693;
            }
          }
LABEL_694:
          goto LABEL_695;
        }
        v261 = wk;
        if (v261->huuma_keycnt <= 4)
        {
          goto LABEL_573;
        }
        v261 = wk;
        v294 = v261->huumagauge_pcnt;
        v261->huuma_keycnt = 0;
        v295 = &v261->huumagauge_pcnt;
        v297 = v261->huumagauge_pcmpcnt;
        v261->huumagauge_pcnt = v294 + 1;
        LimitRange(v295, 0, v297);
        v298 = wk;
        if (v298->huumagauge_pcnt < v298->huumagauge_pcmpcnt)
          goto LABEL_694;
        v298 = wk;
        v299 = v298->huumagauge_ppara;
        v298->huumagauge_pcnt = 0;
        v301 = v299;
        v298 = wk;
        v302 = huuma_hossei * v301;
        v303 = v302;
        if (v302 == INFINITY)
          v303 = 0x80000000;
        v298->huumagauge_counter -= v303;
        v394.x = 0.0;
        v394.y = 0.0;
        v394.z = 0.0;
        v394.w = 0.0;
        sBtlPlaySpecialSE(v394, 2);
        HuumaAnimCall(wk->bsc, 0);
        v304 = wk;
        v305 = v304->huumagauge_counter_start;
        v306 = v304->huumagauge_counter;
        v388 = 0;
        v389 = 0;
        v307 = (f32)(100.0 / (f32)v305) * (f32)v306;
        v308 = 100.0 - v307;
        sBtlGetUnitHelperPos(v19, 1);
        sub_1B335A0(&v388, 0, v309);
        if (v308 < 35.0)
        {
          v282 = *(f32 *)&v389;
          v281 = v388;
          goto LABEL_690;
        }
        if (v308 >= 65.0)
        {
          v383 = *(f32 *)&v389;
          v382 = v388;
        }
        else
        {
          v381 = sub_1905740(100, 0);
          v382 = v388;
          v383 = *(f32 *)&v389;
          if (v381 <= 0x31)
          {
            v384 = 4;
            goto LABEL_849;
          }
        }
        v384 = 5;
LABEL_849:
        Add(v384, *(f32 *)&v382, *((f32 *)&v382 + 1), v383, -1, 0);
        v89 = wk;
        goto LABEL_695;
LABEL_550:
        if (!huuma_auto)
          goto LABEL_547;
        goto LABEL_551;
      }
LABEL_9007:
      goto LABEL_550;
    case 2:
      v28 = wk;
      if (v28->huumamagnone)
      {
        v92 = 20;
      }
      else
      {
        v28 = wk;
        if (v28->huumaMiss)
          v92 = 90;
        else
          v92 = 10;
      }
      v164 = wk;
      if (v164->huuma_counter == 1)
      {
        v164 = wk;
        if (v164->huumacancel)
        {
          v164 = wk;
          v165 = v164->sysmsgList;
          sBtlReleaseSM_List(v165, 1u);
        }
      }
      if (sBtlLoadHuuma_MesData())
      {
        v167 = wk;
        if (v167->huuma_counter >= v92)
        {
          v167 = wk;
          v167->huumastat = 9;
          sBtlSetNSTOP();
          wk->motion_EndNoCng = 0;
          sBtlZakoWarpReset(v19);
          EndLoop();
        }
      }
      goto LABEL_626;
    case 3:
      v28 = wk;
      if (!v28->huumacancel)
      {
        v28 = wk;
        if (!v28->huumaMiss)
        {
          v28 = wk;
          if (!v28->huumamagnone)
          {
            if (wk->para->level >= v19->para->level)
            {
              if (!v93)
              {
                v28 = wk;
              }
              v283 = v28->sysmsgList;
              v97 = 59;
              v95 = v283;
              v96 = wk;
            }
            else
            {
              if (!v93)
              {
                v28 = wk;
              }
              v94 = v28->sysmsgList;
              v95 = v94;
              v96 = wk;
              v97 = 6;
            }
            sBtlCreateSM(v95, v96, v97, 0, 0, 120);
          }
        }
      }
      RestartBattle();
      sBtlResetNSTOP();
      sBtlResetAction(wk);
      sBtlStatusBitOff(wk, 0xFFFFFFEF);
      sBtlSetAction(wk, 1, 0);
      sBtlSetMotion(wk, 130, 0, 0, 0);
      sBtlStatusBitOff(wk, 0xFFFFBFFF);
      wk->huuma_targetID = -1;
      ResetPost();
      sBtlPopAllDisp(wk);
      wk->huuma_weakicon = 1;
      goto LABEL_626;
    case 4:
      sub_1905740(100, 0);
      v99 = wk;
      v99->huumastat = 1280;
      v99->huuma_counter = 0;
      sBtlStatusBitOn(wk, 0x10u);
      sBtlStatusBitOn(v19, 0x10u);
      v100 = get_Instance(0);
      AllDisp(v100, 1, 0, 0);
      MOON_OUT();
      HuumaGageOff = 0;
      CalcCamPost_StepSet(20);
      goto LABEL_626;
    case 5:
      v103 = v19->para->devilid;
      huumaID = sBtlGetDevilData(v103, -1)->huumaID;
      v107 = 0;
      gYorosiku_DevilID = huumaID;
      gYorosiku_SmgLoad = 1;
      while (1)
      {
        v110 = wk->UnitMng;
        if (v107 >= v110->number)
        {
          goto LABEL_470;
        }
        v110 = wk->UnitMng;
        v111 = v110->pUnitL[v107]->pUnit;
        if (v111 && (v111->side & 0x80) == 0)
        {
          if (gYorosiku_DevilID == v111->para->devilid)
            break;
        }
        ++v107;
      }
      gYorosiku_SmgLoad = 0;
LABEL_470:
      if (gYorosiku_SmgLoad)
      {
        DevilSE = GetDevilSE(gYorosiku_DevilID, -1);
        p2sdLoadSMGFile(DevilSE);
        p2sdLoadSMGFile(DevilSE + 0x10000000);
      }
      v210 = gYorosiku_DevilID;
      v211 = GetDevilSE(v210, 17);
      sBtlStopSE(v211);
      sBtlPlaySESub(v211, 127);
      bst_effserialID2 = v19->bst_effserialID2;
      v19->hstatus |= 0x400000u;
      if (bst_effserialID2 != -1)
      {
        bst_effserialID2 = v19->bst_effserialID2;
        effList = wk->effList;
        sBtlSetDecAlpha_SerialID2(effList, bst_effserialID2, 2);
        sBtlDeleteEffectData_SerialID2(wk->effList, v19->bst_effserialID2);
        v19->bst_effserialID2 = -1;
      }
      v216 = v19->pos.x;
      v217 = v19->pos.y;
      v218 = wk->effList;
      v220 = v19->pos.z;
      w = v19->pos.w;
      v392.x = v216;
      v392.y = v217;
      v392.z = v220;
      v392.w = w;
      sBtlCreateEff(v218, v19, 4, 0, v392, 0x80808080, 0, 1.0, 0);
      sBtlSetFade(v19, 1026, 0, 0, 1);
      sBtlSetMotionHitStop(v19, 0.01, 5.0, 0.0);
      MagAddUnitHeight(v19, 5, 90);
      MagAddUnitHeight(v19, 5, 50);
      MagAddUnitHeight(v19, 5, 20);
      EndLoop();
      v224 = wk;
      v224->huuma_return_cnt = 0;
      v224->huumastat = 240;
      CalcCamPost_StepSet(60);
      goto LABEL_626;
    case 6:
      v28 = wk;
      ++v28->huuma_return_cnt;
      if (wk->motionno != 136)
        goto LABEL_222;
      v113 = wk->hModel;
      mdlGetMotionFrameF(v113);
      if (sBtlCheckMotionEnd(wk))
      {
        wk->motion_EndNoCng = 0;
        sBtlSetMotion(wk, 0, 0, 0, 0);
LABEL_222:
        if (wk->huuma_return_cnt >= 128)
        {
          if (gYorosiku_SmgLoad)
          {
            v116 = wk;
            v117 = gYorosiku_DevilID;
            v118 = GetDevilSE(v117, 17);
            sBtlStopSE(v118);
            v119 = GetDevilSE(gYorosiku_DevilID, -1);
            p2sdLoadSMGFile(v119);
            p2sdLoadSMGFile(v119 + 0x10000000);
          }
          else
          {
            v116 = wk;
          }
          sBtlResetAction(v116);
          sBtlStatusBitOff(v116, 0xFFFFFFEF);
          v230 = wk->effList;
          sBtlForceDelete_ID_Return(v230, v19);
          sBtlSetAction(v19, 10, 0);
          v231 = wk;
          v232 = v231->huumastat;
          v231->huuma_targetID = -1;
          v231->huuma_getUnit = 0;
          v231->huumastat = v232 + 1;
          v19->hstatus |= 2u;
          sBtlStatusBitOff(v116, 0xFFFFBFFF);
          v233 = wk;
          v233->eventno = 5;
          v233->eventgstat = 0;
          v233->nego_gstat = 0;
          v233->eventListID = v19->ListID;
          v233->status |= 0x400u;
          sBtlSetNSTOP();
          ResetPost();
          sBtlPopAllDisp(v116);
          wk->huuma_weakicon = 1;
        }
      }
      goto LABEL_626;
    case 7:
      goto LABEL_626;
    case 8:
      v28 = wk;
      v120 = v28->huuma_counter;
      if (v120 >= 30)
      {
        if (!v121)
        {
          v28 = wk;
        }
        if (v28->huumamagnone)
        {
          if (!v148)
          {
            v28 = wk;
          }
          v28->huumastat = 2;
          sBtlStatusBitOff(wk, 0xFFFFBFFF);
          wk->huuma_counter = 0;
        }
        else
        {
          if (!v148)
          {
            v28 = wk;
          }
          v28->huumastat = 1;
          sBtlStatusBitOff(wk, 0xFFFFBFFF);
          wk->huuma_counter = 0;
          CalcCamPost_StepSet(10);
        }
      }
      else
      {
        if (!v121)
        {
          v28 = wk;
          v120 = v28->huuma_counter;
        }
        if (v120 == 16)
        {
          v28 = wk;
          if (v28->huumamagnone)
          {
            v28 = wk;
            v122 = v28->sysmsgList;
            sBtlCreateSM(v122, wk, 54, 0, 0, 120);
            v391.x = 0.0;
            v391.y = 0.0;
            v391.z = 0.0;
            v391.w = 0.0;
            sBtlPlaySpecialSE(v391, 3);
          }
        }
      }
      goto LABEL_626;
    case 9:
      v28 = wk;
      status_high = HIBYTE(v28->status);
      v28->huumastat = 10;
      v28->huuma_counter = 0;
      if ((status_high & 8) != 0)
      {
        effStopEffectStop();
        wk->status &= ~0x8000000u;
      }
      goto LABEL_626;
    case 0xA:
      v28 = wk;
      if (v28->huuma_counter >= 4)
      {
        v28 = wk;
        v28->huumastat = 3;
        sBtlStatusBitOff(wk, 0xFFFFBFFF);
      }
      goto LABEL_626;
    default:
      if (v30 != 240)
      {
        if (v30 == 241)
        {
          v28 = wk;
          v125 = v28->huuma_return_cnt + 1;
          v126 = v28->huuma_return_cnt - 85 < 0;
          v28->huuma_return_cnt = v125;
          if (v126 == __OFSUB__(v125, 86))
          {
            v28 = wk;
            v63 = 256;
            goto LABEL_136;
          }
        }
        goto LABEL_626;
      }
      v28 = wk;
      huuma_return_cnt = v28->huuma_return_cnt;
      v170 = huuma_return_cnt + 1;
      v28->huuma_return_cnt = huuma_return_cnt + 1;
      if (huuma_return_cnt + 1 <= 30)
      {
        if (v170 > 15)
        {
          if (huuma_return_cnt == 19)
          {
            v171 = 5;
            v228 = v19;
            v172 = 60;
            goto LABEL_659;
          }
          if (huuma_return_cnt != 24)
          {
            if (huuma_return_cnt != 29)
              goto LABEL_660;
            v171 = 5;
            v228 = v19;
            v172 = 30;
            goto LABEL_659;
          }
          v172 = 80;
          goto LABEL_654;
        }
        if (huuma_return_cnt == 9)
        {
          v171 = 5;
          v172 = 90;
          goto LABEL_658;
        }
        if (huuma_return_cnt != 14)
          goto LABEL_660;
LABEL_603:
        v172 = 50;
        goto LABEL_654;
      }
      if ((u32)v170 <= 0x2D)
      {
        if (huuma_return_cnt != 34)
        {
          if (huuma_return_cnt == 39)
          {
            v171 = 5;
            v172 = 75;
            goto LABEL_658;
          }
          if (huuma_return_cnt != 44)
            goto LABEL_660;
          v172 = 90;
LABEL_654:
          v228 = v19;
          v171 = 4;
          goto LABEL_659;
        }
        goto LABEL_603;
      }
      if (huuma_return_cnt == 49)
      {
        v171 = 5;
        v172 = 45;
LABEL_658:
        v228 = v19;
        goto LABEL_659;
      }
      if (huuma_return_cnt != 54)
      {
        if (huuma_return_cnt != 59)
          goto LABEL_660;
        v171 = 5;
        v172 = 20;
        goto LABEL_658;
      }
      v228 = v19;
      v171 = 4;
      v172 = 30;
LABEL_659:
      MagAddUnitHeight(v228, v171, v172);
LABEL_660:
      if (wk->huuma_return_cnt >= 111)
      {
        wk->motion_EndNoCng = 0;
        sBtlSetMotion(wk, 136, 0, 0, 0);
        sBtlStatusBitOn(wk, 0x10u);
        v63 = 241;
        v28 = wk;
        goto LABEL_136;
      }
LABEL_626:
      CalcCamPost_Update();
      if (wk->huuma_targetID != -1)
      {
        if (HuumaGageOff)
          goto LABEL_634;
      }
      HuumaGageOff(wk->bsc, 0, 0);
      return 2;
LABEL_634:
      HuumaGageDraw(wk->bsc, v19, (f32)(wk->huumagauge_w - wk->huumagauge_counter), (f32)wk->huumagauge_w, 0);
      return 2;
  }
}

// 0x1f9ef10
static bool HuumaMitama(s32 devilid) {
  return (u32)(devilid - 409) < 8;
}

// 0x1f90040
static bool FalseHuuma(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBATTLE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  SBATTLE_WORK *v13;
  s32 huumastat;
  s32 ListID;
  s64 i;
  SBTLUNIT_LISTWORK *v19;
  SBTLUNIT_WORK *pUnit;

  v4 = wk;
  if (!v4->huumastat)
  {
    if (v4->mode != 12)
      return 1;
  }
  v6 = wk;
  UnitMng = v6->UnitMng;
  huuma_targetID = v6->huuma_targetID;
  v9 = sBtlSearchUnit_ID(UnitMng, huuma_targetID);
  if (!v9)
    goto LABEL_48;
  v10 = v9;
  sBtlSetAction(v10, 9, 0);
  sBtlStatusBitOff(v10, 0xFFFFBFFF);
  sBtlCheckResetBadStatus(v10);
  v13 = wk;
  huumastat = (u16)v13->huumastat;
  if (huumastat == 1)
  {
    v13 = wk;
    v13->eventgstat = 0;
    v13->eventno = 2;
    ListID = wk->ListID;
    v13->nego_gstat = 0;
    v13->eventListID = ListID;
    v13->status |= 0x400u;
    for (i = 0; ; ++i)
    {
      v19 = wk->UnitMng;
      if (i >= v19->number)
        goto LABEL_48;
      pUnit = v19->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if (pUnit->hModel)
        pUnit->vstatus |= 0x8000000u;
    }
  }
  huumastat = (u16)wk->huumastat;
  if (huumastat != 6)
  {
    wk->motion_EndNoCng = 0;
    sBtlSetMotion(wk, 136, 4, 0, 0);
  }
LABEL_48:
  wk->huumastat = 0;
  return 1;
}

// 0x1f9e240
static void HuumaGetItemInit(SBTLUNIT_WORK *wklock) {
  s32 devilid;
  s64 gageNo;
  u32 v7;
  s32 *v8;
  s32 *v9;
  s32 *v10;
  s32 huuma_get_max;
  s64 v13;
  s32 *m_Items;
  s32 *v15;
  s32 v16;
  s32 *v17;
  s32 v18;
  s64 v19;

  devilid = wklock->para->devilid;
  gageNo = (u32)sBtlGetDevilHuumaItem(devilid)->gageNo;
  if ((s32)gageNo <= 0)
  {
    wklock->huuma_get_max = -1;
    return;
  }
  if (!wklock->initHuuma)
  {
    v7 = gageTbl[gageNo];
    wklock->huuma_get_max = v7;
    v8 = NewSpecific(s32, v7);
    wklock->huuma_get_cnt = v8;
    v9 = NewSpecific(s32, wklock->huuma_get_max);
    wklock->huuma_get_flg = v9;
    v10 = NewSpecific(s32, wklock->huuma_get_max);
    wklock->huuma_get_rnd = v10;
    huuma_get_max = wklock->huuma_get_max;
    if (huuma_get_max >= 1)
    {
      v13 = 0;
      m_Items = wklock->huuma_get_flg;
      v15 = wklock->huuma_get_cnt;
      v16 = wk->huumagauge_w / (huuma_get_max + 1);
      v17 = wklock->huuma_get_rnd;
      v18 = v16;
      do
      {
        v19 = v13++;
        v15[v19] = v18;
        v18 += v16;
        m_Items[v19] = 0;
        v17[v19] = 0;
      }
      while (v13 < wklock->huuma_get_max);
    }
    wklock->initHuuma = 1;
  }
}

// 0x1f9e1d0
static bool DlcMitama(void) {
  return (u32)(sBtlGetDlcMapNo() - 1) < 3;
}

// 0x1f9e990
static bool HuumaGetItemCalc(SBTLUNIT_WORK *wklock) {
  s32 devilid;
  DEVIL_HUUMAITEM *DevilHuumaItem;
  s64 v6;
  s32 *huuma_get_flg;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 failureRitu;
  s32 v12;
  s32 *getItem;
  s64 v14;
  s32 v15;
  s64 v16;
  s32 v17;
  s32 kuda_id;
  s32 DlcMapNo;
  s32 v22;
  SBTLSM_LISTWORK *v24;
  bool v25;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v29;
  SBTLSM_LISTWORK *v31;

  if (wklock->huuma_get_max < 1)
    return 0;
  devilid = wklock->para->devilid;
  DevilHuumaItem = sBtlGetDevilHuumaItem(devilid);
  if (wklock->huuma_get_max < 1)
    return 0;
  v6 = 0;
  huuma_get_flg = wklock->huuma_get_flg;
  v8 = wk->huumagauge_w - wk->huumagauge_counter;
  while (1)
  {
    if (huuma_get_flg[v6] || wklock->huuma_get_cnt[v6] > v8)
      goto LABEL_12;
    v9 = sub_1905740(101, 0);
    wklock->huuma_get_rnd[v6] = v9;
    if (DevilHuumaItem->gageNo == 6)
      break;
    failureRitu = DevilHuumaItem->failureRitu;
    v12 = v9;
    if (failureRitu && failureRitu > v9)
    {
      v25 = 0;
      wklock->huuma_get_flg[v6] = -1;
      return v25;
    }
    getItem = DevilHuumaItem->getItem;
    if (SLODWORD(getItem->max_length) >= 1)
    {
      v14 = 8;
      while (2)
      {
        if (*((s32 *)&getItem->obj.klass + v14) < 1)
          goto LABEL_29;
        failureRitu += *((u32 *)&DevilHuumaItem->getRitu->obj.klass + v14);
        if (failureRitu < v12)
          goto LABEL_29;
        v17 = wklock->para->devilid;
        kuda_id = (u8)sBtlGetDevilData(v17, -1)->kuda_id;
        if ((u32)v14 == 12)
        {
          if (kuda_id == 9)
            goto LABEL_49;
          goto LABEL_28;
        }
        if ((u32)v14 != 9)
          goto LABEL_28;
        goto LABEL_39;
LABEL_40:
        DlcMapNo = sBtlGetDlcMapNo();
        if (kuda_id == 9)
          goto LABEL_28;
        goto LABEL_9001;
LABEL_39:
        goto LABEL_40;
        if (kuda_id == 9)
        {
LABEL_28:
          getItem = DevilHuumaItem->getItem;
          v15 = *((u32 *)&getItem->obj.klass + v14);
          if (v15 >= 1)
          {
            wklock->huuma_get_flg[v6] = v15;
            sysmsgList = wk->sysmsgList;
            sBtlCreateSM(sysmsgList, wklock, 162, v15, 0, 60);
            v25 = 1;
            v29 = v15;
            goto LABEL_72;
          }
LABEL_29:
          v16 = v14 - 7;
          ++v14;
          if (v16 >= SLODWORD(getItem->max_length))
            goto LABEL_11;
          continue;
        }
LABEL_9001:
        break;
      }
      if ((u32)(DlcMapNo - 1) >= 3)
      {
LABEL_49:
        v22 = *((u32 *)&DevilHuumaItem->getItem->obj.klass + v14);
        wklock->huuma_get_flg[v6] = v22 + 100000;
        v24 = wk->sysmsgList;
        sBtlCreateSM(v24, wklock, 163, v22, 0, 60);
        datAddMoney(v22);
        return 1;
      }
      goto LABEL_28;
    }
LABEL_11:
    huuma_get_flg = wklock->huuma_get_flg;
    huuma_get_flg[v6] = -2;
LABEL_12:
    if (++v6 >= wklock->huuma_get_max)
      return 0;
  }
  huuma_get_flg = wklock->huuma_get_flg;
  if (huuma_get_flg[0] || (v10 = DevilHuumaItem->getItem[0], v10 < 1))
  {
    if (huuma_get_flg[1] || (v10 = DevilHuumaItem->getItem[2], v10 <= 0))
    {
      if (huuma_get_flg[2])
        goto LABEL_12;
      v10 = DevilHuumaItem->getItem[3];
      if (v10 <= 0)
        goto LABEL_12;
    }
  }
  huuma_get_flg[v6] = v10;
  v31 = wk->sysmsgList;
  sBtlCreateSM(v31, wklock, 162, v10, 0, 60);
  v25 = 1;
  v29 = v10;
LABEL_72:
  datAddItem(v29, 1);
  return v25;
}

// 0x1f9f0f0
static void MagAddUnitHeight(SBTLUNIT_WORK *wkEnemy, s32 _Var, s32 _Par) {
  f32 *p_x;
  u16 major;
  s32 minor;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 z;
  f32 v16;
  bool v17;
  f32 x;

  sBtlGetUnitHelperPos(wkEnemy, 1);
  p_x = &vf00.x;
  major = wkEnemy->major;
  minor = wkEnemy->minor;
  v11 = p_x[4];
  v12 = p_x[5];
  v13 = p_x[6];
  v14 = (f32)(sBtlGetVisualData(major, minor)->nml->height / 100.0)
      * (f32)Par;
  z = wkEnemy->pos.z;
  v16 = wkEnemy->pos.y - v14;
  v17 = v14 < 10.0;
  if (v14 >= 10.0)
    x = wkEnemy->pos.x;
  else
    x = v11;
  if (v17)
  {
    z = v13;
    v16 = v12;
  }
  Add(Var, x, v16, z, -1, 0);
}

// 0x1f9c530
static bool ChkHuuma_PlayerInputOk(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  u32 mode;
  bool v6;
  s32 v7;
  u32 v10;

  v4 = wk;
  mode = v4->mode;
  v6 = mode > 0x1B;
  v7 = (1 << mode) & 0x8E8C008;
  if (!v6 && v7 != 0)
  {
    if (v4->bHuumaCancel)
      return 1;
  }
  if (!gNowActionPause)
    goto LABEL_24;
  if (wk->mode != 3)
    goto LABEL_24;
  v10 = wk->actwk->use_skillid - 1308;
  if (v10 < 0x26 && ((0x3B9FFF907DuLL >> v10) & 1) != 0)
    return 1;
LABEL_24:
  if (wk->mode != 1)
    return 0;
  return sBtlCheckMove(wk);
}

// 0x1f7bc10
void sBtlHuumaRangeCircleProc(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  s32 mode;
  void *Instance;
  s64 v9;
  char v10;
  f32 RotToDir;
  f32 PosToDir;
  f32 AtoB_LR_ABS;
  bool v14;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  bool v23;
  sdfVector4_t v24;

  v5 = wk;
  if (v5->battlemode == 1)
    return;
  if (v5->mode == 12)
    goto LABEL_28;
  v5 = wk;
  if (!v5->cmbSkl->bRun)
    goto LABEL_15;
LABEL_28:
  DeleteAll();
  return;
LABEL_15:
  if ((wk->vstatus & 0x8000) != 0)
    goto LABEL_28;
  v5 = wk;
  mode = v5->mode;
  if (mode == 5)
    goto LABEL_28;
  mode = wk->mode;
  if (mode == 18)
    goto LABEL_28;
  if (!sBtlIsBattleKey(4169, 1))
    goto LABEL_28;
  Instance = get_Instance(0);
  BattleDispUIOn(Instance, 0);
  v9 = 0;
  v10 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v9 >= UnitMng->number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[v9]->pUnit;
    if (pUnit)
    {
      if (sBtlCheckDamageTarget(pUnit) && (pUnit->side & 2) != 0)
      {
        devilid = pUnit->para->devilid;
        if ((u32)(devilid - 261) <= 0xFFFFFFFC && (devilid & 0xFFFFFFFC) != 0x138)
        {
          x = wk->rot.x;
          y = wk->rot.y;
          z = wk->rot.z;
          w = wk->rot.w;
          v24.x = x;
          v24.y = y;
          v24.z = z;
          v24.w = w;
          RotToDir = sBtlGetRotToDir(v24);
          PosToDir = sBtlGetPosToDir(wk->pos.x, wk->pos.z, pUnit->pos.x, pUnit->pos.z);
          AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(RotToDir, PosToDir);
          v14 = sBtlGetLenXZ(wk->pos.x, wk->pos.z, pUnit->pos.x, pUnit->pos.z) <= (f32)(pUnit->actaiwk->hit_area_r + 200.0)
             && AtoB_LR_ABS < 135.0;
          v10 |= v14;
          Add(pUnit->ListID, pUnit->actaiwk->hit_area_r, v14, 0);
        }
      }
    }
    ++v9;
  }
  v23 = ChkHuuma_PlayerInputOk(wk);
  Add(wk->ListID, 200.0, v23 & v10 & 1, 0);
}

// 0x1f9cf90
static void CalcCamPost_Init(void) {
  void *Instance;
  void *mDof;
  void *monitor;
  void *v8;
  UnityEngine_Object_c *klass;
  void *v10;
  intptr_t m_CachedPtr;
  void *v12;
  void *v13;
  void *v14;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v21;
  SBTLUNIT_WORK *v22;
  SBTLCAMERA_WORK *camera;
  f32 *v24;
  u16 major;
  s32 minor;
  V_POSITION_WORK *nml;
  f32 v29;
  f32 x;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 *v34;
  f32 v36;
  f32 z;
  f32 PosToDir;
  f32 v39;
  f32 v40;
  f32 y;
  f32 v43;
  f32 v46;
  __int128 v48;
  s64 ToX;
  s64 ToZ;

  ToZ = 0;
  ToX = 0;
  *(u64 *)&gCamPost_Step = 0;
  gCam_Fovy_Now = 45.0;
  *(u64 *)&gCam_UpV_Now = 0;
  *(u64 *)&gFilmGrainOw_intensity_Now = 0;
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    goto LABEL_14;
  mDof = Instance->mDof;
  if (!op_Inequality(Instance->mDof, 0, 0))
    goto LABEL_14;
  goto LABEL_13;
  if (op_Inequality(mDof, 0, 0))
  {
LABEL_13:
    monitor = mDof[2].monitor;
    v8 = Allocate(UnityEngine_Rendering_Universal_DepthOfFieldModeParameter);
    _ctor(v8, 2, 1, 0);
    (*(*(u64 *)monitor + 440))(monitor, v8, *(u64 *)(*(u64 *)monitor + 448));
    klass = mDof[4].klass;
    v10 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v10, 2.5, 1, 0);
    (*(klass->_1.image + 55))(klass, v10, *((u64 *)klass->_1.image + 56));
    m_CachedPtr = mDof[4].m_CachedPtr;
    v12 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v12, 80.0, 1, 0);
    (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v12, *(u64 *)(*(u64 *)m_CachedPtr + 448));
    v13 = mDof[4].monitor;
    v14 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v14, 10.0, 1, 0);
    (*(*(u64 *)v13 + 440))(v13, v14, *(u64 *)(*(u64 *)v13 + 448));
    SetForceActiveDofSetting(Instance, 1, 0);
  }
LABEL_14:
  if (!op_Inequality(Instance, 0, 0))
  {
    goto LABEL_17;
  }
  PushVignetteSetting(Instance, 0);
LABEL_17:
  if (!!op_Inequality(Instance, 0, 0))
    PushFilmGrainSetting(Instance, 0);
  if (op_Inequality(Instance, 0, 0))
    PushChromaticAberrationSetting(Instance, 0);
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v21 = sBtlSearchUnit_ID(UnitMng, playerID);
  v22 = sBtlSearchUnit_ID(wk->UnitMng, wk->huuma_targetID);
  camera = wk->scene->camera;
  if (v21)
  {
    v24 = v22;
    if (v22)
    {
      major = v22->major;
      minor = v22->minor;
      nml = sBtlGetVisualData(major, minor)->nml;
      v29 = v24[41];
      x = v21->pos.x;
      if ((f32)(nml->height * 0.5) >= 90.0)
        v31 = nml->height * 0.5;
      else
        v31 = 90.0;
      v32 = v24[41];
      v33 = v21->pos.x;
      v34[53] = v29 + (f32)((f32)(x - v29) * 0.5);
      v34[54] = v24[42] - v31;
      v36 = v24[43];
      z = v21->pos.z;
      v34[55] = v36 + (f32)((f32)(z - v36) * 0.5);
      PosToDir = sBtlGetPosToDir(v33, z, v32, v36);
      v39 = sBtlGet360(PosToDir + 115.0);
      v40 = sBtlGet360(PosToDir + -115.0);
      sBtlGetMoveXZ(v21->pos.x, v21->pos.z, v39, 230.0, (f32 *)&ToZ + 1, &ToZ);
      sBtlGetMoveXZ(v21->pos.x, v21->pos.z, v40, 230.0, (f32 *)&ToX + 1, &ToX);
      sBtlGetLenXZ(camera->camerapos.x, camera->camerapos.z, *((f32 *)&ToZ + 1), *(f32 *)&ToZ);
      sBtlGetLenXZ(camera->camerapos.x, camera->camerapos.z, *((f32 *)&ToX + 1), *(f32 *)&ToX);
      gCamPost_CamGoalX = *((f32 *)&ToZ + 1);
      y = v21->pos.y;
      gCamPost_R0L1 = 0;
      v43 = *(f32 *)&ToZ;
      gCamPost_CamGoalY = y + -80.0;
      gCamPost_CamGoalZ = v43;
      CalcCamPost_StepSet(0);
    }
  }
  v46 = camera->targetpos.x;
  gCamPost_TgtNowX = v46;
  *(u64 *)&v48 = *(u64 *)&camera->targetpos.y;
  *((u64 *)&v48 + 1) = *(u64 *)&camera->camerapos.x;
  *(_OWORD *)&gCamPost_TgtNowY = v48;
  gCamPost_CamNowZ = camera->camerapos.z;
}

// 0x1f9e470
static void CalcCamPost_StepSet(s32 _Step) {
  void *Instance;
  void *mBloom;
  f32 v5;
  f32 v7;
  f32 v8;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;
  bool v16;
  u16 major;
  f32 *v18;
  s32 minor;
  V_POSITION_WORK *nml;
  f32 v22;
  f32 x;
  f32 v24;
  f32 v25;
  f32 v26;
  void *v27;
  f32 v28;
  f32 v30;
  f32 v31;
  s64 v33;
  f32 *v34;
  f32 v35;
  f32 z;
  f32 PosToDir;
  f32 v39;
  f32 v40;
  f32 v42;
  s64 v45;
  s64 ToZ;

  v45 = 0;
  ToZ = 0;
  Instance = get_Instance(0);
  if (Step > 30)
  {
    if (Step != 40)
    {
      if (Step == 50)
      {
        if (op_Inequality(Instance, 0, 0))
        {
          PopVignetteSetting(Instance, 0);
          PopFilmGrainSetting(Instance, 0);
          PopChromaticAberrationSetting(Instance, 0);
        }
      }
      else if (Step == 60)
      {
        if (op_Inequality(Instance, 0, 0))
        {
          mBloom = Instance->mBloom;
          v5 = (mBloom->threshold->klass->vtable._14_get_value.methodPtr)(&mBloom->threshold->klass, mBloom->threshold->klass->vtable._14_get_value.method);
          v7 = v5;
          gBloom_threshold_Bk = v7;
          gBloom_intensity_Bk = (mBloom->intensity->klass->vtable._14_get_value.methodPtr)(&mBloom->intensity->klass, mBloom->intensity->klass->vtable._14_get_value.method);
          v8 = (mBloom->scatter->klass->vtable._14_get_value.methodPtr)(&mBloom->scatter->klass, mBloom->scatter->klass->vtable._14_get_value.method);
          gBloom_threshold_Now = 0.5;
          gBloom_scatter_Bk = v8;
          *(u64 *)&gBloom_intensity_Now = 0x3F4CCCCD40800000LL;
        }
      }
      goto LABEL_46;
    }
    goto LABEL_17;
  }
  if (Step != 20)
  {
    if (Step != 30)
      goto LABEL_46;
LABEL_17:
    UnitMng = wk->UnitMng;
    playerID = wk->playerID;
    v14 = sBtlSearchUnit_ID(UnitMng, playerID);
    v15 = sBtlSearchUnit_ID(wk->UnitMng, wk->huuma_targetID);
    if (v14)
      v16 = v15 == 0;
    else
      v16 = 1;
    if (!v16)
    {
      major = v15->major;
      v18 = v15;
      minor = v15->minor;
      nml = sBtlGetVisualData(major, minor)->nml;
      v22 = v18[41];
      x = v14->pos.x;
      if ((f32)(nml->height * 0.5) >= 90.0)
        v24 = nml->height * 0.5;
      else
        v24 = 90.0;
      v25 = v18[41];
      v26 = v14->pos.x;
      v34[53] = v22 + (f32)((f32)(x - v22) * 0.5);
      v34[54] = v18[42] - v24;
      v35 = v18[43];
      z = v14->pos.z;
      v34[55] = v35 + (f32)((f32)(z - v35) * 0.5);
      PosToDir = sBtlGetPosToDir(v26, z, v25, v35);
      v39 = sBtlGet360(PosToDir + 115.0);
      v40 = sBtlGet360(PosToDir + -115.0);
      sBtlGetMoveXZ(v14->pos.x, v14->pos.z, v39, 230.0, (f32 *)&ToZ + 1, &ToZ);
      sBtlGetMoveXZ(v14->pos.x, v14->pos.z, v40, 230.0, (f32 *)&v45 + 1, &v45);
      gCamPost_CamGoalX = *((f32 *)&v45 + 1);
      v42 = *(f32 *)&v45;
      gCamPost_CamGoalY = v14->pos.y + -80.0;
      gCamPost_CamGoalZ = v42;
    }
    goto LABEL_46;
  }
  if (op_Inequality(Instance, 0, 0))
  {
    v27 = Instance->mBloom;
    v28 = (v27->threshold->klass->vtable._14_get_value.methodPtr)(&v27->threshold->klass, v27->threshold->klass->vtable._14_get_value.method);
    v30 = v28;
    gBloom_threshold_Bk = v30;
    gBloom_intensity_Bk = (v27->intensity->klass->vtable._14_get_value.methodPtr)(&v27->intensity->klass, v27->intensity->klass->vtable._14_get_value.method);
    v31 = (v27->scatter->klass->vtable._14_get_value.methodPtr)(&v27->scatter->klass, v27->scatter->klass->vtable._14_get_value.method);
    *(u64 *)&gBloom_threshold_Max = 0x40C0000000000000LL;
    v33 = *(u64 *)&gBloom_threshold_Bk;
    gBloom_scatter_Max = 0.8;
    gBloom_scatter_Bk = v31;
    gBloom_scatter_Now = v31;
    *(u64 *)&gBloom_threshold_Now = v33;
  }
LABEL_46:
  gCamPost_Step = Step;
  gCamPost_Cnt = 0;
}

// 0x1fa1ad0
static void CalcCamPost_TgtPos(SBTLUNIT_WORK *wkPlayer, SBTLUNIT_WORK *wkEnemy, f32 *_TgtX, f32 *_TgtY, f32 *_TgtZ) {
  f32 y;

  if ((u32)(wkEnemy->para->devilid - 413) <= 3)
  {
    y = wkPlayer->pos.y;
    if ((f32)(*TgtY - y) < -200.0)
      *TgtY = y + -200.0;
  }
}

// 0x1f9f290
static void CalcCamPost_Update(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  SBTLCAMERA_WORK *camera;
  void *Instance;
  f32 v13;
  f32 v14;
  f32 v17;
  f32 v18;
  void *v20;
  intptr_t v22;
  void *v24;
  UnityEngine_Object_c *v25;
  f32 v26;
  void *v27;
  void *v28;
  f32 v29;
  void *v30;
  s32 v33;
  bool v34;
  f32 v36;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 *v43;
  f32 v44;
  f32 v45;
  f32 v46;
  u16 major;
  s32 minor;
  V_POSITION_WORK *nml;
  f32 x;
  f32 v54;
  f32 v55;
  u32 v56;
  f32 v57;
  f32 *v58;
  f32 v59;
  f32 z;
  f32 v61;
  f32 y;
  f32 v63;
  f32 v64;
  f32 PosToDir;
  f32 v66;
  f32 v68;
  u64 v70;
  f32 v71;
  f32 v72;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 *v79;
  f32 v80;
  f32 v81;
  f32 v82;
  u16 v85;
  s32 v86;
  V_POSITION_WORK *v87;
  f32 v89;
  f32 v90;
  f32 v91;
  u32 v92;
  f32 v93;
  f32 *v94;
  f32 v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v104;
  f32 v106;
  f32 v107;
  s32 v110;
  f32 v111;
  f32 v112;
  f32 v113;
  f32 v114;
  f32 v117;
  f32 v118;
  f32 v121;
  f32 v122;
  f32 v123;
  f32 v126;
  f32 v127;
  f32 v129;
  f32 v130;
  f32 v131;
  f32 v133;
  f32 v134;
  f32 v135;
  f32 v137;
  f32 v138;
  f32 v140;
  f32 v141;
  f32 v143;
  f32 v144;
  intptr_t v145;
  s64 v146;
  void *v147;
  void *v148;
  s64 v149;
  void *v150;
  void *v151;
  s64 v152;
  void *v153;
  s64 v155;
  f32 v156;
  void *v157;
  intptr_t v158;
  s64 v159;
  void *v160;
  s64 v161;
  void *v162;
  s64 v164;
  f32 v165;
  void *v166;
  intptr_t v167;
  void *monitor;
  f32 gBloom_scatter_Now_local;
  s32 v173;
  s32 v174;
  f32 v176;
  f32 v177;
  f32 v178;
  f32 v185;
  f32 v188;
  f32 v191;
  intptr_t m_CachedPtr;
  s64 v193;
  void *v194;
  void *v195;
  s64 v196;
  void *v197;
  void *v198;
  s64 v199;
  void *v200;
  s64 v202;
  f32 v203;
  void *v204;
  intptr_t v205;
  s64 v206;
  void *v207;
  s64 v208;
  void *v209;
  s64 v211;
  f32 v212;
  void *v213;
  intptr_t v214;
  s64 v216;
  f32 v217;
  void *v218;
  void *v219;
  f32 v221;
  f32 v223;
  u64 v225;
  intptr_t v227;
  void *v228;
  UnityEngine_Object_c *klass;
  void *v231;
  void *v232;
  s32 v235;
  f32 v238;
  f32 v239;
  f32 v240;
  f32 v242;
  f32 v243;
  f32 v245;
  f32 v246;
  f32 v248;
  f32 v249;
  intptr_t v250;
  s64 v251;
  void *v252;
  void *v253;
  s64 v254;
  void *v255;
  void *v256;
  s64 v257;
  void *v258;
  s64 v260;
  f32 v261;
  void *v262;
  intptr_t v263;
  s64 v264;
  void *v265;
  s64 v266;
  void *v267;
  s64 v269;
  f32 v270;
  void *v271;
  intptr_t v272;
  s64 v274;
  f32 v275;
  void *v276;
  f32 v277;
  f32 v278;
  f32 v280;
  f32 v281;
  f32 v283;
  f32 v284;
  f32 v286;
  f32 v287;
  intptr_t v288;
  s64 v289;
  void *v290;
  void *v291;
  s64 v292;
  void *v293;
  void *v294;
  s64 v295;
  void *v296;
  s64 v298;
  f32 v299;
  void *v300;
  intptr_t v301;
  s64 v302;
  void *v303;
  s64 v304;
  void *v305;
  s64 v307;
  f32 v308;
  void *v309;
  intptr_t v310;
  s64 v312;
  f32 v313;
  void *v314;
  void *v315;
  f32 v317;
  s32 v318;
  f32 v320;
  u64 v321;
  f32 v322;
  intptr_t v323;
  void *v324;
  UnityEngine_Object_c *v325;
  f32 v326;
  void *v327;
  void *v328;
  f32 v329;
  void *v330;
  s32 v333;
  s32 v334;
  u32 v335;
  u32 v336;
  f32 value;
  f32 valuea;
  s64 ToZ;
  s64 ToX;
  sdfVector2_t v341;
  sdfVector2_t v342;
  sdfVector2_t v343;
  sdfVector2_t v344;
  sdfColor_t v345;
  sdfColor_t v346;
  sdfColor_t v347;
  sdfColor_t v348;

  ToX = 0;
  ToZ = 0;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  v6 = sBtlSearchUnit_ID(wk->UnitMng, wk->huuma_targetID);
  camera = wk->scene->camera;
  Instance = get_Instance(0);
  if (gCamPost_Step > 30)
    goto LABEL_10;
  if (gCamPost_Step <= 1)
  {
    if (gCamPost_Step)
    {
      if (gCamPost_Step != 1)
        return;
      if (v5 && v6)
      {
        major = v6->major;
        minor = v6->minor;
        nml = sBtlGetVisualData(major, minor)->nml;
        x = v6->pos.x;
        v54 = v5->pos.x;
        v55 = nml->height * 0.5;
        v56 = v6->para->devilid - 413;
        if (v55 < 90.0)
          v55 = 90.0;
        if (v56 >= 4)
          v57 = v55;
        else
          v57 = 120.0;
        v56 = v6->para->devilid - 413;
        v58[53] = x + (f32)((f32)(v54 - x) * 0.5);
        v59 = v6->pos.y - v57;
        v58[54] = v59;
        z = v6->pos.z;
        v61 = v5->pos.z;
        v58[55] = z + (f32)((f32)(v61 - z) * 0.5);
        if (v56 <= 3)
        {
          y = v5->pos.y;
          if ((f32)(v59 - y) < -200.0)
          {
            v58[54] = y + -200.0;
            v61 = v5->pos.z;
            z = v6->pos.z;
          }
        }
        v63 = v5->pos.x;
        v64 = v6->pos.x;
        PosToDir = sBtlGetPosToDir(v63, v61, v64, z);
        v66 = sBtlGet360(PosToDir + -115.0);
        sBtlGetMoveXZ(v5->pos.x, v5->pos.z, v66, 230.0, (f32 *)&ToZ + 1, &ToZ);
        sBtlGetLenXZ(camera->camerapos.x, camera->camerapos.z, *((f32 *)&ToZ + 1), *(f32 *)&ToZ);
        gCamPost_CamGoalX = *((f32 *)&ToZ + 1);
        v68 = *(f32 *)&ToZ;
        gCamPost_CamGoalY = v5->pos.y + -80.0;
        gCamPost_CamGoalZ = v68;
      }
      v70 = 0x40C0000042340000LL;
    }
    else
    {
      if (v5 && v6)
      {
        v85 = v6->major;
        v86 = v6->minor;
        v87 = sBtlGetVisualData(v85, v86)->nml;
        v89 = v6->pos.x;
        v90 = v5->pos.x;
        v91 = v87->height * 0.5;
        v92 = v6->para->devilid - 413;
        if (v91 < 90.0)
          v91 = 90.0;
        if (v92 >= 4)
          v93 = v91;
        else
          v93 = 120.0;
        v92 = v6->para->devilid - 413;
        v94[53] = v89 + (f32)((f32)(v90 - v89) * 0.5);
        v95 = v6->pos.y - v93;
        v94[54] = v95;
        v96 = v6->pos.z;
        v97 = v5->pos.z;
        v94[55] = v96 + (f32)((f32)(v97 - v96) * 0.5);
        if (v92 <= 3)
        {
          v98 = v5->pos.y;
          if ((f32)(v95 - v98) < -200.0)
          {
            v94[54] = v98 + -200.0;
            v97 = v5->pos.z;
            v96 = v6->pos.z;
          }
        }
        v99 = v5->pos.x;
        v100 = v6->pos.x;
        v101 = sBtlGetPosToDir(v99, v97, v100, v96);
        v102 = sBtlGet360(v101 + 115.0);
        sBtlGetMoveXZ(v5->pos.x, v5->pos.z, v102, 230.0, (f32 *)&ToX + 1, &ToX);
        sBtlGetLenXZ(camera->camerapos.x, camera->camerapos.z, *((f32 *)&ToX + 1), *(f32 *)&ToX);
        gCamPost_CamGoalX = *((f32 *)&ToX + 1);
        v104 = *(f32 *)&ToX;
        gCamPost_CamGoalY = v5->pos.y + -80.0;
        gCamPost_CamGoalZ = v104;
      }
      v70 = 0xC0C0000042340000LL;
    }
    *(_OWORD *)&gCamPost_TgtNowX = *(_OWORD *)&gCamPost_TgtGoalX;
    *(u64 *)&gCam_Fovy_Now = v70;
    *(u64 *)&gCamPost_CamNowY = *(u64 *)&gCamPost_CamGoalY;
    return;
  }
  if (gCamPost_Step != 10)
  {
    if (gCamPost_Step != 20)
    {
      if (gCamPost_Step != 30)
        return;
      if (gCam_Fovy_Now < 45.0)
      {
        v36 = gCam_Fovy_Now + 0.125;
        gCam_Fovy_Now = v36;
        if (v36 > 45.0)
        {
          gCam_Fovy_Now = 45.0;
        }
      }
      if (gCam_UpV_Now < 12.0)
      {
        v39 = gCam_UpV_Now + 0.3857143;
        gCam_UpV_Now = v39;
        if (v39 > 12.0)
        {
          gCam_UpV_Now = 12.0;
        }
      }
      v40 = camera->camerapos.x;
      v41 = camera->camerapos.y;
      v42 = camera->camerapos.z;
      v44 = v43[56];
      v45 = v43[57];
      v46 = v43[58];
      if (sBtlGetLenXYZ(v40, v41, v42, v44, v45, v46) >= 12.0)
      {
        v176 = camera->camerapos.x;
        v177 = camera->camerapos.y;
        v178 = camera->camerapos.z;
        GetMovePosToPos(v176, v177, v178, gCamPost_CamGoalX, gCamPost_CamGoalY, gCamPost_CamGoalZ, 12.0, &gCamPost_CamNowX, &gCamPost_CamNowY, &gCamPost_CamNowZ);
      }
      else
      {
        *(u64 *)&gCamPost_CamNowX = *(u64 *)&gCamPost_CamGoalX;
        gCamPost_CamNowZ = gCamPost_CamGoalZ;
      }
      *(u64 *)&gCamPost_TgtNowX = *(u64 *)&gCamPost_TgtGoalX;
      gCamPost_TgtNowZ = gCamPost_TgtGoalZ;
      if (gVignetteOw_intensity_Now > 0.0)
      {
        v185 = gVignetteOw_intensity_Now + -0.01;
        gVignetteOw_intensity_Now = v185;
        if (v185 < 0.0)
        {
          gVignetteOw_intensity_Now = 0.0;
        }
      }
      if (gFilmGrainOw_intensity_Now > 0.0)
      {
        v188 = gFilmGrainOw_intensity_Now + -0.016666668;
        gFilmGrainOw_intensity_Now = v188;
        if (v188 < 0.0)
        {
          gFilmGrainOw_intensity_Now = 0.0;
        }
      }
      if (gChromaticAberrationOw_intensity_Now > 0.0)
      {
        v191 = gChromaticAberrationOw_intensity_Now + -0.011666667;
        gChromaticAberrationOw_intensity_Now = v191;
        if (v191 < 0.0)
        {
          gChromaticAberrationOw_intensity_Now = 0.0;
        }
      }
      if (op_Inequality(Instance, 0, 0))
      {
        m_CachedPtr = Instance[3].m_CachedPtr;
        if (op_Inequality(m_CachedPtr, 0, 0))
        {
          v193 = *(u64 *)(m_CachedPtr + 56);
          v194 = Allocate(UnityEngine_Rendering_ColorParameter);
          v346.g = 1.0;
          v346.r = 0.63;
          v346.b = 0.64;
          v346.a = 1.0;
          v195 = v194;
          _ctor(v194, v346, 0, 0);
          (*(*(u64 *)v193 + 440))(v193, v195, *(u64 *)(*(u64 *)v193 + 448));
          v196 = *(u64 *)(m_CachedPtr + 64);
          v197 = Allocate(UnityEngine_Rendering_Vector2Parameter);
          v342.x = 0.5;
          v198 = v197;
          v342.y = 0.5;
          _ctor(v197, v342, 1, 0);
          (*(*(u64 *)v196 + 440))(v196, v198, *(u64 *)(*(u64 *)v196 + 448));
          v199 = *(u64 *)(m_CachedPtr + 80);
          v200 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v200, 0.2, 1, 0);
          (*(*(u64 *)v199 + 440))(v199, v200, *(u64 *)(*(u64 *)v199 + 448));
          if (!*(u8 *)(m_CachedPtr + 24))
            *(u8 *)(m_CachedPtr + 24) = 1;
          v202 = *(u64 *)(m_CachedPtr + 72);
          v203 = gVignetteOw_intensity_Now;
          v204 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v204, v203, 1, 0);
          (*(*(u64 *)v202 + 440))(v202, v204, *(u64 *)(*(u64 *)v202 + 448));
        }
      }
      if (op_Inequality(Instance, 0, 0))
      {
        v205 = Instance[4].m_CachedPtr;
        if (op_Inequality(v205, 0, 0))
        {
          v206 = *(u64 *)(v205 + 56);
          v207 = Allocate(UnityEngine_Rendering_Universal_FilmGrainLookupParameter);
          _ctor(v207, 9, 1, 0);
          (*(*(u64 *)v206 + 440))(v206, v207, *(u64 *)(*(u64 *)v206 + 448));
          v208 = *(u64 *)(v205 + 72);
          v209 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v209, 0.8, 1, 0);
          (*(*(u64 *)v208 + 440))(v208, v209, *(u64 *)(*(u64 *)v208 + 448));
          if (!*(u8 *)(v205 + 24))
            *(u8 *)(v205 + 24) = 1;
          v211 = *(u64 *)(v205 + 64);
          v212 = gFilmGrainOw_intensity_Now;
          v213 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v213, v212, 1, 0);
          (*(*(u64 *)v211 + 440))(v211, v213, *(u64 *)(*(u64 *)v211 + 448));
        }
      }
      if (op_Inequality(Instance, 0, 0))
      {
        v214 = Instance[5].m_CachedPtr;
        if (op_Inequality(v214, 0, 0))
        {
          if (!*(u8 *)(v214 + 24))
            *(u8 *)(v214 + 24) = 1;
          v216 = *(u64 *)(v214 + 56);
          v217 = gChromaticAberrationOw_intensity_Now;
          v218 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v218, v217, 1, 0);
          (*(*(u64 *)v216 + 440))(v216, v218, *(u64 *)(*(u64 *)v216 + 448));
        }
      }
      if (!op_Inequality(Instance, 0, 0))
        goto LABEL_346;
      v219 = Instance[1].m_CachedPtr;
      if (!op_Inequality(v219, 0, 0))
        goto LABEL_346;
      v221 = 0.0;
      if (gCamPost_Cnt > 9)
      {
LABEL_340:
        v223 = 1.0;
        if (v221 <= 1.0)
          v223 = v221;
        if (v221 < 0.0)
          v223 = 0.0;
        v225 = vadd_f32(*(float32x2_t *)&gBloom_threshold_Bk, vmul_n_f32(vsub_f32(*(float32x2_t *)&gBloom_threshold_Max, *(float32x2_t *)&gBloom_threshold_Bk), v223)).n64_u64[0];
        value = *(f32 *)&v225;
        *(u64 *)&gBloom_threshold_Now = v225;
        gBloom_scatter_Now = gBloom_scatter_Bk
                                 + (f32)(v223 * (f32)(gBloom_scatter_Max - gBloom_scatter_Bk));
        v227 = v219[2].m_CachedPtr;
        v228 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v228, value, 1, 0);
        (*(*(u64 *)v227 + 440))(v227, v228, *(u64 *)(*(u64 *)v227 + 448));
        klass = v219[3].klass;
        v231 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v231, gBloom_intensity_Now, 1, 0);
        (*(klass->_1.image + 55))(klass, v231, *((u64 *)klass->_1.image + 56));
        monitor = v219[3].monitor;
        gBloom_scatter_Now_local = gBloom_scatter_Now;
        goto LABEL_345;
      }
      v221 = (f32)((f32)gCamPost_Cnt / -20.0) + 0.5;
      goto LABEL_340;
    }
    *(_OWORD *)&gCamPost_TgtNowX = *(_OWORD *)&gCamPost_TgtGoalX;
    *(u64 *)&gCamPost_CamNowY = *(u64 *)&gCamPost_CamGoalY;
    if (gCamPost_R0L1)
      v121 = 15.0;
    else
      v121 = -15.0;
    v122 = gCam_Fovy_Now;
    if (v122 > 35.0)
    {
      v122 = gCam_Fovy_Now;
      v123 = v122 + -0.083333336;
      gCam_Fovy_Now = v123;
      if (v123 < 35.0)
      {
        gCam_Fovy_Now = 35.0;
      }
    }
    if (gCamPost_R0L1)
    {
      v126 = gCam_UpV_Now;
      if (v126 >= v121)
        goto LABEL_432;
      v126 = gCam_UpV_Now;
      v127 = v126 + 0.075;
      gCam_UpV_Now = v127;
      if (v127 <= v121)
        goto LABEL_432;
    }
    else
    {
      v277 = gCam_UpV_Now;
      if (v277 <= v121)
        goto LABEL_432;
      v277 = gCam_UpV_Now;
      v278 = v277 + -0.075;
      gCam_UpV_Now = v278;
      if (v278 >= v121)
      {
LABEL_432:
        v280 = gVignetteOw_intensity_Now;
        if (v280 < 0.6)
        {
          v280 = gVignetteOw_intensity_Now;
          v281 = v280 + 0.0050000004;
          gVignetteOw_intensity_Now = v281;
          if (v281 > 0.6)
          {
            gVignetteOw_intensity_Now = 0.6;
          }
        }
        v283 = gFilmGrainOw_intensity_Now;
        if (v283 < 1.0)
        {
          v283 = gFilmGrainOw_intensity_Now;
          v284 = v283 + 0.008333334;
          gFilmGrainOw_intensity_Now = v284;
          if (v284 > 1.0)
          {
            gFilmGrainOw_intensity_Now = 1.0;
          }
        }
        v286 = gChromaticAberrationOw_intensity_Now;
        if (v286 < 0.6)
        {
          v286 = gChromaticAberrationOw_intensity_Now;
          v287 = v286 + 0.0058333334;
          gChromaticAberrationOw_intensity_Now = v287;
          if (v287 > 0.6)
          {
            gChromaticAberrationOw_intensity_Now = 0.6;
          }
        }
        if (op_Inequality(Instance, 0, 0))
        {
          v288 = Instance[3].m_CachedPtr;
          if (op_Inequality(v288, 0, 0))
          {
            v289 = *(u64 *)(v288 + 56);
            v290 = Allocate(UnityEngine_Rendering_ColorParameter);
            v348.g = 1.0;
            v348.r = 0.63;
            v348.b = 0.64;
            v348.a = 1.0;
            v291 = v290;
            _ctor(v290, v348, 0, 0);
            (*(*(u64 *)v289 + 440))(v289, v291, *(u64 *)(*(u64 *)v289 + 448));
            v292 = *(u64 *)(v288 + 64);
            v293 = Allocate(UnityEngine_Rendering_Vector2Parameter);
            v344.x = 0.5;
            v294 = v293;
            v344.y = 0.5;
            _ctor(v293, v344, 1, 0);
            (*(*(u64 *)v292 + 440))(v292, v294, *(u64 *)(*(u64 *)v292 + 448));
            v295 = *(u64 *)(v288 + 80);
            v296 = Allocate(UnityEngine_Rendering_FloatParameter);
            _ctor(v296, 0.2, 1, 0);
            (*(*(u64 *)v295 + 440))(v295, v296, *(u64 *)(*(u64 *)v295 + 448));
            if (!*(u8 *)(v288 + 24))
              *(u8 *)(v288 + 24) = 1;
            v298 = *(u64 *)(v288 + 72);
            v299 = gVignetteOw_intensity_Now;
            v300 = Allocate(UnityEngine_Rendering_FloatParameter);
            _ctor(v300, v299, 1, 0);
            (*(*(u64 *)v298 + 440))(v298, v300, *(u64 *)(*(u64 *)v298 + 448));
          }
        }
        if (op_Inequality(Instance, 0, 0))
        {
          v301 = Instance[4].m_CachedPtr;
          if (op_Inequality(v301, 0, 0))
          {
            v302 = *(u64 *)(v301 + 56);
            v303 = Allocate(UnityEngine_Rendering_Universal_FilmGrainLookupParameter);
            _ctor(v303, 9, 1, 0);
            (*(*(u64 *)v302 + 440))(v302, v303, *(u64 *)(*(u64 *)v302 + 448));
            v304 = *(u64 *)(v301 + 72);
            v305 = Allocate(UnityEngine_Rendering_FloatParameter);
            _ctor(v305, 0.8, 1, 0);
            (*(*(u64 *)v304 + 440))(v304, v305, *(u64 *)(*(u64 *)v304 + 448));
            if (!*(u8 *)(v301 + 24))
              *(u8 *)(v301 + 24) = 1;
            v307 = *(u64 *)(v301 + 64);
            v308 = gFilmGrainOw_intensity_Now;
            v309 = Allocate(UnityEngine_Rendering_FloatParameter);
            _ctor(v309, v308, 1, 0);
            (*(*(u64 *)v307 + 440))(v307, v309, *(u64 *)(*(u64 *)v307 + 448));
          }
        }
        if (op_Inequality(Instance, 0, 0))
        {
          v310 = Instance[5].m_CachedPtr;
          if (op_Inequality(v310, 0, 0))
          {
            if (!*(u8 *)(v310 + 24))
              *(u8 *)(v310 + 24) = 1;
            v312 = *(u64 *)(v310 + 56);
            v313 = gChromaticAberrationOw_intensity_Now;
            v314 = Allocate(UnityEngine_Rendering_FloatParameter);
            _ctor(v314, v313, 1, 0);
            (*(*(u64 *)v312 + 440))(v312, v314, *(u64 *)(*(u64 *)v312 + 448));
          }
        }
        if (!op_Inequality(Instance, 0, 0))
          goto LABEL_508;
        v315 = Instance[1].m_CachedPtr;
        if (!op_Inequality(v315, 0, 0))
        {
LABEL_508:
          v333 = gCamPost_Cnt + 1;
          v34 = gCamPost_Cnt - 60 < 0;
          gCamPost_Cnt = v333;
          if (v34 == __OFSUB__(v333, 61))
          {
            v334 = gCamPost_R0L1;
            if (v334)
            {
              if (!v335)
              v174 = 40;
            }
            else
            {
              if (!v335)
              v174 = 30;
            }
            goto LABEL_521;
          }
          return;
        }
        v317 = 0.0;
        v318 = gCamPost_Cnt;
        if (v318 < 45)
        {
LABEL_502:
          if (v317 <= 1.0)
            v320 = v317;
          else
            v320 = 1.0;
          if (v317 < 0.0)
            v320 = 0.0;
          v321 = vadd_f32(*(float32x2_t *)&gBloom_threshold_Bk, vmul_n_f32(vsub_f32(*(float32x2_t *)&gBloom_threshold_Max, *(float32x2_t *)&gBloom_threshold_Bk), v320)).n64_u64[0];
          v322 = gBloom_scatter_Max;
          *(u64 *)&gBloom_threshold_Now = v321;
          valuea = *(f32 *)&v321;
          gBloom_scatter_Now = gBloom_scatter_Bk
                                   + (f32)(v320 * (f32)(v322 - gBloom_scatter_Bk));
          v323 = v315[2].m_CachedPtr;
          v324 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v324, valuea, 1, 0);
          (*(*(u64 *)v323 + 440))(v323, v324, *(u64 *)(*(u64 *)v323 + 448));
          v325 = v315[3].klass;
          v326 = gBloom_intensity_Now;
          v327 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v327, v326, 1, 0);
          (*(v325->_1.image + 55))(v325, v327, *((u64 *)v325->_1.image + 56));
          v328 = v315[3].monitor;
          v329 = gBloom_scatter_Now;
          v330 = Allocate(UnityEngine_Rendering_FloatParameter);
          _ctor(v330, v329, 1, 0);
          (*(*(u64 *)v328 + 440))(v328, v330, *(u64 *)(*(u64 *)v328 + 448));
          goto LABEL_508;
LABEL_501:
          goto LABEL_502;
        }
        v318 = gCamPost_Cnt;
        if (v318 <= 49)
        {
          if (!v336)
          {
            v318 = gCamPost_Cnt;
          }
          v317 = (f32)(v318 - 45) / 5.0;
          goto LABEL_502;
        }
        else
        {
          if (!v336)
          {
            v318 = gCamPost_Cnt;
          }
          v317 = (f32)((f32)(v318 - 50) / -20.0) + 1.0;
          goto LABEL_502;
        }
        goto LABEL_501;
      }
    }
    gCam_UpV_Now = v121;
    goto LABEL_432;
  }
  v106 = 0.0;
  v107 = 100.0
       - (f32)((f32)(100.0 / (f32)wk->huumagauge_counter_start) * (f32)wk->huumagauge_counter);
  if (v107 >= 0.0)
    v106 = v107 / 100.0;
  v110 = gCamPost_R0L1;
  *(_OWORD *)&gCamPost_TgtNowX = *(_OWORD *)&gCamPost_TgtGoalX;
  *(u64 *)&gCamPost_CamNowY = *(u64 *)&gCamPost_CamGoalY;
  v111 = (f32)(v106 * -10.0) + 45.0;
  if (v110)
    v112 = (f32)(v106 * 9.0) + 6.0;
  else
    v112 = -6.0 - (f32)(v106 * 9.0);
  v113 = gCam_Fovy_Now;
  if (v113 > v111)
  {
    v113 = gCam_Fovy_Now;
    v114 = v113 + -0.083333336;
    gCam_Fovy_Now = v114;
    if (v114 < v111)
    {
      gCam_Fovy_Now = v111;
    }
  }
  if (gCamPost_R0L1)
  {
    v117 = gCam_UpV_Now;
    if (v117 >= v112)
      goto LABEL_363;
    v117 = gCam_UpV_Now;
    v118 = v117 + 0.075;
    gCam_UpV_Now = v118;
    if (v118 <= v112)
      goto LABEL_363;
  }
  else
  {
    v238 = gCam_UpV_Now;
    if (v238 <= v112)
      goto LABEL_363;
    v238 = gCam_UpV_Now;
    v239 = v238 + -0.075;
    gCam_UpV_Now = v239;
    if (v239 >= v112)
      goto LABEL_363;
  }
  gCam_UpV_Now = v112;
LABEL_363:
  v240 = (f32)(v106 * 0.6) + 0.0;
  v242 = gVignetteOw_intensity_Now;
  if (v242 < v240)
  {
    v242 = gVignetteOw_intensity_Now;
    v243 = v242 + 0.0050000004;
    gVignetteOw_intensity_Now = v243;
    if (v243 > v240)
    {
      gVignetteOw_intensity_Now = v240;
    }
  }
  v245 = gFilmGrainOw_intensity_Now;
  if (v245 < v106)
  {
    v245 = gFilmGrainOw_intensity_Now;
    v246 = v245 + 0.008333334;
    gFilmGrainOw_intensity_Now = v246;
    if (v246 > v106)
    {
      gFilmGrainOw_intensity_Now = v106;
    }
  }
  v248 = gChromaticAberrationOw_intensity_Now;
  if (v248 < v240)
  {
    v248 = gChromaticAberrationOw_intensity_Now;
    v249 = v248 + 0.0058333334;
    gChromaticAberrationOw_intensity_Now = v249;
    if (v249 > v240)
    {
      gChromaticAberrationOw_intensity_Now = v240;
    }
  }
  if (op_Inequality(Instance, 0, 0))
  {
    v250 = Instance[3].m_CachedPtr;
    if (op_Inequality(v250, 0, 0))
    {
      v251 = *(u64 *)(v250 + 56);
      v252 = Allocate(UnityEngine_Rendering_ColorParameter);
      v347.g = 1.0;
      v347.r = 0.63;
      v347.b = 0.64;
      v347.a = 1.0;
      v253 = v252;
      _ctor(v252, v347, 0, 0);
      (*(*(u64 *)v251 + 440))(v251, v253, *(u64 *)(*(u64 *)v251 + 448));
      v254 = *(u64 *)(v250 + 64);
      v255 = Allocate(UnityEngine_Rendering_Vector2Parameter);
      v343.x = 0.5;
      v256 = v255;
      v343.y = 0.5;
      _ctor(v255, v343, 1, 0);
      (*(*(u64 *)v254 + 440))(v254, v256, *(u64 *)(*(u64 *)v254 + 448));
      v257 = *(u64 *)(v250 + 80);
      v258 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v258, 0.2, 1, 0);
      (*(*(u64 *)v257 + 440))(v257, v258, *(u64 *)(*(u64 *)v257 + 448));
      if (!*(u8 *)(v250 + 24))
        *(u8 *)(v250 + 24) = 1;
      v260 = *(u64 *)(v250 + 72);
      v261 = gVignetteOw_intensity_Now;
      v262 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v262, v261, 1, 0);
      (*(*(u64 *)v260 + 440))(v260, v262, *(u64 *)(*(u64 *)v260 + 448));
    }
  }
  if (op_Inequality(Instance, 0, 0))
  {
    v263 = Instance[4].m_CachedPtr;
    if (op_Inequality(v263, 0, 0))
    {
      v264 = *(u64 *)(v263 + 56);
      v265 = Allocate(UnityEngine_Rendering_Universal_FilmGrainLookupParameter);
      _ctor(v265, 9, 1, 0);
      (*(*(u64 *)v264 + 440))(v264, v265, *(u64 *)(*(u64 *)v264 + 448));
      v266 = *(u64 *)(v263 + 72);
      v267 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v267, 0.8, 1, 0);
      (*(*(u64 *)v266 + 440))(v266, v267, *(u64 *)(*(u64 *)v266 + 448));
      if (!*(u8 *)(v263 + 24))
        *(u8 *)(v263 + 24) = 1;
      v269 = *(u64 *)(v263 + 64);
      v270 = gFilmGrainOw_intensity_Now;
      v271 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v271, v270, 1, 0);
      (*(*(u64 *)v269 + 440))(v269, v271, *(u64 *)(*(u64 *)v269 + 448));
    }
  }
  if (op_Inequality(Instance, 0, 0))
  {
    v272 = Instance[5].m_CachedPtr;
    if (op_Inequality(v272, 0, 0))
    {
      if (!*(u8 *)(v272 + 24))
        *(u8 *)(v272 + 24) = 1;
      v274 = *(u64 *)(v272 + 56);
      v275 = gChromaticAberrationOw_intensity_Now;
      v276 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v276, v275, 1, 0);
      (*(*(u64 *)v274 + 440))(v274, v276, *(u64 *)(*(u64 *)v274 + 448));
    }
  }
  return;
LABEL_10:
  if ((u32)gCamPost_Step > 0x3C)
    return;
  if (gCamPost_Step == 40)
  {
    v71 = gCam_Fovy_Now;
    if (v71 < 45.0)
    {
      v71 = gCam_Fovy_Now;
      v72 = v71 + 0.125;
      gCam_Fovy_Now = v72;
      if (v72 > 45.0)
      {
        gCam_Fovy_Now = 45.0;
      }
    }
    v74 = gCam_UpV_Now;
    if (v74 > 6.0)
    {
      v74 = gCam_UpV_Now;
      v75 = v74 + -0.1125;
      gCam_UpV_Now = v75;
      if (v75 < 6.0)
      {
        gCam_UpV_Now = 6.0;
      }
    }
    v76 = camera->camerapos.x;
    v77 = camera->camerapos.y;
    v78 = camera->camerapos.z;
    v80 = v79[56];
    v81 = v79[57];
    v82 = v79[58];
    if (sBtlGetLenXYZ(v76, v77, v78, v80, v81, v82) >= 2.0)
    {
      v129 = camera->camerapos.x;
      v130 = camera->camerapos.y;
      v131 = camera->camerapos.z;
      v133 = gCamPost_CamGoalZ;
      v134 = gCamPost_CamGoalX;
      v135 = gCamPost_CamGoalY;
      GetMovePosToPos(v129, v130, v131, v134, v135, v133, 2.0, &gCamPost_CamNowX, &gCamPost_CamNowY, &gCamPost_CamNowZ);
    }
    else
    {
      *(u64 *)&gCamPost_CamNowX = *(u64 *)&gCamPost_CamGoalX;
      gCamPost_CamNowZ = gCamPost_CamGoalZ;
    }
    *(u64 *)&gCamPost_TgtNowX = *(u64 *)&gCamPost_TgtGoalX;
    gCamPost_TgtNowZ = gCamPost_TgtGoalZ;
    v137 = gVignetteOw_intensity_Now;
    if (v137 > 0.0)
    {
      v137 = gVignetteOw_intensity_Now;
      v138 = v137 + -0.01;
      gVignetteOw_intensity_Now = v138;
      if (v138 < 0.0)
      {
        gVignetteOw_intensity_Now = 0.0;
      }
    }
    v140 = gFilmGrainOw_intensity_Now;
    if (v140 > 0.0)
    {
      v140 = gFilmGrainOw_intensity_Now;
      v141 = v140 + -0.016666668;
      gFilmGrainOw_intensity_Now = v141;
      if (v141 < 0.0)
      {
        gFilmGrainOw_intensity_Now = 0.0;
      }
    }
    v143 = gChromaticAberrationOw_intensity_Now;
    if (v143 > 0.0)
    {
      v143 = gChromaticAberrationOw_intensity_Now;
      v144 = v143 + -0.011666667;
      gChromaticAberrationOw_intensity_Now = v144;
      if (v144 < 0.0)
      {
        gChromaticAberrationOw_intensity_Now = 0.0;
      }
    }
    if (op_Inequality(Instance, 0, 0))
    {
      v145 = Instance[3].m_CachedPtr;
      if (op_Inequality(v145, 0, 0))
      {
        v146 = *(u64 *)(v145 + 56);
        v147 = Allocate(UnityEngine_Rendering_ColorParameter);
        v345.g = 1.0;
        v345.r = 0.63;
        v345.b = 0.64;
        v345.a = 1.0;
        v148 = v147;
        _ctor(v147, v345, 0, 0);
        (*(*(u64 *)v146 + 440))(v146, v148, *(u64 *)(*(u64 *)v146 + 448));
        v149 = *(u64 *)(v145 + 64);
        v150 = Allocate(UnityEngine_Rendering_Vector2Parameter);
        v341.x = 0.5;
        v151 = v150;
        v341.y = 0.5;
        _ctor(v150, v341, 1, 0);
        (*(*(u64 *)v149 + 440))(v149, v151, *(u64 *)(*(u64 *)v149 + 448));
        v152 = *(u64 *)(v145 + 80);
        v153 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v153, 0.2, 1, 0);
        (*(*(u64 *)v152 + 440))(v152, v153, *(u64 *)(*(u64 *)v152 + 448));
        if (!*(u8 *)(v145 + 24))
          *(u8 *)(v145 + 24) = 1;
        v155 = *(u64 *)(v145 + 72);
        v156 = gVignetteOw_intensity_Now;
        v157 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v157, v156, 1, 0);
        (*(*(u64 *)v155 + 440))(v155, v157, *(u64 *)(*(u64 *)v155 + 448));
      }
    }
    if (op_Inequality(Instance, 0, 0))
    {
      v158 = Instance[4].m_CachedPtr;
      if (op_Inequality(v158, 0, 0))
      {
        v159 = *(u64 *)(v158 + 56);
        v160 = Allocate(UnityEngine_Rendering_Universal_FilmGrainLookupParameter);
        _ctor(v160, 9, 1, 0);
        (*(*(u64 *)v159 + 440))(v159, v160, *(u64 *)(*(u64 *)v159 + 448));
        v161 = *(u64 *)(v158 + 72);
        v162 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v162, 0.8, 1, 0);
        (*(*(u64 *)v161 + 440))(v161, v162, *(u64 *)(*(u64 *)v161 + 448));
        if (!*(u8 *)(v158 + 24))
          *(u8 *)(v158 + 24) = 1;
        v164 = *(u64 *)(v158 + 64);
        v165 = gFilmGrainOw_intensity_Now;
        v166 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v166, v165, 1, 0);
        (*(*(u64 *)v164 + 440))(v164, v166, *(u64 *)(*(u64 *)v164 + 448));
      }
    }
    if (op_Inequality(Instance, 0, 0))
    {
      v167 = Instance[5].m_CachedPtr;
      if (op_Inequality(v167, 0, 0))
      {
        if (!*(u8 *)(v167 + 24))
          *(u8 *)(v167 + 24) = 1;
        monitor = *(void **)(v167 + 56);
        gBloom_scatter_Now_local = gChromaticAberrationOw_intensity_Now;
LABEL_345:
        v232 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v232, gBloom_scatter_Now_local, 1, 0);
        (*(*(u64 *)monitor + 440))(monitor, v232, *(u64 *)(*(u64 *)monitor + 448));
      }
    }
LABEL_346:
    v235 = gCamPost_Cnt + 1;
    v34 = gCamPost_Cnt - 80 < 0;
    gCamPost_Cnt = v235;
    if (v34 != __OFSUB__(v235, 81))
      return;
    v174 = 50;
    goto LABEL_521;
  }
  if (gCamPost_Step == 60)
  {
    v13 = gBloom_intensity_Now;
    if (v13 > gBloom_intensity_Bk)
    {
      v13 = gBloom_intensity_Now;
      v14 = v13 - (f32)((f32)(4.0 - gBloom_intensity_Bk) / 110.0);
      gBloom_intensity_Now = v14;
      if (v14 < gBloom_intensity_Bk)
      {
        gBloom_intensity_Now = gBloom_intensity_Bk;
      }
    }
    v17 = gBloom_scatter_Now;
    if (v17 > gBloom_scatter_Bk)
    {
      v17 = gBloom_scatter_Now;
      v18 = v17 - (f32)((f32)(0.8 - gBloom_scatter_Bk) / 110.0);
      gBloom_scatter_Now = v18;
      if (v18 < gBloom_scatter_Bk)
      {
        gBloom_scatter_Now = gBloom_scatter_Bk;
      }
    }
    if (op_Inequality(Instance, 0, 0))
    {
      v20 = Instance[1].m_CachedPtr;
      if (op_Inequality(v20, 0, 0))
      {
        v22 = v20[2].m_CachedPtr;
        v24 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v24, gBloom_threshold_Now, 1, 0);
        (*(*(u64 *)v22 + 440))(v22, v24, *(u64 *)(*(u64 *)v22 + 448));
        v25 = v20[3].klass;
        v26 = gBloom_intensity_Now;
        v27 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v27, v26, 1, 0);
        (*(v25->_1.image + 55))(v25, v27, *((u64 *)v25->_1.image + 56));
        v28 = v20[3].monitor;
        v29 = gBloom_scatter_Now;
        v30 = Allocate(UnityEngine_Rendering_FloatParameter);
        _ctor(v30, v29, 1, 0);
        (*(*(u64 *)v28 + 440))(v28, v30, *(u64 *)(*(u64 *)v28 + 448));
      }
    }
    v33 = gCamPost_Cnt + 1;
    v34 = gCamPost_Cnt - 115 < 0;
    gCamPost_Cnt = v33;
    if (v34 == __OFSUB__(v33, 116))
      goto LABEL_263;
    goto LABEL_9003;
    if (v34 == __OFSUB__(v173, 116))
    {
LABEL_263:
      v174 = 61;
LABEL_521:
      CalcCamPost_StepSet(v174);
    }
LABEL_9003:
  }
}

// 0x1fa1b10
void sBtlGetHuuma_CameraParam(f32 *_TgtX, f32 *_TgtY, f32 *_TgtZ, f32 *_CamX, f32 *_CamY, f32 *_CamZ, f32 *_Fovy, f32 *_UpV) {
  f32 *static_fields;

  *TgtX = static_fields[59];
  *TgtY = static_fields[60];
  *TgtZ = static_fields[61];
  *CamX = static_fields[62];
  *CamY = static_fields[63];
  *CamZ = static_fields[64];
  *Fovy = static_fields[65];
  *UpV = static_fields[66];
}

// 0x1f9ef20
static void ResetPost(void) {
  void *Instance;
  void *mDof;

  Instance = get_Instance(0);
  if (op_Inequality(Instance, 0, 0))
  {
    RestoreVignetteSetting(Instance, 0);
    RestoreFilmGrainSetting(Instance, 0);
    RestoreChromaticAberrationSetting(Instance, 0);
    RestoreLensDistortionSetting(Instance, 0);
    RestoreColorAdjustmentsSetting(Instance, 0);
    RestoreWhiteBalanceSetting(Instance, 0);
    RestoreBloomSetting(Instance, 0);
    mDof = Instance->mDof;
    if (!op_Inequality(Instance->mDof, 0, 0))
      goto LABEL_13;
    goto LABEL_9000;
    if (!op_Inequality(mDof, 0, 0))
    {
LABEL_13:
      SetForceActiveDofSetting(Instance, 0, 0);
      goto LABEL_6;
    }
LABEL_9000:
    RestoreDofSetting(Instance, 0);
    goto LABEL_13;
  }
LABEL_6:
  CalcCamPost_StepSet(-1);
}

// 0x1f6f500
static void InitJump(void) {
  P_JUMP_t *gJump_local;

  gJump_local = gJump;
  *(u16 *)&gJump_local->Use = 0;
  gJump_local->InputTime = 0.0;
  *(u64 *)&gJump_local->Step = 0;
  gJump_local->StepBoolA = 0;
}

// 0x1fa1bf0
static s32 NormalProc_Jump(SBTLUNIT_WORK *wk, s32 flg, s32 keyflg) {
  if (keyflg)
    return flg;
  if (!sBtlCheckMove(wk))
    return flg;
  if ((wk->vstatus & 0x80) != 0)
    return flg;
  if (!wk->bJump)
    return flg;
  if (wk->battlemode == 1)
    return flg;
  sBtlJumpStart(wk);
  return 2;
}

// 0x1fa1d80
static bool JumpProc_Jump(SBTLUNIT_WORK *wk) {
  return wk->bJump;
}

// 0x1f98b00
static bool ComboProc_Jump(SBTLUNIT_WORK *wk) {
  return wk->bJump;
}

// 0x1fa1e10
static bool ChkKeyPressJump(void) {
  return wk->bJump2;
}

// 0x1f98b90
void sBtlJumpStart(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v8;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 AnlogKeyToDir;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 ScreenDir;
  f32 v24;
  struct sdfVector4_t v27;
  _OWORD *p_x;
  __int128 v30;
  __int128 v31;
  f32 Item_60922080;
  f32 v33;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 *v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 *v48;
  struct sdfVector4_t pos;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 Radian;
  sdfVector4_t *p_rotbk;
  s32 beforeframe;
  P_JUMP_t *gJump_local;
  f32 v68;
  P_JUMP_t *v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 RotToDir;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 v80;
  SBTLUNIT_WORK *v81;
  SBATTLE_WORK *v84;
  f32 per;
  f32 v86;
  f32 v87;
  struct sdfVector4_t v88;
  f32 v90;
  f32 v94;
  f32 dir;
  sdfVector4_t direction;
  sdfMatrix4_t v97;
  sdfMatrix4_t v98;
  sdfMatrix4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v104;
  sdfVector4_t v105;
  sdfVector4_t v106;
  sdfVector4_t v107;

  *(u64 *)&direction.x = 0;
  *(u64 *)&direction.z = 0;
  dir = 0.0;
  memset(&v97, 0, sizeof(v97));
  sBtlResetCharge(wk, 0);
  ClearPosLink();
  wk->status &= ~0x100u;
  wk->hstatus &= 0xFFF9FFFF;
  v8 = wk;
  v8->bHuumaCancel = 0;
  v8->ComboMotRetryCnt = 0;
  v8->ComboMotRetryUse = 0;
  p_rot = &wk->rot;
  x = wk->rot.x;
  LODWORD(v8) = wk->flg;
  wk->cmstatus = 0;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  wk->flg = (u32)v8 & 0xFFFFF7FF;
  v102.x = x;
  v102.y = y;
  v102.z = z;
  v102.w = w;
  sBtlGetRotToDir(v102);
  AnlogKeyToDir = GetAnlogKeyToDir(wk, &dir);
  v16 = wk->pos.z;
  v17 = wk->pos.x;
  v18 = wk->pos.y;
  mapGetScreenDir(v17, v18, v16, 0.0);
  if (AnlogKeyToDir >= 48.0)
  {
    v19 = wk->pos.x;
    v20 = wk->pos.y;
    v21 = wk->pos.z;
    ScreenDir = mapGetScreenDir(v19, v20, v21, 0.0);
    GetAnlogKey(wk, &direction);
    v24 = ScreenDir * -0.017453292;
    sub_1949280(0, v24);
    v88 = direction;
    vct_A = v88;
    get_transpose(&v99, &mtx_A, 0);
    v98 = v99;
    v101 = op_Multiply_60923920(&v98, vct_A, 0);
    vct_A = v101;
    direction = vct_A;
    v27 = *p_rot;
    vct_A = v27;
    ToMatrix();
    v94 = AnlogKeyToDir;
    p_x = &vf00.x;
    v30 = p_x[5];
    *(_OWORD *)&v97.m00 = p_x[4];
    *(_OWORD *)&v97.m01 = v30;
    v31 = p_x[7];
    *(_OWORD *)&v97.m02 = p_x[6];
    *(_OWORD *)&v97.m03 = v31;
    Item_60922080 = get_Item_60922080(&v97, 2, 0);
    v33 = get_Item_60922080(&v97, 6, 0);
    v35 = get_Item_60922080(&v97, 10, 0);
    v36 = direction.x;
    v37 = direction.y;
    v38 = v35;
    v39 = direction.z;
    v40 = direction.w;
    v42 = &vf00.x;
    v42[4] = v36;
    v42[5] = v37;
    v42[6] = v39;
    v42[7] = v40;
    v43 = -Item_60922080;
    v44 = -v33;
    v45 = -v38;
    vct_B.x = v43;
    vct_B.y = v44;
    vct_B.z = v45;
    vct_B.w = 0.0;
    v48 = &vf00.x;
    v48[4] = v36;
    v48[5] = v37;
    v48[6] = v39;
    v48[7] = v40;
    pos = wk->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v104.x = wk->pos.x;
    v51 = wk->pos.y;
    v52 = wk->pos.z;
    v53 = wk->pos.w;
    v54 = wk->rot.x;
    v55 = wk->rot.y;
    v56 = vct_A.x;
    v57 = wk->rot.z;
    v107.w = wk->rot.w;
    v90 = vct_A.x;
    v86 = wk->rot.w;
    v87 = wk->pos.x;
    v107.w = v86;
    v104.x = v87;
    v56 = v90;
    per = v56;
    v104.y = v51;
    v104.z = v52;
    v104.w = v53;
    v107.x = v54;
    v107.y = v55;
    v107.z = v57;
    *(u64 *)&v100.x = 0;
    Radian = sBtlGetRadian(v104, v107, v100, per);
    sBtlAddUnitDeg(wk, Radian);
    AnlogKeyToDir = v94;
    *p_rot = vct_A;
    p_rotbk = &wk->rotbk;
    *p_rotbk = vct_A;
    goto LABEL_85;
  }
LABEL_85:
  wk->next_motionno = 91;
  sbtlplayertblSetPlayerMotionData_Hokan(wk);
  beforeframe = wk->beforeframe;
  sBtlSetMotion(wk, 91, beforeframe, 0, 0);
  sBtlSetAction(wk, 1, 0);
  gJump_local = gJump;
  *(_OWORD *)&gJump_local->InputTime = xmmword_3D06D40;
  *(u16 *)&gJump_local->Use = 1;
  *(u64 *)&gJump_local->Step = 0;
  gJump_local->StepBoolA = 0;
  *(u64 *)&gJump_local->SpeedRise2 = 0;
  gJump_local->SpeedFall = 0.0;
  if (AnlogKeyToDir >= 48.0)
    v68 = 10.0;
  else
    v68 = 0.0;
  gJump_local->SpeedMove = v68;
  v71 = gJump;
  v71->HighJump = 1;
  *(u64 *)&v71->PeakY = 0;
  v71->SkillStY = 0.0;
  *(u16 *)&v71->ReJumpInput = 0;
  wk->hstatus |= 0x80000u;
  FootEff(wk, 0.0, 0.0, 0.2, 4.0, 0);
  v72 = wk->rot.x;
  v73 = wk->rot.y;
  v74 = wk->rot.z;
  v75 = wk->rot.w;
  v105.x = v72;
  v105.y = v73;
  v105.z = v74;
  v105.w = v75;
  RotToDir = sBtlGetRotToDir(v105);
  Add(1, wk->pos.x, wk->pos.y, wk->pos.z, RotToDir, 0);
  v77 = wk->pos.x;
  v78 = wk->pos.y;
  v79 = wk->pos.z;
  v80 = wk->pos.w;
  v106.x = v77;
  v106.y = v78;
  v106.z = v79;
  v106.w = v80;
  sBtlPlay3DSE(0x10106u, v106);
  JumpVoice(v81);
  v84 = wk;
  v84->kochokuCnt = 999;
  v84->mode = 19;
}

// 0x1fa2110
void sBtlJump3Start(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v8;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 AnlogKeyToDir;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 ScreenDir;
  f32 v24;
  struct sdfVector4_t v27;
  _OWORD *p_x;
  __int128 v30;
  __int128 v31;
  f32 Item_60922080;
  f32 v33;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 *v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 *v48;
  struct sdfVector4_t pos;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 Radian;
  sdfVector4_t *p_rotbk;
  s32 beforeframe;
  P_JUMP_t *gJump_local;
  f32 v68;
  P_JUMP_t *v69;
  f32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 RotToDir;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 v80;
  f32 v81;
  f32 v82;
  SBTLUNIT_WORK *v83;
  SBATTLE_WORK *v86;
  f32 per;
  f32 v88;
  f32 v89;
  struct sdfVector4_t v90;
  f32 v92;
  f32 v96;
  f32 dir;
  sdfVector4_t direction;
  sdfMatrix4_t v99;
  sdfMatrix4_t v100;
  sdfMatrix4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v103;
  sdfVector4_t v104;
  sdfVector4_t v106;
  sdfVector4_t v107;
  sdfVector4_t v108;
  sdfVector4_t v109;

  *(u64 *)&direction.x = 0;
  *(u64 *)&direction.z = 0;
  dir = 0.0;
  memset(&v99, 0, sizeof(v99));
  sBtlResetCharge(wk, 0);
  ClearPosLink();
  wk->status &= ~0x100u;
  wk->hstatus &= 0xFFF9FFFF;
  v8 = wk;
  v8->bHuumaCancel = 0;
  v8->ComboMotRetryCnt = 0;
  v8->ComboMotRetryUse = 0;
  p_rot = &wk->rot;
  x = wk->rot.x;
  wk->cmstatus = 0;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v104.x = x;
  v104.y = y;
  v104.z = z;
  v104.w = w;
  sBtlGetRotToDir(v104);
  AnlogKeyToDir = GetAnlogKeyToDir(wk, &dir);
  v16 = wk->pos.z;
  v17 = wk->pos.x;
  v18 = wk->pos.y;
  mapGetScreenDir(v17, v18, v16, 0.0);
  if (AnlogKeyToDir >= 48.0)
  {
    v19 = wk->pos.x;
    v20 = wk->pos.y;
    v21 = wk->pos.z;
    ScreenDir = mapGetScreenDir(v19, v20, v21, 0.0);
    GetAnlogKey(wk, &direction);
    v24 = ScreenDir * -0.017453292;
    sub_1949280(0, v24);
    v90 = direction;
    vct_A = v90;
    get_transpose(&v101, &mtx_A, 0);
    v100 = v101;
    v103 = op_Multiply_60923920(&v100, vct_A, 0);
    vct_A = v103;
    direction = vct_A;
    v27 = *p_rot;
    vct_A = v27;
    ToMatrix();
    v96 = AnlogKeyToDir;
    p_x = &vf00.x;
    v30 = p_x[5];
    *(_OWORD *)&v99.m00 = p_x[4];
    *(_OWORD *)&v99.m01 = v30;
    v31 = p_x[7];
    *(_OWORD *)&v99.m02 = p_x[6];
    *(_OWORD *)&v99.m03 = v31;
    Item_60922080 = get_Item_60922080(&v99, 2, 0);
    v33 = get_Item_60922080(&v99, 6, 0);
    v35 = get_Item_60922080(&v99, 10, 0);
    v36 = direction.x;
    v37 = direction.y;
    v38 = v35;
    v39 = direction.z;
    v40 = direction.w;
    v42 = &vf00.x;
    v42[4] = v36;
    v42[5] = v37;
    v42[6] = v39;
    v42[7] = v40;
    v43 = -Item_60922080;
    v44 = -v33;
    v45 = -v38;
    vct_B.x = v43;
    vct_B.y = v44;
    vct_B.z = v45;
    vct_B.w = 0.0;
    v48 = &vf00.x;
    v48[4] = v36;
    v48[5] = v37;
    v48[6] = v39;
    v48[7] = v40;
    pos = wk->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v106.x = wk->pos.x;
    v51 = wk->pos.y;
    v52 = wk->pos.z;
    v53 = wk->pos.w;
    v54 = wk->rot.x;
    v55 = wk->rot.y;
    v56 = vct_A.x;
    v57 = wk->rot.z;
    v109.w = wk->rot.w;
    v92 = vct_A.x;
    v88 = wk->rot.w;
    v89 = wk->pos.x;
    v109.w = v88;
    v106.x = v89;
    v56 = v92;
    per = v56;
    v106.y = v51;
    v106.z = v52;
    v106.w = v53;
    v109.x = v54;
    v109.y = v55;
    v109.z = v57;
    *(u64 *)&v102.x = 0;
    Radian = sBtlGetRadian(v106, v109, v102, per);
    sBtlAddUnitDeg(wk, Radian);
    AnlogKeyToDir = v96;
    *p_rot = vct_A;
    p_rotbk = &wk->rotbk;
    *p_rotbk = vct_A;
    goto LABEL_85;
  }
LABEL_85:
  wk->next_motionno = 91;
  sbtlplayertblSetPlayerMotionData_Hokan(wk);
  beforeframe = wk->beforeframe;
  sBtlSetMotion(wk, 91, beforeframe, 0, 0);
  sBtlSetAction(wk, 1, 0);
  gJump_local = gJump;
  *(u64 *)&gJump_local->Step = 60;
  *(u16 *)&gJump_local->Use = 1;
  gJump_local->StepBoolA = 0;
  *(u64 *)&gJump_local->InputTime = 0;
  *(u64 *)&gJump_local->SpeedRise3 = 3246915584LL;
  if (AnlogKeyToDir >= 48.0)
    v68 = 10.0;
  else
    v68 = 0.0;
  gJump_local->SpeedMove = v68;
  v69 = gJump;
  v69->HighJump = 1;
  *(u64 *)&v69->PeakY = 0;
  v69->SkillStY = 0.0;
  *(u16 *)&v69->ReJumpInput = 256;
  wk->hstatus |= 0x80000u;
  if (v69->Y > -30.0)
  {
    FootEff(wk, 0.0, 0.0, 0.2, 4.0, 0);
  }
  v70 = wk->rot.x;
  v71 = wk->rot.y;
  v72 = wk->rot.z;
  v73 = wk->rot.w;
  v107.x = v70;
  v107.y = v71;
  v107.z = v72;
  v107.w = v73;
  RotToDir = sBtlGetRotToDir(v107);
  v76 = RotToDir;
  v77 = wk->pos.x;
  v78 = wk->pos.y;
  Add(2, v77, v78 + gJump->Y, wk->pos.z, v76, 0);
  v79 = wk->pos.x;
  v80 = wk->pos.y;
  v81 = wk->pos.z;
  v82 = wk->pos.w;
  v108.x = v79;
  v108.y = v80;
  v108.z = v81;
  v108.w = v82;
  sBtlPlay3DSE(0x10107u, v108);
  JumpVoice(v83);
  v86 = wk;
  v86->kochokuCnt = 999;
  v86->mode = 19;
}

// 0x1fa1f70
static void JumpVoice(SBTLUNIT_WORK *wk) {
  char **v3;

  switch ((u32)sub_1905740(6, 0))
  {
    case 0u:
      v3 = &"PVA01A_22D_002";
      goto LABEL_5;
    case 1u:
      v3 = &"PVA01A_22D_000";
      goto LABEL_5;
    case 2u:
      v3 = &"PVA01A_26A_000";
      goto LABEL_5;
    case 3u:
      v3 = &"PVA01A_26A_001";
      goto LABEL_5;
    case 4u:
      v3 = &"PVA01A_26A_002";
      goto LABEL_5;
    case 5u:
      v3 = &"PVA01A_26A_003";
LABEL_5:
      sndVoicePlayFile(*v3, 0);
      break;
    default:
      return;
  }
}

// 0x1fa2c40
void sBtlJumpHAtk1Start(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  sdfVector4_t v16;
  sdfVector4_t v17;

  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v16.x = x;
  v16.y = y;
  v16.z = z;
  v16.w = w;
  RotToDir = sBtlGetRotToDir(v16);
  v9 = RotToDir;
  v10 = wk->pos.x;
  v11 = wk->pos.y;
  Add(2, v10, v11 + gJump->Y, wk->pos.z, v9, 0);
  v12 = wk->pos.x;
  v13 = wk->pos.y;
  v14 = wk->pos.z;
  v15 = wk->pos.w;
  v17.x = v12;
  v17.y = v13;
  v17.z = v14;
  v17.w = v15;
  sBtlPlay3DSE(0x10107u, v17);
}

// 0x1fa2d70
static void JumpCalc_Move(SBTLUNIT_WORK *wk, f32 _DirLR) {
  f32 ABS;
  u32 Step;
  f32 v10;
  P_JUMP_t *v12;
  f32 dir;

  ABS = sBtlGetABS(DirLR);
  if (GetAnlogKeyToDir(wk, &dir) < 48.0)
    return;
  Step = gJump->Step;
  if (Step >= 5)
  {
    if (Step != 10 || ABS >= 45.0)
      goto LABEL_25;
    v10 = 0.2;
    goto LABEL_13;
  }
  if (ABS >= 45.0)
  {
    if (ABS <= 90.0)
      goto LABEL_25;
    v10 = 0.5;
  }
  else
  {
    v10 = 2.0;
  }
LABEL_13:
  gJump->SpeedMove = gJump->SpeedMove + v10;
LABEL_25:
  v12 = gJump;
  if (v12->SpeedMove <= 10.0)
    return;
  v12 = gJump;
  v12->SpeedMove = 10.0;
}

// 0x1fa2f70
static void JumpCalc(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 z;
  f32 GroundPos;
  f32 v9;
  P_JUMP_t *v10;
  s32 Step;
  bool v12;
  bool v13;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v17;
  P_JUMP_t *v18;
  f32 v19;
  P_JUMP_t *v20;
  s32 v21;
  f32 v23;
  f32 v24;
  SBATTLE_WORK *v26;
  P_JUMP_t *v29;
  f32 v31;
  f32 v32;
  dds3ModelHandle_t *v33;
  P_JUMP_t *v35;
  f32 v36;
  dds3ModelHandle_t *v37;
  dds3ModelHandle_t *v39;
  P_JUMP_t *v42;
  f32 Y;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 w;
  f32 v48;
  f32 RotToDir;
  dds3ModelHandle_t *v50;
  P_JUMP_t *v52;
  f32 v53;
  P_JUMP_t *v54;
  f32 SpeedRise3;
  f32 v56;
  s64 v57;
  f32 v58;
  f32 SpeedRise;
  f32 v61;
  f32 v63;
  f32 v64;
  s32 beforeframe;
  s32 v66;
  SBTLUNIT_WORK *v67;
  s32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  f32 SpeedFall;
  f32 v73;
  P_JUMP_t *v74;
  f32 v75;
  s32 v77;
  s32 v78;
  SBATTLE_WORK *v80;
  s32 kochokuCnt;
  f32 v82;
  dds3ModelHandle_t *v83;
  f32 v84;
  P_JUMP_t *v86;
  u32 RetStep;
  f32 v88;
  dds3ModelHandle_t *v89;
  P_JUMP_t *v91;
  dds3ModelHandle_t *v92;
  P_JUMP_t *v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  P_JUMP_t *v105;
  f32 v107;
  f32 v109;
  f32 v110;
  s64 ToZ;
  s64 ToX;
  sdfVector4_t v113;
  sdfVector4_t v114;

  ToX = 0;
  ToZ = 0;
  if (!gJump->Use)
    return;
  if (gJump->Pause)
  {
    if (gJump->SpeedFall > 0.0)
      return;
  }
  x = wk->pos.x;
  z = wk->pos.z;
  GroundPos = sBtlGetGroundPos(x, z);
  v9 = GroundPos;
  v10 = gJump;
  Step = v10->Step;
  v12 = (u32)Step >= 0x20;
  v13 = Step == 32;
  if (Step > 32)
  {
LABEL_19:
    switch (Step)
    {
      case '2':
        hModel = wk->hModel;
        MotionFrameF = mdlGetMotionFrameF(hModel);
        v17 = MotionFrameF;
        v18 = gJump;
        v19 = v18->SpeedRise2 + 0.5;
        v18->SpeedRise2 = v19;
        if (v19 >= 0.0)
        {
          v18 = gJump;
          v18->SpeedRise2 = 0.0;
        }
        v20 = gJump;
        v20->Y = v20->Y + v20->SpeedRise2;
        if (v17 < 20.0)
          goto LABEL_236;
        v20 = gJump;
        v21 = 51;
        goto LABEL_90;
      case '3':
        v37 = wk->hModel;
        if (mdlGetMotionFrameF(v37) < 25.0)
          goto LABEL_236;
        v21 = 52;
        v20 = gJump;
        goto LABEL_90;
      case '4':
        v39 = wk->hModel;
        mdlGetMotionFrameF(v39);
        v42 = gJump;
        Y = v42->Y;
        v42->SpeedFall = 40.0;
        v44 = Y + 40.0;
        v42->Y = v44;
        if ((f32)(v44 + wk->pos.y) >= v9)
        {
          v42 = gJump;
          v42->Y = 0.0;
          *(u64 *)&v42->Step = 53;
          wk->flg &= ~0x40000u;
          if (v42->SpeedMove > 5.0)
          {
            v42 = gJump;
            v42->SpeedMove = 5.0;
          }
          sBtlSetFirstAtk(1317);
          v45 = wk->rot.x;
          v46 = wk->rot.y;
          v48 = wk->rot.z;
          w = wk->rot.w;
          v113.x = v45;
          v113.y = v46;
          v113.z = v48;
          v113.w = w;
          RotToDir = sBtlGetRotToDir(v113);
          sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir, 30.0, (f32 *)&ToZ + 1, &ToZ);
          Add(*((f32 *)&ToZ + 1), 0.0, *(f32 *)&ToZ, RotToDir, 1, 0);
          sBtlPlaySE(0x10111u);
        }
        goto LABEL_236;
      case '5':
        goto LABEL_76;
      case '<':
        v50 = wk->hModel;
        mdlGetMotionFrameF(v50);
        v52 = gJump;
        v53 = v52->SpeedRise3 + 1.5;
        v52->SpeedRise3 = v53;
        if (v53 >= 0.0)
        {
          v52 = gJump;
          v52->SpeedRise3 = 0.0;
        }
        v54 = gJump;
        SpeedRise3 = v54->SpeedRise3;
        v56 = v54->Y + SpeedRise3;
        v54->Y = v56;
        if (SpeedRise3 < 0.0)
          goto LABEL_236;
        v54 = gJump;
        v56 = v54->Y;
        v57 = 61;
        goto LABEL_148;
      case '=':
        goto LABEL_70;
      default:
        goto LABEL_236;
    }
  }
  if (v13 || !v12)
  {
    switch (Step)
    {
      case 0:
        v10 = gJump;
        v23 = v10->InputTime + VRF_DeltaTime;
        v10->InputTime = v23;
        if (v23 >= (f32)(FPS60 * 3.0))
        {
          v10 = gJump;
          v24 = v10->SpeedRise + 1.0;
          v10->SpeedRise = v24;
          if (v24 >= 0.0)
          {
            v10 = gJump;
            v10->SpeedRise = 0.0;
          }
        }
        gJump->Y = gJump->Y
                                           + gJump->SpeedRise;
        if (!ChkKeyPressJump())
        {
          v26 = wk;
          if (!v26->bRR_Assist)
          {
            v26 = wk;
            if (!v26->bRU_Assist)
            {
              gJump->HighJump = 0;
            }
          }
        }
        v20 = gJump;
        if (v20->HighJump)
          goto LABEL_257;
        v20 = gJump;
        if (v20->InputTime < (f32)(FPS60 + FPS60))
        {
LABEL_257:
          v29 = gJump;
          if (v29->InputTime >= (f32)(FPS60 * 6.0))
          {
            v29 = gJump;
            *(u64 *)&v29->Step = 3;
          }
        }
        else
        {
          v20 = gJump;
          v21 = 1;
LABEL_90:
          v20->Step = v21;
        }
        break;
      case 1:
        v58 = v10->SpeedRise + 5.0;
        v10->SpeedRise = v58;
        if (v58 < 0.0)
          goto LABEL_125;
        goto LABEL_9001;
        if (v109 < 0.0)
        {
LABEL_125:
          goto LABEL_126;
        }
LABEL_9001:
        v10 = gJump;
        v10->SpeedRise = 0.0;
LABEL_126:
        v54 = gJump;
        SpeedRise = v54->SpeedRise;
        v56 = v54->Y + SpeedRise;
        v54->Y = v56;
        if (SpeedRise < 0.0)
          break;
        v54 = gJump;
        v56 = v54->Y;
        v57 = 2;
        goto LABEL_148;
      case 2:
        v10 = gJump;
        v61 = v10->StepTime + VRF_DeltaTime;
        v10->StepTime = v61;
        if (v61 < (f32)(FPS60 * 0.0))
          break;
        v10 = gJump;
        v63 = v10->Y;
        *(u64 *)&v10->Step = 10;
        v10->PeakY = v63;
        v64 = (f32)(FPS60 * 3.0) + 0.0;
        v10->Time = v64;
        v10->SpeedFall = (f32)(v64 * 11.8) + 0.0;
        goto LABEL_136;
      case 3:
        v69 = v10->SpeedRise + 1.0;
        v10->SpeedRise = v69;
        if (v69 < 0.0)
          goto LABEL_143;
        goto LABEL_9002;
        if (v110 < 0.0)
        {
LABEL_143:
          goto LABEL_144;
        }
LABEL_9002:
        v10 = gJump;
        v10->SpeedRise = 0.0;
LABEL_144:
        v54 = gJump;
        v70 = v54->SpeedRise;
        v56 = v54->Y + v70;
        v54->Y = v56;
        if (v70 >= 0.0)
        {
          v54 = gJump;
          v56 = v54->Y;
          v57 = 4;
LABEL_148:
          *(u64 *)&v54->Step = v57;
          v54->PeakY = v56;
        }
        break;
      case 4:
LABEL_70:
        v10 = gJump;
        v31 = v10->StepTime + VRF_DeltaTime;
        v10->StepTime = v31;
        if (v31 < (f32)(FPS60 * 0.0))
          break;
        v10 = gJump;
        v32 = v10->Y;
        v10->Time = 0.0;
        *(u64 *)&v10->Step = 10;
        v10->SpeedFall = 0.0;
        v10->PeakY = v32;
LABEL_136:
        wk->next_motionno = 92;
        sbtlplayertblSetPlayerMotionData_Hokan(wk);
        beforeframe = wk->beforeframe;
        v66 = 92;
        v67 = wk;
        v68 = beforeframe;
        goto LABEL_176;
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
      case 21:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
      case 28:
      case 29:
        break;
      case 10:
        v10 = gJump;
        v71 = v10->Time + VRF_DeltaTime;
        SpeedFall = v10->SpeedFall;
        v10->Time = v71;
        v73 = SpeedFall + (f32)(v71 * 11.8);
        v10->SpeedFall = v73;
        if (v73 > 70.0)
        {
          v10 = gJump;
          v10->SpeedFall = 70.0;
        }
        v74 = gJump;
        v75 = v74->Y + (f32)(v74->Time * v74->SpeedFall);
        v74->Y = v75;
        if ((f32)(wk->pos.y + v75) < v9)
          break;
        v74 = gJump;
        v74->Y = 0.0;
        *(u64 *)&v74->Step = 11;
        wk->flg &= ~0x40000u;
        if (v74->SpeedMove > 5.0)
        {
          v74 = gJump;
          v74->SpeedMove = 5.0;
        }
        FootEff(wk, 0.0, 0.1, 0.15, 3.0, 0);
        wk->kochokuCnt = 50;
        if (wk->motionno == 89)
          v77 = 87;
        else
          v77 = 93;
        wk->next_motionno = v77;
        sbtlplayertblSetPlayerMotionData_Hokan(wk);
        v78 = wk->beforeframe;
        v67 = wk;
        v66 = v77;
        v68 = v78;
LABEL_176:
        sBtlSetMotion(v67, v66, v68, 0, 0);
        break;
      case 11:
        v10 = gJump;
        v10->StepTime = v10->StepTime + VRF_DeltaTime;
        v80 = wk;
        kochokuCnt = v80->kochokuCnt;
        if (kochokuCnt)
        {
          v80 = wk;
          kochokuCnt = v80->kochokuCnt;
          v80->kochokuCnt = kochokuCnt - 1;
        }
        v35 = gJump;
        v82 = v35->SpeedMove + -0.15;
        v35->SpeedMove = v82;
        if (v82 >= 0.0)
          break;
        goto LABEL_83;
      case 20:
        v83 = wk->hModel;
        v84 = mdlGetMotionFrameF(v83);
        if (v84 >= 7.0)
        {
          v86 = gJump;
          RetStep = v86->RetStep;
          v86->Step = RetStep;
          if (RetStep <= 0x3D && ((1 << RetStep) & 0x300000000000001FLL) != 0)
          {
            v86 = gJump;
            v88 = v86->Y;
            v86->SpeedRise = 0.0;
            *(u64 *)&v86->Step = 10;
            v86->Time = 0.0;
            v86->SpeedRise3 = 0.0;
            v86->SpeedFall = 0.0;
            v86->PeakY = v88;
          }
        }
        gJump->SkillStY = gJump->Y;
        break;
      case 30:
        v10 = gJump;
        v10->SkillStY = v10->Y;
        v89 = wk->hModel;
        if (mdlGetMotionFrameF(v89) >= 5.0)
        {
          v91 = gJump;
          v91->Step = 31;
          v91->StepBoolA = 0;
        }
        break;
      case 31:
        v92 = wk->hModel;
        mdlGetMotionFrameF(v92);
        v95 = gJump;
        v96 = v95->Y;
        v95->SpeedFall = 30.0;
        v97 = v96 + 30.0;
        v95->Y = v97;
        if (!v95->StepBoolA)
        {
          v98 = wk->pos.y;
          v97 = gJump->Y;
          if ((f32)(v98 + v97) >= (f32)(v9 + -100.0))
          {
            v99 = wk->rot.x;
            v100 = wk->rot.y;
            v102 = wk->rot.z;
            v101 = wk->rot.w;
            v114.x = v99;
            v114.y = v100;
            v114.z = v102;
            v114.w = v101;
            v103 = sBtlGetRotToDir(v114);
            sBtlGetMoveXZ(wk->pos.x, wk->pos.z, v103, 30.0, (f32 *)&ToX + 1, &ToX);
            AW_JumpAdd(*((f32 *)&ToX + 1), 0.0, *(f32 *)&ToX, v103);
            gJump->StepBoolA = 1;
          }
        }
        v104 = wk->pos.y;
        v105 = gJump;
        if ((f32)(v104 + v105->Y) >= v9)
        {
          v105 = gJump;
          v105->Y = 0.0;
          *(u64 *)&v105->Step = 32;
          wk->flg &= ~0x40000u;
          if (v105->SpeedMove > 5.0)
          {
            v105 = gJump;
            v105->SpeedMove = 5.0;
          }
          sBtlSetFirstAtk(1304);
        }
        break;
      case 32:
LABEL_76:
        v33 = wk->hModel;
        mdlGetMotionFrameF(v33);
        v35 = gJump;
        v36 = v35->SpeedMove + -0.5;
        v35->SpeedMove = v36;
        if (v36 >= 0.0)
          break;
        wk->hstatus &= ~0x80000u;
        v35 = gJump;
LABEL_83:
        v35->SpeedMove = 0.0;
        break;
      default:
        goto LABEL_19;
    }
  }
LABEL_236:
  v107 = gJump->Y;
  wk->JumpOfsPos.y = v107;
  sBtlUpdateUnitJumpOfsPos(wk);
}

// 0x1f85e80
static s32 JumpProc(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  s32 v10;
  f32 x;
  f32 y;
  f32 z;
  f32 v17;
  struct sdfVector4_t pos;
  f32 *p_x;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 w;
  f32 Rotate_Jump;
  u32 Step;
  _BOOL4 bRU_Assist;
  s32 v35;
  P_JUMP_t *v36;
  SBATTLE_WORK *v38;
  P_JUMP_t *v41;
  s32 v42;
  SBATTLE_WORK *v46;
  P_JUMP_t *v47;
  P_JUMP_t *v49;
  SBATTLE_WORK *v50;
  _BOOL4 bRR_Assist;
  P_JUMP_t *v53;
  P_JUMP_t *v55;
  bool v56;
  P_JUMP_t *v57;
  s32 v59;
  P_JUMP_t *v60;
  P_JUMP_t *v63;
  u32 v64;
  SBATTLE_WORK *v68;
  SBATTLE_WORK *v70;
  SBATTLE_WORK *v75;
  s32 kochokuCnt;
  P_JUMP_t *v83;
  s32 NextSkill;
  bool v85;
  SBATTLE_WORK *v88;
  s32 v89;
  s32 v90;
  s32 hstatus;
  u32 v92;
  s32 v93;
  s32 NextSkillRS;
  SBTLUNIT_WORK *v97;
  s32 v98;
  s32 v99;
  SBATTLE_WORK *v108;
  u32 v112;
  u32 v115;
  s32 m_type;
  s32 v119;
  s32 v120;
  bool v121;
  bool IsBattleKey;
  struct sdfVector4_t v123;
  sdfVector4_t direction;
  sdfMatrix4_t v127;
  sdfMatrix4_t v128;
  sdfVector4_t v129;
  sdfVector4_t v131;
  sdfVector4_t v132;

  *(u64 *)&direction.x = 0;
  *(u64 *)&direction.z = 0;
  v4 = wk;
  if (v4->bSpiritSkill)
  {
    sBtlResetJump(wk);
    sBtlPlayerRSpiritInit(wk);
    return 2;
  }
  if (!v4->bSetsuma)
    goto LABEL_30;
  if (gJump->Step > 1u)
    goto LABEL_30;
  if (gJump->Y < -50.0)
    goto LABEL_30;
  v10 = sBtlInputChkSetsuma(wk);
  if (v10)
  {
LABEL_29:
    sBtlSetFirstAtk(v10);
    return 2;
  }
LABEL_30:
  JumpCalc(wk);
  wk->hstatus &= ~0x40000u;
  if (wk->kochokuCnt >= 11)
  {
    if (GetAnlogKey(wk, &direction) > 48.0)
    {
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      v17 = mapGetScreenDir(x, y, z, 0.0) * -0.017453292;
      sub_1949280(0, v17);
      v123 = direction;
      vct_A = v123;
      get_transpose(&v128, &mtx_A, 0);
      v127 = v128;
      v129 = op_Multiply_60923920(&v127, vct_A, 0);
      vct_A = v129;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_A);
      pos = wk->pos;
      vct_B = pos;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      p_x = &vf00.x;
      v24 = p_x[4];
      v25 = p_x[5];
      v26 = p_x[6];
      w = p_x[7];
      v131.x = v24;
      v131.y = v25;
      v131.z = v26;
      v131.w = w;
      Rotate_Jump = sBtlGetRotate_Jump(wk, v131);
      v132.x = v24;
      v132.y = v25;
      v132.z = v26;
      v132.w = w;
      sBtlCheckRotSpd(wk, v132);
      goto LABEL_65;
    }
  }
  Rotate_Jump = 999.0;
LABEL_65:
  JumpCalc_Move(wk, Rotate_Jump);
  Step = gJump->Step;
  if (Step <= 0x3D && ((1 << Step) & 0x300000000000001FLL) != 0)
  {
    bRU_Assist = 0;
    v35 = 0;
    goto LABEL_69;
  }
  v50 = wk;
  bRR_Assist = v50->bRR_Assist;
  v56 = !bRR_Assist;
  bRU_Assist = v50->bRU_Assist;
  v35 = !v56;
LABEL_69:
  v36 = gJump;
  if (v36->Y >= -50.0)
  {
    if ((v36->Step & 0xFFFFFFFE) != 0xA)
      goto LABEL_166;
    v46 = wk;
    if (v46->bRaiSkill_RU)
    {
      v47 = gJump;
      v49 = gJump;
      v47->NextSkill = GBWK->player->raidouSkill[0];
      v49->NextSkillRS = 0;
      goto LABEL_166;
    }
    v46 = wk;
    if (v46->bRaiSkill_RL)
    {
      v53 = gJump;
      v55 = gJump;
      v53->NextSkill = GBWK->player->raidouSkill[1];
      v59 = 1;
LABEL_165:
      v55->NextSkillRS = v59;
      goto LABEL_166;
    }
    v46 = wk;
    if (v46->bRaiSkill_RD)
    {
      v57 = gJump;
      v55 = gJump;
      v57->NextSkill = GBWK->player->raidouSkill[2];
      v59 = 2;
      goto LABEL_165;
    }
    v46 = wk;
    if (v46->bRR)
      goto LABEL_429;
    v46 = wk;
    if (v46->bRR_Assist)
    {
LABEL_429:
      sBtlBS_LASTB1_Action_Req();
      gJump->NextSkill = 1310;
      goto LABEL_166;
    }
    v46 = wk;
    if (!v46->bComboSRU)
    {
      v46 = wk;
      if (!v46->bRU_Assist)
      {
        v121 = CHECK_PRESS(20488, 1);
        if (!v121)
        {
          IsBattleKey = sBtlIsBattleKey(4122, 2);
          if (IsBattleKey)
          {
            gJump->NextSkill = 176;
            return 2;
          }
        }
LABEL_166:
        v60 = gJump;
        if (v60->Step != 10)
          goto LABEL_183;
        v60 = gJump;
        if (v60->Y <= -80.0)
        {
LABEL_183:
          v63 = gJump;
          v64 = v63->Step;
          if (v64 >= 5 && v64 != 10)
            goto LABEL_202;
          v63 = gJump;
          if (v63->Jump3Use)
          {
LABEL_202:
            if (gJump->Step != 11)
              goto LABEL_375;
            if (wk->kochokuCnt > 50)
            {
LABEL_210:
              v68 = wk;
              if (v68->kochokuCnt <= 50)
              {
                v68 = wk;
                if (v68->bGuard)
                {
                  gJump->Use = 0;
                  sBtlResetAction(wk);
                  sBtlSetUseSkill(wk, 0, 0);
                  return 2;
                }
              }
              v70 = wk;
              if (v70->kochokuCnt <= 48)
              {
                v70 = wk;
                if (v70->bGunMode)
                {
                  sBtlResetAction(wk);
                  sBtlChangeGunMode(wk);
                  return 2;
                }
              }
              if (wk->kochokuCnt > 45)
                goto LABEL_242;
              v83 = gJump;
              NextSkill = v83->NextSkill;
              if (NextSkill <= 191)
              {
                if (NextSkill <= 65)
                {
                  if (NextSkill <= 23)
                  {
                    if (NextSkill != 8 && NextSkill != 23)
                      goto LABEL_242;
                  }
                  else if ((NextSkill | 0x10) != 0x37 && (NextSkill & 0xFFFFFFFE) != 0x40)
                  {
                    goto LABEL_242;
                  }
                }
                else if ((u32)NextSkill <= 0xA3)
                {
                  v92 = NextSkill - 156;
                  if (v92 > 7 || ((1 << v92) & 0x87) == 0)
                    goto LABEL_242;
                }
                else
                {
                  if (NextSkill == 167)
                    goto LABEL_310;
                  if (NextSkill == 176)
                  {
                    v90 = 176;
                    goto LABEL_419;
                  }
                  if (NextSkill != 191)
                    goto LABEL_242;
                }
              }
              else
              {
                if ((u32)NextSkill > 0x513)
                {
                  if ((u32)NextSkill <= 0x51E)
                  {
                    if (NextSkill != 1307 && NextSkill != 1310)
                      goto LABEL_242;
                  }
                  else if ((u32)(NextSkill - 1323) > 0x10 || ((1 << (NextSkill - 43)) & 0x10401) == 0)
                  {
                    goto LABEL_242;
                  }
LABEL_310:
                  v83 = gJump;
                  NextSkill = v83->NextSkill;
                  v83->Use = 0;
                  hstatus = wk->hstatus;
                  wk->JumpOfsPos.y = 0.0;
                  wk->hstatus = hstatus & 0xFFF7FFFF;
                  sBtlSetFirstAtk(NextSkill);
                  return 2;
                }
                if ((u32)NextSkill <= 0xD4)
                {
                  if ((NextSkill | 4) != 0xD4)
                    goto LABEL_242;
                }
                else if ((u32)(NextSkill - 312) >= 2 && NextSkill != 744)
                {
                  if (NextSkill != 1299)
                    goto LABEL_242;
                  v90 = 1299;
LABEL_419:
                  v83->Use = 0;
                  v120 = wk->hstatus;
                  wk->JumpOfsPos.y = 0.0;
                  wk->hstatus = v120 & 0xFFF7FFFF;
                  sBtlSetFirstAtk(v90);
                  return 2;
                }
              }
              v83 = gJump;
              v83->Use = 0;
              v93 = wk->hstatus;
              wk->JumpOfsPos.y = 0.0;
              wk->hstatus = v93 & 0xFFF7FFFF;
              NextSkillRS = v83->NextSkillRS;
              if (NextSkillRS)
              {
                NextSkillRS = gJump->NextSkillRS;
                if (NextSkillRS == 1)
                {
                  v97 = wk;
                  v98 = 1;
                  v99 = GBWK->player->raidouSkill[1];
                }
                else
                {
                  NextSkillRS = gJump->NextSkillRS;
                  if (NextSkillRS != 2)
                    goto LABEL_242;
                  v97 = wk;
                  v98 = 2;
                  v99 = GBWK->player->raidouSkill[2];
                }
              }
              else
              {
                v97 = wk;
                v98 = 0;
                v99 = GBWK->player->raidouSkill[0];
              }
              if (sBtlPlayerRSkillInit(v97, v99, v98))
                return 2;
LABEL_242:
              v75 = wk;
              if (v75->kochokuCnt <= 45)
              {
                v75 = wk;
                if (v75->bComboLRU)
                {
                  gJump->Use = 0;
                  sBtlResetAction(wk);
                  sBtlSetUseSkill(wk, 0, 0);
                  sBtlSetAction(wk, 1, 0);
                  return 2;
                }
              }
              kochokuCnt = wk->kochokuCnt;
              if (kochokuCnt <= 47)
              {
                v85 = JumpProc_Jump(sBtlPlayer);
                if (v85)
                  goto LABEL_430;
                if (gJump->ReJumpInput)
                {
LABEL_430:
                  gJump->Use = 0;
                  wk->JumpOfsPos.y = 0.0;
                  wk->hstatus &= ~0x80000u;
                  sBtlJumpStart(wk);
                  return 2;
                }
              }
              else
              {
                if (JumpProc_Jump(sBtlPlayer))
                {
                  gJump->ReJumpInput = 1;
                }
              }
              v88 = wk;
              if (v88->kochokuCnt <= 45)
              {
                v88 = wk;
                if (v88->bSetsuma)
                {
                  v89 = sBtlInputChkSetsuma(wk);
                  if (v89)
                  {
                    v10 = v89;
                    goto LABEL_29;
                  }
                }
              }
              if (wk->kochokuCnt <= 46)
              {
                if (gJump->PeakY > -90.0)
                  goto LABEL_359;
              }
              if (wk->kochokuCnt > 40)
                goto LABEL_355;
              if (gJump->PeakY <= -120.0)
              {
LABEL_355:
                if (wk->kochokuCnt > 30)
                  goto LABEL_375;
              }
LABEL_359:
              if (sBtlIsMoveBtn(sBtlPlayer))
              {
                gJump->Use = 0;
                sBtlResetAction(wk);
                goto LABEL_392;
              }
              v108 = wk;
              v108->bHuumaCancel = 1;
              if (!IsSceanStop())
              {
                if (sBtlNormalProc_Huuma(wk, 0) == 2)
                  return 2;
              }
LABEL_375:
              v112 = gJump->Step;
              if (v112 > 0x35 || ((1 << v112) & 0x20000100000800LL) == 0)
                return 2;
              if (!sBtlCheckMotionEnd(wk))
                return 2;
              gJump->Use = 0;
              if (wk->actwk->status == 9)
              {
                if (!v115)
                sBtlResetAction(wk);
                return 2;
              }
              if (!v115)
              sBtlResetAction(wk);
LABEL_392:
              sBtlSetUseSkill(wk, 0, 0);
              sBtlSetMotion(wk, 0, 0, 0, 0);
              return 2;
            }
            if (sBtlIsBattleKey(4124, 2))
            {
              gJump->Use = 0;
              wk->JumpOfsPos.y = 0.0;
              wk->hstatus &= ~0x80000u;
              KaihiInit_Sub(wk, 0);
              return 2;
            }
            goto LABEL_210;
          }
          if (!wk->bJump)
            goto LABEL_202;
          sBtlJump3Start(wk);
          goto LABEL_202;
        }
        if (!wk->bJump)
          goto LABEL_183;
        gJump->ReJumpInput = 1;
        goto LABEL_183;
      }
    }
    sBtlBS_LASTB1_Action_Req();
    if (sBtlDat()->m_type == 1)
    {
      gJump->NextSkill = 1323;
      if (sBtlDat()->m_type != 2)
      {
LABEL_407:
        m_type = sBtlDat()->m_type;
        if (m_type != 3)
          goto LABEL_166;
        goto LABEL_413;
      }
    }
    else if (sBtlDat()->m_type != 2)
    {
      goto LABEL_407;
    }
    gJump->NextSkill = 1333;
    v119 = sBtlDat()->m_type;
    if (v119 != 3)
      goto LABEL_166;
LABEL_413:
    gJump->NextSkill = 1339;
    goto LABEL_166;
  }
  v38 = wk;
  if (v38->bRR | v35)
    goto LABEL_72;
  goto LABEL_86;
  if (!(v38->bRR | v35))
  {
LABEL_86:
    v38 = wk;
    if (bRU_Assist || v38->bRU)
    {
      sBtlBS_LASTB1_Action_Req();
      if (!sbtlplayertblChkNG_TutoEtc(0, 1316, 0))
      {
        JumpHAtkStart(wk);
        sBtlSetFirstAtk(1316);
      }
      return 2;
    }
    goto LABEL_166;
  }
LABEL_72:
  sBtlBS_LASTB1_Action_Req();
  if (!sbtlplayertblChkNG_TutoEtc(0, 1305, 0))
  {
    v41 = gJump;
    v42 = v41->Step;
    if (v42 == 20)
      goto LABEL_133;
    goto LABEL_130;
    if (v42 == 20)
    {
LABEL_133:
      sBtlSetFirstAtk(1305);
      return 2;
    }
LABEL_130:
    v41 = gJump;
    v42 = v41->Step;
    v41->RetStep = v42;
    v41->Step = 20;
    goto LABEL_133;
  }
  return 2;
}

// 0x1fa4580
bool sBtlJumpProc_Eve(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v6;
  bool result;
  u32 Step;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v6 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!gJump->Use)
  {
    if (wk->mode != 19)
      return 0;
    goto LABEL_30;
  }
  JumpCalc(v6);
  v6->hstatus &= ~0x40000u;
  sBtlPlayerUpdate(v6);
  result = 1;
  Step = gJump->Step;
  if (Step <= 0x35 && ((1 << Step) & 0x20000100000800LL) != 0)
  {
    if (sBtlCheckMotionEnd(v6))
    {
      gJump->Use = 0;
LABEL_30:
      sBtlResetAction(v6);
      sBtlSetUseSkill(v6, 0, 0);
      sBtlSetMotion(v6, 0, 0, 0, 0);
      return 0;
    }
    return 1;
  }
  return result;
}

// 0x1fa44a0
static void JumpAtk1Start(SBTLUNIT_WORK *wk) {
  s32 Step;

  Step = gJump->Step;
  if (Step == 20)
    return;
  gJump->RetStep = Step;
  gJump->Step = 20;
}

// 0x1f9a100
static s32 JumpAtk1Proc(SBTLUNIT_WORK *wk) {
  JumpCalc(wk);
  wk->hstatus &= ~0x40000u;
  JumpCalc_Move(wk, 999.0);
  return 2;
}

// 0x1f9a3d0
static void JumpAtk2Start(SBTLUNIT_WORK *wk) {
  P_JUMP_t *gJump_local;
  f32 Y;

  gJump_local = gJump;
  Y = gJump_local->Y;
  gJump_local->RetStep = -1;
  gJump_local->Time = 0.0;
  gJump_local->SpeedFall = 0.0;
  *(u64 *)&gJump_local->Step = 30;
  gJump_local->PeakY = Y;
}

// 0x1f9a2a0
static void JumpAtk2Start_From_APPROACHATK(SBTLUNIT_WORK *wk) {
  P_JUMP_t *gJump_local;
  P_JUMP_t *v8;
  f32 Y;

  gJump_local = gJump;
  gJump_local->Y = -170.0;
  gJump_local->SpeedFall = 0.0;
  *(u16 *)&gJump_local->Use = 1;
  sBtlPlayerSetCamJump_To_CamJump2();
  v8 = gJump;
  Y = v8->Y;
  v8->RetStep = -1;
  v8->Time = 0.0;
  v8->SpeedFall = 0.0;
  *(u64 *)&v8->Step = 30;
  wk->JumpOfsPos.y = 0.0;
  v8->PeakY = Y;
}

// 0x1f9a190
static s32 JumpAtk2Proc(SBTLUNIT_WORK *wk) {
  JumpCalc(wk);
  wk->hstatus &= ~0x40000u;
  JumpCalc_Move(wk, 999.0);
  return 2;
}

// 0x1f9a450
static void JumpHAtkStart(SBTLUNIT_WORK *wk) {
  f32 v5;

  wk->flg |= 0x40000u;
  gJump[20] = NAN;
  v5 = gJump[10];
  *((u32 *)gJump + 5) = 50;
  gJump[12] = -22.0;
  LODWORD(gJump) = wk->hstatus;
  wk->JumpOfsPos.y = v5;
  wk->hstatus = (u32)gJump & 0xFFF7FFFF;
}

// 0x1f9a220
static s32 JumpHAtkProc(SBTLUNIT_WORK *wk) {
  JumpCalc(wk);
  wk->hstatus &= ~0x40000u;
  return 2;
}

// 0x1fa4100
f32 sBtlGetRotate_Jump(SBTLUNIT_WORK *wk, const sdfVector4_t *pos) {
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData_P;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 Radian;
  f32 v17;
  f32 v18;
  f32 v19;
  sdfVector4_t *p_rotbk;
  f32 v22;
  f32 rot_spd;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  s32 v28;
  f32 v30;
  s32 v31;
  f32 v32;
  f32 per;
  sdfVector4_t v36;
  sdfVector4_t v37;
  sdfVector4_t v38;

  per = pos->x;
  major = wk->major;
  minor = wk->minor;
  VisualData_P = sBtlGetVisualData_P(major, minor);
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v12 = wk->rot.x;
  v13 = wk->rot.y;
  v14 = wk->rot.z;
  v15 = wk->rot.w;
  v37.y = y;
  v37.z = z;
  v37.w = w;
  v38.x = v12;
  v38.y = v13;
  v38.z = v14;
  v38.w = v15;
  *(u64 *)&v36.x = 0;
  v37.x = x;
  Radian = sBtlGetRadian(v37, v38, v36, per);
  if (Radian >= -135.0 && Radian <= 135.0)
  {
    v17 = -90.0;
    if (Radian >= -90.0)
    {
      v17 = 90.0;
      if (Radian <= 90.0)
      {
        if (Radian >= 0.0 || (v17 = 0.0, Radian <= -15.0))
        {
          if (Radian >= 15.0 || Radian <= 0.0)
            v17 = Radian;
          else
            v17 = 0.0;
        }
      }
    }
  }
  else
  {
    v17 = 0.0;
    wk->hstatus |= 0x40000u;
  }
  v18 = 30.0;
  v19 = v17 / v18;
  p_rotbk = &wk->rotbk;
  v22 = v19 + 360.0;
  *p_rotbk = vct_A;
  rot_spd = VisualData_P->rot_spd;
  v24 = rot_spd * 57.29578;
  v25 = -(f32)(rot_spd * 57.29578);
  if (v19 > -180.0)
    v22 = v19;
  if (v22 <= 180.0)
    v26 = v22;
  else
    v26 = 360.0 - v22;
  if (v26 <= 0.0)
    v27 = -(f32)(rot_spd * 57.29578);
  else
    v27 = rot_spd * 57.29578;
  if ((f32)(v26 / v27) == INFINITY)
    v28 = 0x80000000;
  else
    v28 = (f32)(v26 / v27);
  v30 = VisualData_P->rot_spd;
  if (v28 >= 0)
    LOWORD(v31) = v28;
  else
    v31 = -v28;
  wk->degcnt = v31;
  v32 = v26 * v30;
  if (v27 > 0.0)
  {
    if (v27 > v32)
      goto LABEL_32;
    goto LABEL_31;
  }
  if (v27 >= v32)
LABEL_31:
    v32 = v27;
LABEL_32:
  wk->deg = v32;
  if (v26 >= -120.0 && v26 <= 0.0 || v26 <= 120.0 && v26 >= 0.0)
    wk->degcnt = 0;
  if (v26 > 0.0)
  {
    if (v26 > v24)
      return Radian;
    goto LABEL_43;
  }
  if (v26 >= v25)
LABEL_43:
    wk->deg = v26;
  return Radian;
}

// 0x1fa4830
f32 sBtlGetJumpMoveSpeed(SBTLUNIT_WORK *wk) {
  s32 motionno;
  f32 PeakY;
  f32 result;
  f32 SpeedMove;

  if (!gJump->Use)
    return 0.0;
  motionno = wk->motionno;
  if (motionno == 90)
  {
LABEL_16:
    SpeedMove = gJump->SpeedMove;
    result = 8.0;
    goto LABEL_17;
  }
  if (motionno == 89)
  {
    PeakY = gJump->PeakY;
    if (PeakY > -90.0)
    {
      goto LABEL_16;
    }
    if (PeakY > -120.0)
    {
      SpeedMove = gJump->SpeedMove;
      result = 6.0;
      goto LABEL_17;
    }
    SpeedMove = gJump->SpeedMove;
    result = 3.0;
LABEL_17:
    if (SpeedMove > result)
      return result;
  }
  return gJump->SpeedMove;
}

// 0x1f984e0
f32 sBtlGetJumpY(SBTLUNIT_WORK *wk) {
  if (!gJump->Use)
    return 0.0;
  return gJump->Y;
}

// 0x1fa4a00
f32 sBtlGetJumpY_SkillSt(SBTLUNIT_WORK *wk) {
  if (!gJump->Use)
    return 0.0;
  return gJump->SkillStY;
}

// 0x1f78060
bool sBtlChkNowJump(SBTLUNIT_WORK *wk) {
  return gJump->Use;
}

// 0x1fa4ab0
bool sBtlChkNowJump_NotAtk(SBTLUNIT_WORK *wk) {
  if (wk->mode == 3)
    return 0;
  if (!gJump->Use)
    return 0;
  if (gJump->Y < 0.0)
    return 1;
  return 0;
}

// 0x1fa4c20
bool sBtlChkNowJump_OrAtk(SBTLUNIT_WORK *wk) {
  u32 v3;
  bool v4;
  s32 v5;

  if (wk->mode != 3)
  {
    if (!gJump->Use)
      return 0;
    return gJump->Y < 0.0;
  }
  v3 = sBtlGetPChara()->actwk->use_skillid - 1303;
  v4 = v3 > 0xE;
  v5 = (1 << v3) & 0x600F;
  if (v4 || v5 == 0)
    return 0;
  return gJump->Y < 0.0;
}

// 0x1fa4de0
bool sBtlChkNowJumpOver(SBTLUNIT_WORK *wk, f32 _OverY) {
  if (!sBtlChkNowJump_OrAtk(sBtlPlayer))
    return 0;
  if (gJump->Y < OverY)
    return 1;
  return 0;
}

// 0x1fa4eb0
bool sBtlChkNowJumpAfter(SBTLUNIT_WORK *wk) {
  return wk->JumpAfterCnt > 0;
}

// 0x1fa4ec0
bool sBtlChkReJump(SBTLUNIT_WORK *wk) {
  if (!sBtlChkNowJump_OrAtk(sBtlPlayer))
    return 0;
  if (gJump->ReJumpInput)
    return 1;
  return 0;
}

// 0x1f8f700
void sBtlResetJump(SBTLUNIT_WORK *wk) {
  P_JUMP_t *gJump_local;
  P_JUMP_t *v8;

  gJump_local = gJump;
  *(u16 *)&gJump_local->Use = 0;
  *(u64 *)&gJump_local->Step = 0;
  gJump_local->InputTime = 0.0;
  wk->hstatus &= 0xFFF3FFFF;
  sBtlPlayerResetCamJump();
  wk->JumpOfsPos.y = 0.0;
  v8 = gJump;
  v8->Y = 0.0;
  v8->ReJumpInput = 0;
}

// 0x1fa4f80
static s32 NormalProc_Kaihi(SBTLUNIT_WORK *wk, s32 flg, s32 keyflg) {
  s32 v5;
  SBATTLE_WORK *v11;

  v5 = flg;
  if (keyflg)
    return v5;
  if (!CheckKaihi(wk))
    return v5;
  if ((wk->vstatus & 0x80) != 0)
    return v5;
  v11 = wk;
  if (v11->battlemode == 1)
    return v5;
  v11 = wk;
  if (v11->bKaihi)
  {
    KaihiInit_Sub(wk, 0);
    v5 = 2;
  }
  wk->status &= ~0x100u;
  return v5;
}

// 0x1fa5160
static bool ReStart_Kaihi(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  _BOOL4 bKaihi;

  v5 = wk;
  bKaihi = v5->bKaihi;
  if (!v5->bKaihi)
    return bKaihi;
  KaihiInit_Sub(wk, 0);
  return bKaihi;
}

// 0x1f98a70
void sBtlKaihiInit(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *v5;

  v5 = wk;
  KaihiInit_Sub(v5, 0);
}

// 0x1fa5c90
static bool SetKaihiMawari(SBTLUNIT_WORK *wk, s32 _targetID, f32 _DirRange, f32 _KeyDir2) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v10;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v12;
  s32 devilid;
  u32 v14;
  f32 x;
  f32 z;
  f32 v17;
  f32 v18;
  f32 PosToDir;
  f32 AtoB_LR;
  f32 ABS;
  f32 hit_area_r;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  s32 status;
  SBATTLE_WORK *v35;
  f32 v36;
  SBTLACTAI_WORK *actaiwk;
  f32 v38;
  f32 y;
  f32 w;
  f32 v41;
  s64 ToZ;
  sdfVector4_t v44;

  ToZ = 0;
  UnitMng = wk->UnitMng;
  v10 = wk->actaiwk->targetID;
  v11 = sBtlSearchUnit_ID(UnitMng, v10);
  if (v11)
  {
    v12 = v11;
    devilid = v11->para->devilid;
    if ((u32)(devilid - 188) < 0x19)
      goto LABEL_56;
    v14 = devilid - 258;
    if (v14 < 0x3A && ((0x3E0000000000007uLL >> v14) & 1) != 0)
      goto LABEL_56;
    if (IsAction(5) || IsAction(6))
      goto LABEL_56;
    x = wk->pos.x;
    z = wk->pos.z;
    v17 = v12->pos.x;
    v18 = v12->pos.z;
    PosToDir = sBtlGetPosToDir(x, z, v17, v18);
    AtoB_LR = sBtlGetAtoB_LR(KeyDir2, PosToDir);
    ABS = sBtlGetABS(AtoB_LR);
    hit_area_r = v12->actaiwk->hit_area_r;
    if (ABS >= (f32)(DirRange + 8.0) || ABS < DirRange || hit_area_r <= 90.0)
    {
      if (ABS < DirRange || hit_area_r <= 120.0)
      {
        if (ABS >= DirRange)
        {
LABEL_56:
          LOBYTE(v11) = 0;
          return (char)v11;
        }
      }
      else
      {
        v26 = wk->pos.x;
        v27 = wk->pos.z;
        sBtlGetMoveXZ(v26, v27, KeyDir2, 70.0, (f32 *)&ToZ + 1, &ToZ);
        if (sBtlGetLenXZ(v12->pos.x, v12->pos.z, *((f32 *)&ToZ + 1), *(f32 *)&ToZ) >= (f32)(hit_area_r + 50.0))
          goto LABEL_56;
      }
    }
    v28 = wk->pos.x;
    v29 = wk->pos.z;
    v30 = v12->pos.x;
    v31 = v12->pos.z;
    if (sBtlGetLenXZ(v28, v29, v30, v31) >= (f32)((f32)(hit_area_r + 50.0) + 150.0))
      goto LABEL_56;
    LODWORD(v11) = sBtlMawariChk(wk, v12);
    wk->mawari_lr = (s32)v11;
    if ((u32)v11)
    {
      status = v12->actwk->status;
      if (status <= 21)
      {
        LOBYTE(v11) = 0;
        if ((u32)status > 0x15 || ((1 << status) & 0x2003CF) == 0)
          return (char)v11;
      }
      else if ((u32)status <= 0x21)
      {
        if (status != 23 && status != 33)
          goto LABEL_56;
      }
      else if ((status | 2) != 0x37)
      {
        goto LABEL_56;
      }
      sBtlSetAction(wk, 56, 0);
      sBtlSetMotion(wk, 94, 0, 0, 0);
      wk->JumpAfterCnt = 0;
      wk->mawari_pos_x = v12->pos.x;
      v35 = wk;
      v36 = v12->pos.z;
      v35->kochokuCnt = 26;
      v35->mode = 15;
      LODWORD(v35) = wk->flg;
      actaiwk = wk->actaiwk;
      wk->mawari_pos_z = v36;
      wk->flg = (u32)v35 | 0x800;
      actaiwk->targetID_Mawari = actaiwk->targetID;
      v38 = wk->pos.x;
      y = wk->pos.y;
      v41 = wk->pos.z;
      w = wk->pos.w;
      v44.x = v38;
      v44.y = y;
      v44.z = v41;
      v44.w = w;
      sBtlPlay3DSE(0x10070u, v44);
      LOBYTE(v11) = 1;
    }
  }
  return (char)v11;
}

// 0x1fa5290
static void KaihiInit_Sub(SBTLUNIT_WORK *wk, s32 mode) {
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 AnlogKey;
  f32 v18;
  f32 v19;
  f32 VecToDir;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 AtoB_LR;
  f32 v28;
  _BOOL4 v29;
  _BOOL4 v30;
  f32 Dir180;
  s32 v33;
  sdfVector4_t *p_rotbk;
  dds3ModelHandle_t *hModel;
  s32 MotionFrame;
  f32 turn_goal;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v49;
  sdfVector4_t *v51;
  f32 v52;
  s32 v54;
  s32 v57;
  SBATTLE_WORK *v58;
  sdfVector4_t v61;
  sdfVector4_t v62;

  *(u64 *)&v61.x = 0;
  *(u64 *)&v61.z = 0;
  sBtlResetCharge(wk, 1);
  sBtlResetJump(wk);
  ClearPosLink();
  wk->status &= ~0x100u;
  wk->hstatus &= ~0x20000u;
  wk->KaihiSetsuma = 0;
  gNext_bRaiSkill_RD = 0;
  *(u32 *)&gNext_bRR = 0;
  p_rot = &wk->rot;
  x = wk->rot.x;
  wk->cmstatus = 0;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v62.x = x;
  v62.y = y;
  v62.z = z;
  v62.w = w;
  RotToDir = sBtlGetRotToDir(v62);
  AnlogKey = GetAnlogKey(wk, &v61);
  v18 = v61.x;
  v19 = v61.z;
  VecToDir = sBtlGetVecToDir(v18, v19);
  v21 = wk->pos.z;
  v22 = wk->pos.x;
  v23 = wk->pos.y;
  v24 = 360.0 - mapGetScreenDir(v22, v23, v21, 0.0);
  if (v24 >= 360.0)
    v24 = 0.0;
  v25 = VecToDir + v24;
  if (v25 >= 360.0)
    v26 = v25 + -360.0;
  else
    v26 = v25;
  AtoB_LR = sBtlGetAtoB_LR(RotToDir, v26);
  v28 = sBtlGet360(RotToDir + AtoB_LR);
  if ((u32)(wk->next_motionID - 107) <= 2)
  {
    if (sBtlCheckMotionEnd(wk))
      goto LABEL_27;
    hModel = wk->hModel;
    MotionFrame = mdlGetMotionFrame(hModel);
    v29 = MotionFrame < 8;
    v30 = MotionFrame > 7;
    goto LABEL_29;
  }
LABEL_27:
  v29 = 0;
  v30 = 0;
LABEL_29:
  if (sbtlplayertblChkNG_TutoEtc(1, 0, 4158) || AnlogKey < 48.0 || wk->actaiwk->targetID == -1)
  {
    goto LABEL_54;
  }
  Dir180 = sBtlGetDir180(v28);
  wk->mv_rotbk = Dir180;
  FromEuler(0.0, Dir180 * 0.017453292, 0.0);
  goto LABEL_37;
LABEL_48:
  *p_rotbk = vct_A;
  if (SetKaihiMawari(wk, v33, 50.0, v26))
    return;
  goto LABEL_54;
LABEL_37:
  *p_rot = vct_A;
  p_rotbk = &wk->rotbk;
  goto LABEL_48;
LABEL_54:
  if (v29)
  {
    if (AnlogKey >= 48.0)
    {
      v45 = v28;
    }
    else
    {
      turn_goal = wk->turn_goal;
      v45 = turn_goal;
    }
    v49 = sBtlGetDir180(v45);
    wk->mv_rotbk = v49;
    FromEuler(0.0, v49 * 0.017453292, 0.0);
    *p_rot = vct_A;
    v51 = &wk->rotbk;
    goto LABEL_86;
    if (v54)
    {
      v51 = &wk->rotbk;
      goto LABEL_86;
    }
    else
    {
      v51 = &wk->rotbk;
LABEL_86:
      *v51 = vct_A;
      goto LABEL_88;
    }
    goto LABEL_86;
  }
  if (!v30)
  {
    if (!mode && (AnlogKey < 48.0 || AtoB_LR < -144.0 && AtoB_LR > 144.0))
      goto LABEL_103;
    v52 = sBtlGetDir180(v28);
    wk->mv_rotbk = v52;
    FromEuler(0.0, v52 * 0.017453292, 0.0);
    *p_rot = vct_A;
    wk->rotbk = vct_A;
LABEL_88:
    sBtlSetAction(wk, 1, 0);
    sBtlSetMotion(wk, 37, 0, 0, 0);
    v57 = 26;
    goto LABEL_92;
  }
  v46 = wk->turn_goal;
  v47 = sBtlGetDir180(v46);
  wk->mv_rotbk = v47;
  FromEuler(0.0, v47 * 0.017453292, 0.0);
  *p_rot = vct_A;
  wk->rotbk = vct_A;
LABEL_103:
  sBtlSetAction(wk, 1, 0);
  sBtlSetMotion(wk, 36, 0, 0, 0);
  v57 = 21;
LABEL_92:
  wk->kochokuCnt = v57;
  wk->JumpAfterCnt = 0;
  wk->flg |= 0x800u;
  v58 = wk;
  v58->mode = 14;
  v58->bHuumaCancel = 0;
  v58->ComboMotRetryCnt = 0;
  v58->ComboMotRetryUse = 0;
}

// 0x1f84f90
static s32 KaihiProc(SBTLUNIT_WORK *wk) {
  if (wk->motionID == 37)
  {
    KaihiProc_ZENTEN(wk);
    return 2;
  }
  KaihiProc_BACKSTEP(wk);
  return 2;
}

// 0x1fa61b0
static s32 KaihiProc_ZENTEN(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 AnlogKey;
  f32 v9;
  s32 kochokuCnt;
  SBATTLE_WORK *v12;
  f32 x;
  f32 y;
  f32 z;
  f32 v18;
  struct sdfVector4_t pos;
  f32 *p_x;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  SBATTLE_WORK *v27;
  s32 v29;
  s32 v30;
  _BOOL4 bRU_Assist;
  _BOOL4 bRR_Assist;
  SBATTLE_WORK *v41;
  SBATTLE_WORK *v42;
  SBATTLE_WORK *v43;
  SBATTLE_WORK *v45;
  SBATTLE_WORK *v51;
  SBATTLE_WORK *v57;
  SBATTLE_WORK *v58;
  SBATTLE_WORK *v59;
  u32 v62;
  s32 v63;
  SBTLUNIT_WORK *v64;
  s32 v65;
  SBATTLE_WORK *v67;
  SBATTLE_WORK *v71;
  s32 v72;
  struct sdfVector4_t v75;
  sdfVector4_t direction;
  sdfMatrix4_t v79;
  sdfMatrix4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v83;
  sdfVector4_t v84;

  *(u64 *)&direction.x = 0;
  *(u64 *)&direction.z = 0;
  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  if ((wk->flg & 0x800) == 0 || wk->motionno != 42)
    goto LABEL_24;
  if (!sBtlGetSpiritSkillChk(1386))
    goto LABEL_16;
  if (!sBtlGetSpiritSkillChk(1387))
    goto LABEL_16;
  if (MotionFrameF < 7.0)
    goto LABEL_24;
LABEL_23:
  wk->flg &= ~0x800u;
  goto LABEL_24;
LABEL_16:
  if (sBtlGetSpiritSkillChk(1386))
  {
LABEL_22:
    if (MotionFrameF < 6.0)
      goto LABEL_24;
    goto LABEL_23;
  }
  if (sBtlGetSpiritSkillChk(1387))
    goto LABEL_22;
  if (MotionFrameF >= 5.0)
    goto LABEL_23;
LABEL_24:
  AnlogKey = GetAnlogKey(wk, &direction);
  v9 = AnlogKey;
  kochokuCnt = wk->kochokuCnt;
  if (kochokuCnt <= 27)
  {
    if (kochokuCnt >= 1 && v9 > 48.0)
      goto LABEL_46;
  }
  goto LABEL_37;
LABEL_46:
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  v18 = mapGetScreenDir(x, y, z, 0.0) * -0.017453292;
  sub_1949280(0, v18);
  v75 = direction;
  vct_A = v75;
  get_transpose(&v80, &mtx_A, 0);
  v79 = v80;
  v81 = op_Multiply_60923920(&v79, vct_A, 0);
  vct_A = v81;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_A);
  pos = wk->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  v23 = p_x[4];
  v24 = p_x[5];
  v26 = p_x[6];
  v25 = p_x[7];
  v83.x = v23;
  v83.y = v24;
  v83.z = v26;
  v83.w = v25;
  sBtlGetRotate_Kaihi(wk, v83);
  v84.x = v23;
  v84.y = v24;
  v84.z = v26;
  v84.w = v25;
  sBtlCheckRotSpd(wk, v84);
LABEL_37:
  v12 = wk;
  if (v12->bSpiritSkill)
  {
    sBtlPlayerRSpiritInit(wk);
    return 2;
  }
  if (v12->kochokuCnt > 22)
  {
LABEL_73:
    goto LABEL_75;
  }
  if (!v12->bSetsuma)
    goto LABEL_73;
  v29 = sBtlInputChkSetsuma(wk);
  if (v29)
  {
    v30 = v29;
    sBtlSetFirstAtk(v30);
    return 2;
  }
LABEL_75:
  v27 = wk;
  if (v27->kochokuCnt > 30)
    goto LABEL_119;
  if (v27->bRaiSkill_RU)
  {
    gNext_bRaiSkill_RU = 1;
    goto LABEL_119;
  }
  v27 = wk;
  if (v27->bRaiSkill_RL)
  {
    gNext_bRaiSkill_RL = 1;
  }
  else
  {
    v27 = wk;
    if (v27->bRaiSkill_RD)
    {
      gNext_bRaiSkill_RD = 1;
    }
  }
LABEL_119:
  if (wk->kochokuCnt > 20)
    goto LABEL_143;
  if (gNext_bRaiSkill_RU)
  {
    if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[0], 0))
    {
      return 2;
    }
    goto LABEL_143;
  }
  if (gNext_bRaiSkill_RL)
  {
    if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[1], 1))
    {
      return 2;
    }
  }
  else
  {
    if (gNext_bRaiSkill_RD)
    {
      if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[2], 2))
      {
        return 2;
      }
    }
  }
LABEL_143:
  if (MotionFrameF < 17.0)
  {
    bRU_Assist = 0;
    bRR_Assist = 0;
    goto LABEL_154;
  }
  v41 = wk;
  if (v41->kochokuCnt > 0)
  {
    bRR_Assist = 0;
    goto LABEL_151;
  }
  v41 = wk;
  bRR_Assist = v41->bRR_Assist;
LABEL_151:
  v42 = wk;
  if (v42->kochokuCnt > 0)
  {
    bRU_Assist = 0;
    goto LABEL_154;
  }
  v42 = wk;
  bRU_Assist = v42->bRU_Assist;
LABEL_154:
  v43 = wk;
  if (v43->kochokuCnt <= 25)
  {
    v43 = wk;
    if (v43->bRR || bRR_Assist)
    {
      sBtlBS_LASTB1_Action_Req();
      gNext_bRR = 1;
    }
  }
  if (wk->kochokuCnt > 16)
  {
    goto LABEL_166;
  }
  if (gNext_bRR)
  {
    sBtlSetFirstAtk(1310);
    return 2;
  }
LABEL_166:
  v45 = wk;
  if (v45->kochokuCnt <= 20)
  {
    v45 = wk;
    if (v45->bGunMode)
    {
      sBtlResetAction(wk);
      if ((wk->vstatus & 0x8000) == 0)
      {
        sBtlStartGunMode(wk);
        return 2;
      }
      sBtlResetGunMode(wk, 1);
      return 2;
    }
  }
  v51 = wk;
  if (v51->kochokuCnt <= 26)
  {
    v51 = wk;
    if (bRU_Assist || v51->bComboSRU)
    {
      sBtlBS_LASTB1_Action_Req();
      gNext_bComboSRU = 1;
    }
  }
  if (wk->kochokuCnt <= 16)
  {
    if (gNext_bComboSRU)
    {
      if (sBtlDat()->m_type == 1)
      {
        sBtlSetFirstAtk(1323);
        return 2;
      }
      if (sBtlDat()->m_type == 2)
      {
        sBtlSetFirstAtk(1333);
        return 2;
      }
      if (sBtlDat()->m_type == 3)
      {
        sBtlSetFirstAtk(1339);
        return 2;
      }
    }
    else
    {
      if (wk->bComboLRU)
      {
        sBtlResetAction(wk);
        sBtlSetUseSkill(wk, 0, 0);
        sBtlSetAction(wk, 1, 0);
        return 2;
      }
    }
  }
  v57 = wk;
  if (v57->kochokuCnt <= 22)
  {
    v57 = wk;
    if (v57->bJump)
    {
      sBtlJumpStart(wk);
      return 2;
    }
  }
  v58 = wk;
  if (v58->kochokuCnt <= 8)
  {
    v58 = wk;
    if (v58->bGuard)
    {
      sBtlResetAction(wk);
      sBtlSetUseSkill(wk, 0, 0);
      return 2;
    }
  }
  v59 = wk;
  if (v59->kochokuCnt <= 5)
  {
    v59 = wk;
    if (v59->bKaihi)
    {
      sBtlKaihiInit(wk);
      return 2;
    }
  }
  if (wk->kochokuCnt > 4 || MotionFrameF < 17.0)
    goto LABEL_288;
  if (sBtlIsMoveBtn(sBtlPlayer))
  {
    sBtlResetAction(wk);
    if (MotionFrameF > 12.0)
    {
      if (!v62)
      v63 = 103;
      v64 = wk;
      v65 = 1;
      goto LABEL_313;
    }
    if (!v62)
    v63 = 135;
    v64 = wk;
LABEL_312:
    v65 = 0;
LABEL_313:
    sBtlSetMotion(v64, v63, v65, 0, 0);
    return 2;
  }
  v67 = wk;
  v67->bHuumaCancel = 1;
  if (IsSceanStop())
    goto LABEL_288;
  if (sBtlNormalProc_Huuma(wk, 0) != 2)
  {
LABEL_288:
    v71 = wk;
    v72 = v71->kochokuCnt;
    if (v72)
    {
      v71 = wk;
      v72 = v71->kochokuCnt;
      v71->kochokuCnt = v72 - 1;
    }
    if (wk->kochokuCnt)
    {
      goto LABEL_297;
    }
    wk->flg &= ~0x800u;
LABEL_297:
    if (!sBtlCheckMotionEnd(wk))
      return 2;
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    v64 = wk;
    v63 = 0;
    goto LABEL_312;
  }
  return 2;
}

// 0x1fa73a0
static s32 KaihiProc_BACKSTEP(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  SBATTLE_WORK *v8;
  SBATTLE_WORK *v11;
  s32 v13;
  s32 v14;
  _BOOL4 bRU_Assist;
  _BOOL4 bRR_Assist;
  SBATTLE_WORK *v25;
  SBATTLE_WORK *v26;
  SBATTLE_WORK *v27;
  SBATTLE_WORK *v29;
  SBATTLE_WORK *v35;
  SBATTLE_WORK *v40;
  SBATTLE_WORK *v41;
  SBATTLE_WORK *v42;
  SBATTLE_WORK *v47;
  SBATTLE_WORK *v51;
  s32 kochokuCnt;
  unsigned __int128 v55;

  v55 = 0u;
  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  if ((wk->flg & 0x800) == 0 || wk->motionno != 41)
    goto LABEL_24;
  if (!sBtlGetSpiritSkillChk(1386))
    goto LABEL_16;
  if (!sBtlGetSpiritSkillChk(1387))
    goto LABEL_16;
  if (MotionFrameF < 8.0)
    goto LABEL_24;
LABEL_23:
  wk->flg &= ~0x800u;
  goto LABEL_24;
LABEL_16:
  if (sBtlGetSpiritSkillChk(1386))
  {
LABEL_22:
    if (MotionFrameF < 7.0)
      goto LABEL_24;
    goto LABEL_23;
  }
  if (sBtlGetSpiritSkillChk(1387))
    goto LABEL_22;
  if (MotionFrameF >= 6.0)
    goto LABEL_23;
LABEL_24:
  GetAnlogKey(wk, &v55);
  v8 = wk;
  if (v8->bSpiritSkill)
  {
    sBtlPlayerRSpiritInit(wk);
    return 2;
  }
  if (v8->kochokuCnt > 13)
  {
LABEL_39:
    goto LABEL_41;
  }
  if (!v8->bSetsuma)
    goto LABEL_39;
  v13 = sBtlInputChkSetsuma(wk);
  if (v13)
  {
    v14 = v13;
    sBtlSetFirstAtk(v14);
    return 2;
  }
LABEL_41:
  v11 = wk;
  if (v11->kochokuCnt > 23)
    goto LABEL_72;
  if (v11->bRaiSkill_RU)
  {
    gNext_bRaiSkill_RU = 1;
    goto LABEL_72;
  }
  v11 = wk;
  if (v11->bRaiSkill_RL)
  {
    gNext_bRaiSkill_RL = 1;
  }
  else
  {
    v11 = wk;
    if (v11->bRaiSkill_RD)
    {
      gNext_bRaiSkill_RD = 1;
    }
  }
LABEL_72:
  if (wk->kochokuCnt > 13)
    goto LABEL_96;
  if (gNext_bRaiSkill_RU)
  {
    if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[0], 0))
    {
      return 2;
    }
    goto LABEL_96;
  }
  if (gNext_bRaiSkill_RL)
  {
    if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[1], 1))
    {
      return 2;
    }
  }
  else
  {
    if (gNext_bRaiSkill_RD)
    {
      if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[2], 2))
      {
        return 2;
      }
    }
  }
LABEL_96:
  if (MotionFrameF < 17.0)
  {
    bRU_Assist = 0;
    bRR_Assist = 0;
    goto LABEL_107;
  }
  v25 = wk;
  if (v25->kochokuCnt > 0)
  {
    bRR_Assist = 0;
    goto LABEL_104;
  }
  v25 = wk;
  bRR_Assist = v25->bRR_Assist;
LABEL_104:
  v26 = wk;
  if (v26->kochokuCnt > 0)
  {
    bRU_Assist = 0;
    goto LABEL_107;
  }
  v26 = wk;
  bRU_Assist = v26->bRU_Assist;
LABEL_107:
  v27 = wk;
  if (v27->kochokuCnt <= 21)
  {
    v27 = wk;
    if (v27->bRR || bRR_Assist)
    {
      sBtlBS_LASTB1_Action_Req();
      gNext_bRR = 1;
    }
  }
  if (wk->kochokuCnt > 13)
  {
    goto LABEL_120;
  }
  if (gNext_bRR)
  {
    sBtlSetFirstAtk(1310);
    return 2;
  }
LABEL_120:
  v29 = wk;
  if (v29->kochokuCnt <= 23)
  {
    v29 = wk;
    if (bRU_Assist || v29->bComboSRU)
    {
      sBtlBS_LASTB1_Action_Req();
      gNext_bComboSRU = 1;
    }
  }
  if (wk->kochokuCnt <= 13)
  {
    if (gNext_bComboSRU)
    {
      if (sBtlDat()->m_type == 1)
      {
        sBtlSetFirstAtk(1323);
        return 2;
      }
      if (sBtlDat()->m_type == 2)
      {
        sBtlSetFirstAtk(1333);
        return 2;
      }
      if (sBtlDat()->m_type == 3)
      {
        sBtlSetFirstAtk(1339);
        return 2;
      }
    }
    else
    {
      if (wk->bComboLRU)
      {
        sBtlResetAction(wk);
        sBtlSetUseSkill(wk, 0, 0);
        sBtlSetAction(wk, 1, 0);
        return 2;
      }
    }
  }
  v35 = wk;
  if (v35->kochokuCnt > 13)
    goto LABEL_187;
  v35 = wk;
  if (!v35->bGunMode)
    goto LABEL_187;
  sBtlResetAction(wk);
  if ((wk->vstatus & 0x8000) == 0)
  {
    sBtlStartGunMode(wk);
    return 2;
  }
  sBtlResetGunMode(wk, 1);
  return 2;
LABEL_187:
  v40 = wk;
  if (v40->kochokuCnt <= 18)
  {
    v40 = wk;
    if (v40->bJump)
    {
      sBtlJumpStart(wk);
      return 2;
    }
  }
  v41 = wk;
  if (v41->kochokuCnt <= 8)
  {
    v41 = wk;
    if (v41->bGuard)
    {
      sBtlResetAction(wk);
      sBtlSetUseSkill(wk, 0, 0);
      return 2;
    }
  }
  v42 = wk;
  if (v42->kochokuCnt <= 4)
  {
    v42 = wk;
    if (v42->bKaihi)
    {
      sBtlKaihiInit(wk);
      return 2;
    }
  }
  if (wk->kochokuCnt || MotionFrameF < 17.0)
    goto LABEL_241;
  if (sBtlIsMoveBtn(sBtlPlayer))
  {
    sBtlResetAction(wk);
LABEL_259:
    sBtlSetUseSkill(wk, 0, 0);
    sBtlSetMotion(wk, 0, 0, 0, 0);
    return 2;
  }
  v47 = wk;
  v47->bHuumaCancel = 1;
  if (IsSceanStop())
    goto LABEL_241;
  if (sBtlNormalProc_Huuma(wk, 0) != 2)
  {
LABEL_241:
    v51 = wk;
    kochokuCnt = v51->kochokuCnt;
    if (kochokuCnt)
    {
      v51 = wk;
      kochokuCnt = v51->kochokuCnt;
      v51->kochokuCnt = kochokuCnt - 1;
    }
    if (wk->kochokuCnt)
    {
      goto LABEL_250;
    }
    wk->flg &= ~0x800u;
LABEL_250:
    if (!sBtlCheckMotionEnd(wk))
      return 2;
    sBtlResetAction(wk);
    goto LABEL_259;
  }
  return 2;
}

// 0x1f85040
static s32 MawariProc(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  SBATTLE_WORK *v7;
  s32 v9;
  s32 v10;
  s32 v11;
  SBATTLE_WORK *v12;
  _BOOL4 bRU_Assist;
  _BOOL4 bRR_Assist;
  SBATTLE_WORK *v24;
  SBATTLE_WORK *v26;
  SBATTLE_WORK *v27;
  SBATTLE_WORK *v28;
  SBATTLE_WORK *v34;
  SBATTLE_WORK *v38;
  SBATTLE_WORK *v39;
  SBATTLE_WORK *v41;
  s32 kochokuCnt;
  SBATTLE_WORK *v47;

  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  if ((wk->flg & 0x800) == 0 || wk->motionno != 42)
    goto LABEL_24;
  if (!sBtlGetSpiritSkillChk(1386))
    goto LABEL_16;
  if (!sBtlGetSpiritSkillChk(1387))
    goto LABEL_16;
  if (MotionFrameF < 12.0)
    goto LABEL_24;
LABEL_23:
  wk->flg &= ~0x800u;
  goto LABEL_24;
LABEL_16:
  if (sBtlGetSpiritSkillChk(1386))
  {
LABEL_22:
    if (MotionFrameF < 11.0)
      goto LABEL_24;
    goto LABEL_23;
  }
  if (sBtlGetSpiritSkillChk(1387))
    goto LABEL_22;
  if (MotionFrameF >= 10.0)
    goto LABEL_23;
LABEL_24:
  v7 = wk;
  if (v7->bSpiritSkill)
  {
    sBtlPlayerRSpiritInit(wk);
    return 2;
  }
  if (v7->kochokuCnt > 12)
  {
LABEL_44:
    goto LABEL_46;
  }
  if (!v7->bSetsuma)
    goto LABEL_44;
  v9 = sBtlInputChkSetsuma(wk);
  if (v9)
  {
    v10 = v9;
    v11 = v10;
    goto LABEL_126;
  }
LABEL_46:
  v12 = wk;
  if (v12->kochokuCnt > 20)
    goto LABEL_70;
  if (v12->bRaiSkill_RU)
  {
    gNext_bRaiSkill_RU = 1;
    goto LABEL_70;
  }
  v12 = wk;
  if (v12->bRaiSkill_RL)
  {
    gNext_bRaiSkill_RL = 1;
  }
  else
  {
    v12 = wk;
    if (v12->bRaiSkill_RD)
    {
      gNext_bRaiSkill_RD = 1;
    }
  }
LABEL_70:
  if (wk->kochokuCnt > 10)
    goto LABEL_94;
  if (!gNext_bRaiSkill_RU)
  {
    if (gNext_bRaiSkill_RL)
    {
      if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[1], 1))
      {
        return 2;
      }
    }
    else
    {
      if (gNext_bRaiSkill_RD)
      {
        if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[2], 2))
        {
          return 2;
        }
      }
    }
    goto LABEL_94;
  }
  if (sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[0], 0))
  {
    return 2;
  }
LABEL_94:
  if (MotionFrameF < 17.0)
  {
    bRU_Assist = 0;
    bRR_Assist = 0;
    goto LABEL_97;
  }
  v27 = wk;
  if (v27->kochokuCnt > 0)
  {
    bRR_Assist = 0;
    goto LABEL_116;
  }
  v27 = wk;
  bRR_Assist = v27->bRR_Assist;
LABEL_116:
  v28 = wk;
  if (v28->kochokuCnt <= 0)
  {
    v28 = wk;
    bRU_Assist = v28->bRU_Assist;
  }
  else
  {
    bRU_Assist = 0;
  }
LABEL_97:
  v24 = wk;
  if (v24->kochokuCnt <= 20)
  {
    v24 = wk;
    if (v24->bRR || bRR_Assist)
    {
      sBtlBS_LASTB1_Action_Req();
      gNext_bRR = 1;
    }
  }
  if (wk->kochokuCnt > 10)
  {
    goto LABEL_109;
  }
  if (gNext_bRR)
  {
    v11 = 1310;
    goto LABEL_126;
  }
LABEL_109:
  v26 = wk;
  if (v26->kochokuCnt > 10)
    goto LABEL_146;
  v26 = wk;
  if (!v26->bGunMode)
    goto LABEL_146;
  sBtlResetAction(wk);
  if ((wk->vstatus & 0x8000) == 0)
  {
    sBtlStartGunMode(wk);
    return 2;
  }
  sBtlResetGunMode(wk, 1);
  return 2;
LABEL_146:
  v34 = wk;
  if (v34->kochokuCnt <= 20)
  {
    v34 = wk;
    if (bRU_Assist || v34->bComboSRU)
    {
      sBtlBS_LASTB1_Action_Req();
      gNext_bComboSRU = 1;
    }
  }
  if (wk->kochokuCnt > 10)
    goto LABEL_190;
  if (gNext_bComboSRU)
  {
    if (sBtlDat()->m_type == 1)
    {
      v11 = 1323;
    }
    else if (sBtlDat()->m_type == 2)
    {
      v11 = 1333;
    }
    else
    {
      if (sBtlDat()->m_type != 3)
      {
        goto LABEL_190;
      }
      v11 = 1339;
    }
LABEL_126:
    sBtlSetFirstAtk(v11);
    return 2;
  }
  if (!wk->bComboLRU)
  {
LABEL_190:
    v38 = wk;
    if (v38->kochokuCnt <= 18)
    {
      v38 = wk;
      if (v38->bJump)
      {
        sBtlJumpStart(wk);
        return 2;
      }
    }
    v39 = wk;
    if (v39->kochokuCnt <= 5)
    {
      v39 = wk;
      if (v39->bGuard)
      {
        sBtlResetAction(wk);
        sBtlSetUseSkill(wk, 0, 0);
        return 2;
      }
    }
    if (wk->kochokuCnt <= 5)
    {
      if (ReStart_Kaihi(wk))
        return 2;
    }
    if (!wk->kochokuCnt)
    {
      if (sBtlIsMoveBtn(sBtlPlayer))
      {
        sBtlResetAction(wk);
LABEL_241:
        sBtlSetUseSkill(wk, 0, 0);
        sBtlSetMotion(wk, 0, 0, 0, 0);
        return 2;
      }
      v47 = wk;
      v47->bHuumaCancel = 1;
      if (!IsSceanStop())
      {
        if (sBtlNormalProc_Huuma(wk, 0) == 2)
          return 2;
      }
    }
    v41 = wk;
    kochokuCnt = v41->kochokuCnt;
    if (kochokuCnt)
    {
      v41 = wk;
      kochokuCnt = v41->kochokuCnt;
      v41->kochokuCnt = kochokuCnt - 1;
    }
    if (!sBtlCheckMotionEnd(wk))
      return 2;
    sBtlResetAction(wk);
    goto LABEL_241;
  }
  sBtlResetAction(wk);
  sBtlSetUseSkill(wk, 0, 0);
  sBtlSetAction(wk, 1, 0);
  return 2;
}

// 0x1fa81c0
bool sBtlChkKaihiMawari(SBTLUNIT_WORK *wkEnemy) {
  s32 battlemode;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v9;

  battlemode = (u16)wk->battlemode;
  if (battlemode == 1)
    return 0;
  if (wk->battlemode == 3)
    return 0;
  if ((wkEnemy->side & 2) == 0)
    return 0;
  if (wkEnemy->actwk->no_homing)
    return 1;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v9 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (wk->mode != 15 || wkEnemy->ListID != v9->actaiwk->targetID_Mawari)
  {
    return 0;
  }
  wkEnemy->actwk->no_homing = 1;
  return 1;
}

// 0x1f78eb0
bool sBtlSummonKey(SBTLUNIT_WORK *wk) {
  bool result;
  SBATTLE_WORK *v9;
  u32 NotCnt_R1R2;
  sdatUnitWork_t *para;
  SBATTLE_WORK *v20;
  void *Instance;
  s32 v25;
  s32 v26;
  _BOOL4 v28;
  void *v29;
  void *v30;
  s32 v31;
  void *v32;
  void *v33;
  SBATTLE_WORK *v36;
  s32 mode;
  u32 status4;
  void *v39;
  void *v40;
  s32 v44;
  bool v46;

  if (!wk)
    return 0;
  if (!wk->para || !wk->actaiwk)
    return 0;
  if ((wk->status2 & 0x20000000) != 0)
    return 0;
  if (!!IsSceanStop())
  {
    if (!get_Instance(0)->sc_pause)
      return 0;
  }
  if (!!IsSceanStop())
  {
    if ((wk->status4 & 0x1000000) != 0)
      return 0;
  }
  if (sBtlPlayer_R1R2NoInput >= 1)
  {
    sBtlPlayer_R1R2NoInput = sBtlPlayer_R1R2NoInput - 1;
  }
  v9 = wk;
  if (!v9->sklProc->bRun)
  {
    v9 = wk;
    NotCnt_R1R2 = v9->NotCnt_R1R2;
    if (NotCnt_R1R2)
    {
      v9 = wk;
      NotCnt_R1R2 = v9->NotCnt_R1R2;
      v9->NotCnt_R1R2 = NotCnt_R1R2 - 1;
    }
  }
  para = wk->para;
  sBtlGetBadStatus(wk->para);
  if (wk->mode == 12)
    return 0;
  if ((wk->actaiwk->status & 0x4000) != 0)
    return 0;
  if (sBtlChkNowJump(sBtlPlayer))
    return 0;
  if (sBtlCheckIsMenuNg(wk))
    return 0;
  if (sBtlCheckMove_BadStatus(wk))
  {
    if (!CheckMoveAction(wk))
      return 0;
  }
  v20 = wk;
  if (v20->sklProc->bRun)
    return 0;
  v20 = wk;
  if (v20->kaiwaflg || (wk->status & 0x100) != 0)
    return 0;
  if (!sBtlIsBattleKey(4160, 1) || get_Instance(0)->sc_pause == 2)
  {
    if (wk->battlemode != 3)
    {
      Instance = get_Instance(0);
      AllDisp(Instance, 1, 0, 0);
    }
    goto LABEL_73;
  }
  v29 = get_Instance(0);
  if (!IsActionUIDispOut(v29, 0))
  {
    if ((wk->vstatus & 0x8000) != 0)
      goto LABEL_73;
    v32 = get_Instance(0);
    AllDisp(v32, 1, 1, 0);
    if (get_Instance(0)->sc_pause)
      goto LABEL_73;
    goto LABEL_98;
  }
  v30 = get_Instance(0);
  if (IsNCutIn(v30, 0) && (wk->vstatus & 0x8000) == 0 && !get_Instance(0)->sc_pause)
  {
LABEL_98:
    v33 = get_Instance(0);
    if (!ShortCutPause(v33, 0))
      goto LABEL_73;
    return 0;
  }
LABEL_73:
  if (sBtlIsBattleKey(4175, 2))
  {
    v25 = 0;
    v26 = 5;
  }
  else
  {
    if (sBtlIsBattleKey(4176, 2))
    {
      v28 = evtBitCheck(2093);
      v25 = !v28;
      if (v28)
        v26 = 7;
      else
        v26 = 0;
    }
    else
    {
      if (sBtlIsBattleKey(4174, 2))
      {
        v31 = sBtlCheckSummonUnit();
        v25 = v31 == 1;
        v26 = 2 * (v31 != 1);
      }
      else
      {
        v26 = 0;
        v25 = 1;
      }
    }
  }
  if (!sBtlIsBattleKey(4145, 2) && ((v25 ^ 1) & 1) == 0)
    return 0;
  if (sBtlPlayer_R1R2NoInput)
    return 0;
  v36 = wk;
  if (v36->NotCnt_R1R2)
    return 0;
  v36 = wk;
  mode = v36->mode;
  if (mode == 5)
    return 0;
  v36 = wk;
  mode = v36->mode;
  if (!mode)
    return 0;
  v36 = wk;
  mode = v36->mode;
  if (mode == 6)
    return 0;
  v36 = wk;
  mode = v36->mode;
  if (mode == 13)
    return 0;
  v36 = wk;
  if ((v36->status & 0x40000000) != 0)
    return 0;
  v36 = wk;
  if (v36->cmbSkl->bRun)
    return 0;
  v36 = wk;
  if (v36->pCamSklUser)
    return 0;
  v36 = wk;
  status4 = v36->status4;
  if ((status4 & 0x1000) != 0)
    return 0;
  status4 = wk->status4;
  if ((status4 & 0x20000) != 0)
    return 0;
  v39 = get_Instance(0);
  if (MenuMoveChack(v39, 0))
    return 0;
  v40 = get_Instance(0);
  BattleDispUIOn(v40, 0);
  sBtlPlayer_R1R2NoInput = 4;
  if ((v25 & 1) != 0)
  {
    v44 = 0;
LABEL_149:
    SetSummonMenu(v44);
    wk->vstatus |= 0x8000000u;
    sBtlSetNSTOP();
    return 1;
  }
  sBtlSetMenuItemList();
  v46 = sBtlShortCutStart(v26, 0);
  result = 0;
  if (v46)
  {
    v44 = 1;
    goto LABEL_149;
  }
  return result;
}

// 0x1fa8ab0
static bool IsPlanMenuOpen(s32 index) {
  s8 v2;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;

  v2 = index;
  Nakama = sBtlGetNakama(v2);
  if (!Nakama)
    return 0;
  v4 = Nakama;
  if (!CheckLiveTarget(Nakama))
    return 0;
  if (sBtlCheckReturn_Unit(v4))
    return 0;
  return 1;
}

// 0x1f88d00
bool sBtlSetSummonFunc(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  SBTLPNL_SETDATA *data;
  SBTLUNIT_WORK *v7;
  SBTLAI_WORK *aiwk;
  s64 k;
  SBATTLE_WORK *v13;
  SBTLUNIT_LISTWORK *v14;
  SBTLUNIT_WORK *v15;
  bool v16;
  s32 ctrlSmnIdx;
  s32 v24;
  s32 v25;
  s64 v26;
  SBTLPNL_SETDATA *v27;
  SBTLUNIT_WORK *v28;
  s32 skillid;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLPNL_SETDATA *v32;
  SBTLACTION_WORK *v33;
  SBATTLE_WORK *v35;
  s32 sklid;
  s32 itemid;
  SBATTLE_WORK *v39;
  SBATTLE_WORK *v43;
  u32 v44;
  u32 v45;
  SBATTLE_WORK *v50;
  s64 ii;
  SBTLUNIT_LISTWORK *v52;
  SBTLUNIT_WORK *v53;
  s16 target_p;
  s32 v56;
  SBTLACTION_WORK *v57;
  SBATTLE_WORK *v58;
  s16 *v60;
  void *Instance;
  s64 n;
  SBTLUNIT_LISTWORK *v64;
  SBTLUNIT_WORK *v65;
  SBTLPNL_SETDATA *v66;
  SBATTLE_WORK *v67;
  s64 v68;
  SBATTLE_WORK *v69;
  s32 v70;
  SBATTLE_WORK *v72;
  SBATTLE_WORK *v74;
  s16 *summonindex;
  s16 v76;
  SBATTLE_WORK *v77;
  s64 v79;
  SBTLUNIT_LISTWORK *UnitMng;
  RED_GUAGE *v81;
  s32 v82;
  SBTLUNIT_WORK *v83;
  SBATTLE_WORK *v84;
  SBTLUNIT_WORK *Nakama;
  s64 v87;
  SBATTLE_WORK *v88;
  SBTLUNIT_LISTWORK *v89;
  s32 v90;
  SBTLUNIT_WORK *v91;
  u32 status;
  SBATTLE_WORK *v94;
  s64 i;
  SBATTLE_WORK *v97;
  SBTLUNIT_LISTWORK *v98;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *v102;
  s64 m;
  SBTLUNIT_LISTWORK *v109;
  SBTLUNIT_WORK *v110;
  s32 v112;
  char **v113;
  SBTLACTION_WORK *actwk;
  s32 v116;
  s32 v117;
  f32 v118;
  f32 v119;
  f32 v120;
  f32 v121;
  f32 v122;
  f32 v123;
  long f64 v124;
  f32 v125;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  s64 j;
  SBATTLE_WORK *v133;
  SBTLUNIT_LISTWORK *v134;
  SBTLUNIT_WORK *v135;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  long f64 v140;
  f32 v142;
  f32 v145;
  s64 v146;
  s32 v147;
  SBATTLE_WORK *v148;
  s64 SummonIdx;
  s32 SummonDevilID;
  s64 v151;
  s64 v152;
  sdfVector4_t v153;
  sdfVector4_t v154;

  v151 = 0;
  v152 = 0;
  v5 = wk;
  data = v5->panelwk->data;
  switch (data[0]->select_no)
  {
    case 1:
      ctrlSmnIdx = v5->ctrlSmnIdx;
      if (sBtlCheckSummonUnit_Exist(ctrlSmnIdx) == 2)
      {
        v24 = 1;
        v25 = 3;
        goto LABEL_141;
      }
      if (!sBtlSetReturn(wk, 1))
        goto LABEL_144;
      v24 = 2;
      v25 = 4;
LABEL_141:
      v66 = data[0];
      v67 = wk;
      v68 = v67->ctrlSmnIdx;
      v67->summonindex[v68] = v66->target_p;
      v67->summonindex_menu[v68] = v66->target_p;
      v69 = wk;
      if (v69->summonflg[v69->summonindex[v69->ctrlSmnIdx]] == 2)
      {
LABEL_144:
        v16 = 0;
        goto LABEL_29;
      }
      if (!wk)
        goto LABEL_300;
      v69 = wk;
      if (v69->bBfrBtlEnd)
      {
LABEL_300:
        v70 = wk->summonindex[wk->ctrlSmnIdx];
        v153.x = 0.0;
        v153.y = 0.0;
        v153.z = 0.0;
        v153.w = 0.0;
        sBtlSetSummon_Unit(wk, v70, 0, 0, v153, 0, 1);
        v72 = wk;
        SummonIdx = v72->ctrlSmnIdx;
        SummonDevilID = v72->stock_id[v72->summonindex[SummonIdx]];
LABEL_162:
        v74 = wk;
        summonindex = wk->summonindex;
        v76 = summonindex[v74->ctrlSmnIdx];
        v77 = v74;
        v77 = wk;
        summonindex = v77->summonindex;
        v74->stock_mask |= 1 << v76;
        v79 = v77->ctrlSmnIdx;
        UnitMng = v77->UnitMng;
        v81 = v77->aRedGuage[(s32)v79 + 1];
        v82 = v77->summonID[summonindex[v79]];
        v83 = sBtlSearchUnit_ID(UnitMng, v82);
        sBtlInitRedGg(v81, v83->para->now->hp);
        sBtlSetDevilSkillID(wk->stock_id[wk->summonindex[wk->ctrlSmnIdx]], 0);
        v84 = wk;
        v84->talkwk->mode = 1;
        v84->tgt_ListID[v84->summonindex[v84->ctrlSmnIdx]] = -1;
        Nakama = sBtlGetNakama(v84->ctrlSmnIdx);
        if (Nakama)
        {
          Nakama->status |= 0x40000u;
          v87 = 0;
          wk->status |= 0x4000u;
          while (1)
          {
            v88 = wk;
            if (v87 >= v88->stock_num)
              break;
            v88 = wk;
            v89 = v88->UnitMng;
            v90 = v88->summonID[v87];
            v91 = sBtlSearchUnit_ID(v89, v90);
            if (v91)
            {
              if (Nakama->ListID != v91->ListID)
              {
                status = v91->status;
                if ((status & 0x40000) != 0)
                  v91->status = status & 0xFFFBFFFF;
              }
            }
            ++v87;
          }
        }
        wk->status2 &= ~2u;
        effStopEffectStop();
        v94 = wk;
        v94->status &= ~0x8000000u;
        v94->scrFlag |= 0x20000000u;
        for (i = 0; ; ++i)
        {
          v97 = wk;
          v98 = v97->UnitMng;
          if (i >= v98->number)
            break;
          v98 = wk->UnitMng;
          pUnit = v98->pUnitL[i]->pUnit;
          if (pUnit && pUnit->hModel)
            pUnit->vstatus &= ~0x8000000u;
        }
        *(u32 *)v97->sgstat = 0;
        v97->menutype = 0;
        sBtlResetMidashiAnim(0);
        SummonInit(wk, v24, SummonIdx, SummonDevilID);
        goto LABEL_28;
      }
      v69 = wk;
      v117 = v69->ctrlSmnIdx;
      if (v117 == 1)
      {
        x = wk->pos.x;
        y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        *(__n128 *)&v140 = sub_1B332C0(0, x, y, z, w);
        sub_1B335A0(&v151, 0, v140);
        v125 = *(f32 *)&v152;
        v119 = *(f32 *)&v151 + 200.0;
      }
      else
      {
        v118 = 0.0;
        v119 = 0.0;
        if (v117)
        {
LABEL_289:
          v119 = *(f32 *)&v151;
          v118 = *(f32 *)&v152;
          v142 = *((f32 *)&v151 + 1);
          nakama_pos.z = v118;
          nakama_pos.w = 1.0;
          nakama_pos.x = v119;
          nakama_pos.y = v142;
          v142 = *((f32 *)&v151 + 1);
          v145 = *(f32 *)&v151;
          v146 = v152;
          v147 = wk->summonindex[wk->ctrlSmnIdx];
          v154.x = v145;
          v154.y = v142;
          *(u64 *)&v154.z = v146;
          sBtlSetSummon_Unit(wk, v147, 0, 1, v154, 2, 0);
          v148 = wk;
          SummonDevilID = v148->stock_id[v148->summonindex[v148->ctrlSmnIdx]];
          LODWORD(SummonIdx) = v148->ctrlSmnIdx;
          v24 = v25;
          goto LABEL_162;
        }
        v120 = wk->pos.x;
        v121 = wk->pos.y;
        v123 = wk->pos.z;
        v122 = wk->pos.w;
        *(__n128 *)&v124 = sub_1B332C0(0, v120, v121, v123, v122);
        sub_1B335A0(&v151, 0, v124);
        v125 = *(f32 *)&v152;
        v119 = *(f32 *)&v151 + -200.0;
      }
      v118 = v125 + 200.0;
      *(f32 *)&v151 = v119;
      *(f32 *)&v152 = v125 + 200.0;
      goto LABEL_289;
    case 2:
      v5 = wk;
      v26 = v5->ctrlSmnIdx;
      v27 = data[v26];
      v28 = sBtlGetNakama(v26);
      skillid = v27->skillid;
      v28->actwk->order_skillid = skillid;
      v28->aiwk->meirei_nobk = v27->select_no;
      Skilltbl = sBtlGetSkilltbl(skillid);
      v28->aiwk->status |= 9u;
      v28->actaiwk->status = v28->actaiwk->status & 0xFFFFFF9F | 0x40;
      v28->actcounter = v28->actcounter_max;
      sBtlResetColorFlag();
      v32 = data[0];
      if ((Skilltbl->area & 0x4000) != 0)
      {
        target_p = v32->target_p;
        if (!target_p)
        {
          actwk = v28->actwk;
          v33 = v28->actwk;
          actwk->order_targetID = wk->playerID;
          goto LABEL_250;
        }
        target_p = data[0]->target_p;
        v56 = target_p - 1;
        v57 = v28->actwk;
        v33 = v57;
        v58 = wk;
        v60 = v58->summonindex;
        if (v56 == v60[0])
        {
          v33 = v28->actwk;
          v58 = wk;
          v60 = v58->summonindex;
          v57->order_targetID = v58->summonID[v60[v58->ctrlSmnIdx]];
          goto LABEL_250;
        }
        v33 = v28->actwk;
        v58 = wk;
        v57->order_targetID = v58->playerID;
        v116 = v27->target_p - 1;
      }
      else
      {
        v33 = v28->actwk;
        if (v32->targetid != -1)
        {
          v33->order_targetID = v27->targetid;
LABEL_250:
          v116 = -1;
          goto LABEL_251;
        }
        v102 = v28->actwk;
        v33->order_targetID = wk->playerID;
        v33 = v102;
        v116 = v27->target_p - 1;
      }
LABEL_251:
      v33->order_stockID = v116;
      sBtlResetAAI(v28);
      sBtlSetAIWkStat(v28, 1);
      v28->actcounter = v28->actcounter_max;
      hitList = wk->hitList;
      sBtlClearHitC(hitList, v28);
      effList = wk->effList;
      sBtlForceReset(effList, v28);
      sBtlForceDelete_SkillFlag_Acter(v28, 0x400u);
      wk->status2 &= ~2u;
      RestartBattle();
      sBtlRestart_Scene();
LABEL_267:
      wk->mode = wk->modebk;
      wk->vstatus &= ~0x8000000u;
      for (j = 0; ; ++j)
      {
        v133 = wk;
        v134 = v133->UnitMng;
        if (j >= v134->number)
        {
          *(u32 *)v133->sgstat = 0;
          v133->menutype = 0;
          sBtlResetMidashiAnim(0);
          goto LABEL_28;
        }
        v135 = v134->pUnitL[j]->pUnit;
        if (!v135)
          continue;
        if (v135->hModel)
          v135->vstatus &= ~0x8000000u;
      }
      goto LABEL_267;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      v5 = wk;
      v7 = sBtlGetNakama(v5->ctrlSmnIdx);
      aiwk = v7->aiwk;
      aiwk->status &= 0xFFFFFFF6;
      aiwk->meirei_nobk = data[0]->select_no;
      v7->actaiwk->status = v7->actaiwk->status & 0xFFFFFF9F | 0x40;
      wk->status2 &= ~2u;
      RestartBattle();
      sBtlRestart_Scene();
      goto LABEL_13;
LABEL_14:
      wk->mode = wk->modebk;
      wk->vstatus &= ~0x8000000u;
      for (k = 0; ; ++k)
      {
        v13 = wk;
        v14 = v13->UnitMng;
        if (k >= v14->number)
        {
          *(u32 *)v13->sgstat = 0;
          sBtlResetMidashiAnim(0);
          wk->menutype = 0;
          goto LABEL_28;
        }
        v15 = v14->pUnitL[k]->pUnit;
        if (!v15)
          continue;
        if (v15->hModel)
          v15->vstatus &= ~0x8000000u;
      }
LABEL_13:
      goto LABEL_14;
    case 8:
      v16 = 0;
      if (!sBtlSetReturn(wk, 0))
        goto LABEL_29;
      v35 = wk;
      v35->gunskillid = 0;
      v35->talkwk->mode = 0;
      *(u32 *)v35->sgstat = 0;
      v35->menutype = 0;
      sBtlResetMidashiAnim(0);
      wk->status2 &= ~2u;
      RestartBattle();
      sBtlRestart_Scene();
      sBtlResetAction(wk);
      for (m = 0; ; ++m)
      {
        v109 = wk->UnitMng;
        if (m >= v109->number)
          break;
        v109 = wk->UnitMng;
        v110 = v109->pUnitL[m]->pUnit;
        if (v110 && v110->hModel)
          v110->vstatus &= ~0x8000000u;
      }
      wk->motion_UseWait2 = 1;
      sBtlSetMotion(wk, 130, 0, 0, 0);
      wk->actwk->status = 1;
      v112 = sub_1905740(2, 0);
      if (v112 == 1)
      {
        v113 = &"PVA01A_40B_002";
      }
      else
      {
        v16 = 0;
        if (v112)
          goto LABEL_29;
        v113 = &"PVA01A_40B_001";
      }
      sndVoicePlayFile(*v113, 0);
      v16 = 0;
LABEL_29:
      if (data[0]->select_no != 9)
      {
        sBtlResetColor_PNL(0x80808080);
        return v16;
      }
      return v16;
    case 9:
      v5 = wk;
      v16 = 0;
      v5->mode = 6;
      *(u32 *)v5->gstat = 0;
      if (v5->battlemode != 3)
      {
        sBtlResetATKEffect();
        v16 = 0;
      }
      goto LABEL_29;
    case 0xA:
      v5 = wk;
      sklid = sBtlGetItemtbl(v5->equipbullet)->sklid;
      sBtlForceDelete_EffectWork_ID(sklid, 1);
      v16 = 0;
      itemid = data[0]->itemid;
      v39 = wk;
      v39->equipbullet = itemid;
      v39->equipbulletbk = itemid;
      v39->mode = 13;
      goto LABEL_29;
    case 0xB:
      v5 = wk;
      v5->status2 &= ~2u;
      RestartBattle();
      sBtlRestart_Scene();
      v43 = wk;
      v43->mode = v43->modebk;
      *(u32 *)v43->gstat = 0;
      v44 = v43->status;
      if ((v44 & 0x400000) != 0)
      {
        if (!v45)
        {
          v43 = wk;
          v44 = v43->status;
        }
        v43->status = v44 & 0xFFBFFFFF;
        Instance = get_Instance(0);
        EscapeGaugeOnOff(Instance, 0, 0, 0);
        wk->vstatus &= ~0x8000000u;
        goto LABEL_120;
      }
      else
      {
        if (!v45)
        {
          v43 = wk;
          v44 = v43->status;
        }
        v43->escape_stat = 0;
        v43->status = v44 | 0x400000;
        wk->vstatus &= ~0x8000000u;
        goto LABEL_120;
      }
LABEL_120:
      for (n = 0; ; ++n)
      {
        v64 = wk->UnitMng;
        if (n >= v64->number)
          goto LABEL_28;
        v65 = v64->pUnitL[n]->pUnit;
        if (!v65)
          continue;
        if (v65->hModel)
          v65->vstatus &= ~0x8000000u;
      }
    case 0xC:
      v5 = wk;
      v5->status2 &= ~2u;
      RestartBattle();
      sBtlRestart_Scene();
      goto LABEL_93;
LABEL_94:
      v50 = wk;
      v50->mode = v50->modebk;
      *(u32 *)v50->gstat = 0;
      wk->vstatus &= ~0x8000000u;
      for (ii = 0; ; ++ii)
      {
        v52 = wk->UnitMng;
        if (ii >= v52->number)
        {
LABEL_28:
          v16 = 1;
          goto LABEL_29;
        }
        v53 = v52->pUnitL[ii]->pUnit;
        if (!v53)
          continue;
        if (v53->hModel)
          v53->vstatus &= ~0x8000000u;
      }
LABEL_93:
      goto LABEL_94;
    default:
      goto LABEL_144;
  }
}

// 0x1f7dd60
static s32 UseItemProc(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBTLPNL_SETDATA *data;
  s32 v6;
  SBTLPNL_SETDATA *v7;
  SBATTLE_WORK *v9;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_WORK *v14;
  s32 v15;
  SBATTLE_WORK *v19;
  s16 *gstat;
  s32 target_p;
  u32 stock_mask;
  SBATTLE_WORK *v26;
  SBTLUNIT_LISTWORK *v27;
  s32 v28;
  SBTLUNIT_WORK *v29;
  SBTLUNIT_WORK *v30;
  SBTLACTAI_WORK *actaiwk;
  s32 useitembk;
  s32 itemid;
  SBTLITEM_TBL *Itemtbl;
  s32 sklid;
  s32 v40;
  s32 v41;
  SBTLITEM_TBL *v42;
  SBTLSKILLP_TBL *Skilltbl;
  s16 v44;
  u32 v46;
  s64 v48;
  SBATTLE_WORK *v49;
  SBTLUNIT_LISTWORK *v50;
  s32 v51;
  SBTLUNIT_WORK *v52;
  SBTLACTAI_WORK *v55;
  SBTLACTION_WORK *v56;
  s16 *v59;
  SBTLITEM_TBL *v60;
  SBTLSKILLP_TBL *v61;
  SBTLSKILLP_TBL *v62;
  SBATTLE_WORK *v64;
  _BOOL8 v67;
  SBTLSM_LISTWORK *sysmsgList;
  SBATTLE_WORK *v71;
  s64 v72;
  SBATTLE_WORK *v74;
  u32 flg2;
  s32 para2;
  s32 v78;
  s32 v81;
  s8 v82;
  s32 v84;
  SBATTLE_WORK *v88;
  s64 i;
  SBATTLE_WORK *v94;
  SBTLUNIT_LISTWORK *v95;
  SBTLUNIT_WORK *pUnit;
  s64 v97;
  u64 v100;
  SBTLUNIT_WORK *v102;
  f32 per;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 Radian;
  f32 v112;
  f32 v113;
  u32 v116;
  s64 v117;
  f32 v119;
  f32 v120;
  f32 v121;
  f32 v123;
  f32 v124;
  f32 torimochi_spd_local;
  f32 v127;
  f32 v128;
  f32 v129;
  s32 v132;
  bool v133;
  SBATTLE_WORK *v135;
  s16 *v137;
  u32 v138;
  s32 v142;
  s16 v143;
  s16 v145;
  s16 *v146;
  SBATTLE_WORK *v147;
  SBTLACTAI_WORK *v148;
  SBATTLE_WORK *v151;
  SBTLACTAI_WORK *v155;
  s32 v157;
  s8 v158;
  s32 v160;
  SBTLACTION_WORK *actwk;
  s32 v164;
  SBTLACTAI_WORK *v167;
  SBTLACTAI_WORK *v170;
  f32 v171;
  f32 v172;
  f32 v175;
  f32 v176;
  f32 v177;
  SBATTLE_WORK *v182;
  SBTLUNIT_WORK *v183;
  s64 v184;
  s64 v185;
  s32 v188;
  s32 v193;
  s32 ListID;
  SBTLITEM_TBL *v196;
  s32 v197;
  f32 v201;
  f32 v202;
  f32 v203;
  f32 v204;
  f32 v205;
  f32 v206;
  f32 v207;
  f32 v208;
  f32 v209;
  sdfVector4_t v210;
  sdfVector4_t v211;
  sdfVector4_t v212;
  sdfVector4_t v213;
  sdfVector4_t rot;
  sdfVector4_t v215;

  v4 = wk;
  data = v4->panelwk->data;
  v6 = v4->gstat[1];
  v7 = data[0];
  if (v6 < 0)
    goto LABEL_31;
  if ((s16)v6 > 4)
    goto LABEL_31;
  sBtlResetColor_Select();
  sBtlSetColor_Select(wk, 0x80808080);
  v9 = wk;
  if (v9->gstat[1] < 1)
    goto LABEL_31;
  targetID = wk->actaiwk->targetID;
  if (targetID == -1)
    goto LABEL_31;
  UnitMng = v9->UnitMng;
  v13 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v13)
    goto LABEL_31;
  v14 = v13;
  if (v13->hModel)
  {
    v15 = v13->side & 0x81;
    if (v15 == 1)
    {
      if (!CheckLiveTarget(v14))
        goto LABEL_31;
    }
    sBtlSetColor_Select(v14, 0x80808080);
  }
LABEL_31:
  v19 = wk;
  gstat = v19->gstat;
  switch (gstat[1])
  {
    case 0:
      gBk_targetID_Use = 0;
      target_p = (u16)v7->target_p;
      gBk_targetID = -1;
      if (target_p)
      {
        stock_mask = wk->stock_mask;
        if (((stock_mask >> (target_p - 1)) & 1) != 0)
        {
          v26 = wk;
          v27 = v26->UnitMng;
          v28 = *((u32 *)&v26->summonID->max_length + v7->target_p + 1);
          v29 = sBtlSearchUnit_ID(v27, v28);
          if (v29)
          {
            v30 = v29;
            if (sBtlCheckDamageTargetUseItem(v30))
            {
              if (gBk_targetID_Use)
              {
                actaiwk = wk->actaiwk;
              }
              else
              {
                gBk_targetID_Use = 1;
                actaiwk = wk->actaiwk;
                gBk_targetID = actaiwk->targetID;
              }
              actaiwk->targetID = v30->ListID;
              wk->useitem_stock = -1;
              wk->actwk->order_stockID = -1;
              goto LABEL_224;
            }
            wk->actaiwk->targetID = v30->ListID;
          }
          goto LABEL_313;
        }
        if (gBk_targetID_Use)
        {
          v167 = wk->actaiwk;
        }
        else
        {
          gBk_targetID_Use = 1;
          v167 = wk->actaiwk;
          gBk_targetID = v167->targetID;
        }
        v167->targetID = -1;
LABEL_313:
        v193 = v7->target_p - 1;
        wk->useitem_stock = v193;
        wk->actwk->order_stockID = v193;
        goto LABEL_224;
      }
      {
        v148 = wk->actaiwk;
        gBk_targetID_Use = 1;
        gBk_targetID = v148->targetID;
      }
      else
      {
        v148 = wk->actaiwk;
      }
      v148->targetID = wk->playerID;
      wk->actwk->order_stockID = -1;
      goto LABEL_224;
    case 1:
      useitembk = v19->useitembk;
      if (!sBtlForceDelete_EffectWork_ID(useitembk, 1))
        return 2;
LABEL_222:
LABEL_224:
      goto LABEL_225;
    case 2:
      if (!sBtlCheckUnit_Exec_R())
        return 2;
      itemid = v7->itemid;
      wk->useitemID = itemid;
      Itemtbl = sBtlGetItemtbl(itemid);
      sklid = Itemtbl->sklid;
      wk->useitembk = sklid;
      if ((sBtlGetSkilltbl(sklid)->attr & 0x800) == 0)
      {
        v40 = Itemtbl->sklid;
        if (v40)
        {
          if (!sBtlLoadEffectData_ID(v40))
            return 2;
        }
      }
      goto LABEL_222;
    case 3:
      v19 = wk;
      v19->useitem_stock = -1;
      v41 = v19->panelwk->data[0]->itemid;
      v42 = sBtlGetItemtbl(v41);
      Skilltbl = sBtlGetSkilltbl(v42->sklid);
      v44 = v7->target_p;
      if (v44)
      {
        if ((Skilltbl->attr & 0x800) == 0)
        {
          v44 = v7->target_p;
          v46 = wk->stock_mask;
          if (((v46 >> (v44 - 1)) & 1) == 0)
            goto LABEL_260;
          v48 = v7->target_p - 1;
          v49 = wk;
          if (v49->summonflg[v48] == 2)
          {
            v48 = v7->target_p - 1;
            v49 = wk;
            v50 = v49->UnitMng;
            v51 = v49->summonID[v48];
            v52 = sBtlSearchUnit_ID(v50, v51);
            if (v52)
            {
              if (sBtlCheckDamageTargetUseItem(v52))
              {
                if (gBk_targetID_Use)
                {
                  v55 = wk->actaiwk;
                }
                else
                {
                  gBk_targetID_Use = 1;
                  v55 = wk->actaiwk;
                  gBk_targetID = v55->targetID;
                }
                v55->targetID = v52->ListID;
                goto LABEL_247;
              }
            }
            if (gBk_targetID_Use)
            {
              v170 = wk->actaiwk;
              ListID = v52->ListID;
            }
            else
            {
              gBk_targetID_Use = 1;
              v170 = wk->actaiwk;
              gBk_targetID = v170->targetID;
              ListID = v52->ListID;
            }
          }
          else
          {
LABEL_260:
            if (gBk_targetID_Use)
            {
              v170 = wk->actaiwk;
            }
            else
            {
              gBk_targetID_Use = 1;
              v170 = wk->actaiwk;
              gBk_targetID = v170->targetID;
            }
            ListID = -1;
          }
          v170->targetID = ListID;
          v164 = v7->target_p - 1;
          wk->useitem_stock = v7->target_p - 1;
          actwk = wk->actwk;
          goto LABEL_324;
        }
        wk->actaiwk->targetID = v7->targetid;
LABEL_247:
        wk->useitem_stock = -1;
        actwk = wk->actwk;
        v164 = -1;
LABEL_324:
        actwk->order_stockID = v164;
        goto LABEL_325;
      }
      if (gBk_targetID_Use)
      {
        v155 = wk->actaiwk;
      }
      else
      {
        v155 = wk->actaiwk;
        gBk_targetID_Use = 1;
        gBk_targetID = v155->targetID;
      }
      v155->targetID = wk->playerID;
LABEL_325:
      sBtlCheckItemCost(v41, 1);
      sBtlCheckItemCost_GBWK(v41, 1);
      v196 = sBtlGetItemtbl(v41);
      if ((sBtlGetSkilltbl(v196->sklid)->attr & 0x800) != 0)
        return 2;
      v197 = v196->sklid;
      sBtlSetUseSkill(wk, v197, 0);
      DeleteAll_MenuItemUse();
      sBtlReleaseItemList(wk->itemList);
LABEL_225:
      v151 = wk;
      goto LABEL_226;
    case 4:
      sBtlStatusBitOn(wk, 0x10u);
      v56 = wk->actwk;
      if (v56->status == 37 && v56->action_flg != 1)
        return 2;
      sBtlResetColor_Select();
      sBtlResetColor_PNL(0x80808080);
      sBtlStatusBitOff(wk, 0xFFFFFFEF);
      v59 = wk->gstat;
      ++v59[1];
      sBtlResetColorFlag();
      v60 = sBtlGetItemtbl(v7->itemid);
      v61 = sBtlGetSkilltbl(v60->sklid);
      v62 = v61;
      if ((v61->flg & 0x80) != 0 && (v61->attr & 0x400) != 0)
      {
        v64 = wk;
        v64->status2 &= ~2u;
        RestartBattle();
        sBtlRestart_Scene();
        v67 = sBtlResetAction(wk);
        sBtlResetNSTOP();
        sysmsgList = wk->sysmsgList;
        sBtlCreateSM(sysmsgList, wk, 1, 0, 0, 120);
        wk->sord_counter = 0;
        sBtlStatusBitOn(wk, 0x4000u);
        v71 = wk;
        escape_checkflg = 1;
        v71->status |= 0x1000000u;
        v73 = sub_1A21FE0(2239, 0, v72);
        v74 = wk;
        v74->status |= 0x40000000u;
        v74->mode = 9;
        v74->sord_st = 2;
        sBtlSetEscapeFlag();
      }
      flg2 = v62->flg2;
      if ((flg2 & 0x2000) != 0)
      {
        if (sBtlGetNakama(0))
        {
          v157 = *(u16 *)(*(&GBWK->player->stock_id->max_length + v7->target_p) + 22);
          v158 = 0;
          if (v157 == (u16)sBtlGetNakama(0)->para->devilid)
            goto LABEL_241;
        }
        if (sBtlGetNakama(1))
        {
          v158 = 1;
          v160 = *(u16 *)(*(&GBWK->player->stock_id->max_length + v7->target_p) + 22);
          if (v160 == (u16)sBtlGetNakama(1)->para->devilid)
LABEL_241:
            sBtlGetNakama(v158)->byctCnt = 0;
        }
      }
      else if ((flg2 & 0x4000) != 0)
      {
        para2 = (u16)v62->para2;
        v78 = *(s16 *)(*(&GBWK->player->stock_id->max_length + v7->target_p) + 22);
        if (para2 == (u16)sBtlGetDevilData(v78, -1)->kuda_id)
        {
          *(u8 *)(*(&GBWK->player->stock_id->max_length + v7->target_p) + 218) = 1;
          if (sBtlGetNakama(0))
          {
            v81 = *(u16 *)(*(&GBWK->player->stock_id->max_length + v7->target_p) + 22);
            v82 = 0;
            if (v81 == (u16)sBtlGetNakama(0)->para->devilid)
              goto LABEL_134;
          }
          if (sBtlGetNakama(1))
          {
            v82 = 1;
            v84 = *(u16 *)(*(&GBWK->player->stock_id->max_length + v7->target_p) + 22);
            if (v84 == (u16)sBtlGetNakama(1)->para->devilid)
LABEL_134:
              sBtlGetNakama(v82)->para->bChuuseiDrink = 1;
          }
        }
      }
      return 2;
    case 5:
      if (gBk_targetID_Use)
      {
        gBk_targetID_Use = 0;
        wk->actaiwk->targetID = gBk_targetID;
      }
      v88 = wk;
      v88->status2 &= ~2u;
      RestartBattle();
      sBtlRestart_Scene();
      sBtlResetAction(wk);
      for (i = 0; ; ++i)
      {
        v94 = wk;
        v95 = v94->UnitMng;
        if (i >= v95->number)
        {
          sBtlEntryItemList(v94->itemList);
          v147 = wk;
          *(u32 *)v147->gstat = 0;
          v147->menutype = 0;
          return 2;
        }
        pUnit = v95->pUnitL[i]->pUnit;
        if (!pUnit)
          continue;
        if (pUnit->hModel)
          pUnit->vstatus &= ~0x8000000u;
      }
    case 6:
      sBtlStatusBitOn(wk, 0x10u);
      HIDWORD(v100) = -286331153 * torimochi_cnt + 143165576;
      LODWORD(v100) = HIDWORD(v100);
      if ((u32)(v100 >> 1) <= 0x8888888)
      {
        sBtlPlaySE(0x10024u);
      }
      v102 = wk->UnitMng->pUnitL[v7->targetid]->pUnit;
      if (!v102)
        goto LABEL_278;
      v102->m_rate = 5.0;
      per = v102->pos.x;
      rot = wk->rot;
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v206 = wk->rot.y;
      v208 = wk->rot.x;
      v202 = wk->rot.w;
      v204 = wk->rot.z;
      rot.w = v202;
      rot.z = v204;
      rot.y = v206;
      rot.x = v208;
      v212.x = x;
      v212.y = y;
      v212.z = z;
      v212.w = w;
      *(u64 *)&v210.x = 0;
      *(u64 *)&v210.z = v97;
      Radian = sBtlGetRadian(v212, rot, v210, per);
      v112 = 6.0;
      v113 = Radian / v112;
      wk->rot = vct_A;
      sBtlAddUnitDeg(wk, v113);
      if (torimochi_cnt < 26)
        goto LABEL_278;
      sBtlStatusBitOn(v102, 0x10u);
      v102->status |= 0x80u;
      sBtlStatusBitOn(v102, 0x4000u);
      v116 = v102->status & 0xFFFFFFDE | 1;
      v102->flg |= 2u;
      v102->status = v116;
      v102->aiwk->mode = 0;
      sBtlSetAction(v102, 1, 0);
      v119 = wk->pos.x - v102->pos.x;
      v120 = wk->pos.z;
      v121 = v102->pos.z;
      v102->status &= ~0x20u;
      v123 = v120 - v121;
      v124 = sqrtf((f32)(v119 * v119) + (f32)(v123 * v123));
      v209 = v124;
      torimochi_spd_local = torimochi_spd + 0.1;
      torimochi_spd = torimochi_spd_local;
      v213.x = v102->pos.x;
      if (v124 <= torimochi_spd_local)
      {
        v129 = v102->pos.z;
      }
      else
      {
        v127 = v102->pos.x;
        v213.x = v127;
        torimochi_spd_local = torimochi_spd;
        v128 = v102->pos.z;
        v213.x = v213.x + (f32)((f32)(v119 / v124) * torimochi_spd_local);
        v102->pos.x = v213.x;
        v129 = v128 + (f32)((f32)(v123 / v124) * torimochi_spd);
        v102->pos.z = v129;
      }
      v215.x = v102->rot.x;
      v171 = v102->pos.y;
      v172 = v102->pos.w;
      v215.y = v102->rot.y;
      v215.z = v102->rot.z;
      v175 = v102->rot.w;
      v176 = wk->pos.x;
      v205 = v102->rot.x;
      v207 = v213.x;
      v201 = v102->rot.z;
      v203 = v102->rot.y;
      v215.z = v201;
      v215.y = v203;
      v215.x = v205;
      v213.x = v207;
      v213.y = v171;
      v213.z = v129;
      v213.w = v172;
      v215.w = v175;
      *(u64 *)&v211.x = 0;
      *(u64 *)&v211.z = v117;
      v177 = sBtlGetRadian(v213, v215, v211, v176);
      v102->rot = vct_A;
      sBtlAddUnitDeg(v102, v177);
      if (v209 < 50.0)
      {
        torimochi_get = 1;
        wk->actaiwk->targetID = -1;
        v102->hModel->stat |= 2u;
        sBtlStatusBitOn(v102, 0x4000u);
        v182 = wk;
        v183 = v182->UnitMng->pUnitL[v7->targetid]->pUnit;
        --v182->enemy_num;
        sBtlDeleteEnemy(v183);
        sBtlDeleteUnit(v183);
        v183->hstatus |= 8u;
        v183->para->now->hp = 0;
        sBtlStatusBitOff(v183, 0xFFFFFFEF);
        LODWORD(v184) = *(u64 *)&v183->vstatus;
        v185 = *(u64 *)&v183->vstatus | 0x200000002LL;
        v183->status |= 0x20u;
        LODWORD(v184) = v184 & 0xFF7FFFFF;
        HIDWORD(v184) = HIDWORD(v185);
        *(u64 *)&v183->vstatus = v184;
      }
LABEL_278:
      v188 = torimochi_cnt + 1;
      v133 = torimochi_cnt - 60 < 0;
      torimochi_cnt = v188;
      if (v133 == __OFSUB__(v188, 61))
      {
        if (torimochi_get)
        {
          sBtlPlaySE(0x10025u);
          sBtlSetMotion(wk, 39, 0, 0, 0);
          v151 = wk;
          v151->status2 |= 0x200000u;
          v151 = wk;
          torimochi_cnt = 0;
LABEL_226:
          v146 = v151->gstat;
          v145 = v146[1] + 1;
LABEL_227:
          v146[1] = v145;
        }
      }
      return 2;
    case 7:
      v132 = torimochi_cnt + 1;
      v133 = torimochi_cnt - 70 < 0;
      torimochi_cnt = v132;
      if (v133 == __OFSUB__(v132, 71))
      {
        torimochi_cnt = 0;
        v135 = wk;
        v137 = v135->gstat;
        v135->kaiwa_gstat = 0;
        ++v137[1];
        if (!v138)
        sBtlSetMotion(wk, 0, 10, 10, 0);
      }
      return 2;
    case 8:
      ++torimochi_cnt;
      return 2;
    case 9:
      v142 = torimochi_cnt + 1;
      v133 = torimochi_cnt - 120 < 0;
      torimochi_cnt = v142;
      if (v133 == __OFSUB__(v142, 121))
        goto LABEL_222;
      return 2;
    case 0xC:
      v19 = wk;
      gstat = v19->gstat;
      v143 = gstat[1];
      v19->kaiwa_gstat = 0;
      gstat[1] = v143 + 1;
      return 2;
    case 0x10:
      sBtlStatusBitOn(wk, 0x10u);
      v145 = 17;
      v146 = wk->gstat;
      goto LABEL_227;
    default:
      return 2;
  }
}

// 0x1fa8b80
bool sBtlSetReturn(SBTLUNIT_WORK *wk, s32 _SwitchReturnMode) {
  SBTLUNIT_WORK *Nakama;
  SBATTLE_WORK *v7;
  u32 stock_mask;
  s16 v9;
  SBATTLE_WORK *v11;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 per;
  f32 Radian;
  s32 v24;
  SBATTLE_WORK *v25;
  s16 v26;
  bool result;
  s32 bst_effserialID2;
  SBTLEFF_LISTWORK *effList;
  SBTLDVLTK_LISTWORK *dvltkList;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  sdfVector4_t v36;
  sdfVector4_t v37;
  sdfVector4_t rot;

  Nakama = sBtlGetNakama(wk->ctrlSmnIdx);
  v7 = wk;
  stock_mask = v7->stock_mask;
  v9 = v7->summonindex[v7->ctrlSmnIdx];
  if (((stock_mask >> v9) & 1) == 0)
    return 0;
  v11 = wk;
  if (v11->summonflg[v11->summonindex[v11->ctrlSmnIdx]] != 2)
    return 0;
  if (SwitchReturnMode)
  {
    Nakama->motion_NoUseMSE_motionID = 7;
    goto LABEL_15;
  }
  v11 = wk;
  dvltkList = v11->dvltkList;
  sBtlCreateDvltk_Priority(dvltkList, Nakama, 22);
LABEL_15:
  if (wk->bBfrBtlEnd && Nakama)
  {
    if (sBtlCheckDamageTarget(Nakama))
    {
      rot = wk->rot;
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      per = Nakama->pos.x;
      v34 = wk->rot.y;
      v35 = wk->rot.x;
      v32 = wk->rot.w;
      v33 = wk->rot.z;
      rot.w = v32;
      rot.z = v33;
      rot.y = v34;
      rot.x = v35;
      v37.x = x;
      v37.y = y;
      v37.z = z;
      v37.w = w;
      *(u64 *)&v36.x = 0;
      Radian = sBtlGetRadian(v37, rot, v36, per);
      wk->rot = vct_A;
      sBtlAddUnitDeg(wk, Radian);
      goto LABEL_26;
    }
  }
LABEL_26:
  Nakama->asimoto_mode = 0;
  sBtlSummonDevilAshimotoReset(Nakama);
  Nakama->vstatus &= 0xFFDFEFFC;
  Nakama->fadepara = 16;
  Nakama->color = -2139062144;
  sBtlForceDelete_SkillFlag_Acter(Nakama, 0x400u);
  sBtlForceDelete_ID_Acter(wk->effList, Nakama, 55);
  v24 = wk->summonindex[wk->ctrlSmnIdx];
  SetReturn(v24, 0);
  v25 = wk;
  v26 = v25->summonindex[v25->ctrlSmnIdx];
  result = 1;
  v25->stock_mask &= ~(1 << v26);
  bst_effserialID2 = Nakama->bst_effserialID2;
  if (bst_effserialID2 != -1)
  {
    effList = wk->effList;
    sBtlDeleteEffectData_SerialID2(effList, bst_effserialID2);
    Nakama->bst_effserialID2 = -1;
    return 1;
  }
  return result;
}

// 0x1f8a5d0
bool sBtlResetColor(u32 abgr) {
  sBtlResetColor_PNL(abgr);
  return 1;
}

// 0x1fa8350
void sBtlSetMenuItemList(void) {
  s32 useitembk;
  SBTLEFF_LISTWORK *effList;
  SBATTLE_WORK *v10;
  SBTLEFF_LISTWORK *v11;
  s32 v12;
  SBATTLE_WORK *v14;
  SBTLEFF_LISTWORK *v15;
  s32 v16;

  if (!wk)
    return;
  if (!wk->itemList)
    return;
  useitembk = wk->useitembk;
  if (useitembk)
    goto LABEL_11;
LABEL_40:
  sBtlReleaseItemList(wk->itemList);
  sBtlEntryItemList(wk->itemList);
  return;
LABEL_39:
  goto LABEL_40;
LABEL_11:
  effList = wk->effList;
  if (sBtlSearchEffect_SAB(effList, useitembk, 1u))
    goto LABEL_33;
  v10 = wk;
  v11 = v10->effList;
  v12 = v10->useitembk;
  if (sBtlSearchEffect_SAB(v11, v12, 2u))
    goto LABEL_33;
  goto LABEL_28;
  if (!sBtlSearchEffect_SAB(v11, v12, 2u))
  {
LABEL_28:
    v14 = wk;
    v15 = v14->effList;
    v16 = v14->useitembk;
    if (sBtlSearchEffect_SAB(v15, v16, 5u))
      goto LABEL_33;
    goto LABEL_39;
  }
LABEL_33:
  sBtlReleaseItemList(wk->itemList);
}

// 0x1fa8600
static void SetSummonMenu(s32 mode) {
  s16 *sgstat;
  u32 v9;
  SBATTLE_WORK *v10;
  s32 equipbulletbk;
  SBTLITEM_TBL *Itemtbl;
  SBTLEFF_LISTWORK *effList;
  s32 sklid;
  SBTLITEM_LISTWORK *bulletList;
  s32 v17;
  SBTLEFF_LISTWORK *v18;
  s32 v20;
  SBTLEFF_LISTWORK *v21;

  StopBattle();
  sBtlResetMenuPara();
  sBtlSetColor_PNL(0x80606060);
  sBtlPlaySE(0);
  wk->modebk = wk->mode;
  wk->mode = 5;
  wk->status2 |= 2u;
  if (mode == 1)
    return;
  sgstat = wk->sgstat;
  wk->macter_csr = 0;
  *(u32 *)sgstat = 0;
  wk->menutype = 0;
  sBtlSetStart();
  sBtlSetMenuItemList();
  v10 = wk;
  equipbulletbk = v10->equipbulletbk;
  if (!equipbulletbk)
  {
    if (!v9)
    {
      v10 = wk;
    }
    bulletList = v10->bulletList;
    goto LABEL_37;
  }
  if (!v9)
  {
    equipbulletbk = wk->equipbulletbk;
  }
  Itemtbl = sBtlGetItemtbl(equipbulletbk);
  effList = wk->effList;
  sklid = Itemtbl->sklid;
  if (sBtlSearchEffect_SAB(wk->effList, sklid, 1u))
    goto LABEL_49;
  v17 = Itemtbl->sklid;
  v18 = wk->effList;
  if (sBtlSearchEffect_SAB(v18, v17, 2u))
    goto LABEL_49;
  goto LABEL_45;
  if (!sBtlSearchEffect_SAB(v18, v17, 2u))
  {
LABEL_45:
    v20 = Itemtbl->sklid;
    v21 = wk->effList;
    if (sBtlSearchEffect_SAB(v21, v20, 5u))
      goto LABEL_49;
    bulletList = wk->bulletList;
LABEL_37:
    sBtlReleaseItemList(bulletList);
    sBtlEntryItemList_Type(wk->bulletList, 4u);
    return;
  }
LABEL_49:
  sBtlReleaseItemList(wk->bulletList);
}

// 0x1f6c950
bool sBtlCheckBit(u32 data, s32 bit) {
  return (data >> bit) & 1;
}

// 0x1fa9070
void sBtlSetBit(u32 *data, s32 bit) {
  *data |= 1 << bit;
}

// 0x1fa9360
s32 sBtlGetkuisibariBit(SKLID _sklID) {
  s32 v4;
  char *v6;
  Il2CppObject *v7;
  System_Enum_o v8;

  v4 = IndexOf_Int32Enum_(kuisibariTbl, sklID);
  if (v4 != -1)
    return v4;
  *(u32 *)&v8.System_ValueType_Fields = sklID;
  v8.klass = (System_Enum_c *)SKLID;
  v8.monitor = -1;
  v6 = ToString(&v8, 0);
  v7 = Concat_54766928("食いしばりスキルではない::", v6, 0);
  LogError(v7, 0);
  return -1;
}

// 0x1fa94a0
bool sBtlCheckKuisibari(SKLID _sklID) {
  char v4;

  v4 = sBtlGetkuisibariBit(sklID);
  return (wk->rKuishiUseBit >> v4) & 1;
}

// 0x1fa9580
void sBtlSetKuisibari(SKLID _sklID) {
  char v4;

  v4 = sBtlGetkuisibariBit(sklID);
  wk->rKuishiUseBit |= 1 << v4;
}

// 0x1fa9340
void sBtlResetBit(u32 *data, s32 bit) {
  *data &= ~(1 << bit);
}

// 0x1fa9660
static f32 Cadd(f32 now, f32 add) {
  f32 v6;
  f32 raidouCoolTime;

  v6 = now + add;
  raidouCoolTime = wk->raidouCoolTime;
  if (v6 <= raidouCoolTime)
    return v6;
  v6 = raidouCoolTime;
  return v6;
}

// 0x1fa9740
void sBtlRaidouWazaCoolTimeInit(void) {
  s64 v2;
  SBATTLE_WORK *wk_local;
  f32 raidouCoolTime;
  s32 v7;

  v2 = 8;
  wk->raidouCoolTime = 60.0;
  while (1)
  {
    if (v2 - 8 >= SLODWORD(wk->raidouWazaCool->max_length))
      break;
    v7 = *((u32 *)&GBWK->player->raidouSkill->obj.klass + v2);
    if (v7)
    {
      wk_local = wk;
      raidouCoolTime = wk_local->raidouCoolTime;
    }
    else
    {
      raidouCoolTime = 0.0;
      wk_local = wk;
    }
    *((f32 *)&wk_local->raidouWazaCool->obj.klass + v2++) = raidouCoolTime;
  }
}

// 0x1fa9880
void sBtlRaidouWazaCoolTimeUpdate(void) {
  bool v2;
  f32 v4;
  s32 v5;
  SBTLSKILLP_TBL *Skilltbl;
  f32 *raidouWazaCool;
  f32 raidouCoolTime;
  f32 v11;
  s32 coolTime;
  f32 v13;
  f32 v15;
  f32 v16;
  s32 v17;
  SBTLSKILLP_TBL *v18;
  SBATTLE_WORK *v20;
  f32 *v21;
  f32 v22;
  f32 v23;
  s32 v24;
  f32 v25;
  f32 v27;
  f32 v28;
  s32 v29;
  SBTLSKILLP_TBL *v30;
  SBATTLE_WORK *v32;
  f32 *v33;
  f32 v34;
  f32 v35;
  s32 v36;
  f32 v37;
  f32 v39;
  f32 v40;

  if (!wk)
    return;
  if (IsSceanStop())
    return;
  if (wk->cmbSkl->bRun)
    return;
  v2 = !sBtlGetSpiritSkillChk(1440);
  if (v2)
    v4 = 1.0;
  else
    v4 = 0.8;
  v5 = GBWK->player->raidouSkill[0];
  if (v5)
  {
    Skilltbl = sBtlGetSkilltbl(v5);
    raidouWazaCool = wk->raidouWazaCool;
    raidouCoolTime = wk->raidouCoolTime;
    v11 = raidouWazaCool[0];
    coolTime = Skilltbl->coolTime;
    v13 = raidouCoolTime / (f32)(v4 * (f32)(raidouCoolTime * (f32)coolTime));
    v15 = v11 + v13;
    v16 = wk->raidouCoolTime;
    if (v15 <= v16)
      goto LABEL_35;
    goto LABEL_33;
    if (v15 <= v16)
    {
LABEL_35:
      raidouWazaCool[0] = v15;
      goto LABEL_36;
    }
LABEL_33:
    v15 = v16;
    v15 = wk->raidouCoolTime;
    goto LABEL_35;
  }
LABEL_36:
  v17 = GBWK->player->raidouSkill[1];
  if (v17)
  {
    v18 = sBtlGetSkilltbl(v17);
    v20 = wk;
    v21 = v20->raidouWazaCool;
    v22 = v20->raidouCoolTime;
    v23 = v21[1];
    v24 = v18->coolTime;
    v25 = v22 / (f32)(v4 * (f32)(v22 * (f32)v24));
    v27 = v23 + v25;
    v28 = wk->raidouCoolTime;
    if (v27 <= v28)
      goto LABEL_51;
    goto LABEL_49;
    if (v27 <= v28)
    {
LABEL_51:
      v21[1] = v27;
      goto LABEL_52;
    }
LABEL_49:
    v27 = v28;
    v27 = wk->raidouCoolTime;
    goto LABEL_51;
  }
LABEL_52:
  v29 = GBWK->player->raidouSkill[2];
  if (v29)
  {
    v30 = sBtlGetSkilltbl(v29);
    v32 = wk;
    v33 = v32->raidouWazaCool;
    v34 = v32->raidouCoolTime;
    v35 = v33[2];
    v36 = v30->coolTime;
    v37 = v34 / (f32)(v4 * (f32)(v34 * (f32)v36));
    v39 = v35 + v37;
    v40 = wk->raidouCoolTime;
    if (v39 <= v40)
      goto LABEL_67;
    goto LABEL_65;
    if (v39 <= v40)
    {
LABEL_67:
      v33[2] = v39;
      return;
    }
LABEL_65:
    v39 = v40;
    v39 = wk->raidouCoolTime;
    goto LABEL_67;
  }
}

// 0x1f7b020
bool sBtlIsRaidouWazaCoolTime(s32 index) {
  return wk->raidouWazaCool[index] == wk->raidouCoolTime;
}

// 0x1fa9dc0
void sBtlRaidouWazaCoolTimeClr(s32 index) {
  if (!wk)
    return;
  wk->raidouWazaCool[index] = 0.0;
}

// 0x1fa1ea0
static f32 GetAnlogKeyToDir(SBTLUNIT_WORK *wk, f32 *dir) {
  f32 AnlogKey;
  f32 x;
  f32 z;
  sdfVector4_t v9;

  *(u64 *)&v9.x = 0;
  *(u64 *)&v9.z = 0;
  AnlogKey = GetAnlogKey(wk, &v9);
  x = v9.x;
  z = v9.z;
  *dir = sBtlGetVecToDir(x, z);
  return AnlogKey;
}

// 0x1fa60e0
static f32 GetAnlogKeyToVecAndDir(SBTLUNIT_WORK *wk, sdfVector4_t *vec, f32 *dir) {
  f32 AnlogKey;
  f32 x;
  f32 z;

  AnlogKey = GetAnlogKey(wk, vec);
  x = vec->x;
  z = vec->z;
  *dir = sBtlGetVecToDir(x, z);
  return AnlogKey;
}

// 0x1f7c3c0
static s32 NormalProc(SBTLUNIT_WORK *wk) {
  SBTLAI_WORK *aiwk;
  SBATTLE_WORK *v5;
  s32 v6;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 AnlogKey;
  f32 v17;
  f32 v18;
  f32 VecToDir;
  f32 v22;
  f32 v23;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v27;
  s32 v28;
  s32 motionID;
  s32 v33;
  s32 cmstatus;
  f32 turn_goal;
  f32 AtoB_LR;
  s32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  s32 turn_ed_motionID;
  f32 v45;
  f32 v46;
  SBATTLE_WORK *v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 front_time;
  char v53;
  u32 v54;
  s32 v59;
  u32 v61;
  s32 v63;
  s32 v67;
  char v68;
  s32 v69;
  f32 v70;
  s32 hstatus;
  _BOOL4 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 turn_start;
  f32 v77;
  f32 v78;
  s32 v79;
  s32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  s32 v87;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  long f64 v95;
  long f64 v96;
  s32 v97;
  f32 v99;
  u32 v100;
  f32 v101;
  f32 v104;
  f32 v105;
  s32 next_motionID;
  f32 v107;
  s32 v108;
  f32 v109;
  f32 v110;
  f32 Dir180;
  long f64 v112;
  long f64 v113;
  s32 v114;
  s32 v115;
  f32 v116;
  f32 v117;
  f32 v118;
  long f64 v119;
  long f64 v120;
  s32 v121;
  u32 v122;
  f32 v123;
  s32 v124;
  SBTLUNIT_LISTWORK *v126;
  SBTLUNIT_WORK *v127;
  SBTLUNIT_WORK *v128;
  f32 v129;
  f32 v130;
  f32 v131;
  f32 v132;
  f32 v133;
  f32 v134;
  s32 v135;
  s32 v136;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v140;
  f32 v141;
  f32 v142;
  f32 v143;
  f32 v144;
  f32 PosToDir;
  f32 v146;
  s32 v147;
  s32 v148;
  SBTLUNIT_LISTWORK *v150;
  SBTLUNIT_WORK *v151;
  f32 v152;
  f32 v153;
  f32 v154;
  f32 v155;
  f32 v156;
  f32 v157;
  s32 v158;
  f32 v159;
  s32 v160;
  f32 v161;
  f32 v162;
  f32 v163;
  f32 v164;
  f32 LenXZ;
  f32 v166;
  f32 v167;
  f32 v168;
  s32 v169;
  SBTLUNIT_LISTWORK *v171;
  SBTLUNIT_WORK *v172;
  f32 v173;
  f32 v174;
  f32 v175;
  f32 v176;
  f32 v177;
  f32 v178;
  s32 v179;
  s32 v180;
  sdfVector4_t v181;
  sdfVector4_t v182;

  aiwk = wk->aiwk;
  *(u64 *)&v181.x = 0;
  *(u64 *)&v181.z = 0;
  if (aiwk->bWait || aiwk->bWait2)
    return -1;
  v5 = wk;
  if (v5->cmbSkl->bRun)
    return -1;
  v5 = wk;
  v5->bHuumaCancel = 0;
  v5->ComboMotRetryCnt = 0;
  v5->ComboMotRetryUse = 0;
  x = wk->rot.x;
  y = wk->rot.y;
  p_rot = &wk->rot;
  z = wk->rot.z;
  w = wk->rot.w;
  v182.x = x;
  v182.y = y;
  v182.z = z;
  v182.w = w;
  RotToDir = sBtlGetRotToDir(v182);
  AnlogKey = GetAnlogKey(wk, &v181);
  v17 = v181.x;
  v18 = v181.z;
  VecToDir = sBtlGetVecToDir(v17, v18);
  v22 = VecToDir
      + sBtlGetDir180(wk->scene->camera->followUpAngle.x);
  if (v22 >= 360.0)
    v23 = v22 + -360.0;
  else
    v23 = v22;
  if (wk->actwk->status == 8)
  {
    sBtlResetGunMode(wk, 0);
  }
  SetGunPlayerDir(wk);
  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  v27 = MotionFrameF;
  if (MotionFrameF == INFINITY)
    v28 = 0x80000000;
  else
    v28 = MotionFrameF;
  if (!sBtlCheckMove(wk))
  {
    if (wk->actwk->status != 15)
      goto LABEL_88;
    if (wk->sord_st != 4)
      goto LABEL_88;
  }
  motionID = wk->motionID;
  if ((u32)(motionID - 107) < 3)
  {
    if (!sBtlCheckMotionEnd(wk))
    {
      if (AnlogKey < 48.0)
      {
        if ((v33 = wk->motionID, v27 >= 4.0) && v33 == 108 || v27 >= 3.0 && v33 == 107 || v27 >= 3.0 && v33 == 109)
        {
          cmstatus = wk->cmstatus;
          wk->turn_ed_motionID = v33;
          wk->cmstatus = cmstatus | 8;
        }
      }
      turn_goal = wk->turn_goal;
      AtoB_LR = sBtlGetAtoB_LR(RotToDir, turn_goal);
      v37 = wk->motionID;
      switch (v37)
      {
        case 'k':
          turn_start = wk->turn_start;
          wk->turn_goal = turn_goal;
          v77 = turn_goal + 360.0;
          if (turn_goal >= turn_start)
            v77 = turn_goal;
          v40 = (f32)(v77 - turn_start) / 13.0;
          break;
        case 'm':
          v78 = wk->turn_start;
          wk->turn_goal = turn_goal;
          if (v78 < turn_goal)
            v78 = v78 + 360.0;
          v40 = (f32)(turn_goal - v78) / 13.0;
          if (AtoB_LR <= v40)
            goto LABEL_258;
          goto LABEL_257;
        case 'l':
          v38 = wk->turn_start;
          wk->turn_goal = turn_goal;
          v39 = turn_goal + 360.0;
          if (turn_goal >= v38)
            v39 = turn_goal;
          v40 = (f32)(v39 - v38) / 17.0;
          if ((wk->cmstatus & 8) != 0)
          {
            switch (v28)
            {
              case 4:
                v41 = 7.0;
                goto LABEL_252;
              case 5:
                v41 = 6.0;
                goto LABEL_252;
              case 6:
                v41 = 5.0;
                goto LABEL_252;
              case 7:
                v41 = 4.0;
                goto LABEL_252;
              case 8:
                v41 = 3.0;
LABEL_252:
                v40 = v40 * v41;
                break;
              default:
                break;
            }
          }
          if (AtoB_LR < 0.0)
          {
            if (AtoB_LR <= (f32)-v40)
            {
LABEL_258:
              v105 = wk->max_mvspd.z;
              wk->mv_spd.z = v105;
              next_motionID = wk->next_motionID;
              if (next_motionID == 107 || next_motionID == 109)
              {
                if ((wk->cmstatus & 8) == 0)
                {
                  if (v28 < 0)
                  {
                    v105 = v105 * 0.1;
                    wk->mv_spd.z = v105;
                  }
                  switch (v28)
                  {
                    case 0:
LABEL_269:
                      *(f32 *)&v108 = 0.1;
                      goto LABEL_276;
                    case 1:
LABEL_271:
                      *(f32 *)&v108 = 0.2;
                      goto LABEL_276;
                    case 2:
LABEL_272:
                      *(f32 *)&v108 = 0.3;
                      goto LABEL_276;
                    case 3:
LABEL_273:
                      *(f32 *)&v108 = 0.4;
                      goto LABEL_276;
                    case 4:
LABEL_274:
                      *(f32 *)&v108 = 0.6;
                      goto LABEL_276;
                    case 5:
LABEL_275:
                      *(f32 *)&v108 = 0.8;
LABEL_276:
                      v107 = *(f32 *)&v108;
LABEL_277:
                      v109 = v105 * v107;
                      goto LABEL_278;
                    default:
                      goto LABEL_279;
                  }
                }
                v109 = 20.0;
LABEL_278:
                wk->mv_spd.z = v109;
              }
              else if (next_motionID == 108)
              {
                if (v28 < 0)
                {
                  v105 = v105 * 0.1;
                  wk->mv_spd.z = v105;
                }
                switch (v28)
                {
                  case 0:
                    goto LABEL_269;
                  case 1:
                  case 2:
                    goto LABEL_271;
                  case 3:
                    goto LABEL_272;
                  case 4:
                    goto LABEL_273;
                  case 5:
                    v107 = 0.5;
                    goto LABEL_277;
                  case 6:
                    goto LABEL_274;
                  case 7:
                    goto LABEL_275;
                  default:
                    break;
                }
              }
LABEL_279:
              v70 = RotToDir + v40;
LABEL_280:
              if (v70 >= 360.0)
                v70 = v70 + -360.0;
              if (v70 >= 0.0)
                v110 = v70;
              else
                v110 = v70 + 360.0;
              Dir180 = sBtlGetDir180(v110);
              wk->mv_rotbk = Dir180;
              FromEuler(0.0, Dir180 * 0.017453292, 0.0);
              *(__n128 *)&v113 = sub_1B335A0(&wk->rot, 0, v112);
              sub_1B335A0(&wk->rotbk, 0, v113);
              wk->hstatus |= 0x1000u;
              wk->front_deg = turn_goal;
              goto LABEL_290;
            }
            goto LABEL_257;
          }
          break;
        default:
LABEL_257:
          v40 = AtoB_LR;
          goto LABEL_258;
      }
      if (AtoB_LR >= v40)
        goto LABEL_258;
      goto LABEL_257;
    }
LABEL_77:
    v47 = wk;
    if (v47->battlemode == 1)
    {
      v48 = wk->pos.x;
      v49 = wk->pos.y;
      v50 = wk->pos.z;
      v51 = VecToDir + (f32)(360.0 - mapGetScreenDir(v48, v49, v50, 0.0));
      if (v51 >= 360.0)
        turn_goal = v51 + -360.0;
      else
        turn_goal = v51;
      if (AnlogKey >= 48.0)
      {
        wk->mv_spd.z = wk->max_mvspd.z;
        v70 = RotToDir + (f32)(sBtlGetAtoB_LR(RotToDir, turn_goal) * 0.2);
        goto LABEL_280;
      }
      goto LABEL_88;
    }
    if (AnlogKey < 48.0)
    {
LABEL_88:
      front_time = wk->front_time;
      v6 = 0;
      goto LABEL_89;
    }
    hstatus = wk->hstatus;
    if ((hstatus & 0x800000) != 0)
    {
      wk->mv_spd.z = 4.0;
      goto LABEL_206;
    }
    if ((hstatus & 0x3000000) != 0)
    {
      v72 = 0;
      v73 = 4.0;
    }
    else
    {
      v72 = (wk->vstatus & 0x8000) == 0;
      if ((wk->vstatus & 0x8000) != 0)
        v73 = wk->max_mvspd.z * 0.7;
      else
        v73 = wk->max_mvspd.z;
    }
    wk->mv_spd.z = v73;
    if ((hstatus & 0x3000000) != 0)
    {
LABEL_206:
      v89 = sBtlGetAtoB_LR(RotToDir, v23);
      if (v89 <= -90.0 || v89 >= 90.0)
      {
        v90 = -20.0;
        if (v89 <= -20.0)
          goto LABEL_218;
        v90 = 20.0;
      }
      else
      {
        if (v89 > -45.0 && v89 < 45.0)
          goto LABEL_217;
        v90 = -15.0;
        if (v89 <= -15.0)
        {
LABEL_218:
          v91 = RotToDir + v90;
          v92 = (f32)(RotToDir + v90) + -360.0;
          if (v91 >= 360.0)
            v91 = v92;
          if (v91 >= 0.0)
            v93 = v91;
          else
            v93 = v91 + 360.0;
          v94 = sBtlGetDir180(v93);
          wk->mv_rotbk = v94;
          FromEuler(0.0, v94 * 0.017453292, 0.0);
          *(__n128 *)&v96 = sub_1B335A0(&wk->rot, 0, v95);
          sub_1B335A0(&wk->rotbk, 0, v96);
          v97 = wk->hstatus;
          wk->front_deg = v23;
          wk->hstatus = v97 | 0x1000;
          goto LABEL_290;
        }
        v90 = 15.0;
      }
      if (v89 < v90)
      {
LABEL_217:
        v90 = v89 * 0.2;
        goto LABEL_218;
      }
      goto LABEL_218;
    }
    if ((wk->vstatus & 0x8000) != 0)
    {
      wk->front_deg = v23;
      wk->hstatus = hstatus | 0x1000;
      v104 = sBtlGetAtoB_LR(RotToDir, v23);
      if (v104 < -45.0 || v104 > 45.0)
      {
        if (v104 <= 45.0 || v104 > 135.0)
        {
          v136 = wk->cmstatus;
          if (v104 >= -45.0 || v104 < -135.0)
            wk->cmstatus = v136 | 0x40000;
          else
            wk->cmstatus = v136 | 0x80000;
        }
        else
        {
          wk->cmstatus |= 0x20000u;
        }
      }
      else
      {
        wk->cmstatus |= 0x10000u;
      }
      goto LABEL_290;
    }
    v47 = wk;
    v47->CameraLockOnNear = 0;
    v99 = sBtlGetAtoB_LR(RotToDir, v23);
    v100 = wk->motionID - 103;
    if (v100 <= 0x20)
    {
      if (((1 << v100) & 0x10000000DLL) != 0)
      {
        v101 = 0.0;
        if (v99 <= -135.0 || v99 >= 135.0)
          goto LABEL_315;
        goto LABEL_310;
      }
      if (((1 << v100) & 0xC0000000LL) != 0)
      {
LABEL_310:
        if ((f32)(v99 * 0.2) >= -45.0)
          v101 = v99 * 0.2;
        else
          v101 = -45.0;
        if (v101 > 45.0)
          v101 = 45.0;
LABEL_315:
        v117 = sBtlGet360(RotToDir + v101);
        v118 = sBtlGetDir180(v117);
        wk->mv_rotbk = v118;
        FromEuler(0.0, v118 * 0.017453292, 0.0);
        *(__n128 *)&v120 = sub_1B335A0(&wk->rot, 0, v119);
        sub_1B335A0(&wk->rotbk, 0, v120);
        v121 = wk->hstatus;
        wk->front_deg = v23;
        wk->hstatus = v121 | 0x1000;
        if (!v72)
          goto LABEL_290;
        v122 = wk->motionID - 103;
        v123 = v73 * 0.85;
        if (v122 <= 0x1F)
        {
          if (((1 << v122) & 0x1E0000) != 0)
          {
            targetID = wk->actaiwk->targetID;
            if (targetID != -1)
            {
              targetID = wk->actaiwk->targetID;
              UnitMng = wk->UnitMng;
              v140 = sBtlSearchUnit_ID(UnitMng, targetID);
              if (v140)
              {
                v141 = v140->pos.x;
                v142 = v140->pos.z;
                v143 = wk->pos.x;
                v144 = wk->pos.z;
                PosToDir = sBtlGetPosToDir(v143, v144, v141, v142);
                v146 = sBtlGetAtoB_LR(RotToDir, PosToDir);
                v147 = wk->cmstatus;
                if (v146 >= 0.0)
                  goto LABEL_391;
                goto LABEL_382;
              }
            }
            goto LABEL_369;
          }
          if (((1 << v122) & 0xD) != 0)
          {
            if (v99 > -135.0 && v99 < 135.0)
            {
              v124 = wk->actaiwk->targetID;
              if (v124 != -1)
              {
                v124 = wk->actaiwk->targetID;
                v126 = wk->UnitMng;
                v127 = sBtlSearchUnit_ID(v126, v124);
                if (v127)
                {
                  v128 = v127;
                  v129 = v127->pos.x;
                  v130 = v127->pos.z;
                  v131 = wk->pos.x;
                  v132 = wk->pos.z;
                  v133 = sBtlGetPosToDir(v131, v132, v129, v130);
                  v134 = sBtlGetAtoB_LR(RotToDir, v133);
                  if (v134 > -45.0 || v134 <= -160.0)
                  {
                    v160 = wk->cmstatus;
                    if (v134 < 45.0 || v134 >= 160.0)
                      v135 = v160 | 0x80;
                    else
                      v135 = v160 | 0x20;
                  }
                  else
                  {
                    v135 = wk->cmstatus | 0x40;
                  }
                  wk->cmstatus = v135;
                  wk->mv_spd.z = v123;
                  if (sBtlChkSideBySide())
                  {
                    v161 = wk->pos.x;
                    v162 = wk->pos.z;
                    v163 = v128->pos.x;
                    v164 = v128->pos.z;
                    LenXZ = sBtlGetLenXZ(v161, v162, v163, v164);
                    if (LenXZ >= 100.0)
                      v166 = LenXZ;
                    else
                      v166 = 100.0;
                    v167 = 1.0;
                    v168 = 1.0;
                    if (v166 <= 300.0)
                      v168 = (f32)(v166 + -100.0) / 200.0;
                    if (v168 <= 1.0)
                      v167 = (f32)(v168 * 0.6) + 0.4;
                    wk->mv_spd.z = v123 * v167;
                  }
                  goto LABEL_290;
                }
              }
              goto LABEL_417;
            }
            goto LABEL_377;
          }
          if (((1 << v122) & 0xC0000000) != 0)
          {
            v148 = wk->actaiwk->targetID;
            if (v148 != -1)
            {
              v148 = wk->actaiwk->targetID;
              v150 = wk->UnitMng;
              v151 = sBtlSearchUnit_ID(v150, v148);
              if (v151)
              {
                v152 = v151->pos.x;
                v153 = v151->pos.z;
                v154 = wk->pos.x;
                v155 = wk->pos.z;
                v156 = sBtlGetPosToDir(v154, v155, v152, v153);
                v157 = sBtlGetAtoB_LR(v117, v156);
                if (v157 >= -45.0 && v157 <= 45.0)
                {
                  v147 = wk->cmstatus;
                  if (wk->motionID == 133)
                  {
LABEL_391:
                    wk->cmstatus = v147 | 0x100;
                    goto LABEL_290;
                  }
LABEL_382:
                  wk->cmstatus = v147 | 0x200;
                  goto LABEL_290;
                }
                if (v157 <= -45.0 && v157 > -160.0)
                {
                  v147 = wk->cmstatus;
                  goto LABEL_382;
                }
                v147 = wk->cmstatus;
                if (v157 >= 45.0 && v157 < 160.0)
                  goto LABEL_391;
LABEL_370:
                wk->cmstatus = v147 | 0x80;
LABEL_290:
                sBtlSetAction(wk, 2, 0);
                v6 = 1;
                wk->wait_counter = 0;
                front_time = wk->front_time;
                wk->status &= ~0x100u;
                goto LABEL_295;
              }
            }
LABEL_369:
            v147 = wk->cmstatus;
            goto LABEL_370;
          }
        }
        if (v99 > -135.0 && v99 < 135.0)
        {
          if (v99 < 45.0 || v99 >= 135.0)
          {
            if (v99 > -45.0 || v99 <= -135.0)
            {
              v169 = wk->actaiwk->targetID;
              if (v169 != -1)
              {
                v169 = wk->actaiwk->targetID;
                v171 = wk->UnitMng;
                v172 = sBtlSearchUnit_ID(v171, v169);
                if (v172)
                {
                  v173 = v172->pos.x;
                  v174 = v172->pos.z;
                  v175 = wk->pos.x;
                  v176 = wk->pos.z;
                  v177 = sBtlGetPosToDir(v175, v176, v173, v174);
                  v178 = sBtlGetAtoB_LR(RotToDir, v177);
                  if (v178 <= -45.0 && v178 > -160.0)
                  {
                    v179 = wk->cmstatus | 0x40;
LABEL_419:
                    wk->cmstatus = v179;
                    wk->mv_spd.z = v123;
                    goto LABEL_290;
                  }
                  v180 = wk->cmstatus;
                  if (v178 >= 45.0 && v178 < 160.0)
                  {
                    v179 = v180 | 0x20;
                    goto LABEL_419;
                  }
LABEL_418:
                  v179 = v180 | 0x80;
                  goto LABEL_419;
                }
              }
LABEL_417:
              v180 = wk->cmstatus;
              goto LABEL_418;
            }
            v158 = wk->cmstatus | 4;
          }
          else
          {
            v158 = wk->cmstatus | 1;
          }
          goto LABEL_378;
        }
LABEL_377:
        v158 = wk->cmstatus | 2;
LABEL_378:
        v159 = wk->mv_spd.z;
        wk->cmstatus = v158;
        wk->turn_start = v117;
        wk->turn_goal = v23;
        wk->mv_spd.z = v159 * 0.0;
        goto LABEL_290;
      }
    }
    v101 = 0.0;
    if (v99 <= -135.0 || v99 >= 135.0 || v99 >= 45.0 && v99 < 135.0 || v99 <= -45.0 && v99 > -135.0)
      goto LABEL_315;
    goto LABEL_310;
  }
  if (motionID != 110)
    goto LABEL_77;
  v42 = wk->turn_goal;
  v43 = sBtlGetAtoB_LR(RotToDir, v42);
  if (v43 < -45.0)
    v43 = -45.0;
  turn_ed_motionID = wk->turn_ed_motionID;
  if (v43 > 45.0)
    v43 = 45.0;
  v45 = wk->max_mvspd.z;
  wk->mv_spd.z = v45;
  if (turn_ed_motionID != 107 && turn_ed_motionID != 109)
  {
    if (turn_ed_motionID == 108)
    {
      if (v28 < 0)
      {
        v45 = v45 * 0.3;
        wk->mv_spd.z = v45;
      }
      switch (v28)
      {
        case 0:
          v46 = 0.3;
          goto LABEL_171;
        case 1:
          goto LABEL_238;
        case 2:
          goto LABEL_239;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
          goto LABEL_170;
        default:
          goto LABEL_172;
      }
    }
    goto LABEL_172;
  }
  if (v27 <= -1.0)
  {
    v75 = 0.9;
  }
  else
  {
    if (v27 <= -0.75)
    {
      v74 = 100.0;
      goto LABEL_168;
    }
    v74 = 50.0;
    if (v27 <= -0.5 || v27 <= -0.25)
      goto LABEL_168;
    if ((v28 & 0x80000000) == 0)
      goto LABEL_169;
    v75 = 0.3;
  }
  v74 = v45 * v75;
LABEL_168:
  v45 = v74;
  wk->mv_spd.z = v74;
LABEL_169:
  switch (v28)
  {
    case 0:
LABEL_238:
      v46 = 0.2;
      goto LABEL_171;
    case 1:
LABEL_239:
      v46 = 0.1;
      goto LABEL_171;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
LABEL_170:
      v46 = 0.0;
LABEL_171:
      wk->mv_spd.z = v45 * v46;
      break;
    default:
      break;
  }
LABEL_172:
  v81 = RotToDir + v43;
  if (v81 >= 360.0)
    v81 = v81 + -360.0;
  if (v81 >= 0.0)
    v82 = v81;
  else
    v82 = v81 + 360.0;
  v83 = sBtlGetDir180(v82);
  wk->mv_rotbk = v83;
  FromEuler(0.0, v83 * 0.017453292, 0.0);
  *p_rot = vct_A;
  v87 = wk->hstatus;
  wk->front_deg = v42;
  wk->hstatus = v87 | 0x1000;
  wk->rotbk = vct_A;
  if (v27 >= 7.0)
  {
    sBtlSetAction(wk, 1, 0);
    sBtlSetMotion(wk, 0, 0, 0, 0);
    v6 = 0;
  }
  else
  {
    sBtlSetAction(wk, 2, 0);
    v6 = 1;
  }
  wk->wait_counter = 0;
  front_time = wk->front_time;
  wk->status &= ~0x100u;
  if (v27 >= 7.0)
  {
LABEL_89:
    v53 = 0;
    wk->front_time = 0.0;
    wk->MoveU_Cnt = 0;
    *(u64 *)&wk->MoveL_Cnt = 0;
    goto LABEL_91;
  }
LABEL_295:
  wk->front_time = front_time + VRF_DeltaTime;
  if (v17 >= -0.5)
    v114 = 0;
  else
    v114 = wk->MoveL_Cnt + 1;
  wk->MoveL_Cnt = v114;
  if (v17 <= 0.5)
    v115 = 0;
  else
    v115 = wk->MoveR_Cnt + 1;
  v116 = v181.z;
  wk->MoveR_Cnt = v115;
  if (v116 <= 0.5)
    wk->MoveU_Cnt = 0;
  else
    ++wk->MoveU_Cnt;
  v53 = 1;
LABEL_91:
  if (wk->battlemode != 1)
  {
    if (!v54)
    v59 = NormalProc_Kaihi(wk, v6, 0);
    if (v59 == 2)
      goto LABEL_108;
    if (!v61)
    v63 = NormalProc_Jump(wk, v6, 0);
    if (v63 == 2)
    {
LABEL_108:
      if (!v61)
    }
    else
    {
      if (!v61)
      if (CheckGuard(wk) && (wk->vstatus & 0x80) == 0)
      {
        if (wk->bGuard)
          goto LABEL_99;
      }
      if (IsSceanStop())
        goto LABEL_426;
      if (sBtlNormalProc_Huuma(wk, v6) != 2)
      {
LABEL_426:
        v67 = CheckAction_Raidou(wk);
        if (v67 == -1)
          v68 = v53;
        else
          v68 = 1;
        if (v67 == -1)
          v69 = v6;
        else
          v69 = 4;
        if ((v68 & 1) != 0)
          return v69;
        v79 = wk->next_motionID;
        if ((u32)(v79 - 105) >= 2)
        {
          if (v79 == 135)
          {
            wk->motion_UseWait2 = 0;
            wk->cmstatus |= 0x10u;
            sBtlSetMotion(wk, 104, 0, 0, 0);
            return v6;
          }
          if (v79 != 103)
            return v6;
        }
        if (front_time >= (f32)(FPS60 * 15.0))
        {
          v80 = wk->cmstatus;
          wk->motion_UseWait2 = 0;
          wk->cmstatus = v80 | 0x10;
        }
        return v6;
      }
    }
    sBtlResetGunMode(wk, 0);
    return 2;
  }
  if (!v54)
  if (CheckGuard(wk) && (wk->vstatus & 0x80) == 0)
  {
    if (wk->bGuard)
    {
LABEL_99:
      GuardInit(wk);
      return 2;
    }
  }
  if (CheckAction_Raidou(wk) != -1)
    return 4;
  return v6;
}

// 0x1fa9e80
static bool nakamamode_UnitPad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic) {
  u32 status;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v7;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v9;
  s32 mode;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t *p_nextpos;
  SBATTLE_WORK *v23;
  dds3ModelHandle_t *hModel;
  u32 v31;
  s32 v39;
  s32 MenuStatus;
  s16 v44;
  SBTLUNIT_WORK *v46;
  s32 v47;
  SBATTLE_WORK *v50;
  struct sdfVector4_t pos;
  sdfVector4_t v55;

  status = wk->status;
  if ((status & 0x10000) != 0)
  {
    if ((status & 8) == 0)
      goto LABEL_9;
  }
  LOBYTE(v8) = 0;
  return (char)v8;
LABEL_9:
  UnitMng = wk->UnitMng;
  v7 = wk->summonID[wk->summonindex[0]];
  v8 = sBtlSearchUnit_ID(UnitMng, v7);
  if (!v8)
    return (char)v8;
  v8->mv_spd.z = 0.0;
  v9 = v8;
  v8->mv_spd.x = 0.0;
  v8->mv_rot = 0.0;
  if (!!IsSceanStop())
  {
    mode = wk->mode;
    if (mode != 5)
    {
      mode = wk->mode;
      if (mode != 13)
      {
        mode = wk->mode;
        if (mode != 6)
        {
          EscapeGauge_FadeOut(v9);
          LOBYTE(v8) = 0;
          return (char)v8;
        }
      }
    }
  }
  pos = v9->pos;
  vct_A = pos;
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  p_nextpos = &v9->nextpos;
  *p_nextpos = vct_A;
  v23 = wk;
  v23->bIsNoMoveBad = 0;
  if (sBtlCheckMove_BadStatus(v9))
  {
    sBtlSummonKey(v9);
    if (EscapeGauge(v9))
      goto LABEL_119;
    sBtlPlayer_CommPad();
    hModel = v9->hModel;
    mdlGetMotionFrameF(v9->hModel);
    v31 = wk->mode - 1;
    if (v31 > 0x13)
    {
LABEL_99:
      if (v9->next_motionID == 5)
      {
        v46 = v9;
        v47 = 0;
LABEL_103:
        sBtlSetMotion(v46, v47, 0, 0, 0);
      }
      goto LABEL_116;
    }
    switch (v31)
    {
      case 0u:
        v39 = NormalProc_Nakama(v9);
        Check_SupportAction_CameraLockOn(v9);
        if (v39 == 1)
        {
          if (sBtlCheckMotionID(v9, 5))
          {
            v47 = 5;
            v46 = v9;
            goto LABEL_103;
          }
        }
        else if (!v39)
        {
          goto LABEL_99;
        }
        goto LABEL_116;
      case 1u:
        goto LABEL_116;
      case 2u:
        AtkProc_Nakama(v9);
        goto LABEL_115;
      case 4u:
        MenuStatus = sBtlGetMenuStatus();
        if (MenuStatus != 2)
        {
          if (MenuStatus == 1)
          {
            sBtlSetSummonFunc(v9);
          }
LABEL_116:
          v55.x = x;
          v55.y = y;
          v55.z = z;
          v55.w = w;
          CheckMapHit(v9, v55);
LABEL_119:
          LOBYTE(v8) = 1;
          return (char)v8;
        }
        RestartBattle();
        sBtlRestart_Scene();
        sBtlActiveAction();
        *(u32 *)wk->gstat = 0;
        sBtlResetNSTOP();
        wk->status2 &= ~2u;
        sBtlResetMidashiAnim(0);
        sBtlResetSelectAnim(0);
        v50 = wk;
        v50->s_time = 0;
        v50->menutype = 0;
        *(u32 *)v50->sgstat = 0;
        sBtlResetColor(0x80808080);
        goto LABEL_116;
      case 5u:
        UseItemProc(v9);
        goto LABEL_116;
      case 8u:
        if (IsSceanStop())
          goto LABEL_99;
        goto LABEL_116;
      case 0xAu:
        if (IsSceanStop())
          goto LABEL_99;
        GuardProc_Nakama(v9, v44);
        goto LABEL_115;
      case 0xDu:
        KaihiProc_Nakama(v9);
        goto LABEL_115;
      case 0x13u:
        SklProc_Nakama(v9);
LABEL_115:
        Check_SupportAction_CameraLockOn(v9);
        goto LABEL_116;
      default:
        goto LABEL_99;
    }
  }
  wk->bIsNoMoveBad = 1;
  sBtlPlayer_CommPad();
  Check_SupportAction_CameraLockOn(v9);
  if (wk->mode == 5)
  {
    SBTLMAIN_MODE_STOP_Task(v9);
    LOBYTE(v8) = 0;
  }
  else
  {
    sBtlSummonKey(v9);
    LOBYTE(v8) = 0;
  }
  return (char)v8;
}

// 0x1faa6d0
static s32 NormalProc_Nakama(SBTLUNIT_WORK *wk) {
  SKLID *v3;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v12;
  s64 i;
  s32 v14;
  s32 v15;
  s64 v16;
  SBATTLE_WORK *v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  s32 result;
  SBATTLE_WORK *v29;
  SBATTLE_WORK *v30;
  s32 nakama_soroUseSkill;
  SBATTLE_WORK *v33;
  s32 v34;
  SBTLACTION_WORK *actwk;
  s32 v36;
  SBATTLE_WORK *v38;
  s32 v39;
  bool v40;
  s32 v42;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 AnlogKey;
  f32 v52;
  f32 v53;
  f32 VecToDir;
  f32 v56;
  f32 v58;
  f32 v59;
  bool v60;
  f32 AtoB_LR;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 Dir180;
  sdfVector4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;

  *(u64 *)&v71.x = 0;
  *(u64 *)&v71.z = 0;
  v3 = NewSpecific(SKLID, 0x11u);
  if (wk->AttackBtn_NgTime < 1)
    goto LABEL_13;
  if (IsSceanStop())
    goto LABEL_13;
  --wk->AttackBtn_NgTime;
LABEL_13:
  major = wk->major;
  minor = wk->minor;
  VisualData = sBtlGetVisualData(major, minor);
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  v12 = 0;
  for (i = 32; i != 100; i += 4)
  {
    v14 = *(u32 *)((char *)&wk->para->haveskill->obj.klass + i);
    if (v14 && v14 != 149 && v14 != 288)
    {
      if (datCheckSkillType(v14) == 1)
        continue;
      v15 = *(u32 *)((char *)&wk->para->haveskill->obj.klass + i);
      if ((v15 & 0xFFFFFFFE) != 0x76)
      {
        v16 = (s64)(char *)v3 + 4 * v12++;
        *(u32 *)(v16 + 32) = v15;
      }
    }
  }
  if (v12 < 1)
  {
    wk->nakama_soroUseSkill = 0;
    if (!HIBYTE(wk->color))
      goto LABEL_38;
LABEL_32:
    goto LABEL_33;
LABEL_108:
    x = wk->rot.x;
    y = wk->rot.y;
    p_rot = &wk->rot;
    z = wk->rot.z;
    w = wk->rot.w;
    v73.x = x;
    v73.y = y;
    v73.z = z;
    v73.w = w;
    RotToDir = sBtlGetRotToDir(v73);
    AnlogKey = GetAnlogKey(wk, &v71);
    v52 = v71.x;
    v53 = v71.z;
    VecToDir = sBtlGetVecToDir(v52, v53);
    v56 = VecToDir;
    v58 = v56
        + sBtlGetDir180(wk->scene->camera->followUpAngle.x);
    if (v58 >= 360.0)
      v59 = v58 + -360.0;
    else
      v59 = v58;
    v60 = sBtlCheckMove(wk);
    result = 0;
    if (!v60 || AnlogKey < 48.0)
      return result;
    wk->mv_spd.z = VisualData->mv_spd;
    AtoB_LR = sBtlGetAtoB_LR(RotToDir, v59);
    if (AtoB_LR > -135.0 && AtoB_LR < 135.0)
      v63 = 0.2;
    else
      v63 = 0.3;
    v64 = AtoB_LR * v63;
    if (v64 >= -45.0)
      v65 = v64;
    else
      v65 = -45.0;
    if (v65 > 45.0)
      v65 = 45.0;
    v66 = sBtlGet360(RotToDir + v65);
    Dir180 = sBtlGetDir180(v66);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    *p_rot = vct_A;
    wk->hstatus |= 0x1000u;
    wk->rotbk = vct_A;
    wk->front_deg = v59;
    sBtlSetAction(wk, 2, 0);
    return 1;
  }
  wk->nakama_soroUseSkill = *(u32 *)((s64)(char *)v3 + 4 * wk->selectSkill + 32);
  if (HIBYTE(wk->color))
    goto LABEL_32;
LABEL_38:
  sBtlSetFade(wk, 1, 0, 0, 21);
  wk->flg &= ~0x800u;
LABEL_33:
  if (!sBtlCheckMove(wk))
    goto LABEL_108;
  v23 = wk;
  if (v23->bGuard)
  {
    wk->actwk->use_skillid = 0;
    v23 = wk;
    v23->sord_bugfix = 0;
    v23->mode = 11;
    *(u64 *)&v23->sord_st = 0;
    v23->sord_counter = 0;
    sBtlSetAction(wk, 15, 0);
    sBtlSetMotion(wk, 29, 0, 0, 0);
    v24 = wk->pos.x;
    v25 = wk->pos.y;
    v27 = wk->pos.z;
    v26 = wk->pos.w;
    v72.x = v24;
    v72.y = v25;
    v72.z = v27;
    v72.w = v26;
    sBtlPlay3DSE(0x1000Du, v72);
    return 2;
  }
  v23 = wk;
  if (v23->bRR)
    goto LABEL_61;
  v23 = wk;
  if (!v23->bRR_Assist)
  {
LABEL_63:
    v30 = wk;
    if (v30->bRU)
      goto LABEL_157;
    v30 = wk;
    if (v30->bRU_Assist)
    {
LABEL_157:
      sBtlGetSkilltbl(wk->nakama_soroUseSkill);
      nakama_soroUseSkill = wk->nakama_soroUseSkill;
      result = datCheckSkillType(nakama_soroUseSkill);
      if (result != 2)
      {
        v33 = wk;
        v34 = v33->nakama_soroUseSkill;
        if (!v34 || BadStatus == 10)
          goto LABEL_108;
        actwk = wk->actwk;
        v33 = wk;
        v34 = v33->nakama_soroUseSkill;
        actwk->use_skillid = v34;
        v33->sord_st = 1;
        v33->mode = 20;
        return 2;
      }
      return result;
    }
    v30 = wk;
    if (v30->bKaihi)
    {
      KaihiInit_Nakama(wk);
      return 2;
    }
    if (CHECK_TRIG2(32772))
    {
      v36 = v12 - 1;
      if (v12 < 1)
        goto LABEL_108;
      v38 = wk;
      v39 = v38->selectSkill - 1;
      v38->selectSkill = v39;
      if (v39 >= 0)
        goto LABEL_108;
LABEL_106:
      v38 = wk;
    }
    else
    {
      v40 = CHECK_TRIG2(32773);
      if (v12 < 1 || !v40)
        goto LABEL_108;
      v38 = wk;
      v42 = v38->selectSkill + 1;
      v38->selectSkill = v42;
      if (v42 < v12)
        goto LABEL_108;
      v36 = 0;
      goto LABEL_106;
    }
    v38->selectSkill = v36;
    goto LABEL_108;
  }
LABEL_61:
  v29 = wk;
  if (v29->sord_st)
    goto LABEL_63;
  wk->actwk->use_skillid = 149;
  v29 = wk;
  v29->sord_st = 1;
  v29->mode = 3;
  return 2;
}

// 0x1fab160
static s32 AtkProc_Nakama(SBTLUNIT_WORK *wk) {
  s32 *p_sord_counter;
  s32 sord_st;
  s32 use_skillid;
  s32 v10;
  s32 targetID;
  s32 ListID;
  SBATTLE_WORK *v17;
  s32 vstatus;
  dds3ModelHandle_t *hModel;
  SBATTLE_WORK *v22;
  s32 v23;
  f32 TargetLen;
  s64 v28;
  s32 v32;
  SBTLUNIT_WORK *pUnit;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  f32 v39;
  s32 v49;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  s32 v58;
  s32 v59;
  f32 v61;
  f32 v62;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 PosToDir;
  f32 v69;
  sdfVector4_t *p_rot;
  f32 RotToDir;
  f32 AtoB_LR;
  f32 v73;
  f32 Dir180;
  struct SDF_VU0 *v77;
  SBATTLE_WORK *v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  SBTLEFF_LISTWORK *effList;
  SBTLDMG_HITLISTWORK *hitList;
  s32 v86;
  SBTLEFF_LISTWORK *v87;
  SBTLDMG_HITLISTWORK *v88;
  s32 v90;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  s32 flg;
  sdfVector4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v103;

  p_sord_counter = &wk->sord_counter;
  ++*p_sord_counter;
  LimitRange(p_sord_counter, 0, 0x7FFF);
  sord_st = wk->sord_st;
  if (sord_st == 3)
  {
    if (sBtlCheckNextAction(wk))
    {
      v17 = wk;
      v17->mode = 1;
      *(u32 *)v17->gstat = 0;
      sBtlResetAction(wk);
      sBtlSetAction(wk, 1, 0);
      sBtlSetMotion(wk, 0, 0, 0, 0);
      vstatus = wk->vstatus;
      if ((vstatus & 2) != 0 || !HIBYTE(wk->color))
      {
        wk->vstatus = vstatus & 0xFFFFFFFD;
        sBtlSetFade(wk, 1, 0, 0, 21);
      }
      wk->flg &= ~0x800u;
    }
    goto LABEL_57;
  }
  if (sord_st == 2)
  {
    hModel = wk->hModel;
    if ((mdlGetMotionFrame(hModel) & 0x80000000) == 0)
    {
      v22 = wk;
      v23 = v22->sord_st;
      v22->sord_counter = 0;
      v22->sord_actionf = 0;
      v22->sord_st = v23 + 1;
      sBtlCheckMHTData(wk, wk->actwk->use_skillid);
    }
    goto LABEL_57;
  }
  if (sord_st != 1)
    goto LABEL_57;
  wk->actaiwk->mode = 15;
  use_skillid = wk->actwk->use_skillid;
  sBtlSetUseSkill(wk, use_skillid, 0);
  sBtlSetAction(wk, 12, 0);
  ++wk->sord_st;
  if ((sBtlGetSkilltbl(wk->actwk->use_skillid)->area & 0x4000) == 0)
  {
    targetID = wk->actaiwk->targetID;
    DecideTarget(targetID == -1, v10);
    ListID = wk->actaiwk->targetID;
    goto LABEL_44;
  }
  ListID = wk->ListID;
LABEL_44:
  sBtlSetTargetID(wk, ListID);
  TargetLen = sBtlGetTargetLen(wk);
  if (TargetLen > 800.0)
  {
    v28 = 3;
LABEL_54:
    *(u64 *)&gHomingMode = v28;
    gHomingSeDone = 0;
    FootEff(wk, 0.0, 0.0, 0.2, 4.0, 0);
    goto LABEL_57;
  }
  if (TargetLen > 300.0)
  {
    v28 = 2;
    goto LABEL_54;
  }
  if (TargetLen <= 50.0)
  {
    *(u64 *)&gHomingMode = 0;
  }
  else
  {
    *(u64 *)&gHomingMode = 1;
  }
LABEL_57:
  v32 = wk->actaiwk->targetID;
  if (v32 != -1)
  {
    v32 = wk->actaiwk->targetID;
    pUnit = wk->UnitMng->pUnitL[v32]->pUnit;
    if (pUnit)
    {
      major = wk->major;
      ++gHomingCnt;
      minor = wk->minor;
      VisualData = sBtlGetVisualData(major, minor);
      v39 = sBtlGetTargetLen(wk);
      if (v39 > 50.0)
      {
        switch (gHomingMode)
        {
          case 0:
            wk->mv_spd.z = 0.0;
            goto LABEL_143;
          case 1:
            wk->mv_spd.z = VisualData->mv_spd;
            if ((u32)(-858993459 * gHomingCnt + 429496729) <= 0x33333332)
            {
              FootEff(wk, 0.0, 0.0, 0.05, 1.5, 0);
            }
            if (v39 > 800.0)
            {
              v49 = 3;
LABEL_127:
              gHomingMode = v49;
              gHomingSeDone = 0;
              v61 = 0.2;
              v62 = 4.0;
              goto LABEL_142;
            }
            if (v39 > 300.0)
            {
              v49 = 2;
              goto LABEL_127;
            }
            goto LABEL_143;
          case 2:
            wk->mv_spd.z = 50.0;
            if ((u32)(-1431655765 * gHomingCnt + 715827882) <= 0x55555554)
            {
              FootEff(wk, 0.0, 0.0, 0.1, 2.0, 0);
              if (v39 > 800.0)
              {
LABEL_99:
                gHomingMode = 3;
                if (v39 <= 200.0)
                  goto LABEL_102;
                goto LABEL_207;
              }
            }
            else if (v39 > 800.0)
            {
              goto LABEL_99;
            }
            if (v39 <= 200.0)
            {
LABEL_102:
              if (v39 < 150.0 && (wk->vstatus & 1) == 0)
              {
                sBtlSetFade(wk, 1, 0, 0, 21);
                wk->flg &= ~0x800u;
              }
              goto LABEL_143;
            }
LABEL_207:
            if ((wk->vstatus & 2) == 0)
            {
              sBtlSetFade(wk, 2, 0, 0, 64);
              if (!gHomingSeDone)
              {
                gHomingSeDone = 1;
                x = wk->pos.x;
                y = wk->pos.y;
                z = wk->pos.z;
                w = wk->pos.w;
                v103.x = x;
                v103.y = y;
                v103.z = z;
                v103.w = w;
                sBtlPlay3DSE(0x1002Bu, v103);
              }
              flg = wk->flg;
              wk->damagecnt = 0;
              wk->flg = flg | 0x800;
            }
            goto LABEL_143;
          case 3:
            if (v39 > 300.0)
            {
              if ((wk->vstatus & 2) != 0)
                goto LABEL_136;
              sBtlSetFade(wk, 2, 0, 0, 42);
              if (!gHomingSeDone)
              {
                gHomingSeDone = 1;
                v54 = wk->pos.x;
                v55 = wk->pos.y;
                v57 = wk->pos.z;
                v56 = wk->pos.w;
                v101.x = v54;
                v101.y = v55;
                v101.z = v57;
                v101.w = v56;
                sBtlPlay3DSE(0x1002Bu, v101);
              }
              v58 = wk->flg;
              wk->damagecnt = 0;
              v59 = v58 | 0x800;
              goto LABEL_135;
            }
            if (v39 < 200.0 && (wk->vstatus & 1) == 0)
            {
              sBtlSetFade(wk, 1, 0, 0, 21);
              v59 = wk->flg & 0xFFFFF7FF;
LABEL_135:
              wk->flg = v59;
            }
LABEL_136:
            wk->mv_spd.z = 90.0;
            if ((u32)(-1431655765 * gHomingCnt + 715827882) <= 0x55555554)
            {
              v61 = 0.1;
              v62 = 2.0;
LABEL_142:
              FootEff(wk, 0.0, 0.0, v61, v62, 0);
            }
LABEL_143:
            if ((f32)(v39 + -50.0) < wk->mv_spd.z)
              wk->mv_spd.z = v39 + -50.0;
            break;
          default:
            goto LABEL_143;
        }
LABEL_145:
        v64 = wk->pos.x;
        v65 = wk->pos.z;
        v66 = pUnit->pos.x;
        v67 = pUnit->pos.z;
        PosToDir = sBtlGetPosToDir(v64, v65, v66, v67);
        v69 = sBtlGet360(PosToDir);
        p_rot = &wk->rot;
        RotToDir = sBtlGetRotToDir(wk->rot);
        AtoB_LR = sBtlGetAtoB_LR(RotToDir, v69);
        v73 = sBtlGet360(RotToDir + (f32)(AtoB_LR * 0.3));
        Dir180 = sBtlGetDir180(v73);
        wk->mv_rotbk = Dir180;
        FromEuler(0.0, Dir180 * 0.017453292, 0.0);
        *p_rot = vct_A;
        LODWORD(v77) = wk->hstatus | 0x1000;
        wk->front_deg = v69;
        wk->hstatus = (s32)v77;
        wk->rotbk = vct_A;
        goto LABEL_158;
      }
      wk->mv_spd.z = 0.0;
      if (gHomingMode == 3)
        goto LABEL_75;
      if (gHomingMode != 2)
      {
LABEL_78:
        gHomingMode = 0;
        goto LABEL_145;
      }
LABEL_75:
      FootEff(wk, 0.0, 0.0, 0.1, 2.0, 0);
      goto LABEL_78;
    }
  }
LABEL_158:
  v79 = wk;
  if (v79->sord_st < 3)
    return 2;
  if (v79->bGuard)
  {
    wk->actwk->use_skillid = 0;
    v79 = wk;
    v79->sord_bugfix = 0;
    v79->mode = 11;
    *(u64 *)&v79->sord_st = 0;
    v79->sord_counter = 0;
    sBtlSetAction(wk, 15, 0);
    sBtlSetMotion(wk, 29, 0, 0, 0);
    v80 = wk->pos.x;
    v81 = wk->pos.y;
    v83 = wk->pos.z;
    v82 = wk->pos.w;
    v102.x = v80;
    v102.y = v81;
    v102.z = v83;
    v102.w = v82;
    sBtlPlay3DSE(0x1000Du, v102);
    effList = wk->effList;
    sBtlForceDelete_ID_Summon(effList, wk);
    sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
    hitList = wk->hitList;
    sBtlClearHitC(wk->hitList, wk);
    v86 = wk->vstatus;
    if ((v86 & 2) != 0)
      goto LABEL_190;
    if (HIBYTE(wk->color))
    {
LABEL_193:
      wk->flg &= ~0x800u;
      return 2;
    }
LABEL_190:
    wk->vstatus = v86 & 0xFFFFFFFD;
    sBtlSetFade(wk, 1, 0, 0, 21);
    goto LABEL_193;
  }
  v79 = wk;
  if (v79->bKaihi)
  {
    v79 = wk;
    v87 = v79->effList;
    sBtlForceDelete_ID_Summon(v87, wk);
    sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
    v88 = wk->hitList;
    sBtlClearHitC(wk->hitList, wk);
    v90 = wk->vstatus;
    if ((v90 & 2) != 0)
      goto LABEL_196;
    if (HIBYTE(wk->color))
    {
LABEL_199:
      wk->flg &= ~0x800u;
      KaihiInit_Nakama(wk);
      return 2;
    }
LABEL_196:
    wk->vstatus = v90 & 0xFFFFFFFD;
    sBtlSetFade(wk, 1, 0, 0, 21);
    goto LABEL_199;
  }
  return 2;
}

// 0x1fac240
static s32 SklProc_Nakama(SBTLUNIT_WORK *wk) {
  s32 *p_sord_counter;
  s32 sord_st;
  s32 v8;
  s32 targetID;
  s32 ListID;
  SBATTLE_WORK *v15;
  dds3ModelHandle_t *hModel;
  SBATTLE_WORK *v19;
  s32 v20;
  SBATTLE_WORK *v21;
  s32 use_skillid;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  SBTLEFF_LISTWORK *effList;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *v30;
  SBTLDMG_HITLISTWORK *v31;
  sdfVector4_t v34;

  p_sord_counter = &wk->sord_counter;
  ++*p_sord_counter;
  LimitRange(p_sord_counter, 0, 0x7FFF);
  sord_st = wk->sord_st;
  if (sord_st != 3)
  {
    if (sord_st == 2)
    {
      hModel = wk->hModel;
      if ((mdlGetMotionFrame(hModel) & 0x80000000) == 0)
      {
        v19 = wk;
        v20 = v19->sord_st;
        v19->sord_counter = 0;
        v19->sord_actionf = 0;
        v19->sord_st = v20 + 1;
        sBtlCheckMHTData(wk, wk->actwk->use_skillid);
      }
    }
    else if (sord_st == 1)
    {
      if ((sBtlGetSkilltbl(wk->actwk->use_skillid)->area & 0x4000) != 0)
      {
        ListID = wk->ListID;
        goto LABEL_39;
      }
      else
      {
        targetID = wk->actaiwk->targetID;
        DecideTarget(targetID == -1, v8);
        ListID = wk->actaiwk->targetID;
LABEL_39:
        sBtlSetTargetID(wk, ListID);
        use_skillid = wk->actwk->use_skillid;
        sBtlSetUseSkill(wk, use_skillid, 0);
        sBtlSetAction(wk, 12, 0);
        ++wk->sord_st;
LABEL_35:
        v21 = wk;
        if (v21->sord_st < 3)
          return 2;
        goto LABEL_45;
      }
      goto LABEL_39;
    }
LABEL_34:
    goto LABEL_35;
  }
  if (!sBtlCheckNextAction(wk))
    goto LABEL_34;
  v15 = wk;
  v15->mode = 1;
  *(u32 *)v15->gstat = 0;
  sBtlResetAction(wk);
  sBtlSetAction(wk, 1, 0);
  sBtlSetMotion(wk, 0, 0, 0, 0);
  goto LABEL_35;
LABEL_45:
  if (v21->bGuard)
  {
    wk->actwk->use_skillid = 0;
    v21 = wk;
    v21->sord_bugfix = 0;
    v21->mode = 11;
    *(u64 *)&v21->sord_st = 0;
    v21->sord_counter = 0;
    sBtlSetAction(wk, 15, 0);
    sBtlSetMotion(wk, 29, 0, 0, 0);
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    v34.x = x;
    v34.y = y;
    v34.z = z;
    v34.w = w;
    sBtlPlay3DSE(0x1000Du, v34);
    effList = wk->effList;
    sBtlForceDelete_ID_Summon(effList, wk);
    sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
    hitList = wk->hitList;
    sBtlClearHitC(hitList, wk);
    return 2;
  }
  v21 = wk;
  if (v21->bKaihi)
  {
    v21 = wk;
    v30 = v21->effList;
    sBtlForceDelete_ID_Summon(v30, wk);
    sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
    v31 = wk->hitList;
    sBtlClearHitC(v31, wk);
    KaihiInit_Nakama(wk);
  }
  return 2;
}

// 0x1fad310
static void KaihiInit_Nakama(SBTLUNIT_WORK *wk) {
  sdfVector4_t *p_rot;
  f32 x;
  f32 w;
  f32 y;
  f32 z;
  u32 v9;
  f32 RotToDir;
  f32 AnlogKey;
  f32 v14;
  f32 v15;
  f32 VecToDir;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 AtoB_LR;
  f32 v24;
  f32 front_deg;
  f32 v26;
  sdfVector4_t *v28;
  f32 Dir180;
  sdfVector4_t *p_rotbk;
  s32 v38;
  sdfVector4_t v44;
  sdfVector4_t v45;

  p_rot = &wk->rot;
  x = wk->rot.x;
  wk->cmstatus = 0;
  w = wk->rot.w;
  y = wk->rot.y;
  z = wk->rot.z;
  v9 = wk->status & 0xFFFFFEFF;
  *(u64 *)&v44.x = 0;
  *(u64 *)&v44.z = 0;
  wk->status = v9;
  wk->hstatus &= ~0x20000u;
  v45.x = x;
  v45.y = y;
  v45.z = z;
  v45.w = w;
  RotToDir = sBtlGetRotToDir(v45);
  AnlogKey = GetAnlogKey(wk, &v44);
  v14 = v44.x;
  v15 = v44.z;
  VecToDir = sBtlGetVecToDir(v14, v15);
  v17 = wk->pos.z;
  v18 = wk->pos.x;
  v19 = wk->pos.y;
  v20 = 360.0 - mapGetScreenDir(v18, v19, v17, 0.0);
  if (v20 >= 360.0)
    v20 = 0.0;
  v21 = VecToDir + v20;
  if (v21 >= 360.0)
    v22 = v21 + -360.0;
  else
    v22 = v21;
  AtoB_LR = sBtlGetAtoB_LR(RotToDir, v22);
  v24 = sBtlGet360(RotToDir + AtoB_LR);
  if (AnlogKey >= 48.0)
  {
    Dir180 = sBtlGetDir180(v24);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    *p_rot = vct_A;
    p_rotbk = &wk->rotbk;
    goto LABEL_57;
    if (v38)
    {
      p_rotbk = &wk->rotbk;
      goto LABEL_57;
    }
    else
    {
      p_rotbk = &wk->rotbk;
LABEL_57:
      *p_rotbk = vct_A;
      sBtlSetAction(wk, 1, 0);
      sBtlSetMotion(wk, 5, 0, 0, 0);
      wk->kochokuCnt = 25;
      wk->damagecnt = 0;
      wk->flg |= 0x800u;
      gKaihi_BackStep = 0;
      gKaihiTotalModelen = 0.0;
      wk->hstatus |= 0x1000u;
      wk->front_deg = v24;
      goto LABEL_67;
    }
    goto LABEL_57;
  }
  front_deg = wk->front_deg;
  v26 = sBtlGetDir180(front_deg);
  wk->mv_rotbk = v26;
  FromEuler(0.0, v26 * 0.017453292, 0.0);
  *p_rot = vct_A;
  v28 = &wk->rotbk;
  *v28 = vct_A;
  sBtlSetAction(wk, 1, 0);
  sBtlSetMotion(wk, 0, 0, 0, 0);
  wk->kochokuCnt = 25;
  wk->damagecnt = 0;
  wk->flg |= 0x800u;
  gKaihi_BackStep = 1;
  gKaihiTotalModelen = 0.0;
  wk->hstatus |= 0x1000u;
LABEL_67:
  FootEff(wk, 0.0, 0.0, 0.2, 4.0, 0);
  wk->JumpAfterCnt = 0;
  wk->mode = 14;
}

// 0x1facac0
static s32 KaihiProc_Nakama(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 AnlogKey;
  f32 z;
  f32 x;
  f32 y;
  f32 v13;
  f32 v14;
  struct sdfVector4_t pos;
  f32 *p_x;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  s32 framecnt;
  bool v24;
  f32 v25;
  f32 v26;
  f32 w;
  f32 v28;
  SBATTLE_WORK *v30;
  s32 kochokuCnt;
  SBATTLE_WORK *v32;
  s32 v33;
  s32 flg;
  struct sdfVector4_t v37;
  sdfVector4_t direction;
  sdfMatrix4_t v41;
  sdfMatrix4_t v42;
  sdfVector4_t v43;
  sdfVector4_t v45;
  sdfVector4_t v46;
  sdfVector4_t v47;

  *(u64 *)&direction.x = 0;
  *(u64 *)&direction.z = 0;
  hModel = wk->hModel;
  mdlGetMotionFrameF(wk->hModel);
  AnlogKey = GetAnlogKey(wk, &direction);
  if ((u32)(wk->actwk->framecnt - 22) < 0xFFFFFFEE)
  {
    z = 0.0;
    wk->mv_spd.z = 0.0;
    goto LABEL_12;
  }
  if (!gKaihi_BackStep)
  {
    wk->mv_spd.z = 35.0;
    z = 35.0;
    goto LABEL_12;
  }
  wk->mv_spd.z = -35.0;
  z = -35.0;
  z = wk->mv_spd.z;
LABEL_12:
  gKaihiTotalModelen = gKaihiTotalModelen + z;
  if (!(gKaihi_BackStep || wk->mv_spd.z <= 0.0 || AnlogKey <= 48.0))
  {
    x = wk->pos.x;
    y = wk->pos.y;
    v13 = wk->pos.z;
    v14 = mapGetScreenDir(x, y, v13, 0.0) * -0.017453292;
    sub_1949280(0, v14);
    v37 = direction;
    vct_A = v37;
    get_transpose(&v42, &mtx_A, 0);
    v41 = v42;
    v43 = op_Multiply_60923920(&v41, vct_A, 0);
    vct_A = v43;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_A);
    pos = wk->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    v19 = p_x[4];
    v20 = p_x[5];
    v22 = p_x[6];
    v21 = p_x[7];
    v45.x = v19;
    v45.y = v20;
    v45.z = v22;
    v45.w = v21;
    sBtlGetRotate_Kaihi(wk, v45);
    v46.x = v19;
    v46.y = v20;
    v46.z = v22;
    v46.w = v21;
    sBtlCheckRotSpd(wk, v46);
  }
  framecnt = wk->actwk->framecnt;
  if (framecnt == 1)
  {
    sBtlSetFade(wk, 2, 0, 0, 16);
    v25 = wk->pos.x;
    v26 = wk->pos.y;
    v28 = wk->pos.z;
    w = wk->pos.w;
    v47.x = v25;
    v47.y = v26;
    v47.z = v28;
    v47.w = w;
    sBtlPlay3DSE(0x1002Bu, v47);
    framecnt = wk->actwk->framecnt;
    if (framecnt != 18)
    {
LABEL_37:
      v24 = (u32)framecnt > 0xB;
      if (framecnt > 11)
        goto LABEL_38;
LABEL_49:
      if (v24 || ((1 << framecnt) & 0x920) == 0)
        goto LABEL_58;
      goto LABEL_51;
    }
  }
  else if (framecnt != 18)
  {
    goto LABEL_37;
  }
  sBtlSetFade(wk, 1, 0, 0, 21);
  framecnt = wk->actwk->framecnt;
  v24 = (u32)framecnt > 0xB;
  if (framecnt <= 11)
    goto LABEL_49;
LABEL_38:
  if ((u32)framecnt <= 0x14 && ((1 << framecnt) & 0x124000) != 0)
  {
LABEL_51:
    FootEff(wk, 0.0, 0.0, 0.1, 2.0, 0);
    framecnt = wk->actwk->framecnt;
  }
  if (framecnt == 22)
  {
    FootEff(wk, 0.0, 0.0, 0.1, 2.0, 0);
  }
LABEL_58:
  v30 = wk;
  kochokuCnt = v30->kochokuCnt;
  if (kochokuCnt)
  {
    v30 = wk;
    kochokuCnt = v30->kochokuCnt;
    v30->kochokuCnt = kochokuCnt - 1;
  }
  v32 = wk;
  v33 = v32->kochokuCnt;
  if (!v33)
  {
    flg = wk->flg;
    wk->mv_spd.z = 0.0;
    wk->flg = flg & 0xFFFFF7FF;
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    sBtlSetMotion(wk, 0, 0, 0, 0);
    return 2;
  }
  if (v33 != 20)
    return 2;
  v32 = wk;
  if (v32->bKaihi)
  {
    KaihiInit_Nakama(wk);
  }
  return 2;
}

// 0x1fac880
static s32 GuardProc_Nakama(SBTLUNIT_WORK *wk, s16 mode) {
  SBATTLE_WORK *v5;
  s32 kochokuCnt;
  s32 vstatus;
  SBATTLE_WORK *v8;

  v5 = wk;
  kochokuCnt = v5->kochokuCnt;
  if (kochokuCnt >= 1)
  {
    v5 = wk;
    kochokuCnt = v5->kochokuCnt;
    v5->kochokuCnt = kochokuCnt - 1;
  }
  vstatus = wk->vstatus;
  wk->status |= 0x100u;
  wk->vstatus = vstatus | 0x80;
  if (HIBYTE(wk->color))
  {
    goto LABEL_12;
  }
  sBtlSetFade(wk, 1, 0, 0, 21);
  wk->flg &= ~0x800u;
LABEL_12:
  v8 = wk;
  if (v8->bGuard)
    return 2;
  if (v8->kochokuCnt)
    return 2;
  sBtlResetAction(wk);
  sBtlSetUseSkill(wk, 0, 0);
  sBtlSetMotion(wk, 0, 0, 0, 0);
  return 2;
}

// 0x1f6f7d0
void sBtlInitSetsuma(void) {
  s16 para;
  s32 v3;

  para = sBtlGetSkilltbl(1299)->para;
  gJustFrame = (f32)para;
  v3 = sBtlGetSkilltbl(1300)->para;
  gJustFrameEx = (f32)v3;
  wk->setsuma_BS_LASTB3_cnt = 0;
}

// 0x1f98460
void sBtlSetSetsuma_SkillStart(SBTLUNIT_WORK *wk, SKLID skillid) {
  if (skillid > 1295)
  {
    if ((u32)(skillid - 1296) >= 2)
    {
      if (skillid == 1304 || skillid == 1334 && wk->setsuma_rowhit_skillid == 1334)
      {
        wk->setsuma_rowhit_skillid = skillid;
        return;
      }
      goto LABEL_10;
    }
LABEL_9:
    *(u16 *)&wk->setsuma_rowhit_done = 0;
    return;
  }
  if ((u32)(skillid - 669) < 2 || skillid == 176)
    goto LABEL_9;
LABEL_10:
  if (wk->setsuma_rowhit_done)
  {
    wk->setsuma_rowhit_skillid = skillid;
    wk->setsuma_rowhit_done = 0;
  }
  else
  {
    *(u16 *)&wk->setsuma_rowhit_done = 0;
    wk->setsuma_rowhit_skillid = skillid;
  }
}

// 0x1fad9d0
void sBtlSetSetsuma_SkillHit(SBTLUNIT_WORK *wk, SKLID skillid) {
  if (skillid <= 670)
  {
    if ((u32)(skillid - 669) < 2 || skillid == 176)
      return;
  }
  else if ((u32)(skillid - 1296) <= 0x17 && ((1 << (skillid - 16)) & 0xC0007B) != 0)
  {
    return;
  }
  if (wk->battlemode != 1 && wk->setsuma_rowhit_skillid == skillid)
  {
    if (!wk->setsuma_rowhit_done)
    {
      if ((sub_1FBC9F0(0, *(u64 *)&skillid) & 1) != 0)
        wk->flg |= 0x1000u;
    }
    if ((u32)(skillid - 690) > 0xB || ((1 << (skillid + 78)) & 0x847) == 0)
      wk->setsuma_rowhit_done = 1;
  }
}

// 0x1fadb10
void sBtlSetSetsuma_BS_LASTB3_Hirumi(SBTLUNIT_WORK *wk) {
  s32 devilid;

  if (wk)
  {
    devilid = (u16)wk->para->devilid;
    if (devilid == 315 || devilid == 260)
      wk->flg |= 0x400000u;
  }
}

// 0x1fadb40
void sBtlSetSetsuma_PlayerDamage(SBTLUNIT_WORK *wk) {
  wk->setsuma_rowhit_skillid = 0;
  *(u16 *)&wk->setsuma_rowhit_done = 0;
}

// 0x1f9af90
void sBtlSetSetsuma_PlayerGuard(SBTLUNIT_WORK *wk) {
  wk->setsuma_rowhit_skillid = 0;
  *(u16 *)&wk->setsuma_rowhit_done = 0;
}

// 0x1fadb50
void sBtlSetSetsuma_EnemyUse(SBTLUNIT_WORK *wkEnemy) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v6;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v6 = sBtlSearchUnit_ID(UnitMng, playerID);
  v6->flg |= 0x4000u;
}

// 0x1fadc00
bool sBtlChkSetsuma_Just(s32 *_Frame, SKLID _skillid) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  f32 fuyoeff;
  SBTLUNIT_WORK *v10;
  SBTLSKILLP_TBL *Skilltbl;
  f32 weapontype;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v16;
  s32 motionno;
  bool result;
  bool v19;
  s32 v22;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  fuyoeff = 0.0;
  v10 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!skillid)
  {
    weapontype = 0.0;
    goto LABEL_13;
  }
  Skilltbl = sBtlGetSkilltbl(skillid);
  if (Skilltbl)
  {
    weapontype = 0.0;
    if ((Skilltbl->flg2 & 0x8000000) != 0)
    {
      fuyoeff = Skilltbl->fuyoeff;
      weapontype = Skilltbl->weapontype;
      hModel = v10->hModel;
      goto LABEL_15;
    }
LABEL_13:
    hModel = v10->hModel;
    goto LABEL_15;
  }
  weapontype = 0.0;
  hModel = v10->hModel;
LABEL_15:
  MotionFrameF = mdlGetMotionFrameF(hModel);
  *Frame = 0;
  v16 = MotionFrameF;
  motionno = v10->motionno;
  if (motionno == 41)
    goto LABEL_25;
  if (motionno == 94)
  {
    if (wk->mode == 15)
      goto LABEL_25;
    return 0;
  }
  result = 0;
  if (motionno != 42)
    return result;
LABEL_25:
  v19 = v16 <= 0.0;
  if (!sBtlGetSpiritSkillChk(1381))
  {
    if (v19)
      return 0;
    if (v16 > (f32)((f32)(weapontype * 0.5) + (f32)(gJustFrame * 0.5)))
      return 0;
    goto LABEL_38;
  }
  if (v19)
    return 0;
  if (v16 > (f32)((f32)(fuyoeff * 0.5) + (f32)(gJustFrameEx * 0.5)))
    return 0;
LABEL_38:
  result = 1;
  v22 = (f32)(v16 + v16);
  if ((f32)(v16 + v16) == INFINITY)
    v22 = 0x80000000;
  *Frame = v22;
  return result;
}

// 0x1f76e20
void sBtlResetSetsuma_BossTalk(SBTLUNIT_WORK *wk) {
  void *Instance;

  wk->flg &= 0xFFBD0FFF;
  if (sBtlIsSetsumaPadStop())
  {
    Instance = get_Instance(0);
    SetumaButton(Instance, 0, 0);
    sBtlEndSetsumaPadStop();
    dds3PostSlowClear();
  }
}

// 0x1f7b320
static void CalcSetsuma(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  s32 flg;
  s32 v7;
  bool v8;
  bool IsSceanStop;
  s32 v10;
  s32 v11;
  SBATTLE_WORK *v13;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 devilid;
  s32 v17;
  s32 v20;
  s32 PlayerID;
  void *Instance;
  f32 v24;
  s32 v25;
  s32 KaihiSetsuma_SkillId;
  _BOOL4 v29;
  SBATTLE_WORK *v33;
  s32 v34;
  void *v35;
  s32 v36;
  u32 v37;
  s32 v39;
  void *v40;
  void *v42;
  void *v43;
  s32 Frame;

  Frame = 0;
  if (wk->battlemode == 1)
    return;
  if (sbtlplayertblChkNG_TutoEtc(0, 1299, 0))
    return;
  v5 = wk;
  if (v5->bIsNoMoveBad)
    return;
  v5 = wk;
  if (!v5->cmbSkl->bRun)
  {
    if (!IsSceanStop() || sBtlIsSetsumaPadStop())
    {
      if (!IsSceanStop())
      {
        flg = wk->flg;
        if ((flg & 0x100000) != 0)
        {
          v7 = wk->setsuma_b_muteki_cnt - 1;
          v8 = wk->setsuma_b_muteki_cnt == 1;
          wk->setsuma_b_muteki_cnt = v7;
          if (v7 < 0 || v8)
            wk->flg = flg & 0xFFEFFFFF;
        }
      }
      IsSceanStop = IsSceanStop();
      v10 = wk->flg;
      if (!IsSceanStop && (v10 & 0x200000) != 0)
      {
        v11 = wk->setsuma_a_muteki_cnt - 1;
        v8 = wk->setsuma_a_muteki_cnt == 1;
        wk->setsuma_a_muteki_cnt = v11;
        if (v11 < 0 || v8)
        {
          v10 &= ~0x200000u;
          wk->flg = v10;
        }
      }
      if ((v10 & 0x400000) == 0)
      {
        v13 = wk;
LABEL_52:
        v13->setsuma_BS_LASTB3_cnt = 0;
        if ((wk->flg & 0x1000) == 0)
          goto LABEL_85;
LABEL_53:
        targetID = wk->actaiwk->targetID;
        if (targetID == -1)
          goto LABEL_65;
        targetID = wk->actaiwk->targetID;
        UnitMng = wk->UnitMng;
        if (sBtlSearchUnit_ID(UnitMng, targetID) && ((devilid = (u16)wk->para->devilid, devilid == 315) || devilid == 260))
        {
          v17 = wk->flg;
          wk->flg = v17 & 0xFFBFEFFF;
          wk->setsuma_BS_LASTB3_cnt = 0;
          if ((v17 & 0x400000) == 0)
            goto LABEL_85;
        }
        else
        {
LABEL_65:
          wk->flg &= 0xFFBFEFFF;
          wk->setsuma_BS_LASTB3_cnt = 0;
        }
        if (sBtlChkSceneEnemyLive() && (wk->flg & 0x8000) == 0)
        {
          if (!sBtlPlayerCheckRSpirit())
          {
            v20 = wk->flg;
            if ((v20 & 0x8000) == 0)
            {
              wk->flg = v20 | 0x8000;
              wk->setsuma_rowhit_hirameki = 0;
              PlayerID = sBtlGetPlayerID();
              Add(PlayerID, 0.0, -120.0, 0.0, 0);
              Instance = get_Instance(0);
              SetumaButton(Instance, 1, 0);
              v24 = 0.1;
              if (wk->motionno == 158)
                v24 = 0.002;
              sBtlSetSetsumaPadStop(0, 60, v24);
              dds3PostSlowStart(0x3Cu);
            }
          }
        }
LABEL_85:
        v25 = wk->flg;
        if ((v25 & 0x2000) != 0)
        {
          wk->flg = v25 & 0xFFFFDFFF;
          if ((v25 & 0x8000) == 0)
          {
            if (!sBtlPlayerCheckRSpirit() && (wk->flg & 0x10000) == 0)
            {
              KaihiSetsuma_SkillId = wk->KaihiSetsuma_SkillId;
              v29 = sBtlChkSetsuma_Just(&Frame, KaihiSetsuma_SkillId);
              if (sBtlIsSetumaActive() && v29)
              {
                if (sBtlChkSceneEnemyLive())
                {
                  wk->setsuma_rowhit_hirameki = 0;
                  v33 = wk;
                  wk->flg |= 0x8000u;
                  v33->KaihiSetsuma = 1;
                  v34 = sBtlGetPlayerID();
                  Add(v34, 0.0, -120.0, 0.0, 0);
                  v35 = get_Instance(0);
                  SetumaButton(v35, 1, 0);
                  sBtlSetSetsumaPadStop(0, 60, 0.1);
                  dds3PostSlowStart(0x3Cu);
                }
              }
            }
          }
        }
        v36 = wk->flg;
        if ((v36 & 0x4000) != 0)
        {
          v37 = v36 & 0xFFFFBFFF;
          wk->flg = v36 & 0xFFFFBFFF;
          if ((v36 & 0x20000) == 0)
          {
            wk->flg = v36 & 0xFFFD3FFF | 0x28000;
            wk->setsuma_rowhit_hirameki = 0;
            v39 = sBtlGetPlayerID();
            Add(v39, 0.0, -120.0, 0.0, 0);
            v40 = get_Instance(0);
            SetumaButton_Kaya(v40, 1, 0);
            sBtlSetSetsumaPadStop(0, gEnemyStopTime, 0.1);
            dds3PostSlowStart(gEnemyStopTime);
            v37 = wk->flg;
          }
        }
        else
        {
          v37 = wk->flg;
        }
        if ((v37 & 0x20000) != 0)
        {
          if (!sBtlIsSetsumaPadStop())
          {
            wk->flg &= 0xFFFD7FFF;
            v43 = get_Instance(0);
            SetumaButton(v43, 0, 0);
            sBtlEndSetsumaPadStop();
            dds3PostSlowClear();
            sBtlSetFirstAtk(1318);
          }
        }
        else if ((v37 & 0x8000) != 0 && !sBtlIsSetsumaPadStop())
        {
          wk->flg = wk->flg & 0xFFEF7FFF | 0x100000;
          wk->setsuma_b_muteki_cnt = 60;
          v42 = get_Instance(0);
          SetumaButton(v42, 0, 0);
          sBtlEndSetsumaPadStop();
          dds3PostSlowClear();
        }
        return;
      }
      if ((v10 & 0x1000) != 0)
      {
        goto LABEL_42;
      }
      else
      {
        ++wk->setsuma_BS_LASTB3_cnt;
LABEL_42:
        v13 = wk;
        if (v13->setsuma_BS_LASTB3_cnt < 121)
          goto LABEL_43;
        goto LABEL_49;
      }
      v13 = wk;
      if (v13->setsuma_BS_LASTB3_cnt < 121)
      {
LABEL_43:
        if ((wk->flg & 0x1000) == 0)
          goto LABEL_85;
        goto LABEL_53;
      }
LABEL_49:
      wk->flg &= ~0x400000u;
      goto LABEL_52;
    }
  }
}

// 0x1faded0
void sBtlSetEnemySetsumaStopTime(s32 _Time) {
  gEnemyStopTime = Time;
  return;
}

// 0x1f76fe0
SKLID sBtlInputChkSetsuma(SBTLUNIT_WORK *wk) {
  s32 flg;
  void *Instance;
  s32 v7;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v12;
  s32 devilid;
  s32 HpLowTarget_BS_ITIMOK;

  flg = wk->flg;
  if ((flg & 0x8000) == 0)
    return 0;
  wk->flg = flg & 0xFFFF7FFF;
  Instance = get_Instance(0);
  SetumaButton(Instance, 0, 0);
  v7 = wk->flg;
  if ((v7 & 0x20000) != 0)
  {
    wk->flg = v7 & 0xFFFDFFFF;
    return 1319;
  }
  sBtlSetNextTarget_Setsuma(wk);
  targetID = wk->actaiwk->targetID;
  if (targetID == -1)
    goto LABEL_28;
  targetID = wk->actaiwk->targetID;
  UnitMng = wk->UnitMng;
  v12 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v12)
    goto LABEL_28;
  devilid = (u16)v12->para->devilid;
  if (devilid == 290 || devilid == 297)
  {
    if (v12->Itimoku_CloseEye)
    {
      HpLowTarget_BS_ITIMOK = sBtlGetHpLowTarget_BS_ITIMOK(wk);
      if (HpLowTarget_BS_ITIMOK != -1)
        wk->actaiwk->targetID = HpLowTarget_BS_ITIMOK;
    }
  }
  else if ((devilid & 0xFFFC) == 0x138)
  {
    return 1300;
  }
LABEL_28:
  if (gSetsumaIdx == 2)
  {
    gSetsumaIdx = 0;
    return 1301;
  }
  else if (gSetsumaIdx == 1)
  {
    gSetsumaIdx = 2;
    return 1300;
  }
  else
  {
    if (gSetsumaIdx)
      return 0;
    gSetsumaIdx = 1;
    return 1299;
  }
}

// 0x1f76f00
bool sBtlCheckSetsuma(void) {
  return wk->mode == 17;
}

// 0x1fae270
bool sBtlCheckSetsumaEnd(void) {
  if (wk->mode != 17)
    return 0;
  return gStep != 0;
}

// 0x1fae340
bool sBtlCheckSetsuma_Kaya(f32 *_X, f32 *_Y, f32 *_Z) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v13;
  s32 use_skillid;
  s32 v15;
  s32 v16;

  *X = 0.0;
  *Y = 0.0;
  *Z = 0.0;
  if (wk->mode != 17)
    return 0;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v13 = sBtlSearchUnit_ID(UnitMng, playerID);
  use_skillid = v13->actwk->use_skillid;
  if (use_skillid == 1318)
  {
    v16 = -1027080192;
    v15 = -1035468800;
    goto LABEL_16;
  }
  if (use_skillid != 1319)
    return 0;
  v15 = 0;
  v16 = -1014235136;
LABEL_16:
  *(u32 *)X = v15;
  *Y = v13->pos.y;
  *(u32 *)Z = v16;
  return 1;
}

// 0x1fae4c0
static void SetTargetMagPos(SBTLUNIT_WORK *wk, bool _HelperUse) {
  SBTLACTAI_WORK *actaiwk;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  u32 v12;
  u64 v13;
  s32 v14;
  f32 x;
  s64 v18;
  evtUnitHandle_t *hEveUnit;
  long f64 v21;
  u16 major;
  s32 minor;
  f32 v24;
  struct sdfVector4_t vct_A_local;

  actaiwk = wk->actaiwk;
  vct_A_local = (struct sdfVector4_t)0;
  targetID = actaiwk->targetID;
  if (targetID == -1)
    goto LABEL_19;
  UnitMng = wk->UnitMng;
  v9 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (v9)
  {
    v10 = v9;
    sBtlGetUnitHelperPos(v10, 1);
    v12 = v10->para->devilid - 258;
    vct_A_local = vct_A;
    if (v12 <= 0x39)
    {
      if (((1 << v12) & 0xC0000000000002LL) != 0)
      {
        v13 = 0xC416000000000000LL;
        v14 = 1143930880;
        goto LABEL_26;
      }
      if (((1 << v12) & 0x100000000000001LL) != 0)
      {
        v13 = 0xC3FA000000000000LL;
        v14 = 1148846080;
        goto LABEL_26;
      }
      if (((1 << v12) & 0x200000000000004LL) != 0)
      {
        v13 = 0xC348000000000000LL;
        v14 = 1147207680;
LABEL_26:
        LODWORD(vct_A_local.z) = v14;
        *(u64 *)&vct_A_local.x = v13;
        goto LABEL_27;
      }
    }
    hEveUnit = v10->hEveUnit;
    if (hEveUnit)
    {
      if (HelperUse)
      {
        if (!sdfModelGetMarkPos(hEveUnit->Model->modelRoot, 1))
          sdfModelGetMarkPos(v10->hEveUnit->Model->modelRoot, 0);
        sub_1B335A0(&vct_A_local, 0, v21);
      }
      else
      {
        major = v10->major;
        minor = v10->minor;
        v24 = v10->pos.y
            + (f32)(sBtlGetVisualData(major, minor)->nml->height * -0.5);
        vct_A_local.x = v10->pos.x;
        vct_A_local.y = v24;
        vct_A_local.z = v10->pos.z;
      }
    }
LABEL_27:
    x = vct_A_local.x;
    v18 = *(u64 *)&vct_A_local.y;
    gTargetMagX = x;
    *(u64 *)&gTargetMagY = v18;
    goto LABEL_20;
  }
LABEL_19:
LABEL_20:
  gTargetMagWait = 1;
}

// 0x1fae840
static void BeginSetsuma(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  void *Instance;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v12;
  s32 flg;
  SBTLUNIT_WORK *v15;
  s32 use_skillid;
  u32 status;

  if (wk->actaiwk->targetID == -1 && IsAction(5))
  {
    actaiwk = wk->actaiwk;
    actaiwk->targetID = sBtlGetHpLowTarget(wk);
  }
  sBtlBS_MISHAK_Action_Hiru_Cancel();
  Instance = get_Instance(0);
  RememberIconState(Instance, 0);
  SetTargetMagPos(wk, 1);
  sBtlPlayerPushAllPosRotDispHit();
  sBtlPlayerBgnWaitALL_Spirit(wk, 1);
  sBtlPlayerSetTateHitEnemy();
  sBtlPlayerScrWarp_MutekiOff_And_Push();
  targetID = wk->actaiwk->targetID;
  if (targetID == -1)
    goto LABEL_27;
  UnitMng = wk->UnitMng;
  v12 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v12)
    goto LABEL_27;
  flg = v12->flg;
  v15 = v12;
  v12->damagecnt = 0;
  v12->katana_hit_cnt = 0;
  v12->YukaDamageSkipCnt = 0;
  v12->damage_eff_tgt_cnt = 0;
  v12->flg = flg & 0xFFFFF7FD;
  v12->status = v12->status & 0xFFFFBFFE | 1;
  if (v12->actwk->status != 9)
  {
    sBtlSetAction(v15, 2, 0);
    sBtlEndAction(v15);
  }
LABEL_27:
  sBtlPlayerSetEnemyDrawOnOff(0);
  sBtlPlayerSetNakamaDrawOnOff(0);
  sBtlResetCharge(wk, 0);
  StopBattle();
  sBtlEndSetsumaPadStop();
  dds3PostSlowClear();
  use_skillid = wk->actwk->use_skillid;
  if (use_skillid == 1319)
  {
    sBtlResetMutekiColor(wk);
    goto LABEL_45;
  }
  if (use_skillid != 1318)
    goto LABEL_46;
  wk->next_motion_not_hokan = 1;
  sBtlSetMotion(wk, 0, 0, 0, 0);
  wk->vstatus |= 0x1000u;
LABEL_45:
  sBtlSetTargetEnemyDrawOnOff(wk, 1);
LABEL_46:
  sBtlStatusBitOn(wk, 0x4010u);
  status = wk->status;
  wk->YukaDamageSkipCnt = 0;
  wk->status = status | 1;
  dds3StopQuake();
  BS_MATORY_DELETE();
  *(u64 *)&gStep = 0;
  gStepTime = 0.0;
  *(u16 *)&gLastDead = 0;
  gDeadEventUse = 0;
  *(u64 *)&gKayaCnt = 0x3F80000000000000LL;
}

// 0x1faeee0
void sBtlBeginSetsuma_EX(SBTLUNIT_WORK *wk) {
  s64 v3;
  f32 v4;
  f32 *p_x;
  sdfVector4_t *p_pos;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rotbk;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLDMG_HITLISTWORK *hitList;
  void *Instance;
  SBATTLE_WORK *v23;
  u8 v24;
  s32 use_skillid;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v29;
  SBTLUNIT_WORK *v31;
  SBTLUNIT_LISTWORK *v39;
  s32 v40;
  SBTLUNIT_WORK *v41;
  SBTLUNIT_WORK *v43;
  void *v47;
  void *v48;
  void *mDof;
  void *monitor;
  void *v52;
  intptr_t m_CachedPtr;
  void *v54;
  UnityEngine_Object_c *klass;
  void *v56;
  void *v57;
  void *v58;
  void *v59;
  void *v60;
  UnityEngine_Object_c *v61;
  void *v62;
  intptr_t v63;
  void *v64;
  void *v65;
  void *v66;
  f32 ZeroZ;
  s64 ZeroY;
  sdfVector4_t v69;

  ZeroY = 0;
  ZeroZ = 0.0;
  sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, &ZeroZ);
  v3 = ZeroY;
  v4 = ZeroZ;
  p_x = &vf00.x;
  p_x[4] = *((f32 *)&v3 + 1);
  *((u32 *)p_x + 5) = v3;
  p_x[6] = v4;
  p_x[7] = 0.0;
  p_pos = &wk->pos;
  *p_pos = vct_A;
  FromEuler(0.0, 0.0, 0.0);
  p_rot = &wk->rot;
  *p_rot = vct_A;
  p_rotbk = &wk->rotbk;
  *p_rotbk = vct_A;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v69.x = x;
  v69.y = y;
  v69.z = z;
  v69.w = w;
  dds3SetPosPoseSet(&wk->pBasic, v69);
  dds3SetRotPoseSet(&wk->pBasic, wk->rot);
  sBtlResetMutekiColor(wk);
  sBtlPushCamera();
  sBtlForceDeleteAll(0);
  sBtlForceDeleteAll_TimeStopSkill(0, 0);
  hitList = wk->hitList;
  sBtlReleaseHitC_List(hitList, 1u);
  sBtlAnimListClr();
  sBtlPlayerDeleteFootEff();
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  DeleteAll_Skill();
  Instance = get_Instance(0);
  ClrCallMark(Instance, 0);
  sBtlPlayerClrAllUnit_HitBack();
  v23 = wk;
  if (v23->encountno == 58)
    v24 = 1;
  else
    v24 = 3;
  v23 = wk;
  sBtlReleaseSTP_List(v23->stpList, v24);
  dds3StopQuake();
  use_skillid = wk->actwk->use_skillid;
  if (use_skillid != 1319)
  {
    if (use_skillid != 1318)
      goto LABEL_83;
    *(u64 *)&gKayaEnemyPosX = 0;
    UnitMng = wk->UnitMng;
    targetID = wk->actaiwk->targetID;
    v29 = sBtlSearchUnit_ID(UnitMng, targetID);
    if (v29)
    {
      v31 = v29;
      sBtlBS_LASTB1_Action_Setu_ResetWince(v31);
      v31->next_motion_not_hokan = 1;
    }
    sBtlSetTargetEnemyDrawOnOff(wk, 1);
    sBtlSetTargetEnemyPosRot(wk, gKayaEnemyPosX, 0.0, gKayaEnemyPosZ, 0.0);
    sBtlSetTargetEnemyMotion(wk, 38);
    sBtlSetTargetEnemyTheWorld(wk, 1);
    goto LABEL_82;
  }
  *(u64 *)&gKayaEnemyPosX = 0x441B000000000000LL;
  v39 = wk->UnitMng;
  v40 = wk->actaiwk->targetID;
  v41 = sBtlSearchUnit_ID(v39, v40);
  if (v41)
  {
    v43 = v41;
    sBtlBS_LASTB1_Action_Setu_ResetWince(v43);
    v43->next_motion_not_hokan = 1;
  }
  sBtlSetTargetEnemyDrawOnOff(wk, 1);
  sBtlSetTargetEnemyPosRot(wk, gKayaEnemyPosX, 0.0, gKayaEnemyPosZ, 0.0);
  sBtlSetTargetEnemyMotion(wk, 40);
  sBtlSetTargetEnemyTheWorld(wk, 1);
  v47 = get_Instance(0);
  RememberIconState(v47, 0);
LABEL_82:
  sBtlPlayerSetEnemyHPDrawOnOff(0);
  sBtlPlayerSetNakamaHPDrawOnOff(0);
LABEL_83:
  v48 = get_Instance(0);
  if (!op_Inequality(v48, 0, 0))
    return;
  mDof = v48->mDof;
  if (!op_Inequality(v48->mDof, 0, 0))
    return;
  switch (wk->actwk->use_skillid)
  {
    case 0x513:
    case 0x515:
    case 0x526:
      monitor = mDof[2].monitor;
      v52 = Allocate(UnityEngine_Rendering_Universal_DepthOfFieldModeParameter);
      _ctor(v52, 1, 1, 0);
      (*(*(u64 *)monitor + 440))(monitor, v52, *(u64 *)(*(u64 *)monitor + 448));
      m_CachedPtr = mDof[2].m_CachedPtr;
      v54 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v54, 5.0, 1, 0);
      (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v54, *(u64 *)(*(u64 *)m_CachedPtr + 448));
      klass = mDof[3].klass;
      v56 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v56, 20.0, 1, 0);
      (*(klass->_1.image + 55))(klass, v56, *((u64 *)klass->_1.image + 56));
      v57 = mDof[3].monitor;
      v58 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v58, 1.5, 1, 0);
      (*(*(u64 *)v57 + 440))(v57, v58, *(u64 *)(*(u64 *)v57 + 448));
      (*(*(u64 *)mDof[3].monitor + 408))(mDof[3].monitor, 1, *(u64 *)(*(u64 *)mDof[3].monitor + 416));
      goto LABEL_100;
    case 0x514:
      v59 = mDof[2].monitor;
      v60 = Allocate(UnityEngine_Rendering_Universal_DepthOfFieldModeParameter);
      _ctor(v60, 2, 1, 0);
      (*(*(u64 *)v59 + 440))(v59, v60, *(u64 *)(*(u64 *)v59 + 448));
      v61 = mDof[4].klass;
      v62 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v62, 1.0, 1, 0);
      (*(v61->_1.image + 55))(v61, v62, *((u64 *)v61->_1.image + 56));
      v63 = mDof[4].m_CachedPtr;
      v64 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v64, 38.0, 1, 0);
      (*(*(u64 *)v63 + 440))(v63, v64, *(u64 *)(*(u64 *)v63 + 448));
      v65 = mDof[4].monitor;
      v66 = Allocate(UnityEngine_Rendering_FloatParameter);
      _ctor(v66, 3.7, 1, 0);
      (*(*(u64 *)v65 + 440))(v65, v66, *(u64 *)(*(u64 *)v65 + 448));
LABEL_100:
      SetForceActiveDofSetting(v48, 1, 0);
      break;
    default:
      return;
  }
}

// 0x1faff00
void sBtlSetDevilID_EnemyDrawOnOff(s32 _DevilID, bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 vstatus;
  dds3Basic_t *pBasic;
  f32 x;
  f32 z;
  f32 v13;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && pUnit->para->devilid == DevilID)
    {
      vstatus = pUnit->vstatus;
      if (OnOff)
      {
        pUnit->JumpOfsPos.y = 0.0;
        pBasic = pUnit->pBasic;
        x = pUnit->JumpOfsPos.x;
        pUnit->vstatus = vstatus & 0xFEFFEFFF;
        z = pUnit->JumpOfsPos.z;
        v13 = 0.0;
      }
      else
      {
        pBasic = pUnit->pBasic;
        x = pUnit->JumpOfsPos.x;
        pUnit->vstatus = vstatus | 0x1001000;
        pUnit->JumpOfsPos.y = 5000.0;
        z = pUnit->JumpOfsPos.z;
        v13 = 5000.0;
      }
      dds3UnitObjectBasicSetJumpOfsPos(pBasic, x, v13, z);
      return;
    }
  }
}

// 0x1faed20
void sBtlSetTargetEnemyDrawOnOff(SBTLUNIT_WORK *wk, bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 vstatus;
  dds3Basic_t *pBasic;
  f32 x;
  f32 z;
  f32 v13;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && wk->actaiwk->targetID == pUnit->ListID)
    {
      vstatus = pUnit->vstatus;
      if (OnOff)
      {
        pUnit->JumpOfsPos.y = 0.0;
        pBasic = pUnit->pBasic;
        x = pUnit->JumpOfsPos.x;
        pUnit->vstatus = vstatus & 0xFEFFEFFF;
        z = pUnit->JumpOfsPos.z;
        v13 = 0.0;
      }
      else
      {
        pBasic = pUnit->pBasic;
        x = pUnit->JumpOfsPos.x;
        pUnit->vstatus = vstatus | 0x1001000;
        pUnit->JumpOfsPos.y = 5000.0;
        z = pUnit->JumpOfsPos.z;
        v13 = 5000.0;
      }
      dds3UnitObjectBasicSetJumpOfsPos(pBasic, x, v13, z);
      return;
    }
  }
}

// 0x1faf9a0
void sBtlSetTargetEnemyPosRot(SBTLUNIT_WORK *wk, f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 v15;
  bool v16;
  s64 v17;
  f32 v22;
  f32 v23;
  f32 w;
  f32 v25;
  sdfVector4_t v26;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && wk->actaiwk->targetID == pUnit->ListID)
    {
      v15 = (u16)pUnit->para->devilid - 258;
      v16 = v15 > 0x39;
      v17 = (1 << v15) & 0x300000000000001LL;
      if (!v16 && v17 != 0)
        return;
      vct_A.x = X;
      vct_A.y = Y;
      vct_A.z = Z;
      vct_A.w = 0.0;
      pUnit->pos = vct_A;
      FromEuler(0.0, Dir * 0.017453292, 0.0);
      v22 = pUnit->pos.x;
      v23 = pUnit->pos.y;
      pUnit->rot = vct_A;
      v25 = pUnit->pos.z;
      w = pUnit->pos.w;
      v26.x = v22;
      v26.y = v23;
      v26.z = v25;
      v26.w = w;
      dds3SetPosPoseSet(&pUnit->pBasic, v26);
      dds3SetRotPoseSet(&pUnit->pBasic, pUnit->rot);
      return;
    }
  }
}

// 0x1fb00c0
void sBtlSetDevilID_EnemyRot(s32 _DevilID, f32 _Dir) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdfVector4_t v15;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && pUnit->para->devilid == DevilID)
    {
      FromEuler(0.0, Dir * 0.017453292, 0.0);
      p_rot = &pUnit->rot;
      *p_rot = vct_A;
      x = pUnit->rot.x;
      y = pUnit->rot.y;
      z = pUnit->rot.z;
      w = pUnit->rot.w;
      v15.x = x;
      v15.y = y;
      v15.z = z;
      v15.w = w;
      dds3SetRotPoseSet(&pUnit->pBasic, v15);
      return;
    }
  }
}

// 0x1fafc80
void sBtlSetTargetEnemyMotion(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION _MotionID) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && wk->actaiwk->targetID == pUnit->ListID)
    {
      devilid = (u16)pUnit->para->devilid;
      if (devilid != 258 && devilid != 314)
      {
        sBtlSetMotion(pUnit, MotionID, 0, 0, 0);
      }
      return;
    }
  }
}

// 0x1fafdf0
void sBtlSetTargetEnemyTheWorld(SBTLUNIT_WORK *wk, bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v9;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && wk->actaiwk->targetID == pUnit->ListID)
    {
      if (OnOff)
        v9 = 0x2000000;
      else
        v9 = 0;
      pUnit->vstatus = pUnit->vstatus & 0xFDFFFFFF | v9;
      return;
    }
  }
}

// 0x1fb02d0
void sBtlSetTargetEnemyTheWorld2(SBTLUNIT_WORK *wk, bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && wk->actaiwk->targetID == pUnit->ListID)
    {
      if (OnOff)
      {
        sBtlStatusBitOn(pUnit, 0x10u);
      }
      else
      {
        sBtlStatusBitOff(pUnit, 0xFFFFFFEF);
      }
      return;
    }
  }
}

// 0x1fb0440
void sBtlSetDevilID_EnemyTheWorld(s32 _DevilID, bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v9;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && pUnit->para->devilid == DevilID)
    {
      if (OnOff)
        v9 = 0x2000000;
      else
        v9 = 0;
      pUnit->vstatus = pUnit->vstatus & 0xFDFFFFFF | v9;
      return;
    }
  }
}

// 0x1fb0550
bool sBtlChkEnemyPosReset(f32 *_X, f32 *_Y, f32 *_Z) {
  goto LABEL_3;
LABEL_9:
  *X = 0.0;
  *Y = 0.0;
  *Z = 0.0;
  return 0;
LABEL_3:
  if (gLastDead)
    goto LABEL_9;
  if (gTargetMagWait)
    goto LABEL_9;
  *X = gTargetMagX;
  *Y = gTargetMagY;
  *Z = gTargetMagZ;
  return 1;
}

// 0x1fb0670
static void SetSetsuma_Dof_SETSUMA1_R(SBTLUNIT_WORK *wk) {
  void *Instance;
  void *mDof;
  void *monitor;
  void *v7;
  intptr_t m_CachedPtr;
  void *v9;
  UnityEngine_Object_c *klass;
  void *v11;
  void *v12;
  void *v13;

  Instance = get_Instance(0);
  goto LABEL_4;
LABEL_9:
  mDof = Instance->mDof;
  if (!op_Inequality(Instance->mDof, 0, 0))
    return;
  monitor = mDof[2].monitor;
  v7 = Allocate(UnityEngine_Rendering_Universal_DepthOfFieldModeParameter);
  _ctor(v7, 1, 1, 0);
  (*(*(u64 *)monitor + 440))(monitor, v7, *(u64 *)(*(u64 *)monitor + 448));
  m_CachedPtr = mDof[2].m_CachedPtr;
  v9 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v9, 5.0, 1, 0);
  (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v9, *(u64 *)(*(u64 *)m_CachedPtr + 448));
  klass = mDof[3].klass;
  v11 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v11, 20.0, 1, 0);
  (*(klass->_1.image + 55))(klass, v11, *((u64 *)klass->_1.image + 56));
  v12 = mDof[3].monitor;
  v13 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v13, 1.5, 1, 0);
  (*(*(u64 *)v12 + 440))(v12, v13, *(u64 *)(*(u64 *)v12 + 448));
  (*(*(u64 *)mDof[3].monitor + 408))(mDof[3].monitor, 1, *(u64 *)(*(u64 *)mDof[3].monitor + 416));
  SetForceActiveDofSetting(Instance, 1, 0);
  return;
LABEL_4:
  if (op_Inequality(Instance, 0, 0))
    goto LABEL_9;
}

// 0x1fb08c0
void sBtlSetSetsuma_DofEnd(SBTLUNIT_WORK *wk) {
  void *Instance;
  void *mDof;

  Instance = get_Instance(0);
  if (op_Inequality(Instance, 0, 0))
    goto LABEL_5;
  return;
  if (op_Inequality(Instance, 0, 0))
  {
LABEL_5:
    mDof = Instance->mDof;
    if (!op_Inequality(Instance->mDof, 0, 0))
    {
LABEL_8:
      SetForceActiveDofSetting(Instance, 0, 0);
      return;
    }
    RestoreDofSetting(Instance, 0);
    goto LABEL_8;
  }
}

// 0x1fb0a10
static bool Chk_Unit_Unit_Hit(SBTLUNIT_WORK *wk) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 z;
  f32 v10;
  f32 v11;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->ListID == wk->ListID)
      continue;
    if (sBtlCheckHit_HitHelper(wk, pUnit))
      continue;
    if (!sBtlCheckExist2(pUnit))
      continue;
    if ((wk->status & 1) == 0)
    {
      if (!sBtlCheckSide(wk, pUnit))
        continue;
      if (!sBtlCheckHITCheck_Char(wk))
        continue;
      if (!sBtlCheckHITCheck_Char(pUnit))
        continue;
      if ((pUnit->status & 1) == 0)
      {
        x = wk->pos.x;
        z = wk->pos.z;
        v10 = pUnit->pos.x;
        v11 = pUnit->pos.z;
        if (sBtlGetLenXZ(x, z, v10, v11) <= (f32)(wk->actaiwk->hit_area_r + pUnit->actaiwk->hit_area_r))
          return i < number;
      }
    }
  }
  return i < number;
}

// 0x1fb0cd0
static void FinishSetsuma(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v11;
  f32 x;
  sdfVector4_t *p_pos;
  f32 v17;
  f32 *p_z;
  f32 z;
  f32 v20;
  f32 LenXZ;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 y;
  f32 w;
  f32 v28;
  f32 v29;
  f32 PosToDir;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 Dir180;
  sdfVector4_t *p_rot;
  f32 v39;
  f32 v40;
  sdfVector4_t *v42;
  sdfVector4_t *p_rotbk;
  s32 devilid;
  void *Instance;
  sdfVector4_t v52;

  if (gLastDead)
  {
    wk->motion_EndNoCng = 1;
    return;
  }
  if (wk->actwk->use_skillid == 1318)
  {
    sBtlPlayerPopAllDispHit();
    para = wk->para;
  }
  else
  {
    sBtlPlayerPopAllPosRotDispHit();
    para = wk->para;
  }
  if (sBtlGetBadStatus(para) == 17)
  {
    goto LABEL_18;
  }
  wk->next_motion_not_hokan = 1;
  sBtlSetMotion(wk, 130, 0, 0, 0);
LABEL_18:
  sBtlPlayerJyusoEffOnOff(wk, 1);
  sBtlPlayerPlayer_Bad_Pop(wk);
  targetID = wk->actaiwk->targetID;
  if (targetID == -1)
  {
    v11 = 0;
  }
  else
  {
    targetID = wk->actaiwk->targetID;
    UnitMng = wk->UnitMng;
    v11 = sBtlSearchUnit_ID(UnitMng, targetID);
  }
  sBtlPlayerCamMvReset(wk);
  sBtlPopCamera();
  sBtlNoHokan();
  if (v11)
  {
    if (!(!gDeadEvent || v11->actwk->status != 10))
    {
      x = v11->pos.x;
      p_pos = &wk->pos;
      v17 = wk->pos.x;
      gDeadEventUse = 1;
      p_z = &wk->pos.z;
      z = wk->pos.z;
      v20 = v11->pos.z;
      LenXZ = sBtlGetLenXZ(v17, z, x, v20);
      v22 = wk->pos.x;
      v23 = wk->pos.z;
      v24 = (f32)(wk->actaiwk->hit_area_r + v11->actaiwk->hit_area_r) + 200.0;
      if (LenXZ < v24)
      {
        v25 = v24 - LenXZ;
        y = wk->pos.y;
        w = wk->pos.w;
        v28 = v11->pos.x;
        v29 = v11->pos.z;
        PosToDir = sBtlGetPosToDir(v28, v29, v22, v23);
        sBtlGetMoveXZ(p_pos->x, *p_z, PosToDir, v25, &wk->pos.x, &wk->pos.z);
        v52.x = v22;
        v52.y = y;
        v52.z = v23;
        v52.w = w;
        CheckMapHit(wk, v52);
        if (Chk_Unit_Unit_Hit(wk))
        {
          p_pos->x = v22;
          *p_z = v23;
        }
        else
        {
          v22 = p_pos->x;
          v23 = *p_z;
        }
      }
      v32 = v11->pos.x;
      v33 = v11->pos.z;
      v34 = sBtlGetPosToDir(v22, v23, v32, v33);
      Dir180 = sBtlGetDir180(v34);
      wk->mv_rotbk = Dir180;
      FromEuler(0.0, Dir180 * 0.017453292, 0.0);
      p_rot = &wk->rot;
      *p_rot = vct_A;
      wk->rotbk = vct_A;
      v39 = sBtlGet360(v34 + 180.0);
      v40 = sBtlGetDir180(v39);
      v11->mv_rotbk = v40;
      FromEuler(0.0, v40 * 0.017453292, 0.0);
      v42 = &v11->rot;
      *v42 = vct_A;
      p_rotbk = &v11->rotbk;
      *p_rotbk = vct_A;
      sBtlResetTargetFollowUpAngleX(wk);
      sBtlNoHokan_Ring();
    }
    devilid = v11->para->devilid;
    if ((u32)(devilid - 258) < 3 || (devilid & 0xFFFFFFFC) == 0x138)
    {
      sBtlResetFollowUpAngleX(180.0);
    }
    else if ((wk->actwk->use_skillid & 0xFFFFFFFE) != 0x526)
    {
      sBtlResetTargetFollowUpAngleX(wk);
    }
    goto LABEL_85;
  }
LABEL_85:
  if (gDeadEventUse)
  {
    goto LABEL_88;
  }
  sBtlPlayerSetEnemyHPDrawOnOff(1);
  sBtlPlayerSetNakamaHPDrawOnOff(1);
LABEL_88:
  AW_XAtkDelete_XATK_FLAG2_BsFlowClr_Setsuma();
  if (IsAction(1))
    goto LABEL_96;
  goto LABEL_95;
  if (IsAction(1))
  {
LABEL_96:
    sBtlPlayerResetPlayerPosRot_Start();
    sBtlPlayerResetEnemyPosRot_Start();
    sBtlPlayerResetCamera_Start();
    SetTargetMagPos(wk, 0);
    goto LABEL_101;
  }
LABEL_95:
  if (IsAction(5))
    goto LABEL_96;
LABEL_101:
  if (!v11 || (v11->aiwk->scrflag & 0x20000) == 0)
  {
    gTargetMagWait = 0;
  }
  Instance = get_Instance(0);
  BackIconState(Instance, 0);
}

// 0x1fb15b0
static void EndSetsuma(SBTLUNIT_WORK *wk) {
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v10;
  s32 devilid;
  s32 v12;
  s32 v17;
  SBTLUNIT_LISTWORK *v19;

  if (gLastDead)
    goto LABEL_15;
  if (wk->actwk->use_skillid != 1318)
  {
    if (!gDeadEventUse)
    {
      sBtlPlayerPopAllPosRotDispHit();
      goto LABEL_17;
    }
LABEL_15:
    goto LABEL_17;
  }
  sBtlPlayerPopAllDispHit();
LABEL_17:
  sBtlPlayerSetEnemyNakamaDrawOnOff_ShadowBugPos();
  sBtlPlayerScrWarp_Muteki_Pop();
  targetID = wk->actaiwk->targetID;
  if (targetID == -1)
  {
    v10 = 0;
    goto LABEL_46;
  }
  UnitMng = wk->UnitMng;
  v10 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v10)
    goto LABEL_46;
  devilid = v10->para->devilid;
  if (devilid == 258)
    goto LABEL_88;
  if ((u32)(devilid - 312) < 2)
  {
    v12 = 259;
    goto LABEL_45;
  }
  if (devilid == 315)
  {
    v12 = 260;
    goto LABEL_45;
  }
  if (devilid == 314)
  {
LABEL_88:
    v12 = 258;
LABEL_45:
    sBtlSetDevilID_EnemyTheWorld(v12, 0);
    goto LABEL_46;
  }
  sBtlSetTargetEnemyTheWorld(wk, 0);
LABEL_46:
  if (gDeadEventUse)
  {
    sBtlSetTargetEnemyTheWorld2(wk, 0);
  }
  RestartBattle();
  sBtlStatusBitOff(wk, 0xFFFFBFEF);
  wk->status &= ~1u;
  sBtlEndWaitALL(0, 2);
  sBtlPlayerSP_BS_MUNAKA_Init_Imad_Restart();
  sBtlPlayerSP_BS_MUNAKA_Init_Imad_Kotei_Restart();
  if (gLastDead)
  {
    sBtlPlayerCamMvSetToResultMode(1);
  }
  AW_XAtkDelete_XATK_FLAG2_BsFlowClr_Setsuma();
  if (!IsAction(1))
  {
    if (!IsAction(5))
      goto LABEL_74;
  }
  sBtlPlayerResetPlayerPosRot_Start();
  sBtlPlayerResetEnemyPosRot_Start();
  sBtlPlayerResetCamera_Start();
  SetTargetMagPos(wk, 0);
LABEL_74:
  v17 = wk->actaiwk->targetID;
  if (v17 != -1)
  {
    v19 = wk->UnitMng;
    v10 = sBtlSearchUnit_ID(v19, v17);
    goto LABEL_78;
  }
LABEL_78:
  if (!v10 || (v10->aiwk->scrflag & 0x40000) == 0)
  {
    gTargetMagWait = 0;
  }
}

// 0x1fb1ae0
void sBtlSetsuma_MagWaitDone(void) {
  gTargetMagWait = 0;
  return;
}

// 0x1f877c0
static s32 SetsumaProc(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  s32 sord_st;
  s32 SUMMONSKILL_Start;
  SBATTLE_WORK *v8;
  sdatUnitWork_t *para;
  s32 use_skillid;
  SBATTLE_WORK *v21;

  v4 = wk;
  sord_st = v4->sord_st;
  if (sord_st != 1)
    goto LABEL_4;
  if (UpdateSetsuma(wk))
  {
    v8 = wk;
    v8->mode = 1;
    *(u32 *)v8->gstat = 0;
    para = wk->para;
    if (sBtlGetBadStatus(para) == 17)
      return 2;
    if (wk->actwk->use_skillid == 1319)
      wk->next_motion_not_hokan = 1;
    sBtlResetAction(wk);
    sBtlSetAction(wk, 1, 0);
    if (gLastDead)
    {
      wk->mode = 18;
      wk->motion_EndNoCng = 1;
      goto LABEL_34;
    }
    else
    {
      sBtlSetMotion(wk, 130, 0, 0, 0);
      goto LABEL_34;
    }
LABEL_34:
    BS_MATORY_DELETE();
    return 2;
  }
  wk->setsuma_a_muteki_cnt = 30;
  return 2;
LABEL_4:
  if (sord_st)
    return 2;
  v4 = wk;
  SUMMONSKILL_Start = v4->SUMMONSKILL_Start;
  if (SUMMONSKILL_Start)
  {
    v4 = wk;
    SUMMONSKILL_Start = v4->SUMMONSKILL_Start;
    v4->SUMMONSKILL_Start = SUMMONSKILL_Start - 1;
  }
  if (sBtlPlayerChkAll_EnemySummonW())
    goto LABEL_46;
  if (sBtlCheckSummon_LoadExecOk(0))
    goto LABEL_43;
LABEL_46:
  dds3PostSlowStart2(0x1Eu, 0x3Cu);
  wk->cmbSkl->bRun = 1;
  return 2;
LABEL_43:
  if (wk->SUMMONSKILL_Start)
    goto LABEL_46;
  dds3PostSlowClear();
  wk->damage_ActerOfsY = 0.0;
  wk->cmbSkl->bRun = 0;
  use_skillid = wk->actwk->use_skillid;
  sBtlSetUseSkill(wk, use_skillid, 0);
  sBtlSetAction(wk, 12, 0);
  v21 = wk;
  ++v21->sord_st;
  *(u64 *)&v21->sord_keybk = 0;
  v21->sord_actionf = 0;
  wk->hstatus &= ~0x20000u;
  wk->flg |= 0x200000u;
  wk->setsuma_a_muteki_cnt = 30;
  BeginSetsuma(wk);
  wk->motion_EndNoCng = 1;
  return 2;
}

// 0x1fb1b60
static bool UpdateSetsuma(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v7;
  s32 use_skillid;
  dds3ModelHandle_t *v11;
  dds3ModelHandle_t *hModel;
  dds3ModelHandle_t *v17;
  s32 v18;
  f32 v20;
  s32 v21;
  s32 v24;
  SBATTLE_WORK *v26;
  s32 encountno;
  s32 v28;
  SBTLUNIT_LISTWORK *v29;
  SBTLUNIT_WORK *v31;
  void *Instance;
  f32 v33;
  s32 v34;
  s32 devilid;
  s32 v38;
  dds3ModelHandle_t *v39;
  s32 v43;
  SBTLUNIT_WORK *v47;
  SBTLUNIT_WORK *v49;
  SBTLUNIT_LISTWORK *v55;
  s32 v56;
  SBTLUNIT_WORK *v57;
  SBTLUNIT_WORK *v58;
  SBTLUNIT_LISTWORK *v60;
  s32 v61;
  SBTLUNIT_WORK *v62;
  sdfVector4_t *v67;
  sdfVector4_t *v69;
  f32 v71;
  s32 v72;
  sdfVector4_t *p_pos;
  sdfVector4_t *p_rot;
  void *v79;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  s32 v88;
  SBTLUNIT_LISTWORK *v90;
  SBTLUNIT_WORK *v91;
  f32 v92;
  f32 v93;
  SBTLUNIT_WORK *v94;
  f32 v95;
  f32 v96;
  sdatUnitWork_t *v97;
  SBTLACTAI_WORK *actaiwk;
  long f64 v100;
  long f64 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  f32 v105;
  s32 magMax;
  SBTLUNIT_WORK *v110;
  sdfVector4_t *v115;
  sdfVector4_t *v117;
  f32 v120;
  f32 v121;
  f32 v122;
  f32 v123;
  s32 v124;
  SBTLUNIT_LISTWORK *v128;
  s32 v129;
  SBTLUNIT_WORK *v130;
  dds3ModelHandle_t *v132;
  s32 v136;
  bool v137;
  sdfVector4_t *v142;
  sdfVector4_t *v144;
  f32 v146;
  s32 v147;
  s32 v150;
  sdfVector4_t *v152;
  void *v153;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdatUnitWork_t *para;
  SBTLUNIT_LISTWORK *v163;
  SBTLUNIT_WORK *v165;
  SBTLUNIT_WORK *v167;
  f32 v171;
  f32 v172;
  f32 v173;
  f32 v174;
  SBTLUNIT_WORK *v176;
  SBTLUNIT_WORK *v178;
  f32 v183;
  SBTLUNIT_LISTWORK *v185;
  s32 v186;
  SBTLUNIT_WORK *v187;
  SBTLUNIT_WORK *v189;
  dds3ModelHandle_t *v190;
  SBTLUNIT_LISTWORK *v194;
  s32 v195;
  SBTLUNIT_WORK *v196;
  SBTLUNIT_WORK *v197;
  SBTLUNIT_LISTWORK *v201;
  s32 v202;
  SBTLUNIT_WORK *v203;
  s64 v209;
  s32 v210;
  SBTLUNIT_WORK *v211;
  sdfVector4_t *v215;
  sdfVector4_t *v217;
  f32 v219;
  f32 v220;
  f32 v221;
  f32 v222;
  SBTLUNIT_WORK *v224;
  f32 v227;
  f32 v228;
  f32 v229;
  f32 v230;
  SBTLUNIT_WORK *v233;
  SBTLUNIT_WORK *v235;
  sdfVector4_t v237;
  sdfVector4_t v238;
  sdfVector4_t v239;
  sdfVector4_t v240;
  sdfVector4_t v241;
  sdfVector4_t v242;
  sdfVector4_t v243;
  sdfVector4_t v244;
  sdfVector4_t v245;
  sdfVector4_t v246;

  if (!gLastDead)
  {
    UnitMng = wk->UnitMng;
    targetID = wk->actaiwk->targetID;
    v7 = sBtlSearchUnit_ID(UnitMng, targetID);
    if (v7)
    {
      if ((v7->aiwk->scrflag & 0x20000) != 0)
      {
        gDeadEvent = 1;
      }
      else if ((v7->hstatus & 0x8000000) != 0)
      {
        gLastDead = 1;
      }
    }
  }
  use_skillid = wk->actwk->use_skillid;
  if (use_skillid == 1301)
  {
    hModel = wk->hModel;
    mdlGetMotionFrameF(wk->hModel);
    if (gStep == 2)
      return 1;
    if (gStep == 1)
      goto LABEL_64;
    goto LABEL_42;
  }
  if (use_skillid == 1300)
  {
    v17 = wk->hModel;
    mdlGetMotionFrameF(wk->hModel);
    v18 = gStep;
    if (v18 == 2)
      return 1;
    if (v18 == 1)
      goto LABEL_64;
    if (v18)
      goto LABEL_117;
    if (gStepCnt)
    {
      goto LABEL_55;
    }
    sBtlPlayerSetEnemyNakamaDrawOnOff_ShadowBugPos();
LABEL_55:
    v24 = gStepCnt + 1;
    gStepCnt = v24;
    gStepTime = gStepTime + VRF_DeltaTime;
    if (v24 != 75)
      goto LABEL_106;
    v26 = wk;
    encountno = v26->encountno;
    if (encountno != 59)
    {
      encountno = wk->encountno;
      if (encountno != 60)
      {
LABEL_106:
        if (gStepCnt < 198)
          goto LABEL_117;
        goto LABEL_109;
      }
LABEL_103:
      dds3SetQuake(60, 0x64u);
      goto LABEL_106;
    }
    v28 = wk->actaiwk->targetID;
    if (v28 == -1)
      goto LABEL_106;
    v29 = v26->UnitMng;
    v31 = sBtlSearchUnit_ID(v29, v28);
    if (!v31)
      goto LABEL_106;
    devilid = (u16)v31->para->devilid;
    if (devilid != 314 && devilid != 258)
      goto LABEL_106;
    goto LABEL_103;
  }
  if (use_skillid != 1299)
    goto LABEL_117;
  v11 = wk->hModel;
  mdlGetMotionFrameF(wk->hModel);
  if (gStep == 2)
    return 1;
  if (gStep == 1)
  {
LABEL_64:
    if (gDeadEventUse)
    {
      if (!gStepCnt)
      {
        sBtlPlayerSetEnemyHPDrawOnOff(1);
        sBtlPlayerSetNakamaHPDrawOnOff(1);
      }
    }
    if (gStepCnt == 3)
    {
      Instance = get_Instance(0);
      BackIconState(Instance, 0);
      goto LABEL_81;
    }
LABEL_81:
    v33 = gStepTime;
    v34 = gStepCnt + 1;
    gStepCnt = v34;
    gStepTime = v33 + VRF_DeltaTime;
    if (v34 >= 10)
    {
LABEL_84:
      gStepTime = 0.0;
      *(u64 *)&gStep = 2;
      EndSetsuma(wk);
      return 1;
    }
    goto LABEL_117;
  }
LABEL_42:
  if (gStep)
    goto LABEL_117;
  if (gStepCnt)
  {
    goto LABEL_46;
  }
  sBtlPlayerSetEnemyNakamaDrawOnOff_ShadowBugPos();
LABEL_46:
  v20 = gStepTime;
  v21 = gStepCnt + 1;
  gStepCnt = v21;
  gStepTime = v20 + VRF_DeltaTime;
  if (v21 < 178)
    goto LABEL_117;
LABEL_109:
  if (gLastDead)
  {
    goto LABEL_84;
  }
  FinishSetsuma(wk);
  *(u64 *)&gStep = 1;
  gStepTime = 0.0;
LABEL_117:
  v38 = wk->actwk->use_skillid;
  if (v38 != 1318)
    goto LABEL_335;
  v39 = wk->hModel;
  mdlGetMotionFrameF(wk->hModel);
  v43 = gStep;
  if (v43 == 2)
    return 1;
  if (v43 == 1)
  {
    if (gStepCnt)
    {
      goto LABEL_192;
    }
    dds3FadeIn2(0xAu);
LABEL_192:
    if (gStepCnt)
    {
      goto LABEL_194;
    }
    v79 = get_Instance(0);
    BackIconState(v79, 0);
LABEL_194:
    v71 = gStepTime;
    v72 = gStepCnt + 1;
    gStepCnt = v72;
    gStepTime = v71 + VRF_DeltaTime;
    if (v72 < 30)
      goto LABEL_332;
    gStepTime = 0.0;
    *(u64 *)&gStep = 2;
    EndSetsuma(wk);
    wk->vstatus &= ~0x1000u;
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    p_pos = &wk->pos;
    *p_pos = vct_A;
    FromEuler(0.0, 3.1415927, 0.0);
    p_rot = &wk->rot;
    *p_rot = vct_A;
    x = wk->pos.x;
    y = wk->pos.y;
    wk->rotbk = vct_A;
    z = wk->pos.z;
    w = wk->pos.w;
    v242.x = x;
    v242.y = y;
    v242.z = z;
    v242.w = w;
    dds3SetPosPoseSet(&wk->pBasic, v242);
    dds3SetRotPoseSet(&wk->pBasic, wk->rot);
    para = wk->para;
    if (sBtlGetBadStatus(para) == 17)
    {
      sBtlSetAction(wk, 34, 0);
    }
    else
    {
      wk->next_motion_not_hokan = 1;
      sBtlSetMotion(wk, 0, 0, 0, 0);
    }
    sBtlSetTargetEnemyPosRot(wk, 0.0, 0.0, -350.0, 0.0);
    v163 = wk->UnitMng;
    v165 = sBtlSearchUnit_ID(v163, gKayaUnitID);
    v167 = v165;
    if (v165)
      v165->next_motion_not_hokan = 1;
    sBtlSetTargetEnemyMotion(wk, 0);
    sBtlResetFollowUpAngleX(90.0);
    gKayaCameraCutID = 0.0;
    gKayaUnitID = -1;
    if (v167)
    {
      sBtlBS_LASTB1_Action_Setu_End(v167);
    }
    return 1;
  }
  if (!v43)
  {
    if (gKayaCnt == 0.0)
    {
      sBtlPlaySE(0x5010017u);
      sBtlBeginSetsuma_EX(wk);
      wk->next_motion_not_hokan = 1;
      sBtlSetMotion(wk, 0, 0, 0, 0);
      wk->vstatus |= 0x1000u;
      gKayaEnemyPosZ = 0.0;
      gKayaEnemyPosX = 0.0;
      v47 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
      v49 = v47;
      if (v47)
      {
        v47->next_motion_not_hokan = 1;
        v47->motion_EndNoCng = 1;
      }
      sBtlSetTargetEnemyDrawOnOff(wk, 1);
      sBtlSetTargetEnemyPosRot(wk, gKayaEnemyPosX, 0.0, gKayaEnemyPosZ, 0.0);
      sBtlSetTargetEnemyMotion(wk, 38);
      if (v49)
      {
        v49->next_motion_not_hokan = 1;
        v49->motion_EndNoCng = 1;
      }
      sBtlSetTargetEnemyMotion(wk, 38);
      sBtlSetTargetEnemyTheWorld(wk, 1);
      Add(v49->ListID, 8, 0);
      sBtlPlayerSetEnemyHPDrawOnOff(0);
      sBtlPlayerSetNakamaHPDrawOnOff(0);
      gKayaCameraCutID = 1.0;
    }
    if (gKayaCnt == 0.0)
    {
      v237.x = 0.0;
      v237.y = 0.0;
      v237.z = 0.0;
      v237.w = 0.0;
      sBtlPlay3DSE(0x10066u, v237);
    }
    if (gKayaCnt == 13.0)
    {
      v55 = wk->UnitMng;
      v56 = wk->actaiwk->targetID;
      v57 = sBtlSearchUnit_ID(v55, v56);
      if (v57)
      {
        v58 = v57;
        sBtlPlayMotionSE(v58, 17, 0);
      }
    }
    if (gKayaCnt == 28.0)
    {
      v60 = wk->UnitMng;
      v61 = wk->actaiwk->targetID;
      v62 = sBtlSearchUnit_ID(v60, v61);
      if (v62)
        v62->motion_EndNoCng = 1;
      sBtlSetTargetEnemyMotion(wk, 39);
    }
    if (gKayaCnt != 40.0)
    {
LABEL_231:
      if (gKayaCnt == 40.0)
      {
        Add(wk->ListID, 6, 0);
      }
      if (gKayaCnt == 80.0)
      {
        sndVoicePlayFile("PVA01A_20A_003", 0);
      }
      if (gKayaCnt == 130.0)
      {
        v88 = wk->actaiwk->targetID;
        gKayaUnitID = v88;
        v88 = gKayaUnitID;
        v90 = wk->UnitMng;
        v91 = sBtlSearchUnit_ID(v90, v88);
        if (!v91)
        {
LABEL_262:
          if (gKayaCnt > 40.0)
          {
            if (gKayaCnt < 185.0)
            {
              FromEuler(0.0, 3.1415927, 0.0);
              *(__n128 *)&v101 = sub_1B335A0(&wk->rot, 0, v100);
              sub_1B335A0(&wk->rotbk, 0, v101);
              v102 = wk->rot.x;
              v103 = wk->rot.y;
              v105 = wk->rot.z;
              v104 = wk->rot.w;
              v240.x = v102;
              v240.y = v103;
              v240.z = v105;
              v240.w = v104;
              dds3SetRotPoseSet(&wk->pBasic, v240);
            }
          }
          if (gKayaCnt == 175.0)
          {
            dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0xAu);
          }
          if (gKayaCnt != 185.0)
            goto LABEL_332;
          FinishSetsuma(wk);
          *(u64 *)&gStep = 1;
          gStepTime = 0.0;
          DeleteAll_Skill();
          gTargetMagX = 0.0;
          *(u64 *)&gTargetMagY = 3271688192LL;
          gTargetMagWait = 0;
          sBtlSetAddMag_Setsuma_D(wk);
          magMax = wk->magMax;
          sBtlAddMag(50 * magMax / -100);
          sBtlSetSetsuma_DofEnd(v110);
          wk->vstatus &= ~0x1000u;
          *(u64 *)&vct_A.x = 0;
          *(u64 *)&vct_A.z = 0;
          v115 = &wk->pos;
          *v115 = vct_A;
          FromEuler(0.0, 3.1415927, 0.0);
          v117 = &wk->rot;
          *v117 = vct_A;
          v120 = wk->pos.x;
          v121 = wk->pos.y;
          wk->rotbk = vct_A;
          v123 = wk->pos.z;
          v122 = wk->pos.w;
          v241.x = v120;
          v241.y = v121;
          v241.z = v123;
          v241.w = v122;
          dds3SetPosPoseSet(&wk->pBasic, v241);
          dds3SetRotPoseSet(&wk->pBasic, wk->rot);
          if (sBtlGetBadStatus(wk->para) == 17)
          {
            v124 = 13;
          }
          else
          {
            wk->motion_EndNoCng = 0;
            v124 = 130;
            wk->next_motion_not_hokan = 1;
          }
          sBtlSetMotion(wk, v124, 0, 0, 0);
          sBtlResetMutekiColor(wk);
          sBtlSetTargetEnemyPosRot(wk, 0.0, 0.0, -350.0, 0.0);
          v128 = wk->UnitMng;
          v129 = gKayaUnitID;
          v130 = sBtlSearchUnit_ID(v128, v129);
          if (v130)
          {
            v130->motion_EndNoCng = 0;
            v130->next_motion_not_hokan = 1;
          }
          sBtlSetTargetEnemyMotion(wk, 0);
          sBtlPlayerCamMvReset(wk);
          sBtlPopCamera();
          sBtlNoHokan();
          sBtlResetFollowUpAngleX(90.0);
          gKayaCameraCutID = 10.0;
          goto LABEL_332;
        }
        v92 = wk->pos.x;
        v93 = wk->pos.y;
        v94 = v91;
        wk->flg &= 0xFFDBF7FF;
        v96 = wk->pos.z;
        v95 = wk->pos.w;
        v239.x = v92;
        v239.y = v93;
        v239.z = v96;
        v239.w = v95;
        SetDamageProc(wk, v94, 1550, v239);
        dds3SetQuake(30, 0x3Cu);
        v97 = wk->para;
        sBtlGetBadStatus(v97);
        actaiwk = wk->actaiwk;
        actaiwk->targetID = gKayaUnitID;
      }
      goto LABEL_262;
    }
    wk->vstatus &= ~0x1000u;
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    v67 = &wk->pos;
    *v67 = vct_A;
    FromEuler(0.0, 3.1415927, 0.0);
    v69 = &wk->rot;
    *v69 = vct_A;
    v82 = wk->pos.x;
    v83 = wk->pos.y;
    wk->rotbk = vct_A;
    v85 = wk->pos.z;
    v84 = wk->pos.w;
    v238.x = v82;
    v238.y = v83;
    v238.z = v85;
    v238.w = v84;
    dds3SetPosPoseSet(&wk->pBasic, v238);
    dds3SetRotPoseSet(&wk->pBasic, wk->rot);
    wk->motion_EndNoCng = 1;
    sBtlSetMotion(wk, 126, 0, 0, 0);
    sBtlSetTargetEnemyDrawOnOff(wk, 1);
    gKayaCameraCutID = 2.0;
    goto LABEL_231;
  }
LABEL_332:
  gKayaCnt = gKayaCnt + 1.0;
  v38 = wk->actwk->use_skillid;
LABEL_335:
  if (v38 != 1319)
    return 0;
  v132 = wk->hModel;
  mdlGetMotionFrameF(wk->hModel);
  v136 = gStep;
  if (v136 == 2)
    return 1;
  if (v136 == 1)
  {
    if (gStepCnt)
    {
      goto LABEL_364;
    }
    dds3FadeIn2(0xAu);
    sBtlChangePosToDevil(257);
LABEL_364:
    if (gStepCnt)
    {
      goto LABEL_366;
    }
    v153 = get_Instance(0);
    BackIconState(v153, 0);
LABEL_366:
    v146 = gStepTime;
    v147 = gStepCnt + 1;
    gStepCnt = v147;
    gStepTime = v146 + VRF_DeltaTime;
    if (v147 < 30)
      goto LABEL_575;
    gStepTime = 0.0;
    *(u64 *)&gStep = 2;
    EndSetsuma(wk);
    wk->vstatus &= ~0x1000u;
    v150 = (u8)byte_5755EF6;
    vct_A = (struct sdfVector4_t)xmmword_3D026E0;
    wk->pos = vct_A;
    FromEuler(0.0, 3.1415927, 0.0);
    v152 = &wk->rot;
    *v152 = vct_A;
    v227 = wk->pos.x;
    v228 = wk->pos.y;
    wk->rotbk = vct_A;
    v230 = wk->pos.z;
    v229 = wk->pos.w;
    v246.x = v227;
    v246.y = v228;
    v246.z = v230;
    v246.w = v229;
    dds3SetPosPoseSet(&wk->pBasic, v246);
    dds3SetRotPoseSet(&wk->pBasic, wk->rot);
    wk->next_motion_not_hokan = 1;
    wk->motion_EndNoCng = 0;
    sBtlSetMotion(wk, 130, 0, 0, 0);
    sBtlSetTargetEnemyPosRot(wk, 0.0, 0.0, -200.0, 0.0);
    v233 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
    v235 = v233;
    if (v233)
    {
      v233->motion_EndNoCng = 0;
      v233->next_motion_not_hokan = 1;
    }
    sBtlSetTargetEnemyMotion(wk, 0);
    sBtlResetFollowUpAngleX(270.0);
    gKayaCameraCutID = 0.0;
    if (v235)
    {
      sBtlBS_LASTB1_Action_Setr_End(v235);
    }
    return 1;
  }
  if (!v136)
  {
    if (gKayaCnt != 0.0)
    {
LABEL_457:
      if (gKayaCnt == 0.0)
      {
        v244.x = 0.0;
        v244.y = 0.0;
        v244.z = 0.0;
        v244.w = 0.0;
        sBtlPlay3DSE(0x10066u, v244);
      }
      v183 = gKayaCnt;
      if (v183 == 3.0)
        goto LABEL_472;
      v183 = gKayaCnt;
      if (v183 == 6.0)
        goto LABEL_472;
      v183 = gKayaCnt;
      if (v183 == 9.0)
      {
LABEL_472:
        v185 = wk->UnitMng;
        v186 = wk->actaiwk->targetID;
        v187 = sBtlSearchUnit_ID(v185, v186);
        if (v187)
        {
          v189 = v187;
          if (v187->motionno != 36)
            goto LABEL_481;
          v190 = v187->hModel;
          if (mdlGetMotionFrameF(v190) <= 0.0)
          {
LABEL_481:
            v189->next_motion_not_hokan = 1;
            v189->motion_EndNoCng = 1;
            sBtlSetTargetEnemyMotion(wk, 40);
          }
        }
      }
      if (gKayaCnt == 47.0)
      {
        sndVoicePlayFile("PVA01A_22A_005", 0);
      }
      if (gKayaCnt == 45.0)
      {
        v194 = wk->UnitMng;
        v195 = wk->actaiwk->targetID;
        v196 = sBtlSearchUnit_ID(v194, v195);
        if (v196)
        {
          v197 = v196;
          sBtlPlayMotionSE(v197, 17, 0);
        }
      }
      if (gKayaCnt == 44.0)
      {
        gKayaCameraCutID = 2.0;
        SetSetsuma_Dof_SETSUMA1_R(sBtlPlayer);
      }
      if (gKayaCnt == 91.0)
      {
        Add(wk->ListID, 7, 0);
      }
      if (gKayaCnt == 91.0)
      {
        gKayaCameraCutID = 3.0;
      }
      if (gKayaCnt == 91.0)
      {
        v201 = wk->UnitMng;
        v202 = wk->actaiwk->targetID;
        v203 = sBtlSearchUnit_ID(v201, v202);
        if (v203)
        {
          v203->next_motion_not_hokan = 1;
          v203->motion_EndNoCng = 1;
        }
        sBtlSetTargetEnemyMotion(wk, 41);
        sBtlSetTargetEnemyTheWorld(wk, 1);
      }
      if (gKayaCnt == 205.0)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0xAu);
      }
      if (gKayaCnt != 215.0)
        goto LABEL_575;
      FinishSetsuma(wk);
      *(u64 *)&gStep = 1;
      gStepTime = 0.0;
      DeleteAll_Skill();
      gTargetMagX = 0.0;
      *(u64 *)&gTargetMagY = 0xC3480000C3020000LL;
      gTargetMagWait = 0;
      v209 = 68719476750LL * wk->magMax;
      v210 = (v209 >> 37) + ((u64)v209 >> 63);
      sBtlSetAddMag_Setsuma(wk, v210);
      sBtlSetSetsuma_DofEnd(v211);
      wk->vstatus &= ~0x1000u;
      vct_A = (struct sdfVector4_t)xmmword_3D026E0;
      v215 = &wk->pos;
      *v215 = vct_A;
      FromEuler(0.0, 3.1415927, 0.0);
      v217 = &wk->rot;
      *v217 = vct_A;
      v219 = wk->pos.x;
      v220 = wk->pos.y;
      wk->rotbk = vct_A;
      v222 = wk->pos.z;
      v221 = wk->pos.w;
      v245.x = v219;
      v245.y = v220;
      v245.z = v222;
      v245.w = v221;
      dds3SetPosPoseSet(&wk->pBasic, v245);
      dds3SetRotPoseSet(&wk->pBasic, wk->rot);
      wk->next_motion_not_hokan = 1;
      wk->motion_EndNoCng = 0;
      sBtlSetMotion(wk, 130, 0, 0, 0);
      sBtlSetTargetEnemyPosRot(wk, 0.0, 0.0, -200.0, 0.0);
      v224 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
      if (v224)
      {
        v224->motion_EndNoCng = 0;
        v224->next_motion_not_hokan = 1;
      }
      sBtlSetTargetEnemyMotion(wk, 0);
      sBtlResetFollowUpAngleX(270.0);
      gKayaCameraCutID = 10.0;
      goto LABEL_575;
    }
    sBtlPlaySE(0x5010016u);
    sBtlBeginSetsuma_EX(wk);
    wk->vstatus &= ~0x1000u;
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    v142 = &wk->pos;
    *v142 = vct_A;
    FromEuler(0.0, 3.1415927, 0.0);
    v144 = &wk->rot;
    *v144 = vct_A;
    v171 = wk->pos.x;
    v172 = wk->pos.y;
    wk->rotbk = vct_A;
    v174 = wk->pos.z;
    v173 = wk->pos.w;
    v243.x = v171;
    v243.y = v172;
    v243.z = v174;
    v243.w = v173;
    dds3SetPosPoseSet(&wk->pBasic, v243);
    dds3SetRotPoseSet(&wk->pBasic, wk->rot);
    wk->motion_EndNoCng = 1;
    sBtlSetMotion(wk, 127, 0, 0, 0);
    *(u64 *)&gKayaEnemyPosX = 0x441B000000000000LL;
    v176 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
    v178 = v176;
    if (v176)
    {
      v176->next_motion_not_hokan = 1;
      v176->motion_EndNoCng = 1;
    }
    sBtlSetTargetEnemyDrawOnOff(wk, 1);
    sBtlSetTargetEnemyPosRot(wk, gKayaEnemyPosX, 0.0, gKayaEnemyPosZ, 0.0);
    sBtlSetTargetEnemyMotion(wk, 40);
    if (v178)
    {
      v178->next_motion_not_hokan = 1;
      v178->motion_EndNoCng = 1;
    }
    sBtlSetTargetEnemyMotion(wk, 40);
    sBtlSetTargetEnemyTheWorld(wk, 1);
    sBtlPlayerSetEnemyHPDrawOnOff(0);
    sBtlPlayerSetNakamaHPDrawOnOff(0);
    gKayaCameraCutID = 1.0;
    if (v178)
    {
      sBtlBS_LASTB1_Init_Setr(v178);
    }
    goto LABEL_457;
  }
LABEL_575:
  v137 = 0;
  gKayaCnt = gKayaCnt + 1.0;
  return v137;
}

// 0x1fb47d0
bool sBtlGetSetsumaCamMv(SBTLUNIT_WORK *wk, f32 *_TX, f32 *_TY, f32 *_TZ, f32 *_CX, f32 *_CY, f32 *_CZ, f32 *_Fov, f32 *_UpV, f32 *_AngleX, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos) {
  s32 use_skillid;
  f32 v24;
  s32 v25;
  s32 v27;

  if (wk->mode != 17)
    return 0;
  use_skillid = wk->actwk->use_skillid;
  if (use_skillid == 1319)
  {
    if (gKayaCameraCutID == 1.0)
    {
      *TX = 0.0;
      *TY = -69.0;
      *TZ = 0.0;
      *CX = -96.0;
      *CY = -69.0;
      *CZ = -202.0;
      *Fov = 45.0;
      v27 = 1094713344;
      goto LABEL_35;
    }
    if (gKayaCameraCutID == 2.0)
    {
      *TX = 0.0;
      *TY = -63.0;
      *TZ = 320.0;
      *CX = -150.0;
      *CY = -63.0;
      v25 = 1110704128;
      *CZ = 320.0;
LABEL_29:
      *(u32 *)Fov = v25;
      *UpV = 0.0;
      goto LABEL_37;
    }
    if (gKayaCameraCutID == 3.0)
    {
      *TX = 150.0;
      *TY = -60.0;
      *TZ = 320.0;
      *CX = -169.0;
      *CY = -76.0;
      *CZ = 24.0;
      *Fov = 42.0;
      v27 = -1050673152;
LABEL_35:
      *(u32 *)UpV = v27;
LABEL_37:
      sBtlNoHokan();
      return 1;
    }
LABEL_38:
    return 0;
  }
  if (use_skillid == 1318)
  {
    v24 = gKayaCameraCutID;
    if (v24 == 1.0)
    {
      *TX = 0.0;
      *TY = -70.0;
      *TZ = 0.0;
      *CX = 0.0;
      *CY = -80.0;
      *CZ = -385.0;
      v25 = 1106247680;
      goto LABEL_29;
    }
    v24 = gKayaCameraCutID;
    if (v24 == 2.0)
    {
      *TX = -110.0;
      *TY = -95.0;
      *TZ = 0.0;
      *CX = 111.0;
      *CY = -107.0;
      *CZ = -600.0;
      *Fov = 28.0;
      v27 = -1065353216;
      goto LABEL_35;
    }
    goto LABEL_38;
  }
  return 0;
}

// 0x1f8bae0
void sBtlReset_SupportAction_Shugou(SBTLUNIT_WORK *wk) {
  s64 i;
  SBATTLE_WORK *v5;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v7;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v10;
  u32 stock_mask;
  u32 color;
  sdatUnitWork_t *para;
  u32 BadStatus;

  for (i = 0; i != 32; ++i)
  {
    v5 = wk;
    UnitMng = v5->UnitMng;
    v7 = v5->summonID[i];
    v8 = sBtlSearchUnit_ID(UnitMng, v7);
    if (!v8)
      continue;
    v10 = v8;
    if ((v8->aiwk->m_status & 0x40000) == 0)
      continue;
    stock_mask = wk->stock_mask;
    if (((stock_mask >> i) & 1) == 0)
      continue;
    if (wk->summonflg[i] == 2)
    {
      Check_Stls(v10);
      if ((v10->flg & 0x400) == 0)
        continue;
      v10->L2_muteki = 1;
      color = v10->color;
      v10->chgcolor = color & 0xFFFFFF | 0x40000000;
      sBtlChangeModelColor(v10);
      v10->color_chroma = -2147352062;
    }
  }
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (!sBtlCheckMove_BadStatus(wk))
  {
LABEL_35:
    StlsClr(0);
    StlsClr(1);
    StlsEndChk(0);
    StlsEndChk(1);
    wk->NakamaShugouOn = 0;
    return;
  }
  if ((BadStatus | 2) == 0xA)
    goto LABEL_35;
  if ((wk->status2 & 0x20000000) != 0)
    goto LABEL_35;
}

// 0x1f8c300
static void Check_SupportAction_Shugou(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 v10;
  s32 v17;
  SBATTLE_WORK *v19;
  char **v21;

  Nakama = sBtlGetNakama(0);
  v4 = sBtlGetNakama(1);
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (wk->endcnt)
    goto LABEL_11;
  if ((BadStatus > 0x13 || ((1 << BadStatus) & 0xB31DF) == 0) && (u64)Nakama | (u64)v4)
  {
    if (sBtlIsBattleKey(4153, 2))
    {
      v17 = 65649;
      v19 = wk;
      if (v19->NakamaShugouOn)
      {
        v19 = wk;
        v19->NakamaShugouOn = 0;
        v17 = 65650;
        v21 = &"PVA01A_40A_003";
        goto LABEL_34;
      }
      else
      {
        v19 = wk;
        v19->NakamaShugouOn = 1;
        v21 = &"PVA01A_40B_001";
        goto LABEL_34;
      }
LABEL_34:
      sndVoicePlayFile(*v21, 0);
      SE(v17);
    }
  }
LABEL_11:
  if (!wk->NakamaShugouOn)
  {
    if (!v10)
    StlsClr(0);
    StlsClr(1);
    goto LABEL_17;
  }
  if (!v10)
  sBtlStlsSet(0);
  sBtlStlsSet(1);
LABEL_17:
  StlsEndChk(0);
  StlsEndChk(1);
}

// 0x1fb5200
bool sBtlStlsSet(s32 index) {
  SBTLUNIT_WORK *Nakama;
  SBTLAI_WORK *aiwk;
  SBTLUNIT_WORK *v5;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBTLUNIT_WORK *v9;
  int32x4_t v10;
  SBTLACTION_WORK *actwk;
  int32x4_t v12;
  HpCallCtrl *hpCallCtrl;

  Nakama = sBtlGetNakama(index);
  if (Nakama)
  {
    aiwk = Nakama->aiwk;
    v5 = Nakama;
    if ((aiwk->m_status & 0x40000) != 0 || (aiwk->m_status2 & 0x2000) != 0)
      goto LABEL_32;
    para = Nakama->para;
    BadStatus = sBtlGetBadStatus(para);
    if ((u32)(index + 1) < 2)
    {
      v9 = sBtlGetNakama(0);
      if (v9 && v9->actwk->status == 58)
        goto LABEL_32;
      if (index == -1)
        goto LABEL_16;
      goto LABEL_24;
    }
    if (index == 1)
    {
LABEL_16:
      Nakama = sBtlGetNakama(1);
      if (Nakama)
      {
        v10 = vdupq_n_s32(BadStatus);
        actwk = Nakama->actwk;
        LOBYTE(Nakama) = 0;
        v12 = v10;
        v12.n128_u32[1] = actwk->status;
        if ((vmaxv_u8(vmovn_s16(vuzp1q_s16(vceqq_s32(v12, (int32x4_t)xmmword_3CFB0E0), vceqq_s32(v10, (int32x4_t)xmmword_3CFFEE0)))) & 1) != 0)
          return (char)Nakama;
        if ((vaddvq_s32(vandq_s8(vceqq_s32(v10, (int32x4_t)xmmword_3CFEF20), (int8x16_t)xmmword_3CFFD40)) & 0xF) != 0 || (BadStatus & 0xFFFFFFFD) == 17)
        {
          return (char)Nakama;
        }
        goto LABEL_26;
      }
    }
LABEL_24:
    if (BadStatus >= 0x14 || ((0xB31DFu >> BadStatus) & 1) == 0)
    {
LABEL_26:
      Check_Stls(v5);
      v5->aiwk->m_status |= 0x40000u;
      v5->status |= 0x1000u;
      hpCallCtrl = v5->hpCallCtrl;
      wk->bsc->shortcut_cache = 0;
      OkSign(hpCallCtrl, 0);
      LOBYTE(Nakama) = 1;
      return (char)Nakama;
    }
LABEL_32:
    LOBYTE(Nakama) = 0;
  }
  return (char)Nakama;
}

// 0x1fb4f70
static void StlsClr(s32 index) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  SBTLAI_WORK *aiwk;
  s64 v10;
  HpCallCtrl *hpCallCtrl;

  Nakama = sBtlGetNakama(index);
  if (Nakama)
  {
    v5 = Nakama;
    if ((Nakama->aiwk->m_status & 0x40000) != 0)
    {
      if ((u32)(index + 1) < 2)
      {
        v6 = sBtlGetNakama(0);
        if (v6 && v6->actwk->status == 58)
          return;
        if (index != -1)
          goto LABEL_16;
        goto LABEL_14;
      }
      if (index != 1)
      {
LABEL_16:
        aiwk = v5->aiwk;
        LODWORD(v10) = *(u64 *)&aiwk->m_status & 0xFFFBFFFF;
        HIDWORD(v10) = (*(u64 *)&aiwk->m_status | 0x200000002000uLL) >> 32;
        *(u64 *)&aiwk->m_status = v10;
        v5->status &= ~0x1000u;
        ShugouKaijyoSub(v5);
        v5->damagecnt = 0;
        hpCallCtrl = v5->hpCallCtrl;
        wk->bsc->shortcut_cache = 0;
        OkSign(hpCallCtrl, 0);
        return;
      }
LABEL_14:
      v7 = sBtlGetNakama(1);
      if (v7 && v7->actwk->status == 58)
        return;
      goto LABEL_16;
    }
  }
}

// 0x1fb50f0
static bool StlsEndChk(s32 index) {
  SBTLUNIT_WORK *Nakama;
  SBTLAI_WORK *aiwk;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;

  Nakama = sBtlGetNakama(index);
  if (Nakama)
  {
    aiwk = Nakama->aiwk;
    v5 = Nakama;
    if ((aiwk->m_status & 0x40000) != 0 || (aiwk->m_status2 & 0x2000) == 0)
      goto LABEL_6;
    if ((u32)(index + 1) < 2)
    {
      v6 = sBtlGetNakama(0);
      if (v6 && v6->actwk->status == 58)
        goto LABEL_6;
      if (index == -1)
      {
LABEL_16:
        v7 = sBtlGetNakama(1);
        if (!v7 || v7->actwk->status != 58)
          goto LABEL_18;
LABEL_6:
        LOBYTE(Nakama) = 0;
        return (char)Nakama;
      }
LABEL_18:
      v5->aiwk->m_status2 &= ~0x2000u;
      LOBYTE(Nakama) = 1;
      return (char)Nakama;
    }
    if (index == 1)
      goto LABEL_16;
    goto LABEL_18;
  }
  return (char)Nakama;
}

// 0x1fb54d0
static bool ShugouKaijyoSub(SBTLUNIT_WORK *wklock) {
  s32 flg;
  SBTLAI_WORK *aiwk;
  u32 m_status;
  s32 v6;
  u32 color;
  s32 miusinai;

  if (wklock)
  {
    flg = wklock->flg;
    if ((flg & 0x400) != 0)
    {
      wklock->flg = flg & 0xFFFFFBFD;
      wklock->status &= ~0x1000u;
      aiwk = wklock->aiwk;
      m_status = aiwk->m_status;
      if ((m_status & 0x40000) != 0)
      {
        aiwk->m_status = m_status & 0xFFFBFFFF;
        miusinai = wklock->miusinai;
        wklock->L2_muteki = 0;
        wklock->damagecnt = 0;
        if (miusinai)
        {
LABEL_7:
          color = wklock->color;
          goto LABEL_9;
        }
      }
      else
      {
        v6 = wklock->miusinai;
        wklock->L2_muteki = 0;
        wklock->damagecnt = 0;
        if (v6)
          goto LABEL_7;
      }
      wklock->actaiwk->targetID = -1;
      sBtlResetMode(wklock);
      wklock->aiwk->mode = 0;
      ResetAction(wklock, 0, 0);
      color = wklock->color;
LABEL_9:
      wklock->chgcolor = color & 0xFFFFFF | 0x80000000;
      sBtlChangeModelColor(wklock);
      wklock->color_chroma = -2139062144;
      if (sBtlCheckDamageTarget(wklock))
        wklock->actcounter = wklock->actcounter_max;
    }
  }
  return 1;
}

// 0x1fb5440
static s32 CheckNowNSWARP(s32 index) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;

  if ((u32)(index + 1) >= 2)
  {
    if (index != 1)
      return 0;
    goto LABEL_7;
  }
  Nakama = sBtlGetNakama(0);
  if (Nakama && Nakama->actwk->status == 58)
    return 1;
  if (index == -1)
  {
LABEL_7:
    v4 = sBtlGetNakama(1);
    if (v4 && v4->actwk->status == 58)
      return 1;
  }
  return 0;
}

// 0x1fb4b80
static void Check_Stls(SBTLUNIT_WORK *wklock) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *Nakama;
  s32 v10;
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 status;
  u32 v15;
  SBTLEFF_LISTWORK *effList;
  SBTLDMG_HITLISTWORK *hitList;
  f32 v18;
  f32 hit_area_r;
  f32 v20;
  f32 y;
  f32 x;
  f32 z;
  f32 w;
  f32 v25;
  long f64 v26;
  sdfVector4_t v27;
  SBTLACTAI_WORK *actaiwk;
  f32 v30;
  f32 v31;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (wklock)
  {
    v8 = v7;
    if (v7)
    {
      if ((wklock->flg & 0x400) == 0)
      {
        Nakama = sBtlGetNakama(0);
        if (Nakama == wklock)
          v10 = 0;
        else
          v10 = -1;
        if (sBtlGetNakama(1) == wklock)
        {
          v10 = 1;
        }
        else if (Nakama != wklock)
        {
          return;
        }
        para = wklock->para;
        BadStatus = sBtlGetBadStatus(para);
        if (sBtlCheckDamageTarget(wklock))
        {
          status = wklock->status;
          if ((status & 0x800000) == 0 && (BadStatus > 0x13 || ((1 << BadStatus) & 0xB31DF) == 0) && !wklock->byctCnt)
          {
            wklock->asimoto_mode = 0;
            wklock->status = status & 0xFFFFFFFE;
            v15 = wklock->flg & 0xFFFFFFFD;
            wklock->damagecnt = 0;
            wklock->flg = v15 | 0x400;
            effList = wk->effList;
            sBtlForceDelete_ID_Summon(effList, wklock);
            sBtlForceDelete_SkillFlag_Acter(wklock, 0x400u);
            hitList = wk->hitList;
            sBtlClearHitC(hitList, wklock);
            sBtlForceDelete_SkillID_Acter(wklock, 427);
            if (v10)
              v18 = 60.0;
            else
              v18 = -60.0;
            hit_area_r = wklock->actaiwk->hit_area_r;
            if (!sBtlGetMovePos_MapHit_Nakama(v8, wklock, &pos, hit_area_r + 55.0, v18, 1, v10))
            {
              v20 = wklock->actaiwk->hit_area_r;
              if (!sBtlGetMovePos_MapHit_Nakama(v8, wklock, &pos, v20 + (f32)(v20 + 55.0), v18, 1, v10))
              {
                x = wklock->pos.x;
                y = wklock->pos.y;
                z = wklock->pos.z;
                w = wklock->pos.w;
                v30 = wklock->pos.y;
                v31 = wklock->pos.z;
                v25 = wklock->pos.w;
                y = v30;
                z = v31;
                w = v25;
                *(__n128 *)&v26 = sub_1B332C0(0, x, y, z, w);
                sub_1B335A0(&pos, 0, v26);
              }
            }
            v27 = pos;
            actaiwk = wklock->actaiwk;
            actaiwk->mode = 2;
            actaiwk->ppos = v27;
            *(u64 *)&actaiwk->frame = 0x1400000000LL;
            sBtlSetAction(wklock, 58, 20);
            wklock->actaiwk->stat = 2;
            wklock->aiwk->stat = 2;
          }
        }
      }
    }
  }
}

// 0x1fb5650
void sBtlShugouKaijyo(void) {
  s64 i;
  u32 stock_mask;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v7;
  SBTLUNIT_WORK *v8;
  SBTLAI_WORK *aiwk;
  SBTLUNIT_WORK *v10;
  sdatUnitWork_t *para;
  s64 v13;
  u32 status;
  sdatUnitWork_t *v17;

  for (i = 0; i != 32; ++i)
  {
    stock_mask = wk->stock_mask;
    if (((stock_mask >> i) & 1) == 0)
      continue;
    if (wk->summonflg[i] == 2)
    {
      UnitMng = wk->UnitMng;
      v7 = wk->summonID[i];
      v8 = sBtlSearchUnit_ID(UnitMng, v7);
      if (!v8)
        continue;
      aiwk = v8->aiwk;
      v10 = v8;
      para = v8->para;
      LODWORD(v13) = *(u64 *)&aiwk->m_status & 0xFFFBFFFF;
      HIDWORD(v13) = (*(u64 *)&aiwk->m_status | 0x200000002000uLL) >> 32;
      *(u64 *)&aiwk->m_status = v13;
      if ((sBtlGetBadStatus(para) & 0xFFFFFFFE) != 0x10)
      {
        ShugouKaijyoSub(v10);
        status = v10->status;
        v10->asimoto_mode = 0;
        v10->fadepara = 16;
        v17 = v10->para;
        v10->color = -2139062144;
        v10->status = status & 0xFFFFFFFE;
        v10->vstatus &= 0xFFDFEFFC;
        if (sBtlGetBadStatus(v17) == 11)
          v10->color = -2136655252;
        v10->damagecnt = 0;
        continue;
      }
    }
  }
}

// 0x1fb5900
void sBtlNakamaWarpReset(void) {
  s64 v2;
  u32 stock_mask;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v8;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  sdatUnitWork_t *para;
  u32 status;
  sdatUnitWork_t *v15;
  s64 i;
  u32 v19;
  SBATTLE_WORK *v21;
  SBTLUNIT_LISTWORK *v22;
  s32 v23;
  SBTLUNIT_WORK *v24;
  SBTLUNIT_WORK *v25;
  sdatUnitWork_t *v26;
  s32 vstatus;
  sdatUnitWork_t *v29;

  if ((wk->status & 0x40000) == 0)
  {
    v2 = 0;
    while (1)
    {
      stock_mask = wk->stock_mask;
      if (((stock_mask >> v2) & 1) == 0)
        goto LABEL_6;
      if (wk->summonflg[v2] != 2)
        goto LABEL_6;
      UnitMng = wk->UnitMng;
      v8 = wk->summonID[v2];
      v9 = sBtlSearchUnit_ID(UnitMng, v8);
      if (!v9)
        goto LABEL_6;
      v10 = v9;
      para = v9->para;
      if ((sBtlGetBadStatus(para) & 0xFFFFFFFE) == 0x10)
        goto LABEL_6;
      ShugouKaijyoSub(v10);
      status = v10->status;
      v10->asimoto_mode = 0;
      v10->fadepara = 16;
      v15 = v10->para;
      v10->color = -2139062144;
      v10->status = status & 0xFFFFFFFE;
      v10->vstatus &= 0xFFDFEFFC;
      if (sBtlGetBadStatus(v15) == 11)
        goto LABEL_32;
      goto LABEL_9001;
      if (sBtlGetBadStatus(v15) == 11)
LABEL_32:
        v10->color = -2136655252;
LABEL_9001:
      v10->damagecnt = 0;
LABEL_6:
      if (++v2 == 32)
        return;
    }
  }
  for (i = 0; i != 32; ++i)
  {
    v19 = wk->stock_mask;
    if (((v19 >> i) & 1) == 0)
      continue;
    v21 = wk;
    if (v21->summonflg[i] == 2)
    {
      v21 = wk;
      v22 = v21->UnitMng;
      v23 = v21->summonID[i];
      v24 = sBtlSearchUnit_ID(v22, v23);
      if (!v24)
        continue;
      v25 = v24;
      v26 = v24->para;
      if ((sBtlGetBadStatus(v26) & 0xFFFFFFFE) == 0x10)
        continue;
      vstatus = v25->vstatus;
      v25->asimoto_mode = 0;
      v25->fadepara = 16;
      v29 = v25->para;
      v25->color = -2139062144;
      v25->vstatus = vstatus & 0xFFDFEFFC;
      if (sBtlGetBadStatus(v29) == 11)
        v25->color = -2136655252;
      v25->damagecnt = 0;
      v25->chgcolor = 807411744;
      sBtlChangeModelColor(v25);
      continue;
    }
  }
}

// 0x1fb5de0
void sBtlReset_SupportAction_Shugou2(SBTLUNIT_WORK *wkNakama) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 color;

  if (wkNakama)
  {
    para = wkNakama->para;
    BadStatus = sBtlGetBadStatus(para);
    if (BadStatus > 0x13 || ((1 << BadStatus) & 0xB31DF) == 0)
    {
      wkNakama->flg |= 0x400u;
      wkNakama->aiwk->m_status |= 0x40000u;
      wkNakama->status |= 0x1000u;
      wkNakama->L2_muteki = 1;
      color = wkNakama->color;
      wkNakama->chgcolor = color & 0xFFFFFF | 0x40000000;
      sBtlChangeModelColor(wkNakama);
      wkNakama->color_chroma = -2147352062;
    }
  }
}

// 0x1fa9090
static s32 SummonInit(SBTLUNIT_WORK *wk, s32 _SummonMode, s32 _SummonIdx, s32 _SummonDevilID) {
  s32 v17;
  SBATTLE_WORK *v21;
  SBATTLE_WORK *v25;

  gSummonMode = SummonMode;
  gSummonDevilID = SummonDevilID;
  gSummonIdx = SummonIdx;
  gSummonStep = 0;
  sBtlResetAction(wk);
  wk->cmstatus = 0;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->setsuma_rowhit_skillid = 0;
  *(u16 *)&wk->setsuma_rowhit_done = 0;
  switch (SummonMode)
  {
    case 1:
      v21 = wk;
      v21->mode = 2;
      v21->kochokuCnt = 120;
      sBtlSetMotion(wk, 23, 0, 0, 0);
      wk->actwk->status = 1;
      v17 = 10;
      goto LABEL_25;
    case 2:
      v25 = wk;
      v25->mode = 2;
      v25->kochokuCnt = 120;
      sBtlSetMotion(wk, 23, 0, 0, 0);
      wk->actwk->status = 1;
      v17 = 20;
      goto LABEL_25;
    case 3:
    case 4:
      wk->motion_UseWait2 = 1;
      sBtlSetMotion(wk, 23, 0, 0, 0);
      wk->actwk->status = 1;
      sBtlSetSummonVoice(SummonDevilID);
      v17 = 0;
LABEL_25:
      gSummonStep = v17;
      gSummonStepFrame = 0;
      break;
    default:
      break;
  }
  sBtlStatusBitOn(wk, 0x10u);
  return 2;
}

// 0x1fb7640
static SBTLUNIT_WORK *GetSummonNakama(s32 ctrlSmnIdx) {
  s32 v5;
  s64 v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v8;

  v5 = wk->summonindex[ctrlSmnIdx];
  if (v5 < 0)
    return 0;
  v6 = (u16)v5;
  UnitMng = wk->UnitMng;
  v8 = wk->summonID[v6];
  return sBtlSearchUnit_ID(UnitMng, v8);
}

// 0x1f7f7b0
static s32 SummonProc(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  s32 v10;
  s32 v12;
  s32 v14;
  SBTLUNIT_WORK *SummonNakama;
  SBTLUNIT_WORK *v18;
  SBTLUNIT_WORK *v19;
  SBTLUNIT_WORK *v20;

  hModel = wk->hModel;
  mdlGetMotionFrameF(hModel);
  if (gSummonStep > 10)
  {
    if (gSummonStep == 11)
    {
LABEL_8:
      wk->mode = 1;
      goto LABEL_35;
    }
    if (gSummonStep != 20)
    {
      if (gSummonStep != 21)
        goto LABEL_35;
      goto LABEL_8;
    }
LABEL_16:
    v10 = gSummonStepFrame + 1;
    gSummonStepFrame = v10;
    if (v10 != 10)
      goto LABEL_18;
    goto LABEL_9001;
    if (v12 != 10)
    {
LABEL_18:
      goto LABEL_19;
LABEL_32:
      v14 = gSummonStep;
      gSummonStepFrame = 0;
      gSummonStep = v14 + 1;
      goto LABEL_35;
    }
LABEL_9001:
    sBtlSetSummonVoice(gSummonDevilID);
LABEL_19:
    if (gSummonStepFrame < 120)
      goto LABEL_35;
    goto LABEL_32;
  }
  if (gSummonStep)
  {
    if (gSummonStep != 10)
      goto LABEL_35;
    goto LABEL_16;
  }
  sBtlResetAction(wk);
  sBtlSetUseSkill(wk, 0, 0);
LABEL_35:
  if (wk->mode == 1)
  {
    RestartBattle();
    sBtlRestart_Scene();
    sBtlStatusBitOff(wk, 0xFFFFFFEF);
    SummonNakama = GetSummonNakama(0);
    if (SummonNakama)
    {
      v18 = SummonNakama;
      sBtlStatusBitOff(v18, 0xFFFFFFEF);
    }
    v19 = GetSummonNakama(1);
    if (v19)
    {
      v20 = v19;
      sBtlStatusBitOff(v20, 0xFFFFFFEF);
    }
    wk->scrFlag &= ~0x20000000u;
  }
  wk->vstatus |= 0x80u;
  return 2;
}

// 0x1fb5ef0
void sBtlSetSummonVoice(s32 devilid) {
  char **v4;

  switch (devilid)
  {
    case 1:
      v4 = &"PVA01A_50_002";
      goto LABEL_6;
    case 2:
      v4 = &"PVA01A_50_004";
      goto LABEL_6;
    case 3:
      v4 = &"PVA01A_50_006";
      goto LABEL_6;
    case 4:
      v4 = &"PVA01A_50_009";
      goto LABEL_6;
    case 5:
      v4 = &"PVA01A_50_005";
      goto LABEL_6;
    case 6:
      v4 = &"PVA01A_50_007";
      goto LABEL_6;
    case 7:
      v4 = &"PVA01A_50_046";
      goto LABEL_6;
    case 8:
      v4 = &"PVA01A_50_010";
      goto LABEL_6;
    case 9:
      v4 = &"PVA01A_50_017";
      goto LABEL_6;
    case 10:
      v4 = &"PVA01A_50_013";
      goto LABEL_6;
    case 11:
      v4 = &"PVA01A_50_015";
      goto LABEL_6;
    case 12:
      v4 = &"PVA01A_50_020";
      goto LABEL_6;
    case 13:
      v4 = &"PVA01A_50_000";
      goto LABEL_6;
    case 14:
      v4 = &"PVA01A_50_022";
      goto LABEL_6;
    case 15:
      v4 = &"PVA01A_50_019";
      goto LABEL_6;
    case 16:
      v4 = &"PVA01A_50_021";
      goto LABEL_6;
    case 17:
      v4 = &"PVA01A_50_018";
      goto LABEL_6;
    case 18:
      v4 = &"PVA01A_50_023";
      goto LABEL_6;
    case 19:
      v4 = &"PVA01A_50_027";
      goto LABEL_6;
    case 20:
      v4 = &"PVA01A_50_029";
      goto LABEL_6;
    case 21:
      v4 = &"PVA01A_50_032";
      goto LABEL_6;
    case 22:
      v4 = &"PVA01A_50_028";
      goto LABEL_6;
    case 23:
      v4 = &"PVA01A_50_035";
      goto LABEL_6;
    case 24:
      v4 = &"PVA01A_50_033";
      goto LABEL_6;
    case 25:
      v4 = &"PVA01A_50_034";
      goto LABEL_6;
    case 26:
      v4 = &"PVA01A_50_036";
      goto LABEL_6;
    case 27:
      v4 = &"PVA01A_50_025";
      goto LABEL_6;
    case 28:
      v4 = &"PVA01A_50_040";
      goto LABEL_6;
    case 29:
      v4 = &"PVA01A_50_039";
      goto LABEL_6;
    case 30:
      v4 = &"PVA01A_50_043";
      goto LABEL_6;
    case 31:
      v4 = &"PVA01A_50_045";
      goto LABEL_6;
    case 32:
      v4 = &"PVA01A_50_047";
      goto LABEL_6;
    case 33:
    case 72:
    case 73:
    case 74:
    case 75:
      v4 = &"PVA01A_50_079";
      goto LABEL_6;
    case 34:
      v4 = &"PVA01A_50_044";
      goto LABEL_6;
    case 35:
      v4 = &"PVA01A_50_042";
      goto LABEL_6;
    case 36:
      v4 = &"PVA01A_50_049";
      goto LABEL_6;
    case 37:
      v4 = &"PVA01A_50_050";
      goto LABEL_6;
    case 38:
      v4 = &"PVA01A_50_054";
      goto LABEL_6;
    case 39:
      v4 = &"PVA01A_50_053";
      goto LABEL_6;
    case 40:
      v4 = &"PVA01A_50_055";
      goto LABEL_6;
    case 41:
      v4 = &"PVA01A_50_058";
      goto LABEL_6;
    case 42:
      v4 = &"PVA01A_50_060";
      goto LABEL_6;
    case 43:
      v4 = &"PVA01A_50_059";
      goto LABEL_6;
    case 44:
      v4 = &"PVA01A_50_056";
      goto LABEL_6;
    case 45:
      v4 = &"PVA01A_50_008";
      goto LABEL_6;
    case 46:
      v4 = &"PVA01A_50_061";
      goto LABEL_6;
    case 47:
      v4 = &"PVA01A_50_062";
      goto LABEL_6;
    case 48:
      v4 = &"PVA01A_50_063";
      goto LABEL_6;
    case 49:
      v4 = &"PVA01A_50_074";
      goto LABEL_6;
    case 50:
      v4 = &"PVA01A_50_070";
      goto LABEL_6;
    case 51:
      v4 = &"PVA01A_50_072";
      goto LABEL_6;
    case 52:
      v4 = &"PVA01A_50_065";
      goto LABEL_6;
    case 53:
      v4 = &"PVA01A_50_067";
      goto LABEL_6;
    case 54:
      v4 = &"PVA01A_50_069";
      goto LABEL_6;
    case 55:
      v4 = &"PVA01A_50_075";
      goto LABEL_6;
    case 56:
      v4 = &"PVA01A_50_076";
      goto LABEL_6;
    case 57:
      v4 = &"PVA01A_50_073";
      goto LABEL_6;
    case 58:
      v4 = &"PVA01A_50_078";
      goto LABEL_6;
    case 59:
      v4 = &"PVA01A_50_083";
      goto LABEL_6;
    case 60:
      v4 = &"PVA01A_50_081";
      goto LABEL_6;
    case 61:
      v4 = &"PVA01A_50_086";
      goto LABEL_6;
    case 62:
      v4 = &"PVA01A_50_091";
      goto LABEL_6;
    case 63:
      v4 = &"PVA01A_50_087";
      goto LABEL_6;
    case 64:
      v4 = &"PVA01A_50_089";
      goto LABEL_6;
    case 65:
      v4 = &"PVA01A_50_090";
      goto LABEL_6;
    case 66:
      v4 = &"PVA01A_50_016";
      goto LABEL_6;
    case 67:
      v4 = &"PVA01A_50_084";
      goto LABEL_6;
    case 68:
      v4 = &"PVA01A_50_088";
      goto LABEL_6;
    case 69:
      v4 = &"PVA01A_50_071";
      goto LABEL_6;
    case 70:
      v4 = &"PVA01A_50_057";
      goto LABEL_6;
    case 71:
      v4 = &"PVA01A_50_003";
LABEL_6:
      sndVoicePlayFile(*v4, 0);
      break;
    default:
      switch (devilid)
      {
        case 337:
          v4 = &"PVA01A_50_098";
          goto LABEL_6;
        case 338:
          v4 = &"PVA01A_50_097";
          goto LABEL_6;
        case 339:
          v4 = &"PVA01A_50_095";
          goto LABEL_6;
        case 340:
          v4 = &"PVA01A_50_094";
          goto LABEL_6;
        case 341:
          v4 = &"PVA01A_50_096";
          goto LABEL_6;
        case 342:
          v4 = &"PVA01A_50_093";
          goto LABEL_6;
        case 345:
        case 349:
          v4 = &"PVA01A_50_101";
          goto LABEL_6;
        case 346:
        case 350:
          v4 = &"PVA01A_50_099";
          goto LABEL_6;
        case 347:
        case 351:
          v4 = &"PVA01A_50_100";
          goto LABEL_6;
        case 348:
        case 352:
          v4 = &"PVA01A_50_102";
          goto LABEL_6;
        case 353:
          v4 = &"PVA01A_50_001";
          goto LABEL_6;
        case 354:
          v4 = &"PVA01A_50_011";
          goto LABEL_6;
        case 355:
          v4 = &"PVA01A_50_114";
          goto LABEL_6;
        case 356:
          v4 = &"PVA01A_50_115";
          goto LABEL_6;
        case 357:
          v4 = &"PVA01A_50_116";
          goto LABEL_6;
        case 358:
          v4 = &"PVA01A_50_012";
          goto LABEL_6;
        case 359:
          v4 = &"PVA01A_50_014";
          goto LABEL_6;
        case 360:
          v4 = &"PVA01A_50_024";
          goto LABEL_6;
        case 361:
          v4 = &"PVA01A_50_120";
          goto LABEL_6;
        case 362:
          v4 = &"PVA01A_50_123";
          goto LABEL_6;
        case 363:
          v4 = &"PVA01A_50_031";
          goto LABEL_6;
        case 364:
          v4 = &"PVA01A_50_026";
          goto LABEL_6;
        case 365:
          v4 = &"PVA01A_50_030";
          goto LABEL_6;
        case 366:
          v4 = &"PVA01A_50_037";
          goto LABEL_6;
        case 367:
          v4 = &"PVA01A_50_125";
          goto LABEL_6;
        case 368:
          v4 = &"PVA01A_50_038";
          goto LABEL_6;
        case 369:
          v4 = &"PVA01A_50_041";
          goto LABEL_6;
        case 370:
          v4 = &"PVA01A_50_048";
          goto LABEL_6;
        case 371:
          v4 = &"PVA01A_50_130";
          goto LABEL_6;
        case 372:
          v4 = &"PVA01A_50_131";
          goto LABEL_6;
        case 373:
          v4 = &"PVA01A_50_051";
          goto LABEL_6;
        case 374:
          v4 = &"PVA01A_50_052";
          goto LABEL_6;
        case 375:
          v4 = &"PVA01A_50_064";
          goto LABEL_6;
        case 376:
          v4 = &"PVA01A_50_141";
          goto LABEL_6;
        case 378:
          v4 = &"PVA01A_50_066";
          goto LABEL_6;
        case 379:
          v4 = &"PVA01A_50_068";
          goto LABEL_6;
        case 380:
          v4 = &"PVA01A_50_077";
          goto LABEL_6;
        case 381:
          v4 = &"PVA01A_50_147";
          goto LABEL_6;
        case 382:
          v4 = &"PVA01A_50_148";
          goto LABEL_6;
        case 383:
          v4 = &"PVA01A_50_080";
          goto LABEL_6;
        case 384:
          v4 = &"PVA01A_50_082";
          goto LABEL_6;
        case 385:
          v4 = &"PVA01A_50_085";
          goto LABEL_6;
        case 386:
          v4 = &"PVA01A_50_092";
          goto LABEL_6;
        case 387:
          v4 = &"PVA01A_50_157";
          goto LABEL_6;
        case 389:
          v4 = &"PVA01A_50_117";
          goto LABEL_6;
        case 391:
          v4 = &"PVA01A_50_124";
          goto LABEL_6;
        case 393:
          v4 = &"PVA01A_50_126";
          goto LABEL_6;
        case 394:
          v4 = &"PVA01A_50_127";
          goto LABEL_6;
        case 395:
          v4 = &"PVA01A_50_133";
          goto LABEL_6;
        case 396:
          v4 = &"PVA01A_50_134";
          goto LABEL_6;
        case 397:
          v4 = &"PVA01A_50_149";
          goto LABEL_6;
        case 398:
          v4 = &"PVA01A_50_150";
          goto LABEL_6;
        case 496:
        case 497:
        case 498:
          switch ((u32)sub_1905740(5, 0))
          {
            case 0u:
              v4 = &"PVA01A_40A_000";
              goto LABEL_6;
            case 1u:
              v4 = &"PVA01A_40A_001";
              goto LABEL_6;
            case 2u:
              v4 = &"PVA01A_40A_002";
              goto LABEL_6;
            case 3u:
              v4 = &"PVA01A_40A_003";
              goto LABEL_6;
            case 4u:
              v4 = &"PVA01A_40B_000";
              goto LABEL_6;
            default:
              return;
          }
        case 499:
          v4 = &"PVA01A_50_128";
          goto LABEL_6;
        case 500:
          v4 = &"PVA01A_50_137";
          goto LABEL_6;
        case 501:
          v4 = &"PVA01A_50_138";
          goto LABEL_6;
        default:
          return;
      }
  }
}

// 0x1f6f620
void sBtlInitAutoTaget(void) {
  __int128 v2;

  *(u64 *)&v2 = 0xFFFFFFFFLL;
  *((u64 *)&v2 + 1) = 0xFFFFFFFFLL;
  *(_OWORD *)&gAutoTgt_NextID = v2;
}

// 0x1fb7750
void sBtlSetAutoTagetDamage(SBTLUNIT_WORK *wk_player, SBTLUNIT_WORK *wk_enemy) {
  s32 targetID;
  __int128 v7;
  __int128 v10;
  bool v12;
  f32 x;
  f32 z;
  f32 v15;
  f32 v16;
  f32 LenXZ;
  f32 v19;
  s32 ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  s32 v33;
  f32 v34;
  s32 v35;
  SBTLUNIT_LISTWORK *v38;
  s32 v41;
  SBTLUNIT_WORK *v42;
  SBTLUNIT_WORK *v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  s32 v49;
  s32 v53;
  f32 v55;

  if (!wk_player || !wk_enemy)
    return;
  targetID = wk_player->actaiwk->targetID;
  if (targetID == wk_enemy->ListID)
  {
    wk_enemy->AutoTgtDmgCnt = 0;
    *(u64 *)&v7 = 0xFFFFFFFFLL;
    *((u64 *)&v7 + 1) = 0xFFFFFFFFLL;
    *(_OWORD *)&gAutoTgt_NextID = v7;
    return;
  }
  if (gAutoTgt_NextID != targetID)
  {
    if ((wk_enemy->side & 2) == 0)
      goto LABEL_34;
    goto LABEL_18;
  }
  *(u64 *)&v10 = 0xFFFFFFFFLL;
  *((u64 *)&v10 + 1) = 0xFFFFFFFFLL;
  *(_OWORD *)&gAutoTgt_NextID = v10;
  if ((wk_enemy->side & 2) == 0)
    goto LABEL_34;
  goto LABEL_9001;
  if ((wk_enemy->side & 2) == 0)
  {
LABEL_34:
    if (gAutoTgt_NextID == wk_enemy->ListID)
    {
      gAutoTgt_NextID = -1;
      *(u64 *)&gAutoTgt_NextCnt = 0xFFFFFFFF00000000LL;
    }
    return;
  }
LABEL_9001:
LABEL_18:
  if ((wk_enemy->status & 0x4000000) != 0 || (wk_enemy->vstatus & 0x10000) != 0)
    goto LABEL_34;
  v12 = sBtlCheckDamageTarget(wk_enemy);
  if (!v12)
    goto LABEL_34;
  if (gAutoTgt_NextID == wk_enemy->ListID)
    return;
  x = wk_player->pos.x;
  z = wk_player->pos.z;
  v15 = wk_enemy->pos.x;
  v16 = wk_enemy->pos.z;
  LenXZ = sBtlGetLenXZ(x, z, v15, v16);
  v19 = LenXZ;
  ListID = wk_enemy->ListID;
  if (gAutoTgt_LastDmgID == ListID)
  {
    ++gAutoTgt_LastDmgCnt;
  }
  else
  {
    gAutoTgt_LastDmgID = ListID;
    gAutoTgt_LastDmgCnt = 0;
  }
  UnitMng = wk->UnitMng;
  v26 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v26)
    goto LABEL_59;
  goto LABEL_50;
  if (!v26)
  {
LABEL_59:
    v34 = 9999.0;
    v35 = 0;
    v33 = 0;
    goto LABEL_60;
  }
LABEL_50:
  if ((v26->side & 2) == 0 || (v26->status & 0x4000000) != 0 || (v26->vstatus & 0x10000) != 0)
    goto LABEL_59;
  if (!sBtlCheckLiveTarget_NotHitDmg(v26))
    goto LABEL_59;
  v27 = wk_player->pos.x;
  v28 = wk_player->pos.z;
  v29 = v26->pos.x;
  v30 = v26->pos.z;
  v31 = v26->pos.x;
  v32 = v26->pos.z;
  v30 = v32;
  v29 = v31;
  v33 = 1;
  v34 = sBtlGetLenXZ(v27, v28, v29, v30) - v26->actaiwk->hit_area_r;
  v35 = ((u32)v26->para->aisyo->para[0] >> 12) & 1;
LABEL_60:
  if (gAutoTgt_NextID == -1)
  {
LABEL_92:
    if (v33)
    {
      if (gAutoTgt_LastDmgCnt >= 4)
      {
        if (v34 > 800.0 ? 1 : v35)
          goto LABEL_100;
      }
      return;
    }
LABEL_102:
    wk_enemy->AutoTgtDmgCnt = 0;
    v53 = wk_enemy->ListID;
    gAutoTgt_NextID = v53;
    gAutoTgt_NextCnt = 0;
    return;
  }
  if (gAutoTgt_NextID == wk_enemy->ListID)
    return;
  v38 = wk->UnitMng;
  v41 = gAutoTgt_NextID;
  v42 = sBtlSearchUnit_ID(v38, v41);
  if (!v42)
    goto LABEL_92;
  v43 = v42;
  if ((v42->side & 2) == 0 || (v42->status & 0x4000000) != 0 || (v42->vstatus & 0x10000) != 0)
    goto LABEL_92;
  if (!sBtlCheckDamageTarget(v43))
    goto LABEL_92;
  v55 = v34;
  v44 = wk_player->pos.x;
  v45 = wk_player->pos.z;
  v46 = v43->pos.x;
  v47 = v43->pos.z;
  v34 = sBtlGetLenXZ(v44, v45, v46, v47) - v43->actaiwk->hit_area_r;
  if (!v33)
  {
    if (v19 >= v34)
      return;
    goto LABEL_102;
  }
  if (gAutoTgt_LastDmgCnt >= 4)
  {
    v49 = v55 > 800.0 ? 1 : v35;
    if (v49 && v19 < v55)
    {
LABEL_100:
      if (v19 >= v34 || v26->AutoTgtDmgCnt <= 60)
        return;
      goto LABEL_102;
    }
  }
}

// 0x1f969c0
void sBtlResetAutoTaget(SBTLUNIT_WORK *wk_player, s32 old_targetID) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v8;
  s32 targetID;
  SBTLUNIT_LISTWORK *v11;
  SBTLUNIT_WORK *v12;

  if (wk_player)
  {
    *(u64 *)&gAutoTgt_NextID = 0xFFFFFFFFLL;
    if (old_targetID != -1)
    {
      UnitMng = wk->UnitMng;
      v8 = sBtlSearchUnit_ID(UnitMng, old_targetID);
      if (v8)
        v8->AutoTgtDmgCnt = 0;
    }
    targetID = wk_player->actaiwk->targetID;
    if (targetID != -1)
    {
      v11 = wk->UnitMng;
      v12 = sBtlSearchUnit_ID(v11, targetID);
      if (v12)
        v12->AutoTgtDmgCnt = 0;
    }
  }
}

// 0x1f95340
void sBtlUpdateAutoTaget(SBTLUNIT_WORK *wk_player) {
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 AutoTgtDmgCnt;
  s32 v8;
  s32 v11;
  bool v12;
  SBTLUNIT_LISTWORK *v15;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  SBTLACTAI_WORK *actaiwk;
  s32 v22;

  if (!wk_player)
    return;
  targetID = wk_player->actaiwk->targetID;
  if (targetID != -1)
  {
    UnitMng = wk->UnitMng;
    v6 = sBtlSearchUnit_ID(UnitMng, targetID);
    if (v6 && (wk_player->hstatus & 0x4000) == 0)
    {
      AutoTgtDmgCnt = v6->AutoTgtDmgCnt;
      if (AutoTgtDmgCnt + 1 < 999)
        v8 = AutoTgtDmgCnt + 1;
      else
        v8 = 999;
      v6->AutoTgtDmgCnt = v8;
    }
  }
  if (gAutoTgt_NextID == -1)
    return;
  v11 = gAutoTgt_NextCnt + 1;
  v12 = gAutoTgt_NextCnt - 25 < 0;
  gAutoTgt_NextCnt = v11;
  if (v12 != __OFSUB__(v11, 26))
    return;
  v15 = wk->UnitMng;
  v17 = sBtlSearchUnit_ID(v15, gAutoTgt_NextID);
  if (!v17)
    goto LABEL_40;
  goto LABEL_9000;
  if (!v17)
  {
LABEL_40:
    *(u64 *)&gAutoTgt_NextID = 0xFFFFFFFFLL;
    return;
  }
LABEL_9000:
  v18 = v17;
  if ((v17->side & 2) == 0 || (v17->status & 0x4000000) != 0 || (v17->vstatus & 0x10000) != 0)
    goto LABEL_40;
  if (!sBtlCheckDamageTarget(v18))
    goto LABEL_40;
  actaiwk = wk_player->actaiwk;
  v22 = actaiwk->targetID;
  actaiwk->targetID = gAutoTgt_NextID;
  sBtlResetAutoTaget(wk_player, v22);
}

// 0x1fb7da0
bool sBtlGetRandomTarget(SBTLUNIT_WORK *wk, s32 flg, bool bNewTgt) {
  sdfVector4_t *p_rot;
  f32 x;
  f32 w;
  f32 y;
  f32 z;
  s32 targetID;
  f32 RotToDir;
  f32 AnlogKeyToDir;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 turn_goal;
  SBTLACTAI_WORK *actaiwk;
  s32 v25;
  SBTLACTAI_WORK *v27;
  s32 targetID_Mawari;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v31;
  SBTLUNIT_LISTWORK *v33;
  SBTLACTAI_WORK *v34;
  f32 v35;
  s32 v36;
  SBTLACTAI_WORK *v37;
  f32 v38;
  SBTLUNIT_WORK *v39;
  SBTLUNIT_LISTWORK *v41;
  SBTLUNIT_WORK *v42;
  s32 v44;
  s32 use_skillid;
  u32 v46;
  s32 v47;
  SBTLUNIT_LISTWORK *v49;
  SBTLUNIT_WORK *v50;
  s32 devilid;
  f32 Dir180;
  s32 v54;
  SBTLUNIT_LISTWORK *v56;
  SBTLUNIT_WORK *v57;
  f32 v58;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 PosToDir;
  f32 v65;
  sdfVector4_t *p_rotbk;
  f32 dir;
  sdfVector4_t v74;

  p_rot = &wk->rot;
  x = wk->rot.x;
  dir = 0.0;
  w = wk->rot.w;
  y = wk->rot.y;
  z = wk->rot.z;
  targetID = wk->actaiwk->targetID;
  v74.x = x;
  v74.y = y;
  v74.z = z;
  v74.w = w;
  RotToDir = sBtlGetRotToDir(v74);
  AnlogKeyToDir = GetAnlogKeyToDir(wk, &dir);
  v16 = wk->pos.z;
  v17 = wk->pos.x;
  v18 = wk->pos.y;
  v20 = 360.0 - mapGetScreenDir(v17, v18, v16, 0.0);
  if (v20 >= 360.0)
    v20 = 0.0;
  v21 = dir + v20;
  v22 = v21 + -360.0;
  if (v21 >= 360.0)
    turn_goal = v21 + -360.0;
  else
    turn_goal = v21;
  if ((u32)(wk->next_motionID - 107) > 2)
    goto LABEL_18;
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_18;
  goto LABEL_17;
  if (!sBtlCheckMotionEnd(wk))
LABEL_17:
    turn_goal = wk->turn_goal;
LABEL_18:
  switch (flg)
  {
    case 0:
      targetID_Mawari = wk->actaiwk->targetID_Mawari;
      if (targetID_Mawari != -1)
      {
        UnitMng = wk->UnitMng;
        if (sBtlSearchUnit_ID(UnitMng, targetID_Mawari))
        {
          v31 = wk->actaiwk->targetID_Mawari;
          goto LABEL_43;
        }
      }
      v41 = wk->UnitMng;
      v42 = sBtlSearchUnit_ID(v41, targetID);
      if (v42)
      {
        if ((v42->side & 2) != 0)
          goto LABEL_82;
      }
      sBtlSetTargetID(wk, -1);
      if (AnlogKeyToDir >= 48.0)
        RotToDir = turn_goal;
      v44 = sBtlGetNearTarget2(wk, RotToDir, 400.0, 90.0, 0);
      sBtlSetTargetID(wk, v44);
      targetID = -1;
      goto LABEL_82;
    case 1:
      goto LABEL_82;
    case 3:
    case 4:
    case 6:
      actaiwk = wk->actaiwk;
      v25 = actaiwk->targetID_Mawari;
      if (v25 != -1)
      {
        v25 = wk->actaiwk->targetID_Mawari;
        v33 = wk->UnitMng;
        if (sBtlSearchUnit_ID(v33, v25))
        {
          v31 = wk->actaiwk->targetID_Mawari;
LABEL_43:
          sBtlSetTargetID(wk, v31);
          goto LABEL_82;
        }
        if (!bNewTgt)
          goto LABEL_82;
LABEL_28:
        switch (flg)
        {
          case 3:
            v34 = wk->actaiwk;
            if (AnlogKeyToDir >= 48.0)
              v35 = turn_goal;
            else
              v35 = RotToDir;
            v36 = sBtlGetNearTargetScore(wk, RotToDir, v35, v22, 0);
            v37 = wk->actaiwk;
            v34->targetID = v36;
            if (v37->targetID == -1)
            {
              v38 = v35;
              v39 = wk;
              goto LABEL_61;
            }
            break;
          case 4:
          case 16:
            v27 = wk->actaiwk;
            v27->targetID = sBtlGetNearTargetScore(wk, RotToDir, RotToDir, v22, 0);
            break;
          case 7:
            if (AnlogKeyToDir >= 48.0)
              RotToDir = turn_goal;
            v39 = wk;
            v38 = RotToDir;
LABEL_61:
            v31 = sBtlGetNearTarget2(v39, v38, 400.0, 90.0, 0);
            goto LABEL_43;
          default:
            goto LABEL_82;
        }
        goto LABEL_82;
      }
      if (actaiwk->targetID != -1)
        goto LABEL_82;
LABEL_27:
      if (bNewTgt)
        goto LABEL_28;
LABEL_82:
      if (wk->actaiwk->targetID != -1)
        goto LABEL_85;
      if (targetID == wk->playerID)
        goto LABEL_85;
      goto LABEL_9002;
      if (targetID == wk->playerID)
      {
LABEL_85:
        use_skillid = wk->actwk->use_skillid;
        if ((use_skillid & 0xFFFFFFFE) == 0x510)
          goto LABEL_86;
LABEL_95:
        v46 = use_skillid - 1299;
        if (v46 < 0x15 && ((0x18000Fu >> v46) & 1) != 0)
          goto LABEL_154;
        goto LABEL_97;
      }
LABEL_9002:
      sBtlSetTargetID(wk, targetID);
      use_skillid = wk->actwk->use_skillid;
      if ((use_skillid & 0xFFFFFFFE) != 0x510)
        goto LABEL_95;
LABEL_86:
      if (wk->CameraGazeOff)
        goto LABEL_154;
LABEL_97:
      v47 = wk->actaiwk->targetID;
      if (v47 == -1)
        goto LABEL_112;
      v49 = wk->UnitMng;
      v50 = sBtlSearchUnit_ID(v49, v47);
      if (!v50)
        goto LABEL_112;
      devilid = (u16)v50->para->devilid;
      if (devilid == 314 || devilid == 258)
      {
        Dir180 = sBtlGetDir180(0.0);
        wk->mv_rotbk = Dir180;
        FromEuler(0.0, Dir180 * 0.017453292, 0.0);
        *p_rot = vct_A;
        wk->rotbk = vct_A;
        wk->front_deg = wk->mv_rotbk;
        goto LABEL_146;
      }
LABEL_112:
      v54 = wk->actaiwk->targetID;
      if (v54 == -1)
      {
        if (AnlogKeyToDir >= 48.0)
        {
          v58 = sBtlGetDir180(turn_goal);
          wk->mv_rotbk = v58;
          FromEuler(0.0, v58 * 0.017453292, 0.0);
          *p_rot = vct_A;
          p_rotbk = &wk->rotbk;
          *p_rotbk = vct_A;
          goto LABEL_154;
        }
LABEL_154:
        LOBYTE(v57) = 1;
        return (char)v57;
      }
      v56 = wk->UnitMng;
      v57 = sBtlSearchUnit_ID(v56, v54);
      if (!v57)
        return (char)v57;
      v60 = v57->pos.x;
      v61 = v57->pos.z;
      v62 = wk->pos.x;
      v63 = wk->pos.z;
      PosToDir = sBtlGetPosToDir(v62, v63, v60, v61);
      v65 = sBtlGetDir180(PosToDir);
      wk->mv_rotbk = v65;
      FromEuler(0.0, v65 * 0.017453292, 0.0);
      *p_rot = vct_A;
      wk->front_deg = PosToDir;
      wk->rotbk = vct_A;
LABEL_146:
      wk->actaiwk->targetID_Last = wk->actaiwk->targetID;
      goto LABEL_154;
    case 5:
    case 7:
      if (wk->actaiwk->targetID != -1)
        goto LABEL_82;
      goto LABEL_27;
    default:
      goto LABEL_27;
  }
}

// 0x1f97c20
static void DecideTarget(bool bFirst, SKLID _Old_skillid) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v5;
  s32 use_skillid;
  s32 v7;
  s32 v9;
  char v10;
  SBTLUNIT_WORK *v11;
  s32 v12;

  PChara = sBtlGetPChara();
  v5 = sBtlGetPChara();
  sBtlGetSkilltbl(v5->actwk->use_skillid);
  use_skillid = sBtlGetPChara()->actwk->use_skillid;
  if (use_skillid <= 164)
  {
    if (use_skillid == 144)
    {
      if (PChara->motionno == 42)
        v7 = 11;
      else
        v7 = 10;
    }
    else if (use_skillid == 164)
    {
      v7 = 20;
    }
    else
    {
LABEL_10:
      v7 = 0;
    }
  }
  else
  {
    if ((u32)(use_skillid - 167) > 0xFFFFFFFD)
      return;
    v7 = 5;
    switch (use_skillid)
    {
      case 1304:
      case 1305:
      case 1306:
      case 1316:
      case 1317:
        v7 = 7;
        break;
      case 1307:
        break;
      case 1333:
        if (PChara->motionno == 41)
          v7 = 10;
        else
          v7 = 11;
        break;
      default:
        goto LABEL_10;
    }
  }
  if (sBtlGetPChara()->actwk->use_skillid == 1299)
    v9 = 6;
  else
    v9 = v7;
  switch (v9)
  {
    case 0:
      v10 = bFirst;
      v11 = PChara;
      v12 = 0;
      goto LABEL_21;
    case 5:
      v11 = PChara;
      v12 = 3;
      v10 = 1;
      goto LABEL_21;
    case 6:
      v11 = PChara;
      v12 = 4;
      v10 = 1;
      goto LABEL_21;
    case 10:
      v11 = PChara;
      v12 = 1;
      v10 = 1;
      goto LABEL_21;
    case 11:
      v11 = PChara;
      v12 = 7;
      v10 = 1;
      goto LABEL_21;
    case 20:
      v11 = PChara;
      v12 = 16;
      v10 = 1;
LABEL_21:
      sBtlGetRandomTarget(v11, v12, v10);
      break;
    default:
      return;
  }
}

// 0x1fb9930
s32 sBtlGetNearTarget_Random(SBTLUNIT_WORK *wk, const sdfVector4_t *a_rot, f32 area_r, f32 rad0, f32 rad1, s8 flg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s32 v12;
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  f32 *p_x;
  f32 *v20;
  SBATTLE_WORK *v22;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  s64 v24;
  s16 v25;
  SBTLUNIT_LISTWORK *v27;
  s64 count;
  SBTLUNIT_WORK *pUnit;
  f32 hit_area_r;
  f32 *v33;
  f32 v34;
  f32 v35;
  f32 v36;
  struct sdfVector4_t v38;
  f32 area;
  f32 v42;
  struct sdfVector4_t v45;
  f32 *v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v51;
  struct sdfVector4_t v53;
  f32 *v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v59;
  struct sdfVector4_t v61;
  f32 *v62;
  f32 v63;
  f32 v64;
  f32 v65;
  s32 v67;
  f32 v68;
  f32 v69;
  s32 v74;
  s16 v75;
  s32 ListID;
  s32 LargePara;
  SBTLUNIT_LISTWORK *v81;
  SBTLUNIT_LISTWORK *v82;
  u32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  f32 v89;
  s32 v90;
  s16 *adr;
  struct sdfVector4_t pos;
  struct sdfVector4_t v93;
  struct sdfVector4_t v94;
  struct sdfVector4_t v95;
  struct sdfVector4_t v96;
  struct sdfVector4_t v97;
  s32 v105;
  sdfVector4_t v106;
  sdfVector4_t v107;
  sdfVector4_t v108;
  sdfVector4_t v109;
  sdfVector4_t v110;
  sdfVector4_t v111;
  sdfVector4_t v112;
  sdfVector4_t v113;

  w = a_rot->w;
  z = a_rot->z;
  y = a_rot->y;
  x = a_rot->x;
  LOBYTE(v12) = flg;
  adr = NewSpecific(s16, 0x30u);
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
    goto LABEL_9;
  }
LABEL_9:
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v20 = &vf00.x;
  v88 = v20[5];
  v89 = v20[4];
  v86 = v20[7];
  v87 = v20[6];
  v12 = (u8)v12;
  v22 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v22->other_List2 = TargetList_MASK;
  v24 = 0;
  v84 = v12 - 2;
  v105 = 0;
  v90 = -1;
  v85 = area_r;
  while (1)
  {
    v27 = wk->other_List2;
    count = v27->count;
    if (v24 >= count)
      break;
    v27 = wk->other_List2;
    pUnit = v27->pUnitL[v24]->pUnit;
    hit_area_r = pUnit->actaiwk->hit_area_r;
    if (!sBtlCheckLiveTarget_NotHitDmg(wk))
      goto LABEL_19;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && v12 != 1 && (v12 != 2 || (pUnit->hstatus & 0x10) != 0 && !pUnit->damagecnt))
    {
      pos = wk->pos;
      goto LABEL_37;
LABEL_38:
      vct_A = pos;
      goto LABEL_39;
LABEL_40:
      v33 = &vf00.x;
      v34 = v33[4];
      v36 = v33[6];
      v35 = v33[7];
      v38 = pUnit->pos;
      v93 = v38;
      v38 = v93;
      v94 = v38;
      vct_A = v94;
      area = vct_A.x;
      v42 = vct_A.z;
      goto LABEL_61;
LABEL_65:
      switch (v12)
      {
        case 2:
        case 4:
          v108.y = 0.0;
          v108.z = v36;
          v111.y = v88;
          v111.x = v89;
          v108.w = v35;
          v111.w = v86;
          v111.z = v87;
          *(u64 *)&v106.x = 0;
          v108.x = v34;
          if (sBtlCheckVerticalArea(v108, v111, v106, area))
            goto LABEL_69;
          goto LABEL_19;
        case 5:
          v96 = wk->pos;
          vct_A = v96;
          v53 = pUnit->pos;
          vct_B = v53;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v54 = &vf00.x;
          v55 = v54[4];
          v56 = v54[5];
          v57 = v54[6];
          v59 = sqrtf((f32)((f32)(v55 * v55) + (f32)(v56 * v56)) + (f32)(v57 * v57)) - hit_area_r;
          if (v59 < 1.0)
            v59 = 1.0;
          if (v59 >= area_r)
            goto LABEL_19;
          v97 = wk->pos;
          vct_A = v97;
          v61 = pUnit->pos;
          vct_B = v61;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v62 = &vf00.x;
          v63 = v62[4];
          v64 = v62[5];
          v65 = v62[6];
          v67 = v90;
          v68 = sqrtf((f32)((f32)(v63 * v63) + (f32)(v64 * v64)) + (f32)(v65 * v65)) - hit_area_r;
          if (v68 < 1.0)
            v68 = 1.0;
          v69 = v85;
          if (v85 >= v68)
          {
            v69 = v68;
            v67 = v24;
          }
          v90 = v67;
          v25 = 20;
          v85 = v69;
          break;
        case 6:
          sBtlGetLenXZ(v34, v36, area, v42);
          if (rad0 <= 1.0)
          {
            v110.y = 0.0;
            v110.w = v35;
            *(u64 *)&v107.x = 0;
            v113.y = v88;
            v113.x = v89;
            v113.w = v86;
            v113.z = v87;
            v110.z = v36;
            v110.x = v34;
            if (sBtlCheckCrossCircle_Rot(v110, v113, area_r, v107, area, v42))
              goto LABEL_17;
          }
          goto LABEL_19;
        default:
          goto LABEL_87;
      }
      goto LABEL_18;
LABEL_61:
      if ((u32)(v12 - 2) <= 4)
        goto LABEL_65;
LABEL_87:
      if (rad0 < 1.0)
      {
        v109.y = 0.0;
        v109.z = v36;
        v112.y = v88;
        v112.x = v89;
        v109.w = v35;
        v112.w = v86;
        v112.z = v87;
        *(u64 *)&v106.x = 0;
        v109.x = v34;
        if (sBtlCheckCrossCircle_Rot(v109, v112, area_r, v106, area, v42))
        {
          if (v84 <= 2)
          {
LABEL_69:
            v95 = wk->pos;
            vct_A = v95;
            v45 = pUnit->pos;
            goto LABEL_75;
LABEL_76:
            goto LABEL_9009;
LABEL_75:
            vct_B = v45;
            goto LABEL_76;
LABEL_9009:
            vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
            goto LABEL_80;
LABEL_81:
            goto LABEL_9010;
LABEL_80:
            v46 = &vf00.x;
            v47 = v46[4];
            v48 = v46[5];
            v49 = v46[6];
            goto LABEL_81;
LABEL_9010:
            v51 = sqrtf((f32)((f32)(v47 * v47) + (f32)(v48 * v48)) + (f32)(v49 * v49)) - hit_area_r;
            if (v51 < 1.0)
              v51 = 1.0;
            if (v85 >= v51)
            {
              v90 = v24;
              v85 = v51;
            }
          }
LABEL_17:
          v25 = GetIntervalRand(0, 15) + 20;
LABEL_18:
          adr[v24] = v25;
          ++v105;
          goto LABEL_19;
        }
      }
      goto LABEL_19;
LABEL_37:
      goto LABEL_38;
LABEL_39:
      goto LABEL_40;
    }
LABEL_19:
    ++v24;
  }
  if (!v105)
  {
    sBtlDeleteUnitList(v27, 0);
    ListID = -1;
    goto LABEL_187;
  }
  if (v84 >= 3)
  {
    v74 = v90;
    if (v12 == 5 && v90 != -1)
    {
      v75 = 100;
LABEL_181:
      adr[v74] = v75;
    }
  }
  else
  {
    v74 = v90;
    if (v90 != -1)
    {
      v75 = 60;
      goto LABEL_181;
    }
  }
  LargePara = sBtlGetLargePara(adr, count);
  v81 = wk->other_List2;
  ListID = v81->pUnitL[LargePara]->pUnit->ListID;
  sBtlDeleteUnitList(v81, 0);
LABEL_187:
  v82 = &wk->other_List2;
  v82 = 0;
  return ListID;
}

// 0x1fb8940
s32 sBtlGetNearTarget2(SBTLUNIT_WORK *wk, f32 dir, f32 area_r, f32 dirLR, s8 flg) {
  SBTLUNIT_LISTWORK *other_List2;
  SBATTLE_WORK *v14;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  f32 v16;
  s64 v17;
  s32 v18;
  s32 v19;
  SBTLUNIT_LISTWORK *v21;
  SBTLUNIT_WORK *pUnit;
  f32 hit_area_r;
  f32 x;
  f32 z;
  f32 v26;
  f32 v27;
  f32 LenXZ;
  f32 PosToDir;
  f32 AtoB_LR;
  f32 ABS;
  s32 ListID;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBTLUNIT_LISTWORK *v41;

  other_List2 = wk->other_List2;
  if (!other_List2)
  {
    goto LABEL_5;
  }
  sBtlDeleteUnitList(other_List2, 0);
  p_other_List2 = &wk->other_List2;
  p_other_List2 = 0;
LABEL_5:
  v14 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v14->other_List2 = TargetList_MASK;
  v16 = 999.0;
  v17 = 0;
  v18 = 0;
  v19 = -1;
  while (1)
  {
    v21 = wk->other_List2;
    if (v17 >= v21->count)
      break;
    v21 = wk->other_List2;
    pUnit = v21->pUnitL[v17]->pUnit;
    hit_area_r = pUnit->actaiwk->hit_area_r;
    if (!sBtlCheckLiveTarget_NotHitDmg(wk))
      goto LABEL_10;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && flg != 1 && (flg != 2 || (pUnit->hstatus & 0x10) != 0 && !pUnit->damagecnt))
    {
      x = wk->pos.x;
      z = wk->pos.z;
      v26 = pUnit->pos.x;
      v27 = pUnit->pos.z;
      LenXZ = sBtlGetLenXZ(x, z, v26, v27);
      PosToDir = sBtlGetPosToDir(wk->pos.x, wk->pos.z, pUnit->pos.x, pUnit->pos.z);
      AtoB_LR = sBtlGetAtoB_LR(dir, PosToDir);
      ABS = sBtlGetABS(AtoB_LR);
      switch (flg)
      {
        case 0:
        case 2:
        case 4:
          if (LenXZ <= area_r && ABS < dirLR)
            goto LABEL_8;
          break;
        case 3:
          if (LenXZ <= (f32)(hit_area_r + area_r) && ABS < dirLR)
            goto LABEL_8;
          break;
        case 5:
          if (LenXZ <= (f32)(hit_area_r + area_r))
            goto LABEL_8;
          break;
        case 6:
          goto LABEL_8;
        case 7:
          if (pUnit->ListID == wk->actaiwk->targetID_Last && LenXZ <= area_r && ABS < dirLR)
          {
LABEL_8:
            ++v18;
            if (v16 > ABS)
            {
              v16 = ABS;
              v19 = v17;
            }
          }
          break;
        default:
          break;
      }
    }
LABEL_10:
    ++v17;
  }
  if (!v18)
  {
    sBtlDeleteUnitList(v21, 0);
    ListID = -1;
    goto LABEL_66;
  }
  v21 = wk->other_List2;
  ListID = v21->pUnitL[v19]->pUnit->ListID;
  sBtlDeleteUnitList(v21, 0);
LABEL_66:
  v41 = &wk->other_List2;
  v41 = 0;
  return ListID;
}

// 0x1f96b20
s32 sBtlGetCameraTgtSelect1Score(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 AnlogKeyToDir;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 turn_goal;
  _BOOL4 CameraGazeOff;
  f32 v20;
  f32 dir;
  sdfVector4_t v23;

  dir = 0.0;
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  RotToDir = sBtlGetRotToDir(v23);
  AnlogKeyToDir = GetAnlogKeyToDir(wk, &dir);
  v10 = wk->pos.z;
  v11 = wk->pos.x;
  v12 = wk->pos.y;
  v14 = 360.0 - mapGetScreenDir(v11, v12, v10, 0.0);
  if (v14 >= 360.0)
    v14 = 0.0;
  v15 = dir + v14;
  v16 = v15 + -360.0;
  if (v15 >= 360.0)
    turn_goal = v15 + -360.0;
  else
    turn_goal = v15;
  if ((u32)(wk->next_motionID - 107) <= 2)
  {
    if (sBtlCheckMotionEnd(wk))
      goto LABEL_18;
    goto LABEL_17;
    if (!sBtlCheckMotionEnd(wk))
LABEL_17:
      turn_goal = wk->turn_goal;
  }
LABEL_18:
  CameraGazeOff = wk->CameraGazeOff;
  if (AnlogKeyToDir >= 48.0)
    v20 = turn_goal;
  else
    v20 = RotToDir;
  return sBtlGetNearTargetScore(wk, RotToDir, v20, v16, !CameraGazeOff);
}

// 0x1f96040
s32 sBtlGetEnemyDeadTgtSelect1Score(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 AnlogKeyToDir;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 turn_goal;
  f32 v18;
  f32 dir;
  sdfVector4_t v21;

  dir = 0.0;
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v21.x = x;
  v21.y = y;
  v21.z = z;
  v21.w = w;
  RotToDir = sBtlGetRotToDir(v21);
  AnlogKeyToDir = GetAnlogKeyToDir(wk, &dir);
  v10 = wk->pos.z;
  v11 = wk->pos.x;
  v12 = wk->pos.y;
  v14 = 360.0 - mapGetScreenDir(v11, v12, v10, 0.0);
  if (v14 >= 360.0)
    v14 = 0.0;
  v15 = dir + v14;
  v16 = v15 + -360.0;
  if (v15 >= 360.0)
    turn_goal = v15 + -360.0;
  else
    turn_goal = v15;
  if ((u32)(wk->next_motionID - 107) <= 2)
  {
    if (sBtlCheckMotionEnd(wk))
      goto LABEL_18;
    goto LABEL_17;
    if (!sBtlCheckMotionEnd(wk))
LABEL_17:
      turn_goal = wk->turn_goal;
  }
LABEL_18:
  if (AnlogKeyToDir >= 48.0)
    v18 = turn_goal;
  else
    v18 = RotToDir;
  return sBtlGetNearTargetScore(wk, RotToDir, v18, v16, 0);
}

// 0x1fb8de0
s32 sBtlGetNearTargetScore(SBTLUNIT_WORK *wk, f32 pdir, f32 sdir, f32 _KeyLength, bool _UseDone) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *v12;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  SBTLUNIT_LISTWORK *v14;
  s32 count;
  s64 v17;
  s64 v18;
  s64 v19;
  s64 v21;
  s64 v22;
  s64 v23;
  SBATTLE_WORK *v24;
  SBTLCAMERA_WORK *camera;
  f32 x;
  f32 z;
  f32 v28;
  f32 v29;
  s64 v31;
  s64 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  SBTLUNIT_LISTWORK *v36;
  SBTLUNIT_WORK *pUnit;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 hit_area_r;
  f32 LenXZ;
  f32 v44;
  f32 AtoB_LR;
  f32 ABS;
  f32 v47;
  f32 v48;
  f32 v49;
  bool v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  SBTLACTAI_WORK *actaiwk;
  f32 v56;
  s32 ListID;
  s32 devilid;
  f32 v59;
  u32 v60;
  s64 v61;
  s64 v62;
  s32 v63;
  s64 i;
  s64 v65;
  f32 *v66;
  s32 *v67;
  f32 v68;
  f32 v69;
  s64 v70;
  s32 v71;
  s64 v72;
  s32 j;
  s32 v74;
  s64 v75;
  s64 v76;
  f32 v77;
  s64 v78;
  s32 v79;
  f32 v80;
  s64 v81;
  f32 v82;
  _BOOL4 v83;
  SBTLUNIT_LISTWORK *v84;
  s64 v85;
  s32 v86;
  SBTLUNIT_LISTWORK *v88;
  s64 v90;
  u32 v91;
  f32 PosToDir;
  bool v95;
  u32 v96;
  s64 v97;

  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
  }
  v12 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v12->other_List2 = TargetList_MASK;
  v14 = wk->other_List2;
  count = v14->count;
  if (!count)
  {
    v14 = wk->other_List2;
    v86 = -1;
    goto LABEL_132;
  }
  v95 = UseDone;
  count = wk->other_List2->count;
  v17 = NewSpecific(f32, count);
  v18 = NewSpecific(f32, wk->other_List2->count);
  v19 = NewSpecific(s32, wk->other_List2->count);
  v21 = 0;
  v97 = v18;
  v22 = v18 + 32;
  while (1)
  {
    v24 = wk;
    if (v21 >= v24->other_List2->count)
      break;
    v23 = 4 * v21;
    *(u32 *)(v19 + 32 + v23) = v21++;
    *(u32 *)(v17 + 32 + v23) = 0;
    *(u32 *)(v22 + v23) = 1176255488;
  }
  v24 = wk;
  camera = v24->scene->camera;
  x = camera->camerapos.x;
  z = camera->camerapos.z;
  v28 = camera->targetpos.x;
  v29 = camera->targetpos.z;
  PosToDir = sBtlGetPosToDir(x, z, v28, v29);
  v31 = 0;
  v90 = v17;
  v91 = -1;
  v32 = v17 + 32;
  v33 = 9999.0;
  v34 = 999.0;
  v96 = -1;
  while (1)
  {
    v36 = wk->other_List2;
    if (v31 >= v36->count)
      break;
    pUnit = v36->pUnitL[v31]->pUnit;
    if (!pUnit)
      goto LABEL_26;
    v38 = wk->pos.x;
    v39 = wk->pos.z;
    v40 = pUnit->pos.x;
    v41 = pUnit->pos.z;
    hit_area_r = pUnit->actaiwk->hit_area_r;
    LenXZ = sBtlGetLenXZ(v38, v39, v40, v41);
    v44 = sBtlGetPosToDir(wk->pos.x, wk->pos.z, pUnit->pos.x, pUnit->pos.z);
    AtoB_LR = sBtlGetAtoB_LR(pdir, v44);
    ABS = sBtlGetABS(AtoB_LR);
    v47 = sBtlGetAtoB_LR(sdir, v44);
    sBtlGetABS(v47);
    v48 = sBtlGetPosToDir(camera->camerapos.x, camera->camerapos.z, pUnit->pos.x, pUnit->pos.z);
    v49 = sBtlGetAtoB_LR(PosToDir, v48);
    v35 = sBtlGetABS(v49);
    v50 = sBtlCheckLiveTarget_NotHitDmg(pUnit);
    if (v50)
    {
      if ((pUnit->vstatus & 0x10000) == 0)
        goto LABEL_41;
    }
    else
    {
      *(f32 *)(v32 + 4 * v31) = *(f32 *)(v32 + 4 * v31) + -100.0;
      if ((pUnit->vstatus & 0x10000) == 0)
      {
LABEL_41:
        if ((pUnit->status & 0x4000000) == 0)
          goto LABEL_42;
        goto LABEL_48;
      }
    }
    *(f32 *)(v32 + 4 * v31) = *(f32 *)(v32 + 4 * v31) + -100.0;
    if ((pUnit->status & 0x4000000) == 0)
    {
LABEL_42:
      if ((pUnit->hstatus & 0x10) == 0)
        goto LABEL_43;
      goto LABEL_49;
    }
LABEL_48:
    *(f32 *)(v32 + 4 * v31) = *(f32 *)(v32 + 4 * v31) + -100.0;
    if ((pUnit->hstatus & 0x10) == 0)
    {
LABEL_43:
      if (pUnit->actwk->status == 8)
        goto LABEL_44;
      goto LABEL_50;
    }
LABEL_49:
    *(f32 *)(v32 + 4 * v31) = *(f32 *)(v32 + 4 * v31) + 10.0;
    if (pUnit->actwk->status == 8)
    {
LABEL_44:
      *(f32 *)(v32 + 4 * v31) = *(f32 *)(v32 + 4 * v31) + 6.0;
      if (wk->actwk->status != 56)
        goto LABEL_53;
      goto LABEL_51;
    }
LABEL_50:
    if (wk->actwk->status != 56)
      goto LABEL_53;
LABEL_51:
    if (pUnit->ListID == wk->actaiwk->targetID_Mawari)
      *(f32 *)(v32 + 4 * v31) = *(f32 *)(v32 + 4 * v31) + 20.0;
LABEL_53:
    v51 = 10.0;
    if (LenXZ <= (f32)(hit_area_r + 400.0) || (v51 = 5.0, LenXZ <= (f32)(hit_area_r + 800.0)) || (v51 = 2.0, LenXZ <= (f32)(hit_area_r + 1500.0)))
    {
      *(f32 *)(v32 + 4 * v31) = *(f32 *)(v32 + 4 * v31) + v51;
    }
    if (ABS >= 60.0)
    {
      v54 = *(f32 *)(v32 + 4 * v31);
      if (ABS >= 90.0)
      {
        v52 = v54 + -3.0;
        if (v35 < 60.0)
        {
LABEL_59:
          v53 = 5.0;
          goto LABEL_67;
        }
      }
      else
      {
        v52 = v54 + 2.0;
        if (v35 < 60.0)
          goto LABEL_59;
      }
    }
    else
    {
      v52 = *(f32 *)(v32 + 4 * v31) + 6.0;
      if (v35 < 60.0)
        goto LABEL_59;
    }
    if (v35 >= 90.0)
      v53 = -3.0;
    else
      v53 = 2.0;
LABEL_67:
    actaiwk = wk->actaiwk;
    v56 = v52 + v53;
    ListID = pUnit->ListID;
    *(f32 *)(v32 + 4 * v31) = v56;
    if (ListID == actaiwk->targetID_Last)
    {
      v56 = v56 + 6.0;
      *(f32 *)(v32 + 4 * v31) = v56;
    }
    devilid = (u16)pUnit->para->devilid;
    if ((devilid == 297 || devilid == 290) && pUnit->Itimoku_CloseEye)
    {
      v56 = v56 + -40.0;
      *(f32 *)(v32 + 4 * v31) = v56;
    }
    if ((u32)((s16)devilid - 258) <= 2)
      *(f32 *)(v32 + 4 * v31) = v56 + -99999.0;
    if ((f32)(LenXZ - hit_area_r) >= 1.0)
      v59 = LenXZ - hit_area_r;
    else
      v59 = 1.0;
    *(f32 *)(v97 + 32 + 4 * v31) = v59;
    if (v95)
    {
      if (wk->other_List2->pUnitL[v31]->pUnit->DoneCameraTgtSelect1)
        goto LABEL_26;
    }
    if (v33 <= v59)
    {
      v60 = v96;
    }
    else
    {
      v33 = v59;
      v60 = v31;
    }
    v96 = v60;
    if (v34 <= v35)
    {
LABEL_26:
      v35 = v34;
      goto LABEL_27;
    }
    v91 = v31;
LABEL_27:
    v34 = v35;
    ++v31;
  }
  v61 = 0;
  v62 = v19 + 36;
  v63 = 1;
  for (i = v97 + 36; ; i += 4)
  {
    if (v61 >= wk->other_List2->count - 1)
      break;
    v65 = 0;
    v66 = (v97 + 4 * v61 + 32);
    v67 = (v19 + 4 * v61 + 32);
    while (1)
    {
      if (wk->other_List2->count <= v63 + (s32)v65)
        break;
      v68 = *v66;
      v69 = *(f32 *)(i + 4 * v65);
      if (*v66 > v69)
      {
        v70 = 4 * v65;
        v71 = *v67;
        *v66 = v69;
        *v67 = *(u32 *)(v62 + 4 * v65);
        *(u32 *)(v62 + v70) = v71;
        *(f32 *)(i + v70) = v68;
      }
      ++v65;
    }
    ++v61;
    ++v63;
    v62 += 4;
  }
  v72 = 0;
  for (j = -1; ; --j)
  {
    v75 = wk->other_List2->count;
    if (v72 >= v75)
      break;
    v76 = *(s32 *)(v19 + 32 + 4 * v72);
    v77 = *(f32 *)(v32 + 4 * v76);
    LODWORD(v75) = wk->other_List2->count;
    v74 = v75 + j;
    ++v72;
    *(f32 *)(v32 + 4 * v76) = v77 + (f32)v74;
  }
  if ((v96 & 0x80000000) == 0)
    *(f32 *)(v32 + 4 * v96) = *(f32 *)(v32 + 4 * v96) + 9.0;
  if ((v91 & 0x80000000) == 0)
    *(f32 *)(v32 + 4 * v91) = *(f32 *)(v32 + 4 * v91) + 6.0;
  v78 = 0;
  v79 = -1;
  v80 = -9999.0;
  v81 = v90 + 32;
  while (1)
  {
    v84 = wk->other_List2;
    if (v78 >= v84->count)
      break;
    if (!v95)
      goto LABEL_111;
    if (!wk->other_List2->pUnitL[v78]->pUnit->DoneCameraTgtSelect1)
    {
LABEL_111:
      v82 = *(f32 *)(v81 + 4 * v78);
      v83 = v80 >= v82;
      if (v82 < 0.0)
        v83 = 1;
      if (!v83)
      {
        v80 = *(f32 *)(v81 + 4 * v78);
        v79 = v78;
      }
    }
    ++v78;
  }
  if (v79 != -1)
  {
    v84 = wk->other_List2;
    v85 = (s64)v84->pUnitL + 8 * v79;
    goto LABEL_128;
  }
  if ((v96 & 0x80000000) != 0 || *(f32 *)(v90 + 4 * v96 + 32) < -9000.0)
  {
    v86 = -1;
  }
  else
  {
    v84 = wk->other_List2;
    v85 = (s64)v84->pUnitL + 8 * v96;
LABEL_128:
    v86 = *(u32 *)(*(u64 *)(*(u64 *)(v85 + 32) + 24) + 364);
  }
  v14 = wk->other_List2;
LABEL_132:
  sBtlDeleteUnitList(v14, 0);
  v88 = &wk->other_List2;
  v88 = 0;
  return v86;
}

// 0x1f958d0
s32 sBtlGetNearTarget_CameraLockOn2(SBTLUNIT_WORK *wk, s32 _Mode) {
  f32 CameraLockOnX;
  f32 v7;
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *v12;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  s64 v14;
  f32 v15;
  s64 v16;
  s64 v17;
  s32 v18;
  s32 v19;
  f32 PosToDir;
  f32 Dir180;
  f32 AtoB_LR;
  f32 ABS;
  SBATTLE_WORK *v25;
  SBTLUNIT_LISTWORK *v26;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 z;
  f32 v30;
  f32 v31;
  s64 v32;
  s64 v33;
  s64 v34;
  s64 v35;
  s64 v36;
  f32 *v37;
  s32 *v38;
  f32 v39;
  s64 v40;
  f32 *v41;
  f32 v42;
  f32 v43;
  s64 v44;
  s32 v45;
  s32 v46;
  s64 v47;
  s64 v48;
  s32 *v49;
  f32 *v50;
  f32 v51;
  f32 v52;
  s32 v53;
  f32 v54;
  f32 v55;
  s32 v56;
  s32 CameraLockOnTgtID;
  SBTLUNIT_LISTWORK *v59;
  SBTLUNIT_LISTWK **p_pUnitL;
  s64 v62;
  SBATTLE_WORK *v64;
  s32 v65;
  s32 v67;

  CameraLockOnX = sBtlGetCameraLockOnX();
  v7 = CameraLockOnX;
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
    goto LABEL_13;
  }
LABEL_13:
  v67 = Mode;
  v12 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v12->other_List2 = TargetList_MASK;
  v14 = NewSpecific(s32, wk->other_List2->count);
  v15 = 999.0;
  v16 = NewSpecific(f32, wk->other_List2->count);
  v17 = 0;
  v18 = 0;
  v19 = -1;
  while (1)
  {
    v25 = wk;
    v26 = v25->other_List2;
    if (v17 >= v26->count)
      break;
    pUnit = v26->pUnitL[v17]->pUnit;
    if (!pUnit)
      goto LABEL_19;
    if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
      goto LABEL_19;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0)
    {
      x = pUnit->pos.x;
      z = pUnit->pos.z;
      v30 = wk->pos.x;
      v31 = wk->pos.z;
      PosToDir = sBtlGetPosToDir(v30, v31, x, z);
      Dir180 = sBtlGetDir180(PosToDir);
      AtoB_LR = sBtlGetAtoB_LR(v7, Dir180);
      ABS = sBtlGetABS(AtoB_LR);
      ++v18;
      *(u32 *)(v14 + 32 + 4 * v17) = v17;
      if (v15 > ABS)
      {
        v15 = ABS;
        v19 = v17;
      }
      *(f32 *)(v16 + 32 + 4 * v17) = AtoB_LR;
    }
LABEL_19:
    ++v17;
  }
  if (!v18 || v19 == -1)
  {
    CameraLockOnTgtID = -1;
    goto LABEL_59;
  }
  if (!v67 || (v32 = (u32)(v18 - 1), v18 == 1))
  {
    v26 = wk->other_List2;
    p_pUnitL = &v26->pUnitL;
    goto LABEL_84;
  }
  if ((s32)v32 < 1)
    goto LABEL_78;
  v33 = 0;
  v34 = 1;
  while (2)
  {
    v35 = v33 + 1;
    if (v33 + 1 < v18)
    {
      v36 = v34;
      v37 = (v16 + 4 * v33 + 32);
      v38 = (v14 + 4 * v33 + 32);
      if (((~(u32)v33 + v18) & 1) != 0)
      {
        v39 = *v37;
        v40 = v16 + 4 * v34;
        v42 = *(f32 *)(v40 + 32);
        v41 = (v40 + 32);
        v43 = v42;
        if (v42 < *v37)
        {
          v44 = v14 + 4 * v34;
          v45 = *v38;
          *v37 = v43;
          *v41 = v39;
          v46 = *(u32 *)(v44 + 32);
          *(u32 *)(v44 + 32) = v45;
          *v38 = v46;
        }
        v36 = v34 + 1;
      }
      if ((u32)v18 - 2 != v33)
      {
        v47 = 4 * v36;
        v48 = (u32)v18 - v36;
        v49 = (v14 + 36 + 4 * v36);
        v50 = (v16 + 36 + v47);
        do
        {
          v51 = *(v50 - 1);
          v52 = *v37;
          if (v51 >= *v37)
          {
            v54 = *v50;
            v55 = *v37;
            if (*v50 < *v37)
            {
LABEL_55:
              v56 = *v38;
              *v37 = v54;
              *v50 = v55;
              *v38 = *v49;
              *v49 = v56;
            }
          }
          else
          {
            v53 = *v38;
            *v37 = v51;
            *(v50 - 1) = v52;
            *v38 = *(v49 - 1);
            *(v49 - 1) = v53;
            v54 = *v50;
            v55 = *v37;
            if (*v50 < *v37)
              goto LABEL_55;
          }
          v48 -= 2;
          v49 += 2;
          v50 += 2;
        }
        while (v48);
      }
    }
    ++v34;
    v33 = v35;
    if (v35 != v32)
      continue;
    break;
  }
  if (v18 < 1)
  {
LABEL_78:
    LODWORD(v62) = 0;
    goto LABEL_79;
  }
  v62 = 0;
  while (1)
  {
    if (wk->other_List2->pUnitL[*(s32 *)(v14 + 32 + 4 * v62)]->pUnit->ListID == wk->CameraLockOnTgtID)
      break;
    if (v18 == (u32)++v62)
      goto LABEL_78;
  }
LABEL_79:
  v64 = wk;
  CameraLockOnTgtID = v64->CameraLockOnTgtID;
  if (v67 != -1)
  {
    v65 = v62 + 1;
    if (v65 < v18)
    {
      goto LABEL_83;
    }
    goto LABEL_85;
  }
  if ((u32)v62)
  {
    v65 = v62 - 1;
    v64 = wk;
LABEL_83:
    v19 = *(u32 *)(v14 + 4 * (u32)v65 + 32);
    p_pUnitL = &v64->other_List2->pUnitL;
LABEL_84:
    CameraLockOnTgtID = (*p_pUnitL)[v19]->pUnit->ListID;
  }
LABEL_85:
  v26 = wk->other_List2;
LABEL_59:
  sBtlDeleteUnitList(v26, 0);
  v59 = &wk->other_List2;
  v59 = 0;
  return CameraLockOnTgtID;
}

// 0x1f96210
s32 sBtlGetNearTarget_CameraLockOn3(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  f32 v11;
  s64 v12;
  s32 ListID;
  SBTLUNIT_LISTWORK *v15;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 z;
  f32 v20;
  f32 v21;
  f32 v22;
  SBTLUNIT_LISTWORK *v24;

  if (!wk)
    return -1;
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
    goto LABEL_10;
  }
LABEL_10:
  v9 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v9->other_List2 = TargetList_MASK;
  v11 = 9999.0;
  v12 = 0;
  ListID = -1;
  while (1)
  {
    v15 = wk->other_List2;
    if (v12 >= v15->count)
      break;
    pUnit = v15->pUnitL[v12]->pUnit;
    if (!pUnit)
      goto LABEL_13;
    if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
      goto LABEL_13;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0)
    {
      x = wk->pos.x;
      z = wk->pos.z;
      v20 = pUnit->pos.x;
      v21 = pUnit->pos.z;
      v22 = sBtlGetLenXZ(x, z, v20, v21) - pUnit->actaiwk->hit_area_r;
      if (v22 < v11)
      {
        ListID = pUnit->ListID;
        v11 = v22;
      }
    }
LABEL_13:
    ++v12;
  }
  sBtlDeleteUnitList(v15, 0);
  v24 = &wk->other_List2;
  v24 = 0;
  return ListID;
}

// 0x1f966c0
s32 sBtlGetHpLowTarget(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  s64 v12;
  s32 hp;
  s32 ListID;
  SBTLUNIT_LISTWORK *v15;
  SBTLUNIT_WORK *pUnit;
  bool v18;
  SBTLUNIT_LISTWORK *v21;

  if (!wk)
    return -1;
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
    goto LABEL_10;
  }
LABEL_10:
  v9 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v9->other_List2 = TargetList_MASK;
  v12 = 0;
  hp = 999999;
  ListID = -1;
  while (1)
  {
    v15 = wk->other_List2;
    if (v12 >= v15->count)
      break;
    pUnit = v15->pUnitL[v12]->pUnit;
    if (!pUnit)
      goto LABEL_13;
    v18 = sBtlCheckLiveTarget_NotHitDmg(pUnit);
    if (!v18)
      goto LABEL_13;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0 && pUnit->para->now->hp < hp)
    {
      ListID = pUnit->ListID;
      hp = pUnit->para->now->hp;
    }
LABEL_13:
    ++v12;
  }
  sBtlDeleteUnitList(v15, 0);
  v21 = &wk->other_List2;
  v21 = 0;
  return ListID;
}

// 0x1fadf60
s32 sBtlGetHpLowTarget_BS_ITIMOK(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  s64 v12;
  s32 v13;
  s32 ListID;
  SBTLUNIT_LISTWORK *v15;
  SBTLUNIT_WORK *pUnit;
  bool v18;
  sdatUnitWork_t *para;
  s32 devilid;
  s32 hp;
  SBTLUNIT_LISTWORK *v24;

  if (!wk)
    return -1;
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
    goto LABEL_11;
  }
LABEL_11:
  v9 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v9->other_List2 = TargetList_MASK;
  v12 = 0;
  v13 = 999999;
  ListID = -1;
  while (1)
  {
    v15 = wk->other_List2;
    if (v12 >= v15->count)
      break;
    pUnit = v15->pUnitL[v12]->pUnit;
    if (!pUnit)
      goto LABEL_14;
    v18 = sBtlCheckLiveTarget_NotHitDmg(pUnit);
    if (!v18)
      goto LABEL_14;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0)
    {
      para = pUnit->para;
      devilid = (u16)para->devilid;
      if (devilid != 290 && devilid != 297)
      {
        hp = para->now->hp;
        if (hp < v13)
        {
          ListID = pUnit->ListID;
          v13 = hp;
        }
      }
    }
LABEL_14:
    ++v12;
  }
  sBtlDeleteUnitList(v15, 0);
  v24 = &wk->other_List2;
  v24 = 0;
  return ListID;
}

// 0x1f94f70
s32 sBtlGetFrontTarget(SBTLUNIT_WORK *wk, s32 _DevilID) {
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *v11;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  f32 v13;
  s64 v14;
  s32 ListID;
  SBTLUNIT_LISTWORK *v17;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 z;
  f32 v22;
  f32 v23;
  f32 PosToDir;
  f32 AtoB_LR_ABS;
  SBTLUNIT_LISTWORK *v27;

  if (!wk)
    return -1;
  other_List2 = wk->other_List2;
  if (other_List2)
  {
    sBtlDeleteUnitList(other_List2, 0);
    p_other_List2 = &wk->other_List2;
    p_other_List2 = 0;
    goto LABEL_11;
  }
LABEL_11:
  v11 = wk;
  TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
  v11->other_List2 = TargetList_MASK;
  v13 = 9999.0;
  v14 = 0;
  ListID = -1;
  while (1)
  {
    v17 = wk->other_List2;
    if (v14 >= v17->count)
      break;
    pUnit = v17->pUnitL[v14]->pUnit;
    if (!pUnit)
      goto LABEL_15;
    if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
      goto LABEL_15;
    if ((pUnit->vstatus & 0x10000) == 0 && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0 && pUnit->para->devilid == DevilID)
    {
      x = wk->pos.x;
      z = wk->pos.z;
      v22 = pUnit->pos.x;
      v23 = pUnit->pos.z;
      PosToDir = sBtlGetPosToDir(x, z, v22, v23);
      AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(0.0, PosToDir);
      if (AtoB_LR_ABS < v13)
      {
        ListID = pUnit->ListID;
        v13 = AtoB_LR_ABS;
      }
    }
LABEL_15:
    ++v14;
  }
  sBtlDeleteUnitList(v17, 0);
  v27 = &wk->other_List2;
  v27 = 0;
  return ListID;
}

// 0x1f97440
f32 sBtlGetTargetLen(SBTLUNIT_WORK *wk) {
  f32 v3;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  s32 devilid;
  f32 x;
  f32 z;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;

  v3 = -1.0;
  targetID = wk->actaiwk->targetID;
  if (targetID != -1)
  {
    UnitMng = wk->UnitMng;
    v7 = sBtlSearchUnit_ID(UnitMng, targetID);
    if (!v7)
      return v3;
LABEL_10:
    v8 = v7;
    devilid = (u16)v7->para->devilid;
    if (devilid == 314 || devilid == 258)
    {
      x = wk->pos.x;
      z = wk->pos.z;
      return sBtlGetLenXZ(x, z, x, 960.0) - wk->actaiwk->hit_area_r;
    }
    else
    {
      v12 = wk->pos.x;
      v13 = wk->pos.z;
      v14 = v7->pos.x;
      v15 = v7->pos.z;
      return (f32)(sBtlGetLenXZ(v12, v13, v14, v15) - wk->actaiwk->hit_area_r)
           - v8->actaiwk->hit_area_r;
    }
    v7 = sBtlSearchUnit_ID(UnitMng, targetID);
    if (!v7)
      return v3;
    goto LABEL_10;
  }
  return v3;
}

// 0x1fba890
bool sBtlChkSpace(SBTLUNIT_WORK *wk) {
  s32 next_motionno;
  f32 TargetLen;

  if (wk->major)
    return 0;
  next_motionno = wk->next_motionno;
  if (next_motionno > 95)
  {
    if ((next_motionno & 0xFFFFFFF8) == 0xA0 || (u32)(next_motionno - 97) < 5 || (u32)(next_motionno - 144) <= 0xD)
    {
      goto LABEL_12;
    }
    return 0;
  }
  if (next_motionno != 39 && next_motionno != 95)
    return 0;
LABEL_12:
  TargetLen = sBtlGetTargetLen(wk);
  return TargetLen > -1.0 && TargetLen < 130.0;
}

// 0x1f9a4f0
void sBtlSetPlayerDir_ToTarget(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v6;
  s32 devilid;
  f32 Dir180;
  sdfVector4_t *p_rot;
  f32 x;
  f32 z;
  f32 v13;
  f32 v14;
  f32 mv_rotbk;
  f32 v16;
  sdfVector4_t *v18;
  sdfVector4_t *p_rotbk;

  UnitMng = wk->UnitMng;
  targetID = wk->actaiwk->targetID;
  v6 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (v6)
  {
    devilid = (u16)v6->para->devilid;
    if (devilid == 314 || devilid == 258)
    {
      Dir180 = sBtlGetDir180(0.0);
      wk->mv_rotbk = Dir180;
      FromEuler(0.0, Dir180 * 0.017453292, 0.0);
      p_rot = &wk->rot;
      *p_rot = vct_A;
      p_rotbk = &wk->rotbk;
      mv_rotbk = wk->mv_rotbk;
LABEL_36:
      *p_rotbk = vct_A;
      wk->front_deg = mv_rotbk;
      return;
    }
    x = wk->pos.x;
    z = wk->pos.z;
    v13 = v6->pos.x;
    v14 = v6->pos.z;
    mv_rotbk = sBtlGetPosToDir(x, z, v13, v14);
    v16 = sBtlGetDir180(mv_rotbk);
    wk->mv_rotbk = v16;
    FromEuler(0.0, v16 * 0.017453292, 0.0);
    v18 = &wk->rot;
    *v18 = vct_A;
    p_rotbk = &wk->rotbk;
    goto LABEL_36;
  }
}
