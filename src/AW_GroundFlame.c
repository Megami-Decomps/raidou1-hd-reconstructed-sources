#include "types.h"
#include "aw.h"
#include "aw_groundflame.h"
#include "sbtlsound.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e36f90
void Init(void) {
  ;
}

// 0x1e36fa0
s32 Add_Wait(f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z, s32 _Wait) {
  AW_Func v9;
  s32 v10;
  AW_WORK_t *AW;
  char *v12;
  AW_WORK_t *v13;

  v9 = Allocate(AW_Func);
  _ctor(v9, 0, Method_Project_AW_GroundFlame_CalcWait__, 0);
  v10 = Add(267, Ps2X, Ps2Y, Ps2Z, 0, v9, 0, 1);
  AW = GetAW(v10);
  v12 = "AW_GroundFlameWait";
  v13 = AW;
  AW->X = Ps2X;
  AW->Y = Ps2Y;
  AW->Z = Ps2Z;
  AW->StepIntA = Wait;
  AW->DbgStr = v12;
  return v13->UID;
}

// 0x1e370d0
s32 Add(f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v8;
  f32 v9;
  f32 x;
  f32 y;
  f32 v13;
  f32 z;
  f32 w;
  f32 v16;
  Il2CppObject *v17;
  AW_Func v18;
  AW_Func v19;
  s32 v20;
  AW_WORK_t *AW;
  char *v22;
  f32 v24;
  sdfVector3_t v26;
  sdfVector4_t v27;
  sdfQuaternion_t v28;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 155, 0);
  v8 = Ps2X / -100.0;
  v24 = Ps2X;
  v9 = Ps2Y;
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  v13 = Ps2Y / -100.0;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v16 = Ps2Z / -100.0;
  v26.x = v8;
  v26.y = v13;
  v26.z = Ps2Z / -100.0;
  v28.x = x;
  v28.y = y;
  v28.z = z;
  v28.w = w;
  v17 = Instantiate_object__39504752(AwPrefab, v26, v28);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_GroundFlame_Calc__, 0);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_GroundFlame_Draw__, 0);
  v20 = Add(267, v8, v13, v16, v17, v18, v19, 1);
  Set_HDEff(v20, 1, -1);
  AW = GetAW(v20);
  AW->X = v8;
  AW->Y = v13;
  AW->Z = v16;
  AW->Dir = 0.0;
  v27.z = Ps2Z;
  v27.w = 0.0;
  v27.x = v24;
  v27.y = v9;
  sBtlPlay3DSE(0x503001Cu, v27);
  v22 = "AW_GroundFlame";
  AW->DbgStr = "AW_GroundFlame";
  return AW->UID;
}

// 0x1e37380
void CalcWait(AW_WORK_t *aWork) {
  _BOOL8 v4;
  s32 v5;
  bool v6;
  s32 Idx;

  v4 = ChkPause(aWork);
  if (v4)
    return;
  v5 = aWork->StepIntA - 1;
  v6 = aWork->StepIntA == 1;
  aWork->StepIntA = v5;
  if (v5 < 0 || v6)
  {
    Add(aWork->X, aWork->Y, aWork->Z, v4);
    Idx = aWork->Idx;
    DelAW(Idx, 0);
  }
}

// 0x1e37460
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v6;

  memset(&v6, 0, sizeof(v6));
  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v6, aWork->ParticleSystemList);
  while (_MoveNext(&v6))
  {
    current = v6._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v6);
      return;
    }
  }
  _Dispose(&v6);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e376a0
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.y = aWork->Dir;
  v5.x = 0.0;
  v5.z = 0.0;
  set_eulerAngles(v4, v5, 0);
}
