#include "types.h"
#include "GaugeType.h"
#include "SKLID.h"
#include "configgame.h"
#include "dat.h"
#include "evtbit.h"
#include "fld.h"
#include "raijindlc.h"
#include "rstinit.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtldvltk.h"
#include "sbtlencount.h"
#include "sbtlexp.h"
#include "sbtlmain.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdfrand.h"
#include "smnr.h"

#define TADASHI_VAL 120
#define MONEY_SAKEME 8
#define EXP_SAKEME 4
#define KUDA_EXP 3
#define KUDA_CYUUSEI 3
#define SBTLREWARD_MAXEXP 99999
#define SBTLREWARD_MAXMONEY 99999
#define SBTLREWARD_MAXMAG 9999
#define SBTLREWARD_MAXCHU 100
#define SBTLREWARD_MAXDANGAN 99
#define SBTLREWARD_MAXITEM 9
#define SBTLREWARD_MAXCHU_BASE 4
#define SBTL_KOUFUN_PROBABILITY 70

typedef struct SBTLEXP_LISTWORK SBTLEXP_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct TypeExpSpecialTbl TypeExpSpecialTbl;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct TypeExpSpecialTbl {
    s32 enc_id;
    s32 exp;
    s32 money;
};

static s32 riritutbl_nz[21];
static s32 *riritutbl_nb;
s32 *riritutbl_e;
static s32 *enemy_weak_time_para;
static s32 *nakama_weak_time_para;
static s32 *vice_gage_w;
GaugeType *vice_gage_type;

static s32 CalcInitVice(SBTLUNIT_WORK *wk);

// 0x1f05490
s32 sBtlGetRiritutbl_n(SBTLUNIT_WORK *wk, s32 mode) {
  s64 v6;
  s32 v8;
  s64 v10;

  if (!wk || (wk->side & 2) != 0 && (wk->status & 0x100000) != 0)
  {
    v10 = (s64)riritutbl_nb + 4 * mode;
    v8 = *(u32 *)(v10 + 32);
  }
  else
  {
    v6 = (s64)riritutbl_nz + 4 * mode;
    v8 = *(u32 *)(v6 + 32);
  }
  if (sBtlGetSpiritSkillChk(1452))
    return 120 * v8 / 100;
  else
    return v8;
}

// 0x1f055d0
s32 sBtlCalcWeakTime(SBTLUNIT_WORK *wk, s32 iKouchoku) {
  s32 side;
  f32 v6;
  s32 v7;
  f32 v8;

  side = wk->side;
  if ((side & 2) != 0)
  {
    v6 = iKouchoku;
    v7 = 30;
    goto LABEL_11;
  }
  if ((side & 1) != 0)
  {
    v6 = iKouchoku;
    v7 = 29;
LABEL_11:
    v8 = ConvLevelValue(v7, v6);
    if (v8 == INFINITY)
      iKouchoku = 0x80000000;
    else
      iKouchoku = (s32)v8;
  }
  if (iKouchoku <= 1)
    return 1;
  else
    return iKouchoku;
}

// 0x1f05690
s32 sBtlCalcHuumaW(SBTLUNIT_WORK *wk, s32 gage_w) {
  return gage_w;
}

// 0x1f056a0
GaugeType sBtlCalcHuumaType(SBTLUNIT_WORK *wk) {
  if ((wk->side & 2) != 0)
    return 2;
  else
    return 5;
}

// 0x1f056c0
void sBtlCheckDropItem_Limit(void *reward, s32 item_cnt) {
  void *v5;

  v5 = reward->Item[item_cnt];
  LimitRange(&v5->Nums, 0, 9);
}

// 0x1f05740
SBTLEXP_LISTWORK *sBtlCreateEXPList(void) {
  SBTLEXP_LISTWORK *v1;

  v1 = Allocate(SBTLEXP_LISTWORK);
  v1->ewk = 0;
  v1->o_counter = 0;
  *(u32 *)&v1->riritu = 1065353216;
  v1->counter = 180;
  v1->o_alpha = 128;
  *(u64 *)&v1->alpha = sub_80;
  return v1;
}

// 0x1f057d0
void sBtlInitDropWork(void) {
  SBATTLE_WORK *wk_local;
  SBTLDROP_WORK *v3;

  wk_local = wk;
  v3 = Allocate(SBTLDROP_WORK);
  _ctor(v3, 0);
  wk_local->drop = v3;
}

// 0x1f05870
void sBtlGetAutoSkillPoint(void) {
  AUTO *v1;
  u32 *v2;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v7;
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;
  s32 AutoSkillPara;
  sdatUnitWork_t *v11;
  s32 v12;
  s32 v13;
  sdatUnitWork_t *v14;
  s32 autost_cnt;
  s32 autost_cnt2;
  sdatUnitWork_t *v17;
  s32 v18;
  s32 v19;
  sdatUnitWork_t *v20;
  s32 v21;
  s32 v22;
  sdatUnitWork_t *v23;
  s32 v24;
  s32 v25;
  sdatUnitWork_t *v26;
  s32 v27;
  s32 v28;
  sdatUnitWork_t *v29;
  s32 v30;
  s32 v31;
  sdatUnitWork_t *v32;
  s32 v33;
  s32 v34;
  s64 v35;

  v1 = NewSpecific(AUTO, 8u);
  InitializeArray_55364416(v1, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__DF0829040774CD17DB603854364857E2B9C3DE0CB57343F4CEBF526B21240538, 0);
  v2 = NewSpecific(s32, 8u);
  for (i = 0; ; i = v35 + 1)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    v35 = i;
    pUnit = wk->UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 1) == 0)
      continue;
    v7 = 0;
