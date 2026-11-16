#include "types.h"
#include "dds3_pad.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3padmanager.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "evt.h"
#include "evtmoon.h"
#include "fclmisc.h"
#include "fld.h"
#include "kernel.h"
#include "mdl.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlexp.h"
#include "sbtlmain.h"
#include "sbtlpanel.h"
#include "sbtlscene.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sndat3.h"

#define SBTL_SCENEDEBUG_NO 1
#define EFFVIEWER_MOVE_SPEED 11.25
#define EFFVIEWER_ROT_SPEED 0.03

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct sdfPacDecodeResrcHandle_t sdfPacDecodeResrcHandle_t;

static s32 gSbtlScene_Zoom2On;
static f32 gSbtlScene_Zoom2X;
static f32 gSbtlScene_Zoom2Y;
static f32 gSbtlScene_Zoom2Z;
static s32 gSbtlScene_Zoom2FrameGoal;
static s32 gSbtlScene_Zoom2FrameNow;
static f32 gSbtlScene_Zoom2ScaleGoal;
static f32 gSbtlScene_Zoom2ScaleStart;
static f32 gSbtlScene_Zoom2ScaleNow;
static s32 gSbtlScene_ForceScrollOn;
static f32 gSbtlScene_ForceScrollX;
static f32 gSbtlScene_ForceScrollY;
static f32 gSbtlScene_ForceScrollZ;
static s32 gSbtlScene_UnitScrollOn;
static s32 gSbtlScene_UnitScrollID;
static s32 gSbtlSceneRndEnc_ID;
static s32 gSbtlSceneRndEnc_Map;
static s32 gSbtlSceneRndEnc_Floor;
static s32 gSbtlSceneRndEnc_IDFlag;
static sdfVector4_t CameraTargetPos_Bk;
static sdfVector4_t CameraEyePos_Bk;
static sdfVector4_t CameraUpVec_Bk;
static f32 Camerafov_Bk;
static sdfVector4_t raidouPos_Bk;
static sdfVector4_t raidouRot_Bk;
sdfVector4_t nakama_pos;
sdfVector4_t nakama_rot;
f32 nakama_mv_rotbk;
static char *gMapSceneName;
static char *gMapAssetName;
static s32 freeUIsts;
static s32 loadstep;
static sdfPacDecodeResrcHandle_t *mpBgFile;
static s32 sizeBgFile;
static pacFileHandle_t *pacHandle_Bg;
static s32 gBg_Minor;
static u32 *aMapMdl;

static void SetMapLight(dds3Basic_t *unit, u32 lgba, u32 rgba);
static dds3ProcessFunc_t DataLoadProc(dds3ProcessID_t *id);
static void DataLoadShutdown(dds3ProcessID_t *id);
static bool BasicSceneFree(void);
static bool SetTestCamera(void);
static bool DebugPad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic);
static void BgLoad_Block(void);
static void BgLoad_UnBlock(void);
static bool LoadMap_FromMemory(s32 fldno, s32 floorno);
static sdfVector4_t MakeMapColor(u32 rgba);

// 0x1fbec10
void sBtlBackUpCamera(void) {
  struct sdfVector4_t CameraUpVector_local;

  CameraUpVector_local = CameraUpVector;
  CameraUpVec_Bk = CameraUpVector_local;
  CameraEyePos_Bk = CameraEyePos;
  CameraTargetPos_Bk = CameraTargetPos;
  Camerafov_Bk = ScreenParam->fovy;
}

// 0x1fbed60
void sBtlReturnCamera(void) {
  struct sdfVector4_t CameraUpVec_Bk_local;

  CameraUpVec_Bk_local = CameraUpVec_Bk;
  CameraUpVector = CameraUpVec_Bk_local;
  CameraEyePos = CameraEyePos_Bk;
  CameraTargetPos = CameraTargetPos_Bk;
  ScreenParam->fovy = Camerafov_Bk;
}

// 0x1fbeeb0
void sBtlBackUpCharTsf(void) {
  SBTLUNIT_WORK *PChara;
  struct sdfVector4_t pos;

  PChara = sBtlGetPChara();
  pos = PChara->pos;
  raidouPos_Bk = pos;
  raidouRot_Bk = PChara->rot;
}

// 0x1fbef40
void sBtlReturnCharTsf(void) {
  SBTLUNIT_WORK *PChara;

  PChara = sBtlGetPChara();
  PChara->pos = raidouPos_Bk;
  PChara->rot = raidouRot_Bk;
}

// 0x1fbefc0
static void SetMapLight(dds3Basic_t *unit, u32 lgba, u32 rgba) {
  evtUnitHandle_t *UnitHandle2;
  dds3Basic_t *unita;

  unita = unit;
  if (unit)
  {
    UnitHandle2 = evtGetUnitHandle2(unita);
    evtUnitLightOn(UnitHandle2);
    evtSetUnitLightAndAmbient(UnitHandle2, 0, lgba, rgba);
  }
}

// 0x1fbf070
void sBtlSetRndEncBg(s32 rnd_enc_id, bool isSymbolEncount) {
  s32 RndEncJoken;
  datRndEncTbl_t *RndEncTbl_t;
  s32 map;

  gSbtlSceneRndEnc_ID = rnd_enc_id;
  RndEncJoken = sBtlGetRndEncJoken(rnd_enc_id);
  RndEncTbl_t = sBtlGetRndEncTbl_t(rnd_enc_id, RndEncJoken);
  map = RndEncTbl_t->map;
  LODWORD(RndEncTbl_t) = RndEncTbl_t->floor;
  gSbtlSceneRndEnc_Map = map;
  gSbtlSceneRndEnc_Floor = (s32)RndEncTbl_t;
  gSbtlSceneRndEnc_IDFlag = isSymbolEncount;
}

// 0x1fbf1a0
void sBtlInitSceneRndEnc_IDFlag(void) {
  if (!gSbtlSceneRndEnc_IDFlag)
    return;
  gSbtlSceneRndEnc_IDFlag = 0;
}

// 0x1fbf250
bool Init(void) {
  SBTLSCENE_WORK *scene;
  SBTLSCENE_WORK *v4;
  s32 v7;
  s32 v9;
  SBTLSCENE_WORK *v10;
  dds3ProcessFunc_t v11;
  shutdownfuncDelegate v12;
  SB_ENCOUNTPAC *EncountPac;
  s64 encountno;
  SBTLSCENE_WORK *v19;
  SB_ENCOUNTPAC *v20;
  u32 start_map;
  s32 floor[2];

  *(u64 *)floor = 0;
  if (!gSbtlSceneRndEnc_Map)
  {
    if (!gSbtlSceneRndEnc_Floor)
      goto LABEL_28;
  }
  scene = wk->scene;
  v4 = scene;
  scene->major = gSbtlSceneRndEnc_Map;
  v4->minor = gSbtlSceneRndEnc_Floor;
  *(u64 *)&gSbtlSceneRndEnc_Map = 0;
  goto LABEL_15;
LABEL_28:
  EncountPac = sBtlGetEncountPac(-1);
  encountno = wk->encountno;
  v19 = wk->scene;
  v20 = EncountPac[encountno];
  start_map = v20->start_map;
  LODWORD(v20) = v20->start_floor;
  v19->major = start_map;
  v19->minor = (u32)v20;
LABEL_15:
  if (gSbtlSceneRndEnc_IDFlag)
  {
    sBtlRndEncTopPriorityMap(&floor[1], floor);
    v7 = floor[1];
    if (floor[1] >= 1)
    {
      v7 = floor[1];
      v9 = floor[0];
      v10 = wk->scene;
      v10->major = v7;
      v10->minor = v9;
    }
  }
  fclFilterOFF();
  v11 = Allocate(dds3ProcessFunc_t);
  _ctor(v11, 0, Method_Project_sBtlScene_DataLoadProc__, 0);
  v12 = Allocate(shutdownfuncDelegate);
  _ctor(v12, 0, Method_Project_sBtlScene_DataLoadShutdown__, 0);
  dds3StartProcess("sbtlscene_load", 1016, 1, 1, v11, v12, 0);
  return 1;
}

// 0x1fbf580
void sBtlDrawON(void) {
  u32 status;

  status = wk->status;
  if ((status & 0x200000) == 0)
    return;
  wk->status = status & 0xFFDFFFFF;
  sBtlMapVisiblerSet(1);
  return;
}

// 0x1fbf890
bool Draw(void) {
  dds3Basic_t *basic;

  basic = dds3GetActiveScene();
  if (!basic)
    return 1;
  if (ProcessCheck())
    goto LABEL_13;
  if (dds3FadeCheck())
    goto LABEL_13;
  goto LABEL_9000;
  if (dds3FadeCheck())
  {
LABEL_13:
    goto LABEL_14;
  }
LABEL_9000:
  dds3SceneBasicVisible(basic, 1);
LABEL_14:
  if ((wk->status2 & 0x4000) != 0)
    return 1;
  return 1;
}

// 0x1fbfa50
f32 sBtlGetGroundPos(f32 x, f32 z) {
  f32 result;

  result = mapGetY(x, z);
  if (result == -99999.0)
    return 0.0;
  return result;
}

