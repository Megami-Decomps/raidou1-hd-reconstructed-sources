#include "types.h"
#include "BackRaiAnim.h"
#include "CMP_MENU_ID.h"
#include "CMP_MODE.h"
#include "CmpTitle.h"
#include "PanelFocus.h"
#include "buttonguide.h"
#include "camp.h"
#include "cfg.h"
#include "cmp.h"
#include "cmpbook.h"
#include "cmpfile.h"
#include "cmpitem.h"
#include "cmpkuda.h"
#include "cmpmain.h"
#include "cmpmap.h"
#include "cmpmenuopen.h"
#include "cmpmisc.h"
#include "cmpstatus.h"
#include "configunity.h"
#include "dat.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "itf.h"
#include "jmsinit.h"
#include "kernel.h"
#include "lmap.h"
#include "localize.h"
#include "raijindlc.h"
#include "rspecialskill.h"
#include "rstgrowth.h"
#include "scr.h"
#include "sdat.h"
#include "sdfmem.h"
#include "sdfsound.h"
#include "slmain.h"
#include "sndat3.h"
#include "tips.h"

#define CMPKUDASELNAKAMAOFS 4
#define CMPTAB1PAGEMAX 8
#define CMPKUDASELNAKAMAHDOFS 3
#define titleDlcContentsName "new_title"
#define titleDlcAssetName "dlc_title_msg."
#define CMP_PROCNAME "camp_main"
#define CMP_PROCNAME_DRAW "camp_draw"
#define CMPTAB_CENTER 167
#define CMPTAB_LEFT 168
#define CMPTAB_RIGHT 169

typedef enum {
    CMP_MENU_PANEL_X = 28,
    CMP_MENU_PANEL_Y = 65,
    CMP_MENU_PANEL_W = 128,
    CMP_MENU_PANEL_H = 23,
    CMP_MENU_PANEL_FX = 2,
    CMP_MENU_PANEL_FY = 1,
} CMP_MENU_PANEL;

typedef enum {
    CMP_BASE_MAG_X = -10,
    CMP_BASE_MAG_Y = 287,
    CMP_BASE_MNY_X = 328,
    CMP_BASE_MNY_Y = 352,
    CMP_BASE_BLT_X = -10,
    CMP_BASE_BLT_Y = 287,
    CMP_BASE_TABS_X = 220,
    CMP_BASE_TABS_Y = 125,
    CMP_BASE_TABS_MW = 25,
    CMP_BASE_TABS_MH = 25,
} CMP_BASE;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagCMP_WORK tagCMP_WORK;

void *debugSetting;
s32 testAnimNo;
bool subMenuActive;
bool exMenu;
bool itemNumDraw;
CMP_GUIDE oldGuide;
void *cmpGuides;
dds3ProcessID_t *g_mainPID;
dds3ProcessID_t *debugPID;
static bool _debugLoad_k__BackingField;
CMP_MODE g_endmode;
s8 g_GoldNoDspFlg;
void *menuName;
char *strCmpMenu;
void *helpName;
void *titleName;
u8 **cmptabsprtbl;
s16 **cmptabpostbl;
static dds3ProcessFunc_t SuspendFunc;
static dds3ProcessID_t *SuspendID;
static CMP_SUSPEND SuspendProc;

static bool Sord_RSlill_Menu(void);
static void ChkEnableSelectMenuBook(tagCMP_WORK *wk);

// macros
// 0x1f4de80: s32 CMP_MENU_ID_ROOT_MASK(s32 _id)
#define CMP_MENU_ID_ROOT_MASK(_id) (id >> 16)

// 0x1f4df80
void cmpLoadLocalizeText(void) {
  if (!Exists("new_title"))
    return;
  Load(Dependent, "dlc_title_msg.", "dlc_title_msg.");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  LoadLocalizeText_2("dlc_title_msg.", "CMP_P_TITLE_DLC");
  Unload(Dependent, "dlc_title_msg.", 0);
}

// 0x1f4e140
void cmpCmpGuideSet(CMP_GUIDE _id, bool _timer, s32 _waitTimer) {
  Il2CppObject *Item;
  Il2CppObject *v15;
  void *Instance;

  if (tipsProcessCheck())
    return;
  if (rstProcessCheck())
    return;
  if (object___ContainsKey(cmpGuides, id))
  {
    Item = object___get_Item(cmpGuides, id);
    if (!op_Inequality(GuideName, Item, 0))
      return;
    if ((u32)id <= 0x3B && ((1 << id) & 0xC0003C000000000LL) != 0)
    {
LABEL_23:
      v15 = object___get_Item(cmpGuides, id);
      ButtonGuideDispSet(v15, timer, waitTimer);
      oldGuide = id;
      return;
    }
    else
    {
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      goto LABEL_23;
    }
    goto LABEL_23;
  }
  LogWarning("不明なボタンガイドID", 0);
}

// 0x1f4e490
bool cmpStatusViewTitleOff(void) {
  dds3ProcessID_t *menuPID;
  s32 v5;
  tagCMP_WORK *Work;
  bool v9;

  menuPID = cmpGetWork()->menuPID;
  SelectID = itfMenuGetSelectID(menuPID);
  v5 = SelectID;
  Work = cmpGetWork();
  if (!Work)
    return 0;
  if (!Work->menuPID)
    return 0;
  if (v5 != 256)
  {
    if (v5 == 65552)
    {
      v9 = Work->step == 5;
      goto LABEL_27;
    }
    if (v5 == 61442)
    {
      g_step = (u8)g_step;
      if (g_step)
      {
        g_step = (u8)g_step;
        v9 = g_step != 15;
        goto LABEL_27;
      }
    }
LABEL_26:
    v9 = 0;
    goto LABEL_27;
  }
  if (Work->step != 5)
    goto LABEL_26;
  v9 = cfgGetConfigGAME(16, 0) == 0;
  if (!cmpNowStatus())
    return v9;
  goto LABEL_28;
LABEL_27:
  if (!cmpNowStatus())
    return v9;
LABEL_28:
  return !cmpSwordSelFlagChk() || v9;
}

// 0x1f4e9e0
void cmpMenuTitleDrawUnity(void) {
  dds3ProcessID_t *p_menuPID;
  Il2CppObject *ProcessData;
  tagCMP_WORK *Work;
  void (*monitor)();
  Il2CppMethodPointer virtualMethodPointer;
  u32 nowTitle;
  s32 v11;
  char *v12;
  s64 v13;
  char *v14;
  Il2CppMethodPointer v15;
  char *v17;

  p_menuPID = &cmpGetWork()->menuPID;
  ProcessData = dds3GetProcessData(p_menuPID);
  Work = cmpGetWork();
  monitor = (void (*)())_get_Instance()[5].monitor;
  Instance = _get_Instance();
  virtualMethodPointer = Instance[1].virtualMethodPointer;
  nowTitle = Work->nowTitle;
  if (cmpStatusViewTitleOff())
  {
    (*(void (void (*)(), s64, u64))(*(u64 *)monitor + 392))(monitor, 1, *(u64 *)(*(u64 *)monitor + 400));
    (*(*(u64 *)virtualMethodPointer + 392))(virtualMethodPointer, 1, *(u64 *)(*(u64 *)virtualMethodPointer + 400));
  }
  else
  {
    if (Work->nowTitle)
    {
      (*(*(u64 *)virtualMethodPointer + 392))(virtualMethodPointer, 0, *(u64 *)(*(u64 *)virtualMethodPointer + 400));
      (*(void (void (*)(), s64, u64))(*(u64 *)monitor + 392))(monitor, 1, *(u64 *)(*(u64 *)monitor + 400));
      switch (Work->nowTitle)
      {
        case 1:
          v11 = 61441;
          break;
        case 2:
          v11 = 2;
          break;
        case 3:
          v11 = 458753;
          break;
        case 4:
          v11 = 128;
          break;
        case 5:
          v11 = 262146;
          break;
        case 6:
          v11 = 64;
          break;
        case 7:
          v11 = 512;
          break;
        case 8:
          v11 = 16;
          break;
        default:
          v11 = 0;
          break;
      }
      v12 = cmpGetstrCmpMenuHD(v11, 0);
      v13 = *(u64 *)virtualMethodPointer;
      v14 = v12;
      v15 = virtualMethodPointer;
    }
    else
    {
      (*(void (void (*)(), u64, u64))(*(u64 *)monitor + 392))(monitor, 0, *(u64 *)(*(u64 *)monitor + 400));
      (*(*(u64 *)virtualMethodPointer + 392))(virtualMethodPointer, 1, *(u64 *)(*(u64 *)virtualMethodPointer + 400));
      v17 = cmpGetstrCmpMenuHD(0, 0);
      v13 = *(u64 *)monitor;
      v14 = v17;
      v15 = monitor;
    }
    (*(v13 + 408))(v15, nowTitle, v14, *(u64 *)(v13 + 416));
  }
}

// 0x1f4f010
void cmpUnityBackRaidouDraw(void) {
  tagCMP_WORK *Work;
  s32 nowBackRaiAnim;
  Il2CppObject *v4;
  Il2CppObject *v5;
  Il2CppObject *v6;
  Il2CppObject *v7;
  Il2CppObject *v8;
  Il2CppObject *v9;
  Il2CppObject *v10;
  Il2CppObject *v11;
  Il2CppObject *v12;
  Il2CppObject *Instance;
  Il2CppObject *v15;
  Il2CppObject *v16;
  Il2CppObject *v17;
  Il2CppObject *v18;
  Il2CppObject *v19;
  Il2CppObject *v20;
  Il2CppObject *v21;
  Il2CppClass *klass;
  tagCMP_WORK *v23;
  Il2CppObject *v24;
  Il2CppClass *v25;

  Work = cmpGetWork();
  nowBackRaiAnim = Work->nowBackRaiAnim;
  if (nowBackRaiAnim == -1)
  {
    Instance = _get_Instance();
    TopAnimSet(Instance[5].klass, 0, 0, 0);
    v15 = _get_Instance();
    AnimSet(v15[5].klass, 2, 0, 0);
    v16 = _get_Instance();
    AnimSet(v16[5].klass, 3, 0, 0);
    v17 = _get_Instance();
    AnimSet(v17[5].klass, 1, 0, 0);
    v18 = _get_Instance();
    AnimSet(v18[5].klass, 4, 0, 0);
    v19 = _get_Instance();
    AnimSet(v19[5].klass, 6, 0, 0);
    v20 = _get_Instance();
    AnimSet(v20[5].klass, 5, 0, 0);
    v21 = _get_Instance();
    AnimSet(v21[5].klass, 7, 0, 0);
    klass = _get_Instance()[5].klass;
    AnimSet(klass, 8, 0, 0);
    return;
  }
  if (nowBackRaiAnim)
  {
    v23 = Work;
    v24 = _get_Instance();
    TopAnimSet(v24[5].klass, 0, 0, 0);
    v25 = _get_Instance()[5].klass;
    AnimSet(v25, v23->nowBackRaiAnim, 1, 0);
  }
  else
  {
    v4 = _get_Instance();
    AnimSet(v4[5].klass, 2, 0, 0);
    v5 = _get_Instance();
    AnimSet(v5[5].klass, 3, 0, 0);
    v6 = _get_Instance();
    AnimSet(v6[5].klass, 1, 0, 0);
    v7 = _get_Instance();
    AnimSet(v7[5].klass, 4, 0, 0);
    v8 = _get_Instance();
    AnimSet(v8[5].klass, 6, 0, 0);
    v9 = _get_Instance();
    AnimSet(v9[5].klass, 5, 0, 0);
    v10 = _get_Instance();
    AnimSet(v10[5].klass, 7, 0, 0);
    v11 = _get_Instance();
    AnimSet(v11[5].klass, 8, 0, 0);
    v12 = _get_Instance();
    TopAnimSet(v12[5].klass, 0, 1, 0);
  }
}

// 0x1f4f300
void cmpUnityUiDraw(void) {
  Il2CppObject *Instance;

  if (cmpNowStatus())
    return;
  cmpGetWork();
  Instance = _get_Instance();
  (*(*(u64 *)Instance[10].monitor + 536))(Instance[10].monitor, 0, *(u64 *)(*(u64 *)Instance[10].monitor + 544));
  if (!exMenu)
  {
    MainManuDraw();
    MainMenuCursorMove();
  }
}

// 0x1f4e850
bool cmpNowStatus(void) {
  u8 *ProcessData;

  if (!dds3ExistProcess(g_mainPID))
  {
    LOBYTE(ProcessData) = 0;
    return (char)ProcessData;
  }
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LODWORD(ProcessData) = (ProcessData[25] >> 2) & 1;
  return (char)ProcessData;
}

