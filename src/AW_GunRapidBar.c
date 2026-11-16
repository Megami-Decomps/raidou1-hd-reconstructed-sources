#include "types.h"
#include "aw.h"
#include "aw_gunrapidbar.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

static void CalcPos(AW_WORK_t *aWork);

// 0x1e38350
void Init(void) {
  ;
}

// 0x1e37b10
s32 Add(f32 _Par) {
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
  AW_Func v14;
  s32 v15;
  AW_WORK_t *AW;
  AW_WORK_t *v17;
  s64 v18;
  char *v19;
  s64 ToZ;
  sdfVector3_t v22;
  sdfQuaternion_t v23;

  AwParentImage = get_Instance(0)->AwParentImage;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 53, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  transform = get_transform(AwParentImage, 0);
  v22.x = 0.0;
  v22.y = 0.0;
  v22.z = 0.0;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  v12 = Instantiate_object__39505040(AwPrefab, v22, v23, transform);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0, Method_Project_AW_GunRapidBar_Calc__, 0);
  v14 = Allocate(AW_Func);
  _ctor(v14, 0, Method_Project_AW_GunRapidBar_Draw__, 0);
  v15 = Add(306, 0.0, 0.0, 0.0, v12, v13, v14, 1);
  Set_AnimObj(v15, 0, "gunrapidbar_0");
  Set_AnimObj(v15, 1, "gunrapidbar_1");
  AW = GetAW(v15);
  AW->StepFloatA = Par;
  AW->AnimIdx = -1;
  v17 = AW;
  Par = v17->StepFloatA;
  ToZ = 0;
  sBtlGetMoveXZ(0.0, 0.0, Par + 10.0, 270.0, (f32 *)&ToZ + 1, &ToZ);
  v18 = ToZ;
  v19 = "AW_GunRapidBar";
  v17->Scale = 1.0;
  v17->DbgStr = v19;
  v17->X = *((f32 *)&v18 + 1);
  LODWORD(v17->Y) = v18;
  return v15;
}

// 0x1e38410
void Del(s32 _Unit_ListID, s32 _SubIdx) {
  AW_WORK_t *AW_Unit_ListID_SubIdx;
  s32 Idx;

  AW_Unit_ListID_SubIdx = GetAW_Unit_ListID_SubIdx(303, Unit_ListID, SubIdx);
  if (!AW_Unit_ListID_SubIdx)
    return;
  Idx = AW_Unit_ListID_SubIdx->Idx;
  DelAW(Idx, 1);
}

// 0x1e384e0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e37f30
void DeleteAll(void) {
  DelAW_ID(306, 1);
}

// 0x1e38360
static void CalcPos(AW_WORK_t *aWork) {
  f32 StepFloatA;
  s64 v4;
  s64 ToZ;

  ToZ = 0;
  StepFloatA = aWork->StepFloatA;
  sBtlGetMoveXZ(0.0, 0.0, StepFloatA + 10.0, 270.0, (f32 *)&ToZ + 1, &ToZ);
  v4 = ToZ;
  aWork->Scale = 1.0;
  aWork->X = *((f32 *)&v4 + 1);
  LODWORD(aWork->Y) = v4;
}

// 0x1e38550
void Calc(AW_WORK_t *aWork) {
  f32 StepFloatA;
  f32 v6;
  f32 ToZ;
  f32 ToX;

  if ((wk->status & 0x400) == 0)
  {
    if (sBtlChkMenu2Open())
      goto LABEL_13;
    if ((wk->status & 0x40) == 0)
      goto LABEL_13;
  }
  aWork->AnimIdx = -1;
  return;
LABEL_13:
  if (!aWork->Step)
  {
    ToX = 0.0;
    ToZ = 0.0;
    StepFloatA = aWork->StepFloatA;
    sBtlGetMoveXZ(0.0, 0.0, StepFloatA + 10.0, 270.0, &ToX, &ToZ);
    aWork->Scale = 1.0;
    v6 = ToZ;
    aWork->X = ToX;
    aWork->Y = v6;
    aWork->AnimIdx = aWork->StepFloatA >= (f32)(-10 * wk->GunRapidNum + 360);
  }
}

// 0x1e38770
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.x = aWork->Scale;
  v5.y = v5.x;
  v5.z = v5.x;
  set_localScale(v4, v5, 0);
  Draw_AnimObj(aWork);
}
