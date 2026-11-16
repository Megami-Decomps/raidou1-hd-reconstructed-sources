#include "types.h"
#include "AUTO.h"
#include "SKLID.h"
#include "cfg.h"
#include "itf.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlai.h"
#include "sbtlainew.h"
#include "sbtlcalc.h"
#include "sbtlcommand.h"
#include "sbtldmg.h"
#include "sbtlequat.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "smnr.h"

#define D_BYCT_PER 3
#define D_BYCT_CNT 1800

typedef struct SBTLAI_WORK SBTLAI_WORK;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

typedef bool (*sBtlAI_SkillEquationFuncDelegate)(SBTLUNIT_WORK *UnnamedParameter, s32 UnnamedParameter2);

static s32 boss_proc_timer;
static sBtlAI_SkillEquationFuncDelegate *sBtlAI_SkillEquationFunc;

static void ChangeTarget_BSHelper(SBTLUNIT_WORK *wk);
static void SetBSHelper(SBTLUNIT_WORK *wk);
static bool CheckActionEquation(SBTLUNIT_WORK *wk);
static s16 GetSkill_Geta(SKLID skillid);
static bool CheckAIScript(SBTLUNIT_WORK *wk);
static bool IsKaja(SBTLUNIT_WORK *pBtlUnit, SBTLSKILLP_TBL *ptbl);
static bool IsEnemyZenmetsu(void);
static bool Tuto(void);
static void SetATK(SBTLUNIT_WORK *wk);
static bool CheckBSTTarget(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl);
static s16 GetMeireiNo(SBTLUNIT_WORK *wk);
static bool SEquationno_00(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_01(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_02(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_03(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_04(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_05(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_06(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_07(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_08(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_09(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_0a(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_0b(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_0c(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_0d(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_0e(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_0f(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_10(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_11(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_12(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_13(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_14(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_15(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_16(SBTLUNIT_WORK *wk, SKLID skillid);
static bool SEquationno_17(SBTLUNIT_WORK *wk, SKLID skillid);
static bool TEquationno_01(SBTLUNIT_WORK *wk);
static bool TEquationno_0c(SBTLUNIT_WORK *wk);
static bool TEquationno_0d(SBTLUNIT_WORK *wk);
static bool TEquationno_0e(SBTLUNIT_WORK *wk);
bool CheckAutono(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, AUTO autono);
bool SetOrderTarget(SBTLUNIT_WORK *wk);
bool SetNextTarget(SBTLUNIT_WORK *wk);
bool CheckEnemyTarget(SBTLUNIT_WORK *wk);

// 0x1ecd0d0
static void ChangeTarget_BSHelper(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 v7;
  s64 v8;
  SBTLUNIT_WORK *v9;
  struct sdfVector4_t v11;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 v17;
  SBTLUNIT_WORK *v19;
  s32 v21;
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
    if (pUnit->para->devilid == 314 && (pUnit->status & 0x800) != 0)
    {
      sBtlEntryUnitList(UnitList, pUnit);
    }
  }
  if (UnitList->count < 1)
  {
    goto LABEL_52;
  }
  v21 = -1;
  v7 = 30000.0;
  v8 = 0;
  while (2)
  {
    v9 = UnitList->pUnitL[v8]->pUnit;
    if (v9)
    {
      pos = v9->pos;
      vct_A = pos;
      v11 = wk->pos;
      goto LABEL_28;
LABEL_29:
      goto LABEL_30;
LABEL_31:
      goto LABEL_32;
LABEL_33:
      goto LABEL_34;
LABEL_28:
      vct_B = v11;
      goto LABEL_29;
LABEL_30:
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      goto LABEL_31;
LABEL_32:
      p_x = &vf00.x;
      x = p_x[4];
      y = p_x[5];
      z = p_x[6];
      goto LABEL_33;
LABEL_34:
      v17 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
      if (v7 >= v17)
      {
        v7 = v17;
        v21 = v8;
      }
    }
    if (++v8 < UnitList->count)
      continue;
    break;
  }
  if (v21 != -1)
  {
    v19 = UnitList->pUnitL[v21]->pUnit;
    if (v19)
      wk->actaiwk->targetID = v19->ListID;
  }
LABEL_52:
  sBtlDeleteUnitList(UnitList, 0);
}

// 0x1ecd510
static void SetBSHelper(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v6;

  UnitMng = wk->UnitMng;
  targetID = wk->actaiwk->targetID;
  v6 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v6)
    return;
  if (v6->para->devilid == 314 && (v6->status & 0x800) != 0)
  {
    ChangeTarget_BSHelper(wk);
  }
}

// 0x1ecd640
static bool CheckActionEquation(SBTLUNIT_WORK *wk) {
  s64 v3;
  SKLID *haveskill;
  s64 v5;
  il2cpp_array_size_t max_length;
  u64 v7;
  u64 v8;
  _OWORD *v9;
  s32 *v10;
  u64 v11;
  __int128 v12;
  __int128 v13;
  __int128 v14;
  __int128 v15;
  char v16;
  u64 v17;
  u64 v18;
  s64 v19;
  u32 *v20;
  s32 *v21;
  s32 v22;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBATTLE_WORK *v26;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v29;
  s64 v30;
  s64 v31;
  SBTLAI_WORK *aiwk;
  s64 v33;
  s32 v34;
  s64 v35;
  s64 v36;
  s16 v37;
  s32 v39;
  s16 *aibuff;
  char *v41;
  s16 v42;
  SBTLAI_WORK *v46;
  s16 *airnd;
  s64 dfltOdrSkl;
  u32 chuusei;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 priv_area_r;
  bool v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  s64 v62;
  bool result;
  SBTLAI_WORK *v64;
  s32 motionID;
  SBTLAI_WORK *v67;
  SBTLACTION_WORK *actwk;
  SBTLSKILLP_TBL *v70;
  s32 v71;
  s32 v72;
  u32 v73;
  u16 Percentage;
  SBTLAI_WORK *v76;
  void *wkBarrier;
  s32 v78;
  char v79;
  s32 klass_high;
  tagSBTLSKL_AURA_WORK *wkAura;
  s32 use_skillid;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v84;
  s32 v85;
  SBTLAI_WORK *v86;
  s16 v87;
  s32 v88;
  SBTLAI_WORK *v89;
  s16 v90;
  s32 v91;
  SBTLAI_WORK *v92;
  s32 v93;
  u16 v94;
  u16 v95;
  s16 v96;
  s32 v97;
  s32 v98;
  sdfVector4_t v99;
  sdfVector4_t v100;

  v3 = NewSpecific(SKLID, 0x13u);
  haveskill = wk->haveskill;
  v5 = v3;
  max_length = haveskill->max_length;
  if ((s32)max_length >= 1)
  {
    v7 = (u32)haveskill->max_length;
    v8 = 0;
    if (v7 < 0x10)
      goto LABEL_9;
    if ((u64)(v3 - (u64)haveskill) < 0x40)
      goto LABEL_9;
    v9 = (v3 + 80);
    v10 = &haveskill[4];
    v8 = v7 - (haveskill->max_length & 0xF);
    v11 = v8;
    do
    {
      v12 = *((_OWORD *)v10 - 1);
      v13 = *(_OWORD *)v10;
      v11 -= 16;
      v14 = *((_OWORD *)v10 + 1);
      v15 = *((_OWORD *)v10 + 2);
      v10 += 16;
      *(v9 - 3) = v12;
      *(v9 - 2) = v13;
      *(v9 - 1) = v14;
      *v9 = v15;
      v9 += 4;
    }
    while (v11);
    if ((max_length & 0xF) != 0)
    {
LABEL_9:
      v16 = max_length - v8;
      v17 = v8 + 1;
      if ((v16 & 1) != 0)
      {
        *(u32 *)(v3 + 4 * v8 + 32) = haveskill[v8];
        ++v8;
      }
      if (v7 != v17)
      {
        v18 = v7 - v8;
        v19 = 4 * v8 + 36;
        v20 = (v3 + v19);
        v21 = ((char *)haveskill + v19);
        do
        {
          v18 -= 2;
          *(v20 - 1) = *(v21 - 1);
          v22 = *v21;
          v21 += 2;
          *v20 = v22;
          v20 += 2;
        }
        while (v18);
      }
    }
  }
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  v26 = wk;
  UnitMng = v26->UnitMng;
  playerID = v26->playerID;
  v29 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v29)
  {
    if (v29->actwk->status != 42)
    {
      if ((wk->status & 0x1000000) == 0 && BadStatus == 8 && GetPercentage() <= 4u)
      {
        wk->aiwk->mode = 18;
        goto LABEL_128;
      }
    }
  }
  v30 = 0;
  v31 = v5 + 32;
  v96 = 0;
  v97 = 0;
  v98 = 0xFFFF;
  do
  {
    aiwk = wk->aiwk;
    v33 = v30;
    v34 = *(u32 *)(v31 + 4 * v30);
    v35 = (s64)aiwk->aibuff + 2 * v30;
    v36 = (s64)aiwk->airnd + 2 * v30;
    *(u16 *)(v35 + 32) = 0;
    *(u16 *)(v36 + 32) = 0;
    if ((sBtlGetSkilltbl(v34)->flg2 & 1) == 0 && (sBtlGetSkilltbl(*(u32 *)(v31 + 4 * v30))->flg2 & 2) == 0 && (sBtlGetSkilltbl(*(u32 *)(v31 + 4 * v30))->flg & 0x200) == 0)
    {
      v39 = *(u32 *)(v31 + 4 * v30);
      aibuff = wk->aiwk->aibuff;
      if (!v39)
      {
        aibuff[v30] = -1;
        goto LABEL_25;
      }
      v41 = (char *)aibuff + 2 * v30;
      v42 = *((u16 *)v41 + 16);
      *((u16 *)v41 + 16) = v42;
      if (!sBtlCheckSkillEquation(wk, v37, v39))
        goto LABEL_25;
      v46 = wk->aiwk;
      if (v46->aibuff[v30] != -1)
      {
        airnd = v46->airnd;
        airnd[v33] = GetIntervalRand(0, 7);
        wk->aiwk->aibuff[v33] += wk->aiwk->airnd[v33];
        dfltOdrSkl = wk->aiwk->dfltOdrSkl;
        if ((tbldata[dfltOdrSkl]->flg & 4) != 0 && *(u32 *)(v31 + 4 * v30) == (u32)dfltOdrSkl)
        {
          v96 = v30;
          v97 = 1;
          v98 = 1;
        }
        goto LABEL_25;
      }
    }
LABEL_25:
    ++v30;
  }
  while (v30 != 19);
  if ((wk->side & 1) == 0 || !wk->miusinai && (wk->aiwk->m_status & 0x40000) == 0)
  {
LABEL_43:
    if (BadStatus - 7 < 2)
    {
      wk->panelwk->data[0]->meirei_no = 7;
      goto LABEL_47;
    }
    v67 = wk->aiwk;
    wk->panelwk->data[0]->meirei_no = v67->meirei_nobk;
    if ((v67->status & 1) == 0 && !v67->cmndFrm)
    {
LABEL_47:
      chuusei = (u16)wk->para->chuusei;
      if (GetPercentage() < (s16)(chuusei + (chuusei >> 15)) >> 1)
      {
        x = wk->pos.x;
        y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        priv_area_r = wk->actaiwk->priv_area_r;
        v99.x = x;
        v99.y = y;
        v99.z = z;
        v99.w = w;
        v57 = sBtlCheckArea_Atk(wk, v99, priv_area_r + priv_area_r);
        v58 = wk->pos.x;
        v59 = wk->pos.y;
        v60 = wk->pos.z;
        v61 = wk->pos.w;
        v100.x = v58;
        v100.y = v59;
        v100.z = v60;
        v100.w = v61;
        if (sBtlCheckArea_Masic(wk, v100, 2000.0, 0) != -1 || v57)
        {
          wk->actwk->use_skillid = 0;
          wk->aiwk->mode = 17;
LABEL_128:
          result = 1;
          wk->actaiwk->stat = 1;
          return result;
        }
      }
      if (BadStatus == 8)
        v72 = 25;
      else
        v72 = 3;
      if (wk->byctCnt)
        v73 = 25;
      else
        v73 = v72;
      if (v73 > GetPercentage())
      {
        Percentage = GetPercentage();
        wk->actwk->use_skillid = 0;
        v76 = wk->aiwk;
        if (Percentage <= 0x31u)
          v76->mode = 12;
        else
          v76->mode = 11;
        goto LABEL_128;
      }
      wkBarrier = wk->wkBarrier;
      if (wkBarrier->_size < 1)
        goto LABEL_106;
      v78 = 0;
      v79 = 0;
      do
      {
        klass_high = HIDWORD(_get_Item(wkBarrier, v78++)[1].klass);
        wkBarrier = wk->wkBarrier;
        v79 |= klass_high > 0;
      }
      while (v78 < wkBarrier->_size);
      if ((v79 & 1) == 0)
      {
LABEL_106:
        if (wk->enchantcnt <= 0 && wk->bulletcnt <= 0)
        {
          wkAura = wk->wkAura;
          if (wkAura[0]->auracnt <= 0 && wkAura[1]->auracnt <= 0 && wkAura[2]->auracnt < 1)
          {
            if (wk->byctCnt)
            {
              do
                v93 = *(u32 *)(v5 + 4 * (s32)sub_1905740(19, 0) + 32);
              while (!v93);
              wk->actwk->use_skillid = v93;
              wk->aiwk->dfltOdrTgt = -1;
            }
            else
            {
              if (v98 == 0xFFFF)
                return 0;
              if (v97 == 1)
              {
                wk->actwk->use_skillid = *(u32 *)(v5 + 4 * v96 + 32);
              }
              else
              {
                v94 = GetPercentage();
                wk->actwk->use_skillid = 0;
                if (v94 <= 0x31u)
                  v95 = 12;
                else
                  v95 = 11;
                wk->aiwk->mode = v95;
                wk->actaiwk->stat = 1;
              }
            }
            sBtlSetAIMode(wk);
            goto LABEL_128;
          }
        }
      }
      use_skillid = 149;
      wk->actwk->use_skillid = 149;
      wk->actaiwk->stat = 1;
      use_skillid = wk->actwk->use_skillid;
      Skilltbl = sBtlGetSkilltbl(use_skillid);
      v84 = wk->actwk->use_skillid;
      if (v84 == 288 || !v84)
      {
        wk->aiwk->mode = 0;
        return 1;
      }
      if ((Skilltbl->type & 0xFFFu) <= 0x10)
      {
        v88 = 1 << LOBYTE(Skilltbl->type);
        if ((v88 & 0x1CE2C) != 0)
        {
          v89 = wk->aiwk;
          v90 = 8;
LABEL_132:
          v89->mode = v90;
          v89->scrflag |= 0x10000u;
LABEL_133:
          wk->NakamaAtkFormationUse = 0;
          return 1;
        }
        if ((v88 & 0x3012) != 0)
        {
          v89 = wk->aiwk;
          v90 = 1;
          goto LABEL_132;
        }
      }
      wk->aiwk->mode = 0;
      goto LABEL_133;
    }
    actwk = wk->actwk;
    if (BadStatus != 10)
    {
      actwk->use_skillid = actwk->order_skillid;
      if (sBtlCheckCost(wk, 0))
      {
LABEL_86:
        v70 = sBtlGetSkilltbl(wk->actwk->use_skillid);
        v71 = wk->actwk->use_skillid;
        if (v71 == 288 || !v71)
        {
          wk->aiwk->mode = 0;
          goto LABEL_128;
        }
        if ((v70->type & 0xFFFu) <= 0x10)
        {
          v85 = 1 << LOBYTE(v70->type);
          if ((v85 & 0x1CE2C) != 0)
          {
            v86 = wk->aiwk;
            v87 = 8;
LABEL_127:
            v86->mode = v87;
            v91 = v86->scrflag | 0x10000;
            wk->NakamaAtkFormationUse = 0;
            v86->scrflag = v91;
            goto LABEL_128;
          }
          if ((v85 & 0x3012) != 0)
          {
            v86 = wk->aiwk;
            v87 = 1;
            goto LABEL_127;
          }
        }
        v92 = wk->aiwk;
        wk->NakamaAtkFormationUse = 0;
        v92->mode = 0;
        goto LABEL_128;
      }
      actwk = wk->actwk;
    }
    actwk->use_skillid = 149;
    goto LABEL_86;
  }
  if (v98 != 0xFFFF)
  {
    wk->actwk->use_skillid = *(u32 *)(v5 + 4 * v96 + 32);
    v62 = wk->aiwk->dfltOdrSkl;
    if ((tbldata[v62]->flg & 4) != 0 && wk->actwk->use_skillid == (u32)v62 && BadStatus != 10 && !wk->byctCnt)
    {
      goto LABEL_43;
    }
  }
  if (BadStatus > 0x16 || ((1 << BadStatus) & 0x600E00) == 0)
    goto LABEL_43;
  result = 1;
  wk->actwk->use_skillid = 0;
  v64 = wk->aiwk;
  if (v64->mode)
  {
    v64->mode = 0;
    wk->actaiwk->stat = 1;
    if (wk->miusinai)
    {
      motionID = wk->motionID;
      if (motionID)
      {
        if (motionID != 5)
        {
          sBtlSetMotion(wk, 5, 4, 0, 0);
          return 1;
        }
      }
    }
  }
  return result;
}

// 0x1ece170
static s16 GetSkill_Geta(SKLID skillid) {
  return 0;
}

// 0x1ece7b0
bool sBtlCheckScriptData(s32 devilid, SBTLUNIT_WORK *wk) {
  return sBtlGetAITBL(devilid, wk)->scr_no != 0;
}

// 0x1ece830
static bool CheckAIScript(SBTLUNIT_WORK *wk) {
  s32 devilid;
  AITBLDATA_WORK *AITBL;
  AITBLDATA_WORK *v6;
  SBTLACTAI_WORK *actaiwk;
  SBTLUNIT_WORK *PChara;
  sdatUnitWork_t *para;
  SBTLACTION_WORK *actwk;
  s32 MesHandle;
  s32 v13;
  scrHandle_t *hAIScript;
  s32 scr_no;
  SBTLUNIT_WORK *p_scrunit;

  devilid = wk->para->devilid;
  AITBL = sBtlGetAITBL(devilid, wk);
  if (!AITBL->scr_no)
    return 0;
  v6 = AITBL;
  if (!wk->hAIScript)
    return 0;
  actaiwk = wk->actaiwk;
  if ((u32)(actaiwk->mode - 9) <= 1 && !actaiwk->eventStart)
    return 0;
  if (!cfgGetConfigGAME(1, 0))
    goto LABEL_27;
  if ((wk->side & 2) != 0)
  {
    if (wk->battlemode == 3)
      goto LABEL_27;
    PChara = sBtlGetPChara();
    if (PChara)
    {
      para = PChara->para;
      if (para)
      {
        actwk = PChara->actwk;
        if (actwk)
        {
          if (actwk->status == 34 || para->now->hp < 1)
            return 0;
        }
      }
    }
  }
LABEL_27:
  MesHandle = wk->hAIScript->MesHandle;
  if ((MesHandle & 0x80000000) == 0)
  {
    MesHandle = wk->hAIScript->MesHandle;
    v13 = wk->para->devilid;
    itfMesMngSetVar(MesHandle, 0, v13, 0);
  }
  wk->aiwk->scr_actcheckflg = 0;
  hAIScript = wk->hAIScript;
  scr_no = v6->scr_no;
  scrSetStartProc(hAIScript, scr_no);
  p_scrunit = &wk->scrunit;
  p_scrunit = wk;
  scrRunScript(wk->hAIScript);
  return 1;
}

// 0x1eceb60
SBTLAI_WORK *Create(void) {
  SBTLAI_WORK *v1;

  v1 = Allocate(SBTLAI_WORK);
  _ctor(v1);
  *(u32 *)&v1->stat = 1;
  v1->processID = 0;
  return v1;
}

// 0x1ecebd0
bool Delete(SBTLAI_WORK *wk) {
  return 1;
}

// 0x1ecebe0
static bool IsKaja(SBTLUNIT_WORK *pBtlUnit, SBTLSKILLP_TBL *ptbl) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  s32 side;
  u32 flg;
  SBTLSKL_KAJA_WORK *v12;
  SBTLSKL_KAJA_WORK *v13;
  SBTLSKL_KAJA_WORK *v14;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    side = pBtlUnit->side;
    if ((side & 1) != 0)
    {
      if ((pUnit->side & 1) == 0)
        continue;
    }
    else if ((side & 2) == 0 || (pUnit->side & 2) == 0)
    {
      continue;
    }
    flg = ptbl->flg;
    if ((flg & 0x1000000) != 0)
    {
      v12 = pUnit->wkKaja[0];
      if ((sBtlCheckRegistKaja(v12, ptbl) & 0x80000000) == 0)
        return i < number;
      flg = ptbl->flg;
    }
    if ((flg & 0x2000000) != 0)
    {
      v13 = pUnit->wkKaja[1];
      if ((sBtlCheckRegistKaja(v13, ptbl) & 0x80000000) == 0)
        return i < number;
      flg = ptbl->flg;
    }
    if ((flg & 0x4000000) != 0)
    {
      v14 = pUnit->wkKaja[2];
      if ((sBtlCheckRegistKaja(v14, ptbl) & 0x80000000) == 0)
        return i < number;
    }
  }
  return i < number;
}

// 0x1ecedb0
static bool IsEnemyZenmetsu(void) {
  s64 v1;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  v1 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (v1 >= number)
      return v1 >= number;
    pUnit = UnitMng->pUnitL[v1]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 2) != 0)
      {
        if (CheckLiveTarget(pUnit))
          return v1 >= number;
      }
    }
    ++v1;
  }
}

// 0x1eceed0
s32 sBtlSetByct(SBTLUNIT_WORK *wk, s32 cnt, s32 mode) {
  SBTLAI_WORK *aiwk;
  u16 Percentage;
  u16 v10;
  SBTLSM_LISTWORK *sysmsgList;

  if (mode == 1 && wk->byctCnt)
    return wk->byctCnt;
  aiwk = wk->aiwk;
  wk->byctCnt = cnt;
  aiwk->rsvSkl = 0;
  Percentage = GetPercentage();
  wk->actwk->use_skillid = 0;
  if (Percentage <= 0x31u)
    v10 = 12;
  else
    v10 = 11;
  wk->aiwk->mode = v10;
  wk->actaiwk->stat = 1;
  sysmsgList = wk->sysmsgList;
  sBtlCreateSM(sysmsgList, wk, 156, 0, 0, 120);
  return wk->byctCnt;
}

// 0x1ecf000
void sBtlProc_YoyakuEndChk(SBTLUNIT_WORK *wk) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLAI_WORK *aiwk;
  s32 usedSkl;
  s32 rsvSkl;

  Skilltbl = sBtlGetSkilltbl(wk->aiwk->rsvSkl);
  if (!sBtlCheckCost(wk, 0))
  {
    aiwk = wk->aiwk;
    goto LABEL_10;
  }
  aiwk = wk->aiwk;
  usedSkl = aiwk->usedSkl;
  rsvSkl = aiwk->rsvSkl;
  if ((Skilltbl->flg2 & 1) == 0)
  {
    if (usedSkl != rsvSkl)
      return;
LABEL_10:
    *(u64 *)&aiwk->rsvSkl = 0xFFFFFFFF00000000LL;
    return;
  }
  if (usedSkl == GetExeSkill(rsvSkl))
    *(u64 *)&wk->aiwk->rsvSkl = 0xFFFFFFFF00000000LL;
}

// 0x1ecf100
void sBtlProc_YoyakuEnd(SBTLUNIT_WORK *wk) {
  *(u64 *)&wk->aiwk->rsvSkl = 0xFFFFFFFF00000000LL;
}

// 0x1ecf110
static bool Tuto(void) {
  s64 v2;
  bool v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 v7;
  bool v8;
  SBTLUNIT_LISTWORK *v9;
  SBTLUNIT_WORK *v10;
  sdatUnitWork_t *para;
  s32 devilid;

  if (wk->encountno == 23)
  {
    v2 = 0;
    v3 = 0;
    while (1)
    {
      UnitMng = wk->UnitMng;
      if (v2 >= UnitMng->number)
      {
        goto LABEL_22;
      }
      pUnit = UnitMng->pUnitL[v2]->pUnit;
      if (pUnit)
      {
        if ((pUnit->side & 2) != 0 && pUnit->para->devilid == 316)
          v3 = 1;
      }
      ++v2;
    }
  }
  v3 = 0;
LABEL_22:
  if (wk->encountno != 22)
    return v3;
  v7 = 0;
  v8 = 1;
  while (1)
  {
    v9 = wk->UnitMng;
    if (v7 >= v9->number)
      return v8;
    v10 = v9->pUnitL[v7]->pUnit;
    if (v10)
    {
      if ((v10->side & 2) != 0)
      {
        para = v10->para;
        devilid = (u16)para->devilid;
        if ((devilid == 164 || devilid == 90) && para->now->hp != para->now->maxhp)
          v8 = 0;
      }
    }
    ++v7;
  }
}

// 0x1ecf360
bool sBtlYasoAI(void) {
  s64 v3;
  bool v4;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 v8;
  bool v9;
  SBTLUNIT_LISTWORK *v10;
  SBTLUNIT_WORK *v11;

  if (wk->encountno != 59)
    return 0;
  if (BS_LASTB2_pos_type)
  {
    v3 = 0;
    v4 = 0;
    while (1)
    {
      UnitMng = wk->UnitMng;
      if (v3 >= UnitMng->number)
        return v4;
      pUnit = UnitMng->pUnitL[v3]->pUnit;
      if (pUnit)
      {
        if ((pUnit->side & 2) != 0 && pUnit->para->devilid == 258 && !pUnit->aiwk->scrStep)
        {
          v4 = 1;
        }
      }
      ++v3;
    }
  }
  v8 = 0;
  v9 = 0;
  while (1)
  {
    v10 = wk->UnitMng;
    if (v8 >= v10->number)
      return v9;
    v11 = v10->pUnitL[v8]->pUnit;
    if (v11)
    {
      if ((v11->side & 2) != 0)
      {
        if ((u32)(u16)v11->para->devilid - 242 < 3)
          return 0;
        v9 = 1;
      }
    }
    ++v8;
  }
}

// 0x1ecf5d0
bool Proc(SBTLUNIT_WORK *wk) {
  SBTLAI_WORK *aiwk;
  SBATTLE_WORK *v6;
  s32 byctCnt;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v10;
  s64 v12;
  s64 v13;
  SBATTLE_WORK *v14;
  SBTLAI_WORK *v15;
  s64 v16;
  s64 v17;
  SBTLAI_WORK *v18;
  u32 status;
  SBTLACTAI_WORK *actaiwk;
  s32 atkCnt;
  bool v22;
  s32 v23;
  s32 stat;
  SBTLUNIT_LISTWORK *TargetList_AI;
  sdatUnitWork_t *v26;
  u32 v27;
  bool v29;
  SBTLUNIT_LISTWORK *TargetList;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBTLAI_WORK *v33;
  SBTLAI_WORK *v35;
  u32 v36;
  u32 v37;
  long f64 v38;
  s32 playerID;
  SBTLUNIT_WORK *PlayerUnit;
  f32 z;
  f32 priv_area_r;
  f32 w;
  f32 x;
  f32 y;
  f32 v48;
  f32 v49;
  f32 hit_area_r;
  s32 actcounter_max;
  s32 v53;
  u32 v54;
  s32 actcounter;
  s16 v56;
  s16 v57;
  s16 v58;
  s16 v59;
  SBTLACTAI_WORK *v60;
  SBTLAI_WORK *v62;
  SBTLACTION_WORK *actwk;
  long f64 v65;
  SBTLAI_WORK *v66;
  u16 Percentage;
  u16 v68;
  s32 rsvSkl;
  SBTLAI_WORK *v72;
  s32 cmndSkl;
  s32 usedSkl;
  s32 ExeSkill_33327568;
  char v76;
  s32 v77;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLAI_WORK *v80;
  SBTLSKILLP_TBL *v81;
  SBTLACTION_WORK *v82;
  s32 v83;
  s32 rsvStk;
  s32 rsvTgt;
  SBTLUNIT_WORK *pUnit;
  SBTLAI_WORK *v88;
  SBTLACTION_WORK *v89;
  sdatUnitWork_t *v92;
  s32 use_skillid;
  SBTLAI_WORK *v95;
  s32 dfltOdrSkl;
  s32 v97;
  SBTLSKILLP_TBL *v100;
  SBTLAI_WORK *v101;
  s32 dfltOdrTgt;
  SBTLAI_WORK *v108;
  SBTLACTION_WORK *v109;
  SBTLACTION_WORK *v113;
  u32 v114;
  SBTLACTION_WORK *v116;
  s32 dfltOdrStk;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLAI_WORK *v122;
  SBTLACTION_WORK *v123;
  s32 v124;
  sdfVector4_t vector2;
  f32 v127;
  f32 v128;
  f32 vector1;
  sdfVector4_t v130;

  aiwk = wk->aiwk;
  if ((tbldata[aiwk->dfltOdrSkl]->flg & 4) != 0)
  {
    aiwk->atkCnt = 0;
    aiwk->bFarOk = 1;
LABEL_6:
    v6 = wk;
    if ((v6->status & 0x10000) == 0)
      return 0;
    goto LABEL_13;
  }
  else
  {
    goto LABEL_6;
  }
  v6 = wk;
  if ((v6->status & 0x10000) == 0)
    return 0;
LABEL_13:
  if (v6->cmbSkl->bRun)
    return 0;
  if (v6->kaiwaflg)
    return 0;
  if (Tuto())
    return 0;
  if (sBtlIsHuuma() || (wk->status & 4) == 0 || (wk->actaiwk->status & 0x1000) != 0)
  {
    return 0;
  }
  byctCnt = wk->byctCnt;
  if (byctCnt)
    wk->byctCnt = byctCnt - 1;
  Nakama = sBtlGetNakama(0);
  v10 = sBtlGetNakama(1);
  if (Nakama == wk)
    v12 = 0;
  else
    v12 = 0xFFFFFFFFLL;
  if (v10 == wk || Nakama == wk)
  {
    if (v10 == wk)
      v13 = 1;
    else
      v13 = v12;
    v14 = wk;
    if (v14->rsvCmbSkl[v13])
    {
      v14 = wk;
      if (!v14->cmbSkl->bRun)
      {
        v15 = wk->aiwk;
        v14 = wk;
        v16 = (s64)v14->rsvCmbTgt + 4 * v13;
        v17 = (s64)v14->rsvCmbSkl + 4 * v13;
        v15->dfltOdrTgt = *(u32 *)(v16 + 32);
        *(u32 *)(v17 + 32) = 0;
      }
    }
  }
  v18 = wk->aiwk;
  if (wk->endcnt)
  {
    status = v18->status;
    v18->rsvSkl = 0;
    v18->cmndFrm = 0;
    v18->cmndSkl = 0;
    v18->status = status & 0xFFFFFFEE;
    actaiwk = wk->actaiwk;
    if (actaiwk->mode != 4)
    {
      actaiwk->stat = 1;
      *(u32 *)&v18->stat = 2;
    }
  }
  atkCnt = v18->atkCnt;
  v22 = __OFSUB__(atkCnt, 1);
  v23 = atkCnt - 1;
  if (v23 < 0 == v22)
    v18->atkCnt = v23;
  stat = v18->stat;
  if (stat == 4)
  {
    if (wk->actwk->status != 59)
    {
      v18 = wk->aiwk;
      v29 = 1;
      v18->stat = 1;
      return v29;
    }
    return 1;
  }
  if (stat == 2)
  {
    if ((wk->side & 1) == 0)
      return 1;
    TargetList = sBtlCreateTargetList(2);
    sBtlUpdateMiusinai(wk);
    para = wk->para;
    BadStatus = sBtlGetBadStatus(para);
    if (wk->miusinai)
    {
      if (wk->actwk->use_skillid)
        goto LABEL_102;
      if (BadStatus - 7 >= 2)
      {
        v33 = wk->aiwk;
        goto LABEL_92;
      }
    }
    else
    {
      v33 = wk->aiwk;
      if ((v33->m_status & 0x40000) != 0 && BadStatus != 8 && BadStatus != 7)
      {
LABEL_92:
        if (v33->mode)
        {
          *(__n128 *)&v38 = sub_1B332C0(0, 0.0, 0.0, 0.0, 0.0);
          sub_1B335A0(&wk->mv_spdbk, 0, v38);
          wk->aiwk->stat = 1;
          wk->actcounter = wk->actcounter_max;
          if (wk->motionID != 5)
          {
            sBtlSetMotion(wk, 5, 4, 0, 0);
          }
        }
        goto LABEL_103;
      }
    }
    if ((wk->status & 0x40000) == 0)
    {
LABEL_103:
      sBtlDeleteUnitList(TargetList, 0);
      return 1;
    }
LABEL_102:
    if (!wk->aiwk->mode)
    {
      if (wk->enemy_num >= 1 && TargetList->count)
      {
        *(__n128 *)&v65 = sub_1B332C0(0, 0.0, 0.0, 0.0, 0.0);
        sub_1B335A0(&wk->mv_spdbk, 0, v65);
        v66 = wk->aiwk;
        v66->stat = 1;
        wk->actcounter = wk->actcounter_max;
        v66->status &= ~1u;
      }
    }
    goto LABEL_103;
  }
  if (stat != 1 || (wk->side & 1) == 0)
    return 1;
  TargetList_AI = sBtlCreateTargetList_AI(2);
  v26 = wk->para;
  v27 = sBtlGetBadStatus(v26);
  sBtlUpdateMiusinai(wk);
  if (!wk->miusinai)
  {
    if (wk->enemy_num >= 1)
    {
      if (TargetList_AI->count)
      {
        v35 = wk->aiwk;
        if ((v35->m_status & 0x40000) == 0)
        {
          v36 = v35->status;
          if ((v36 & 8) == 0)
            goto LABEL_121;
          v37 = v36 | 1;
          goto LABEL_120;
        }
      }
    }
  }
  if (v27 <= 0x16 && ((1 << v27) & 0x600E00) != 0)
  {
    playerID = wk->playerID;
    PlayerUnit = sBtlGetPlayerUnit(playerID);
    z = wk->max_mvspd.z;
    v130.x = wk->pos.x;
    v130.y = wk->pos.y;
    priv_area_r = wk->actaiwk->priv_area_r;
    v130.z = wk->pos.z;
    w = wk->pos.w;
    x = PlayerUnit->pos.x;
    y = PlayerUnit->pos.y;
    v49 = PlayerUnit->pos.z;
    v48 = PlayerUnit->pos.w;
    hit_area_r = PlayerUnit->actaiwk->hit_area_r;
    v128 = wk->pos.y;
    vector1 = wk->pos.x;
    v127 = wk->pos.z;
    v130.z = v127;
    v130.y = v128;
    v130.x = vector1;
    *(u64 *)&vector2.z = __PAIR64__(LODWORD(v48), LODWORD(v49));
    *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(x));
    v130.w = w;
    if (sBtlCheckCrossCircle(v130, priv_area_r + (f32)(z * 4.0), vector2, hit_area_r) && (wk->status & 0x800000) == 0 && (wk->next_motionID | 2) == 2)
    {
      sBtlDeleteUnitList(TargetList_AI, 0);
      sBtlProc_YoyakuEndChk(wk);
      return 1;
    }
    wk->actcounter = wk->actcounter_max;
    v35 = wk->aiwk;
    v37 = v35->status & 0xFFFFFFFE;
LABEL_120:
    v35->status = v37;
  }
LABEL_121:
  sBtlDeleteUnitList(TargetList_AI, 0);
  if (v27 == 12)
  {
    wk->actcounter = 0;
    actcounter_max = wk->actcounter_max;
    if (!wk->actaiwk->tgt_nullmode)
      goto LABEL_124;
    goto LABEL_128;
  }
  actcounter_max = wk->actcounter_max;
  if (!wk->actaiwk->tgt_nullmode)
  {
LABEL_124:
    if (actcounter_max >= 31)
      actcounter_max = 30;
    goto LABEL_136;
  }
LABEL_128:
  if (actcounter_max >= 61)
    v53 = 60;
  else
    v53 = actcounter_max;
  v54 = sub_1905740(100, 0);
  if (v53 >= 30)
    actcounter_max = 30;
  else
    actcounter_max = v53;
  if (v54 >= 5)
    actcounter_max = v53;
LABEL_136:
  actcounter = wk->actcounter;
  if (actcounter_max <= actcounter)
  {
    v60 = wk->actaiwk;
    wk->actcounter = 0;
    v60->tgt_nullmode = 0;
  }
  else
  {
    v56 = actcounter + 1;
    wk->actcounter = actcounter + 1;
    v57 = wk->actcounter_max;
    v56 = wk->actcounter;
    v58 = v57;
    if (v56 < v57)
      v58 = v56;
    if (v56 <= 0)
      v59 = 0;
    else
      v59 = v58;
    wk->actcounter = v59;
  }
  if (IsEnemyZenmetsu())
  {
    wk->actwk->use_skillid = 0;
    wk->aiwk->mode = 12;
LABEL_155:
    v29 = 1;
    wk->actaiwk->stat = 1;
    return v29;
  }
  v62 = wk->aiwk;
  if (wk->actcounter && !v62->cmndFrm)
    return 1;
  if (v62->bWait || v62->bWait2)
  {
    actwk = wk->actwk;
    v62->mode = 12;
    actwk->use_skillid = 0;
    goto LABEL_155;
  }
  if (wk->byctCnt)
  {
LABEL_166:
    Percentage = GetPercentage();
    wk->actwk->use_skillid = 0;
    if (Percentage <= 0x31u)
      v68 = 12;
    else
      v68 = 11;
    wk->aiwk->mode = v68;
    goto LABEL_155;
  }
  rsvSkl = v62->rsvSkl;
  v62->cancelCnt = 0;
  v62->bFarOk = 0;
  sBtlGetSkilltbl(rsvSkl);
  sBtlProc_YoyakuEndChk(wk);
  v72 = wk->aiwk;
  cmndSkl = v72->cmndSkl;
  if (cmndSkl)
  {
    usedSkl = v72->usedSkl;
    ExeSkill_33327568 = GetExeSkill(cmndSkl);
    v72 = wk->aiwk;
    if (usedSkl == ExeSkill_33327568)
      v72->bCmndEnd = 1;
    if (!v72->cmndFrm)
      v72->cmndSkl = 0;
  }
  v76 = BYTE2(v72->m_status);
  v72->usedSkl = 0;
  if ((v76 & 4) != 0)
  {
    v89 = wk->actwk;
    *(u64 *)&v89->order_skillid = 0xFFFFFFFF00000000LL;
    v89->order_stockID = 0;
    v72->status |= 1u;
    CheckActionEquation(wk);
    sBtlCheckTargetEquation(wk);
    goto LABEL_239;
  }
  v77 = v72->rsvSkl;
  if (v77)
  {
    Skilltbl = sBtlGetSkilltbl(v77);
    v80 = wk->aiwk;
    v81 = Skilltbl;
    v82 = wk->actwk;
    v83 = v80->rsvSkl;
    v82->use_skillid = v83;
    if ((v81->flg2 & 1) != 0)
    {
      v82->use_skillid = GetExeSkill(v83);
      v82 = wk->actwk;
      v80 = wk->aiwk;
    }
    rsvTgt = v80->rsvTgt;
    rsvStk = v80->rsvStk;
    v82->order_targetID = rsvTgt;
    v82->order_stockID = rsvStk;
    if (rsvTgt < 0)
    {
      if (rsvStk < 0)
        goto LABEL_221;
      rsvTgt = 0;
    }
    else
    {
      rsvTgt = wk->actwk->order_targetID;
      pUnit = wk->UnitMng->pUnitL[rsvTgt]->pUnit;
      if (!pUnit)
      {
        *(u64 *)&wk->aiwk->rsvSkl = 0xFFFFFFFF00000000LL;
        goto LABEL_235;
      }
      if (pUnit->para->devilid == 258)
      {
        v88 = wk->aiwk;
        v88->rsvTgt = sBtlGetPlayerTarget()->ListID;
        rsvTgt = wk->aiwk->rsvTgt;
        wk->actwk->order_targetID = rsvTgt;
      }
    }
    sBtlSetTargetID(wk, rsvTgt);
LABEL_221:
    if (sBtlCheckCost(wk, 0))
    {
LABEL_239:
      sBtlSetAIMode(wk);
      v29 = 1;
      wk->actaiwk->stat = 1;
      wk->aiwk->stat = 2;
      SetBSHelper(wk);
      return v29;
    }
LABEL_235:
    SetATK(wk);
    goto LABEL_239;
  }
  v72->dfltOdrSkl = v72->RepeatOdrSkl;
  if (!AI_NakamaUseSkill(wk))
  {
    if (wk->actwk->status == 59)
    {
      v29 = 0;
      wk->aiwk->stat = 4;
      return v29;
    }
    return 0;
  }
  v92 = wk->para;
  if (sBtlGetBadStatus(v92) - 7 <= 1 && (wk->side & 1) != 0)
  {
    use_skillid = wk->actwk->use_skillid;
    if (use_skillid != 149 && (sBtlGetSkilltbl(use_skillid)->flg & 0x24) != 0)
      wk->actwk->use_skillid = 149;
  }
  v95 = wk->aiwk;
  if (v95->RepeatOdrDisable)
    goto LABEL_275;
  dfltOdrSkl = v95->dfltOdrSkl;
  if (!sBtlCheckCost2(wk, dfltOdrSkl, 0))
  {
LABEL_275:
    SetATK(wk);
    goto LABEL_239;
  }
  v97 = wk->aiwk->dfltOdrSkl;
  if (v97)
  {
    v100 = sBtlGetSkilltbl(v97);
    if ((v100->flg & 0x400000) == 0)
    {
      v101 = wk->aiwk;
      if ((tbldata[v101->dfltOdrSkl]->flg & 4) != 0)
      {
        v113 = wk->actwk;
        v113->order_skillid = 0;
        *(u64 *)&v113->order_targetID = *(u64 *)&v101->dfltOdrTgt;
        v114 = v101->status;
        v101->status = v114 & 0xFFFFFFFE;
        if (!wk->miusinai && (v101->m_status & 0x40000) == 0 && !v113->use_skillid)
        {
          *(u64 *)&v113->order_skillid = -4294967147LL;
          v101->status = v114 | 1;
          v113->use_skillid = 149;
          sBtlSetAIMode(wk);
          wk->actaiwk->stat = 1;
        }
LABEL_271:
        sBtlCheckTargetEquation(wk);
        goto LABEL_239;
      }
      dfltOdrTgt = v101->dfltOdrTgt;
      if (dfltOdrTgt == -1)
      {
        dfltOdrTgt = wk->actaiwk->targetID;
        if (dfltOdrTgt == -1)
        {
          v116 = wk->actwk;
          dfltOdrStk = v101->dfltOdrStk;
          v116->order_targetID = -1;
          v116->order_stockID = dfltOdrStk;
          v101->status |= 1u;
          CheckActionEquation(wk);
          sBtlCheckTargetEquation(wk);
          dfltOdrTgt = wk->actaiwk->targetID;
          if (dfltOdrTgt == -1)
            goto LABEL_266;
        }
        dfltOdrTgt = wk->actaiwk->targetID;
      }
      else
      {
        dfltOdrTgt = wk->aiwk->dfltOdrTgt;
      }
      UnitMng = wk->UnitMng;
      sBtlSearchUnit_ID(UnitMng, dfltOdrTgt);
LABEL_266:
      v122 = wk->aiwk;
      v123 = wk->actwk;
      v124 = v122->dfltOdrSkl;
      v123->order_skillid = v124;
      if ((v100->flg2 & 1) != 0)
      {
        v123->order_skillid = GetExeSkill(v124);
        v123 = wk->actwk;
        v122 = wk->aiwk;
      }
      *(u64 *)&v123->order_targetID = *(u64 *)&v122->dfltOdrTgt;
      v122->status |= 1u;
      CheckActionEquation(wk);
      goto LABEL_271;
    }
    if (!IsKaja(wk, v100))
      goto LABEL_166;
    v108 = wk->aiwk;
    v109 = wk->actwk;
    v109->use_skillid = v108->dfltOdrSkl;
    *(u64 *)&v109->order_targetID = *(u64 *)&v108->dfltOdrTgt;
    v108->status |= 1u;
    CheckActionEquation(wk);
    sBtlCheckTargetEquation(wk);
    sBtlSetAIMode(wk);
    v29 = 1;
    wk->actaiwk->stat = 1;
    wk->aiwk->stat = 2;
  }
  else
  {
    SetATK(wk);
    return 1;
  }
  return v29;
}

// 0x1ed0bc0
static void SetATK(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  SBTLAI_WORK *aiwk;
  SBTLACTION_WORK *v6;
  SBTLAI_WORK *v7;
  SBTLSKILLP_TBL *Skilltbl;
  s32 use_skillid;
  s32 v11;
  SBTLAI_WORK *v12;
  s16 v13;

  actwk = wk->actwk;
  actwk->order_skillid = 0;
  aiwk = wk->aiwk;
  *(u64 *)&actwk->order_targetID = *(u64 *)&aiwk->dfltOdrTgt;
  aiwk->status &= ~1u;
  CheckActionEquation(wk);
  v6 = wk->actwk;
  v6->use_skillid = 149;
  v7 = wk->aiwk;
  *(u64 *)&v6->order_skillid = -4294967147LL;
  v6->order_stockID = v7->dfltOdrStk;
  v7->status |= 1u;
  Skilltbl = sBtlGetSkilltbl(149);
  use_skillid = wk->actwk->use_skillid;
  if (use_skillid != 288 && use_skillid)
  {
    if ((Skilltbl->type & 0xFFFu) <= 0x10)
    {
      v11 = 1 << LOBYTE(Skilltbl->type);
      if ((v11 & 0x1CE2C) != 0)
      {
        v12 = wk->aiwk;
        v13 = 8;
LABEL_13:
        v12->mode = v13;
        v12->scrflag |= 0x10000u;
LABEL_14:
        wk->NakamaAtkFormationUse = 0;
        goto LABEL_15;
      }
      if ((v11 & 0x3012) != 0)
      {
        v12 = wk->aiwk;
        v13 = 1;
        goto LABEL_13;
      }
    }
    wk->aiwk->mode = 0;
    goto LABEL_14;
  }
  wk->aiwk->mode = 0;
LABEL_15:
  wk->actaiwk->stat = 1;
  sBtlCheckTargetEquation(wk);
}

// 0x1ed0d20
void sBtlSetAIWkStat(SBTLUNIT_WORK *wk, s32 stat) {
  wk->aiwk->stat = stat;
}

// 0x1ece6d0
bool sBtlSetAIMode(SBTLUNIT_WORK *wk) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 use_skillid;
  s32 v7;
  SBTLAI_WORK *aiwk;
  s16 v9;

  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  use_skillid = wk->actwk->use_skillid;
  if (use_skillid == 288 || use_skillid == 0)
  {
    wk->aiwk->mode = 0;
    return 1;
  }
  if ((Skilltbl->type & 0xFFFu) <= 0x10)
  {
    v7 = 1 << LOBYTE(Skilltbl->type);
    if ((v7 & 0x1CE2C) != 0)
    {
      aiwk = wk->aiwk;
      v9 = 8;
LABEL_12:
      aiwk->mode = v9;
      aiwk->scrflag |= 0x10000u;
      wk->NakamaAtkFormationUse = 0;
      return 1;
    }
    if ((v7 & 0x3012) != 0)
    {
      aiwk = wk->aiwk;
      v9 = 1;
      goto LABEL_12;
    }
  }
  wk->aiwk->mode = 0;
  wk->NakamaAtkFormationUse = 0;
  return 1;
}

// 0x1ed0d30
bool sBtlProcScript(SBTLUNIT_WORK *wk) {
  u32 status;

  if (!wk)
    return 0;
  status = wk->actwk->status;
  switch (status)
  {
    case 0xEu:
    case 0xBu:
      return 0;
    case 0xAu:
      if ((wk->aiwk->scrflag & 0x120000) == 0)
        return 0;
      break;
    case 0x1Eu:
      return 0;
  }
  if (wk->actaiwk->mode == 9 || wk->mode < 5 || (wk->aiwk->scrflag & 0x10000000) != 0 && (wk->hstatus & 0x10) != 0 && wk->para->now->hp > 0)
  {
    return 0;
  }
  return CheckAIScript(wk);
}

// 0x1ed0e20
static bool CheckBSTTarget(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  bool result;
  SBTLAI_WORK *aiwk;
  s32 ListID;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  result = 0;
  if ((ptbl->area & 0x4000) == 0 && BadStatus - 7 <= 1)
  {
    aiwk = wk->aiwk;
    if (aiwk->mode == 18)
    {
      ListID = wk->ListID;
LABEL_10:
      sBtlSetTargetID(wk, ListID);
      return 1;
    }
    else
    {
      if ((aiwk->bstside & 1) != 0)
        return 0;
      ListID = wk->playerID;
      goto LABEL_10;
    }
    goto LABEL_10;
  }
  return result;
}

// 0x1ed0f60
static s16 GetMeireiNo(SBTLUNIT_WORK *wk) {
  s16 result;
  s32 SmnNo;
  s32 v6;
  SBTLPNL_SETDATA *data;

  result = 0;
  if (!wk)
    return result;
  if (wk)
  {
    SmnNo = sBtlGetSmnNo(wk);
    if (SmnNo < 0)
      return 0;
    v6 = SmnNo;
    data = wk->panelwk->data;
    if (v6 >= SLODWORD(data->max_length))
    {
      return 0;
    }
    else
    {
      data = wk->panelwk->data;
      return data[v6]->meirei_no;
    }
  }
  return result;
}

// 0x1ed1090
static bool SEquationno_00(SBTLUNIT_WORK *wk, SKLID skillid) {
  u16 area;
  s64 v5;
  SBTLUNIT_LISTWORK *other_List;
  s64 count;
  bool v9;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWORK *friend_List;
  s64 v12;
  SBTLUNIT_WORK *v13;

  area = sBtlGetSkilltbl(skillid)->area;
  v5 = 0;
  if ((area & 0x4000) == 0)
  {
    while (1)
    {
      other_List = wk->other_List;
      count = other_List->count;
      v9 = v5 < count;
      if (v5 >= count)
        return v9;
      pUnit = other_List->pUnitL[v5]->pUnit;
      if (pUnit)
      {
        if (sBtlCheckDamageTarget(pUnit))
          return v9;
      }
      ++v5;
    }
  }
  while (1)
  {
    friend_List = wk->friend_List;
    v12 = friend_List->count;
    v9 = v5 < v12;
    if (v5 >= v12)
      return v9;
    v13 = friend_List->pUnitL[v5]->pUnit;
    if (v13)
    {
      if (sBtlCheckDamageTarget(v13))
        return v9;
    }
    ++v5;
  }
}

// 0x1ed1260
static bool SEquationno_01(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 v6;
  s64 i;
  SBTLUNIT_LISTWORK *other_List;
  s64 count;
  bool v11;
  SBTLUNIT_WORK *pUnit;
  f32 hit_area_r;
  f32 x;
  f32 z;
  f32 w;
  f32 v17;
  f32 v18;
  f32 y;
  f32 v20;
  f32 v21;
  sdfVector4_t vector2;
  f32 v24;
  f32 v25;
  sdfVector4_t v26;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if ((Skilltbl->type & 0xFFF) != 1)
  {
    v6 = 0;
    if (skillid <= 97)
      goto LABEL_5;
LABEL_11:
    if ((u32)skillid <= 0x214)
    {
      if ((u32)(skillid - 401) < 2 || skillid == 532)
        goto LABEL_21;
    }
    else if ((u32)(skillid - 548) <= 0x20 && ((1 << ((u8)skillid - 36)) & 0x100010001LL) != 0)
    {
      goto LABEL_21;
    }
    goto LABEL_20;
  }
  v6 = Skilltbl->flg & 1;
  if (skillid > 97)
    goto LABEL_11;
LABEL_5:
  if (skillid > 18)
  {
    if ((skillid | 0x10) == 0x32 || (skillid & 0xFFFFFFFE) == 0x60 || v6)
      goto LABEL_21;
    return 0;
  }
  if (skillid == 3 || skillid == 18)
    goto LABEL_21;
LABEL_20:
  if (v6)
  {
LABEL_21:
    for (i = 0; ; ++i)
    {
      other_List = wk->other_List;
      count = other_List->count;
      v11 = i < count;
      if (i >= count)
        return v11;
      pUnit = other_List->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if (!sBtlCheckDamageTarget(pUnit))
        continue;
      hit_area_r = wk->actaiwk->hit_area_r;
      x = wk->pos.x;
      v26.y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v17 = pUnit->actaiwk->hit_area_r;
      v18 = pUnit->pos.x;
      y = pUnit->pos.y;
      v21 = pUnit->pos.z;
      v20 = pUnit->pos.w;
      v24 = wk->pos.y;
      v25 = wk->pos.x;
      v26.y = v24;
      x = v25;
      v26.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v20), LODWORD(v21));
      v26.x = x;
      v26.z = z;
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(v18));
      if (sBtlCheckCrossCircle(v26, hit_area_r * 2.5, vector2, v17))
        return v11;
    }
  }
  return 0;
}

// 0x1ed1510
static bool SEquationno_02(SBTLUNIT_WORK *wk, SKLID skillid) {
  bool v5;
  s64 i;
  SBTLUNIT_LISTWORK *other_List;
  s64 count;
  SBTLUNIT_WORK *pUnit;
  f32 hit_area_r;
  f32 x;
  f32 z;
  f32 w;
  f32 v16;
  f32 v17;
  f32 y;
  f32 v19;
  f32 v20;
  sdfVector4_t vector2;
  f32 v22;
  f32 v23;
  sdfVector4_t v24;

  if (skillid <= 97)
  {
    if (skillid >= 19)
    {
      if ((skillid | 0x10) != 0x32 && (skillid & 0xFFFFFFFE) != 0x60)
        goto LABEL_19;
      return 0;
    }
    v5 = 0;
    if (skillid != 3 && skillid != 18)
      goto LABEL_19;
  }
  else
  {
    if ((u32)skillid > 0x214)
    {
      if ((u32)(skillid - 548) > 0x20 || ((1 << ((u8)skillid - 36)) & 0x100010001LL) == 0)
      {
LABEL_19:
        for (i = 0; ; ++i)
        {
          other_List = wk->other_List;
          count = other_List->count;
          v5 = i < count;
          if (i >= count)
            return v5;
          pUnit = other_List->pUnitL[i]->pUnit;
          if (!pUnit)
            continue;
          if (!sBtlCheckDamageTarget(pUnit))
            continue;
          hit_area_r = wk->actaiwk->hit_area_r;
          x = wk->pos.x;
          v24.y = wk->pos.y;
          z = wk->pos.z;
          w = wk->pos.w;
          v16 = pUnit->actaiwk->hit_area_r;
          v17 = pUnit->pos.x;
          y = pUnit->pos.y;
          v20 = pUnit->pos.z;
          v19 = pUnit->pos.w;
          v22 = wk->pos.y;
          v23 = wk->pos.x;
          v24.y = v22;
          x = v23;
          v24.w = w;
          *(u64 *)&vector2.z = __PAIR64__(LODWORD(v19), LODWORD(v20));
          v24.x = x;
          v24.z = z;
          *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(v17));
          if (sBtlCheckCrossCircle(v24, hit_area_r * 8.0, vector2, v16))
            return v5;
        }
      }
      return 0;
    }
    v5 = 0;
    if ((u32)(skillid - 401) >= 2 && skillid != 149 && skillid != 532)
      goto LABEL_19;
  }
  return v5;
}

// 0x1ed1780
static bool SEquationno_03(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v7;
  s64 v8;
  s32 v9;
  SBTLUNIT_LISTWORK *other_List;
  SBTLUNIT_WORK *pUnit;
  u32 attr;
  u32 v14;
  s32 v16;
  s32 a_pHanshaType;

  a_pHanshaType = 0;
  Skilltbl = sBtlGetSkilltbl(skillid);
  if ((Skilltbl->area & 0x4000) != 0)
    return 1;
  v7 = Skilltbl;
  v8 = 0;
  v9 = 0;
  while (1)
  {
    other_List = wk->other_List;
    if (v8 >= other_List->count)
      break;
    pUnit = other_List->pUnitL[v8]->pUnit;
    if (!pUnit)
      goto LABEL_5;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_5;
    a_pHanshaType = 0;
    attr = v7->attr;
    v14 = sBtlCheckAisyoEx(pUnit, attr, &a_pHanshaType);
    if (v14 != 4096 && v14 != 0x2000)
      ++v9;
LABEL_5:
    ++v8;
  }
  if (v9)
    return 1;
  v16 = v7->type & 0xFFF;
  if ((u32)(v16 - 1) < 2)
  {
    if (GetMeireiNo(wk) != 3)
      return 0;
    return 1;
  }
  if (v16 != 3 && v16 != 5)
    return 0;
  if (GetMeireiNo(wk) != 4)
    return 0;
  return 1;
}

// 0x1ed1a10
static bool SEquationno_04(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  s64 v5;
  char v6;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_WORK *pUnit;
  u32 flg;
  s32 v12;

  Skilltbl = sBtlGetSkilltbl(skillid);
  v5 = 0;
  v6 = 0;
  while (1)
  {
    friend_List = wk->friend_List;
    if (v5 >= friend_List->count)
      return v6 & 1;
    pUnit = friend_List->pUnitL[v5]->pUnit;
    if (!pUnit)
      goto LABEL_5;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_5;
    flg = Skilltbl->flg;
    if ((flg & 0x20) != 0)
    {
      if ((flg & 0x400000) != 0)
      {
        v12 = sBtlCheckEnableUseKaja(pUnit, skillid);
      }
      else
      {
        v12 = sBtlCheckEnableUseAura(pUnit, skillid);
      }
      v6 |= v12 > 0;
    }
    else
    {
      v6 = 1;
    }
LABEL_5:
    ++v5;
  }
}

// 0x1ed1bc0
static bool SEquationno_05(SBTLUNIT_WORK *wk, SKLID skillid) {
  u32 flg;
  bool v5;
  s64 v6;
  SBTLUNIT_LISTWORK *friend_List;
  s64 count;
  SBTLUNIT_WORK *pUnit;
  bool v11;
  sdatParaWork_t *now;
  s32 maxhp;

  flg = sBtlGetSkilltbl(skillid)->flg;
  v5 = 0;
  if ((flg & 4) != 0 && (flg & 0x81F000) != 0)
  {
    v6 = 0;
    while (1)
    {
      friend_List = wk->friend_List;
      count = friend_List->count;
      v5 = v6 < count;
      if (v6 >= count)
        return v5;
      pUnit = friend_List->pUnitL[v6]->pUnit;
      if (!pUnit)
        goto LABEL_6;
      v11 = sBtlCheckDamageTarget(pUnit);
      if (!v11)
        goto LABEL_6;
      now = pUnit->para->now;
      maxhp = now->maxhp;
      if (maxhp && 100 * now->hp / maxhp < 40)
        return v5;
LABEL_6:
      ++v6;
    }
  }
  return v5;
}

// 0x1ed1d50
static bool SEquationno_06(SBTLUNIT_WORK *wk, SKLID skillid) {
  sdatUnitWork_t *para;
  sdatParaWork_t *v6;
  sdatUnitWork_t *v7;
  SBTLCALC_DMGWORK *v8;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v10;
  s64 i;
  SBTLUNIT_LISTWORK *friend_List;
  s64 count;
  bool v15;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *v17;
  sdatParaWork_t *now;
  s32 luck;
  s32 Damage_MRecover;
  s32 hp;
  s32 maxhp;
  bool v23;

  para = wk->para;
  v6 = Allocate(sdatParaWork_t);
  _ctor(v6, 0);
  v7 = sBtlGetPlayerData()->para;
  v8 = Allocate(SBTLCALC_DMGWORK);
  sBtlGetPlayerTec_ParaUp(v7, v6);
  Skilltbl = sBtlGetSkilltbl(skillid);
  if ((Skilltbl->flg & 0x10004) == 4)
  {
    v10 = Skilltbl;
    for (i = 0; ; ++i)
    {
      friend_List = wk->friend_List;
      count = friend_List->count;
      v15 = i < count;
      if (i >= count)
        return v15;
      friend_List = wk->friend_List;
      pUnit = friend_List->pUnitL[i]->pUnit;
      v17 = pUnit->para;
      if (!sBtlCheckDamageTarget(pUnit))
        continue;
      if ((v10->area & 0x2000) == 0 || para->devilid == v17->devilid)
      {
        now = v17->now;
        if (now->maxhp)
        {
          luck = now->luck;
          v8->atec = v6->tec + para->now->tec;
          v8->tluck = v6->luck + luck;
          v8->n0 = v10->n0;
          v8->alevel = para->level;
          *(u32 *)&v8->damage_per = 1065353216;
          v8->tmaxhp = (f32)pUnit->para->now->maxhp;
          Damage_MRecover = sBtlGetDamage_MRecover(v8, v10);
          if (Damage_MRecover < 1)
            continue;
          hp = pUnit->para->now->hp;
          maxhp = pUnit->para->now->maxhp;
          v23 = hp >= maxhp >> 1 && maxhp - hp <= Damage_MRecover;
          if (!v23 && ((v10->flg & 0x800000) == 0 || pUnit->rejyenecounter < 1))
            return v15;
        }
      }
    }
  }
  return 1;
}

// 0x1ed2020
static bool SEquationno_07(SBTLUNIT_WORK *wk, SKLID skillid) {
  return (sBtlGetSkilltbl(skillid)->type >> 13) & 1;
}

// 0x1ed2050
static bool SEquationno_08(SBTLUNIT_WORK *wk, SKLID skillid) {
  u32 flg;
  bool v5;
  s64 v6;
  SBTLUNIT_LISTWORK *friend_List;
  s64 count;
  SBTLUNIT_WORK *pUnit;
  bool v11;
  sdatParaWork_t *now;
  s32 maxhp;

  flg = sBtlGetSkilltbl(skillid)->flg;
  v5 = 0;
  if ((flg & 4) != 0 && (flg & 0x81F000) != 0)
  {
    v6 = 0;
    while (1)
    {
      friend_List = wk->friend_List;
      count = friend_List->count;
      v5 = v6 < count;
      if (v6 >= count)
        return v5;
      pUnit = friend_List->pUnitL[v6]->pUnit;
      if (!pUnit)
        goto LABEL_6;
      v11 = sBtlCheckDamageTarget(pUnit);
      if (!v11)
        goto LABEL_6;
      now = pUnit->para->now;
      maxhp = now->maxhp;
      if (maxhp && 100 * now->hp / maxhp < 70)
        return v5;
LABEL_6:
      ++v6;
    }
  }
  return v5;
}

// 0x1ed21e0
static bool SEquationno_09(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  bool v5;
  s64 v7;
  SBTLUNIT_LISTWORK *other_List;
  s64 count;
  SBTLUNIT_WORK *pUnit;
  bool v12;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if ((Skilltbl->attr & 1) != 0)
  {
    if ((Skilltbl->flg & 1) == 0)
      return 0;
    v7 = 0;
    while (1)
    {
      other_List = wk->other_List;
      count = other_List->count;
      v5 = v7 < count;
      if (v7 >= count)
        return v5;
      pUnit = other_List->pUnitL[v7]->pUnit;
      if (!pUnit)
        goto LABEL_9;
      v12 = sBtlCheckDamageTarget(pUnit);
      if (!v12)
        goto LABEL_9;
      if ((pUnit->hstatus & 0x10) != 0)
        return v5;
LABEL_9:
      ++v7;
    }
  }
  return 0;
}

// 0x1ed2360
static bool SEquationno_0a(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  bool v5;
  SBTLSKILLP_TBL *v7;
  s64 i;
  SBTLUNIT_LISTWORK *other_List;
  s64 count;
  SBTLUNIT_WORK *pUnit;
  u32 attr;
  s32 a_pHanshaType;

  a_pHanshaType = 0;
  Skilltbl = sBtlGetSkilltbl(skillid);
  v5 = 0;
  if ((Skilltbl->flg & 1) != 0)
  {
    v7 = Skilltbl;
    for (i = 0; ; ++i)
    {
      other_List = wk->other_List;
      count = other_List->count;
      v5 = i < count;
      if (i >= count)
        return v5;
      pUnit = other_List->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if (!sBtlCheckDamageTarget(pUnit))
        continue;
      a_pHanshaType = 0;
      attr = v7->attr;
      if (sBtlCheckAisyoEx(pUnit, attr, &a_pHanshaType) == 0x4000)
        return v5;
    }
  }
  return v5;
}

// 0x1ed2510
static bool SEquationno_0b(SBTLUNIT_WORK *wk, SKLID skillid) {
  return (sBtlGetSkilltbl(skillid)->type & 0xFFFu) - 1 <= 1
      && wk->para->now->tec > wk->para->now->str;
}

// 0x1ed2580
static bool SEquationno_0c(SBTLUNIT_WORK *wk, SKLID skillid) {
  s32 v4;

  v4 = sBtlGetSkilltbl(skillid)->type & 0xFFF;
  return (v4 == 5 || v4 == 3) && wk->para->now->str > wk->para->now->tec;
}

// 0x1ed25f0
static bool SEquationno_0d(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;
  s32 AutoSkillPara;
  sdatUnitWork_t *v10;
  s32 v11;
  s32 v12;
  sdatUnitWork_t *v13;
  s32 v14;
  s32 v15;
  sdatUnitWork_t *v16;
  s32 v17;
  s32 v18;
  sdatUnitWork_t *v19;
  s32 v20;
  s32 v21;
  sdatUnitWork_t *v22;
  s32 v23;
  s32 v24;
  sdatUnitWork_t *v25;
  s32 v26;
  s32 v27;
  sdatUnitWork_t *v28;
  s32 v29;
  s32 v30;

  Skilltbl = sBtlGetSkilltbl(skillid);
  para = wk->para;
  AutoSkill_ID = sBtlGetAutoSkill_ID(para, 0);
  AutoSkillPara = sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, AutoSkillPara))
    return 1;
  v10 = wk->para;
  v11 = sBtlGetAutoSkill_ID(v10, 1);
  v12 = sBtlGetAutoSkillPara(v11, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, v12))
    return 1;
  v13 = wk->para;
  v14 = sBtlGetAutoSkill_ID(v13, 2);
  v15 = sBtlGetAutoSkillPara(v14, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, v15))
    return 1;
  v16 = wk->para;
  v17 = sBtlGetAutoSkill_ID(v16, 3);
  v18 = sBtlGetAutoSkillPara(v17, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, v18))
    return 1;
  v19 = wk->para;
  v20 = sBtlGetAutoSkill_ID(v19, 4);
  v21 = sBtlGetAutoSkillPara(v20, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, v21))
    return 1;
  v22 = wk->para;
  v23 = sBtlGetAutoSkill_ID(v22, 5);
  v24 = sBtlGetAutoSkillPara(v23, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, v24))
    return 1;
  v25 = wk->para;
  v26 = sBtlGetAutoSkill_ID(v25, 6);
  v27 = sBtlGetAutoSkillPara(v26, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, v27))
    return 1;
  v28 = wk->para;
  v29 = sBtlGetAutoSkill_ID(v28, 7);
  v30 = sBtlGetAutoSkillPara(v29, &wk->para->autost_cnt, &wk->para->autost_cnt2);
  if (CheckAutono(wk, Skilltbl, v30))
    return 1;
  return sBtlIsAura(wk, 0x1000000) && (Skilltbl->type & 0xFFF) == 1;
}

