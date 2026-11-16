#include "types.h"
#include "aw.h"
#include "aw_camlockon.h"
#include "aw_camlockonout.h"
#include "dds3vrf.h"
#include "ditectivebook.h"
#include "rspecialskill.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"

#define gCameraLockOnMark_Max 5
#define gCameraLockOnMark_ZanFrame 24
#define gCameraLockOnMark_AnimFrame_On 20
#define gCameraLockOnMark_AnimFrame_Off 32

typedef struct AW_WORK_t AW_WORK_t;

static f32 gCameraLockOnMark_ZanSt[5];
static bool gCameraLockOnMark_Use;
static bool gCameraLockOnMark_Cng;
static sdfVector3_t *gCameraLockOnMark_Pos3D;
static f32 *gCameraLockOnMark_Pos3D_Time;
static sdfVector3_t gCameraLockOnMark_Pos3D_Old;
static bool *gCameraLockOnMark_ZanUse;
static s32 gAwIdx;
static s32 *gAwIdx_OutSide;

static void Clear(void);

// 0x1e310d0
void Init(void) {
  Clear(AW_CamLockon);
}

// 0x1e31140
static void Clear(void) {
  s32 *gAwIdx_OutSide_local;
  sdfVector3_t *gCameraLockOnMark_Pos3D_local;
  f32 *gCameraLockOnMark_Pos3D_Time_local;

  gAwIdx = -1;
  gAwIdx_OutSide_local = gAwIdx_OutSide;
  *(u16 *)&gCameraLockOnMark_Use = 0;
  *(u64 *)gAwIdx_OutSide_local = -1;
  *(u64 *)&gAwIdx_OutSide_local[2] = -1;
  gCameraLockOnMark_Pos3D_local = gCameraLockOnMark_Pos3D;
  gCameraLockOnMark_Pos3D_Time_local = gCameraLockOnMark_Pos3D_Time;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[0].x = 0;
  gCameraLockOnMark_Pos3D_local[0].z = 0.0;
  gCameraLockOnMark_Pos3D_Time_local[0] = 0.0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[1].x = 0;
  gCameraLockOnMark_Pos3D_local[1].z = 0.0;
  gCameraLockOnMark_Pos3D_Time_local[1] = 0.0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[2].x = 0;
  gCameraLockOnMark_Pos3D_local[2].z = 0.0;
  gCameraLockOnMark_Pos3D_Time_local[2] = 0.0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[3].x = 0;
  gCameraLockOnMark_Pos3D_local[3].z = 0.0;
  gCameraLockOnMark_Pos3D_Time_local[3] = 0.0;
  *(u32 *)gCameraLockOnMark_ZanUse = 0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[4].x = 0;
  gCameraLockOnMark_Pos3D_local[4].z = 0.0;
  gCameraLockOnMark_Pos3D_Time_local[4] = 0.0;
  gCameraLockOnMark_ZanUse[4] = 0;
}

// 0x1e31310
s32 Add(void) {
  s32 result;

  Add_2(4);
  Add_2(3);
  Add_2(2);
  Add_2(1);
  result = Add_2(0);
  gAwIdx = result;
  return result;
}

