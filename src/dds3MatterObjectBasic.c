#include "types.h"
#include "dds3basic.h"
#include "dds3kerneldraw.h"
#include "dds3matterobjectbasic.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "fld.h"
#include "kernel.h"
#include "sdf_vu0.h"

typedef struct SDF_GS_TEST SDF_GS_TEST;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;

dds3BasicFunction_t *Function;
static SDF_GS_TEST *procTest60;
static SDF_GS_TEST *procTest80;
static s32 gMatterDrawFlg;

static bool Constructor(dds3Basic_t *aPtr);
static void Destructor(dds3Basic_t *aPtr);
static bool MainProcedure(dds3Basic_t *aPtr);
static bool DrawProcedure(dds3Basic_t *aPtr);

// 0x22face0
static bool Constructor(dds3Basic_t *aPtr) {
  dds3Basic_t *v2;
  void *v3;
  void *workdata;
  dds3ObjectBaseControlWorkData_t *inited;
  void *v8;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *basic;

  basic = aPtr;
  dds3InitPoseSet(basic);
  v2 = basic;
  v3 = Allocate(Project_Basic_dds3MatterObjectBasicWorkData_t);
  _ctor(v3, 0);
  v2->workdata = v3;
  workdata = basic->workdata;
  inited = dds3ObjectBaseInitControlWorkData(basic);
  workdata[1].klass = (Project_Basic_dds3Basic_t_WORK_c *)inited;
  v8 = workdata + 1;
  v8->monitor = 0;
  LODWORD(v8[1].klass) = -1;
  *(void *)((char *)&v8[1] + 4) = (struct Project_Basic_dds3Basic_t_WORK_o)xmmword_3CFD5C0;
  *(void *)((char *)&v8[2] + 4) = (struct Project_Basic_dds3Basic_t_WORK_o)xmmword_3CFD5C0;
  BaseControlWorkData = dds3GetBaseControlWorkData(basic);
  BaseControlWorkData->flag |= 0xE2u;
  return 1;
}

