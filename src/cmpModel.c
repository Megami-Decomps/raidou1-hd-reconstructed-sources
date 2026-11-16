#include "types.h"
#include "BST.h"
#include "MODELTYPE.h"
#include "cmpmodel.h"
#include "cmpstatus.h"
#include "dds3effect.h"
#include "dds3kerneldraw.h"
#include "dds3kernelmain.h"
#include "evtbit.h"
#include "file.h"
#include "fld.h"
#include "mdl.h"
#include "mdl_check.h"
#include "mjn.h"
#include "sbtlsound.h"
#include "sbtlvisual.h"
#include "sdf3d.h"
#include "sdf_vu0.h"
#include "sdfmem.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "sdfsound.h"
#include "sdfsystem.h"
#include "tneffect_model.h"

#define CMP_CAMERA_DEFZ -512
#define CMP_DEFAULT_FOVY 0.43633232
#define CMP_MODEL_MAJOR_NO 7
#define CMP_MODEL_PLAYER_MAJOR_NO 0
#define CMP_MODEL_PLAYER_MINOR_NO_DEF 1
#define CMP_MODEL_PLAYER_MINOR_NO_CUR 4
#define MODEL_PLAYER_LEV_UP_MOTION 193
#define MODEL_PLAYER_TITLE_UP_MOTION 194
#define MODEL_PLAYER_HAT_MOTION 195
#define MODEL_DEVIL_LEV_UP_MOTION 7
#define MODEL_TAM_LEV_UP_MOTION 15
#define MODEL_BST_MOTION 2
#define CMPMODEL_DARK_LIGHTNO 3
#define MODEL_BUFF_MAX 32

typedef struct StatusGattaiPosY_t StatusGattaiPosY_t;
typedef struct cmpUnknownColor_t cmpUnknownColor_t;
typedef struct cmpViewerModel_t cmpViewerModel_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ModelResrc_t dds3ModelResrc_t;
typedef struct effHandle_t effHandle_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdfModelOt_t sdfModelOt_t;

struct cmpViewerModel_t {
    s16 PosXMin;
    s16 PosXMax;
    s16 PosYMin;
    s16 PosYMax;
    s16 PosZMin;
    s16 PosZMax;
    s16 RotXMin;
    s16 RotXMax;
    s16 RotYMin;
    s16 RotYMax;
};

struct cmpUnknownColor_t {
    s32 devilID;
    u32 abgr;
};

s32 playerScModelId[11];
s32 *playerFieldID;
dds3ModelHandle_t *cmpModelHandle;
void *g_pDatBst;
effHandle_t *g_hEffBst;
effHandle_t *g_hEffBst2;
void *cmpModelBuffer;
bool mdlEffSclSet;
s32 dummyModelId;
s8 gLoadStat;
MODELTYPE gMajorNo;
u16 gMinorNo;
bool gBlockMode;
s8 gViewerLimit;
s8 gPosLimit;
BST g_bstID;
static sdfVector4_t cmpCameraTargetPos;
static sdfVector4_t cmpCameraEyePos;
static sdfVector4_t cmpCameraUpVector;
void *cmpStatusModelTbl;
void *cmpStatusViewerModelTbl;
void *cmpStatusLightTbl;
static sdfVector4_t cmpModelPos;
static sdfVector4_t cmpModelRot;
f32 cmpModelScl;
f32 cmpModelEffScl;
s32 g_defMotNo;
f32 g_beforeLeng;
f32 g_smoothLeng;
sdf3DLightParallelPacket_t *g_pLightPacket;
s32 g_lightNo;
void *g_addr;
effHandle_t *g_hEff;
bool backHDrawSync;
s32 g_GoodByMode;
s32 g_GoodByModeZahyou;
StatusGattaiPosY_t *gGattaiPosOffsetY;

static dds3ModelResrc_t *Load(MODELTYPE MajorNo, s32 MinorNo, bool BlockMode);
u32 GetDevilSE(s32 devilID, s32 motionID);

// 0x1f63250
void datLoadCampStausTable(void) {
  void *Asset;
  s64 naturalAligment;
  void *v7;
  void *p_cmpStatusModelTbl;
  void *v11;
  void *v13;
  s64 v15;
  void *v16;
  void *p_cmpStatusViewerModelTbl;
  void *v20;
  void *v22;
  s64 v24;
  void *v25;
  void *v26;
  void *p_cmpStatusLightTbl;

  Load(Dependent, "cmp_tbl", "cmp_tbl");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "cmp_tbl", "CmpStatusModelTbl", 0);
  if (!Asset)
  {
    cmpStatusModelTbl = 0;
    goto LABEL_32;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_CmpStatusModelTbl)
      v7 = Asset;
    else
      v7 = 0;
  }
  else
  {
    v7 = 0;
  }
  cmpStatusModelTbl = (void *)v7;
  p_cmpStatusModelTbl = &cmpStatusModelTbl;
  if (Asset->klass->_2.naturalAligment < (u32)naturalAligment)
  {
    goto LABEL_32;
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_CmpStatusModelTbl)
    v11 = Asset;
  else
    v11 = 0;
LABEL_32:
  v13 = LoadAsset(_Ctrl_k__BackingField, "cmp_tbl", "CmpViewerModelTbl", 0);
  if (!v13)
  {
    cmpStatusViewerModelTbl = 0;
    goto LABEL_50;
  }
  if (v13->klass->_2.naturalAligment >= (u32)v15)
  {
    if (v13->klass->_2.typeHierarchy[v15 - 1] == Project_CmpStatusViewerModelTbl)
      v16 = v13;
    else
      v16 = 0;
  }
  else
  {
    v16 = 0;
  }
  cmpStatusViewerModelTbl = (void *)v16;
  p_cmpStatusViewerModelTbl = &cmpStatusViewerModelTbl;
  if (v13->klass->_2.naturalAligment < (u32)v15)
  {
    goto LABEL_50;
  }
  if (v13->klass->_2.typeHierarchy[v15 - 1] == Project_CmpStatusViewerModelTbl)
    v20 = v13;
  else
    v20 = 0;
LABEL_50:
  v22 = LoadAsset(_Ctrl_k__BackingField, "cmp_tbl", "CmpStatusLightTbl", 0);
  if (v22)
  {
    if (v22->klass->_2.naturalAligment >= (u32)v24)
    {
      if (v22->klass->_2.typeHierarchy[v24 - 1] == Project_CmpStatusLightTbl)
        v25 = v22;
      else
        v25 = 0;
    }
    else
    {
      v25 = 0;
    }
    cmpStatusLightTbl = (void *)v25;
    p_cmpStatusLightTbl = &cmpStatusLightTbl;
    if (v22->klass->_2.naturalAligment >= (u32)v24)
    {
      if (v22->klass->_2.typeHierarchy[v24 - 1] == Project_CmpStatusLightTbl)
        v26 = v22;
      else
        v26 = 0;
    }
    else
    {
      v26 = 0;
    }
  }
  else
  {
    v26 = 0;
    cmpStatusLightTbl = 0;
    p_cmpStatusLightTbl = &cmpStatusLightTbl;
  }
  Unload(Dependent, "cmp_tbl", 0);
}

// 0x1f636c0
void cmpDynamicBoneSet(dds3ModelHandle_t *_a_hModel, bool _OnOff) {
  void *gameObject;
  void *v6;
  void *transform;
  void *v8;

  gameObject = get_gameObject(a_hModel->modelRoot->modelObj, 0);
  v6 = 0;
  if (!op_Inequality(gameObject, 0, 0))
    goto LABEL_10;
  transform = get_transform(gameObject, 0);
  v8 = Find(transform, "program_ctrl/mant", 0);
  v6 = 0;
  if (!op_Inequality(v8, 0, 0))
    goto LABEL_10;
  goto LABEL_9;
  if (op_Inequality(v8, 0, 0))
LABEL_9:
    v6 = get_gameObject(v8, 0);
LABEL_10:
  if (!OnOff)
  {
    if (!op_Inequality(v6, 0, 0))
      return;
    if (!get_activeSelf(v6, 0))
      return;
LABEL_24:
    SetActive(v6, OnOff, 0);
    return;
  }
  if (!op_Inequality(v6, 0, 0))
    return;
  if (!get_activeSelf(v6, 0))
    goto LABEL_24;
}