// 0x1ed2b10
static bool SEquationno_0e(SBTLUNIT_WORK *wk, SKLID skillid) {
  return (sBtlGetSkilltbl(skillid)->type >> 12) & 1;
}

// 0x1ed2b40
static bool SEquationno_0f(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if (GetMeireiNo(wk) != 6)
    return 0;
  if (Skilltbl->s_type)
    return Skilltbl->para != 0;
  return 0;
}

// 0x1ed2c10
static bool SEquationno_10(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBATTLE_WORK *v5;
  SBATTLE_WORK *v7;

  if (skillid != 288)
    return 0;
  v5 = wk;
  if (v5->enemy_num != 1)
    goto LABEL_11;
  if (v5->other_List->count)
    goto LABEL_11;
  return 1;
LABEL_11:
  v7 = wk;
  if (v7->enemy_num < 1)
    return 1;
  v7 = wk;
  return v7->other_List->count == 0;
}

// 0x1ed2d60
static bool SEquationno_11(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  sdatUnitWork_t *para;
  u32 BadStatus;

  Skilltbl = sBtlGetSkilltbl(skillid);
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (!Skilltbl->s_type)
    return 0;
  if (!Skilltbl->para)
    return 0;
  return skillid != 149 && BadStatus == 10;
}

// 0x1ed2e30
static bool SEquationno_12(SBTLUNIT_WORK *wk, SKLID skillid) {
  return sBtlCheckCost_SkillID(wk, skillid, 0);
}

