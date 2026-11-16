#include "types.h"
#include "BSTF.h"
#include "CMP_MENU_ID.h"
#include "PanelFocus.h"
#include "SKLID.h"
#include "cmp.h"
#include "cmpitem.h"
#include "cmpkuda.h"
#include "cmpmain.h"
#include "cmpstatus.h"
#include "cmpstatusitmsklset.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "ecmpKudaCMU.h"
#include "ecmpKudaDecideFilter.h"
#include "ecmpKudaSelectMode.h"
#include "evtbit.h"
#include "fld.h"
#include "itf.h"
#include "localize.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sdat.h"
#include "tips.h"

typedef enum {
    SKILL_NUM = 8,
    BATSKILL_NUM = 4,
    COMBSKILL_NUM = 2,
    DVL_SKL = 576,
} CMP_KUDA;

typedef enum {
    CMP_KUDA_PANEL_X = 28,
    CMP_KUDA_PANEL_Y = 65,
    CMP_KUDA_PANEL_W = 175,
    CMP_KUDA_PANEL_H = 23,
    CMP_KUDA_PANEL_FX = 23,
    CMP_KUDA_PANEL_FY = 1,
} CMP_KUDA_PANEL;

typedef enum {
    SwapStep_Swap = 0,
    SwapStep_ListReCreate = 1,
    SwapStep_ChangeState = 2,
} SwapStep;

typedef struct OrganaizeEndState OrganaizeEndState;
typedef struct OrganaizePartState OrganaizePartState;
typedef struct OrganaizeReturnState OrganaizeReturnState;
typedef struct OrganaizeSelState OrganaizeSelState;
typedef struct OrganaizeStartState OrganaizeStartState;
typedef struct OrganaizeStatusState OrganaizeStatusState;
typedef struct OrganaizeSwapState OrganaizeSwapState;
typedef struct OrganizeStateMachine OrganizeStateMachine;
typedef struct SelectStockID SelectStockID;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfMover_t itfMover_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagCMP_WORK tagCMP_WORK;

typedef bool (*cmpKudaFunc_t)(void);

struct OrganaizeEndState {
    dds3ProcessID_t *PID;
};

struct OrganaizePartState {
    dds3ProcessID_t *activePID;
    dds3ProcessID_t *partyPID;
    dds3ProcessID_t *stockPID;
    PanelFocus stock;
    s32 step;
    s32 count;
};

struct OrganaizeReturnState {
    dds3ProcessID_t *partyPID;
};

struct OrganaizeSelState {
    dds3ProcessID_t *PID;
    dds3ProcessID_t *stockPID;
    s32 waitCnt;
};

struct OrganaizeStartState {
    dds3ProcessID_t *partyPID;
    dds3ProcessID_t *stockPID;
    s32 waitCnt;
    bool dlcChk;
};

struct OrganaizeStatusState {
    dds3ProcessID_t *partyPID;
    dds3ProcessID_t *stockPID;
    dds3ProcessID_t *activePID;
    dds3ProcessID_t *menuPID;
    tagCMP_WORK *wk;
    s32 step;
};

struct OrganaizeSwapState {
    dds3ProcessID_t *PID;
    dds3ProcessID_t *stockPID;
    bool summon;
    bool dvlReturn;
    bool recreate;
    PanelFocus setPanel;
    SwapStep step;
};

struct OrganizeStateMachine {
    void *_CurrentState_k__BackingField;
    void *StateChanged;
    OrganaizeStartState *start;
    OrganaizeSelState *sel;
    OrganaizeSwapState *swap;
    OrganaizePartState *part;
    OrganaizeReturnState *ret;
    OrganaizeStatusState *status;
    OrganaizeEndState *endState;
    bool end;
    s32 _OldState_k__BackingField;
    s32 _NowState_k__BackingField;
};

dds3ProcessID_t *g_listPID;
s8 g_step;
s8 g_count;
bool g_setSaveCsr;
void *sklMenus;
SKLID *g_skillID;
SKLID *g_batskillID;
s8 *g_autoskillID;
CMP_MENU_ID g_menuID;
s16 g_stockID1;
s16 g_stockID2;
s32 g_stockSelID;
static OrganizeStateMachine *organizeMachine;
SelectStockID *selStockID1;
SelectStockID *selStockID2;
s32 g_stockSelTab;
s32 g_summonID;
s32 g_statusID;
PanelFocus g_panel;
PanelFocus g_panel2;
itfMover_t *particle;
static cmpKudaFunc_t *cmpKudaFunc;

static s32 CallFuncSkillSet(void);
static s32 CallFuncSkill2(void);
static s32 CallFuncSkill(void);
static s32 CallFuncStatus(void);
static s32 CallFuncPart(void);
static s32 CallFuncSwap(void);
static s32 CallFuncSummon(void);
static void DrawSkillList(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static bool UpdateSkillSet(void);
static bool UpdatePart(void);
static bool UpdateSwap(void);
static bool UpdateSummon(void);

// 0x1e6f920
s32 cmpGetSkillStep(void) {
  return g_step;
}

// 0x1e6f9a0
s32 cmpGetSelectStockIndex(void) {
  dds3ProcessID_t *CharPID;
  s32 SelectID;
  s32 v5;

  CharPID = cmpGetCharPID();
  SelectID = itfMenuGetSelectID(CharPID);
  if (SelectID != 2)
  {
    v5 = SelectID;
    if (SelectID == 1)
    {
      return GBWK->player->stack_p[0];
    }
    else if (SelectID < 4)
    {
      return -1;
    }
    else
    {
      return v5 + 8 * cmpGetWork()->tabpage - 4;
    }
  }
  return GBWK->player->stack_p[1];
}

// 0x1e6fb60
sdatUnitWork_t *cmpGetStockUnitWork(s32 a_stockidx) {
  if ((u32)a_stockidx > 0x1F)
    return 0;
  return GBWK->player->stock_id[a_stockidx];
}

// 0x1e6fbf0
void cmpSetStatus(s32 a_no) {
  s64 v5;
  sdatPlayerUnitWork_t *v7;
  sdatUnitWork_t *stock_id;
  s64 v9;
  sdatUnitWork_t *para;
  sdatPlayerUnitWork_t *player;

  if (g_panel == 2)
  {
    v5 = (s64)GBWK->player->stock_id + 8 * a_no;
  }
  else
  {
    if (a_no <= 0)
    {
      para = GBWK->player->para;
      goto LABEL_25;
    }
    if (a_no == 2)
    {
      player = GBWK->player;
      stock_id = player->stock_id;
      v9 = player->stack_p[1];
    }
    else
    {
      if (a_no != 1)
        goto LABEL_26;
      v7 = GBWK->player;
      stock_id = v7->stock_id;
      v9 = v7->stack_p[0];
    }
    v5 = (s64)stock_id + 8 * v9;
  }
  para = *(sdatUnitWork_t *)(v5 + 32);
LABEL_25:
  Start(para, 0);
LABEL_26:
  SetType(0x1000000, 0, 0);
}

// 0x1e6fda0
void cmpSetStatusSkill(s32 a_no) {
  ;
}

// 0x1e6fdb0
void cmpSwapUnitWork(s32 a_stockNo0, s32 a_stockNo1) {
  sdatUnitWork_t *v5;
  s64 m_Items;
  sdatUnitWork_t *v8;
  sdatUnitWork_t *v9;

  v5 = Allocate(sdatUnitWork_t);
  _ctor(v5, 0);
  m_Items = GBWK->player->stock_id;
  v8 = *(sdatUnitWork_t *)(m_Items + 8 * a_stockNo0);
  v9 = *(sdatUnitWork_t *)(m_Items + 8 * a_stockNo1);
  ClassCopy(v5, v8, 0);
  ClassCopy(v8, v9, 0);
  ClassCopy(v9, v5, 0);
}

// 0x1e6fe90
bool cmpMenuFilterUnit(sdatUnitWork_t *psUnit, sdatUnitWork_t *psUnitChk, ecmpKudaCMU iAttrId, BSTF iBadStatus) {
  s32 v9;
  sdatPlayerUnitWork_t *v11;
  sdatParaWork_t *now;
  s32 hp;
  s32 maxhp;
  sdatPlayerUnitWork_t *player;
  s32 devilid;
  s32 v20;
  s32 v22;
  s32 v24;
  s32 v26;
  s32 v28;
  s32 v29;
  s32 str;
  s32 v31;
  s32 tec;
  s32 v34;
  s32 vit;
  s32 v37;
  s32 luck;
  s32 v40;
  sdatUnitWork_t *v42;
  sdatUnitWork_t *UpdateUnit;
  CmpSklItemConversionTbl_Tbl *Item;
  ItemUpdateManager *v49;
  sdatUnitWork_t *v50;

  if (!psUnit || (iAttrId & 1) != 0 && !psUnit->devilid)
    goto LABEL_122;
  if ((iAttrId & 2) != 0 && (psUnit->flag & 2) == 0)
  {
    LOBYTE(v9) = 0;
    return v9;
  }
  if ((iAttrId & 0x2000000) != 0)
  {
    now = psUnit->now;
    hp = now->hp;
    maxhp = now->maxhp;
    player = GBWK->player;
    if (player->mag >= player->maxmag && hp >= maxhp)
      goto LABEL_122;
  }
  else
  {
    if ((iAttrId & 4) != 0 && psUnit->now->hp >= psUnit->now->maxhp)
      goto LABEL_122;
    if ((iAttrId & 8) != 0)
    {
      v11 = GBWK->player;
      if (v11->mag >= v11->maxmag)
        goto LABEL_122;
    }
  }
  if ((iAttrId & 0x10) != 0)
  {
    devilid = psUnit->devilid;
    if (sBtlGetDevilData(devilid, -1)->kuda_id != 1)
      goto LABEL_122;
  }
  if ((iAttrId & 0x20) != 0)
  {
    v20 = psUnit->devilid;
    if (sBtlGetDevilData(v20, -1)->kuda_id != 2)
      goto LABEL_122;
  }
  if ((iAttrId & 0x40) != 0)
  {
    v22 = psUnit->devilid;
    if (sBtlGetDevilData(v22, -1)->kuda_id != 3)
      goto LABEL_122;
  }
  if ((iAttrId & 0x80) != 0)
  {
    v24 = psUnit->devilid;
    if (sBtlGetDevilData(v24, -1)->kuda_id != 4)
      goto LABEL_122;
  }
  if ((iAttrId & 0x100) != 0)
  {
    v26 = psUnit->devilid;
    if (sBtlGetDevilData(v26, -1)->kuda_id != 5)
      goto LABEL_122;
  }
  if ((iAttrId & 0x200) != 0)
  {
    v28 = psUnit->devilid;
    if ((u32)sub_1B6D720(v28) != 6)
      goto LABEL_122;
  }
  if ((iAttrId & 0x400) != 0)
  {
    v29 = psUnit->devilid;
    if ((u32)sub_1B6D720(v29) != 7)
      goto LABEL_122;
  }
  if ((iAttrId & 0x800) != 0 && (psUnit->badstatus & 0x20000) != 0 || (iAttrId & 0x1000) != 0 && (psUnit->badstatus & iBadStatus) == 0)
  {
    goto LABEL_122;
  }
  if ((iAttrId & 0x2000) != 0)
  {
    str = psUnit->backup->str;
    v31 = GETITEMPARA_LOW(psUnit->pitem->str) + str;
    if ((psUnit->flag & 2) != 0)
    {
      v31 -= datGetSword4Param(GBWK->player->swordno, 0);
    }
    if (v31 > 39)
      goto LABEL_122;
  }
  if ((iAttrId & 0x4000) != 0)
  {
    tec = psUnit->backup->tec;
    v34 = GETITEMPARA_LOW(psUnit->pitem->tec) + tec;
    if ((psUnit->flag & 2) != 0)
    {
      v34 -= datGetSword4Param(GBWK->player->swordno, 1);
    }
    if (v34 > 39)
      goto LABEL_122;
  }
  if ((iAttrId & 0x8000) != 0)
  {
    vit = psUnit->backup->vit;
    v37 = GETITEMPARA_LOW(psUnit->pitem->vit) + vit;
    if ((psUnit->flag & 2) != 0)
    {
      v37 -= datGetSword4Param(GBWK->player->swordno, 2);
    }
    if (v37 > 39)
      goto LABEL_122;
  }
  if ((iAttrId & 0x10000) != 0)
  {
    luck = psUnit->backup->luck;
    v40 = GETITEMPARA_LOW(psUnit->pitem->luck) + luck;
    if ((psUnit->flag & 2) != 0)
    {
      v40 -= datGetSword4Param(GBWK->player->swordno, 3);
    }
    if (v40 > 39)
      goto LABEL_122;
  }
  if ((iAttrId & 0x20000) != 0)
  {
    if (itmUpdateMg)
    {
      UpdateUnit = GetUpdateUnit(itmUpdateMg, psUnit->devilid, psUnit->uniq_code, *(const MethodInfo **)&iBadStatus);
    }
    else
    {
      UpdateUnit = 0;
    }
    if (UpdateUnit)
      v42 = UpdateUnit;
    else
      v42 = psUnit;
    if (v42->chuusei > 99)
      goto LABEL_122;
  }
  else
  {
    v42 = 0;
  }
  if ((iAttrId & 0x40000) != 0 && (psUnit->badstatus & 0x100000) != 0 || (iAttrId & 0x100000) != 0 && (psUnit->flag & 2) == 0 || psUnit != psUnitChk && (iAttrId & 0x200000) != 0 || psUnit == psUnitChk && (iAttrId & 0x400000) != 0)
  {
LABEL_122:
    LOBYTE(v9) = 0;
    return v9;
  }
  if ((iAttrId & 0x800000) == 0)
    goto LABEL_137;
  Item = get_Item(sklItemConvTbl, g_itemNo, 0);
  v9 = CmpStatusChkUseSklItem(psUnit, Item->sklID);
  if (v9)
  {
LABEL_137:
    if ((iAttrId & 0x1000000) == 0)
      goto LABEL_138;
    v49 = itmUpdateMg;
    if (v49)
    {
      v49 = itmUpdateMg;
      v42 = GetUpdateUnit(v49, psUnit->devilid, psUnit->uniq_code, *(const MethodInfo **)&iBadStatus);
    }
    v50 = v42 ? v42 : psUnit;
    if (v50->level <= 98)
    {
LABEL_138:
      LOBYTE(v9) = 1;
      return v9;
    }
    goto LABEL_122;
  }
  return v9;
}

// 0x1e70660
bool cmpMenuDecFilter(s32 _menuID, ecmpKudaDecideFilter _fiter, bool _party, bool _empty) {
  s16 v7;
  sdatPlayerUnitWork_t *player;
  s32 v11;
  s32 devilid;

  v7 = fiter;
  if (party)
  {
    if ((v7 & 4) == 0 && (!menuID || (v7 & 8) == 0) && (menuID || (v7 & 0x10) == 0))
    {
      if ((v7 & 2) != 0)
      {
        if (menuID == 2)
        {
          if (GBWK->player->stack_p[1] != -1)
            return 1;
        }
        else
        {
          if (menuID != 1)
            return 1;
          if (GBWK->player->stack_p[0] != -1)
            return 1;
        }
      }
      else
      {
        if (menuID == 2)
        {
          player = GBWK->player;
          v11 = (u16)player->stack_p[1];
          if (v11 == 0xFFFF)
            return 1;
          player = GBWK->player;
          LOWORD(v11) = player->stack_p[1];
        }
        else
        {
          if (menuID != 1)
            return 1;
          player = GBWK->player;
          v11 = (u16)player->stack_p[0];
          if (v11 == 0xFFFF)
            return 1;
          player = GBWK->player;
          LOWORD(v11) = player->stack_p[0];
        }
        devilid = player->stock_id[(s16)v11]->devilid;
        if (DlcDevilSelCheck(devilid))
          return 1;
      }
    }
  }
  else if (empty)
  {
    if ((v7 & 0x100) == 0)
      return 1;
  }
  else if ((v7 & 0x20) == 0)
  {
    return 1;
  }
  return 0;
}

// 0x1e708a0
bool cmpMenuEmptyFilter(ecmpKudaDecideFilter _fiter) {
  return (fiter & 0x20) == 0;
}

// 0x1e708b0
s32 cmpMenuFilter(tagCMP_WORK *wk) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  s32 eSelMode;
  sdatUnitWork_t *v6;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  sdatPlayerUnitWork_t *v11;
  s32 v12;
  s64 v13;
  sdatUnitWork_t *v14;
  sdatPlayerUnitWork_t *v16;
  s32 v17;
  s64 v18;
  sdatUnitWork_t *v19;
  sdatUnitWork_t *v21;
  bool v22;
  s32 v23;
  sdatUnitWork_t *psUse;
  s32 iSelectAttrId;
  sdatUnitWork_t *v27;
  sdatUnitWork_t *v28;
  s32 iDecideAttrId;
  s64 v33;
  s64 v34;
  sdatUnitWork_t *v35;
  tagCMP_WORK *v36;
  sdatUnitWork_t *v37;
  s32 v38;
  bool v41;
  s32 v42;
  sdatUnitWork_t *v45;
  sdatUnitWork_t *v46;
  s32 v47;
  sdatUnitWork_t *v49;
  s64 v50;
  s64 v51;
  s64 v52;
  sdatUnitWork_t *v54;
  s64 v56;
  s64 v57;
  s64 v58;
  s32 v59;
  u32 v60;
  s32 StockDevilIndex;
  s32 v63;
  _BOOL4 v64;
  sdatUnitWork_t *v66;
  sdatUnitWork_t *v67;
  s32 v68;
  sdatUnitWork_t *v70;
  sdatUnitWork_t *v71;
  s32 v72;
  s32 v74;
  s32 v75;
  s32 v76;
  s32 v77;
  bool v78;
  s32 iBadStatus;
  s32 iBadStatusa;
  s64 stock_max;
  u32 eDecFilter;
  dds3ProcessID_t *v86;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  eSelMode = wk->eSelMode;
  eDecFilter = wk->eDecFilter;
  itfMenuSetFlagMenu(CharPID, -1, 1, 0);
  itfMenuSetFlagMenu(CharPID, -1, 2, 0);
  itfMenuSetFlagMenu(CharPID, -1, 4, 0);
  itfMenuSetFlagMenu(CharPID, -1, 16, 0);
  itfMenuSetFlag(CharPID, 512, 0);
  itfMenuSetFlagMenu(StockPID, -1, 1, 0);
  itfMenuSetFlagMenu(StockPID, -1, 2, 0);
  itfMenuSetFlagMenu(StockPID, -1, 4, 0);
  itfMenuSetFlagMenu(StockPID, -1, 16, 0);
  itfMenuSetFlag(StockPID, 512, 0);
  wk->iTabEnableCnt = 0;
  v6 = NewSpecific(sdatUnitWork_t, 0x20u);
  iBadStatus = wk->iBadStatus;
  player = GBWK->player;
  para = player->para;
  stock_max = (u32)player->stock_max;
  if (para && !QueryInterface(para, *(void **)(*(u64 *)v6 + 64)))
    goto LABEL_90;
  v6[0] = para;
  v11 = GBWK->player;
  v12 = v11->stack_p[0];
  if ((v12 & 0x80000000) != 0)
  {
    v14 = 0;
    goto LABEL_20;
  }
  v13 = (u16)v12;
  v14 = v11->stock_id[(u16)v12];
  if (!v14)
    goto LABEL_20;
  if (!QueryInterface(v14, *(void **)(*(u64 *)v6 + 64)))
    goto LABEL_90;
LABEL_20:
  v6[1] = v14;
  v16 = GBWK->player;
  v17 = v16->stack_p[1];
  if ((v17 & 0x80000000) != 0)
  {
    v19 = 0;
    goto LABEL_29;
  }
  v18 = (u16)v17;
  v19 = GBWK->player->stock_id[v18];
  if (!v19)
    goto LABEL_29;
LABEL_28:
  if (QueryInterface(v19, *(void **)(*(u64 *)v6 + 64)))
    goto LABEL_29;
LABEL_90:
  v19 = v16->stock_id[(u16)v17];
  if (v19)
    goto LABEL_28;
LABEL_29:
  v86 = StockPID;
  v6[2] = v19;
  v6[3] = 0;
  v21 = v6[0];
  if (!v21)
  {
LABEL_43:
    v23 = 0;
    v22 = 0;
    if (eSelMode == 6)
    {
LABEL_44:
      itfMenuSetFlagMenu(CharPID, 0, 8, v23);
      itfMenuSetFlagMenu(CharPID, 0, 16, v23);
      itfMenuSetFlagMenu(CharPID, 0, 4, 1);
    }
    goto LABEL_47;
  }
  v22 = 0;
  v23 = 0;
  switch (eSelMode)
  {
    case 2:
    case 7:
      goto LABEL_47;
    case 4:
      if (wk->psUse == v21)
        goto LABEL_34;
      goto LABEL_32;
    case 5:
      if (wk->psUse != v21)
        goto LABEL_34;
LABEL_32:
      v22 = 0;
      v23 = 0;
      goto LABEL_47;
    default:
LABEL_34:
      psUse = wk->psUse;
      iSelectAttrId = wk->iSelectAttrId;
      if (!cmpMenuFilterUnit(v6[0], wk->psUse, iSelectAttrId, iBadStatus))
        goto LABEL_43;
      v27 = v6[0];
      v28 = wk->psUse;
      iDecideAttrId = wk->iDecideAttrId;
      if (cmpMenuFilterUnit(v6[0], wk->psUse, iDecideAttrId, iBadStatus))
      {
        goto LABEL_38;
      }
      v22 = 0;
      v23 = 1;
      if (eSelMode == 6)
        goto LABEL_44;
      goto LABEL_47;
LABEL_38:
      v23 = 1;
      v22 = cmpMenuDecFilter(0, eDecFilter, 1, 0);
      if (eSelMode == 6)
        goto LABEL_44;
LABEL_47:
      itfMenuSetFlagMenu(CharPID, 0, 1, v23);
      itfMenuSetFlagMenu(CharPID, 0, 2, v22);
      v33 = 0;
      v34 = &v6[1];
      do
      {
        v35 = *(sdatUnitWork_t *)(v34 + 8 * v33);
        if (!v35)
        {
          if ((u64)(v33 + 1) > 2 || !((eSelMode != 2) & (u8)(eDecFilter >> 6)))
          {
LABEL_75:
            v42 = 0;
            v41 = 0;
            if (eSelMode != 6)
              goto LABEL_73;
            goto LABEL_76;
          }
LABEL_70:
          v42 = 1;
          v41 = cmpMenuDecFilter(v33 + 1, eDecFilter, 1, 0);
          if (eSelMode == 6)
            goto LABEL_76;
LABEL_73:
          goto LABEL_50;
        }
        if ((u32)(eSelMode - 2) < 2)
          goto LABEL_65;
        if (eSelMode != 4)
        {
          v36 = wk;
          if (eSelMode != 5 || wk->psUse != v35)
            goto LABEL_56;
LABEL_65:
          v41 = 0;
          v42 = 0;
          goto LABEL_50;
        }
        v36 = wk;
        if (wk->psUse != v35)
          goto LABEL_65;
LABEL_56:
        v37 = v36->psUse;
        v38 = v36->iSelectAttrId;
        if (!cmpMenuFilterUnit(*(sdatUnitWork_t *)(v34 + 8 * v33), v36->psUse, v38, iBadStatus))
          goto LABEL_75;
        v45 = *(sdatUnitWork_t *)(v34 + 8 * v33);
        v46 = wk->psUse;
        v47 = wk->iDecideAttrId;
        if (cmpMenuFilterUnit(*(sdatUnitWork_t *)(v34 + 8 * v33), wk->psUse, v47, iBadStatus))
        {
          goto LABEL_70;
        }
        v41 = 0;
        v42 = 1;
        if (eSelMode != 6)
          goto LABEL_73;
LABEL_76:
        itfMenuSetFlagMenu(CharPID, v33 + 1, 8, v42);
        itfMenuSetFlagMenu(CharPID, v33 + 1, 16, v42);
        itfMenuSetFlagMenu(CharPID, v33 + 1, 4, 1);
LABEL_50:
        itfMenuSetFlagMenu(CharPID, ++v33, 1, v42);
        itfMenuSetFlagMenu(CharPID, v33, 2, v41);
        v23 += v42;
      }
      while (v33 != 3);
      v49 = NewSpecific(sdatUnitWork_t, 0x20u);
      if ((s32)stock_max >= 1)
      {
        v50 = v49;
        v51 = 0;
        v52 = &v49[0];
        iBadStatusa = wk->iBadStatus;
        do
        {
          v54 = GBWK->player->stock_id[v51];
          if (v54 && !QueryInterface(v54, *(void **)(*(u64 *)v50 + 64)))
            goto LABEL_90;
          *(u64 *)(v52 + v51 * 8) = v54;
          ++v51;
        }
        while ((u32)stock_max != v51);
        v56 = 0;
        v57 = v50 + 32;
        while (2)
        {
          v58 = *(u64 *)(v57 + 8 * v56);
          v59 = *(s16 *)(v58 + 22);
          v60 = *(u32 *)(v58 + 280);
          StockDevilIndex = datGetStockDevilIndex(v59, v60);
          v63 = 0;
          v64 = 0;
          switch (eSelMode)
          {
            case 1:
            case 3:
              goto LABEL_113;
            case 4:
              if (wk->psUse != *(sdatUnitWork_t *)(v57 + 8 * v56))
                goto LABEL_112;
              goto LABEL_99;
            case 5:
              if (wk->psUse != *(sdatUnitWork_t *)(v57 + 8 * v56))
                goto LABEL_99;
              goto LABEL_112;
            default:
LABEL_99:
              if (StockDevilIndex != -1)
              {
                if (StockDevilIndex == GBWK->player->stack_p[0])
                  goto LABEL_112;
              }
              if (StockDevilIndex == GBWK->player->stack_p[1])
                goto LABEL_112;
              v66 = *(sdatUnitWork_t *)(v57 + 8 * v56);
              v67 = wk->psUse;
              v68 = wk->iSelectAttrId;
              if (!cmpMenuFilterUnit(*(sdatUnitWork_t *)(v57 + 8 * v56), wk->psUse, v68, iBadStatusa))
                goto LABEL_112;
              goto LABEL_9000;
              if (!cmpMenuFilterUnit(v66, v67, v68, iBadStatusa))
              {
LABEL_112:
                v63 = 0;
                v64 = 0;
                goto LABEL_113;
              }
LABEL_9000:
              v70 = *(sdatUnitWork_t *)(v57 + 8 * v56);
              v71 = wk->psUse;
              v72 = wk->iDecideAttrId;
              v64 = cmpMenuFilterUnit(v70, v71, v72, iBadStatusa);
              v63 = 1;
LABEL_113:
              v74 = *(s16 *)(*(u64 *)(v57 + 8 * v56) + 22);
              v75 = DlcDevilSelCheck(v74) && v64;
              v76 = *(u32 *)(*(u64 *)(v57 + 8 * v56) + 16);
              if ((v76 & 1) != 0)
              {
                v77 = v63;
              }
              else
              {
                LOBYTE(v75) = (eDecFilter & 0x80) != 0;
                v77 = (eDecFilter >> 7) & 1;
              }
              if ((v75 & 1) == 0)
              {
                v78 = 0;
                if (eSelMode == 6)
                  goto LABEL_132;
                goto LABEL_126;
              }
              if ((v76 & 1) == 0)
              {
                if ((eDecFilter & 0x100) != 0)
                  goto LABEL_123;
                goto LABEL_131;
              }
              if ((eDecFilter & 0x20) != 0)
              {
LABEL_123:
                v78 = 0;
                if (eSelMode == 6)
                {
LABEL_132:
                  itfMenuSetFlagMenu(v86, v56, 8, v77);
                  itfMenuSetFlagMenu(v86, v56, 16, v77);
                  itfMenuSetFlagMenu(v86, v56, 4, 1);
LABEL_92:
                  itfMenuSetFlagMenu(v86, v56, 1, v77);
                  itfMenuSetFlagMenu(v86, v56++, 2, v78);
                  v23 += v77;
                  if (stock_max == v56)
                    return v23;
                  continue;
                }
LABEL_126:
                goto LABEL_92;
              }
LABEL_131:
              v78 = 1;
              if (eSelMode == 6)
                goto LABEL_132;
              goto LABEL_126;
          }
        }
      }
      return v23;
  }
}