// 0x1f4f400
void MainManuDraw(void) {
  dds3ProcessID_t *p_menuPID;
  Il2CppObject *ProcessData;
  s64 v7;
  Il2CppClass *klass;
  s64 v9;
  u32 v10;
  MenuMover_t *v11;
  u32 TextColor;
  s64 v13;

  p_menuPID = &cmpGetWork()->menuPID;
  ProcessData = dds3GetProcessData(p_menuPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v7 = *((u32 *)&ProcessData[9].klass->_1.byval_arg.data + SBYTE4(ProcessData[5].monitor));
  klass = _get_Instance()[7].klass;
  MainManuDraw(klass, HIDWORD(ProcessData[7].monitor), 0);
  if (SHIDWORD(ProcessData[8].klass) >= 1)
  {
    v9 = 0;
    do
    {
      v10 = ProcessData[13].klass;
      v11 = *((MenuMover_t *)&ProcessData[5].klass->_1.byval_arg.data + v9);
      TextColor = itfGetTextColor(v11, v10);
      if (v7 == v9 && ((s64)ProcessData[13].klass & 8) == 0)
        TextColor = 1;
      v13 = *(u64 *)(*((u64 *)&ProcessData[5].klass->_1.byval_arg.data + v9) + 24);
      SubMenuTextDraw(klass, v9++, *(char **)(v13 + 48), TextColor, *(char **)(v13 + 56), *(u32 *)(v13 + 16), 0);
    }
    while (v9 < SHIDWORD(ProcessData[8].klass));
  }
}

// 0x1f4f630
void MainMenuCursorMove(void) {
  dds3ProcessID_t *p_menuPID;
  Il2CppObject *ProcessData;
  bool v7;
  Il2CppObject *Instance;

  p_menuPID = &cmpGetWork()->menuPID;
  ProcessData = dds3GetProcessData(p_menuPID);
  if (!ProcessData)
  v7 = ((s64)ProcessData[13].klass & 8) == 0;
  Instance = _get_Instance();
  MainMenuCursorMove(Instance[7].klass, *((u32 *)&ProcessData[9].klass->_1.byval_arg.data + SBYTE4(ProcessData[5].monitor)), v7, 0);
}

// 0x1f4f790
void cmpDrawMenuFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  dds3ProcessID_t *menuPID;

  cmpGetSpriteHnd(0);
  if (!cmpGetWork())
    return;
  if (!cmpGetWork()->menuPID)
    return;
  menuPID = cmpGetWork()->menuPID;
  itfMenuChkMenuTop(menuPID, a_id);
}

// 0x1f4f8e0
void cmpCallProcEnd(tagCMP_WORK *wk) {
  dds3ProcessID_t *menuPID;

  ProcessEnd();
  ProcessEnd();
  menuPID = wk->menuPID;
  itfMenuProcessEnd(menuPID);
  itfMenuProcessEnd(wk->charPID);
  itfMenuProcessEnd(wk->stockPID);
  itfMenuProcessEnd(wk->listPID);
  itfMenuProcessEnd(wk->submPID);
  Delete(0);
  ProcessEnd(0, 0);
}

// 0x1f4fb40
u8 cmpCheckProcEnd(tagCMP_WORK *wk) {
  bool v3;
  char v4;
  bool v5;
  char v6;
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *p_charPID;
  dds3ProcessID_t *charPID;
  dds3ProcessID_t *p_stockPID;
  dds3ProcessID_t *stockPID;
  dds3ProcessID_t *p_listPID;
  dds3ProcessID_t *listPID;
  dds3ProcessID_t *p_submPID;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *submPID;
  dds3ProcessID_t *v22;
  bool v23;

  v3 = ProcessCheck();
  v4 = !v3;
  v5 = ProcessCheck();
  if (v3)
    v6 = 1;
  else
    v6 = 2;
  if (v5)
    v4 = v6;
  p_menuPID = &wk->menuPID;
  menuPID = wk->menuPID;
  if (itfMenuProcessCheck(menuPID))
    goto LABEL_12;
  p_menuPID = 0;
  p_charPID = &wk->charPID;
  charPID = wk->charPID;
LABEL_16:
  if (!itfMenuProcessCheck(charPID))
    goto LABEL_20;
  ++v4;
  p_stockPID = &wk->stockPID;
  stockPID = wk->stockPID;
  goto LABEL_21;
LABEL_12:
  ++v4;
  p_charPID = &wk->charPID;
  charPID = wk->charPID;
  goto LABEL_16;
LABEL_20:
  p_charPID = 0;
  p_stockPID = &wk->stockPID;
  stockPID = wk->stockPID;
LABEL_21:
  if (itfMenuProcessCheck(stockPID))
    goto LABEL_22;
  p_stockPID = 0;
  p_listPID = &wk->listPID;
  listPID = wk->listPID;
LABEL_26:
  if (!itfMenuProcessCheck(listPID))
    goto LABEL_30;
  ++v4;
  submPID = wk->submPID;
  p_submPID = &wk->submPID;
  v20 = submPID;
  goto LABEL_31;
LABEL_22:
  ++v4;
  p_listPID = &wk->listPID;
  listPID = wk->listPID;
  goto LABEL_26;
LABEL_30:
  p_listPID = 0;
  v22 = wk->submPID;
  p_submPID = &wk->submPID;
  v20 = v22;
LABEL_31:
  if (itfMenuProcessCheck(v20))
  {
    ++v4;
    v23 = fclCheck();
    return v4 + v23 + ProcessCheck();
  }
  p_submPID = 0;
  v23 = fclCheck();
  return v4 + v23 + ProcessCheck();
}

// 0x1f4ff30
bool cmpEventMenuChk(void) {
  return 0;
}

// 0x1f4e710
tagCMP_WORK *cmpGetWork(void) {
  tagCMP_WORK *result;

  if (!g_mainPID)
    return 0;
  result = (tagCMP_WORK *)dds3GetProcessData(g_mainPID);
  if (!result)
    return result;
  return result;
}

// 0x1f4ff40
dds3ProcessID_t *cmpGetMenuPID(void) {
  return cmpGetWork()->menuPID;
}

// 0x1f4ffc0
dds3ProcessID_t *cmpGetCharPID(void) {
  dds3ProcessID_t *result;

  result = (dds3ProcessID_t *)cmpGetWork();
  if (!result)
    return result;
  return cmpGetWork()->charPID;
}

// 0x1f50070
dds3ProcessID_t *cmpGetStockPID(void) {
  dds3ProcessID_t *result;

  result = (dds3ProcessID_t *)cmpGetWork();
  if (!result)
    return result;
  return cmpGetWork()->stockPID;
}

// 0x1f50120
void cmpSetStockPanelActive(PanelFocus _active, bool _se) {
  tagCMP_WORK *Work;

  Work = cmpGetWork();
  if (!Work)
    return;
  Work->changeActivePanel = active;
  if (se)
    SE(3);
}

// 0x1f501c0
PanelFocus cmpGetStockPanelActive(void) {
  tagCMP_WORK *Work;

  Work = cmpGetWork();
  if (Work)
    LODWORD(Work) = Work->stockPanelActive;
  return (s32)Work;
}

// 0x1f50240
dds3ProcessID_t *cmpGetListPID(void) {
  return cmpGetWork()->listPID;
}

// 0x1f502c0
dds3ProcessID_t *cmpGetsubMenuPID(void) {
  return cmpGetWork()->submPID;
}

// 0x1f50340
void cmpSetTabFlag(s8 flg) {
  cmpGetWork()->tabNoDisp = flg;
  return;
}

// 0x1f503d0
void cmpSetHelpFlag(s8 flg) {
  cmpGetWork()->helpNoDisp = flg;
  return;
}

// 0x1f50460
void cmpSetGoldFlag(s8 flg) {
  g_GoldNoDspFlg = flg;
  return;
}

// 0x1f504f0
void cmpSetItemNumDraw(bool _draw) {
  itemNumDraw = draw;
}

// 0x1f50560
void cmpSetHelpDispFlag(s8 flg) {
  cmpGetWork()->helpDispflg = flg;
  return;
}

// 0x1f505f0
bool cmpChkUnopenedMenu(CMP_MENU_ID index) {
  s32 v3;
  s32 v4;
  bool result;

  if (!evtBitCheck(42))
  {
    v4 = 61441;
    result = 1;
    if (index > 61441)
    {
      if (index != 458753 && index != 262146)
        return index == 61442 && !evtBitCheck(9991);
      return result;
    }
    if (index <= 511)
    {
      if (index != 128 && index != 256)
        return 0;
      return result;
    }
    if (index == 512)
      return !evtBitCheck(10040);
LABEL_30:
    if (index != v4)
      return 0;
    return result;
  }
  if (evtBitCheck(2103))
    v3 = 43;
  else
    v3 = 65;
  if (evtBitCheck(v3))
  {
    if (index == 512)
      return !evtBitCheck(10040);
    return index == 256 && !evtBitCheck(10009);
  }
  result = 1;
  if (index > 511)
  {
    if (index == 512)
      return !evtBitCheck(10040);
    v4 = 262146;
    goto LABEL_30;
  }
  if (index != 128)
    return index == 256 && !evtBitCheck(10009);
  return result;
}

// 0x1f50780
static bool Sord_RSlill_Menu(void) {
  s32 v1;

  if (evtBitCheck(2103))
    v1 = 43;
  else
    v1 = 65;
  return evtBitCheck(v1);
}

// 0x1f507b0
char *cmpGetUnopenedMenuName(CMP_MENU_ID index, bool label) {
  if (cmpChkUnopenedMenu(index))
    return "CMP_STATUS_L0019";
  if (index != 64)
    return 0;
  if (evtBitCheck(42))
    return 0;
  return "CMP_MENU_L0043";
}

// 0x1f4ec90
char *cmpGetstrCmpMenuHD(CMP_MENU_ID index, bool label) {
  char *Item;
  s32 StockReprtStok;
  Il2CppObject *v9;
  char *v10;
  char *v11;
  char *v12;
  char *LocalizeText;
  s32 data;

  if (cmpChkUnopenedMenu(index))
  {
    Item = "CMP_STATUS_L0019";
    if ("CMP_STATUS_L0019")
      goto LABEL_33;
  }
  else if (index == 64 && !evtBitCheck(42))
  {
    Item = "CMP_MENU_L0043";
    if ("CMP_MENU_L0043")
      goto LABEL_33;
  }
  StockReprtStok = datGetStockReprtStok();
  if (index != 256)
    goto LABEL_27;
  goto LABEL_9001;
  if (index != 256)
  {
LABEL_27:
    if (!object___ContainsKey(menuName, index))
    {
      Item = 0;
      goto LABEL_35;
    }
    Item = object___get_Item(menuName, index);
LABEL_33:
LABEL_35:
    LocalizeText = GetLocalizeText(Item, label);
    return itfTextTagReplace(LocalizeText, 1);
  }
LABEL_9001:
  if (!StockReprtStok)
    goto LABEL_27;
  data = datGetStockReprtStok();
  v9 = Box(s32, &data);
  v10 = Format("{0}", v9, 0);
  frSetVariableRequest(0, v10);
  v11 = GetLocalizeText("CMP_MENU_L0049", label);
  v12 = itfTextTagReplace(v11, 1);
  frSetVariableRequest(0, "");
  return v12;
}

// 0x1f508a0
char *cmpGetTitleText(CMP_TITLE_ID index) {
  Il2CppObject *Item;

  if (object___ContainsKey(titleName, index))
  {
    Item = object___get_Item(titleName, index);
  }
  else
  {
    Item = 0;
  }
  return GetLocalizeText(Item, 1);
}

// 0x1f509b0
char *cmpGetstrCmpMenu(s32 index, bool label) {
  char *v6;

  if (evtBitCheck(42))
  {
LABEL_4:
    if (index < 0)
      return "";
    goto LABEL_5;
  }
  if (index <= 3)
  {
    if ((index | 2) != 3)
      goto LABEL_4;
  }
  else if (index != 20 && index != 12)
  {
LABEL_5:
    if (SLODWORD(strCmpMenu->max_length) > index)
    {
      v6 = strCmpMenu[index];
      return GetLocalizeText(v6, 1);
    }
    return "";
  }
  return GetLocalizeText("CMP_STATUS_L0019", 1);
}

// 0x1f50b30
s32 cmpChkTabChg(void) {
  return cmpGetWork()->tabpagestockmax != 0;
}

// 0x1f50b90
void cmpMenuMaskSet(void) {
  tagCMP_WORK *Work;
  s32 menuID;
  tagCMP_WORK *v5;
  u32 v6;
  u64 v7;
  dds3ProcessID_t *menuPID;

  Work = cmpGetWork();
  menuID = Work->menuID;
  if ((menuID & 1) == 0)
    return;
  v5 = Work;
  HIDWORD(v7) = menuID - 65537;
  LODWORD(v7) = menuID - 65537;
  v6 = v7 >> 16;
  if (v6 <= 5 && ((1 << v6) & 0x27) != 0 || menuID == 262145)
  {
    menuPID = Work->menuPID;
    itfMenuSetFlagMenu(menuPID, -1, 2, 0);
    itfMenuSetFlagMenu(v5->menuPID, v5->menuID, 2, 1);
  }
}

