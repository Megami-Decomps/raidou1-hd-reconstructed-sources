#include "types.h"
#include "BSTF.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"
#include "aw_kudasupport.h"
#include "dat.h"
#include "evtbit.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtldmg.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtltubesupport.h"
#include "sbtlunit.h"
#include "sdat.h"

#define EFF_WAIT_TIME 80

typedef enum {
    KUDA_SUPPORT_NONE = -1,
    KUDA_SUPPORT_WAIT = 0,
    KUDA_SUPPORT_JUDGE = 1,
    KUDA_SUPPORT_SUPPORT_START = 2,
    KUDA_SUPPORT_SUPPORT_EFF = 3,
    KUDA_SUPPORT_SUPPORT = 4,
    KUDA_SUPPORT_SUPPORT_END = 5,
} KUDA_SUPPORT;

typedef enum {
    HP_JUDGE_TYPE_UP = 0,
    HP_JUDGE_TYPE_DOWN = 1,
} HP_JUDGE_TYPE;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sdatUnitWork_t sdatUnitWork_t;

static s32 counter;
static s32 btsCounter;
static s32 confirm;
static s32 beforeHp;
static bool belowHp;
static bool bstAdhesion;
static SKLID useSkill;
static BSTF beforeBst;
static KUDA_SUPPORT supportState;
static void *tubeNo;
static s32 actionCounter4;
static sdatUnitWork_t *supportUnit;
SBTLUNIT_WORK *supportWk;

static SKLID JudgeUseSkill(SBTLUNIT_WORK *wk);
static f32 GetRatio(SBTLUNIT_WORK *wk, HP_JUDGE_TYPE judgeType);
static s32 ActivationProbability(s32 basic);
static f32 GetTotalLoyalty(void);
static SKLID RandUseAura(bool judgeDir);
static bool IsTubeEmpty(void);
static bool JudgBstAdhesion(SBTLUNIT_WORK *wk);
static bool SelectTargetSide(void);
static bool CheckUsableDlcDvl(s32 id);
static bool LoadSupportSkill(void);
static void UseSupportSkill(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *userWk, SKLID sklid);
static SBTLUNIT_WORK *CreateUnitWork(sdatUnitWork_t *unit, s32 tubeNo);
static void Regener(SBTLUNIT_WORK *tgtwk, SKLID sklid);
static void Aura(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtwk, SKLID sklid);
static void CheckEffectDataSingle(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime);
static bool FlgCheck(void);
bool CheckEffectData_Core(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s32 index, s32 id, SBTLUNIT_SIDE acterside, s32 serialID2, SBTLEFF_TFLG tflg, s32 sttime, s32 count);

// 0x2129550
void sbtlInit(void) {
  s32 tubeSupportCount;

  *(u64 *)&counter = 0;
  beforeHp = -1;
  useSkill = 0;
  supportState = 0;
  *(u16 *)&belowHp = 1;
  tubeSupportCount = GBWK->player->tubeSupportCount;
  if (tubeSupportCount <= 0)
    tubeSupportCount = 0;
  actionCounter4 = tubeSupportCount;
  return;
}

