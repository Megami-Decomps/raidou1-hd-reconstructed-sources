#include "types.h"
#include "aw.h"
#include "aw_shields.h"
#include "sbtl.h"
#include "sbtlplayer.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e50640
void Init(void) {
  ;
}

// 0x1e522e0
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
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  char *v25;
  sdfVector3_t v27;
  sdfVector4_t v28;
  sdfQuaternion_t v29;

  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v7)
    return -1;
  v8 = v7;
  v9 = get_Instance(v7)->AwPrefab[2];
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
  _ctor(v16, 0, Method_Project_AW_ShieldS_Calc__, 0);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_ShieldS_Draw__, 0);
  v18 = Add(223, 0.0, 0.0, 0.0, v15, v16, v17, 1);
  Set_HDEff(v18, 1, -1);
  AW = GetAW(v18);
  AW->Unit_ListID = ListID;
  AW->Scale = 1.0;
  CalcPos(AW);
  v21 = v8[41];
  v22 = v8[42];
  v23 = v8[43];
  v24 = v8[44];
  v28.x = v21;
  v28.y = v22;
  v28.z = v23;
  v28.w = v24;
  sBtlPlay3DSE(0x1006Du, v28);
  v25 = "AW_ShieldS";
  AW->DbgStr = "AW_ShieldS";
  return v18;
}

// 0x1e52610
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  f32 X;
  f32 y;
  f32 z;
  f32 v13;
  SBTLCAMERA_WORK *camera;
  f32 v15;
  f32 v16;
  s64 v17;
  s64 GetZ;

  GetZ = 0;
  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v6)
    return v6 != 0;
  sBtlGetUnitHelperPos(v6, 0);
  X = v6->pos.x / -100.0;
  y = vct_A.y;
  z = v6->pos.z;
  aWork->X = X;
  aWork->Y = y / -100.0;
  v13 = z / -100.0;
  aWork->Z = z / -100.0;
  X = aWork->X;
  v13 = aWork->Z;
  camera = wk->scene->camera;
  v15 = camera->camerapos.x / -100.0;
  v16 = camera->camerapos.z / -100.0;
  sBtlGetMovePosToPos(X, v13, v15, v16, (f32)(v6->actaiwk->hit_area_r / 100.0) + 0.5, (f32 *)&GetZ + 1, &GetZ);
  v17 = GetZ;
  aWork->X = *((f32 *)&GetZ + 1);
  LODWORD(aWork->Z) = v17;
  aWork->Dir = sBtlGetPosToDir(*((f32 *)&v17 + 1), *(f32 *)&v17, v15, v16);
  return v6 != 0;
}

// 0x1e52860
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v7;

  memset(&v7, 0, sizeof(v7));
  if (!sBtlIsHuuma())
  {
    if (ChkPause(aWork))
      return;
  }
  _GetEnumerator(&v7, aWork->ParticleSystemList);
  do
  {
    if (!_MoveNext(&v7))
    {
      _Dispose(&v7);
      goto LABEL_20;
    }
    current = v7._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v7);
  if (CalcPos(aWork))
    return;
LABEL_20:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e52ad0
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
