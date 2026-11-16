#include "types.h"
#include "dds3areabasic.h"
#include "dds3basic.h"
#include "dds3effect.h"
#include "dds3effectobjectbasic.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3EffectObjectBasicWorkData_t dds3EffectObjectBasicWorkData_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct effHandle_t effHandle_t;

dds3BasicFunction_t *Function;

static s32 fldGbGetEAnimeCngID(s32 fld, s32 area, s32 grp);
static void FreeEffectData(dds3EffectObjectBasicWorkData_t *work);
static dds3Basic_t *AddD3PEffect(effHandle_t *eff, const sdfVector4_t *pos, const sdfVector4_t *rot);
static dds3Basic_t *AddEPLEffect(effHandle_t *eff, const sdfVector4_t *pos, const sdfVector4_t *rot);
static dds3Basic_t *AddESPEffect(char *name, const sdfVector4_t *pos, const sdfVector4_t *rot, f32 r);

// 0x22f5b00
static s32 fldGbGetEAnimeCngID(s32 fld, s32 area, s32 grp) {
  return 0;
}

// 0x22f5b10
bool dds3EffectObjectBasicConstructor(dds3Basic_t *aPtr) {
  Il2CppObject *v3;
  void *p_workdata;
  dds3EffectObjectBasicWorkData_t *v6;
  s64 naturalAligment;
  dds3EffectObjectBasicWorkData_t *v8;
  dds3ObjectBaseControlWorkData_t *inited;
  dds3EffectObjectBasicWorkData_t *klass;
  s64 v12;
  Il2CppClass **typeHierarchy;
  dds3Basic_t *basic;

  basic = aPtr;
  dds3InitPoseSet(basic);
  v3 = Allocate(dds3EffectObjectBasicWorkData_t);
  _ctor(v3, 0);
  aPtr->workdata = (void *)v3;
  p_workdata = &aPtr->workdata;
  v6 = p_workdata;
  if (p_workdata)
  {
    if (v6->klass->_2.naturalAligment < (u32)naturalAligment || v6->klass->_2.typeHierarchy[naturalAligment - 1] != dds3EffectObjectBasicWorkData_t)
    {
LABEL_13:
    }
  }
  Clear(v6);
  v8 = p_workdata;
  inited = dds3ObjectBaseInitControlWorkData(basic);
  klass = v8->klass;
  if (v8->klass->_2.naturalAligment < (u32)v12 || klass->_2.typeHierarchy[v12 - 1] != dds3EffectObjectBasicWorkData_t || (typeHierarchy = klass->_2.typeHierarchy, v8->pObjectBaseControlWorkData = inited, typeHierarchy[v12 - 1] != dds3EffectObjectBasicWorkData_t))
  {
    v6 = v8;
    goto LABEL_13;
  }
  dds3ObjectBaseOnFlag(basic, 0x60u);
  return 1;
}

// 0x22f5dc0
void dds3EffectObjectBasicDestructor(dds3Basic_t *aPtr) {
  void *p_workdata;
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;
  dds3PoseSet_t *p_poseset;
  dds3PoseSet_t *poseset;
  dds3EffectObjectBasicWorkData_t *work;

  p_workdata = &aPtr->workdata;
  workdata = aPtr->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(dds3EffectObjectBasicWorkData_t **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != dds3EffectObjectBasicWorkData_t;
    work = aPtr->workdata;
    FreeEffectData(work);
    poseset = aPtr->poseset;
    p_poseset = &aPtr->poseset;
    if (!poseset)
    {
LABEL_10:
      dds3ObjectBaseFreeControlWorkData(workdata + 2);
      p_workdata = 0;
      return;
    }
    p_poseset = 0;
    goto LABEL_10;
  }
}

