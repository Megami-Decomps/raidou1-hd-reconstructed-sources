#include "types.h"
#include "achievement.h"
#include "buttonguide.h"
#include "cmphelp.h"
#include "cmpmodel.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kerneldraw.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "fclmenu.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "itf.h"
#include "nwdnews.h"
#include "sdat.h"
#include "shpaction.h"
#include "shpmain.h"
#include "shpmessage.h"
#include "shpmisc.h"
#include "shpmodel.h"
#include "sndat3.h"

#define NWD_ARRIVAL_CHAPTER_BIT 0

typedef struct tagSHP_WK tagSHP_WK;

tagSHP_WK *wk;
static s32 g_goodrank_old;
static bool g_bRankUp;
bool g_bGuideOff;

static s32 shpSelectList(s32 a_pSelNo, s32 a_pDrwNo, s32 a_pTopNo, s32 a_nmax, s32 a_ndrw, s32 a_acttype);
static s32 shpSelectListPage(void);
static void shpListCtrlSelect(s32 a_acttype);
static void SetStatFadeIn(void);
static bool FadeIn(void);
static void SetStatFadeOut(void);
static bool FadeOut(void);
static s32 shpListUpdateBuySelNum(void);
static s8 shpListCtrlBuySelItem(void);
static s8 shpListCtrlSelNum(s32 a_type);
static void UpdateInit(void);
static void UpdateBuyReturnList(void);
static s32 shpListUpdateSellSelectNum(void);
static s8 shpListCtrlSellSelectItem(void);
static void UpdateSellReturnList(void);
static s32 GetStepAct(void);
static s8 shpListCtrlTradeSelectDevil(void);
static s8 shpListCtrlOrderSelectItem(void);
static bool GuideOnOffChack(void);
static void EnterSetMsg(void);
static void TalkSetMotionStart(void);
static void TalkSetMotionEnd(void);
static bool TalkSetMotionSpeak(void);
void _shpReadNewArrival(s32 a_type, s32 a_itemID);
void LoadFile(char **filename);

// 0x2173a80
void shpSetWork(tagSHP_WK *a_pWork) {
  if (a_pWork)
  {
    wk = a_pWork;
  }
}

// 0x2173af0
static s32 shpSelectList(s32 a_pSelNo, s32 a_pDrwNo, s32 a_pTopNo, s32 a_nmax, s32 a_ndrw, s32 a_acttype) {
  s32 v14;
  char v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  char v22;

  if (a_acttype != 1058 && a_acttype != 138)
  {
    v17 = 0;
    v16 = 0;
    v14 = 0;
    v15 = 1;
    if (CHECK_TRIG(4100, 1))
      goto LABEL_22;
    goto LABEL_13;
  }
  v14 = s_wk->index[a_pSelNo];
  if (shpChkNewArrival(v14, a_acttype))
    goto LABEL_10;
  goto LABEL_21;
  if (!shpChkNewArrival(v14, a_acttype))
  {
LABEL_21:
    v17 = 0;
    v16 = 0;
    v15 = 1;
    if (CHECK_TRIG(4100, 1))
      goto LABEL_22;
LABEL_13:
    if (CHECK_REP(4100, 1))
    {
      v18 = a_pSelNo - 1;
      if (a_pSelNo - 1 >= 0)
        goto LABEL_23;
      v18 = 0;
      if (CHECK_TRIG(4101, 1))
        goto LABEL_26;
    }
    else
    {
      v18 = a_pSelNo;
      if (CHECK_TRIG(4101, 1))
        goto LABEL_26;
    }
LABEL_33:
    if (!CHECK_REP(4101, 1))
      goto LABEL_37;
    if (++v18 >= a_nmax)
    {
      v18 = a_nmax - 1;
      if (a_nmax - 1 == a_pSelNo)
        goto LABEL_38;
      goto LABEL_40;
    }
LABEL_35:
    if (++a_pDrwNo >= a_ndrw)
    {
      a_pDrwNo = a_ndrw - 1;
      ++a_pTopNo;
    }
LABEL_37:
    if (v18 == a_pSelNo)
      goto LABEL_38;
    goto LABEL_40;
  }
LABEL_10:
  v15 = 0;
  v16 = a_pSelNo;
  v17 = a_acttype != 138;
  if (!CHECK_TRIG(4100, 1))
    goto LABEL_13;
LABEL_22:
  v18 = a_pSelNo - 1;
  if (a_pSelNo - 1 < 0)
  {
    v18 = a_nmax - 1;
    a_pDrwNo = a_ndrw - 1;
    if (a_nmax <= a_ndrw)
      a_pTopNo = 0;
    else
      a_pTopNo = a_nmax - a_ndrw;
    if (!CHECK_TRIG(4101, 1))
      goto LABEL_33;
    goto LABEL_26;
  }
LABEL_23:
  v19 = (a_pDrwNo - 1) >> 31;
  a_pTopNo += v19;
  a_pDrwNo = (a_pDrwNo - 1) & ~v19;
  if (!CHECK_TRIG(4101, 1))
    goto LABEL_33;
LABEL_26:
  if (++v18 < a_nmax)
    goto LABEL_35;
  a_pTopNo = 0;
  a_pDrwNo = 0;
  v18 = 0;
  if (!a_pSelNo)
  {
LABEL_38:
    v20 = 0;
    goto LABEL_41;
  }
LABEL_40:
  SE(3);
  v20 = 1;
LABEL_41:
  wk->drwNo = a_pDrwNo;
  wk->topNo = a_pTopNo;
  wk->selNo = v18;
  if (v18 == v16)
    v22 = 1;
  else
    v22 = v15;
  if ((v22 & 1) == 0)
  {
    _shpReadNewArrival(v17, v14);
  }
  return v20;
}

// 0x2173ec0
static s32 shpSelectListPage(void) {
  s32 selNo;
  tagSHP_WK *wk_local;
  s32 drwMax;
  s32 v4;
  s32 v5;
  bool v6;
  tagSHP_WK *v7;
  s32 v8;
  s32 selMax;
  s32 v10;

  selNo = wk->selNo;
  if (CHECK_REP(43526, 1))
  {
    wk_local = wk;
    drwMax = wk_local->drwMax;
    v4 = wk_local->selNo - drwMax;
    v5 = wk_local->topNo - drwMax;
    wk_local->selNo = v4;
    wk_local->topNo = v5;
    if (v4 < 0 || v5 <= 0)
    {
      *(u64 *)&wk_local->selNo = 0;
      wk_local->topNo = 0;
      if (selNo)
        goto LABEL_15;
      return 0;
    }
  }
  else
  {
    v6 = CHECK_REP(43527, 1);
    v7 = wk;
    v4 = v7->selNo;
    if (v6)
    {
      selMax = v7->selMax;
      v8 = v7->drwMax;
      v4 += v8;
      v10 = v7->topNo + v8;
      v7->selNo = v4;
      v7->topNo = v10;
      if (v10 >= selMax)
      {
        v7->selNo = selMax - 1;
        v7->drwNo = v8 - 1;
        v7->topNo = selMax - v8;
        if (selNo == selMax - 1)
          return 0;
        goto LABEL_15;
      }
      if (v4 > selMax - v8)
      {
        v4 = selMax - 1;
        v7->topNo = selMax - v8;
        v7->selNo = selMax - 1;
        v7->drwNo = v8 - 1;
      }
    }
  }
  if (selNo == v4)
    return 0;
LABEL_15:
  SE(3);
  return 1;
}

// 0x2174020
static void shpListCtrlSelect(s32 a_acttype) {
  if (!shpSelectListPage())
  {
    shpSelectList(wk->selNo, wk->drwNo, wk->topNo, wk->selMax, wk->drwMax, a_acttype);
  }
}

// 0x21740a0
static void SetStatFadeIn(void) {
  u32 stat;

  if (wk)
  {
    stat = wk->stat;
    wk->count = 0;
    wk->stat = stat & 0xFFFE0F9F | 0x5000;
  }
}

