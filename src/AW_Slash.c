#include "types.h"
#include "aw.h"
#include "aw_slash.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayertbl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

// 0x1e505c0
void Init(void) {
  ;
}

// 0x1e53040
s32 Add(SBTLUNIT_WORK *wk, s32 _TblIdx) {
  sbtlplayertbl_HDEFF_TABLE_t *HDEffTable_Idx;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RootPosDir;
  f32 Speed;
  f32 Size;
  s32 PrefabIdx;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 Dir180;
  void *Slash;
  f32 v22;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  Il2CppObject *v28;
  void *transform;
  void *v30;
  f32 v31;
  f32 v32;
  AW_Func v33;
  AW_Func v34;
  s32 v35;
  AW_WORK_t *AW;
  void *ParticleSystemList;
  const MethodInfo_2DFD680 *v38;
  s32 use_skillid;
  f32 HDEff_SimSpeed;
  char *v41;
  f32 v43;
  f32 RootPosLen;
  f32 RootPosY;
  f32 value;
  f32 RootRotY;
  f32 RootRotX;
  f32 v49;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v51;
  f32 ToZ;
  f32 ToX;
  UnityEngine_ParticleSystem_MainModule_o v54;
  sdfVector3_t v55;
  sdfVector3_t v56;
  sdfVector3_t v57;
  sdfVector3_t v58;
  sdfVector4_t v59;
  sdfQuaternion_t v60;

  memset(&v51, 0, sizeof(v51));
  m_ParticleSystem = 0;
  HDEffTable_Idx = sbtlplayertblGetHDEffTable_Idx(TblIdx);
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v59.x = x;
  v59.y = y;
  v59.z = z;
  v59.w = w;
  sBtlGetRotToDir(v59);
  RootPosDir = HDEffTable_Idx->RootPosDir;
  RootPosLen = HDEffTable_Idx->RootPosLen;
  RootPosY = HDEffTable_Idx->RootPosY;
  RootRotY = HDEffTable_Idx->RootRotY;
  RootRotX = HDEffTable_Idx->RootRotX;
  value = HDEffTable_Idx->RootRotZ;
  Speed = HDEffTable_Idx->Speed;
  Size = HDEffTable_Idx->Size;
  PrefabIdx = HDEffTable_Idx->PrefabIdx;
  v49 = Speed;
  v15 = wk->pos.y;
  v16 = wk->pos.x / -100.0;
  v17 = wk->pos.z / -100.0;
  ToZ = v17;
  ToX = v16;
  Dir180 = sBtlGetDir180(RootPosDir);
  v43 = Dir180;
  Slash = GetSlash(wk->bsc, PrefabIdx, 0);
  gPrefab_Slash = Slash;
  v22 = v15 / -100.0;
  v24 = identityQuaternion.x;
  v25 = identityQuaternion.y;
  v26 = identityQuaternion.z;
  v27 = identityQuaternion.w;
  v55.x = v16;
  v55.y = v22;
  v55.z = v17;
  v60.x = v24;
  v60.y = v25;
  v60.z = v26;
  v60.w = v27;
  v28 = Instantiate_object__39504752(gPrefab_Slash, v55, v60);
  transform = get_transform(v28, 0);
  v30 = Find(transform, "root", 0);
  sBtlGetMoveXZ(0.0, 0.0, v43, RootPosLen / 100.0, &ToX, &ToZ);
  v56.z = ToZ;
  v56.x = ToX;
  v56.y = RootPosY / -100.0;
  set_localPosition(v30, v56, 0);
  v57.y = RootRotY;
  v57.x = RootRotX;
  v57.z = value;
  set_localEulerAngles(v30, v57, 0);
  v58.y = 1.0;
  v58.x = Size;
  v58.z = Size;
  set_localScale(v30, v58, 0);
  v31 = ToZ;
  v32 = ToX;
  v33 = Allocate(AW_Func);
  _ctor(v33, 0, Method_Project_AW_Slash_Calc_Slash__, 0);
  v34 = Allocate(AW_Func);
  _ctor(v34, 0, Method_Project_AW_Slash_Draw_Slash__, 0);
  v35 = Add(200, v32, v22, v31, v28, v33, v34, 2);
  Set_HDEff(v35, 1, TblIdx);
  AW = GetAW(v35);
  AW->wk = wk;
  ParticleSystemList = AW->ParticleSystemList;
  v38 = Method_System_Collections_Generic_List_ParticleSystem__GetEnumerator__;
  use_skillid = wk->actwk->use_skillid;
  AW->HDEff_PosLink = 1;
  AW->HDEff_Speed = v49;
  AW->HDEff_SimSpeed = v49;
  AW->HDEff_SkillID = use_skillid;
  _GetEnumerator(&v51, ParticleSystemList, v38);
  while (_MoveNext(&v51))
  {
    v54.m_ParticleSystem = get_main(v51._current, 0).m_ParticleSystem;
    HDEff_SimSpeed = AW->HDEff_SimSpeed;
    m_ParticleSystem = v54.m_ParticleSystem;
    set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
  }
  _Dispose(&v51);
  v41 = "AW_Slash";
  AW->DbgStr = "AW_Slash";
  return AW->UID;
}

