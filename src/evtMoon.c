#include "types.h"
#include "cmpkuda.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fld.h"
#include "itf.h"
#include "kernel.h"
#include "sbtlsub.h"
#include "scrcommand.h"
#include "sdat.h"
#include "slmain.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;

static dds3ProcessID_t *moonprocess_id;
sprHandle_t *moon_spr;
static u32 gMoonBaseARate;
static s32 gMoonFade;
static s32 gMoonFadeFrame;
static s32 gMoonFadeFrameMax;
static f32 gMoonCnt;
static s32 gMoonCngCnt;
static s32 gMoonAgeOld;
static s32 gMoonAge16Old;
static f32 s_aanm;
s32 LoyaltyID;
s16 LoyaltyAdd;

static void PreCalcFade(s32 Frame);
static void CalcBlendColor(u32 *pDstCol, u32 *pSrcCol, s32 AlphaRate);
static dds3ProcessFunc_t Process2(dds3ProcessID_t *id);
static dds3ProcessFunc_t Process1(dds3ProcessID_t *id);
static void Shutdown(dds3ProcessID_t *id);

// 0x1a25210
void evtMoonTakaraCntReset(bool SummonDV) {
  s8 v3;
  s32 StockDevilIndex;
  s32 i;
  sdatUnitWork_t *StockUnitWork;

  v3 = sub_1905740(5, 0) + 6;
  if (SummonDV)
  {
    StockDevilIndex = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
    cmpGetStockUnitWork(StockDevilIndex)->TakaraCnt = v3;
  }
  else
  {
    for (i = 0; ; ++i)
    {
      if (i >= GBWK->player->stock_max)
        break;
      StockUnitWork = cmpGetStockUnitWork(i);
      StockUnitWork->TakaraCnt = v3;
    }
  }
}

// 0x1a25340
void evtMoonZeniCntReset(bool SummonDV) {
  s8 v3;
  s32 StockDevilIndex;
  s32 i;
  sdatUnitWork_t *StockUnitWork;

  v3 = sub_1905740(5, 0) + 6;
  if (SummonDV)
  {
    StockDevilIndex = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
    cmpGetStockUnitWork(StockDevilIndex)->ZeniCnt = v3;
  }
  else
  {
    for (i = 0; ; ++i)
    {
      if (i >= GBWK->player->stock_max)
        break;
      StockUnitWork = cmpGetStockUnitWork(i);
      StockUnitWork->ZeniCnt = v3;
    }
  }
}

// 0x1a25470
void evtMoonTakumiCntReset(void) {
  s32 v1;
  s8 i;
  sdatUnitWork_t *StockUnitWork;

  v1 = 0;
  for (i = sub_1905740(5, 0) + 16; ; StockUnitWork->TakumiCnt = i)
  {
    if (v1 >= GBWK->player->stock_max)
      break;
    StockUnitWork = cmpGetStockUnitWork(v1++);
  }
  GBWK->Moon->TakumiCnt = 0;
}

// 0x1a25570
void evtMoonTeisatuCntReset(void) {
  GBWK->Moon->TeisatuCnt = 1;
}

// 0x1a255e0
void evtMoonLoyaltyDataClear(void) {
  LoyaltyID = 0;
  LoyaltyAdd = 0;
  return;
}

// 0x1a25670
void evtMoonLoyaltyCntClear(void) {
  GBWK->Moon->LoyaltyCnt = -1;
}

// 0x1a256e0
void evtMoonLoyaltyCntReset(void) {
  GBWK->Moon->LoyaltyCnt = 16;
}

