#include "types.h"
#include "aw.h"
#include "aw_jumpkick1.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e40050
void Init(void) {
  ;
}

// 0x1e40060
s32 Add(s32 _ListID) {
  void *Instance;
  Il2CppObject *AwPrefab;
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

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 14, 0);
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
  v10 = Instantiate_object__39504752(AwPrefab, v18, v19);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0, Method_Project_AW_JumpKick1_Calc__, 0);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_JumpKick1_Draw__, 0);
  v13 = Add(207, 0.0, 0.0, 0.0, v10, v11, v12, 1);
  Set_HDEff(v13, 1, -1);
  AW = GetAW(v13);
  AW->Unit_ListID = ListID;
  CalcPos(AW);
  v16 = "AW_JumpKick1";
  AW->DbgStr = "AW_JumpKick1";
  return v13;
}

// 0x1e40410
void AW_JumpSetPosLinkOff(s32 _ListID) {
  AW_WORK_t *AW_Unit_ListID_SubIdx;

  AW_Unit_ListID_SubIdx = GetAW_Unit_ListID_SubIdx(207, ListID, -1);
  if (!AW_Unit_ListID_SubIdx)
    return;
  AW_Unit_ListID_SubIdx->Step = 1;
}

// 0x1e40290
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  float32x2_t v7;
  f32 x;
  f32 y;
  f32 v10;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 Dir180;
  sdfVector4_t v16;
  sdfVector4_t v17;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (v6 && !aWork->Step)
  {
    *(u64 *)&v16.x = 0;
    *(u64 *)&v16.z = 0;
    GetUnitHelperPos(v6, &v16);
    v7.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v16.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
    x = v6->rot.x;
    y = v6->rot.y;
    v10 = v16.z / -100.0;
    z = v6->rot.z;
    w = v6->rot.w;
    v17.x = x;
    v17.y = y;
    v17.z = z;
    v17.w = w;
    RotToDir = sBtlGetRotToDir(v17);
    Dir180 = sBtlGetDir180(RotToDir);
    *(float32x2_t *)&aWork->X = v7;
    aWork->Z = v10;
    aWork->Dir = Dir180;
  }
  return v6 != 0;
}

// 0x1e404c0
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  _GetEnumerator(&v5, aWork->ParticleSystemList);
  do
  {
    if (!_MoveNext(&v5))
    {
      _Dispose(&v5);
      goto LABEL_9;
    }
  }
  while (!IsAlive_61441520(v5._current, 0));
  _Dispose(&v5);
  if (CalcPos(aWork))
    return;
LABEL_9:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e40660
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