LABEL_16:
    para = pUnit->para;
    AutoSkill_ID = sBtlGetAutoSkill_ID(para, v7);
    AutoSkillPara = sBtlGetAutoSkillPara(AutoSkill_ID, &pUnit->para->autost_cnt, &pUnit->para->autost_cnt2);
    if (v1[0] == AutoSkillPara && !v2[8])
    {
      v14 = pUnit->para;
      autost_cnt = v14->autost_cnt;
      autost_cnt2 = v14->autost_cnt2;
      CalcAutoSkill(v14, AutoSkillPara, 0, 0, autost_cnt, autost_cnt2);
      v2[8] = 1;
      if (v1[1] == AutoSkillPara)
      {
LABEL_21:
        if (!v2[9])
        {
          v11 = pUnit->para;
          v12 = v11->autost_cnt;
          v13 = v11->autost_cnt2;
          CalcAutoSkill(v11, AutoSkillPara, 0, 0, v12, v13);
          v2[9] = 1;
        }
      }
    }
    else if (v1[1] == AutoSkillPara)
    {
      goto LABEL_21;
    }
    if (v1[2] == AutoSkillPara && !v2[10])
    {
      v20 = pUnit->para;
      v21 = v20->autost_cnt;
      v22 = v20->autost_cnt2;
      CalcAutoSkill(v20, AutoSkillPara, 0, 0, v21, v22);
      v2[10] = 1;
      if (v1[3] == AutoSkillPara)
      {
LABEL_31:
        if (!v2[11])
        {
          v17 = pUnit->para;
          v18 = v17->autost_cnt;
          v19 = v17->autost_cnt2;
          CalcAutoSkill(v17, AutoSkillPara, 0, 0, v18, v19);
          v2[11] = 1;
        }
      }
    }
    else if (v1[3] == AutoSkillPara)
    {
      goto LABEL_31;
    }
    if (v1[4] == AutoSkillPara && !v2[12])
    {
      v26 = pUnit->para;
      v27 = v26->autost_cnt;
      v28 = v26->autost_cnt2;
      CalcAutoSkill(v26, AutoSkillPara, 0, 0, v27, v28);
      v2[12] = 1;
      if (v1[5] == AutoSkillPara)
      {
LABEL_41:
        if (!v2[13])
        {
          v23 = pUnit->para;
          v24 = v23->autost_cnt;
          v25 = v23->autost_cnt2;
          CalcAutoSkill(v23, AutoSkillPara, 0, 0, v24, v25);
          v2[13] = 1;
        }
      }
    }
    else if (v1[5] == AutoSkillPara)
    {
      goto LABEL_41;
    }
    if (v1[6] == AutoSkillPara && !v2[14])
    {
      v32 = pUnit->para;
      v33 = v32->autost_cnt;
      v34 = v32->autost_cnt2;
      CalcAutoSkill(v32, AutoSkillPara, 0, 0, v33, v34);
      v2[14] = 1;
      if (v1[7] == AutoSkillPara)
      {
LABEL_51:
        if (!v2[15])
        {
          v29 = pUnit->para;
          v30 = v29->autost_cnt;
          v31 = v29->autost_cnt2;
          CalcAutoSkill(v29, AutoSkillPara, 0, 0, v30, v31);
          v2[15] = 1;
        }
      }
    }
    else if (v1[7] == AutoSkillPara)
    {
      goto LABEL_51;
    }
    if (++v7 == 8)
      continue;
    goto LABEL_16;
  }
}

// 0x1f05d40
void sBtlGetChuuseiPoint(void) {
  SBTLDROP_WORK *drop;

  drop = wk->drop;
  drop->get_chuusei = drop->chuusei;
}

// 0x1f05db0
s32 sBtlGetSpecialExp(void) {
  return -1;
}

// 0x1f05dc0
s32 sBtlGetSpecialMoney(void) {
  return -1;
}

// 0x1f05dd0
s32 sBtlGetExp_ChkMemSkl(s32 a_exp, sdatUnitWork_t *a_pUnit) {
  f32 v5;
  f32 v7;
  s32 v8;

  if (a_pUnit)
  {
    if (sBtlChkHaveMemSkl(a_pUnit, 9))
    {
      v5 = (f32)a_pUnit->autost_cnt2 + -100.0;
      goto LABEL_8;
    }
    v5 = 0.0;
LABEL_8:
    if (sBtlChkHaveMemSkl(a_pUnit, 88))
      v5 = v5 + (f32)((f32)a_pUnit->autost_cnt2 + -100.0);
    if (!sBtlChkHaveMemSkl(a_pUnit, 89))
    {
LABEL_13:
      v7 = (f32)(v5 * (f32)a_exp) / 100.0;
      v8 = v7;
      if (v7 == INFINITY)
        v8 = 0x80000000;
      a_exp += v8;
      return a_exp;
    }
    v5 = v5 + (f32)((f32)a_pUnit->autost_cnt2 + -100.0);
    goto LABEL_13;
  }
  return a_exp;
}

// 0x1f05f50
s32 sBtlGetChuusei_ChkMemSkl(s32 a_chuusei, sdatUnitWork_t *a_pUnit) {
  s32 HaveMemSkl;
  f32 v6;
  f32 v7;
  s32 v8;

  if (a_pUnit)
  {
    HaveMemSkl = sBtlChkHaveMemSkl(a_pUnit, 55);
    v6 = -50.0;
    if (!HaveMemSkl)
      v6 = 0.0;
    v7 = (f32)(v6 * (f32)a_chuusei) / 100.0;
    v8 = v7;
    if (v7 == INFINITY)
      v8 = 0x80000000;
    a_chuusei += v8;
  }
  return a_chuusei;
}

