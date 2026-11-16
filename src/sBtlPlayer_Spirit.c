#include "types.h"
#include "ATRB.h"
#include "SKLID.h"
#include "aw_combibg.h"
#include "aw_combicam.h"
#include "aw_hits.h"
#include "aw_hitsscore.h"
#include "aw_rangecircle.h"
#include "aw_sbattle.h"
#include "aw_tuugikai.h"
#include "aw_tuugitotu.h"
#include "aw_tuugizan.h"
#include "aw_xatkpad.h"
#include "bsflow.h"
#include "dat.h"
#include "dds3basic.h"
#include "dds3kerneldraw.h"
#include "dds3unitobjectbasic.h"
#include "dds3vrf.h"
#include "evt.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "lmap.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtldmg.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlexp.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayerex.h"
#include "sbtlplayerfoot.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

#define D_DIST_TATE 250
#define D_DIST_NEW_MODE 600
#define Z_DIST_NEW_MODE 500
#define Z_DIST_NEW_MODE2 1300
#define Z_DIST_NEW_MODE3 150
#define Z_DIST_NEW_MODE4 800

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_CameraMoveDt S_CameraMoveDt;
typedef struct S_PosMove S_PosMove;

static s32 gStep;
static s32 gStepCnt;
static f32 gStepTime;
static SKLID gSklID;
s32 gEnemyNum;
static s32 gReTryCnt;
static s32 gReTryAddCnt;
static s32 gMotReTryCnt;
static s32 gMotReTryAddCnt;
bool gEndPosReset;
bool gEnd_BS_MUNAKA_Init_Imad_Restart;
SBTLUNIT_WORK *wk_BS_MUNAKA_Init_Imad_Restart;
bool gEnd_BS_MUNAKA_Init_Imad_Kotei;
static s32 gBkNakamaCutInFrameWait;
S_PosMove *g_aCamMoveJizenTyuugi;
S_PosMove *g_aTgtMoveJizenTyuugi;
S_CameraMoveDt *g_CamMovJizenTyuugi;
void *bloomCtrl;
s32 gStartWaitCnt;

static ATRB GetWeak(void);
static void SetLightChg(void);
static void ResetLightChg(void);
static void SetRndHitNum(s32 num, s32 frq);
static s32 _FakeRndHit(void);
static bool FakeRndHit(s32 qFrm, s32 qPow);
static void FakeDmgOne(s32 i);
s32 Support_RunWarpProcess_Skip(SBTLUNIT_WORK *wk);

// 0x20f18e0
s32 sBtlPlayerRSpiritInit(SBTLUNIT_WORK *wk) {
  s32 *EventBit;
  SBATTLE_WORK *v7;
  bool IsAction;
  s32 Weak;
  s32 v13;
  bool v14;
  s32 v17;
  s32 v18;
  SBATTLE_WORK *v23;
  SBTLSTP_LISTWORK *stpList;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v27;
  SBTLAI_WORK *aiwk;
  SBTLACTAI_WORK *actaiwk;
  SBTLAI_WORK *v32;
  SBTLACTAI_WORK *v33;
  CMBSKL *cmbSkl;
  CMBSKL *v36;
  CMBSKL *v38;
  CMBSKL *v39;
  void *Instance;
  s32 v46;
  s32 v52;
  void *v56;

  if (evtBitCheck(686) && !evtBitCheck(687))
  {
    EventBit = GBWK->EventBit;
    EventBit[21] |= 0x8000u;
    lmapSetBattleDestFlag(6);
    goto LABEL_11;
  }
LABEL_11:
  sBtlResetAction(wk);
  sBtlSetAction(wk, 1, 0);
  sBtlSetMotion(wk, 130, 0, 0, 0);
  sBtlResetSetsuma_BossTalk(wk);
  wk->cmstatus = 0;
  v7 = wk;
  v7->mode = 28;
  v7->kochokuCnt = 0;
  v7->sord_counter = 0;
  v7->bHuumaCancel = 0;
  v7->ComboMotRetryCnt = 0;
  v7->ComboMotRetryUse = 0;
  *(u64 *)&v7->sord_st = 0;
  wk->status &= ~0x100u;
  sBtlResetGunMode(wk, 0);
  sBtlResetCharge(wk, 0);
  sBtlResetJump(wk);
  wk->JumpAfterCnt = 0;
  sBtlBS_MISHAK_Action_Hiru_Cancel();
  gEndPosReset = 0;
  if (!IsAction(1))
  {
    IsAction = IsAction(5);
    if (!IsAction)
      goto LABEL_27;
  }
  gEndPosReset = 1;
LABEL_27:
  gEnd_BS_MUNAKA_Init_Imad_Restart = 0;
  gStep = 0;
  *(u64 *)&gStepTime = 0x2B200000000LL;
  Weak = GetWeak();
  if (Weak > 8)
  {
    switch (Weak)
    {
      case 16:
        v18 = sub_1905740(3, 0);
        if (v18 == 1)
        {
          v13 = 695;
          goto LABEL_39;
        }
        else if (v18)
        {
          v13 = 699;
          goto LABEL_39;
        }
        else
        {
          v13 = 691;
          goto LABEL_39;
        }
        break;
      case 32:
        v13 = 692;
        goto LABEL_39;
      case 64:
        v13 = 701;
        goto LABEL_39;
      default:
        goto LABEL_40;
    }
    goto LABEL_38;
  }
  if (Weak == 4)
  {
    v13 = 690;
    goto LABEL_39;
  }
  if (Weak != 8)
    goto LABEL_40;
  v13 = 696;
LABEL_38:
LABEL_39:
  gSklID = v13;
LABEL_40:
  v14 = IsAction(15);
  if (!v14)
    goto LABEL_68;
  if (gSklID != 695)
  {
    if (gSklID != 692)
      goto LABEL_68;
  }
  switch ((u32)sub_1905740(5, 0))
  {
    case 0u:
      v17 = 690;
      break;
    case 1u:
      v17 = 696;
      break;
    case 2u:
      v17 = 691;
      break;
    case 3u:
      v17 = 699;
      break;
    default:
      v17 = 701;
      break;
  }
  gSklID = v17;
LABEL_68:
  sBtlPlayerPushAllPosRotDispHit();
  sBtlPushCamera();
  sBtlClrSpiritWaza();
  sBtlPlayerSetTateHitEnemy();
  sBtlGetNakama(wk->SpiritSkillNakamaIdx);
  v23 = wk;
  stpList = v23->stpList;
  v23->status2 |= 0x20u;
  sBtlReleaseSTP_List(stpList, 2u);
  sBtlPlayerBgnWaitALL_Spirit(wk, 0);
  Nakama = sBtlGetNakama(0);
  v27 = sBtlGetNakama(1);
  if (Nakama)
  {
    sBtlEndWait(Nakama);
  }
  if (v27)
  {
    sBtlEndWait(v27);
  }
  if (Nakama)
  {
    sBtlProc_YoyakuEndChk(Nakama);
    sBtlSetAction(Nakama, 1, 0);
    sBtlSetMotion(Nakama, 0, 0, 0, 0);
    aiwk = Nakama->aiwk;
    Nakama->actwk->use_skillid = 0;
    actaiwk = Nakama->actaiwk;
    aiwk->mode = 12;
    actaiwk->stat = 1;
    sBtlProc_YoyakuEnd(Nakama);
    goto LABEL_86;
  }
LABEL_86:
  if (v27)
  {
    sBtlProc_YoyakuEndChk(v27);
    sBtlSetAction(v27, 1, 0);
    sBtlSetMotion(v27, 0, 0, 0, 0);
    v32 = v27->aiwk;
    v27->actwk->use_skillid = 0;
    v33 = v27->actaiwk;
    v32->mode = 12;
    v33->stat = 1;
    sBtlProc_YoyakuEnd(v27);
  }
  sBtlShugouKaijyo();
  cmbSkl = wk->cmbSkl;
  cmbSkl->pNakama0 = 0;
  v36 = wk->cmbSkl;
  v36->pNakama1 = 0;
  v38 = wk->cmbSkl;
  v39 = wk->cmbSkl;
  v39->cnt = 0;
  v38->sklId = gSklID;
  *(u32 *)&v39->step = 0x10000;
  sBtlStatusBitOn(wk, 0x4010u);
  wk->status |= 1u;
  wk->flg |= 2u;
  if (Nakama)
    Nakama->flg |= 2u;
  if (v27)
    v27->flg |= 2u;
  sBtlResetMutekiColor(wk);
  sBtlForceDeleteAll(0);
  DeleteAll();
  Instance = get_Instance(0);
  ClrCallMark(Instance, 0);
  switch (gSklID)
  {
    case 0x2B2:
      v46 = 0;
      goto LABEL_120;
    case 0x2B3:
    case 0x2B7:
    case 0x2BB:
      v46 = 2;
      goto LABEL_120;
    case 0x2B4:
      v46 = 3;
      goto LABEL_120;
    case 0x2B8:
      v46 = 1;
      goto LABEL_120;
    case 0x2BD:
      v46 = 4;
LABEL_120:
      sBtlPlayerSetTuugiZokusei(v46);
      break;
    default:
      break;
  }
  DeleteAll_Skill();
  sBtlPlayerDeleteFootEff();
  sBtlPlayerClrAllUnit_HitBack();
  BS_MATORY_DELETE();
  v52 = gSklID;
  wk->actwk->use_skillid = v52;
  sBtlSetSetsuma_SkillStart(wk, v52);
  wk->mode = 28;
  v56 = get_Instance(0);
  bloomCtrl = v56;
  gStartWaitCnt = 0;
  return 2;
}

// 0x20f24c0
static ATRB GetWeak(void) {
  s64 v1;
  s32 v2;
  s32 v3;
  s32 v4;
  s32 v5;
  s32 v6;
  u32 v7;
  s32 v8;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;
  s32 v13;
  s32 v14;
  _BOOL4 v16;
  u32 v17;
  s32 v18;
  u32 v19;
  s32 v20;
  s32 v21;
  u32 v22;
  s32 v23;
  s32 v24;
  u32 v25;
  s32 v26;
  bool *v27;
  s64 v28;
  u8 *v29;
  s32 v30;
  s32 v31;
  s32 a_pHanshaType;

  v1 = 0;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  a_pHanshaType = 0;
  v5 = 0;
  v6 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (!pUnit)
      goto LABEL_9;
    if ((pUnit->side & 2) == 0)
      goto LABEL_9;
    devilid = (u16)pUnit->para->devilid;
    if ((s16)devilid <= 290)
      v13 = 267;
    else
      v13 = 297;
    if ((s16)devilid <= 290)
      v14 = 290;
    else
      v14 = 310;
    v16 = devilid == v13 || devilid == v14;
    if (((v16 | sBtlCheckDamageTarget(pUnit)) & 1) == 0)
      goto LABEL_9;
    if (pUnit->para->devilid == 315)
    {
      pUnit = sBtlGetUnitFromDevilID(260);
    }
    a_pHanshaType = 0;
    v17 = sBtlCheckAisyoEx(pUnit, 4u, &a_pHanshaType);
    a_pHanshaType = 0;
    v18 = ((v17 >> 14) & 1) + v6 + ((s32)(v17 << 19) >> 31);
    if ((v17 & 0x2000) != 0)
      v18 -= 100;
    if ((v17 & 0x10000) != 0)
      v6 = v18 - 100;
    else
      v6 = v18;
    v19 = sBtlCheckAisyoEx(pUnit, 8u, &a_pHanshaType);
    v20 = ((v19 >> 14) & 1) + v5 + ((s32)(v19 << 19) >> 31);
    if ((v19 & 0x2000) != 0)
      v20 -= 100;
    if ((v19 & 0x10000) != 0)
      v5 = v20 - 100;
    else
      v5 = v20;
    v21 = (u16)pUnit->para->devilid;
    if (v21 == 310 || v21 == 267)
      v5 += 2;
    a_pHanshaType = 0;
    v22 = sBtlCheckAisyoEx(pUnit, 0x10u, &a_pHanshaType);
    v23 = ((v22 >> 14) & 1) + v4 + ((s32)(v22 << 19) >> 31);
    if ((v22 & 0x2000) != 0)
      v23 -= 100;
    if ((v22 & 0x10000) != 0)
      v4 = v23 - 100;
    else
      v4 = v23;
    v24 = (u16)pUnit->para->devilid;
    if (v24 == 297 || v24 == 290)
      v4 += 2;
    a_pHanshaType = 0;
    v25 = sBtlCheckAisyoEx(pUnit, 0x20u, &a_pHanshaType);
    a_pHanshaType = 0;
    v26 = ((v25 >> 14) & 1) + v3 + ((s32)(v25 << 19) >> 31);
    if ((v25 & 0x2000) != 0)
      v26 -= 100;
    if ((v25 & 0x10000) != 0)
      v3 = v26 - 100;
    else
      v3 = v26;
    v7 = sBtlCheckAisyoEx(pUnit, 0x40u, &a_pHanshaType);
    v8 = ((v7 >> 14) & 1) + v2 + ((s32)(v7 << 19) >> 31);
    if ((v7 & 0x2000) != 0)
      v8 -= 100;
    if ((v7 & 0x10000) != 0)
      v2 = v8 - 100;
    else
      v2 = v8;
LABEL_9:
    ++v1;
  }
  v27 = NewSpecific(bool, 5u);
  v28 = 0;
  v27[4] = 0;
  *(u32 *)&v27[0] = 0;
  v29 = &v27[0];
  if (v6 >= v5 && v6 >= v4 && v6 >= v3 && v6 >= v2)
  {
    v28 = 1;
    *v29 = 1;
  }
  if (v5 >= v6 && v5 >= v4 && v5 >= v3 && v5 >= v2)
  {
    v28 = (u32)(v28 + 1);
    v27[1] = 1;
  }
  if (v4 >= v6 && v4 >= v5 && v4 >= v3 && v4 >= v2)
  {
    v28 = (u32)(v28 + 1);
    v27[2] = 1;
  }
  if (v3 >= v6 && v3 >= v5 && v3 >= v4 && v3 >= v2)
  {
    v28 = (u32)(v28 + 1);
    v27[3] = 1;
  }
  if (v2 >= v6 && v2 >= v5 && v2 >= v4 && v2 >= v3)
  {
    v28 = (u32)(v28 + 1);
    v27[4] = 1;
  }
  v30 = sub_1905740(v28, 0);
  v31 = (u8)*v29;
  if (*v29)
  {
    if (v30)
    {
      v31 = 1;
      goto LABEL_102;
    }
    return 4;
  }
  else
  {
LABEL_102:
    if (v27[1])
    {
      if (v31 == v30)
        return 8;
      ++v31;
    }
    if (v27[2])
    {
      if (v31 == v30)
        return 16;
      ++v31;
    }
    if (v31 != v30 || v27[3] == 0)
      return 64;
    else
      return 32;
  }
}

