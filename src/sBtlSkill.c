#include "types.h"
#include "SKLID.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtlcalc.h"
#include "sbtleff.h"
#include "sbtlplayertbl.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlunit.h"

typedef struct SBTLAUTO_TBL SBTLAUTO_TBL;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLSKLVISUAL_TBL SBTLSKLVISUAL_TBL;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

SBTLSKILLP_TBL *tbldata[1600];
SBTLSKLVISUAL_TBL *visualtbldata;
SBTLAUTO_TBL *autotbldata;

static bool CheckBadStatus(SBTLUNIT_WORK *wk, SKLID sklid);

// 0x1fc8730
static bool CheckBadStatus(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLSKILLP_TBL *v5;
  bool result;
  sdatUnitWork_t *para;

  v5 = 0;
  if ((u32)sklid <= 0x63F)
  {
    if (tbldata)
      v5 = tbldata[sklid];
  }
  result = 0;
  if ((v5->type & 0xFFFu) > 7 || ((1 << LOBYTE(v5->type)) & 0xBA) == 0)
    return result;
  para = wk->para;
  if (sBtlGetBadStatus(para) != 10)
    return 0;
  return ((v5->type & 0x1000) == 0) & sbtlplayertblChkSklNG_MAHUU(wk, sklid);
}

// 0x1fc8920
SKLID sBtlGetExeSkill(SKLID sklid, s32 *pSklid1) {
  SBTLSKILLP_TBL *v5;
  u64 v7;

  v5 = 0;
  if ((u32)sklid <= 0x63F)
  {
    if (tbldata)
      v5 = tbldata[sklid];
  }
  if (*pSklid1)
    *pSklid1 = 0;
  HIDWORD(v7) = sklid - 529;
  LODWORD(v7) = sklid - 529;
  if ((u32)(v7 >> 4) >= 4 && (v5->flg2 & 3) != 0)
    return v5->badst;
  return sklid;
}

// 0x1fc89d0
SKLID GetExeSkill(SKLID sklid) {
  SBTLSKILLP_TBL *v3;
  u64 v5;

  v3 = 0;
  if ((u32)sklid <= 0x63F)
  {
    if (tbldata)
      v3 = tbldata[sklid];
  }
  HIDWORD(v5) = sklid - 529;
  LODWORD(v5) = sklid - 529;
  if ((u32)(v5 >> 4) >= 4 && (v3->flg2 & 3) != 0)
    return v3->badst;
  return sklid;
}

// 0x1fc8a60
bool sBtlCheckHaveSkill(SBTLUNIT_WORK *wk, SKLID sklid) {
  SKLID *haveskill;

  haveskill = wk->haveskill;
  if (haveskill[0] == sklid)
    return 1;
  if (haveskill[1] == sklid)
    return 1;
  if (haveskill[2] == sklid)
    return 1;
  if (haveskill[3] == sklid)
    return 1;
  if (haveskill[4] == sklid)
    return 1;
  if (haveskill[5] == sklid)
    return 1;
  if (haveskill[6] == sklid)
    return 1;
  if (haveskill[7] == sklid)
    return 1;
  if (haveskill[8] == sklid)
    return 1;
  if (haveskill[9] == sklid)
    return 1;
  if (haveskill[10] == sklid)
    return 1;
  if (haveskill[11] == sklid)
    return 1;
  if (haveskill[12] == sklid)
    return 1;
  if (haveskill[13] == sklid)
    return 1;
  if (haveskill[14] == sklid)
    return 1;
  if (haveskill[15] == sklid)
    return 1;
  if (haveskill[16] == sklid)
    return 1;
  if (haveskill[17] == sklid)
    return 1;
  return haveskill[18] == sklid;
}

// 0x1fc88b0
SBTLSKILLP_TBL *sBtlGetSkilltbl(SKLID skillid) {
  SBTLSKILLP_TBL *result;

  result = 0;
  if ((u32)skillid <= 0x63F)
  {
    if (tbldata)
      return tbldata[skillid];
  }
  return result;
}

// 0x1fc8be0
SBTLSKLVISUAL_TBL *sBtlGetSklVisualTbl(SKLID sklid) {
  SBTLSKLVISUAL_TBL *result;

  result = 0;
  if ((sklid & 0x80000000) == 0)
  {
    if (SLODWORD(visualtbldata->max_length) > sklid)
      return visualtbldata[sklid];
  }
  return result;
}