// 0x1ed2ea0
static bool SEquationno_13(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  u16 s_type;
  SBTLSKILLP_TBL *v8;

  Skilltbl = sBtlGetSkilltbl(skillid);
  s_type = Skilltbl->s_type;
  v8 = Skilltbl;
  if ((s_type & 1) != 0 && Skilltbl->para >= 1)
  {
    if (GetMeireiNo(wk) == 6)
      return 1;
    s_type = v8->s_type;
  }
  if ((s_type & 2) != 0 && v8->para >= 1)
  {
    if (GetMeireiNo(wk) == 6)
      return 1;
    s_type = v8->s_type;
  }
  if ((s_type & 4) != 0 && v8->para >= 1)
  {
    if (GetMeireiNo(wk) == 6)
      return 1;
    s_type = v8->s_type;
  }
  if ((s_type & 8) != 0 && v8->para >= 1)
  {
    if (GetMeireiNo(wk) == 6)
      return 1;
    s_type = v8->s_type;
  }
  if ((s_type & 0x10) != 0 && v8->para >= 1)
  {
    if (GetMeireiNo(wk) == 6)
      return 1;
    s_type = v8->s_type;
  }
  if ((s_type & 0x20) != 0 && v8->para >= 1)
  {
    if (GetMeireiNo(wk) == 6)
      return 1;
  }
  return 0;
}