// 0x2174110
static bool FadeIn(void) {
  tagSHP_WK *wk_local;
  u32 stat;
  bool v3;
  s32 v4;
  bool v6;
  tagSHP_WK *v8;
  tagSHP_WK *v9;
  s32 count;

  wk_local = wk;
  if (wk_local)
  {
    stat = wk_local->stat;
    v3 = (stat & 0x4000) == 0;
    if ((stat & 0x4000) != 0)
    {
      v6 = evtBitCheck(-1);
      if (v6)
      {
        v8 = wk;
        if (v8->pMenu->actType == 2082 && !v8->count)
        {
          fclSetApperTitle();
        }
      }
      v9 = wk;
      count = (u16)v9->count;
      v9->count = count + 1;
      if (count == 14)
      {
        v9->stat = v9->stat & 0xFFFF1F9F | 0xA060;
        v9->count = 0;
        return v3;
      }
    }
    else if ((stat & 0x8000) != 0)
    {
      v4 = ++wk_local->count;
      if (v4 >= 13)
      {
        wk_local->stat = stat & 0xFFFF7FFF;
        wk_local->count = 0;
        return (stat & 0x4000) == 0;
      }
    }
  }
  return 0;
}

// 0x2174260
static void SetStatFadeOut(void) {
  u32 stat;

  if (wk)
  {
    stat = wk->stat;
    wk->count = 0;
    wk->stat = stat & 0xFFFE0F9F | 0x1B040;
  }
}

// 0x21742e0
static bool FadeOut(void) {
  u32 stat;
  bool v3;
  bool v4;
  tagSHP_WK *v6;
  tagSHP_WK *v7;
  s16 count;
  s32 v10;

  if (wk)
  {
    stat = wk->stat;
    v3 = (stat & 0x8000) == 0;
    if ((stat & 0x8000) != 0)
    {
      v10 = (u16)wk->count++ + 1;
      if (v10 == 13)
      {
        wk->stat = stat & 0xFFFF1FFF | 0x4000;
        wk->count = 0;
        return (stat & 0x8000) == 0;
      }
    }
    else if ((stat & 0x4000) != 0)
    {
      v4 = evtBitCheck(-1);
      if (v4)
      {
        v6 = wk;
        if (v6->pMenu->actType == 2082 && !v6->count)
        {
          fclSetDisapperTitle();
        }
      }
      v7 = wk;
      count = v7->count;
      v7->count = count + 1;
      if ((s16)(count + 1) >= 20)
      {
        v7->stat &= 0xFFFEAF9F;
        v7->count = 0;
        return v3;
      }
    }
  }
  return 0;
}

// 0x2174440
static s32 shpListUpdateBuySelNum(void) {
  s64 selNo;
  s32 v3;
  s32 PriceBuy;
  s32 ItemNumEquipMinus;
  s32 yen;
  s32 ItemMaxNum;
  s32 result;

  selNo = wk->selNo;
  v3 = s_wk->index[selNo];
  PriceBuy = knyGetPriceBuy(v3);
  ItemNumEquipMinus = datGetItemNumEquipMinus(v3);
  yen = wk->yen;
  ItemMaxNum = datGetItemMaxNum(v3);
  if (ItemMaxNum - ItemNumEquipMinus >= yen / PriceBuy)
    result = yen / PriceBuy;
  else
    result = ItemMaxNum - ItemNumEquipMinus;
  wk->selNumMax = result;
  return result;
}

// 0x2174700
static s8 shpListCtrlBuySelItem(void) {
  _BOOL8 v1;
  _BOOL8 v3;

  v1 = CHECK_TRIG(4096, 1);
  if (v1 && shpListUpdateBuySelNum() > 0)
    return 2;
  v3 = CHECK_TRIG(4097, 1);
  if (v3)
    return 3;
  if (!shpSelectListPage())
  {
    shpSelectList(wk->selNo, wk->drwNo, wk->topNo, wk->selMax, wk->drwMax, 138);
  }
  return 1;
}

// 0x21747d0
static s8 shpListCtrlSelNum(s32 a_type) {
  bool v4;
  s32 selNum;
  s32 v7;
  s32 selNumMax;
  s32 v9;
  tagSHP_WK *v11;
  s32 v12;
  bool v13;
  s32 v14;
  bool v15;
  tagSHP_WK *v16;
  s64 selNo;
  s32 v19;
  s32 PriceSell;

  if (CHECK_TRIG(4097, 1))
    return 3;
  v4 = CHECK_TRIG(4096, 1);
  selNum = wk->selNum;
  if (v4 && selNum > 0)
    return 2;
  if (CHECK_TRIG(4100, 1))
  {
    v7 = wk->selNum;
    if (v7 + 1 <= wk->selNumMax)
      selNumMax = v7 + 1;
    else
      selNumMax = 1;
  }
  else
  {
    if (!CHECK_REP(4100, 1))
      goto LABEL_17;
    v9 = wk->selNum;
    if (v9 + 1 < wk->selNumMax)
      selNumMax = v9 + 1;
    else
      selNumMax = wk->selNumMax;
  }
  wk->selNum = selNumMax;
LABEL_17:
  if (!CHECK_TRIG(4101, 1))
  {
    v15 = CHECK_REP(4101, 1);
    if (!v15)
      goto LABEL_25;
    v11 = wk;
    v14 = v11->selNum - 1;
    if (v14 <= 1)
      v14 = 1;
    goto LABEL_24;
  }
  v11 = wk;
  v12 = v11->selNum - 1;
  v13 = v11->selNum == 1;
  v11->selNum = v12;
  if (v12 < 0 || v13)
  {
    v14 = v11->selNumMax;
LABEL_24:
    v11->selNum = v14;
  }
LABEL_25:
  v16 = wk;
  if (v16->selNum != selNum)
  {
    selNo = v16->selNo;
    v19 = s_wk->index[selNo];
    if (a_type)
    {
      PriceSell = knyGetPriceSell(v19);
    }
    else
    {
      PriceSell = knyGetPriceBuy(v19);
    }
    wk->trade = wk->selNum
                                                                * PriceSell;
    SE(4259844);
    return 1;
  }
  return 1;
}

// 0x2174a90
static void UpdateInit(void) {
  s64 selNo;
  s32 v5;
  s32 actType;

  wk->drwNo = 0;
  wk->topNo = 0;
  wk->selNum = 1;
  wk->trade = 0;
  wk->count = 0;
  if (!cmpGetDraw())
    return;
  selNo = (u32)wk->selNo;
  if ((selNo & 0x80000000) != 0)
    return;
  v5 = s_wk->index[selNo];
  cmpSetId(v5);
  actType = wk->pMenu->actType;
  if (!shpChkNewArrival(v5, actType))
    return;
  cmpSetNew();
}

// 0x2174ca0
static void UpdateBuyReturnList(void) {
  wk->ctrlType = 4;
  wk->trade = 0;
  wk->selNum = 1;
  wk->stepAct = 2;
}

