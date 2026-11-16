#include "types.h"
#include "aw.h"
#include "aw_setsuma2.h"
#include "sbtl.h"
#include "sbtlscene.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e50600
void Init(void) {
  ;
}

// 0x1e50e40
s32 Add(s32 _Unit_ListID, s32 _Variation) {
  f32 v4;
  f32 v5;
  f32 v7;
  f32 v8;
  f32 v9;
  s64 v10;
  Il2CppObject *v11;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v17;
  AW_Func v18;
  AW_Func v19;
  s32 v20;
  AW_WORK_t *AW;
  AW_WORK_t *v23;
  s32 v24;
  char *v25;
  f32 ZeroZ;
  s64 ZeroY;
  sdfVector3_t v29;
  sdfQuaternion_t v30;

  ZeroY = 0;
  ZeroZ = 0.0;
  sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, &ZeroZ);
  v4 = *((f32 *)&ZeroY + 1);
  v5 = *(f32 *)&ZeroY / -100.0;
  v7 = ZeroZ;
  v8 = v4 / -100.0;
  if (wk->encountno == 60)
    v5 = v5 + 0.05;
  v9 = v7 / -100.0;
  v10 = 91;
  switch (Variation)
  {
    case 0:
      break;
    case 2:
      v10 = 94;
      break;
    case 4:
      v10 = 95;
      break;
    case 5:
      v10 = 96;
      break;
    case 6:
      v9 = 0.0;
      v10 = 67;
      goto LABEL_17;
    case 7:
      v9 = 0.0;
      v10 = 68;
      goto LABEL_17;
    case 8:
      v9 = 0.0;
      v10 = 69;
LABEL_17:
      v5 = 0.0;
      v8 = 0.0;
      break;
    default:
      v10 = 92;
      break;
  }
  v11 = get_Instance(sbtl)->AwPrefab[v10];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v29.x = v8;
  v29.y = v5;
  v29.z = v9;
  v30.x = x;
  v30.y = y;
  v30.z = z;
  v30.w = w;
  v17 = Instantiate_object__39504752(v11, v29, v30);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_Setsuma2_Calc__, 0);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_Setsuma2_Draw__, 0);
  v20 = Add(217, v8, v5, v9, v17, v18, v19, 1);
  Set_HDEff(v20, 1, -1);
  AW = GetAW(v20);
  v23 = AW;
  AW->Variation = Variation;
  switch (Variation)
  {
    case 0:
      v24 = 0;
      AW->HDEff_PosLink = 1;
      goto LABEL_31;
    case 1:
    case 2:
    case 5:
      AW->HDEff_PosLink = 0;
      v24 = 100;
      goto LABEL_31;
    case 4:
      AW->HDEff_PosLink = 1;
      v24 = 200;
      goto LABEL_31;
    case 6:
    case 7:
      AW->HDEff_PosLink = 0;
      v24 = 300;
      goto LABEL_29;
    case 8:
      v24 = 400;
      AW->HDEff_PosLink = 0;
LABEL_29:
      AW->Dir = 0.0;
LABEL_31:
      AW->Step = v24;
      break;
    default:
      break;
  }
  CalcPos(AW);
  v25 = "AW_Setsuma2";
  v23->DbgStr = "AW_Setsuma2";
  return v20;
}

// 0x1e51460
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e514d0
void DeleteAll(void) {
  DelAW_ID(217, 1);
}

// 0x1e51200
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  s32 Step;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  u64 v15;
  f32 Dir180;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 *p_x;
  f32 v24;
  f32 v25;
  f32 v26;
  sdfVector4_t v28;
  sdfVector4_t v29;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  v7 = v6;
  if (!v6)
    return v7 != 0;
  Step = aWork->Step;
  if (Step == 200)
  {
    x = v6->rot.x;
    y = v6->rot.y;
    z = v6->rot.z;
    w = v6->rot.w;
    v29.x = x;
    v29.y = y;
    v29.z = z;
    v29.w = w;
    RotToDir = sBtlGetRotToDir(v29);
    sBtlGetUnitHelperPos(v7, 0);
    p_x = &vf00.x;
    v24 = p_x[4] / -100.0;
    v25 = p_x[6] / -100.0;
    v26 = (f32)(p_x[5] + 90.0) / -100.0;
    Dir180 = sBtlGetDir180(RotToDir);
    aWork->X = v24;
    aWork->Y = v26;
    aWork->Z = v25;
LABEL_20:
    aWork->Dir = Dir180;
    return v7 != 0;
  }
  if (!Step)
  {
    if (!aWork->HDEff_PosLink)
    {
      aWork->Step = 1;
      return v7 != 0;
    }
    v9 = v6->rot.x;
    v10 = v6->rot.y;
    v12 = v6->rot.z;
    v11 = v6->rot.w;
    v28.x = v9;
    v28.y = v10;
    v28.z = v12;
    v28.w = v11;
    v13 = sBtlGetRotToDir(v28);
    v14 = v7->pos.z / -100.0;
    v15 = vdiv_f32(*(float32x2_t *)&v7->pos.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
    Dir180 = sBtlGetDir180(v13);
    *(u64 *)&aWork->X = v15;
    aWork->Z = v14;
    goto LABEL_20;
  }
  return v7 != 0;
}

// 0x1e51550
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

// 0x1e516f0
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