// 0x1a25750
void evtMoonLoyaltyCntUpdate(void) {
  evtMoon_t *Moon;
  s32 LoyaltyCnt;
  s8 v5;
  s32 mapSummonID;
  s32 v10;
  u32 mapSummonUNIQ;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v13;
  s32 chuusei;
  s32 v18;
  f32 getchuusei;
  s32 v21;
  s16 v23;

  if (GBWK->mapSummonID < 1)
    return;
  Moon = GBWK->Moon;
  LoyaltyCnt = Moon->LoyaltyCnt;
  if (LoyaltyCnt >= 1)
  {
    v5 = LoyaltyCnt - 1;
    Moon->LoyaltyCnt = v5;
    if (!v5)
    {
      mapSummonID = GBWK->mapSummonID;
      v10 = mapSummonID;
      mapSummonUNIQ = GBWK->mapSummonUNIQ;
      LoyaltyID = mapSummonID;
      stock_id = GBWK->player->stock_id;
      v13 = stock_id[datGetStockDevilIndex(v10, mapSummonUNIQ)];
      chuusei = v13->chuusei;
      if (chuusei <= 99)
      {
        v18 = GBWK->mapSummonID;
        getchuusei = sBtlGetDevilData(v18, -1)->getchuusei;
        if (getchuusei == INFINITY)
          v21 = 0;
        else
          v21 = getchuusei;
        LoyaltyAdd = v21;
        if (v21 + chuusei >= 99)
        {
          LoyaltyAdd = 99 - chuusei;
        }
        v23 = v13->chuusei;
        v13->chuusei = LoyaltyAdd + v23;
        datAddTotalCyuusei(GBWK->player->para, LoyaltyAdd);
LABEL_22:
        goto LABEL_23;
      }
      else
      {
        goto LABEL_22;
      }
LABEL_23:
      GBWK->Moon->LoyaltyCnt = 16;
      return;
    }
  }
}

// 0x1a25ab0
bool evtMoonLoyaltyCntCheck(void) {
  if (GBWK->mapSummonID < 1)
    return 0;
  if (GBWK->Moon->LoyaltyCnt)
    return 0;
  return 1;
}

// 0x1a25b80
void evtMoonLoyaltyWinSetup(void) {
  void *devilReportWin;

  if (LoyaltyID < 1)
    return;
  if (LoyaltyAdd >= 1)
  {
    if (WinCheck(fldUI->devilReportWin, 0))
      return;
    devilReportWin = fldUI->devilReportWin;
    AddReport(devilReportWin, 2, "SYSMES_L0171", LoyaltyID, LoyaltyAdd, 0);
    LoyaltyID = 0;
    LoyaltyAdd = 0;
    return;
  }
}

// 0x1a25d70
s32 evtMoonGetAge(void) {
  u32 Age;

  Age = GBWK->Moon->Age;
  if (Age <= 8)
    return GBWK->Moon->Age;
  else
    return 8 - (Age & 7);
}

// 0x1a25df0
s32 evtMoonGetAge16(void) {
  return GBWK->Moon->Age;
}

// 0x1a25e60
void evtMoonSetAge(u32 age) {
  char v2;
  evtMoon_t *Moon;

  v2 = age;
  Moon = GBWK->Moon;
  Moon->Age = v2 & 0xF;
  Moon->MoveCnt = 0.0;
}

// 0x1a25ee0
void evtMoonSetAgeBit(s32 age) {
  s32 *v3;
  s64 v4;
  s32 v5;
  s64 v6;
  s32 v7;
  s32 v9;
  s64 v11;

  v3 = NewSpecific(s32, 9u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__32C1B1A15673067C6091843887F8B6B08C1E95F67C78EF174576162DD563FBBD, 0);
  if (*(s32 *)((char *)v3 + 24) >= 1)
  {
    v4 = 0;
    v5 = (u8)byte_5755E7B;
    do
    {
      v7 = *(u32 *)((s64)&v3[0] + 4 * v4);
      if (!v5)
      {
        v5 = 1;
        v5 = (u8)byte_5755E7B;
      }
      ++v4;
      v6 = (s64)GBWK->EventBit + 4 * (v7 / 32);
      *(u32 *)(v6 + 32) &= ~(1 << v7);
    }
    while (v4 < *(s32 *)((char *)v3 + 24));
  }
  v9 = v3[age];
  if (!v9)
    return;
  if ((u32)(v9 - 2618) >= 0xFFFFFFC6)
    evtBitKityouItemAdd(v9);
  v11 = (s64)GBWK->EventBit + 4 * (v9 / 32);
  *(u32 *)(v11 + 32) |= 1 << v9;
}

// 0x1a260d0
void evtMoonEnableCalc(void) {
  evtMoon_t *Moon;

  Moon = GBWK->Moon;
  Moon->Stat |= 1u;
}

// 0x1a26140
void evtMoonDisableCalc(void) {
  evtMoon_t *Moon;

  Moon = GBWK->Moon;
  Moon->Stat &= ~1u;
}

