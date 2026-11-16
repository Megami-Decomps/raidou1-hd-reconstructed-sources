#include "types.h"
#include "dds3areabasic.h"
#include "dds3basic.h"
#include "dds3kerneldraw.h"
#include "dds3lightobjectbasic.h"
#include "dds3objectbase.h"
#include "dds3pointbasic.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "evt.h"
#include "mdl.h"
#include "sbtlmain.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

#define DDS3_UNIT_FLAG_ROT180 1

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;

dds3BasicFunction_t *Function;
static sdfVector4_t r_q;
static sdfVector4_t r_v;
static dds3PoseSet_t *r_update;

static bool Constructor(dds3Basic_t *aPtr);
static void Destructor(dds3Basic_t *aPtr);
static bool MainProcedure(dds3Basic_t *aPtr);
static bool DrawProcedure(dds3Basic_t *aPtr);

// macros
// 0x2308380: f32 R360LR(f32 a, f32 b)
static inline f32 R360LR(f32 a, f32 b) {
  _BOOL4 v3;
  f32 v4;
  f32 v5;

  v3 = a < 0.0;
  if (b < 0.0)
    v3 = 1;
  if (v3)
  {
    a = a + 360.0;
    b = b + 360.0;
  }
  if (a == INFINITY)
    v4 = -128.0;
  else
    v4 = ((s32)a % 360);
  if (b == INFINITY)
    v5 = -128.0;
  else
    v5 = ((s32)b % 360);
  if ((f32)(v4 - v5) > 180.0 || (f32)(v4 - v5) < -180.0)
  {
    if (v4 < v5)
      return v5 - (f32)(v4 + 360.0);
    v5 = v5 + 360.0;
  }
  return v5 - v4;
}

// 0x2305af0
static bool Constructor(dds3Basic_t *aPtr) {
  dds3Basic_t *v2;
  void *v3;
  evtUnitHandle_t *v4;
  void *workdata;
  void *v9;
  dds3ObjectBaseControlWorkData_t *inited;
  void *v12;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *basic;

  basic = aPtr;
  dds3InitPoseSet(basic);
  v2 = basic;
  v3 = Allocate(Project_Basic_dds3UnitObjectBasicWorkData_t);
  v4 = Allocate(evtUnitHandle_t);
  _ctor(v4, 0);
  v3[2].klass = (Project_Basic_dds3Basic_t_WORK_c *)v4;
  _ctor(v3, 0);
  v2->workdata = v3;
  workdata = basic->workdata;
  Clear(workdata);
  v9 = basic->workdata;
  inited = dds3ObjectBaseInitControlWorkData(basic);
  v9[2].monitor = inited;
  v9[2].klass = 0;
  v12 = v9 + 2;
  HIDWORD(v12[1].monitor) = 0;
  LODWORD(v12[2].klass) = 0;
  *(Project_Basic_dds3Basic_t_WORK_c **)((char *)&v12[4].klass + 4) = 0;
  *(Project_Basic_dds3Basic_t_WORK_c **)((char *)&v12[5].klass + 4) = 0;
  *(void **)((char *)&v12[3].monitor + 4) = -3184263168LL;
  v12[1].klass = (Project_Basic_dds3Basic_t_WORK_c *)-1;
  *(void **)((char *)&v12[4].monitor + 4) = 0;
  *(Project_Basic_dds3Basic_t_WORK_c **)((char *)&v12[3].klass + 4) = (Project_Basic_dds3Basic_t_WORK_c *)0xC234000000000000LL;
  *(void *)((char *)&v12[2] + 4) = (struct Project_Basic_dds3Basic_t_WORK_o)xmmword_3CFB1D0;
  BaseControlWorkData = dds3GetBaseControlWorkData(basic);
  BaseControlWorkData->flag |= 0x42u;
  return 1;
}