// 0x1fbfae0
bool sBtlFree(void) {
  u32 status;
  s32 i;
  void *readdvl;
  s32 Item;
  char *DevilModelName;
  s32 v10;

  status = wk->status;
  if ((status & 1) == 0)
    return status & 1;
  if (wk)
  {
    if ((wk->status & 0x10) != 0)
      return status & 1;
  }
  for (i = 0; ; ++i)
  {
    readdvl = wk->readdvl;
    if (i >= readdvl->_size)
      break;
    readdvl = wk->readdvl;
    Item = _get_Item(readdvl, i);
    DevilModelName = mdlGetDevilModelName(Item);
    Unload(Dependent, DevilModelName, 0);
  }
  readdvl = wk->readdvl;
  v10 = readdvl->_version + 1;
  readdvl->_size = 0;
  readdvl->_version = v10;
  evtMoonDisableDraw(1);
  BasicSceneFree();
  mdlUnRegist(2u, gBg_Minor);
  wk->status |= 0x10u;
  return status & 1;
}

// 0x1fc0040
bool sBtlFreeBgScene(void) {
  u32 fieldmap_use;
  void *Instance;
  s32 i;
  char *name;
  void *v17;
  void *v19;
  s32 m_Handle;
  UnityEngine_SceneManagement_Scene_o v23;

  m_Handle = 0;
  goto LABEL_3;
LABEL_9:
  if (bgSceneOp)
  {
    if (get_isDone(bgSceneOp, 0))
      goto LABEL_22;
    return 0;
  }
  for (i = 0; ; ++i)
  {
    if (i >= get_sceneCount(0))
      break;
    m_Handle = GetSceneAt(i, 0).m_Handle;
    name = get_name((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0);
    if (Contains(name, gMapSceneName, 0))
    {
      v23.m_Handle = GetSceneByName("System", 0).m_Handle;
      SetActiveScene(v23, 0);
      GetActiveScene(0);
      v19 = UnloadSceneAsync(name, 0);
      bgSceneOp = v19;
      return 0;
    }
  }
  goto LABEL_22;
LABEL_3:
  fieldmap_use = wk->fieldmap_use;
  if (!fieldmap_use)
    goto LABEL_9;
  if (fieldmap_use != 1)
    goto LABEL_22;
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
  {
    goto LABEL_20;
  }
  v17 = get_Instance(0);
  SetPos(v17, 0.0, 0.0, 0.0);
LABEL_20:
  sBtlFldMapDisp(0, 0);
  wk->fieldmap_use = 2;
LABEL_22:
  wk->status5 |= 1u;
  bgSceneOp = 0;
  return 1;
}

// 0x1fc0530
bool sBtlReLoadFldScene(void) {
  char *v4;
  void *SceneAsync;

  if (IsNullOrEmpty(ret_field_scene, 0))
    goto LABEL_18;
  if (Equals_54828784(ret_field_scene, "bg23", 0))
    v4 = "bg23-01";
  else
    v4 = ret_field_scene;
  if (fdSceneOp)
  {
    if (get_isDone(fdSceneOp, 0))
    {
      Unload(Dependent, v4, 0);
LABEL_18:
      fdSceneOp = 0;
      ret_field_scene = 0;
      return 1;
    }
    return 0;
  }
  Load(Dependent, v4, v4);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, ret_field_scene, 0);
  fdSceneOp = SceneAsync;
  return 0;
}

// 0x1fc0440
void sBtlFldMapDisp(bool flg, char *sName) {
  void *v6;

  if (!sName)
  {
    sName = gMapSceneName;
  }
  v6 = GetFromScene(sName, 0);
  if (!op_Inequality(v6, 0, 0))
    return;
  goto LABEL_9;
  if (op_Inequality(v6, 0, 0))
LABEL_9:
    SetActive(v6, flg, 0);
}

// 0x1fc0850
bool sBtlFreeUIScene(void) {
  void *Instance;
  void *v5;

  if (freeUIsts != 300)
  {
    if (freeUIsts == 101)
    {
      freeUIsts = 300;
      return 0;
    }
    else if (freeUIsts)
    {
      return 0;
    }
    else
    {
      Instance = get_Instance(0);
      End(Instance, 0);
      v5 = get_Instance(0);
      End(v5, 0);
      freeUIsts = 101;
      return 0;
    }
  }
  wk->status5 |= 4u;
  return 1;
}

// 0x1fc0a10
void sBtlFreeUISceneEnd(void) {
  struct sBtlScene *static_fields;

  uiSceneOp0 = 0;
  static_fields = ((char *)static_fields + 232);
  gSbtlScene_Zoom2ScaleGoal = 0.0;
  uiSceneOp1 = 0;
  uiSceneOp2 = 0;
}

// 0x1fc0aa0
bool sBtlSetScrollID(s32 id) {
  wk->scrollID = id;
  return 1;
}

// 0x1fc0b10
bool sBtlRestart_Scene(void) {
  wk->status &= ~0x40u;
  *(u32 *)wk->gstat = 0;
  return 1;
}

// 0x1fc0b90
static dds3ProcessFunc_t DataLoadProc(dds3ProcessID_t *id) {
  dds3ProcessFunc_t result;
  s64 encountno;
  s32 bgm;
  SBTLSCENE_WORK *scene;
  s32 major;
  s32 minor;
  u32 v15;
  s32 v20;
  dds3ProcessFunc_t v22;

  goto LABEL_4;
  if (loadstep > 3)
  {
LABEL_10:
    if (loadstep != 100)
      return 0;
    if (encWait())
      return 0;
    loadstep = 3;
    if (BYTE4(Flish_mesh))
    {
      (loc_1FDB450)(1, 0);
      return 0;
    }
    return 0;
  }
LABEL_4:
  switch (loadstep)
  {
    case 0u:
      loadstep = 1;
      return 0;
    case 1u:
      encountno = wk->encountno;
      bgm = sBtlGetEncountPac(-1)[encountno]->bgm;
      sndBgmPlay(bgm, 0);
      loadstep = 2;
      return 0;
    case 2u:
      scene = wk->scene;
      major = scene->major;
      minor = scene->minor;
      LoadMap_FromMemory(major, minor);
      if (BYTE4(Flish_mesh))
        v15 = 0;
      else
        v15 = 15;
      dds3FadeIn2(v15);
      loadstep = 100;
      sBtlSetLoadPanelData();
      result = 0;
      break;
    case 3u:
      if (!sBtlCheckLoadData())
        return 0;
      v20 = wk->encountno;
      wk->status2 |= 0x800u;
      sBtlSetEncountPacData(v20);
      sBtlEnemyViceInit();
      loadstep = 0;
      v22 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v22, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v22;
    default:
      goto LABEL_10;
  }
  return result;
}

// 0x1fc34a0
static void DataLoadShutdown(dds3ProcessID_t *id) {
  sBtlOnDataLoadInit();
}

// 0x1fbfe00
static bool BasicSceneFree(void) {
  dds3Basic_t *ActiveScene;
  void *workdata;
  dds3Basic_t *i;
  dds3Basic_t *scene;

  ActiveScene = dds3GetActiveScene();
  scene = ActiveScene;
  if (!ActiveScene)
    return ActiveScene != 0;
  workdata = ActiveScene->workdata;
  for (i = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24); i; i = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24))
  {
    dds3SceneBasicDelete(i);
  }
  dds3DeleteScene(scene);
  return ActiveScene != 0;
}

// 0x1fc3510
static bool SetTestCamera(void) {
  u32 v2;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *v4;
  dds3Basic_t *pBasic;
  sdfVector4_t v8;
  sdfVector4_t v9;
  sdfVector4_t v10;

  v2 = dds3SerializeID();
  v9.w = 1.0;
  v9.x = 0.0;
  v9.y = 0.0;
  v9.z = 0.0;
  v10.x = 0.0;
  v10.y = 0.0;
  v10.z = 10.0;
  v10.w = 1.0;
  *(u64 *)&v8.x = 0;
  pBasic = dds3CameraObjectBasicAddTypeLookAt(v2, v9, v10, v8);
  dds3SetBasicName(pBasic, "sbtl_Cam");
  dds3SetRadiusPoseSet(pBasic, 10.0);
  dds3ObjectBaseCreateMover(pBasic);
  ActiveScene = dds3GetActiveScene();
  v4 = pBasic;
  SetActiveCamera(ActiveScene, v4, 0);
  dds3ObjectBaseSetPadControl(pBasic, 0);
  wk->status |= 1u;
  return 1;
}

