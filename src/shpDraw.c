#include "types.h"
#include "buttonguide.h"
#include "dat.h"
#include "fcldrawback.h"
#include "fclmenu.h"
#include "fclmisc.h"
#include "itf.h"
#include "localize.h"
#include "sbtlitem.h"
#include "sbtlweapon.h"
#include "sdat.h"
#include "shpaction.h"
#include "shpdraw.h"
#include "shpdrawmisc.h"
#include "shpmain.h"
#include "shpmisc.h"

typedef struct itfSprList_t itfSprList_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagSHP_DRAW_WK tagSHP_DRAW_WK;

struct tagSHP_DRAW_WK {
    sprHandle_t *phSpr;
    s16 countRootCur;
    s16 countRootCur2;
    s16 countRootLine;
    s16 countListCur;
    s16 countNumCur;
    s16 countScrollBar;
    s16 countListFade;
    bool bRootLineEnd;
};

tagSHP_DRAW_WK *wk;
static itfSprList_t *shpSprParamListMoney;
static itfSprList_t *shpSprParamListSelNum;
static itfSprList_t *shpSprParamListSelItem;
static itfSprList_t *shpSprParamListSelItemTarget;
static itfSprList_t *shpSprParamListMain;
static itfSprList_t *arrSprListDrinkTitle;
static itfSprList_t *arrSprListSelect2;
static itfSprList_t *arrSprListTradeTitle;
static itfSprList_t *arrSprListMag;
static sdfIVector2_t *shpSLineParamKN01;
static sdfIVector2_t *shpSLineParamKN02;
static sdfIVector2_t *shpSLineParamKN03;
static sdfIVector2_t *shpSLineParamKN04;
static sdfIVector2_t **shpSLineParamKN;
static char *MenuText;
static char *shpMoney;
static f32 PartsSelNum_alpha;
static char *ButtonGuideName;

static void SpriteDef(s32 a_x, s32 a_y, s32 a_sprNo);
static void SpriteAlpha(s32 a_x, s32 a_y, s32 a_alpha, sprHandle_t *a_hSpr, s32 a_sprNo, u32 a_otNo);
static void SpriteAlphaDef(s32 a_x, s32 a_y, s32 a_alpha, s32 a_sprNo);
static void SpriteColor(s32 a_x, s32 a_y, u32 a_color, s32 a_sprNo);
static void SmallFont(s32 a_x, s32 a_y, u32 a_col, s8 a_str);
static void ItemName(s32 a_id, s32 a_x, s32 a_y, u32 a_col);
static void DevilName(s32 a_id, s32 a_x, s32 a_y, u32 a_col);
static void Price(s32 a_price, s32 a_x, s32 a_y, u32 a_col, s32 a_size, s32 a_maxfigure);
static void Magunetite(s32 a_price, s32 a_x, s32 a_y, u32 a_col, s32 a_size);
static void PartsListBase(s32 a_acttype, f32 a_alphaRate);
static void PartsSelNum(s32 a_selNum, s32 a_selMax, s32 i);
static void PartsMag(s32 a_mag, f32 a_alphaRate);
static void PartsMoney(s32 a_money, s32 a_trade, f32 a_alphaRate);
static void PartsMoney2(s32 a_money, f32 a_alphaRate);
static void PartsListCursor(bool a_bTarget, f32 a_alphaRate);
static void Select2(f32 a_alpha);
static void PartsListDat(s32 a_itemNo, bool a_bSelect, bool a_bTarget, s32 a_acttype, f32 a_alphaRate, s32 i);
static void ScrollBar(s32 a_w, s32 a_h, s32 a_topNo, s32 a_drwMax, s32 a_selMax, f32 a_alphaRate, s32 type);
static void ScrollBarCursor(s32 a_topno, s32 a_drwmax, s32 a_selmax, f32 a_alphaRate, s32 type);
static void PartsList(s32 a_actType, s32 a_topNo, s32 a_drwNo, s32 a_lstMax, s32 a_drwMax, s32 a_selNum, s32 a_selMax, f32 a_alphaRate);

// 0x217f310
void shpBackParam(s32 a_alphaType, s32 a_u0, s32 a_v0, s32 a_u1, s32 a_v1, u32 a_col) {
  ;
}

