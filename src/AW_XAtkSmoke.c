#include "types.h"
#include "aw.h"
#include "aw_xatksmoke.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1ebd1c0
void Init(void) {
  ;
}

// 0x1ebd1d0
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, s32 _Variation) {
  s32 v11;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v19;
  AW_Func v20;
  AW_Func v21;
  s32 v22;
  AW_WORK_t *AW;
  char *v24;
  sdfVector3_t v26;
  sdfQuaternion_t v27;

  if (Variation == 1)
    v11 = 57;
  else
    v11 = 56;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v11, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v26.x = UnityX;
  v26.y = UnityY;
  v26.z = UnityZ;
  v27.x = x;
  v27.y = y;
  v27.z = z;
  v27.w = w;
  v19 = Instantiate_object__39504752(AwPrefab, v26, v27);
  v20 = Allocate(AW_Func);
  _ctor(v20, 0, Method_Project_AW_XAtkSmoke_Calc__, 0);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0, Method_Project_AW_XAtkSmoke_Draw__, 0);
  v22 = Add(265, UnityX, UnityY, UnityZ, v19, v20, v21, 1);
  Set_HDEff(v22, 1, -1);
  AW = GetAW(v22);
  v24 = "AW_XAtkSmoke";
  AW->Dir = UnityDir;
  AW->Variation = Variation;
  AW->DbgStr = v24;
  return v22;
}

// 0x1ebd430
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1ebd4a0
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

// 0x1ebd6e0
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