// 0x1fc36e0
static bool DebugPad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic) {
  u8 AnalogLX;
  u8 AnalogLY;
  u8 AnalogRX;
  u8 AnalogRY;
  u8 v8;
  struct sdfVector4_t v11;
  struct sdfVector4_t v13;
  int32x2_t v15;
  int32x2_t v16;
  float32x2_t v17;
  float32x2_t v18;
  f32 *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v27;
  f32 v29;
  struct sdfVector4_t v30;
  struct sdfVector4_t v32;
  sdfVector4_t *v35;
  struct sdfVector4_t v38;
  struct sdfVector4_t v40;
  int32x2_t v42;
  int32x2_t v43;
  float32x2_t v44;
  float32x2_t v45;
  int32x2_t v48;
  int32x2_t v49;
  float32x2_t v50;
  float32x2_t v51;
  s32 v53;
  struct sdfVector4_t v54;
  sdfVector4_t *v56;
  struct sdfVector4_t v57;
  sdfVector4_t *v58;
  u8 v59;
  struct sdfVector4_t v62;
  s32 v63;
  f32 v64;
  f32 v65;
  f32 v67;
  int32x4_t v68;
  struct sdfVector4_t v69;
  sdfVector4_t *p_CameraEyePos;
  struct sdfVector4_t v72;
  sdfVector4_t *v74;
  struct sdfVector4_t CameraEyePos_local;
  struct sdfVector4_t CameraUpVector_local;
  int32x2_t v81;
  int32x2_t v82;
  float32x2_t v83;
  float32x2_t v84;
  int32x2_t v87;
  int32x2_t v88;
  float32x2_t v89;
  float32x2_t v90;
  f32 *p_x;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 v96;
  f32 v97;
  f32 v99;
  f32 v101;
  struct sdfVector4_t v102;
  struct sdfVector4_t v104;
  sdfVector4_t *p_CameraTargetPos;
  struct sdfVector4_t v110;
  struct sdfVector4_t v112;
  int32x2_t v114;
  int32x2_t v115;
  float32x2_t v116;
  float32x2_t v117;
  int32x2_t v120;
  int32x2_t v121;
  float32x2_t v122;
  float32x2_t v123;
  s32 v124;
  struct sdfVector4_t v127;
  struct sdfVector4_t v129;
  int32x2_t v131;
  int32x2_t v132;
  float32x2_t v133;
  float32x2_t v134;
  int32x2_t v137;
  int32x2_t v138;
  float32x2_t v139;
  float32x2_t v140;
  f32 *v142;
  f32 v143;
  f32 v144;
  f32 v145;
  f32 v146;
  f32 v147;
  f32 v149;
  f32 v151;
  struct sdfVector4_t v152;
  struct sdfVector4_t v154;
  sdfVector4_t *v157;
  struct sdfVector4_t v159;
  struct sdfVector4_t v160;
  struct sdfVector4_t v161;
  struct sdfVector4_t v163;
  struct sdfVector4_t v164;
  sdfMatrix4_t v208;
  sdfMatrix4_t v209;
  sdfVector4_t v210;
  sdfVector4_t v211;
  sdfVector4_t v212;
  sdfVector4_t v213;
  sdfVector4_t v215;

  AnalogLX = dds3PadGetAnalogLX(1);
  AnalogLY = dds3PadGetAnalogLY(1);
  if ((u8)(AnalogLY - 64) < 0x81u)
  {
    if ((u8)(AnalogLX - 64) < 0x81u)
      goto LABEL_7;
LABEL_117:
    vct_A = CameraTargetPos;
    CameraEyePos_local = CameraEyePos;
    vct_B = CameraEyePos_local;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_C = vct_A;
    vct_B = vct_A;
    CameraUpVector_local = CameraUpVector;
    vct_A = CameraUpVector_local;
    v81.n64_u64[0] = *(u64 *)&vct_B.y;
    v82.n64_u64[0] = *(u64 *)&vct_A.y;
    v83.n64_u32[0] = vdup_lane_s32(v81, 1).n64_u32[0];
    v84.n64_u32[0] = vdup_lane_s32(v82, 1).n64_u32[0];
    v83.n64_u32[1] = LODWORD(vct_B.x);
    v84.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v84.n64_f32[1] * v81.n64_f32[0])
                                  - (f32)(v83.n64_f32[1] * v82.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v82, v83), vmul_f32(v84, v81));
    sub_1949110(0);
    vct_B = vct_C;
    v87.n64_u64[0] = *(u64 *)&vct_B.y;
    v88.n64_u64[0] = *(u64 *)&vct_A.y;
    v89.n64_u32[0] = vdup_lane_s32(v87, 1).n64_u32[0];
    v90.n64_u32[0] = vdup_lane_s32(v88, 1).n64_u32[0];
    v89.n64_u32[1] = LODWORD(vct_B.x);
    v90.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v90.n64_f32[1] * v87.n64_f32[0])
                        - (f32)(v89.n64_f32[1] * v88.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v88, v89), vmul_f32(v90, v87));
    sub_1949110(0);
    p_x = &vf00.x;
    v93 = p_x[4];
    v94 = p_x[5];
    v96 = p_x[6];
    v95 = p_x[7];
    v97 = (128 - AnalogLX);
    v99 = v97 * 0.0078125;
    v101 = v99 * 0.03;
    sub_197D860(&mtx_A, 0, v101, v93, v94, v96, v95);
    v102 = CameraTargetPos;
    vct_A = v102;
    v104 = CameraEyePos;
    vct_B = v104;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    get_transpose(&v209, &mtx_A, 0);
    v208 = v209;
    v211 = op_Multiply_60923920(&v208, vct_A, 0);
    vct_A = v211;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_CameraTargetPos = &CameraTargetPos;
    *p_CameraTargetPos = vct_A;
    goto LABEL_8;
  }
  v59 = AnalogLY;
  v161 = CameraTargetPos;
  vct_A = v161;
  v62 = CameraEyePos;
  v63 = 128 - v59;
  vct_B = v62;
  v64 = v63;
  v65 = v64 * 0.0078125;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v67 = v65 * 11.25;
  v68 = vzip1q_s32((int32x4_t)LODWORD(v67), (int32x4_t)LODWORD(v67));
  v68.n128_f32[2] = v67;
  vct_B = (struct sdfVector4_t)v68;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_C = vct_A;
  v69 = CameraEyePos;
  vct_B = v69;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_CameraEyePos = &CameraEyePos;
  *p_CameraEyePos = vct_A;
  vct_A = vct_C;
  v72 = CameraTargetPos;
  vct_B = v72;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v74 = &CameraTargetPos;
  *v74 = vct_A;
  if ((u8)(AnalogLX - 64) >= 0x81u)
    goto LABEL_117;
LABEL_7:
LABEL_8:
  AnalogRX = dds3PadGetAnalogRX(1);
  AnalogRY = dds3PadGetAnalogRY(1);
  if ((u8)(AnalogRY - 64) >= 0x81u)
  {
    v8 = AnalogRY;
    v159 = CameraTargetPos;
    vct_A = v159;
    v11 = CameraEyePos;
    vct_B = v11;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_B = vct_A;
    v13 = CameraUpVector;
    vct_A = v13;
    v15.n64_u64[0] = *(u64 *)&vct_B.y;
    v16.n64_u64[0] = *(u64 *)&vct_A.y;
    v17.n64_u32[0] = vdup_lane_s32(v15, 1).n64_u32[0];
    v18.n64_u32[0] = vdup_lane_s32(v16, 1).n64_u32[0];
    v17.n64_u32[1] = LODWORD(vct_B.x);
    v18.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v18.n64_f32[1] * v15.n64_f32[0]) - (f32)(v17.n64_f32[1] * v16.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v16, v17), vmul_f32(v18, v15));
    sub_1949110(0);
    v20 = &vf00.x;
    v21 = v20[4];
    v22 = v20[5];
    v24 = v20[6];
    v23 = v20[7];
    v25 = (128 - v8);
    v27 = v25 * 0.0078125;
    v29 = v27 * 0.03;
    sub_197D860(&mtx_A, 0, v29, v21, v22, v24, v23);
    v30 = CameraTargetPos;
    vct_A = v30;
    v32 = CameraEyePos;
    vct_B = v32;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    get_transpose(&v209, &mtx_A, 0);
    v213 = vct_A;
    v208 = v209;
    v210 = op_Multiply_60923920(&v208, v213, 0);
    vct_A = v210;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v35 = &CameraTargetPos;
    *v35 = vct_A;
  }
  if (CHECK_PRESS(4107, 1))
  {
    v160 = CameraTargetPos;
    vct_A = v160;
    v38 = CameraEyePos;
    vct_B = v38;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_C = vct_A;
    vct_B = vct_A;
    v40 = CameraUpVector;
    vct_A = v40;
    v42.n64_u64[0] = *(u64 *)&vct_B.y;
    v43.n64_u64[0] = *(u64 *)&vct_A.y;
    v44.n64_u32[0] = vdup_lane_s32(v42, 1).n64_u32[0];
    v45.n64_u32[0] = vdup_lane_s32(v43, 1).n64_u32[0];
    v44.n64_u32[1] = LODWORD(vct_B.x);
    v45.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v45.n64_f32[1] * v42.n64_f32[0]) - (f32)(v44.n64_f32[1] * v43.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v43, v44), vmul_f32(v45, v42));
    sub_1949110(0);
    vct_B = vct_C;
    v48.n64_u64[0] = *(u64 *)&vct_B.y;
    v49.n64_u64[0] = *(u64 *)&vct_A.y;
    v50.n64_u32[0] = vdup_lane_s32(v48, 1).n64_u32[0];
    v51.n64_u32[0] = vdup_lane_s32(v49, 1).n64_u32[0];
    v50.n64_u32[1] = LODWORD(vct_B.x);
    v51.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v51.n64_f32[1] * v48.n64_f32[0])
                        - (f32)(v50.n64_f32[1] * v49.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v49, v50), vmul_f32(v51, v48));
    sub_1949110(0);
    v53 = (u8)byte_5756177;
    vct_B = (struct sdfVector4_t)xmmword_3CFCEA0;
    if (v53)
      goto LABEL_69;
    goto LABEL_184;
  }
  if (CHECK_PRESS(4104, 1))
  {
    v163 = CameraTargetPos;
    vct_A = v163;
    v110 = CameraEyePos;
    vct_B = v110;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_C = vct_A;
    vct_B = vct_A;
    v112 = CameraUpVector;
    vct_A = v112;
    v114.n64_u64[0] = *(u64 *)&vct_B.y;
    v115.n64_u64[0] = *(u64 *)&vct_A.y;
    v116.n64_u32[0] = vdup_lane_s32(v114, 1).n64_u32[0];
    v117.n64_u32[0] = vdup_lane_s32(v115, 1).n64_u32[0];
    v116.n64_u32[1] = LODWORD(vct_B.x);
    v117.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v117.n64_f32[1] * v114.n64_f32[0])
                         - (f32)(v116.n64_f32[1] * v115.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v115, v116), vmul_f32(v117, v114));
    sub_1949110(0);
    vct_B = vct_C;
    v120.n64_u64[0] = *(u64 *)&vct_B.y;
    v121.n64_u64[0] = *(u64 *)&vct_A.y;
    v122.n64_u32[0] = vdup_lane_s32(v120, 1).n64_u32[0];
    v123.n64_u32[0] = vdup_lane_s32(v121, 1).n64_u32[0];
    v122.n64_u32[1] = LODWORD(vct_B.x);
    v123.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v123.n64_f32[1] * v120.n64_f32[0])
                         - (f32)(v122.n64_f32[1] * v121.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v121, v122), vmul_f32(v123, v120));
    sub_1949110(0);
    v124 = (u8)byte_5756177;
    vct_B = (struct sdfVector4_t)xmmword_3CFE7F0;
    if (v124)
    {
LABEL_69:
      goto LABEL_70;
    }
