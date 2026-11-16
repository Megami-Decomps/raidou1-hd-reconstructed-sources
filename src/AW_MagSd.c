#include "types.h"
#include "aw.h"
#include "aw_magsd.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e46d60
void Init(void) {
  ;
}

// 0x1e46d70
s32 Add(s32 _ListID) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  void *KudaObj;
  AW_WORK_t *AW_ID;
  Il2CppObject *v12;
  void *transform;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v16;
  s32 v17;
  AW_WORK_t *AW;
  char *v19;

  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v7)
    return -1;
  v8 = v7;
  KudaObj = v7->KudaObj;
  if (!!op_Equality(KudaObj, 0, 0))
    return -1;
  AW_ID = GetAW_ID(232);
  if (AW_ID)
    return -1;
  v12 = get_Instance(AW_ID)->AwPrefab[47];
  transform = get_transform(v8->MagSdObj, 0);
  v14 = Instantiate_object__39504352(v12, transform);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_MagSd_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_MagSd_Draw__, 0);
  v17 = Add(232, 0.0, 0.0, 0.0, v14, v15, v16, 1);
  Set_HDEff(v17, 1, -1);
  AW = GetAW(v17);
  AW->Unit_ListID = ListID;
  v19 = "AW_MagSd";
  AW->DbgStr = "AW_MagSd";
  DelAW_ID2(233, 234, 1);
  return v17;
}

// 0x1e47080
void Del(void) {
  AW_WORK_t *AW_ID_Default;
  s32 Idx;

  AW_ID_Default = GetAW_ID_Default(232);
  if (!AW_ID_Default)
    return;
  Idx = AW_ID_Default->Idx;
  DelAW(Idx, 1);
}

// 0x1e47140
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  if (sBtlIsSetsumaPadStop())
  {
    if (ChkPause(aWork))
      return;
  }
  _GetEnumerator(&v5, aWork->ParticleSystemList);
  while (_MoveNext(&v5))
  {
    current = v5._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v5);
      return;
    }
  }
  _Dispose(&v5);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e47370
void Draw(AW_WORK_t *aWork) {
  void *transform;
  sdfVector3_t v3;

  transform = get_transform(aWork->Obj, 0);
  v3.x = 0.0;
  v3.y = 0.0;
  v3.z = 0.0;
  set_localPosition(transform, v3, 0);
}