// 0x1e313a0
s32 Add_2(s32 _SubIdx) {
  void *AwParentImage;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *transform;
  Il2CppObject *v12;
  AW_Func v13;
  AW_Func v15;
  s32 v18;
  AW_WORK_t *v26;
  s32 v29;
  s32 *v31;
  s32 v32;
  s32 *v34;
  s32 v35;
  s32 *v37;
  char *v38;
  sdfVector3_t v40;
  sdfQuaternion_t v41;

  AwParentImage = get_Instance(0)->AwParentImage;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 4, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  transform = get_transform(AwParentImage, 0);
  v40.x = 0.0;
  v40.y = 0.0;
  v40.z = 0.0;
  v41.x = x;
  v41.y = y;
  v41.z = z;
  v41.w = w;
  v12 = Instantiate_object__39505040(AwPrefab, v40, v41, transform);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0);
  v18 = Add(301, 0.0, 0.0, 0.0, v12, v13, v15, 3);
  Set_AnimObj(v18, 0, "camlockon_0");
  Set_AnimObj(v18, 1, "camlockon_1");
  Set_AnimObj(v18, 2, "camlockon_zan1");
  Set_AnimObj(v18, 3, "camlockon_zan2");
  Set_AnimObj(v18, 4, "camlockon_zan3");
  Set_AnimObj(v18, 5, "camlockon_zan4");
  v26 = gWork[v18];
  v26->SubIdx = SubIdx;
  v26->Step = 0;
  if (SubIdx)
  {
    if ((u32)(SubIdx - 5) >= 0xFFFFFFFC)
    {
      v26->Dir = 0.0;
      v26->AnimStep = 0;
      v26->AnimIdx = -1;
      v26->AnimTime = 0.0;
    }
  }
  else
  {
    v26->Dir = 0.0;
    v26->AnimStep = 0;
    v26->AnimIdx = 0;
    v26->AnimTime = 0.0;
    v29 = AW_CamLockonAdd(0);
    gAwIdx_OutSide[0] = v29;
    v31 = gAwIdx_OutSide;
    v32 = AW_CamLockonAdd(1);
    v31[1] = v32;
    v34 = gAwIdx_OutSide;
    v35 = AW_CamLockonAdd(2);
    v34[2] = v35;
    v37 = gAwIdx_OutSide;
    v37[3] = AW_CamLockonAdd(3);
  }
  v38 = "AW_CamLockon";
  v26->DbgStr = "AW_CamLockon";
  return v18;
}

// 0x1e317a0
void DeleteAll(void) {
  AW_CamLockonDeleteAll();
  DelAW_ID(301, 1);
  Clear(AW_CamLockon);
}

// 0x1e31850
void Cng(void) {
  AW_WORK_t *v5;
  sdfVector3_t *gCameraLockOnMark_Pos3D_local;

  if (gAwIdx == -1)
    return;
  v5 = gWork[gAwIdx];
  if (v5->Step != 20)
  {
    v5->AnimStep = 0;
    v5->Step = 10;
    v5->AnimIdx = 0;
    gCameraLockOnMark_Pos3D_local = gCameraLockOnMark_Pos3D;
    gCameraLockOnMark_Cng = 1;
    *(u64 *)&gCameraLockOnMark_Pos3D_Old.x = *(u64 *)&gCameraLockOnMark_Pos3D_local[0].x;
    gCameraLockOnMark_Pos3D_Old.z = gCameraLockOnMark_Pos3D_local[0].z;
    gCameraLockOnMark_Pos3D_Time[0] = 0.0;
    v5->AnimTime = 0.0;
  }
}

// 0x1e319f0
void Cng2(void) {
  sdfVector3_t *gCameraLockOnMark_Pos3D_local;
  AW_WORK_t *v9;

  if (gAwIdx == -1)
    return;
  gCameraLockOnMark_Pos3D_local = gCameraLockOnMark_Pos3D;
  gCameraLockOnMark_Cng = 0;
  *(u64 *)&gCameraLockOnMark_Pos3D_Old.x = *(u64 *)&gCameraLockOnMark_Pos3D_local[0].x;
  gCameraLockOnMark_Pos3D_Old.z = gCameraLockOnMark_Pos3D_local[0].z;
  gCameraLockOnMark_Pos3D_Time[0] = 0.0;
  v9 = gWork[gAwIdx];
  v9->Step = 20;
  v9->AnimStep = 0;
  v9->AnimIdx = 0;
  v9->AnimTime = 0.0;
  return;
}

// 0x1e31b60
void Cng3(void) {
  sdfVector3_t *gCameraLockOnMark_Pos3D_local;
  AW_WORK_t *v9;

  if (gAwIdx == -1)
    return;
  gCameraLockOnMark_Pos3D_local = gCameraLockOnMark_Pos3D;
  gCameraLockOnMark_Cng = 0;
  *(u64 *)&gCameraLockOnMark_Pos3D_Old.x = *(u64 *)&gCameraLockOnMark_Pos3D_local[0].x;
  gCameraLockOnMark_Pos3D_Old.z = gCameraLockOnMark_Pos3D_local[0].z;
  gCameraLockOnMark_Pos3D_Time[0] = FPS60 * 32.0;
  v9 = gWork[gAwIdx];
  v9->Step = 30;
  v9->AnimStep = 0;
  v9->AnimIdx = 0;
  v9->AnimTime = 0.0;
  return;
}

