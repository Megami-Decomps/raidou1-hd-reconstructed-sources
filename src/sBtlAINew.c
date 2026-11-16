#include "types.h"
#include "SBTLUNIT_HST.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"
#include "dat.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlainew.h"
#include "sbtlcalc.h"
#include "sbtlmain.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "smnr.h"

typedef enum {
    TP_1 = 0,
    TP_2 = 1,
    TP_3 = 2,
    TP_4 = 3,
    TP_5 = 4,
    TP_6 = 5,
    TP_7 = 6,
    TP_MAX = 7,
} COND;

typedef struct ATK_TARGET ATK_TARGET;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct ATK_TARGET {
    SKLID sklid;
    SBTLUNIT_LISTWORK *cond[7];
    s32 tgtidx;
};

static ATK_TARGET *atkTarget[17];

static bool RecoverAll(SBTLUNIT_WORK *wk);
static bool DeadRecover(SBTLUNIT_WORK *wk, SKLID use_sklid);
static bool DeKazya(SBTLUNIT_WORK *wk);
static s32 IsEnemyParamUP(void);
static bool GetAttack(SBTLUNIT_WORK *wk);
static bool IsAtk1Shot(void);
static s32 GetDamage(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtwk, SKLID sklid);
static bool ChkMukouSkill(SKLID sklid, SBTLUNIT_WORK *tgtwk);
static s32 GetShildDamage(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtwk, SKLID sklid);
static s32 GetUseSkillIdx(s32 cond_tp, SBTLUNIT_WORK *wk);
static s32 GetLowCostSkill(s32 cond_tp);
static s32 GetMaxDmgSkill(s32 cond_tp, SBTLUNIT_WORK *wk);
static s32 GetMaxShildDmgSkill(s32 cond_tp, SBTLUNIT_WORK *wk);
static void SetSkillTarget(s32 cond_tp, s32 skilIdx, SBTLUNIT_WORK *wk);
static void SetAtlTarget(s32 cond_tp, s32 skilIdx, s32 max, SBTLUNIT_WORK *user, SBTLUNIT_WORK *playerTgt, SBTLUNIT_WORK *tgtwk, SBTLUNIT_WORK *wk);
static bool FoundKabe(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtWk);
static bool WeakCheckDamageTarget(SBTLUNIT_WORK *wk);
static bool IsWeakSkill(SBTLUNIT_WORK *acterwk);
static s32 ParamUpChk(SBTLUNIT_WORK *wk, SKLID skillid);
static bool ParamUpSame(SBTLUNIT_WORK *wk, SKLID skillid);
static SBTLUNIT_WORK *GetGuardTarget(SBTLUNIT_WORK *pwk);
static bool SetNakamaGuard(SBTLUNIT_WORK *wk, bool target_user);
static bool IsNakamaGuard(void);
static bool UseJudgRecoverAll(SBTLUNIT_WORK *wk, SKLID sklid);
static SBTLUNIT_WORK *CreateUnitWork(sdatUnitWork_t *unit, s32 tubeNo);
static bool IsKabe(SBTLUNIT_WORK *wklock);
SBTLUNIT_WORK *Support_GetUserData(void);

// 0x2030d90
bool AI_NakamaUseSkill(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *PChara;
  sdatUnitWork_t *para;
  u32 BadStatus;
  bool result;
  u32 v8;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *PlayerTarget;
  SBTLUNIT_WORK *v13;
  s64 v14;
  s32 chuusei;
  bool v18;
  s32 skillAct;
  s64 v21;
  s32 v22;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLUNIT_WORK *v24;
  SBTLSKILLP_TBL *v25;
  SBTLUNIT_WORK *v26;
  SBTLSKILLP_TBL *v27;
  u32 flg;
  SBATTLE_WORK *v30;
  SBTLUNIT_LISTWORK *TargetList;
  s64 v32;
  s32 v33;
  s32 ListID;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_WORK *pUnit;
  u32 Damage;
  sdatParaWork_t *now;
  s32 hp;
  s32 maxhp;
  s32 v45;
  SBATTLE_WORK *v50;
  SBTLUNIT_LISTWORK *v51;
  s64 v52;
  s32 v53;
  s32 v54;
  SBTLUNIT_LISTWORK *v57;
  s32 v60;
  s32 v61;
  SBTLAI_WORK *v62;
  SBTLAI_WORK *v65;
  SBTLACTION_WORK *actwk;
  SBTLUNIT_LISTWORK *v68;
  SBTLAI_WORK *aiwk;
  u32 v70;

  PChara = sBtlGetPChara();
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus - 7 < 2)
    goto LABEL_6;
  v8 = BadStatus;
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    if (Nakama->actwk->status == 59)
      goto LABEL_40;
  }
  v13 = sBtlGetNakama(1);
  if (v13 && v13->actwk->status == 59)
    goto LABEL_40;
  v14 = 34359738375LL * PChara->para->now->maxhp;
  if ((signed s32)((v14 >> 37) + ((u64)v14 >> 63)) >= PChara->para->now->hp)
  {
    chuusei = wk->para->chuusei;
    if (GetPercentage() < chuusei >> 1)
    {
      if (SetNakamaGuard(wk, 1))
      {
        PChara->damagecnt = 60;
        return 0;
      }
    }
  }
  if (!GetGuardTarget(wk))
    goto LABEL_40;
  if (GetPercentage() > 0x31u)
    goto LABEL_40;
  v18 = SetNakamaGuard(wk, 0);
  result = 0;
  if (!v18)
  {
LABEL_40:
    skillAct = wk->aiwk->skillAct;
    if (v8 != 10 && !skillAct)
    {
      if (RecoverAll(wk))
        return 1;
      skillAct = wk->aiwk->skillAct;
    }
    if (v8 == 10 || skillAct)
      goto LABEL_115;
    v70 = v8;
    v21 = 0;
LABEL_52:
    v22 = wk->para->haveskill[v21];
    Skilltbl = sBtlGetSkilltbl(v22);
    if ((~Skilltbl->flg & 0x800004) == 0)
    {
      v24 = sBtlGetNakama(0);
      if (v24)
      {
        if (wk->ListID != v24->ListID)
        {
          v25 = sBtlGetSkilltbl(v24->actwk->use_skillid);
          if (v25)
          {
            if ((~v25->flg & 0x800004) == 0)
              goto LABEL_51;
          }
        }
      }
      v26 = sBtlGetNakama(1);
      if (v26)
      {
        if (wk->ListID != v26->ListID)
        {
          v27 = sBtlGetSkilltbl(v26->actwk->use_skillid);
          if (v27)
          {
            if ((~v27->flg & 0x800004) == 0)
              goto LABEL_51;
          }
        }
      }
    }
    flg = Skilltbl->flg;
    if ((flg & 4) == 0)
      goto LABEL_51;
    if ((flg & 0x10000) == 0)
    {
      v30 = wk;
LABEL_65:
      TargetList = sBtlCreateTargetList(1);
      v30->friend_List = TargetList;
      v32 = 0;
      v33 = 999999;
      ListID = -1;
      while (1)
      {
        friend_List = wk->friend_List;
        if (v32 >= friend_List->count)
        {
          sBtlDeleteUnitList(friend_List, 0);
          if (ListID != -1)
          {
            wk->actaiwk->targetID = ListID;
            goto LABEL_165;
          }
LABEL_51:
          if (++v21 == 17)
            goto LABEL_114;
          goto LABEL_52;
        }
        pUnit = friend_List->pUnitL[v32]->pUnit;
        if (!pUnit)
          goto LABEL_67;
        if (!sBtlCheckDamageTarget(pUnit))
          goto LABEL_67;
        Damage = GetDamage(wk, pUnit, v22);
        if ((Skilltbl->flg & 0x800000) != 0)
        {
          if (pUnit->rejyenecounter > 0)
            goto LABEL_67;
          if (Damage <= 1)
            Damage = 1;
        }
        now = pUnit->para->now;
        hp = now->hp;
        maxhp = now->maxhp;
        if (maxhp >= 0)
          v45 = maxhp;
        else
          v45 = maxhp + 1;
        if ((hp <= v45 >> 1 || (s32)(hp + Damage) <= maxhp) && v33 > hp)
        {
          ListID = pUnit->ListID;
          v33 = hp;
        }
LABEL_67:
        ++v32;
      }
      goto LABEL_65;
    }
    wk->actwk->use_skillid = v22;
    if (!sBtlCheckCost2(wk, v22, 0))
      goto LABEL_51;
    wk->actwk->order_targetID = -1;
    wk->actaiwk->targetID = -1;
    if (!sBtlCheckTargetEquation(wk))
      goto LABEL_51;
    if (wk->actaiwk->targetID != -1)
    {
      ListID = wk->actaiwk->targetID;
LABEL_165:
      aiwk = wk->aiwk;
      aiwk->dfltOdrSkl = v22;
      aiwk->dfltOdrTgt = ListID;
      aiwk->dfltOdrStk = -1;
      wk->actwk->use_skillid = v22;
      return 1;
    }
LABEL_114:
    skillAct = wk->aiwk->skillAct;
    v8 = v70;
LABEL_115:
    if (v8 == 10 || skillAct)
    {
LABEL_136:
      if (v8 != 10 && !skillAct)
      {
        if (DeadRecover(wk, 119))
          return 1;
        if (DeadRecover(wk, 118))
          return 1;
        skillAct = wk->aiwk->skillAct;
      }
      if (v8 != 10 && !skillAct)
      {
        if (DeKazya(wk))
          return 1;
      }
LABEL_6:
      if (sBtlYasoAI())
      {
        if ((wk->side & 1) != 0 && wk->actaiwk->stat == 1)
          wk->aiwk->mode = 1;
        wk->actwk->use_skillid = 0;
        return 0;
      }
      if (GetAttack(wk))
        return 1;
      PlayerTarget = sBtlGetPlayerTarget();
      if (!PlayerTarget)
        goto LABEL_144;
      v60 = PlayerTarget->ListID;
      if (v60 != -1)
      {
        v61 = 149;
LABEL_145:
        wk->actwk->use_skillid = v61;
        v62 = wk->aiwk;
        v62->dfltOdrSkl = v61;
        v62->dfltOdrTgt = v60;
        v62->dfltOdrStk = -1;
        sBtlCheckTargetEquation(wk);
        return 1;
      }
LABEL_144:
      v61 = 0;
      v60 = -1;
      goto LABEL_145;
    }
    v50 = wk;
    v51 = sBtlCreateTargetList(1);
    v50->friend_List = v51;
    v52 = 32;
    while (1)
    {
      v54 = *(u32 *)((char *)&wk->para->haveskill->obj.klass + v52);
      if ((sBtlGetSkilltbl(v54)->flg & 0x20) != 0)
      {
        wk->actwk->use_skillid = v54;
        if (!sBtlCheckCost2(wk, v54, 0))
          goto LABEL_123;
        wk->actwk->order_targetID = -1;
        wk->actaiwk->targetID = -1;
        v53 = ParamUpChk(wk, v54);
        if (v53 != -1)
        {
          v65 = wk->aiwk;
          v65->dfltOdrSkl = v54;
          v65->dfltOdrTgt = v53;
          v65->dfltOdrStk = -1;
          actwk = wk->actwk;
          actwk->order_skillid = v54;
          actwk->order_targetID = v53;
          v68 = wk->friend_List;
          sBtlDeleteUnitList(v68, 0);
          return 1;
        }
      }
LABEL_123:
      v52 += 4;
      if (v52 == 100)
      {
        v57 = wk->friend_List;
        sBtlDeleteUnitList(v57, 0);
        skillAct = wk->aiwk->skillAct;
        goto LABEL_136;
      }
    }
  }
  return result;
}

