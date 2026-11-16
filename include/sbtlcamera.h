#pragma once
#include "types.h"
#include "E_CAMERA_MODE.h"

typedef enum {
    E_CAMMOD_CUT_Non = 0,
    E_CAMMOD_CUT_DmgNum = 1,
    E_CAMMOD_CUT_Stp = 2,
    E_CAMMOD_CUT_NakamaIcon = 4,
    E_CAMMOD_CUT_ExcRenkeiTameEff = 8,
} E_CAMMOD_CUT;

typedef struct SBTLCAMERA_WORK SBTLCAMERA_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_CameraMoveDt S_CameraMoveDt;

extern void *battleCameraPar;
extern S_CameraMoveDt *g_aCamMovEnd;
extern sdfVector2_t gBk_followUpAngle;
extern sdfVector4_t gBk_targetpos;
extern sdfVector4_t gBk_camerapos;
extern f32 gBk_Fovy;
extern sdfVector4_t gBk_UpV;
extern sdfVector3_t gStartCam_TgtEnemySmnPos;
extern sdfVector3_t gStartCam_CamEnemySmnPos;
extern sdfVector3_t gStartCam_TgtGoalPos;
extern sdfVector3_t gStartCam_CamGoalPos;
extern f32 gStartCam_Nml;

S_CameraMoveDt *sBtlGetCamMovePtn(s32 idx);
void sBtlSetMove(S_CameraMoveDt *pCamMovDt, bool _SetClearDof2Bokah);
void sBtlSetDof2Bokah(f32 _Frame, f32 _focusDistance_St, f32 _focalLength_St, f32 _aperture_St, f32 _focusDistance_Ed, f32 _focalLength_Ed, f32 _aperture_Ed);
void sBtlClearDof2Bokah(void);
void sBtlCreateCamera(void);
bool Proc(void);
void sBtlSetBossMode(s32 mode);
void sBtlSetStaticInit(void);
void sBtlClearZoom(void);
void sBtlClearTgt(void);
bool sBtlGetIdling(SBTLCAMERA_WORK *wk, sdfVector4_t *vResPos, sdfVector4_t *vResTgt, bool reCal, SBTLUNIT_WORK *pBaseUnit, bool bGun);
void sBtlResetIdling_HD(void);
void sBtlGetIdling_HD_Sub(SBTLCAMERA_WORK *wk, SBTLUNIT_WORK *pBaseUnit, const sdfVector4_t *vResTgt, sdfVector4_t *targetPos, sdfVector4_t *cameraPos);
void sBtlGetIdling_HD(SBTLCAMERA_WORK *wk, SBTLUNIT_WORK *pBaseUnit, SBTLUNIT_WORK *pTgtUnit, sdfVector4_t *vResPos, sdfVector4_t *vResTgt);
void Slerp(SBTLCAMERA_WORK *wk, const sdfVector4_t *vPos, const sdfVector4_t *vTgt, f32 f);
bool sBtlIsMoveEnd(void);
void sBtlSetMoveEnd(void);
void sBtlEventFovOff(void);
void sBtlEventUpVOff(void);
void sBtlMenuOpen(void);
void sBtlMenuClose(void);
bool sBtlChkMenu2Open(void);
s32 sBtlBossStartSub(SBTLCAMERA_WORK *wk);
void sBtlSetFollowUpCameraPar(void);
void sBtlGetAnalogSensitivity(f32 *InSen, f32 *SpdSen);
void sBtlInputFollowUp(SBTLCAMERA_WORK *_wk, sdfVector2_t *_followUpAngle);
void sBtlInputFollowUp_Menu2(SBTLCAMERA_WORK *_wk, sdfVector2_t *_followUpAngle);
void sBtlNakamaSetUp(s32 nakama_index);
void sBtlNoHokan(void);
void sBtlNoHokan_Ring(void);
bool sBtlSetMode(E_CAMERA_MODE no);
E_CAMERA_MODE sBtlGetMode(void);
E_CAMMOD_CUT sBtlGetCutFlg(void);
void sBtlSetPos(const sdfVector4_t *pvPos);
void sBtlSetPosSlp(const sdfVector4_t *pvPos);
void sBtlBgnPosSlp(void);
s32 sBtlGetPosSlp(void);
void sBtlSetTgt(const sdfVector4_t *pvTgt);
void sBtlSetTgtSlp(const sdfVector4_t *pvTgt);
void sBtlBgnTgtSlp(void);
s32 sBtlGetTgtSlp(void);
void sBtlSetCameraLockOnTgtPos(f32 x, f32 y, f32 z);
void sBtlSetCameraLockOnTgtNone(void);
f32 sBtlGetCameraLockOnX(void);
void sBtlSetCameraHighTargetUse(bool _Use, s32 _TargetID);
f32 sBtlGetCameraDir(void);
void sBtlPushCamera(void);
void sBtlPopCamera(void);
bool sBtlChkSideBySide(void);
void sBtlResetFollowUpAngleX(f32 _followUpAngle_x);
void sBtlResetTargetFollowUpAngleX(SBTLUNIT_WORK *wk);
void sBtlResetGazeOnOff(void);
void sBtlResettgtCng(void);
void sBtlSetBossTalkTarget(SBTLUNIT_WORK *_wk);
