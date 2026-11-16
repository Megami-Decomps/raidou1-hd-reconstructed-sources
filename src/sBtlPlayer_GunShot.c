#include "types.h"
#include "SKLID.h"
#include "aw_hits.h"
#include "aw_rsbullet.h"
#include "aw_rsmuzzle.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_gunshot.h"
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
static bool gEffHit2Done;
static s32 gEffHit2Cnt;
static bool gEffHit3Done;
static s32 gEffHit3Cnt;
static f32 gTargetX;
static f32 gTargetY;
static f32 gTargetZ;
static s32 gClearIndex;

static void KayaHajiki(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, f32 _OfsY);

// 0x20e5f80
s32 sBtlPlayerRGunShotInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
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
  f32 v30;
  f32 y;
  f32 v32;
  f32 w;
  sdfVector4_t v35;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 23;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 169, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u32 *)&gSklUse = 0;
  gEffHit2Done = 0;
  gEffHit3Done = 0;
  gClearIndex = ClearIndex;
  targetID = wk->actaiwk->targetID;
  gEffHit2Cnt = 4;
  gEffHit3Cnt = 7;
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
  v30 = wk->pos.x;
  y = wk->pos.y;
  v32 = wk->pos.z;
  w = wk->pos.w;
  v35.x = v30;
  v35.y = y;
  v35.z = v32;
  v35.w = w;
  sBtlPlay3DSE(0x7080003u, v35);
  return 2;
}

// 0x20e84d0
void sBtlPlayerCallHitDone(void) {
  gEffHitDone = 1;
}

// 0x20e8520
static void KayaHajiki(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, f32 _OfsY) {
  f32 x;
  f32 z;
  f32 v9;
  f32 v10;
  f32 PosToDir;
  f32 RotToDir;
  s64 v13;
  f32 y;
  s32 ListID;
  f32 Dir180;
  s64 ToZ;

  ToZ = 0;
  if (wklock && wklock->para->devilid == 257)
  {
    x = wklock->pos.x;
    z = wklock->pos.z;
    v9 = wk->pos.x;
    v10 = wk->pos.z;
    PosToDir = sBtlGetPosToDir(x, z, v9, v10);
    RotToDir = sBtlGetRotToDir(wklock->rot);
    sBtlGetMoveXZ(wklock->pos.x, wklock->pos.z, PosToDir, 80.0, (f32 *)&ToZ + 1, &ToZ);
    v13 = ToZ;
    y = wklock->pos.y;
    ListID = wklock->ListID;
    Dir180 = sBtlGetDir180(RotToDir);
    Add_Hajiki(ListID, *((f32 *)&v13 + 1) / -100.0, (f32)((f32)(y + -76.0) + OfsY) / -100.0, *(f32 *)&v13 / -100.0, Dir180);
  }
}