// 0x2032020
static bool RecoverAll(SBTLUNIT_WORK *wk) {
  u64 v3;
  char v4;
  s32 v6;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLAI_WORK *aiwk;

  v3 = 0;
  v4 = 1;
  while (1)
  {
    v6 = wk->para->haveskill[v3];
    Skilltbl = sBtlGetSkilltbl(v6);
    if ((Skilltbl->flg & 4) != 0 && (Skilltbl->area & 4) != 0)
    {
      if (UseJudgRecoverAll(wk, v6))
        break;
    }
    v4 = v3++ < 0x10;
    if (v3 == 17)
      return v4;
  }
  aiwk = wk->aiwk;
  aiwk->dfltOdrSkl = v6;
  *(u64 *)&aiwk->dfltOdrTgt = -1;
  wk->actwk->use_skillid = v6;
  return v4;
}

// 0x20324a0
static bool DeadRecover(SBTLUNIT_WORK *wk, SKLID use_sklid) {
  s64 v5;
  sdatUnitWork_t *v7;
  s32 devilid;
  bool v9;
  s64 v11;
  SBTLAI_WORK *aiwk;

  v5 = 0;
  while (1)
  {
    if (v5 >= datGetStockDevilNums(0))
      return 0;
    v7 = GBWK->player->stock_id[v5];
    devilid = v7->devilid;
    if (v7->devilid)
    {
      if ((v7->flag & 1) != 0)
      {
        v9 = DlcDevilSelCheck(devilid);
        if (!v9)
          goto LABEL_4;
        if ((v7->badstatus & 0x20000) != 0)
          break;
      }
    }
LABEL_4:
    ++v5;
  }
  v11 = 32;
  while (1)
  {
    if (*(u32 *)((char *)&wk->para->haveskill->obj.klass + v11) == use_sklid)
    {
      if (sBtlCheckCost2(wk, use_sklid, 0))
        break;
    }
    v11 += 4;
    if (v11 == 100)
      return 0;
  }
  aiwk = wk->aiwk;
  aiwk->rsvSkl = use_sklid;
  aiwk->rsvTgt = -1;
  aiwk->rsvStk = v5;
  aiwk->usedSkl = 0;
  return 1;
}

// 0x2032670
static bool DeKazya(SBTLUNIT_WORK *wk) {
  u64 v3;
  char v4;
  s32 IsEnemyParamUP;
  SBATTLE_WORK *v10;
  SBTLUNIT_LISTWORK *TargetList;
  SBTLACTION_WORK *actwk;
  SBTLAI_WORK *aiwk;

  v3 = 0;
  v4 = 1;
  while (1)
  {
    if (wk->para->haveskill[v3] != 134)
      goto LABEL_5;
    if (sBtlCheckCost2(wk, 134, 0))
      goto LABEL_14;
LABEL_5:
    v4 = v3++ < 0x10;
    if (v3 == 17)
      return v4;
  }
  if (!sBtlCheckCost2(wk, 134, 0))
    goto LABEL_5;
LABEL_14:
  wk->actwk->order_targetID = -1;
  wk->actaiwk->targetID = -1;
  v10 = wk;
  TargetList = sBtlCreateTargetList(2);
  v10->friend_List = TargetList;
  IsEnemyParamUP = IsEnemyParamUP();
  sBtlDeleteUnitList(wk->friend_List, 0);
  if (IsEnemyParamUP == -1)
    goto LABEL_5;
  actwk = wk->actwk;
  actwk->use_skillid = 134;
  aiwk = wk->aiwk;
  aiwk->dfltOdrSkl = 134;
  aiwk->dfltOdrTgt = IsEnemyParamUP;
  aiwk->dfltOdrStk = -1;
  actwk->order_skillid = 134;
  actwk->order_targetID = IsEnemyParamUP;
  return v4;
}

// 0x2033b80
static s32 IsEnemyParamUP(void) {
  s64 v1;
  s32 v2;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_WORK *pUnit;
  SBTLSKL_KAJA_WORK **wkKaja;
  SBTLSKL_KAJA_WORK *v7;
  SBTLSKL_KAJA_WORK *v8;
  SBTLSKL_KAJA_WORK *v9;
  SBTLSKL_KAJA_WORK *v10;
  SBTLSKL_KAJA_WORK *v11;
  SBTLSKL_KAJA_WORK *v12;
  SBTLSKL_KAJA_WORK *v13;
  SBTLSKL_KAJA_WORK *v14;
  SBTLSKL_KAJA_WORK *v15;
  tagSBTLSKL_AURA_WORK *wkAura;
  void *wkBarrier;
  s32 v18;

  v1 = 0;
  v2 = -1;
  while (1)
  {
    friend_List = wk->friend_List;
    if (v1 >= friend_List->count)
      return v2;
    pUnit = friend_List->pUnitL[v1]->pUnit;
    if (!pUnit)
      goto LABEL_4;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_4;
    wkKaja = pUnit->wkKaja;
    v7 = wkKaja[0];
    v8 = v7[0];
    if (v8->m_cnt && v8->m_fPara > 0.0)
      return v1;
    v9 = v7[1];
    if (v9->m_cnt)
    {
      if (v9->m_fPara > 0.0)
        return v1;
    }
    v10 = wkKaja[1];
    v11 = v10[0];
    if (v11->m_cnt)
    {
      if (v11->m_fPara > 0.0)
        return v1;
    }
    v12 = v10[1];
    if (v12->m_cnt)
    {
      if (v12->m_fPara > 0.0)
        return v1;
    }
    v13 = wkKaja[2];
    v14 = v13[0];
    if (v14->m_cnt)
    {
      if (v14->m_fPara > 0.0)
        return v1;
    }
    v15 = v13[1];
    if (v15->m_cnt)
    {
      if (v15->m_fPara > 0.0)
        return v1;
    }
    if (pUnit->wkKarn[0]->m_cnt)
      return v1;
    wkAura = pUnit->wkAura;
    if (wkAura[0]->auracnt || wkAura[1]->auracnt || wkAura[2]->auracnt)
      return v1;
    wkBarrier = pUnit->wkBarrier;
    if (wkBarrier->_size >= 1)
    {
      v18 = 0;
      while (!HIDWORD(_get_Item(wkBarrier, v18)[1].klass))
      {
        wkBarrier = pUnit->wkBarrier;
        if (++v18 >= wkBarrier->_size)
          goto LABEL_4;
      }
      return v1;
    }
LABEL_4:
    ++v1;
  }
}