// 0x1f06010
void sBtlCheckDropItem(void *a_pReward) {
  char *log;
  s32 v5;
  s64 v6;
  s64 v8;
  s32 data;
  s32 v12;
  void *v13;
  void *v14;
  void *v15;
  s64 i;
  s64 size;
  u64 *v19;
  s32 *items;
  s64 v21;
  s64 v22;
  bool v23;
  u32 *v;
  u32 v27;
  u32 v28;
  s32 v29;
  s32 v30;
  u32 v31;
  s32 v32;
  s32 v33;
  s32 Item;
  s64 v36;
  s64 v37;
  s32 *v38;
  s32 v39;

  log = wk->drop->log;
  a_pReward->dropLog = log;
  v5 = 0;
  v6 = 32;
  while (1)
  {
    data = (*(Il2CppClass **)((char *)&wk->drop->item->obj.klass + v6))->_1.byval_arg.data;
    if (!datCheckEventItem(data))
      goto LABEL_8;
    v12 = (*(Il2CppClass **)((char *)&wk->drop->item->obj.klass + v6))->_1.byval_arg.data;
    if (!datCheckItem(v12, 1))
      goto LABEL_21;
LABEL_8:
    v6 += 8;
    if (v6 == 128)
    {
      v15 = Allocate(System_Collections_Generic_List_int_);
      __ctor(v15);
      for (i = 4; i != 16; ++i)
      {
        if (*(u32 *)(*((u64 *)&wk->drop->item->obj.klass + i) + 32))
        {
          if (*(s32 *)(*((u64 *)&wk->drop->item->obj.klass + i) + 40) > 99)
            goto LABEL_35;
          if (*(s32 *)(*((u64 *)&wk->drop->item->obj.klass + i) + 36) > 0)
            goto LABEL_35;
          if (!*(u32 *)(*((u64 *)&wk->drop->item->obj.klass + i) + 36))
          {
LABEL_35:
            size = v15->_size;
            v19 = Method_System_Collections_Generic_List_int__Add__;
            ++v15->_version;
            items = v15->_items;
            if ((u32)size >= LODWORD(items->max_length))
            {
              _AddWithResize(v15, i - 4, *(const MethodInfo_2D8F530 **)(*(u64 *)(v19[4] + 192) + 112));
            }
            else
            {
              v15->_size = size + 1;
              items[size] = i - 4;
            }
          }
        }
      }
      v21 = v5 + 4;
      while (1)
      {
        if (!v15->_size)
        {
LABEL_65:
          v39 = v15->_version + 1;
          v15->_size = 0;
          v15->_version = v39;
          return;
        }
        v = sdfDefaultRandCB->v;
        v27 = v[0];
        v28 = v[2];
        v29 = *(u64 *)v >> 30;
        v30 = *(u64 *)&v[2] >> 31;
        v[2] = v[1];
        v[3] = v28;
        v31 = v30 ^ v29;
        v[0] = v31;
        v[1] = v27;
        v32 = (s32)(f32)v31 % v15->_size;
        if (v32 >= 0)
          v33 = (s32)(f32)v31 % v15->_size;
        else
          v33 = -v32;
        Item = _get_Item(v15, v33);
        _RemoveAt(v15, v33);
        v36 = *((u64 *)&a_pReward->Item->obj.klass + v21);
        v37 = *((u64 *)&a_pReward->Item->obj.klass + v21);
        v38 = wk->drop->item[Item];
        *(u32 *)(v36 + 16) = v38[0];
        *(u32 *)(v37 + 20) = v38[1];
        *(u32 *)(v37 + 24) = v38[3];
        v22 = *((u64 *)&a_pReward->Item->obj.klass + v21);
        LimitRange((v22 + 20), 0, 9);
        v23 = (u32)v21++ == 6;
        wk->drop->item[Item][0] = 0;
        if (v23)
          goto LABEL_65;
      }
    }
  }
  if (datCheckItem(v12, 1))
    goto LABEL_8;
LABEL_21:
  v13 = a_pReward->Item[v5];
  v14 = a_pReward->Item[v5++];
  v8 = *(s64 *)((char *)&wk->drop->item->obj.klass + v6);
  v13->ID = *(u32 *)(v8 + 32);
  *(u64 *)&v14->Nums = 1;
  *(u32 *)(v8 + 32) = 0;
  if (v5 <= 2)
    goto LABEL_8;
}

// 0x1f06610
bool sBtlCheckGetExpUnit(sdatUnitWork_t *unit) {
  s32 devilid;

  if ((unit->flag & 1) == 0 || (unit->badstatus & 0x130000) != 0)
    return 0;
  devilid = unit->devilid;
  return DlcDevilSelCheck(devilid);
}

