#include "types.h"
#include "aw.h"
#include "aw_xatkcharge.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e8c380
void Init(void) {
  ;
}

// 0x1e8c390
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v16;
  s32 v17;
  AW_WORK_t *AW;
  f32 v19;
  char *v20;
  sdfVector3_t v22;
  sdfQuaternion_t v23;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 106, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v22.x = UnityX;
  v22.y = UnityY;
  v22.z = UnityZ;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v22, v23);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_XAtkCharge_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_XAtkCharge_Draw__, 0);
  v17 = Add(261, UnityX, UnityY, UnityZ, v14, v15, v16, 4);
  Set_HDEff(v17, 1, -1);
  AW = GetAW(v17);
  v19 = AW->Y;
  v20 = "AW_XAtkCharge";
  AW->Scale = 0.1;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->DbgStr = v20;
  AW->Y = v19 + 0.03;
  return v17;
}

// 0x1e8c5f0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8c660
void Delete_2(s32 aw_idx) {
  AW_WORK_t *AW;
  AW_WORK_t *v4;
  s32 Idx;

  if (aw_idx != -1)
  {
    AW = GetAW(aw_idx);
    if (!AW)
      return;
    v4 = AW;
    Idx = v4->Idx;
    DelAW(Idx, 1);
  }
}

// 0x1e8c740
void AW_XAtkScaleFadeOut(s32 aw_idx) {
  AW_WORK_t *AW;

  if (aw_idx != -1)
  {
    AW = GetAW(aw_idx);
    if (!AW)
      return;
    AW->Step = 2;
  }
}

// 0x1e8c7d0
void AW_XAtkSetPos(s32 aw_idx, f32 _X, f32 _Y, f32 _Z) {
  AW_WORK_t *AW;

  if (aw_idx != -1)
  {
    AW = GetAW(aw_idx);
    if (!AW)
      return;
    AW->Z = Z;
    AW->X = X;
    AW->Y = Y + 0.03;
  }
}

// 0x1e8c890
void Calc(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  s32 Step;
  f32 v7;
  s32 Idx;
  f32 v9;
  System_Collections_Generic_List_Enumerator_T__o v10;
  System_Collections_Generic_List_Enumerator_T__o v11;

  goto LABEL_3;
LABEL_9:
  if (!get_activeSelf(aWork->Obj, 0))
    SetActive(aWork->Obj, 1, 0);
  _GetEnumerator(&v10, aWork->ParticleSystemList);
  v4 = *(_OWORD *)&v10._list;
  v10._list = 0;
  *(u64 *)&v10._index = &v11;
  v11._current = v10._current;
  *(_OWORD *)&v11._list = v4;
  do
  {
    if (!_MoveNext(&v11))
    {
      _Dispose(&v11);
LABEL_22:
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      return;
    }
    current = v11._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v11);
  Step = aWork->Step;
  if (Step)
  {
    if (Step != 2)
      return;
    v7 = aWork->Scale + -0.033333335;
    aWork->Scale = v7;
    if (v7 >= 0.0)
      return;
    aWork->Scale = 0.0;
    goto LABEL_22;
  }
  v9 = aWork->Scale + 0.01;
  aWork->Scale = v9;
  if (v9 > 1.0)
  {
    aWork->Scale = 1.0;
    aWork->Step = 1;
  }
  return;
LABEL_3:
  if (!ChkPause(aWork))
    goto LABEL_9;
  if (sBtlCheckSetsuma())
    goto LABEL_30;
  goto LABEL_9000;
  if (sBtlCheckSetsuma())
  {
LABEL_30:
    SetActive(aWork->Obj, 0, 0);
    return;
  }
LABEL_9000:
  if (sBtlPlayerCheckRSpirit())
    goto LABEL_30;
}

// 0x1e8cbe0
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
  v7.y = 1.0;
  v7.z = v7.x;
  set_localScale(v5, v7, 0);
}
