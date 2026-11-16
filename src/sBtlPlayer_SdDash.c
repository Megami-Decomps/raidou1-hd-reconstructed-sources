#include "types.h"
#include "SKLID.h"
#include "aw_rszanzo.h"
#include "aw_slash.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_sddash.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

#define SPEED_1 70
#define SPEED_1D 0
#define SPEED_1DH 1
#define SPEED_2 70
#define SPEED_2D 0
#define SPEED_2DH 1
#define SPEED_3 70
#define SPEED_3D 0
#define SPEED_3DN 1
#define SPEED_3E 5

typedef struct HIT_BUFF_t HIT_BUFF_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct HIT_BUFF_t {
    s32 Enemy_ListID;
    s32 Hit_SerialID;
};

static s32 gStep;
static f32 gStepTime;
static SKLID gSklID;
static bool gSklUse;
static bool gSklHit;
static f32 gMoveSpeed;
static s32 gStepCnt;
static f32 gDirOfs;
static f32 gCamStartX;
static f32 gCamStartY;
static f32 gCamStartZ;
static f32 gCamPrevX;
static f32 gCamPrevY;
static f32 gCamPrevZ;
static f32 gGoalOfsX;
static f32 gGoalOfsZ;
static HIT_BUFF_t *gHit_Buff;
static s32 gHit_Buff_Index;
static bool gHit_BS_LASTBS;
static s32 gClearIndex;

static void SetPlayerDir(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _SizeNml, f32 _RotSpeed, bool _Suka180);
static bool SetPlayerDir2(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _SizeNml, f32 _RotSpeed);

// 0x20ee1c0
void sBtlPlayerRSdDash_Init(void) {
  HIT_BUFF_t *v2;
  s64 v5;
  s64 v6;
  s32 *gHit_Buff_local;
  Il2CppObject *v9;

  if (gHit_Buff)
    return;
  v2 = NewSpecific(HIT_BUFF_t, 0x10u);
  gHit_Buff = v2;
  v5 = 0;
  v6 = 8;
  while (1)
  {
    gHit_Buff_local = gHit_Buff;
    if (v5 >= gHit_Buff_local[6])
      break;
    gHit_Buff_local = gHit_Buff;
    v9 = Allocate(HIT_BUFF_t);
    _ctor(v9, 0);
    v9[1].klass = 0;
    QueryInterface(v9, *(void **)(*(u64 *)gHit_Buff_local + 64));
    *(u64 *)&gHit_Buff_local[v6] = v9;
    ++v5;
    v6 += 2;
  }
}

// 0x20ee390
void sBtlPlayerRSdDash_Hit(SBTLUNIT_WORK *wkDmg, s32 _SerialID) {
  s64 v9;
  s64 v10;

  v9 = (s64)gHit_Buff + 8 * gHit_Buff_Index;
  LODWORD(gHit_Buff) = gHit_Buff->max_length;
  v10 = *(u64 *)(v9 + 32);
  *(u32 *)(v10 + 16) = wkDmg->ListID;
  *(u32 *)(v10 + 20) = SerialID;
  gHit_Buff_Index = ((s32)gHit_Buff_Index + 1) % (s32)gHit_Buff;
  gHit_BS_LASTBS = 1;
}

// 0x20ee430
bool sBtlPlayerRSdDash_ChkHit(SBTLUNIT_WORK *wkDmg, s32 _SerialID) {
  s32 devilid;
  bool v7;
  s64 i;
  HIT_BUFF_t *gHit_Buff_local;
  s64 max_length_low;

  devilid = (u16)wkDmg->para->devilid;
  if (devilid != 258 && devilid != 314)
  {
    goto LABEL_12;
  }
  if (gHit_BS_LASTBS)
    return 0;
LABEL_12:
  for (i = 4; ; ++i)
  {
    gHit_Buff_local = gHit_Buff;
    max_length_low = SLODWORD(gHit_Buff_local->max_length);
    v7 = i - 4 >= max_length_low;
    if (i - 4 >= max_length_low)
      return v7;
    if (*(u32 *)(*((u64 *)&gHit_Buff_local->obj.klass + i) + 16) != wkDmg->ListID)
      continue;
    if (*(u32 *)(*((u64 *)&gHit_Buff->obj.klass + i) + 20) == SerialID)
      return v7;
  }
  if (!gHit_BS_LASTBS)
    goto LABEL_12;
  return 0;
}

