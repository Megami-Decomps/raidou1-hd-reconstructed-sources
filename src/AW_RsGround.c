#include "types.h"
#include "aw.h"
#include "aw_rsground.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e4cd80
void Init(void) {
  ;
}

// 0x1e4cd90
s32 Add(f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  f32 Dir180;
  Il2CppObject *v11;
  f32 v12;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 w;
  Il2CppObject *v20;
  AW_Func v21;
  AW_Func v22;
  s32 v23;
  AW_WORK_t *AW;
  char *v25;
  AW_WORK_t *v26;
  sdfVector3_t v28;
  sdfQuaternion_t v29;

  Dir180 = sBtlGetDir180(Dir);
  v11 = get_Instance()->AwPrefab[141];
  v12 = X / -100.0;
  v14 = identityQuaternion.x;
  v15 = identityQuaternion.y;
  v16 = Y / -100.0;
  v17 = Z / -100.0;
  v18 = identityQuaternion.z;
  w = identityQuaternion.w;
  v28.x = v12;
  v28.y = v16;
  v28.z = v17;
  v29.x = v14;
  v29.y = v15;
  v29.z = v18;
  v29.w = w;
  v20 = Instantiate_object__39504752(v11, v28, v29);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0, Method_Project_AW_RsGround_Calc__, 0);
  v22 = Allocate(AW_Func);
  _ctor(v22, 0, Method_Project_AW_RsGround_Draw__, 0);
  v23 = Add(275, v12, v16, v17, v20, v21, v22, 1);
  Set_HDEff(v23, 1, -1);
  AW = GetAW(v23);
  v25 = "AW_RsGround";
  v26 = AW;
  AW->X = v12;
  AW->Y = v16;
  AW->Z = v17;
  AW->Dir = Dir180;
  AW->DbgStr = v25;
  return v26->UID;
}

// 0x1e4d010
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

// 0x1e4d250
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