// 0x22f6000
bool dds3EffectObjectBasicMainProcedure(dds3Basic_t *aPtr) {
  void *workdata;
  s64 naturalAligment;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3PoseSet_t *poseset;
  struct sdfVector4_t scl;
  char v15;
  __int128 vct_A_local;
  s32 klass_high;
  dds3Basic_t *monitor;
  s32 v20;
  effHandle_t *v21;
  s64 v22;
  struct sdfVector4_t v23;
  effHandle_t *klass;
  _OWORD *v30;
  __int128 v31;
  __int128 v32;
  __int128 v33;
  __int128 v36;
  __int128 v37;
  __int128 v38;
  __int128 v39;
  __int128 v40;
  _OWORD *v41;
  __int128 v42;
  struct sdfVector4_t v43;
  _OWORD *v45;
  __int128 v46;
  __int128 v47;
  __int128 v48;
  __int128 v49;
  __int128 v52;
  __int128 v53;
  __int128 v54;
  s32 v56;
  _OWORD *v57;
  s64 v59;
  effHandle_t *p_fields;
  f32 *v62;
  dds3PoseSet_t *v63;
  struct sdfVector4_t v65;
  dds3PoseSet_t *v66;
  sdfVector4_t *p_pos;
  s64 v69;
  _OWORD *v72;
  __int128 v73;
  __int128 v74;
  s32 v75;
  __int128 v79;
  __int128 v80;
  __int128 v81;
  __int128 v82;
  __int128 v83;
  _OWORD *v84;
  __int128 v85;
  struct sdfVector4_t v86;
  struct sdfVector4_t v90;
  __int128 v92;
  __int128 v93;
  sdfMatrix4_t v94;
  dds3Basic_t *scene;
  dds3Basic_t *pBasic;
  sdfMatrix4_t v97;
  sdfMatrix4_t v98;
  sdfMatrix4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v103;
  sdfVector4_t v104;

  pBasic = aPtr;
  workdata = aPtr->workdata;
  scene = 0;
  if (((s64)workdata[1].monitor & 4) == 0)
  {
    aPtr->poseset->flag &= ~1u;
    dds3GetPosPoseSetMCR(pBasic);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    w = p_x[7];
    poseset = aPtr->poseset;
    scl = poseset->scl;
    poseset->workscl = scl;
    aPtr->poseset->workrot = aPtr->poseset->rot;
    aPtr->poseset->workpos = aPtr->poseset->pos;
    dds3GetRotPoseSetMCR(pBasic);
    v15 = 0;
    vct_A_local = vct_A;
    if (HIDWORD(workdata[1].monitor) != 1)
      return 1;
    goto LABEL_126;
  }
  scene = dds3GetActiveScene();
  klass_high = HIDWORD(workdata[4].klass);
  monitor = workdata[3].monitor;
  if (dds3SceneBasicExistBasicFromType(scene, klass_high, workdata[3].monitor))
  {
    goto LABEL_22;
  }
  klass = aPtr->workdata;
  if (!klass)
  {
LABEL_85:
    *(u64 *)&klass[1].major = 0;
    p_fields = &klass[1].fields;
    LODWORD(p_fields[-2].version) &= 0xFFFFFFF3;
    HIDWORD(p_fields->pwork) = 0;
    x = 0.0;
    vct_A_local = xmmword_3CFD5C0;
    LOWORD(p_fields->pwork) = 0;
    v15 = 1;
    y = 0.0;
    z = 0.0;
    w = 0.0;
    if (HIDWORD(workdata[1].monitor) != 1)
      return 1;
    goto LABEL_126;
  }
  if (klass->klass->_2.naturalAligment < (u32)v59 || klass->klass->_2.typeHierarchy[v59 - 1] != dds3EffectObjectBasicWorkData_t)
  {
LABEL_171:
    v21 = klass;
    goto LABEL_172;
  }
  goto LABEL_85;
LABEL_22:
  if (((s64)workdata[1].monitor & 8) != 0)
  {
    dds3EffectObjectBasicGetObjectIndex(pBasic);
    v92 = xmmword_3CFD5C0;
    goto LABEL_50;
  }
  v20 = HIDWORD(workdata[4].klass);
  if ((u32)(v20 - 10) > 0xFFFFFFF9)
  {
    v90 = *(sdfVector4_t *)(*((u64 *)workdata[3].monitor + 7) + 96);
    goto LABEL_105;
  }
  if (v20 != 16)
  {
    v79 = *(_OWORD *)&identityMatrix.m00;
    v80 = *(_OWORD *)&identityMatrix.m01;
    v81 = *(_OWORD *)&identityMatrix.m02;
    v82 = *(_OWORD *)&identityMatrix.m03;
    *(_OWORD *)&v99.m00 = v79;
    *(_OWORD *)&v99.m01 = v80;
    *(_OWORD *)&v99.m02 = v81;
    *(_OWORD *)&v99.m03 = v82;
    v83 = *(_OWORD *)&v99.m01;
    v84 = &vf00.x;
    v84[4] = *(_OWORD *)&v99.m00;
    v84[5] = v83;
    v85 = *(_OWORD *)&v99.m03;
    v92 = xmmword_3CFD5C0;
    v84[6] = *(_OWORD *)&v99.m02;
    v84[7] = v85;
    goto LABEL_50;
  }
  v21 = *((effHandle_t *)workdata[3].monitor + 6);
  if (v21)
  {
    if (v21->klass->_2.naturalAligment < (u32)v22 || v21->klass->_2.typeHierarchy[v22 - 1] != fldResourcePoint_t)
    {
LABEL_172:
    }
  }
  v23 = *(sdfVector4_t *)&v21->version;
  v90 = v23;
  goto LABEL_106;
LABEL_105:
  goto LABEL_107;
LABEL_106:
  vct_A = v90;
  goto LABEL_108;
LABEL_107:
  vct_A = v90;
LABEL_108:
  v92 = vct_A;
  ToMatrix();
LABEL_50:
  v30 = &vf00.x;
  v31 = v30[5];
  v32 = v30[6];
  v33 = v30[7];
  v30[8] = v30[4];
  v30[9] = v31;
  v30[10] = v32;
  v30[11] = v33;
  v36 = *(_OWORD *)&identityMatrix.m00;
  v37 = *(_OWORD *)&identityMatrix.m01;
  v38 = *(_OWORD *)&identityMatrix.m02;
  v39 = *(_OWORD *)&identityMatrix.m03;
  *(_OWORD *)&v99.m00 = v36;
  *(_OWORD *)&v99.m01 = v37;
  *(_OWORD *)&v99.m02 = v38;
  *(_OWORD *)&v99.m03 = v39;
  v40 = *(_OWORD *)&v99.m01;
  v41 = &vf00.x;
  v41[4] = *(_OWORD *)&v99.m00;
  v41[5] = v40;
  v42 = *(_OWORD *)&v99.m03;
  v41[6] = *(_OWORD *)&v99.m02;
  v41[7] = v42;
  v43 = *(sdfVector4_t *)&workdata[2].monitor;
  vct_A = v43;
  vct_A.w = 1.0;
  get_transpose(&v99, &mtx_A, 0);
  v101 = vct_A;
  v98 = v99;
  v104 = op_Multiply_60923920(&v98, v101, 0);
  SetRow(&mtx_A, 3, v104, 0);
  v45 = &vf00.x;
  v46 = v45[5];
  *(_OWORD *)&v98.m00 = v45[4];
  *(_OWORD *)&v98.m01 = v46;
  v47 = v45[7];
  *(_OWORD *)&v98.m02 = v45[6];
  *(_OWORD *)&v98.m03 = v47;
  v48 = v45[9];
  *(_OWORD *)&v97.m00 = v45[8];
  *(_OWORD *)&v97.m01 = v48;
  v49 = v45[11];
  *(_OWORD *)&v97.m02 = v45[10];
  *(_OWORD *)&v97.m03 = v49;
  op_Multiply(&v99, &v98, &v97, 0);
  v52 = *(_OWORD *)&v99.m01;
  v53 = *(_OWORD *)&v99.m02;
  v54 = *(_OWORD *)&v99.m03;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v99.m00;
  *(_OWORD *)&mtx_A.m01 = v52;
  *(_OWORD *)&mtx_A.m02 = v53;
  *(_OWORD *)&mtx_A.m03 = v54;
  vct_A = vf00;
  get_transpose(&v99, &mtx_A, 0);
  v102 = vct_A;
  v98 = v99;
  v100 = op_Multiply_60923920(&v98, v102, 0);
  vct_A = v100;
  if (((s64)workdata[1].monitor & 8) != 0)
    goto LABEL_117;
  v56 = HIDWORD(workdata[4].klass);
  if ((u32)(v56 - 10) > 0xFFFFFFF9)
  {
    v86 = *(sdfVector4_t *)(*((u64 *)workdata[3].monitor + 7) + 80);
  }
  else
  {
    if (v56 != 16)
      goto LABEL_117;
    v57 = *((_OWORD **)workdata[3].monitor + 6);
    v86 = (struct sdfVector4_t)v57[1];
    goto LABEL_113;
  }
  goto LABEL_114;
LABEL_113:
  vct_B = v86;
LABEL_115:
  goto LABEL_116;
LABEL_114:
  vct_B = v86;
  goto LABEL_115;
LABEL_116:
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_117:
  v62 = &vf00.x;
  x = v62[4];
  y = v62[5];
  z = v62[6];
  w = v62[7];
  v63 = aPtr->poseset;
  v65 = v63->scl;
  v63->workscl = v65;
  aPtr->poseset->workrot = aPtr->poseset->rot;
  aPtr->poseset->workpos = aPtr->poseset->pos;
  v66 = aPtr->poseset;
  p_pos = &v66->pos;
  v15 = 0;
  *p_pos = vct_A;
  vct_A_local = v92;
  aPtr->poseset->flag &= ~1u;
  if (HIDWORD(workdata[1].monitor) != 1)
    return 1;
LABEL_126:
  klass = workdata[2].klass;
  if (!klass)
    goto LABEL_140;
  if (klass->klass->_2.naturalAligment < (u32)v69 || klass->klass->_2.typeHierarchy[v69 - 1] != effHandle_t)
  {
    goto LABEL_171;
  }
  if ((v15 & 1) == 0)
  {
    v93 = vct_A_local;
    v103.x = x;
    v103.y = y;
    v103.z = z;
    v103.w = w;
    dds3EffectSetPosition(klass, v103);
    vct_A = (struct sdfVector4_t)v93;
    ToMatrix();
    v72 = &vf00.x;
    v73 = v72[5];
    *(_OWORD *)&v94.m00 = v72[4];
    *(_OWORD *)&v94.m01 = v73;
    v74 = v72[7];
    *(_OWORD *)&v94.m02 = v72[6];
    *(_OWORD *)&v94.m03 = v74;
    dds3EffectSetRotateMatrix(klass, &v94);
    goto LABEL_140;
  }
LABEL_140:
  if (dds3EffectGetState(klass))
    return 1;
  v75 = workdata[1].monitor;
  LODWORD(workdata[1].monitor) = v75 & 0xFFFFFFFE;
  if ((v75 & 2) != 0)
  {
    dds3SceneBasicDelete(aPtr);
  }
  return 1;
}