// 0x20ee5a0
s32 sBtlPlayerRSdDashInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;
  s32 hstatus;
  u32 v16;
  f32 v18;
  int8x16_t v19;
  int8x16_t v20;
  SBATTLE_WORK *v23;
  SBTLSCENE_WORK *scene;
  SBTLCAMERA_WORK *camera;
  int8x16_t v27;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 27;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 175, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  ClearPosLink();
  hstatus = wk->hstatus;
  wk->cmstatus = 0;
  wk->flg |= 0x40000u;
  wk->hstatus = hstatus & 0xFBF9FFFF | 0x4000000;
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u16 *)&gSklUse = 0;
  *(u64 *)&gMoveSpeed = 0;
  v16 = sub_1905740(100, 0);
  if (v16 >= 0x32)
    v18 = -90.0;
  else
    v18 = 90.0;
  gDirOfs = v18;
  SetPlayerDir(wk, gDirOfs, 0.8, 360.0, 0);
  v23 = wk;
  gClearIndex = ClearIndex;
  scene = v23->scene;
  gHit_BS_LASTBS = 0;
  camera = scene->camera;
  v19.n128_u64[0] = *(u64 *)&camera->camerapos.x;
  *(u64 *)&gCamStartX = v19.n128_u64[0];
  v20.n128_u32[0] = LODWORD(camera->camerapos.z);
  gGoalOfsX = 0.0;
  gGoalOfsZ = 0.0;
  v27 = vextq_s8(vextq_s8(v20, v20, 4u), v19, 0xCu);
  v27.n128_u32[3] = v27.n128_u32[0];
  *(int8x16_t *)&gCamStartZ = v27;
  return 2;
}

// 0x20eed90
void sBtlPlayerSetDamage(SBTLUNIT_WORK *wk_player, SBTLUNIT_WORK *wk_enemy) {
  s32 targetID;

  if (wk_player && wk_enemy && (~wk_player->side & 0x81) == 0)
  {
    if (wk->mode == 27)
    {
      targetID = wk_player->actaiwk->targetID;
      if (targetID != -1 && targetID == wk_enemy->ListID)
      {
        gSklHit = 1;
      }
    }
  }
}

// 0x20eee70
f32 sBtlPlayerGetMoveSdDash(SBTLUNIT_WORK *wk) {
  f32 result;

  result = 0.0;
  if (wk->mode != 27)
    return result;
  return gMoveSpeed;
}