// 0x2174d10
s8 shpUpdateBuy(void) {
  tagSHP_WK *v4;
  u32 stat;
  tagSHP_WK *v6;
  char v9;
  void *Instance;
  _BOOL8 ItfSortSysActive;
  s8 v12;
  void *v13;
  s32 v16;
  s32 v17;
  tagSHP_WK *v18;
  void *v20;
  s32 v21;
  tagSHP_WK *v22;
  s32 v23;
  s32 v24;
  s32 GoodRank;
  bool v28;
  long f64 v30;
  s64 v32;
  char *v33;
  s32 v34;
  tagSHP_WK *v35;
  s32 trade;
  dds3ProcessID_t *started;
  tagSHP_WK *v38;
  s32 ReturnNum00;
  tagSHP_WK *v41;
  s32 v43;
  s16 v44;
  s32 selNum;
  s32 v48;
  s32 v49;
  s32 v52;
  s32 v53;
  void *v56;
  _BOOL8 v58;
  s32 v60;
  tagSHP_WK *v62;
  void *v63;
  tagSHP_WK *v65;
  s32 selNo;
  s16 ListItemNo;
  s64 v68;
  char *v69;

  if (!wk)
    return (char)wk;
  switch (wk->stepAct)
  {
    case 0:
      UpdateInit();
      v4 = wk;
      if (v4)
      {
        stat = v4->stat;
        v4->count = 0;
        v4->stat = stat & 0xFFFE0F9F | 0x5000;
      }
      shpListUpdateBuySelNum();
      LOBYTE(wk) = 1;
      v6 = wk;
      v6->selNo = 0;
      v6->stepAct = 1;
      return (char)wk;
    case 1:
      if (!FadeIn())
        return 1;
      ButtonGuideDispOn();
      v9 = 2;
      goto LABEL_69;
    case 2:
      Instance = get_Instance(0);
      ItfSortSysActive = GetItfSortSysActive(Instance, 0);
      if (ItfSortSysActive)
        return 1;
      v12 = shpListCtrlBuySelItem();
      v13 = get_Instance(0);
      LOBYTE(wk) = 1;
      ItfSortMenuActive(v13, 1, 0);
      if (v12 == 2)
      {
        v62 = wk;
        v62->ctrlType = 5;
        v62->stepAct = 3;
        v63 = get_Instance(0);
        ItfSortMenuActive(v63, 0, 0);
        v65 = wk;
        selNo = v65->selNo;
        ListItemNo = shpGetListItemNo(selNo);
        v65->trade = knyGetPriceBuy(ListItemNo);
        SE(0);
        return 1;
      }
      if (v12 != 3)
        return (char)wk;
      SetStatFadeOut();
      v16 = wk->selNo;
      v17 = shpGetListItemNo(v16);
      if (shpChkNewArrival(v17, 138))
      {
        _shpReadNewArrival(0, v17);
      }
      v18 = wk;
      v18->selNo = -1;
      v18->stepAct = 8;
      KnyItemListSetAnim(shpUIManager, 2, 0);
      v20 = get_Instance(0);
      ItfSortMenuActive(v20, 0, 0);
      goto LABEL_40;
    case 3:
      v21 = (u8)shpListCtrlSelNum(0);
      if (v21 == 2)
      {
        ButtonGuideDispOff();
        Reset(0);
        SetMessagePos(0);
        if (knyGetGoodRank() <= 4)
          v60 = 5;
        else
          v60 = 6;
        fclStart2(v60, 0, 0);
        fclSetSelCancelPos(1);
        v23 = 0;
        wk->stepAct = 4;
      }
      else
      {
        if (v21 != 3)
          return 1;
        v22 = wk;
        v22->ctrlType = 4;
        v22->selNum = 1;
        v22->trade = 0;
        v22->stepAct = 2;
LABEL_40:
        v23 = 1;
      }
      SE(v23);
      return 1;
    case 4:
      v24 = Update();
      if (v24 == 1)
      {
        ButtonGuideDispOn();
LABEL_99:
        UpdateBuyReturnList();
        return 1;
      }
      if (v24)
        return 1;
      GoodRank = knyGetGoodRank();
      g_goodrank_old = GoodRank;
      shpAddGoodPointBuy(wk->trade);
      v28 = g_goodrank_old != knyGetGoodRank();
      g_bRankUp = v28;
      if (knyGetGoodRank() >= 9)
      {
        v68 = sub_1A24F60(0, v30);
        v69 = sub_8360(37, Project_DefineAchievementID_string_, v68);
        Unlock_2(v69);
      }
      v32 = sub_1A24F60(0, v30);
      v33 = sub_8360(37, Project_DefineAchievementID_string_, v32);
      v34 = knyGetGoodRank();
      ProgressUnlock_3(v33, v34, 9);
      v35 = wk;
      trade = v35->trade;
      started = itfCountProcessStartMoney(trade);
      v35->cntrPID = started;
      itfCountSetData(wk->cntrPID, wk->yen, 1);
      itfCountSetData(wk->cntrPID, wk->trade, 1);
      v38 = wk;
      v38->ctrlType = 4;
      v38->stepAct = 5;
      return 1;
    case 5:
      ReturnNum00 = itfGetReturnNum00();
      wk->yen = ReturnNum00;
      if (itfCountProcessCheck(wk->cntrPID))
        return 1;
      v41 = wk;
      v41->cntrPID = 0;
      fclStart1(7, 0);
      v9 = 6;
      goto LABEL_69;
    case 6:
      if (Update())
        return 1;
      v43 = wk->selNo;
      v44 = shpGetListItemNo(v43);
      selNum = wk->selNum;
      datAddItem(v44, selNum);
      GBWK->player->gold = wk->yen;
      if (!g_bRankUp)
        goto LABEL_99;
      g_bRankUp = 0;
      v48 = knyGetGoodRank();
      if (knyChkArrivalRank(v48, g_goodrank_old) < 1)
        v49 = 12;
      else
        v49 = 13;
      fclStart1(v49, 0);
      v9 = 7;
LABEL_69:
      wk->stepAct = v9;
      return 1;
    case 7:
      v50 = Update();
      if ((u32)v50)
        return 1;
      SetStatFadeOut();
      v52 = wk->selNo;
      v53 = shpGetListItemNo(v52);
      if (shpChkNewArrival(v53, 138))
      {
        _shpReadNewArrival(0, v53);
      }
      wk->selNo = -1;
      ButtonGuideDispOff();
      wk->stepAct = 8;
      v56 = get_Instance(0);
      ItfSortMenuActive(v56, 0, 0);
      KnyItemListSetAnim(shpUIManager, 2, 0);
      return 1;
    case 8:
      v58 = FadeOut();
      if (!v58)
        return 1;
      UpdateInit();
      wk->stepAct = 0;
      ButtonLineHelpDispSet(1);
      return 3;
    default:
      return 1;
  }
}

// 0x21757b0
static s32 shpListUpdateSellSelectNum(void) {
  s64 selNo;
  s32 result;

  selNo = wk->selNo;
  result = datGetItemNumEquipMinus(s_wk->index[selNo]);
  wk->selNumMax = result;
  return result;
}

// 0x21758b0
static s8 shpListCtrlSellSelectItem(void) {
  _BOOL8 v1;
  _BOOL8 v3;

  v1 = CHECK_TRIG(4096, 1);
  if (v1 && shpListUpdateSellSelectNum() > 0)
    return 2;
  v3 = CHECK_TRIG(4097, 1);
  if (v3)
    return 3;
  if (!shpSelectListPage())
  {
    shpSelectList(wk->selNo, wk->drwNo, wk->topNo, wk->selMax, wk->drwMax, 0);
  }
  return 1;
}

// 0x2175980
static void UpdateSellReturnList(void) {
  wk->ctrlType = 4;
  wk->trade = 0;
  wk->selNum = 1;
  wk->stepAct = 2;
}

// 0x21759f0
static s32 GetStepAct(void) {
  return wk->stepAct;
}