// 0x22f7090
bool dds3EffectObjectBasicDrawProcedure(dds3Basic_t *aPtr) {
  void *workdata;
  s64 naturalAligment;
  s64 v5;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = aPtr;
  workdata = aPtr->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3EffectObjectBasicWorkData_t)
    {
      goto LABEL_15;
    }
  }
  if (!dds3ObjectBaseCheckFlag(pObjectBasic, 1) && HIDWORD(workdata[1].monitor) == 1)
  {
    workdata = workdata[2].klass;
    if (workdata)
    {
      if (workdata->klass->_2.naturalAligment >= (u32)v5 && (effHandle_t *)workdata->klass->_2.typeHierarchy[v5 - 1] == effHandle_t)
      {
        dds3EffectDraw(workdata);
        return 1;
      }
LABEL_15:
    }
  }
  return 1;
}

// 0x22f5f10
static void FreeEffectData(dds3EffectObjectBasicWorkData_t *work) {
  dds3EffectObjectBasicWorkData_t *v3;
  effHandle_t *handle;
  dds3EffectObjectBasicWorkData_t *v6;
  Il2CppObject **p_handle;

  v3 = work;
  if (work)
  {
    if (v3->type == 1)
    {
      handle = v3->handle;
      if (handle)
      {
        Delete(handle);
        v6 = work;
        v6->handle = 0;
        v3 = work;
      }
    }
    v3->handle = 0;
    p_handle = &v3->handle;
    *((u32 *)p_handle - 1) = 0;
  }
}