// 0x1fc8c50
bool sBtlSetSkill_MotionData(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLSKILLP_TBL *v5;
  SBTLSKLVISUAL_TBL *v7;
  s32 req_skill_motion;
  char v10;
  s32 v11;
  SBATTLE_WORK *v13;
  s32 battlemode;
  SBTLUNIT_WORK *v15;
  s32 v16;
  s32 scrStep3;
  SBTLUNIT_WORK *v18;
  s32 v19;
  SBTLUNIT_WORK *AnotherEnemy;
  s32 motionno;

  v5 = 0;
  if ((u32)sklid <= 0x63F)
  {
    if (tbldata)
      v5 = tbldata[sklid];
  }
  v7 = 0;
  if ((sklid & 0x80000000) == 0)
  {
    if (SLODWORD(visualtbldata->max_length) > sklid)
      v7 = visualtbldata[sklid];
  }
  req_skill_motion = wk->req_skill_motion;
  if (req_skill_motion == -1)
  {
    req_skill_motion = v7->motionno;
    v10 = sklid + 78;
    if ((u32)(sklid - 690) <= 6)
    {
LABEL_16:
      v11 = 1 << v10;
      if ((v11 & 0x38) == 0)
      {
        if ((v11 & 0x43) != 0)
        {
          req_skill_motion = 49;
LABEL_26:
          v13 = wk;
          battlemode = (u16)v13->battlemode;
          if (battlemode != 3)
            goto LABEL_36;
          goto LABEL_32;
        }
        req_skill_motion = 50;
      }
      goto LABEL_26;
    }
  }
  else
  {
    wk->req_skill_motion = -1;
    v10 = sklid + 78;
    if ((u32)(sklid - 690) <= 6)
      goto LABEL_16;
  }
  if (sklid == 158)
  {
    req_skill_motion = 52;
    goto LABEL_26;
  }
  else
  {
    if (sklid == 701)
      req_skill_motion = 51;
    goto LABEL_26;
  }
  v13 = wk;
  battlemode = (u16)v13->battlemode;
  if (battlemode != 3)
    goto LABEL_36;
LABEL_32:
  if ((v5->type & 0xFFF) == 8)
  {
    v15 = wk;
    v16 = 4;
LABEL_64:
    sBtlSetMotion(v15, v16, 0, 0, 0);
    return 1;
  }
LABEL_36:
  if (battlemode != 3)
    goto LABEL_45;
  if (v13->mode != 11)
    goto LABEL_45;
  if ((wk->side & 1) != 0)
  {
    if (wk->motionID != 29)
    {
      v16 = 29;
      v15 = wk;
      goto LABEL_64;
    }
    return 1;
  }
LABEL_45:
  if (sklid != 465)
  {
    sBtlSetMotion(wk, req_skill_motion, 0, 0, 0);
    if (sklid != 890)
      return 1;
    AnotherEnemy = sBtlGetAnotherEnemy(wk);
    motionno = v7->motionno;
    v15 = AnotherEnemy;
    v16 = motionno;
    goto LABEL_64;
  }
  scrStep3 = wk->aiwk->scrStep3;
  if (scrStep3 == 1)
  {
    v18 = wk;
    v19 = 16;
    goto LABEL_72;
  }
  if (!scrStep3)
  {
    v19 = 17;
    v18 = wk;
    goto LABEL_72;
  }
  if (scrStep3 != -1)
    return 1;
  v18 = wk;
  v19 = 15;
LABEL_72:
  sBtlSetMotion_ID(v18, v19, 0, 0, 0);
  return 1;
}