// 0x1a261b0
void evtMoonEnableDraw(void) {
  fieldUIDispFlag = 1;
  GBWK->Moon->Stat |= 2u;
  gMoonFade = 1;
  *(u64 *)&gMoonFadeFrameMax = 0x3F80000000000000LL;
  fldSetupObject(txtMgr->moon, 1);
  if (fldGb->fieldID == 16)
  {
    if (!op_Inequality(GetureiUI, 0, 0))
      return;
    GetureiDraw(GetureiUI, 0);
  }
}

// 0x1a26390
void evtMoonDisableDraw(bool fldobjout_reset) {
  void *moon;

  GBWK->Moon->Stat &= ~2u;
  *(u64 *)&gMoonFadeFrameMax = 0;
  gMoonFade = 0;
  moon = txtMgr->moon;
  fldSetupObject(moon, 0);
  if (!op_Inequality(GetureiUI, 0, 0))
  {
    if (!fldobjout_reset)
      return;
    goto LABEL_14;
  }
  GetureiInit(GetureiUI, 0);
  if (!fldobjout_reset)
    return;
LABEL_14:
  scrFldObjOutReset();
}

// 0x1a265a0
void evtMoonEnableDraw2(void) {
  fieldUIDispFlag = 1;
  GBWK->Moon->Stat |= 2u;
  gMoonFade = 1;
  gMoonFadeFrameMax = 0;
}

// 0x1a26680
void evtMoonDisableDraw2(void) {
  GBWK->Moon->Stat &= ~2u;
  gMoonFade = 0;
  gMoonFadeFrameMax = 0;
}

// 0x1a26740
bool evtMoonGetDraw(void) {
  return (GBWK->Moon->Stat >> 1) & 1;
}

// 0x1a267b0
static void PreCalcFade(s32 Frame) {
  if (Frame)
  {
    if (gMoonFadeFrameMax)
    {
      gMoonFadeFrame = gMoonFadeFrame * Frame / gMoonFadeFrameMax;
      return;
    }
    if (!gMoonFade)
      Frame = 0;
    gMoonFadeFrame = Frame;
  }
}

// 0x1a268b0
void evtMoonFadeIn(s32 Frame) {
  GBWK->Moon->Stat |= 2u;
  gMoonCnt = 1.0;
  PreCalcFade(Frame);
  gMoonFadeFrameMax = Frame;
  gMoonFade = 1;
}

// 0x1a26980
void evtMoonFadeOut(s32 Frame) {
  PreCalcFade(Frame);
  gMoonFadeFrameMax = Frame;
  gMoonFade = 0;
}

// 0x1a26a00
s32 evtMoonFadeCheck(void) {
  if (!gMoonFadeFrame)
    return 1;
  return gMoonFadeFrame == gMoonFadeFrameMax;
}

// 0x1a26ab0
static void CalcBlendColor(u32 *pDstCol, u32 *pSrcCol, s32 AlphaRate) {
  ;
}