// 0x1e5e2f0
s32 cmpUpdateEnable(void) {
  tagCMP_WORK *Work;
  tagCMP_WORK *v5;

  Work = cmpGetWork();
  v5 = Work;
  return cmpMenuFilter(v5);
}

// 0x1e5e1d0
void cmpSetFilterEx(sdatUnitWork_t *psUse, ecmpKudaSelectMode eSelMode, ecmpKudaCMU iSelectAttrId, ecmpKudaCMU iDecideAttrId, ecmpKudaDecideFilter eDecFilter) {
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;

  Work = cmpGetWork();
  Work->psUse = psUse;
  p_psUse = &Work->psUse;
  *((u32 *)p_psUse + 4) = iSelectAttrId;
  *((u32 *)p_psUse + 5) = iSelectAttrId;
  *((u32 *)p_psUse + 6) = iDecideAttrId;
  *((u32 *)p_psUse + 2) = eSelMode;
  *((u32 *)p_psUse + 3) = eDecFilter;
}

// 0x1e71580
void cmpSetFilter(sdatUnitWork_t *psUse, ecmpKudaSelectMode eSelMode, ecmpKudaCMU iAttrId) {
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;

  Work = cmpGetWork();
  Work->psUse = psUse;
  p_psUse = &Work->psUse;
  *((u32 *)p_psUse + 4) = iAttrId;
  *((u32 *)p_psUse + 5) = iAttrId;
  *((u32 *)p_psUse + 6) = iAttrId;
  *((u32 *)p_psUse + 2) = eSelMode;
  *((u32 *)p_psUse + 3) = 0;
}

// 0x1e5e280
void cmpSetFilterBadStatus(BSTF iBadStatus) {
  cmpGetWork()->iBadStatus = iBadStatus;
}

// 0x1e71680
void cmpClearFilter(void) {
  cmpSetFilter(0, 0, 0);
  cmpGetWork()->iBadStatus = 0;
  return;
}

// 0x1e71750
bool cmpChkEnableUseSkill(sdatUnitWork_t *use, sdatUnitWork_t *tgt, SKLID id) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v8;
  s32 devilid;
  s32 mapSummonID;
  s32 v12;
  _BOOL4 v14;
  s32 badstatus;

  Skilltbl = sBtlGetSkilltbl(id);
  if (!Skilltbl)
    return (char)Skilltbl;
  if ((use->flag & 4) == 0)
    goto LABEL_39;
  if (!use->devilid)
    goto LABEL_39;
  v8 = Skilltbl;
  if ((tgt->flag & 6) == 4 && !tgt->devilid)
    goto LABEL_39;
  if (fldGb->nakamaMode)
  {
    devilid = use->devilid;
    mapSummonID = GBWK->mapSummonID;
    if (mapSummonID != devilid)
      goto LABEL_39;
    v12 = tgt->devilid;
    mapSummonID = GBWK->mapSummonID;
    if (mapSummonID != v12)
      goto LABEL_39;
  }
  if ((v8->area & 8) != 0 && ((tgt->flag & 2) == 0 || tgt->devilid) || use != tgt && (v8->area & 0x2000) != 0)
  {
    goto LABEL_39;
  }
  LOBYTE(Skilltbl) = 0;
  v14 = (v8->area & 0x1000) == 0 || use != tgt;
  if ((v8->area & 0x8000) == 0 && v14)
  {
    badstatus = tgt->badstatus;
    if ((badstatus & 0x100000) == 0 && ((badstatus & 0x10000) == 0 || !tgt->devilid))
    {
      if ((badstatus & 0x20000) != 0)
      {
        if ((v8->attr & 0x200) != 0 && (v8->badst & 0x20000) != 0)
        {
          LOBYTE(Skilltbl) = 1;
          return (char)Skilltbl;
        }
      }
      else
      {
        if (id == 116 && (badstatus & 0x3FC0) != 0)
        {
          LOBYTE(Skilltbl) = 1;
          return (char)Skilltbl;
        }
        if (tgt->now->hp < tgt->now->maxhp && (v8->flg & 4) != 0 && !v8->badst)
        {
          LOBYTE(Skilltbl) = 1;
          return (char)Skilltbl;
        }
      }
    }
LABEL_39:
    LOBYTE(Skilltbl) = 0;
  }
  return (char)Skilltbl;
}

// 0x1e71980
void cmpChkSkillSelectHd(void) {
  s32 v2;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *v7;
  System_Collections_Generic_List_Enumerator_T__o v10;
  System_Collections_Generic_List_Enumerator_T__o v11;

  _GetEnumerator(&v10, sklMenus);
  v2 = 0;
  v11 = v10;
  v10._list = 0;
  *(u64 *)&v10._index = &v11;
  while (_MoveNext(&v11))
  {
    if (((s64)v11._current[1].monitor & 0x80000000) == 0)
    {
      if (!LOBYTE(v11._current[1].klass))
      {
        itfMenuSetFlagMenu(g_listPID, v2, 2, 0);
        goto LABEL_7;
      }
      v5 = g_listPID;
      itfMenuSetFlagMenu(v5, v2, 1, 1);
      itfMenuSetFlagMenu(g_listPID, v2, 2, 1);
      goto LABEL_7;
    }
    v7 = g_listPID;
    itfMenuSetFlagMenu(v7, v2, 1, 0);
    itfMenuSetFlagMenu(g_listPID, v2, 2, 0);
LABEL_7:
    ++v2;
  }
  _Dispose(&v11);
}