// 0x1f638a0
void cmpSetModelMotion(dds3ModelHandle_t *a_hModel) {
  s32 MotionNo;
  f32 Spd;

  if (!gMajorNo)
  {
    MotionNo = GetTblDate(cmpStatusModelTbl, 0, 0)->MotionNo;
    Spd = GetTblDate(cmpStatusModelTbl, 0, 0)->Spd;
    goto LABEL_8;
  }
  MotionNo = GetTblDate(cmpStatusModelTbl, gMinorNo, 0)->MotionNo;
  Spd = GetTblDate(cmpStatusModelTbl, gMinorNo, 0)->Spd;
LABEL_8:
  if (g_bstID == 22)
  {
    goto LABEL_10;
  }
  if (gMajorNo)
  MotionNo = 2;
LABEL_10:
  if (g_defMotNo == MotionNo)
    return;
  g_defMotNo = MotionNo;
  mdlLoopMotion(a_hModel, 0, MotionNo);
  mdlSetMotionSpeed(a_hModel, Spd);
  if (g_GoodByMode)
  {
    mdlSingleMotion(a_hModel, 0, 13);
  }
}

// 0x1f63b40
bool cmpCheckHandle(void) {
  return cmpModelHandle != 0;
}

// 0x1f63bb0
bool cmpCheckCurse(void) {
  return evtBitCheck(161) && !evtBitCheck(163);
}

// 0x1f63bf0
void ModelLoadBuffStart(void) {
  void *v1;
  s32 size;
  s32 v6;

  v1 = Allocate(System_Collections_Generic_List_string_);
  __ctor_48217280(v1, 32);
  cmpModelBuffer = v1;
  size = cmpModelBuffer->_size;
  v6 = cmpModelBuffer->_version + 1;
  cmpModelBuffer->_size = 0;
  cmpModelBuffer->_version = v6;
  if (size >= 1)
    Clear(cmpModelBuffer->_items, 0, size, 0);
}

// 0x1f63cf0
void cmpInitCore(void) {
  cmpInitCore2();
}

// 0x1f63f50
void cmpSetLight(void) {
  sdfVector4_t *v1;
  f32 *v2;
  sdfVector4_t *v3;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  sdfVector4_t v16;
  sdfVector4_t v17;
  sdfVector4_t v18;
  sdfVector4_t v19;

  v1 = NewSpecific(sdfVector4_t, 3u);
  *(u64 *)&v1[2].y = 0;
  v2 = v1;
  *(u64 *)&v1[1].w = 0;
  *(u32 *)&v1[2].w = 0;
  *(_OWORD *)&v1[0] = xmmword_3CFD7A0;
  *(u32 *)&v1[1].z = 1051931443;
  *(u64 *)&v1[1] = 0x3ECCCCCD3F19999ALL;
  v3 = NewSpecific(sdfVector4_t, 3u);
  v3[2] = (sdfVector4_t)xmmword_3D006A0;
  v3[3] = (sdfVector4_t)xmmword_3D07B50;
  v3[4] = (sdfVector4_t)xmmword_3CFD5C0;
  v4 = v2[8];
  v5 = v2[9];
  v6 = v2[10];
  v7 = v2[11];
  v16.x = v4;
  v16.y = v5;
  v16.z = v6;
  v16.w = v7;
  dds3SetLightColor(0, 0, v16);
  dds3SetLightDir(0, 0, v3[2]);
  v8 = v2[12];
  v9 = v2[13];
  v10 = v2[14];
  v11 = v2[15];
  v17.x = v8;
  v17.y = v9;
  v17.z = v10;
  v17.w = v11;
  dds3SetLightColor(0, 1u, v17);
  dds3SetLightDir(0, 1u, v3[3]);
  v12 = v2[16];
  v13 = v2[17];
  v14 = v2[18];
  v15 = v2[19];
  v18.x = v12;
  v18.y = v13;
  v18.z = v14;
  v18.w = v15;
  dds3SetLightColor(0, 2u, v18);
  dds3SetLightDir(0, 2u, v3[4]);
  v19.z = 0.0;
  v19.w = 0.0;
  v19.x = 0.1;
  v19.y = 0.05;
  dds3SetAmbientColor(0, v19);
}

// 0x1f63d60
void cmpInitCore2(void) {
  struct sdfVector4_t cmpCameraEyePos_local;
  __int128 *p_CameraTM;
  _OWORD *p_x;
  struct sdfVector4_t v14;
  __int128 v15;
  __int128 v16;
  __int128 v17;
  __int128 v18;

  cmpSetLight();
  ScreenParam->fovy = 0.43633232;
  cmpCameraEyePos_local = cmpCameraEyePos;
  v14 = cmpCameraEyePos;
  cmpCameraEyePos_local = v14;
  CameraEyePos = cmpCameraEyePos_local;
  CameraTargetPos = cmpCameraTargetPos;
  CameraUpVector = cmpCameraUpVector;
  p_CameraTM = &CameraTM;
  v15 = *p_CameraTM;
  v16 = p_CameraTM[1];
  v17 = p_CameraTM[2];
  v18 = p_CameraTM[3];
  p_x = &vf00.x;
  p_x[4] = v15;
  p_x[5] = v16;
  p_x[6] = v17;
  p_x[7] = v18;
  sdf3SetCamera(ScreenParam, &CameraTM, cameraObject);
}

// 0x1f64160
void cmpSetLightUnit(s32 a_modelID, s32 a_lightNo) {
  sdf3DLight_t *v5;
  sdf3DLight_t *v7;
  sdf3DLight_t *v9;
  sdf3DLight_t *v11;
  sdf3DLight_t *m_Items;
  sdf3DLight_t *v13;
  sdf3DLight_t *v14;
  sdf3DLight_t *v18;
  cmpStatusLight_t *TblDate;
  sdf3DLight_t *v21;
  cmpStatusLight_t *v22;
  sdf3DLight_t *v24;
  cmpStatusLight_t *v25;
  sdf3DLight_t *v27;
  cmpStatusLight_t *v29;
  sdf3DLight_t *v31;
  cmpStatusLight_t *v32;
  sdf3DLight_t *v34;
  sdfVector4_t *dir;
  sdf3DLight_t *v37;
  sdf3DLight_t *v38;
  cmpStatusLight_t *v39;
  sdf3DLight_t *v41;
  cmpStatusLight_t *v42;
  sdf3DLight_t *v44;
  cmpStatusLight_t *v45;
  sdf3DLight_t *v47;
  void *v48;
  cmpStatusLight_t *v49;
  sdf3DLight_t *v51;
  cmpStatusLight_t *v52;
  sdf3DLight_t *v54;
  sdfVector4_t *v55;
  sdf3DLight_t *v57;
  sdf3DLight_t *v58;
  cmpStatusLight_t *v59;
  sdf3DLight_t *v61;
  cmpStatusLight_t *v62;
  sdf3DLight_t *v64;
  cmpStatusLight_t *v65;
  sdf3DLight_t *v67;
  void *v68;
  cmpStatusLight_t *v69;
  sdf3DLight_t *v71;
  cmpStatusLight_t *v72;
  sdf3DLight_t *v74;
  sdfVector4_t *v75;
  sdf3DLight_t *v77;
  f32 z;
  f32 x;
  f32 y;
  f32 v81;
  sdfVector4_t v84;

  v5 = Allocate(sdf3DLight_t);
  *(_OWORD *)&v5->color = 0u;
  *(_OWORD *)&v5->v = 0u;
  v7 = Allocate(sdf3DLight_t);
  *(_OWORD *)&v7->color = 0u;
  *(_OWORD *)&v7->v = 0u;
  v9 = Allocate(sdf3DLight_t);
  *(_OWORD *)&v9->color = 0u;
  *(_OWORD *)&v9->v = 0u;
  v11 = NewSpecific(sdf3DLight_t, 3u);
  v11[2] = v9;
  v14 = &v11[2];
  if (a_modelID < 0)
    return;
  if (g_pLightPacket)
  {
    if (a_lightNo < 0)
    {
      LOBYTE(a_lightNo) = GetTblDate(cmpStatusModelTbl, a_modelID, 0)->LightNo;
      goto LABEL_13;
    }
    {
      goto LABEL_13;
    }
LABEL_13:
    if (GetListCount(cmpStatusLightTbl, 0) > (u8)a_lightNo)
    {
      v18 = m_Items;
      TblDate = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v18->color.x = TblDate->col[0].x;
      v21 = m_Items;
      v22 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v21->color.y = v22->col[0].y;
      v24 = m_Items;
      v25 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v24->color.z = v25->col[0].z;
      v27 = m_Items;
      m_Items->color.w = 0.0;
      v29 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v27->v.x = v29->dir[0].x;
      v31 = m_Items;
      v32 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v31->v.y = v32->dir[0].y;
      v34 = m_Items;
      dir = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0)->dir;
      v37 = m_Items;
      v38 = v13;
      v34->v.z = dir[0].z;
      v37->v.w = 0.0;
      v39 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v38->color.x = v39->col[1].x;
      v41 = v13;
      v42 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v41->color.y = v42->col[1].y;
      v44 = v13;
      v45 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v44->color.z = v45->col[1].z;
      v47 = v13;
      v48 = cmpStatusLightTbl;
      v13->color.w = 0.0;
      v49 = GetTblDate(v48, (u8)a_lightNo, 0);
      v47->v.x = v49->dir[1].x;
      v51 = v13;
      v52 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v51->v.y = v52->dir[1].y;
      v54 = v13;
      v55 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0)->dir;
      v57 = v13;
      v58 = v14;
      v54->v.z = v55[1].z;
      v57->v.w = 0.0;
      v59 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v58->color.x = v59->col[2].x;
      v61 = v14;
      v62 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v61->color.y = v62->col[2].y;
      v64 = v14;
      v65 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v64->color.z = v65->col[2].z;
      v67 = v14;
      v68 = cmpStatusLightTbl;
      v14->color.w = 0.0;
      v69 = GetTblDate(v68, (u8)a_lightNo, 0);
      v67->v.x = v69->dir[2].x;
      v71 = v14;
      v72 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0);
      v71->v.y = v72->dir[2].y;
      v74 = v14;
      v75 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0)->dir;
      v77 = v14;
      z = v75[2].z;
      v74->v.z = z;
      v77->v.w = 0.0;
      x = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0)->amb.x;
      y = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0)->amb.y;
      v81 = GetTblDate(cmpStatusLightTbl, (u8)a_lightNo, 0)->amb.z;
      v84.x = x;
      v84.y = y;
      v84.w = 1.0;
      v84.z = v81;
      sdf3MakeLightParallelPacket(g_pLightPacket, v11, v84, 1);
    }
  }
}

