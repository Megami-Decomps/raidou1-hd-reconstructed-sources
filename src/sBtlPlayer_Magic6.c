#include "types.h"
#include "SKLID.h"
#include "aw_rsbarrier.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtlcalc.h"
#include "sbtldmg.h"
#include "sbtlexp.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_magic6.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static s32 gStep;
static f32 gStepTime;
static SKLID gSklID;
static bool gSklUse;
static bool gSklBarrierUse;
static bool gSklHatudoUse;
static s32 gClearIndex;
static s32 gRetryCnt;

// 0x20ed3d0
s32 sBtlPlayerRMagic6Init(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 33;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 183, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  gSklID = SklID;
  gClearIndex = ClearIndex;
  gRetryCnt = 0;
  *(u64 *)&gStep = 0;
  *(u16 *)&gSklUse = 0;
  gSklHatudoUse = 0;
  return 2;
}

// 0x20ed580
s32 sBtlPlayerRMagic6Proc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v7;
  f32 gStepTime_local;
  s32 use_skillid;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v15;
  s32 v16;
  bool v18;
  f32 v20;
  f32 v21;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  s32 ListID;
  f32 v29;
  f32 v30;
  s32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  s32 v38;
  f32 v39;
  f32 v40;
  s32 v41;
  f32 v42;
  SBTLUNIT_WORK *Nakama;
  f32 *v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  s32 v53;
  s32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  SBTLUNIT_WORK *v58;
  f32 *v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  s32 v68;
  s32 v69;
  f32 v70;
  f32 v71;
  f32 v72;
  SBTLUNIT_WORK *PChara;
  s32 v74;
  u32 badstatus;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *v79;
  f32 v81;
  f32 v82;
  s64 v83;
  f32 v84;
  f32 v85;
  SBTLUNIT_WORK *v86;
  u32 v87;
  sdatUnitWork_t *v88;
  SBTLUNIT_WORK *v89;
  SBTLUNIT_WORK *v90;
  u32 v91;
  sdatUnitWork_t *v92;
  sdfVector4_t v94;
  sdfVector4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;
  sdfVector4_t v98;
  sdfVector4_t v99;

  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  if (gStep != 1)
  {
    if (gStep)
      return 2;
    v7 = MotionFrameF;
    gStepTime_local = gStepTime + VRF_DeltaTime;
    gStepTime = gStepTime_local;
    if (gStepTime_local > (f32)(FPS60 * 5.0) && !gSklUse)
    {
      wk->damage_ActerOfsY = 0.0;
      gSklUse = 1;
      wk->actwk->use_skillid = gSklID;
      sBtlSetUseSkill(wk, gSklID, 0);
      wk->hstatus &= ~0x20000u;
      use_skillid = wk->actwk->use_skillid;
      sBtlSetSetsuma_SkillStart(wk, use_skillid);
      sysmsgList = wk->sysmsgList;
      v15 = gSklID;
      sBtlCreateSM(sysmsgList, wk, 10, v15, 0, 120);
      gStepTime_local = gStepTime;
    }
    v16 = gRetryCnt + 1;
    gRetryCnt = v16;
    v18 = gStepTime_local > (f32)(FPS60 + FPS60) && v16 % 3 == 0 && v16 <= 19;
    if (v18 && (wk->motionno != 183 || v7 == 0.0))
    {
      sBtlSetMotion(wk, 183, 0, 0, 0);
    }
    v20 = FPS60;
    v21 = gStepTime;
    if (v21 > (f32)(v20 * 0.0) && !gSklHatudoUse)
    {
      gSklHatudoUse = 1;
      sBtlPlayerRSkill_CoolTimeClr(wk, gClearIndex);
      x = wk->rot.x;
      y = wk->rot.y;
      z = wk->rot.z;
      w = wk->rot.w;
      v94.x = x;
      v94.y = y;
      v94.z = z;
      v94.w = w;
      RotToDir = sBtlGetRotToDir(v94);
      ListID = wk->ListID;
      v29 = wk->pos.x;
      v30 = wk->pos.y;
      v31 = gSklID;
      v32 = wk->pos.z;
      Add(ListID, v31, v29, v30, v32, RotToDir, 0);
      v21 = gStepTime;
      v20 = FPS60;
    }
    if (v21 <= (f32)(v20 * 35.0) || gSklBarrierUse)
      goto LABEL_130;
    gSklBarrierUse = 1;
    v33 = wk->rot.x;
    v34 = wk->rot.y;
    v36 = wk->rot.z;
    v35 = wk->rot.w;
    v95.x = v33;
    v95.y = v34;
    v95.z = v36;
    v95.w = v35;
    v37 = sBtlGetRotToDir(v95);
    v38 = wk->ListID;
    v39 = wk->pos.x;
    v40 = wk->pos.y;
    v41 = gSklID;
    v42 = wk->pos.z;
    Add(v38, v41, v39, v40, v42, v37, 0);
    Nakama = sBtlGetNakama(0);
    if (Nakama)
    {
      v44 = Nakama;
      v45 = Nakama->rot.x;
      v46 = Nakama->rot.y;
      v47 = Nakama->rot.z;
      v48 = Nakama->rot.w;
      v96.x = v45;
      v96.y = v46;
      v96.z = v47;
      v96.w = v48;
      v49 = sBtlGetRotToDir(v96);
      v50 = v44[41];
      v51 = v44[42];
      v52 = v44[43];
      v53 = *((u32 *)v44 + 91);
      v54 = gSklID;
      Add(v53, v54, v50, v51, v52, v49, 0);
      v55 = v44[41];
      v56 = v44[42];
      v57 = v44[43];
      v97.w = 0.0;
      v97.x = v55;
      v97.y = v56;
      v97.z = v57;
      sBtlPlay3DSE(0x8390004u, v97);
    }
    v58 = sBtlGetNakama(1);
    if (v58)
    {
      v59 = v58;
      v60 = v58->rot.x;
      v61 = v58->rot.y;
      v62 = v58->rot.z;
      v63 = v58->rot.w;
      v98.x = v60;
      v98.y = v61;
      v98.z = v62;
      v98.w = v63;
      v64 = sBtlGetRotToDir(v98);
      v65 = v59[41];
      v66 = v59[42];
      v67 = v59[43];
      v68 = *((u32 *)v59 + 91);
      v69 = gSklID;
      Add(v68, v69, v65, v66, v67, v64, 0);
      v70 = v59[41];
      v71 = v59[42];
      v72 = v59[43];
      v99.w = 0.0;
      v99.x = v70;
      v99.y = v71;
      v99.z = v72;
      sBtlPlay3DSE(0x8390004u, v99);
    }
    PChara = sBtlGetPChara();
    v74 = gSklID;
    sBtlKofunSpiritAdd(PChara, 3, v74);
    sBtlGetSklVisualTbl(gSklID);
    sBtlGetSkilltbl(gSklID);
    badstatus = wk->para->badstatus;
    if (sBtlCheckBadStatus_Number(badstatus, 5, wk))
    {
      para = wk->para;
      wk->koufunskl = gSklID;
      if (sBtlGetBadStatus(para) == 16)
      {
        goto LABEL_67;
      }
      sBtlCheckResetBadStatus(wk);
LABEL_67:
      sBtlSetBadStatus_No(wk, 313, 5u, 1, -1);
      v79 = sBtlGetNakama(0);
      if (!v79)
        goto LABEL_119;
      goto LABEL_110;
    }
    v79 = sBtlGetNakama(0);
    if (!v79)
    {
LABEL_119:
      v89 = sBtlGetNakama(1);
      if (v89)
      {
        v90 = v89;
        v91 = v89->para->badstatus;
        if (sBtlCheckBadStatus_Number(v91, 5, v90))
        {
          v92 = v90->para;
          if (sBtlGetBadStatus(v92) != 16)
          {
            sBtlCheckResetBadStatus(v90);
            sBtlSetBadStatus_No(v90, 313, 5u, 1, -1);
          }
        }
      }
      v21 = gStepTime;
      v20 = FPS60;
LABEL_130:
      if (v21 > (f32)(v20 * 60.0))
      {
        v83 = 1;
LABEL_132:
        *(u64 *)&gStep = v83;
        return 2;
      }
      return 2;
    }
LABEL_110:
    v86 = v79;
    v87 = v79->para->badstatus;
    if (sBtlCheckBadStatus_Number(v87, 5, v86))
    {
      v88 = v86->para;
      if (sBtlGetBadStatus(v88) != 16)
      {
        sBtlCheckResetBadStatus(v86);
        sBtlSetBadStatus_No(v86, 313, 5u, 1, -1);
      }
    }
    goto LABEL_119;
  }
  gStepTime = gStepTime + VRF_DeltaTime;
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_74;
  goto LABEL_9002;
  if (sBtlCheckMotionEnd(wk))
  {
LABEL_74:
    sBtlClrSuperArmor2(wk);
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    v83 = 2;
    goto LABEL_132;
  }