// 0x2305e40
static void Destructor(dds3Basic_t *aPtr) {
  void *workdata;
  evtUnitHandle_t *v8;
  dds3Basic_t *unitBasic;

  unitBasic = aPtr;
  dds3UnitObjectBasicEL_LinkFree(unitBasic);
  dds3FreePoseSet(unitBasic);
  workdata = unitBasic->workdata;
  if (!workdata)
    return;
  if (LODWORD(workdata[1].klass) != -1)
    LODWORD(workdata[1].klass) = -1;
  v8 = &workdata[2];
  if (workdata[2].klass)
  {
    evtDeleteUnitHandle(v8);
    v8 = 0;
  }
  dds3ObjectBaseFreeModelHandle(unitBasic);
  dds3ObjectBaseFreeControlWorkData(&workdata[2].monitor);
}

// 0x23060c0
static bool MainProcedure(dds3Basic_t *aPtr) {
  void *workdata;
  s64 naturalAligment;
  dds3PoseSet_t *p_poseset;
  f32 *v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  dds3PoseSet_t *v16;
  bool v17;
  dds3PoseSet_t *v18;
  dds3PoseSet_t *v19;
  f32 v20;
  dds3PoseSet_t *poseset;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  s64 v35;
  f32 v36;
  s32 klass;
  dds3PoseSet_t *v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  s32 v43;
  dds3PoseSet_t *v44;
  dds3PoseSet_t *v45;
  f32 y;
  f32 x;
  f32 v48;
  dds3ModelHandle_t *v49;
  s64 v50;
  dds3PoseSet_t *v53;
  Project_Basic_dds3Basic_t_WORK_c *v54;
  u32 v55;
  s32 v56;
  u32 v57;
  char v59;
  char v62;
  dds3PoseSet_t *v64;
  bool v65;
  f32 v69;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v75;
  struct sdfVector4_t r_v_local;
  f32 v81;
  dds3PoseSet_t *v84;
  dds3Basic_t *ControlScene;
  s32 monitor_high;
  void *v91;
  dds3Basic_t *v92;
  s64 v93;
  s64 v94;
  dds3Basic_t *next;
  dds3PointBasicWorkData_t *v96;
  f32 v98;
  f32 v99;
  dds3Basic_t *v100;
  f32 z;
  f32 w;
  dds3Basic_t *pBasic;
  sdfVector4_t v108;
  sdfVector4_t v109;

  pBasic = aPtr;
  workdata = aPtr->workdata;
  if (!!workdata[2].klass)
  {
    dds3InitPoseSetValue(r_update);
    if (evtUnitManagerPrimaryFunc(r_update, aPtr))
      goto LABEL_18;
  }
  p_poseset = &aPtr->poseset;
  goto LABEL_12;
LABEL_18:
  v11 = r_update;
  v12 = v11[28];
  v13 = v11[29];
  v14 = v11[30];
  v15 = v11[31];
  v108.x = v12;
  v108.y = v13;
  v108.z = v14;
  v108.w = v15;
  dds3AddSclPoseSet(pBasic, v108);
  dds3AddRotPoseSet(pBasic, r_update->rot);
  dds3AddPosPoseSet(pBasic, r_update->pos);
  p_poseset = &pBasic->poseset;
LABEL_12:
  if (!dds3CheckPoseSetFlag(p_poseset, 0x10u))
    goto LABEL_13;
  v16 = &pBasic->poseset;
  v17 = dds3CheckPoseSetFlag(v16, 1u);
  v18 = &pBasic->poseset;
  if (v17)
  {
    v19 = v18;
    *(f32 *)&workdata[6].monitor = v18->pos.x;
    HIDWORD(workdata[6].monitor) = LODWORD(v19->pos.y);
    if (sBtlIsSetsumaPadStop())
      goto LABEL_57;
    goto LABEL_45;
  }
  dds3OnPoseSetFlag(v18, 1u);
  v20 = *((f32 *)&workdata[4].klass + 1) + 0.05;
  poseset = pBasic->poseset;
  *((f32 *)&workdata[4].klass + 1) = v20;
  v22 = v20 * 0.15915494;
  v23 = (s32)v22;
  if (v22 == INFINITY)
    v23 = -2147500000.0;
  v24 = v22 - v23;
  if ((f32)(v22 - v23) <= 0.5)
  {
    if (v24 >= -0.5)
      goto LABEL_38;
    v25 = 1.0;
  }
  else
  {
    v25 = -1.0;
  }
  v24 = v24 + v25;
LABEL_38:
  if (v24 <= 0.25)
  {
    if (v24 < -0.25)
      v24 = -0.5 - v24;
  }
  else
  {
    v24 = 0.5 - v24;
  }
  v26 = v24 * 4.0;
  v27 = v26 * (f32)(v26 * v26);
  v28 = *(f32 *)&workdata[6].monitor
      + (f32)((f32)((f32)((f32)((f32)((f32)(v26 * 1.5707963) + (f32)(v27 * -0.6459637)) + (f32)((f32)((f32)(v26 * v26) * v27) * 0.07968968)) + (f32)((f32)((f32)(v26 * v26) * (f32)((f32)(v26 * v26) * v27)) * -0.0046737655)) + (f32)((f32)((f32)(v26 * v26) * (f32)((f32)(v26 * v26) * (f32)((f32)(v26 * v26) * v27))) * 0.00015148419)) * 2.5);
  poseset->pos.x = v28;
  v29 = v28 - *(f32 *)&workdata[6].monitor;
  if (v29 < 0.0)
    v29 = -v29;
  v30 = *((f32 *)&workdata[6].monitor + 1) + (f32)(v29 * -0.5);
  poseset->pos.y = v30;
  poseset->pos2.x = v28;
  poseset->pos2.y = v30;
  if (sBtlIsSetsumaPadStop())
    goto LABEL_57;
  goto LABEL_45;
LABEL_13:
  if (sBtlIsSetsumaPadStop())
    goto LABEL_57;
LABEL_45:
  if (((s64)workdata[6].klass & 0x80000000) != 0)
    goto LABEL_57;
  v31 = sub_1B34D00(0);
  v32 = *((f32 *)&workdata[6].klass + 1);
  v33 = v31;
  v34 = v31 * v32;
  v36 = sub_1B34D00(0, v35) * v32;
  klass = workdata[6].klass;
  v38 = pBasic->poseset;
  if ((klass & 4) != 0)
    v39 = v34;
  else
    v39 = -(f32)(v33 * v32);
  if ((klass & 4) != 0)
    v40 = v36;
  else
    v40 = -v36;
  v38->pos.x = v38->pos.x + v39;
  v38->pos2.x = v39 + v38->pos2.x;
  v38->pos.z = v40 + v38->pos.z;
  v38->pos2.z = v40 + v38->pos2.z;
  v41 = *((f32 *)&workdata[6].klass + 1);
  if (v41 <= 0.0)
  {
    v43 = klass + 1;
  }
  else
  {
    v42 = v41 + -0.2;
    *((f32 *)&workdata[6].klass + 1) = v42;
    if (v42 >= 0.0)
      goto LABEL_57;
    HIDWORD(workdata[6].klass) = 0;
    v43 = -1;
  }
  LODWORD(workdata[6].klass) = v43;
LABEL_57:
  v45 = &pBasic->poseset;
  v44 = pBasic->poseset;
  y = v44->pos.y;
  v44->pos.x = v44->pos.x + *(f32 *)&workdata[7].klass;
  v44->pos.y = y + *((f32 *)&workdata[7].klass + 1);
  x = v44->pos2.x;
  v48 = v44->pos2.y;
  v44->pos.z = v44->pos.z + *(f32 *)&workdata[7].monitor;
  v44->pos2.x = x + *(f32 *)&workdata[7].klass;
  v44->pos2.y = v48 + *((f32 *)&workdata[7].klass + 1);
  v44->pos2.z = v44->pos2.z + *(f32 *)&workdata[7].monitor;
  v49 = *((dds3ModelHandle_t *)workdata[2].monitor + 5);
  if (!v49)
    goto LABEL_62;
  if (v49->klass->_2.naturalAligment < (u32)v50 || v49->klass->_2.typeHierarchy[v50 - 1] != dds3ModelHandle_t)
  {
    v91 = *((void *)workdata[2].monitor + 5);
    goto LABEL_186;
  }
  if (!dds3CheckPoseSetFlag(v45, 1u))
    goto LABEL_62;
  goto LABEL_9000;
  if (!dds3CheckPoseSetFlag(v45, 1u))
  {
LABEL_62:
    if ((dds3GetBaseControlWorkData(pBasic)->flag & 0x100) != 0)
      goto LABEL_63;
LABEL_137:
    dds3UnitObjectBasicEL_Link(pBasic);
    if ((dds3GetBaseControlWorkData(pBasic)->flag & 0x2000) == 0)
      return 1;
    goto LABEL_140;
  }
LABEL_9000:
  v53 = &pBasic->poseset;
  dds3OffPoseSetFlag(v53, 1u);
  v54 = workdata[2].klass;
  if (!v54)
  {
    LOBYTE(v57) = 0;
    goto LABEL_77;
  }
  if (LOWORD(v54[1]._1.this_arg.data) && LOWORD(v54[1]._1.this_arg.data) != 3)
  {
    v55 = *(&v54[1]._1.byval_arg.bits + 1);
    v56 = 0;
  }
  else
  {
    v55 = *(&v54[1]._1.byval_arg.bits + 1);
    v56 = (v55 >> 6) & 1;
  }
  v57 = v56 | ((v55 & 0x400000) >> 22);
LABEL_77:
  dds3GetSclPoseSetMCR(pBasic);
  v59 = v57 ^ 1;
  if (!workdata[2].klass)
    v59 = 1;
  if ((v59 & 1) != 0)
  {
    goto LABEL_81;
  }
  vct_B = vct_A;
  vct_A = vf00;
  vct_A.w = 0.0;
  v69 = sub_188E3D0(*(f32 *)&workdata[2].klass[1]._1.namespaze);
  v71 = v69 * 0.01;
  vct_A.x = v71;
  v72 = sub_188E3D0(*(f32 *)&workdata[2].klass[1]._1.namespaze);
  v73 = v72;
  v75 = v72 * 0.004;
  vct_A.y = v75;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_81:
  mdlSetScale(v49);
  dds3GetRotPoseSetMCR(pBasic);
  v62 = v57 ^ 1;
  if (!workdata[2].klass)
    v62 = 1;
  if ((v62 & 1) != 0)
  {
    if (((s64)workdata[3].monitor & 1) == 0)
      goto LABEL_86;
LABEL_123:
    vct_B = r_q;
    Mult();
    goto LABEL_87;
  }
  vct_B = vct_A;
  r_v_local = r_v;
  vct_A = r_v_local;
  v81 = sub_188E3D0(*(f32 *)&workdata[2].klass[1]._1.namespaze);
  FromRotation(v81 * 0.006);
  Mult();
  if (((s64)workdata[3].monitor & 1) != 0)
    goto LABEL_123;
LABEL_86:
LABEL_87:
  mdlSetRotate(v49);
  v64 = &pBasic->poseset;
  v65 = dds3CheckPoseSetFlag(v64, 8u);
  if (v65)
  {
    dds3GetPos2PoseSetMCR(pBasic);
  }
  else
  {
    dds3GetPosPoseSetMCR(pBasic);
  }
  mdlSetPosition(v49);
  v84 = &pBasic->poseset;
  dds3BackupPoseSet(v84);
  if ((dds3GetBaseControlWorkData(pBasic)->flag & 0x100) == 0)
    goto LABEL_137;
LABEL_63:
  if ((dds3GetBaseControlWorkData(pBasic)->flag & 0x2000) == 0)
    return 1;
LABEL_140:
  if (HIDWORD(workdata[3].monitor))
  {
    ControlScene = dds3GetControlScene();
    monitor_high = HIDWORD(workdata[3].monitor);
    v91 = ControlScene->workdata;
    if (!v91)
      goto LABEL_154;
LABEL_152:
    if (v91->klass->_2.naturalAligment >= (u32)v93 && (dds3SceneBasic_t *)v91->klass->_2.typeHierarchy[v93 - 1] == dds3SceneBasic_t)
    {
      goto LABEL_154;
    }
LABEL_186:
    v91 = ControlScene->workdata;
    if (!v91)
    {
LABEL_154:
      v94 = *((u64 *)v91[1].monitor + 20);
      if (*(u32 *)(v94 + 16))
      {
        next = *(dds3Basic_t *)(v94 + 24);
        do
        {
          if (next->serialID == monitor_high)
            break;
          next = next->next;
        }
        while (next);
      }
      else
      {
        next = 0;
      }
      v96 = dds3PointBasicGetWorkData(next);
      v98 = v96->pos.x;
      v99 = v96->pos.y;
      v100 = pBasic;
      z = v96->pos.z;
      w = v96->pos.w;
      v109.x = v98;
      v109.y = v99;
      v109.z = z;
      v109.w = w;
      dds3UnitObjectBasicSetKubiTerget(v100, v109);
      return 1;
    }
    goto LABEL_152;
  }
  v92 = pBasic;
  dds3UnitObjectBasicSetKubiModori(v92);
  return 1;
}