// 0x1f64770
void cmpInitDstEff2(CMPMODEL_BST type) {
  effHandle_t *v4;

  if ((u32)type <= 1)
  {
    v4 = g_hEffBst2[type];
    if (v4)
    {
      dds3EffectSetLoop(v4, 1u);
      dds3EffectSetScale(g_hEffBst2[type], 1.0);
      return;
    }
  }
}

// 0x1f648a0
void cmpInitDstEff(void) {
  fileHandle_t *v1;
  void *topPtr;
  s64 naturalAligment;
  void *data;
  effHandle_t *EPL;
  fileHandle_t *v9;
  void *v10;
  s64 v11;
  effHandle_t *v12;
  effHandle_t *v13;
  effHandle_t *v14;

  v1 = fileLoad("fld_all", "BAD01");
  fileSync(v1);
  topPtr = v1->topPtr;
  if (topPtr)
  {
    if (topPtr->klass->_2.naturalAligment < (u32)naturalAligment || topPtr->klass->_2.typeHierarchy[naturalAligment - 1] != Project_libsdf_sdfResourcePack)
    {
      v10 = v1->topPtr;
      goto LABEL_22;
    }
  }
  data = topPtr[1].klass->_1.byval_arg.data;
  EPL = dds3EffectLoadEPL(data);
  if (!EPL)
  g_hEffBst2[0] = EPL;
  fileHandleFree(v1);
  cmpInitDstEff2(0);
  v9 = fileLoad("fld_all", "BAD04");
  fileSync(v9);
  v10 = v9->topPtr;
  if (v10)
  {
    if (v10->klass->_2.naturalAligment < (u32)v11 || v10->klass->_2.typeHierarchy[v11 - 1] != Project_libsdf_sdfResourcePack)
    {
LABEL_22:
    }
  }
  v12 = g_hEffBst2;
  v13 = dds3EffectLoadEPL(v10[1].klass->_1.byval_arg.data);
  v14 = v13;
  v12[1] = v14;
  fileHandleFree(v9);
  cmpInitDstEff2(1);
}

// 0x1f64b30
CMPMODEL_BST cmpCreateBstEff(void) {
  u32 v5;
  effHandle_t *v7;

  if (!cmpModelHandle)
    return -1;
  if (g_bstID == 11)
  {
    v5 = 0;
    goto LABEL_15;
  }
  if (g_bstID == 10)
  {
    v5 = 1;
LABEL_15:
    v7 = g_hEffBst2[v5];
    g_hEffBst = v7;
    if (g_hEffBst)
    {
      Reset(g_hEffBst, 0);
      return v5;
    }
    return -1;
  }
  g_hEffBst = 0;
  return -1;
}

// 0x1f64d60
void cmpDeleteBstEff(void) {
  effHandle_t *v2;
  effHandle_t *v3;
  effHandle_t *v9;

  v2 = g_hEffBst2[0];
  if (!v2)
  {
    goto LABEL_5;
  }
  Delete(v2);
  g_hEffBst2[0] = 0;
LABEL_5:
  v3 = g_hEffBst2[1];
  if (v3)
  {
    Delete(v3);
    v9 = g_hEffBst2;
    v9[1] = 0;
  }
  g_hEffBst = 0;
  g_pDatBst = 0;
  g_bstID = 22;
}

// 0x1f64f60
void cmpDrawBstEff(void) {
  f32 *p_x;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  sdfVector4_t v11;

  if (!cmpModelHandle)
    return;
  if (!g_hEffBst)
    return;
  sdfModelGetMarkPos(cmpModelHandle->modelRoot, 2);
  p_x = &vf00.x;
  v6 = p_x[4];
  v7 = p_x[5];
  v8 = p_x[6];
  v9 = p_x[7];
  v11.x = v6;
  v11.y = v7;
  v11.z = v8;
  v11.w = v9;
  dds3EffectSetPosition(g_hEffBst, v11);
  dds3EffectDraw(g_hEffBst);
}

// 0x1f65180
void Init(void) {
  sdf3DLightParallelPacket_t *v6;

  cmpInitCore2();
  cmpLoadEffect();
  cmpInitDstEff();
  g_pLightPacket = 0;
  v6 = Allocate(sdf3DLightParallelPacket_t);
  _ctor(v6, 0);
  g_pLightPacket = v6;
  g_lightNo = -1;
  g_defMotNo = -1;
  gLoadStat = 0;
  *(u32 *)&gMajorNo = 7;
  gBlockMode = 0;
  *(u64 *)&g_beforeLeng = 0x41F0000000000000LL;
  ModelLoadBuffStart();
}

// 0x1f654a0
void End(void) {
  _BOOL8 Model;

  Model = cmpWaitLoadModel();
  cmpFreeResource();
  ModelLoadBuffClear();
  cmpModelBuffer = 0;
  cmpDeleteBstEff();
  cmpDeleteEffect();
  if (g_pLightPacket)
  {
    g_pLightPacket = 0;
  }
}

// 0x1f659a0
void ModelLoadBuffEnd(void) {
  ModelLoadBuffClear();
  cmpModelBuffer = 0;
}

// 0x1f65bc0
void ModelLoadBuffClear(void) {
  Il2CppObject *current;
  void *v6;
  s32 size;
  s32 v8;
  System_Collections_Generic_List_Enumerator_T__o v9;

  memset(&v9, 0, sizeof(v9));
  if (!cmpModelBuffer)
    return;
  _GetEnumerator(&v9, cmpModelBuffer);
  while (_MoveNext(&v9))
  {
    current = v9._current;
    Unload(Dependent, current, 0);
  }
  _Dispose(&v9);
  v6 = cmpModelBuffer;
  size = v6->_size;
  v8 = v6->_version + 1;
  v6->_size = 0;
  v6->_version = v8;
  if (size >= 1)
    Clear(v6->_items, 0, size, 0);
}

