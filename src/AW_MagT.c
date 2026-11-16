#include "types.h"
#include "aw.h"
#include "aw_magt.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e473b0
void Init(void) {
  ;
}

// 0x1e473c0
s32 Add(s32 _Variation, f32 _UX, f32 _UY, f32 _UZ) {
  s64 v9;
  Il2CppObject *v10;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  if ((u32)Variation > 0xA)
    v9 = 0;
  else
    v9 = *(&off_3E635C8 + Variation);
  v10 = get_Instance(*(const MethodInfo **)&Variation)->AwPrefab[v9];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = UX;
  v23.y = UY;
  v23.z = UZ;
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  v16 = Instantiate_object__39504752(v10, v23, v24);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_MagT_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_MagT_Draw__, 0);
  v19 = Add(224, UX, UY, UZ, v16, v17, v18, 1);
  Set_HDEff(v19, 1, -1);
  AW = GetAW(v19);
  v21 = "AW_MagT";
  AW->Variation = Variation;
  AW->Scale = 1.0;
  AW->DbgStr = v21;
  return v19;
}

// 0x1e47620
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v6;

  memset(&v6, 0, sizeof(v6));
  if (sBtlCheckSetsuma())
    goto LABEL_16;
  if (sBtlPlayerCheckRSpirit())
    goto LABEL_16;
  if ((aWork->Variation & 0xFFFFFFFE) != 4)
  {
    if (ChkPause(aWork))
      return;
  }
LABEL_16:
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

// 0x1e478f0
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
