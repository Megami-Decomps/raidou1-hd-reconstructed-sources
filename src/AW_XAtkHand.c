#include "types.h"
#include "aw.h"
#include "aw_xatkhand.h"
#include "dds3vrf.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

static s32 gTableHomingOfsDir[8];
static s32 gHomingOfsIdx;
static f32 *gTableMoveSpeed;
static s32 gMoveSpeedIdx;
static f32 *gTableMoveSpeedMax;
static s32 gMoveSpeedMaxIdx;

// 0x1e8e0f0
void Init(void) {
  ;
}

// 0x1e8e100
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ) {
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
  AW_WORK_t *v19;
  s32 max_length;
  s32 v26;
  s64 v27;
  f32 v29;
  s32 v30;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 PosToDir;
  s32 *v40;
  s64 v42;
  s32 v43;
  char *v44;
  sdfVector3_t v46;
  sdfQuaternion_t v47;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 104, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v46.x = UnityX;
  v46.y = UnityY;
  v46.z = UnityZ;
  v47.x = x;
  v47.y = y;
  v47.z = z;
  v47.w = w;
  v14 = Instantiate_object__39504752(AwPrefab, v46, v47);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_XAtkHand_Calc__, 0);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_XAtkHand_Draw__, 0);
  v17 = Add(259, UnityX, UnityY, UnityZ, v14, v15, v16, 1);
  AW = GetAW(v17);
  AW->Scale = 0.1;
  v19 = AW;
  max_length = gTableMoveSpeed->max_length;
  v26 = gMoveSpeedIdx + 1;
  v27 = (s64)gTableMoveSpeed + 4 * gMoveSpeedIdx;
  v29 = *(f32 *)(v27 + 32);
  v19->MoveSpdRate = 0.0001;
  v19->MoveSpd = v29;
  v30 = v26 % max_length;
  gMoveSpeedIdx = v30;
  LODWORD(v27) = gTableMoveSpeedMax->max_length;
  v19->MoveSpdMax = gTableMoveSpeedMax[gMoveSpeedMaxIdx];
  gMoveSpeedMaxIdx = ((s32)gMoveSpeedMaxIdx + 1) % (s32)v27;
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  if (PlayerUnit)
  {
    v34 = v19->X;
    v35 = PlayerUnit->pos.x / -100.0;
    v36 = v19->Z;
    v37 = PlayerUnit->pos.z / -100.0;
    PosToDir = sBtlGetPosToDir(v34, v36, v35, v37);
    v19->Dir = PosToDir;
    v19->MoveDir = PosToDir;
  }
  v42 = v40[2];
  v43 = *(u32 *)(*(u64 *)v40 + 4 * v42 + 32);
  v40[2] = ((s32)v42 + 1) % *(u32 *)(*(u64 *)v40 + 24);
  sBtlGetMoveXZ(0.0, 0.0, (f32)v43, 0.5, &v19->HomingX, &v19->HomingZ);
  v44 = "AW_XAtkHand";
  v19->DbgStr = "AW_XAtkHand";
  return v17;
}

// 0x1e8e4c0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8e530
void Calc(AW_WORK_t *aWork) {
  f32 v4;
  s64 v5;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  f32 X;
  f32 v9;
  f32 Z;
  f32 v11;
  f32 PosToDir;
  f32 v13;
  f32 v14;
  f32 v15;
  _BOOL4 v16;
  f32 v17;
  s32 Idx;
  f32 v20;
  f32 v21;
  f32 MoveDir;
  f32 MoveSpd;
  f32 MoveSpdMax;
  f32 MoveSpdRate;
  f32 v26;
  f32 v29;
  s64 ToZ;

  ToZ = 0;
  if (ChkPause(aWork))
    return;
  goto LABEL_7;
  if (!ChkPause(aWork))
  {
LABEL_7:
    switch (aWork->Step)
    {
      case 0:
        v4 = aWork->Scale + (f32)(VRF * 0.016666668);
        aWork->Scale = v4;
        if (v4 > 1.0)
        {
          aWork->Scale = 1.0;
          v5 = 1;
          goto LABEL_18;
        }
        return;
      case 1:
        PlayerID = sBtlGetPlayerID();
        PlayerUnit = sBtlGetPlayerUnit(PlayerID);
        if (PlayerUnit)
        {
          X = aWork->X;
          v9 = PlayerUnit->pos.x / -100.0;
          Z = aWork->Z;
          v11 = PlayerUnit->pos.z / -100.0;
          PosToDir = sBtlGetPosToDir(X, Z, v9, v11);
          aWork->Dir = sBtlGetDir_Hokan(aWork->Dir, PosToDir, 1.0);
          v13 = v9 + aWork->HomingX;
          v14 = v11 + aWork->HomingZ;
          v15 = sBtlGetPosToDir(aWork->X, aWork->Z, v13, v14);
          aWork->MoveDir = sBtlGetDir_Hokan(aWork->MoveDir, v15, 10.0);
          v16 = sBtlGetLenXZ(aWork->X, aWork->Z, v13, v14) < 1.0;
        }
        else
        {
          v16 = 0;
        }
        v20 = aWork->X;
        v21 = aWork->Z;
        MoveDir = aWork->MoveDir;
        MoveSpd = aWork->MoveSpd;
        sBtlGetMoveXZ(v20, v21, MoveDir, MoveSpd, (f32 *)&ToZ + 1, &ToZ);
        aWork->X = *((f32 *)&ToZ + 1);
        LODWORD(aWork->Z) = ToZ;
        MoveSpdMax = aWork->MoveSpdMax;
        aWork->MoveLen = MoveSpd + aWork->MoveLen;
        MoveSpdRate = aWork->MoveSpdRate;
        if (v16)
          MoveSpdRate = MoveSpdRate * -4.0;
        v26 = aWork->MoveSpd + MoveSpdRate;
        if (v26 < 0.0)
          v26 = 0.0;
        aWork->MoveSpd = v26;
        if (v26 > MoveSpdMax)
          aWork->MoveSpd = MoveSpdMax;
        v29 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v29;
        if (v29 > (f32)(FPS60 * 120.0))
          *(u64 *)&aWork->Step = (u32)(aWork->Step + 1);
        return;
      case 2:
        v17 = aWork->Scale + (f32)(VRF * -0.016666668);
        aWork->Scale = v17;
        if (v17 <= 0.0)
        {
          v5 = 3;
          aWork->Scale = 0.0;
LABEL_18:
          *(u64 *)&aWork->Step = v5;
        }
        return;
      case 3:
        Idx = aWork->Idx;
        DelAW(Idx, 1);
        return;
      default:
        return;
    }
  }
}

// 0x1e8e950
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
