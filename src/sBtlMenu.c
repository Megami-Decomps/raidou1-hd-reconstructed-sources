#include "types.h"
#include "BST.h"
#include "DEVIL_STATUS_TYPE.h"
#include "ITM.h"
#include "SBTL_MENU_ID.h"
#include "SKLID.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpitem.h"
#include "cmpkuda.h"
#include "configunity.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "itf.h"
#include "itfMenuDrawFunc_t.h"
#include "itfMenuFunc_t.h"
#include "kernel.h"
#include "lmap.h"
#include "localize.h"
#include "raijindlc.h"
#include "rspecialskill.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcmndmenunew.h"
#include "sbtldraw.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlpanel.h"
#include "sbtlplayer.h"
#include "sbtlplayerex.h"
#include "sbtlscene.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdat.h"
#include "tips.h"

#define SBTL_MENU_MAINPROC_NAME "sbtlmenu_main"
#define SBTL_MENU_DRAWPROC_NAME "sbtlmenu_draw"
#define SBTL_MENU_SPR_FILE "/camp/sub.spr"
#define STOCK_MENU_MAX 8

typedef struct DevilSkillCsr DevilSkillCsr;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct sBtlMenu_t sBtlMenu_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

s8 g_nakamaTab;
bool g_nakamaTabMov;
dds3ProcessID_t *g_mainPID;
sprHandle_t *g_hSpr;
SBTLMENU_BIT_MOON g_bitMoon;
s32 g_equipNo;
s32 g_equipNoOld;
s32 *lastOrangePar;
s32 *param;
sdatUnitWork_t *unitCsr;
sdatUnitWork_t *stockUnitTgt;
DevilSkillCsr *devilSkillcsr;
bool devilInfo;
SBTL_MENU_BEFOR_STEP menuBeforFlag;
DEVIL_STATUS_TYPE skilltype;
SBTL_MENU_INFO_TYPE infotype;
bool bRikamu;
SBTLUNIT_WORK *EnemyUnitTgt;
s32 enemyNowCsr;
s32 enemyNumCount;
bool orderMenuCtrl;
bool shortcutFlag;
SBTLUNIT_WORK *saveUnitTgt;
bool analizeChangeFlag;
static s32 AnalizeCnt;
static bool AnalizeClose;
s32 MenuCnt;
bool MenuShortCutFarst;
bool returnFlag;
bool menu_onoff;
static bool config_onoff;
static bool camp_onoff;
static s32 camp_onoffCnt;
static s32 itemIdSave;
static SBTL_MENU_NAKAMA2 menu_nakama2;
static dds3ProcessID_t *tips_proc;
static dds3ProcessID_t *script_proc;
static dds3Basic_t *bookscene;
void *animChengeTbl;
static char *str_sBtlMenu;
static char *str_sBtlMenuHelp;
itfSprList_t *arr_sBtlMenu_MenuPanel;
itfSprList_t *arr_sBtlMenu_MenuSelect;
itfSprList_t *arr_sBtlMenu_MenuTitle;
itfSprList_t *arr_sBtlMenu_MenuScrollBar;
SBTLMENU_HELP *s_sBtlMenuHelpNo;
SBTLMENU_NODE *s_sBtlMenuNode;
char *s_strRepeat;

static void LoadLocalizeText(void);
static SBTL_MENU_ID GetSelectRootID(void);
static bool RootMenuReturn(bool _start);
static void EnemyKudaDrawEnd(void);
static s32 FuncDecideBullet(void);
static void DrawFuncBullet(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static s32 FuncBullet(void);
static s32 FuncDecideKatana(void);
static void ChkEnableDecideEscape(sBtlMenu_t *wk);
static bool CalcKuzunohaDirect(sBtlMenu_t *wk);
static bool CalcConfig(sBtlMenu_t *wk);
static bool Sord_RSlill_Menu(void);
static void TutorialMenuCtrl(sBtlMenu_t *wk);
static bool EventBattleStopChack(sBtlMenu_t *wk);
static bool ChkEnableBadStatus(SBTLUNIT_WORK *wklock, SBTL_MENU_ID menu_id, BST bstno, bool bSel);
static void SetCommand(sBtlMenu_t *wk);

// 0x1f1ca40
char *sBtlGetMenuStr(s32 index) {
  char *v3;
  char *result;

  v3 = "CMP_STATUS_L0019";
  switch (index)
  {
    case 1:
    case 2:
      if (!sBtlChkTutorialMenu(1))
        goto LABEL_37;
      goto LABEL_41;
    case 3:
      if (sBtlChkTutorialMenu(2))
        goto LABEL_41;
      goto LABEL_37;
    case 4:
      if (sBtlChkTutorialMenu(3))
        goto LABEL_41;
      goto LABEL_37;
    case 6:
      if (sBtlChkTutorialMenu(5))
        goto LABEL_41;
      goto LABEL_37;
    case 7:
      if (sBtlChkTutorialMenu(7))
        goto LABEL_41;
      goto LABEL_37;
    case 8:
      if (sBtlChkTutorialMenu(8))
        goto LABEL_41;
      goto LABEL_37;
    case 17:
      if (evtBitCheck(42))
        goto LABEL_41;
      result = "CMP_MENU_L0043";
      break;
    case 18:
      if (sBtlChkTutorialMenu(6))
        goto LABEL_41;
      goto LABEL_37;
    case 19:
      if (!sBtlChkTutorialMenu(18))
        goto LABEL_37;
      goto LABEL_41;
    case 20:
      if (sBtlChkTutorialMenu(19))
        goto LABEL_41;
LABEL_37:
      result = v3;
      break;
    default:
LABEL_41:
      result = str_sBtlMenu[index];
      break;
  }
  return result;
}

// 0x1f1d150
char *sBtlGetMenuHelpStr(s32 index) {
  char *v3;
  char *result;

  v3 = "";
  switch (index)
  {
    case 1:
      if (!sBtlChkTutorialMenu(1))
        goto LABEL_35;
      goto LABEL_39;
    case 2:
      if (sBtlChkTutorialMenu(2))
        goto LABEL_39;
      goto LABEL_35;
    case 3:
      if (sBtlChkTutorialMenu(3))
        goto LABEL_39;
      goto LABEL_35;
    case 5:
      if (sBtlChkTutorialMenu(5))
        goto LABEL_39;
      goto LABEL_35;
    case 6:
      if (sBtlChkTutorialMenu(7))
        goto LABEL_39;
      goto LABEL_35;
    case 7:
      if (sBtlChkTutorialMenu(8))
        goto LABEL_39;
      goto LABEL_35;
    case 22:
      if (sBtlChkTutorialMenu(6))
        goto LABEL_39;
      goto LABEL_35;
    case 23:
      if (!sBtlChkTutorialMenu(18))
        goto LABEL_35;
      goto LABEL_39;
    case 24:
      if (sBtlChkTutorialMenu(19))
        goto LABEL_39;
LABEL_35:
      result = v3;
      break;
    default:
LABEL_39:
      result = str_sBtlMenuHelp[index];
      break;
  }
  return result;
}

// 0x1f1d330
static void LoadLocalizeText(void) {
  LoadLocalizeText();
}

// 0x1f1d3a0
bool sBtlShortCutStart(s32 com_no, s32 com_smn_idx) {
  Il2CppObject *ProcessData;
  sBtlMenu_t *v9;
  dds3ProcessID_t *menuPID;
  bool FlagMenu;
  void *Instance;
  bool result;
  SBTLUNIT_WORK *PChara;

  ProcessData = dds3GetProcessData(g_mainPID);
  v9 = ProcessData;
  if (com_no != 7)
    goto LABEL_10;
  if (MenuCnt >= 25)
    goto LABEL_10;
  return 0;
LABEL_10:
  v9->type = 0;
  shortcutFlag = 1;
  MenuShortCutFarst = 1;
  SetCommand(v9);
  sBtlChkEnableDecideMenu(v9);
  v9->short_cut_id = com_no;
  menuPID = v9->menuPID;
  FlagMenu = itfMenuGetFlagMenu(menuPID, com_no, 2u);
  if (FlagMenu)
  {
    Instance = get_Instance(0);
    ShortCutGuideSet(Instance, 0);
  }
  result = 0;
  switch (com_no)
  {
    case 1:
      if (!FlagMenu)
        goto LABEL_52;
      sBtlStart(com_smn_idx);
      result = 1;
      break;
    case 2:
      if (!FlagMenu)
        goto LABEL_52;
      sBtlFuncSummon();
      result = 1;
      break;
    case 3:
      if (!FlagMenu)
        goto LABEL_52;
      sBtlFuncReturn();
      result = 1;
      break;
    case 5:
      if (!FlagMenu)
        goto LABEL_52;
      sBtlFuncItem();
      result = 1;
      break;
    case 7:
      if (!FlagMenu)
        goto LABEL_52;
      sBtlFuncAnalyze();
      result = 1;
      break;
    case 8:
      if (FlagMenu)
      {
        sBtlFuncEscape();
        PChara = sBtlGetPChara();
        sBtlSetSummonFunc(PChara);
        wk->mode = 1;
        result = 0;
      }
      else
      {
LABEL_52:
        result = 0;
      }
      break;
    case 17:
      sBtlFuncDitectiveBook();
      result = 1;
      break;
    default:
      return result;
  }
  return result;
}

// 0x1f208a0
static SBTL_MENU_ID GetSelectRootID(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *monitor;
  s32 result;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  monitor = ProcessData[1].monitor;
  result = itfMenuGetSelectID(monitor);
  if (HIDWORD(v4[5].monitor))
    return HIDWORD(v4[5].monitor);
  return result;
}

// 0x1f209e0
bool sBtlGetShortCutFlg(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return HIDWORD(ProcessData[5].monitor) != 0;
  return HIDWORD(ProcessData[5].monitor) != 0;
}

// 0x1f20b00
void sBtlCallEnd(sBtlMenu_t *wk) {
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  s32 type;
  void *Instance;
  s32 v13;
  SBATTLE_WORK *v17;
  u32 status2;
  void *v21;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v24;

  goto LABEL_3;
LABEL_7:
  sBtlDeleteUnitList(tgtList, 0);
  p_tgtList = &wk->tgtList;
  p_tgtList = 0;
  goto LABEL_10;
LABEL_3:
  tgtList = wk->tgtList;
  if (tgtList)
    goto LABEL_7;
LABEL_10:
  type = wk->type;
  if (type == 1)
  {
    wk->bBfrBtlEnd = 1;
    sBtlMenuClose();
    Instance = get_Instance(0);
    BattleMenuClose(Instance, 0, 0);
    goto LABEL_21;
  }
  if (!type)
  {
    sBtlCancelMenuPara();
  }
LABEL_21:
  v13 = wk->flag & 0xFFFFFFCD;
  wk->step = 1;
  wk->flag = v13;
  if (shortcutFlag)
  {
    shortcutFlag = 0;
    MenuShortCutFarst = 0;
  }
  MenuCnt = 0;
  v17 = wk;
  status2 = v17->status2;
  if ((status2 & 2) == 0)
    return;
  v17->status2 = status2 & 0xFFFFFFFD;
  sBtlMenuClose();
  v21 = get_Instance(0);
  BattleMenuClose(v21, 0, 0);
  if (wk->closedOkDisp[0])
  {
    Nakama = sBtlGetNakama(0);
    OkSign(Nakama->hpCallCtrl, 0);
    wk->closedOkDisp[0] = 0;
  }
  if (!wk->closedOkDisp[1])
    return;
  v24 = sBtlGetNakama(1);
  OkSign(v24->hpCallCtrl, 0);
  wk->closedOkDisp[1] = 0;
}

// 0x1f20f30
static bool RootMenuReturn(bool _start) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s32 monitor_high;
  void *Instance;
  dds3ProcessID_t *monitor;
  s32 v13;
  bool v14;
  dds3ProcessID_t *v16;
  dds3ProcessID_t *v17;
  void *v20;

  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  monitor_high = HIDWORD(ProcessData[5].monitor);
  if (monitor_high)
  {
    sBtlMenuClose();
    sBtlCancelMenuPara();
    HIDWORD(v6[5].monitor) = 0;
    return monitor_high == 0;
  }
  Instance = get_Instance(0);
  BattleRootMenu1st(Instance, 0);
  if (HIDWORD(v6[5].klass) != 1)
  {
    if (!start)
      goto LABEL_36;
    if (wk->battlemode == 3)
    {
      monitor = v6[1].monitor;
      v13 = 5;
      goto LABEL_31;
    }
    v14 = evtBitCheck(10007);
    monitor = v6[1].monitor;
    if (!v14)
    {
      v16 = monitor;
      v13 = 1;
      goto LABEL_35;
    }
    v13 = 18;
LABEL_31:
    v16 = monitor;
LABEL_35:
    itfMenuSetInitSelectID(v16, v13);
LABEL_36:
    v17 = v6[1].monitor;
    itfMenuSetDrawParam(v17, 8, 1);
    itfMenuStart(v6[1].monitor);
    v6[6].monitor = 0;
    LODWORD(v6[4].klass) = 2;
    MenuCnt = 0;
    EnemyKudaDrawEnd();
    v20 = get_Instance(0);
    BattleMenuOpen(v20, HIDWORD(v6[5].klass), 0);
    return monitor_high == 0;
  }
  sBtlCallEnd(v6);
  EnemyKudaDrawEnd();
  return monitor_high == 0;
}

// 0x1f21460
bool sBtlIsAnalyzeShortCut(void) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return 0;
  return HIDWORD(ProcessData[5].monitor) == 7;
}

// 0x1f21270
static void EnemyKudaDrawEnd(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  void *devilNameObj;
  void *nameUI;
  void *p_devilNameObj;
  void *p_nameUI;
  void *v11;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) == 0)
      continue;
    devilNameObj = pUnit->devilNameObj;
    if (op_Equality(pUnit->devilNameObj, 0, 0))
      continue;
    nameUI = pUnit->nameUI;
    if (op_Equality(pUnit->nameUI, 0, 0))
      continue;
    p_devilNameObj = &pUnit->devilNameObj;
    p_nameUI = &pUnit->nameUI;
    DrawEnd(p_nameUI, 0);
    v11 = p_devilNameObj;
    if (get_activeSelf(p_devilNameObj, 0))
      SetActive(v11, 0, 0);
    p_nameUI = 0;
    p_devilNameObj = 0;
  }
  EndDispry(wk->bsc, 0);
}

// 0x1f215b0
s32 sBtlFuncSummonList(void) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v4;
  s64 naturalAligment;
  dds3ProcessID_t *v6;
  char **v8;
  s32 stock_num;
  SBTLUNIT_WORK *Nakama;
  u64 v11;
  dds3ProcessID_t *v13;
  s32 v14;
  char *LocalizeText;
  itfMenuFunc_t v16;
  dds3ProcessID_t *v17;
  s32 v18;
  itfMenuDrawFunc_t v19;
  s32 v20;
  s32 v21;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v24;
  s32 v25;
  dds3ProcessID_t *v26;
  s32 v27;
  char *v28;
  itfMenuFunc_t v29;
  dds3ProcessID_t *v30;
  itfMenuDrawFunc_t v31;
  s32 v32;
  dds3ProcessID_t *v33;
  itfMenuDrawFunc_t v34;
  sdatUnitWork_t *v35;
  sdatUnitWork_t *v36;
  s64 status3_param;
  s32 v40;
  bool v42;
  s32 v43;
  dds3ProcessID_t *v44;
  s32 v45;
  char **v46;
  char *v47;
  itfMenuFunc_t v48;
  s64 j;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  dds3ProcessID_t *v52;
  s32 SelectRootID;
  s32 v55;
  void *Instance;
  dds3ProcessID_t *v57;
  void *v58;
  bool ShortCutFlg;
  s32 i;
  s32 devilid;
  s32 v64;
  bool v65;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((sBtlMenu_t **)(ProcessData)[1].next + naturalAligment - 1) != sBtlMenu_t;
  }
  v6 = ProcessData[5];
  itfMenuClearMenuAll(ProcessData[5]);
  v8 = &"new_devil";
  stock_num = wk->stock_num;
  if (!Exists("new_devil"))
  {
    for (i = 0; ; ++i)
    {
      if (i >= wk->stock_num)
        break;
      devilid = sBtlGetStockUnitData(i)->devilid;
      stock_num -= sBtlIsDLCDevil(devilid);
    }
  }
  v64 = stock_num;
  Nakama = sBtlGetNakama(0);
  v11 = (u64)Nakama | (u64)sBtlGetNakama(1);
  v13 = v4[5];
  v65 = v11 != 0;
  v14 = wk->stock_num;
  LocalizeText = GetLocalizeText("SBTL_MENU_L0004", 1);
  v16 = Allocate(itfMenuFunc_t);
  _ctor(v16, 0, Method_Project_sBtlMenu_FuncReturn__, 0);
  itfMenuSetRootMenu(v13, v14 + 1, LocalizeText, v16, "");
  v17 = v4[5];
  v18 = wk->stock_num;
  v19 = Allocate(itfMenuDrawFunc_t);
  _ctor(v19, 0, Method_Project_sBtlMenu_DrawFuncSummon__, 0);
  itfMenuSetDrawFunc(v17, v18 + 1, v19, 0);
  itfMenuSetFlagMenu(v4[5], wk->stock_num + 1, 2, v65);
  v20 = 0;
  v21 = -1;
  while (1)
  {
    if (v20 >= wk->stock_num)
      break;
    StockUnitData = sBtlGetStockUnitData(v20);
    if (!StockUnitData)
      goto LABEL_26;
    v24 = StockUnitData;
    if (wk->smnCtrl->bNoOk)
      goto LABEL_26;
    if (sBtlCheckSummonUnit_Exist(0) != 2)
    {
      if (v20 == wk->summonindex[0])
        goto LABEL_49;
    }
    if (sBtlCheckSummonUnit_Exist(1) == 2)
      goto LABEL_26;
    if (v20 != wk->summonindex[1])
      goto LABEL_26;
LABEL_49:
    if (!Exists("new_devil"))
    {
      v25 = v24->devilid;
      if (sBtlIsDLCDevil(v25))
        goto LABEL_26;
    }
    v26 = v4[5];
    v27 = v24->devilid;
    if (v21 == -1)
      v21 = v20;
    v28 = sdatDevilName(v27, 0);
    v29 = Allocate(itfMenuFunc_t);
    _ctor(v29, 0, Method_Project_sBtlMenu_FuncSummon2__, 0);
    itfMenuSetRootMenu(v26, v20, v28, v29, "");
    v30 = v4[5];
    v31 = Allocate(itfMenuDrawFunc_t);
    _ctor(v31, 0, Method_Project_sBtlMenu_DrawFuncSummon__, 0);
    itfMenuSetDrawFunc(v30, v20, v31, 0);
    itfMenuSetFlagMenu(v4[5], v20, 2, 0);
LABEL_26:
    ++v20;
  }
  v32 = 0;
LABEL_67:
  if (v32 < wk->stock_num)
  {
    v35 = sBtlGetStockUnitData(v32);
    if (!v35)
      goto LABEL_66;
    v36 = v35;
    if (wk->smnCtrl->bNoOk)
      goto LABEL_102;
    if (sBtlCheckSummonUnit_Exist(0) != 2)
    {
      if (v32 == wk->summonindex[0])
        goto LABEL_66;
    }
    if (sBtlCheckSummonUnit_Exist(1) != 2)
    {
      if (v32 == wk->summonindex[1])
        goto LABEL_66;
    }
    if (!sBtlCheckSelect(v36))
      goto LABEL_102;
    if ((wk->status3 & 0x80000) == 0)
      goto LABEL_118;
    goto LABEL_9000;
    if ((wk->status3 & 0x80000) == 0)
    {
LABEL_118:
      for (j = 0; ; ++j)
      {
        UnitMng = wk->UnitMng;
        if (j >= UnitMng->number)
        {
          v42 = 1;
          goto LABEL_103;
        }
        pUnit = UnitMng->pUnitL[j]->pUnit;
        if (!pUnit)
          continue;
        if ((pUnit->side & 1) != 0 && pUnit->para->devilid == v36->devilid)
        {
          v42 = CheckLiveTarget(pUnit);
LABEL_103:
          if (Exists(*v8))
            goto LABEL_111;
          v43 = v36->devilid;
          if (!sBtlIsDLCDevil(v43))
          {
LABEL_111:
            v44 = v4[5];
            v45 = v36->devilid;
            v46 = v8;
            if (v21 == -1)
              v21 = v32;
            v47 = sdatDevilName(v45, 0);
            v48 = Allocate(itfMenuFunc_t);
            _ctor(v48, 0, Method_Project_sBtlMenu_FuncSummon2__, 0);
            itfMenuSetRootMenu(v44, v32, v47, v48, "");
            v33 = v4[5];
            v34 = Allocate(itfMenuDrawFunc_t);
            _ctor(v34, 0, Method_Project_sBtlMenu_DrawFuncSummon__, 0);
            itfMenuSetDrawFunc(v33, v32, v34, 0);
            itfMenuSetFlagMenu(v4[5], v32, 2, v42);
            v8 = v46;
          }
LABEL_66:
          ++v32;
          goto LABEL_67;
        }
      }
    }
LABEL_9000:
    status3_param = wk->status3_param;
    v40 = v36->devilid;
    if (status3_param == sBtlGetDevilData(v40, -1)->kuda_id)
    {
LABEL_102:
      v42 = 0;
      goto LABEL_103;
    }
    goto LABEL_118;
  }
  v52 = v4[5];
  itfMenuSetInitSelectID(v52, v21);
  itfMenuSetFlag(v4[5], 1024, 0);
  itfMenuStart(v4[5]);
  SelectRootID = GetSelectRootID();
  if (v64 < 8)
    v55 = v64 + 1;
  else
    v55 = 8;
  Instance = get_Instance(0);
  v57 = v4[5];
  v58 = Instance;
  ShortCutFlg = sBtlGetShortCutFlg();
  OpenCommonMenu(v58, v57, 0, SelectRootID, 0, v55, ShortCutFlg, 0);
  MenuCnt = 0;
  *((u32 *)v4 + 16) = 9;
  return 1;
}

// 0x1f22330
s32 sBtlGetTabLimitCharStock(s32 *a_pmin, s32 *a_pmax) {
  s32 StockDevilNums;
  s32 v7;

  goto LABEL_3;
LABEL_9:
  v7 = 0;
  goto LABEL_11;
LABEL_3:
  StockDevilNums = datGetStockDevilNums(0);
  if (StockDevilNums == 8)
    goto LABEL_9;
  if (StockDevilNums == 24 || StockDevilNums == 16)
    v7 = ((u32)StockDevilNums >> 3) - 1;
  else
    v7 = (s16)(StockDevilNums / 8);
LABEL_11:
  *a_pmin = 0;
  *a_pmax = v7;
  return 0;
}

// 0x1f22410
s32 sBtlGetTabLimitCharItem(s32 *a_pmin, s32 *a_pmax) {
  s32 v6;

  if (sBtlGetStockUnitData(16))
  {
    *a_pmin = 0;
    *a_pmax = 3;
    return 0;
  }
  else
  {
    if (sBtlGetStockUnitData(8))
      v6 = 2;
    else
      v6 = 1;
    *a_pmin = 0;
    *a_pmax = v6;
    return 0;
  }
}

// 0x1f22480
sBtlMenu_t *sBtlGetWork(void) {
  sBtlMenu_t *result;

  if (!ProcessCheck())
    return 0;
  result = (sBtlMenu_t *)dds3GetProcessData(g_mainPID);
  if (!result)
    return result;
  return result;
}

// 0x1f22730
void sBtlDrawTargetCursorNakama(s32 a_nakamaId) {
  SBTLUNIT_WORK *Nakama;

  if ((u32)a_nakamaId <= 1)
  {
    Nakama = sBtlGetNakama(a_nakamaId);
    sBtlResetColor_Select();
    if (!Nakama)
      return;
    sBtlSelectTargetCursorSub(Nakama, 0);
    sBtlSetColor_Select(Nakama, 0x80808080);
  }
}

// 0x1f22830
void sBtlDrawTargetCursorEnemy(void) {
  SBTLUNIT_WORK *v2;
  SBTLUNIT_WORK *v3;

  sBtlSelectTargetCursor(0);
  sBtlResetColor_Select();
  v2 = sBtlSearchUnit_ID(wk->tgtList, wk->tgt_csr);
  if (v2)
  {
    v3 = v2;
    sBtlSetColor_Select(v3, 0x80808080);
  }
}

// 0x1f22960
void sBtlDrawTargetCharList(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v11;
  s64 naturalAligment;
  dds3ProcessID_t *v13;
  SBTLUNIT_WORK *pUnit;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  v11 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((sBtlMenu_t **)(ProcessData)[1].next + naturalAligment - 1) != sBtlMenu_t;
  }
  v13 = ProcessData[5];
  if (itfMenuGetSelectID(ProcessData[5]) != a_id)
    return;
  pUnit = wk->UnitMng->pUnitL[a_id]->pUnit;
  sBtlSelectTargetCursorSub(pUnit, 0);
  sBtlResetColor_Select();
  sBtlSetColor_Select(pUnit, 0x80808080);
  Instance = get_Instance(0);
  CommonMenuDraw(Instance, 0, v11[5], 0, 0, 0);
}

// 0x1f22bc0
s32 sBtlReturnAL(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s32 SelectID;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  u32 v13;
  SUMMON_CTRL *smnCtrl;
  SBTLUNIT_WORK *PChara;
  void *Instance;
  void *v19;
  void *v21;
  void *v22;
  void *v24;
  void *v25;
  void *v26;
  void *v27;
  void *v29;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[3].klass;
  SelectID = itfMenuGetSelectID(klass);
  sBtlSetMenuPara(8, wk->summonindex[SelectID], -1, -1, -1, SelectID);
  tgtList = wk->tgtList;
  if (tgtList)
  {
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
    goto LABEL_15;
  }
LABEL_15:
  v13 = HIDWORD(v4[4].klass) & 0xFFFFFFCD;
  LODWORD(v4[4].klass) = 1;
  HIDWORD(v4[4].klass) = v13;
  wk->ctrlSmnIdx = SelectID;
  smnCtrl = wk->smnCtrl;
  smnCtrl->bNoOk = 1;
  smnCtrl->aprId = SelectID;
  smnCtrl->io = 0;
  if (HIDWORD(v4[5].klass) == 1)
  {
    PChara = sBtlGetPChara();
    sBtlSetSummonFunc(PChara);
    HIDWORD(v4[4].klass) |= 0x10u;
    Instance = get_Instance(0);
    CloseCommonNakamaMenu(Instance, 3, 0, 0);
    v19 = get_Instance(0);
    MenuClose(v19->devil_info2, 0);
    devilInfo = 0;
    v21 = get_Instance(0);
    CharIconCtr(v21, 0, 0);
    v22 = get_Instance(0);
    BattleMenuOpen(v22, HIDWORD(v4[5].klass), 0);
    return 1;
  }
  else
  {
    sBtlMenuClose();
    v24 = get_Instance(0);
    BattleMenuClose(v24, 0, 0);
    v25 = get_Instance(0);
    CloseHelpWin(v25, 0);
    v26 = get_Instance(0);
    CloseCommonNakamaMenu(v26, 3, 0, 0);
    v27 = get_Instance(0);
    MenuClose(v27->devil_info2, 0);
    devilInfo = 0;
    v29 = get_Instance(0);
    CharIconCtr(v29, 0, 0);
    return 1;
  }
}

// 0x1f23000
s32 sBtlFuncSummonExe(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s32 SelectID;
  s32 v8;
  u32 v10;
  sdatUnitWork_t *StockUnitData;
  s32 v12;
  SUMMON_CTRL *smnCtrl;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  SBTLUNIT_WORK *PChara;
  void *Instance;
  void *v23;
  s32 SelectRootID;
  void *v25;
  void *v26;
  void *v27;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[3].klass;
  SelectID = itfMenuGetSelectID(klass);
  v8 = itfMenuGetSelectID(v4[2].monitor);
  v10 = HIDWORD(v4[4].klass) & 0xFFFFFFCD;
  LODWORD(v4[4].klass) = 1;
  HIDWORD(v4[4].klass) = v10;
  if ((wk->status3 & 0x40000) == 0)
    goto LABEL_33;
  StockUnitData = sBtlGetStockUnitData(v8);
  sBtlGetAutoSkill_ID(StockUnitData, 0);
  sBtlGetAutoSkill_ID(StockUnitData, 1);
  sBtlGetAutoSkill_ID(StockUnitData, 2);
  sBtlGetAutoSkill_ID(StockUnitData, 3);
  sBtlGetAutoSkill_ID(StockUnitData, 4);
  sBtlGetAutoSkill_ID(StockUnitData, 5);
  sBtlGetAutoSkill_ID(StockUnitData, 6);
  sBtlGetAutoSkill_ID(StockUnitData, 7);
  v12 = sub_1905740(2, 0);
  if (v12)
  {
LABEL_33:
    wk->macter_csr = v8;
    sBtlSetMenuPara(1, v8, -1, -1, -1, SelectID);
    sBtlInitDevil();
    smnCtrl = wk->smnCtrl;
    wk->ctrlSmnIdx = SelectID;
    smnCtrl->aprId = SelectID;
    smnCtrl->io = 1;
    tgtList = wk->tgtList;
    smnCtrl->bNoOk = 1;
    smnCtrl->stkId = v8;
    if (!tgtList)
    {
LABEL_41:
      if (HIDWORD(v4[5].klass) == 1)
      {
        PChara = sBtlGetPChara();
        sBtlSetSummonFunc(PChara);
        LODWORD(v4[4].klass) = 16;
        goto LABEL_50;
      }
      sBtlMenuClose();
      Instance = get_Instance(0);
      BattleMenuClose(Instance, 0, 0);
      v23 = get_Instance(0);
      CloseHelpWin(v23, 0);
LABEL_50:
      SelectRootID = GetSelectRootID();
      v25 = get_Instance(0);
      CloseCommonMenu(v25, SelectRootID, 0, 0);
      v26 = get_Instance(0);
      MenuClose(v26->devil_info2, 0);
      devilInfo = 0;
      v27 = get_Instance(0);
      CharIconCtr(v27, 0, 0);
      return 1;
    }
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
    goto LABEL_41;
  }
  StockUnitData->badst_cnt3 = 0;
  *(u64 *)&StockUnitData->badstatus = 0x100000;
  wk->kaiwa_gstat = 0;
  LODWORD(v4[4].klass) = 15;
  return 1;
}