// 0x2175a40
s8 shpUpdateSell(void) {
  tagSHP_WK *v3;
  u32 stat;
  void *Instance;
  _BOOL8 ItfSortSysActive;
  s8 v8;
  void *v9;
  void *v12;
  s32 v13;
  s32 v14;
  tagSHP_WK *v15;
  char v16;
  s32 yen;
  s32 trade;
  s32 v19;
  tagSHP_WK *v20;
  dds3ProcessID_t *started;
  tagSHP_WK *v22;
  char v23;
  s32 ReturnNum00;
  tagSHP_WK *v26;
  dds3ProcessID_t *cntrPID;
  s64 v29;
  s32 v31;
  s32 selNum;
  tagSHP_WK *v37;
  s32 v39;
  tagSHP_WK *v42;
  void *v43;
  tagSHP_WK *v45;
  s32 selNo;
  s16 ListItemNo;
  tagSHP_WK *v48;
  s16 *index;
  tagSHP_WK *v51;
  s32 selMax;
  s32 v53;
  s32 topNo;
  s32 v56;

  if (!wk)
    return 0;
  switch (wk->stepAct)
  {
    case 0:
      UpdateInit();
      v3 = wk;
      if (v3)
      {
        stat = v3->stat;
        v3->count = 0;
        v3->stat = stat & 0xFFFE0F9F | 0x5000;
      }
      v3->selNo = 0;
      v3->stepAct = 1;
      return 1;
    case 1:
      if (!FadeIn())
        return 1;
      ButtonGuideDispOn();
      wk->stepAct = 2;
      return 1;
    case 2:
      Instance = get_Instance(0);
      ItfSortSysActive = GetItfSortSysActive(Instance, 0);
      if (ItfSortSysActive)
        return 1;
      v8 = shpListCtrlSellSelectItem();
      v9 = get_Instance(0);
      ItfSortMenuActive(v9, 1, 0);
      if (v8 == 2)
      {
        v42 = wk;
        v42->ctrlType = 5;
        v42->stepAct = 3;
        v43 = get_Instance(0);
        ItfSortMenuActive(v43, 0, 0);
        v45 = wk;
        selNo = v45->selNo;
        ListItemNo = shpGetListItemNo(selNo);
        v45->trade = knyGetPriceSell(ListItemNo);
        SE(0);
      }
      else
      {
        if (v8 != 3)
          return 1;
        SetStatFadeOut();
        wk->stepAct = 8;
        KnyItemListSetAnim(shpUIManager, 2, 0);
        SE(1);
        v12 = get_Instance(0);
        ItfSortMenuActive(v12, 0, 0);
      }
      return 1;
    case 3:
      v13 = (u8)shpListCtrlSelNum(1);
      if (v13 == 2)
      {
        ButtonGuideDispOff();
        Reset(0);
        SetMessagePos(0);
        if (knyGetGoodRank() <= 4)
          v39 = 8;
        else
          v39 = 9;
        fclStart2(v39, 0, 0);
        fclSetSelCancelPos(1);
        v16 = 4;
        v14 = 0;
        v15 = wk;
      }
      else
      {
        if (v13 != 3)
          return 1;
        v14 = 1;
        v15 = wk;
        v15->ctrlType = 4;
        v16 = 2;
        v15->selNum = 1;
        v15->trade = 0;
      }
      v15->stepAct = v16;
      SE(v14);
      return 1;
    case 4:
      yen = wk->yen;
      trade = wk->trade;
      v19 = Update();
      if (v19 == 1)
      {
        ButtonGuideDispOn();
        ButtonLineHelpDispSet(1);
        UpdateSellReturnList();
        return 1;
      }
      if (v19)
        return 1;
      v20 = wk;
      started = itfCountProcessStartMoney(trade);
      v20->cntrPID = started;
      itfCountSetData(wk->cntrPID, yen, 2);
      itfCountSetMax(wk->cntrPID, yen, 9999999);
      v22 = wk;
      v22->ctrlType = 4;
      v23 = 5;
      goto LABEL_60;
    case 5:
      ReturnNum00 = itfGetReturnNum00();
      wk->yen = ReturnNum00;
      v26 = wk;
      if (v26->yen >= 10000000)
      {
        v26->yen = 9999999;
        cntrPID = v26->cntrPID;
LABEL_41:
        if (itfCountProcessCheck(cntrPID))
          return 1;
        goto LABEL_58;
      }
      else
      {
        cntrPID = v26->cntrPID;
        goto LABEL_41;
      }
      if (itfCountProcessCheck(cntrPID))
        return 1;
LABEL_58:
      v37 = wk;
      v37->cntrPID = 0;
      fclStart1(10, 0);
      v23 = 6;
      goto LABEL_59;
    case 6:
      if (Update())
        return 1;
      v29 = wk->selNo;
      v31 = s_wk->index[v29];
      selNum = wk->selNum;
      datAddItem(v31, -selNum);
      GBWK->player->gold = wk->yen;
      ItemNumEquipMinus = datGetItemNumEquipMinus(v31);
      if ((s32)ItemNumEquipMinus > 0)
        goto LABEL_50;
      v48 = wk;
      index = v48->index;
      ItemNumEquipMinus = shpMakeIndexList(4, index, 0);
      v48->selMax = (s32)ItemNumEquipMinus;
      v51 = wk;
      selMax = v51->selMax;
      v51->drwMax = selMax;
      if (selMax >= 6)
      {
        v53 = 6;
        v51->drwMax = 6;
LABEL_94:
        topNo = v51->topNo;
        if (topNo)
        {
          if (topNo <= selMax - v53)
            goto LABEL_50;
          --v51->selNo;
          v51->topNo = topNo - 1;
          if (topNo - 1 >= 0)
            goto LABEL_50;
          v51->topNo = 0;
        }
        else
        {
          v56 = v51->selNo;
          if (v56 < 1 || v56 != selMax)
            goto LABEL_50;
          v51->selNo = selMax - 1;
        }
        --v51->drwNo;
LABEL_50:
        UpdateSellReturnList();
        return 1;
      }
      v53 = selMax;
      if (selMax > 0)
        goto LABEL_94;
      SetStatFadeOut();
      wk->selNo = -1;
      KnyItemListSetAnim(shpUIManager, 2, 0);
      v23 = 8;
LABEL_59:
      v22 = wk;
LABEL_60:
      v22->stepAct = v23;
      return 1;
    case 8:
      if (!FadeOut())
        return 1;
      ButtonLineHelpDispSet(1);
      UpdateInit();
      wk->stepAct = 0;
      return 3;
    default:
      return 1;
  }
}

// 0x2176d20
static s8 shpListCtrlTradeSelectDevil(void) {
  _BOOL8 v2;
  tagSHP_WK *v5;
  s32 v6;

  if (CHECK_TRIG(4097, 1))
    return 3;
  if (CHECK_TRIG(4098, 1))
    return 4;
  v2 = CHECK_TRIG(4096, 0);
  if (v2)
    return 2;
  if (!shpSelectListPage())
  {
    shpSelectList(wk->selNo, wk->drwNo, wk->topNo, wk->selMax, wk->drwMax, 0);
  }
  v5 = wk;
  v6 = v5->index[v5->selNo];
  v5->trade = nwdGetMagTrade(v6);
  return 1;
}

// 0x2176e70
s8 shpUpdateTrade(void) {
  s32 trade;
  s32 v5;
  tagSHP_WK *v6;
  u32 stat;
  s32 mag;
  s32 v11;
  tagSHP_WK *v12;
  char v13;
  s32 v14;
  bool v16;
  s32 v18;
  s32 StockDevilID;
  tagSHP_WK *v21;
  s16 *index;
  s32 IndexList;
  tagSHP_WK *v25;
  s32 selMax;
  s32 topNo;
  s32 v28;
  s32 ReturnNum00;
  s32 v32;
  s32 maxmag;
  tagSHP_WK *v34;
  dds3ProcessID_t *v36;
  tagSHP_WK *v40;
  s32 GoodRank;
  s32 v42;
  char v44;
  tagSHP_WK *v46;
  _BOOL8 v47;
  u32 count;
  tagSHP_WK *v49;
  s32 v50;
  s32 v52;
  s16 *v55;
  s32 selNo;
  dds3ProcessID_t *v57;
  tagSHP_WK *v59;
  dds3ProcessID_t *cntrPID;
  s32 v61;
  tagSHP_WK *v63;

  if (!wk)
    return 0;
  trade = wk->trade;
  switch (wk->stepAct)
  {
    case 0:
      UpdateInit();
      wk->selNo = 0;
      v5 = s_wk->index[0];
      nwdGetMagTrade(v5);
      v6 = wk;
      if (!v6)
        goto LABEL_12;
      goto LABEL_11;
      if (v6)
      {
LABEL_11:
        stat = v6->stat;
        v6->count = 0;
        v6->stat = stat & 0xFFFE0F9F | 0x5000;
      }
LABEL_12:
      v6->stepAct = 1;
      return 1;
    case 1:
      if (!FadeIn())
        return 1;
      goto LABEL_64;
    case 2:
      mag = wk->mag;
      v10 = shpListCtrlTradeSelectDevil();
      switch ((u8)v10)
      {
        case 2u:
          Reset(0);
          SetMessagePos(1u);
          if (trade + mag <= GBWK->player->maxmag)
          {
            if (nwdGetGoodRank() <= 4)
              v52 = 8;
            else
              v52 = 9;
          }
          else
          {
            v52 = 10;
          }
          fclStart2(v52, 0, 0);
          fclSetSelCancelPos(1);
          v13 = 3;
          v11 = 0;
          v12 = wk;
          break;
        case 4u:
          v44 = 8;
          v46 = wk;
          v46->count = 0;
          goto LABEL_111;
        case 3u:
          SetStatFadeOut();
          v11 = 1;
          v12 = wk;
          v12->selNo = -1;
          v13 = 7;
          break;
        default:
          return 1;
      }
      v12->stepAct = v13;
      SE(v11);
      return 1;
    case 3:
      v14 = Update();
      if (v14 == 1)
      {
LABEL_64:
        v44 = 2;
        goto LABEL_110;
      }
      if (v14)
        return 1;
      g_goodrank_old = nwdGetGoodRank();
      shpAddGoodPointTrade(trade);
      v16 = g_goodrank_old != nwdGetGoodRank();
      g_bRankUp = v16;
      v18 = wk->index[wk->selNo];
      StockDevilID = datGetStockDevilID(v18);
      datDelDevil(StockDevilID, 0);
      datAdjustStock(0);
      v21 = wk;
      index = v21->index;
      IndexList = shpMakeIndexList(5, index, 0);
      v21->selMax = IndexList;
      v25 = wk;
      topNo = v25->topNo;
      selMax = v25->selMax;
      if (selMax >= 8)
        v28 = 8;
      else
        v28 = v25->selMax;
      v25->drwMax = v28;
      if (topNo)
      {
        if (topNo > selMax - v28)
        {
          --v25->selNo;
          v25->topNo = topNo - 1;
          if (topNo - 1 < 0)
          {
            v25->topNo = 0;
LABEL_104:
            --v25->drwNo;
          }
        }
      }
      else
      {
        selNo = v25->selNo;
        if (selNo >= 1 && selNo == selMax)
        {
          v25->selNo = selMax - 1;
          goto LABEL_104;
        }
      }
      v57 = itfCountProcessStart(trade, 30, 2, 4259843);
      v25->cntrPID = v57;
      itfCountSetData(wk->cntrPID, wk->mag, 2);
      v59 = wk;
      cntrPID = v59->cntrPID;
      v61 = v59->mag;
      itfCountSetMax(cntrPID, v61, GBWK->player->maxmag);
      v44 = 4;
      goto LABEL_110;
    case 4:
      ReturnNum00 = itfGetReturnNum00();
      wk->mag = ReturnNum00;
      v32 = wk->mag;
      maxmag = GBWK->player->maxmag;
      if (v32 <= maxmag)
      {
        v36 = wk->cntrPID;
        goto LABEL_73;
      }
      v34 = wk;
      maxmag = GBWK->player->maxmag;
      v34->mag = maxmag;
      v36 = wk->cntrPID;
      if (itfCountProcessCheck(v36))
        return 1;
      goto LABEL_74;
LABEL_73:
      if (itfCountProcessCheck(v36))
        return 1;
LABEL_74:
      v49 = wk;
      v49->cntrPID = 0;
      if (nwdGetGoodRank() <= 4)
        v50 = 11;
      else
        v50 = 12;
      fclStart1(v50, 0);
      v44 = 5;
LABEL_110:
      v46 = wk;
LABEL_111:
      v46->stepAct = v44;
      return 1;
    case 5:
      if (Update())
        return 1;
      v40 = wk;
      GBWK->player->mag = wk->mag;
      if (g_bRankUp)
      {
        g_bRankUp = 0;
        GoodRank = nwdGetGoodRank();
        if (nwdChkArrivalRank(GoodRank, g_goodrank_old) < 1)
          v42 = 15;
        else
          v42 = 16;
        fclStart1(v42, 0);
        v44 = 6;
        goto LABEL_110;
      }
      v40->stepAct = 2;
      v55 = v40->index;
      v45 = shpMakeIndexList(5, v55, 0);
      if ((s32)v45 <= 0)
      {
LABEL_55:
        SetStatFadeOut();
        v46 = wk;
        v46->selNo = -1;
        v44 = 7;
        goto LABEL_111;
      }
      return 1;
    case 6:
      v45 = Update();
      if (!(u32)v45)
        goto LABEL_55;
      return 1;
    case 7:
      v47 = FadeOut();
      if (!v47)
        return 1;
      UpdateInit();
      wk->stepAct = 0;
      return 3;
    case 8:
      count = (u16)wk->count;
      if (count == 9)
      {
        dds3FadeIn(0, 0, 0, 1u);
      }
      else if (count == 8)
      {
        ProcessStart(0);
        Start(GBWK->player->stock_id[wk->selNo], 0);
        shpSetStatDraw(0);
      }
      else if (wk->count)
      {
        if ((s16)count >= 10)
        {
          if (count <= 0x13)
          {
            wk->count = 9;
            if (CHECK_TRIG(4097, 1))
            {
              dds3FadeOut(0, 0, 0, 5u);
              wk->count = 19;
            }
          }
          else if (count == 24)
          {
            End();
          }
          else if (count >= 0x19)
          {
            if (cmpChkEnd())
            {
              ProcessEnd(0, 0);
              shpSetStatDraw(1);
              shpResetCamera();
              dds3FadeIn(0, 0, 0, 1u);
              v63 = wk;
              v63->count = 0;
              v63->stepAct = 2;
              return 1;
            }
          }
        }
      }
      else
      {
        dds3FadeOut(0, 0, 0, 5u);
      }
      ++wk->count;
      return 1;
    default:
      return 1;
  }
}