// 0x20ee870
static void SetPlayerDir(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _SizeNml, f32 _RotSpeed, bool _Suka180) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;
  f32 x;
  f32 z;
  f32 v18;
  f32 v19;
  f32 PosToDir;
  f32 v21;
  sdfVector4_t *p_rot;
  f32 RotToDir;
  f32 v24;
  f32 Dir_Hokan;
  f32 v26;
  f32 y;
  f32 v28;
  f32 w;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v35;
  sdfVector4_t *v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v46;
  f32 v48;
  f32 v49;
  f32 v51;
  f32 Dir180;
  sdfVector4_t *p_rotbk;
  s64 ToZ;
  sdfVector4_t v59;
  sdfVector4_t v60;

  ToZ = 0;
  UnitMng = wk->UnitMng;
  targetID = wk->actaiwk->targetID;
  v14 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (v14)
  {
    v15 = v14;
    x = v14->pos.x;
    z = v14->pos.z;
    v18 = wk->pos.x;
    v19 = wk->pos.z;
    PosToDir = sBtlGetPosToDir(v18, v19, x, z);
    v21 = sBtlGet360(PosToDir + DirOfs);
    sBtlGetMoveXZ(v15->pos.x, v15->pos.z, v21, v15->actaiwk->hit_area_r * SizeNml, (f32 *)&ToZ + 1, &ToZ);
    p_rot = &wk->rot;
    RotToDir = sBtlGetRotToDir(wk->rot);
    v24 = sBtlGetPosToDir(wk->pos.x, wk->pos.z, *((f32 *)&ToZ + 1), *(f32 *)&ToZ);
    Dir_Hokan = sBtlGetDir_Hokan(RotToDir, v24, RotSpeed);
    if (sBtlGetLenXZ(wk->pos.x, wk->pos.z, v15->pos.x, v15->pos.z) >= 50.0)
    {
      v48 = *((f32 *)&ToZ + 1);
      v49 = v15->pos.x;
      v51 = *(f32 *)&ToZ - v15->pos.z;
      gGoalOfsX = v48 - v49;
      gGoalOfsZ = v51;
      v35 = Dir_Hokan;
    }
    else
    {
      if (!Suka180)
        return;
      v26 = wk->rot.x;
      y = wk->rot.y;
      v28 = wk->rot.z;
      w = wk->rot.w;
      v59.x = v26;
      v59.y = y;
      v59.z = v28;
      v59.w = w;
      v30 = sBtlGetRotToDir(v59);
      v31 = sBtlGet360(v30 + 180.0);
      v32 = sBtlGetDir_Hokan(v30, v31, RotSpeed);
      v35 = v32;
      gGoalOfsX = 0.0;
      gGoalOfsZ = 0.0;
    }
    Dir180 = sBtlGetDir180(v35);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    *p_rot = vct_A;
    goto LABEL_44;
  }
  if (!Suka180)
    return;
  v37 = wk->rot.x;
  v38 = wk->rot.y;
  v36 = &wk->rot;
  v39 = wk->rot.z;
  v40 = wk->rot.w;
  v60.x = v37;
  v60.y = v38;
  v60.z = v39;
  v60.w = v40;
  v41 = sBtlGetRotToDir(v60);
  v42 = sBtlGet360(v41 + 180.0);
  v43 = sBtlGetDir_Hokan(v41, v42, RotSpeed);
  gGoalOfsX = 0.0;
  gGoalOfsZ = 0.0;
  v46 = sBtlGetDir180(v43);
  wk->mv_rotbk = v46;
  FromEuler(0.0, v46 * 0.017453292, 0.0);
  *v36 = vct_A;
LABEL_44:
  p_rotbk = &wk->rotbk;
  *p_rotbk = vct_A;
}

// 0x20eef50
static bool SetPlayerDir2(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _SizeNml, f32 _RotSpeed) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 PosToDir;
  f32 AtoB_LR_ABS;
  bool v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v31;
  f32 Dir_Hokan;
  f32 Dir180;
  sdfVector4_t *p_rotbk;
  f32 rotspeed;
  sdfVector4_t v42;

  UnitMng = wk->UnitMng;
  targetID = wk->actaiwk->targetID;
  v10 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v10)
    return 0;
  v11 = v10;
  x = wk->rot.x;
  y = wk->rot.y;
  p_rot = &wk->rot;
  z = wk->rot.z;
  w = wk->rot.w;
  v42.x = x;
  v42.y = y;
  v42.z = z;
  v42.w = w;
  RotToDir = sBtlGetRotToDir(v42);
  v19 = RotToDir;
  v20 = wk->pos.x;
  v21 = wk->pos.z;
  v22 = v11->pos.x;
  PosToDir = sBtlGetPosToDir(v20, v21, v22 + gGoalOfsX, v11->pos.z + gGoalOfsZ);
  AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(v19, PosToDir);
  if (RotSpeed < 359.0 && AtoB_LR_ABS > 90.0)
    return 1;
  rotspeed = RotSpeed;
  v26 = wk->pos.x;
  v27 = wk->pos.z;
  v28 = v11->pos.x;
  v31 = v11->pos.z;
  if (sBtlGetLenXZ(v26, v27, v28 + gGoalOfsX, v31 + gGoalOfsZ) < 300.0)
    return 0;
  Dir_Hokan = sBtlGetDir_Hokan(v19, PosToDir, rotspeed);
  Dir180 = sBtlGetDir180(Dir_Hokan);
  wk->mv_rotbk = Dir180;
  FromEuler(0.0, Dir180 * 0.017453292, 0.0);
  *p_rot = vct_A;
  p_rotbk = &wk->rotbk;
  v25 = 0;
  *p_rotbk = vct_A;
  return v25;
}