// 0x2032870
static bool GetAttack(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  ATK_TARGET *v5;
  s64 i;
  const char *v8;
  ATK_TARGET *atkTarget_local;
  s64 v11;
  ATK_TARGET *v12;
  s64 v15;
  const char *namespaze;
  const char *v19;
  const char *v21;
  const char *v23;
  const char *v25;
  s64 j;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 v32;
  SBTLUNIT_LISTWORK *v33;
  SBTLUNIT_LISTWORK *v34;
  SBTLUNIT_LISTWORK *v35;
  SBTLUNIT_LISTWORK *v36;
  SBTLUNIT_LISTWORK *v38;
  SBTLUNIT_LISTWORK *cond;
  SBTLUNIT_LISTWORK *TargetList_DeadDamage;
  SBTLUNIT_LISTWORK *v45;
  ATK_TARGET *v47;
  s32 v48;
  SBTLSKILLP_TBL *Skilltbl;
  bool IsAtk1Shot;
  ATK_TARGET *v52;
  SBTLUNIT_LISTWORK *v53;
  SBTLUNIT_LISTWORK *v54;
  SBTLUNIT_LISTWORK *v55;
  SBTLUNIT_LISTWORK *v56;
  SBTLUNIT_LISTWORK *v58;
  SBTLUNIT_LISTWORK *v59;
  ATK_TARGET *v63;
  SBTLUNIT_LISTWORK *v64;
  SBTLUNIT_LISTWORK *v65;
  SBTLUNIT_LISTWORK *v66;
  SBTLUNIT_LISTWORK *v67;
  SBTLUNIT_LISTWORK *TargetList_HST;
  SBTLUNIT_LISTWORK *v70;
  SBTLUNIT_LISTWORK *v71;
  SBTLUNIT_LISTWORK *TargetList_WeakAtk;
  SBTLUNIT_LISTWORK *v74;
  SBTLUNIT_LISTWORK *v75;
  SBTLUNIT_LISTWORK *v77;
  SBTLUNIT_LISTWORK *v78;
  SBTLUNIT_LISTWORK *v82;
  SBTLUNIT_LISTWORK *TargetList_RaidouTarget;
  SBTLUNIT_LISTWORK *v84;
  SBTLUNIT_LISTWORK *v85;
  SBTLUNIT_LISTWORK *v87;
  SBTLUNIT_LISTWORK *v88;
  s64 v89;
  s64 v90;
  s32 UseSkillIdx;
  s32 v93;
  SBTLUNIT_WORK *PlayerTarget;
  SBTLAI_WORK *v98;
  ATK_TARGET *v100;
  s64 tgtidx;
  SBTLUNIT_WORK *v102;
  SBTLAI_WORK *aiwk;
  SBTLACTION_WORK *actwk;
  SBTLAI_WORK *v105;
  s64 v106;
  s64 v108;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (!atkTarget)
  {
    v5 = NewSpecific(ATK_TARGET, 0x11u);
    atkTarget = v5;
  }
  for (i = 32; i != 168; i += 8)
  {
    atkTarget_local = atkTarget;
    if (*(Il2CppClass **)((char *)&atkTarget_local->obj.klass + i))
    {
      goto LABEL_17;
    }
    v12 = Allocate(ATK_TARGET);
    _ctor(v12, 0);
    *(Il2CppClass **)((char *)&atkTarget_local->obj.klass + i) = v12;
LABEL_17:
    v11 = *(s64 *)((char *)&atkTarget->obj.klass + i);
    *(u32 *)(v11 + 16) = 0;
    v15 = *(u64 *)(v11 + 24);
    *(u64 *)(v15 + 32) = 0;
    namespaze = (*(Il2CppClass **)((char *)&atkTarget->obj.klass + i))->_1.namespaze;
    *((u64 *)namespaze + 5) = 0;
    v19 = (*(Il2CppClass **)((char *)&atkTarget->obj.klass + i))->_1.namespaze;
    *((u64 *)v19 + 6) = 0;
    v21 = (*(Il2CppClass **)((char *)&atkTarget->obj.klass + i))->_1.namespaze;
    *((u64 *)v21 + 7) = 0;
    v23 = (*(Il2CppClass **)((char *)&atkTarget->obj.klass + i))->_1.namespaze;
    *((u64 *)v23 + 8) = 0;
    v25 = (*(Il2CppClass **)((char *)&atkTarget->obj.klass + i))->_1.namespaze;
    *((u64 *)v25 + 9) = 0;
    v8 = (*(Il2CppClass **)((char *)&atkTarget->obj.klass + i))->_1.namespaze;
    *((u64 *)v8 + 10) = 0;
  }
  if (!wk->aiwk->skillAct && BadStatus != 10)
  {
    for (j = 0; ; ++j)
    {
      UnitMng = wk->UnitMng;
      if (j >= UnitMng->number)
        break;
      pUnit = UnitMng->pUnitL[j]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x3F) != 2)
        continue;
      if (!sBtlCheckDamageTarget(pUnit))
        continue;
      if (FoundKabe(wk, pUnit))
        goto LABEL_160;
    }
  }
  v32 = 0;
  while (2)
  {
    if (!!IsAtk1Shot())
      goto LABEL_72;
    cond = atkTarget[v32]->cond;
    TargetList_DeadDamage = sBtlCreateTargetList_DeadDamage(wk, 2, 149);
    v45 = TargetList_DeadDamage;
    cond[0] = v45;
    v47 = atkTarget[v32];
    if (!v47->cond[0]->count)
    {
LABEL_72:
      if (!wk->aiwk->skillAct && BadStatus != 10)
      {
        v48 = wk->para->haveskill[v32];
        Skilltbl = sBtlGetSkilltbl(v48);
        if (!v48 || v48 == 288 || (Skilltbl->flg & 1) == 0 || (Skilltbl->type & 0x1000) != 0)
          goto LABEL_62;
        IsAtk1Shot = IsAtk1Shot();
        if (v48 != 149)
        {
LABEL_90:
          if (sBtlCheckCost2(wk, v48, 0))
          {
            v63 = atkTarget[v32];
            v64 = v63->cond;
            v63->sklid = v48;
            v65 = sBtlCreateTargetList_DeadDamage(wk, 2, v48);
            v66 = v65;
            v64[0] = v66;
            v67 = atkTarget[v32]->cond;
            TargetList_HST = sBtlCreateTargetList_HST(2, 16);
            v70 = TargetList_HST;
            v67[1] = v70;
            v71 = atkTarget[v32]->cond;
            TargetList_WeakAtk = sBtlCreateTargetList_WeakAtk(2, v48, 0);
            v74 = TargetList_WeakAtk;
            v71[2] = v74;
            v75 = atkTarget[v32]->cond;
            v77 = sBtlCreateTargetList_WeakAtk(2, v48, 1);
            v78 = v77;
            v75[3] = v78;
            if (!IsWeakSkill(wk))
            {
              v82 = atkTarget[v32]->cond;
              TargetList_RaidouTarget = sBtlCreateTargetList_RaidouTarget(2, 0);
              v84 = TargetList_RaidouTarget;
              v82[4] = v84;
              v85 = atkTarget[v32]->cond;
              v87 = sBtlCreateTargetList_RaidouTarget(2, 1);
              v88 = v87;
              v85[5] = v88;
            }
            goto LABEL_60;
          }
          goto LABEL_62;
        }
        if (!IsAtk1Shot)
          goto LABEL_90;
        goto LABEL_62;
      }
      v52 = atkTarget[v32];
      v53 = v52->cond;
      v52->sklid = 149;
      v54 = sBtlCreateTargetList_DeadDamage(wk, 2, 149);
      v55 = v54;
      v53[0] = v55;
      v56 = atkTarget[v32]->cond;
      v58 = sBtlCreateTargetList_HST(2, 16);
      v59 = v58;
      v56[1] = v59;
      v33 = atkTarget[v32]->cond;
      v33[2] = 0;
      v34 = atkTarget[v32]->cond;
      v34[3] = 0;
      v35 = atkTarget[v32]->cond;
      v35[4] = 0;
      v36 = atkTarget[v32]->cond;
      v36[5] = 0;
LABEL_60:
      v38 = atkTarget[v32]->cond;
      v38[6] = 0;
LABEL_62:
      if (++v32 == 17)
      {
        goto LABEL_118;
      }
      continue;
    }
    break;
  }
  v47 = atkTarget[v32];
  v47->sklid = 149;