// 0x1f65e00
void cmpMemCheckRelease(void) {
  if (sdfMemGetDifference() < 20971521)
    return;
  sdfMemResourcesRelease();
}

// 0x1f656e0
bool cmpFreeResource(void) {
  dds3ModelHandle_t *v4;
  u32 DevilSE;

  if (!cmpModelHandle)
    return cmpModelHandle != 0;
  v4 = cmpModelHandle;
  Free(v4);
  cmpModelHandle = 0;
  DevilSE = GetDevilSE(gMinorNo, -1);
  p2sdUnLoadSMGFile(DevilSE, 1);
  p2sdUnLoadSMGFile(DevilSE + 0x10000000, 1);
  if (cmpModelBuffer->_size >= 32)
  {
    ModelLoadBuffClear();
    if (sdfMemGetDifference() < 20971521)
      return cmpModelHandle != 0;
    sdfMemResourcesRelease();
    return cmpModelHandle != 0;
  }
  return cmpModelHandle != 0;
}

// 0x1f65ec0
static dds3ModelResrc_t *Load(MODELTYPE MajorNo, s32 MinorNo, bool BlockMode) {
  return mdlPrepare(MajorNo, MinorNo, BlockMode);
}

// 0x1f65f40
s8 Setup(u16 DevilID, bool BlockMode) {
  s8 v7;
  u16 v10;
  s32 v11;
  bool FlagScreenShot;
  bool v16;
  char gBlockMode_local;
  dds3ModelResrc_t *v24;

  if (gLoadStat)
    return 0;
  if (DevilID)
  {
    v10 = DevilID;
    if (g_GoodByMode)
      v11 = 1;
    else
      v11 = 7;
    goto LABEL_26;
  }
  if (!evtBitCheck(161))
  {
    v11 = 0;
    v10 = 1;
    goto LABEL_26;
  }
  v11 = 0;
  if (evtBitCheck(163))
    v10 = 1;
  else
    v10 = 4;
LABEL_26:
  if (v11 != gMajorNo)
    goto LABEL_42;
  if (gMinorNo != v10)
    goto LABEL_42;
  if (!cmpModelHandle)
    goto LABEL_42;
  FlagScreenShot = cmpGetFlagScreenShot();
  if (!FlagScreenShot)
  {
    cmpSetModelMotion(cmpModelHandle);
    cmpCreateBstEff();
    cmpSetLightUnit(DevilID, g_lightNo);
    return 2;
  }
LABEL_42:
  v16 = BlockMode;
  cmpFreeResource();
  gBlockMode = v16;
  v7 = 1;
  gMajorNo = v11;
  gMinorNo = v10;
  g_defMotNo = -1;
  gLoadStat = 1;
  cmpSetLightUnit(DevilID, g_lightNo);
  if (!gBlockMode)
    return v7;
  gBlockMode_local = 1;
  v24 = mdlPrepare(gMajorNo, gMinorNo, gBlockMode_local);
  cmpChkStatusModelLoadStat();
  gLoadStat = 2;
  return 1;
}

// 0x1f662d0
s8 cmpChkStatusModelLoadStat(void) {
  u16 v4;
  s32 v5;
  _BOOL4 v6;
  dds3ModelResrc_t *v8;
  s32 v10;
  u32 DevilSE;
  u16 v13;
  s32 v14;
  dds3ModelHandle_t *v15;

  if (gLoadStat != 1)
  {
    goto LABEL_7;
  }
  mdlPrepare(gMajorNo, gMinorNo, gBlockMode);
  gLoadStat = 2;
LABEL_7:
  if (!gLoadStat)
    return 0;
  v4 = gMajorNo;
  v5 = gMinorNo;
  v6 = gBlockMode;
  v8 = mdlPrepare(v4, v5, v6);
  if (!READY(v8))
    return 1;
  cmpFreeResource();
  ModelLoadBuff();
  v10 = gMinorNo;
  DevilSE = GetDevilSE(v10, -1);
  p2sdLoadSMGFile(DevilSE);
  p2sdLoadSMGFile(DevilSE + 0x10000000);
  v13 = gMajorNo;
  v14 = gMinorNo;
  v15 = mdlLoad(v13, v14);
  cmpModelHandle = v15;
  cmpSetModelMotion(cmpModelHandle);
  cmpDynamicBoneSet(cmpModelHandle, 0);
  cmpCreateBstEff();
  mdlEffSclSet = 0;
  gLoadStat = 0;
  return 2;
}

// 0x1f66840
void ModelLoadInitAction(void) {
  s32 v5;
  s32 v6;
  u32 DevilSE;

  if (gMjnRun == 1)
    return;
  if (gMajorNo != 7)
    return;
  if (gMinorNo == 384)
    v5 = 15;
  else
    v5 = 7;
  cmpSetSmoothSingleMotion(v5, 0.0, 0.0);
  v6 = 13;
  if (evtBitCheck(42))
  {
    if ((u32)sub_1905740(2, 0) == 1)
      v6 = 16;
    else
      v6 = 13;
  }
  DevilSE = GetDevilSE(gMinorNo, v6);
  sBtlStopSE(DevilSE);
  sBtlPlaySESub(DevilSE, 127);
}

// 0x1f66680
void ModelLoadBuff(void) {
  char *ModelName;
  void *cmpModelBuffer_local;
  u64 *v9;
  s64 size;
  void *items;
  Il2CppClass **v12;

  ModelName = mdlGetModelName(gMajorNo, gMinorNo);
  if (!_Contains(cmpModelBuffer, ModelName))
  {
    Load(Dependent, ModelName, ModelName);
    cmpModelBuffer_local = cmpModelBuffer;
    v9 = Method_System_Collections_Generic_List_string__Add__;
    size = cmpModelBuffer_local->_size;
    ++cmpModelBuffer_local->_version;
    items = cmpModelBuffer_local->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(cmpModelBuffer_local, ModelName, *(const MethodInfo_2DFC660 **)(*(u64 *)(v9[4] + 192) + 112));
    }
    else
    {
      v12 = &items->obj.klass + size;
      v12[4] = ModelName;
      cmpModelBuffer_local->_size = size + 1;
    }
  }
}

// 0x1f655d0
bool cmpWaitLoadModel(void) {
  bool v7;
  dds3ModelResrc_t *v8;

  if (cmpChkStatusModelLoadStat() != 1)
    return 0;
  v7 = 1;
  v8 = mdlPrepare(gMajorNo, gMinorNo, 1);
  if (cmpChkStatusModelLoadStat() == 1)
    return 0;
  return v7;
}

// 0x1f66b50
void cmpSetMotion(s32 a_motNo, f32 a_motSpd) {
  if (cmpModelHandle)
    goto LABEL_6;
  return;
  if (cmpModelHandle)
  {
LABEL_6:
    mdlLoopMotion(cmpModelHandle, 0, a_motNo);
    mdlSetMotionSpeed(cmpModelHandle, a_motSpd);
    return;
  }
}

// 0x1f669f0
void cmpSetSmoothSingleMotion(s32 a_motNo, f32 a_beforeLeng, f32 a_smoothLeng) {
  if (cmpModelHandle)
    goto LABEL_6;
  return;
  if (cmpModelHandle)
  {
LABEL_6:
    mdlSmoothSingleMotion(cmpModelHandle, 0, a_motNo, a_beforeLeng, a_smoothLeng, 0.0);
    return;
  }
}

// 0x1f66cb0
void cmpSetSmoothLoopMotion(s32 a_motNo, f32 a_beforeLeng, f32 a_smoothLeng) {
  if (cmpModelHandle)
    goto LABEL_6;
  return;
  if (cmpModelHandle)
  {
LABEL_6:
    mdlSmoothLoopMotion(cmpModelHandle, 0, a_motNo, a_beforeLeng, a_smoothLeng, 0.0);
    return;
  }
}

// 0x1f66e10
void cmpSetLoopMotion(s32 a_motNo) {
  if (cmpModelHandle)
    goto LABEL_6;
  return;
  if (cmpModelHandle)
  {
LABEL_6:
    mdlLoopMotion(cmpModelHandle, 0, a_motNo);
    return;
  }
}