// 0x1f066b0
void sBtlCheckDrop(void) {
  void *v1;
  sdatPlayerUnitWork_t *player;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  u32 status2;
  SBATTLE_WORK *v13;
  SBTLDROP_WORK *v14;
  SBATTLE_WORK *v16;
  SBTLDROP_WORK *v17;
  sdatUnitWork_t *para;
  s32 gold;
  f32 Money;
  u32 v23;
  SBATTLE_WORK *v25;
  u32 v26;
  u32 v27;
  u32 v28;
  s32 v33;
  u32 v34;
  SBATTLE_WORK *v36;
  u32 status3;
  u32 v38;
  SBTLDROP_WORK *v39;
  s32 v40;
  s32 *p_PlayerExp;
  s32 get_chuusei;
  s32 v47;
  s32 v48;
  s16 *stack_p;
  s32 v54;
  s64 v55;
  s32 v56;
  s64 v57;
  f32 v58;
  SBATTLE_WORK *v60;
  sdatUnitWork_t *v61;
  s32 devilid;
  s32 v64;
  s64 v65;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v68;
  s32 *StockExp;
  s32 *Cyuusei;
  s32 v71;
  f32 v72;
  s32 v74;
  sdatUnitWork_t *v75;
  s32 *v76;
  s32 v77;
  char *v78;
  s32 v79;
  sdatUnitWork_t *v80;
  s64 v82;
  sdatUnitWork_t *v83;
  sdatUnitWork_t *v85;
  s32 Exp_ChkMemSkl;
  sdatUnitWork_t *v87;
  sdatUnitWork_t *v88;
  s32 v89;
  s32 *v90;
  s32 *v92;
  s32 v93;
  f32 v94;
  s32 v96;
  sdatUnitWork_t *v97;
  s32 *v98;
  char *v99;
  s32 v100;
  sdatUnitWork_t *v101;
  s32 v102;
  f32 v103;
  f32 v104;
  s32 v105;
  s32 HaveMemSkl;
  f32 v107;
  f32 v108;
  s32 v109;
  s32 *v110;
  s32 *v112;
  f32 v113;
  s32 v114;
  s32 *v115;
  f32 v116;
  s32 v117;
  u32 v118;
  SBATTLE_WORK *v121;
  SBTLDROP_WORK *v122;
  SBTLDROP_WORK *drop;
  s32 exp;
  s32 a_exp;

  v1 = Allocate(rstReward_t);
  _ctor(v1, 0);
  player = GBWK->player;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  v1->Mag = wk->drop->mag;
  v1->lucktypef = 0;
  LimitRange(&v1->Mag, 0, 9999);
  if ((wk->status & 0x1000000) == 0)
  {
    goto LABEL_11;
  }
  v13 = wk;
  v14 = Allocate(SBTLDROP_WORK);
  _ctor(v14, 0);
  v13->drop = v14;
  v1->Money = 0;
  v1->ExpAll = 0;
  v1->drawexp = 0;
  v1->drawmon = 0;
  rstSetReward(v1);
  v16 = wk;
  v17 = Allocate(SBTLDROP_WORK);
  _ctor(v17, 0);
  v16->drop = v17;
LABEL_11:
  status2 = wk->status2;
  if ((status2 & 0x10000000) == 0)
    goto LABEL_34;
  if ((status2 & 0x70000) != 0)
LABEL_34:
  if (!v7)
  {
    v1->Money = wk->drop->gold;
    goto LABEL_41;
  }
  para = v7->para;
  gold = wk->drop->gold;
  v1->Money = sBtlGetDropMoney(para, gold);
LABEL_41:
  if ((fldGb->nowKiretsuIdx & 0x80000000) == 0)
  {
    Money = v1->Money;
    v23 = vcvts_n_s32_f32(Money, 3u);
    if ((f32)(Money * 8.0) == INFINITY)
      v23 = 0x80000000;
    v1->Money = v23;
  }
  LimitRange(&v1->Money, 0, 99999);
  v1->drawmon = v1->Money;
  v25 = wk;
  if ((v25->status3 & 0x10) == 0)
  {
    v1->ExpAll = 0;
    if (v26)
      goto LABEL_50;
LABEL_54:
    v27 = wk->status2;
    if ((v27 & 0x10000000) == 0)
      goto LABEL_60;
    goto LABEL_55;
  }
  v1->Money *= 2;
  v1->ExpAll = 0;
  if (!v28)
    goto LABEL_54;
LABEL_50:
  v27 = v25->status2;
  if ((v27 & 0x10000000) == 0)
    goto LABEL_60;
LABEL_55:
  if ((v27 & 0x70000) != 0)
LABEL_60:
  if (sBtlCheckEndEscape())
  {
    goto LABEL_62;
  }
  drop = wk->drop;
  exp = drop->exp;
  drop->exp = sBtlGetExpHosei(exp);
LABEL_62:
  v33 = wk->drop->exp;
  if ((fldGb->nowKiretsuIdx & 0x80000000) == 0)
  {
    v34 = vcvts_n_s32_f32((f32)v33, 2u);
    if ((f32)((f32)v33 * 4.0) == INFINITY)
      v33 = 0x80000000;
    else
      v33 = v34;
  }
  v1->drawexp = v33;
  v36 = wk;
  status3 = v36->status3;
  LOBYTE(v38) = status3;
  v39 = v36->drop;
  v40 = (status3 >> 2) & 1;
  v1->PlayerExp = 0;
  p_PlayerExp = &v1->PlayerExp;
  get_chuusei = v39->get_chuusei;
  if (v36->battlemode == 3)
  {
    a_exp = v33 << v40;
    goto LABEL_73;
  }
  else
  {
    *p_PlayerExp = v33 << v40;
    a_exp = v33 << v40;
    goto LABEL_73;
  }
LABEL_73:
  LimitRange(p_PlayerExp, 0, 99999);
  v47 = get_chuusei << ((v38 & 8) != 0);
  if (wk->battlemode != 3)
  {
    stack_p = GBWK->player->stack_p;
    v54 = stack_p[0];
    v48 = stack_p[1];
    v1->StockIndex0 = v54;
    goto LABEL_87;
  }
  v1->StockIndex0 = main_data->stock_id;
  v48 = -1;
LABEL_87:
  v55 = 0;
  v56 = 0;
  v1->StockIndex1 = v48;
  v57 = 32;
  v58 = v47;
  while (1)
  {
    v60 = wk;
    if (v55 >= v60->stock_num)
      break;
    v61 = player->stock_id[v55];
    if ((v61->flag & 1) == 0)
      goto LABEL_89;
    if ((v61->badstatus & 0x130000) != 0)
      goto LABEL_89;
    devilid = v61->devilid;
    if (!DlcDevilSelCheck(devilid))
      goto LABEL_89;
    v64 = v56;
    if (wk->member_num >= 1)
    {
      if (v55 == v1->StockIndex0 || v55 == v1->StockIndex1)
      {
        v65 = (s64)v1->StockExp + 4 * v55;
        stock_id = player->stock_id;
        *(u32 *)(v65 + 32) = a_exp;
        v68 = stock_id[v55];
        *(u32 *)(v65 + 32) = sBtlGetExp_ChkMemSkl(a_exp, v68);
        StockExp = v1->StockExp;
        LimitRange(((char *)StockExp + v57), 0, 99999);
        Cyuusei = v1->Cyuusei;
        v71 = player->stock_id[v55]->devilid;
        v72 = sBtlGetDevilData(v71, -1)->getchuusei * v58;
        v74 = v72;
        if (v72 == INFINITY)
          v74 = 0x80000000;
        Cyuusei[v55] = v74;
        v75 = GBWK->player->stock_id[v55];
        v76 = v1->Cyuusei;
        if (v75->bChuuseiDrink)
        {
          v76[v55] *= 2;
          v75 = GBWK->player->stock_id[v55];
          v76 = v1->Cyuusei;
          v75->bChuuseiDrink = 0;
        }
        v77 = v64;
        v78 = (char *)v76 + 4 * v55;
        v79 = *((u32 *)v78 + 8);
        v80 = player->stock_id[v55];
        if (v80)
        {
          HaveMemSkl = sBtlChkHaveMemSkl(v80, 55);
          v107 = -50.0;
          if (!HaveMemSkl)
            v107 = 0.0;
          v108 = (f32)(v107 * (f32)v79) / 100.0;
          v109 = v108;
          if (v108 == INFINITY)
            v109 = 0x80000000;
          v79 += v109;
        }
        v110 = v1->Cyuusei;
        *((u32 *)v78 + 8) = v79;
        goto LABEL_88;
      }
    }
    if (!evtBitCheck(2100))
      goto LABEL_135;
    if (v55 != v1->StockIndex0 && v55 != v1->StockIndex1)
    {
LABEL_135:
      v82 = (s64)v1->StockExp + 4 * v55;
      v83 = player->stock_id;
      *(u32 *)(v82 + 32) = a_exp;
      v85 = v83[v55];
      Exp_ChkMemSkl = sBtlGetExp_ChkMemSkl(a_exp, v85);
      v87 = player->stock_id;
      *(u32 *)(v82 + 32) = Exp_ChkMemSkl;
      v88 = v87[v55];
      v89 = sBtlChkHaveMemSkl(v88, 45);
      v90 = v1->StockExp;
      if (v89)
      {
        v77 = v64;
        goto LABEL_141;
      }
      else
      {
        v112 = ((char *)v90 + 4 * v55);
        v113 = (f32)v112[8] / 3.0;
        v114 = v113;
        if (v113 == INFINITY)
          v114 = 0x80000000;
        v112[8] = v114;
        v77 = v64;
      }
LABEL_141:
      LimitRange(((char *)v90 + v57), 0, 99999);
      v92 = v1->Cyuusei;
      v93 = player->stock_id[v55]->devilid;
      v94 = sBtlGetDevilData(v93, -1)->getchuusei * v58;
      v96 = v94;
      if (v94 == INFINITY)
        v96 = 0x80000000;
      v92[v55] = v96;
      v97 = GBWK->player->stock_id[v55];
      v98 = v1->Cyuusei;
      if (v97->bChuuseiDrink)
      {
        v98[v55] *= 2;
        v97 = GBWK->player->stock_id[v55];
        v98 = v1->Cyuusei;
        v97->bChuuseiDrink = 0;
      }
      v99 = (char *)v98 + 4 * v55;
      v100 = *((u32 *)v99 + 8);
      v101 = player->stock_id[v55];
      goto LABEL_153;
LABEL_154:
      v102 = sBtlChkHaveMemSkl(v101, 55);
      v103 = -50.0;
      if (!v102)
        v103 = 0.0;
      v104 = (f32)(v103 * (f32)v100) / 100.0;
      v105 = v104;
      if (v104 == INFINITY)
        v105 = 0x80000000;
      v100 += v105;
      goto LABEL_178;
LABEL_153:
      if (v101)
        goto LABEL_154;
LABEL_178:
      v110 = v1->Cyuusei;
      *((u32 *)v99 + 8) = v100;
      v115 = ((char *)v110 + 4 * v55);
      v116 = (f32)v115[8] / 3.0;
      v117 = v116;
      if (v116 == INFINITY)
        v117 = 0x80000000;
      v115[8] = v117;
LABEL_88:
      LimitRange(((char *)v110 + v57), 0, 100);
      v56 = v1->Cyuusei[v55] + v77;
      goto LABEL_89;
    }
    v56 = v64;
    v1->StockExp[v55] = a_exp;
LABEL_89:
    ++v55;
    v57 += 4;
  }
  v1->drawchu = v56;
  if (v118)
  {
    if ((v60->status3 & 8) == 0)
      goto LABEL_184;
LABEL_190:
    v1->drawchu >>= 1;
  }
  else
  {
    if ((wk->status3 & 8) != 0)
      goto LABEL_190;
LABEL_184:
  }
  sBtlCheckDropItem(v1);
  rstSetReward(v1);
  v121 = wk;
  v122 = Allocate(SBTLDROP_WORK);
  _ctor(v122, 0);
  v121->drop = v122;
}