LABEL_118:
  v89 = 0;
LABEL_120:
  v90 = 32;
  while (2)
  {
    if (!*(u64 *)&(*(Il2CppClass **)((char *)&atkTarget->obj.klass + v90))->_1.namespaze[8 * v89 + 32])
      goto LABEL_122;
    if (LODWORD((*(Il2CppClass **)((char *)&atkTarget->obj.klass + v90))->_1.name) == 149)
      goto LABEL_122;
    if (!*(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&atkTarget->obj.klass + v90))->_1.namespaze[8 * v89 + 32] + 20))
    {
LABEL_122:
      v90 += 8;
      if (v90 != 168)
        continue;
      if (++v89 != 7)
        goto LABEL_120;
      v89 = 0;
LABEL_164:
      v108 = 32;
LABEL_167:
      if (*(u64 *)&(*(Il2CppClass **)((char *)&atkTarget->obj.klass + v108))->_1.namespaze[8 * v89 + 32])
      {
        if (LODWORD((*(Il2CppClass **)((char *)&atkTarget->obj.klass + v108))->_1.name) == 149)
        {
          if (*(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&atkTarget->obj.klass + v108))->_1.namespaze[8 * v89 + 32] + 20))
          {
            if ((u32)v89 != -1)
              break;
LABEL_163:
            if (++v89 == 7)
              goto LABEL_176;
            goto LABEL_164;
          }
        }
      }
      v108 += 8;
      if (v108 == 168)
        goto LABEL_163;
      goto LABEL_167;
    }
    break;
  }
  UseSkillIdx = GetUseSkillIdx(v89, wk);
  if (UseSkillIdx == -1)
  {
LABEL_176:
    LOBYTE(PlayerTarget) = 0;
    return (char)PlayerTarget;
  }
  v93 = UseSkillIdx;
  PlayerTarget = sBtlGetPlayerTarget();
  if (PlayerTarget)
  {
    SetSkillTarget(v89, v93, wk);
    if ((u32)v89 < 4)
    {
      wk->aiwk->dfltOdrTgt = -1;
      v100 = atkTarget[v93];
      tgtidx = v100->tgtidx;
      if ((u32)tgtidx != -1)
      {
        v100 = atkTarget[v93];
        v102 = v100->cond[(u32)v89]->pUnitL[tgtidx]->pUnit;
        if (v102)
        {
          aiwk = wk->aiwk;
          v102 = atkTarget[v93]->cond[(u32)v89]->pUnitL[tgtidx]->pUnit;
          aiwk->dfltOdrTgt = v102->ListID;
        }
      }
    }
    else
    {
      if ((v89 & 0xFFFFFFFE) == 4)
      {
        v98 = wk->aiwk;
        v98->dfltOdrTgt = sBtlGetPlayerTarget()->ListID;
      }
    }
    actwk = wk->actwk;
    v105 = wk->aiwk;
    v106 = (s64)atkTarget + 8 * v93;
    v105->dfltOdrStk = -1;
    LODWORD(v106) = *(u32 *)(*(u64 *)(v106 + 32) + 16);
    actwk->use_skillid = v106;
    v105->dfltOdrSkl = v106;
    sBtlCheckTargetEquation(wk);
LABEL_160:
    LOBYTE(PlayerTarget) = 1;
  }
  return (char)PlayerTarget;
}

// 0x2034090
static bool IsAtk1Shot(void) {
  s32 encountno;

  encountno = wk->encountno;
  if (encountno == 488)
    return 1;
  if (encountno == 489)
    return 1;
  if (encountno == 490)
    return 1;
  if (encountno == 66)
    return 1;
  encountno = wk->encountno;
  if (encountno == 528)
    return 1;
  encountno = wk->encountno;
  return encountno == 531;
}

// 0x2033620
SBTLUNIT_WORK *sBtlGetPlayerTarget(void) {
  SBTLACTAI_WORK *actaiwk;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;

  actaiwk = sBtlGetPChara()->actaiwk;
  targetID = actaiwk->targetID;
  if (targetID != -1)
  {
LABEL_4:
    UnitMng = wk->UnitMng;
    return sBtlSearchUnit_ID(UnitMng, targetID);
  }
  if (!wk->CameraLockOn)
    return 0;
  targetID = wk->CameraLockOnTgtID;
  if (targetID != -1)
    goto LABEL_4;
  return 0;
}

// 0x2032110
static s32 GetDamage(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtwk, SKLID sklid) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLDMG_HITWORK *v8;
  u32 flg;
  s32 v11;
  SBTLCALC_DMGWORK_A *v12;
  u32 attr;
  sdatUnitWork_t *para;
  s16 level;
  int32x2_t *now;
  s32 v17;

  Skilltbl = sBtlGetSkilltbl(sklid);
  v8 = Allocate(SBTLDMG_HITWORK);
  _ctor(v8, 0);
  flg = Skilltbl->flg;
  v8->skillid = sklid;
  v8->skillflg = flg;
  v11 = *(u32 *)&Skilltbl->type;
  v8->workID = 0;
  *(u32 *)&v8->type = v11;
  v8->BEDtype = 1;
  v12 = v8->awk;
  attr = Skilltbl->attr;
  v12->aside = tgtwk->side;
  para = tgtwk->para;
  v8->attr_flg = attr;
  v12->adevilid = para->devilid;
  v12->aListID = tgtwk->ListID;
  level = para->level;
  now = para->now;
  v12->alevel = level;
  v17 = now[4].n64_i16[2];
  v12->aatk = now[4].n64_i16[0];
  v12->atec = v17;
  *(float32x2_t *)&v12->ahp = vcvt_f32_s32(now[2]);
  return sBtlGetDamage(wk, tgtwk, v8, sklid, attr, 1);
}

// 0x2035330
static bool ChkMukouSkill(SKLID sklid, SBTLUNIT_WORK *tgtwk) {
  SBTLSKILLP_TBL *Skilltbl;
  sdatUnitWork_t *para;
  SBTLSKILLP_TBL *v7;
  SBTLUNIT_WORK *v8;
  u32 attr;
  u32 v10;
  bool result;
  s32 a_pHanshaType;

  Skilltbl = sBtlGetSkilltbl(sklid);
  para = tgtwk->para;
  v7 = Skilltbl;
  a_pHanshaType = 0;
  if (para->devilid == 315)
  {
    v8 = sBtlSearchDeivl(260);
    if (v8)
      tgtwk = v8;
  }
  attr = v7->attr;
  v10 = sBtlCheckAisyoEx(tgtwk, attr, &a_pHanshaType);
  result = 0;
  if (!a_pHanshaType && (v10 & 0x1000) == 0 && (v10 & 0x2000) == 0)
    return (v10 & 0x10000) == 0;
  return result;
}

// 0x2035430
static s32 GetShildDamage(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtwk, SKLID sklid) {
  return sBtlGetSkilltbl(sklid)->shild_dmg;
}

// 0x2034d70
static s32 GetUseSkillIdx(s32 cond_tp, SBTLUNIT_WORK *wk) {
  if ((u32)cond_tp > 5)
    return -1;
  if (((1 << cond_tp) & 0x16) != 0)
  {
    return GetMaxDmgSkill(cond_tp, wk);
  }
  else if (((1 << cond_tp) & 0x28) != 0)
  {
    return GetMaxShildDmgSkill(cond_tp, wk);
  }
  else
  {
    return GetLowCostSkill(0);
  }
}