// 0x1e71c90
void cmpChkSkillSelect(sdatUnitWork_t *a_pUseUnit) {
  s32 v5;
  u32 v7;
  s32 badstatus;
  s32 j;
  void *v11;
  s32 v12;
  s32 v13;
  u32 v14;
  s32 v16;
  dds3ProcessID_t *v18;
  s32 i;
  s32 klass_high;
  s32 devilid;
  u32 uniq_code;
  s32 monitor;
  s64 monitor_low;
  s32 SkillCost;
  sdatUnitWork_t *para;
  s64 v34;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *v38;
  dds3ProcessID_t *v41;
  Il2CppObject *Item;
  s32 k;
  void *v49;
  s32 v50;
  s32 v51;
  u32 v52;
  s32 v54;
  Il2CppObject *v56;
  dds3ProcessID_t *v58;

  if (!fldGb->nakamaMode)
  {
LABEL_13:
    badstatus = a_pUseUnit->badstatus;
    if ((badstatus & 0x120400) == 0 && ((badstatus & 0x10000) == 0 || !a_pUseUnit->devilid))
    {
      for (i = 0; ; ++i)
      {
        if (i >= sklMenus->_size)
          return;
        klass_high = HIDWORD(_get_Item(sklMenus, i)[1].klass);
        devilid = a_pUseUnit->devilid;
        uniq_code = a_pUseUnit->uniq_code;
        if (klass_high != datGetStockDevilIndex(devilid, uniq_code))
          continue;
        monitor = _get_Item(sklMenus, i)[1].monitor;
        if (cmpChkSousaSkill(monitor))
          continue;
        monitor_low = LODWORD(_get_Item(sklMenus, i)[1].monitor);
        if ((monitor_low & 0x80000000) != 0)
        {
LABEL_100:
          Item = _get_Item(sklMenus, i);
          LOBYTE(Item[1].klass) = 0;
          itfMenuSetFlagMenu(g_listPID, i, 2, 0);
          continue;
        }
        if ((tbldata[monitor_low]->useflg & 2) == 0)
          goto LABEL_100;
        SkillCost = sBtlGetSkillCost(a_pUseUnit, monitor_low);
        if (GBWK->player->mag < SkillCost)
          goto LABEL_100;
        if (!fldGb->nakamaMode)
        {
          para = GBWK->player->para;
          if (cmpChkEnableUseSkill(a_pUseUnit, para, monitor_low))
            goto LABEL_93;
          v34 = 0;
          while (2)
          {
            player = GBWK->player;
            if (v34 >= player->stock_max)
              goto LABEL_100;
            v38 = player->stock_id[v34];
            ++v34;
            if (cmpChkEnableUseSkill(a_pUseUnit, v38, monitor_low))
              goto LABEL_93;
            continue;
          }
        }
        if (!cmpChkEnableUseSkill(a_pUseUnit, a_pUseUnit, monitor_low))
          goto LABEL_100;
LABEL_93:
        v41 = g_listPID;
        itfMenuSetFlagMenu(v41, i, 2, 1);
        LOBYTE(_get_Item(sklMenus, i)[1].klass) = 1;
      }
    }
    for (j = 0; ; ++j)
    {
      v11 = sklMenus;
      if (j >= v11->_size)
        return;
      v11 = sklMenus;
      v12 = HIDWORD(_get_Item(v11, j)[1].klass);
      v13 = a_pUseUnit->devilid;
      v14 = a_pUseUnit->uniq_code;
      if (v12 != datGetStockDevilIndex(v13, v14))
        continue;
      v16 = _get_Item(sklMenus, j)[1].monitor;
      if (!cmpChkSousaSkill(v16))
      {
        v18 = g_listPID;
        itfMenuSetFlagMenu(v18, j, 2, 0);
        continue;
      }
    }
  }
  v5 = a_pUseUnit->devilid;
  if (GBWK->mapSummonID == v5)
  {
    v7 = a_pUseUnit->uniq_code;
    if (v7 == GBWK->mapSummonUNIQ)
      goto LABEL_13;
  }
  for (k = 0; ; ++k)
  {
    v49 = sklMenus;
    if (k >= v49->_size)
      break;
    v49 = sklMenus;
    v50 = HIDWORD(_get_Item(v49, k)[1].klass);
    v51 = a_pUseUnit->devilid;
    v52 = a_pUseUnit->uniq_code;
    if (v50 != datGetStockDevilIndex(v51, v52))
      continue;
    v54 = _get_Item(sklMenus, k)[1].monitor;
    if (cmpChkSousaSkill(v54))
      continue;
    v56 = _get_Item(sklMenus, k);
    LOBYTE(v56[1].klass) = 0;
    v58 = g_listPID;
    itfMenuSetFlagMenu(v58, k, 2, 0);
  }
}

// 0x1e725f0
s32 cmpUpdateEnableUseSkillUnit(SKLID a_skillID) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v4;
  char v5;
  s32 v7;
  s32 v8;
  s32 v9;
  u32 v10;
  u32 badst;
  s32 v12;
  s32 v13;
  s32 v14;
  u16 area;
  s32 v16;
  u32 v17;
  u32 v18;
  s32 v20;
  sdatUnitWork_t *v22;
  s32 v23;
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;
  char v26;
  tagCMP_WORK *v30;

  Skilltbl = sBtlGetSkilltbl(a_skillID);
  if (Skilltbl)
  {
    v4 = Skilltbl;
    v5 = Skilltbl->area << 29 >> 31;
    v7 = v5 & 6;
    if (fldGb->nakamaMode)
      v8 = 4;
    else
      v8 = v7;
    if ((v4->attr & 0x200) != 0)
    {
      badst = v4->badst;
      v9 = badst & ((s32)(badst << 14) >> 31);
      v10 = (badst & 0x20000) >> 5;
    }
    else
    {
      v9 = 0;
      v10 = 0;
    }
    if (a_skillID == 116)
      v12 = 16320;
    else
      v12 = v9;
    if (a_skillID == 116)
      v13 = 4096;
    else
      v13 = v10;
    if ((v4->flg & 4) != 0 && (v4->badst & 0x20000) == 0)
    {
      v14 = v10 | 0x804;
      if (a_skillID == 116)
        v13 = 6144;
      else
        v13 = v14;
    }
    area = v4->area;
    v16 = (u16)(area & 0x1000) >> 12;
    v17 = ((area & 0x2000) << 8) & 0xFFEFFFFF | ((((u8)(area & 8) >> 3) & 1) << 20);
    v18 = ((area & 0x2000) << 8) & 0xFFAFFFFF
        | ((((u8)(area & 8) >> 3) & 1) << 20) & 0xFFBFFFFF
        | (((area & 0x1000) != 0) << 22);
    v20 = v18 | v13;
    if (g_stockID1 <= 0x1F)
    {
      v22 = GBWK->player->stock_id[g_stockID1];
      v23 = v20 | 0x40000;
LABEL_35:
      Work = cmpGetWork();
      Work->psUse = v22;
      p_psUse = &Work->psUse;
      *((u32 *)p_psUse + 4) = v13;
      *((u32 *)p_psUse + 5) = v13;
      v26 = byte_575803D;
      *((u32 *)p_psUse + 6) = v23;
      *((u32 *)p_psUse + 2) = v8;
      *((u32 *)p_psUse + 3) = 0;
      if ((v26 & 1) != 0)
      {
        goto LABEL_39;
      }
      else
      {
LABEL_39:
        cmpGetWork()->iBadStatus = v12;
        goto LABEL_40;
      }
      cmpGetWork()->iBadStatus = v12;
LABEL_40:
      v30 = cmpGetWork();
      LODWORD(Skilltbl) = cmpMenuFilter(v30);
      return (s32)Skilltbl;
    }
    v22 = 0;
    v23 = v20 | 0x40000;
    goto LABEL_35;
  }
  return (s32)Skilltbl;
}

// 0x1e72950
static s32 CallFuncSkillSet(void) {
  dds3ProcessID_t *CharPID;
  s32 SelectID;
  tagCMP_WORK *Work;

  CharPID = cmpGetCharPID();
  SelectID = itfMenuGetSelectID(CharPID);
  Work = cmpGetWork();
  if (Work->tabpage)
  {
    SelectID += 8 * Work->tabpage;
  }
  else if (SelectID > 3)
  {
    goto LABEL_18;
  }
  if (SelectID == 1)
  {
    SelectID = GBWK->player->stack_p[0] + 4;
  }
  if (SelectID == 2)
  {
    SelectID = GBWK->player->stack_p[1] + 4;
  }
LABEL_18:
  g_statusID = SelectID;
  ++g_step;
  cmpSetSklCsrMax();
  return 1;
}

// 0x1e72b30
s32 cmpNakamaView(void) {
  s32 StockPanelActive;
  dds3ProcessID_t *StockPID;
  s32 SelectID;

  cmpGetWork();
  StockPanelActive = cmpGetStockPanelActive();
  if (StockPanelActive == 2)
  {
    StockPID = cmpGetStockPID();
  }
  else
  {
    StockPID = cmpGetCharPID();
  }
  SelectID = itfMenuGetSelectID(StockPID);
  g_statusID = SelectID;
  cmpSetStatus(SelectID);
  cmpSetFlagCtrlMode(1);
  cmpSetFlagNoExplan(1);
  return 1;
}

// 0x1e72ca0
static s32 CallFuncSkill2(void) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  s32 SelectID;
  Il2CppObject *Item;
  s64 v7;
  s32 v13;
  s32 v14;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  SelectID = itfMenuGetSelectID(g_listPID);
  Item = _get_Item(sklMenus, SelectID);
  g_stockID1 = HIDWORD(Item[1].klass);
  cmpSetFilterSkillUse();
  itfMenuSetFlag(g_listPID, 8, 0);
  itfMenuSetFlagMenu(g_listPID, SelectID, 8, 1);
  itfMenuSetFlag(CharPID, 512, 0);
  itfMenuSetFlag(StockPID, 512, 0);
  v7 = SelectID;
  cmpUpdateEnableUseSkillUnit(g_skillID[v7]);
  g_panel = cmpSetFocusPanel(1);
  itfMenuSetSelectID(CharPID, 0);
  cmpUpdateSelectPosCharPID();
  cmpUpdateSelectNextPosCharPID2();
  cmpUpdateSelectNextPosStockPID();
  v13 = g_skillID[v7];
  if (v13 == 118)
  {
    v14 = 21;
    goto LABEL_19;
  }
  v13 = g_skillID[SelectID];
  if (v13 == 119)
    v14 = 21;
  else
    v14 = 20;
LABEL_19:
  itfMenuSetDecideSE(CharPID, -1, v14);
  itfMenuSetDecideSE(StockPID, -1, v14);
  *(u16 *)&g_step = -255;
  return 1;
}

// 0x1e73100
static s32 CallFuncSkill(void) {
  s32 StockPanelActive;
  dds3ProcessID_t *CharPID;
  s32 SelectID;
  s32 v9;
  s16 *m_Items;
  sdatUnitWork_t *stock_id;
  Il2CppClass **v18;
  sdatUnitWork_t *v20;
  s32 v21;
  s32 v22;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v28;
  s64 v29;
  sdatUnitWork_t *v31;
  sdatUnitWork_t *v34;
  sdatUnitWork_t *v36;
  s32 SkillCost;
  s64 i;
  sdatUnitWork_t *v47;
  sdatUnitWork_t *v48;
  dds3ProcessID_t *v50;
  s32 v55;

  StockPanelActive = cmpGetStockPanelActive();
  g_panel = StockPanelActive;
  if (StockPanelActive == 1)
  {
    CharPID = cmpGetCharPID();
  }
  else
  {
    CharPID = cmpGetStockPID();
  }
  SelectID = itfMenuGetSelectID(CharPID);
  cmpGetWork();
  v9 = SelectID;
  if (g_panel != 1)
    goto LABEL_31;
  if (SelectID == 2)
  {
    m_Items = &GBWK->player->stack_p[1];
  }
  else
  {
    v9 = SelectID;
    if (SelectID != 1)
      goto LABEL_31;
    m_Items = GBWK->player->stack_p;
  }
  v9 = *m_Items;
LABEL_31:
  g_step = (u8)g_step;
  if (g_step != 1)
  {
    LOBYTE(g_step) = g_step;
    g_step = g_step + 1;
    return 1;
  }
  stock_id = GBWK->player->stock_id;
  v18 = &stock_id->obj.klass + g_stockID1;
  v20 = v18[4];
  v21 = itfMenuGetSelectID(g_listPID);
  v22 = g_skillID[v21];
  if (itfMenuGetFlagMenu(CharPID, SelectID, 4u))
  {
    para = GBWK->player->para;
    if (cmpChkEnableUseSkill(v20, para, v22))
    {
      v28 = GBWK->player->para;
      sdatCalcSkill(v20, v28, v22);
    }
    v29 = 32;
    while (1)
    {
      v31 = *(sdatUnitWork_t *)((char *)&GBWK->player->stock_id->obj.klass + v29);
      if (cmpChkEnableUseSkill(v20, v31, v22))
      {
        v34 = *(sdatUnitWork_t *)((char *)&GBWK->player->stock_id->obj.klass + v29);
        sdatCalcSkill(v20, v34, v22);
      }
      v29 += 8;
      if (v29 == 288)
        goto LABEL_80;
    }
  }
  if (!SelectID)
  {
    if (g_panel == 1)
      goto LABEL_68;
  }
  v36 = GBWK->player->stock_id[v9];
  goto LABEL_79;
LABEL_68:
  v36 = GBWK->player->para;
LABEL_79:
  sdatCalcSkill(v20, v36, v22);
LABEL_80:
  SkillCost = sBtlGetSkillCost(v20, v22);
  GBWK->player->mag -= SkillCost;
  cmpUpdateEnableUseSkillUnit(v22);
  for (i = 0; ; ++i)
  {
    v47 = GBWK->player->stock_id;
    if (i >= SLODWORD(v47->max_length))
      break;
    v48 = v47[i];
    if ((v48->flag & 1) == 0)
      continue;
    cmpChkSkillSelect(v48);
  }
  v50 = g_listPID;
  goto LABEL_100;
LABEL_101:
  cmpUpdateSelectPosCharPID();
  cmpUpdateSelectNextPosCharPID2();
  cmpUpdateSelectNextPosStockPID();
  v55 = cmpSetFocusPanel(g_panel);
  g_panel = v55;
  goto LABEL_9002;
LABEL_100:
  if (itfMenuGetFlagMenu(v50, v21, 2u))
    goto LABEL_101;
  itfMenuSetFlag(CharPID, 256, 1);
LABEL_9002:
  g_count = 0;
  return 1;
}

// 0x1e738e0
void cmpSetSavePanel(bool _second, PanelFocus _focus) {
  if (!second)
  {
    g_panel = focus;
    return;
  }
  g_panel2 = focus;
}

// 0x1e739a0
s32 cmpCallFuncOraganize(void) {
  s32 StockPanelActive;
  dds3ProcessID_t *StockPID;
  s32 SelectID;
  s32 v6;
  u32 v16;
  u32 v19;

  cmpGetWork();
  StockPanelActive = cmpGetStockPanelActive();
  if (StockPanelActive == 2)
  {
    StockPID = cmpGetStockPID();
  }
  else
  {
    StockPID = cmpGetCharPID();
  }
  SelectID = itfMenuGetSelectID(StockPID);
  v6 = SelectID;
  if (StockPanelActive != 2)
  {
    if (SelectID == 1)
    {
      v6 = GBWK->player->stack_p[0];
    }
    else
    {
      v16 = (u16)GBWK->player->stack_p[1];
      if (v16 >= 0xFFFE)
        LOWORD(v16) = -2;
      v6 = (s16)v16;
    }
LABEL_16:
    if (g_step)
      goto LABEL_17;
    g_stockID1 = SelectID;
    selStockID1->stockID = v6;
    selStockID1->menuID = SelectID;
    selStockID1->stock = StockPanelActive;
    if (!v19)
    itfMenuSetFlagMenu(StockPID, SelectID, 16, 1);
    cmpSetMarkID(SelectID);
    StateChange(organizeMachine, 2, 0);
    g_panel = StockPanelActive;
    goto LABEL_25;
  }
  goto LABEL_16;
LABEL_17:
  g_stockID2 = SelectID;
  selStockID2->stockID = v6;
  selStockID2->menuID = SelectID;
  selStockID2->stock = StockPanelActive;
  StateChange(organizeMachine, 3, 0);
  g_panel2 = StockPanelActive;
LABEL_25:
  ++g_step;
  return 1;
}

// 0x1e73cf0
static s32 CallFuncStatus(void) {
  dds3ProcessID_t *CharPID;
  s32 SelectID;
  s32 tabpage;
  bool v5;
  s32 v7;
  s32 v8;

  CharPID = cmpGetCharPID();
  SelectID = itfMenuGetSelectID(CharPID);
  tabpage = cmpGetWork()->tabpage;
  v5 = SelectID < 4 || tabpage == 0;
  v7 = 8 * tabpage;
  if (v5)
    v7 = 0;
  v8 = v7 + SelectID;
  g_statusID = v8;
  cmpSetStatus(v8);
  ++g_step;
  cmpSetFlagCtrlMode(1);
  cmpSetFlagNoExplan(1);
  return 1;
}

// 0x1e73e40
static s32 CallFuncPart(void) {
  return 1;
}

// 0x1e73e50
static s32 CallFuncSwap(void) {
  return 1;
}

// 0x1e73e60
s32 cmpCallFuncSummon2(void) {
  return 1;
}

// 0x1e73e70
static s32 CallFuncSummon(void) {
  return 1;
}