// 0x1f50cb0
void cmpTitleChange(CMP_MENU_ID _id) {
  s32 v3;
  tagCMP_WORK *Work;

  if (id > 61440)
  {
    if (id > 262145)
    {
      if (id == 262146)
      {
        v3 = 5;
        goto LABEL_32;
      }
      if (id == 458753)
      {
        v3 = 3;
        goto LABEL_32;
      }
    }
    else
    {
      if (id == 61441)
      {
        v3 = 1;
        goto LABEL_32;
      }
      if (id == 61442)
      {
        v3 = 2;
        goto LABEL_32;
      }
    }
LABEL_30:
    v3 = 0;
    goto LABEL_32;
  }
  if (id > 127)
  {
    if (id == 128)
    {
      v3 = 4;
      goto LABEL_32;
    }
    if (id == 512)
    {
      v3 = 7;
      goto LABEL_32;
    }
    goto LABEL_30;
  }
  if (id == 16)
  {
    v3 = 8;
    goto LABEL_32;
  }
  if (id != 64)
    goto LABEL_30;
  v3 = 6;
LABEL_32:
  Work = cmpGetWork();
  if (!Work)
    return;
  Work->nowTitle = v3;
}

// 0x1f50f00
s32 cmpCallFunc(void) {
  tagCMP_WORK *Work;
  dds3ProcessID_t *menuPID;
  s32 SelectID;
  s32 menuID;
  s32 v10;
  s32 v13;
  Il2CppObject *v14;
  dds3ProcessID_t *v16;
  s32 v17;
  tagCMP_WORK *v20;
  u32 v24;
  u64 v25;
  dds3ProcessID_t *v26;
  tagCMP_WORK *v28;
  u64 v29;
  dds3ProcessID_t *v32;
  s32 v35;
  dds3ProcessID_t *v38;
  dds3ProcessID_t *v42;
  dds3ProcessID_t *v44;
  DvlReportStateMachine *v45;
  s32 ConfigGAME;
  DvlReportStateMachine *dvlReportMachine;
  dds3ProcessID_t *v48;
  s32 v49;
  void *Instance;
  dds3ProcessID_t *v52;

  Work = cmpGetWork();
  menuPID = Work->menuPID;
  SelectID = itfMenuGetSelectID(menuPID);
  Work->menuID = SelectID;
  if (cmpChkUnopenedMenu(SelectID))
    goto LABEL_5;
  goto LABEL_10;
  if (cmpChkUnopenedMenu(v10))
  {
LABEL_5:
    menuID = Work->menuID;
    if (menuID == 65552)
      goto LABEL_16;
    goto LABEL_11;
  }
LABEL_10:
  CmpOnMenu(Work->menuID);
  menuID = Work->menuID;
  if (menuID == 65552)
    goto LABEL_16;
LABEL_11:
  if (menuID != 262160 && menuID != 524304)
  {
    cmpTitleChange(menuID);
  }
LABEL_16:
  cmpMenuMaskSet();
  v13 = Work->menuID;
  if ((v13 & 1) == 0)
    goto LABEL_18;
  if (v13 == 61441)
  {
    Work->count = 0;
    Work->helpDispflg = 1;
    Work->step = 4;
    SortSetting(61441);
    cmpSetupDvlSkl(Work->menuID);
    v20 = cmpGetWork();
    if (!v20)
      return 1;
    v35 = 4;
LABEL_94:
    v20->nowBackRaiAnim = v35;
    return 1;
  }
  Setup(v13, 0);
  HIDWORD(v25) = Work->menuID - 65537;
  LODWORD(v25) = HIDWORD(v25);
  v24 = v25 >> 16;
  if (v24 > 6 || v24 == 4)
    goto LABEL_58;
  v26 = Work->menuPID;
  itfMenuSetFlag(v26, 8, 0);
  itfMenuSetFlagMenu(Work->menuPID, Work->menuID, 8, 1);
  cmpUpdateFontCharPID();
  cmpUpdateSelectPosCharPID();
  goto LABEL_56;
  if (v28)
LABEL_57:
    v28->nowBackRaiAnim = 2;
LABEL_58:
  HIDWORD(v29) = Work->menuID - 131073;
  LODWORD(v29) = HIDWORD(v29);
  if ((u32)(v29 >> 16) <= 4)
    Work->helpDispflg = 1;
  goto LABEL_60;
LABEL_56:
  v28 = cmpGetWork();
  if (!v28)
    goto LABEL_58;
  goto LABEL_57;
LABEL_18:
  if ((v13 & 2) != 0)
  {
    Work->step = 4;
    Work->count = 0;
    if (v13 == 262146)
    {
      v20 = cmpGetWork();
      if (!v20)
        return 1;
      v35 = 6;
      goto LABEL_94;
    }
    v20 = cmpGetWork();
    if (!v20)
      return 1;
    v35 = 3;
    goto LABEL_94;
  }
  if ((v13 & 0x80) != 0)
  {
    dds3FadeOut(0, 0, 0, 0xAu);
    Work->count = 0;
    v32 = Work->menuPID;
    itfMenuSetFlag(v32, 8, 0);
    itfMenuSetFlagMenu(Work->menuPID, Work->menuID, 8, 1);
    v17 = 6;
    goto LABEL_85;
  }
  if ((v13 & 0x40) != 0)
  {
    dds3FadeOut(0, 0, 0, 0x14u);
    Work->count = 0;
    v38 = Work->menuPID;
    itfMenuSetFlag(v38, 8, 0);
    itfMenuSetFlagMenu(Work->menuPID, Work->menuID, 8, 1);
    v17 = 7;
    goto LABEL_85;
  }
  if ((v13 & 0x200) != 0)
  {
    dds3FadeOut(0, 0, 0, 0x14u);
    Work->count = 0;
    v42 = Work->menuPID;
    itfMenuSetFlag(v42, 8, 0);
    itfMenuSetFlagMenu(Work->menuPID, Work->menuID, 8, 1);
    Work->step = 8;
    return 1;
  }
  else
  {
    if ((v13 & 0x100) == 0)
    {
      if (v13 <= 131087)
      {
        switch (v13)
        {
          case 8:
            Work->count = 0;
            Work->step = 3;
            Instance = get_Instance(0);
            ItfButtonGuideActive(Instance, 0, 0);
            return 1;
          case 16:
            TitleChange(8);
            return 1;
          case 65552:
            v14 = _get_Instance();
            sub_1BB07C0(*((u64 *)v14[7].monitor + 2), 0, 0);
            Work->count = 0;
            v16 = Work->menuPID;
            itfMenuSetFlag(v16, 8, 0);
            itfMenuSetFlagMenu(Work->menuPID, Work->menuID, 8, 1);
            v17 = 10;
LABEL_85:
            Work->step = v17;
            return 1;
        }
        goto LABEL_60;
      }
      switch (v13)
      {
        case 131088:
          return 0;
        case 262160:
          Work->count = 0;
          Work->step = 11;
          SuspendProc = 0;
          goto LABEL_126;
        case 524304:
          Work->count = 0;
          Work->step = 12;
          *(u64 *)&Work->workStat = 0x1800000000LL;
LABEL_126:
          v52 = Work->menuPID;
          itfMenuSetFlag(v52, 8, 0);
          itfMenuSetFlagMenu(Work->menuPID, Work->menuID, 8, 1);
          return 1;
      }
LABEL_60:
      Work->count = 0;
      Work->step = 5;
      return 1;
    }
    Work->count = 0;
    v44 = Work->menuPID;
    itfMenuSetFlag(v44, 8, 0);
    itfMenuSetFlagMenu(Work->menuPID, Work->menuID, 8, 1);
    Work->step = 9;
    v45 = Allocate(DvlReportStateMachine);
    _ctor(v45, 0);
    Work->dvlReportMachine = v45;
    ConfigGAME = cfgGetConfigGAME(16, 0);
    dvlReportMachine = Work->dvlReportMachine;
    if (ConfigGAME)
    {
      Init(dvlReportMachine, 5, 0);
      v48 = Work->menuPID;
      v49 = Work->menuID;
      itfMenuSetFlagMenu(v48, v49, 2048, 1);
    }
    else
    {
      Init(dvlReportMachine, 0, 0);
      dds3FadeOut(0, 0, 0, 0x14u);
    }
    fclGetLogStop(g_mainPID, 1);
    return 1;
  }
}

// 0x1f51990
static void ChkEnableSelectMenuBook(tagCMP_WORK *wk) {
  CMP_MENU_ID *v3;
  s64 i;
  dds3ProcessID_t *menuPID;
  s32 v7;

  v3 = NewSpecific(CMP_MENU_ID, 3u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__21D1F62A1F3935E550787E73252BD130719AD1898C97A0A99A5F3FEAABE4CC8A, 0);
  if (*(s32 *)((char *)v3 + 24) >= 1)
  {
    for (i = 0; i < *(s32 *)((char *)v3 + 24); ++i)
    {
      menuPID = wk->menuPID;
      v7 = *(u32 *)((s64)&v3[0] + 4 * i);
      itfMenuSetFlagMenu(menuPID, v7, 2, g_itemNum > 0);
    }
  }
}

// 0x1f51b10
void cmpChkEnableSelectMenuItem(tagCMP_WORK *wk) {
  CMP_MENU_ID *v3;
  s64 v4;
  s64 v5;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v7;
  s32 v8;
  s32 List;
  s32 v10;
  s32 v11;

  v3 = NewSpecific(CMP_MENU_ID, 5u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E824ABDF04F9AFD63F66A42BCFDB5D23B6DC4F8C86905E1C99780024F051AD2E, 0);
  if (*(s32 *)((char *)v3 + 24) >= 1)
  {
    v4 = 0;
    v5 = &v3[0];
    do
    {
      while (1)
      {
        v8 = *(u32 *)(v5 + 4 * v4);
        List = MakeList(v8);
        v10 = *(u32 *)(v5 + 4 * v4);
        v11 = List;
        if ((v10 == 61442 || v10 == 196610 || v10 == 393218 || v10 == 327682) && !List)
          break;
        menuPID = wk->menuPID;
        itfMenuSetFlagMenu(menuPID, v10, 2, v11 > 0);
        if (++v4 >= *(s32 *)((char *)v3 + 24))
          return;
      }
      v7 = wk->menuPID;
      itfMenuSetFlagMenu(v7, v10, 2, 1);
      ++v4;
    }
    while (v4 < *(s32 *)((char *)v3 + 24));
  }
}

// 0x1f51ce0
void cmpChkEnableDecideMenu2(tagCMP_WORK *wk) {
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  itfMenuSetFlagMenu(menuPID, 262146, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 458753, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 256, 2, 0);
}

