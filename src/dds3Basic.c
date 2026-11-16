#include "types.h"
#include "basic.h"
#include "dds3basic.h"
#include "dds3scenebasic.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;

static dds3BasicFunction_t *basicfunctiontable[17];
u32 dds3SerializeID_serialCounter;

// 0x22f0dc0
void dds3GetSclPoseSetMCR(dds3Basic_t *_pBasic) {
  struct sdfVector4_t scl;

  scl = pBasic->poseset->scl;
  vct_A = scl;
}

// 0x22f0e90
void dds3GetPos2PoseSetMCR(dds3Basic_t *_pBasic) {
  struct sdfVector4_t pos2;

  pos2 = pBasic->poseset->pos2;
  vct_A = pos2;
  vct_A.w = 1.0;
}

// 0x22f0fc0
void dds3GetPosPoseSetMCR(dds3Basic_t *_pBasic) {
  struct sdfVector4_t pos;

  pos = pBasic->poseset->pos;
  vct_A = pos;
  vct_A.w = 1.0;
}

// 0x22f10f0
void dds3GetRotPoseSetMCR(dds3Basic_t *_pBasic) {
  struct sdfVector4_t rot;

  rot = pBasic->poseset->rot;
  vct_A = rot;
  Normalize();
}

// 0x22f11d0
dds3Basic_t *dds3Add(BASIC_TYPE type) {
  Il2CppObject *v3;
  Il2CppClass *v4;
  dds3BasicFunction_t *v6;
  s64 v7;

  if (type > 16)
    return 0;
  v3 = Allocate(dds3Basic_t);
  v4 = NewSpecific(uint, 3u);
  v3[7].klass = v4;
  _ctor(v3, 0);
  v3[1].monitor = 0;
  v3[1].klass = 0;
  LODWORD(v3[2].klass) = type << 24;
  v6 = basicfunctiontable[type];
  v3[2].monitor = v6;
  v3[3].klass = 0;
  v3[3].monitor = 0;
  v3[4].klass = 0;
  v3[4].monitor = 0;
  v3[5].klass = 0;
  v3[5].monitor = 0;
  v3[6].klass = 0;
  LODWORD(v3[6].monitor) = -2139062144;
  if (v3[2].monitor)
  {
    v7 = *((u64 *)v3[2].monitor + 2);
    if (v7)
    {
      if (((*(v7 + 24))(*(u64 *)(v7 + 64), v3, *(u64 *)(v7 + 40)) & 1) == 0)
      {
        dds3Delete(v3);
        return 0;
      }
    }
  }
  return (dds3Basic_t *)v3;
}

// 0x22f1430
void dds3Delete(dds3Basic_t *basic) {
  dds3BasicFunction_t *basicfunction;
  void *destructor;
  dds3Basic_t *prev;
  dds3Basic_t *next;
  dds3Basic_t *v7;
  dds3Basic_t *v8;

  if (basic)
  {
    basicfunction = basic->basicfunction;
    if (basicfunction)
    {
      destructor = basicfunction->destructor;
      if (destructor)
        (destructor->invoke_impl)(destructor->method_code, basic, destructor->method);
    }
    prev = basic->prev;
    if (prev)
    {
      next = basic->next;
      prev->next = next;
    }
    v7 = basic->next;
    if (v7)
    {
      v8 = basic->prev;
      v7->prev = v8;
    }
  }
}

// 0x22f14b0
bool dds3InitPoseSet(dds3Basic_t *basic) {
  dds3PoseSet_t *v4;
  sdfVector4_t *v7;
  dds3Basic_t *v9;
  dds3PoseSet_t *pPoseSet;

  if (!basic)
    return 0;
  if (basic->poseset)
    return 0;
  v4 = Allocate(dds3PoseSet_t);
  pPoseSet = v4;
  if (!v4)
    return 0;
  v4->flag = 1;
  dds3InitPoseSetValue(pPoseSet);
  v7 = &v4->plane;
  *(u32 *)&v4->r = 0;
  *(u32 *)&v4->frameFall = 0;
  *v7 = vf00;
  v9 = basic;
  v9->poseset = v4;
  return 1;
}