// 0x20f30b0
void sBtlPlayerBgnWaitALL_Spirit(SBTLUNIT_WORK *wk, bool is_setuma) {
  s64 v5;
  bool v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 flg;
  SBTLEFF_LISTWORK *effList;
  SBTLDMG_HITLISTWORK *hitList;
  sdatUnitWork_t *v18;
  u32 v19;
  _BOOL4 v21;
  sdatUnitWork_t *v22;
  s32 v23;
  char v26;
  _BOOL4 v27;
  sdatUnitWork_t *v28;
  s32 devilid;
  struct sBtlPlayer_Spirit *static_fields;
  SBTLACTAI_WORK *actaiwk;
  s32 mode;
  SBTLAI_WORK *aiwk;
  SBTLACTION_WORK *actwk;
  char v41;
  struct sBtlPlayer_Spirit *v42;
  SBTLACTION_WORK *v43;
  s32 status;
  bool v46;
  SBTLACTAI_WORK *v47;
  s32 stat;
  s32 v49;
  SBTLAI_WORK *v50;
  s32 v51;

  v5 = 0;
  v6 = is_setuma;
  gEnd_BS_MUNAKA_Init_Imad_Kotei = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v5 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v5]->pUnit;
    if (!pUnit)
      goto LABEL_11;
    if ((pUnit->side & 2) != 0)
    {
      sBtlEnemyPush(pUnit, v6);
      para = pUnit->para;
      BadStatus = sBtlGetBadStatus(para);
      if (!sBtlCheckDamageTarget(pUnit))
        goto LABEL_32;
      if (BadStatus > 0x11 || ((1 << BadStatus) & 0x21040) == 0)
      {
        v28 = pUnit->para;
        if (v28->now->hp >= 1)
        {
          devilid = v28->devilid;
          if (sBtlGetAITBL(devilid, pUnit)->scr_no)
          {
            if (pUnit->actwk->use_skillid == 1549)
            {
              wk_BS_MUNAKA_Init_Imad_Restart = pUnit;
              static_fields = ((char *)static_fields + 40);
              *((u8 *)&static_fields[-1].gStartWaitCnt + 5) = 1;
              actaiwk = pUnit->actaiwk;
              pUnit->bk_action_use = 1;
              pUnit->bk_cmbret_mot_Locked = 1;
              pUnit->bk_action_actaiwk_stat = actaiwk->stat;
              mode = actaiwk->mode;
              LODWORD(actaiwk) = actaiwk->cmpframe;
              pUnit->bk_action_actaiwk_mode = mode;
              aiwk = pUnit->aiwk;
              pUnit->bk_action_actaiwk_cmpframe = (s32)actaiwk;
              LODWORD(actaiwk) = aiwk->stat;
              LODWORD(aiwk) = aiwk->mode;
              pUnit->bk_action_aiwk_stat = (s32)actaiwk;
              actwk = pUnit->actwk;
              pUnit->bk_action_aiwk_mode = (s32)aiwk;
              LODWORD(aiwk) = actwk->status;
              pUnit->bk_action_actwk_use_skillid = actwk->use_skillid;
              LOBYTE(actwk) = BYTE2(pUnit->status);
              pUnit->bk_action_status = (s32)aiwk;
              if (((u8)actwk & 8) != 0)
              {
                gEnd_BS_MUNAKA_Init_Imad_Kotei = 1;
              }
            }
            else
            {
              wk_BS_MUNAKA_Init_Imad_Restart = 0;
              v42 = ((char *)v42 + 40);
              *((u8 *)&v42[-1].gStartWaitCnt + 5) = 0;
            }
            v43 = pUnit->actwk;
            if (v43->use_skillid == 1548 && (pUnit->status & 0x80000) != 0)
            {
              v43 = pUnit->actwk;
              gEnd_BS_MUNAKA_Init_Imad_Kotei = 1;
            }
            status = v43->status;
            v46 = status == 6 || status == 3;
            if (v46 && !v43->action_flg)
            {
              v47 = pUnit->actaiwk;
              pUnit->bk_action_status = status;
              pUnit->bk_action_use = 1;
              stat = v47->stat;
              v49 = v47->mode;
              LODWORD(v47) = v47->cmpframe;
              pUnit->bk_action_actwk_use_skillid = v43->use_skillid;
              pUnit->bk_cmbret_mot_Locked = 1;
              pUnit->bk_action_actaiwk_stat = stat;
              v50 = pUnit->aiwk;
              pUnit->bk_action_actaiwk_mode = v49;
              pUnit->bk_action_actaiwk_cmpframe = (s32)v47;
              v51 = v50->stat;
              LODWORD(v50) = v50->mode;
              pUnit->bk_action_aiwk_stat = v51;
              pUnit->bk_action_aiwk_mode = (s32)v50;
            }
          }
        }
      }
    }
LABEL_32:
    flg = pUnit->flg;
    pUnit->damagecnt = 0;
    pUnit->flg = flg & 0xFFFFF7FF;
    if ((pUnit->side & 2) != 0)
    {
      effList = wk->effList;
      sBtlForceReset(effList, pUnit);
      hitList = wk->hitList;
      sBtlClearHitC(hitList, pUnit);
      v18 = pUnit->para;
      v19 = sBtlGetBadStatus(v18);
      if (!sBtlCheckDamageTarget(pUnit))
        goto LABEL_49;
      if (v19 > 0x11 || ((1 << v19) & 0x21040) == 0)
      {
        v21 = (pUnit->hstatus & 0x10) == 0 && v19 != 13;
        v22 = pUnit->para;
        v23 = v22->devilid;
        if ((u32)(v23 - 259) < 2)
          goto LABEL_92;
LABEL_50:
        if (v23 == 257)
        {
          v27 = (wk->actwk->use_skillid & 0xFFFFFFFE) != 0x526 && v21;
          if (!v21)
            goto LABEL_10;
          v21 = v27;
        }
        else
        {
          if (v23 != 258)
          {
            if (!v21)
              goto LABEL_10;
            goto LABEL_97;
          }
          if (v19 <= 0x11 && ((1 << v19) & 0x21040) != 0)
            goto LABEL_96;
          v26 = (pUnit->hstatus & 0x10) == 0 && v19 != 13 || v21;
          if ((v26 & 1) == 0)
            goto LABEL_10;
        }
        if (v22->now->hp < 1)
          goto LABEL_10;
      }
      else
      {
LABEL_49:
        v21 = 0;
        v22 = pUnit->para;
        v23 = v22->devilid;
        if ((u32)(v23 - 259) >= 2)
          goto LABEL_50;
LABEL_92:
        if (v19 <= 0x11 && ((1 << v19) & 0x21040) != 0)
        {
LABEL_96:
          if (v21)
            goto LABEL_97;
LABEL_10:
          pUnit->aiwk->bWait = 1;
          goto LABEL_11;
        }
        v41 = (pUnit->hstatus & 0x10) == 0 && v19 != 13 || v21;
        if ((v41 & 1) == 0)
          goto LABEL_10;
LABEL_97:
        v21 = 1;
        if (v22->now->hp < 1)
          goto LABEL_10;
      }
      sBtlEndAction(pUnit);
      sBtlResetAAI(pUnit);
      sBtlResetMode(pUnit);
      sBtlZakoWarpReset(pUnit);
      sBtlSetAction(pUnit, 1, 0);
      if (v21)
      {
        sBtlSetMotion(pUnit, 0, 0, 0, 0);
      }
      pUnit->actwk->use_skillid = 0;
      pUnit->aiwk->mode = 12;
      pUnit->actaiwk->stat = 1;
      ResetAction(pUnit, 0, 0);
      goto LABEL_10;
    }
LABEL_11:
    ++v5;
  }
}

// 0x20f37a0
void sBtlPlayerClrAllUnit_HitBack(void) {
  s64 v1;
  s32 vstatus;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  dds3Basic_t *pBasic;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      pBasic = pUnit->pBasic;
      if (pBasic)
      {
        dds3UnitObjectBasicSetDamageYure(pBasic, 0.0);
      }
      vstatus = pUnit->vstatus;
      pUnit->yure = 0;
      pUnit->hitlight_cnt = 0;
      pUnit->vstatus = vstatus & 0xFFFFF7FF;
    }
    ++v1;
  }
}

// 0x20f38d0
void sBtlPlayerSetEnemyPos(s32 _NewPosMode) {
  SBTLUNIT_WORK *PChara;
  _OWORD *p_x;
  __int128 v7;
  __int128 v8;
  __int128 v9;
  struct sdfVector4_t pos;
  s32 tateHitCnt;
  s32 v15;
  f32 v16;
  s64 v17;
  f32 v23;
  SBATTLE_WORK *wk_local;
  s32 v26;
  SBTLUNIT_WORK *v27;
  u32 status;
  u32 v29;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  __int128 v67;
  _OWORD *v68;
  s32 v69;
  __int128 v70;
  s64 v71;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 per;
  f32 Radian;
  f32 v84;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  u32 v93;
  u64 v94;
  f32 v95;
  struct sdfVector4_t rot;
  f32 v99;
  sdfMatrix4_t v100;
  sdfMatrix4_t v101;
  sdfMatrix4_t v102;
  sdfVector4_t v103;
  sdfVector4_t v104;
  sdfVector4_t v106;
  sdfVector4_t v107;

  memset(&v100, 0, sizeof(v100));
  PChara = sBtlGetPChara();
  rot = PChara->rot;
  vct_A = rot;
  ToMatrix();
  p_x = &vf00.x;
  v7 = p_x[5];
  v8 = p_x[6];
  v9 = p_x[7];
  *(_OWORD *)&v100.m00 = p_x[4];
  *(_OWORD *)&v100.m01 = v7;
  pos = PChara->pos;
  *(_OWORD *)&v100.m02 = v8;
  *(_OWORD *)&v100.m03 = v9;
  vct_A = pos;
  GetColumn(&v100, 3, 0);
  SetColumn(&v100, 3, vct_A, 0);
  set_Item_60922352(&v100, 15, 1.0, 0);
  tateHitCnt = wk->tateHitCnt;
  goto LABEL_14;
  if (!NewPosMode)
  {
LABEL_193:
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        goto LABEL_27;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) != 0)
      {
        pUnit->bOldNotHitDmg = (pUnit->status & 0x4000) != 0;
        sBtlStatusBitOn(pUnit, 0x4000u);
      }
    }
  }
  goto LABEL_27;
LABEL_14:
  v15 = tateHitCnt + 1;
  gEnemyNum = 0;
  if (!NewPosMode)
    goto LABEL_193;
