#include "types.h"
#include "aw.h"
#include "aw_tuugizan.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e831c0
void Init(void) {
  ;
}

// 0x1e831d0
s32 Add(s32 _Variation) {
  s32 v3;
  s32 v4;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v12;
  AW_Func v13;
  AW_Func v14;
  s32 v15;
  AW_WORK_t *AW;
  char *v17;
  sdfVector3_t v19;
  sdfQuaternion_t v20;

  if (Variation == 1)
    v3 = 24;
  else
    v3 = 23;
  if (Variation == 2)
    v4 = 25;
  else
    v4 = v3;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v4, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v19.x = 0.0;
  v19.y = 0.0;
  v19.z = 0.0;
  v20.x = x;
  v20.y = y;
  v20.z = z;
  v20.w = w;
  v12 = Instantiate_object__39504752(AwPrefab, v19, v20);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0, Method_Project_AW_Tuugizan_Calc__, 0);
  v14 = Allocate(AW_Func);
  _ctor(v14, 0, Method_Project_AW_Tuugizan_Draw__, 0);
  v15 = Add(218, 0.0, 0.0, 0.0, v12, v13, v14, 1);
  Set_HDEff(v15, 1, -1);
  AW = GetAW(v15);
  v17 = "AW_Tuugizan";
  AW->StepIntA = Variation;
  AW->DbgStr = v17;
  return v15;
}

// 0x1e83410
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e83480
void DeleteAll(void) {
  DelAW_ID(218, 1);
}

// 0x1e83500
bool ChkRun(void) {
  return GetAW_ID(218) != 0;
}

// 0x1e83570
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v4;

  memset(&v4, 0, sizeof(v4));
  _GetEnumerator(&v4, aWork->ParticleSystemList);
  while (_MoveNext(&v4))
  {
    if (IsAlive_61441520(v4._current, 0))
    {
      _Dispose(&v4);
      return;
    }
  }
  _Dispose(&v4);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e83700
void Draw(AW_WORK_t *aWork) {
}