// 0x1e73e80
static void DrawSkillList(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  CmpSubMenuPass *p_menuPass;
  CmpSubMenuPass *v15;
  void *klass;
  Il2CppObject *ProcessData;
  Il2CppClass *v21;
  s64 v22;
  s64 namespaze;
  Il2CppType *p_byval_arg;
  s32 v25;
  s64 v26;
  u8 Alpha;
  bool v31;
  u32 v32;
  s64 v33;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v35;
  s32 SkillIconType;
  s64 v37;
  s32 v38;
  CmpSubMenuPass *v39;
  char *v40;
  CmpSubMenuPass *v41;
  char *v42;
  CmpSubMenuPass *v43;
  s32 klass_high;
  void *v46;
  dds3ProcessID_t *v48;
  s64 v49;
  s32 v51;
  f32 v52;
  s32 v53;
  f32 v54;
  s32 v57;
  s32 SkillIconSpriteNo;
  s32 v59;
  dds3ProcessID_t *v61;
  s64 v67;
  s64 v68;
  sdatUnitWork_t *para;
  s32 v71;
  s32 SkillCost;
  Il2CppObject *v73;
  char *v74;
  char *LocalizeText;
  sdatPlayerUnitWork_t *player;
  s32 v77;
  s32 v78;
  u32 v81;
  s32 data;

  p_menuPass = &cmpGetWork()->menuPass;
  if (!p_menuPass)
  {
    v15 = Allocate(CmpSubMenuPass);
    _ctor(v15, 0);
    p_menuPass = v15;
  }
  klass = _get_Instance()[7].klass;
  exMenu = 1;
  ProcessData = dds3GetProcessData(g_listPID);
  if (!ProcessData)
    goto LABEL_23;
  goto LABEL_21;
  if (!ProcessData)
LABEL_21:
LABEL_23:
  ExtendMenuClearCheck(klass, (s32)ProcessData[8].klass, 0);
  ExtendMenuOn(klass, 8, 0);
  v21 = ProcessData[5].klass;
  if ((s32)v21->_1.namespaze < 1)
  {
    v25 = -1;
  }
  else
  {
    v22 = 0;
    namespaze = (u32)v21->_1.namespaze;
    p_byval_arg = &v21->_1.byval_arg;
    v25 = -1;
    do
    {
      v26 = *(u64 *)(*((u64 *)&p_byval_arg->data + v22) + 24);
      if (v26 && *(u32 *)(v26 + 16) == a_id)
        v25 = v22;
      ++v22;
    }
    while (namespaze != v22);
  }
  (klass->scrollBarSet->klass->vtable._4_ScrollBarDraw.methodPtr)(klass->scrollBarSet, HIDWORD(ProcessData[8].klass), HIDWORD(ProcessData[7].monitor), *((u32 *)ProcessData[9].monitor + SBYTE4(ProcessData[5].monitor) + 8), klass->scrollBarSet->klass->vtable._4_ScrollBarDraw.method);
  v77 = a_x;
  Alpha = itfMenuImgGetAlpha(g_listPID, 2);
  v78 = a_z;
  if (Alpha)
    v31 = 0;
  else
    v31 = a_fontColor == 1692838528;
  if (v31)
    v32 = 1;
  else
    v32 = a_fontColor;
  v81 = v32;
  v33 = a_id;
  Skilltbl = sBtlGetSkilltbl(g_skillID[v33]);
  v35 = g_skillID[v33];
  SkillIconType = cmpGetSkillIconType(Skilltbl, v35);
  v37 = 8 * v25;
  v38 = SkillIconType;
  v39 = p_menuPass;
  v40 = *(char **)((*(u64 **)((char *)&ProcessData[5].klass->_1.byval_arg.data + v37))[3] + 48);
  v39->str = v40;
  v39 = ((char *)v39 + 24);
  v39[-1].devilID = v25;
  v41 = p_menuPass;
  v42 = *(char **)((*(u64 **)((char *)&ProcessData[5].klass->_1.byval_arg.data + v37))[3] + 56);
  v41->tag = v42;
  v43 = p_menuPass;
  v43->sklSprNo = v38;
  v43->itmType = 0;
  v43->color = v81;
  v43->id = 61441;
  if (sklMenus->_size > a_id)
  {
    klass_high = HIDWORD(_get_Item(sklMenus, a_id)[1].klass);
    v43->devilID = datGetStockDevilID(klass_high);
    v43 = p_menuPass;
  }
  ExtendMenuText(klass, v43, 0);
  if (!cmpNowStatus())
  {
    v46 = *((void *)_get_Instance()[9].monitor + 3);
    if (get_activeSelf(v46, 0))
      SetActive(v46, 0, 0);
  }
  v48 = g_listPID;
  goto LABEL_59;
LABEL_63:
  if (Alpha)
  {
    MainMenuCursorMove(klass, v25, 0, 0);
    goto LABEL_71;
  }
  else if (v81 == 1)
  {
    MainMenuCursorMove(klass, v25, 1, 0);
    goto LABEL_71;
  }
  else
  {
    ExtendMenuCursorClear(klass, 0);
    goto LABEL_71;
  }
LABEL_71:
  v51 = g_skillID[v49];
  if (v51 < 1)
    goto LABEL_82;
  v52 = a_alphaRate;
  if (cmpChkSousaSkill(v51))
  {
    LOWORD(v51) = fldChangeFromSKLIDToMskGetNo(v51);
    v53 = 2;
    v54 = v52 / 255.0;
    goto LABEL_81;
  }
  v53 = 0;
  v54 = v52 / 255.0;
LABEL_81:
  itfDrawMiscHelp(0xA09DC380, v54, v53, v51, 0);
  goto LABEL_82;
LABEL_59:
  v49 = a_id;
  if (itfMenuGetSelectID(v48) == a_id)
    goto LABEL_63;
LABEL_82:
  v57 = g_skillID[v49];
  SkillIconSpriteNo = cmpGetSkillIconSpriteNo(v57);
  if ((SkillIconSpriteNo & 0x80000000) == 0)
  {
    v59 = SkillIconSpriteNo;
    itfIconDrawSprite(v77 + 1, a_y + 1, v78, a_alphaRate, v59, 108);
  }
  v61 = g_listPID;
  itfMenuChkMenuTop(v61, a_id);
  if ((g_skillID[v49] & 0x80000000) == 0)
  {
    if ((g_stockID1 & 0x80000000) == 0)
    {
      v67 = (u16)g_stockID1;
      v68 = (s64)GBWK->player->stock_id + 8 * v67;
      para = *(sdatUnitWork_t *)(v68 + 32);
      goto LABEL_100;
    }
    player = GBWK->player;
    para = player->para;
LABEL_100:
    v71 = g_skillID[v49];
    SkillCost = sBtlGetSkillCost(para, v71);
    if (SkillCost >= 1)
    {
      data = SkillCost;
      v73 = Box(s32, &data);
      v74 = Format("{0,3:d}", v73, 0);
      Concat_54766928(0, v74, 0);
    }
    return;
  }
  LocalizeText = GetLocalizeText("CMP_STATUS_L0018", 1);
  Concat_54766928(0, LocalizeText, 0);
}

// 0x1e74920
bool cmpSklMenuUseCheck(sdatUnitWork_t *_useUnit, SKLID _sklID) {
  s32 devilid;
  s32 badstatus;
  bool v8;
  s32 SkillCost;
  sdatUnitWork_t *para;
  s64 v17;
  sdatUnitWork_t *v19;
  sdatPlayerUnitWork_t *player;
  s64 stock_max;

  if (!fldGb->nakamaMode)
    goto LABEL_11;
  devilid = useUnit->devilid;
  if (GBWK->mapSummonID == devilid)
    goto LABEL_11;
  return 0;
LABEL_11:
  badstatus = useUnit->badstatus;
  if ((badstatus & 0x120400) != 0)
    return 0;
  if ((badstatus & 0x10000) != 0)
  {
    v8 = 0;
    if (sklID < 0 || useUnit->devilid)
      return v8;
  }
  else if (sklID < 0)
  {
    return 0;
  }
  if ((tbldata[sklID]->useflg & 2) == 0)
    return 0;
  SkillCost = sBtlGetSkillCost(useUnit, sklID);
  if (GBWK->player->mag < SkillCost)
    return 0;
  if (!fldGb->nakamaMode)
  {
    para = GBWK->player->para;
    if (cmpChkEnableUseSkill(useUnit, para, sklID))
      return 1;
    v17 = 0;
    while (1)
    {
      player = GBWK->player;
      stock_max = player->stock_max;
      v8 = v17 < stock_max;
      if (v17 >= stock_max)
        return v8;
      v19 = player->stock_id[v17];
      ++v17;
      if (cmpChkEnableUseSkill(useUnit, v19, sklID))
        return v8;
    }
  }
  return cmpChkEnableUseSkill(useUnit, useUnit, sklID);
}

// 0x1e74ca0
void cmpAddSklMenu(sdatUnitWork_t *_unit, SKLID _sklID) {
  SklMenu *v5;
  s32 devilid;
  u32 uniq_code;
  bool v9;
  void *sklMenus_local;
  u64 *v13;
  s64 size;
  void *items;
  Il2CppClass **v16;

  v5 = Allocate(SklMenu);
  _ctor(v5, 0);
  devilid = unit->devilid;
  uniq_code = unit->uniq_code;
  v5->stockIndex = datGetStockDevilIndex(devilid, uniq_code);
  v5->sklID = sklID;
  v9 = cmpSklMenuUseCheck(unit, sklID);
  v5->use = v9;
  if (tbldata[sklID]->sortType == 11)
  {
    v5->sort = 1;
    goto LABEL_22;
  }
  else
  {
    if (tbldata[sklID]->sortType == 12)
    {
      v5->sort = 2;
      goto LABEL_22;
    }
    else
    {
      v5->sort = 0;
      goto LABEL_22;
    }
  }
LABEL_22:
  sklMenus_local = sklMenus;
  v13 = Method_System_Collections_Generic_List_SklMenu__Add__;
  size = sklMenus_local->_size;
  ++sklMenus_local->_version;
  items = sklMenus_local->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(sklMenus_local, v5, *(const MethodInfo_2DFC660 **)(*(u64 *)(v13[4] + 192) + 112));
  }
  else
  {
    v16 = &items->obj.klass + size;
    v16[4] = v5;
    sklMenus_local->_size = size + 1;
  }
}

// 0x1e74f30
void cmpCreateSklMenus(void) {
  s32 size;
  s32 v5;
  void **v7;
  sdatUnitWork_t *stock_id;
  s64 v9;
  void **v10;
  sdatUnitWork_t *v11;
  s32 devilid;
  s64 v14;
  s32 v15;
  sdatUnitWork_t *v16;
  s64 v17;
  sdatUnitWork_t *v18;
  s32 v19;
  SKLID *aOmoideSkill;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  sdatUnitWork_t *v30;
  s64 i;
  sdatUnitWork_t *v32;
  s32 v33;
  SKLID *sousaSkill;
  s32 v36;
  s32 v37;
  void *Instance;
  void *v40;
  void *v41;
  void *DvlSklList;
  void *v43;

  cmpGetWork();
  size = sklMenus->_size;
  v5 = sklMenus->_version + 1;
  sklMenus->_size = 0;
  sklMenus->_version = v5;
  if (size >= 1)
    Clear(sklMenus->_items, 0, size, 0);
  v7 = &RaijinDLC;
  stock_id = GBWK->player->stock_id;
  if (SLODWORD(stock_id->max_length) >= 1)
  {
    v9 = 0;
    while (1)
    {
      v10 = v7;
      v11 = stock_id[v9];
      devilid = v11->devilid;
      if (*((u32 *)*v7 + 56))
      {
        if (DlcDevilSelCheck(devilid))
          break;
        goto LABEL_10;
      }
      if (DlcDevilSelCheck(devilid))
        break;
LABEL_10:
      ++v9;
      v7 = v10;
      if (v9 >= SLODWORD(stock_id->max_length))
      {
        goto LABEL_31;
      }
    }
    v14 = 32;
    while (1)
    {
      v15 = *(u32 *)((char *)&v11->haveskill->obj.klass + v14);
      if (v15)
      {
        if (v15 != 149 && v15 != 288)
          break;
      }
LABEL_19:
      v14 += 4;
      if (v14 == 64)
        goto LABEL_10;
    }
    if ((tbldata[v15]->type & 0xF000) == 0x1000 || (tbldata[v15]->type & 0xF000) == 0)
    {
      cmpAddSklMenu(v11, v15);
    }
    goto LABEL_19;
  }
LABEL_31:
  v16 = GBWK->player->stock_id;
  if (SLODWORD(v16->max_length) >= 1)
  {
    v17 = 0;
    while (1)
    {
      v18 = v16[v17];
      v19 = v18->devilid;
      if (*((u32 *)*v7 + 56))
      {
        if (DlcDevilSelCheck(v19))
          goto LABEL_41;
      }
      else
      {
        if (DlcDevilSelCheck(v19))
        {
LABEL_41:
          aOmoideSkill = v18->aOmoideSkill;
          v22 = aOmoideSkill[0];
          if (v22 && v22 != 149 && v22 != 288)
          {
            cmpAddSklMenu(v18, v22);
            aOmoideSkill = v18->aOmoideSkill;
          }
          v23 = aOmoideSkill[1];
          if (v23 && v23 != 149 && v23 != 288)
          {
            cmpAddSklMenu(v18, v23);
            aOmoideSkill = v18->aOmoideSkill;
          }
          v24 = aOmoideSkill[2];
          if (v24 && v24 != 149 && v24 != 288)
          {
            cmpAddSklMenu(v18, v24);
            aOmoideSkill = v18->aOmoideSkill;
          }
          v25 = aOmoideSkill[3];
          if (v25 && v25 != 149 && v25 != 288)
          {
            cmpAddSklMenu(v18, v25);
            aOmoideSkill = v18->aOmoideSkill;
          }
          v26 = aOmoideSkill[4];
          if (v26 && v26 != 149 && v26 != 288)
          {
            cmpAddSklMenu(v18, v26);
            aOmoideSkill = v18->aOmoideSkill;
          }
          v27 = aOmoideSkill[5];
          if (v27 && v27 != 149 && v27 != 288)
          {
            cmpAddSklMenu(v18, v27);
            aOmoideSkill = v18->aOmoideSkill;
          }
          v28 = aOmoideSkill[6];
          if (v28 && v28 != 149 && v28 != 288)
          {
            cmpAddSklMenu(v18, v28);
            aOmoideSkill = v18->aOmoideSkill;
          }
          v29 = aOmoideSkill[7];
          if (v29 && v29 != 149 && v29 != 288)
          {
            cmpAddSklMenu(v18, v29);
          }
        }
      }
      if (++v17 >= SLODWORD(v16->max_length))
      {
        break;
      }
    }
  }
  v30 = GBWK->player->stock_id;
  if (SLODWORD(v30->max_length) >= 1)
  {
    for (i = 0; i < SLODWORD(v30->max_length); ++i)
    {
      v32 = v30[i];
      v33 = v32->devilid;
      if (*((u32 *)*v7 + 56))
      {
        if (DlcDevilSelCheck(v33))
          goto LABEL_99;
      }
      else
      {
        if (DlcDevilSelCheck(v33))
        {
LABEL_99:
          sousaSkill = v32->sousaSkill;
          v36 = sousaSkill[0];
          if (v36 && v36 != 1408)
          {
            cmpAddSklMenu(v32, v36);
            sousaSkill = v32->sousaSkill;
          }
          v37 = sousaSkill[1];
          if (v37 && v37 != 1408)
          {
            cmpAddSklMenu(v32, v37);
          }
        }
      }
    }
  }
  Instance = get_Instance(0);
  ListSet_object_(Instance, sklMenus);
  v40 = get_Instance(0);
  ListSort(v40, 0);
  v41 = get_Instance(0);
  DvlSklList = GetDvlSklList(v41, 0);
  v43 = Allocate(System_Collections_Generic_List_SklMenu_);
  __ctor_48217552(v43, DvlSklList);
  sklMenus = v43;
}

// 0x1e75610
void cmpUpdateSkillListHd(void) {
  s64 i;
  s64 v3;
  s32 monitor;
  char *SousaSklName;
  s32 v13;
  dds3ProcessID_t *v14;
  itfMenuFunc_t v15;
  dds3ProcessID_t *v18;
  char **v19;
  char *LocalizeText;
  dds3ProcessID_t *v22;
  _BOOL8 v23;
  void *v25;
  void *_9__62_0;
  Il2CppObject *v28;
  s32 Index;
  u32 v31;
  dds3ProcessID_t *v33;
  dds3ProcessID_t *v34;
  s32 v35;
  dds3ProcessID_t *v37;

  cmpGetWork();
  for (i = 0; ; ++i)
  {
    if (i >= sklMenus->_size)
      break;
    monitor = _get_Item(sklMenus, i)[1].monitor;
    if ((u32)(monitor - 1423) >= 0xFFFFFFF2)
    {
      v13 = fldChangeFromSKLIDToMskGetNo(monitor);
      SousaSklName = cmpGetSousaSklName(v13, 0);
LABEL_28:
      itfMenuSetFont(g_listPID, i, SousaSklName, "");
      v14 = g_listPID;
      v15 = Allocate(itfMenuFunc_t);
      _ctor(v15, 0, Method_Project_cmpKuda_CallFuncSkill2__, 0);
      itfMenuSetFunc(v14, i, v15);
      goto LABEL_6;
    }
    if (monitor >= 1)
    {
      SousaSklName = sdatSkillName(monitor);
      goto LABEL_28;
    }
    if (monitor)
    {
      v18 = g_listPID;
      v19 = &"CMP_STATUS_L0018";
    }
    else
    {
      v18 = g_listPID;
      v19 = &"CMP_STATUS_L0019";
    }
    LocalizeText = GetLocalizeText(*v19, 1);
    itfMenuSetFont(v18, i, LocalizeText, "");
    itfMenuSetFunc(g_listPID, i, 0);
LABEL_6:
    v3 = (s64)g_skillID + 4 * i;
    *(u32 *)(v3 + 32) = monitor;
  }
  v22 = g_listPID;
  v23 = itfMenuSetFlagMenu(v22, -1, 128, 1);
  cmpChkSkillSelectHd();
  v25 = sklMenus;
  _9__62_0 = __9__62_0;
  if (!_9__62_0)
  {
    v28 = __9;
    _9__62_0 = Allocate(System_Predicate_SklMenu_);
    __ctor(_9__62_0, v28, Method_Project_cmpKuda___c__UpdateSkillListHd_b__62_0__, 0);
    __9__62_0 = _9__62_0;
  }
  Index = _FindIndex(v25, _9__62_0);
  if (Index < 0)
  {
    if (v31)
    {
      v37 = g_listPID;
LABEL_64:
      itfMenuSetFlagMenu(v37, 0, 1, 1);
      v35 = 0;
      v34 = g_listPID;
      goto LABEL_65;
    }
    else
    {
      v37 = g_listPID;
      goto LABEL_64;
    }
    goto LABEL_64;
  }
  if (v31)
  {
    v33 = g_listPID;
  }
  else
  {
    v33 = g_listPID;
  }
  v34 = v33;
  v35 = Index;
LABEL_65:
  itfMenuSetSelectID(v34, v35);
}

