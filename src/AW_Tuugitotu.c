#include "types.h"
#include "aw.h"
#include "aw_tuugitotu.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e82c20
void Init(void) {
  ;
}

// 0x1e82c30
s32 Add(s32 _Variation) {
  s32 v3;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v11;
  AW_Func v12;
  AW_Func v13;
  s32 v14;
  AW_WORK_t *AW;
  char *v16;
  sdfVector3_t v18;
  sdfQuaternion_t v19;

  if (Variation == 2)
    v3 = 28;
  else
    v3 = 27;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v3, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v18.x = 0.0;
  v18.y = 0.0;
  v18.z = 0.0;
  v19.x = x;
  v19.y = y;
  v19.z = z;
  v19.w = w;
  v11 = Instantiate_object__39504752(AwPrefab, v18, v19);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_Tuugitotu_Calc__, 0);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0, Method_Project_AW_Tuugitotu_Draw__, 0);
  v14 = Add(219, 0.0, 0.0, 0.0, v11, v12, v13, 1);
  Set_HDEff(v14, 1, -1);
  AW = GetAW(v14);
  v16 = "AW_Tuugitotu";
  AW->DbgStr = "AW_Tuugitotu";
  return v14;
}

// 0x1e82e60
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e82ed0
void DeleteAll(void) {
  DelAW_ID(219, 1);
}

// 0x1e82f50
bool ChkRun(void) {
  return GetAW_ID(219) != 0;
}

// 0x1e82fc0
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

// 0x1e83150
void Draw(AW_WORK_t *aWork) {
}
