#include "types.h"
#include "aw.h"
#include "aw_approach.h"
#include "bsflow.h"
#include "sbtl.h"
#include "sbtlevent.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e2d3d0
void Init(void) {
  ;
}

// 0x1e2d3e0
s32 Add(s32 _ListID) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v10;
  AW_Func v11;
  AW_Func v13;
  s32 v16;
  AW_WORK_t *v20;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 15, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = 0.0;
  v23.y = 0.0;
  v23.z = 0.0;
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  v10 = Instantiate_object__39504752(AwPrefab, v23, v24);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0);
  v16 = Add(209, 0.0, 0.0, 0.0, v10, v11, v13, 1);
  Set_HDEff(v16, 1, -1);
  v20 = gWork[v16];
  v20->Unit_ListID = ListID;
  *(u64 *)&v20->HDEff_Speed = 0x3F8000003F800000LL;
  CalcPos(v20);
  v21 = "AW_Approach";
  v20->DbgStr = "AW_Approach";
  return v16;
}

// 0x1e2d790
void DeleteAll(void) {
  DelAW_ID(209, 1);
}

// 0x1e2d810
s32 Add_Kaya(s32 _ListID) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v10;
  AW_Func v11;
  AW_Func v13;
  s32 v16;
  AW_WORK_t *v20;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 58, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = 0.0;
  v23.y = 0.0;
  v23.z = 0.0;
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  v10 = Instantiate_object__39504752(AwPrefab, v23, v24);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0);
  v16 = Add(210, 0.0, 0.0, 0.0, v10, v11, v13, 1);
  Set_HDEff(v16, 1, -1);
  v20 = gWork[v16];
  v20->Unit_ListID = ListID;
  *(u64 *)&v20->HDEff_Speed = 0x3F8000003F800000LL;
  CalcPos(v20);
  v21 = "AW_Approach_Kaya";
  v20->DbgStr = "AW_Approach_Kaya";
  return v16;
}

// 0x1e2d640
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
  if (v6 && !aWork->Step)
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
  return v7 != 0;
}

// 0x1e2da70
void Calc(AW_WORK_t *aWork) {
  __int128 v4;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  s32 Idx;
  SBTLUNIT_WORK *v11;
  f32 HDEff_SimSpeed;
  f32 HDEff_Speed;
  void *ParticleSystemList;
  __int128 v15;
  f32 v16;
  System_Collections_Generic_List_Enumerator_T__o v17;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v19;
  f32 MSlow_Speed;
  UnityEngine_ParticleSystem_MainModule_o v21;

  MSlow_Speed = 0.0;
  memset(&v19, 0, sizeof(v19));
  m_ParticleSystem = 0;
  if (sBtlIsSetsumaPadStop() || sBtlIsEnemyLastDeadStop() || IsAction(20) || IsAction(21))
  {
    goto LABEL_13;
  }
  if (sBtlChkEvent())
    goto LABEL_13;
  if (!ChkPause(aWork))
  {
LABEL_13:
    _GetEnumerator(&v17, aWork->ParticleSystemList);
    v19._current = v17._current;
    v4 = *(_OWORD *)&v17._list;
    v17._list = 0;
    *(u64 *)&v17._index = &v19;
    *(_OWORD *)&v19._list = v4;
    do
    {
      if (!_MoveNext(&v19))
      {
        _Dispose(&v19);
        goto LABEL_21;
      }
    }
    while (!IsAlive_61441520(v19._current, 0));
    _Dispose(&v19);
    if (CalcPos(aWork))
    {
      PlayerID = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(PlayerID);
      if (!PlayerUnit)
        return;
      v11 = PlayerUnit;
      HDEff_SimSpeed = aWork->HDEff_SimSpeed;
      if (!sBtlChkSlowMotion(PlayerUnit, &MSlow_Speed))
      {
        if (HDEff_SimSpeed == aWork->HDEff_SimSpeed)
          return;
LABEL_32:
        ParticleSystemList = aWork->ParticleSystemList;
        aWork->HDEff_SimSpeed = HDEff_SimSpeed;
        _GetEnumerator(&v17, ParticleSystemList);
        v19._current = v17._current;
        v15 = *(_OWORD *)&v17._list;
        v17._list = 0;
        *(u64 *)&v17._index = &v19;
        *(_OWORD *)&v19._list = v15;
        while (_MoveNext(&v19))
        {
          v21.m_ParticleSystem = get_main(v19._current, 0).m_ParticleSystem;
          v16 = aWork->HDEff_SimSpeed;
          m_ParticleSystem = v21.m_ParticleSystem;
          set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, v16, 0);
        }
        _Dispose(&v19);
        return;
      }
      HDEff_Speed = aWork->HDEff_Speed;
      MSlow_Speed = 0.05;
      HDEff_SimSpeed = HDEff_Speed * 0.05;
      if ((f32)(HDEff_Speed * 0.05) == aWork->HDEff_SimSpeed)
        return;
      goto LABEL_32;
    }
LABEL_21:
    Idx = aWork->Idx;
    DelAW(Idx, 1);
  }
}

// 0x1e2de40
void Draw(AW_WORK_t *aWork) {
}