LABEL_184:
LABEL_70:
    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    vct_C = vct_A;
    v54 = CameraEyePos;
    vct_B = v54;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v56 = &CameraEyePos;
    *v56 = vct_A;
    vct_A = vct_C;
    v57 = CameraTargetPos;
    vct_B = v57;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v58 = &CameraTargetPos;
    *v58 = vct_A;
    goto LABEL_188;
  }
LABEL_188:
  if ((u8)(AnalogRX + 63) <= 0x7Eu)
  {
    v164 = CameraTargetPos;
    vct_A = v164;
    v127 = CameraEyePos;
    vct_B = v127;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_C = vct_A;
    vct_B = vct_A;
    v129 = CameraUpVector;
    vct_A = v129;
    v131.n64_u64[0] = *(u64 *)&vct_B.y;
    v132.n64_u64[0] = *(u64 *)&vct_A.y;
    v133.n64_u32[0] = vdup_lane_s32(v131, 1).n64_u32[0];
    v134.n64_u32[0] = vdup_lane_s32(v132, 1).n64_u32[0];
    v133.n64_u32[1] = LODWORD(vct_B.x);
    v134.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v134.n64_f32[1] * v131.n64_f32[0])
                         - (f32)(v133.n64_f32[1] * v132.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v132, v133), vmul_f32(v134, v131));
    sub_1949110(0);
    vct_B = vct_C;
    v137.n64_u64[0] = *(u64 *)&vct_B.y;
    v138.n64_u64[0] = *(u64 *)&vct_A.y;
    v139.n64_u32[0] = vdup_lane_s32(v137, 1).n64_u32[0];
    v140.n64_u32[0] = vdup_lane_s32(v138, 1).n64_u32[0];
    v139.n64_u32[1] = LODWORD(vct_B.x);
    v140.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v140.n64_f32[1] * v137.n64_f32[0])
                         - (f32)(v139.n64_f32[1] * v138.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v138, v139), vmul_f32(v140, v137));
    sub_1949110(0);
    v142 = &vf00.x;
    v143 = v142[4];
    v144 = v142[5];
    v146 = v142[6];
    v145 = v142[7];
    v147 = (128 - AnalogRX);
    v149 = v147 * 0.0078125;
    v151 = v149 * 0.03;
    sub_197D860(&mtx_A, 0, v151, v143, v144, v146, v145);
    v152 = CameraTargetPos;
    vct_A = v152;
    v154 = CameraEyePos;
    vct_B = v154;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    get_transpose(&v209, &mtx_A, 0);
    v215 = vct_A;
    v208 = v209;
    v212 = op_Multiply_60923920(&v208, v215, 0);
    vct_A = v212;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v157 = &CameraTargetPos;
    *v157 = vct_A;
    return 1;
  }
  return 1;
}

// 0x1fc5db0
static void BgLoad_Block(void) {
  mdlRegistDummy(2u, gBg_Minor);
}

// 0x1fbff70
static void BgLoad_UnBlock(void) {
  mdlUnRegist(2u, gBg_Minor);
}

