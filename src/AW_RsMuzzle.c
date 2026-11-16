#include "types.h"
#include "aw.h"
#include "aw_rsmuzzle.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e4ee90
void Init(void) {
  ;
}

// 0x1e4eea0
s32 Add(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir) {
  f32 Dir180;
  Il2CppObject *v11;
  f32 v12;
  f32 x;
  f32 y;
  f32 v16;
  f32 v17;
  f32 z;
  f32 w;
  Il2CppObject *v20;
  AW_Func v21;
  AW_Func v22;
  s32 v23;
  AW_WORK_t *AW;
  char *v25;
  sdfVector3_t v27;
  sdfQuaternion_t v28;

  Dir180 = sBtlGetDir180(SDir);
  v11 = get_Instance()->AwPrefab[121];
  v12 = SX / -100.0;
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  v16 = SY / -100.0;
  v17 = SZ / -100.0;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v27.x = v12;
  v27.y = v16;
  v27.z = v17;
  v28.x = x;
  v28.y = y;
  v28.z = z;
  v28.w = w;
  v20 = Instantiate_object__39504752(v11, v27, v28);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0, Method_Project_AW_RsMuzzle_Calc__, 0);
  v22 = Allocate(AW_Func);
  _ctor(v22, 0, Method_Project_AW_RsMuzzle_Draw__, 0);
  v23 = Add(274, v12, v16, v17, v20, v21, v22, 1);
  Set_HDEff(v23, 1, -1);
  AW = GetAW(v23);
  v25 = "AW_RsMuzzle";
  AW->Dir = Dir180;
  AW->DbgStr = v25;
  return v23;
}

// 0x1e4f120
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

// 0x1e4f360
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