// 0x20ef2e0
void sBtlPlayerGetCamSdDash(f32 _NewCamX, f32 _NewCamY, f32 _NewCamZ, f32 *_OutX, f32 *_OutY, f32 *_OutZ) {
  f32 LenXZ;
  f32 v20;
  f32 v21;
  f32 v22;
  s32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 *p_gStep;
  f32 v30;
  f32 GetZ;
  f32 GetX;

  goto LABEL_3;
LABEL_17:
  *OutX = NewCamX;
  *OutY = NewCamY;
  *OutZ = NewCamZ;
  return;
LABEL_3:
  if (wk->mode != 27)
    goto LABEL_17;
  GetX = NewCamX;
  GetZ = NewCamZ;
  LenXZ = sBtlGetLenXZ(gCamStartX, gCamStartZ, NewCamX, NewCamZ);
  v20 = 0.05;
  switch (gStep)
  {
    case 0:
    case 1:
    case 2:
    case 3:
      if (LenXZ <= 500.0)
        goto LABEL_25;
      v21 = gCamStartX;
      v22 = gCamStartZ;
      sBtlGetMovePosToPos(v21, v22, NewCamX, NewCamZ, 500.0, &GetX, &GetZ);
      *(f32 *)&v23 = 0.03;
      break;
    case 4:
    case 5:
    case 6:
      if (LenXZ <= 500.0)
      {
        *(f32 *)&v23 = 0.8;
      }
      else
      {
        v24 = gCamStartX;
        v25 = gCamStartZ;
        sBtlGetMovePosToPos(v24, v25, NewCamX, NewCamZ, 500.0, &GetX, &GetZ);
        *(f32 *)&v23 = 0.1;
      }
      break;
    case 7:
    case 8:
      if (LenXZ > 500.0)
        goto LABEL_28;
LABEL_25:
      *(f32 *)&v23 = 0.2;
      break;
    case 9:
    case 0xA:
    case 0xB:
      goto LABEL_35;
    default:
      if (LenXZ <= 500.0)
      {
        *(f32 *)&v23 = 0.7;
      }
      else
      {
LABEL_28:
        v26 = gCamStartX;
        v27 = gCamStartZ;
        sBtlGetMovePosToPos(v26, v27, NewCamX, NewCamZ, 500.0, &GetX, &GetZ);
        *(f32 *)&v23 = 0.05;
      }
      break;
  }
  v20 = *(f32 *)&v23;
LABEL_35:
  p_gStep = &gStep;
  *OutX = p_gStep[10] + (f32)(v20 * (f32)(GetX - p_gStep[10]));
  v30 = GetZ;
  *OutY = p_gStep[11] + (f32)(v20 * (f32)(NewCamY - p_gStep[11]));
  *OutZ = p_gStep[12] + (f32)(v20 * (f32)(v30 - p_gStep[12]));
  p_gStep[10] = *OutX;
  p_gStep[11] = *OutY;
  p_gStep[12] = *OutZ;
}