// 0x2177b40
static s8 shpListCtrlOrderSelectItem(void) {
  s32 yen;
  s64 selNo;
  s32 v5;
  _BOOL8 v6;
  tagSHP_WK *v9;
  s64 v10;
  s32 v12;
  tagSHP_WK *v13;

  if (!CHECK_TRIG(4096, 1))
    goto LABEL_9;
  yen = wk->yen;
  selNo = wk->selNo;
  v5 = s_wk->index[selNo];
  if (yen < nwdGetPriceOrder(v5))
    goto LABEL_9;
  return 2;
LABEL_9:
  v6 = CHECK_TRIG(4097, 1);
  if (v6)
    return 3;
  if (!shpSelectListPage())
  {
    v9 = wk;
    shpSelectList(v9->selNo, v9->drwNo, v9->topNo, v9->selMax, v9->drwMax, 1058);
  }
  v10 = wk->selNo;
  v12 = s_wk->index[v10];
  v13 = wk;
  v13->trade = nwdGetPriceOrder(v12);
  return 1;
}

// 0x2177dd0
s8 shpUpdateOrder(void) {
  s32 v4;
  tagSHP_WK *v5;
  u32 stat;
  s8 result;
  tagSHP_WK *v9;
  sdatPlayerUnitWork_t *player;
  dds3ProcessID_t *cntrPID;
  tagSHP_WK *v12;
  tagSHP_WK *v13;
  s32 count;
  s32 v16;
  s32 v17;
  char v18;
  _BOOL8 v19;
  char *v23;
  s32 selNo;
  s32 ListItemNo;
  s32 v30;
  tagSHP_WK *v31;
  char v32;
  s32 yen;
  s32 trade;
  s32 v35;
  bool v37;
  long f64 v39;
  s64 v41;
  char *v42;
  s32 GoodRank;
  s32 v45;
  s16 v46;
  s32 PriceOrder;
  tagSHP_WK *v48;
  dds3ProcessID_t *started;
  char v51;
  sdatUnitWork_t *para;
  s32 v54;
  sdatPlayerUnitWork_t *v55;
  u32 v57;
  u8 *v58;
  _BOOL8 v59;
  s32 v62;
  s32 v63;
  char *v65;
  char *v69;
  char *v72;
  s64 v74;
  char *v75;

  if (!wk)
    return (char)wk;
  switch (wk->stepAct)
  {
    case 0:
      UpdateInit();
      wk->selNo = 0;
      v4 = s_wk->index[0];
      nwdGetPriceOrder(v4);
      v5 = wk;
      if (!v5)
      {
LABEL_12:
        LOBYTE(wk) = 1;
        v5->stepAct = 1;
        return (char)wk;
      }
      stat = v5->stat;
      v5->count = 0;
      v5->stat = stat & 0xFFFE0F9F | 0x5000;
      goto LABEL_12;
    case 1:
      if (!FadeIn())
        return 1;
      v23 = "";
      ButtonGuideName = "";
      goto LABEL_117;
    case 2:
      v25 = shpListCtrlOrderSelectItem();
      if ((u8)v25 == 2)
      {
        Reset(0);
        SetMessagePos(0);
        nwdGetGoodRank();
        v65 = sdatDevilName(241, 0);
        fclSetMessageVar(0, v65);
        fclStart2(5, 0, 0);
        fclSetSelCancelPos(1);
        ButtonGuideDispOff();
        v32 = 3;
        v30 = 0;
        g_bGuideOff = 1;
        v31 = wk;
      }
      else
      {
        if ((u8)v25 != 3)
          return 1;
        SetStatFadeOut();
        MilkItemListSetAnim(shpUIManager, 2, 0);
        selNo = wk->selNo;
        ListItemNo = shpGetListItemNo(selNo);
        if (shpChkNewArrival(ListItemNo, 1058))
        {
          _shpReadNewArrival(1, ListItemNo);
        }
        v30 = 1;
        v31 = wk;
        v31->selNo = -1;
        v32 = 11;
      }
      v31->stepAct = v32;
      SE(v30);
      return 1;
    case 3:
      yen = wk->yen;
      trade = wk->trade;
      v35 = Update();
      if (v35 != 1)
      {
        if (v35)
          return 1;
        g_goodrank_old = nwdGetGoodRank();
        shpAddGoodPointOrder(10 * trade);
        v37 = g_goodrank_old != nwdGetGoodRank();
        g_bRankUp = v37;
        if (nwdGetGoodRank() < 9)
        {
LABEL_57:
          v41 = sub_1A24F60(0, v39);
          v42 = sub_8360(38, Project_DefineAchievementID_string_, v41);
          GoodRank = nwdGetGoodRank();
          ProgressUnlock_3(v42, GoodRank, 9);
          v45 = wk->selNo;
          v46 = shpGetListItemNo(v45);
          PriceOrder = nwdGetPriceOrder(v46);
          v48 = wk;
          started = itfCountProcessStartMoney(PriceOrder);
          v48->cntrPID = started;
          itfCountSetData(wk->cntrPID, yen, 1);
          itfCountSetData(wk->cntrPID, PriceOrder, 1);
          v51 = 4;
          goto LABEL_127;
        }
        v74 = sub_1A24F60(0, v39);
        v75 = sub_8360(38, Project_DefineAchievementID_string_, v74);
        Unlock_2(v75);
        goto LABEL_57;
      }
      v69 = "";
      ButtonGuideName = "";
      g_bGuideOff = 0;
LABEL_117:
      ButtonGuideDispOn();
      v18 = 2;
      v13 = wk;
      goto LABEL_121;
    case 4:
      wk->yen = itfGetReturnNum00();
      v9 = wk;
      player = GBWK->player;
      cntrPID = v9->cntrPID;
      player->gold = v9->yen;
      if (itfCountProcessCheck(cntrPID))
        return 1;
      v12 = wk;
      v12->cntrPID = 0;
      v13 = wk;
      count = v13->count;
      if (count < 10)
      {
        v13->count = count + 1;
        return 1;
      }
      v13->count = 0;
      v18 = 5;
      goto LABEL_121;
    case 5:
      SE(4259841);
      para = GBWK->player->para;
      v54 = wk->index[wk->selNo];
      sdatCalcItem(para, v54);
      v55 = GBWK->player;
      datCalcNowParam(v55->para, v55->swordno, 0);
      datDvlParaUpdate(0);
      g_bGuideOff = 1;
      ButtonGuideDispOff();
      v13 = wk;
      if (!v13)
        goto LABEL_72;
      goto LABEL_71;
      if (v13)
      {
LABEL_71:
        v57 = v13->stat;
        v13->count = 0;
        v13->stat = v57 & 0xFFFE0F9F | 0x1B040;
      }
LABEL_72:
      v18 = 6;
LABEL_121:
      v13->stepAct = v18;
      result = 1;
      break;
    case 6:
      if (!FadeOut())
        return 1;
      v18 = 7;
      v13 = wk;
      goto LABEL_121;
    case 7:
      v58 = wk->pDatScr[1];
      shpLinkData(v58);
      shpOrderStartScript(-1, wk->index[wk->selNo]);
      v18 = 8;
      v13 = wk;
      goto LABEL_121;
    case 8:
      v59 = shpCheckScript();
      if (!v59)
        return 1;
      SetStatFadeIn();
      v18 = 9;
      v13 = wk;
      goto LABEL_121;
    case 9:
      if (!FadeIn())
        return 1;
      if (g_bRankUp)
      {
        g_bRankUp = 0;
        v16 = nwdGetGoodRank();
        if (nwdChkArrivalRank(v16, g_goodrank_old) < 1)
          v17 = 15;
        else
          v17 = 16;
        fclStart1(v17, 0);
        v18 = 10;
        v13 = wk;
        goto LABEL_121;
      }
      v72 = "";
      ButtonGuideName = "";
      g_bGuideOff = 0;
      ButtonGuideDispOn();
      ButtonLineHelpDispSet(1);
      v51 = 2;
LABEL_127:
      wk->stepAct = v51;
      return 1;
    case 0xA:
      v60 = Update();
      if ((u32)v60)
        return 1;
      SetStatFadeOut();
      v62 = wk->selNo;
      v63 = shpGetListItemNo(v62);
      if (shpChkNewArrival(v63, 1058))
      {
        _shpReadNewArrival(1, v63);
      }
      wk->selNo = -1;
      MilkItemListSetAnim(shpUIManager, 2, 0);
      v18 = 11;
      v13 = wk;
      goto LABEL_121;
    case 0xB:
      v19 = FadeOut();
      if (!v19)
        return 1;
      UpdateInit();
      g_bGuideOff = 0;
      ButtonLineHelpDispSet(1);
      ButtonGuideDispOn();
      wk->stepAct = 0;
      return 3;
    default:
      return 1;
  }
  return result;
}