// 0x1f07930
void sBtlCheckDrop_Normal(SBTLUNIT_WORK *wk) {
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  sdatUnitWork_t *para;
  u32 getexp;
  _BOOL4 v8;
  u32 v11;
  s32 getmag;
  s32 getmoney;
  SBTLDROP_WORK *drop;
  u64 v16;
  SBTLDROP_WORK *v18;
  s32 v19;
  bool v20;
  SBATTLE_WORK *v21;
  SBTLDROP_WORK *v23;
  s32 v24;

  if ((wk->hstatus & 0xA) != 0)
    return;
  devilid = wk->para->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  para = wk->para;
  sBtlGetBadStatus(para);
  wk->drop->setflg = 1;
  getexp = DevilData->getexp;
  v8 = evtBitCheck(2100) && getexp == 0;
  if (v8)
    v11 = 0;
  else
    v11 = getexp;
  getmag = DevilData->getmag;
  getmoney = DevilData->getmoney;
  drop = wk->drop;
  v16 = vadd_s32(*(int32x2_t *)&drop->exp, vdup_n_s32(v11)).n64_u64[0];
  drop->mag += getmag;
  *(u64 *)&drop->exp = v16;
  evtBitCheck(2100);
  v18 = wk->drop;
  v18->gold += getmoney;
  v19 = v18->chuusei + 1;
  v20 = v18->chuusei - 4 < 0;
  v18->chuusei = v19;
  if (v20 == __OFSUB__(v19, 5))
  {
    v18 = wk->drop;
    v18->chuusei = 4;
  }
  v21 = wk;
  v23 = v21->drop;
  v24 = v23->tlev + wk->para->level;
  ++v23->num;
  v23->tlev = v24;
  sBtlSetItem(wk);
  wk->hstatus |= 8u;
}

// 0x1f07780
s32 sBtlGetExpHosei(s32 getexp) {
  SB_ENCOUNTPAC *EncountPac;
  s32 v5;
  s64 v6;
  SB_ENCOUNTPAC *v7;
  s32 level;
  s32 name_high;
  s32 v10;
  s32 v11;
  s32 v12;

  if (getexp >= 1)
  {
    EncountPac = sBtlGetEncountPac(-1);
    v5 = 0;
    v6 = 32;
    v7 = EncountPac[wk->encountno];
    do
    {
      name_high = SHIWORD((*(Il2CppClass **)((char *)&v7->enc1->obj.klass + v6))->_1.name);
      level = sBtlGetDevilData(name_high, -1)->level;
      v6 += 8;
      if (v5 <= level)
        v5 = level;
    }
    while (v6 != 224);
    if (v5)
    {
      v10 = sBtlGetPChara()->para->level - v5;
      if (v10 >= 5)
      {
        v11 = -10 * v10;
        if (v11 <= -90)
          v11 = -90;
        v12 = (v11 + 140) * getexp;
        if ((u32)(v12 + 99) >= 0xC7)
          return v12 / 100;
        else
          return 1;
      }
    }
  }
  return getexp;
}