// 0x2035450
static s32 GetLowCostSkill(s32 cond_tp) {
  s64 v4;
  s32 v5;
  s32 v6;
  s64 i;
  s64 v8;
  SBTLSKILLP_TBL *Skilltbl;
  s32 s_type;
  SBTLSKILLP_TBL *v11;
  bool v12;
  s32 para;
  bool v14;

  v4 = cond_tp;
  v5 = 9999;
  v6 = -1;
  for (i = 4; i != 21; ++i)
  {
    if (*(u64 *)(*(u64 *)(*((u64 *)&atkTarget->obj.klass + i) + 24) + 8 * v4 + 32))
    {
      v8 = *((u64 *)&atkTarget->obj.klass + i);
      if (*(u32 *)(*(u64 *)(*(u64 *)(v8 + 24) + 8 * v4 + 32) + 20))
      {
        v8 = *((u64 *)&atkTarget->obj.klass + i);
        Skilltbl = sBtlGetSkilltbl(*(u32 *)(v8 + 16));
        s_type = Skilltbl->s_type;
        v11 = Skilltbl;
        if (s_type)
          v12 = (s_type & 0x10) == 0;
        else
          v12 = 0;
        if (!v12)
        {
          para = v11->para;
          v14 = v5 <= para;
          if (v5 >= para)
            v5 = para;
          if (!v14)
            v6 = i - 4;
        }
      }
    }
  }
  return v6;
}

// 0x2035590
static s32 GetMaxDmgSkill(s32 cond_tp, SBTLUNIT_WORK *wk) {
  s64 v4;
  s64 v5;
  ATK_TARGET *v7;
  SBTLUNIT_LISTWORK *v8;
  s32 sklid;
  s64 count;
  u64 v11;
  s64 v12;
  SBTLSKILLP_TBL *v13;
  SBTLDMG_HITWORK *v14;
  u32 flg;
  s32 v17;
  SBTLCALC_DMGWORK_A *v18;
  u32 v19;
  sdatUnitWork_t *v20;
  s16 level;
  int32x2_t *now;
  s32 v23;
  s32 Damage;
  s32 v25;
  s32 v26;
  bool v27;
  s32 v28;
  SBTLUNIT_WORK *pUnit;
  SBTLSKILLP_TBL *v31;
  sdatUnitWork_t *para;
  SBTLSKILLP_TBL *v33;
  SBTLUNIT_WORK *v34;
  SBTLUNIT_WORK *v35;
  u32 attr;
  u32 v37;
  bool v38;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v42;
  s32 v43;
  s32 a_pHanshaType;

  v4 = 0;
  v5 = cond_tp;
  v42 = -1;
  v43 = -1;
  do
  {
    v7 = atkTarget[v4];
    v8 = v7->cond[v5];
    if (v8)
    {
      if (!v8->count)
        goto LABEL_4;
      v7 = atkTarget[v4];
      sklid = v7->sklid;
      Skilltbl = sBtlGetSkilltbl(sklid);
      count = (u32)atkTarget[v4]->cond[v5]->count;
      if ((s32)count >= 1)
      {
        v11 = 0;
        v12 = 8 * count;
        do
        {
          pUnit = atkTarget[v4]->cond[v5]->pUnitL[v11 / 8]->pUnit;
          v31 = sBtlGetSkilltbl(sklid);
          para = pUnit->para;
          v33 = v31;
          v34 = pUnit;
          a_pHanshaType = 0;
          if (para->devilid == 315)
          {
            v35 = sBtlSearchDeivl(260);
            if (v35)
              v34 = v35;
            else
              v34 = pUnit;
          }
          attr = v33->attr;
          v37 = sBtlCheckAisyoEx(v34, attr, &a_pHanshaType);
          if (a_pHanshaType)
            goto LABEL_23;
          v38 = (v37 & 0x1000) == 0 && (v37 & 0x2000) == 0;
          if (!v38 || (v37 & 0x10000) != 0)
            goto LABEL_23;
          v13 = sBtlGetSkilltbl(sklid);
          v14 = Allocate(SBTLDMG_HITWORK);
          _ctor(v14, 0);
          flg = v13->flg;
          v14->skillid = sklid;
          v14->skillflg = flg;
          v17 = *(u32 *)&v13->type;
          v14->workID = 0;
          *(u32 *)&v14->type = v17;
          v14->BEDtype = 1;
          v18 = v14->awk;
          v19 = v13->attr;
          v18->aside = pUnit->side;
          v20 = pUnit->para;
          v14->attr_flg = v19;
          v18->adevilid = v20->devilid;
          v18->aListID = pUnit->ListID;
          level = v20->level;
          now = v20->now;
          v18->alevel = level;
          v23 = now[4].n64_i16[2];
          v18->aatk = now[4].n64_i16[0];
          v18->atec = v23;
          *(float32x2_t *)&v18->ahp = vcvt_f32_s32(now[2]);
          Damage = sBtlGetDamage(wk, pUnit, v14, sklid, v19, 1);
          v25 = v42;
          v26 = Damage * Skilltbl->count;
          v27 = v42 < v26;
          if (v42 <= v26)
            v25 = Damage * Skilltbl->count;
          v28 = v43;
          if (v27)
            v28 = v4;
          v42 = v25;
          v43 = v28;
LABEL_23:
          v11 += 8;
        }
        while (v12 != v11);
      }
    }
LABEL_4:
    ++v4;
  }
  while (v4 != 17);
  return v43;
}

// 0x2035970
static s32 GetMaxShildDmgSkill(s32 cond_tp, SBTLUNIT_WORK *wk) {
  s64 v3;
  s64 v4;
  void **v5;
  s32 v6;
  void *v7;
  s64 v8;
  s64 v9;
  s32 v10;
  s64 v11;
  s64 v12;
  s64 v13;
  s32 v14;
  u64 **v15;
  SBTLUNIT_WORK *v16;
  SBTLSKILLP_TBL *v17;
  sdatUnitWork_t *para;
  SBTLSKILLP_TBL *v19;
  SBTLUNIT_WORK *v20;
  SBTLUNIT_WORK *v21;
  u32 attr;
  u32 v23;
  bool v24;
  void **v25;
  s32 shild_dmg;
  s32 count;
  SBTLSKILLP_TBL *v28;
  SBTLDMG_HITWORK *v29;
  u32 flg;
  s32 v31;
  SBTLCALC_DMGWORK_A *v32;
  u32 v33;
  sdatUnitWork_t *v34;
  s16 level;
  int32x2_t *now;
  s32 v37;
  s32 v38;
  s32 v39;
  s64 v41;
  s32 v43;
  s32 v44;
  s32 v45;
  SBTLSKILLP_TBL *Skilltbl;
  s32 a_pHanshaType;

  LODWORD(v3) = cond_tp;
  v4 = 0;
  v5 = &sBtlAINew;
  v3 = (s32)v3;
  v6 = -1;
  v44 = -1;
  v45 = -1;
  v41 = (s32)v3;
  do
  {
    v7 = *v5;
    if (!*((u32 *)*v5 + 56))
    {
      v7 = *v5;
    }
    v8 = *(u64 *)(**((u64 **)v7 + 23) + 8 * v4 + 32);
    v9 = *(u64 *)(*(u64 *)(v8 + 24) + 8 * v3 + 32);
    if (v9)
    {
      if (*((u32 *)v7 + 56))
      {
        if (!*(u32 *)(v9 + 20))
          goto LABEL_4;
      }
      else
      {
        v7 = *v5;
        v8 = *(u64 *)(**((u64 **)*v5 + 23) + 8 * v4 + 32);
        if (!*(u32 *)(*(u64 *)(*(u64 *)(v8 + 24) + 8 * v3 + 32) + 20))
          goto LABEL_4;
      }
      if (!*((u32 *)v7 + 56))
      {
        v8 = *(u64 *)(**((u64 **)*v5 + 23) + 8 * v4 + 32);
      }
      v10 = *(u32 *)(v8 + 16);
      Skilltbl = sBtlGetSkilltbl(v10);
      v11 = *(u32 *)(*(u64 *)(*(u64 *)(*(u64 *)(**((u64 **)*v5 + 23) + 8 * v4 + 32) + 24) + 8 * v3 + 32) + 20);
      if ((s32)v11 >= 1)
      {
        v12 = 0;
        v13 = 8 * v11;
        do
        {
          v15 = *v5;
          if (!*((u32 *)*v5 + 56))
          {
            v15 = *v5;
          }
          v16 = *(SBTLUNIT_WORK *)(*(u64 *)(*(u64 *)(*(u64 *)(*(u64 *)(*(u64 *)(*v15[23] + 8 * v4 + 32) + 24) + 8 * v3 + 32) + 24) + v12 + 32) + 24);
          v17 = sBtlGetSkilltbl(v10);
          para = v16->para;
          v19 = v17;
          v20 = v16;
          a_pHanshaType = 0;
          if (para->devilid == 315)
          {
            v21 = sBtlSearchDeivl(260);
            if (v21)
              v20 = v21;
            else
              v20 = v16;
          }
          attr = v19->attr;
          v23 = sBtlCheckAisyoEx(v20, attr, &a_pHanshaType);
          if (!a_pHanshaType)
          {
            v24 = (v23 & 0x1000) == 0 && (v23 & 0x2000) == 0;
            if (v24 && (v23 & 0x10000) == 0)
            {
              v25 = v5;
              v43 = v6;
              if (!*((u32 *)*v5 + 56))
              shild_dmg = sBtlGetSkilltbl(v10)->shild_dmg;
              count = Skilltbl->count;
              v28 = sBtlGetSkilltbl(v10);
              v29 = Allocate(SBTLDMG_HITWORK);
              _ctor(v29, 0);
              flg = v28->flg;
              v29->skillid = v10;
              v29->skillflg = flg;
              v31 = *(u32 *)&v28->type;
              v29->workID = 0;
              *(u32 *)&v29->type = v31;
              v29->BEDtype = 1;
              v32 = v29->awk;
              v33 = v28->attr;
              v32->aside = v16->side;
              v34 = v16->para;
              v29->attr_flg = v33;
              v32->adevilid = v34->devilid;
              v32->aListID = v16->ListID;
              level = v34->level;
              now = v34->now;
              v32->alevel = level;
              v37 = now[4].n64_i16[2];
              v32->aatk = now[4].n64_i16[0];
              v32->atec = v37;
              *(float32x2_t *)&v32->ahp = vcvt_f32_s32(now[2]);
              v38 = shild_dmg * count;
              v39 = sBtlGetDamage(wk, v16, v29, v10, v33, 1)
                  * Skilltbl->count;
              if (v45 >= v38)
              {
                v6 = v43;
                v14 = v44;
                if (v45 == v38 && v44 < v39)
                {
                  v14 = v39;
                  v6 = v4;
                }
                v44 = v14;
              }
              else
              {
                v45 = v38;
                v6 = v4;
                v44 = v39;
              }
              v5 = v25;
              v3 = v41;
            }
          }
          v12 += 8;
        }
        while (v13 != v12);
      }
    }
LABEL_4:
    ++v4;
  }
  while (v4 != 17);
  return v6;
}