// 0x1f235a0
void sBtlMakeNakamaList(itfMenuFunc_t pFunc, itfMenuDrawFunc_t pDrawFunc, SBTL_MENU_NAKAMA2 pMenu_nakama2) {
  Il2CppObject *ProcessData;
  Il2CppObject *v10;
  u64 *v12;
  dds3ProcessID_t *klass;
  s64 v14;
  s64 v15;
  SBTLUNIT_WORK *v16;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v18;
  u64 *v19;
  dds3ProcessID_t *v20;
  s32 devilid;
  char *v22;
  itfMenuFunc_t v23;
  bool v24;
  dds3ProcessID_t *v25;
  char *LocalizeText;
  dds3ProcessID_t *v29;
  bool v30;
  dds3ProcessID_t *v32;
  char *v33;
  dds3ProcessID_t *v34;
  dds3ProcessID_t *v36;
  s32 SelectRootID;
  void *Instance;
  dds3ProcessID_t *v40;
  void *v41;
  bool ShortCutFlg;
  dds3ProcessID_t *v43;
  u64 *v45;
  s32 v46;
  s64 v47;

  ProcessData = dds3GetProcessData(g_mainPID);
  v10 = ProcessData;
  v46 = pMenu_nakama2;
  v12 = NewSpecific(SBTLUNIT_WORK, 2u);
  klass = v10[3].klass;
  itfMenuClearMenuAll(klass);
  v14 = 0;
  if (evtBitCheck(10002))
    v15 = 2;
  else
    v15 = 1;
  v47 = v15;
  v16 = (v12 + 4);
  v45 = v12 + 4;
  do
  {
    Nakama = sBtlGetNakama(v14);
    if (Nakama)
    {
      v18 = Nakama;
      v19 = v12;
      QueryInterface(Nakama, *(void **)(*v12 + 64));
      v16 = v18;
      v20 = v10[3].klass;
      devilid = v18->para->devilid;
      v22 = sdatDevilName(devilid, 0);
      itfMenuSetRootMenu(v20, v14, v22, pFunc, "");
      v12 = v19;
      if (!CheckLiveTarget(v18))
        goto LABEL_34;
      if (v18->byctCnt <= 0 && (v18->para->badstatus & 0x335DF) == 0)
      {
        v30 = v18->actaiwk->mode != 10;
        v32 = v10[3].klass;
LABEL_36:
        itfMenuSetFlagMenu(v32, v14, 2, v30);
        v29 = v10[3].klass;
        goto LABEL_14;
      }
LABEL_34:
      v30 = 0;
      v32 = v10[3].klass;
      goto LABEL_36;
    }
    v16 = 0;
    v23 = Allocate(itfMenuFunc_t);
    _ctor(v23, 0, Method_Project_sBtlMenu_FuncSummonExe__, 0);
    v24 = op_Equality(pFunc, v23, 0);
    v25 = v10[3].klass;
    if (v24)
    {
      LocalizeText = GetLocalizeText("SBTL_MENU_L0020", 1);
      itfMenuSetRootMenu(v25, v14, LocalizeText, pFunc, "");
      v29 = v10[3].klass;
    }
    else
    {
      v33 = GetLocalizeText("SBTL_MENU_L0020", 1);
      itfMenuSetRootMenu(v25, v14, v33, 0, "");
      v29 = v10[3].klass;
    }
LABEL_14:
    itfMenuSetDrawFunc(v29, v14++, pDrawFunc, 0);
    ++v16;
  }
  while (v47 != v14);
  if (v46 != 1)
  {
    v36 = v10[3].klass;
    goto LABEL_55;
  }
  if (*v45 && !v12[5])
  {
    v43 = v10[3].klass;
    itfMenuSetInitSelectID(v43, 1);
    v36 = v10[3].klass;
    goto LABEL_55;
  }
  v34 = v10[3].klass;
  itfMenuSetInitSelectID(v34, 0);
  v36 = v10[3].klass;
LABEL_55:
  itfMenuStart(v36);
  SelectRootID = GetSelectRootID();
  Instance = get_Instance(0);
  v40 = v10[3].klass;
  v41 = Instance;
  ShortCutFlg = sBtlGetShortCutFlg();
  OpenCommonNakamaMenu(v41, v40, 0, SelectRootID, 0, v47, ShortCutFlg, 0);
}

// 0x1f20f20
void sBtlSetFadeOutMoon(void) {
  ;
}

// 0x1f23be0
SBTLMENU_ENABLETALK sBtlCheckEnableTalk(SBTLUNIT_WORK *unit) {
  s32 result;
  sdatUnitWork_t *para;
  u32 BadStatus;

  if (!unit)
    return 0;
  if ((unit->flg & 1) != 0)
    return 2;
  if (unit->talkBreakDownFlg)
    return 4;
  para = unit->para;
  BadStatus = sBtlGetBadStatus(para);
  result = 3;
  if (BadStatus <= 0x16 && ((1 << BadStatus) & 0x400C00) != 0)
  {
    if (sBtlCheckTalkSelectTarget(unit))
      return 1;
    else
      return 2;
  }
  return result;
}

// 0x1f23cf0
void sBtlSetMenuImage(dds3ProcessID_t *PID) {
  sprHandle_t *hPanelSpr3;

  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  itfMenuLinkSprite(PID, hPanelSpr3);
  itfMenuSetSpriteData(PID, 0, 0, 0, 0, 0, 23, 24, 0, arr_sBtlMenu_MenuTitle);
  itfMenuSetSpriteData(PID, 1, 322, 160, 128, 23, 17, 3, 0, arr_sBtlMenu_MenuPanel);
  itfMenuSetSpriteData(PID, 2, 322, 160, 128, 23, 17, 3, 0, arr_sBtlMenu_MenuSelect);
  itfMenuSetSpriteData(PID, 3, 322, 160, 3, 164, 172, 11, 0, arr_sBtlMenu_MenuScrollBar);
  itfMenuSetImageColor(PID, 3, 0xC8u, 0xB4u, 0x50u, 0x80u);
}

// 0x1f23ee0
dds3ProcessID_t *sBtlInitMenuPID(u8 a_max) {
  dds3ProcessID_t *v4;
  s32 v6;
  s32 v7;

  v4 = itfMenuProcessStart();
  if (!v4)
    return v4;
  v6 = a_max;
  if (a_max)
  {
    v7 = 0;
    do
    {
      itfMenuSetRootMenu(v4, v7++, "", 0, "");
    }
    while (v6 != v7);
  }
  itfMenuSetMoveAppear(v4, 3);
  itfMenuSetMoveDisappear(v4, 3);
  itfMenuSetFlag(v4, 2, 0);
  itfMenuSetFlag(v4, 16, 0);
  itfMenuUpdateLink(v4);
  return v4;
}

// 0x1f24060
void sBtlDrawFuncTalk(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  Il2CppObject *ProcessData;
  Il2CppObject *v12;
  dds3ProcessID_t *monitor;
  SBTLUNIT_LISTWORK *tgtList;
  s32 tgt_csr;
  SBTLUNIT_WORK *v19;
  s32 v21;
  s32 v22;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  if (!wk->tgtList)
    return;
  monitor = v12[2].monitor;
  if (itfMenuGetSelectID(v12[2].monitor) != a_id)
    return;
  wk->tgt_csr = a_id;
  sBtlDrawTargetCursorEnemy();
  tgtList = wk->tgtList;
  tgt_csr = wk->tgt_csr;
  v19 = sBtlSearchUnit_ID(tgtList, tgt_csr);
  v21 = sBtlCheckEnableTalk(v19);
  if ((u32)(v21 - 2) < 2)
  {
    v22 = 15;
  }
  else
  {
    if (v21 != 4)
    {
      if (v21 == 1)
      {
        sBtlHelp(3, 17, alphaRate);
      }
      goto LABEL_37;
    }
    v22 = 14;
  }
  sBtlHelpCantUse(5, v22, alphaRate);
LABEL_37:
  Instance = get_Instance(0);
  CommonMenuDraw(Instance, 0, v12[2].monitor, 0, 0, 0);
}

// 0x1f243b0
void sBtlDrawAnalyzePlayer(s32 a_id, u8 a_alphaRate) {
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *Nakama;
  s32 PlayerID;
  sdatUnitWork_t *v8;
  SBTLUNIT_WORK *v9;

  if (a_id <= 0)
  {
    PlayerID = sBtlGetPlayerID();
    para = sBtlGetPlayerUnit(PlayerID)->para;
    Nakama = sBtlGetNakama(0);
    if (!Nakama)
      goto LABEL_10;
LABEL_9:
    v8 = Nakama->para;
    if (v8->devilid == para->devilid)
      goto LABEL_13;
    goto LABEL_10;
  }
  para = sBtlGetStockUnitData(a_id - 1);
  Nakama = sBtlGetNakama(0);
  if (Nakama)
    goto LABEL_9;
LABEL_10:
  v9 = sBtlGetNakama(1);
  if (!v9 || (v8 = v9->para, v8->devilid != para->devilid))
    v8 = para;
LABEL_13:
  sBtlAnalyzePlayer(v8, a_alphaRate);
}

// 0x1f244e0
void sBtlDrawFuncPartyDat(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  Il2CppObject *v12;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  void *Instance;
  void *v19;
  void *v22;
  dds3ProcessID_t *v23;
  u8 Alpha;
  sdatUnitWork_t *StockUnitData;
  SBTLUNIT_WORK *Nakama;
  sdatUnitWork_t *v29;
  SBTLUNIT_WORK *v30;
  SBTLUNIT_WORK *v31;
  sdatUnitWork_t *v32;
  void *v35;
  s32 v37;
  s32 PlayerID;
  void *v40;
  void *v42;
  s32 v43;
  SBTLUNIT_WORK *PlayerUnit;
  sdatUnitWork_t *para;
  void *v46;
  void *devil_info2;
  s32 v51;
  char **v53;
  s32 v54;
  void *v56;
  void *v58;
  void *v59;
  void *v60;
  dds3ProcessID_t *v61;
  void *v63;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  monitor = ProcessData[2].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  if (itfMenuGetSelectID(v12[2].monitor) == a_id)
  {
    if (wk->stock_num + 1 == a_id)
    {
      if (devilInfo)
      {
        Instance = get_Instance(0);
        MenuClose(Instance->devil_info2, 0);
        v19 = get_Instance(0);
        CharIconCtr(v19, 0, 0);
        infotype = 0;
        devilInfo = 0;
        v22 = get_Instance(0);
        GuideSet(v22, "BTL001", 0, 90, 0);
      }
      v23 = v12[2].monitor;
      Alpha = itfMenuImgGetAlpha(v23, 2);
LABEL_108:
      sBtlHelp(3, 15, Alpha);
      goto LABEL_106;
    }
    if (SelectID != a_id)
    {
      if (!g_nakamaTab)
      {
        if (SelectID > 0 && !sBtlGetStockUnitData(SelectID - 1))
          goto LABEL_57;
        PlayerID = sBtlGetPlayerID();
        if (!sBtlGetPlayerUnit(PlayerID))
        {
LABEL_57:
          if (devilInfo)
          {
            v40 = get_Instance(0);
            MenuClose(v40->devil_info2, 0);
            devilInfo = 0;
            v42 = get_Instance(0);
            CharIconCtr(v42, 0, 0);
            HIDWORD(v12[6].klass) = 2;
          }
        }
      }
LABEL_101:
      v61 = v12[2].monitor;
      Alpha = itfMenuImgGetAlpha(v61, 2);
      if (!wk->modeSq)
        goto LABEL_108;
LABEL_106:
      v63 = get_Instance(0);
      CommonMenuDraw(v63, 0, v12[2].monitor, 0, 0, 0);
      return;
    }
    sBtlDrawAnalyzePlayer(a_id, a_alphaRate);
    if (a_id <= 0)
    {
      v43 = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(v43);
      para = PlayerUnit->para;
      sBtlSelectTargetCursorSub(PlayerUnit, 0);
      v46 = get_Instance(0);
      GuideSet(v46, "BTL001", 0, 90, 0);
      datCalcNowParam(para, GBWK->player->swordno, 0);
      datDvlParaUpdate(0);
      devil_info2 = get_Instance(0)->devil_info2;
      SetDevilStatus(devil_info2, para, 0, 0, GBWK->player, 0, 0);
      v37 = 1;
      infotype = 1;
      goto LABEL_80;
    }
    else
    {
      StockUnitData = sBtlGetStockUnitData(a_id - 1);
      datCalcNowParam(StockUnitData, 0, 0);
      Nakama = sBtlGetNakama(0);
      if (Nakama && (v29 = Nakama->para, v30 = Nakama, v29->devilid == StockUnitData->devilid) && v29->uniq_code == StockUnitData->uniq_code || (v31 = sBtlGetNakama(1), (v30 = v31) != 0) && (v32 = v31->para, v32->devilid == StockUnitData->devilid) && v32->uniq_code == StockUnitData->uniq_code)
      {
        sBtlSelectTargetCursorSub(v30, 0);
      }
      unitCsr = StockUnitData;
      v35 = get_Instance(0);
      Status(v35, v30->para, HIDWORD(v12[6].klass), devilSkillcsr->statusSkillCsr, 0, 0, 0);
      v37 = 2;
      infotype = 2;
    }
LABEL_80:
    if (devilInfo)
    {
      if (a_id <= 0)
      {
        v51 = 0;
        v53 = &"BTL001";
      }
      else
      {
        v51 = animChengeTbl[SHIDWORD(v12[6].klass)];
        if (devilSkillcsr->statusSkillCsr)
          goto LABEL_98;
        v53 = &"BTL007";
      }
      v59 = get_Instance(0);
      GuideSet(v59, *v53, 0, 90, 0);
LABEL_98:
      v60 = get_Instance(0);
      MenuChange(v60->devil_info2, v51, 0);
      goto LABEL_101;
    }
    if (a_id < 1)
    {
      v54 = 0;
      goto LABEL_92;
    }
    else
    {
      v54 = animChengeTbl[SHIDWORD(v12[6].klass)];
      goto LABEL_92;
    }
LABEL_92:
    v56 = get_Instance(0);
    MenuOpne(v56->devil_info2, v37, v54, 0);
    devilInfo = 1;
    v58 = get_Instance(0);
    CharIconCtr(v58, 1, 0);
    goto LABEL_101;
  }
}

// 0x1f24e20
void sBtlDrawFuncStockDat(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  Il2CppObject *v12;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  sdatUnitWork_t *v18;
  void *Instance;
  s32 v23;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  sdatUnitWork_t *para;
  void *devil_info2;
  s32 v32;
  void *v33;
  s32 v34;
  void *v35;
  void *v37;
  dds3ProcessID_t *v39;
  u8 Alpha;
  void *v42;
  void *v43;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  monitor = ProcessData[3].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  if (itfMenuGetSelectID(v12[3].monitor) == a_id)
  {
    if (SelectID != a_id)
      goto LABEL_54;
    sBtlDrawAnalyzePlayer(a_id, a_alphaRate);
    if (a_id > 0)
    {
      v18 = stockUnitTgt[a_id - 1];
      datCalcNowParam(v18, 0, 0);
      unitCsr = v18;
      Instance = get_Instance(0);
      Status(Instance, v18, HIDWORD(v12[6].klass), devilSkillcsr->statusSkillCsr, 0, 0, 0);
      v23 = 2;
      infotype = 2;
      goto LABEL_41;
    }
    PlayerID = sBtlGetPlayerID();
    PlayerUnit = sBtlGetPlayerUnit(PlayerID);
    para = PlayerUnit->para;
    sBtlSelectTargetCursorSub(PlayerUnit, 0);
    datCalcNowParam(para, GBWK->player->swordno, 0);
    datDvlParaUpdate(0);
    devil_info2 = get_Instance(0)->devil_info2;
    SetDevilStatus(devil_info2, para, 0, 0, GBWK->player, 0, 0);
    v23 = 1;
    infotype = 1;
LABEL_41:
    if (devilInfo)
    {
      if (a_id < 1)
      {
        v32 = 0;
      }
      else
      {
        v32 = animChengeTbl[SHIDWORD(v12[6].klass)];
        if (!devilSkillcsr->statusSkillCsr)
        {
          v33 = get_Instance(0);
          GuideSet(v33, "BTL007", 0, 90, 0);
        }
      }
      v43 = get_Instance(0);
      MenuChange(v43->devil_info2, v32, 0);
      v39 = v12[2].monitor;
LABEL_56:
      Alpha = itfMenuImgGetAlpha(v39, 2);
      if (wk->modeSq)
      {
LABEL_59:
        v42 = get_Instance(0);
        CommonStockMenuDraw(v42, 0, v12[3].monitor, 0, 0, 0);
        return;
      }
      sBtlHelp(3, 15, Alpha);
      goto LABEL_59;
    }
    v34 = a_id > 0;
    v35 = get_Instance(0);
    MenuOpne(v35->devil_info2, v23, v34, 0);
    devilInfo = 1;
    v37 = get_Instance(0);
    CharIconCtr(v37, 1, 0);
LABEL_54:
    v39 = v12[2].monitor;
    goto LABEL_56;
  }
}

// 0x1f25470
void sBtlDrawFuncSummon(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  Il2CppObject *v12;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *Nakama;
  sdatUnitWork_t *v19;
  SBTLUNIT_WORK *v20;
  SBTLUNIT_WORK *v21;
  void *v23;
  void *v25;
  void *v28;
  void *Instance;
  s32 v30;
  void *v31;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  monitor = ProcessData[2].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  StockUnitData = sBtlGetStockUnitData(a_id);
  if (StockUnitData)
  {
    if (SelectID != a_id)
    {
LABEL_46:
      Instance = get_Instance(0);
      CommonMenuDraw(Instance, 0, v12[2].monitor, 0, 1, 0);
      return;
    }
    para = StockUnitData;
    Nakama = sBtlGetNakama(0);
    if (Nakama && (v19 = Nakama->para, v20 = Nakama, v19->devilid == para->devilid) && v19->uniq_code == para->uniq_code || (v21 = sBtlGetNakama(1)) != 0 && (v19 = v21->para, v20 = v21, v19->devilid == para->devilid) && v19->uniq_code == para->uniq_code)
    {
      sBtlAnalyzePlayer(v19, a_alphaRate);
      para = v20->para;
    }
    else
    {
      sBtlAnalyzePlayer(para, a_alphaRate);
    }
    if (devilInfo)
    {
LABEL_40:
      unitCsr = para;
      v28 = get_Instance(0);
      Status(v28, para, HIDWORD(v12[6].klass), devilSkillcsr->statusSkillCsr, 0, 0, 0);
      if (LODWORD(v12[4].klass) != 17)
      {
        sBtlHelp(3, 12, a_alphaRate);
      }
      goto LABEL_46;
    }
    else
    {
      v30 = animChengeTbl[SHIDWORD(v12[6].klass)];
      v31 = get_Instance(0);
      MenuOpne(v31->devil_info2, 2, v30, 0);
      devilInfo = 1;
      goto LABEL_40;
    }
    goto LABEL_40;
  }
  if (SelectID != a_id)
    return;
  if (!devilInfo)
    return;
  v23 = get_Instance(0);
  MenuClose(v23->devil_info2, 0);
  devilInfo = 0;
  sBtlHelp(3, 3, a_alphaRate);
  v25 = get_Instance(0);
  GuideSet(v25, "BTL021", 0, 90, 0);
}

// 0x1f25920
s32 sBtlFuncStart(void) {
  Il2CppObject *ProcessData;
  sBtlMenu_t *v5;

  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  if (wk->member_num < 1)
    goto LABEL_16;
  if (wk->battlemode == 3)
    goto LABEL_16;
  if (!sBtlStartBattle1st())
    goto LABEL_33;
  v5->step = 14;
  return 1;
LABEL_16:
  if (wk->encountno != 43)
    goto LABEL_33;
  if (IsSceanStop())
    goto LABEL_33;
  StopBattle();
LABEL_33:
  sBtlCallEnd(v5);
  return 1;
}

// 0x1f25bc0
bool sBtlSkillChkUseUnit(sdatUnitWork_t *unit, SKLID a_skillID) {
  if ((tbldata[a_skillID]->useflg & 2) == 0)
    return 1;
  return cmpChkEnableUseSkill(unit, unit, a_skillID);
}

// 0x1f25cd0
s32 sBtlFuncMeirei(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  sBtlStart(-1);
  MenuCnt = 0;
  LODWORD(ProcessData[4].klass) = 8;
  return 1;
}

// 0x1f25e30
void sBtlDrawFuncSummon2(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v12;
  s64 naturalAligment;
  dds3ProcessID_t *v14;
  SBTLUNIT_WORK *Nakama;
  dds3ProcessID_t *v20;
  bool FlagMenu;
  u32 v22;
  void *Instance;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *v30;
  s32 i;
  void *v32;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *para;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((sBtlMenu_t **)(ProcessData)[1].next + naturalAligment - 1) != sBtlMenu_t;
  }
  v14 = ProcessData[6];
  if (itfMenuGetSelectID(ProcessData[6]) != a_id)
    return;
  Nakama = sBtlGetNakama(a_id);
  sBtlDrawTargetCursorNakama(a_id);
  if (*((u32 *)v12 + 16) == 17)
  {
    if (Nakama)
      goto LABEL_12;
LABEL_31:
    if (devilInfo)
    {
      Instance = get_Instance(0);
      MenuClose(Instance->devil_info2, 0);
      devilInfo = 0;
      v25 = get_Instance(0);
      CharIconCtr(v25, 0, 0);
      *((u32 *)v12 + 25) = 2;
    }
    v26 = get_Instance(0);
    GuideSet(v26, "BTL015", 0, 90, 0);
    goto LABEL_42;
  }
  v20 = v12[6];
  FlagMenu = itfMenuGetFlagMenu(v20, a_id, 2u);
  if (FlagMenu)
  {
    if (!v22)
    sBtlHelp(3, 13, alphaRate);
    if (!Nakama)
      goto LABEL_31;
  }
  else
  {
    if (!v22)
    sBtlHelpCantUse(3, 19, alphaRate);
    if (!Nakama)
      goto LABEL_31;
  }
LABEL_12:
  if (!devilInfo)
  {
    v28 = get_Instance(0);
    MenuOpne(v28->devil_info2, 2, 1, 0);
    devilInfo = 1;
    v30 = get_Instance(0);
    CharIconCtr(v30, 1, 0);
  }
  for (i = 0; i != 32; ++i)
  {
    StockUnitData = sBtlGetStockUnitData(i);
    if (StockUnitData)
    {
      para = Nakama->para;
      if (para->devilid == StockUnitData->devilid && para->uniq_code == StockUnitData->uniq_code)
      {
        unitCsr = para;
        v32 = get_Instance(0);
        Status(v32, Nakama->para, *((u32 *)v12 + 25), devilSkillcsr->statusSkillCsr, 0, 0, 0);
      }
    }
  }
LABEL_42:
  v27 = get_Instance(0);
  CommonMenuNakamaDraw(v27, 0, v12[6], 1, 1, 0);
}

// 0x1f26300
s32 sBtlFuncSummon2(void) {
  Il2CppObject *ProcessData;
  itfMenuFunc_t v2;
  itfMenuDrawFunc_t v3;

  ProcessData = dds3GetProcessData(g_mainPID);
  v2 = Allocate(itfMenuFunc_t);
  _ctor(v2, 0, Method_Project_sBtlMenu_FuncSummonExe__, 0);
  v3 = Allocate(itfMenuDrawFunc_t);
  _ctor(v3, 0, Method_Project_sBtlMenu_DrawFuncSummon2__, 0);
  sBtlMakeNakamaList(v2, v3, 1);
  MenuCnt = 0;
  LODWORD(ProcessData[4].klass) = 7;
  return 1;
}

// 0x1f1f1e0
s32 sBtlFuncSummon(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *monitor;
  void *Instance;
  void *v10;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  g_nakamaTab = 0;
  monitor = ProcessData[2].monitor;
  itfMenuSetDrawParam(monitor, 8, 1);
  sBtlFuncSummonList();
  Instance = get_Instance(0);
  MenuOpne(Instance->devil_info2, 2, 2, 0);
  devilInfo = 1;
  returnFlag = 0;
  v10 = get_Instance(0);
  CharIconCtr(v10, 1, 0);
  HIDWORD(v4[6].klass) = 0;
  return 1;
}

// 0x1f264a0
void sBtlDrawFuncReturn(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v12;
  s64 naturalAligment;
  dds3ProcessID_t *v14;
  SBTLUNIT_WORK *Nakama;
  dds3ProcessID_t *v20;
  bool FlagMenu;
  u32 v22;
  void *Instance;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *v30;
  s32 i;
  void *v32;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *para;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((sBtlMenu_t **)(ProcessData)[1].next + naturalAligment - 1) != sBtlMenu_t;
  }
  v14 = ProcessData[6];
  if (itfMenuGetSelectID(ProcessData[6]) != a_id)
    return;
  Nakama = sBtlGetNakama(a_id);
  sBtlDrawTargetCursorNakama(a_id);
  if (*((u32 *)v12 + 16) == 17)
  {
    if (Nakama)
      goto LABEL_12;
LABEL_31:
    if (devilInfo)
    {
      Instance = get_Instance(0);
      MenuClose(Instance->devil_info2, 0);
      devilInfo = 0;
      v25 = get_Instance(0);
      CharIconCtr(v25, 0, 0);
      *((u32 *)v12 + 25) = 2;
    }
    v26 = get_Instance(0);
    GuideSet(v26, "BTL015", 0, 90, 0);
    goto LABEL_42;
  }
  v20 = v12[6];
  FlagMenu = itfMenuGetFlagMenu(v20, a_id, 2u);
  if (FlagMenu)
  {
    if (!v22)
    sBtlHelp(3, 14, alphaRate);
    if (!Nakama)
      goto LABEL_31;
  }
  else
  {
    if (!v22)
    sBtlHelpCantUse(3, 19, alphaRate);
    if (!Nakama)
      goto LABEL_31;
  }
LABEL_12:
  if (!devilInfo)
  {
    v28 = get_Instance(0);
    MenuOpne(v28->devil_info2, 2, 1, 0);
    devilInfo = 1;
    v30 = get_Instance(0);
    CharIconCtr(v30, 1, 0);
  }
  for (i = 0; i != 32; ++i)
  {
    StockUnitData = sBtlGetStockUnitData(i);
    if (StockUnitData)
    {
      para = Nakama->para;
      if (para->devilid == StockUnitData->devilid && para->uniq_code == StockUnitData->uniq_code)
      {
        unitCsr = para;
        v32 = get_Instance(0);
        Status(v32, Nakama->para, *((u32 *)v12 + 25), devilSkillcsr->statusSkillCsr, 0, 0, 0);
      }
    }
  }
LABEL_42:
  v27 = get_Instance(0);
  CommonMenuNakamaDraw(v27, 0, v12[6], 1, 1, 0);
}

// 0x1f1f3b0
s32 sBtlFuncReturn(void) {
  Il2CppObject *ProcessData;
  itfMenuFunc_t v2;
  itfMenuDrawFunc_t v3;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  v2 = Allocate(itfMenuFunc_t);
  _ctor(v2, 0, Method_Project_sBtlMenu_ReturnAL__, 0);
  v3 = Allocate(itfMenuDrawFunc_t);
  _ctor(v3, 0, Method_Project_sBtlMenu_DrawFuncReturn__, 0);
  sBtlMakeNakamaList(v2, v3, 2);
  Instance = get_Instance(0);
  CharIconCtr(Instance, 1, 0);
  MenuCnt = 0;
  returnFlag = 1;
  LODWORD(ProcessData[4].klass) = 7;
  HIDWORD(ProcessData[6].klass) = 2;
  return 1;
}

// 0x1f26970
static s32 FuncDecideBullet(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s32 SelectID;
  u32 v10;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  wk->macter_csr = SelectID;
  sBtlSetMenuPara(10, -1, -1, wk->bulletList->data[SelectID]->id, -1, 0);
  v10 = HIDWORD(v4[4].klass) & 0xFFFFFFEF;
  LODWORD(v4[4].klass) = 1;
  HIDWORD(v4[4].klass) = v10;
  sBtlSetMode(2);
  return 1;
}

// 0x1f26b60
static void DrawFuncBullet(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  s32 v20;
  s64 v21;
  s32 v22;
  s32 v23;
  s32 id;
  Il2CppObject *v25;
  char *v26;
  char *v27;
  s32 SelectID;
  u32 v29;
  s32 data;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  v29 = a_fontColor;
  v20 = a_id;
  v21 = a_id;
  v22 = a_x + 130;
  v23 = a_x + 105;
  id = wk->bulletList->data[v21]->id;
  itfIconDrawBullet(v23, a_y + 2, a_z, a_alphaRate, id, 109);
  itfDrawMiscSpriteAlpha(v22, a_y + 12, a_z, a_alphaRate, wk->panelwk->hPanelSpr3, 5, 109);
  data = wk->bulletList->data[v21]->num;
  v25 = Box(s32, &data);
  v26 = Format("{0,3:d}", v25, 0);
  v27 = Concat_54766928(0, v26, 0);
  itfDrawMiscFont(3, v22, a_y + 7, a_z, 0, v29, a_alphaRate, v27);
  if (SelectID == v20)
  {
    sBtlHelp(2, id, a_alphaRate);
  }
}

// 0x1f26e80
static s32 FuncBullet(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s64 i;
  dds3ProcessID_t *v8;
  itfMenuDrawFunc_t v9;
  SBTLITEM_LISTWORK *bulletList;
  dds3ProcessID_t *v12;
  s32 id;
  char *v14;
  itfMenuFunc_t v15;
  dds3ProcessID_t *v16;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[2].klass;
  itfMenuClearMenuAll(klass);
  for (i = 0; ; ++i)
  {
    bulletList = wk->bulletList;
    if (i >= bulletList->num)
      break;
    bulletList = wk->bulletList;
    v12 = v4[2].klass;
    id = bulletList->data[i]->id;
    v14 = sdatItemName(id);
    v15 = Allocate(itfMenuFunc_t);
    _ctor(v15, 0, Method_Project_sBtlMenu_FuncDecideBullet__, 0);
    itfMenuSetRootMenu(v12, i, v14, v15, "");
    v8 = v4[2].klass;
    v9 = Allocate(itfMenuDrawFunc_t);
    _ctor(v9, 0, Method_Project_sBtlMenu_DrawFuncBullet__, 0);
    itfMenuSetDrawFunc(v8, i, v9, 0);
    itfMenuSetDecideSE(v4[2].klass, i, 19);
  }
  v16 = v4[2].klass;
  itfMenuSetDrawParam(v16, 8, 1);
  itfMenuStart(v4[2].klass);
  LODWORD(v4[4].klass) = 3;
  return 1;
}

// 0x1f271d0
s32 sBtlFuncDecideItemTarget(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  SBTLITEM_TBL *Itemtbl;
  SBTLSKILLP_TBL *Skilltbl;
  dds3ProcessID_t *v12;
  bool v13;
  s32 v17;
  s32 v18;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  u32 v23;
  void *Instance;
  s32 SelectRootID;
  void *v28;
  void *v29;
  void *v30;
  void *v31;
  SBTLITEM_TBL *p_item_keep;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  monitor = ProcessData[2].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  Itemtbl = sBtlGetItemtbl(wk->panelwk->data[0]->itemid);
  Skilltbl = sBtlGetSkilltbl(Itemtbl->sklid);
  if (itfMenuGetSelectID(v4[2].monitor) == wk->stock_num + 1)
  {
    sBtlFuncDecideItemStock();
    sBtlPlaySE(0x1001Fu);
    return 1;
  }
  v12 = v4[2].monitor;
  v13 = !itfMenuGetFlagMenu(v12, SelectID, 8u);
  if (!v13)
    SelectID = -1;
  if ((Skilltbl->attr & 0x800) != 0)
  {
    v17 = -1;
    v18 = SelectID;
  }
  else
  {
    v17 = SelectID;
    v18 = -1;
  }
  sBtlSetMenuPara(9, v17, -1, wk->panelwk->data[0]->itemid, v18, 0);
  tgtList = wk->tgtList;
  if (tgtList)
  {
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
    goto LABEL_35;
  }
LABEL_35:
  v23 = HIDWORD(v4[4].klass) & 0xFFFFFFCD;
  LODWORD(v4[4].klass) = 1;
  HIDWORD(v4[4].klass) = v23;
  Instance = get_Instance(0);
  BattleMenuClose(Instance, 0, 0);
  sBtlMenuClose();
  SelectRootID = GetSelectRootID();
  v28 = get_Instance(0);
  CloseCommonMenu(v28, SelectRootID, 0, 0);
  v29 = get_Instance(0);
  CloseHelpWin(v29, 0);
  v30 = get_Instance(0);
  MenuClose(v30->devil_info2, 0);
  devilInfo = 0;
  v31 = get_Instance(0);
  CharIconCtr(v31, 0, 0);
  p_item_keep = &wk->item_keep;
  p_item_keep = 0;
  return 1;
}