// 0x217f320
static void SpriteDef(s32 a_x, s32 a_y, s32 a_sprNo) {
  ;
}

// 0x217f330
static void SpriteAlpha(s32 a_x, s32 a_y, s32 a_alpha, sprHandle_t *a_hSpr, s32 a_sprNo, u32 a_otNo) {
  ;
}

// 0x217f340
static void SpriteAlphaDef(s32 a_x, s32 a_y, s32 a_alpha, s32 a_sprNo) {

}

// 0x217f3a0
static void SpriteColor(s32 a_x, s32 a_y, u32 a_color, s32 a_sprNo) {
  return;
}

// 0x217f450
static void SmallFont(s32 a_x, s32 a_y, u32 a_col, s8 a_str) {
  ;
}

// 0x217f460
static void ItemName(s32 a_id, s32 a_x, s32 a_y, u32 a_col) {
  ;
}

// 0x217f470
static void DevilName(s32 a_id, s32 a_x, s32 a_y, u32 a_col) {
  ;
}

// 0x217f480
static void Price(s32 a_price, s32 a_x, s32 a_y, u32 a_col, s32 a_size, s32 a_maxfigure) {
  ;
}

// 0x217f490
static void Magunetite(s32 a_price, s32 a_x, s32 a_y, u32 a_col, s32 a_size) {
  ;
}

// 0x217f4a0
static void PartsListBase(s32 a_acttype, f32 a_alphaRate) {
  char *v7;
  char *LocalizeText;
  char *v9;
  char *v12;
  char *v13;

  if ((a_acttype & 0x28) == 8)
  {
    if (a_acttype == 266)
    {
      v12 = MenuText[2];
      LocalizeText = GetLocalizeText(v12, 1);
      v9 = MenuText[3];
      goto LABEL_21;
    }
    if (a_acttype == 138)
    {
      v7 = MenuText[0];
      LocalizeText = GetLocalizeText(v7, 1);
      v9 = MenuText[1];
LABEL_21:
      v13 = GetLocalizeText(v9, 1);
      SetKnyHeadText(shpUIManager, LocalizeText, v13, 0);
    }
  }
}

// 0x217f660
static void PartsSelNum(s32 a_selNum, s32 a_selMax, s32 i) {
  s32 countNumCur;
  f32 v10;
  f32 v11;
  tagSHP_DRAW_WK *wk_local;
  s32 v14;

  countNumCur = (u16)wk->countNumCur;
  if (!wk->countNumCur)
    PartsSelNum_alpha = 0.0;
  v10 = -6.551724;
  if ((u32)(countNumCur - 70) < 0xFFFFFFE3)
    v10 = 0.0;
  if ((u32)(countNumCur - 41) >= 0xFFFFFFD8)
    v11 = 4.75;
  else
    v11 = v10;
  PartsSelNum_alpha = v11 + PartsSelNum_alpha;
  wk_local = wk;
  v14 = ++wk_local->countNumCur;
  if (v14 < 70)
  {
    goto LABEL_19;
  }
  wk_local->countNumCur = 0;
LABEL_19:
  ItemListSelNum(shpUIManager, i, a_selNum, a_selMax, (f32)(PartsSelNum_alpha / -255.0) + 1.0, 0);
}

// 0x217f850
static void PartsMag(s32 a_mag, f32 a_alphaRate) {
  void *p_shpUIManager;
  void *shpUIManager_local;

  p_shpUIManager = &shpUIManager;
  shpUIManager_local = p_shpUIManager;
  SetMAG(shpUIManager_local, GBWK->player->maxmag, a_mag, 0);
}

// 0x217f930
static void PartsMoney(s32 a_money, s32 a_trade, f32 a_alphaRate) {
  char *v9;
  char *LocalizeText;
  char *v11;
  void *v12;
  char *v13;
  char *v14;

  v9 = shpMoney[0];
  LocalizeText = GetLocalizeText(v9, 1);
  v11 = GetLocalizeText(shpMoney[2], 1);
  SetMoney(shpUIManager, 0, a_money, LocalizeText, v11, 0);
  v12 = shpUIManager;
  v13 = GetLocalizeText(shpMoney[1], 1);
  v14 = GetLocalizeText(shpMoney[2], 1);
  SetMoney(v12, 1, a_trade, v13, v14, 0);
}

