#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_mawasikeri.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e48290
void Init(void) {
  ;
}

// 0x1e482a0
s32 Add(s32 _ListID, f32 _Spd, s32 _Variation, SKLID _SklID) {
  s64 v8;
  s64 v9;
  Il2CppObject *v10;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  const MethodInfo_2DFD680 *v21;
  void *ParticleSystemList;
  f32 HDEff_SimSpeed;
  char *v25;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v28;
  UnityEngine_ParticleSystem_MainModule_o v29;
  sdfVector3_t v30;
  sdfQuaternion_t v31;

  v8 = 16;
  v28._current = 0;
  if (Variation == 1)
    v8 = 30;
  m_ParticleSystem = 0;
  v28._list = 0;
  *(u64 *)&v28._index = 0;
  if (Variation)
    v9 = v8;
  else
    v9 = 29;
  v10 = get_Instance(*(const MethodInfo **)&ListID)->AwPrefab[v9];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v30.x = 0.0;
  v30.y = 0.0;
  v30.z = 0.0;
  v31.x = x;
  v31.y = y;
  v31.z = z;
  v31.w = w;
  v16 = Instantiate_object__39504752(v10, v30, v31);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_Mawasikeri_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_Mawasikeri_Draw__, 0);
  v19 = Add(213, 0.0, 0.0, 0.0, v16, v17, v18, 1);
  Set_HDEff(v19, 1, -1);
  AW = GetAW(v19);
  AW->HDEff_SkillID = SklID;
  v21 = Method_System_Collections_Generic_List_ParticleSystem__GetEnumerator__;
  AW->HDEff_Speed = Spd;
  AW->HDEff_SimSpeed = Spd;
  ParticleSystemList = AW->ParticleSystemList;
  AW->HDEff_PosLink = 1;
  _GetEnumerator(&v28, ParticleSystemList, v21);
  while (_MoveNext(&v28))
  {
    v29.m_ParticleSystem = get_main(v28._current, 0).m_ParticleSystem;
    HDEff_SimSpeed = AW->HDEff_SimSpeed;
    m_ParticleSystem = v29.m_ParticleSystem;
    set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
  }
  _Dispose(&v28);
  CalcPos(AW);
  v25 = "AW_Mawasikeri";
  AW->DbgStr = "AW_Mawasikeri";
  return AW->UID;
}

// 0x1e48790
void DeleteAll(void) {
  DelAW_ID(213, 1);
}

// 0x1e48610
static bool CalcPos(AW_WORK_t *aWork) {
    return 0;
}

// 0x1e48810
void Calc(AW_WORK_t *aWork) {
  __int128 v5;
  Il2CppObject *current;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  s32 Idx;
  SBTLUNIT_WORK *v12;
  f32 HDEff_Speed;
  void *ParticleSystemList;
  __int128 v15;
  f32 HDEff_SimSpeed;
  System_Collections_Generic_List_Enumerator_T__o v17;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v19;
  f32 MSlow_Speed;
  UnityEngine_ParticleSystem_MainModule_o v21;

  MSlow_Speed = 0.0;
  memset(&v19, 0, sizeof(v19));
  m_ParticleSystem = 0;
  if ((wk->status4 & 0x800000) == 0)
  {
    if (sBtlIsHuuma())
      goto LABEL_15;
    if (!sBtlIsSetsumaPadStop() && !sBtlIsEnemyLastDeadStop())
    {
      if (ChkPause(aWork))
        return;
    }
  }
LABEL_15:
  _GetEnumerator(&v17, aWork->ParticleSystemList);
  v19._current = v17._current;
  v5 = *(_OWORD *)&v17._list;
  v17._list = 0;
  *(u64 *)&v17._index = &v19;
  *(_OWORD *)&v19._list = v5;
  do
  {
    if (!_MoveNext(&v19))
    {
      _Dispose(&v19);
      goto LABEL_26;
    }
    current = v19._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v19);
  if (CalcPos(aWork))
  {
    PlayerID = sBtlGetPlayerID();
    PlayerUnit = sBtlGetPlayerUnit(PlayerID);
    if (!PlayerUnit)
      return;
    v12 = PlayerUnit;
    HDEff_Speed = aWork->HDEff_Speed;
    if (!sBtlChkSlowMotion(PlayerUnit, &MSlow_Speed))
    {
      if (v12->SlashSkillID == aWork->HDEff_SkillID && v12->SlashUID == aWork->UID && (v12->hstatus & 0x10000) != 0)
      {
        HDEff_Speed = v12->EHitStop_Speed;
      }
      goto LABEL_9000;
    }
    HDEff_Speed = HDEff_Speed * MSlow_Speed;
LABEL_9000:
    if (HDEff_Speed != aWork->HDEff_SimSpeed)
    {
      ParticleSystemList = aWork->ParticleSystemList;
      aWork->HDEff_SimSpeed = HDEff_Speed;
      _GetEnumerator(&v17, ParticleSystemList);
      v19._current = v17._current;
      v15 = *(_OWORD *)&v17._list;
      v17._list = 0;
      *(u64 *)&v17._index = &v19;
      *(_OWORD *)&v19._list = v15;
      while (_MoveNext(&v19))
      {
        v21.m_ParticleSystem = get_main(v19._current, 0).m_ParticleSystem;
        HDEff_SimSpeed = aWork->HDEff_SimSpeed;
        m_ParticleSystem = v21.m_ParticleSystem;
        set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
      }
      _Dispose(&v19);
    }
    return;
  }
LABEL_26:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e48c50
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
