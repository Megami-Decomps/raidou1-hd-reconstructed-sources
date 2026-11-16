#include "types.h"
#include "SKLID.h"
#include "aw_hits.h"
#include "aw_rsbullet.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_magic.h"
#include "sbtlplayerex.h"
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
static bool gSklBulletUse;
static bool gSklHitUse;
static bool gEffHitDone;
static s32 gTargetID;
static f32 gTargetX;
static f32 gTargetY;
static f32 gTargetZ;
static s32 gClearIndex;
static s32 gRetryCnt;

// 0x20e6370
s32 sBtlPlayerRMagicInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;
  s32 targetID;
  SBTLUNIT_WORK *v15;
  f32 x;
  f32 z;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 PosToDir;
  f32 Dir180;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rotbk;
  s64 v31;
  s64 v32;
  u32 v33;
  s64 v36;
  s64 v37;
  sdfVector4_t v38;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 24;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 170, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u32 *)&gSklUse = 0;
  gClearIndex = ClearIndex;
  gRetryCnt = 0;
  targetID = wk->actaiwk->targetID;
  gTargetID = targetID;
  v15 = sBtlSearchUnit_ID(wk->UnitMng, targetID);
  if (v15)
  {
    x = wk->pos.x;
    z = wk->pos.z;
    if (v15->para->devilid == 314)
    {
      v18 = z;
      v19 = x;
      v20 = z + 500.0;
      v21 = x;
    }
    else
    {
      v22 = v15->pos.x;
      v23 = v15->pos.z;
      v21 = x;
      v18 = z;
      v19 = v22;
      v20 = v23;
    }
    PosToDir = sBtlGetPosToDir(v21, v18, v19, v20);
    Dir180 = sBtlGetDir180(PosToDir);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    p_rot = &wk->rot;
    *p_rot = vct_A;
    p_rotbk = &wk->rotbk;
    *p_rotbk = vct_A;
  }
  if (gSklID <= 23)
  {
    if (gSklID == 8)
    {
      v31 = *(u64 *)&wk->pos.x;
      v33 = 117964803;
      v32 = *(u64 *)&wk->pos.z;
      goto LABEL_35;
    }
    else
    {
      if (gSklID != 23)
        return 2;
      v31 = *(u64 *)&wk->pos.x;
      v32 = *(u64 *)&wk->pos.z;
      v33 = 118947843;
      goto LABEL_35;
    }
    goto LABEL_34;
  }
  if (gSklID == 39)
  {
    v31 = *(u64 *)&wk->pos.x;
    v32 = *(u64 *)&wk->pos.z;
    v33 = 119996419;
    goto LABEL_35;
  }
  if (gSklID == 55)
  {
    v31 = *(u64 *)&wk->pos.x;
    v32 = *(u64 *)&wk->pos.z;
    v33 = 121044995;
LABEL_35:
    *(u64 *)&v38.x = v31;
    *(u64 *)&v38.z = v32;
    sBtlPlay3DSE(v33, v38);
    return 2;
LABEL_34:
    v36 = v32;
    v37 = v31;
    v32 = v36;
    v31 = v37;
    goto LABEL_35;
  }
  return 2;
}

// 0x20e9e00
void CallHitDone(void) {
  gEffHitDone = 1;
}