// 0x22f71c0
dds3ObjectBaseControlWorkData_t *dds3EffectObjectBasicGetControlWorkData(dds3Basic_t *pBasic) {
  dds3ObjectBaseControlWorkData_t *result;

  result = (dds3ObjectBaseControlWorkData_t *)pBasic->workdata;
  if (result)
  {
    return *(dds3ObjectBaseControlWorkData_t *)&result->flag;
  }
  return result;
}

// 0x22f7240
dds3Basic_t *dds3EffectObjectBasicAdd(u32 serialID, const sdfVector4_t *aPos, const sdfVector4_t *aRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  dds3Basic_t *result;
  dds3Basic_t *v16;
  dds3PoseSet_t *poseset;
  char v19;
  dds3PoseSet_t *v20;
  struct sdfVector4_t scl;
  void *workdata;
  void **p_monitor;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v29;

  w = aRot->w;
  z = aRot->z;
  y = aRot->y;
  x = aRot->x;
  v8 = aPos->w;
  v9 = aPos->z;
  v10 = aPos->y;
  v11 = aPos->x;
  result = dds3SceneBasicAdd(7);
  pObjectBasic = result;
  if (!result)
    return result;
  result->serialID = serialID;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v29.x = v11;
  v29.y = v10;
  v29.z = v9;
  v29.w = v8;
  dds3SetPosPoseSet(pObjectBasic, v29);
  v16 = pObjectBasic;
  poseset = pObjectBasic->poseset;
  poseset->flag = poseset->flag & 0xFFFFFFFC | 1;
  poseset->rot.x = x;
  poseset->rot.y = y;
  v19 = byte_5759874;
  poseset->rot.z = z;
  poseset->rot.w = w;
  if ((v19 & 1) == 0)
  {
    v20 = v16->poseset;
    scl = v20->scl;
    goto LABEL_14;
  }
  v20 = v16->poseset;
  scl = v20->scl;
LABEL_14:
  v20->workscl = scl;
  v16->poseset->workrot = v16->poseset->rot;
  v16->poseset->workpos = v16->poseset->pos;
  workdata = pObjectBasic->workdata;
  workdata[1].monitor = 0;
  workdata[2].klass = 0;
  workdata[3].monitor = 0;
  p_monitor = &workdata[3].monitor;
  result = pObjectBasic;
  *((u16 *)p_monitor + 4) = 0;
  *((u32 *)p_monitor + 3) = 0;
  return result;
}

