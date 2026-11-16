#include "types.h"
#include "aw.h"
#include "aw_bulletmuzzle.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e30420
void AW_BulletInit(void) {
  ;
}

// 0x1e30430
s32 AW_BulletAdd(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir) {
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
  AW_Func v23;
  s32 v26;
  char *v29;
  AW_WORK_t *v30;
  sdfVector3_t v32;
  sdfQuaternion_t v33;

  Dir180 = sBtlGetDir180(SDir);
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 8, 0);
  v12 = SX / -100.0;
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  v16 = SY / -100.0;
  v17 = SZ / -100.0;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v32.x = v12;
  v32.y = v16;
  v32.z = v17;
  v33.x = x;
  v33.y = y;
  v33.z = z;
  v33.w = w;
  v20 = Instantiate_object__39504752(AwPrefab, v32, v33);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0);
  v23 = Allocate(AW_Func);
  _ctor(v23, 0);
  v26 = Add(203, v12, v16, v17, v20, v21, v23, 1);
  Set_HDEff(v26, 1, -1);
  v29 = "AW_BulletMuzzle";
  v30 = gWork[v26];
  v30->Dir = Dir180;
  v30->DbgStr = v29;
  return v26;
}

// 0x1e306e0
s32 AW_BulletAdd_Setsuma(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir) {
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
  AW_Func v23;
  s32 v26;
  char *v29;
  AW_WORK_t *v30;
  sdfVector3_t v32;
  sdfQuaternion_t v33;

  Dir180 = sBtlGetDir180(SDir);
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 93, 0);
  v12 = SX / -100.0;
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  v16 = SY / -100.0;
  v17 = SZ / -100.0;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v32.x = v12;
  v32.y = v16;
  v32.z = v17;
  v33.x = x;
  v33.y = y;
  v33.z = z;
  v33.w = w;
  v20 = Instantiate_object__39504752(AwPrefab, v32, v33);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0);
  v23 = Allocate(AW_Func);
  _ctor(v23, 0);
  v26 = Add(203, v12, v16, v17, v20, v21, v23, 1);
  Set_HDEff(v26, 1, -1);
  v29 = "AW_BulletMuzzle";
  v30 = gWork[v26];
  v30->Dir = Dir180;
  v30->DbgStr = v29;
  return v26;
}

// 0x1e30990
void AW_BulletCalc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v9;

  memset(&v9, 0, sizeof(v9));
  if (sBtlCheckSetsuma())
    goto LABEL_15;
  if (sBtlPlayerCheckRSpirit())
    goto LABEL_15;
  if (ChkPause(aWork))
    return;
LABEL_15:
  _GetEnumerator(&v9, aWork->ParticleSystemList);
  while (_MoveNext(&v9))
  {
    current = v9._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v9);
      return;
    }
  }
  _Dispose(&v9);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e30c40
void AW_BulletDraw(AW_WORK_t *aWork) {
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