// 0x1f07c00
void DecVice(SBTLEXP_LISTWORK *lwk, s32 para) {
  ;
}

// 0x1f07c10
void sBtlSetVicePara(SBTLEXP_LISTWORK *lwk, s32 para) {
  ;
}

// 0x1f07c20
void sBtlResetVicePara(SBTLEXP_LISTWORK *lwk) {
  ;
}

// 0x1f07c30
s32 GetViceLevel(void) {
  return 0;
}

// 0x1f07c40
bool sBtlSetRiritu(SBTLEXP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID, u16 mode) {
  return sBtlSetRirituNakamaHD(sBtlEXP, wk, sklid, acterID, mode);
}

// 0x1f07cc0
bool sBtlSetRirituNakamaHD(SBTLEXP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID, u16 mode) {
  u32 v10;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_WORK *v14;
  s32 side;
  SBTLUNIT_WORK *v16;
  void *v17;
  s32 v18;
  s32 vice;
  s32 ViceLevel;
  s32 Riritutbl_n;
  f32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  SBTLUNIT_WORK *v29;
  SBTLUNIT_WORK *v30;
  s32 v31;
  bool v32;

  if (!wk)
    return 0;
  v10 = mode;
  if ((u32)mode - 14 < 7)
    return 0;
  UnitMng = wk->UnitMng;
  v13 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v13)
    return 0;
  v14 = v13;
  if (!sBtlCheckDamageTarget(v13))
    return 0;
  side = v14->side;
  if ((side & 0x80) != 0)
    return 0;
  if ((side & 1) == 0 || (v16 = v14, (wk->side & 1) != 0))
    v16 = wk;
  v17 = NewSpecific(SBTLUNIT_SIDE, 0x14u);
  InitializeArray_55364416(v17, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__4BC99153157C7EE9DC28DA9982389A3AA080FEC7D5F9679C01D71C90FDB223D6, 0);
  if ((sBtlGetSkilltbl(sklid)->type & 0x1000) != 0)
    return 0;
  v18 = mode;
  vice = v16->para->vice;
  ViceLevel = sBtlGetViceLevel(vice);
  Riritutbl_n = sBtlGetRiritutbl_n(wk, v18);
  v24 = Riritutbl_n;
  if (v10 <= 7 && ((1 << v10) & 0xC4) != 0 && (v14->side & 2) != 0 && ((Riritutbl_n > 0) & (BYTE2(v14->status) >> 4)) != 0)
  {
    v24 = v24 * 1.5;
  }
  if (v24 == INFINITY)
    v25 = 0x80000000;
  else
    v25 = v24;
  sBtlViceAddNakamaHD(v16, v25, 0, 4000);
  v26 = v16->para->vice;
  v27 = sBtlGetViceLevel(v26);
  v28 = v16->side;
  if ((v28 & 0x80) != 0)
    v29 = 0;
  else
    v29 = v16;
  if ((v28 & 1) != 0)
    v30 = v29;
  else
    v30 = 0;
  if (ViceLevel >= v27)
  {
    if (ViceLevel > v27 && (v16->side & 0x81) == 1)
    {
      sBtlPlayViceSE(v30, 2);
    }
    return 1;
  }
  v31 = v16->side & 0x81;
  if (v27 == 5)
  {
    if (v31 == 1)
    {
      sBtlPlayViceSE(v30, 3);
      v32 = 1;
      v16->vice_kaisin_cnt = 1200;
      v16->vice_kaisin_flg = 1;
      return v32;
    }
    return 1;
  }
  if (v31 != 1)
    return 1;
  v32 = 1;
  sBtlPlayViceSE(v30, 1);
  return v32;
}

// 0x1f08070
void sBtlViceAddNakamaHD(SBTLUNIT_WORK *wk, s32 add, s16 min, s16 max) {
  sdatUnitWork_t *para;
  s32 v11;

  if ((add & 0x80000000) == 0)
  {
    para = wk->para;
    v11 = (s16)(para->vice + add);
    if (v11 <= min)
      v11 = min;
    if (v11 >= max)
      LOWORD(v11) = max;
    para->vice = v11;
    sBtlSpiritWazaAdd(add, min, max);
  }
}

// 0x1f08130
void sBtlSpiritWazaAdd(s32 add, s32 min, s32 max) {
  s32 sprit_waza;
  bool v10;
  void *Instance;
  f32 SpritRaito;
  f32 v14;
  s32 v15;
  SBATTLE_WORK *v16;
  s32 v17;
  SBATTLE_WORK *v18;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLUNIT_WORK *PChara;

  if (wk)
  {
    if (wk->battlemode == 3)
      return;
  }
  sprit_waza = wk->sprit_waza;
  v10 = evtBitCheck(9998);
  if (add >= 1 && !v10)
    return;
  Instance = get_Instance(0);
  SpritRaito = GetSpritRaito(Instance, 0);
  v14 = SpritRaito * (f32)add;
  if (v14 == INFINITY)
    v15 = 0x80000000;
  else
    v15 = v14;
  v16 = wk;
  v17 = v16->sprit_waza + v15;
  v16->sprit_waza = v17;
  if (v17 > min)
  {
    goto LABEL_22;
  }
  v16->sprit_waza = min;
LABEL_22:
  v18 = wk;
  if (v18->sprit_waza < max)
    return;
  v18->sprit_waza = max;
  if (sprit_waza == max)
    return;
  v18 = wk;
  dvltkList = v18->dvltkList;
  PChara = sBtlGetPChara();
  sBtlCreateDvltk_Gouto(dvltkList, PChara, 263, 2);
}

// 0x1f083b0
s32 sBtlGetSpiritWazaLevel(void) {
  s32 sprit_waza;

  sprit_waza = wk->sprit_waza;
  return sBtlGetViceLevel(sprit_waza);
}

// 0x1f08480
void sBtlClrSpiritWaza(void) {
  wk->sprit_waza = 0;
  return;
}

// 0x1f08510
void sBtlSpiritAddDirect(SBTLUNIT_WORK *wk, s32 mode) {
  s32 v6;

  if (wk && (wk->side & 1) != 0)
  {
    v6 = riritutbl_nb[mode];
    if (!sBtlGetSpiritSkillChk(1452))
    {
LABEL_12:
      sBtlSpiritWazaAdd(v6, 0, 4000);
      return;
    }
    v6 = 120 * v6 / 100;
    goto LABEL_12;
  }
}