// 0x1f28420
s32 sBtlFuncDecideItemTargetStock(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  SBTLITEM_TBL *Itemtbl;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v11;
  s32 v12;
  s64 v13;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v16;
  s32 v21;
  s32 v22;
  u32 v23;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  void *Instance;
  s32 SelectRootID;
  void *v31;
  void *v32;
  void *v33;
  void *v34;
  SBTLITEM_TBL *p_item_keep;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  monitor = ProcessData[3].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  Itemtbl = sBtlGetItemtbl(wk->panelwk->data[0]->itemid);
  Skilltbl = sBtlGetSkilltbl(Itemtbl->sklid);
  if (itfMenuGetFlagMenu(v4[3].monitor, SelectID, 8u))
  {
    v11 = -1;
  }
  else
  {
    v12 = SelectID - 1;
    v11 = 1;
    v13 = v12;
    while (1)
    {
      if (v11 - 1 >= wk->stock_num)
        break;
      StockUnitData = sBtlGetStockUnitData(v11 - 1);
      if (StockUnitData)
      {
        v16 = StockUnitData;
        if (stockUnitTgt[v13] == v16)
          goto LABEL_26;
      }
      ++v11;
    }
    v11 = -1;
  }
LABEL_26:
  if ((Skilltbl->attr & 0x800) != 0)
  {
    v21 = -1;
    v22 = v11;
  }
  else
  {
    v21 = v11;
    v22 = -1;
  }
  sBtlSetMenuPara(9, v21, -1, wk->panelwk->data[0]->itemid, v22, 0);
  v23 = HIDWORD(v4[4].klass) & 0xFFFFFFCD;
  LODWORD(v4[4].klass) = 1;
  HIDWORD(v4[4].klass) = v23;
  tgtList = wk->tgtList;
  if (tgtList)
  {
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
    goto LABEL_39;
  }
LABEL_39:
  Instance = get_Instance(0);
  BattleMenuClose(Instance, 0, 0);
  sBtlMenuClose();
  SelectRootID = GetSelectRootID();
  v31 = get_Instance(0);
  CloseCommonStockMenu(v31, SelectRootID, 0, 0);
  v32 = get_Instance(0);
  CloseHelpWin(v32, 0);
  v33 = get_Instance(0);
  MenuClose(v33->devil_info2, 0);
  devilInfo = 0;
  v34 = get_Instance(0);
  CharIconCtr(v34, 0, 0);
  p_item_keep = &wk->item_keep;
  p_item_keep = 0;
  return 1;
}

// 0x1f288c0
bool sBtlItemChkUseUnit(sdatUnitWork_t *a_pUnit, s32 a_itemId) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v6;
  u64 v7;
  SBTLUNIT_WORK *Nakama;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *v11;
  sdatUnitWork_t *v12;

  LOBYTE(Skilltbl) = 0;
  if (a_pUnit && (u32)a_itemId <= 0x2FF)
  {
    Skilltbl = sBtlGetSkilltbl(tbldata[a_itemId]->sklid);
    if (!Skilltbl)
      return (char)Skilltbl;
    v6 = Skilltbl;
    if ((tbldata[a_itemId]->usetype & 2) == 0)
    {
      LOBYTE(Skilltbl) = 0;
      return (char)Skilltbl;
    }
    if ((v6->flg2 & 0x2000) != 0)
    {
      Nakama = sBtlGetNakama(0);
      if (Nakama && (para = Nakama->para, para->devilid == a_pUnit->devilid) && para->uniq_code == a_pUnit->uniq_code && Nakama->byctCnt || (v11 = sBtlGetNakama(1)) != 0 && (v12 = v11->para, v12->devilid == a_pUnit->devilid) && v12->uniq_code == a_pUnit->uniq_code && v11->byctCnt)
      {
        LOBYTE(Skilltbl) = 1;
        return (char)Skilltbl;
      }
    }
    else if ((v6->attr & 0x800) == 0)
    {
      v7 = cmpChkEnableUseUnit(a_pUnit, a_itemId);
      if ((v7 & 0xC000) != 0)
      {
        if (wk->mag >= wk->magMax)
          v7 = (u32)v7 & 0xFFFF3FFF;
      }
      LOBYTE(Skilltbl) = v7 != 0;
      return (char)Skilltbl;
    }
    LOBYTE(Skilltbl) = 0;
  }
  return (char)Skilltbl;
}

// 0x1f28b70
bool sBtlItemChkUseUnitEx(sdatUnitWork_t *a_pUnit, s32 a_itemId, bool a_bStock) {
  s32 devilid;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *Nakama;
  sdatUnitWork_t *v11;
  u32 uniq_code;
  u32 v13;
  _BOOL4 v14;
  SBTLUNIT_WORK *v15;
  sdatUnitWork_t *v17;
  u32 BadStatus;

  if (!Exists("new_devil"))
  {
    devilid = a_pUnit->devilid;
    if (sBtlIsDLCDevil(devilid))
      return 0;
  }
  para = a_pUnit;
  if (!a_bStock)
    goto LABEL_24;
  Nakama = sBtlGetNakama(0);
  if (Nakama && (v11 = Nakama->para, v11->devilid == a_pUnit->devilid))
  {
    uniq_code = v11->uniq_code;
    v13 = a_pUnit->uniq_code;
    v14 = uniq_code != v13;
    if (uniq_code == v13)
      para = Nakama->para;
    else
      para = a_pUnit;
    v15 = sBtlGetNakama(1);
    if (!v15)
      goto LABEL_23;
  }
  else
  {
    v14 = 1;
    para = a_pUnit;
    v15 = sBtlGetNakama(1);
    if (!v15)
      goto LABEL_23;
  }
  v17 = v15->para;
  if (v17->devilid == para->devilid && v17->uniq_code == para->uniq_code)
  {
    para = v15->para;
    v14 = 0;
  }
LABEL_23:
  if (v14)
    goto LABEL_31;
LABEL_24:
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus == 17)
    return 0;
  if (BadStatus == 16 && a_pUnit->devilid)
    return 0;
LABEL_31:
  return sBtlItemChkUseUnit(para, a_itemId);
}

// 0x1f28db0
void sBtlSetItemScript(sBtlMenu_t *_wk, ITM _itemID) {
  s32 itemScrReq;
  dds3ProcessID_t *started;
  Il2CppObject *ProcessData;
  s64 naturalAligment;
  s32 mapSummonID;
  char *PlayerName;
  s64 v15;
  char *v16;
  s32 monitor_high;
  s32 v18;
  s32 scrItem;
  char *v20;

  wk->scrItem = itemID;
  if (itemID == 9)
    wk->itemScrReq = 15;
  itemScrReq = wk->itemScrReq;
  started = scrStartScript2(1, g_pDatScr, itemScrReq, 1);
  wk->itemScr = started;
  ProcessData = dds3GetProcessData(&wk->itemScr);
  if (wk->battlemode == 3)
  {
    {
      mapSummonID = GBWK->mapSummonID;
      PlayerName = sdatDevilName(mapSummonID, 0);
      goto LABEL_26;
    }
LABEL_33:
  }
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)v15 || ProcessData->klass->_2.typeHierarchy[v15 - 1] != scrHandle_t)
    {
      goto LABEL_33;
    }
  }
  PlayerName = sBtlGetPlayerName();
LABEL_26:
  v16 = PlayerName;
  monitor_high = HIDWORD(ProcessData[6].monitor);
  itfMesMngSetVarImmediate(monitor_high, 0, v16);
  v18 = HIDWORD(ProcessData[6].monitor);
  scrItem = wk->scrItem;
  v20 = sdatItemName(scrItem);
  itfMesMngSetVarImmediate(v18, 1, v20);
  wk->step = 27;
}

// 0x1f290e0
s32 sBtlFuncDecideItem(void) {
  sBtlMenu **v1;
  Il2CppObject *ProcessData;
  sBtlMenu_t *v5;
  dds3ProcessID_t *klass;
  s32 SelectID;
  s32 id;
  SBTLITEM_TBL *Itemtbl;
  SBTLITEM_TBL *p_item_keep;
  s32 SelectRootID;
  s32 stock_num;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  u32 v21;
  void *Instance;
  s32 i;
  s32 devilid;
  dds3ProcessID_t *charPID;
  dds3ProcessID_t *v29;
  u32 v31;
  void *v33;
  dds3ProcessID_t *v35;
  bool v36;
  void *v37;
  dds3ProcessID_t *v38;
  s32 v39;
  s32 v40;
  dds3ProcessID_t *v41;
  s64 m;
  bool v43;
  SBATTLE_WORK *v46;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  dds3ProcessID_t *v49;
  s32 v50;
  char *v51;
  itfMenuFunc_t v52;
  dds3ProcessID_t *v53;
  itfMenuDrawFunc_t v54;
  sdatUnitWork_t *v56;
  dds3ProcessID_t *v59;
  char *PlayerName;
  itfMenuFunc_t v61;
  dds3ProcessID_t *v62;
  itfMenuDrawFunc_t v63;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  bool v67;
  dds3ProcessID_t *v68;
  s32 v70;
  struct sBtlMenu *static_fields;
  s32 v72;
  sdatUnitWork_t *StockUnitData;
  dds3ProcessID_t *v75;
  sdatUnitWork_t *v76;
  s32 v77;
  void **v78;
  char *v79;
  itfMenuFunc_t v80;
  dds3ProcessID_t *v81;
  itfMenuDrawFunc_t v82;
  bool v84;
  dds3ProcessID_t *v85;
  dds3ProcessID_t *v86;
  void *v87;
  dds3ProcessID_t *v89;
  SBTLUNIT_WORK *Nakama;
  s32 v92;
  dds3ProcessID_t *v93;
  char *v94;
  itfMenuFunc_t v95;
  dds3ProcessID_t *v96;
  itfMenuDrawFunc_t v97;
  bool v99;
  dds3ProcessID_t *v100;
  sdatUnitWork_t *para;
  s32 j;
  void **v104;
  sdatUnitWork_t *v105;
  s32 v106;
  itfMenuFunc_t v107;
  itfMenuDrawFunc_t v108;
  s32 v110;
  bool v111;
  s32 v112;
  dds3ProcessID_t *v113;
  SBTLUNIT_WORK *v114;
  sdatUnitWork_t *v115;
  s32 k;
  void **v118;
  sdatUnitWork_t *v119;
  s32 v120;
  itfMenuFunc_t v121;
  itfMenuDrawFunc_t v122;
  bool v124;
  dds3ProcessID_t *v125;
  SBATTLE_WORK *v127;
  dds3ProcessID_t *v128;
  s32 v129;
  char *LocalizeText;
  itfMenuFunc_t v131;
  dds3ProcessID_t *v132;
  s32 v133;
  itfMenuDrawFunc_t v134;
  sBtlMenu *v135;
  dds3ProcessID_t *v136;
  dds3ProcessID_t *v138;
  dds3ProcessID_t *v140;
  s32 v141;
  s32 v142;
  s32 v145;
  dds3ProcessID_t *v147;
  s32 *IdList;
  s32 *v149;
  s64 v150;
  s32 *m_Items;
  s32 v152;
  dds3ProcessID_t *v153;
  dds3ProcessID_t *v154;
  dds3ProcessID_t *v155;
  void *v156;
  MethodInfo *v157;
  dds3ProcessID_t *v158;
  bool ShortCutFlg;
  sBtlMenu *v161;
  struct sBtlMenu *v162;
  dds3ProcessID_t *v164;
  sBtlMenu *v165;
  char *v166;
  char *PID;
  dds3ProcessID_t *PIDa;
  dds3ProcessID_t *PIDb;
  sdatUnitWork_t *a_pUnit;
  sdatUnitWork_t *a_pUnita;
  sdatUnitWork_t *a_pUnitc;
  s32 a_pUnitb;
  s32 v174;
  u16 side;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v177;

  v1 = &sBtlMenu;
  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  sBtlGetNakama(0);
  wk->macter_csr = SelectID;
  id = wk->itemList->data[SelectID]->id;
  itemIdSave = id;
  Itemtbl = sBtlGetItemtbl(id);
  side = Itemtbl->side;
  Skilltbl = sBtlGetSkilltbl(Itemtbl->sklid);
  p_item_keep = &wk->item_keep;
  p_item_keep = Itemtbl;
  MenuCnt = 0;
  SelectRootID = GetSelectRootID();
  stock_num = wk->stock_num;
  if (Exists("new_devil"))
    goto LABEL_13;
  for (i = 0; ; ++i)
  {
    if (i >= wk->stock_num)
      break;
    devilid = sBtlGetStockUnitData(i)->devilid;
    stock_num -= sBtlIsDLCDevil(devilid);
  }
  v1 = &sBtlMenu;
  if ((u32)(id - 17) >= 2)
    goto LABEL_14;
LABEL_41:
  sBtlFuncDecideItemStock();
  return 1;
LABEL_13:
  if ((u32)(id - 17) < 2)
    goto LABEL_41;
LABEL_14:
  if (id != 9)
  {
    if (id == 38)
    {
      tgtList = wk->tgtList;
      if (tgtList)
      {
        tgtList = wk->tgtList;
        sBtlDeleteUnitList(tgtList, 0);
        p_tgtList = &wk->tgtList;
        p_tgtList = 0;
      }
      wk->panelwk->data[0]->itemid = 38;
      sBtlSetMenuPara(9, 0, -1, 38, -1, 0);
      v21 = v5->flag & 0xFFFFFFCD;
      v5->step = 1;
      v5->flag = v21;
      Instance = get_Instance(0);
      CloseCommonMenu(Instance, SelectRootID, 0, 0);
      return 1;
    }
    charPID = v5->charPID;
    itfMenuSetFlag(charPID, 512, 0);
    if ((side & 0x2000) != 0)
    {
      g_nakamaTabMov = 0;
    }
    else
    {
      if ((side & 0x5000) != 0)
      {
        v29 = v5->charPID;
        itfMenuClearMenuAll(v29);
        if ((side & 0x1000) != 0)
        {
          if (wk->battlemode == 3)
          {
            v174 = 0;
          }
          else
          {
            g_nakamaTabMov = 0;
            v59 = v5->charPID;
            PlayerName = sBtlGetPlayerName();
            v61 = Allocate(itfMenuFunc_t);
            _ctor(v61, 0, Method_Project_sBtlMenu_FuncDecideItemTarget__, 0);
            itfMenuSetRootMenu(v59, 0, PlayerName, v61, "");
            v62 = v5->charPID;
            v63 = Allocate(itfMenuDrawFunc_t);
            _ctor(v63, 0, Method_Project_sBtlMenu_DrawFuncPartyDat__, 0);
            itfMenuSetDrawFunc(v62, 0, v63, 0);
            PlayerID = sBtlGetPlayerID();
            PlayerUnit = sBtlGetPlayerUnit(PlayerID);
            v67 = sBtlItemChkUseUnitEx(PlayerUnit->para, id, 0);
            itfMenuSetFlagMenu(v5->charPID, 0, 2, v67);
            if (v67)
            {
              v68 = v5->charPID;
              itfMenuSetSelectID(v68, 0);
            }
            v174 = 1;
          }
          if ((side & 0x4000) == 0)
            goto LABEL_209;
        }
        else
        {
          v174 = 0;
          if ((side & 0x4000) == 0)
            goto LABEL_209;
        }
        v70 = wk->stock_num;
        g_nakamaTabMov = v70 > 0;
        if (g_nakamaTab)
        {
          v72 = 0;
          while (v72 < wk->stock_num)
          {
            StockUnitData = sBtlGetStockUnitData(v72);
            if (StockUnitData)
            {
              v75 = v5->charPID;
              v76 = StockUnitData;
              v77 = StockUnitData->devilid;
              v78 = v1;
              v79 = sdatDevilName(v77, 0);
              v80 = Allocate(itfMenuFunc_t);
              _ctor(v80, 0, Method_Project_sBtlMenu_FuncDecideItemTarget__, 0);
              itfMenuSetRootMenu(v75, ++v72, v79, v80, "");
              v81 = v5->charPID;
              v82 = Allocate(itfMenuDrawFunc_t);
              _ctor(v82, 0, Method_Project_sBtlMenu_DrawFuncPartyDat__, 0);
              itfMenuSetDrawFunc(v81, v72, v82, 0);
              v1 = v78;
              if (!*((u32 *)*v78 + 56))
              ++v174;
              v84 = sBtlItemChkUseUnitEx(v76, id, 1);
              itfMenuSetFlagMenu(v5->charPID, v72, 2, v84);
            }
            else
            {
              ++v72;
            }
          }
          v85 = v5->charPID;
          itfMenuSetSelectID(v85, 8);
          goto LABEL_209;
        }
        if (wk->battlemode == 3)
        {
          Nakama = sBtlGetNakama(0);
          if (!Nakama)
            goto LABEL_171;
          goto LABEL_156;
        }
        v92 = sBtlGetPlayerID();
        a_pUnit = sBtlGetPlayerUnit(v92)->para;
        v93 = v5->charPID;
        v94 = sBtlGetPlayerName();
        v95 = Allocate(itfMenuFunc_t);
        _ctor(v95, 0, Method_Project_sBtlMenu_FuncDecideItemTarget__, 0);
        itfMenuSetRootMenu(v93, 0, v94, v95, "");
        v96 = v5->charPID;
        v97 = Allocate(itfMenuDrawFunc_t);
        _ctor(v97, 0, Method_Project_sBtlMenu_DrawFuncPartyDat__, 0);
        itfMenuSetDrawFunc(v96, 0, v97, 0);
        if ((Itemtbl->side & 4) != 0)
        {
          v99 = 1;
          v1 = &sBtlMenu;
        }
        else
        {
          v1 = &sBtlMenu;
          v99 = sBtlItemChkUseUnitEx(a_pUnit, id, 0);
        }
        v100 = v5->charPID;
        ++v174;
        itfMenuSetFlagMenu(v100, 0, 2, v99);
        itfMenuSetSelectID(v5->charPID, 0);
        Nakama = sBtlGetNakama(0);
        if (!Nakama)
          goto LABEL_171;
LABEL_156:
        para = Nakama->para;
        for (j = 1; ; ++j)
        {
          if (j - 1 >= wk->stock_num)
            break;
          v104 = v1;
          v105 = sBtlGetStockUnitData(j - 1);
          v106 = para->devilid;
          if (v105->devilid == para->devilid && para->uniq_code == v105->uniq_code)
          {
            a_pUnita = v5->charPID;
            PID = sdatDevilName(v106, 0);
            v107 = Allocate(itfMenuFunc_t);
            _ctor(v107, 0, Method_Project_sBtlMenu_FuncDecideItemTarget__, 0);
            itfMenuSetRootMenu(a_pUnita, j, PID, v107, "");
            a_pUnitc = v5->charPID;
            v108 = Allocate(itfMenuDrawFunc_t);
            _ctor(v108, 0, Method_Project_sBtlMenu_DrawFuncPartyDat__, 0);
            itfMenuSetDrawFunc(a_pUnitc, j, v108, 0);
            if ((Itemtbl->side & 4) != 0)
            {
              v110 = v174;
              v111 = 1;
            }
            else
            {
              v110 = v174;
              if (!*((u32 *)*v104 + 56))
              v111 = sBtlItemChkUseUnitEx(para, id, 0);
            }
            v174 = v110 + 1;
            v113 = v5->charPID;
            itfMenuSetFlagMenu(v113, j, 2, v111);
            v112 = 1;
            v1 = v104;
            goto LABEL_176;
          }
          v1 = v104;
        }
LABEL_171:
        v112 = 0;
LABEL_176:
        v114 = sBtlGetNakama(1);
        if (v114)
        {
          v115 = v114->para;
          a_pUnitb = v112;
          for (k = 1; ; ++k)
          {
            if (k - 1 >= wk->stock_num)
              break;
            v118 = v1;
            v119 = sBtlGetStockUnitData(k - 1);
            v120 = v115->devilid;
            if (v119->devilid == v115->devilid && v115->uniq_code == v119->uniq_code)
            {
              PIDa = v5->charPID;
              v166 = sdatDevilName(v120, 0);
              v121 = Allocate(itfMenuFunc_t);
              _ctor(v121, 0, Method_Project_sBtlMenu_FuncDecideItemTarget__, 0);
              itfMenuSetRootMenu(PIDa, k, v166, v121, "");
              PIDb = v5->charPID;
              v122 = Allocate(itfMenuDrawFunc_t);
              _ctor(v122, 0, Method_Project_sBtlMenu_DrawFuncPartyDat__, 0);
              itfMenuSetDrawFunc(PIDb, k, v122, 0);
              if ((Itemtbl->side & 4) != 0)
              {
                v124 = 1;
                v1 = v118;
              }
              else
              {
                v1 = v118;
                if (!*((u32 *)*v118 + 56))
                v124 = sBtlItemChkUseUnitEx(v115, id, 0);
              }
              v125 = v5->charPID;
              ++v174;
              ++a_pUnitb;
              itfMenuSetFlagMenu(v125, k, 2, v124);
              break;
            }
            v1 = v118;
          }
          v112 = a_pUnitb;
        }
        if (stock_num - v112 >= 1)
        {
          v127 = wk;
          if (v127->battlemode == 3)
            goto LABEL_209;
          v128 = v5->charPID;
          v127 = wk;
          v129 = v127->stock_num;
          ++v174;
          LocalizeText = GetLocalizeText("SBTL_MENU_L0021", 1);
          v131 = Allocate(itfMenuFunc_t);
          _ctor(v131, 0, Method_Project_sBtlMenu_FuncDecideItemTarget__, 0);
          itfMenuSetRootMenu(v128, v129 + 1, LocalizeText, v131, "");
          v132 = v5->charPID;
          v133 = wk->stock_num;
          v134 = Allocate(itfMenuDrawFunc_t);
          _ctor(v134, 0, Method_Project_sBtlMenu_DrawFuncPartyDat__, 0);
          itfMenuSetDrawFunc(v132, v133 + 1, v134, 0);
          itfMenuSetFlagMenu(v5->charPID, wk->stock_num + 1, 2, 1);
        }
LABEL_209:
        if (wk->battlemode == 3)
        {
          v135 = *v1;
          v135 = *v1;
          g_nakamaTabMov = 1;
          v136 = v5->charPID;
          itfMenuSetFlagMenu(v136, -1, 1, 0);
          v138 = v5->charPID;
          v140 = v138;
          v141 = 1;
          v142 = wk->summonindex[0] + 1;
          goto LABEL_218;
        }
        if ((side & 1) != 0)
        {
          if ((side & 0x1000) != 0)
          {
            v165 = *v1;
            v165 = *v1;
            g_nakamaTabMov = 0;
          }
          goto LABEL_219;
        }
        v161 = *v1;
        v161 = *v1;
        g_nakamaTabMov = 1;
        if ((side & 4) == 0)
        {
LABEL_219:
          v145 = SelectID;
          v147 = v5->charPID;
          wk->panelwk->data[0]->itemid = id;
          IdList = itfMenuGetIdList(v147);
          if (SLODWORD(IdList->max_length) >= 1)
          {
            v149 = IdList;
            v150 = 0;
            m_Items = IdList;
            do
            {
              v152 = m_Items[v150];
              v153 = v5->charPID;
              if (!!itfMenuGetFlagMenu(v5->charPID, v152, 2u))
              {
                if ((Skilltbl->flg & 0x13000) != 0)
                {
                  if ((v152 & 0x80000000) == 0)
                  {
                    v154 = v5->charPID;
                    itfMenuSetInitSelectID(v154, v152);
                  }
                  break;
                }
              }
              ++v150;
            }
            while (v150 < SLODWORD(v149->max_length));
          }
          v155 = v5->charPID;
          itfMenuStart(v155);
          v5->step = 10;
          v156 = get_Instance(0);
          v157 = *v1;
          v158 = v5->charPID;
          ShortCutFlg = sBtlGetShortCutFlg();
          v40 = v174;
          v36 = ShortCutFlg;
          v37 = v156;
          v38 = v158;
          v39 = v145;
LABEL_242:
          OpenCommonMenu(v37, v38, 0, v39, 0, v40, v36, 0);
          return 1;
        }
        v162 = (*v1)->static_fields;
        g_nakamaTabMov = 1;
        v164 = v5->charPID;
        itfMenuSetFlagMenu(v164, -1, 16, 1);
        v140 = v5->charPID;
        v142 = -1;
        v141 = 2;
LABEL_218:
        itfMenuSetFlagMenu(v140, v142, v141, 1);
        goto LABEL_219;
      }
      if ((side & 0x8000) != 0)
      {
        v177 = SelectID;
        v41 = v5->charPID;
        itfMenuClearMenuAll(v41);
        for (m = 0; ; ++m)
        {
          v46 = wk;
          UnitMng = v46->UnitMng;
          if (m >= UnitMng->number)
            break;
          UnitMng = wk->UnitMng;
          pUnit = UnitMng->pUnitL[m]->pUnit;
          if (pUnit && (pUnit->side & 2) != 0)
          {
            if (CheckLiveTarget(pUnit) && (pUnit->flg & 0x200) == 0)
            {
              v49 = v5->charPID;
              v50 = pUnit->para->devilid;
              v51 = sdatDevilName(v50, 0);
              v52 = Allocate(itfMenuFunc_t);
              _ctor(v52, 0, Method_Project_sBtlMenu_FuncDecideItemTarget__, 0);
              itfMenuSetRootMenu(v49, m, v51, v52, "");
              v53 = v5->charPID;
              v54 = Allocate(itfMenuDrawFunc_t);
              _ctor(v54, 0, Method_Project_sBtlMenu_DrawTargetCharList__, 0);
              itfMenuSetDrawFunc(v53, m, v54, 0);
              v56 = pUnit->para;
              v43 = sBtlItemChkUseUnitEx(v56, id, 0);
              itfMenuSetFlagMenu(v5->charPID, m, 2, v43);
            }
          }
        }
        v46 = wk;
        v86 = v5->charPID;
        v46->panelwk->data[0]->itemid = id;
        itfMenuStart(v86);
        v5->step = 5;
        v87 = get_Instance(0);
        v89 = v5->charPID;
        v36 = sBtlGetShortCutFlg();
        v37 = v87;
        v38 = v89;
        v39 = v177;
LABEL_64:
        v40 = 8;
        goto LABEL_242;
      }
    }
    v31 = v5->flag & 0xFFFFFFEF;
    v5->step = 1;
    v5->flag = v31;
    v33 = get_Instance(0);
    v35 = v5->charPID;
    v36 = sBtlGetShortCutFlg();
    v37 = v33;
    v38 = v35;
    v39 = SelectID;
    goto LABEL_64;
  }
  sBtlSetItemScript(v5, 9);
  return 1;
}

