#include "types.h"
#include "aw.h"
#include "aw_jumpkick2.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e406d0
void Init(void) {
  ;
}

// 0x1e406e0
s32 Add(s32 _ListID) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v14;
  AW_Func v15;
  AW_Func v16;
  s32 v17;
  AW_WORK_t *AW;
  char *v20;
  sdfVector3_t v22;
  sdfQuaternion_t v23;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  if (!sBtlSearchUnit_ID(UnitMng, playerID))
    return -1;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 13, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v22.x = 0.0;
  v22.y = 0.0;
  v22.z = 0.0;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v22, v23);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_JumpKick2_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_JumpKick2_Draw__, 0);
  v17 = Add(208, 0.0, 0.0, 0.0, v14, v15, v16, 1);
  Set_HDEff(v17, 1, -1);
  AW = GetAW(v17);
  AW->Unit_ListID = ListID;
  CalcPos(AW);
  v20 = "AW_JumpKick2";
  AW->DbgStr = "AW_JumpKick2";
  return v17;
}

// 0x1e410a0
void AW_JumpSetLanding(s32 _ListID) {
  GetAW_Unit_ListID_SubIdx(208, ListID, -1);
}

// 0x1e409a0
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  f32 x;
  f32 y;
  f32 z;
  f32 v11;
  f32 v12;
  f32 w;
  f32 v14;
  f32 RotToDir;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  bool v20;
  f32 v21;
  f32 v22;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  s32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 Dir180;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  bool v57;
  f32 ToZ;
  f32 ToX;
  sdfVector4_t v60;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  v7 = v6;
  if (v6 && v6->motionno == 158 && !aWork->Step)
  {
    x = v6->pos.x;
    y = v6->pos.y;
    z = v6->pos.z;
    ToZ = z;
    ToX = x;
    v11 = v6->rot.x;
    v12 = v6->rot.y;
    v14 = v6->rot.z;
    w = v6->rot.w;
    v60.x = v11;
    v60.y = v12;
    v60.z = v14;
    v60.w = w;
    RotToDir = sBtlGetRotToDir(v60);
    hModel = v7->hModel;
    aWork->Y = y / -100.0;
    MotionFrameF = mdlGetMotionFrameF(hModel);
    v20 = MotionFrameF < 13.0;
    if (MotionFrameF < 13.0)
    {
      v21 = aWork->Y;
      v22 = 3.46;
LABEL_36:
      v33 = v21 + v22;
      *(f32 *)&v34 = 50.0;
LABEL_37:
      v35 = *(f32 *)&v34;
LABEL_38:
      aWork->Y = v33;
      goto LABEL_39;
    }
    if (!v20 && MotionFrameF < 13.5)
    {
      v22 = aWork->Y;
      v31 = (f32)(MotionFrameF + -13.0) + (f32)(MotionFrameF + -13.0);
      v32 = (f32)(v31 * 0.47000027) + 3.4299998;
      if (v31 > 1.0)
        v32 = 3.9;
      if (v31 >= 0.0)
        v21 = v32;
      else
        v21 = 3.4299998;
      goto LABEL_36;
    }
    if (MotionFrameF >= 13.5 && MotionFrameF < 14.0)
    {
      v40 = aWork->Y;
      v41 = (f32)(MotionFrameF + -13.5) + (f32)(MotionFrameF + -13.5);
      v42 = (f32)(v41 * 0.00999999) + 3.9;
      if (v41 > 1.0)
        v42 = 3.91;
      if (v41 >= 0.0)
        v43 = v42;
      else
        v43 = 3.9;
    }
    else
    {
      if (MotionFrameF >= 14.0 && MotionFrameF < 14.5)
      {
        v44 = aWork->Y;
        v45 = (f32)(MotionFrameF + -14.0) + (f32)(MotionFrameF + -14.0);
        v46 = (f32)(v45 * 0.06) + 3.91;
        if (v45 > 1.0)
          v46 = 3.9700003;
        if (v45 >= 0.0)
          v47 = v46;
        else
          v47 = 3.91;
        goto LABEL_54;
      }
      if (MotionFrameF >= 14.5 && MotionFrameF < 15.0)
      {
        v26 = -14.5;
        v27 = -0.06;
        v28 = 3.9700003;
        v29 = 1.0;
        v30 = 3.91;
LABEL_64:
        v48 = (f32)(MotionFrameF + v26) + (f32)(MotionFrameF + v26);
        v49 = (f32)(v48 * v27) + v28;
        if (v48 > v29)
          v49 = v30;
        v35 = 100.0;
        if (v48 >= 0.0)
          v50 = v49;
        else
          v50 = v28;
        v33 = v50 + aWork->Y;
        goto LABEL_38;
      }
      if (MotionFrameF >= 15.0 && MotionFrameF < 15.5)
      {
        v26 = -15.0;
        v27 = -0.11000061;
        v28 = 3.91;
        v29 = 1.0;
        v30 = 3.7999997;
        goto LABEL_64;
      }
      if (MotionFrameF >= 15.5 && MotionFrameF < 16.0)
      {
        v26 = -15.5;
        v27 = -0.33999968;
        v28 = 3.7999997;
        v29 = 1.0;
        v30 = 3.46;
        goto LABEL_64;
      }
      if (MotionFrameF >= 16.0 && MotionFrameF < 16.5)
      {
        v26 = -16.0;
        v27 = -1.02;
        v28 = 3.46;
        v29 = 1.0;
        v30 = 2.44;
        goto LABEL_64;
      }
      if (MotionFrameF >= 16.5 && MotionFrameF < 17.0)
      {
        v51 = (f32)(MotionFrameF + -16.5) + (f32)(MotionFrameF + -16.5);
        v35 = 110.0;
        v52 = (f32)(v51 * -0.6200001) + 2.44;
        if (v51 > 1.0)
          v52 = 1.8199999;
        if (v51 >= 0.0)
          v53 = v52;
        else
          v53 = 2.44;
        v33 = v53 + aWork->Y;
        goto LABEL_38;
      }
      if (MotionFrameF >= 17.0 && MotionFrameF < 17.5)
      {
        v26 = -17.0;
        v27 = -0.7399999;
        v28 = 1.8199999;
        v29 = 1.0;
        v30 = 1.08;
        goto LABEL_64;
      }
      if (MotionFrameF >= 17.5 && MotionFrameF < 18.0)
      {
        v29 = 1.0;
        v26 = -17.5;
        v27 = -0.64000005;
        v28 = 1.08;
        v30 = 0.44;
        goto LABEL_64;
      }
      if (MotionFrameF >= 18.0 && MotionFrameF < 18.5)
      {
        v54 = 1.0;
        v55 = (f32)(MotionFrameF + -18.0) + (f32)(MotionFrameF + -18.0);
        if (v55 <= 1.0)
          v54 = v55;
        if (v55 >= 0.0)
          v56 = v54;
        else
          v56 = 0.0;
        aWork->Y = (f32)(0.44 - (f32)(v56 * 0.44)) + aWork->Y;
        v35 = (f32)((f32)(v56 * -10.0) + 100.0) + 100.0;
        goto LABEL_39;
      }
      if (MotionFrameF >= 18.5 && MotionFrameF < 19.0)
      {
        v47 = aWork->Y;
        v44 = 0.0;
LABEL_54:
        v33 = v47 + v44;
        *(f32 *)&v34 = 90.0;
        goto LABEL_37;
      }
      if ((MotionFrameF < 19.0 || MotionFrameF >= 19.5) && (MotionFrameF < 19.5 || MotionFrameF >= 20.0) && (MotionFrameF < 20.0 || MotionFrameF >= 20.5) && (MotionFrameF < 20.5 || MotionFrameF >= 21.0))
      {
        v57 = MotionFrameF >= 21.5 || MotionFrameF < 21.0;
        aWork->Y = aWork->Y + 0.0;
        if (v57)
          v35 = 70.0;
        else
          v35 = 75.0;
LABEL_39:
        sBtlGetMoveXZ(x, z, RotToDir + -1.5, v35, &ToX, &ToZ);
        v36 = ToX / -100.0;
        v37 = ToZ / -100.0;
        Dir180 = sBtlGetDir180(RotToDir);
        aWork->X = v36;
        aWork->Z = v37;
        aWork->Dir = Dir180;
        return v7 != 0;
      }
      v43 = aWork->Y;
      v40 = 0.0;
    }
    v33 = v43 + v40;
    *(f32 *)&v34 = 80.0;
    goto LABEL_37;
  }
  return v7 != 0;
}