// 0x1fc11a0
static bool LoadMap_FromMemory(s32 fldno, s32 floorno) {
  u32 v20;
  dds3Basic_t *v22;
  dds3Basic_t *ControlScene;
  u32 *v28;
  SBATTLE_WORK *wk_local;
  Il2CppObject *ModelHandle;
  Il2CppObject *v34;
  dds3ModelHandle_t *p_hMapMdl;
  dds3Basic_t *v38;
  evtUnitHandle_t *UnitHandle2;
  SBATTLE_WORK *v40;
  dds3ModelHandle_t *hMapMdl;
  char *v46;
  char *v48;
  SB_ENCOUNTPAC *v50;
  SB_ENCOUNTPAC *v52;
  SB_ENCOUNTPAC *v54;
  char *v58;
  char *v60;
  s64 i;
  s32 v62;
  s64 v63;
  s32 v65;
  char *v69;
  char *asset_name;
  s64 v72;
  char *v74;
  char *v76;
  SBTLSCENE_WORK *scene;
  char *v82;
  char *v83;
  SBTLSCENE_WORK *v85;
  char *v88;
  char *v89;
  SBTLSCENE_WORK *v91;
  char *v94;
  char *name;
  bool IsNullOrEmpty;
  u32 v104;
  SBATTLE_WORK *v105;
  s32 encountno;
  void *Instance;
  s64 v113;
  dds3Basic_t *apMarkerUnit;
  u32 v116;
  dds3Basic_t *v118;
  Il2CppClass *v119;
  s64 v120;
  dds3Basic_t *apMarkerUnitR;
  u32 v123;
  dds3Basic_t *v125;
  Il2CppClass *v126;
  SB_ENCOUNTPAC *v127;
  s64 start_map;
  SB_ENCOUNTPAC *v130;
  SBATTLE_WORK *v131;
  s64 start_floor;
  SB_ENCOUNTPAC *v133;
  SBATTLE_WORK *v134;
  SB_ENCOUNTPAC *v135;
  SBATTLE_WORK *v137;
  SBTLSCENE_WORK *v138;
  il2cpp_array_size_t max_length;
  s64 v140;
  s64 v141;
  SBATTLE_WORK *v142;
  s64 v143;
  s64 v144;
  s64 v146;
  SBATTLE_WORK *v148;
  SBTLSCENE_WORK *v149;
  s32 v152;
  s32 v153;
  s32 v154;
  SBATTLE_WORK *v155;
  SBTLSCENE_WORK *v156;
  SB_ENCOUNTPAC *EncountPac;
  char *scene_name;
  SBTLSCENE_WORK *v166;
  SBTLSCENE_WORK *v167;
  SBATTLE_WORK *v171;
  SBTLSCENE_WORK *v172;
  s32 v179;
  SB_ENCOUNTPAC *v180;
  s32 start_form;
  dds3Basic_t *ActiveCamera;
  SBATTLE_WORK *v184;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v187;
  SBTLUNIT_WORK *v188;
  SB_ENCOUNTPAC *v189;
  s16 start_playerpos;
  f32 v192;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rot_p;
  f32 x;
  f32 v200;
  f32 v202;
  f32 v203;
  f32 v204;
  f32 v207;
  bool v210;
  u32 v213;
  sdfVector4_t *p_nakama_rot;
  f32 v221;
  f32 v222;
  f32 z;
  SBTLUNIT_WORK *PChara;
  dds3Basic_t *pBasic;
  s32 m_Handle;
  dds3Basic_t *pObjectBasic;
  s64 r;
  s64 y;
  dds3Basic_t *unit[2];
  sdfVector4_t v241;
  sdfVector4_t v242;
  sdfVector4_t v243;
  sdfVector4_t v244;
  sdfVector4_t v245;
  sdfVector4_t v246;
  sdfVector4_t v247;

  m_Handle = 0;
  pBasic = 0;
  pObjectBasic = 0;
  r = 0;
  y = 0;
  __asm { FMOV            V0.2S, #1.0 }
  *(u64 *)&gSbtlScene_Zoom2FrameGoal = 0;
  *(u64 *)&gSbtlScene_Zoom2On = 0;
  *(u64 *)&gSbtlScene_Zoom2Y = 0;
  *(u64 *)&gSbtlScene_Zoom2ScaleGoal = _D0;
  gSbtlScene_Zoom2ScaleNow = 1.0;
  *(u64 *)&gSbtlScene_ForceScrollOn = 0;
  *(u64 *)&gSbtlScene_UnitScrollOn = 0;
  *(u64 *)&gSbtlScene_ForceScrollY = 0;
  dds3BistaClear();
  dds3PostEspClear();
  BasicSceneFree();
  fldGb->battleMap = 1;
  evtLoadMap(fldno, floorno);
  if (aMapMdl[wk->mapmdl])
  {
    v20 = dds3SerializeID();
    v241.w = 1.0;
    v241.x = 0.0;
    v241.y = 0.0;
    v241.z = 0.0;
    v245.x = 0.0;
    v245.y = 0.0;
    v245.z = 0.0;
    v245.w = 0.0;
    v22 = dds3UnitObjectBasicAdd(v20, v241, v245);
    pObjectBasic = v22;
    ControlScene = dds3GetControlScene();
    dds3SceneBasicSetActiveUnit(ControlScene, v22);
    v28 = aMapMdl;
    gBg_Minor = v28[wk->mapmdl];
    mdlRegistDummy(2u, gBg_Minor);
    dds3ObjectBaseMakeUnit(v22, 2u, gBg_Minor);
    wk_local = wk;
    ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
    v34 = ModelHandle;
    if (ModelHandle)
    {
      p_hMapMdl = &wk_local->hMapMdl;
    }
    else
    {
      p_hMapMdl = &wk_local->hMapMdl;
      wk_local->hMapMdl = 0;
    }
    dds3ObjectBaseOffFlag(pObjectBasic, 1u);
    dds3UnitObjectBasicSetOt(pObjectBasic, 4);
    v38 = pObjectBasic;
    unit[0] = pObjectBasic;
    if (v38)
    {
      UnitHandle2 = evtGetUnitHandle2(unit);
      evtUnitLightOn(UnitHandle2);
      evtSetUnitLightAndAmbient(UnitHandle2, 0, 0, 0x80808080);
    }
    v40 = wk;
    v40->mapclr = -2139062144;
    hMapMdl = v40->hMapMdl;
    v242.x = 1.0;
    v242.y = 1.0;
    v242.z = 1.0;
    v242.w = 1.0;
    SetColor(hMapMdl, v242);
    goto LABEL_49;
  }
LABEL_49:
  if (main_data->flg)
    goto LABEL_51;
  if (wk->mapmdl)
  {
    v69 = mapModelInfo[wk->mapmdl][0];
    gMapSceneName = v69;
    asset_name = mapModelInfo[wk->mapmdl][1];
    goto LABEL_243;
  }
  EncountPac = sBtlGetEncountPac(-1);
  scene_name = EncountPac[wk->encountno]->scene_name;
  gMapSceneName = scene_name;
  asset_name = sBtlGetEncountPac(-1)[wk->encountno]->asset_name;
LABEL_243:
  gMapAssetName = asset_name;
  wk->scrEncountNo = wk->encountno;
  goto LABEL_134;
LABEL_51:
  v46 = "bt_map03";
  gMapSceneName = "bt_map03";
  v48 = "bt_map03";
  gMapAssetName = "bt_map03";
  v50 = sBtlGetEncountPac(-1);
  if (wk->scene->major == v50[wk->encountno]->start_map)
  {
    v52 = sBtlGetEncountPac(-1);
    if (wk->scene->minor == v52[wk->encountno]->start_floor)
    {
      v54 = sBtlGetEncountPac(-1);
      v58 = v54[wk->encountno]->scene_name;
      gMapSceneName = v58;
      v60 = sBtlGetEncountPac(-1)[wk->encountno]->asset_name;
LABEL_132:
      gMapAssetName = v60;
      goto LABEL_133;
    }
  }
  for (i = 4; ; ++i)
  {
    if (i - 4 >= SLODWORD(sBtlGetEncountPac(-1)->max_length))
      break;
    v62 = *(char *)(*((u64 *)&sBtlGetEncountPac(-1)->obj.klass + i) + 16);
    if (wk->scene->major != v62)
      continue;
    v63 = *((u64 *)&sBtlGetEncountPac(-1)->obj.klass + i);
    v65 = *(char *)(v63 + 17);
    if (wk->scene->minor == v65)
    {
      v72 = *((u64 *)&sBtlGetEncountPac(-1)->obj.klass + i);
      v74 = *(char **)(v72 + 24);
      gMapSceneName = v74;
      v76 = *(char **)(*((u64 *)&sBtlGetEncountPac(-1)->obj.klass + i) + 32);
      gMapAssetName = v76;
      break;
    }
  }
  scene = wk->scene;
  if (scene->major == 37)
  {
    scene = wk->scene;
    if (scene->minor == 13)
    {
      v82 = "bg09_10_battle";
      gMapSceneName = "bg09_10_battle";
      v83 = "bg09_10_battle";
      gMapAssetName = "bg09_10_battle";
    }
  }
  v85 = wk->scene;
  if (v85->major == 37)
  {
    v85 = wk->scene;
    if (v85->minor == 15)
    {
      v88 = "bg37_15";
      gMapSceneName = "bg37_15";
      v89 = "bg37_15";
      gMapAssetName = "bg37_15";
    }
  }
  v91 = wk->scene;
  if (v91->major != 37)
    goto LABEL_133;
  v91 = wk->scene;
  if (v91->minor == 16)
  {
    v94 = "bg37_17";
    gMapSceneName = "bg37_17";
    v60 = "bg37_17";
    goto LABEL_132;
  }
LABEL_133:
LABEL_134:
  m_Handle = GetSceneByName(gMapSceneName, 0).m_Handle;
  name = get_name((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0);
  IsNullOrEmpty = IsNullOrEmpty(name, 0);
  if (!IsNullOrEmpty)
  {
    wk->fieldmap_use = 1;
    sBtlFldMapDisp(1, 0);
    Instance = get_Instance(0);
    goto LABEL_152;
  }
  if (!v104)
  {
    v105 = wk;
    encountno = v105->encountno;
    if (encountno != 43)
      goto LABEL_185;
LABEL_138:
    sBtlFldMapDisp(0, "temple");
    goto LABEL_142;
  }
  v105 = wk;
  encountno = v105->encountno;
  if (encountno == 43)
    goto LABEL_138;
LABEL_185:
  v105 = wk;
  if (v105->encountno != 46)
    goto LABEL_344;
  sBtlFldMapDisp(0, "bg10");
LABEL_142:
LABEL_344:
  v105 = wk;
  v105->fieldmap_use = 0;
  Instance = get_Instance(0);
LABEL_152:
  MapLoad(Instance, gMapSceneName, gMapAssetName, 0);
  v113 = 32;
  while (2)
  {
    apMarkerUnit = wk->apMarkerUnit;
    v116 = dds3SerializeID();
    v243.x = 0.0;
    v243.y = 0.0;
    v243.z = 0.0;
    v246.x = 0.0;
    v246.y = 0.0;
    v246.z = 0.0;
    v246.w = 0.0;
    v243.w = 1.0;
    v118 = dds3UnitObjectBasicAdd(v116, v243, v246);
    v119 = v118;
    *(Il2CppClass **)((char *)&apMarkerUnit->obj.klass + v113) = v119;
    dds3ObjectBaseOnFlag(((char *)wk->apMarkerUnit + v113), 1u);
    dds3ObjectBaseOffFlag(((char *)wk->apMarkerUnit + v113), 0x400u);
    dds3UnitObjectBasicSetOt(*(dds3Basic_t *)((char *)&wk->apMarkerUnit->obj.klass + v113), 1);
    v113 += 8;
    if (v113 != 96)
      continue;
    break;
  }
  v120 = 32;
  while (2)
  {
    apMarkerUnitR = wk->apMarkerUnitR;
    v123 = dds3SerializeID();
    v244.x = 0.0;
    v244.y = 0.0;
    v244.z = 0.0;
    v247.x = 0.0;
    v247.y = 0.0;
    v247.z = 0.0;
    v247.w = 0.0;
    v244.w = 1.0;
    v125 = dds3UnitObjectBasicAdd(v123, v244, v247);
    v126 = v125;
    *(Il2CppClass **)((char *)&apMarkerUnitR->obj.klass + v120) = v126;
    dds3ObjectBaseOnFlag(((char *)wk->apMarkerUnitR + v120), 1u);
    dds3ObjectBaseOffFlag(((char *)wk->apMarkerUnitR + v120), 0x400u);
    dds3UnitObjectBasicSetOt(*(dds3Basic_t *)((char *)&wk->apMarkerUnitR->obj.klass + v120), 1);
    v120 += 8;
    if (v120 != 96)
      continue;
    break;
  }
  evtMoonDisableDraw(1);
  v127 = sBtlGetEncountPac(-1);
  start_map = v127[wk->encountno]->start_map;
  v130 = sBtlGetEncountPac(-1);
  v131 = wk;
  start_floor = v130[v131->encountno]->start_floor;
  v133 = sBtlGetEncountPac(-1);
  v134 = wk;
  v131->camera_mode = v133[v134->encountno]->camera_mode;
  v135 = sBtlGetEncountPac(-1);
  v137 = wk;
  v134->collider_type = v135[v137->encountno]->collider_type;
  v138 = v137->scene;
  if (start_map == v138->major)
  {
    if (start_floor == v138->minor)
      goto LABEL_213;
  }
  max_length = sBtlGetEncountPac(-1)->max_length;
  if ((s32)max_length >= 1)
  {
    v140 = 4;
    v141 = -(s64)(u32)max_length;
    do
    {
      v143 = *(char *)(*((u64 *)&sBtlGetEncountPac(-1)->obj.klass + v140) + 16);
      if (v143 == wk->scene->major)
      {
        v144 = *((u64 *)&sBtlGetEncountPac(-1)->obj.klass + v140);
        v146 = *(char *)(v144 + 17);
        v142 = wk;
        if (v146 == v142->scene->minor)
        {
          v142 = wk;
          v142->collider_type = *(u16 *)(*((u64 *)&sBtlGetEncountPac(-1)->obj.klass + v140) + 72);
          break;
        }
      }
      ++v140;
    }
    while (v141 + v140 != 4);
  }
LABEL_213:
  v148 = wk;
  v149 = v148->scene;
  v148->collider_center_x = 0.0;
  *(u64 *)&v148->collider_center_y = 0;
  if (v149->major == 31)
  {
    if (v149->minor == 6)
      goto LABEL_218;
    goto LABEL_9006;
    if (v148->scene->minor == 6)
    {
LABEL_218:
      v148->collider_type = 100;
      v152 = 0;
      v153 = 1158250496;
      v154 = 0;
      goto LABEL_268;
    }
LABEL_9006:
  }
  v155 = wk;
  v156 = v155->scene;
  if (v156->major != 37)
    goto LABEL_249;
  if (v156->minor != 8)
    goto LABEL_249;
  v155->collider_type = 100;
  v152 = 1120403456;
  v154 = -1035468800;
  v153 = 1154777088;
  goto LABEL_268;
LABEL_249:
  v166 = wk->scene;
  if (v166->major == 37)
  {
    if (v166->minor == 13)
      goto LABEL_263;
  }
  v167 = wk->scene;
  if (v167->major != 39)
    goto LABEL_352;
  if (v167->minor != 13)
    goto LABEL_352;
LABEL_263:
LABEL_264:
  wk->collider_type = 100;
  v152 = 0;
  v153 = 1145569280;
  v154 = 0;
LABEL_268:
  LODWORD(distance_r) = v153;
  v171 = wk;
  LODWORD(v171->collider_center_x) = v152;
  v171->collider_center_y = 0.0;
  LODWORD(v171->collider_center_z) = v154;
  goto LABEL_269;
LABEL_352:
  if (op_Equality(gMapAssetName, "bg09_10_battle", 0))
  {
    goto LABEL_264;
  }
  v210 = op_Equality(gMapAssetName, "new_bt_map27", 0);
  if (v210)
  {
    wk->collider_type = 100;
    v152 = 0;
    v153 = 1152319488;
    v154 = 0;
    goto LABEL_268;
  }
LABEL_269:
  v172 = wk->scene;
  if (v172->major != 39)
  {
LABEL_275:
    goto LABEL_276;
  }
  if (v172->minor != 1)
    goto LABEL_275;
  mapWHitAdd(0xFFFF, 0, -600.0, 900.0, -900.0, 600.0, 0.5, -0.5, 0);
  mapWHitAdd(0xFFFF, 0, 600.0, 900.0, 900.0, 600.0, -0.5, -0.5, 0);
  mapWHitAdd(0xFFFF, 0, -900.0, -600.0, -600.0, -900.0, 0.5, 0.5, 0);
  mapWHitAdd(0xFFFF, 0, 900.0, -600.0, 600.0, -900.0, -0.5, 0.5, 0);
LABEL_276:
  SetTestCamera();
  sBtlCreateCamera();
  sBtlResetRndEncCount();
  v179 = wk->encountno;
  mapMapSetEnc(v179);
  v180 = sBtlGetEncountPac(-1)[wk->encountno];
  start_form = v180->start_form;
  if (v180->start_form)
  {
    mapMapSetForm(start_form);
  }
  pBasic = dds3GetActiveScene();
  ActiveCamera = dds3SceneBasicGetActiveCamera(pBasic);
  mapCutSetCam(ActiveCamera, 0);
  v184 = wk;
  UnitMng = v184->UnitMng;
  playerID = v184->playerID;
  v187 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v187)
  {
    v188 = v187;
    v189 = sBtlGetEncountPac(-1);
    start_playerpos = v189[wk->encountno]->start_playerpos;
    mapEncPointGet(start_playerpos, (f32 *)&y + 1, &y, (f32 *)&r + 1, &r);
    v192 = *(f32 *)&y;
    v188->pos.x = *((f32 *)&y + 1);
    v188->pos.y = v192;
    v188->pos.z = *((f32 *)&r + 1);
    FromEuler(0.0, *(f32 *)&r * 0.017453292, 0.0);
    p_rot = &v188->rot;
    *p_rot = vct_A;
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    p_rot_p = &v188->rot_p;
    *p_rot_p = vct_A;
    LODWORD(v188->mv_rotbk) = r;
    if (!sBtlCheckSummon(0))
    {
      goto LABEL_387;
    }
    wk->scene->status |= 0x20u;
    x = *((f32 *)&y + 1);
    v200 = *(f32 *)&y;
    nakama_pos.x = *((f32 *)&y + 1);
    nakama_pos.y = v200;
    v202 = *((f32 *)&r + 1);
    v203 = *(f32 *)&r;
    nakama_pos.z = *((f32 *)&r + 1);
    if (v203 > -45.0 && v203 < 45.0)
    {
      x = nakama_pos.x;
      v204 = -200.0;
LABEL_380:
      nakama_pos.x = x + v204;
LABEL_381:
      FromEuler(0.0, *(f32 *)&r * 0.017453292, 0.0);
      p_nakama_rot = &nakama_rot;
      *p_nakama_rot = vct_A;
      LODWORD(nakama_mv_rotbk) = r;
LABEL_387:
      gSbtlScene_ForceScrollOn = 0;
      gSbtlScene_ForceScrollX = v188->pos.x;
      gSbtlScene_ForceScrollY = v188->pos.y;
      gSbtlScene_ForceScrollZ = v188->pos.z;
      v221 = v188->pos.x;
      v222 = v188->pos.y;
      z = v188->pos.z;
      mapCutSet_From_Pos(v221, v222 + -100.0, z, 0);
      GlobalParamFlag = 1;
      *(_OWORD *)&GlobalParamScaleX = xmmword_3CFEE20;
      Zoom = 1.0;
      ScreenParam->height = 512.0;
      goto LABEL_394;
    }
    if (v203 >= -45.0 || v203 <= -135.0)
    {
      if (v203 <= 45.0 || v203 >= 135.0)
      {
        if (!v213)
        {
          x = nakama_pos.x;
        }
        v204 = 200.0;
        goto LABEL_380;
      }
      if (!v213)
      {
        v202 = nakama_pos.z;
      }
      v207 = 200.0;
    }
    else
    {
      v202 = nakama_pos.z;
      v207 = -200.0;
    }
    nakama_pos.z = v202 + v207;
    goto LABEL_381;
  }
LABEL_394:
  mapCutSetLight();
  sBtlGetEncountPac(-1);
  sBtlBackUpCamera();
  PChara = sBtlGetPChara();
  *(sdfVector4_t *)unit = PChara->pos;
  raidouPos_Bk = *(sdfVector4_t *)unit;
  raidouRot_Bk = PChara->rot;
  return 1;
}

// 0x1fc5f20
bool sBtlReLoadMap(void) {
  SB_ENCOUNTPAC *EncountPac;
  s64 encountno;
  SBTLSCENE_WORK *scene;
  SB_ENCOUNTPAC *v6;
  s32 start_map;
  u32 start_floor;
  SBTLSCENE_WORK *v10;
  SB_ENCOUNTPAC *v12;
  s32 start_form;
  dds3Basic_t *ActiveCamera;
  SBATTLE_WORK *v17;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v20;
  SBTLUNIT_WORK *v21;
  SB_ENCOUNTPAC *v22;
  s16 start_playerpos;
  f32 v25;
  sdfVector4_t *p_rot;
  s32 v28;
  sdfVector4_t *p_rot_p;
  SBTLUNIT_WORK *Nakama;
  s64 v31;
  SBTLUNIT_WORK *v32;
  s64 v33;
  f32 v34;
  s32 v35;
  f32 v36;
  sdfVector4_t *v38;
  s32 v39;
  sdfVector4_t *v40;
  f32 x;
  f32 v45;
  f32 z;
  dds3Basic_t *v48;
  s32 v50;
  dds3Basic_t *pBasic;
  s64 r;
  s64 y;

  pBasic = 0;
  r = 0;
  y = 0;
  EncountPac = sBtlGetEncountPac(-1);
  encountno = wk->encountno;
  scene = wk->scene;
  v6 = EncountPac[encountno];
  start_map = v6->start_map;
  scene->major = start_map;
  start_floor = v6->start_floor;
  scene->minor = start_floor;
  v10 = wk->scene;
  start_map = v10->major;
  start_floor = v10->minor;
  fldGb->floorID = start_floor;
  fldGb->fieldID = start_map;
  fldGb->areaID = 0;
  fldGb->battleMap = 1;
  fldMapFileLoad(start_map);
  mapMapSetEnc(wk->encountno);
  v12 = sBtlGetEncountPac(-1)[wk->encountno];
  start_form = v12->start_form;
  if (v12->start_form)
  {
    mapMapSetForm(start_form);
  }
  pBasic = dds3GetActiveScene();
  ActiveCamera = dds3SceneBasicGetActiveCamera(pBasic);
  mapCutSetCam(ActiveCamera, 0);
  v17 = wk;
  UnitMng = v17->UnitMng;
  playerID = v17->playerID;
  v20 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v20)
  {
    v21 = v20;
    v22 = sBtlGetEncountPac(-1);
    start_playerpos = v22[wk->encountno]->start_playerpos;
    mapEncPointGet(start_playerpos, (f32 *)&y + 1, &y, (f32 *)&r + 1, &r);
    v25 = *(f32 *)&y;
    v21->pos.x = *((f32 *)&y + 1);
    v21->pos.y = v25;
    v21->pos.z = *((f32 *)&r + 1);
    FromEuler(0.0, *(f32 *)&r * 0.017453292, 0.0);
    p_rot = &v21->rot;
    v28 = (u8)byte_5755EF5;
    *p_rot = vct_A;
    if (v28)
      goto LABEL_32;
    goto LABEL_44;
    if (v35)
    {
LABEL_32:
LABEL_33:
      vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
      p_rot_p = &v21->rot_p;
      *p_rot_p = vct_A;
      LODWORD(v21->mv_rotbk) = r;
      Nakama = sBtlGetNakama(0);
      if (!Nakama)
      {
LABEL_65:
        gSbtlScene_ForceScrollOn = 0;
        gSbtlScene_ForceScrollX = v21->pos.x;
        gSbtlScene_ForceScrollY = v21->pos.y;
        gSbtlScene_ForceScrollZ = v21->pos.z;
        x = v21->pos.x;
        v45 = v21->pos.y;
        z = v21->pos.z;
        mapCutSet_From_Pos(x, v45, z, 0);
        goto LABEL_70;
      }
      v31 = y;
      v32 = Nakama;
      Nakama->pos.x = *((f32 *)&y + 1);
      LODWORD(Nakama->pos.y) = v31;
      v33 = r;
      Nakama->pos.z = *((f32 *)&r + 1);
      if (*(f32 *)&v33 > -45.0 && *(f32 *)&v33 < 45.0)
      {
        v34 = -200.0;
LABEL_56:
        Nakama->pos.x = *((f32 *)&v31 + 1) + v34;
LABEL_57:
        FromEuler(0.0, *(f32 *)&v33 * 0.017453292, 0.0);
        v38 = &v32->rot;
        v39 = (u8)byte_5755EF5;
        *v38 = vct_A;
        if (v39)
          goto LABEL_61;
        goto LABEL_80;
        if (v50)
        {
LABEL_61:
          goto LABEL_62;
        }
LABEL_80:
LABEL_62:
        vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
        v40 = &v32->rot_p;
        *v40 = vct_A;
        LODWORD(v32->mv_rotbk) = r;
        goto LABEL_65;
      }
      if (*(f32 *)&v33 >= -45.0 || *(f32 *)&v33 <= -135.0)
      {
        if (*(f32 *)&v33 <= 45.0 || *(f32 *)&v33 >= 135.0)
        {
          v34 = 200.0;
          goto LABEL_56;
        }
        v36 = 200.0;
      }
      else
      {
        v36 = -200.0;
      }
      Nakama->pos.z = *((f32 *)&v33 + 1) + v36;
      goto LABEL_57;
    }
LABEL_44:
    goto LABEL_33;
  }
LABEL_70:
  pBasic = dds3GetActiveScene();
  v48 = dds3SceneBasicGetActiveCamera(pBasic);
  mapCutSetCam(v48, 1);
  mapCutSetLight();
  return 1;
}