// 0x1f27690
s32 sBtlFuncDecideItemStock(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s32 SelectID;
  s64 v8;
  s32 id;
  SBTLITEM_TBL *Itemtbl;
  u16 side;
  s32 SelectRootID;
  void *Instance;
  dds3ProcessID_t *monitor;
  s32 v17;
  SBTLSKILLP_TBL *v18;
  s32 v19;
  Il2CppClass **v20;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v23;
  s32 devilid;
  SBTLUNIT_WORK *Nakama;
  sdatUnitWork_t *v26;
  SBTLUNIT_WORK *v27;
  sdatUnitWork_t *v29;
  s64 v31;
  void **v32;
  Il2CppClass *v34;
  sdatUnitWork_t *stockUnitTgt_local;
  s32 v37;
  s32 i;
  Il2CppClass **v39;
  sdatUnitWork_t *v40;
  sdatUnitWork_t *v41;
  s32 v42;
  SBTLUNIT_WORK *v43;
  sdatUnitWork_t *v44;
  SBTLUNIT_WORK *v45;
  sdatUnitWork_t *v47;
  s64 v49;
  void **v50;
  Il2CppClass *v52;
  sdatUnitWork_t *v53;
  s64 v55;
  bool v56;
  dds3ProcessID_t *v57;
  s64 v58;
  s64 v59;
  sdatUnitWork_t *v60;
  s64 v61;
  s32 v62;
  dds3ProcessID_t *v63;
  char *v64;
  itfMenuFunc_t v65;
  dds3ProcessID_t *v66;
  itfMenuDrawFunc_t v67;
  sdatUnitWork_t *v69;
  sdatUnitWork_t *v71;
  dds3ProcessID_t *v73;
  char *PlayerName;
  itfMenuFunc_t v75;
  dds3ProcessID_t *v76;
  itfMenuDrawFunc_t v77;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  sdatUnitWork_t *para;
  bool v82;
  dds3ProcessID_t *v83;
  bool v84;
  dds3ProcessID_t *v85;
  dds3ProcessID_t *v87;
  s32 *IdList;
  s32 *v89;
  s64 v90;
  s32 *m_Items;
  s32 v92;
  dds3ProcessID_t *v93;
  dds3ProcessID_t *v94;
  dds3ProcessID_t *v95;
  s32 v96;
  void *v97;
  dds3ProcessID_t *v99;
  bool ShortCutFlg;
  dds3ProcessID_t *v102;
  s32 v103;
  SBTLSKILLP_TBL *Skilltbl;
  s64 v105;
  SBTLITEM_TBL *v106;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  v8 = NewSpecific(sdatUnitWork_t, 0x20u);
  sBtlGetNakama(0);
  wk->macter_csr = SelectID;
  id = wk->itemList->data[SelectID]->id;
  Itemtbl = sBtlGetItemtbl(id);
  side = Itemtbl->side;
  v106 = Itemtbl;
  Skilltbl = sBtlGetSkilltbl(Itemtbl->sklid);
  MenuCnt = 0;
  SelectRootID = GetSelectRootID();
  Instance = get_Instance(0);
  CloseCommonMenu(Instance, SelectRootID, 0, 0);
  itfMenuSetFlag(v4[3].monitor, 512, 0);
  if ((side & 0x2000) != 0)
  {
    g_nakamaTabMov = 0;
    return 1;
  }
  if ((side & 0x5000) == 0)
    return 1;
  monitor = v4[3].monitor;
  itfMenuClearMenuAll(v4[3].monitor);
  v103 = SelectID;
  if ((side & 0x1000) == 0)
    goto LABEL_17;
  g_nakamaTabMov = 0;
  v73 = v4[3].monitor;
  PlayerName = sBtlGetPlayerName();
  v75 = Allocate(itfMenuFunc_t);
  _ctor(v75, 0, Method_Project_sBtlMenu_FuncDecideItemTargetStock__, 0);
  itfMenuSetRootMenu(v73, 0, PlayerName, v75, "");
  v76 = v4[3].monitor;
  v77 = Allocate(itfMenuDrawFunc_t);
  _ctor(v77, 0, Method_Project_sBtlMenu_DrawFuncStockDat__, 0);
  itfMenuSetDrawFunc(v76, 0, v77, 0);
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  if ((v106->side & 4) != 0)
  {
    v102 = v4[3].monitor;
    itfMenuSetFlagMenu(v102, 0, 2, 1);
    v85 = v4[3].monitor;
    goto LABEL_124;
  }
  else
  {
    para = PlayerUnit->para;
    v82 = sBtlItemChkUseUnitEx(para, id, 0);
    v83 = v4[3].monitor;
    v84 = v82;
    itfMenuSetFlagMenu(v83, 0, 2, v84);
    if (!v84)
    {
LABEL_125:
      v17 = 1;
      v18 = Skilltbl;
      if ((side & 0x4000) != 0)
        goto LABEL_18;
LABEL_126:
      goto LABEL_128;
    }
    v85 = v4[3].monitor;
LABEL_124:
    itfMenuSetSelectID(v85, 0);
    goto LABEL_125;
  }
  goto LABEL_124;
LABEL_17:
  v17 = 0;
  v18 = Skilltbl;
  if ((side & 0x4000) == 0)
    goto LABEL_126;
LABEL_18:
  v19 = 0;
  v105 = v8 + 32;
  while (1)
  {
    if (v19 >= wk->stock_num)
      break;
    StockUnitData = sBtlGetStockUnitData(v19);
    if (!StockUnitData)
      goto LABEL_20;
    v23 = StockUnitData;
    if (!Exists("new_devil"))
    {
      devilid = v23->devilid;
      if (sBtlIsDLCDevil(devilid))
        goto LABEL_20;
    }
    Nakama = sBtlGetNakama(0);
    if (!Nakama || (v26 = Nakama->para, v26->devilid != v23->devilid) || v26->uniq_code != v23->uniq_code)
    {
      v27 = sBtlGetNakama(1);
      if (!v27 || (v29 = v27->para, v29->devilid != v23->devilid) || v29->uniq_code != v23->uniq_code)
      {
        if (!sBtlItemChkUseUnitEx(v23, id, 1))
          goto LABEL_20;
        if (!QueryInterface(v23, *(void **)(*(u64 *)v8 + 64)))
          goto LABEL_85;
        v31 = 8 * v17;
        *(u64 *)(v8 + v31 + 32) = v23;
        v32 = (v8 + v31 + 32);
        v34 = *v32;
        stockUnitTgt_local = stockUnitTgt;
        if (*v32)
        {
          {
LABEL_85:
          }
        }
        v20 = &stockUnitTgt_local->obj.klass + v17;
        v20[4] = v34;
        ++v17;
      }
    }
LABEL_20:
    ++v19;
  }
  v37 = v17;
  for (i = 0; ; ++i)
  {
    if (i >= wk->stock_num)
      break;
    v40 = sBtlGetStockUnitData(i);
    if (!v40)
      goto LABEL_57;
    v41 = v40;
    if (!Exists("new_devil"))
    {
      v42 = v41->devilid;
      if (sBtlIsDLCDevil(v42))
        goto LABEL_57;
    }
    v43 = sBtlGetNakama(0);
    if (!v43 || (v44 = v43->para, v44->devilid != v41->devilid) || v44->uniq_code != v41->uniq_code)
    {
      v45 = sBtlGetNakama(1);
      if (!v45 || (v47 = v45->para, v47->devilid != v41->devilid) || v47->uniq_code != v41->uniq_code)
      {
        if (sBtlItemChkUseUnitEx(v41, id, 1))
          goto LABEL_57;
        if (!QueryInterface(v41, *(void **)(*(u64 *)v8 + 64)))
          goto LABEL_85;
        v49 = 8 * v37;
        *(u64 *)(v8 + v49 + 32) = v41;
        v50 = (v8 + v49 + 32);
        v52 = *v50;
        v53 = stockUnitTgt;
        v39 = &v53->obj.klass + v37;
        v39[4] = v52;
        ++v37;
      }
    }
LABEL_57:
  }
  v55 = 0;
  while (v55 < wk->stock_num)
  {
    v58 = v8 + 8 * v55;
    v61 = *(u64 *)(v58 + 32);
    v60 = (v58 + 32);
    v59 = v61;
    if (v61)
    {
      v62 = *(s16 *)(v59 + 22);
      v63 = v4[3].monitor;
      v64 = sdatDevilName(v62, 0);
      v65 = Allocate(itfMenuFunc_t);
      _ctor(v65, 0, Method_Project_sBtlMenu_FuncDecideItemTargetStock__, 0);
      itfMenuSetRootMenu(v63, ++v55, v64, v65, "");
      v66 = v4[3].monitor;
      v67 = Allocate(itfMenuDrawFunc_t);
      _ctor(v67, 0, Method_Project_sBtlMenu_DrawFuncStockDat__, 0);
      itfMenuSetDrawFunc(v66, v55, v67, 0);
      v69 = v60;
      v56 = 1;
      sBtlItemChkUseUnitEx(v69, id, 1);
      if ((v106->side & 4) == 0)
      {
        v71 = v60;
        v56 = sBtlItemChkUseUnitEx(v71, id, 1);
      }
      v57 = v4[3].monitor;
      itfMenuSetFlagMenu(v57, v55, 2, v56);
      itfMenuSetSelectID(v4[3].monitor, 8);
    }
    else
    {
      ++v55;
    }
  }
  v18 = Skilltbl;
  v17 = v37;
LABEL_128:
  wk->panelwk->data[0]->itemid = id;
  v87 = v4[3].monitor;
  IdList = itfMenuGetIdList(v87);
  if (SLODWORD(IdList->max_length) >= 1)
  {
    v89 = IdList;
    v90 = 0;
    m_Items = IdList;
    do
    {
      v92 = m_Items[v90];
      v93 = v4[3].monitor;
      if (!!itfMenuGetFlagMenu(v4[3].monitor, v92, 2u))
      {
        if ((v18->flg & 0x3000) != 0)
        {
          if ((v92 & 0x80000000) == 0)
          {
            v94 = v4[3].monitor;
            itfMenuSetInitSelectID(v94, v92);
          }
          break;
        }
      }
      ++v90;
    }
    while (v90 < SLODWORD(v89->max_length));
  }
  v95 = v4[3].monitor;
  if (v17 >= 8)
    v96 = 8;
  else
    v96 = v17;
  itfMenuSetDrawParam(v95, 8, 1);
  itfMenuStart(v4[3].monitor);
  LODWORD(v4[4].klass) = 11;
  v97 = get_Instance(0);
  v99 = v4[3].monitor;
  ShortCutFlg = sBtlGetShortCutFlg();
  OpenCommonStockMenu(v97, v99, 0, v103, 0, v96, ShortCutFlg, 0);
  return 1;
}

// 0x1f2a830
void sBtlDrawFuncItem(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  Il2CppObject *v12;
  dds3ProcessID_t *klass;
  char **v17;
  void *Instance;
  s32 id;
  void *v21;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  klass = ProcessData[2].klass;
  if (itfMenuGetSelectID(klass) == a_id)
  {
    if (wk->itemList->data[a_id]->id == 9)
    {
      if (DlcItemGetCheck(9))
      {
        v17 = &"BTL022";
        goto LABEL_23;
      }
    }
    v17 = &"BTL001";
LABEL_23:
    Instance = get_Instance(0);
    GuideSet(Instance, *v17, 0, 90, 0);
    id = wk->itemList->data[a_id]->id;
    sBtlHelp(2, id, a_alphaRate);
  }
  v21 = get_Instance(0);
  ItemMenuDraw(v21, a_id, 0, v12[2].klass, 0);
}

// 0x1f2ab30
s32 sBtlItemChkUse(s32 a_itemId) {
  char *v5;
  char *NoneItemText;
  s32 v7;
  SBTLSKILLP_TBL *Skilltbl;
  s64 v9;
  SBTLUNIT_LISTWORK *v11;
  SBTLUNIT_WORK *v12;
  sdatUnitWork_t *para;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 j;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v22;

  dds3GetProcessData(g_mainPID);
  if (wk->battlemode == 3)
  {
    if ((tbldata[a_itemId]->usetype & 0x10) != 0)
      return 0;
  }
  if (!!sBtlCheckTutorialBattle())
  {
    if ((u32)(a_itemId - 17) < 2)
      return 0;
  }
  if (a_itemId == 9)
  {
    v5 = sdatItemName(9);
    NoneItemText = cmpGetNoneItemText();
    if (op_Inequality(v5, NoneItemText, 0))
      return 1;
  }
  else if (a_itemId == 38)
  {
    if (sBtlEscapeCheck() == 2)
      return 0;
    return ((wk->status3 >> 21) & 1) == 0;
  }
  Skilltbl = sBtlGetSkilltbl(tbldata[a_itemId]->sklid);
  if (!Skilltbl)
    return 0;
  if ((Skilltbl->attr & 0x800) != 0)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return 0;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) != 0)
      {
        CheckLiveTarget(pUnit);
      }
    }
  }
  v9 = 0;
  v7 = 0;
  while (1)
  {
    v11 = wk->UnitMng;
    if (v9 >= v11->number)
      break;
    v12 = v11->pUnitL[v9]->pUnit;
    if (!v12)
      goto LABEL_36;
    if ((v12->side & 1) == 0 || (v12->para->flag & 4) == 0)
    {
      if (!CheckLiveTarget(v12))
        goto LABEL_36;
      para = v12->para;
      v7 += sBtlItemChkUseUnitEx(para, a_itemId, 0);
    }
LABEL_36:
    ++v9;
  }
  for (j = 0; ; ++j)
  {
    if (j >= wk->stock_num)
      break;
    StockUnitData = sBtlGetStockUnitData(j);
    if (StockUnitData)
    {
      v22 = StockUnitData;
      v7 += sBtlItemChkUseUnitEx(v22, a_itemId, 1);
    }
  }
  return v7;
}

// 0x1f1f5a0
s32 sBtlFuncItem(void) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v3;
  s64 naturalAligment;
  dds3ProcessID_t *v5;
  SBTLITEM_TBL *p_item_keep;
  s64 v8;
  SBTLITEM_LISTWORK *itemList;
  dds3ProcessID_t *v12;
  s32 id;
  char *v14;
  itfMenuFunc_t v15;
  dds3ProcessID_t *v16;
  itfMenuDrawFunc_t v17;
  s32 v19;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;
  void *Instance;
  void *v23;
  dds3ProcessID_t *v24;
  void *v25;
  bool ShortCutFlg;

  ProcessData = dds3GetProcessData(g_mainPID);
  v3 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((sBtlMenu_t **)(ProcessData)[1].next + naturalAligment - 1) != sBtlMenu_t;
  }
  v5 = ProcessData[4];
  itfMenuClearMenuAll(v5);
  p_item_keep = &wk->item_keep;
  p_item_keep = 0;
  v8 = 0;
  g_nakamaTab = 0;
  MenuCnt = 0;
  *((u32 *)v3 + 25) = 2;
  while (1)
  {
    itemList = wk->itemList;
    if (v8 >= itemList->num)
      break;
    itemList = wk->itemList;
    v12 = v3[4];
    id = itemList->data[v8]->id;
    v14 = sdatItemName(id);
    v15 = Allocate(itfMenuFunc_t);
    _ctor(v15, 0, Method_Project_sBtlMenu_FuncDecideItem__, 0);
    itfMenuSetRootMenu(v12, v8, v14, v15, "");
    v16 = v3[4];
    v17 = Allocate(itfMenuDrawFunc_t);
    _ctor(v17, 0, Method_Project_sBtlMenu_DrawFuncItem__, 0);
    itfMenuSetDrawFunc(v16, v8, v17, 0);
    v19 = sBtlItemChkUse(id);
    v20 = v3[4];
    itfMenuSetFlagMenu(v20, v8++, 2, v19 > 0);
  }
  v21 = v3[5];
  itfMenuSetDrawParam(v21, 8, 1);
  itfMenuSetDrawParam(v3[4], 8, 1);
  itfMenuStart(v3[4]);
  Instance = get_Instance(0);
  GuideSet(Instance, "BTL001", 0, 90, 0);
  v23 = get_Instance(0);
  v24 = v3[4];
  v25 = v23;
  ShortCutFlg = sBtlGetShortCutFlg();
  OpenItemMenu(v25, v24, 0, 5, 0, 8, ShortCutFlg, 0);
  *((u32 *)v3 + 16) = 3;
  return 1;
}

// 0x1f2b0f0
s32 sBtlFuncKatana(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s64 i;
  SBTLITEM_LISTWORK *katanaList;
  dds3ProcessID_t *v10;
  s32 id;
  char *v12;
  itfMenuFunc_t v13;
  dds3ProcessID_t *v14;
  itfMenuDrawFunc_t v15;
  dds3ProcessID_t *v17;
  s32 swordno;
  s32 v19;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;
  void *Instance;
  dds3ProcessID_t *v24;
  bool ShortCutFlg;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[2].klass;
  itfMenuClearMenuAll(klass);
  for (i = 0; ; ++i)
  {
    katanaList = wk->katanaList;
    if (i >= katanaList->num)
      break;
    katanaList = wk->katanaList;
    v10 = v4[2].klass;
    id = katanaList->data[i]->id;
    v12 = sdatItemName(id);
    v13 = Allocate(itfMenuFunc_t);
    _ctor(v13, 0, Method_Project_sBtlMenu_FuncDecideKatana__, 0);
    itfMenuSetRootMenu(v10, i, v12, v13, "");
    v14 = v4[2].klass;
    v15 = Allocate(itfMenuDrawFunc_t);
    _ctor(v15, 0, Method_Project_sBtlMenu_DrawFuncKatana__, 0);
    itfMenuSetDrawFunc(v14, i, v15, 0);
    v17 = v4[2].klass;
    swordno = GBWK->player->swordno;
    v19 = id - 144;
    itfMenuSetFlagMenu(v17, i, 2, v19 != swordno);
    if (v19 != GBWK->player->swordno)
      continue;
    v20 = v4[2].klass;
    itfMenuSetInitSelectID(v20, i);
  }
  v21 = v4[2].klass;
  itfMenuSetDrawParam(v21, 8, 1);
  itfMenuStart(v4[2].klass);
  Instance = get_Instance(0);
  v24 = v4[2].klass;
  ShortCutFlg = sBtlGetShortCutFlg();
  OpenSwordMenu(Instance, v24, 0, 6, 0, 8, ShortCutFlg, 0);
  MenuCnt = 0;
  LODWORD(v4[4].klass) = 3;
  return 1;
}

// 0x1f2b580
static s32 FuncDecideKatana(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s32 SelectID;
  s32 id;
  s32 v12;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  wk->macter_csr = SelectID;
  id = wk->katanaList->data[SelectID]->id;
  sBtlSetMenuPara(13, -1, -1, id, -1, 0);
  itfMenuSetFlag(v4[2].klass, 512, 0);
  v12 = id - 144;
  g_equipNo = v12;
  sBtlSetType(v12, 0);
  LODWORD(v4[4].klass) = 12;
  MenuCnt = 0;
  wk->panelwk->data[0]->itemid = id;
  Instance = get_Instance(0);
  RaidouGaugeCtr(Instance, 1, 0);
  return 1;
}

// 0x1f2bb30
void sBtlDrawFuncKatana(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  Il2CppObject *v11;
  dds3ProcessID_t *klass;
  u32 SelectID;
  u32 v15;
  s32 swordno;
  s64 v19;
  s64 v20;
  SBTLITEM_LISTWORK *katanaList;
  s32 id;
  s32 v25;
  s32 v26;
  void *Instance;
  u32 v30;
  s32 v33;
  void *v34;
  void *v40;
  void *v41;
  void *v55;
  void *v56;
  void *v57;
  s32 v58;

  ProcessData = dds3GetProcessData(g_mainPID);
  v11 = ProcessData;
  v58 = a_id;
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  if (SelectID == itfMenuGetSelectID(v11[2].klass))
  {
    swordno = GBWK->player->swordno;
    sBtlDrawBeforeSwordParam(swordno, -1, v15);
    v19 = 0;
    v20 = SelectID;
    while (1)
    {
      katanaList = wk->katanaList;
      if (v19 >= katanaList->num)
        break;
      katanaList = wk->katanaList;
      id = katanaList->data[v19]->id;
      v25 = id - 144;
      v26 = GBWK->player->swordno;
      if (v25 != v26 && v20 == v19)
      {
        Instance = get_Instance(0);
        RaidouAffterWeapon(Instance, 1, 0);
        v33 = GBWK->player->swordno;
        sBtlDrawBeforeSwordParam(v25, v33, v30);
        if (g_equipNoOld != v25)
        {
          v34 = get_Instance(0);
          AllGaugeOff(v34->raidouGaugeSet, 0);
          g_equipNo = v25;
          sBtlSetType(v25, 0);
          sBtlDrawParam(0);
          sBtlDrawParam(1);
          sBtlDrawParam(2);
          sBtlDrawParam(3);
          goto LABEL_15;
LABEL_70:
          sBtlDrawParam(3);
LABEL_15:
          g_equipNoOld = v25;
          goto LABEL_16;
LABEL_69:
          sBtlDrawParam(2);
          goto LABEL_70;
LABEL_68:
          sBtlDrawParam(1);
          goto LABEL_69;
LABEL_67:
          sBtlDrawParam(0);
          goto LABEL_68;
        }
      }
      else
      {
        if (v25 != v26 || v20 != v19)
          goto LABEL_16;
        v40 = get_Instance(0);
        RaidouAffterWeapon(v40, 0, 0);
        if (g_equipNoOld != v25)
        {
          v41 = get_Instance(0);
          AllGaugeOff(v41->raidouGaugeSet, 0);
          sBtlSetType(v25, 0);
          goto LABEL_67;
        }
      }
LABEL_16:
      ++v19;
    }
  }
  v55 = get_Instance(0);
  RaidouBeforWeaPon(v55, 1, 0);
  v56 = get_Instance(0);
  RaidouGaugeCtr(v56, 1, 0);
  v57 = get_Instance(0);
  ItemMenuDraw(v57, v58, 0, v11[2].klass, 0);
}

// 0x1f2c0f0
void sBtlDrawBeforeSwordParam(s32 a_swordno, s32 a_swordno_chk, u32 a_swordnameColor) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  u32 SelectID;
  s32 swordno;
  void *weaponSet;
  s64 v16;
  s64 v17;
  char *v18;
  SBTLITEM_LISTWORK *katanaList;
  s32 id;
  bool v23;
  void *v24;
  u32 v26;
  u32 ValueColor;
  s32 m_atk;
  s32 v29;
  Il2CppObject *v30;
  char *v31;
  char *v32;
  void *Instance;
  u32 v34;
  s32 hp;
  s32 v36;
  Il2CppObject *v37;
  char *v38;
  char *v39;
  void *v40;
  u32 v41;
  s32 str;
  s32 v43;
  Il2CppObject *v44;
  char *v45;
  char *v46;
  void *v47;
  u32 v48;
  s32 tec;
  s32 v50;
  Il2CppObject *v51;
  char *v52;
  char *v53;
  void *v54;
  u32 v55;
  s32 vit;
  s32 v57;
  Il2CppObject *v58;
  char *v59;
  char *v60;
  void *v61;
  s32 luck;
  s32 v63;
  Il2CppObject *v64;
  char *v65;
  void *v66;
  s32 v67;
  s64 v68;
  s32 v69;
  s32 data;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  swordno = GBWK->player->swordno;
  v69 = swordno != a_swordno;
  weaponSet = get_Instance(0)->weaponSet;
  v67 = a_swordno_chk;
  v68 = a_swordno;
  DetailsSwordTypeIconDraw(weaponSet, tbl[a_swordno]->m_type, v69, 0);
  v16 = 0;
  v17 = SelectID;
  while (1)
  {
    katanaList = wk->katanaList;
    if (v16 >= katanaList->num)
      break;
    katanaList = wk->katanaList;
    id = katanaList->data[v16]->id;
    v23 = id - 144 == GBWK->player->swordno && swordno == a_swordno;
    if (v23 || v17 == v16 && swordno != a_swordno)
    {
      v24 = get_Instance(0)->weaponSet;
      v18 = sdatItemName(id);
      WeaponDetailsTextDraw(v24, v18, 1, v69, "", 1, 0);
    }
    ++v16;
  }
  v26 = -1600273536;
  ValueColor = -1600273536;
  m_atk = tbl[v68]->m_atk;
  if ((v67 & 0x80000000) == 0)
  {
    v29 = tbl[v67]->m_atk;
    ValueColor = cmpGetValueColor(m_atk, v29);
  }
  data = m_atk;
  v30 = Box(s32, &data);
  v31 = Format("{0,3:d}", v30, 0);
  v32 = Concat_54766928(0, v31, 0);
  Instance = get_Instance(0);
  WeaponParaDraw(Instance->weaponSet, 5, 1, m_atk, ValueColor, v69, 0);
  v34 = -1600273536;
  hp = tbl[v68]->m_paraBns->hp;
  if ((v67 & 0x80000000) == 0)
  {
    v36 = tbl[v67]->m_paraBns->hp;
    v34 = cmpGetValueColor(hp, v36);
  }
  data = hp;
  v37 = Box(s32, &data);
  v38 = Format("{0,2:d}", v37, 0);
  v39 = Concat_54766928(v32, v38, 0);
  v40 = get_Instance(0);
  WeaponParaDraw(v40->weaponSet, 4, 0, hp, v34, v69, 0);
  v41 = -1600273536;
  str = tbl[v68]->m_paraBns->str;
  if ((v67 & 0x80000000) == 0)
  {
    v43 = tbl[v67]->m_paraBns->str;
    v41 = cmpGetValueColor(str, v43);
  }
  data = str;
  v44 = Box(s32, &data);
  v45 = Format("{0,1:d}", v44, 0);
  v46 = Concat_54766928(v39, v45, 0);
  v47 = get_Instance(0);
  WeaponParaDraw(v47->weaponSet, 0, 1, str, v41, v69, 0);
  v48 = -1600273536;
  tec = tbl[v68]->m_paraBns->tec;
  if ((v67 & 0x80000000) == 0)
  {
    v50 = tbl[v67]->m_paraBns->tec;
    v48 = cmpGetValueColor(tec, v50);
  }
  data = tec;
  v51 = Box(s32, &data);
  v52 = Format("{0,1:d}", v51, 0);
  v53 = Concat_54766928(v46, v52, 0);
  v54 = get_Instance(0);
  WeaponParaDraw(v54->weaponSet, 1, 2, tec, v48, v69, 0);
  v55 = -1600273536;
  vit = tbl[v68]->m_paraBns->vit;
  if ((v67 & 0x80000000) == 0)
  {
    v57 = tbl[v67]->m_paraBns->vit;
    v55 = cmpGetValueColor(vit, v57);
  }
  data = vit;
  v58 = Box(s32, &data);
  v59 = Format("{0,1:d}", v58, 0);
  v60 = Concat_54766928(v53, v59, 0);
  v61 = get_Instance(0);
  WeaponParaDraw(v61->weaponSet, 2, 3, vit, v55, v69, 0);
  luck = tbl[v68]->m_paraBns->luck;
  if ((v67 & 0x80000000) == 0)
  {
    v63 = tbl[v67]->m_paraBns->luck;
    v26 = cmpGetValueColor(luck, v63);
  }
  data = luck;
  v64 = Box(s32, &data);
  v65 = Format("{0,1:d}", v64, 0);
  Concat_54766928(v60, v65, 0);
  v66 = get_Instance(0);
  WeaponParaDraw(v66->weaponSet, 3, 4, luck, v26, v69, 0);
}

// 0x1f2cd20
void sBtlDrawParam(s32 a_type) {
  sdatUnitWork_t *v3;
  sdatParaWork_t *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  sdatUnitWork_t *para;
  s32 tec;
  s32 CorrectionParamLuck;
  s32 v13;
  u32 v14;
  s16 *p_str;
  s32 luck;
  s32 v20;
  s32 v21;
  s32 v22;
  Il2CppObject *v23;
  char *v24;
  s64 v25;
  void *Instance;
  s32 v27;
  s32 v28;
  sdatUnitWork_t *v29;
  void *v30;
  s32 v31;
  s32 v32;
  void *v33;
  void *v34;
  void *v38;
  void *v39;
  s32 v41;
  void *v42;
  void *v43;
  void *v44;
  s32 v45;
  s32 v47;
  void *v48;
  s32 Sword4Param;
  sdatUnitWork_t *v50;
  s32 v51;
  s32 str;
  s32 data;

  v3 = Allocate(sdatUnitWork_t);
  _ctor(v3, 0);
  v4 = Allocate(sdatParaWork_t);
  _ctor(v4, 0);
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  para = sBtlSearchUnit_ID(UnitMng, playerID)->para;
  v50 = para;
  switch (a_type)
  {
    case 0:
      str = para->now->str;
      tec = para->backup->str;
      Sword4Param = datGetSword4Param(GBWK->player->swordno, 0);
      if ((para->flag & 2) != 0)
      {
        CorrectionParamLuck = 0;
        tec += GETITEMPARA_LOW(para->pitem->str);
        p_str = &para->pitem->str;
        goto LABEL_32;
      }
      CorrectionParamLuck = 0;
      v13 = 0;
      v14 = 0;
      goto LABEL_33;
    case 1:
      str = para->now->tec;
      tec = para->backup->tec;
      v14 = 1;
      Sword4Param = datGetSword4Param(GBWK->player->swordno, 1);
      if ((para->flag & 2) == 0)
        goto LABEL_20;
      CorrectionParamLuck = 0;
      tec += GETITEMPARA_LOW(para->pitem->tec);
      p_str = &para->pitem->tec;
      goto LABEL_32;
    case 2:
      str = para->now->vit;
      tec = para->backup->vit;
      v14 = 2;
      Sword4Param = datGetSword4Param(GBWK->player->swordno, 2);
      if ((para->flag & 2) == 0)
      {
LABEL_20:
        CorrectionParamLuck = 0;
        v13 = 0;
        goto LABEL_33;
      }
      CorrectionParamLuck = 0;
      tec += GETITEMPARA_LOW(para->pitem->vit);
      p_str = &para->pitem->vit;
      goto LABEL_32;
    case 3:
      datCalcLuckParam();
      tec = para->backup->luck;
      str = para->now->luck;
      Sword4Param = datGetSword4Param(GBWK->player->swordno, 3);
      if (para->devilid)
      {
        CorrectionParamLuck = 0;
        if ((para->flag & 2) == 0)
        {
LABEL_25:
          v13 = 0;
          v14 = 3;
          goto LABEL_33;
        }
      }
      else
      {
        CorrectionParamLuck = sBtlGetCorrectionParamLuck();
        luck = para->backup->luck;
        str = GETITEMPARA(para->pitem->luck)
            + luck
            + para->pbtl->luck
            + para->huuma->luck
            + para->surpriseParam->luck;
        if ((para->flag & 2) == 0)
          goto LABEL_25;
      }
      tec += GETITEMPARA_LOW(para->pitem->luck);
      p_str = &para->pitem->luck;
LABEL_32:
      v13 = GETITEMPARA_HIGH(*p_str);
      v14 = a_type;
LABEL_33:
      v51 = tec + v13;
      v20 = tec + v13 + param[a_type];
      v21 = v20 + CorrectionParamLuck;
      if (v20 + CorrectionParamLuck <= 1)
        v21 = 1;
      if (a_type == 3)
        v20 = v21;
      if (v20 >= 40)
        v22 = 40;
      else
        v22 = v20;
      data = v22;
      v23 = Box(s32, &data);
      v24 = Format("{0,2:d}", v23, 0);
      Concat_54766928(0, v24, 0);
      v25 = a_type;
      Instance = get_Instance(0);
      ParDrawNumUnity(Instance->raidouGaugeSet, v22, v14, 0);
      v27 = 0;
      v28 = tec - Sword4Param;
      v29 = v50;
      break;
    default:
      CorrectionParamLuck = 0;
      v13 = 0;
      Sword4Param = 0;
      tec = 0;
      str = 0;
      v14 = -1;
      goto LABEL_33;
  }
  do
  {
    if ((v29->flag & 2) != 0)
      v31 = 40;
    else
      v31 = v13;
    if (v27 < v31)
    {
      if (v31 >= 40)
        v32 = 40;
      else
        v32 = v31;
      v33 = get_Instance(0);
      BaseGaugeDrawUnity(v33->raidouGaugeSet, v32, v14, 0);
      v29 = v50;
    }
    if (v27 < v28)
    {
      v34 = get_Instance(0);
      GaugeChangeColor(v34->raidouGaugeSet, v27, v14, 1, 0);
      if (str != lastOrangePar[v25])
      {
        lastOrangePar[v25] = str;
        v38 = get_Instance(0);
        (v38->raidouGaugeSet->klass->vtable._4_OrangeGaugeDrawUnity.methodPtr)(v38->raidouGaugeSet, v27, v14, v38->raidouGaugeSet->klass->vtable._4_OrangeGaugeDrawUnity.method);
        goto LABEL_66;
      }
    }
LABEL_66:
    if (v28 <= v27 && v27 < tec)
    {
      v39 = get_Instance(0);
      GaugeChangeColor(v39->raidouGaugeSet, v27, v14, 2, 0);
    }
    v41 = param[v25];
    if (v41 >= 1)
    {
      v41 = param[v25];
      if (tec <= v27 && v27 < v41 + tec)
      {
        v42 = get_Instance(0);
        LightGaugeDrawUnity(v42->raidouGaugeSet, v27, v14, 0);
        v43 = get_Instance(0);
        (v43->raidouGaugeSet->klass->vtable._4_OrangeGaugeDrawUnity.methodPtr)(v43->raidouGaugeSet, v27, v14, v43->raidouGaugeSet->klass->vtable._4_OrangeGaugeDrawUnity.method);
        v44 = get_Instance(0);
        GaugeChangeColor(v44->raidouGaugeSet, v27, v14, 1, 0);
      }
    }
    v45 = param[v25] + tec;
    if (v45 <= v27 && v27 < v45 + v13)
    {
      v48 = get_Instance(0);
      GaugeChangeColor(v48->raidouGaugeSet, v27, v14, 3, 0);
LABEL_94:
      v47 = param[v25];
      if ((v47 & 0x80000000) == 0)
        goto LABEL_46;
      goto LABEL_95;
    }
    {
      goto LABEL_94;
    }
    v47 = param[v25];
    if ((v47 & 0x80000000) == 0)
      goto LABEL_46;
LABEL_95:
    v47 = param[v25];
    if (v27 < v51 && v51 + v47 <= v27)
    {
      v30 = get_Instance(0);
      GaugeChangeColor(v30->raidouGaugeSet, v27, v14, 4, 0);
    }
LABEL_46:
    ++v27;
  }
  while (v27 != 40);
}