LABEL_27:
  v16 = 0.5;
  v17 = 32;
  v94 = 0;
  v95 = 0.0;
  __asm { FMOV            V0.2S, #1.0 }
  v93 = HIDWORD(_D0);
  v23 = -3.1415927 / (f32)v15;
  do
  {
    wk_local = wk;
    v26 = *(u32 *)((char *)&wk_local->aTateHitID->obj.klass + v17);
    if (!v26)
      goto LABEL_31;
    v27 = wk_local->UnitMng->pUnitL[v26]->pUnit;
    if (v27)
    {
      status = v27->status;
      if ((status & 0x80000) != 0)
        v29 = status & 0xFFF7FF7F | 0x80;
      else
        v29 = status | 0x80;
      v27->status = v29;
      ++gEnemyNum;
      switch (NewPosMode)
      {
        case 0:
          v31 = (f32)(v23 + 1.5708) * 0.15915494;
          v32 = (s32)v31;
          if (v31 == INFINITY)
            v32 = -2147500000.0;
          v33 = v31 - v32;
          if (v33 <= v16)
          {
            if (v33 >= -0.5)
            {
              if (v33 <= 0.25)
                goto LABEL_50;
            }
            else
            {
              v33 = v33 + 1.0;
              if (v33 <= 0.25)
                goto LABEL_50;
            }
          }
          else
          {
            v33 = v33 + -1.0;
            if (v33 <= 0.25)
            {
LABEL_50:
              if (v33 < -0.25)
                v33 = -0.5 - v33;
LABEL_81:
              v46 = (s32)(v23 * 0.15915494);
              if ((f32)(v23 * 0.15915494) == INFINITY)
                v46 = -2147500000.0;
              v47 = (f32)(v23 * 0.15915494) - v46;
              if (v47 <= v16)
              {
                if (v47 >= -0.5)
                {
                  if (v47 <= 0.25)
                    goto LABEL_85;
                }
                else
                {
                  v47 = v47 + 1.0;
                  if (v47 <= 0.25)
                    goto LABEL_85;
                }
              }
              else
              {
                v47 = v47 + -1.0;
                if (v47 <= 0.25)
                {
LABEL_85:
                  if (v47 < -0.25)
                    v47 = -0.5 - v47;
                  goto LABEL_136;
                }
              }
              v47 = v16 - v47;
LABEL_136:
              v53 = v33 * 4.0;
              v95 = (f32)((f32)((f32)((f32)((f32)(v53 * 1.5708) + (f32)((f32)(v53 * (f32)(v53 * v53)) * -0.6459637)) + (f32)((f32)((f32)(v53 * v53) * (f32)(v53 * (f32)(v53 * v53))) * 0.07968968)) + (f32)((f32)((f32)(v53 * v53) * (f32)((f32)(v53 * v53) * (f32)(v53 * (f32)(v53 * v53)))) * -0.0046737655)) + (f32)((f32)((f32)(v53 * v53) * (f32)((f32)(v53 * v53) * (f32)((f32)(v53 * v53) * (f32)(v53 * (f32)(v53 * v53))))) * 0.00015148419))
                  * 250.0;
              v54 = v47 * 4.0;
              v55 = (f32)((f32)((f32)((f32)((f32)(v54 * 1.5708) + (f32)((f32)(v54 * (f32)(v54 * v54)) * -0.6459637)) + (f32)((f32)((f32)(v54 * v54) * (f32)(v54 * (f32)(v54 * v54))) * 0.07968968)) + (f32)((f32)((f32)(v54 * v54) * (f32)((f32)(v54 * v54) * (f32)(v54 * (f32)(v54 * v54)))) * -0.0046737655)) + (f32)((f32)((f32)(v54 * v54) * (f32)((f32)(v54 * v54) * (f32)((f32)(v54 * v54) * (f32)(v54 * (f32)(v54 * v54))))) * 0.00015148419))
                  * 250.0;
              goto LABEL_162;
            }
          }
          v33 = v16 - v33;
          goto LABEL_81;
        case 1:
          v34 = (f32)(v23 + 1.5708) * 0.15915494;
          v35 = (s32)v34;
          if (v34 == INFINITY)
            v35 = -2147500000.0;
          v36 = v34 - v35;
          if (v36 <= v16)
          {
            if (v36 >= -0.5)
            {
              if (v36 > 0.25)
              {
LABEL_91:
                v36 = v16 - v36;
                goto LABEL_92;
              }
            }
            else
            {
              v36 = v36 + 1.0;
              if (v36 > 0.25)
                goto LABEL_91;
            }
          }
          else
          {
            v36 = v36 + -1.0;
            if (v36 > 0.25)
              goto LABEL_91;
          }
          if (v36 < -0.25)
            v36 = -0.5 - v36;
LABEL_92:
          v48 = (s32)(v23 * 0.15915494);
          if ((f32)(v23 * 0.15915494) == INFINITY)
            v48 = -2147500000.0;
          v49 = (f32)(v23 * 0.15915494) - v48;
          if (v49 <= v16)
          {
            if (v49 >= -0.5)
            {
              if (v49 > 0.25)
              {
LABEL_141:
                v49 = v16 - v49;
                goto LABEL_142;
              }
            }
            else
            {
              v49 = v49 + 1.0;
              if (v49 > 0.25)
                goto LABEL_141;
            }
          }
          else
          {
            v49 = v49 + -1.0;
            if (v49 > 0.25)
              goto LABEL_141;
          }
          if (v49 < -0.25)
            v49 = -0.5 - v49;
LABEL_142:
          v56 = 4.0;
          v57 = v36 * 4.0;
          v58 = (f32)((f32)((f32)((f32)(v57 * 1.5708) + (f32)((f32)(v57 * (f32)(v57 * v57)) * -0.6459637)) + (f32)((f32)((f32)(v57 * v57) * (f32)(v57 * (f32)(v57 * v57))) * 0.07968968)) + (f32)((f32)((f32)(v57 * v57) * (f32)((f32)(v57 * v57) * (f32)(v57 * (f32)(v57 * v57)))) * -0.0046737655))
              + (f32)((f32)((f32)(v57 * v57) * (f32)((f32)(v57 * v57) * (f32)((f32)(v57 * v57) * (f32)(v57 * (f32)(v57 * v57))))) * 0.00015148419);
          v59 = -500.0;
          goto LABEL_161;
        case 2:
          v37 = (f32)(v23 + 1.5708) * 0.15915494;
          v38 = (s32)v37;
          if (v37 == INFINITY)
            v38 = -2147500000.0;
          v39 = v37 - v38;
          if (v39 <= v16)
          {
            if (v39 >= -0.5)
            {
              if (v39 > 0.25)
              {
LABEL_102:
                v39 = v16 - v39;
                goto LABEL_103;
              }
            }
            else
            {
              v39 = v39 + 1.0;
              if (v39 > 0.25)
                goto LABEL_102;
            }
          }
          else
          {
            v39 = v39 + -1.0;
            if (v39 > 0.25)
              goto LABEL_102;
          }
          if (v39 < -0.25)
            v39 = -0.5 - v39;
LABEL_103:
          v50 = (s32)(v23 * 0.15915494);
          if ((f32)(v23 * 0.15915494) == INFINITY)
            v50 = -2147500000.0;
          v49 = (f32)(v23 * 0.15915494) - v50;
          if (v49 <= v16)
          {
            if (v49 >= -0.5)
            {
              if (v49 > 0.25)
              {
LABEL_147:
                v49 = v16 - v49;
                goto LABEL_148;
              }
            }
            else
            {
              v49 = v49 + 1.0;
              if (v49 > 0.25)
                goto LABEL_147;
            }
          }
          else
          {
            v49 = v49 + -1.0;
            if (v49 > 0.25)
              goto LABEL_147;
          }
          if (v49 < -0.25)
            v49 = -0.5 - v49;
LABEL_148:
          v56 = 4.0;
          v60 = v39 * 4.0;
          v58 = (f32)((f32)((f32)((f32)(v60 * 1.5708) + (f32)((f32)(v60 * (f32)(v60 * v60)) * -0.6459637)) + (f32)((f32)((f32)(v60 * v60) * (f32)(v60 * (f32)(v60 * v60))) * 0.07968968)) + (f32)((f32)((f32)(v60 * v60) * (f32)((f32)(v60 * v60) * (f32)(v60 * (f32)(v60 * v60)))) * -0.0046737655))
              + (f32)((f32)((f32)(v60 * v60) * (f32)((f32)(v60 * v60) * (f32)((f32)(v60 * v60) * (f32)(v60 * (f32)(v60 * v60))))) * 0.00015148419);
          v59 = -1300.0;
          goto LABEL_161;
        case 3:
          v40 = (f32)(v23 + 1.5708) * 0.15915494;
          v41 = (s32)v40;
          if (v40 == INFINITY)
            v41 = -2147500000.0;
          v42 = v40 - v41;
          if (v42 <= v16)
          {
            if (v42 >= -0.5)
            {
              if (v42 > 0.25)
              {
LABEL_113:
                v42 = v16 - v42;
                goto LABEL_114;
              }
            }
            else
            {
              v42 = v42 + 1.0;
              if (v42 > 0.25)
                goto LABEL_113;
            }
          }
          else
          {
            v42 = v42 + -1.0;
            if (v42 > 0.25)
              goto LABEL_113;
          }
          if (v42 < -0.25)
            v42 = -0.5 - v42;
LABEL_114:
          v51 = (s32)(v23 * 0.15915494);
          if ((f32)(v23 * 0.15915494) == INFINITY)
            v51 = -2147500000.0;
          v49 = (f32)(v23 * 0.15915494) - v51;
          if (v49 <= v16)
          {
            if (v49 >= -0.5)
            {
              if (v49 > 0.25)
              {
LABEL_153:
                v49 = v16 - v49;
                goto LABEL_154;
              }
            }
            else
            {
              v49 = v49 + 1.0;
              if (v49 > 0.25)
                goto LABEL_153;
            }
          }
          else
          {
            v49 = v49 + -1.0;
            if (v49 > 0.25)
              goto LABEL_153;
          }
          if (v49 < -0.25)
            v49 = -0.5 - v49;
LABEL_154:
          v56 = 4.0;
          v61 = v42 * 4.0;
          v58 = (f32)((f32)((f32)((f32)(v61 * 1.5708) + (f32)((f32)(v61 * (f32)(v61 * v61)) * -0.6459637)) + (f32)((f32)((f32)(v61 * v61) * (f32)(v61 * (f32)(v61 * v61))) * 0.07968968)) + (f32)((f32)((f32)(v61 * v61) * (f32)((f32)(v61 * v61) * (f32)(v61 * (f32)(v61 * v61)))) * -0.0046737655))
              + (f32)((f32)((f32)(v61 * v61) * (f32)((f32)(v61 * v61) * (f32)((f32)(v61 * v61) * (f32)(v61 * (f32)(v61 * v61))))) * 0.00015148419);
          v59 = -150.0;
          goto LABEL_161;
        case 4:
          v43 = (f32)(v23 + 1.5708) * 0.15915494;
          v44 = (s32)v43;
          if (v43 == INFINITY)
            v44 = -2147500000.0;
          v45 = v43 - v44;
          if (v45 <= v16)
          {
            if (v45 >= -0.5)
            {
              if (v45 > 0.25)
              {
LABEL_124:
                v45 = v16 - v45;
                goto LABEL_125;
              }
            }
            else
            {
              v45 = v45 + 1.0;
              if (v45 > 0.25)
                goto LABEL_124;
            }
          }
          else
          {
            v45 = v45 + -1.0;
            if (v45 > 0.25)
              goto LABEL_124;
          }
          if (v45 < -0.25)
            v45 = -0.5 - v45;
LABEL_125:
          v52 = (s32)(v23 * 0.15915494);
          if ((f32)(v23 * 0.15915494) == INFINITY)
            v52 = -2147500000.0;
          v49 = (f32)(v23 * 0.15915494) - v52;
          if (v49 <= v16)
          {
            if (v49 >= -0.5)
            {
              if (v49 > 0.25)
              {
LABEL_159:
                v49 = v16 - v49;
                goto LABEL_160;
              }
            }
            else
            {
              v49 = v49 + 1.0;
              if (v49 > 0.25)
                goto LABEL_159;
            }
          }
          else
          {
            v49 = v49 + -1.0;
            if (v49 > 0.25)
              goto LABEL_159;
          }
          if (v49 < -0.25)
            v49 = -0.5 - v49;
LABEL_160:
          v56 = 4.0;
          v62 = v45 * 4.0;
          v58 = (f32)((f32)((f32)((f32)(v62 * 1.5708) + (f32)((f32)(v62 * (f32)(v62 * v62)) * -0.6459637)) + (f32)((f32)((f32)(v62 * v62) * (f32)(v62 * (f32)(v62 * v62))) * 0.07968968)) + (f32)((f32)((f32)(v62 * v62) * (f32)((f32)(v62 * v62) * (f32)(v62 * (f32)(v62 * v62)))) * -0.0046737655))
              + (f32)((f32)((f32)(v62 * v62) * (f32)((f32)(v62 * v62) * (f32)((f32)(v62 * v62) * (f32)(v62 * (f32)(v62 * v62))))) * 0.00015148419);
          v59 = -800.0;
LABEL_161:
          v95 = v58 * 600.0;
          v63 = v49 * v56;
          v55 = (f32)((f32)((f32)((f32)((f32)((f32)(v63 * 1.5708) + (f32)((f32)(v63 * (f32)(v63 * v63)) * -0.6459637)) + (f32)((f32)((f32)(v63 * v63) * (f32)(v63 * (f32)(v63 * v63))) * 0.07968968)) + (f32)((f32)((f32)(v63 * v63) * (f32)((f32)(v63 * v63) * (f32)(v63 * (f32)(v63 * v63)))) * -0.0046737655)) + (f32)((f32)((f32)(v63 * v63) * (f32)((f32)(v63 * v63) * (f32)((f32)(v63 * v63) * (f32)(v63 * (f32)(v63 * v63))))) * 0.00015148419)) * 600.0)
              + v59;
LABEL_162:
          v94 = __PAIR64__(v93, LODWORD(v55));
LABEL_163:
          vct_A.y = 0.0;
          vct_A.x = v95;
          *(u64 *)&vct_A.z = v94;
          *(_OWORD *)&v102.m00 = *(_OWORD *)&v100.m00;
          *(_OWORD *)&v102.m01 = *(_OWORD *)&v100.m01;
          *(_OWORD *)&v102.m02 = *(_OWORD *)&v100.m02;
          *(_OWORD *)&v102.m03 = *(_OWORD *)&v100.m03;
          v67 = *(_OWORD *)&v102.m01;
          v68 = &vf00.x;
          v69 = (u8)byte_5756085;
          v68[4] = *(_OWORD *)&v102.m00;
          v68[5] = v67;
          v70 = *(_OWORD *)&v102.m03;
          v68[6] = *(_OWORD *)&v102.m02;
          v68[7] = v70;
          if (v69)
          {
            goto LABEL_170;
          }
          else
          {
            goto LABEL_170;
          }
LABEL_170:
          get_transpose(&v102, &mtx_A, 0);
          v101 = v102;
          v103 = op_Multiply_60923920(&v101, vct_A, 0);
          vct_A = v103;
          v99 = v23;
          v107 = v27->rot;
          v27->pos = vct_A;
          x = v27->pos.x;
          y = v27->pos.y;
          z = v27->pos.z;
          w = v27->pos.w;
          per = PChara->pos.x;
          v91 = v107.y;
          v92 = v107.x;
          v89 = v107.w;
          v90 = v107.z;
          v107.w = v89;
          v107.z = v90;
          v107.y = v91;
          v107.x = v92;
          v106.x = x;
          v106.y = y;
          v106.z = z;
          v106.w = w;
          *(u64 *)&v104.x = 0;
          *(u64 *)&v104.z = v71;
          Radian = sBtlGetRadian(v106, v107, v104, per);
          v16 = 0.5;
          v84 = v99;
          v27->rot = vct_A;
          sBtlAddUnitDeg(v27, Radian);
          v27->JumpOfsPos.y = 0.0;
          sBtlUpdateUnitJumpOfsPos(v27);
          v23 = (f32)(-3.1415927 / (f32)v15) + v84;
          if (!v27->bOldNotHitDmg)
          {
            sBtlStatusBitOff(v27, 0xFFFFBFFF);
          }
          break;
        default:
          goto LABEL_163;
      }
    }
LABEL_31:
    v17 += 4;
  }
  while (v17 != 96);
}

