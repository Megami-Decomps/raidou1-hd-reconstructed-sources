#include "types.h"
#include "aw.h"
#include "aw_summonng.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e50680
void Init(void) {
  ;
}

// 0x1e54da0
s32 Add(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  Il2CppObject *v7;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v13;
  AW_Func v14;
  AW_Func v15;
  s32 v16;
  AW_WORK_t *AW;
  s32 ListID;
  AW_WORK_t *v19;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    return -1;
  v6 = v5;
  v7 = get_Instance(v5)->AwPrefab[65];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = 0.0;
  v23.y = 0.0;
  v23.z = 0.0;
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  v13 = Instantiate_object__39504752(v7, v23, v24);
  v14 = Allocate(AW_Func);
  _ctor(v14, 0, Method_Project_AW_SummonNg_Calc__, 0);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_SummonNg_Draw__, 0);
  v16 = Add(280, 0.0, 0.0, 0.0, v13, v14, v15, 1);
  Set_HDEff(v16, 1, -1);
  AW = GetAW(v16);
  ListID = v6->ListID;
  v19 = AW;
  AW->HDEff_PosLink = 1;
  AW->Unit_ListID = ListID;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  CalcPos(AW);
  v21 = "AW_SummonNg";
  v19->DbgStr = "AW_SummonNg";
  return v19->UID;
}

// 0x1e55240
s32 Add_Pur(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  Il2CppObject *v7;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v13;
  AW_Func v14;
  AW_Func v15;
  s32 v16;
  AW_WORK_t *AW;
  s32 ListID;
  AW_WORK_t *v19;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    return -1;
  v6 = v5;
  v7 = get_Instance(v5)->AwPrefab[66];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = 0.0;
  v23.y = 0.0;
  v23.z = 0.0;
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  v13 = Instantiate_object__39504752(v7, v23, v24);
  v14 = Allocate(AW_Func);
  _ctor(v14, 0, Method_Project_AW_SummonNg_Calc__, 0);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_SummonNg_Draw__, 0);
  v16 = Add(280, 0.0, 0.0, 0.0, v13, v14, v15, 1);
  Set_HDEff(v16, 1, -1);
  AW = GetAW(v16);
  ListID = v6->ListID;
  v19 = AW;
  AW->HDEff_PosLink = 1;
  AW->Unit_ListID = ListID;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  CalcPos(AW);
  v21 = "AW_SummonNg_Pur";
  v19->DbgStr = "AW_SummonNg_Pur";
  return v19->UID;
}

// 0x1e55500
void DeleteAll(void) {
  DelAW_ID(280, 1);
}

// 0x1e55060
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  f32 z;
  f32 v11;
  f32 RotToDir;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v6)
    return v6 != 0;
  sBtlGetUnitHelperPos(v6, 0);
  z = vct_A.z;
  v11 = v6->pos.y / -100.0;
  aWork->X = vct_A.x / -100.0;
  aWork->Y = v11;
  aWork->Z = z / -100.0;
  RotToDir = sBtlGetRotToDir(v6->rot);
  aWork->Dir = sBtlGetDir180(RotToDir);
  return v6 != 0;
}

// 0x1e55580
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v6;

  memset(&v6, 0, sizeof(v6));
  _GetEnumerator(&v6, aWork->ParticleSystemList);
  while (_MoveNext(&v6))
  {
    current = v6._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v6);
      CalcPos(aWork);
      return;
    }
  }
  _Dispose(&v6);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e55760
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