// 0x22f74d0
static dds3Basic_t *AddD3PEffect(effHandle_t *eff, const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  u32 v17;
  u32 v19;
  dds3Basic_t *v20;
  f32 *p_x;
  f32 *v23;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  void *workdata;
  s64 naturalAligment;
  void **p_monitor;
  void *v33;
  s64 v34;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  dds3Basic_t *FastArea;
  u64 *data;
  dds3Basic_t *v41;
  dds3Basic_t *pAreaBasic;
  dds3Basic_t *pItemBasic;
  sdfVector4_t v47;
  sdfVector4_t v48;
  sdfVector4_t v49;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v8 = pos->w;
  v9 = pos->z;
  v10 = pos->y;
  v11 = pos->x;
  pItemBasic = 0;
  pAreaBasic = 0;
  v17 = (dds3SerializeID_serialCounter + 1) & 0xFFF;
  dds3SerializeID_serialCounter = v17;
  v19 = dds3SceneBasicSearchSerialID_Used(v17);
  dds3SerializeID_serialCounter = v19;
  v47.x = v11;
  v47.y = v10;
  v47.z = v9;
  v47.w = v8;
  v49.x = x;
  v49.y = y;
  v49.z = z;
  v49.w = w;
  v20 = dds3EffectObjectBasicAdd(v19, v47, v49);
  pItemBasic = v20;
  if (!v20)
    return v20;
  p_x = &vf00.x;
  p_x[4] = v11;
  p_x[5] = v10;
  p_x[6] = v9;
  p_x[7] = v8;
  v23 = &vf00.x;
  v25 = v23[4];
  v26 = v23[5];
  v27 = v23[6];
  v28 = v23[7];
  v48.x = v25;
  v48.y = v26;
  v48.z = v27;
  v48.w = v28;
  dds3EffectSetPosition(eff, v48);
  workdata = v20->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3EffectObjectBasicWorkData_t)
    {
      v33 = v20->workdata;
      goto LABEL_46;
    }
  }
  workdata[2].klass = (Project_Basic_dds3Basic_t_WORK_c *)eff;
  workdata[1].monitor = 0x100000000LL;
  workdata[3].monitor = 0;
  p_monitor = &workdata[3].monitor;
  *((u16 *)p_monitor + 4) = 0;
  *((u32 *)p_monitor + 3) = 0;
  v33 = v20->workdata;
  if (v33->klass->_2.naturalAligment < (u32)v34 || v33->klass->_2.typeHierarchy[v34 - 1] != dds3EffectObjectBasicWorkData_t)
  {
LABEL_46:
  }
  klass = v33[1].klass;
  LODWORD(klass->_1.byval_arg.data) = 2;
  FastArea = dds3AreaBasicGetFastArea();
  pAreaBasic = FastArea;
  if (!FastArea)
    return v20;
  data = klass->_1.this_arg.data;
  v41 = FastArea;
  QueryInterface(FastArea, *(void **)(*data + 64));
  data[8] = v41;
  dds3AreaBasicRegistItem(pAreaBasic, pItemBasic);
  return pItemBasic;
}

