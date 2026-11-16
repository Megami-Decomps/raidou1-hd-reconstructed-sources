#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_rsmagget.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e4d800
void Init(void) {
  ;
}

// 0x1e4d810
s32 Add(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_WORK *v16;
  Il2CppObject *v17;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 w;
  Il2CppObject *v23;
  AW_Func v24;
  AW_Func v25;
  s32 v26;
  AW_WORK_t *AW;
  AW_WORK_t *v28;
  float32x2_t v29;
  f32 v30;
  f32 Dir180;
  u64 v32;
  char *v34;
  sdfVector3_t v38;
  sdfQuaternion_t v39;

  UnitMng = wk->UnitMng;
  v15 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v15)
    return -1;
  v16 = v15;
  v17 = get_Instance(v15)->AwPrefab[143];
  v19 = identityQuaternion.x;
  v20 = identityQuaternion.y;
  v21 = identityQuaternion.z;
  w = identityQuaternion.w;
  v38.x = 0.0;
  v38.y = 0.0;
  v38.z = 0.0;
  v39.x = v19;
  v39.y = v20;
  v39.z = v21;
  v39.w = w;
  v23 = Instantiate_object__39504752(v17, v38, v39);
  v24 = Allocate(AW_Func);
  _ctor(v24, 0, Method_Project_AW_RsMagGet_Calc__, 0);
  v25 = Allocate(AW_Func);
  _ctor(v25, 0, Method_Project_AW_RsMagGet_Draw__, 0);
  v26 = Add(277, 0.0, 0.0, 0.0, v23, v24, v25, 1);
  Set_HDEff(v26, 1, -1);
  AW = GetAW(v26);
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->HDEff_PosLink = 1;
  AW->HDEff_SkillID = SkillID;
  AW->Unit_ListID = ListID;
  v28 = AW;
  v29.n64_u64[0] = vdiv_f32((float32x2_t)__PAIR64__(LODWORD(Y), LODWORD(X)), vdup_n_s32(0xC2C80000)).n64_u64[0];
  v30 = Z / -100.0;
  Dir180 = sBtlGetDir180(Dir);
  *(float32x2_t *)&v28->X = v29;
  v28->Z = v30;
  v28->Dir = Dir180;
  v32 = vadd_f32(v29, vdiv_f32(*(float32x2_t *)&v16->pos.x, vdup_n_s32(0x42C80000u))).n64_u64[0];
  v28->VelocityZ = v30 + (f32)(v16->pos.z / 100.0);
  *(u64 *)&v28->VelocityX = v32;
  CalcPos(v28);
  v34 = "AW_RsMagGet";
  v28->DbgStr = "AW_RsMagGet";
  return v28->UID;
}

// 0x1e4dbb0
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  f32 v9;
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
  v9 = v6->pos.z / -100.0;
  *(float32x2_t *)&aWork->X = vadd_f32(*(float32x2_t *)&aWork->VelocityX, vdiv_f32(*(float32x2_t *)&v6->pos.x, vdup_n_s32(0xC2C80000)));
  aWork->Z = aWork->VelocityZ + v9;
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

// 0x1e4dd20
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

// 0x1e4df70
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