// 0x2307a60
static bool DrawProcedure(dds3Basic_t *aPtr) {
  void *workdata;
  void *v6;
  s32 klass_high;
  s64 ModelOt_local;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = aPtr;
  workdata = aPtr->workdata;
  if ((dds3GetBaseControlWorkData(pObjectBasic)->flag & 1) == 0)
  {
    v6 = aPtr->workdata;
    if (!v6)
      goto LABEL_15;
    goto LABEL_13;
    if (!v6)
    {
LABEL_15:
      klass_high = HIDWORD(v6[3].klass);
      if (klass_high == -1)
      {
        ModelOt_local = ModelOt;
      }
      else
      {
        klass_high = HIDWORD(v6[3].klass);
        ModelOt_local = (s64)ModelOt + 8 * klass_high;
      }
      dds3ObjectBaseModelLinkOt(*(sdfModelOt_t *)(ModelOt_local + 32), pObjectBasic);
      return 1;
    }
LABEL_13:
    goto LABEL_15;
  }
  return 1;
}

// 0x2305ff0
void dds3UnitObjectBasicEL_LinkFree(dds3Basic_t *unitBasic) {
  void *workdata;

  workdata = unitBasic->workdata;
  if (LODWORD(workdata[3].klass) != -1)
  {
    dds3UnlinkLightObjectFromUnitObject(unitBasic, 0xAu);
    LODWORD(workdata[3].klass) = -1;
  }
}