// 0x217fad0
static void PartsMoney2(s32 a_money, f32 a_alphaRate) {
  char *v7;
  char *LocalizeText;
  char *v9;

  v7 = shpMoney[0];
  LocalizeText = GetLocalizeText(v7, 1);
  v9 = GetLocalizeText(shpMoney[2], 1);
  SetMoney2(shpUIManager, a_money, LocalizeText, v9, 0);
}

// 0x217fc10
static void PartsListCursor(bool a_bTarget, f32 a_alphaRate) {
  ;
}

// 0x217fc20
static void Select2(f32 a_alpha) {
  ;
}

// 0x217fc30
static void PartsListDat(s32 a_itemNo, bool a_bSelect, bool a_bTarget, s32 a_acttype, f32 a_alphaRate, s32 i) {
  s32 ItemNumEquipMinus;
  s32 ItemMaxNum;
  char v15;
  s32 PriceOrder;
  char v17;
  s32 PriceSell;
  void *p_shpUIManager;
  void *shpUIManager_local;
  _BOOL4 v26;
  s32 v27;
  void *v28;
  void *v30;
  SBTLITEM_TBL *v32;
  void *v34;
  void *ItmIconSpr;
  void *v38;
  char *v39;
  char *v41;
  char *v42;
  void *v44;
  char *v45;
  char *v47;
  char *v48;
  s32 MagTrade;
  s32 v50;
  s32 PriceBuy;
  char v52;
  s32 v53;
  s32 iconType;
  void *Instance;
  void *v56;
  char *v57;
  char *v59;
  char *LocalizeText;
  void *v62;
  char *v63;
  char *v65;
  char *v66;
  s32 posse;
  s32 v69;

  ItemNumEquipMinus = datGetItemNumEquipMinus(a_itemNo);
  ItemMaxNum = datGetItemMaxNum(a_itemNo);
  posse = ItemNumEquipMinus;
  if (a_bSelect)
    v15 = 2;
  else
    v15 = 0;
  if (a_acttype <= 266)
  {
    if (a_acttype != 138)
    {
      if (a_acttype != 266)
        goto LABEL_35;
      PriceSell = knyGetPriceSell(a_itemNo);
      v15 |= !datCheckItem(a_itemNo, 0);
      v69 = PriceSell;
      if ((v15 & 4) != 0)
        goto LABEL_29;
      goto LABEL_36;
    }
    v50 = ItemMaxNum;
    PriceBuy = knyGetPriceBuy(a_itemNo);
    if (shpChkNewArrival(a_itemNo, 138))
      v52 = v15 | 4;
    else
      v52 = v15;
    v53 = PriceBuy;
    if (datCheckMoney(PriceBuy))
    {
      v15 = v52 | datCheckItem(a_itemNo, v50);
LABEL_125:
      v69 = v53;
      if ((v15 & 4) == 0)
        goto LABEL_36;
      goto LABEL_29;
    }
    v15 = v52 | 1;
    goto LABEL_125;
  }
  if (a_acttype != 530)
  {
    if (a_acttype == 1058)
    {
      PriceOrder = nwdGetPriceOrder(a_itemNo);
      if (shpChkNewArrival(a_itemNo, 1058))
        v17 = v15 | 4;
      else
        v17 = v15;
      v15 = v17 | !datCheckMoney(PriceOrder);
      v69 = PriceOrder;
      if ((v15 & 4) == 0)
        goto LABEL_36;
LABEL_29:
      p_shpUIManager = &shpUIManager;
      shpUIManager_local = p_shpUIManager;
      v26 = 1;
      NewPopActive(shpUIManager_local, 1, i, s_wk->shopType, 0);
      if ((v15 & 2) != 0)
      {
        if ((v15 & 1) != 0)
          v27 = 2;
        else
          v27 = 1;
      }
      else
      {
        v26 = 0;
        v27 = v15 & 1 ^ 3;
      }
      goto LABEL_50;
    }
LABEL_35:
    v69 = -1;
    goto LABEL_36;
  }
  MagTrade = nwdGetMagTrade(a_itemNo);
  v69 = MagTrade;
LABEL_36:
  v28 = &shpUIManager;
  v30 = v28;
  NewPopActive(v30, 0, i, s_wk->shopType, 0);
  if ((v15 & 2) != 0)
  {
    v26 = 1;
    if ((v15 & 1) != 0)
      v27 = 2;
    else
      v27 = 1;
    if (a_acttype == 530)
      return;
  }
  else
  {
    v26 = 0;
    v27 = 2 * (v15 & 1);
    if (a_acttype == 530)
      return;
  }
LABEL_50:
  if ((a_acttype & 0x20) == 0)
  {
    v32 = tbldata[a_itemNo];
    if (v32->type != 1024)
    {
      iconType = v32->iconType;
      Instance = get_Instance(0);
      ItmIconSpr = GetItmIconSpr(Instance, iconType, 0);
LABEL_103:
      ItemListMenuSetActive(shpUIManager, i, 1, 0);
      ItemListPanelCursorSetActive(shpUIManager, i, v26, 0);
      ItemListTextMode(shpUIManager, i, v27, 0);
      v56 = shpUIManager;
      v57 = sdatItemName(a_itemNo);
      v59 = shpMoney[2];
      LocalizeText = GetLocalizeText(v59, 1);
      SetItemListMenuBarStat(v56, i, v57, v69, posse, LocalizeText, ItmIconSpr, 0);
      if (v26)
      {
        v62 = shpUIManager;
        v63 = sdatItemHelp(a_itemNo, 1);
        v65 = MenuText[8];
        v66 = GetLocalizeText(v65, 1);
        SetItemHelpMes(v62, v63, v66, 0);
      }
      ItemListBulletIconSetActive(shpUIManager, i, 0, 0);
      return;
    }
    v34 = shpUIManager;
    ItmIconSpr = SwordIconChange(v34, tbl[a_itemNo - 144]->m_type, 0);
    goto LABEL_103;
  }
  SODAListMenuSetActive(shpUIManager, i, 1, 0);
  SODAListPanelCursorSetActive(shpUIManager, i, v26, 0);
  SODAListTextMode(shpUIManager, i, v27, 0);
  v38 = shpUIManager;
  v39 = sdatItemName(a_itemNo);
  v41 = shpMoney[2];
  v42 = GetLocalizeText(v41, 1);
  SetSODAListMenuBarStat(v38, i, v39, v69, v42, 0);
  if (v26)
  {
    v44 = shpUIManager;
    v45 = sdatItemHelp(a_itemNo, 1);
    v47 = MenuText[8];
    v48 = GetLocalizeText(v47, 1);
    SetSODAHelpMes(v44, v45, v48, 0);
  }
}