// 0x2034ec0
static void SetSkillTarget(s32 cond_tp, s32 skilIdx, SBTLUNIT_WORK *wk) {
  s64 v8;
  s64 count;
  SBTLUNIT_WORK *UserData;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *PlayerTarget;
  bool v15;
  s64 v16;
  f32 v17;
  ATK_TARGET *v20;
  SBTLUNIT_WORK *pUnit;
  struct sdfVector4_t v23;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 v29;
  struct sdfVector4_t pos;

  v8 = skilIdx;
  count = (u32)atkTarget[v8]->cond[cond_tp]->count;
  UserData = Support_GetUserData();
  PlayerTarget = sBtlGetPlayerTarget();
  if (atkTarget[v8]->sklid == 149)
  {
    SetAtlTarget(cond_tp, skilIdx, count, UserData, PlayerTarget, v11, wk);
    return;
  }
  if ((s32)count < 1)
    return;
  if (PlayerTarget)
    v15 = UserData == 0;
  else
    v15 = 1;
  if (!v15)
  {
    v16 = 0;
    v17 = -1.0;
    while (1)
    {
      v20 = atkTarget[skilIdx];
      pUnit = v20->cond[cond_tp]->pUnitL[v16]->pUnit;
      if (pUnit)
      {
        if (pUnit->ListID == PlayerTarget->ListID)
        {
          v20 = atkTarget[skilIdx];
          v20->tgtidx = v16;
          return;
        }
        pos = pUnit->pos;
        vct_A = pos;
        v23 = UserData->pos;
        vct_B = v23;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        p_x = &vf00.x;
        x = p_x[4];
        y = p_x[5];
        z = p_x[6];
        v29 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
        if (v17 == -1.0 || v29 < v17)
        {
          v17 = v29;
          atkTarget[skilIdx]->tgtidx = v16;
        }
      }
      if (count == ++v16)
        return;
    }
  }
  do
  {
    LODWORD(count) = count - 1;
  }
  while ((u32)count);
}

// 0x2035da0
static void SetAtlTarget(s32 cond_tp, s32 skilIdx, s32 max, SBTLUNIT_WORK *user, SBTLUNIT_WORK *playerTgt, SBTLUNIT_WORK *tgtwk, SBTLUNIT_WORK *wk) {
  s64 v12;
  s64 v13;
  f32 v14;
  s32 v15;
  f32 v16;
  SBTLUNIT_WORK *pUnit;
  struct sdfVector4_t v21;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  s32 v28;
  s32 v30;
  s32 ListID;
  SBTLSKILLP_TBL *Skilltbl;
  struct sdfVector4_t pos;

  Skilltbl = sBtlGetSkilltbl(149);
  if (max >= 1)
  {
    v12 = 0;
    v13 = skilIdx;
    v14 = -1.0;
    v15 = -1;
    ListID = -1;
    do
    {
      pUnit = atkTarget[v13]->cond[cond_tp]->pUnitL[v12]->pUnit;
      if (!!ChkMukouSkill(149, pUnit))
      {
        pos = pUnit->pos;
        vct_A = pos;
        v21 = user->pos;
        vct_B = v21;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        p_x = &vf00.x;
        x = p_x[4];
        y = p_x[5];
        z = p_x[6];
        v16 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
        v28 = GetDamage(wk, pUnit, 149) * Skilltbl->count;
        if (v15 < v28)
        {
          v15 = v28;
          atkTarget[v13]->tgtidx = v12;
          ListID = pUnit->ListID;
          goto LABEL_6;
        }
        if (v15 == v28)
        {
          v30 = playerTgt->ListID;
          if (ListID != v30)
          {
            if (pUnit->ListID == v30)
            {
              v16 = v14;
              atkTarget[v13]->tgtidx = v12;
              goto LABEL_6;
            }
            if (v14 == -1.0 || v16 < v14)
            {
              atkTarget[v13]->tgtidx = v12;
              goto LABEL_6;
            }
          }
        }
      }
      v16 = v14;
LABEL_6:
      v14 = v16;
      ++v12;
    }
    while (max != v12);
  }
}

// 0x2033df0
static bool FoundKabe(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtWk) {
  SBTLAI_WORK *aiwk;
  s64 v7;
  s32 v8;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v11;
  s32 para;
  u32 attr;
  s32 Damage;
  s32 count;
  s32 v16;
  SBTLAI_WORK *v17;
  s32 ListID;
  SBTLAI_WORK *v19;
  s32 v20;
  SBTLAI_WORK *v21;
  s32 v23;
  s32 a_pHanshaType;

  aiwk = wk->aiwk;
  a_pHanshaType = 0;
  aiwk->dfltOdrTgt = -1;
  if (!tgtWk)
    return 0;
  if ((u32)(tgtWk->para->devilid - 188) > 0x18)
    return 0;
  v7 = 32;
  v23 = -1;
  do
  {
    v8 = *(u32 *)((char *)&wk->para->haveskill->obj.klass + v7);
    Skilltbl = sBtlGetSkilltbl(v8);
    if (v8)
    {
      if (v8 != 288)
      {
        v11 = Skilltbl;
        if ((Skilltbl->s_type & 0x10) != 0 && (Skilltbl->flg & 1) != 0)
        {
          para = Skilltbl->para;
          if (wk->mag < para)
            goto LABEL_10;
          a_pHanshaType = 0;
          attr = v11->attr;
          Damage = GetDamage(wk, tgtWk, v8);
          count = v11->count;
          v16 = Damage;
          if ((sBtlCheckAisyoEx(tgtWk, attr, &a_pHanshaType) & 0x1000) != 0)
            goto LABEL_10;
          if (v23 < v16 * count)
          {
            v23 = v16 * count;
            wk->actwk->use_skillid = v8;
            v17 = wk->aiwk;
            ListID = tgtWk->ListID;
            v17->dfltOdrSkl = v8;
            v17->dfltOdrTgt = ListID;
          }
          if (tgtWk->para->now->hp - v16 * count <= 0 && v11->para <= 998)
          {
            wk->actwk->use_skillid = v8;
            v19 = wk->aiwk;
            v20 = tgtWk->ListID;
            v19->dfltOdrSkl = v8;
            v19->dfltOdrTgt = v20;
            return 1;
          }
        }
      }
    }
LABEL_10:
    v7 += 4;
  }
  while (v7 != 100);
  v21 = wk->aiwk;
  if (v21->dfltOdrTgt == -1)
    return 0;
  v21->dfltOdrStk = -1;
  sBtlCheckTargetEquation(wk);
  return 1;
}