// 0x1f66f50
void cmpSetMotionSpeed(f32 a_motSpd) {
  if (cmpModelHandle)
    goto LABEL_6;
  return;
  if (cmpModelHandle)
  {
LABEL_6:
    mdlSetMotionSpeed(cmpModelHandle, a_motSpd);
    return;
  }
}

// 0x1f67090
void cmpSetColor(s32 rgba) {
  mdlSetColor(cmpModelHandle, rgba);
}

// 0x1f67160
s32 cmpGetMotionNum(void) {
  if (cmpModelHandle)
  {
    return mdlGetMotionNum(cmpModelHandle, 0);
  }
  return -1;
}

// 0x1f672a0
s32 cmpGetMotionCut(void) {
  if (cmpModelHandle)
  {
    return mdlGetNumOfCut(cmpModelHandle, 0);
  }
  return -1;
}

// 0x1f673e0
f32 cmpGetMotionSpeed(void) {
  if (!cmpModelHandle)
    return -1.0;
  return mdlGetMotionSpeed(cmpModelHandle);
}

// 0x1f67530
f32 cmpSetModelScale(dds3ModelHandle_t *Handle, s32 Mode) {
  s32 gMinorNo_local;
  f32 v8;
  int32x4_t v18;
  f32 Scl;
  cmpStatusModel_t *TblDate;
  f32 v24;
  f32 scale;

  if (gMajorNo)
    goto LABEL_4;
  gMinorNo_local = 0;
  if (Mode)
    goto LABEL_7;
LABEL_21:
  Scl = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Scl;
  TblDate = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0);
  v24 = Scl + cmpModelScl;
  if (v24 < 0.0)
    v24 = 0.0;
  if ((f32)(TblDate->EffScl + cmpModelEffScl) < 0.0)
    v8 = 0.0;
  else
    v8 = TblDate->EffScl + cmpModelEffScl;
  scale = v24;
  goto LABEL_11;
LABEL_4:
  gMinorNo_local = gMinorNo;
  if (!Mode)
    goto LABEL_21;
LABEL_7:
  v8 = 1.0;
  scale = sBtlGetVisualDataZ(gMinorNo_local)->scale;
LABEL_11:
  __asm { FMOV            V0.4S, #1.0 }
  _Q0.n128_f32[0] = scale;
  v18 = vzip1q_s32(_Q0, _Q0);
  v18.n128_f32[2] = scale;
  vct_A = (struct sdfVector4_t)v18;
  mdlSetScale(Handle);
  cmpSetEffScl(v8);
  return scale;
}

// 0x1f678c0
void cmpSetModelPosition(dds3ModelHandle_t *Handle) {
  s32 gMinorNo_local;
  s32 i;
  f32 y;
  u32 *p_z;
  char *v10;
  cmpStatusModel_t *TblDate;
  f32 *p_x;
  f32 v14;
  f32 *v15;
  f32 v17;
  f32 *p_y;
  f32 v20;
  s16 PosXMin;
  s16 *p_PosYMax;
  f32 v25;
  s16 PosYMin;
  s16 PosZMin;
  s16 v28;
  f32 *v29;
  f32 v30;
  f32 v31;
  sdfVector4_t *p_cmpModelPos;
  f32 v33;
  f32 v34;
  s64 v35;
  s64 v36;
  u32 *v38;
  void *v41;
  void *v42;
  char *v43;
  void *v44;
  s64 v45;
  s64 v46;

  v46 = 0;
  v45 = 0;
  if (gMajorNo)
  {
    gMinorNo_local = gMinorNo;
    goto LABEL_10;
  }
  gMinorNo_local = 0;
LABEL_10:
  for (i = 0; i != 3; ++i)
  {
    if (g_GoodByModeZahyou)
    {
      if (i != 1)
      {
        if (i == 2)
        {
          p_z = &cmpModelPos.z;
          v10 = (char *)&v45 + 4;
          goto LABEL_9000;
        }
        if (i)
          goto LABEL_83;
        p_z = &cmpModelPos.x;
        v10 = (char *)&v46 + 4;
LABEL_9000:
        *(u32 *)v10 = *p_z;
        continue;
      }
      y = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Pos.y;
      *(f32 *)&v46 = y + cmpModelPos.y;
      continue;
    }
    TblDate = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0);
    if (i == 2)
    {
      v15 = &TblDate->Pos.z;
      v17 = *v15 + cmpModelPos.z;
      LODWORD(v15) = (u8)gViewerLimit;
      *((f32 *)&v45 + 1) = v17;
      if (!(u32)v15)
        continue;
LABEL_33:
      if (!gPosLimit)
        continue;
      if (i == 1)
      {
        PosYMin = GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->PosYMin;
        p_PosYMax = &GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->PosYMax;
        v25 = PosYMin;
        if (*(f32 *)&v46 >= v25)
          goto LABEL_55;
      }
      else
      {
        if (!i)
        {
          PosXMin = GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->PosXMin;
          p_PosYMax = &GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->PosXMax;
          v25 = PosXMin;
          if (*((f32 *)&v46 + 1) < v25)
            goto LABEL_45;
LABEL_55:
          v28 = *p_PosYMax;
          if (!i)
          {
            v25 = v28;
            if (*((f32 *)&v46 + 1) <= v25)
              goto LABEL_67;
            goto LABEL_63;
          }
          if (i == 2)
          {
            v25 = v28;
            if (*((f32 *)&v45 + 1) > v25)
              goto LABEL_63;
          }
          else
          {
            v25 = v28;
            if (*(f32 *)&v46 <= v25)
              goto LABEL_67;
LABEL_63:
            v29 = (f32 *)&v46 + 1;
            switch (i)
            {
              case 0:
                break;
              case 1:
                goto LABEL_64;
              case 2:
                goto LABEL_65;
            }
LABEL_66:
            *v29 = v25;
          }
LABEL_67:
          switch (i)
          {
            case 0:
              v30 = *((f32 *)&v46 + 1);
              v31 = v30
                  - GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Pos.x;
              p_cmpModelPos = &cmpModelPos;
              break;
            case 1:
              v33 = *(f32 *)&v46;
              v31 = v33
                  - GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Pos.y;
              p_cmpModelPos = &cmpModelPos.y;
              break;
            case 2:
              v34 = *((f32 *)&v45 + 1);
              v31 = v34
                  - GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Pos.z;
              p_cmpModelPos = &cmpModelPos.z;
              break;
          }
          p_cmpModelPos->x = v31;
          continue;
        }
        PosZMin = GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->PosZMin;
        p_PosYMax = &GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->PosZMax;
        v25 = PosZMin;
        if (*((f32 *)&v45 + 1) >= v25)
          goto LABEL_55;
      }
LABEL_45:
      if (i)
      {
        if (i == 2)
LABEL_65:
          v29 = (f32 *)&v45 + 1;
        else
LABEL_64:
          v29 = &v46;
      }
      else
      {
        v29 = (f32 *)&v46 + 1;
      }
      goto LABEL_66;
    }
    if (i == 1)
    {
      p_y = &TblDate->Pos.y;
      v20 = *p_y + cmpModelPos.y;
      LODWORD(p_y) = (u8)gViewerLimit;
      *(f32 *)&v46 = v20;
      if (!(u32)p_y)
        continue;
      goto LABEL_33;
    }
    if (i)
    {
LABEL_83:
      v41 = InitializedMetadata(&System_IndexOutOfRangeException);
      v42 = Allocate(v41);
      v43 = InitializedMetadata(&"Invalid Vector4 index!");
      v44 = InitializedMetadata(&Method_UnityEngine_Vector4_get_Item__);
    }
    p_x = &TblDate->Pos.x;
    v14 = *p_x + cmpModelPos.x;
    LODWORD(p_x) = (u8)gViewerLimit;
    *((f32 *)&v46 + 1) = v14;
    if ((u32)p_x)
      goto LABEL_33;
  }
  v35 = v46;
  v36 = v45;
  goto LABEL_76;
LABEL_77:
  v38 = &vf00.x;
  v38[4] = HIDWORD(v35);
  v38[5] = v35;
  v38[6] = HIDWORD(v36);
  v38[7] = v36;
  goto LABEL_78;
