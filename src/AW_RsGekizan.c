#include "types.h"
#include "aw.h"
#include "aw_rsgekizan.h"
#include "sbtl.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e4c4e0
void Init(void) {
  ;
}

// 0x1e4c4f0
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
  void *ParticleSystemList;
  const MethodInfo_2DFD680 *v19;
  f32 HDEff_SimSpeed;
  char *v22;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v25;
  UnityEngine_ParticleSystem_MainModule_o v26;
  sdfVector3_t v27;
  sdfQuaternion_t v28;

  memset(&v25, 0, sizeof(v25));
  m_ParticleSystem = 0;
  v2 = get_Instance(*(const MethodInfo **)&ListID)->AwPrefab[120];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v27.x = 0.0;
  v27.y = 0.0;
  v27.z = 0.0;
  v28.x = x;
  v28.y = y;
  v28.z = z;
  v28.w = w;
  v8 = Instantiate_object__39504752(v2, v27, v28);
  v9 = Allocate(AW_Func);
  _ctor(v9, 0, Method_Project_AW_RsGekizan_Calc__, 0);
  v10 = Allocate(AW_Func);
  _ctor(v10, 0, Method_Project_AW_RsGekizan_Draw__, 0);
  v11 = Add(270, 0.0, 0.0, 0.0, v8, v9, v10, 1);
  Set_HDEff(v11, 1, -1);
  AW = GetAW(v11);
  __asm { FMOV            V0.2S, #1.0 }
  AW->HDEff_SkillID = 158;
  AW->HDEff_PosLink = 1;
  ParticleSystemList = AW->ParticleSystemList;
  v19 = Method_System_Collections_Generic_List_ParticleSystem__GetEnumerator__;
  *(u64 *)&AW->HDEff_Speed = _D0;
  _GetEnumerator(&v25, ParticleSystemList, v19);
  while (_MoveNext(&v25))
  {
    v26.m_ParticleSystem = get_main(v25._current, 0).m_ParticleSystem;
    HDEff_SimSpeed = AW->HDEff_SimSpeed;
    m_ParticleSystem = v26.m_ParticleSystem;
    set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
  }
  _Dispose(&v25);
  CalcPos(AW);
  v22 = "AW_RsGekizan";
  AW->DbgStr = "AW_RsGekizan";
  return AW->UID;
}

// 0x1e4c830
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
  if (v6)
  {
    if (v6->motionno == 52)
    {
      if (!aWork->Step)
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
    }
    else
    {
      aWork->Step = 1;
    }
  }
  return v7 != 0;
}

// 0x1e4c990
void Calc(AW_WORK_t *aWork) {
  __int128 v6;
  Il2CppObject *current;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  f32 HDEff_Speed;
  void *ParticleSystemList;
  __int128 v13;
  f32 HDEff_SimSpeed;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v16;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v18;
  UnityEngine_ParticleSystem_MainModule_o v19;

  memset(&v18, 0, sizeof(v18));
  m_ParticleSystem = 0;
  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v16, aWork->ParticleSystemList);
  v18._current = v16._current;
  v6 = *(_OWORD *)&v16._list;
  v16._list = 0;
  *(u64 *)&v16._index = &v18;
  *(_OWORD *)&v18._list = v6;
  do
  {
    if (!_MoveNext(&v18))
    {
      _Dispose(&v18);
      goto LABEL_26;
    }
    current = v18._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v18);
  if (CalcPos(aWork))
  {
    PlayerID = sBtlGetPlayerID();
    PlayerUnit = sBtlGetPlayerUnit(PlayerID);
    if (PlayerUnit)
    {
      HDEff_Speed = aWork->HDEff_Speed;
      if (PlayerUnit->SlashSkillID == aWork->HDEff_SkillID && PlayerUnit->SlashUID == aWork->UID && (PlayerUnit->hstatus & 0x10000) != 0)
      {
        HDEff_Speed = PlayerUnit->EHitStop_Speed;
      }
      if (HDEff_Speed != aWork->HDEff_SimSpeed)
      {
        ParticleSystemList = aWork->ParticleSystemList;
        aWork->HDEff_SimSpeed = HDEff_Speed;
        _GetEnumerator(&v16, ParticleSystemList);
        v18._current = v16._current;
        v13 = *(_OWORD *)&v16._list;
        v16._list = 0;
        *(u64 *)&v16._index = &v18;
        *(_OWORD *)&v18._list = v13;
        while (_MoveNext(&v18))
        {
          v19.m_ParticleSystem = get_main(v18._current, 0).m_ParticleSystem;
          HDEff_SimSpeed = aWork->HDEff_SimSpeed;
          m_ParticleSystem = v19.m_ParticleSystem;
          set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
        }
        sub_33548(&v16);
      }
    }
    return;
  }
LABEL_26:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e4cd10
void Draw(AW_WORK_t *aWork) {
}
