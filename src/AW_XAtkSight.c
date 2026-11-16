#include "types.h"
#include "aw.h"
#include "aw_xatksight.h"
#include "dds3vrf.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1ebc600
void Init(void) {
  ;
}

// 0x1ebc610
s32 Add(f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 114, 0);
  v12 = identityQuaternion.x;
  v13 = identityQuaternion.y;
  v14 = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = X;
  v23.y = Y;
  v23.z = Z;
  v24.x = v12;
  v24.y = v13;
  v24.z = v14;
  v24.w = w;
  v16 = Instantiate_object__39504752(AwPrefab, v23, v24);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_XAtkSight_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkSight_Draw__, 0);
  v19 = Add(257, X, Y, Z, v16, v17, v18, 1);
  AW = GetAW(v19);
  v21 = "AW_XAtkSight";
  AW->Scale = 0.1;
  AW->Dir = Dir;
  AW->DbgStr = v21;
  return v19;
}

// 0x1ebc840
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1ebc8b0
void AW_XAtkFadeOut(s32 _Idx) {
  AW_WORK_t *AW;

  if (Idx != -1)
  {
    AW = GetAW(Idx);
    if (AW)
    {
      if (AW->Step <= 1u)
        *(u64 *)&AW->Step = 2;
    }
  }
}

// 0x1ebc930
void Calc(AW_WORK_t *aWork) {
  f32 v4;
  f32 v7;
  f32 v8;
  s32 Idx;

  if (ChkPause(aWork))
    return;
  switch (aWork->Step)
  {
    case 0:
      v4 = aWork->Scale + (f32)(VRF * 0.1);
      aWork->Scale = v4;
      if (v4 > 1.0)
      {
        aWork->Scale = 1.0;
        *(u64 *)&aWork->Step = 1;
      }
      break;
    case 1:
      v7 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v7;
      if (v7 > (f32)(FPS60 * 180.0))
        *(u64 *)&aWork->Step = 2;
      break;
    case 2:
      v8 = aWork->Scale + (f32)(VRF * -0.2);
      aWork->Scale = v8;
      if (v8 <= 0.0)
      {
        aWork->Scale = 0.0;
        *(u64 *)&aWork->Step = 3;
      }
      break;
    case 3:
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      break;
    default:
      return;
  }
}

// 0x1ebcb40
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  void *v5;
  sdfVector3_t v6;
  sdfVector3_t v7;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v6.y = aWork->Dir;
  v6.x = 0.0;
  v6.z = 0.0;
  set_eulerAngles(v4, v6, 0);
  v5 = get_transform(aWork->Obj, 0);
  v7.x = aWork->Scale;
  v7.y = v7.x;
  v7.z = v7.x;
  set_localScale(v5, v7, 0);
}