// 0x1f51d90
void cmpChkEnableSelectMenu(tagCMP_WORK *wk) {
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v7;
  s32 v8;
  dds3ProcessID_t *v10;
  dds3ProcessID_t *v11;
  s32 StockDevilNums;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *v16;
  dds3ProcessID_t *v18;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *v22;
  char *v23;
  char *v25;
  s32 ConfigGAME;
  dds3ProcessID_t *v27;
  s32 v28;
  dds3ProcessID_t *v30;
  s32 v31;
  s32 v33;
  dds3ProcessID_t *v35;
  dds3ProcessID_t *v36;
  s32 v37;
  dds3ProcessID_t *v39;
  s32 v40;
  dds3ProcessID_t *v42;
  s32 v43;
  s32 v47;
  dds3ProcessID_t *v48;
  s32 v49;
  s32 v50;
  dds3ProcessID_t *v51;
  dds3ProcessID_t *v52;

  cmpChkEnableSelectMenuItem(wk);
  ChkEnableSelectMenuBook(wk);
  if (fldGb->nakamaMode)
  {
    menuPID = wk->menuPID;
    itfMenuSetFlagMenu(menuPID, 262146, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 458753, 2, 0);
    v7 = wk->menuPID;
    v8 = 256;
    goto LABEL_12;
  }
  StockDevilNums = datGetStockDevilNums(1);
  v15 = wk->menuPID;
  itfMenuSetFlagMenu(v15, 458753, 2, 1);
  v16 = wk->menuPID;
  if (StockDevilNums >= 1)
  {
    itfMenuSetFlagMenu(v16, 61441, 2, 1);
    v10 = wk->menuPID;
    goto LABEL_14;
  }
  v8 = 61441;
  v7 = v16;
LABEL_12:
  itfMenuSetFlagMenu(v7, v8, 2, 0);
  v10 = wk->menuPID;
LABEL_14:
  itfMenuSetFlagMenu(v10, 2, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 61442, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 64, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 512, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 128, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 8, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 16, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 65552, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 131088, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 524304, 2, 1);
  if (dds3AdminiGetActiveSequence() != 7 && dds3AdminiGetActiveSequence() != 35)
  {
    goto LABEL_18;
  }
  if (!fldGb->nakamaMode)
    goto LABEL_35;
LABEL_18:
  v11 = wk->menuPID;
  itfMenuSetFlagMenu(v11, 262160, 2, 0);
  goto LABEL_21;
LABEL_39:
  if (fldGb->fieldID == 12)
    goto LABEL_41;
  v52 = wk->menuPID;
  itfMenuSetFlagMenu(v52, 256, 2, 1);
  v22 = wk->menuPID;
  goto LABEL_45;
LABEL_35:
  v18 = wk->menuPID;
  itfMenuSetFlagMenu(v18, 262160, 2, 1);
LABEL_21:
  if (datGetStockReprtStok() >= 1)
    goto LABEL_39;
LABEL_41:
  v19 = wk->menuPID;
  itfMenuSetFlagMenu(v19, 256, 2, 0);
  v22 = wk->menuPID;
LABEL_45:
  v23 = cmpGetstrCmpMenuHD(256, 0);
  v25 = cmpGetstrCmpMenuHD(256, 1);
  itfMenuSetFont(v22, 256, v23, v25);
  ConfigGAME = cfgGetConfigGAME(16, 0);
  v27 = wk->menuPID;
  itfMenuSetFlagMenu(v27, 256, 128, ConfigGAME != 0);
  if (!evtBitCheck(42))
  {
    v30 = wk->menuPID;
    itfMenuSetFlagMenu(v30, 61441, 2, 0);
    goto LABEL_67;
  }
  if (evtBitCheck(2103))
    v28 = 43;
  else
    v28 = 65;
  evtBitCheck(v28);
LABEL_67:
  if (evtBitCheck(42))
  {
    if (evtBitCheck(2103))
      v31 = 43;
    else
      v31 = 65;
    evtBitCheck(v31);
LABEL_79:
    if (!evtBitCheck(42))
      goto LABEL_93;
    if (evtBitCheck(2103))
      v33 = 43;
    else
      v33 = 65;
    evtBitCheck(v33);
    goto LABEL_97;
  }
  if (evtBitCheck(9991))
  {
    goto LABEL_79;
  }
  v35 = wk->menuPID;
  itfMenuSetFlagMenu(v35, 61442, 2, 0);
  goto LABEL_79;
LABEL_93:
  v36 = wk->menuPID;
  itfMenuSetFlagMenu(v36, 458753, 2, 0);
LABEL_97:
  if (!evtBitCheck(42))
    goto LABEL_111;
  if (evtBitCheck(2103))
    v37 = 43;
  else
    v37 = 65;
  if (evtBitCheck(v37))
  {
LABEL_108:
    if (!evtBitCheck(42))
      goto LABEL_126;
    goto LABEL_116;
  }
LABEL_111:
  v39 = wk->menuPID;
  itfMenuSetFlagMenu(v39, 128, 2, 0);
  goto LABEL_108;
LABEL_116:
  if (evtBitCheck(2103))
    v40 = 43;
  else
    v40 = 65;
  if (evtBitCheck(v40))
  {
    goto LABEL_123;
  }
LABEL_126:
  v42 = wk->menuPID;
  itfMenuSetFlagMenu(v42, 262146, 2, 0);
LABEL_123:
  if (!evtBitCheck(42))
    goto LABEL_153;
  if (evtBitCheck(2103))
    v43 = 43;
  else
    v43 = 65;
  evtBitCheck(v43);
  if (evtBitCheck(10009))
  {
LABEL_138:
    if (evtBitCheck(42))
      goto LABEL_158;
LABEL_141:
    if (evtBitCheck(42))
      goto LABEL_166;
    if (!evtBitCheck(10040))
      goto LABEL_172;
LABEL_144:
LABEL_145:
    goto LABEL_146;
  }
LABEL_153:
  v48 = wk->menuPID;
  itfMenuSetFlagMenu(v48, 256, 2, 0);
  goto LABEL_138;
LABEL_158:
  if (evtBitCheck(2103))
    v49 = 43;
  else
    v49 = 65;
  evtBitCheck(v49);
  goto LABEL_141;
LABEL_166:
  if (evtBitCheck(2103))
    v50 = 43;
  else
    v50 = 65;
  evtBitCheck(v50);
  if (evtBitCheck(10040))
    goto LABEL_144;
LABEL_172:
  v51 = wk->menuPID;
  itfMenuSetFlagMenu(v51, 512, 2, 0);
  goto LABEL_145;
LABEL_146:
  if (!evtBitCheck(42))
    return;
  if (evtBitCheck(2103))
    v47 = 43;
  else
    v47 = 65;
  evtBitCheck(v47);
}

// 0x1f52a40
s32 cmpSubMenuAnimFunc(s32 mode) {
  Il2CppClass *klass;
  s32 v6;

  if (mode == 1)
  {
    klass = _get_Instance()[7].klass;
    v6 = 2;
    goto LABEL_10;
  }
  if (mode)
    return 1;
  klass = _get_Instance()[7].klass;
  if (subMenuActive)
  {
    v6 = 3;
LABEL_10:
    AnimSet(klass, v6, 0);
    return 1;
  }
  AnimSet(klass, 0, 0);
  subMenuActive = 1;
  return 1;
}

// 0x1f52b40
s32 cmpExSubMenuAnimFunc(s32 mode) {
  s32 v3;
  Il2CppObject *Instance;

  if (!mode)
  {
    v3 = 5;
    goto LABEL_7;
  }
  if (mode == 1)
  {
    v3 = 6;
LABEL_7:
    Instance = _get_Instance();
    AnimSet(Instance[7].klass, v3, 0);
  }
  return 1;
}

// 0x1f52bc0
s32 cmpWeaponMenuAnimFunc(s32 mode) {
  Il2CppObject *Instance;

  if ((u32)mode > 1)
    return 1;
  Instance = _get_Instance();
  AnimSet(Instance[11].klass, mode, 0);
  return 1;
}

// 0x1f52c40
void cmpSetMenu(tagCMP_WORK *wk) {
  dds3ProcessID_t *menuPID;
  itfMenuFunc_t v4;
  char *v6;
  char *v8;
  itfMoverFunc_t v9;
  char *v11;
  char *v13;
  char *v15;
  char *v17;
  char *v19;
  char *v21;
  char *v23;
  char *v25;
  char *v27;
  char *v29;
  char *v31;
  char *v33;
  char *v35;
  char *v37;
  char *v39;
  char *v41;
  char *v43;
  char *v45;
  itfMenuDrawFunc_t v46;
  itfMenuDrawFunc_t v47;
  char *v49;
  char *v51;
  char *v53;
  char *v55;
  char *v57;
  char *v59;
  char *v61;
  char *v63;
  char *v65;
  char *v67;
  char *v69;
  char *v71;
  itfMenuDrawFunc_t v72;
  s32 ConfigGAME;
  tagCMP_WORK *Work;

  menuPID = wk->menuPID;
  v4 = Allocate(itfMenuFunc_t);
  _ctor(v4, 0, Method_Project_cmpMain_CallFunc__, 0);
  v6 = cmpGetstrCmpMenuHD(0, 0);
  v8 = cmpGetstrCmpMenuHD(0, 1);
  itfMenuSetMenuTitle(menuPID, v6, v8);
  v9 = Allocate(itfMoverFunc_t);
  _ctor(v9, 0, Method_Project_cmpMain_SubMenuAnimFunc__, 0);
  itfMoverSetMenu(menuPID, v9);
  v11 = cmpGetstrCmpMenuHD(61441, 0);
  v13 = cmpGetstrCmpMenuHD(61441, 1);
  itfMenuSetMenu(menuPID, 61441, -1, v11, v4, v13);
  v15 = cmpGetstrCmpMenuHD(61442, 0);
  v17 = cmpGetstrCmpMenuHD(61442, 1);
  itfMenuSetMenu(menuPID, 61442, -1, v15, v4, v17);
  v19 = cmpGetstrCmpMenuHD(458753, 0);
  v21 = cmpGetstrCmpMenuHD(458753, 1);
  itfMenuSetMenu(menuPID, 458753, -1, v19, v4, v21);
  v23 = cmpGetstrCmpMenuHD(128, 0);
  v25 = cmpGetstrCmpMenuHD(128, 1);
  itfMenuSetMenu(menuPID, 128, -1, v23, v4, v25);
  v27 = cmpGetstrCmpMenuHD(262146, 0);
  v29 = cmpGetstrCmpMenuHD(262146, 1);
  itfMenuSetMenu(menuPID, 262146, -1, v27, v4, v29);
  v31 = cmpGetstrCmpMenuHD(256, 0);
  v33 = cmpGetstrCmpMenuHD(256, 1);
  itfMenuSetMenu(menuPID, 256, -1, v31, v4, v33);
  evtBitCheck(42);
  v35 = cmpGetstrCmpMenuHD(64, 0);
  v37 = cmpGetstrCmpMenuHD(64, 1);
  itfMenuSetMenu(menuPID, 64, -1, v35, v4, v37);
  v39 = cmpGetstrCmpMenuHD(512, 0);
  v41 = cmpGetstrCmpMenuHD(512, 1);
  itfMenuSetMenu(menuPID, 512, -1, v39, v4, v41);
  v43 = cmpGetstrCmpMenuHD(16, 0);
  v45 = cmpGetstrCmpMenuHD(16, 1);
  itfMenuSetMenu(menuPID, 16, -1, v43, v4, v45);
  v46 = Allocate(itfMenuDrawFunc_t);
  _ctor(v46, 0, Method_Project_cmpMain_DrawMenuFunc__, 0);
  itfMenuSetDrawFunc(menuPID, 61441, v46, 0);
  v47 = Allocate(itfMenuDrawFunc_t);
  _ctor(v47, 0, Method_Project_cmpMain_DrawMenuFunc__, 0);
  itfMenuSetDrawFunc(menuPID, 61442, v47, 0);
  v49 = cmpGetstrCmpMenuHD(196610, 0);
  v51 = cmpGetstrCmpMenuHD(196610, 1);
  itfMenuSetMenu(menuPID, 196610, 2, v49, v4, v51);
  v53 = cmpGetstrCmpMenuHD(393218, 0);
  v55 = cmpGetstrCmpMenuHD(393218, 1);
  itfMenuSetMenu(menuPID, 393218, 2, v53, v4, v55);
  v57 = cmpGetstrCmpMenuHD(65552, 0);
  v59 = cmpGetstrCmpMenuHD(65552, 1);
  itfMenuSetMenu(menuPID, 65552, 16, v57, v4, v59);
  itfMenuSetFlagMenu(menuPID, 65552, 64, 0);
  v61 = cmpGetstrCmpMenuHD(131088, 0);
  v63 = cmpGetstrCmpMenuHD(131088, 1);
  itfMenuSetMenu(menuPID, 131088, 16, v61, v4, v63);
  v65 = cmpGetstrCmpMenuHD(262160, 0);
  v67 = cmpGetstrCmpMenuHD(262160, 1);
  itfMenuSetMenu(menuPID, 262160, 16, v65, v4, v67);
  v69 = cmpGetstrCmpMenuHD(524304, 0);
  v71 = cmpGetstrCmpMenuHD(524304, 1);
  itfMenuSetMenu(menuPID, 524304, 16, v69, v4, v71);
  v72 = Allocate(itfMenuDrawFunc_t);
  _ctor(v72, 0, Method_Project_cmpMain_DrawMenuFunc__, 0);
  itfMenuSetDrawFunc(menuPID, 327681, v72, 0);
  itfMenuSetFlagMenu(menuPID, 65537, 128, 1);
  itfMenuSetFlagMenu(menuPID, 262145, 128, 1);
  itfMenuSetFlagMenu(menuPID, 196609, 128, 1);
  itfMenuSetFlagMenu(menuPID, 131073, 128, 1);
  itfMenuSetFlagMenu(menuPID, 393217, 128, 1);
  itfMenuSetFlagMenu(menuPID, 458753, 128, 1);
  ConfigGAME = cfgGetConfigGAME(16, 0);
  itfMenuSetFlagMenu(menuPID, 256, 128, ConfigGAME != 0);
  itfMenuSetFlagMenu(menuPID, 61441, 512, 0);
  itfMenuSetFlagMenu(menuPID, 458753, 512, 0);
  itfMenuSetFlagMenu(menuPID, 262160, 128, 1);
  itfMenuSetFlagMenu(menuPID, 262160, 512, 1);
  itfMenuSetFlagMenu(menuPID, 524304, 128, 1);
  itfMenuSetFlagMenu(menuPID, 524304, 512, 1);
  itfMenuSetCancelSE(menuPID, 61441, -2);
  itfMenuSetCancelSE(menuPID, 2, -2);
  itfMenuSetCancelSE(menuPID, 1, -2);
  itfMenuSetCancelSE(menuPID, 65537, -2);
  itfMenuSetCancelSE(menuPID, 8, -2);
  itfMenuSetCancelSE(menuPID, 128, -2);
  itfMenuSetCancelSE(menuPID, 64, -2);
  itfMenuSetCancelSE(menuPID, 512, -2);
  itfMenuSetCancelSE(menuPID, 16, -2);
  itfMenuSetCancelSE(menuPID, 458753, -2);
  itfMenuSetCancelSE(menuPID, 61442, -2);
  itfMenuSetCancelSE(menuPID, 262146, -2);
  itfMenuSetCancelSE(menuPID, 256, -2);
  cmpChkEnableSelectMenu(wk);
  itfMenuSetFlag(menuPID, 16, 0);
  itfMenuSetMoveAppear(menuPID, 1);
  itfMenuSetMoveDisappear(menuPID, 1);
  if (wk->runmode == 1)
  {
    Work = cmpGetWork();
    if (!Work)
    {
LABEL_29:
      wk->menuID = 131088;
      itfMenuSetInitSelectID(menuPID, 131088);
      goto LABEL_32;
    }
    Work->nowTitle = 8;
    goto LABEL_29;
  }
LABEL_32:
  itfMenuStart(menuPID);
}