// 0x1fc66c0
void sBtlSetCutScroll(const sdfVector4_t *pos) {
  f32 z;
  f32 y;
  f32 x;
  dds3Basic_t *ActiveCamera;
  dds3Basic_t *pBasic;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  gSbtlScene_ForceScrollOn = 1;
  gSbtlScene_ForceScrollX = x;
  gSbtlScene_ForceScrollY = y;
  gSbtlScene_ForceScrollZ = z;
  mapCutSet_From_Pos(x, y, z, 0);
  pBasic = dds3GetActiveScene();
  ActiveCamera = dds3SceneBasicGetActiveCamera(pBasic);
  mapCutSetCam(ActiveCamera, 1);
  mapCutSetLight();
}

// 0x1fc6810
void sBtlDefaultCutScroll(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  f32 x;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    return;
  v6 = v5;
  x = v6->pos.x;
  gSbtlScene_ForceScrollOn = 0;
  gSbtlScene_ForceScrollX = x;
  gSbtlScene_ForceScrollY = v6->pos.y;
  gSbtlScene_ForceScrollZ = v6->pos.z;
}

// 0x1fc6930
bool sBtlSetZoom(f32 x, f32 y, f32 z, f32 per, s32 time, u32 flg) {
  SBTLSCENE_WORK *scene;
  s32 status;

  scene = wk->scene;
  status = scene->status;
  scene->zoom_z = z;
  scene->zoom_bairitu = per;
  scene->zoom_time = time;
  scene->zoom_x = x;
  scene->zoom_y = y;
  scene->status = status | flg;
  return 1;
}