// 0x1ed3170
static bool SEquationno_14(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  u32 badst;
  s64 i;
  SBTLUNIT_LISTWORK *friend_List;
  s64 count;
  bool v10;
  SBTLUNIT_WORK *pUnit;
  bool v12;
  s64 j;
  SBTLUNIT_LISTWORK *v16;
  SBTLUNIT_WORK *v17;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if ((~Skilltbl->flg & 0x10004) != 0)
    return 1;
  badst = Skilltbl->badst;
  if ((badst & 0x20000) == 0)
  {
    for (i = 0; ; ++i)
    {
      friend_List = wk->friend_List;
      count = friend_List->count;
      v10 = i < count;
      if (i >= count)
        return v10;
      pUnit = friend_List->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      v12 = sBtlCheckDamageTarget(pUnit);
      if (!v12)
        continue;
      if ((pUnit->para->badstatus & badst) != 0)
        return v10;
    }
  }
  for (j = 0; ; ++j)
  {
    v16 = wk->friend_List;
    if (j >= v16->count)
      break;
    v17 = v16->pUnitL[j]->pUnit;
    if (!v17)
      continue;
    sBtlCheckDamageTarget(v17);
  }
  return 0;
}

// 0x1ed33d0
static bool SEquationno_15(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  s16 MeireiNo;
  u32 flg;

  Skilltbl = sBtlGetSkilltbl(skillid);
  MeireiNo = GetMeireiNo(wk);
  if (MeireiNo != 5)
  {
    if (MeireiNo == 4)
    {
      if ((Skilltbl->flg & 1) != 0 && (Skilltbl->type & 0xFFF) == 3)
        return 1;
    }
    else if (MeireiNo != 3 || (Skilltbl->flg & 1) != 0 && (Skilltbl->type & 0xFFF) == 1)
    {
      return 1;
    }
    return 0;
  }
  flg = Skilltbl->flg;
  if ((flg & 4) != 0 && (flg & 0x81F000) != 0)
    return 1;
  if ((flg & 0x20) == 0)
    return 0;
  if ((flg & 0x400000) != 0)
  {
    return sBtlCheckEnableUseKaja(wk, skillid) > 0;
  }
  else
  {
    return sBtlCheckEnableUseAura(wk, skillid) > 0;
  }
}

