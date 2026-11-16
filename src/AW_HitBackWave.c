#include "types.h"
#include "aw.h"
#include "aw_hitbackwave.h"
#include "bsflow.h"
#include "sbtl.h"
#include "sbtlevent.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e39590
void Init(void) {
  ;
}

// 0x1e395a0
s32 Add(s32 _ListID, f32 _BackDir, f32 _Size) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v12;
  AW_WORK_t *AW_Unit_ListID;
  s32 v14;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v22;
  AW_Func v23;
  AW_Func v24;
  AW_WORK_t *AW;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 Dir180;
  char *v33;
  s64 ToZ;
  sdfVector3_t v36;
  sdfQuaternion_t v37;

  ToZ = 0;
  UnitMng = wk->UnitMng;
  v11 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v11)
    return -1;
  v12 = v11;
  AW_Unit_ListID = GetAW_Unit_ListID(215, ListID);
  if (AW_Unit_ListID)
    return -1;
  Instance = get_Instance(AW_Unit_ListID);
  AwPrefab = GetAwPrefab(Instance, 40, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v36.x = 0.0;
  v36.y = 0.0;
  v36.z = 0.0;
  v37.x = x;
  v37.y = y;
  v37.z = z;
  v37.w = w;
  v22 = Instantiate_object__39504752(AwPrefab, v36, v37);
  v23 = Allocate(AW_Func);
  _ctor(v23, 0, Method_Project_AW_HitBackWave_Calc__, 0);
  v24 = Allocate(AW_Func);
  _ctor(v24, 0, Method_Project_AW_HitBackWave_Draw__, 0);
  v14 = Add(215, 0.0, 0.0, 0.0, v22, v23, v24, 1);
  Set_HDEff(v14, 1, -1);
  AW = GetAW(v14);
  AW->Unit_ListID = ListID;
  sBtlGetUnitHelperPos(v12, 0);
  v27 = vct_A.y;
  AW->StepFloatA = BackDir;
  AW->StepFloatB = 0.0;
  AW->HDEff_PosLink = 0;
  AW->StepFloatC = v27;
  v28 = sBtlGet360(BackDir);
  sBtlGetMoveXZ(v12->pos.x, v12->pos.z, v28, AW->StepFloatB, (f32 *)&ToZ + 1, &ToZ);
  v29 = *((f32 *)&ToZ + 1) / -100.0;
  v30 = AW->StepFloatC / -100.0;
  v31 = *(f32 *)&ToZ / -100.0;
  Dir180 = sBtlGetDir180(v28);
  AW->X = v29;
  AW->Y = v30;
  AW->Z = v31;
  AW->Dir = Dir180;
  AW->Scale = Size;
  v33 = "AW_HitBackWave";
  AW->DbgStr = "AW_HitBackWave";
  return v14;
}

// 0x1e399f0
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v6;

  memset(&v6, 0, sizeof(v6));
  if (sBtlIsHuuma())
    goto LABEL_16;
  if (!IsAction(20) && !IsAction(21))
  {
    if (sBtlChkEvent())
      goto LABEL_16;
    if (ChkPause(aWork))
      return;
  }
LABEL_16:
  _GetEnumerator(&v6, aWork->ParticleSystemList);
  while (_MoveNext(&v6))
  {
    current = v6._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v6);
      return;
    }
  }
  _Dispose(&v6);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e39ca0
void Draw(AW_WORK_t *aWork) {
}
