#include "types.h"
#include "SKLID.h"
#include "aw_rsgekizan.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_kaiten.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static s32 gStep;
static f32 gStepTime;
static SKLID gSklID;
static bool gSklUse;
static bool gEffDone;
static s32 gClearIndex;

// 0x20e5bd0
s32 sBtlPlayerRKaitenInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
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
  SBTLSM_LISTWORK *sysmsgList;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 21;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 52, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u16 *)&gSklUse = 0;
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
  sysmsgList = wk->sysmsgList;
  sBtlCreateSM(sysmsgList, wk, 10, gSklID, 0, 60);
  return 2;
}

// 0x20e9890
s32 sBtlPlayerRKaitenProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  SBTLUNIT_WORK *v5;
  struct sBtlPlayer_Kaiten *static_fields;
  f32 v9;
  f32 v10;
  s32 use_skillid;
  f32 v16;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 v25;
  f32 v26;
  sdfVector4_t v28;

  hModel = wk->hModel;
  mdlGetMotionFrameF(hModel);
  if (gStep != 1)
  {
    if (!gStep)
    {
      v9 = gStepTime + VRF_DeltaTime;
      v10 = FPS60 * 0.0;
      gStepTime = v9;
      if (v9 > v10)
      {
        *(u64 *)&gStep = 1;
        if (!gSklUse)
        {
          gSklUse = 1;
          wk->damage_ActerOfsY = 0.0;
          wk->actwk->use_skillid = gSklID;
          sBtlSetUseSkill(wk, gSklID, 0);
          sBtlSetAction(wk, 12, 0);
          wk->hstatus &= ~0x20000u;
          use_skillid = wk->actwk->use_skillid;
          sBtlSetSetsuma_SkillStart(wk, use_skillid);
        }
      }
    }
    return 2;
  }
  v16 = gStepTime + VRF_DeltaTime;
  gStepTime = v16;
  if (!gEffDone && v16 >= (f32)(FPS60 + FPS60))
  {
    sBtlPlayerRSkill_CoolTimeClr(v5, gClearIndex);
    Add(wk->ListID, 0);
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    v28.x = x;
    v28.y = y;
    v28.z = z;
    v28.w = w;
    sBtlPlay3DSE(0x79E0004u, v28);
    gEffDone = 1;
  }
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_24;
  goto LABEL_9000;
  if (sBtlCheckMotionEnd(wk))
  {
LABEL_24:
    sBtlClrSuperArmor2(wk);
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    *(u64 *)sBtlPlayer_Kaiten->static_fields = 2;
    return 2;
  }
LABEL_9000:
  if (gStepTime > (f32)(FPS60 * 120.0))
    goto LABEL_24;
  v25 = FPS60 * 40.0;
  if (gStepTime >= (f32)(FPS60 * 40.0))
  {
    sBtlClrSuperArmor2(wk);
    v25 = FPS60 * 40.0;
  }
  if (gStepTime >= v25)
  {
    if (sBtlPlayerRSkillCancel_Setsuma(wk))
      return 2;
    v25 = FPS60 * 40.0;
  }
  if (gStepTime >= v25)
  {
    if (sBtlPlayerRSkillCancel_RSptrit(wk))
      return 2;
  }
  v26 = FPS60 * 52.0;
  if (gStepTime >= (f32)(FPS60 * 52.0))
  {
    if (sBtlPlayerRSkillCancel_Skill(wk))
      return 2;
    v26 = FPS60 * 52.0;
  }
  if (gStepTime >= v26)
  {
    if (sBtlPlayerRSkillCancel_Guard(wk))
      return 2;
    v26 = FPS60 * 52.0;
  }
  if (gStepTime >= v26)
  {
    if (sBtlPlayerRSkillCancel_Jump(wk))
      return 2;
    v26 = FPS60 * 52.0;
  }
  if (gStepTime >= v26)
  {
    if (sBtlPlayerRSkillCancel_Kaihi(wk))
      return 2;
    v26 = FPS60 * 52.0;
  }
  if (gStepTime >= v26)
  {
    if (sBtlPlayerRSkillCancel_Gun(wk))
      return 2;
  }
  if (gStepTime >= (f32)(FPS60 * 80.0) && !sBtlPlayerRSkillCancel_Move(wk))
    sBtlPlayerRSkillCancel_Huuma(wk);
  return 2;
}