// 0x22f7970
dds3Basic_t *dds3EffectObjectBasicAddD3P2(void *effdata, const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  effHandle_t *v14;
  sdfVector4_t v16;
  sdfVector4_t v17;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v8 = pos->w;
  v9 = pos->z;
  v10 = pos->y;
  v11 = pos->x;
  v14 = dds3EffectLoad(effdata);
  v16.z = v9;
  v16.w = v8;
  v17.x = x;
  v17.y = y;
  v17.z = z;
  v17.w = w;
  v16.x = v11;
  v16.y = v10;
  return AddD3PEffect(v14, v16, v17);
}

// 0x22f7a70
static dds3Basic_t *AddEPLEffect(effHandle_t *eff, const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  u32 v17;
  u32 v19;
  dds3Basic_t *v20;
  f32 *p_x;
  f32 *v23;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  void *workdata;
  s64 naturalAligment;
  void **p_monitor;
  void *v33;
  s64 v34;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  dds3Basic_t *FastArea;
  u64 *data;
  dds3Basic_t *v41;
  dds3Basic_t *pAreaBasic;
  dds3Basic_t *pItemBasic;
  sdfVector4_t v47;
  sdfVector4_t v48;
  sdfVector4_t v49;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v8 = pos->w;
  v9 = pos->z;
  v10 = pos->y;
  v11 = pos->x;
  pItemBasic = 0;
  pAreaBasic = 0;
  v17 = (dds3SerializeID_serialCounter + 1) & 0xFFF;
  dds3SerializeID_serialCounter = v17;
  v19 = dds3SceneBasicSearchSerialID_Used(v17);
  dds3SerializeID_serialCounter = v19;
  v47.x = v11;
  v47.y = v10;
  v47.z = v9;
  v47.w = v8;
  v49.x = x;
  v49.y = y;
  v49.z = z;
  v49.w = w;
  v20 = dds3EffectObjectBasicAdd(v19, v47, v49);
  pItemBasic = v20;
  if (!v20)
    return v20;
  p_x = &vf00.x;
  p_x[4] = v11;
  p_x[5] = v10;
  p_x[6] = v9;
  p_x[7] = v8;
  v23 = &vf00.x;
  v25 = v23[4];
  v26 = v23[5];
  v27 = v23[6];
  v28 = v23[7];
  v48.x = v25;
  v48.y = v26;
  v48.z = v27;
  v48.w = v28;
  dds3EffectSetPosition(eff, v48);
  workdata = v20->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3EffectObjectBasicWorkData_t)
    {
      v33 = v20->workdata;
      goto LABEL_46;
    }
  }
  workdata[2].klass = (Project_Basic_dds3Basic_t_WORK_c *)eff;
  workdata[1].monitor = 0x100000000LL;
  workdata[3].monitor = 0;
  p_monitor = &workdata[3].monitor;
  *((u16 *)p_monitor + 4) = 0;
  *((u32 *)p_monitor + 3) = 0;
  v33 = v20->workdata;
  if (v33->klass->_2.naturalAligment < (u32)v34 || v33->klass->_2.typeHierarchy[v34 - 1] != dds3EffectObjectBasicWorkData_t)
  {
LABEL_46:
  }
  klass = v33[1].klass;
  LODWORD(klass->_1.byval_arg.data) = 2;
  FastArea = dds3AreaBasicGetFastArea();
  pAreaBasic = FastArea;
  if (!FastArea)
    return v20;
  data = klass->_1.this_arg.data;
  v41 = FastArea;
  QueryInterface(FastArea, *(void **)(*data + 64));
  data[8] = v41;
  dds3AreaBasicRegistItem(pAreaBasic, pItemBasic);
  return pItemBasic;
}