// 0x1ed3560
static bool SEquationno_16(SBTLUNIT_WORK *wk, SKLID skillid) {
  u32 flg;
  bool v5;
  s64 v6;
  SBTLUNIT_LISTWORK *friend_List;
  s64 count;
  SBTLUNIT_WORK *pUnit;
  bool v11;
  sdatParaWork_t *now;
  s32 maxhp;

  flg = sBtlGetSkilltbl(skillid)->flg;
  v5 = 0;
  if ((flg & 4) != 0 && (flg & 0x81F000) != 0)
  {
    v6 = 0;
    while (1)
    {
      friend_List = wk->friend_List;
      count = friend_List->count;
      v5 = v6 < count;
      if (v6 >= count)
        return v5;
      pUnit = friend_List->pUnitL[v6]->pUnit;
      if (!pUnit)
        goto LABEL_6;
      v11 = sBtlCheckDamageTarget(pUnit);
      if (!v11)
        goto LABEL_6;
      now = pUnit->para->now;
      maxhp = now->maxhp;
      if (maxhp && 100 * now->hp / maxhp < 20)
        return v5;
LABEL_6:
      ++v6;
    }
  }
  return v5;
}

// 0x1ed36f0
static bool SEquationno_17(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  s16 MeireiNo;
  u32 flg;

  Skilltbl = sBtlGetSkilltbl(skillid);
  MeireiNo = GetMeireiNo(wk);
  if (MeireiNo != 5)
  {
    if (MeireiNo == 4)
    {
      if ((Skilltbl->flg & 1) != 0 && (Skilltbl->type & 0xFFF) == 3)
        return 1;
    }
    else if (MeireiNo == 3 && (Skilltbl->flg & 1) != 0 && (Skilltbl->type & 0xFFF) == 1)
    {
      return 1;
    }
    return 0;
  }
  flg = Skilltbl->flg;
  if ((flg & 4) != 0 && (flg & 0x81F000) != 0)
    return 1;
  if ((flg & 0x20) == 0)
    return 1;
  if ((flg & 0x400000) == 0)
  {
    return sBtlCheckEnableUseAura(wk, skillid) >= 1;
  }
  return sBtlCheckEnableUseKaja(wk, skillid) > 0;
}

