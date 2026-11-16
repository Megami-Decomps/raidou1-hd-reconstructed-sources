#include "types.h"
#include "basic.h"
#include "dds3.h"
#include "dds3basic.h"
#include "dds3lightobjectbasic.h"
#include "dds3moverbasic.h"
#include "dds3objectbase.h"
#include "dds3pathbasic.h"
#include "dds3scenebasic.h"
#include "sdf_vu0.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;

dds3BasicFunction_t *Function;
s32 movername;
char *movernamestr;

static bool Constructor(dds3Basic_t *pBasic);
static void Destructor(dds3Basic_t *pBasic);
static bool Mainprocuder(dds3Basic_t *pBasic);

// 0x22fdc70
static bool Constructor(dds3Basic_t *pBasic) {
  void *v3;
  void *p_workdata;
  void *v6;

  v3 = Allocate(Project_Basic_dds3MoverBasicWorkData_t);
  _ctor(v3, 0);
  pBasic->workdata = v3;
  p_workdata = &pBasic->workdata;
  v6 = p_workdata;
  Clear(v6);
  return 1;
}

// 0x22fddd0
static void Destructor(dds3Basic_t *pBasic) {
  dds3Basic_t *workdata;
  s64 naturalAligment;
  dds3Basic_t *pItemBasic;

  workdata = pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].next) < (u32)naturalAligment || *((Project_Basic_dds3MoverBasicWorkData_t_c **)(workdata)[1].worknext + naturalAligment - 1) != Project_Basic_dds3MoverBasicWorkData_t;
    dds3MoverBasicFreePath(pBasic);
    pItemBasic = 0;
    dds3ObjectBaseSetControlBasicType(workdata + 2, pItemBasic, 1u);
  }
}

// 0x22fe040
static bool Mainprocuder(dds3Basic_t *pBasic) {
  fldResourceLightPath_t *v3;
  void *workdata;
  s64 naturalAligment;
  u8 *monitor;
  dds3PathBasicControl_t *p_monitor;
  dds3Basic_t *klass;
  f32 *p_x;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 *v16;
  s64 v17;
  u32 flag;
  f32 *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 Fovy;
  dds3PoseSet_t *poseset;
  Project_Basic_dds3Basic_t_WORK_c *v29;
  dds3PoseSet_t *v30;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s64 v36;
  dds3Basic_t *v37;
  s64 v38;
  dds3PathBasicControl_t *v40;
  u32 v41;
  s32 mode;
  f32 frame;
  f32 v44;
  f32 frameMax;
  dds3PoseSet_t *v47;
  fldResourceLightPath_t *resource;
  dds3Basic_t *pBasica;
  sdfVector4_t v50;
  sdfVector4_t v51;
  sdfVector4_t v52;

  pBasica = 0;
  v47 = 0;
  v3 = Allocate(fldResourceLightPath_t);
  _ctor(v3, 0);
  workdata = pBasic->workdata;
  resource = v3;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != Project_Basic_dds3MoverBasicWorkData_t)
    {
LABEL_82:
    }
  }
  p_monitor = &workdata[1].monitor;
  monitor = workdata[1].monitor;
  klass = workdata[1].klass;
  pBasica = klass;
  if (!monitor)
  {
    poseset = klass->poseset;
    if (poseset)
    {
      poseset->frameFall = 0.0;
      v29 = workdata[2].klass;
      if (v29)
      {
        v30 = Allocate(dds3PoseSet_t);
        _ctor(v30, 0);
        v47 = v30;
        dds3InitPoseSetValue(v47);
        if (((v29->_1.namespaze)(v29->_1.element_class, v47, pBasica, *(u64 *)&v29->_1.byval_arg.bits) & 1) != 0)
        {
          x = v47->scl.x;
          y = v47->scl.y;
          z = v47->scl.z;
          w = v47->scl.w;
          v52.x = x;
          v52.y = y;
          v52.z = z;
          v52.w = w;
          dds3AddSclPoseSet(pBasica, v52);
          dds3AddRotPoseSet(pBasica, v47->rot);
          dds3AddPosPoseSet(pBasica, v47->pos);
        }
      }
    }
    return 1;
  }
  if ((monitor[20] & 1) != 0)
  {
    dds3PathBasicControlGetPos(p_monitor);
    p_x = &vf00.x;
    v12 = p_x[4];
    v13 = p_x[5];
    v15 = p_x[6];
    v14 = p_x[7];
    v50.x = v12;
    v50.y = v13;
    v50.z = v15;
    v50.w = v14;
    dds3SetPosPoseSet(pBasica, v50);
    if (GETBASICTYPEL(pBasica) == 6)
    {
      v16 = pBasica->workdata;
      if (v16)
      {
        if (*(u8 *)(*(u64 *)v16 + 304) < (u32)v17 || *(Project_Basic_dds3MatterObjectBasicWorkData_t_c **)(*(u64 *)(*(u64 *)v16 + 200) + 8 * v17 - 8) != Project_Basic_dds3MatterObjectBasicWorkData_t)
        {
          goto LABEL_83;
        }
      }
      v16[13] = v12;
      v16[14] = v13;
      v16[15] = v15;
      v16[16] = v14;
    }
  }
  flag = p_monitor->flag;
  if ((flag & 2) != 0)
  {
    dds3PathBasicControlGetRot(p_monitor);
    v20 = &vf00.x;
    v21 = v20[4];
    v22 = v20[5];
    v24 = v20[6];
    v23 = v20[7];
    v51.x = v21;
    v51.y = v22;
    v51.z = v24;
    v51.w = v23;
    dds3SetRotPoseSet(pBasica, v51);
    flag = p_monitor->flag;
  }
  if ((flag & 4) == 0 || GETBASICTYPEL(pBasica) != 4)
    goto LABEL_58;
  v16 = pBasica->workdata;
  Fovy = dds3PathBasicControlGetFovy(p_monitor);
  if (!v16)
    goto LABEL_54;
  if (*(u8 *)(*(u64 *)v16 + 304) < (u32)v36 || *(dds3CameraObjectBasicWorkData_t **)(*(u64 *)(*(u64 *)v16 + 200) + 8 * v36 - 8) != dds3CameraObjectBasicWorkData_t)
  {
LABEL_83:
  }
