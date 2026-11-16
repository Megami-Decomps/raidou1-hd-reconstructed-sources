#include "types.h"
#include "aw.h"
#include "aw_hitlight.h"
#include "aw_kudaopen.h"
#include "aw_kudasupport.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e42270
void Init(void) {
  ;
}

// 0x1e42280
s32 Add(void) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v8;
  AW_Func v9;
  AW_Func v10;
  s32 v11;
  AW_WORK_t *AW;
  AW_WORK_t *v13;
  _BOOL8 v15;
  char *v17;
  sdfVector3_t v19;
  sdfQuaternion_t v20;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 39, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v19.x = 0.0;
  v19.y = 0.0;
  v19.z = 0.0;
  v20.x = x;
  v20.y = y;
  v20.z = z;
  v20.w = w;
  v8 = Instantiate_object__39504752(AwPrefab, v19, v20);
  v9 = Allocate(AW_Func);
  _ctor(v9, 0, Method_Project_AW_KudaSupport_Calc__, 0);
  v10 = Allocate(AW_Func);
  _ctor(v10, 0, Method_Project_AW_KudaSupport_Draw__, 0);
  v11 = Add(231, 0.0, 0.0, 0.0, v8, v9, v10, 1);
  Set_HDEff(v11, 1, -1);
  AW = GetAW(v11);
  AW->HDEff_PosLink = 1;
  v13 = AW;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  v15 = CalcPos(AW);
  v16 = Add_Support();
  Add_KudaSupport(v13->X, v13->Y, v13->Z);
  v17 = "AW_KudaSupport";
  v13->DbgStr = "AW_KudaSupport";
  return v13->UID;
}

// 0x1e42810
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e424c0
static bool CalcPos(AW_WORK_t *aWork) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  void *KudaSupportObj;
  u64 *p_KudaSupportObj;
  void *gameObject;
  void *transform;
  void *v13;
  void *v14;
  Il2CppClass *klass;
  void *v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  void *v21;
  f32 v22;
  f32 v23;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 Dir180;
  f32 v28;
  f32 x;
  f32 y;
  sdfVector4_t v32;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v7)
    return (char)v7;
  v8 = v7;
  KudaSupportObj = v7->KudaSupportObj;
  p_KudaSupportObj = &v7->KudaSupportObj;
  if (!op_Equality(KudaSupportObj, 0, 0))
    goto LABEL_21;
  gameObject = get_gameObject(v8->hModel->modelRoot->modelObj, 0);
  if (!op_Inequality(gameObject, 0, 0))
    goto LABEL_21;
  transform = get_transform(gameObject, 0);
  v13 = Find(transform, "program_ctrl/linknode", 0);
  if (op_Inequality(v13, 0, 0))
  {
    v14 = get_gameObject(v13, 0);
    klass = GetComponent_object_(v14)[4].klass;
    *p_KudaSupportObj = klass;
  }
LABEL_21:
  v16 = *p_KudaSupportObj;
  if (op_Equality(v16, 0, 0))
  {
    LOBYTE(v7) = 0;
    return (char)v7;
  }
  v17 = get_transform(v8->KudaSupportObj, 0);
  x = get_position(v17, 0).x;
  v18 = v8->KudaSupportObj;
  aWork->X = x;
  v19 = get_transform(v18, 0);
  y = get_position(v19, 0).y;
  v20 = v8->KudaSupportObj;
  aWork->Y = y;
  v21 = get_transform(v20, 0);
  aWork->Z = get_position(v21, 0).z;
  v22 = v8->rot.x;
  v23 = v8->rot.y;
  z = v8->rot.z;
  w = v8->rot.w;
  v32.x = v22;
  v32.y = v23;
  v32.z = z;
  v32.w = w;
  RotToDir = sBtlGetRotToDir(v32);
  Dir180 = sBtlGetDir180(RotToDir);
  v28 = aWork->X;
  aWork->Dir = Dir180;
  sBtlGetMoveXZ(v28, aWork->Z, Dir180 + 50.0, 0.1, &aWork->X, &aWork->Z);
  aWork->Y = aWork->Y + 0.05;
  LOBYTE(v7) = 1;
  return (char)v7;
}

// 0x1e42880
void Calc(AW_WORK_t *aWork) {
  __int128 v4;
  Il2CppObject *current;
  f32 v8;
  char v9;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v11;
  System_Collections_Generic_List_Enumerator_T__o v12;

  memset(&v12, 0, sizeof(v12));
  if (!sBtlIsHuuma())
  {
    if (ChkPause(aWork))
      return;
  }
  _GetEnumerator(&v11, aWork->ParticleSystemList);
  v12._current = v11._current;
  v4 = *(_OWORD *)&v11._list;
  v11._list = 0;
  *(u64 *)&v11._index = &v12;
  *(_OWORD *)&v12._list = v4;
  do
  {
    if (!_MoveNext(&v12))
    {
      _Dispose(&v12);
      goto LABEL_23;
    }
    current = v12._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v12);
  if (aWork->Step)
    return;
  if (!CalcPos(aWork))
  {
LABEL_23:
    goto LABEL_25;
  }
  v8 = aWork->StepTime + VRF_DeltaTime;
  aWork->StepTime = v8;
  if (v8 <= (f32)(FPS60 * 180.0))
    return;
  v9 = byte_5757EE6;
  *(u64 *)&aWork->Step = 1;
LABEL_25:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e42b90
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
