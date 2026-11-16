#include "types.h"
#include "aw.h"
#include "aw_shieldb.h"
#include "sbtl.h"
#include "sbtlplayer.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e50620
void Init(void) {
  ;
}

// 0x1e51760
s32 Add(s32 _ListID, s32 acterID) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v9;
  f32 *v10;
  SBTLUNIT_LISTWORK *v12;
  SBTLUNIT_WORK *PlayerUnit;
  Il2CppObject *v14;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v20;
  AW_Func v21;
  AW_Func v22;
  s32 v23;
  AW_WORK_t *AW;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  char *v30;
  s32 PlayerID;
  sdfVector3_t v34;
  sdfVector4_t v35;
  sdfQuaternion_t v36;

  UnitMng = wk->UnitMng;
  v9 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v9)
    return -1;
  v10 = v9;
  if (acterID == -1)
  {
    PlayerID = sBtlGetPlayerID();
    PlayerUnit = sBtlGetPlayerUnit(PlayerID);
    if (PlayerUnit)
      goto LABEL_13;
    return -1;
  }
  else
  {
    v12 = wk->UnitMng;
    PlayerUnit = sBtlSearchUnit_ID(v12, acterID);
    if (PlayerUnit)
      goto LABEL_13;
    return -1;
  }
LABEL_13:
  v14 = get_Instance(PlayerUnit)->AwPrefab[1];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v34.x = 0.0;
  v34.y = 0.0;
  v34.z = 0.0;
  v36.x = x;
  v36.y = y;
  v36.z = z;
  v36.w = w;
  v20 = Instantiate_object__39504752(v14, v34, v36);
  v21 = Allocate(AW_Func);
  _ctor(v21, 0, Method_Project_AW_ShieldB_Calc__, 0);
  v22 = Allocate(AW_Func);
  _ctor(v22, 0, Method_Project_AW_ShieldB_Draw__, 0);
  v23 = Add(221, 0.0, 0.0, 0.0, v20, v21, v22, 1);
  Set_HDEff(v23, 1, -1);
  AW = GetAW(v23);
  AW->Unit_ListID = ListID;
  AW->Scale = 1.0;
  CalcPos(AW);
  v26 = v10[41];
  v27 = v10[42];
  v29 = v10[43];
  v28 = v10[44];
  v35.x = v26;
  v35.y = v27;
  v35.z = v29;
  v35.w = v28;
  sBtlPlay3DSE(0x1006Du, v35);
  v30 = "AW_ShieldB";
  AW->DbgStr = "AW_ShieldB";
  return v23;
}

// 0x1e51b50
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
  sBtlGetMovePosToPos(X, v13, v15, v16, v6->actaiwk->hit_area_r / 100.0, (f32 *)&GetZ + 1, &GetZ);
  v17 = GetZ;
  aWork->X = *((f32 *)&GetZ + 1);
  LODWORD(aWork->Z) = v17;
  aWork->Dir = sBtlGetPosToDir(*((f32 *)&v17 + 1), *(f32 *)&v17, v15, v16);
  return v6 != 0;
}

// 0x1e51da0
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

// 0x1e52010
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