// 0x20f4ab0
void sBtlPlayerResetEnemyPos(void) {
  s64 i;
  SBTLUNIT_WORK *pUnit;
  u32 status;
  s64 j;
  s32 flg;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v9;

  sBtlGetPChara();
  for (i = 32; i != 96; i += 4)
  {
    if (!*(u32 *)((char *)&wk->aTateHitID->obj.klass + i))
      continue;
    pUnit = wk->UnitMng->pUnitL[*(s32 *)((char *)&wk->aTateHitID->obj.klass + i)]->pUnit;
    if (pUnit)
    {
      status = pUnit->status;
      pUnit->JumpOfsPos.y = 0.0;
      pUnit->status = (*(u32 *)((char *)&wk->aTateHitFlg->obj.klass + i) | status)
                           & 0xFFFFFF7F
                           | (pUnit->bOldNotMapHit << 7);
    }
  }
  for (j = 0; ; ++j)
  {
    UnitMng = wk->UnitMng;
    if (j >= UnitMng->number)
      break;
    v9 = UnitMng->pUnitL[j]->pUnit;
    if (!v9)
      continue;
    if ((v9->side & 2) != 0 && !v9->bOldNotHitDmg)
    {
      sBtlStatusBitOff(v9, 0xFFFFBFFF);
      flg = v9->flg;
      v9->JumpOfsPos.y = 0.0;
      v9->flg = flg & 0xFFFFFEFF;
    }
  }
}

// 0x20f29e0
void sBtlPlayerPushAllPosRotDispHit(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 status;
  struct sdfVector4_t pos;
  s32 vstatus;
  struct sdfVector4_t v11;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (pUnit)
    {
      sBtlCalcAnim_DmgNumPos(pUnit, 0, &pUnit->vDmgPosBfrCmb);
      status = pUnit->status;
      pos = pUnit->pos;
      pUnit->bOldHitNone = status & 1;
      vstatus = pUnit->vstatus;
      pUnit->bOldNotMapHit = (status & 0x80) != 0;
      v11 = pos;
      pUnit->bOldDispOff = (vstatus & 0x1000) != 0;
      goto LABEL_17;
LABEL_18:
      vct_A = v11;
      goto LABEL_19;
LABEL_17:
      goto LABEL_18;
LABEL_19:
      pUnit->vPosBfrCmb = vct_A;
      pUnit->vRotBfrCmb = pUnit->rot;
      continue;
    }
  }
}

// 0x20f4cc0
void sBtlPlayerPopAllPosRotDispHit(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 v6;
  struct sdfVector4_t vRotBfrCmb;
  struct sdfVector4_t vPosBfrCmb;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      v6 = pUnit->status & 0xFFFFFF7E | pUnit->bOldHitNone | (pUnit->bOldNotMapHit << 7);
      vPosBfrCmb = pUnit->vPosBfrCmb;
      pUnit->vstatus = pUnit->vstatus & 0xFFFFEFFF | (pUnit->bOldDispOff << 12);
      pUnit->status = v6;
      vct_A = vPosBfrCmb;
      pUnit->JumpOfsPos.y = 0.0;
      pUnit->pos = vct_A;
      vRotBfrCmb = pUnit->vRotBfrCmb;
      pUnit->rot = vRotBfrCmb;
      pUnit->rotbk = vRotBfrCmb;
      sBtlUpdateUnitJumpOfsPos(pUnit);
    }
    ++v1;
  }
}

// 0x20f4f10
void sBtlPlayerResetPlayerPosRot_Start(void) {
  SBTLUNIT_WORK *PChara;
  SBATTLE_WORK *wk_local;
  f32 PlayerBtlStartDir;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rotbk;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v13;
  SBATTLE_WORK *v15;
  f32 *NakamaBtlStartPosY;
  f32 v17;
  f32 *NakamaBtlStartPosZ;
  f32 *NakamaBtlStartDir;
  f32 v20;
  sdfVector4_t *v22;
  sdfVector4_t *v23;
  struct sdfVector4_t v27;
  SBTLUNIT_WORK *v28;
  SBTLUNIT_WORK *v29;
  SBATTLE_WORK *v31;
  f32 *v32;
  f32 v33;
  f32 *v34;
  f32 *v35;
  f32 v36;
  sdfVector4_t *v38;
  sdfVector4_t *v39;
  struct sdfVector4_t v43;

  PChara = sBtlGetPChara();
  wk_local = wk;
  *(u64 *)&PChara->pos.x = *(u64 *)&wk_local->PlayerBtlStartPosX;
  PChara->pos.z = wk_local->PlayerBtlStartPosZ;
  PlayerBtlStartDir = wk_local->PlayerBtlStartDir;
  PChara->mv_rotbk = PlayerBtlStartDir;
  FromEuler(0.0, PlayerBtlStartDir * 0.017453292, 0.0);
  p_rot = &PChara->rot;
  *p_rot = vct_A;
  p_rotbk = &PChara->rotbk;
  PChara->JumpOfsPos.y = 0.0;
  *p_rotbk = vct_A;
  sBtlUpdateUnitJumpOfsPos(PChara);
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    v13 = Nakama;
    v15 = wk;
    NakamaBtlStartPosY = v15->NakamaBtlStartPosY;
    v13->pos.x = v15->NakamaBtlStartPosX[0];
    v17 = NakamaBtlStartPosY[0];
    NakamaBtlStartPosZ = v15->NakamaBtlStartPosZ;
    NakamaBtlStartDir = v15->NakamaBtlStartDir;
    v13->pos.y = v17;
    v13->pos.z = NakamaBtlStartPosZ[0];
    v20 = NakamaBtlStartDir[0];
    v13->mv_rotbk = v20;
    FromEuler(0.0, v20 * 0.017453292, 0.0);
    v22 = &v13->rot;
    *v22 = vct_A;
    v23 = &v13->rotbk;
    v27 = vct_A;
    v13->JumpOfsPos.y = 0.0;
    *v23 = v27;
    sBtlUpdateUnitJumpOfsPos(v13);
  }
  v28 = sBtlGetNakama(1);
  if (!v28)
    return;
  v29 = v28;
  v31 = wk;
  v32 = v31->NakamaBtlStartPosY;
  v29->pos.x = v31->NakamaBtlStartPosX[1];
  v33 = v32[1];
  v34 = v31->NakamaBtlStartPosZ;
  v35 = v31->NakamaBtlStartDir;
  v29->pos.y = v33;
  v29->pos.z = v34[1];
  v36 = v35[1];
  v29->mv_rotbk = v36;
  FromEuler(0.0, v36 * 0.017453292, 0.0);
  v38 = &v29->rot;
  *v38 = vct_A;
  v39 = &v29->rotbk;
  v43 = vct_A;
  v29->JumpOfsPos.y = 0.0;
  *v39 = v43;
  sBtlUpdateUnitJumpOfsPos(v29);
}

// 0x20f53f0
void sBtlPlayerResetPlayerPosRot_Start_Boss(s32 _Pattern) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  u32 status;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v12;
  SBTLAI_WORK *aiwk;
  SBTLACTAI_WORK *actaiwk;
  SBTLAI_WORK *v17;
  SBTLACTAI_WORK *v18;
  f32 CameraBtlStartX;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 *p_z;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  sdfVector4_t v54;
  sdfVector4_t v55;
  sdfVector4_t v56;
  sdfVector4_t v57;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  sBtlResetAction(v7);
  sBtlSetUseSkill(v7, 0, 0);
  sBtlSetAction(v7, 1, 0);
  sBtlSetMotion(v7, 130, 0, 0, 0);
  status = v7->status;
  v7->cmstatus = 0;
  v7->status = status & 0xFFFFFEFF;
  sBtlResetGunMode(v7, 0);
  sBtlResetCharge(v7, 0);
  sBtlResetJump(v7);
  v7->JumpAfterCnt = 0;
  sBtlPlayerCamMvReset(v7);
  sBtlResetMutekiColor(v7);
  DeleteAll_Skill();
  sBtlPlayerDeleteFootEff();
  sBtlPlayerClrAllUnit_HitBack();
  sBtlShugouKaijyo();
  Nakama = sBtlGetNakama(0);
  v12 = sBtlGetNakama(1);
  if (Nakama)
  {
    sBtlEndWait(Nakama);
  }
  if (v12)
  {
    sBtlEndWait(v12);
  }
  if (Nakama)
  {
    sBtlProc_YoyakuEndChk(Nakama);
    sBtlSetAction(Nakama, 1, 0);
    sBtlSetMotion(Nakama, 0, 0, 0, 0);
    aiwk = Nakama->aiwk;
    Nakama->actwk->use_skillid = 0;
    actaiwk = Nakama->actaiwk;
    aiwk->mode = 12;
    actaiwk->stat = 1;
    sBtlProc_YoyakuEnd(Nakama);
    sBtlResetAAI(Nakama);
    Nakama->aiwk->mode = 0;
    goto LABEL_33;
  }
LABEL_33:
  if (v12)
  {
    sBtlProc_YoyakuEndChk(v12);
    sBtlSetAction(v12, 1, 0);
    sBtlSetMotion(v12, 0, 0, 0, 0);
    v17 = v12->aiwk;
    v12->actwk->use_skillid = 0;
    v18 = v12->actaiwk;
    v17->mode = 12;
    v18->stat = 1;
    sBtlProc_YoyakuEnd(v12);
    sBtlResetAAI(v12);
    v12->aiwk->mode = 0;
  }
  sBtlPlayerResetPlayerPosRot_Start();
  CameraBtlStartX = wk->CameraBtlStartX;
  sBtlResetFollowUpAngleX(CameraBtlStartX);
  if (Pattern != 2)
  {
    if (Pattern == 1)
    {
      if (Nakama)
      {
        x = Nakama->rot.x;
        y = Nakama->rot.y;
        z = Nakama->rot.z;
        w = Nakama->rot.w;
        v54.x = x;
        v54.y = y;
        v54.z = z;
        v54.w = w;
        RotToDir = sBtlGetRotToDir(v54);
        v28 = sBtlGet360(RotToDir + -160.0);
        sBtlGetMoveXZ(Nakama->pos.x, Nakama->pos.z, v28, 500.0, &Nakama->pos.x, &Nakama->pos.z);
      }
      if (v12)
      {
        v29 = v12->rot.x;
        v30 = v12->rot.y;
        v32 = v12->rot.z;
        v31 = v12->rot.w;
        v55.x = v29;
        v55.y = v30;
        v55.z = v32;
        v55.w = v31;
        v33 = sBtlGetRotToDir(v55);
        v34 = sBtlGet360(v33 + 160.0);
        v36 = v12->pos.z;
        p_z = &v12->pos.z;
        v37 = v36;
        v38 = v34;
        v39 = 500.0;
LABEL_69:
        sBtlGetMoveXZ(*(p_z - 2), v37, v38, v39, p_z - 2, p_z);
        return;
      }
    }
    return;
  }
  if (Nakama)
  {
    v41 = Nakama->rot.x;
    v42 = Nakama->rot.y;
    v44 = Nakama->rot.z;
    v43 = Nakama->rot.w;
    v56.x = v41;
    v56.y = v42;
    v56.z = v44;
    v56.w = v43;
    v45 = sBtlGetRotToDir(v56);
    v46 = sBtlGet360(v45 + -90.0);
    sBtlGetMoveXZ(Nakama->pos.x, Nakama->pos.z, v46, 100.0, &Nakama->pos.x, &Nakama->pos.z);
  }
  if (v12)
  {
    v47 = v12->rot.x;
    v48 = v12->rot.y;
    v50 = v12->rot.z;
    v49 = v12->rot.w;
    v57.x = v47;
    v57.y = v48;
    v57.z = v50;
    v57.w = v49;
    v51 = sBtlGetRotToDir(v57);
    v52 = sBtlGet360(v51 + 90.0);
    v53 = v12->pos.z;
    p_z = &v12->pos.z;
    v37 = v53;
    v38 = v52;
    v39 = 100.0;
    goto LABEL_69;
  }
}

// 0x20f5c60
void sBtlPlayerResetEnemyPosRot_Start(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 enc_posid;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 2) != 0)
      {
        enc_posid = pUnit->enc_posid;
        if (enc_posid)
        {
          sBtlGetPointData(enc_posid, &pUnit->pos, &pUnit->rot);
          pUnit->rotbk = pUnit->rot;
        }
        pUnit->JumpOfsPos.y = 0.0;
        sBtlUpdateUnitJumpOfsPos(pUnit);
      }
    }
    ++v1;
  }
}

// 0x20f5b80
void sBtlPlayerResetCamera_Start(void) {
  f32 CameraBtlStartX;

  CameraBtlStartX = wk->CameraBtlStartX;
  sBtlResetFollowUpAngleX(CameraBtlStartX);
}

// 0x20f5dd0
void sBtlPlayerPopAllDispHit(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 status;
  s32 bOldNotMapHit;
  u32 v8;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      status = pUnit->status;
      pUnit->JumpOfsPos.y = 0.0;
      bOldNotMapHit = pUnit->bOldNotMapHit;
      v8 = status & 0xFFFFFF7E | pUnit->bOldHitNone;
      pUnit->vstatus = pUnit->vstatus & 0xFFFFEFFF | (pUnit->bOldDispOff << 12);
      pUnit->status = v8 | (bOldNotMapHit << 7);
      sBtlUpdateUnitJumpOfsPos(pUnit);
    }
    ++v1;
  }
}

// 0x20f5f20
void sBtlPlayerSetEnemyDrawOnOff(bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 j;
  SBTLUNIT_LISTWORK *v8;
  SBTLUNIT_WORK *v9;

  if (OnOff)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) != 0)
        pUnit->vstatus &= 0xFEFFEFFF;
    }
  }
  for (j = 0; ; ++j)
  {
    v8 = wk->UnitMng;
    if (j >= v8->number)
      break;
    v9 = v8->pUnitL[j]->pUnit;
    if (!v9)
      continue;
    if ((v9->side & 2) != 0)
      v9->vstatus |= 0x1001000u;
  }
}

// 0x20f60b0
void sBtlPlayerSetNakamaDrawOnOff(bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 j;
  SBTLUNIT_LISTWORK *v8;
  SBTLUNIT_WORK *v9;

  if (OnOff)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x81) == 1)
        pUnit->vstatus &= 0xFEFFEFFF;
    }
  }
  for (j = 0; ; ++j)
  {
    v8 = wk->UnitMng;
    if (j >= v8->number)
      break;
    v9 = v8->pUnitL[j]->pUnit;
    if (!v9)
      continue;
    if ((v9->side & 0x81) == 1)
      v9->vstatus |= 0x1001000u;
  }
}

