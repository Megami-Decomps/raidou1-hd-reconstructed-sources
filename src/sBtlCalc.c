#include "types.h"
#include "AUTO.h"
#include "BST.h"
#include "BSTF.h"
#include "ITM.h"
#include "SBTLACTION_ST.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"
#include "aw_shieldb_wait.h"
#include "cfg.h"
#include "cmpitem.h"
#include "configgame.h"
#include "dat.h"
#include "dvl.h"
#include "evt.h"
#include "evtbit.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlcalc.h"
#include "sbtldmg.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlexp.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayertbl.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlweapon.h"
#include "sdfmodel.h"
#include "smnr.h"

#define VICE_VAL_1ST 0
#define VICE_LVL0_VAL 0
#define VICE_LVL1_VAL 300
#define VICE_LVL2_VAL 1000
#define VICE_LVL3_VAL 2000
#define VICE_LVL4_VAL 3000
#define VICE_LVL5_VAL 4000
#define VICE_LVL0 0
#define VICE_LVL1 1
#define VICE_LVL2 2
#define VICE_LVL3 3
#define VICE_LVL4 4
#define VICE_LVL5 5
#define CONTINUE_ADD_VAL 100
#define MOUDOKU_TIME 1800
#define KOFUN_TIME 600
#define HUUIN_TIME 3600
#define INF_TIME 9999
#define BREAK_CORRECTION 1.5
#define SBTLHARDG_MODE_ATK 2
#define SBTLHARDG_MODE_DEF 2
#define PLAYER_TECPARAUP_MAX 13

typedef struct SBTLAISYO_DATAWORK SBTLAISYO_DATAWORK;
typedef struct SBTLCALC_DMGWORK SBTLCALC_DMGWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLSKL_KAJA_WORK SBTLSKL_KAJA_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct TEXCOLOR_WORK TEXCOLOR_WORK;
typedef struct sdatParaWork_t sdatParaWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

SBTLAISYO_DATAWORK *aisyo_tbldata[544];
TEXCOLOR_WORK *bstcolor_tbldata;
TEXCOLOR_WORK *bstcolor_tbldata_raidou;

static bool SetBadStatusCounter(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, BST badstno, s32 acterID, SKLID sklid);
static s16 c_DITEMMASK(s16 para);
static s32 GetDamage_Rejyene(SBTLUNIT_WORK *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, bool calc_only);
static bool CheckBadStatusPrioritySame(BSTF _par1, BSTF _par2, SBTLUNIT_WORK *wk);
static void WeakBstDvlTk(SBTLUNIT_WORK *wk, BST badno);
static s32 GetDamageLevel(SBTLUNIT_WORK *target, LTYPE ltype, s32 damage, s32 atk_raito);

// 0x1ed5280
static bool SetBadStatusCounter(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, BST badstno, s32 acterID, SKLID sklid) {
  s32 attrtime;
  u32 attr;
  s16 v12;
  bool v16;
  SBTLEXP_LISTWORK *expList;
  sdatUnitWork_t *para;
  s32 badstatus;
  s32 a_pHanshaType;

  a_pHanshaType = 0;
  attrtime = ptbl->attrtime;
  attr = ptbl->attr;
  v12 = sBtlCheckAisyoEx(wk, attr, &a_pHanshaType);
  if (badstno == 14)
  {
    sBtlPlaySE(0x10025u);
    attrtime = 180;
    goto LABEL_16;
  }
  if (badstno != 13)
  {
    if (badstno == 10)
    {
      if ((wk->side & 0x80) != 0)
        attrtime = 900;
      else
        attrtime = 1800;
      if ((wk->side & 2) != 0)
        goto LABEL_27;
      goto LABEL_17;
    }
LABEL_16:
    if ((wk->side & 2) != 0)
      goto LABEL_27;
    goto LABEL_17;
  }
  if ((v12 & 0x4000) == 0 || (ptbl->attr & 0x401) == 0)
    attrtime = 180;
  if ((wk->side & 2) != 0)
  {
LABEL_27:
    if (badstno != 14 && wk->weak_shild)
      return 0;
    expList = wk->expList;
    sBtlSetRirituEnemyHD(expList, wk, 0, 0, 16);
    goto LABEL_34;
  }
LABEL_17:
  attrtime = sBtlCalcWeakTime(wk, attrtime);
  if ((wk->side & 2) != 0)
    goto LABEL_27;
LABEL_34:
  para = wk->para;
  badstatus = para->badstatus;
  para->badst_cnt = attrtime;
  *(u32 *)&para->badst_cnt2 = 0;
  para->badstatus = badstatus | (1 << badstno);
  if ((wk->status & 8) == 0)
  {
    wk->noWeakStfCnt = 0;
    sBtlSetBadStatusAction(wk, 9, attrtime);
    if ((wk->side & 0x80) == 0)
      goto LABEL_42;
LABEL_40:
    v16 = 1;
    if (badstno == 7 || badstno == 13)
      return v16;
    goto LABEL_42;
  }
  wk->noWeakStfCnt = attrtime;
  if ((wk->side & 0x80) != 0)
    goto LABEL_40;
LABEL_42:
  v16 = 1;
  sBtlSetMotion(wk, 1, 0, 0, 0);
  return v16;
}

// 0x1ed59a0
void sBtlDeleteShild(SBTLUNIT_WORK *wk, SKLID sklid, s32 del_raito) {
  s32 weak_shild;
  s64 v8;
  u64 v9;
  s64 v10;
  s32 v11;
  s64 v12;
  char *v14;
  SKLID *spiritSkill;
  f32 v16;
  SBTLUNIT_WORK *PChara;

  weak_shild = wk->weak_shild;
  v8 = 1374389535 * sBtlGetSkilltbl(sklid)->shild_dmg * del_raito;
  v9 = (u64)v8 >> 63;
  v10 = v8 >> 37;
  v11 = v10 + v9;
  v12 = 0;
  while (1)
  {
    spiritSkill = GBWK->player->spiritSkill;
    if (v12 >= SLODWORD(spiritSkill->max_length))
      break;
    spiritSkill = GBWK->player->spiritSkill;
    v14 = (char *)spiritSkill + 4 * v12++;
    if (*((u32 *)v14 + 8) == 1391)
    {
      v16 = (f32)v11 * 1.5;
      if (v16 == INFINITY)
        v11 = 0x80000000;
      else
        v11 = v16;
      break;
    }
  }
  wk->weak_shild = (wk->weak_shild - v11) & ~((wk->weak_shild - v11) >> 31);
  WeakGageAnimCtrl(wk->bsc, wk, 1, 0);
  if ((wk->side & 2) != 0 && weak_shild && !wk->weak_shild)
  {
    PChara = sBtlGetPChara();
    sBtlSpiritAddDirect(PChara, 12);
  }
}

// 0x1ed5cb0
u32 sBtlWeakShildActive(SBTLUNIT_WORK *wk, u32 attr, s32 acterID, SKLID sklid) {
  s32 weak_shild;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLEFF_LISTWORK *effList;
  sdfVector4_t v17;

  weak_shild = wk->weak_shild;
  if ((attr & 0x204000) != 0 && weak_shild)
  {
    sBtlDeleteShild(wk, sklid, 300);
    attr &= 0xFFDFBFFF;
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    effList = wk->effList;
    v17.x = x;
    v17.y = y;
    v17.z = z;
    v17.w = w;
    sBtlCreateEff(effList, wk, 8, 0, v17, 0x80808080, 0, 1.0, 0);
    if (!wk->weak_shild)
LABEL_17:
      Add(wk->ListID, acterID, 0);
  }
  else if (weak_shild)
  {
    sBtlDeleteShild(wk, sklid, 100);
    if (!wk->weak_shild)
      goto LABEL_17;
  }
  return attr;
}

// 0x1ed5e50
s32 sBtlGetWeakShildCount(SBTLUNIT_WORK *wk) {
  if (wk)
    LODWORD(wk) = wk->weak_shild;
  return (s32)wk;
}

// 0x1ed5e60
bool sBtlCheckBadStatus_Color(SBTLUNIT_WORK *wk, BST badstno) {
  TEXCOLOR_WORK *v10;

  if (!bstcolor_tbldata)
    return 0;
  if ((wk->side & 0x80) != 0)
  {
    v10 = bstcolor_tbldata_raidou[badstno];
    if (v10)
      return v10->flg != 0;
  }
  {
    v10 = bstcolor_tbldata[badstno];
    if (v10)
      return v10->flg != 0;
  }
  else
  {
    v10 = bstcolor_tbldata[badstno];
    if (v10)
      return v10->flg != 0;
  }
  return 0;
}

// 0x1ed60a0
bool sBtlSetBadStatus_Color(SBTLUNIT_WORK *wk, BST badstno) {
  TEXCOLOR_WORK **p_bstcolor_tbldata;
  TEXCOLOR_WORK *v10;
  u32 v11;
  f32 ratio;
  f32 v13;
  evtUnitHandle_t *hEveUnit;
  f32 rim_r;
  f32 rim_g;
  f32 rim_p;
  f32 rim_b;
  f32 v19;
  evtUnitHandle_t *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;

  if ((wk->side & 0x80) == 0)
  {
    p_bstcolor_tbldata = &bstcolor_tbldata;
    goto LABEL_16;
  }
  p_bstcolor_tbldata = &bstcolor_tbldata_raidou;
LABEL_16:
  v10 = (*p_bstcolor_tbldata)[badstno];
  v11 = (v10->mb << 16) | (v10->mg << 8) | v10->mr | 0x80000000;
  switch (v10->flg)
  {
    case 2:
    case 3:
      ratio = v10->ratio;
      sBtlSetChangeModelColor_DST(wk, 0x80808080, v11, ratio);
      sBtlChangeModelColor_DST(wk);
      break;
    case 4:
      v13 = v10->ratio;
      sBtlSetChangeModelColor_DST(wk, 0x80000000, v11, v13);
      sBtlChangeModelColor_DST(wk);
      hEveUnit = wk->hEveUnit;
      rim_r = v10->rim_r;
      rim_g = v10->rim_g;
      rim_b = v10->rim_b;
      rim_p = v10->rim_p;
      evtSetUnitRim(hEveUnit, rim_r, rim_g, rim_b, rim_p);
      break;
    case 5:
      v19 = v10->ratio;
      sBtlSetChangeModelColor_DST(wk, 0x80000000, v11, v19);
      sBtlChangeModelColor_DST(wk);
      v20 = wk->hEveUnit;
      v21 = v10->rim_r;
      v22 = v10->rim_g;
      v24 = v10->rim_b;
      v23 = v10->rim_p;
      evtSetUnitRim(v20, v21, v22, v24, v23);
      wk->stoneUse = 1;
      break;
    default:
      return 1;
  }
  return 1;
}

// 0x1ed6370
void sBtlReetBadStatus_Color(SBTLUNIT_WORK *wk) {
  evtUnitHandle_t *hEveUnit;

  sBtlResetModelColor(wk);
  sBtlResetModelColor_DST(wk);
  hEveUnit = wk->hEveUnit;
  evtSetUnitRim(hEveUnit, 1.0, 1.0, 1.0, 1.0);
  wk->stoneUse = 0;
}

// 0x1ed5830
void sBtlSetBadStatusAction(SBTLUNIT_WORK *wk, SBTLACTION_ST st, s32 cnt) {
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  SBTLACTAI_WORK *actaiwk;
  u32 v11;
  s32 status;
  s32 v13;

  sBtlSetAction(wk, st, cnt);
  hitList = wk->hitList;
  sBtlClearHitC(hitList, wk);
  effList = wk->effList;
  sBtlForceReset(effList, wk);
  actaiwk = wk->actaiwk;
  v11 = wk->status | 0x20;
  status = actaiwk->status;
  v13 = wk->vstatus | 0x80;
  wk->actwk->gravcnt = 0;
  wk->status = v11;
  wk->vstatus = v13;
  actaiwk->status = status & 0xFFFFFFDF;
  sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
}

// 0x1ed6430
void sBtlCheckBadStatus_Weak(SBTLUNIT_WORK *wk, SKLID sklid, SBTLSKILLP_TBL *ptbl, s32 acterID) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 hstatus;
  s32 v14;
  sdatUnitWork_t *v16;
  SBTLSTP_LISTWORK *stpList;
  s32 attrtime;
  s32 v20;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus <= 0xD)
  {
    if (BadStatus != 5)
    {
      hstatus = wk->hstatus;
      if ((hstatus & 0x10) != 0)
      {
        wk->getMag = 0;
        wk->hstatus = hstatus & 0xFFFFFFEF;
      }
    }
  }
  v14 = wk->hstatus;
  wk->hstatus_old = v14;
  if ((v14 & 0x10) != 0)
    return;
  v16 = wk->para;
  if (v16)
  {
    if ((v16->koufunst & 0x20) != 0)
      return;
  }
  if ((wk->side & 0x80) != 0)
    return;
  if (sklid <= 443)
  {
    if ((u32)(sklid - 427) <= 0x10 && ((1 << (sklid + 85)) & 0x10021) != 0)
      return;
    goto LABEL_29;
  }
  if (sklid == 450 || sklid == 903 || sklid == 1131)
    return;
LABEL_29:
  if (!wk->weak_shild)
  {
    sBtlSetHstatusWeak(wk);
    wk->weak_shild_next = 1;
    wk->aiwk->scrflag |= 0x400000u;
    stpList = wk->stpList;
    attrtime = ptbl->attrtime;
    v20 = sBtlCalcWeakTime(wk, attrtime);
    sBtlCreateSTP_Unit(stpList, wk, 1, v20, ptbl->badst, ptbl->attr);
    *(u64 *)&wk->WeakReceiveFlg = 1;
    wk->weak_attrinvtime_cnt = 0;
    ResetAction(wk, 1, 0);
  }
}

// 0x1ed6860
void sBtlSetHstatusWeak(SBTLUNIT_WORK *wk) {
  void *Instance;
  void *v3;

  if (wk)
  {
    wk->hstatus |= 0x10u;
    if (wk->para->devilid == 291)
    {
      wk->status &= ~0x80000u;
      Instance = get_Instance(0);
      if (Check(Instance, 0, 0))
      {
        v3 = get_Instance(0);
        Stop(v3, 0, 0);
      }
    }
  }
}

// 0x1ed67f0
void sBtlSetHstatusWeakOld(SBTLUNIT_WORK *wk) {
  wk->hstatus_old = wk->hstatus;
}

// 0x1ed68d0
static s16 c_DITEMMASK(s16 para) {
  return (u8)para;
}

// 0x1ed68e0
void sBtlResetItemPara(sdatUnitWork_t *unit) {
  sdatParaWork_t *pitem;
  s16 str_low;
  sdatParaWork_t *v5;
  s16 vit_low;

  pitem = unit->pitem;
  *(u64 *)&pitem->hp = 0;
  *(u64 *)&pitem->mp = 0;
  str_low = LOBYTE(pitem->str);
  v5 = pitem;
  v5 = unit->pitem;
  vit_low = LOBYTE(v5->vit);
  pitem->str = str_low;
  v5->vit = vit_low;
  v5->tec = LOBYTE(v5->tec);
  v5->luck = LOBYTE(v5->luck);
  *(u64 *)&unit->itemstatus = unit->itemstatus & 0x3FFFFCF0;
}

// 0x1ed6980
bool sBtlAutoRec(SBTLUNIT_WORK *wk, s32 para) {
  sdatUnitWork_t *v5;
  sdatParaWork_t *now;
  s32 hp;
  s32 maxhp;
  s32 v9;
  s32 v10;
  s32 v15;
  sdatParaWork_t *v16;
  s32 v18;
  s32 v19;
  s32 *p_hp;
  f32 x;
  f32 y;
  SBTLEFF_LISTWORK *effList;
  f32 w;
  f32 z;
  sdfVector4_t v28;

  v5 = wk->para;
  now = v5->now;
  hp = now->hp;
  maxhp = now->maxhp;
  if (hp < maxhp)
  {
    if (para <= 1)
      para = 1;
    v9 = hp + para;
    v10 = maxhp - hp;
    if (v9 > maxhp)
      para = v10;
    if ((wk->side & 1) != 0)
    {
      if ((wk->status3 & 0x8000000) != 0)
      {
        if (para >= 0)
          v15 = para;
        else
          v15 = para + 1;
        para = v15 >> 1;
      }
    }
    v16 = wk->para->now;
    v18 = v16->hp;
    v19 = v16->maxhp;
    p_hp = &v16->hp;
    *p_hp = v18 + para;
    LimitRange(p_hp, 0, v19);
    sBtlCreateAnim_Unit(wk, 0, para, 0, 3, 0);
    x = wk->pos.x;
    y = wk->pos.y;
    effList = wk->effList;
    z = wk->pos.z;
    w = wk->pos.w;
    v28.x = x;
    v28.y = y;
    v28.z = z;
    v28.w = w;
    sBtlCreateEff(effList, wk, 25, 0, v28, 0x80808080, 0, 1.0, 0);
  }
  return 1;
}

// 0x1ed6810
bool sBtlCheckBadStatus_BossSkill(SKLID sklid) {
  if (sklid > 443)
    return sklid == 450 || sklid == 1131 || sklid == 903;
  if ((u32)(sklid - 427) >= 0x11)
    return 0;
  else
    return (0x10021u >> (sklid + 85)) & 1;
}

// 0x1ed6c10
void sBtlCheckD3POff(SBTLUNIT_WORK *wk, BST bstno) {
  if (wk->major && (bstno == 6 || bstno == 1))
    wk->hModel->stat |= 2u;
}

// 0x1ed6c40
s32 CalcItem_Battle(SBTLUNIT_WORK *wklock, sdatUnitWork_t *unit, s32 itemid) {
  SBTLCALC_DMGWORK *v7;
  s32 sklid;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v10;
  MethodInfo *v11;
  SBTLSKILLP_TBL *v12;
  u32 flg;
  s32 Damage_I_REC_P;
  s32 *v17;
  s32 v18;
  u16 Percentage;
  s64 v21;
  u32 v22;
  u32 badst;
  s32 badstatus;
  u32 v33;
  sdatParaWork_t *pitem;
  s16 str_low;
  sdatParaWork_t *v36;
  s16 vit_low;

  v7 = Allocate(SBTLCALC_DMGWORK);
  if (!CheckLiveTarget(wklock))
    return 0;
  sklid = sBtlGetItemtbl(itemid)->sklid;
  if (!sklid)
    return 0;
  Skilltbl = sBtlGetSkilltbl(sklid);
  v10 = Skilltbl;
  if (!cmpChkEnableUseUnit(unit, itemid))
    return 0;
  flg = v10->flg;
  if ((flg & 0x1000) == 0)
  {
    Damage_I_REC_P = 0;
    if ((flg & 0x2000) == 0)
      goto LABEL_56;
LABEL_24:
    v7->n1 = v10->n1;
    Damage_I_REC_P = sBtlGetDamage_I_REC_P(unit, v7, v12, 0);
    sBtlCreateAnim_Unit(wklock, 0, Damage_I_REC_P, 0, 3, 0);
    if (sklid != 323)
      goto LABEL_55;
    v17 = NewSpecific(s32, 5u);
    InitializeArray_55364416(v17, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__83F07A0FF7F15BB48E87D6CE388FC191B140534C69BB3EB88A858ABCF11096E1, 0);
    v18 = *(u32 *)((char *)v17 + 24);
    Percentage = GetPercentage();
    v21 = 0;
    v22 = 18;
    while ((v18 & ~(v18 >> 31)) != (u32)v21)
    {
      if (100 / v18 * (s32)++v21 > Percentage)
      {
        v22 = *(u32 *)((s64)(char *)v17 + 4 * v21 + 28);
        break;
      }
    }
    if (wklock->para->badstatus)
      goto LABEL_55;
    if ((~wklock->side & 0x81) != 0)
      goto LABEL_46;
    if (wk->battlemode == 3)
    {
LABEL_46:
      if (wklock->actwk->status == 57 && (v22 - 7 < 2 || v22 == 12))
        v22 = 11;
    }
    else
    {
      if (sBtlGetSpiritSkillChk(1392))
        goto LABEL_55;
    }
    sBtlSetBadStatus_No(wklock, 323, v22, 0, (s32)v14);
LABEL_55:
    wklock->total_recover += Damage_I_REC_P;
    flg = v10->flg;
    goto LABEL_56;
  }
  v7->n0 = v10->n0;
  Damage_I_REC_P = sBtlGetDamage_I_REC_K(unit, v7, v12, 0);
  sBtlCreateAnim_Unit(wklock, 0, Damage_I_REC_P, 0, 3, 0);
  wklock->total_recover += Damage_I_REC_P;
  flg = v10->flg;
  if ((flg & 0x2000) != 0)
    goto LABEL_24;
LABEL_56:
  if ((flg & 0x4000) == 0)
    goto LABEL_68;
  v7->n0 = v10->n0;
  Damage_I_REC_P = sBtlGetDamage_I_REC_K(unit, v7, v12, 1);
  sBtlGetUnitHelperPos(wklock, 0);
  if (sdfModelGetMarkPos(wklock->hEveUnit->Model->modelRoot, 1))
  {
    goto LABEL_66;
  }
  else
  {
    sdfModelGetMarkPos(wklock->hEveUnit->Model->modelRoot, 0);
LABEL_66:
    goto LABEL_67;
  }
LABEL_67:
LABEL_68:
  if ((v10->flg & 0x8000) == 0)
    goto LABEL_90;
  v7->n1 = v10->n1;
  Damage_I_REC_P = sBtlGetDamage_I_REC_P(unit, v7, v12, 1);
  sBtlGetUnitHelperPos(wklock, 0);
  if (sdfModelGetMarkPos(wklock->hEveUnit->Model->modelRoot, 1))
  {
    goto LABEL_78;
  }
  else
  {
    sdfModelGetMarkPos(wklock->hEveUnit->Model->modelRoot, 0);
LABEL_78:
    goto LABEL_79;
  }
LABEL_79:
LABEL_90:
  if ((v10->flg & 0x10000) != 0)
  {
    badst = v10->badst;
    badstatus = unit->badstatus;
    if ((badstatus & badst) == 0)
    {
      Damage_I_REC_P = 0;
      v33 = v10->flg;
      if (v10->attrtime < 1)
        goto LABEL_104;
      goto LABEL_96;
    }
    Damage_I_REC_P = 0;
    unit->badst_cnt = 0;
    unit->badstatus = badstatus & ~badst;
  }
  v33 = v10->flg;
  if (v10->attrtime < 1)
    goto LABEL_104;
LABEL_96:
  if ((v33 & 0x1E0000) != 0)
  {
    pitem = unit->pitem;
    *(u64 *)&pitem->hp = 0;
    *(u64 *)&pitem->mp = 0;
    str_low = LOBYTE(pitem->str);
    v36 = pitem;
    v36 = unit->pitem;
    vit_low = LOBYTE(v36->vit);
    pitem->str = str_low;
    v36->vit = vit_low;
    v36->tec = LOBYTE(v36->tec);
    v36->luck = LOBYTE(v36->luck);
    unit->itemstatus &= 0x3FFFFCF0u;
    *(u32 *)&unit->itemst_cnt = 0;
    v33 = v10->flg;
  }
LABEL_104:
  if ((v33 & 0x20000) != 0)
  {
    sBtlGetDamage_P_STR(unit, v11, v10, itemid);
    v33 = v10->flg;
    Damage_I_REC_P = 0;
    if ((v33 & 0x40000) == 0)
    {
LABEL_106:
      if ((v33 & 0x80000) == 0)
        goto LABEL_107;
      goto LABEL_117;
    }
  }
  else if ((v33 & 0x40000) == 0)
  {
    goto LABEL_106;
  }
  sBtlGetDamage_P_VIT(unit, v11, v10, itemid);
  v33 = v10->flg;
  Damage_I_REC_P = 0;
  if ((v33 & 0x80000) == 0)
  {
LABEL_107:
    if ((v33 & 0x100000) == 0)
      goto LABEL_108;
    goto LABEL_120;
  }
LABEL_117:
  sBtlGetDamage_P_TEC(unit, v11, v10, itemid);
  v33 = v10->flg;
  Damage_I_REC_P = 0;
  if ((v33 & 0x100000) == 0)
  {
LABEL_108:
    if ((v33 & 0x40) == 0)
      goto LABEL_109;
    goto LABEL_123;
  }
LABEL_120:
  sBtlGetDamage_P_LUCK(unit, v11, v10, itemid);
  v33 = v10->flg;
  Damage_I_REC_P = 0;
  if ((v33 & 0x40) == 0)
  {
LABEL_109:
    if ((v33 & 0x80) == 0)
      return Damage_I_REC_P;
    goto LABEL_126;
  }
LABEL_123:
  Damage_I_REC_P = sBtlGetDamage_CHUUSEI(unit, v11, v10);
  if ((v10->flg & 0x80) != 0)
  {
LABEL_126:
    sBtlGetDamage_ITEMFLG(unit, v11, v10, itemid);
    return 0;
  }
  return Damage_I_REC_P;
}

// 0x1eda6b0
bool sBtlCheckBadStatus_WeakNumber(SBTLUNIT_WORK *wk, BST bstno) {
  SBTLAISYO_DATAWORK *aisyo;
  void *v6;
  sdatUnitWork_t *para;
  s64 v8;
  u32 BadStatus;
  bool result;
  s32 v12;

  aisyo = wk->para->aisyo;
  v6 = NewSpecific(s32, 0x15u);
  InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__515F9C7D26FB948050975ABBBF53EA89B3FBD3E402B5A7B2AEC7081E44591542, 0);
  para = wk->para;
  v8 = *((s32 *)&v6[2].klass + bstno);
  BadStatus = sBtlGetBadStatus(para);
  if (!para)
  {
    if (BadStatus == 5)
      return 0;
    goto LABEL_12;
  }
  result = 0;
  if ((para->koufunst & 0x20) == 0 && BadStatus != 5)
  {
LABEL_12:
    if (BadStatus - 13 >= 0xFFFFFFF9)
    {
      v12 = aisyo->para[v8];
      if ((v12 & 0x23000) == 0 && (bstno < 5 || bstno == 13) && (v12 & 0x4000) != 0)
        return 1;
    }
    return 0;
  }
  return result;
}

// 0x1eda8b0
bool sBtlSetAutoSkill_GBID(sdatUnitWork_t *unit, AUTO autono, SKLID sklId) {
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  f32 *v9;
  f32 *v10;
  s32 str;
  s32 v12;
  s32 tec;
  s32 v14;
  s32 vit;
  sdatParaWork_t *pitem;
  s32 v17;
  s32 luck;
  sdatParaWork_t *v19;
  s32 v20;
  float32x4_t v21;
  float32x4_t v22;
  f32 v23;
  s32 v24;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v26;
  SBTLAUTO_TBL *autotbldata_local;
  f32 v29;
  s32 v30;
  sdatParaWork_t *pbtl;
  int16x4_t *m_paraBns;
  int16x4_t v33;
  int16x4_t v34;
  u32 v35;
  s32 maxmp;
  f32 v38;

  if (autono <= 12)
  {
    if (autono == 11)
    {
      v29 = (f32)((f32)unit->autost_cnt2 / 100.0) * (f32)unit->backup->maxhp;
      v30 = v29;
      if (v29 == INFINITY)
        v30 = 0x80000000;
      unit->pbtl->maxhp += v30;
    }
    else if (autono == 12)
    {
      v23 = (f32)((f32)unit->autost_cnt2 / 100.0) * (f32)unit->backup->maxmp;
      v24 = v23;
      if (v23 == INFINITY)
        v24 = 0x80000000;
      unit->pbtl->maxmp += v24;
    }
  }
  else if (autono == 27)
  {
    Skilltbl = sBtlGetSkilltbl(sklId);
    if (!Skilltbl)
      return (char)Skilltbl;
    v26 = Skilltbl;
    if (Skilltbl->weapontype < 0)
    {
      LOBYTE(Skilltbl) = 0;
      return (char)Skilltbl;
    }
    if ((Skilltbl->flg2 & 0x8000000) != 0)
    {
      autotbldata_local = autotbldata;
    }
    else
    {
      autotbldata_local = ((char *)autotbldata + 8 * v26->weapontype);
    }
    pbtl = unit->pbtl;
    m_paraBns = autotbldata_local[0]->m_paraBns;
    v33.n64_u64[0] = *(u64 *)&pbtl->str;
    v34.n64_u64[0] = m_paraBns[4].n64_u64[0];
    v35 = m_paraBns[3].n64_u32[1];
    pbtl->maxhp += m_paraBns[2].n64_i32[1];
    maxmp = pbtl->maxmp;
    *(int16x4_t *)&pbtl->str = vadd_s16(v34, v33);
    pbtl->maxmp = v35 + maxmp;
  }
  else if (autono == 53)
  {
    devilid = unit->devilid;
    DevilData = sBtlGetDevilData(devilid, -1);
    v9 = NewSpecific(f32, 4u);
    if (DevilData)
    {
      v10 = v9;
      str = DevilData->str;
      v38 = (f32)(unit->autost_cnt2 - 100) / 100.0;
      v12 = GETITEMPARA_LOW(unit->pitem->str) + str;
      tec = DevilData->tec;
      v10[8] = (f32)v12;
      v14 = GETITEMPARA_LOW(unit->pitem->tec);
      vit = DevilData->vit;
      pitem = unit->pitem;
      v10[9] = (f32)(v14 + tec);
      v17 = GETITEMPARA_LOW(pitem->vit);
      luck = DevilData->luck;
      v19 = unit->pitem;
      v10[10] = (f32)(v17 + vit);
      v20 = GETITEMPARA_LOW(v19->luck);
      v21.n128_f32[0] = v10[8];
      v21.n128_f32[1] = v10[10];
      v10[11] = (f32)(v20 + luck);
      v21.n128_f32[2] = v10[9];
      v21.n128_f32[3] = (f32)(v20 + luck);
      v22 = vmulq_n_f32(v21, v38);
      *(int16x4_t *)&unit->pbtl->str = vadd_s16(*(int16x4_t *)&unit->pbtl->str, vbic_s8(vmovn_s32(vcvtq_s32_f32(v22)), vmovn_s32(vceqq_f32(v22, vdupq_n_s32(0x7F800000u)))));
    }
  }
  LOBYTE(Skilltbl) = 1;
  return (char)Skilltbl;
}

// 0x1edac40
s32 sBtlGetDamage_ATK(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  s32 v5;
  u32 attr;
  f32 v7;
  f32 v8;
  s64 v9;
  u32 v10;
  f32 v11;

  v5 = wk->tdef + wk->tlevel;
  attr = ptbl->attr;
  v7 = (f32)((f32)((f32)((f32)wk->sword_power * 0.333333) + (f32)((f32)((f32)((f32)wk->sword_power * 0.5) * (f32)(wk->aatk + wk->alevel)) * 0.033333)) * (f32)wk->n0)
     * 0.01;
  if ((f32)((f32)((f32)(100.0 - (f32)((f32)v5 * 0.5)) * v7) * 0.01) == 0.0)
    v8 = 1.0;
  else
    v8 = (f32)((f32)(100.0 - (f32)((f32)v5 * 0.5)) * v7) * 0.01;
  if ((attr & 1) != 0)
  {
    v9 = 0;
    goto LABEL_40;
  }
  if ((attr & 2) != 0)
  {
    v9 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v9 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v9 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v9 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v9 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v9 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v9 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v9 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v9 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v9 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v9 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v9 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v9 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v9 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_43;
    v9 = 15;
  }
LABEL_40:
  v10 = wk->aisyo_tbl->para[v9] & 0xFFF;
  v11 = (f32)v10 / 100.0;
  if (((v10 < 0x64) & BYTE2(ptbl->flg)) != 0)
    v11 = 1.0;
  v8 = v8 * v11;
LABEL_43:
  if (v8 == INFINITY)
    return 0x80000000;
  else
    return (s32)v8;
}

// 0x1edaf30
s32 sBtlGetDamage_C_ATK1(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  u32 attr;
  f32 v6;
  f32 v7;
  s64 v8;
  f32 v9;

  attr = ptbl->attr;
  v6 = (f32)(100.0 - (f32)((f32)(wk->tdef + wk->tlevel) * 0.5))
     * (f32)((f32)((f32)((f32)((f32)wk->sword_power * 0.333333) + (f32)((f32)((f32)((f32)wk->sword_power * 0.5) * (f32)(wk->aatk + wk->alevel)) * 0.033333)) * (f32)wk->n0) * 0.01);
  v7 = v6 * 0.01;
  if ((attr & 1) != 0)
  {
    v8 = 0;
    goto LABEL_37;
  }
  if ((attr & 2) != 0)
  {
    v8 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v8 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v8 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v8 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v8 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v8 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v8 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v8 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v8 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v8 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v8 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v8 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v8 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v8 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_38;
    v8 = 15;
  }
LABEL_37:
  v7 = v7 * (f32)((f32)(wk->aisyo_tbl->para[v8] & 0xFFF) / 100.0);
LABEL_38:
  v9 = fmaxf(v7, 1.0);
  if (v9 == INFINITY)
    return 0x80000000;
  else
    return (s32)v9;
}

// 0x1edb140
s32 sBtlGetDamage_C_GUN(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  f32 damage_per;
  u32 attr;
  f32 v7;
  f32 v8;
  s64 v9;

  damage_per = wk->damage_per;
  attr = ptbl->attr;
  v7 = (f32)((wk->gun_power + wk->alevel + wk->aatk) * wk->n0)
     / (f32)((f32)((f32)((f32)wk->tlevel / 10.0) + 16.5) + (f32)((f32)wk->tdef / 10.0));
  v8 = v7 / damage_per;
  if ((attr & 1) != 0)
  {
    v9 = 0;
    goto LABEL_37;
  }
  if ((attr & 2) != 0)
  {
    v9 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v9 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v9 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v9 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v9 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v9 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v9 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v9 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v9 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v9 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v9 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v9 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v9 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v9 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_38;
    v9 = 15;
  }
LABEL_37:
  v8 = v8 * (f32)((f32)(wk->aisyo_tbl->para[v9] & 0xFFF) / 100.0);
LABEL_38:
  if (v8 == INFINITY)
    return 0x80000000;
  else
    return (s32)v8;
}

// 0x1edb310
s32 sBtlGetDamage_GUN(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  f32 damage_per;
  u32 attr;
  f32 v7;
  f32 v8;
  s64 v9;

  damage_per = wk->damage_per;
  attr = ptbl->attr;
  v7 = (f32)((wk->gun_power + wk->alevel) * wk->n0)
     / (f32)((f32)((f32)((f32)wk->tlevel / 10.0) + 16.5) + (f32)((f32)wk->tdef / 10.0));
  v8 = v7 / damage_per;
  if ((attr & 1) != 0)
  {
    v9 = 0;
    goto LABEL_37;
  }
  if ((attr & 2) != 0)
  {
    v9 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v9 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v9 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v9 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v9 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v9 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v9 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v9 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v9 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v9 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v9 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v9 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v9 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v9 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_38;
    v9 = 15;
  }
LABEL_37:
  v8 = v8 * (f32)((f32)(wk->aisyo_tbl->para[v9] & 0xFFF) / 100.0);
LABEL_38:
  if (v8 == INFINITY)
    return 0x80000000;
  else
    return (s32)v8;
}

// 0x1edb4d0
s32 sBtlGetDamage_C_MAGIC(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  f32 damage_per;
  u32 attr;
  f32 v7;
  f32 v8;
  s64 v9;
  u32 v10;
  f32 v11;

  damage_per = wk->damage_per;
  attr = ptbl->attr;
  v7 = (f32)((f32)((f32)(wk->atec + wk->alevel) + 20.0) * (f32)wk->n0)
     / (f32)(wk->ttec + 15);
  v8 = damage_per * v7;
  if ((attr & 1) != 0)
  {
    v9 = 0;
    goto LABEL_37;
  }
  if ((attr & 2) != 0)
  {
    v9 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v9 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v9 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v9 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v9 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v9 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v9 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v9 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v9 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v9 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v9 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v9 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v9 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v9 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_40;
    v9 = 15;
  }
LABEL_37:
  v10 = wk->aisyo_tbl->para[v9] & 0xFFF;
  v11 = (f32)v10 / 100.0;
  if (((v10 < 0x64) & BYTE2(ptbl->flg)) != 0)
    v11 = 1.0;
  v8 = v8 * v11;
LABEL_40:
  if (v8 == INFINITY)
    return 0x80000000;
  else
    return (s32)v8;
}

// 0x1edb6a0
s32 sBtlGetDamage_MAGIC(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  f32 damage_per;
  u32 attr;
  f32 v7;
  f32 v8;
  s64 v9;

  damage_per = wk->damage_per;
  attr = ptbl->attr;
  v7 = (f32)((f32)((f32)(3 * wk->atec + wk->alevel) + 20.0) * (f32)wk->n0)
     / (f32)(wk->ttec + 15);
  v8 = damage_per * v7;
  if ((attr & 1) != 0)
  {
    v9 = 0;
    goto LABEL_37;
  }
  if ((attr & 2) != 0)
  {
    v9 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v9 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v9 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v9 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v9 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v9 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v9 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v9 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v9 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v9 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v9 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v9 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v9 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v9 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_38;
    v9 = 15;
  }
LABEL_37:
  v8 = v8 * (f32)((f32)(wk->aisyo_tbl->para[v9] & 0xFFF) / 100.0);
LABEL_38:
  if (v8 == INFINITY)
    return 0x80000000;
  else
    return (s32)v8;
}

// 0x1edb850
s32 sBtlGetDamage_NHP(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  f32 hp;
  f32 n1;
  u32 attr;
  f32 v10;
  f32 v11;
  s64 v12;

  hp = unit->now->hp;
  n1 = ptbl->n1;
  attr = ptbl->attr;
  v10 = n1 / 100.0;
  v11 = v10 * hp;
  if ((attr & 1) != 0)
  {
    v12 = 0;
    goto LABEL_37;
  }
  if ((attr & 2) != 0)
  {
    v12 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v12 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v12 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v12 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v12 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v12 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v12 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v12 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v12 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v12 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v12 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v12 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v12 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v12 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_38;
    v12 = 15;
  }
LABEL_37:
  v11 = v11 * (f32)((f32)(wk->aisyo_tbl->para[v12] & 0xFFF) / 100.0);
LABEL_38:
  if (v11 == INFINITY)
    return 0x80000000;
  else
    return (s32)v11;
}

// 0x1edb9f0
s32 sBtlGetDamage_REC_P(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s8 flg) {
  s32 badstatus;
  f32 v7;
  s32 *p_maxmp;

  badstatus = unit->badstatus;
  if ((badstatus & 0x100000) != 0 || (badstatus & 0x10000) != 0 && unit->devilid)
    return 0;
  if (flg == 1)
  {
    p_maxmp = &unit->now->maxmp;
  }
  else
  {
    v7 = 0.0;
    if (flg)
      goto LABEL_10;
    p_maxmp = &unit->now->maxhp;
  }
  v7 = (f32)(wk->n1 / 100.0) * (f32)*p_maxmp;
LABEL_10:
  if (v7 == INFINITY)
    return 0x80000000;
  else
    return (s32)v7;
}

// 0x1edba70
s32 sBtlGetDamage_ATK_MG(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  f32 damage_per;
  u32 attr;
  f32 v7;
  f32 v8;
  f32 v9;
  s64 v10;

  damage_per = wk->damage_per;
  attr = ptbl->attr;
  v7 = (f32)((f32)((f32)wk->alevel + (f32)wk->alevel) + (f32)((f32)((f32)wk->aatk + (f32)wk->aatk) * (f32)wk->n0))
     / (f32)((f32)((f32)(s32)(((26215 * wk->tlevel) >> 18) + ((u32)(26215 * wk->tlevel) >> 31)) + 16.5) + (f32)(wk->tdef / 10));
  v8 = v7 + (f32)((f32)(wk->ahp * (f32)(v7 * 0.25)) / wk->amaxhp);
  v9 = damage_per * v8;
  if ((attr & 1) != 0)
  {
    v10 = 0;
    goto LABEL_37;
  }
  if ((attr & 2) != 0)
  {
    v10 = 1;
  }
  else if ((attr & 4) != 0)
  {
    v10 = 2;
  }
  else if ((attr & 8) != 0)
  {
    v10 = 3;
  }
  else if ((attr & 0x10) != 0)
  {
    v10 = 4;
  }
  else if ((attr & 0x20) != 0)
  {
    v10 = 5;
  }
  else if ((attr & 0x40) != 0)
  {
    v10 = 6;
  }
  else if ((attr & 0x80) != 0)
  {
    v10 = 7;
  }
  else if ((attr & 0x100) != 0)
  {
    v10 = 8;
  }
  else if ((attr & 0x200) != 0)
  {
    v10 = 9;
  }
  else if ((attr & 0x400) != 0)
  {
    v10 = 10;
  }
  else if ((attr & 0x800) != 0)
  {
    v10 = 11;
  }
  else if ((attr & 0x1000) != 0)
  {
    v10 = 12;
  }
  else if ((attr & 0x2000) != 0)
  {
    v10 = 13;
  }
  else if ((attr & 0x4000) != 0)
  {
    v10 = 14;
  }
  else
  {
    if ((attr & 0x8000) == 0)
      goto LABEL_38;
    v10 = 15;
  }
LABEL_37:
  v9 = v9 * (f32)((f32)(wk->aisyo_tbl->para[v10] & 0xFFF) / 100.0);
LABEL_38:
  if (v9 == INFINITY)
    return 0x80000000;
  else
    return (s32)v9;
}

// 0x1edbc80
s32 sBtlGetDamage_Slip(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID skillid, s32 damage, SBTLUNIT_SIDE side) {
  s32 v11;
  f32 n1;
  f32 v13;
  s32 v14;
  SBTLEFF_LISTWORK *effList;

  if ((wk->status & 0x100) == 0)
  {
    v11 = sub_1905740(4, 0);
    wk->slip_sklid = skillid;
    *(u64 *)&wk->slipcnt = 0x3C00000000LL;
    wk->side_given_slip = side;
    n1 = ptbl->n1;
    wk->slipcounter = 60 * v11 + 122;
    v13 = (f32)(n1 / 100.0) * (f32)damage;
    if (v13 == INFINITY)
      v14 = 0x80000000;
    else
      v14 = v13;
    wk->slippara = v14;
    if (v14 <= 1)
      wk->slippara = 1;
    if ((wk->status & 0x1000) == 0)
    {
      effList = wk->effList;
      sBtlForceDelete_ID_Acter(effList, wk, 55);
      sBtlCreateEff(wk->effList, wk, 55, 0, wk->pos, 0x80808080, 0, 1.0, skillid);
    }
  }
  return damage;
}

// 0x1edbe10
s32 sBtlGetDamage_Barrier(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID sklid) {
  return 0;
}

// 0x1edbe20
s32 sBtlGetDamage_The_W(SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID) {
  sBtlSetDyingDamage(wk, sklid, 0, 0, acterID);
  return 0;
}

// 0x1edbeb0
s32 sBtlGetDamage_Tadan(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID skillid, s32 damage, s32 actID) {
  s32 tdan_sklid;
  s32 para2;
  s32 count;
  s64 n1_low;
  f32 v11;
  s32 v12;

  if ((wk->status & 0x100) != 0 && (ptbl->flg2 & 0x20000) == 0)
    return damage;
  tdan_sklid = wk->tdan_sklid;
  if (skillid == 168 || tdan_sklid != 168)
  {
    if (!tdan_sklid)
      goto LABEL_8;
    return damage;
  }
  wk->tdanpara = 0;
  *(_OWORD *)&wk->tdancounter = 0u;
LABEL_8:
  para2 = ptbl->para2;
  wk->tdan_sklid = skillid;
  count = ptbl->count;
  wk->tdan_acterid = actID;
  *(u64 *)&wk->tdancnt = 0;
  n1_low = LODWORD(ptbl->n1);
  wk->tdancounter = para2;
  wk->tdancmpcnt = para2 / count;
  v11 = (f32)(*(f32 *)&n1_low / 100.0) * (f32)damage;
  v12 = v11;
  if ((s32)v11 <= 1)
    v12 = 1;
  if (v11 == INFINITY)
    v12 = 1;
  wk->tdanpara = v12;
  return damage;
}

// 0x1edbf60
static s32 GetDamage_Rejyene(SBTLUNIT_WORK *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, bool calc_only) {
  s32 attrtime;
  sdatUnitWork_t *para;
  s32 v11;
  sdatUnitWork_t *v12;
  s32 count;
  s32 v14;
  sdatParaWork_t *now;
  f32 n1;
  f32 v17;
  s32 v18;
  s32 HaveMemSkl;

  if (calc_only)
    return 0;
  attrtime = ptbl->attrtime;
  para = unit->para;
  HaveMemSkl = sBtlChkHaveMemSkl(para, 43);
  v12 = unit->para;
  if (!HaveMemSkl)
    goto LABEL_8;
  goto LABEL_7;
  if (v11)
LABEL_7:
    attrtime += v12->autost_cnt;
LABEL_8:
  count = ptbl->count;
  unit->rejyenecnt = 0;
  if (attrtime <= 1)
    v14 = 1;
  else
    v14 = attrtime;
  now = v12->now;
  unit->rejyenecounter = v14;
  n1 = ptbl->n1;
  unit->rejyenecmpcnt = v14 / count;
  v17 = (f32)(n1 * (f32)now->maxhp) / 100.0;
  v18 = v17;
  if ((s32)v17 <= 1)
    v18 = 1;
  if (v17 == INFINITY)
    v18 = 1;
  unit->rejyenepara = v18;
  return 0;
}

// 0x1edc090
s32 sBtlGetDamage_ParaUP(SBTLUNIT_WORK *unit, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v7;
  s32 devilid;
  u32 flg;
  s32 attrtime;
  sdatParaWork_t *pbtl;
  u32 v12;
  SBTLSKL_KAJA_WORK *v15;
  SBTLSKL_KAJA_WORK *v17;
  SBTLSKL_KAJA_WORK *v18;
  f32 v19;
  f32 v20;
  bool v21;
  f32 v22;
  s32 side;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v26;
  SBTLSKL_KAJA_WORK *v28;
  SBTLSKL_KAJA_WORK *v30;
  SBTLSKL_KAJA_WORK *v31;
  f32 n1;
  f32 m_fPara;
  bool v34;
  f32 v35;
  s32 v36;
  SBTLSM_LISTWORK *v38;
  s32 v39;
  SBTLSKL_KAJA_WORK *v41;
  SBTLSKL_KAJA_WORK *v43;
  s32 v44;
  SBTLSM_LISTWORK *v46;
  s32 v47;
  SBTLSKL_KAJA_WORK *v48;
  f32 v49;
  f32 v50;
  bool v51;
  f32 v52;
  SBTLSKL_KAJA_WORK *v53;
  SBTLSKL_KAJA_WORK *v54;
  f32 str;
  f32 v57;
  s32 v58;
  f32 vit;
  f32 v60;
  s32 v61;
  f32 tec;
  f32 v63;
  s32 v64;
  f32 luck;
  f32 v66;
  s32 v67;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if (Skilltbl)
  {
    v7 = Skilltbl;
    if (skillid != 128 || (devilid = (u16)unit->para->devilid, devilid != 262) && devilid != 300)
    {
      flg = Skilltbl->flg;
      if ((flg & 0x400000) == 0)
      {
        if ((flg & 0x7000000) == 0)
        {
          attrtime = Skilltbl->attrtime;
          pbtl = unit->para->pbtl;
          if (attrtime >= 1)
            unit->paraupcnt = attrtime;
          v12 = Skilltbl->flg;
          if ((v12 & 0x20000) == 0)
          {
LABEL_12:
            if ((v12 & 0x40000) == 0)
              goto LABEL_13;
            goto LABEL_109;
          }
LABEL_106:
          str = unit->para->backup->str;
          v57 = (f32)(v7->n1 * str) - str;
          v58 = v57;
          if (v57 == INFINITY)
            LOWORD(v58) = 0;
          pbtl->str = v58;
          if ((v12 & 0x40000) == 0)
          {
LABEL_13:
            if ((v12 & 0x80000) == 0)
              goto LABEL_14;
            goto LABEL_112;
          }
LABEL_109:
          vit = unit->para->backup->vit;
          v60 = (f32)(v7->n1 * vit) - vit;
          v61 = v60;
          if (v60 == INFINITY)
            LOWORD(v61) = 0;
          pbtl->vit = v61;
          if ((v12 & 0x80000) == 0)
          {
LABEL_14:
            if ((v12 & 0x100000) == 0)
              goto LABEL_15;
            goto LABEL_115;
          }
LABEL_112:
          tec = unit->para->backup->tec;
          v63 = (f32)(v7->n1 * tec) - tec;
          v64 = v63;
          if (v63 == INFINITY)
            LOWORD(v64) = 0;
          pbtl->tec = v64;
          if ((v12 & 0x100000) == 0)
          {
LABEL_15:
LABEL_16:
            sBtlCheckBattlePara(unit);
            return 0;
          }
LABEL_115:
          luck = unit->para->backup->luck;
          v66 = (f32)(v7->n1 * luck) - luck;
          v67 = v66;
          if (v66 == INFINITY)
            LOWORD(v67) = 0;
          pbtl->luck = v67;
          goto LABEL_16;
        }
LABEL_105:
        pbtl = 0;
        v12 = v7->flg;
        if ((v12 & 0x20000) == 0)
          goto LABEL_12;
        goto LABEL_106;
      }
      if ((flg & 0x1000000) == 0)
        goto LABEL_47;
      v15 = unit->wkKaja[0];
      v17 = v15[0];
      if (!v17->m_cnt)
        goto LABEL_34;
      goto LABEL_27;
      if (!v17->m_cnt)
      {
LABEL_34:
        v17->m_fPara = v7->n1;
        v17->m_cnt = v7->attrtime;
        side = unit->side;
        if ((side & 1) != 0)
        {
          sysmsgList = wk->sysmsgList;
          v26 = 36;
        }
        else
        {
          if ((side & 2) == 0)
            goto LABEL_47;
          sysmsgList = wk->sysmsgList;
          v26 = 37;
        }
        sBtlCreateSM(sysmsgList, unit, v26, 0, 0, 120);
LABEL_47:
        if ((v7->flg & 0x2000000) == 0)
          goto LABEL_76;
        v28 = unit->wkKaja[1];
        v30 = v28[0];
        if (v30->m_cnt)
        {
          v31 = v28[1];
          if (v31->m_cnt)
          {
            n1 = v7->n1;
            m_fPara = v30->m_fPara;
            v34 = m_fPara < n1;
            if (m_fPara < n1)
              n1 = v30->m_fPara;
            v35 = v31->m_fPara;
            if (!v34 && v35 >= n1)
              goto LABEL_76;
            v30 = v28[v35 < n1];
          }
          else
          {
            v30 = v28[1];
          }
        }
        v30->m_fPara = v7->n1;
        v30->m_cnt = v7->attrtime;
        v36 = unit->side;
        if ((v36 & 1) != 0)
        {
          v38 = wk->sysmsgList;
          v39 = 38;
        }
        else
        {
          if ((v36 & 2) == 0)
            goto LABEL_76;
          v38 = wk->sysmsgList;
          v39 = 39;
        }
        sBtlCreateSM(v38, unit, v39, 0, 0, 120);
LABEL_76:
        if ((v7->flg & 0x4000000) == 0)
          goto LABEL_105;
        v41 = unit->wkKaja[2];
        v43 = v41[0];
        if (!v43->m_cnt)
        {
          v43->m_fPara = v7->n1;
          v43->m_cnt = v7->attrtime;
          v44 = unit->side;
          if ((v44 & 1) == 0)
          {
LABEL_82:
            if ((v44 & 2) == 0)
              goto LABEL_105;
            v46 = wk->sysmsgList;
            v47 = 41;
            goto LABEL_104;
          }
LABEL_99:
          v46 = wk->sysmsgList;
          v47 = 40;
LABEL_104:
          sBtlCreateSM(v46, unit, v47, 0, 0, 120);
          goto LABEL_105;
        }
        v48 = v41[1];
        if (v48->m_cnt)
        {
          v49 = v7->n1;
          v50 = v43->m_fPara;
          v51 = v50 < v49;
          if (v50 < v49)
            v49 = v43->m_fPara;
          v52 = v48->m_fPara;
          if (!v51 && v52 >= v49)
            goto LABEL_105;
          v53 = v41[v52 < v49];
          v53->m_fPara = v7->n1;
          v53->m_cnt = v7->attrtime;
          v44 = unit->side;
          if ((v44 & 1) == 0)
            goto LABEL_82;
        }
        else
        {
          v54 = v41[1];
          v48->m_fPara = v7->n1;
          v54->m_cnt = v7->attrtime;
          v44 = unit->side;
          if ((v44 & 1) == 0)
            goto LABEL_82;
        }
        goto LABEL_99;
      }
LABEL_27:
      v18 = v15[1];
      if (v18->m_cnt)
      {
        v19 = v7->n1;
        v20 = v17->m_fPara;
        v21 = v20 < v19;
        if (v20 < v19)
          v19 = v17->m_fPara;
        v22 = v18->m_fPara;
        if (!v21 && v22 >= v19)
          goto LABEL_47;
        v17 = v15[v22 < v19];
      }
      else
      {
        v17 = v15[1];
      }
      goto LABEL_34;
    }
  }
  return 0;
}

// 0x1ed7570
s32 sBtlGetDamage_I_REC_K(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s8 flg) {
  s32 badstatus;
  u32 n0;
  sdatParaWork_t *now;
  s64 v12;
  s32 hp;
  s32 v14;
  u32 v15;
  SKLID *spiritSkill;
  s32 v19;
  s64 i;
  SKLID *v23;
  s32 v25;
  sdatParaWork_t *v27;
  s32 *p_hp;
  s32 v29;
  s32 v30;
  SBATTLE_WORK *v34;
  s32 mag;
  s32 magMax;
  SBATTLE_WORK *v37;
  SBATTLE_WORK *v38;
  s32 *p_mag;
  s32 v41;
  sdatPlayerUnitWork_t *player;
  s32 v44;
  s32 maxmag;
  sdatPlayerUnitWork_t *v46;
  struct dat *static_fields;
  sdatPlayerUnitWork_t *v48;
  s16 para2[2];
  s16 para1[2];

  badstatus = unit->badstatus;
  n0 = 0;
  para1[0] = 0;
  para2[0] = 0;
  if ((badstatus & 0x100000) != 0)
    return n0;
  if ((badstatus & 0x10000) != 0 && unit->devilid)
    return 0;
  n0 = (u16)wk->n0;
  if ((wk->status3 & 0x8000000) != 0)
    n0 = (s16)(n0 + (n0 >> 15)) >> 1;
  n0 = (s16)n0;
  if (flg != 1)
  {
    if (flg)
      return n0;
    now = unit->now;
    v12 = 0;
    hp = now->hp;
    LODWORD(now) = now->maxhp;
    v14 = hp + (s16)n0;
    v15 = (u32)now - hp;
    if (v14 > (s32)now)
      n0 = v15;
    while (1)
    {
      spiritSkill = GBWK->player->spiritSkill;
      if (v12 >= SLODWORD(spiritSkill->max_length))
      {
        v27 = unit->now;
        v29 = v27->hp;
        p_hp = &v27->hp;
        *p_hp = v29 + n0;
        v30 = p_hp[1];
        goto LABEL_44;
      }
      v19 = spiritSkill[v12];
      if (sBtlGetAutoSkillPara(v19, para1, para2) == 68)
        n0 = (s32)(n0 * para2[0]) / 100;
      ++v12;
    }
  }
  if (unit->devilid)
    return n0;
  for (i = 0; ; ++i)
  {
    v23 = GBWK->player->spiritSkill;
    if (i >= SLODWORD(v23->max_length))
      break;
    v25 = v23[i];
    if (sBtlGetAutoSkillPara(v25, para1, para2) != 68)
      continue;
    n0 = (s32)(n0 * para2[0]) / 100;
  }
  v34 = wk;
  mag = v34->mag;
  magMax = v34->magMax;
  if ((s32)(mag + n0) > magMax)
  {
    v37 = wk;
    mag = v37->mag;
    magMax = v37->magMax;
    n0 = magMax - mag;
  }
  v38 = wk;
  p_mag = &v38->mag;
  v41 = v38->magMax;
  v38->mag += n0;
  LimitRange(p_mag, 0, v41);
  player = GBWK->player;
  v44 = player->mag;
  maxmag = player->maxmag;
  if ((s32)(v44 + n0) > maxmag)
  {
    v46 = GBWK->player;
    v44 = v46->mag;
    maxmag = v46->maxmag;
    n0 = maxmag - v44;
  }
  v48 = GBWK->player;
  LODWORD(static_fields) = v48->mag;
  v30 = v48->maxmag;
  p_hp = &v48->mag;
  *p_hp = (u32)static_fields + n0;
LABEL_44:
  LimitRange(p_hp, 0, v30);
  return n0;
}

// 0x1ed7a00
s32 sBtlGetDamage_I_REC_P(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s8 flg) {
  s32 badstatus;
  s32 v9;
  s64 v10;
  f32 v11;
  SKLID *spiritSkill;
  s32 v15;
  sdatParaWork_t *now;
  s32 v18;
  s32 hp;
  s32 maxhp;
  f32 v22;
  f32 v23;
  sdatParaWork_t *p_fields;
  s32 *p_hp;
  s32 v27;
  s64 v29;
  f32 v30;
  SKLID *v32;
  s32 v34;
  SBATTLE_WORK *v37;
  f32 magMax;
  f32 v39;
  SBATTLE_WORK *v40;
  SBATTLE_WORK *v41;
  s32 *p_mag;
  s32 v44;
  s64 v47;
  f32 v48;
  sdatPlayerUnitWork_t *player;
  SKLID *v51;
  s32 v53;
  f32 maxmag;
  f32 v56;
  sdatPlayerUnitWork_t *v57;
  s32 v61;
  sdatPlayerUnitWork_t *v62;
  s32 mag;
  s32 *v64;
  s32 v65;
  s16 para2[2];
  s16 para1[2];

  badstatus = unit->badstatus;
  v9 = 0;
  para1[0] = 0;
  para2[0] = 0;
  if ((badstatus & 0x100000) != 0)
    return v9;
  if ((badstatus & 0x10000) != 0 && unit->devilid)
    return 0;
  if (flg != 1)
  {
    if (!flg)
    {
      v10 = 0;
      v11 = (f32)(wk->n1 / 100.0) * (f32)unit->now->maxhp;
      while (1)
      {
        spiritSkill = GBWK->player->spiritSkill;
        if (v10 >= SLODWORD(spiritSkill->max_length))
        {
          now = unit->now;
          if (v11 == INFINITY)
            v18 = 0x80000000;
          else
            v18 = v11;
          hp = now->hp;
          maxhp = now->maxhp;
          if (hp + v18 > maxhp)
            v18 = maxhp - hp;
          v22 = v18;
          now = unit->now;
          hp = now->hp;
          maxhp = now->maxhp;
          v23 = v22 * 0.5;
          if ((wk->status3 & 0x8000000) == 0)
            v23 = v22;
          if (v23 == INFINITY)
            v9 = 0x80000000;
          else
            v9 = (s32)v23;
          now->hp = v9 + hp;
          p_fields = &now->fields;
          p_hp = &p_fields->hp;
          v27 = maxhp;
          goto LABEL_93;
        }
        v15 = spiritSkill[v10];
        if (sBtlGetAutoSkillPara(v15, para1, para2) == 68)
          v11 = (f32)(v11 * (f32)para2[0]) / 100.0;
        ++v10;
      }
    }
    return 0;
  }
  if (unit->devilid)
    return 0;
  v29 = 0;
  v30 = (f32)(wk->n1 / 100.0) * (f32)wk->magMax;
  while (1)
  {
    v32 = GBWK->player->spiritSkill;
    if (v29 >= SLODWORD(v32->max_length))
      break;
    v34 = v32[v29];
    if (sBtlGetAutoSkillPara(v34, para1, para2) == 68)
      v30 = (f32)(v30 * (f32)para2[0]) / 100.0;
    ++v29;
  }
  v37 = wk;
  magMax = v37->magMax;
  v39 = v30 + (f32)v37->mag;
  if (v39 > magMax)
  {
    v40 = wk;
    v39 = v30 + (f32)v40->mag;
    magMax = v40->magMax;
    v30 = v30 - (f32)(v39 - magMax);
  }
  v41 = wk;
  p_mag = &v41->mag;
  v44 = v41->magMax;
  if (v30 == INFINITY)
    v9 = 0x80000000;
  else
    v9 = (s32)v30;
  v41->mag += v9;
  LimitRange(p_mag, 0, v44);
  v47 = 0;
  v48 = (f32)(wk->n1 / 100.0) * (f32)GBWK->player->maxmag;
  while (2)
  {
    player = GBWK->player;
    v51 = player->spiritSkill;
    if (v47 < SLODWORD(v51->max_length))
    {
      v53 = v51[v47];
      if (sBtlGetAutoSkillPara(v53, para1, para2) == 68)
        v48 = (f32)(v48 * (f32)para2[0]) / 100.0;
      ++v47;
      continue;
    }
    break;
  }
  maxmag = player->maxmag;
  v56 = v48 + (f32)player->mag;
  if (v56 > maxmag)
  {
    v57 = GBWK->player;
    maxmag = v57->maxmag;
    v56 = v48 + (f32)v57->mag;
    v48 = v48 - (f32)(v56 - maxmag);
  }
  v61 = v48;
  v62 = GBWK->player;
  mag = v62->mag;
  v65 = v62->maxmag;
  v64 = &v62->mag;
  if (v48 == INFINITY)
    v61 = 0x80000000;
  *v64 = mag + v61;
  p_hp = v64;
  v27 = v65;
LABEL_93:
  LimitRange(p_hp, 0, v27);
  return v9;
}

// 0x1ed9b20
s32 sBtlGetDamage_I_REC_PARA(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  u32 badst;
  s32 badstatus;

  badst = ptbl->badst;
  badstatus = unit->badstatus;
  if ((badstatus & badst) != 0)
  {
    unit->badst_cnt = 0;
    unit->badstatus = badstatus & ~badst;
  }
  return 0;
}

// 0x1edccd0
s32 sBtlGetDamege_I_EXP(sdatUnitWork_t *unit, ITM _itmID) {
  s32 devilid;
  s32 level;
  s32 DevilExp;
  s32 v9;
  f32 v11;
  s32 v12;
  s32 PlayerExp;

  devilid = unit->devilid;
  level = unit->level;
  if (unit->devilid)
  {
    DevilExp = datGetDevilExp(devilid, level);
    v9 = datGetDevilExp(unit->devilid, unit->level + 1) - DevilExp;
  }
  else
  {
    PlayerExp = datGetPlayerExp(level);
    v9 = datGetPlayerExp(unit->level + 1) - PlayerExp;
  }
  v11 = v9;
  if (itmID == 752)
    v11 = (f32)v9 * 0.25;
  v12 = vcvtps_s32_f32(v11);
  if (ceilf(v11) == INFINITY)
    return 0x80000000;
  else
    return v12;
}

// 0x1ed9b50
s32 sBtlGetDamage_P_STR(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid) {
  s16 v5;
  s16 str;
  sdatParaWork_t *pitem;
  s16 v10;
  s16 v12;
  u16 *v13;
  s16 x[2];

  v5 = itemid;
  str = unit->pitem->str;
  if (!ptbl->attrtime)
  {
    x[0] = ptbl->n0 + (u8)str;
    LimitRange_2(x, 0, 40);
    LOBYTE(unit->pitem->str) = x[0];
    return 0;
  }
  x[0] = ptbl->n0 + HIBYTE(unit->pitem->str);
  LimitRange_2(x, 0, 40);
  pitem = unit->pitem;
  v10 = x[0];
  unit->itemst_cnt = ptbl->attrtime;
  v12 = pitem->str + (v10 << 8);
  unit->itemstatus = unit->itemstatus & 0xFFFFFFE | 1;
  pitem->str = v12;
  v13 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  if (evtBitCheck(v13[0]))
    unit->itemstatus |= 0x80000000;
  unit->itemst_cnt2 = v5;
  return 0;
}

// 0x1ed9d30
s32 sBtlGetDamage_P_VIT(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid) {
  s16 v5;
  s16 vit;
  sdatParaWork_t *pitem;
  s16 v10;
  s16 v12;
  u16 *v13;
  s16 x[2];

  v5 = itemid;
  vit = unit->pitem->vit;
  if (!ptbl->attrtime)
  {
    x[0] = ptbl->n0 + (u8)vit;
    LimitRange_2(x, 0, 40);
    LOBYTE(unit->pitem->vit) = x[0];
    return 0;
  }
  x[0] = ptbl->n0 + HIBYTE(unit->pitem->vit);
  LimitRange_2(x, 0, 40);
  pitem = unit->pitem;
  v10 = x[0];
  unit->itemst_cnt = ptbl->attrtime;
  v12 = pitem->vit + (v10 << 8);
  unit->itemstatus = unit->itemstatus & 0xFFFFFFD | 2;
  pitem->vit = v12;
  v13 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  if (evtBitCheck(v13[0]))
    unit->itemstatus |= 0x80000000;
  unit->itemst_cnt2 = v5;
  return 0;
}

// 0x1ed9f10
s32 sBtlGetDamage_P_TEC(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid) {
  s16 v5;
  s16 tec;
  sdatParaWork_t *pitem;
  s16 v10;
  s16 v12;
  u16 *v13;
  s16 x[2];

  v5 = itemid;
  tec = unit->pitem->tec;
  if (!ptbl->attrtime)
  {
    x[0] = ptbl->n0 + (u8)tec;
    LimitRange_2(x, 0, 40);
    LOBYTE(unit->pitem->tec) = x[0];
    return 0;
  }
  x[0] = ptbl->n0 + HIBYTE(unit->pitem->tec);
  LimitRange_2(x, 0, 40);
  pitem = unit->pitem;
  v10 = x[0];
  unit->itemst_cnt = ptbl->attrtime;
  v12 = pitem->tec + (v10 << 8);
  unit->itemstatus = unit->itemstatus & 0xFFFFFFB | 4;
  pitem->tec = v12;
  v13 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  if (evtBitCheck(v13[0]))
    unit->itemstatus |= 0x80000000;
  unit->itemst_cnt2 = v5;
  return 0;
}

// 0x1eda0f0
s32 sBtlGetDamage_P_LUCK(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid) {
  s16 v5;
  s16 luck;
  sdatParaWork_t *pitem;
  s16 v10;
  s16 v12;
  u16 *v13;
  s16 x[2];

  v5 = itemid;
  luck = unit->pitem->luck;
  if (!ptbl->attrtime)
  {
    x[0] = ptbl->n0 + (u8)luck;
    LimitRange_2(x, 0, 40);
    LOBYTE(unit->pitem->luck) = x[0];
    return 0;
  }
  x[0] = ptbl->n0 + HIBYTE(unit->pitem->luck);
  LimitRange_2(x, 0, 40);
  pitem = unit->pitem;
  v10 = x[0];
  unit->itemst_cnt = ptbl->attrtime;
  v12 = pitem->luck + (v10 << 8);
  unit->itemstatus = unit->itemstatus & 0xFFFFFF7 | 8;
  pitem->luck = v12;
  v13 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  if (evtBitCheck(v13[0]))
    unit->itemstatus |= 0x80000000;
  unit->itemst_cnt2 = v5;
  return 0;
}

// 0x1eda2d0
s32 sBtlGetDamage_CHUUSEI(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  u32 attr;
  char max_damage;
  signed s16 Percentage;
  f32 n1;
  s32 v10;
  u16 *v12;
  s32 chuusei;
  s32 v14;
  s32 v15;

  if ((ptbl->flg & 0x80) != 0)
  {
    Percentage = GetPercentage();
    n1 = ptbl->n1;
    v10 = n1;
    if (n1 == INFINITY)
      v10 = 0;
    if (v10 >= Percentage)
    {
      max_damage = ptbl->max_damage;
    }
    else
    {
      max_damage = GetIntervalRand(1, ptbl->n0);
    }
    v12 = NewSpecific(ushort, 9u);
    InitializeArray_55364416(v12, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
    if (evtBitCheck(v12[0]))
      unit->itemstatus |= 0x80000000;
    goto LABEL_31;
  }
  attr = ptbl->attr;
  if (attr && ((attr & 1) == 0 || unit->raceid != 1) && ((attr & 2) == 0 || unit->raceid != 2) && ((attr & 4) == 0 || unit->raceid != 3) && ((attr & 8) == 0 || unit->raceid != 4) && ((attr & 0x10) == 0 || unit->raceid != 5) && ((attr & 0x20) == 0 || unit->raceid != 6) && ((attr & 0x40) == 0 || unit->raceid != 7))
  {
    return -1;
  }
  max_damage = ptbl->n0;
LABEL_31:
  chuusei = unit->chuusei;
  v14 = chuusei + max_damage;
  if (v14 << 16 >= 6553600)
    v15 = 100;
  else
    v15 = (s16)v14 & ~((s16)v14 >> 31);
  unit->chuusei = v15;
  return v15 - chuusei;
}

// 0x1eda4d0
s32 sBtlGetDamage_ITEMFLG(sdatUnitWork_t *unit, SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl, s32 itemid) {
  s16 v5;
  u32 attr;
  sdatParaWork_t *pitem;
  s16 str_low;
  sdatParaWork_t *v11;
  s16 vit_low;
  u32 itemstatus;
  u32 v14;
  s32 attrtime;
  u16 *v18;

  v5 = itemid;
  attr = ptbl->attr;
  if ((attr & 0xC000030F) != 0)
  {
    pitem = unit->pitem;
    *(u64 *)&pitem->hp = 0;
    *(u64 *)&pitem->mp = 0;
    str_low = LOBYTE(pitem->str);
    v11 = pitem;
    v11 = unit->pitem;
    vit_low = LOBYTE(v11->vit);
    pitem->str = str_low;
    v11->vit = vit_low;
    v11->tec = LOBYTE(v11->tec);
    v11->luck = LOBYTE(v11->luck);
    itemstatus = unit->itemstatus;
    *(u32 *)&unit->itemst_cnt = 0;
    v14 = ptbl->attr | itemstatus & 0x3FFFFCF0;
    attrtime = ptbl->attrtime;
    unit->itemstatus = v14;
    if (attrtime < 1)
      return 0;
    goto LABEL_12;
  }
  v14 = attr | unit->itemstatus;
  attrtime = ptbl->attrtime;
  unit->itemstatus = v14;
  if (attrtime < 1)
    return 0;
LABEL_12:
  unit->itemst_cnt = attrtime;
  unit->itemstatus = v14 & 0xFFFFFFF;
  v18 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v18, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  if (evtBitCheck(v18[0]))
    unit->itemstatus |= 0x80000000;
  unit->itemst_cnt2 = v5;
  return 0;
}

// 0x1ed7560
s32 sBtlGetDamage_Escape(sdatUnitWork_t *unit) {
  return 0;
}

// 0x1edce90
bool sBtlResetUnit(SBTLUNIT_WORK *wklock, s32 bstno) {
  SBTLACTAI_WORK *actaiwk;
  s32 ListID;
  s32 v7;

  actaiwk = wklock->actaiwk;
  if (actaiwk->mode == 10)
  {
    actaiwk->status = actaiwk->status & 0xFFFFFF9F | 0x40;
    ListID = wklock->ListID;
    if (ListID == wk->playerID)
      return 1;
  }
  else
  {
    v7 = wklock->ListID;
    if (v7 == wk->playerID)
      return 1;
    if (wk->battlemode != 3)
      goto LABEL_18;
    if ((wklock->side & 1) != 0)
      return 1;
  }
LABEL_18:
  ResetAction(wklock, 0, 0);
  sBtlResetAAI(wklock);
  if ((wklock->side & 1) == 0)
    return 1;
  wklock->aiwk->mode = 0;
  wklock->actcounter = wklock->actcounter_max;
  return 1;
}

// 0x1edd080
bool sBtlCheckJyuso_GB(void) {
  return 0;
}

// 0x1edd090
bool sBtlCheckItemCost_GBWK(s32 itemid, s32 flg) {
  s32 v6;
  s64 v8;
  s64 v9;
  sdatPlayerUnitWork_t *player;
  SortSave *sortSave;
  s64 v13;
  u16 *v14;
  s32 v15;

  v6 = GBWK->player->item[itemid];
  if (!flg || v6 < 1)
    return v6 > 0;
  v8 = itemid;
  v9 = v8;
  player = GBWK->player;
  sortSave = GBWK->sortSave;
  --player->item[v9];
  UpdateGetList(sortSave, itemid, -1, 0);
  v13 = (s64)player->item + v9 * 2;
  v15 = *(s16 *)(v13 + 32);
  v14 = (v13 + 32);
  if (v15 > 0)
    return v6 > 0;
  *v14 = 0;
  return 1;
}

// 0x1edd2d0
bool sBtlCheckItemCost(s32 itemid, s32 flg) {
  s64 v6;
  s64 v7;
  s64 v8;
  SBTLITEM_LISTWORK *itemList;
  s64 v12;

  v6 = 0;
  do
  {
    itemList = wk->itemList;
    if (v6 >= itemList->num)
      return 0;
    itemList = wk->itemList;
    v7 = (s64)itemList->data + 8 * v6++;
    v8 = *(u64 *)(v7 + 32);
  }
  while (*(u32 *)(v8 + 16) != itemid);
  if (*(s32 *)(*(&wk->itemList->data->max_length + v6) + 20) < 1)
    return 0;
  if (flg)
  {
    v12 = *(&wk->itemList->data->max_length + v6);
    --*(u32 *)(v12 + 20);
    return 1;
  }
  return 1;
}

// 0x1edd530
void sBtlSetWeakBit(s32 devilid) {
  s32 v4;
  u32 *anlyzBit;
  u32 v6;
  char v7;
  s64 v8;

  v4 = devilid / 32;
  anlyzBit = GBWK->anlyzBit;
  if (v4 >= SLODWORD(anlyzBit->max_length))
  {
    if (devilid > 126)
      goto LABEL_6;
    goto LABEL_13;
  }
  anlyzBit = GBWK->anlyzBit;
  anlyzBit[v4] |= 1 << devilid;
  if (devilid > 126)
  {
LABEL_6:
    switch (devilid)
    {
      case 214:
        v6 = 136;
        v7 = 8;
        goto LABEL_31;
      case 215:
      case 216:
      case 217:
      case 218:
      case 219:
      case 220:
      case 221:
      case 222:
      case 223:
      case 224:
      case 225:
      case 226:
      case 227:
      case 228:
      case 229:
      case 230:
      case 231:
      case 232:
      case 233:
        return;
      case 234:
        v6 = 104;
        v7 = 8;
        goto LABEL_31;
      case 235:
        v6 = 96;
        v7 = 0;
        goto LABEL_31;
      case 236:
        v6 = 126;
        v7 = 30;
        goto LABEL_31;
      default:
        if (devilid != 136)
          return;
        v6 = 236;
        v7 = 12;
        goto LABEL_31;
    }
  }
LABEL_13:
  if (devilid == 96)
  {
    v6 = 235;
    v7 = 11;
    goto LABEL_31;
  }
  if (devilid == 104)
  {
    v6 = 234;
    v7 = 10;
    goto LABEL_31;
  }
  if (devilid != 126)
    return;
  v6 = 214;
  v7 = 22;
LABEL_31:
  v8 = (s64)GBWK->anlyzBit + 4 * (v6 >> 5);
  *(u32 *)(v8 + 32) |= 1 << v7;
}

// 0x1edd730
bool sBtlCheckItemMember_Dead(s32 index) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v7;
  s32 badstatus;
  sdatUnitWork_t *StockUnitData;
  u32 v12;
  s32 v13;
  u32 v15;

  if (wk->member_num <= 0)
    return 1;
  if (wk->summonindex[0] != index)
    return 1;
  Nakama = sBtlGetNakama(0);
  if (!Nakama)
    return 1;
  v7 = Nakama;
  if (CheckLiveTarget(v7))
    return 1;
  badstatus = v7->para->badstatus;
  sBtlResetBadStatus(v7, badstatus);
  StockUnitData = sBtlGetStockUnitData(index);
  ClassCopy(v7->para, StockUnitData, 0);
  v12 = sBtlGetBadStatus(v7->para);
  if (v12 == 22)
    return 1;
  v15 = v12;
  sBtlSetBadStatus_No(v7, 0, v15, 1, v13);
  return 1;
}

// 0x1eddaf0
bool sBtlCheckItemMember(s32 index) {
  s16 *summonindex;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v8;
  s32 badstatus;
  sdatUnitWork_t *StockUnitData;
  u32 v13;
  s32 v14;
  u32 v16;
  SBTLEXP_LISTWORK *expList;

  if (wk->member_num < 1)
    return 1;
  summonindex = wk->summonindex;
  if (summonindex[0] != index)
  {
    if (summonindex[1] != index)
      return 1;
    goto LABEL_15;
  }
  Nakama = sBtlGetNakama(0);
  if (!Nakama)
    return 1;
  goto LABEL_16;
LABEL_15:
  Nakama = sBtlGetNakama(1);
  if (!Nakama)
    return 1;
LABEL_16:
  v8 = Nakama;
  if (wk->summonflg[index] == 2)
  {
    if (!CheckLiveTarget(v8))
    {
      expList = wk->expList;
      sBtlResetVicePara(expList);
      sBtlResetBattlePara(v8, index);
      return 1;
    }
    return 1;
  }
  badstatus = v8->para->badstatus;
  sBtlResetBadStatus(v8, badstatus);
  StockUnitData = sBtlGetStockUnitData(index);
  ClassCopy(v8->para, StockUnitData, 0);
  v13 = sBtlGetBadStatus(v8->para);
  if (v13 == 22 || (u32)(v8->mode - 1) < 2)
    return 1;
  v16 = v13;
  sBtlSetBadStatus_No(v8, 0, v16, 1, v14);
  return 1;
}

// 0x1eddf50
void sBtlSetBadStatus(sdatUnitWork_t *unit, s32 bstno) {
  s32 badstatus;
  s16 v4;
  s16 v5;

  if (unit && (u32)bstno <= 0x14)
  {
    badstatus = unit->badstatus;
    *(u32 *)&unit->badst_cnt2 = 0;
    if (bstno == 12)
      v4 = 900;
    else
      v4 = 0;
    unit->badstatus = badstatus | (1 << bstno);
    if (bstno == 11)
      v5 = 1800;
    else
      v5 = v4;
    unit->badst_cnt = v5;
  }
}

// 0x1ed80b0
s32 sBtlUpdateBadStatusNo(s32 bstno) {
  s32 *v3;
  s32 v4;
  u16 Percentage;
  s64 v6;

  v3 = NewSpecific(s32, 5u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__83F07A0FF7F15BB48E87D6CE388FC191B140534C69BB3EB88A858ABCF11096E1, 0);
  if (bstno == 18)
  {
    v4 = *(u32 *)((char *)v3 + 24);
    Percentage = GetPercentage();
    v6 = 0;
    while ((v4 & ~(v4 >> 31)) != (u32)v6)
    {
      if (100 / v4 * (s32)++v6 > Percentage)
        return *(u32 *)((s64)(char *)v3 + 4 * v6 + 28);
    }
  }
  return bstno;
}

// 0x1eddfa0
void sBtlSetBadStatusRand(sdatUnitWork_t *unit, SKLID sklid) {
  SBTLUNIT_WORK *Nakama;
  sdatUnitWork_t *v7;
  SBTLUNIT_WORK *PlayerUnit;
  SBTLUNIT_WORK *v9;
  sdatUnitWork_t *para;
  s32 *v11;
  s32 v12;
  u16 Percentage;
  s64 v15;
  u32 v16;
  void *v17;
  s32 luck;
  s32 badstatus;
  s16 v20;
  s16 v21;
  s32 PlayerID;

  if ((sBtlGetSkilltbl(sklid)->badst & 0x40000) == 0)
    return;
  if (unit->devilid || (unit->flag & 2) == 0)
  {
    Nakama = sBtlGetNakama(0);
    if (!Nakama || (v7 = Nakama->para, PlayerUnit = Nakama, v7->devilid != unit->devilid) || v7->uniq_code != unit->uniq_code)
    {
      v9 = sBtlGetNakama(1);
      if (!v9)
        goto LABEL_12;
      para = v9->para;
      PlayerUnit = v9;
      if (para->devilid != unit->devilid || para->uniq_code != unit->uniq_code)
        goto LABEL_12;
    }
LABEL_40:
    sBtlCheckBadStatus(0, PlayerUnit, sklid, 0);
    return;
  }
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  if (PlayerUnit)
    goto LABEL_40;
LABEL_12:
  v11 = NewSpecific(s32, 5u);
  InitializeArray_55364416(v11, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__83F07A0FF7F15BB48E87D6CE388FC191B140534C69BB3EB88A858ABCF11096E1, 0);
  v12 = *(u32 *)((char *)v11 + 24);
  Percentage = GetPercentage();
  v15 = 0;
  v16 = 18;
  while ((v12 & ~(v12 >> 31)) != (u32)v15)
  {
    if (100 / v12 * (s32)++v15 > Percentage)
    {
      v16 = *(u32 *)((s64)(char *)v11 + 4 * v15 + 28);
      break;
    }
  }
  if (sBtlCheckBadStatus_Number(unit->badstatus, v16, 0))
  {
    v17 = NewSpecific(s32, 0x15u);
    InitializeArray_55364416(v17, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__515F9C7D26FB948050975ABBBF53EA89B3FBD3E402B5A7B2AEC7081E44591542, 0);
    luck = unit->now->luck;
    if (sBtlCheckBadStatus_Hit(unit->aisyo, luck, unit, luck, sklid, v16, *((u32 *)&v17[2].klass + v16), 1u, 0))
    {
      if (v16 <= 0x14)
      {
        badstatus = unit->badstatus;
        *(u32 *)&unit->badst_cnt2 = 0;
        if (v16 == 12)
          v20 = 900;
        else
          v20 = 0;
        unit->badstatus = badstatus | (1 << v16);
        if (v16 == 11)
          v21 = 1800;
        else
          v21 = v20;
        unit->badst_cnt = v21;
      }
    }
  }
}

// 0x1edfa70
s32 CalcItem(sdatUnitWork_t *unit, s32 itemid) {
  SBTLCALC_DMGWORK *v5;
  s32 sklid;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v8;
  SBTLCALC_DMGWORK *v10;
  SBTLSKILLP_TBL *v11;
  u32 flg;
  s32 Damage_CHUUSEI;
  u32 v18;
  s32 Damage_I_REC_K;
  s32 Damage_I_REC_P;
  s32 v21;
  u32 badst;
  s32 badstatus;
  sdatParaWork_t *pitem;
  s16 str_low;
  sdatParaWork_t *v26;
  s16 vit_low;
  u32 v31;
  s32 BadStatus_Attr;
  s32 luck;

  v5 = Allocate(SBTLCALC_DMGWORK);
  sklid = sBtlGetItemtbl(itemid)->sklid;
  if (sklid)
  {
    Skilltbl = sBtlGetSkilltbl(sklid);
    v8 = Skilltbl;
    if (!cmpChkEnableUseUnit(unit, itemid))
      return 0;
    flg = v8->flg;
    if ((flg & 0x1000) != 0)
    {
      v5->n0 = v8->n0;
      Damage_I_REC_K = sBtlGetDamage_I_REC_K(unit, v5, v11, 0);
      flg = v8->flg;
      Damage_CHUUSEI = Damage_I_REC_K;
      if ((flg & 0x2000) == 0)
      {
LABEL_26:
        if ((flg & 0x4000) == 0)
          goto LABEL_27;
        goto LABEL_38;
      }
    }
    else
    {
      Damage_CHUUSEI = 0;
      if ((flg & 0x2000) == 0)
        goto LABEL_26;
    }
    v5->n1 = v8->n1;
    Damage_I_REC_P = sBtlGetDamage_I_REC_P(unit, v5, v11, 0);
    flg = v8->flg;
    Damage_CHUUSEI = Damage_I_REC_P;
    if ((flg & 0x4000) == 0)
    {
LABEL_27:
      if ((flg & 0x8000) == 0)
        goto LABEL_28;
      goto LABEL_41;
    }
LABEL_38:
    v5->n0 = v8->n0;
    v21 = sBtlGetDamage_I_REC_K(unit, v5, v11, 1);
    flg = v8->flg;
    Damage_CHUUSEI = v21;
    if ((flg & 0x8000) == 0)
    {
LABEL_28:
      if ((flg & 0x10000) == 0)
        goto LABEL_29;
      goto LABEL_44;
    }
LABEL_41:
    v5->n1 = v8->n1;
    Damage_CHUUSEI = sBtlGetDamage_I_REC_P(unit, v5, v11, 1);
    if ((v8->flg & 0x10000) == 0)
    {
LABEL_29:
      v18 = v8->flg;
      if (v8->attrtime < 1)
        goto LABEL_58;
      goto LABEL_50;
    }
LABEL_44:
    badst = v8->badst;
    badstatus = unit->badstatus;
    if ((badstatus & badst) != 0)
    {
      Damage_CHUUSEI = 0;
      unit->badst_cnt = 0;
      unit->badstatus = badstatus & ~badst;
      v18 = v8->flg;
      if (v8->attrtime < 1)
        goto LABEL_58;
      goto LABEL_50;
    }
    Damage_CHUUSEI = 0;
    v18 = v8->flg;
    if (v8->attrtime < 1)
      goto LABEL_58;
LABEL_50:
    if ((v18 & 0x1E0000) != 0)
    {
      pitem = unit->pitem;
      *(u64 *)&pitem->hp = 0;
      *(u64 *)&pitem->mp = 0;
      str_low = LOBYTE(pitem->str);
      v26 = pitem;
      v26 = unit->pitem;
      vit_low = LOBYTE(v26->vit);
      pitem->str = str_low;
      v26->vit = vit_low;
      v26->tec = LOBYTE(v26->tec);
      v26->luck = LOBYTE(v26->luck);
      unit->itemstatus &= 0x3FFFFCF0u;
      *(u32 *)&unit->itemst_cnt = 0;
      v18 = v8->flg;
    }
LABEL_58:
    if ((v18 & 0x20000) != 0)
    {
      sBtlGetDamage_P_STR(unit, v10, v8, itemid);
      v18 = v8->flg;
      Damage_CHUUSEI = 0;
      if ((v18 & 0x40000) == 0)
      {
LABEL_60:
        if ((v18 & 0x80000) == 0)
          goto LABEL_61;
        goto LABEL_73;
      }
    }
    else if ((v18 & 0x40000) == 0)
    {
      goto LABEL_60;
    }
    sBtlGetDamage_P_VIT(unit, v10, v8, itemid);
    v18 = v8->flg;
    Damage_CHUUSEI = 0;
    if ((v18 & 0x80000) == 0)
    {
LABEL_61:
      if ((v18 & 0x100000) == 0)
        goto LABEL_62;
      goto LABEL_76;
    }
LABEL_73:
    sBtlGetDamage_P_TEC(unit, v10, v8, itemid);
    v18 = v8->flg;
    Damage_CHUUSEI = 0;
    if ((v18 & 0x100000) == 0)
    {
LABEL_62:
      if ((v18 & 0x40) == 0)
        goto LABEL_63;
      goto LABEL_79;
    }
LABEL_76:
    sBtlGetDamage_P_LUCK(unit, v10, v8, itemid);
    v18 = v8->flg;
    Damage_CHUUSEI = 0;
    if ((v18 & 0x40) == 0)
    {
LABEL_63:
      if ((v18 & 0x80) == 0)
        goto LABEL_64;
      goto LABEL_82;
    }
LABEL_79:
    Damage_CHUUSEI = sBtlGetDamage_CHUUSEI(unit, v10, v8);
    if ((v8->flg & 0x80) == 0)
    {
LABEL_64:
      goto LABEL_65;
    }
LABEL_82:
    sBtlGetDamage_ITEMFLG(unit, v10, v8, itemid);
    Damage_CHUUSEI = 0;
LABEL_65:
    sBtlSetBadStatusRand(unit, sklid);
    if ((v8->badst & 0x40000) == 0)
      return Damage_CHUUSEI;
    if ((unit->badstatus & 0x1D80) == 0 && GetPercentage() <= 0x31u)
    {
      v31 = unit->badstatus;
      if (sBtlCheckBadStatus_Number(v31, 11, 0))
      {
        BadStatus_Attr = sBtlGetBadStatus_Attr(0xBu);
        luck = unit->now->luck;
        if (sBtlCheckBadStatus_Hit(unit->aisyo, luck, unit, luck, sklid, 0xBu, BadStatus_Attr, 1u, 0))
        {
          unit->badstatus = unit->badstatus & 0xFFFFF3FF | 0x800;
          unit->badst_cnt = 1800;
        }
      }
    }
    return Damage_CHUUSEI;
  }
  if (!cmpChkEnableUseUnit(unit, itemid))
    return 0;
  if (tbldata[itemid]->type != 0x4000)
    return 0;
  return sBtlGetDamege_I_EXP(unit, itemid);
}

// 0x1ee00e0
void sBtlResetItemFlg(sdatUnitWork_t *unit) {
  unit->itemstatus &= 0xFFFFFBEF;
}

// 0x1ee0100
s32 sBtlCheckDrink(void) {
  sdatPlayerUnitWork_t *PlayerData;
  sdatUnitWork_t *para;
  sdatPlayerUnitWork_t *v3;
  u16 *v4;
  bool v5;
  u32 itemstatus;
  s32 itemst_cnt2;
  s32 swordno;

  PlayerData = sBtlGetPlayerData();
  para = PlayerData->para;
  if (!para->itemst_cnt2)
    return 0;
  v3 = PlayerData;
  v4 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v4, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  v5 = evtBitCheck(v4[0]);
  itemstatus = para->itemstatus;
  if (!v5)
  {
    para->itemstatus = itemstatus & 0xBFFFFFFF;
LABEL_18:
    if (para->itemst_cnt <= 0)
      goto LABEL_12;
    return 0;
  }
  if ((itemstatus & 0x40000000) != 0)
    goto LABEL_18;
  if ((itemstatus & 0x80000000) != 0)
  {
    para->itemstatus = itemstatus & 0x3FFFFFFF | 0x40000000;
    if (--para->itemst_cnt <= 0)
      goto LABEL_12;
    return 0;
  }
  para->itemstatus = itemstatus | 0x40000000;
  if (--para->itemst_cnt > 0)
    return 0;
LABEL_12:
  itemst_cnt2 = para->itemst_cnt2;
  sBtlCheckItemCount(para);
  swordno = v3->swordno;
  datCalcNowParam(para, swordno, 0);
  return itemst_cnt2;
}

// 0x1ee02c0
bool sBtlCheckItemCount(sdatUnitWork_t *unit) {
  sdatParaWork_t *pitem;
  s16 str_low;
  u8 *v6;
  s16 v7;
  s16 v9;
  s16 v10;

  unit->itemstatus &= 0x3FFFFCF0u;
  *(u32 *)&unit->itemst_cnt = 0;
  pitem = unit->pitem;
  *(u64 *)&pitem->hp = 0;
  *(u64 *)&pitem->mp = 0;
  str_low = LOBYTE(pitem->str);
  v6 = pitem;
  v6 = unit->pitem;
  v7 = v6[34];
  pitem->str = str_low;
  v9 = v6[36];
  *((u16 *)v6 + 17) = v7;
  v10 = v6[38];
  *((u16 *)v6 + 18) = v9;
  *((u16 *)v6 + 19) = v10;
  *(u64 *)&unit->itemstatus = unit->itemstatus & 0x3FFFFCF0;
  return 1;
}

// 0x1ee03c0
bool sBtlCheckHaveskill_Atk(sdatUnitWork_t *unit) {
  u64 v3;
  char v4;
  bool v5;
  s32 v6;
  SBTLSKILLP_TBL *Skilltbl;
  u32 type;

  v3 = 0;
  v4 = 1;
  do
  {
    v6 = unit->haveskill[v3];
    if (v6)
    {
      if (v6 != 288)
      {
        Skilltbl = sBtlGetSkilltbl(v6);
        type = Skilltbl->type;
        if (type <= 0xFFF && ((Skilltbl->attr & 1) != 0 || type - 1 < 2))
          break;
      }
    }
    v5 = v3++ >= 0x10;
    v4 = !v5;
  }
  while (v3 != 17);
  return v4;
}

// 0x1ee0450
bool sBtlCheckHaveskill_Magic(sdatUnitWork_t *unit) {
  s32 v3;
  u32 type;
  bool result;
  s32 v7;
  u32 v8;
  s32 v9;
  u32 v10;
  s32 v11;
  u32 v12;
  s32 v13;
  u32 v14;
  s32 v15;
  u32 v16;
  s32 v17;
  u32 v18;
  s32 v19;
  u32 v20;
  s32 v21;
  u32 v22;
  s32 v23;
  u32 v24;
  s32 v25;
  u32 v26;
  s32 v27;
  u32 v28;
  s32 v29;
  u32 v30;
  s32 v31;
  u32 v32;
  s32 v33;
  u32 v34;
  s32 v35;
  u32 v36;
  s32 v37;
  u32 v38;

  v3 = unit->haveskill[0];
  if (v3)
  {
    if (v3 != 149 && v3 != 288)
    {
      type = sBtlGetSkilltbl(v3)->type;
      if (type <= 0xFFF && (type == 3 || type == 5))
        return 1;
    }
  }
  v7 = unit->haveskill[1];
  if (!v7 || v7 == 149 || v7 == 288 || (v8 = sBtlGetSkilltbl(v7)->type, v8 > 0xFFF) || (result = 1, v8 != 3) && v8 != 5)
  {
    v9 = unit->haveskill[2];
    if (!v9 || v9 == 149 || v9 == 288 || (v10 = sBtlGetSkilltbl(v9)->type, v10 > 0xFFF) || (result = 1, v10 != 3) && v10 != 5)
    {
      v11 = unit->haveskill[3];
      if (!v11 || v11 == 149 || v11 == 288 || (v12 = sBtlGetSkilltbl(v11)->type, v12 > 0xFFF) || (result = 1, v12 != 3) && v12 != 5)
      {
        v13 = unit->haveskill[4];
        if (!v13 || v13 == 149 || v13 == 288 || (v14 = sBtlGetSkilltbl(v13)->type, v14 > 0xFFF) || (result = 1, v14 != 3) && v14 != 5)
        {
          v15 = unit->haveskill[5];
          if (!v15 || v15 == 149 || v15 == 288 || (v16 = sBtlGetSkilltbl(v15)->type, v16 > 0xFFF) || (result = 1, v16 != 3) && v16 != 5)
          {
            v17 = unit->haveskill[6];
            if (!v17 || v17 == 149 || v17 == 288 || (v18 = sBtlGetSkilltbl(v17)->type, v18 > 0xFFF) || (result = 1, v18 != 3) && v18 != 5)
            {
              v19 = unit->haveskill[7];
              if (!v19 || v19 == 149 || v19 == 288 || (v20 = sBtlGetSkilltbl(v19)->type, v20 > 0xFFF) || (result = 1, v20 != 3) && v20 != 5)
              {
                v21 = unit->haveskill[8];
                if (!v21 || v21 == 149 || v21 == 288 || (v22 = sBtlGetSkilltbl(v21)->type, v22 > 0xFFF) || (result = 1, v22 != 3) && v22 != 5)
                {
                  v23 = unit->haveskill[9];
                  if (!v23 || v23 == 149 || v23 == 288 || (v24 = sBtlGetSkilltbl(v23)->type, v24 > 0xFFF) || (result = 1, v24 != 3) && v24 != 5)
                  {
                    v25 = unit->haveskill[10];
                    if (!v25 || v25 == 149 || v25 == 288 || (v26 = sBtlGetSkilltbl(v25)->type, v26 > 0xFFF) || (result = 1, v26 != 3) && v26 != 5)
                    {
                      v27 = unit->haveskill[11];
                      if (!v27 || v27 == 149 || v27 == 288 || (v28 = sBtlGetSkilltbl(v27)->type, v28 > 0xFFF) || (result = 1, v28 != 3) && v28 != 5)
                      {
                        v29 = unit->haveskill[12];
                        if (!v29 || v29 == 149 || v29 == 288 || (v30 = sBtlGetSkilltbl(v29)->type, v30 > 0xFFF) || (result = 1, v30 != 3) && v30 != 5)
                        {
                          v31 = unit->haveskill[13];
                          if (!v31 || v31 == 149 || v31 == 288 || (v32 = sBtlGetSkilltbl(v31)->type, v32 > 0xFFF) || (result = 1, v32 != 3) && v32 != 5)
                          {
                            v33 = unit->haveskill[14];
                            if (!v33 || v33 == 149 || v33 == 288 || (v34 = sBtlGetSkilltbl(v33)->type, v34 > 0xFFF) || (result = 1, v34 != 3) && v34 != 5)
                            {
                              v35 = unit->haveskill[15];
                              if (!v35 || v35 == 149 || v35 == 288 || (v36 = sBtlGetSkilltbl(v35)->type, v36 > 0xFFF) || (result = 1, v36 != 3) && v36 != 5)
                              {
                                result = 0;
                                v37 = unit->haveskill[16];
                                if (v37 && v37 != 149 && v37 != 288)
                                {
                                  v38 = sBtlGetSkilltbl(v37)->type;
                                  return v38 <= 0xFFF && ((v38 - 3) & 0xFFFD) == 0;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

// 0x1ee0910
bool sBtlCheckHaveskill_Rec(sdatUnitWork_t *unit) {
  u64 v3;
  char v4;
  bool v5;
  s32 v6;
  SBTLSKILLP_TBL *Skilltbl;

  v3 = 0;
  v4 = 1;
  do
  {
    v6 = unit->haveskill[v3];
    if (v6)
    {
      if (v6 != 149 && v6 != 288)
      {
        Skilltbl = sBtlGetSkilltbl(v6);
        if (Skilltbl->type <= 0xFFFu && ((Skilltbl->flg & 0x24) != 0 || (Skilltbl->flg2 & 0x40) != 0))
        {
          break;
        }
      }
    }
    v5 = v3++ >= 0x10;
    v4 = !v5;
  }
  while (v3 != 17);
  return v4;
}

// 0x1ee09b0
bool sBtlCheckAutoSkill(sdatUnitWork_t *unit, s8 flg) {
  return 0;
}

// 0x1ee09c0
bool sBtlCheckAutoSkill_Enemy(SBTLUNIT_WORK *wk) {
  SKLID *haveskill;
  SKLID *v5;

  haveskill = wk->haveskill;
  v5 = wk->para->haveskill;
  v5[0] = haveskill[0];
  v5[1] = haveskill[1];
  v5[2] = haveskill[2];
  v5[3] = haveskill[3];
  v5[4] = haveskill[4];
  v5[5] = haveskill[5];
  v5[6] = haveskill[6];
  v5[7] = haveskill[7];
  v5[8] = haveskill[8];
  v5[9] = haveskill[9];
  v5[10] = haveskill[10];
  v5[11] = haveskill[11];
  v5[12] = haveskill[12];
  v5[13] = haveskill[13];
  v5[14] = haveskill[14];
  v5[15] = haveskill[15];
  sBtlSetAutoSkill(wk);
  return 1;
}

// 0x1ee0ab0
bool sBtlSetAutoSkill(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;
  sdatUnitWork_t *v9;
  s32 v10;
  sdatUnitWork_t *v13;
  s32 v14;
  sdatUnitWork_t *v17;
  s32 v18;
  sdatUnitWork_t *v21;
  s32 v22;
  sdatUnitWork_t *v25;
  s32 v26;
  sdatUnitWork_t *v29;
  s32 v30;
  sdatUnitWork_t *v33;
  s32 v34;
  s32 v38;
  s32 v40;
  s32 v42;
  s32 v44;
  s32 v46;
  s32 v48;
  s32 v50;
  s32 v52;

  para = wk->para;
  AutoSkill_ID = sBtlGetAutoSkill_ID(para, 0);
  if (!AutoSkill_ID)
  {
    v9 = wk->para;
    goto LABEL_5;
  }
  v38 = AutoSkill_ID;
  sBtlSetAutoSkill_ID(wk, v38);
  v9 = wk->para;
LABEL_5:
  v10 = sBtlGetAutoSkill_ID(v9, 1);
  if (!v10)
  {
    v13 = wk->para;
    goto LABEL_7;
  }
  v40 = v10;
  sBtlSetAutoSkill_ID(wk, v40);
  v13 = wk->para;
LABEL_7:
  v14 = sBtlGetAutoSkill_ID(v13, 2);
  if (!v14)
  {
    v17 = wk->para;
    goto LABEL_9;
  }
  v42 = v14;
  sBtlSetAutoSkill_ID(wk, v42);
  v17 = wk->para;
LABEL_9:
  v18 = sBtlGetAutoSkill_ID(v17, 3);
  if (!v18)
  {
    v21 = wk->para;
    goto LABEL_11;
  }
  v44 = v18;
  sBtlSetAutoSkill_ID(wk, v44);
  v21 = wk->para;
LABEL_11:
  v22 = sBtlGetAutoSkill_ID(v21, 4);
  if (!v22)
  {
    v25 = wk->para;
    goto LABEL_13;
  }
  v46 = v22;
  sBtlSetAutoSkill_ID(wk, v46);
  v25 = wk->para;
LABEL_13:
  v26 = sBtlGetAutoSkill_ID(v25, 5);
  if (!v26)
  {
    v29 = wk->para;
    goto LABEL_15;
  }
  v48 = v26;
  sBtlSetAutoSkill_ID(wk, v48);
  v29 = wk->para;
LABEL_15:
  v30 = sBtlGetAutoSkill_ID(v29, 6);
  if (!v30)
  {
    v33 = wk->para;
    goto LABEL_17;
  }
  v50 = v30;
  sBtlSetAutoSkill_ID(wk, v50);
  v33 = wk->para;
LABEL_17:
  v34 = sBtlGetAutoSkill_ID(v33, 7);
  if (!v34)
    return 1;
  v52 = v34;
  sBtlSetAutoSkill_ID(wk, v52);
  return 1;
}

// 0x1ee15c0
bool sBtlSetRaidouKuisibari(SBTLUNIT_WORK *wk) {
  s32 v4;

  if ((~wk->side & 0x81) != 0)
    return 0;
  if (sBtlKuisibariChk(wk))
    v4 = 0x20000000;
  else
    v4 = 0;
  wk->status = wk->status & 0xDFFFFFFF | v4;
  return 0;
}

// 0x1ee1b00
bool sBtlSetAutoSkill_GB(sdatUnitWork_t *unit) {
  sdatParaWork_t *v4;
  s32 AutoSkill_ID;
  s32 AutoSkillPara;
  s32 v12;
  s32 v13;
  s32 v15;
  s32 v18;
  s32 v19;
  s32 v21;
  s32 v24;
  s32 v25;
  s32 v27;
  s32 v30;
  s32 v31;
  s32 v33;
  s32 v36;
  s32 v37;
  s32 v39;
  s32 v42;
  s32 v43;
  s32 v45;
  s32 v48;
  s32 v49;
  s32 v51;
  s32 v53;

  v4 = Allocate(sdatParaWork_t);
  _ctor(v4, 0);
  unit->pbtl = v4;
  *(u32 *)&unit->autost_cnt = 0;
  AutoSkill_ID = sBtlGetAutoSkill_ID(unit, 0);
  AutoSkillPara = sBtlGetAutoSkillPara(AutoSkill_ID, &unit->autost_cnt, &unit->autost_cnt2);
  if ((AutoSkillPara & 0x80000000) == 0)
  {
    v12 = AutoSkillPara;
    sBtlSetAutoSkill_GBID(unit, v12, AutoSkill_ID);
  }
  v13 = sBtlGetAutoSkill_ID(unit, 1);
  v15 = sBtlGetAutoSkillPara(v13, &unit->autost_cnt, &unit->autost_cnt2);
  if ((v15 & 0x80000000) == 0)
  {
    v18 = v15;
    sBtlSetAutoSkill_GBID(unit, v18, v13);
  }
  v19 = sBtlGetAutoSkill_ID(unit, 2);
  v21 = sBtlGetAutoSkillPara(v19, &unit->autost_cnt, &unit->autost_cnt2);
  if ((v21 & 0x80000000) == 0)
  {
    v24 = v21;
    sBtlSetAutoSkill_GBID(unit, v24, v19);
  }
  v25 = sBtlGetAutoSkill_ID(unit, 3);
  v27 = sBtlGetAutoSkillPara(v25, &unit->autost_cnt, &unit->autost_cnt2);
  if ((v27 & 0x80000000) == 0)
  {
    v30 = v27;
    sBtlSetAutoSkill_GBID(unit, v30, v25);
  }
  v31 = sBtlGetAutoSkill_ID(unit, 4);
  v33 = sBtlGetAutoSkillPara(v31, &unit->autost_cnt, &unit->autost_cnt2);
  if ((v33 & 0x80000000) == 0)
  {
    v36 = v33;
    sBtlSetAutoSkill_GBID(unit, v36, v31);
  }
  v37 = sBtlGetAutoSkill_ID(unit, 5);
  v39 = sBtlGetAutoSkillPara(v37, &unit->autost_cnt, &unit->autost_cnt2);
  if ((v39 & 0x80000000) == 0)
  {
    v42 = v39;
    sBtlSetAutoSkill_GBID(unit, v42, v37);
  }
  v43 = sBtlGetAutoSkill_ID(unit, 6);
  v45 = sBtlGetAutoSkillPara(v43, &unit->autost_cnt, &unit->autost_cnt2);
  if ((v45 & 0x80000000) == 0)
  {
    v48 = v45;
    sBtlSetAutoSkill_GBID(unit, v48, v43);
  }
  v49 = sBtlGetAutoSkill_ID(unit, 7);
  v51 = sBtlGetAutoSkillPara(v49, &unit->autost_cnt, &unit->autost_cnt2);
  if ((v51 & 0x80000000) == 0)
  {
    v53 = v51;
    sBtlSetAutoSkill_GBID(unit, v53, v49);
  }
  return 1;
}

// 0x1ee1300
bool sBtlSetAutoSkill_ID(SBTLUNIT_WORK *wk, SKLID sklid) {
  s64 v6;
  u32 v7;
  s32 side;
  s32 ListID;
  SBATTLE_WORK *v11;
  s32 v12;
  s32 v14;
  SBATTLE_WORK *v15;
  s32 v16;
  u32 kuishibBit;
  u32 deadbombBit;

  v6 = (u16)wk->summonindex[0];
  v7 = sBtlGetSkilltbl(sklid)->attr & 0xFFFFF000;
  if (v7 != 4096)
  {
    if (v7 != 20480)
      return 1;
    side = wk->side;
    if ((side & 0x81) != 1)
    {
      if ((side & 0x80) == 0)
      {
LABEL_34:
        wk->status |= 0x20000000u;
        return 1;
      }
      return 1;
    }
    if ((v6 & 0x8000) != 0)
      goto LABEL_45;
    ListID = wk->ListID;
    v11 = wk;
    if (ListID != v11->summonID[v6])
    {
LABEL_45:
      v12 = wk->summonindex[1];
    }
    else
    {
      v11 = wk;
      v12 = v11->summonindex[0];
    }
    kuishibBit = wk->kuishibBit;
    if (!sBtlCheckBit(kuishibBit, v12))
      goto LABEL_34;
    return 1;
  }
  if ((wk->side & 0x81) == 1)
  {
    if ((v6 & 0x8000) != 0)
      goto LABEL_46;
    v14 = wk->ListID;
    v15 = wk;
    if (v14 != v15->summonID[v6])
    {
LABEL_46:
      v16 = wk->summonindex[1];
    }
    else
    {
      v15 = wk;
      v16 = v15->summonindex[0];
    }
    deadbombBit = wk->deadbombBit;
    if (sBtlCheckBit(deadbombBit, v16))
      return 1;
  }
  wk->hstatus |= 0x800u;
  return 1;
}

// 0x1ee1e90
bool sBtlResetAutoSkill(sdatUnitWork_t *unit) {
  sdatParaWork_t *v3;
  sdatParaWork_t *p_pbtl;

  v3 = Allocate(sdatParaWork_t);
  _ctor(v3, 0);
  unit->pbtl = v3;
  p_pbtl = &unit->pbtl;
  *(u32 *)((char *)p_pbtl + 98) = 0;
  return 1;
}

// 0x1ed5be0
bool sBtlGetSpiritSkillChk(SKLID sklid) {
  s64 v4;
  s32 v5;
  s64 v6;
  SKLID *spiritSkill;
  s64 max_length_low;

  v4 = 0;
  do
  {
    v6 = v4;
    spiritSkill = GBWK->player->spiritSkill;
    max_length_low = SLODWORD(spiritSkill->max_length);
    if (v6 >= max_length_low)
      break;
    spiritSkill = GBWK->player->spiritSkill;
    v5 = spiritSkill[v6];
    v4 = v6 + 1;
  }
  while (v5 != sklid);
  return v6 < max_length_low;
}

// 0x1edcab0
AUTO sBtlGetAutoSkillPara(SKLID sklid, s16 *para1, s16 *para2) {
  SBTLSKILLP_TBL *Skilltbl;
  f32 n1;
  u32 attr;
  signed s32 v10;
  s32 v11;
  s16 v13;
  s16 v14;
  s16 n0;

  if (!sklid)
  {
    *para1 = 0;
    *para2 = 0;
    return -1;
  }
  Skilltbl = sBtlGetSkilltbl(sklid);
  n1 = Skilltbl->n1;
  attr = Skilltbl->attr;
  v10 = attr & 0xFFFFF000;
  *para1 = Skilltbl->badst & 0xFFF;
  v11 = n1;
  if (n1 == INFINITY)
    LOWORD(v11) = 0;
  *para2 = v11;
  if (v10 < 176128)
  {
    if (v10 != 12288)
    {
      if (v10 != 61440 && v10 != 73728)
        return attr >> 12;
      goto LABEL_18;
    }
    n0 = 0;
  }
  else
  {
    if (v10 >= 356352)
    {
      if (v10 != 376832)
      {
        if (v10 != 356352)
          return attr >> 12;
LABEL_18:
        v13 = *para1;
        if ((v13 & 1) == 0)
        {
          if ((v13 & 2) != 0)
          {
            v14 = 1;
          }
          else if ((v13 & 4) != 0)
          {
            v14 = 2;
          }
          else if ((v13 & 8) != 0)
          {
            v14 = 3;
          }
          else if ((v13 & 0x10) != 0)
          {
            v14 = 4;
          }
          else if ((v13 & 0x20) != 0)
          {
            v14 = 5;
          }
          else if ((v13 & 0x40) != 0)
          {
            v14 = 6;
          }
          else if ((v13 & 0x80) != 0)
          {
            v14 = 7;
          }
          else if ((v13 & 0x100) != 0)
          {
            v14 = 8;
          }
          else if ((v13 & 0x200) != 0)
          {
            v14 = 9;
          }
          else if ((v13 & 0x400) != 0)
          {
            v14 = 10;
          }
          else if ((v13 & 0x800) != 0)
          {
            v14 = 11;
          }
          else if ((v13 & 0x1000) != 0)
          {
            v14 = 12;
          }
          else if ((v13 & 0x2000) != 0)
          {
            v14 = 13;
          }
          else if ((v13 & 0x4000) != 0)
          {
            v14 = 14;
          }
          else if (v13 >= 0)
          {
            v14 = -1;
          }
          else
          {
            v14 = 15;
          }
          goto LABEL_54;
        }
        v14 = 0;
LABEL_54:
        *para1 = v14;
        return attr >> 12;
      }
    }
    else if (v10 != 176128)
    {
      if (v10 != 352256)
        return attr >> 12;
      goto LABEL_18;
    }
    n0 = Skilltbl->n0;
  }
  *para1 = n0;
  return attr >> 12;
}

// 0x1ee0e40
SKLID sBtlGetAutoSkill_ID(sdatUnitWork_t *unit, s32 id) {
  s32 iOmoideSkillCnt;
  s32 v6;
  s32 v7;
  s32 v8;
  s64 v9;
  s32 result;
  char *v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  SBTLSKILLP_TBL *Skilltbl;

  iOmoideSkillCnt = unit->iOmoideSkillCnt;
  if (!IsENEMYOFFSET(unit->devilid))
  {
    result = 0;
    if ((id & 0x80000000) == 0 && iOmoideSkillCnt > id)
    {
      v11 = (char *)unit->aOmoideSkill + 4 * (u32)id;
      return *((u32 *)v11 + 8);
    }
    return result;
  }
  v6 = 0;
  v7 = unit->haveskill[0];
  if (!v7 || v7 == 149 || v7 == 288)
  {
LABEL_7:
    v8 = unit->haveskill[1];
    if (v8)
      goto LABEL_8;
    goto LABEL_20;
  }
  if ((sBtlGetSkilltbl(v7)->type & 0x2000) == 0)
  {
    v6 = 0;
    goto LABEL_7;
  }
  if (!id)
  {
    v9 = 0;
    goto LABEL_125;
  }
  v6 = 1;
  v8 = unit->haveskill[1];
  if (v8)
  {
LABEL_8:
    if (v8 != 149 && v8 != 288 && (sBtlGetSkilltbl(v8)->type & 0x2000) != 0)
    {
      if (v6 == id)
      {
        v9 = 1;
LABEL_125:
        v11 = (char *)unit->haveskill + 4 * v9;
        return *((u32 *)v11 + 8);
      }
      ++v6;
    }
  }
LABEL_20:
  v12 = unit->haveskill[2];
  if (v12 && v12 != 149 && v12 != 288 && (sBtlGetSkilltbl(v12)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 2;
      goto LABEL_125;
    }
    ++v6;
  }
  v13 = unit->haveskill[3];
  if (v13 && v13 != 149 && v13 != 288 && (sBtlGetSkilltbl(v13)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 3;
      goto LABEL_125;
    }
    ++v6;
  }
  v14 = unit->haveskill[4];
  if (v14 && v14 != 149 && v14 != 288 && (sBtlGetSkilltbl(v14)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 4;
      goto LABEL_125;
    }
    ++v6;
  }
  v15 = unit->haveskill[5];
  if (v15 && v15 != 149 && v15 != 288 && (sBtlGetSkilltbl(v15)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 5;
      goto LABEL_125;
    }
    ++v6;
  }
  v16 = unit->haveskill[6];
  if (v16 && v16 != 149 && v16 != 288 && (sBtlGetSkilltbl(v16)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 6;
      goto LABEL_125;
    }
    ++v6;
  }
  v17 = unit->haveskill[7];
  if (v17 && v17 != 149 && v17 != 288 && (sBtlGetSkilltbl(v17)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 7;
      goto LABEL_125;
    }
    ++v6;
  }
  v18 = unit->haveskill[8];
  if (v18 && v18 != 149 && v18 != 288 && (sBtlGetSkilltbl(v18)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 8;
      goto LABEL_125;
    }
    ++v6;
  }
  v19 = unit->haveskill[9];
  if (v19 && v19 != 149 && v19 != 288 && (sBtlGetSkilltbl(v19)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 9;
      goto LABEL_125;
    }
    ++v6;
  }
  v20 = unit->haveskill[10];
  if (v20 && v20 != 149 && v20 != 288 && (sBtlGetSkilltbl(v20)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 10;
      goto LABEL_125;
    }
    ++v6;
  }
  v21 = unit->haveskill[11];
  if (v21 && v21 != 149 && v21 != 288 && (sBtlGetSkilltbl(v21)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 11;
      goto LABEL_125;
    }
    ++v6;
  }
  v22 = unit->haveskill[12];
  if (v22 && v22 != 149 && v22 != 288 && (sBtlGetSkilltbl(v22)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 12;
      goto LABEL_125;
    }
    ++v6;
  }
  v23 = unit->haveskill[13];
  if (v23 && v23 != 149 && v23 != 288 && (sBtlGetSkilltbl(v23)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 13;
      goto LABEL_125;
    }
    ++v6;
  }
  v24 = unit->haveskill[14];
  if (v24 && v24 != 149 && v24 != 288 && (sBtlGetSkilltbl(v24)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 14;
      goto LABEL_125;
    }
    ++v6;
  }
  v25 = unit->haveskill[15];
  if (v25 && v25 != 149 && v25 != 288 && (sBtlGetSkilltbl(v25)->type & 0x2000) != 0)
  {
    if (v6 == id)
    {
      v9 = 15;
      goto LABEL_125;
    }
    ++v6;
  }
  result = 0;
  v26 = unit->haveskill[16];
  if (v26)
  {
    if (v26 != 149 && v26 != 288)
    {
      Skilltbl = sBtlGetSkilltbl(v26);
      result = 0;
      if ((Skilltbl->type & 0x2000) != 0 && v6 == id)
      {
        v9 = 16;
        goto LABEL_125;
      }
    }
  }
  return result;
}

// 0x1ee1f10
bool sBtlCheckAutoSkill_ActerDamage_ID(SKLID sklid) {
  u32 attr;
  u32 v3;

  attr = sBtlGetSkilltbl(sklid)->attr;
  v3 = attr & 0xFFFFF000;
  if ((attr & 0xFFFFF000) <= 0xE000)
    return attr - 53248 < 0x2000;
  return v3 == 61440 || v3 == 221184 || v3 == 0x10000;
}

// 0x1ee1f80
bool sBtlCheckAutoSkill_TargetDamage_ID(SKLID sklid) {
  u32 attr;
  u32 v3;
  bool v4;
  bool v6;

  attr = sBtlGetSkilltbl(sklid)->attr;
  v3 = attr & 0xFFFFF000;
  v4 = (attr & 0xFFFFE000) == 352256;
  v6 = v3 == 0x4000 || v3 == 73728;
  if (v3 < 0x12001)
    return v6;
  else
    return v4;
}

// 0x1ee1fe0
bool sBtlCheckAutoSkill_ActerDamage(AUTO autono) {
  return ((u32)autono < 0x37) & (0x4000000001E000uLL >> autono);
}

// 0x1ee2000
bool sBtlCheckAutoSkill_TargetDamage(AUTO autono) {
  return autono == 4 || autono == 18 || (autono & 0xFFFFFFFE) == 0x56;
}

// 0x1ee2030
bool sBtlCheckAutoSkill_Action(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 attr) {
  bool result;
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 v11;
  sdatUnitWork_t *v12;

  if (attr && (attr & 0x8000) == 0)
    return 0;
  if ((hwk->attr_flg & 0x100) != 0)
    return 0;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(wk->para);
  if (BadStatus - 7 < 5)
    return 1;
  v11 = BadStatus;
  v12 = wk->para;
  if (v12)
    goto LABEL_15;
  goto LABEL_19;
  if (!v12)
  {
LABEL_19:
    if (v11 != 22)
      return v11 == 21;
    return 1;
  }
LABEL_15:
  result = 1;
  if (v11 != 22 && (v12->koufunst & 0x20) == 0)
    return v11 == 21;
  return result;
}

// 0x1ee2160
s32 CalcAutoSkill(sdatUnitWork_t *unit, AUTO autono, s32 damage, SKLID skillid, s32 para1, s32 para2) {
  char v8;
  SBTLSKILLP_TBL *Skilltbl;
  s32 result;
  SBTLDROP_WORK *v16;
  f32 v17;
  s32 v18;
  s32 ExpHosei;
  SBTLDROP_WORK *drop;
  f32 v22;
  s32 v23;
  SBTLDROP_WORK *v25;
  f32 v26;
  s32 v27;
  s32 v28;
  sdatParaWork_t *now;
  s32 hp;
  s32 *p_hp;
  s32 maxhp;
  f32 v33;
  s32 v34;
  f32 v35;

  v8 = para1;
  Skilltbl = sBtlGetSkilltbl(skillid);
  result = 0;
  switch (autono)
  {
    case 2:
      now = unit->now;
      hp = now->hp;
      maxhp = now->maxhp;
      p_hp = &now->hp;
      v33 = (f32)((f32)para2 / 100.0) * (f32)maxhp;
      v34 = v33;
      if (v33 == INFINITY)
        v34 = 0x80000000;
      *p_hp = v34 + hp;
      LimitRange(p_hp, 0, maxhp);
      goto LABEL_48;
    case 4:
      goto LABEL_40;
    case 7:
    case 81:
      result = 0;
      drop = wk->drop;
      v22 = (f32)((f32)para2 * (f32)drop->gold) / 100.0;
      v23 = v22;
      if (v22 == INFINITY)
        v23 = 0x80000000;
      drop->gold = v23;
      return result;
    case 9:
    case 83:
    case 88:
    case 89:
      v16 = wk->drop;
      v17 = (f32)((f32)para2 / 100.0) * (f32)v16->nakama_exp;
      if (v17 == INFINITY)
        v18 = 0x80000000;
      else
        v18 = v17;
      v16->nakama_exp = v18;
      ExpHosei = sBtlGetExpHosei(v18);
      result = 0;
      v16->nakama_exp = ExpHosei;
      return result;
    case 10:
    case 84:
      result = 0;
      v25 = wk->drop;
      v26 = (f32)((f32)para2 / 100.0) * (f32)v25->chuusei;
      v27 = v26;
      if (v26 == INFINITY)
        v27 = 0x80000000;
      v25->chuusei = v27;
      return result;
    case 13:
      if ((Skilltbl->flg & 0x200001) != 1 || (s16)GetPercentage() > 49)
        goto LABEL_48;
      result = 0;
      if ((Skilltbl->type & 0xFFFu) > 0xD || ((1 << LOBYTE(Skilltbl->type)) & 0x3002) == 0)
        return result;
      goto LABEL_40;
    case 14:
      if ((Skilltbl->flg & 0x200001) != 1)
        goto LABEL_48;
      if ((s16)GetPercentage() > 49)
        goto LABEL_48;
      v28 = Skilltbl->type & 0xFFF;
      if (v28 != 15 && v28 != 3)
        goto LABEL_48;
      goto LABEL_40;
    case 15:
      if ((Skilltbl->flg & 0x200001) == 1)
        goto LABEL_39;
      goto LABEL_48;
    case 16:
      if ((Skilltbl->flg & 0x10004) != 4 || (Skilltbl->s_type & 8) != 0)
        goto LABEL_48;
      goto LABEL_40;
    case 18:
    case 86:
    case 87:
LABEL_39:
      if ((((Skilltbl->attr & 0xFFF) >> v8) & 1) != 0)
        goto LABEL_40;
      goto LABEL_48;
    case 54:
      if ((Skilltbl->flg & 0x200001) == 1)
      {
LABEL_40:
        v35 = (f32)((f32)para2 / 100.0) * (f32)damage;
        if (v35 == INFINITY)
          result = 0x80000000;
        else
          result = (s32)v35;
      }
      else
      {
LABEL_48:
        result = 0;
      }
      break;
    default:
      return result;
  }
  return result;
}

// 0x1ee2570
s32 sBtlGetDropMoney(sdatUnitWork_t *unit, s32 gold) {
  if ((unit->itemstatus & 0x100) != 0)
    gold += gold / 5;
  return gold;
}

// 0x1edce00
bool sBtlCheckMoon(SBTL_MOON moon) {
  void *v3;

  v3 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  return evtBitCheck(*((u16 *)&v3[2].klass + moon));
}

// 0x1ee25a0
s32 sBtlGetSkillCost(sdatUnitWork_t *a_pUnit, SKLID a_skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v6;
  s32 para;
  s64 v10;
  char *v11;
  SKLID *spiritSkill;
  s64 v15;
  char *v16;
  SKLID *v17;
  f32 v18;

  if (!a_pUnit)
    return 0;
  Skilltbl = sBtlGetSkilltbl(a_skillid);
  if (!Skilltbl)
    return 0;
  v6 = Skilltbl;
  para = Skilltbl->para;
  if (sBtlChkHaveMemSkl(a_pUnit, 93))
    para = a_pUnit->autost_cnt2 * para / 100;
  if (wk->battlemode != 3)
  {
    v10 = 0;
    while (1)
    {
      spiritSkill = GBWK->player->spiritSkill;
      if (v10 >= SLODWORD(spiritSkill->max_length))
        break;
      spiritSkill = GBWK->player->spiritSkill;
      v11 = (char *)spiritSkill + 4 * v10++;
      if (*((u32 *)v11 + 8) == 1450)
      {
        para <<= (v6->flg & 0x200001) == 1;
        break;
      }
    }
  }
  v15 = 0;
  while (1)
  {
    v17 = GBWK->player->spiritSkill;
    if (v15 >= SLODWORD(v17->max_length))
      break;
    v17 = GBWK->player->spiritSkill;
    v16 = (char *)v17 + 4 * v15++;
    if (*((u32 *)v16 + 8) == 1447)
    {
      v18 = (f32)para * 0.8;
      if (v18 == INFINITY)
        return 0x80000000;
      para = (s32)v18;
      break;
    }
  }
  if (para)
    return para;
  return v6->para > 0;
}

// 0x1ee28b0
s32 sBtlGetMagCost(sdatUnitWork_t *player, sdatUnitWork_t *unit, s32 devilid) {
  return 0;
}

// 0x1ee28c0
bool sBtlCheckUseSkill(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 use_skillid;
  bool v10;
  bool result;
  sdatUnitWork_t *para;

  Skilltbl = sBtlGetSkilltbl(sklid);
  use_skillid = wk->actwk->use_skillid;
  v10 = sBtlCheckCost2(wk, use_skillid, 0);
  result = 0;
  if (!v10)
    return result;
  if ((Skilltbl->type & 0xFFF) != 3)
    return 1;
  para = wk->para;
  return sBtlGetBadStatus(para) != 10;
}

// 0x1ee2a90
bool sBtlCheckMagCost_GB(sdatUnitWork_t *player, sdatUnitWork_t *unit, s32 devilid, s8 flg) {
  return 1;
}

// 0x1ee2aa0
bool sBtlCheckMagCost(sdatUnitWork_t *unit, s32 devilid, s8 flg) {
  return 1;
}

// 0x1ee2ab0
bool sBtlCheckCost2(SBTLUNIT_WORK *wk, SKLID sklid, s32 flg) {
  SBTLAI_WORK *aiwk;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v9;

  if ((wk->side & 2) != 0)
    return 1;
  aiwk = wk->aiwk;
  if (aiwk->cmndFrm)
  {
    Skilltbl = sBtlGetSkilltbl(aiwk->cmndSkl);
    if ((Skilltbl->flg2 & 1) != 0 && wk->actwk->use_skillid == Skilltbl->badst)
      return 1;
  }
  if ((wk->status & 0x100000) != 0)
    return 1;
  v9 = sBtlGetSkilltbl(wk->actwk->use_skillid);
  if ((v9->type & 0x1000) != 0)
    return 1;
  if ((v9->flg2 & 2) != 0)
    sklid = v9->badst;
  return sBtlCheckCost_SkillID(wk, sklid, flg);
}

// 0x1ee2a10
bool sBtlCheckCost(SBTLUNIT_WORK *wk, s32 flg) {
  s32 use_skillid;

  use_skillid = wk->actwk->use_skillid;
  return sBtlCheckCost2(wk, use_skillid, flg);
}

// 0x1ee2ba0
bool sBtlCheckCost_SkillID(SBTLUNIT_WORK *wk, SKLID skillid, s32 flg) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v9;
  u16 v10;
  s32 v11;
  u16 s_type;
  u32 v13;
  s32 v14;
  _BOOL4 v15;
  u32 v16;
  s32 side;
  SBTLUNIT_WORK *Nakama;
  s32 para;
  s32 vice;
  sdatUnitWork_t *v24;
  s32 SkillCost;
  SBATTLE_WORK *v28;
  s32 v29;
  s32 mag;
  s64 v32;
  char *v33;
  SKLID *spiritSkill;
  s32 v35;
  s32 hp;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v40;
  sdatParaWork_t *now;
  s32 mp;

  Skilltbl = sBtlGetSkilltbl(skillid);
  v9 = Skilltbl;
  if ((u32)(flg - 1) > 1)
  {
    s_type = Skilltbl->s_type;
    if ((s_type & 1) != 0)
      goto LABEL_52;
    if ((s_type & 2) == 0)
    {
      if ((s_type & 4) == 0)
      {
        if ((s_type & 0x10) == 0)
        {
          if ((s_type & 0x20) == 0)
            goto LABEL_108;
          if ((wk->side & 1) != 0)
            goto LABEL_52;
LABEL_40:
          side = wk->side;
          if ((side & 2) == 0)
          {
            if ((side & 0x80) != 0)
            {
              if (wk->member_num < 1)
                goto LABEL_77;
              Nakama = sBtlGetNakama(0);
              wk = Nakama;
              if (!Nakama)
                return (char)Nakama;
            }
            para = v9->para;
            vice = wk->para->vice;
            LOBYTE(Nakama) = vice >= para;
            if (flg != 1 || vice < para)
              return (char)Nakama;
            sBtlDecVice(wk, para);
          }
LABEL_108:
          LOBYTE(Nakama) = 1;
          return (char)Nakama;
        }
        if ((wk->side & 1) != 0)
          goto LABEL_52;
LABEL_103:
        v40 = v9->para;
        now = wk->para->now;
        mp = now->mp;
        LOBYTE(Nakama) = mp >= v40;
        if (flg != 1 || mp < v40)
          return (char)Nakama;
        now = wk->para->now;
        mp = now->mp;
        now->mp = mp - v40;
        goto LABEL_108;
      }
LABEL_90:
      v37 = v9->para;
      v38 = *(u32 *)(**(u64 **)&Nakama->rot.y + 912);
      LOBYTE(Nakama) = v38 >= v37;
      if (flg != 1 || v38 < v37)
        return (char)Nakama;
      goto LABEL_108;
    }
LABEL_79:
    v35 = v9->para;
    hp = wk->para->now->hp;
    LOBYTE(Nakama) = hp >= v35;
    if (flg != 1 || hp < v35)
      return (char)Nakama;
    sBtlDecHP(wk, v35);
    goto LABEL_108;
  }
  if (skillid != 149)
  {
    v13 = 0;
    while (1)
    {
      if (((v9->s_type >> v13) & 1) != 0)
      {
        v14 = wk->side;
        v15 = (v13 & 0x7FFFFFFE) == 4;
        if (sBtlGetNakama(0) == wk)
        {
          wk->aAiGgFlsAlpha[0] = 255;
          if (sBtlGetNakama(1) == wk)
          {
LABEL_34:
            wk->aAiGgFlsAlpha[1] = 255;
            if ((v15 & v14) != 0)
              v16 = 0;
            else
              v16 = v13;
LABEL_39:
            switch (v16)
            {
              case 0u:
                goto LABEL_52;
              case 1u:
                goto LABEL_79;
              case 2u:
                goto LABEL_90;
              case 4u:
                goto LABEL_103;
              case 5u:
                goto LABEL_40;
              default:
                goto LABEL_22;
            }
          }
        }
        else if (sBtlGetNakama(1) == wk)
        {
          goto LABEL_34;
        }
        if ((v15 & v14) != 0)
          v16 = 0;
        else
          v16 = v13;
        if (v16 <= 5)
          goto LABEL_39;
      }
LABEL_22:
      if (++v13 == 6)
        goto LABEL_108;
    }
  }
  v10 = Skilltbl->s_type;
  if ((v10 & 1) != 0)
  {
    sBtlGetNakama(0);
    sBtlGetNakama(1);
    goto LABEL_52;
  }
  if ((v10 & 2) != 0)
  {
    sBtlGetNakama(0);
    sBtlGetNakama(1);
    goto LABEL_79;
  }
  if ((v10 & 4) != 0)
  {
    sBtlGetNakama(0);
    sBtlGetNakama(1);
    goto LABEL_90;
  }
  if ((v10 & 8) != 0)
  {
    sBtlGetNakama(0);
    sBtlGetNakama(1);
    v10 = v9->s_type;
  }
  if ((v10 & 0x10) != 0)
  {
    v39 = wk->side;
    sBtlGetNakama(0);
    sBtlGetNakama(1);
    if ((v39 & 1) != 0)
      goto LABEL_52;
    goto LABEL_103;
  }
  if ((v10 & 0x20) == 0)
    goto LABEL_108;
  v11 = wk->side;
  sBtlGetNakama(0);
  sBtlGetNakama(1);
  if ((v11 & 1) == 0)
    goto LABEL_40;
LABEL_52:
  v24 = wk->para;
  SkillCost = sBtlGetSkillCost(v24, skillid);
  v28 = wk;
  v29 = SkillCost << ((v28->status3 & 0x2000000) != 0);
  mag = v28->mag;
  if (mag < v29)
    goto LABEL_57;
  goto LABEL_65;
  if (mag >= v29)
  {
LABEL_65:
    if ((u32)(flg - 1) <= 1)
    {
      v32 = 0;
      while (1)
      {
        spiritSkill = GBWK->player->spiritSkill;
        if (v32 >= SLODWORD(spiritSkill->max_length))
          break;
        spiritSkill = GBWK->player->spiritSkill;
        v33 = (char *)spiritSkill + 4 * v32++;
        if (*((u32 *)v33 + 8) == 1448)
        {
          if (GetRand(0x64u) <= 0x1Eu)
            v29 = 0;
          break;
        }
      }
      sBtlDecMag(v29);
    }
    goto LABEL_108;
  }
LABEL_57:
  if (flg != 2)
  {
LABEL_77:
    LOBYTE(Nakama) = 0;
    return (char)Nakama;
  }
  mag = wk->mag;
  sBtlDecMag(mag);
  LOBYTE(Nakama) = 0;
  return (char)Nakama;
}

// 0x1ee3210
void sBtlDecVice(SBTLUNIT_WORK *wk, s32 vice) {
  SBTLEXP_LISTWORK *expList;

  expList = wk->expList;
  DecVice(expList, vice);
  wk->para->vice -= vice;
}

// 0x1ee3300
void sBtlDecMag(s32 mag) {
  SBATTLE_WORK *wk_local;
  u32 status3;
  s32 v6;
  s32 *p_mag;
  s32 magMax;

  wk_local = wk;
  if (wk_local->enemy_zenmetu)
    return;
  status3 = wk_local->status3;
  v6 = mag << ((status3 & 0x2000000) != 0);
  p_mag = &wk_local->mag;
  wk_local->mag -= v6;
  magMax = wk_local->magMax;
  LimitRange(p_mag, 0, magMax);
  wk->magUpCnt = 0;
}

// 0x1ee3570
s32 sBtlPerDecMag(s32 per) {
  SBATTLE_WORK *wk_local;
  s32 v6;
  s32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  u32 v11;
  s32 magMax;
  u32 v15;

  wk_local = wk;
  v6 = per << ((wk_local->status3 & 0x2000000) != 0);
  v7 = wk_local->magMax * v6;
  if (v7 < 100)
    v8 = -1;
  else
    v8 = v7 / -100;
  goto LABEL_13;
  if (v10 < 100)
  {
    v8 = -1;
    if (!v9)
      goto LABEL_17;
LABEL_13:
    v11 = wk_local->mag + v8;
    wk_local->mag = v11;
    goto LABEL_14;
  }
  v8 = v10 / -100;
  if (v9)
    goto LABEL_13;
LABEL_17:
  wk_local = wk;
  v11 = wk_local->mag + v8;
  wk_local->mag = v11;
  if (!v15)
  {
    wk_local = wk;
  }
LABEL_14:
  magMax = wk_local->magMax;
  LimitRange(&wk_local->mag, 0, magMax);
  wk->magUpCnt = 0;
  return v11 >> 31;
}

// 0x1ee3710
void sBtlAddMag(s32 mag) {
  SBATTLE_WORK *wk_local;
  s32 *p_mag;
  s32 v8;
  s32 magMax;

  wk_local = wk;
  p_mag = &wk_local->mag;
  v8 = wk_local->mag + mag;
  magMax = wk_local->magMax;
  wk_local->mag = v8;
  LimitRange(p_mag, 0, magMax);
}

// 0x1ee3440
void sBtlDecHP(SBTLUNIT_WORK *wk, s32 para) {
  sBtlDecHp(wk, para, 0);
}

// 0x1ee34b0
void sBtlDecMP(SBTLUNIT_WORK *wk, s32 para) {
  wk->para->now->mp -= para;
}

// 0x1edd210
void sBtlDecItem_GBWK(s32 itemid) {
  s64 v4;
  sdatPlayerUnitWork_t *player;
  SortSave *sortSave;
  s64 v8;
  u16 *v9;
  s32 v10;

  v4 = itemid;
  player = GBWK->player;
  sortSave = GBWK->sortSave;
  --player->item[v4];
  UpdateGetList(sortSave, itemid, -1, 0);
  v8 = (s64)player->item + v4 * 2;
  v10 = *(s16 *)(v8 + 32);
  v9 = (v8 + 32);
  if (v10 <= 0)
    *v9 = 0;
}

// 0x1edd4a0
void sBtlDecItem(s32 index, s32 itemid) {
  s64 v5;

  v5 = (s64)wk->itemList->data + 8 * index;
  --*(u32 *)(*(u64 *)(v5 + 32) + 20);
}

// 0x1ee37c0
void sBtlSetGunNum(s32 para) {
  sBtlGetPlayerData();
  wk->hgun_num = para;
}

// 0x1ee3560
void sBtlDecGunNum(s32 para) {
  ;
}

// 0x1ee34d0
s32 sBtlGetGun_Num(void) {
  return wk->hgun_num;
}

// 0x1ee3840
SBTLAISYO_DATAWORK *sBtlGetAisyotbl(s32 id) {
  return aisyo_tbldata[id];
}

// 0x1ee38b0
bool sBtlCheckAttrFlg(s32 id, u32 attr, u32 attrnum) {
  return (aisyo_tbldata[id]->para[attrnum] & attr) != 0;
}

// 0x1edae60
s32 sBtlGetAttr(u32 attr) {
  if ((attr & 1) != 0)
    return 0;
  if ((attr & 2) != 0)
    return 1;
  if ((attr & 4) != 0)
    return 2;
  if ((attr & 8) != 0)
    return 3;
  if ((attr & 0x10) != 0)
    return 4;
  if ((attr & 0x20) != 0)
    return 5;
  if ((attr & 0x40) != 0)
    return 6;
  if ((attr & 0x80) != 0)
    return 7;
  if ((attr & 0x100) != 0)
    return 8;
  if ((attr & 0x200) != 0)
    return 9;
  if ((attr & 0x400) != 0)
    return 10;
  if ((attr & 0x800) != 0)
    return 11;
  if ((attr & 0x1000) != 0)
    return 12;
  if ((attr & 0x2000) != 0)
    return 13;
  if ((attr & 0x4000) != 0)
    return 14;
  if ((attr & 0x8000) != 0)
    return 15;
  return -1;
}

// 0x1ee3950
u32 sBtlCheckAisyo_Old(SBTLAISYO_DATAWORK *aisyo_tbl, u32 attr) {
  s64 v4;
  u32 result;
  s32 v6;

  v4 = 0;
  result = 0;
  while (((attr >> v4) & 1) == 0)
  {
LABEL_2:
    if (++v4 == 16)
      return result;
  }
  v6 = aisyo_tbl->para[v4];
  if ((v6 & 0x10000) != 0)
    return 0x10000;
  if ((v6 & 0x2000) != 0)
    return 0x2000;
  if ((v6 & 0x1000) != 0)
    return 4096;
  if ((v6 & 0x80000) == 0)
  {
    result |= v6 & 0x6C000;
    goto LABEL_2;
  }
  return 0x80000;
}

// 0x1ed5590
u32 sBtlCheckAisyoEx(SBTLUNIT_WORK *a_pUnit, u32 a_SkillAttr, s32 *a_pHanshaType) {
  SBTLAISYO_DATAWORK *aisyo;
  s64 v8;
  u32 v9;
  s32 v10;
  void *wkBarrier;
  s32 v12;
  s32 monitor_high;

  aisyo = a_pUnit->para->aisyo;
  v8 = 0;
  v9 = 0;
  while (((a_SkillAttr >> v8) & 1) == 0)
  {
LABEL_6:
    if (++v8 == 16)
      goto LABEL_18;
  }
  v10 = aisyo->para[v8];
  if ((v10 & 0x10000) != 0)
  {
    v9 = 0x10000;
    if (!*a_pHanshaType)
      goto LABEL_20;
    goto LABEL_19;
  }
  if ((v10 & 0x2000) != 0)
  {
    v9 = 0x2000;
    if (!*a_pHanshaType)
      goto LABEL_20;
    goto LABEL_19;
  }
  if ((v10 & 0x1000) != 0)
  {
    v9 = 4096;
LABEL_18:
    if (!*a_pHanshaType)
      goto LABEL_20;
    goto LABEL_19;
  }
  if ((v10 & 0x80000) == 0)
  {
    v9 |= v10 & 0x6C000;
    goto LABEL_6;
  }
  v9 = 0x80000;
  if (*a_pHanshaType)
LABEL_19:
    *a_pHanshaType = 0;
LABEL_20:
  if ((a_SkillAttr & 0x401) != 0 && a_pUnit->wkKarn[0]->m_cnt && (a_pUnit->hstatus & 0x10) == 0)
  {
    v9 = 4096;
    *a_pHanshaType = 2;
  }
  else
  {
    wkBarrier = a_pUnit->wkBarrier;
    if (wkBarrier->_size >= 1)
    {
      v12 = 0;
      do
      {
        if (LODWORD(_get_Item(wkBarrier, v12)[1].klass))
        {
          if (LODWORD(_get_Item(a_pUnit->wkBarrier, v12)[1].klass) == 773 && *a_pHanshaType)
          {
            *a_pHanshaType = 1;
          }
          if (LODWORD(_get_Item(a_pUnit->wkBarrier, v12)[1].klass) == 774)
          {
            if (*a_pHanshaType)
              *a_pHanshaType = 2;
            v9 = 4096;
          }
          a_SkillAttr |= (a_SkillAttr >> 10) & 1;
          if (((s64)_get_Item(a_pUnit->wkBarrier, v12)[1].monitor & a_SkillAttr) != 0)
          {
            if (*a_pHanshaType)
              *a_pHanshaType = 3;
            monitor_high = HIDWORD(_get_Item(a_pUnit->wkBarrier, v12)[1].monitor);
            switch (monitor_high)
            {
              case 0x80000:
                if (v9 != 4096 && v9 != 0x2000)
                  v9 = 0x80000;
                break;
              case 0x2000:
                v9 = 0x2000;
                break;
              case 0x1000:
                if (v9 == 0x2000)
                  v9 = 0x2000;
                else
                  v9 = 4096;
                break;
            }
          }
        }
        wkBarrier = a_pUnit->wkBarrier;
        ++v12;
      }
      while (v12 < wkBarrier->_size);
    }
  }
  return v9;
}

// 0x1ee39d0
bool sBtlGetParameter_Rsc(SBTLUNIT_WORK *wk, sdatParaWork_t *para) {
  Clone(wk->para->backup, 0);
  return 1;
}

// 0x1ed6bc0
s32 sBtlCheckRecoverData(sdatUnitWork_t *unit, s32 para, s32 flg, bool revival) {
  sdatParaWork_t *now;
  s64 v6;
  s64 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;

  now = unit->now;
  v6 = 24;
  v7 = 28;
  if (!flg)
  {
    v6 = 16;
    v7 = 20;
  }
  v8 = *(u32 *)((char *)&now->klass + v6);
  v9 = *(u32 *)((char *)&now->klass + v7);
  v10 = v8 + para;
  v11 = v9 - v8;
  if (v8 < 1 && revival)
    v12 = v9;
  else
    v12 = para;
  if (v10 <= v9)
    return v12;
  else
    return v11;
}

// 0x1ee3a00
s32 sBtlCheckKuishibari(SBTLUNIT_WORK *wk, s32 para) {
  SBATTLE_WORK *v6;
  s64 v7;
  s32 scrFlag;
  s32 hp;
  void *v10;
  s32 klass_high;
  s32 i;
  Il2CppClass **v13;
  KuishibariSkl *v15;
  sdatUnitWork_t *v17;
  s32 AutoSkill_ID;
  s32 side;
  s32 autost_cnt2;
  s64 size;
  u64 *v24;
  void *items;
  s32 v26;
  void *_9__128_0;
  Il2CppObject *v30;
  void *v32;
  sdatUnitWork_t *v36;
  s16 *p_autost_cnt;
  s16 *p_autost_cnt2;
  s32 v39;
  void *_9__128_1;
  Il2CppObject *v43;
  void *v45;
  void *v46;
  sdatUnitWork_t *v47;
  s32 v48;
  s32 v49;
  u32 BadStatus;
  sdatUnitWork_t *v51;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v54;
  SBTLSM_LISTWORK *v56;
  char v58;
  _BOOL8 v59;
  SBATTLE_WORK *v61;
  s16 *summonindex;
  s32 ListID;
  s32 v64;
  u32 *p_kuishibBit;
  s32 v67;
  SBTLSM_LISTWORK *v69;
  SBTLSM_LISTWORK *v70;
  SBTLSM_LISTWORK *v71;
  s32 v72;
  s32 v73;
  u32 v78;
  bool v80;
  u32 status;
  SBATTLE_WORK *v83;
  s16 *v84;
  s32 v85;
  _BOOL8 v86;
  s32 v87;
  u32 *v88;
  sdatParaWork_t *now;
  s64 v90;
  s32 v91;
  s64 v93;
  s32 v94;
  s32 klass;

  v6 = wk;
  v7 = (u16)v6->summonindex[0];
  if (wk->ListID != v6->playerID)
    goto LABEL_14;
  scrFlag = v6->scrFlag;
  if ((scrFlag & 0x20) == 0)
    goto LABEL_14;
  hp = wk->para->now->hp;
  if (hp - para <= 0)
  {
    para = hp - 1;
    v6 = wk;
    scrFlag = v6->scrFlag;
    v6->scrFlag = scrFlag | 0x10;
  }
LABEL_14:
  if ((wk->status & 0x20000000) == 0)
    return para;
  v94 = para;
  v93 = v7;
  v10 = Allocate(System_Collections_Generic_List_KuishibariSkl_);
  __ctor(v10);
  klass = 0;
  klass_high = 0;
  for (i = 0; i != 8; ++i)
  {
    v15 = Allocate(KuishibariSkl);
    _ctor(v15, 0);
    v17 = wk->para;
    AutoSkill_ID = sBtlGetAutoSkill_ID(v17, i);
    if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
    {
      side = wk->side;
      if ((side & 0x80) != 0)
      {
        if (sBtlCheckKuisibari(AutoSkill_ID))
          continue;
        side = wk->side;
      }
      if ((side & 0x81) != 1)
      {
LABEL_37:
        autost_cnt2 = wk->para->autost_cnt2;
        if (klass >= autost_cnt2)
        {
          if (!klass_high)
          {
            klass_high = AutoSkill_ID;
            v15->hp = 0;
            v15->skl = AutoSkill_ID;
          }
        }
        else
        {
          v15->hp = autost_cnt2;
          v15->skl = AutoSkill_ID;
          size = v10->_size;
          v24 = Method_System_Collections_Generic_List_KuishibariSkl__Add__;
          ++v10->_version;
          items = v10->_items;
          if ((u32)size < LODWORD(items->max_length))
          {
            v13 = &items->obj.klass + size;
            v10->_size = size + 1;
            v13[4] = v15;
          }
          else
          {
            _AddWithResize(v10, v15, *(const MethodInfo_2DFC660 **)(*(u64 *)(v24[4] + 192) + 112));
          }
          klass = autost_cnt2;
          klass_high = AutoSkill_ID;
        }
        continue;
      }
      if ((((u32)wk->kuisibariFlag >> sBtlGetkuisibariBit(AutoSkill_ID)) & 1) != 0)
        continue;
      goto LABEL_37;
    }
  }
  if ((wk->side & 0x80) == 0)
  {
    para = v94;
    goto LABEL_68;
  }
  v26 = v10->_size;
  if (v26 >= 2)
  {
    para = v94;
    _9__128_0 = __9__128_0;
    if (!_9__128_0)
    {
      v30 = __9;
      _9__128_0 = Allocate(System_Func_KuishibariSkl__int_);
      int____ctor(_9__128_0, v30, Method_Project_sBtlCalc___c__CheckKuishibari_b__128_0__, 0);
      __9__128_0 = _9__128_0;
    }
    v32 = OrderBy_object__int_(v10, _9__128_0);
    v10 = Allocate(System_Collections_Generic_List_KuishibariSkl_);
    __ctor_48217552(v10, v32);
    klass = _get_Item(v10, 0)[1].klass;
    klass_high = HIDWORD(_get_Item(v10, 0)[1].klass);
    if (v10->_size)
      goto LABEL_68;
LABEL_54:
    if (!GBWK->player->seikatu)
      goto LABEL_68;
    if (!sBtlSeikatuUseChk())
      goto LABEL_68;
    v36 = wk->para;
    p_autost_cnt = &v36->autost_cnt;
    p_autost_cnt2 = &v36->autost_cnt2;
    klass_high = 375;
    sBtlGetAutoSkillPara(375, p_autost_cnt, p_autost_cnt2);
    v39 = 1;
    klass = wk->para->autost_cnt2;
    goto LABEL_69;
  }
  para = v94;
  if (!v26)
    goto LABEL_54;
LABEL_68:
  v39 = 0;
LABEL_69:
  if ((wk->side & 0x81) == 1 && v10->_size >= 2)
  {
    _9__128_1 = __9__128_1;
    if (!_9__128_1)
    {
      v43 = __9;
      _9__128_1 = Allocate(System_Func_KuishibariSkl__int_);
      int____ctor(_9__128_1, v43, Method_Project_sBtlCalc___c__CheckKuishibari_b__128_1__, 0);
      __9__128_1 = _9__128_1;
    }
    v45 = OrderBy_object__int_(v10, _9__128_1);
    v46 = Allocate(System_Collections_Generic_List_KuishibariSkl_);
    __ctor_48217552(v46, v45);
    klass = _get_Item(v46, 0)[1].klass;
    klass_high = HIDWORD(_get_Item(v46, 0)[1].klass);
  }
  v47 = wk->para;
  v48 = v47->now->hp;
  v49 = v48 - para;
  if (!klass_high)
  {
    v67 = v48 - 1;
    if (v49 < 1)
      return v67;
    return para;
  }
  if (para != -1 && v49 > 0)
    return para;
  BadStatus = sBtlGetBadStatus(v47);
  if (BadStatus <= 0x13 && ((1 << BadStatus) & 0xAC000) != 0)
  {
    v51 = wk->para;
    if (!v51 || (v51->koufunst & 0x20) == 0)
      return para;
  }
  sysmsgList = wk->sysmsgList;
  if (sysmsgList->bLock)
  {
    sysmsgList = wk->sysmsgList;
    sysmsgList->bLock = 0;
  }
  v54 = wk->side;
  if ((v54 & 0x80) != 0)
  {
    if (v39)
    {
      v69 = wk->sysmsgList;
      sBtlCreateSM(v69, wk, 11, klass_high, 0, 120);
      datAddItem(9, -1);
    }
    else
    {
      v71 = wk->sysmsgList;
      sBtlCreateSM(v71, wk, 185, klass_high, 0, 120);
    }
    wk->actwk->order_stockID = -1;
    sBtlSetKuisibari(klass_high);
  }
  else
  {
    if ((v54 & 2) != 0)
    {
      v70 = wk->sysmsgList;
      sBtlCreateSM(v70, wk, 187, klass_high, 0, 120);
    }
    else
    {
      v56 = wk->sysmsgList;
      sBtlCreateSM(v56, wk, 186, klass_high, 0, 120);
      v58 = sBtlGetkuisibariBit(klass_high);
      v59 = 1;
      wk->kuisibariFlag |= 1 << v58;
      v61 = wk;
      summonindex = v61->summonindex;
      if ((v93 & 0x8000) == 0)
      {
        ListID = wk->ListID;
        v61 = wk;
        v59 = ListID != v61->summonID[v93];
      }
      v64 = summonindex[v59];
      p_kuishibBit = &wk->kuishibBit;
      sBtlSetBit(p_kuishibBit, v64);
    }
  }
  if (klass_high == 1074 || klass_high == 828)
  {
    v72 = wk->ListID;
    v73 = 112;
    goto LABEL_141;
  }
  if (((klass_high != 1084) & ~v39) == 0)
  {
    v72 = wk->ListID;
    v73 = 114;
LABEL_141:
    sBtlSetTargetID(wk, v72);
    sBtlSetSkill_EffectData(wk, v73, 0);
  }
  wk->status &= ~0x20000000u;
  if (!!sBtlKuisibariChk(wk))
  {
    v78 = wk->status | 0x20000000;
    goto LABEL_159;
  }
  v80 = sBtlNakamaKuisibariChk(wk);
  status = wk->status;
  if (!v80)
  {
    v78 = status & 0xDFFFFFFF;
LABEL_159:
    wk->status = v78;
    goto LABEL_169;
  }
  wk->status = status | 0x20000000;
  v83 = wk;
  v84 = v83->summonindex;
  if ((v93 & 0x8000) != 0)
  {
    v86 = 1;
  }
  else
  {
    v85 = wk->ListID;
    v83 = wk;
    v86 = v85 != v83->summonID[v93];
  }
  v87 = v84[v86];
  v88 = &wk->kuishibBit;
  sBtlResetBit(v88, v87);
LABEL_169:
  wk->hstatus |= 0x40u;
  wk->damagecnt = 180;
  now = wk->para->now;
  para = now->hp - 1;
  if (klass)
  {
    v90 = 1374389535 * now->maxhp * klass;
    v91 = (v90 >> 37) + ((u64)v90 >> 63);
    now->hp = v91;
    sBtlCreateAnim_Unit(wk, 0, v91 - 1, 12, 3, 0);
    sBtlCreateAnim_Unit(wk, 0, para, 0, 0, 0);
    para = 0;
  }
  if (BadStatus <= 0xD && ((1 << BadStatus) & 0x205F) != 0)
  {
    sBtlResetBadStatus(wk, 1 << BadStatus);
  }
  return para;
}

// 0x1ee4980
bool sBtlKuisibariBstChk(BST bstno) {
  return (bstno > 0x13) | (0x53FFFu >> bstno) & 1;
}

// 0x1ee1670
bool sBtlKuisibariChk(SBTLUNIT_WORK *_wk) {
  s32 v4;
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;
  sdatUnitWork_t *v10;
  s32 v11;
  sdatUnitWork_t *v14;
  s32 v15;
  sdatUnitWork_t *v18;
  s32 v19;
  sdatUnitWork_t *v22;
  s32 v23;
  sdatUnitWork_t *v26;
  s32 v27;
  sdatUnitWork_t *v30;
  s32 v31;
  sdatUnitWork_t *v34;
  s32 v35;

  if ((wk->side & 0x80) == 0)
    goto LABEL_4;
  para = wk->para;
  AutoSkill_ID = sBtlGetAutoSkill_ID(para, 0);
  v4 = 0;
  if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    v4 = !sBtlCheckKuisibari(AutoSkill_ID);
  }
  v10 = wk->para;
  v11 = sBtlGetAutoSkill_ID(v10, 1);
  if (sBtlGetAutoSkillPara(v11, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    v4 |= !sBtlCheckKuisibari(v11);
  }
  v14 = wk->para;
  v15 = sBtlGetAutoSkill_ID(v14, 2);
  if (sBtlGetAutoSkillPara(v15, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    v4 |= !sBtlCheckKuisibari(v15);
  }
  v18 = wk->para;
  v19 = sBtlGetAutoSkill_ID(v18, 3);
  if (sBtlGetAutoSkillPara(v19, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    v4 |= !sBtlCheckKuisibari(v19);
  }
  v22 = wk->para;
  v23 = sBtlGetAutoSkill_ID(v22, 4);
  if (sBtlGetAutoSkillPara(v23, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    v4 |= !sBtlCheckKuisibari(v23);
  }
  v26 = wk->para;
  v27 = sBtlGetAutoSkill_ID(v26, 5);
  if (sBtlGetAutoSkillPara(v27, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    v4 |= !sBtlCheckKuisibari(v27);
  }
  v30 = wk->para;
  v31 = sBtlGetAutoSkill_ID(v30, 6);
  if (sBtlGetAutoSkillPara(v31, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    v4 |= !sBtlCheckKuisibari(v31);
  }
  v34 = wk->para;
  v35 = sBtlGetAutoSkill_ID(v34, 7);
  if (sBtlGetAutoSkillPara(v35, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
  {
    LOBYTE(v4) = !sBtlCheckKuisibari(v35) | v4;
  }
  if ((wk->side & 0x80) == 0 || (v4 & 1) != 0)
    return v4 & 1;
  if (!GBWK->player->seikatu)
    goto LABEL_4;
  goto LABEL_64;
  if (!GBWK->player->seikatu)
  {
LABEL_4:
    LOBYTE(v4) = 0;
    return v4 & 1;
  }
LABEL_64:
  return sBtlSeikatuUseChk();
}

// 0x1ee4a20
bool sBtlNakamaKuisibariChk(SBTLUNIT_WORK *_wk) {
  char v4;
  s32 v5;
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;

  if ((wk->side & 0x81) == 1)
  {
    v4 = 0;
    v5 = 0;
    while (1)
    {
      para = wk->para;
      AutoSkill_ID = sBtlGetAutoSkill_ID(para, v5);
      if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 5)
        v4 |= (((u32)wk->kuisibariFlag >> sBtlGetkuisibariBit(AutoSkill_ID)) & 1) == 0;
      if (++v5 == 8)
        return v4 & 1;
    }
  }
  v4 = 0;
  return v4 & 1;
}

// 0x1ee4820
bool sBtlCheckNakamaKuisibari(SBTLUNIT_WORK *_wk, SKLID _sklID) {
  _BOOL4 v5;

  if (wk)
  {
    return ((u32)wk->kuisibariFlag >> sBtlGetkuisibariBit(sklID)) & 1;
  }
  else
  {
    LOBYTE(v5) = 0;
  }
  return v5;
}

// 0x1ee49a0
void sBtlSetNakamaKuisibari(SBTLUNIT_WORK *_wk, SKLID _sklID) {
  wk->kuisibariFlag |= 1 << sBtlGetkuisibariBit(sklID);
}

// 0x1ee48b0
bool sBtlSeikatuChk(void) {
  if (!GBWK->player->seikatu)
    return 0;
  return sBtlSeikatuUseChk();
}

// 0x1ee4b70
bool sBtlSeikatuUseChk(void) {
  s32 ConfigGAME;

  ConfigGAME = cfgGetConfigGAME(1, 0);
  if (datGetItemNum(9) < 1)
    return 0;
  return DlcItemGetCheck(9) && ConfigGAME != 0;
}

// 0x1ee4c70
bool sBtlCheckSpecialDamage_Stop(SBTLUNIT_WORK *wk) {
  s32 devilid;

  if ((wk->status & 0x2000000) != 0)
    return 1;
  if (IsSceanStop())
    return 1;
  devilid = (u16)wk->para->devilid;
  return (devilid == 302 || devilid == 263) && wk->actwk->status == 7;
}

// 0x1ee4da0
bool CalcBtlMagicStatus(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  s32 v5;
  bool v6;
  s32 rejyenecounter;
  bool v8;
  s32 v9;
  s32 v10;
  s32 rejyenecmpcnt;
  s32 rejyenepara;
  sdatUnitWork_t *v14;
  sdatParaWork_t *now;
  s32 hp;
  s32 v17;
  s32 v18;
  s32 v20;
  sdatParaWork_t *v21;
  s32 v23;
  s32 maxhp;
  s32 *p_hp;
  s32 v26;
  SBTLUNIT_WORK *v27;
  s32 rejyenehelper;
  SBTLUNIT_LISTWORK *v30;
  SBTLUNIT_WORK *v31;
  f32 v33;
  f32 v34;
  SBTLEFF_LISTWORK *effList;
  f32 v36;
  f32 v37;
  void *wkBarrier;
  s32 v39;
  Il2CppObject *Item;
  const MethodInfo_2DFC320 *v41;
  SBTLSM_LISTWORK *sysmsgList;
  s32 klass;
  s32 enchantcnt;
  s32 v47;
  SBATTLE_WORK *v49;
  s32 sword_eff_skl;
  SBTLSM_LISTWORK *v51;
  s32 bulletcnt;
  s32 v53;
  s32 bulletskl;
  SBTLSM_LISTWORK *v56;
  tagSBTLSKL_AURA_WORK *wkAura;
  tagSBTLSKL_AURA_WORK *v58;
  s32 auracnt;
  s32 v60;
  s32 auraskl;
  SBTLSM_LISTWORK *v64;
  s32 v65;
  sdatUnitWork_t *v66;
  s32 v67;
  s32 v68;
  s32 side;
  s32 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v74;
  f32 hit_area_r;
  f32 z;
  f32 w;
  f32 r2;
  f32 v83;
  tagSBTLSKL_AURA_WORK *v85;
  s32 v86;
  s32 v87;
  s32 v88;
  u32 v90;
  SBTLSM_LISTWORK *v91;
  s32 v92;
  tagSBTLSKL_AURA_WORK *v93;
  s32 v94;
  s32 v95;
  s32 v96;
  u32 v98;
  SBTLSM_LISTWORK *v99;
  s32 v100;
  f32 moveSpdMul;
  f32 v102;
  f32 v103;
  f32 v104;
  s32 slipcounter;
  s32 v109;
  s32 v110;
  s32 slipcmpcnt;
  s32 slippara;
  s32 v114;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v116;
  SBTLUNIT_WORK *v117;
  u32 attr;
  SBTLEFF_LISTWORK *v121;
  SBTLEFF_LISTWORK *v123;
  s32 tdancounter;
  s32 v127;
  s32 v128;
  s32 tdancmpcnt;
  s32 tdanhitcnt;
  s32 tdanpara;
  s32 v133;
  SBTLSKILLP_TBL *v134;
  u32 v135;
  SBTLSKILLP_TBL *v136;
  u32 v138;
  u32 v140;
  s32 tdan_acterid;
  s32 tdan_sklid;
  s32 v143;
  s32 v144;
  s64 v146;
  char *v147;
  SKLID *spiritSkill;
  s32 hitsliphelper;
  SBTLUNIT_LISTWORK *v151;
  SBTLUNIT_WORK *v152;
  f32 v154;
  f32 v155;
  SBTLEFF_LISTWORK *v156;
  f32 v157;
  f32 v158;
  f32 v160;
  f32 v161;
  SBTLEFF_LISTWORK *v162;
  f32 v163;
  f32 v164;
  f32 v166;
  f32 v167;
  SBTLEFF_LISTWORK *v168;
  f32 v169;
  f32 v170;
  f32 v172;
  f32 v173;
  SBTLEFF_LISTWORK *v174;
  f32 v175;
  f32 v176;
  f32 v179;
  f32 v180;
  f32 v181;
  f32 v182;
  f32 v183;
  f32 y;
  f32 x;
  s32 a_pHanshaType;
  sdfVector4_t v187;
  sdfVector4_t v188;
  sdfVector4_t pos;
  sdfVector4_t v190;
  sdfVector4_t v191;
  sdfVector4_t v192;
  sdfVector4_t v193;
  sdfVector4_t v194;

  a_pHanshaType = 0;
  if (!wk->bBfrBtlEnd)
    goto LABEL_12;
  para = wk->para;
  if (sBtlChkHaveMemSkl(para, 3))
  {
    v5 = wk->autoreccnt + 1;
    v6 = wk->autoreccnt - 179 < 0;
    wk->autoreccnt = v5;
    if (v6 == __OFSUB__(v5, 180))
    {
      v66 = wk->para;
      wk->autoreccnt = 0;
      v67 = v66->now->maxhp * v66->autost_cnt2;
      if (v67 < 100)
        v68 = 1;
      else
        v68 = v67 / 100;
      side = wk->side;
      for (i = 0; ; ++i)
      {
        UnitMng = wk->UnitMng;
        if (i >= UnitMng->number)
          break;
        v74 = sBtlSearchUnit_ID(UnitMng, i);
        if (sBtlCheckDamageTarget(v74))
        {
          if (v74 == wk)
            goto LABEL_274;
          if (((v74->side ^ side) & 3) == 0)
          {
            hit_area_r = wk->actaiwk->hit_area_r;
            pos = wk->pos;
            v194.x = wk->rot.x;
            v194.y = wk->rot.y;
            z = wk->rot.z;
            w = wk->rot.w;
            r2 = v74->pos.x;
            v83 = v74->pos.z;
            y = wk->pos.y;
            x = wk->pos.x;
            v182 = wk->pos.w;
            v183 = wk->pos.z;
            v180 = wk->rot.y;
            v181 = wk->rot.x;
            v194.y = v180;
            v194.x = v181;
            pos.w = v182;
            pos.z = v183;
            pos.y = y;
            pos.x = x;
            v194.w = w;
            v194.z = z;
            *(u64 *)&v187.x = 0;
            *(u64 *)&v187.z = method;
            if (sBtlCheckCrossCircle_Rot(pos, v194, hit_area_r + 300.0, v187, r2, v83))
            {
LABEL_274:
              sBtlAutoRec(v74, v68);
            }
          }
        }
      }
    }
  }
LABEL_12:
  rejyenecounter = wk->rejyenecounter;
  v8 = __OFSUB__(rejyenecounter, 1);
  v9 = rejyenecounter - 1;
  if (v9 < 0 == v8)
  {
    wk->rejyenecounter = v9;
    if (v9)
    {
      v10 = wk->rejyenecnt + 1;
      rejyenecmpcnt = wk->rejyenecmpcnt;
      wk->rejyenecnt = v10;
      if (rejyenecmpcnt <= v10)
      {
        wk->rejyenecnt = 0;
        rejyenepara = wk->rejyenepara;
        v14 = wk->para;
        now = v14->now;
        hp = now->hp;
        LODWORD(now) = now->maxhp;
        v17 = hp + rejyenepara;
        v18 = (u32)now - hp;
        if (v17 > (s32)now)
          rejyenepara = v18;
        if ((wk->side & 1) != 0)
        {
          if ((wk->status3 & 0x8000000) != 0)
          {
            if (rejyenepara >= 0)
              v20 = rejyenepara;
            else
              v20 = rejyenepara + 1;
            rejyenepara = v20 >> 1;
          }
        }
        v21 = wk->para->now;
        v23 = v21->hp;
        maxhp = v21->maxhp;
        p_hp = &v21->hp;
        *p_hp = v23 + rejyenepara;
        LimitRange(p_hp, 0, maxhp);
        if (rejyenepara >= 1)
        {
          sBtlCreateAnim_Unit(wk, 0, rejyenepara, 0, 3, 0);
          v26 = wk->total_recover + rejyenepara;
          v27 = wk;
          wk->total_recover = v26;
          if ((wk->status & 0x1000) != 0)
          {
            rejyenehelper = wk->rejyenehelper;
            v30 = wk->UnitMng;
            v31 = sBtlSearchUnit_ID(v30, rejyenehelper);
            if (v31)
              v27 = v31;
            else
              v27 = wk;
          }
          v33 = v27->pos.x;
          v34 = v27->pos.y;
          effList = wk->effList;
          v37 = v27->pos.z;
          v36 = v27->pos.w;
          v188.x = v33;
          v188.y = v34;
          v188.z = v37;
          v188.w = v36;
          sBtlCreateEff(effList, v27, 25, 0, v188, 0x80808080, 0, 1.0, 0);
        }
      }
    }
    else
    {
      wk->rejyenecounter = 0;
      *(u64 *)&wk->rejyenecnt = 0;
      wk->rejyenepara = 0;
    }
  }
  wkBarrier = wk->wkBarrier;
  if (wkBarrier->_size >= 1)
  {
    v39 = 0;
    do
    {
      if (SHIDWORD(_get_Item(wkBarrier, v39)[1].klass) >= 1)
      {
        Item = _get_Item(wk->wkBarrier, v39);
        v41 = Method_System_Collections_Generic_List_tagSBTLSKL_BARRIER_WORK__get_Item__;
        --HIDWORD(Item[1].klass);
        if (SHIDWORD(_get_Item(wk->wkBarrier, v39, v41)[1].klass) <= 0)
        {
          LODWORD(_get_Item(wk->wkBarrier, v39)[1].monitor) = 0;
          HIDWORD(_get_Item(wk->wkBarrier, v39)[1].monitor) = 0;
          HIDWORD(_get_Item(wk->wkBarrier, v39)[1].klass) = 0;
          if (LODWORD(_get_Item(wk->wkBarrier, v39)[1].klass))
          {
            if ((wk->side & 1) != 0 && LOBYTE(_get_Item(wk->wkBarrier, v39)[2].klass))
            {
              sysmsgList = wk->sysmsgList;
              klass = _get_Item(wk->wkBarrier, v39)[1].klass;
              sBtlCreateSM(sysmsgList, wk, 62, klass, 0, 120);
            }
            LODWORD(_get_Item(wk->wkBarrier, v39)[1].klass) = 0;
            _RemoveAt(wk->wkBarrier, v39);
          }
          sBtlCheckBattlePara(wk);
        }
      }
      wkBarrier = wk->wkBarrier;
      ++v39;
    }
    while (v39 < wkBarrier->_size);
  }
  enchantcnt = wk->enchantcnt;
  v8 = __OFSUB__(enchantcnt, 1);
  v47 = enchantcnt - 1;
  if (v47 < 0 == v8)
  {
    wk->enchantcnt = v47;
    if (!v47)
    {
      wk->enchantcnt = 0;
      v49 = wk;
      sword_eff_skl = v49->sword_eff_skl;
      if (sword_eff_skl)
      {
        if ((wk->side & 1) != 0)
        {
          v49 = wk;
          sword_eff_skl = v49->sword_eff_skl;
          v51 = v49->sysmsgList;
          sBtlCreateSM(v51, wk, 62, sword_eff_skl, 0, 120);
        }
        wk->swordskl = 0;
      }
    }
  }
  bulletcnt = wk->bulletcnt;
  v8 = __OFSUB__(bulletcnt, 1);
  v53 = bulletcnt - 1;
  if (v53 < 0 == v8)
  {
    if (v53)
    {
      wk->bulletcnt = v53;
    }
    else
    {
      bulletskl = wk->bulletskl;
      wk->bulletcnt = 0;
      if (bulletskl)
      {
        if ((wk->side & 1) != 0)
        {
          bulletskl = wk->bulletskl;
          v56 = wk->sysmsgList;
          sBtlCreateSM(v56, wk, 62, bulletskl, 0, 120);
        }
        wk->bulletskl = 0;
      }
    }
  }
  wkAura = wk->wkAura;
  v58 = wkAura[0];
  auracnt = v58->auracnt;
  v8 = __OFSUB__(auracnt, 1);
  v60 = auracnt - 1;
  if (v60 < 0 == v8)
  {
    v58->auracnt = v60;
    if (!v60)
    {
      auraskl = v58->auraskl;
      wk->aurakind &= ~0x1000000u;
      v58->auracnt = 0;
      v58->aurapara = 0;
      if (auraskl)
      {
        if ((wk->side & 1) != 0)
        {
          auraskl = wk->wkAura[0]->auraskl;
          v64 = wk->sysmsgList;
          v65 = 66;
        }
        else
        {
          auraskl = wk->wkAura[0]->auraskl;
          v64 = wk->sysmsgList;
          v65 = 70;
        }
        sBtlCreateSM(v64, wk, v65, auraskl, 0, 120);
        wkAura = wk->wkAura;
        wkAura[0]->auraskl = 0;
      }
    }
  }
  v85 = wkAura[1];
  v86 = v85->auracnt;
  v8 = __OFSUB__(v86, 1);
  v87 = v86 - 1;
  if (v87 < 0 == v8)
  {
    v85->auracnt = v87;
    if (!v87)
    {
      v88 = v85->auraskl;
      wk->aurakind &= ~0x4000000u;
      v85->auracnt = 0;
      v85->aurapara = 0;
      if (v88)
      {
        if ((wk->side & 1) != 0)
        {
          if (!v90)
          {
            v88 = wk->wkAura[1]->auraskl;
          }
          v91 = wk->sysmsgList;
          v92 = 66;
        }
        else
        {
          if (!v90)
          {
            v88 = wk->wkAura[1]->auraskl;
          }
          v91 = wk->sysmsgList;
          v92 = 70;
        }
        sBtlCreateSM(v91, wk, v92, v88, 0, 120);
        wkAura = wk->wkAura;
        wkAura[1]->auraskl = 0;
      }
    }
  }
  v93 = wkAura[2];
  v94 = v93->auracnt;
  v8 = __OFSUB__(v94, 1);
  v95 = v94 - 1;
  if (v95 < 0 == v8)
  {
    v93->auracnt = v95;
    if (!v95)
    {
      v96 = v93->auraskl;
      wk->aurakind &= ~0x2000000u;
      v93->auracnt = 0;
      v93->aurapara = 0;
      if (v96)
      {
        if ((wk->side & 1) != 0)
        {
          if (!v98)
          {
            v96 = wk->wkAura[2]->auraskl;
          }
          v99 = wk->sysmsgList;
          v100 = 66;
        }
        else
        {
          if (!v98)
          {
            v96 = wk->wkAura[2]->auraskl;
          }
          v99 = wk->sysmsgList;
          v100 = 70;
        }
        sBtlCreateSM(v99, wk, v100, v96, 0, 120);
        wk->wkAura[2]->auraskl = 0;
      }
    }
  }
  moveSpdMul = wk->moveSpdMul;
  if (moveSpdMul != 0.0)
  {
    v102 = wk->mv_spd.z;
    v103 = wk->max_mvspd.z;
    if (v102 == v103)
      wk->mv_spd.z = moveSpdMul * v102;
    v104 = wk->mv_spdbk.z;
    if (v104 == v103)
      wk->mv_spdbk.z = moveSpdMul * v104;
  }
  if (sBtlCheckSpecialDamage_Stop(wk))
    goto LABEL_196;
  slipcounter = wk->slipcounter;
  v8 = __OFSUB__(slipcounter, 1);
  v109 = slipcounter - 1;
  if (v109 < 0 != v8)
    goto LABEL_196;
  wk->slipcounter = v109;
  if (!v109)
  {
    *(u64 *)&wk->slippara = 0;
    *(u64 *)&wk->slipcounter = 0;
    *(u64 *)&wk->slipcmpcnt = 0;
    v123 = wk->effList;
    sBtlForceDelete_ID_Acter(v123, wk, 55);
    goto LABEL_196;
  }
  v110 = wk->slipcnt + 1;
  slipcmpcnt = wk->slipcmpcnt;
  wk->slipcnt = v110;
  if (slipcmpcnt > v110)
    goto LABEL_196;
  wk->slipcnt = 0;
  slippara = wk->slippara;
  if (wk->battlemode != 3)
  {
    v146 = 0;
    while (1)
    {
      spiritSkill = GBWK->player->spiritSkill;
      if (v146 >= SLODWORD(spiritSkill->max_length))
        break;
      spiritSkill = GBWK->player->spiritSkill;
      v147 = (char *)spiritSkill + 4 * v146++;
      if (*((u32 *)v147 + 8) == 1450)
      {
        if ((wk->side & 2) != 0 && (wk->side_given_slip & 0x81) == 1)
        {
          v179 = (f32)slippara * 2.5;
          if (v179 == INFINITY)
            slippara = 0x80000000;
          else
            slippara = v179;
        }
        break;
      }
    }
  }
  v114 = sBtlCheckKuishibari(wk, slippara);
  sBtlDecHp(wk, v114, 0);
  if ((wk->side & 1) != 0)
    wk->hpGageDamageFlag = 1;
  Skilltbl = sBtlGetSkilltbl(wk->slip_sklid);
  v116 = Skilltbl;
  v117 = wk;
  if ((wk->status & 0x1000) != 0)
  {
    hitsliphelper = wk->hitsliphelper;
    v151 = wk->UnitMng;
    v152 = sBtlSearchUnit_ID(v151, hitsliphelper);
    if (v152)
      v117 = v152;
    else
      v117 = wk;
    attr = v116->attr;
    if ((attr & 4) == 0)
    {
LABEL_176:
      if ((attr & 8) == 0)
        goto LABEL_177;
      goto LABEL_245;
    }
  }
  else
  {
    attr = Skilltbl->attr;
    if ((attr & 4) == 0)
      goto LABEL_176;
  }
  v154 = v117->pos.x;
  v155 = v117->pos.y;
  v156 = wk->effList;
  v158 = v117->pos.z;
  v157 = v117->pos.w;
  v190.x = v154;
  v190.y = v155;
  v190.z = v158;
  v190.w = v157;
  sBtlCreateEff(v156, v117, 26, 0, v190, 0x80808080, 0, 1.0, 0);
  attr = v116->attr;
  if ((attr & 8) == 0)
  {
LABEL_177:
    if ((attr & 0x10) == 0)
      goto LABEL_178;
    goto LABEL_250;
  }
LABEL_245:
  v160 = v117->pos.x;
  v161 = v117->pos.y;
  v162 = wk->effList;
  v164 = v117->pos.z;
  v163 = v117->pos.w;
  v191.x = v160;
  v191.y = v161;
  v191.z = v164;
  v191.w = v163;
  sBtlCreateEff(v162, v117, 27, 0, v191, 0x80808080, 0, 1.0, 0);
  attr = v116->attr;
  if ((attr & 0x10) == 0)
  {
LABEL_178:
    if ((attr & 0x20) == 0)
      goto LABEL_179;
    goto LABEL_255;
  }
LABEL_250:
  v166 = v117->pos.x;
  v167 = v117->pos.y;
  v168 = wk->effList;
  v170 = v117->pos.z;
  v169 = v117->pos.w;
  v192.x = v166;
  v192.y = v167;
  v192.z = v170;
  v192.w = v169;
  sBtlCreateEff(v168, v117, 28, 0, v192, 0x80808080, 0, 1.0, 0);
  if ((v116->attr & 0x20) == 0)
  {
LABEL_179:
    goto LABEL_180;
  }
LABEL_255:
  v172 = v117->pos.x;
  v173 = v117->pos.y;
  v174 = wk->effList;
  v176 = v117->pos.z;
  v175 = v117->pos.w;
  v193.x = v172;
  v193.y = v173;
  v193.z = v176;
  v193.w = v175;
  sBtlCreateEff(v174, v117, 29, 0, v193, 0x80808080, 0, 1.0, 0);
LABEL_180:
  sBtlCreateAnim_Unit(wk, 0, slippara, 0, 1, 0);
  if ((wk->status & 0x40000000) != 0)
  {
LABEL_263:
    sBtlSetSpecialDamage_DamageOnly(wk);
    return 0;
  }
  if (sBtlIsDeadBgn(wk))
  {
    sBtlSetDeadDamage(wk, 0, 0);
    v121 = wk->effList;
    sBtlForceDelete_ID_Acter(v121, wk, 55);
    return 0;
  }
LABEL_196:
  if (sBtlCheckSpecialDamage_Stop(wk))
    return 0;
  tdancounter = wk->tdancounter;
  v8 = __OFSUB__(tdancounter, 1);
  v127 = tdancounter - 1;
  if (v127 < 0 == v8)
  {
    wk->tdancounter = v127;
    if (!v127)
    {
      wk->tdanpara = 0;
      wk->tdan_sklid = 0;
      *(u64 *)&wk->tdancounter = 0;
      *(u64 *)&wk->tdanhitcnt = 0;
      return 0;
    }
    v128 = wk->tdancnt + 1;
    tdancmpcnt = wk->tdancmpcnt;
    wk->tdancnt = v128;
    if (tdancmpcnt <= v128)
    {
      tdanhitcnt = wk->tdanhitcnt;
      wk->tdancnt = 0;
      tdanpara = wk->tdanpara;
      wk->tdanhitcnt = tdanhitcnt + 1;
      v133 = sBtlCheckKuishibari(wk, tdanpara);
      sBtlDecHp(wk, v133, 0);
      v134 = sBtlGetSkilltbl(wk->tdan_sklid);
      v135 = v134->attr;
      v136 = v134;
      a_pHanshaType = 0;
      v138 = sBtlCheckAisyoEx(wk, v135, &a_pHanshaType);
      if (wk->tdanhitcnt < v136->count)
      {
        v140 = v138;
        tdan_acterid = wk->tdan_acterid;
        tdan_sklid = wk->tdan_sklid;
        sBtlWeakShildActive(wk, v140, tdan_acterid, tdan_sklid);
      }
      v143 = wk->tdanpara;
      v144 = wk->tdan_sklid;
      sBtlCreateAnim_Unit(wk, 0, v143, 0, 2, v144);
      if ((wk->status & 0x40000000) == 0)
      {
        if (sBtlIsDeadBgn(wk))
        {
          sBtlSetDeadDamage(wk, 0, 0);
        }
        return 0;
      }
      goto LABEL_263;
    }
  }
  return 0;
}

// 0x1ee6020
bool sBtlCheckBadStatus_Return(s32 idx) {
  _BOOL4 v4;
  sdatUnitWork_t *para;
  u32 BadStatus;

  goto LABEL_3;
LABEL_7:
  para = sBtlGetNakama(idx)->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus <= 0x16)
    return (0x600800u >> BadStatus) & 1;
  LOBYTE(v4) = 0;
  return v4;
LABEL_3:
  if (!sBtlCheckSummonUnit_Exist(idx))
    goto LABEL_7;
  LOBYTE(v4) = 0;
  return v4;
}

// 0x1ed66d0
BST sBtlGetBadStatus(sdatUnitWork_t *unit) {
  s32 badstatus;
  u32 result;

  if (!unit)
    return 22;
  badstatus = unit->badstatus;
  result = 22;
  if (badstatus)
  {
    if ((badstatus & 1) != 0)
    {
      return 0;
    }
    else if ((badstatus & 2) != 0)
    {
      return 1;
    }
    else if ((badstatus & 4) != 0)
    {
      return 2;
    }
    else if ((badstatus & 8) != 0)
    {
      return 3;
    }
    else if ((badstatus & 0x10) != 0)
    {
      return 4;
    }
    else if ((badstatus & 0x20) != 0)
    {
      return 5;
    }
    else if ((badstatus & 0x40) != 0)
    {
      return 6;
    }
    else if ((badstatus & 0x80) != 0)
    {
      return 7;
    }
    else if ((badstatus & 0x100) != 0)
    {
      return 8;
    }
    else if ((badstatus & 0x200) != 0)
    {
      return 9;
    }
    else if ((badstatus & 0x400) != 0)
    {
      return 10;
    }
    else if ((badstatus & 0x800) != 0)
    {
      return 11;
    }
    else if ((badstatus & 0x1000) != 0)
    {
      return 12;
    }
    else if ((badstatus & 0x2000) != 0)
    {
      return 13;
    }
    else if ((badstatus & 0x4000) != 0)
    {
      return 14;
    }
    else if ((badstatus & 0x8000) != 0)
    {
      return 15;
    }
    else if ((badstatus & 0x10000) != 0)
    {
      return 16;
    }
    else if ((badstatus & 0x20000) != 0)
    {
      return 17;
    }
    else if ((badstatus & 0x40000) != 0)
    {
      return 18;
    }
    else if ((badstatus & 0x80000) != 0)
    {
      return 19;
    }
    else if ((badstatus & 0x100000) != 0)
    {
      return 20;
    }
    else
    {
      return 22;
    }
  }
  return result;
}

// 0x1ed6800
bool sBtlIsKoufun(sdatUnitWork_t *unit) {
  if (unit)
    LODWORD(unit) = (LOBYTE(unit->koufunst) >> 5) & 1;
  return (char)unit;
}

// 0x1ee6140
bool CalcBadStatus(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  sdatUnitWork_t *para;
  s32 v9;
  sdatUnitWork_t *v10;
  s32 badst_cnt;
  s16 v13;
  s16 *v14;
  s16 v15;
  sdatUnitWork_t *v17;
  f32 v18;
  s32 level;
  s16 *p_badst_cnt2;
  s16 badst_cnt2;
  sdatUnitWork_t *v23;
  s16 *v25;
  s16 v26;
  sdatUnitWork_t *v27;
  sdatUnitWork_t *v28;
  sdatParaWork_t *now;
  s32 maxhp;
  f32 v31;
  s32 v32;
  s32 v33;
  s32 v34;
  sdatParaWork_t *v35;
  SBTLUNIT_WORK *PChara;
  sdatUnitWork_t *v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 side;
  s32 hp;
  s32 v46;
  s32 v47;
  s32 *p_hp;
  s32 v50;
  sdatUnitWork_t *v51;
  sdatParaWork_t *v52;
  s32 maxmp;
  f32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  sdatParaWork_t *v58;
  s32 mp;
  s32 v60;
  s32 v61;
  bool v63;
  s32 v64;
  s32 *p_mp;
  s32 v66;
  s16 v67;
  s32 koufunskl;
  SBTLSM_LISTWORK *sysmsgList;
  s32 bst_effserialID2;
  SBTLEFF_LISTWORK *effList;
  char v74;
  s32 devilid;
  sdatUnitWork_t *v76;
  s32 v77;
  __int128 v78;
  s32 *v79;
  s32 v80;
  SBTLEFF_LISTWORK *v82;

  v4 = wk;
  if (!v4->bBfrBtlEnd)
    return 1;
  if (v4->cmbSkl->bRun)
    return 1;
  if (v4->sklProc->bRun)
    return 1;
  v4 = wk;
  if (v4->kaiwaflg)
    return 1;
  if (IsSceanStop())
  {
    if (!sBtlCheckPlayerDead())
      return 1;
  }
  para = wk->para;
  if (!para->badstatus)
  {
LABEL_116:
    if (para->koufunst)
    {
      if (para->koufun_cnt)
      {
        v67 = para->koufun_cnt - 1;
        para->koufun_cnt = v67;
        if (v67 <= 0)
        {
          if ((wk->side & 0x80) != 0)
          {
            koufunskl = wk->koufunskl;
            if (koufunskl)
            {
              koufunskl = wk->koufunskl;
              sysmsgList = wk->sysmsgList;
              sBtlCreateSM(sysmsgList, wk, 62, koufunskl, 0, 120);
              wk->koufunskl = 0;
            }
          }
          sBtlResetBadStatus(wk, 32);
          bst_effserialID2 = wk->bst_effserialID2;
          if (bst_effserialID2 != -1)
          {
            bst_effserialID2 = wk->bst_effserialID2;
            effList = wk->effList;
            sBtlDeleteEffectData_SerialID2(effList, bst_effserialID2);
            wk->bst_effserialID2 = -1;
          }
        }
      }
    }
    return 1;
  }
  v9 = 0;
  while (1)
  {
    v10 = wk->para;
    if ((v10->badstatus & (1 << v9)) == 0)
      goto LABEL_28;
    if (v9 == 15)
    {
      badst_cnt2 = v10->badst_cnt2;
      p_badst_cnt2 = &v10->badst_cnt2;
      *p_badst_cnt2 = badst_cnt2 + 1;
      LimitRange_2(p_badst_cnt2, 0, 30);
      if (wk->para->badst_cnt2 >= 10)
      {
        sBtlDecMag(1);
      }
      goto LABEL_28;
    }
    if (v9 == 16)
    {
      if (wk->encountno == 58)
        goto LABEL_28;
      v10 = wk->para;
    }
    badst_cnt = (u16)v10->badst_cnt;
    if (v10->badst_cnt)
    {
      if (badst_cnt != 9999)
      {
        v13 = badst_cnt - 1;
        v10->badst_cnt = v13;
        if (v13 <= 0)
          break;
      }
    }
    if (v9 == 12)
    {
      if (!sBtlCheckSpecialDamage_Stop(wk))
      {
        v23 = wk->para;
        v26 = v23->badst_cnt2;
        v25 = &v23->badst_cnt2;
        *v25 = v26 + 1;
        LimitRange_2(v25, 0, 180);
        v27 = wk->para;
        if (v27->badst_cnt2 >= 180)
        {
          v27->badst_cnt2 = 0;
          if (v27->now->hp >= 1)
          {
            if (sBtlCheckDamageTarget(wk))
            {
              v28 = wk->para;
              now = v28->now;
              maxhp = now->maxhp;
              v31 = (f32)maxhp * 0.01;
              v32 = v31;
              if ((s32)v31 <= 1)
                v32 = 1;
              if (v31 == INFINITY)
                v33 = 1;
              else
                v33 = v32;
              v34 = now->maxhp;
              v35 = v28->now;
              hp = v35->hp;
              v46 = hp + v33;
              v47 = v34 - hp;
              if (v46 > v34)
                v33 = v47;
              v50 = now->hp;
              p_hp = &now->hp;
              *p_hp = v50 + v33;
              LimitRange(p_hp, 0, maxhp);
              sBtlCreateAnim_Unit(wk, 0, v33, 0, 3, 0);
              v51 = wk->para;
              v52 = v51->now;
              maxmp = v52->maxmp;
              v54 = (f32)maxmp * 0.01;
              v55 = v54;
              if ((s32)v54 <= 1)
                v55 = 1;
              if (v54 == INFINITY)
                v56 = 1;
              else
                v56 = v55;
              v57 = v52->maxmp;
              v58 = v51->now;
              mp = v58->mp;
              v60 = mp + v56;
              v61 = v57 - mp;
              v63 = v60 <= v57;
              v66 = v52->mp;
              p_mp = &v52->mp;
              v64 = v66;
              if (!v63)
                v56 = v61;
              *p_mp = v64 + v56;
              LimitRange(p_mp, 0, maxmp);
              sBtlCreateAnim_Unit(wk, 0, v56, 12, 4, 0);
            }
          }
        }
      }
      goto LABEL_28;
    }
    if (v9 == 11)
    {
      v15 = v10->badst_cnt2;
      v14 = &v10->badst_cnt2;
      *v14 = v15 + 1;
      LimitRange_2(v14, 0, 180);
      v17 = wk->para;
      if (v17->badst_cnt2 >= 180)
      {
        v17->badst_cnt2 = 0;
        if ((wk->side & 2) != 0)
        {
          PChara = sBtlGetPChara();
          if (PChara && (v37 = PChara->para) != 0)
            level = v37->level;
          else
            level = 1;
        }
        else
        {
          v18 = (f32)v17->now->maxhp * 0.03;
          level = v18;
          if (v18 == INFINITY)
            level = 0x80000000;
        }
        v38 = wk->para->now->hp;
        if (v38 >= 2)
        {
          v39 = v38 - level;
          v40 = v38 - 1;
          if (v39 <= 0)
            v41 = v40;
          else
            v41 = level;
          sBtlDecHp(wk, v41, 0);
          side = wk->side;
          if ((~side & 0x81) != 0)
          {
            if ((side & 1) != 0)
              goto LABEL_84;
          }
          else
          {
            sBtlSetVibe(6);
            if ((wk->side & 1) != 0)
            {
LABEL_84:
              wk->hpGageDamageFlag = 1;
LABEL_90:
              if (sBtlIsDeadBgn(wk))
                goto LABEL_91;
              goto LABEL_87;
            }
          }
          goto LABEL_90;
LABEL_91:
          wk->para->now->hp = 1;
LABEL_87:
          sBtlCreateAnim_Unit(wk, 0, v41, 0, 0, 0);
          goto LABEL_28;
        }
      }
    }
LABEL_28:
    if (++v9 == 21)
    {
      para = wk->para;
      goto LABEL_116;
    }
  }
  v74 = BYTE1(v10->badstatus);
  v10->badst_cnt = 0;
  if ((v74 & 0x40) != 0)
  {
    devilid = v10->devilid;
    if (sBtlCheckScriptData(devilid, wk))
    {
      sBtlSetAIWkStat(wk, 1);
    }
  }
  sBtlResetBadStatus(wk, 1 << v9);
  v76 = wk->para;
  v77 = (u16)v76->devilid;
  if ((v77 == 297 || v77 == 290) && wk->Itimoku_CloseEye)
  {
    *(u64 *)&v78 = 0x100000001000LL;
    *((u64 *)&v78 + 1) = 0x100000001000LL;
    v79 = v76->aisyo->para;
    *(_OWORD *)v79 = v78;
    *(_OWORD *)&v79[4] = v78;
    *(_OWORD *)&v79[8] = v78;
    *(_OWORD *)&v79[12] = v78;
    return 0;
  }
  else
  {
    if (v9 != 5)
      return 0;
    v80 = wk->bst_effserialID2;
    if (v80 == -1)
    {
      return 0;
    }
    else
    {
      v80 = wk->bst_effserialID2;
      v82 = wk->effList;
      sBtlDeleteEffectData_SerialID2(v82, v80);
      wk->bst_effserialID2 = -1;
      return 0;
    }
  }
}

// 0x1ee6af0
void sBtlKudaHuuinCheck(void) {
  SBATTLE_WORK *v4;
  void *v5;
  s64 i;
  void *v8;
  sdatUnitWork_t *v10;
  sdatUnitWork_t *unit;
  void *huuinUnit;
  void *v14;
  Il2CppObject *v16;
  void *v17;
  s64 size;
  u64 *v19;
  void *items;
  Il2CppClass **v21;
  Il2CppObject *current;
  s16 v24;
  s32 v25;
  System_Collections_Generic_List_Enumerator_T__o v27;

  memset(&v27, 0, sizeof(v27));
  if (!wk->bBfrBtlEnd)
    return;
  if (wk->cmbSkl->bRun)
    return;
  if (wk->sklProc->bRun)
    return;
  if (!wk->kaiwaflg)
  {
    if (!IsSceanStop())
      goto LABEL_24;
    if (sBtlCheckPlayerDead())
    {
LABEL_24:
      v4 = wk;
      if (!v4->huuinUnit)
      {
        v4 = wk;
        v5 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
        __ctor(v5);
        v4->huuinUnit = v5;
      }
      for (i = 0; ; ++i)
      {
        if (i >= GBWK->player->stock_max)
          break;
        v8 = Allocate(Project_sBtlCalc___c__DisplayClass142_0);
        _c__DisplayClass142_0___ctor(v8, 0);
        v10 = GBWK->player->stock_id[i];
        v8->unit = v10;
        unit = v8->unit;
        if (unit->devilid && (unit->flag & 1) != 0 && (unit->badstatus & 0x10000) != 0)
        {
          huuinUnit = wk->huuinUnit;
          v14 = Allocate(System_Predicate_sdatUnitWork_t_);
          __ctor(v14, v8, Method_Project_sBtlCalc___c__DisplayClass142_0__KudaHuuinCheck_b__0__, 0);
          if (!_Find(huuinUnit, v14))
          {
            v16 = v8->unit;
            v17 = wk->huuinUnit;
            size = v17->_size;
            v19 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
            ++v17->_version;
            items = v17->_items;
            if ((u32)size >= LODWORD(items->max_length))
            {
              _AddWithResize(v17, v16, *(const MethodInfo_2DFC660 **)(*(u64 *)(v19[4] + 192) + 112));
            }
            else
            {
              v17->_size = size + 1;
              v21 = &items->obj.klass + size;
              v21[4] = v16;
            }
          }
        }
      }
      _GetEnumerator(&v27, wk->huuinUnit);
      while (_MoveNext(&v27))
      {
        current = v27._current;
        v24 = *(u16 *)((char *)&v27._current->klass + (u64)&qword_98);
        if (*(u16 *)((char *)&v27._current->klass + (u64)&locret_94) != 9999)
          *(u16 *)((char *)&v27._current->klass + (u64)&qword_98) = --v24;
        if (v24 <= 0)
        {
          v25 = *(u32 *)((char *)sub_90 + (u64)current);
          *(u16 *)((char *)&qword_98 + (u64)current) = 0;
          *(u32 *)((char *)sub_90 + (u64)current) = v25 & 0xFFFEFFFF;
          _Remove(wk->huuinUnit, current);
          break;
        }
      }
      _Dispose(&v27);
    }
  }
}

// 0x1ee7090
void sBtlKudaHuuin_AllOn(bool _InfTime) {
  SBATTLE_WORK *wk_local;
  void *v5;
  s64 v6;
  s16 v7;
  void *v9;
  sdatUnitWork_t *v11;
  sdatUnitWork_t *unit;
  s32 badstatus;
  void *huuinUnit;
  void *v16;
  Il2CppObject *v18;
  void *v19;
  s64 size;
  u64 *v21;
  void *items;
  Il2CppClass **v23;

  wk_local = wk;
  if (!wk_local->huuinUnit)
  {
    wk_local = wk;
    v5 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
    __ctor(v5);
    wk_local->huuinUnit = v5;
  }
  v6 = 0;
  if (InfTime)
    v7 = 9999;
  else
    v7 = 600;
  while (1)
  {
    if (v6 >= GBWK->player->stock_max)
      break;
    v9 = Allocate(Project_sBtlCalc___c__DisplayClass143_0);
    _c__DisplayClass143_0___ctor(v9, 0);
    v11 = GBWK->player->stock_id[v6];
    v9->unit = v11;
    unit = v9->unit;
    if (unit->devilid && (unit->flag & 1) != 0)
    {
      badstatus = unit->badstatus;
      unit->badst_cnt = v7;
      *(u32 *)&unit->badst_cnt2 = 235929600;
      unit->badstatus = badstatus | 0x10000;
      huuinUnit = wk->huuinUnit;
      v16 = Allocate(System_Predicate_sdatUnitWork_t_);
      __ctor(v16, v9, Method_Project_sBtlCalc___c__DisplayClass143_0__KudaHuuin_AllOn_b__0__, 0);
      if (!_Find(huuinUnit, v16))
      {
        v18 = v9->unit;
        v19 = wk->huuinUnit;
        size = v19->_size;
        v21 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
        ++v19->_version;
        items = v19->_items;
        if ((u32)size >= LODWORD(items->max_length))
        {
          _AddWithResize(v19, v18, *(const MethodInfo_2DFC660 **)(*(u64 *)(v21[4] + 192) + 112));
        }
        else
        {
          v19->_size = size + 1;
          v23 = &items->obj.klass + size;
          v23[4] = v18;
        }
      }
    }
    ++v6;
  }
}

// 0x1ee73a0
void sBtlKudaHuuin_AllOff(void) {
  s64 v2;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *v5;
  s32 badstatus;

  if (wk->huuinUnit)
  {
    v2 = 0;
    while (1)
    {
      player = GBWK->player;
      if (v2 >= player->stock_max)
        return;
      v5 = player->stock_id[v2];
      if (v5->devilid)
      {
        if ((v5->flag & 1) != 0)
        {
          badstatus = v5->badstatus;
          if ((badstatus & 0x10000) != 0)
          {
            v5->badst_cnt3 = 0;
            v5->badstatus = badstatus & 0xFFFEFFFF;
            _Remove(wk->huuinUnit, v5);
          }
        }
      }
      ++v2;
    }
  }
}

// 0x1ee7530
bool sBtlResetBadStatus_GB(sdatUnitWork_t *unit, BSTF flg) {
  s32 badstatus;
  s32 koufunst;

  badstatus = unit->badstatus;
  unit->badst_cnt = 0;
  unit->badstatus = badstatus & ~flg;
  if (flg == 0x3FFFF || flg == 32)
  {
    koufunst = unit->koufunst;
    unit->koufun_cnt = 0;
    unit->koufunst = koufunst & ~flg;
  }
  return 1;
}

// 0x1edd8f0
bool sBtlResetBadStatus(SBTLUNIT_WORK *wk, BSTF flg) {
  bool v5;
  bool v6;
  sdatUnitWork_t *para;
  s32 badstatus;
  SBTLACTION_WORK *actwk;
  s32 devilid;
  s32 bst_effserialID2;
  SBTLEFF_LISTWORK *effList;
  dds3ModelHandle_t *hModel;

  v5 = (wk->status & 0x800) != 0 || flg == 0;
  v6 = !v5;
  if (!v5)
  {
    if (flg > 196606)
    {
      if (flg != 196607 && flg != 0x3FFFF)
        goto LABEL_36;
    }
    else if (flg != 32 && flg != 98303)
    {
LABEL_36:
      para = wk->para;
LABEL_17:
      badstatus = para->badstatus;
      para->badst_cnt = 0;
      para->badstatus = badstatus & ~flg;
      actwk = wk->actwk;
      if (actwk->status == 9)
      {
        actwk->cmpframecnt = 0;
      }
      else
      {
        sBtlReetBadStatus_Color(wk);
        devilid = (u16)wk->para->devilid;
        if (devilid == 260)
          goto LABEL_27;
        goto LABEL_23;
      }
      sBtlReetBadStatus_Color(wk);
      devilid = (u16)wk->para->devilid;
      if (devilid == 260)
      {
LABEL_27:
        bst_effserialID2 = wk->bst_effserialID2;
        if (bst_effserialID2 != -1)
        {
          bst_effserialID2 = wk->bst_effserialID2;
          effList = wk->effList;
          sBtlDeleteEffectData_SerialID2(effList, bst_effserialID2);
          wk->bst_effserialID2 = -1;
        }
        hModel = wk->hModel;
        if (hModel)
          hModel->stat &= ~2u;
        return v6;
      }
LABEL_23:
      if (devilid != 315)
      {
        CalcAisyo(wk);
      }
      goto LABEL_27;
    }
    para = wk->para;
    para->koufun_cnt = 0;
    para->koufunst &= ~flg;
    goto LABEL_17;
  }
  return v6;
}

// 0x1eda820
s32 sBtlGetBadStatus_Attr(BST bstno) {
  void *v3;

  v3 = NewSpecific(s32, 0x15u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__515F9C7D26FB948050975ABBBF53EA89B3FBD3E402B5A7B2AEC7081E44591542, 0);
  return *((u32 *)&v3[2].klass + bstno);
}

// 0x1ee79d0
void sBtlCheckResetBadStatus(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  char v8;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus - 21 < 2)
    return;
  v8 = BadStatus;
  sBtlResetBadStatus(wk, 1 << v8);
}

// 0x1ede2d0
s32 sBtlCheckBadStatus(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *wk, SKLID sklid, s32 flg) {
  SBTLSKILLP_TBL *Skilltbl;
  u32 v12;
  s32 v13;
  s32 hstatus;
  SBTLSKILLP_TBL *v15;
  s32 badst;
  SBATTLE_WORK *v18;
  s32 *p_tateClr;
  s32 v24;
  SBTLACTION_WORK *actwk;
  u32 status;
  signed s16 Rand;
  s32 damage_gunnum;
  s32 v29;
  s32 v30;
  u32 attr;
  s16 v33;
  s32 v35;
  s32 v36;
  SBTLACTION_WORK *v37;
  u32 v38;
  bool v39;
  char v40;
  s32 v42;
  _BOOL4 v44;
  char v45;
  u32 v46;
  u32 v47;
  s32 *v48;
  u32 v50;
  s32 v51;
  u16 Percentage;
  s64 v53;
  void *v55;
  char *v57;
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;
  sdatUnitWork_t *v62;
  s32 v63;
  sdatUnitWork_t *v66;
  s32 v67;
  sdatUnitWork_t *v70;
  s32 v71;
  sdatUnitWork_t *v74;
  s32 v75;
  sdatUnitWork_t *v78;
  s32 v79;
  sdatUnitWork_t *v82;
  s32 v83;
  sdatUnitWork_t *v86;
  s32 v87;
  sdatUnitWork_t *atkunit;
  u64 luck;
  sdatUnitWork_t *v91;
  s32 v92;
  _BOOL4 v93;
  u32 v94;
  char v95;
  s32 v96;
  sdatUnitWork_t *v97;
  s32 side;
  SBTLAISYO_DATAWORK *aisyo;
  s32 v100;
  s32 v101;
  SBTLAISYO_DATAWORK *v102;
  sdatUnitWork_t *v105;
  s32 v106;
  s32 v110;
  s32 v112;
  s32 v113;
  s32 v115;
  s32 v116;
  s32 v117;
  s32 v119;
  u32 v121;
  SBTLSKILLP_TBL *v122;
  char v123;
  SBTLUNIT_WORK *v124;
  s32 v125;
  _BOOL4 v126;
  s32 v127;
  _BOOL4 v128;
  s32 v129;
  s32 a_pHanshaType;

  if ((wk->hstatus & 0x10) == 0 && (wk->status & 0x100000) != 0 && (!CheckBadStatus(wk, 0) || wk->hangeki_notjyakuten > 0))
  {
    return -1;
  }
  if (wk->bTateNoDmg)
    return -1;
  Skilltbl = sBtlGetSkilltbl(sklid);
  v12 = Skilltbl->flg;
  v13 = -1;
  if ((v12 & 0x200) != 0 || (v12 & 0x10004) == 0x10004)
    return v13;
  hstatus = wk->hstatus;
  if ((hstatus & 0x40) != 0)
  {
    wk->hstatus = hstatus & 0xFFFFFFBF;
    return v13;
  }
  v15 = Skilltbl;
  if ((~wk->side & 0x81) == 0)
  {
    if (wk->sklProc->bRun && (wk->status & 0x100) != 0 && (v15->flg2 & 0x20000) == 0)
    {
      return v13;
    }
  }
  if ((~wk->side & 0x81) == 0)
  {
    if (wk->battlemode != 3)
    {
      if (sBtlGetSpiritSkillChk(1392))
        return v13;
    }
  }
  badst = v15->badst;
  v18 = wk;
  if (v18->sword_eff_cmb)
  {
    p_tateClr = &wk->cmbSkl->tateClr;
  }
  else
  {
    if ((v15->flg2 & 0x10) == 0)
      goto LABEL_49;
    v18 = wk;
    if (!v18->sword_eff_step)
      goto LABEL_49;
    p_tateClr = &wk->sword_eff_kind;
  }
  badst = swordBstTbl[*p_tateClr];
LABEL_49:
  if (badst != 0x4000)
    goto LABEL_65;
  wk->damage_guncnt = 60;
  v24 = (u16)wk->damage_gunnum + 1;
  wk->damage_gunnum = v24;
  if (v24 << 16 <= 196608)
    return v13;
  actwk = wk->actwk;
  status = actwk->status;
  if (status > 0x1F)
  {
    if (status == 41 || status == 53 || status == 54 && actwk->framecnt < 45)
      return v13;
  }
  else if (((1 << status) & 0x80000048) != 0)
  {
    return v13;
  }
  Rand = GetRand(0x64u);
  damage_gunnum = (u16)wk->damage_gunnum;
  v29 = damage_gunnum == 5 ? 30 : 90;
  v30 = damage_gunnum == 4 ? 20 : v29;
  if (v30 > Rand)
  {
LABEL_65:
    v127 = badst;
    a_pHanshaType = 0;
    attr = v15->attr;
    v33 = sBtlCheckAisyoEx(wk, attr, &a_pHanshaType);
    v125 = sklid;
    v124 = acter;
    if ((wk->status2 & 0x20000000) != 0)
      goto LABEL_91;
    v35 = v127 & 0x2000;
    if (v127 && (v127 & 0x2000) == 0)
      goto LABEL_92;
    v36 = v15->attr & 0x401;
    if (!(v36 | v35))
      goto LABEL_91;
    v37 = wk->actwk;
    v38 = v37->status;
    if (v38 > 0x1F)
    {
      if (v38 == 41 || v38 == 53)
        goto LABEL_82;
      if (v38 == 54)
      {
        v39 = v37->framecnt > 44;
        goto LABEL_85;
      }
    }
    else
    {
      if (v38 == 3 || v38 == 6)
      {
        v39 = v37->action_flg != 0;
        goto LABEL_85;
      }
      if (v38 == 31)
      {
LABEL_82:
        v39 = 0;
        goto LABEL_85;
      }
    }
    v39 = 1;
LABEL_85:
    if ((wk->para->aisyo->para[0] & 0x20000) != 0)
      goto LABEL_91;
    v40 = !v39;
    if (wk->bYobidousa)
      v40 = 1;
    if ((v40 & 1) != 0 || v36 && (v33 & 0x4000) != 0)
      goto LABEL_91;
    v115 = (s16)GetRand(0x64u);
    if ((v127 & 0x2000) == 0)
    {
      if ((wk->side & 2) != 0)
        v116 = 20;
      else
        v116 = 10;
      if (v116 > v115)
      {
        LOBYTE(v35) = 0;
        if ((u32)(sklid - 1536) >= 2 && sklid != 149)
        {
          if (acter)
          {
            v117 = v127;
            LOBYTE(v35) = (acter->side & 0x80) == 0;
            if ((acter->side & 0x80) == 0)
              v117 = 0x2000;
            v127 = v117;
          }
          else
          {
            LOBYTE(v35) = 0;
          }
        }
        goto LABEL_92;
      }
LABEL_91:
      LOBYTE(v35) = 0;
      goto LABEL_92;
    }
    v119 = v127;
    LOBYTE(v35) = v115 < v15->percentage;
    if (v115 < v15->percentage)
      v119 = 0x2000;
    v127 = v119;
LABEL_92:
    if ((wk->status2 & 0x20000000) == 0 && sklid != 149 && (v15->attr & 0x401) != 0 && (v33 & 0x4000) != 0)
    {
      v42 = acter->hstatus;
      LOBYTE(v35) = 1;
      acter->WeakAtkCnt = 0;
      wk->weak_attrinvtime_cnt = 0;
      acter->hstatus = v42 | 0x200000;
      *(u64 *)&wk->WeakReceiveFlg = 1;
      v127 = 0x2000;
    }
    if ((u32)(sklid - 1559) < 2)
    {
      if ((wk->side & 0x80) != 0)
        return -1;
    }
    else if ((u32)(sklid - 1548) > 1)
    {
      goto LABEL_106;
    }
    sBtlCheckResetBadStatus(wk);
LABEL_106:
    v44 = sklid == 457 || sklid == 1554;
    v126 = v44;
    if (v127)
    {
      v45 = v35 ^ 1;
      v46 = v127;
      v47 = 0;
      v13 = -1;
      v123 = v45;
      v122 = v15;
      while (1)
      {
        if (((v46 >> v47) & 1) == 0)
        {
          v93 = 0;
          goto LABEL_184;
        }
        v128 = v47 == 18;
        v48 = NewSpecific(s32, 5u);
        InitializeArray_55364416(v48, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__83F07A0FF7F15BB48E87D6CE388FC191B140534C69BB3EB88A858ABCF11096E1, 0);
        v50 = v47;
        if (v47 == 18)
        {
          v51 = *(u32 *)((char *)v48 + 24);
          Percentage = GetPercentage();
          v53 = 0;
          while ((v51 & ~(v51 >> 31)) != (u32)v53)
          {
            if (100 / v51 * (s32)++v53 > Percentage)
            {
              v50 = *(u32 *)((s64)(char *)v48 + 4 * v53 + 28);
              goto LABEL_124;
            }
          }
          v50 = 18;
          if (sBtlCheckBadStatus_Number(wk->para->badstatus, 18, wk))
          {
LABEL_125:
            if (!(v126 | 1))
              goto LABEL_171;
            goto LABEL_126;
          }
        }
        else
        {
LABEL_124:
          if (sBtlCheckBadStatus_Number(wk->para->badstatus, v50, wk))
            goto LABEL_125;
        }
        if (!sBtlCheckBadStatus_WeakNumber(wk, v50) && !v126)
        {
LABEL_171:
          v93 = v47 == 18;
          v47 = v50;
          goto LABEL_184;
        }
LABEL_126:
        v55 = NewSpecific(s32, 0x15u);
        InitializeArray_55364416(v55, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__515F9C7D26FB948050975ABBBF53EA89B3FBD3E402B5A7B2AEC7081E44591542, 0);
        v57 = (char *)v55 + 4 * v50;
        para = wk->para;
        v129 = *((u32 *)v57 + 8);
        AutoSkill_ID = sBtlGetAutoSkill_ID(para, 0);
        if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 18 || v129 != wk->para->autost_cnt)
        {
          v62 = wk->para;
          v63 = sBtlGetAutoSkill_ID(v62, 1);
          if (sBtlGetAutoSkillPara(v63, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 18 || v129 != wk->para->autost_cnt)
          {
            v66 = wk->para;
            v67 = sBtlGetAutoSkill_ID(v66, 2);
            if (sBtlGetAutoSkillPara(v67, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 18 || v129 != wk->para->autost_cnt)
            {
              v70 = wk->para;
              v71 = sBtlGetAutoSkill_ID(v70, 3);
              if (sBtlGetAutoSkillPara(v71, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 18 || v129 != wk->para->autost_cnt)
              {
                v74 = wk->para;
                v75 = sBtlGetAutoSkill_ID(v74, 4);
                if (sBtlGetAutoSkillPara(v75, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 18 || v129 != wk->para->autost_cnt)
                {
                  v78 = wk->para;
                  v79 = sBtlGetAutoSkill_ID(v78, 5);
                  if (sBtlGetAutoSkillPara(v79, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 18 || v129 != wk->para->autost_cnt)
                  {
                    v82 = wk->para;
                    v83 = sBtlGetAutoSkill_ID(v82, 6);
                    if (sBtlGetAutoSkillPara(v83, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 18 || v129 != wk->para->autost_cnt)
                    {
                      v86 = wk->para;
                      v87 = sBtlGetAutoSkill_ID(v86, 7);
                      sBtlGetAutoSkillPara(v87, &wk->para->autost_cnt, &wk->para->autost_cnt2);
                    }
                  }
                }
              }
            }
          }
        }
        if ((v15->area & 0x400) == 0)
        {
          if (acter)
          {
            atkunit = acter->para;
            luck = (u32)atkunit->now->luck;
            v91 = wk->para;
            v92 = v91->now->luck;
            if (sklid != 432)
              goto LABEL_176;
          }
          else
          {
            atkunit = 0;
            luck = 0;
            v91 = wk->para;
            v92 = v91->now->luck;
            if (sklid != 432)
            {
LABEL_176:
              v95 = v123;
              if (v50 != 13)
                v95 = 1;
              if ((v95 & 1) == 0)
              {
                if (sklid == 457)
                {
                  v105 = wk->para;
                  if (sBtlGetBadStatus(wk->para) == 16)
                    goto LABEL_190;
                }
                sBtlCheckResetBadStatus(wk);
                if (!flg)
                {
LABEL_230:
                  v13 = 13;
                  sBtlSetBadStatus_No(wk, sklid, 0xDu, 0, v106);
                  return v13;
                }
                goto LABEL_9000;
LABEL_190:
                if (!flg)
                  goto LABEL_230;
LABEL_9000:
                return 13;
              }
              v96 = flg;
              v97 = wk->para;
              side = wk->side;
              aisyo = v97->aisyo;
              v121 = v50;
              v100 = v92;
              v101 = luck;
              LODWORD(luck) = v101;
              v92 = v100;
              v50 = v121;
              v102 = aisyo;
              sklid = v125;
              if (sBtlCheckBadStatus_Hit(v102, luck, v97, v92, v125, v50, v129, side, atkunit))
              {
                if (sBtlCanWeakBstAttach(wk, v50))
                {
                  sBtlCheckResetBadStatus(wk);
                  if (!v96)
                  {
                    sBtlSetBadStatus_No(wk, v125, v50, 0, v110);
                    if (v50 < 5 || v50 == 13)
                    {
                      wk->weak_attrinvtime_cnt = 0;
                      v112 = v124->hstatus;
                      v124->WeakAtkCnt = 0;
                      v124->hstatus = v112 | 0x200000;
                      *(u64 *)&wk->WeakReceiveFlg = 1;
                    }
                  }
                }
                if (v47 == 18)
                {
                  sBtlResetUnit(wk, (s32)v108);
                }
                return v50;
              }
              flg = v96;
              acter = v124;
              v15 = v122;
              v47 = v50;
              goto LABEL_183;
            }
          }
          v94 = luck;
          luck = v94;
          if ((v91->koufunst & 0x20) == 0)
          {
            sBtlCheckResetBadStatus(wk);
            if (!flg)
            {
              sBtlSetBadStatus_No(wk, 432, v50, 0, v113);
            }
            return v50;
          }
          goto LABEL_176;
        }
        v47 = v50;
LABEL_183:
        v46 = v127;
        v93 = v128;
LABEL_184:
        if ((s32)++v47 > 20 || v93)
          return v13;
      }
    }
    return -1;
  }
  return v13;
}

// 0x1ee7aa0
bool sBtlCanWeakBstAttach(SBTLUNIT_WORK *wk, BST bstno) {
  if ((wk->para->badstatus & 0x1F) != 0)
    return 0;
  if (bstno == 13)
  {
    if ((wk->hstatus_old & 0x10) != 0)
      return 0;
  }
  else if (bstno - 1 >= 4 && bstno)
  {
    return 1;
  }
  if (wk->weak_shild > 0)
    return 0;
  return 1;
}

// 0x1edf000
bool sBtlCheckBadStatus_Number(u32 badstatus, s32 bstno, SBTLUNIT_WORK *wk) {
  char v5;
  void *v7;
  void *monitor;
  s64 v10;
  s64 v11;
  bool result;
  s64 v13;
  void *v14;
  s32 v15;
  s32 v16;
  u32 v17;

  v5 = bstno;
  v7 = NewSpecific(uint, 0x13u);
  InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FF4BEE529730C451AABF968ED568175D5DA32D66A1A19AC9FAA4FB284C161DA2, 0);
  monitor = v7[1].monitor;
  v10 = (u32)((u32)monitor - 1);
  if ((s32)monitor < 1)
    return 1;
  v11 = 0;
  while ((*((u32 *)&v7[2].klass + v11) & badstatus) == 0)
  {
    if ((u32)v7[1].monitor == ++v11)
      return 1;
  }
  result = 1;
  if ((s32)v10 >= 1)
  {
    v13 = 0;
    v14 = v7 + 2;
    while (*((u32 *)&v14->klass + v13) != (s64)(1 << v5))
    {
      if (v10 == ++v13)
        return 1;
    }
    v15 = *((u32 *)&v14->klass + v11);
    v16 = *((u32 *)&v7[2].klass + v13);
    if (CheckBadStatusPrioritySame(v15, v16, wk))
      v17 = v11;
    else
      v17 = v13;
    if (*((u32 *)&v7[2].klass + v17) != 32 || *((u32 *)&v14->klass + v11) == 0x20000)
      return v17 > (u32)v11;
    return 1;
  }
  return result;
}

// 0x1ee7b90
static bool CheckBadStatusPrioritySame(BSTF _par1, BSTF _par2, SBTLUNIT_WORK *wk) {
  void *v7;
  s32 v8;
  s32 v9;
  s32 v10;
  _BOOL4 v12;

  v7 = NewSpecific(BSTF, 5u);
  InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__CD82F8CBBAE0E08AD97DD079F1608973F971CABDB23C2762E7366147665A9CFD, 0);
  v8 = IndexOf_Int32Enum_(v7, par1);
  v9 = IndexOf_Int32Enum_(v7, par2);
  v10 = v9;
  v12 = v8 != -1 && v9 != -1;
  if (wk && par1 == 0x2000 && v10 != -1)
    return v12 | ((u8)(wk->hstatus & 0x10) >> 4);
  return v12;
}

// 0x1ee7c90
void sBtlSetBadStatus_Effect(SBTLUNIT_WORK *wk, BST bstno) {
  s32 side;
  s32 v9;

  sBtlResetModelColor(wk);
  sBtlResetModelColor_DST(wk);
  if (!sBtlCheckBadStatus_Color(wk, bstno))
  {
    if (bstno > 0xD)
      return;
    goto LABEL_13;
  }
  sBtlSetBadStatus_Color(wk, bstno);
LABEL_13:
  switch (bstno)
  {
    case 0u:
      side = wk->side;
      v9 = 294;
      goto LABEL_50;
    case 1u:
      side = wk->side;
      v9 = 290;
      goto LABEL_50;
    case 2u:
      side = wk->side;
      v9 = 291;
      goto LABEL_50;
    case 3u:
      side = wk->side;
      v9 = 292;
      goto LABEL_50;
    case 4u:
      side = wk->side;
      v9 = 289;
      goto LABEL_50;
    case 7u:
      side = wk->side;
      v9 = 298;
      goto LABEL_50;
    case 8u:
      side = wk->side;
      v9 = 297;
      goto LABEL_50;
    case 9u:
      side = wk->side;
      v9 = 300;
      goto LABEL_50;
    case 0xAu:
      side = wk->side;
      v9 = 299;
      goto LABEL_50;
    case 0xBu:
      side = wk->side;
      v9 = 295;
      goto LABEL_50;
    case 0xCu:
      side = wk->side;
      v9 = 296;
      goto LABEL_50;
    case 0xDu:
      side = wk->side;
      v9 = 293;
LABEL_50:
      sBtlCheckEffectData(wk, v9, 1u, 0, side, -1, 0);
      wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
      break;
    default:
      return;
  }
}

// 0x1ed8180
bool sBtlSetBadStatus_No(SBTLUNIT_WORK *wk, SKLID sklid, BST badstno, s32 flg, s32 acterID) {
  sdatUnitWork_t *para;
  bool v11;
  sdatParaWork_t *v12;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v21;
  s32 v22;
  s32 v25;
  s32 v26;
  SBTLUNIT_WORK *v28;
  SBTLSKILLP_TBL *v29;
  u32 v30;
  u32 v31;
  s32 v34;
  sdatUnitWork_t *v39;
  sdatUnitWork_t *v44;
  s32 v47;
  s32 v50;
  sdatUnitWork_t *v55;
  sdatUnitWork_t *v60;
  s32 v62;
  u32 attr;
  s16 v67;
  u32 v68;
  s32 v70;
  s32 v71;
  s32 v76;
  sdatUnitWork_t *v77;
  sdatUnitWork_t *v80;
  s32 v81;
  s32 side;
  sdatUnitWork_t *v89;
  s32 EffectSerialID2_Now;
  sdatUnitWork_t *v94;
  s32 badstatus;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v98;
  sdatUnitWork_t *v100;
  s32 v101;
  s32 v102;
  sdatUnitWork_t *v104;
  s16 v105;
  u32 v106;
  s32 v108;
  SBTLSM_LISTWORK *v111;
  SBTLSM_LISTWORK *v112;
  SBTLUNIT_WORK *v113;
  sdatUnitWork_t *v115;
  s32 v116;
  s32 v117;
  u32 v118;
  sdatUnitWork_t *v121;
  s32 v122;
  u32 v124;
  s32 v126;
  s32 v129;
  sdatUnitWork_t *v130;
  u32 v133;
  sdatUnitWork_t *v135;
  s32 v139;
  u32 v140;
  char v142;
  sdatUnitWork_t *v143;
  s16 v144;
  s32 v145;
  sdatUnitWork_t *v149;
  s32 v150;
  u32 v151;
  sdatUnitWork_t *v153;
  s32 v155;
  SBTLSM_LISTWORK *v158;
  sdatUnitWork_t *v160;
  s32 v161;
  s32 attrtime;
  u32 v164;
  sdatUnitWork_t *v171;
  sdatUnitWork_t *v172;
  __int128 v173;
  s32 *v175;
  s32 v176;
  s32 v177;
  SBTLSM_LISTWORK *v180;
  sdatUnitWork_t *v182;
  s32 v184;
  SBTLSM_LISTWORK *v187;
  s32 v190;
  SBATTLE_WORK *v191;
  u32 *v192;
  s32 v193;
  s32 v195;
  SBATTLE_WORK *v196;
  u32 *p_stock_mask;
  s32 v198;
  s32 v199;
  SBTLSM_LISTWORK *v201;
  SBTLSM_LISTWORK *v204;
  SBTLSM_LISTWORK *v205;
  s32 a_pHanshaType;

  a_pHanshaType = 0;
  if (badstno == 16)
  {
    if (wk->encountno != 50)
      goto LABEL_9;
    if ((wk->side & 0x80) != 0)
      return 0;
  }
LABEL_9:
  para = wk->para;
  if (para)
  {
    if ((para->koufunst & 0x20) != 0)
    {
      v11 = 0;
      if (badstno > 0x11 || ((1 << badstno) & 0x30020) == 0)
        return v11;
    }
  }
  v12 = Allocate(sdatParaWork_t);
  _ctor(v12, 0);
  if (badstno == 18)
    return 0;
  Skilltbl = sBtlGetSkilltbl(sklid);
  sBtlReetBadStatus_Color(wk);
  if (wk->major)
    goto LABEL_21;
  goto LABEL_25;
  if (!wk->major)
  {
LABEL_25:
    v11 = 1;
LABEL_26:
    switch (badstno)
    {
      case 0u:
        goto LABEL_27;
      case 1u:
        if (!wk->weak_shild)
        {
          side = wk->side;
          sBtlCheckEffectData(wk, 290, 1u, 0, side, -1, 0);
          wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
          if (sBtlCheckBadStatus_Color(wk, 1u))
          {
            sBtlSetBadStatus_Color(wk, 1u);
          }
        }
        sBtlCheckBadStatus_Weak(wk, sklid, Skilltbl, (s32)v18);
        v28 = wk;
        v29 = Skilltbl;
        v30 = 1;
        goto LABEL_60;
      case 2u:
        goto LABEL_33;
      case 3u:
        goto LABEL_39;
      case 4u:
        goto LABEL_45;
      case 5u:
        goto LABEL_61;
      case 6u:
        if (sBtlCheckBadStatus_Color(wk, 6u))
        {
          sBtlSetBadStatus_Color(wk, 6u);
          v89 = wk->para;
          if (sBtlGetBadStatus(v89) == 9)
            return 0;
          goto LABEL_324;
LABEL_323:
          if (sBtlGetBadStatus(v89) == 9)
            return 0;
LABEL_324:
          v171 = wk->para;
          if (v171 && (v171->koufunst & 0x20) != 0)
            return 0;
          v172 = wk->para;
          *(u64 *)&v173 = 0xA0000000ALL;
          *((u64 *)&v173 + 1) = 0xA0000000ALL;
          v172->badst_cnt3 = 0;
          v172->badstatus |= 0x40u;
          *(u32 *)&v172->badst_cnt = 480;
          v175 = v172->aisyo->para;
          v175[10] = 10;
          *(_OWORD *)v175 = v173;
          *(_OWORD *)&v175[4] = v173;
          *(u64 *)&v175[8] = 0x6400000064LL;
          wk->getMag = 0;
          wk->hstatus &= ~0x10u;
          sBtlSetBadStatusAction(wk, 9, 480);
          if ((wk->side & 0x80) != 0)
            v176 = 138;
          else
            v176 = 1;
          sBtlSetMotion(wk, v176, 0, 0, 0);
          if (flg == 1)
            return v11;
          v177 = wk->side;
          if ((v177 & 0x80) != 0)
          {
            sysmsgList = wk->sysmsgList;
            v98 = 26;
          }
          else
          {
            if ((v177 & 1) == 0)
            {
              v180 = wk->sysmsgList;
              v112 = v180;
              v113 = wk;
              v98 = 28;
              goto LABEL_424;
            }
            sysmsgList = wk->sysmsgList;
            v98 = 27;
          }
LABEL_423:
          v112 = sysmsgList;
          v113 = wk;
LABEL_424:
          sBtlCreateSM(v112, v113, v98, 0, 0, 120);
          return v11;
        }
        v89 = wk->para;
        goto LABEL_323;
      case 7u:
        goto LABEL_67;
      case 8u:
        goto LABEL_74;
      case 9u:
        goto LABEL_81;
      case 0xAu:
        goto LABEL_87;
      case 0xBu:
        goto LABEL_93;
      case 0xCu:
        goto LABEL_100;
      case 0xDu:
        goto LABEL_107;
      case 0xEu:
        goto LABEL_130;
      case 0xFu:
        goto LABEL_138;
      case 0x10u:
        goto LABEL_144;
      case 0x11u:
        goto LABEL_148;
      case 0x13u:
        goto LABEL_155;
      default:
        return v11;
    }
  }
LABEL_21:
  v11 = 1;
  switch (badstno)
  {
    case 0u:
LABEL_27:
      if (wk->weak_shild)
        goto LABEL_57;
      v21 = wk->side;
      v22 = 294;
      goto LABEL_51;
    case 1u:
    case 6u:
      wk->hModel->stat |= 2u;
      v11 = 1;
      if (badstno > 0x13)
        return v11;
      goto LABEL_26;
    case 2u:
LABEL_33:
      if (wk->weak_shild)
        goto LABEL_57;
      v21 = wk->side;
      v22 = 291;
      goto LABEL_51;
    case 3u:
LABEL_39:
      if (wk->weak_shild)
        goto LABEL_57;
      v21 = wk->side;
      v22 = 292;
      goto LABEL_51;
    case 4u:
LABEL_45:
      if (wk->weak_shild)
        goto LABEL_57;
      v21 = wk->side;
      v22 = 289;
LABEL_51:
      sBtlCheckEffectData(wk, v22, 1u, 0, v21, -1, 0);
      wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
      }
LABEL_57:
      sBtlCheckBadStatus_Weak(wk, sklid, Skilltbl, (s32)v18);
      v28 = wk;
      v29 = Skilltbl;
      v30 = badstno;
LABEL_60:
      SetBadStatusCounter(v28, v29, v30, v25, v26);
      WeakBstDvlTk(wk, v31);
      return v11;
    case 5u:
LABEL_61:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        v34 = wk->side;
        goto LABEL_186;
      }
      v34 = wk->side;
LABEL_186:
      sBtlCheckEffectData(wk, 300, 1u, 0, v34, -1, 0);
      EffectSerialID2_Now = sBtlGetEffectSerialID2_Now();
      v94 = wk->para;
      wk->bst_effserialID2 = EffectSerialID2_Now;
      v94->koufun_cnt = 600;
      badstatus = v94->badstatus;
      *(u32 *)&v94->badst_cnt = 0;
      v94->badst_cnt3 = 0;
      if ((badstatus & 0x10000) == 0)
        v94->badstatus = badstatus | (1 << badstno);
      v94->koufunst |= 0x20u;
      if (flg == 1)
        return v11;
      sysmsgList = wk->sysmsgList;
      v98 = 36;
      goto LABEL_423;
    case 7u:
LABEL_67:
      if (!sBtlCheckBadStatus_Color(wk, badstno))
      {
        v39 = wk->para;
        goto LABEL_196;
      }
      sBtlSetBadStatus_Color(wk, badstno);
      v39 = wk->para;
      if (sBtlGetBadStatus(v39) == 9)
        return 0;
      goto LABEL_197;
LABEL_196:
      if (sBtlGetBadStatus(v39) == 9)
        return 0;
LABEL_197:
      v100 = wk->para;
      if (v100 && (v100->koufunst & 0x20) != 0)
        return 0;
      v101 = wk->side;
      sBtlCheckEffectData(wk, 298, 1u, 0, v101, -1, 0);
      wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
      if ((~wk->side & 0x81) != 0)
        v102 = 2;
      else
        v102 = 128;
      sBtlSetMotion(wk, v102, 0, 0, 0);
      v104 = wk->para;
      *(u32 *)&v104->badst_cnt2 = 0;
      v104->badstatus |= 1 << badstno;
      if ((wk->side & 0x80) != 0)
        v105 = 300;
      else
        v105 = 600;
      v104->badst_cnt = v105;
      if (flg != 1)
      {
        sBtlSetBadStatusAction(wk, 9, 1);
        WeakBstDvlTk(wk, v106);
        v108 = wk->side;
        if ((v108 & 0x80) != 0)
        {
          v201 = wk->sysmsgList;
          v112 = v201;
          v113 = wk;
          v98 = 12;
          goto LABEL_424;
        }
        if ((v108 & 1) == 0)
        {
          v111 = wk->sysmsgList;
          v112 = v111;
          v113 = wk;
          v98 = 14;
          goto LABEL_424;
        }
        sysmsgList = wk->sysmsgList;
        v98 = 13;
        goto LABEL_423;
      }
      return v11;
    case 8u:
LABEL_74:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        v44 = wk->para;
        if (sBtlGetBadStatus(v44) == 9)
          return 0;
        goto LABEL_224;
LABEL_223:
        if (sBtlGetBadStatus(v44) == 9)
          return 0;
LABEL_224:
        v115 = wk->para;
        if (v115 && (v115->koufunst & 0x20) != 0)
          return 0;
        v116 = wk->side;
        sBtlCheckEffectData(wk, 297, 1u, 0, v116, -1, 0);
        v117 = sBtlGetEffectSerialID2_Now();
        v121 = wk->para;
        wk->bst_effserialID2 = v117;
        v122 = v121->badstatus;
        v121->badst_cnt3 = 0;
        v121->badstatus = v122 | (1 << badstno);
        *(u32 *)&v121->badst_cnt = 600;
        if (flg == 1)
          return v11;
        if ((wk->side & 0x80) == 0)
        {
          sBtlSetBadStatusAction(wk, 9, 1);
          WeakBstDvlTk(wk, v124);
          v126 = wk->side;
          if ((v126 & 0x80) != 0)
          {
LABEL_236:
            sysmsgList = wk->sysmsgList;
            v98 = 20;
            goto LABEL_423;
          }
LABEL_315:
          if ((v126 & 1) != 0)
          {
            sysmsgList = wk->sysmsgList;
            v98 = 21;
          }
          else
          {
            sysmsgList = wk->sysmsgList;
            v98 = 22;
          }
          goto LABEL_423;
        }
        WeakBstDvlTk(wk, v118);
        v126 = wk->side;
        if ((v126 & 0x80) != 0)
          goto LABEL_236;
        goto LABEL_315;
      }
      v44 = wk->para;
      goto LABEL_223;
    case 9u:
LABEL_81:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        v47 = wk->side;
        goto LABEL_243;
      }
      v47 = wk->side;
LABEL_243:
      sBtlCheckEffectData(wk, 300, 1u, 0, v47, -1, 0);
      v129 = sBtlGetEffectSerialID2_Now();
      v130 = wk->para;
      wk->bst_effserialID2 = v129;
      v130->badstatus |= 1 << badstno;
      v130 = wk->para;
      Clone(v130->backup, 0);
      sBtlCheckBattlePara(wk);
      if (flg == 1)
        return v11;
      v135 = wk->para;
      *(u32 *)&v135->badst_cnt = 1800;
      v135->badst_cnt3 = 0;
      WeakBstDvlTk(wk, v133);
      if ((wk->side & 0x80) != 0)
      {
        goto LABEL_251;
      }
      else
      {
LABEL_251:
        sysmsgList = wk->sysmsgList;
        v98 = 183;
        goto LABEL_423;
      }
      goto LABEL_251;
    case 0xAu:
LABEL_87:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        v50 = wk->side;
LABEL_256:
        sBtlCheckEffectData(wk, 299, 1u, 0, v50, -1, 0);
        v139 = sBtlGetEffectSerialID2_Now();
        v142 = wk->side;
        wk->bst_effserialID2 = v139;
        v143 = wk->para;
        *(u32 *)&v143->badst_cnt2 = 0;
        if (v142 < 0)
          v144 = 900;
        else
          v144 = 1800;
        v143->badst_cnt = v144;
        v143->badstatus |= 1 << badstno;
        if (flg == 1)
          return v11;
        WeakBstDvlTk(wk, v140);
        v145 = wk->side;
        if ((v145 & 0x80) != 0)
        {
          sysmsgList = wk->sysmsgList;
          v98 = 23;
        }
        else
        {
          if ((v145 & 1) != 0)
          {
            v187 = wk->sysmsgList;
            v112 = v187;
            v113 = wk;
            v98 = 24;
            goto LABEL_424;
          }
          sysmsgList = wk->sysmsgList;
          v98 = 25;
        }
        goto LABEL_423;
      }
      v50 = wk->side;
      goto LABEL_256;
    case 0xBu:
LABEL_93:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        v55 = wk->para;
        if (sBtlGetBadStatus(v55) == 9)
          return 0;
        goto LABEL_272;
      }
      v55 = wk->para;
      if (sBtlGetBadStatus(v55) == 9)
        return 0;
LABEL_272:
      v149 = wk->para;
      if (v149 && (v149->koufunst & 0x20) != 0)
        return 0;
      v150 = wk->side;
      sBtlCheckEffectData(wk, 295, 1u, 0, v150, -1, 0);
      wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
      if (flg == 1)
        return v11;
      v153 = wk->para;
      v153->badst_cnt3 = 0;
      v153->badstatus |= 1 << badstno;
      *(u32 *)&v153->badst_cnt = 1800;
      WeakBstDvlTk(wk, v151);
      v155 = wk->side;
      if ((v155 & 0x80) == 0)
      {
        if ((v155 & 1) != 0)
        {
          v205 = wk->sysmsgList;
          v112 = v205;
          v113 = wk;
          v98 = 30;
        }
        else
        {
          v158 = wk->sysmsgList;
          v112 = v158;
          v113 = wk;
          v98 = 31;
        }
        goto LABEL_424;
      }
      sysmsgList = wk->sysmsgList;
      v98 = 29;
      goto LABEL_423;
    case 0xCu:
LABEL_100:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        v60 = wk->para;
        if (sBtlGetBadStatus(v60) == 9)
          return 0;
        goto LABEL_291;
LABEL_290:
        if (sBtlGetBadStatus(v60) == 9)
          return 0;
LABEL_291:
        v160 = wk->para;
        if (v160 && (v160->koufunst & 0x20) != 0)
          return 0;
        v161 = wk->side;
        sBtlCheckEffectData(wk, 296, 1u, 0, v161, -1, 0);
        wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
        attrtime = Skilltbl->attrtime;
        sBtlSetBadStatusAction(wk, 33, attrtime);
        if ((wk->side & 0x80) == 0)
        {
          sBtlSetMotion(wk, 2, 0, 0, 0);
          if (flg == 1)
            return v11;
          goto LABEL_345;
        }
        if (flg == 1)
          return v11;
LABEL_345:
        v182 = wk->para;
        v182->badst_cnt3 = 0;
        v182->badstatus |= 1 << badstno;
        *(u32 *)&v182->badst_cnt = 900;
        WeakBstDvlTk(wk, v164);
        v184 = wk->side;
        if ((v184 & 0x80) != 0)
        {
          v204 = wk->sysmsgList;
          v112 = v204;
          v113 = wk;
          v98 = 16;
          goto LABEL_424;
        }
        if ((v184 & 1) != 0)
        {
          sysmsgList = wk->sysmsgList;
          v98 = 17;
        }
        else
        {
          sysmsgList = wk->sysmsgList;
          v98 = 18;
        }
        goto LABEL_423;
      }
      v60 = wk->para;
      goto LABEL_290;
    case 0xDu:
LABEL_107:
      if (!wk->weak_shild)
      {
        v62 = wk->side;
        sBtlCheckEffectData(wk, 293, 1u, 0, v62, -1, 0);
        wk->bst_effserialID2 = sBtlGetEffectSerialID2_Now();
        if (sBtlCheckBadStatus_Color(wk, badstno))
        {
          sBtlSetBadStatus_Color(wk, badstno);
        }
      }
      attr = Skilltbl->attr;
      a_pHanshaType = 0;
      if ((attr & 0x401) != 0)
      {
        v67 = sBtlCheckAisyoEx(wk, attr, &a_pHanshaType);
        if ((v67 & 0x4000) != 0)
        {
          sBtlCheckBadStatus_Weak(wk, sklid, Skilltbl, (s32)v18);
        }
      }
      SetBadStatusCounter(wk, Skilltbl, badstno, (s32)(s32)v18);
      WeakBstDvlTk(wk, v68);
      sBtlDmg_BossDYING(wk);
      return v11;
    case 0xEu:
LABEL_130:
      sBtlSetMotion(wk, 1, 0, 0, 0);
      SetBadStatusCounter(wk, Skilltbl, badstno, v70, v71);
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
      }
      return v11;
    case 0xFu:
LABEL_138:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        if ((wk->side & 1) == 0)
          return v11;
LABEL_305:
        v80 = wk->para;
        v81 = 600;
        goto LABEL_377;
      }
      if ((wk->side & 1) == 0)
        return v11;
      goto LABEL_305;
    case 0x10u:
LABEL_144:
      v76 = wk->side;
      if ((v76 & 0x81) == 1)
      {
        v77 = wk->para;
        v77->badst_cnt3 = 3600;
        v77->badstatus |= 1 << badstno;
        *(u32 *)&v77->badst_cnt = 600;
        sBtlSetBadStatusAction(wk, 46, 600);
        wk->status |= 0x4001u;
        return v11;
      }
      if ((v76 & 0x80) == 0)
        return v11;
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
        if (!sBtlGetNakama(0))
        {
LABEL_368:
          if (sBtlGetNakama(1))
          {
            v195 = wk->summonindex[1];
            SetReturn(v195, 0);
            v196 = wk;
            p_stock_mask = &v196->stock_mask;
            v198 = v196->summonindex[1];
            sBtlResetBit(p_stock_mask, v198);
          }
          v80 = wk->para;
          v81 = 9999;
LABEL_377:
          v199 = v80->badstatus;
          v80->badst_cnt3 = 0;
          v80->badstatus = v199 | (1 << badstno);
          *(u32 *)&v80->badst_cnt = v81;
          return v11;
        }
LABEL_361:
        v190 = wk->summonindex[0];
        SetReturn(v190, 0);
        v191 = wk;
        v192 = &v191->stock_mask;
        v193 = v191->summonindex[0];
        sBtlResetBit(v192, v193);
        goto LABEL_368;
      }
      if (!sBtlGetNakama(0))
        goto LABEL_368;
      goto LABEL_361;
    case 0x11u:
LABEL_148:
      if (sBtlCheckBadStatus_Color(wk, badstno))
      {
        sBtlSetBadStatus_Color(wk, badstno);
      }
      v80 = wk->para;
      v81 = 360;
      goto LABEL_377;
    case 0x13u:
LABEL_155:
      wk->para->badstatus |= 1 << badstno;
      return v11;
    default:
      return v11;
  }
}

// 0x1ee7f90
static void WeakBstDvlTk(SBTLUNIT_WORK *wk, BST badno) {
  SBTLDVLTK_LISTWORK *dvltkList;

  dvltkList = wk->dvltkList;
  sBtlCreateDvltk_Priority(dvltkList, wk, 14);
}

// 0x1ed5fc0
TEXCOLOR_WORK *sBtlGetBSTColortbl(SBTLUNIT_WORK *wk, BST badstno) {
  TEXCOLOR_WORK *bstcolor_tbldata_local;
  TEXCOLOR_WORK **p_bstcolor_tbldata_raidou;

  bstcolor_tbldata_local = bstcolor_tbldata;
  if (!bstcolor_tbldata_local)
    return 0;
  if ((wk->side & 0x80) != 0)
  {
    p_bstcolor_tbldata_raidou = &bstcolor_tbldata_raidou;
    goto LABEL_13;
  }
  p_bstcolor_tbldata_raidou = &bstcolor_tbldata;
LABEL_13:
  bstcolor_tbldata_local = *p_bstcolor_tbldata_raidou;
  return bstcolor_tbldata_local[badstno];
}

// 0x1edf1b0
bool sBtlCheckBadStatus_Hit(SBTLAISYO_DATAWORK *aisyo_tbl, s32 aluck, sdatUnitWork_t *unit, s32 tluck, SKLID skillid, BST bstno, s32 attr, u8 side, sdatUnitWork_t *atkunit) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v20;
  u32 v21;
  s32 v22;
  bool result;
  s64 v24;
  SBTLAISYO_DATAWORK *aisyo_tbldata_local;
  s32 devilid;
  Il2CppClass **v28;
  f32 v29;
  s16 *p_autost_cnt2;
  s32 AutoSkill_ID;
  s32 v34;
  s32 v37;
  s32 v40;
  s32 v43;
  s32 v46;
  s32 v49;
  s32 v52;
  s16 *v55;
  s32 v56;
  s32 v59;
  s32 v62;
  s32 v65;
  s32 v68;
  s32 v71;
  s32 v74;
  s32 v77;
  s32 v80;
  s32 v81;
  f32 v84;
  f32 v85;
  s32 v86;
  s32 v87;
  u8 v88;

  Skilltbl = sBtlGetSkilltbl(skillid);
  v20 = Skilltbl;
  if (skillid == 1193 && !unit->devilid)
    return 0;
  v21 = Skilltbl->attr;
  if ((v21 & 1) != 0)
  {
    if ((v21 & 0x20000) != 0 || (aisyo_tbl->para[0] & 0x20000) != 0)
      return 0;
  }
  else if ((aisyo_tbl->para[attr] & 0x23000) != 0)
  {
    return 0;
  }
  if ((bstno & 0xFFFFFFFE) != 0x10)
  {
    if (!unit)
      goto LABEL_16;
    if ((unit->koufunst & 0x20) == 0)
      goto LABEL_16;
    return 0;
  }
LABEL_16:
  v22 = aisyo_tbl->para[attr];
  if (bstno == 13 && (v22 & 0x4000) != 0)
    return 0;
  v24 = attr;
  if (bstno < 5)
    goto LABEL_21;
  if (bstno != 16)
  {
    if (bstno != 13)
      goto LABEL_41;
LABEL_21:
    if ((unit->badstatus & 0x40) != 0)
    {
      v88 = side;
      aisyo_tbldata_local = aisyo_tbldata;
      devilid = unit->devilid;
      v28 = &aisyo_tbldata_local->obj.klass + sBtlGetDevilData(devilid, -1)->aishou;
      side = v88;
      if ((*(u32 *)&v28[4]->_1.name[4 * v24 + 32] & 0x4000) == 0)
      {
LABEL_23:
        if (skillid <= 443)
        {
          result = 0;
          if ((u32)(skillid - 427) > 0x10 || ((1 << (skillid + 85)) & 0x10021) == 0)
            return result;
        }
        else if (skillid != 450 && skillid != 903 && skillid != 1131)
        {
          return 0;
        }
LABEL_41:
        v29 = (f32)((f32)((f32)((f32)v20->percentage / 100.0) * (f32)(2 * aluck + 100)) / (f32)(2 * tluck + 100))
            * (f32)(aisyo_tbl->para[v24] & 0xFFF);
        if (!atkunit)
          goto LABEL_79;
        p_autost_cnt2 = &atkunit->autost_cnt2;
        AutoSkill_ID = sBtlGetAutoSkill_ID(atkunit, 0);
        if (sBtlGetAutoSkillPara(AutoSkill_ID, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        v34 = sBtlGetAutoSkill_ID(atkunit, 1);
        if (sBtlGetAutoSkillPara(v34, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        v37 = sBtlGetAutoSkill_ID(atkunit, 2);
        if (sBtlGetAutoSkillPara(v37, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        v40 = sBtlGetAutoSkill_ID(atkunit, 3);
        if (sBtlGetAutoSkillPara(v40, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        v43 = sBtlGetAutoSkill_ID(atkunit, 4);
        if (sBtlGetAutoSkillPara(v43, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        v46 = sBtlGetAutoSkill_ID(atkunit, 5);
        if (sBtlGetAutoSkillPara(v46, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        v49 = sBtlGetAutoSkill_ID(atkunit, 6);
        if (sBtlGetAutoSkillPara(v49, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        v52 = sBtlGetAutoSkill_ID(atkunit, 7);
        if (sBtlGetAutoSkillPara(v52, &atkunit->autost_cnt, &atkunit->autost_cnt2) == 17)
        {
          v29 = v29 * (f32)((f32)*p_autost_cnt2 / 100.0);
        }
        else
        {
          if (!sBtlChkHaveMemSkl(atkunit, 31))
          {
LABEL_79:
            v55 = &unit->autost_cnt2;
            v56 = sBtlGetAutoSkill_ID(unit, 0);
            if (sBtlGetAutoSkillPara(v56, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            v59 = sBtlGetAutoSkill_ID(unit, 1);
            if (sBtlGetAutoSkillPara(v59, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            v62 = sBtlGetAutoSkill_ID(unit, 2);
            if (sBtlGetAutoSkillPara(v62, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            v65 = sBtlGetAutoSkill_ID(unit, 3);
            if (sBtlGetAutoSkillPara(v65, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            v68 = sBtlGetAutoSkill_ID(unit, 4);
            if (sBtlGetAutoSkillPara(v68, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            v71 = sBtlGetAutoSkill_ID(unit, 5);
            if (sBtlGetAutoSkillPara(v71, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            v74 = sBtlGetAutoSkill_ID(unit, 6);
            if (sBtlGetAutoSkillPara(v74, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            v77 = sBtlGetAutoSkill_ID(unit, 7);
            if (sBtlGetAutoSkillPara(v77, &unit->autost_cnt, &unit->autost_cnt2) == 86)
              v29 = v29 * (f32)((f32)*v55 / 100.0);
            if ((side & 2) != 0)
            {
              v81 = 10;
LABEL_130:
              v84 = 0.0;
              if (v29 != INFINITY)
                v84 = (s32)v29;
              v85 = ConvLevelValue(v81, v84);
              v86 = v85;
              if ((s32)v85 <= 1)
                v86 = 1;
              if (v85 == INFINITY)
                v87 = 1;
              else
                v87 = v86;
              return v87 > (s16)GetPercentage();
            }
            else
            {
              if (bstno == 17)
                v80 = 11;
              else
                v80 = 13;
              if ((side & 0x80u) != 0)
                v81 = v80;
              else
                v81 = v80 + 1;
              goto LABEL_130;
            }
            goto LABEL_130;
          }
LABEL_78:
          v29 = v29 + (f32)atkunit->now->luck;
          goto LABEL_79;
        }
        if (!sBtlChkHaveMemSkl(atkunit, 31))
          goto LABEL_79;
        goto LABEL_78;
      }
    }
    else if ((v22 & 0x4000) == 0)
    {
      goto LABEL_23;
    }
    return 1;
  }
  return (side & 0x80u) == 0 || wk->encountno != 50;
}

// 0x1ee8060
s32 sBtlGetDamage_GB(sdatUnitWork_t *acter, sdatUnitWork_t *target, SKLID skillid) {
  SBTLCALC_DMGWORK *v6;
  sdatParaWork_t *v7;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v10;
  s32 v11;
  u32 flg;
  u32 badst;
  s32 badstatus;
  s32 v15;
  sdatUnitWork_t *para;
  s32 n0;
  sdatParaWork_t *now;
  s32 level;
  sdatParaWork_t *v21;
  s32 v22;
  f32 maxhp;
  f32 v24;
  s32 max_damage;
  f32 v26;
  f32 v28;
  s32 v29;
  s32 v31;
  s32 i;
  s32 AutoSkill_ID;
  s32 AutoSkillPara;
  s32 v37;
  s32 autost_cnt;
  s32 autost_cnt2;
  s32 v40;
  u32 v41;
  u32 v42;
  s32 v43;
  s32 koufunst;
  u32 v45;
  s32 v48;
  f32 v49;
  s32 v50;
  sdatParaWork_t *v51;
  s32 *p_hp;
  s32 hp;
  s32 v54;
  sdatParaWork_t *v55;
  s32 *p_mp;
  s32 mp;
  s32 v58;
  SBTLSKILLP_TBL *v60;
  s32 x;

  x = 0;
  v6 = Allocate(SBTLCALC_DMGWORK);
  v7 = Allocate(sdatParaWork_t);
  _ctor(v7, 0);
  Skilltbl = sBtlGetSkilltbl(skillid);
  v10 = Skilltbl;
  v11 = Skilltbl->type & 0xFFF;
  if (v11 != 5 && v11 != 3)
    goto LABEL_29;
  flg = Skilltbl->flg;
  if ((flg & 4) == 0)
    goto LABEL_30;
  if ((flg & 0x10000) != 0)
  {
    badst = v10->badst;
    badstatus = target->badstatus;
    if ((badstatus & badst) != 0)
    {
      target->badst_cnt = 0;
      target->badstatus = badstatus & ~badst;
    }
    flg = v10->flg;
  }
  if ((flg & 0x2000) == 0)
  {
    v15 = target->badstatus;
    if ((v15 & 0x100000) == 0 && ((v15 & 0x10000) == 0 || !target->devilid))
    {
      *(u32 *)&v6->damage_per = 1065353216;
      para = sBtlGetPlayerData()->para;
      ClassClear(v7, 0);
      sBtlGetPlayerTec_ParaUp(para, v7);
      n0 = v10->n0;
      now = acter->now;
      v6->n0 = n0;
      level = acter->level;
      v6->alevel = acter->level;
      v21 = target->now;
      LODWORD(now) = v7->tec + now->tec;
      v22 = v7->luck + v21->luck;
      v6->side = 1;
      v6->atec = (u32)now;
      v6->tluck = v22;
      maxhp = v21->maxhp;
      v24 = v6->damage_per;
      max_damage = v10->max_damage;
      v6->tmaxhp = maxhp;
      v26 = (f32)((f32)((f32)n0 / 100.0) * maxhp)
          + (f32)((f32)((f32)((f32)level * 0.5) + (f32)((f32)(s32)now * 1.5)) + (f32)((f32)v22 * 1.5));
      v28 = v24 * (f32)(v26 + 20.0);
      v29 = v28;
      if (v28 == INFINITY)
        v29 = 0x80000000;
      x = v29;
      LimitRange(&x, 0, max_damage);
      goto LABEL_30;
    }
LABEL_29:
    x = 0;
    goto LABEL_30;
  }
  v6->n1 = v10->n1;
  v31 = target->badstatus;
  if ((v31 & 0x100000) != 0)
    goto LABEL_29;
  if ((v31 & 0x10000) != 0 && target->devilid)
    goto LABEL_29;
  v49 = (f32)(v6->n1 / 100.0) * (f32)target->now->maxhp;
  v50 = v49;
  if (v49 == INFINITY)
    v50 = 0x80000000;
  x = v50;
LABEL_30:
  v60 = v10;
  for (i = 0; i != 8; ++i)
  {
    AutoSkill_ID = sBtlGetAutoSkill_ID(acter, i);
    AutoSkillPara = sBtlGetAutoSkillPara(AutoSkill_ID, &acter->autost_cnt, &acter->autost_cnt2);
    if ((u32)(AutoSkillPara - 13) < 4 || AutoSkillPara == 54)
    {
      v37 = x;
      autost_cnt = acter->autost_cnt;
      autost_cnt2 = acter->autost_cnt2;
      v40 = CalcAutoSkill(target, AutoSkillPara, v37, skillid, autost_cnt, autost_cnt2);
      if (v40)
        x = v40;
    }
  }
  v41 = v10->flg;
  if ((v41 & 4) != 0)
  {
    if ((v41 & 0x10000) != 0)
    {
      v42 = v10->badst;
      v43 = target->badstatus;
      target->badst_cnt = 0;
      target->badstatus = v43 & ~v42;
      if (v42 == 0x3FFFF || v42 == 32)
      {
        koufunst = target->koufunst;
        target->koufun_cnt = 0;
        target->koufunst = koufunst & ~v42;
      }
    }
    if ((v10->s_type & 8) == 0)
    {
      v45 = v10->flg;
      if ((v45 & 0x3000) == 0)
        goto LABEL_66;
      if (wk)
      {
        v48 = x;
        if ((wk->status3 & 0x8000000) != 0)
        {
          v48 = x / 2;
          x /= 2;
        }
        goto LABEL_63;
      }
      v48 = x;
LABEL_63:
      v51 = target->now;
      hp = v51->hp;
      p_hp = &v51->hp;
      *p_hp = v48 + hp;
      v54 = p_hp[1];
      LimitRange(p_hp, 0, v54);
      v45 = v60->flg;
LABEL_66:
      if ((v45 & 0xC000) != 0)
      {
        v55 = target->now;
        mp = v55->mp;
        p_mp = &v55->mp;
        *p_mp = x + mp;
        v58 = p_mp[1];
        LimitRange(p_mp, 0, v58);
      }
    }
  }
  return x;
}

// 0x1ee8810
void sBtlKudaDmg(s8 kuda, s32 *pDmg) {
  void *v5;
  s64 v7;
  s64 v8;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 v12;
  sdatUnitWork_t *para;
  s32 v14;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLAUTO_TBL *v19;
  s32 v20;
  s64 v21;

  v5 = NewSpecific(s32, 8u);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FD26F52E3411331087533B075CD62AD2D7891C5700ACCEC3203147501B0837A5, 0);
  if (kuda <= 7 && kuda)
  {
    v7 = 0;
    v8 = *((char *)&v5[2].klass + 4 * kuda);
    while (1)
    {
      UnitMng = wk->UnitMng;
      if (v7 >= UnitMng->number)
        return;
      v21 = v7;
      pUnit = UnitMng->pUnitL[v7]->pUnit;
      if (pUnit)
        goto LABEL_14;
LABEL_6:
      v7 = v21 + 1;
    }
    v21 = v7;
    pUnit = wk->UnitMng->pUnitL[v7]->pUnit;
    if (!pUnit)
      goto LABEL_6;
LABEL_14:
    v12 = 32;
    *(u32 *)&pUnit->para->autost_cnt = 0;
    while (1)
    {
      para = pUnit->para;
      v14 = *(u32 *)((char *)&para->aOmoideSkill->obj.klass + v12);
      if (sBtlGetAutoSkillPara(v14, &para->autost_cnt, &para->autost_cnt2) == 19)
      {
        Skilltbl = sBtlGetSkilltbl(v14);
        if ((Skilltbl->flg2 & 0x8000000) == 0)
        {
          v19 = ((char *)autotbldata + 8 * sBtlGetSkilltbl(v14)->weapontype);
LABEL_27:
          v20 = v19[0]->m_aisyo->para[v8];
          if (v20)
            *pDmg = *pDmg * v20 / 100;
          goto LABEL_15;
        }
        v19 = autotbldata;
        goto LABEL_27;
      }
LABEL_15:
      v12 += 4;
      if (v12 == 64)
        goto LABEL_6;
    }
  }
}

// 0x1ee8b10
void sBtlFullMoonDmg(s32 *pDmg, SBTLUNIT_WORK *pAtkr) {
  u16 *v5;
  sdatUnitWork_t *v7;
  s16 *v8;
  s16 *v9;
  s32 v10;
  sdatUnitWork_t *p_para;
  u32 v13;
  sdatUnitWork_t *v14;
  s64 v15;
  u16 *v16;
  sdatUnitWork_t *para;
  s16 *p_autost_cnt;
  s16 *p_autost_cnt2;
  s32 v21;
  s32 AutoSkillPara;
  sdatUnitWork_t *v24;
  s64 v25;
  s16 *v26;
  s16 *v27;
  s32 v28;
  s32 v29;
  sdatUnitWork_t *v31;
  s64 v32;
  s16 *v33;
  s16 *v34;
  s32 v35;
  s32 v36;
  sdatUnitWork_t *v38;
  s64 v39;
  s16 *v40;
  s16 *v41;
  s32 v42;
  s32 v43;
  sdatUnitWork_t *v45;
  s64 v46;
  s16 *v47;
  s16 *v48;
  s32 v49;
  s32 v50;
  sdatUnitWork_t *v52;
  s64 v53;
  s16 *v54;
  s16 *v55;
  s32 v56;
  s32 v57;
  sdatUnitWork_t *v59;
  s64 v60;
  s16 *v61;
  s16 *v62;
  s32 v63;
  s32 v64;
  sdatUnitWork_t *v66;
  s64 v67;
  s16 *v68;
  s16 *v69;
  s32 v70;
  s16 *v71;
  s16 *v72;
  s32 v73;
  u32 v75;
  sdatUnitWork_t *v76;
  s64 v77;
  s16 *v78;
  s16 *v79;
  s32 v80;
  u32 v82;
  sdatUnitWork_t *v83;
  s64 v84;
  s16 *v85;
  s16 *v86;
  s32 v87;
  u32 v89;
  sdatUnitWork_t *v90;
  s64 v91;
  s16 *v92;
  s16 *v93;
  s32 v94;
  u32 v96;
  sdatUnitWork_t *v97;
  s64 v98;
  s16 *v99;
  s16 *v100;
  s32 v101;
  u32 v103;
  sdatUnitWork_t *v104;
  s64 v105;
  s16 *v106;
  s16 *v107;
  s32 v108;
  u32 v110;
  sdatUnitWork_t *v111;
  s64 v112;
  s16 *v113;
  s16 *v114;
  s32 v115;
  u32 v116;
  s64 v117;

  if (!pAtkr)
    return;
  v5 = NewSpecific(ushort, 9u);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
  if (!evtBitCheck(v5[8]))
  {
    v16 = NewSpecific(ushort, 9u);
    InitializeArray_55364416(v16, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
    if (evtBitCheck(v16[0]))
    {
      para = pAtkr->para;
      p_para = &pAtkr->para;
      p_autost_cnt = &para->autost_cnt;
      p_autost_cnt2 = &para->autost_cnt2;
      v21 = para->aOmoideSkill[0];
      AutoSkillPara = sBtlGetAutoSkillPara(v21, p_autost_cnt, p_autost_cnt2);
      v24 = p_para;
      if (AutoSkillPara == 75)
      {
        v25 = 1374389535 * *pDmg * v24->autost_cnt2;
        *pDmg = (v25 >> 37) + ((u64)v25 >> 63);
      }
      v26 = &v24->autost_cnt;
      v27 = &v24->autost_cnt2;
      v28 = v24->aOmoideSkill[1];
      v29 = sBtlGetAutoSkillPara(v28, v26, v27);
      v31 = p_para;
      if (v29 == 75)
      {
        v32 = 1374389535 * *pDmg * v31->autost_cnt2;
        *pDmg = (v32 >> 37) + ((u64)v32 >> 63);
      }
      v33 = &v31->autost_cnt;
      v34 = &v31->autost_cnt2;
      v35 = v31->aOmoideSkill[2];
      v36 = sBtlGetAutoSkillPara(v35, v33, v34);
      v38 = p_para;
      if (v36 == 75)
      {
        v39 = 1374389535 * *pDmg * v38->autost_cnt2;
        *pDmg = (v39 >> 37) + ((u64)v39 >> 63);
      }
      v40 = &v38->autost_cnt;
      v41 = &v38->autost_cnt2;
      v42 = v38->aOmoideSkill[3];
      v43 = sBtlGetAutoSkillPara(v42, v40, v41);
      v45 = p_para;
      if (v43 == 75)
      {
        v46 = 1374389535 * *pDmg * v45->autost_cnt2;
        *pDmg = (v46 >> 37) + ((u64)v46 >> 63);
      }
      v47 = &v45->autost_cnt;
      v48 = &v45->autost_cnt2;
      v49 = v45->aOmoideSkill[4];
      v50 = sBtlGetAutoSkillPara(v49, v47, v48);
      v52 = p_para;
      if (v50 == 75)
      {
        v53 = 1374389535 * *pDmg * v52->autost_cnt2;
        *pDmg = (v53 >> 37) + ((u64)v53 >> 63);
      }
      v54 = &v52->autost_cnt;
      v55 = &v52->autost_cnt2;
      v56 = v52->aOmoideSkill[5];
      v57 = sBtlGetAutoSkillPara(v56, v54, v55);
      v59 = p_para;
      if (v57 == 75)
      {
        v60 = 1374389535 * *pDmg * v59->autost_cnt2;
        *pDmg = (v60 >> 37) + ((u64)v60 >> 63);
      }
      v61 = &v59->autost_cnt;
      v62 = &v59->autost_cnt2;
      v63 = v59->aOmoideSkill[6];
      v64 = sBtlGetAutoSkillPara(v63, v61, v62);
      v66 = p_para;
      if (v64 == 75)
      {
        v67 = 1374389535 * *pDmg * v66->autost_cnt2;
        *pDmg = (v67 >> 37) + ((u64)v67 >> 63);
      }
      v68 = &v66->autost_cnt;
      v69 = &v66->autost_cnt2;
      v70 = v66->aOmoideSkill[7];
      if (sBtlGetAutoSkillPara(v70, v68, v69) == 75)
        goto LABEL_93;
    }
    return;
  }
  v7 = pAtkr->para;
  v8 = &v7->autost_cnt;
  v9 = &v7->autost_cnt2;
  v10 = v7->aOmoideSkill[0];
  p_para = &pAtkr->para;
  v13 = sBtlGetAutoSkillPara(v10, v8, v9) - 40;
  if (v13 <= 0x23 && ((1 << v13) & 0x800000005LL) != 0)
  {
    v14 = p_para;
    v15 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v15 >> 37) + ((u64)v15 >> 63);
  }
  else
  {
    v14 = p_para;
  }
  v71 = &v14->autost_cnt;
  v72 = &v14->autost_cnt2;
  v73 = v14->aOmoideSkill[1];
  v75 = sBtlGetAutoSkillPara(v73, v71, v72) - 40;
  if (v75 <= 0x23 && ((1 << v75) & 0x800000005LL) != 0)
  {
    v76 = p_para;
    v77 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v77 >> 37) + ((u64)v77 >> 63);
  }
  else
  {
    v76 = p_para;
  }
  v78 = &v76->autost_cnt;
  v79 = &v76->autost_cnt2;
  v80 = v76->aOmoideSkill[2];
  v82 = sBtlGetAutoSkillPara(v80, v78, v79) - 40;
  if (v82 <= 0x23 && ((1 << v82) & 0x800000005LL) != 0)
  {
    v83 = p_para;
    v84 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v84 >> 37) + ((u64)v84 >> 63);
  }
  else
  {
    v83 = p_para;
  }
  v85 = &v83->autost_cnt;
  v86 = &v83->autost_cnt2;
  v87 = v83->aOmoideSkill[3];
  v89 = sBtlGetAutoSkillPara(v87, v85, v86) - 40;
  if (v89 <= 0x23 && ((1 << v89) & 0x800000005LL) != 0)
  {
    v90 = p_para;
    v91 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v91 >> 37) + ((u64)v91 >> 63);
  }
  else
  {
    v90 = p_para;
  }
  v92 = &v90->autost_cnt;
  v93 = &v90->autost_cnt2;
  v94 = v90->aOmoideSkill[4];
  v96 = sBtlGetAutoSkillPara(v94, v92, v93) - 40;
  if (v96 <= 0x23 && ((1 << v96) & 0x800000005LL) != 0)
  {
    v97 = p_para;
    v98 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v98 >> 37) + ((u64)v98 >> 63);
  }
  else
  {
    v97 = p_para;
  }
  v99 = &v97->autost_cnt;
  v100 = &v97->autost_cnt2;
  v101 = v97->aOmoideSkill[5];
  v103 = sBtlGetAutoSkillPara(v101, v99, v100) - 40;
  if (v103 <= 0x23 && ((1 << v103) & 0x800000005LL) != 0)
  {
    v104 = p_para;
    v105 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v105 >> 37) + ((u64)v105 >> 63);
  }
  else
  {
    v104 = p_para;
  }
  v106 = &v104->autost_cnt;
  v107 = &v104->autost_cnt2;
  v108 = v104->aOmoideSkill[6];
  v110 = sBtlGetAutoSkillPara(v108, v106, v107) - 40;
  if (v110 <= 0x23 && ((1 << v110) & 0x800000005LL) != 0)
  {
    v111 = p_para;
    v112 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v112 >> 37) + ((u64)v112 >> 63);
  }
  else
  {
    v111 = p_para;
  }
  v113 = &v111->autost_cnt;
  v114 = &v111->autost_cnt2;
  v115 = v111->aOmoideSkill[7];
  v116 = sBtlGetAutoSkillPara(v115, v113, v114) - 40;
  if (v116 <= 0x23 && ((1 << v116) & 0x800000005LL) != 0)
  {
LABEL_93:
    v117 = 1374389535 * *pDmg * p_para->autost_cnt2;
    *pDmg = (v117 >> 37) + ((u64)v117 >> 63);
  }
}

// 0x1ee9380
void sBtlZokuseiDmg(s32 *pDmg, SBTLUNIT_WORK *pTgt, s32 attr) {
  s32 v7;
  s32 v8;
  s64 v9;
  sdatUnitWork_t *para;
  s32 v11;
  s32 AutoSkillPara;
  char flg2_high;
  SBTLAUTO_TBL *v17;
  u16 *v18;
  char v19;
  u32 v20;
  SBTLAUTO_TBL *v21;
  SBTLAUTO_TBL *v22;
  SBTLSKILLP_TBL *Skilltbl;
  u32 v24;
  SBTLAUTO_TBL *m_Items;
  s64 v26;
  s32 v27;
  s64 v28;

  if (pTgt && (attr & 0x80000000) == 0)
  {
    if ((attr & 0x8000) != 0)
      v7 = 15;
    else
      v7 = -1;
    v8 = (attr & 1) == 0;
    if ((attr & 3) == 0)
      v8 = 2;
    if ((attr & 7) == 0)
      v8 = 3;
    if ((attr & 0xF) == 0)
      v8 = 4;
    if ((attr & 0x1F) == 0)
      v8 = 5;
    if ((attr & 0x3F) == 0)
      v8 = 6;
    if ((attr & 0x7F) == 0)
      v8 = 7;
    if (!(u8)attr)
      v8 = 8;
    if ((attr & 0x1FF) == 0)
      v8 = 9;
    if ((attr & 0x3FF) == 0)
      v8 = 10;
    if ((attr & 0x7FF) == 0)
      v8 = 11;
    if ((attr & 0xFFF) == 0)
      v8 = 12;
    if ((attr & 0x1FFF) == 0)
      v8 = 13;
    if ((attr & 0x4000) != 0)
      v7 = 14;
    if ((attr & 0x3FFF) != 0)
      v7 = v8;
    v28 = v7;
    v9 = 32;
    while (1)
    {
      para = pTgt->para;
      v11 = *(u32 *)((char *)&para->aOmoideSkill->obj.klass + v9);
      AutoSkillPara = sBtlGetAutoSkillPara(v11, &para->autost_cnt, &para->autost_cnt2);
      if ((u32)(AutoSkillPara - 43) <= 0xFFFFFFFD)
      {
        if ((u32)(AutoSkillPara - 53) <= 0xFFFFFFFD)
        {
          if (AutoSkillPara != 74 || (pTgt->status & 0x100) == 0)
            goto LABEL_37;
          flg2_high = HIBYTE(sBtlGetSkilltbl(v11)->flg2);
          if ((flg2_high & 8) == 0)
          {
            v17 = ((char *)autotbldata + 8 * sBtlGetSkilltbl(v11)->weapontype);
LABEL_71:
            m_Items = v17;
            v26 = attr;
            goto LABEL_72;
          }
LABEL_81:
LABEL_70:
          v17 = autotbldata;
          goto LABEL_71;
LABEL_69:
          goto LABEL_70;
        }
        Skilltbl = sBtlGetSkilltbl(v11);
        if ((Skilltbl->flg2 & 0x8000000) != 0)
        {
          if (!v24)
            goto LABEL_81;
          goto LABEL_69;
        }
        if (v24)
        {
LABEL_61:
          v17 = ((char *)autotbldata + 8 * Skilltbl->weapontype);
          goto LABEL_71;
        }
        else
        {
          goto LABEL_61;
        }
        goto LABEL_61;
      }
      break;
LABEL_51:
      v18 = NewSpecific(ushort, 9u);
      InitializeArray_55364416(v18, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E0A70A0D5DDCA34A6361B6DED06969C0115BB903C0F10403EA304D9B099D0978, 0);
      if (evtBitCheck(v18[0]))
      {
        v19 = HIBYTE(sBtlGetSkilltbl(v11)->flg2);
        if ((v19 & 8) == 0)
        {
          if (v20)
          {
            goto LABEL_57;
          }
          else
          {
          }
LABEL_57:
          v21 = autotbldata;
          v22 = ((char *)v21 + 8 * sBtlGetSkilltbl(v11)->weapontype);
LABEL_67:
          m_Items = v22;
          v26 = v28;
LABEL_72:
          v27 = m_Items->m_aisyo->para[v26] & 0xFFF;
          if (v27)
            *pDmg = *pDmg * v27 / 100;
          goto LABEL_37;
        }
        if (v20)
        {
LABEL_66:
          v22 = autotbldata;
          goto LABEL_67;
        }
        else
        {
          goto LABEL_66;
        }
        goto LABEL_66;
      }
LABEL_37:
      v9 += 4;
      if (v9 == 64)
        return;
    }
    goto LABEL_51;
  }
}

// 0x1ee9810
s32 sBtlGetDamage(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *target, SBTLDMG_HITWORK *hwk, SKLID skillid, u32 attr, bool calc_only) {
  SBTLCALC_DMGWORK *v11;
  SBTLUNIT_WORK *v12;
  SBTLCALC_DMGWORK *v13;
  s32 BEDtype;
  SBTLCALC_DMGWORK_A *awk;
  s32 aside;
  s32 aListID;
  SBTLUNIT_LISTWORK *UnitMng;
  s16 devilid;
  DEVILDATA_WORK *DevilData;
  s32 v28;
  s32 ListID;
  u32 flg;
  SBTLSKILLP_TBL *v31;
  SBATTLE_WORK *v33;
  SBTLUNIT_LISTWORK *v34;
  s32 playerID;
  SBTLUNIT_WORK *v36;
  SBATTLE_WORK *v37;
  SBTLUNIT_WORK *pNakama0;
  sdatUnitWork_t *v39;
  SBTLSKILLP_TBL *v40;
  sdatParaWork_t *v41;
  s64 v42;
  f32 v43;
  s32 v44;
  s16 v45;
  s32 swordatk;
  s32 v47;
  SBTLCALC_DMGWORK_A *v48;
  s32 atec;
  s16 alevel;
  sdatUnitWork_t *v51;
  s32 v52;
  f32 v53;
  f32 v54;
  SBTLAISYO_DATAWORK *v55;
  s16 v56;
  sdatUnitWork_t *v58;
  s32 v59;
  s32 Damage_ATK;
  SBTLUNIT_WORK *v61;
  SBTLSKILLP_TBL *v62;
  f32 v63;
  f32 v64;
  bool v65;
  s32 m_atk;
  f32 v67;
  SBTLSKILLP_TBL *v68;
  f32 v69;
  s16 n0;
  s32 side;
  SBTLAISYO_DATAWORK *v72;
  sdatUnitWork_t *v74;
  sdatParaWork_t *v75;
  s32 v76;
  s32 v77;
  SBTLSKILLP_TBL *v78;
  SBTLUNIT_WORK *v79;
  s16 v80;
  sdatUnitWork_t *v81;
  s32 itemid;
  SBTLACTION_WORK *actwk;
  f32 v85;
  SBATTLE_WORK *v87;
  SBTLUNIT_LISTWORK *v88;
  s32 v89;
  SBTLUNIT_WORK *v90;
  SBATTLE_WORK *v91;
  SBTLUNIT_WORK *v92;
  sdatUnitWork_t *v93;
  sdatParaWork_t *v94;
  sdatParaWork_t *v95;
  u64 v96;
  s32 *v97;
  f32 v98;
  SBATTLE_WORK *v100;
  SBTLUNIT_LISTWORK *v101;
  s32 v102;
  SBTLUNIT_WORK *v103;
  sdatUnitWork_t *v104;
  f32 v105;
  s32 tec;
  s32 *v107;
  SBTLUNIT_WORK *v108;
  sdatUnitWork_t *v109;
  u32 badst;
  s32 badstatus;
  sdatUnitWork_t *v112;
  s32 v113;
  SBTLAISYO_DATAWORK *v114;
  sdatUnitWork_t *v116;
  sdatUnitWork_t *v117;
  s32 Damage_NHP;
  sdatUnitWork_t *v119;
  s16 v120;
  s32 v121;
  SBTLAISYO_DATAWORK *v122;
  sdatUnitWork_t *v124;
  s32 v125;
  s16 *p_atkpower;
  s16 v127;
  sdatUnitWork_t *para;
  SBTLAISYO_DATAWORK *aisyo;
  sdatParaWork_t *now;
  s32 str;
  sdatUnitWork_t *v133;
  s32 vit;
  SBTLAISYO_DATAWORK *v135;
  int32x2_t *v136;
  sdatUnitWork_t *v138;
  sdatUnitWork_t *v139;
  sdatParaWork_t *v140;
  sdatParaWork_t *v141;
  s16 v142;
  s32 v143;
  SBTLAISYO_DATAWORK *v144;
  SBTLSKILLP_TBL *v146;
  u32 v147;
  SBTLUNIT_WORK *v148;
  bool v149;
  s32 atk_raito;
  f32 v152;
  s32 v153;
  f32 v154;
  s32 v155;
  sdatUnitWork_t *v156;
  sdatParaWork_t *v157;
  SBTLAISYO_DATAWORK *v158;
  sdatUnitWork_t *v160;
  s32 v161;
  f32 v163;
  s32 v164;
  f32 v165;
  s32 v166;
  u32 v167;
  s32 v168;
  s32 tdan_sklid;
  s32 para2;
  s32 count;
  s64 n1_low;
  f32 v173;
  s32 v174;
  s32 i;
  s32 v176;
  sdatUnitWork_t *v177;
  s32 AutoSkill_ID;
  s32 AutoSkillPara;
  sdatUnitWork_t *v182;
  sdatUnitWork_t *v183;
  s32 autost_cnt;
  s32 autost_cnt2;
  SBTLUNIT_WORK *v186;
  s32 v187;
  s32 v188;
  sdatUnitWork_t *v189;
  s32 v190;
  s32 v193;
  sdatUnitWork_t *v194;
  s32 v195;
  s32 v196;
  s64 v197;
  char *v199;
  SKLID *spiritSkill;
  s64 v202;
  char *v203;
  SKLID *v204;
  sdatUnitWork_t *v205;
  u32 v206;
  f32 v207;
  s64 v209;
  char *v210;
  SKLID *v211;
  f32 v212;
  s64 v214;
  char *v215;
  SKLID *v216;
  f32 v217;
  s32 v218;
  s8 kuda_id;
  SBTLUNIT_WORK *v221;
  u32 v224;
  s32 v225;
  f32 v226;
  s32 v227;
  sdatUnitWork_t *v228;
  sdatParaWork_t *v229;
  s16 level;
  f32 v231;
  SBTLUNIT_WORK *v232;
  s32 v233;
  s32 j;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v237;
  s64 k;
  sdatUnitWork_t *v239;
  s32 v240;
  SBTLSKILLP_TBL *v242;
  u32 v243;
  s32 *v245;
  u32 v246;
  s64 v247;
  s32 v248;
  f32 v249;
  sdatUnitWork_t *v250;
  sdatUnitWork_t *v251;
  sdatUnitWork_t *v253;
  s64 v254;
  s32 v255;
  SBTLUNIT_WORK *v256;
  s32 v257;
  SBTLUNIT_WORK *v258;
  SBTLUNIT_WORK *v259;
  sdatUnitWork_t *v260;
  sdatUnitWork_t *v261;
  SBTLUNIT_WORK *v262;
  SBTLUNIT_WORK *v263;
  sdatUnitWork_t *v264;
  SBTLUNIT_WORK *v265;
  SBTLUNIT_WORK *v266;
  sdatUnitWork_t *v267;
  sdatUnitWork_t *v268;
  u32 v269;
  SBTLUNIT_WORK *v270;
  SBTLUNIT_WORK *v271;
  sdatUnitWork_t *v272;
  s32 HaveMemSkl;
  f32 v274;
  f32 v275;
  s64 v277;
  sdatPlayerUnitWork_t *PlayerData;
  s32 *p_side;
  u32 v280;
  SBTLUNIT_WORK *wkEnemy;
  SBTLUNIT_WORK *pAtkr;
  SBTLSKILLP_TBL *Skilltbl;
  s32 pDmg;

  pDmg = 0;
  v11 = Allocate(SBTLCALC_DMGWORK);
  if (skillid == 72)
  {
    v12 = sBtlSearchDeivl(260);
    if (v12)
      acter = v12;
  }
  PlayerData = sBtlGetPlayerData();
  Skilltbl = sBtlGetSkilltbl(skillid);
  p_side = &acter->side;
  wkEnemy = acter;
  BEDtype = hwk->BEDtype;
  if (BEDtype != 5 && BEDtype != 2)
  {
    aside = *p_side;
    if ((*p_side & 0x80) == 0)
    {
      devilid = acter->para->devilid;
      goto LABEL_21;
    }
    goto LABEL_22;
  }
  awk = hwk->awk;
  aside = awk->aside;
  awk = hwk->awk;
  aListID = awk->aListID;
  UnitMng = wk->UnitMng;
  acter = sBtlSearchUnit_ID(UnitMng, aListID);
  if ((aside & 0x80) == 0)
    goto LABEL_19;
LABEL_22:
  DevilData = 0;
  goto LABEL_23;
LABEL_19:
  devilid = hwk->awk->adevilid;
LABEL_21:
  DevilData = sBtlGetDevilData(devilid, -1);
LABEL_23:
  v28 = 0;
  ListID = -1;
  pAtkr = acter;
  switch (Skilltbl->type & 0xFFF)
  {
    case 1:
      if ((aside & 0x80) != 0)
      {
        m_atk = sBtlDat()->m_atk;
        v67 = 1.5;
        v62 = Skilltbl;
        v61 = wkEnemy;
      }
      else
      {
        v61 = wkEnemy;
        v62 = Skilltbl;
        v63 = (wkEnemy->para->now->str + wkEnemy->para->level);
        v64 = (f32)(v63 + v63) + 50.0;
        v65 = v64 == INFINITY;
        m_atk = v64;
        v67 = 1.0;
        if (v65)
          m_atk = 0x80000000;
      }
      v11->sword_power = m_atk;
      if (skillid == 149)
        p_atkpower = &DevilData->atkpower;
      else
        p_atkpower = &v62->n0;
      v127 = *p_atkpower;
      if ((aside & 2) != 0)
        v67 = 2.0;
      v11->n0 = v127;
      para = v61->para;
      aisyo = target->para->aisyo;
      now = para->now;
      LOWORD(para) = para->level;
      str = now->str;
      v11->aisyo_tbl = aisyo;
      v11->alevel = (u16)para;
      LODWORD(para) = v61->side;
      v11->damage_per = v67;
      v11->aatk = str;
      v11->side = (u8)para;
      v133 = target->para;
      vit = v133->now->vit;
      v11->tlevel = v133->level;
      v11->tdef = vit;
      Damage_ATK = sBtlGetDamage_ATK(v11, v62);
      goto LABEL_141;
    case 2:
      v68 = Skilltbl;
      if ((aside & 0x80) != 0)
      {
        v68 = Skilltbl;
        if (acter->bulletskl == 744)
          v68 = sBtlGetSkilltbl(744);
      }
      v69 = 4.0;
      n0 = v68->n0;
      side = wkEnemy->side;
      if ((side & 2) == 0)
        v69 = 2.0;
      v11->damage_per = v69;
      v72 = target->para->aisyo;
      v11->aisyo_tbl = v72;
      v11->n0 = n0;
      v11->side = side;
      v11->gun_power = 10;
      v74 = target->para;
      v75 = v74->now;
      LOWORD(v74) = v74->level;
      v11->alevel = wkEnemy->para->level;
      v76 = v75->vit;
      v11->tlevel = (u16)v74;
      v11->tdef = v76;
      Damage_ATK = sBtlGetDamage_GUN(v11, Skilltbl);
      goto LABEL_141;
    case 3:
    case 5:
    case 9:
      flg = Skilltbl->flg;
      if ((flg & 1) != 0)
      {
        if ((flg & 0x200000) != 0)
        {
          v114 = target->para->aisyo;
          v11->aisyo_tbl = v114;
          v116 = target->para;
          v117 = v116;
          v31 = Skilltbl;
          Damage_NHP = sBtlGetDamage_NHP(v117, v11, Skilltbl);
        }
        else
        {
          *(u32 *)&v11->damage_per = 1063675494;
          v11->n0 = Skilltbl->n0;
          v47 = hwk->BEDtype;
          if (v47 == 5 || v47 == 2)
          {
            v48 = hwk->awk;
            v11->side = v48->aside;
            atec = v48->atec;
            alevel = v48->alevel;
          }
          else
          {
            v11->side = wkEnemy->side;
            v156 = wkEnemy->para;
            v157 = v156->now;
            alevel = v156->level;
            atec = v157->tec;
          }
          v11->atec = atec;
          v158 = target->para->aisyo;
          v11->aisyo_tbl = v158;
          v11->alevel = alevel;
          v11->ttec = target->para->now->tec;
          v31 = Skilltbl;
          Damage_NHP = sBtlGetDamage_MAGIC(v11, Skilltbl);
        }
        goto LABEL_193;
      }
      if ((flg & 4) != 0)
      {
        v108 = target;
        v31 = Skilltbl;
        if ((flg & 0x10000) != 0)
        {
          v109 = target->para;
          badst = Skilltbl->badst;
          badstatus = v109->badstatus;
          if ((badstatus & badst) != 0)
          {
            v109->badst_cnt = 0;
            v109->badstatus = badstatus & ~badst;
          }
          flg = Skilltbl->flg;
          v108 = target;
        }
        if ((flg & 0x800000) != 0)
        {
          GetDamage_Rejyene(v108, v13, Skilltbl, calc_only);
          v28 = 0;
          pDmg = 0;
          if ((Skilltbl->flg & 0x10000000) != 0)
            goto LABEL_204;
          goto LABEL_142;
        }
        if ((flg & 0x2000) != 0)
        {
          v11->n1 = Skilltbl->n1;
          v160 = v108->para;
          v161 = v160->badstatus;
          if ((v161 & 0x100000) != 0 || (v161 & 0x10000) != 0 && v160->devilid)
            goto LABEL_203;
          v231 = (f32)(v11->n1 / 100.0) * (f32)v160->now->maxhp;
          if (v231 == INFINITY)
            v28 = 0x80000000;
          else
            v28 = v231;
          pDmg = v28;
          if ((Skilltbl->flg & 0x10000000) != 0)
            goto LABEL_204;
          goto LABEL_142;
        }
        v112 = v108->para;
        v113 = v112->badstatus;
        if ((v113 & 0x100000) != 0 || (v113 & 0x10000) != 0 && v112->devilid)
        {
          v28 = 0;
          pDmg = 0;
          goto LABEL_142;
        }
        v226 = 0.8;
        v227 = wkEnemy->side;
        v11->side = v227;
        if ((v227 & 2) == 0)
          v226 = 1.0;
        v11->damage_per = v226;
        v228 = wkEnemy->para;
        v229 = v112->now;
        v11->n0 = Skilltbl->n0;
        level = v228->level;
        LODWORD(v228) = v228->now->tec;
        v11->alevel = level;
        v11->atec = (u32)v228;
        v11->tluck = v229->luck;
        v11->tmaxhp = (f32)v229->maxhp;
        Damage_NHP = sBtlGetDamage_MRecover(v11, v13);
LABEL_193:
        v28 = Damage_NHP;
        pDmg = Damage_NHP;
        if ((v31->flg & 0x10000000) == 0)
          goto LABEL_142;
        goto LABEL_204;
      }
      v31 = Skilltbl;
      if ((flg & 0x20) == 0)
      {
        if ((flg & 0x200) == 0)
        {
          v28 = 0;
          if ((Skilltbl->flg & 0x10000000) == 0)
            goto LABEL_142;
          goto LABEL_204;
        }
        v28 = 0;
        pDmg = 0;
        if ((Skilltbl->flg & 0x10000000) == 0)
          goto LABEL_142;
        goto LABEL_204;
LABEL_203:
        v28 = 0;
        pDmg = 0;
        if ((v31->flg & 0x10000000) == 0)
          goto LABEL_142;
LABEL_204:
        if (wkEnemy)
          ListID = wkEnemy->ListID;
        sBtlSetDyingDamage(target, skillid, 0, 0, ListID);
        goto LABEL_142;
      }
      sBtlGetDamage_ParaUP(target, skillid);
      v28 = 0;
      pDmg = 0;
      if ((Skilltbl->flg & 0x10000000) != 0)
        goto LABEL_204;
LABEL_142:
      v146 = Skilltbl;
      v147 = Skilltbl->flg;
      if ((v147 & 1) == 0)
      {
        v148 = target;
        v149 = calc_only;
        goto LABEL_242;
      }
      v148 = target;
      if ((Skilltbl->flg2 & 0x400000) != 0 || !acter)
      {
        v149 = calc_only;
        goto LABEL_179;
      }
      v149 = calc_only;
      if ((v147 & 0x200000) == 0 && (acter->side & 2) != 0)
      {
        atk_raito = acter->atk_raito;
        if ((target->side & 0x80) == 0)
        {
          if ((target->para->badstatus & 0x1000) != 0)
            goto LABEL_177;
          goto LABEL_164;
          if ((target->para->badstatus & 0x1000) == 0)
          {
LABEL_164:
            v152 = v28;
            v153 = 2;
LABEL_172:
            v154 = (f32)(ConvLevelValue(v153, v152) * (f32)atk_raito) / 100.0;
            v155 = v154;
            if ((s32)v154 <= 1)
              v155 = 1;
            if (v154 == INFINITY)
              v28 = 1;
            else
              v28 = v155;
          }
LABEL_177:
          v148 = target;
          pDmg = v28;
          goto LABEL_178;
        }
        if ((target->para->badstatus & 0x1000) != 0)
          goto LABEL_177;
        v152 = v28;
        v153 = 1;
        goto LABEL_172;
      }
LABEL_178:
      if ((acter->side & 1) != 0)
      {
        if ((v148->side & 1) == 0)
          goto LABEL_223;
        if (v148->para->devilid == 476)
          goto LABEL_223;
        v148 = target;
        if ((target->para->badstatus & 0x1000) != 0)
          goto LABEL_222;
        goto LABEL_215;
        if ((target->para->badstatus & 0x1000) != 0)
        {
LABEL_222:
          pDmg = v28;
          goto LABEL_223;
        }
LABEL_215:
        v163 = (f32)(ConvLevelValue(3, (f32)v28) * 100.0) / 100.0;
        v164 = v163;
        if ((s32)v163 <= 1)
          v164 = 1;
        if (v163 == INFINITY)
          v28 = 1;
        else
          v28 = v164;
        goto LABEL_222;
      }
LABEL_179:
      if (!v148)
        goto LABEL_242;
LABEL_223:
      if ((v148->side & 2) != 0 && (Skilltbl->flg & 0x200000) == 0)
      {
        if (v148->para->devilid != 476)
        {
          v148 = target;
          if ((target->para->badstatus & 0x1000) != 0)
            goto LABEL_241;
          goto LABEL_234;
          if ((target->para->badstatus & 0x1000) != 0)
          {
LABEL_241:
            pDmg = v28;
            goto LABEL_242;
          }
LABEL_234:
          v165 = (f32)(ConvLevelValue(0, (f32)v28) * 100.0) / 100.0;
          v166 = v165;
          if ((s32)v165 <= 1)
            v166 = 1;
          if (v165 == INFINITY)
            v28 = 1;
          else
            v28 = v166;
          goto LABEL_241;
        }
      }
LABEL_242:
      v167 = Skilltbl->flg;
      if (attr != 0x2000 && (v167 & 0x8000000) != 0 && !v149)
      {
        v168 = acter->side;
        sBtlGetDamage_Slip(v148, Skilltbl, skillid, v28, v168);
        v167 = Skilltbl->flg;
      }
      if (attr == 0x2000 || (v167 & 0x20000000) == 0 || v149)
        goto LABEL_267;
      if (wkEnemy)
        ListID = wkEnemy->ListID;
      if ((v148->status & 0x100) != 0)
      {
        if ((Skilltbl->flg2 & 0x20000) == 0)
          goto LABEL_267;
      }
      tdan_sklid = v148->tdan_sklid;
      if (skillid == 168 || tdan_sklid != 168)
      {
        if (tdan_sklid)
          goto LABEL_267;
      }
      else
      {
        v148->tdanpara = 0;
        *(_OWORD *)&v148->tdancounter = 0u;
      }
      para2 = Skilltbl->para2;
      v148->tdan_sklid = skillid;
      count = Skilltbl->count;
      v148->tdan_acterid = ListID;
      *(u64 *)&v148->tdancnt = 0;
      n1_low = LODWORD(Skilltbl->n1);
      v148->tdancounter = para2;
      v148->tdancmpcnt = para2 / count;
      v173 = (f32)(*(f32 *)&n1_low / 100.0) * (f32)v28;
      v174 = v173;
      if ((s32)v173 <= 1)
        v174 = 1;
      if (v173 == INFINITY)
        v174 = 1;
      v148->tdanpara = v174;
LABEL_267:
      if (acter && !v149)
      {
        for (i = 0; i != 8; ++i)
        {
          v177 = acter->para;
          AutoSkill_ID = sBtlGetAutoSkill_ID(v177, i);
          AutoSkillPara = sBtlGetAutoSkillPara(AutoSkill_ID, &acter->para->autost_cnt, &acter->para->autost_cnt2);
          if ((u32)(AutoSkillPara - 13) < 4 || AutoSkillPara == 54)
          {
            v182 = acter->para;
            v183 = v148->para;
            autost_cnt = v182->autost_cnt;
            autost_cnt2 = v182->autost_cnt2;
            v176 = CalcAutoSkill(v183, AutoSkillPara, v28, skillid, autost_cnt, autost_cnt2);
            if (v176)
              v28 = v176;
          }
        }
        v146 = Skilltbl;
        pDmg = v28;
      }
      v186 = wkEnemy;
      if (v148)
      {
        v187 = 0;
        while (1)
        {
          v189 = v148->para;
          v190 = sBtlGetAutoSkill_ID(v189, v187);
          v193 = sBtlGetAutoSkillPara(v190, &v148->para->autost_cnt, &v148->para->autost_cnt2);
          if (v193 == 4 || v193 == 18)
          {
            if ((attr & 0x2000) == 0 && v193 != 4)
              goto LABEL_295;
          }
          else if ((v193 & 0xFFFFFFFE) == 0x56 && (attr & 0x2000) == 0)
          {
LABEL_295:
            v194 = v148->para;
            v195 = v194->autost_cnt;
            v196 = v194->autost_cnt2;
            v188 = CalcAutoSkill(v194, v193, v28, skillid, v195, v196);
            if (v188)
              v28 = v188;
          }
          if (++v187 == 8)
          {
            v146 = Skilltbl;
            pDmg = v28;
            break;
          }
        }
      }
      if ((~*p_side & 0x81) == 0)
      {
        if (wk->battlemode != 3)
          goto LABEL_306;
      }
      if ((~target->side & 0x81) != 0)
        goto LABEL_378;
      goto LABEL_302;
LABEL_306:
      v197 = 0;
      while (1)
      {
        spiritSkill = GBWK->player->spiritSkill;
        if (v197 >= SLODWORD(spiritSkill->max_length))
          break;
        spiritSkill = GBWK->player->spiritSkill;
        v199 = (char *)spiritSkill + 4 * v197++;
        if (*((u32 *)v199 + 8) == 1389)
        {
          v205 = wkEnemy->para;
          v206 = sBtlGetBadStatus(v205);
          if ((v206 <= 0xB && ((1 << v206) & 0xD00) != 0 || (f32)((f32)wkEnemy->para->now->hp / (f32)wkEnemy->para->now->maxhp) < 0.26) && (Skilltbl->flg2 & 0x10) != 0)
          {
            v207 = (f32)v28 * 1.8;
            if (v207 == INFINITY)
              v28 = 0x80000000;
            else
              v28 = v207;
            pDmg = v28;
          }
          break;
        }
      }
      v209 = 0;
      while (1)
      {
        v211 = GBWK->player->spiritSkill;
        if (v209 >= SLODWORD(v211->max_length))
          break;
        v211 = GBWK->player->spiritSkill;
        v210 = (char *)v211 + 4 * v209++;
        if (*((u32 *)v210 + 8) == 1393)
        {
          if (wkEnemy->para->now->hp == wkEnemy->para->now->maxhp && (Skilltbl->flg2 & 0x10) != 0)
          {
            v212 = (f32)v28 * 1.2;
            if (v212 == INFINITY)
              v28 = 0x80000000;
            else
              v28 = v212;
            pDmg = v28;
          }
          break;
        }
      }
      v214 = 0;
      v186 = wkEnemy;
      while (1)
      {
        v216 = GBWK->player->spiritSkill;
        if (v214 >= SLODWORD(v216->max_length))
          break;
        v216 = GBWK->player->spiritSkill;
        v215 = (char *)v216 + 4 * v214++;
        if (*((u32 *)v215 + 8) == 1395)
        {
          if ((u32)(skillid - 1299) < 4 || skillid == 1319)
          {
            v217 = (f32)v28 * 1.2;
            if (v217 == INFINITY)
              v28 = 0x80000000;
            else
              v28 = v217;
            pDmg = v28;
          }
          break;
        }
      }
      v146 = Skilltbl;
      if ((~target->side & 0x81) != 0)
        goto LABEL_378;
LABEL_302:
      if (wk->battlemode == 3)
        goto LABEL_378;
      if ((*(u8 *)p_side & 2) != 0)
      {
        v202 = 0;
        while (1)
        {
          v204 = GBWK->player->spiritSkill;
          if (v202 >= SLODWORD(v204->max_length))
            break;
          v204 = GBWK->player->spiritSkill;
          v203 = (char *)v204 + 4 * v202++;
          if (*((u32 *)v203 + 8) == 1397)
          {
            sbtlplayertblPlayerSkill_GetMag3(target, v186, v28);
            goto LABEL_378;
          }
        }
      }
LABEL_378:
      v218 = v186->para->devilid;
      kuda_id = sBtlGetDevilData(v218, -1)->kuda_id;
      v221 = target;
      sBtlKudaDmg(kuda_id, &pDmg);
      sBtlFullMoonDmg(&pDmg, pAtkr);
      v224 = v146->attr;
      if ((v224 & 1) != 0)
      {
        v225 = 0;
      }
      else if ((v224 & 2) != 0)
      {
        v225 = 1;
      }
      else if ((v224 & 4) != 0)
      {
        v225 = 2;
      }
      else if ((v224 & 8) != 0)
      {
        v225 = 3;
      }
      else if ((v224 & 0x10) != 0)
      {
        v225 = 4;
      }
      else if ((v224 & 0x20) != 0)
      {
        v225 = 5;
      }
      else if ((v224 & 0x40) != 0)
      {
        v225 = 6;
      }
      else if ((v224 & 0x80) != 0)
      {
        v225 = 7;
      }
      else if ((v224 & 0x100) != 0)
      {
        v225 = 8;
      }
      else if ((v224 & 0x200) != 0)
      {
        v225 = 9;
      }
      else if ((v224 & 0x400) != 0)
      {
        v225 = 10;
      }
      else if ((v224 & 0x800) != 0)
      {
        v225 = 11;
      }
      else if ((v224 & 0x1000) != 0)
      {
        v225 = 12;
      }
      else if ((v224 & 0x2000) != 0)
      {
        v225 = 13;
      }
      else
      {
        if ((v224 & 0x4000) != 0)
        {
          v225 = 14;
        }
        else if ((v224 & 0x8000) != 0)
        {
          v225 = 15;
        }
        else
        {
          v225 = -1;
        }
        v221 = target;
      }
      sBtlZokuseiDmg(&pDmg, v221, v225);
      if (sBtlGetPChara() != v221)
      {
        v232 = pAtkr;
        if (sBtlGetPChara() != pAtkr)
          goto LABEL_517;
LABEL_506:
        v250 = v232->para;
        if (sBtlChkHaveMemSkl(v250, 71))
        {
          v251 = pAtkr->para;
          if ((Skilltbl->type & 0x1000) == 0)
          {
            goto LABEL_510;
          }
          v277 = 1374389535 * pDmg * v251->autost_cnt2;
          pDmg = (v277 >> 37) + ((u64)v277 >> 63);
LABEL_510:
          v232 = pAtkr;
          if (!sBtlChkHaveMemSkl(v251, 72))
            goto LABEL_517;
          v253 = v232->para;
          if (v253->now->hp == v253->now->maxhp)
          {
            v254 = 1374389535 * pDmg * v253->autost_cnt2;
            pDmg = (v254 >> 37) + ((u64)v254 >> 63);
          }
          goto LABEL_517;
        }
        v251 = pAtkr->para;
        goto LABEL_510;
      }
      v280 = attr;
      v233 = pDmg;
      for (j = 0; j != 2; ++j)
      {
        Nakama = sBtlGetNakama(j);
        if (Nakama)
        {
          v237 = Nakama;
          for (k = 32; k != 64; k += 4)
          {
            v239 = v237->para;
            v240 = *(u32 *)((char *)&v239->aOmoideSkill->obj.klass + k);
            if (sBtlGetAutoSkillPara(v240, &v239->autost_cnt, &v239->autost_cnt2) == 56)
            {
              v242 = sBtlGetSkilltbl(v240);
              if ((v242->flg2 & 0x8000000) == 0)
              {
                if (v243)
                {
                  goto LABEL_441;
                }
                else
                {
                }
LABEL_441:
                v245 = autotbldata[sBtlGetSkilltbl(v240)->weapontype]->m_aisyo->para;
                v246 = Skilltbl->attr;
                if ((v246 & 1) == 0)
                {
                  if ((v246 & 2) == 0)
                  {
                    if ((v246 & 4) == 0)
                    {
                      if ((v246 & 8) == 0)
                      {
                        if ((v246 & 0x10) == 0)
                        {
                          if ((v246 & 0x20) == 0)
                          {
                            if ((v246 & 0x40) == 0)
                            {
                              if ((v246 & 0x80) == 0)
                              {
                                if ((v246 & 0x100) == 0)
                                {
                                  if ((v246 & 0x200) == 0)
                                  {
                                    if ((v246 & 0x400) == 0)
                                    {
                                      if ((v246 & 0x800) == 0)
                                      {
                                        if ((v246 & 0x1000) == 0)
                                        {
                                          if ((v246 & 0x2000) == 0)
                                          {
                                            if ((v246 & 0x4000) == 0)
                                            {
LABEL_466:
                                              v247 = 0xF00000000LL;
                                              if ((v246 & 0x8000) == 0)
                                                v247 = 0xFFFFFFFF00000000LL;
                                              goto LABEL_501;
                                            }
LABEL_486:
                                            v247 = 0xE00000000LL;
LABEL_501:
                                            v248 = *(s32 *)((char *)v245 + (v247 >> 30));
                                            if (v248)
                                            {
                                              v249 = (f32)(v248 / 100) * (f32)v233;
                                              if (v249 == INFINITY)
                                                v233 = 0x80000000;
                                              else
                                                v233 = v249;
                                            }
                                            continue;
                                          }
LABEL_500:
                                          v247 = 0xD00000000LL;
                                          goto LABEL_501;
                                        }
                                        goto LABEL_499;
                                      }
                                      goto LABEL_498;
                                    }
                                    goto LABEL_497;
                                  }
                                  goto LABEL_496;
                                }
                                goto LABEL_495;
                              }
                              goto LABEL_494;
                            }
                            goto LABEL_493;
                          }
                          goto LABEL_492;
                        }
                        goto LABEL_491;
                      }
                      goto LABEL_490;
                    }
                    goto LABEL_489;
                  }
                  goto LABEL_488;
                }
LABEL_487:
                v247 = 0;
                goto LABEL_501;
              }
              if (v243)
              {
                goto LABEL_446;
              }
              else
              {
              }
LABEL_446:
              v245 = autotbldata[0]->m_aisyo->para;
              v246 = Skilltbl->attr;
              if ((v246 & 1) != 0)
                goto LABEL_487;
              if ((v246 & 2) == 0)
              {
                if ((v246 & 4) == 0)
                {
                  if ((v246 & 8) == 0)
                  {
                    if ((v246 & 0x10) == 0)
                    {
                      if ((v246 & 0x20) == 0)
                      {
                        if ((v246 & 0x40) == 0)
                        {
                          if ((v246 & 0x80) == 0)
                          {
                            if ((v246 & 0x100) == 0)
                            {
                              if ((v246 & 0x200) == 0)
                              {
                                if ((v246 & 0x400) == 0)
                                {
                                  if ((v246 & 0x800) == 0)
                                  {
                                    if ((v246 & 0x1000) == 0)
                                    {
                                      if ((v246 & 0x2000) == 0)
                                      {
                                        if ((v246 & 0x4000) == 0)
                                          goto LABEL_466;
                                        goto LABEL_486;
                                      }
                                      goto LABEL_500;
                                    }
LABEL_499:
                                    v247 = 0xC00000000LL;
                                    goto LABEL_501;
                                  }
LABEL_498:
                                  v247 = 0xB00000000LL;
                                  goto LABEL_501;
                                }
LABEL_497:
                                v247 = 0xA00000000LL;
                                goto LABEL_501;
                              }
LABEL_496:
                              v247 = 0x900000000LL;
                              goto LABEL_501;
                            }
LABEL_495:
                            v247 = 0x800000000LL;
                            goto LABEL_501;
                          }
LABEL_494:
                          v247 = 0x700000000LL;
                          goto LABEL_501;
                        }
LABEL_493:
                        v247 = 0x600000000LL;
                        goto LABEL_501;
                      }
LABEL_492:
                      v247 = 0x500000000LL;
                      goto LABEL_501;
                    }
LABEL_491:
                    v247 = 0x400000000LL;
                    goto LABEL_501;
                  }
LABEL_490:
                  v247 = 0x300000000LL;
                  goto LABEL_501;
                }
LABEL_489:
                v247 = 0x200000000LL;
                goto LABEL_501;
              }
LABEL_488:
              v247 = 0x100000000LL;
              goto LABEL_501;
            }
          }
        }
      }
      pDmg = v233;
      attr = v280;
      v221 = target;
      v232 = pAtkr;
      if (sBtlGetPChara() == pAtkr)
        goto LABEL_506;
LABEL_517:
      v255 = pDmg;
      if (sBtlGetNakama(0) == v232)
      {
        v258 = sBtlGetNakama(1);
        if (v258)
        {
          v259 = v258;
          if ((Skilltbl->type & 1) != 0)
          {
            v260 = v258->para;
            if (sBtlChkHaveMemSkl(v260, 58))
              v255 = v255 * v259->para->autost_cnt2 / 100;
          }
          if ((Skilltbl->type & 3) != 0)
          {
            v261 = v259->para;
            if (sBtlChkHaveMemSkl(v261, 59))
              v255 = v255 * v259->para->autost_cnt2 / 100;
          }
        }
      }
      if (sBtlGetNakama(0) == v221)
      {
        v262 = sBtlGetNakama(1);
        if (v262)
        {
          v263 = v262;
          v264 = v262->para;
          if (sBtlChkHaveMemSkl(v264, 57))
            v255 = v255 * v263->para->autost_cnt2 / 100;
        }
      }
      if (sBtlGetNakama(1) == pAtkr)
      {
        v265 = sBtlGetNakama(0);
        if (v265)
        {
          v266 = v265;
          if ((Skilltbl->type & 1) != 0)
          {
            v267 = v265->para;
            if (sBtlChkHaveMemSkl(v267, 58))
              v255 = v255 * v266->para->autost_cnt2 / 100;
          }
          if ((Skilltbl->type & 3) != 0)
          {
            v268 = v266->para;
            if (sBtlChkHaveMemSkl(v268, 59))
              v255 = v255 * v266->para->autost_cnt2 / 100;
          }
        }
      }
      if (sBtlGetNakama(1) == v221)
      {
        v269 = attr;
        v270 = sBtlGetNakama(0);
        if (v270)
        {
          v271 = v270;
          v272 = v270->para;
          HaveMemSkl = sBtlChkHaveMemSkl(v272, 57);
          v256 = pAtkr;
          if (HaveMemSkl)
            v255 = v255 * v271->para->autost_cnt2 / 100;
          if (v269 != 0x80000)
            goto LABEL_526;
        }
        else
        {
          v256 = pAtkr;
          if (attr != 0x80000)
            goto LABEL_526;
        }
LABEL_522:
        if (v255 >= 0)
          v257 = v255;
        else
          v257 = v255 + 1;
        v255 = v257 >> 1;
        goto LABEL_526;
      }
      v256 = pAtkr;
      if (attr == 0x80000)
        goto LABEL_522;
LABEL_526:
      if (sBtlGetPChara() == v256)
      {
        if (skillid <= 23)
        {
          if (skillid == 8 || skillid == 23)
            goto LABEL_567;
        }
        else
        {
          if ((skillid | 0x10) != 0x37 && (skillid & 0xFFFFFFFE) != 0x40)
            return v255;
LABEL_567:
          v274 = (f32)sBtlDat()->m_atk / 100.0;
          if (v274 < 1.0)
            v274 = 1.0;
          v275 = (f32)((f32)v255 * 0.5) + (f32)((f32)(v274 * (f32)v255) * 0.5);
          if (v275 == INFINITY)
            return 0x80000000;
          else
            return (s32)v275;
        }
      }
      return v255;
    case 7:
      v77 = *p_side;
      if ((*p_side & 0x80) != 0)
      {
        v79 = target;
        v80 = 10;
        v78 = Skilltbl;
      }
      else
      {
        v78 = Skilltbl;
        v79 = target;
        v80 = Skilltbl->n0;
      }
      v11->n0 = v80;
      *(u32 *)&v11->damage_per = 1065353216;
      v135 = v79->para->aisyo;
      v136 = wkEnemy->para->now;
      v11->aisyo_tbl = v135;
      v11->side = v77;
      *(float32x2_t *)&v11->ahp = vcvt_f32_s32(v136[2]);
      v138 = wkEnemy->para;
      v139 = v79->para;
      v140 = v138->now;
      v141 = v139->now;
      v11->alevel = v138->level;
      LODWORD(v140) = v140->str;
      LODWORD(v138) = v141->vit;
      v11->tlevel = v139->level;
      v11->aatk = (u32)v140;
      v11->tdef = (u32)v138;
      Damage_ATK = sBtlGetDamage_ATK_MG(v11, v78);
      goto LABEL_141;
    case 8:
      v81 = target->para;
      itemid = wk->panelwk->data[0]->itemid;
      v28 = CalcItem_Battle(target, v81, itemid);
      pDmg = v28;
      if ((Skilltbl->flg & 0x10000) != 0)
      {
        actwk = target->actwk;
        if (actwk->status == 9)
          actwk->cmpframecnt = 0;
      }
      goto LABEL_142;
    case 0xC:
    case 0xD:
      v33 = wk;
      v34 = v33->UnitMng;
      playerID = v33->playerID;
      v36 = sBtlSearchUnit_ID(v34, playerID);
      v37 = wk;
      if (v37->member_num < 1)
        goto LABEL_49;
      v37 = wk;
      if (v36 && (pNakama0 = v37->cmbSkl->pNakama0) != 0)
      {
        v39 = v36->para;
        v40 = Skilltbl;
        v41 = pNakama0->para->now;
        v42 = 32;
        if ((Skilltbl->type & 0xFFF) == 0xD)
          v42 = 36;
        v43 = (f32)((f32)((f32)(*(s16 *)((char *)&v41->klass + v42) + v39->now->str) * 0.5) + (f32)v39->now->tec)
            / 1.5;
        v44 = v43;
        if (v43 == INFINITY)
          v44 = 0x80000000;
        v45 = v39->level;
        v11->aatk = v44;
        v11->alevel = v45;
        if ((*(u8 *)p_side & 0x80) != 0)
          goto LABEL_44;
      }
      else
      {
LABEL_49:
        v40 = Skilltbl;
        v51 = wkEnemy->para;
        v52 = v51->now->str;
        LOWORD(v51) = v51->level;
        v11->aatk = v52;
        v11->alevel = (u16)v51;
        if ((*(u8 *)p_side & 0x80) != 0)
        {
LABEL_44:
          swordatk = PlayerData->swordatk;
          goto LABEL_52;
        }
      }
      v53 = (wkEnemy->para->now->str + wkEnemy->para->level);
      v54 = (f32)(v53 + v53) + 50.0;
      swordatk = v54;
      if (v54 == INFINITY)
        swordatk = 0x80000000;
LABEL_52:
      v11->sword_power = swordatk;
      v55 = target->para->aisyo;
      v56 = v40->n0;
      v11->aisyo_tbl = v55;
      v11->n0 = v56;
      *(u32 *)&v11->damage_per = 1069547520;
      v58 = target->para;
      v11->side = *p_side;
      v59 = v58->now->vit;
      v11->tlevel = v58->level;
      v11->tdef = v59;
      Damage_ATK = sBtlGetDamage_C_ATK1(v11, v40);
LABEL_141:
      v28 = Damage_ATK;
      pDmg = Damage_ATK;
      goto LABEL_142;
    case 0xE:
      v85 = 4.0;
      v11->n0 = Skilltbl->n0;
      if ((*p_side & 2) == 0)
        v85 = 2.0;
      v11->gun_power = 10;
      v11->damage_per = v85;
      v87 = wk;
      v88 = v87->UnitMng;
      v89 = v87->playerID;
      v90 = sBtlSearchUnit_ID(v88, v89);
      v91 = wk;
      if (v91->member_num < 1)
        goto LABEL_116;
      v91 = wk;
      if (v90 && (v92 = v91->cmbSkl->pNakama0) != 0)
      {
        v93 = v90->para;
        v94 = v93->now;
        v95 = v92->para->now;
        v11->alevel = v93->level;
        v96 = 1431655766 * (v95->tec + v94->tec);
        v11->aatk = HIDWORD(v96) + (v96 >> 63);
        v97 = &v90->side;
      }
      else
      {
LABEL_116:
        v119 = wkEnemy->para;
        v120 = v119->level;
        LODWORD(v119) = v119->now->str;
        v11->alevel = v120;
        v11->aatk = (u32)v119;
        v97 = p_side;
      }
      v121 = *v97;
      v122 = target->para->aisyo;
      v11->aisyo_tbl = v122;
      v11->side = v121;
      v124 = target->para;
      v125 = v124->now->vit;
      v11->tlevel = v124->level;
      v11->tdef = v125;
      Damage_ATK = sBtlGetDamage_C_GUN(v11, Skilltbl);
      goto LABEL_141;
    case 0xF:
      v98 = 0.45;
      if ((*p_side & 2) == 0)
        v98 = 0.95;
      v11->damage_per = v98;
      v11->n0 = Skilltbl->n0;
      v100 = wk;
      v101 = v100->UnitMng;
      v102 = v100->playerID;
      v103 = sBtlSearchUnit_ID(v101, v102);
      if (v103)
      {
        v104 = v103->para;
        v105 = (f32)v104->now->tec * 1.5;
        tec = v105;
        if (v105 == INFINITY)
          tec = 0x80000000;
        v107 = &v103->side;
      }
      else
      {
        v107 = p_side;
        v104 = wkEnemy->para;
        tec = v104->now->tec;
      }
      v142 = v104->level;
      v143 = *v107;
      v11->atec = tec;
      v11->side = v143;
      v11->alevel = v142;
      v144 = target->para->aisyo;
      v11->aisyo_tbl = v144;
      v11->ttec = target->para->now->tec;
      Damage_ATK = sBtlGetDamage_C_MAGIC(v11, Skilltbl);
      goto LABEL_141;
    default:
      goto LABEL_142;
  }
}

// 0x1eebbf0
static s32 GetDamageLevel(SBTLUNIT_WORK *target, LTYPE ltype, s32 damage, s32 atk_raito) {
  f32 v10;
  s32 v11;

  if ((target->para->badstatus & 0x1000) != 0)
    return damage;
  v10 = (f32)(ConvLevelValue(ltype, (f32)damage) * (f32)atk_raito) / 100.0;
  v11 = (s32)v10;
  if ((s32)v10 <= 1)
    v11 = 1;
  if (v10 == INFINITY)
    return 1;
  else
    return v11;
}

// 0x1eebce0
bool sBtlIsDamageCorrection(SBTLUNIT_WORK *wk) {
  return !wk || wk->para->devilid != 476;
}

// 0x1eddde0
void sBtlResetBattlePara(SBTLUNIT_WORK *wk, s32 index) {
  void *wkBarrier;
  s32 size;
  s32 v8;
  s16 *p_str;

  sBtlCheckStockPara(wk->para);
  wkBarrier = wk->wkBarrier;
  size = wkBarrier->_size;
  v8 = wkBarrier->_version + 1;
  wkBarrier->_size = 0;
  wkBarrier->_version = v8;
  if (size >= 1)
    Clear(wkBarrier->_items, 0, size, 0);
  CalcAisyo(wk);
  p_str = &wk->para->now->str;
  LimitRange_2(p_str, 0, 40);
  LimitRange_2(&wk->para->now->vit, 0, 40);
  LimitRange_2(&wk->para->now->tec, 0, 40);
  LimitRange_2(&wk->para->now->luck, 0, 40);
  if (index != -1)
    sBtlSetData_Unit_Stock(wk, index);
}

// 0x1ee85b0
void sBtlGetPlayerTec_ParaUp(sdatUnitWork_t *unit, sdatParaWork_t *data) {
  s32 *v5;
  void *v6;
  s64 v7;
  s32 tec;

  v5 = NewSpecific(s32, 0xDu);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__0B986FE39F33340EC09BA62C0D05E8D0846781528319238FC4EF721BDB1E74BF, 0);
  v6 = NewSpecific(s32, 0x34u);
  InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__AD727962CF5B78031ABFDAE6F28877B5521EF5E174D544783169B96E63D2F945, 0);
  v7 = 0;
  tec = unit->now->tec;
  if (tec >= 40)
    tec = 40;
  if (v5[0] < tec)
  {
    if (v5[1] >= tec)
    {
      v7 = 1;
    }
    else if (v5[2] >= tec)
    {
      v7 = 2;
    }
    else if (v5[3] >= tec)
    {
      v7 = 3;
    }
    else if (v5[4] >= tec)
    {
      v7 = 4;
    }
    else if (v5[5] >= tec)
    {
      v7 = 5;
    }
    else if (v5[6] >= tec)
    {
      v7 = 6;
    }
    else if (v5[7] >= tec)
    {
      v7 = 7;
    }
    else if (v5[8] >= tec)
    {
      v7 = 8;
    }
    else if (v5[9] >= tec)
    {
      v7 = 9;
    }
    else if (v5[10] >= tec)
    {
      v7 = 10;
    }
    else if (v5[11] >= tec)
    {
      v7 = 11;
    }
    else
    {
      v7 = 12;
      if (v5[12] < tec)
        v7 = 0;
    }
  }
  *(int16x4_t *)&data->str = vmovn_s32((int32x4_t)v6[v7 + 2]);
}

// 0x1edc850
void sBtlCheckBattlePara(SBTLUNIT_WORK *wk) {
  sdatParaWork_t *v3;
  s32 v7;
  sdatUnitWork_t *para;
  s32 side;
  sdatParaWork_t *now;
  s16 v13;

  v3 = Allocate(sdatParaWork_t);
  sBtlSetAutoSkill(wk);
  if ((~wk->side & 0x81) == 0)
  {
    if (sBtlKuisibariChk(wk))
      v7 = 0x20000000;
    else
      v7 = 0;
    wk->status = wk->status & 0xDFFFFFFF | v7;
  }
  sBtlCheckStockPara(wk->para);
  *(int16x4_t *)&wk->para->now->str = vadd_s16(*(int16x4_t *)&wk->kajyapara->str, *(int16x4_t *)&wk->para->now->str);
  if ((wk->side & 0x81) == 1)
  {
    para = sBtlGetPlayerData()->para;
    if ((para->flag & 1) != 0)
    {
      sBtlGetPlayerTec_ParaUp(para, v3);
      *(int16x4_t *)&wk->para->now->str = vadd_s16(*(int16x4_t *)&v3->str, *(int16x4_t *)&wk->para->now->str);
    }
  }
  CalcAisyo(wk);
  side = wk->side;
  now = wk->para->now;
  if ((side & 2) != 0)
    v13 = 99;
  else
    v13 = 40;
  LimitRange_2(&now->str, 0, v13);
  LimitRange_2(&wk->para->now->vit, 0, v13);
  LimitRange_2(&wk->para->now->tec, 0, v13);
  LimitRange_2(&wk->para->now->luck, 0, v13);
}

// 0x1ee7570
void CalcAisyo(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  SBTLAISYO_DATAWORK *aisyo;
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  s32 i;
  sdatUnitWork_t *v12;
  s32 v13;
  SBTLSKILLP_TBL *Skilltbl;
  s32 AutoSkill_ID;
  SBTLSKILLP_TBL *v17;
  s64 v18;
  s64 v19;
  s32 v21;
  s32 *v22;
  s32 *v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;

  para = wk->para;
  aisyo = para->aisyo;
  devilid = wk->para->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  ClassCopy(aisyo, aisyo_tbldata[DevilData->aishou], 0);
  sBtlKudanAisyo(wk);
  for (i = 0; i != 8; ++i)
  {
    v12 = wk->para;
    AutoSkill_ID = sBtlGetAutoSkill_ID(v12, i);
    Skilltbl = sBtlGetSkilltbl(AutoSkill_ID);
    if (!Skilltbl)
      continue;
LABEL_11:
    v17 = Skilltbl;
    if ((Skilltbl->attr & 0x33032) == 0)
      continue;
    v18 = 32;
    while (1)
    {
      if ((v17->flg2 & 0x8000000) == 0)
      {
        v21 = *(u32 *)((char *)&autotbldata[v17->weapontype]->m_aisyo->para->obj.klass + v18);
        if (v21)
          goto LABEL_24;
        goto LABEL_15;
      }
      v21 = *(u32 *)((char *)&autotbldata[0]->m_aisyo->para->obj.klass + v18);
      if (v21)
      {
LABEL_24:
        v22 = wk->para->aisyo->para;
        if ((v17->attr & 0x32) != 0)
        {
          v19 = 1374389535 * *(u32 *)((char *)&v22->obj.klass + v18) * (v21 & 0xFFF);
          *(u32 *)((char *)&v22->obj.klass + v18) = (v19 >> 37) + ((u64)v19 >> 63);
        }
        *(u32 *)((char *)&v22->obj.klass + v18) |= v21 & 0xFFFFF000;
      }
LABEL_15:
      v18 += 4;
      if (v18 == 96)
        goto LABEL_6;
    }
    v13 = sBtlGetAutoSkill_ID(wk->para, i);
    Skilltbl = sBtlGetSkilltbl(v13);
    if (Skilltbl)
      goto LABEL_11;
LABEL_6:
    ;
  }
  v23 = wk->para->aisyo->para;
  v24 = v23[0];
  if ((v24 & 0x800000) != 0)
  {
    v23[0] = v24 & 0xFF7FBFFF;
    v25 = v23[1];
    if ((v25 & 0x800000) == 0)
    {
LABEL_32:
      v26 = v23[2];
      if ((v26 & 0x800000) == 0)
        goto LABEL_33;
      goto LABEL_50;
    }
  }
  else
  {
    v25 = v23[1];
    if ((v25 & 0x800000) == 0)
      goto LABEL_32;
  }
  v23[1] = v25 & 0xFF7FBFFF;
  v26 = v23[2];
  if ((v26 & 0x800000) == 0)
  {
LABEL_33:
    v27 = v23[3];
    if ((v27 & 0x800000) == 0)
      goto LABEL_34;
    goto LABEL_51;
  }
LABEL_50:
  v23[2] = v26 & 0xFF7FBFFF;
  v27 = v23[3];
  if ((v27 & 0x800000) == 0)
  {
LABEL_34:
    v28 = v23[4];
    if ((v28 & 0x800000) == 0)
      goto LABEL_35;
    goto LABEL_52;
  }
LABEL_51:
  v23[3] = v27 & 0xFF7FBFFF;
  v28 = v23[4];
  if ((v28 & 0x800000) == 0)
  {
LABEL_35:
    v29 = v23[5];
    if ((v29 & 0x800000) == 0)
      goto LABEL_36;
    goto LABEL_53;
  }
LABEL_52:
  v23[4] = v28 & 0xFF7FBFFF;
  v29 = v23[5];
  if ((v29 & 0x800000) == 0)
  {
LABEL_36:
    v30 = v23[6];
    if ((v30 & 0x800000) == 0)
      goto LABEL_37;
    goto LABEL_54;
  }
LABEL_53:
  v23[5] = v29 & 0xFF7FBFFF;
  v30 = v23[6];
  if ((v30 & 0x800000) == 0)
  {
LABEL_37:
    v31 = v23[7];
    if ((v31 & 0x800000) == 0)
      goto LABEL_38;
    goto LABEL_55;
  }
LABEL_54:
  v23[6] = v30 & 0xFF7FBFFF;
  v31 = v23[7];
  if ((v31 & 0x800000) == 0)
  {
LABEL_38:
    v32 = v23[8];
    if ((v32 & 0x800000) == 0)
      goto LABEL_39;
    goto LABEL_56;
  }
LABEL_55:
  v23[7] = v31 & 0xFF7FBFFF;
  v32 = v23[8];
  if ((v32 & 0x800000) == 0)
  {
LABEL_39:
    v33 = v23[9];
    if ((v33 & 0x800000) == 0)
      goto LABEL_40;
    goto LABEL_57;
  }
LABEL_56:
  v23[8] = v32 & 0xFF7FBFFF;
  v33 = v23[9];
  if ((v33 & 0x800000) == 0)
  {
LABEL_40:
    v34 = v23[10];
    if ((v34 & 0x800000) == 0)
      goto LABEL_41;
    goto LABEL_58;
  }
LABEL_57:
  v23[9] = v33 & 0xFF7FBFFF;
  v34 = v23[10];
  if ((v34 & 0x800000) == 0)
  {
LABEL_41:
    v35 = v23[11];
    if ((v35 & 0x800000) == 0)
      goto LABEL_42;
    goto LABEL_59;
  }
LABEL_58:
  v23[10] = v34 & 0xFF7FBFFF;
  v35 = v23[11];
  if ((v35 & 0x800000) == 0)
  {
LABEL_42:
    v36 = v23[12];
    if ((v36 & 0x800000) == 0)
      goto LABEL_43;
    goto LABEL_60;
  }
LABEL_59:
  v23[11] = v35 & 0xFF7FBFFF;
  v36 = v23[12];
  if ((v36 & 0x800000) == 0)
  {
LABEL_43:
    v37 = v23[13];
    if ((v37 & 0x800000) == 0)
      goto LABEL_44;
    goto LABEL_61;
  }
LABEL_60:
  v23[12] = v36 & 0xFF7FBFFF;
  v37 = v23[13];
  if ((v37 & 0x800000) == 0)
  {
LABEL_44:
    v38 = v23[14];
    if ((v38 & 0x800000) == 0)
      goto LABEL_45;
    goto LABEL_62;
  }
LABEL_61:
  v23[13] = v37 & 0xFF7FBFFF;
  v38 = v23[14];
  if ((v38 & 0x800000) == 0)
  {
LABEL_45:
    v39 = v23[15];
    if ((v39 & 0x800000) == 0)
      return;
    goto LABEL_46;
  }
LABEL_62:
  v23[14] = v38 & 0xFF7FBFFF;
  v39 = v23[15];
  if ((v39 & 0x800000) != 0)
LABEL_46:
    v23[15] = v39 & 0xFF7FBFFF;
}

// 0x1eebd10
void sBtlKudanAisyo(SBTLUNIT_WORK *wk) {
  s32 encountno;
  sdatUnitWork_t *para;

  encountno = wk->encountno;
  if (encountno == 493)
    goto LABEL_19;
  if (encountno == 494)
    goto LABEL_19;
  if (encountno == 495)
    goto LABEL_19;
  if (encountno != 496)
    return;
LABEL_19:
  para = wk->para;
  if (para->devilid == 145)
  {
    AllMUKOU(para->aisyo, 0);
    AllMUKOU(wk->aisyo_bkup, 0);
  }
}

// 0x1ee8790
s32 sBtlGetDamage_MRecover(SBTLCALC_DMGWORK *wk, SBTLSKILLP_TBL *ptbl) {
  f32 v3;

  v3 = wk->damage_per
     * (f32)((f32)((f32)(wk->tmaxhp * (f32)((f32)wk->n0 / 100.0)) + (f32)((f32)((f32)wk->tluck * 1.5) + (f32)((f32)((f32)wk->atec * 1.5) + (f32)((f32)wk->alevel * 0.5)))) + 20.0);
  if (v3 == INFINITY)
    return 0x80000000;
  else
    return (s32)v3;
}

// 0x1eebe70
s32 sBtlCheckRegistKaja(SBTLSKL_KAJA_WORK *a_pKaja, SBTLSKILLP_TBL *a_pSkill) {
  SBTLSKL_KAJA_WORK *v3;
  SBTLSKL_KAJA_WORK *v4;
  f32 n1;
  s32 result;

  v3 = a_pKaja[0];
  if (!v3->m_cnt)
    return 0;
  v4 = a_pKaja[1];
  if (!v4->m_cnt)
    return 1;
  n1 = a_pSkill->n1;
  if (v3->m_fPara >= n1)
  {
    result = -1;
  }
  else
  {
    n1 = v3->m_fPara;
    result = 0;
  }
  if (v4->m_fPara < n1)
    return 1;
  return result;
}

// 0x1eebec0
bool sBtlCheckRegistKajaMaxNewAI(SBTLSKL_KAJA_WORK *a_pKaja, SBTLSKILLP_TBL *a_pSkill) {
  return !a_pKaja[0]->m_cnt && a_pKaja[1]->m_cnt == 0;
}

// 0x1edc760
bool sBtlRegistKaja(SBTLUNIT_WORK *wk, SBTLSKL_KAJA_WORK *a_pKaja, SBTLSKILLP_TBL *a_pSkill) {
  SBTLSKL_KAJA_WORK *v7;
  SBTLSKL_KAJA_WORK *v8;
  f32 n1;
  f32 m_fPara;
  bool v11;
  f32 v12;

  v7 = a_pKaja[0];
  if (v7->m_cnt)
  {
    v8 = a_pKaja[1];
    if (v8->m_cnt)
    {
      n1 = a_pSkill->n1;
      m_fPara = v7->m_fPara;
      v11 = m_fPara < n1;
      if (m_fPara < n1)
        n1 = v7->m_fPara;
      v12 = v8->m_fPara;
      if (!v11 && v12 >= n1)
        return 0;
      v7 = a_pKaja[v12 < n1];
    }
    else
    {
      v7 = a_pKaja[1];
    }
  }
  v7->m_fPara = a_pSkill->n1;
  v7->m_cnt = a_pSkill->attrtime;
  return 1;
}

// 0x1eebef0
s32 sBtlGetViceLevel(s32 vice) {
  if (vice > 3999)
    return 5;
  if (vice > 2999)
    return 4;
  if (vice > 1999)
    return 3;
  if (vice > 999)
    return 2;
  return vice > 299;
}

// 0x1eebf40
s32 sBtlGetViceLevelValue(s32 lvl) {
  s32 v2;
  u32 v3;

  if (lvl >= 5)
    v2 = 5;
  else
    v2 = lvl;
  v3 = v2 & ~(v2 >> 31);
  if (v3 > 4)
    return 4000;
  else
    return dword_3E63AE4[v3];
}

// 0x1eebf70
bool sBtlIsUseVice(SBTLUNIT_WORK *wk, SKLID sklId) {
  sdatUnitWork_t *para;
  s32 SkillCost;
  s32 vice;
  s32 v9;
  s32 v10;

  sBtlGetSkilltbl(sklId);
  para = wk->para;
  SkillCost = sBtlGetSkillCost(para, sklId);
  vice = wk->para->vice;
  if (vice > 3999)
    return SkillCost <= 5;
  if (vice > 2999)
    return SkillCost <= 4;
  if (vice <= 999)
    v9 = vice > 299;
  else
    v9 = 2;
  if (vice <= 1999)
    v10 = v9;
  else
    v10 = 3;
  return SkillCost <= v10;
}

// 0x1eec070
void sBtlUseVice(SBTLUNIT_WORK *wk, s32 use_cost) {
  s32 vice;
  s32 v7;
  u32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;

  vice = wk->para->vice;
  if (vice <= 3999)
  {
    if (vice > 2999)
    {
      if (4 - use_cost >= 5)
        v10 = 5;
      else
        v10 = 4 - use_cost;
      v8 = v10 & ~(v10 >> 31);
      if (v8 <= 4)
        goto LABEL_8;
    }
    else if (vice > 1999)
    {
      if (3 - use_cost >= 5)
        v11 = 5;
      else
        v11 = 3 - use_cost;
      v8 = v11 & ~(v11 >> 31);
      if (v8 <= 4)
        goto LABEL_8;
    }
    else if (vice > 999)
    {
      if (2 - use_cost >= 5)
        v12 = 5;
      else
        v12 = 2 - use_cost;
      v8 = v12 & ~(v12 >> 31);
      if (v8 <= 4)
        goto LABEL_8;
    }
    else
    {
      if ((vice > 299) - use_cost >= 5)
        v9 = 5;
      else
        v9 = (vice > 299) - use_cost;
      v8 = v9 & ~(v9 >> 31);
      if (v8 <= 4)
        goto LABEL_8;
    }
    goto LABEL_23;
  }
  if (5 - use_cost >= 5)
    v7 = 5;
  else
    v7 = 5 - use_cost;
  v8 = v7 & ~(v7 >> 31);
  if (v8 <= 4)
  {
LABEL_8:
    wk->para->vice = word_3E63AF8[v8];
    return;
  }
LABEL_23:
  wk->para->vice = 4000;
}

// 0x1eec1f0
void sBtlRecalcAisyoMember(SBTLUNIT_WORK *wk) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 side;

  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (!pUnit)
      goto LABEL_5;
    side = wk->side;
    if ((side & 1) != 0)
    {
      if ((pUnit->side & 1) == 0)
        goto LABEL_5;
    }
    else if ((side & 2) == 0 || (pUnit->side & 2) == 0)
    {
      goto LABEL_5;
    }
    sBtlCheckBattlePara(pUnit);
LABEL_5:
    ++v3;
  }
}
