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
#include "sbtlplayer_magic3.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sndmanager.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static s32 gStep;
static f32 gStepTime;
static SKLID gSklID;
static bool gSklUse;
static bool gSklBarrierUse;
static bool gVoiceUse;
static s32 gClearIndex;

// 0x20eb0c0
s32 sBtlPlayerRMagic3Init(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  SBATTLE_WORK *v10;
  f32 x;
  f32 y;
  u32 v16;
  f32 z;
  f32 w;
  sdfVector4_t v21;

  wk->cmstatus = 0;
  v10 = wk;
  v10->mode = 30;
  v10->kochokuCnt = 0;
  v10->sord_counter = 0;
  v10->bHuumaCancel = 0;
  v10->ComboMotRetryCnt = 0;
  v10->ComboMotRetryUse = 0;
  *(u64 *)&v10->sord_st = 0;
  sBtlSetAction(wk, 15, 0);
  sBtlSetMotion(wk, 180, 0, 0, 0);
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  *(u64 *)&gStep = 0;
  gSklID = SklID;
  *(u16 *)&gSklUse = 0;
  gVoiceUse = 0;
  gClearIndex = ClearIndex;
  if (SklID == 212)
  {
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    v16 = 131334147;
    goto LABEL_15;
  }
  if (SklID == 208)
  {
    x = wk->pos.x;
    y = wk->pos.y;
    v16 = 131072003;
    z = wk->pos.z;
    w = wk->pos.w;
LABEL_15:
    v21.x = x;
    v21.y = y;
    v21.z = z;
    v21.w = w;
    sBtlPlay3DSE(v16, v21);
    return 2;
  }
  return 2;
}