LABEL_76:
  goto LABEL_77;
LABEL_78:
  mdlSetPosition(Handle);
}

// 0x1f67fe0
void cmpSetModelRotate(dds3ModelHandle_t *Handle) {
  s32 gMinorNo_local;
  cmpStatusModel_t *TblDate;
  f32 y;
  f32 v11;
  cmpStatusModel_t *v12;
  cmpStatusModel_t *v14;
  cmpStatusModel_t *v15;

  if (!gMajorNo)
  {
    gMinorNo_local = 0;
    goto LABEL_7;
  }
  gMinorNo_local = gMinorNo;
LABEL_7:
  if (g_GoodByModeZahyou)
  {
    TblDate = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0);
    y = cmpModelRot.y;
    v11 = TblDate->Rot.x + cmpModelRot.x;
    goto LABEL_18;
  }
  v12 = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0);
  v11 = v12->Rot.x + cmpModelRot.x;
  v14 = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0);
  y = v14->Rot.y + cmpModelRot.y;
LABEL_18:
  v15 = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0);
  FromEuler((f32)(v11 * 3.1415927) / 180.0, (f32)(y * 3.1415927) / 180.0, (f32)((f32)(v15->Rot.z + cmpModelRot.z) * 3.1415927) / 180.0);
  mdlSetRotate(Handle);
}

// 0x1f681e0
void cmpSetStatusModelParam(void) {
  struct sdfVector4_t cmpCameraEyePos_local;
  struct sdfVector4_t CameraTargetPos_local;
  struct sdfVector4_t CameraEyePos_local;
  struct sdfVector4_t CameraOffset_local;
  f32 *p_x;
  struct sdfVector4_t v15;
  f32 *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  _OWORD *v28;
  __int128 v29;
  __int128 v30;
  __int128 v31;
  f32 v35;
  f32 v36;
  f32 v37;
  struct sdfVector4_t v38;
  f32 v39;

  cmpCameraEyePos_local = cmpCameraEyePos;
  v38 = cmpCameraEyePos;
  cmpCameraEyePos_local = v38;
  CameraEyePos = cmpCameraEyePos_local;
  CameraTargetPos = cmpCameraTargetPos;
  CameraUpVector = cmpCameraUpVector;
  ScreenParam->fovy = 0.43633232;
  GlobalParamFlag = 0;
  sdf3MakeScreenParam(ScreenParam);
  CameraTargetPos_local = CameraTargetPos;
  vct_A = CameraTargetPos_local;
  CameraEyePos_local = CameraEyePos;
  vct_B = CameraEyePos_local;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x44160000u));
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  CameraOffset_local = CameraOffset;
  vct_B = CameraOffset_local;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  v37 = p_x[5];
  v39 = p_x[4];
  v35 = p_x[7];
  v36 = p_x[6];
  v15 = CameraEyePos;
  vct_A = v15;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v16 = &vf00.x;
  v17 = v16[4];
  v18 = v16[5];
  v19 = v16[6];
  v20 = v16[7];
  x = CameraUpVector.x;
  y = CameraUpVector.y;
  z = CameraUpVector.z;
  w = CameraUpVector.w;
  sub_1B33630(0, v39, v37, v36, v35, v17, v18, v19, v20, COERCE_DOUBLE(__PAIR64__(LODWORD(y), LODWORD(x))), COERCE_DOUBLE(__PAIR64__(LODWORD(w), LODWORD(z))));
  v28 = &vf00.x;
  v29 = v28[4];
  v30 = v28[5];
  v31 = v28[6];
  *(_OWORD *)&CameraTM.m03 = v28[7];
  *(_OWORD *)&CameraTM.m01 = v30;
  *(_OWORD *)&CameraTM.m02 = v31;
  *(_OWORD *)&CameraTM.m00 = v29;
  sdf3MakeViewportPacket(DrawEnv[FrameID]->ViewportPacket, ScreenParam, &CameraTM, cameraObject);
  sdf3SetCamera(ScreenParam, &CameraTM, cameraObject);
}

// 0x1f688e0
void cmpGetPos(sdfVector4_t *a_pos) {
  if (!cmpModelHandle)
    return;
  mdlGetPosition(cmpModelHandle);
  *a_pos = vct_A;
  return;
}

// 0x1f68ab0
void cmpGetPosStatus(sdfVector4_t *a_pos) {
  s32 gMinorNo_local;
  struct sdfVector4_t Pos;

  if (gMajorNo)
  {
    gMinorNo_local = gMinorNo;
    goto LABEL_8;
  }
  gMinorNo_local = 0;
LABEL_8:
  Pos = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Pos;
  vct_A = Pos;
  *a_pos = vct_A;
}

// 0x1f68c80
void cmpGetRot(sdfVector4_t *a_rot) {
  s32 gMinorNo_local;
  f32 x;
  f32 v8;
  f32 v9;
  f32 y;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;

  if (gMajorNo)
  {
    gMinorNo_local = gMinorNo;
    goto LABEL_8;
  }
  gMinorNo_local = 0;
LABEL_8:
  x = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Rot.x;
  v8 = x + cmpModelRot.x;
  a_rot->x = v8;
  if (v8 <= 180.0)
  {
    if (v8 >= -179.0)
      goto LABEL_17;
    v9 = -a_rot->x;
  }
  else
  {
    v9 = v8 + -360.0;
  }
  a_rot->x = v9;
LABEL_17:
  y = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Rot.y;
  v12 = y + cmpModelRot.y;
  a_rot->y = v12;
  if (v12 <= 180.0)
  {
    if (v12 >= -179.0)
      goto LABEL_24;
    v13 = -a_rot->y;
  }
  else
  {
    v13 = v12 + -360.0;
  }
  a_rot->y = v13;
LABEL_24:
  v14 = GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->Rot.z
      + cmpModelRot.z;
  a_rot->z = v14;
  if (v14 <= 180.0)
  {
    if (v14 >= -179.0)
      return;
    v15 = -a_rot->z;
  }
  else
  {
    v15 = v14 + -360.0;
  }
  a_rot->z = v15;
}

// 0x1f68ea0
void cmpGetScl(sdfVector4_t *a_scl) {
  if (!cmpModelHandle)
    return;
  mdlGetScale(cmpModelHandle);
  *a_scl = vct_A;
  return;
}

// 0x1f69070
void cmpGetEffScl(f32 *a_scl, bool _screenShot) {
  s32 gMinorNo_local;

  if (!cmpModelHandle)
    return;
  if (gMajorNo)
  {
    gMinorNo_local = gMinorNo;
    if (screenShot)
      goto LABEL_16;
    goto LABEL_21;
  }
  gMinorNo_local = 0;
  if (screenShot)
  {
LABEL_16:
    *a_scl = cmpModelEffScl;
    return;
  }
LABEL_21:
  *a_scl = cmpModelEffScl
         + GetTblDate(cmpStatusModelTbl, gMinorNo_local, 0)->EffScl;
}

// 0x1f69210
void cmpSetPos(const sdfVector4_t *a_pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;

  w = a_pos->w;
  z = a_pos->z;
  y = a_pos->y;
  x = a_pos->x;
  if (cmpModelHandle)
    goto LABEL_6;
  return;
  if (cmpModelHandle)
  {
LABEL_6:
    p_x = &vf00.x;
    p_x[4] = x;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    mdlSetPosition(cmpModelHandle);
    return;
  }
}

// 0x1f693f0
void cmpSetRot(const sdfVector4_t *_rot) {
  f32 z;
  f32 y;
  f32 x;

  z = rot->z;
  y = rot->y;
  x = rot->x;
  if (cmpModelHandle)
    goto LABEL_6;
  return;
  if (cmpModelHandle)
  {
LABEL_6:
    FromEuler((f32)(x * 3.1415927) / 180.0, (f32)(y * 3.1415927) / 180.0, (f32)(z * 3.1415927) / 180.0);
    mdlSetRotate(cmpModelHandle);
    return;
  }
}

// 0x1f69580
void cmpSetScl(f32 _scl) {
  int32x4_t v6;

  v6 = vzip1q_s32((int32x4_t)LODWORD(scl), (int32x4_t)LODWORD(scl));
  v6.n128_f32[2] = scl;
  vct_A = (struct sdfVector4_t)v6;
  mdlSetScale(cmpModelHandle);
}