// 0x1f2b820
bool sBtlSetType(s32 a_katanano, bool _root) {
  sdatPlayerUnitWork_t *PlayerData;
  s32 PlayerID;
  sdatPlayerUnitWork_t *player;
  s32 swordno;
  s32 Sword4Param;
  s32 *v16;
  s32 v17;
  s32 *v18;
  s32 v19;
  s32 *v20;
  s32 v21;
  SBTLUNIT_WORK *PChara;

  dds3GetProcessData(g_mainPID);
  PlayerData = sBtlGetPlayerData();
  PlayerID = sBtlGetPlayerID();
  sBtlGetPlayerUnit(PlayerID);
  if (a_katanano < 0)
    return a_katanano >= 0;
  player = GBWK->player;
  wk->equipsord = player->swordno;
  ClassCopy(PlayerData, player, 0);
  swordno = GBWK->player->swordno;
  Sword4Param = datGetSword4Param(a_katanano, 0);
  param[0] = Sword4Param - datGetSword4Param(swordno, 0);
  v16 = param;
  v17 = datGetSword4Param(a_katanano, 1);
  v16[1] = v17 - datGetSword4Param(swordno, 1);
  v18 = param;
  v19 = datGetSword4Param(a_katanano, 2);
  v18[2] = v19 - datGetSword4Param(swordno, 2);
  v20 = param;
  v21 = datGetSword4Param(a_katanano, 3);
  v20[3] = v21 - datGetSword4Param(swordno, 3);
  PChara = sBtlGetPChara();
  datCalcNowParam(PChara->para, GBWK->player->swordno, 0);
  datDvlParaUpdate(0);
  return a_katanano >= 0;
}

// 0x1f2d5d0
void sBtlSetEquipKatanaNo(s32 iKatanaNo) {
  g_equipNo = iKatanaNo;
  return;
}

// 0x1f2d660
s32 sBtlFuncDecideAnalyze(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  s32 SelectRootID;
  void *Instance;
  void *v13;
  void *v14;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  monitor = ProcessData[2].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  itfMenuSetFlag(v4[2].monitor, 8, 0);
  itfMenuSetFlagMenu(v4[2].monitor, SelectID, 8, 1);
  sBtlDecMag(0);
  SelectRootID = GetSelectRootID();
  Instance = get_Instance(0);
  CloseCommonMenu(Instance, SelectRootID, 0, 0);
  LOWORD(v4[4].monitor) = 0;
  LODWORD(v4[5].klass) = 0;
  MenuCnt = 0;
  LODWORD(v4[4].klass) = 13;
  v13 = get_Instance(0);
  OpenHuumaInfo(v13, 0);
  v14 = get_Instance(0);
  GuideSet(v14, "BTL001", 0, 90, 0);
  return 1;
}

// 0x1f2d8e0
void sBtlDrawFuncAnalyze(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  Il2CppObject *ProcessData;
  Il2CppObject *v12;
  dds3ProcessID_t *monitor;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  v12 = ProcessData;
  if (!wk->tgtList)
    return;
  monitor = v12[2].monitor;
  if (itfMenuGetSelectID(v12[2].monitor) == a_id)
    goto LABEL_16;
  goto LABEL_9001;
  if (itfMenuGetSelectID(monitor) == a_id)
  {
LABEL_16:
    wk->tgt_csr = a_id;
    sBtlDrawTargetCursorEnemy();
    if (wk->modeSq)
    {
LABEL_20:
      Instance = get_Instance(0);
      CommonMenuDraw(Instance, 0, v12[2].monitor, 0, 0, 0);
      return;
    }
    sBtlHelp(3, 16, alphaRate);
    goto LABEL_20;
  }
LABEL_9001:
}

// 0x1f1fa30
s32 sBtlFuncAnalyze(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitList;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *TargetList_Analyze;
  s64 v24;
  s32 v25;
  u32 v27;
  SBATTLE_WORK *v28;
  SBTLUNIT_LISTWORK *v29;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_WORK *EnemyUnitTgt_local;
  u64 v33;
  SBTLUNIT_WORK *v34;
  s32 battlemode;
  u32 v36;
  s32 v37;
  SBTLUNIT_WORK *v38;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  SBTLUNIT_WORK *Nakama;
  s32 v42;
  s32 v43;
  SBTLUNIT_WORK *v44;
  SBTLUNIT_WORK *v46;
  u64 v47;
  SBTLUNIT_WORK *v48;
  SBTLUNIT_WORK *v49;
  SBTLUNIT_WORK *v51;
  u64 v52;
  SBTLUNIT_WORK *v53;
  SBTLUNIT_WORK *v54;
  SBTLUNIT_WORK *v56;
  u64 v57;
  SBTLUNIT_WORK *v58;
  SBATTLE_WORK *v60;
  u32 status;
  s64 v63;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v66;
  s32 SelectRootID;
  void *Instance;
  void *v71;
  void *v72;
  Il2CppObject *v75;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  targetID = sBtlGetPChara()->actaiwk->targetID;
  UnitList = sBtlCreateUnitList(48);
  saveUnitTgt = 0;
  analizeChangeFlag = 0;
  enemyNowCsr = 0;
  AnalizeCnt = 0;
  AnalizeClose = 0;
  v11 = NewSpecific(SBTLUNIT_WORK, 0x20u);
  EnemyUnitTgt = v11;
  tgtList = wk->tgtList;
  if (tgtList)
  {
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
    goto LABEL_15;
  }
LABEL_15:
  wk_local = wk;
  TargetList_Analyze = sBtlCreateTargetList_Analyze(2);
  wk_local->tgtList = TargetList_Analyze;
  if (wk->tgtList->count <= 0)
  {
    RootMenuReturn(0);
    return 1;
  }
  v75 = v4;
  v24 = 0;
  v25 = 0;
  enemyNumCount = -1;
  while (1)
  {
    v28 = wk;
    v29 = v28->tgtList;
    if (v24 >= v29->count)
      break;
    if (v27)
    {
      pUnit = v29->pUnitL[v24]->pUnit;
      if (!pUnit)
        goto LABEL_22;
    }
    else
    {
      pUnit = wk->tgtList->pUnitL[v24]->pUnit;
      if (!pUnit)
        goto LABEL_22;
    }
    if (!CheckLiveTarget(pUnit))
      goto LABEL_22;
    EnemyUnitTgt_local = EnemyUnitTgt;
    v33 = v25;
    EnemyUnitTgt_local[v33] = pUnit;
    v34 = EnemyUnitTgt[v33];
    sBtlEntryUnitList(UnitList, v34);
    ++v25;
    ++enemyNumCount;
LABEL_22:
    ++v24;
  }
  if (!v27)
  {
    v28 = wk;
  }
  battlemode = (u16)v28->battlemode;
  if (battlemode != 3)
  {
    if (v36)
    {
      PlayerID = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(PlayerID);
      if (!PlayerUnit)
        goto LABEL_55;
    }
    else
    {
      v43 = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(v43);
      if (!PlayerUnit)
      {
LABEL_55:
        Nakama = sBtlGetNakama(0);
        if (!Nakama)
        {
LABEL_56:
          v38 = sBtlGetNakama(1);
          if (v38)
            goto LABEL_75;
          goto LABEL_81;
        }
LABEL_69:
        v49 = Nakama;
        v51 = EnemyUnitTgt;
        v52 = v25;
        v51[v52] = v49;
        v53 = EnemyUnitTgt[v52];
        sBtlEntryUnitList(UnitList, v53);
        ++v25;
        ++enemyNumCount;
        v38 = sBtlGetNakama(1);
        if (v38)
          goto LABEL_75;
        goto LABEL_81;
      }
    }
    v44 = PlayerUnit;
    v46 = EnemyUnitTgt;
    v47 = v25;
    v46[v47] = v44;
    v48 = EnemyUnitTgt[v47];
    sBtlEntryUnitList(UnitList, v48);
    ++v25;
    ++enemyNumCount;
    Nakama = sBtlGetNakama(0);
    if (!Nakama)
      goto LABEL_56;
    goto LABEL_69;
  }
  if (v36)
  {
    v37 = sBtlGetPlayerID();
    v38 = sBtlGetPlayerUnit(v37);
    if (!v38)
      goto LABEL_81;
LABEL_75:
    v54 = v38;
    v56 = EnemyUnitTgt;
    {
      v57 = v25;
      v56[v57] = v54;
      v58 = EnemyUnitTgt[v57];
      sBtlEntryUnitList(UnitList, v58);
      ++enemyNumCount;
      goto LABEL_81;
    }
  }
  v42 = sBtlGetPlayerID();
  v38 = sBtlGetPlayerUnit(v42);
  if (v38)
    goto LABEL_75;
LABEL_81:
  HIDWORD(v75[4].klass) |= 2u;
  sBtlMenuOpen();
  v60 = wk;
  status = v60->status;
  v60->tgtList = UnitList;
  v60->status = status | 0x80000;
  v63 = 0;
  while (2)
  {
    if (v63 < SLODWORD(EnemyUnitTgt->max_length))
    {
      UnitMng = wk->UnitMng;
      v66 = sBtlSearchUnit_ID(UnitMng, targetID);
      if (v66 == EnemyUnitTgt[v63])
      {
        enemyNowCsr = v63;
      }
      ++v63;
      continue;
    }
    break;
  }
  sBtlResetTargetCursor();
  SelectRootID = GetSelectRootID();
  Instance = get_Instance(0);
  CloseCommonMenu(Instance, SelectRootID, 0, 0);
  LODWORD(v75[4].klass) = 18;
  v71 = get_Instance(0);
  OpenHuumaInfo(v71, 0);
  v72 = get_Instance(0);
  GuideSet(v72, "BTL001", 0, 90, 0);
  return 1;
}

// 0x1f2dbb0
void sBtlAnalizeEnemySel(void) {
  s32 enemyNumCount_local;
  u32 v9;
  s32 v10;
  SBATTLE_WORK *v14;
  SBATTLE_WORK *v15;
  SBTLUNIT_LISTWORK *tgtList;
  s32 tgt_csr;
  SBTLUNIT_WORK *v20;
  SBTLUNIT_WORK *v21;

  if (!wk->tgtList)
    return;
  if (wk->modeSq)
    goto LABEL_35;
  if (CHECK_TRIG(4100, 1) || CHECK_TRIG(4102, 1))
  {
    if (enemyNowCsr < enemyNumCount)
    {
      enemyNumCount_local = enemyNowCsr + 1;
LABEL_33:
      enemyNowCsr = enemyNumCount_local;
LABEL_34:
      SE(3);
      goto LABEL_35;
    }
    enemyNowCsr = 0;
    goto LABEL_34;
  }
  if (CHECK_TRIG(4101, 1) || CHECK_TRIG(4103, 1))
  {
    v10 = enemyNowCsr;
    if (v10 < 1)
    {
      enemyNumCount_local = enemyNumCount;
    }
    else
    {
      if (!v9)
      {
        v10 = enemyNowCsr;
      }
      enemyNumCount_local = v10 - 1;
    }
    goto LABEL_33;
  }
LABEL_35:
  v14 = wk;
  v15 = wk;
  tgtList = v15->tgtList;
  v14->tgt_csr = enemyNowCsr;
  tgt_csr = v15->tgt_csr;
  v20 = sBtlSearchUnit_ID(tgtList, tgt_csr);
  if (!v20)
    goto LABEL_49;
  v21 = v20;
  if (saveUnitTgt)
  {
    goto LABEL_46;
  }
  saveUnitTgt = v21;
LABEL_46:
  if (saveUnitTgt->side != v21->side)
    analizeChangeFlag = 1;
  saveUnitTgt = v21;
LABEL_49:
  sBtlDrawTargetCursorEnemy();
}

// 0x1f203d0
s32 sBtlFuncEscape(void) {
  Il2CppObject *ProcessData;
  sBtlMenu_t *v4;
  s32 v6;
  u32 v10;
  u32 v12;
  u32 status;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if ((g_bitMoon & 4) == 0)
  {
    v6 = sBtlEscapeCheck();
    if (v6 == 1)
    {
      v10 = g_bitMoon & 0xFFFFFFFE;
    }
    else
    {
      v10 = g_bitMoon | 1;
    }
    g_bitMoon = v10;
  }
  sBtlSetMenuPara(11, -1, -1, -1, -1, 0);
  sBtlResetEscapeGauge();
  v12 = v4->flag & 0xFFFFFFCD;
  v4->step = 1;
  v4->flag = v12;
  v4->endtype = 1;
  if (v4->type == 1)
  {
    status = wk->status;
    wk->escape_stat = 0;
    wk->status = status | 0x400000;
    sBtlCallEnd(v4);
    return 1;
  }
  tgtList = wk->tgtList;
  if (tgtList)
  {
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
    goto LABEL_35;
  }
LABEL_35:
  sBtlMenuClose();
  Instance = get_Instance(0);
  BattleMenuClose(Instance, 0, 0);
  return 1;
}

// 0x1f2df70
s32 sBtlFuncDecideTalk(void) {
  Il2CppObject *ProcessData;
  sBtlMenu_t *v4;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  s32 playerID;
  s64 v11;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 v13;
  SBATTLE_WORK *v14;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  monitor = ProcessData[2].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  playerID = wk->playerID;
  v11 = (s64)wk->tgtList->pUnitL + 8 * SelectID;
  UnitMng = wk->UnitMng;
  v13 = *(u64 *)(*(u64 *)(v11 + 32) + 24);
  sBtlSearchUnit_ID(UnitMng, playerID);
  v14 = wk;
  v14->huuma_targetID = *(u32 *)(v13 + 364);
  v14->kaiwa_mode = 0;
  v4->endtype = 2;
  sBtlCallEnd(v4);
  sBtlSetMenuPara(0, 0, -1, 0, -1, 0);
  return 1;
}

// 0x1f2e180
s32 sBtlFuncTalk(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v3;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *TargetList_Talk;
  dds3ProcessID_t *monitor;
  s32 i;
  SBATTLE_WORK *v18;
  SBTLUNIT_LISTWORK *v19;
  SBTLUNIT_WORK *v21;
  s32 hithelperID;
  SBTLUNIT_LISTWORK *UnitMng;
  dds3ProcessID_t *v25;
  s32 devilid;
  char *v27;
  itfMenuFunc_t v28;
  dds3ProcessID_t *v29;
  itfMenuDrawFunc_t v30;
  s32 v32;
  dds3ProcessID_t *v33;
  dds3ProcessID_t *v35;
  void *Instance;
  dds3ProcessID_t *v37;
  s32 count;
  bool ShortCutFlg;

  ProcessData = dds3GetProcessData(g_mainPID);
  v3 = ProcessData;
  tgtList = wk->tgtList;
  if (tgtList)
  {
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
    goto LABEL_14;
  }
LABEL_14:
  wk_local = wk;
  TargetList_Talk = sBtlCreateTargetList_Talk(2);
  wk_local->tgtList = TargetList_Talk;
  if (wk->tgtList->count <= 0)
  {
    RootMenuReturn(0);
    return 1;
  }
  monitor = v3[2].monitor;
  itfMenuSetFlag(monitor, 512, 0);
  itfMenuClearMenuAll(v3[2].monitor);
  for (i = 0; ; ++i)
  {
    v18 = wk;
    v19 = v18->tgtList;
    if (i >= v19->count)
      break;
    v21 = sBtlSearchUnit_ID(v19, i);
    if ((v21->status & 0x800) != 0)
    {
      hithelperID = v21->hithelperID;
      UnitMng = wk->UnitMng;
      v21 = sBtlSearchUnit_ID(UnitMng, hithelperID);
    }
    v25 = v3[2].monitor;
    devilid = v21->para->devilid;
    v27 = sdatDevilName(devilid, 0);
    v28 = Allocate(itfMenuFunc_t);
    _ctor(v28, 0, Method_Project_sBtlMenu_FuncDecideTalk__, 0);
    itfMenuSetRootMenu(v25, i, v27, v28, "");
    v29 = v3[2].monitor;
    v30 = Allocate(itfMenuDrawFunc_t);
    _ctor(v30, 0, Method_Project_sBtlMenu_DrawFuncTalk__, 0);
    itfMenuSetDrawFunc(v29, i, v30, 0);
    v32 = sBtlCheckEnableTalk(v21);
    v33 = v3[2].monitor;
    itfMenuSetFlagMenu(v33, i, 2, v32 == 1);
  }
  v18 = wk;
  v18->status |= 0x80000u;
  sBtlResetTargetCursor();
  v35 = v3[2].monitor;
  itfMenuStart(v35);
  Instance = get_Instance(0);
  v37 = v3[2].monitor;
  count = wk->tgtList->count;
  ShortCutFlg = sBtlGetShortCutFlg();
  OpenCommonMenu(Instance, v37, 0, 15, 0, count, ShortCutFlg, 0);
  LODWORD(v3[4].klass) = 4;
  return 1;
}

// 0x1f20740
s32 sBtlFuncDitectiveBook(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  dds3FadeOut(0, 0, 0, 0x1Eu);
  LODWORD(ProcessData[4].klass) = 21;
  return 1;
}

// 0x1f2e7b0
static void ChkEnableDecideEscape(sBtlMenu_t *wk) {
  s32 v4;
  s32 v5;
  dds3ProcessID_t *menuPID;
  char *MenuStr;
  char *LocalizeText;
  SBATTLE_WORK *v10;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v13;
  sdatUnitWork_t *para;
  u32 BadStatus;
  bool v18;
  bool v19;
  dds3ProcessID_t *v20;

  v4 = sBtlEscapeCheck();
  if (v4 == 1)
    v5 = 9;
  else
    v5 = 8;
  menuPID = wk->menuPID;
  MenuStr = sBtlGetMenuStr(v5);
  LocalizeText = GetLocalizeText(MenuStr, 1);
  itfMenuSetFont(menuPID, 8, LocalizeText, "");
  v10 = wk;
  UnitMng = v10->UnitMng;
  playerID = v10->playerID;
  v13 = sBtlSearchUnit_ID(UnitMng, playerID);
  para = v13->para;
  BadStatus = sBtlGetBadStatus(para);
  v18 = (wk->status3 & 0x200000) == 0 && v4 != 2;
  v19 = ChkEnableBadStatus(v13, 8, BadStatus, v18);
  v20 = wk->menuPID;
  itfMenuSetFlagMenu(v20, 8, 2, v19);
}

// 0x1f2ed10
bool sBtlSetTalkDisable(sBtlMenu_t *pMW) {
  return 0;
}

// 0x1f2ed20
s32 sBtlFuncKuzunohaDirect(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  dds3FadeOut(0, 0, 0, 0x1Eu);
  LODWORD(ProcessData[4].klass) = 23;
  return 1;
}

// 0x1f2ee80
static bool CalcKuzunohaDirect(sBtlMenu_t *wk) {
  s32 step;
  void *Instance;
  void *v11;
  void *v12;
  dds3ProcessID_t *menuPID;
  void *v14;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  void *v21;

  step = wk->step;
  if (step != 23)
    return step == 23;
  if (dds3FadeCheck())
    return step == 23;
  if (camp_onoff)
  {
    if (ProcessCheck())
      return step == 23;
    if (!camp_onoffCnt)
      goto LABEL_32;
    if (wk->battlemode != 1)
    {
      *(u64 *)&wk->FadeInDelay = 0x1E00000002LL;
LABEL_19:
      menu_onoff = 0;
      camp_onoff = 0;
      Instance = get_Instance(0);
      BattleDispUIOn(Instance, 0);
      v11 = get_Instance(0);
      CanvasAllActive(v11, 1, 0);
      v12 = get_Instance(0);
      DevilHPactive(v12, 1, 0);
      menuPID = wk->menuPID;
      itfMenuStart(menuPID);
      wk->step = 2;
      v14 = get_Instance(0);
      SetBattleMenuGuide(v14, 1, 0, 0);
      PlayerID = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(PlayerID);
      UnitSetPlayerSprit(PlayerUnit);
      sBtlCheckBattlePara(PlayerUnit);
      v17 = get_Instance(0);
      BackIconState(v17, 0);
LABEL_32:
      ++camp_onoffCnt;
      return 1;
    }
    sBtlReturnCamera();
    *(u64 *)&wk->FadeInDelay = 0x1E00000002LL;
    goto LABEL_19;
  }
  menu_onoff = 1;
  camp_onoff = 1;
  camp_onoffCnt = 0;
  v18 = get_Instance(0);
  BattleDispUI(v18, 0, 0);
  v19 = get_Instance(0);
  RememberIconState(v19, 0);
  v20 = get_Instance(0);
  CanvasAllActive(v20, 0, 0);
  v21 = get_Instance(0);
  DevilHPactive(v21, 0, 0);
  ProcessStart(-1, 0, 0);
  wk->step = 23;
  return 1;
}

// 0x1f2f300
s32 sBtlFuncConfig(void) {
  Il2CppObject *ProcessData;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  dds3FadeOut(0, 0, 0, 0xAu);
  Instance = get_Instance(0);
  BattleDispUI(Instance, 0, 0);
  menu_onoff = 1;
  LODWORD(ProcessData[4].klass) = 24;
  return 1;
}

// 0x1f2f4a0
static bool CalcConfig(sBtlMenu_t *wk) {
  s32 step;
  void *v7;
  void *v8;
  void *v9;
  dds3ProcessID_t *menuPID;
  void *v11;
  void *Instance;
  void *v13;
  s32 ConfigGAME;
  s32 v16;
  s32 v17;

  step = wk->step;
  if (step != 24)
    return step == 24;
  if (dds3FadeCheck())
    return step == 24;
  if (!config_onoff)
  {
    config_onoff = 1;
    ProcessStart(0);
    lmapSetBattleDestDisp(0);
    Instance = get_Instance(0);
    RememberIconState(Instance, 0);
    v13 = get_Instance(0);
    DevilHPactive(v13, 0, 0);
    return step == 24;
  }
  if (!ProcessCheck())
  {
    lmapSetBattleDestDisp(1);
    if (!lmapSetBattleDestFlagCheck(15))
    {
      if (!lmapSetBattleDestFlagCheck(19))
      {
        *(u64 *)&wk->FadeInDelay = 0xA00000002LL;
LABEL_19:
        *(u16 *)&menu_onoff = 0;
        v7 = get_Instance(0);
        BattleDispUIOn(v7, 0);
        v8 = get_Instance(0);
        DevilHPactive(v8, 1, 0);
        v9 = get_Instance(0);
        BackIconState(v9, 0);
        menuPID = wk->menuPID;
        itfMenuStart(menuPID);
        wk->step = 2;
        v11 = get_Instance(0);
        SetBattleMenuGuide(v11, 1, 0, 0);
        return step == 24;
      }
    }
    ConfigGAME = cfgGetConfigGAME(7, 0);
    if (ConfigGAME)
      v16 = 15;
    else
      v16 = 19;
    if (ConfigGAME)
      v17 = 19;
    else
      v17 = 15;
    lmapClrBattleDestFlag(v16);
    lmapSetBattleDestFlag(v17);
    *(u64 *)&wk->FadeInDelay = 0xA00000002LL;
    goto LABEL_19;
  }
  return step == 24;
}

// 0x1f1cc60
bool sBtlChkTutorialMenu(SBTL_MENU_ID id) {
  s32 v4;
  s32 encountno;
  s32 v8;

  switch (id)
  {
    case 1:
    case 2:
      encountno = wk->encountno;
      if (encountno == 512)
        return 0;
      if (encountno == 513)
        return 0;
      encountno = wk->encountno;
      if (encountno == 514)
        return 0;
      encountno = wk->encountno;
      if (encountno == 515)
        return 0;
      goto LABEL_86;
    case 3:
    case 6:
    case 7:
    case 8:
      v4 = wk->encountno;
      if (v4 == 512)
        return 0;
      if (v4 == 513)
        return 0;
      if (v4 == 514)
        return 0;
      v4 = wk->encountno;
      if (v4 == 515)
        return 0;
      v4 = wk->encountno;
      if (v4 == 516)
        return 0;
      v4 = wk->encountno;
      return v4 != 517;
    case 5:
      encountno = wk->encountno;
      if (encountno == 512)
        return 0;
      encountno = wk->encountno;
      if (encountno != 513)
        goto LABEL_80;
      return 0;
    case 17:
    case 19:
      encountno = wk->encountno;
      if (encountno == 512)
        return 1;
      if (encountno == 513)
        return 1;
LABEL_80:
      encountno = wk->encountno;
      if (encountno == 514)
        return 1;
      encountno = wk->encountno;
      if (encountno == 515)
        return 1;
LABEL_86:
      encountno = wk->encountno;
        return 1;
    case 18:
      v8 = wk->encountno;
      if (v8 == 512)
        return 0;
      v8 = wk->encountno;
      if (v8 == 513)
        return 0;
      v8 = wk->encountno;
      if (v8 == 514)
        return 0;
      v8 = wk->encountno;
      if (v8 == 515)
        return 0;
      v8 = wk->encountno;
      if (v8 == 516)
        return 0;
      v8 = wk->encountno;
      if (v8 == 517)
        return 0;
      return Sord_RSlill_Menu();
    default:
      return 1;
  }
}

// 0x1f2f840
static bool Sord_RSlill_Menu(void) {
  s32 v1;

  if (evtBitCheck(2103))
    v1 = 241;
  else
    v1 = 10007;
  return evtBitCheck(v1);
}

// 0x1f1e690
void sBtlChkEnableDecideMenu(sBtlMenu_t *wk) {
  SBATTLE_WORK *v6;
  dds3ProcessID_t *menuPID;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v12;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBTLUNIT_LISTWORK *TargetList;
  bool v17;
  bool v19;
  dds3ProcessID_t *v20;
  s32 num;
  bool v24;
  dds3ProcessID_t *v25;
  SBTLUNIT_LISTWORK *v27;
  s32 v28;
  SBTLUNIT_WORK *v29;
  sdatUnitWork_t *v30;
  u32 v32;
  char v35;
  bool v37;
  dds3ProcessID_t *v38;
  s32 v39;
  bool v40;
  _BOOL4 enemy_zenmetu;
  bool v47;
  bool v48;
  dds3ProcessID_t *v49;
  bool v51;
  bool v53;
  dds3ProcessID_t *v54;
  s32 v57;
  bool v58;
  dds3ProcessID_t *v59;
  SBTLUNIT_LISTWORK *v61;
  s32 count;
  s32 v64;
  bool v65;
  dds3ProcessID_t *v66;
  dds3ProcessID_t *v68;
  dds3ProcessID_t *v69;
  bool v70;
  bool v71;
  bool v72;
  dds3ProcessID_t *v73;
  bool v76;
  dds3ProcessID_t *v77;
  bool v79;
  dds3ProcessID_t *v80;
  bool v82;
  dds3ProcessID_t *v83;

  if (wk->encountno == 514)
  {
    if (evtBitCheck(688) && !evtBitCheck(689))
      goto LABEL_43;
  }
  if (wk->encountno == 23)
  {
    if (evtBitCheck(684) && !evtBitCheck(685))
      goto LABEL_43;
  }
  if (wk->encountno != 22)
    goto LABEL_21;
  if (!evtBitCheck(686) || evtBitCheck(687))
  {
LABEL_21:
    v6 = wk;
    if (v6->battlemode == 3)
    {
      menuPID = wk->menuPID;
      itfMenuSetFlagMenu(menuPID, 1, 2, 0);
      itfMenuSetFlagMenu(wk->menuPID, 2, 2, 0);
      itfMenuSetFlagMenu(wk->menuPID, 3, 2, 0);
      itfMenuSetFlagMenu(wk->menuPID, 6, 2, 0);
      itfMenuSetFlagMenu(wk->menuPID, 4, 2, 0);
      v9 = wk;
      UnitMng = v9->UnitMng;
      playerID = v9->playerID;
      v12 = sBtlSearchUnit_ID(UnitMng, playerID);
      para = v12->para;
      BadStatus = sBtlGetBadStatus(para);
      TargetList = sBtlCreateTargetList(2);
      if (TargetList)
      {
        v17 = TargetList->count > 0;
LABEL_34:
        v19 = ChkEnableBadStatus(v12, 7, BadStatus, v17);
        v20 = wk->menuPID;
        itfMenuSetFlagMenu(v20, 7, 2, v19);
        num = wk->itemList->num;
        v24 = ChkEnableBadStatus(v12, 5, BadStatus, num > 0);
        v25 = wk->menuPID;
        itfMenuSetFlagMenu(v25, 5, 2, v24);
        ChkEnableDecideEscape(wk);
        itfMenuSetFlagMenu(wk->menuPID, 17, 2, 1);
        return;
      }
      else
      {
        v17 = 0;
        goto LABEL_34;
      }
      goto LABEL_34;
    }
    v6 = wk;
    v27 = v6->UnitMng;
    v28 = v6->playerID;
    v29 = sBtlSearchUnit_ID(v27, v28);
    v30 = v29->para;
    v32 = sBtlGetBadStatus(v30);
    if (!sBtlIsMeirei(v29))
      goto LABEL_68;
    if (sBtlIsStart(0))
    {
LABEL_65:
      v35 = 1;
LABEL_70:
      v37 = v35 & sBtlChkTutorialMenu(1);
      v38 = wk->menuPID;
      itfMenuSetFlagMenu(v38, 1, 2, v37);
      v39 = sBtlCheckSummonUnit();
      v40 = v39 != 1;
      if (sBtlCheckSummonUnit_Dead_or_ALive(0))
      {
        goto LABEL_77;
      }
      if (sBtlCheckSummonUnit_Dead_or_ALive(1))
        v71 = v39 == 1;
      else
        v71 = 1;
      v40 = !v71;
LABEL_77:
      enemy_zenmetu = wk->enemy_zenmetu;
      v47 = !enemy_zenmetu & ~EventBattleStopChack(sBtlMenu) & v40;
      v48 = ChkEnableBadStatus(v29, 2, v32, v47);
      v49 = wk->menuPID;
      itfMenuSetFlagMenu(v49, 2, 2, v48);
      if (wk->member_num >= 1)
      {
        v51 = !sBtlCheckTutorialBattle();
LABEL_87:
        v53 = ChkEnableBadStatus(v29, 3, v32, v51);
        v54 = wk->menuPID;
        itfMenuSetFlagMenu(v54, 3, 2, v53);
        v57 = wk->itemList->num;
        v58 = ChkEnableBadStatus(v29, 5, v32, v57 > 0);
        v59 = wk->menuPID;
        itfMenuSetFlagMenu(v59, 5, 2, v58);
        v61 = sBtlCreateTargetList(2);
        if (v61)
        {
          count = v61->count;
          goto LABEL_99;
        }
        count = 0;
LABEL_99:
        v64 = wk->katanaList->num;
        v65 = ChkEnableBadStatus(v29, 6, v32, v64 > 1);
        v66 = wk->menuPID;
        itfMenuSetFlagMenu(v66, 6, 2, v65);
        if (wk->battlemode == 1)
        {
          v68 = wk->menuPID;
          v69 = v68;
          v70 = 0;
LABEL_132:
          itfMenuSetFlagMenu(v69, 7, 2, v70);
          ChkEnableDecideEscape(wk);
          v76 = sBtlChkTutorialMenu(17);
          v77 = wk->menuPID;
          itfMenuSetFlagMenu(v77, 17, 2, v76);
          v79 = sBtlChkTutorialMenu(18);
          v80 = wk->menuPID;
          itfMenuSetFlagMenu(v80, 18, 2, v79);
          v82 = sBtlChkTutorialMenu(19);
          v83 = wk->menuPID;
          itfMenuSetFlagMenu(v83, 19, 2, v82);
          sBtlDeleteUnitList(v61, 0);
          return;
        }
        v72 = ChkEnableBadStatus(v29, 7, v32, count > 0);
        v73 = wk->menuPID;
        v70 = v72;
        v69 = v73;
        goto LABEL_132;
      }
      v51 = 0;
      goto LABEL_87;
    }
    if (sBtlIsStart(1))
      goto LABEL_65;
LABEL_68:
    v35 = 0;
    goto LABEL_70;
  }
LABEL_43:
  TutorialMenuCtrl(wk);
}

