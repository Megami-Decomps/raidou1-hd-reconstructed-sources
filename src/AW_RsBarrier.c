#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_rsbarrier.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool toggle_kofun;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e4a3c0
void Init(void) {
  ;
}

// 0x1e4a3d0
s32 Add(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  SBTLUNIT_LISTWORK *UnitMng;
  void *v17;
  f32 *v18;
  SBTLUNIT_LISTWORK *v21;
  s32 playerID;
  struct AW_RsBarrier *v23;
  s32 v24;
  bool v25;
  s64 v27;
  char v28;
  Il2CppObject *v29;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 w;
  Il2CppObject *v35;
  AW_Func v36;
  AW_Func v37;
  s32 v38;
  AW_WORK_t *AW;
  AW_WORK_t *v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 Dir180;
  f32 v46;
  f32 v47;
  f32 v48;
  char *v49;
  s32 v50;
  sdfVector3_t v51;
  sdfQuaternion_t v52;

  UnitMng = wk->UnitMng;
  v17 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v17)
    return -1;
  v18 = v17;
  if (SkillID == 212)
  {
    v27 = 134;
    v50 = 0;
  }
  else if (SkillID == 313)
  {
    v21 = wk->UnitMng;
    playerID = wk->playerID;
    v17 = sBtlSearchUnit_ID(v21, playerID);
    if (*((u32 *)v17 + 91) == ListID)
    {
      v23 = *((struct AW_RsBarrier **)v17 + 23);
      v24 = *((u32 *)v17 + 56);
      if (toggle_kofun)
      {
        if (v24)
        {
          v25 = 0;
        }
        else
        {
          v25 = !toggle_kofun;
        }
        toggle_kofun = v25;
        v27 = 140;
        v50 = 1;
      }
      else
      {
        if (v24)
        {
          v28 = 1;
        }
        else
        {
          v28 = !toggle_kofun;
        }
        v50 = 0;
        v27 = 139;
        toggle_kofun = v28;
      }
    }
    else
    {
      v50 = 0;
      v27 = 139;
    }
  }
  else
  {
    v50 = 0;
    v27 = 133;
  }
  v29 = get_Instance(v17)->AwPrefab[v27];
  v31 = identityQuaternion.x;
  v32 = identityQuaternion.y;
  v33 = identityQuaternion.z;
  w = identityQuaternion.w;
  v51.x = 0.0;
  v51.y = 0.0;
  v51.z = 0.0;
  v52.x = v31;
  v52.y = v32;
  v52.z = v33;
  v52.w = w;
  v35 = Instantiate_object__39504752(v29, v51, v52);
  v36 = Allocate(AW_Func);
  _ctor(v36, 0, Method_Project_AW_RsBarrier_Calc__, 0);
  v37 = Allocate(AW_Func);
  _ctor(v37, 0, Method_Project_AW_RsBarrier_Draw__, 0);
  v38 = Add(272, 0.0, 0.0, 0.0, v35, v36, v37, 1);
  Set_HDEff(v38, 1, -1);
  AW = GetAW(v38);
  AW->HDEff_SkillID = SkillID;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  v40 = AW;
  AW->Unit_ListID = ListID;
  AW->HDEff_PosLink = 1;
  AW->StepIntA = v50;
  v40->Dir = sBtlGetDir180(Dir);
  v41 = X / -100.0;
  v42 = Y / -100.0;
  v43 = Z / -100.0;
  Dir180 = sBtlGetDir180(Dir);
  v46 = v18[41];
  v47 = v18[42];
  v40->Dir = Dir180;
  v40->X = v41;
  v40->Y = v42;
  v48 = v18[43];
  v40->Z = v43;
  v40->VelocityX = v41 + (f32)(v46 / 100.0);
  v40->VelocityY = v42 + (f32)(v47 / 100.0);
  v40->VelocityZ = v43 + (f32)(v48 / 100.0);
  CalcPos(v40);
  v49 = "AW_RsBarrier";
  v40->DbgStr = "AW_RsBarrier";
  return v40->UID;
}

// 0x1e4a8c0
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  f32 z;
  f32 VelocityZ;
  s32 StepIntA;
  f32 x;
  f32 y;
  f32 w;
  f32 v14;
  f32 RotToDir;
  sdfVector4_t v17;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  v7 = v6;
  if (v6)
  {
    z = v6->pos.z;
    VelocityZ = aWork->VelocityZ;
    StepIntA = aWork->StepIntA;
    *(float32x2_t *)&aWork->X = vadd_f32(*(float32x2_t *)&aWork->VelocityX, vdiv_f32(*(float32x2_t *)&v6->pos.x, vdup_n_s32(0xC2C80000)));
    aWork->Z = VelocityZ + (f32)(z / -100.0);
    if (StepIntA == 1)
    {
      x = v6->rot.x;
      y = v6->rot.y;
      v14 = v6->rot.z;
      w = v6->rot.w;
      v17.x = x;
      v17.y = y;
      v17.z = v14;
      v17.w = w;
      RotToDir = sBtlGetRotToDir(v17);
      aWork->Dir = sBtlGetDir180(RotToDir);
    }
  }
  return v7 != 0;
}

// 0x1e4aa20
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v7;

  memset(&v7, 0, sizeof(v7));
  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v7, aWork->ParticleSystemList);
  while (_MoveNext(&v7))
  {
    current = v7._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v7);
      CalcPos(aWork);
      return;
    }
  }
  _Dispose(&v7);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e4ac90
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  void *v5;
  sdfVector3_t v6;
  sdfVector3_t v7;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v6.y = aWork->Dir;
  v6.x = 0.0;
  v6.z = 0.0;
  set_eulerAngles(v4, v6, 0);
  v5 = get_transform(aWork->Obj, 0);
  v7.x = aWork->Scale;
  v7.y = v7.x;
  v7.z = v7.x;
  set_localScale(v5, v7, 0);
}