// 0x20f6270
void sBtlPlayerSetEnemyNakamaDrawOnOff_ShadowBugPos(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 || (pUnit->side & 0x81) == 1)
    {
      if ((pUnit->vstatus & 0x1000) != 0)
      {
        pUnit->JumpOfsPos.y = 5000.0;
      }
      else
      {
        pUnit->JumpOfsPos.y = 0.0;
      }
      sBtlUpdateUnitJumpOfsPos(pUnit);
      continue;
    }
  }
}

// 0x20f63c0
void sBtlPlayerSetEnemyHPDrawOnOff(bool _OnOff) {
  void *Instance;

  Instance = get_Instance(0);
  DevilHPactive_Not_Stp_Num4(Instance, OnOff, 0);
}

// 0x20f6430
void sBtlPlayerSetNakamaHPDrawOnOff(bool _OnOff) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 j;
  SBTLUNIT_LISTWORK *v8;
  SBTLUNIT_WORK *v9;

  if (OnOff)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x81) == 1)
        pUnit->hstatus &= ~0x400000u;
    }
  }
  for (j = 0; ; ++j)
  {
    v8 = wk->UnitMng;
    if (j >= v8->number)
      break;
    v9 = v8->pUnitL[j]->pUnit;
    if (!v9)
      continue;
    if ((v9->side & 0x81) == 1)
      v9->hstatus |= 0x400000u;
  }
}

// 0x20f65d0
void sBtlPlayerSetTateHit(SBTLUNIT_WORK *pTgt) {
  s64 v7;
  sdfVector4_t *v9;
  s32 v10;
  struct sdfVector4_t rot;
  sdfVector4_t *avTateHitRot;
  s64 tateHitCnt;
  SBATTLE_WORK *v16;
  struct sdfVector4_t pos;
  struct sdfVector4_t v19;

  pos = pTgt->pos;
  vct_A = pos;
  v7 = (s64)wk->avTateHitPos + 16 * wk->tateHitCnt;
  v9 = (v7 + 32);
  v10 = (u8)byte_5755EF5;
  *v9 = vct_A;
  rot = pTgt->rot;
  if (!v10)
  {
    v19 = rot;
    rot = v19;
  }
  vct_A = rot;
  avTateHitRot = wk->avTateHitRot;
  tateHitCnt = wk->tateHitCnt;
  avTateHitRot[tateHitCnt] = vct_A;
  v16 = wk;
  v16->aTateHitID[v16->tateHitCnt] = pTgt->ListID;
  v16->aTateHitFlg[v16->tateHitCnt++] = pTgt->status;
}

// 0x20f2c10
void sBtlPlayerSetTateHitEnemy(void) {
  SBTLUNIT_WORK *PChara;
  SBATTLE_WORK *wk_local;
  s32 *v4;
  SBATTLE_WORK *v5;
  s32 *v6;
  _OWORD *p_x;
  __int128 v10;
  __int128 v11;
  __int128 v12;
  struct sdfVector4_t pos;
  s64 v16;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  char side;
  struct sdfVector4_t rot;
  sdfMatrix4_t v25;
  sdfVector4_t Column;

  memset(&v25, 0, sizeof(v25));
  PChara = sBtlGetPChara();
  wk_local = wk;
  v4 = NewSpecific(s32, 0x10u);
  wk_local->aTateHitID = v4;
  v5 = wk;
  v6 = NewSpecific(s32, 0x10u);
  v5->aTateHitFlg = v6;
  rot = PChara->rot;
  vct_A = rot;
  ToMatrix();
  p_x = &vf00.x;
  v10 = p_x[5];
  v11 = p_x[6];
  v12 = p_x[7];
  *(_OWORD *)&v25.m00 = p_x[4];
  *(_OWORD *)&v25.m01 = v10;
  pos = PChara->pos;
  *(_OWORD *)&v25.m02 = v11;
  *(_OWORD *)&v25.m03 = v12;
  vct_A = pos;
  GetColumn(&v25, 3, 0);
  SetColumn(&v25, 3, vct_A, 0);
  Column = GetColumn(&v25, 2, 0);
  vct_A = Column;
  v16 = 0;
  wk->tateHitCnt = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v16 >= UnitMng->number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[v16]->pUnit;
    sBtlEnemyPush(pUnit, 0);
    if (pUnit)
    {
      side = pUnit->side;
      pUnit->bOldScrWarp = 0;
      if ((side & 2) != 0)
      {
        if (((pUnit->aiwk->scrflag & 8) == 0 || (pUnit->bOldScrWarp = (pUnit->aiwk->scrflag & 8) != 0, Support_RunWarpProcess_Skip(pUnit), (pUnit->side & 2) != 0)) && (pUnit->status & 0x4004000) == 0 || pUnit->bOldScrWarp)
        {
          sBtlPlayerSetTateHit(pUnit);
        }
      }
    }
    ++v16;
  }
}

// 0x20f6880
bool sBtlPlayerChkAll_EnemySummonW(void) {
  char v2;
  s64 i;
  const char *namespaze;
  const char *v6;

  v2 = 0;
  for (i = 32; i != 416; i += 8)
  {
    namespaze = (*(Il2CppClass **)((char *)&wk->UnitMng->pUnitL->obj.klass + i))->_1.namespaze;
    if (namespaze && (namespaze[832] & 2) != 0 && !namespaze[2045])
      v2 |= *((u32 *)namespaze + 93) < 5;
  }
  return v2 & 1;
}

// 0x20f69a0
static void SetLightChg(void) {
  mapLightParam_t *v1;
  f32 v4;
  s32 v5;
  f32 v6;
  f32 v7;
  s64 v8;
  s64 v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  evtUnitHandle_t *hEveUnit;
  u32 v14;
  u32 v15;
  u32 v16;
  u32 v17;
  struct sdfVector4_t v19;
  struct sdfVector4_t v21;
  void *mBloom;
  void *mDof;
  void *Instance;
  void *threshold;
  void *v39;
  void *intensity;
  void *v41;
  void *scatter;
  void *v43;
  void *monitor;
  void *v45;
  void *v46;
  UnityEngine_Object_c *klass;
  void *v48;
  intptr_t m_CachedPtr;
  void *v50;
  void *v51;
  void *v52;
  struct sdfVector4_t v53;
  struct sdfVector4_t v57;

  v1 = Allocate(mapLightParam_t);
  _ctor(v1, 0);
  v1->rgb2 = 0x80000000;
  v1->rgb0 = -2139062144;
  v1->rgb1 = -2146430960;
  v1->rgba = -2146430960;
  *(_OWORD *)&v1->dir0 = xmmword_3D07C40;
  *(_OWORD *)&v1->dir1 = xmmword_3D01F70;
  *(_OWORD *)&v1->dir2 = xmmword_3D07470;
  v4 = 1.0;
  v5 = gSklID - 690;
  if ((u32)v5 > 0xB)
  {
    v6 = 1.0;
    v7 = 1.0;
  }
  else
  {
    v6 = 1.0;
    v7 = 1.0;
    if (((0xA67u >> (LOBYTE(gSklID) + 78)) & 1) != 0)
    {
      v8 = 4 * v5;
      v4 = *(f32 *)((char *)&unk_3E65398 + v8);
      v6 = *(f32 *)((char *)&unk_3E653C8 + v8);
      v7 = *(f32 *)((char *)&unk_3E653F8 + v8);
      v1->rgb0 = *(u32 *)((char *)&unk_3E65368 + v8);
    }
  }
  v9 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v9 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v9]->pUnit;
    if (pUnit)
    {
      hEveUnit = pUnit->hEveUnit;
      if (hEveUnit)
      {
        v14 = v1->rgb0;
        v15 = v1->rgb1;
        v16 = v1->rgb2;
        v17 = v1->rgba;
        pUnit->vstatus |= 0x10000000u;
        evtSetUnitLightAndAmbient3(hEveUnit, 0, v14, v15, v16, v17);
        v53 = v1->dir0;
        vct_A = v53;
        evtSetUnitLightDir(pUnit->hEveUnit, 0);
        v19 = v1->dir1;
        vct_A = v19;
        evtSetUnitLightDir1(pUnit->hEveUnit, 1);
        v21 = v1->dir2;
        v57 = v21;
        v21 = v57;
        vct_A = v21;
        evtSetUnitLightDir2(pUnit->hEveUnit, 2);
        evtSetUnitRim(pUnit->hEveUnit, v7, v6, v4, 1.0);
      }
    }
    ++v9;
  }
  _Off(MFilter, 0);
  if (!op_Inequality(bloomCtrl, 0, 0))
    goto LABEL_42;
  mBloom = bloomCtrl->mBloom;
  gBloomOw = mBloom;
  if (!op_Inequality(gBloomOw, 0, 0))
  {
    goto LABEL_52;
  }
  threshold = gBloomOw->threshold;
  v39 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v39, 0.7, 1, 0);
  (threshold->klass->vtable._8_SetValue.methodPtr)(threshold, v39, threshold->klass->vtable._8_SetValue.method);
  intensity = gBloomOw->intensity;
  v41 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v41, 3.0, 1, 0);
  (intensity->klass->vtable._8_SetValue.methodPtr)(intensity, v41, intensity->klass->vtable._8_SetValue.method);
  scatter = gBloomOw->scatter;
  v43 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v43, 0.4, 1, 0);
  (scatter->klass->vtable._8_SetValue.methodPtr)(scatter, v43, scatter->klass->vtable._8_SetValue.method);
LABEL_52:
  mDof = bloomCtrl->mDof;
  gDofOw = mDof;
  op_Inequality(gDofOw, 0, 0);
LABEL_42:
  if ((u32)(wk->encountno - 58) > 2)
    return;
  Instance = get_Instance(0);
  if (op_Inequality(Instance, 0, 0))
  {
    monitor = Instance[2].monitor;
    if (!op_Inequality(monitor, 0, 0))
      return;
    v45 = monitor[2].monitor;
    v46 = Allocate(UnityEngine_Rendering_Universal_DepthOfFieldModeParameter);
    _ctor(v46, 2, 1, 0);
    (*(*(u64 *)v45 + 440))(v45, v46, *(u64 *)(*(u64 *)v45 + 448));
    klass = monitor[4].klass;
    v48 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v48, 0.8, 1, 0);
    (*(klass->_1.image + 55))(klass, v48, *((u64 *)klass->_1.image + 56));
    m_CachedPtr = monitor[4].m_CachedPtr;
    v50 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v50, 50.0, 1, 0);
    (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v50, *(u64 *)(*(u64 *)m_CachedPtr + 448));
    v51 = monitor[4].monitor;
    v52 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v52, 18.0, 1, 0);
    (*(*(u64 *)v51 + 440))(v51, v52, *(u64 *)(*(u64 *)v51 + 448));
  }
}

// 0x20f7270
static void ResetLightChg(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  evtUnitHandle_t *hEveUnit;
  void *v13;
  void *mDof;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v1 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      hEveUnit = pUnit->hEveUnit;
      if (hEveUnit)
      {
        pUnit->vstatus &= ~0x10000000u;
        evtSetUnitRim(hEveUnit, 1.0, 1.0, 1.0, 1.0);
      }
    }
    ++v1;
  }
  _On(MFilter, 0);
  if (!op_Inequality(bloomCtrl, 0, 0))
    goto LABEL_21;
  RestoreBloomSetting(bloomCtrl, 0);
  RestoreDofSetting(bloomCtrl, 0);
LABEL_22:
  if ((u32)(wk->encountno - 58) > 2)
    return;
  v13 = bloomCtrl;
  if (!op_Inequality(v13, 0, 0))
    return;
  mDof = bloomCtrl->mDof;
  if (!op_Inequality(mDof, 0, 0))
  {
LABEL_37:
    SetForceActiveDofSetting(bloomCtrl, 0, 0);
    return;
  }
  RestoreDofSetting(bloomCtrl, 0);
  goto LABEL_37;
LABEL_21:
  goto LABEL_22;
}

// 0x20f7680
static void SetRndHitNum(s32 num, s32 frq) {
  _RNDHIT *rndHit;
  bool *v7;
  _RNDHIT *v8;

  rndHit = wk->rndHit;
  v7 = NewSpecific(bool, 0x10u);
  rndHit->abTateHit = v7;
  v8 = wk->rndHit;
  v8->num = num;
  v8->frq = frq;
  v8->cnt0 = frq;
  v8->cnt1 = 0;
  v8->bFrm = 0;
}

// 0x20f7750
static s32 _FakeRndHit(void) {
  s64 v2;
  s32 v3;
  SBATTLE_WORK *wk_local;

  v2 = 32;
  v3 = -1;
  while (1)
  {
    wk_local = wk;
    if (v2 - 32 >= wk_local->tateHitCnt)
      break;
    wk_local = wk;
    if (!*((u8 *)&wk_local->rndHit->abTateHit->obj.klass + v2++))
    {
      do
      {
        v3 = sub_1905740((u32)wk->tateHitCnt, 0);
      }
      while (wk->rndHit->abTateHit[v3]);
      return v3;
    }
  }
  return v3;
}

// 0x20f7860
static bool FakeRndHit(s32 qFrm, s32 qPow) {
  _RNDHIT *rndHit;
  _RNDHIT *v10;
  _RNDHIT *v11;
  s32 v14;
  _RNDHIT *v17;
  s32 v18;
  _RNDHIT *v20;

  rndHit = wk->rndHit;
  if (rndHit->bFrm)
  {
    if (rndHit->cnt1 != rndHit->frm)
      goto LABEL_16;
    return 0;
  }
  v10 = wk->rndHit;
  if (v10->cnt1 != v10->num)
    goto LABEL_16;
  return 0;
LABEL_16:
  v11 = wk->rndHit;
  if (v11->frq > v11->cnt0)
    goto LABEL_44;
  v14 = _FakeRndHit();
  if (v14 != -1)
    goto LABEL_34;
  v17 = wk->rndHit;
  if (!v17->bFrm)
  {
    v17 = wk->rndHit;
    v18 = v17->cnt1 + 1;
    v17->cnt1 = v18;
    if (v18 == v17->num)
      return 0;
  }
  v14 = _FakeRndHit();
  if (v14 == -1)
  {
LABEL_40:
    wk->rndHit->cnt0 = 0;
    if (qFrm)
    {
      dds3SetQuake(qFrm, qPow);
    }
    goto LABEL_44;
  }
LABEL_34:
  FakeDmgOne(v14);
  wk->rndHit->abTateHit[v14] = 1;
  goto LABEL_40;
LABEL_44:
  v20 = wk->rndHit;
  if (v20->bFrm)
  {
    v20 = wk->rndHit;
    ++v20->cnt1;
  }
  ++wk->rndHit->cnt0;
  return 1;
}