// 0x22faf70
static void Destructor(dds3Basic_t *aPtr) {
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;
  dds3Basic_t *basic;

  basic = aPtr;
  dds3FreePoseSet(basic);
  workdata = basic->workdata;
  if (workdata)
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(Project_Basic_dds3MatterObjectBasicWorkData_t_c **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != Project_Basic_dds3MatterObjectBasicWorkData_t;
  dds3ObjectBaseFreeControlWorkData(workdata + 2);
}

// 0x22fb1b0
static bool MainProcedure(dds3Basic_t *aPtr) {
  void *workdata;
  u32 v5;
  u32 color;
  u32 v7;
  s32 v8;
  u32 color_high;
  u32 v10;
  s32 v11;
  u32 v12;
  u32 v13;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  Il2CppObject *pModel;
  dds3PoseSet_t *p_poseset;
  sdfVector4_t *p_monitor;
  void **v22;
  _OWORD *p_x;
  __int128 v24;
  __int128 v25;
  __int128 v26;
  dds3PoseSet_t *v27;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = aPtr;
  workdata = aPtr->workdata;
  switch (HIDWORD(workdata[1].monitor))
  {
    case 0:
    case 1:
      v5 = -2139062144;
      goto LABEL_29;
    case 2:
      v5 = 8421504;
      goto LABEL_29;
    case 3:
      color = aPtr->color;
      v7 = HIBYTE(color);
      v8 = HIBYTE(color) + 8;
      goto LABEL_17;
    case 4:
      color_high = HIBYTE(aPtr->color);
      if (color_high > 0x20)
        color_high -= 8;
      if (color_high <= 0x20)
        color_high = 32;
      goto LABEL_22;
    case 5:
      color = aPtr->color;
      v7 = HIBYTE(color);
      v8 = HIBYTE(color) + 4;
      goto LABEL_17;
    case 6:
      v10 = aPtr->color;
      v11 = -67108864;
      goto LABEL_25;
    case 7:
      color = aPtr->color;
      v7 = HIBYTE(color);
      v8 = HIBYTE(color) + 2;
LABEL_17:
      if ((color & 0x80000000) == 0)
        color_high = v8;
      else
        color_high = v7;
      if (color_high >= 0x80)
        color_high = 128;
LABEL_22:
      v5 = (color_high << 24) | 0x808080;
      goto LABEL_29;
    case 8:
      v10 = aPtr->color;
      v11 = -33554432;
      goto LABEL_25;
    case 9:
      v10 = aPtr->color;
      v11 = -184549376;
LABEL_25:
      v12 = (v10 & 0xFF000000) + v11;
      if (HIBYTE(v10))
        v13 = v12;
      else
        v13 = v10 & 0xFF000000;
      v5 = v13 | 0x808080;
LABEL_29:
      aPtr->color = v5;
      break;
    default:
      break;
  }
  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  pModel = BaseControlWorkData->pModel;
  if (pModel)
  {
    p_poseset = &aPtr->poseset;
    dds3OffPoseSetFlag(p_poseset, 1u);
    dds3GetRotPoseSet(pObjectBasic);
    p_monitor = &pModel[9].monitor;
    *p_monitor = vct_A;
    dds3GetTMPoseSet(pObjectBasic);
    dds3GetPosPoseSet(pObjectBasic);
    SetRow(&mtx_A, 3, vct_A, 0);
    v22 = &pModel[5].monitor;
    p_x = &vf00.x;
    v24 = p_x[5];
    v25 = p_x[6];
    v26 = p_x[7];
    *(_OWORD *)v22 = p_x[4];
    *((_OWORD *)v22 + 1) = v24;
    v27 = &pObjectBasic->poseset;
    *((_OWORD *)v22 + 2) = v25;
    *((_OWORD *)v22 + 3) = v26;
    dds3BackupPoseSet(v27);
    return 1;
  }
  return 1;
}

// 0x22fb560
static bool DrawProcedure(dds3Basic_t *aPtr) {
  void *workdata;
  u32 color;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = aPtr;
  if (!gMatterDrawFlg)
    return 1;
  workdata = aPtr->workdata;
  if (LODWORD(workdata[2].klass) != -1)
  {
    ooyTest_OT_Offset = 42;
    rsetTest(procTest60);
    if ((u32)(HIDWORD(workdata[1].monitor) - 3) > 1 || aPtr->color == -2139062144)
    {
      dds3ObjectBaseModelLinkOt(ModelOt[SLODWORD(workdata[2].klass)], pObjectBasic);
LABEL_21:
      ooyTest_OT_Offset = 42;
LABEL_42:
      rsetTest(procTest80);
      return 1;
    }
    if ((dds3GetBaseControlWorkData(playerBasic)->flag & 1) == 0)
    {
      dds3ObjectBaseModelLinkOt(ModelOt[10], pObjectBasic);
      goto LABEL_21;
    }
    color = aPtr->color;
    aPtr->color = -2139062144;
    dds3ObjectBaseModelLinkOt(ModelOt[SLODWORD(workdata[2].klass)], pObjectBasic);
    aPtr->color = color;
    goto LABEL_21;
  }
  ooyTest_OT_Offset = 44;
  rsetTest(procTest60);
  dds3ObjectBaseModelLinkOt(ModelOt[0], pObjectBasic);
  ooyTest_OT_Offset = 44;
  goto LABEL_42;
}

// 0x22fbfb0
dds3ObjectBaseControlWorkData_t *dds3MatterObjectBasicGetControlWorkData(dds3Basic_t *pBasic) {
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;

  workdata = (dds3ObjectBaseControlWorkData_t *)pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(Project_Basic_dds3MatterObjectBasicWorkData_t_c **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != Project_Basic_dds3MatterObjectBasicWorkData_t;
  }
  return workdata[2];
}

// 0x22fc030
dds3Basic_t *dds3MatterObjectBasicAdd(u32 serialID, const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  dds3Basic_t *v14;
  void *workdata;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v19;
  sdfVector4_t v20;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v8 = pos->w;
  v9 = pos->z;
  v10 = pos->y;
  v11 = pos->x;
  pObjectBasic = dds3SceneBasicAdd(6);
  pObjectBasic->serialID = serialID;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v19.x = x;
  v19.y = y;
  v19.z = z;
  v19.w = w;
  dds3SetRotPoseSet(pObjectBasic, v19);
  v20.w = 1.0;
  v20.x = 0.0;
  v20.y = 0.0;
  v20.z = 0.0;
  dds3SetPosPoseSet(pObjectBasic, v20);
  dds3BackupPoseSet(&pObjectBasic->poseset);
  v14 = pObjectBasic;
  workdata = pObjectBasic->workdata;
  *((f32 *)&workdata[2].klass + 1) = v11;
  *(f32 *)&workdata[2].monitor = v10;
  *((f32 *)&workdata[2].monitor + 1) = v9;
  *(f32 *)&workdata[3].klass = v8;
  return v14;
}

// 0x22fc440
void dds3MatterObjectBasicDelete(dds3Basic_t *aPtr) {
  dds3Basic_t *v4;

  v4 = aPtr;
  dds3SceneBasicDelete(v4);
}

// 0x22fc610
void dds3MatterObjectBasicSetOt(dds3Basic_t *aPtr, DDS3_MODEL_OT idx) {
  void *workdata;

  workdata = aPtr->workdata;
  LODWORD(workdata[2].klass) = idx;
}

// 0x22fc6a0
void dds3MatterObjectBasicSetHojiID(dds3Basic_t *aPtr, s32 hojiID) {
  void *workdata;

  workdata = aPtr->workdata;
  LODWORD(workdata[1].monitor) = hojiID;
}

// 0x22fc730
s32 dds3MatterObjectBasicGetHojiID(s32 resID) {
  dds3Basic_t *ControlScene;
  s32 *workdata;
  s64 naturalAligment;
  u64 *v9;
  s64 v10;
  s64 v11;

  ControlScene = dds3GetControlScene();
  workdata = ControlScene->workdata;
  if (!workdata)
    goto LABEL_13;
  if (*(u8 *)(*(u64 *)workdata + 304) < (u32)naturalAligment || *(dds3SceneBasic_t **)(*(u64 *)(*(u64 *)workdata + 200) + 8 * naturalAligment - 8) != dds3SceneBasic_t)
  {
LABEL_19:
  }
LABEL_13:
  v9 = (*(u64 *)(*((u64 *)workdata + 3) + 80) + 24);
  do
  {
    v10 = *v9;
    v9 = (*v9 + 64);
  }
  while (*(u32 *)(v10 + 20) != resID);
  workdata = *(s32 **)(v10 + 48);
  if (workdata)
  {
    if (*(u8 *)(*(u64 *)workdata + 304) < (u32)v11 || *(Project_Basic_dds3MatterObjectBasicWorkData_t_c **)(*(u64 *)(*(u64 *)workdata + 200) + 8 * v11 - 8) != Project_Basic_dds3MatterObjectBasicWorkData_t)
    {
      goto LABEL_19;
    }
  }
  return workdata[6];
}

// 0x22fcaa0
void dds3MatterObjectBasicSetAlpMode(dds3Basic_t *aPtr, s32 alpmode) {
  void *workdata;

  workdata = aPtr->workdata;
  HIDWORD(workdata[1].monitor) = alpmode;
}

// 0x22fcb30
s32 dds3MatterObjectBasicGetAlpMode(dds3Basic_t *aPtr) {
  s32 *workdata;

  workdata = aPtr->workdata;
  return workdata[7];
}

// 0x22fcbc0
void dds3MatterObjectBasicDrawMode(s32 mode) {
  gMatterDrawFlg = mode;
  return;
}

// 0x22fcc50
void dds3MatterObjectBasicPosToBase(dds3Basic_t *aPtr) {
  void *workdata;
  dds3PoseSet_t *poseset;

  workdata = aPtr->workdata;
  poseset = aPtr->poseset;
  HIDWORD(workdata[2].klass) = LODWORD(poseset->pos.x);
  *(f32 *)&workdata[2].monitor = poseset->pos.y;
  HIDWORD(workdata[2].monitor) = LODWORD(poseset->pos.z);
}