// 0x2306f10
void dds3UnitObjectBasicEL_Link(dds3Basic_t *unitBasic) {
  Il2CppObject *v3;
  void *workdata;
  s64 naturalAligment;
  dds3BasicArrayHandle_t *List;
  s16 *v11;
  s32 v14;
  s32 v15;
  dds3Basic_t *BasicArray;
  void *v18;
  s64 v20;
  dds3Basic_t *v21;
  dds3BasicArrayHandle_t *v25;
  s32 firstindex;
  dds3Basic_t *v28;
  s64 v30;
  dds3Basic_t *v31;
  dds3Basic_t *v33;
  dds3Basic_t *ControlScene;
  dds3BasicArrayHandle_t *hndl;

  v3 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v3, 0);
  workdata = unitBasic->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
    {
      v18 = unitBasic->workdata;
LABEL_74:
    }
  }
  ControlScene = dds3GetControlScene();
  if (!ControlScene)
    return;
  List = dds3SceneBasicGetList(ControlScene, 9u);
  hndl = List;
  if (!List)
    return;
  v11 = List;
  if (v11[11])
    goto LABEL_16;
LABEL_22:
  dds3FreeBasicArrayHandle(hndl);
  return;
LABEL_16:
  v15 = v11[8];
  v11[10] = v11[8];
  if (v15 < 0)
    goto LABEL_44;
  while (1)
  {
LABEL_28:
    BasicArray = dds3GetBasicArray(hndl);
    v18 = BasicArray->workdata;
    if (v18)
    {
      if (v18->klass->_2.naturalAligment < (u32)v20 || v18->klass->_2.typeHierarchy[v20 - 1] != dds3LightObjectBasicWorkData_t)
      {
        goto LABEL_74;
      }
    }
    if ((BYTE4(v18[3].monitor) & 4) == 0)
    {
      v21 = unitBasic;
      if (!dds3RadiusCheckPoseSet2(&v21->poseset, &BasicArray->poseset))
      {
        if (LODWORD(workdata[3].klass) == (u64)BasicArray->serialID)
        {
          dds3UnlinkLightObjectFromUnitObject(unitBasic, 0xAu);
          LODWORD(workdata[3].klass) = -1;
        }
      }
    }
    if (!dds3SetNextBasicArray(hndl))
      goto LABEL_44;
  }
  v14 = v11[8];
  v11[10] = v11[8];
  if ((v14 & 0x80000000) == 0)
    goto LABEL_28;