// 0x1a26ac0
static dds3ProcessFunc_t Process2(dds3ProcessID_t *id) {
  void *moon;
  void *v8;
  void *v9;
  s32 v18;
  s32 v20;
  s32 v21;
  u32 v23;
  s32 v24;
  s32 v25;
  u8 Stat;
  u32 v29;
  void *v30;

  NewSpecific(uint, 4u);
  NewSpecific(uint, 4u);
  NewSpecific(uint, 4u);
  NewSpecific(uint, 4u);
  if (evtBitCheck(2100))
  {
    moon = txtMgr->moon;
    fldSetupObject(moon, 0);
    return 0;
  }
  if (fmProcessChk())
  {
    goto LABEL_11;
LABEL_67:
    v8 = txtMgr->moon;
    goto LABEL_12;
  }
  if (gMoonCngCnt >= 1)
  {
    gMoonCngCnt = gMoonCngCnt - 1;
  }
  if (dds3BistaCheck())
    return 0;
  if (gMoonFade)
  {
    v18 = gMoonFadeFrame + 1;
    gMoonFadeFrame = v18;
    if (v18 > gMoonFadeFrameMax)
    {
      gMoonFadeFrame = gMoonFadeFrameMax;
    }
    goto LABEL_53;
  }
  v20 = gMoonFadeFrame - 1;
  gMoonFadeFrame = v20;
  if (v20 >= 0)
    goto LABEL_42;
  goto LABEL_9001;
  if (v21 >= 0)
  {
LABEL_42:
    goto LABEL_43;
  }
LABEL_9001:
  gMoonFadeFrame = 0;
LABEL_43:
  if (gMoonFadeFrame)
    goto LABEL_53;
  evtMoonDisableDraw(0);
LABEL_53:
  v24 = gMoonFadeFrameMax;
  if (v24 < 1)
  {
    if (v23)
    {
      v25 = (gMoonFade != 0) << 8;
    }
    else
    {
      v25 = (gMoonFade != 0) << 8;
    }
  }
  else
  {
    if (!v23)
    {
      v24 = gMoonFadeFrameMax;
    }
    v25 = (gMoonFadeFrame << 8) / v24;
  }
  gMoonBaseARate = v25;
  Stat = GBWK->Moon->Stat;
  if ((Stat & 2) != 0)
  {
    v30 = txtMgr->moon;
    fldSetupObject(v30, 1);
    if (!op_Inequality(GetureiUI, 0, 0))
      return 0;
    GetureiDraw(GetureiUI, 0);
    return 0;
  }
  if (!v29)
    goto LABEL_67;
LABEL_11:
  v8 = txtMgr->moon;
LABEL_12:
  fldSetupObject(v8, 0);
  v9 = GetureiUI;
  if (!op_Inequality(GetureiUI, 0, 0))
    return 0;
  GetureiInit(GetureiUI, 0);
  return 0;
}

// 0x1a27010
void evtMoonAddMove(f32 leng) {
  evtMoon_t *Moon;
  f32 v6;
  u32 Age;
  evtMoon_t *v11;
  u8 v12;
  evtMoon_t *v13;
  u32 v14;
  s32 v15;
  u32 v20;
  dds3GlobalWork_t *v21;
  s32 mapSummonID;
  s32 StockDevilIndex;
  sdatUnitWork_t *StockUnitWork;
  s8 v26;
  s8 v27;
  s8 v28;
  evtMoon_t *v30;
  s8 v31;

  if (!evtBitCheck(2100))
  {
    Moon = GBWK->Moon;
    v6 = Moon->MoveCnt + leng;
    Moon->MoveCnt = v6;
    if (v6 > 4000.0)
    {
      Moon->MoveCnt = 0.0;
      Age = GBWK->Moon->Age;
      if (Age > 8)
        Age = 8 - (Age & 7);
      gMoonAgeOld = Age;
      v11 = GBWK->Moon;
      gMoonCngCnt = 85;
      LODWORD(v11) = v11->Age;
      gMoonAge16Old = (s32)v11;
      v12 = ((u8)v11 + 1) & 0xF;
      v13 = GBWK->Moon;
      v13->Age = v12;
      v13->MoveCnt = 0.0;
      v14 = GBWK->Moon->Age;
      if (v14 <= 8)
        v15 = GBWK->Moon->Age;
      else
        v15 = 8 - (v14 & 7);
      evtMoonSetAgeBit(v15);
      if (GBWK->Moon->Age)
      {
        goto LABEL_32;
      }
      mapEsutoMaClearMsg();
      mapRiberaMaClearMsg();
      mapEsutoMa2ClearMsg();
      mapRiberaMa2ClearMsg();
      mapMoudokuClearMsg();
LABEL_32:
      v20 = GBWK->Moon->Age;
      if (v20 > 8)
        v20 = 8 - (v20 & 7);
      if (v20 == 8)
      {
        GBWK->fldSave->kiretsuClr = 1;
LABEL_38:
        v21 = GBWK;
        mapSummonID = v21->mapSummonID;
        if (mapSummonID >= 1)
          goto LABEL_39;
        goto LABEL_87;
      }
      {
        goto LABEL_38;
      }
      v21 = GBWK;
      mapSummonID = v21->mapSummonID;
      if (mapSummonID >= 1)
      {
LABEL_39:
        v21 = GBWK;
        mapSummonID = v21->mapSummonID;
        StockDevilIndex = datGetStockDevilIndex(mapSummonID, v21->mapSummonUNIQ);
        StockUnitWork = cmpGetStockUnitWork(StockDevilIndex);
LABEL_45:
        if (mapGetSkilTakaraSagasiMapCheck() && StockUnitWork)
        {
          v26 = StockUnitWork->TakaraCnt - 1;
          if (v26 < 0)
            v26 = 0;
          StockUnitWork->TakaraCnt = v26;
        }
        if (mapGetSkilZeniSagasiMapCheck() && StockUnitWork)
        {
          v27 = StockUnitWork->ZeniCnt - 1;
          if (v27 < 0)
            v27 = 0;
          StockUnitWork->ZeniCnt = v27;
        }
        if (mapGetSkilTakumiMapCheck() && StockUnitWork)
        {
          v28 = StockUnitWork->TakumiCnt - 1;
          if (v28 < 0)
            v28 = 0;
          StockUnitWork->TakumiCnt = v28;
        }
        v30 = GBWK->Moon;
        v31 = v30->TeisatuCnt - 1;
        v30->TeisatuCnt = v31;
        if (v31 < 0)
        {
          v30 = GBWK->Moon;
          v30->TeisatuCnt = 0;
LABEL_68:
          evtMoonLoyaltyCntUpdate();
          goto LABEL_70;
        }
        else
        {
          goto LABEL_68;
        }
        evtMoonLoyaltyCntUpdate();
LABEL_70:
        if ((u32)((s32)(f32)sdatCalcDrink() - 128) <= 0xE)
        {
          mapDrinkClearMsg();
        }
        return;
      }
LABEL_87:
      StockUnitWork = 0;
      goto LABEL_45;
    }
  }
}