// 0x22f7f10
dds3Basic_t *dds3EffectObjectBasicAddEPL(void *effdata, const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  effHandle_t *EPL;
  sdfVector4_t v16;
  sdfVector4_t v17;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v8 = pos->w;
  v9 = pos->z;
  v10 = pos->y;
  v11 = pos->x;
  EPL = dds3EffectLoadEPL(effdata);
  v16.z = v9;
  v16.w = v8;
  v17.x = x;
  v17.y = y;
  v17.z = z;
  v17.w = w;
  v16.x = v11;
  v16.y = v10;
  return AddEPLEffect(EPL, v16, v17);
}

// 0x22f8010
static dds3Basic_t *AddESPEffect(char *name, const sdfVector4_t *pos, const sdfVector4_t *rot, f32 r) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  u32 v18;
  u32 v20;
  dds3Basic_t *v21;
  dds3Basic_t *v22;
  f32 *poseset;
  void *workdata;
  s64 naturalAligment;
  void **p_monitor;
  void *v28;
  s64 v29;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  dds3Basic_t *FastArea;
  u64 *data;
  dds3Basic_t *v34;
  dds3Basic_t *pAreaBasic;
  dds3Basic_t *pItemBasic;
  sdfVector4_t v40;
  sdfVector4_t v41;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v9 = pos->w;
  v10 = pos->z;
  v11 = pos->y;
  v12 = pos->x;
  pItemBasic = 0;
  pAreaBasic = 0;
  v18 = (dds3SerializeID_serialCounter + 1) & 0xFFF;
  dds3SerializeID_serialCounter = v18;
  v20 = dds3SceneBasicSearchSerialID_Used(v18);
  dds3SerializeID_serialCounter = v20;
  v40.x = v12;
  v40.y = v11;
  v40.z = v10;
  v40.w = v9;
  v41.x = x;
  v41.y = y;
  v41.z = z;
  v41.w = w;
  v21 = dds3EffectObjectBasicAdd(v20, v40, v41);
  v22 = v21;
  pItemBasic = v21;
  if (!v21)
    return v22;
  v21->name = name;
  poseset = v22->poseset;
  poseset[28] = r;
  poseset[29] = r;
  poseset[30] = r;
  workdata = v22->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3EffectObjectBasicWorkData_t)
    {
      v28 = v22->workdata;
      goto LABEL_34;
    }
  }
  workdata[2].klass = 0;
  workdata[1].monitor = 0x600000000LL;
  workdata[5].klass = 0;
  workdata[3].monitor = 0;
  p_monitor = &workdata[3].monitor;
  *((u16 *)p_monitor + 4) = 0;
  *((u32 *)p_monitor + 3) = 0;
  v28 = v22->workdata;
  if (v28->klass->_2.naturalAligment < (u32)v29 || v28->klass->_2.typeHierarchy[v29 - 1] != dds3EffectObjectBasicWorkData_t)
  {
LABEL_34:
  }
  klass = v28[1].klass;
  LODWORD(klass->_1.byval_arg.data) = 2;
  FastArea = dds3AreaBasicGetFastArea();
  pAreaBasic = FastArea;
  if (!FastArea)
    return v22;
  data = klass->_1.this_arg.data;
  v34 = FastArea;
  QueryInterface(FastArea, *(void **)(*data + 64));
  data[8] = v34;
  dds3AreaBasicRegistItem(pAreaBasic, pItemBasic);
  return pItemBasic;
}

// 0x22f83b0
dds3Basic_t *dds3EffectObjectBasicAddESP(char *name, const sdfVector4_t *pos, const sdfVector4_t *rot, f32 r) {
  f32 v5;
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v24;

  v5 = r;
  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v11 = pos->w;
  v12 = pos->z;
  v13 = pos->y;
  v14 = pos->x;
  v5 = r;
  pos->x = v14;
  pos->y = v13;
  pos->z = v12;
  pos->w = v11;
  rot->x = x;
  rot->y = y;
  rot->z = z;
  rot->w = w;
  v15 = rot->w;
  v16 = rot->z;
  v24 = v5;
  v17 = rot->y;
  v18 = rot->x;
  v19 = pos->w;
  v20 = pos->z;
  v21 = pos->y;
  v22 = pos->x;
  v5 = v24;
  pos->x = v22;
  pos->y = v21;
  pos->z = v20;
  pos->w = v19;
  rot->x = v18;
  rot->y = v17;
  rot->z = v16;
  rot->w = v15;
  return AddESPEffect(name, pos, rot, v5);
}