// 0x1fc69e0
bool sBtlSetZoomLock(SBTLUNIT_WORK *wk, f32 per) {
  SBTLSCENE_WORK *scene;
  SBTLSCENE_WORK *v8;
  s32 status;

  scene = wk->scene;
  scene->zoomlockID = wk->ListID;
  if (per != 0.0)
  {
    scene->zoom_bairitu = per;
    goto LABEL_8;
  }
LABEL_8:
  v8 = wk->scene;
  status = v8->status;
  v8->zoomlocktime = 0;
  v8->zoomlockflg = 0;
  v8->status = status | 4;
  return 1;
}

// 0x1fc6ae0
bool sBtlResetZoomLock(void) {
  SBTLSCENE_WORK *scene;
  s32 status;

  scene = wk->scene;
  status = scene->status;
  scene->zoomlockflg = 0;
  scene->status = status & 0xFFFFFFFB;
  return 1;
}

// 0x1fc6b60
bool sBtlCheckZoom(void) {
  SBTLSCENE_WORK *scene;
  s32 status;
  SBTLSCENE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v11;
  f32 zoom_bairitu;
  SBTLUNIT_LISTWORK *v13;
  s32 zoomlockID;
  SBTLUNIT_WORK *v16;
  SBTLSCENE_WORK *v18;
  SBTLSCENE_WORK *v19;

  scene = wk->scene;
  status = scene->status;
  if ((status & 3) != 0)
  {
    if ((status & 1) == 0)
      goto LABEL_8;
    goto LABEL_9000;
    if ((wk->scene->status & 1) == 0)
    {
LABEL_8:
LABEL_9:
      v6 = wk->scene;
      v6->status &= 0xFFFFFFFC;
      return 1;
    }
LABEL_9000:
    UnitMng = wk->UnitMng;
    playerID = wk->playerID;
    v11 = sBtlSearchUnit_ID(UnitMng, playerID);
    zoom_bairitu = wk->scene->zoom_bairitu;
    sBtlSetZoomLock(v11, zoom_bairitu);
    goto LABEL_9;
  }
  if ((status & 4) == 0)
    return 1;
  scene = wk->scene;
  v13 = wk->UnitMng;
  ++scene->zoomlocktime;
  zoomlockID = scene->zoomlockID;
  v16 = sBtlSearchUnit_ID(v13, zoomlockID);
  v18 = wk->scene;
  if (v18->zoomlocktime <= 59)
  {
    v18 = wk->scene;
    if (v18->zoomlockflg)
      return 1;
  }
  v19 = wk->scene;
  v19->zoomlockflg = 1;
  v19->zoomlocktime = 0;
  sBtlGetUnitHelperPos(v16, 0);
  return 1;
}

// 0x1fc7080
s32 sBtlGetScrollID(void) {
  SBTLUNIT_LISTWORK *tgtList;
  s32 tgt_csr;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v8;
  SBATTLE_WORK *v12;

  if ((wk->status & 0x80000) == 0)
    goto LABEL_25;
  tgtList = wk->tgtList;
  if (!tgtList)
    goto LABEL_25;
  if (tgtList->count < 1)
    goto LABEL_25;
  tgt_csr = wk->tgt_csr;
  goto LABEL_17;
LABEL_21:
  v8 = v6;
  if (!sBtlCheckDamageTarget(v6))
    goto LABEL_25;
  return v8->ListID;
LABEL_17:
  v6 = sBtlSearchUnit_ID(tgtList, tgt_csr);
  if (v6)
    goto LABEL_21;
LABEL_25:
  v12 = wk;
  if ((v12->status & 0x4000000) == 0)
  {
    return v12->playerID;
  }
  return v12->unitpadID;
}

// 0x1fc7300
void sBtlSetZoom2(const sdfVector4_t *pos, f32 size, s32 frame) {
  f32 z;
  f32 y;
  f32 x;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  gSbtlScene_Zoom2Z = z;
  gSbtlScene_Zoom2ScaleGoal = size;
  gSbtlScene_Zoom2FrameGoal = frame;
  gSbtlScene_Zoom2FrameNow = 0;
  gSbtlScene_Zoom2X = x;
  gSbtlScene_Zoom2Y = y;
  gSbtlScene_Zoom2On = 1;
  gSbtlScene_Zoom2ScaleStart = gSbtlScene_Zoom2ScaleNow;
}

// 0x1fc73b0
void sBtlDefaultZoom2(s32 frame) {
  gSbtlScene_Zoom2FrameGoal = frame;
  *(u64 *)&gSbtlScene_Zoom2FrameNow = 0x3F80000000000000LL;
  gSbtlScene_Zoom2ScaleStart = gSbtlScene_Zoom2ScaleNow;
}

// 0x1fc7430
bool sBtlCheckZoom2(f32 *_ZoomScale) {
  f32 v7;
  s32 v8;
  f32 v12;
  f32 v13;
  s32 v14;
  f32 v16;
  f32 v17;
  bool v18;
  f32 v19;

  *ZoomScale = 1.0;
  if (!gSbtlScene_Zoom2On)
    return gSbtlScene_Zoom2On != 0;
  v7 = 1.0;
  v8 = gSbtlScene_Zoom2FrameNow + 1;
  gSbtlScene_Zoom2FrameNow = v8;
  if (v8 <= gSbtlScene_Zoom2FrameGoal)
  {
LABEL_13:
    goto LABEL_15;
  }
  gSbtlScene_Zoom2FrameNow = gSbtlScene_Zoom2FrameGoal;
  if (gSbtlScene_Zoom2ScaleGoal > v7)
    goto LABEL_13;
  gSbtlScene_Zoom2On = 0;
LABEL_15:
  v12 = 0.0;
  v13 = 0.0;
  v14 = gSbtlScene_Zoom2FrameGoal;
  if (v14)
  {
    v16 = gSbtlScene_Zoom2FrameNow / (f32)v14;
    v17 = v16 <= v7 ? gSbtlScene_Zoom2FrameNow / (f32)v14 : v7;
    v18 = v16 < 0.0;
    v13 = 0.0;
    if (!v18)
      v13 = v17;
  }
  if (v13 >= 0.0)
    v12 = v13;
  v19 = gSbtlScene_Zoom2ScaleStart
      + (f32)(v12 * (f32)(gSbtlScene_Zoom2ScaleGoal - gSbtlScene_Zoom2ScaleStart));
  gSbtlScene_Zoom2ScaleNow = v19;
  *ZoomScale = v19;
  return gSbtlScene_Zoom2On != 0;
}