// 0x20f7c00
static void FakeDmgOne(s32 i) {
  SBTLUNIT_WORK *PChara;
  s32 v6;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 PosToDir;
  sdfVector4_t HitEffectPos;
  sdfVector4_t v19;

  PChara = sBtlGetPChara();
  v6 = wk->aTateHitID[i];
  if (!v6)
    return;
  pUnit = wk->UnitMng->pUnitL[v6]->pUnit;
  if (!pUnit)
    return;
  devilid = pUnit->para->devilid;
  if ((u32)(devilid - 258) >= 3 && (devilid & 0xFFFFFFFC) != 0x138)
  {
    if (pUnit->motion_setno != 11)
    {
      sBtlSetMotion(pUnit, 1, 0, 0, 0);
    }
    x = pUnit->pos.x;
    y = pUnit->pos.y;
    z = pUnit->pos.z;
    w = pUnit->pos.w;
    v19.x = x;
    v19.y = y;
    v19.z = z;
    v19.w = w;
    sBtlPlayDamageSE(v19, 2);
    v13 = pUnit->pos.x;
    v14 = pUnit->pos.z;
    v15 = PChara->pos.x;
    v16 = PChara->pos.z;
    PosToDir = sBtlGetPosToDir(v13, v14, v15, v16);
    HitEffectPos = sBtlGetHitEffectPos(149, pUnit, PChara);
    Add(pUnit->ListID, 149, HitEffectPos.x, HitEffectPos.y, HitEffectPos.z, PosToDir, 1.0, 0);
  }
}

// 0x20f7e90
bool sBtlPlayerDirectDmg(void) {
  SBTLUNIT_WORK *PChara;
  bool v3;
  s64 v4;
  s32 *aTateHitID;
  SBTLUNIT_WORK *pUnit;
  u64 v8;
  u32 devilid;
  SBTLUNIT_WORK *v10;
  s32 v11;
  sdfVector4_t *p_pos;
  SBTLDMG_HITWORK *v14;
  SBTLSKILLP_TBL *Skilltbl;
  s32 ListID;
  s32 v19;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdfVector4_t v25;

  PChara = sBtlGetPChara();
  v3 = 1;
  v4 = 8;
  {
    if (*((u32 *)&wk->aTateHitID->obj.klass + v4))
      goto LABEL_10;
LABEL_5:
    v8 = v4 - 8;
    ++v4;
    v3 = v8 < 0xF;
    if (v4 == 24)
      return v3;
  }
  if (!*((u32 *)&wk->aTateHitID->obj.klass + v4))
    goto LABEL_5;
LABEL_10:
  aTateHitID = wk->aTateHitID;
  pUnit = wk->UnitMng->pUnitL[*((s32 *)&aTateHitID->obj.klass + v4)]->pUnit;
  if (!pUnit)
    goto LABEL_5;
  devilid = (u16)pUnit->para->devilid;
  if (devilid > 0x138)
  {
    if (devilid != 313)
    {
      if (devilid != 314 || pUnit->ListID == 5)
        goto LABEL_34;
LABEL_23:
      goto LABEL_41;
    }
    v10 = wk->scrUnitList[0];
    v11 = 102;
LABEL_30:
    sBtlGetUnitHelperPos(v10, v11);
    p_pos = &pUnit->pos;
    *p_pos = vct_A;
    goto LABEL_34;
  }
  if (devilid == 260)
    goto LABEL_23;
  if (devilid == 312)
  {
    v10 = wk->scrUnitList[0];
    v11 = 101;
    goto LABEL_30;
  }
LABEL_34:
  v14 = Allocate(SBTLDMG_HITWORK);
  _ctor(v14, 0);
  Skilltbl = sBtlGetSkilltbl(gSklID);
  ListID = PChara->ListID;
  *(u64 *)&v14->hitbk_cnt = 0x4200000042000000LL;
  v14->acterID = ListID;
  v14->actID = ListID;
  v19 = Skilltbl->flg | 2;
  v14->skillid = gSklID;
  v14->skillflg = v19;
  *(u32 *)&v14->type = *(u32 *)&Skilltbl->type;
  v14->attr_flg = Skilltbl->attr;
  x = pUnit->pos.x;
  y = pUnit->pos.y;
  z = pUnit->pos.z;
  w = pUnit->pos.w;
  v25.x = x;
  v25.y = y;
  v25.z = z;
  v25.w = w;
  SetDamageProc(pUnit, PChara, gSklID, v25);
  aTateHitID = wk->aTateHitID;
LABEL_41:
  *((u32 *)&aTateHitID->obj.klass + v4) = 0;
  return v3;
}

// 0x20f8230
void sBtlPlayerPlayer_Bad_Push(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 bst_effserialID2;
  SBTLEFF_LISTWORK *effList;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus > 0xD)
    return;
  if (BadStatus != 6)
  {
    bst_effserialID2 = wk->bst_effserialID2;
    if (bst_effserialID2 != -1)
    {
      effList = wk->effList;
      sBtlDeleteEffectData_SerialID2(effList, bst_effserialID2);
      wk->bst_effserialID2 = -1;
      return;
    }
  }
}

// 0x20f8380
void sBtlPlayerPlayer_Bad_Pop(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 side;
  s32 v7;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus > 0xD)
    return;
  switch (BadStatus)
  {
    case 0u:
      side = wk->side;
      v7 = 294;
      goto LABEL_44;
    case 1u:
      side = wk->side;
      v7 = 290;
      goto LABEL_44;
    case 2u:
      side = wk->side;
      v7 = 291;
      goto LABEL_44;
    case 3u:
      side = wk->side;
      v7 = 292;
      goto LABEL_44;
    case 4u:
      side = wk->side;
      v7 = 289;
      goto LABEL_44;
    case 5u:
    case 9u:
      side = wk->side;
      v7 = 300;
      goto LABEL_44;
    case 7u:
      side = wk->side;
      v7 = 298;
      goto LABEL_44;
    case 8u:
      side = wk->side;
      v7 = 297;
      goto LABEL_44;
    case 0xAu:
      side = wk->side;
      v7 = 299;
      goto LABEL_44;
    case 0xBu:
      side = wk->side;
      v7 = 295;
      goto LABEL_44;
    case 0xCu:
      side = wk->side;
      v7 = 296;
      goto LABEL_44;
    case 0xDu:
      side = wk->side;
      v7 = 293;
LABEL_44:
      sBtlCheckEffectData(wk, v7, 1u, 0, side, -1, 0);
      wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
      break;
    default:
      return;
  }
}

// 0x20f8630
void sBtlPlayerScrWarp_MutekiOff_And_Push(void) {
  s64 v1;
  SBTLUNIT_WORK *pUnit;
  u32 status;
  char flg;

  v1 = 32;
  do
  {
    if (!!*(u32 *)((char *)&wk->aTateHitID->obj.klass + v1))
    {
      pUnit = wk->UnitMng->pUnitL[*(s32 *)((char *)&wk->aTateHitID->obj.klass + v1)]->pUnit;
      if (pUnit && (pUnit->side & 2) != 0 && pUnit->bOldScrWarp)
      {
        status = pUnit->status;
        pUnit->bOldHitNone = status & 1;
        pUnit->bOldNotHitDmg = (status & 0x4000) != 0;
        flg = pUnit->flg;
        pUnit->bOldNotMapHit = (status & 0x80) != 0;
        pUnit->bOldMuteki = (flg & 2) != 0;
        sBtlStatusBitOff(pUnit, 0xFFFFFFFE);
        sBtlStatusBitOff(pUnit, 0xFFFFBFFF);
        pUnit->flg &= ~2u;
      }
    }
    v1 += 4;
  }
  while (v1 != 96);
}

// 0x20f87a0
void sBtlPlayerScrWarp_Muteki_Pop(void) {
  s64 i;
  SBATTLE_WORK *wk_local;
  s32 v4;
  SBTLUNIT_WORK *pUnit;
  u32 v8;
  _BOOL4 bOldNotMapHit;
  u32 v11;

  for (i = 32; i != 96; i += 4)
  {
    wk_local = wk;
    v4 = *(u32 *)((char *)&wk_local->aTateHitID->obj.klass + i);
    if (!v4)
      continue;
    pUnit = wk_local->UnitMng->pUnitL[v4]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && pUnit->bOldScrWarp)
    {
      if (pUnit->bOldHitNone)
      {
        sBtlStatusBitOn(pUnit, 1u);
        if (pUnit->bOldNotHitDmg)
        {
LABEL_20:
          if (!v8)
          sBtlStatusBitOn(pUnit, 0x4000u);
LABEL_29:
          bOldNotMapHit = pUnit->bOldNotMapHit;
          pUnit->flg = pUnit->flg & 0xFFFFFFFD | (2 * pUnit->bOldMuteki);
          if (bOldNotMapHit)
          {
            if (!v11)
            sBtlStatusBitOn(pUnit, 0x80u);
          }
          else
          {
            if (!v11)
            sBtlStatusBitOff(pUnit, 0xFFFFFF7F);
          }
          continue;
        }
      }
      else
      {
        sBtlStatusBitOff(pUnit, 0xFFFFFFFE);
        if (pUnit->bOldNotHitDmg)
          goto LABEL_20;
      }
      if (!v8)
      sBtlStatusBitOff(pUnit, 0xFFFFBFFF);
      goto LABEL_29;
    }
  }
}

// 0x20f89b0
void sBtlPlayerSP_BS_MUNAKA_Init_Imad_Restart(void) {
  struct sBtlPlayer_Spirit *v5;

  if (!gEnd_BS_MUNAKA_Init_Imad_Restart)
    goto LABEL_16;
  if (wk_BS_MUNAKA_Init_Imad_Restart)
  {
    if (wk_BS_MUNAKA_Init_Imad_Restart->para->now->hp >= 1)
    {
      sBtlBS_MUNAKA_Init_Imad_Restart(wk_BS_MUNAKA_Init_Imad_Restart);
      goto LABEL_16;
    }
  }
LABEL_16:
  wk_BS_MUNAKA_Init_Imad_Restart = 0;
  v5 = ((char *)v5 + 40);
  *((u8 *)&v5[-1].gStartWaitCnt + 5) = 0;
}

// 0x20f8b00
void sBtlPlayerSP_BS_MUNAKA_Init_Imad_Kotei_Restart(void) {
  SBTLUNIT_WORK *UnitFromDevilID;

  if (!gEnd_BS_MUNAKA_Init_Imad_Kotei)
    return;
  UnitFromDevilID = sBtlGetUnitFromDevilID(291);
  if (UnitFromDevilID && UnitFromDevilID->actwk->status == 8)
    UnitFromDevilID->status &= ~0x80000u;
  gEnd_BS_MUNAKA_Init_Imad_Kotei = 0;
}

// 0x20f8c10
bool sBtlPlayerCheckRSpirit(void) {
  return wk->mode == 28;
}

// 0x20f8c80
bool sBtlPlayerCheckRSpiritEnd(void) {
  if (wk->mode != 28)
    return 0;
  return gStep > 30;
}

// 0x20f8d50
bool sBtlPlayerCheckRSpirit_Start(void) {
  if (wk->mode != 28)
    return 0;
  return gStep < 2 || gStep == 10;
}

// 0x20f8e30
void sBtlPlayerEndRSpiritProc(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v6;

  if (wk->mode == 28)
    goto LABEL_6;
  return;
  if (wk->mode == 28)
  {
LABEL_6:
    UnitMng = wk->UnitMng;
    playerID = wk->playerID;
    v6 = sBtlSearchUnit_ID(UnitMng, playerID);
    sBtlResetAction(v6);
    sBtlSetUseSkill(v6, 0, 0);
    return;
  }
}

