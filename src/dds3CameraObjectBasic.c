#include "types.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct CamOffset CamOffset;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;

dds3BasicFunction_t *Function;

static bool Constructor(dds3Basic_t *pBasic);
static void Destructor(dds3Basic_t *pBasic);
static bool Mainprocuder(dds3Basic_t *pBasic);
static bool Drawprocuder(dds3Basic_t *pBasic);

// 0x22f3460
static bool Constructor(dds3Basic_t *pBasic) {
  Il2CppObject *v3;
  void *p_workdata;
  void *v5;
  dds3ObjectBaseControlWorkData_t *inited;
  void *v8;
  dds3Basic_t *basic;

  basic = pBasic;
  dds3InitPoseSet(basic);
  v3 = Allocate(dds3CameraObjectBasicWorkData_t);
  _ctor(v3, 0);
  pBasic->workdata = (void *)v3;
  p_workdata = &pBasic->workdata;
  v5 = p_workdata;
  inited = dds3ObjectBaseInitControlWorkData(basic);
  v5[9].klass = (Project_Basic_dds3Basic_t_WORK_c *)inited;
  v8 = v5 + 9;
  dds3ObjectBaseOnFlag(basic, 0x62u);
  HIDWORD(v8->monitor) = 0;
  return 1;
}

// 0x22f3580
static void Destructor(dds3Basic_t *pBasic) {
  dds3PoseSet_t *p_poseset;
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;

  if (pBasic)
  {
    p_poseset = &pBasic->poseset;
    if (pBasic->poseset)
    {
      p_poseset = 0;
    }
  }
  workdata = pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(dds3CameraObjectBasicWorkData_t **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != dds3CameraObjectBasicWorkData_t;
    dds3ObjectBaseFreeControlWorkData(workdata + 18);
  }
}

// 0x22f3670
static bool Mainprocuder(dds3Basic_t *pBasic) {
  void *workdata;
  dds3PoseSet_t *poseset;
  u32 flag;
  struct sdfVector4_t scl;
  struct sdfVector4_t rot;
  struct sdfVector4_t pos;
  f32 v14;
  dds3Basic_t *ControlScene;
  dds3Basic_t *pBasica;

  pBasica = pBasic;
  workdata = pBasic->workdata;
  poseset = pBasic->poseset;
  ControlScene = 0;
  flag = poseset->flag;
  if ((flag & 1) == 0)
  {
    goto LABEL_9;
  }
  flag = poseset->flag;
  poseset->flag = flag & 0xFFFFFFFE;
  MakeCamera(pBasica);
  scl = poseset->scl;
  poseset->workscl = scl;
  rot = poseset->rot;
  poseset->workpos = poseset->pos;
  poseset->workrot = rot;
LABEL_9:
  ControlScene = dds3GetControlScene();
  if (!ControlScene)
    return 1;
  if (dds3SceneBasicGetActiveCamera(ControlScene) != pBasic)
    return 1;
  pos = poseset->pos;
  CameraEyePos = pos;
  CameraTargetPos = (struct sdfVector4_t)workdata[7];
  CameraUpVector = (struct sdfVector4_t)workdata[8];
  if ((BYTE4(workdata[9].monitor) & 1) != 0)
  {
    v14 = *(f32 *)&workdata[10].klass;
    dds3SetScreenFovy(v14);
    HIDWORD(workdata[9].monitor) &= ~1u;
  }
  return 1;
}

// 0x22f3ff0
static bool Drawprocuder(dds3Basic_t *pBasic) {
  return 1;
}