// 0x1fc7600
void sBtlSetScroll(const sdfVector4_t *pos) {
  f32 z;
  f32 y;
  f32 x;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  gSbtlScene_ForceScrollY = y;
  gSbtlScene_ForceScrollZ = z;
  gSbtlScene_ForceScrollOn = 1;
  gSbtlScene_ForceScrollX = x;
}

// 0x1fc7690
void sBtlDefaultScroll(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  f32 x;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    return;
  v6 = v5;
  x = v6->pos.x;
  gSbtlScene_ForceScrollOn = 0;
  gSbtlScene_ForceScrollX = x;
  gSbtlScene_ForceScrollY = v6->pos.y;
  gSbtlScene_ForceScrollZ = v6->pos.z;
}

// 0x1fc77b0
void sBtlSetUnitScroll(s32 unitID) {
  gSbtlScene_UnitScrollOn = 1;
  gSbtlScene_UnitScrollID = unitID;
}

// 0x1fc7820
void sBtlDefaultUnitScroll(void) {
  gSbtlScene_UnitScrollOn = 0;
  gSbtlScene_UnitScrollID = 0;
  return;
}

// 0x1fc1120
s32 sBtlGetBgmID(s32 encountid) {
  return sBtlGetEncountPac(-1)[encountid]->bgm;
}

// 0x1fc78a0
void sBtlMapColorSet(u32 rgba) {
  dds3ModelHandle_t *hMapMdl;
  float32x2_t v9;
  SBATTLE_WORK *v10;
  dds3ModelHandle_t *hMapMdl2;
  u32 mapclr;
  float32x2_t v15;
  u64 aColor;
  u64 aColora;
  sdfVector4_t v19;
  sdfVector4_t v20;

  wk->mapclr = rgba;
  hMapMdl = wk->hMapMdl;
  v9.n64_u64[0] = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(rgba), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL).n64_u64[0];
  aColor = v9.n64_u64[0];
  v9.n64_u64[0] = aColor;
  v19.x = (f32)(u8)rgba * 0.0078125;
  *(float32x2_t *)&v19.y = v9;
  v19.w = (f32)HIBYTE(rgba) * 0.0078125;
  SetColor(hMapMdl, v19);
  v10 = wk;
  hMapMdl2 = v10->hMapMdl2;
  if (hMapMdl2)
  {
    mapclr = v10->mapclr;
    v15.n64_u64[0] = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(mapclr), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL).n64_u64[0];
    aColora = v15.n64_u64[0];
    v15.n64_u64[0] = aColora;
    v20.x = (f32)(u8)mapclr * 0.0078125;
    *(float32x2_t *)&v20.y = v15;
    v20.w = (f32)HIBYTE(mapclr) * 0.0078125;
    SetColor(hMapMdl2, v20);
    return;
  }
}

// 0x1fbf680
void sBtlMapVisiblerSet(s32 mode) {
  dds3ModelHandle_t *v5;
  dds3ModelHandle_t *v6;
  dds3ModelHandle_t *hMapMdl;
  dds3ModelHandle_t *hMapMdl2;

  if (!mode)
  {
    hMapMdl = wk->hMapMdl;
    mdlHideBG(hMapMdl);
    hMapMdl2 = wk->hMapMdl2;
    if (!hMapMdl2)
      return;
    mdlHideBG(hMapMdl2);
    return;
  }
  v5 = wk->hMapMdl;
  mdlShowBG(v5);
  v6 = wk->hMapMdl2;
  if (v6)
  {
    mdlShowBG(v6);
    return;
  }
}

// 0x1fc5e80
static sdfVector4_t MakeMapColor(u32 rgba) {
  float32x2_t v5;
  sdfVector4_t result;

  result.x = (f32)(u8)rgba * 0.0078125;
  result.w = (f32)HIBYTE(rgba) * 0.0078125;
  v5.n64_u64[0] = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(rgba), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL).n64_u64[0];
  LODWORD(result.z) = v5.n64_u32[1];
  result.y = v5.n64_f32[0];
  return result;
}

// 0x1fc7b60
void sBtlGetZeroPos(f32 *_ZeroX, f32 *_ZeroY, f32 *_ZeroZ) {
  SBTLSCENE_WORK *scene;
  SBTLSCENE_WORK *v11;
  SBTLSCENE_WORK *v12;

  *ZeroX = 0.0;
  *ZeroY = 0.0;
  *ZeroZ = 0.0;
  scene = wk->scene;
  if (scene->major != 23)
    goto LABEL_10;
  if (scene->minor != 4)
    goto LABEL_10;
  goto LABEL_9;
  if (wk->scene->minor == 4)
  {
LABEL_9:
    *ZeroX = 7000.0;
    *ZeroY = 0.0;
    *ZeroZ = -1000.0;
  }
LABEL_10:
  v11 = wk->scene;
  if (v11->major != 4)
    goto LABEL_17;
  if (v11->minor != 6)
    goto LABEL_17;
  goto LABEL_16;
  if (wk->scene->minor == 6)
  {
LABEL_16:
    *ZeroX = 0.0;
    *ZeroY = 0.0;
    *ZeroZ = 2000.0;
  }
LABEL_17:
  v12 = wk->scene;
  if (v12->major != 10)
    return;
  if (v12->minor == 6)
    goto LABEL_29;
  goto LABEL_9000;
  if (wk->scene->minor == 6)
  {
LABEL_29:
    *ZeroX = 0.0;
    *ZeroY = 0.0;
    *ZeroZ = 3000.0;
  }
LABEL_9000:
}

// 0x1fc7db0
f32 sBtlGetYukaEffY(void) {
  SBTLSCENE_WORK *scene;
  SBTLSCENE_WORK *v4;
  SBTLSCENE_WORK *v5;
  SBTLSCENE_WORK *v6;
  SBTLSCENE_WORK *v7;
  SBTLSCENE_WORK *v8;
  SBTLSCENE_WORK *v9;
  SBTLSCENE_WORK *v10;
  SBTLSCENE_WORK *v11;
  SBTLSCENE_WORK *v12;
  SBTLSCENE_WORK *v13;
  SBTLSCENE_WORK *v14;
  SBTLSCENE_WORK *v15;
  SBTLSCENE_WORK *v16;

  goto LABEL_3;
LABEL_7:
  if (scene->minor != 3)
    goto LABEL_11;
  return -3.0;
LABEL_3:
  scene = wk->scene;
  if (scene->major == 1)
    goto LABEL_7;
LABEL_11:
  v4 = wk->scene;
  if (v4->major != 4)
    goto LABEL_19;
  if (v4->minor != 6)
    goto LABEL_19;
  return -2.0;
LABEL_19:
  v5 = wk->scene;
  if (v5->major != 10)
    goto LABEL_27;
  if (v5->minor != 6)
    goto LABEL_27;
  return -2.0;
LABEL_27:
  v6 = wk->scene;
  if (v6->major != 31)
    goto LABEL_35;
  if (v6->minor != 6)
    goto LABEL_35;
  return -3.0;
LABEL_35:
  v7 = wk->scene;
  if (v7->major != 37)
    goto LABEL_43;
  if (v7->minor != 12)
    goto LABEL_43;
  return -2.0;
LABEL_43:
  v8 = wk->scene;
  if (v8->major != 37)
    goto LABEL_51;
  if (v8->minor != 14)
    goto LABEL_51;
  return -2.0;
LABEL_51:
  v9 = wk->scene;
  if (v9->major != 37)
    goto LABEL_59;
  if (v9->minor != 15)
    goto LABEL_59;
  return -2.0;
LABEL_59:
  v10 = wk->scene;
  if (v10->major == 39)
  {
    v10 = wk->scene;
    if (v10->minor == 1)
      return -2.0;
  }
  v11 = wk->scene;
  if (v11->major == 39)
  {
    v11 = wk->scene;
    if (v11->minor == 14)
      return -2.0;
  }
  v12 = wk->scene;
  if (v12->major == 39)
  {
    v12 = wk->scene;
    if (v12->minor == 15)
      return -2.0;
  }
  v13 = wk->scene;
  if (v13->major == 37)
  {
    v13 = wk->scene;
    if (v13->minor == 17)
      return -2.0;
  }
  v14 = wk->scene;
  if (v14->major == 37)
  {
    v14 = wk->scene;
    if (v14->minor == 18)
      return -2.0;
  }
  v15 = wk->scene;
  if (v15->major == 39)
  {
    v15 = wk->scene;
    if (v15->minor == 18)
      return -2.0;
  }
  v16 = wk->scene;
  if (v16->major != 37)
    return 0.0;
  v16 = wk->scene;
  if (v16->minor == 20)
    return -2.0;
  else
    return 0.0;
}