// 0x1a27650
static dds3ProcessFunc_t Process1(dds3ProcessID_t *id) {
  s32 v3;
  s32 *EventBit;
  _BOOL4 v5;
  s32 *v6;
  _BOOL4 v7;
  s32 *v8;
  _BOOL4 v9;
  s32 *v10;
  _BOOL4 v11;
  s32 *v12;
  _BOOL4 v13;
  s32 *v14;
  _BOOL4 v15;
  s32 *v16;
  _BOOL4 v17;
  s32 *v18;
  dds3ProcessFunc_t v21;

  v3 = 1;
  EventBit = GBWK->EventBit;
  EventBit[94] &= ~1u;
  if (v3)
  {
LABEL_10:
    v5 = 0;
    goto LABEL_13;
  }
  else
  {
    goto LABEL_10;
  }
  v5 = byte_5755E7B == 0;
LABEL_13:
  v6 = GBWK->EventBit;
  v6[94] &= ~2u;
  v7 = 0;
  v8 = GBWK->EventBit;
  v8[94] &= ~4u;
  v9 = 0;
  v10 = GBWK->EventBit;
  v10[94] &= ~8u;
  v11 = 0;
  v12 = GBWK->EventBit;
  v12[94] &= ~0x10u;
  v13 = 0;
  v14 = GBWK->EventBit;
  v14[94] &= ~0x20u;
  v15 = 0;
  v16 = GBWK->EventBit;
  v16[94] &= ~0x40u;
  v17 = 0;
  v18 = GBWK->EventBit;
  v18[94] &= ~0x80u;
  GBWK->EventBit[94] &= ~0x100u;
  v21 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v21, 0, Method_Project_evtMoon_Process2__, 0);
  return v21;
}

// 0x1a279e0
static void Shutdown(dds3ProcessID_t *id) {
  moonprocess_id = 0;
}

// 0x1a27a50
void evtMoonInitProcess(void) {
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  evtMoon_t *Moon;

  if (moonprocess_id)
    return;
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_evtMoon_Process1__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_evtMoon_Shutdown__, 0);
  started = dds3StartProcess("moon", 11017, 1, 1, v2, v3, 0);
  moonprocess_id = started;
  GBWK->Moon->Stat |= 1u;
  evtMoonDisableDraw(0);
  Moon = GBWK->Moon;
  Moon->Age = 0;
  Moon->MoveCnt = 0.0;
  evtMoonTakaraCntReset(0);
  evtMoonZeniCntReset(0);
  evtMoonTakumiCntReset();
  GBWK->Moon->TeisatuCnt = 1;
}

// 0x1a27d00
void evtMoonFreeProcess(void) {
  if (moonprocess_id)
    goto LABEL_4;
  return;
  if (moonprocess_id)
  {
LABEL_4:
    dds3KillProcess(moonprocess_id, 1);
    return;
  }
}