// 0x22f1820
void dds3FreePoseSet(dds3Basic_t *basic) {
  dds3Basic_t *v2;
  dds3PoseSet_t *p_poseset;
  dds3PoseSet_t *poseset;

  v2 = basic;
  if (v2)
  {
    poseset = v2->poseset;
    p_poseset = &v2->poseset;
    if (poseset)
    {
      p_poseset = 0;
    }
  }
}

// 0x22f1840
void dds3OnPoseSetFlag(dds3PoseSet_t *pPoseSet, u32 flag) {
  pPoseSet->flag |= flag;
}

// 0x22f1860
void dds3OffPoseSetFlag(dds3PoseSet_t *pPoseSet, u32 flag) {
  pPoseSet->flag &= ~flag;
}

// 0x22f1880
bool dds3CheckPoseSetFlag(dds3PoseSet_t *pPoseSet, u32 flag) {
  return (pPoseSet->flag & flag) != 0;
}

// 0x22f1630
void dds3InitPoseSetValue(dds3PoseSet_t *pPoseSet) {
  dds3PoseSet_t *v4;
  sdfVector4_t *p_pos;
  sdfVector4_t *p_rot;
  dds3PoseSet_t *v10;

  v4 = pPoseSet;
  p_pos = &v4->pos;
  goto LABEL_5;
LABEL_12:
  *p_rot = vf00;
  goto LABEL_15;
LABEL_5:
  *p_pos = vf00;
  p_rot = &pPoseSet->rot;
  goto LABEL_12;
LABEL_15:
  vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
  v10 = pPoseSet;
  v10->scl = vct_A;
}

// 0x22f18a0
void dds3BackupPoseSet(dds3PoseSet_t *pPoseSet) {
  dds3PoseSet_t *v3;
  struct sdfVector4_t scl;
  struct sdfVector4_t v5;

  v3 = pPoseSet;
  scl = pPoseSet->scl;
  v5 = pPoseSet->scl;
  scl = v5;
  v3->workscl = scl;
  pPoseSet->workrot = pPoseSet->rot;
  pPoseSet->workpos = pPoseSet->pos;
}

// 0x22f1930
void dds3SetRadiusPoseSet(dds3Basic_t *pBasic, f32 radius) {
  pBasic->poseset->r = radius;
}

// 0x22f1940
f32 dds3GetRadiusPoseSet(dds3Basic_t *pBasic) {
  return pBasic->poseset->r;
}

// 0x22f1950
void dds3SetPosPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  dds3Basic_t *v8;
  dds3PoseSet_t *poseset;
  void *workdata;
  dds3Basic_t *v13;
  sdfVector4_t v15;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v8 = pBasic;
  poseset = pBasic->poseset;
  if (poseset || HIBYTE(v8->type) != 5)
    goto LABEL_9;
  workdata = v8->workdata;
  if (workdata[2].klass)
  {
    v13 = sub_83F0(workdata, Project_Basic_dds3UnitObjectBasicWorkData_t, *(long f64 *)&pos);
    dds3SetRotPoseSet(v13, v15);
  }
  else
  {
LABEL_9:
    poseset->flag = poseset->flag & 0xFFFFFFFC | 1;
    poseset->pos.z = z;
    poseset->pos.w = w;
    poseset->pos.x = x;
    poseset->pos.y = y;
  }
}

// 0x22f1a50
void dds3SetRotPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  dds3PoseSet_t *poseset;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  poseset = pBasic->poseset;
  poseset->flag = poseset->flag & 0xFFFFFFFC | 1;
  poseset->rot.z = z;
  poseset->rot.w = w;
  poseset->rot.x = x;
  poseset->rot.y = y;
}

// 0x22f1af0
void dds3SetSclPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *scl) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  dds3PoseSet_t *poseset;

  w = scl->w;
  z = scl->z;
  y = scl->y;
  x = scl->x;
  poseset = pBasic->poseset;
  poseset->flag = poseset->flag & 0xFFFFFFFC | 1;
  poseset->scl.z = z;
  poseset->scl.w = w;
  poseset->scl.x = x;
  poseset->scl.y = y;
}