// 0x21296a0
void sbtlProc(void) {
  SBTLUNIT_WORK *PChara;
  s32 battlemode;
  s32 hp;
  s32 v14;
  s32 v15;
  s32 v18;
  sdatUnitWork_t *StockUnitData;
  SBTLUNIT_WORK *UnitWork;
  sbtldvltk_unitworktag *dvltkwk;
  s32 Kucyou;
  u8 *v29;
  u8 **v30;
  void *v31;
  SBTLUNIT_WORK *v32;
  void *pData;
  u8 **v34;
  s32 v35;
  void *Instance;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLUNIT_WORK *v43;
  bool v46;

  if (LoadSupportSkill())
    return;
  PChara = sBtlGetPChara();
  battlemode = (u16)wk->battlemode;
  if (battlemode == 3)
    return;
  battlemode = (u16)wk->battlemode;
  if (battlemode != 1)
  {
    if (evtBitCheck(2065) && (PChara->para->badstatus & 0x20000) == 0)
    {
      if (!IsSceanStop())
      {
        if (!IsTubeEmpty())
        {
          if ((beforeHp & 0x80000000) == 0)
          {
            goto LABEL_27;
          }
          hp = PChara->para->now->hp;
          beforeHp = hp;
LABEL_27:
          if (supportState > 5)
            goto LABEL_81;
          switch (supportState)
          {
            case 0u:
              if (counter < 1200)
                goto LABEL_78;
              v14 = 1;
              goto LABEL_77;
            case 1u:
              v15 = JudgeUseSkill(PChara);
              useSkill = v15;
              counter = counter + 1;
              ++actionCounter4;
              if (v15)
              {
                counter = 0;
                supportState = 2;
              }
              goto LABEL_81;
            case 2u:
              v18 = sbtlSelectDevil();
              StockUnitData = sBtlGetStockUnitData(v18);
              supportUnit = StockUnitData;
              UnitWork = CreateUnitWork(supportUnit, v18);
              supportWk = UnitWork;
              dvltkwk = supportWk->dvltkwk;
              Kucyou = sBtlGetKucyou(supportWk->para->devilid);
              v29 = NewSpecific(byte, pGlobalMsg[Kucyou]->max_length);
              dvltkwk->pData = v29;
              v30 = pGlobalMsg;
              v31 = v30[sBtlGetKucyou(supportWk->para->devilid)];
              v32 = supportWk;
              pData = v32->dvltkwk->pData;
              v34 = pGlobalMsg;
              v35 = sBtlGetKucyou(v32->para->devilid);
              Copy_56180528(v31, pData, v34[v35]->max_length, 0);
              supportState = 3;
              goto LABEL_81;
            case 3u:
              if (counter)
              {
                goto LABEL_55;
              }
              Instance = get_Instance(0);
              HitikotoTubeActive(Instance, 1, 0);
              dvltkList = wk->dvltkList;
              v43 = supportWk;
              sBtlCreateDvltk_Kuda(dvltkList, v43, 3);
              Add(0);
LABEL_55:
              if (counter < 80)
                goto LABEL_78;
              v14 = 4;
LABEL_77:
              supportState = v14;
LABEL_78:
              ++counter;
              ++actionCounter4;
LABEL_81:
              v46 = JudgBstAdhesion(PChara);
              if (v46)
              {
                if (!bstAdhesion)
                {
                  bstAdhesion = 1;
                }
              }
              if ((PChara->para->badstatus & 0x3FC0) != 0)
              {
                goto LABEL_92;
              }
              else
              {
                bstAdhesion = 0;
LABEL_92:
                if (bstAdhesion)
                {
LABEL_93:
                  ++btsCounter;
LABEL_106:
                  if (GetRatio(PChara, 0) > 70.0)
                  {
                    if (!belowHp)
                    {
                      belowHp = 1;
                    }
                  }
                  return;
                }
LABEL_100:
                if (btsCounter)
                {
                  btsCounter = 0;
                }
                goto LABEL_106;
              }
              if (bstAdhesion)
                goto LABEL_93;
              goto LABEL_100;
            case 4u:
              UseSupportSkill(supportWk, PChara, useSkill);
              supportState = 5;
              goto LABEL_81;
            case 5u:
              supportUnit = 0;
              useSkill = 0;
              supportWk = 0;
              counter = 0;
              actionCounter4 = 0;
              supportState = 0;
              goto LABEL_81;
            default:
              goto LABEL_81;
          }
        }
      }
    }
  }
}

// 0x212b1c0
void sbtlEnd(void) {
  sdatUnitWork_t *p_supportUnit;

  *(u64 *)&counter = 0;
  beforeHp = -1;
  useSkill = 0;
  supportState = 0;
  *(u16 *)&belowHp = 1;
  supportUnit = 0;
  p_supportUnit = &supportUnit;
  GBWK->player->tubeSupportCount = *((u32 *)p_supportUnit - 2);
  supportWk = 0;
}