// 0x1f677b0
void cmpSetEffScl(f32 _scl) {
  if (mdlEffSclSet)
    return;
  mdlSetEffectScale(cmpModelHandle, scl);
  mdlEffSclSet = 1;
  return;
}

// 0x1f696e0
void cmpAddPos(f32 a_x, f32 a_y, f32 a_z) {
  f32 *static_fields;
  f32 v9;

  v9 = static_fields[39] + a_y;
  static_fields[38] = static_fields[38] + a_x;
  static_fields[39] = v9;
  static_fields[40] = static_fields[40] + a_z;
}

// 0x1f69770
void cmpSetPos_GoodBy(f32 a_x, f32 a_y, f32 a_z) {
  f32 *static_fields;

  static_fields[38] = a_x;
  static_fields[39] = a_y;
  static_fields[40] = a_z;
}

// 0x1f697f0
f32 cmpAdjustPosY_Gattai(void) {
  u32 v2;
  Il2CppClass **v3;
  s64 v5;
  StatusGattaiPosY_t *gGattaiPosOffsetY_local;
  StatusGattaiPosY_t *v8;

  v2 = 1;
  while (1)
  {
    v5 = v2 - 1;
    gGattaiPosOffsetY_local = gGattaiPosOffsetY;
    v8 = gGattaiPosOffsetY_local[(u32)v5];
    if (v8->devilId == gMinorNo)
      break;
    gGattaiPosOffsetY_local = gGattaiPosOffsetY;
    v3 = &gGattaiPosOffsetY_local->obj.klass + v2++;
    if (LODWORD(v3[4]->_1.name) == -1)
      return 0.0;
  }
  v8 = gGattaiPosOffsetY[v5];
  return v8->y;
}

// 0x1f698f0
void cmpAddRot(f32 a_x, f32 a_y, f32 a_z) {
  s32 gMinorNo_local;
  s32 RotYMin;
  s32 RotYMax;
  f32 v16;
  u32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v26;
  u32 v28;
  f32 v29;
  u32 v31;
  f32 v32;

  if (gMajorNo)
  {
    gMinorNo_local = gMinorNo;
    goto LABEL_8;
  }
  gMinorNo_local = 0;
LABEL_8:
  cmpModelRot.x = cmpModelRot.x + a_x;
  RotYMin = (u16)GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->RotYMin;
  RotYMax = (u16)GetTblDate(cmpStatusViewerModelTbl, gMinorNo_local, 0)->RotYMax;
  if (cmpGetFlagScreenShot())
  {
LABEL_19:
    v16 = cmpModelRot.z + a_z;
    cmpModelRot.y = a_y + cmpModelRot.y;
    cmpModelRot.z = v16;
    goto LABEL_20;
  }
  if (!(RotYMin | RotYMax))
  {
    goto LABEL_19;
  }
  v19 = (s16)RotYMin;
  v20 = (s16)RotYMax;
  v21 = cmpModelRot.y + a_y;
  if (v21 < 0.0)
    v21 = v21 + 360.0;
  if (a_y >= 0.0)
  {
    if (v21 > v19 && v21 <= v20 && a_y > 0.0)
      a_y = 0.0;
    goto LABEL_19;
  }
  else
  {
    if (v21 < v20 && v21 >= v19)
      a_y = 0.0;
    goto LABEL_19;
  }
  v26 = cmpModelRot.z + a_z;
  cmpModelRot.y = a_y + cmpModelRot.y;
  cmpModelRot.z = v26;
LABEL_20:
  if (cmpModelRot.x <= 180.0)
    goto LABEL_47;
  v18 = cmpModelRot.x + -360.0;
LABEL_68:
  cmpModelRot.x = v18;
  goto LABEL_50;
LABEL_47:
  if (v17)
  {
    if (cmpModelRot.x >= -179.0)
      goto LABEL_49;
    goto LABEL_65;
  }
  if (cmpModelRot.x < -179.0)
  {
LABEL_65:
    v18 = -cmpModelRot.x;
    goto LABEL_68;
  }
LABEL_49:
LABEL_50:
  if (cmpModelRot.y > 180.0)
  {
    v29 = cmpModelRot.y + -360.0;
    goto LABEL_74;
  }
  if (v28)
  {
    if (cmpModelRot.y >= -179.0)
      goto LABEL_56;
LABEL_71:
    v29 = -cmpModelRot.y;
LABEL_74:
    cmpModelRot.y = v29;
    goto LABEL_57;
  }
  if (cmpModelRot.y < -179.0)
    goto LABEL_71;
LABEL_56:
LABEL_57:
  if (cmpModelRot.z > 180.0)
  {
    v32 = cmpModelRot.z + -360.0;
LABEL_80:
    cmpModelRot.z = v32;
    return;
  }
  if (v31)
  {
    if (cmpModelRot.z >= -179.0)
      return;
LABEL_77:
    v32 = -cmpModelRot.z;
    goto LABEL_80;
  }
  if (cmpModelRot.z < -179.0)
    goto LABEL_77;
}

// 0x1f69d60
void cmpSetRot_GoodBy(f32 a_x, f32 a_y, f32 a_z) {
  u32 v9;
  f32 v11;
  u32 v13;
  f32 v14;
  u32 v16;

  cmpModelRot.x = a_x;
  cmpModelRot.y = a_y;
  cmpModelRot.z = a_z;
  if (cmpModelRot.x <= 180.0)
    goto LABEL_12;
  v11 = cmpModelRot.x + -360.0;
LABEL_33:
  cmpModelRot.x = v11;
  goto LABEL_15;
LABEL_12:
  if (v9)
  {
    if (cmpModelRot.x >= -179.0)
      goto LABEL_14;
    goto LABEL_30;
  }
  if (cmpModelRot.x < -179.0)
  {
LABEL_30:
    v11 = -cmpModelRot.x;
    goto LABEL_33;
  }
LABEL_14:
LABEL_15:
  if (cmpModelRot.y > 180.0)
  {
    v14 = cmpModelRot.y + -360.0;
    goto LABEL_39;
  }
  if (v13)
  {
    if (cmpModelRot.y >= -179.0)
      goto LABEL_21;
LABEL_36:
    v14 = -cmpModelRot.y;
LABEL_39:
    cmpModelRot.y = v14;
    goto LABEL_22;
  }
  if (cmpModelRot.y < -179.0)
    goto LABEL_36;
LABEL_21:
LABEL_22:
  if (cmpModelRot.z <= 180.0)
  {
    if (v16)
    {
      if (cmpModelRot.z >= -179.0)
        return;
    }
    else
    {
      if (cmpModelRot.z >= -179.0)
        return;
    }
    cmpModelRot.z = -cmpModelRot.z;
  }
  else
  {
    cmpModelRot.z = cmpModelRot.z + -360.0;
  }
}

// 0x1f6a060
void cmpAddScl(f32 a_scl) {
  cmpModelScl = cmpModelScl + a_scl;
}

// 0x1f6a0d0
void cmpAddEffScl(f32 a_scl) {
  cmpModelEffScl = cmpModelEffScl + a_scl;
}

// 0x1f6a140
void cmpClrRot(void) {
  *(u64 *)&cmpModelRot.x = 0;
  cmpModelRot.z = 0.0;
  return;
}

// 0x1f6a1d0
void cmpClearDat(void) {
  *(u64 *)&cmpModelPos.x = 0;
  *(u64 *)&cmpModelRot.x = 0;
  cmpModelPos.z = 0.0;
  cmpModelRot.z = 0.0;
  *(u64 *)&cmpModelScl = 0;
  return;
}

// 0x1f6a2d0
void cmpSetBstID(BST a_bstID) {
  g_bstID = a_bstID;
  return;
}

