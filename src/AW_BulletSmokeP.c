#include "types.h"
#include "aw.h"
#include "aw_bulletsmokep.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e30cb0
void Init(void) {
  ;
}

// 0x1e30150
s32 Add(f32 _UX, f32 _UY, f32 _UZ) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v17;
  s32 v20;
  char *v23;
  char **p_DbgStr;
  sdfVector3_t v26;
  sdfQuaternion_t v27;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 7, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v26.x = UX;
  v26.y = UY;
  v26.z = UZ;
  v27.x = x;
  v27.y = y;
  v27.z = z;
  v27.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v26, v27);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0);
  v20 = Add(203, UX, UY, UZ, v14, v15, v17, 1);
  Set_HDEff(v20, 1, -1);
  v23 = "AW_BulletSmokeP";
  p_DbgStr = &gWork[v20]->DbgStr;
  *p_DbgStr = "AW_BulletSmokeP";
  return v20;
}

// 0x1e30cc0
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  _GetEnumerator(&v5, aWork->ParticleSystemList);
  while (_MoveNext(&v5))
  {
    if (IsAlive_61441520(v5._current, 0))
    {
      _Dispose(&v5);
      return;
    }
  }
  _Dispose(&v5);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e30e50
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