// 0x1fc9080
bool sBtlSetSkill_EffectData(SBTLUNIT_WORK *wk, SKLID sklid, bool r_kaja) {
  SBTLSKLVISUAL_TBL *v6;
  bool v9;
  SBTLSKILLP_TBL *v10;
  u32 flg;
  u32 attrtime;
  sdatUnitWork_t *para;
  s32 side;
  SBTLUNIT_WORK *v16;
  SBTLUNIT_LISTWORK *SideList;
  s64 v18;
  SBTLAI_WORK *aiwk;
  SBTLUNIT_WORK *pUnit;
  tagSBTLSKL_AURA_WORK *wkAura;
  s32 AuraIdx;
  f32 n1;
  s32 v24;
  tagSBTLSKL_AURA_WORK *v25;
  tagSBTLSKL_AURA_WORK *v26;
  s64 v27;
  tagSBTLSKL_AURA_WORK *v28;
  tagSBTLSKL_AURA_WORK *v29;
  SBTLSM_LISTWORK *v31;
  s32 v32;
  SBTLSM_LISTWORK *v33;
  SBTLUNIT_WORK *v34;
  SBTLSM_LISTWORK *sysmsgList;
  SBTLSM_LISTWORK *v38;
  s32 v39;
  SBTLSM_LISTWORK *v40;
  SBTLUNIT_WORK *v41;
  SBTLSM_LISTWORK *v43;
  SBTLSM_LISTWORK *v45;
  s32 v46;
  s32 v48;
  s32 v49;
  s32 BothSide;
  SBTLSKLVISUAL_TBL *v52;

  v6 = 0;
  if (sklid >= 0)
  {
    if (SLODWORD(visualtbldata->max_length) > sklid)
      v6 = visualtbldata[sklid];
  }
  sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
  v9 = CheckBadStatus(wk, sklid);
  if (!v9)
  {
    v10 = 0;
    if ((u32)sklid <= 0x63F)
    {
      if (tbldata)
        v10 = tbldata[sklid];
    }
    flg = v10->flg;
    if ((flg & 0x7000000) == 0 || (flg & 0x400000) != 0)
      goto LABEL_80;
    attrtime = v10->attrtime;
    para = wk->para;
    if (sBtlChkHaveMemSkl(para, 43))
      attrtime += wk->para->autost_cnt;
    v52 = v6;
    side = wk->side;
    v16 = wk;
    BothSide = sBtlGetBothSide(wk, side);
    SideList = sBtlCreateSideList(BothSide, 0);
    if (SideList->count >= 1)
    {
      v18 = 0;
      do
      {
        pUnit = SideList->pUnitL[v18]->pUnit;
        wkAura = pUnit->wkAura;
        pUnit->aurakind |= v10->flg;
        AuraIdx = sBtlGetAuraIdx(sklid);
        n1 = v10->n1;
        v24 = n1;
        v25 = wkAura[AuraIdx];
        v26 = pUnit->wkAura;
        if (n1 == INFINITY)
          v24 = 0x80000000;
        v25->aurapara = v24;
        v27 = (s64)v26 + 8 * sBtlGetAuraIdx(sklid);
        v28 = pUnit->wkAura;
        *(u32 *)(*(u64 *)(v27 + 32) + 20) = attrtime;
        v28[sBtlGetAuraIdx(sklid)]->auraskl = 0;
        if (pUnit == v16)
        {
          v29 = pUnit->wkAura;
          v29[sBtlGetAuraIdx(sklid)]->auraskl = sklid;
          aiwk = v16->aiwk;
          aiwk->cmndFrm = 0;
          aiwk->cmndFrmMax = attrtime;
          v16->drawgaugetype = 4;
        }
        ++v18;
      }
      while (v18 < SideList->count);
    }
    sBtlDeleteUnitList(SideList, 0);
    wk = v16;
    v6 = v52;
    if ((v10->flg & 0x1000000) != 0)
    {
      if ((BothSide & 1) != 0)
      {
        sysmsgList = wk->sysmsgList;
        v33 = sysmsgList;
        v34 = wk;
        v32 = 63;
      }
      else
      {
        if ((BothSide & 2) == 0)
          goto LABEL_52;
        v31 = wk->sysmsgList;
        v32 = 67;
        v33 = v31;
        v34 = wk;
      }
      sBtlCreateSM(v33, v34, v32, 0, 0, 120);
    }
LABEL_52:
    if ((v10->flg & 0x4000000) == 0)
      goto LABEL_66;
    if ((BothSide & 1) != 0)
    {
      v43 = wk->sysmsgList;
      v40 = v43;
      v41 = wk;
      v39 = 64;
    }
    else
    {
      if ((BothSide & 2) == 0)
        goto LABEL_66;
      v38 = wk->sysmsgList;
      v39 = 68;
      v40 = v38;
      v41 = wk;
    }
    sBtlCreateSM(v40, v41, v39, 0, 0, 120);
LABEL_66:
    if ((v10->flg & 0x2000000) != 0)
    {
      if ((BothSide & 1) != 0)
      {
        v45 = wk->sysmsgList;
        v46 = 65;
        goto LABEL_79;
      }
      if ((BothSide & 2) != 0)
      {
        v45 = wk->sysmsgList;
        v46 = 69;
LABEL_79:
        sBtlCreateSM(v45, wk, v46, 0, 0, 120);
      }
    }
LABEL_80:
    if (sklid == 149 || !v6->SABno)
    {
      if ((sklid & 0xFFFFFFFE) == 0x510)
      {
        v49 = wk->side;
        sBtlCheckEffectData_GunMode2(wk, sklid, 1u, 0, v49, -1, 0);
      }
    }
    else
    {
      v48 = wk->side;
      sBtlCheckEffectData(wk, sklid, 1u, 0, v48, -1, 0);
    }
  }
  return !v9;
}

