#include "types.h"
#include "aw.h"
#include "aw_rszanzo.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e4f3d0
void Init(void) {
  ;
}

// 0x1e4f3e0
s32 Add(s32 _ListID) {
  Il2CppObject *v2;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v8;
  AW_Func v9;
  AW_Func v10;
  s32 v11;
  AW_WORK_t *AW;
  char *v14;
  sdfVector3_t v16;
  sdfQuaternion_t v17;

  v2 = get_Instance(*(const MethodInfo **)&ListID)->AwPrefab[135];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v16.x = 0.0;
  v16.y = 0.0;
  v16.z = 0.0;
  v17.x = x;
  v17.y = y;
  v17.z = z;
  v17.w = w;
  v8 = Instantiate_object__39504752(v2, v16, v17);
  v9 = Allocate(AW_Func);
  _ctor(v9, 0, Method_Project_AW_RsZanzo_Calc__, 0);
  v10 = Allocate(AW_Func);
  _ctor(v10, 0, Method_Project_AW_RsZanzo_Draw__, 0);
  v11 = Add(276, 0.0, 0.0, 0.0, v8, v9, v10, 1);
  Set_HDEff(v11, 1, -1);
  AW = GetAW(v11);
  CalcPos(AW);
  v14 = "AW_RsZanzo";
  AW->DbgStr = "AW_RsZanzo";
  return v11;
}

// 0x1e4f5f0
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  float32x2_t v8;
  f32 x;
  f32 y;
  f32 v11;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 Dir180;
  sdfVector4_t v17;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  v7 = v6;
  if (v6 && !aWork->Step)
  {
    v8.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v6->pos.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
    x = v6->rot.x;
    y = v6->rot.y;
    v11 = v6->pos.z / -100.0;
    z = v6->rot.z;
    w = v6->rot.w;
    v17.x = x;
    v17.y = y;
    v17.z = z;
    v17.w = w;
    RotToDir = sBtlGetRotToDir(v17);
    Dir180 = sBtlGetDir180(RotToDir);
    *(float32x2_t *)&aWork->X = v8;
    aWork->Z = v11;
    aWork->Dir = Dir180;
  }
  return v7 != 0;
}

// 0x1e4f740
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

// 0x1e4f8e0
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
