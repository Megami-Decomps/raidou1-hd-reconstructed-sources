#include "types.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3kernelcore.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "kernel.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtlcamerar1.h"
#include "sbtlmain.h"
#include "sdf_vu0.h"

typedef struct SBTLCAMERA_WORK SBTLCAMERA_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

static dds3ProcessFunc_t ProcCamera(dds3ProcessID_t *id);
static void ShutdownCamera(dds3ProcessID_t *id);
static bool Backup(SBTLCAMERA_WORK *wk, dds3Basic_t *cm);
static bool Set(SBTLCAMERA_WORK *wk);

// 0x205dbd0
static dds3ProcessFunc_t ProcCamera(dds3ProcessID_t *id) {
  return 0;
}

// 0x205dbe0
static void ShutdownCamera(dds3ProcessID_t *id) {
  ;
}

// 0x205dbf0
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

// 0x205e140
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

// 0x205e6c0
void sBtlCameraCreateCamera(void) {
  SBTLCAMERA_WORK *camera;
  SBTLCAMERA_WORK *camerabk;
  dds3ProcessFunc_t v4;
  shutdownfuncDelegate v5;
  f32 offset_x;
  f32 offset_z;
  u32 v9;
  dds3Basic_t *v10;
  SBTLCAMERA_WORK *v11;
  SBTLCAMERA_WORK *v12;
  SBTLCAMERA_WORK *v14;
  f32 v16;
  f32 v17;
  sdfVector4_t *p_targetpos;
  s32 v20;
  struct sdfVector4_t v21;
  struct sdfVector4_t camerapos;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  s32 v30;
  struct sdfVector4_t v32;
  dds3Basic_t *pBasic;
  dds3ProcessID_t *target;
  sdfVector4_t v38;
  sdfVector4_t v39;

  pBasic = 0;
  target = 0;
  camera = wk->scene->camera;
  camera->cm = 0;
  camerabk = wk->scene->camerabk;
  camerabk->cm = 0;
  v4 = Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_sBtlCameraR1_ProcCamera__, 0);
  v5 = Allocate(shutdownfuncDelegate);
  _ctor(v5, 0, Method_Project_sBtlCameraR1_ShutdownCamera__, 0);
  target = dds3StartProcess("sbtl_cameraproc", 1035, 1, 1, v4, v5, 0);
  offset_x = main_data->offset_x;
  offset_z = main_data->offset_z;
  v9 = dds3SerializeID();
  v38.w = 0.0;
  v38.y = -435.3;
  v39.x = 0.16;
  v39.y = -0.22;
  v39.z = -0.04;
  v39.w = 0.89;
  v38.x = offset_x + -507.7;
  v38.z = offset_z + -973.36;
  pBasic = dds3CameraObjectBasicAddTypeFree(v9, v38, v39);
  dds3SetBasicName(pBasic, "sbtl_scam");
  dds3SetRadiusPoseSet(pBasic, 10.0);
  dds3ObjectBaseCreateMover(pBasic);
  v10 = pBasic;
  v11 = wk->scene->camera;
  v11->cm = pBasic;
  v12 = wk->scene->camera;
  v12->fovy = 0.6981317;
  dds3CameraObjectBasicSetFovy(&v12->cm, 0.6981317);
  Backup(wk->scene->camera, pBasic);
  v14 = wk->scene->camera;
  v16 = offset_x + 0.0;
  v17 = offset_z + 0.0;
  vct_A.x = v16;
  vct_A.y = 0.0;
  vct_A.z = v17;
  vct_A.w = 0.0;
  p_targetpos = &v14->targetpos;
  v20 = (u8)byte_5755EF5;
  *p_targetpos = vct_A;
  v21 = *p_targetpos;
  if (v20)
    goto LABEL_17;
  goto LABEL_34;
  if (v30)
  {
LABEL_17:
    goto LABEL_18;
  }
LABEL_34:
  v32 = v21;
  v21 = v32;