// 0x20eb310
s32 sBtlPlayerRMagic3Proc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 v7;
  s32 use_skillid;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v13;
  s32 v14;
  char **v16;
  s32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  s32 v24;
  f32 v25;
  f32 v26;
  s32 v27;
  f32 v28;
  SBTLUNIT_WORK *v29;
  SBTLUNIT_WORK *v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  s32 v39;
  s32 v40;
  SBTLUNIT_WORK *v41;
  SBTLUNIT_WORK *v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v49;
  s64 v50;
  s64 v53;
  f32 v54;
  f32 v55;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  s32 ListID;
  f32 v62;
  f32 v63;
  s32 v64;
  f32 v65;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  s64 v74;
  s32 v75;
  s32 v76;
  SBTLUNIT_WORK *v77;
  f32 v78;
  f32 v79;
  f32 v80;
  f32 v81;
  s32 v82;
  s32 v83;
  s32 v84;
  SBTLUNIT_WORK *PChara;
  s32 v86;
  SBTLSKILLP_TBL *Skilltbl;
  s32 attrtime;
  SBTLSKILLP_TBL *v89;
  tagSBTLSKL_BARRIER_WORK *v90;
  u32 badst;
  void *wkBarrier;
  u64 *v93;
  s64 size;
  void *items;
  Il2CppClass **v96;
  SBTLUNIT_WORK *v97;
  SBTLUNIT_WORK *v98;
  tagSBTLSKL_BARRIER_WORK *v99;
  u32 v100;
  u64 *v101;
  void *v102;
  s64 v103;
  void *v104;
  Il2CppClass **v105;
  SBTLUNIT_WORK *v106;
  SBTLUNIT_WORK *v107;
  tagSBTLSKL_BARRIER_WORK *v108;
  u32 v109;
  u64 *v110;
  void *v111;
  s64 v112;
  void *v113;
  Il2CppClass **v114;
  sdfVector4_t v116;
  sdfVector4_t HelperPos;
  sdfVector4_t v118;
  sdfVector4_t v119;
  sdfVector4_t v120;
  sdfVector4_t v121;
  sdfVector4_t v122;
  sdfVector4_t v123;

  *(u64 *)&HelperPos.x = 0;
  *(u64 *)&HelperPos.z = 0;
  hModel = wk->hModel;
  *(u64 *)&v116.x = 0;
  *(u64 *)&v116.z = 0;
  mdlGetMotionFrameF(hModel);
  if (gStep != 1)
  {
    if (gStep)
      return 2;
    v7 = gStepTime + VRF_DeltaTime;
    gStepTime = v7;
    if (v7 > (f32)(FPS60 * 5.0) && !gSklUse)
    {
      gSklUse = 1;
      sBtlPlayerRSkill_CoolTimeClr(wk, gClearIndex);
      if ((gSklID | 4) == 0xD4)
      {
        wk->damage_ActerOfsY = 0.0;
        wk->actwk->use_skillid = gSklID;
        sBtlSetUseSkill(wk, gSklID, 0);
        wk->hstatus &= ~0x20000u;
        use_skillid = wk->actwk->use_skillid;
        sBtlSetSetsuma_SkillStart(wk, use_skillid);
        sysmsgList = wk->sysmsgList;
        v13 = gSklID;
        sBtlCreateSM(sysmsgList, wk, 10, v13, 0, 120);
      }
    }
    if (gStepTime > (f32)(FPS60 * 16.0) && !gVoiceUse)
    {
      gVoiceUse = 1;
      v14 = gSklID;
      if (v14 == 212)
      {
        v16 = &"PVA01A_23C_000";
        goto LABEL_25;
      }
      if (v14 == 208)
      {
        v16 = &"PVA01A_22D_003";
LABEL_25:
        sndVoicePlayFile(*v16, 0);
        goto LABEL_26;
      }
    }
LABEL_26:
    if (gStepTime <= (f32)(FPS60 * 35.0) || gSklBarrierUse)
      goto LABEL_135;
    gSklBarrierUse = 1;
    v18 = gSklID;
    if (v18 == 212)
    {
      x = wk->rot.x;
      y = wk->rot.y;
      z = wk->rot.z;
      w = wk->rot.w;
      v121.x = x;
      v121.y = y;
      v121.z = z;
      v121.w = w;
      RotToDir = sBtlGetRotToDir(v121);
      ListID = wk->ListID;
      v62 = wk->pos.x;
      v63 = wk->pos.y;
      v64 = gSklID;
      v65 = wk->pos.z;
      Add(ListID, v64, v62, v63 + -100.0, v65, RotToDir, 0);
      Nakama = sBtlGetNakama(0);
      if (Nakama)
      {
        v67 = Nakama;
        v68 = Nakama->rot.x;
        v69 = Nakama->rot.y;
        v70 = Nakama->rot.z;
        v71 = Nakama->rot.w;
        v122.x = v68;
        v122.y = v69;
        v122.z = v70;
        v122.w = v71;
        v72 = sBtlGetRotToDir(v122);
        *(u64 *)&v116.x = 0;
        *(u64 *)&v116.z = 0;
        GetUnitHelperPos(v67, &v116);
        v73 = v116.z;
        v74 = *(u64 *)&v116.x;
        v75 = v67->ListID;
        v76 = gSklID;
        Add(v75, v76, *(f32 *)&v74, *((f32 *)&v74 + 1), v73, v72, 0);
      }
      v77 = sBtlGetNakama(1);
      if (!v77)
        goto LABEL_110;
      v42 = v77;
      v78 = v77->rot.x;
      v79 = v77->rot.y;
      v80 = v77->rot.z;
      v81 = v77->rot.w;
      v123.x = v78;
      v123.y = v79;
      v123.z = v80;
      v123.w = v81;
      v47 = sBtlGetRotToDir(v123);
      *(u64 *)&v116.x = 0;
      *(u64 *)&v116.z = 0;
      GetUnitHelperPos(v42, &v116);
      v50 = *(u64 *)&v116.x;
      v49 = v116.z;
    }
    else
    {
      if (v18 != 208)
        goto LABEL_110;
      v19 = wk->rot.x;
      v20 = wk->rot.y;
      v22 = wk->rot.z;
      v21 = wk->rot.w;
      v118.x = v19;
      v118.y = v20;
      v118.z = v22;
      v118.w = v21;
      v23 = sBtlGetRotToDir(v118);
      v24 = wk->ListID;
      v25 = wk->pos.x;
      v26 = wk->pos.y;
      v27 = gSklID;
      v28 = wk->pos.z;
      Add(v24, v27, v25, v26 + -100.0, v28, v23, 0);
      v29 = sBtlGetNakama(0);
      if (v29)
      {
        v30 = v29;
        v31 = v29->rot.x;
        v32 = v29->rot.y;
        v33 = v29->rot.z;
        v34 = v29->rot.w;
        v119.x = v31;
        v119.y = v32;
        v119.z = v33;
        v119.w = v34;
        v35 = sBtlGetRotToDir(v119);
        *(u64 *)&HelperPos.x = 0;
        *(u64 *)&HelperPos.z = 0;
        GetUnitHelperPos(v30, &HelperPos);
        v36 = HelperPos.z;
        v37 = HelperPos.x;
        v38 = HelperPos.y;
        v39 = v30->ListID;
        v40 = gSklID;
        Add(v39, v40, v37, v38, v36, v35, 0);
      }
      v41 = sBtlGetNakama(1);
      if (!v41)
        goto LABEL_110;
      v42 = v41;
      v43 = v41->rot.x;
      v44 = v41->rot.y;
      v45 = v41->rot.z;
      v46 = v41->rot.w;
      v120.x = v43;
      v120.y = v44;
      v120.z = v45;
      v120.w = v46;
      v47 = sBtlGetRotToDir(v120);
      *(u64 *)&HelperPos.x = 0;
      *(u64 *)&HelperPos.z = 0;
      GetUnitHelperPos(v42, &HelperPos);
      v49 = HelperPos.z;
      v50 = *(u64 *)&HelperPos.x;
    }
    v82 = v42->ListID;
    v83 = gSklID;
    Add(v82, v83, *(f32 *)&v50, *((f32 *)&v50 + 1), v49, v47, 0);
LABEL_110:
    v84 = gSklID;
    if ((v84 | 4) == 0xD4)
    {
      PChara = sBtlGetPChara();
      v86 = gSklID;
      sBtlRecoverSpiritAdd(PChara, 3, v86);
      v84 = gSklID;
    }
    sBtlGetSklVisualTbl(v84);
    Skilltbl = sBtlGetSkilltbl(gSklID);
    if ((gSklID | 4) == 0xD4)
    {
      attrtime = Skilltbl->attrtime;
      v89 = Skilltbl;
      v90 = Allocate(tagSBTLSKL_BARRIER_WORK);
      _ctor(v90, 0);
      v90->m_skillid = gSklID;
      v90->m_barrierstatus = v89->attr;
      badst = v89->badst;
      v90->m_cnt = attrtime;
      v90->m_barrieradv = badst;
      v90->m_EndSM = 1;
      wkBarrier = wk->wkBarrier;
      v93 = Method_System_Collections_Generic_List_tagSBTLSKL_BARRIER_WORK__Add__;
      size = wkBarrier->_size;
      ++wkBarrier->_version;
      items = wkBarrier->_items;
      if ((u32)size >= LODWORD(items->max_length))
      {
        _AddWithResize(wkBarrier, v90, *(const MethodInfo_2DFC660 **)(*(u64 *)(v93[4] + 192) + 112));
      }
      else
      {
        wkBarrier->_size = size + 1;
        v96 = &items->obj.klass + size;
        v96[4] = v90;
      }
      CalcAisyo(wk);
      v97 = sBtlGetNakama(0);
      if (v97)
      {
        v98 = v97;
        v99 = Allocate(tagSBTLSKL_BARRIER_WORK);
        _ctor(v99, 0);
        v99->m_skillid = gSklID;
        v99->m_barrierstatus = v89->attr;
        v100 = v89->badst;
        v99->m_cnt = attrtime;
        v99->m_EndSM = 0;
        v99->m_barrieradv = v100;
        v101 = Method_System_Collections_Generic_List_tagSBTLSKL_BARRIER_WORK__Add__;
        v102 = v98->wkBarrier;
        v103 = v102->_size;
        ++v102->_version;
        v104 = v102->_items;
        if ((u32)v103 >= LODWORD(v104->max_length))
        {
          _AddWithResize(v102, v99, *(const MethodInfo_2DFC660 **)(*(u64 *)(v101[4] + 192) + 112));
        }
        else
        {
          v102->_size = v103 + 1;
          v105 = &v104->obj.klass + v103;
          v105[4] = v99;
        }
        CalcAisyo(v98);
      }
      v106 = sBtlGetNakama(1);
      if (v106)
      {
        v107 = v106;
        v108 = Allocate(tagSBTLSKL_BARRIER_WORK);
        _ctor(v108, 0);
        v108->m_skillid = gSklID;
        v108->m_barrierstatus = v89->attr;
        v109 = v89->badst;
        v108->m_cnt = attrtime;
        v108->m_EndSM = 0;
        v108->m_barrieradv = v109;
        v110 = Method_System_Collections_Generic_List_tagSBTLSKL_BARRIER_WORK__Add__;
        v111 = v107->wkBarrier;
        v112 = v111->_size;
        ++v111->_version;
        v113 = v111->_items;
        if ((u32)v112 >= LODWORD(v113->max_length))
        {
          _AddWithResize(v111, v108, *(const MethodInfo_2DFC660 **)(*(u64 *)(v110[4] + 192) + 112));
        }
        else
        {
          v111->_size = v112 + 1;
          v114 = &v113->obj.klass + v112;
          v114[4] = v108;
        }
        CalcAisyo(v107);
      }
      wk->hstatus &= ~0x20000u;
    }
LABEL_135:
    if (gStepTime > (f32)(FPS60 * 60.0))
    {
      v53 = 1;
LABEL_137:
      *(u64 *)&gStep = v53;
      return 2;
    }
    return 2;
  }
  gStepTime = gStepTime + VRF_DeltaTime;
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_53;
  goto LABEL_9000;
  if (sBtlCheckMotionEnd(wk))
  {
LABEL_53:
    sBtlClrSuperArmor2(wk);
    sBtlResetAction(wk);
    sBtlSetUseSkill(wk, 0, 0);
    v53 = 2;
    goto LABEL_137;
  }
LABEL_9000:
  if (gStepTime > (f32)(FPS60 * 45.0))
    goto LABEL_53;
  v54 = FPS60 + FPS60;
  if (gStepTime >= (f32)(FPS60 + FPS60))
  {
    sBtlClrSuperArmor2(wk);
    v54 = FPS60 + FPS60;
  }
  if (gStepTime >= v54)
  {
    if (sBtlPlayerRSkillCancel_Setsuma(wk))
      return 2;
    v54 = FPS60 + FPS60;
  }
  if (gStepTime >= v54)
  {
    if (sBtlPlayerRSkillCancel_RSptrit(wk))
      return 2;
  }
  if (gStepTime >= (f32)(FPS60 * 8.0))
  {
    if (sBtlPlayerRSkillCancel_Skill(wk))
      return 2;
  }
  v55 = FPS60 + FPS60;
  if (gStepTime >= (f32)(FPS60 + FPS60))
  {
    if (sBtlPlayerRSkillCancel_Guard(wk))
      return 2;
    v55 = FPS60 + FPS60;
  }
  if (gStepTime >= v55)
  {
    if (sBtlPlayerRSkillCancel_Jump(wk))
      return 2;
    v55 = FPS60 + FPS60;
  }
  if (gStepTime >= v55)
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
