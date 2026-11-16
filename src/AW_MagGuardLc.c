#include "types.h"
#include "aw.h"
#include "aw_magguardlc.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e456d0
void Init(void) {
  ;
}

// 0x1e456e0
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
  char *v20;

  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v7)
    return -1;
  v8 = v7;
  KudaObj = v7->KudaObj;
  if (!!op_Equality(KudaObj, 0, 0))
    return -1;
  AW_ID = GetAW_ID(236);
  if (AW_ID)
    return -1;
  v12 = get_Instance(AW_ID)->AwPrefab[147];
  transform = get_transform(v8->MagSdObj, 0);
  v14 = Instantiate_object__39504352(v12, transform);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_MagGuardLc_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_MagGuardLc_Draw__, 0);
  v17 = Add(236, 0.0, 0.0, 0.0, v14, v15, v16, 1);
  Set_HDEff(v17, 1, -1);
  AW = GetAW(v17);
  AW->Unit_ListID = ListID;
  AW->StepIntA = 0;
  if (wk->mode == 5)
    AW->StepIntA = 30;
  v20 = "AW_MagGuardLc";
  AW->DbgStr = "AW_MagGuardLc";
  DelAW_ID2(235, 237, 1);
  return v17;
}

// 0x1e45a30
void Del(void) {
  AW_WORK_t *AW_ID_Default;
  s32 Idx;

  AW_ID_Default = GetAW_ID_Default(236);
  if (!AW_ID_Default)
    return;
  Idx = AW_ID_Default->Idx;
  DelAW(Idx, 1);
}

// 0x1e45af0
void Calc(AW_WORK_t *aWork) {
  s32 mode;
  void *ParticleSystemList;
  Il2CppObject *current;
  __int128 v7;
  Il2CppObject *v8;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v10;
  System_Collections_Generic_List_Enumerator_T__o v11;

  memset(&v11, 0, sizeof(v11));
  mode = wk->mode;
  if (mode != 5)
    aWork->StepIntA = 0;
  if (mode == 5 && aWork->StepIntA >= 1)
  {
    ParticleSystemList = aWork->ParticleSystemList;
    aWork->StepIntA = 0;
    _GetEnumerator(&v10, ParticleSystemList);
    v11 = v10;
    v10._list = 0;
    *(u64 *)&v10._index = &v11;
    while (_MoveNext(&v11))
    {
      current = v11._current;
      if (!op_Equality(current, 0, 0))
        Simulate_61440688(current, 1.0, 1, 1, 0);
    }
    _Dispose(&v11);
  }
  else if (!sBtlIsSetsumaPadStop() && !sBtlIsEnemyLastDeadStop())
  {
    if (ChkPause(aWork))
      return;
  }
  _GetEnumerator(&v10, aWork->ParticleSystemList);
  v11._current = v10._current;
  v7 = *(_OWORD *)&v10._list;
  v10._list = 0;
  *(u64 *)&v10._index = &v11;
  *(_OWORD *)&v11._list = v7;
  while (_MoveNext(&v11))
  {
    v8 = v11._current;
    if (!op_Equality(v8, 0, 0) && IsAlive_61441520(v8, 0))
    {
      _Dispose(&v11);
      return;
    }
  }
  _Dispose(&v11);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e45eb0
void Draw(AW_WORK_t *aWork) {
  void *transform;
  sdfVector3_t v3;

  transform = get_transform(aWork->Obj, 0);
  v3.x = 0.0;
  v3.y = 0.0;
  v3.z = 0.0;
  set_localPosition(transform, v3, 0);
}