// 0x2180720
static void ScrollBar(s32 a_w, s32 a_h, s32 a_topNo, s32 a_drwMax, s32 a_selMax, f32 a_alphaRate, s32 type) {
  f32 v12;
  f32 v13;
  f32 v14;

  if (type)
    v12 = 332.0;
  else
    v12 = 445.0;
  if (a_drwMax)
  {
    v13 = (f32)a_drwMax / (f32)a_selMax;
    if (a_selMax)
      goto LABEL_8;
LABEL_12:
    v14 = 0.0;
    goto LABEL_10;
  }
  v13 = 1.0;
  if (!a_selMax)
    goto LABEL_12;
LABEL_8:
  v14 = (f32)((f32)a_topNo / (f32)a_selMax) * v12;
LABEL_10:
  SetItemListScrollBar(shpUIManager, v12 * v13, -v14, type, 0);
}

// 0x2180820
static void ScrollBarCursor(s32 a_topno, s32 a_drwmax, s32 a_selmax, f32 a_alphaRate, s32 type) {
  bool v10;
  s32 v11;
  bool v15;

  v10 = __OFSUB__(a_selmax, a_drwmax);
  v11 = a_selmax - a_drwmax;
  if ((v11 < 0) ^ v10 | (v11 == 0))
  {
    SetItemListScrollBarArrowActive_U(shpUIManager, 0, type, 0);
    goto LABEL_15;
  }
  SetItemListScrollBarArrowActive_U(shpUIManager, a_topno > 0, type, 0);
  if (v11 <= a_topno)
  {
LABEL_15:
    v15 = 0;
    goto LABEL_16;
  }
  v15 = 1;
LABEL_16:
  SetItemListScrollBarArrowActive_D(shpUIManager, v15, type, 0);
}