// 0x212a170
static SKLID JudgeUseSkill(SBTLUNIT_WORK *wk) {
  f32 Ratio;
  f32 v8;
  f32 v10;
  f32 v11;
  s32 v12;
  f32 v17;
  f32 v18;
  s32 v19;
  s32 v20;
  bool v21;
  s32 v22;
  s32 v23;
  s32 v25;

  Ratio = GetRatio(wk, 1);
  if (Ratio != -1.0 && Ratio <= 10.0)
    return 112;
  if (btsCounter < 300)
  {
    if (Ratio == -1.0)
      goto LABEL_42;
    goto LABEL_21;
  }
  bstAdhesion = 0;
  btsCounter = 0;
  v8 = GetTotalLoyalty();
  v10 = v8;
  v11 = (f32)((f32)(v10 * 0.2) + (f32)(v10 * 0.2)) + 20.0;
  v12 = (loc_2137B20)(100, 0);
  if (ceilf(v11) != INFINITY && (s32)vcvtps_s32_f32(v11) >= (s64)(u32)(v12 + 1))
    return 116;
  if (Ratio == -1.0)
  {
LABEL_42:
    if ((f32)((f32)((f32)confirm + (f32)(GetTotalLoyalty() * -0.5)) * 60.0) > (f32)actionCounter4)
      return 0;
    v25 = (loc_2137B20)(100, 0) + 1;
    if (v25 >= 30)
    {
      v21 = (u32)v25 > 0x3B;
      v22 = 133;
      v23 = 117;
      goto LABEL_49;
    }
    return 132;
  }
LABEL_21:
  if (Ratio > 70.0)
    goto LABEL_42;
  if (!belowHp)
    goto LABEL_42;
  belowHp = 0;
  v17 = GetTotalLoyalty();
  v18 = (f32)(v17 * 0.2) + 10.0;
  v19 = (loc_2137B20)(100, 0);
  if (ceilf(v18) == INFINITY || (s32)vcvtps_s32_f32(v18) < (s64)(u32)(v19 + 1))
    goto LABEL_42;
  v20 = (loc_2137B20)(100, 0) + 1;
  if (v20 < 30)
    return 132;
  if ((u32)v20 < 0x3C)
    return 133;
  v21 = (u32)v20 > 0x4F;
  v22 = 117;
  v23 = 112;
LABEL_49:
  if (v21)
    return v23;
  else
    return v22;
}

// 0x212b030
static f32 GetRatio(SBTLUNIT_WORK *wk, HP_JUDGE_TYPE judgeType) {
  f32 v7;
  sdatParaWork_t *now;
  s32 hp;
  s32 v12;
  s32 v13;
  sdatUnitWork_t *p_para;

  v7 = -1.0;
  if (beforeHp == -1)
    return v7;
  if (judgeType != 1)
  {
    if (judgeType)
      return v7;
    now = wk->para->now;
    hp = now->hp;
    if (beforeHp == hp)
      return v7;
    v12 = now->hp;
    goto LABEL_21;
  }
  v13 = wk->para->now->hp;
  if (v13 >= beforeHp)
    return v7;
  p_para = &wk->para;
  now = p_para->now;
  hp = now->hp;
  v12 = hp;
LABEL_21:
  beforeHp = hp;
  return (f32)((f32)v12 / (f32)now->maxhp) * 100.0;
}

// 0x212b2a0
static s32 ActivationProbability(s32 basic) {
  f32 v4;
  f32 v6;
  f32 v7;
  s32 v8;

  v4 = GetTotalLoyalty();
  v6 = v4;
  v7 = (f32)((f32)((f32)basic * 0.1) * (f32)(v6 * 0.2)) + (f32)basic;
  v8 = vcvtps_s32_f32(v7);
  if (ceilf(v7) == INFINITY)
    return 0x80000000;
  else
    return v8;
}

// 0x212b420
static f32 GetTotalLoyalty(void) {
  f32 v1;
  s64 i;
  s32 devilid;
  sdatUnitWork_t *v8;

  v1 = 0.0;
  for (i = 0; ; ++i)
  {
    if (i >= datGetStockDevilNums(0))
      break;
    devilid = GBWK->player->stock_id[i]->devilid;
    if (!CheckUsableDlcDvl(devilid))
      continue;
    if (wk->summonID[i])
      continue;
    v8 = GBWK->player->stock_id[i];
    if ((v8->badstatus & 0x20000) == 0)
    {
      v8 = GBWK->player->stock_id[i];
      v1 = v1 + (f32)v8->chuusei;
    }
  }
  return sqrtf(v1);
}

// 0x212b3b0
static SKLID RandUseAura(bool judgeDir) {
  u32 v3;
  s32 v4;
  s32 v5;

  v3 = (loc_2137B20)(100, 0) + 1;
  if (v3 <= 0x3B)
    v4 = 133;
  else
    v4 = 117;
  if (v3 <= 0x4F)
    v5 = 117;
  else
    v5 = 112;
  if (!judgeDir)
    v5 = v4;
  if (v3 >= 0x3C)
    v4 = v5;
  if ((s32)v3 >= 30)
    return v4;
  else
    return 132;
}

