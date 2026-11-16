#include "types.h"
#include "aw.h"
#include "aw_tamemax.h"
#include "sbtlplayer.h"
#include "sbtlscene.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

static void CalcPos(AW_WORK_t *aWork);

// 0x1e50660
void AW_TameInit(void) {
  ;
}

// 0x1e55fb0
s32 AW_TameAdd(void) {
  AW_WORK_t *AW_ID;
  s32 Idx;
  Il2CppObject *v4;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v10;
  AW_Func v11;
  AW_Func v12;
  s32 v13;
  AW_WORK_t *AW;
  char *v16;
  sdfVector3_t v18;
  sdfQuaternion_t v19;

  AW_ID = GetAW_ID(239);
  if (AW_ID)
  {
    Idx = AW_ID->Idx;
    DelAW(Idx, 1);
  }
  v4 = get_Instance(AW_ID)->AwPrefab[59];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v18.x = 0.0;
  v18.y = 0.0;
  v18.z = 0.0;
  v19.x = x;
  v19.y = y;
  v19.z = z;
  v19.w = w;
  v10 = Instantiate_object__39504752(v4, v18, v19);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0, Method_Project_AW_TameMax_Calc__, 0);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_TameMax_Draw__, 0);
  v13 = Add(239, 0.0, 0.0, 0.0, v10, v11, v12, 1);
  Set_HDEff(v13, 1, -1);
  AW = GetAW(v13);
  AW->StepCnt = 0;
  CalcPos(AW);
  v16 = "AW_TameMax";
  AW->DbgStr = "AW_TameMax";
  return v13;
}

// 0x1e56230
static void CalcPos(AW_WORK_t *aWork) {
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 Dir180;
  sdfVector4_t v15;

  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  x = PlayerUnit->rot.x;
  y = PlayerUnit->rot.y;
  z = PlayerUnit->rot.z;
  w = PlayerUnit->rot.w;
  v15.x = x;
  v15.y = y;
  v15.z = z;
  v15.w = w;
  RotToDir = sBtlGetRotToDir(v15);
  v10 = PlayerUnit->pos.z;
  v11 = PlayerUnit->pos.x;
  v12 = PlayerUnit->pos.y;
  v13 = (f32)(v12 + sBtlGetYukaEffY()) / -100.0;
  Dir180 = sBtlGetDir180(RotToDir);
  aWork->X = v11 / -100.0;
  aWork->Y = v13;
  aWork->Z = v10 / -100.0;
  aWork->Dir = Dir180;
}

// 0x1e50250
void AW_TameDeleteAll(void) {
  DelAW_ID(239, 1);
}

// 0x1e56360
void AW_TameDel(bool _Immed) {
  AW_WORK_t *AW_ID;
  s32 v5;

  AW_ID = GetAW_ID(239);
  if (!AW_ID)
    return;
  if (!AW_ID->Step || Immed)
  {
    if (Immed)
      v5 = 2;
    else
      v5 = 1;
    AW_ID->Step = v5;
  }
}

// 0x1e56420
void AW_TameCalc(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  s32 Step;
  s32 Idx;
  s32 v9;
  bool v10;
  System_Collections_Generic_List_Enumerator_T__o v11;
  System_Collections_Generic_List_Enumerator_T__o v12;

  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v11, aWork->ParticleSystemList);
  v4 = *(_OWORD *)&v11._list;
  v11._list = 0;
  *(u64 *)&v11._index = &v12;
  v12._current = v11._current;
  *(_OWORD *)&v12._list = v4;
  do
  {
    if (!_MoveNext(&v12))
    {
      _Dispose(&v12);
      goto LABEL_18;
    }
    current = v12._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v12);
  CalcPos(aWork);
  Step = aWork->Step;
  if (Step != 2)
  {
    if (Step == 1)
    {
      v9 = aWork->StepCnt + 1;
      v10 = aWork->StepCnt - 59 < 0;
      aWork->StepCnt = v9;
      if (v10 == __OFSUB__(v9, 60))
        aWork->Step = 2;
    }
    else if (!Step)
    {
      ++aWork->StepCnt;
    }
    return;
  }
LABEL_18:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e566c0
void AW_TameDraw(AW_WORK_t *aWork) {
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