// 0x2180940
static void PartsList(s32 a_actType, s32 a_topNo, s32 a_drwNo, s32 a_lstMax, s32 a_drwMax, s32 a_selNum, s32 a_selMax, f32 a_alphaRate) {
  f32 v15;
  f32 v16;
  f32 v19;
  s32 v20;
  f32 v24;
  f32 v25;
  void *p_shpUIManager;
  f32 v28;
  f32 v29;
  s32 v30;
  f32 v31;
  f32 v32;
  f32 v35;
  s64 v36;
  s64 v37;
  s32 v38;
  s32 v41;
  s32 v44;

  PartsListBase(a_actType, a_alphaRate);
  if (a_actType == 530)
    goto LABEL_4;
  if ((a_actType & 0x20) == 0)
  {
    if (a_drwMax)
    {
      v24 = (f32)((f32)a_drwMax / (f32)a_lstMax) * 332.0;
      if (a_lstMax)
        goto LABEL_18;
      goto LABEL_72;
    }
    v24 = 332.0;
    if (a_lstMax)
    {
LABEL_18:
      v25 = (f32)((f32)a_topNo / (f32)a_lstMax) * 332.0;
LABEL_20:
      p_shpUIManager = &shpUIManager;
      v28 = -v25;
      v29 = v24;
      v20 = 2;
      v30 = 2;
LABEL_28:
      SetItemListScrollBar(p_shpUIManager, v29, v28, v30, 0);
      goto LABEL_29;
    }
LABEL_72:
    v25 = 0.0;
    goto LABEL_20;
  }
  if (a_drwMax)
  {
    v31 = (f32)((f32)a_drwMax / (f32)a_lstMax) * 332.0;
    if (a_lstMax)
      goto LABEL_25;
    goto LABEL_77;
  }
  v31 = 332.0;
  if (a_lstMax)
  {
LABEL_25:
    v32 = (f32)((f32)a_topNo / (f32)a_lstMax) * 332.0;
LABEL_27:
    p_shpUIManager = &shpUIManager;
    v28 = -v32;
    v20 = 1;
    v29 = v31;
    v30 = 1;
    goto LABEL_28;
  }
LABEL_77:
  v32 = 0.0;
  goto LABEL_27;
LABEL_4:
  if (a_drwMax)
  {
    v15 = (f32)((f32)a_drwMax / (f32)a_lstMax) * 445.0;
    if (a_lstMax)
      goto LABEL_8;
LABEL_67:
    v16 = 0.0;
    goto LABEL_10;
  }
  v15 = 445.0;
  if (!a_lstMax)
    goto LABEL_67;
LABEL_8:
  v16 = (f32)((f32)a_topNo / (f32)a_lstMax) * 445.0;
LABEL_10:
  SetItemListScrollBar(shpUIManager, v15, -v16, 0, 0);
  v20 = 0;
LABEL_29:
  ScrollBarCursor(a_topNo, a_drwMax, a_lstMax, v19, v20);
  if (a_drwMax < 1)
  {
    a_drwMax = 0;
    v44 = 0;
    if (a_actType != 1058)
      goto LABEL_57;
    goto LABEL_54;
  }
  v36 = 0;
  v37 = a_drwNo;
  v38 = a_topNo;
  do
  {
    while (1)
    {
      v41 = s_wk->index[v38 + (s32)v36];
      PartsListDat(v41, v37 == v36, 0, a_actType, v35, v36);
      if (a_selNum < 0 || v37 != v36)
        break;
      PartsSelNum(a_selNum, a_selMax, v36++);
      if (a_drwMax == v36)
        goto LABEL_48;
    }
    ItemListQuantitySetActive(shpUIManager, v36++, 0, 0);
  }
  while (a_drwMax != v36);
LABEL_48:
  if ((u32)a_drwMax <= 5)
  {
    v44 = a_drwMax;
    if (a_actType != 1058)
    {
      do
      {
LABEL_57:
        ItemListMenuSetActive(shpUIManager, v44++, 0, 0);
      }
      while (v44 != 6);
      goto LABEL_59;
    }
    do
    {
LABEL_54:
      SODAListMenuSetActive(shpUIManager, v44++, 0, 0);
    }
    while (v44 != 6);
LABEL_59:
    if (a_actType == 530)
    {
      do
      {
        MAGListMenuSetActive(shpUIManager, a_drwMax++, 0, 0);
      }
      while (a_drwMax != 6);
    }
  }
}