// 0x2129fd0
static bool IsTubeEmpty(void) {
  s64 i;
  s64 StockDevilNums;
  s32 devilid;

  for (i = 0; ; ++i)
  {
    StockDevilNums = datGetStockDevilNums(0);
    if (i >= StockDevilNums)
      break;
    devilid = GBWK->player->stock_id[i]->devilid;
    if (!CheckUsableDlcDvl(devilid))
      continue;
    if (wk->summonID[i])
      continue;
    if ((GBWK->player->stock_id[i]->badstatus & 0x20000) == 0)
      return i >= StockDevilNums;
  }
  return i >= StockDevilNums;
}

// 0x212af40
static bool JudgBstAdhesion(SBTLUNIT_WORK *wk) {
  s32 badstatus;
  char v6;
  bool v7;

  badstatus = wk->para->badstatus;
  if ((badstatus & 0x3FC0) != 0)
  {
    if (beforeBst == badstatus)
      goto LABEL_6;
    v6 = 1;
    beforeBst = badstatus;
    return 1;
  }
LABEL_6:
  v6 = 0;
  v7 = 0;
  v7 = v6;
  beforeBst = badstatus;
  return v7;
}

// 0x212a5d0
s32 sbtlSelectDevil(void) {
  s64 v2;
  s32 v3;
  s64 v4;
  s32 devilid;
  s32 v9;
  void *tubeNo_local;
  u64 *v14;
  s64 size;
  s32 *items;
  s32 v19;
  s32 v21;
  sdatUnitWork_t *v24;
  void *v26;
  u64 *v27;
  s64 v28;
  s32 *v29;
  void *v31;
  s32 v32;

  v2 = *((u64 *)*((const MethodInfo *)sbtlTubeSupport + 2).virtualMethodPointer + 4);
  v3 = *(u32 *)(v2 + 28) + 1;
  *(u32 *)(v2 + 24) = 0;
  *(u32 *)(v2 + 28) = v3;
  v4 = 0;
  if (!SelectTargetSide())
  {
    while (1)
    {
      if (v4 >= datGetStockDevilNums(0))
        goto LABEL_75;
      if (!Exists("new_devil"))
      {
        devilid = GBWK->player->stock_id[v4]->devilid;
        if (sBtlIsDLCDevil(devilid))
          goto LABEL_8;
      }
      v9 = GBWK->player->stock_id[v4]->devilid;
      if (!CheckUsableDlcDvl(v9))
        goto LABEL_8;
      if (wk->summonID[v4])
        goto LABEL_8;
      if ((GBWK->player->stock_id[v4]->badstatus & 0x20000) == 0)
      {
        tubeNo_local = tubeNo;
        v14 = Method_System_Collections_Generic_List_int__Add__;
        size = tubeNo_local->_size;
        ++tubeNo_local->_version;
        items = tubeNo_local->_items;
        if ((u32)size >= LODWORD(items->max_length))
        {
          _AddWithResize(tubeNo_local, v4, *(const MethodInfo_2D8F530 **)(*(u64 *)(v14[4] + 192) + 112));
        }
        else
        {
          tubeNo_local->_size = size + 1;
          items[size] = v4;
        }
      }
LABEL_8:
      ++v4;
    }
  }
  while (1)
  {
    if (v4 >= datGetStockDevilNums(0))
      break;
    if (!Exists("new_devil"))
    {
      v19 = GBWK->player->stock_id[v4]->devilid;
      if (sBtlIsDLCDevil(v19))
        goto LABEL_40;
    }
    v21 = GBWK->player->stock_id[v4]->devilid;
    if (!CheckUsableDlcDvl(v21))
      goto LABEL_40;
    if (wk->summonID[v4])
      goto LABEL_40;
    v24 = GBWK->player->stock_id[v4];
    if ((v24->badstatus & 0x20000) == 0)
    {
      if (v24->chuusei < 1)
        goto LABEL_40;
      v26 = tubeNo;
      v27 = Method_System_Collections_Generic_List_int__Add__;
      v28 = v26->_size;
      ++v26->_version;
      v29 = v26->_items;
      if ((u32)v28 >= LODWORD(v29->max_length))
      {
        _AddWithResize(v26, v4, *(const MethodInfo_2D8F530 **)(*(u64 *)(v27[4] + 192) + 112));
      }
      else
      {
        v26->_size = v28 + 1;
        v29[v28] = v4;
      }
    }
LABEL_40:
    ++v4;
  }
LABEL_75:
  v31 = tubeNo;
  v32 = (loc_2137B20)((u32)v31->_size, 0);
  return _get_Item(v31, v32);
}

