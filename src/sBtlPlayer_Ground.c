#include "types.h"
#include "SKLID.h"
#include "aw_rsground.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_ground.h"
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
static bool gSklHitUse;
static bool gSklEffUse;
static s32 gStepCnt;
static s32 gClearIndex;

// 0x20e6b50
s32 sBtlPlayerRGroundInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;
  SBTLUNIT_WORK *v15;
  f32 x;
  f32 z;
  f32 v18;
  f32 v19;
  f32 PosToDir;
  f32 Dir180;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rotbk;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 26;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  wk->motion_EndNoCng = 1;
  sBtlSetMotion(wk, 172, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u16 *)&gSklUse = 0;
  gSklEffUse = 0;
  gStepCnt = 0;
  gClearIndex = ClearIndex;
  v15 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
  if (v15)
  {
    x = v15->pos.x;
    z = v15->pos.z;
    v18 = wk->pos.x;
    v19 = wk->pos.z;
    PosToDir = sBtlGetPosToDir(v18, v19, x, z);
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

// 0x20e7cc0
s32 sBtlPlayerRGroundProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  SBTLUNIT_WORK *v5;
  f32 MotionFrameF;
  struct sBtlPlayer_Ground *static_fields;
  f32 v12;
  s32 use_skillid;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_LISTWORK *v21;
  s32 v22;
  SBTLUNIT_WORK *v23;
  f32 x;
  f32 y;
  f32 *v26;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v34;
  s32 v35;
  f32 v36;
  s64 v39;
  f32 v41;
  f32 v42;
  f32 v46;
  f32 v47;
  sdfVector4_t v48;
  sdfVector4_t v49;

  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  if (gStep == 2)
  {
    gStepTime = gStepTime + VRF_DeltaTime;
    if (wk->motionID != 174 || MotionFrameF >= 30.5)
      goto LABEL_97;
    if (sBtlCheckMotionEnd(wk))
    {
LABEL_97:
      sBtlClrSuperArmor2(wk);
      sBtlResetAction(wk);
      sBtlSetUseSkill(wk, 0, 0);
      v39 = 3;
      goto LABEL_61;
    }
    v46 = FPS60 + FPS60;
    if (gStepTime >= (f32)(FPS60 + FPS60))
    {
      sBtlClrSuperArmor2(wk);
      v46 = FPS60 + FPS60;
    }
    if (gStepTime >= v46)
    {
      if (sBtlPlayerRSkillCancel_Setsuma(wk))
        return 2;
      v46 = FPS60 + FPS60;
    }
    if (gStepTime >= v46)
    {
      if (sBtlPlayerRSkillCancel_RSptrit(wk))
        return 2;
    }
    v47 = FPS60 * 10.0;
    if (gStepTime >= (f32)(FPS60 * 10.0))
    {
      if (sBtlPlayerRSkillCancel_Skill(wk))
        return 2;
      v47 = FPS60 * 10.0;
    }
    if (gStepTime >= v47)
    {
      if (sBtlPlayerRSkillCancel_Guard(wk))
        return 2;
      v47 = FPS60 * 10.0;
    }
    if (gStepTime >= v47)
    {
      if (sBtlPlayerRSkillCancel_Jump(wk))
        return 2;
      v47 = FPS60 * 10.0;
    }
    if (gStepTime >= v47)
    {
      if (sBtlPlayerRSkillCancel_Kaihi(wk))
        return 2;
      v47 = FPS60 * 10.0;
    }
    if (gStepTime >= v47)
    {
      if (sBtlPlayerRSkillCancel_Gun(wk))
        return 2;
    }
    if (gStepTime >= (f32)(FPS60 * 30.0))
      sBtlPlayerRSkillCancel_Move(wk);
    return 2;
  }
  if (gStep == 1)
  {
    v41 = gStepTime + VRF_DeltaTime;
    v42 = FPS60 * 30.0;
    gStepTime = v41;
    if (v41 <= v42)
      return 2;
    sBtlSetMotion(wk, 174, 0, 0, 0);
    v39 = 2;
LABEL_61:
    *(u64 *)sBtlPlayer_Ground->static_fields = v39;
    return 2;
  }
  if (gStep)
    return 2;
  v12 = gStepTime + VRF_DeltaTime;
  gStepTime = v12;
  if (!gSklUse)
  {
    gSklUse = 1;
    sBtlPlayerRSkill_CoolTimeClr(v5, gClearIndex);
    wk->damage_ActerOfsY = 0.0;
    wk->actwk->use_skillid = gSklID;
    sBtlSetUseSkill(wk, gSklID, 0);
    wk->hstatus &= ~0x20000u;
    use_skillid = wk->actwk->use_skillid;
    sBtlSetSetsuma_SkillStart(wk, use_skillid);
    v12 = gStepTime;
  }
  if (v12 > (f32)(FPS60 * 52.0) && !gSklEffUse)
  {
    gSklEffUse = 1;
    UnitMng = wk->UnitMng;
    targetID = wk->actaiwk->targetID;
    if (sBtlSearchUnit_ID(UnitMng, targetID))
    {
LABEL_21:
      v21 = wk->UnitMng;
      v22 = wk->actaiwk->targetID;
      v23 = sBtlSearchUnit_ID(v21, v22);
      if (v23)
      {
        x = v23->rot.x;
        y = v23->rot.y;
        v26 = v23;
        z = v23->rot.z;
        w = v23->rot.w;
        v48.x = x;
        v48.y = y;
        v48.z = z;
        v48.w = w;
        RotToDir = sBtlGetRotToDir(v48);
        Add(v26[41], v26[42], v26[43], RotToDir, 0);
        v30 = v26[41];
        v31 = v26[42];
        v32 = v26[43];
        v49.w = 0.0;
        v49.x = v30;
        v49.y = v31;
        v49.z = v32;
        sBtlPlay3DSE(0x7400004u, v49);
      }
      goto LABEL_29;
    }
    sBtlSetNextTarget_RS(wk);
    goto LABEL_21;
  }
LABEL_29:
  v34 = gStepTime;
  v35 = gStepCnt + 1;
  v36 = FPS60 + FPS60;
  gStepCnt = v35;
  if (v34 > v36 && (wk->motionno != 172 || MotionFrameF == 0.0 && !(v35 % 3)))
  {
    sBtlSetMotion(wk, 172, 0, 0, 0);
    return 2;
  }
  if (wk->motionID == 172 && gSklEffUse)
  {
    if (MotionFrameF >= 29.5)
      goto LABEL_58;
    if (sBtlCheckMotionEnd(wk))
    {
LABEL_58:
      wk->motion_EndNoCng = 0;
      sBtlSetMotion(wk, 173, 0, 0, 0);
      v39 = 1;
      goto LABEL_61;
    }
  }
  return 2;
}