// 0x1f2f870
static void TutorialMenuCtrl(sBtlMenu_t *wk) {
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  itfMenuSetFlagMenu(menuPID, 1, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 2, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 3, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 6, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 7, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 8, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 18, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 5, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 17, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 19, 2, 1);
}

// 0x1f2fab0
static bool EventBattleStopChack(sBtlMenu_t *wk) {
  s32 encountno;
  s64 v4;
  s32 v5;
  SBTLUNIT_WORK *i;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v9;
  s32 devilid;

  encountno = wk->encountno;
  if (encountno != 48)
  {
    if (encountno != 52)
      return 0;
  }
  v4 = 0;
  v5 = 0;
  for (i = 0; ; i = pUnit)
  {
    UnitMng = wk->UnitMng;
    if (v4 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v4]->pUnit;
    if (!pUnit)
      goto LABEL_12;
    if ((pUnit->side & 2) != 0 && pUnit->para->now->hp >= 1)
    {
      v9 = sBtlCheckDamageTarget(pUnit);
      v5 += v9;
    }
    devilid = (u16)pUnit->para->devilid;
    if (devilid != 297 && devilid != 290)
LABEL_12:
      pUnit = i;
    ++v4;
  }
  return v5 == 1 && i && i->Itimoku_CloseEye && !i->Itimoku_CloseCnt;
}

// 0x1f2f9c0
bool sBtlIsMeirei(SBTLUNIT_WORK *wklock) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  _BOOL4 v5;

  if (!wklock)
    goto LABEL_12;
  if (!CheckLiveTarget(wklock))
    goto LABEL_12;
  para = wklock->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus <= 0xD)
    return (0xA3Fu >> BadStatus) & 1;
LABEL_12:
  LOBYTE(v5) = 1;
  return v5;
}

// 0x1f2ea10
static bool ChkEnableBadStatus(SBTLUNIT_WORK *wklock, SBTL_MENU_ID menu_id, BST bstno, bool bSel) {
  s32 v5;
  bool result;
  bool v11;
  char v12;
  u32 v13;
  char v15;
  u32 v16;
  bool v17;
  s32 v18;
  bool v20;

  v5 = bSel;
  if (!wklock)
    return v5 & 1;
  if (!CheckLiveTarget(wklock))
    return v5 & 1;
  switch (menu_id)
  {
    case 1:
      v11 = sBtlChkTutorialMenu(1);
      v12 = bstno - 6;
      LOBYTE(v5) = v11 & v5;
      if (bstno - 6 >= 8)
        return v5 & 1;
      v13 = 215;
      return (((v13 >> v12) & 1) == 0) & v5;
    case 2:
      v5 &= sBtlChkTutorialMenu(2);
      LOBYTE(v5) = (wk->battlemode != 1) & v5;
      v15 = bstno - 6;
      if (bstno - 6 >= 0xB)
        return v5 & 1;
      v16 = 1239;
      goto LABEL_33;
    case 3:
      v17 = sBtlChkTutorialMenu(3);
      v12 = bstno - 6;
      LOBYTE(v5) = v17 & v5;
      if (bstno - 6 >= 0xB)
        return v5 & 1;
      v13 = 1239;
      return (((v13 >> v12) & 1) == 0) & v5;
    case 5:
      v18 = 5;
      goto LABEL_29;
    case 6:
      v18 = 6;
LABEL_29:
      v5 &= sBtlChkTutorialMenu(v18);
      LOBYTE(v5) = (wk->battlemode != 1) & v5;
      v15 = bstno - 6;
      if (bstno - 6 >= 8)
        return v5 & 1;
      v16 = 199;
LABEL_33:
      if (((v16 >> v15) & 1) != 0)
        LOBYTE(v5) = 0;
      result = v5 & 1;
      break;
    case 7:
      return sBtlChkTutorialMenu(7) & v5 & 1;
    case 8:
      v20 = sBtlChkTutorialMenu(8);
      v12 = bstno - 6;
      LOBYTE(v5) = v20 & v5;
      if (bstno - 6 >= 8)
        return v5 & 1;
      v13 = 223;
      return (((v13 >> v12) & 1) == 0) & v5;
    default:
      return v5 & 1;
  }
  return result;
}

// 0x1f2fcc0
void Init(sBtlMenu_t *wk) {
  dds3ProcessID_t *inited;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *v11;
  DevilSkillCsr *v12;
  SBTLUNIT_WORK *v14;
  sdatUnitWork_t *v16;

  inited = sBtlInitMenuPID(8u);
  wk->menuPID = inited;
  v5 = sBtlInitMenuPID(0x20u);
  wk->listPID = v5;
  v7 = sBtlInitMenuPID(0x20u);
  wk->charPID = v7;
  v9 = sBtlInitMenuPID(2u);
  wk->nakamaPID = v9;
  v11 = sBtlInitMenuPID(0x20u);
  wk->stockPID = v11;
  v12 = Allocate(DevilSkillCsr);
  _ctor(v12, 0);
  devilSkillcsr = v12;
  v14 = NewSpecific(SBTLUNIT_WORK, 0x20u);
  EnemyUnitTgt = v14;
  v16 = NewSpecific(sdatUnitWork_t, 0x20u);
  stockUnitTgt = v16;
  if (!sBtlCheckTutorialBattle())
    return;
  g_bitMoon |= 4u;
}

// 0x1f1d7d0
static void SetCommand(sBtlMenu_t *wk) {
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *menuPID;
  s32 battlemode;
  dds3ProcessID_t *v12;
  char *MenuStr;
  char *LocalizeText;
  itfMenuFunc_t v15;
  char *v16;
  dds3ProcessID_t *v17;
  u32 v18;
  char *v19;
  char *v20;
  itfMenuFunc_t v21;
  dds3ProcessID_t *v22;
  s32 v23;
  dds3ProcessID_t *v24;
  char *v25;
  char *v26;
  itfMenuFunc_t v27;
  dds3ProcessID_t *v30;
  char *v31;
  char *v32;
  itfMenuFunc_t v33;
  dds3ProcessID_t *v34;
  char **v36;
  dds3ProcessID_t *v38;
  char *v39;
  char *v40;
  itfMenuFunc_t v41;
  dds3ProcessID_t *v42;
  char *v43;
  char *v44;
  itfMenuFunc_t v45;
  dds3ProcessID_t *v46;
  char *v48;
  char *v49;
  itfMenuFunc_t v50;
  dds3ProcessID_t *v51;
  char *v53;
  char *v54;
  itfMenuFunc_t v55;
  dds3ProcessID_t *v56;
  char *v58;
  char *v59;
  itfMenuFunc_t v60;
  dds3ProcessID_t *v61;
  char *v63;
  char *v64;
  itfMenuFunc_t v65;
  dds3ProcessID_t *v66;
  char *v68;
  char *v69;
  itfMenuFunc_t v70;
  dds3ProcessID_t *v72;
  char *v73;
  char *v74;
  itfMenuFunc_t v75;
  dds3ProcessID_t *v76;
  char *v77;
  char *v78;
  itfMenuFunc_t v79;
  char *v80;
  dds3ProcessID_t *v82;
  char *v83;
  char *v84;
  itfMenuFunc_t v85;
  dds3ProcessID_t *v86;
  char *v88;
  char *v89;
  itfMenuFunc_t v90;
  dds3ProcessID_t *v92;
  char *v93;
  char *v94;
  itfMenuFunc_t v95;
  char *v97;
  dds3ProcessID_t *v98;
  s32 v99;
  char *v100;
  itfMenuFunc_t v101;
  dds3ProcessID_t *v102;
  char *v104;

  p_menuPID = &wk->menuPID;
  menuPID = wk->menuPID;
  itfMenuClearMenuAll(menuPID);
  dds3GetProcessData(&wk->menuPID);
  battlemode = (u16)wk->battlemode;
  if (battlemode == 3)
  {
    if (shortcutFlag)
    {
      if (evtBitCheck(2093))
      {
        v12 = p_menuPID;
        MenuStr = sBtlGetMenuStr(7);
        LocalizeText = GetLocalizeText(MenuStr, 1);
        v15 = Allocate(itfMenuFunc_t);
        _ctor(v15, 0, Method_Project_sBtlMenu_FuncAnalyze__, 0);
        v16 = "";
LABEL_118:
        v98 = v12;
        v99 = 7;
LABEL_122:
        itfMenuSetRootMenu(v98, v99, LocalizeText, v15, v16);
        goto LABEL_123;
      }
      goto LABEL_123;
    }
    if (wk->type == 1)
    {
      v24 = p_menuPID;
      v25 = sBtlGetMenuStr(1);
      v26 = GetLocalizeText(v25, 1);
      v27 = Allocate(itfMenuFunc_t);
      _ctor(v27, 0, Method_Project_sBtlMenu_FuncStart__, 0);
      itfMenuSetRootMenu(v24, 16, v26, v27, "");
      if (!evtBitCheck(2093))
      {
LABEL_39:
        if (wk->type)
          goto LABEL_40;
        goto LABEL_81;
      }
    }
    else if (!evtBitCheck(2093))
    {
      goto LABEL_39;
    }
    v72 = p_menuPID;
    v73 = sBtlGetMenuStr(7);
    v74 = GetLocalizeText(v73, 1);
    v75 = Allocate(itfMenuFunc_t);
    _ctor(v75, 0, Method_Project_sBtlMenu_FuncAnalyze__, 0);
    itfMenuSetRootMenu(v72, 7, v74, v75, "");
    if (wk->type)
    {
LABEL_40:
      v30 = p_menuPID;
LABEL_42:
      v31 = sBtlGetMenuStr(8);
      v32 = GetLocalizeText(v31, 1);
      v33 = Allocate(itfMenuFunc_t);
      _ctor(v33, 0, Method_Project_sBtlMenu_FuncEscape__, 0);
      itfMenuSetRootMenu(v30, 8, v32, v33, "");
      v34 = p_menuPID;
      if (evtBitCheck(42))
      {
        v36 = &str_sBtlMenu[17];
      }
      else
      {
        v36 = &"CMP_MENU_L0043";
      }
LABEL_121:
      v100 = GetLocalizeText(*v36, 1);
      v101 = Allocate(itfMenuFunc_t);
      _ctor(v101, 0, Method_Project_sBtlMenu_FuncDitectiveBook__, 0);
      itfMenuSetRootMenu(v34, 17, v100, v101, "");
      v102 = p_menuPID;
      v104 = sBtlGetMenuStr(20);
      LocalizeText = GetLocalizeText(v104, 1);
      v15 = Allocate(itfMenuFunc_t);
      _ctor(v15, 0, Method_Project_sBtlMenu_FuncConfig__, 0);
      v16 = "";
      v99 = 19;
      v98 = v102;
      goto LABEL_122;
    }
LABEL_81:
    v76 = p_menuPID;
    v77 = sBtlGetMenuStr(6);
    v78 = GetLocalizeText(v77, 1);
    v79 = Allocate(itfMenuFunc_t);
    _ctor(v79, 0, Method_Project_sBtlMenu_FuncItem__, 0);
    itfMenuSetRootMenu(v76, 5, v78, v79, "");
    v30 = p_menuPID;
    goto LABEL_42;
  }
  if (!shortcutFlag)
  {
    if (evtBitCheck(2093))
    {
      v38 = p_menuPID;
      v39 = sBtlGetMenuStr(7);
      v40 = GetLocalizeText(v39, 1);
      v41 = Allocate(itfMenuFunc_t);
      _ctor(v41, 0, Method_Project_sBtlMenu_FuncAnalyze__, 0);
      itfMenuSetRootMenu(v38, 7, v40, v41, "");
    }
    v42 = p_menuPID;
    v43 = sBtlGetMenuStr(6);
    v44 = GetLocalizeText(v43, 1);
    v45 = Allocate(itfMenuFunc_t);
    _ctor(v45, 0, Method_Project_sBtlMenu_FuncItem__, 0);
    itfMenuSetRootMenu(v42, 5, v44, v45, "");
    v46 = p_menuPID;
    v48 = sBtlGetMenuStr(3);
    v49 = GetLocalizeText(v48, 1);
    v50 = Allocate(itfMenuFunc_t);
    _ctor(v50, 0, Method_Project_sBtlMenu_FuncSummon__, 0);
    itfMenuSetRootMenu(v46, 2, v49, v50, "");
    v51 = p_menuPID;
    v53 = sBtlGetMenuStr(19);
    v54 = GetLocalizeText(v53, 1);
    v55 = Allocate(itfMenuFunc_t);
    _ctor(v55, 0, Method_Project_sBtlMenu_FuncKuzunohaDirect__, 0);
    itfMenuSetRootMenu(v51, 18, v54, v55, "");
    v56 = p_menuPID;
    v58 = sBtlGetMenuStr(2);
    v59 = GetLocalizeText(v58, 1);
    v60 = Allocate(itfMenuFunc_t);
    _ctor(v60, 0, Method_Project_sBtlMenu_FuncMeirei__, 0);
    itfMenuSetRootMenu(v56, 1, v59, v60, "");
    v61 = p_menuPID;
    v63 = sBtlGetMenuStr(18);
    v64 = GetLocalizeText(v63, 1);
    v65 = Allocate(itfMenuFunc_t);
    _ctor(v65, 0, Method_Project_sBtlMenu_FuncKatana__, 0);
    itfMenuSetRootMenu(v61, 6, v64, v65, "");
    v66 = p_menuPID;
    v68 = sBtlGetMenuStr(8);
    v69 = GetLocalizeText(v68, 1);
    v70 = Allocate(itfMenuFunc_t);
    _ctor(v70, 0, Method_Project_sBtlMenu_FuncEscape__, 0);
    itfMenuSetRootMenu(v66, 8, v69, v70, "");
    v34 = p_menuPID;
    if (evtBitCheck(42))
    {
      v36 = &str_sBtlMenu[17];
    }
    else
    {
      v36 = &"CMP_MENU_L0043";
    }
    goto LABEL_121;
  }
  v17 = wk->menuPID;
  if (wk->type == 1)
  {
    if (!v18)
    v19 = sBtlGetMenuStr(1);
    v20 = GetLocalizeText(v19, 1);
    v21 = Allocate(itfMenuFunc_t);
    _ctor(v21, 0, Method_Project_sBtlMenu_FuncStart__, 0);
    v22 = v17;
    v23 = 16;
  }
  else
  {
    if (!v18)
    v80 = sBtlGetMenuStr(2);
    v20 = GetLocalizeText(v80, 1);
    v21 = Allocate(itfMenuFunc_t);
    _ctor(v21, 0, Method_Project_sBtlMenu_FuncMeirei__, 0);
    v22 = v17;
    v23 = 1;
  }
  itfMenuSetRootMenu(v22, v23, v20, v21, "");
  v82 = p_menuPID;
  v83 = sBtlGetMenuStr(3);
  v84 = GetLocalizeText(v83, 1);
  v85 = Allocate(itfMenuFunc_t);
  _ctor(v85, 0, Method_Project_sBtlMenu_FuncSummon__, 0);
  itfMenuSetRootMenu(v82, 2, v84, v85, "");
  v86 = wk->menuPID;
  v88 = sBtlGetMenuStr(4);
  v89 = GetLocalizeText(v88, 1);
  v90 = Allocate(itfMenuFunc_t);
  _ctor(v90, 0, Method_Project_sBtlMenu_FuncReturn__, 0);
  itfMenuSetRootMenu(v86, 3, v89, v90, "");
  if (!wk->type)
  {
    v92 = p_menuPID;
    v93 = sBtlGetMenuStr(6);
    v94 = GetLocalizeText(v93, 1);
    v95 = Allocate(itfMenuFunc_t);
    _ctor(v95, 0, Method_Project_sBtlMenu_FuncItem__, 0);
    itfMenuSetRootMenu(v92, 5, v94, v95, "");
  }
  if (evtBitCheck(2093))
  {
    v12 = p_menuPID;
    v97 = sBtlGetMenuStr(7);
    LocalizeText = GetLocalizeText(v97, 1);
    v15 = Allocate(itfMenuFunc_t);
    _ctor(v15, 0, Method_Project_sBtlMenu_FuncAnalyze__, 0);
    v16 = "";
    goto LABEL_118;
  }
LABEL_123:
  *(u64 *)&wk->FadeInDelay = 0;
  *(u64 *)&wk->short_cut_id = 0x100000000LL;
}

// 0x1f2fec0
void sBtlCallProcEnd(sBtlMenu_t *wk) {
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *p_listPID;
  dds3ProcessID_t *p_charPID;
  dds3ProcessID_t *p_nakamaPID;
  dds3ProcessID_t *p_stockPID;
  dds3ProcessID_t *stockPID;

  p_menuPID = &wk->menuPID;
  menuPID = wk->menuPID;
  itfMenuProcessEnd(menuPID);
  p_listPID = &wk->listPID;
  itfMenuProcessEnd(wk->listPID);
  p_charPID = &wk->charPID;
  itfMenuProcessEnd(wk->charPID);
  p_nakamaPID = &wk->nakamaPID;
  itfMenuProcessEnd(wk->nakamaPID);
  stockPID = wk->stockPID;
  p_stockPID = &wk->stockPID;
  itfMenuProcessEnd(stockPID);
  *(p_stockPID - 4) = 0;
  p_listPID = 0;
  p_charPID = 0;
  p_nakamaPID = 0;
  p_stockPID = 0;
}

// 0x1f2ffc0
u8 sBtlCheckProcEnd(sBtlMenu_t *wk) {
  dds3ProcessID_t *menuPID;
  bool v4;
  dds3ProcessID_t *listPID;
  bool v6;
  dds3ProcessID_t *charPID;
  bool v8;
  dds3ProcessID_t *nakamaPID;
  bool v10;
  dds3ProcessID_t *stockPID;

  menuPID = wk->menuPID;
  v4 = itfMenuProcessCheck(menuPID);
  listPID = wk->listPID;
  v6 = itfMenuProcessCheck(listPID);
  charPID = wk->charPID;
  v8 = itfMenuProcessCheck(charPID);
  nakamaPID = wk->nakamaPID;
  v10 = itfMenuProcessCheck(nakamaPID);
  stockPID = wk->stockPID;
  return v6 + v4 + v8 + v10 + itfMenuProcessCheck(stockPID);
}

// 0x1f300f0
bool sBtlChkCallEnd(sBtlMenu_t *wk) {
  bool result;
  void *Instance;
  dds3ProcessID_t *charPID;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *nakamaPID;
  dds3ProcessID_t *v10;
  dds3ProcessID_t *listPID;
  dds3ProcessID_t *v12;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v14;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *stockPID;
  dds3ProcessID_t *v18;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;
  void *v22;
  void *v28;
  dds3ProcessID_t *monitor;
  dds3ProcessID_t *v31;
  dds3ProcessID_t *klass;
  dds3ProcessID_t *v34;
  void *v37;

  if (wk->step == 1)
  {
    if (!CHECK_TRIG(20494, 1))
      return 0;
  }
  else if (!CHECK_TRIG(42510, 1))
  {
    return 0;
  }
  Instance = get_Instance(0);
  if (!!MenuMoveChack(Instance, 0))
    return 0;
  switch (wk->step)
  {
    case 2:
      menuPID = wk->menuPID;
      if (!itfMenuProcessCheck(menuPID))
        return 0;
      v14 = wk->menuPID;
      if (itfMenuGetCtrlType(v14) != 1)
        return 0;
      v8 = wk->menuPID;
      goto LABEL_51;
    case 3:
    case 0xC:
      listPID = wk->listPID;
      if (!itfMenuProcessCheck(listPID))
        return 0;
      v12 = wk->listPID;
      if (itfMenuGetCtrlType(v12) != 1)
        return 0;
      v8 = wk->listPID;
      goto LABEL_51;
    case 4:
    case 5:
    case 9:
    case 0xA:
      charPID = wk->charPID;
      if (!itfMenuProcessCheck(charPID))
        return 0;
      v7 = wk->charPID;
      if (itfMenuGetCtrlType(v7) != 1)
        return 0;
      v8 = wk->charPID;
      goto LABEL_51;
    case 6:
    case 7:
      nakamaPID = wk->nakamaPID;
      if (!itfMenuProcessCheck(nakamaPID))
        return 0;
      v10 = wk->nakamaPID;
      if (itfMenuGetCtrlType(v10) != 1)
        return 0;
      v8 = wk->nakamaPID;
      goto LABEL_51;
    case 8:
      ProcessData = dds3GetProcessData(g_mainPID);
      if (!ProcessData)
        goto LABEL_87;
      goto LABEL_85;
      if (!ProcessData)
LABEL_85:
LABEL_87:
      switch (HIDWORD(ProcessData[3].klass))
      {
        case 2:
          monitor = ProcessData[1].monitor;
          if (itfMenuGetCtrlType(monitor) != 1)
            return 0;
          v31 = ProcessData[1].monitor;
          break;
        case 3:
          klass = ProcessData[2].klass;
          if (itfMenuGetCtrlType(klass) != 1)
            return 0;
          v31 = ProcessData[2].klass;
          break;
        case 4:
          v34 = ProcessData[2].monitor;
          if (itfMenuGetCtrlType(v34) != 1)
            return 0;
          v31 = ProcessData[2].monitor;
          break;
        case 5:
          if (MenuCnt < 15)
            return 0;
          v31 = ProcessData[2].klass;
          break;
        default:
          return 0;
      }
      itfMenuCallEnd(v31);
      orderMenuCtrl = 1;
LABEL_54:
      wk->flag |= 0x20u;
      SE(1);
      result = 1;
      break;
    case 0xB:
      stockPID = wk->stockPID;
      if (!itfMenuProcessCheck(stockPID))
        return 0;
      v18 = wk->stockPID;
      if (itfMenuGetCtrlType(v18) != 1)
        return 0;
      v8 = wk->stockPID;
LABEL_51:
      itfMenuCallEnd(v8);
      goto LABEL_54;
    case 0xD:
      v19 = wk->charPID;
      if (!itfMenuProcessCheck(v19))
        return 0;
      v20 = wk->charPID;
      if (itfMenuGetCtrlType(v20) != 1)
        return 0;
      v21 = wk->charPID;
      itfMenuSetFlag(v21, 8, 1);
      itfMenuCallEnd(wk->charPID);
      v22 = (loc_1F38220)(0);
      EndAnimInfo(v22, 0);
      wk->modeSq = 0;
      goto LABEL_54;
    case 0x12:
      if (AnalizeCnt <= 29)
      {
        AnalizeCnt = AnalizeCnt + 1;
        return 0;
      }
      if (!AnalizeClose)
      {
        if (infotype == 3)
        {
          v28 = (loc_1F38220)(0);
          EndAnimInfo(v28, 0);
        }
        else
        {
          v37 = get_Instance(0);
          MenuClose(v37->devil_info2, 0);
        }
        wk->modeSq = 0;
        infotype = 0;
        devilSkillcsr->statusSkillCsr = 0;
        AnalizeClose = 1;
        goto LABEL_54;
      }
      return 0;
    default:
      return 0;
  }
  return result;
}

