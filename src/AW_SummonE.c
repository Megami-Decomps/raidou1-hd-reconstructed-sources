#include "types.h"
#include "aw.h"
#include "aw_summone.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e50670
void Init(void) {
  ;
}

// 0x1e54560
s32 Add(s32 _ListID) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  f32 *v8;
  Il2CppObject *v9;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v15;
  AW_Func v16;
  AW_Func v17;
  s32 v18;
  AW_WORK_t *AW;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  char *v25;
  sdfVector3_t v27;
  sdfVector4_t v28;
  sdfQuaternion_t v29;

  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v7)
    return -1;
  v8 = v7;
  v9 = get_Instance(v7)->AwPrefab[149];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v27.x = 0.0;
  v27.y = 0.0;
  v27.z = 0.0;
  v29.x = x;
  v29.y = y;
  v29.z = z;
  v29.w = w;
  v15 = Instantiate_object__39504752(v9, v27, v29);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_SummonE_Calc__, 0);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_SummonE_Draw__, 0);
  v18 = Add(279, 0.0, 0.0, 0.0, v15, v16, v17, 1);
  Set_HDEff(v18, 1, -1);
  AW = GetAW(v18);
  AW->Unit_ListID = ListID;
  AW->Scale = 1.0;
  v20 = v8[45];
  v21 = v8[46];
  v22 = v8[47];
  v23 = v8[48];
  v28.x = v20;
  v28.y = v21;
  v28.z = v22;
  v28.w = v23;
  AW->Dir = sBtlGetRotToDir(v28);
  CalcPos(AW);
  v25 = "AW_SummonE";
  AW->DbgStr = "AW_SummonE";
  return v18;
}

// 0x1e54890
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  f32 v9;
  f32 z;
  f32 x;
  f32 y;
  f32 v13;
  f32 w;
  sdfVector4_t v16;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v6)
    return v6 != 0;
  v9 = (f32)(v6->pos.y / -100.0) + 0.03;
  z = v6->pos.z;
  aWork->X = v6->pos.x / -100.0;
  aWork->Y = v9;
  aWork->Z = z / -100.0;
  x = v6->rot.x;
  y = v6->rot.y;
  v13 = v6->rot.z;
  w = v6->rot.w;
  v16.x = x;
  v16.y = y;
  v16.z = v13;
  v16.w = w;
  aWork->Dir = sBtlGetRotToDir(v16);
  return v6 != 0;
}

// 0x1e549f0
void Calc(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v11;

  memset(&v11, 0, sizeof(v11));
  if (!IsSceanStop())
    goto LABEL_15;
  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v7)
    goto LABEL_15;
  if ((v7->status & 0x10) != 0 || (v7->vstatus & 0x2000000) != 0)
    goto LABEL_19;
LABEL_15:
  if (ChkPause(aWork))
    return;
LABEL_19:
  _GetEnumerator(&v11, aWork->ParticleSystemList);
  do
  {
    if (!_MoveNext(&v11))
    {
      _Dispose(&v11);
      goto LABEL_28;
    }
    current = v11._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v11);
  if (CalcPos(aWork))
    return;
LABEL_28:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e54d10
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