// 0x2180ee0
void shpItemListTest(s32 a_acttype, s32 a_topno, s32 a_drwno, s32 a_lstmax, s32 a_drwmax, s32 a_selnum, s32 a_selmax, s32 a_yen, s32 a_mag, s32 a_trade, f32 a_alphaRate) {
  void *p_shpUIManager;
  s32 v24;
  void *v25;
  f32 v27;
  f32 v32;
  char *v34;
  char *LocalizeText;
  char *v36;
  f32 v38;

  if (a_acttype != 530)
  {
    if ((a_acttype & 0x20) != 0)
    {
      v34 = MenuText[10];
      LocalizeText = GetLocalizeText(v34, 1);
      v36 = GetLocalizeText(MenuText[6], 1);
      SODAListSetHead(shpUIManager, LocalizeText, v36, 0);
      SODAListActive(shpUIManager, 1, 0);
      MilkHallListAlpha(shpUIManager, a_alphaRate, 0);
      PartsMoney2(a_yen, v38);
      v24 = a_topno;
    }
    else
    {
      ItemListActive(shpUIManager, 1, 0);
      ItemListAlpha(shpUIManager, a_alphaRate, 0);
      PartsMoney(a_yen, a_trade, v32);
      v24 = a_topno;
    }
    goto LABEL_27;
  }
  MAGListActive(shpUIManager, 1, 0);
  MilkHallListAlpha(shpUIManager, a_alphaRate, 0);
  p_shpUIManager = &shpUIManager;
  v24 = a_topno;
  v25 = p_shpUIManager;
  SetMAG(v25, GBWK->player->maxmag, a_mag, 0);
LABEL_27:
  PartsList(a_acttype, v24, a_drwno, a_lstmax, a_drwmax, a_selnum, a_selmax, v27);
}

// 0x2181260
void knyDrawKeyHelp(s32 a_type, f32 a_alphaRate) {
  char *v5;
  void *Instance;
  char *v8;
  s32 stepAct;
  char **v13;

  v5 = "";
  if (fclChkMessageDraw() == 1)
    return;
  Instance = get_Instance(0);
  if (GetItfSortSysActive(Instance, 0))
  {
    v8 = "";
    ButtonGuideName = "";
    return;
  }
  stepAct = (u8)wk->stepAct;
  if ((u32)(stepAct - 6) < 2 || stepAct == 4)
  {
    if (!op_Inequality(v5, "", 0))
      return;
  }
  else
  {
    if (stepAct == 3)
    {
      v13 = &"KNY03";
    }
    else if (a_type == 2)
    {
      v13 = &"KNY04";
    }
    else if (a_type == 1)
    {
      v13 = &"KNY02";
    }
    else
    {
      v13 = &"KNY01";
    }
    v5 = *v13;
    if (!op_Inequality(*v13, "", 0))
      return;
  }
  if (!op_Inequality(v5, ButtonGuideName, 0))
    return;
  ButtonGuideName = v5;
  ButtonGuideDispSet(ButtonGuideName, 0, 90);
  ButtonLineHelpDispSet(1);
}

// 0x2181560
void nwdDrawKeyHelp(s32 a_type, f32 a_alphaRate) {
  char **v6;
  s32 stepAct;
  char **v8;
  char *v9;
  bool v12;
  char *v18;

  goto LABEL_3;
LABEL_9:
  if (g_bGuideOff)
    return;
  v6 = &"KNY02";
  stepAct = (u8)wk->stepAct;
  if (a_type != 1)
    v6 = &"KNY01";
  if (stepAct == 3)
    v8 = &"KNY03";
  else
    v8 = v6;
  v9 = *v8;
  if (!op_Inequality(v9, ButtonGuideName, 0))
  {
    goto LABEL_23;
LABEL_24:
    if (a_type != 2)
      return;
    return;
  }
  v12 = op_Equality(v9, "KNY03", 0);
  if (v12)
  {
    ButtonGuideName = v9;
    ButtonGuideDispOff();
  }
  else
  {
    ButtonGuideName = v9;
    Log(ButtonGuideName);
    v18 = ButtonGuideName;
    ButtonGuideDispSet(v18, 0, 90);
    ButtonLineHelpDispSet(1);
  }
LABEL_23:
  goto LABEL_24;
LABEL_3:
  if (fclChkMessageDraw() != 1)
    goto LABEL_9;
  ButtonGuideDispOff();
}