// 0x1f08670
void sBtlRwazaSpiritAdd(void) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v4;

  PChara = sBtlGetPChara();
  v4 = PChara;
  sBtlSpiritAddDirect(v4, 0);
}

// 0x1f08700
void sBtlSetumaSpiritAdd(s32 mode) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v6;
  s32 v7;

  PChara = sBtlGetPChara();
  v6 = PChara;
  v7 = mode;
  sBtlSpiritAddDirect(v6, v7);
}

// 0x1f087a0
void sBtlRecoverSpiritAdd(SBTLUNIT_WORK *wk, s32 mode, SKLID sklid) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 v9;

  Skilltbl = sBtlGetSkilltbl(sklid);
  v9 = 1;
  if ((Skilltbl->area & 6) != 0)
  {
    v9 = sBtlGetNakama(0) ? 2 : 1;
    if (sBtlGetNakama(1))
      ++v9;
  }
  do
  {
    sBtlSpiritAddDirect(wk, mode);
    --v9;
  }
  while (v9);
}

// 0x1f08870
void sBtlKofunSpiritAdd(SBTLUNIT_WORK *wk, s32 mode, SKLID sklid) {
  s32 v6;

  if (sBtlGetNakama(0))
    v6 = 2;
  else
    v6 = 1;
  if (sBtlGetNakama(1))
    ++v6;
  do
  {
    sBtlSpiritAddDirect(wk, mode);
    --v6;
  }
  while (v6);
}

// 0x1f08920
bool sBtlIsSpiritWaza(void) {
  s32 sprit_waza;

  sprit_waza = wk->sprit_waza;
  return sBtlGetViceLevel(sprit_waza) == 5;
}

// 0x1f08a40
bool sBtlIsSpiritWazaAndEnemyLive(void) {
  if (!sBtlIsSpiritWaza())
    return 0;
  return sBtlChkSceneEnemyLive();
}

// 0x1f08b00
void sBtlEnemyViceInit(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v10;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0)
    {
      CalcInitVice(sBtlEXP);
    }
  }
  wk->spirit_enemy = 0;
  if (sBtlCheckMoon(8))
    v10 = 180;
  else
    v10 = 0;
  wk->vice1stKoufun = v10;
  return;
}

// 0x1f08ce0
static s32 CalcInitVice(SBTLUNIT_WORK *wk) {
  SB_ENCOUNTPAC *EncountPac;
  SB_ENCOUNTPAC *v4;
  bool v5;

  EncountPac = sBtlGetEncountPac(-1);
  v4 = EncountPac[wk->encountno];
  sBtlGetViceLevel(0);
  sBtlGetPChara();
  if ((~v4->flag & 6) == 0)
    return 0;
  v5 = sBtlCheckMoon(8);
  if (!v5)
  {
    sBtlCheckMoon(0);
    return 0;
  }
  return sBtlGetViceLevelValue(5);
}

// 0x1f08e60
void sBtlNakamaViceInit(SBTLUNIT_WORK *_unit) {
  SB_ENCOUNTPAC *EncountPac;
  SB_ENCOUNTPAC *v5;
  s32 vice;
  bool v7;
  s16 v9;
  sdatUnitWork_t *v10;
  s32 devilid;
  s16 ViceLevelValue;
  sdatUnitWork_t *para;

  EncountPac = sBtlGetEncountPac(-1);
  if (unit)
  {
    v5 = EncountPac[wk->encountno];
    vice = unit->para->vice;
    sBtlGetViceLevel(vice);
    if ((~v5->flag & 6) != 0 && !unit->para->geturei_vice_flag)
    {
      v7 = sBtlCheckMoon(8);
      if (!v7)
      {
        sBtlCheckMoon(0);
LABEL_19:
        if (wk->encountno != 517)
          return;
        devilid = (u16)unit->para->devilid;
        if (devilid == 52 || devilid == 13)
        {
          ViceLevelValue = sBtlGetViceLevelValue(5);
          para = unit->para;
          para->vice = ViceLevelValue;
          para->geturei_vice_flag = 1;
        }
        return;
      }
      v9 = sBtlGetViceLevelValue(5);
      v10 = unit->para;
      v10->vice = v9;
      v10->geturei_vice_flag = 1;
    }
    goto LABEL_19;
  }
}

// 0x1f09070
bool sBtlSetRirituEnemyHD(SBTLEXP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid, s32 acterID, s32 mode) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v12;
  s32 side;
  s32 vice;
  s32 ViceLevel;
  s32 v18;
  s32 v19;

  if (!wk)
    return 0;
  UnitMng = wk->UnitMng;
  v11 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v11)
    return 0;
  v12 = v11;
  if (!sBtlCheckDamageTarget(v11))
    return 0;
  side = wk->side;
  if ((v12->side & 2) != 0)
  {
    if ((side & 2) == 0)
      wk = v12;
  }
  else if ((side & 2) == 0)
  {
    return 0;
  }
  vice = wk->para->vice;
  ViceLevel = sBtlGetViceLevel(vice);
  if (mode == 16 && ViceLevel == 5)
  {
    if (!wk->weak_cnt)
    {
      mode = 16;
      wk->weak_cnt = 1;
      goto LABEL_27;
    }
    mode = 17;
  }
LABEL_27:
  if (mode != 5 || riritutbl_e[5] < 0)
    return 0;
  v18 = wk->para->vice;
  v19 = sBtlGetViceLevel(v18);
  sBtlEnemyViceKoufun(ViceLevel, v19);
  return 1;
}