// 0x2178ab0
static bool GuideOnOffChack(void) {
  return g_bGuideOff;
}

// 0x2178b00
static void EnterSetMsg(void) {
  s32 v2;
  s32 GoodRank;
  s32 v4;
  s32 v5;
  s32 *EventBit;

  if (wk->shopType)
  {
    goto LABEL_5;
  }
  if (!evtBitCheck(2318))
  {
    fclStart1(4, 0);
    EventBit = GBWK->EventBit;
    EventBit[72] |= 0x4000u;
    return;
  }
  GoodRank = knyGetGoodRank();
  if ((u32)GoodRank <= 8)
    v4 = 2;
  else
    v4 = 3;
  if (GoodRank <= 4)
    v5 = 1;
  else
    v5 = v4;
  fclStart1(v5, 1);
LABEL_5:
  v2 = nwdGetGoodRank();
  if (v2 <= 4)
  {
    fclStart1(1, 1);
    return;
  }
  if ((u32)v2 <= 8)
    fclStart1(2, 1);
  else
    fclStart1(3, 1);
}

// 0x2178cc0
s8 shpUpdateEnter(void) {
  tagSHP_WK *wk_local;
  s32 count;
  s32 shopType;
  char v7;
  s32 v8;
  s32 *EventBit;
  tagSHP_WK *v12;

  wk_local = wk;
  switch (wk_local->stepAct)
  {
    case 0:
      wk_local->count = 0;
      wk_local->stepAct = 1;
      return 1;
    case 1:
      count = (u16)wk_local->count;
      if (count == 27)
      {
        wk_local->count = 0;
        wk_local->stepAct = 2;
        return 1;
      }
      else
      {
        if (count == 1)
        {
          shpSetStatDraw(1);
        }
        else if (!wk_local->count)
        {
          dds3FadeIn(0, 0, 0, 0x1Eu);
        }
        ++wk->count;
        return 1;
      }
    case 2:
      shopType = wk_local->shopType;
      shpEnterStartScript(shopType);
      shpSetMotionSpeed(0, 0.5);
      v7 = 3;
      goto LABEL_21;
    case 3:
      if (!shpCheckScript())
        return 1;
      if (evtBitCheck(2304))
      {
        EventBit = GBWK->EventBit;
        EventBit[72] &= ~1u;
        wk->stepAct = 0;
        return 2;
      }
      else
      {
        v12 = wk;
        v12->count = 0;
        v12->stepAct = 4;
        return 1;
      }
    case 4:
      v8 = ++wk_local->count;
      if (v8 < 90)
        return 1;
      wk_local->count = 0;
      EnterSetMsg();
      v7 = 5;
LABEL_21:
      wk->stepAct = v7;
      return 1;
    case 5:
      if (Update())
        return 1;
      wk->stepAct = 0;
      return 2;
    default:
      return 1;
  }
}

// 0x2178fe0
s8 shpUpdateLeaveKonnouya(void) {
  tagSHP_WK *v3;
  char v6;
  tagSHP_WK *v7;
  s32 count;
  s32 v9;
  tagSHP_WK *v10;

  switch (wk->stepAct)
  {
    case 0:
      SetBackObjActive(shpUIManager, 0, 0, 0);
      KnyTitleAnim(shpUIManager, 2, 0);
      v3 = wk;
      if (!g_shpsave)
      {
        v3->stepAct = 1;
        return 1;
      }
      v3->stepAct = 4;
      return 1;
    case 1:
      fclStart1(11, 1);
      v6 = 2;
      goto LABEL_21;
    case 2:
      if (Update())
        return 1;
      v7 = wk;
      v7->count = 0;
      v7->stepAct = 3;
      return 1;
    case 3:
      count = (u16)wk->count;
      if (count == 30)
      {
        wk->stepAct = 0;
        wk->count = 0;
        return 2;
      }
      else
      {
        if (!wk->count)
        {
          dds3FadeOut(0, 0, 0, 0x1Eu);
          LOWORD(count) = wk->count;
        }
        wk->count = count + 1;
        return 1;
      }
    case 4:
      Reset(0);
      SetMessagePos(0);
      fclStart2(16, 0, 0);
      fclSetSelCancelPos(1);
      v6 = 5;
LABEL_21:
      wk->stepAct = v6;
      return 1;
    case 5:
      v9 = Update();
      if (v9 == 1)
      {
        ButtonGuideDispOn();
        ButtonLineHelpDispSet(1);
        v10 = wk;
        v10->stepAct = 0;
        v10->count = 0;
        return 3;
      }
      else if (v9)
      {
        return 1;
      }
      else
      {
        wk->stepAct = 1;
        return 1;
      }
    default:
      return 1;
  }
}

