#include "types.h"
#include "aw.h"
#include "aw_plasmalaser.h"
#include "sbtlsound.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e48d10
void Init(void) {
  ;
}

// 0x1e48d20
s32 Add(f32 _X, f32 _Y, f32 _Z) {
  Il2CppObject *v7;
  f32 v8;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  v7 = get_Instance()->AwPrefab[111];
  v8 = X / -100.0;
  v10 = identityQuaternion.x;
  v11 = identityQuaternion.y;
  v12 = Y / -100.0;
  v13 = Z / -100.0;
  v14 = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = v8;
  v23.y = v12;
  v23.z = v13;
  v24.x = v10;
  v24.y = v11;
  v24.z = v14;
  v24.w = w;
  v16 = Instantiate_object__39504752(v7, v23, v24);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_PlasmaLaser_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_PlasmaLaser_Draw__, 0);
  v19 = Add(266, v8, v12, v13, v16, v17, v18, 1);
  Set_HDEff(v19, 1, -1);
  AW = GetAW(v19);
  v21 = "AW_PlasmaLaser";
  AW->StepIntA = 0;
  AW->Scale = 1.0;
  AW->DbgStr = v21;
  return v19;
}

// 0x1e48f70
void SetTgtPos(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ) {
  AW_WORK_t *AW_ID;
  f32 v15;
  f32 v16;
  f32 v17;

  AW_ID = GetAW_ID(266);
  if (!AW_ID)
    return;
  AW_ID->X = SX / -100.0;
  AW_ID->Y = SY / -100.0;
  AW_ID->HomingZ = EZ / -100.0;
  AW_ID->Z = SZ / -100.0;
  v15 = EX / -100.0;
  v16 = -7.0;
  AW_ID->HomingX = EX / -100.0;
  AW_ID->HomingY = EY / -100.0;
  if ((f32)(EZ / -100.0) < -7.0 || (v16 = 7.0, (f32)(EZ / -100.0) > 7.0))
    AW_ID->HomingZ = v16;
  v17 = 9.0;
  if (v15 > 9.0 || (v17 = -9.0, v15 < -9.0))
    AW_ID->HomingX = v17;
}

// 0x1e490a0
void SetScale(f32 _Scale) {
  AW_WORK_t *AW_ID;

  AW_ID = GetAW_ID(266);
  if (!AW_ID)
    return;
  AW_ID->Scale = Scale;
}

// 0x1e49130
void DeleteAll(void) {
  DelAW_ID(266, 1);
}

// 0x1e491b0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e49220
void Calc(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  s32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  s32 Step;
  f32 v11;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v13;
  System_Collections_Generic_List_Enumerator_T__o v14;
  sdfVector4_t v15;

  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v13, aWork->ParticleSystemList);
  v4 = *(_OWORD *)&v13._list;
  v13._list = 0;
  *(u64 *)&v13._index = &v14;
  v14._current = v13._current;
  *(_OWORD *)&v14._list = v4;
  do
  {
    if (!_MoveNext(&v14))
    {
      _Dispose(&v14);
      goto LABEL_22;
    }
    current = v14._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v14);
  v6 = aWork->StepIntA + 1;
  aWork->StepIntA = v6;
  if (v6 == 5)
  {
    v7 = aWork->HomingX * -100.0;
    v8 = aWork->HomingY * -100.0;
    v9 = aWork->HomingZ * -100.0;
    v15.w = 0.0;
    v15.x = v7;
    v15.y = v8;
    v15.z = v9;
    sBtlPlay3DSE(0x503001Fu, v15);
  }
  Step = aWork->Step;
  if (Step != 3)
  {
    if (!Step)
    {
      v11 = aWork->StepFloatA + 0.06666667;
      aWork->StepFloatA = v11;
      if (v11 >= 1.0)
      {
        aWork->StepFloatA = 1.0;
        aWork->Step = 1;
      }
    }
    return;
  }
LABEL_22:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e49500
void Draw(AW_WORK_t *aWork) {
  void *transform;
  f32 HomingX;
  f32 HomingY;
  f32 HomingZ;
  void *v7;
  void *v8;
  sdfVector3_t v9;
  sdfVector3_t v10;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  HomingX = aWork->HomingX;
  HomingY = aWork->HomingY;
  HomingZ = aWork->HomingZ;
  v7 = get_transform(aWork->Obj, 0);
  v9.x = HomingX;
  v9.y = HomingY;
  v9.z = HomingZ;
  LookAt(v7, v9);
  v8 = get_transform(aWork->Obj, 0);
  v10.x = aWork->Scale;
  v10.z = 1.0;
  v10.y = v10.x;
  set_localScale(v8, v10, 0);
}