// 0x1f092f0
void sBtlEnemyViceKoufun(s32 oldlevel, s32 nowlevel) {
  s64 v5;
  char v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v11;

  if (nowlevel == 5 && oldlevel <= 4)
  {
    v5 = 0;
    v6 = 0;
    while (1)
    {
      UnitMng = wk->UnitMng;
      if (v5 >= UnitMng->number)
      {
        if ((v6 & 1) != 0)
        {
          sBtlGetViceLevelValue(5);
          sBtlGetViceLevelValue(3);
        }
        return;
      }
      pUnit = UnitMng->pUnitL[v5]->pUnit;
      if (!pUnit)
        goto LABEL_7;
      if ((pUnit->side & 2) == 0)
        goto LABEL_7;
      para = pUnit->para;
      if (sBtlIsKoufun(pUnit->para))
        goto LABEL_7;
      if ((pUnit->status & 0x100000) != 0 || GetPercentage() <= 0x45u)
      {
        sBtlSetBadStatus_No(pUnit, 0, 5u, 0, -1);
      }
      v11 = pUnit->para;
      v6 |= sBtlGetBadStatus(v11) == 5;
LABEL_7:
      ++v5;
    }
  }
}

// 0x1f08e50
void sBtlViceAddEnemyHD(SBTLUNIT_WORK *wk, s32 add, s16 min, s16 max) {
  ;
}

// 0x1f09520
bool Proc(SBTLEXP_LISTWORK *lwk) {
  SBTLEXP_WORK *ewk;
  s32 ralpha;
  s32 v7;
  f32 v8;
  s32 alpha;

  if (!lwk)
    return 0;
  ewk = lwk->ewk;
  ++lwk->counter;
  LimitRange_2(&lwk->counter, 0, 180);
  if (lwk->counter >= 180)
    *(u64 *)&lwk->ganpon = 0x3F80000000000000LL;
  ralpha = lwk->ralpha;
  if (ralpha >= 1)
  {
    if (ralpha == 128)
    {
      ++lwk->rcounter;
      LimitRange(&lwk->rcounter, 0, 60);
      if (lwk->rcounter >= 60)
      {
        v7 = lwk->ralpha - 1;
        v8 = lwk->ganpon * lwk->riritu;
        lwk->alpha = 255;
        lwk->ralpha = v7;
        lwk->ganpon = v8;
      }
    }
    else
    {
      lwk->ralpha = ralpha - 16;
      LimitRange(&lwk->ralpha, 0, 128);
    }
  }
  alpha = lwk->alpha;
  if (alpha >= 129)
  {
    lwk->alpha = alpha - 8;
    LimitRange(&lwk->alpha, 128, 255);
  }
  if (!ewk || !lwk->num)
    return 0;
  if (IsSceanStop())
    return 0;
  lwk->za_cnt = 0;
  do
  {
    if (ewk->status == 1)
    {
      ewk->alpha -= 4;
      LimitRange(&ewk->alpha, 0, 128);
      ewk->y -= 2;
      if (ewk->alpha <= 0)
        ewk->status = 2;
    }
    ewk = ewk->next;
  }
  while (ewk);
  return 1;
}

// 0x1f09760
bool sBtlDraw(SBTLEXP_LISTWORK *lwk) {
  return 1;
}

// 0x1f09770
bool sBtlReleaseEXP_List(SBTLEXP_LISTWORK *lwk, u8 flg) {
  SBTLEXP_LISTWORK *v3;
  SBTLEXP_WORK *p_ewk;
  SBTLEXP_WORK *ewk;
  SBTLEXP_WORK *prev;
  SBTLEXP_WORK *v7;
  SBTLEXP_WORK *next;
  SBTLEXP_WORK *v9;
  SBTLEXP_WORK *v10;
  SBTLEXP_WORK *v11;
  SBTLEXP_WORK *v12;
  SBTLEXP_WORK *v13;
  SBTLEXP_WORK *v14;
  SBTLEXP_WORK *v15;
  SBTLEXP_WORK *v16;
  SBTLEXP_WORK *v17;

  if (lwk)
  {
    v3 = lwk;
    p_ewk = &lwk->ewk;
    ewk = lwk->ewk;
    if (ewk && lwk->num)
    {
      if (flg)
      {
        while (1)
        {
          prev = ewk->prev;
          ewk->status = 2;
          if (prev)
            break;
          v9 = 0;
          next = ewk->next;
          if (next)
            goto LABEL_9;
LABEL_10:
          if (!v9)
          {
            v10 = ewk->next;
            p_ewk = v10;
            v11 = p_ewk;
            if (p_ewk)
            {
              v11->prev = 0;
            }
          }
          ewk = ewk->next;
          --v3->num;
          if (!ewk)
            goto LABEL_28;
        }
        v7 = ewk->next;
        prev->next = v7;
        v9 = ewk->prev;
        next = ewk->next;
        if (!next)
          goto LABEL_10;
LABEL_9:
        next->prev = v9;
        v9 = ewk->prev;
        goto LABEL_10;
      }
      while (1)
      {
        while (ewk->status != 2)
        {
          ewk = ewk->next;
          if (!ewk)
            goto LABEL_28;
        }
        v12 = ewk->prev;
        if (v12)
          break;
        v15 = 0;
        v14 = ewk->next;
        if (v14)
          goto LABEL_19;
LABEL_20:
        if (!v15)
        {
          v16 = ewk->next;
          p_ewk = v16;
          v17 = p_ewk;
          if (p_ewk)
          {
            v17->prev = 0;
          }
        }
        ewk = ewk->next;
        --v3->num;
        if (!ewk)
        {
LABEL_28:
          LOBYTE(lwk) = 1;
          return (char)lwk;
        }
      }
      v13 = ewk->next;
      v12->next = v13;
      v15 = ewk->prev;
      v14 = ewk->next;
      if (!v14)
        goto LABEL_20;
LABEL_19:
      v14->prev = v15;
      v15 = ewk->prev;
      goto LABEL_20;
    }
    LOBYTE(lwk) = 0;
  }
  return (char)lwk;
}

// 0x1f098e0
bool sBtlDeleteEXPList(SBTLEXP_LISTWORK *lwk) {
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v7;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v9;

  wk_local = wk;
  if (wk_local->UnitMng)
  {
    {
      wk_local = wk;
      if (wk_local->member_num >= 1)
      {
        wk_local = wk;
        UnitMng = wk_local->UnitMng;
        v7 = wk_local->summonindex[0];
        v8 = sBtlSearchUnit_ID(UnitMng, v7);
        if (v8)
        {
          v9 = v8;
          sBtlCheckDamageTarget(v9);
        }
      }
    }
  }
  sBtlReleaseEXP_List(lwk, 1u);
  return 1;
}
