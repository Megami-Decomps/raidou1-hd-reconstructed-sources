#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_rsmegidraon.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e4e800
void Init(void) {
  ;
}

// 0x1e4e810
s32 Add(s32 _ListID, SKLID _SkillID) {
  Il2CppObject *v5;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v11;
  AW_Func v12;
  AW_Func v13;
  s32 v14;
  AW_WORK_t *AW;
  AW_WORK_t *v16;
  char *v18;
  sdfVector3_t v20;
  sdfQuaternion_t v21;

  v5 = get_Instance(*(const MethodInfo **)&ListID)->AwPrefab[132];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v20.x = 0.0;
  v20.y = 0.0;
  v20.z = 0.0;
  v21.x = x;
  v21.y = y;
  v21.z = z;
  v21.w = w;
  v11 = Instantiate_object__39504752(v5, v20, v21);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_RsMegidraon_Calc__, 0);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0, Method_Project_AW_RsMegidraon_Draw__, 0);
  v14 = Add(272, 0.0, 0.0, 0.0, v11, v12, v13, 1);
  Set_HDEff(v14, 1, -1);
  AW = GetAW(v14);
  AW->HDEff_SkillID = SkillID;
  v16 = AW;
  AW->Unit_ListID = ListID;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->HDEff_PosLink = 1;
  CalcPos(AW);
  v18 = "AW_RsMegidraon";
  v16->DbgStr = "AW_RsMegidraon";
  return v16->UID;
}

// 0x1e4ea50
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  float32x2_t v7;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  sdfVector4_t v16;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v6)
    return v6 != 0;
  v7.n64_u64[0] = *(u64 *)&v6->pos.x;
  aWork->Z = v6->pos.z / -100.0;
  *(float32x2_t *)&aWork->X = vdiv_f32(v7, vdup_n_s32(0xC2C80000));
  x = v6->rot.x;
  y = v6->rot.y;
  z = v6->rot.z;
  w = v6->rot.w;
  v16.x = x;
  v16.y = y;
  v16.z = z;
  v16.w = w;
  RotToDir = sBtlGetRotToDir(v16);
  aWork->Dir = sBtlGetDir180(RotToDir);
  return v6 != 0;
}

// 0x1e4ebb0
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v7;

  memset(&v7, 0, sizeof(v7));
  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v7, aWork->ParticleSystemList);
  while (_MoveNext(&v7))
  {
    current = v7._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v7);
      CalcPos(aWork);
      return;
    }
  }
  _Dispose(&v7);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e4ee00
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
