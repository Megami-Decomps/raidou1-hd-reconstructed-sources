#include "types.h"
#include "aw.h"
#include "aw_xatkchargel.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e8cc70
void AW_XAtkChargeInit(void) {
  ;
}

// 0x1e8cc80
s32 AW_XAtkChargeAdd(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  f32 v21;
  char *v22;
  sdfVector3_t v24;
  sdfQuaternion_t v25;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 112, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v24.x = UnityX;
  v24.y = UnityY;
  v24.z = UnityZ;
  v25.x = x;
  v25.y = y;
  v25.z = z;
  v25.w = w;
  v16 = Instantiate_object__39504752(AwPrefab, v24, v25);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_XAtkChargeL_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkChargeL_Draw__, 0);
  v19 = Add(262, UnityX, UnityY, UnityZ, v16, v17, v18, 1);
  Set_HDEff(v19, 1, -1);
  AW = GetAW(v19);
  v21 = AW->Y;
  v22 = "AW_XAtkChargeL";
  AW->Scale = 1.0;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->Dir = UnityDir;
  AW->DbgStr = v22;
  AW->Y = v21 + 0.8;
  return v19;
}

// 0x1e8cef0
void AW_XAtkChargeDelete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8cf60
void Delete(s32 aw_idx) {
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

// 0x1e8d040
void AW_XAtkChargeScaleFadeOut(s32 aw_idx) {
  AW_WORK_t *AW;

  if (aw_idx != -1)
  {
    AW = GetAW(aw_idx);
    if (!AW)
      return;
    AW->Step = 2;
  }
}

// 0x1e8d0d0
void AW_XAtkChargeSetPos(s32 aw_idx, f32 _X, f32 _Y, f32 _Z) {
  AW_WORK_t *AW;

  if (aw_idx != -1)
  {
    AW = GetAW(aw_idx);
    if (!AW)
      return;
    AW->X = X;
    AW->Y = Y;
    AW->Z = Z;
  }
}

// 0x1e8d180
void AW_XAtkChargeCalc(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  f32 v6;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v8;
  System_Collections_Generic_List_Enumerator_T__o v9;

  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v8, aWork->ParticleSystemList);
  v4 = *(_OWORD *)&v8._list;
  v8._list = 0;
  *(u64 *)&v8._index = &v9;
  v9._current = v8._current;
  *(_OWORD *)&v9._list = v4;
  do
  {
    if (!_MoveNext(&v9))
    {
      _Dispose(&v9);
      goto LABEL_17;
    }
    current = v9._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v9);
  if (aWork->Step != 2)
    return;
  v6 = aWork->Scale + -0.016666668;
  aWork->Scale = v6;
  if (v6 >= 0.0)
    return;
  aWork->Scale = 0.0;
LABEL_17:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8d3e0
void AW_XAtkChargeDraw(AW_WORK_t *aWork) {
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
  v7.z = 1.0;
  v7.y = v7.x;
  set_localScale(v5, v7, 0);
}