// 0x1f536d0
void cmpPanelChange(tagCMP_WORK *_wk) {
  dds3ProcessID_t *charPID;
  dds3ProcessID_t *stockPID;
  s32 v11;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *v18;
  s32 changeActivePanel;
  s32 stockPanelActive;
  dds3ProcessID_t *v27;
  dds3ProcessID_t *Work;
  dds3ProcessID_t *v33;
  dds3ProcessID_t *v37;
  bool v41;

  if (wk->step <= 12)
  {
    if (cmpGetWork())
    {
      charPID = cmpGetWork()->charPID;
      goto LABEL_12;
    }
    charPID = 0;
LABEL_12:
    if (itfMenuGetFlag(charPID, 8u))
      goto LABEL_51;
    if (cmpGetWork())
    {
      stockPID = cmpGetWork()->stockPID;
LABEL_21:
      if (itfMenuGetFlag(stockPID, 8u) || (v11 = wk->stockPanelActive) == 0)
      {
LABEL_51:
        changeActivePanel = wk->changeActivePanel;
        stockPanelActive = wk->stockPanelActive;
        if (stockPanelActive == changeActivePanel)
          return;
        wk->stockPanelActive = changeActivePanel;
        wk->oldActive = stockPanelActive;
        if (changeActivePanel != 1)
        {
          if (changeActivePanel == 2)
          {
            if (cmpGetWork())
            {
              v27 = cmpGetWork()->charPID;
              goto LABEL_63;
            }
            v27 = 0;
LABEL_63:
            itfMenuSetFlag(v27, 8, 0);
            Work = cmpGetWork();
            if (!Work)
              goto LABEL_100;
            goto LABEL_97;
            if (!Work)
            {
LABEL_100:
              v41 = 1;
LABEL_94:
              itfMenuSetFlag(Work, 8, v41);
              return;
            }
LABEL_97:
            Work = cmpGetWork()->stockPID;
            goto LABEL_100;
          }
          if (cmpGetWork())
          {
            v37 = cmpGetWork()->charPID;
            goto LABEL_85;
          }
          v37 = 0;
LABEL_85:
          itfMenuSetFlag(v37, 8, 0);
LABEL_87:
          Work = cmpGetWork();
          if (Work)
          {
            Work = cmpGetWork()->stockPID;
          }
          v41 = 0;
          goto LABEL_94;
        }
        if (cmpGetWork())
        {
          v33 = cmpGetWork()->charPID;
          goto LABEL_75;
        }
        v33 = 0;
LABEL_75:
        itfMenuSetFlag(v33, 8, 1);
        goto LABEL_87;
      }
      *(u64 *)&wk->changeActivePanel = 0;
      wk->oldActive = v11;
      if (cmpGetWork())
      {
        v15 = cmpGetWork()->charPID;
        goto LABEL_31;
      }
      v15 = 0;
LABEL_31:
      itfMenuSetFlag(v15, 8, 0);
      v18 = cmpGetWork();
      if (!v18)
        goto LABEL_50;
      goto LABEL_47;
      if (!v18)
      {
LABEL_50:
        itfMenuSetFlag(v18, 8, 0);
        goto LABEL_51;
      }
LABEL_47:
      v18 = cmpGetWork()->stockPID;
      goto LABEL_50;
    }
    stockPID = 0;
    goto LABEL_21;
  }
}

// 0x1f51910
void cmpRaidouBackChange(BackRaiAnim _changeAnim) {
  tagCMP_WORK *Work;

  Work = cmpGetWork();
  if (!Work)
    return;
  Work->nowBackRaiAnim = changeAnim;
}

// 0x1f50e80
void TitleChange(CmpTitle _cmpTitle) {
  tagCMP_WORK *Work;

  Work = cmpGetWork();
  if (!Work)
    return;
  Work->nowTitle = cmpTitle;
}

// 0x1f53d40
bool cmpTipsCalc(tagCMP_WORK *_wk) {
  dds3ProcessID_t *menuPID;
  tagCMP_WORK *Work;
  dds3ProcessID_t *v9;
  tagCMP_WORK *v11;

  if (evtBitCheck(10009))
    goto LABEL_19;
  if (datGetStockReprtStok() < 1)
    goto LABEL_19;
  menuPID = cmpGetWork()->menuPID;
  itfMenuSetFlag(menuPID, 256, 1);
  Work = cmpGetWork();
  itfMenuSetFlag(Work->listPID, 256, 1);
  tipsTIPSStart(25);
  wk->tips = 1;
LABEL_19:
  if (!wk->tips)
    return 0;
  if (tipsProcessCheck())
    return 1;
  if (!wk->tips)
    return 0;
  v9 = cmpGetWork()->menuPID;
  itfMenuSetFlag(v9, 256, 0);
  v11 = cmpGetWork();
  itfMenuSetFlag(v11->listPID, 256, 0);
  wk->tips = 0;
  return 0;
}

// 0x1f54050
void cmpSelectUpdate(tagCMP_WORK *_wk) {
  const MethodInfo_32670E0 *v3;
  Il2CppObject *Instance;
  dds3ProcessID_t *menuPID;
  s32 CtrlType;
  s32 SelectID;
  dds3ProcessID_t *charPID;
  dds3ProcessID_t *v12;
  u32 v13;
  u64 v14;
  dds3ProcessID_t *v15;
  tagCMP_WORK *Work;
  dds3ProcessID_t *v19;
  u64 v20;

  cmpTipsCalc(wk);
  v3 = Method_Project_SingletonMonoBehaviour_CampManager__get_Instance__;
  exMenu = 0;
  Instance = _get_Instance(v3);
  ExtendMenuOff(Instance[7].klass, 0);
  menuPID = wk->menuPID;
  CtrlType = itfMenuGetCtrlType(menuPID);
  SelectID = itfMenuGetSelectID(wk->menuPID);
  if (CtrlType != 4)
  {
    if (CtrlType == 5)
    {
      g_endmode = 0;
      SE(18);
      charPID = wk->charPID;
      goto LABEL_13;
    }
    goto LABEL_39;
  }
  if (SelectID > 511)
  {
    if (SelectID > 131087)
    {
      if (SelectID != 262146)
      {
        if (SelectID == 131088)
        {
          g_endmode = 1;
          charPID = wk->charPID;
LABEL_13:
          itfMenuSetFlag(charPID, 2048, 1);
          itfMenuSetFlag(wk->stockPID, 2048, 1);
          wk->count = 0;
          wk->step = 14;
          return;
        }
        goto LABEL_39;
      }
    }
    else if (SelectID != 512 && SelectID != 65552)
    {
      goto LABEL_39;
    }
LABEL_36:
    v12 = wk->charPID;
    itfMenuSetFlag(v12, 2048, 1);
    itfMenuSetFlag(wk->stockPID, 2048, 1);
    goto LABEL_39;
  }
  if (SelectID > 127)
  {
    if (SelectID != 128)
    {
      if (SelectID != 256)
        goto LABEL_39;
      if (cfgGetConfigGAME(16, 0))
        goto LABEL_39;
    }
    goto LABEL_36;
  }
  if (SelectID == 8)
  {
    v19 = wk->charPID;
    itfMenuSetFlag(v19, 2048, 1);
    itfMenuSetFlag(wk->stockPID, 2048, 1);
    dds3FadeOut(0, 0, 0, 0xAu);
    HIDWORD(v20) = wk->menuID - 16;
    LODWORD(v20) = HIDWORD(v20);
    v13 = v20 >> 16;
    if (v13 > 8)
      return;
    goto LABEL_40;
  }
  if (SelectID == 64)
    goto LABEL_36;
LABEL_39:
  HIDWORD(v14) = wk->menuID - 16;
  LODWORD(v14) = HIDWORD(v14);
  v13 = v14 >> 16;
  if (v13 > 8)
    return;
LABEL_40:
  if (((1 << v13) & 0x117) != 0 && CtrlType == 3)
  {
    v15 = wk->menuPID;
    if (itfMenuGetHierarchy(v15))
    {
      Work = cmpGetWork();
      if (!Work)
        return;
      Work->nowTitle = 0;
      return;
    }
  }
}

// 0x1f54450
void cmpContentUpdate(tagCMP_WORK *_wk) {
  s32 menuID;
  void *v4;
  dds3ProcessID_t *menuPID;
  s32 v7;
  bool v8;
  dds3ProcessID_t *charPID;
  void *v11;
  Il2CppObject *Instance;
  Il2CppClass *klass;
  void *v15;
  Il2CppObject *v17;
  Il2CppObject *v18;
  bool v19;
  Il2CppClass *v20;
  tagCMP_WORK *Work;
  Il2CppObject *v23;
  void *v25;
  Il2CppObject *v28;
  Il2CppClass *v29;
  tagCMP_WORK *v31;
  Il2CppClass *v32;
  s32 v33;
  void *v35;
  dds3ProcessID_t *v37;
  s32 v38;
  dds3ProcessID_t *v41;
  Il2CppObject *v43;
  void *v45;
  dds3ProcessID_t *v47;
  s32 stat;

  menuID = wk->menuID;
  if ((menuID & 1) != 0)
  {
    menuPID = wk->menuPID;
    itfMenuGetSelectID(menuPID);
    v7 = wk->menuID;
    v8 = Update(v7, 0);
    charPID = wk->charPID;
    itfMenuGetCtrlType(wk->charPID);
    if (!v8)
      return;
    goto LABEL_29;
  }
  if ((menuID & 2) != 0)
  {
    if (Update())
      goto LABEL_29;
    return;
  }
  if ((menuID & 0x80) != 0)
  {
    v11 = *((void *)_get_Instance()[7].monitor + 2);
    if (get_activeSelf(v11, 0))
    {
      SetActive(v11, 0, 0);
LABEL_34:
      if (ProcessCheck())
      {
LABEL_35:
        Instance = _get_Instance();
        TopAnimSet(Instance[5].klass, 0, 0, 0);
        klass = _get_Instance()[5].klass;
        AnimSet(klass, 5, 1, 0);
        return;
      }
LABEL_42:
      Work = cmpGetWork();
      if (!Work)
        goto LABEL_47;
      goto LABEL_46;
      if (!Work)
      {
LABEL_47:
        v23 = _get_Instance();
        AnimSet(v23[5].klass, 5, 0, 0);
        ++wk->count;
        if (dds3FadeCheck())
          return;
        if (sdfMemCheckRelease())
          return;
LABEL_91:
        if (wk->count < 30)
          return;
        wk->count = 0;
        dds3FadeIn(0, 0, 0, 0x14u);
        goto LABEL_95;
      }
LABEL_46:
      Work->nowBackRaiAnim = 0;
      goto LABEL_47;
    }
    else
    {
      goto LABEL_34;
    }
    if (ProcessCheck())
      goto LABEL_35;
    goto LABEL_42;
  }
  if ((menuID & 0x40) != 0)
  {
    v15 = *((void *)_get_Instance()[7].monitor + 2);
    if (get_activeSelf(v15, 0))
    {
      SetActive(v15, 0, 0);
LABEL_38:
      if (ProcessCheck())
      {
LABEL_39:
        v17 = _get_Instance();
        TopAnimSet(v17[5].klass, 0, 0, 0);
        v18 = _get_Instance();
        AnimSet(v18[5].klass, 1, 1, 0);
        v19 = evtBitCheck(42);
        v20 = _get_Instance()[5].klass;
        BookSpriteSet(v20, !v19, 0);
        return;
      }
LABEL_60:
      v31 = cmpGetWork();
      if (!v31)
      {
LABEL_65:
        v32 = _get_Instance()[5].klass;
        v33 = 1;
        goto LABEL_88;
      }
      v31->nowBackRaiAnim = 0;
      goto LABEL_65;
    }
    else
    {
      goto LABEL_38;
    }
    if (ProcessCheck())
      goto LABEL_39;
    goto LABEL_60;
  }
  if ((menuID & 0x200) != 0)
  {
    v25 = *((void *)_get_Instance()[7].monitor + 2);
    if (get_activeSelf(v25, 0))
    {
      SetActive(v25, 0, 0);
LABEL_56:
      if (ProcessCheck())
      {
LABEL_57:
        v28 = _get_Instance();
        TopAnimSet(v28[5].klass, 0, 0, 0);
        v29 = _get_Instance()[5].klass;
        AnimSet(v29, 8, 1, 0);
        return;
      }
      goto LABEL_85;
    }
    else
    {
      goto LABEL_56;
    }
    if (ProcessCheck())
      goto LABEL_57;
LABEL_85:
    cmpRaidouBackChange(0);
    v32 = _get_Instance()[5].klass;
    v33 = 8;
LABEL_88:
    AnimSet(v32, v33, 0, 0);
    ++wk->count;
    if (dds3FadeCheck())
      return;
    goto LABEL_91;
  }
  if ((menuID & 0x100) != 0)
  {
    Update(wk->dvlReportMachine, 0);
    if (!wk->dvlReportMachine->end)
      return;
    v35 = get_Instance(0);
    ItfButtonGuideActive(v35, 1, 0);
    cmpCmpGuideSet(0, 0, 90);
    fclGetLogStop(g_mainPID, 0);
    scrLogFlgReset();
    if (cfgGetConfigGAME(16, 0))
    {
      v37 = wk->menuPID;
      v38 = wk->menuID;
      itfMenuSetFlagMenu(v37, v38, 2048, 0);
    }
    else
    {
      v47 = wk->charPID;
      itfMenuSetFlag(v47, 4096, 1);
      itfMenuSetFlag(wk->stockPID, 4096, 1);
    }
    stat = wk->stat;
    wk->dvlReportMachine = 0;
    wk->stat = stat | 8;
    goto LABEL_29;
  }
  if (menuID != 65552)
  {
    if (menuID != 8 || !ProcessCheck())
      return;
    v4 = get_Instance(0);
    ItfButtonGuideSet(v4, 1, 0);
    wk->stat |= 8u;
    dds3FadeIn(0, 0, 0, 0xAu);
    goto LABEL_96;
  }
  v43 = _get_Instance();
  sub_1BB07C0(*((u64 *)v43[7].monitor + 2), 0, 0);
  if (!ProcessCheck())
  {
    TitleChange(8);
    v45 = get_Instance(0);
    ItfButtonGuideSet(v45, 1, 0);
    cmpCmpGuideSet(0, 0, 90);
LABEL_95:
    wk->stat |= 8u;
LABEL_96:
    v41 = wk->charPID;
    itfMenuSetFlag(v41, 4096, 1);
    itfMenuSetFlag(wk->stockPID, 4096, 1);
LABEL_29:
    cmpChkEnableSelectMenu(wk);
    wk->count = 0;
    wk->helpDispflg = 0;
    wk->step = 13;
  }
}