// 0x20e8670
s32 sBtlPlayerRGunShotProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  SBTLUNIT_WORK *v5;
  f32 gStepTime_local;
  s32 use_skillid;
  SBATTLE_WORK *v16;
  SBTLUNIT_LISTWORK *v17;
  s32 v18;
  SBTLUNIT_LISTWORK *v20;
  s32 v21;
  SBTLUNIT_WORK *v22;
  f32 v23;
  f32 v24;
  SBTLUNIT_WORK *v25;
  f32 v26;
  f32 v27;
  f32 RotToDir;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v33;
  s32 v37;
  SBTLUNIT_LISTWORK *v38;
  SBTLUNIT_WORK *v39;
  SBTLUNIT_WORK *v40;
  s32 devilid;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  s64 v48;
  f32 v49;
  f32 v50;
  u32 v52;
  f32 x;
  f32 y;
  s32 v56;
  f32 w;
  f32 z;
  s32 v62;
  SBTLUNIT_LISTWORK *v63;
  SBTLUNIT_WORK *v64;
  SBTLUNIT_WORK *v67;
  s32 v68;
  bool v69;
  s32 v70;
  s64 ToZ;
  sdfVector4_t v73;
  sdfVector4_t v74;

  ToZ = 0;
  hModel = wk->hModel;
  mdlGetMotionFrameF(hModel);
  if (gStep != 1)
  {
    if (gStep)
      return 2;
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
    if (gStepTime_local <= (f32)(FPS60 * 32.0) || gSklBulletUse)
    {
LABEL_27:
      UnitMng = wk->UnitMng;
      v33 = sBtlSearchUnit_ID(UnitMng, gTargetID);
      if (v33)
      {
        *(u64 *)&gTargetX = *(u64 *)&v33->pos.x;
        gTargetZ = v33->pos.z;
        if (gEffHitDone)
        {
LABEL_32:
          if (gSklHitUse)
            goto LABEL_104;
          gSklHitUse = 1;
          v37 = gTargetID;
          v38 = wk->UnitMng;
          v39 = sBtlSearchUnit_ID(v38, v37);
          if (!v39)
            goto LABEL_104;
          v40 = v39;
          devilid = v39->para->devilid;
          if (devilid <= 274)
          {
            if (devilid != 232 && v39->para->devilid != 264 && (u32)(devilid - 275) < 0xFFFFFFFD)
            {
              goto LABEL_100;
            }
          }
          else
          {
            if ((u32)devilid > 0x121)
            {
              if (devilid == 299 || (u32)(devilid - 306) <= 3)
                goto LABEL_97;
LABEL_100:
              x = v40->pos.x;
              y = v40->pos.y;
              v56 = gSklID;
              z = v40->pos.z;
              w = v40->pos.w;
              v74.x = x;
              v74.y = y;
              v74.z = z;
              v74.w = w;
              SetDamageProc(v40, wk, v56, v74);
LABEL_103:
              KayaHajiki(wk, v40, 0.0);
LABEL_104:
              if (gSklHitUse)
              {
                v62 = gTargetID;
                v63 = wk->UnitMng;
                v64 = sBtlSearchUnit_ID(v63, v62);
                if (v64)
                {
                  v67 = v64;
                  if (!gEffHit2Done)
                  {
                    v68 = gEffHit2Cnt - 1;
                    v69 = gEffHit2Cnt == 1;
                    gEffHit2Cnt = v68;
                    if (v68 < 0 || v69)
                    {
                      gEffHit2Done = 1;
                      KayaHajiki(wk, v64, -20.0);
                    }
                  }
                  if (!gEffHit3Done)
                  {
                    v70 = gEffHit3Cnt - 1;
                    v69 = gEffHit3Cnt == 1;
                    gEffHit3Cnt = v70;
                    if (v70 < 0 || v69)
                    {
                      gEffHit3Done = 1;
                      KayaHajiki(wk, v67, -40.0);
                    }
                  }
                }
              }
              v44 = gStepTime;
              v45 = FPS60;
              if (v44 > (f32)(v45 * 60.0))
              {
                v44 = 0.0;
                *(u64 *)&gStep = 1;
              }
LABEL_120:
              if (v44 > (f32)(v45 * 90.0))
              {
                v48 = 1;
LABEL_122:
                *(u64 *)&gStep = v48;
                return 2;
              }
              return 2;
            }
            v52 = devilid - 285;
            if (v52 > 4 || v52 == 2)
              goto LABEL_100;
          }
LABEL_97:
          if (!sBtlCheckDamageTarget(v40))
            goto LABEL_103;
          goto LABEL_100;
        }
LABEL_48:
        v44 = gStepTime;
        v45 = FPS60;
        goto LABEL_120;
      }
      if (gEffHitDone)
        goto LABEL_32;
      goto LABEL_48;
    }
    gSklBulletUse = 1;
    v16 = wk;
    v17 = v16->UnitMng;
    v18 = gTargetID;
    if (sBtlSearchUnit_ID(v16->UnitMng, v18))
      goto LABEL_20;
    goto LABEL_9001;
    if (sBtlSearchUnit_ID(v17, v18))
    {
LABEL_20:
LABEL_21:
      v20 = wk->UnitMng;
      v21 = gTargetID;
      v22 = sBtlSearchUnit_ID(v20, v21);
      if (v22)
      {
        v23 = wk->rot.x;
        v24 = wk->rot.y;
        v25 = v22;
        v27 = wk->rot.z;
        v26 = wk->rot.w;
        v73.x = v23;
        v73.y = v24;
        v73.z = v27;
        v73.w = v26;
        RotToDir = sBtlGetRotToDir(v73);
        sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir, 30.0, (f32 *)&ToZ + 1, &ToZ);
        Add(v25->ListID, gSklID, *((f32 *)&ToZ + 1), wk->pos.y + -150.0, *(f32 *)&ToZ, RotToDir, 0);
        sBtlGetMoveXZ(wk->pos.x, wk->pos.z, RotToDir, 70.0, (f32 *)&ToZ + 1, &ToZ);
        Add(*((f32 *)&ToZ + 1), wk->pos.y + -150.0, *(f32 *)&ToZ, RotToDir, 0);
        *(u64 *)&gTargetX = *(u64 *)&v25->pos.x;
        gTargetZ = v25->pos.z;
      }
      goto LABEL_27;
    }