// 0x2034240
SBTLUNIT_LISTWORK *sBtlCreateTargetList_DeadDamage(SBTLUNIT_WORK *acterwk, SBTLUNIT_SIDE side, SKLID sklid) {
  SBTLSKILLP_TBL *Skilltbl;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 Damage;
  sdatUnitWork_t *para;
  s32 v13;
  u32 attr;
  SBTLAISYO_DATAWORK *aisyo;
  s32 hp;
  s32 v17;
  SBTLUNIT_LISTWORK *lwk;

  lwk = sBtlCreateUnitList(48);
  Skilltbl = sBtlGetSkilltbl(sklid);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) != side)
      continue;
    if (!sBtlCheckDamageTarget(pUnit))
      continue;
    if (pUnit->para->devilid != 314)
    {
      Damage = GetDamage(acterwk, pUnit, sklid);
      para = pUnit->para;
      v13 = Damage;
      attr = Skilltbl->attr;
      aisyo = para->aisyo;
      hp = para->now->hp;
      v17 = hp - v13;
      if ((sBtlCheckAisyo_Old(aisyo, attr) & 0x3000) != 0)
      {
        if ((Skilltbl->flg & 0x10000) == 0 || v17 >= 1)
          continue;
      }
      else if (v17 > 0)
      {
        continue;
      }
      sBtlEntryUnitList(lwk, pUnit);
    }
  }
  return lwk;
}

// 0x2034710
SBTLUNIT_LISTWORK *sBtlCreateTargetList_WeakAtk(SBTLUNIT_SIDE side, SKLID sklid, bool shild) {
  SBTLSKILLP_TBL *Skilltbl;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  s32 devilid;
  SBTLAISYO_DATAWORK *aisyo;
  u32 attr;
  s32 weak_shild;
  SBTLUNIT_LISTWORK *lwk;

  lwk = sBtlCreateUnitList(48);
  Skilltbl = sBtlGetSkilltbl(sklid);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) != side)
      continue;
    para = pUnit->para;
    devilid = (u16)para->devilid;
    if (devilid != 260)
    {
      if (devilid == 315)
        continue;
      if (!sBtlCheckDamageTarget(pUnit))
        continue;
      para = pUnit->para;
    }
    aisyo = para->aisyo;
    attr = Skilltbl->attr;
    if ((sBtlCheckAisyo_Old(aisyo, attr) & 0x4000) == 0)
      continue;
    weak_shild = pUnit->weak_shild;
    if (shild)
    {
      if (!weak_shild)
        continue;
    }
    else if (weak_shild)
    {
      continue;
    }
    sBtlEntryUnitList(lwk, pUnit);
  }
  return lwk;
}

// 0x2036230
static bool WeakCheckDamageTarget(SBTLUNIT_WORK *wk) {
  s32 devilid;

  devilid = (u16)wk->para->devilid;
  if (devilid == 260)
    return 1;
  if (devilid == 315)
    return 0;
  return sBtlCheckDamageTarget(wk);
}

// 0x20349a0
static bool IsWeakSkill(SBTLUNIT_WORK *acterwk) {
  u64 v3;
  char v4;
  s32 v6;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v8;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 attr;
  SBTLAISYO_DATAWORK *aisyo;

  v3 = 0;
  v4 = 1;
  do
  {
    v6 = acterwk->para->haveskill[v3];
    Skilltbl = sBtlGetSkilltbl(v6);
    if (v6)
    {
      if (v6 != 149 && v6 != 288)
      {
        v8 = Skilltbl;
        if ((Skilltbl->flg & 1) != 0 && (Skilltbl->type & 0x1000) == 0)
        {
          for (i = 0; ; ++i)
          {
            UnitMng = wk->UnitMng;
            if (i >= UnitMng->number)
              break;
            pUnit = UnitMng->pUnitL[i]->pUnit;
            if (!pUnit)
              continue;
            if ((pUnit->side & 0x3F) != 2)
              continue;
            if (!sBtlCheckDamageTarget(pUnit))
              continue;
            attr = v8->attr;
            aisyo = pUnit->para->aisyo;
            if ((sBtlCheckAisyo_Old(aisyo, attr) & 0x4000) != 0)
              return v4;
          }
        }
      }
    }
    v4 = v3++ < 0x10;
  }
  while (v3 != 17);
  return v4;
}

// 0x20344b0
SBTLUNIT_LISTWORK *sBtlCreateTargetList_HST(SBTLUNIT_SIDE side, SBTLUNIT_HST mask_hst) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 j;
  SBTLUNIT_LISTWORK *v12;
  SBTLUNIT_WORK *v13;

  UnitList = sBtlCreateUnitList(48);
  if (mask_hst)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return UnitList;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x3F) != side)
        continue;
      if (!sBtlCheckDamageTarget(pUnit))
        continue;
      if ((pUnit->hstatus & mask_hst) != 0)
      {
        sBtlEntryUnitList(UnitList, pUnit);
      }
    }
  }
  for (j = 0; ; ++j)
  {
    v12 = wk->UnitMng;
    if (j >= v12->number)
      break;
    v13 = v12->pUnitL[j]->pUnit;
    if (!v13)
      continue;
    if ((v13->side & 0x3F) == side)
    {
      sBtlCheckDamageTarget(v13);
    }
  }
  return UnitList;
}

// 0x2034b90
SBTLUNIT_LISTWORK *sBtlCreateTargetList_RaidouTarget(SBTLUNIT_SIDE side, bool shild) {
  SBTLUNIT_LISTWORK *UnitList;
  SBTLUNIT_WORK *PlayerTarget;
  SBTLUNIT_WORK *v8;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 weak_shild;

  UnitList = sBtlCreateUnitList(48);
  PlayerTarget = sBtlGetPlayerTarget();
  if (!PlayerTarget)
    return UnitList;
  goto LABEL_9;
  if (PlayerTarget)
  {
LABEL_9:
    v8 = PlayerTarget;
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return UnitList;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x3F) != side)
        continue;
      if (!sBtlCheckDamageTarget(pUnit))
        continue;
      if (pUnit->ListID == v8->ListID)
      {
        weak_shild = pUnit->weak_shild;
        if (shild)
        {
          if (!weak_shild)
            continue;
        }
        else if (weak_shild)
        {
          continue;
        }
        sBtlEntryUnitList(UnitList, pUnit);
      }
    }
  }
  return UnitList;
}

// 0x2032240
static s32 ParamUpChk(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  s64 v7;
  s32 v8;
  SBTLUNIT_WORK *pUnit;
  u32 flg;
  SBTLUNIT_LISTWORK *friend_List;

  if (ParamUpSame(wk, skillid))
  {
    Skilltbl = sBtlGetSkilltbl(skillid);
    v7 = 0;
    v8 = -1;
    while (1)
    {
      friend_List = wk->friend_List;
      if (v7 >= friend_List->count)
        return v8;
      pUnit = friend_List->pUnitL[v7]->pUnit;
      if (!pUnit)
        goto LABEL_25;
      if (!sBtlCheckDamageTarget(pUnit))
        goto LABEL_25;
      flg = Skilltbl->flg;
      if ((flg & 0x20) != 0)
      {
        if ((flg & 0x400000) != 0)
        {
          if (sBtlCheckEnableUseKajaNewAI(pUnit, skillid) >= 1)
            return pUnit->ListID;
        }
        else if ((flg & 0x7000000) != 0)
        {
          if (sBtlCheckEnableUseAura(pUnit, skillid) >= 1)
            return pUnit->ListID;
        }
        else if (pUnit->wkKarn[0]->m_cnt < 1)
        {
          return pUnit->ListID;
        }
      }
LABEL_25:
      ++v7;
    }
  }
  return -1;
}

// 0x20362e0
static bool ParamUpSame(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v5;
  SBTLUNIT_WORK *Nakama;
  SBTLSKILLP_TBL *v7;
  u32 flg;
  SBTLUNIT_WORK *v9;
  SBTLSKILLP_TBL *v10;
  u32 v11;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if (Skilltbl)
  {
    v5 = Skilltbl;
    LOBYTE(Skilltbl) = (Skilltbl->flg & 0x20) == 0
                    || ((Nakama = sBtlGetNakama(0)) == 0 || wk->ListID == Nakama->ListID || (v7 = sBtlGetSkilltbl(Nakama->actwk->order_skillid)) == 0 || ((flg = v5->flg, (flg & 0x1000000) == 0) || (v7->flg & 0x1000000) == 0) && ((flg & 0x2000000) == 0 || (v7->flg & 0x2000000) == 0) && ((flg & 0x4000000) == 0 || (v7->flg & 0x4000000) == 0) && ((flg & 0x40000000) == 0 || (v7->flg & 0x40000000) == 0))
                    && ((v9 = sBtlGetNakama(1)) == 0 || wk->ListID == v9->ListID || (v10 = sBtlGetSkilltbl(v9->actwk->order_skillid)) == 0 || ((v11 = v5->flg, (v11 & 0x1000000) == 0) || (v10->flg & 0x1000000) == 0) && ((v11 & 0x2000000) == 0 || (v10->flg & 0x2000000) == 0) && ((v11 & 0x4000000) == 0 || (v10->flg & 0x4000000) == 0) && ((v11 & 0x40000000) == 0 || (v10->flg & 0x40000000) == 0));
  }
  return (char)Skilltbl;
}