// 0x212b750
static bool SelectTargetSide(void) {
  s64 i;
  s64 StockDevilNums;
  s32 devilid;
  sdatUnitWork_t *v8;

  for (i = 0; ; ++i)
  {
    StockDevilNums = datGetStockDevilNums(0);
    if (i >= StockDevilNums)
      break;
    devilid = GBWK->player->stock_id[i]->devilid;
    if (!CheckUsableDlcDvl(devilid))
      continue;
    if (wk->summonID[i])
      continue;
    v8 = GBWK->player->stock_id[i];
    if ((v8->badstatus & 0x20000) == 0)
    {
      v8 = GBWK->player->stock_id[i];
      if (v8->chuusei > 0)
        return i < StockDevilNums;
    }
  }
  return i < StockDevilNums;
}

// 0x212b640
static bool CheckUsableDlcDvl(s32 id) {
  if (Exists("new_devil"))
    return 1;
  if (sBtlIsDLCDevil(id))
    return 0;
  return 1;
}

// 0x2129e40
static bool LoadSupportSkill(void) {
  if (!sBtlHDloadChk(112))
    return 1;
  if (!sBtlHDloadChk(116))
    return 1;
  if (!sBtlHDloadChk(117))
    return 1;
  if (!sBtlHDloadChk(133))
    return 1;
  return !sBtlHDloadChk(132);
}

// 0x212ad30
static void UseSupportSkill(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *userWk, SKLID sklid) {
  s32 side;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v13;

  if ((userWk->para->badstatus & 0x20000) == 0)
  {
    side = wk->side;
    CheckEffectDataSingle(wk, sklid, 1u, 0, side, -1, 0);
    if (sklid <= 116)
    {
      if (sklid == 112)
      {
        para = wk->para;
        v13 = GBWK->player->para;
        sdatCalcSkill(para, v13, 112);
      }
      else if (sklid == 116 && (~sBtlGetSkilltbl(116)->flg & 0x10004) == 0)
      {
        sBtlResetBadStatus(userWk, 16320);
      }
    }
    else if (sklid == 117)
    {
      Regener(userWk, 117);
    }
    else if ((sklid & 0xFFFFFFFE) == 0x84)
    {
      Aura(wk, userWk, sklid);
    }
  }
}

// 0x212abb0
static SBTLUNIT_WORK *CreateUnitWork(sdatUnitWork_t *unit, s32 tubeNo) {
  s32 v6;
  s32 minorno;
  SBTLUNIT_WORK *v8;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;

  v6 = wk->stock_id[tubeNo];
  minorno = sBtlGetDevilData(v6, -1)->minorno;
  v8 = sBtlCreateUnit(1u, minorno, 0);
  v8->para = unit;
  v8->side = 1;
  actwk = v8->actwk;
  actwk->use_skillid = useSkill;
  actaiwk = v8->actaiwk;
  actaiwk->targetID = sBtlGetPlayerID();
  return v8;
}

// 0x212bc30
static void Regener(SBTLUNIT_WORK *tgtwk, SKLID sklid) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 attrtime;
  sdatUnitWork_t *para;
  s32 HaveMemSkl;
  sdatUnitWork_t *v9;
  s32 count;
  s32 v11;
  sdatParaWork_t *now;
  f32 n1;
  f32 v14;
  s32 v15;
  s32 v16;

  Skilltbl = sBtlGetSkilltbl(sklid);
  attrtime = Skilltbl->attrtime;
  para = tgtwk->para;
  HaveMemSkl = sBtlChkHaveMemSkl(tgtwk->para, 43);
  v9 = tgtwk->para;
  if (!HaveMemSkl)
    goto LABEL_6;
  goto LABEL_5;
  if (v16)
LABEL_5:
    attrtime += v9->autost_cnt;
LABEL_6:
  count = Skilltbl->count;
  tgtwk->rejyenecnt = 0;
  if (attrtime <= 1)
    v11 = 1;
  else
    v11 = attrtime;
  now = v9->now;
  tgtwk->rejyenecounter = v11;
  n1 = Skilltbl->n1;
  tgtwk->rejyenecmpcnt = v11 / count;
  v14 = (f32)(n1 * (f32)now->maxhp) / 100.0;
  v15 = v14;
  if ((s32)v14 <= 1)
    v15 = 1;
  if (v14 == INFINITY)
    v15 = 1;
  tgtwk->rejyenepara = v15;
}