LABEL_9001:
    sBtlSetNextTarget_RS(wk);
    gTargetID = wk->actaiwk->targetID;
    goto LABEL_21;
  }
  gStepTime = gStepTime + VRF_DeltaTime;
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_51;
  goto LABEL_9002;
  if (sBtlCheckMotionEnd(wk))
  {
LABEL_51:
    sBtlClrSuperArmor2(wk);
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    v48 = 2;
    goto LABEL_122;
  }
LABEL_9002:
  v46 = gStepTime;
  v47 = FPS60;
  if (v46 > (f32)(v47 * 60.0))
    goto LABEL_51;
  v49 = v47 * 12.0;
  if (v46 >= (f32)(v47 * 12.0))
  {
    sBtlClrSuperArmor2(wk);
    v46 = gStepTime;
    v47 = FPS60;
    v49 = v47 * 12.0;
  }
  if (v46 >= v49)
  {
    if (sBtlPlayerRSkillCancel_Setsuma(wk))
      return 2;
    v46 = gStepTime;
    v47 = FPS60;
    v49 = v47 * 12.0;
  }
  if (v46 >= v49)
  {
    if (sBtlPlayerRSkillCancel_RSptrit(wk))
      return 2;
    v46 = gStepTime;
    v47 = FPS60;
  }
  v50 = v47 * 25.0;
  if (v46 >= (f32)(v47 * 25.0))
  {
    if (sBtlPlayerRSkillCancel_Skill(wk))
      return 2;
    v46 = gStepTime;
    v47 = FPS60;
    v50 = v47 * 25.0;
  }
  if (v46 >= v50)
  {
    if (sBtlPlayerRSkillCancel_Guard(wk))
      return 2;
    v46 = gStepTime;
    v47 = FPS60;
    v50 = v47 * 25.0;
  }
  if (v46 >= v50)
  {
    if (sBtlPlayerRSkillCancel_Jump(wk))
      return 2;
    v46 = gStepTime;
    v47 = FPS60;
    v50 = v47 * 25.0;
  }
  if (v46 >= v50)
  {
    if (sBtlPlayerRSkillCancel_Kaihi(wk))
      return 2;
    v46 = gStepTime;
    v47 = FPS60;
  }
  if (v46 >= (f32)(v47 * 10.0))
  {
    if (sBtlPlayerRSkillCancel_Gun(wk))
      return 2;
    v46 = gStepTime;
    v47 = FPS60;
  }
  if (v46 >= (f32)(v47 * 40.0) && !sBtlPlayerRSkillCancel_Move(wk))
    sBtlPlayerRSkillCancel_Huuma(wk);
  return 2;
}
