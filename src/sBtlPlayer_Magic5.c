#include "types.h"
#include "SKLID.h"
#include "aw_mag.h"
#include "aw_rsmagget.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_magic5.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static s32 gStep;
static f32 gStepTime;
static SKLID gSklID;
static bool gSklUse;
static bool gSklEffUse;
static s32 gClearIndex;

// 0x20eca70
s32 sBtlPlayerRMagic5Init(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 32;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 182, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  gSklID = SklID;
  gClearIndex = ClearIndex;
  *(u64 *)&gStep = 0;
  *(u16 *)&gSklUse = 0;
  return 2;
}

// 0x20ecc20
s32 sBtlPlayerRMagic5Proc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 v7;
  f32 v8;
  s32 use_skillid;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  s64 v20;
  s32 v21;
  f32 RotToDir;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v31;
  s64 v32;
  f32 v37;
  f32 v38;
  s64 ToZ;
  sdfVector4_t v40;
  sdfVector4_t v41;
  sdfVector4_t v42;

  ToZ = 0;
  hModel = wk->hModel;
  mdlGetMotionFrameF(hModel);
  if (gStep == 1)
  {
    gStepTime = gStepTime + VRF_DeltaTime;
    if (!sBtlCheckMotionEnd(wk))
    {
      if (gStepTime <= (f32)(FPS60 * 120.0))
      {
        v37 = FPS60 + FPS60;
        if (gStepTime >= (f32)(FPS60 + FPS60))
        {
          sBtlClrSuperArmor2(wk);
          v37 = FPS60 + FPS60;
        }
        if (gStepTime >= v37)
        {
          if (sBtlPlayerRSkillCancel_Setsuma(wk))
            return 2;
          v37 = FPS60 + FPS60;
        }
        if (gStepTime >= v37)
        {
          if (sBtlPlayerRSkillCancel_RSptrit(wk))
            return 2;
        }
        if (gStepTime >= (f32)(FPS60 * 8.0))
        {
          if (sBtlPlayerRSkillCancel_Skill(wk))
            return 2;
        }
        v38 = FPS60 + FPS60;
        if (gStepTime >= (f32)(FPS60 + FPS60))
        {
          if (sBtlPlayerRSkillCancel_Guard(wk))
            return 2;
          v38 = FPS60 + FPS60;
        }
        if (gStepTime >= v38)
        {
          if (sBtlPlayerRSkillCancel_Jump(wk))
            return 2;
          v38 = FPS60 + FPS60;
        }
        if (gStepTime >= v38)
        {
          if (sBtlPlayerRSkillCancel_Kaihi(wk))
            return 2;
        }
        if (gStepTime >= (f32)(FPS60 * 8.0))
        {
          if (sBtlPlayerRSkillCancel_Gun(wk))
            return 2;
        }
        if (gStepTime >= (f32)(FPS60 * 16.0))
          sBtlPlayerRSkillCancel_Move(wk);
        return 2;
      }
    }
    sBtlClrSuperArmor2(wk);
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    v32 = 2;
    goto LABEL_43;
  }
  if (!gStep)
  {
    v7 = FPS60;
    v8 = gStepTime + VRF_DeltaTime;
    gStepTime = v8;
    if (v8 > (f32)(v7 * 30.0) && !gSklUse)
    {
      wk->damage_ActerOfsY = 0.0;
      gSklUse = 1;
      wk->actwk->use_skillid = gSklID;
      sBtlSetUseSkill(wk, gSklID, 0);
      wk->hstatus &= ~0x20000u;
      use_skillid = wk->actwk->use_skillid;
      sBtlSetSetsuma_SkillStart(wk, use_skillid);
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v40.x = x;
      v40.y = y;
      v40.z = z;
      v40.w = w;
      sBtlPlay3DSE(0x8380003u, v40);
      v17 = wk->rot.x;
      v16 = wk->rot.y;
      v19 = wk->rot.z;
      v18 = wk->rot.w;
      v20 = 68719476750LL * wk->magMax;
      v21 = (v20 >> 37) + ((u64)v20 >> 63);
      v41.x = v17;
      v41.y = v16;
      v41.z = v19;
      v41.w = v18;
      RotToDir = sBtlGetRotToDir(v41);
      sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir, 20.0, (f32 *)&ToZ + 1, &ToZ);
      Add(2, *((f32 *)&ToZ + 1), wk->pos.y + -150.0, *(f32 *)&ToZ, v21, 0);
      Add(2, *((f32 *)&ToZ + 1), wk->pos.y + -165.0, *(f32 *)&ToZ, -1, 0);
      Add(2, *((f32 *)&ToZ + 1), wk->pos.y + -180.0, *(f32 *)&ToZ, -1, 0);
      Add(2, *((f32 *)&ToZ + 1), wk->pos.y + -195.0, *(f32 *)&ToZ, -1, 0);
      Add(2, *((f32 *)&ToZ + 1), wk->pos.y + -210.0, *(f32 *)&ToZ, -1, 0);
      v8 = gStepTime;
      v7 = FPS60;
    }
    if (v8 > (f32)(v7 * 0.0) && !gSklEffUse)
    {
      gSklEffUse = 1;
      sBtlPlayerRSkill_CoolTimeClr(wk, gClearIndex);
      v24 = wk->rot.x;
      v25 = wk->rot.y;
      v27 = wk->rot.z;
      v26 = wk->rot.w;
      v42.x = v24;
      v42.y = v25;
      v42.z = v27;
      v42.w = v26;
      v28 = sBtlGetRotToDir(v42);
      Add(wk->ListID, gSklID, wk->pos.x, wk->pos.y, wk->pos.z, v28, 0);
      sysmsgList = wk->sysmsgList;
      v31 = gSklID;
      sBtlCreateSM(sysmsgList, wk, 10, v31, 0, 120);
      v8 = gStepTime;
      v7 = FPS60;
    }
    if (v8 > (f32)(v7 * 60.0))
    {
      v32 = 1;
LABEL_43:
      *(u64 *)&gStep = v32;
    }
  }
  return 2;
}