// 0x1e75c00
void cmpUpdateSkillList(void) {
  dds3ProcessID_t *CharPID;
  SKLID *v2;
  tagCMP_WORK *Work;
  s32 SelectID;
  __int128 v7;
  s32 v8;
  s64 v9;
  s64 v10;
  s32 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  s64 v17;
  s32 v18;
  dds3ProcessID_t *v20;
  char *v21;
  dds3ProcessID_t *v22;
  itfMenuFunc_t v23;
  char **v28;
  char *LocalizeText;
  dds3ProcessID_t *v31;
  dds3ProcessID_t *v35;
  bool FlagMenu;
  s32 v37;
  dds3ProcessID_t *v39;
  dds3ProcessID_t *v41;
  dds3ProcessID_t *v43;
  dds3ProcessID_t *v45;
  dds3ProcessID_t *v47;
  dds3ProcessID_t *v49;
  dds3ProcessID_t *v51;
  dds3ProcessID_t *v53;
  bool v54;
  dds3ProcessID_t *v56;
  dds3ProcessID_t *v58;
  dds3ProcessID_t *v60;
  dds3ProcessID_t *v62;
  dds3ProcessID_t *v64;
  dds3ProcessID_t *v66;
  dds3ProcessID_t *v68;
  dds3ProcessID_t *v70;
  dds3ProcessID_t *v71;
  s32 v72;
  dds3ProcessID_t *v74;

  CharPID = cmpGetCharPID();
  v2 = NewSpecific(SKLID, 8u);
  Work = cmpGetWork();
  SelectID = itfMenuGetSelectID(CharPID);
  switch (SelectID)
  {
    case 0:
    case 3:
      return;
    case 1:
      SelectID = GBWK->player->stack_p[0];
      goto LABEL_16;
    case 2:
      SelectID = GBWK->player->stack_p[1];
      goto LABEL_16;
    default:
      if (SelectID >= 4)
        SelectID = SelectID + 8 * Work->tabpage - 4;
LABEL_16:
      *(u64 *)&v7 = -1;
      *((u64 *)&v7 + 1) = -1;
      v8 = 0;
      v9 = SelectID;
      v10 = 32;
      *(_OWORD *)&v2[0] = v7;
      *(_OWORD *)&v2[4] = v7;
      break;
  }
  do
  {
    v12 = *(u32 *)((char *)&GBWK->player->stock_id[v9]->haveskill->obj.klass + v10);
    if (v12 && v12 != 149 && v12 != 288)
    {
      if ((tbldata[v12]->type & 0xE000 | 0x1000) == 0x1000)
      {
        v13 = (s64)(char *)v2 + 4 * (s16)v8++;
        *(u32 *)(v13 + 32) = v12;
      }
    }
    v10 += 4;
  }
  while (v10 != 100);
  v14 = 0;
  v15 = &v2[0];
  do
  {
    v18 = *(u32 *)(v15 + 4 * v14);
    if (v18 < 1)
    {
      if (v18)
      {
        v28 = &"CMP_STATUS_L0018";
      }
      else
      {
        v28 = &"CMP_STATUS_L0019";
      }
      LocalizeText = GetLocalizeText(*v28, 1);
      itfMenuSetFont(g_listPID, v14, LocalizeText, "");
      itfMenuSetFunc(g_listPID, v14, 0);
    }
    else
    {
      v20 = g_listPID;
      v21 = sdatSkillName(v18);
      itfMenuSetFont(v20, v14, v21, "");
      v22 = g_listPID;
      v23 = Allocate(itfMenuFunc_t);
      _ctor(v23, 0, Method_Project_cmpKuda_CallFuncSkill2__, 0);
      itfMenuSetFunc(v22, v14, v23);
    }
    v17 = (s64)g_skillID + 4 * v14++;
    *(u32 *)(v17 + 32) = v18;
  }
  while (v14 != 8);
  v31 = g_listPID;
  itfMenuSetFlagMenu(v31, -1, 128, 1);
  cmpChkSkillSelect(GBWK->player->stock_id[v9]);
  v35 = g_listPID;
  FlagMenu = itfMenuGetFlagMenu(v35, 0, 2u);
  v37 = 0;
  if (FlagMenu)
  {
LABEL_135:
    v70 = g_listPID;
    v71 = v70;
    v72 = v37;
    goto LABEL_138;
  }
  v39 = g_listPID;
  v37 = 1;
  if (itfMenuGetFlagMenu(v39, 1, 2u))
    goto LABEL_135;
  v41 = g_listPID;
  v37 = 2;
  if (itfMenuGetFlagMenu(v41, 2, 2u))
    goto LABEL_135;
  v43 = g_listPID;
  v37 = 3;
  if (itfMenuGetFlagMenu(v43, 3, 2u))
    goto LABEL_135;
  v45 = g_listPID;
  v37 = 4;
  if (itfMenuGetFlagMenu(v45, 4, 2u))
    goto LABEL_135;
  v47 = g_listPID;
  v37 = 5;
  if (itfMenuGetFlagMenu(v47, 5, 2u))
    goto LABEL_135;
  v49 = g_listPID;
  v37 = 6;
  if (itfMenuGetFlagMenu(v49, 6, 2u))
    goto LABEL_135;
  v51 = g_listPID;
  v37 = 7;
  if (itfMenuGetFlagMenu(v51, 7, 2u))
    goto LABEL_135;
  v53 = g_listPID;
  v54 = itfMenuGetFlagMenu(v53, 0, 1u);
  v37 = 0;
  if (v54)
    goto LABEL_135;
  v56 = g_listPID;
  v37 = 1;
  if (itfMenuGetFlagMenu(v56, 1, 1u))
    goto LABEL_135;
  v58 = g_listPID;
  v37 = 2;
  if (itfMenuGetFlagMenu(v58, 2, 1u))
    goto LABEL_135;
  v60 = g_listPID;
  v37 = 3;
  if (itfMenuGetFlagMenu(v60, 3, 1u))
    goto LABEL_135;
  v62 = g_listPID;
  v37 = 4;
  if (itfMenuGetFlagMenu(v62, 4, 1u))
    goto LABEL_135;
  v64 = g_listPID;
  v37 = 5;
  if (itfMenuGetFlagMenu(v64, 5, 1u))
    goto LABEL_135;
  v66 = g_listPID;
  v37 = 6;
  if (itfMenuGetFlagMenu(v66, 6, 1u))
    goto LABEL_135;
  v68 = g_listPID;
  v37 = 7;
  if (itfMenuGetFlagMenu(v68, 7, 1u))
    goto LABEL_135;
  v74 = g_listPID;
  itfMenuSetFlagMenu(v74, 0, 1, 1);
  v72 = 0;
  v71 = g_listPID;
LABEL_138:
  itfMenuSetSelectID(v71, v72);
}

// 0x1e766f0
void cmpSetSkillListHd(void) {
  dds3ProcessID_t *ListPID;
  dds3ProcessID_t *v4;
  itfMoverFunc_t v5;
  s32 size;
  s32 v9;
  dds3ProcessID_t *v10;
  itfMenuDrawFunc_t v11;
  dds3ProcessID_t *v13;
  dds3ProcessID_t *v14;

  ListPID = cmpGetListPID();
  g_listPID = ListPID;
  itfMenuClearMenuAll(g_listPID);
  v4 = g_listPID;
  v5 = Allocate(itfMoverFunc_t);
  _ctor(v5, 0, Method_Project_cmpMain_ExSubMenuAnimFunc__, 0);
  itfMoverSetMenu(v4, v5);
  itfMenuSetFlag(g_listPID, 8, 1);
  itfMenuSetFlag(g_listPID, 32, 0);
  itfMenuSetFlag(g_listPID, 256, 0);
  itfMenuSetFlag(g_listPID, 512, 0);
  itfMenuSetFlag(g_listPID, 2048, 0);
  itfMenuSetFlag(g_listPID, 4096, 0);
  itfMenuSetFlag(g_listPID, 0x2000, 0);
  itfMenuSetFlag(g_listPID, 1, 1);
  itfMenuSetSelectID(g_listPID, 0);
  cmpCreateSklMenus();
  size = sklMenus->_size;
  if (size >= 1)
  {
    v9 = 0;
    while (1)
    {
      v13 = g_listPID;
      itfMenuSetRootMenu(v13, v9, "", 0, "");
      v10 = g_listPID;
      v11 = Allocate(itfMenuDrawFunc_t);
      _ctor(v11, 0, Method_Project_cmpKuda_DrawSkillList__, 0);
      itfMenuSetDrawFunc(v10, v9++, v11, 0);
      if (size == v9)
      {
        break;
      }
    }
  }
  cmpUpdateSkillListHd();
  v14 = g_listPID;
  itfMenuSetFlag(v14, 2, 0);
  itfMenuSetDrawParam(g_listPID, 8, 1);
  itfMenuStart(g_listPID);
}

// 0x1e72f30
void cmpSetFilterSkillUse(void) {
  u32 v3;
  sdatUnitWork_t *v5;
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;

  if (g_stockID1 < 0)
  {
LABEL_16:
    v5 = 0;
    goto LABEL_17;
  }
  v3 = (s16)g_stockID1;
  if (v3 > 0x1F)
    goto LABEL_16;
  v5 = GBWK->player->stock_id[v3];
LABEL_17:
  Work = cmpGetWork();
  Work->psUse = v5;
  p_psUse = &Work->psUse;
  *((u32 *)p_psUse + 6) = 1;
  *(_OWORD *)(p_psUse + 1) = xmmword_3D03F00;
}

// 0x1e76ad0
void cmpSetFilterSkillBt(void) {
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;

  cmpSetFilter(0, 0, 262145);
  Work = cmpGetWork();
  Work->psUse = 0;
  p_psUse = &Work->psUse;
  *((u32 *)p_psUse + 6) = 1;
  *(_OWORD *)(p_psUse + 1) = xmmword_3D03F00;
}

// 0x1e76ba0
void cmpSetFilterSummon(void) {
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;

  cmpSetFilter(0, 2, 264192);
  Work = cmpGetWork();
  Work->psUse = 0;
  p_psUse = &Work->psUse;
  *((u32 *)p_psUse + 6) = 264192;
  *(_OWORD *)(p_psUse + 1) = xmmword_3CFE770;
}

// 0x1e76c80
void cmpSetFilterSwap(void) {
  cmpSetFilter(0, 2, 0);
}

// 0x1e76d00
void cmpSetFilterPart(void) {
  cmpSetFilter(0, 2, 0);
}

// 0x1e76d80
void cmpSetFilterOrganize(void) {
  bool v1;
  s32 v3;
  OrganizeStateMachine *v6;
  sdatUnitWork_t *stock_id;
  s32 stockID;
  s32 v10;
  s32 v11;
  tagCMP_WORK *Work;
  sdatUnitWork_t *p_psUse;
  sdatUnitWork_t *v15;

  v1 = datGetStockDevilNums(0) < 1;
  if (v1)
    v3 = 144;
  else
    v3 = 208;
  if (!organizeMachine)
    goto LABEL_15;
  if (organizeMachine->_NowState_k__BackingField != 6)
    goto LABEL_15;
  goto LABEL_14;
  if (organizeMachine->_NowState_k__BackingField == 6)
LABEL_14:
    v3 = v3 & 0x50 | 0x100;
LABEL_15:
  v6 = organizeMachine;
  if (!v6)
  {
LABEL_38:
    v10 = 0;
    v11 = 1;
    goto LABEL_40;
  }
  if (v6->_NowState_k__BackingField != 2)
    goto LABEL_38;
  if ((selStockID1->stockID & 0x80000000) == 0)
  {
    stock_id = GBWK->player->stock_id;
    if ((stock_id[selStockID1->stockID]->flag & 1) == 0)
      v3 &= ~0x40u;
  }
  stockID = selStockID1->stockID;
  if (stockID < 0)
    v3 |= 0x100u;
  if (stockID < 0)
  {
LABEL_49:
    v10 = 7;
    goto LABEL_51;
  }
  v15 = GBWK->player->stock_id;
  if ((v15[selStockID1->stockID]->badstatus & 0x20000) == 0)
    goto LABEL_49;
  v10 = 2;
LABEL_51:
  if (selStockID1->stock == 1)
    v11 = 2049;
  else
    v11 = 1;
LABEL_40:
  Work = cmpGetWork();
  Work->psUse = 0;
  p_psUse = &Work->psUse;
  p_psUse[2] = 0;
  *((u32 *)p_psUse + 6) = v11;
  *((u32 *)p_psUse + 2) = v10;
  *((u32 *)p_psUse + 3) = v3;
}

// 0x1e77110
void SortActiveOnFunc(void) {
  cmpSetHelpFlag(0);
  itfMenuSetFlag(g_listPID, 256, 1);
}

// 0x1e771f0
void SortActiveOffFunc(void) {
  cmpSetHelpFlag(1);
  itfMenuSetFlag(g_listPID, 256, 0);
}

// 0x1e772d0
void SortFunc(void) {
  cmpSetSkillListHd();
  itfMenuSetFlag(g_listPID, 256, 1);
}

// 0x1e77370
void SortSetting(CMP_MENU_ID _id) {
  void *Instance;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;

  if (id == 61441)
  {
    Instance = get_Instance(0);
    SortSetting(Instance, 2, 0);
    v4 = get_Instance(0);
    v5 = Allocate(System_Action);
    _ctor(v5, 0, Method_Project_cmpKuda_SortActiveOnFunc__, 0);
    v6 = Allocate(System_Action);
    _ctor(v6, 0, Method_Project_cmpKuda_SortActiveOffFunc__, 0);
    SetActiveCallBack(v4, v5, v6, 0);
  }
  v7 = get_Instance(0);
  v8 = Allocate(System_Action);
  _ctor(v8, 0, Method_Project_cmpKuda_SortFunc__, 0);
  SetSortCallBack(v7, v8, 0);
}

// 0x1e774e0
void cmpSetupDvlSkl(CMP_MENU_ID a_id) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  itfMenuFunc_t v6;
  itfMenuFunc_t v7;
  _BOOL8 v8;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  g_menuID = a_id;
  v6 = Allocate(itfMenuFunc_t);
  _ctor(v6, 0, Method_Project_cmpKuda_CallFuncSkill__, 0);
  itfMenuSetFunc(CharPID, -1, v6);
  v7 = Allocate(itfMenuFunc_t);
  _ctor(v7, 0, Method_Project_cmpKuda_CallFuncSkill__, 0);
  itfMenuSetFunc(StockPID, -1, v7);
  itfMenuSetFlagMenu(CharPID, -1, 64, 1);
  itfMenuSetFlagMenu(CharPID, -1, 128, 1);
  itfMenuSetFlagMenu(StockPID, -1, 64, 1);
  v8 = itfMenuSetFlagMenu(StockPID, -1, 128, 1);
  cmpSetSkillListHd();
  g_step = 0;
}

// 0x1e776c0
void Setup(CMP_MENU_ID a_id) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  tagCMP_WORK *Work;
  OrganizeStateMachine *v14;
  SelectStockID *v17;
  SelectStockID *v19;
  itfMenuFunc_t v21;
  itfMenuFunc_t v22;
  tagCMP_WORK *v27;
  s32 StockDevilIndex;
  u32 SavePanel;
  s32 v39;
  s32 v40;
  MenuSelectData *SaveSelectID;
  u32 v42;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  Work = cmpGetWork();
  g_menuID = a_id;
  *(u32 *)&g_stockID1 = -1;
  if (a_id == 458753)
  {
    v14 = Allocate(OrganizeStateMachine);
    _ctor(v14, 0);
    organizeMachine = v14;
    Init(organizeMachine, 1, 0);
    v17 = Allocate(SelectStockID);
    _ctor(v17, 0);
    selStockID1 = v17;
    v19 = Allocate(SelectStockID);
    _ctor(v19, 0);
    selStockID2 = v19;
    v21 = Allocate(itfMenuFunc_t);
    _ctor(v21, 0, Method_Project_cmpKuda_CallFuncOraganize__, 0);
    itfMenuSetFunc(CharPID, -1, v21);
    v22 = Allocate(itfMenuFunc_t);
    _ctor(v22, 0, Method_Project_cmpKuda_CallFuncOraganize__, 0);
    itfMenuSetFunc(StockPID, -1, v22);
LABEL_9:
    if (g_menuID == 458753)
      goto LABEL_10;
LABEL_22:
    itfMenuSetFlagMenu(CharPID, -1, 64, 1);
    itfMenuSetFlagMenu(CharPID, -1, 128, 1);
    cmpSetFilter(0, 0, 264193);
    goto LABEL_28;
  }
  {
    goto LABEL_9;
  }
  if (g_menuID != 458753)
    goto LABEL_22;
LABEL_10:
  itfMenuSetFlagMenu(CharPID, -1, 64, 1);
  itfMenuSetFlagMenu(CharPID, -1, 128, 1);
  itfMenuSetFlagMenu(StockPID, -1, 64, 1);
  itfMenuSetFlagMenu(StockPID, -1, 128, 1);
  cmpSetFilterOrganize();
LABEL_28:
  cmpGetWork()->iBadStatus = 0;
  v27 = cmpGetWork();
  cmpMenuFilter(v27);
  itfMenuSetFlag(CharPID, 512, 0);
  if (fldGb->nakamaMode)
  {
    StockDevilIndex = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
    itfMenuSetSelectID(CharPID, StockDevilIndex);
    cmpSetFocusPanel(1);
    goto LABEL_57;
  }
  if (g_menuID != 458753)
  {
    cmpUpdateSelectPosCharPID();
    cmpUpdateSelectNextPosCharPID2();
    cmpUpdateSelectNextPosStockPID();
    g_panel = cmpSetFocusPanel(g_panel);
    goto LABEL_57;
  }
  if (!cmpGetStockPanelActive())
  {
    SavePanel = GetSavePanel(Work->csrSave, 0, 0);
    if (SavePanel <= 1)
      v39 = 1;
    else
      v39 = SavePanel;
    v40 = cmpSetFocusPanel(v39);
    if (v40 != 1)
      CharPID = StockPID;
    g_panel = v40;
    SaveSelectID = GetSaveSelectID(Work->csrSave, 2, 0);
    if (SaveSelectID)
    {
      if (!v42)
      itfMenuSetSelectData(CharPID, SaveSelectID);
    }
    else
    {
      if (!v42)
      itfMenuSetSelectID(CharPID, 0);
    }
  }