// 0x20e9e50
s32 sBtlPlayerRMagicProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  SBTLUNIT_WORK *v5;
  f32 MotionFrameF;
  struct sBtlPlayer_Magic *static_fields;
  f32 v9;
  f32 gStepTime_local;
  s32 use_skillid;
  s32 v17;
  bool v19;
  SBATTLE_WORK *v22;
  SBTLUNIT_LISTWORK *v23;
  s32 v24;
  SBTLUNIT_LISTWORK *v26;
  s32 v27;
  SBTLUNIT_WORK *v28;
  f32 v29;
  f32 y;
  SBTLUNIT_WORK *v31;
  f32 w;
  f32 v33;
  f32 RotToDir;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v39;
  s32 v43;
  SBTLUNIT_LISTWORK *v44;
  SBTLUNIT_WORK *v45;
  f32 x;
  SBTLUNIT_WORK *v47;
  f32 z;
  f32 v49;
  f32 v50;
  f32 PosToDir;
  SBTLUNIT_WORK *v52;
  s32 v54;
  f32 v59;
  f32 v60;
  f32 v63;
  f32 v64;
  f32 v66;
  f32 v67;
  sdfVector4_t v68;

  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  if (gStep != 1)
  {
    if (gStep)
      return 2;
    v9 = MotionFrameF;
    gStepTime_local = gStepTime + VRF_DeltaTime;
    gStepTime = gStepTime_local;
    if (gStepTime_local > FPS60 && !gSklUse)
    {
      gSklUse = 1;
      sBtlPlayerRSkill_CoolTimeClr(v5, gClearIndex);
      wk->damage_ActerOfsY = 0.0;
      wk->actwk->use_skillid = gSklID;
      sBtlSetUseSkill(wk, gSklID, 0);
      wk->hstatus &= ~0x20000u;
      use_skillid = wk->actwk->use_skillid;
      sBtlSetSetsuma_SkillStart(wk, use_skillid);
      gStepTime_local = gStepTime;
    }
    v17 = gRetryCnt + 1;
    gRetryCnt = v17;
    v19 = gStepTime_local > (f32)(FPS60 + FPS60) && v17 % 3 == 0 && v17 <= 19;
    if (v19 && (wk->motionno != 170 || v9 == 0.0))
    {
      sBtlSetMotion(wk, 170, 0, 0, 0);
    }
    if (gStepTime <= (f32)(FPS60 * 38.0) || gSklBulletUse)
    {
LABEL_40:
      UnitMng = wk->UnitMng;
      v39 = sBtlSearchUnit_ID(UnitMng, gTargetID);
      if (v39)
      {
        *(u64 *)&gTargetX = *(u64 *)&v39->pos.x;
        gTargetZ = v39->pos.z;
        if (gEffHitDone)
          goto LABEL_45;
        goto LABEL_69;
      }
      if (gEffHitDone)
      {
LABEL_45:
        if (!gSklHitUse)
        {
          gSklHitUse = 1;
          v43 = gTargetID;
          v44 = wk->UnitMng;
          v45 = sBtlSearchUnit_ID(v44, v43);
          if (v45)
          {
            x = v45->pos.x;
            v47 = v45;
            z = v45->pos.z;
            v49 = wk->pos.x;
            v50 = wk->pos.z;
            PosToDir = sBtlGetPosToDir(x, z, v49, v50);
            if (v47->para->devilid == 314)
              v52 = wk;
            else
              v52 = v47;
            Add(v47->ListID, gSklID, v52->pos.x, v52->pos.y, v47->pos.z, PosToDir, 1.0, 0);
          }
          v54 = gSklID;
          sBtlPlayerSetDirectHitRangeTgt(wk, v54, 4, 0.0, 400.0, gTargetX, gTargetY, gTargetZ);
        }
        v59 = FPS60;
        v60 = gStepTime;
        if (v60 > (f32)(v59 * 60.0))
        {
          v60 = 0.0;
          *(u64 *)&gStep = 1;
        }
        if (v60 <= (f32)(v59 * 90.0))
          return 2;
LABEL_73:
        sBtlClrSuperArmor2(wk);
        sBtlResetAction(wk);
        sBtlSetUseSkill(wk, 0, 0);
        *(u64 *)sBtlPlayer_Magic->static_fields = 2;
        return 2;
      }
LABEL_69:
      if (gStepTime <= (f32)(FPS60 * 90.0))
        return 2;
      goto LABEL_73;
    }
    gSklBulletUse = 1;
    v22 = wk;
    v23 = v22->UnitMng;
    v24 = gTargetID;
    if (sBtlSearchUnit_ID(v22->UnitMng, v24))
      goto LABEL_33;
    goto LABEL_9001;
    if (sBtlSearchUnit_ID(v23, v24))
    {
LABEL_33:
LABEL_34:
      v26 = wk->UnitMng;
      v27 = gTargetID;
      v28 = sBtlSearchUnit_ID(v26, v27);
      if (v28)
      {
        v29 = wk->rot.x;
        y = wk->rot.y;
        v31 = v28;
        v33 = wk->rot.z;
        w = wk->rot.w;
        v68.x = v29;
        v68.y = y;
        v68.z = v33;
        v68.w = w;
        RotToDir = sBtlGetRotToDir(v68);
        Add(v31->ListID, gSklID, wk->pos.x, wk->pos.y + -120.0, wk->pos.z, RotToDir, 0);
        *(u64 *)&gTargetX = *(u64 *)&v31->pos.x;
        gTargetZ = v31->pos.z;
      }
      goto LABEL_40;
    }
LABEL_9001:
    sBtlSetNextTarget_RS(wk);
    gTargetID = wk->actaiwk->targetID;
    goto LABEL_34;
  }
  gStepTime = gStepTime + VRF_DeltaTime;
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_73;
  v63 = gStepTime;
  v64 = FPS60;
  if (v63 > (f32)(v64 * 120.0))
    goto LABEL_73;
  v66 = v64 * 16.0;
  if (v63 >= (f32)(v64 * 16.0))
  {
    sBtlClrSuperArmor2(wk);
    v63 = gStepTime;
    v64 = FPS60;
    v66 = v64 * 16.0;
  }
  if (v63 >= v66)
  {
    if (sBtlPlayerRSkillCancel_Setsuma(wk))
      return 2;
    v63 = gStepTime;
    v64 = FPS60;
    v66 = v64 * 16.0;
  }
  if (v63 >= v66)
  {
    if (sBtlPlayerRSkillCancel_RSptrit(wk))
      return 2;
    v63 = gStepTime;
    v64 = FPS60;
  }
  v67 = v64 * 20.0;
  if (v63 >= (f32)(v64 * 20.0))
  {
    if (sBtlPlayerRSkillCancel_Skill(wk))
      return 2;
    v63 = gStepTime;
    v64 = FPS60;
    v67 = v64 * 20.0;
  }
  if (v63 >= v67)
  {
    if (sBtlPlayerRSkillCancel_Guard(wk))
      return 2;
    v63 = gStepTime;
    v64 = FPS60;
    v67 = v64 * 20.0;
  }
  if (v63 >= v67)
  {
    if (sBtlPlayerRSkillCancel_Jump(wk))
      return 2;
    v63 = gStepTime;
    v64 = FPS60;
    v67 = v64 * 20.0;
  }
  if (v63 >= v67)
  {
    if (sBtlPlayerRSkillCancel_Kaihi(wk))
      return 2;
    v63 = gStepTime;
    v64 = FPS60;
    v67 = v64 * 20.0;
  }
  if (v63 >= v67)
  {
    if (sBtlPlayerRSkillCancel_Gun(wk))
      return 2;
    v63 = gStepTime;
    v64 = FPS60;
  }
  if (v63 >= (f32)(v64 * 25.0))
    sBtlPlayerRSkillCancel_Move(wk);
  return 2;
}