// 0x1ed38b0
static bool TEquationno_01(SBTLUNIT_WORK *wk) {
  s32 count;
  s16 *v5;
  SBTLSKILLP_TBL *Skilltbl;
  s64 i;
  SBTLUNIT_LISTWORK *other_List;
  s64 v11;
  SBTLUNIT_WORK *pUnit;
  SBTLACTAI_WORK *actaiwk;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 search_area_r;
  f32 v20;
  f32 v21;
  f32 hit_area_r;
  char *v23;
  u32 attr;
  s32 LargePara;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v28;
  SBTLUNIT_WORK *v29;
  s32 ListID;
  sdfVector4_t vector2;
  f32 v34;
  f32 v35;
  s32 a_pHanshaType;
  sdfVector4_t v37;

  NewSpecific(s16, 0x30u);
  a_pHanshaType = 0;
  count = wk->other_List->count;
  if (count >= 1)
  {
    if (SetOrderTarget(wk))
      return count > 0;
    if (!SetNextTarget(wk))
    {
      if (!CheckEnemyTarget(wk))
      {
        v5 = NewSpecific(s16, 0x30u);
        Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
        for (i = 0; ; ++i)
        {
          other_List = wk->other_List;
          v11 = other_List->count;
          if (i >= v11)
          {
            LODWORD(v11) = wk->other_List->count;
            LargePara = sBtlGetLargePara(v5, v11);
            UnitMng = wk->UnitMng;
            targetID = wk->actaiwk->targetID;
            v28 = sBtlSearchUnit_ID(UnitMng, targetID);
            if (!v28)
              goto LABEL_49;
            v29 = v28;
            if (!sBtlCheckDamageTarget(v29) || (wk->side & 0x81) == 0 || (v29->side & 2) == 0)
            {
LABEL_49:
              ListID = wk->other_List->pUnitL[LargePara]->pUnit->ListID;
              sBtlSetTargetID(wk, ListID);
            }
            return count > 0;
          }
          pUnit = other_List->pUnitL[i]->pUnit;
          if (!pUnit)
            continue;
          if (!sBtlCheckDamageTarget(pUnit))
            continue;
          actaiwk = wk->actaiwk;
          x = pUnit->pos.x;
          y = pUnit->pos.y;
          z = pUnit->pos.z;
          w = pUnit->pos.w;
          search_area_r = actaiwk->search_area_r;
          v37.x = actaiwk->searchpos.x;
          v37.y = actaiwk->searchpos.y;
          v20 = actaiwk->searchpos.z;
          v21 = actaiwk->searchpos.w;
          hit_area_r = pUnit->actaiwk->hit_area_r;
          v34 = actaiwk->searchpos.y;
          v35 = actaiwk->searchpos.x;
          v37.y = v34;
          v37.x = v35;
          v37.z = v20;
          v37.w = v21;
          *(u64 *)&vector2.z = __PAIR64__(LODWORD(w), LODWORD(z));
          *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(x));
          v23 = (char *)v5 + 2 * i;
          if (sBtlCheckCrossCircle(v37, search_area_r, vector2, hit_area_r))
            *((u16 *)v23 + 16) = GetIntervalRand(0, 15) + 20;
          attr = Skilltbl->attr;
          if (sBtlCheckAisyoEx(pUnit, attr, &a_pHanshaType) == 0x4000)
            *((u16 *)v23 + 16) += 28;
        }
      }
    }
  }
  return count > 0;
}