LABEL_57:
  g_step = 0;
}

// 0x1e61040
PanelFocus cmpSetFocusPanel(PanelFocus _priority) {
  s32 SelectStockPIDSelMaxCnt;
  s32 SelectCharPIDSelMaxCnt;

  SelectStockPIDSelMaxCnt = cmpGetSelectStockPIDSelMaxCnt(0, 0);
  SelectCharPIDSelMaxCnt = cmpGetSelectCharPIDSelMaxCnt(0);
  if (SelectStockPIDSelMaxCnt != -1)
  {
    if (SelectCharPIDSelMaxCnt != -1)
      goto LABEL_14;
  }
  if (SelectStockPIDSelMaxCnt == -1)
  {
    priority = SelectCharPIDSelMaxCnt != -1;
    goto LABEL_16;
  }
  priority = 2;
  cmpSetStockPanelActive(2, 0);
LABEL_14:
LABEL_16:
  cmpSetStockPanelActive(priority, 0);
  return priority;
}

// 0x1e780e0
s32 cmpGetSelectCharPIDSelMaxCnt(bool _max) {
  dds3ProcessID_t *CharPID;
  s32 v5;

  CharPID = cmpGetCharPID();
  if (max)
  {
    v5 = 32;
    while (1)
    {
      if (itfMenuGetFlagMenu(CharPID, v5, 1u))
        break;
      if (--v5 == -1)
        return -1;
    }
    return v5;
  }
  v5 = 0;
  while (1)
  {
    if (itfMenuGetFlagMenu(CharPID, v5, 1u))
      break;
    if (++v5 == 32)
      return -1;
  }
  return v5;
}

// 0x1e78210
void cmpUpdateSelectPosCharPIDSelMax(bool _max) {
  dds3ProcessID_t *CharPID;
  s32 SelectCharPIDSelMaxCnt;

  CharPID = cmpGetCharPID();
  SelectCharPIDSelMaxCnt = cmpGetSelectCharPIDSelMaxCnt(max);
  itfMenuSetSelectID(CharPID, SelectCharPIDSelMaxCnt);
}

// 0x1e77dd0
s32 cmpGetSelectStockPIDSelMaxCnt(bool _max, bool _dlc) {
  dds3ProcessID_t *StockPID;
  s64 v7;
  s32 v8;
  s32 v10;
  s64 v11;
  s32 devilid;

  StockPID = cmpGetStockPID();
  if (!max)
  {
    if (!dlc)
    {
      v8 = 0;
      while (1)
      {
        if (itfMenuGetFlagMenu(StockPID, v8, 1u))
          break;
        if (++v8 == 32)
          return -1;
      }
      return v8;
    }
    v11 = 0;
    v8 = -1;
    while (1)
    {
      if (itfMenuGetFlagMenu(StockPID, v11, 1u))
      {
        devilid = GBWK->player->stock_id[v11]->devilid;
        if (DlcDevilSelCheck(devilid))
          return v11;
      }
      if (++v11 == 32)
        return v8;
    }
  }
  if (dlc)
  {
    v7 = 36;
    v8 = -1;
    while (1)
    {
      if (!!itfMenuGetFlagMenu(StockPID, v7 - 4, 1u))
      {
        v10 = *(s16 *)(*((u64 *)&GBWK->player->stock_id->obj.klass + v7) + 22);
        if (DlcDevilSelCheck(v10))
          return v7 - 4;
      }
      if (--v7 == 3)
        return v8;
    }
  }
  v8 = 32;
  while (1)
  {
    if (itfMenuGetFlagMenu(StockPID, v8, 1u))
      break;
    if (--v8 == -1)
      return -1;
  }
  return v8;
}

// 0x1e78300
void cmpUpdateSelectPosStockPIDSelMax(bool _max) {
  dds3ProcessID_t *StockPID;
  s32 SelectStockPIDSelMaxCnt;

  StockPID = cmpGetStockPID();
  SelectStockPIDSelMaxCnt = cmpGetSelectStockPIDSelMaxCnt(max, 0);
  itfMenuSetSelectID(StockPID, SelectStockPIDSelMaxCnt);
}

// 0x1e60460
void cmpUpdateSelectPosCharPID(void) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  s32 SelectID;
  s32 v4;
  s32 v7;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  datGetStockDevilNums(0);
  cmpGetWork();
  SelectID = itfMenuGetSelectID(CharPID);
  v4 = itfMenuGetSelectID(StockPID);
  if (cmpGetStockPanelActive() == 2)
  {
    if (!itfMenuGetFlagMenu(StockPID, v4, 1u))
      goto LABEL_22;
    goto LABEL_17;
  }
  if ((u32)SelectID <= 2)
  {
    goto LABEL_21;
  }
LABEL_22:
  while (1)
  {
    ++SelectID;
    if (SelectID >= 4)
      break;
LABEL_21:
    if (itfMenuGetFlagMenu(CharPID, SelectID, 1u))
      goto LABEL_37;
  }
  SelectID = 0;
  if (itfMenuGetFlagMenu(CharPID, 0, 1u))
    goto LABEL_37;
  SelectID = 1;
  if (itfMenuGetFlagMenu(CharPID, 1, 1u))
    goto LABEL_37;
  SelectID = 2;
  if (itfMenuGetFlagMenu(CharPID, 2, 1u))
    goto LABEL_37;
  SelectID = 3;
  if (itfMenuGetFlagMenu(CharPID, 3, 1u))
  {
LABEL_37:
    itfMenuSetSelectID(CharPID, SelectID);
    return;
  }
  if (v4 <= 31)
  {
    while (1)
    {
      if (itfMenuGetFlagMenu(StockPID, v4, 1u))
        break;
      if (++v4 == 32)
        goto LABEL_45;
    }
LABEL_17:
    itfMenuSetSelectID(StockPID, v4);
    return;
  }
LABEL_45:
  v7 = 0;
  while (1)
  {
    if (itfMenuGetFlagMenu(StockPID, v7, 1u))
      break;
    if (++v7 == 32)
      return;
  }
  itfMenuSetSelectID(StockPID, v7);
}

// 0x1e783d0
void cmpUpdateSelectNextPosCharPID(void) {
  ;
}

// 0x1e607b0
void cmpUpdateSelectNextPosCharPID2(void) {
  tagCMP_WORK *Work;
  dds3ProcessID_t *CharPID;
  SMenuType *v3;
  s64 v4;
  s64 v5;
  SMenuType *v6;
  SMenuType *v7;
  s32 iDecideAttrId;
  s32 iBadStatus;
  sdatUnitWork_t *para;
  u64 *v12;
  s32 v13;
  sdatPlayerUnitWork_t *player;
  s64 v16;
  sdatUnitWork_t *v17;
  u64 *v18;
  sdatPlayerUnitWork_t *v20;
  s32 v21;
  sdatUnitWork_t *v22;
  u64 *v23;
  s32 SelectID;
  s32 v26;
  s32 v27;
  s64 v28;
  s64 v29;
  s64 v30;
  sdatUnitWork_t *v31;
  sdatUnitWork_t *psUse;
  s32 v34;
  s32 v35;
  s32 v36;
  s64 v37;
  sdatUnitWork_t *v38;
  s64 v39;
  sdatUnitWork_t *v40;
  s32 v42;
  s32 v43;
  s64 v44;
  sdatUnitWork_t *v45;
  s64 v46;
  sdatUnitWork_t *v47;

  Work = cmpGetWork();
  CharPID = cmpGetCharPID();
  v3 = NewSpecific(SMenuType, 3u);
  v4 = v3;
  if (*(s32 *)((char *)v3 + 24) >= 1)
  {
    v5 = 0;
    v6 = &v3[0];
    do
    {
      v7 = Allocate(SMenuType);
      _ctor(v7, 0);
      if (v7)
        QueryInterface(v7, *(void **)(*(u64 *)v4 + 64));
      v6 = v7;
      ++v5;
      ++v6;
    }
    while (v5 < *(s32 *)(v4 + 24));
  }
  datGetStockDevilNums(0);
  iDecideAttrId = Work->iDecideAttrId;
  iBadStatus = Work->iBadStatus;
  para = GBWK->player->para;
  if (para)
  {
    v12 = *(u64 **)(v4 + 32);
    v12[3] = para;
    v12 += 3;
    *((u32 *)v12 - 2) = 0;
    v13 = 1;
    goto LABEL_17;
  }
  v13 = 0;
LABEL_17:
  player = GBWK->player;
  if ((player->stack_p[0] & 0x80000000) == 0)
  {
    v16 = (u16)player->stack_p[0];
    player = GBWK->player;
    v17 = player->stock_id[v16];
    if (v17)
    {
      v18 = *(u64 **)(v4 + 8 * (u32)v13 + 32);
      v18[3] = v17;
      v18 += 3;
      *((u32 *)v18 - 2) = 1;
      ++v13;
    }
  }
  v20 = GBWK->player;
  v21 = v20->stack_p[1];
  if ((v21 & 0x80000000) == 0)
  {
    v20 = GBWK->player;
    v22 = v20->stock_id[(u16)v21];
    if (v22)
    {
      v23 = *(u64 **)(v4 + 8 * (u32)v13 + 32);
      v23[3] = v22;
      v23 += 3;
      *((u32 *)v23 - 2) = 2;
      ++v13;
    }
  }
  if (v13 < *(u32 *)(v4 + 24))
  {
    SelectID = itfMenuGetSelectID(CharPID);
    if (!v13)
      return;
    if (*(u32 *)(*(u64 *)(v4 + 32) + 16) == SelectID)
    {
      v21 = 0;
    }
    else if (v13 != 1)
    {
      if (*(u32 *)(*(u64 *)(v4 + 40) + 16) == SelectID)
      {
        v21 = 1;
      }
      else if (v13 != 2 && *(u32 *)(*(u64 *)(v4 + 48) + 16) == SelectID)
      {
        v21 = 2;
      }
    }
    if (v21 >= v13)
      v26 = v13;
    else
      v26 = 0;
    v27 = (v21 - v26) & ~((v21 - v26) >> 31);
    if (v27 < *(u32 *)(v4 + 24))
    {
      v28 = v4 + 8 * (u32)v27;
      v30 = *(u64 *)(v28 + 32);
      v29 = v28 + 32;
      v31 = *(sdatUnitWork_t *)(v30 + 24);
      psUse = Work->psUse;
      if (cmpMenuFilterUnit(v31, psUse, iDecideAttrId, iBadStatus))
        goto LABEL_52;
      if (v13 != 1)
      {
        v35 = v27 + 1 >= v13 ? v13 : 0;
        v36 = (v27 + 1 - v35) & ~((v27 + 1 - v35) >> 31);
        if (v36 < *(u32 *)(v4 + 24))
        {
          v37 = v4 + 8 * (u32)v36;
          v38 = Work->psUse;
          v39 = *(u64 *)(v37 + 32);
          v29 = v37 + 32;
          v40 = *(sdatUnitWork_t *)(v39 + 24);
          if (cmpMenuFilterUnit(v40, v38, iDecideAttrId, iBadStatus))
            goto LABEL_52;
          if (v13 != 2)
          {
            v42 = v36 + 1 >= v13 ? v13 : 0;
            v43 = (v36 + 1 - v42) & ~((v36 + 1 - v42) >> 31);
            if (v43 < *(u32 *)(v4 + 24))
            {
              v44 = v4 + 8 * (u32)v43;
              v45 = Work->psUse;
              v46 = *(u64 *)(v44 + 32);
              v29 = v44 + 32;
              v47 = *(sdatUnitWork_t *)(v46 + 24);
              if (cmpMenuFilterUnit(v47, v45, iDecideAttrId, iBadStatus))
              {
LABEL_52:
                v34 = *(u32 *)(*(u64 *)v29 + 16);
                itfMenuSetSelectID(CharPID, v34);
              }
            }
          }
        }
      }
    }
  }
}

// 0x1e60ca0
void cmpUpdateSelectNextPosStockPID(void) {
  dds3ProcessID_t *StockPID;
  SMenuType *v2;
  s32 *v3;
  s64 v4;
  SMenuType *v5;
  SMenuType *v6;
  s32 iBadStatus;
  s64 v10;
  s32 v11;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *v13;
  u64 *v15;
  s32 SelectID;
  s64 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 *v22;
  s32 *v23;
  s64 v24;
  sdatUnitWork_t *v25;
  sdatUnitWork_t *psUse;
  s32 v27;
  dds3ProcessID_t *PID;
  s32 iDecideAttrId;
  tagCMP_WORK *Work;

  Work = cmpGetWork();
  StockPID = cmpGetStockPID();
  v2 = NewSpecific(SMenuType, 0x20u);
  v3 = v2;
  if (*(s32 *)((char *)v2 + 24) >= 1)
  {
    v4 = 0;
    v5 = &v2[0];
    do
    {
      v6 = Allocate(SMenuType);
      _ctor(v6, 0);
      if (v6)
        QueryInterface(v6, *(void **)(*(u64 *)v3 + 64));
      v5 = v6;
      ++v4;
      ++v5;
    }
    while (v4 < v3[6]);
  }
  datGetStockDevilNums(0);
  iBadStatus = Work->iBadStatus;
  iDecideAttrId = Work->iDecideAttrId;
  if (v3[6] - 1 < 1)
  {
    v11 = 0;
  }
  else
  {
    v10 = 0;
    v11 = 0;
    do
    {
      player = GBWK->player;
      if (v10 != player->stack_p[0])
      {
        v13 = player->stock_id[v10];
        if (v10 != GBWK->player->stack_p[1] && v13 != 0)
        {
          v15 = *(u64 **)&v3[2 * v11 + 8];
          v15[3] = v13;
          v15 += 3;
          *((u32 *)v15 - 2) = v10;
          ++v11;
        }
      }
      ++v10;
    }
    while (v10 < v3[6] - 1);
  }
  PID = StockPID;
  SelectID = itfMenuGetSelectID(StockPID);
  if (v11 < 1)
    return;
  v18 = 0;
  while (*(u32 *)(*(u64 *)&v3[2 * v18 + 8] + 16) != SelectID)
  {
    if (v11 == ++v18)
    {
      LODWORD(v18) = 0;
      break;
    }
  }
  v19 = v11;
  while (1)
  {
    if ((s32)v18 >= v11)
      v20 = v11;
    else
      v20 = 0;
    v21 = (v18 - v20) & ~(((s32)v18 - v20) >> 31);
    v22 = &v3[2 * v21];
    v24 = *((u64 *)v22 + 4);
    v23 = v22 + 8;
    v25 = *(sdatUnitWork_t *)(v24 + 24);
    psUse = Work->psUse;
    if (cmpMenuFilterUnit(v25, psUse, iDecideAttrId, iBadStatus))
      break;
    LODWORD(v18) = v21 + 1;
    if (!--v19)
      return;
  }
  v27 = *(u32 *)(*(u64 *)v23 + 16);
  itfMenuSetSelectID(PID, v27);
}

// 0x1e783e0
s32 cmpUpdateFontCharPID(void) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  s32 StockDevilNums;
  s32 stock_max;
  sdatPlayerUnitWork_t *player;
  s32 v6;
  s32 devilid;
  char *LocalizeText;
  sdatPlayerUnitWork_t *v11;
  s32 v12;
  s32 v13;
  char *v14;
  void *v16;
  s64 v17;
  s32 v18;
  s32 v19;
  s64 v20;
  sdatPlayerUnitWork_t *v22;
  s16 *stack_p;
  u64 *v24;
  s64 size;
  s32 *items;
  itfMenuDrawFunc_t v27;
  s32 v29;
  char *v30;
  char *v31;
  itfMenuDrawFunc_t v32;
  itfMenuDrawFunc_t v35;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  StockDevilNums = datGetStockDevilNums(0);
  stock_max = GBWK->player->stock_max;
  cmpGetWork();
  player = GBWK->player;
  v6 = (u16)player->stack_p[0];
  if (v6 == 0xFFFF)
  {
    LocalizeText = GetLocalizeText("CMP_MENU_L0045", 1);
LABEL_15:
    itfMenuSetFont(CharPID, 1, LocalizeText, "");
    goto LABEL_16;
  }
  player = GBWK->player;
  LOWORD(v6) = player->stack_p[0];
  devilid = player->stock_id[(s16)v6]->devilid;
  if (devilid >= 1)
  {
    LocalizeText = sdatDevilName(devilid, 0);
    goto LABEL_15;
  }
LABEL_16:
  v11 = GBWK->player;
  v12 = (u16)v11->stack_p[1];
  if (v12 == 0xFFFF)
  {
    v14 = GetLocalizeText("CMP_MENU_L0045", 1);
    goto LABEL_26;
  }
  v11 = GBWK->player;
  LOWORD(v12) = v11->stack_p[1];
  v13 = v11->stock_id[(s16)v12]->devilid;
  if (v13 < 1)
    goto LABEL_27;
  v14 = sdatDevilName(v13, 0);
LABEL_26:
  itfMenuSetFont(CharPID, 2, v14, "");