LABEL_44:
  dds3FreeBasicArrayHandle(hndl);
  if (LODWORD(workdata[3].klass) != -1)
    return;
  v25 = dds3SceneBasicGetList(ControlScene, 9u);
  hndl = v25;
  firstindex = v25->firstindex;
  v25->nowindex = v25->firstindex;
  if ((firstindex & 0x80000000) == 0)
  {
    while (1)
    {
      v28 = dds3GetBasicArray(hndl);
      v18 = v28->workdata;
      if (v18)
      {
        if (v18->klass->_2.naturalAligment < (u32)v30 || v18->klass->_2.typeHierarchy[v30 - 1] != dds3LightObjectBasicWorkData_t)
        {
          goto LABEL_74;
        }
      }
      if ((BYTE4(v18[3].monitor) & 4) == 0)
      {
        v31 = unitBasic;
        if (dds3RadiusCheckPoseSet2(&v31->poseset, &v28->poseset))
        {
          v33 = unitBasic;
          dds3LinkLightObjectToUnitObject(v28, v33, 0xAu);
          LODWORD(workdata[3].klass) = v28->serialID;
          break;
        }
      }
      if (!dds3SetNextBasicArray(hndl))
        break;
    }
  }
  goto LABEL_22;
}

// 0x23029b0
dds3ObjectBaseControlWorkData_t *dds3UnitObjectBasicGetControlWorkData(dds3Basic_t *pBasic) {
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;

  workdata = (dds3ObjectBaseControlWorkData_t *)pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(Project_Basic_dds3UnitObjectBasicWorkData_t_c **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != Project_Basic_dds3UnitObjectBasicWorkData_t;
  }
  return workdata[5];
}