// 0x1e41110
void Calc(AW_WORK_t *aWork) {
  __int128 v4;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  SBTLUNIT_WORK *v8;
  f32 v9;
  s32 Idx;
  void *ParticleSystemList;
  __int128 v12;
  f32 HDEff_SimSpeed;
  System_Collections_Generic_List_Enumerator_T__o v14;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v16;
  f32 MSlow_Speed;
  UnityEngine_ParticleSystem_MainModule_o v18;

  MSlow_Speed = 0.0;
  memset(&v16, 0, sizeof(v16));
  m_ParticleSystem = 0;
  if ((wk->status4 & 0x800000) == 0)
  {
    if (!sBtlIsSetsumaPadStop() && !sBtlIsEnemyLastDeadStop())
    {
      if (ChkPause(aWork))
        return;
    }
  }
  _GetEnumerator(&v14, aWork->ParticleSystemList);
  v16._current = v14._current;
  v4 = *(_OWORD *)&v14._list;
  v14._list = 0;
  *(u64 *)&v14._index = &v16;
  *(_OWORD *)&v16._list = v4;
  do
  {
    if (!_MoveNext(&v16))
    {
      _Dispose(&v16);
      goto LABEL_25;
    }
  }
  while (!IsAlive_61441520(v16._current, 0));
  _Dispose(&v16);
  if (!CalcPos(aWork))
  {
LABEL_25:
    Idx = aWork->Idx;
    DelAW(Idx, 1);
    return;
  }
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  if (PlayerUnit)
  {
    v8 = PlayerUnit;
    if (sBtlChkSlowMotion(PlayerUnit, &MSlow_Speed))
    {
      v9 = aWork->HDEff_Speed * MSlow_Speed;
      if (v9 == aWork->HDEff_SimSpeed)
        return;
LABEL_30:
      ParticleSystemList = aWork->ParticleSystemList;
      aWork->HDEff_SimSpeed = v9;
      _GetEnumerator(&v14, ParticleSystemList);
      v16._current = v14._current;
      v12 = *(_OWORD *)&v14._list;
      v14._list = 0;
      *(u64 *)&v14._index = &v16;
      *(_OWORD *)&v16._list = v12;
      while (_MoveNext(&v16))
      {
        v18.m_ParticleSystem = get_main(v16._current, 0).m_ParticleSystem;
        HDEff_SimSpeed = aWork->HDEff_SimSpeed;
        m_ParticleSystem = v18.m_ParticleSystem;
        set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
      }
      _Dispose(&v16);
      return;
    }
    v9 = 1.0;
    if (1.0 == aWork->HDEff_SimSpeed)
      return;
    goto LABEL_30;
  }
}

// 0x1e41500
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.y = aWork->Dir;
  v5.x = -30.0;
  v5.z = 0.0;
  set_eulerAngles(v4, v5, 0);
}