// 0x22f1b90
void dds3GetPosPoseSet(dds3Basic_t *pBasic) {
  dds3Basic_t *v4;

  v4 = pBasic;
  dds3GetPosPoseSetMCR(v4);
}

// 0x22f1c10
void dds3GetRotPoseSet(dds3Basic_t *pBasic) {
  dds3Basic_t *v4;

  v4 = pBasic;
  dds3GetRotPoseSetMCR(v4);
}

// 0x22f1c90
void dds3GetSclPoseSet(dds3Basic_t *pBasic) {
  struct sdfVector4_t scl;

  scl = pBasic->poseset->scl;
  vct_A = scl;
}

// 0x22f1dd0
void dds3AddPosPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_pos;
  struct sdfVector4_t v11;
  f32 *p_x;
  struct sdfVector4_t v15;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  poseset = pBasic->poseset;
  v11 = poseset->pos;
  p_pos = &poseset->pos;
  v15 = v11;
  LODWORD(p_pos[8].x) = LODWORD(p_pos[8].x) & 0xFFFFFFFC | 1;
  vct_A = v15;
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = y;
  p_x[10] = z;
  p_x[11] = w;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  *p_pos = vct_A;
}

// 0x22f1fe0
void dds3AddRotPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_rot;
  struct sdfVector4_t v11;
  f32 *p_x;
  struct sdfVector4_t v15;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  poseset = pBasic->poseset;
  v11 = poseset->rot;
  p_rot = &poseset->rot;
  v15 = v11;
  LODWORD(p_rot[7].x) = LODWORD(p_rot[7].x) & 0xFFFFFFFC | 1;
  vct_A = v15;
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = y;
  p_x[10] = z;
  p_x[11] = w;
  Mult();
  *p_rot = vct_A;
}

// 0x22f21a0
void dds3AddSclPoseSet(dds3Basic_t *pBasic, const sdfVector4_t *scl) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_scl;
  struct sdfVector4_t v11;
  f32 *p_x;
  struct sdfVector4_t v15;

  w = scl->w;
  z = scl->z;
  y = scl->y;
  x = scl->x;
  poseset = pBasic->poseset;
  v11 = poseset->scl;
  p_scl = &poseset->scl;
  v15 = v11;
  LODWORD(p_scl[6].x) = LODWORD(p_scl[6].x) & 0xFFFFFFFC | 1;
  vct_A = v15;
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = y;
  p_x[10] = z;
  p_x[11] = w;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  *p_scl = vct_A;
}

// 0x22f23b0
void dds3MakeMatrix(const sdfVector4_t *scale, const sdfVector4_t *quaternion, const sdfVector4_t *transrate) {
  f32 x;
  f32 w;
  f32 z;
  f32 y;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v16;
  s64 v19;
  s64 v20;

  x = scale->x;
  w = quaternion->w;
  z = quaternion->z;
  y = quaternion->y;
  v8 = quaternion->x;
  v9 = scale->w;
  v10 = scale->z;
  v11 = scale->y;
  p_x = &vf00.x;
  p_x[4] = v8;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  ToMatrix();
  v16 = &vf00.x;
  v16[4] = x;
  v16[5] = v11;
  v16[6] = v10;
  v16[7] = v9;
  sub_197D730(0);
  *(u64 *)&vct_A.x = v19;
  *(u64 *)&vct_A.z = v20;
  vct_A.w = 1.0;
  SetRow(&mtx_A, 3, vct_A, 0);
}

