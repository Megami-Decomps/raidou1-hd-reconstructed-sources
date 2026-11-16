#include "types.h"
#include "aw.h"
#include "aw_jumpattack2l.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e3fbc0
void AW_JumpInit(void) {
  ;
}

// 0x1e3fbd0
s32 AW_JumpAdd(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir) {
  f32 Dir180;
  void *Instance;
  Il2CppObject *AwPrefab;
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
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 17, 0);
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
  v20 = Instantiate_object__39504752(AwPrefab, v27, v28);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0, Method_Project_AW_JumpAttack2L_Calc__, 0);
  v22 = Allocate(AW_Func);
  _ctor(v22, 0, Method_Project_AW_JumpAttack2L_Draw__, 0);
  v23 = Add(206, v12, v16, v17, v20, v21, v22, 1);
  Set_HDEff(v23, 1, -1);
  AW = GetAW(v23);
  v25 = "AW_JumpAttack2L";
  AW->Dir = Dir180;
  AW->DbgStr = v25;
  return v23;
}

// 0x1e3fe50
void AW_JumpCalc(AW_WORK_t *aWork) {
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

// 0x1e3ffe0
void AW_JumpDraw(AW_WORK_t *aWork) {
}