LABEL_18:
  vct_A = v21;
  camerapos = v14->camerapos;
  vct_B = camerapos;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v14->distance = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
  sub_1949110(0);
  v14->direction = vct_A;
  dds3LinkProcess(&wk->MProc_ID, target);
}

// 0x205ed60
bool sBtlCameraProc(void) {
  sBtlCameraSetPara(wk->scene->camera);
  return 1;
}

// 0x205edd0
bool sBtlCameraSetPara(SBTLCAMERA_WORK *wk) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v4;
  void *workdata;
  SBATTLE_WORK *v8;
  SBTLSCENE_WORK *v9;
  SBTLSCENE_WORK *scene;
  sdfVector4_t *v13;
  f32 distance;
  f32 v15;
  struct sdfVector4_t targetpos;
  sdfVector4_t *v17;
  s32 v18;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *v26;
  f32 fovy;
  s32 v31;
  u32 status4;
  SBATTLE_WORK *v34;
  struct sdfVector4_t direction;
  sdfVector4_t v39;
  sdfVector4_t v40;

  PChara = sBtlGetPChara();
  v4 = PChara;
  workdata = wk->cm->workdata;
  if (PChara)
  {
    if (wk->mode)
      goto LABEL_21;
    v8 = wk;
    if ((v8->status & 0x8000) == 0)
      goto LABEL_14;
    goto LABEL_9000;
    if ((v8->status & 0x8000) == 0)
    {
LABEL_14:
      scene = wk->scene;
      ++scene->camCnt;
      goto LABEL_17;
    }
LABEL_9000:
    v9 = v8->scene;
    if (v9->camCnt < 21)
      goto LABEL_14;
    ++v9->camCnt2;
    status4 = v8->status4;
    if ((status4 & 0x80) != 0)
    {
      goto LABEL_72;
    }
    v8 = wk;
    status4 = v8->status4;
    v8->status4 = status4 | 0x80;
    sBtlNakamaSetUp(0);
    sBtlNakamaSetUp(1);
LABEL_72:
    v34 = wk;
    if ((v34->status4 & 0x80) == 0)
      goto LABEL_17;
    v34 = wk;
    if (v34->scene->camCnt2 >= 17)
    {
      v34 = wk;
      v34->step = 1;
    }
LABEL_17:
    sBtlBossStartSub(wk);
    if (!wk->bBfrBtlEnd)
      goto LABEL_21;
    goto LABEL_20;
    if (!wk->bBfrBtlEnd)
    {
LABEL_21:
      direction = wk->direction;
      vct_A = direction;
      v13 = &workdata[5];
      *v13 = vct_A;
      distance = wk->distance;
      v15 = -distance;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v15);
      targetpos = wk->targetpos;
      vct_B = targetpos;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v17 = &workdata[7];
      v18 = (u8)byte_5755EF6;
      *v17 = vct_B;
      if (v18)
        goto LABEL_35;
      goto LABEL_58;
      if (v31)
      {
LABEL_35:
        goto LABEL_36;
      }
LABEL_58:
LABEL_36:
      p_x = &vf00.x;
      x = p_x[4];
      y = p_x[5];
      z = p_x[6];
      w = p_x[7];
      v39.x = x;
      v39.y = y;
      v39.z = z;
      v39.w = w;
      dds3SetPosPoseSet(&wk->cm, v39);
      v40.w = 1.0;
      v40.x = 0.0;
      v40.y = 0.0;
      v40.z = 0.0;
      dds3SetRotPoseSet(&wk->cm, v40);
      vct_A = (struct sdfVector4_t)xmmword_3D05530;
      v26 = workdata + 6;
      *v26 = (struct Project_Basic_dds3Basic_t_WORK_o)vct_A;
      fovy = wk->fovy;
      dds3CameraObjectBasicSetFovy(&wk->cm, fovy);
      HIDWORD(workdata[9].monitor) |= 1u;
      return v4 != 0;
    }
LABEL_20:
    wk->modeOld = 2;
    goto LABEL_21;
  }
  return v4 != 0;
}