// 0x2307ed0
dds3Basic_t *dds3UnitObjectBasicAdd(u32 serialID, const sdfVector4_t *aPos, const sdfVector4_t *aRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  dds3Basic_t *result;
  void *workdata;
  void *v19;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  s32 data;
  dds3Basic_t *pItemBasic;
  dds3Basic_t *pObjectBasic;
  dds3Basic_t *pAreaBasic;
  sdfVector4_t v27;
  sdfVector4_t v28;

  w = aRot->w;
  z = aRot->z;
  y = aRot->y;
  x = aRot->x;
  v8 = aPos->w;
  v9 = aPos->z;
  v10 = aPos->y;
  v11 = aPos->x;
  result = dds3SceneBasicAdd(5);
  pObjectBasic = result;
  if (!result)
    return result;
  result->serialID = serialID;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v27.x = v11;
  v27.y = v10;
  v27.z = v9;
  v27.w = v8;
  dds3SetPosPoseSet(pObjectBasic, v27);
  v28.x = x;
  v28.y = y;
  v28.z = z;
  v28.w = w;
  dds3SetRotPoseSet(pObjectBasic, v28);
  dds3BackupPoseSet(&pObjectBasic->poseset);
  workdata = pObjectBasic->workdata;
  LODWORD(workdata[1].klass) = -1;
  data = 0;
  v19 = Box(s32, &data);
  workdata[1].monitor = v19;
  pItemBasic = dds3AreaBasicGetFastArea();
  dds3ObjectBaseSetControlBasicType(pObjectBasic, pItemBasic, 4u);
  if (pObjectBasic)
  {
    BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
    if (BaseControlWorkData)
    {
      pAreaBasic = BaseControlWorkData->pBasic[4];
      if (pAreaBasic)
      {
        dds3AreaBasicRegistItem(pAreaBasic, pObjectBasic);
      }
    }
  }
  return pObjectBasic;
}

// 0x2308160
void dds3UnitObjectBasicDelete(dds3Basic_t *aPtr) {
  dds3Basic_t *v4;

  v4 = aPtr;
  dds3SceneBasicDelete(v4);
}

// 0x23081e0
s32 dds3UnitObjectBasicGetStatus(dds3Basic_t *aPtr) {
  s32 *workdata;

  workdata = aPtr->workdata;
  return workdata[4];
}