// 0x1f54de0
void cmpRodiouMeganeCheck(void) {
  if (!IsRmegane())
    return;
  if (datCheckItem(760, 1))
    return;
  datAddItem(760, 1);
}

// 0x1f54ef0
void Init(tagCMP_WORK *wk) {
  u32 v6;
  CmpCsrSave *v8;
  RaidouSKillCsrSave *v10;
  void *v12;
  void *p_skillListSelectSave;
  void *v14;
  u64 *v15;
  s64 size;
  u32 *items;
  u32 v18;
  s64 v19;
  u32 v20;

  cmpLoadLocalizeText();
  cmpRodiouMeganeCheck();
  StockDevilNums = datGetStockDevilNums(0);
  wk->stat = 0;
  wk->count = 0;
  wk->tabpage = 0;
  *(u64 *)&wk->menuID = -1;
  wk->tabpagestockmax = ((u64)(954437177 * (s32)StockDevilNums) >> 33)
                             + ((u64)(954437177 * (s32)StockDevilNums) >> 63);
  v6 = 57 * GBWK->player->stock_max;
  wk->tabpagemax = (char)(((v6 & 0x8000) != 0) + (v6 >> 9));
  cmpUpdateBulletNum();
  cmpResetMotion(0);
  wk->countMotMoya = 0;
  *(u64 *)&wk->changeActivePanel = 0;
  *(u64 *)&wk->nowBackRaiAnim = 0;
  wk->tips = 0;
  v8 = Allocate(CmpCsrSave);
  _ctor(v8);
  wk->csrSave = v8;
  v10 = Allocate(RaidouSKillCsrSave);
  _ctor(v10, 0);
  wk->rSkillCsrSave = v10;
  wk->rSkillTabSave = 0;
  v12 = Allocate(System_Collections_Generic_List_LIST_SELECT_);
  __ctor_47784064(v12, 2);
  wk->skillListSelectSave = v12;
  p_skillListSelectSave = &wk->skillListSelectSave;
  v14 = p_skillListSelectSave;
  v15 = Method_System_Collections_Generic_List_LIST_SELECT__Add__;
  size = p_skillListSelectSave->_size;
  v14->_version = p_skillListSelectSave->_version + 1;
  items = v14->_items;
  v18 = items[6];
  if ((u32)size >= v18)
  {
    _AddWithResize(v14, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v15[4] + 192) + 112));
    v14 = p_skillListSelectSave;
    v15 = Method_System_Collections_Generic_List_LIST_SELECT__Add__;
    items = p_skillListSelectSave->_items;
    v20 = items[6];
    v19 = p_skillListSelectSave->_size;
    ++p_skillListSelectSave->_version;
    if ((u32)v19 >= v20)
      goto LABEL_11;
  }
  else
  {
    v14->_size = size + 1;
    items[size + 8] = 0;
    v19 = v14->_size;
    ++v14->_version;
    if ((u32)v19 >= v18)
    {
LABEL_11:
      _AddWithResize(v14, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v15[4] + 192) + 112));
      return;
    }
  }
  v14->_size = v19 + 1;
  items[v19 + 8] = 0;
}

// 0x1f552a0
void cmpUiInit(void) {
  u32 SummonerRank2SprNo;
  Il2CppClass *klass;
  s32 v3;
  Il2CppClass **typeHierarchy;
  char *v6;
  char *LocalizeText;
  Il2CppClass *v8;
  Il2CppObject *Instance;
  void *gameObject;
  Il2CppClass *v11;
  void *v12;
  Il2CppObject *v13;

  SummonerRank2SprNo = cmpGetSummonerRank2SprNo(0);
  klass = _get_Instance()[8].klass;
  if (SummonerRank2SprNo <= 1)
    v3 = 1;
  else
    v3 = SummonerRank2SprNo;
  typeHierarchy = klass->_2.typeHierarchy;
  v6 = rankText[v3];
  LocalizeText = GetLocalizeText(v6, 1);
  ((*typeHierarchy)->vtable[66].methodPtr)(typeHierarchy, LocalizeText, (*typeHierarchy)->vtable[66].method);
  v8 = _get_Instance()[3].klass;
  if (!get_activeSelf(v8, 0))
    SetActive(v8, 1, 0);
  Instance = _get_Instance();
  gameObject = get_gameObject(Instance[3].monitor, 0);
  if (!get_activeSelf(gameObject, 0))
    SetActive(gameObject, 1, 0);
  v11 = _get_Instance()[4].klass;
  if (get_activeSelf(v11, 0))
    SetActive(v11, 0, 0);
  v12 = get_Instance(0);
  ItfButtonGuideSet(v12, 1, 0);
  v13 = _get_Instance();
  ExtendMenuOff(v13[7].klass, 0);
}

// 0x1f554a0
dds3ProcessFunc_t cmpProcess(dds3ProcessID_t *PID) {
  tagCMP_WORK *ProcessData;
  s32 count;
  s32 v11;
  s32 stat;
  tagCMP_WORK *Work;
  s32 v16;
  tagCMP_WORK *v19;
  s32 v20;
  Il2CppObject *v23;
  Il2CppObject *v24;
  s32 v25;
  dds3ProcessID_t *menuPID;
  tagCMP_WORK *v29;
  s32 v31;
  Il2CppObject *v35;
  Il2CppObject *Instance;
  dds3ProcessID_t *charPID;
  s32 menuID;
  dds3ProcessFunc_t v46;
  s32 v49;
  tagCMP_WORK *v52;
  dds3ProcessID_t *id;

  id = PID;
  goto LABEL_3;
LABEL_7:
  goto LABEL_9;
LABEL_3:
  ProcessData = dds3GetProcessData(id);
  if (ProcessData)
    goto LABEL_7;
LABEL_9:
  v52 = ProcessData;
  cmpPanelChange(ProcessData);
  switch (ProcessData->step)
  {
    case 0:
      ProcessData->count = 0;
      ProcessData->step = 1;
      goto LABEL_13;
    case 1:
LABEL_13:
      if (!BYTE1(_get_Instance()[4].monitor))
        return 0;
      count = ProcessData->count;
      if (!count)
      {
        ProcessData->stat |= 0x28u;
        cmpUiInit();
        Instance = _get_Instance();
        CallStart(Instance, 0, 1, 0);
        dds3FadeIn(0, 0, 0, 1u);
        cmpSetMenu(ProcessData);
        charPID = ProcessData->charPID;
        itfMenuStart(charPID);
        itfMenuStart(ProcessData->stockPID);
        goto LABEL_181;
      }
      if (count < 1)
        goto LABEL_182;
      ProcessData->count = 0;
      ProcessData->step = 2;
      goto LABEL_85;
    case 2:
      cmpSelectUpdate(ProcessData);
      return 0;
    case 3:
      count = ProcessData->count;
      if (count < 10)
        goto LABEL_182;
      ProcessData->stat &= ~8u;
      ProcessStart(0, 0, 0, 0, 0, 0);
      goto LABEL_63;
    case 4:
      v11 = ProcessData->count;
      if (v11 == 1)
      {
        menuID = ProcessData->menuID;
        if (menuID == 61441)
        {
          SortSetting(61441);
          cmpSetupDvlSkl(ProcessData->menuID);
        }
        else if (menuID == 327681)
        {
          Setup(327681, 0);
        }
        else if ((menuID & 2) != 0)
        {
          cmpSortSetting(menuID);
          Setup(ProcessData->menuID, 0);
        }
      }
      else if (v11)
      {
        if (v11 >= 2)
        {
LABEL_63:
          v25 = 5;
          goto LABEL_64;
        }
      }
      else
      {
        cmpLoadSpriteHnd(1);
      }
      goto LABEL_181;
    case 5:
      cmpContentUpdate(ProcessData);
      return 0;
    case 6:
      count = ProcessData->count;
      if (count < 10)
        goto LABEL_182;
      ProcessStart(-1, 0, 0);
      stat = ProcessData->stat;
      ProcessData->count = 0;
      ProcessData->step = 5;
      ProcessData->stat = stat & 0xFFFFFFF7;
      Work = cmpGetWork();
      if (!Work)
        return 0;
      Work->nowBackRaiAnim = 5;
      return 0;
    case 7:
      count = ProcessData->count;
      if (count < 20)
        goto LABEL_182;
      ProcessStart(0);
      v16 = ProcessData->stat;
      ProcessData->count = 0;
      ProcessData->step = 5;
      ProcessData->stat = v16 & 0xFFFFFFF7;
      v19 = cmpGetWork();
      if (!v19)
        return 0;
      v49 = 1;
      goto LABEL_166;
    case 8:
      count = ProcessData->count;
      if (count < 20)
        goto LABEL_182;
      QuestProcessStart();
      v20 = ProcessData->stat;
      ProcessData->count = 0;
      ProcessData->step = 5;
      ProcessData->stat = v20 & 0xFFFFFFF7;
      v19 = cmpGetWork();
      if (!v19)
        return 0;
      v49 = 8;
LABEL_166:
      v19->nowBackRaiAnim = v49;
      return 0;
    case 9:
      count = ProcessData->count;
      if (count < 10)
        goto LABEL_182;
      if (!cfgGetConfigGAME(16, 0))
      {
        ProcessData->stat &= ~8u;
        v23 = _get_Instance();
        (*(*(u64 *)v23[5].monitor + 392))(v23[5].monitor, 1, *(u64 *)(*(u64 *)v23[5].monitor + 400));
      }
      goto LABEL_63;
    case 0xA:
      ProcessData->stat &= ~8u;
      v24 = _get_Instance();
      (*(v24[6].klass->_1.image + 49))(v24[6].klass, 1, *((u64 *)v24[6].klass->_1.image + 50));
      ProcessStart(0);
      goto LABEL_63;
    case 0xB:
      count = ProcessData->count;
      if (count < 10)
        goto LABEL_182;
      cmpUpdateSuspend(v52);
      return 0;
    case 0xC:
      cmpEndMesChk(ProcessData);
      return 0;
    case 0xD:
      count = ProcessData->count;
      if (count < 2)
        goto LABEL_182;
      menuPID = ProcessData->menuPID;
      itfMenuSetFlag(menuPID, 8, 1);
      itfMenuSetFlagMenu(ProcessData->menuPID, -1, 8, 0);
      itfMenuStart(ProcessData->menuPID);
      itfMenuLinkSprite(ProcessData->listPID, 0);
      cmpFreeSpriteHnd(1);
      ProcessData->count = 0;
      ProcessData->step = 2;
      v29 = cmpGetWork();
      if (!v29)
        goto LABEL_82;
      goto LABEL_81;
      if (v29)
LABEL_81:
        v29->nowBackRaiAnim = 0;
LABEL_82:
      v31 = 8 * (ProcessData->menuID == 65552);
      TitleChange(v31);
LABEL_85:
      cmpCmpGuideSet(0, 0, 90);
      return 0;
    case 0xE:
      count = ProcessData->count;
      if (!count)
      {
        dds3FadeOut(0, 0, 0, 0xAu);
LABEL_181:
        count = ProcessData->count;
        goto LABEL_182;
      }
      if (count < 10)
        goto LABEL_182;
      v25 = 15;
      goto LABEL_64;
    case 0xF:
      if (!ProcessData->count)
      {
        cmpCallProcEnd(ProcessData);
        if (op_Inequality(map_win, 0, 0))
        {
          map_win->NxtAnimeNum = 3;
        }
      }
      if (cmpCheckProcEnd(ProcessData))
        goto LABEL_181;
      v25 = 16;
      goto LABEL_64;
    case 0x10:
      count = ProcessData->count;
      if (count)
      {
        if (count >= 2)
        {
          v25 = 17;
LABEL_64:
          ProcessData->count = 0;
          ProcessData->step = v25;
          return 0;
        }
      }
      else
      {
        ProcessData->stat &= ~8u;
      }
LABEL_182:
      ProcessData->count = count + 1;
      return 0;
    case 0x11:
      v35 = _get_Instance();
      CallEnd(v35, 0);
      if (g_endmode == 1)
      {
        _debugLoad_k__BackingField = 0;
LABEL_118:
        noDrawReport = 0;
        goto LABEL_153;
      }
      if (g_endmode == 2)
      {
        p2sdSndStopAll();
        evtMoonDisableDraw(1);
        dds3AdminiCallSequence2(2, 2, 0, 0);
        goto LABEL_118;
      }
      jmsProcessCheck();
LABEL_153:
      v46 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v46, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v46;
    case 0x12:
      if (!slUpdateAutoSave())
        return 0;
      goto LABEL_153;
    default:
      return 0;
  }
}