// 0x2179340
s8 shpUpdateLeaveMilkHall(void) {
  s8 result;
  s32 count;
  tagSHP_WK *v5;

  switch (wk->stepAct)
  {
    case 0:
      SetBackObjActive(shpUIManager, 0, 1, 0);
      MilkTitleAnim(shpUIManager, 2, 0);
      wk->stepAct = 1;
      result = 1;
      break;
    case 1:
      fclStart1(14, 1);
      wk->stepAct = 2;
      result = 1;
      break;
    case 2:
      if (Update())
        goto LABEL_9;
      v5 = wk;
      v5->count = 0;
      v5->stepAct = 3;
      result = 1;
      break;
    case 3:
      count = (u16)wk->count;
      if (count == 30)
      {
        wk->stepAct = 0;
        wk->count = 0;
        result = 2;
      }
      else
      {
        if (!wk->count)
        {
          dds3FadeOut(0, 0, 0, 0x1Eu);
          LOWORD(count) = wk->count;
        }
        wk->count = count + 1;
        result = 1;
      }
      break;
    default:
LABEL_9:
      result = 1;
      break;
  }
  return result;
}

// 0x2179560
s8 shpUpdateLeave(void) {
  ButtonGuideDispOff();
  ButtonLineHelpDispSet(0);
  if (wk->shopType == 1)
    return shpUpdateLeaveMilkHall();
  if (wk->shopType)
    return 2;
  return shpUpdateLeaveKonnouya();
}

// 0x2179610
static void TalkSetMotionStart(void) {
  s32 objId;
  s32 v2;

  objId = (u16)wk->pMenu->objId;
  if (objId == 8)
  {
    shpSetSmoothLoopMotion(8, 0);
  }
  else if (wk->pMenu->objId)
  {
    v2 = (s16)objId;
    shpSetSmoothSingleMotion(v2, 1);
    shpSetSwitchMotion(wk->pMenu->objId, 2);
  }
  else
  {
    shpSetSmoothSingleMotion(0, 2);
  }
}

// 0x2179760
static void TalkSetMotionEnd(void) {
  s32 objId;
  s32 v2;

  objId = (u16)wk->pMenu->objId;
  if (objId == 8)
  {
    shpSetSmoothLoopMotion(8, 2);
  }
  else if (wk->pMenu->objId)
  {
    v2 = (s16)objId;
    shpSetSmoothSingleMotion(v2, 0);
    shpSetSwitchMotion(wk->pMenu->objId, 0);
  }
  else
  {
    shpSetSmoothLoopMotion(0, 1);
  }
}

// 0x2179890
static bool TalkSetMotionSpeak(void) {
  s32 objId;
  s32 v3;

  objId = (u16)wk->pMenu->objId;
  if (objId == 8)
  {
    shpSetSmoothLoopMotion(8, 2);
    return 0;
  }
  else if (wk->pMenu->objId)
  {
    v3 = (s16)objId;
    shpSetSmoothSingleMotion(v3, 4);
    shpSetSwitchMotion(wk->pMenu->objId, 3);
    return 1;
  }
  else
  {
    shpSetSmoothLoopMotion(0, 1);
    return 0;
  }
}

// 0x21799c0
void shpTalkTitleSet(s32 num, s32 type) {
  if (type == 1)
  {
    MilkTitleAnim(shpUIManager, num, 0);
    MilkBackAnim(shpUIManager, num, 0);
  }
  else if (!type)
  {
    KnyTitleAnim(shpUIManager, num, 0);
    KnyBackAnim(shpUIManager, num, 0);
  }
}

// 0x2179ac0
s8 shpUpdateTalk(void) {
  tagSHP_WK *wk_local;
  tagSHP_WK *v5;
  _BOOL8 v6;
  tagSHP_WK *v7;
  char v10;
  s32 objId;
  char *v17;
  s32 shopType;
  char **v19;
  void *Instance;
  u8 *v21;
  tagSHP_WK *v23;
  char v24;
  u32 stat;
  char *filename;

  filename = 0;
  wk_local = wk;
  switch (wk_local->stepAct)
  {
    case 0:
      ButtonLineHelpDispSet(0);
      ButtonGuideDispOff();
      TalkModelCursorSetActive(shpUIManager, 0, 0);
      cmpMemCheckRelease();
      v5 = wk;
      v5->count = 0;
      v5->stepAct = 1;
      return 1;
    case 1:
      v6 = evtBitCheck(-1);
      if (v6)
      {
        v7 = wk;
        v7->stepAct = 3;
        v7->count = 0;
      }
      else
      {
        TalkSetMotionStart();
        wk->stepAct = 2;
      }
      return 1;
    case 2:
      if (wk_local->count == 30)
      {
        v24 = 3;
        goto LABEL_87;
      }
      if (wk_local->count)
        goto LABEL_37;
      dds3ChangeBistaMode(2);
      dds3BistaOutEx(0x1Eu, 0x30u);
      goto LABEL_33;
    case 3:
      if (GBWK->GameFileInfo->chapter == 2)
      {
        if (fldDestBitChk(2, 10))
        {
          if (!fldDestBitChk(2, 11) && !wk->shopType)
            goto LABEL_88;
        }
      }
      if (GBWK->GameFileInfo->chapter != 5)
        goto LABEL_79;
      goto LABEL_72;
      if (GBWK->GameFileInfo->chapter == 5)
      {
LABEL_72:
        if (!fldDestBitChk(5, 10))
          goto LABEL_79;
        if (fldDestBitChk(5, 11) || wk->shopType)
          goto LABEL_79;
LABEL_88:
        filename = "kny_evt.bf";
        LoadFile(&filename, 0);
        goto LABEL_83;
      }
LABEL_79:
      v21 = wk->pDatScr[0];
      shpLinkData(v21);
LABEL_83:
      shpStartScript(0);
      v10 = 4;
LABEL_84:
      v23 = wk;
      v23->count = 0;
      v23->stepAct = v10;
      return 1;
    case 4:
      if (!wk_local->count && TalkSetMotionSpeak())
        wk->count = 1;
      if (shpCheckScript())
      {
        v10 = 5;
        goto LABEL_84;
      }
      return 1;
    case 5:
      if (wk_local->count == 30)
      {
        v24 = 6;
LABEL_87:
        wk_local->stepAct = v24;
        stat = wk_local->stat;
        wk_local->count = 0;
        wk_local->stat = stat & 0xFFFDFFFF;
        return 1;
      }
      else
      {
        if (!wk_local->count)
        {
          TalkSetMotionEnd();
          dds3BistaIn(0x1Eu);
LABEL_33:
          wk_local = wk;
          objId = wk_local->pMenu->objId;
          if (objId != -1)
          {
            shpSetZoom(objId);
            wk_local = wk;
          }
        }
LABEL_37:
        ++wk_local->count;
        return 1;
      }
    case 6:
      shpTalkTitleSet(1, wk_local->shopType);
      if (s_wk)
      {
        s_wk->yen = GBWK->player->gold;
      }
      v17 = "";
      ButtonGuideName = "";
      shopType = (u8)wk->shopType;
      v19 = &"KNY01";
      if (shopType)
        v19 = &"KNY02";
      ButtonGuideDispSet(*v19, 0, 90);
      Instance = get_Instance(0);
      ItfButtonGuideSet(Instance, 1, 0);
      ButtonLineHelpDispSet(1);
      ButtonGuideDispOn();
      return 2;
    default:
      return 1;
  }
}

