#include "types.h"
#include "aw.h"
#include "aw_xatkhatudo.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e8eb60
void Init(void) {
  ;
}

// 0x1e8eb70
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v16;
  s32 v17;
  AW_WORK_t *AW;
  f32 v19;
  char *v20;
  sdfVector3_t v22;
  sdfQuaternion_t v23;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 109, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v22.x = UnityX;
  v22.y = UnityY;
  v22.z = UnityZ;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v22, v23);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_XAtkHatudo_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_XAtkHatudo_Draw__, 0);
  v17 = Add(263, UnityX, UnityY, UnityZ, v14, v15, v16, 1);
  Set_HDEff(v17, 1, -1);
  AW = GetAW(v17);
  v19 = AW->Y;
  v20 = "AW_XAtkHatudo";
  AW->Scale = 1.0;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->DbgStr = v20;
  AW->Y = v19 + 0.02;
  return v17;
}

// 0x1e8edd0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8ee40
void Delete_2(s32 aw_idx) {
  AW_WORK_t *AW;
  AW_WORK_t *v4;
  s32 Idx;

  if (aw_idx != -1)
  {
    AW = GetAW(aw_idx);
    if (!AW)
      return;
    v4 = AW;
    Idx = v4->Idx;
    DelAW(Idx, 1);
  }
}

// 0x1e8ef20
void SetPos(s32 aw_idx, f32 _X, f32 _Y, f32 _Z) {
  AW_WORK_t *AW;

  if (aw_idx != -1)
  {
    AW = GetAW(aw_idx);
    if (!AW)
      return;
    AW->Z = Z;
    AW->X = X;
    AW->Y = Y + 0.02;
  }
}

// 0x1e8efe0
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

// 0x1e8f220
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