// 0x1e31cf0
void SetTargetDead(void) {
  AW_WORK_t *v5;

  if (gAwIdx == -1)
    return;
  v5 = gWork[gAwIdx];
  if (v5->Step)
    return;
  v5->Step = 1;
  gCameraLockOnMark_Pos3D_Time[0] = FPS60
                                                              * 32.0;
}

// 0x1e31ea0
void SetTargetDeadSkill(const sdfVector3_t *_Pos3D) {
  f32 z;
  f32 y;
  f32 x;
  AW_WORK_t *v11;

  z = Pos3D->z;
  y = Pos3D->y;
  x = Pos3D->x;
  if (gAwIdx == -1)
    return;
  v11 = gWork[gAwIdx];
  if (v11->Step)
  {
LABEL_14:
    gCameraLockOnMark_Pos3D[8] = x;
    gCameraLockOnMark_Pos3D[9] = y;
    gCameraLockOnMark_Pos3D[10] = z;
    return;
  }
  else
  {
    v11->Step = 1;
    gCameraLockOnMark_Pos3D_Time[0] = FPS60
                                                                 * 32.0;
    goto LABEL_14;
  }
  goto LABEL_14;
}

// 0x1e32090
void OnVisible(const sdfVector3_t *_Pos3D) {
  f32 z;
  f32 y;
  f32 x;
  struct AW_CamLockon *static_fields;
  AW_WORK_t *v11;
  s32 Step;
  sdfVector3_t *v17;
  float32x2_t v18;
  f32 v19;
  f32 v20;
  float32x2_t v21;
  f32 v22;
  f32 v23;
  float32x2_t *v28;
  f32 v29;
  float32x2_t v30;
  f32 v31;
  float32x2_t v32;
  f32 v33;
  f32 v34;
  sdfVector3_t *v37;
  float32x2_t v38;
  f32 v39;
  f32 v40;
  float32x2_t v41;
  f32 v42;
  f32 v43;
  bool *v46;
  float32x2_t *v48;
  f32 v49;
  f32 v50;
  f32 v51;
  float32x2_t v52;
  float32x2_t v53;
  bool *v56;

  z = Pos3D->z;
  y = Pos3D->y;
  x = Pos3D->x;
  gCameraLockOnMark_Use = 1;
  gCameraLockOnMark_Pos3D[8] = x;
  gCameraLockOnMark_Pos3D[9] = y;
  gCameraLockOnMark_Pos3D[10] = z;
  if ((u32)static_fields)
  {
    goto LABEL_7;
  }
LABEL_7:
  v11 = gWork[gAwIdx];
  Step = v11->Step;
  if ((u32)(Step - 30) < 2)
  {
    v11->Step = 31;
  }
  else if ((u32)(Step - 20) > 1)
  {
    v11->Step = 0;
    if (gCameraLockOnMark_Cng)
    {
      gCameraLockOnMark_Cng = 0;
      v17 = gCameraLockOnMark_Pos3D;
      v18.n64_u64[0] = *(u64 *)&gCameraLockOnMark_Pos3D_Old.x;
      v19 = gCameraLockOnMark_ZanSt[1];
      if (v19 <= 1.0)
        v20 = gCameraLockOnMark_ZanSt[1];
      else
        v20 = 1.0;
      v21.n64_u64[0] = vsub_f32(*(float32x2_t *)&v17[0].x, v18).n64_u64[0];
      if (v19 >= 0.0)
        v22 = v20;
      else
        v22 = 0.0;
      v23 = gCameraLockOnMark_Pos3D_Old.z
          + (f32)((f32)(v17[0].z - gCameraLockOnMark_Pos3D_Old.z) * v22);
      *(float32x2_t *)&v17[1].x = vadd_f32(v18, vmul_n_f32(v21, v22));
      v17[1].z = v23;
      gCameraLockOnMark_Pos3D_Time[1] = 0.0;
      gCameraLockOnMark_ZanUse[1] = 1;
      v28 = gCameraLockOnMark_Pos3D;
      v29 = gCameraLockOnMark_Pos3D_Old.z;
      v30.n64_u64[0] = *(u64 *)&gCameraLockOnMark_Pos3D_Old.x;
      v31 = gCameraLockOnMark_ZanSt[2];
      v32.n64_u64[0] = vsub_f32(v28[4], v30).n64_u64[0];
      if (v31 <= 1.0)
        v33 = gCameraLockOnMark_ZanSt[2];
      else
        v33 = 1.0;
      if (v31 < 0.0)
        v33 = 0.0;
      v34 = (f32)(v28[5].n64_f32[0] - v29) * v33;
      v28[7].n64_u64[0] = vadd_f32(v30, vmul_n_f32(v32, v33)).n64_u64[0];
      v28[8].n64_f32[0] = v29 + v34;
      gCameraLockOnMark_Pos3D_Time[2] = 0.0;
      gCameraLockOnMark_ZanUse[2] = 1;
      v37 = gCameraLockOnMark_Pos3D;
      v38.n64_u64[0] = *(u64 *)&gCameraLockOnMark_Pos3D_Old.x;
      v39 = gCameraLockOnMark_ZanSt[3];
      if (v39 <= 1.0)
        v40 = gCameraLockOnMark_ZanSt[3];
      else
        v40 = 1.0;
      v41.n64_u64[0] = vsub_f32(*(float32x2_t *)&v37[0].x, v38).n64_u64[0];
      if (v39 >= 0.0)
        v42 = v40;
      else
        v42 = 0.0;
      v43 = gCameraLockOnMark_Pos3D_Old.z
          + (f32)((f32)(v37[0].z - gCameraLockOnMark_Pos3D_Old.z) * v42);
      *(float32x2_t *)&v37[3].x = vadd_f32(v38, vmul_n_f32(v41, v42));
      v37[3].z = v43;
      v46 = gCameraLockOnMark_ZanUse;
      gCameraLockOnMark_Pos3D_Time[3] = 0.0;
      v46[3] = 1;
      v48 = gCameraLockOnMark_Pos3D;
      v49 = gCameraLockOnMark_ZanSt[4];
      if (v49 <= 1.0)
        v50 = gCameraLockOnMark_ZanSt[4];
      else
        v50 = 1.0;
      if (v49 >= 0.0)
        v51 = v50;
      else
        v51 = 0.0;
      v52.n64_u64[0] = *(u64 *)&gCameraLockOnMark_Pos3D_Old.x;
      v53.n64_u64[0] = vsub_f32(v48[4], v52).n64_u64[0];
      v48[11].n64_f32[0] = gCameraLockOnMark_Pos3D_Old.z
                         + (f32)((f32)(v48[5].n64_f32[0] - gCameraLockOnMark_Pos3D_Old.z) * v51);
      v48[10].n64_u64[0] = vadd_f32(v52, vmul_n_f32(v53, v51)).n64_u64[0];
      v56 = gCameraLockOnMark_ZanUse;
      gCameraLockOnMark_Pos3D_Time[4] = 0.0;
      v56[4] = 1;
    }
  }
  else
  {
    v11->Step = 21;
  }
}