// 0x217a4c0
s8 shpUpdateNews(void) {
  tagSHP_WK *v2;
  u32 stat;
  tagSHP_WK *v5;
  u32 v7;
  bool v8;
  tagSHP_WK *v9;
  u32 v10;
  u8 *v11;
  char v13;
  void *Instance;
  tagSHP_WK *v15;
  u32 v16;
  tagSHP_WK *v18;

  switch (wk->stepAct)
  {
    case 0:
      ButtonGuideDispOff();
      ButtonLineHelpDispSet(0);
      v2 = wk;
      if (v2)
      {
        stat = v2->stat;
        v2->count = 0;
        v2->stat = stat & 0xFFFE0F9F | 0x5000;
      }
      MilkBack02Anim(shpUIManager, 1, 0);
      v5 = wk;
      v5->count = 0;
      v5->stepAct = 1;
      return 1;
    case 1:
      v7 = wk->stat;
      v8 = FadeIn();
      v9 = wk;
      if (v8)
        v9->stepAct = 2;
      v10 = v9->stat;
      if ((v10 & 0x2000) != 0 && (v7 & 0x2000) == 0)
      {
        nwdCallNext();
        SE(4259842);
        v9 = wk;
        v10 = v9->stat;
      }
      v9->stat = v10 & 0xFFFFFF9F;
      return 1;
    case 2:
      v11 = wk->pDatScr[2];
      shpLinkData(v11);
      shpStartScript(0);
      v13 = 3;
      goto LABEL_29;
    case 3:
      if (!shpCheckScript())
        return 1;
      nwdCallNext();
      SE(4259842);
      v15 = wk;
      if (v15)
      {
        v16 = v15->stat;
        v15->count = 0;
        v15->stat = v16 & 0xFFFE0F9F | 0x1B040;
      }
      MilkBack02Anim(shpUIManager, 2, 0);
      v18 = wk;
      v18->stat &= 0xFFFFFF9F;
      v18->stepAct = 4;
      return 1;
    case 4:
      if (!FadeOut())
        return 1;
      v13 = 5;
LABEL_29:
      wk->stepAct = v13;
      return 1;
    case 5:
      ButtonGuideDispSet("KNY01", 0, 90);
      Instance = get_Instance(0);
      ItfButtonGuideSet(Instance, 1, 0);
      ButtonLineHelpDispSet(1);
      ButtonGuideDispOn();
      return 2;
    default:
      return 1;
  }
}

// 0x217a900
s8 shpUpdateGoma(void) {
  s8 result;
  tagSHP_WK *v4;
  s32 v5;
  s32 count;
  bool v7;
  tagSHP_WK *v8;
  s32 *EventBit;

  result = 1;
  switch (wk->stepAct)
  {
    case 0:
      SetBackObjActive(shpUIManager, 0, wk->shopType, 0);
      KnyTitleAnim(shpUIManager, 2, 0);
      ButtonGuideDispOff();
      ButtonLineHelpDispSet(0);
      v4 = wk;
      v4->count = 0;
      v4->stepAct = 1;
      return 1;
    case 1:
      if (!evtBitCheck(2620))
      {
        v5 = 17;
        goto LABEL_25;
      }
      if (evtBitCheck(2463))
      {
        v5 = 14;
LABEL_25:
        fclStart1(v5, 1);
        goto LABEL_39;
      }
      fclStart1(18, 1);
      EventBit = GBWK->EventBit;
      EventBit[76] |= 0x80000000;
LABEL_39:
      wk->stepAct = 2;
      return 1;
    case 2:
      if (Update())
        return 1;
      wk->count = 0;
      v7 = evtBitCheck(2620);
      v8 = wk;
      if (v7)
        v8->stepAct = 3;
      else
        v8->stepAct = 6;
      return 1;
    case 3:
      count = (u16)wk->count;
      if (count == 50)
      {
        SE_NotKillFlag = 1;
        SE(4259846);
        goto LABEL_33;
      }
      if (!wk->count)
      {
        dds3FadeOut(0, 0, 0, 0x1Eu);
        sndBgmFadeOut2();
        goto LABEL_33;
      }
      if ((s16)count < 60)
      {
LABEL_33:
        ++wk->count;
        return 1;
      }
      wk->count = 0;
      return 5;
    case 6:
      ButtonLineHelpDispSet(1);
      ButtonGuideDispOn();
      return 2;
    default:
      return result;
  }
}

// 0x217acd0
s8 shpUpdateDBOOK(void) {
  char v4;
  void *Instance;
  dds3Basic_t *basic;

  basic = 0;
  switch (wk->stepAct)
  {
    case 0:
      ButtonGuideDispOff();
      ButtonLineHelpDispSet(0);
      dds3FadeOut(0, 0, 0, 0x1Eu);
      wk->stepAct = 1;
      return 1;
    case 1:
      if (dds3FadeCheck())
        return 1;
      v4 = 2;
      goto LABEL_44;
    case 2:
      basic = dds3GetActiveScene();
      dds3SceneBasicVisible(basic, 0);
      SetBackObjActive(shpUIManager, 0, wk->shopType, 0);
      TitleAnimSet(shpUIManager, 1, wk->shopType, 0);
      ActiveKanbanOnOff(shpUIManager, 0, wk->shopType, 0);
      ProcessStart(0);
      v4 = 3;
      goto LABEL_44;
    case 3:
      if (!!ProcessCheck())
        return 1;
      basic = dds3GetActiveScene();
      dds3SceneBasicVisible(basic, 1);
      shpResetCamera();
      v4 = 4;
LABEL_44:
      wk->stepAct = v4;
      return 1;
    case 4:
      dds3FadeIn(0, 0, 0, 0x1Eu);
      Instance = get_Instance(0);
      ItfButtonGuideSet(Instance, 1, 0);
      ButtonGuideDispSet("KNY01", 0, 90);
      ButtonLineHelpDispSet(1);
      ActiveKanbanOnOff(shpUIManager, 1, wk->shopType, 0);
      SetBackObjActive(shpUIManager, 1, wk->shopType, 0);
      TitleAnimSet(shpUIManager, 0, wk->shopType, 0);
      return 2;
    default:
      return 1;
  }
}

// 0x217b190
void chkpDatscr(void) {

}

// 0x217b1d0
void shpSortMenu(s16 **_nowList, s32 _num, SHP_SORT _sort) {
  void *v6;
  u64 v7;
  s64 v8;
  u64 *v9;
  s32 v10;
  s64 size;
  s32 *items;
  void *Instance;
  void *v14;
  void *v15;
  void *IndexList;
  void *v17;
  s64 v18;
  s64 i;
  s16 *v20;
  s16 Item;
  char *v22;

  v6 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v6);
  if (num >= 1)
  {
    v7 = 0;
    v8 = 2 * (u32)num;
    v9 = Method_System_Collections_Generic_List_int__Add__;
    do
    {
      while (1)
      {
        v10 = (*nowList)[v7 / 2];
        size = v6->_size;
        ++v6->_version;
        items = v6->_items;
        if ((u32)size < LODWORD(items->max_length))
          break;
        _AddWithResize(v6, v10, *(const MethodInfo_2D8F530 **)(*(u64 *)(v9[4] + 192) + 112));
        v9 = Method_System_Collections_Generic_List_int__Add__;
        v7 += 2;
        if (v8 == v7)
          goto LABEL_8;
      }
      v6->_size = size + 1;
      items[size] = v10;
      v7 += 2;
    }
    while (v8 != v7);
  }
LABEL_8:
  Instance = get_Instance(0);
  ListSet_object_(Instance, v6);
  v14 = get_Instance(0);
  ListSort(v14, 0);
  v15 = get_Instance(0);
  IndexList = GetIndexList(v15, 0);
  if (num >= 1)
  {
    v17 = IndexList;
    v18 = num;
    sub_188E3B0((*nowList), 255, 2 * (u32)num);
    for (i = 0; i != v18; ++i)
    {
      v20 = *nowList;
      Item = _get_Item(v17, i);
      v22 = (char *)v20 + 2 * i;
      *((u16 *)v22 + 16) = Item;
    }
  }
}

// 0x217b3d0
void shpSortSetting(SHP_SORT _sort) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  intptr_t *v7;
  void *Instance;

  if (sort == 2)
  {
    Instance = get_Instance(0);
    SortSetting(Instance, 10, 0);
    v4 = get_Instance(0);
    v5 = Allocate(System_Action);
    v6 = v5;
    v7 = &Method_Project_shpAction_SortFunc_Sell__;
  }
  else
  {
    if (sort != 1)
      return;
    v3 = get_Instance(0);
    SortSetting(v3, 9, 0);
    v4 = get_Instance(0);
    v5 = Allocate(System_Action);
    v6 = v5;
    v7 = &Method_Project_shpAction_SortFunc_Buy__;
  }
  _ctor(v5, 0, *v7, 0);
  SetSortCallBack(v4, v6, 0);
}

// 0x217b520
void shpSortFunc_Buy(void) {
  s16 *index;

  index = wk->index;
  shpMakeIndexList(1, index, 0);
}

// 0x217b5b0
void shpSortFunc_Sell(void) {
  s16 *index;

  index = wk->index;
  shpMakeIndexList(4, index, 0);
}
