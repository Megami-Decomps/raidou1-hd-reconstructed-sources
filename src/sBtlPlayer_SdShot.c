#include "types.h"
#include "SKLID.h"
#include "aw_rsbullet.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_sdshot.h"
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
static s32 gClearIndex;
static s32 gRetryCnt;
static bool gRetryUse;
static s32 gRetry_ListID;
static SKLID gRetry_SkillID;
static f32 gRetry_X;
static f32 gRetry_Y;
static f32 gRetry_Z;
static f32 gRetry_Dir;
static f32 gRetry_Num;

// 0x20f0d60
s32 sBtlPlayerRSdShotInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
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
  v10->mode = 22;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 168, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u16 *)&gSklUse = 0;
  gClearIndex = ClearIndex;
  gRetryCnt = 0;
  gRetryUse = 0;
  gRetry_Num = 0.0;
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

// 0x20f10b0
s32 sBtlPlayerRSdShotProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 gStepTime_local;
  s32 use_skillid;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  f32 v21;
  f32 v24;
  s32 v25;
  SBTLUNIT_LISTWORK *v26;
  s32 v27;
  SBTLUNIT_WORK *v28;
  s32 ListID;
  f32 v30;
  s64 v31;
  f32 v34;
  f32 v35;
  s64 v36;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  s32 v42;
  bool v43;
  SBTLUNIT_LISTWORK *v48;
  SBTLUNIT_WORK *v49;
  s32 v50;
  s64 ToZ;
  sdfVector4_t v53;
  sdfVector4_t v54;

  ToZ = 0;
  hModel = wk->hModel;
  mdlGetMotionFrameF(hModel);
  if (gStep != 1)
  {
    if (!gStep)
    {
      gStepTime_local = gStepTime + VRF_DeltaTime;
      gStepTime = gStepTime_local;
      if (gStepTime_local > FPS60 && !gSklUse)
      {
        gSklUse = 1;
        sBtlPlayerRSkill_CoolTimeClr(wk, gClearIndex);
        wk->damage_ActerOfsY = 0.0;
        wk->actwk->use_skillid = gSklID;
        sBtlSetUseSkill(wk, gSklID, 0);
        wk->hstatus &= ~0x20000u;
        use_skillid = wk->actwk->use_skillid;
        sBtlSetSetsuma_SkillStart(wk, use_skillid);
        gStepTime_local = gStepTime;
      }
      if (gStepTime_local > (f32)(FPS60 * 57.0) && !gSklBulletUse)
      {
        gSklBulletUse = 1;
        x = wk->rot.x;
        y = wk->rot.y;
        z = wk->rot.z;
        w = wk->rot.w;
        v53.x = x;
        v53.y = y;
        v53.z = z;
        v53.w = w;
        RotToDir = sBtlGetRotToDir(v53);
        sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir, 120.0, (f32 *)&ToZ + 1, &ToZ);
        UnitMng = wk->UnitMng;
        targetID = wk->actaiwk->targetID;
        if (!sBtlSearchUnit_ID(UnitMng, targetID))
        {
          sBtlSetNextTarget_RS(wk);
        }
        v21 = wk->pos.y;
        gRetry_X = *((f32 *)&ToZ + 1);
        gRetry_Y = v21;
        v24 = *(f32 *)&ToZ;
        v25 = gSklID;
        gRetry_Num = 0.0;
        gRetry_ListID = -1;
        gRetry_SkillID = v25;
        gRetry_Z = v24;
        gRetry_Dir = RotToDir;
        v26 = wk->UnitMng;
        v27 = wk->actaiwk->targetID;
        v28 = sBtlSearchUnit_ID(v26, v27);
        if (v28)
        {
          ListID = v28->ListID;
          v30 = wk->pos.y;
          v31 = ToZ;
          gRetry_ListID = ListID;
        }
        else
        {
          ListID = -1;
          v30 = wk->pos.y;
          v31 = ToZ;
        }
        Add(ListID, gSklID, *((f32 *)&v31 + 1), v30, *(f32 *)&v31, RotToDir, 0);
        v38 = wk->pos.x;
        v39 = wk->pos.y;
        v41 = wk->pos.z;
        v40 = wk->pos.w;
        v54.x = v38;
        v54.y = v39;
        v54.z = v41;
        v54.w = v40;
        sBtlPlay3DSE(0x7A30004u, v54);
      }
      if (gSklBulletUse && gRetry_Num < 3.0)
      {
        v42 = gRetryCnt + 1;
        v43 = gRetryCnt - 14 < 0;
        gRetryCnt = v42;
        if (v43 ^ __OFSUB__(v42, 15) | (v42 == 15))
        {
          if (!(v42 % 3) && !Chk_C_ZANTOBI())
          {
            gRetryUse = 1;
            gRetry_Num = gRetry_Num + 1.0;
            if (gRetry_ListID == -1)
            {
              v50 = -1;
            }
            else
            {
              v48 = wk->UnitMng;
              v49 = sBtlSearchUnit_ID(v48, gRetry_ListID);
              if (v49)
                v50 = v49->ListID;
              else
                v50 = -1;
            }
            Add(v50, gRetry_SkillID, gRetry_X, gRetry_Y, gRetry_Z, gRetry_Dir, 0);
          }
        }
      }
      if (gStepTime > (f32)(FPS60 * 70.0))
      {
        v36 = 1;
LABEL_95:
        *(u64 *)&gStep = v36;
        return 2;
      }
    }
    return 2;
  }
  gStepTime = gStepTime + VRF_DeltaTime;
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_37;
  goto LABEL_9000;
  if (sBtlCheckMotionEnd(wk))
  {
LABEL_37:
    sBtlClrSuperArmor2(wk);
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    v36 = 2;
    goto LABEL_95;
  }
LABEL_9000:
  v34 = gStepTime;
  v35 = FPS60;
  if (v34 > (f32)(v35 * 120.0))
    goto LABEL_37;
  if (v34 >= v35)
  {
    sBtlClrSuperArmor2(wk);
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= v35)
  {
    if (sBtlPlayerRSkillCancel_Setsuma(wk))
      return 2;
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= v35)
  {
    if (sBtlPlayerRSkillCancel_RSptrit(wk))
      return 2;
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= v35)
  {
    if (sBtlPlayerRSkillCancel_Skill(wk))
      return 2;
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= v35)
  {
    if (sBtlPlayerRSkillCancel_Guard(wk))
      return 2;
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= v35)
  {
    if (sBtlPlayerRSkillCancel_Jump(wk))
      return 2;
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= v35)
  {
    if (sBtlPlayerRSkillCancel_Kaihi(wk))
      return 2;
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= v35)
  {
    if (sBtlPlayerRSkillCancel_Gun(wk))
      return 2;
    v34 = gStepTime;
    v35 = FPS60;
  }
  if (v34 >= (f32)(v35 * 30.0) && !sBtlPlayerRSkillCancel_Move(wk))
    sBtlPlayerRSkillCancel_Huuma(wk);
  return 2;
}