// 0x1e32440
void OffVisible(void) {
  sdfVector3_t *gCameraLockOnMark_Pos3D_local;
  u32 v8;
  bool *v9;
  f32 *v10;
  sdfVector3_t *v11;
  u32 v14;
  u32 v16;
  u32 v18;
  sdfVector3_t *v21;
  f32 *v22;
  bool *v23;

  *(u16 *)&gCameraLockOnMark_Use = 0;
  *(u64 *)&gCameraLockOnMark_Pos3D_Old.x = 0;
  gCameraLockOnMark_Pos3D_Old.z = 0.0;
  gCameraLockOnMark_Pos3D_local = gCameraLockOnMark_Pos3D;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[0].x = 0;
  gCameraLockOnMark_Pos3D_local[0].z = 0.0;
  gCameraLockOnMark_Pos3D_Time[0] = 0.0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[1].x = 0;
  gCameraLockOnMark_Pos3D_local[1].z = 0.0;
  gCameraLockOnMark_Pos3D_Time[1] = 0.0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[2].x = 0;
  gCameraLockOnMark_Pos3D_local[2].z = 0.0;
  gCameraLockOnMark_Pos3D_Time[2] = 0.0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[3].x = 0;
  gCameraLockOnMark_Pos3D_local[3].z = 0.0;
  gCameraLockOnMark_Pos3D_Time[3] = 0.0;
  *(u32 *)gCameraLockOnMark_ZanUse = 0;
  *(u64 *)&gCameraLockOnMark_Pos3D_local[4].x = 0;
  gCameraLockOnMark_Pos3D_local[4].z = 0.0;
  gCameraLockOnMark_Pos3D_Time[4] = 0.0;
  gCameraLockOnMark_ZanUse[4] = 0;
  goto LABEL_13;
  if (v8)
  {
    *(u64 *)&v11[1].y = 0;
    v11[1].x = 0.0;
    v10[1] = 0.0;
    v9[1] = 0;
LABEL_10:
    *(u64 *)&v11[2].x = 0;
    v11[2].z = 0.0;
    v10[2] = 0.0;
    v9[2] = 0;
LABEL_11:
    *(u64 *)&v11[3].y = 0;
    v11[3].x = 0.0;
    v10[3] = 0.0;
    v9[3] = 0;
LABEL_12:
    *(u64 *)&v11[4].x = 0;
    v11[4].z = 0.0;
    v10[4] = 0.0;
    v9[4] = 0;
    goto LABEL_13;
  }
  v11 = gCameraLockOnMark_Pos3D;
  v10 = gCameraLockOnMark_Pos3D_Time;
  v9 = gCameraLockOnMark_ZanUse;
  *(u64 *)&v11[1].y = 0;
  v11[1].x = 0.0;
  v10[1] = 0.0;
  v9[1] = 0;
  if (v14)
    goto LABEL_10;
  v11 = gCameraLockOnMark_Pos3D;
  v10 = gCameraLockOnMark_Pos3D_Time;
  v9 = gCameraLockOnMark_ZanUse;
  *(u64 *)&v11[2].x = 0;
  v11[2].z = 0.0;
  v10[2] = 0.0;
  v9[2] = 0;
  if (v16)
    goto LABEL_11;
  v11 = gCameraLockOnMark_Pos3D;
  v10 = gCameraLockOnMark_Pos3D_Time;
  v9 = gCameraLockOnMark_ZanUse;
  *(u64 *)&v11[3].y = 0;
  v11[3].x = 0.0;
  v10[3] = 0.0;
  v9[3] = 0;
  if (v18)
    goto LABEL_12;
  v21 = gCameraLockOnMark_Pos3D;
  v22 = gCameraLockOnMark_Pos3D_Time;
  v23 = gCameraLockOnMark_ZanUse;
  *(u64 *)&v21[4].x = 0;
  v21[4].z = 0.0;
  v22[4] = 0.0;
  v23[4] = 0;
LABEL_13:
  AW_CamLockonSetVisible(gAwIdx_OutSide[0], 0);
  AW_CamLockonSetVisible(gAwIdx_OutSide[1], 0);
  AW_CamLockonSetVisible(gAwIdx_OutSide[2], 0);
  AW_CamLockonSetVisible(gAwIdx_OutSide[3], 0);
}

