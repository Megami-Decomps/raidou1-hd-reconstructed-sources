#include "types.h"
#include "SKLID.h"
#include "aw_rsmegidraon.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_magic2.h"
#include "sbtlsm.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static s32 gStep;
static f32 gStepTime;
static SKLID gSklID;
static bool gSklUse;
static bool gSklBulletUse;
static bool gSklHitUse;
static s32 gClearIndex;

// 0x20ea7d0
s32 sBtlPlayerRMagic2Init(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;
  SBTLUNIT_WORK *v14;
  f32 x;
  f32 z;
  f32 v17;
  f32 v18;
  f32 PosToDir;
  f32 Dir180;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rotbk;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 29;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 179, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u16 *)&gSklUse = 0;
  gSklHitUse = 0;
  gClearIndex = ClearIndex;
  v14 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
  if (v14)
  {
    x = v14->pos.x;
    z = v14->pos.z;
    v17 = wk->pos.x;
    v18 = wk->pos.z;
    PosToDir = sBtlGetPosToDir(v17, v18, x, z);
    Dir180 = sBtlGetDir180(PosToDir);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    p_rot = &wk->rot;
    *p_rot = vct_A;
    p_rotbk = &wk->rotbk;
    *p_rotbk = vct_A;
  }
  return 2;
}

// 0x20eab20
s32 sBtlPlayerRMagic2Proc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 v7;
  f32 v8;
  s32 use_skillid;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v15;
  s32 ListID;
  s32 v17;
  s64 v18;
  f32 v23;
  f32 v24;

  hModel = wk->hModel;
  mdlGetMotionFrameF(hModel);
  if (gStep == 1)
  {
    gStepTime = gStepTime + VRF_DeltaTime;
    if (!sBtlCheckMotionEnd(wk))
    {
      if (gStepTime <= (f32)(FPS60 * 45.0))
      {
        v23 = FPS60 + FPS60;
        if (gStepTime >= (f32)(FPS60 + FPS60))
        {
          sBtlClrSuperArmor2(wk);
          v23 = FPS60 + FPS60;
        }
        if (gStepTime >= v23)
        {
          if (sBtlPlayerRSkillCancel_Setsuma(wk))
            return 2;
          v23 = FPS60 + FPS60;
        }
        if (gStepTime >= v23)
        {
          if (sBtlPlayerRSkillCancel_RSptrit(wk))
            return 2;
        }
        if (gStepTime >= (f32)(FPS60 * 8.0))
        {
          if (sBtlPlayerRSkillCancel_Skill(wk))
            return 2;
        }
        v24 = FPS60 + FPS60;
        if (gStepTime >= (f32)(FPS60 + FPS60))
        {
          if (sBtlPlayerRSkillCancel_Guard(wk))
            return 2;
          v24 = FPS60 + FPS60;
        }
        if (gStepTime >= v24)
        {
          if (sBtlPlayerRSkillCancel_Jump(wk))
            return 2;
          v24 = FPS60 + FPS60;
        }
        if (gStepTime >= v24)
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
    v18 = 2;
    goto LABEL_35;
  }
  if (!gStep)
  {
    v7 = FPS60;
    v8 = gStepTime + VRF_DeltaTime;
    gStepTime = v8;
    if (v8 > v7 && !gSklUse)
    {
      gSklUse = 1;
      sBtlPlayerRSkill_CoolTimeClr(wk, gClearIndex);
      wk->damage_ActerOfsY = 0.0;
      wk->actwk->use_skillid = gSklID;
      sBtlSetUseSkill(wk, gSklID, 0);
      wk->hstatus &= ~0x20000u;
      use_skillid = wk->actwk->use_skillid;
      sBtlSetSetsuma_SkillStart(wk, use_skillid);
      sysmsgList = wk->sysmsgList;
      v15 = gSklID;
      sBtlCreateSM(sysmsgList, wk, 10, v15, 0, 120);
      v8 = gStepTime;
      v7 = FPS60;
    }
    if (v8 > v7 && !gSklBulletUse)
    {
      ListID = wk->ListID;
      v17 = gSklID;
      gSklBulletUse = 1;
      Add(ListID, v17, 0);
      v8 = gStepTime;
      v7 = FPS60;
    }
    if (v8 > (f32)(v7 * 60.0))
    {
      v18 = 1;
LABEL_35:
      *(u64 *)&gStep = v18;
    }
  }
  return 2;
}