// 0x22f84d0
dds3EffectObjectBasicWorkData_t *CheckESP(dds3Basic_t *b) {
  dds3Basic_t *v3;
  dds3EffectObjectBasicWorkData_t *result;

  v3 = b;
  if (!b || HIBYTE(v3->type) != 7)
    return 0;
  result = (dds3EffectObjectBasicWorkData_t *)v3->workdata;
  if (result->type != 6)
    return 0;
  return result;
}

// 0x22f8580
bool GetESPPos(dds3Basic_t *b) {
  dds3Basic_t *v4;
  void *workdata;
  struct sdfVector4_t pos;

  v4 = b;
  if (!b)
    return 0;
  if (HIBYTE(v4->type) != 7)
    return 0;
  workdata = v4->workdata;
  if (HIDWORD(workdata[1].monitor) != 6)
    return 0;
  pos = v4->poseset->pos;
  vct_A = pos;
  return 1;
}

// 0x22f8730
s32 GetESPR(dds3Basic_t *b) {
  dds3Basic_t *v4;
  void *workdata;
  f32 x;

  v4 = b;
  if (!b)
    return 0;
  if (HIBYTE(v4->type) != 7)
    return 0;
  workdata = v4->workdata;
  if (HIDWORD(workdata[1].monitor) != 6)
    return 0;
  x = v4->poseset->scl.x;
  if (x == INFINITY)
    return 0x80000000;
  else
    return (s32)x;
}

// 0x22f8870
void dds3EffectObjectBasicStatOn(dds3Basic_t *basic, u32 s) {
  void *workdata;

  if (basic)
  {
    workdata = basic->workdata;
    LODWORD(workdata[1].monitor) |= s;
  }
}

// 0x22f8910
void dds3EffectObjectBasicStatOff(dds3Basic_t *basic, u32 s) {
  void *workdata;

  if (basic)
  {
    workdata = basic->workdata;
    LODWORD(workdata[1].monitor) &= ~s;
  }
}

// 0x22f89b0
bool dds3EffectObjectBasicLinkObject(dds3Basic_t *basic, dds3Basic_t *target) {
  dds3Basic_t *v5;
  u32 type_high;
  void *workdata;
  void **p_monitor;
  dds3Basic_t *v11;

  v5 = target;
  type_high = HIBYTE(target->type);
  if (type_high - 4 >= 6 && type_high != 16)
    return 0;
  workdata = basic->workdata;
  workdata[3].monitor = v5;
  p_monitor = &workdata[3].monitor;
  *((u32 *)p_monitor - 8) = *(u32 *)(p_monitor - 4) & 0xFFFFFFF3 | 4;
  v11 = target;
  *((u16 *)p_monitor + 4) = 0;
  *((u32 *)p_monitor - 2) = 0;
  LODWORD(v11) = HIBYTE(v11->type);
  *(p_monitor - 2) = 0;
  *((u32 *)p_monitor + 3) = (u32)v11;
  return 1;
}

// 0x22f6f00
void dds3EffectObjectBasicGetObjectIndex(dds3Basic_t *basic) {
  void *workdata;

  workdata = basic->workdata;
}

// 0x22f8ab0
s32 dds3EffectObjectBasicLinkObjectIndex(dds3Basic_t *basic, dds3Basic_t *target, s32 index) {
  s16 v4;
  void *workdata;
  s32 monitor;

  v4 = index;
  if (!dds3EffectObjectBasicLinkObject(basic, target))
    return 1;
  workdata = basic->workdata;
  monitor = workdata[1].monitor;
  LOWORD(workdata[4].klass) = v4;
  LODWORD(workdata[1].monitor) = monitor | 8;
  return 1;
}

// 0x22f6fe0
void dds3EffectObjectBasicUnlinkObject(dds3Basic_t *basic) {
  void *workdata;
  void **p_monitor;

  workdata = basic->workdata;
  workdata[3].monitor = 0;
  p_monitor = &workdata[3].monitor;
  *((u32 *)p_monitor - 8) &= 0xFFFFFFF3;
  *((u32 *)p_monitor + 3) = 0;
  *((u16 *)p_monitor + 4) = 0;
}