// 0x2307c00
evtUnitHandle_t *dds3UnitObjectBasicGetUnitHandle(dds3Basic_t *b) {
  evtUnitHandle_t *workdata;
  s64 naturalAligment;

  workdata = (evtUnitHandle_t *)b->workdata;
  if (workdata)
  {
    LOBYTE(workdata->TargetModelRGBA.x) < (u32)naturalAligment || *(Project_Basic_dds3UnitObjectBasicWorkData_t_c **)(*(u64 *)&workdata->NowLightDir2.z + 8 * naturalAligment - 8) != Project_Basic_dds3UnitObjectBasicWorkData_t;
  }
  return workdata[4];
}

// 0x2308270
void dds3UnitObjectBasicSetOt(dds3Basic_t *aPtr, s32 idx) {
  void *workdata;

  workdata = aPtr->workdata;
  HIDWORD(workdata[3].klass) = idx;
}

// 0x2308300
s32 dds3UnitObjectBasicGetOt(dds3Basic_t *aPtr) {
  s32 *workdata;

  workdata = aPtr->workdata;
  return workdata[13];
}

// 0x23073e0
void dds3UnitObjectBasicSetKubiTerget(dds3Basic_t *pBasic, const sdfVector4_t *aTgt) {
  f32 z;
  f32 x;
  void *workdata;
  f32 v8;
  s64 v9;
  bool v13;
  long f64 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  _BOOL4 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v26;
  f32 v27;
  _BOOL4 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v34;
  f32 v35;
  dds3Basic_t *pBasica;

  z = aTgt->z;
  x = aTgt->x;
  pBasica = pBasic;
  workdata = pBasic->workdata;
  v8 = *(f32 *)&workdata[4].monitor;
  dds3GetPosPoseSet(pBasica);
  v13 = vct_A.x == x && vct_A.z == z;
  if (!v13)
    goto LABEL_23;
  return;
  if (vct_A.x != x || vct_A.z != z)
  {
LABEL_23:
    v16 = sub_18E6660(0, v9);
    v17 = *(f32 *)&v16;
    v18 = v17 * -57.32484;
    dds3GetRotPoseSet(pBasica);
    v19 = EulerAngleAxisY() * 57.29578;
    v20 = v18 < 0.0;
    if (v19 < 0.0)
      v20 = 1;
    if (v20)
      v21 = v18 + 360.0;
    else
      v21 = v18;
    if (v20)
      v22 = v19 + 360.0;
    else
      v22 = v19;
    if (v22 == INFINITY)
      v23 = -128.0;
    else
      v23 = ((s32)v22 % 360);
    v24 = ((s32)v21 % 360);
    if (v21 == INFINITY)
      v24 = -128.0;
    if ((f32)(v23 - v24) > 180.0 || (f32)(v23 - v24) < -180.0)
    {
      if (v23 >= v24)
        v24 = v24 + 360.0;
      else
        v23 = v23 + 360.0;
    }
    v26 = v24 - v23;
    if (v26 < *((f32 *)&workdata[4].monitor + 1))
      v26 = *((f32 *)&workdata[4].monitor + 1);
    if (v26 <= *(f32 *)&workdata[5].klass)
      v27 = v26;
    else
      v27 = *(f32 *)&workdata[5].klass;
    v28 = v8 < 0.0;
    v29 = v8 + 360.0;
    if (v27 < 0.0)
      v28 = 1;
    if (v28)
    {
      v30 = v27 + 360.0;
    }
    else
    {
      v29 = v8;
      v30 = v27;
    }
    v31 = ((s32)v29 % 360);
    v13 = v29 == INFINITY;
    v32 = -128.0;
    if (v13)
      v31 = -128.0;
    if (v30 != INFINITY)
      v32 = ((s32)v30 % 360);
    if ((f32)(v31 - v32) > 180.0 || (f32)(v31 - v32) < -180.0)
    {
      if (v31 >= v32)
      {
        v34 = (f32)(v32 + 360.0) - v31;
        v35 = 1.5;
        if (v34 >= 0.0 && v34 <= 1.5)
          goto LABEL_89;
LABEL_76:
        if (v34 > 0.0 || v34 < -1.5)
        {
          if (v34 >= 0.0)
            v27 = v8 + v35;
          else
            v27 = v8 + -1.5;
        }
LABEL_89:
        *(f32 *)&workdata[4].monitor = v27;
        HIDWORD(workdata[5].klass) = 0;
        return;
      }
      v31 = v31 + 360.0;
    }
    v34 = v32 - v31;
    v35 = 1.5;
    if (v34 >= 0.0 && v34 <= 1.5)
      goto LABEL_89;
    goto LABEL_76;
  }
}