// 0x22f3990
void MakeCamera(dds3Basic_t *pBasic) {
  dds3Basic_t *v3;
  void *workdata;
  dds3PoseSet_t *poseset;
  struct sdfVector4_t v8;
  sdfVector4_t *v11;
  s32 monitor;
  struct sdfVector4_t pos;
  sdfVector4_t *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  u32 klass;
  u32 klass_high;
  u32 v27;
  u32 monitor_high;
  void *static_fields;
  struct Project_Basic_dds3Basic_t_WORK_o v31;
  struct Project_Basic_dds3Basic_t_WORK_o v32;
  struct Project_Basic_dds3Basic_t_WORK_o v33;
  f32 v34;
  f32 v35;
  f32 v36;
  struct sdfVector4_t rot;
  struct sdfVector4_t v38;
  f32 v39;
  sdfMatrix4_t v44;
  sdfMatrix4_t v45;
  sdfVector4_t v46;
  sdfVector4_t v47;
  sdfVector4_t v49;

  v3 = pBasic;
  workdata = pBasic->workdata;
  poseset = v3->poseset;
  rot = poseset->rot;
  vct_A = rot;
  ToMatrix();
  v8 = (struct sdfVector4_t)workdata[6];
  vct_A = v8;
  get_transpose(&v45, &mtx_A, 0);
  v44 = v45;
  v46 = op_Multiply_60923920(&v44, vct_A, 0);
  vct_A = v46;
  vct_A.w = 1.0;
  v11 = &workdata[8];
  monitor = workdata[9].monitor;
  *v11 = vct_A;
  if (monitor == 1)
  {
    v38 = (struct sdfVector4_t)workdata[5];
    vct_A = v38;
    get_transpose(&v45, &mtx_A, 0);
    v49 = vct_A;
    v44 = v45;
    v47 = op_Multiply_60923920(&v44, v49, 0);
    vct_A = v47;
    pos = poseset->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    vct_A.w = 1.0;
    v16 = &workdata[7];
    *v16 = vct_A;
  }
  v17 = *(f32 *)&workdata[7].klass;
  v18 = *((f32 *)&workdata[7].klass + 1);
  v19 = *(f32 *)&workdata[7].monitor;
  v20 = *((f32 *)&workdata[7].monitor + 1);
  x = poseset->pos.x;
  y = poseset->pos.y;
  z = poseset->pos.z;
  w = poseset->pos.w;
  klass = workdata[8].klass;
  klass_high = HIDWORD(workdata[8].klass);
  v27 = workdata[8].monitor;
  monitor_high = HIDWORD(workdata[8].monitor);
  v36 = *((f32 *)&workdata[7].klass + 1);
  v39 = *(f32 *)&workdata[7].klass;
  v34 = *((f32 *)&workdata[7].monitor + 1);
  v35 = *(f32 *)&workdata[7].monitor;
  v20 = v34;
  v19 = v35;
  v18 = v36;
  v17 = v39;
  sub_1B33630(0, v17, v18, v19, v20, x, y, z, w, COERCE_DOUBLE(__PAIR64__(klass_high, klass)), COERCE_DOUBLE(__PAIR64__(monitor_high, v27)));
  v31 = static_fields[5];
  v32 = static_fields[6];
  v33 = static_fields[7];
  workdata[1] = static_fields[4];
  workdata[2] = v31;
  workdata[3] = v32;
  workdata[4] = v33;
}

// 0x22f4000
dds3ObjectBaseControlWorkData_t *dds3CameraObjectBasicGetControlWorkData(dds3Basic_t *pBasic) {
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;

  workdata = (dds3ObjectBaseControlWorkData_t *)pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(dds3CameraObjectBasicWorkData_t **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != dds3CameraObjectBasicWorkData_t;
  }
  return workdata[18];
}

// 0x22f4080
dds3Basic_t *dds3CameraObjectBasicAddDef(u32 serialID) {
  dds3Basic_t *pObjectBasic;

  pObjectBasic = dds3SceneBasicAdd(4);
  pObjectBasic->serialID = serialID;
  dds3ObjectBaseCreateMover(pObjectBasic);
  return pObjectBasic;
}

// 0x22f4100
dds3Basic_t *dds3CameraObjectBasicAddTypeFree(u32 serialID, const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  dds3Basic_t *v16;
  void *workdata;
  f32 *poseset;
  dds3PoseSet_t *v22;
  struct sdfVector4_t scl;
  struct sdfVector4_t v26;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v28;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v8 = pos->w;
  v9 = pos->z;
  v10 = pos->y;
  v11 = pos->x;
  pObjectBasic = dds3SceneBasicAdd(4);
  pObjectBasic->serialID = serialID;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v16 = pObjectBasic;
  workdata = pObjectBasic->workdata;
  LODWORD(workdata[9].monitor) = 1;
  LODWORD(workdata[10].klass) = 1059117436;
  poseset = v16->poseset;
  *((u32 *)poseset + 52) = (u32)poseset[52] & 0xFFFFFFFC | 1;
  v28.x = v11;
  v28.y = v10;
  v28.z = v9;
  v28.w = v8;
  poseset[24] = x;
  poseset[25] = y;
  poseset[26] = z;
  poseset[27] = w;
  dds3SetPosPoseSet(pObjectBasic, v28);
  v22 = v16->poseset;
  scl = v22->scl;
  v26 = v22->scl;
  scl = v26;
  v22->workscl = scl;
  v16->poseset->workrot = v16->poseset->rot;
  v16->poseset->workpos = v16->poseset->pos;
  workdata[5] = (struct Project_Basic_dds3Basic_t_WORK_o)xmmword_3CF97A0;
  workdata[6] = (struct Project_Basic_dds3Basic_t_WORK_o)xmmword_3D015F0;
  MakeCamera(pObjectBasic);
  return v16;
}