LABEL_27:
  v16 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v16);
  if (stock_max < 1)
  {
    v19 = 0;
    goto LABEL_67;
  }
  v17 = 0;
  v18 = 0;
  v19 = 0;
  v20 = StockDevilNums;
  do
  {
    if (v17 >= v20)
    {
      itfMenuSetFont(StockPID, v17, "", "");
      v27 = Allocate(itfMenuDrawFunc_t);
      _ctor(v27, 0, Method_Project_cmpMisc_StockDrawFunc__, 0);
      itfMenuSetDrawFunc(StockPID, v17, v27, 0);
      itfMenuSetFlagMenu(StockPID, v17, 1, 1);
      ++v18;
      if (v17 >= GBWK->player->stock_max)
      {
        itfMenuSetFlagMenu(StockPID, v17, 1, 0);
      }
    }
    else
    {
      v22 = GBWK->player;
      stack_p = v22->stack_p;
      if (v17 == stack_p[0])
      {
LABEL_37:
        v24 = Method_System_Collections_Generic_List_int__Add__;
        size = v16->_size;
        ++v16->_version;
        items = v16->_items;
        if ((u32)size >= LODWORD(items->max_length))
        {
          _AddWithResize(v16, v17, *(const MethodInfo_2D8F530 **)(*(u64 *)(v24[4] + 192) + 112));
        }
        else
        {
          v16->_size = size + 1;
          items[size] = v17;
        }
        goto LABEL_30;
      }
      if (v17 == stack_p[1])
        goto LABEL_37;
      v22 = GBWK->player;
      v29 = v22->stock_id[v17]->devilid;
      v30 = sdatDevilName(v29, 0);
      v31 = sdatDevilName(v29, 1);
      ++v18;
      itfMenuSetFont(StockPID, v17, v30, v31);
      v32 = Allocate(itfMenuDrawFunc_t);
      _ctor(v32, 0, Method_Project_cmpMisc_StockDrawFunc__, 0);
      itfMenuSetDrawFunc(StockPID, v17, v32, 0);
      itfMenuSetFlagMenu(StockPID, v17, 1024, 0);
      v19 = v17;
    }
LABEL_30:
    ++v17;
  }
  while (stock_max != v17);
  if (v18)
  {
    goto LABEL_57;
  }
LABEL_67:
  itfMenuSetRootMenu(StockPID, 999, "", 0, "");
  v35 = Allocate(itfMenuDrawFunc_t);
  _ctor(v35, 0, Method_Project_cmpMisc_StockDrawFunc__, 0);
  itfMenuSetDrawFunc(StockPID, 999, v35, 0);
  itfMenuSetFlagMenu(StockPID, 999, 1, 0);
LABEL_57:
  itfMenuDelMenus(StockPID, v16);
  return v19;
}

// 0x1e78b60
bool cmpChangeChkTabPage(CMP_MENU_ID a_id) {
  dds3ProcessID_t *CharPID;
  s32 v14;

  CharPID = cmpGetCharPID();
  if (itfMenuGetFlag(CharPID, 0x200u))
    return 0;
  if (a_id > 196610)
  {
    if ((u32)a_id <= 0x50001)
    {
      if (a_id != 262145)
      {
        if (a_id != 262146)
        {
          if (a_id == 327681)
          {
            g_step = (u8)g_step;
            if (g_step)
            {
              g_step = (u8)g_step;
              if (g_step != 3)
                return 0;
              if ((g_count & 0x80000000) == 0)
                return 0;
            }
          }
          return 1;
        }
        return 0;
      }
    }
    else
    {
      if (a_id == 327682)
        return 0;
      if (a_id != 393217)
        return a_id != 393218;
    }
    goto LABEL_38;
  }
  if (a_id <= 65537)
  {
    if (a_id != 61442)
    {
      if (a_id == 65537)
      {
        return g_step != 1;
      }
      return 1;
    }
    if (g_step != 1)
      return 0;
    return g_count < 0;
  }
  if (a_id == 131073)
  {
LABEL_38:
    return g_step == 0;
  }
  if (a_id != 196609)
    return a_id != 196610;
  v14 = (u8)g_step;
  if (!g_step)
    return 1;
  v14 = (u8)g_step;
  return v14 == 1;
}

// 0x1e78f90
void cmpChangeTabPage(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  s32 klass_low;
  s16 v11;
  tagCMP_WORK *Work;
  u16 klass;
  s16 v19;
  tagCMP_WORK *v22;
  s16 v26;
  tagCMP_WORK *v29;
  s32 v33;
  tagCMP_WORK *v37;
  u16 v39;
  s16 v41;
  tagCMP_WORK *v45;
  s16 v48;
  tagCMP_WORK *v52;
  u16 v58;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  if (!cmpChangeChkTabPage(SelectID))
    return;
  if (CHECK_TRIG(4107, 1))
  {
    klass_low = LOWORD(ProcessData[6].klass);
    if (SWORD2(ProcessData[6].klass) >= (s16)(klass_low + 1))
      v11 = klass_low + 1;
    else
      v11 = 0;
    LOWORD(ProcessData[6].klass) = v11;
    Work = cmpGetWork();
    cmpMenuFilter(Work);
    klass = ProcessData[6].klass;
    if (LODWORD(ProcessData[9].klass))
      goto LABEL_50;
    if (SWORD2(ProcessData[6].klass) >= (s16)(klass + 1))
      v19 = klass + 1;
    else
      v19 = 0;
    LOWORD(ProcessData[6].klass) = v19;
    v22 = cmpGetWork();
    cmpMenuFilter(v22);
    klass = ProcessData[6].klass;
    if (LODWORD(ProcessData[9].klass))
      goto LABEL_50;
    if (SWORD2(ProcessData[6].klass) >= (s16)(klass + 1))
      v26 = klass + 1;
    else
      v26 = 0;
    LOWORD(ProcessData[6].klass) = v26;
    v29 = cmpGetWork();
    cmpMenuFilter(v29);
    klass = ProcessData[6].klass;
    if (LODWORD(ProcessData[9].klass))
      goto LABEL_50;
    goto LABEL_103;
    if (LODWORD(ProcessData[9].klass))
    {
LABEL_50:
      if (klass_low == klass)
      {
LABEL_52:
        updated = cmpUpdateFontCharPID();
        cmpUpdateSelectPosCharPID();
        goto LABEL_55;
      }
LABEL_51:
      SE(24);
      goto LABEL_52;
    }
LABEL_103:
    if (SWORD2(ProcessData[6].klass) >= (s16)(klass + 1))
      v58 = klass + 1;
    else
      v58 = 0;
    LOWORD(ProcessData[6].klass) = v58;
    if (klass_low == v58)
      goto LABEL_52;
    goto LABEL_51;
  }
LABEL_55:
  if (!CHECK_TRIG(4104, 1))
    return;
  v33 = LOWORD(ProcessData[6].klass);
  LOWORD(ProcessData[6].klass) = v33 - 1;
  if (((v33 - 1) & 0x8000) != 0)
  {
    LOWORD(ProcessData[6].klass) = WORD2(ProcessData[6].klass);
LABEL_58:
    goto LABEL_59;
  }
  else
  {
    goto LABEL_58;
  }
LABEL_59:
  v37 = cmpGetWork();
  cmpMenuFilter(v37);
  v39 = ProcessData[6].klass;
  if (LODWORD(ProcessData[9].klass))
    goto LABEL_94;
  v41 = v39 - 1;
  LOWORD(ProcessData[6].klass) = v41;
  if (v41 < 0)
  {
    LOWORD(ProcessData[6].klass) = WORD2(ProcessData[6].klass);
LABEL_70:
    goto LABEL_71;
  }
  else
  {
    goto LABEL_70;
  }
LABEL_71:
  v45 = cmpGetWork();
  cmpMenuFilter(v45);
  v39 = ProcessData[6].klass;
  if (LODWORD(ProcessData[9].klass))
    goto LABEL_94;
  v48 = v39 - 1;
  LOWORD(ProcessData[6].klass) = v48;
  if (v48 < 0)
  {
    LOWORD(ProcessData[6].klass) = WORD2(ProcessData[6].klass);
LABEL_82:
    goto LABEL_83;
  }
  else
  {
    goto LABEL_82;
  }
LABEL_83:
  v52 = cmpGetWork();
  cmpMenuFilter(v52);
  v39 = ProcessData[6].klass;
  if (!LODWORD(ProcessData[9].klass))
  {
    LOWORD(ProcessData[6].klass) = --v39;
    if ((v39 & 0x8000) != 0)
    {
      v39 = WORD2(ProcessData[6].klass);
      LOWORD(ProcessData[6].klass) = v39;
    }
  }
LABEL_94:
  if (v33 != v39)
    SE(24);
  v56 = cmpUpdateFontCharPID();
  cmpUpdateSelectPosCharPID();
}

// 0x1e796d0
void cmpButtonGuideStatus(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 v6;
  s32 devilid;
  s32 v11;
  s32 ModeSq;
  s32 monitor_high;
  s32 klass;
  sdatPlayerUnitWork_t *player;
  bool v17;
  bool v18;
  bool v19;
  s32 v20;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  if (cmpChgSkillNow())
  {
    v6 = 29;
LABEL_15:
    cmpCmpGuideSet(v6, 0, 90);
    return;
LABEL_14:
    goto LABEL_15;
  }
  devilid = (u16)cmpGetUnit()->devilid;
  if (devilid)
    goto LABEL_19;
  goto LABEL_9003;
  if (v11)
  {
LABEL_19:
    if (cmpGetStatusStep() == 2)
    {
LABEL_32:
      v6 = 37;
      goto LABEL_15;
    }
    if (cmpSetSkillNow())
    {
      v6 = 31;
      goto LABEL_15;
    }
    if (cmpGetModeSq())
    {
      if (cmpGetModeSq() == 2)
      {
        v6 = 30;
        goto LABEL_15;
      }
      else
      {
        if (LODWORD(v4[13].klass) == 1)
          v6 = 28;
        else
          v6 = 26;
        goto LABEL_15;
      }
    }
    else
    {
      if (LODWORD(v4[13].klass) == 1)
        v6 = 24;
      else
        v6 = 23;
      goto LABEL_15;
    }
    goto LABEL_14;
  }
LABEL_9003:
  if (cmpGetStatusStep() == 2)
    goto LABEL_32;
  ModeSq = cmpGetModeSq();
  monitor_high = HIDWORD(v4[21].monitor);
  if (ModeSq)
  {
    if (monitor_high == 1)
    {
      if (cmpSetSkillNow())
      {
        v6 = 34;
        goto LABEL_15;
      }
      else
      {
        v19 = cmpGetModeSq() == 2;
        if (v19)
          v6 = 33;
        else
          v6 = 32;
        goto LABEL_15;
      }
      goto LABEL_14;
    }
    if (!monitor_high)
    {
      if (cmpGetModeSq() == 2)
      {
        klass = _get_Item(v4[23].klass, *((u32 *)v4[19].monitor + 9))[2].klass;
        player = GBWK->player;
        if (klass != player->syougou)
          goto LABEL_90;
        player = GBWK->player;
        if (player->setSyougou)
        {
          v6 = 36;
          goto LABEL_15;
        }
        else
        {
LABEL_90:
          v6 = 35;
          goto LABEL_15;
        }
        goto LABEL_14;
      }
    }
  }
  else
  {
    if (monitor_high == 1)
    {
      v6 = 22;
      goto LABEL_15;
    }
    if (!monitor_high)
    {
      v17 = cmpChkUnopenedMenu(262146);
      v18 = evtBitCheck(2067);
      v19 = !v18;
      if (v17)
        v20 = 18;
      else
        v20 = 20;
      if (v19)
        v6 = v20;
      else
        v6 = v20 + 1;
      goto LABEL_15;
    }
  }
}

// 0x1e79c10
s32 cmpGetPartyPanelSummonSetIndex(s32 _index, bool _ascending) {
  sdatPlayerUnitWork_t *player;
  s16 *stack_p;
  s64 v8;
  s64 v9;
  s32 devilid;
  s32 v11;
  s32 v14;
  s32 v16;

  player = GBWK->player;
  stack_p = player->stack_p;
  v8 = stack_p[0];
  v9 = stack_p[1];
  if (ascending)
  {
    if (index != 2)
    {
      if (index != 1)
        return index;
      if ((u32)v8 != -1)
      {
        player = GBWK->player;
        devilid = player->stock_id[v8]->devilid;
        if (DlcDevilSelCheck(devilid))
          return 1;
      }
    }
    if ((u32)v9 == -1)
      return 3;
    v14 = GBWK->player->stock_id[v9]->devilid;
    if (DlcDevilSelCheck(v14))
      return 2;
    return 3;
  }
  if (index != 1)
  {
    if (index != 2)
      return index;
    if ((u32)v9 != -1)
    {
      player = GBWK->player;
      v11 = player->stock_id[v9]->devilid;
      if (DlcDevilSelCheck(v11))
        return 2;
    }
  }
  if ((u32)v8 != -1)
  {
    v16 = GBWK->player->stock_id[v8]->devilid;
    if (DlcDevilSelCheck(v16))
      return 1;
  }
  return 0;
}

// 0x1e79f00
void cmpCtrlStatus(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  tagCMP_STATUS_WORK *v5;
  s32 StockDevilNums;
  dds3ProcessID_t *CharPID;
  s32 v19;
  s32 ModeSq;
  s32 v26;
  s32 v27;
  s32 v30;
  s32 v33;
  sdatUnitWork_t *stock_id;
  s32 devilid;
  s32 v44;
  s32 v45;
  s32 v49;
  s32 v51;
  sdatUnitWork_t *v55;
  s32 v56;
  s32 SelectStockPIDSelMaxCnt;
  u32 v60;
  s32 SelectCharPIDSelMaxCnt;
  s32 v63;
  s32 v66;
  u32 v69;
  s32 v71;
  s32 PartyPanelSummonSetIndex;
  sdatUnitWork_t *unit;
  sdatUnitWork_t *v75;
  s32 v76;
  s32 v79;
  tagCMP_WORK *Work;
  u32 v85;
  dds3ProcessID_t *StockPID;
  dds3ProcessID_t *v87;
  s32 v88;
  sdatUnitWork_t *v89;

  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  StockDevilNums = datGetStockDevilNums(0);
  cmpGetWork();
  if (g_panel != 2)
  {
    CharPID = cmpGetCharPID();
    goto LABEL_25;
  }
  CharPID = cmpGetStockPID();
LABEL_25:
  cmpGetFlagCallDebug();
  cmpButtonGuideStatus();
  if (tipsProcessCheck())
    return;
  if (v5->unit->devilid && !evtBitCheck(10016))
  {
    tipsTIPSStart(32);
  }
  if ((GetType(0) & 0x8000000) != 0)
    return;
  if (v5->mode != 2)
  {
    v19 = g_panel;
    ModeSq = cmpGetModeSq();
    if (ModeSq != 2)
    {
      if (ModeSq != 1)
      {
        if (ModeSq)
          goto LABEL_216;
        cmpMouseSetSklType();
        if (CHECK_TRIG(41476, 1) || CHECK_REP(41476, 1))
        {
          if (!StockDevilNums || v5->statusGoSword)
            return;
          v26 = g_panel;
          v27 = g_statusID - 1;
          g_statusID = v27;
          if (v26 == 2)
          {
            while (1)
            {
              v33 = g_statusID;
              if (!itfMenuChkExistMenu(CharPID, v33))
                goto LABEL_74;
              stock_id = GBWK->player->stock_id;
              devilid = stock_id[g_statusID]->devilid;
              if (DlcDevilSelCheck(devilid))
              {
LABEL_152:
                if (g_statusID < 0)
                {
                  g_panel = 1;
                  SelectCharPIDSelMaxCnt = cmpGetSelectCharPIDSelMaxCnt(1);
                  g_statusID = SelectCharPIDSelMaxCnt;
                  goto LABEL_214;
                }
                goto LABEL_216;
              }
LABEL_74:
              v30 = g_statusID - 1;
              g_statusID = v30;
              if (v30 < 0)
                goto LABEL_152;
            }
          }
          if ((v27 & 0x80000000) == 0)
            goto LABEL_126;
          goto LABEL_9004;
          if ((g_statusID & 0x80000000) == 0)
          {
LABEL_126:
            goto LABEL_127;
LABEL_211:
            SelectCharPIDSelMaxCnt = g_statusID;
LABEL_214:
            PartyPanelSummonSetIndex = cmpGetPartyPanelSummonSetIndex(SelectCharPIDSelMaxCnt, 0);
            goto LABEL_215;
          }
LABEL_9004:
          SelectStockPIDSelMaxCnt = cmpGetSelectStockPIDSelMaxCnt(1, 1);
          g_statusID = SelectStockPIDSelMaxCnt;
          if (SelectStockPIDSelMaxCnt < 0)
          {
            if (!v60)
            v76 = cmpGetSelectCharPIDSelMaxCnt(1);
            g_statusID = v76;
          }
          else
          {
            g_panel = 2;
          }
LABEL_127:
          if (g_panel != 1)
            goto LABEL_216;
          goto LABEL_211;
        }
        if (CHECK_TRIG(41477, 1) || CHECK_REP(41477, 1))
        {
          if (!StockDevilNums || v5->statusGoSword)
            return;
          v44 = g_panel;
          v45 = g_statusID + 1;
          g_statusID = v45;
          if (v44 != 2)
          {
            v45 = g_statusID;
            v63 = cmpGetPartyPanelSummonSetIndex(v45, 1);
            g_statusID = v63;
            if (v63 <= cmpGetSelectCharPIDSelMaxCnt(1))
              goto LABEL_216;
            v66 = cmpGetSelectStockPIDSelMaxCnt(0, 1);
            g_statusID = v66;
            if ((v66 & 0x80000000) == 0)
            {
              g_panel = 2;
              goto LABEL_216;
            }
            if (!v69)
LABEL_173:
            PartyPanelSummonSetIndex = cmpGetSelectCharPIDSelMaxCnt(0);
LABEL_215:
            g_statusID = PartyPanelSummonSetIndex;
            goto LABEL_216;
          }
          while (1)
          {
            v51 = g_statusID;
            if (!itfMenuChkExistMenu(CharPID, v51))
              goto LABEL_109;
            v55 = GBWK->player->stock_id;
            v56 = v55[g_statusID]->devilid;
            if (DlcDevilSelCheck(v56))
            {
LABEL_167:
              v71 = g_statusID;
              if (v71 <= cmpGetSelectStockPIDSelMaxCnt(1, 1))
                goto LABEL_216;
              g_panel = 1;
              goto LABEL_173;
            }
LABEL_109:
            v49 = g_statusID + 1;
            g_statusID = v49;
            if (v49 > cmpGetSelectStockPIDSelMaxCnt(1, 1))
              goto LABEL_167;
          }
        }
        if (CHECK_TRIG(4104, 1))
        {
LABEL_130:
          cmpSklTypeSub();
          goto LABEL_216;
        }
        if (CHECK_TRIG(4107, 1))
        {
LABEL_148:
          cmpSklTypeAdd();
          goto LABEL_216;
        }
        if (!CHECK_TRIG(45059, 1) || v5->unit->devilid || v5->sklType_r || v5->statusGoSword)
        {
          goto LABEL_189;
        }
        if (cmpChkUnopenedMenu(262146) || CHECK_PRESS(41741, 1))
        {
LABEL_189:
          if (CHECK_TRIG(45315, 1))
          {
            unit = v5->unit;
            if (unit->devilid)
            {
              if (v5->sklType == 1)
              {
LABEL_190:
                cmpCurInitMemSkl(unit, 0);
                cmpSetSkillMode(1);
                v5->modeSq = 1;
LABEL_193:
                SE(0);
                goto LABEL_216;
              }
            }
          }
          if (CHECK_TRIG(45058, 1) && !v5->unit->devilid && !v5->sklType_r && evtBitCheck(2067))
          {
            v75 = v5->unit;
            cmpCurInitMemSkl(v75, 2);
            cmpSetSkillMode(1);
            v5->modeSq = 2;
            goto LABEL_193;
          }
          if (!CHECK_TRIG(45314, 1) || !v5->unit->devilid && !v5->sklType_r)
          {
            goto LABEL_216;
          }
          goto LABEL_204;
        }
        v5->statusGoSword = 1;
        cmpRaidouBackChange(6);
        TitleChange(5);
        cmpSortSetting(262146);
        Setup(262146, 0);
        v88 = 0;
LABEL_240:
        SE(v88);
        return;
      }
      cmpSklCsrMouse(0);
      cmpMouseSetSklType();
      if (CHECK_TRIG(4100, 1) || CHECK_REP(4100, 1))
      {
        cmpSklCsrU();
        goto LABEL_216;
      }
      if (CHECK_TRIG(4101, 1) || CHECK_REP(4101, 1))
      {
        cmpSklCsrD();
        goto LABEL_216;
      }
      if (CHECK_TRIG(4102, 1) || CHECK_REP(4102, 1))
      {
        cmpSklCsrL();
        goto LABEL_216;
      }
      if (CHECK_TRIG(4103, 1) || CHECK_REP(4103, 1))
      {
        cmpSklCsrR();
        goto LABEL_216;
      }
      if (!cmpSetSkillNow())
      {
        if (!cmpChgSkillNow())
        {
          if (CHECK_TRIG(4104, 1))
            goto LABEL_130;
          if (CHECK_TRIG(4107, 1))
            goto LABEL_148;
          if (CHECK_TRIG(4096, 1))
          {
            if (cmpSklSwapBaseCheck(v5))
            {
              cmpChgSkillMode(1);
            }
            goto LABEL_216;
          }
          if (CHECK_TRIG(45571, 1))
          {
            v89 = v5->unit;
            if (!v89->devilid)
            {
              cmpCurInitMemSkl(v89, 0);
              goto LABEL_206;
            }
          }
          if (CHECK_TRIG(45826, 1) && v5->unit->devilid)
          {
            if (v5->sklType != 1)
              return;
LABEL_204:
LABEL_206:
            cmpIncModeSq(0);
            goto LABEL_216;
          }
          if (CHECK_TRIG(45315, 1))
          {
            if (!cmpOpenOmoedeLog())
              goto LABEL_216;
            unit = v5->unit;
            if (!unit->devilid)
              return;
            goto LABEL_190;
          }
          if (!CHECK_TRIG(4097, 1))
            goto LABEL_216;
LABEL_100:
          cmpDecModeSq(0);
        }
      }
LABEL_216:
      if (g_statusID == g_statusID)
      {
        if (g_panel == v19)
          return;
      }
      cmpSetStatus(g_statusID);
      v79 = g_statusID;
      cmpUpdateFontCharPID();
      Work = cmpGetWork();
      cmpMenuFilter(Work);
      if (g_panel == 2)
      {
        if (!v85)
        StockPID = cmpGetStockPID();
      }
      else
      {
        if (!v85)
        StockPID = cmpGetCharPID();
      }
      v87 = StockPID;
      itfMenuSetSelectID(CharPID, v79);
      itfMenuSetSelectID(v87, v79);
      v88 = 24;
      goto LABEL_240;
    }
    if (!CHECK_TRIG(4097, 1))
      goto LABEL_283;
    if (cmpSetSkillNow())
    {
LABEL_283:
      cmpMemSklCurUpdate();
      goto LABEL_216;
    }
    if (!v5->unit->devilid && !v5->sklType_r)
    {
      v5->modeSq = 0;
      goto LABEL_216;
    }
    goto LABEL_100;
  }
}