// 0x1ed3d20
static bool TEquationno_0c(SBTLUNIT_WORK *wk) {
  SBTLSKILLP_TBL *Skilltbl;
  s64 v6;
  s32 v7;
  s32 v8;
  bool v9;
  char v10;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_WORK *pUnit;
  bool v13;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 hp;
  s32 v18;
  s32 ListID;

  if (wk->friend_List->count < 1)
    return 0;
  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  if (SetOrderTarget(wk))
    return 1;
  v6 = 0;
  v7 = 999999;
  v8 = 255;
  while (1)
  {
    friend_List = wk->friend_List;
    if (v6 >= friend_List->count)
      break;
    pUnit = friend_List->pUnitL[v6]->pUnit;
    if (!pUnit)
      goto LABEL_18;
    v13 = sBtlCheckDamageTarget(pUnit);
    if (!v13)
      goto LABEL_18;
    now = pUnit->para->now;
    maxhp = now->maxhp;
    if (maxhp)
    {
      hp = now->hp;
      v18 = 100 * hp / maxhp;
      if ((Skilltbl->flg & 0x800000) != 0)
        v9 = pUnit->rejyenecounter < 1 && v18 < 100;
      else
        v9 = v18 < 100;
      v10 = v9;
      if (((u8)v10 & (hp < v7)) != 0)
      {
        v8 = v6;
        v7 = hp;
      }
    }
LABEL_18:
    ++v6;
  }
  if (v8 == 255)
    return 0;
  friend_List = wk->friend_List;
  ListID = friend_List->pUnitL[v8]->pUnit->ListID;
  sBtlSetTargetID(wk, ListID);
  return 1;
}

// 0x1ed3ff0
static bool TEquationno_0d(SBTLUNIT_WORK *wk) {
  u32 badst;
  s64 v5;
  s32 v7;
  s16 v8;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_WORK *pUnit;
  bool v11;
  sdatUnitWork_t *para;
  s32 badst_cnt;
  s32 v15;
  s32 ListID;

  if (wk->friend_List->count < 1)
    return 0;
  if (SetOrderTarget(wk))
    return 1;
  badst = sBtlGetSkilltbl(wk->actwk->use_skillid)->badst;
  v5 = 0;
  v7 = 255;
  v8 = 5400;
  while (1)
  {
    friend_List = wk->friend_List;
    if (v5 >= friend_List->count)
      break;
    pUnit = friend_List->pUnitL[v5]->pUnit;
    if (!pUnit)
      goto LABEL_12;
    v11 = sBtlCheckDamageTarget(pUnit);
    if (!v11)
      goto LABEL_12;
    para = pUnit->para;
    if ((para->badstatus & badst) != 0)
    {
      badst_cnt = para->badst_cnt;
      v15 = v8;
      if (badst_cnt < v8)
        v8 = badst_cnt;
      if (badst_cnt < v15)
        v7 = v5;
    }
LABEL_12:
    ++v5;
  }
  if (v7 == 255)
    return 0;
  friend_List = wk->friend_List;
  ListID = friend_List->pUnitL[v7]->pUnit->ListID;
  sBtlSetTargetID(wk, ListID);
  return 1;
}

// 0x1ed42a0
static bool TEquationno_0e(SBTLUNIT_WORK *wk) {
  s64 v6;
  s32 v7;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_WORK *pUnit;
  s32 ListID;

  if (wk->friend_List->count < 1)
    return 0;
  if (SetOrderTarget(wk))
    return 1;
  v6 = 0;
  v7 = 255;
  while (1)
  {
    friend_List = wk->friend_List;
    if (v6 >= friend_List->count)
      break;
    pUnit = friend_List->pUnitL[v6]->pUnit;
    if (pUnit)
    {
      if (pUnit->ListID == wk->ListID)
        v7 = v6;
    }
    ++v6;
  }
  if (v7 == 255)
    return 0;
  friend_List = wk->friend_List;
  ListID = friend_List->pUnitL[v7]->pUnit->ListID;
  sBtlSetTargetID(wk, ListID);
  return 1;
}

// 0x1ece180
bool sBtlCheckSkillEquation(SBTLUNIT_WORK *wk, s16 adr, SKLID skillid) {
  SBTLAI_EQUATWORK *sbtlai_equat_01_local;
  s32 side;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_LISTWORK *p_friend_List;
  SBTLUNIT_LISTWORK *other_List;
  SBTLUNIT_LISTWORK *p_other_List;
  s32 v19;
  sdatUnitWork_t *para;
  s32 v21;
  SBATTLE_WORK *v23;
  SBTLUNIT_LISTWORK *TargetList;
  u32 v25;
  SBATTLE_WORK *v27;
  s32 v28;
  SBTLUNIT_LISTWORK *v30;
  SBATTLE_WORK *v32;
  SBTLAI_EQUATWORK *v33;
  SBTLAI_EQUATWORK *m_Items;
  bool v36;
  SBTLUNIT_LISTWORK *v38;
  SBTLUNIT_LISTWORK *v39;
  SBTLUNIT_LISTWORK *v40;
  s32 v42;
  s64 v43;
  SBTLAI_EQUATWORK *v44;
  sBtlAI_SkillEquationFuncDelegate v46;
  char v47;
  SBTLAI_EQUATWORK *v48;
  s32 flg;

  if (skillid == 288)
  {
    sbtlai_equat_01_local = sbtlai_equat_01;
    side = wk->side;
  }
  else
  {
    sbtlai_equat_01_local = sbtlai_equat_0a;
    side = wk->side;
  }
  friend_List = wk->friend_List;
  if (friend_List)
  {
    friend_List = wk->friend_List;
    sBtlDeleteUnitList(friend_List, 0);
    p_friend_List = &wk->friend_List;
    p_friend_List = 0;
  }
  other_List = wk->other_List;
  if (other_List)
  {
    sBtlDeleteUnitList(other_List, 0);
    p_other_List = &wk->other_List;
    p_other_List = 0;
    goto LABEL_24;
  }
LABEL_24:
  v19 = side & 0x3F;
  para = wk->para;
  if (sBtlGetBadStatus(para) == 7)
    v21 = 2;
  else
    v21 = v19;
  v23 = wk;
  TargetList = sBtlCreateTargetList(v21);
  v23->friend_List = TargetList;
  if (v21 == 1)
  {
    if (v25)
    {
      v27 = wk;
LABEL_34:
      v28 = 2;
      goto LABEL_38;
    }
    else
    {
      v27 = wk;
      goto LABEL_34;
    }
    goto LABEL_34;
  }
  if (!v25)
  {
    v27 = wk;
    goto LABEL_37;
  }
  v27 = wk;
LABEL_37:
  v28 = 1;
LABEL_38:
  v30 = sBtlCreateTargetList(v28);
  v27->other_List = v30;
  v32 = wk;
  if ((v32->status & 0x2000000) == 0)
  {
    m_Items = sbtlai_equat_01_local;
    v33 = sbtlai_equat_01_local[0];
    if (v33->no == -1)
      goto LABEL_41;
LABEL_51:
    v42 = 1;
    while (1)
    {
      v33 = m_Items;
      v46 = sBtlAI_SkillEquationFunc[v33->no];
      v47 = (v46->invoke_impl)(v46->method_code, wk, skillid, v46->method);
      v48 = m_Items;
      flg = m_Items->flg;
      if ((v47 & 1) != 0)
      {
        if (flg == 255 && !v48->boolflg)
          goto LABEL_61;
      }
      else if (flg == 255 && v48->boolflg)
      {
LABEL_61:
        v36 = 0;
        v38 = wk->friend_List;
        goto LABEL_44;
      }
      v43 = (s64)sbtlai_equat_01_local + 8 * v42++;
      v44 = *(SBTLAI_EQUATWORK *)(v43 + 32);
      m_Items = (v43 + 32);
      v33 = v44;
      if (v44->no == -1)
      {
        goto LABEL_42;
      }
    }
  }
  v32 = wk;
  v32->friend_List->count = 0;
  m_Items = sbtlai_equat_01_local;
  v33 = sbtlai_equat_01_local[0];
  if (v33->no != -1)
    goto LABEL_51;
LABEL_41:
LABEL_42:
  v36 = 1;
  v38 = wk->friend_List;
LABEL_44:
  sBtlDeleteUnitList(v38, 0);
  sBtlDeleteUnitList(wk->other_List, 0);
  v39 = &wk->friend_List;
  v39 = 0;
  v40 = &wk->other_List;
  v40 = 0;
  return v36;
}