// 0x22f43e0
dds3Basic_t *dds3CameraObjectBasicAddTypeLookAt(u32 serialID, const sdfVector4_t *eyePos, const sdfVector4_t *targetPos, const sdfVector4_t *vertical) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  dds3Basic_t *v17;
  void *workdata;
  dds3PoseSet_t *poseset;
  struct sdfVector4_t scl;
  struct sdfVector4_t v25;
  dds3Basic_t *pObjectBasic;
  Project_Basic_dds3Basic_t_WORK_c *v27;
  void *v28;
  sdfVector4_t v29;

  w = targetPos->w;
  z = targetPos->z;
  y = targetPos->y;
  x = targetPos->x;
  v9 = eyePos->w;
  v10 = eyePos->z;
  v11 = eyePos->y;
  v12 = eyePos->x;
  pObjectBasic = dds3SceneBasicAdd(4);
  pObjectBasic->serialID = serialID;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v17 = pObjectBasic;
  workdata = pObjectBasic->workdata;
  LODWORD(workdata[9].monitor) = 0;
  LODWORD(workdata[10].klass) = 1059117436;
  v29.x = v12;
  v29.y = v11;
  v29.z = v10;
  v29.w = v9;
  dds3SetPosPoseSet(pObjectBasic, v29);
  poseset = v17->poseset;
  scl = poseset->scl;
  v25 = poseset->scl;
  scl = v25;
  poseset->workscl = scl;
  v17->poseset->workrot = v17->poseset->rot;
  v17->poseset->workpos = v17->poseset->pos;
  workdata[6].klass = v27;
  workdata[6].monitor = v28;
  *(f32 *)&workdata[7].klass = x;
  *((f32 *)&workdata[7].klass + 1) = y;
  *(f32 *)&workdata[7].monitor = z;
  *((f32 *)&workdata[7].monitor + 1) = w;
  MakeCamera(pObjectBasic);
  return v17;
}

// 0x22f4660
dds3Basic_t *dds3CameraObjectBasicAdd(u32 serialID, const sdfVector4_t *eyePos, const sdfVector4_t *eyeVector, const sdfVector4_t *vertical, f32 fovy, u32 mode) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  dds3Basic_t *v20;
  void *workdata;
  dds3PoseSet_t *poseset;
  struct sdfVector4_t scl;
  struct sdfVector4_t v29;
  dds3Basic_t *pObjectBasic;
  void *v31;
  s32 v32;
  sdfVector4_t v33;

  w = eyeVector->w;
  z = eyeVector->z;
  y = eyeVector->y;
  x = eyeVector->x;
  v11 = eyePos->w;
  v12 = eyePos->z;
  v13 = eyePos->y;
  v14 = eyePos->x;
  v15 = vertical->x;
  pObjectBasic = dds3SceneBasicAdd(4);
  pObjectBasic->serialID = serialID;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v20 = pObjectBasic;
  workdata = pObjectBasic->workdata;
  *(f32 *)&workdata[9].monitor = v15;
  LODWORD(workdata[10].klass) = v32;
  v33.x = v14;
  v33.y = v13;
  v33.z = v12;
  v33.w = v11;
  dds3SetPosPoseSet(pObjectBasic, v33);
  poseset = v20->poseset;
  scl = poseset->scl;
  v29 = poseset->scl;
  scl = v29;
  poseset->workscl = scl;
  v20->poseset->workrot = v20->poseset->rot;
  v20->poseset->workpos = v20->poseset->pos;
  workdata[6].klass = *(Project_Basic_dds3Basic_t_WORK_c **)&fovy;
  workdata[6].monitor = v31;
  *(f32 *)&workdata[5].klass = x;
  *((f32 *)&workdata[5].klass + 1) = y;
  *(f32 *)&workdata[5].monitor = z;
  *((f32 *)&workdata[5].monitor + 1) = w;
  if (v15 == 0.0)
  {
    *(f32 *)&workdata[7].klass = x;
    *((f32 *)&workdata[7].klass + 1) = y;
    *(f32 *)&workdata[7].monitor = z;
    *((f32 *)&workdata[7].monitor + 1) = w;
  }
  MakeCamera(pObjectBasic);
  return v20;
}

