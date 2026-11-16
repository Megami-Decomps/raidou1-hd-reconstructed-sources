#include "types.h"
#include "aw.h"
#include "aw_down.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e35940
void Init(void) {
  ;
}

// 0x1e35950
s32 Add(s32 _ListID, f32 _OfsDir, f32 _OfsLen, f32 _Size) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  char *v22;
  sdfVector3_t v24;
  sdfQuaternion_t v25;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 20, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v24.x = 0.0;
  v24.y = 0.0;
  v24.z = 0.0;
  v25.x = x;
  v25.y = y;
  v25.z = z;
  v25.w = w;
  v16 = Instantiate_object__39504752(AwPrefab, v24, v25);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_Down_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_Down_Draw__, 0);
  v19 = Add(214, 0.0, 0.0, 0.0, v16, v17, v18, 1);
  Set_HDEff(v19, 1, -1);
  AW = GetAW(v19);
  AW->Unit_ListID = ListID;
  AW->StepFloatA = OfsDir;
  AW->StepFloatB = OfsLen;
  AW->HDEff_PosLink = 1;
  AW->Scale = Size;
  CalcPos(AW);
  v22 = "AW_Down";
  AW->DbgStr = "AW_Down";
  return v19;
}

// 0x1e35d40
void ClearPosLink(void) {
  SetPosLink_ID(214, 0);
}

// 0x1e35bb0
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  f32 *v7;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 Dir180;
  s64 ToZ;
  sdfVector4_t v19;

  ToZ = 0;
  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  v7 = v6;
  if (v6 && !aWork->Step)
  {
    if (aWork->HDEff_PosLink)
    {
      x = v6->rot.x;
      y = v6->rot.y;
      z = v6->rot.z;
      w = v6->rot.w;
      v19.x = x;
      v19.y = y;
      v19.z = z;
      v19.w = w;
      RotToDir = sBtlGetRotToDir(v19);
      sBtlGetMoveXZ(v7[41], v7[43], RotToDir + aWork->StepFloatA, aWork->StepFloatB, (f32 *)&ToZ + 1, &ToZ);
      v13 = *((f32 *)&ToZ + 1) / -100.0;
      v14 = v7[42] / -100.0;
      v15 = *(f32 *)&ToZ / -100.0;
      Dir180 = sBtlGetDir180(RotToDir);
      aWork->X = v13;
      aWork->Y = v14;
      aWork->Z = v15;
      aWork->Dir = Dir180;
    }
    else
    {
      aWork->Step = 1;
    }
  }
  return v7 != 0;
}

// 0x1e35dc0
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v4;

  memset(&v4, 0, sizeof(v4));
  _GetEnumerator(&v4, aWork->ParticleSystemList);
  while (_MoveNext(&v4))
  {
    if (IsAlive_61441520(v4._current, 0))
    {
      _Dispose(&v4);
      return;
    }
  }
  _Dispose(&v4);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e35f50
void Draw(AW_WORK_t *aWork) {
}