// 0x1e7af50
bool cmpUpdateSkillHD(void) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  tagCMP_WORK *Work;
  void *v6;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *listPID;
  MenuSelectData *SelectData;
  void *v11;
  bool result;
  tagCMP_WORK *v14;
  MenuSelectData *SaveSelectID;
  MenuSelectData *v16;
  dds3ProcessID_t *v18;
  void *Instance;
  void *v20;
  s32 SelectID;
  s32 v23;
  sdatUnitWork_t *stock_id;
  s32 devilid;
  s32 v29;
  char v34;
  dds3ProcessID_t *v36;
  tagCMP_WORK *v39;
  _BOOL8 v42;
  s32 v45;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  cmpGetMenuPID();
  itfMenuGetSelectID(CharPID);
  Work = cmpGetWork();
  if (g_setSaveCsr)
    goto LABEL_9;
  v14 = cmpGetWork();
  SaveSelectID = GetSaveSelectID(v14->csrSave, 0, 0);
  if (!SaveSelectID)
  {
LABEL_31:
    g_setSaveCsr = 1;
LABEL_10:
    g_step = (u8)g_step;
    if (g_step != 1)
      goto LABEL_11;
    Instance = get_Instance(0);
    ItfSortMenuActive(Instance, 0, 0);
    if (cmpGetStockPanelActive() != 2)
    {
LABEL_66:
      v29 = 2;
      goto LABEL_68;
    }
    SelectID = itfMenuGetSelectID(StockPID);
    if (SelectID < 0)
      goto LABEL_64;
    v23 = SelectID;
    stock_id = GBWK->player->stock_id;
    if (v23 < SLODWORD(stock_id->max_length))
    {
      stock_id = GBWK->player->stock_id;
      devilid = stock_id[v23]->devilid;
LABEL_65:
      if (DlcDevilSelCheck(devilid))
        goto LABEL_66;
      v29 = 3;
LABEL_68:
      cmpCmpGuideSet(v29, 0, 90);
      if (itfMenuGetFlag(CharPID, 8u))
      {
LABEL_74:
        if (g_count < 0)
          return 0;
        if ((char)g_count < 50)
        {
          LOBYTE(g_count) = g_count;
          result = 0;
          v34 = g_count + 1;
LABEL_111:
          g_count = v34;
          return result;
        }
        v45 = itfMenuGetSelectID(g_listPID);
        if (!itfMenuGetFlagMenu(g_listPID, v45, 2u))
        {
          if (cmpGetStockPanelActive() == 1)
            StockPID = CharPID;
          itfMenuSetFlag(StockPID, 8, 0);
        }
        result = 0;
        v34 = -1;
        goto LABEL_111;
      }
      if (itfMenuGetFlag(StockPID, 8u))
        goto LABEL_74;
      v36 = g_listPID;
      itfMenuSetFlagMenu(v36, -1, 8, 0);
      itfMenuSetFlagMenu(g_listPID, -1, 16, 0);
      itfMenuSetFlag(g_listPID, 8, 1);
      itfMenuSetFlag(CharPID, 256, 0);
      itfMenuSetFlag(CharPID, 512, 0);
      itfMenuSetFlag(StockPID, 256, 0);
      itfMenuSetFlag(StockPID, 512, 0);
      itfMenuSetDecideSE(CharPID, -1, -1);
      itfMenuSetDecideSE(StockPID, -1, -1);
      v39 = cmpGetWork();
      v41 = cmpMenuFilter(v39);
      cmpUpdateFontCharPID();
      itfMenuSetFlagMenu(CharPID, -1, 8, 0);
      itfMenuSetFlagMenu(CharPID, -1, 16, 0);
      itfMenuSetFlagMenu(CharPID, -1, 1, 0);
      itfMenuSetFlagMenu(StockPID, -1, 8, 0);
      itfMenuSetFlagMenu(StockPID, -1, 16, 0);
      v42 = itfMenuSetFlagMenu(StockPID, -1, 1, 0);
      cmpCharSelectSetDefault();
      cmpSetSkillListHd();
      g_step = 0;
      return 0;
    }
LABEL_64:
    devilid = 0;
    goto LABEL_65;
  }
  v16 = SaveSelectID;
  v18 = g_listPID;
  itfMenuSetSelectData(v18, v16);
  goto LABEL_31;
LABEL_9:
  goto LABEL_10;
LABEL_11:
  if (g_step)
    return 0;
  v6 = get_Instance(0);
  ItfSortMenuActive(v6, 1, 0);
  v8 = g_listPID;
  if (itfMenuGetWaitType(v8) != 4)
  {
    v20 = get_Instance(0);
    if (GetItfSortSysActive(v20, 0))
      return 0;
    cmpCmpGuideSet(1, 0, 90);
    return 0;
  }
  listPID = Work->listPID;
  SelectData = itfMenuCreateSelectData(listPID);
  SetCsrSave(Work->csrSave, 0, SelectData, 0);
  itfMenuSetDecideSE(CharPID, -1, -1);
  itfMenuSetDecideSE(StockPID, -1, -1);
  v11 = get_Instance(0);
  ItfSortMenuActive(v11, 0, 0);
  *(u16 *)&g_count = 0;
  return 1;
}

// 0x1e7b8d0
bool cmpUpdateSkill(void) {
  return 0;
}

// 0x1e7b8e0
void cmpDrawSkillSet(void) {
  Il2CppClass *klass;
  u32 SklCsr;
  s32 RsvCsr;
  s64 v4;

  klass = _get_Instance()[10].klass;
  SklCsr = cmpGetSklCsr();
  RsvCsr = cmpGetRsvCsr();
  if (RsvCsr == -1)
    v4 = SklCsr;
  else
    v4 = (u32)(RsvCsr + 8);
  (*(klass->_1.image + 63))(klass, v4, 1, 0xFFFFFFFFLL, 1, *((u64 *)klass->_1.image + 64));
}

// 0x1e7b9e0
void cmpBattleSkillSet(sdatUnitWork_t *unit) {
  SKLID *battleskill;
  s64 v7;
  SKLID *v8;
  SKLID *v9;
  SKLID *v10;
  SKLID *v11;
  SKLID *v12;
  SKLID *v13;
  SKLID *v14;
  SKLID *v15;

  battleskill = unit->battleskill;
  v7 = g_statusID - 4;
  v8 = unit->battleskill;
  v9 = GBWK->player->stock_id[v7]->battleskill;
  battleskill[0] = v9[0];
  v10 = v8;
  v8[1] = v9[1];
  v11 = v10;
  v10[2] = v9[2];
  v12 = v11;
  v11[3] = v9[3];
  v13 = v12;
  v12[4] = v9[4];
  v14 = v13;
  v13[5] = v9[5];
  v15 = v14;
  v14[6] = v9[6];
  v9 = GBWK->player->stock_id[v7]->battleskill;
  v15[7] = v9[7];
}

// 0x1e7b9d0
void cmpKuzunohaDirectGuideDraw(void) {
  ;
}

// 0x1e7bcc0
static bool UpdateSkillSet(void) {
  return 0;
}

// 0x1e7bcd0
bool cmpUpdateOrganize(void) {
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  s32 v5;
  s32 v7;
  s32 v9;
  s32 stockID;
  _BOOL4 end;

  CharPID = cmpGetCharPID();
  StockPID = cmpGetStockPID();
  if (selStockID1->stock != 2)
  {
    v7 = GBWK->player->stack_p[0];
    if (selStockID1->stockID == v7)
    {
      v5 = 1;
      goto LABEL_33;
    }
    v9 = GBWK->player->stack_p[1];
    stockID = selStockID1->stockID;
    if (stockID == v9)
    {
      v5 = 2;
      goto LABEL_33;
    }
    stockID = selStockID1->stockID;
    if (stockID == -1)
      v5 = 1;
    else
      v5 = 2;
    goto LABEL_33;
  }
  v5 = selStockID1->stockID;
  CharPID = StockPID;
LABEL_33:
  if (organizeMachine->_NowState_k__BackingField == 4)
  {
    goto LABEL_35;
  }
  g_step = (u8)g_step;
  if (g_step == 1)
  {
    itfMenuSetFlagMenu(CharPID, v5, 2048, 1);
    goto LABEL_35;
  }
  itfMenuSetFlagMenu(CharPID, -1, 2048, 0);
LABEL_35:
  end = organizeMachine->end;
  if (organizeMachine->end)
    return end;
  Update(organizeMachine, 0);
  return end;
}

// 0x1e7c030
bool cmpChkStatusJump(void) {
  s32 StockPanelActive;
  dds3ProcessID_t *CharPID;
  dds3ProcessID_t *StockPID;
  s32 SelectID;
  dds3ProcessID_t *v8;

  StockPanelActive = cmpGetStockPanelActive();
  if (StockPanelActive == 1)
  {
    CharPID = cmpGetCharPID();
    if (itfMenuGetSelectID(CharPID) == 1)
    {
      if (GBWK->player->stack_p[0] == -1)
        return 0;
    }
    v8 = cmpGetCharPID();
    if (itfMenuGetSelectID(v8) == 2)
    {
      return GBWK->player->stack_p[1] != -1;
    }
    return 1;
  }
  StockPID = cmpGetStockPID();
  SelectID = itfMenuGetSelectID(StockPID);
  return SelectID < datGetStockDevilNums(0);
}

// 0x1e7c2a0
bool cmpPartyPanelSelBlankCheck(void) {
  dds3ProcessID_t *CharPID;
  s32 SelectID;

  CharPID = cmpGetCharPID();
  SelectID = itfMenuGetSelectID(CharPID);
  if (SelectID != 2)
  {
    if (SelectID != 1)
      return 1;
    return GBWK->player->stack_p[0] != -1;
  }
  return GBWK->player->stack_p[1] != -1;
}

// 0x1e7c420
bool cmpUpdateStatus(void) {
  return 0;
}

// 0x1e7c430
void cmpPartSetParticle(s32 a_x, s32 a_y, s32 a_w, s32 a_h) {
  s64 i;
  s32 v10;
  s32 v11;
  s32 v12;
  itfMover_t *v14;

  for (i = 32; i != 1056; i += 8)
  {
    v12 = sub_1905740(20, 0);
    v14 = *(itfMover_t *)((char *)&particle->obj.klass + i);
    itfMoverInit(v14);
    v10 = sub_1905740(a_w, 0) + a_x;
    v11 = sub_1905740(a_h, 0);
    itfMoverSetData(*(itfMover_t *)((char *)&particle->obj.klass + i), v10, v11 + a_y, v10, v11 + a_y - v12, -1.0, 0, 0, v12 + 10);
  }
}

// 0x1e7c5b0
void cmpDrawParticle(void) {
  s64 v1;
  itfMover_t *v3;
  itfMover_t *v5;
  itfMover_t *v9;
  f32 a_pPosY;
  f32 a_pPosX;

  v1 = 32;
  a_pPosX = 0.0;
  a_pPosY = 0.0;
  do
  {
    v3 = *(itfMover_t *)((char *)&particle->obj.klass + v1);
    if (itfMoverUpdate(v3) == 1)
    {
      v5 = *(itfMover_t *)((char *)&particle->obj.klass + v1);
      goto LABEL_14;
LABEL_15:
      v9 = *(itfMover_t *)((char *)&particle->obj.klass + v1);
      goto LABEL_9001;
LABEL_14:
      itfMoverGetRatio(v5);
      goto LABEL_15;
LABEL_9001:
      itfMoverGetPosition(v9, &a_pPosX, &a_pPosY);
    }
    v1 += 8;
  }
  while (v1 != 1056);
}

// 0x1e7c780
static bool UpdatePart(void) {
  return 0;
}

// 0x1e7c790
static bool UpdateSwap(void) {
  return 0;
}

// 0x1e7c7a0
static bool UpdateSummon(void) {
  return 0;
}

// 0x1e68d00
void cmpCharSelectSetDefault(void) {
  dds3ProcessID_t *CharPID;
  s32 v3;
  s32 v5;
  dds3ProcessID_t *StockPID;

  CharPID = cmpGetCharPID();
  itfMenuSetFlagMenu(CharPID, -1, 2, 1);
  itfMenuSetFlagMenu(CharPID, -1, 1, 1);
  v3 = (u16)GBWK->player->stack_p[0];
  itfMenuSetFlagMenu(CharPID, 1, 1, v3 != 0xFFFF);
  v5 = (u16)GBWK->player->stack_p[1];
  itfMenuSetFlagMenu(CharPID, 2, 1, v5 != 0xFFFF);
  StockPID = cmpGetStockPID();
  itfMenuSetFlagMenu(StockPID, -1, 2, 1);
  itfMenuSetFlagMenu(StockPID, -1, 1, 1);
}

// 0x1e7c7b0
bool Update(CMP_MENU_ID a_id) {
  s32 v3;
  cmpKudaFunc_t v5;

  v3 = CMP_MENU_ID_ROOT_MASK(a_id);
  v5 = cmpKudaFunc[v3];
  return (v5->invoke_impl)(v5->method_code, v5->method);
}
