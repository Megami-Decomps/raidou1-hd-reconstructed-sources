#include "types.h"
#include "aw.h"
#include "aw_xatklaser.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e8f2b0
void Init(void) {
  ;
}

// 0x1e85e30
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, s32 _Group_AW_Idx, s32 _Group_AW_UID) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v20;
  AW_Func v21;
  AW_Func v22;
  s32 v23;
  AW_WORK_t *AW;
  f32 v25;
  char *v26;
  sdfVector3_t v28;
  sdfQuaternion_t v29;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 110, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v28.x = UnityX;
  v28.y = UnityY;
  v28.z = UnityZ;
  v29.x = x;
  v29.y = y;
  v29.z = z;
  v29.w = w;
  v20 = Instantiate_object__39504752(AwPrefab, v28, v29);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0, Method_Project_AW_XAtkLaser_Calc__, 0);
  v22 = Allocate(AW_Func);
  _ctor(v22, 0, Method_Project_AW_XAtkLaser_Draw__, 0);
  v23 = Add(256, UnityX, UnityY, UnityZ, v20, v21, v22, 1);
  Set_HDEff(v23, 1, -1);
  AW = GetAW(v23);
  v25 = AW->Y;
  v26 = "AW_XAtkLaser";
  AW->StepFloatA = 0.1;
  AW->Group_AW_Idx = Group_AW_Idx;
  AW->Group_AW_UID = Group_AW_UID;
  AW->Dir = UnityDir;
  AW->DbgStr = v26;
  AW->Y = v25 + 0.8;
  return v23;
}

// 0x1e860a0
s32 AW_XAtkAdd2(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, s32 _Group_AW_Idx, s32 _Group_AW_UID) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v20;
  AW_Func v21;
  AW_Func v22;
  s32 v23;
  AW_WORK_t *AW;
  f32 v25;
  char *v26;
  sdfVector3_t v28;
  sdfQuaternion_t v29;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 111, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v28.x = UnityX;
  v28.y = UnityY;
  v28.z = UnityZ;
  v29.x = x;
  v29.y = y;
  v29.z = z;
  v29.w = w;
  v20 = Instantiate_object__39504752(AwPrefab, v28, v29);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0, Method_Project_AW_XAtkLaser_Calc__, 0);
  v22 = Allocate(AW_Func);
  _ctor(v22, 0, Method_Project_AW_XAtkLaser_Draw__, 0);
  v23 = Add(256, UnityX, UnityY, UnityZ, v20, v21, v22, 1);
  Set_HDEff(v23, 1, -1);
  AW = GetAW(v23);
  v25 = AW->Y;
  v26 = "AW_XAtkLaser";
  AW->StepFloatA = 0.1;
  AW->Group_AW_Idx = Group_AW_Idx;
  AW->Group_AW_UID = Group_AW_UID;
  AW->Dir = UnityDir;
  AW->DbgStr = v26;
  AW->Y = v25 + 0.8;
  return v23;
}

// 0x1e8f2c0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8f330
void Calc(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  s32 v6;
  AW_WORK_t *AW;
  s32 Group_AW_Idx;
  s32 Idx;
  s32 v10;
  AW_WORK_t *v11;
  s32 v12;
  s32 Step;
  f32 v14;
  s32 v15;
  System_Collections_Generic_List_Enumerator_T__o v16;
  System_Collections_Generic_List_Enumerator_T__o v17;

  memset(&v17, 0, sizeof(v17));
  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v16, aWork->ParticleSystemList);
  v4 = *(_OWORD *)&v16._list;
  v16._list = 0;
  *(u64 *)&v16._index = &v17;
  v17._current = v16._current;
  *(_OWORD *)&v17._list = v4;
  do
  {
    if (!_MoveNext(&v17))
    {
      _Dispose(&v17);
      Group_AW_Idx = aWork->Group_AW_Idx;
      AW = GetAW(Group_AW_Idx);
      if (AW && AW->UID == aWork->Group_AW_UID)
        goto LABEL_25;
LABEL_26:
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      return;
    }
    current = v17._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v17);
  v6 = aWork->Group_AW_Idx;
  AW = GetAW(v6);
  if (!AW)
    goto LABEL_26;
  if (AW->UID != aWork->Group_AW_UID)
    goto LABEL_26;
  if (AW->StepBoolB)
  {
LABEL_25:
    AW->StepBoolA = 1;
    goto LABEL_26;
  }
  v10 = aWork->Group_AW_Idx;
  v11 = GetAW(v10);
  if (v11 && v11->UID == aWork->Group_AW_UID)
  {
    aWork->X = v11->X;
    aWork->Z = v11->Z;
    aWork->Dir = v11->Dir;
    if (v11->Step == 2)
      v12 = 0;
    else
      v12 = 15;
  }
  else
  {
    v12 = 0;
  }
  Step = aWork->Step;
  switch (Step)
  {
    case 3:
      goto LABEL_26;
    case 1:
      if (v12)
        return;
      v15 = 2;
      goto LABEL_44;
    case 0:
      v14 = aWork->StepFloatA + 0.06666667;
      aWork->StepFloatA = v14;
      if (v14 >= 1.0)
      {
        aWork->StepFloatA = 1.0;
        v15 = 1;
LABEL_44:
        aWork->Step = v15;
      }
      break;
  }
}

// 0x1e8f6e0
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