// 0x1f308a0
dds3ProcessFunc_t sBtlProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  dds3ProcessFunc_t Nakama;
  dds3Basic_t *v10;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  dds3Basic_t *ActiveScene;
  void *Instance;
  void *v23;
  void *v24;
  dds3ProcessID_t *monitor;
  void *v26;
  void *v27;
  s32 v30;
  s32 klass_high;
  s32 v38;
  void *v41;
  dds3ProcessID_t *v42;
  void *v44;
  s32 v47;
  dds3ProcessID_t *v48;
  s32 v50;
  void *v51;
  dds3ProcessID_t *v59;
  SBATTLE_WORK *wk_local;
  dds3ProcessID_t *v64;
  SBTLITEM_TBL *p_item_keep;
  s32 v69;
  dds3ProcessID_t *v70;
  void *v71;
  void *v72;
  void *v74;
  void *v78;
  dds3ProcessID_t *v79;
  s32 v84;
  u32 v85;
  dds3ProcessID_t *v86;
  s32 v90;
  s32 stock_num;
  s32 v92;
  s32 v93;
  void *v96;
  dds3ProcessID_t *v97;
  void *v98;
  bool ShortCutFlg;
  void *v102;
  void *v104;
  Il2CppObject *v106;
  long f64 v107;
  s64 v108;
  s64 v109;
  void *v110;
  void *v112;
  dds3ProcessID_t *v113;
  void *v114;
  dds3ProcessID_t *v115;
  s32 v116;
  dds3ProcessID_t *v124;
  s32 v125;
  void *v126;
  s32 v131;
  dds3ProcessID_t *v132;
  void *v133;
  dds3ProcessID_t *v134;
  s32 v135;
  s32 v137;
  s32 v138;
  s32 v140;
  s32 v142;
  SBATTLE_WORK *v143;
  SBTLUNIT_WORK *PChara;
  s64 j;
  SBTLITEM_LISTWORK *katanaList;
  s32 v150;
  s32 swordno;
  void *v152;
  dds3ProcessID_t *v153;
  dds3ProcessID_t *v154;
  void *v157;
  dds3ProcessID_t *v159;
  s32 count;
  bool v161;
  s64 v165;
  void *v166;
  bool EffectData_Decode;
  s32 v169;
  DevilSkillCsr *v171;
  void *v172;
  dds3ProcessID_t *v176;
  s32 v177;
  s32 monitor_low;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  dds3ProcessID_t *v195;
  s32 v202;
  dds3ProcessID_t *v203;
  s32 v207;
  s32 v208;
  dds3ProcessID_t *v209;
  dds3ProcessID_t *v210;
  s32 v211;
  bool v212;
  s32 v213;
  u32 monitor_high;
  dds3ProcessID_t *v215;
  void *v217;
  s32 SelectRootID;
  void *v220;
  void *v221;
  void *v222;
  s32 v225;
  s32 *v226;
  s32 v227;
  s32 v229;
  s32 *v230;
  s32 v231;
  dds3ProcessID_t *v232;
  s32 v234;
  void *v235;
  void *v236;
  void *v237;
  s32 v240;
  s32 v241;
  void *v244;
  s32 v247;
  s32 v248;
  s32 v250;
  void *devil_info2;
  dds3ProcessID_t *v254;
  s32 SelectID;
  s32 v258;
  void *v259;
  dds3ProcessID_t *v262;
  s32 v263;
  s32 v267;
  s32 v268;
  s32 v270;
  dds3ProcessID_t *v271;
  s32 v274;
  s32 v277;
  s32 v278;
  s32 v279;
  s32 v281;
  void *v282;
  s32 v284;
  void *v286;
  void *v287;
  void *v292;
  void *v294;
  dds3ProcessID_t *v298;
  void *v300;
  SBTLITEM_TBL *v302;
  void *v306;
  void *v308;
  SBTLITEM_TBL *v314;
  dds3ProcessID_t *v316;
  void *v318;
  void *v319;
  dds3ProcessID_t *v320;
  void *v321;
  bool v322;
  dds3ProcessID_t *v323;
  s32 CtrlType;
  s32 v326;
  s32 *v327;
  s32 v328;
  dds3ProcessID_t *v329;
  SBATTLE_WORK *v331;
  dds3ProcessID_t *v333;
  dds3ProcessID_t *v335;
  void *v338;
  dds3ProcessID_t *v339;
  s32 v340;
  void *v346;
  s32 v348;
  s32 v350;
  s32 i;
  s32 devilid;
  void *v356;
  void *v358;
  void *v361;
  s32 v368;
  void *v371;
  s32 v372;
  s32 v373;
  void *v378;
  void *v379;
  void *v386;
  void *v387;
  s32 v390;
  void *v391;
  dds3ProcessID_t *v394;
  s32 v395;
  void *v397;
  SBATTLE_WORK *v398;
  void *v402;
  void *v407;
  void *v408;
  void *v410;
  void *v411;
  void *v412;
  dds3ProcessID_t *v413;
  s32 v414;
  SBTLITEM_TBL *v416;
  s32 v419;
  dds3ProcessID_t *v423;
  s32 v427;
  s32 v429;
  s32 cursorMax[2];
  dds3ProcessID_t *id;

  id = PID;
  *(u64 *)cursorMax = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[4].klass;
  if (klass == 22)
  {
LABEL_31:
    Nakama = 0;
    if (!ProcessCheck())
    {
      lmapSetBattleDestDisp(1);
      ActiveScene = dds3GetActiveScene();
      bookscene = ActiveScene;
      if (wk->battlemode == 1)
      {
        sBtlReturnCamera();
        ProcessData[6].monitor = 0x1E00000002LL;
LABEL_53:
        menu_onoff = 0;
        Instance = get_Instance(0);
        BattleDispUIOn(Instance, 0);
        v23 = get_Instance(0);
        CanvasAllActive(v23, 1, 0);
        v24 = get_Instance(0);
        DevilHPactive(v24, 1, 0);
        monitor = ProcessData[1].monitor;
        itfMenuStart(monitor);
        LODWORD(ProcessData[4].klass) = 2;
        v26 = get_Instance(0);
        SetBattleMenuGuide(v26, 1, 0, 0);
        v27 = get_Instance(0);
        BackIconState(v27, 0);
        return 0;
      }
      ProcessData[6].monitor = 0x1E00000002LL;
      goto LABEL_53;
    }
    return Nakama;
  }
  if (klass == 21)
  {
    Nakama = 0;
    if (dds3FadeCheck())
      return Nakama;
    lmapSetBattleDestDisp(0);
    menu_onoff = 1;
    v10 = dds3GetActiveScene();
    bookscene = v10;
    v12 = get_Instance(0);
    BattleDispUI(v12, 0, 0);
    v13 = get_Instance(0);
    RememberIconState(v13, 0);
    v14 = get_Instance(0);
    CanvasAllActive(v14, 0, 0);
    v15 = get_Instance(0);
    DevilHPactive(v15, 0, 0);
    ProcessStart(2);
    LODWORD(ProcessData[4].klass) = 22;
    goto LABEL_31;
  }
  if (CalcKuzunohaDirect(ProcessData))
    return 0;
  if (!!CalcConfig(ProcessData))
    return 0;
  v30 = ProcessData[4].klass;
  switch (v30)
  {
    case 0:
LABEL_64:
      Nakama = 0;
      if (!sBtlCheckLoadFlg())
        return Nakama;
      LoadLocalizeText();
      Init();
LABEL_68:
      Nakama = 0;
      goto LABEL_69;
    case 19:
LABEL_81:
      if (LOWORD(ProcessData[4].monitor))
      {
        goto LABEL_83;
      }
      else
      {
        sBtlCallProcEnd(ProcessData);
LABEL_83:
        if (sBtlCheckProcEnd(ProcessData))
          goto LABEL_84;
        goto LABEL_90;
      }
      if (sBtlCheckProcEnd(ProcessData))
      {
LABEL_84:
        LOWORD(v38) = ProcessData[4].monitor;
LABEL_85:
        Nakama = 0;
        LOWORD(ProcessData[4].monitor) = v38 + 1;
        return Nakama;
      }
LABEL_90:
      Nakama = 0;
      LOWORD(ProcessData[4].monitor) = 0;
      LODWORD(ProcessData[4].klass) = 20;
      return Nakama;
    case 20:
    case 28:
      break;
    default:
      if (HIDWORD(ProcessData[5].klass))
        break;
      if (sBtlChkCallEnd(ProcessData))
      {
        Nakama = 0;
        HIDWORD(ProcessData[4].klass) |= 0x20u;
        return Nakama;
      }
      v30 = ProcessData[4].klass;
      break;
  }
  Nakama = 0;
  switch (v30)
  {
    case 0:
      goto LABEL_64;
    case 1:
      if (MenuCnt > 24)
      {
        klass_high = HIDWORD(ProcessData[4].klass);
        if ((klass_high & 0x10) == 0)
        {
LABEL_80:
          Nakama = 0;
          HIDWORD(ProcessData[4].klass) = klass_high & 0xFFFFFFFD;
          return Nakama;
        }
LABEL_440:
        if (wk->smnCtrl->bNoOk && HIDWORD(ProcessData[5].klass) == 1)
          return 0;
        HIDWORD(ProcessData[4].klass) = HIDWORD(ProcessData[4].klass) & 0xFFFFFFCD | 2;
        if (shortcutFlag)
        {
          shortcutFlag = 0;
          MenuShortCutFarst = 0;
        }
        SetCommand(ProcessData);
        sBtlChkEnableDecideMenu(ProcessData);
        dds3GetProcessData(&ProcessData[1].monitor);
        v202 = HIDWORD(ProcessData[5].klass);
        v203 = ProcessData[1].monitor;
        itfMenuSetFlag(v203, 0x8000, v202 == 1);
        RootMenuReturn(1);
        Nakama = 0;
        LODWORD(ProcessData[5].monitor) = 0;
        return Nakama;
      }
      MenuCnt = MenuCnt + 1;
      klass_high = HIDWORD(ProcessData[4].klass);
      if ((klass_high & 0x10) == 0)
        goto LABEL_80;
      goto LABEL_440;
    case 2:
      if (MenuCnt < 20)
        goto LABEL_98;
      v41 = get_Instance(0);
      if (MenuMoveChack(v41, 0))
      {
LABEL_98:
        ++MenuCnt;
        v42 = ProcessData[1].monitor;
        goto LABEL_425;
      }
      v210 = ProcessData[1].monitor;
      itfMenuSetFlag(v210, 8, 1);
      v211 = ProcessData[6].monitor;
      v212 = __OFSUB__(v211, 1);
      v213 = v211 - 1;
      if (v213 < 0 == v212)
      {
        LODWORD(ProcessData[6].monitor) = v213;
        if (!v213)
        {
          monitor_high = HIDWORD(ProcessData[6].monitor);
          dds3FadeIn(0, 0, 0, monitor_high);
        }
        return 0;
      }
      v333 = ProcessData[1].monitor;
      if (itfMenuGetWaitType(v333) == 4)
        goto LABEL_431;
      Nakama = 0;
      if (!CHECK_TRIG(4098, 1))
        return Nakama;
      if (HIDWORD(ProcessData[5].klass) == 1)
      {
        if (wk->member_num >= 1)
        {
          Nakama = 0;
          if (!evtBitCheck(42))
            return Nakama;
          v335 = ProcessData[1].monitor;
          itfMenuFrcCancel(v335);
        }
      }
      return 0;
    case 3:
      if (MenuCnt < 20)
        goto LABEL_108;
      v44 = get_Instance(0);
      if (MenuMoveChack(v44, 0))
      {
LABEL_108:
        ++MenuCnt;
        v42 = ProcessData[2].klass;
        goto LABEL_425;
      }
      v215 = ProcessData[2].klass;
      itfMenuSetFlag(v215, 8, 1);
      MenuShortCutFarst = 0;
      Nakama = 0;
      if (itfMenuGetWaitType(ProcessData[2].klass) != 4)
        return Nakama;
      v217 = get_Instance(0);
      Nakama = 0;
      if (MenuMoveChack(v217, 0))
        return Nakama;
      SelectRootID = GetSelectRootID();
      v220 = get_Instance(0);
      CloseCommonMenu(v220, SelectRootID, 0, 0);
      if (SelectRootID == 6)
      {
        v221 = get_Instance(0);
        RaidouBeforWeaPon(v221, 0, 0);
        v222 = get_Instance(0);
        RaidouGaugeCtr(v222, 0, 0);
      }
      MenuCnt = 0;
      goto LABEL_123;
    case 4:
      v47 = MenuCnt;
      if (v47 <= 14)
        goto LABEL_275;
      v48 = ProcessData[2].monitor;
      itfMenuSetFlag(v48, 8, 1);
      Nakama = 0;
      if (itfMenuGetWaitType(ProcessData[2].monitor) != 4)
        return Nakama;
      v50 = GetSelectRootID();
      v51 = get_Instance(0);
      CloseCommonMenu(v51, v50, 0, 0);
      goto LABEL_123;
    case 5:
      v47 = MenuCnt;
      if (v47 <= 14)
        goto LABEL_275;
      v59 = ProcessData[2].monitor;
      itfMenuSetFlag(v59, 8, 1);
      Nakama = 0;
      if (itfMenuGetWaitType(ProcessData[2].monitor) != 4)
        return Nakama;
      wk_local = wk;
      wk_local->status &= ~0x80000u;
      if ((BYTE4(ProcessData[4].klass) & 0x20) == 0)
      {
        MenuCnt = 0;
        sBtlChkEnableDecideMenu(ProcessData);
        v64 = ProcessData[2].klass;
        itfMenuStart(v64);
        LODWORD(ProcessData[4].klass) = 3;
        p_item_keep = &wk->item_keep;
        p_item_keep = 0;
        goto LABEL_699;
      }
      goto LABEL_875;
    case 6:
      v69 = MenuCnt;
      if (v69 <= 14)
        goto LABEL_414;
      v70 = ProcessData[3].klass;
      itfMenuSetFlag(v70, 8, 1);
      if (itfMenuGetWaitType(ProcessData[3].klass) == 4)
      {
        v71 = get_Instance(0);
        CloseCommonMenu(v71, 3, 0, 0);
        v72 = get_Instance(0);
        MenuClose(v72->devil_info2, 0);
        devilInfo = 0;
        v74 = get_Instance(0);
        CharIconCtr(v74, 0, 0);
        wk->status &= ~0x80000u;
        if ((BYTE4(ProcessData[4].klass) & 0x20) != 0)
          goto LABEL_474;
        sBtlChkEnableDecideMenu(ProcessData);
        if (!RootMenuReturn(0))
        {
          goto LABEL_165;
        }
        goto LABEL_700;
      }
      if (!CHECK_TRIG(4107, 1))
        goto LABEL_1013;
      if (devilInfo)
      {
        v226 = (s32 *)&ProcessData[6].klass + 1;
        v225 = HIDWORD(ProcessData[6].klass);
        if (v225 <= 1)
          v227 = v225 + 1;
        else
          v227 = 0;
      }
      else
      {
LABEL_1013:
        if (!CHECK_TRIG(4104, 1))
          goto LABEL_573;
        if (!devilInfo)
        {
LABEL_573:
          Nakama = 0;
          if (!CHECK_TRIG(42498, 1))
            return Nakama;
          if (devilInfo)
          {
            v254 = ProcessData[3].klass;
            SelectID = itfMenuGetSelectID(v254);
            devilSkillcsr->statusSkillCsr = 1;
            SE(0);
            itfMenuSetFlag(ProcessData[3].klass, 8, 0);
            itfMenuSetFlagMenu(ProcessData[3].klass, SelectID, 8, 1);
            LODWORD(ProcessData[4].klass) = 17;
            Nakama = 0;
            menuBeforFlag = 2;
            return Nakama;
          }
          return 0;
        }
        v226 = (s32 *)&ProcessData[6].klass + 1;
        v250 = HIDWORD(ProcessData[6].klass);
        v212 = __OFSUB__(v250, 1);
        v227 = v250 - 1;
        if (v227 < 0 != v212)
          v227 = 2;
      }
      *v226 = v227;
      SE(9);
      devil_info2 = get_Instance(0)->devil_info2;
      MenuChange(devil_info2, animChengeTbl[*v226], 0);
      goto LABEL_573;
    case 7:
      v69 = MenuCnt;
      if (v69 <= 14)
      {
LABEL_414:
        v69 = MenuCnt;
        MenuCnt = v69 + 1;
        v42 = ProcessData[3].klass;
        goto LABEL_425;
      }
      v79 = ProcessData[3].klass;
      itfMenuSetFlag(v79, 8, 1);
      if (itfMenuGetWaitType(ProcessData[3].klass) == 4)
      {
        wk->status &= ~0x80000u;
        v84 = GetSelectRootID();
        if ((BYTE4(ProcessData[4].klass) & 0x20) == 0)
        {
          if (!v85)
          sBtlChkEnableDecideMenu(ProcessData);
          v86 = ProcessData[2].monitor;
          itfMenuStart(v86);
          MenuCnt = 0;
          LODWORD(ProcessData[4].klass) = 9;
          v90 = 8 * g_nakamaTab;
          stock_num = wk->stock_num;
          v92 = v90 + 8;
          if (!Exists("new_devil"))
          {
            for (i = 0; ; ++i)
            {
              if (i >= wk->stock_num)
                break;
              devilid = sBtlGetStockUnitData(i)->devilid;
              stock_num -= sBtlIsDLCDevil(devilid);
            }
          }
          if (v92 >= stock_num)
            v93 = stock_num;
          else
            v93 = v92;
          sBtlGetNakama(0);
          sBtlGetNakama(1);
          if (v93 < 8)
            ++v93;
          itfMenuSetInitSelectID(ProcessData[2].monitor, 0);
          GetSelectRootID();
          v96 = get_Instance(0);
          v97 = ProcessData[2].monitor;
          v98 = v96;
          ShortCutFlg = sBtlGetShortCutFlg();
          OpenCommonMenu(v98, v97, 0, v84, 0, v93, ShortCutFlg, 0);
          if (!devilInfo)
          {
            if (!returnFlag)
            {
              v102 = get_Instance(0);
              MenuOpne(v102->devil_info2, 2, 2, 0);
              HIDWORD(ProcessData[6].klass) = 0;
              devilInfo = 1;
              v104 = get_Instance(0);
              CharIconCtr(v104, 1, 0);
            }
          }
          returnFlag = 0;
          goto LABEL_700;
        }
        if (!v85)
        sBtlCallEnd(ProcessData);
        v286 = get_Instance(0);
        CloseCommonMenu(v286, v84, 0, 0);
        if (devilInfo)
        {
          v287 = get_Instance(0);
          MenuClose(v287->devil_info2, 0);
          devilInfo = 0;
        }
LABEL_700:
LABEL_701:
        sBtlResetColor_Select();
        return 0;
      }
      if (!CHECK_TRIG(4107, 1))
        goto LABEL_1014;
      if (devilInfo)
      {
        v230 = (s32 *)&ProcessData[6].klass + 1;
        v229 = HIDWORD(ProcessData[6].klass);
        if (v229 <= 1)
          v231 = v229 + 1;
        else
          v231 = 0;
      }
      else
      {
LABEL_1014:
        if (!CHECK_TRIG(4104, 1))
          goto LABEL_593;
        if (!devilInfo)
          goto LABEL_593;
        v230 = (s32 *)&ProcessData[6].klass + 1;
        v258 = HIDWORD(ProcessData[6].klass);
        v212 = __OFSUB__(v258, 1);
        v231 = v258 - 1;
        if (v231 < 0 != v212)
          v231 = 2;
      }
      *v230 = v231;
      SE(9);
      v259 = get_Instance(0)->devil_info2;
      MenuChange(v259, animChengeTbl[*v230], 0);
LABEL_593:
      Nakama = 0;
      if (!CHECK_TRIG(42498, 1))
        return Nakama;
      if (!devilInfo)
        return 0;
      v262 = ProcessData[3].klass;
      v263 = itfMenuGetSelectID(v262);
      devilSkillcsr->statusSkillCsr = 1;
      SE(0);
      itfMenuSetFlag(ProcessData[3].klass, 8, 0);
      itfMenuSetFlagMenu(ProcessData[3].klass, v263, 8, 1);
      LODWORD(ProcessData[4].klass) = 17;
      Nakama = 0;
      menuBeforFlag = 3;
      return Nakama;
    case 8:
      if ((BYTE4(ProcessData[4].klass) & 0x20) != 0)
      {
        if (orderMenuCtrl)
        {
          v106 = dds3GetProcessData(g_mainPID);
          v108 = sub_83F0(v106, S_CmndMenuNew, v107);
          switch (*(u32 *)(v108 + 52))
          {
            case 2:
              v109 = v108;
              v110 = get_Instance(0);
              CloseSkillMenu(v110, 0, 0, *(u8 *)(v109 + 49), 0);
              break;
            case 3:
              if (devilInfo)
              {
                goto LABEL_788;
              }
              break;
            case 4:
              v356 = get_Instance(0);
              BattleMenuClose(v356, 0, 0);
              if (devilInfo)
              {
LABEL_788:
                v358 = get_Instance(0);
                MenuClose(v358->devil_info2, 0);
                goto LABEL_800;
              }
              break;
            case 5:
              v361 = get_Instance(0);
              CloseHuumaInfo(v361, 0);
              if (devilInfo)
              {
LABEL_800:
                devilInfo = 0;
              }
              break;
            default:
              break;
          }
          infotype = 0;
          sBtlEnd();
          wk->status &= ~0x80000u;
          sBtlCallEnd(ProcessData);
        }
      }
      if (sBtlGetStat() == 2)
      {
        if (!CHECK_TRIG(4107, 1))
          goto LABEL_837;
        if (!devilInfo)
          goto LABEL_837;
        if (infotype == 2)
        {
          v368 = HIDWORD(ProcessData[6].klass);
          if (v368 > 1)
          {
            HIDWORD(ProcessData[6].klass) = 0;
            skilltype = 0;
LABEL_924:
            SE(9);
LABEL_925:
            if (infotype)
              return 0;
            HIDWORD(ProcessData[6].klass) = 2;
            Nakama = 0;
            skilltype = 2;
            return Nakama;
          }
          v373 = v368 + 1;
        }
        else
        {
LABEL_837:
          if (!CHECK_TRIG(4104, 1))
            goto LABEL_840;
          if (!devilInfo)
            goto LABEL_840;
          if (infotype != 2)
          {
LABEL_840:
            if (CHECK_TRIG(42498, 1))
            {
              if (devilInfo)
              {
                if (infotype == 2)
                {
                  devilSkillcsr->statusSkillCsr = 1;
                  LODWORD(ProcessData[4].klass) = 17;
                  SE(0);
                  menuBeforFlag = 4;
                  wk->modeSq = 1;
                }
              }
            }
            goto LABEL_925;
          }
          v372 = HIDWORD(ProcessData[6].klass);
          v373 = v372 - 1;
          if (v372 < 1)
            v373 = 2;
        }
        HIDWORD(ProcessData[6].klass) = v373;
        skilltype = v373;
        goto LABEL_924;
      }
      if (sBtlChkDecide())
      {
        HIDWORD(ProcessData[4].klass) &= ~0x10u;
        if (infotype == 3)
        {
          v371 = (loc_1F38220)(0);
          EndAnimInfo(v371, 0);
        }
        else
        {
          v378 = get_Instance(0);
          MenuClose(v378->devil_info2, 0);
          v379 = get_Instance(0);
          CharIconCtr(v379, 0, 0);
        }
        infotype = 0;
        HIDWORD(ProcessData[6].klass) = 2;
        Nakama = 0;
        skilltype = 2;
        devilInfo = 0;
LABEL_69:
        LODWORD(ProcessData[4].klass) = 1;
        return Nakama;
      }
      if (orderMenuCtrl)
      {
LABEL_855:
        Nakama = 0;
        orderMenuCtrl = 0;
        return Nakama;
      }
      sBtlChkEnableDecideMenu(ProcessData);
      RootMenuReturn(0);
      goto LABEL_855;
    case 9:
      if (MenuCnt < 20)
        goto LABEL_227;
      v112 = get_Instance(0);
      if (MenuMoveChack(v112, 0))
      {
LABEL_227:
        goto LABEL_277;
      }
      v232 = ProcessData[2].monitor;
      itfMenuSetFlag(v232, 8, 1);
      if (itfMenuGetWaitType(ProcessData[2].monitor) == 4)
      {
        v234 = GetSelectRootID();
        v235 = get_Instance(0);
        CloseCommonMenu(v235, v234, 0, 0);
        v236 = get_Instance(0);
        MenuClose(v236->devil_info2, 0);
        devilInfo = 0;
        v237 = get_Instance(0);
        CharIconCtr(v237, 0, 0);
LABEL_123:
        wk->status &= ~0x80000u;
        if ((BYTE4(ProcessData[4].klass) & 0x20) == 0)
        {
          sBtlChkEnableDecideMenu(ProcessData);
          if (!RootMenuReturn(0))
          {
LABEL_165:
            sBtlCallEnd(ProcessData);
            v78 = get_Instance(0);
            SetBattleMenuGuide(v78, 0, 0, 0);
          }
          goto LABEL_700;
        }
LABEL_474:
LABEL_476:
        sBtlCallEnd(ProcessData);
        goto LABEL_700;
      }
      v323 = ProcessData[2].monitor;
      CtrlType = itfMenuGetCtrlType(v323);
      Nakama = 0;
      if (CtrlType != 1)
        return Nakama;
      if (!CHECK_TRIG(4107, 1))
        goto LABEL_1015;
      if (devilInfo)
      {
        v327 = (s32 *)&ProcessData[6].klass + 1;
        v326 = HIDWORD(ProcessData[6].klass);
        if (v326 <= 1)
          v328 = v326 + 1;
        else
          v328 = 0;
      }
      else
      {
LABEL_1015:
        if (!CHECK_TRIG(4104, 1))
          goto LABEL_898;
        if (!devilInfo)
        {
LABEL_898:
          Nakama = 0;
          if (!CHECK_TRIG(42498, 1))
            return Nakama;
          if (devilInfo)
          {
            v394 = ProcessData[2].monitor;
            v395 = itfMenuGetSelectID(v394);
            devilSkillcsr->statusSkillCsr = 1;
            itfMenuSetFlag(ProcessData[2].monitor, 8, 0);
            itfMenuSetFlagMenu(ProcessData[2].monitor, v395, 8, 1);
            LODWORD(ProcessData[4].klass) = 17;
            SE(0);
            Nakama = 0;
            menuBeforFlag = 1;
            return Nakama;
          }
          return 0;
        }
        v327 = (s32 *)&ProcessData[6].klass + 1;
        v390 = HIDWORD(ProcessData[6].klass);
        v212 = __OFSUB__(v390, 1);
        v328 = v390 - 1;
        if (v328 < 0 != v212)
          v328 = 2;
      }
      *v327 = v328;
      SE(9);
      v391 = get_Instance(0)->devil_info2;
      MenuChange(v391, animChengeTbl[*v327], 0);
      goto LABEL_898;
    case 10:
      v47 = MenuCnt;
      if (v47 <= 19)
      {
LABEL_275:
LABEL_277:
        v47 = MenuCnt;
        MenuCnt = v47 + 1;
        v42 = ProcessData[2].monitor;
        goto LABEL_425;
      }
      v113 = ProcessData[2].monitor;
      itfMenuSetFlag(v113, 8, 1);
      if (itfMenuGetWaitType(ProcessData[2].monitor) != 4)
        goto LABEL_239;
      v114 = get_Instance(0);
      if (MenuMoveChack(v114, 0))
      {
LABEL_239:
        v115 = ProcessData[2].monitor;
        v116 = itfMenuGetCtrlType(v115);
        Nakama = 0;
        if (v116 != 1)
          return Nakama;
        if (g_nakamaTabMov)
        {
          if (CHECK_TRIG(4107, 1))
          {
            if (devilInfo)
            {
              if (infotype == 2)
                goto LABEL_295;
            }
          }
          if (CHECK_TRIG(4104, 1))
          {
            if (devilInfo)
            {
              if (infotype == 2)
                goto LABEL_636;
            }
          }
          Nakama = 0;
          if (!CHECK_TRIG(42498, 1))
            return Nakama;
          if (devilInfo)
          {
            if (infotype == 2)
            {
              v124 = ProcessData[2].monitor;
              v125 = itfMenuGetSelectID(v124);
              v126 = get_Instance(0);
              GuideSet(v126, "BTL005", 0, 90, 0);
              devilSkillcsr->statusSkillCsr = 1;
              itfMenuSetFlag(ProcessData[2].monitor, 8, 0);
              itfMenuSetFlagMenu(ProcessData[2].monitor, v125, 8, 1);
              LODWORD(ProcessData[4].klass) = 17;
              wk->modeSq = 1;
              SE(0);
              Nakama = 0;
              menuBeforFlag = 6;
              return Nakama;
            }
          }
        }
        return 0;
      }
      wk->status &= ~0x80000u;
      v292 = get_Instance(0);
      MenuClose(v292->devil_info2, 0);
      devilInfo = 0;
      v294 = get_Instance(0);
      CharIconCtr(v294, 0, 0);
      g_nakamaTab = 0;
      if ((BYTE4(ProcessData[4].klass) & 0x20) == 0)
      {
        MenuCnt = 0;
        sBtlChkEnableDecideMenu(ProcessData);
        v298 = ProcessData[2].klass;
        itfMenuStart(v298);
        LODWORD(ProcessData[4].klass) = 3;
        v300 = get_Instance(0);
        GuideSet(v300, "BTL001", 0, 90, 0);
        v302 = &wk->item_keep;
        v302 = 0;
        goto LABEL_699;
      }
      goto LABEL_873;
    case 11:
      v131 = MenuCnt;
      if (v131 <= 19)
      {
        v131 = MenuCnt;
        MenuCnt = v131 + 1;
        v42 = ProcessData[3].monitor;
LABEL_425:
        itfMenuSetFlag(v42, 8, 0);
        return 0;
      }
      v132 = ProcessData[3].monitor;
      itfMenuSetFlag(v132, 8, 1);
      if (itfMenuGetWaitType(ProcessData[3].monitor) == 4)
      {
        v133 = get_Instance(0);
        if (!MenuMoveChack(v133, 0))
        {
          wk->status &= ~0x80000u;
          v306 = get_Instance(0);
          MenuClose(v306->devil_info2, 0);
          devilInfo = 0;
          HIDWORD(ProcessData[6].klass) = 2;
          v308 = get_Instance(0);
          CharIconCtr(v308, 0, 0);
          g_nakamaTab = 0;
          if ((BYTE4(ProcessData[4].klass) & 0x20) == 0)
          {
            if (itemIdSave == 17)
              goto LABEL_1016;
            if (itemIdSave == 18)
            {
LABEL_1016:
              MenuCnt = 0;
              itemIdSave = 0;
              v314 = &wk->item_keep;
              v314 = 0;
              sBtlChkEnableDecideMenu(ProcessData);
              v316 = ProcessData[2].klass;
              itfMenuStart(v316);
              LODWORD(ProcessData[4].klass) = 3;
              v318 = get_Instance(0);
              GuideSet(v318, "BTL001", 0, 90, 0);
LABEL_699:
              v319 = get_Instance(0);
              v320 = ProcessData[2].klass;
              v321 = v319;
              v322 = sBtlGetShortCutFlg();
              OpenItemMenu(v321, v320, 0, 5, 0, 8, v322, 0);
            }
            else
            {
              MenuCnt = 0;
              itemIdSave = 0;
              v416 = &wk->item_keep;
              v416 = 0;
              sBtlChkEnableDecideMenu(ProcessData);
              sBtlFuncDecideItem();
              LODWORD(ProcessData[4].klass) = 10;
            }
            goto LABEL_700;
          }
LABEL_873:
          wk_local = wk;
LABEL_875:
          wk_local->item_keep = 0;
          goto LABEL_476;
        }
      }
      v134 = ProcessData[3].monitor;
      v135 = itfMenuGetCtrlType(v134);
      Nakama = 0;
      if (v135 == 1)
      {
        if (!CHECK_TRIG(4107, 1))
          goto LABEL_1017;
        if (devilInfo)
        {
LABEL_295:
          v137 = HIDWORD(ProcessData[6].klass);
          if (v137 <= 1)
            v138 = v137 + 1;
          else
            v138 = 0;
        }
        else
        {
LABEL_1017:
          if (!CHECK_TRIG(4104, 1))
            goto LABEL_751;
          if (!devilInfo)
          {
LABEL_751:
            Nakama = 0;
            if (CHECK_TRIG(42498, 1))
            {
              v339 = ProcessData[2].monitor;
              v340 = itfMenuGetSelectID(v339);
              wk->modeSq = 1;
              devilSkillcsr->statusSkillCsr = 1;
              v346 = get_Instance(0);
              GuideSet(v346, "BTL005", 0, 90, 0);
              itfMenuSetFlag(ProcessData[3].monitor, 8, 0);
              itfMenuSetFlagMenu(ProcessData[3].monitor, v340, 8, 1);
              LODWORD(ProcessData[4].klass) = 17;
              SE(0);
              Nakama = 0;
              menuBeforFlag = 7;
            }
            return Nakama;
          }
LABEL_636:
          v281 = HIDWORD(ProcessData[6].klass);
          v212 = __OFSUB__(v281, 1);
          v138 = v281 - 1;
          if (v138 < 0 != v212)
            v138 = 2;
        }
        HIDWORD(ProcessData[6].klass) = v138;
        SE(9);
        v282 = get_Instance(0)->devil_info2;
        MenuChange(v282, animChengeTbl[SHIDWORD(ProcessData[6].klass)], 0);
        return 0;
      }
      return Nakama;
    case 12:
      v140 = sBtlDatType(wk->equipsord);
      v142 = sBtlDatType(g_equipNo);
      sBtlPlayerMagSdLcAxEff_WeaponCng_FromMenu(v140, v142);
      v143 = wk;
      v143->weaponId = g_equipNo;
      v143->equipsord = g_equipNo;
      datSetPlayerSword(g_equipNo, 0);
      PChara = sBtlGetPChara();
      datCalcNowParam(PChara->para, g_equipNo, 0);
      datDvlParaUpdate(0);
      for (j = 0; ; ++j)
      {
        katanaList = wk->katanaList;
        if (j >= katanaList->num)
          break;
        katanaList = wk->katanaList;
        v150 = katanaList->data[j]->id;
        swordno = GBWK->player->swordno;
        v152 = get_Instance(0);
        RaidouGaugeCtr(v152, 0, 0);
        v153 = ProcessData[2].klass;
        itfMenuSetFlagMenu(v153, j, 2, v150 - 144 != swordno);
      }
      MenuCnt = 0;
      g_equipNoOld = -1;
      SE(57);
      sBtlChkEnableDecideMenu(ProcessData);
      v195 = ProcessData[2].klass;
      itfMenuStart(v195);
      LODWORD(ProcessData[4].klass) = 3;
      goto LABEL_701;
    case 13:
      if ((BYTE4(ProcessData[4].klass) & 0x20) != 0)
      {
        wk->status &= ~0x80000u;
LABEL_431:
LABEL_886:
        sBtlCallEnd(ProcessData);
        return 0;
      }
      if (!LOWORD(ProcessData[4].monitor))
      {
        if (CHECK_TRIG(4097, 1))
        {
          if (!wk->modeSq)
          {
            SE(1);
            LOWORD(ProcessData[4].monitor) = 1;
          }
        }
        v240 = ProcessData[5].klass;
        Nakama = 0;
        if (v240 + 1 < 10)
          v241 = v240 + 1;
        else
          v241 = 10;
        LODWORD(ProcessData[5].klass) = v241;
        return Nakama;
      }
      if ((wk->mag & 0x80000000) == 0)
      {
        v154 = ProcessData[2].monitor;
LABEL_324:
        itfMenuSetFlag(v154, 8, 1);
        itfMenuSetFlagMenu(ProcessData[2].monitor, -1, 8, 0);
        ButtonLineHelpDispSet(1);
        LOWORD(ProcessData[4].monitor) = 0;
        LODWORD(ProcessData[5].klass) = 0;
        MenuCnt = 0;
        LODWORD(ProcessData[4].klass) = 4;
        v157 = get_Instance(0);
        v159 = ProcessData[2].monitor;
        count = wk->tgtList->count;
        v161 = sBtlGetShortCutFlg();
        OpenCommonMenu(v157, v159, 0, 7, 0, count, v161, 0);
        return 0;
      }
      v329 = ProcessData[2].monitor;
      itfMenuSetFlagMenu(v329, -1, 2, 0);
      v154 = ProcessData[2].monitor;
      goto LABEL_324;
    case 14:
      if (tips_proc)
      {
        Nakama = 0;
        if (!tipsProcessCheck())
        {
          tips_proc = 0;
          sub_1B34170(675, 0);
          sub_1A21FE0(676, 0, v165);
          v166 = get_Instance(0);
          GuideOnOff(v166, 1, 0);
          return 0;
        }
        return Nakama;
      }
      if (sBtlGetStat() == 2)
      {
        if (!CHECK_TRIG(11, 1))
          goto LABEL_602;
        if (!devilInfo)
          goto LABEL_602;
        if (infotype == 2)
        {
          v207 = HIDWORD(ProcessData[6].klass);
          if (v207 <= 1)
          {
            v208 = v207 + 1;
            HIDWORD(ProcessData[6].klass) = v207 + 1;
          }
          else
          {
            v208 = 0;
            HIDWORD(ProcessData[6].klass) = 0;
          }
          skilltype = v208;
          v419 = HIDWORD(ProcessData[6].klass);
          skilltype = v419;
          SE(9);
        }
        else
        {
LABEL_602:
          if (CHECK_TRIG(4104, 1))
          {
            if (devilInfo)
            {
              v267 = HIDWORD(ProcessData[6].klass);
              v268 = v267 - 1;
              if (v267 < 1)
                v268 = 2;
              HIDWORD(ProcessData[6].klass) = v268;
              skilltype = v268;
              SE(9);
              v270 = HIDWORD(ProcessData[6].klass);
              skilltype = v270;
            }
          }
        }
        Nakama = 0;
        if (!CHECK_TRIG(42498, 1))
          return Nakama;
        if (devilInfo)
        {
          if (infotype == 2)
          {
            devilSkillcsr->statusSkillCsr = 1;
            LODWORD(ProcessData[4].klass) = 17;
            SE(0);
            menuBeforFlag = 5;
            Nakama = 0;
            wk->modeSq = 1;
            return Nakama;
          }
        }
      }
      else
      {
        if (sBtlChkDecide())
        {
          HIDWORD(ProcessData[4].klass) |= 0x40u;
          if (infotype == 3)
          {
            v244 = (loc_1F38220)(0);
            EndAnimInfo(v244, 0);
          }
          else
          {
            v386 = get_Instance(0);
            MenuClose(v386->devil_info2, 0);
            v387 = get_Instance(0);
            CharIconCtr(v387, 0, 0);
          }
          devilInfo = 0;
          goto LABEL_886;
        }
        sBtlChkEnableDecideMenu(ProcessData);
        if (!RootMenuReturn(0))
        {
          sBtlCallEnd(ProcessData);
          if (infotype == 3)
          {
            v338 = (loc_1F38220)(0);
            EndAnimInfo(v338, 0);
          }
          else
          {
            v410 = get_Instance(0);
            MenuClose(v410->devil_info2, 0);
          }
          v411 = get_Instance(0);
          MenuClose(v411->devil_info2, 0);
          v412 = get_Instance(0);
          SetBattleMenuGuide(v412, 0, 0, 0);
        }
      }
      return 0;
    case 16:
      Nakama = (dds3ProcessFunc_t)sBtlGetNakama(wk->ctrlSmnIdx);
      if (Nakama)
      {
        EffectData_Decode = sBtlLoadEffectData_Decode(Nakama);
        Nakama = 0;
        if (EffectData_Decode)
        {
          Nakama = 0;
          v169 = HIDWORD(ProcessData[4].klass) | 0x10;
          LODWORD(ProcessData[4].klass) = 1;
          HIDWORD(ProcessData[4].klass) = v169;
        }
      }
      return Nakama;
    case 17:
      if (LOWORD(ProcessData[4].monitor))
      {
        v171 = devilSkillcsr;
        v171->statusSkillCsr = 0;
        CursorClear(v171, 0);
        v172 = get_Instance(0);
        DevilStatusBasicCsrOff(v172, 0);
        MenuCnt = 0;
        SE(1);
        if (menuBeforFlag == 1)
        {
          v176 = ProcessData[2].monitor;
          itfMenuSetFlag(v176, 8, 1);
          itfMenuSetFlagMenu(ProcessData[2].monitor, -1, 8, 0);
          v177 = 9;
LABEL_619:
          LODWORD(ProcessData[4].klass) = v177;
          menuBeforFlag = 0;
          LOWORD(ProcessData[4].monitor) = 0;
          goto LABEL_622;
        }
        if (menuBeforFlag == 3)
        {
          v209 = ProcessData[3].klass;
          itfMenuSetFlag(v209, 8, 1);
          itfMenuSetFlagMenu(ProcessData[3].klass, -1, 8, 0);
          v177 = 7;
          goto LABEL_619;
        }
        if (menuBeforFlag == 2)
        {
          v271 = ProcessData[3].klass;
          itfMenuSetFlag(v271, 8, 1);
          itfMenuSetFlagMenu(ProcessData[3].klass, -1, 8, 0);
          v177 = 6;
          goto LABEL_619;
        }
        if (menuBeforFlag == 4)
        {
          v350 = 8;
        }
        else
        {
          if (menuBeforFlag != 5)
          {
            if (menuBeforFlag == 6)
            {
              v413 = ProcessData[2].monitor;
              itfMenuSetFlag(v413, 8, 1);
              itfMenuSetFlagMenu(ProcessData[2].monitor, -1, 8, 0);
              v414 = 10;
            }
            else
            {
              if (menuBeforFlag != 7)
                goto LABEL_622;
              v423 = ProcessData[3].monitor;
              itfMenuSetFlag(v423, 8, 1);
              itfMenuSetFlagMenu(ProcessData[3].monitor, -1, 8, 0);
              v414 = 11;
            }
            LODWORD(ProcessData[4].klass) = v414;
LABEL_998:
            menuBeforFlag = 0;
            LOWORD(ProcessData[4].monitor) = 0;
            wk->modeSq = 0;
LABEL_622:
            *(u64 *)cursorMax = 0;
            v274 = HIDWORD(ProcessData[6].klass);
            GetStatusCsrCnt(v274, &cursorMax[1], cursorMax, unitCsr, 0);
            if (devilSkillcsr->statusSkillCsr)
            {
              v278 = cursorMax[0];
              v277 = cursorMax[1];
              v279 = animChengeTbl[SHIDWORD(ProcessData[6].klass)];
              SkillListCursorUpdate(v277, v278, v279, 0);
            }
            return 0;
          }
          v350 = 14;
        }
        LODWORD(ProcessData[4].klass) = v350;
        goto LABEL_998;
      }
      if (CHECK_TRIG(4097, 1))
      {
        LOWORD(ProcessData[4].monitor) = 1;
        goto LABEL_622;
      }
      if (!CHECK_TRIG(4107, 1))
        goto LABEL_1018;
      if (devilInfo)
      {
        v247 = HIDWORD(ProcessData[6].klass);
        if (v247 > 1)
        {
          v248 = 0;
          HIDWORD(ProcessData[6].klass) = 0;
LABEL_933:
          skilltype = v248;
          SE(9);
          CursorClear(devilSkillcsr, 0);
          v402 = get_Instance(0);
          MenuChange(v402->devil_info2, animChengeTbl[SHIDWORD(ProcessData[6].klass)], 0);
          goto LABEL_622;
        }
        v248 = v247 + 1;
      }
      else
      {
LABEL_1018:
        if (!CHECK_TRIG(4104, 1))
          goto LABEL_622;
        if (!devilInfo)
          goto LABEL_622;
        v284 = HIDWORD(ProcessData[6].klass);
        v248 = v284 - 1;
        if (v284 < 1)
          v248 = 2;
      }
      HIDWORD(ProcessData[6].klass) = v248;
      goto LABEL_933;
    case 18:
      if (AnalizeCnt <= 29)
      {
        Nakama = 0;
        AnalizeCnt = AnalizeCnt + 1;
        return Nakama;
      }
      if ((BYTE4(ProcessData[4].klass) & 0x20) != 0)
      {
        wk->status &= ~0x80000u;
        sBtlCallEnd(ProcessData);
        Nakama = 0;
        AnalizeCnt = 0;
        return Nakama;
      }
      monitor_low = SLOWORD(ProcessData[4].monitor);
      if (LOWORD(ProcessData[4].monitor))
      {
        if (monitor_low < 100)
        {
          if (RootMenuReturn(0))
          {
            tgtList = wk->tgtList;
            if (tgtList)
            {
              tgtList = wk->tgtList;
              sBtlDeleteUnitList(tgtList, 0);
              p_tgtList = &wk->tgtList;
              p_tgtList = 0;
            }
            ButtonLineHelpDispSet(1);
          }
          else
          {
            sBtlCallEnd(ProcessData);
            v397 = get_Instance(0);
            SetBattleMenuGuide(v397, 0, 0, 0);
          }
          LOWORD(ProcessData[4].monitor) = 0;
          HIDWORD(ProcessData[8].klass) = 0;
          v398 = wk;
          v398->modeSq = 0;
          v398->status &= ~0x80000u;
          LODWORD(ProcessData[5].klass) = 0;
          enemyNowCsr = 0;
          if (infotype == 3)
          {
            v407 = (loc_1F38220)(0);
            EndAnimInfo(v407, 0);
          }
          else
          {
            v408 = get_Instance(0);
            MenuClose(v408->devil_info2, 0);
          }
          Nakama = 0;
          infotype = 0;
          return Nakama;
        }
        LODWORD(ProcessData[5].klass) = 10;
        LOWORD(monitor_low) = ProcessData[4].monitor;
        v348 = (u16)monitor_low + 1;
        wk->modeSq = 0;
        LOWORD(ProcessData[4].monitor) = v348;
        if (v348 << 16 >= 7012352)
        {
          Nakama = 0;
          AnalizeClose = 1;
          LOWORD(ProcessData[4].monitor) = 1;
          return Nakama;
        }
      }
      else
      {
        if (CHECK_TRIG(4097, 1))
        {
          v331 = wk;
          if (!v331->modeSq)
          {
            v331 = wk;
            if ((v331->status & 0x80000) != 0)
            {
              SE(1);
              if (HIDWORD(ProcessData[5].monitor))
              {
                HIDWORD(ProcessData[8].klass) = 1;
                LOWORD(ProcessData[4].monitor) = 100;
                wk->modeSq = 1;
              }
              else
              {
                AnalizeClose = 1;
                HIDWORD(ProcessData[8].klass) = 0;
                LOWORD(ProcessData[4].monitor) = 1;
              }
            }
          }
        }
        v427 = ProcessData[5].klass;
        if (v427 + 1 < 10)
          v429 = v427 + 1;
        else
          v429 = 10;
        LODWORD(ProcessData[5].klass) = v429;
        sBtlAnalizeEnemySel();
      }
      return 0;
    case 19:
      goto LABEL_81;
    case 20:
      v38 = SLOWORD(ProcessData[4].monitor);
      if (!LOWORD(ProcessData[4].monitor))
      {
        HIDWORD(ProcessData[4].klass) &= ~2u;
        goto LABEL_85;
      }
      if (v38 < 2)
        goto LABEL_85;
      Nakama = 0;
      LOWORD(ProcessData[4].monitor) = 0;
      LODWORD(ProcessData[4].klass) = 28;
      return Nakama;
    case 25:
      if (!tips_proc)
        return 0;
      Nakama = 0;
      if (tipsProcessCheck())
        return Nakama;
      tips_proc = 0;
      goto LABEL_68;
    case 26:
      if (!script_proc)
        return 0;
      if (dds3GetProcessStat(script_proc) != 3)
      {
        Nakama = 0;
        if (dds3GetProcessStat(script_proc))
        {
          return Nakama;
        }
      }
      script_proc = 0;
      LODWORD(ProcessData[4].klass) = 1;
      MOON_IN();
      return 0;
    case 27:
      MenuItemScrUpdate(ProcessData);
      return 0;
    case 28:
      Nakama = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(Nakama, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return Nakama;
    default:
      return Nakama;
  }
}

