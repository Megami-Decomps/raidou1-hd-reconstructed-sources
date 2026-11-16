#include "types.h"
#include "aw.h"
#include "aw_approachatk.h"
#include "sbtlplayer.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);
static bool CalcPos_Kaya(AW_WORK_t *aWork);

// 0x1e2deb0
void AW_ApproachInit(void) {
  ;
}

// 0x1e2dec0
s32 AW_ApproachAdd(s32 _ListID, f32 _OfsDir, f32 _OfsLen) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v17;
  s32 v20;
  AW_WORK_t *v23;
  void *ParticleSystemList;
  const MethodInfo_2DFD680 *v25;
  f32 HDEff_SimSpeed;
  char *v28;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v31;
  UnityEngine_ParticleSystem_MainModule_o v32;
  sdfVector3_t v33;
  sdfQuaternion_t v34;

  memset(&v31, 0, sizeof(v31));
  m_ParticleSystem = 0;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 19, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v33.x = 0.0;
  v33.y = 0.0;
  v33.z = 0.0;
  v34.x = x;
  v34.y = y;
  v34.z = z;
  v34.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v33, v34);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0);
  v20 = Add(211, 0.0, 0.0, 0.0, v14, v15, v17, 1);
  Set_HDEff(v20, 1, -1);
  v23 = gWork[v20];
  v23->StepFloatA = OfsDir;
  v23->StepFloatB = OfsLen;
  ParticleSystemList = v23->ParticleSystemList;
  v25 = Method_System_Collections_Generic_List_ParticleSystem__GetEnumerator__;
  v23->HDEff_SkillID = 1308;
  v23->Unit_ListID = ListID;
  v23->HDEff_SimSpeed = 1.0;
  v23->HDEff_PosLink = 1;
  _GetEnumerator(&v31, ParticleSystemList, v25);
  while (_MoveNext(&v31))
  {
    v32.m_ParticleSystem = get_main(v31._current, 0).m_ParticleSystem;
    HDEff_SimSpeed = v23->HDEff_SimSpeed;
    m_ParticleSystem = v32.m_ParticleSystem;
    set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
  }
  _Dispose(&v31);
  CalcPos(v23);
  v28 = "AW_ApproachAtk";
  v23->DbgStr = "AW_ApproachAtk";
  return v23->UID;
}

// 0x1e2e3e0
void AW_ApproachDeleteAll(void) {
  DelAW_ID(211, 1);
}

// 0x1e2e240
static bool CalcPos(AW_WORK_t *aWork) {
    return 0;
}

// 0x1e2e460
void AW_ApproachCalc(AW_WORK_t *aWork) {
  void *ParticleSystemList;
  __int128 v4;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  s32 Idx;
  f32 EHitStop_Speed;
  void *v12;
  __int128 v13;
  f32 HDEff_SimSpeed;
  System_Collections_Generic_List_Enumerator_T__o v15;
  System_Collections_Generic_List_Enumerator_T__o v16;
  void *m_ParticleSystem;
  UnityEngine_ParticleSystem_MainModule_o v18;

  memset(&v16, 0, sizeof(v16));
  ParticleSystemList = aWork->ParticleSystemList;
  m_ParticleSystem = 0;
  _GetEnumerator(&v15, ParticleSystemList);
  v16._current = v15._current;
  v4 = *(_OWORD *)&v15._list;
  v15._list = 0;
  *(u64 *)&v15._index = &v16;
  *(_OWORD *)&v16._list = v4;
  do
  {
    if (!_MoveNext(&v16))
    {
      _Dispose(&v16);
      goto LABEL_11;
    }
  }
  while (!IsAlive_61441520(v16._current, 0));
  _Dispose(&v16);
  if (!CalcPos(aWork))
  {
LABEL_11:
    Idx = aWork->Idx;
    DelAW(Idx, 1);
    return;
  }
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  if (!PlayerUnit)
    return;
  EHitStop_Speed = 1.0;
  if (PlayerUnit->SlashSkillID == aWork->HDEff_SkillID && PlayerUnit->SlashUID == aWork->UID && (PlayerUnit->hstatus & 0x10000) != 0)
  {
    EHitStop_Speed = PlayerUnit->EHitStop_Speed;
  }
  if (EHitStop_Speed != aWork->HDEff_SimSpeed)
  {
    v12 = aWork->ParticleSystemList;
    aWork->HDEff_SimSpeed = EHitStop_Speed;
    _GetEnumerator(&v15, v12);
    v16._current = v15._current;
    v13 = *(_OWORD *)&v15._list;
    v15._list = 0;
    *(u64 *)&v15._index = &v16;
    *(_OWORD *)&v16._list = v13;
    while (_MoveNext(&v16))
    {
      v18.m_ParticleSystem = get_main(v16._current, 0).m_ParticleSystem;
      HDEff_SimSpeed = aWork->HDEff_SimSpeed;
      m_ParticleSystem = v18.m_ParticleSystem;
      set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
    }
    _Dispose(&v16);
  }
}

// 0x1e2e770
s32 AW_ApproachAdd_Kaya(s32 _ListID, f32 _OfsDir, f32 _OfsLen) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v17;
  s32 v20;
  AW_WORK_t *v23;
  void *ParticleSystemList;
  const MethodInfo_2DFD680 *v25;
  f32 HDEff_SimSpeed;
  char *v28;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v31;
  UnityEngine_ParticleSystem_MainModule_o v32;
  sdfVector3_t v33;
  sdfQuaternion_t v34;

  memset(&v31, 0, sizeof(v31));
  m_ParticleSystem = 0;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 19, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v33.x = 0.0;
  v33.y = 0.0;
  v33.z = 0.0;
  v34.x = x;
  v34.y = y;
  v34.z = z;
  v34.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v33, v34);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0);
  v20 = Add(212, 0.0, 0.0, 0.0, v14, v15, v17, 1);
  Set_HDEff(v20, 1, -1);
  v23 = gWork[v20];
  v23->StepFloatA = OfsDir;
  v23->StepFloatB = OfsLen;
  ParticleSystemList = v23->ParticleSystemList;
  v25 = Method_System_Collections_Generic_List_ParticleSystem__GetEnumerator__;
  v23->HDEff_SkillID = 1558;
  v23->Unit_ListID = ListID;
  v23->HDEff_SimSpeed = 1.0;
  v23->HDEff_PosLink = 1;
  _GetEnumerator(&v31, ParticleSystemList, v25);
  while (_MoveNext(&v31))
  {
    v32.m_ParticleSystem = get_main(v31._current, 0).m_ParticleSystem;
    HDEff_SimSpeed = v23->HDEff_SimSpeed;
    m_ParticleSystem = v32.m_ParticleSystem;
    set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
  }
  _Dispose(&v31);
  CalcPos_Kaya(v23);
  v28 = "AW_ApproachAtk_Kaya";
  v23->DbgStr = "AW_ApproachAtk_Kaya";
  return v23->UID;
}

// 0x1e2eaf0
static bool CalcPos_Kaya(AW_WORK_t *aWork) {
    return 0;
}

// 0x1e2ec90
void AW_ApproachCalc_Kaya(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v6;

  memset(&v6, 0, sizeof(v6));
  _GetEnumerator(&v6, aWork->ParticleSystemList);
  do
  {
    if (!_MoveNext(&v6))
    {
      _Dispose(&v6);
      goto LABEL_9;
    }
  }
  while (!IsAlive_61441520(v6._current, 0));
  _Dispose(&v6);
  if (CalcPos_Kaya(aWork))
    return;
LABEL_9:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e2ee30
void AW_ApproachDraw(AW_WORK_t *aWork) {
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