// 0x2031bf0
static SBTLUNIT_WORK *GetGuardTarget(SBTLUNIT_WORK *pwk) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 v8;
  s64 v9;
  s32 v10;
  f32 v12;
  SBTLUNIT_WORK *v13;
  struct sdfVector4_t v15;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  struct sdfVector4_t pos;

  UnitList = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) != 2)
      continue;
    if (!sBtlCheckDamageTarget(pUnit))
      continue;
    if (pUnit->actaiwk->targetID == pwk->ListID)
    {
      sBtlEntryUnitList(UnitList, pUnit);
    }
  }
  if (UnitList->count < 2)
    return 0;
  v8 = 100000000.0;
  v9 = 0;
  v10 = -1;
  while (2)
  {
    v13 = UnitList->pUnitL[v9]->pUnit;
    pos = pwk->pos;
    vct_A = pos;
    v15 = v13->pos;
    goto LABEL_34;
LABEL_35:
    goto LABEL_36;
LABEL_37:
    goto LABEL_38;
LABEL_34:
    vct_B = v15;
    goto LABEL_35;
LABEL_36:
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    goto LABEL_37;
LABEL_38:
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    v12 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
    if (v8 > v12)
    {
      v8 = v12;
      v10 = v9;
    }
    if (++v9 < UnitList->count)
      continue;
    break;
  }
  if (v10 != -1)
    return UnitList->pUnitL[v10]->pUnit;
  return 0;
}

// 0x2031830
static bool SetNakamaGuard(SBTLUNIT_WORK *wk, bool target_user) {
  char *GuardTarget;
  SBTLUNIT_WORK *PChara;
  char *v9;
  s64 v11;
  struct sdfVector4_t v13;
  long f64 v14;
  f32 v15;
  sdfVector4_t *p_rot;
  struct sdfVector4_t v17;
  float32x2_t v18;
  float32x2_t v19;
  struct sdfVector4_t pos;

  if (wk->actwk->status == 59)
  {
    LOBYTE(GuardTarget) = 0;
    return (char)GuardTarget;
  }
  PChara = wk;
  if (target_user)
  {
    PChara = sBtlGetPChara();
LABEL_8:
    GuardTarget = GetGuardTarget(PChara);
    if (!GuardTarget)
      return (char)GuardTarget;
    goto LABEL_12;
  }
  else
  {
    goto LABEL_8;
  }
  GuardTarget = GetGuardTarget(PChara);
  if (!GuardTarget)
    return (char)GuardTarget;
LABEL_12:
  v9 = GuardTarget;
  if (target_user)
  {
    v18.n64_u64[0] = *(u64 *)&PChara->pos.x;
    v19.n64_u64[0] = vmul_f32(vsub_f32(*(float32x2_t *)(GuardTarget + 164), v18), (float32x2_t)0x3F0000003F000000LL).n64_u64[0];
    wk->pos.z = PChara->pos.z
                            + (f32)((f32)(*((f32 *)GuardTarget + 43) - PChara->pos.z) * 0.5);
    *(float32x2_t *)&wk->pos.x = vadd_f32(v18, v19);
    if (wk->motionID == 29)
    {
LABEL_14:
      goto LABEL_15;
    }
  }
  else if (wk->motionID == 29)
  {
    goto LABEL_14;
  }
  sBtlSetMotion(wk, 29, 6, 0, 0);
LABEL_15:
  sBtlSetAction(wk, 59, 0);
  pos = wk->pos;
  vct_A = pos;
  v13 = *(sdfVector4_t *)(v9 + 164);
  vct_B = v13;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v14 = sub_18E6660(0, v11);
  v15 = *(f32 *)&v14;
  FromEuler(0.0, *(f32 *)&v14, 0.0);
  p_rot = &wk->rot;
  v17 = *(sdfVector4_t *)(*((u64 *)GuardTarget + 23) + 16);
  wk->mv_rotbk = v15;
  *p_rot = v17;
  LOBYTE(GuardTarget) = 1;
  return (char)GuardTarget;
}

// 0x20317c0
static bool IsNakamaGuard(void) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v3;

  Nakama = sBtlGetNakama(0);
  if (Nakama && Nakama->actwk->status == 59)
    return 1;
  v3 = sBtlGetNakama(1);
  return v3 && v3->actwk->status == 59;
}

// 0x2033770
static bool UseJudgRecoverAll(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBATTLE_WORK *v8;
  SBTLUNIT_LISTWORK *TargetList;
  s64 v10;
  s32 v11;
  s32 v12;
  s32 Damage;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 hp;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_WORK *pUnit;
  s64 i;
  s32 v22;
  sdatUnitWork_t *v25;
  SBTLUNIT_WORK *UnitWork;
  s32 v29;
  sdatParaWork_t *v30;
  s32 v31;
  s32 v32;
  sdatParaWork_t *v33;

  v8 = wk;
  TargetList = sBtlCreateTargetList(1);
  v8->friend_List = TargetList;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  while (1)
  {
    friend_List = wk->friend_List;
    if (v10 >= friend_List->count)
      break;
    pUnit = friend_List->pUnitL[v10]->pUnit;
    if (!pUnit)
      goto LABEL_9;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_9;
    Damage = GetDamage(wk, pUnit, sklid);
    now = pUnit->para->now;
    hp = now->hp;
    maxhp = now->maxhp;
    if (hp + Damage <= maxhp)
      ++v12;
    if (hp <= maxhp / 2)
      ++v11;
LABEL_9:
    ++v10;
  }
  for (i = 0; ; ++i)
  {
    if (i >= datGetStockDevilNums(0))
      break;
    if (wk->summonID[i])
      continue;
    v25 = GBWK->player->stock_id[i];
    if (v25)
    {
      if (v25->badstatus == 0x20000)
        continue;
      UnitWork = CreateUnitWork(v25, i);
      v29 = GetDamage(wk, UnitWork, sklid);
      v30 = GBWK->player->stock_id[i]->now;
      v31 = v30->hp;
      v32 = v30->maxhp;
      if (v31 + v29 <= v32)
        ++v12;
      v33 = GBWK->player->stock_id[i]->now;
      v31 = v33->hp;
      v32 = v33->maxhp;
      if (v32 >= 0)
        v22 = v32;
      else
        v22 = v32 + 1;
      if (v31 <= v22 >> 1)
        ++v11;
      continue;
    }
  }
  return v12 > 1 || v11 > 1;
}

// 0x2036400
static SBTLUNIT_WORK *CreateUnitWork(sdatUnitWork_t *unit, s32 tubeNo) {
  s32 v6;
  s32 minorno;
  SBTLUNIT_WORK *v8;
  SBTLACTAI_WORK *actaiwk;

  v6 = wk->stock_id[tubeNo];
  minorno = sBtlGetDevilData(v6, -1)->minorno;
  v8 = sBtlCreateUnit(1u, minorno, 0);
  v8->para = unit;
  actaiwk = v8->actaiwk;
  v8->side = 1;
  actaiwk->targetID = -1;
  return v8;
}

// 0x2036520
void sBtlDestroyTarget(void) {
  s64 v2;
  s64 i;
  ATK_TARGET *atkTarget_local;

  if (!atkTarget)
    return;
  v2 = 0;
  for (i = 32; ; i += 8)
  {
    atkTarget_local = atkTarget;
    if (v2 >= SLODWORD(atkTarget->max_length))
      break;
    if (!!*(Il2CppClass **)((char *)&atkTarget_local->obj.klass + i))
    {
      atkTarget_local = atkTarget;
      *(Il2CppClass **)((char *)&atkTarget_local->obj.klass + i) = 0;
    }
    ++v2;
  }
  atkTarget = 0;
}

// 0x2036200
static bool IsKabe(SBTLUNIT_WORK *wklock) {
  return wklock && (u32)(wklock->para->devilid - 188) < 0x19;
}