// 0x22f2630
void dds3GetTMPoseSet(dds3Basic_t *pBasic) {
  dds3PoseSet_t *poseset;
  u32 flag;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  _OWORD *p_m00;
  _OWORD *p_x;
  __int128 v17;
  __int128 v18;
  __int128 v19;
  __int128 *p_fields;
  _OWORD *v22;
  f32 v23;
  f32 v24;
  __int128 v25;
  __int128 v26;
  __int128 v27;
  __int128 v28;
  f32 v29;
  f32 v30;
  sdfVector4_t v31;
  sdfVector4_t scl;
  sdfVector4_t v33;

  poseset = pBasic->poseset;
  flag = poseset->flag;
  if ((flag & 2) == 0)
  {
    poseset->flag = flag | 2;
    scl = poseset->scl;
    x = poseset->rot.x;
    y = poseset->rot.y;
    z = poseset->rot.z;
    w = poseset->rot.w;
    v29 = poseset->scl.y;
    v30 = poseset->scl.x;
    v23 = poseset->scl.w;
    v24 = poseset->scl.z;
    scl.w = v23;
    scl.z = v24;
    scl.y = v29;
    scl.x = v30;
    v33.x = x;
    v33.y = y;
    v33.z = z;
    v33.w = w;
    *(u64 *)&v31.z = method;
    dds3MakeMatrix(scl, v33, v31);
    p_m00 = &poseset->workTM.m00;
    p_x = &vf00.x;
    v17 = p_x[5];
    v18 = p_x[6];
    v19 = p_x[7];
    *p_m00 = p_x[4];
    p_m00[1] = v17;
    p_m00[2] = v18;
    p_m00[3] = v19;
    return;
  }
  p_fields = &poseset->fields;
  v25 = *p_fields;
  v26 = p_fields[1];
  v27 = p_fields[2];
  v28 = p_fields[3];
  v22 = &vf00.x;
  v22[4] = v25;
  v22[5] = v26;
  v22[6] = v27;
  v22[7] = v28;
}

// 0x22f2840
bool dds3RadiusCheckPoseSet(dds3PoseSet_t *p1, dds3PoseSet_t *p2) {
  struct sdfVector4_t v7;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  struct sdfVector4_t pos;

  pos = p1->pos;
  vct_A = pos;
  v7 = p2->pos;
  vct_B = v7;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  return (f32)(fabsf(sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z))) - (f32)(p1->r + p2->r)) < 0.0;
}

// 0x22f2ae0
bool dds3RadiusCheckPoseSet2(dds3PoseSet_t *p1, dds3PoseSet_t *p2) {
  struct sdfVector4_t v7;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  struct sdfVector4_t pos;

  pos = p1->pos;
  vct_A = pos;
  v7 = p2->pos;
  vct_B = v7;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  return (f32)(fabsf(sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z))) - p2->r) < 0.0;
}

// 0x22f2d70
bool dds3CallMainProcuder(dds3Basic_t *basic) {
  dds3BasicFunction_t *basicfunction;
  void *mainprocuder;

  return !basic
      || (basicfunction = basic->basicfunction) == 0
      || (mainprocuder = basicfunction->mainprocuder) == 0
      || (mainprocuder->invoke_impl)(mainprocuder->method_code, basic, mainprocuder->method);
}

// 0x22f2da0
bool dds3CallDrawProcuder(dds3Basic_t *basic) {
  dds3BasicFunction_t *basicfunction;
  void *drawprocuder;

  return !basic
      || (basicfunction = basic->basicfunction) == 0
      || (drawprocuder = basicfunction->drawprocuder) == 0
      || (drawprocuder->invoke_impl)(drawprocuder->method_code, basic, drawprocuder->method);
}

// 0x22f2dd0
u32 dds3SerializeID(void) {
  u32 v4;
  u32 result;

  v4 = (dds3SerializeID_serialCounter + 1) & 0xFFF;
  dds3SerializeID_serialCounter = v4;
  result = dds3SceneBasicSearchSerialID_Used(v4);
  dds3SerializeID_serialCounter = result;
  return result;
}

// 0x22f2e80
void dds3SetBasicName(dds3Basic_t *basic, char *name) {
  if (basic)
  {
    basic->name = name;
  }
}

// 0x22f2e90
char *dds3GetBasicName(dds3Basic_t *basic) {
  if (basic)
    return basic->name;
  else
    return 0;
}