// 0x2181950
void shpRootCursor(s32 a_x, s32 a_y) {
  if (!wk->phSpr)
    return;
}

// 0x21819f0
void shpRootCursorInit(void) {
  if (!wk)
    return;
  wk->countRootCur = 0;
}

// 0x2181aa0
void shpResetRootLine(void) {
  tagSHP_DRAW_WK *wk_local;

  wk_local = wk;
  if (!wk_local)
    return;
  wk_local = wk;
  wk_local->bRootLineEnd = 0;
  *(u32 *)&wk_local->countRootCur2 = 0;
}

// 0x2181b60
bool shpCheckRootLineMax(void) {
  if (!wk)
    return 0;
  return wk->bRootLineEnd;
}

// 0x2181c10
void shpCursorLine(s32 a_shopType, s32 a_menuNo) {
  sdfIVector2_t *v5;
  u32 v6;
  sdfIVector2_t *v8;
  s32 v13;
  s32 countRootLine;
  f32 v15;
  u32 v16;
  u32 v18;
  sdfIVector2_t *v19;
  s32 v20;
  s32 v21;
  u32 v22;
  u32 v24;
  tagSHP_DRAW_WK *v25;
  s32 v26;
  u32 v27;

  v5 = NewSpecific(sdfIVector2_t, 2u);
  if (a_shopType)
  {
    v8 = v5;
    if (!v5)
      return;
  }
  else
  {
    v8 = shpSLineParamKN[a_menuNo];
    if (!v8)
      return;
  }
  if (!wk->bRootLineEnd)
  {
    countRootLine = wk->countRootLine;
    if (countRootLine >= 4)
    {
      LOWORD(countRootLine) = wk->countRootLine;
      v15 = 1.0;
      shpDrawStraightLineWide(v8, v6, 32, 4 * (s16)countRootLine - 16, 32, 0x43372C64u, 0, 1.0);
      v18 = -1903988096;
      v19 = v8;
      v20 = 4 * wk->countRootLine - 16;
      goto LABEL_42;
    }
    goto LABEL_43;
  }
  v13 = wk->countRootLine;
  if (v13 < 0)
    goto LABEL_26;
  if ((s16)v13 > 3)
    goto LABEL_26;
  v15 = 1.0;
  shpDrawStraightLineWide(v8, v6, 32, 32, 32, 0x43372C64u, 0, 1.0);
  v18 = -1903988096;
  goto LABEL_41;
LABEL_26:
  v21 = wk->countRootLine;
  if (v21 >= 4)
  {
    LOWORD(v21) = wk->countRootLine;
    if ((s16)v21 <= 15)
    {
      LOWORD(v21) = wk->countRootLine;
      v22 = (u8)(s32)(f32)((f32)((f32)((f32)((s16)v21 - 4) * 100.0) / -12.0) + 100.0)
          + 1127689216;
      v15 = 1.0;
      shpDrawStraightLineWide(v8, v6, 32, 32, 32, v22, 0, 1.0);
      v18 = (u8)(s32)(f32)((f32)((f32)((f32)(wk->countRootLine - 4) * 128.0) / -12.0) + 128.0)
          - 1903988224;
LABEL_41:
      v19 = v8;
      v20 = 32;
LABEL_42:
      shpDrawStraightLineWide(v19, v16, 32, v20, 32, v18, 1, v15);
    }
  }
LABEL_43:
  v25 = wk;
  if (v25->bRootLineEnd)
    goto LABEL_45;
  if (v24)
  {
    v26 = v25->countRootLine;
    if (v26 < 12)
      goto LABEL_51;
  }
  else
  {
    v25 = wk;
    v26 = v25->countRootLine;
    if (v26 < 12)
    {
LABEL_51:
      if (!v27)
        goto LABEL_55;
      goto LABEL_56;
    }
  }
  if (!v27)
  {
    v25 = wk;
  }
  v25->countRootLine = 0;
  v25->bRootLineEnd = 1;
  return;
LABEL_45:
  if (v24)
  {
    v26 = v25->countRootLine;
    if (v26 <= 15)
    {
LABEL_54:
LABEL_55:
      v25 = wk;
      LOWORD(v26) = v25->countRootLine;
LABEL_56:
      v25->countRootLine = v26 + 1;
    }
  }
  else
  {
    v25 = wk;
    v26 = v25->countRootLine;
    if (v26 <= 15)
      goto LABEL_54;
  }
}