// 0x212bd50
static void Aura(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgtwk, SKLID sklid) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 side;
  char BothSide;
  s32 attrtime;
  s32 v11;
  f32 n1;
  s32 v13;
  u32 flg;
  _BOOL4 v15;
  bool v16;
  SBTLAI_WORK *aiwk;
  s64 v18;
  s32 v19;
  tagSBTLSKL_AURA_WORK *wkAura;
  s64 v21;
  tagSBTLSKL_AURA_WORK *v22;
  tagSBTLSKL_AURA_WORK *v23;
  SBTLSM_LISTWORK *v26;
  SBTLSM_LISTWORK *v27;
  SBTLUNIT_WORK *v28;
  s32 v29;
  SBTLSM_LISTWORK *sysmsgList;

  Skilltbl = sBtlGetSkilltbl(sklid);
  side = wk->side;
  BothSide = sBtlGetBothSide(wk, side);
  attrtime = Skilltbl->attrtime;
  if (sBtlChkHaveMemSkl(wk->para, 43))
    attrtime += wk->para->autost_cnt;
  v11 = sklid - 131;
  n1 = Skilltbl->n1;
  if (attrtime <= 1)
    v13 = 1;
  else
    v13 = attrtime;
  flg = Skilltbl->flg;
  v15 = v11 == 1;
  v16 = v11 == 2;
  aiwk = wk->aiwk;
  v18 = 2 * v15;
  if (v16)
    v18 = 1;
  v19 = n1;
  tgtwk->aurakind |= flg;
  wkAura = tgtwk->wkAura;
  aiwk->cmndFrm = 0;
  aiwk->cmndFrmMax = v13;
  v21 = v18;
  v22 = wkAura[v21];
  v23 = wk->wkAura[v21];
  v22->auraskl = 0;
  v22->auracnt = v13;
  v23->auraskl = sklid;
  if (n1 == INFINITY)
    v19 = 0x80000000;
  v22->aurapara = v19;
  wk->drawgaugetype = 4;
  if ((flg & 0x7000000) != 0 && (BothSide & 1) != 0)
  {
    if ((flg & 0x2000000) != 0)
    {
      sysmsgList = wk->sysmsgList;
      v29 = 65;
      v27 = sysmsgList;
      v28 = wk;
    }
    else
    {
      v26 = wk->sysmsgList;
      v27 = v26;
      v28 = wk;
      v29 = 64;
    }
    sBtlCreateSM(v27, v28, v29, 0, 0, 120);
  }
}

// 0x212b930
static void CheckEffectDataSingle(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime) {
  s32 v16;
  s32 v17;
  SBTLSKILLP_TBL *Skilltbl;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  s32 EffectData_Num;
  s32 v24;
  s32 v25;
  EFFPDATA_WORK *EffectData;
  s32 count;
  EFFPDATA_WORK *v28;
  sdfVector4_t v29;

  v16 = sBtlSearchEffectData(sklid);
  if (v16 == -1)
    return;
  v17 = v16;
  Skilltbl = sBtlGetSkilltbl(sklid);
  if (Skilltbl)
  {
    if (type == 1)
    {
      if ((Skilltbl->flg2 & 0x100000) != 0)
        goto LABEL_16;
    }
    else if (type == 2 && (Skilltbl->flg2 & 0x200000) != 0)
    {
      goto LABEL_16;
    }
  }
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v29.x = x;
  v29.y = y;
  v29.z = z;
  v29.w = w;
  sBtlPlaySkillSE(v29, sklid, type);
LABEL_16:
  EffectData_Num = sBtlGetEffectData_Num(v17);
  if (EffectData_Num < 1)
    return;
  v24 = EffectData_Num;
  if (flg == 1)
  {
    v25 = 0;
    while (1)
    {
      EffectData = sBtlGetEffectData(v17, v25);
      if (sBtlCheckBEDType(EffectData->type, type))
        break;
      if (v24 == ++v25)
        goto LABEL_26;
    }
  }
  else
  {
    for (count = 0; count != v24; ++count)
    {
      v28 = sBtlGetEffectData(v17, count);
      if (sBtlCheckBEDType(v28->type, type))
      {
        CheckEffectData_Core(wk, sklid, type, v17, count, acterside, serialID2, 0, sttime, count);
      }
    }
LABEL_26:
    AddSerialID2();
    sBtlAddSerialID2();
  }
}

// 0x2129fc0
static bool FlgCheck(void) {
  return evtBitCheck(2065);
}