// 0x1f34a20
void MenuItemScrUpdate(sBtlMenu_t *wk) {
  dds3ProcessID_t *listPID;
  void *Instance;
  SBTLITEM_TBL *p_item_keep;
  void *v10;
  dds3ProcessID_t *v11;
  void *v12;
  bool ShortCutFlg;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  s32 v17;

  if (wk->itemScr)
  {
    if (dds3GetProcessStat(&wk->itemScr) != 3)
    {
      if (dds3GetProcessStat(&wk->itemScr))
        return;
    }
    wk->itemScr = 0;
    wk->itemScrReq = -1;
    if ((wk->flag & 0x20) == 0)
    {
      sBtlChkEnableDecideMenu(wk);
      listPID = wk->listPID;
      itfMenuStart(listPID);
      wk->step = 3;
      MenuCnt = 0;
      Instance = get_Instance(0);
      GuideSet(Instance, "BTL001", 0, 90, 0);
      p_item_keep = &wk->item_keep;
      p_item_keep = 0;
      v10 = get_Instance(0);
      v11 = wk->listPID;
      v12 = v10;
      ShortCutFlg = sBtlGetShortCutFlg();
      OpenItemMenu(v12, v11, 0, 5, 0, 8, ShortCutFlg, 0);
      if (wk->scrItem != 9)
        goto LABEL_22;
      goto LABEL_27;
    }
    sBtlCallEnd(wk);
    if (wk->scrItem == 9)
      goto LABEL_27;
    goto LABEL_9000;
    if (wk->scrItem == 9)
    {
LABEL_27:
      PlayerID = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(PlayerID);
      if (sBtlKuisibariChk(PlayerUnit))
        v17 = 0x20000000;
      else
        v17 = 0;
      PlayerUnit->status = PlayerUnit->status & 0xDFFFFFFF | v17;
      wk->scrItem = 0;
      return;
    }
LABEL_9000:
LABEL_22:
    wk->scrItem = 0;
  }
}

// 0x1f34d30
void sBtlRelease(sBtlMenu_t *wk) {
  ;
}

// 0x1f34d40
void sBtlShutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void **p_monitor;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  ProcessData[7].monitor = 0;
  p_monitor = &ProcessData[7].monitor;
  saveUnitTgt = 0;
  unitCsr = 0;
  stockUnitTgt = 0;
  devilSkillcsr = 0;
  EnemyUnitTgt = 0;
  tips_proc = 0;
  script_proc = 0;
  bookscene = 0;
  v14 = (p_monitor - 13);
  if (dds3ExistProcess(v14))
  {
    dds3KillProcess(v14, 0);
    v14 = 0;
  }
  g_mainPID = 0;
}

// 0x1f34f60
dds3ProcessFunc_t sBtlDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *p_monitor;
  u32 SelectRootID;
  void *Instance;
  s32 v12;
  dds3ProcessID_t *v13;
  u8 Alpha;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *v17;
  u8 v18;
  u32 v20;
  u32 v21;
  s32 v24;
  dds3ProcessID_t *monitor;
  u8 v26;
  u8 v27;
  s32 StockDevilNums;
  s32 v31;
  dds3ProcessID_t *v32;
  u8 v33;
  s32 v35;
  dds3ProcessID_t *v42;
  s32 SelectID;
  SBTLUNIT_WORK *pUnit;
  u8 v47;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 hithelperID;
  SBATTLE_WORK *v52;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_WORK *v56;
  s32 v58;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if ((BYTE4(ProcessData[4].klass) & 2) == 0)
    return 0;
  p_monitor = &ProcessData[1].monitor;
  dds3GetProcessData(&ProcessData[1].monitor);
  switch (LODWORD(ProcessData[4].klass))
  {
    case 2:
      SelectRootID = GetSelectRootID();
      Instance = get_Instance(0);
      BattleMenuDraw(Instance, p_monitor, 0);
      if ((SelectRootID & 0x80000000) == 0)
      {
        v12 = s_sBtlMenuHelpNo[SelectRootID];
        if ((v12 & 0x80000000) == 0)
        {
          if (v12 == 7)
          {
            if (sBtlEscapeCheck() == 1)
              v12 = 8;
            else
              v12 = 7;
          }
          v13 = p_monitor;
          Alpha = itfMenuImgGetAlpha(v13, 2);
          sBtlHelp(3, v12, Alpha);
        }
      }
      v15 = p_monitor;
      itfMenuImgGetAlpha(v15, 2);
      if (HIDWORD(ProcessData[5].klass) == 1)
      {
        if (wk->member_num >= 1)
        {
          v17 = p_monitor;
          v18 = itfMenuImgGetAlpha(v17, 2);
          v20 = v18;
          itfDrawMiscSpriteAlpha(398, 335, 0, v18, g_MapStatusBar->m_hSpr, 15, 109);
          v21 = ((4210816 * (u32)v18) >> 23) | 0xA09DC300;
          itfIconDrawSprite(414, 336, 0, v20, 14, 109);
          itfDrawFont(0, 437, 336, 0x100000, 0, 0, v21, 1.0, 109, s_strRepeat[3]);
        }
      }
      return 0;
    case 5:
      v24 = GetSelectRootID();
      monitor = ProcessData[2].monitor;
      v26 = itfMenuImgGetAlpha(monitor, 2);
      if (v24 == 5)
      {
        v27 = v26;
        sBtlHelp(3, 15, v27);
      }
      return 0;
    case 9:
      StockDevilNums = datGetStockDevilNums(0);
      if (StockDevilNums != 8)
      {
        if (StockDevilNums == 24 || StockDevilNums == 16)
          v31 = ((u32)StockDevilNums >> 3) - 1;
        else
          v31 = (s16)(StockDevilNums / 8);
LABEL_114:
        sBtlDrawTabPanel(374, 147, 0, 1.0, 0, v31, g_nakamaTab, 1);
        return 0;
      }
      v31 = 0;
      goto LABEL_114;
    case 0xA:
      v32 = ProcessData[2].monitor;
      v33 = itfMenuImgGetAlpha(v32, 2);
      if (sBtlGetStockUnitData(16))
      {
        v35 = 3;
      }
      else if (sBtlGetStockUnitData(8))
      {
        v35 = 2;
      }
      else
      {
        v35 = 1;
      }
      v58 = g_nakamaTab;
      sBtlDrawTabPanel(374, 147, 0, (f32)v33 / 255.0, 0, v35, v58, 0);
      return 0;
    case 0xC:
      sBtlDrawParam(0);
      sBtlDrawParam(1);
      sBtlDrawParam(2);
      sBtlDrawParam(3);
      return 0;
    case 0xD:
      v42 = ProcessData[2].monitor;
      SelectID = itfMenuGetSelectID(v42);
      pUnit = wk->tgtList->pUnitL[SelectID]->pUnit;
      v47 = (s32)(f32)((f32)((f32)SLODWORD(ProcessData[5].klass) * 255.0) / 10.0);
      if ((pUnit->status & 0x800) == 0)
        goto LABEL_90;
      UnitMng = wk->UnitMng;
      hithelperID = pUnit->hithelperID;
      goto LABEL_81;
    case 0x12:
      v52 = wk;
      tgtList = v52->tgtList;
      v56 = sBtlSearchUnit_ID(tgtList, enemyNowCsr);
      if (v56)
      {
        pUnit = v56;
        v47 = (s32)(f32)((f32)((f32)SLODWORD(ProcessData[5].klass) * 255.0) / 10.0);
        if ((v56->status & 0x800) != 0)
        {
          hithelperID = pUnit->hithelperID;
          UnitMng = wk->UnitMng;
LABEL_81:
          pUnit = sBtlSearchUnit_ID(UnitMng, hithelperID);
        }
LABEL_90:
        sBtlAnalyzeEnemy(pUnit, v47);
      }
      return 0;
    default:
      return 0;
  }
}

// 0x1f35960
void sBtlSetStartEx(SBTLMENU_TYPE a_type) {
  Il2CppObject *ProcessData;
  Il2CppObject *v7;
  SB_ENCOUNTPAC *EncountPac;
  s64 encountno;
  SB_ENCOUNTPAC *v14;
  dds3ProcessID_t *v16;
  s32 *EventBit;
  bool v22;
  dds3ProcessID_t *v24;
  s64 v27;
  s32 v28;
  dds3ProcessID_t *started;
  s32 *v33;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v7 = ProcessData;
  HIDWORD(ProcessData[5].klass) = a_type;
  HIDWORD(v7[4].klass) |= 0x10u;
  EncountPac = sBtlGetEncountPac(-1);
  encountno = wk->encountno;
  v14 = EncountPac[encountno];
  if (a_type == 1 && wk->battlemode == 3)
  {
    {
      if (!evtBitCheck(10028))
      {
        v16 = tipsTIPSStart(44);
        tips_proc = v16;
        LODWORD(v7[4].klass) = 25;
        EventBit = GBWK->EventBit;
        EventBit[313] |= 0x1000u;
        ReceiptSet(9520);
      }
    }
    return;
  }
  if ((u32)encountno == 23)
  {
    if (!evtBitCheck(10023))
    {
      ReceiptSet(9502);
      v28 = 9351;
      goto LABEL_71;
    }
  }
  if (evtBitCheck(49))
  {
    v22 = evtBitCheck(10021);
    if (!v22)
    {
      if (wk->encountno != 448 && (v14->flag & 0x36) == 0)
      {
        v24 = tipsTIPSStart(37);
        tips_proc = v24;
        LODWORD(v7[4].klass) = 25;
        sub_1A21FE0(10021, 0, v27);
        v28 = 9484;
LABEL_71:
        ReceiptSet(v28);
        goto LABEL_72;
      }
    }
  }
  else
  {
  }
  if (wk->encountno != 516 || evtBitCheck(680))
    goto LABEL_72;
  LoadPM1LocalizeText(690);
  started = scrStartScript3(1003, "e690", "e690.bf", 3, 1);
  script_proc = started;
  LODWORD(v7[4].klass) = 26;
  MOON_OUT();
  v33 = GBWK->EventBit;
  v33[21] |= 0x100u;
LABEL_72:
  sBtlMenuOpen();
}

// 0x1f35fa0
bool sBtlIsMenuStartScript(void) {
  Il2CppObject *ProcessData;

  if (!ProcessCheck())
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return LODWORD(ProcessData[4].klass) == 26;
  return LODWORD(ProcessData[4].klass) == 26;
}

// 0x1f360f0
void sBtlSetStart(void) {
  sBtlSetStartEx(0);
}

// 0x1f36160
bool IsStart(void) {
  Il2CppObject *ProcessData;

  if (!ProcessCheck())
    return 1;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  if (LODWORD(ProcessData[6].klass))
    return (BYTE4(ProcessData[4].klass) & 0x12) != 0;
  return 1;
}

// 0x1f362c0
void ProcessStart(void) {
  sBtlMenu_t *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;
  sBtlMenu_t *p_fields;

  v1 = Allocate(sBtlMenu_t);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_sBtlMenu_Process__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_sBtlMenu_Shutdown__, 0);
  started = dds3StartProcess("sbtlmenu_main", 1023, 0, 0, v2, v3, v1);
  g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_sBtlMenu_DrawProcess__, 0);
  v8 = dds3StartProcess("sbtlmenu_draw", 11029, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
  p_fields = &v1->fields;
  p_fields->step = 0;
  MenuCnt = 0;
  g_bitMoon = 0;
}

// 0x1f364e0
void sBtlProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 klass_high;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  klass_high = HIDWORD(ProcessData[4].klass);
  if ((klass_high & 1) == 0)
  {
    LOWORD(ProcessData[4].monitor) = 0;
    LODWORD(ProcessData[4].klass) = 19;
    HIDWORD(ProcessData[4].klass) = klass_high | 1;
  }
}

// 0x1f225c0
bool ProcessCheck(void) {
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 1;
    }
  }
  g_mainPID = 0;
  return 0;
}

// 0x1f36690
SBTLMENU_NODE sBtlGetNode(void) {
  dds3ProcessID_t *Work;
  dds3ProcessID_t *v4;
  dds3ProcessID_t *v5;
  s32 v6;
  u32 SelectRootID;
  u32 v9;

  Work = sBtlGetWork();
  if (!Work)
    return (s32)Work;
  v4 = Work;
  v5 = Work[3];
  if (!itfMenuProcessCheck(v5))
    goto LABEL_26;
  v6 = *((u32 *)v4 + 16);
  if (v6 == 1)
  {
    LODWORD(Work) = sBtlGetStat();
    if ((u32)Work == 2)
      return (s32)Work;
    v6 = *((u32 *)v4 + 16);
  }
  if (v6 == 2)
  {
    LODWORD(Work) = 1;
    return (s32)Work;
  }
  if ((u32)(v6 - 3) > 0xF)
    goto LABEL_26;
  SelectRootID = GetSelectRootID();
  if (SelectRootID > 0x13)
  {
LABEL_26:
    LODWORD(Work) = 0;
    return (s32)Work;
  }
  v9 = SelectRootID;
  LODWORD(Work) = *(u32 *)(*(u64 *)&Work[23][2].nameHash + 4 * v9 + 32);
  return (s32)Work;
}

// 0x1f36840
SBTLUNIT_WORK *GetActionUnit(void) {
  sBtlMenu_t *Work;
  dds3ProcessID_t *menuPID;

  Work = sBtlGetWork();
  if (!Work)
    return 0;
  menuPID = Work->menuPID;
  if (!itfMenuProcessCheck(menuPID))
    return 0;
  if (sBtlGetNode() != 2)
    return 0;
  return sBtlGetActionUnit();
}

// 0x1f36970
s32 sBtlGetTargetUnitIndex(void) {
  SBTLUNIT_WORK *TargetUnit;
  SBTLUNIT_WORK *v4;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v7;

  TargetUnit = GetTargetUnit();
  if (!TargetUnit)
    return -1;
  v4 = TargetUnit;
  if (TargetUnit->para->devilid)
  {
    Nakama = sBtlGetNakama(0);
    if (Nakama && SameDataCheck(Nakama->para, v4->para, 0))
      return 1;
    v7 = sBtlGetNakama(1);
    if (v7 && SameDataCheck(v7->para, v4->para, 0))
      return 2;
    return -1;
  }
  return 0;
}

// 0x1f36a70
SBTLUNIT_WORK *GetTargetUnit(void) {
  SBTLUNIT_WORK *result;
  SBTLUNIT_WORK *v4;
  dds3ProcessID_t *v5;
  bool v6;
  SBTLUNIT_LISTWORK *tgtList;
  f32 x;
  dds3ProcessID_t *v20;
  u32 v21;
  f32 v22;
  dds3ProcessID_t *v23;
  s32 v24;
  dds3ProcessID_t *v25;
  s32 v26;
  s32 PlayerID;
  dds3ProcessID_t *v28;
  s32 SelectID;
  SBTLUNIT_WORK *v30;
  sdatUnitWork_t *v31;
  sdatUnitWork_t *para;
  dds3ProcessID_t *v33;
  s32 v34;
  s32 v35;

  result = (SBTLUNIT_WORK *)sBtlGetWork();
  if (!result)
    return result;
  v4 = result;
  v5 = *(dds3ProcessID_t *)&result->vPosCmbMov0.z;
  v6 = itfMenuProcessCheck(v5);
  result = 0;
  if (!v6)
    return result;
  switch (sBtlGetNode())
  {
    case 2:
      result = GetTargetUnit();
      if (!result)
      {
        return GetActionUnit();
      }
      return result;
    case 3:
      x = v4->vRotBfrCmb.x;
      if (LODWORD(x) == 7)
        goto LABEL_36;
      if (LODWORD(x) != 17)
      {
        v28 = *(dds3ProcessID_t *)&v4->vPosCmbMov1.z;
        goto LABEL_58;
      }
      if (menuBeforFlag == 3)
      {
        v20 = *(dds3ProcessID_t *)&v4->vPosBfrCmb.x;
        goto LABEL_38;
      }
      v28 = *(dds3ProcessID_t *)&v4->vPosCmbMov1.z;
LABEL_58:
      SelectID = itfMenuGetSelectID(v28);
      if (SelectID < 0)
        return 0;
      result = (SBTLUNIT_WORK *)sBtlGetStockUnitData(SelectID);
      if (result)
        goto LABEL_60;
      return result;
    case 4:
LABEL_36:
      v20 = *(dds3ProcessID_t *)&v4->vPosBfrCmb.x;
LABEL_38:
      v21 = itfMenuGetSelectID(v20);
      result = 0;
      if (v21 <= 1)
        return sBtlGetNakama(v21);
      return result;
    case 5:
      v22 = v4->vRotBfrCmb.x;
      if (LODWORD(v22) == 5)
      {
        v33 = *(dds3ProcessID_t *)&v4->vPosCmbMov1.z;
        v34 = itfMenuGetSelectID(v33);
        if (v34 < 0)
          return 0;
        v35 = v34;
        return wk->UnitMng->pUnitL[v35]->pUnit;
      }
      else
      {
        if (LODWORD(v22) != 17 && LODWORD(v22) != 10)
          return 0;
        v23 = *(dds3ProcessID_t *)&v4->vPosCmbMov1.z;
        v24 = itfMenuGetSelectID(v23);
        if (v24 < 0)
          return 0;
        if (!v24)
          goto LABEL_53;
        result = (SBTLUNIT_WORK *)sBtlGetStockUnitData(v24 - 1);
        if (result)
        {
LABEL_60:
          v30 = result;
          result = sBtlGetNakama(0);
          if (!result || (v31 = result->para, (u16)v31->devilid != HIWORD(v30->vPosCmbMov0.y)) || v31->uniq_code != LODWORD(v30->effpos.y))
          {
            result = sBtlGetNakama(1);
            if (!result)
              return 0;
            para = result->para;
            if ((u16)para->devilid != HIWORD(v30->vPosCmbMov0.y) || para->uniq_code != LODWORD(v30->effpos.y))
            {
              return 0;
            }
          }
        }
      }
      return result;
    case 6:
      if (LODWORD(v4->vRotBfrCmb.x) != 12)
        return 0;
      v25 = *(dds3ProcessID_t *)&v4->vPosCmbMov1.z;
      v26 = itfMenuGetSelectID(v25);
      result = 0;
      if (!v26)
      {
LABEL_53:
        PlayerID = sBtlGetPlayerID();
        return sBtlGetPlayerUnit(PlayerID);
      }
      return result;
    case 7:
    case 8:
      enemyNowCsr = (u32)enemyNowCsr;
      if ((enemyNowCsr & 0x80000000) != 0)
        return 0;
      tgtList = wk->tgtList;
      if (!tgtList)
        return 0;
      tgtList = wk->tgtList;
      return tgtList->pUnitL[enemyNowCsr]->pUnit;
    default:
      return 0;
  }
}

// 0x1f36f00
void sBtlDrawTabPanel(s32 a_x, s32 a_y, s32 a_z, f32 a_alphaRate, s32 a_min, s32 a_max, s32 a_sel, s32 a_ofs) {
  sprHandle_t *m_hSpr;
  s32 v18;
  u32 v19;
  s32 v21;
  u32 v22;
  s32 v23;

  m_hSpr = g_MapStatusBar->m_hSpr;
  if (!m_hSpr)
    return;
  v23 = a_x;
  v18 = a_x - 2;
  v19 = (u8)(s32)(f32)(a_alphaRate * 255.0);
  itfDrawMiscSpriteAlpha(v18, a_y, a_z, v19, m_hSpr, 25, 109);
  v21 = v23 + 18;
  itfDrawMiscSpriteAlpha(v23 + 18, a_y, a_z, v19, g_MapStatusBar->m_hSpr, 26, 109);
  for (; a_min <= a_max; v21 += 28)
  {
    if (a_sel == a_min)
      v22 = -1600085856;
    else
      v22 = 1616928864;
    sBtlNum(v21, a_y, v22, v19, a_ofs + a_min++, 115);
  }
}

// 0x1f358c0
void sBtlDrawTabPanelCharList(s32 a_min, s32 a_max, s32 a_sel, s32 a_ofs, f32 a_alphaRate) {
  sBtlDrawTabPanel(374, 147, 0, a_alphaRate, a_min, a_max, a_sel, a_ofs);
}

// 0x1f37130
void MenuActive(bool _active) {
  s32 Node;
  Il2CppObject *ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *p_monitor;
  dds3ProcessID_t *v10;
  s64 v12;

  Node = sBtlGetNode();
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)naturalAligment || ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] != sBtlMenu_t)
    {
      goto LABEL_27;
    }
  }
  if (Node != 2)
  {
    p_monitor = &ProcessData[1].monitor;
    goto LABEL_13;
  }
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment >= (u32)v12 && (S_CmndMenuNew *)ProcessData->klass->_2.typeHierarchy[v12 - 1] == S_CmndMenuNew)
    {
      goto LABEL_24;
    }
LABEL_27:
  }
LABEL_24:
  if (HIDWORD(ProcessData[3].klass) == 3)
    p_monitor = &ProcessData[2];
  else
    p_monitor = &ProcessData[1].monitor;
LABEL_13:
  v10 = p_monitor;
  itfMenuSetFlag(v10, 8, active);
}