// 0x20f9010
s32 sBtlPlayerRSpiritProc(SBTLUNIT_WORK *wk, s16 mode) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v7;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v11;
  s32 gReTryCnt_local;
  bool v16;
  s32 v17;
  SBTLSM_LISTWORK *sysmsgList;
  SBATTLE_WORK *v23;
  s32 SUMMONSKILL_Start;
  s32 v25;
  SBTLSM_LISTWORK *v28;
  f32 v30;
  SBATTLE_WORK *v33;
  f32 Dir180;
  sdfVector4_t *p_rot;
  f32 gStepTime_local;
  s32 v41;
  f32 v50;
  s32 v53;
  void *v54;
  bool v59;
  SBTLSM_LISTWORK *v61;
  s32 v64;
  u32 v65;
  s32 v66;
  s32 v69;
  SBTLAI_WORK *aiwk;
  u32 m_status;
  u32 v75;
  u32 v76;
  SBTLAI_WORK *v77;
  u32 v78;
  u32 v80;
  u32 v81;
  s32 v83;
  void *v85;
  bool v87;
  void *v88;
  void *v89;
  SBATTLE_WORK *v92;
  SBTLSM_LISTWORK *v93;
  SBATTLE_WORK *v97;
  s32 sprit_waza_usecnt;
  s32 v99;
  SBTLDVLTK_LISTWORK *v100;
  SBTLUNIT_WORK *v101;
  s32 v102;
  SBTLDVLTK_LISTWORK *v103;
  SBTLUNIT_WORK *v104;
  s32 v105;
  SBTLDVLTK_LISTWORK *v106;
  SBTLUNIT_WORK *PChara;
  SBTLDVLTK_LISTWORK *v108;
  SBTLUNIT_WORK *v109;
  void *v112;
  s64 v115;
  s32 v116;
  s32 v117;
  SBATTLE_WORK *v119;
  s32 v120;
  SBTLUNIT_WORK *v121;
  s32 ListID;
  f32 v124;
  f32 v125;
  f32 v126;
  s32 v129;
  SBTLUNIT_LISTWORK *v131;
  s32 targetID;
  SBTLUNIT_WORK *v133;
  u32 v134;
  bool v135;
  s64 v136;
  bool v137;
  s32 v142;
  u32 v146;
  s32 v147;
  s64 v149;
  u32 v150;
  s64 v151;
  SBATTLE_WORK *v155;
  u32 status2;
  SBTLSM_LISTWORK *v159;
  SBTLSM_LISTWORK *v163;
  void *Instance;
  SBTLDMG_HITLISTWORK *hitList;
  s64 i;
  SBATTLE_WORK *v168;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v171;
  s32 vstatus;
  long f64 v174;
  long f64 v175;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  SBATTLE_WORK *v181;
  SBTLDVLTK_LISTWORK *dvltkList;
  s32 frameWait;
  void *v186;
  f32 v191;
  S_PosMove *v192;
  S_PosMove *v193;
  S_PosMove *v194;
  S_PosMove *v195;
  f32 v196;
  f32 v197;
  s32 v199;
  s32 v200;
  s32 gMotReTryCnt_local;
  u32 v205;
  s32 v206;
  _BOOL4 v208;
  s32 v209;
  u32 v210;
  s32 v211;
  s32 v212;
  u32 v214;
  s32 v216;
  s32 v217;
  u32 v218;
  s32 v219;
  f32 CameraBtlStartX;
  SBTLSM_LISTWORK *v227;
  SBTLSM_LISTWORK *v231;
  s64 v232;
  s64 v233;
  sdfVector4_t v234;
  sdfVector4_t v235;

  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  v7 = MotionFrameF;
  sBtlGetSklVisualTbl(wk->cmbSkl->sklId);
  sBtlGetSkilltbl(wk->cmbSkl->sklId);
  Nakama = sBtlGetNakama(wk->SpiritSkillNakamaIdx);
  v9 = sBtlGetNakama(0);
  v11 = sBtlGetNakama(1);
  if (gStep > 10)
    goto LABEL_9;
  if (gStep)
  {
    if (gStep != 1)
    {
      if (gStep == 10)
      {
        gStepTime = gStepTime
                                 + VRF_DeltaTime;
        sysmsgList = wk->sysmsgList;
        sBtlReleaseSM_List(sysmsgList, 1u);
        sBtlCreateSM(wk->sysmsgList, wk, 10, gSklID, 0, 120);
        wk->sysmsgList->bLock = 1;
        dds3FadeIn2(4u);
        gStepTime = 0.0;
        *(u64 *)&gStep = 20;
        *(u64 *)&gMotReTryCnt = 0;
        *(u64 *)&gReTryCnt = 0;
      }
      return 2;
    }
    v30 = gStepTime + VRF_DeltaTime;
    ++gStepCnt;
    gStepTime = v30;
    wk->actwk->use_skillid = gSklID;
    v33 = wk;
    v33->sord_newcnt = 0;
    v33->sord_counter = 0;
    *(_OWORD *)&v33->sord_st = 0u;
    wk->pos.x = 0.0;
    wk->pos.y = 0.0;
    wk->pos.z = 0.0;
    Dir180 = sBtlGetDir180(180.0);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    p_rot = &wk->rot;
    *p_rot = vct_A;
LABEL_126:
    wk->hstatus |= 0x1000u;
    wk->rotbk = vct_A;
    switch (gSklID)
    {
      case 0x2B2:
        sBtlSetMotion(wk, 49, 0, 0, 0);
        Add(0, 0);
        v69 = 0;
        goto LABEL_331;
      case 0x2B3:
        sBtlSetMotion(wk, 49, 0, 0, 0);
        Add(0, 0);
        v69 = 2;
        goto LABEL_331;
      case 0x2B4:
        sBtlSetMotion(wk, 50, 0, 0, 0);
        Add(1, 0);
        v142 = 3;
        goto LABEL_326;
      case 0x2B7:
        sBtlSetMotion(wk, 50, 0, 0, 0);
        Add(1, 0);
        v142 = 2;
LABEL_326:
        Add(v142, 0);
        goto LABEL_333;
      case 0x2B8:
        sBtlSetMotion(wk, 49, 0, 0, 0);
        Add(0, 0);
        v69 = 1;
LABEL_331:
        Add(v69, 0);
        goto LABEL_332;
      case 0x2BB:
        sBtlSetMotion(wk, 51, 0, 0, 0);
        Add(2, 0);
        v147 = 2;
        goto LABEL_342;
      case 0x2BD:
        sBtlSetMotion(wk, 51, 0, 0, 0);
        Add(2, 0);
        v147 = 4;
LABEL_342:
        Add(v147, 0);
        goto LABEL_333;
      default:
LABEL_332:
LABEL_333:
        sBtlMapVisiblerSet(0);
        v146 = gSklID - 690;
        if (v146 <= 0xB)
        {
          if (((0xA67u >> v146) & 1) != 0)
            Add(dword_3E65428[v146], 0);
        }
        switch (gSklID)
        {
          case 0x2B2:
            v149 = *(u64 *)&wk->pos.x;
            v150 = 152502274;
            v151 = *(u64 *)&wk->pos.z;
            goto LABEL_364;
          case 0x2B3:
            v149 = *(u64 *)&wk->pos.x;
            v151 = *(u64 *)&wk->pos.z;
            v150 = 152567810;
            goto LABEL_364;
          case 0x2B4:
            v149 = *(u64 *)&wk->pos.x;
            v151 = *(u64 *)&wk->pos.z;
            v150 = 152633346;
            goto LABEL_364;
          case 0x2B7:
            v149 = *(u64 *)&wk->pos.x;
            v151 = *(u64 *)&wk->pos.z;
            v150 = 152829954;
            goto LABEL_364;
          case 0x2B8:
            v149 = *(u64 *)&wk->pos.x;
            v151 = *(u64 *)&wk->pos.z;
            v150 = 152895490;
            goto LABEL_364;
          case 0x2BB:
            v149 = *(u64 *)&wk->pos.x;
            v151 = *(u64 *)&wk->pos.z;
            v150 = 153092098;
            goto LABEL_364;
          case 0x2BD:
            v149 = *(u64 *)&wk->pos.x;
            v151 = *(u64 *)&wk->pos.z;
            v150 = 153223170;
            v232 = v151;
            v233 = v149;
            v151 = v232;
            v149 = v233;
LABEL_364:
            *(u64 *)&v234.x = v149;
            *(u64 *)&v234.z = v151;
            sBtlPlay3DSE(v150, v234);
            break;
          default:
            break;
        }
        sBtlPlayerSetEnemyPos(0);
        SetLightChg();
        sBtlSetMode(2);
        sBtlNoHokan();
        v155 = wk;
        status2 = v155->status2;
        v155->bEffNoDraw = 0;
        v155->status2 = status2 & 0xFFFFFFDF;
        sBtlAnimListClr();
        sBtlPlayerJyusoEffOnOff(wk, 0);
        sBtlPlayerPlayer_Bad_Push(wk);
        v159 = wk->sysmsgList;
        sBtlReleaseSM_List(v159, 1u);
        gStepTime = 0.0;
        *(u64 *)&gStep = 10;
        return 2;
    }
    v66 = (u8)byte_5755EF6;
    *p_rot = vct_A;
    goto LABEL_126;
  }
  v23 = wk;
  SUMMONSKILL_Start = v23->SUMMONSKILL_Start;
  if (SUMMONSKILL_Start)
  {
    v23 = wk;
    SUMMONSKILL_Start = v23->SUMMONSKILL_Start;
    v25 = SUMMONSKILL_Start - 1;
    v23->SUMMONSKILL_Start = v25;
    if (v25 <= 0)
    {
      sBtlPlayerSetTateHitEnemy();
    }
  }
  if (sBtlPlayerChkAll_EnemySummonW())
  {
    v28 = wk->sysmsgList;
    sBtlReleaseSM_List(v28, 1u);
    goto LABEL_116;
  }
  v59 = sBtlCheckSummon_LoadExecOk(1);
  if (v59)
  {
    if (!wk->SUMMONSKILL_Start)
    {
      *(u64 *)&gStepCnt = 0;
      ++gStep;
      v163 = wk->sysmsgList;
      sBtlReleaseSM_List(v163, 1u);
      Instance = get_Instance(0);
      RememberIconState(Instance, 0);
      sBtlForceDeleteAll_TimeStopSkill(0, 0);
      hitList = wk->hitList;
      sBtlReleaseHitC_List(hitList, 1u);
      sBtlAnimListClr();
      for (i = 0; ; ++i)
      {
        v168 = wk;
        UnitMng = v168->UnitMng;
        if (i >= UnitMng->number)
          break;
        UnitMng = wk->UnitMng;
        pUnit = UnitMng->pUnitL[i]->pUnit;
        if (pUnit)
          v171 = pUnit == wk;
        else
          v171 = 1;
        if (!v171)
        {
          vstatus = pUnit->vstatus;
          pUnit->JumpOfsPos.y = 5000.0;
          pUnit->vstatus = vstatus | 0x1000;
          sBtlUpdateUnitJumpOfsPos(pUnit);
        }
      }
      wk->vstatus &= ~0x1000u;
      v168 = wk;
      v168->effNoStop = 1;
      v168->bEffNoDraw = 1;
      *(u16 *)&v168->kaiwapaneldisp0 = 0;
      evtMoonDisableDraw(1);
      *(__n128 *)&v174 = sub_1B332C0(0, 0.0, 0.0, 0.0, 0.0);
      sub_1B335A0(&wk->pos, 0, v174);
      FromEuler(0.0, 0.0, 0.0);
      sub_1B335A0(&wk->rot, 0, v175);
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v235.x = x;
      v235.y = y;
      v235.z = z;
      v235.w = w;
      dds3SetPosPoseSet(&wk->pBasic, v235);
      dds3SetRotPoseSet(&wk->pBasic, wk->rot);
      sBtlSetMotion(wk, 23, 0, 0, 1);
      if (Nakama)
      {
        v181 = wk;
        v181->hitokoto_spirit = 1;
        dvltkList = v181->dvltkList;
        sBtlCreateDvltk(dvltkList, Nakama, 1, 0, 0);
        wk->hitokoto_spirit = 0;
        frameWait = get_Instance(0)->frameWait;
        gBkNakamaCutInFrameWait = frameWait;
        v186 = get_Instance(0);
        SetFrameWait(v186, 80, 0);
      }
      v191 = (f32)(wk->pos.y + -140.0) + -40.0;
      v193 = g_aCamMoveJizenTyuugi[0];
      v192 = g_aCamMoveJizenTyuugi[1];
      v193->m_vPos.x = 50.0;
      v193->m_vPos.z = -130.0;
      v192->m_fFrm = 60.0;
      v193->m_vPos.y = v191;
      v195 = g_aTgtMoveJizenTyuugi[0];
      v194 = g_aTgtMoveJizenTyuugi[1];
      v196 = wk->pos.y;
      v194->m_fFrm = 60.0;
      v192->m_vPos.y = (f32)(v196 + -140.0) + 60.0;
      v195->m_vPos.y = wk->pos.y + -140.0;
      v197 = wk->pos.y;
      v192->m_vPos.z = -120.0;
      v192->m_vPos.x = 0.0;
      v195->m_vPos.x = 0.0;
      v195->m_vPos.z = 0.0;
      v194->m_vPos.z = 0.0;
      v194->m_vPos.x = 10.0;
      v194->m_vPos.y = (f32)(v197 + -140.0) + 15.0;
      sBtlClearZoom();
      sBtlNoHokan();
      sBtlSetMove(g_CamMovJizenTyuugi, 1);
      sBtlSetMode(13);
      v65 = 0;
      goto LABEL_431;
    }
  }
  v61 = wk->sysmsgList;
  sBtlReleaseSM_List(v61, 1u);
  v64 = gStartWaitCnt + 1;
  v16 = gStartWaitCnt - 39 < 0;
  gStartWaitCnt = v64;
  if (v16 != __OFSUB__(v64, 40))
    return 2;
LABEL_116:
  if (dds3FadeOutCheck2())
    return 2;
  v65 = 8;
LABEL_431:
  dds3FadeOut(0xFFu, 0xFFu, 0xFFu, v65);
  return 2;