// 0x1e326c0
bool ChkVisible(void) {
  return gCameraLockOnMark_Use;
}

// 0x1e32740
void Calc(AW_WORK_t *aWork) {
  s64 SubIdx;
  s64 v9;
  f32 v11;
  f32 v12;
  sdfVector3_t *v13;
  f32 v14;
  sdfVector3_t *m_Items;
  f32 x;
  f32 v17;
  f32 v18;
  f32 *p_x;
  f32 v20;
  f32 v21;
  f32 v22;
  bool v23;
  f32 v24;
  bool v25;
  f32 v26;
  s64 v27;
  s32 Step;
  f32 *v30;
  f32 v31;
  f32 v35;
  f32 *v36;
  f32 v37;
  f32 v38;
  f32 v39;
  bool v40;
  s32 huumastat;
  f32 *v45;
  f32 v46;
  f32 *v50;
  f32 v51;
  f32 v52;
  f32 v53;
  bool v54;
  f32 v55;
  bool v56;
  f32 v57;
  f32 *v59;
  f32 v60;
  f32 v61;
  f32 v62;
  bool v63;
  char v64;
  f32 v65;
  f32 v66;
  s64 v67;
  f32 v74;
  f32 v75;
  f32 v77;
  f32 v78;
  f32 v79;
  char v80;
  f32 v81;
  f32 v82;
  s64 v83;
  s32 v85;
  u32 v86;
  s32 v89;
  f32 StepFloatA;
  f32 v91;
  f32 v92;
  unsigned __int128 v93;

  v93 = 0u;
  if (!gCameraLockOnMark_Use)
    goto LABEL_149;
  if (wk->cmbSkl->bRun)
    goto LABEL_149;
  if ((wk->status & 0x400) != 0)
    goto LABEL_149;
  if (sBtlChkMenu2Open())
    goto LABEL_20;
  if (!get_Instance(0)->sc_pause)
  {
    if ((wk->status & 0x40) != 0)
      goto LABEL_149;
    if (sBtlIsHuuma())
    {
      huumastat = (u16)wk->huumastat;
      if (wk->huumastat <= 240)
      {
        if ((u32)(huumastat - 6) < 2 || huumastat == 240)
        {
LABEL_149:
          aWork->AnimTime = 0.0;
          aWork->AnimIdx = -1;
          aWork->AnimStep = 0;
          AW_CamLockonSetVisible(gAwIdx_OutSide[0], 0);
          AW_CamLockonSetVisible(gAwIdx_OutSide[1], 0);
          AW_CamLockonSetVisible(gAwIdx_OutSide[2], 0);
          AW_CamLockonSetVisible(gAwIdx_OutSide[3], 0);
          return;
        }
      }
      else if ((u32)(huumastat - 256) < 2 || huumastat == 1360)
      {
        goto LABEL_149;
      }
    }
  }
LABEL_20:
  SubIdx = (u32)aWork->SubIdx;
  if (!(u32)SubIdx)
  {
    Step = aWork->Step;
    if (Step <= 10)
    {
      if (!Step)
      {
        v74 = gCameraLockOnMark_Pos3D_Time[0] + VRF_DeltaTime;
        gCameraLockOnMark_Pos3D_Time[0] = v74;
        v75 = v74 / (f32)(FPS60 * 20.0);
        if (v75 <= 1.0)
          v35 = v75;
        else
          v35 = 1.0;
        aWork->StepFloatA = v35;
        v77 = gCameraLockOnMark_Pos3D[8];
        v78 = gCameraLockOnMark_Pos3D[9];
        v79 = gCameraLockOnMark_Pos3D[10];
        v40 = sBtlChangeWorldtoScreenUnity3(v77, v78, v79, &v93);
        if (!ProcessCheck())
        {
          if (!ProcessCheck())
          {
LABEL_152:
            v80 = 0;
            v81 = *(f32 *)&v93;
            if (*(f32 *)&v93 <= -16.0)
              goto LABEL_155;
            goto LABEL_136;
          }
        }
        goto LABEL_135;
      }
      if (Step == 1)
      {
        v45 = gCameraLockOnMark_Pos3D_Time;
        v46 = v45[0] - VRF_DeltaTime;
        v45[0] = v46;
        if (v46 < 0.0)
        {
          v45 = gCameraLockOnMark_Pos3D_Time;
          v45[0] = 0.0;
        }
        if ((f32)(gCameraLockOnMark_Pos3D_Time[0] / (f32)(FPS60 * 32.0)) >= 0.0)
          v35 = gCameraLockOnMark_Pos3D_Time[0] / (f32)(FPS60 * 32.0);
        else
          v35 = 0.0;
        aWork->StepFloatA = v35;
        v50 = gCameraLockOnMark_Pos3D;
        v51 = v50[8];
        v52 = v50[9];
        v53 = v50[10];
        v54 = sBtlChangeWorldtoScreenUnity3(v51, v52, v53, &v93);
        v55 = *(f32 *)&v93;
        if (*(f32 *)&v93 <= -16.0)
          goto LABEL_155;
        v56 = v54;
        if (v55 >= (f32)(get_width(0) + 16))
          goto LABEL_155;
        v57 = *((f32 *)&v93 + 1);
        if (*((f32 *)&v93 + 1) <= 0.0 || v57 >= (f32)get_height(0) || !v56)
          goto LABEL_155;
        goto LABEL_139;
      }
    }
    else if ((u32)Step <= 0x15)
    {
      if (Step == 21)
      {
        aWork->StepFloatA = 1.0;
        v59 = gCameraLockOnMark_Pos3D;
        v60 = v59[8];
        v61 = v59[9];
        v62 = v59[10];
        v63 = sBtlChangeWorldtoScreenUnity3(v60, v61, v62, &v93);
        if (ProcessCheck())
          goto LABEL_113;
        if (ProcessCheck())
        {
LABEL_113:
          v64 = 1;
          v65 = *(f32 *)&v93;
          if (*(f32 *)&v93 <= -16.0)
            goto LABEL_155;
        }
        else
        {
          v64 = 0;
          v65 = *(f32 *)&v93;
          if (*(f32 *)&v93 <= -16.0)
            goto LABEL_155;
        }
        if (v65 < (f32)(get_width(0) + 16))
        {
          v66 = *((f32 *)&v93 + 1);
          if (*((f32 *)&v93 + 1) > 0.0 && !(v64 & 1 | (v66 >= (f32)get_height(0) || !v63)))
          {
            v67 = v93;
            aWork->Z = 0.0;
            *(u64 *)&aWork->X = v67;
            AW_CamLockonSetVisible(gAwIdx_OutSide[0], 0);
            AW_CamLockonSetVisible(gAwIdx_OutSide[1], 0);
            AW_CamLockonSetVisible(gAwIdx_OutSide[2], 0);
            AW_CamLockonSetVisible(gAwIdx_OutSide[3], 0);
            goto LABEL_142;
          }
        }
        goto LABEL_155;
      }
    }
    else if (Step == 31)
    {
      v30 = gCameraLockOnMark_Pos3D_Time;
      v31 = v30[0] - VRF_DeltaTime;
      v30[0] = v31;
      if (v31 < 0.0)
      {
        v30 = gCameraLockOnMark_Pos3D_Time;
        v30[0] = 0.0;
      }
      if ((f32)(gCameraLockOnMark_Pos3D_Time[0] / (f32)(FPS60 * 32.0)) >= 0.0)
        v35 = gCameraLockOnMark_Pos3D_Time[0] / (f32)(FPS60 * 32.0);
      else
        v35 = 0.0;
      aWork->StepFloatA = v35;
      v36 = gCameraLockOnMark_Pos3D;
      v37 = v36[8];
      v38 = v36[9];
      v39 = v36[10];
      v40 = sBtlChangeWorldtoScreenUnity3(v37, v38, v39, &v93);
      if (!ProcessCheck())
      {
        if (!ProcessCheck())
          goto LABEL_152;
      }
LABEL_135:
      v80 = 1;
      v81 = *(f32 *)&v93;
      if (*(f32 *)&v93 > -16.0)
      {
LABEL_136:
        if (v81 >= (f32)(get_width(0) + 16))
          goto LABEL_155;
        v82 = *((f32 *)&v93 + 1);
        if (*((f32 *)&v93 + 1) <= 0.0 || v80 & 1 | (v82 >= (f32)get_height(0) || !v40))
          goto LABEL_155;
LABEL_139:
        v83 = v93;
        aWork->Z = 0.0;
        *(u64 *)&aWork->X = v83;
        AW_CamLockonSetVisible(gAwIdx_OutSide[0], 1);
        AW_CamLockonSetVisible(gAwIdx_OutSide[1], 1);
        AW_CamLockonSetVisible(gAwIdx_OutSide[2], 1);
        AW_CamLockonSetVisible(gAwIdx_OutSide[3], 1);
        AW_CamLockonSetPos(gAwIdx_OutSide[0], *(f32 *)&v93, *((f32 *)&v93 + 1), v35);
        AW_CamLockonSetPos(gAwIdx_OutSide[1], *(f32 *)&v93, *((f32 *)&v93 + 1), v35);
        AW_CamLockonSetPos(gAwIdx_OutSide[2], *(f32 *)&v93, *((f32 *)&v93 + 1), v35);
        AW_CamLockonSetPos(gAwIdx_OutSide[3], *(f32 *)&v93, *((f32 *)&v93 + 1), v35);
        goto LABEL_142;
      }
LABEL_155:
      AW_CamLockonSetVisible(gAwIdx_OutSide[0], 0);
      AW_CamLockonSetVisible(gAwIdx_OutSide[1], 0);
      AW_CamLockonSetVisible(gAwIdx_OutSide[2], 0);
      AW_CamLockonSetVisible(gAwIdx_OutSide[3], 0);
    }
LABEL_158:
    v89 = -1;
LABEL_159:
    aWork->AnimIdx = v89;
    return;
  }
  if ((u32)(SubIdx - 5) < 0xFFFFFFFC)
    goto LABEL_158;
  if (!gCameraLockOnMark_ZanUse[SubIdx])
    goto LABEL_158;
  v9 = (s64)gCameraLockOnMark_Pos3D_Time + 4 * SubIdx;
  v11 = *(f32 *)(v9 + 32) + VRF_DeltaTime;
  *(f32 *)(v9 + 32) = v11;
  v12 = v11 / (f32)(FPS60 * 24.0);
  if (v12 >= 1.0)
    goto LABEL_158;
  v13 = gCameraLockOnMark_Pos3D;
  if (v12 <= 1.0)
    v14 = v12;
  else
    v14 = 1.0;
  x = v13[0].x;
  m_Items = v13;
  v17 = x;
  if (v12 >= 0.0)
    v18 = v14;
  else
    v18 = 0.0;
  p_x = &m_Items[(u32)SubIdx].x;
  v20 = *p_x + (f32)(v18 * (f32)(v17 - *p_x));
  v21 = p_x[1] + (f32)(v18 * (f32)(m_Items->y - p_x[1]));
  v22 = p_x[2] + (f32)(v18 * (f32)(m_Items->z - p_x[2]));
  v23 = sBtlChangeWorldtoScreenUnity3(v20, v21, v22, &v93);
  v24 = *(f32 *)&v93;
  if (*(f32 *)&v93 <= -16.0)
    goto LABEL_158;
  v25 = v23;
  if (v24 >= (f32)(get_width(0) + 16))
    goto LABEL_158;
  v26 = *((f32 *)&v93 + 1);
  if (*((f32 *)&v93 + 1) <= 0.0 || v26 >= (f32)get_height(0) || !v25)
    goto LABEL_158;
  v27 = v93;
  aWork->Z = 0.0;
  *(u64 *)&aWork->X = v27;
  aWork->Dir = (f32)(v18 * -45.0) + 0.0;
LABEL_142:
  switch (aWork->SubIdx)
  {
    case 0:
      v85 = aWork->Step;
      if (v85 <= 1)
      {
        if ((u32)v85 > 1)
          return;
      }
      else
      {
        v86 = v85 & 0xFFFFFFFE;
        if (v86 == 20)
        {
          aWork->AnimIdx = 1;
          aWork->Dir = -45.0;
          return;
        }
        if (v86 != 30)
          return;
      }
      StepFloatA = aWork->StepFloatA;
      if (StepFloatA >= 1.0)
      {
        v89 = 1;
        aWork->Dir = 0.0;
        goto LABEL_159;
      }
      aWork->AnimIdx = 0;
      if (StepFloatA <= 1.0)
        v91 = (f32)(StepFloatA * -45.0) + 0.0;
      else
        v91 = -45.0;
      if (StepFloatA >= 0.0)
        v92 = v91;
      else
        v92 = 0.0;
      aWork->Dir = v92;
      break;
    case 1:
      v89 = 2;
      goto LABEL_159;
    case 2:
      v89 = 3;
      goto LABEL_159;
    case 3:
      v89 = 4;
      goto LABEL_159;
    case 4:
      v89 = 5;
      goto LABEL_159;
    default:
      return;
  }
}

// 0x1e33420
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  s32 AnimIdx;
  s32 AnimNum;
  s64 v7;
  s64 v8;
  sdfVector3_t v9;

  transform = get_transform(aWork->Obj, 0);
  set_position(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v9.z = aWork->Dir;
  v9.x = 0.0;
  v9.y = 0.0;
  set_eulerAngles(v4, v9, 0);
  AnimIdx = aWork->AnimIdx;
  if (aWork->AnimIdxOld == AnimIdx)
    return;
  AnimNum = aWork->AnimNum;
  aWork->AnimIdxOld = AnimIdx;
  if (AnimIdx == -1)
  {
    if (AnimNum >= 1)
    {
      v8 = 0;
      do
        SetActive(aWork->AnimObj[v8++], 0, 0);
      while (v8 < aWork->AnimNum);
    }
  }
  else if (AnimNum >= 1)
  {
    v7 = 0;
    do
    {
      SetActive(aWork->AnimObj[v7], v7 == aWork->AnimIdx, 0);
      ++v7;
    }
    while (v7 < aWork->AnimNum);
  }
}