// 0x21820b0
void shpRootLine(s32 a_x, s32 a_y) {
  u32 v3;
  s32 countRootLine;
  bool v12;
  tagSHP_DRAW_WK *v13;
  s32 v14;

  countRootLine = wk->countRootLine;
  shpDrawBezierCurveWide(a_x, a_y, 175, 42, 448, 64, v3, 48, 4 * countRootLine, 0x8E837280, 1.5);
  v12 = wk->countRootLine > 11;
  wk->bRootLineEnd = v12;
  v13 = wk;
  v14 = v13->countRootLine;
  if (v14 > 11)
    return;
  v13 = wk;
  LOWORD(v14) = v13->countRootLine;
  v13->countRootLine = v14 + 1;
}

// 0x2182270
void shpRootCursorSelect(s32 a_x, s32 a_y) {
  s32 countRootCur2;
  tagSHP_DRAW_WK *wk_local;
  s32 v6;

  countRootCur2 = wk->countRootCur2;
  if (countRootCur2 >= 0)
  {
    if (wk->countRootCur2 <= 23)
      goto LABEL_24;
  }
  goto LABEL_18;
LABEL_24:
  ++wk->countRootCur2;
LABEL_18:
  wk_local = wk;
  v6 = ++wk_local->countRootCur;
  if (v6 >= 25)
  {
    wk_local = wk;
    wk_local->countRootCur = 0;
  }
}

// 0x2182480
void shpBackSpr(s32 a_shopType, f32 a_alphaRate1, f32 a_alphaRate2) {
  s32 v7;
  sprHandle_t *phSpr;

  if (!a_shopType)
  {
    v7 = 1;
LABEL_7:
    phSpr = wk->phSpr;
    fclBackSprite(v7, (s32)a_alphaRate1, (s32)a_alphaRate2, phSpr);
    return;
  }
  if (a_shopType == 1)
  {
    v7 = 2;
    goto LABEL_7;
  }
}

// 0x2182590
void shpCommandHelp(s32 a_cmdID, u8 a_alphaRate) {
  if ((a_cmdID & 0x80000000) == 0)
  {
    fclCommandHelp(a_cmdID, a_alphaRate);
  }
}

// 0x2182610
void shpRootMenuTitle(s32 a_shoptype) {
  u8 TitleAlpha;
  u8 v5;
  sprHandle_t *phSpr;

  TitleAlpha = fclGetTitleAlpha();
  if (a_shoptype)
    goto LABEL_4;
  return;
  if (a_shoptype)
  {
LABEL_4:
    v5 = TitleAlpha;
    phSpr = wk->phSpr;
    itfDrawMiscSpriteAlpha(16, 38, 0, v5, phSpr, 103, 109);
    return;
  }
}

// 0x2182740
void shpLoadFile(s32 a_shopType) {
  ;
}

// 0x2182750
void Init(void) {
  tagSHP_DRAW_WK *v1;

  v1 = Allocate(tagSHP_DRAW_WK);
  _ctor(v1, 0);
  wk = v1;
}

// 0x21827f0
void shpEnd(void) {
  tagSHP_DRAW_WK *wk_local;

  wk_local = wk;
  if (!wk_local->phSpr)
  {
    goto LABEL_5;
  }
  wk_local = wk;
  wk_local->phSpr = 0;
LABEL_5:
  if (!wk)
    return;
  wk = 0;
}