LABEL_9002:
  v81 = gStepTime;
  v82 = FPS60;
  if (v81 > (f32)(v82 * 945.0))
    goto LABEL_74;
  v84 = v82 + v82;
  if (v81 >= (f32)(v82 + v82))
  {
    sBtlClrSuperArmor2(wk);
    v81 = gStepTime;
    v82 = FPS60;
    v84 = v82 + v82;
  }
  if (v81 >= v84)
  {
    if (sBtlPlayerRSkillCancel_Setsuma(wk))
      return 2;
    v81 = gStepTime;
    v82 = FPS60;
    v84 = v82 + v82;
  }
  if (v81 >= v84)
  {
    if (sBtlPlayerRSkillCancel_RSptrit(wk))
      return 2;
    v81 = gStepTime;
    v82 = FPS60;
  }
  if (v81 >= (f32)(v82 * 8.0))
  {
    if (sBtlPlayerRSkillCancel_Skill(wk))
      return 2;
    v81 = gStepTime;
    v82 = FPS60;
  }
  v85 = v82 + v82;
  if (v81 >= (f32)(v82 + v82))
  {
    if (sBtlPlayerRSkillCancel_Guard(wk))
      return 2;
    v81 = gStepTime;
    v82 = FPS60;
    v85 = v82 + v82;
  }
  if (v81 >= v85)
  {
    if (sBtlPlayerRSkillCancel_Jump(wk))
      return 2;
    v81 = gStepTime;
    v82 = FPS60;
    v85 = v82 + v82;
  }
  if (v81 >= v85)
  {
    if (sBtlPlayerRSkillCancel_Kaihi(wk))
      return 2;
    v81 = gStepTime;
    v82 = FPS60;
  }
  if (v81 >= (f32)(v82 * 8.0))
  {
    if (sBtlPlayerRSkillCancel_Gun(wk))
      return 2;
    v81 = gStepTime;
    v82 = FPS60;
  }
  if (v81 >= (f32)(v82 * 16.0))
    sBtlPlayerRSkillCancel_Move(wk);
  return 2;
}