// 0x1ed0670
bool sBtlCheckTargetEquation(SBTLUNIT_WORK *wk) {
  s32 v3;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *TargetList;
  s32 targetGroupID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v15;
  s32 GroupID;
  SBATTLE_WORK *v19;
  SBTLUNIT_LISTWORK *TargetList_Group;
  SBTLAI_WORK *aiwk;
  SBATTLE_WORK *v25;
  s32 v26;
  SBTLUNIT_LISTWORK *TargetList_PForward;
  bool TargetUnit;
  SBTLUNIT_LISTWORK *other_List;
  u32 v34;
  SBATTLE_WORK *v36;
  s32 v37;
  SBTLUNIT_LISTWORK *v39;
  SBTLUNIT_LISTWORK *friend_List;
  SBTLUNIT_LISTWORK *p_friend_List;
  SBTLUNIT_LISTWORK *p_other_List;
  u16 Percentage;

  v3 = wk->side & 0x3F;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus - 7 > 1)
  {
    goto LABEL_7;
  }
  if (v3 == 1)
  {
    if (BadStatus == 7)
    {
      aiwk = wk->aiwk;
    }
    else
    {
      Percentage = GetPercentage();
      aiwk = wk->aiwk;
      if (Percentage <= 0x27u)
      {
        v3 = 1;
LABEL_75:
        aiwk->bstside = v3;
        goto LABEL_7;
      }
    }
    v3 = 2;
    goto LABEL_75;
  }
  v3 = 1;
LABEL_7:
  v9 = wk;
  TargetList = sBtlCreateTargetList(v3);
  v9->friend_List = TargetList;
  if (v3 != 1)
  {
    v25 = wk;
    v26 = 1;
LABEL_27:
    TargetList_PForward = sBtlCreateTargetList(v26);
    goto LABEL_33;
  }
  targetGroupID = wk->actaiwk->targetGroupID;
  if (targetGroupID == -1)
  {
    v25 = wk;
    TargetList_PForward = sBtlCreateTargetList_PForward(2);
LABEL_33:
    v25->other_List = TargetList_PForward;
LABEL_34:
    if (!sBtlGetTargetUnit(wk))
      goto LABEL_38;
    TargetUnit = 1;
    goto LABEL_52;
  }
  UnitMng = wk->UnitMng;
  v15 = sBtlSearchUnit_GroupID(UnitMng, targetGroupID);
  if (!v15)
  {
    v25 = wk;
    v26 = 2;
    goto LABEL_27;
  }
  GroupID = v15->GroupID;
  v19 = wk;
  TargetList_Group = sBtlCreateTargetList_Group(2, GroupID);
  v19->other_List = TargetList_Group;
  goto LABEL_34;
LABEL_38:
  other_List = wk->other_List;
  sBtlDeleteUnitList(other_List, 0);
  if (v3 == 1)
  {
    if (v34)
    {
      v36 = wk;
LABEL_44:
      v37 = 2;
      goto LABEL_48;
    }
    else
    {
      v36 = wk;
      goto LABEL_44;
    }
    goto LABEL_44;
  }
  if (!v34)
  {
    v36 = wk;
    goto LABEL_47;
  }
  v36 = wk;
LABEL_47:
  v37 = 1;
LABEL_48:
  v39 = sBtlCreateTargetList(v37);
  v36->other_List = v39;
  TargetUnit = sBtlGetTargetUnit(wk);
LABEL_52:
  friend_List = wk->friend_List;
  sBtlDeleteUnitList(friend_List, 0);
  sBtlDeleteUnitList(wk->other_List, 0);
  p_friend_List = &wk->friend_List;
  p_friend_List = 0;
  p_other_List = &wk->other_List;
  p_other_List = 0;
  return TargetUnit;
}

// 0x1ed4610
bool sBtlAI_SetSeikaku_Action(SBTLUNIT_WORK *wk) {
  u16 Rand;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 priv_area_r;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 enmy_area_r;
  s32 v14;
  f32 frid_area_r;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  u16 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  u16 v35;
  f32 v36;
  SBTLACTAI_WORK *actaiwk;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  s64 v43;
  u16 v44;
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
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  sdfVector4_t v63;
  sdfVector4_t v64;
  sdfVector4_t v65;
  sdfVector4_t v66;
  sdfVector4_t v67;
  sdfVector4_t v68;
  sdfVector4_t v69;
  sdfVector4_t v70;
  sdfVector4_t v71;
  sdfVector4_t v72;

  switch (wk->para->seikaku)
  {
    case 0:
      goto LABEL_39;
    case 1:
      Rand = GetRand(0x64u);
      if (Rand < 0x32u || wk->para->now->maxhp >= 2 * wk->para->now->hp)
      {
        x = wk->pos.x;
        y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        priv_area_r = wk->actaiwk->priv_area_r;
        v63.x = x;
        v63.y = y;
        v63.z = z;
        v63.w = w;
        if (sBtlCheckArea_Atk(wk, v63, priv_area_r + priv_area_r))
          goto LABEL_42;
      }
      v9 = wk->pos.x;
      v10 = wk->pos.y;
      v11 = wk->pos.z;
      v12 = wk->pos.w;
      enmy_area_r = wk->actaiwk->enmy_area_r;
      v64.x = v9;
      v64.y = v10;
      v64.z = v11;
      v64.w = v12;
      v14 = sBtlCheckArea_Masic(wk, v64, enmy_area_r, 0);
      if (v14 != -1)
        goto LABEL_27;
      if (wk->para->now->maxhp >= 2 * wk->para->now->hp)
      {
        frid_area_r = wk->actaiwk->frid_area_r;
        v16 = wk->pos.x;
        v17 = wk->pos.y;
        v18 = wk->pos.z;
        v19 = wk->pos.w;
        v65.y = v17;
        v65.z = v18;
        v65.w = v19;
        v65.x = v16;
        if (sBtlCheckArea(wk, v65, frid_area_r * 0.5))
          goto LABEL_52;
      }
      if (Rand <= 4u)
      {
        v20 = wk->actaiwk->frid_area_r;
        v21 = wk->pos.x;
        v22 = wk->pos.y;
        v23 = wk->pos.z;
        v24 = wk->pos.w;
        v66.x = v21;
        v66.y = v22;
        v66.z = v23;
        v66.w = v24;
        if (sBtlCheckArea(wk, v66, v20 * 0.5))
        {
          v25 = wk->actaiwk->frid_area_r;
          v26 = wk->pos.x;
          v27 = wk->pos.y;
          v28 = wk->pos.z;
          v29 = wk->pos.w;
          v67.x = v26;
          v67.y = v27;
          v67.z = v28;
          v67.w = v29;
          if (sBtlCheckAreaCount(wk, v67, v25 * 0.5) >= 4)
            goto LABEL_52;
        }
      }
      return 0;
    case 2:
      v30 = GetRand(0x64u);
      v31 = wk->pos.x;
      v32 = wk->pos.y;
      v33 = wk->pos.z;
      v34 = wk->pos.w;
      v35 = v30;
      v36 = wk->actaiwk->enmy_area_r;
      v68.x = v31;
      v68.y = v32;
      v68.z = v33;
      v68.w = v34;
      v14 = sBtlCheckArea_Masic(wk, v68, v36, 0);
      if (v14 != -1)
        goto LABEL_27;
      if (v35 <= 0x18u)
      {
        v54 = wk->actaiwk->priv_area_r;
        v50 = wk->pos.x;
        v51 = wk->pos.y;
        v52 = wk->pos.z;
        v53 = wk->pos.w;
        goto LABEL_41;
      }
      if (v35 > 0x31u)
        return 0;
      v58 = wk->actaiwk->frid_area_r;
      v59 = wk->pos.x;
      v60 = wk->pos.y;
      v61 = wk->pos.z;
      v62 = wk->pos.w;
      goto LABEL_51;
    case 4:
      v44 = GetRand(0x64u);
      if (v44 <= 4u)
      {
LABEL_39:
        v50 = wk->pos.x;
        v51 = wk->pos.y;
        v52 = wk->pos.z;
        v53 = wk->pos.w;
        v54 = wk->actaiwk->priv_area_r;
LABEL_41:
        v71.x = v50;
        v71.y = v51;
        v71.z = v52;
        v71.w = v53;
        if (!sBtlCheckArea_Atk(wk, v71, v54 + v54))
          return 0;
LABEL_42:
        *(u32 *)&wk->aiwk->stat = 720898;
        actaiwk = wk->actaiwk;
        actaiwk->spce_area_r = actaiwk->priv_area_r;
        v43 = 0x4040000040000000LL;
        goto LABEL_43;
      }
      if (v44 <= 9u)
      {
        v59 = wk->pos.x;
        v60 = wk->pos.y;
        v61 = wk->pos.z;
        v62 = wk->pos.w;
        v58 = wk->actaiwk->frid_area_r;
LABEL_51:
        v72.y = v60;
        v72.z = v61;
        v72.w = v62;
        v72.x = v59;
        if (!sBtlCheckArea(wk, v72, v58 * 0.5))
          return 0;
LABEL_52:
        *(u32 *)&wk->aiwk->stat = 720898;
        actaiwk = wk->actaiwk;
        actaiwk->spce_area_r = actaiwk->frid_area_r;
        v43 = 0x3FB333333F000000LL;
LABEL_43:
        *(u64 *)&actaiwk->check_area = v43;
        goto LABEL_44;
      }
      if (v44 <= 0xEu)
      {
        v45 = wk->pos.x;
        v46 = wk->pos.y;
        v47 = wk->pos.z;
        v48 = wk->pos.w;
        v49 = wk->actaiwk->enmy_area_r;
        v70.x = v45;
        v70.y = v46;
        v70.z = v47;
        v70.w = v48;
        v14 = sBtlCheckArea_Masic(wk, v70, v49, 0);
        if (v14 != -1)
        {
LABEL_27:
          *(u32 *)&wk->aiwk->stat = 851970;
          actaiwk = wk->actaiwk;
          actaiwk->kaihiID = v14;
LABEL_44:
          actaiwk->actioncnt = 0;
          actaiwk->stat = 1;
          return 1;
        }
      }
      return 0;
    default:
      v38 = wk->pos.x;
      v39 = wk->pos.y;
      v40 = wk->pos.z;
      v41 = wk->pos.w;
      v42 = wk->actaiwk->frid_area_r;
      v69.y = v39;
      v69.z = v40;
      v69.w = v41;
      v69.x = v38;
      if (!sBtlCheckArea(wk, v69, v42 * 0.75))
        return 0;
      *(u32 *)&wk->aiwk->stat = 720898;
      actaiwk = wk->actaiwk;
      actaiwk->spce_area_r = actaiwk->frid_area_r;
      v43 = 0x3FB333333F400000LL;
      goto LABEL_43;
  }
}

// 0x1ed44c0
bool sBtlGetTargetUnit(SBTLUNIT_WORK *wk) {
  SBTLSKILLP_TBL *Skilltbl;
  u32 flg;
  SBTLUNIT_WORK *v11;

  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  if (CheckBSTTarget(wk, Skilltbl))
    return 1;
  flg = Skilltbl->flg;
  if ((flg & 1) != 0)
  {
    v11 = wk;
    return TEquationno_01(v11);
LABEL_13:
    v11 = wk;
    return TEquationno_01(v11);
  }
  if ((flg & 4) != 0)
  {
    if ((flg & 0x10000) != 0)
    {
      return TEquationno_0d(wk);
    }
    else
    {
      return TEquationno_0c(wk);
    }
  }
  else
  {
    if ((flg & 0x200) == 0)
    {
      goto LABEL_13;
    }
    return TEquationno_0e(wk);
  }
}