LABEL_9:
  switch (gStep)
  {
    case 20:
      gReTryCnt_local = gReTryCnt + 1;
      v16 = gReTryCnt - 28 < 0;
      gReTryCnt = gReTryCnt_local;
      if (v16 ^ __OFSUB__(gReTryCnt_local, 29) | (gReTryCnt_local == 29))
      {
        gReTryCnt_local = gReTryCnt;
        if ((u32)(-1431655765 * gReTryCnt_local + 715827882) <= 0x55555554)
        {
          switch (gSklID)
          {
            case 0x2B2:
              if (!ChkRun())
              {
                v17 = 0;
                goto LABEL_441;
              }
              break;
            case 0x2B3:
              if (!ChkRun())
              {
                v17 = 2;
                goto LABEL_441;
              }
              break;
            case 0x2B4:
              if (!ChkRun())
              {
                v199 = 3;
                goto LABEL_438;
              }
              break;
            case 0x2B7:
              if (!ChkRun())
              {
                v199 = 2;
LABEL_438:
                Add(v199, 0);
                goto LABEL_447;
              }
              break;
            case 0x2B8:
              if (!ChkRun())
              {
                v17 = 1;
LABEL_441:
                Add(v17, 0);
                goto LABEL_447;
              }
              break;
            case 0x2BB:
              if (!ChkRun())
              {
                v200 = 2;
                goto LABEL_446;
              }
              break;
            case 0x2BD:
              if (!ChkRun())
              {
                v200 = 4;
LABEL_446:
                Add(v200, 0);
LABEL_447:
                ++gReTryAddCnt;
              }
              break;
            default:
              break;
          }
        }
      }
      gMotReTryCnt_local = gMotReTryCnt + 1;
      v16 = gMotReTryCnt - 1 < 0;
      gMotReTryCnt = gMotReTryCnt_local;
      if (v16 != __OFSUB__(gMotReTryCnt_local, 2))
        goto LABEL_486;
      gMotReTryCnt_local = gMotReTryCnt;
      if (gMotReTryCnt_local > 29)
        goto LABEL_486;
      gMotReTryCnt_local = gMotReTryCnt;
      if ((u32)(-1431655765 * gMotReTryCnt_local + 715827882) > 0x55555554)
        goto LABEL_486;
      if (gMotReTryAddCnt > 2)
        goto LABEL_486;
      v205 = gSklID - 690;
      if (v205 > 0xB)
        goto LABEL_486;
      if (((1 << v205) & 0x43) != 0)
      {
        if (wk->motionno != 49 || v7 != 0.0)
          goto LABEL_486;
        v206 = 49;
      }
      else if (((1 << v205) & 0x24) != 0)
      {
        if (wk->motionno != 50 || v7 != 0.0)
          goto LABEL_486;
        v206 = 50;
      }
      else
      {
        if (((1 << v205) & 0xA00) == 0 || wk->motionno != 51 || v7 != 0.0)
          goto LABEL_486;
        v206 = 51;
      }
      sBtlSetMotion(wk, v206, 0, 0, 0);
      ++gMotReTryAddCnt;
LABEL_486:
      v208 = 0;
      if ((u32)(gSklID - 690) > 0xB)
        goto LABEL_548;
      if (((1 << (LOBYTE(gSklID) + 78)) & 0x43) != 0)
      {
        if (gEnemyNum >= 1)
        {
          if (gStepCnt == 300)
          {
            if (!v214)
              goto LABEL_519;
            goto LABEL_509;
          }
          if (gStepCnt >= 301)
            goto LABEL_538;
        }
        goto LABEL_541;
      }
      if (((1 << (LOBYTE(gSklID) + 78)) & 0x24) != 0)
      {
        if (gEnemyNum >= 1)
        {
          v217 = gStepCnt;
          if (v217 == 230)
          {
            if (!v218)
            {
LABEL_519:
              if (70 / gEnemyNum >= 20)
                v216 = 20;
              else
                v216 = 70 / gEnemyNum;
              goto LABEL_524;
            }
LABEL_509:
            if (70 / gEnemyNum >= 20)
              v216 = 20;
            else
              v216 = 70 / gEnemyNum;
LABEL_524:
            SetRndHitNum(gEnemyNum, v216);
            goto LABEL_541;
          }
          if (!v218)
          {
            v217 = gStepCnt;
          }
          if (v217 >= 231)
          {
LABEL_538:
            FakeRndHit(0, 0);
          }
        }
LABEL_541:
        if (gStepCnt != 240)
        {
          goto LABEL_544;
        }
        v227 = wk->sysmsgList;
        sBtlReleaseSM_List(v227, 1u);
LABEL_544:
        if (gStepCnt != 375)
        {
          v219 = 379;
          goto LABEL_547;
        }
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 4u);
        v219 = 379;
        goto LABEL_547;
      }
      if (((1 << (LOBYTE(gSklID) + 78)) & 0xA00) == 0)
        goto LABEL_548;
      if (gEnemyNum >= 1)
      {
        v209 = gStepCnt;
        if (v209 == 310)
        {
          if (v210)
          {
            v211 = gEnemyNum;
            if (70 / v211 >= 20)
              v212 = 20;
            else
              v212 = 70 / v211;
          }
          else
          {
            v211 = gEnemyNum;
            if (70 / v211 >= 20)
              v212 = 20;
            else
              v212 = 70 / v211;
            v211 = gEnemyNum;
          }
          SetRndHitNum(v211, v212);
        }
        else
        {
          if (!v210)
          {
            v209 = gStepCnt;
          }
          if (v209 >= 311)
          {
            FakeRndHit(0, 0);
          }
        }
      }
      if (gStepCnt != 240)
      {
        goto LABEL_588;
      }
      v231 = wk->sysmsgList;
      sBtlReleaseSM_List(v231, 1u);
LABEL_588:
      if (gStepCnt == 417)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 4u);
        v219 = 421;
        goto LABEL_547;
      }
      v219 = 421;
LABEL_547:
      v208 = gStepCnt > v219;
LABEL_548:
      ++gStepCnt;
      gStepTime = gStepTime + VRF_DeltaTime;
      if (v208)
      {
        sBtlPlayerPopAllPosRotDispHit();
        if (gEndPosReset)
        {
          sBtlPlayerResetPlayerPosRot_Start();
          sBtlPlayerResetEnemyPosRot_Start();
          CameraBtlStartX = wk->CameraBtlStartX;
          sBtlResetFollowUpAngleX(CameraBtlStartX);
        }
        v41 = 30;
        goto LABEL_563;
      }
      return 2;
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
      return 2;
    case 30:
      v41 = 31;
      goto LABEL_563;
    case 31:
      dds3FadeIn2(0xAu);
      sBtlPlayerResetEnemyPos();
      sBtlSetMode(2);
      sBtlPopCamera();
      sBtlNoHokan();
      wk->camSlpMode = 2;
      if (gEndPosReset)
      {
        v50 = wk->CameraBtlStartX;
        sBtlResetFollowUpAngleX(v50);
      }
      AW_XAtkDelete_XATK_FLAG2_BsFlowClr_Setsuma();
      ResetLightChg();
      if (v9)
      {
        sBtlStatusBitOff(v9, 0xFFFFBFEF);
        sBtlResetAAI(v9);
        v9->aiwk->mode = 0;
        sBtlSetMotion(v9, 0, 4, 0, 0);
        aiwk = v9->aiwk;
        m_status = aiwk->m_status;
        v75 = v9->status & 0xFFFFFFFE;
        v9->vstatus &= ~0x1000u;
        v76 = v9->flg & 0xFFFFFFFD;
        v9->status = v75;
        v9->flg = v76;
        aiwk->m_status = m_status & 0xFFFBFFFF;
        if (wk->NakamaShugouOn)
        {
          sBtlReset_SupportAction_Shugou2(v9);
        }
      }
      if (v11)
      {
        sBtlStatusBitOff(v11, 0xFFFFBFEF);
        sBtlResetAAI(v11);
        v11->aiwk->mode = 0;
        sBtlSetMotion(v11, 0, 4, 0, 0);
        v77 = v11->aiwk;
        v78 = v77->m_status;
        v80 = v11->status & 0xFFFFFFFE;
        v11->vstatus &= ~0x1000u;
        v81 = v11->flg & 0xFFFFFFFD;
        v11->status = v80;
        v11->flg = v81;
        v77->m_status = v78 & 0xFFFBFFFF;
        if (wk->NakamaShugouOn)
        {
          sBtlReset_SupportAction_Shugou2(v11);
        }
      }
      if ((u32)(gSklID - 690) > 0xB)
      {
LABEL_187:
        v92 = wk;
        v93 = v92->sysmsgList;
        *(u16 *)&v92->kaiwapaneldisp0 = 257;
        v93->bLock = 0;
        sBtlReleaseSM_List(v93, 1u);
        sBtlStatusBitOff(wk, 0xFFFFBFEF);
        wk->status &= ~1u;
        wk->flg &= ~2u;
        wk->effNoStop = 0;
        sBtlEndWaitALL(0, 1);
        wk->cmbSkl->bRun_DrawUI = 0;
        sBtlPlayerJyusoEffOnOff(wk, 1);
        sBtlPlayerPlayer_Bad_Pop(wk);
        v97 = wk;
        sprit_waza_usecnt = v97->sprit_waza_usecnt;
        v99 = sprit_waza_usecnt + 1;
        v97->sprit_waza_usecnt = sprit_waza_usecnt + 1;
        if (sprit_waza_usecnt == 1)
        {
          v97 = wk;
          v106 = v97->dvltkList;
          PChara = sBtlGetPChara();
          v102 = 268;
          v103 = v106;
          v104 = PChara;
          v105 = 2;
        }
        else if (sprit_waza_usecnt)
        {
          v97 = wk;
          v99 = v97->sprit_waza_usecnt;
          if (v99 < 3)
          {
LABEL_257:
            DeleteAll();
            DeleteAll();
            sBtlMapVisiblerSet(1);
LABEL_261:
            v112 = get_Instance(0);
            DevilHPactive_Not_Stp_Num4(v112, 1, 0);
            sBtlPlayerScrWarp_MutekiOff_And_Push();
            sBtlPlayerSP_BS_MUNAKA_Init_Imad_Restart();
            BS_MATORY_DELETE();
            AW_HitsClrScoreWork();
            v115 = 32;
            while (1)
            {
              v119 = wk;
              v120 = *(u32 *)((char *)&v119->aTateHitID->obj.klass + v115);
              if (!v120)
                goto LABEL_268;
              v121 = v119->UnitMng->pUnitL[v120]->pUnit;
              if (!v121)
                goto LABEL_268;
              ListID = v121->ListID;
              if (v121->para->devilid == 314)
              {
                if (ListID != 5)
                  goto LABEL_268;
                v124 = v121->pos.z;
                v125 = v121->pos.x;
                v126 = v121->pos.y;
                v116 = 5;
                v117 = gSklID;
              }
              else
              {
                v124 = v121->pos.z;
                v125 = v121->pos.x;
                v126 = v121->pos.y;
                v129 = gSklID;
                v116 = ListID;
                v117 = v129;
              }
              AW_HitsAdd_Spirit(v116, v117, v125, v126, v124);
LABEL_268:
              v115 += 4;
              if (v115 == 96)
              {
                v131 = wk->UnitMng;
                targetID = wk->actaiwk->targetID;
                v133 = sBtlSearchUnit_ID(v131, targetID);
                if (!v133 || ((v134 = (u16)v133->para->devilid - 259, v135 = v134 > 0x36, v136 = (1 << v134) & 0x60000000000001LL, !v135) ? (v137 = v136 == 0) : (v137 = 1), v137))
                {
                  sBtlPlayerDirectDmg();
                }
                gStepTime = 0.0;
                *(u64 *)&gStep = 32;
                return 2;
              }
            }
            goto LABEL_261;
          }
          v97 = wk;
          v108 = v97->dvltkList;
          v109 = sBtlGetPChara();
          v102 = 270;
          v105 = 5;
          v103 = v108;
          v104 = v109;
        }
        else
        {
          v97 = wk;
          v100 = v97->dvltkList;
          v101 = sBtlGetPChara();
          v102 = 265;
          v103 = v100;
          v104 = v101;
          v105 = 3;
        }
        sBtlCreateDvltk_Gouto(v103, v104, v102, v105);
        goto LABEL_257;
      }
      if (((1 << (LOBYTE(gSklID) + 78)) & 0x43) != 0)
      {
        v83 = 58;
LABEL_186:
        sBtlSetMotion(wk, v83, 0, 0, 0);
        goto LABEL_187;
      }
      else if (((1 << (LOBYTE(gSklID) + 78)) & 0x24) != 0)
      {
        v83 = 59;
        goto LABEL_186;
      }
      else
      {
        if (((1 << (LOBYTE(gSklID) + 78)) & 0xA00) == 0)
          goto LABEL_187;
        v83 = 60;
        goto LABEL_186;
      }
      goto LABEL_186;
    case 32:
      if (gStepCnt)
      {
        goto LABEL_93;
      }
      v85 = get_Instance(0);
      BackIconState(v85, 0);
LABEL_93:
      v53 = gStepCnt + 1;
      v16 = gStepCnt - 3 < 0;
      gStepCnt = v53;
      if (v16 == __OFSUB__(v53, 4))
      {
        gStepCnt = 0;
        v87 = sBtlPlayerDirectDmg();
        if (!v87)
        {
          sBtlPlayerScrWarp_Muteki_Pop();
          gStepTime = 0.0;
          *(u64 *)&gStep = (char *)&off_20 + 1;
          return 2;
        }
      }
      gStepTime = gStepTime
                                    + VRF_DeltaTime;
      return 2;
    case 33:
      v54 = get_Instance(0);
      if (IsNCutIn(v54, 0))
        goto LABEL_98;
      goto LABEL_9010;
      if (IsNCutIn(v88, 0))
      {
LABEL_98:
        goto LABEL_99;
      }
LABEL_9010:
      v89 = get_Instance(0);
      SetFrameWait(v89, gBkNakamaCutInFrameWait, 0);
LABEL_99:
      gStepTime = gStepTime + VRF_DeltaTime;
      wk->cmbSkl->bRun = 0;
      sBtlPlayerSP_BS_MUNAKA_Init_Imad_Kotei_Restart();
      v41 = 100;
LABEL_563:
      gStep = v41;
      gStepTime = 0.0;
      return 2;
    default:
      if (gStep != 100)
        return 2;
      gStepTime_local = gStepTime + VRF_DeltaTime;
      gStepTime = gStepTime_local;
      if (gStepTime_local > (f32)(FPS60 * 60.0))
      {
        sBtlResetAction(wk);
        sBtlSetUseSkill(wk, 0, 0);
        v41 = 2;
        goto LABEL_563;
      }
      gStepTime_local = gStepTime;
      if (gStepTime_local >= (f32)(FPS60 * 10.0))
      {
        if (sBtlPlayerRSkillCancel_Setsuma(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 10.0))
      {
        if (sBtlPlayerRSkillCancel_RSptrit(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 24.0))
      {
        if (sBtlPlayerRSkillCancel_Skill(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 10.0))
      {
        if (sBtlPlayerRSkillCancel_Guard(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 24.0))
      {
        if (sBtlPlayerRSkillCancel_Jump(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 10.0))
      {
        if (sBtlPlayerRSkillCancel_Kaihi(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 24.0))
      {
        if (sBtlPlayerRSkillCancel_Gun(wk))
          return 2;
      }
      if (gStepTime >= (f32)(FPS60 * 35.0))
        sBtlPlayerRSkillCancel_Move(wk);
      return 2;
  }
}
