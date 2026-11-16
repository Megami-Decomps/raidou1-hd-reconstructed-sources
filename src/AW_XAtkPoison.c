#include "types.h"
#include "aw.h"
#include "aw_xatkpoison.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1ebbc80
void Init(void) {
  ;
}

// 0x1ebbc90
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
  char *v19;
  sdfVector3_t v21;
  sdfQuaternion_t v22;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 105, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v21.x = UnityX;
  v21.y = UnityY;
  v21.z = UnityZ;
  v22.x = x;
  v22.y = y;
  v22.z = z;
  v22.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v21, v22);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_XAtkPoison_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_XAtkPoison_Draw__, 0);
  v17 = Add(260, UnityX, UnityY, UnityZ, v14, v15, v16, 1);
  Set_HDEff(v17, 1, -1);
  AW = GetAW(v17);
  v19 = "AW_XAtkPoison";
  AW->Scale = 1.0;
  AW->DbgStr = v19;
  return v17;
}

// 0x1ebbed0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1ebbf40
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

// 0x1ebc180
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
