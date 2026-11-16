#include "types.h"
#include "E_CAMERA_MODE.h"
#include "SBTLUNIT_SIDE.h"
#include "aw.h"
#include "bsflow.h"
#include "cfg.h"
#include "configunity.h"
#include "dat.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3kernelcore.h"
#include "dds3objectbase.h"
#include "dds3padmanager.h"
#include "dds3scenebasic.h"
#include "dds3vrf.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "g_aposmove.h"
#include "kernel.h"
#include "rspecialskill.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtlcamerar1.h"
#include "sbtlcmbskl.h"
#include "sbtlevent.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlplayer.h"
#include "sbtlplayer_sddash.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayerex.h"
#include "sbtlscene.h"
#include "sbtlsub.h"
#include "sbtltalk.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf3d.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "tips.h"

#define SBTLC_TMENU_NONE 0
#define SBTLC_TMENU_USER 1
#define SBTLC_TMENU_NAKAMA1 2
#define SBTLC_CMENU_NONE 0
#define SBTLC_CMENU_USER 1
#define SBTLC_CMV_KOTEI 0
#define SBTLC_CMV_CDIS_IN 1
#define SBTLC_CMV_CDIS_OUT 2
#define SBTLC_CMV_CROT 3

typedef enum {
    ENUM_AUTO_CAMERA_STATUS_NORMAL = 0,
    ENUM_AUTO_CAMERA_STATUS_E_REVERSE = 1,
    ENUM_AUTO_CAMERA_STATUS_E_REVERSE_H = 2,
    ENUM_AUTO_CAMERA_STATUS_E_SCREENSIDE = 3,
    ENUM_AUTO_CAMERA_STATUS_E_SCREENOUT = 4,
    ENUM_AUTO_CAMERA_STATUS_E_SCREENOUT_H = 5,
    ENUM_AUTO_CAMERA_STATUS_E_LONG = 6,
    ENUM_AUTO_CAMERA_STATUS_E_SIDEBYSIDE = 7,
    ENUM_AUTO_CAMERA_STATUS_E_ZERO = 8,
    ENUM_AUTO_CAMERA_STATUS_EVENT = 9,
    ENUM_AUTO_CAMERA_STATUS_MENU = 10,
    ENUM_AUTO_CAMERA_STATUS_RSTICK = 11,
    ENUM_AUTO_CAMERA_STATUS_RSTICK_END = 12,
    ENUM_AUTO_CAMERA_STATUS_RSDDASH = 13,
    ENUM_AUTO_CAMERA_STATUS_MAWARI = 14,
    ENUM_AUTO_CAMERA_STATUS_JUMP = 15,
    ENUM_AUTO_CAMERA_STATUS_JUMPAFTER = 16,
    ENUM_AUTO_CAMERA_STATUS_BOSSTALK = 17,
    ENUM_AUTO_CAMERA_STATUS_BOSSDEAD = 18,
    ENUM_AUTO_CAMERA_STATUS_BS14_KAITEN = 19,
    ENUM_AUTO_CAMERA_STATUS_AMATOBITALK1 = 20,
    ENUM_AUTO_CAMERA_STATUS_AMATOBITALK2 = 21,
    ENUM_AUTO_CAMERA_STATUS_AMATOBI = 22,
    ENUM_AUTO_CAMERA_STATUS_AMATOBI_GAZEOFF1 = 23,
} ENUM_AUTO_CAMERA_STATUS;

typedef struct DepthOfFieldSetting DepthOfFieldSetting;
typedef struct SBTLCAMERA_DATA SBTLCAMERA_DATA;
typedef struct SBTLCAMERA_WORK SBTLCAMERA_WORK;
typedef struct SBTLC_DATA SBTLC_DATA;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_CameraMoveDt S_CameraMoveDt;
typedef struct S_DofCtrl S_DofCtrl;
typedef struct S_FovCtrl S_FovCtrl;
typedef struct S_PosCtrl S_PosCtrl;
typedef struct S_PosMove S_PosMove;
typedef struct S_UpVCtrl S_UpVCtrl;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

struct SBTLC_DATA {
    s32 menu;
    f32 distance;
    f32 deg;
    f32 offsx;
    f32 offsy;
    f32 offsz;
    f32 dummy;
};

struct SBTLCAMERA_DATA {
    s32 type;
    f32 time;
    f32 divpara;
    f32 fovy;
    f32 distance;
    SBTLC_DATA *tmenu;
    SBTLC_DATA *cmenu;
    SBTLC_DATA *e_tmenu;
    SBTLC_DATA *e_cmenu;
};

void *battleCameraPar;
static s32 camera_bossmode;
static s32 camera_bossmode_cnt;
static s32 gsBtlCamera_Hokan_Not;
static s32 gsBtlCamera_RingHokan_Not;
static SBTLCAMERA_WORK *sbtl_stcam;
static SBTLCAMERA_WORK *sbtl_endcam;
static sdfVector4_t sbtlcamera_target_def;
static S_PosMove *g_aPmCamMovEnd0;
static S_PosMove *g_aPmCamMovEnd1;
static S_PosMove *g_aPmCamMovEnd2;
static S_PosMove *g_aPmCamTgtEnd;
static S_PosMove *g_aPmCamTgtEnd0;
S_CameraMoveDt *g_aCamMovEnd;
static f32 gFreeCam_Length;
static f32 gFreeCam_Y;
static f32 gFreeTgt_Y_ETgtOff;
static f32 gFreeCam_Fov;
static s32 gLayerMask_sBtlCamHit;
static s32 gLayerMask_aBtlCamHide;
static s32 gAuto_ManualKaiten_Cnt;
static bool gAuto_ManualKaiten_Input;
static f32 gRingTgt_Dir;
static f32 gRingTgt_R;
static f32 gTgtExSkill_Y;
static s32 gZoomStatus;
static s32 gZoomCnt;
static f32 gZoomLenNml;
static s32 gReverseCnt;
static bool gKaitenHiSpd;
static bool gFOVY_OW_Use;
static f32 gFOVY_OW_Param;
static bool gFOVY2_OW_Use;
static f32 gFOVY2_OW_Param;
static bool gUpV2_OW_Use;
static f32 gUpV2_OW_Param;
static bool gHokan_OW_Use;
static f32 gHokan_OW_Param;
sdfVector2_t gBk_followUpAngle;
sdfVector4_t gBk_targetpos;
sdfVector4_t gBk_camerapos;
f32 gBk_Fovy;
sdfVector4_t gBk_UpV;
sdfVector3_t gStartCam_TgtEnemySmnPos;
sdfVector3_t gStartCam_CamEnemySmnPos;
sdfVector3_t gStartCam_TgtGoalPos;
sdfVector3_t gStartCam_CamGoalPos;
f32 gStartCam_Nml;
static s32 gAuto_Status;
static s32 gAuto_DoneCnt;
static f32 gAuto_DirSpd;
static f32 gAuto_SideNormal;
static f32 *gSbtlCam_offset_pos;
static f32 gSbtlCam_len;
static f32 gBoss_BS_LASTB2_ST_Nml;
static f32 gBoss_BS_LASTB2_Nml;
static s32 gBoss_BS_LASTB2_Wait;
static f32 gBoss_SkillLong_Nml;
static f32 gBoss_AMATOBI_Z;
static f32 gBoss_AMATOBI_END_Nml;
static s32 gBossTalk_targetID;
static bool gDof2_Use;
static f32 gDof2_Frame_Now;
static f32 gDof2_Frame_End;
static f32 gDof2_focusDistance_St;
static f32 gDof2_focalLength_St;
static f32 gDof2_aperture_St;
static f32 gDof2_focusDistance_Ed;
static f32 gDof2_focalLength_Ed;
static f32 gDof2_aperture_Ed;
static s32 gFastLoa_SCENE_LOADEND;
static s32 gFastLoa_PANEL_LOAD;
static s32 gFastLoa_EFFONMEM_LOADEND;
static s32 gFastLoa_MODELLOAD;
static s32 gFastLoa_DEVILSELOAD;
static s32 gFastLoa_SABLOAD;
static s32 gFastLoa_VIEWTIME;

static f32 GetHighest(SBTLUNIT_SIDE flg);
static f32 GetDisNoCamDep(const sdfVector4_t *pos0, const sdfVector4_t *pos1);
static bool RaycastCamHit(SBTLUNIT_WORK *pBaseUnit, const sdfVector4_t *targetPos, sdfVector4_t *cameraPos, f32 _MiorosiY);
static void RaycastCamHide(const sdfVector4_t *targetPos, const sdfVector4_t *cameraPos);
static void GetNowPosAS(sdfVector4_t *vPosRes, const sdfVector4_t *vPosBgn, const sdfVector4_t *vPosEnd, f32 fTime, f32 x);
static void GetNowPosS(sdfVector4_t *vPosRes, const sdfVector4_t *vPosBgn, const sdfVector4_t *vPosEnd, f32 fTime, f32 x);
static void GetNowPos(sdfVector4_t *vPosRes, const sdfVector4_t *vPosBgn, const sdfVector4_t *vPosEnd, f32 fTime, f32 x);
static void GetNowFovyAS(f32 *fovy, f32 fovyBgn, f32 fovyEnd, f32 fTime, f32 x);
static void GetNowFovyS(f32 *fovy, f32 fovyBgn, f32 fovyEnd, f32 fTime, f32 x);
static void GetNowFovy(f32 *fovy, f32 fovyBgn, f32 fovyEnd, f32 fTime, f32 x);
static f32 PosCtrlSystem(S_PosCtrl *pPosCtrl, sdfVector4_t *pvRet);
static bool FovCtrlSystem(S_FovCtrl *pFovCtrl, f32 *fov);
static bool DofCtrlSystem(S_DofCtrl *pDofCtrl, DepthOfFieldSetting *dof);
static bool UpVCtrlSystem(S_UpVCtrl *pUpVCtrl, f32 *_UpV);
static f32 CameraMoveSystem(SBTLCAMERA_WORK *wk);
static void SetEnemyCPos(void);
static void MenuStealth(s32 mode);
static bool SetPara(SBTLCAMERA_WORK *wk);
static sdfVector3_t GetDisAngle(f32 sou_x, f32 sou_z, f32 dst_x, f32 dst_z, f32 distance);
static bool Backup(SBTLCAMERA_WORK *wk, dds3Basic_t *cm);
static bool Set(SBTLCAMERA_WORK *wk);
static dds3ProcessFunc_t ProcCamera(dds3ProcessID_t *id);
static void ShutdownCamera(dds3ProcessID_t *id);
static bool PrintfZa(void);
static bool CalcCameraPara(void);
static bool SetWork(SBTLCAMERA_WORK *cm, SBTLCAMERA_DATA *cdata, const sdfVector4_t *target, const sdfVector4_t *camera);
static bool GetTargetData(SBTLC_DATA *cd, const sdfVector4_t *tpos);
static bool GetCameraData(SBTLC_DATA *cd, const sdfVector4_t *cpos);
static void UpdateAwCamera(void);

// 0x1eed350
S_CameraMoveDt *sBtlGetCamMovePtn(s32 idx) {
  if (idx > 299)
  {
    return GetData(g_aCamMoveDtHd, idx - 300, 0);
  }
  return g_aCamMoveDt[idx];
}

// 0x1eed410
void sBtlSetMove(S_CameraMoveDt *pCamMovDt, bool _SetClearDof2Bokah) {
  S_PosMove *m_pPosMoveCam;
  SBTLCAMERA_WORK *camera;
  S_PosCtrl *m_PosCtrlCam;
  S_CameraMove *m_CamMov;
  S_PosMove *m_pPosMoveTgt;
  S_PosCtrl *m_PosCtrlTgt;
  S_PosCtrl *v12;
  S_CameraMove *v13;
  S_FovMove *m_pFovMove;
  S_FovCtrl *m_FovCtrl;
  S_PosCtrl *v16;
  S_CameraMove *v17;
  S_UpVMove *m_pUpVMove;
  S_UpVCtrl *m_UpVCtrl;
  S_FovCtrl *v20;
  S_UpVCtrl *v21;

  m_pPosMoveCam = pCamMovDt->m_pPosMoveCam;
  camera = wk->scene->camera;
  m_PosCtrlCam = camera->m_CamMov->m_PosCtrlCam;
  m_PosCtrlCam->m_pPosMove = m_pPosMoveCam;
  m_CamMov = camera->m_CamMov;
  m_pPosMoveTgt = pCamMovDt->m_pPosMoveTgt;
  v12 = m_CamMov->m_PosCtrlCam;
  m_PosCtrlTgt = m_CamMov->m_PosCtrlTgt;
  m_PosCtrlTgt->m_pPosMove = m_pPosMoveTgt;
  *(u64 *)&v12->m_cnt = 0;
  v12->m_run = 1;
  v13 = camera->m_CamMov;
  m_pFovMove = pCamMovDt->m_pFovMove;
  v16 = v13->m_PosCtrlTgt;
  m_FovCtrl = v13->m_FovCtrl;
  *(u64 *)&v16->m_cnt = 0;
  m_FovCtrl->m_pFovMove = m_pFovMove;
  v16->m_run = 1;
  v17 = camera->m_CamMov;
  m_pUpVMove = pCamMovDt->m_pUpVMove;
  v20 = v17->m_FovCtrl;
  m_UpVCtrl = v17->m_UpVCtrl;
  *(u64 *)&v20->m_cnt = 0;
  m_UpVCtrl->m_pUpVMove = m_pUpVMove;
  v20->m_run = 1;
  v21 = camera->m_CamMov->m_UpVCtrl;
  *(u64 *)&v21->m_cnt = 0;
  v21->m_run = 1;
  if (SetClearDof2Bokah)
  {
    sBtlClearDof2Bokah();
  }
}

// 0x1eed710
void sBtlSetDof2Bokah(f32 _Frame, f32 _focusDistance_St, f32 _focalLength_St, f32 _aperture_St, f32 _focusDistance_Ed, f32 _focalLength_Ed, f32 _aperture_Ed) {
  gDof2_focusDistance_St = focusDistance_St;
  gDof2_focalLength_St = focalLength_St;
  gDof2_aperture_St = aperture_St;
  gDof2_focusDistance_Ed = focusDistance_Ed;
  gDof2_focalLength_Ed = focalLength_Ed;
  gDof2_aperture_Ed = aperture_Ed;
  gDof2_Use = 1;
  gDof2_Frame_Now = 0.0;
  gDof2_Frame_End = Frame;
}

// 0x1eed560
void sBtlClearDof2Bokah(void) {
  void *Instance;
  struct sBtlCamera *static_fields;
  void *mDof;

  goto LABEL_3;
LABEL_7:
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    goto LABEL_10;
  mDof = Instance->mDof;
  if (!op_Inequality(Instance->mDof, 0, 0))
    goto LABEL_18;
  goto LABEL_9001;
  if (!op_Inequality(mDof, 0, 0))
  {
LABEL_18:
    SetForceActiveDofSetting(Instance, 0, 0);
    goto LABEL_12;
  }
LABEL_9001:
  RestoreDofSetting(Instance, 0);
  goto LABEL_18;
LABEL_3:
  if (gDof2_Use)
    goto LABEL_7;
LABEL_10:
LABEL_12:
  gDof2_Use = 0;
  static_fields = ((char *)static_fields + 372);
  *(_OWORD *)&battleCameraPar = 0u;
  *(_OWORD *)&gsBtlCamera_Hokan_Not = 0u;
}

// 0x1eed7d0
static f32 GetHighest(SBTLUNIT_SIDE flg) {
  f32 height;
  s64 v4;
  const char *namespaze;
  u16 v7;
  s32 v8;
  V_POSITION_WORK *nml;

  height = 0.0;
  v4 = 32;
  do
  {
    namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + v4))->_1.namespaze;
    if (namespaze && (*((u32 *)namespaze + 208) & flg) != 0)
    {
      v7 = *((u16 *)namespaze + 306);
      v8 = *((u32 *)namespaze + 154);
      nml = sBtlGetVisualData(v7, v8)->nml;
      if (height < nml->height)
        height = nml->height;
    }
    v4 += 8;
  }
  while (v4 != 416);
  return height;
}

// 0x1eed8f0
static f32 GetDisNoCamDep(const sdfVector4_t *pos0, const sdfVector4_t *pos1) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 *p_x;
  f32 *v15;
  f32 *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  u64 v23;
  struct sdfVector4_t direction;

  w = pos1->w;
  z = pos1->z;
  y = pos1->y;
  x = pos1->x;
  v7 = pos0->w;
  v8 = pos0->z;
  v9 = pos0->y;
  v10 = pos0->x;
  direction = wk->scene->camera->direction;
  vct_A = direction;
  vct_A.y = 0.0;
  sub_1949110(0);
  p_x = &vf00.x;
  p_x[4] = v10;
  p_x[5] = v9;
  p_x[6] = v8;
  p_x[7] = v7;
  v15 = &vf00.x;
  v15[8] = x;
  v15[9] = y;
  v15[10] = z;
  v15[11] = w;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v16 = &vf00.x;
  v17 = v16[6];
  v18 = v16[4];
  v19 = v16[5];
  vct_B = vct_A;
  v23 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return sqrtf((f32)((f32)(v18 * v18) + (f32)(v19 * v19)) + (f32)(v17 * v17))
       - fmaxf(*((f32 *)&v23 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v23), 0.0);
}

// 0x1eedd90
void sBtlCreateCamera(void) {
  SBTLCAMERA_WORK *camera;
  SBTLCAMERA_WORK *camerabk;
  dds3ProcessFunc_t v5;
  shutdownfuncDelegate v6;
  f32 offset_x;
  f32 offset_z;
  u32 v11;
  dds3Basic_t *v12;
  SBTLCAMERA_WORK *v13;
  SBTLCAMERA_WORK *v14;
  dds3Basic_t *v16;
  SBTLCAMERA_WORK *v17;
  SBTLCAMERA_WORK *v18;
  f32 v20;
  f32 v21;
  sdfVector4_t *p_targetpos;
  s32 v24;
  struct sdfVector4_t v25;
  struct sdfVector4_t camerapos;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  sdfVector4_t *p_direction;
  s32 v36;
  struct sdfVector4_t v38;
  dds3Basic_t *pBasic;
  dds3ProcessID_t *target;
  sdfVector4_t v44;
  sdfVector4_t v45;
  sdfVector4_t v46;
  sdfVector4_t v47;

  pBasic = 0;
  if (wk->camera_mode == 1)
  {
    sBtlCameraCreateCamera();
    return;
  }
  target = 0;
  camera = wk->scene->camera;
  camera->cm = 0;
  camerabk = wk->scene->camerabk;
  camerabk->cm = 0;
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_sBtlCamera_ProcCamera__, 0);
  v6 = Allocate(shutdownfuncDelegate);
  _ctor(v6, 0, Method_Project_sBtlCamera_ShutdownCamera__, 0);
  target = dds3StartProcess("sbtl_cameraproc", 1035, 1, 1, v5, v6, 0);
  offset_x = main_data->offset_x;
  offset_z = main_data->offset_z;
  v11 = dds3SerializeID();
  v45.x = 0.0;
  v45.y = 0.0;
  v45.z = 0.0;
  v47.x = 0.0;
  v47.y = 0.0;
  v45.w = 1.0;
  v47.z = 10.0;
  v47.w = 1.0;
  *(u64 *)&v44.x = 0;
  pBasic = dds3CameraObjectBasicAddTypeLookAt(v11, v45, v47, v44);
  dds3SetBasicName(pBasic, "sbtl_scam");
  v46.x = 0.0;
  v46.y = 0.0;
  v46.z = 10.0;
  v46.w = 1.0;
  dds3CameraObjectBasicSetTargetPos(pBasic, v46);
  dds3SetRadiusPoseSet(pBasic, 10.0);
  dds3ObjectBaseCreateMover(pBasic);
  v12 = pBasic;
  v13 = wk->scene->camera;
  v13->cm = pBasic;
  v14 = wk->scene->camera;
  v14->fovy = 0.6981317;
  dds3CameraObjectBasicSetFovy(&v14->cm, 0.6981317);
  v16 = pBasic;
  v17 = wk->scene->camera;
  Backup(v17, v16);
  v18 = wk->scene->camera;
  v20 = offset_x + 0.0;
  v21 = offset_z + 0.0;
  vct_A.x = v20;
  vct_A.y = 0.0;
  vct_A.z = v21;
  vct_A.w = 0.0;
  p_targetpos = &v18->targetpos;
  v24 = (u8)byte_5755EF5;
  *p_targetpos = vct_A;
  v25 = *p_targetpos;
  if (v24)
    goto LABEL_23;
  goto LABEL_44;
  if (v36)
  {
LABEL_23:
    goto LABEL_24;
  }
LABEL_44:
  v38 = v25;
  v25 = v38;
LABEL_24:
  vct_A = v25;
  camerapos = v18->camerapos;
  vct_B = camerapos;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v18->distance = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
  sub_1949110(0);
  p_direction = &v18->direction;
  *p_direction = vct_A;
  dds3LinkProcess(&wk->MProc_ID, target);
  *(u64 *)&camera_bossmode = 0;
}

// 0x1eeeae0
bool Proc(void) {
  SBTLCAMERA_WORK *camera;

  if (wk->camera_mode == 1)
    return sBtlCameraProc();
  camera = wk->scene->camera;
  SetPara(camera);
  return 1;
}

// 0x1eeea50
void sBtlSetBossMode(s32 mode) {
  camera_bossmode = mode;
  camera_bossmode_cnt = 0;
  return;
}

// 0x1eeecf0
void sBtlSetStaticInit(void) {
  SBTLSCENE_WORK *scene;

  *(u64 *)&camera_bossmode = 0;
  gsBtlCamera_Hokan_Not = 0;
  *(u64 *)gSbtlCam_offset_pos = 0;
  gSbtlCam_offset_pos[2] = 0.0;
  gFOVY2_OW_Use = 0;
  gBoss_SkillLong_Nml = 0.0;
  *(u64 *)&gBoss_BS_LASTB2_Nml = 0;
  gAuto_Status = 0;
  gFOVY2_OW_Param = 40.0;
  *(u64 *)&gRingTgt_R = 1125515264;
  gBossTalk_targetID = -1;
  *(u64 *)&gSbtlCam_len = 0x3F80000042C80000LL;
  scene = wk->scene;
  scene->camCnt = 0;
  scene->camCnt2 = 0;
}

// 0x1eeedd0
void sBtlClearZoom(void) {
  *(u64 *)&gZoomCnt = 0;
  gZoomStatus = 0;
  return;
}

// 0x1eeee60
void sBtlClearTgt(void) {
  *(u64 *)&gRingTgt_Dir = 0;
  return;
}

// 0x1eeeee0
bool sBtlGetIdling(SBTLCAMERA_WORK *wk, sdfVector4_t *vResPos, sdfVector4_t *vResTgt, bool reCal, SBTLUNIT_WORK *pBaseUnit, bool bGun) {
  bool v13;
  char v14;
  sdfVector4_t *p_pos;
  f32 x;
  f32 *p_z;
  f32 z;
  s64 v21;
  f32 v23;
  f32 v24;
  u32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  SBTLUNIT_WORK *namespaze;
  s32 side;
  f32 v34;
  sdfVector4_t *v35;
  f32 v36;
  s32 minor;
  f32 v38;
  u16 major;
  f32 v40;
  V_POSITION_WORK *nml;
  f32 height;
  f32 v45;
  f32 v46;
  f32 *p_x;
  f32 v48;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v55;
  f32 v56;
  s64 v57;
  f32 *v58;
  f32 *v59;
  f32 *v61;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 DisNoCamDep;
  f32 v72;
  f32 v74;
  f32 v75;
  sdfVector4_t v78;
  f32 *v79;
  struct sdfVector4_t v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  f32 v89;
  f32 v90;
  f32 v91;
  float32x2_t v94;
  f32 v95;
  float32x2_t v96;
  f32 *v97;
  u64 v98;
  f32 v99;
  f32 v100;
  struct sdfVector4_t v102;
  f32 v104;
  f32 v105;
  f32 v106;
  f32 v109;
  f32 v110;
  s64 v111;
  f32 v112;
  f32 v114;
  f32 v115;
  f32 v116;
  f32 v117;
  f32 v118;
  f32 v120;
  struct sdfVector4_t v122;
  sdfVector4_t *v123;
  f32 v126;
  f32 v129;
  f32 v131;
  f32 v132;
  f32 v133;
  f32 v134;
  f32 v135;
  f32 v136;
  f32 v138;
  f32 v139;
  f32 v140;
  f32 *v141;
  f32 v142;
  f32 v143;
  f32 v144;
  f32 v145;
  f32 v146;
  f32 *p_y;
  bool v148;
  f32 w;
  f32 v150;
  SBTLCAMERA_WORK *v151;
  sdfVector4_t *v152;
  f32 *v153;
  f32 v154;
  f32 y;
  f32 v156;
  struct sdfVector4_t v157;
  s32 v159;
  f32 v160;
  struct sdfVector4_t direction;
  struct sdfVector4_t v162;
  struct sdfVector4_t v163;
  sdfVector4_t ppos;
  sdfVector4_t v173;
  sdfVector4_t v174;

  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  vResTgt->w = 1.0;
  vResPos->w = 1.0;
  v151 = wk;
  v152 = vResPos;
  if (bGun)
  {
    if (pBaseUnit)
      v13 = wk->gunTgtId == 0;
    else
      v13 = 1;
    v14 = !v13;
    v148 = v14;
  }
  else
  {
    v148 = 0;
  }
  p_pos = &pBaseUnit->pos;
  x = pBaseUnit->pos.x;
  p_z = &pBaseUnit->pos.z;
  z = pBaseUnit->pos.z;
  y = pBaseUnit->pos.y;
  p_y = &pBaseUnit->pos.y;
  w = pBaseUnit->pos.w;
  v21 = 32;
  v159 = 1;
  v23 = 2000.0;
  v24 = 0.05;
  v154 = 70.0;
  v153 = &pBaseUnit->pos.z;
  v25 = camera_bossmode - 1;
  do
  {
    namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + v21))->_1.namespaze;
    if (namespaze != pBaseUnit && namespaze != 0)
    {
      side = namespaze->side;
      if ((side & 1) != 0 || v25 >= 2 && (side & 2) != 0)
      {
        v26 = p_pos->x;
        v27 = namespaze->pos.x - p_pos->x;
        v28 = *p_z;
        v29 = namespaze->pos.z - *p_z;
        v30 = sqrtf((f32)(v27 * v27) + (f32)(v29 * v29));
        if (v30 != 0.0)
        {
          v34 = (f32)(v23 - v30) * v24;
          if (v34 > 0.0)
          {
            v35 = p_pos;
            v36 = v24;
            minor = namespaze->minor;
            v38 = v23;
            major = namespaze->major;
            v40 = (f32)(v30 / 100.0) * v34;
            x = x + (f32)((f32)((f32)(v27 / v30) * v40) + v26);
            z = z + (f32)((f32)((f32)(v29 / v30) * v40) + v28);
            nml = sBtlGetVisualData(major, minor)->nml;
            v23 = v38;
            v24 = v36;
            height = v154;
            p_pos = v35;
            p_z = &pBaseUnit->pos.z;
            ++v159;
            if (v154 < nml->height)
              height = nml->height;
            v154 = height;
          }
        }
      }
    }
    v21 += 8;
  }
  while (v21 != 416);
  if (v159 >= 1)
  {
    vct_A.x = x;
    vct_A.y = y;
    vct_A.z = z;
    vct_A.w = w;
    v45 = v159;
    v46 = 1.0 / v45;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v46);
    p_x = &vf00.x;
    v48 = p_x[6];
    v50 = v48;
    v51 = p_x[5];
    v52 = p_x[4];
    goto LABEL_44;
  }
  v48 = *p_z + 100.0;
  v50 = v48;
  v51 = *p_y;
  v52 = p_pos->x;
LABEL_44:
  if (gsBtlCamera_Hokan_Not)
    goto LABEL_45;
  v163 = *p_pos;
  vct_A = v163;
  v110 = vct_A.x;
  v109 = vct_A.y;
  v111 = *(u64 *)&vct_A.z;
  v112 = v109 + -100.0;
  vct_A.x = v110;
  vct_A.y = v112;
  *(u64 *)&vct_A.z = v111;
  if (sBtlChangeWorldtoScreen(&ppos))
  {
    if (ppos.x >= 432.0)
    {
      v138 = (f32)(ppos.x + -512.0) + 80.0;
    }
    else
    {
      if (ppos.x > 80.0)
      {
        v114 = -1.0;
        if (-1.0 > 100.0)
          v114 = 100.0;
        if (v114 <= 1.0)
          goto LABEL_241;
LABEL_236:
        v142 = p_pos->x - v52;
        v143 = *p_z - v50;
        v144 = sqrtf((f32)(v142 * v142) + (f32)(v143 * v143));
        if (v144 > 1.0)
        {
          v145 = v142 / v144;
          v146 = v114 * 8.0;
          if (v146 > v144)
            v146 = v144;
          v52 = v52 + (f32)(v145 * v146);
          v48 = v50 + (f32)((f32)(v143 / v144) * v146);
LABEL_46:
          if (gsBtlCamera_Hokan_Not)
            goto LABEL_47;
          goto LABEL_218;
        }
LABEL_241:
        v48 = v50;
        goto LABEL_46;
      }
      v138 = 80.0 - ppos.x;
    }
    v114 = v138 * 1.25;
    if (v114 > 100.0)
      v114 = 100.0;
    if (v114 <= 1.0)
      goto LABEL_241;
    goto LABEL_236;
  }
  v52 = p_pos->x;
  v51 = *p_y + -100.0;
  v48 = *p_z + 100.0;
  goto LABEL_46;
LABEL_45:
  goto LABEL_46;
  if (gsBtlCamera_Hokan_Not)
  {
LABEL_47:
    goto LABEL_49;
  }
LABEL_218:
  v129 = v48;
  v131 = gSbtlCam_offset_pos[0];
  v52 = v52 + (f32)((f32)(v131 - v52) * 0.3);
  v132 = gSbtlCam_offset_pos[2];
  v133 = v52 - v131;
  v134 = v129 + (f32)((f32)(v132 - v129) * 0.3);
  v135 = v134 - v132;
  v136 = sqrtf((f32)(v133 * v133) + (f32)(v135 * v135));
  if (v136 <= 1.0 || v136 <= 100.0)
  {
    v48 = v134;
    goto LABEL_49;
  }
  v139 = v133 / v136;
  v140 = v135 / v136;
  v141 = gSbtlCam_offset_pos;
  v131 = v141[0];
  v132 = v141[2];
  v52 = (f32)(v139 * 100.0) + v131;
  v48 = (f32)(v140 * 100.0) + v132;
  v55 = v48;
  v48 = v55;
LABEL_49:
  v150 = v48;
  v56 = 0.0;
  v57 = 32;
  v156 = v52;
  v58 = gSbtlCam_offset_pos;
  v58[0] = v52;
  v58[2] = v48;
  vResTgt->w = 1.0;
  vResTgt->z = v48;
  v59 = &vResTgt->z;
  vResTgt->x = v52;
  vResTgt->y = v51 + (f32)(v154 * -0.5);
  do
  {
    v61 = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + v57))->_1.namespaze;
    if (v61)
    {
      v160 = v56;
      v63 = v61[41];
      v64 = v61[42];
      v65 = v61[43];
      v66 = v61[44];
      v67 = vResTgt->x;
      v68 = vResTgt->y;
      v69 = vResTgt->z;
      v70 = vResTgt->w;
      v173.x = v63;
      v173.y = v64;
      v173.z = v65;
      v173.w = v66;
      v174.x = v67;
      v174.y = v68;
      v174.z = v69;
      v174.w = v70;
      DisNoCamDep = GetDisNoCamDep(v173, v174);
      v72 = DisNoCamDep + DisNoCamDep;
      v56 = v160;
      if (v72 > v160)
        v56 = v72;
      v52 = v156;
    }
    v57 += 8;
  }
  while (v57 != 416);
  v74 = (f32)(v56 + sqrtf((f32)((f32)(v52 - p_pos->x) * (f32)(v52 - p_pos->x)) + (f32)((f32)(v150 - *v153) * (f32)(v150 - *v153))))
      * 0.5;
  if (v74 < 200.0)
    v74 = 200.0;
  if (v74 <= 1500.0)
    v75 = v74;
  else
    v75 = 1500.0;
  if (gsBtlCamera_Hokan_Not)
  {
    goto LABEL_67;
  }
  gSbtlCam_len = v75 + (f32)((f32)(gSbtlCam_len - v75) * 0.3);
LABEL_67:
  gSbtlCam_len = v75;
  direction = v151->direction;
  vct_B = direction;
  v78 = *vResTgt;
  vct_A = v78;
  v79 = &vf00.x;
  v80 = *p_pos;
  v81 = v79[6];
  v82 = v79[4];
  v83 = v79[5];
  v84 = v79[10];
  v85 = v79[8];
  v86 = v79[9];
  v87 = v82 * v85;
  v88 = v83 * v86;
  v89 = v87 + v88;
  v90 = v81 * v84;
  vct_A = v80;
  v91 = v90 + v89;
  v94.n64_u64[0] = *(u64 *)&vct_B.y;
  v95 = vct_A.x * vct_B.x;
  v96.n64_u64[0] = *(u64 *)&vct_A.y;
  v97 = &pBaseUnit->pos.z;
  v98 = vmul_f32(v96, v94).n64_u64[0];
  v99 = *((f32 *)&v98 + 1) + (f32)(v95 + *(f32 *)&v98);
  if (v99 >= v91)
    v97 = &vResTgt->z;
  v162 = *vResTgt;
  v100 = *v97;
  vct_A = v162;
  v102 = *p_pos;
  vct_B = v102;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x43C80000u));
  v104 = vct_A.z;
  if (v104 <= 0.0)
  {
    if (v99 >= v91)
      goto LABEL_96;
    goto LABEL_142;
  }
  v105 = -v104;
  vct_A.z = v105;
  if (v99 >= v91)
  {
LABEL_96:
    v106 = 720.0;
    goto LABEL_143;
  }
LABEL_142:
  v106 = (f32)(720.0 / (f32)((f32)(v91 - v99) + 720.0)) * 720.0;
LABEL_143:
  v115 = vResTgt->x;
  v116 = p_pos->x;
  v117 = vabds_f32(v115, v116);
  v118 = v117 + v117;
  if (v106 < v118)
    v106 = v118;
  v120 = -v106;
  if (vct_A.z > v120)
    vct_A.z = v120;
  v122 = *p_pos;
  v157 = v122;
  v122 = v157;
  v123 = v152;
  vct_A = v122;
  vct_A.z = v100;
  vct_B = vct_A;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  *v123 = vct_A;
  v123->x = vResTgt->x * 0.9;
  v123->y = (f32)((f32)((f32)(*v153 + 1000.0) * -0.04) * 3.0) + -150.0;
  if (camera_bossmode == 1)
  {
    v126 = v123->z;
    v123->y = -450.0;
    v123->z = v126 + -200.0;
    if (*v59 < -200.0)
      *v59 = -200.0;
  }
  vResTgt->w = 1.0;
  v123->w = 1.0;
  return v148;
}

// 0x1ef0200
void sBtlResetIdling_HD(void) {
  SBTLCAMERA_WORK *camera;
  s32 encountno;
  f32 v8;

  camera = wk->scene->camera;
  *(u64 *)&gZoomCnt = 0;
  gZoomStatus = 0;
  gAuto_ManualKaiten_Cnt = 0;
  gKaitenHiSpd = 0;
  gBoss_SkillLong_Nml = 0.0;
  encountno = wk->encountno;
  camera->followUpAngle.y = 0.0;
  v8 = 180.0;
  if (encountno == 26)
    v8 = 0.0;
  camera->followUpAngle.x = v8;
  gsBtlCamera_Hokan_Not = 1;
}

// 0x1ef03d0
void sBtlGetIdling_HD_Sub(SBTLCAMERA_WORK *wk, SBTLUNIT_WORK *pBaseUnit, const sdfVector4_t *vResTgt, sdfVector4_t *targetPos, sdfVector4_t *cameraPos) {
  f32 z;
  f32 y;
  f32 gFreeCam_Length_local;
  bool v13;
  bool v14;
  _BOOL4 v15;
  _BOOL4 v16;
  bool v17;
  bool v18;
  bool v19;
  f32 v22;
  f32 v26;
  f32 v31;
  f32 v35;
  SBATTLE_WORK *v36;
  f32 v37;
  SBATTLE_WORK *v38;
  s32 encountno;
  f32 v40;
  SBTLSCENE_WORK *scene;
  SBTLCAMERA_WORK *v42;
  f32 v43;
  f32 v44;
  SBTLSCENE_WORK *v45;
  f32 v46;
  s32 v47;
  s32 battlemode;
  bool v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  s32 v58;
  s32 v59;
  u32 v61;
  f32 v62;
  f32 v64;
  f32 v65;
  f32 v67;
  f32 v68;
  u32 v70;
  f32 v71;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  f32 v105;
  f32 v106;
  f32 v107;
  f32 v108;
  s32 v109;
  f32 v110;
  f32 v111;
  f32 v115;
  bool v116;
  f32 v120;
  s32 v121;
  bool v122;
  f32 v123;
  f32 v124;
  f32 v125;
  f32 v126;
  f32 v127;
  f32 v128;
  f32 v129;
  u32 v131;
  f32 v132;
  f32 v133;
  f32 v134;
  f32 v135;
  f32 v136;
  f32 v137;
  f32 v138;
  f32 v139;
  f32 v140;
  f32 v141;
  f32 v142;
  f32 v144;
  f32 v145;
  f32 v147;
  f32 v149;
  f32 v153;
  f32 v154;
  bool IsAction;
  SBTLCAMERA_WORK *v156;
  f32 v157;
  bool v158;
  f32 v159;
  f32 x;
  f32 v161;

  x = vResTgt->x;
  z = vResTgt->z;
  y = vResTgt->y;
  v156 = wk;
  gFreeCam_Length_local = gFreeCam_Length;
  IsAction = IsAction(3);
  v158 = IsAction(5);
  v13 = IsAction(12);
  v14 = IsAction(15);
  v15 = IsAction(13);
  v16 = IsAction(14);
  v17 = IsAction(16);
  v18 = IsAction(17);
  v19 = IsAction(18);
  if (!v13)
  {
    v22 = gBoss_BS_LASTB2_ST_Nml + -0.05;
    gBoss_BS_LASTB2_ST_Nml = v22;
    if (v22 < 0.0)
    {
      gBoss_BS_LASTB2_ST_Nml = 0.0;
    }
  }
  if (v15 || v16)
  {
    goto LABEL_44;
  }
  if (v14 || v17 || v18)
  {
    v26 = gBoss_BS_LASTB2_Nml + 0.01;
    gBoss_BS_LASTB2_Nml = v26;
    if (v26 > 1.0)
    {
      gBoss_BS_LASTB2_Nml = 1.0;
    }
    gBoss_BS_LASTB2_Wait = 150;
    goto LABEL_44;
  }
  if (gBoss_BS_LASTB2_Wait >= 1)
  {
    gBoss_BS_LASTB2_Wait = gBoss_BS_LASTB2_Wait - 1;
  }
  if (gBoss_BS_LASTB2_Nml > 0.0)
    goto LABEL_32;
LABEL_43:
  gBoss_BS_LASTB2_Nml = 0.0;
  goto LABEL_44;
LABEL_32:
  if (!gBoss_BS_LASTB2_Wait)
  {
    v31 = gBoss_BS_LASTB2_Nml + -0.01;
    gBoss_BS_LASTB2_Nml = v31;
    if (v31 < 0.0)
    {
      goto LABEL_43;
    }
  }
LABEL_44:
  v161 = z;
  v35 = 0.0;
  v36 = wk;
  if (v36->CameraGazeOff)
  {
    v37 = 0.0;
    goto LABEL_48;
  }
  v36 = wk;
  battlemode = (u16)v36->battlemode;
  if (gZoomLenNml < 0.0 || battlemode == 3)
    v35 = 0.0;
  else
    v35 = gZoomLenNml;
  if (battlemode == 3)
    v37 = 0.0;
  else
    v37 = gZoomLenNml;
LABEL_48:
  v38 = wk;
  encountno = v38->encountno;
  if (encountno > 477)
    goto LABEL_49;
  goto LABEL_82;
  if (encountno <= 477)
  {
LABEL_82:
    switch (encountno)
    {
      case 22:
        v51 = v35 <= 0.0;
        v47 = 0;
        v52 = 200.0;
        goto LABEL_89;
      case 23:
      case 25:
      case 26:
      case 30:
      case 40:
      case 45:
      case 53:
      case 58:
      case 449:
      case 451:
      case 452:
      case 453:
      case 454:
      case 455:
      case 456:
      case 457:
      case 458:
      case 459:
      case 460:
      case 461:
      case 462:
      case 463:
      case 464:
      case 465:
      case 466:
      case 467:
      case 468:
      case 469:
      case 470:
      case 471:
      case 472:
      case 473:
      case 474:
      case 475:
        v47 = 0;
        if (v37 > 0.0)
          v37 = 0.0;
        if (v35 > 0.0)
          v35 = 0.0;
        goto LABEL_87;
      case 24:
      case 29:
      case 34:
      case 41:
      case 50:
      case 56:
      case 57:
LABEL_88:
        v51 = v35 <= 0.0;
        v47 = 0;
        v52 = 100.0;
        goto LABEL_89;
      case 32:
      case 476:
      case 477:
        v53 = v35;
        v42 = v156;
        if (!sBtlChkEnemyID(184))
        {
          v47 = 0;
          v35 = v53;
          if (v37 <= 0.0)
            goto LABEL_163;
          goto LABEL_109;
        }
        v47 = 1;
        if (v53 <= 0.0)
          v35 = v53;
        else
          v35 = 0.0;
        gFreeCam_Length_local = gFreeCam_Length_local + 400.0;
        if (v37 <= 0.0)
          goto LABEL_108;
        goto LABEL_173;
      case 46:
      case 55:
        if (v37 > 0.0)
          v37 = 0.0;
        if (v35 > 0.0)
          v35 = 0.0;
        if (v158)
        {
          if (!v61)
          {
            v62 = v35;
            v35 = v62;
          }
          v64 = 1.0;
          v42 = v156;
          v65 = gBoss_SkillLong_Nml + 0.01;
          gBoss_SkillLong_Nml = v65;
          if (v65 > 1.0)
          {
            goto LABEL_149;
          }
        }
        else
        {
          if (!v61)
          {
            v75 = v35;
            v35 = v75;
          }
          v42 = v156;
          v76 = gBoss_SkillLong_Nml + -0.01;
          gBoss_SkillLong_Nml = v76;
          if (v76 < 0.0)
          {
            v64 = 0.0;
            v77 = v35;
            v35 = v77;
LABEL_149:
            gBoss_SkillLong_Nml = v64;
          }
        }
        v78 = v35;
        v35 = v78;
        v47 = 0;
        v80 = 150.0;
        goto LABEL_162;
      case 48:
      case 52:
        v51 = v35 <= 0.0;
        v47 = 0;
        v52 = 50.0;
LABEL_89:
        if (!v51)
          v35 = 0.0;
        gFreeCam_Length_local = gFreeCam_Length_local + v52;
        v42 = v156;
        if (v37 > 0.0)
          goto LABEL_173;
        goto LABEL_108;
      case 59:
        if (v37 > 0.0)
          v37 = 0.0;
        if (v35 > 0.0)
          v35 = 0.0;
        v67 = gFreeCam_Length_local + 150.0;
        v68 = v35;
        v35 = v68;
        v47 = 0;
        gFreeCam_Length_local = v67 + (f32)(gBoss_BS_LASTB2_Nml * 500.0);
LABEL_87:
        v42 = v156;
        goto LABEL_163;
      case 60:
        if (v37 > 0.0)
          v37 = 0.0;
        if (v35 > 0.0)
          v35 = 0.0;
        if (v19)
        {
          if (!v70)
          {
            v71 = v35;
            v35 = v71;
          }
          v73 = 1.0;
          v42 = v156;
          v74 = gBoss_SkillLong_Nml + 0.05;
          gBoss_SkillLong_Nml = v74;
          if (v74 > 1.0)
          {
            goto LABEL_158;
          }
        }
        else
        {
          if (!v70)
          {
            v81 = v35;
            v35 = v81;
          }
          v42 = v156;
          v82 = gBoss_SkillLong_Nml + -0.01;
          gBoss_SkillLong_Nml = v82;
          if (v82 < 0.0)
          {
            v73 = 0.0;
            v83 = v35;
            v35 = v83;
LABEL_158:
            gBoss_SkillLong_Nml = v73;
          }
        }
        v84 = v35;
        v35 = v84;
        v47 = 0;
        v80 = 700.0;
LABEL_162:
        gFreeCam_Length_local = gFreeCam_Length_local + (f32)((f32)(gBoss_SkillLong_Nml * 400.0) + v80);
        goto LABEL_163;
      default:
LABEL_51:
        v40 = v35;
        v35 = v40;
        v38 = wk;
        scene = v38->scene;
        v42 = v156;
        if (scene->major != 37)
          goto LABEL_62;
        v43 = v35;
        v35 = v43;
        scene = wk->scene;
        if (scene->minor != 13)
        {
LABEL_62:
          v44 = v35;
          v35 = v44;
          v45 = wk->scene;
          if (v45->major != 39)
            goto LABEL_107;
          v46 = v35;
          v35 = v46;
          v45 = wk->scene;
          if (v45->minor != 13)
          {
LABEL_107:
            v47 = 0;
            goto LABEL_108;
          }
        }
        v47 = 0;
        if (v35 > 0.0)
          v35 = 0.0;
        gFreeCam_Length_local = gFreeCam_Length_local + 150.0;
        if (v37 > 0.0)
          goto LABEL_173;
        goto LABEL_108;
    }
  }
LABEL_49:
  if ((u32)(encountno - 518) <= 0xFFFFFFF9)
  {
    switch (encountno)
    {
      case 526:
      case 534:
      case 535:
      case 536:
      case 537:
        goto LABEL_88;
      default:
        goto LABEL_51;
    }
  }
  v42 = v156;
  if (!IsAction)
  {
    v47 = 0;
    v35 = 0.0;
    goto LABEL_173;
  }
  v47 = 0;
  if (v35 > 0.0)
    v35 = 0.0;
  gFreeCam_Length_local = gFreeCam_Length_local + 400.0;
  if (v37 <= 0.0)
  {
LABEL_108:
    if (v37 > 0.0)
    {
LABEL_109:
      v54 = v42->followUpAngle.y;
      if (v54 > 300.0 && v35 > 0.0)
      {
        v55 = (f32)(360.0 - v54) / 30.0;
        v56 = 75.0;
        v57 = -150.0;
        *(f32 *)&v58 = -75.0;
        goto LABEL_167;
      }
      *(f32 *)&v59 = -150.0;
      goto LABEL_171;
    }
LABEL_163:
    if (v37 >= 0.0)
      goto LABEL_173;
    v85 = v42->followUpAngle.y;
    if (v85 > 300.0 && v35 > 0.0)
    {
      v55 = (f32)(360.0 - v85) / 30.0;
      v56 = 50.0;
      v57 = -100.0;
      *(f32 *)&v58 = -50.0;
LABEL_167:
      v86 = (f32)(v55 * v56) + v57;
      v51 = v55 <= 1.0;
      v87 = *(f32 *)&v58;
      if (v51)
        v87 = v86;
      goto LABEL_172;
    }
    *(f32 *)&v59 = -100.0;
LABEL_171:
    v87 = *(f32 *)&v59;
LABEL_172:
    gFreeCam_Length_local = gFreeCam_Length_local + (f32)(v37 * v87);
  }
LABEL_173:
  v88 = v42->followUpAngle.y;
  v89 = 0.5;
  v90 = (f32)(v88 * 0.017453292) * 0.15915494;
  v91 = (s32)v90;
  if (v90 == INFINITY)
    v91 = -2147500000.0;
  v92 = v90 - v91;
  if ((f32)(v90 - v91) <= 0.5)
  {
    if (v92 >= -0.5)
      goto LABEL_180;
    v93 = 1.0;
  }
  else
  {
    v93 = -1.0;
  }
  v92 = v92 + v93;
LABEL_180:
  if (v92 <= 0.25)
  {
    if (v92 < -0.25)
      v92 = -0.5 - v92;
  }
  else
  {
    v92 = 0.5 - v92;
  }
  v94 = (f32)((f32)(v88 * 0.017453292) + 1.5708) * 0.15915494;
  v95 = (s32)v94;
  if (v94 == INFINITY)
    v95 = -2147500000.0;
  v96 = v94 - v95;
  if ((f32)(v94 - v95) <= 0.5)
  {
    if (v96 >= -0.5)
      goto LABEL_191;
    v97 = 1.0;
  }
  else
  {
    v97 = -1.0;
  }
  v96 = v96 + v97;
LABEL_191:
  if (v96 <= 0.25)
  {
    if (v96 < -0.25)
      v96 = -0.5 - v96;
  }
  else
  {
    v96 = 0.5 - v96;
  }
  v98 = v42->followUpAngle.x * 0.017453292;
  v99 = v98 * 0.15915494;
  v100 = (s32)(v98 * 0.15915494);
  if ((f32)(v98 * 0.15915494) == INFINITY)
    v100 = -2147500000.0;
  v101 = v99 - v100;
  if ((f32)(v99 - v100) <= 0.5)
  {
    if (v101 >= -0.5)
      goto LABEL_202;
    v102 = 1.0;
  }
  else
  {
    v102 = -1.0;
  }
  v101 = v101 + v102;
LABEL_202:
  v157 = y;
  if (v101 <= 0.25)
  {
    if (v101 < -0.25)
      v101 = -0.5 - v101;
  }
  else
  {
    v101 = 0.5 - v101;
  }
  v103 = (f32)(v98 + 1.5708) * 0.15915494;
  v104 = (s32)v103;
  if (v103 == INFINITY)
    v104 = -2147500000.0;
  v105 = v103 - v104;
  if ((f32)(v103 - v104) <= 0.5)
  {
    if (v105 >= -0.5)
      goto LABEL_213;
    v106 = 1.0;
  }
  else
  {
    v106 = -1.0;
  }
  v105 = v105 + v106;
LABEL_213:
  if (v105 <= 0.25)
  {
    if (v105 < -0.25)
      v105 = -0.5 - v105;
  }
  else
  {
    v105 = 0.5 - v105;
  }
  v107 = 0.0;
  v108 = 11.0;
  if (v88 > 0.0 && v88 < 11.0)
    v107 = (f32)(v88 / 10.0) * -60.0;
  v159 = gFreeCam_Length_local;
  v109 = wk->encountno;
  if (v109 > 477)
    goto LABEL_222;
  goto LABEL_231;
  if (v109 <= 477)
  {
LABEL_231:
    v110 = 0.0;
    v111 = 0.0;
    switch (v109)
    {
      case 22:
      case 23:
      case 24:
      case 26:
      case 27:
      case 28:
      case 29:
      case 31:
      case 33:
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 40:
      case 41:
      case 42:
      case 43:
      case 44:
      case 45:
      case 47:
      case 49:
      case 50:
      case 51:
      case 54:
      case 57:
        goto LABEL_246;
      case 25:
      case 30:
      case 53:
        v115 = v35;
        v116 = IsAction(2);
        if (v116)
        {
          v35 = v115;
          v120 = gTgtExSkill_Y + -2.0;
          gTgtExSkill_Y = v120;
          if (v120 < -100.0)
          {
            v121 = -1027080192;
LABEL_238:
            LODWORD(gTgtExSkill_Y) = v121;
            goto LABEL_276;
          }
        }
        else
        {
          v35 = v115;
          if (gTgtExSkill_Y < 0.0)
          {
            v35 = v115;
            v147 = gTgtExSkill_Y + v89;
            gTgtExSkill_Y = v147;
            if (v147 > 0.0)
            {
              v121 = 0;
              goto LABEL_238;
            }
          }
        }
LABEL_276:
        v35 = v115;
        v111 = gTgtExSkill_Y;
        v110 = 100.0;
        goto LABEL_246;
      case 32:
        goto LABEL_281;
      case 34:
      case 56:
        v111 = 25.0;
        v110 = -50.0;
        goto LABEL_246;
      case 46:
      case 55:
        v144 = v35;
        v35 = v144;
        v145 = gBoss_SkillLong_Nml;
        v111 = (f32)(v145 * 40.0) + -40.0;
        v110 = (f32)(v145 * -300.0) + -30.0;
        goto LABEL_246;
      case 48:
      case 52:
        v110 = 10.0;
        v111 = -60.0;
        goto LABEL_246;
      case 58:
        v111 = 30.0;
        goto LABEL_246;
      case 59:
        v149 = v35;
        v35 = v149;
        v111 = (f32)((f32)(gBoss_BS_LASTB2_Nml * -50.0) + 0.0) + (f32)(gBoss_BS_LASTB2_ST_Nml * -10.0);
        v110 = (f32)(gBoss_BS_LASTB2_ST_Nml * 110.0) + 0.0;
        goto LABEL_246;
      case 60:
        v153 = v35;
        v35 = v153;
        v154 = gBoss_SkillLong_Nml;
        v111 = (f32)(v154 * 300.0) + -150.0;
        v110 = (f32)(v154 * -700.0) + 0.0;
        goto LABEL_246;
      default:
        if (v109 == 449)
        {
          v111 = 0.0;
          goto LABEL_246;
        }
        v111 = 0.0;
        if ((v109 & 0xFFFFFFFE) != 0x1DC)
          goto LABEL_246;
LABEL_281:
        v122 = v47 == 0;
        goto LABEL_240;
    }
  }
LABEL_222:
  if ((u32)(v109 - 518) > 0xFFFFFFF9)
  {
    v122 = !IsAction;
LABEL_240:
    if (v122)
      v110 = 0.0;
    else
      v110 = -100.0;
    v111 = -130.0;
    if (v122)
      v111 = 0.0;
  }
  else
  {
    v110 = 0.0;
    v111 = 0.0;
    if (v109 != 526)
    {
      v110 = v109 == 537 ? -50.0 : 0.0;
      v111 = 25.0;
      if (v109 != 537)
        v111 = 0.0;
    }
  }
LABEL_246:
  v123 = v42->followUpAngle.y;
  if (v123 <= 0.0 || v123 >= v108 || v35 <= 0.0)
  {
    v127 = 0.0;
    if (v123 <= 300.0 || v35 <= 0.0)
    {
      v126 = 0.0;
    }
    else
    {
      v128 = (f32)(360.0 - v123) / 30.0;
      v129 = 1.0;
      if (v128 <= 1.0)
        v129 = v128;
      v126 = (f32)(v129 * -20.0) + 0.0;
      v127 = (f32)(v129 * -50.0) + 0.0;
    }
  }
  else
  {
    v124 = v123 / 10.0;
    if (v124 <= 1.0)
      v125 = v124;
    else
      v125 = 1.0;
    v126 = (f32)(v125 * -50.0) + 0.0;
    v127 = (f32)(v125 * 100.0) + 0.0;
    if (v110 > 0.0)
      v110 = v110 * (f32)(1.0 - v125);
  }
  targetPos->w = 1.0;
  v133 = x;
  v132 = v161;
  targetPos->x = x;
  targetPos->z = v161;
  targetPos->y = v111 + (f32)((f32)(v157 + v107) + v126);
  if (!v131)
  {
    v133 = targetPos->x;
    v132 = targetPos->z;
  }
  v134 = v96 * 4.0;
  v135 = v105 * 4.0;
  v136 = v92 * 4.0;
  v137 = v101 * 4.0;
  cameraPos->w = 1.0;
  v138 = v134 * v134;
  v139 = v135 * v135;
  v140 = v137 * v137;
  v141 = v159
       * (f32)((f32)((f32)((f32)((f32)(v134 * 1.5708) - (f32)((f32)(v134 * (f32)(v134 * v134)) * 0.6459637)) + (f32)((f32)(v138 * (f32)(v134 * (f32)(v134 * v134))) * 0.07968968)) - (f32)((f32)(v138 * (f32)(v138 * (f32)(v134 * (f32)(v134 * v134)))) * 0.0046737655)) + (f32)((f32)(v138 * (f32)(v138 * (f32)(v138 * (f32)(v134 * (f32)(v134 * v134))))) * 0.00015148419));
  v142 = v127
       + (f32)((f32)((f32)((f32)(v159 * (f32)((f32)((f32)((f32)((f32)((f32)(v92 * 4.0) * 1.5708) - (f32)((f32)(v136 * (f32)(v136 * v136)) * 0.6459637)) + (f32)((f32)((f32)(v136 * v136) * (f32)(v136 * (f32)(v136 * v136))) * 0.07968968)) - (f32)((f32)((f32)(v136 * v136) * (f32)((f32)(v136 * v136) * (f32)(v136 * (f32)(v136 * v136)))) * 0.0046737655)) + (f32)((f32)((f32)(v136 * v136) * (f32)((f32)(v136 * v136) * (f32)((f32)(v136 * v136) * (f32)(v136 * (f32)(v136 * v136))))) * 0.00015148419))) * 1.0) + 0.0) + gFreeCam_Y);
  cameraPos->x = (f32)(v141 * (f32)((f32)((f32)((f32)((f32)(v137 * 1.5708) - (f32)((f32)(v137 * (f32)(v137 * v137)) * 0.6459637)) + (f32)((f32)(v140 * (f32)(v137 * (f32)(v137 * v137))) * 0.07968968)) - (f32)((f32)(v140 * (f32)(v140 * (f32)(v137 * (f32)(v137 * v137)))) * 0.0046737655)) + (f32)((f32)(v140 * (f32)(v140 * (f32)(v140 * (f32)(v137 * (f32)(v137 * v137))))) * 0.00015148419)))
                      + v133;
  cameraPos->y = v110 + v142;
  cameraPos->z = (f32)(v141 * (f32)((f32)((f32)((f32)((f32)((f32)(v105 * 4.0) * 1.5708) - (f32)((f32)(v135 * (f32)(v135 * v135)) * 0.6459637)) + (f32)((f32)(v139 * (f32)(v135 * (f32)(v135 * v135))) * 0.07968968)) - (f32)((f32)(v139 * (f32)(v139 * (f32)(v135 * (f32)(v135 * v135)))) * 0.0046737655)) + (f32)((f32)(v139 * (f32)(v139 * (f32)(v139 * (f32)(v135 * (f32)(v135 * v135))))) * 0.00015148419)))
                      + v132;
}

// 0x1ef15f0
void sBtlGetIdling_HD(SBTLCAMERA_WORK *wk, SBTLUNIT_WORK *pBaseUnit, SBTLUNIT_WORK *pTgtUnit, sdfVector4_t *vResPos, sdfVector4_t *vResTgt) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  bool GunMode_Camera;
  SBTLCAMERA_WORK *p_fields;
  f32 v19;
  f32 v20;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *UnitFromDevilID;
  _BOOL4 IsAction;
  _BOOL4 v26;
  SBTLUNIT_LISTWORK *v29;
  f32 v31;
  SBTLCAMERA_WORK *camera;
  s32 v34;
  f32 v35;
  s64 v36;
  SBTLUNIT_WORK *v38;
  SBTLUNIT_WORK *v40;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *v43;
  int32x2_t v44;
  s32 devilid;
  u64 v46;
  sdfVector2_t *v47;
  u64 v49;
  u64 v50;
  f32 v52;
  int32x2_t v53;
  f32 gRingTgt_Dir_local;
  s32 v56;
  sdfVector4_t *v57;
  u32 status;
  char v59;
  u32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  u64 v66;
  u64 v67;
  f32 v69;
  f32 v70;
  f32 v71;
  s32 v72;
  s64 j;
  VISUALDATA_WORK *VisualData;
  f32 v75;
  const char *v76;
  SBTLUNIT_WORK *v77;
  f32 v78;
  f32 v79;
  f32 v80;
  u16 v81;
  s32 v82;
  f32 v84;
  f32 v88;
  f32 v89;
  f32 Dir_Hokan;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 LenXZ;
  f32 v97;
  f32 v98;
  SBTLCAMERA_WORK *v99;
  f32 v100;
  f32 v101;
  f32 hit_area_r;
  f32 v103;
  f32 v104;
  f32 v105;
  s32 v106;
  f32 v108;
  f32 v109;
  s32 v110;
  s64 i;
  const char *namespaze;
  f32 *v113;
  f32 v114;
  f32 v115;
  f32 v116;
  f32 v117;
  f32 v120;
  f32 v121;
  f32 PosToDir;
  f32 v124;
  f32 v125;
  f32 v126;
  f32 v127;
  f32 v128;
  f32 v131;
  f32 v133;
  f32 v135;
  SBTLUNIT_WORK *v136;
  f32 v138;
  sdfVector4_t *v139;
  __int128 v142;
  s32 v143;
  f32 v144;
  f32 v145;
  f32 v146;
  f32 v148;
  f32 v149;
  u32 v150;
  f32 v151;
  f32 v152;
  f32 v153;
  f32 v154;
  f32 v155;
  u32 v156;
  f32 v163;
  f32 v164;
  SBTLCAMERA_WORK *v165;
  f32 v166;
  f32 v167;
  f32 v168;
  f32 v171;
  s32 v172;
  f32 v175;
  f32 AtoB_LR_ABS;
  f32 v181;
  f32 v182;
  SBTLCAMERA_WORK *v183;
  f32 v184;
  f32 v185;
  f32 v186;
  f32 v187;
  f32 v189;
  f32 v190;
  s64 v191;
  u64 v192;
  s64 v193;
  s64 v194;
  u64 v195;
  s64 v196;
  s64 v197;
  u64 v198;
  s64 v199;
  s64 v200;
  u64 v201;
  s64 v202;
  s32 mode;
  s32 v205;
  f32 v208;
  f32 v209;
  f32 v212;
  s32 v213;
  s32 v214;
  s32 v215;
  s32 v216;
  s32 v217;
  s32 v218;
  s32 v219;
  s32 v220;
  f32 v222;
  f32 v223;
  f32 v224;
  f32 v225;
  f32 v226;
  f32 v227;
  f32 v228;
  f32 v229;
  f32 v230;
  f32 v231;
  f32 v232;
  f32 v233;
  f32 v234;
  char v235;
  f32 v237;
  f32 v238;
  s64 v239;
  f32 *v240;
  bool v241;
  f32 v242;
  f32 v243;
  f32 v244;
  s32 v245;
  f32 v246;
  f32 v247;
  f32 v248;
  f32 v249;
  f32 v250;
  f32 v251;
  f32 v252;
  f32 v253;
  f32 v254;
  f32 v255;
  f32 v256;
  f32 v257;
  f32 v258;
  f32 v259;
  f32 v260;
  f32 v261;
  f32 v262;
  f32 v263;
  f32 v264;
  f32 v265;
  f32 v266;
  SBTLCAMERA_WORK *v272;
  f32 v273;
  f32 v274;
  f32 v279;
  f32 v280;
  f32 v281;
  f32 v282;
  f32 v283;
  f32 v284;
  _BOOL4 v285;
  _BOOL4 v286;
  f32 v287;
  int32x2_t v288;
  f32 v289;
  f32 v290;
  f32 v294;
  f32 *v296;
  SBATTLE_WORK *v297;
  f32 v298;
  f32 v299;
  f32 v300;
  f32 v301;
  f32 v302;
  f32 v303;
  f32 v304;
  f32 v305;
  f32 v306;
  f32 v307;
  f32 v308;
  f32 v309;
  f32 v310;
  f32 v311;
  SBTLUNIT_WORK *v312;
  SBTLUNIT_LISTWORK *v313;
  s32 v314;
  SBTLUNIT_WORK *v315;
  SBTLUNIT_WORK *v316;
  SBATTLE_WORK *v318;
  f32 v319;
  f32 v320;
  float32x2_t v321;
  f32 v322;
  f32 v323;
  u64 v324;
  f32 v325;
  f32 v326;
  s32 v329;
  f32 v330;
  f32 v331;
  SBTLCAMERA_WORK *v332;
  f32 v333;
  f32 v334;
  f32 v335;
  f32 v336;
  float32x2_t v337;
  f32 v340;
  f32 v342;
  f32 v343;
  f32 v344;
  f32 v345;
  f32 v346;
  f32 v347;
  f32 v348;
  f32 v349;
  f32 v350;
  f32 v351;
  f32 fovy;
  f32 v353;
  f32 v354;
  f32 v355;
  f32 v356;
  f32 v357;
  f32 v358;
  u32 v359;
  f32 v361;
  f32 v362;
  f32 v363;
  f32 v364;
  f32 v366;
  f32 v367;
  s32 v368;
  f32 v369;
  f32 v370;
  f32 v371;
  f32 v372;
  f32 v373;
  f32 v374;
  f32 v375;
  f32 v376;
  u32 v378;
  f32 v379;
  bool IsHuuma;
  f32 v385;
  f32 v386;
  f32 v387;
  f32 v388;
  f32 v391;
  sdfVector4_t *v392;
  f32 v393;
  f32 v394;
  f32 v395;
  f32 v397;
  f32 v398;
  f32 v399;
  f32 v400;
  f32 v407;
  f32 v408;
  f32 v409;
  f32 v410;
  f32 v411;
  f32 v412;
  f32 v413;
  f32 v414;
  f32 v415;
  f32 v416;
  f32 v417;
  bool v418;
  s32 v419;
  f32 v420;
  f32 v421;
  _BOOL4 v422;
  f32 v423;
  f32 v424;
  f32 v425;
  f32 v426;
  f32 v427;
  f32 v428;
  f32 v429;
  f32 v430;
  u32 v438;
  bool v439;
  s32 v440;
  f32 v442;
  char v445;
  f32 *v446;
  f32 *v448;
  f32 *v451;
  SBTLUNIT_WORK *v453;
  SBTLCAMERA_WORK *v454;
  f32 v456;
  f32 v458;
  f32 v459;
  SBTLCAMERA_WORK *v460;
  f32 v461;
  f32 v462;
  f32 v463;
  f32 v466;
  f32 v467;
  f32 v469;
  f32 v471;
  f32 v472;
  SBTLCAMERA_WORK *v473;
  f32 v474;
  f32 v475;
  f32 v476;
  f32 v479;
  f32 v480;
  f32 v482;
  f32 *v483;
  f32 v484;
  f32 v485;
  f32 v488;
  f32 v491;
  s32 v492;
  f32 v493;
  f32 v495;
  f32 v496;
  f32 v498;
  f32 v503;
  f32 v504;
  f32 v507;
  f32 v508;
  f32 v510;
  f32 v511;
  f32 v513;
  f32 v514;
  f32 v516;
  f32 v517;
  f32 v519;
  f32 v520;
  char v522;
  f32 v523;
  f32 v527;
  f32 v531;
  s32 v533;
  f32 v534;
  f32 v535;
  f32 v536;
  f32 v537;
  f32 v540;
  f32 v541;
  f32 v542;
  f32 v543;
  f32 v544;
  f32 v545;
  f32 v546;
  s32 v547;
  f32 v548;
  f32 v549;
  f32 v550;
  s32 v551;
  f32 v552;
  f32 v553;
  f32 v554;
  f32 v555;
  f32 v556;
  f32 v561;
  f32 v563;
  f32 v564;
  f32 v565;
  f32 v566;
  f32 v567;
  f32 v568;
  f32 v569;
  f32 v570;
  f32 v571;
  f32 v572;
  bool v573;
  f32 v574;
  f32 v575;
  u32 v576;
  f32 v577;
  f32 v578;
  f32 v579;
  f32 v580;
  f32 v581;
  u32 v582;
  f32 v583;
  f32 v584;
  f32 v585;
  f32 v586;
  f32 v587;
  u32 v588;
  f32 v589;
  f32 v590;
  f32 v591;
  f32 v592;
  f32 v593;
  u32 v594;
  f32 v595;
  f32 v596;
  f32 v597;
  f32 v598;
  f32 v599;
  f32 v600;
  f32 v601;
  f32 v602;
  f32 v603;
  f32 v604;
  f32 v605;
  f32 v606;
  f32 v607;
  f32 v608;
  f32 v609;
  f32 v610;
  f32 v611;
  f32 v612;
  f32 v613;
  f32 v614;
  f32 v615;
  f32 v616;
  f32 v617;
  f32 v618;
  f32 v619;
  f32 v620;
  f32 v621;
  f32 v622;
  f32 v623;
  s32 v624;
  f32 v625;
  f32 v626;
  f32 v627;
  f32 v628;
  f32 v629;
  f32 v630;
  f32 v632;
  f32 v633;
  f32 v634;
  f32 v635;
  f32 v636;
  f32 v637;
  f32 LenXYZ;
  f32 v639;
  u64 *p_gAuto_Status;
  s64 v644;
  f32 v645;
  f32 *v646;
  u32 v649;
  f32 v650;
  f32 v651;
  f32 v652;
  f32 ABS;
  f32 v658;
  f32 v659;
  f32 v661;
  f32 v662;
  f32 v663;
  f32 v664;
  f32 v667;
  f32 v670;
  f32 v671;
  f32 v673;
  f32 v674;
  f32 v675;
  f32 v676;
  char v680;
  f32 v681;
  f32 v684;
  f32 v685;
  f32 v686;
  f32 v689;
  f32 v691;
  f32 v692;
  f32 v693;
  f32 v694;
  f32 v697;
  f32 v699;
  f32 v701;
  float32x2_t v703;
  float32x2_t v704;
  f32 v705;
  f32 v707;
  f32 v708;
  f32 v710;
  f32 v711;
  f32 v714;
  f32 v715;
  f32 v716;
  f32 v717;
  f32 v718;
  f32 v719;
  f32 v720;
  f32 v721;
  f32 v722;
  f32 v723;
  f32 *v725;
  f32 v726;
  f32 v727;
  f32 v728;
  f32 *v729;
  f32 v730;
  f32 v731;
  f32 v732;
  f32 v733;
  f32 v734;
  f32 AtoB_LR;
  f32 v736;
  f32 v739;
  f32 v740;
  f32 v742;
  f32 v745;
  f32 v746;
  f32 v748;
  f32 v749;
  f32 v750;
  f32 v751;
  f32 v756;
  f32 v757;
  f32 v759;
  f32 v760;
  f32 v761;
  f32 v762;
  f32 v763;
  f32 v766;
  f32 v768;
  f32 v769;
  f32 v770;
  f32 v771;
  s64 v774;
  f32 v775;
  f32 v777;
  f32 v778;
  f32 v780;
  s32 v782;
  f32 v784;
  u32 v785;
  f32 v786;
  s32 gZoomCnt_local;
  u32 v788;
  f32 v789;
  f32 v790;
  f32 v794;
  f32 v795;
  f32 v798;
  f32 v799;
  f32 v800;
  f32 v801;
  f32 v802;
  SBTLCAMERA_WORK *v803;
  s64 v811;
  s64 v815;
  u32 v822;
  f32 v823;
  f32 v825;
  f32 v826;
  f32 v827;
  f32 v828;
  f32 v831;
  _BOOL4 v832;
  f32 v833;
  f32 v834;
  s32 v835;
  s32 v836;
  s32 v837;
  _BOOL4 v838;
  _BOOL4 v839;
  s32 v840;
  f32 v841;
  _BOOL4 v842;
  u64 v843;
  f32 v844;
  s32 v845;
  s32 v846;
  s32 v847;
  s32 v848;
  f32 v849;
  s64 FromX;
  s64 v851;
  SBTLUNIT_WORK *v852;
  SBTLUNIT_WORK *v853;
  f32 v854;
  f32 v855;
  f32 v856;
  s32 v857;
  char v858;
  s32 v859;
  f32 v860;
  char v861;
  bool v862;
  s32 width;
  char v864;
  f32 v865;
  f32 GazeOff_GunMode_RY;
  _BOOL4 v867;
  bool v868;
  bool v869;
  bool v870;
  f32 v871;
  bool v872;
  f32 v873;
  _BOOL4 v874;
  f32 v875;
  float32x2_t v876;
  _BOOL4 gKaitenHiSpd_local;
  _BOOL4 v878;
  bool v879;
  _BOOL4 v880;
  _BOOL4 v881;
  sdfVector4_t *v882;
  f32 FromZ;
  bool v884;
  f32 v885;
  _BOOL4 v886;
  s64 v887;
  f32 v888;
  _BOOL4 v889;
  f32 v890;
  bool v891;
  SBTLCAMERA_WORK *wka;
  f32 *p_followUpAngle;
  struct sdfVector4_t v895;
  s64 UpV;
  u64 Fov;
  s64 CY;
  s64 TZ;
  s64 TX;
  s64 VY;
  s64 v902;
  s64 v903;
  s64 v904;
  sdfVector4_t ppos;
  f32 OutZ;
  s64 OutY;
  sdfVector4_t cameraPos;
  sdfVector4_t targetPos;
  u64 ToX;
  s64 ToZ;
  s64 Dir;
  f32 SlideNml[3];
  sdfVector4_t v914;
  sdfVector4_t v915;
  sdfVector4_t v916;
  sdfVector4_t v917;
  sdfVector4_t v918;
  sdfVector4_t v919;
  sdfVector4_t v920;
  sdfVector4_t v921;
  sdfVector4_t v922;

  SlideNml[0] = 0.0;
  Dir = 0;
  ToZ = 0;
  x = pBaseUnit->rot.x;
  y = pBaseUnit->rot.y;
  z = pBaseUnit->rot.z;
  w = pBaseUnit->rot.w;
  ToX = 0;
  *(u64 *)&targetPos.x = 0;
  *(u64 *)&targetPos.z = 0;
  OutY = 0;
  OutZ = 0.0;
  UpV = 0;
  *(u64 *)&cameraPos.x = 0;
  *(u64 *)&cameraPos.z = 0;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  v903 = 0;
  v904 = 0;
  VY = 0;
  v902 = 0;
  TZ = 0;
  TX = 0;
  Fov = 0;
  CY = 0;
  v914.x = x;
  v914.y = y;
  v914.z = z;
  v914.w = w;
  RotToDir = sBtlGetRotToDir(v914);
  vResTgt->w = 1.0;
  vResPos->w = 1.0;
  GunMode_Camera = sBtlGetGunMode_Camera(SlideNml, (f32 *)&Dir + 1, &Dir);
  v891 = GunMode_Camera;
  wka = wk;
  v882 = vResPos;
  gAuto_ManualKaiten_Input = 0;
  v19 = wk->followUpAngle.x;
  p_fields = &wk->fields;
  v20 = v19;
  targetID = pBaseUnit->actaiwk->targetID;
  GazeOff_GunMode_RY = p_fields->GazeOff_GunMode_RY;
  if (targetID != -1)
  {
    UnitMng = wk->UnitMng;
    UnitFromDevilID = sBtlSearchUnit_ID(UnitMng, targetID);
    goto LABEL_14;
  }
  UnitFromDevilID = 0;
LABEL_14:
  gKaitenHiSpd_local = 1;
  IsAction = IsAction(1);
  v26 = IsAction(2);
  v886 = IsAction(7);
  v880 = IsAction(5);
  v881 = IsAction(6);
  v870 = IsAction(8);
  v869 = IsAction(9);
  v868 = IsAction(10);
  v867 = IsAction(11);
  IsAction(12);
  v878 = IsAction(13);
  v884 = IsAction(15);
  v874 = IsAction(16);
  v879 = IsAction(20);
  v889 = IsAction(21);
  v872 = v26;
  v862 = IsAction || v26;
  if (!IsAction && !v26)
  {
    gKaitenHiSpd_local = gKaitenHiSpd;
  }
  p_followUpAngle = &p_fields->followUpAngle;
  v871 = RotToDir;
  gKaitenHiSpd = 0;
  if (v889)
  {
    if (gBossTalk_targetID == -1)
    {
LABEL_30:
      v31 = 0.0;
      v855 = 0.0;
      if (!UnitFromDevilID)
      {
LABEL_35:
        v865 = v31;
        goto LABEL_36;
      }
LABEL_31:
      camera = wk->scene->camera;
      *(u64 *)&camera->CameraLockOnTargetPos.x = *(u64 *)&UnitFromDevilID->pos.x;
      camera->CameraLockOnTargetPos.z = UnitFromDevilID->pos.z;
LABEL_34:
      v31 = 0.0;
      goto LABEL_35;
    }
    v29 = wk->UnitMng;
    UnitFromDevilID = sBtlSearchUnit_ID(v29, gBossTalk_targetID);
    goto LABEL_30;
  }
  if (v879)
    goto LABEL_30;
  if (!v886)
  {
    if (v880 || v881)
    {
      v108 = 0.0;
      v109 = 0.0;
      v110 = 0;
      for (i = 32; i != 416; i += 8)
      {
        namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + i))->_1.namespaze;
        if (namespaze && (namespaze[832] & 2) != 0)
        {
          ++v110;
          v108 = v108 + *((f32 *)namespaze + 41);
          v109 = v109 + *((f32 *)namespaze + 43);
        }
      }
      v855 = v108 / (f32)v110;
      v31 = v109 / (f32)v110;
      goto LABEL_35;
    }
    if (v870)
    {
      UnitFromDevilID = sBtlGetUnitFromDevilID(269);
      if (!UnitFromDevilID)
      {
        UnitFromDevilID = sBtlGetUnitFromDevilID(304);
        if (!UnitFromDevilID)
          goto LABEL_424;
      }
    }
    else if (v869)
    {
      UnitFromDevilID = sBtlGetUnitFromDevilID(268);
      if (!UnitFromDevilID)
      {
        UnitFromDevilID = sBtlGetUnitFromDevilID(305);
        if (!UnitFromDevilID)
          goto LABEL_424;
      }
    }
    else
    {
      if (!v868)
      {
        v31 = 0.0;
        v855 = 0.0;
        if (!v867)
          goto LABEL_35;
        UnitFromDevilID = sBtlGetUnitEnemy1_Live();
        if (!UnitFromDevilID)
          goto LABEL_34;
        goto LABEL_31;
      }
      if (!UnitFromDevilID)
      {
        UnitFromDevilID = sBtlGetUnitEnemy1();
        if (!UnitFromDevilID)
        {
LABEL_424:
          v31 = 0.0;
          v855 = 0.0;
          goto LABEL_35;
        }
      }
    }
    v272 = wk->scene->camera;
    *(u64 *)&v272->CameraLockOnTargetPos.x = *(u64 *)&UnitFromDevilID->pos.x;
    v272->CameraLockOnTargetPos.z = UnitFromDevilID->pos.z;
    goto LABEL_424;
  }
  v69 = 0.0;
  v70 = 0.0;
  v71 = 0.0;
  v72 = 0;
  for (j = 32; j != 416; j += 8)
  {
    v76 = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + j))->_1.namespaze;
    if (v76 && (v76[832] & 2) != 0)
    {
      v77 = UnitFromDevilID;
      v78 = *((f32 *)v76 + 43);
      v79 = *((f32 *)v76 + 41);
      v80 = *((f32 *)v76 + 42);
      v81 = *((u16 *)v76 + 306);
      v82 = *((u32 *)v76 + 154);
      v69 = v69 + v79;
      v71 = v71 + v78;
      VisualData = sBtlGetVisualData(v81, v82);
      ++v72;
      UnitFromDevilID = v77;
      v75 = VisualData->nml->height * -0.5;
      v70 = (f32)(v70 + v80) + v75;
    }
  }
  v113 = wk->scene->camera;
  v855 = v69 / (f32)v72;
  v113[44] = v855;
  v113[45] = v70 / (f32)v72;
  v865 = v71 / (f32)v72;
  v113[46] = v865;
LABEL_36:
  v34 = 0;
  v35 = pBaseUnit->pos.x;
  v36 = 32;
  FromZ = pBaseUnit->pos.z;
  do
  {
    v38 = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + v36))->_1.namespaze;
    if (v38)
      _ZF = v38 == pBaseUnit;
    else
      _ZF = 1;
    if (!_ZF)
      v34 += ((u32)v38->side >> 1) & 1;
    v36 += 8;
  }
  while (v36 != 416);
  if (!UnitFromDevilID)
  {
    v52 = *(f32 *)&Dir;
    sBtlGetMoveXZ(v35, FromZ, v52, 500.0, (f32 *)&ToZ + 1, &ToZ);
    v47 = p_followUpAngle;
    v873 = *(f32 *)&ToZ;
    v53.n64_u32[0] = -1021968384;
    v53.n64_u32[1] = vdup_lane_s32(v53, 0).n64_u32[1];
    v53.n64_u32[0] = HIDWORD(ToZ);
    v876.n64_u64[0] = v53.n64_u64[0];
    goto LABEL_60;
  }
  v40 = UnitFromDevilID;
  major = UnitFromDevilID->major;
  minor = UnitFromDevilID->minor;
  v43 = sBtlGetVisualData(major, minor);
  UnitFromDevilID = v40;
  v873 = v40->pos.z;
  devilid = v40->para->devilid;
  *(f32 *)&v46 = v40->pos.x;
  v47 = p_followUpAngle;
  if ((devilid & 0xFFFFFFFE) == 0x138)
  {
    v875 = v40->pos.x;
    *(f32 *)&v46 = v875;
    v44.n64_u32[0] = -1021968384;
    HIDWORD(v49) = vdup_lane_s32(v44, 0).n64_u32[1];
    LODWORD(v49) = v46;
    v876.n64_u64[0] = v49;
    if (!wk->CameraGazeOff && (f32)(v40->pos.y + -50.0) <= -150.0)
    {
      LODWORD(v50) = v46;
      *((f32 *)&v50 + 1) = v40->pos.y + -50.0;
      v876.n64_u64[0] = v50;
LABEL_61:
      if (!pBaseUnit)
        goto LABEL_77;
      goto LABEL_62;
    }
LABEL_60:
    goto LABEL_61;
  }
  v61 = devilid - 413;
  v62 = v43->nml->height * 0.5;
  if (v62 < 90.0)
    v62 = 90.0;
  v63 = v40->pos.y - v62;
  if (v61 < 4)
    v63 = -200.0;
  *((f32 *)&v46 + 1) = v63;
  v876.n64_u64[0] = v46;
  goto LABEL_61;
  if (!pBaseUnit)
  {
LABEL_77:
    v57 = vResTgt;
    v64 = 0.0;
    v66 = 0;
    v67 = 0;
    goto LABEL_190;
  }
LABEL_62:
  gRingTgt_Dir_local = gRingTgt_Dir;
  if (!UnitFromDevilID)
  {
    if (!v884)
    {
      v57 = vResTgt;
      v89 = 150.0;
      goto LABEL_184;
    }
    v84 = 1.0;
    v57 = vResTgt;
    if (gRingTgt_R > 1.0)
    {
      gRingTgt_R = gRingTgt_R + -2.0;
      if (gRingTgt_R >= v84)
        goto LABEL_98;
      goto LABEL_164;
LABEL_163:
      if (gRingTgt_R >= v84)
      {
LABEL_98:
        goto LABEL_99;
      }
LABEL_164:
      gRingTgt_R = 1.0;
LABEL_99:
      v88 = gRingTgt_Dir;
      v89 = gRingTgt_R;
      gRingTgt_Dir_local = 0.0;
      Dir_Hokan = sBtlGetDir_Hokan(v88, 0.0, 1.0);
      gRingTgt_Dir = Dir_Hokan;
      goto LABEL_184;
    }
    goto LABEL_163;
  }
  v56 = (UnitFromDevilID->vstatus & 0x10000 | UnitFromDevilID->status & 0x4000000) == 0;
  v57 = vResTgt;
  if (sBtlIsHuuma())
  {
    status = UnitFromDevilID->actwk->status;
    goto LABEL_66;
  }
  v56 &= sBtlCheckDamageTarget(UnitFromDevilID);
  status = UnitFromDevilID->actwk->status;
LABEL_66:
  v59 = (gsBtlCamera_RingHokan_Not != 0) | (v881 || v880 || v886 || v872 || status == 40) | v56;
  if ((UnitFromDevilID->vstatus & 0x10000) != 0)
  {
    if ((v59 & 1) == 0)
      goto LABEL_123;
  }
  else
  {
    if (!((wk->encountno == 40) | v59 & 1))
    {
LABEL_123:
      v89 = 150.0;
      goto LABEL_184;
    }
  }
  v91 = pBaseUnit->pos.x;
  v92 = pBaseUnit->pos.z;
  v93 = UnitFromDevilID->pos.x;
  v94 = UnitFromDevilID->pos.z;
  LenXZ = sBtlGetLenXZ(v91, v92, v93, v94);
  if (v886)
  {
    v97 = pBaseUnit->pos.x;
    v98 = pBaseUnit->pos.z;
    v99 = wk->scene->camera;
    v100 = v99->CameraLockOnTargetPos.x;
    v101 = v99->CameraLockOnTargetPos.z;
    LenXZ = sBtlGetLenXZ(v97, v98, v100, v101);
  }
  hit_area_r = pBaseUnit->actaiwk->hit_area_r;
  v103 = fminf(hit_area_r + (f32)((f32)(LenXZ - (f32)(hit_area_r + UnitFromDevilID->actaiwk->hit_area_r)) * 0.5), 150.0);
  if (v103 >= hit_area_r)
    v89 = v103;
  else
    v89 = pBaseUnit->actaiwk->hit_area_r;
  v104 = 3.0;
  if (v89 < 100.0)
    v104 = 6.0;
  if (gKaitenHiSpd_local)
    v105 = 10.0;
  else
    v105 = v104;
  if (LenXZ >= 0.01)
  {
    v114 = pBaseUnit->pos.x;
    v115 = pBaseUnit->pos.z;
    v116 = UnitFromDevilID->pos.x;
    v117 = UnitFromDevilID->pos.z;
    gRingTgt_Dir_local = sBtlGetPosToDir(v114, v115, v116, v117);
    if (wk->mode == 27)
    {
      gRingTgt_Dir = gRingTgt_Dir_local;
      if (gsBtlCamera_Hokan_Not)
        goto LABEL_175;
LABEL_172:
      if (!gsBtlCamera_RingHokan_Not)
      {
        v273 = gRingTgt_Dir;
        v274 = sBtlGetDir_Hokan(v273, gRingTgt_Dir_local, v105);
        gRingTgt_Dir = v274;
        v106 = (u16)UnitFromDevilID->para->devilid;
        if (v106 == 314)
          goto LABEL_179;
        goto LABEL_178;
      }
LABEL_175:
      gRingTgt_Dir = gRingTgt_Dir_local;
      v106 = (u16)UnitFromDevilID->para->devilid;
      if (v106 == 314)
        goto LABEL_179;
LABEL_178:
      if (v106 != 258)
        goto LABEL_184;
      goto LABEL_179;
LABEL_171:
      if (gsBtlCamera_Hokan_Not)
        goto LABEL_175;
      goto LABEL_172;
    }
    goto LABEL_171;
  }
  v89 = gRingTgt_R;
  v106 = (u16)UnitFromDevilID->para->devilid;
  if (v106 != 314)
    goto LABEL_178;
LABEL_179:
  v120 = pBaseUnit->pos.x;
  v121 = pBaseUnit->pos.z;
  PosToDir = sBtlGetPosToDir(v120, v121, v120, v121 + 500.0);
  gRingTgt_Dir_local = PosToDir;
  v89 = 1.0;
  gRingTgt_Dir = gRingTgt_Dir_local;
LABEL_184:
  gRingTgt_R = v89;
  v124 = gRingTgt_Dir;
  v125 = pBaseUnit->pos.x;
  v126 = pBaseUnit->pos.z;
  sBtlGetMoveXZ(v125, v126, v124, v89, (f32 *)&ToX + 1, &ToX);
  v66 = ToX;
  v64 = pBaseUnit->pos.y + -160.0;
  sBtlGetMoveXZ(pBaseUnit->pos.x, pBaseUnit->pos.z, gRingTgt_Dir_local, v89, (f32 *)&ToX + 1, &ToX);
  v67 = ToX;
LABEL_190:
  if (wk->CameraGazeOff)
  {
    v127 = pBaseUnit->pos.x;
    v128 = pBaseUnit->pos.z;
    v64 = pBaseUnit->pos.y + -160.0;
    v66 = __PAIR64__(LODWORD(v127), LODWORD(v128));
    v67 = __PAIR64__(LODWORD(v127), LODWORD(v128));
  }
  gSbtlCam_offset_pos[1] = v64;
  LODWORD(gSbtlCam_offset_pos[2]) = v66;
  gSbtlCam_offset_pos[0] = *((f32 *)&v66 + 1);
  v57->x = *((f32 *)&v66 + 1);
  v57->y = v64;
  LODWORD(v57->z) = v66;
  v57->w = 1.0;
  if (!pBaseUnit)
  {
    v139 = v882;
    v142 = xmmword_3D06D30;
    vct_B.x = *((f32 *)&v66 + 1);
    vct_B.y = v64;
    v143 = (u8)byte_5755EF5;
    LODWORD(vct_B.z) = v66;
    vct_B.w = 1.0;
    *v139 = (struct sdfVector4_t)xmmword_3D06D30;
    if (v143)
    {
      goto LABEL_205;
    }
    else
    {
      v142 = xmmword_3D06D30;
LABEL_205:
      vct_A = (struct sdfVector4_t)v142;
      goto LABEL_206;
    }
    v895 = (struct sdfVector4_t)v142;
    vct_A = v895;
LABEL_206:
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    *v139 = vct_A;
    return;
  }
  v131 = wka->followUpAngle.x;
  v133 = sub_188E3E0(wka->followUpAngle.y + 360.0);
  wka->followUpAngle.y = v133;
  sBtlInputFollowUp(wka, v47);
  v135 = wka->followUpAngle.x;
  v138 = sBtlGet360(wka->followUpAngle.x);
  v47->x = v138;
  if (!v884)
    goto LABEL_216;
  if (v138 <= 250.0)
  {
    if (v138 >= 110.0)
      goto LABEL_216;
    v144 = -110.0;
  }
  else
  {
    v144 = -250.0;
  }
  v47->x = v138 + (f32)((f32)(v138 + v144) * -0.3);
LABEL_216:
  if (wk->encountno != 60)
    goto LABEL_225;
  v145 = v47->x;
  if (v47->x <= 270.0)
  {
    if (v145 >= 90.0)
      goto LABEL_225;
    v146 = -90.0;
  }
  else
  {
    v146 = -270.0;
  }
  v47->x = v145 + (f32)((f32)(v145 + v146) * -0.3);
LABEL_225:
  if (v878 || v874)
  {
    v47->x = v131;
  }
  else
  {
    if ((u32)(gAuto_Status - 17) > 5)
      goto LABEL_228;
LABEL_237:
    v47->x = v131;
    v148 = v57->x;
    v149 = v57->y;
    *(u64 *)&targetPos.x = 0;
    *(u64 *)&targetPos.z = 0;
    v152 = v57->z;
    v151 = v57->w;
    *(u64 *)&cameraPos.x = 0;
    *(u64 *)&cameraPos.z = 0;
    if (v156)
      goto LABEL_229;
    goto LABEL_238;
  }
  if ((u32)(gAuto_Status - 17) <= 5)
    goto LABEL_237;
LABEL_228:
  v148 = v57->x;
  v149 = v57->y;
  *(u64 *)&targetPos.x = 0;
  *(u64 *)&targetPos.z = 0;
  v152 = v57->z;
  v151 = v57->w;
  *(u64 *)&cameraPos.x = 0;
  *(u64 *)&cameraPos.z = 0;
  if (v150)
LABEL_238:
LABEL_229:
  v915.x = v148;
  v915.y = v149;
  v915.z = v152;
  v915.w = v151;
  sBtlGetIdling_HD_Sub(wka, v136, v915, &targetPos, &cameraPos);
  if (wk->mode == 27)
  {
    v153 = cameraPos.x;
    v154 = cameraPos.y;
    v155 = cameraPos.z;
    sBtlPlayerGetCamSdDash(v153, v154, v155, (f32 *)&OutY + 1, &OutY, &OutZ);
    cameraPos.x = *((f32 *)&OutY + 1);
    cameraPos.z = OutZ;
    v856 = v35;
    v854 = v20;
    if (!UnitFromDevilID)
      goto LABEL_267;
    goto LABEL_241;
  }
  v856 = v35;
  v854 = v20;
  if (!UnitFromDevilID)
    goto LABEL_267;
LABEL_241:
  if (wk->CameraGazeOff)
  {
    {
      if (v886 || v867 || v889)
      {
        gAuto_ManualKaiten_Cnt = 0;
        *(u64 *)&gAuto_Status = 17;
      }
      if (v870 || v869 || v868 || v879)
      {
        gAuto_ManualKaiten_Cnt = 0;
        *(u64 *)&gAuto_Status = 18;
        if (!v880 && !v881)
        {
LABEL_253:
          goto LABEL_254;
        }
      }
      else if (!v880 && !v881)
      {
        goto LABEL_253;
      }
      gAuto_ManualKaiten_Cnt = 0;
      *(u64 *)&gAuto_Status = 23;
LABEL_254:
      if (gAuto_Status != 18)
      {
        if (gAuto_Status != 17)
          goto LABEL_340;
        v163 = pBaseUnit->pos.x;
        v164 = pBaseUnit->pos.z;
        v165 = wk->scene->camera;
        v166 = v165->CameraLockOnTargetPos.x;
        v167 = v165->CameraLockOnTargetPos.z;
        v168 = sBtlGetPosToDir(v166, v167, v163, v164);
        if (sBtlGetAtoB_LR_ABS(v47->x, v168) <= 0.5)
        {
          v47->x = v168;
          gAuto_DirSpd = 0.0;
          gAuto_ManualKaiten_Cnt = 0;
          gAuto_Status = 0;
          ClrAction();
          SetCamDone();
          goto LABEL_340;
        }
        v171 = gAuto_DirSpd + 0.2;
        gAuto_DirSpd = v171;
        if (v171 > 2.0)
        {
          v172 = 0x40000000;
LABEL_292:
          LODWORD(gAuto_DirSpd) = v172;
          goto LABEL_293;
        }
        goto LABEL_293;
      }
      v181 = pBaseUnit->pos.x;
      v182 = pBaseUnit->pos.z;
      v183 = wk->scene->camera;
      v184 = v183->CameraLockOnTargetPos.x;
      v185 = v183->CameraLockOnTargetPos.z;
      v168 = sBtlGetPosToDir(v184, v185, v181, v182);
      if (sBtlGetAtoB_LR_ABS(v47->x, v168) <= 0.5)
      {
        v47->x = v168;
        gAuto_DirSpd = 0.0;
        gAuto_ManualKaiten_Cnt = 0;
        gAuto_Status = 0;
        if (v870 || v869 || v868 || v879)
        {
          SetCamDone();
          ClrAction();
        }
        goto LABEL_340;
      }
      v186 = gAuto_DirSpd + 0.4;
      gAuto_DirSpd = v186;
      if (v186 > 3.0)
      {
        v172 = 1077936128;
        goto LABEL_292;
      }
LABEL_293:
      v187 = v47->x;
      v189 = v187;
      v190 = v168;
      goto LABEL_339;
    }
LABEL_267:
    if (gAuto_Status == 19)
    {
      v175 = v47->x;
      AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(v175, 180.0);
      if (AtoB_LR_ABS <= 0.5)
      {
        ++gAuto_DoneCnt;
      }
      else
      {
        gAuto_DoneCnt = 0;
      }
      if (gAuto_DoneCnt >= 31)
      {
        v47->x = 180.0;
        gAuto_DirSpd = 0.0;
        gAuto_ManualKaiten_Cnt = 0;
        gAuto_Status = 0;
        if (v878 || v874)
        {
          if (v878)
            v205 = 14;
          else
            v205 = 17;
          SetAction(v205);
        }
      }
      v208 = gAuto_DirSpd + 0.1;
      gAuto_DirSpd = v208;
      if (v208 <= 2.0)
      {
        v209 = v47->x;
      }
      else
      {
        gAuto_DirSpd = 2.0;
        v209 = v47->x;
LABEL_338:
        v189 = v209;
        v190 = 180.0;
LABEL_339:
        v212 = sBtlGetDir_Hokan(v189, v190, gAuto_DirSpd);
        v47->x = sBtlGet360(v212);
        goto LABEL_340;
      }
      goto LABEL_338;
    }
    if (v878 || v874)
    {
      *(u64 *)&gAuto_Status = 19;
    }
    goto LABEL_340;
  }
  v852 = UnitFromDevilID;
  v853 = pBaseUnit;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  v191 = 1374389535 * get_width(0);
  v192 = (u64)v191 >> 63;
  FromX = v191 >> 37;
  width = get_width(0);
  v193 = 1374389535 * get_width(0);
  v843 = (u64)v193 >> 63;
  v851 = v193 >> 37;
  v859 = get_width(0);
  v194 = 1374389535 * get_width(0);
  v195 = (u64)v194 >> 63;
  v196 = v194 >> 37;
  v857 = get_width(0);
  get_height(0);
  get_height(0);
  get_height(0);
  v197 = 1374389535 * get_width(0);
  v198 = (u64)v197 >> 63;
  v199 = v197 >> 37;
  v848 = get_width(0);
  v200 = 1374389535 * get_width(0);
  v201 = (u64)v200 >> 63;
  v202 = v200 >> 37;
  v846 = get_width(0);
  mode = wk->mode;
  v837 = mode;
  v836 = mode;
  v214 = v196 + v195;
  v215 = v199 + v198;
  v216 = v202 + v201;
  v839 = sBtlChkNowJump_NotAtk(v853);
  v838 = sBtlChkNowJumpAfter(v853);
  v217 = 33 * (v851 + v843);
  v218 = 38 * (FromX + v192);
  v219 = 15 * v215;
  v220 = 28 * v214;
  pBaseUnit = v853;
  if (IsSceanStop())
    goto LABEL_352;
  if (wk->mode == 5)
LABEL_352:
    v840 = 1;
  else
    v840 = 0;
  v222 = v218;
  v223 = v217;
  v224 = v220;
  v841 = v220;
  v844 = v218;
  v225 = width;
  v226 = v859;
  v227 = v219;
  v228 = (8 * v216);
  v229 = v857;
  v230 = v848;
  if (v34 > 2)
  {
    v864 = 1;
    v235 = 0;
    UnitFromDevilID = v852;
  }
  else
  {
    UnitFromDevilID = v852;
    v849 = v859;
    v860 = width;
    v231 = v853->pos.x;
    v232 = v853->pos.z;
    v233 = v852->pos.x;
    v234 = v852->pos.z;
    if (sBtlGetLenXZ(v231, v232, v233, v234) >= 600.0)
    {
      v235 = 0;
      v864 = 1;
    }
    else
    {
      v864 = 0;
      v235 = 1;
    }
    v224 = v220;
    v222 = v844;
    v223 = v217;
    v225 = v860;
    v229 = v857;
    v226 = v849;
  }
  v237 = v230 - v227;
  v57 = vResTgt;
  v238 = 0.0;
  v239 = 32;
  v858 = 1;
  v861 = 0;
  v833 = v225 - v222;
  v834 = v226 - v223;
  v831 = v229 - v224;
  while (1)
  {
    v240 = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + v239))->_1.namespaze;
    if (v240)
      v241 = v240 == v853;
    else
      v241 = 1;
    if (!v241)
    {
      v242 = v240[41];
      v243 = v240[42];
      v244 = v240[43];
      sBtlChangeWorldtoScreenUnity3(v242, v243, v244, &ppos);
      v245 = get_width(0);
      v246 = ppos.x;
      v247 = (f32)(ppos.x * (f32)(2.0 / (f32)v245)) + -1.0;
      if (v247 < -1.0)
        v247 = -1.0;
      v238 = v247 <= 1.0 ? v247 : 1.0;
      if (ppos.x <= 0.0 || v246 >= (f32)get_width(0))
        break;
      if (ppos.x <= v227 || ppos.x >= v237)
      {
        v235 = 0;
        v858 = 0;
      }
      if (ppos.x <= v228 || ppos.x >= (f32)((f32)v846 - v228))
      {
        v861 = 1;
        v864 = 1;
      }
    }
    v239 += 8;
    if (v239 == 416)
      goto LABEL_387;
  }
  v235 = 0;
  v858 = 0;
  v861 = 1;
  v864 = 1;
LABEL_387:
  v248 = cameraPos.x;
  v249 = cameraPos.z;
  v250 = targetPos.x;
  v251 = targetPos.z;
  v252 = sBtlGetPosToDir(v248, v249, v250, v251);
  v253 = sBtlGetPosToDir(cameraPos.x, cameraPos.z, UnitFromDevilID->pos.x, UnitFromDevilID->pos.z);
  if (sBtlGetAtoB_LR_ABS(v252, v253) > 120.0)
    goto LABEL_439;
  v254 = cameraPos.x;
  v255 = cameraPos.z;
  v256 = v853->pos.x;
  v257 = v853->pos.z;
  v258 = sBtlGetLenXZ(v254, v255, v256, v257);
  if (v258 <= sBtlGetLenXZ(cameraPos.x, cameraPos.z, UnitFromDevilID->pos.x, UnitFromDevilID->pos.z))
    goto LABEL_442;
  v259 = cameraPos.x;
  v260 = cameraPos.z;
  v261 = v853->pos.x;
  v262 = v853->pos.z;
  v263 = sBtlGetPosToDir(v259, v260, v261, v262);
  v264 = sBtlGetAtoB_LR_ABS(v263, v253);
  v265 = UnitFromDevilID->actaiwk->hit_area_r;
  if (v265 >= 200.0)
  {
    v266 = 19.0;
  }
  else if (v265 >= 149.0)
  {
    v266 = 16.0;
  }
  else
  {
    v266 = v265 >= 129.0 ? 11.0 : 9.0;
  }
  if (v264 >= v266)
  {
LABEL_442:
    v847 = 0;
    gReverseCnt = 0;
  }
  else
  {
LABEL_439:
    if (gReverseCnt <= 9)
    {
      v847 = 0;
      gReverseCnt = gReverseCnt + 1;
      goto LABEL_9006;
    }
    v847 = 1;
LABEL_9006:
  }
  v279 = v853->pos.x;
  v280 = v853->pos.z;
  v281 = UnitFromDevilID->pos.x;
  v282 = UnitFromDevilID->pos.z;
  v283 = sBtlGetLenXZ(v279, v280, v281, v282);
  v284 = UnitFromDevilID->actaiwk->hit_area_r;
  v285 = v283 >= 1300.0;
  v286 = v283 <= (f32)(v284 + 500.0);
  if (!v891)
  {
    if (wka->CameraLockOnNone)
    {
      v835 = 0;
      v842 = 0;
      v845 = 0;
      v832 = 0;
      goto LABEL_621;
    }
    v415 = wka->CameraLockOnTargetPos.x;
    v416 = wka->CameraLockOnTargetPos.y;
    v417 = wka->CameraLockOnTargetPos.z;
    v418 = sBtlChangeWorldtoScreenUnity3(v415, v416, v417, &ppos);
    v419 = get_width(0);
    v420 = ppos.x;
    v238 = -1.0;
    v421 = (f32)(ppos.x * (f32)(2.0 / (f32)v419)) + -1.0;
    if (v421 >= -1.0)
    {
      if (v421 <= 1.0)
        v238 = (f32)(ppos.x * (f32)(2.0 / (f32)v419)) + -1.0;
      else
        v238 = 1.0;
      if (!v418)
        goto LABEL_620;
    }
    else if (!v418)
    {
      goto LABEL_620;
    }
    if (ppos.x > 0.0 && v420 < (f32)get_width(0))
    {
      v832 = ppos.x <= v841 || ppos.x >= v831;
      if (ppos.x >= v844)
      {
        v842 = ppos.x <= v833;
        if (ppos.x <= v834)
        {
          v845 = 0;
          v835 = 1;
          goto LABEL_621;
        }
      }
      else
      {
        v842 = 0;
      }
      v835 = 0;
      v845 = 0;
LABEL_621:
      v422 = 0;
      if (v283 < 500.0 && v283 <= (f32)(v284 + 300.0))
      {
        v423 = v856;
        v424 = v865;
        if (v853->MoveU_Cnt < 5)
        {
LABEL_631:
          if (v884)
            goto LABEL_635;
          if (wk->encountno == 60)
          {
LABEL_635:
            v422 = 0;
            v286 = 0;
            v285 = 0;
            v847 = 0;
            v842 = 0;
            v845 = 0;
            v832 = 0;
            gAuto_DirSpd = 0.0;
            if (!v867 && !v889)
            {
LABEL_643:
              if (v870 || v869 || v868 || v879)
              {
                gAuto_ManualKaiten_Cnt = 0;
                *(u64 *)&gAuto_Status = 18;
              }
              if (v886)
              {
                if (gAuto_Status != 21)
                {
                  gAuto_ManualKaiten_Cnt = 0;
                  *(u64 *)&gAuto_Status = 20;
                }
              }
              if (v880 || v881)
              {
                gAuto_ManualKaiten_Cnt = 0;
                *(u64 *)&gAuto_Status = 22;
LABEL_658:
                v438 = gAuto_Status;
                if (v438 > 0x16)
                {
LABEL_667:
                  v440 = 0;
                  UnitFromDevilID = v852;
                  goto LABEL_1349;
                }
                goto LABEL_662;
              }
              {
                goto LABEL_658;
              }
              v438 = gAuto_Status;
LABEL_662:
              v439 = v862 || v886;
              switch (v438)
              {
                case 0u:
                  if (sBtlPlayerCheckRSpirit())
                  {
                    pBaseUnit = v853;
                    goto LABEL_667;
                  }
                  if (v878 || v874)
                  {
                    UnitFromDevilID = v852;
                    pBaseUnit = v853;
                    v442 = -1.0;
                    v440 = 0;
                    v644 = 19;
                    p_gAuto_Status = &gAuto_Status;
LABEL_1418:
                    *p_gAuto_Status = v644;
LABEL_1491:
                    v782 = gAuto_Status;
                    if (v782 == 11)
                    {
                      goto LABEL_340;
                    }
                    if (v782)
                      goto LABEL_340;
                    if (gZoomStatus > 11)
                    {
                      if ((u32)gZoomStatus > 0x14)
                      {
                        if (gZoomStatus != 21)
                        {
                          if (gZoomStatus != 25)
                            goto LABEL_340;
                          v784 = gZoomLenNml + 0.005;
                          gZoomLenNml = v784;
                          if (v784 < 0.0)
                          {
                            if ((v858 & 1) != 0)
                              goto LABEL_340;
                            goto LABEL_1587;
                          }
LABEL_1575:
                          gZoomLenNml = 0.0;
                          goto LABEL_1589;
                        }
                        gZoomCnt_local = gZoomCnt + 1;
                        gZoomCnt = gZoomCnt_local;
                        if ((v861 & 1) != 0)
                        {
                          if (!v788)
                            goto LABEL_1588;
                          goto LABEL_1589;
                        }
                        if (v788)
                          goto LABEL_1586;
                        goto LABEL_1584;
                      }
                      if (gZoomStatus != 15)
                      {
                        if (gZoomStatus != 20)
                          goto LABEL_340;
                        v786 = gZoomLenNml + -0.005;
                        gZoomLenNml = v786;
                        if (v786 >= v442)
                        {
                          if ((v861 & 1) != 0)
                            goto LABEL_340;
                        }
                        else
                        {
                          gZoomLenNml = -1.0;
                        }
                        *(u64 *)&gZoomStatus = 21;
                        goto LABEL_340;
                      }
                      if (v872)
                        v789 = -0.02;
                      else
                        v789 = -0.005;
                      gZoomLenNml = gZoomLenNml + v789;
                      if (gZoomLenNml <= 0.0)
                        goto LABEL_1575;
                      if (((v872 | (u8)v864) & 1) != 0)
                        goto LABEL_340;
                      goto LABEL_1587;
                    }
                    if (gZoomStatus)
                    {
                      if (gZoomStatus == 10)
                      {
                        if (!v872)
                        {
                          v790 = gZoomLenNml + 0.005;
                          gZoomLenNml = v790;
                          if (v790 <= 1.0)
                          {
                            if ((v235 & 1) != 0)
                              goto LABEL_340;
                          }
                          else
                          {
                            gZoomLenNml = 1.0;
                          }
                          *(u64 *)&gZoomStatus = 11;
LABEL_340:
                          *(f32 *)&v213 = 0.0;
                          v887 = 0;
                          if (v891)
                            goto LABEL_452;
                          goto LABEL_561;
                        }
                      }
                      else
                      {
                        if (gZoomStatus != 11)
                          goto LABEL_340;
                        if (!v872)
                        {
                          if (v785)
                          {
                            ++gZoomCnt;
                            if ((v235 & 1) != 0)
                              goto LABEL_1512;
                          }
                          else
                          {
                            ++gZoomCnt;
                            if ((v235 & 1) != 0)
                            {
LABEL_1512:
                              gZoomStatus = 0;
                              gZoomCnt = 0;
                              goto LABEL_1585;
                            }
                          }
LABEL_1585:
                          gZoomCnt_local = gZoomCnt;
LABEL_1586:
                          if (gZoomCnt_local < 31)
                            goto LABEL_340;
LABEL_1587:
LABEL_1588:
LABEL_1589:
                          gZoomStatus = 0;
                          gZoomCnt = 0;
                          goto LABEL_340;
LABEL_1584:
                          goto LABEL_1585;
                        }
                      }
                      if (!v785)
                        goto LABEL_1536;
                    }
                    else
                    {
                      ++gZoomCnt;
                      if (!v440)
                        goto LABEL_340;
                      if ((v858 & 1) != 0)
                      {
                        if (gZoomLenNml < 0.0)
                        {
                          *(u64 *)&gZoomStatus = 25;
                          goto LABEL_340;
                        }
                      }
                      if (((v872 | (u8)v864) & 1) == 0)
                        goto LABEL_1569;
                      if (gZoomLenNml <= 0.0)
                      {
LABEL_1569:
                        if ((v861 & 1) != 0)
                        {
                          *(u64 *)&gZoomStatus = 20;
                        }
                        else if ((v235 & 1) != 0)
                        {
                          *(u64 *)&gZoomStatus = 10;
                        }
                        goto LABEL_340;
                      }
LABEL_1536:
                    }
                    *(u64 *)&gZoomStatus = 15;
                    goto LABEL_340;
                  }
                  if (gAuto_ManualKaiten_Input)
                  {
                    UnitFromDevilID = v852;
                    pBaseUnit = v853;
                    v440 = 0;
                    *(u64 *)&gAuto_Status = 11;
LABEL_1349:
                    v442 = -1.0;
                    goto LABEL_1491;
                  }
                  if (sBtlChkEvent())
                  {
                    v442 = -1.0;
                    UnitFromDevilID = v852;
                    pBaseUnit = v853;
                    v440 = 0;
                    *(u64 *)&gAuto_Status = 9;
                    goto LABEL_1491;
                  }
                  if (v840)
                  {
                    v774 = 10;
LABEL_1635:
                    v440 = 0;
                    *(u64 *)&gAuto_Status = v774;
LABEL_1636:
                    v57 = vResTgt;
                    UnitFromDevilID = v852;
                    pBaseUnit = v853;
                    goto LABEL_1349;
                  }
                  if (!v34)
                  {
                    v774 = 8;
                    goto LABEL_1635;
                  }
                  if (!v439 && v838)
                  {
                    v774 = 16;
                    goto LABEL_1635;
                  }
                  if (v839)
                  {
                    v774 = 15;
                    goto LABEL_1635;
                  }
                  if (v837 == 27)
                  {
                    v774 = 13;
                    goto LABEL_1635;
                  }
                  if (v836 == 15)
                  {
                    v774 = 14;
                    goto LABEL_1635;
                  }
                  if (v845)
                  {
                    if (gKaitenHiSpd_local)
                    {
                      v440 = 0;
                      v811 = 5;
LABEL_1650:
                      *(u64 *)&gAuto_Status = v811;
                      gAuto_DirSpd = 1.0;
                      goto LABEL_1636;
                    }
                    v440 = 0;
                    v815 = 4;
                    goto LABEL_1662;
                  }
                  if (v832)
                  {
                    v440 = 0;
                    gAuto_SideNormal = v238;
                    *(u64 *)&gAuto_Status = 3;
                    gAuto_DirSpd = 0.5;
                    goto LABEL_1636;
                  }
                  if (v422)
                  {
                    v440 = 0;
                    v815 = 7;
                    goto LABEL_1662;
                  }
                  if (v847)
                  {
                    if (gKaitenHiSpd_local)
                    {
                      v440 = 0;
                      v811 = 2;
                      goto LABEL_1650;
                    }
                    v440 = 0;
                    v815 = 1;
LABEL_1662:
                    *(u64 *)&gAuto_Status = v815;
                    gAuto_DirSpd = 0.5;
                    goto LABEL_1636;
                  }
                  if (!v842 && v285)
                  {
                    v440 = 0;
                    v815 = 6;
                    goto LABEL_1662;
                  }
                  if (v286)
                  {
                    v823 = gAuto_DirSpd;
                    if (v823 <= 0.1)
                    {
                      gAuto_DirSpd = 0.05;
                    }
                    else
                    {
                      if (!v822)
                      {
                        v823 = gAuto_DirSpd;
                      }
                      gAuto_DirSpd = v823 * 0.9;
                    }
                    v826 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v856, FromZ);
                    v828 = *p_followUpAngle;
                    v827 = sBtlGetDir_Hokan(v828, v826, gAuto_DirSpd);
                    *p_followUpAngle = sBtlGet360(v827);
                  }
                  else
                  {
                    v825 = gAuto_DirSpd;
                    if (v825 <= 0.1)
                      goto LABEL_1703;
                    v825 = gAuto_DirSpd;
                    gAuto_DirSpd = v825 * 0.9;
                    v826 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v856, FromZ);
                    v827 = sBtlGetDir_Hokan(*p_followUpAngle, v826, gAuto_DirSpd);
                    *p_followUpAngle = sBtlGet360(v827);
                  }
                  if (sBtlGetAtoB_LR_ABS(v827, v826) >= 20.0)
                  {
                    if (gAuto_DirSpd > 0.05)
                    {
                      v440 = 0;
                      goto LABEL_1636;
                    }
                  }
LABEL_1703:
                  v440 = 1;
                  goto LABEL_1636;
                case 1u:
                  if ((v842 & (v847 ^ 1)) == 1)
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    ++gAuto_DoneCnt;
                  }
                  else
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    gAuto_DoneCnt = 0;
                  }
                  pBaseUnit = v853;
                  if ((v835 & (v847 ^ 1)) != 1)
                    goto LABEL_1271;
                  if (v842)
                  {
                    v503 = gAuto_DirSpd;
                    if (v503 > 0.1)
                    {
                      v503 = gAuto_DirSpd;
                      v504 = v503 * 0.95;
LABEL_1270:
                      gAuto_DirSpd = v504;
                    }
                  }
                  else
                  {
                    v699 = gAuto_DirSpd;
                    if (v699 > 0.5)
                    {
                      v699 = gAuto_DirSpd;
                      v504 = v699 + -0.2;
                      goto LABEL_1270;
                    }
                  }
LABEL_1271:
                  if (gAuto_DoneCnt < 4)
                  {
                    if (!v847)
                      goto LABEL_1375;
                    goto LABEL_1369;
                  }
                  if (gAuto_DirSpd > 0.5)
                  {
                    gAuto_DirSpd = 0.5;
                    gAuto_Status = 0;
                    if (!v847)
                      goto LABEL_1375;
LABEL_1369:
                    v745 = gAuto_DirSpd + 0.1;
                    gAuto_DirSpd = v745;
                    if (v745 > 2.0)
                    {
                      gAuto_DirSpd = 2.0;
                    }
LABEL_1375:
                    v746 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v423, FromZ);
                    v748 = v746;
                    v749 = *p_followUpAngle;
                    v750 = sBtlGetDir_Hokan(v749, v748, gAuto_DirSpd);
                    v751 = sBtlGet360(v750);
                    *p_followUpAngle = v751;
                    if (gAuto_ManualKaiten_Cnt >= 1)
                    {
                      *(u64 *)&gAuto_Status = 11;
                    }
                    if (gKaitenHiSpd_local)
                    {
                      if (gAuto_Status == 1)
                      {
                        v440 = 0;
                        gAuto_Status = 2;
                        goto LABEL_1491;
                      }
                    }
                    goto LABEL_1488;
LABEL_1368:
                    gAuto_Status = 0;
                    if (!v847)
                      goto LABEL_1375;
                    goto LABEL_1369;
                  }
                  goto LABEL_1368;
                case 2u:
                  if ((v842 & (v847 ^ 1)) == 1)
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    ++gAuto_DoneCnt;
                  }
                  else
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    gAuto_DoneCnt = 0;
                  }
                  pBaseUnit = v853;
                  if ((v835 & (v847 ^ 1)) != 1)
                    goto LABEL_1290;
                  if (v842)
                  {
                    v507 = gAuto_DirSpd;
                    if (v507 > 0.1)
                    {
                      v507 = gAuto_DirSpd;
                      v508 = v507 * 0.95;
LABEL_1289:
                      gAuto_DirSpd = v508;
                    }
                  }
                  else
                  {
                    v701 = gAuto_DirSpd;
                    if (v701 > 0.5)
                    {
                      v701 = gAuto_DirSpd;
                      v508 = v701 + -0.2;
                      goto LABEL_1289;
                    }
                  }
LABEL_1290:
                  if (gAuto_DoneCnt < 4)
                  {
                    if (!v847)
                      goto LABEL_1400;
                    goto LABEL_1394;
                  }
                  if (gAuto_DirSpd > 0.5)
                  {
                    gAuto_DirSpd = 0.5;
                    gAuto_Status = 0;
                    if (!v847)
                      goto LABEL_1400;
LABEL_1394:
                    v756 = gAuto_DirSpd + 0.5;
                    gAuto_DirSpd = v756;
                    if (v756 > 5.0)
                    {
                      gAuto_DirSpd = 5.0;
                    }
LABEL_1400:
                    v757 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v423, FromZ);
                    v759 = v757;
                    v760 = *p_followUpAngle;
                    v761 = sBtlGetDir_Hokan(v760, v759, gAuto_DirSpd);
                    v762 = sBtlGet360(v761);
                    *p_followUpAngle = v762;
                    if (gAuto_ManualKaiten_Cnt >= 1)
                    {
LABEL_1405:
                      *(u64 *)&gAuto_Status = 11;
                      v440 = 0;
                      goto LABEL_1491;
                    }
LABEL_1488:
                    v440 = 0;
                    goto LABEL_1489;
LABEL_1393:
                    gAuto_Status = 0;
                    if (!v847)
                      goto LABEL_1400;
                    goto LABEL_1394;
                  }
                  goto LABEL_1393;
                case 3u:
                  if (!v842)
                  {
                    UnitFromDevilID = v852;
                    v445 = v835;
                    gAuto_DoneCnt = 0;
                    pBaseUnit = v853;
                    v446 = p_followUpAngle;
                    if ((v835 & 1) != 0)
                    {
                      v510 = gAuto_DirSpd;
                      if (v510 > 0.5)
                      {
                        v510 = gAuto_DirSpd;
                        v511 = v510 + -0.2;
                        goto LABEL_1118;
                      }
                    }
LABEL_1119:
                    if (gAuto_DoneCnt >= 4)
                    {
                      gAuto_Status = 0;
                    }
                    else if (v845)
                    {
                      *(u64 *)&gAuto_Status = 4;
                    }
                    if ((v445 & 1) == 0)
                    {
                      ABS = sBtlGetABS(gAuto_SideNormal);
                      if ((f32)(ABS + 0.01) < sBtlGetABS(v238))
                      {
                        gAuto_SideNormal = v238;
                        v658 = gAuto_DirSpd + 0.12;
                        gAuto_DirSpd = v658;
                        if (v658 > 2.0)
                        {
                          gAuto_DirSpd = 2.0;
                        }
                      }
                    }
                    v659 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v423, FromZ);
                    v661 = v659;
                    v442 = -1.0;
                    v662 = *v446;
LABEL_1145:
                    v663 = sBtlGetDir_Hokan(v662, v661, gAuto_DirSpd);
                    v664 = sBtlGet360(v663);
                    *v446 = v664;
                    if (gAuto_ManualKaiten_Cnt >= 1)
                      goto LABEL_1405;
                    goto LABEL_1488;
                  }
                  UnitFromDevilID = v852;
                  v445 = v835;
                  pBaseUnit = v853;
                  v446 = p_followUpAngle;
                  ++gAuto_DoneCnt;
                  if (v853->MoveL_Cnt >= 9)
                  {
                    gAuto_DoneCnt = 0;
                    if (v853->MoveR_Cnt < 9)
                    {
LABEL_681:
                      if ((v835 & 1) == 0)
                        goto LABEL_1119;
LABEL_1112:
                      v652 = gAuto_DirSpd;
                      if (v652 > 0.1)
                      {
                        v652 = gAuto_DirSpd;
                        v511 = v652 * 0.95;
LABEL_1118:
                        gAuto_DirSpd = v511;
                        goto LABEL_1119;
                      }
                      goto LABEL_1119;
                    }
                  }
                  else if (v853->MoveR_Cnt < 9)
                  {
                    goto LABEL_681;
                  }
                  gAuto_DoneCnt = 0;
                  if ((v835 & 1) == 0)
                    goto LABEL_1119;
                  goto LABEL_1112;
                case 4u:
                  if (!v842)
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    gAuto_DoneCnt = 0;
                    pBaseUnit = v853;
                    v448 = p_followUpAngle;
                    if ((((u8)v845 | (u8)v835 ^ 1) & 1) == 0)
                    {
                      v513 = gAuto_DirSpd;
                      if (v513 > 0.5)
                      {
                        v513 = gAuto_DirSpd;
                        v514 = v513 + -0.2;
                        goto LABEL_1159;
                      }
                    }
LABEL_1160:
                    if (gAuto_DoneCnt < 4)
                    {
                      if (!v845)
                      {
LABEL_1174:
                        v671 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v423, FromZ);
                        v673 = v671;
                        v674 = *v448;
                        v675 = sBtlGetDir_Hokan(v674, v673, gAuto_DirSpd);
                        v676 = sBtlGet360(v675);
                        *v448 = v676;
                        if (gAuto_ManualKaiten_Cnt >= 1)
                        {
                          *(u64 *)&gAuto_Status = 11;
                        }
                        v680 = !gKaitenHiSpd_local;
                        if (gAuto_Status != 4)
                          v680 = 1;
                        if ((v680 & 1) != 0)
                          goto LABEL_1488;
                        v440 = 0;
                        gAuto_Status = 5;
                        goto LABEL_1491;
LABEL_1490:
                        goto LABEL_1491;
                      }
LABEL_1168:
                      v670 = gAuto_DirSpd + 0.3;
                      gAuto_DirSpd = v670;
                      if (v670 > 3.0)
                      {
                        gAuto_DirSpd = 3.0;
                      }
                      goto LABEL_1174;
                    }
                    gAuto_Status = 0;
                    if (!v845)
                      goto LABEL_1174;
                    goto LABEL_1168;
                  }
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  pBaseUnit = v853;
                  v448 = p_followUpAngle;
                  ++gAuto_DoneCnt;
                  if (v853->MoveL_Cnt >= 9)
                  {
                    gAuto_DoneCnt = 0;
                    if (v853->MoveR_Cnt < 9)
                    {
LABEL_688:
                      if (((v845 | v835 ^ 1) & 1) != 0)
                        goto LABEL_1160;
LABEL_1153:
                      v667 = gAuto_DirSpd;
                      if (v667 > 0.1)
                      {
                        v667 = gAuto_DirSpd;
                        v514 = v667 * 0.95;
LABEL_1159:
                        gAuto_DirSpd = v514;
                        goto LABEL_1160;
                      }
                      goto LABEL_1160;
                    }
                  }
                  else if (v853->MoveR_Cnt < 9)
                  {
                    goto LABEL_688;
                  }
                  gAuto_DoneCnt = 0;
                  if (((v845 | v835 ^ 1) & 1) != 0)
                    goto LABEL_1160;
                  goto LABEL_1153;
                case 5u:
                  if (!v842)
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    gAuto_DoneCnt = 0;
                    pBaseUnit = v853;
                    v446 = p_followUpAngle;
                    if ((((u8)v845 | (u8)v835 ^ 1) & 1) == 0)
                    {
                      v516 = gAuto_DirSpd;
                      if (v516 > 0.5)
                      {
                        v516 = gAuto_DirSpd;
                        v517 = v516 + -0.2;
                        goto LABEL_1203;
                      }
                    }
LABEL_1204:
                    if (gAuto_DoneCnt < 4)
                    {
                      if (!v845)
                        goto LABEL_1218;
                      goto LABEL_1212;
                    }
                    gAuto_Status = 0;
                    if (!v845)
                    {
LABEL_1218:
                      v685 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v423, FromZ);
                      v661 = v685;
                      v662 = *v446;
                      goto LABEL_1145;
                    }
LABEL_1212:
                    v684 = gAuto_DirSpd + 0.8;
                    gAuto_DirSpd = v684;
                    if (v684 > 5.0)
                    {
                      gAuto_DirSpd = 5.0;
                    }
                    goto LABEL_1218;
                  }
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  pBaseUnit = v853;
                  v446 = p_followUpAngle;
                  ++gAuto_DoneCnt;
                  if (v853->MoveL_Cnt >= 9)
                  {
                    gAuto_DoneCnt = 0;
                    if (v853->MoveR_Cnt < 9)
                    {
LABEL_695:
                      if (((v845 | v835 ^ 1) & 1) != 0)
                        goto LABEL_1204;
LABEL_1197:
                      v681 = gAuto_DirSpd;
                      if (v681 > 0.1)
                      {
                        v681 = gAuto_DirSpd;
                        v517 = v681 * 0.95;
LABEL_1203:
                        gAuto_DirSpd = v517;
                        goto LABEL_1204;
                      }
                      goto LABEL_1204;
                    }
                  }
                  else if (v853->MoveR_Cnt < 9)
                  {
                    goto LABEL_695;
                  }
                  gAuto_DoneCnt = 0;
                  if (((v845 | v835 ^ 1) & 1) != 0)
                    goto LABEL_1204;
                  goto LABEL_1197;
                case 6u:
                  if (!v842)
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    gAuto_DoneCnt = 0;
                    pBaseUnit = v853;
                    v451 = p_followUpAngle;
                    if ((v835 & 1) != 0)
                    {
                      v519 = gAuto_DirSpd;
                      if (v519 > 0.5)
                      {
                        v519 = gAuto_DirSpd;
                        v520 = v519 + -0.2;
                        goto LABEL_1234;
                      }
                    }
LABEL_1235:
                    if (gAuto_DoneCnt < 4)
                    {
                      goto LABEL_1238;
                    }
                    gAuto_Status = 0;
LABEL_1238:
                    v689 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v423, FromZ);
                    v691 = v689;
                    v692 = *v451;
                    v693 = sBtlGetDir_Hokan(v692, v691, gAuto_DirSpd);
                    v694 = sBtlGet360(v693);
                    *v451 = v694;
                    if (gAuto_ManualKaiten_Cnt >= 1)
                    {
                      *(u64 *)&gAuto_Status = 11;
                    }
                    if (gAuto_Status != 6)
                      goto LABEL_1488;
                    if (v847)
                    {
                      if (gKaitenHiSpd_local)
                      {
                        v697 = gAuto_DirSpd;
                        *(u64 *)&gAuto_Status = 2;
                        if (v697 >= 1.0)
                          goto LABEL_1488;
                        goto LABEL_1484;
                      }
                      v763 = gAuto_DirSpd;
                      *(u64 *)&gAuto_Status = 1;
                      if (v763 >= 0.5)
                        goto LABEL_1488;
                    }
                    else
                    {
                      if (!v845)
                        goto LABEL_1488;
                      if (gKaitenHiSpd_local)
                      {
                        v714 = gAuto_DirSpd;
                        *(u64 *)&gAuto_Status = 5;
                        if (v714 >= 1.0)
                          goto LABEL_1488;
LABEL_1484:
LABEL_1486:
                        v440 = 0;
                        gAuto_DirSpd = 1.0;
                        goto LABEL_1491;
                      }
                      v771 = gAuto_DirSpd;
                      *(u64 *)&gAuto_Status = 4;
                      if (v771 >= 0.5)
                        goto LABEL_1488;
                    }
                    v440 = 0;
                    gAuto_DirSpd = 0.5;
                    goto LABEL_1491;
                  }
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  pBaseUnit = v853;
                  v451 = p_followUpAngle;
                  ++gAuto_DoneCnt;
                  if (v853->MoveL_Cnt >= 9)
                  {
                    gAuto_DoneCnt = 0;
                    if (v853->MoveR_Cnt < 9)
                    {
LABEL_702:
                      if ((v835 & 1) == 0)
                        goto LABEL_1235;
LABEL_1228:
                      v686 = gAuto_DirSpd;
                      if (v686 > 0.1)
                      {
                        v686 = gAuto_DirSpd;
                        v520 = v686 * 0.95;
LABEL_1234:
                        gAuto_DirSpd = v520;
                        goto LABEL_1235;
                      }
                      goto LABEL_1235;
                    }
                  }
                  else if (v853->MoveR_Cnt < 9)
                  {
                    goto LABEL_702;
                  }
                  gAuto_DoneCnt = 0;
                  if ((v835 & 1) == 0)
                    goto LABEL_1235;
                  goto LABEL_1228;
                case 7u:
                  pBaseUnit = v853;
                  if (v853->MoveU_Cnt)
                  {
                    v453 = v852;
                    gAuto_DoneCnt = 0;
                  }
                  else
                  {
                    v453 = v852;
                    ++gAuto_DoneCnt;
                  }
                  if (gAuto_DoneCnt < 4)
                  {
                    if (v845)
                    {
                      *(u64 *)&gAuto_Status = 4;
                      gAuto_DirSpd = 0.5;
                    }
LABEL_1336:
                    v715 = targetPos.x;
                    v716 = targetPos.z;
                    v717 = v453->pos.x;
                    v718 = v453->pos.z;
                    v719 = sBtlGetPosToDir(v715, v716, v717, v718);
                    v720 = sBtlGet360(v719 + -90.0);
                    v721 = sBtlGet360(v719 + 90.0);
                    sBtlGetMoveXZ(targetPos.x, targetPos.z, v720, 600.0, (f32 *)&v904 + 1, &v904);
                    sBtlGetMoveXZ(targetPos.x, targetPos.z, v721, 600.0, (f32 *)&v903 + 1, &v903);
                    v722 = sBtlGetLenXZ(cameraPos.x, cameraPos.z, *((f32 *)&v904 + 1), *(f32 *)&v904);
                    v723 = sBtlGetLenXZ(cameraPos.x, cameraPos.z, *((f32 *)&v903 + 1), *(f32 *)&v903);
                    _NF = v722 < v723;
                    if (v722 >= v723)
                      v725 = (f32 *)&v903 + 1;
                    else
                      v725 = (f32 *)&v904 + 1;
                    v726 = targetPos.x;
                    v727 = targetPos.z;
                    v728 = *v725;
                    if (_NF)
                      v729 = &v904;
                    else
                      v729 = &v903;
                    v730 = *v729;
                    v731 = sBtlGetPosToDir(v726, v727, v728, v730);
                    v732 = sBtlGetPosToDir(cameraPos.x, cameraPos.z, targetPos.x, targetPos.z);
                    v733 = sBtlGetPosToDir(v853->pos.x, v853->pos.z, targetPos.x, targetPos.z);
                    v734 = sBtlGetPosToDir(cameraPos.x, cameraPos.z, v728, v730);
                    AtoB_LR = sBtlGetAtoB_LR(v732, v733);
                    v736 = sBtlGetAtoB_LR(v732, v734);
                    UnitFromDevilID = v852;
                    if (AtoB_LR > 0.0 && v736 > 0.0)
                    {
                      v440 = 0;
                      goto LABEL_1349;
                    }
                    v442 = -1.0;
                    if (AtoB_LR < 0.0 && v736 < 0.0)
                      goto LABEL_1488;
                    v739 = gAuto_DirSpd;
                    if (v739 < 30.0)
                    {
                      v739 = gAuto_DirSpd;
                      gAuto_DirSpd = v739 + 0.2;
                      v740 = *p_followUpAngle;
                      v742 = gAuto_DirSpd;
                      goto LABEL_1430;
LABEL_1429:
                      v742 = gAuto_DirSpd;
LABEL_1430:
                      v766 = sBtlGetDir_Hokan(v740, v731, v742);
                      v440 = 0;
                      *p_followUpAngle = sBtlGet360(v766);
                      goto LABEL_1491;
                    }
                    v740 = *p_followUpAngle;
                    goto LABEL_1429;
                  }
                  if (gAuto_DirSpd > 0.5)
                  {
                    gAuto_DirSpd = 0.5;
LABEL_1335:
                    gAuto_Status = 0;
                    goto LABEL_1336;
                  }
                  goto LABEL_1335;
                case 8u:
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  if (v34 < 1)
                    goto LABEL_727;
                  goto LABEL_721;
                case 9u:
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  if (sBtlChkEvent())
                  {
                    v440 = 0;
                    goto LABEL_961;
                  }
                  v440 = 0;
                  gAuto_Status = 0;
                  pBaseUnit = v853;
                  goto LABEL_1491;
                case 0xAu:
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  if ((v840 & 1) != 0)
                    goto LABEL_727;
                  goto LABEL_721;
                case 0xBu:
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  if (gAuto_ManualKaiten_Input)
                    goto LABEL_1061;
                  if ((gKaitenHiSpd_local & v845) == 1)
                  {
                    v645 = gAuto_DirSpd;
                    pBaseUnit = v853;
                    *(u64 *)&gAuto_Status = 5;
                    if (v645 < 1.0)
                      goto LABEL_1484;
                  }
                  else
                  {
                    if ((gKaitenHiSpd_local & v847) == 1)
                    {
                      goto LABEL_870;
                    }
LABEL_1061:
                    if (gAuto_ManualKaiten_Cnt < 1)
                      goto LABEL_1072;
                    if ((((v839 || v838) | v840) & 1) == 0)
                    {
                      gAuto_ManualKaiten_Cnt = gAuto_ManualKaiten_Cnt - 1;
                    }
                    if (v862 || v886)
                    {
                      pBaseUnit = v853;
                      gAuto_ManualKaiten_Cnt = 0;
                    }
                    else
                    {
LABEL_1072:
                      pBaseUnit = v853;
                    }
                    if (gAuto_ManualKaiten_Cnt <= 0)
                    {
                      *(u64 *)&gAuto_Status = 12;
                      goto LABEL_1486;
                    }
                  }
                  goto LABEL_1488;
                case 0xCu:
                  v454 = wka;
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  if (gAuto_ManualKaiten_Input)
                  {
                    pBaseUnit = v853;
                    v440 = 0;
                    p_gAuto_Status = &gAuto_Status;
                    v644 = 11;
                    goto LABEL_1418;
                  }
                  pBaseUnit = v853;
                  v646 = p_followUpAngle;
                  if ((gKaitenHiSpd_local & v845) == 1)
                  {
                    v770 = gAuto_DirSpd;
                    *(u64 *)&gAuto_Status = 5;
                    if (v770 >= 1.0)
                      goto LABEL_1488;
                    goto LABEL_1484;
                  }
                  if ((gKaitenHiSpd_local & v847) == 1)
                  {
                    v780 = gAuto_DirSpd;
                    *(u64 *)&gAuto_Status = 2;
                    if (v780 >= 1.0)
                      goto LABEL_1488;
                    goto LABEL_1484;
                  }
                  if (v842)
                  {
                    ++gAuto_DoneCnt;
                    if (v454->followUpAngle.y > 0.1)
                    {
                      gAuto_DoneCnt = 0;
                      UnitFromDevilID = v852;
                      pBaseUnit = v853;
                      v646 = p_followUpAngle;
                      v454 = wka;
                      v423 = v856;
                    }
                    if (((v845 | v835 ^ 1) & 1) == 0)
                    {
                      UnitFromDevilID = v852;
                      pBaseUnit = v853;
                      v768 = gAuto_DirSpd;
                      v646 = p_followUpAngle;
                      v454 = wka;
                      v423 = v856;
                      if (v768 > 0.1)
                      {
                        v768 = gAuto_DirSpd;
                        v769 = v768 * 0.95;
LABEL_1471:
                        v423 = v856;
                        gAuto_DirSpd = v769;
                        UnitFromDevilID = v852;
                        pBaseUnit = v853;
                        v646 = p_followUpAngle;
                        v454 = wka;
                      }
                    }
                  }
                  else
                  {
                    gAuto_DoneCnt = 0;
                    if (((v845 | v835 ^ 1) & 1) == 0)
                    {
                      v775 = gAuto_DirSpd;
                      UnitFromDevilID = v852;
                      pBaseUnit = v853;
                      v646 = p_followUpAngle;
                      v454 = wka;
                      v423 = v856;
                      if (v775 > 0.5)
                      {
                        v775 = gAuto_DirSpd;
                        v769 = v775 + -0.2;
                        goto LABEL_1471;
                      }
                    }
                  }
                  if (v884)
                    goto LABEL_1476;
                  if (wk->encountno == 60)
                  {
LABEL_1476:
                    v777 = *v646;
                    v778 = sBtlGetAtoB_LR_ABS(v777, 180.0);
                    if (v778 < 5.0)
                    {
                      v454 = wka;
                      v57 = vResTgt;
                      UnitFromDevilID = v852;
                      pBaseUnit = v853;
                      ++gAuto_DoneCnt;
                      v646 = p_followUpAngle;
                      v423 = v856;
LABEL_1602:
                      if (gAuto_DoneCnt < 5)
                      {
                        goto LABEL_1605;
                      }
                      gAuto_Status = 0;
LABEL_1605:
                      v794 = sBtlGetPosToDir(*((f32 *)&v67 + 1), *(f32 *)&v67, v423, FromZ);
                      if (v884)
                        goto LABEL_1608;
                      v795 = v794;
                      if (wk->encountno == 60)
                        goto LABEL_1608;
                      goto LABEL_9018;
                      if (wk->encountno == 60)
                      {
LABEL_1608:
                        v795 = 180.0;
                        if (!v845)
                          goto LABEL_1623;
LABEL_1617:
                        v798 = gAuto_DirSpd + 0.2;
                        gAuto_DirSpd = v798;
                        if (v798 > 3.0)
                        {
                          gAuto_DirSpd = 3.0;
                          v454 = wka;
                          v57 = vResTgt;
                          UnitFromDevilID = v852;
                          pBaseUnit = v853;
                          v646 = p_followUpAngle;
                        }
LABEL_1623:
                        v799 = *v646;
                        v800 = gAuto_DirSpd;
                        v801 = sBtlGetDir_Hokan(v799, v795, v800);
                        v454->followUpAngle.x = sBtlGet360(v801);
                        v802 = sBtlGetDir_Hokan(v454->followUpAngle.y, 0.0, 1.0);
                        v803 = v454;
                        v440 = 0;
                        v803->followUpAngle.y = v802;
                        goto LABEL_1491;
                      }
LABEL_9018:
                      if (!v845)
                        goto LABEL_1623;
                      goto LABEL_1617;
                    }
                  }
                  else
                  {
                  }
                  v57 = vResTgt;
                  goto LABEL_1602;
                case 0xDu:
                  v442 = -1.0;
                  UnitFromDevilID = v852;
                  if (v837 == 27)
                    goto LABEL_727;
LABEL_721:
                  v440 = 0;
                  goto LABEL_960;
                case 0xEu:
                  UnitFromDevilID = v852;
                  pBaseUnit = v853;
                  v442 = -1.0;
                  gHokan_OW_Use = 1;
                  gHokan_OW_Param = 0.2;
                  if (v836 == 15)
                    goto LABEL_1488;
                  goto LABEL_1088;
                case 0xFu:
                  UnitFromDevilID = v852;
                  v442 = -1.0;
                  if (v839)
                  {
LABEL_727:
                    pBaseUnit = v853;
                    v440 = 0;
                    goto LABEL_1491;
                  }
                  else
                  {
                    v440 = 0;
                    gAuto_Status = 0;
                    v522 = v439 | ~v838;
                    pBaseUnit = v853;
                    if ((v522 & 1) != 0)
                      goto LABEL_1489;
                    v440 = 0;
                    gAuto_Status = 16;
                    goto LABEL_1491;
                  }
                  goto LABEL_1490;
                case 0x10u:
                  if ((gKaitenHiSpd_local & v845) == 1)
                  {
                    v442 = -1.0;
                    UnitFromDevilID = v852;
                    v456 = gAuto_DirSpd;
                    pBaseUnit = v853;
                    *(u64 *)&gAuto_Status = 5;
                    if (v456 >= 1.0)
                      goto LABEL_1488;
                    goto LABEL_1484;
                  }
                  v442 = -1.0;
                  UnitFromDevilID = v852;
                  if ((gKaitenHiSpd_local & v847) != 1)
                  {
                    if (v862 || v886)
                    {
                      pBaseUnit = v853;
                      v440 = 0;
                      gAuto_Status = 0;
                      goto LABEL_1491;
                    }
                    else if (v838)
                    {
                      pBaseUnit = v853;
                      v440 = 0;
                      goto LABEL_1491;
                    }
                    else
                    {
                      pBaseUnit = v853;
LABEL_1088:
                      v440 = 0;
                      gAuto_Status = 0;
                      goto LABEL_1491;
                    }
                    goto LABEL_1490;
                  }
LABEL_870:
                  v523 = gAuto_DirSpd;
                  pBaseUnit = v853;
                  *(u64 *)&gAuto_Status = 2;
                  if (v523 >= 1.0)
                    goto LABEL_1488;
                  goto LABEL_1484;
                case 0x11u:
                  UnitFromDevilID = v852;
                  pBaseUnit = v853;
                  v458 = v853->pos.x;
                  v459 = v853->pos.z;
                  v460 = wk->scene->camera;
                  v461 = v460->CameraLockOnTargetPos.x;
                  v462 = v460->CameraLockOnTargetPos.z;
                  v463 = sBtlGetPosToDir(v461, v462, v458, v459);
                  if (sBtlGetAtoB_LR_ABS(*p_followUpAngle, v463) <= 0.5)
                  {
                    *p_followUpAngle = v463;
                    v442 = -1.0;
                    gAuto_DirSpd = 0.0;
                    gAuto_ManualKaiten_Cnt = 0;
                    gAuto_Status = 0;
LABEL_882:
                    ClrAction();
                    v440 = 0;
                    goto LABEL_1491;
                  }
                  v466 = gAuto_DirSpd + 0.2;
                  gAuto_DirSpd = v466;
                  if (v466 <= 2.0)
                  {
                    v467 = *p_followUpAngle;
                  }
                  else
                  {
                    gAuto_DirSpd = 2.0;
                    v467 = *p_followUpAngle;
                    v469 = gAuto_DirSpd;
LABEL_877:
                    v527 = sBtlGetDir_Hokan(v467, v463, v469);
                    v440 = 0;
                    *p_followUpAngle = sBtlGet360(v527);
                    goto LABEL_1349;
                  }
                  v469 = gAuto_DirSpd;
                  goto LABEL_877;
                case 0x12u:
                  pBaseUnit = v853;
                  v471 = v853->pos.x;
                  v472 = v853->pos.z;
                  v473 = wk->scene->camera;
                  v474 = v473->CameraLockOnTargetPos.x;
                  v475 = v473->CameraLockOnTargetPos.z;
                  v476 = sBtlGetPosToDir(v474, v475, v471, v472);
                  if (sBtlGetAtoB_LR_ABS(*p_followUpAngle, v476) <= 0.5)
                  {
                    *p_followUpAngle = v476;
                    v442 = -1.0;
                    UnitFromDevilID = v852;
                    v440 = 0;
                    gAuto_DirSpd = 0.0;
                    gAuto_ManualKaiten_Cnt = 0;
                    gAuto_Status = 0;
                    if (v870 || v869 || v868 || v879)
                    {
                      SetCamDone();
                      goto LABEL_882;
                    }
LABEL_1489:
                    goto LABEL_1491;
                  }
                  v479 = gAuto_DirSpd + 0.4;
                  gAuto_DirSpd = v479;
                  if (v479 <= 3.0)
                  {
                    v480 = *p_followUpAngle;
                  }
                  else
                  {
                    gAuto_DirSpd = 3.0;
                    v480 = *p_followUpAngle;
                    v482 = gAuto_DirSpd;
LABEL_886:
                    v531 = sBtlGetDir_Hokan(v480, v476, v482);
                    *p_followUpAngle = sBtlGet360(v531);
                    UnitFromDevilID = v852;
                    v440 = 0;
                    goto LABEL_1349;
                  }
                  v482 = gAuto_DirSpd;
                  goto LABEL_886;
                case 0x13u:
                  v483 = p_followUpAngle;
                  v484 = *p_followUpAngle;
                  v485 = sBtlGetAtoB_LR_ABS(v484, 180.0);
                  v442 = -1.0;
                  if (v485 <= 0.5)
                  {
                    pBaseUnit = v853;
                    ++gAuto_DoneCnt;
                  }
                  else
                  {
                    pBaseUnit = v853;
                    gAuto_DoneCnt = 0;
                  }
                  if (gAuto_DoneCnt >= 31)
                  {
                    *p_followUpAngle = 180.0;
                    gAuto_DirSpd = 0.0;
                    gAuto_ManualKaiten_Cnt = 0;
                    gAuto_Status = 0;
                    if (v878 || v874)
                    {
                      if (v878)
                        v533 = 14;
                      else
                        v533 = 17;
                      SetAction(v533);
                    }
                  }
                  v534 = gAuto_DirSpd + 0.1;
                  gAuto_DirSpd = v534;
                  if (v534 <= 2.0)
                    goto LABEL_907;
                  v492 = 0x40000000;
                  goto LABEL_906;
                case 0x14u:
                  v483 = p_followUpAngle;
                  v488 = *p_followUpAngle;
                  v442 = -1.0;
                  if (sBtlGetAtoB_LR_ABS(v488, 180.0) <= 0.5)
                  {
                    *p_followUpAngle = 180.0;
                    UnitFromDevilID = v852;
                    pBaseUnit = v853;
                    v440 = 0;
                    gAuto_DirSpd = 0.0;
                    gAuto_ManualKaiten_Cnt = 0;
                    *(u64 *)&gBoss_AMATOBI_Z = 0x3F800000461C3C00LL;
                    *(u64 *)&gAuto_Status = 21;
                    goto LABEL_1491;
                  }
                  else
                  {
                    pBaseUnit = v853;
                    v491 = gAuto_DirSpd + 0.4;
                    gAuto_DirSpd = v491;
                    if (v491 > 3.0)
                    {
                      v492 = 1077936128;
LABEL_906:
                      LODWORD(gAuto_DirSpd) = v492;
                    }
LABEL_907:
                    v535 = *v483;
                    v536 = gAuto_DirSpd;
                    v537 = sBtlGetDir_Hokan(v535, 180.0, v536);
                    *v483 = sBtlGet360(v537);
                    UnitFromDevilID = v852;
                    v440 = 0;
                    goto LABEL_1491;
                  }
                  goto LABEL_1490;
                case 0x15u:
                  v493 = gAuto_DirSpd + 0.1;
                  gAuto_DirSpd = v493;
                  if (v493 <= 2.0)
                  {
                    pBaseUnit = v853;
                  }
                  else
                  {
                    pBaseUnit = v853;
                    gAuto_DirSpd = 2.0;
                  }
                  v540 = *p_followUpAngle;
                  v541 = gAuto_DirSpd;
                  v542 = sBtlGetDir_Hokan(v540, 180.0, v541);
                  *p_followUpAngle = sBtlGet360(v542);
                  v543 = -1400.0;
                  v544 = (f32)(v855 + pBaseUnit->pos.x) * 0.5;
                  v545 = (f32)(v424 + pBaseUnit->pos.z) * 0.5;
                  targetPos.x = v544;
                  cameraPos.x = v544;
                  targetPos.z = v545;
                  if (v544 < -1400.0 || (v543 = 1400.0, v544 > 1400.0))
                  {
                    cameraPos.x = v543;
                    targetPos.x = v543;
                  }
                  v546 = cameraPos.z;
                  if ((f32)(v424 + -700.0) <= cameraPos.z)
                  {
                    v546 = (f32)(cameraPos.z - (f32)(cameraPos.z - v424)) + -700.0;
                    cameraPos.z = v546;
                  }
                  v547 = 10;
                  while (1)
                  {
                    v548 = cameraPos.x;
                    v549 = sBtlGetPosToDir(v548, v546, v855, v424);
                    v550 = sBtlGetAtoB_LR_ABS(0.0, v549);
                    if (v550 <= 25.0)
                      break;
                    if (v550 > 50.0)
                    {
                      v546 = cameraPos.z + -300.0;
                      --v547;
                      cameraPos.z = cameraPos.z + -300.0;
                      if (!v547)
                        goto LABEL_939;
                      continue;
                    }
                    if (v550 > 40.0)
                      v546 = cameraPos.z + -150.0;
                    else
                      v546 = cameraPos.z + -50.0;
                    --v547;
                    cameraPos.z = v546;
                    if (!v547)
                      goto LABEL_939;
                  }
                  v546 = cameraPos.z;
LABEL_939:
                  v551 = 10;
                  while (1)
                  {
                    v552 = cameraPos.x;
                    v553 = pBaseUnit->pos.x;
                    v554 = pBaseUnit->pos.z;
                    v555 = sBtlGetPosToDir(v552, v546, v553, v554);
                    v556 = sBtlGetAtoB_LR_ABS(0.0, v555);
                    if (v556 <= 30.0)
                      break;
                    if (v556 <= 50.0)
                    {
                      if (v556 > 40.0)
                        v546 = cameraPos.z + -150.0;
                      else
                        v546 = cameraPos.z + -50.0;
                      --v551;
                      cameraPos.z = v546;
                      if (!v551)
                        goto LABEL_951;
                    }
                    else
                    {
                      v546 = cameraPos.z + -300.0;
                      --v551;
                      cameraPos.z = cameraPos.z + -300.0;
                      if (!v551)
                        goto LABEL_951;
                    }
                  }
                  v546 = cameraPos.z;
LABEL_951:
                  v57 = vResTgt;
                  UnitFromDevilID = v852;
                  if (v546 >= gBoss_AMATOBI_Z)
                  {
                    v561 = (f32)(cameraPos.z - gBoss_AMATOBI_Z) * 0.5;
                  }
                  else
                  {
                    v561 = (f32)(cameraPos.z - gBoss_AMATOBI_Z) * 0.9;
                  }
                  v630 = gBoss_AMATOBI_Z + v561;
                  gBoss_AMATOBI_Z = v630;
                  v632 = targetPos.x;
                  v633 = targetPos.y;
                  v634 = targetPos.z;
                  cameraPos.z = v630;
                  v635 = wka->targetpos.x;
                  v636 = wka->targetpos.y;
                  v637 = wka->targetpos.z;
                  LenXYZ = sBtlGetLenXYZ(v635, v636, v637, v632, v633, v634);
                  v639 = sBtlGetLenXYZ(wka->camerapos.x, wka->camerapos.y, wka->camerapos.z, cameraPos.x, cameraPos.y, cameraPos.z);
                  if (LenXYZ >= 10.0)
                  {
                    v442 = -1.0;
                  }
                  else
                  {
                    v442 = -1.0;
                    if (v639 < 10.0)
                    {
                      ++gAuto_DoneCnt;
                    }
                  }
                  v703.n64_u64[0] = *(u64 *)&wka->camerapos.x;
                  v704.n64_u64[0] = vdup_n_s32(0x3E4CCCCDu).n64_u64[0];
                  v705 = wka->camerapos.z;
                  v707 = wka->targetpos.z
                       + (f32)((f32)(targetPos.z - wka->targetpos.z) * 0.2);
                  *(float32x2_t *)&targetPos.x = vadd_f32(*(float32x2_t *)&wka->targetpos.x, vmul_f32(vsub_f32(*(float32x2_t *)&targetPos.x, *(float32x2_t *)&wka->targetpos.x), v704));
                  targetPos.z = v707;
                  *(float32x2_t *)&cameraPos.x = vadd_f32(v703, vmul_f32(vsub_f32(*(float32x2_t *)&cameraPos.x, v703), v704));
                  cameraPos.z = v705 + (f32)((f32)(cameraPos.z - v705) * 0.2);
                  if (gAuto_DoneCnt < 5)
                    goto LABEL_1488;
                  SetCamDone();
                  v440 = 0;
                  goto LABEL_1491;
                case 0x16u:
                  if (!v880 && !v881)
                  {
                    UnitFromDevilID = v852;
                    v442 = -1.0;
                    v440 = 0;
                    gAuto_DirSpd = 0.0;
LABEL_960:
                    gAuto_Status = 0;
LABEL_961:
                    pBaseUnit = v853;
                    goto LABEL_1491;
                  }
                  v495 = gAuto_DirSpd + 0.1;
                  pBaseUnit = v853;
                  gAuto_DirSpd = v495;
                  if (v495 <= 2.0)
                  {
                    v496 = *p_followUpAngle;
                  }
                  else
                  {
                    gAuto_DirSpd = 2.0;
                    v496 = *p_followUpAngle;
                    v498 = gAuto_DirSpd;
                    goto LABEL_965;
                  }
                  v498 = gAuto_DirSpd;
LABEL_965:
                  v563 = sBtlGetDir_Hokan(v496, 180.0, v498);
                  *p_followUpAngle = sBtlGet360(v563);
                  v564 = -1400.0;
                  v890 = targetPos.x;
                  v565 = cameraPos.x;
                  v566 = cameraPos.z;
                  v888 = targetPos.z;
                  v567 = (f32)(v855 + v853->pos.x) * 0.5;
                  v568 = v865 + v853->pos.z;
                  targetPos.x = v567;
                  cameraPos.x = v567;
                  targetPos.z = v568 * 0.5;
                  if (v567 < -1400.0 || (v564 = 1400.0, v567 > 1400.0))
                  {
                    v567 = v564;
                    cameraPos.x = v564;
                    targetPos.x = v564;
                  }
                  v569 = cameraPos.z;
                  if ((f32)(v865 + -700.0) <= cameraPos.z)
                  {
                    v569 = (f32)(cameraPos.z - (f32)(cameraPos.z - v865)) + -700.0;
                    cameraPos.z = v569;
                  }
                  v570 = sBtlGetPosToDir(v567, v569, v855, v865);
                  v571 = sBtlGetAtoB_LR_ABS(0.0, v570);
                  v572 = cameraPos.z;
                  if (v571 > 30.0)
                  {
                    v573 = v571 <= 40.0;
                    v574 = -50.0;
                    v575 = cameraPos.x;
                    if (!v573)
                      v574 = -100.0;
                    v577 = cameraPos.z + v574;
                    cameraPos.z = cameraPos.z + v574;
                    if (!v576)
                    v578 = sBtlGetPosToDir(v575, v577, v855, v865);
                    v579 = sBtlGetAtoB_LR_ABS(0.0, v578);
                    v572 = cameraPos.z;
                    if (v579 > 30.0)
                    {
                      v573 = v579 <= 40.0;
                      v580 = -50.0;
                      v581 = cameraPos.x;
                      if (!v573)
                        v580 = -100.0;
                      v583 = cameraPos.z + v580;
                      cameraPos.z = cameraPos.z + v580;
                      if (!v582)
                      v584 = sBtlGetPosToDir(v581, v583, v855, v865);
                      v585 = sBtlGetAtoB_LR_ABS(0.0, v584);
                      v572 = cameraPos.z;
                      if (v585 > 30.0)
                      {
                        v573 = v585 <= 40.0;
                        v586 = -50.0;
                        v587 = cameraPos.x;
                        if (!v573)
                          v586 = -100.0;
                        v589 = cameraPos.z + v586;
                        cameraPos.z = cameraPos.z + v586;
                        if (!v588)
                        v590 = sBtlGetPosToDir(v587, v589, v855, v865);
                        v591 = sBtlGetAtoB_LR_ABS(0.0, v590);
                        v572 = cameraPos.z;
                        if (v591 > 30.0)
                        {
                          v573 = v591 <= 40.0;
                          v592 = -50.0;
                          v593 = cameraPos.x;
                          if (!v573)
                            v592 = -100.0;
                          v595 = cameraPos.z + v592;
                          cameraPos.z = cameraPos.z + v592;
                          if (!v594)
                          v596 = sBtlGetPosToDir(v593, v595, v855, v865);
                          v597 = sBtlGetAtoB_LR_ABS(0.0, v596);
                          v572 = cameraPos.z;
                          if (v597 > 30.0)
                          {
                            v598 = cameraPos.x;
                            v573 = v597 <= 40.0;
                            v599 = -50.0;
                            if (!v573)
                              v599 = -100.0;
                            v600 = cameraPos.z + v599;
                            cameraPos.z = cameraPos.z + v599;
                            v601 = sBtlGetPosToDir(v598, v600, v855, v865);
                            v602 = sBtlGetAtoB_LR_ABS(0.0, v601);
                            v572 = cameraPos.z;
                            if (v602 > 30.0)
                            {
                              v603 = cameraPos.x;
                              v573 = v602 <= 40.0;
                              v604 = -50.0;
                              if (!v573)
                                v604 = -100.0;
                              v605 = cameraPos.z + v604;
                              cameraPos.z = cameraPos.z + v604;
                              v606 = sBtlGetPosToDir(v603, v605, v855, v865);
                              v607 = sBtlGetAtoB_LR_ABS(0.0, v606);
                              v572 = cameraPos.z;
                              if (v607 > 30.0)
                              {
                                v608 = cameraPos.x;
                                v573 = v607 <= 40.0;
                                v609 = -50.0;
                                if (!v573)
                                  v609 = -100.0;
                                v610 = cameraPos.z + v609;
                                cameraPos.z = cameraPos.z + v609;
                                v611 = sBtlGetPosToDir(v608, v610, v855, v865);
                                v612 = sBtlGetAtoB_LR_ABS(0.0, v611);
                                v572 = cameraPos.z;
                                if (v612 > 30.0)
                                {
                                  v613 = cameraPos.x;
                                  v573 = v612 <= 40.0;
                                  v614 = -50.0;
                                  if (!v573)
                                    v614 = -100.0;
                                  v615 = cameraPos.z + v614;
                                  cameraPos.z = cameraPos.z + v614;
                                  v616 = sBtlGetPosToDir(v613, v615, v855, v865);
                                  v617 = sBtlGetAtoB_LR_ABS(0.0, v616);
                                  v572 = cameraPos.z;
                                  if (v617 > 30.0)
                                  {
                                    v618 = cameraPos.x;
                                    v573 = v617 <= 40.0;
                                    v619 = -50.0;
                                    if (!v573)
                                      v619 = -100.0;
                                    v620 = cameraPos.z + v619;
                                    cameraPos.z = cameraPos.z + v619;
                                    v621 = sBtlGetPosToDir(v618, v620, v855, v865);
                                    v622 = sBtlGetAtoB_LR_ABS(0.0, v621);
                                    v572 = cameraPos.z;
                                    if (v622 > 30.0)
                                    {
                                      v573 = v622 <= 40.0;
                                      v623 = -50.0;
                                      if (!v573)
                                        v623 = -100.0;
                                      v572 = cameraPos.z + v623;
                                      cameraPos.z = cameraPos.z + v623;
                                    }
                                  }
                                }
                              }
                            }
                          }
                          pBaseUnit = v853;
                        }
                      }
                    }
                  }
                  v624 = 10;
                  while (1)
                  {
                    v625 = cameraPos.x;
                    v626 = pBaseUnit->pos.x;
                    v627 = pBaseUnit->pos.z;
                    v628 = sBtlGetPosToDir(v625, v572, v626, v627);
                    v629 = sBtlGetAtoB_LR_ABS(0.0, v628);
                    if (v629 <= 30.0)
                      break;
                    if (v629 <= 50.0)
                    {
                      if (v629 > 40.0)
                        v572 = cameraPos.z + -150.0;
                      else
                        v572 = cameraPos.z + -50.0;
                      --v624;
                      cameraPos.z = v572;
                      if (!v624)
                        goto LABEL_1100;
                    }
                    else
                    {
                      v572 = cameraPos.z + -300.0;
                      --v624;
                      cameraPos.z = cameraPos.z + -300.0;
                      if (!v624)
                        goto LABEL_1100;
                    }
                  }
                  v572 = cameraPos.z;
LABEL_1100:
                  v442 = -1.0;
                  v57 = vResTgt;
                  UnitFromDevilID = v852;
                  v650 = gBoss_AMATOBI_Z;
                  if (v572 >= v650)
                  {
                    if (!v649)
                    {
                      v650 = gBoss_AMATOBI_Z;
                    }
                    v651 = (f32)(cameraPos.z - v650) * 0.5;
                  }
                  else
                  {
                    if (!v649)
                    {
                      v650 = gBoss_AMATOBI_Z;
                    }
                    v651 = (f32)(cameraPos.z - v650) * 0.9;
                  }
                  v708 = v650 + v651;
                  gBoss_AMATOBI_Z = v708;
                  cameraPos.z = v708;
                  if (!v881)
                    goto LABEL_1488;
                  v710 = gBoss_AMATOBI_END_Nml + -0.05;
                  gBoss_AMATOBI_END_Nml = v710;
                  if (v710 < 0.0)
                  {
                    gBoss_AMATOBI_END_Nml = 0.0;
                  }
                  v711 = targetPos.x;
                  v440 = 0;
                  targetPos.x = v890 + (f32)((f32)(v711 - v890) * gBoss_AMATOBI_END_Nml);
                  targetPos.z = v888 + (f32)((f32)(targetPos.z - v888) * gBoss_AMATOBI_END_Nml);
                  cameraPos.x = v565 + (f32)((f32)(cameraPos.x - v565) * gBoss_AMATOBI_END_Nml);
                  cameraPos.z = v566 + (f32)((f32)(cameraPos.z - v566) * gBoss_AMATOBI_END_Nml);
                  goto LABEL_1491;
                default:
                  pBaseUnit = v853;
                  goto LABEL_667;
              }
            }
          }
          else
          {
            if (!v867 && !v889)
              goto LABEL_643;
          }
          gAuto_ManualKaiten_Cnt = 0;
          *(u64 *)&gAuto_Status = 17;
          goto LABEL_643;
        }
        if (v852->actaiwk->hit_area_r < 80.0)
        {
          v422 = 0;
          goto LABEL_631;
        }
        v425 = cameraPos.x;
        v426 = cameraPos.z;
        v427 = v853->pos.x;
        v428 = v853->pos.z;
        v429 = sBtlGetPosToDir(v425, v426, v427, v428);
        v430 = sBtlGetPosToDir(cameraPos.x, cameraPos.z, v852->pos.x, v852->pos.z);
        v422 = sBtlGetAtoB_LR_ABS(v429, v430) > 10.0;
      }
      v423 = v856;
      v424 = v865;
      goto LABEL_631;
    }
LABEL_620:
    v835 = 0;
    v832 = 0;
    v842 = 0;
    v845 = 1;
    goto LABEL_621;
  }
LABEL_452:
  v287 = v871;
  sBtlGetMoveXZ(v856, FromZ, v871 + 155.0, 140.0, (f32 *)&v902 + 1, &v902);
  v288.n64_u32[0] = -1021968384;
  v288.n64_u32[1] = vdup_lane_s32(v288, 0).n64_u32[1];
  if (SlideNml[0] <= 1.0)
    v289 = SlideNml[0];
  else
    v289 = 1.0;
  if (SlideNml[0] < 0.0)
    v289 = 0.0;
  v288.n64_u32[0] = HIDWORD(v902);
  *(float32x2_t *)&cameraPos.x = vadd_f32(*(float32x2_t *)&cameraPos.x, vmul_n_f32(vsub_f32(v288, *(float32x2_t *)&cameraPos.x), v289));
  cameraPos.z = cameraPos.z + (f32)(v289 * (f32)(*(f32 *)&v902 - cameraPos.z));
  v290 = v876.n64_f32[1];
  sBtlGetPosToVec(cameraPos.x, cameraPos.y, cameraPos.z, v876.n64_f32[0], v876.n64_f32[1], v873, (f32 *)&VY + 1, &VY, (f32 *)&TX + 1);
  __asm { FMOV            V2.2S, #30.0 }
  if (*((f32 *)&Dir + 1) <= 1.0)
    v294 = *((f32 *)&Dir + 1);
  else
    v294 = 1.0;
  if (*((f32 *)&Dir + 1) < 0.0)
    v294 = 0.0;
  cameraPos.z = cameraPos.z
                     + (f32)((f32)((f32)(cameraPos.z + (f32)(*((f32 *)&TX + 1) * 30.0)) - cameraPos.z) * v294);
  *(float32x2_t *)&cameraPos.x = vadd_f32(*(float32x2_t *)&cameraPos.x, vmul_n_f32(vsub_f32(vadd_f32(*(float32x2_t *)&cameraPos.x, vmul_f32((float32x2_t)__PAIR64__(VY, HIDWORD(VY)), _D2)), *(float32x2_t *)&cameraPos.x), v294));
  sBtlGetMoveXZ(v856, FromZ, v871 + 90.0, 30.0, (f32 *)&v902 + 1, &v902);
  v887 = v902;
  v296 = p_followUpAngle;
  v297 = wk;
  if (v297->CameraGazeOff)
    goto LABEL_468;
  v312 = UnitFromDevilID;
  v297 = wk;
  v313 = v297->UnitMng;
  v314 = pBaseUnit->actaiwk->targetID;
  v315 = sBtlSearchUnit_ID(v313, v314);
  UnitFromDevilID = v312;
  if (v315)
  {
    v316 = v315;
    v318 = wk;
    if (v318->Camera_EnemyDeadNear_ListID != v316->ListID)
      goto LABEL_530;
    v318 = wk;
    if (v318->Camera_EnemyDeadNear_UID != v316->UID)
    {
LABEL_530:
      if (v316->actwk->status != 10 || v884)
      {
        if (wk->Camera_EnemyDeadNear_ListID != -1)
        {
          if (((loc_1F04F20)(0) & 1) == 0)
            goto LABEL_545;
        }
LABEL_468:
        if (wk->CameraGazeOff)
          goto LABEL_470;
        v319 = 0.0;
        if (SlideNml[0] <= 1.0)
          v320 = SlideNml[0];
        else
          v320 = 1.0;
        if (SlideNml[0] >= 0.0)
          v319 = v320;
        *(float32x2_t *)&targetPos.x = vadd_f32(*(float32x2_t *)&targetPos.x, vmul_n_f32(vsub_f32(v876, *(float32x2_t *)&targetPos.x), v319));
        targetPos.z = targetPos.z + (f32)(v319 * (f32)(v873 - targetPos.z));
        if (v884)
        {
          sBtlGetMoveXZ(v856, FromZ, v287, 500.0, (f32 *)&v902 + 1, &v902);
          v321.n64_u32[1] = v876.n64_u32[1];
          if (SlideNml[0] <= 1.0)
            v322 = SlideNml[0];
          else
            v322 = 1.0;
          v323 = 0.0;
          if (SlideNml[0] >= 0.0)
            v323 = v322;
          v321.n64_u32[0] = HIDWORD(v902);
          v324 = vadd_f32(*(float32x2_t *)&targetPos.x, vmul_n_f32(vsub_f32(v321, *(float32x2_t *)&targetPos.x), v323)).n64_u64[0];
          v325 = targetPos.z;
          *(u64 *)&targetPos.x = v324;
          v326 = v323 * (f32)(*(f32 *)&v902 - targetPos.z);
LABEL_511:
          targetPos.z = v325 + v326;
        }
        goto LABEL_9019;
LABEL_470:
        sBtlGetMoveXZ(v856, FromZ, v287, 500.0, (f32 *)&v902 + 1, &v902);
        if (UnitFromDevilID)
        {
          v298 = pBaseUnit->pos.x;
          v299 = pBaseUnit->pos.z;
          v300 = UnitFromDevilID->pos.x;
          v301 = UnitFromDevilID->pos.z;
          v302 = sBtlGetLenXZ(v298, v299, v300, v301);
          if (v302 > 500.0)
            v290 = cameraPos.y + (f32)((f32)((f32)(v876.n64_f32[1] - cameraPos.y) / v302) * 500.0);
        }
        if (SlideNml[0] <= 1.0)
          v303 = SlideNml[0];
        else
          v303 = 1.0;
        if (SlideNml[0] >= 0.0)
          v304 = v303;
        else
          v304 = 0.0;
        v305 = targetPos.z + (f32)(v304 * (f32)(*(f32 *)&v902 - targetPos.z));
        v306 = targetPos.x + (f32)((f32)(*((f32 *)&v902 + 1) - targetPos.x) * v304);
        v307 = targetPos.y + (f32)((f32)(v290 - targetPos.y) * v304);
        v308 = wka->GazeOff_GunMode_RY;
        targetPos.z = v305;
        targetPos.x = v306;
        if (v308 <= 300.0)
        {
          v311 = 20.0;
          if ((f32)(v308 / 100.0) <= 1.0)
            v309 = v308 / 100.0;
          else
            v309 = 1.0;
          v310 = -300.0;
        }
        else
        {
          if ((f32)((f32)(360.0 - v308) / 50.0) <= 1.0)
            v309 = (f32)(360.0 - v308) / 50.0;
          else
            v309 = 1.0;
          v310 = 200.0;
          v311 = -60.0;
        }
        targetPos.y = v307 + (f32)((f32)(v309 * v310) + 0.0);
        cameraPos.y = (f32)((f32)(v309 * v311) + 0.0) + cameraPos.y;
        if (v308 == GazeOff_GunMode_RY)
        {
          if (!gsBtlCamera_Hokan_Not)
          {
            if (!gsBtlCamera_RingHokan_Not)
              targetPos.y = wka->targetpos.y
                                 + (f32)((f32)(targetPos.y - wka->targetpos.y) * 0.3);
          }
        }
LABEL_9019:
        goto LABEL_558;
      }
      v329 = (u16)v316->para->devilid;
      if (v329 == 258 || v329 == 314)
        goto LABEL_468;
      v330 = pBaseUnit->pos.x;
      v331 = pBaseUnit->pos.z;
      v332 = wk->scene->camera;
      v333 = v332->CameraLockOnTargetPos.x;
      v334 = v332->CameraLockOnTargetPos.z;
      v335 = sBtlGetLenXZ(v330, v331, v333, v334);
      v287 = v871;
      if (v335 >= 100.0)
        goto LABEL_468;
    }
  }
LABEL_545:
  sBtlGetMoveXZ(v856, FromZ, v287, 200.0, (f32 *)&v902 + 1, &v902);
  v336 = 0.0;
  v337.n64_u32[1] = v876.n64_u32[1];
  if (SlideNml[0] <= 1.0)
    v340 = SlideNml[0];
  else
    v340 = 1.0;
  if (SlideNml[0] >= 0.0)
    v336 = v340;
  v337.n64_u32[0] = HIDWORD(v902);
  *(float32x2_t *)&targetPos.x = vadd_f32(*(float32x2_t *)&targetPos.x, vmul_n_f32(vsub_f32(v337, *(float32x2_t *)&targetPos.x), v336));
  targetPos.z = targetPos.z + (f32)(v336 * (f32)(*(f32 *)&v902 - targetPos.z));
  if (!gsBtlCamera_Hokan_Not)
  {
    if (!gsBtlCamera_RingHokan_Not)
    {
      v325 = wka->targetpos.z;
      *(float32x2_t *)&targetPos.x = vadd_f32(*(float32x2_t *)&wka->targetpos.x, vmul_f32(vsub_f32(*(float32x2_t *)&targetPos.x, *(float32x2_t *)&wka->targetpos.x), vdup_n_s32(0x3E4CCCCDu)));
      v326 = (f32)(targetPos.z - v325) * 0.2;
      goto LABEL_511;
    }
  }
LABEL_558:
  v342 = targetPos.x;
  v343 = targetPos.z;
  v344 = cameraPos.x;
  v345 = cameraPos.z;
  *v296 = sBtlGetPosToDir(v342, v343, v344, v345);
  *(f32 *)&v213 = -150.0;
LABEL_561:
  v885 = *(f32 *)&v213;
  HIDWORD(UpV) = 0;
  v346 = targetPos.x;
  v347 = targetPos.y;
  v348 = targetPos.z;
  v349 = targetPos.w;
  v350 = wka->targetpos.z;
  v351 = wka->targetpos.x;
  HIDWORD(TZ) = LODWORD(wka->targetpos.y);
  *(f32 *)&TX = v351;
  fovy = wka->fovy;
  v353 = wka->camerapos.y;
  v354 = wka->camerapos.z;
  v355 = cameraPos.x;
  v356 = cameraPos.y;
  HIDWORD(CY) = LODWORD(wka->camerapos.x);
  *(f32 *)&TZ = v350;
  *(f32 *)&CY = v353;
  Fov = __PAIR64__(LODWORD(v354), LODWORD(fovy));
  v357 = cameraPos.z;
  v358 = cameraPos.w;
  *(f32 *)&UpV = wka->followUpAngle.x;
  if (!v359)
  v916.x = v346;
  v916.y = v347;
  v916.z = v348;
  v916.w = v349;
  v920.x = v355;
  v920.y = v356;
  v920.z = v357;
  v920.w = v358;
  if (sBtlPlayerGetCamMv(&TX, (f32 *)&TZ + 1, &TZ, (f32 *)&CY + 1, &CY, (f32 *)&Fov + 1, &Fov, (f32 *)&UpV + 1, &UpV, v916, v920))
  {
    *p_followUpAngle = v854;
    v361 = *((f32 *)&TZ + 1);
    v362 = *(f32 *)&TX;
    v364 = *((f32 *)&CY + 1);
    v363 = *(f32 *)&TZ;
    LODWORD(targetPos.z) = TZ;
    v366 = v885;
    gAuto_Status = 0;
    gFOVY_OW_Use = 1;
    gUpV2_OW_Use = 1;
    targetPos.x = v362;
    targetPos.y = v361;
    v367 = *((f32 *)&Fov + 1);
    cameraPos.x = v364;
    LODWORD(cameraPos.y) = CY;
    cameraPos.z = *((f32 *)&Fov + 1);
    LODWORD(gFOVY_OW_Param) = Fov;
    gUpV2_OW_Param = *((f32 *)&UpV + 1);
    if (UnitFromDevilID)
    {
      if ((pBaseUnit->motionID & 0xFFFFFFFE) == 0x7C)
      {
        v368 = UnitFromDevilID->para->devilid;
        if ((u32)(v368 - 258) < 3 || (v368 & 0xFFFFFFFC) == 0x138)
          goto LABEL_580;
      }
    }
LABEL_577:
    *p_followUpAngle = sBtlGetPosToDir(v362, v363, v364, v367);
    goto LABEL_580;
  }
  v369 = targetPos.x;
  v370 = targetPos.y;
  v371 = targetPos.z;
  v372 = targetPos.w;
  v374 = cameraPos.x;
  v373 = cameraPos.y;
  v375 = cameraPos.z;
  v376 = cameraPos.w;
  v917.x = v369;
  v917.y = v370;
  v917.z = v371;
  v917.w = v372;
  v921.x = v374;
  v921.y = v373;
  v921.z = v375;
  v921.w = v376;
  v366 = v885;
  if (sBtlGetSetsumaCamMv(pBaseUnit, &TX, (f32 *)&TZ + 1, &TZ, (f32 *)&CY + 1, &CY, (f32 *)&Fov + 1, &Fov, (f32 *)&UpV + 1, &UpV, v917, v921))
  {
    *(u32 *)p_followUpAngle = UpV;
    v362 = *(f32 *)&TX;
    v364 = *((f32 *)&CY + 1);
    v363 = *(f32 *)&TZ;
    LODWORD(targetPos.z) = TZ;
    LODWORD(targetPos.x) = TX;
    targetPos.y = *((f32 *)&TZ + 1);
    v367 = *((f32 *)&Fov + 1);
    cameraPos.x = *((f32 *)&CY + 1);
    LODWORD(cameraPos.y) = CY;
    cameraPos.z = *((f32 *)&Fov + 1);
    if (!v378)
    {
      v362 = targetPos.x;
      v363 = targetPos.z;
      v364 = cameraPos.x;
      v367 = cameraPos.z;
    }
    v379 = *(f32 *)&Fov;
    gFOVY_OW_Use = 1;
    gUpV2_OW_Use = 1;
    gFOVY_OW_Param = v379;
    gUpV2_OW_Param = *((f32 *)&UpV + 1);
    goto LABEL_577;
  }
LABEL_580:
  IsHuuma = sBtlIsHuuma();
  if (UnitFromDevilID && IsHuuma)
  {
    sBtlGetHuuma_CameraParam(&targetPos.x, &targetPos.y, &targetPos.z, &cameraPos.x, &cameraPos.y, &cameraPos.z, &gFOVY_OW_Param, &gUpV2_OW_Param);
    v385 = targetPos.x;
    v386 = targetPos.z;
    v387 = cameraPos.x;
    v388 = cameraPos.z;
    gFOVY_OW_Use = 1;
    gUpV2_OW_Use = 1;
    *p_followUpAngle = sBtlGetPosToDir(v385, v386, v387, v388);
  }
  if (v891 && SlideNml[0] > 0.7)
  {
    v391 = 0.0;
    v392 = v882;
    v393 = *((f32 *)&v887 + 1);
    v394 = v366;
    v395 = *(f32 *)&v887;
    goto LABEL_598;
  }
  else
  {
    v393 = targetPos.x;
    v394 = targetPos.y;
    v395 = targetPos.z;
    v391 = targetPos.w;
    v392 = v882;
  }
LABEL_598:
  v918.x = v393;
  v918.y = v394;
  v918.z = v395;
  v918.w = v391;
  RaycastCamHit(pBaseUnit, v918, &cameraPos, 100.0);
  *v57 = targetPos;
  *v392 = cameraPos;
  if (v891 && SlideNml[0] > 0.7)
  {
    v397 = v392->x;
    v398 = v392->y;
    v399 = v392->z;
    v400 = v392->w;
    v919.x = *((f32 *)&v887 + 1);
    v919.w = 0.0;
    v919.y = v366;
    LODWORD(v919.z) = v887;
    v922.x = v397;
    v922.y = v398;
    v922.z = v399;
    v922.w = v400;
  }
  else
  {
    v407 = v57->x;
    v408 = v57->y;
    v409 = v57->z;
    v410 = v57->w;
    v411 = v392->x;
    v412 = v392->y;
    v413 = v392->z;
    v414 = v392->w;
    v919.x = v407;
    v919.y = v408;
    v919.z = v409;
    v919.w = v410;
    v922.x = v411;
    v922.y = v412;
    v922.z = v413;
    v922.w = v414;
  }
  RaycastCamHide(v919, v922);
}

// 0x1ef8fd0
static bool RaycastCamHit(SBTLUNIT_WORK *pBaseUnit, const sdfVector4_t *targetPos, sdfVector4_t *cameraPos, f32 _MiorosiY) {
  f32 z;
  f32 y;
  f32 x;
  f32 v13;
  f32 v14;
  f32 v15;
  bool v19;
  f32 v20;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 LenXZ;
  f32 v28;
  f32 v29;
  char v31;
  f32 HitZ;
  s64 HitY;
  UnityEngine_RaycastHit_o Hit;

  z = targetPos->z;
  y = targetPos->y;
  x = targetPos->x;
  HitY = 0;
  HitZ = 0.0;
  memset(&Hit, 0, sizeof(Hit));
  if (gLayerMask_sBtlCamHit)
  {
    v13 = cameraPos->z;
    v14 = cameraPos->x;
    v15 = cameraPos->y;
    goto LABEL_6;
  }
  v31 = NameToLayer("Layer_sBtlCamHit", 0);
  gLayerMask_sBtlCamHit = 1 << v31;
  v13 = cameraPos->z;
  v14 = cameraPos->x;
  v15 = cameraPos->y;
LABEL_6:
  v19 = sBtlRaycast_PS2(x, y, z, v14, v15, v13, gLayerMask_sBtlCamHit, &Hit, (f32 *)&HitY + 1, &HitY, &HitZ);
  if (v19)
  {
    v20 = *(f32 *)&HitY;
    cameraPos->x = *((f32 *)&HitY + 1);
    cameraPos->y = v20;
    cameraPos->z = HitZ;
    v22 = pBaseUnit->pos.y;
    if (sBtlGetABS(v20 - v22) <= 200.0)
    {
      v23 = pBaseUnit->pos.x;
      v24 = pBaseUnit->pos.z;
      v25 = cameraPos->x;
      v26 = cameraPos->z;
      LenXZ = sBtlGetLenXZ(v23, v24, v25, v26);
      if (LenXZ < 300.0)
      {
        v28 = (f32)(LenXZ + -300.0) / -300.0;
        v29 = 1.0;
        if (v28 <= 1.0)
          v29 = v28;
        if (v28 < 0.0)
          v29 = 0.0;
        if (v29 < 0.0)
          v29 = 0.0;
        cameraPos->y = cameraPos->y - (f32)((f32)(v29 * MiorosiY) + 0.0);
      }
    }
  }
  return v19;
}

// 0x1ef9270
static void RaycastCamHide(const sdfVector4_t *targetPos, const sdfVector4_t *cameraPos) {
  f32 z;
  f32 y;
  f32 x;
  f32 v6;
  f32 v7;
  f32 v8;
  void *v14;
  s64 v15;
  void *m_Items;
  __int128 v17;
  __int128 v18;
  struct sdfVector2_t m_UV;
  void *collider;
  void *gameObject;
  Il2CppObject *Component_object;
  s32 v24;
  void *v25;
  s64 i;
  void *v27;
  Il2CppObject *v28;
  char v29;
  UnityEngine_RaycastHit_o v30;
  void *HitColliders;
  void *Hits;

  z = cameraPos->z;
  y = cameraPos->y;
  x = cameraPos->x;
  v6 = targetPos->z;
  v7 = targetPos->y;
  v8 = targetPos->x;
  HitColliders = 0;
  Hits = 0;
  memset(&v30, 0, sizeof(v30));
  if (gLayerMask_aBtlCamHide)
  {
    goto LABEL_6;
  }
  v29 = NameToLayer("Layer_aBtlCamHide", 0);
  gLayerMask_aBtlCamHide = 1 << v29;
LABEL_6:
  if (sBtlRaycastAll_PS2(v8, v7, v6, x, y, z, gLayerMask_aBtlCamHide, &Hits))
  {
    v14 = Hits;
    if (SLODWORD(Hits->max_length) >= 1)
    {
      v15 = 0;
      m_Items = Hits;
      do
      {
        v17 = *(_OWORD *)&m_Items->m_Point.x;
        v18 = *(_OWORD *)&m_Items->m_Normal.y;
        m_UV = m_Items->m_UV;
        v30.m_Collider = m_Items->m_Collider;
        v30.m_UV = m_UV;
        *(_OWORD *)&v30.m_Point.x = v17;
        *(_OWORD *)&v30.m_Normal.y = v18;
        collider = get_collider(&v30, 0);
        gameObject = get_gameObject(collider, 0);
        Component_object = GetComponent_object_(gameObject);
        if (op_Inequality(Component_object, 0, 0))
          goto LABEL_16;
        goto LABEL_9001;
        if (op_Inequality(Component_object, 0, 0))
LABEL_16:
          SetView(Component_object, 0, 0);
LABEL_9001:
        ++v15;
        ++m_Items;
      }
      while (v15 < SLODWORD(v14->max_length));
    }
  }
  v24 = gLayerMask_aBtlCamHide;
  if (sBtlRaycastInside_PS2(x, y, z, v24, &HitColliders))
  {
    v25 = HitColliders;
    if (SLODWORD(HitColliders->max_length) >= 1)
    {
      for (i = 0; i < SLODWORD(v25->max_length); ++i)
      {
        v27 = get_gameObject(v25[i], 0);
        v28 = GetComponent_object_(v27);
        if (op_Inequality(v28, 0, 0))
          goto LABEL_28;
        goto LABEL_9002;
        if (op_Inequality(v28, 0, 0))
LABEL_28:
          SetViewInnside(v28, 0, 0);
LABEL_9002:
      }
    }
  }
}

// 0x1ef9610
void Slerp(SBTLCAMERA_WORK *wk, const sdfVector4_t *vPos, const sdfVector4_t *vTgt, f32 f) {
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  sdfVector4_t *p_camerapos;
  f32 *p_x;
  s32 v17;
  sdfVector4_t *p_targetpos;
  struct sdfVector4_t targetpos;
  struct sdfVector4_t v20;
  f32 *v21;
  s32 v23;
  struct sdfVector4_t v27;
  f32 w;
  struct sdfVector4_t camerapos;
  f32 v31;
  struct sdfVector4_t v32;

  w = vTgt->w;
  z = vTgt->z;
  y = vTgt->y;
  x = vTgt->x;
  v8 = vPos->w;
  v9 = vPos->z;
  v10 = vPos->y;
  v11 = vPos->x;
  p_camerapos = &wk->camerapos;
  camerapos = wk->camerapos;
  vct_A = camerapos;
  v31 = 1.0 - f;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v31);
  p_x = &vf00.x;
  p_x[4] = v11;
  p_x[5] = v10;
  p_x[6] = v9;
  p_x[7] = v8;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, f);
  vct_B = vct_A;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v17 = (u8)byte_5755EF5;
  *p_camerapos = vct_A;
  targetpos = wk->targetpos;
  p_targetpos = &wk->targetpos;
  v20 = targetpos;
  if (v17)
    goto LABEL_20;
  goto LABEL_54;
  if (v23)
  {
LABEL_20:
    goto LABEL_21;
  }
LABEL_54:
  v27 = v20;
  v20 = v27;
LABEL_21:
  vct_A = v20;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v31);
  v32 = vct_A;
  v21 = &vf00.x;
  v21[4] = x;
  v21[5] = y;
  v21[6] = z;
  v21[7] = w;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, f);
  vct_B = v32;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  *p_targetpos = vct_A;
}

// 0x1ef9c60
bool sBtlIsMoveEnd(void) {
  return wk->scene->camera->m_CamMov->m_PosCtrlCam->m_run == -1;
}

// 0x1ef9ce0
void sBtlSetMoveEnd(void) {
  wk->scene->camera->m_CamMov->m_PosCtrlCam->m_run = 0;
}

// 0x1ef9d50
static void GetNowPosAS(sdfVector4_t *vPosRes, const sdfVector4_t *vPosBgn, const sdfVector4_t *vPosEnd, f32 fTime, f32 x) {
  f32 w;
  f32 z;
  f32 y;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v15;
  f32 v16;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v24;
  f32 v26;

  w = vPosEnd->w;
  z = vPosEnd->z;
  y = vPosEnd->y;
  v9 = vPosEnd->x;
  v10 = vPosBgn->y;
  v11 = vPosBgn->x;
  v24 = vPosBgn->w;
  v26 = vPosBgn->z;
  if (x == fTime)
  {
    p_x = &vf00.x;
    p_x[4] = v9;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    goto LABEL_9;
  }
  v15 = &vf00.x;
  v15[4] = v9;
  v15[5] = y;
  v15[6] = z;
  v15[7] = w;
  v16 = fTime * fTime;
  v17 = &vf00.x;
  v17[8] = v11;
  v17[9] = v10;
  v17[10] = v26;
  v17[11] = v24;
  v18 = x * x;
  v19 = v16 * fTime;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v20 = (f32)((f32)(v18 * x) + (f32)(v18 * x)) / v19;
  v21 = (f32)(v18 * 3.0) / v16;
  v22 = v21 - v20;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v22);
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_9:
  *vPosRes = vct_A;
}

// 0x1efa0b0
static void GetNowPosS(sdfVector4_t *vPosRes, const sdfVector4_t *vPosBgn, const sdfVector4_t *vPosEnd, f32 fTime, f32 x) {
  f32 w;
  f32 z;
  f32 y;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v15;
  f32 *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v22;
  f32 v24;

  w = vPosEnd->w;
  z = vPosEnd->z;
  y = vPosEnd->y;
  v9 = vPosEnd->x;
  v10 = vPosBgn->y;
  v11 = vPosBgn->x;
  v22 = vPosBgn->w;
  v24 = vPosBgn->z;
  if (x == fTime)
  {
    p_x = &vf00.x;
    p_x[4] = v9;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    goto LABEL_9;
  }
  v15 = &vf00.x;
  v15[4] = v9;
  v15[5] = y;
  v15[6] = z;
  v15[7] = w;
  v16 = &vf00.x;
  v16[8] = v11;
  v16[9] = v10;
  v16[10] = v24;
  v16[11] = v22;
  v17 = fTime * fTime;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v18 = (f32)(x * x) / v17;
  v19 = (f32)(x + x) / fTime;
  v20 = v19 - v18;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v20);
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_9:
  *vPosRes = vct_A;
}

// 0x1efa3f0
static void GetNowPos(sdfVector4_t *vPosRes, const sdfVector4_t *vPosBgn, const sdfVector4_t *vPosEnd, f32 fTime, f32 x) {
  f32 v6;
  f32 v7;
  f32 y;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v16;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 w;
  f32 z;

  w = vPosBgn->w;
  z = vPosBgn->z;
  v6 = vPosEnd->w;
  v7 = vPosEnd->z;
  y = vPosEnd->y;
  v9 = vPosEnd->x;
  v10 = vPosBgn->y;
  v11 = vPosBgn->x;
  if (x == fTime)
  {
    p_x = &vf00.x;
    p_x[4] = v9;
    p_x[5] = y;
    p_x[6] = v7;
    p_x[7] = v6;
    goto LABEL_9;
  }
  v16 = &vf00.x;
  v16[4] = v9;
  v16[5] = y;
  v16[6] = v7;
  v16[7] = v6;
  v17 = &vf00.x;
  v17[8] = v11;
  v17[9] = v10;
  v17[10] = z;
  v17[11] = w;
  v18 = x / fTime;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v19 = 1.0 - v18;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v19);
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_9:
  *vPosRes = vct_A;
}

// 0x1efa720
static void GetNowFovyAS(f32 *fovy, f32 fovyBgn, f32 fovyEnd, f32 fTime, f32 x) {
  if (fovyBgn != -1.0 && fovyEnd != -1.0)
  {
    if (x != fTime)
      fovyEnd = (f32)((f32)(fovyEnd - fovyBgn) * (f32)((f32)((f32)((f32)(x * x) * 3.0) / (f32)(fTime * fTime)) - (f32)((f32)((f32)((f32)(x * x) * x) + (f32)((f32)(x * x) * x)) / (f32)((f32)(fTime * fTime) * fTime))))
              + fovyBgn;
    *fovy = fovyEnd;
  }
}

// 0x1efa780
static void GetNowFovyS(f32 *fovy, f32 fovyBgn, f32 fovyEnd, f32 fTime, f32 x) {
  if (fovyBgn != -1.0 && fovyEnd != -1.0)
  {
    if (x != fTime)
      fovyEnd = (f32)((f32)(fovyEnd - fovyBgn) * (f32)((f32)((f32)(x + x) / fTime) - (f32)((f32)(x * x) / (f32)(fTime * fTime))))
              + fovyBgn;
    *fovy = fovyEnd;
  }
}

// 0x1efa7d0
static void GetNowFovy(f32 *fovy, f32 fovyBgn, f32 fovyEnd, f32 fTime, f32 x) {
  if (fovyBgn != -1.0 && fovyEnd != -1.0)
  {
    if (x != fTime)
      fovyEnd = (f32)((f32)(fovyEnd - fovyBgn) / fTime) + *fovy;
    *fovy = fovyEnd;
  }
}

// 0x1efa800
static f32 PosCtrlSystem(S_PosCtrl *pPosCtrl, sdfVector4_t *pvRet) {
  S_PosMove *m_pPosMove;
  f32 v6;
  s32 m_cnt;
  S_PosMove *v8;
  SBTLUNIT_WORK *pCamSklUser;
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  f32 w;
  f32 y;
  f32 z;
  f32 v20;
  f32 v21;
  s64 v23;
  f32 v24;
  struct sdfVector4_t pos;
  s64 v29;
  f32 v30;
  u16 major;
  f32 v35;
  s32 minor;
  s64 v37;
  f32 v38;
  u16 v41;
  s32 v42;
  f32 cylinder;
  u16 v44;
  s32 v45;
  s64 v48;
  f32 v49;
  f32 x;
  s64 m_eCtrl;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  long f64 v58;
  s64 v59;
  long f64 v60;
  long f64 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 fTime;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 m_fFrm;
  f32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  S_PosCtrl *p_fields;
  struct sdfVector4_t v76;
  struct sdfVector4_t vPosEnd;
  struct sdfVector4_t vPosEndh;
  struct sdfVector4_t vPosEndi;
  struct sdfVector4_t vPosEnda;
  struct sdfVector4_t vPosEndb;
  struct sdfVector4_t vPosEndc;
  f32 vPosEndd;
  f32 vPosEnde;
  f32 vPosEndf;
  struct sdfVector4_t vPosEndg;
  sdfMatrix4_t v88;
  sdfMatrix4_t v89;
  sdfVector4_t vPosBgn;
  sdfVector4_t v91;
  sdfVector4_t v93;
  sdfVector4_t v94;
  sdfVector4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;
  sdfVector4_t v98;

  m_pPosMove = pPosCtrl->m_pPosMove;
  v6 = 0.0;
  if (m_pPosMove && pPosCtrl->m_run)
  {
    m_cnt = pPosCtrl->m_cnt;
    v8 = m_pPosMove[pPosCtrl->m_stp];
    switch (v8->m_eChar)
    {
      case 1:
        pCamSklUser = wk->pCamSklUser;
        break;
      case 2:
        PChara = sBtlGetPChara();
        goto LABEL_19;
      case 3:
        pCamSklUser = wk->cmbSkl->pNakama0;
        break;
      case 4:
        UnitMng = wk->UnitMng;
        boss_eventID = wk->boss_eventID;
        PChara = sBtlSearchUnit_ID(UnitMng, boss_eventID);
LABEL_19:
        pCamSklUser = PChara;
        break;
      default:
        pCamSklUser = 0;
        break;
    }
    w = 0.0;
    y = 0.0;
    z = 0.0;
    switch (v8->m_ePosType)
    {
      case 1:
        v6 = v8->m_vPos.x;
        y = v8->m_vPos.y;
        z = v8->m_vPos.z;
        goto LABEL_104;
      case 2:
        if (v8->m_eChar == 2)
        {
          v20 = pCamSklUser->pos.x;
          v21 = pCamSklUser->pos.z;
          sub_1B332C0(0, v20, -90.0, v21, 1.0);
        }
        else
        {
          sBtlGetUnitHelperPos(pCamSklUser, 0);
        }
        v48 = *(u64 *)&v8->m_vPos.x;
        v49 = v8->m_vPos.z;
        goto LABEL_92;
      case 3:
        vPosEnd = pCamSklUser->rot;
        vct_A = vPosEnd;
        ToMatrix();
        v23 = *(u64 *)&v8->m_vPos.x;
        v24 = v8->m_vPos.z;
        *(u64 *)&vct_A.x = v23;
        vct_A.z = v24;
        vct_A.w = 0.0;
        get_transpose(&v89, &mtx_A, 0);
        v88 = v89;
        v91 = op_Multiply_60923920(&v88, vct_A, 0);
        vct_A = v91;
        pos = pCamSklUser->pos;
        goto LABEL_44;
      case 4:
        v29 = *(u64 *)&v8->m_vPos.x;
        v30 = v8->m_vPos.z;
        *(u64 *)&vct_A.x = v29;
        vct_A.z = v30;
        vct_A.w = 0.0;
        pos = pCamSklUser->pos;
        vPosEndh = pos;
        pos = vPosEndh;
LABEL_44:
        vPosEndi = pos;
        pos = vPosEndi;
        vct_B = pos;
        goto LABEL_48;
      case 5:
        vPosEnda = pCamSklUser->pos;
        vct_A = vPosEnda;
        major = pCamSklUser->major;
        z = vct_A.z;
        v6 = vct_A.x;
        v35 = vct_A.y;
        minor = pCamSklUser->minor;
        y = v35 + (f32)(sBtlGetVisualData(major, minor)->nml->height * -0.5);
        goto LABEL_104;
      case 6:
        v37 = *(u64 *)&v8->m_vPos.x;
        v38 = v8->m_vPos.z;
        *(u64 *)&vct_A.x = v37;
        vct_A.z = v38;
        vct_A.w = 0.0;
        v41 = pCamSklUser->major;
        v42 = pCamSklUser->minor;
        cylinder = sBtlGetVisualData(v41, v42)->nml->cylinder;
        if (cylinder < sBtlGetVisualData(pCamSklUser->major, pCamSklUser->minor)->nml->height)
        {
          v44 = pCamSklUser->major;
          v45 = pCamSklUser->minor;
          cylinder = sBtlGetVisualData(v44, v45)->nml->height;
        }
        if ((f32)(cylinder * 0.01) > 1.0)
        {
          sub_1B33480(0, cylinder * 0.01);
          vPosEndb = pCamSklUser->pos;
LABEL_74:
          goto LABEL_75;
        }
        else
        {
          vPosEndb = pCamSklUser->pos;
          goto LABEL_74;
        }
LABEL_75:
        vct_B = vPosEndb;
LABEL_48:
        vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        goto LABEL_103;
      case 7:
        vPosEndc = wk->vPosBossEvent;
        vct_A = vPosEndc;
        v48 = *(u64 *)&v8->m_vPos.x;
        v49 = v8->m_vPos.z;
LABEL_92:
        *(u64 *)&vct_B.x = v48;
        vct_B.z = v49;
        vct_B.w = 0.0;
        vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_103:
        v6 = vct_A.x;
        y = vct_A.y;
        z = vct_A.z;
LABEL_104:
        x = m_cnt;
        m_eCtrl = v8->m_eCtrl;
        if ((u8)m_eCtrl <= 4u)
        {
          w = v8->m_vPos.w;
          switch ((char)m_eCtrl)
          {
            case 0:
              v54 = pPosCtrl->vLast.x;
              v55 = pPosCtrl->vLast.y;
              v57 = pPosCtrl->vLast.z;
              v56 = pPosCtrl->vLast.w;
              *(__n128 *)&v58 = sub_1B332C0(0, v54, v55, v57, v56);
              sub_1B335A0(pvRet, 0, v58);
              w = pPosCtrl->vLast.w;
              pvRet->w = 0.0;
              break;
            case 1:
              v59 = (u32)m_eCtrl & 0xFFFF0000;
              *(__n128 *)&v60 = sub_1B332C0(0, v6, y, z, w);
              *(__n128 *)&v61 = sub_1B335A0(pvRet, 0, v60);
              sub_1B335A0(&pPosCtrl->fields, 0, v61);
              if (v59)
                sBtlSetDrawChar(v59);
              break;
            case 2:
              vPosEndd = v8->m_vPos.w;
              v93.x = pPosCtrl->vLast.x;
              v62 = pPosCtrl->vLast.y;
              v63 = pPosCtrl->vLast.z;
              v64 = pPosCtrl->vLast.w;
              fTime = v8->m_fFrm;
              vPosBgn.x = pPosCtrl->vLast.x;
              v93.x = vPosBgn.x;
              v96.w = vPosEndd;
              v93.y = v62;
              v93.z = v63;
              v93.w = v64;
              v96.x = v6;
              v96.y = y;
              v96.z = z;
              GetNowPosAS(pvRet, v93, v96, fTime, x);
              goto LABEL_122;
            case 3:
              vPosEnde = v8->m_vPos.w;
              v94.x = pPosCtrl->vLast.x;
              v66 = pPosCtrl->vLast.y;
              v67 = pPosCtrl->vLast.z;
              v68 = pPosCtrl->vLast.w;
              m_fFrm = v8->m_fFrm;
              vPosBgn.x = pPosCtrl->vLast.x;
              v94.x = vPosBgn.x;
              v97.w = vPosEnde;
              v94.y = v66;
              v94.z = v67;
              v94.w = v68;
              v97.x = v6;
              v97.y = y;
              v97.z = z;
              GetNowPosS(pvRet, v94, v97, m_fFrm, x);
              goto LABEL_122;
            case 4:
              vPosEndf = v8->m_vPos.w;
              v95.x = pPosCtrl->vLast.x;
              v70 = pPosCtrl->vLast.y;
              v71 = pPosCtrl->vLast.z;
              v72 = pPosCtrl->vLast.w;
              v73 = v8->m_fFrm;
              vPosBgn.x = pPosCtrl->vLast.x;
              v95.x = vPosBgn.x;
              v98.w = vPosEndf;
              v95.y = v70;
              v95.z = v71;
              v95.w = v72;
              v98.x = v6;
              v98.y = y;
              v98.z = z;
              GetNowPos(pvRet, v95, v98, v73, x);
LABEL_122:
              w = (f32)((f32)(v8->m_vPos.w * x) / v8->m_fFrm)
                + (f32)(pPosCtrl->vLast.w * (f32)(1.0 - (f32)(x / v8->m_fFrm)));
              break;
            default:
              w = 0.0;
              break;
          }
        }
        v6 = (f32)(w * 3.141592) / 180.0;
        if (v8->m_fFrm > x)
        {
          ++pPosCtrl->m_cnt;
          return v6;
        }
        if ((v8->m_eCtrl & 0x100) == 0)
        {
          pPosCtrl->m_cnt = 0;
          vPosEndg = *pvRet;
          vct_A = vPosEndg;
          p_fields = &pPosCtrl->fields;
          v76 = vct_A;
          ++pPosCtrl->m_stp;
          p_fields->vLast = v76;
          pPosCtrl->vLast.w = w;
          return v6;
        }
        pPosCtrl->m_run = -1;
        break;
      default:
        goto LABEL_104;
    }
  }
  return v6;
}

// 0x1efb540
static bool FovCtrlSystem(S_FovCtrl *pFovCtrl, f32 *fov) {
  f32 m_cnt;
  S_FovMove *v6;
  s32 m_eCtrl;
  f32 v8;
  f32 m_fovy;
  f32 v10;
  s32 v12;
  f32 m_fovLast;
  f32 m_fFrm;
  f32 v15;
  f32 v16;

  if (!pFovCtrl->m_run)
    return 0;
  m_cnt = pFovCtrl->m_cnt;
  v6 = pFovCtrl->m_pFovMove[pFovCtrl->m_stp];
  m_eCtrl = v6->m_eCtrl;
  if ((m_eCtrl & 1) != 0)
  {
    m_fovy = v6->m_fovy;
LABEL_16:
    *fov = m_fovy;
    goto LABEL_17;
  }
  if ((m_eCtrl & 2) != 0)
  {
    m_fovLast = pFovCtrl->m_fovLast;
    m_fovy = v6->m_fovy;
    m_fFrm = v6->m_fFrm;
    if (m_fovLast != -1.0 && m_fovy != -1.0)
    {
      if (m_fFrm != m_cnt)
        m_fovy = m_fovLast
               + (f32)((f32)(m_fovy - m_fovLast) * (f32)((f32)((f32)((f32)(m_cnt * m_cnt) * 3.0) / (f32)(m_fFrm * m_fFrm)) - (f32)((f32)((f32)((f32)(m_cnt * m_cnt) * m_cnt) + (f32)((f32)(m_cnt * m_cnt) * m_cnt)) / (f32)(m_fFrm * (f32)(m_fFrm * m_fFrm)))));
      goto LABEL_16;
    }
  }
  else if ((m_eCtrl & 4) != 0)
  {
    v15 = pFovCtrl->m_fovLast;
    m_fovy = v6->m_fovy;
    v16 = v6->m_fFrm;
    if (v15 != -1.0 && m_fovy != -1.0)
    {
      if (v16 != m_cnt)
        m_fovy = v15
               + (f32)((f32)(m_fovy - v15) * (f32)((f32)((f32)(m_cnt + m_cnt) / v16) - (f32)((f32)(m_cnt * m_cnt) / (f32)(v16 * v16))));
      goto LABEL_16;
    }
  }
  else if ((m_eCtrl & 8) != 0)
  {
    v8 = pFovCtrl->m_fovLast;
    m_fovy = v6->m_fovy;
    v10 = v6->m_fFrm;
    if (v8 != -1.0 && m_fovy != -1.0)
    {
      if (v10 != m_cnt)
        m_fovy = (f32)((f32)(m_fovy - v8) / v10) + *fov;
      goto LABEL_16;
    }
  }
LABEL_17:
  if (v6->m_fFrm > m_cnt)
  {
    ++pFovCtrl->m_cnt;
    return 1;
  }
  if ((v6->m_eCtrl & 0x10) == 0)
  {
    pFovCtrl->m_fovLast = *fov;
    v12 = pFovCtrl->m_stp + 1;
    pFovCtrl->m_cnt = 0;
    pFovCtrl->m_stp = v12;
    return 1;
  }
  pFovCtrl->m_run = -1;
  return 0;
}

// 0x1efb790
static bool DofCtrlSystem(S_DofCtrl *pDofCtrl, DepthOfFieldSetting *dof) {
  f32 m_cnt;
  S_DofMove *v6;
  DepthOfFieldSetting *m_dof;
  DepthOfFieldSetting *v9;
  DepthOfFieldSetting *p_m_dofLast;

  if (!pDofCtrl->m_run)
    return 0;
  m_cnt = pDofCtrl->m_cnt;
  v6 = pDofCtrl->m_dofMove[pDofCtrl->m_stp];
  if ((v6->m_eCtrl & 1) != 0)
  {
    m_dof = v6->m_dof;
    dof = m_dof;
  }
  if (v6->m_fFrm <= m_cnt)
  {
    if ((v6->m_eCtrl & 0x10) != 0)
    {
      pDofCtrl->m_run = -1;
      return 0;
    }
    else
    {
      v9 = dof;
      pDofCtrl->m_dofLast = dof;
      p_m_dofLast = &pDofCtrl->m_dofLast;
      *((u32 *)p_m_dofLast - 4) = 0;
      ++*((u32 *)p_m_dofLast - 3);
      return 1;
    }
  }
  else
  {
    ++pDofCtrl->m_cnt;
    return 1;
  }
}

// 0x1efb880
void sBtlEventFovOff(void) {
  gFOVY2_OW_Use = 0;
  return;
}

// 0x1efb900
static bool UpVCtrlSystem(S_UpVCtrl *pUpVCtrl, f32 *_UpV) {
  f32 m_cnt;
  S_UpVMove *v6;
  s32 m_eCtrl;
  f32 v8;
  f32 m_UpV;
  f32 v10;
  s32 v12;
  f32 m_UpVLast;
  f32 m_fFrm;
  f32 v15;
  f32 v16;

  if (!pUpVCtrl->m_run)
    return 0;
  m_cnt = pUpVCtrl->m_cnt;
  v6 = pUpVCtrl->m_pUpVMove[pUpVCtrl->m_stp];
  m_eCtrl = v6->m_eCtrl;
  if ((m_eCtrl & 1) != 0)
  {
    m_UpV = v6->m_UpV;
LABEL_16:
    *UpV = m_UpV;
    goto LABEL_17;
  }
  if ((m_eCtrl & 2) != 0)
  {
    m_UpVLast = pUpVCtrl->m_UpVLast;
    m_UpV = v6->m_UpV;
    m_fFrm = v6->m_fFrm;
    if (m_UpVLast != -1.0 && m_UpV != -1.0)
    {
      if (m_fFrm != m_cnt)
        m_UpV = m_UpVLast
              + (f32)((f32)(m_UpV - m_UpVLast) * (f32)((f32)((f32)((f32)(m_cnt * m_cnt) * 3.0) / (f32)(m_fFrm * m_fFrm)) - (f32)((f32)((f32)((f32)(m_cnt * m_cnt) * m_cnt) + (f32)((f32)(m_cnt * m_cnt) * m_cnt)) / (f32)(m_fFrm * (f32)(m_fFrm * m_fFrm)))));
      goto LABEL_16;
    }
  }
  else if ((m_eCtrl & 4) != 0)
  {
    v15 = pUpVCtrl->m_UpVLast;
    m_UpV = v6->m_UpV;
    v16 = v6->m_fFrm;
    if (v15 != -1.0 && m_UpV != -1.0)
    {
      if (v16 != m_cnt)
        m_UpV = v15
              + (f32)((f32)(m_UpV - v15) * (f32)((f32)((f32)(m_cnt + m_cnt) / v16) - (f32)((f32)(m_cnt * m_cnt) / (f32)(v16 * v16))));
      goto LABEL_16;
    }
  }
  else if ((m_eCtrl & 8) != 0)
  {
    v8 = pUpVCtrl->m_UpVLast;
    m_UpV = v6->m_UpV;
    v10 = v6->m_fFrm;
    if (v8 != -1.0 && m_UpV != -1.0)
    {
      if (v10 != m_cnt)
        m_UpV = (f32)((f32)(m_UpV - v8) / v10) + *UpV;
      goto LABEL_16;
    }
  }
LABEL_17:
  if (v6->m_fFrm > m_cnt)
  {
    ++pUpVCtrl->m_cnt;
    return 1;
  }
  if ((v6->m_eCtrl & 0x10) == 0)
  {
    pUpVCtrl->m_UpVLast = *UpV;
    v12 = pUpVCtrl->m_stp + 1;
    pUpVCtrl->m_cnt = 0;
    pUpVCtrl->m_stp = v12;
    return 1;
  }
  pUpVCtrl->m_run = -1;
  return 0;
}

// 0x1efbb50
void sBtlEventUpVOff(void) {
  gUpV2_OW_Use = 0;
  return;
}

// 0x1efbbd0
static f32 CameraMoveSystem(SBTLCAMERA_WORK *wk) {
  S_PosCtrl *m_PosCtrlCam;
  f32 v5;
  S_FovCtrl *m_FovCtrl;
  S_FovMove *m_pFovMove;
  f32 v12;
  f32 v15;
  void *Instance;
  void *mDof;
  S_UpVCtrl *m_UpVCtrl;
  S_UpVMove *m_pUpVMove;
  f32 v25;
  f32 *v26;
  void *monitor;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  void *v32;
  UnityEngine_Object_c *klass;
  void *v34;
  intptr_t m_CachedPtr;
  void *v36;
  void *v37;
  void *v38;

  m_PosCtrlCam = wk->m_CamMov->m_PosCtrlCam;
  v5 = PosCtrlSystem(m_PosCtrlCam, &wk->camerapos);
  PosCtrlSystem(wk->m_CamMov->m_PosCtrlTgt, &wk->targetpos);
  m_FovCtrl = wk->m_CamMov->m_FovCtrl;
  m_pFovMove = m_FovCtrl->m_pFovMove;
  if (m_pFovMove)
  {
    if (m_FovCtrl->m_stp >= SLODWORD(m_pFovMove->max_length))
    {
      goto LABEL_8;
    }
    FovCtrlSystem(m_FovCtrl, &gFOVY2_OW_Param);
    gFOVY2_OW_Use = 1;
  }
  else
  {
  }
LABEL_8:
  if (!gDof2_Use)
    goto LABEL_32;
  v12 = gDof2_Frame_Now + 1.0;
  gDof2_Frame_Now = v12;
  if (v12 > gDof2_Frame_End)
  {
    gDof2_Frame_Now = gDof2_Frame_End;
  }
  v15 = gDof2_Frame_End;
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
  {
LABEL_32:
    m_UpVCtrl = wk->m_CamMov->m_UpVCtrl;
    m_pUpVMove = m_UpVCtrl->m_pUpVMove;
    if (!m_pUpVMove)
      return v5;
    goto LABEL_33;
  }
  mDof = Instance->mDof;
  if (!op_Inequality(Instance->mDof, 0, 0))
    goto LABEL_32;
  v25 = (f32)(1.0 / v15) * gDof2_Frame_Now;
  monitor = mDof[2].monitor;
  if (v25 <= 1.0)
    v28 = v25;
  else
    v28 = 1.0;
  if (v25 < 0.0)
    v28 = 0.0;
  v29 = v26[95] + (f32)(v28 * (f32)(v26[98] - v26[95]));
  v30 = v26[96] + (f32)(v28 * (f32)(v26[99] - v26[96]));
  v31 = v26[97] + (f32)(v28 * (f32)(v26[100] - v26[97]));
  v32 = Allocate(UnityEngine_Rendering_Universal_DepthOfFieldModeParameter);
  _ctor(v32, 2, 1, 0);
  (*(*(u64 *)monitor + 440))(monitor, v32, *(u64 *)(*(u64 *)monitor + 448));
  klass = mDof[4].klass;
  v34 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v34, v29, 1, 0);
  (*(klass->_1.image + 55))(klass, v34, *((u64 *)klass->_1.image + 56));
  m_CachedPtr = mDof[4].m_CachedPtr;
  v36 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v36, v30, 1, 0);
  (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v36, *(u64 *)(*(u64 *)m_CachedPtr + 448));
  v37 = mDof[4].monitor;
  v38 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v38, v31, 1, 0);
  (*(*(u64 *)v37 + 440))(v37, v38, *(u64 *)(*(u64 *)v37 + 448));
  SetForceActiveDofSetting(Instance, 1, 0);
  m_UpVCtrl = wk->m_CamMov->m_UpVCtrl;
  m_pUpVMove = m_UpVCtrl->m_pUpVMove;
  if (m_pUpVMove)
  {
LABEL_33:
    if (m_UpVCtrl->m_stp < SLODWORD(m_pUpVMove->max_length))
    {
      UpVCtrlSystem(m_UpVCtrl, &gUpV2_OW_Param);
      gUpV2_OW_Use = 1;
    }
  }
  return v5;
}

// 0x1efc030
static void SetEnemyCPos(void) {
  f32 v5;
  f32 height;
  f32 v7;
  s32 v8;
  s64 i;
  V_POSITION_WORK *nml;
  const char *namespaze;
  f32 v12;
  f32 v13;
  u16 v14;
  s32 v15;
  f32 v17;
  f32 v18;
  f32 x;
  s64 v21;
  s32 v24;

  if ((u32)(camera_bossmode - 1) < 2)
  {
    v24 = 48;
    do
    {
      --v24;
    }
    while (v24);
    v5 = 0.0;
    height = 70.0;
    v7 = 0.0;
    v8 = 1;
    goto LABEL_19;
  }
  v5 = 0.0;
  height = 70.0;
  v7 = 0.0;
  v8 = 1;
  for (i = 32; i != 416; i += 8)
  {
    namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + i))->_1.namespaze;
    if (namespaze && (namespaze[832] & 2) != 0)
    {
      v12 = *((f32 *)namespaze + 41);
      v13 = *((f32 *)namespaze + 43);
      v14 = *((u16 *)namespaze + 306);
      v15 = *((u32 *)namespaze + 154);
      v7 = v7 + v12;
      v5 = v5 + v13;
      nml = sBtlGetVisualData(v14, v15)->nml;
      ++v8;
      if (height < nml->height)
        height = nml->height;
    }
  }
  if (v8 >= 1)
  {
LABEL_19:
    vct_A.z = v5;
    v17 = v8;
    vct_A.x = v7;
    vct_A.y = 0.0;
    vct_A.w = 1.0;
    v18 = 1.0 / v17;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v18);
    x = vct_A.x;
    v21 = *(u64 *)&vct_A.z;
    goto LABEL_30;
  }
  x = 0.0;
  v21 = 0x3F80000000000000LL;
LABEL_30:
  vct_A.x = x;
  vct_A.y = height;
  *(u64 *)&vct_A.z = v21;
}

// 0x1efc3b0
static void MenuStealth(s32 mode) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v5;
  dds3Basic_t *p_pBasic;

  PChara = sBtlGetPChara();
  Nakama = sBtlGetNakama(0);
  v5 = sBtlGetNakama(1);
  p_pBasic = &PChara->pBasic;
  if (mode)
  {
    dds3ObjectBaseOnFlag(p_pBasic, 0x400000u);
    if (Nakama)
      dds3ObjectBaseOnFlag(&Nakama->pBasic, 0x400000u);
    if (v5)
      dds3ObjectBaseOnFlag(&v5->pBasic, 0x400000u);
  }
  else
  {
    dds3ObjectBaseOffFlag(p_pBasic, 0x400000u);
    if (Nakama)
      dds3ObjectBaseOffFlag(&Nakama->pBasic, 0x400000u);
    if (v5)
      dds3ObjectBaseOffFlag(&v5->pBasic, 0x400000u);
  }
}

// 0x1efc480
void sBtlMenuOpen(void) {
  signed s32 status;
  s32 v6;

  status = wk->status;
  if (status < 0)
    v6 = 4;
  else
    v6 = 14;
  sBtlSetMode(v6);
}

// 0x1efcae0
void sBtlMenuClose(void) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v6;

  if (wk->cmbSkl->bRun)
  {
    goto LABEL_8;
  }
  sBtlSetMode(2);
LABEL_8:
  PChara = sBtlGetPChara();
  Nakama = sBtlGetNakama(0);
  v6 = sBtlGetNakama(1);
  dds3ObjectBaseOffFlag(&PChara->pBasic, 0x400000u);
  if (Nakama)
    dds3ObjectBaseOffFlag(&Nakama->pBasic, 0x400000u);
  if (v6)
    dds3ObjectBaseOffFlag(&v6->pBasic, 0x400000u);
}

// 0x1efcc30
bool sBtlChkMenu2Open(void) {
  if (wk->mode == 5)
    return 1;
  return wk->scene->camera->mode == 14;
}

// 0x1efcd00
s32 sBtlBossStartSub(SBTLCAMERA_WORK *wk) {
  SBATTLE_WORK *v4;
  u32 status4;

  v4 = wk;
  status4 = v4->status4;
  ++v4->gStartBossCamCnt;
  v4->status4 = status4 | 4;
  return 0;
}

// 0x1efcd80
void sBtlSetFollowUpCameraPar(void) {
  void *Asset;
  s64 naturalAligment;
  void *v5;
  void *v6;
  s64 v8;

  Asset = LoadAsset(_Ctrl_k__BackingField, "battle", "BattleCameraPar", 0);
  if (!Asset)
  {
    v6 = 0;
    battleCameraPar = 0;
    goto LABEL_16;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == BattleCameraPar)
      v5 = Asset;
    else
      v5 = 0;
  }
  else
  {
    v5 = 0;
  }
  battleCameraPar = v5;
  if (Asset->klass->_2.naturalAligment >= (u32)v8)
  {
    if (Asset->klass->_2.typeHierarchy[v8 - 1] == BattleCameraPar)
      v6 = Asset;
    else
      v6 = 0;
  }
  else
  {
    v6 = 0;
  }
LABEL_16:
}

// 0x1efcf60
void sBtlGetAnalogSensitivity(f32 *InSen, f32 *SpdSen) {
  s32 ConfigGAMEPAD;
  void *v6;
  void *v7;
  s64 v8;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(2, 0);
  v6 = NewSpecific(f32, 5u);
  InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__898412EF024A2555B05E6C46D06F26E6D93C15536E02A463F5DD9EAAF7438C62, 0);
  v7 = NewSpecific(f32, 5u);
  InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__4FBD22705A682B672F3E396F39DAE253201A37BD45082456C1502991514365A8, 0);
  v8 = 4 * ConfigGAMEPAD;
  *InSen = *(f32 *)((char *)&v6[2].klass + v8);
  *SpdSen = *(f32 *)((char *)&v7[2].klass + v8);
}

// 0x1ef8930
void sBtlInputFollowUp(SBTLCAMERA_WORK *_wk, sdfVector2_t *_followUpAngle) {
  u8 AnalogRX;
  u8 AnalogRY;
  f32 v8;
  f32 v9;
  f32 v11;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  bool v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  _BOOL4 v25;
  f32 GazeOff_GunMode_RY;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 *p_y;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 y;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  s64 SpdSen;

  SpdSen = 0;
  goto LABEL_3;
LABEL_7:
  AnalogRX = dds3PadGetAnalogRX(0);
  AnalogRY = dds3PadGetAnalogRY(0);
  v8 = AnalogRX;
  if (cfgGetConfigGAME(5, 0))
  {
    if (AnalogRX < 0x81u)
    {
      if ((AnalogRX & 0x80) == 0)
        v8 = (f32)(128.0 - v8) + 128.0;
    }
    else
    {
      v8 = 128.0 - (f32)(v8 + -128.0);
    }
  }
  v9 = AnalogRY;
  if (cfgGetConfigGAME(4, 0))
  {
    if (AnalogRY < 0x81u)
    {
      if ((AnalogRY & 0x80) == 0)
        v9 = (f32)(128.0 - v9) + 128.0;
    }
    else
    {
      v9 = 128.0 - (f32)(v9 + -128.0);
    }
  }
  if ((wk->mode | 4) == 4)
  {
    v9 = 128.0;
    v11 = 128.0;
    goto LABEL_27;
  }
  if ((wk->status4 & 0x80000) != 0)
  {
    v8 = 128.0;
    v9 = 128.0;
  }
  if (IsAction(4))
  {
    v9 = 128.0;
    v11 = 128.0;
  }
  else
  {
    v11 = v8;
  }
LABEL_27:
  sBtlGetAnalogSensitivity((f32 *)&SpdSen + 1, &SpdSen);
  v13 = *((f32 *)&SpdSen + 1);
  v14 = *((f32 *)&SpdSen + 1) + 128.0;
  v15 = 128.0 - *((f32 *)&SpdSen + 1);
  if (v11 <= (f32)(*((f32 *)&SpdSen + 1) + 128.0))
  {
    if (v11 >= v15)
      goto LABEL_53;
    if (v15 == 0.0)
    {
      v22 = 0.0;
    }
    else
    {
      v20 = 1.0;
      v21 = (f32)((f32)(128.0 - v11) - *((f32 *)&SpdSen + 1)) / v15;
      if (v21 <= 1.0)
        v20 = (f32)((f32)(128.0 - v11) - *((f32 *)&SpdSen + 1)) / v15;
      v18 = v21 < 0.0;
      v22 = 0.0;
      if (!v18)
        v22 = v20;
    }
    followUpAngle->x = followUpAngle->x
                            - (f32)((f32)(v22 * *(f32 *)&SpdSen) * VRF);
LABEL_52:
    gAuto_ManualKaiten_Cnt = 60;
    gAuto_ManualKaiten_Input = 1;
LABEL_53:
    v25 = v9 >= v15 && v9 > v14;
    if (sBtlCheckGunMode())
    {
      if (wk->CameraGazeOff)
      {
        GazeOff_GunMode_RY = wk->GazeOff_GunMode_RY;
        v27 = -(f32)(360.0 - GazeOff_GunMode_RY);
        if (GazeOff_GunMode_RY <= 180.0)
          v27 = wk->GazeOff_GunMode_RY;
        if (v9 < v15)
        {
          if (v15 == 0.0)
          {
            v38 = 0.0;
          }
          else
          {
            v36 = 1.0;
            v37 = (f32)((f32)(128.0 - v9) - v13) / v15;
            if (v37 <= 1.0)
              v36 = (f32)((f32)(128.0 - v9) - v13) / v15;
            v18 = v37 < 0.0;
            v38 = 0.0;
            if (!v18)
              v38 = v36;
          }
          v39 = v27
              + (f32)((f32)(v38 * *(f32 *)&SpdSen) * VRF);
          GazeOff_GunMode_RY = 100.0;
          if (v39 <= 100.0)
            GazeOff_GunMode_RY = v39;
        }
        else if (v25)
        {
          if (v15 == 0.0)
          {
            v30 = 0.0;
          }
          else
          {
            v28 = 1.0;
            v29 = (f32)((f32)(v9 + -128.0) - v13) / v15;
            if (v29 <= 1.0)
              v28 = (f32)((f32)(v9 + -128.0) - v13) / v15;
            v18 = v29 < 0.0;
            v30 = 0.0;
            if (!v18)
              v30 = v28;
          }
          v40 = v27
              - (f32)((f32)(v30 * *(f32 *)&SpdSen) * VRF);
          GazeOff_GunMode_RY = -50.0;
          if (v40 >= -50.0)
            GazeOff_GunMode_RY = v40;
        }
        v41 = sub_188E3E0(GazeOff_GunMode_RY + 360.0);
        y = followUpAngle->y;
        p_y = &followUpAngle->y;
        v33 = y;
        wk->GazeOff_GunMode_RY = v41;
        v34 = 360.0 - y;
        goto LABEL_91;
      }
      v35 = followUpAngle->y;
      p_y = &followUpAngle->y;
      v33 = v35;
      wk->GazeOff_GunMode_RY = 0.0;
      goto LABEL_116;
    }
    v32 = followUpAngle->y;
    p_y = &followUpAngle->y;
    v33 = v32;
    wk->GazeOff_GunMode_RY = 0.0;
    v34 = 360.0 - v32;
LABEL_91:
    v43 = -v34;
    if (v33 <= 180.0)
      v43 = v33;
    if (v9 < v15)
    {
      if (v15 == 0.0)
      {
        v49 = 0.0;
      }
      else
      {
        v47 = 1.0;
        v48 = (f32)((f32)(128.0 - v9) - v13) / v15;
        if (v48 <= 1.0)
          v47 = (f32)((f32)(128.0 - v9) - v13) / v15;
        v18 = v48 < 0.0;
        v49 = 0.0;
        if (!v18)
          v49 = v47;
      }
      v50 = v43 + (f32)((f32)(v49 * *(f32 *)&SpdSen) * VRF);
      if (v50 <= 10.0)
        v33 = v50;
      else
        v33 = 10.0;
      goto LABEL_115;
    }
    if (v25)
    {
      if (v15 == 0.0)
      {
        v46 = 0.0;
      }
      else
      {
        v44 = 1.0;
        v45 = (f32)((f32)(v9 + -128.0) - v13) / v15;
        if (v45 <= 1.0)
          v44 = (f32)((f32)(v9 + -128.0) - v13) / v15;
        v18 = v45 < 0.0;
        v46 = 0.0;
        if (!v18)
          v46 = v44;
      }
      v51 = v43 - (f32)((f32)(v46 * *(f32 *)&SpdSen) * VRF);
      if (v51 >= -30.0)
        v33 = v51;
      else
        v33 = -30.0;
LABEL_115:
      *p_y = v33;
    }
LABEL_116:
    *p_y = sub_188E3E0(v33 + 360.0);
    return;
  }
  else
  {
    if (v15 == 0.0)
    {
      v19 = 0.0;
    }
    else
    {
      v16 = 1.0;
      v17 = (f32)((f32)(v11 + -128.0) - *((f32 *)&SpdSen + 1)) / v15;
      if (v17 <= 1.0)
        v16 = (f32)((f32)(v11 + -128.0) - *((f32 *)&SpdSen + 1)) / v15;
      v18 = v17 < 0.0;
      v19 = 0.0;
      if (!v18)
        v19 = v16;
    }
    followUpAngle->x = followUpAngle->x
                            + (f32)((f32)(v19 * *(f32 *)&SpdSen) * VRF);
    goto LABEL_52;
  }
  goto LABEL_52;
LABEL_3:
  if (!sBtlIsBattleKey(4125, 1))
    goto LABEL_7;
}

// 0x1efd080
void sBtlInputFollowUp_Menu2(SBTLCAMERA_WORK *_wk, sdfVector2_t *_followUpAngle) {
  u8 AnalogRX;
  f32 x;
  f32 v6;
  f32 v8;
  f32 v9;
  f32 v10;
  bool v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  _BOOL4 IsAction;
  bool v18;
  _BOOL4 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  s64 SpdSen;

  SpdSen = 0;
  AnalogRX = dds3PadGetAnalogRX(1);
  x = followUpAngle->x;
  v6 = AnalogRX;
  if (cfgGetConfigGAME(5, 0))
  {
    if (AnalogRX < 0x81u)
    {
      if ((AnalogRX & 0x80) == 0)
        v6 = (f32)(128.0 - v6) + 128.0;
    }
    else
    {
      v6 = 128.0 - (f32)(v6 + -128.0);
    }
  }
  sBtlGetAnalogSensitivity((f32 *)&SpdSen + 1, &SpdSen);
  v8 = 128.0 - *((f32 *)&SpdSen + 1);
  if (v6 <= (f32)(*((f32 *)&SpdSen + 1) + 128.0))
  {
    if (v6 >= v8)
      goto LABEL_33;
    if (v8 == 0.0)
    {
      v15 = 0.0;
    }
    else
    {
      v13 = (f32)((f32)(128.0 - v6) - *((f32 *)&SpdSen + 1)) / v8;
      v14 = 1.0;
      if (v13 <= 1.0)
        v14 = v13;
      v11 = v13 < 0.0;
      v15 = 0.0;
      if (!v11)
        v15 = v14;
    }
    v16 = followUpAngle->x
        - (f32)((f32)(v15 * *(f32 *)&SpdSen) * VRF);
  }
  else
  {
    if (v8 == 0.0)
    {
      v12 = 0.0;
    }
    else
    {
      v9 = (f32)((f32)(v6 + -128.0) - *((f32 *)&SpdSen + 1)) / v8;
      v10 = 1.0;
      if (v9 <= 1.0)
        v10 = v9;
      v11 = v9 < 0.0;
      v12 = 0.0;
      if (!v11)
        v12 = v10;
    }
    v16 = followUpAngle->x
        + (f32)((f32)(v12 * *(f32 *)&SpdSen) * VRF);
  }
  followUpAngle->x = v16;
LABEL_33:
  followUpAngle->y = sub_188E3E0(followUpAngle->y + 360.0);
  IsAction = IsAction(13);
  v18 = IsAction(15);
  v19 = IsAction(16);
  if (!v18)
    goto LABEL_39;
  v20 = followUpAngle->x;
  if (followUpAngle->x <= 250.0)
  {
    if (v20 >= 110.0)
      goto LABEL_39;
    v21 = -110.0;
  }
  else
  {
    v21 = -250.0;
  }
  followUpAngle->x = v20 + (f32)((f32)(v20 + v21) * -0.3);
LABEL_39:
  if (wk->encountno != 60)
    goto LABEL_48;
  v22 = followUpAngle->x;
  if (followUpAngle->x <= 270.0)
  {
    if (v22 >= 90.0)
      goto LABEL_48;
    v23 = -90.0;
  }
  else
  {
    v23 = -270.0;
  }
  followUpAngle->x = v22 + (f32)((f32)(v22 + v23) * -0.3);
LABEL_48:
  if (IsAction || v19)
    followUpAngle->x = x;
}

// 0x1efd3f0
static bool SetPara(SBTLCAMERA_WORK *wk) {
  SBTLUNIT_WORK *PChara;
  s32 CameraHighTargetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *Nakama;
  dds3ModelHandle_t *v12;
  dds3Basic_t *cm;
  dds3Basic_t *p_cm;
  sdfVector4_t *workdata;
  f32 v23;
  f32 v24;
  struct sdfVector2_t v28;
  s32 encountno;
  s32 v31;
  f32 v33;
  long f64 v34;
  S_CameraMove *m_CamMov;
  f32 v36;
  f32 v37;
  SBTLUNIT_WORK *v40;
  SBATTLE_WORK *v43;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  long f64 v49;
  long f64 v50;
  s64 v51;
  f32 v52;
  f32 v53;
  f32 v55;
  s64 v58;
  s64 v59;
  long f64 v60;
  __n128 v61;
  sdfVector4_t *p_targetpos;
  s32 Node;
  SBTLUNIT_WORK *v64;
  long f64 v67;
  long f64 v68;
  u32 v69;
  SBTLUNIT_WORK *TargetUnit;
  s32 side;
  SBTLUNIT_WORK *v72;
  f32 v73;
  u32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 v80;
  u32 v81;
  f32 v82;
  f32 v83;
  u32 v85;
  SBATTLE_WORK *v86;
  SBTLSCENE_WORK *v87;
  s32 v88;
  SBTLUNIT_WORK *pNakama0;
  long f64 v90;
  S_PosCtrl *m_PosCtrlCam;
  s32 m_cnt;
  f32 m_fFrm;
  f32 v94;
  SBTLUNIT_WORK *v95;
  f32 v96;
  long f64 v97;
  long f64 v98;
  SBTLUNIT_WORK *v99;
  long f64 v100;
  f32 v102;
  f32 v103;
  SBTLSCENE_WORK *v105;
  f32 v106;
  S_PosCtrl *v107;
  f32 v108;
  f32 v109;
  SBTLUNIT_WORK *v110;
  f32 v111;
  long f64 v112;
  long f64 v113;
  long f64 v115;
  long f64 v116;
  SBTLSCENE_WORK *v118;
  f32 v119;
  f32 v120;
  f32 v121;
  f32 v122;
  long f64 v123;
  long f64 v124;
  sdfVector4_t *p_camerapos;
  f32 v127;
  f32 v128;
  f32 v129;
  f32 v130;
  f32 v131;
  long f64 v132;
  long f64 v134;
  SBTLSCENE_WORK *v136;
  s32 v137;
  f32 v139;
  f32 v140;
  f32 v141;
  f32 v142;
  long f64 v143;
  f32 v144;
  f32 v145;
  f32 v146;
  f32 v147;
  SBATTLE_WORK *v148;
  s32 v149;
  f32 v150;
  u32 v151;
  long f64 v152;
  f32 v153;
  SBTLUNIT_WORK *v155;
  SBATTLE_WORK *v158;
  f32 v159;
  f32 v160;
  f32 v161;
  f32 v162;
  f32 v163;
  f32 v164;
  f32 v165;
  f32 v166;
  f32 camPosSlpTime;
  f32 camPosSlpCnt;
  u32 v169;
  SBATTLE_WORK *v170;
  s32 v171;
  f32 v172;
  f32 v173;
  f32 v174;
  f32 v175;
  long f64 v176;
  f32 v177;
  long f64 v178;
  SBTLSCENE_WORK *v180;
  f32 v181;
  f32 v182;
  f32 v183;
  u32 v184;
  SBTLUNIT_WORK *v185;
  SBTLUNIT_WORK *v187;
  f32 v189;
  f32 v190;
  f32 v191;
  f32 v192;
  f32 v193;
  f32 v194;
  f32 v195;
  float32x2_t v196;
  int32x2_t v197;
  float32x2_t v198;
  f32 v199;
  s32 devilid;
  u32 v201;
  f32 v202;
  u32 v203;
  f32 v204;
  f32 v205;
  f32 v206;
  SBTLUNIT_WORK *v208;
  SBTLCAMERA_WORK *p_fields;
  u32 v211;
  f32 v212;
  f32 v213;
  f32 v214;
  f32 v215;
  f32 v216;
  f32 v217;
  f32 v218;
  u64 v219;
  sdfVector4_t *p_ppos;
  f32 v221;
  f32 v222;
  SBATTLE_WORK *v223;
  f32 v224;
  f32 v225;
  f32 v226;
  f32 v227;
  f32 v228;
  f32 v229;
  f32 v230;
  f32 v231;
  f32 camTgtSlpTime;
  f32 camTgtSlpCnt;
  u32 v234;
  SBATTLE_WORK *v235;
  s32 v236;
  f32 v237;
  f32 v238;
  f32 v239;
  f32 v240;
  f32 v241;
  f32 v242;
  u32 v243;
  f32 v244;
  long f64 v245;
  f32 v246;
  u32 v247;
  f32 v248;
  f32 v249;
  f32 v250;
  f32 v251;
  f32 v252;
  f32 v253;
  f32 v254;
  bool v255;
  bool v257;
  f32 v258;
  f32 v259;
  bool v261;
  f32 v262;
  f32 v263;
  f32 v264;
  f32 v265;
  f32 v266;
  f32 v267;
  f32 v268;
  long f64 v269;
  long f64 v270;
  long f64 v271;
  long f64 v272;
  f32 v274;
  f32 v275;
  f32 v276;
  f32 v277;
  f32 v278;
  f32 v279;
  f32 v280;
  f32 v281;
  SBTLUNIT_WORK *v283;
  s64 v286;
  s64 v287;
  s64 v288;
  f32 v289;
  f32 v290;
  SBTLSCENE_WORK *v291;
  s64 v293;
  __int128 v294;
  f32 v295;
  f32 v296;
  f32 v298;
  f32 v299;
  f32 v300;
  f32 v301;
  f32 v302;
  float32x2_t v303;
  int32x2_t v304;
  f32 v305;
  f32 v306;
  f32 v307;
  f32 v308;
  float32x2_t v310;
  int32x2_t v311;
  long f64 v313;
  SBTLUNIT_WORK *v314;
  SBTLUNIT_WORK *v315;
  f32 v316;
  f32 v317;
  f32 v318;
  s32 camSlpMode;
  f32 v321;
  s32 v322;
  f32 v323;
  f32 v324;
  f32 v325;
  f32 v326;
  long f64 v327;
  f32 v328;
  long f64 v329;
  f32 v331;
  f32 v332;
  f32 v333;
  f32 v334;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  f32 v338;
  f32 v339;
  f32 v340;
  f32 v341;
  f32 v342;
  f32 v343;
  f32 v344;
  f32 v345;
  f32 v346;
  f32 v347;
  f32 v348;
  f32 v349;
  f32 v350;
  f32 v351;
  f32 v352;
  f32 height;
  f32 v354;
  s32 v355;
  f32 v356;
  f32 v357;
  u32 v358;
  f32 v359;
  f32 v361;
  f32 v362;
  f32 v363;
  f32 v364;
  f32 v365;
  f32 v366;
  u32 v367;
  f32 v368;
  f32 v369;
  f32 v370;
  SBATTLE_WORK *v373;
  SBTLSCENE_WORK *scene;
  SBTLSCENE_WORK *v375;
  SBTLSCENE_WORK *v376;
  SBTLSCENE_WORK *v377;
  SBTLSCENE_WORK *v378;
  _BOOL4 v379;
  s32 v380;
  f32 v381;
  f32 Dir180;
  f32 v384;
  f32 y;
  f32 v386;
  f32 v387;
  f32 GroundPos;
  u32 v390;
  SBATTLE_WORK *v391;
  f32 camCnt;
  f32 v393;
  f32 v394;
  f32 v395;
  f32 v396;
  f32 v397;
  f32 v398;
  f32 v399;
  f32 z;
  s64 v403;
  f32 v404;
  f32 w;
  long f64 v406;
  long f64 v407;
  long f64 v408;
  long f64 v409;
  __int128 v413;
  u32 v414;
  SBATTLE_WORK *v415;
  SBTLSCENE_WORK *v416;
  s32 v417;
  f32 v420;
  float32x2_t v422;
  float32x2_t v423;
  f32 v424;
  u64 v425;
  float32x2_t v426;
  float32x2_t v427;
  u64 v428;
  f32 v429;
  SBATTLE_WORK *v431;
  SBATTLE_WORK *v434;
  SBTLUNIT_WORK *v436;
  s64 v439;
  __int128 v442;
  SBTLSCENE_WORK *v443;
  s64 v444;
  s64 v445;
  s64 v446;
  f32 v447;
  f32 v448;
  f32 v450;
  f32 v451;
  f32 v452;
  f32 v453;
  f32 v454;
  f32 v455;
  f32 v456;
  f32 v457;
  f32 v458;
  f32 v459;
  f32 v460;
  f32 v461;
  f32 v462;
  f32 PosToDir;
  f32 LenXZ;
  f32 v469;
  f32 v470;
  f32 v471;
  f32 v472;
  long f64 v473;
  long f64 v474;
  long f64 v475;
  f32 v476;
  struct sdfVector4_t targetpos;
  f32 v483;
  f32 v484;
  f32 v485;
  f32 v486;
  f32 v487;
  f32 v488;
  f32 v489;
  f32 v490;
  f32 v491;
  f32 v492;
  f32 v493;
  f32 v494;
  f32 v495;
  f32 v496;
  f32 v497;
  f32 v498;
  f32 v499;
  f32 v500;
  f32 v501;
  f32 v502;
  f32 v503;
  f32 v504;
  f32 v505;
  f32 v506;
  f32 v507;
  f32 v508;
  f32 v509;
  f32 v510;
  f32 v511;
  sdfVector4_t *v514;
  sdfVector4_t *p_vertical;
  u32 v518;
  f32 gFOVY2_OW_Param_local;
  f32 v524;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *v527;
  dds3Basic_t *v528;
  f32 v529;
  f32 v530;
  f32 v531;
  f32 v532;
  f32 v533;
  f32 v534;
  f32 v535;
  f32 v536;
  s32 mode;
  dds3Basic_t *v538;
  f32 v539;
  f32 v540;
  f32 v541;
  f32 v542;
  f32 v543;
  f32 v544;
  f32 v545;
  f32 v546;
  struct sdfVector4_t v549;
  sdfVector4_t *p_direction;
  f32 v557;
  f32 v558;
  f32 v559;
  f32 v560;
  long f64 v561;
  long f64 v562;
  s64 v563;
  f32 v564;
  f32 v565;
  f32 fa;
  f32 fb;
  f32 f;
  f32 x;
  f32 xa;
  f32 v572;
  f32 v573;
  SBTLUNIT_WORK *ActionUnit;
  f32 v575;
  f32 v576;
  struct sdfVector4_t v577;
  struct sdfVector4_t v580;
  f32 v583;
  s64 ZeroZ;
  s64 ZeroY;
  s64 v586;
  s64 v587;
  s64 v588;
  s64 v589;
  sdfVector4_t HelperPos;
  s64 ToZ;
  s64 v592;
  sdfVector4_t ppos;
  s64 v594;
  s64 v595;
  s64 v596;
  s64 v597;
  s64 v598;
  s64 v599;
  f32 v600;
  s64 ToX;
  s64 v602;
  s64 v603;
  __int128 v604;
  sdfVector4_t vResTgt;
  sdfVector4_t cameraPos;
  sdfVector4_t v607;
  sdfVector4_t vResPos;
  s64 v609;
  s64 v610;
  sdfVector4_t v611;
  sdfVector4_t v612;
  sdfVector4_t v613;
  sdfVector4_t v614;
  sdfVector4_t v615;
  sdfVector4_t v616;
  sdfVector4_t v617;
  sdfVector4_t v618;
  sdfVector4_t v619;
  sdfVector4_t v620;
  sdfVector4_t v621;
  sdfVector4_t v622;
  sdfVector4_t v623;
  sdfVector4_t v624;
  sdfVector4_t v625;
  sdfVector4_t v626;

  ToX = 0;
  v600 = 0.0;
  v583 = 0.0;
  v598 = 0;
  v599 = 0;
  v596 = 0;
  v597 = 0;
  v594 = 0;
  v595 = 0;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  ToZ = 0;
  v592 = 0;
  *(u64 *)&HelperPos.x = 0;
  *(u64 *)&HelperPos.z = 0;
  v588 = 0;
  v589 = 0;
  v586 = 0;
  v587 = 0;
  ZeroZ = 0;
  ZeroY = 0;
  v609 = 0;
  v610 = 0;
  *(u64 *)&vResPos.x = 0;
  *(u64 *)&vResPos.z = 0;
  v607 = (sdfVector4_t)0;
  *(u64 *)&cameraPos.x = 0;
  *(u64 *)&cameraPos.z = 0;
  *(u64 *)&vResTgt.x = 0;
  *(u64 *)&vResTgt.z = 0;
  v604 = 0u;
  v602 = 0;
  v603 = 0;
  PChara = sBtlGetPChara();
  if (wk->CameraHighTargetUse)
  {
    CameraHighTargetID = wk->CameraHighTargetID;
    UnitMng = wk->UnitMng;
  }
  else
  {
    UnitMng = wk->UnitMng;
    CameraHighTargetID = PChara->actaiwk->targetID;
  }
  v10 = sBtlSearchUnit_ID(UnitMng, CameraHighTargetID);
  Nakama = sBtlGetNakama(0);
  sBtlGetNakama(1);
  v12 = Allocate(dds3ModelHandle_t);
  _ctor(v12, 0);
  *(u64 *)&vResPos.x = 0;
  *(u64 *)&vResPos.z = 0;
  *(u64 *)&vResTgt.x = 0;
  *(u64 *)&vResTgt.z = 0;
  gFOVY_OW_Use = 0;
  gFOVY2_OW_Use = 0;
  gUpV2_OW_Use = 0;
  gUpV2_OW_Param = 0.0;
  gHokan_OW_Use = 0;
  gHokan_OW_Param = 0.5;
  gFOVY_OW_Param = gFreeCam_Fov;
  p_cm = &wk->cm;
  cm = wk->cm;
  if (!cm)
    return 0;
  workdata = cm->workdata;
  if (!PChara)
    return 0;
  v23 = 0.0;
  v24 = 1.0;
  switch (wk->mode)
  {
    case 0:
      if (tipsProcessCheck())
        goto LABEL_540;
      if (wk->scene->camCnt)
        goto LABEL_369;
      v28 = *(sdfVector2_t *)&battleCameraPar->initRotX;
      *(u64 *)&wk->CameraLockOnTargetPos.x = 0;
      wk->CameraLockOnTargetPos.z = 0.0;
      wk->followUpAngle = v28;
      wk->scene->camera->CameraLockOnNone = 1;
      wk->CameraHighTargetUse = 0;
      wk->CameraHighTargetID = -1;
      gRingTgt_Dir = 0.0;
      gReverseCnt = 0;
      sBtlClearZoom();
      encountno = wk->encountno;
      if (encountno <= 43)
      {
        if (encountno == 26)
        {
          wk->followUpAngle.x = 0.0;
          gRingTgt_Dir = 180.0;
          wk->targetpos.z = -150.0;
          wk->camerapos.z = 0.0;
          *(u64 *)&wk->targetpos.x = 0xC310000042480000LL;
          *(u64 *)&wk->camerapos.x = 0xC316000042480000LL;
LABEL_369:
          v373 = wk;
          if ((v373->status & 0x8000) != 0)
          {
            v373 = wk;
            scene = v373->scene;
            if (scene->camCnt >= 159)
            {
              scene = wk->scene;
              ++scene->camCnt2;
              v420 = 0.0;
              HIDWORD(v604) = 0;
              v422.n64_u64[0] = *(u64 *)&gStartCam_TgtEnemySmnPos.x;
              v423.n64_u64[0] = vsub_f32(*(float32x2_t *)&gStartCam_TgtGoalPos.x, v422).n64_u64[0];
              if (gStartCam_Nml <= 1.0)
                v424 = gStartCam_Nml;
              else
                v424 = 1.0;
              if (gStartCam_Nml >= 0.0)
                v420 = v424;
              v425 = vadd_f32(v422, vmul_n_f32(v423, v420)).n64_u64[0];
              *(u64 *)&wk->targetpos.x = v425;
              *(u64 *)&v604 = v425;
              *((f32 *)&v604 + 2) = gStartCam_TgtEnemySmnPos.z
                                    + (f32)(v420 * (f32)(gStartCam_TgtGoalPos.z - gStartCam_TgtEnemySmnPos.z));
              wk->targetpos.z = *((f32 *)&v604 + 2);
              v426.n64_u64[0] = *(u64 *)&gStartCam_CamEnemySmnPos.x;
              v427.n64_u64[0] = *(u64 *)&gStartCam_CamGoalPos.x;
              v607.w = 0.0;
              v428 = vadd_f32(v426, vmul_n_f32(vsub_f32(v427, v426), v420)).n64_u64[0];
              *(u64 *)&wk->camerapos.x = v428;
              *(u64 *)&v607.x = v428;
              v429 = gStartCam_Nml + 0.05;
              v607.z = gStartCam_CamEnemySmnPos.z
                            + (f32)(v420 * (f32)(gStartCam_CamGoalPos.z - gStartCam_CamEnemySmnPos.z));
              wk->camerapos.z = v607.z;
              gStartCam_Nml = v429;
              if (v429 > 1.0)
              {
                gStartCam_Nml = 1.0;
              }
              v431 = wk;
              ++v431->scene->camCnt;
              if ((v431->status4 & 0x80) == 0)
              {
                v431 = wk;
                if (v431->step <= 0)
                {
                  v431 = wk;
                  v431->status4 |= 0x80u;
                  sBtlNakamaSetUp(0);
                  sBtlNakamaSetUp(1);
                }
              }
              v434 = wk;
              if ((v434->status4 & 0x80) != 0)
              {
                v434 = wk;
                if (v434->scene->camCnt2 >= 17)
                {
                  v434 = wk;
                  v434->step = 1;
                }
              }
              goto LABEL_492;
            }
          }
          v375 = wk->scene;
          if (v375->major == 37)
          {
            v375 = wk->scene;
            if (v375->minor == 22)
              goto LABEL_399;
          }
          v376 = wk->scene;
          if (v376->major == 39)
          {
            v376 = wk->scene;
            if (v376->minor == 22)
              goto LABEL_399;
          }
          v377 = wk->scene;
          if (v377->major == 37)
          {
            v377 = wk->scene;
            if (v377->minor == 17)
              goto LABEL_399;
          }
          v378 = wk->scene;
          if (v378->major != 37)
            goto LABEL_676;
          v378 = wk->scene;
          if (v378->minor == 18)
          {
LABEL_399:
            v379 = 1;
          }
          else
          {
LABEL_676:
            v443 = wk->scene;
            if (v443->major == 39)
            {
              v443 = wk->scene;
              v379 = v443->minor == 18;
            }
            else
            {
              v379 = 0;
            }
          }
          v380 = wk->encountno;
          if (v380 <= 43)
          {
            if ((u32)v380 <= 0x2B && ((1 << v380) & 0x80404000000LL) != 0)
              goto LABEL_410;
          }
          else if ((u32)v380 <= 0x3A && ((1 << v380) & 0x5CC400000000000LL) != 0 || v380 == 534 || v380 == 537)
          {
            goto LABEL_410;
          }
          if (!v379)
          {
            v386 = PChara->pos.x;
            y = 0.0;
            v387 = 0.0;
            goto LABEL_420;
          }
LABEL_410:
          v381 = wk->followUpAngle.x;
          Dir180 = sBtlGetDir180(v381);
          if (wk->battlemode == 3)
            v384 = 650.0;
          else
            v384 = 750.0;
          sBtlGetMoveXZ(0.0, 0.0, Dir180, v384, (f32 *)&v587 + 1, &v587);
          y = PChara->pos.y;
          v386 = PChara->pos.x + *((f32 *)&v587 + 1);
          v387 = PChara->pos.z + *(f32 *)&v587;
LABEL_420:
          *(f32 *)&v604 = v386;
          *((f32 *)&v604 + 2) = v387;
          GroundPos = sBtlGetGroundPos(v386, v387);
          HIDWORD(v604) = 0;
          *((f32 *)&v604 + 1) = (f32)(y + -120.0) + GroundPos;
          v391 = wk;
          camCnt = v391->scene->camCnt;
          if ((f32)(camCnt * 0.35) <= 45.0)
            v393 = camCnt * 0.35;
          else
            v393 = 45.0;
          if (!v390)
          {
            v391 = wk;
            camCnt = v391->scene->camCnt;
          }
          v394 = camCnt + camCnt;
          if (v394 <= 100.0)
            v395 = v394;
          else
            v395 = 100.0;
          v396 = wk->followUpAngle.x + 35.0;
          if (!v390)
          {
            v391 = wk;
          }
          v397 = v396 - v393;
          v398 = 500.0;
          if (v391->battlemode == 3)
            v398 = 400.0;
          v399 = v395 + v398;
          sBtlGetMoveXZ(0.0, 0.0, v397, v399, (f32 *)&v586 + 1, &v586);
          v607.x = *(f32 *)&v604 + *((f32 *)&v586 + 1);
          v607.y = *((f32 *)&v604 + 1);
          v607.z = *((f32 *)&v604 + 2) + *(f32 *)&v586;
          if (wk->scene->camCnt)
          {
            z = wk->camerapos.z;
            v403 = *(u64 *)&wk->camerapos.x;
          }
          else
          {
            *(u64 *)&wk->targetpos.x = v604;
            z = v607.z;
            v403 = *(u64 *)&v607.x;
            v404 = *((f32 *)&v604 + 2);
            *(u64 *)&wk->camerapos.x = *(u64 *)&v607.x;
            wk->camerapos.z = z;
            wk->targetpos.z = v404;
          }
          w = wk->camerapos.w;
          sub_1B332C0(0, *(f32 *)&v403, *((f32 *)&v403 + 1), z, w);
          *(__n128 *)&v406 = sub_1B33480(0, 0.1);
          sub_1B335A0(&vResPos, 0, v406);
          sub_1B332C0(0, v607.x, v607.y, v607.z, v607.w);
          sub_1B33480(0, 0.9);
          sub_1B33360(0, vResPos.x, vResPos.y, vResPos.z, vResPos.w);
          *(__n128 *)&v407 = sub_1B33520(0);
          sub_1B335A0(&wk->camerapos, 0, v407);
          sub_1B332C0(0, wk->targetpos.x, wk->targetpos.y, wk->targetpos.z, wk->targetpos.w);
          *(__n128 *)&v408 = sub_1B33480(0, 0.1);
          sub_1B335A0(&vResTgt, 0, v408);
          sub_1B332C0(0, *(f32 *)&v604, *((f32 *)&v604 + 1), *((f32 *)&v604 + 2), *((f32 *)&v604 + 3));
          sub_1B33480(0, 0.9);
          sub_1B33360(0, vResTgt.x, vResTgt.y, vResTgt.z, vResTgt.w);
          *(__n128 *)&v409 = sub_1B33520(0);
          sub_1B335A0(&wk->targetpos, 0, v409);
          gStartCam_TgtEnemySmnPos.x = wk->targetpos.x;
          *(u64 *)&v413 = *(u64 *)&wk->targetpos.y;
          *((u64 *)&v413 + 1) = *(u64 *)&wk->camerapos.x;
          *(_OWORD *)&gStartCam_TgtEnemySmnPos.y = v413;
          *(f32 *)&v413 = wk->camerapos.z;
          gStartCam_Nml = 0.0;
          LODWORD(gStartCam_CamEnemySmnPos.z) = v413;
          v415 = wk;
          if (v415->encount_fieldmap_load_done)
          {
            if (v414)
            {
LABEL_452:
              v416 = v415->scene;
              v417 = v416->camCnt;
LABEL_453:
              v416->camCnt = v417 + 1;
LABEL_492:
              sBtlBossStartSub(sBtlCamera);
              sBtlGetIdling_HD(wk, PChara, v436, &vResPos, &vResTgt);
              v439 = *(u64 *)&vResPos.x;
              gStartCam_TgtGoalPos.x = vResTgt.x;
              *(u64 *)&v442 = *(u64 *)&vResTgt.y;
              *((u64 *)&v442 + 1) = v439;
              *(_OWORD *)&gStartCam_TgtGoalPos.y = v442;
              gStartCam_CamGoalPos.z = vResPos.z;
              if (wk->bBfrBtlEnd)
              {
                sBtlSetMode(2);
                wk->modeOld = 2;
              }
              goto LABEL_540;
            }
          }
          else
          {
            if (!v414)
            {
              v415 = wk;
            }
            v416 = v415->scene;
            if (v416->camCnt)
              goto LABEL_492;
            v417 = 0;
            goto LABEL_453;
          }
          v415 = wk;
          goto LABEL_452;
        }
        if (encountno != 43)
          goto LABEL_369;
      }
      else if (encountno != 54)
      {
        if (encountno != 59)
          goto LABEL_369;
        v31 = 12;
        goto LABEL_306;
      }
      v31 = 4;
LABEL_306:
      SetAction(v31);
      goto LABEL_369;
    case 1:
      v33 = CameraMoveSystem(wk);
      v24 = sub_1B33E20(0, v33);
      v34 = sub_1B33D20(0, v33);
      v23 = *(f32 *)&v34;
      sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, (f32 *)&ZeroZ + 1);
      m_CamMov = wk->m_CamMov;
      if (m_CamMov->m_PosCtrlTgt->m_pPosMove[0]->m_ePosType == 1)
      {
        v36 = wk->targetpos.z;
        v37 = wk->targetpos.y + *(f32 *)&ZeroY;
        wk->targetpos.x = wk->targetpos.x + *((f32 *)&ZeroY + 1);
        wk->targetpos.y = v37;
        wk->targetpos.z = v36 + *((f32 *)&ZeroZ + 1);
        if (m_CamMov->m_PosCtrlCam->m_pPosMove[0]->m_ePosType != 1)
          goto LABEL_43;
      }
      else if (m_CamMov->m_PosCtrlCam->m_pPosMove[0]->m_ePosType != 1)
      {
LABEL_43:
        goto LABEL_44;
      }
      v205 = wk->camerapos.z;
      v206 = wk->camerapos.y + *(f32 *)&ZeroY;
      wk->camerapos.x = wk->camerapos.x + *((f32 *)&ZeroY + 1);
      wk->camerapos.y = v206;
      wk->camerapos.z = v205 + *((f32 *)&ZeroZ + 1);
LABEL_44:
LABEL_125:
      ++wk->scene->camCnt;
      goto LABEL_540;
    case 2:
      if (tipsProcessCheck())
        goto LABEL_540;
      v43 = wk;
      if (v43->pCamTgt != v10)
      {
        v43 = wk;
        v43->pCamTgt = v10;
        *(u64 *)&v43->camTgtConsF = 0x1400000000LL;
      }
      sBtlGetIdling_HD(wk, PChara, v40, &vResPos, &vResTgt);
      v45 = vResPos.x;
      v46 = vResPos.y;
      *(u64 *)&wk->camTgtConsF = 0;
      v48 = vResPos.z;
      v47 = vResPos.w;
      *(__n128 *)&v49 = sub_1B332C0(0, v45, v46, v48, v47);
      sub_1B335A0(&v607, 0, v49);
      *(__n128 *)&v50 = sub_1B332C0(0, vResTgt.x, vResTgt.y, vResTgt.z, vResTgt.w);
      sub_1B335A0(&v604, 0, v50);
      v51 = *(u64 *)&v607.x;
      v52 = v607.z;
      v607.y = *((f32 *)&v51 + 1) + sBtlGetGroundPos(*(f32 *)&v51, v52);
      v53 = *((f32 *)&v604 + 1);
      v55 = sBtlGetGroundPos(*(f32 *)&v604, *((f32 *)&v604 + 2));
      *((f32 *)&v604 + 1) = v53 + v55;
      if (gsBtlCamera_Hokan_Not)
      {
        v58 = *(u64 *)&v607.x;
        v59 = *(u64 *)&v607.z;
        *(__n128 *)&v60 = sub_1B332C0(0, *(f32 *)&v58, *((f32 *)&v58 + 1), *(f32 *)&v59, *((f32 *)&v59 + 1));
        sub_1B335A0(&wk->camerapos, 0, v60);
        v61 = sub_1B332C0(0, *(f32 *)&v604, *((f32 *)&v604 + 1), *((f32 *)&v604 + 2), *((f32 *)&v604 + 3));
        p_targetpos = &wk->targetpos;
LABEL_539:
        sub_1B335A0(p_targetpos, 0, *(long f64 *)&v61);
        goto LABEL_540;
      }
      if (gHokan_OW_Use)
      {
        v286 = *(u64 *)&v607.x;
        v287 = *(u64 *)&v607.z;
        v288 = v604;
        v622.w = *((f32 *)&v604 + 3);
        v289 = *((f32 *)&v604 + 2);
        v290 = *((f32 *)&v604 + 3);
        v622.w = v290;
        f = gHokan_OW_Param;
LABEL_518:
        *(u64 *)&v616.x = v286;
        *(u64 *)&v616.z = v287;
        *(u64 *)&v622.x = v288;
        v622.z = v289;
        Slerp(wk, v616, v622, f);
        v24 = 1.0;
        v23 = 0.0;
        goto LABEL_540;
      }
      camSlpMode = wk->camSlpMode;
      if (camSlpMode != 2)
      {
        if (camSlpMode == 1)
        {
          v622.w = *((f32 *)&v604 + 3);
          v289 = *((f32 *)&v604 + 2);
          v286 = *(u64 *)&v607.x;
          v287 = *(u64 *)&v607.z;
          v288 = v604;
          v450 = *((f32 *)&v604 + 3);
          v622.w = v450;
          *(f32 *)&v322 = 0.02;
        }
        else
        {
          if (camSlpMode)
            goto LABEL_540;
          v622.w = *((f32 *)&v604 + 3);
          v289 = *((f32 *)&v604 + 2);
          v286 = *(u64 *)&v607.x;
          v287 = *(u64 *)&v607.z;
          v288 = v604;
          v321 = *((f32 *)&v604 + 3);
          v622.w = v321;
          *(f32 *)&v322 = 0.5;
        }
        f = *(f32 *)&v322;
        goto LABEL_518;
      }
      v444 = *(u64 *)&v607.x;
      v445 = *(u64 *)&v607.z;
      v446 = v604;
      v623.w = *((f32 *)&v604 + 3);
      v447 = *((f32 *)&v604 + 2);
      v448 = *((f32 *)&v604 + 3);
      v623.w = v448;
      *(u64 *)&v615.x = v444;
      *(u64 *)&v615.z = v445;
      *(u64 *)&v623.x = v446;
      v623.z = v447;
      Slerp(wk, v615, v623, 1.0);
      v24 = 1.0;
      v23 = 0.0;
      wk->camSlpMode = 0;
      goto LABEL_540;
    case 4:
      if (tipsProcessCheck())
        goto LABEL_540;
      Node = sBtlGetNode();
      if (!Node)
      {
        sBtlGetIdling_HD(wk, PChara, v64, &vResPos, &vResTgt);
        HIDWORD(v604) = 0;
        v293 = *(u64 *)&vResPos.x;
        *(u64 *)&v294 = *(u64 *)&vResTgt.y;
        v295 = vResTgt.x;
        v296 = vResPos.z;
        *(f32 *)&v604 = vResTgt.x;
        *(u64 *)((char *)&v604 + 4) = *(u64 *)&vResTgt.y;
        *(u64 *)&v607.x = *(u64 *)&vResPos.x;
        *(u64 *)&v607.z = LODWORD(vResPos.z);
        gStartCam_TgtGoalPos.x = vResTgt.x;
        gStartCam_CamGoalPos.z = v296;
        *((u64 *)&v294 + 1) = v293;
        *(_OWORD *)&gStartCam_TgtGoalPos.y = v294;
        wk->targetpos.x = v295;
        *(u64 *)&wk->targetpos.y = v294;
        *(u64 *)&wk->camerapos.x = v293;
        wk->camerapos.z = v296;
LABEL_534:
        v469 = wk->camerapos.x;
        v470 = wk->camerapos.y;
        v471 = wk->camerapos.z;
        v472 = wk->camerapos.w;
        sub_1B332C0(0, v469, v470, v471, v472);
        *(__n128 *)&v473 = sub_1B33480(0, 0.9);
        sub_1B335A0(&vResPos, 0, v473);
        sub_1B332C0(0, v607.x, v607.y, v607.z, v607.w);
        sub_1B33480(0, 0.1);
        sub_1B33360(0, vResPos.x, vResPos.y, vResPos.z, vResPos.w);
        *(__n128 *)&v474 = sub_1B33520(0);
        sub_1B335A0(&wk->camerapos, 0, v474);
        p_camerapos = &wk->targetpos;
        sub_1B332C0(0, wk->targetpos.x, wk->targetpos.y, wk->targetpos.z, wk->targetpos.w);
        *(__n128 *)&v475 = sub_1B33480(0, 0.9);
        sub_1B335A0(&vResTgt, 0, v475);
        sub_1B332C0(0, *(f32 *)&v604, *((f32 *)&v604 + 1), *((f32 *)&v604 + 2), *((f32 *)&v604 + 3));
        sub_1B33480(0, 0.1);
        sub_1B33360(0, vResTgt.x, vResTgt.y, vResTgt.z, vResTgt.w);
LABEL_537:
        v61 = sub_1B33520(0);
LABEL_538:
        p_targetpos = p_camerapos;
        goto LABEL_539;
      }
      if (Node == 2)
      {
        SetEnemyCPos();
        *(__n128 *)&v68 = sub_1B335A0(&vResTgt, 0, v67);
        sub_1B335A0(&v602, 0, v68);
        vResTgt.y = -100.0;
        *((f32 *)&v602 + 1) = -*((f32 *)&v602 + 1);
        if (!v69)
        ActionUnit = GetActionUnit();
        if (!ActionUnit)
        {
          v323 = PChara->pos.x;
          v324 = PChara->pos.y;
          v325 = PChara->pos.z;
          v326 = PChara->pos.w;
          *(__n128 *)&v327 = sub_1B332C0(0, v323, v324, v325, v326);
          sub_1B335A0(&v604, 0, v327);
          v328 = PChara->pos.x;
          v607.w = 0.0;
          *(u64 *)&v604 = 0xC2F0000042B40000LL;
          *(u64 *)&v607.y = 0xC3FA0000C2C80000LL;
          v607.x = v328 + 30.0;
          sub_1B33360(0, v328 + 30.0, -100.0, -500.0, 0.0);
          *(__n128 *)&v329 = sub_1B33520(0);
          sub_1B335A0(&v607, 0, v329);
          goto LABEL_530;
        }
        TargetUnit = GetTargetUnit();
        if (TargetUnit)
        {
          side = TargetUnit->side;
          v72 = TargetUnit;
          if ((side & 2) != 0)
          {
            v356 = TargetUnit->pos.x;
            v357 = vResTgt.z;
            DWORD1(v604) = -1027080192;
            *((u64 *)&v604 + 1) = LODWORD(vResTgt.z) | 0x3F80000000000000LL;
            v359 = (f32)(vResTgt.x * 0.1) + (f32)(v356 * 0.9);
            *(f32 *)&v604 = v359;
            if (!v358)
            *((f32 *)&v604 + 1) = sBtlGetGroundPos(v359, v357) + -100.0;
            v361 = wk->followUpAngle.x;
            if (wk->encountno == 26)
              v362 = 300.0;
            else
              v362 = 400.0;
            if (wk->encountno == 26)
              v363 = 800.0;
            else
              v363 = 1200.0;
            if (wk->encountno == 26)
              v364 = 100.0;
            else
              v364 = 400.0;
            v365 = sBtlGetDir180(v361);
            v366 = -v363;
            if (ActionUnit == Nakama)
            {
              if (!v367)
              PosToDir = sBtlGetPosToDir(0.0, 0.0, -v364, v366);
              v369 = sBtlGet360(v365 + PosToDir);
              v370 = -v364;
            }
            else
            {
              if (!v367)
              v368 = sBtlGetPosToDir(0.0, 0.0, v364, v366);
              v369 = sBtlGet360(v365 + v368);
              v370 = v364;
            }
            LenXZ = sBtlGetLenXZ(0.0, 0.0, v370, v366);
            sBtlGetMoveXZ(0.0, 0.0, v369, LenXZ, (f32 *)&v592 + 1, &v592);
            v607.w = 0.0;
            v607.x = *(f32 *)&v604 + *((f32 *)&v592 + 1);
            v607.y = *((f32 *)&v604 + 1) - v362;
            v607.z = *((f32 *)&v604 + 2) + *(f32 *)&v592;
          }
          else
          {
            v73 = wk->followUpAngle.x;
            if ((side & 0x80) != 0)
            {
              if (!v74)
              v451 = sBtlGetDir180(v73);
              v452 = sBtlGetPosToDir(0.0, 0.0, -70.0, 0.0);
              v453 = sBtlGet360(v451 + v452);
              v454 = sBtlGetLenXZ(0.0, 0.0, -70.0, 0.0);
              sBtlGetMoveXZ(0.0, 0.0, v453, v454, (f32 *)&ToZ + 1, &ToZ);
              v455 = v72->pos.x;
              v456 = v72->pos.y;
              HIDWORD(v604) = 0;
              v457 = v72->pos.z;
              *(f32 *)&v604 = v455 + *((f32 *)&ToZ + 1);
              *((f32 *)&v604 + 1) = (f32)(v456 + -120.0) + 20.0;
              v458 = wk->followUpAngle.x;
              *((f32 *)&v604 + 2) = v457 + *(f32 *)&ToZ;
              v82 = sBtlGetDir180(v458);
              v83 = -600.0;
            }
            else
            {
              if (!v74)
              v75 = sBtlGetDir180(v73);
              v76 = sBtlGetPosToDir(0.0, 0.0, -70.0, 0.0);
              v77 = sBtlGet360(v75 + v76);
              v78 = sBtlGetLenXZ(0.0, 0.0, -70.0, 0.0);
              sBtlGetMoveXZ(0.0, 0.0, v77, v78, (f32 *)&ToZ + 1, &ToZ);
              v79 = v72->pos.x;
              HIDWORD(v604) = 0;
              v80 = v72->pos.z;
              *(u64 *)&HelperPos.x = 0;
              *(u64 *)&HelperPos.z = 0;
              *(f32 *)&v604 = v79 + *((f32 *)&ToZ + 1);
              *((f32 *)&v604 + 2) = v80 + *(f32 *)&ToZ;
              if (!v81)
              GetUnitHelperPos(v72, &HelperPos);
              *((f32 *)&v604 + 1) = HelperPos.y + 20.0;
              v82 = sBtlGetDir180(wk->followUpAngle.x);
              v83 = -800.0;
            }
            v459 = v83;
            v460 = sBtlGetPosToDir(0.0, 0.0, 0.0, v83);
            v461 = sBtlGet360(v82 + v460);
            v462 = sBtlGetLenXZ(0.0, 0.0, 0.0, v459);
            sBtlGetMoveXZ(0.0, 0.0, v461, v462, (f32 *)&ToZ + 1, &ToZ);
            __asm { FMOV            V0.2S, #-20.0 }
            v607.w = 0.0;
            _D0.n64_u32[0] = HIDWORD(ToZ);
            *(float32x2_t *)&v607.x = vadd_f32(*(float32x2_t *)&v604, _D0);
            v607.z = *((f32 *)&v604 + 2) + *(f32 *)&ToZ;
          }
LABEL_529:
LABEL_530:
          v355 = 0;
LABEL_533:
          MenuStealth(v355);
          goto LABEL_534;
        }
        v331 = *(f32 *)&v603;
        v332 = *(f32 *)&v602;
        *((u64 *)&v604 + 1) = (u32)v603 | 0x3F80000000000000LL;
        v333 = *((f32 *)&v602 + 1) * 0.3;
        LODWORD(v604) = v602;
        *((f32 *)&v604 + 1) = *((f32 *)&v602 + 1) * 0.3;
        v334 = sBtlGetGroundPos(v332, v331);
        major = ActionUnit->major;
        *((f32 *)&v604 + 1) = v333 + v334;
        minor = ActionUnit->minor;
        VisualData = sBtlGetVisualData(major, minor);
        v338 = wk->followUpAngle.x;
        v339 = sBtlGetDir180(v338);
        v340 = sBtlGetPosToDir(0.0, 0.0, 150.0, 0.0);
        v341 = sBtlGet360(v339 + v340);
        v342 = sBtlGetLenXZ(0.0, 0.0, 150.0, 0.0);
        sBtlGetMoveXZ(0.0, 0.0, v341, v342, (f32 *)&v589 + 1, &v589);
        *(f32 *)&v604 = *(f32 *)&v604 + *((f32 *)&v589 + 1);
        v343 = wk->followUpAngle.x;
        *((f32 *)&v604 + 2) = *((f32 *)&v604 + 2) + *(f32 *)&v589;
        v344 = sBtlGetDir180(v343);
        if (ActionUnit == Nakama)
          v345 = -100.0;
        else
          v345 = 100.0;
        v346 = sBtlGetPosToDir(0.0, 0.0, v345, -500.0);
        v347 = sBtlGet360(v344 + v346);
        v348 = sBtlGetLenXZ(0.0, 0.0, v345, -500.0);
        sBtlGetMoveXZ(0.0, 0.0, v347, v348, (f32 *)&v589 + 1, &v589);
        v349 = ActionUnit->pos.x;
        v350 = ActionUnit->pos.y;
        v607.w = 0.0;
        v351 = v349 + *((f32 *)&v589 + 1);
        v352 = ActionUnit->pos.z + *(f32 *)&v589;
        height = VisualData->nml->height;
        v607.x = v351;
        v354 = height * 0.8;
        if (v354 < 100.0)
          v354 = 100.0;
        v607.y = v350 - v354;
        v607.z = v352;
      }
      else
      {
        if ((u32)(Node - 9) < 0xFFFFFFFE)
        {
          v298 = wk->followUpAngle.x;
          v299 = sBtlGetDir180(v298);
          v300 = sBtlGetPosToDir(0.0, 0.0, 80.0, -350.0);
          v301 = sBtlGet360(v299 + v300);
          v302 = sBtlGetLenXZ(0.0, 0.0, 80.0, -350.0);
          sBtlGetMoveXZ(0.0, 0.0, v301, v302, (f32 *)&v588 + 1, &v588);
          v303.n64_u64[0] = *(u64 *)&PChara->pos.x;
          v304.n64_u32[0] = -1027080192;
          v607.w = 0.0;
          v304.n64_u32[1] = vdup_lane_s32(v304, 0).n64_u32[1];
          v304.n64_u32[0] = HIDWORD(v588);
          v607.z = PChara->pos.z + *(f32 *)&v588;
          *(float32x2_t *)&v607.x = vadd_f32(v303, v304);
          v305 = sBtlGetDir180(wk->followUpAngle.x);
          v306 = sBtlGetPosToDir(0.0, 0.0, 40.0, 0.0);
          v307 = sBtlGet360(v305 + v306);
          v308 = sBtlGetLenXZ(0.0, 0.0, 40.0, 0.0);
          sBtlGetMoveXZ(0.0, 0.0, v307, v308, (f32 *)&v588 + 1, &v588);
          v310.n64_u64[0] = *(u64 *)&PChara->pos.x;
          HIDWORD(v604) = 0;
          v311.n64_u32[0] = -1024458752;
          v311.n64_u32[1] = vdup_lane_s32(v311, 0).n64_u32[1];
          *((f32 *)&v604 + 2) = PChara->pos.z + *(f32 *)&v588;
          v311.n64_u32[0] = HIDWORD(v588);
          *(float32x2_t *)&v604 = vadd_f32(v310, v311);
          goto LABEL_529;
        }
        SetEnemyCPos();
        sub_1B335A0(&vResTgt, 0, v313);
        vResTgt.y = -100.0;
        v314 = GetTargetUnit();
        if (v314)
          v315 = v314;
        else
          v315 = PChara;
        v316 = v315->pos.x;
        v607.w = 1.0;
        *((u64 *)&v604 + 1) = LODWORD(vResTgt.z) | 0x3F80000000000000LL;
        v317 = PChara->pos.z;
        v318 = PChara->pos.x * 0.7;
        *(f32 *)&v604 = (f32)(vResTgt.x * 0.3) + (f32)(v316 * 0.7);
        DWORD1(v604) = -1024458752;
        v607.y = -120.0;
        v607.z = v317 + -300.0;
        v607.x = (f32)(*(f32 *)&v604 * 0.3) + v318;
      }
      v355 = 1;
      goto LABEL_533;
    case 6:
      v86 = wk;
      v87 = v86->scene;
      v88 = v87->camCnt;
      if (!v88)
      {
        if (v85)
        {
          v87->camCnt = 1;
        }
        else
        {
          v291 = wk->scene;
          ++v291->camCnt;
        }
        return 1;
      }
      if (!v85)
      {
        v86 = wk;
        v88 = v86->scene->camCnt;
      }
      if (v88 == 1)
      {
        v86 = wk;
        pNakama0 = v86->cmbSkl->pNakama0;
        sBtlGetUnitHelperPos(pNakama0, 0);
        sub_1B335A0(&wk->targetpos, 0, v90);
      }
      m_PosCtrlCam = wk->m_CamMov->m_PosCtrlCam;
      m_cnt = m_PosCtrlCam->m_cnt;
      m_fFrm = m_PosCtrlCam->m_pPosMove[m_PosCtrlCam->m_stp]->m_fFrm;
      v94 = m_cnt;
      v95 = wk->cmbSkl->pNakama0;
      v96 = v94 / m_fFrm;
      sBtlGetUnitHelperPos(v95, 0);
      sub_1B335A0(&wk->targetpos, 0, v97);
      *(__n128 *)&v98 = sub_1B33480(0, 1.0 - v96);
      (loc_1F04FB0)(0, v98);
      v99 = sBtlGetPChara();
      sBtlGetUnitHelperPos(v99, 0);
      sub_1B33480(0, v96);
      *(__n128 *)&v100 = sub_1B33520(0);
      sub_1B335A0(&wk->targetpos, 0, v100);
      v102 = CameraMoveSystem(wk);
      v24 = sub_1B33E20(0, v102);
      v103 = v102;
      goto LABEL_124;
    case 7:
      v105 = wk->scene;
      if (!v105->camCnt)
      {
        v105->camCnt = 1;
        return 1;
      }
      v106 = CameraMoveSystem(wk);
      v107 = wk->m_CamMov->m_PosCtrlCam;
      v108 = v107->m_cnt;
      v109 = v107->m_pPosMove[v107->m_stp]->m_fFrm;
      v110 = sBtlGetPChara();
      v111 = v108 / v109;
      sBtlGetUnitHelperPos(v110, 0);
      sub_1B335A0(&wk->targetpos, 0, v112);
      *(__n128 *)&v113 = sub_1B33480(0, 1.0 - v111);
      (loc_1F04FB0)(0, v113);
      sBtlGetUnitHelperPos(wk->cmbSkl->pNakama0, 0);
      sub_1B33480(0, v111);
      *(__n128 *)&v115 = sub_1B33520(0);
      sub_1B335A0(&wk->targetpos, 0, v115);
      v24 = sub_1B33E20(0, v106);
      v103 = v106;
LABEL_124:
      v116 = sub_1B33D20(0, v103);
      v23 = *(f32 *)&v116;
      goto LABEL_125;
    case 8:
      v118 = wk->scene;
      ++v118->camCnt;
      if (!v10)
        goto LABEL_540;
      v119 = v10->pos.x;
      v120 = v10->pos.y;
      v122 = v10->pos.z;
      v121 = v10->pos.w;
      *(__n128 *)&v123 = sub_1B332C0(0, v119, v120, v122, v121);
      sub_1B335A0(&wk->targetpos, 0, v123);
      wk->targetpos.y = wk->targetpos.y + -80.0;
      *(__n128 *)&v124 = sub_1B332C0(0, PChara->pos.x, PChara->pos.y, PChara->pos.z, PChara->pos.w);
      p_camerapos = &wk->camerapos;
      sub_1B335A0(&wk->camerapos, 0, v124);
      v127 = wk->camerapos.y;
      v128 = wk->camerapos.z;
      v129 = wk->camerapos.w;
      v130 = v127 - (f32)((f32)((f32)wk->scene->camCnt * -0.25) + 200.0);
      v131 = wk->camerapos.x;
      wk->camerapos.y = v130;
      sub_1B33360(0, v131, v130, v128, v129);
      sub_1B332C0(0, wk->targetpos.x, wk->targetpos.y, wk->targetpos.z, wk->targetpos.w);
      sub_1B33400(0);
      sub_1949110(0);
      sub_1B335A0(&v609, 0, v132);
      sub_1B33480(0, -(f32)((f32)wk->scene->camCnt + 300.0));
      goto LABEL_537;
    case 9:
      if (wk->pCamSklUser)
      {
        PChara = wk->pCamSklUser;
        PChara = wk->pCamSklUser;
      }
      dds3ObjectBaseGetModelHandle(&PChara->pBasic);
      sub_1B335A0(&wk->targetpos, 0, v134);
      v136 = wk->scene;
      v137 = v136->camCnt + 1;
      _NF = v136->camCnt - 78 < 0;
      v136->camCnt = v137;
      if (_NF ^ __OFSUB__(v137, 79) | (v137 == 79))
      {
        wk->targetpos.x = 0.0;
        v137 = wk->scene->camCnt;
        wk->targetpos.z = 200.0;
        *(float32x2_t *)&wk->camerapos.x = vadd_f32(vdiv_f32(vmul_n_f32((float32x2_t)0xC2C80000C3480000LL, (f32)v137), vdup_n_s32(0x42A00000u)), (float32x2_t)0xC3480000C3FA0000LL);
        wk->targetpos.y = (f32)((f32)((f32)v137 / 80.0) * -300.0) + -100.0;
        wk->camerapos.z = (f32)((f32)((f32)v137 * -400.0) / 80.0) + -100.0;
      }
      else
      {
        v137 = wk->scene->camCnt;
        if (v137 <= 119)
        {
          vResPos.x = 220.0;
          v137 = wk->scene->camCnt;
          vResPos.w = 0.0;
          v241 = (f32)v137 + -80.0;
          v242 = -350.0 - v241;
          v244 = (f32)(v241 + -250.0) + -100.0;
          vResPos.y = v244;
          vResPos.z = -350.0 - v241;
          if (!v243)
          sub_1B332C0(0, 220.0, v244, v242, 0.0);
          sub_1B33360(0, wk->targetpos.x, wk->targetpos.y, wk->targetpos.z, wk->targetpos.w);
          *(__n128 *)&v245 = sub_1B33520(0);
          sub_1B335A0(&wk->camerapos, 0, v245);
          v246 = wk->camerapos.y;
          wk->camerapos.z = wk->camerapos.z + -500.0;
          if (v246 > -500.0)
            wk->camerapos.y = -500.0;
        }
        else
        {
          v139 = PChara->pos.x;
          v140 = PChara->pos.y;
          v141 = PChara->pos.z;
          v142 = PChara->pos.w;
          *(__n128 *)&v143 = sub_1B332C0(0, v139, v140, v141, v142);
          sub_1B335A0(&wk->targetpos, 0, v143);
          v144 = PChara->pos.x;
          v145 = PChara->pos.y;
          v147 = PChara->pos.z;
          v146 = PChara->pos.w;
          v148 = wk;
          v609 = 0;
          HIDWORD(v610) = 0;
          v149 = v148->scene->camCnt;
          if (v149 >= 240)
            v149 = 240;
          v150 = (v149 - 120);
          *(f32 *)&v610 = -(f32)((f32)(v150 * 6.25) + 650.0);
          if (!v151)
          sub_1B332C0(0, v144, v145, v147, v146);
          sub_1B33360(0, 0.0, 0.0, -(f32)((f32)(v150 * 6.25) + 650.0), 0.0);
          *(__n128 *)&v152 = sub_1B33520(0);
          sub_1B335A0(&wk->camerapos, 0, v152);
          v153 = wk->camerapos.z + -250.0;
          wk->camerapos.y = (f32)(v150 * -5.0) + -150.0;
          wk->camerapos.z = v153;
        }
      }
      sBtlGetPChara();
      goto LABEL_540;
    case 0xB:
      v155 = wk->cmbSkl->pNakama0;
      sBtlGetIdling(wk, &vResPos, &vResTgt, 0, v155, 1);
      Slerp(wk, vResPos, vResTgt, 0.1);
      goto LABEL_540;
    case 0xC:
      v158 = wk;
      if (v158->bCamPosSlp)
      {
        v158 = wk;
        v159 = v158->camPos_s.x;
        v160 = v158->camPos_s.y;
        v161 = v158->camPos_s.z;
        v162 = v158->camPos_s.w;
        v163 = v158->camPos_t.x;
        v164 = v158->camPos_t.y;
        v165 = v158->camPos_t.z;
        v166 = v158->camPos_t.w;
        camPosSlpTime = v158->camPosSlpTime;
        camPosSlpCnt = v158->camPosSlpCnt;
        v572 = v158->camPosSlpCnt;
        v575 = v158->camPosSlpTime;
        camPosSlpCnt = v572;
        camPosSlpTime = v575;
        x = camPosSlpCnt;
        v611.x = v159;
        v611.z = v161;
        fa = camPosSlpTime;
        v611.y = v160;
        v611.w = v162;
        v619.x = v163;
        v619.y = v164;
        v619.z = v165;
        v619.w = v166;
        GetNowPosAS(&wk->camerapos, v611, v619, fa, x);
        v24 = 1.0;
        v23 = 0.0;
        v170 = wk;
        v171 = v170->camPosSlpCnt;
        if (v171 == v170->camPosSlpTime)
        {
          if (!v169)
          {
            v170 = wk;
          }
          v170->bCamPosSlp = 0;
          v172 = v170->camPos_t.x;
          v173 = v170->camPos_t.y;
          v175 = v170->camPos_t.z;
          v174 = v170->camPos_t.w;
          *(__n128 *)&v176 = sub_1B332C0(0, v172, v173, v175, v174);
          sub_1B335A0(&wk->camerapos, 0, v176);
        }
        else
        {
          if (!v169)
          {
            v170 = wk;
            v171 = v170->camPosSlpCnt;
          }
          v170->camPosSlpCnt = v171 + 1;
        }
      }
      v223 = wk;
      if (!v223->bCamTgtSlp)
        goto LABEL_540;
      v223 = wk;
      p_camerapos = &wk->targetpos;
      v224 = v223->camTgt_s.x;
      v225 = v223->camTgt_s.y;
      v226 = v223->camTgt_s.z;
      v227 = v223->camTgt_s.w;
      v228 = v223->camTgt_t.x;
      v229 = v223->camTgt_t.y;
      v230 = v223->camTgt_t.z;
      v231 = v223->camTgt_t.w;
      camTgtSlpTime = v223->camTgtSlpTime;
      camTgtSlpCnt = v223->camTgtSlpCnt;
      v573 = v223->camTgtSlpCnt;
      v576 = v223->camTgtSlpTime;
      camTgtSlpCnt = v573;
      camTgtSlpTime = v576;
      xa = camTgtSlpCnt;
      v612.x = v224;
      v612.z = v226;
      fb = camTgtSlpTime;
      v612.y = v225;
      v612.w = v227;
      v620.x = v228;
      v620.y = v229;
      v620.z = v230;
      v620.w = v231;
      GetNowPosAS(&wk->targetpos, v612, v620, fb, xa);
      v24 = 1.0;
      v23 = 0.0;
      v235 = wk;
      v236 = v235->camTgtSlpCnt;
      if (v236 == v235->camTgtSlpTime)
      {
        if (!v234)
        {
          v235 = wk;
        }
        v235->bCamTgtSlp = 0;
        v237 = v235->camTgt_t.x;
        v238 = v235->camTgt_t.y;
        v240 = v235->camTgt_t.z;
        v239 = v235->camTgt_t.w;
        v61 = sub_1B332C0(0, v237, v238, v240, v239);
        goto LABEL_538;
      }
      if (!v234)
      {
        v235 = wk;
        v236 = v235->camTgtSlpCnt;
      }
      v235->camTgtSlpCnt = v236 + 1;
      goto LABEL_540;
    case 0xD:
      v177 = CameraMoveSystem(wk);
      v24 = sub_1B33E20(0, v177);
      v178 = sub_1B33D20(0, v177);
      v23 = *(f32 *)&v178;
      v180 = wk->scene;
      ++v180->camCnt;
      v181 = wk->targetpos.x;
      v182 = wk->targetpos.y;
      v183 = wk->targetpos.z;
      sBtlDrawLineX_PS2(v181, v182, v183, 100.0, 0x80800080);
      sBtlDrawLineX_PS2(wk->camerapos.x, wk->camerapos.y, wk->camerapos.z, 100.0, 0x80808080);
      sBtlDrawLine_PS2(wk->targetpos.x, wk->targetpos.y, wk->targetpos.z, wk->camerapos.x, wk->camerapos.y, wk->camerapos.z, 0xFFFFFFFF);
      goto LABEL_540;
    case 0xE:
      v184 = sBtlGetNode();
      if (v184 > 8)
        goto LABEL_275;
      if (((1 << v184) & 0x38) != 0)
      {
        v208 = GetTargetUnit();
        p_fields = &wk->fields;
        if (v208)
        {
          if (!v211)
          sBtlInputFollowUp_Menu2(sBtlCamera, &wk->followUpAngle);
          v212 = v208->pos.x;
          v213 = v208->pos.y;
          HIDWORD(v604) = 1065353216;
          *(f32 *)&v604 = v212;
          *((f32 *)&v604 + 1) = v213 + -100.0;
          DWORD2(v604) = LODWORD(v208->pos.z);
          v214 = p_fields->followUpAngle.x;
          v215 = sBtlGetDir180(v214);
          v216 = sBtlGetPosToDir(0.0, 0.0, 0.0, -900.0);
          v217 = sBtlGet360(v215 + v216);
          v218 = sBtlGetLenXZ(0.0, 0.0, 0.0, -900.0);
          sBtlGetMoveXZ(0.0, 0.0, v217, v218, (f32 *)&v597 + 1, &v597);
          v607.w = 0.0;
          v219 = v604;
          p_ppos = &v595;
          v595 = 0;
          v596 = 0;
          v221 = *((f32 *)&v604 + 2);
          v607.x = *(f32 *)&v604 + *((f32 *)&v597 + 1);
          v607.y = *((f32 *)&v604 + 1) + -300.0;
          v222 = *(f32 *)&v597;
        }
        else
        {
          if (!v211)
          sBtlInputFollowUp_Menu2(sBtlCamera, &wk->followUpAngle);
          v248 = PChara->pos.x;
          v249 = PChara->pos.y;
          HIDWORD(v604) = 1065353216;
          *(f32 *)&v604 = v248;
          *((f32 *)&v604 + 1) = v249 + -100.0;
          DWORD2(v604) = LODWORD(PChara->pos.z);
          v250 = p_fields->followUpAngle.x;
          v251 = sBtlGetDir180(v250);
          v252 = sBtlGetPosToDir(0.0, 0.0, 0.0, -900.0);
          v253 = sBtlGet360(v251 + v252);
          v254 = sBtlGetLenXZ(0.0, 0.0, 0.0, -900.0);
          sBtlGetMoveXZ(0.0, 0.0, v253, v254, (f32 *)&v594 + 1, &v594);
          v607.w = 0.0;
          p_ppos = &ppos;
          *(u64 *)&ppos.x = 0;
          *(u64 *)&ppos.z = 0;
          v221 = *((f32 *)&v604 + 2);
          v607.x = *(f32 *)&v604 + *((f32 *)&v594 + 1);
          v607.y = *((f32 *)&v604 + 1) + -300.0;
          v222 = *(f32 *)&v594;
          v219 = v604;
        }
        v607.z = v221 + v222;
        goto LABEL_253;
      }
      if (((1 << v184) & 0x184) != 0)
      {
        v185 = GetTargetUnit();
        if (v185)
          v187 = v185;
        else
          v187 = PChara;
        sBtlInputFollowUp_Menu2(sBtlCamera, &wk->followUpAngle);
        v189 = v187->pos.x;
        v190 = v187->pos.y;
        HIDWORD(v604) = 1065353216;
        *(f32 *)&v604 = v189;
        *((f32 *)&v604 + 1) = v190 + -100.0;
        DWORD2(v604) = LODWORD(v187->pos.z);
        v191 = wk->followUpAngle.x;
        v192 = sBtlGetDir180(v191);
        v193 = sBtlGetPosToDir(0.0, 0.0, 0.0, -900.0);
        v194 = sBtlGet360(v192 + v193);
        v195 = sBtlGetLenXZ(0.0, 0.0, 0.0, -900.0);
        sBtlGetMoveXZ(0.0, 0.0, v194, v195, &ToX, &v600);
        v196.n64_u64[0] = *(u64 *)&v187->pos.x;
        v607.w = 0.0;
        v197.n64_u32[0] = -1010302976;
        v198.n64_u32[1] = vdup_lane_s32(v197, 0).n64_u32[1];
        v199 = v187->pos.z;
        devilid = (u16)v187->para->devilid;
        v198.n64_u32[0] = ToX;
        v607.z = v199 + v600;
        *(float32x2_t *)&v607.x = vadd_f32(v196, v198);
        if (devilid == 260)
        {
          *(u64 *)&v604 = v196.n64_u32[0] | 0xC348000000000000LL;
          *((f32 *)&v604 + 2) = v199 + -200.0;
          if (!v201)
          v202 = sBtlGetLenXZ(0.0, 0.0, 0.0, -1400.0);
          sBtlGetMoveXZ(0.0, 0.0, v194, v202, &ToX, &v600);
          v607.y = -500.0;
          v203 = v604;
          v204 = *((f32 *)&v604 + 2);
          v607.x = *(f32 *)&v604 + *(f32 *)&ToX;
          v607.z = *((f32 *)&v604 + 2) + v600;
        }
        else
        {
          v203 = v604;
          v204 = *((f32 *)&v604 + 2);
        }
        v598 = 0;
        v599 = 0;
        v247 = DWORD1(v604);
        p_ppos = &v598;
        v221 = v204;
        v219 = __PAIR64__(v247, v203);
LABEL_253:
        v255 = sBtlChangeWorldtoScreenUnity3(*(f32 *)&v219, *((f32 *)&v219 + 1), v221, p_ppos);
        v257 = v255;
        if (v255)
          v258 = 0.1;
        else
          v258 = 0.2;
        if (v255)
          v259 = 0.9;
        else
          v259 = 0.8;
        MenuStealth(1);
        v613.w = wk->targetpos.w;
        v613.x = wk->targetpos.x;
        cameraPos = v607;
        v613.y = wk->targetpos.y;
        v613.z = wk->targetpos.z;
        v261 = RaycastCamHit(PChara, v613, &cameraPos, 200.0);
        v262 = 0.9;
        if (v257)
          v262 = 0.4;
        v263 = 0.1;
        if (v257)
          v263 = 0.6;
        if (v261)
          v264 = v262;
        else
          v264 = v258;
        if (v261)
          v259 = v263;
        v265 = wk->camerapos.x;
        v266 = wk->camerapos.y;
        v267 = wk->camerapos.z;
        v268 = wk->camerapos.w;
        sub_1B332C0(0, v265, v266, v267, v268);
        *(__n128 *)&v269 = sub_1B33480(0, v259);
        sub_1B335A0(&vResPos, 0, v269);
        sub_1B332C0(0, cameraPos.x, cameraPos.y, cameraPos.z, cameraPos.w);
        sub_1B33480(0, v264);
        sub_1B33360(0, vResPos.x, vResPos.y, vResPos.z, vResPos.w);
        *(__n128 *)&v270 = sub_1B33520(0);
        sub_1B335A0(&wk->camerapos, 0, v270);
        sub_1B332C0(0, wk->targetpos.x, wk->targetpos.y, wk->targetpos.z, wk->targetpos.w);
        *(__n128 *)&v271 = sub_1B33480(0, v259);
        sub_1B335A0(&vResTgt, 0, v271);
        sub_1B332C0(0, *(f32 *)&v604, *((f32 *)&v604 + 1), *((f32 *)&v604 + 2), *((f32 *)&v604 + 3));
        sub_1B33480(0, v264);
        sub_1B33360(0, vResTgt.x, vResTgt.y, vResTgt.z, vResTgt.w);
        *(__n128 *)&v272 = sub_1B33520(0);
        sub_1B335A0(&wk->targetpos, 0, v272);
        v274 = wk->targetpos.x;
        v275 = wk->targetpos.y;
        v276 = wk->targetpos.z;
        v277 = wk->targetpos.w;
        v278 = wk->camerapos.x;
        v279 = wk->camerapos.y;
        v280 = wk->camerapos.z;
        v281 = wk->camerapos.w;
        v614.x = v274;
        v614.y = v275;
        v614.z = v276;
        v614.w = v277;
        v621.x = v278;
        v621.y = v279;
        v621.z = v280;
        v621.w = v281;
        RaycastCamHide(v614, v621);
        v23 = 0.0;
        v24 = 1.0;
        goto LABEL_540;
      }
LABEL_275:
      if (!ProcessCheck())
      {
        if (!ProcessCheck())
        {
          if (!ProcessCheck())
          {
            if (wk->cmbSkl->bRun)
            {
LABEL_287:
              MenuStealth(0);
              goto LABEL_540;
            }
            sBtlGetIdling_HD(wk, PChara, v283, &vResPos, &vResTgt);
            v557 = vResPos.x;
            v558 = vResPos.y;
            *(u64 *)&wk->camTgtConsF = 0;
            v560 = vResPos.z;
            v559 = vResPos.w;
            *(__n128 *)&v561 = sub_1B332C0(0, v557, v558, v560, v559);
            sub_1B335A0(&v607, 0, v561);
            *(__n128 *)&v562 = sub_1B332C0(0, vResTgt.x, vResTgt.y, vResTgt.z, vResTgt.w);
            sub_1B335A0(&v604, 0, v562);
            v563 = *(u64 *)&v607.x;
            v564 = v607.z;
            v607.y = *((f32 *)&v563 + 1) + sBtlGetGroundPos(*(f32 *)&v563, v564);
            v565 = *((f32 *)&v604 + 1);
            v626.y = v565 + sBtlGetGroundPos(*(f32 *)&v604, *((f32 *)&v604 + 2));
            LODWORD(v626.x) = v604;
            *(u64 *)&v626.z = *((u64 *)&v604 + 1);
            DWORD1(v604) = LODWORD(v626.y);
            Slerp(wk, v607, v626, 0.5);
            goto LABEL_287;
          }
        }
      }
LABEL_540:
      if (!!sBtlCheckZoom2((f32 *)&ToX + 1))
      {
        v476 = *((f32 *)&ToX + 1);
        GlobalParamScaleX = *((f32 *)&ToX + 1);
        GlobalParamScaleY = v476;
      }
      *(u64 *)&gsBtlCamera_Hokan_Not = 0;
      v577 = wk->camerapos;
      vct_A = v577;
      vResPos = vct_A;
      targetpos = wk->targetpos;
      vct_A = targetpos;
      vResTgt = vct_A;
      if (!gUpV2_OW_Use)
      {
        v488 = 0.0;
        goto LABEL_596;
      }
      v483 = gUpV2_OW_Param * -0.017453292;
      v484 = (s32)(v483 * 0.15915494);
      if ((f32)(v483 * 0.15915494) == INFINITY)
        v484 = -2147500000.0;
      v485 = (f32)(v483 * 0.15915494) - v484;
      v486 = 0.5;
      if (v485 <= 0.5)
      {
        if (v485 >= -0.5)
          goto LABEL_578;
        v487 = 1.0;
      }
      else
      {
        v487 = -1.0;
      }
      v485 = v485 + v487;
LABEL_578:
      if (v485 <= 0.25)
      {
        if (v485 < -0.25)
          v485 = -0.5 - v485;
      }
      else
      {
        v485 = 0.5 - v485;
      }
      v489 = v485 * 4.0;
      v490 = v489 * v489;
      v491 = v489 * (f32)(v489 * v489);
      v492 = (f32)(v489 * v489) * v491;
      v493 = (f32)(v489 * v489) * v492;
      v494 = (f32)((f32)(v489 * 1.5708) + (f32)(v491 * -0.6459637)) + (f32)(v492 * 0.07968968);
      v495 = v490 * (f32)(v490 * v492);
      v496 = v493 * -0.0046737655;
      v497 = (f32)(v483 + 1.5708) * 0.15915494;
      v498 = (s32)v497;
      if (v497 == INFINITY)
        v498 = -2147500000.0;
      v499 = v497 - v498;
      if (v499 <= 0.5)
      {
        if (v499 >= -0.5)
          goto LABEL_589;
        v500 = 1.0;
      }
      else
      {
        v500 = -1.0;
      }
      v499 = v499 + v500;
LABEL_589:
      v501 = v494 + v496;
      v502 = v495 * 0.00015148419;
      if (v499 <= 0.25)
      {
        if (v499 >= -0.25)
          goto LABEL_593;
        v486 = -0.5;
      }
      v499 = v486 - v499;
LABEL_593:
      v503 = v499 * 4.0;
      v504 = v501 + v502;
      v505 = v503 * (f32)(v503 * v503);
      v506 = (f32)(v503 * v503) * v505;
      v507 = (f32)((f32)((f32)(v503 * 1.5708) + (f32)(v505 * -0.6459637)) + (f32)(v506 * 0.07968968))
           + (f32)((f32)((f32)(v503 * v503) * v506) * -0.0046737655);
      v508 = (f32)((f32)(v503 * v503) * (f32)((f32)(v503 * v503) * v506)) * 0.00015148419;
      v24 = v507 + v508;
      v509 = sBtlGetPosToDir(0.0, 0.0, v504, 0.0);
      v510 = sBtlGetLenXZ(0.0, 0.0, v504, 0.0);
      v511 = sBtlGet360(v509 + wk->followUpAngle.x);
      sBtlGetMoveXZ(0.0, 0.0, v511, v510, &ZeroZ, &v583);
      v488 = v583;
      v23 = *(f32 *)&ZeroZ;
LABEL_596:
      vct_A.x = v23;
      vct_A.y = v24;
      vct_A.z = v488;
      vct_A.w = 0.0;
      v514 = workdata + 6;
      goto LABEL_600;
LABEL_615:
      if (!gFOVY2_OW_Use)
        goto LABEL_603;
      gFOVY2_OW_Param_local = gFOVY2_OW_Param;
      goto LABEL_619;
LABEL_600:
      *v514 = vct_A;
      p_vertical = &wk->vertical;
      *p_vertical = vct_A;
      goto LABEL_615;
LABEL_603:
      if (v518)
      {
        if (gFOVY_OW_Use)
        {
LABEL_605:
          gFOVY2_OW_Param_local = gFOVY_OW_Param;
          goto LABEL_619;
        }
      }
      else
      {
        if (gFOVY_OW_Use)
          goto LABEL_605;
      }
      gFOVY2_OW_Param_local = gFreeCam_Fov;
LABEL_619:
      v524 = gFOVY2_OW_Param_local * 0.017453292;
      dds3CameraObjectBasicSetFovy(&wk->cm, v524);
      LODWORD(workdata[9].w) |= 1u;
      ActiveScene = dds3GetActiveScene();
      v527 = p_cm;
      SetActiveCamera(ActiveScene, v527, 0);
      if (wk->mode == 1)
        goto LABEL_629;
      v528 = p_cm;
      v529 = vResTgt.x;
      v530 = vResTgt.y;
      v531 = vResTgt.z;
      v532 = vResTgt.w;
      v533 = vResPos.x;
      v534 = vResPos.y;
      v536 = vResPos.z;
      v535 = vResPos.w;
      v617.x = v529;
      v617.y = v530;
      v617.z = v531;
      v617.w = v532;
      v624.x = v533;
      v624.y = v534;
      v624.z = v536;
      v624.w = v535;
      dds3CameraObjectBasicSetTgtCam(v528, v617, v624);
      mode = wk->mode;
      if (mode == 1)
      {
LABEL_629:
        v538 = p_cm;
        v539 = vResTgt.x;
        v540 = vResTgt.y;
        v541 = vResTgt.z;
        v542 = vResTgt.w;
        v543 = vResPos.x;
        v544 = vResPos.y;
        v546 = vResPos.z;
        v545 = vResPos.w;
        v618.x = v539;
        v618.y = v540;
        v618.z = v541;
        v618.w = v542;
        v625.x = v543;
        v625.y = v544;
        v625.z = v546;
        v625.w = v545;
        dds3CameraObjectBasicSetTgtCam(v538, v618, v625);
        wk->modeOld = wk->mode;
        v580 = wk->targetpos;
        goto LABEL_637;
      }
      else
      {
        wk->modeOld = mode;
        v580 = wk->targetpos;
      }
LABEL_637:
      vct_A = v580;
      v549 = wk->camerapos;
      vct_B = v549;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      sub_1949110(0);
      p_direction = &wk->direction;
      *p_direction = vct_A;
      UpdateAwCamera();
      return 1;
    default:
      goto LABEL_540;
  }
}

// 0x1f01cf0
static sdfVector3_t GetDisAngle(f32 sou_x, f32 sou_z, f32 dst_x, f32 dst_z, f32 distance) {
  f32 PosToDir;
  sdfVector3_t v12;
  sdfVector3_t v14;
  sdfQuaternion_t v15;

  PosToDir = sBtlGetPosToDir(sou_x, sou_z, dst_x, dst_z);
  v12.z = 0.0;
  v12.y = PosToDir * 0.017453292;
  v12.x = 0.0;
  v15 = Internal_FromEulerRad(v12, 0);
  v14.z = distance;
  v14.x = 0.0;
  v14.y = 0.0;
  return op_Multiply_60935616(v15, v14, 0);
}

// 0x1f012d0
void sBtlNakamaSetUp(s32 nakama_index) {
  sdatPlayerUnitWork_t *player;
  SBTLUNIT_WORK *PChara;
  u32 v7;
  SBTLUNIT_WORK *v8;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 Dir180;
  struct sdfVector4_t v24;
  f32 v26;
  f32 v27;
  f32 PosToDir;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 LenXZ;
  f32 v35;
  s64 v38;
  SBATTLE_WORK *v39;
  SBATTLE_WORK *v40;
  s32 v41;
  sdatUnitWork_t *stock_id;
  SBATTLE_WORK *v44;
  s32 v45;
  DEVILDATA_WORK *DevilData;
  SBATTLE_WORK *v48;
  s64 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  long f64 v54;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  u32 v68;
  f32 v69;
  s32 v70;
  f32 v71;
  f32 v72;
  SBATTLE_WORK *v73;
  u32 *p_stock_mask;
  s32 v75;
  SBATTLE_WORK *v76;
  RED_GUAGE *v77;
  SBTLUNIT_WORK *v78;
  SBATTLE_WORK *v80;
  SUMMON_CTRL *smnCtrl;
  s32 v82;
  struct sdfVector4_t pos;
  s64 v84;
  s64 ToZ;
  struct sdfVector4_t vct_A_local;
  sdfVector4_t v87;
  sdfVector4_t v88;

  vct_A_local = (struct sdfVector4_t)0;
  v84 = 0;
  ToZ = 0;
  goto LABEL_3;
  if (v7)
  {
LABEL_3:
    player = GBWK->player;
    PChara = sBtlGetPChara();
    if (!PChara)
      return;
    goto LABEL_7;
  }
  player = GBWK->player;
  PChara = sBtlGetPChara();
  if (!PChara)
    return;
LABEL_7:
  v8 = PChara;
  *(u64 *)&wk->PlayerBtlStartPosX = *(u64 *)&v8->pos.x;
  wk->PlayerBtlStartPosZ = v8->pos.z;
  x = v8->rot.x;
  y = v8->rot.y;
  z = v8->rot.z;
  w = v8->rot.w;
  v87.x = x;
  v87.y = y;
  v87.z = z;
  v87.w = w;
  RotToDir = sBtlGetRotToDir(v87);
  Dir180 = sBtlGetDir180(RotToDir);
  wk->PlayerBtlStartDir = Dir180;
  *(sdfVector2_t *)&wk->CameraBtlStartX = wk->scene->camera->followUpAngle;
  pos = v8->pos;
  vct_A = pos;
  v24 = vct_A;
  vct_A_local = v24;
  if (nakama_index)
  {
    v26 = wk->scene->camera->followUpAngle.x;
    v27 = sBtlGetDir180(v26);
    PosToDir = sBtlGetPosToDir(0.0, 0.0, 200.0, 200.0);
    v29 = sBtlGet360(v27 + PosToDir);
    v30 = 200.0;
    goto LABEL_32;
  }
  v31 = wk->scene->camera->followUpAngle.x;
  v32 = sBtlGetDir180(v31);
  v33 = sBtlGetPosToDir(0.0, 0.0, -200.0, 200.0);
  v29 = sBtlGet360(v32 + v33);
  v30 = -200.0;
LABEL_32:
  LenXZ = sBtlGetLenXZ(0.0, 0.0, v30, 200.0);
  sBtlGetMoveXZ(0.0, 0.0, v29, LenXZ, (f32 *)&ToZ + 1, &ToZ);
  v35 = vct_A_local.x + *((f32 *)&ToZ + 1);
  vct_A_local.x = vct_A_local.x + *((f32 *)&ToZ + 1);
  vct_A_local.z = vct_A_local.z + *(f32 *)&ToZ;
  v38 = nakama_index;
  v39 = wk;
  v39->NakamaBtlStartPosX[v38] = v35;
  v39->NakamaBtlStartPosY[v38] = vct_A_local.y;
  v39->NakamaBtlStartPosZ[v38] = vct_A_local.z;
  v39->NakamaBtlStartDir[v38] = v39->PlayerBtlStartDir;
  if (v39->encountno == 23)
  {
    if (!evtBitCheck(10023))
      return;
  }
  v40 = wk;
  if (v40->stock_num >= 1)
  {
    v40 = wk;
    v41 = v40->summonindex[nakama_index];
    if ((v41 & 0x80000000) == 0)
    {
      stock_id = player->stock_id;
      LOWORD(v41) = wk->summonindex[nakama_index];
      if (sBtlCheckSelect(stock_id[(s16)v41]))
      {
        v44 = wk;
        if (!v44->battlemode)
        {
          v44 = wk;
          v45 = v44->stock_id[v44->summonindex[nakama_index]];
          DevilData = sBtlGetDevilData(v45, -1);
          v48 = wk;
          if (v48->RouletteStBotKuda == (s64)DevilData->kuda_id)
          {
            v48 = wk;
            v49 = (s64)v48->summonindex + 2 * nakama_index;
            v48->summonindex_menu[nakama_index] = -1;
            *(u16 *)(v49 + 32) = -1;
LABEL_56:
            if (wk->summonindex[nakama_index] < 0)
              return;
            goto LABEL_62;
          }
          {
            goto LABEL_56;
          }
          if (wk->summonindex[nakama_index] < 0)
            return;
LABEL_62:
          v50 = v8->pos.x;
          v51 = v8->pos.y;
          v52 = v8->pos.z;
          v53 = v8->pos.w;
          *(__n128 *)&v54 = sub_1B332C0(0, v50, v51, v52, v53);
          sub_1B335A0(&vct_A_local, 0, v54);
          if (nakama_index)
          {
            v57 = wk->scene->camera->followUpAngle.x;
            v58 = sBtlGetDir180(v57);
            v59 = sBtlGetPosToDir(0.0, 0.0, 200.0, 200.0);
            v60 = sBtlGet360(v58 + v59);
            v61 = 200.0;
          }
          else
          {
            v62 = wk->scene->camera->followUpAngle.x;
            v63 = sBtlGetDir180(v62);
            v64 = sBtlGetPosToDir(0.0, 0.0, -200.0, 200.0);
            v60 = sBtlGet360(v63 + v64);
            v61 = -200.0;
          }
          v65 = sBtlGetLenXZ(0.0, 0.0, v61, 200.0);
          sBtlGetMoveXZ(0.0, 0.0, v60, v65, (f32 *)&v84 + 1, &v84);
          v66 = vct_A_local.x + *((f32 *)&v84 + 1);
          v69 = vct_A_local.z + *(f32 *)&v84;
          vct_A_local.x = vct_A_local.x + *((f32 *)&v84 + 1);
          vct_A_local.z = vct_A_local.z + *(f32 *)&v84;
          if (!v68)
          {
            v66 = vct_A_local.x;
            v69 = vct_A_local.z;
          }
          v70 = wk->summonindex[nakama_index];
          v71 = vct_A_local.y;
          v72 = vct_A_local.w;
          v88.x = v66;
          v88.y = v71;
          v88.z = v69;
          v88.w = v72;
          sBtlSetSummon_Unit(v8, v70, 0, 1, v88, 2, 0);
          v73 = wk;
          p_stock_mask = &v73->stock_mask;
          v75 = v73->summonindex[nakama_index];
          sBtlSetBit(p_stock_mask, v75);
          v76 = wk;
          v77 = v76->aRedGuage[nakama_index + 1];
          v78 = sBtlSearchUnit_ID(v76->UnitMng, v76->summonID[v76->summonindex[nakama_index]]);
          sBtlInitRedGg(v77, v78->para->now->hp);
          v80 = wk;
          smnCtrl = v80->smnCtrl;
          smnCtrl->bNoOk = 1;
          smnCtrl->aprId = nakama_index;
          v82 = v80->summonindex[nakama_index];
          smnCtrl->io = 1;
          smnCtrl->stkId = v82;
          if (!nakama_index)
          {
            v80 = wk;
            LOWORD(v82) = v80->summonindex[0];
            sBtlSetDevilSkillID(v80->stock_id[(s16)v82], 0);
            wk->talkwk->mode = 1;
          }
        }
      }
    }
  }
}

// 0x1eee500
static bool Backup(SBTLCAMERA_WORK *wk, dds3Basic_t *cm) {
  void *workdata;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_targetpos;
  s32 v10;
  struct sdfVector4_t v11;
  sdfVector4_t *p_direction;
  s32 v13;
  struct sdfVector4_t pos;
  sdfVector4_t *p_camerapos;
  s32 v16;
  struct sdfVector4_t v17;
  struct sdfVector4_t v18;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  s32 v26;
  s32 v27;
  s32 v28;
  struct sdfVector4_t v30;
  struct sdfVector4_t v31;
  struct sdfVector4_t v33;
  struct sdfVector4_t v35;
  dds3Basic_t *pBasic;

  pBasic = cm;
  workdata = cm->workdata;
  poseset = cm->poseset;
  wk->cm = cm;
  v30 = (struct sdfVector4_t)workdata[7];
  vct_A = v30;
  p_targetpos = &wk->targetpos;
  v10 = (u8)byte_5755EF5;
  *p_targetpos = vct_A;
  v11 = (struct sdfVector4_t)workdata[5];
  if (v10)
    goto LABEL_12;
  goto LABEL_38;
  if (v26)
  {
LABEL_12:
    goto LABEL_13;
  }
LABEL_38:
  v31 = v11;
  v11 = v31;
LABEL_13:
  vct_A = v11;
  p_direction = &wk->direction;
  v13 = (u8)byte_5755EF5;
  *p_direction = vct_A;
  pos = poseset->pos;
  if (v13)
    goto LABEL_16;
  goto LABEL_42;
  if (v27)
  {
LABEL_16:
    goto LABEL_17;
  }
LABEL_42:
  v33 = pos;
  pos = v33;
LABEL_17:
  vct_A = pos;
  p_camerapos = &wk->camerapos;
  v16 = (u8)byte_5755EF5;
  *p_camerapos = vct_A;
  v17 = *p_targetpos;
  if (v16)
    goto LABEL_20;
  goto LABEL_46;
  if (v28)
  {
LABEL_20:
    goto LABEL_21;
  }
LABEL_46:
  v35 = v17;
  v17 = v35;
LABEL_21:
  vct_A = v17;
  v18 = *p_camerapos;
  vct_B = v18;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  wk->distance = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
  wk->fovy = dds3CameraObjectBasicGetFovy(pBasic);
  return 1;
}

// 0x1f01dc0
static bool Set(SBTLCAMERA_WORK *wk) {
  dds3Basic_t *p_cm;
  void *workdata;
  s64 naturalAligment;
  sdfVector4_t *v7;
  f32 distance;
  f32 v9;
  struct sdfVector4_t targetpos;
  sdfVector4_t *v11;
  s32 v12;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *v20;
  f32 fovy;
  void *v24;
  s64 v25;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *v27;
  s32 v29;
  struct sdfVector4_t direction;
  sdfVector4_t v35;
  sdfVector4_t v36;

  p_cm = &wk->cm;
  direction = wk->direction;
  workdata = wk->cm->workdata;
  vct_A = direction;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3CameraObjectBasicWorkData_t)
    {
      v24 = workdata;
      goto LABEL_58;
    }
  }
  v7 = &workdata[5];
  *v7 = vct_A;
  distance = wk->distance;
  v9 = -distance;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v9);
  targetpos = wk->targetpos;
  vct_B = targetpos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v11 = &workdata[7];
  v12 = (u8)byte_5755EF6;
  *v11 = vct_B;
  if (v12)
    goto LABEL_24;
  goto LABEL_50;
  if (v29)
  {
LABEL_24:
    goto LABEL_25;
  }
LABEL_50:
LABEL_25:
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  v35.x = x;
  v35.y = y;
  v35.z = z;
  v35.w = w;
  dds3SetPosPoseSet(&wk->cm, v35);
  v36.w = 1.0;
  v36.x = 0.0;
  v36.y = 0.0;
  v36.z = 0.0;
  dds3SetRotPoseSet(&wk->cm, v36);
  vct_A = (struct sdfVector4_t)xmmword_3D05530;
  v20 = workdata + 6;
  *v20 = (struct Project_Basic_dds3Basic_t_WORK_o)vct_A;
  fovy = wk->fovy;
  dds3CameraObjectBasicSetFovy(&wk->cm, fovy);
  v24 = p_cm->workdata;
  if (v24)
  {
    if (v24->klass->_2.naturalAligment < (u32)v25 || v24->klass->_2.typeHierarchy[v25 - 1] != dds3CameraObjectBasicWorkData_t)
    {
LABEL_58:
    }
  }
  HIDWORD(v24[9].monitor) |= 1u;
  ActiveScene = dds3GetActiveScene();
  v27 = p_cm;
  SetActiveCamera(ActiveScene, v27, 0);
  return 1;
}

// 0x1f02340
static dds3ProcessFunc_t ProcCamera(dds3ProcessID_t *id) {
  return 0;
}

// 0x1f02350
static void ShutdownCamera(dds3ProcessID_t *id) {
  ;
}

// 0x1eeec30
static bool PrintfZa(void) {
  return 1;
}

// 0x1eeec40
static bool CalcCameraPara(void) {
  SBTLCAMERA_WORK *camera;

  camera = wk->scene->camera;
  SetPara(camera);
  return 1;
}

// 0x1ef0340
void sBtlNoHokan(void) {
  gsBtlCamera_Hokan_Not = 1;
  return;
}

// 0x1f02360
void sBtlNoHokan_Ring(void) {
  gsBtlCamera_RingHokan_Not = 1;
  return;
}

// 0x1efc550
bool sBtlSetMode(E_CAMERA_MODE no) {
  s32 v5;
  s32 v6;
  s32 v7;
  SBATTLE_WORK *v8;
  SBTLSCENE_WORK *scene;
  SBTLCAMERA_WORK *camera;
  sdfVector4_t *p_camerapos_bk;
  s32 v16;
  struct sdfVector4_t direction;
  sdfVector4_t *p_direction_bk;
  s32 v19;
  struct sdfVector4_t v20;
  sdfVector4_t *p_targetpos_bk;
  sdfVector4_t *m_PosCtrlCam;
  sdfVector4_t *v24;
  s32 v25;
  struct sdfVector4_t targetpos;
  sdfVector4_t *m_PosCtrlTgt;
  sdfVector4_t *v28;
  s32 v29;
  s32 v30;
  s32 v31;
  struct sdfVector4_t camerapos;
  struct sdfVector4_t v33;
  struct sdfVector4_t v34;
  struct sdfVector4_t v36;
  struct sdfVector4_t v38;

  if (no != 2)
    goto LABEL_10;
  if (wk->bBfrBtlEnd)
    goto LABEL_10;
  if (!wk->bosseventflg)
    goto LABEL_70;
LABEL_10:
  v5 = 0;
  v6 = 0;
  v5 = v6;
  v7 = no;
  goto LABEL_13;
LABEL_70:
  no = 0;
  v7 = 0;
  v5 = 200;
LABEL_13:
  wk->scene->camCnt = v5;
  v8 = wk;
  scene = v8->scene;
  camera = scene->camera;
  scene->camCnt2 = 0;
  if (!camera)
    return 1;
  camera->mode = v7;
  v8 = wk;
  *(u64 *)&v8->camTgtConsF = 0;
  if (v7 != 13)
  {
    camerapos = camera->camerapos;
    goto LABEL_21;
  }
  v33 = camera->camerapos;
  vct_A = v33;
  m_PosCtrlCam = camera->m_CamMov->m_PosCtrlCam;
  v24 = m_PosCtrlCam + 1;
  v25 = (u8)byte_5755EF5;
  *v24 = vct_A;
  targetpos = camera->targetpos;
  if (v25)
    goto LABEL_42;
  goto LABEL_65;
  if (v31)
  {
LABEL_42:
    goto LABEL_43;
  }
LABEL_65:
  v38 = targetpos;
  targetpos = v38;
LABEL_43:
  vct_A = targetpos;
  m_PosCtrlTgt = camera->m_CamMov->m_PosCtrlTgt;
  v28 = m_PosCtrlTgt + 1;
  *v28 = vct_A;
  camerapos = camera->camerapos;
LABEL_21:
  vct_A = camerapos;
  p_camerapos_bk = &camera->camerapos_bk;
  v16 = (u8)byte_5755EF5;
  *p_camerapos_bk = vct_A;
  direction = camera->direction;
  if (v16)
    goto LABEL_26;
  goto LABEL_52;
  if (v29)
  {
LABEL_26:
    goto LABEL_27;
  }
LABEL_52:
  v34 = direction;
  direction = v34;
LABEL_27:
  vct_A = direction;
  p_direction_bk = &camera->direction_bk;
  v19 = (u8)byte_5755EF5;
  *p_direction_bk = vct_A;
  v20 = camera->targetpos;
  if (v19)
    goto LABEL_30;
  goto LABEL_56;
  if (v30)
  {
LABEL_30:
    goto LABEL_31;
  }
LABEL_56:
  v36 = v20;
  v20 = v36;
LABEL_31:
  vct_A = v20;
  p_targetpos_bk = &camera->targetpos_bk;
  *p_targetpos_bk = vct_A;
  return 1;
}

// 0x1f023f0
E_CAMERA_MODE sBtlGetMode(void) {
  return wk->scene->camera->mode;
}

// 0x1f02460
static bool SetWork(SBTLCAMERA_WORK *cm, SBTLCAMERA_DATA *cdata, const sdfVector4_t *target, const sdfVector4_t *camera) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 *p_x;
  f32 *v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 *v23;
  f32 *v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 *v29;
  sdfVector4_t *p_targetpos;
  s32 v31;
  f32 *v32;
  sdfVector4_t *p_camerapos;
  s32 v34;
  f32 *v35;
  f32 *v36;
  f32 *v37;
  f32 v38;
  f32 v39;
  f32 v40;
  s32 v49;
  s32 v51;

  w = camera->w;
  z = camera->z;
  y = camera->y;
  x = camera->x;
  v9 = target->w;
  v10 = target->z;
  v11 = target->y;
  v12 = target->x;
  p_x = &vf00.x;
  p_x[4] = v12;
  p_x[5] = v11;
  p_x[6] = v10;
  p_x[7] = v9;
  v18 = &vf00.x;
  v19 = v18[4];
  v20 = v18[5];
  v21 = v18[6];
  v22 = v18[7];
  v23 = &vf00.x;
  v23[4] = x;
  v23[5] = y;
  v23[6] = z;
  v23[7] = w;
  v24 = &vf00.x;
  v25 = v24[4];
  v26 = v24[5];
  v27 = v24[6];
  v28 = v24[7];
  v29 = &vf00.x;
  v29[4] = v19;
  v29[5] = v20;
  v29[6] = v21;
  v29[7] = v22;
  p_targetpos = &cm->targetpos;
  v31 = (u8)byte_5755EF5;
  *p_targetpos = vct_A;
  if (v31)
    goto LABEL_16;
  goto LABEL_46;
  if (v49)
  {
LABEL_16:
    goto LABEL_17;
  }
LABEL_46:
LABEL_17:
  v32 = &vf00.x;
  v32[4] = v25;
  v32[5] = v26;
  v32[6] = v27;
  v32[7] = v28;
  p_camerapos = &cm->camerapos;
  v34 = (u8)byte_5755EF5;
  *p_camerapos = vct_A;
  if (v34)
    goto LABEL_20;
  goto LABEL_50;
  if (v51)
  {
LABEL_20:
    goto LABEL_21;
  }
LABEL_50:
LABEL_21:
  v35 = &vf00.x;
  v35[4] = v19;
  v35[5] = v20;
  v35[6] = v21;
  v35[7] = v22;
  v36 = &vf00.x;
  v36[8] = v25;
  v36[9] = v26;
  v36[10] = v27;
  v36[11] = v28;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v37 = &vf00.x;
  v38 = v37[6];
  v39 = v37[4];
  v40 = v37[5];
  cm->distance = sqrtf((f32)((f32)(v39 * v39) + (f32)(v40 * v40)) + (f32)(v38 * v38));
  sub_1949110(0);
  cm->direction = vct_A;
  cm->fovy = cdata->fovy * 0.017453292;
  return 1;
}

// 0x1f02a20
static bool GetTargetData(SBTLC_DATA *cd, const sdfVector4_t *tpos) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v8;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 deg;
  f32 distance;
  f32 v18;
  float32x2_t *v22;
  float32x2_t v23;
  f32 offsz;
  u32 v25;
  f32 v26;
  float32x2_t v27;
  float32x2_t v28;
  f32 v29;
  float32x2_t *v30;
  struct sdfVector4_t v33;
  struct sdfVector4_t vct_A_local;
  struct sdfVector4_t pos;
  sdfMatrix4_t v36;
  sdfMatrix4_t v37;
  sdfVector4_t v38;
  sdfVector4_t v39;

  vct_A_local = (struct sdfVector4_t)0;
  if (cd->menu != 1)
  {
    distance = cd->distance;
    v33 = (struct sdfVector4_t)0;
    goto LABEL_22;
  }
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v8 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v8)
  {
    pos = v8->pos;
    vct_A = pos;
    x = v8->rot.x;
    y = v8->rot.y;
    z = v8->rot.z;
    w = v8->rot.w;
    vct_A_local = vct_A;
    deg = cd->deg;
    v39.x = x;
    v39.y = y;
    v39.z = z;
    v39.w = w;
    sBtlGetRotateDeg(v39, deg);
    distance = cd->distance;
    v33 = vct_A;
    goto LABEL_22;
  }
  distance = cd->distance;
  v33 = (struct sdfVector4_t)0;
LABEL_22:
  v18 = -distance;
  *(u64 *)&vct_B.x = 0;
  vct_B.z = v18;
  vct_B.w = 1.0;
  vct_A = v33;
  ToMatrix();
  get_transpose(&v37, &mtx_A, 0);
  *(_OWORD *)&v36.m00 = *(_OWORD *)&v37.m00;
  *(_OWORD *)&v36.m01 = *(_OWORD *)&v37.m01;
  *(_OWORD *)&v36.m02 = *(_OWORD *)&v37.m02;
  *(_OWORD *)&v36.m03 = *(_OWORD *)&v37.m03;
  v38 = op_Multiply_60923920(&v36, vct_B, 0);
  vct_B = v38;
  vct_A = vct_A_local;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v23.n64_u64[0] = *(u64 *)&cd->offsx;
  offsz = cd->offsz;
  v26 = v22[3].n64_f32[0];
  v25 = v22[3].n64_u32[1];
  v27.n64_u64[0] = v22[2].n64_u64[0];
  v28.n64_u64[0] = vadd_f32(v27, v23).n64_u64[0];
  v29 = v26 + offsz;
  v30[2].n64_u64[0] = v28.n64_u64[0];
  v30[3].n64_f32[0] = v29;
  v30[3].n64_u32[1] = v25;
  return 1;
}

// 0x1f02fb0
static bool GetCameraData(SBTLC_DATA *cd, const sdfVector4_t *cpos) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v8;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 deg;
  f32 distance;
  f32 v18;
  float32x2_t *v22;
  float32x2_t v23;
  f32 offsz;
  u32 v25;
  f32 v26;
  float32x2_t v27;
  float32x2_t v28;
  f32 v29;
  float32x2_t *v30;
  struct sdfVector4_t v33;
  struct sdfVector4_t vct_A_local;
  struct sdfVector4_t pos;
  sdfMatrix4_t v36;
  sdfMatrix4_t v37;
  sdfVector4_t v38;
  sdfVector4_t v39;

  vct_A_local = (struct sdfVector4_t)0;
  if (cd->menu != 1)
  {
    distance = cd->distance;
    v33 = (struct sdfVector4_t)0;
    goto LABEL_22;
  }
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v8 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v8)
  {
    pos = v8->pos;
    vct_A = pos;
    x = v8->rot.x;
    y = v8->rot.y;
    z = v8->rot.z;
    w = v8->rot.w;
    vct_A_local = vct_A;
    deg = cd->deg;
    v39.x = x;
    v39.y = y;
    v39.z = z;
    v39.w = w;
    sBtlGetRotateDeg(v39, deg);
    distance = cd->distance;
    v33 = vct_A;
    goto LABEL_22;
  }
  distance = cd->distance;
  v33 = (struct sdfVector4_t)0;
LABEL_22:
  v18 = -distance;
  *(u64 *)&vct_B.x = 0;
  vct_B.z = v18;
  vct_B.w = 1.0;
  vct_A = v33;
  ToMatrix();
  get_transpose(&v37, &mtx_A, 0);
  *(_OWORD *)&v36.m00 = *(_OWORD *)&v37.m00;
  *(_OWORD *)&v36.m01 = *(_OWORD *)&v37.m01;
  *(_OWORD *)&v36.m02 = *(_OWORD *)&v37.m02;
  *(_OWORD *)&v36.m03 = *(_OWORD *)&v37.m03;
  v38 = op_Multiply_60923920(&v36, vct_B, 0);
  vct_B = v38;
  vct_A = vct_A_local;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v23.n64_u64[0] = *(u64 *)&cd->offsx;
  offsz = cd->offsz;
  v26 = v22[3].n64_f32[0];
  v25 = v22[3].n64_u32[1];
  v27.n64_u64[0] = v22[2].n64_u64[0];
  v28.n64_u64[0] = vadd_f32(v27, v23).n64_u64[0];
  v29 = v26 + offsz;
  v30[2].n64_u64[0] = v28.n64_u64[0];
  v30[3].n64_f32[0] = v29;
  v30[3].n64_u32[1] = v25;
  return 1;
}

// 0x1f03540
E_CAMMOD_CUT sBtlGetCutFlg(void) {
  if ((wk->scene->camera->mode & 0xFFFFFFFE) == 6)
    return 15;
  else
    return 0;
}

// 0x1f035c0
void sBtlSetPos(const sdfVector4_t *pvPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  SBTLCAMERA_WORK *camera;

  w = pvPos->w;
  z = pvPos->z;
  y = pvPos->y;
  x = pvPos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  camera = wk->scene->camera;
  camera->camerapos = vct_A;
}

// 0x1f03750
void sBtlSetPosSlp(const sdfVector4_t *pvPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;

  w = pvPos->w;
  z = pvPos->z;
  y = pvPos->y;
  x = pvPos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  wk->camPos_t = vct_A;
}

// 0x1f038e0
void sBtlBgnPosSlp(void) {
  SBATTLE_WORK *v6;
  struct sdfVector4_t camerapos;

  wk->bCamPosSlp = 1;
  wk->camPosSlpCnt = 0;
  wk->camPosSlpTime = 30;
  camerapos = wk->scene->camera->camerapos;
  vct_A = camerapos;
  v6 = wk;
  v6->camPos_s = vct_A;
}

// 0x1f03a50
s32 sBtlGetPosSlp(void) {
  return wk->bCamPosSlp;
}

// 0x1f03ae0
void sBtlSetTgt(const sdfVector4_t *pvTgt) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  SBTLCAMERA_WORK *camera;

  w = pvTgt->w;
  z = pvTgt->z;
  y = pvTgt->y;
  x = pvTgt->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  camera = wk->scene->camera;
  camera->targetpos = vct_A;
}

// 0x1f03c70
void sBtlSetTgtSlp(const sdfVector4_t *pvTgt) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;

  w = pvTgt->w;
  z = pvTgt->z;
  y = pvTgt->y;
  x = pvTgt->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  wk->camTgt_t = vct_A;
}

// 0x1f03e00
void sBtlBgnTgtSlp(void) {
  SBATTLE_WORK *v6;
  struct sdfVector4_t targetpos;

  wk->bCamTgtSlp = 1;
  wk->camTgtSlpCnt = 0;
  wk->camTgtSlpTime = 30;
  targetpos = wk->scene->camera->targetpos;
  vct_A = targetpos;
  v6 = wk;
  v6->camTgt_s = vct_A;
}

// 0x1f03f70
s32 sBtlGetTgtSlp(void) {
  return wk->bCamTgtSlp;
}

// 0x1f04000
void sBtlSetCameraLockOnTgtPos(f32 x, f32 y, f32 z) {
  f32 *camera;
  SBTLCAMERA_WORK *v9;
  f32 v10;
  f32 GroundPos;

  camera = wk->scene->camera;
  camera[44] = x;
  camera[45] = y;
  camera[46] = z;
  v9 = wk->scene->camera;
  v10 = v9->CameraLockOnTargetPos.y;
  GroundPos = sBtlGetGroundPos(x, z);
  v9->CameraLockOnTargetPos.y = v10 - GroundPos;
  wk->scene->camera->CameraLockOnNone = 0;
}

// 0x1f04100
void sBtlSetCameraLockOnTgtNone(void) {
  wk->scene->camera->CameraLockOnNone = 1;
}

// 0x1f04170
f32 sBtlGetCameraLockOnX(void) {
  return wk->scene->camera->followUpAngle.x;
}

// 0x1f041e0
void sBtlSetCameraHighTargetUse(bool _Use, s32 _TargetID) {
  SBTLCAMERA_WORK *camera;

  camera = wk->scene->camera;
  camera->CameraHighTargetID = TargetID;
  camera->CameraHighTargetUse = Use;
}

// 0x1f01c40
static void UpdateAwCamera(void) {
  f32 *camera;
  f32 v3;
  f32 v4;
  f32 v5;

  camera = wk->scene->camera;
  v3 = camera[18];
  v4 = camera[16];
  v5 = camera[17];
  SetCameraPs2Pos(v4, v5, v3);
}

// 0x1f04260
f32 sBtlGetCameraDir(void) {
  return wk->scene->camera->followUpAngle.x;
}

// 0x1f042d0
void sBtlPushCamera(void) {
  SBTLCAMERA_WORK *camera;

  camera = wk->scene->camera;
  gBk_followUpAngle = camera->followUpAngle;
  gBk_targetpos = camera->targetpos;
  gBk_camerapos = camera->camerapos;
  gBk_Fovy = camera->fovy;
  gBk_UpV = camera->vertical;
}

// 0x1f04390
void sBtlPopCamera(void) {
  SBTLCAMERA_WORK *camera;

  camera = wk->scene->camera;
  camera->followUpAngle = gBk_followUpAngle;
  camera->targetpos = gBk_targetpos;
  camera->camerapos = gBk_camerapos;
  camera->fovy = gBk_Fovy;
  camera->vertical = gBk_UpV;
}

// 0x1f04450
bool sBtlChkSideBySide(void) {
  return gAuto_Status == 7;
}

// 0x1f044c0
void sBtlResetFollowUpAngleX(f32 _followUpAngle_x) {
  wk->scene->camera->followUpAngle.x = followUpAngle_x;
  gAuto_Status = 0;
}

// 0x1f04580
void sBtlResetTargetFollowUpAngleX(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 z;
  SBTLCAMERA_WORK *camera;
  f32 v7;
  f32 v8;
  f32 PosToDir;

  x = wk->pos.x;
  z = wk->pos.z;
  camera = wk->scene->camera;
  v7 = camera->CameraLockOnTargetPos.x;
  v8 = camera->CameraLockOnTargetPos.z;
  PosToDir = sBtlGetPosToDir(v7, v8, x, z);
  camera->followUpAngle.x = PosToDir;
  gAuto_Status = 0;
}

// 0x1f04680
void sBtlResetGazeOnOff(void) {
  gAuto_ManualKaiten_Cnt = 0;
  gKaitenHiSpd = 1;
}

// 0x1f046f0
void sBtlResettgtCng(void) {
  gAuto_ManualKaiten_Cnt = 0;
  gKaitenHiSpd = 1;
}

// 0x1f04760
void sBtlSetBossTalkTarget(SBTLUNIT_WORK *_wk) {
  s32 ListID;

  ListID = wk->ListID;
  gBossTalk_targetID = ListID;
  return;
}
