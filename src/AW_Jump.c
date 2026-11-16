#include "types.h"
#include "aw.h"
#include "aw_jump.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e3f640
void Init(void) {
  ;
}

// 0x1e3f650
s32 Add(s32 _Dan, f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z, f32 _Ps2Dir) {
  f32 Dir180;
  s32 v12;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v15;
  f32 x;
  f32 y;
  f32 v19;
  f32 v20;
  f32 z;
  f32 w;
  Il2CppObject *v23;
  AW_Func v24;
  AW_Func v25;
  s32 v26;
  AW_WORK_t *AW;
  char *v28;
  sdfVector3_t v30;
  sdfQuaternion_t v31;

  Dir180 = sBtlGetDir180(Ps2Dir);
  if (Dan == 2)
    v12 = 55;
  else
    v12 = 54;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v12, 0);
  v15 = Ps2X / -100.0;
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  v19 = Ps2Y / -100.0;
  v20 = Ps2Z / -100.0;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v30.x = v15;
  v30.y = v19;
  v30.z = v20;
  v31.x = x;
  v31.y = y;
  v31.z = z;
  v31.w = w;
  v23 = Instantiate_object__39504752(AwPrefab, v30, v31);
  v24 = Allocate(AW_Func);
  _ctor(v24, 0, Method_Project_AW_Jump_Calc__, 0);
  v25 = Allocate(AW_Func);
  _ctor(v25, 0, Method_Project_AW_Jump_Draw__, 0);
  v26 = Add(242, v15, v19, v20, v23, v24, v25, 1);
  Set_HDEff(v26, 1, -1);
  AW = GetAW(v26);
  v28 = "AW_Jump";
  AW->HDEff_PosLink = 0;
  AW->X = v15;
  AW->Y = v19;
  AW->Z = v20;
  AW->Dir = Dir180;
  AW->DbgStr = v28;
  return v26;
}

// 0x1e3f8f0
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  if ((wk->status4 & 0x800000) == 0)
  {
    if (!sBtlIsSetsumaPadStop() && !sBtlIsEnemyLastDeadStop())
    {
      if (ChkPause(aWork))
        return;
    }
  }
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

// 0x1e3fb50
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
