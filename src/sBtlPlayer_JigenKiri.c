#include "types.h"
#include "SKLID.h"
#include "aw_rsjigenkiri.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_jigenkiri.h"
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
static bool gEffUse;
f32 gDistLen;
static s32 gClearIndex;

// 0x20e6810
s32 sBtlPlayerRJigenKiriInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;
  SBTLUNIT_WORK *v13;
  f32 x;
  f32 z;
  f32 v16;
  f32 v17;
  f32 PosToDir;
  f32 Dir180;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rotbk;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 25;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 171, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u16 *)&gSklUse = 0;
  gDistLen = 800.0;
  gClearIndex = ClearIndex;
  v13 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
  if (v13)
  {
    x = v13->pos.x;
    z = v13->pos.z;
    v16 = wk->pos.x;
    v17 = wk->pos.z;
    PosToDir = sBtlGetPosToDir(v16, v17, x, z);
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

// 0x20e90a0
f32 sBtlPlayerGetJigenKiriDist(void) {
  return gDistLen;
}

// 0x20e90f0
s32 sBtlPlayerRJigenKiriProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  SBTLUNIT_WORK *v5;
  f32 v9;
  f32 v10;
  s32 use_skillid;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_LISTWORK *v19;
  s32 v20;
  SBTLUNIT_WORK *v21;
  f32 x;
  SBTLUNIT_WORK *v23;
  f32 z;
  f32 v25;
  f32 v26;
  f32 LenXZ;
  s32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 PosToDir;
  s64 v35;
  f32 y;
  s64 v38;
  f32 v44;
  f32 v45;
  s64 GetZ;
  sdfVector4_t v47;

  GetZ = 0;
  hModel = wk->hModel;
  mdlGetMotionFrameF(hModel);
  if (gStep == 1)
  {
    gStepTime = gStepTime + VRF_DeltaTime;
    if (!sBtlCheckMotionEnd(wk))
    {
      if (gStepTime <= (f32)(FPS60 * 150.0))
      {
        v44 = FPS60 * 45.0;
        if (gStepTime >= (f32)(FPS60 * 45.0))
        {
          sBtlClrSuperArmor2(wk);
          v44 = FPS60 * 45.0;
        }
        if (gStepTime >= v44)
        {
          if (sBtlPlayerRSkillCancel_Setsuma(wk))
            return 2;
          v44 = FPS60 * 45.0;
        }
        if (gStepTime >= v44)
        {
          if (sBtlPlayerRSkillCancel_RSptrit(wk))
            return 2;
        }
        v45 = FPS60 * 50.0;
        if (gStepTime >= (f32)(FPS60 * 50.0))
        {
          if (sBtlPlayerRSkillCancel_Skill(wk))
            return 2;
          v45 = FPS60 * 50.0;
        }
        if (gStepTime >= v45)
        {
          if (sBtlPlayerRSkillCancel_Guard(wk))
            return 2;
          v45 = FPS60 * 50.0;
        }
        if (gStepTime >= v45)
        {
          if (sBtlPlayerRSkillCancel_Jump(wk))
            return 2;
          v45 = FPS60 * 50.0;
        }
        if (gStepTime >= v45)
        {
          if (sBtlPlayerRSkillCancel_Kaihi(wk))
            return 2;
          v45 = FPS60 * 50.0;
        }
        if (gStepTime >= v45)
        {
          if (sBtlPlayerRSkillCancel_Gun(wk))
            return 2;
        }
        if (gStepTime >= (f32)(FPS60 * 80.0))
          sBtlPlayerRSkillCancel_Move(wk);
        return 2;
      }
    }
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    sBtlClrSuperArmor2(wk);
    v38 = 2;
    goto LABEL_48;
  }
  if (gStep)
    return 2;
  v9 = FPS60;
  v10 = gStepTime + VRF_DeltaTime;
  gStepTime = v10;
  if (v10 > (f32)(v9 * 4.0) && !gSklUse)
  {
    gSklUse = 1;
    sBtlPlayerRSkill_CoolTimeClr(v5, gClearIndex);
    wk->damage_ActerOfsY = 0.0;
    wk->actwk->use_skillid = gSklID;
    sBtlSetUseSkill(wk, gSklID, 0);
    wk->hstatus &= ~0x20000u;
    use_skillid = wk->actwk->use_skillid;
    sBtlSetSetsuma_SkillStart(wk, use_skillid);
    v10 = gStepTime;
    v9 = FPS60;
  }
  if (!(v10 <= (f32)(v9 * 64.0) || gEffUse))
  {
    gEffUse = 1;
    UnitMng = wk->UnitMng;
    targetID = wk->actaiwk->targetID;
    if (!sBtlSearchUnit_ID(UnitMng, targetID))
      sBtlSetNextTarget_RS(wk);
    v19 = wk->UnitMng;
    v20 = wk->actaiwk->targetID;
    v21 = sBtlSearchUnit_ID(v19, v20);
    if (v21)
    {
      x = wk->pos.x;
      v23 = v21;
      z = wk->pos.z;
      v25 = v21->pos.x;
      v26 = v21->pos.z;
      LenXZ = sBtlGetLenXZ(x, z, v25, v26);
      gDistLen = LenXZ;
      *(f32 *)&v29 = 800.0;
      if (LenXZ > 800.0 || (*(f32 *)&v29 = 600.0, LenXZ < 600.0))
      {
        LenXZ = *(f32 *)&v29;
        gDistLen = *(f32 *)&v29;
      }
      v30 = wk->pos.x;
      v31 = wk->pos.z;
      v32 = v23->pos.x;
      v33 = v23->pos.z;
      sBtlGetMovePosToPos(v30, v31, v32, v33, LenXZ, (f32 *)&GetZ + 1, &GetZ);
      PosToDir = sBtlGetPosToDir(wk->pos.x, wk->pos.z, v23->pos.x, v23->pos.z);
      Add(*((f32 *)&GetZ + 1), wk->pos.y, *(f32 *)&GetZ, PosToDir, 0);
      v35 = GetZ;
      y = wk->pos.y;
      v47.w = 0.0;
      v47.x = *((f32 *)&v35 + 1);
      v47.y = y;
      LODWORD(v47.z) = v35;
      sBtlPlay3DSE(0x79D0004u, v47);
    }
  }
  if (gStepTime > (f32)(FPS60 * 64.0))
  {
    v38 = 1;
LABEL_48:
    *(u64 *)&gStep = v38;
  }
  return 2;
}