// 0x1e4fb70
void DeleteAll(void) {
  DelAW_ID(200, 1);
}

// 0x1e53590
void ClearPosLink(void) {
  SetPosLink_ID(200, 0);
}

// 0x1e53610
void Calc_Slash(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  s32 HDEff_TblIdx;
  sbtlplayertbl_HDEFF_TABLE_t *HDEffTable_Idx;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  s32 Idx;
  f32 x;
  f32 y;
  SBTLUNIT_WORK *v14;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 Speed;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 JumpY;
  void *ParticleSystemList;
  __int128 v25;
  f32 HDEff_SimSpeed;
  System_Collections_Generic_List_Enumerator_T__o v27;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v29;
  f32 MSlow_Speed;
  UnityEngine_ParticleSystem_MainModule_o v31;
  sdfVector4_t v32;

  MSlow_Speed = 0.0;
  memset(&v29, 0, sizeof(v29));
  m_ParticleSystem = 0;
  if ((wk->status4 & 0x800000) != 0)
    goto LABEL_16;
  if (sBtlIsHuuma())
    goto LABEL_16;
  if (!sBtlIsSetsumaPadStop() && !sBtlIsEnemyLastDeadStop())
  {
    if (ChkPause(aWork))
      return;
  }
LABEL_16:
  _GetEnumerator(&v27, aWork->ParticleSystemList);
  v29._current = v27._current;
  v4 = *(_OWORD *)&v27._list;
  v27._list = 0;
  *(u64 *)&v27._index = &v29;
  *(_OWORD *)&v29._list = v4;
  while (_MoveNext(&v29))
  {
    current = v29._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v29);
      HDEff_TblIdx = aWork->HDEff_TblIdx;
      HDEffTable_Idx = sbtlplayertblGetHDEffTable_Idx(HDEff_TblIdx);
      PlayerID = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(PlayerID);
      if (!PlayerUnit)
        return;
      x = PlayerUnit->rot.x;
      y = PlayerUnit->rot.y;
      v14 = PlayerUnit;
      z = PlayerUnit->rot.z;
      w = PlayerUnit->rot.w;
      v32.x = x;
      v32.y = y;
      v32.z = z;
      v32.w = w;
      RotToDir = sBtlGetRotToDir(v32);
      Speed = HDEffTable_Idx->Speed;
      if (aWork->HDEff_PosLink)
      {
        v19 = RotToDir;
        v20 = v14->pos.x / -100.0;
        v21 = v14->pos.y / -100.0;
        v22 = v14->pos.z / -100.0;
        JumpY = sBtlGetJumpY(v14);
        aWork->Z = v22;
        aWork->Dir = v19;
        aWork->X = v20;
        aWork->Y = v21 + (f32)(JumpY / -100.0);
      }
      if (!sBtlChkSlowMotion(v14, &MSlow_Speed))
      {
        if (v14->SlashSkillID == aWork->HDEff_SkillID && v14->SlashUID == aWork->UID && (v14->hstatus & 0x10000) != 0)
        {
          Speed = v14->EHitStop_Speed;
        }
        goto LABEL_9000;
      }
      Speed = aWork->HDEff_Speed * MSlow_Speed;
LABEL_9000:
      if (Speed != aWork->HDEff_SimSpeed)
      {
        ParticleSystemList = aWork->ParticleSystemList;
        aWork->HDEff_SimSpeed = Speed;
        _GetEnumerator(&v27, ParticleSystemList);
        v29._current = v27._current;
        v25 = *(_OWORD *)&v27._list;
        v27._list = 0;
        *(u64 *)&v27._index = &v29;
        *(_OWORD *)&v29._list = v25;
        while (_MoveNext(&v29))
        {
          v31.m_ParticleSystem = get_main(v29._current, 0).m_ParticleSystem;
          HDEff_SimSpeed = aWork->HDEff_SimSpeed;
          m_ParticleSystem = v31.m_ParticleSystem;
          set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
        }
        _Dispose(&v29);
      }
      return;
    }
  }
  _Dispose(&v29);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e53b50
void Draw_Slash(AW_WORK_t *aWork) {
}