// 0x1f571c0
void cmpDebugLoadFlagOff(void) {
  _debugLoad_k__BackingField = 0;
  return;
}

// 0x1f57290
void cmpDrawTop(tagCMP_WORK *wk, u8 a_alphaRate) {
  s32 v6;
  s32 gold;
  s32 v12;
  char *v13;
  void *monitor;
  void *v16;
  void *v17;
  bool v18;
  void *v19;

  cmpGetSpriteHnd(0);
  v6 = a_alphaRate;
  cmpDrawEquipBullet(20, 322, v6, 0);
  if (g_GoldNoDspFlg)
  {
    if (!a_alphaRate)
      goto LABEL_27;
    goto LABEL_25;
  }
  if (!itemNumDraw)
  {
    v13 = 0;
    gold = GBWK->player->gold;
    monitor = _get_Instance()[7].monitor;
    goto LABEL_24;
  }
  gold = datGetItemNum(g_itemNo);
  v12 = g_itemNo;
  v13 = sdatItemName(v12);
  monitor = _get_Instance()[7].monitor;
LABEL_24:
  GoldTextDraw(monitor, gold, 0xA09DC380, itemNumDraw, v13, 0);
  if (!a_alphaRate)
  {
LABEL_27:
    v16 = *((void *)_get_Instance()[7].monitor + 2);
    if (!get_activeSelf(v16, 0))
      goto LABEL_33;
    v17 = v16;
    v18 = 0;
    goto LABEL_32;
  }
LABEL_25:
  if (g_GoldNoDspFlg)
    goto LABEL_27;
  v19 = *((void *)_get_Instance()[7].monitor + 2);
  if (get_activeSelf(v19, 0))
    goto LABEL_33;
  v17 = v19;
  v18 = 1;
LABEL_32:
  SetActive(v17, v18, 0);
LABEL_33:
  cmpDrawEquipBullet(20, 322, v6, 1);
}

// 0x1f57690
void cmpDrawHelpWindow(u8 a_alphaRate, CMP a_ot) {
  ;
}

// 0x1f576a0
void cmpDrawHelpText(tagCMP_WORK *wk, u8 a_alphaRate) {
  void *v4;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v6;
  s32 SelectID;
  Il2CppObject *Instance;
  char *Item;
  bool v13;
  Il2CppObject *v14;

  v4 = NewSpecific(CMP_MENU_ID, 0x1Fu);
  InitializeArray_55364416(v4, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__73A88D4334A70BEE3C6EACB60AB775E394A2E79EDFB2104E1B246A592D7C7CB0, 0);
  menuPID = wk->menuPID;
  if (!itfMenuProcessCheck(wk->menuPID))
    return;
  v6 = wk->menuPID;
  SelectID = itfMenuGetSelectID(v6);
  if (object___ContainsKey(helpName, SelectID))
  {
    if (cmpChkUnopenedMenu(SelectID))
    {
      Instance = _get_Instance();
      Item = "CMP_STATUS_L0019";
LABEL_15:
      HelpTextDraw(Instance, Item, 1, 0xA09DC380, 0);
      return;
    }
    v13 = evtBitCheck(42);
    v14 = _get_Instance();
    if (v13 || SelectID != 64)
    {
      Item = object___get_Item(helpName, SelectID);
    }
    else
    {
      Item = "CMP_HELP_L0034";
    }
    Instance = v14;
    goto LABEL_15;
  }
}

// 0x1f57920
void cmpDrawKeyReturnHelp(tagCMP_WORK *wk, u8 a_alphaRate1, u8 a_alphaRate2) {
  cmpGetSpriteHnd(0);
  if (fclChkMessageDraw() == 1)
    return;
  if (cmpChkMessageDraw() == 1)
    return;
  itfIconDrawSprite(438, 413, 0, a_alphaRate2, 13, 108);
}

// 0x1f57a90
void cmpDrawKeyHelp(tagCMP_WORK *wk, u8 a_alphaRate1, u8 a_alphaRate2) {
  cmpGetSpriteHnd(0);
  if (fclChkMessageDraw() == 1)
    return;
  if (cmpChkMessageDraw() == 1)
    return;
  itfIconDrawSprite(375, 413, 0, a_alphaRate1, 12, 108);
  itfIconDrawSprite(438, 413, 0, a_alphaRate2, 13, 108);
}

// 0x1f57c30
void cmpDrawKeyHelp2(tagCMP_WORK *wk, u8 a_alphaRate1, u8 a_alphaRate2) {
  cmpGetSpriteHnd(0);
  if (fclChkMessageDraw() == 1)
    return;
  if (cmpChkMessageDraw() == 1)
    return;
  itfIconDrawSprite(295, 413, 0, a_alphaRate2, 11, 108);
}

// 0x1f57da0
void cmpDrawKeyHelp3(tagCMP_WORK *wk, u8 a_alphaRate1, s32 ax) {
  s32 StockDevilNums;

  cmpGetSpriteHnd(0);
  StockDevilNums = datGetStockDevilNums(0);
  if (fclChkMessageDraw() == 1)
    return;
  if (cmpChkMessageDraw() == 1)
    return;
  if (StockDevilNums >= 9)
  {
    itfIconDrawSprite(ax + 215, 413, 0, a_alphaRate1, 15, 108);
  }
}

// 0x1f57f40
void cmpDrawTab(tagCMP_WORK *wk, u8 a_alphaRate1) {
  s32 stock_max;
  Il2CppObject *v5;
  char *v6;
  s32 StockDevilNums;
  Il2CppObject *Instance;
  s32 data;

  stock_max = GBWK->player->stock_max;
  data = stock_max;
  v5 = Box(s32, &data);
  v6 = Format("{0,2:d}", v5, 0);
  Concat_54766928(0, v6, 0);
  StockDevilNums = datGetStockDevilNums(0);
  Instance = _get_Instance();
  StockNumDraw(Instance[6].monitor, stock_max, StockDevilNums, 0xA09DC380, 0);
}

// 0x1f57620
void cmpDrawBulletData(s32 a_alphaRate) {
  cmpDrawEquipBullet(20, 322, a_alphaRate, 0);
}

// 0x1f58070
void cmpDrawBackSpriteAlpha(s32 a_sprNo, s32 a_x, s32 a_y, s32 a_alphaRate, sprHandle_t *a_hSpr) {
  ;
}

// 0x1f58080
void cmpDrawBackSprA1(s32 a_sprNo, s32 a_x, s32 a_y, s32 a_alphaRate) {
  cmpGetSpriteHnd(0);
  return;
}

// 0x1f58140
void cmpDrawBackSprA2(s32 a_sprNo, s32 a_x, s32 a_y, s32 a_alphaRate) {
  cmpGetSpriteHnd(2);
  return;
}

// 0x1f58200
void cmpDrawBackPartsA(s32 a_x, s32 a_y, s32 a_alphaRate) {
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  return;
}

// 0x1f58810
void cmpDrawBackPartsB(s32 a_x, s32 a_y, s32 a_alphaRate) {
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  return;
}

// 0x1f58e20
void cmpDrawBackGradation(s32 a_rate) {
  ;
}

// 0x1f58e30
void cmpDrawBackStat2(s32 a_alphaRate) {
  cmpGetSpriteHnd(2);
  return;
}

// 0x1f58f40
void cmpDrawBackStat4(s32 a_alphaRate) {
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  return;
}

// 0x1f59dd0
void cmpDrawBackMain1(s32 a_alphaRate) {
  s32 v8;
  s32 v9;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v24;
  s32 v25;
  s32 v26;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v32;
  s32 v33;
  s32 v34;

  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpDrawBackPartsA((s32)cmpMain, v8, v9);
  cmpDrawBackPartsA(v12, v13, v14);
  cmpDrawBackPartsA(v16, v17, v18);
  cmpDrawBackPartsA(v20, v21, v22);
  cmpDrawBackPartsA(v24, v25, v26);
  cmpDrawBackPartsA(v28, v29, v30);
  cmpDrawBackPartsA(v32, v33, v34);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  return;
}

// 0x1f5a0f0
void cmpDrawBackMain3(s32 a_alphaRate) {
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  return;
}

// 0x1f5b700
void cmpDrawBackMain5(s32 a_alphaRate) {
  s32 v2;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v49;
  s32 v50;
  s32 v51;

  cmpDrawBackPartsB((s32)cmpMain, (s32)v2);
  cmpDrawBackPartsB(v5, v6, v7);
  cmpDrawBackPartsB(v9, v10, v11);
  cmpDrawBackPartsB(v13, v14, v15);
  cmpDrawBackPartsB(v17, v18, v19);
  cmpDrawBackPartsB(v21, v22, v23);
  cmpDrawBackPartsB(v25, v26, v27);
  cmpDrawBackPartsB(v29, v30, v31);
  cmpDrawBackPartsB(v33, v34, v35);
  cmpDrawBackPartsB(v37, v38, v39);
  cmpDrawBackPartsB(v41, v42, v43);
  cmpDrawBackPartsB(v45, v46, v47);
  cmpDrawBackPartsB(v49, v50, v51);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  cmpGetSpriteHnd(0);
  return;
}

// 0x1f5b9a0
void MainDrawBack(tagCMP_WORK *wk, s32 a_alphaRate) {
  ;
}

// 0x1f5b9b0
bool cmpHelpDrawCheckUnity(tagCMP_WORK *_wk, CMP_MENU_ID _id) {
  if ((id & 2) != 0 && wk->step == 5)
    return 0;
  return (id & 0xF001) == 0 || (wk->step & 0xFFFFFFFE) != 4;
}