// 0x20ef670
s32 sBtlPlayerRSdDashProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v9;
  struct sBtlPlayer_SdDash *static_fields;
  s32 gStepCnt_local;
  bool v12;
  f32 v14;
  _BOOL4 v15;
  f32 TargetLen;
  f32 v18;
  f32 v21;
  f32 v22;
  s32 v23;
  f32 v25;
  f32 v26;
  f32 v27;
  _BOOL4 v28;
  f32 v30;
  f32 v33;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v39;
  s32 v40;
  f32 v42;
  f32 v48;
  u32 status;
  f32 v51;
  f32 v52;
  f32 v53;
  u32 v55;
  s32 motionID;
  f32 v58;
  f32 v59;
  s32 v64;
  f32 v65;
  u32 v68;
  u32 v70;
  f32 v74;
  _BOOL4 v79;
  _BOOL4 v80;
  s32 v81;
  SBTLCAMERA_WORK *camera;
  f32 x;
  f32 y;
  f32 z;
  s32 v87;
  s32 use_skillid;

  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  v9 = MotionFrameF;
  switch (gStep)
  {
    case 0:
      gStepCnt_local = gStepCnt + 1;
      v12 = gStepCnt - 1 < 0;
      gStepCnt = gStepCnt_local;
      if (v12 == __OFSUB__(gStepCnt_local, 2))
      {
        gStepCnt_local = gStepCnt;
        if (gStepCnt_local <= 14)
        {
          gStepCnt_local = gStepCnt;
          if ((u32)(-1431655765 * gStepCnt_local + 715827882) <= 0x55555554 && (wk->motionno != 175 || v9 == 0.0))
          {
            sBtlSetMotion(wk, 175, 0, 0, 0);
            goto LABEL_314;
          }
        }
      }
      if (wk->motionID == 175)
      {
        if (gStepCnt >= 11)
        {
          v64 = (s32)v9 - 21;
          if (v9 == INFINITY)
            v64 = 2147483627;
          switch (v64)
          {
            case 0:
              v65 = 7.0;
              break;
            case 1:
              v65 = 21.0;
              break;
            case 2:
              *(f32 *)&v87 = 35.0;
              goto LABEL_296;
            case 3:
              *(f32 *)&v87 = 42.0;
LABEL_296:
              v65 = *(f32 *)&v87;
              break;
            default:
              camera = wk->scene->camera;
              x = camera->camerapos.x;
              camera = wk->scene->camera;
              y = camera->camerapos.y;
              z = camera->camerapos.z;
              gCamStartZ = z;
              gCamPrevX = x;
              gCamStartX = x;
              gCamStartY = y;
              v65 = 0.0;
              gCamPrevY = y;
              gCamPrevZ = z;
              break;
          }
          gMoveSpeed = v65;
          if (v9 >= 21.0)
          {
            SetPlayerDir(wk, gDirOfs, 0.8, 10.0, 0);
          }
          if (v9 >= 24.0)
            goto LABEL_305;
          if (sBtlCheckMotionEnd_AnimatorNormal(wk))
          {
LABEL_305:
            sBtlPlayerRSkill_CoolTimeClr(wk, gClearIndex);
            wk->status |= 1u;
            gSklHit = 0;
            sBtlSetMotion(wk, 176, 0, 0, 0);
            Add(wk->ListID, 0);
            *(u64 *)&gStep = 1;
            wk->damage_ActerOfsY = 0.0;
            wk->actwk->use_skillid = gSklID;
            sBtlSetUseSkill(wk, gSklID, 0);
            sBtlSetAction(wk, 12, 0);
            wk->hstatus &= ~0x20000u;
            use_skillid = wk->actwk->use_skillid;
            sBtlSetSetsuma_SkillStart(wk, use_skillid);
            gMoveSpeed = 70.0;
          }
        }
      }
      goto LABEL_314;
    case 1:
      v14 = gStepTime + VRF_DeltaTime;
      gStepTime = v14;
      v15 = SetPlayerDir2(wk, v14, VRF_DeltaTime, 10.0);
      TargetLen = sBtlGetTargetLen(wk);
      if (v15)
      {
        v18 = gMoveSpeed - VRF;
LABEL_128:
        gMoveSpeed = v18;
        goto LABEL_129;
      }
      if (TargetLen > -1.0 && TargetLen < 800.0)
      {
        v18 = gMoveSpeed + (f32)(VRF * -0.0);
        goto LABEL_128;
      }
LABEL_129:
      if (gStepTime <= (f32)(FPS60 * 35.0))
      {
        if (gSklHit)
        {
          *(u64 *)&gStep = 2;
          goto LABEL_314;
        }
        if (v68)
        {
          v79 = 1;
        }
        else
        {
          v79 = !gSklHit;
        }
        if (TargetLen <= 400.0)
          v79 = 0;
        if (v15 && v79)
        {
          v81 = 2;
          goto LABEL_282;
        }
      }
      else
      {
LABEL_134:
        SetPlayerDir(wk, gDirOfs, 0.8, 360.0, 1);
        sBtlSetMotion(wk, 178, 0, 0, 0);
        gSklHit = 0;
        gMoveSpeed = 0.0;
        *(u64 *)&gStep = 3;
      }
      goto LABEL_314;
    case 2:
      v21 = gStepTime + VRF_DeltaTime;
      v22 = gMoveSpeed - VRF;
      gStepTime = v21;
      gMoveSpeed = v22;
      if (v21 <= (f32)(FPS60 * 12.0))
        goto LABEL_314;
      goto LABEL_134;
    case 3:
      gStepTime = gStepTime
                               + VRF_DeltaTime;
      SetPlayerDir(wk, gDirOfs, 0.8, 45.0, 0);
      v23 = v9;
      if (v9 == INFINITY)
        v23 = 0x80000000;
      switch (v23)
      {
        case 2:
          v25 = 7.0;
          break;
        case 3:
          v25 = 21.0;
          break;
        case 4:
          v25 = 35.0;
          break;
        case 5:
        case 6:
        case 7:
          v25 = 42.0;
          break;
        default:
          v25 = 0.0;
          break;
      }
      gMoveSpeed = v25;
      if (gStepTime > (f32)(FPS60 * 9.0))
      {
        sBtlSetMotion(wk, 176, 0, 0, 0);
        Add(wk->ListID, 0);
        gMoveSpeed = 70.0;
        gHit_BS_LASTBS = 0;
        *(u64 *)&gStep = 4;
      }
      goto LABEL_314;
    case 4:
      v26 = VRF_DeltaTime;
      v27 = gStepTime + v26;
      gStepTime = v27;
      v28 = SetPlayerDir2(wk, v27, v26, 10.0);
      v30 = sBtlGetTargetLen(wk);
      if (v28)
      {
        v33 = gMoveSpeed - VRF;
LABEL_149:
        gMoveSpeed = v33;
        goto LABEL_150;
      }
      if (v30 > -1.0 && v30 < 800.0)
      {
        v33 = gMoveSpeed + (f32)(VRF * -0.0);
        goto LABEL_149;
      }
LABEL_150:
      if (gStepTime <= (f32)(FPS60 * 35.0))
      {
        if (gSklHit)
        {
          *(u64 *)&gStep = 5;
        }
        else
        {
          if (v70)
          {
            v80 = 1;
          }
          else
          {
            v80 = !gSklHit;
          }
          if (v30 <= 400.0)
            v80 = 0;
          if (v28 && v80)
          {
            v81 = 5;
LABEL_282:
            gStep = v81;
            gStepTime = FPS60 * 3.0;
          }
        }
      }
      else
      {
        gDirOfs = 0.0;
        SetPlayerDir(wk, 0.0, 0.0, 360.0, 1);
        sBtlSetMotion(wk, 178, 0, 0, 0);
        wk->status &= ~1u;
LABEL_158:
        gMoveSpeed = 0.0;
        *(u64 *)&gStep = 6;
      }
      goto LABEL_314;
    case 5:
      v35 = FPS60;
      v36 = gStepTime + VRF_DeltaTime;
      v37 = gMoveSpeed - VRF;
      gStepTime = v36;
      gMoveSpeed = v37;
      if (v36 <= (f32)(v35 * 12.0))
        goto LABEL_314;
      gDirOfs = 0.0;
      SetPlayerDir(wk, 0.0, 0.0, 360.0, 1);
      sBtlSetMotion(wk, 178, 0, 0, 0);
      gSklHit = 0;
      goto LABEL_158;
    case 6:
      v39 = 0.0;
      gStepTime = gStepTime
                               + VRF_DeltaTime;
      SetPlayerDir(wk, gDirOfs, 0.0, 45.0, 0);
      v40 = v9;
      if (v9 == INFINITY)
        v40 = 0x80000000;
      switch (v40)
      {
        case 2:
          v39 = 7.0;
          break;
        case 3:
          v39 = 21.0;
          break;
        case 4:
          v39 = 35.0;
          break;
        case 5:
        case 6:
        case 7:
          v39 = 42.0;
          break;
        default:
          break;
      }
      gMoveSpeed = v39;
      v74 = sBtlGetTargetLen(wk);
      if (v74 > -1.0 && v74 < 400.0)
      {
        gMoveSpeed = 0.0;
        wk->status &= ~1u;
      }
      if (gStepTime > (f32)(FPS60 * 9.0))
      {
        sBtlSetMotion(wk, 176, 0, 0, 0);
        Add(wk->ListID, 0);
        gMoveSpeed = 70.0;
        if (v74 <= 50.0)
        {
          gMoveSpeed = 5.0;
        }
        gHit_BS_LASTBS = 0;
        *(u64 *)&gStep = 7;
      }
      goto LABEL_314;
    case 7:
      gStepTime = gStepTime
                               + VRF_DeltaTime;
      SetPlayerDir(wk, gDirOfs, 0.0, 10.0, 0);
      v42 = sBtlGetTargetLen(wk);
      if (v42 > -1.0 && v42 < 800.0)
      {
        gMoveSpeed = gMoveSpeed
                                       + (f32)(VRF * -0.0);
      }
      if (v42 > -1.0 && v42 < 200.0)
      {
        wk->status &= ~1u;
        *(u64 *)sBtlPlayer_SdDash->static_fields = 8;
        goto LABEL_314;
      }
      if (gStepTime > (f32)(FPS60 * 40.0))
      {
LABEL_70:
        status = wk->status;
        wk->flg &= ~0x40000u;
        wk->status = status & 0xFFFFFFFE;
LABEL_103:
        *(u64 *)&gStep = 9;
        goto LABEL_314;
      }
LABEL_100:
      if (gSklHit)
        goto LABEL_103;
      goto LABEL_314;
    case 8:
      gStepTime = gStepTime
                               + VRF_DeltaTime;
      SetPlayerDir(wk, gDirOfs, 0.0, 10.0, 0);
      v48 = FPS60 + FPS60;
      gMoveSpeed = gMoveSpeed - VRF;
      if (gStepTime > v48)
        goto LABEL_70;
      goto LABEL_100;
    case 9:
      v51 = FPS60;
      v52 = gStepTime + VRF_DeltaTime;
      v53 = gMoveSpeed - VRF;
      gStepTime = v52;
      gMoveSpeed = v53;
      if (v52 > (f32)(v51 + v51))
      {
        SetPlayerDir(wk, gDirOfs, 0.0, 360.0, 0);
        sBtlSetMotion(wk, 177, 0, 0, 0);
        v55 = wk->status & 0xFFFFFFFE;
        wk->flg &= ~0x40000u;
        wk->status = v55;
        gSklHit = 0;
        gMoveSpeed = 0.0;
        *(u64 *)&gStep = 10;
      }
      goto LABEL_314;
    case 0xA:
      motionID = wk->motionID;
      gMoveSpeed = 0.0;
      if (motionID == 177)
      {
        v58 = FPS60;
        v59 = gStepTime + VRF_DeltaTime;
        gStepTime = v59;
        if (v59 > (f32)(v58 * 120.0))
          goto LABEL_88;
        if (sBtlCheckMotionEnd_AnimatorNormal(wk) || !wk->motionID)
          goto LABEL_88;
        goto LABEL_167;
      }
      if (!motionID)
      {
LABEL_88:
        sBtlClrSuperArmor2(wk);
        sBtlResetAction(wk);
        sBtlSetUseSkill(wk, 0, 0);
        *(u64 *)sBtlPlayer_SdDash->static_fields = 11;
        return 2;
      }
LABEL_167:
      if (gStepTime >= FPS60)
      {
        sBtlClrSuperArmor2(wk);
      }
      if (gStepTime >= FPS60)
      {
        if (sBtlPlayerRSkillCancel_Setsuma(wk))
          return 2;
      }
      if (gStepTime >= FPS60)
      {
        if (sBtlPlayerRSkillCancel_RSptrit(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 40.0))
      {
        if (sBtlPlayerRSkillCancel_Skill(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 40.0))
      {
        if (sBtlPlayerRSkillCancel_Guard(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 40.0))
      {
        if (sBtlPlayerRSkillCancel_Jump(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 40.0))
      {
        if (sBtlPlayerRSkillCancel_Kaihi(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 40.0))
      {
        if (sBtlPlayerRSkillCancel_Gun(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 60.0) && (sBtlPlayerRSkillCancel_Move(wk) || sBtlPlayerRSkillCancel_Huuma(wk)))
      {
        return 2;
      }
LABEL_314:
      if (gSklUse)
        return 2;
      gSklUse = 1;
      return 2;
    default:
      goto LABEL_314;
  }
}