// 0x22f4950
void dds3CameraObjectBasicDelete(dds3Basic_t *pBasic) {
  dds3SceneBasicDelete(pBasic);
}

// 0x22f49e0
void dds3CameraObjectBasicGetCameraTM(dds3Basic_t *pBasic) {
  void *workdata;
  void *v5;
  _OWORD *p_x;
  struct Project_Basic_dds3Basic_t_WORK_o v8;
  struct Project_Basic_dds3Basic_t_WORK_o v9;
  struct Project_Basic_dds3Basic_t_WORK_o v10;
  struct Project_Basic_dds3Basic_t_WORK_o v11;

  workdata = pBasic->workdata;
  v5 = workdata + 1;
  v8 = *v5;
  v9 = v5[1];
  v10 = v5[2];
  v11 = v5[3];
  p_x = &vf00.x;
  p_x[4] = v8;
  p_x[5] = v9;
  p_x[6] = v10;
  p_x[7] = v11;
}

// 0x22f4b10
void dds3CameraObjectBasicSetTargetPos(dds3Basic_t *pBasic, const sdfVector4_t *targetPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  void *workdata;

  w = targetPos->w;
  z = targetPos->z;
  y = targetPos->y;
  x = targetPos->x;
  workdata = pBasic->workdata;
  *(f32 *)&workdata[7].monitor = z;
  *((f32 *)&workdata[7].monitor + 1) = w;
  *(f32 *)&workdata[7].klass = x;
  *((f32 *)&workdata[7].klass + 1) = y;
}

// 0x22f4be0
void dds3CameraObjectBasicGetTargetPos(dds3Basic_t *pBasic) {
  void *workdata;
  struct sdfVector4_t v6;

  workdata = pBasic->workdata;
  v6 = (struct sdfVector4_t)workdata[7];
  vct_A = v6;
}

// 0x22f4cf0
void dds3CameraObjectBasicSetFovy(dds3Basic_t *pBasic, f32 fovy) {
  void *workdata;
  s32 monitor_high;

  workdata = pBasic->workdata;
  monitor_high = HIDWORD(workdata[9].monitor);
  *(f32 *)&workdata[10].klass = fovy;
  HIDWORD(workdata[9].monitor) = monitor_high | 1;
}

// 0x22f4d90
f32 dds3CameraObjectBasicGetFovy(dds3Basic_t *pBasic) {
  f32 *workdata;

  workdata = pBasic->workdata;
  return workdata[40];
}

// 0x22f4e20
void dds3CameraObjectBasicGetTgtCam(dds3Basic_t *pBasic, sdfVector4_t *tgtpos, sdfVector4_t *campos) {
  dds3Basic_t *v7;
  void *workdata;
  dds3PoseSet_t *poseset;
  struct sdfVector4_t v12;
  sdfVector4_t *v15;
  s32 monitor;
  s32 v17;
  struct sdfVector4_t pos;
  sdfVector4_t *v21;
  struct sdfVector4_t rot;
  struct sdfVector4_t v25;
  sdfMatrix4_t v28;
  sdfMatrix4_t v29;
  sdfVector4_t v30;
  sdfVector4_t v31;
  sdfVector4_t v33;

  v7 = pBasic;
  if (pBasic)
  {
    workdata = v7->workdata;
    poseset = v7->poseset;
    rot = poseset->rot;
    vct_A = rot;
    ToMatrix();
    v12 = (struct sdfVector4_t)workdata[6];
    vct_A = v12;
    get_transpose(&v29, &mtx_A, 0);
    v28 = v29;
    v30 = op_Multiply_60923920(&v28, vct_A, 0);
    vct_A = v30;
    vct_A.w = 1.0;
    v15 = &workdata[8];
    monitor = workdata[9].monitor;
    *v15 = vct_A;
    if (monitor != 1)
      goto LABEL_45;
    goto LABEL_31;
    if (v17 != 1)
    {
LABEL_45:
      *tgtpos = (sdfVector4_t)workdata[7];
      *campos = poseset->pos;
      return;
    }
LABEL_31:
    v25 = (struct sdfVector4_t)workdata[5];
    vct_A = v25;
    get_transpose(&v29, &mtx_A, 0);
    v33 = vct_A;
    v28 = v29;
    v31 = op_Multiply_60923920(&v28, v33, 0);
    vct_A = v31;
    pos = poseset->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    vct_A.w = 1.0;
    v21 = &workdata[7];
    *v21 = vct_A;
    goto LABEL_45;
  }
}