// 0x1f5ba00
dds3ProcessFunc_t cmpDrawProcess(dds3ProcessID_t *PID) {
  tagCMP_WORK *ProcessData;
  s32 stat;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v8;
  s32 CtrlType;
  dds3ProcessID_t *v10;
  s32 SelectID;
  u8 Alpha;
  u8 v13;
  int32x4_t v14;
  bool v15;
  bool v16;
  char v17;
  Il2CppObject *Instance;
  void *gameObject;
  tagCMP_WORK *v23;
  u8 v26;
  u8 v31;
  dds3ProcessID_t *v32;
  s32 v35;
  dds3ProcessID_t *charPID;
  u8 v38;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  stat = ProcessData->stat;
  if ((stat & 8) == 0)
    return 0;
  menuPID = ProcessData->menuPID;
  if (!itfMenuProcessCheck(menuPID))
    return 0;
  v8 = ProcessData->menuPID;
  CtrlType = itfMenuGetCtrlType(v8);
  v10 = ProcessData->menuPID;
  SelectID = itfMenuGetSelectID(v10);
  Alpha = itfMenuImgGetAlpha(ProcessData->menuPID, 1);
  v13 = Alpha;
  if (CtrlType != 5)
  {
    if ((SelectID & 2) != 0 || ((v14 = vdupq_n_s32(SelectID), (SelectID & 1) != 0) ? (v15 = SelectID == 65537) : (v15 = 1), !v15 ? (v16 = SelectID == 393217) : (v16 = 1), !v16 ? (v17 = 0) : (v17 = 1), (vmaxv_u16(vmovn_s32(vtstq_s32(v14, (int32x4_t)xmmword_3D026D0))) & 1) != 0 || (v13 = Alpha, (v17 & 1) == 0)))
    {
      v13 = -1;
    }
  }
  Instance = _get_Instance();
  gameObject = get_gameObject(Instance, 0);
  if (get_activeSelf(gameObject, 0))
  {
    cmpUnityUiDraw();
LABEL_37:
    cmpDrawTop(cmpMain, v13);
    if (!v13)
      goto LABEL_55;
    goto LABEL_43;
  }
  else
  {
    goto LABEL_37;
  }
  cmpDrawTop(v23, v13);
  if (!v13)
    goto LABEL_55;
LABEL_43:
  if (!cmpNowStatus())
  {
    if (((SelectID & 2) == 0 || ProcessData->step != 5) && ((SelectID & 0xF001) == 0 || (ProcessData->step & 0xFFFFFFFE) != 4))
    {
      cmpDrawHelpText(ProcessData, v26);
    }
  }
LABEL_55:
  cmpMenuTitleDrawUnity();
  cmpUnityBackRaidouDraw();
  if (!ProcessData->helpNoDisp)
  {
    v31 = v13;
    if (SelectID == 196610)
    {
      if (CtrlType == 4 || (v31 = v13, CtrlType == 1))
        v31 = Alpha;
    }
    if (ProcessData->step == 5)
      goto LABEL_77;
    v32 = ProcessData->menuPID;
    if (itfMenuGetHierarchy(v32))
    {
      if ((CtrlType & 1) == 0 || (SelectID & 2) == 0)
        goto LABEL_74;
      v35 = 4;
    }
    else
    {
      v35 = 0;
    }
    cmpCmpGuideSet(v35, 0, 90);
LABEL_74:
    cmpDrawKeyHelp(cmpMain, v31, v13);
  }
LABEL_77:
  if (!ProcessData->tabNoDisp)
  {
    charPID = ProcessData->charPID;
    itfMenuImgGetAlpha(charPID, 1);
    cmpDrawTab(cmpMain, v38);
  }
  return 0;
}

// 0x1f5be80
CMP_MODE cmpGetEndMode(void) {
  return g_endmode;
}

// 0x1f5bf00
void cmpSetMarkID(s32 a_markID) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[5].klass) = a_markID;
}

// 0x1f5c020
s32 cmpGetMarkID(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[21];
  return ProcessData[21];
}

// 0x1f5c130
void cmpRelease(tagCMP_WORK *wk) {
  Il2CppObject *Instance;

  End();
  cmpFreeSpriteToGS();
  Instance = _get_Instance();
  UIDestroy(Instance, 0, 0);
}

// 0x1f5c1e0
void cmpShutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  cmpRelease(cmpMain);
  v7 = &ProcessData[1];
  if (dds3ExistProcess(v7))
  {
    dds3KillProcess(v7, 0);
    v7 = 0;
    goto LABEL_13;
  }
  else
  {
LABEL_13:
    GuideObjClr();
    return;
  }
  GuideObjClr();
}

// 0x1f5c380
void cmpProcessStartEx(CMP_MODE a_runmode) {
  tagCMP_WORK *v3;
  Il2CppObject *Instance;
  dds3ProcessFunc_t v7;
  shutdownfuncDelegate v8;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *v12;
  s32 v14;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *menuPID;
  sprHandle_t *SpriteHnd;
  _BOOL8 v18;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *charPID;
  sprHandle_t *v21;
  dds3ProcessID_t *v23;
  dds3ProcessID_t *stockPID;
  sprHandle_t *v25;
  dds3ProcessID_t *v26;
  dds3ProcessID_t *p_listPID;
  s32 i;
  dds3ProcessID_t *v29;
  dds3ProcessID_t *v30;

  v3 = Allocate(tagCMP_WORK);
  _ctor(v3);
  *(u16 *)&subMenuActive = 0;
  Instance = _get_Instance();
  CallStart(Instance, 0, 1, 0);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_cmpMain_Process__, 0);
  v8 = Allocate(shutdownfuncDelegate);
  _ctor(v8, 0, Method_Project_cmpMain_Shutdown__, 0);
  started = dds3StartProcess("camp_main", 1007, 0, 0, v7, v8, v3);
  g_mainPID = started;
  v11 = Allocate(dds3ProcessFunc_t);
  _ctor(v11, 0, Method_Project_cmpMain_DrawProcess__, 0);
  v12 = dds3StartProcess("camp_draw", 11012, 0, 0, v11, 0, v3);
  v3->drawPID = v12;
  if ((u32)a_runmode >= 4)
    v14 = 0;
  else
    v14 = a_runmode;
  v3->runmode = v14;
  g_endmode = -1;
  datDlcNoneCheck();
  v15 = itfMenuProcessStart();
  v3->menuPID = v15;
  itfMenuSetOt(v3->menuPID, 108);
  menuPID = v3->menuPID;
  SpriteHnd = cmpGetSpriteHnd(0);
  v18 = itfMenuLinkSprite(menuPID, SpriteHnd);
  v19 = cmpPartyListProcessStart();
  v3->charPID = v19;
  itfMenuSetOt(v3->charPID, 108);
  charPID = v3->charPID;
  v21 = cmpGetSpriteHnd(0);
  itfMenuLinkSprite(charPID, v21);
  itfMenuSetMoveAppear(charPID, 3);
  itfMenuSetMoveDisappear(charPID, 3);
  v23 = cmpStockListProcessStart();
  v3->stockPID = v23;
  itfMenuSetOt(v3->stockPID, 108);
  stockPID = v3->stockPID;
  v25 = cmpGetSpriteHnd(0);
  itfMenuLinkSprite(stockPID, v25);
  itfMenuSetMoveAppear(stockPID, 3);
  itfMenuSetMoveDisappear(stockPID, 3);
  v26 = itfMenuProcessStart();
  v3->listPID = v26;
  p_listPID = &v3->listPID;
  itfMenuSetOt(v3->listPID, 108);
  for (i = 0; i != 64; ++i)
  {
    v29 = p_listPID;
    itfMenuSetRootMenu(v29, i, "", 0, "");
  }
  v30 = p_listPID;
  itfMenuSetFlag(v30, 2, 0);
  itfMenuSetFlag(p_listPID, 16, 0);
  itfMenuUpdateLink(p_listPID);
  Create(0);
  fclLinkData(sys);
  ProcessStart(0);
  cmpSetFlagCamp();
  cmpStart();
  Init();
  v3->tabNoDisp = 0;
}

// 0x1f5cc00
void cmpProcessStart(void) {
  cmpProcessStartEx(0);
}

// 0x1f5cc70
void cmpProcessEnd(void) {
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
    LODWORD(ProcessData[5].monitor) = 0;
    LODWORD(ProcessData[4].klass) = 15;
    HIDWORD(ProcessData[4].klass) = klass_high | 1;
  }
}

// 0x1f5ce20
bool cmpProcessCheck(void) {
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

// 0x1f5cf90
void cmpRestorBgm(s32 reqBgm) {
  s32 BgmId;

  if (reqBgm == -1)
  {
    if (CallCampFromLmap)
    {
      sndBgmPlay(10, 0);
      return;
    }
    if (jmsProcessCheck())
    {
      sndBgmPlay(16, 0);
    }
    else
    {
      mapSoundKankyoSeSet(fldGb->fieldID, fldGb->floorID, fldGb->cut_idx);
      BgmId = mapSoundGetBgmId(fldGb->fieldID, fldGb->floorID);
      sndBgmPlay(BgmId, 0);
    }
    return;
  }
  if (!reqBgm)
  {
    sndBgmLoadId_XF(0);
  }
  sndBgmPlay(reqBgm, 0);
  if (CallCampFromLmap)
    return;
  if (jmsProcessCheck())
    return;
  mapSoundKankyoSeSet(fldGb->fieldID, fldGb->floorID, fldGb->cut_idx);
}

// 0x1f56760
bool cmpUpdateSuspend(tagCMP_WORK *wk) {
  dds3ProcessFunc_t v7;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *v12;
  void *processfunc;
  dds3ProcessFunc_t v14;
  s32 v17;
  dds3ProcessID_t *v20;
  dds3ProcessFunc_t v23;
  dds3ProcessID_t *SuspendID_local;
  dds3ProcessFunc_t v30;
  dds3ProcessFunc_t v33;
  dds3ProcessID_t *v34;
  s32 v44;

  fclUpdateMessage();
  if (fclChkMessage())
    return 1;
  switch (SuspendProc)
  {
    case 0:
      if (evtBitCheck(10025))
        goto LABEL_31;
      tipsTIPSStart(41);
      v17 = 1;
      goto LABEL_122;
    case 1:
      if (tipsProcessCheck())
        return 1;
LABEL_31:
      v17 = 2;
      goto LABEL_122;
    case 2:
      Reset(0);
      slSetInfo(0);
      v20 = Allocate(dds3ProcessID_t);
      _ctor(v20, 0);
      SuspendID = v20;
      v17 = 4;
      goto LABEL_122;
    case 4:
      v23 = slSuspendProc();
      SuspendFunc = v23;
      if (SuspendFunc)
      {
        SuspendID_local = SuspendID;
        SuspendID_local->processfunc = SuspendFunc;
      }
      v17 = 5;
      goto LABEL_122;
    case 5:
      v30 = (SuspendID->processfunc->invoke_impl)(SuspendID->processfunc->method_code);
      SuspendFunc = v30;
      v33 = SuspendFunc;
      if (v33)
      {
        v33 = SuspendFunc;
        v34 = SuspendID;
        v34->processfunc = v33;
      }
      if (gslInfoCode == 4)
      {
        if (itfMesMngGetStat(gMsgID) != 768)
        {
          fclSetMessageInvalid(0);
          fclStartMessage(7);
          slSetKayWait();
          SuspendProc = 6;
        }
      }
      if (gslErrorKeyNoWait != 1)
      {
        if (gslInfoCode != 100)
          return 1;
      }
      v44 = gMsgID;
      if (itfMesMngGetStat(v44) == 768)
        return 1;
      if (gslErrorKeyNoWait)
      {
        gslErrorKeyNoWait = 0;
      }
      else
      {
        fclSetMessageInvalid(0);
        fclStartMessage(8);
      }
      slSetKayWait();
      v17 = 8;
LABEL_122:
      SuspendProc = v17;
      return 1;
    case 6:
    case 8:
      v7 = (SuspendID->processfunc->invoke_impl)(SuspendID->processfunc->method_code);
      SuspendFunc = v7;
      v11 = SuspendFunc;
      if (v11)
      {
        v11 = SuspendFunc;
        v12 = SuspendID;
        v12->processfunc = v11;
      }
      processfunc = SuspendID->processfunc;
      v14 = Allocate(dds3ProcessFunc_t);
      _ctor(v14, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      if (!op_Equality(processfunc, v14, 0))
        return 1;
      v17 = 7;
      goto LABEL_122;
    case 7:
      SelectYesSe = -1;
      fclEndMessage();
      wk->step = 2;
      cmpCmpGuideSet(0, 0, 90);
      itfMenuSetFlag(wk->menuPID, 8, 1);
      itfMenuSetFlagMenu(wk->menuPID, -1, 8, 0);
      return 1;
    default:
      return 1;
  }
}

// 0x1f5d2b0
void cmpSuspendEndProc(void) {
  fclEndMessage();
  p2sdSndStopAll();
  if (!!dds3SearchProcessName("fldProcSequence"))
    fldAllShutDown(1);
  dds3SearchProcessName("lmpMainProc");
}

// 0x1f56fc0
void cmpEndMesChk(tagCMP_WORK *wk) {
  s32 workStat;
  s32 endMesType;
  s32 v5;
  s32 v6;
  dds3ProcessID_t *menuPID;

  workStat = wk->workStat;
  endMesType = wk->endMesType;
  if (endMesType == 24)
    v5 = 2;
  else
    v5 = 3;
  if (workStat == 1)
  {
    v6 = Update();
    if (v6 == 1)
    {
      fclEndMessage();
      cmpChkEnableSelectMenu(wk);
      wk->workStat = 0;
      wk->count = 0;
      wk->step = 2;
      cmpCmpGuideSet(0, 0, 90);
      menuPID = wk->menuPID;
      itfMenuSetFlag(menuPID, 8, 1);
      itfMenuSetFlagMenu(wk->menuPID, -1, 8, 0);
    }
    else if (!v6)
    {
      fclEndMessage();
      wk->workStat = 0;
      g_endmode = v5;
      wk->step = 14;
    }
  }
  else if (!workStat)
  {
    Reset(0);
    fclStart2(endMesType, 0, 1);
    fclSetSelCancelPos(1);
    SetMessagePos(1u);
    ++wk->workStat;
  }
}
