#include "types.h"
#include "aw.h"
#include "aw_xatkmuzzle.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e8f750
void Init(void) {
  ;
}

// 0x1e8f760
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, f32 _Size) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v17;
  AW_Func v18;
  AW_Func v19;
  s32 v20;
  AW_WORK_t *AW;
  char *v22;
  sdfVector3_t v25;
  sdfQuaternion_t v26;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 108, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v25.x = UnityX;
  v25.y = UnityY;
  v25.z = UnityZ;
  v26.x = x;
  v26.y = y;
  v26.z = z;
  v26.w = w;
  v17 = Instantiate_object__39504752(AwPrefab, v25, v26);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkMuzzle_Calc__, 0);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_XAtkMuzzle_Draw__, 0);
  v20 = Add(253, UnityX, UnityY, UnityZ, v17, v18, v19, 1);
  Set_HDEff(v20, 1, -1);
  AW = GetAW(v20);
  AW->Dir = UnityDir;
  v22 = "AW_XAtkMuzzle";
  AW->DirY = 0.0;
  AW->DbgStr = v22;
  AW->Scale = Size;
  return v20;
}

// 0x1e8f9b0
s32 AW_XAtkAdd_Homing(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, f32 _Size) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v17;
  AW_Func v18;
  AW_Func v19;
  s32 v20;
  AW_WORK_t *AW;
  char *v22;
  sdfVector3_t v25;
  sdfQuaternion_t v26;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 118, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v25.x = UnityX;
  v25.y = UnityY;
  v25.z = UnityZ;
  v26.x = x;
  v26.y = y;
  v26.z = z;
  v26.w = w;
  v17 = Instantiate_object__39504752(AwPrefab, v25, v26);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkMuzzle_Calc__, 0);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_XAtkMuzzle_Draw__, 0);
  v20 = Add(253, UnityX, UnityY, UnityZ, v17, v18, v19, 1);
  Set_HDEff(v20, 1, -1);
  AW = GetAW(v20);
  AW->Dir = UnityDir;
  v22 = "AW_XAtkMuzzleHoming";
  AW->DirY = 0.0;
  AW->DbgStr = v22;
  AW->Scale = Size;
  return v20;
}

// 0x1e8fc00
s32 AW_XAtkAdd_Gun(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, f32 _UnityDirY) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v17;
  AW_Func v18;
  AW_Func v19;
  s32 v20;
  AW_WORK_t *AW;
  char *v22;
  sdfVector3_t v25;
  sdfQuaternion_t v26;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 152, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v25.x = UnityX;
  v25.y = UnityY;
  v25.z = UnityZ;
  v26.x = x;
  v26.y = y;
  v26.z = z;
  v26.w = w;
  v17 = Instantiate_object__39504752(AwPrefab, v25, v26);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkMuzzle_Calc__, 0);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_XAtkMuzzle_Draw__, 0);
  v20 = Add(253, UnityX, UnityY, UnityZ, v17, v18, v19, 1);
  Set_HDEff(v20, 1, -1);
  AW = GetAW(v20);
  AW->Dir = UnityDir;
  v22 = "AW_XAtkMuzzleGun";
  AW->Scale = 1.0;
  AW->DbgStr = v22;
  AW->DirY = UnityDirY;
  return v20;
}

// 0x1e8fe60
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8fed0
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

// 0x1e90110
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
  v6.z = 0.0;
  v6.x = -aWork->DirY;
  set_eulerAngles(v4, v6, 0);
  v5 = get_transform(aWork->Obj, 0);
  v7.x = aWork->Scale;
  v7.y = v7.x;
  v7.z = v7.x;
  set_localScale(v5, v7, 0);
}