// 0x1fc96e0
bool sBtlSetHatData(SBTLUNIT_WORK *wk, SKLID sklid) {
  s32 h_effectno;
  s32 side;

  h_effectno = visualtbldata[sklid]->h_effectno;
  if (h_effectno)
  {
    side = wk->side;
    sBtlCheckEffectData(wk, h_effectno, 1u, 0, side, -1, 0);
  }
  return 1;
}

// 0x1fc97b0
bool sBtlSetSkillData(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLSKLVISUAL_TBL *v5;
  s32 motionno;
  s32 side;

  v5 = visualtbldata[sklid];
  motionno = v5->motionno;
  sBtlSetMotion(wk, motionno, 0, 0, 1);
  if (v5->SABno)
  {
    side = wk->side;
    sBtlCheckEffectData(wk, sklid, 1u, 0, side, -1, 0);
  }
  return 1;
}

// 0x1fc98d0
bool sBtlSetSkillData_EffectOnly(SBTLUNIT_WORK *wk, SKLID sklid) {
  s32 side;

  if (visualtbldata[sklid]->SABno)
  {
    side = wk->side;
    sBtlCheckEffectData(wk, sklid, 1u, 0, side, -1, 0);
  }
  return 1;
}

// 0x1fc99a0
bool sBtlCheckMHTData(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLSKLVISUAL_TBL *v5;
  sdatUnitWork_t *para;
  s32 next_motionno;

  v5 = 0;
  if (sklid >= 0)
  {
    if (SLODWORD(visualtbldata->max_length) > sklid)
      v5 = visualtbldata[sklid];
  }
  para = wk->para;
  sBtlGetBadStatus(wk->para);
  if ((v5->flg & 4) == 0)
    return 1;
  if (CheckBadStatus(wk, sklid))
  {
    sBtlSetMotion(wk, 0, 0, 0, 0);
    return 1;
  }
  else
  {
    next_motionno = wk->next_motionno;
    sBtlSetMotionHit(wk, next_motionno, sklid);
    return 1;
  }
}

// 0x1fc9b60
void sBtlKettouProc(void) {
  _S_KETTOU *kettou;
  s32 m_stp;
  SBTLUNIT_WORK *v4;
  _S_KETTOU *v6;
  s32 v7;
  bool v8;
  SBTLUNIT_WORK *m_pUnit;

  kettou = wk->kettou;
  m_stp = kettou->m_stp;
  if (!m_stp)
    return;
  if (m_stp == 2)
  {
    kettou = wk->kettou;
    v7 = kettou->m_cnt + 1;
    v8 = kettou->m_cnt - 600 < 0;
    kettou->m_cnt = v7;
    if (v8 == __OFSUB__(v7, 601))
    {
      kettou = wk->kettou;
      m_pUnit = kettou->m_pUnit;
      sBtlEndWaitALL(m_pUnit, 0);
      wk->kettou->m_stp = 0;
    }
    return;
  }
  if (m_stp == 1)
  {
    v4 = kettou->m_pUnit;
    sBtlBgnWaitALL(v4);
    v6 = wk->kettou;
    *(u64 *)&v6->m_stp = (u32)(v6->m_stp + 1);
    return;
  }
}