// 0x1f6a360
s8 cmpDrawStatusModel(sdfModelOt_t *pModelOt) {
  s8 Stat;
  dds3ModelHandle_t *v11;
  u32 MotionNum;
  s32 v15;
  dds3ModelHandle_t *v18;
  dds3ModelHandle_t *v20;
  dds3ModelHandle_t *v23;
  f32 HokanFrame_NakamaMotion;
  dds3ModelHandle_t *v35;
  dds3ModelHandle_t *v38;
  s32 MotionFrame;
  s32 SetMotionFrame;
  u32 v42;
  dds3ModelHandle_t *v43;
  dds3ModelHandle_t *v47;
  dds3ModelHandle_t *v50;
  dds3ModelHandle_t *v51;

  Stat = cmpChkStatusModelLoadStat();
  if (Stat == 1)
    return Stat;
  goto LABEL_9;
LABEL_10:
  if (!cmpModelHandle)
    return Stat;
  cmpSetModelPosition(cmpModelHandle);
  cmpSetModelRotate(cmpModelHandle);
  cmpSetModelScale(cmpModelHandle, 0);
  v11 = cmpModelHandle;
  MotionNum = mdlGetMotionNum(v11, 0);
  if (gMajorNo == 1)
  {
    if (MotionNum < 3)
    {
LABEL_32:
      v15 = 0;
LABEL_40:
      v23 = cmpModelHandle;
      if (!(v15 | mdlChkMotionEnd(v23)))
        goto LABEL_73;
      if (cmpGetFlagDebug())
        goto LABEL_73;
      if (g_defMotNo < 0)
        goto LABEL_73;
      g_smoothLeng = 20.0;
      if (gMinorNo == 104)
        goto LABEL_57;
      if (gMinorNo == 154)
        goto LABEL_57;
      if (gMinorNo == 159)
      {
LABEL_57:
        HokanFrame_NakamaMotion = 6.0;
      }
      else
      {
        v51 = cmpModelHandle;
        HokanFrame_NakamaMotion = fldGetHokanFrame_NakamaMotion(v51, gMinorNo, g_defMotNo, 3);
        if (HokanFrame_NakamaMotion >= 10.0)
          goto LABEL_60;
      }
      g_smoothLeng = HokanFrame_NakamaMotion;
LABEL_60:
      if (g_smoothLeng > 0.0)
      {
        cmpSetSmoothLoopMotion(g_defMotNo, g_beforeLeng, g_smoothLeng);
        goto LABEL_73;
      }
      cmpSetLoopMotion(g_defMotNo);
LABEL_73:
      cmpSetStatusModelParam();
      v35 = cmpModelHandle;
      mdlSetLight(v35, g_pLightPacket);
      if (cmpGetFlagScreenShot())
      {
        v38 = cmpModelHandle;
        MotionFrame = mdlGetMotionFrame(v38);
        SetMotionFrame = cmpGetSetMotionFrame();
        if (MotionFrame == SetMotionFrame)
        {
          v43 = *((dds3ModelHandle_t *)*((const MethodInfo *)cmpModel + 2).virtualMethodPointer + 2);
          mdlMotionPause(v43);
        }
        else
        {
          if (!v42)
          cmpSetMotionSpeed(1.0);
          v50 = cmpModelHandle;
          mdlMotionPauseOff(v50);
          v47 = cmpModelHandle;
          goto LABEL_95;
        }
LABEL_94:
        v47 = cmpModelHandle;
LABEL_95:
        Link(v47, pModelOt);
        cmpDrawBstEff();
        return Stat;
      }
      goto LABEL_94;
    }
  }
  else
  {
    v15 = 0;
    if (gMajorNo != 7 || MotionNum < 3)
    {
LABEL_39:
      goto LABEL_40;
    }
  }
  v18 = cmpModelHandle;
  if (mdlGetMotionFrameF(v18) > 5.0)
    goto LABEL_29;
LABEL_38:
  v15 = 0;
  goto LABEL_39;
  if (mdlGetMotionFrameF(v18) > 5.0)
  {
LABEL_29:
    v20 = cmpModelHandle;
    if (mdlGetMotionNormalAnimator(v20) < 1.0)
      goto LABEL_32;
    v15 = 1;
    goto LABEL_40;
  }
  goto LABEL_38;
LABEL_9:
  goto LABEL_10;
}

// 0x1f6aa50
s8 cmpGetViewerLimit(void) {
  return gViewerLimit;
}

// 0x1f6aad0
void cmpSetViewerLimit(s8 a_bool) {
  gViewerLimit = a_bool;
  return;
}

// 0x1f6ab60
s8 cmpGetPosLimit(void) {
  return gPosLimit;
}

// 0x1f6abe0
void cmpSetPosLimit(s8 a_bool) {
  gPosLimit = a_bool;
  return;
}

// 0x1f6ac70
void cmpSetLightDef(void) {
  g_lightNo = -1;
  return;
}

// 0x1f6ad00
void cmpSetLightDark(void) {
  g_lightNo = 3;
  return;
}

// 0x1f6ad90
void cmpLoadTitleEff(void) {
  void *Asset;
  void *v6;
  void *p_titleUpEff;
  void *v8;

  Asset = LoadAsset(_Ctrl_k__BackingField, "fld_all", "SubTitleUpEff", 0);
  if (!Asset)
  {
    titleUpEff = 0;
    return;
  }
  if (Asset->klass == UnityEngine_GameObject)
    v6 = Asset;
  else
    v6 = 0;
  titleUpEff = v6;
  p_titleUpEff = &titleUpEff;
  if (Asset->klass == UnityEngine_GameObject)
    v8 = Asset;
  else
    v8 = 0;
}

// 0x1f6af10
void cmpInstanceTitleEff(void) {
  void *transform;
  Il2CppObject *v9;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  sdfVector3_t position;
  sdfQuaternion_t rotation;

  HDrawSync = 1;
  backHDrawSync = HDrawSync;
  transform = get_transform(hook, 0);
  v9 = Instantiate_object__39504352(titleUpEff, transform);
  titleUpEffObj = v9;
  v11 = get_transform(titleUpEffObj, 0);
  v12 = get_transform(cmpModelHandle->modelRoot->modelObj, 0);
  position = get_position(v12, 0);
  set_position(v11, position, 0);
  v13 = get_transform(titleUpEffObj, 0);
  v14 = get_transform(cmpModelHandle->modelRoot->modelObj, 0);
  rotation = get_rotation(v14, 0);
  set_rotation(v13, rotation, 0);
}

// 0x1f6b0f0
void cmpDestroyTitleEff(void) {
  HDrawSync = backHDrawSync;
  Destroy_61007920(titleUpEffObj, 0);
  titleUpEffObj = 0;
}

// 0x1f652c0
void cmpLoadEffect(void) {
  fileHandle_t *v1;
  void *topPtr;
  void *data;
  effHandle_t *EPL;
  sdfVector4_t v8;

  v1 = fileLoad("fld_all", "EFF_TES");
  fileSync(v1);
  topPtr = v1->topPtr;
  data = topPtr[1].klass->_1.byval_arg.data;
  EPL = dds3EffectLoadEPL(data);
  g_hEff = EPL;
  fileHandleFree(v1);
  Reset(g_hEff, 0);
  v8.w = 0.0;
  v8.x = 128.0;
  v8.y = -100.0;
  v8.z = 64.0;
  dds3EffectSetPosition(g_hEff, v8);
  dds3EffectSetLoop(g_hEff, 1u);
  dds3EffectSetScale(g_hEff, 1.5);
}

// 0x1f65a10
void cmpDeleteEffect(void) {
  if (!g_hEff)
  {
    goto LABEL_5;
  }
  Delete(g_hEff);
  g_hEff = 0;
LABEL_5:
  if (!op_Inequality(titleUpEff, 0, 0))
    return;
  titleUpEff = 0;
}

// 0x1f6b1f0
void cmpEffectSetRGBA(u32 a_rgba) {
  if (g_hEff)
    goto LABEL_4;
  return;
  if (g_hEff)
  {
LABEL_4:
    dds3EffectSetRGBA(g_hEff, a_rgba);
    return;
  }
}

// 0x1f6b2e0
void cmpDrawEffect(void) {
  if (!g_hEff)
    return;
  cmpSetStatusModelParam();
  OT = 8;
  dds3EffectDraw(g_hEff);
  OT = 12;
}

// 0x1f6b420
void cmpSetGoodByZahyouMode(s32 mode) {
  g_GoodByModeZahyou = mode;
  return;
}

// 0x1f6b4b0
void cmpSetGoodByMode(s32 mode) {
  g_GoodByMode = mode;
  g_GoodByModeZahyou = 0;
}
