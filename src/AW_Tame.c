#include "types.h"
#include "aw.h"
#include "aw_tame.h"
#include "sbtlplayer.h"
#include "sbtlscene.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

static void CalcPos(AW_WORK_t *aWork);

// 0x1e50650
void Init(void) {
  ;
}

// 0x1e557d0
s32 Add(s32 _Variation) {
  AW_WORK_t *AW_ID;
  s32 Idx;
  s64 v6;
  s64 v7;
  Il2CppObject *v8;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v16;
  s32 v17;
  AW_WORK_t *AW;
  char *v20;
  sdfVector3_t v22;
  sdfQuaternion_t v23;

  AW_ID = GetAW_ID(238);
  if (AW_ID)
  {
    Idx = AW_ID->Idx;
    DelAW(Idx, 1);
  }
  v6 = 38;
  if (Variation == 1)
    v6 = 22;
  if (Variation == 2)
    v7 = 35;
  else
    v7 = v6;
  v8 = get_Instance(AW_ID)->AwPrefab[v7];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v22.x = 0.0;
  v22.y = 0.0;
  v22.z = 0.0;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  v14 = Instantiate_object__39504752(v8, v22, v23);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_Tame_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_Tame_Draw__, 0);
  v17 = Add(238, 0.0, 0.0, 0.0, v14, v15, v16, 1);
  Set_HDEff(v17, 1, -1);
  AW = GetAW(v17);
  AW->StepCnt = 0;
  AW->Variation = Variation;
  CalcPos(AW);
  v20 = "AW_Tame";
  AW->DbgStr = "AW_Tame";
  return v17;
}

// 0x1e55a80
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

// 0x1e501d0
void DeleteAll(void) {
  DelAW_ID(238, 1);
}

// 0x1e55bb0
void Del(bool _Immed) {
  AW_WORK_t *AW_ID;
  s32 v5;

  AW_ID = GetAW_ID(238);
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

// 0x1e55c70
void Calc(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  s32 Idx;
  s32 v8;
  bool v9;
  s32 v10;
  s32 v11;
  System_Collections_Generic_List_Enumerator_T__o v12;
  System_Collections_Generic_List_Enumerator_T__o v13;

  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v12, aWork->ParticleSystemList);
  v4 = *(_OWORD *)&v12._list;
  v12._list = 0;
  *(u64 *)&v12._index = &v13;
  v13._current = v12._current;
  *(_OWORD *)&v13._list = v4;
  do
  {
    if (!_MoveNext(&v13))
    {
      _Dispose(&v13);
LABEL_16:
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      return;
    }
    current = v13._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v13);
  CalcPos(aWork);
  switch (aWork->Step)
  {
    case 0:
      ++aWork->StepCnt;
      return;
    case 1:
      v11 = aWork->StepCnt + 1;
      v9 = aWork->StepCnt - 29 < 0;
      aWork->StepCnt = v11;
      if (v9 != __OFSUB__(v11, 30))
        return;
      v10 = 2;
      break;
    case 2:
    case 4:
      goto LABEL_16;
    case 3:
      v8 = aWork->StepCnt + 1;
      v9 = aWork->StepCnt - 69 < 0;
      aWork->StepCnt = v8;
      if (v9 != __OFSUB__(v8, 70))
        return;
      v10 = 4;
      break;
    default:
      return;
  }
  aWork->Step = v10;
}

// 0x1e55f40
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