// 0x2307820
void dds3UnitObjectBasicSetKubiModori(dds3Basic_t *pBasic) {
  void *workdata;
  s32 klass;
  bool v6;
  s32 v7;
  f32 v8;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v16;
  f32 v17;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = pBasic;
  workdata = pBasic->workdata;
  klass = workdata[4].klass;
  v6 = __OFSUB__(klass, 1);
  v7 = klass - 1;
  if (v7 < 0 == v6)
  {
    LODWORD(workdata[4].klass) = v7;
    return;
  }
  v8 = *(f32 *)&workdata[4].monitor;
  if (v8 < 0.1 && v8 > -0.1)
  {
    BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
    BaseControlWorkData->flag &= ~0x2000u;
    return;
  }
  v10 = 0.0;
  v11 = v8 + 360.0;
  if (v8 >= 0.0)
    v12 = 0.0;
  else
    v12 = 360.0;
  if (v8 >= 0.0)
    v11 = v8;
  v13 = ((s32)v11 % 360);
  if (v11 == INFINITY)
    v13 = -128.0;
  v14 = ((s32)v12 % 360);
  if ((f32)(v13 - v14) > 180.0 || (f32)(v13 - v14) < -180.0)
  {
    if (v13 >= v14)
    {
      v16 = (f32)(v14 + 360.0) - v13;
      v17 = 0.5;
      if (v16 >= 0.0 && v16 <= 0.5)
        goto LABEL_41;
      goto LABEL_34;
    }
    v13 = v13 + 360.0;
  }
  v16 = v14 - v13;
  v17 = 0.5;
  if (v16 >= 0.0 && v16 <= 0.5)
    goto LABEL_41;
LABEL_34:
  if (v16 <= 0.0 && v16 >= -0.5)
    goto LABEL_41;
  if (v16 < 0.0)
  {
    v10 = v8 + -0.5;
LABEL_41:
    *(f32 *)&workdata[4].monitor = v10;
    HIDWORD(workdata[5].klass) = 0;
    return;
  }
  *(f32 *)&workdata[4].monitor = v8 + v17;
  HIDWORD(workdata[5].klass) = 0;
}

// 0x2308460
void dds3UnitObjectBasicKubiOn(dds3Basic_t *pBasic, s32 posid) {
  s32 v3;
  void *workdata;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *pObjectBasic;

  v3 = posid;
  pObjectBasic = pBasic;
  if (pBasic)
  {
    workdata = pBasic->workdata;
    BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
    BaseControlWorkData->flag |= 0x2000u;
    if (HIDWORD(workdata[3].monitor) != v3)
    {
      HIDWORD(workdata[3].monitor) = v3;
      LODWORD(workdata[4].klass) = 0;
    }
  }
}

// 0x2308520
void dds3UnitObjectBasicKubiOff(dds3Basic_t *pBasic) {
  void *workdata;

  if (pBasic)
  {
    workdata = pBasic->workdata;
    if (HIDWORD(workdata[3].monitor))
      *(void **)((char *)&workdata[3].monitor + 4) = 0x1E00000000LL;
  }
}

// 0x23085c0
void dds3UnitObjectBasicSetDamageYure(dds3Basic_t *pBasic, f32 range) {
  void *workdata;

  workdata = pBasic->workdata;
  LODWORD(workdata[6].klass) = 0;
  *((f32 *)&workdata[6].klass + 1) = range;
}

// 0x2308650
void dds3UnitObjectBasicSetJumpOfsPos(dds3Basic_t *pBasic, f32 _X, f32 _Y, f32 _Z) {
  f32 *workdata;

  if (pBasic)
  {
    workdata = pBasic->workdata;
    if (workdata)
    {
      workdata[28] = X;
      workdata[29] = Y;
      workdata[30] = Z;
    }
  }
}
