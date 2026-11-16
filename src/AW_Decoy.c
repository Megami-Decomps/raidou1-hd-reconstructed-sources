#include "types.h"
#include "aw.h"
#include "aw_decoy.h"
#include "sbtl.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static void DeleteID(s32 _ID);
static bool CalcPos(AW_WORK_t *aWork);

// 0x1e34480
void Init(void) {
  ;
}

// 0x1e34490
s32 Add(s32 _ListID, s32 _Ver) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v11;
  s32 v12;
  s32 v13;
  AW_WORK_t *AW_ID;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v23;
  AW_Func v24;
  AW_Func v25;
  s32 v26;
  AW_WORK_t *AW;
  char *v29;
  sdfVector3_t v34;
  sdfQuaternion_t v35;

  UnitMng = wk->UnitMng;
  if (!sBtlSearchUnit_ID(UnitMng, ListID))
    return -1;
  switch (Ver)
  {
    case 0:
      DelAW_ID(226, 1);
      DelAW_ID(227, 1);
      v11 = 42;
      v12 = 225;
      v13 = 228;
      goto LABEL_60;
    case 1:
      DelAW_ID(225, 1);
      DelAW_ID(227, 1);
      v11 = 43;
      v12 = 226;
      v13 = 228;
      goto LABEL_60;
    case 2:
      DelAW_ID(225, 1);
      DelAW_ID(226, 1);
      v11 = 44;
      v12 = 227;
      v13 = 228;
      goto LABEL_60;
    case 3:
      DelAW_ID(225, 1);
      DelAW_ID(226, 1);
      v11 = 45;
      v12 = 228;
      v13 = 227;
LABEL_60:
      DelAW_ID(v13, 1);
      AW_ID = GetAW_ID(v12);
      if (!AW_ID)
        goto LABEL_22;
      return -1;
LABEL_61:
      AW_ID = GetAW_ID(v12);
      if (AW_ID)
        return -1;
LABEL_22:
      Instance = get_Instance(AW_ID);
      AwPrefab = GetAwPrefab(Instance, v11, 0);
      x = identityQuaternion.x;
      y = identityQuaternion.y;
      z = identityQuaternion.z;
      w = identityQuaternion.w;
      v34.x = 0.0;
      v34.y = 0.0;
      v34.z = 0.0;
      v35.x = x;
      v35.y = y;
      v35.z = z;
      v35.w = w;
      v23 = Instantiate_object__39504752(AwPrefab, v34, v35);
      v24 = Allocate(AW_Func);
      _ctor(v24, 0, Method_Project_AW_Decoy_Calc__, 0);
      v25 = Allocate(AW_Func);
      _ctor(v25, 0, Method_Project_AW_Decoy_Draw__, 0);
      v26 = Add(v12, 0.0, 0.0, 0.0, v23, v24, v25, 4);
      Set_HDEff(v26, 1, -1);
      AW = GetAW(v26);
      AW->Unit_ListID = ListID;
      AW->Scale = 1.0;
      CalcPos(AW);
      sBtlPlaySE(0x5040012u);
      v29 = "AW_Decoy";
      AW->DbgStr = "AW_Decoy";
      return v26;
    default:
      v11 = 42;
      v12 = 225;
      goto LABEL_61;
  }
}

// 0x1e34b90
static void DeleteID(s32 _ID) {
  DelAW_ID(ID, 1);
}

// 0x1e34c00
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  f32 v9;
  f32 v10;
  f32 RotToDir;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v6)
    return v6 != 0;
  sBtlGetUnitHelperPos(v6, 0);
  v9 = vct_A.x / -100.0;
  v10 = vct_A.z / -100.0;
  RotToDir = sBtlGetRotToDir(v6->rot);
  aWork->X = v9;
  aWork->Z = v10;
  aWork->Y = 0.5;
  aWork->Dir = RotToDir;
  return v6 != 0;
}

// 0x1e34dc0
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v7;

  memset(&v7, 0, sizeof(v7));
  goto LABEL_3;
LABEL_9:
  if (!get_activeSelf(aWork->Obj, 0))
    SetActive(aWork->Obj, 1, 0);
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
  return;
LABEL_3:
  if (!ChkPause(aWork))
    goto LABEL_9;
  if (sBtlCheckSetsuma())
    goto LABEL_27;
  goto LABEL_9000;
  if (sBtlCheckSetsuma())
  {
LABEL_27:
    SetActive(aWork->Obj, 0, 0);
    return;
  }
LABEL_9000:
  if (sBtlPlayerCheckRSpirit())
    goto LABEL_27;
}

// 0x1e350b0
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
