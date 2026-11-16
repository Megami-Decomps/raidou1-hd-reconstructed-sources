#include "types.h"
#include "aw.h"
#include "aw_tuugikai.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e50610
void Init(void) {
  ;
}

// 0x1e56730
s32 Add(s32 _Variation) {
  s64 v3;
  Il2CppObject *v4;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v10;
  AW_Func v11;
  AW_Func v12;
  s32 v13;
  AW_WORK_t *AW;
  char *v15;
  sdfVector3_t v17;
  sdfQuaternion_t v18;

  if (Variation == 2)
    v3 = 32;
  else
    v3 = 31;
  v4 = get_Instance(*(const MethodInfo **)&Variation)->AwPrefab[v3];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v17.x = 0.0;
  v17.y = 0.0;
  v17.z = 0.0;
  v18.x = x;
  v18.y = y;
  v18.z = z;
  v18.w = w;
  v10 = Instantiate_object__39504752(v4, v17, v18);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0, Method_Project_AW_Tuugikai_Calc__, 0);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_Tuugikai_Draw__, 0);
  v13 = Add(220, 0.0, 0.0, 0.0, v10, v11, v12, 1);
  Set_HDEff(v13, 1, -1);
  AW = GetAW(v13);
  v15 = "AW_Tuugikai";
  AW->DbgStr = "AW_Tuugikai";
  return v13;
}

// 0x1e56950
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e569c0
void DeleteAll(void) {
  DelAW_ID(220, 1);
}

// 0x1e56a40
bool ChkRun(void) {
  return GetAW_ID(220) != 0;
}

// 0x1e56ab0
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

// 0x1e56c40
void Draw(AW_WORK_t *aWork) {
}