LABEL_54:
  v37 = pBasica;
  v16[40] = Fovy;
  workdata = v37->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)v38 || workdata->klass->_2.typeHierarchy[v38 - 1] != dds3CameraObjectBasicWorkData_t)
    {
      goto LABEL_82;
    }
  }
  HIDWORD(workdata[9].monitor) |= 1u;
LABEL_58:
  if ((p_monitor->flag & 0x10) != 0 && GETBASICTYPEL(pBasica) == 9)
  {
    dds3PathBasicControlGetLight(p_monitor, resource);
    dds3SetLightObjectPathResoruce(pBasica, v3);
  }
  v40 = p_monitor;
  v41 = v40->flag;
  if ((v41 & 8) != 0)
    return 1;
  mode = v40->mode;
  if (mode == 1)
  {
    frame = v40->frame;
    if (frame <= 0.0)
    {
      if ((v41 & 0x20) == 0)
        return 1;
      frameMax = v40->frameMax;
      goto LABEL_76;
    }
    v44 = -1.0;
LABEL_75:
    frameMax = frame + v44;
LABEL_76:
    v40->frame = frameMax;
    return 1;
  }
  if (!mode)
  {
    frame = v40->frame;
    if (v40->frameMax > frame)
    {
      v44 = 1.0;
      goto LABEL_75;
    }
    if ((v41 & 0x20) != 0)
      v40->frame = 0.0;
  }
  return 1;
}

// 0x2300170
dds3Basic_t *dds3MoverBasicAdd(dds3Basic_t *pObjectBasic) {
  dds3Basic_t *v4;
  void *workdata;
  dds3Basic_t *v6;
  u32 v10;
  dds3Basic_t *v11;
  char *v13;

  v4 = dds3SceneBasicAdd(3);
  workdata = v4->workdata;
  v6 = v4;
  if (!workdata)
    goto LABEL_9;
  goto LABEL_7;
  if (!workdata)
LABEL_7:
LABEL_9:
  v10 = dds3SerializeID();
  v11 = pObjectBasic;
  v6->serialID = v10;
  workdata[1].klass = (Project_Basic_dds3Basic_t_WORK_c *)v11;
  v13 = movernamestr[movername];
  v6->name = v13;
  movername = (movername + 1)
                                                                  % 10;
  return v6;
}

// 0x2300310
void dds3MoverBasicSetCallBackPrimaryControl(dds3Basic_t *mover, dds3MoverBasicObjFunc_t func) {
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  workdata = mover->workdata;
  klass = workdata->klass;
}

// 0x23003c0
void dds3MoverBasicSetPath(dds3Basic_t *pMoverBasic, dds3Basic_t *pPathBasic) {
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  workdata = pMoverBasic->workdata;
  klass = workdata->klass;
}

// 0x2300470
void dds3MoverBasicMakePath(dds3Basic_t *pMoverBasic) {
  void *workdata;
  dds3PathBasicControl_t *Control;

  workdata = pMoverBasic->workdata;
  Control = dds3PathBasicMakeControl(&workdata[2].monitor);
  workdata[1].monitor = Control;
}

// 0x22fdea0
void dds3MoverBasicFreePath(dds3Basic_t *pMoverBasic) {
  void *workdata;
  void **p_monitor;
  void *monitor;

  workdata = pMoverBasic->workdata;
  monitor = workdata[1].monitor;
  p_monitor = &workdata[1].monitor;
  if (monitor)
  {
    *p_monitor = 0;
  }
}

// 0x2300970
dds3PathBasicControl_t *dds3MoverBasicGetPathControl(dds3Basic_t *pMoverBasic) {
  dds3PathBasicControl_t *workdata;
  s64 naturalAligment;

  workdata = (dds3PathBasicControl_t *)pMoverBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[4].pFovy) < (u32)naturalAligment || *((Project_Basic_dds3MoverBasicWorkData_t_c **)(workdata)[3].monitor + naturalAligment - 1) != Project_Basic_dds3MoverBasicWorkData_t;
  }
  return workdata[3];
}

// 0x23009f0
bool dds3MoverBasicUpdate(dds3Basic_t *pBasic) {
  Mainprocuder(pBasic);
  return 1;
}
