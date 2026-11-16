#include "types.h"
#include "aw.h"
#include "aw_rangecircle.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e49c00
void Init(void) {
  ;
}

// 0x1e49c10
s32 Add(s32 _Unit_ListID, f32 _SizeR, bool _Hit) {
  bool v8;
  AW_WORK_t *AW_Unit_ListID_SubIdx;
  s32 Idx;
  Il2CppObject *v11;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v17;
  AW_Func v18;
  AW_Func v19;
  AW_WORK_t *AW;
  char *v21;
  f32 v22;
  sdfVector3_t v24;
  sdfQuaternion_t v25;

  v8 = Hit;
  AW_Unit_ListID_SubIdx = GetAW_Unit_ListID_SubIdx(403, Unit_ListID, 0);
  if (AW_Unit_ListID_SubIdx)
  {
    Idx = AW_Unit_ListID_SubIdx->Idx;
    AW_Unit_ListID_SubIdx->StepBoolA = v8;
    return Idx;
  }
  v11 = get_Instance(AW_Unit_ListID_SubIdx)->AwPrefab[11];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v24.x = 0.0;
  v24.y = 0.0;
  v24.z = 0.0;
  v25.x = x;
  v25.y = y;
  v25.z = z;
  v25.w = w;
  v17 = Instantiate_object__39504752(v11, v24, v25);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_RangeCircle_Calc__, 0);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_RangeCircle_Draw__, 0);
  Idx = Add(403, 0.0, 0.0, 0.0, v17, v18, v19, 1);
  Set_AnimObj(Idx, 0, "Circle_NoHit");
  Set_AnimObj(Idx, 1, "Circle_Hit");
  AW = GetAW(Idx);
  AW->Unit_ListID = Unit_ListID;
  AW->SubIdx = 0;
  AW->StepBoolA = v8;
  AW->AnimIdx = -1;
  v21 = "AW_RangeCircle";
  AW->DbgStr = "AW_RangeCircle";
  v22 = (f32)(SizeR / 100.0) * 0.5;
  AW->StepFloatA = v22;
  AW->StepFloatB = SizeR / 100.0;
  AW->Scale = v22;
  return Idx;
}

// 0x1e49ef0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e49f60
void DeleteAll(void) {
  DelAW_ID(403, 1);
}

// 0x1e49fe0
void Calc(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  f32 z;
  s32 Step;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v14;
  f32 StepTime;
  f32 v16;
  f32 StepFloatA;
  f32 StepFloatB;
  f32 v19;
  s32 Idx;

  if (!get_Instance(0)->sc_pause)
  {
    if (ChkPause(aWork))
      return;
  }
  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (v6)
  {
    v7 = v6;
    if (sBtlCheckDamageTarget(v7))
      goto LABEL_16;
  }
  Idx = aWork->Idx;
  DelAW(Idx, 1);
  return;
LABEL_16:
  z = v7->pos.z;
  Step = aWork->Step;
  v10 = (f32)(v7->pos.y / -100.0) + 0.03;
  aWork->X = v7->pos.x / -100.0;
  aWork->Y = v10;
  aWork->Z = z / -100.0;
  if (!Step)
  {
    v11 = 0.0;
    v12 = 0.0;
    v14 = FPS60 * 8.0;
    StepTime = aWork->StepTime;
    if (v14 != 0.0)
    {
      v16 = 1.0;
      if ((f32)(StepTime / v14) <= 1.0)
        v16 = StepTime / v14;
      v12 = 0.0;
      if ((f32)(StepTime / v14) >= 0.0)
        v12 = v16;
    }
    StepFloatA = aWork->StepFloatA;
    StepFloatB = aWork->StepFloatB;
    if (v12 >= 0.0)
      v11 = v12;
    v19 = StepTime + VRF_DeltaTime;
    aWork->StepTime = v19;
    aWork->Scale = StepFloatA + (f32)(v11 * (f32)(StepFloatB - StepFloatA));
    if (v19 > v14)
      *(u64 *)&aWork->Step = 1;
  }
  aWork->AnimIdx = aWork->StepBoolA;
}

// 0x1e4a290
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
