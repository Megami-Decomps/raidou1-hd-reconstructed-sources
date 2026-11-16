#include "types.h"
#include "aw.h"
#include "aw_slashunitex.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e505d0
void AW_SlashInit(void) {
  ;
}

// 0x1e53bc0
s32 AW_SlashAdd(s32 _ListID, f32 _RootPosDir, f32 _RootPosLen, f32 _RootPosY, f32 _RootRotX, f32 _RootRotY, f32 _RootRotZ, f32 _Speed, f32 _Size, s32 _PrefabIdx) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v24;
  SBTLUNIT_WORK *v25;
  f32 y;
  f32 v27;
  u32 v28;
  f32 v29;
  f32 Dir180;
  f32 v32;
  void *Slash;
  f32 v35;
  f32 x;
  f32 v38;
  f32 w;
  f32 z;
  Il2CppObject *v41;
  void *transform;
  void *v43;
  f32 v44;
  f32 v45;
  AW_Func v46;
  AW_Func v47;
  s32 v48;
  AW_WORK_t *AW;
  void *ParticleSystemList;
  s32 use_skillid;
  f32 HDEff_SimSpeed;
  char *v53;
  f32 v55;
  f32 v56;
  sdfVector3_t v57;
  f32 v58;
  f32 v59;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v61;
  f32 ToZ;
  f32 ToX;
  UnityEngine_ParticleSystem_MainModule_o v64;
  sdfVector3_t v65;
  sdfVector3_t v66;
  sdfVector3_t v67;
  sdfQuaternion_t v68;

  memset(&v61, 0, sizeof(v61));
  m_ParticleSystem = 0;
  UnitMng = wk->UnitMng;
  v24 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v24)
    return -1;
  v56 = RootPosLen;
  v57.x = RootRotX;
  v57.y = RootRotY;
  v57.z = RootRotZ;
  v25 = v24;
  v58 = Size;
  y = v24->pos.y;
  v27 = v24->pos.x / -100.0;
  v29 = v24->pos.z / -100.0;
  ToZ = v29;
  ToX = v27;
  if (!v28)
  Dir180 = sBtlGetDir180(RootPosDir);
  v55 = Dir180;
  v59 = Speed;
  v32 = RootPosY;
  Slash = GetSlash(wk->bsc, PrefabIdx, 0);
  gPrefab_Slash = Slash;
  v35 = y / -100.0;
  x = identityQuaternion.x;
  v38 = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v65.x = v27;
  v65.y = v35;
  v65.z = v29;
  v68.x = x;
  v68.y = v38;
  v68.z = z;
  v68.w = w;
  v41 = Instantiate_object__39504752(gPrefab_Slash, v65, v68);
  transform = get_transform(v41, 0);
  v43 = Find(transform, "root", 0);
  sBtlGetMoveXZ(0.0, 0.0, v55, v56 / 100.0, &ToX, &ToZ);
  v66.z = ToZ;
  v66.x = ToX;
  v66.y = v32 / -100.0;
  set_localPosition(v43, v66, 0);
  set_localEulerAngles(v43, v57, 0);
  v67.x = v58;
  v67.y = 1.0;
  v67.z = v58;
  set_localScale(v43, v67, 0);
  v44 = ToZ;
  v45 = ToX;
  v46 = Allocate(AW_Func);
  _ctor(v46, 0, Method_Project_AW_SlashUnitEx_Calc_Slash__, 0);
  v47 = Allocate(AW_Func);
  _ctor(v47, 0, Method_Project_AW_SlashUnitEx_Draw_Slash__, 0);
  v48 = Add(201, v45, v35, v44, v41, v46, v47, 2);
  Set_HDEff(v48, 0, 0);
  AW = GetAW(v48);
  AW->wk = v25;
  AW->Unit_ListID = ListID;
  ParticleSystemList = AW->ParticleSystemList;
  use_skillid = v25->actwk->use_skillid;
  AW->HDEff_Speed = v59;
  AW->HDEff_SimSpeed = v59;
  AW->HDEff_PosLink = 1;
  AW->HDEff_SkillID = use_skillid;
  _GetEnumerator(&v61, ParticleSystemList);
  while (_MoveNext(&v61))
  {
    v64.m_ParticleSystem = get_main(v61._current, 0).m_ParticleSystem;
    HDEff_SimSpeed = AW->HDEff_SimSpeed;
    m_ParticleSystem = v64.m_ParticleSystem;
    set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
  }
  _Dispose(&v61);
  v53 = "AW_SlashUnitEx";
  AW->DbgStr = "AW_SlashUnitEx";
  return AW->UID;
}

// 0x1e4fbf0
void AW_SlashDeleteAll(void) {
  DelAW_ID(201, 1);
}

// 0x1e54160
void AW_SlashClearPosLink(void) {
  SetPosLink_ID(201, 0);
}

// 0x1e541e0
void AW_SlashCalc_Slash(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v9;
  f32 x;
  f32 y;
  SBTLUNIT_WORK *v12;
  f32 w;
  f32 z;
  f32 RotToDir;
  float32x2_t v16;
  f32 v17;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v19;
  System_Collections_Generic_List_Enumerator_T__o v20;
  sdfVector4_t v21;

  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v19, aWork->ParticleSystemList);
  v4 = *(_OWORD *)&v19._list;
  v19._list = 0;
  *(u64 *)&v19._index = &v20;
  v20._current = v19._current;
  *(_OWORD *)&v20._list = v4;
  while (_MoveNext(&v20))
  {
    current = v20._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v20);
      UnitMng = wk->UnitMng;
      Unit_ListID = aWork->Unit_ListID;
      v9 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
      if (v9)
      {
        x = v9->rot.x;
        y = v9->rot.y;
        v12 = v9;
        z = v9->rot.z;
        w = v9->rot.w;
        v21.x = x;
        v21.y = y;
        v21.z = z;
        v21.w = w;
        RotToDir = sBtlGetRotToDir(v21);
        if (aWork->HDEff_PosLink)
        {
          v16.n64_u64[0] = *(u64 *)&v12->pos.x;
          v17 = v12->pos.z;
          aWork->Dir = RotToDir;
          *(float32x2_t *)&aWork->X = vdiv_f32(v16, vdup_n_s32(0xC2C80000));
          aWork->Z = v17 / -100.0;
        }
      }
      return;
    }
  }
  _Dispose(&v20);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e544f0
void AW_SlashDraw_Slash(AW_WORK_t *aWork) {
}