// 0x22f53b0
u32 dds3CameraObjectBasicGetMode(dds3Basic_t *pBasic) {
  u32 *workdata;

  workdata = pBasic->workdata;
  return workdata[38];
}

// 0x22f5440
void dds3CameraObjectBasicAlterMode(dds3Basic_t *pBasic, u32 mode) {
  void *workdata;

  workdata = pBasic->workdata;
  if (LODWORD(workdata[9].monitor) != mode)
    LODWORD(workdata[9].monitor) = mode;
}

// 0x22f54e0
void dds3CameraObjectBasicSetTgtCam(dds3Basic_t *pBasic, const sdfVector4_t *tgtpos, const sdfVector4_t *campos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  void *workdata;
  dds3Basic_t *pBasica;
  sdfVector4_t v18;

  pBasica = pBasic;
  w = campos->w;
  z = campos->z;
  y = campos->y;
  x = campos->x;
  v8 = tgtpos->w;
  v9 = tgtpos->z;
  v10 = tgtpos->y;
  v11 = tgtpos->x;
  workdata = pBasic->workdata;
  if (!workdata)
    goto LABEL_11;
  goto LABEL_9;
  if (!workdata)
LABEL_9:
LABEL_11:
  *(f32 *)&workdata[7].klass = v11;
  *((f32 *)&workdata[7].klass + 1) = v10;
  *(f32 *)&workdata[7].monitor = v9;
  *((f32 *)&workdata[7].monitor + 1) = v8;
  v18.x = x;
  v18.y = y;
  v18.z = z;
  v18.w = w;
  dds3SetPosPoseSet(pBasica, v18);
  (pBasic->basicfunction->mainprocuder->invoke_impl)(pBasic->basicfunction->mainprocuder->method_code, pBasic, pBasic->basicfunction->mainprocuder->method);
}

// 0x22f56a0
bool dds3CameraObjectBasicFourceCalc(dds3Basic_t *pBasic, CamOffset *cof) {
  CamOffset *v3;
  void *workdata;
  void *v6;
  void *p_workdata;
  struct Project_Basic_dds3Basic_t_WORK_o v11;
  f32 v12;
  f32 v13;
  __int128 v15;
  f32 v16;
  f32 v20;
  dds3Basic_t *pBasica;

  v3 = cof;
  pBasica = pBasic;
  p_workdata = &pBasic->workdata;
  workdata = pBasic->workdata;
  v6 = p_workdata[1];
  if (v3)
  {
    workdata[7] = (struct Project_Basic_dds3Basic_t_WORK_o)v3->tpos;
    v6[5] = (struct Project_Basic_dds3Basic_t_WORK_o)v3->cpos;
  }
  MakeCamera(pBasica);
  v11 = v6[7];
  v6[11] = v11;
  v12 = *(f32 *)&v6[5].klass;
  v13 = *((f32 *)&v6[5].klass + 1);
  v6[10].monitor = v6[6].monitor;
  v15 = *(_OWORD *)&v6[5].monitor;
  *(f32 *)&v6[9].klass = v12;
  *((f32 *)&v6[9].klass + 1) = v13;
  *(_OWORD *)&v6[9].monitor = v15;
  v16 = *((f32 *)&v15 + 1);
  CameraEyePos.x = v12;
  CameraEyePos.y = v13;
  LODWORD(CameraEyePos.z) = v15;
  CameraEyePos.w = v16;
  CameraTargetPos = (struct sdfVector4_t)workdata[7];
  CameraUpVector = (struct sdfVector4_t)workdata[8];
  if ((BYTE4(workdata[9].monitor) & 1) != 0)
  {
    v20 = *(f32 *)&workdata[10].klass;
    dds3SetScreenFovy(v20);
    HIDWORD(workdata[9].monitor) &= ~1u;
  }
  return 1;
}
