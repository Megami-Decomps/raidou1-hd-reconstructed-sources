#include "types.h"
#include "book_cmdlist.h"
#include "book_cmdmenu.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpmain.h"
#include "cmpmap.h"
#include "cmpmodel.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fclmisc.h"
#include "fld.h"
#include "itf.h"
#include "jmsinit.h"
#include "kernel.h"
#include "lmap.h"
#include "localize.h"
#include "quest.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlitem.h"
#include "scr.h"
#include "sdat.h"
#include "sdfmem.h"
#include "tips.h"

#define PAGELENGTH 256
#define DbookDataDLCALLAssetKey "dlc_all_dbookdata"
#define DbookDataDLCDE1AssetKey "dlc_exp_dbookdata"
#define DbookDataDLCDE2AssetKey "dlc_money_dbookdata"
#define DbookDataDLCDE3AssetKey "dlc_incense_dbookdata"
#define DbookDataDLCDZ1AssetKey "dlc_oni1_dbookdata"
#define DbookDataDLCDZ2AssetKey "dlc_oni2_dbookdata"
#define DbookDataDLCDS1AssetKey "dlc_title_dbookdata"
#define DbookDataDLCDB1AssetKey "dlc_dbook_dbookdata"
#define DbookDataDLCDD1AssetKey "dlc_devil_dbookdata"
#define DbookDataDLCRM1AssetKey "dlc_glasses_dbookdata"
#define DbookDataDLCDI1AssetKey "dlc_skill_dbookdata"
#define DbookDataDLCDI2AssetKey "dlc_item_dbookdata"
#define DbookDataDLCDI3AssetKey "dlc_crm_dbookdata"
#define DbookTextDataDLCALLAssetKey "dlc_all_dbooktext."
#define DbookTextDataDLCDE1AssetKey "dlc_exp_dbooktext."
#define DbookTextDataDLCDE2AssetKey "dlc_money_dbooktext."
#define DbookTextDataDLCDE3AssetKey "dlc_incense_dbooktext."
#define DbookTextDataDLCDZ1AssetKey "dlc_oni1_dbooktext."
#define DbookTextDataDLCDZ2AssetKey "dlc_oni2_dbooktext."
#define DbookTextDataDLCDS1AssetKey "dlc_title_dbooktext."
#define DbookTextDataDLCDB1AssetKey "dlc_dbook_dbooktext."
#define DbookTextDataDLCDD1AssetKey "dlc_devil_dbooktext."
#define DbookTextDataDLCRM1AssetKey "dlc_glasses_dbooktext."
#define DbookTextDataDLCDI1AssetKey "dlc_skill_dbooktext."
#define DbookTextDataDLCDI2AssetKey "dlc_item_dbooktext."
#define DbookTextDataDLCDI3AssetKey "dlc_crm_dbooktext."
#define DbookTextTitleDataDLCALLAssetName "DBOOK_DLC_ALL_TITLE"
#define DbookTextTitleDataDLCDE1AssetName "DBOOK_DLC_DE1_TITLE"
#define DbookTextTitleDataDLCDZ1AssetName "DBOOK_DLC_DZ1_TITLE"
#define DbookTextTitleDataDLCDS1AssetName "DBOOK_DLC_DS1_TITLE"
#define DbookTextTitleDataDLCDB1AssetName "DBOOK_DLC_DB1_TITLE"
#define DbookTextTitleDataDLCDD1AssetName "DBOOK_DLC_DD1_TITLE"
#define DbookTextTitleDataDLCRM1AssetName "DBOOK_DLC_RM1_TITLE"
#define DbookTextTitleDataDLCDI1AssetName "DBOOK_DLC_DI1_TITLE"
#define DbookTextTitleDataDLCDI2AssetName "DBOOK_DLC_DI2_TITLE"
#define DbookTextTitleDataDLCDI3AssetName "DBOOK_DLC_DI3_TITLE"
#define DbookTextHekpTextDataDLCDB2AssetName "DBOOK_DLC_DB2_HELPTEXT"
#define DbookTitleDataDLCDE1AssetName "DBOOK_DLC_DE1_TEXT"
#define DbookTitleDataDLCDZ1AssetName "DBOOK_DLC_DZ1_TEXT"
#define DbookTitleDataDLCDS1AssetName "DBOOK_DLC_DS1_TEXT"
#define DbookTitleDataDLCDB1AssetName "DBOOK_DLC_DB1_TEXT"
#define DbookTitleDataDLCDD1AssetName "DBOOK_DLC_DD1_TEXT"
#define DbookTitleDataDLCRM1AssetName "DBOOK_DLC_RM1_TEXT"
#define DbookTitleDataDLCDI1AssetName "DBOOK_DLC_DI1_TEXT"
#define DbookTitleDataDLCDI2AssetName "DBOOK_DLC_DI2_TEXT"
#define DbookTitleDataDLCDI3AssetName "DBOOK_DLC_DI3_TEXT"
#define DbookDataDLCALLAssetName "DBookPanelDataTable_DLCALL"
#define DbookDataDLCDEAAssetName "DBookPanelDataTable_DLCDEA"
#define DbookDataDLCDE1AssetName "DBookPanelDataTable_DLCDE1"
#define DbookDataDLCDZAAssetName "DBookPanelDataTable_DLCDZA"
#define DbookDataDLCDZ1AssetName "DBookPanelDataTable_DLCDZ1"
#define DbookDataDLCDS1AssetName "DBookPanelDataTable_DLCDS1"
#define DbookDataDLCDB1AssetName "DBookPanelDataTable_DLCDB1"
#define DbookDataDLCDD1AssetName "DBookPanelDataTable_DLCDD1"
#define DbookDataDLCRM1AssetName "DBookPanelDataTable_DLCRM1"
#define DbookDataDLCDI1AssetName "DBookPanelDataTable_DLCDI1"
#define DbookDataDLCDI2AssetName "DBookPanelDataTable_DLCDI2"
#define DbookDataDLCDI3AssetName "DBookPanelDataTable_DLCDI3"
#define DbookDataDLCDB2AssetName "DBookPanelDataTable_DLCDB2"
#define QUESTLENGTH 128

typedef enum {
    DBOOKMESSAGESCROLL_DOWN = -1,
    DBOOKMESSAGESCROLL_ZERO = 0,
    DBOOKMESSAGESCROLL_UP = 1,
} DBOOKMESSAGESCROLL;

typedef enum {
    BOOK_MENU_STEP_MAIN = 0,
    BOOK_MENU_STEP_DRAW_OFF = 1,
    BOOK_MENU_STEP_RELEASE = 2,
    BOOK_MENU_STEP_END = 3,
} BOOK_MENU_STEP;

typedef enum {
    DitectiveBook_KEY_TYPE_NONE = -1,
    DitectiveBook_KEY_TYPE_UP = 0,
    DitectiveBook_KEY_TYPE_DOWN = 1,
    DitectiveBook_KEY_TYPE_RIGHT = 2,
    DitectiveBook_KEY_TYPE_LEFT = 3,
} DitectiveBook_KEY_TYPE;

typedef enum {
    RECEIPT_STAT_INIT = 0,
    RECEIPT_STAT_WAIT = 1,
    RECEIPT_STAT_CHECK = 2,
    RECEIPT_STAT_FADEIN = 3,
    RECEIPT_STAT_PLAY = 4,
    RECEIPT_STAT_ENDWAIT = 5,
    RECEIPT_STAT_FADEOUT = 6,
    RECEIPT_STAT_FASTMODE = 7,
    RECEIPT_STAT_LOADWAIT = 8,
    RECEIPT_STAT_END = 9,
} RECEIPT_STAT;

typedef enum {
    QUEST_MENU_ID_NONE = 0,
    QUEST_MENU_ID_BASIC_I = 1,
    QUEST_MENU_ID_BASIC_RO = 2,
    QUEST_MENU_ID_BASIC_HA = 3,
    QUEST_MENU_ID_THIRD_I = 4,
    QUEST_MENU_ID_THIRD_RO = 5,
    QUEST_MENU_ID_THIRD_HA = 6,
    QUEST_MENU_ID_SECOND_GRADE_I = 7,
    QUEST_MENU_ID_SECOND_GRADE_RO = 8,
    QUEST_MENU_ID_SECOND_GRADE_HA = 9,
    QUEST_MENU_ID_FIRST_GRADE_I = 10,
    QUEST_MENU_ID_FIRST_GRADE_RO = 11,
    QUEST_MENU_ID_FIRST_GRADE_HA = 12,
    QUEST_MENU_ID_EXPERT_I = 13,
    QUEST_MENU_ID_EXPERT_RO = 14,
    QUEST_MENU_ID_EXPERT_HA = 15,
} QUEST_MENU_ID;

typedef enum {
    REWARD_CHECK_MODE_INIT = 0,
    REWARD_CHECK_MODE_WAIT = 1,
    REWARD_CHECK_MODE_CHECK = 2,
    REWARD_CHECK_MODE_END = 3,
} REWARD_CHECK_MODE;

typedef enum {
    MAP_CHECK_MODE_INIT = 0,
    MAP_CHECK_MODE_WAIT = 1,
    MAP_CHECK_MODE_DRAW = 2,
    MAP_CHECK_MODE_END = 3,
} MAP_CHECK_MODE;

typedef struct DBOOK_READ_FLAG_CLASS DBOOK_READ_FLAG_CLASS;
typedef struct DITECTIVEBOOK_CLASS DITECTIVEBOOK_CLASS;
typedef struct QUEST_READ_FLAG_CLASS QUEST_READ_FLAG_CLASS;
typedef struct QUEST_TEXT_CLASS QUEST_TEXT_CLASS;
typedef struct bookCyousaRootTable_t bookCyousaRootTable_t;
typedef struct bookData_t bookData_t;
typedef struct bookSeqHandle_t bookSeqHandle_t;
typedef struct bookSeqUnit_t bookSeqUnit_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct receiptMainWork receiptMainWork;
typedef struct sprHandle_t sprHandle_t;

DITECTIVEBOOK_CLASS *BOOKPAGE[256];
bool DLCEXIST;
bool DLCDEEXIST;
bool DLCDZEXIST;
DBOOK_READ_FLAG_CLASS *DBOOK_READ_FLAG;
void *helpDic;
static void *bookSprTable01;
static void *bookSprTable02;
static void *bookSprTable03;
static void *bookSprTable04;
static void *bookSprTable05;
static void *bookSprTableRoot;
static dds3ProcessID_t *GlobalPID;
static char *s_szModelName;
static s32 gCallFromMenu;
bool DebugProcessFlag;
u8 moonSave;
void *DestNowList;
void *DestTextList;
void *DestListTbl;
void *DestTextIDList;
bool QuestFlag;
static bool DestDrawText;
static s32 SakuraCnt;
s32 CursorInitFlag;
static s32 CHAPTER3_STORNSTART_NO;
static s32 CHAPTER3_STORN_ONE_NO;
static s32 CHAPTER3_STORNFINISH_NO;
static s32 CHAPTER9_FIELD25_NO;
static s32 CHAPTER9_FIELD22_NO;
static s32 CHAPTER9_FIELD24_NO;
static s32 CHAPTER9_ALLGET_NO;
char *book_scene_name;
static char *jms_asset_name;
char *DbookDataAssetKey;
char *DbookImageDataAssetKey;
bool buttonUse;
static char *bookCyousaFileTitle;
static char *bookChosaFileMesssage;
char *dbookMenuHlepText;
static bookSeqUnit_t *bookSeqUnit;
static dds3ProcessID_t *g_mainPID;
s32 *bookCyousaTable;
u32 *bookCyousaTable1;
u32 *bookCyousaTable2;
u32 *bookCyousaTable3;
bookCyousaRootTable_t *bookCyousaRootTable;
static itfSprList_t *arrBookMenuPanel;
static itfSprList_t *arrBookMenuSelect;
static itfSprList_t *arrBookMenuBekkenFilePanel;
static itfSprList_t *arrBookMenuBekkenFileSelect;
static itfSprList_t *arrBookMenuBekkenPanel;
static itfSprList_t *arrBookMenuTitle;
static s32 *MenuParentID;
s32 *secondHi;
bool MenuActive;
static s32 MENU_DRAW_MAX;
static s32 MENU_PARENT_MAX;
dds3ProcessID_t *DBMPID;
char *szSeqNameNull;
receiptMainWork *wk;
void *paneldata;
s32 StartPosX;
s32 StartPosY;
char *dbookAssetKey;
char *dbookPanelDataTableName;
static void *rcptwk;
QUEST_TEXT_CLASS *QUESTPAGE;
QUEST_READ_FLAG_CLASS *QUEST_READ_FLAG;
char *QuestDataAssetKey;
static REWARD_CHECK_MODE RewardChackProc;
static MAP_CHECK_MODE MapChackProc;
static dds3ProcessFunc_t SuspendFunc;
static dds3ProcessID_t *SuspendID;
static bool RewardChack;
static s32 RewardMsgNum;
static s32 RewardMsgStep;
static s32 RewardItemNo;
bool QuestLoadMap;

static void *CmdListItemMoveNextEx(void *pCmdList, s32 Mode, s32 BlurMode);
static void *CmdListItemMovePrevEx(void *pCmdList, s32 Mode, s32 BlurMode);
static void DrawCursorCore(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 Mode, s32 OtNo);
static void UpdateCmdListStat(void *pCmdList);
static s32 ChkCmdListDrawTail(void *pCmdList);
static void *CmdListMoveUp(void *pCmdList);
static void *CmdListMoveDown(void *pCmdList);
static void UpdateCmdListTimer(void *pCmdList);
static void DrawCmdListIcon(s32 X, s32 Y, u32 Z, void *pCmdList, void *pItem, s32 OtNo);
static void DrawCmdListEx(s32 X, s32 Y, u32 Z, s32 StrOfsX, s32 StrOfsY, s32 AlphaRate, u32 Flag, void *pCmdList, s32 OtNo);
static void DrawCmdMenuScrollBar(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo);
static void DrawCmdMenuPanelTypeNormal(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 LineMax, u32 OtNo);
static void DrawCmdMenuPanel(s32 X, s32 Y, u32 Z, void *pCmdMenu, u32 OtNo);
static void DrawCmdMenuTitle(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo);
static void DrawCmdMenuCursor(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo);
static void DrawCursorNormal(s32 X, s32 Y, u32 Z, s32 *AlphaRate, void *pCursor, s32 Mode, s32 OtNo);
static void DrawCursorLR(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 OtNo);
static void DrawCursorTabLR(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 OtNo);
static void CmdListRecalcHead(void *pCmdList);
static void CmdListRecalcTail(void *pCmdList);
static void CmdListRecalcListTop(void *pCmdList, u32 Mode);
static void CmdListRecalcLinkList(void **pItemList, s32 Nums);
static s32 CmdListSortCallbackA(void *op1, void *op2);
static s32 CmdListSortCallbackA_R(void *op1, void *op2);
static s32 CmdListSortCallbackB(void *op1, void *op2);
static s32 CmdListSortCallbackB_R(void *op1, void *op2);
static s32 CmdListSortCallbackC(void *op1, void *op2);
static s32 CmdListSortCallbackC_R(void *op1, void *op2);
static void StartEtcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t Load2ndProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t Load0Process(dds3ProcessID_t *PID);
static dds3ProcessFunc_t Load1stProcess(dds3ProcessID_t *PID);
static bookData_t *Init(void);
static void Destroy(dds3ProcessID_t *PID);
static void DlcTextDestroy(char *DLCname, char *AssetNameText, char *AssetNameTitle);
static s32 RootInit(dds3ProcessID_t *PID);
static s32 RootDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootUpdateProcess(dds3ProcessID_t *PID);
static s32 TipsInit(dds3ProcessID_t *PID);
static s32 TipsDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TipsCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TipsDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TipsUpdateProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t PANELFILECalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t PANELFILEUpdateProcess(dds3ProcessID_t *PID);
static s32 CallFunc(void);
static void SetFlagMenu(dds3ProcessID_t *PID, s32 MenuID, u32 Flag, bool Bool);
static s32 CheckCyousaFlag(void);
static s32 CheckABADONcode(void);
static s32 CheckNextDest(void);
static s32 CheckChildID(s32 ID);
static void SetCommand_New(void *wk);
static void SetCommondParent(void *wk);
static void CallProcEnd(void *wk);
static u8 CheckProcEnd(void *wk);
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
static void Release(void *wk);
static void Shutdown(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
static void DrawPanelCtrl(void *wk);
static void SetMenu_New(void *wk, s32 MenuID, s32 ParentMenuID, char *pStr, s32 _type, s32 _subID);
static void SetRootMenu_New(void *wk, s32 MenuID, s32 ChildNum, char *pStr);
static void MenuMoveStartCtrl(void *wk);
static bool MenuMoveCalc(void *wk);
static void MenuCursorCtrlSub(void *wk);
static void CursorUp(void *wk);
static void CursorDown(void *wk);
static void CursorLeft(void *wk);
static void CursorRight(void *wk);
static void DrawMenuBeforeAfterSave(void *wk);
static void CalcSeqHandle(s32 Mode, bookSeqUnit_t *pSeqUnit, bookSeqHandle_t *pSeqHandle, dds3ProcessID_t *ID);
static void PanelTextCtrlSub(void *wk);
static s32 RightStickCtrl(void);
static bookData_t *QuestInit(void);
static dds3ProcessFunc_t QuestLoad0Process(dds3ProcessID_t *PID);
static dds3ProcessFunc_t QuestLoad1stProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t QuestLoad2ndProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t QuestDrawProcess(dds3ProcessID_t *PID);
static void SetCommand_Quest(void *wk);
static void SetRootMenu_Quest(void *wk, s32 MenuID, s32 ChildNum, char *pStr);
static s32 QuestCheckChildID(s32 ID);
static void SetCommondParentQuest(void *wk);
static void SetMenu_Quest(void *wk, s32 MenuID, s32 ParentMenuID, char *pStr, s32 _type, s32 _subID, s32 _questID);
static void QuestMenuMoveStartCtrl(void *wk);
static void CheckAllQuestParentReadFlag(void);
static void CheckAllQuestParentClearFlag(void);
static void CheckQuestTextUpdate(s32 ID, s32 parentID);
static void AccessQuestReadFlag(s32 accessID);
static void CheckQuestParentReadFlag(s32 ID);
static void CheckQuestClearUpdate(s32 ID, s32 parentID);
static char *IconConvert(s32 _itemID);
static bool RewardMoveCalc(void *wk);
static bool RewardMsgDraw(s32 _num, s32 _questID);
static bool MapMoveCalc(void *wk);
static s32 GetQuestMapNo(QUEST_TEXT_CLASS *_quest);
static s32 GetQuestFloorNo(QUEST_TEXT_CLASS *_quest);
static f32 GetQuestMap_X(QUEST_TEXT_CLASS *_quest);
static f32 GetQuestMap_Y(QUEST_TEXT_CLASS *_quest);

// macros
// 0x1bfba90: s32 DBOOK_RECEIPT(void)
#define DBOOK_RECEIPT() (1)

// 0x1bfbaa0: s32 DBOOK_RECEIPT_INIT(void)
static inline s32 DBOOK_RECEIPT_INIT(void) {
  s64 i;
  s32 *bit_Table;
  s64 v5;
  receiptMainWork *wk_local;
  s32 *ID_Table;
  char *v9;
  receiptMainWork *v11;

  ImageSetActive(rcptwk, 0, 0);
  for (i = 8; ; ++i)
  {
    wk_local = wk;
    ID_Table = wk_local->ID_Table;
    if (i - 8 >= SLODWORD(ID_Table->max_length))
      break;
    wk_local = wk;
    ID_Table = wk_local->ID_Table;
    bit_Table = wk_local->bit_Table;
    v5 = 4 * i;
    *(u32 *)((char *)&ID_Table->obj.klass + v5) = 0;
    *(u32 *)((char *)&bit_Table->obj.klass + v5) = 0;
  }
  wk_local = wk;
  v9 = "";
  wk_local->pageName01 = "";
  wk_local->num = 0;
  v11 = wk;
  *(u64 *)&v11->ObjAlpha = 0;
  v11->posY = 0.0;
  *(u64 *)&StartPosX = 0;
  v11->cnt = 0;
  v11->step = 1;
  ImageSetActive(rcptwk, 1, 0);
  return 1;
}

// 0x1bfbd40: s32 DBOOK_RECEIPT_SET(void)
static inline s32 DBOOK_RECEIPT_SET(void) {
  s32 IntPara;
  s64 v4;

  scrGetIntPara(0);
  IntPara = scrGetIntPara(1);
  if (!evtBitCheck(IntPara))
  {
    if (IntPara)
    {
      if ((u32)(IntPara - 2618) >= 0xFFFFFFC6)
        evtBitKityouItemAdd(IntPara);
      v4 = (s64)GBWK->EventBit + 4 * (IntPara / 32);
      *(u32 *)(v4 + 32) |= 1 << IntPara;
    }
    GetID(IntPara);
    wk->bit_Table[wk->num++] = IntPara;
  }
  return 1;
}

// 0x1bfc300: s32 DBOOK_RECEIPT_START(void)
static inline s32 DBOOK_RECEIPT_START(void) {
  u8 IntPara;
  receiptMainWork *v6;

  IntPara = scrGetIntPara(0);
  if (!wk->num)
    return 1;
  wk->SKIPFLAG = scrIsEventSkip(0);
  v6 = wk;
  v6->mode = IntPara;
  v6->step = 2;
  return 1;
}

// 0x1be4a50
static void *CmdListItemMoveNextEx(void *pCmdList, s32 Mode, s32 BlurMode) {
  void *pCurrent;
  void *p_pCurrent;
  s32 ItemCnt;
  s32 Flag;
  void *pNext;
  s32 ItemOfs;
  s32 v15;
  void *pHead;
  void *v18;
  void *pListTop;
  u32 v20;
  s32 DrawItemMax;
  s32 v22;
  void *pTail;
  void *v24;
  u32 v25;
  s32 v26;
  void *pCmdLista;

  pCmdLista = pCmdList;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  ItemCnt = pCmdList->ItemCnt;
  Flag = pCmdList->Flag;
  if (ItemCnt > 1)
  {
    if ((Flag & 2) == 0)
      goto LABEL_4;
LABEL_9:
    pCmdList->Flag = Flag & 0xFFFFFFFE;
    return 0;
  }
  Flag |= 2u;
  pCmdList->Flag = Flag;
  if ((Flag & 2) != 0)
    goto LABEL_9;
LABEL_4:
  if (ItemCnt == 1)
    return pCurrent;
  if (pCurrent == pCmdList->pTail)
  {
    if (pCmdList->ItemCnt < 1)
    {
LABEL_24:
      pListTop = pCmdList->pListTop;
      if (pListTop)
      {
        v20 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
        DrawItemMax = pCmdList->DrawItemMax;
        if (DrawItemMax < 1)
        {
LABEL_28:
          v22 = v20 | 2;
        }
        else
        {
          while (1)
          {
            pListTop = pListTop->pNext;
            if (!pListTop)
              break;
            if (!--DrawItemMax)
              goto LABEL_28;
          }
          v22 = v20 & 0xFFFFFFFD;
        }
        pNext = p_pCurrent;
        goto LABEL_54;
      }
      pNext = p_pCurrent;
LABEL_52:
      pCmdList->Stat = 0;
      return pNext;
    }
    pHead = pCmdList->pHead;
    pCmdList->pListTop = pHead;
    v18 = pCmdList->pHead;
    pCmdList->pCurrent = v18;
    pCmdList->ItemOfs = 0;
    goto LABEL_24;
  }
  if (!pCurrent)
    return 0;
  pNext = pCurrent->pNext;
  if (!pNext)
    return pNext;
  if (!BlurMode)
    pCurrent->Timer = 256;
  pCmdList->pCurrent = pNext;
  ItemOfs = pCmdList->ItemOfs;
  v15 = pCmdList->DrawItemMax - 1;
  pCmdList->ItemOfs = ItemOfs + 1;
  if (ItemOfs + 1 >= v15)
  {
    if (Mode)
    {
      if (pNext != pCmdList->pTail)
      {
        pNext = pNext->pPrev;
        pCmdList->ItemOfs = ItemOfs;
        pCmdList->pCurrent = pNext;
      }
    }
    else
    {
      pNext = CmdListMoveUp(pCmdLista);
    }
  }
  pTail = pCmdList->pTail;
  if (pNext == pTail)
    pCmdList->Flag |= 3u;
  if (pNext->pNext == pTail && (pTail->Flag & 2) != 0)
    pCmdList->Flag |= 3u;
  v24 = pCmdList->pListTop;
  if (!v24)
    goto LABEL_52;
  v25 = pCmdList->Stat & 0xFFFFFFFE | (v24->pPrev != 0);
  v26 = pCmdList->DrawItemMax;
  if (v26 < 1)
  {
LABEL_51:
    v22 = v25 | 2;
  }
  else
  {
    while (1)
    {
      v24 = v24->pNext;
      if (!v24)
        break;
      if (!--v26)
        goto LABEL_51;
    }
    v22 = v25 & 0xFFFFFFFD;
  }
LABEL_54:
  pCmdList->Stat = v22;
  return pNext;
}

// 0x1be4f20
static void *CmdListItemMovePrevEx(void *pCmdList, s32 Mode, s32 BlurMode) {
  void *pCurrent;
  void *p_pCurrent;
  s32 ItemCnt;
  s32 Flag;
  void *pPrev;
  s32 ItemOfs;
  void *pHead;
  void *pNext;
  u32 v17;
  s32 v18;
  s32 v19;
  s32 v21;
  void *pListTop;
  u32 v23;
  s32 DrawItemMax;
  void *pCmdLista;

  pCmdLista = pCmdList;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  ItemCnt = pCmdList->ItemCnt;
  Flag = pCmdList->Flag;
  if (ItemCnt > 1)
  {
    if ((Flag & 2) == 0)
      goto LABEL_4;
LABEL_9:
    pCmdList->Flag = Flag & 0xFFFFFFFE;
    return 0;
  }
  Flag |= 2u;
  pCmdList->Flag = Flag;
  if ((Flag & 2) != 0)
    goto LABEL_9;
LABEL_4:
  if (ItemCnt == 1)
    return pCurrent;
  if (pCurrent == pCmdList->pHead)
  {
    v21 = pCmdList->ItemCnt;
    CmdListItemMoveIndex(v21 - 1, pCmdLista);
    pListTop = pCmdList->pListTop;
    if (pListTop)
    {
      v23 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
      DrawItemMax = pCmdList->DrawItemMax;
      if (DrawItemMax < 1)
      {
LABEL_35:
        v19 = v23 | 2;
      }
      else
      {
        while (1)
        {
          pListTop = pListTop->pNext;
          if (!pListTop)
            break;
          if (!--DrawItemMax)
            goto LABEL_35;
        }
        v19 = v23 & 0xFFFFFFFD;
      }
      pPrev = p_pCurrent;
      goto LABEL_47;
    }
    pPrev = p_pCurrent;
LABEL_41:
    pCmdList->Stat = 0;
    return pPrev;
  }
  if (!pCurrent)
    return 0;
  pPrev = pCurrent->pPrev;
  if (!pPrev)
    return pPrev;
  if (!BlurMode)
    pCurrent->Timer = 256;
  pCmdList->pCurrent = pPrev;
  ItemOfs = pCmdList->ItemOfs;
  pCmdList->ItemOfs = ItemOfs - 1;
  if (ItemOfs - 1 <= 0)
  {
    if (Mode)
    {
      if (pPrev != pCmdList->pHead)
      {
        pPrev = pPrev->pNext;
        pCmdList->ItemOfs = ItemOfs;
        pCmdList->pCurrent = pPrev;
      }
    }
    else
    {
      pPrev = CmdListMoveDown(pCmdLista);
    }
  }
  pHead = pCmdList->pHead;
  if (pPrev == pHead)
    pCmdList->Flag |= 3u;
  if (pPrev->pPrev == pHead && (pHead->Flag & 2) != 0)
    pCmdList->Flag |= 3u;
  pNext = pCmdList->pListTop;
  if (!pNext)
    goto LABEL_41;
  v17 = pCmdList->Stat & 0xFFFFFFFE | (pNext->pPrev != 0);
  v18 = pCmdList->DrawItemMax;
  if (v18 < 1)
  {
LABEL_27:
    v19 = v17 | 2;
  }
  else
  {
    while (1)
    {
      pNext = pNext->pNext;
      if (!pNext)
        break;
      if (!--v18)
        goto LABEL_27;
    }
    v19 = v17 & 0xFFFFFFFD;
  }
LABEL_47:
  pCmdList->Stat = v19;
  return pPrev;
}

// 0x1be5370
static void DrawCursorCore(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 Mode, s32 OtNo) {
  u32 Type;
  sdfIVector2_t *v12;
  sdfIVector2_t v13;
  sdfIVector2_t v14;
  sdfIVector2_t *v15;
  s32 SprMax;
  s64 v17;
  sdfIVector2_t v18;
  s32 AlphaRatea;

  Type = pCursor->Type;
  if (Type >= 4)
  {
    if (Type == 4)
    {
      v15 = NewSpecific(sdfIVector2_t, 0);
      SprMax = pCursor->SprMax;
      if (SprMax >= 1)
      {
        v17 = 0;
        v18 = (sdfIVector2_t)((s64)&v15[0]);
        do
        {
          if ((u32)v17 != 3 && (u32)v17 != 5)
          {
            get_Item(v18, 0, 0);
            get_Item(v18, 1, 0);
            SprMax = pCursor->SprMax;
          }
          ++v17;
          *(u64 *)&v18 += 8;
        }
        while (v17 < SprMax);
      }
    }
    else if (Type == 5)
    {
      v12 = NewSpecific(sdfIVector2_t, 0);
      v13 = (sdfIVector2_t)((s64)&v12[0]);
      v14 = (sdfIVector2_t)v12;
      get_Item((sdfIVector2_t)((s64)&v12[0]), 0, 0);
      get_Item(v13, 1, 0);
      *(u64 *)&v14 += 40;
      get_Item(v14, 0, 0);
      get_Item(v14, 1, 0);
    }
  }
  else
  {
    DrawCursorNormal((s32)DitectiveBook, Y, Z, &AlphaRatea, pCursor, Mode, OtNo);
  }
}

// 0x1be5820
void *CreateCmdList(u32 Type, s32 DrawItemMax, s32 StepY) {
  void *v6;

  v6 = (void *)Allocate(bookCmdList_s);
  _ctor(v6, 0);
  v6->Type = Type;
  v6->DrawItemMax = DrawItemMax;
  v6->pCurrent = 0;
  v6->pListTop = 0;
  v6->pHead = 0;
  v6->ItemOfs = 0;
  v6->AlphaRate = 256;
  return v6;
}

// 0x1be58d0
s32 DestroyCmdList(void *pCmdList) {
  do
  {
  }
  while (DelCmdListItem(pCmdList));
  return 1;
}

// 0x1be4e60
static void UpdateCmdListStat(void *pCmdList) {
  void *v2;
  void *pListTop;
  u32 v4;
  s32 DrawItemMax;

  v2 = pCmdList;
  pListTop = pCmdList->pListTop;
  if (pListTop)
  {
    v4 = v2->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
    DrawItemMax = v2->DrawItemMax;
    if (DrawItemMax < 1)
    {
LABEL_5:
      v2->Stat = v4 | 2;
    }
    else
    {
      while (1)
      {
        pListTop = pListTop->pNext;
        if (!pListTop)
          break;
        if (!--DrawItemMax)
          goto LABEL_5;
      }
      v2->Stat = v4 & 0xFFFFFFFD;
    }
  }
  else
  {
    v2->Stat = 0;
  }
}

// 0x1be5bf0
void *AddCmdListItem(void *pCmdList, s8 pItemName) {
  void *v5;
  void *pTail;
  void *v7;
  void *pPrev;
  s32 ItemCnt;
  void *pListTop;
  u32 v12;
  s32 DrawItemMax;
  s32 v14;
  s32 v15;
  s32 v17;

  v5 = (void *)Allocate(bookCmdListItem_s);
  _ctor(v5, 0);
  if (!pCmdList->ItemCnt)
  {
    pCmdList->pListTop = v5;
    pCmdList->pCurrent = v5;
    pCmdList->pHead = v5;
  }
  v5->pItemName = pItemName;
  pTail = pCmdList->pTail;
  v5->pPrev = pTail;
  v5->pNext = 0;
  v7 = pCmdList->pTail;
  v5->pPrev = v7;
  pPrev = v5->pPrev;
  if (pPrev)
  {
    pPrev->pNext = v5;
  }
  pCmdList->pTail = v5;
  ItemCnt = pCmdList->ItemCnt;
  v5->Index = ItemCnt;
  pCmdList->ItemCnt = ItemCnt + 1;
  pListTop = pCmdList->pListTop;
  if (pListTop)
  {
    v12 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
    DrawItemMax = pCmdList->DrawItemMax;
    if (DrawItemMax < 1)
    {
LABEL_13:
      v15 = v12 | 2;
    }
    else
    {
      v14 = pCmdList->DrawItemMax;
      while (1)
      {
        pListTop = pListTop->pNext;
        if (!pListTop)
          break;
        if (!--v14)
          goto LABEL_13;
      }
      v15 = v12 & 0xFFFFFFFD;
    }
    pCmdList->Stat = v15;
    if (DrawItemMax > 2)
      return v5;
    goto LABEL_19;
  }
  DrawItemMax = pCmdList->DrawItemMax;
  pCmdList->Stat = 0;
  if (DrawItemMax > 2)
    return v5;
LABEL_19:
  v17 = pCmdList->ItemCnt;
  if (DrawItemMax >= v17)
    return v5;
  pCmdList->DrawItemMax = v17;
  return v5;
}

// 0x1be5dd0
static s32 ChkCmdListDrawTail(void *pCmdList) {
  void *pListTop;
  s32 v3;

  pListTop = pCmdList->pListTop;
  if (pListTop)
  {
    v3 = (pCmdList->DrawItemMax & ~(pCmdList->DrawItemMax >> 31)) + 1;
    do
    {
      if (!--v3)
        break;
      if (pListTop == pCmdList->pTail)
        return 1;
      pListTop = pListTop->pNext;
    }
    while (pListTop);
  }
  return 0;
}

// 0x1be5e10
void *InsertCmdListItem(void *pCmdList, void *pItem, s8 pItemName, s32 DelItemIndex, u32 Mode) {
  char v6;
  void *v11;
  void *v12;
  void *pPrev;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *p_pListTop;
  void *pNext;
  void *v21;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  s32 Index;
  void *v28;
  s32 v29;
  void *p_pCurrent;
  void *v31;
  void *pHead;
  void *pListTop;
  void *v35;
  s32 v36;
  void *v37;
  void *v38;
  void *v39;
  s32 DrawItemMax;
  s32 v41;
  s32 ItemCnt;
  void *v43;
  u32 v44;
  s32 v45;
  s32 v46;

  v6 = Mode;
  if (!pCmdList->ItemCnt || !pItem || pItem == pCmdList->pTail)
  {
    v11 = AddCmdListItem(pCmdList, pItemName);
    if (pCmdList->ItemOfs < pCmdList->DrawItemMax - 1 || pCmdList->pCurrent == pCmdList->pTail)
    {
      if (DelItemIndex == -2)
      {
        CmdListItemMoveNextEx(pCmdList, 0, 1);
      }
    }
    else
    {
      pNext = pCmdList->pListTop->pNext;
      pCmdList->pListTop = pNext;
      v21 = pCmdList->pCurrent->pNext;
      pCmdList->pCurrent = v21;
      if (DelItemIndex == -1)
      {
        CmdListItemMovePrevEx(pCmdList, 0, 1);
      }
    }
    return v11;
  }
  v11 = (void *)Allocate(bookCmdListItem_s);
  _ctor(v11, 0);
  v12 = pItem;
  v11->pItemName = pItemName;
  if ((v6 & 2) != 0)
  {
    v11->pPrev = v12;
    v23 = pItem->pNext;
    v11->pNext = v23;
    v24 = pItem;
    v11->Index = pItem->Index;
    v25 = v24->pNext;
    if (v25)
    {
      v25->pPrev = v11;
      v24 = pItem;
    }
    v24->pNext = v11;
    v26 = v11;
    do
    {
      ++v26->Index;
      v26 = v26->pNext;
    }
    while (v26);
  }
  else
  {
    pPrev = v12->pPrev;
    v11->pPrev = pPrev;
    v14 = pItem;
    v11->pNext = pItem;
    v15 = pItem;
    v11->Index = pItem->Index;
    v16 = v15->pPrev;
    if (v16)
    {
      v16->pNext = v11;
      v15 = pItem;
    }
    v15->pPrev = v11;
    v17 = pItem;
    if (pItem == pCmdList->pHead)
    {
      pCmdList->pHead = v11;
      p_pListTop = &pCmdList->pListTop;
      if (pCmdList->pCurrent == pCmdList->pListTop || pCmdList->ItemCnt < pCmdList->DrawItemMax)
      {
        p_pListTop = v11;
      }
      v17 = pItem;
    }
    for (; v17; v17 = v17->pNext)
      ++v17->Index;
  }
  Index = v11->Index;
  v28 = &pCmdList->pListTop;
  v29 = pCmdList->pListTop->Index;
  ++pCmdList->ItemCnt;
  if (Index < v29 || Index >= ITEMIDX(pCmdList))
    goto LABEL_61;
  p_pCurrent = &pCmdList->pCurrent;
  v31 = pCmdList->pCurrent->pPrev;
  pCmdList->pCurrent = v31;
  pHead = pCmdList->pHead;
  pListTop = pCmdList->pListTop;
  if (pHead == pListTop)
  {
    DrawItemMax = pCmdList->DrawItemMax;
    v41 = DrawItemMax + 1;
    ItemCnt = pCmdList->ItemCnt;
    if ((DelItemIndex & 0x80000000) == 0 || DelItemIndex == -2)
    {
      if (ItemCnt < v41 || p_pCurrent->Index - pHead->Index != DrawItemMax - 1)
      {
        if (DelItemIndex != -2)
          goto LABEL_61;
        goto LABEL_58;
      }
    }
    else if (ItemCnt < v41 || p_pCurrent->Index - pHead->Index != DrawItemMax - 1)
    {
LABEL_58:
      CmdListItemMoveNextEx(pCmdList, 0, 1);
      goto LABEL_61;
    }
    v37 = pHead->pNext;
LABEL_47:
    v28 = v37;
    v38 = &pCmdList->pCurrent;
    v39 = p_pCurrent->pNext;
    p_pCurrent = v39;
LABEL_48:
    goto LABEL_61;
  }
  pListTop = v28;
  if (pListTop)
  {
    v35 = pListTop;
    v36 = (pCmdList->DrawItemMax & ~(pCmdList->DrawItemMax >> 31)) + 1;
    do
    {
      if (!--v36)
        break;
      if (v35 == pCmdList->pTail)
      {
        if (DelItemIndex < 0 && DelItemIndex != -2)
        {
          v39 = pListTop->pNext;
          v38 = &pCmdList->pListTop;
          v28 = v39;
          goto LABEL_48;
        }
        goto LABEL_61;
      }
      v35 = v35->pNext;
    }
    while (v35);
  }
  if (DelItemIndex < 0 && DelItemIndex != -2 || DelItemIndex == -2)
  {
    v37 = pListTop->pNext;
    goto LABEL_47;
  }
LABEL_61:
  v43 = v28;
  if (!v28)
  {
    pCmdList->Stat = 0;
    return v11;
  }
  v44 = pCmdList->Stat & 0xFFFFFFFE | (v43->pPrev != 0);
  v45 = pCmdList->DrawItemMax;
  if (v45 < 1)
  {
LABEL_66:
    v46 = v44 | 2;
  }
  else
  {
    while (1)
    {
      v43 = v43->pNext;
      if (!v43)
        break;
      if (!--v45)
        goto LABEL_66;
    }
    v46 = v44 & 0xFFFFFFFD;
  }
  pCmdList->Stat = v46;
  return v11;
}

// 0x1be5940
void *DelCmdListItem(void *pCmdList) {
  void *pCurrent;
  void *p_pCurrent;
  void *pNext;
  s32 Index;
  bool v7;
  s32 v8;
  void *pPrev;
  void *v11;
  void *pListTop;
  void *p_pListTop;
  void *v14;
  void *v15;
  void *v16;
  void *v18;
  u32 v19;
  s32 DrawItemMax;
  s32 v21;
  void *v22;
  void *v23;

  if (!pCmdList->ItemCnt)
    return 0;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  if (!pCurrent)
    return 0;
  pNext = pCmdList->pCurrent;
  do
  {
    Index = pNext->Index;
    v7 = __OFSUB__(Index, 1);
    v8 = Index - 1;
    if (v8 < 0 == v7)
      pNext->Index = v8;
    pNext = pNext->pNext;
  }
  while (pNext);
  v11 = pCurrent->pNext;
  pPrev = pCurrent->pPrev;
  p_pListTop = &pCmdList->pListTop;
  pListTop = pCmdList->pListTop;
  if (pCmdList->pTail->Index - pListTop->Index + 1 > pCmdList->DrawItemMax)
  {
    if (!v11)
      goto LABEL_16;
    goto LABEL_12;
  }
  if (pListTop != pCmdList->pHead)
  {
    v16 = pListTop->pPrev;
    p_pListTop = v16;
    p_pCurrent = pPrev;
    v14 = &pCmdList->pCurrent;
    v15 = pPrev;
    goto LABEL_15;
  }
  if (pCurrent == pListTop)
  {
    if (!v11)
    {
      v23 = pCurrent->pPrev;
      pCmdList->pListTop = pPrev;
      goto LABEL_43;
    }
    v22 = pCurrent->pNext;
    p_pListTop = v11;
LABEL_12:
    v14 = &pCmdList->pCurrent;
    v15 = v11;
    p_pCurrent = v11;
LABEL_15:
LABEL_16:
    if (p_pCurrent)
      goto LABEL_18;
    goto LABEL_17;
  }
  if (v11)
    goto LABEL_12;
LABEL_43:
  pCmdList->pCurrent = pPrev;
  --pCmdList->ItemOfs;
  if (!p_pCurrent)
  {
LABEL_17:
    pCmdList->pListTop = 0;
    pCmdList->pHead = 0;
    pCmdList->pTail = 0;
    pCmdList->ItemOfs = 0;
  }
LABEL_18:
  if (pPrev)
  {
    pPrev->pNext = v11;
  }
  if (v11)
  {
    v11->pPrev = pPrev;
  }
  if (pPrev)
  {
    if (v11)
      goto LABEL_24;
  }
  else
  {
    pCmdList->pListTop = v11;
    pCmdList->pHead = v11;
    if (v11)
      goto LABEL_24;
  }
  pCmdList->pTail = pPrev;
LABEL_24:
  --pCmdList->ItemCnt;
  v18 = p_pListTop;
  if (p_pListTop)
  {
    v19 = pCmdList->Stat & 0xFFFFFFFE | (v18->pPrev != 0);
    DrawItemMax = pCmdList->DrawItemMax;
    if (DrawItemMax < 1)
    {
LABEL_29:
      v21 = v19 | 2;
    }
    else
    {
      while (1)
      {
        v18 = v18->pNext;
        if (!v18)
          break;
        if (!--DrawItemMax)
          goto LABEL_29;
      }
      v21 = v19 & 0xFFFFFFFD;
    }
    pCmdList->Stat = v21;
    return *p_pCurrent;
  }
  pCmdList->Stat = 0;
  return *p_pCurrent;
}

// 0x1be62d0
void *CmdListGetTargetItem(s32 Index, void *pCmdList) {
  void *result;
  bool v5;
  s32 v6;
  bool v7;

  result = pCmdList->pHead;
  if (result)
    v5 = Index == 0;
  else
    v5 = 1;
  if (!v5)
  {
    v6 = Index - 1;
    do
    {
      result = result->pNext;
      if (result)
        v7 = v6 == 0;
      else
        v7 = 1;
      --v6;
    }
    while (!v7);
  }
  return result;
}

// 0x1be6310
s32 CmdListItemMoveIndex(s32 Index, void *pCmdList) {
  void *v4;
  void *pHead;
  void *v7;
  void *v8;
  void *pNext;
  void *p_pListTop;
  void *p_pCurrent;
  void *v12;
  void *v13;
  void *pListTop;
  void *v15;
  void *pCurrent;
  void *v17;

  v4 = pCmdList;
  if (pCmdList->ItemCnt <= Index)
    return 0;
  pHead = v4->pHead;
  v4->pListTop = pHead;
  v7 = pCmdList;
  v8 = pCmdList->pHead;
  v7->pCurrent = v8;
  pCmdList->ItemOfs = 0;
  if (Index >= 1)
  {
    do
    {
      while (1)
      {
        v13 = pCmdList;
        pListTop = pCmdList->pListTop;
        if (pCmdList->ItemCnt - pListTop->Index <= pCmdList->DrawItemMax)
          break;
        pNext = pListTop->pNext;
        p_pListTop = &pCmdList->pListTop;
        p_pListTop = pNext;
        p_pCurrent = &pCmdList->pCurrent;
        v12 = p_pCurrent->pNext;
        p_pCurrent = v12;
        if (!--Index)
          return 1;
      }
      ++v13->ItemOfs;
      pCurrent = v13->pCurrent;
      v15 = &v13->pCurrent;
      v17 = pCurrent->pNext;
      v15 = v17;
      --Index;
    }
    while (Index);
  }
  return 1;
}

// 0x1be4db0
void CmdListItemMoveHead(void *pCmdList) {
  void *v4;
  void *pHead;
  void *v6;
  void *v7;

  v4 = pCmdList;
  if (pCmdList->ItemCnt < 1)
    return;
  pHead = v4->pHead;
  v4->pListTop = pHead;
  v6 = pCmdList;
  v7 = pCmdList->pHead;
  v6->pCurrent = v7;
  pCmdList->ItemOfs = 0;
}

// 0x1be5250
void CmdListItemMoveTail(void *pCmdList) {
  s32 ItemCnt;
  s32 v6;
  void *v7;

  ItemCnt = pCmdList->ItemCnt;
  v6 = ItemCnt - 1;
  v7 = pCmdList;
  CmdListItemMoveIndex(v6, v7);
}

// 0x1be4ec0
static void *CmdListMoveUp(void *pCmdList) {
  void *v2;
  void *result;
  void *p_pListTop;
  void *pListTop;
  void *pNext;

  v2 = pCmdList;
  result = pCmdList->pCurrent;
  if (result != v2->pTail)
  {
    pListTop = v2->pListTop;
    p_pListTop = &v2->pListTop;
    pNext = pListTop->pNext;
    if (pNext)
    {
      p_pListTop = pNext;
      result = pCmdList->pCurrent;
      --pCmdList->ItemOfs;
    }
  }
  return result;
}

// 0x1be52f0
static void *CmdListMoveDown(void *pCmdList) {
  void *v2;
  void *result;
  void *v5;
  void *p_pListTop;
  void *v7;
  void *pListTop;
  s32 DrawItemMax;
  void *pNext;
  void *pPrev;

  v2 = pCmdList;
  result = pCmdList->pCurrent;
  if (result != v2->pHead)
  {
    v5 = v2;
    pListTop = v2->pListTop;
    p_pListTop = &v2->pListTop;
    v7 = pListTop;
    DrawItemMax = v5->DrawItemMax;
    if (DrawItemMax < 1)
    {
LABEL_6:
      pPrev = v7->pPrev;
      p_pListTop = pPrev;
      result = pCmdList->pCurrent;
      ++pCmdList->ItemOfs;
    }
    else
    {
      pNext = v7;
      while (pNext)
      {
        pNext = pNext->pNext;
        if (!--DrawItemMax)
          goto LABEL_6;
      }
    }
  }
  return result;
}

// 0x1be6400
void *CmdListItemMoveNext(void *pCmdList) {
  void *v4;

  v4 = pCmdList;
  return CmdListItemMoveNextEx(v4, 0, 0);
}

// 0x1be6470
void *CmdListItemMovePrev(void *pCmdList) {
  void *v4;

  v4 = pCmdList;
  return CmdListItemMovePrevEx(v4, 0, 0);
}

// 0x1be64e0
void *CmdListItemMoveNextPage(void *pCmdList) {
  void *p_pCurrent;
  s32 v4;
  void *p_pListTop;
  void *v6;
  void *pNext;
  s32 DrawItemMax;
  s32 v9;
  void *pCurrent;
  void *v11;
  void *pListTop;
  s32 v13;
  s32 v14;
  void *v16;
  u32 v17;
  s32 v18;
  s32 v19;
  void *v20;
  s32 v22;

  p_pCurrent = &pCmdList->pCurrent;
  if (!pCmdList->pCurrent)
    return 0;
  if (pCmdList->DrawItemMax >= 1)
  {
    v4 = 0;
    p_pListTop = &pCmdList->pListTop;
    do
    {
      pNext = p_pListTop;
      if (!p_pListTop)
        goto LABEL_15;
      DrawItemMax = pCmdList->DrawItemMax;
      v9 = (DrawItemMax & ~(DrawItemMax >> 31)) + 1;
      do
      {
        if (!--v9)
          break;
        if (pNext == pCmdList->pTail)
        {
          if (v4)
            goto LABEL_22;
          if (p_pCurrent != pNext)
          {
            v22 = DrawItemMax - 1;
LABEL_44:
            pCmdList->ItemOfs = v22;
            pCmdList->pCurrent = pNext;
            return *p_pCurrent;
          }
          return 0;
        }
        pNext = pNext->pNext;
      }
      while (pNext);
LABEL_15:
      pCurrent = pCmdList->pCurrent;
      if (pCurrent != pCmdList->pTail)
      {
        v11 = p_pListTop->pNext;
        if (v11)
        {
          pCmdList->pListTop = v11;
          --pCmdList->ItemOfs;
          pCurrent = pCmdList->pCurrent;
        }
      }
      v6 = pCurrent->pNext;
      pCmdList->pCurrent = v6;
      ++v4;
      ++pCmdList->ItemOfs;
    }
    while (v4 < pCmdList->DrawItemMax);
  }
LABEL_22:
  pListTop = pCmdList->pListTop;
  if (!pListTop)
    goto LABEL_30;
  v13 = pCmdList->DrawItemMax;
  pNext = pListTop;
  v14 = (v13 & ~(v13 >> 31)) + 1;
  do
  {
    if (!--v14)
      break;
    if (pNext == pCmdList->pTail)
    {
      v22 = v13 - 1;
      goto LABEL_44;
    }
    pNext = pNext->pNext;
  }
  while (pNext);
LABEL_30:
  if (p_pCurrent != pListTop)
  {
    goto LABEL_32;
LABEL_39:
    pCmdList->Stat = 0;
    return *p_pCurrent;
  }
  v20 = pListTop->pNext;
  pCmdList->ItemOfs = 1;
  pCmdList->pCurrent = v20;
LABEL_32:
  v16 = pCmdList->pListTop;
  if (!v16)
    goto LABEL_39;
  v17 = pCmdList->Stat & 0xFFFFFFFE | (v16->pPrev != 0);
  v18 = pCmdList->DrawItemMax;
  if (v18 < 1)
  {
LABEL_36:
    v19 = v17 | 2;
  }
  else
  {
    while (1)
    {
      v16 = v16->pNext;
      if (!v16)
        break;
      if (!--v18)
        goto LABEL_36;
    }
    v19 = v17 & 0xFFFFFFFD;
  }
  pCmdList->Stat = v19;
  return *p_pCurrent;
}

// 0x1be67b0
void *CmdListItemMovePrevPage(void *pCmdList) {
  void *p_pCurrent;
  s32 DrawItemMax;
  void *pListTop;
  void *pHead;
  s32 v7;
  void *pCurrent;
  void *v9;
  void *v10;
  s32 v11;
  void *pNext;
  void *pPrev;
  void *v14;
  s32 v15;
  void *v16;
  s32 v17;
  void *v18;
  void *v19;
  u32 v20;
  s32 v21;
  s32 v22;

  p_pCurrent = &pCmdList->pCurrent;
  if (!pCmdList->pCurrent)
    return 0;
  DrawItemMax = pCmdList->DrawItemMax;
  if (DrawItemMax < 1)
    goto LABEL_20;
  pListTop = pCmdList->pListTop;
  pHead = pCmdList->pHead;
  if (pListTop == pHead)
  {
    v9 = pCmdList->pListTop;
LABEL_36:
    if (p_pCurrent != v9)
      goto LABEL_37;
    return 0;
  }
  v7 = 0;
  pCurrent = pCmdList->pHead;
  v9 = pCmdList->pListTop;
  do
  {
    v10 = p_pCurrent;
    if (p_pCurrent == pCurrent)
      goto LABEL_17;
    v11 = pCmdList->DrawItemMax;
    if (v11 < 1)
    {
LABEL_15:
      pPrev = v9->pPrev;
      pCmdList->pListTop = pPrev;
      pCurrent = pCmdList->pCurrent;
      ++pCmdList->ItemOfs;
    }
    else
    {
      pNext = v9;
      while (pNext)
      {
        pNext = pNext->pNext;
        if (!--v11)
          goto LABEL_15;
      }
      pCurrent = v10;
    }
LABEL_17:
    v14 = pCurrent->pPrev;
    pCmdList->pCurrent = v14;
    ++v7;
    --pCmdList->ItemOfs;
    DrawItemMax = pCmdList->DrawItemMax;
    if (v7 >= DrawItemMax)
      goto LABEL_20;
    v9 = pCmdList->pListTop;
    pCurrent = pCmdList->pHead;
  }
  while (v9 != pCurrent);
  if (pListTop == pHead)
    goto LABEL_36;
LABEL_20:
  v9 = pCmdList->pListTop;
  if (v9 == pCmdList->pHead)
  {
LABEL_37:
    pCmdList->ItemOfs = 0;
    pCmdList->pCurrent = v9;
    return *p_pCurrent;
  }
  v15 = DrawItemMax - 1;
  v16 = pCmdList->pListTop;
  if (DrawItemMax - 1 >= 1)
  {
    v16 = pCmdList->pListTop;
    do
    {
      v16 = v16->pNext;
      if (!v16)
        break;
      --v15;
    }
    while (v15);
  }
  if (p_pCurrent == v16)
  {
    pCmdList->pCurrent = v9;
    pCmdList->ItemOfs = DrawItemMax - 2;
    if (pCmdList->DrawItemMax - 2 >= 1)
    {
      v17 = 0;
      do
      {
        v18 = pCmdList->pCurrent->pNext;
        pCmdList->pCurrent = v18;
        ++v17;
      }
      while (v17 < pCmdList->DrawItemMax - 2);
    }
  }
  v19 = pCmdList->pListTop;
  if (!v19)
  {
    pCmdList->Stat = 0;
    goto LABEL_9000;
  }
  v20 = pCmdList->Stat & 0xFFFFFFFE | (v19->pPrev != 0);
  v21 = pCmdList->DrawItemMax;
  if (v21 < 1)
  {
LABEL_34:
    v22 = v20 | 2;
  }
  else
  {
    while (1)
    {
      v19 = v19->pNext;
      if (!v19)
        break;
      if (!--v21)
        goto LABEL_34;
    }
    v22 = v20 & 0xFFFFFFFD;
  }
  pCmdList->Stat = v22;
LABEL_9000:
  return *p_pCurrent;
}

// 0x1be6a80
void CmdListMoveUnlock(void *pCmdList) {
  pCmdList->Flag &= 0xFFFFFFFC;
}

// 0x1be6a90
u32 ChkCmdListMoveLock(void *pCmdList) {
  return pCmdList->Flag & 2;
}

// 0x1be6aa0
s32 GetCmdListH(void *pCmdList) {
  return pCmdList->DrawItemMax * pCmdList->StepY;
}

// 0x1be6ab0
void ClearCmdListCursorBlur(void *pCmdList) {
  void *i;

  for (i = pCmdList->pHead; i; i = i->pNext)
    i->Timer = 0;
}

// 0x1be6ad0
static void UpdateCmdListTimer(void *pCmdList) {
  void *i;
  s32 Timer;

  for (i = pCmdList->pHead; i; i = i->pNext)
  {
    Timer = i->Timer;
    if (Timer <= 0)
    {
      if ((Timer & 0x80000000) == 0)
        continue;
    }
    else
    {
      Timer -= 16;
    }
    i->Timer = Timer & ~(Timer >> 31);
  }
}

// 0x1be6b10
static void DrawCmdListIcon(s32 X, s32 Y, u32 Z, void *pCmdList, void *pItem, s32 OtNo) {
  ;
}

// 0x1be6b20
u32 GetCmdListItemColor(u32 Col, void *pItem) {
  return 0;
}

// 0x1be6b30
static void DrawCmdListEx(s32 X, s32 Y, u32 Z, s32 StrOfsX, s32 StrOfsY, s32 AlphaRate, u32 Flag, void *pCmdList, s32 OtNo) {
  ;
}

// 0x1be6b40
void DrawCmdList(s32 X, s32 Y, u32 Z, void *pCmdList, s32 OtNo) {

}

// 0x1be6ba0
void *CreateCmdMenu(u32 Type, s32 StrOfsX, s32 StrOfsY, s32 DrawItemMax, s32 StepY) {
  void *v10;
  void *v12;

  v10 = (void *)Allocate(bookCmdMenu_s);
  _ctor(v10, 0);
  v10->Type = Type;
  v10->StrOfsX = StrOfsX;
  v10->StrOfsY = StrOfsY;
  v12 = Allocate(bookCmdList_s);
  _ctor(v12, 0);
  v12->Type = Type;
  v12->DrawItemMax = DrawItemMax;
  v12->pCurrent = 0;
  v12->pListTop = 0;
  v12->pHead = 0;
  v12->ItemOfs = 0;
  v10->pCmdList = v12;
  v12->AlphaRate = 256;
  v10->AlphaRate = 0;
  return v10;
}

// 0x1be6d00
void DestroyCmdMenu(void *pCmdMenu) {
  void *pCmdList;

  pCmdList = pCmdMenu->pCmdList;
  goto LABEL_9;
  do
  {
LABEL_9:
  }
  while (DelCmdListItem(pCmdList));
}

// 0x1be6e00
void SetCmdListAlphaRate(void *pCmdList, s32 AlphaRate) {
  pCmdList->AlphaRate = AlphaRate;
}

// 0x1be6e10
void SetCmdMenuAlphaRate(void *pCmdMenu, s32 AlphaRate) {
  pCmdMenu->AlphaRate = AlphaRate;
}

// 0x1be6e20
void SetCmdMenuCursor(void *pCmdMenu, void *pCursor, s32 X1, s32 X2, s32 X3, s32 X4) {
  void *v7;
  s32 *OfsX;

  v7 = pCmdMenu;
  OfsX = pCmdMenu->Cursor->OfsX;
  OfsX[0] = X1;
  OfsX[1] = X2;
  OfsX[2] = X3;
  OfsX[3] = X4;
  v7->Flag |= 4u;
}

// 0x1be6e50
void CmdMenuCursorDrawUnlock(void *pCmdMenu) {
  pCmdMenu->Flag &= ~4u;
}

// 0x1be6e70
void *AddCmdMenuItem(void *pCmdMenu, s8 pItemName) {
  void *pCmdList;
  void *v7;
  s8 v8;

  pCmdList = pCmdMenu->pCmdList;
  v7 = pCmdList;
  v8 = pItemName;
  return AddCmdListItem(v7, v8);
}

// 0x1be6f10
void *InsertCmdMenuItem(void *pCmdMenu, void *pItem, s8 pItemName, s32 DelItemIndex, u32 Mode) {
  void *pCmdList;
  void *pItema;

  pItema = pItem;
  pCmdList = pCmdMenu->pCmdList;
  return InsertCmdListItem(pCmdList, pItema, pItemName, DelItemIndex, Mode);
}

// 0x1be6fb0
void *DelCmdMenuItem(void *pCmdMenu) {
  void *pCmdList;
  void *v5;

  pCmdList = pCmdMenu->pCmdList;
  v5 = pCmdList;
  return DelCmdListItem(v5);
}

// 0x1be7040
void *CmdMenuItemMoveNextEx(void *pCmdMenu, s32 Mode) {
  void *pCmdList;
  void *v8;

  pCmdList = pCmdMenu->pCmdList;
  v8 = CmdListItemMoveNextEx(pCmdList, Mode, 0);
  if (!v8)
    return v8;
  v8->PnlAlpha = 0;
  return v8;
}

// 0x1be7120
void *CmdMenuItemMovePrevEx(void *pCmdMenu, s32 Mode) {
  void *pCmdList;
  void *v8;

  pCmdList = pCmdMenu->pCmdList;
  v8 = CmdListItemMovePrevEx(pCmdList, Mode, 0);
  if (!v8)
    return v8;
  v8->PnlAlpha = 0;
  return v8;
}

// 0x1be71f0
void *CmdMenuItemMoveNext(void *pCmdMenu) {
  void *pCmdList;
  void *v7;

  pCmdList = pCmdMenu->pCmdList;
  v7 = CmdListItemMoveNextEx(pCmdList, 0, 0);
  if (!v7)
    return v7;
  v7->PnlAlpha = 0;
  return v7;
}

// 0x1be7310
void *CmdMenuItemMovePrev(void *pCmdMenu) {
  void *pCmdList;
  void *v7;

  pCmdList = pCmdMenu->pCmdList;
  v7 = CmdListItemMovePrevEx(pCmdList, 0, 0);
  if (!v7)
    return v7;
  v7->PnlAlpha = 0;
  return v7;
}

// 0x1be7430
void CmdMenuMoveUnlock(void *pCmdMenu) {
  void *pCmdList;

  pCmdList = pCmdMenu->pCmdList;
  pCmdList->Flag &= 0xFFFFFFFC;
}

// 0x1be74a0
u32 ChkCmdMenuMoveLock(void *pCmdMenu) {
  void *pCmdList;

  pCmdList = pCmdMenu->pCmdList;
  return pCmdList->Flag & 2;
}

// 0x1be6df0
void DestroyScrollBar(void *pScrollBar) {
  ;
}

// 0x1be7530
void DrawScrollBar(s32 X, s32 Y, s32 Z, s32 AlphaRate, void *pCmdList, void *pScrollBar, u32 OtNo) {
  ;
}

// 0x1be7540
static void DrawCmdMenuScrollBar(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  ;
}

// 0x1be7550
static void DrawCmdMenuPanelTypeNormal(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 LineMax, u32 OtNo) {
  s32 v7;

  if (LineMax >= 1)
  {
    v7 = LineMax;
    do
    {
      STEPY(pCmdMenu);
      --v7;
    }
    while (v7);
  }
}

// 0x1be7590
static void DrawCmdMenuPanel(s32 X, s32 Y, u32 Z, void *pCmdMenu, u32 OtNo) {
  s32 DrawItemMax;

  DrawItemMax = pCmdMenu->pCmdList->DrawItemMax;
  if (DrawItemMax < 1)
    return;
  goto LABEL_4;
  do
  {
LABEL_4:
    STEPY(pCmdMenu);
    --DrawItemMax;
  }
  while (DrawItemMax);
}

// 0x1be7630
static void DrawCmdMenuTitle(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  ;
}

// 0x1be7640
static void DrawCmdMenuCursor(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  u32 Flag;
  s32 v12;
  s32 v13;
  s32 v15;
  void *Cursor;
  void *v17;
  s32 Timer;
  s32 v19;
  s32 v20;
  s32 v21;

  Flag = pCmdMenu->pCmdList->Flag;
  if ((Flag & 0x10) != 0)
    v12 = 2;
  else
    v12 = (Flag >> 3) & 1;
  LINEOFS(pCmdMenu);
  v15 = Y(pCmdMenu, 0) + Y;
  Cursor = pCmdMenu->Cursor;
  DrawCursorCore(X, v15, Z, v13, Cursor, v12, OtNo);
  v17 = pCmdMenu->Cursor;
  Timer = v17->Timer;
  v19 = Timer + 32;
  v20 = Timer + 16;
  if (v19 >= 256)
    v19 = 256;
  if (v20 >= 512)
    v20 = 512;
  if ((pCmdMenu->Flag & 4) != 0)
    v21 = v20;
  else
    v21 = v19;
  v17->Timer = v21;
}

// 0x1be7770
void DrawCmdMenu(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  void *v11;
  s32 DrawItemMax;
  void *v16;
  void *v17;
  void *v18;

  v11 = pCmdMenu;
  pCmdMenu->pCmdList->AlphaRate = pCmdMenu->AlphaRate;
  DrawItemMax = v11->pCmdList->DrawItemMax;
  if (DrawItemMax < 1)
    goto LABEL_8;
  do
  {
    STEPY(v11);
    --DrawItemMax;
  }
  while (DrawItemMax);
LABEL_8:
  if (ITEMCNT(pCmdMenu))
  {
    DrawCmdMenuCursor(X, Y, Z, pCmdMenu, OtNo);
  }
  v16 = pCmdMenu->UserFunc[0];
  if (!v16 || (v16->invoke_impl)(v16->method_code, X, Y, Z))
  {
    v17 = pCmdMenu;
    if (pCmdMenu->pScrollBar)
    {
      v17 = pCmdMenu;
      v18 = pCmdMenu->UserFunc[1];
      if (v18)
        goto LABEL_24;
      goto LABEL_27;
    }
    v18 = v17->UserFunc[1];
    if (v18)
    {
LABEL_24:
      if (!(v18->invoke_impl)(v18->method_code, X, Y, Z))
        return;
      v17 = pCmdMenu;
    }
LABEL_27:
    v17->Flag |= 4u;
  }
}

// 0x1be7110
void ResetCursorMotion(void *pCursor) {
  ;
}

// 0x1be7990
void DestroyCursor(void *pCursor) {
  ;
}

// 0x1be5540
static void DrawCursorNormal(s32 X, s32 Y, u32 Z, s32 *AlphaRate, void *pCursor, s32 Mode, s32 OtNo) {
  sdfIVector2_t *v11;
  s32 Timer;
  s64 v13;
  sdfIVector2_t v14;
  sdfIVector2_t v15;
  s64 v16;
  s64 v17;

  v11 = NewSpecific(sdfIVector2_t, 0);
  Timer = pCursor->Timer;
  v13 = v11;
  if (Timer >= 257)
    *AlphaRate = (0x20000 - (Timer << 8)) >> 8;
  if (pCursor->SprMax >= 1)
  {
    v14 = (sdfIVector2_t)((s64)&v11[0]);
    if (Mode == 2)
    {
      get_Item((sdfIVector2_t)((s64)&v11[0]), 0, 0);
      get_Item((sdfIVector2_t)(v13 + 32), 1, 0);
      if (pCursor->SprMax >= 2)
      {
        get_Item((sdfIVector2_t)(v13 + 40), 0, 0);
        get_Item((sdfIVector2_t)(v13 + 40), 1, 0);
        if (pCursor->SprMax >= 4)
        {
          v15 = (sdfIVector2_t)(v13 + 56);
          v16 = 3;
          do
          {
            get_Item(v15, 0, 0);
            get_Item(v15, 1, 0);
            ++v16;
            *(u64 *)&v15 += 8;
          }
          while (v16 < pCursor->SprMax);
        }
      }
    }
    else
    {
      v17 = 0;
      do
      {
        get_Item(v14, 0, 0);
        get_Item(v14, 1, 0);
        ++v17;
        *(u64 *)&v14 += 8;
      }
      while (v17 < pCursor->SprMax);
    }
  }
}

// 0x1be56c0
static void DrawCursorLR(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 OtNo) {
  sdfIVector2_t *v8;
  s32 SprMax;
  s64 v10;
  sdfIVector2_t v11;

  v8 = NewSpecific(sdfIVector2_t, 0);
  SprMax = pCursor->SprMax;
  if (SprMax >= 1)
  {
    v10 = 0;
    v11 = (sdfIVector2_t)((s64)&v8[0]);
    do
    {
      if ((u32)v10 != 3 && (u32)v10 != 5)
      {
        get_Item(v11, 0, 0);
        get_Item(v11, 1, 0);
        SprMax = pCursor->SprMax;
      }
      ++v10;
      *(u64 *)&v11 += 8;
    }
    while (v10 < SprMax);
  }
}

// 0x1be5780
static void DrawCursorTabLR(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 OtNo) {
  sdfIVector2_t *v7;
  sdfIVector2_t v8;
  sdfIVector2_t v9;

  v7 = NewSpecific(sdfIVector2_t, 0);
  v8 = (sdfIVector2_t)((s64)&v7[0]);
  v9 = (sdfIVector2_t)v7;
  get_Item((sdfIVector2_t)((s64)&v7[0]), 0, 0);
  get_Item(v8, 1, 0);
  *(u64 *)&v9 += 40;
  get_Item(v9, 0, 0);
  get_Item(v9, 1, 0);
}

// 0x1be79a0
void DrawCursorEx(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 Mode, s32 OtNo) {
  DrawCursorCore(X, Y, Z, AlphaRate, pCursor, Mode, OtNo);
}

// 0x1be7a40
void DrawCursor(s32 X, s32 Y, u32 Z, void *pCursor, s32 OtNo) {
  DrawCursorCore(X, Y, Z, (s32)pCursor, pCursor, 0, OtNo);
}

// 0x1be7760
void UpdateCursor(void *pCursor) {
  ;
}

// 0x1be7b30
static void CmdListRecalcHead(void *pCmdList) {
  void *v2;
  void *pCurrent;
  void *v4;

  v2 = pCmdList;
  pCurrent = v2->pCurrent;
  if (pCurrent)
  {
    do
    {
      v4 = pCurrent;
      pCurrent = pCurrent->pPrev;
    }
    while (pCurrent);
    v2->pHead = v4;
  }
  else
  {
    v2->pHead = 0;
  }
}

// 0x1be7b60
static void CmdListRecalcTail(void *pCmdList) {
  void *v2;
  void *pCurrent;
  void *v4;

  v2 = pCmdList;
  pCurrent = v2->pCurrent;
  if (pCurrent)
  {
    do
    {
      v4 = pCurrent;
      pCurrent = pCurrent->pNext;
    }
    while (pCurrent);
    v2->pTail = v4;
  }
  else
  {
    v2->pTail = 0;
  }
}

// 0x1be7b90
static void CmdListRecalcListTop(void *pCmdList, u32 Mode) {
  void *v5;
  void *pHead;
  void *monitor;
  void *v8;
  void *v9;
  void *v11;
  void *pNext;
  void *v14;

  v5 = pCmdList;
  pHead = pCmdList->pHead;
  v5->pListTop = pHead;
  v5 = ((char *)v5 + 48);
  monitor = v5->monitor;
  v8 = pCmdList;
  v9 = pCmdList->pHead;
  v8->pCurrent = v9;
  v11 = pCmdList;
  pCmdList->ItemOfs = 0;
  if (Mode == 1)
  {
    pNext = v11->pHead;
    if (pNext)
    {
      while (pNext != monitor)
      {
        v14 = pCmdList;
        CmdListItemMoveNextEx(v14, 0, 0);
        pNext = pNext->pNext;
        if (!pNext)
          return;
      }
    }
  }
}

// 0x1be7cd0
static void CmdListRecalcLinkList(void **pItemList, s32 Nums) {
  void *v5;
  void *v6;
  void *v7;
  s64 v8;
  char *v9;
  s64 v10;
  void *v11;
  char *v12;
  s64 v13;
  void *v14;
  s64 v15;
  void *m_Items;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  s64 v21;
  s64 v22;
  void *v23;
  s64 v24;
  s32 v25;
  s64 v26;
  s32 v27;
  s32 v28;
  void *v29;
  s64 v30;
  Il2CppClass **v31;
  Il2CppClass *v32;
  Il2CppClass *v33;

  v5 = (*pItemList)[0];
  v5->pPrev = 0;
  v6 = (*pItemList)[0];
  v7 = (*pItemList)[1];
  v6->pNext = v7;
  if (Nums - 1 > 1)
  {
    v8 = 0;
    do
    {
      v9 = (char *)*pItemList + v8;
      v11 = *((void **)v9 + 4);
      v10 = *((u64 *)v9 + 5);
      *(u64 *)(v10 + 48) = v11;
      v12 = (char *)*pItemList + v8;
      v13 = *((u64 *)v12 + 5);
      v14 = *((void **)v12 + 6);
      *(u64 *)(v13 + 40) = v14;
      v8 += 8;
    }
    while (8 * (u32)(Nums - 1) - 8 != v8);
  }
  v15 = Nums - 1;
  m_Items = (*pItemList);
  v17 = m_Items[v15];
  v18 = m_Items[Nums - 2];
  v17->pPrev = v18;
  v19 = (*pItemList)[v15];
  v19->pNext = 0;
  if (Nums >= 1)
  {
    v20 = *pItemList;
    if ((u32)Nums >= 4)
    {
      v22 = 0;
      v21 = Nums & 0xFFFFFFFC;
      v23 = &v20[3];
      do
      {
        v24 = *(v23 - 2);
        v25 = v22 + 1;
        v26 = *(v23 - 1);
        v27 = v22 + 2;
        v28 = v22 + 3;
        (*(v23 - 3))->Index = v22;
        v29 = v23;
        v23 += 4;
        v22 += 4;
        *(u32 *)(v24 + 20) = v25;
        *(u32 *)(v26 + 20) = v27;
        v29->Index = v28;
      }
      while (v21 != v22);
      if (v21 == Nums)
        return;
    }
    else
    {
      v21 = 0;
    }
    v30 = ~v21;
    if ((Nums & 1) != 0)
    {
      v20[v21]->Index = v21;
      v21 |= 1u;
    }
    if (v30 + (u32)Nums)
    {
      do
      {
        v31 = &v20->obj.klass + v21;
        v33 = v31[4];
        v32 = v31[5];
        HIDWORD(v33->_1.name) = v21;
        LODWORD(v33) = v21 + 1;
        v21 += 2;
        HIDWORD(v32->_1.name) = (u32)v33;
      }
      while (v21 != Nums);
    }
  }
}

// 0x1be7e70
static s32 CmdListSortCallbackA(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 8);
  v8 = *((u32 *)op2[3].monitor + 8);
  v9 = v7 > v8;
  v10 = v7 < v8;
  if (v9)
    return -1;
  else
    return v10;
}

// 0x1be7f50
static s32 CmdListSortCallbackA_R(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 8);
  v8 = *((u32 *)op2[3].monitor + 8);
  v9 = v7 > v8;
  if (v7 >= v8)
    v10 = 0;
  else
    v10 = -1;
  if (v9)
    return 1;
  else
    return v10;
}

// 0x1be8030
static s32 CmdListSortCallbackB(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 9);
  v8 = *((u32 *)op2[3].monitor + 9);
  v9 = v7 > v8;
  v10 = v7 < v8;
  if (v9)
    return -1;
  else
    return v10;
}

// 0x1be8110
static s32 CmdListSortCallbackB_R(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 9);
  v8 = *((u32 *)op2[3].monitor + 9);
  v9 = v7 > v8;
  if (v7 >= v8)
    v10 = 0;
  else
    v10 = -1;
  if (v9)
    return 1;
  else
    return v10;
}

// 0x1be81f0
static s32 CmdListSortCallbackC(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 10);
  v8 = *((u32 *)op2[3].monitor + 10);
  v9 = v7 > v8;
  v10 = v7 < v8;
  if (v9)
    return -1;
  else
    return v10;
}

// 0x1be82d0
static s32 CmdListSortCallbackC_R(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 10);
  v8 = *((u32 *)op2[3].monitor + 10);
  v9 = v7 > v8;
  if (v7 >= v8)
    v10 = 0;
  else
    v10 = -1;
  if (v9)
    return 1;
  else
    return v10;
}

// 0x1be83b0
void CmdListSort(void *pCmdList, u32 Type, u32 Mode) {
  void *pHead;
  void *p_pHead;
  s32 v8;
  void *pCurrent;
  void *p_pCurrent;
  void *v13;
  void *pNext;
  void *v15;
  void *v16;
  void *v17;
  void *pItemList;

  pItemList = NewSpecific(bookCmdListItem_s, pCmdList->ItemCnt);
  p_pHead = &pCmdList->pHead;
  pHead = pCmdList->pHead;
  if (!pHead)
  {
    v8 = 0;
    goto LABEL_7;
  }
  v8 = 0;
  do
  {
    pHead = pHead->pNext;
    ++v8;
  }
  while (pHead);
LABEL_7:
  CmdListRecalcLinkList(&pItemList, v8);
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  if (!pCurrent)
  {
    p_pHead = 0;
    pNext = p_pCurrent;
    if (p_pCurrent)
      goto LABEL_15;
LABEL_19:
    pCmdList->pTail = 0;
    goto LABEL_18;
  }
  do
  {
    v13 = pCurrent;
    pCurrent = pCurrent->pPrev;
  }
  while (pCurrent);
  p_pHead = v13;
  pNext = p_pCurrent;
  if (!p_pCurrent)
    goto LABEL_19;
  do
  {
LABEL_15:
    v15 = pNext;
    pNext = pNext->pNext;
  }
  while (pNext);
  pCmdList->pTail = v15;
LABEL_18:
  v16 = pCmdList->pHead;
  pCmdList->pListTop = v16;
  v17 = pCmdList->pHead;
  pCmdList->pCurrent = v17;
  pCmdList->ItemOfs = 0;
}

// 0x1be8560
void CreateCmdMenuMover(void *pMover) {
  s32 *pItem;
  s64 v4;
  s64 v5;
  void *v6;

  pItem = pMover->pItem;
  if (pItem[6] >= 1)
  {
    v4 = 0;
    v5 = 8;
    do
    {
      v6 = Allocate(bookCmdMenuMoverCore_t);
      _ctor(v6, 0);
      if (v6)
      {
        QueryInterface(v6, *(void **)(*(u64 *)pItem + 64));
      }
      *(u64 *)&pItem[v5] = v6;
      ++v4;
      v5 += 2;
      pItem = pMover->pItem;
    }
    while (v4 < pItem[6]);
  }
}

// 0x1be8640
void DestroyCmdMenuMover(void *pMover) {
  ;
}

// 0x1be8650
void SetCmdMenuToMover(u32 Type, void *pCmdMenu, void *pMover) {
  void *pItem;
  s64 ItemCnt;
  void *v6;

  pItem = pMover->pItem;
  ItemCnt = pMover->ItemCnt;
  if (SLODWORD(pItem->max_length) < ItemCnt)
  {
    pMover->ItemCnt = ItemCnt + 1;
    v6 = pItem[ItemCnt];
    v6->pCmdMenu = pCmdMenu;
    v6 = ((char *)v6 + 16);
    LODWORD(v6->monitor) = Type;
  }
}

// 0x1be8690
void DelCmdMenuFromMover(void *pMover, u32 Index) {
  s64 v5;
  void *pItem;
  void *pCmdMenu;
  void *v8;
  void *v9;

  v5 = Index;
  pItem = pMover->pItem;
  if (SLODWORD(pItem->max_length) >= (s64)Index)
    return;
  pCmdMenu = pItem[v5]->pCmdMenu;
  DestroyCmdMenu(pCmdMenu);
  v8 = pMover->pItem[v5];
  v8->pCmdMenu = 0;
  v9 = pMover->pItem[0];
  v9->pCmdMenu = 0;
  --pMover->ItemCnt;
}

// 0x1be8790
void DrawCmdMenuMover(u32 Z, void *pMover, u32 OtNo) {
  s64 v8;
  s32 v9;
  void *v10;
  s32 X;
  s32 Y;

  if (pMover->ItemCnt)
  {
    v8 = 0;
    v9 = 1;
    do
    {
      v10 = pMover->pItem[v8];
      X = v10->X;
      Y = v10->Y;
      DrawCmdMenu(X, Y, Z, &v10->pCmdMenu, OtNo);
      v8 = v9++;
    }
    while (v8 < pMover->ItemCnt);
  }
}

// 0x1be8860
void UpdateCmdMenuMover(void *pMover) {
  void *pItem;
  s64 v5;
  void *v6;
  u32 Timer;
  void *pMovera;

  pMovera = pMover;
  pItem = pMover->pItem;
  if (SLODWORD(pItem->max_length) >= 1)
  {
    v5 = 0;
    do
    {
      while (1)
      {
        v6 = pItem[v5];
        Timer = v6->Timer;
        if (!Timer)
          break;
        v6->Timer = Timer - 64;
        if (++v5 >= SLODWORD(pItem->max_length))
          return;
      }
      DelCmdMenuFromMover(pMovera, v5);
      pItem = pMover->pItem;
      ++v5;
    }
    while (v5 < SLODWORD(pItem->max_length));
  }
}

// 0x1be8930
void InitCmdMenuManager(void *pHandle) {
  void *v3;

  v3 = pHandle;
  v3->pDst = 0;
  v3 = ((char *)v3 + 32);
  *(void **)((char *)&v3->monitor + 4) = 0x20000000000LL;
  pHandle->DstTimer = 0;
}

// 0x1be8970
void SetCmdMenuManager(void *pCmdMenu, void *pHandle) {
  void *v4;
  void *v5;
  void *p_pDst;

  v4 = pHandle;
  *(u64 *)&pHandle->SrcScrollBarFlag = 0x20000000000LL;
  v5 = pCmdMenu;
  if (pCmdMenu)
  {
    v5->Cursor->Timer = 512;
    v5->Flag |= 4u;
  }
  v4->pDst = v5;
  p_pDst = &v4->pDst;
  *((u32 *)p_pDst + 5) = 0;
}

// 0x1be89b0
void ResetCmdMenuManager(void *pHandle) {
  void *v3;

  v3 = pHandle;
  v3->pDst = 0;
  v3 = ((char *)v3 + 32);
  LODWORD(v3->Src) = 512;
  pHandle->DstTimer = 0;
}

// 0x1be89f0
void DrawCmdMenuManager(s32 X, s32 Y, s32 Z, void *pHandle, u32 OtNo) {
  void *v11;
  s32 SrcTimer;
  void *v13;
  void *Src;
  void *SrcScrollBar;
  s32 v16;
  s32 v17;
  void *v19;
  s32 DstTimer;
  s32 v21;
  s32 v22;
  void *v23;
  void *p_pDst;
  void *pDst;
  void *v28;
  s32 v29;

  v11 = pHandle;
  SrcTimer = pHandle->SrcTimer;
  if (SrcTimer > 511)
    goto LABEL_12;
  v13 = pHandle;
  v13 = pHandle;
  Src = v13->Src;
  SrcScrollBar = v13->SrcScrollBar;
  if (SrcTimer >= 0)
    v16 = SrcTimer;
  else
    v16 = SrcTimer + 1;
  v11->Src->AlphaRate = 256 - (v16 >> 1);
  Src->pScrollBar = SrcScrollBar;
  v11 = pHandle;
  v17 = pHandle->SrcTimer;
  if (v17 < 512)
  {
    v17 += 100;
    goto LABEL_30;
  }
  if (v17 < 513)
  {
LABEL_12:
    v19 = v11;
    DstTimer = v11->DstTimer;
    goto LABEL_14;
  }
LABEL_30:
  if (v17 >= 512)
    v17 = 512;
  v11->SrcTimer = v17;
  v19 = v11;
  DstTimer = v11->DstTimer;
  v19 = pHandle;
LABEL_14:
  if (DstTimer >= 0)
    v21 = DstTimer;
  else
    v21 = DstTimer + 1;
  v22 = v21 >> 1;
  pDst = v19->pDst;
  p_pDst = &v19->pDst;
  v23 = pDst;
  v11->pDst->AlphaRate = v22;
  if (pDst->Cursor->Timer)
  {
    goto LABEL_19;
  }
  else
  {
    v23->Flag &= ~4u;
    goto LABEL_19;
  }
LABEL_19:
  DrawCmdMenu(X, Y, Z, p_pDst, OtNo);
  v28 = pHandle;
  v29 = v28->DstTimer;
  if (v29 < 512)
  {
    v29 += 80;
    goto LABEL_24;
  }
  if (v29 >= 513)
  {
LABEL_24:
    if (v29 >= 512)
      v29 = 512;
    v28->DstTimer = v29;
    goto LABEL_23;
  }
LABEL_23:
  DrawCmdMenu(X, Y, Z, &v28->pDst, OtNo);
}

// 0x1be8be0
sprHandle_t *GetSpriteHandle(void) {
  sprHandle_t *ProcessData;
  s64 naturalAligment;

  if (!GlobalPID)
    return 0;
  ProcessData = (sprHandle_t *)dds3GetProcessData(GlobalPID);
  if (!ProcessData)
    return ProcessData[22];
  LOBYTE(ProcessData[6].Type) < (u32)naturalAligment || *((bookData_t **)(ProcessData)[4].monitor + naturalAligment - 1) != bookData_t;
  return ProcessData[22];
}

// 0x1be8d20
void ModelFree(bookData_t *pData) {
  pData->Flag &= 0xFFFFFFF0;
}

// 0x1be8d40
void LoadBgModel(dds3ProcessID_t *ParentPID, bookData_t *pData) {
  char *v6;
  char *v8;
  void *SceneAsync;

  if ((pData->Flag & 0x30) != 0)
    return;
  v6 = "UI_DBook";
  book_scene_name = "UI_DBook";
  v8 = "dbook";
  Load(Dependent, v8, v8);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, book_scene_name, 0);
  scene_asyncLoad = SceneAsync;
  if (QuestFlag)
  {
    fldJmsQuestSceneLoadInit();
  }
  pData->Flag |= 0x10u;
}

// 0x1be8f70
s32 CheckBgModel(bookData_t *pData) {
  if (!scene_asyncLoad)
    goto LABEL_9;
  if (get_isDone(scene_asyncLoad, 0))
    goto LABEL_9;
  return 0;
LABEL_9:
  pData->Flag |= 0x20u;
  Unload(Dependent, "dbook", 0);
  return 1;
}

// 0x1be90b0
void FreeBgModel(bookData_t *pData) {
  pData->Flag &= 0xFFFFFFCF;
}

// 0x1be90d0
static void StartEtcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  u32 v6;
  dds3ProcessFunc_t v7;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = Allocate(dds3ProcessID_t);
  _ctor(v5, 0);
  if (cmpProcessCheck())
    v6 = 20;
  else
    v6 = 30;
  dds3FadeIn(0, 0, 0, v6);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_DitectiveBook_RootWaitDrawProcess__, 0);
  dds3StartProcess("DitectiveBook_Draw", 11028, 0, 0, v7, 0, ProcessData);
  v8 = Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_DitectiveBook_RootWaitUpdateProcess__, 0);
  dds3StartProcess("DitectiveBook_Update", 21009, 0, 0, v8, 0, ProcessData);
}

// 0x1be9360
static dds3ProcessFunc_t Load2ndProcess(dds3ProcessID_t *PID) {
  bookData_t *ProcessData;
  u8 Stat;
  dds3ProcessID_t *v17;
  s32 Flag;
  dds3ProcessFunc_t v20;
  dds3ProcessFunc_t v21;
  intptr_t *v22;
  bool v23;
  bookData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  pData = ProcessData;
  LoadBgModel(DitectiveBook, pData);
  if (!CheckBgModel(pData))
    return 0;
  v23 = CheckRun();
  if (!v23)
  {
    if (SakuraCnt <= 3)
      goto LABEL_30;
    goto LABEL_17;
  }
  if (SakuraCnt > 6)
    goto LABEL_17;
LABEL_30:
  SakuraCnt = SakuraCnt + 1;
  SakuraEffectDraw();
  return 0;
LABEL_17:
  Stat = GBWK->Moon->Stat;
  moonSave = Stat;
  if ((Stat & 2) == 0)
  {
    v17 = id;
    goto LABEL_21;
  }
  evtMoonDisableDraw(1);
  v17 = id;
LABEL_21:
  StartEtcProcess(v17);
  Flag = ProcessData->Flag;
  if ((Flag & 0x800) == 0)
    goto LABEL_22;
  ProcessData->Flag = Flag | 0x400;
  if (evtBitCheck(42))
    goto LABEL_23;
LABEL_43:
  ButtonGuideDispOff();
  SetActive(bookUI->BUTTONGUIDEOBJECT, 0, 0);
  PANELActiveOnOff(bookUI, 0, 0);
  MenuActiveOnOff(bookUI, 0, 0);
  v20 = Allocate(dds3ProcessFunc_t);
  v21 = v20;
  v22 = &Method_Project_DitectiveBook_TipsWaitCalcProcess__;
  goto LABEL_48;
LABEL_22:
  if (!evtBitCheck(42))
    goto LABEL_43;
LABEL_23:
  MenuProcessStart();
  v20 = Allocate(dds3ProcessFunc_t);
  v21 = v20;
  v22 = &Method_Project_DitectiveBook_RootWaitCalcProcess__;
LABEL_48:
  _ctor(v20, 0, *v22, 0);
  return v21;
}

// 0x1bea590
static dds3ProcessFunc_t Load0Process(dds3ProcessID_t *PID) {
  void *p_Dependent;
  void *Dependent_local;
  dds3ProcessFunc_t v7;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, jms_asset_name, jms_asset_name);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_DitectiveBook_Load1stProcess__, 0);
  return v7;
}

// 0x1bea6f0
static dds3ProcessFunc_t Load1stProcess(dds3ProcessID_t *PID) {
  void *p_Dependent;
  void *Dependent_local;
  bool IsLoad;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *id;

  id = PID;
  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  IsLoad = IsLoad(Dependent_local, jms_asset_name, 0);
  v7 = 0;
  if (!IsLoad)
    return v7;
  dds3GetProcessData(id);
  SetDestCheck();
  Unload(Dependent, jms_asset_name, 0);
  v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_DitectiveBook_Load2ndProcess__, 0);
  return v7;
}

// 0x1bead60
static bookData_t *Init(void) {
  void *p_Dependent;
  void *Dependent_local;
  void *Asset;
  s64 naturalAligment;
  void *v9;
  void *v10;
  void *v12;
  void *v15;
  bookData_t *v17;
  s32 *SeqParent;
  DITECTIVEBOOK_CLASS *v19;
  s64 i;
  DITECTIVEBOOK_CLASS *BOOKPAGE_local;
  DITECTIVEBOOK_CLASS *v23;
  void *v25;
  s64 v27;
  void *v28;
  DBOOK_READ_FLAG_CLASS *v31;
  s64 j;
  DBOOK_READ_FLAG_CLASS *v33;
  il2cpp_array_size_t max_length;
  il2cpp_array_size_t v35;
  DBOOK_READ_FLAG_CLASS *m_Items;
  s32 *dbook_updateFlag;
  bool *v40;
  s32 *v41;
  s64 v42;
  s64 v43;
  DBOOK_READ_FLAG_CLASS *v44;
  s64 v48;
  s32 *v49;
  s64 v50;
  DITECTIVEBOOK_CLASS *v51;
  s64 v52;
  DITECTIVEBOOK_CLASS *TblDate;
  DITECTIVEBOOK_CLASS *v54;
  s64 v56;
  s64 v57;
  s64 v58;
  Il2CppClass *v59;
  DITECTIVEBOOK_CLASS *v60;
  char *v61;
  char *v62;
  char *v63;
  char *v64;
  void *p_DestListTbl;
  void *v67;
  s64 v68;
  DBOOK_READ_FLAG_CLASS *v69;
  DBOOK_READ_FLAG_CLASS *v70;
  dds3GlobalWork_t *v71;
  bool *dbook_readFlag;
  s64 v73;
  s64 v74;
  DBOOK_READ_FLAG_CLASS *v75;
  void *v80;
  s64 v81;
  void *v82;
  DITECTIVEBOOK_CLASS *v85;
  DITECTIVEBOOK_CLASS *v86;
  DITECTIVEBOOK_CLASS *v87;
  DITECTIVEBOOK_CLASS *v88;
  DITECTIVEBOOK_CLASS *v89;
  DITECTIVEBOOK_CLASS *v90;
  bookSeqHandle_t *v92;
  char *DLCname;
  char *name;
  char *v107;
  char *v108;
  char *v109;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, DbookDataAssetKey, DbookDataAssetKey);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, DbookDataAssetKey, "DBookPanelDataTable", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DitectiveBookPanelDataTable)
      v9 = Asset;
    else
      v9 = 0;
  }
  else
  {
    v9 = 0;
  }
  v10 = Allocate(System_Collections_Generic_List_DestData_t_);
  __ctor(v10);
  DestNowList = v10;
  v12 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v12);
  DestTextList = v12;
  DestListTbl = 0;
  v15 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v15);
  DestTextIDList = v15;
  v17 = (bookData_t *)Allocate(bookData_t);
  _ctor(v17, 0);
  v17->nowHierarchy = 0;
  v17->MenuFade = 1;
  v17->BgmNo = 16;
  SeqParent = v17->SeqParent;
  *(u64 *)SeqParent = 0;
  *(u64 *)&SeqParent[2] = 0;
  v19 = NewSpecific(DITECTIVEBOOK_CLASS, 0x100u);
  BOOKPAGE = v19;
  for (i = 32; i != 2080; i += 8)
  {
    BOOKPAGE_local = BOOKPAGE;
    v23 = Allocate(DITECTIVEBOOK_CLASS);
    _ctor_30843072(v23, 0);
    *(Il2CppClass **)((char *)&BOOKPAGE_local->obj.klass + i) = v23;
  }
  v25 = LoadAsset(_Ctrl_k__BackingField, "fld_common", "DestTbl", 0);
  if (v25)
  {
    if (v25->klass->_2.naturalAligment >= (u32)v27)
    {
      if (v25->klass->_2.typeHierarchy[v27 - 1] == Project_DestTbl)
        v28 = v25;
      else
        v28 = 0;
    }
    else
    {
      v28 = 0;
    }
    DestListTbl = (void *)v28;
    p_DestListTbl = &DestListTbl;
    if (v25->klass->_2.naturalAligment >= (u32)v27)
    {
      if (v25->klass->_2.typeHierarchy[v27 - 1] == Project_DestTbl)
        v67 = v25;
      else
        v67 = 0;
      goto LABEL_41;
    }
    else
    {
      goto LABEL_41;
    }
    goto LABEL_40;
  }
  DestListTbl = 0;
LABEL_40:
LABEL_41:
  if (!ProcessCheck())
  {
    cmpLoadEffect();
  }
  v31 = NewSpecific(DBOOK_READ_FLAG_CLASS, 0x100u);
  for (j = 32; j != 2080; j += 8)
  {
    v33 = Allocate(DBOOK_READ_FLAG_CLASS);
    _ctor(v33, 0);
    *(Il2CppClass **)((char *)&v31->obj.klass + j) = v33;
  }
  max_length = v31->max_length;
  if ((s32)max_length < 1)
  {
LABEL_54:
    v44 = NewSpecific(DBOOK_READ_FLAG_CLASS, max_length);
    goto LABEL_55;
  }
  v35 = (u32)v31->max_length;
  m_Items = v31;
  dbook_updateFlag = GBWK->dbook_updateFlag;
  v40 = GBWK->dbook_readFlag;
  v41 = dbook_updateFlag;
  do
  {
    v43 = (s64)*m_Items++;
    v42 = v43;
    --v35;
    LOBYTE(v43) = *v40++;
    *(u8 *)(v42 + 16) = v43;
    LODWORD(v43) = *v41++;
    *(u32 *)(v42 + 20) = v43;
  }
  while (v35);
  goto LABEL_54;
  do
  {
    v75 = v69[v68];
    v70 = v69[v68];
    v71 = GBWK;
    dbook_readFlag = v71->dbook_readFlag;
    v73 = (s64)v71->dbook_updateFlag + 4 * v68;
    v74 = (s64)dbook_readFlag + v68++;
    LODWORD(v73) = *(u32 *)(v73 + 32);
    v75->READ_FLAG = *(u8 *)(v74 + 32);
    v70->UPDATE_FLAG = v73;
  }
  while (v68 < (s32)v35);
  v44 = NewSpecific(DBOOK_READ_FLAG_CLASS, v35);
LABEL_55:
  DBOOK_READ_FLAG = v44;
  DBOOK_READ_FLAG = v31;
  v48 = NewSpecific(DITECTIVEBOOK_CLASS, v9->_arrPanel->_size);
  v49 = v48;
  if (v9->_arrPanel->_size >= 1)
  {
    v50 = 0;
    v51 = (v48 + 32);
    while (1)
    {
      TblDate = GetTblDate(v9, v50, 0);
      v54 = TblDate;
      if (TblDate)
      {
        if (!QueryInterface(TblDate, *(void **)(*(u64 *)v49 + 64)))
          break;
      }
      v51 = v54;
      v52 = (s64)*v51++;
      ++v50;
      *(u32 *)(v52 + 56) = 0;
      if (v50 >= v9->_arrPanel->_size)
        goto LABEL_61;
    }
  }
LABEL_61:
  if (v49[6] >= 1)
  {
    v56 = 0;
    v57 = 8;
    do
    {
      v59 = *(Il2CppClass **)&v49[v57];
      v60 = BOOKPAGE;
      if (!v59)
      *(Il2CppClass **)((char *)&v60->obj.klass + v57 * 4) = v59;
      ++v56;
      v58 = *(s64 *)((char *)&BOOKPAGE->obj.klass + v57 * 4);
      v57 += 2;
      *(u32 *)(v58 + 92) = 0;
    }
    while (v56 < v49[6]);
  }
  NewSpecific(DITECTIVEBOOK_CLASS, 0x100u);
  v61 = "new_exp";
  v62 = "new_oni";
  v63 = "new_title";
  v64 = "new_dbook";
  v109 = "new_devil";
  v108 = "new_glasses";
  v107 = "new_skill";
  name = "new_item";
  DLCname = "new_crm";
  if (Exists("new_exp"))
    goto LABEL_119;
  if (Exists(v62))
    goto LABEL_119;
  if (Exists(v63))
    goto LABEL_119;
  if (Exists(v64))
    goto LABEL_119;
  if (Exists(v109))
    goto LABEL_119;
  if (Exists(v108))
    goto LABEL_119;
  if (Exists(v107))
    goto LABEL_119;
  if (Exists(name))
    goto LABEL_119;
  if (Exists(DLCname))
  {
LABEL_119:
    Load(Dependent, "dlc_all_dbookdata", "dlc_all_dbookdata");
    LoadSyncAll(_Ctrl_k__BackingField, 0);
    Load(Dependent, "dlc_all_dbooktext.", "dlc_all_dbooktext.");
    LoadSyncAll(_Ctrl_k__BackingField, 0);
    LoadLocalizeText_2("dlc_all_dbooktext.", "DBOOK_DLC_ALL_TITLE");
    v80 = LoadAsset(_Ctrl_k__BackingField, "dlc_all_dbookdata", "DBookPanelDataTable_DLCALL", 0);
    {
      if (v80->klass->_2.typeHierarchy[v81 - 1] == Project_DitectiveBookPanelDataTable)
        v82 = v80;
      else
        v82 = 0;
LABEL_133:
      v85 = BOOKPAGE;
      DLCEXIST = 1;
      v86 = GetTblDate(v82, 0, 0);
      v87 = v86;
      v85[230] = v87;
      v88 = BOOKPAGE;
      v89 = GetTblDate(v82, 1, 0);
      v90 = v89;
      v88[243] = v90;
      Unload(Dependent, "dlc_all_dbookdata", 0);
      Unload(Dependent, "dlc_all_dbooktext.", 0);
      goto LABEL_139;
    }
    else
    {
      v82 = 0;
      goto LABEL_133;
    }
    goto LABEL_133;
  }
  DLCEXIST = 0;
LABEL_139:
  if (DLCEXIST)
  {
    DBookCheckDLC(v61, "dlc_exp_dbookdata", "DBookPanelDataTable_DLCDE1", "dlc_exp_dbooktext.", "DBOOK_DLC_DE1_TEXT", "DBOOK_DLC_DE1_TITLE", 0, "", "");
    DBookCheckDLC(v62, "dlc_oni1_dbookdata", "DBookPanelDataTable_DLCDZ1", "dlc_oni1_dbooktext.", "DBOOK_DLC_DZ1_TEXT", "DBOOK_DLC_DZ1_TITLE", 0, "", "");
    DBookCheckDLC(v63, "dlc_title_dbookdata", "DBookPanelDataTable_DLCDS1", "dlc_title_dbooktext.", "DBOOK_DLC_DS1_TEXT", "DBOOK_DLC_DS1_TITLE", 0, "", "");
    DBookCheckDLC(v64, "dlc_dbook_dbookdata", "DBookPanelDataTable_DLCDB1", "dlc_dbook_dbooktext.", "DBOOK_DLC_DB1_TEXT", "DBOOK_DLC_DB1_TITLE", 0, "", "");
    DBookCheckDLC(v109, "dlc_devil_dbookdata", "DBookPanelDataTable_DLCDD1", "dlc_devil_dbooktext.", "DBOOK_DLC_DD1_TEXT", "DBOOK_DLC_DD1_TITLE", 0, "", "");
    DBookCheckDLC(v108, "dlc_glasses_dbookdata", "DBookPanelDataTable_DLCRM1", "dlc_glasses_dbooktext.", "DBOOK_DLC_RM1_TEXT", "DBOOK_DLC_RM1_TITLE", 0, "", "");
    DBookCheckDLC(v107, "dlc_skill_dbookdata", "DBookPanelDataTable_DLCDI1", "dlc_skill_dbooktext.", "DBOOK_DLC_DI1_TEXT", "DBOOK_DLC_DI1_TITLE", 0, "", "");
    DBookCheckDLC(name, "dlc_item_dbookdata", "DBookPanelDataTable_DLCDI2", "dlc_item_dbooktext.", "DBOOK_DLC_DI2_TEXT", "DBOOK_DLC_DI2_TITLE", 0, "", "");
    DBookCheckDLC(DLCname, "dlc_crm_dbookdata", "DBookPanelDataTable_DLCDI3", "dlc_crm_dbooktext.", "DBOOK_DLC_DI3_TEXT", "DBOOK_DLC_DI3_TITLE", 0, "", "");
  }
  v92 = Allocate(bookSeqHandle_t);
  _ctor(v92, 0);
  Unload(Dependent, DbookDataAssetKey, 0);
  Unload(Dependent, DbookImageDataAssetKey, 0);
  Unload(Dependent, "dbook", 0);
  return v17;
}

// 0x1bec230
void DBookCheckDLC(char *DLCname, char *keyName, char *assetName, char *textKeyName, char *textAssetName, char *titleAssetName, bool helptextFlg, char *helpTextKeyName, char *helpTextAssetName) {
  char *v24;
  void *Asset;
  s64 naturalAligment;
  void *v29;
  s32 v30;
  s32 size;
  s64 v32;
  s64 v34;
  DITECTIVEBOOK_CLASS *v35;
  s64 v36;
  DITECTIVEBOOK_CLASS *TblDate;
  s32 v38;
  s32 v39;
  Il2CppClass **v40;
  DITECTIVEBOOK_CLASS *BOOKPAGE_local;
  s64 ID;
  DITECTIVEBOOK_CLASS *v44;
  DITECTIVEBOOK_CLASS *v45;

  if (!Exists(DLCname))
    return;
  Load(Dependent, keyName, keyName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Load(Dependent, textKeyName, textKeyName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  LoadLocalizeText_2(textKeyName, textAssetName);
  LoadLocalizeText_2(textKeyName, titleAssetName);
  if (!helptextFlg)
  {
    goto LABEL_27;
  }
  Load(Dependent, helpTextKeyName, helpTextKeyName);
  v24 = helpTextAssetName;
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  LoadLocalizeText_2(helpTextKeyName, v24);
  Unload(Dependent, helpTextKeyName, 0);
LABEL_27:
  Asset = LoadAsset(_Ctrl_k__BackingField, keyName, assetName, 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DitectiveBookPanelDataTable)
      v29 = Asset;
    else
      v29 = 0;
    if (v29->_arrPanel->_size < 1)
      goto LABEL_64;
  }
  else
  {
    v29 = 0;
    if ((s32)&xmmword_0 < 1)
      goto LABEL_64;
  }
  v30 = 0;
  do
  {
    if (SLODWORD(GetTblDate(v29, v30, 0)->upDateTextFlag->max_length) >= 1)
    {
      v32 = 8;
      do
      {
        TblDate = GetTblDate(v29, v30, 0);
        if (!evtBitCheck(*((u32 *)&TblDate->upDateTextFlag->obj.klass + v32)))
        {
          v38 = *((u32 *)&GetTblDate(v29, v30, 0)->upDateTextFlag->obj.klass + v32);
          if (v38)
          {
            if ((u32)(v38 - 2618) >= 0xFFFFFFC6)
              evtBitKityouItemAdd(v38);
            v34 = (s64)GBWK->EventBit + 4 * (v38 / 32);
            *(u32 *)(v34 + 32) |= 1 << v38;
          }
        }
        v35 = GetTblDate(v29, v30, 0);
        v36 = v32 - 7;
        ++v32;
      }
      while (v36 < SLODWORD(v35->upDateTextFlag->max_length));
    }
    ++v30;
    size = v29->_arrPanel->_size;
  }
  while (v30 < size);
  if (size >= 1)
  {
    v39 = 0;
    do
    {
      BOOKPAGE_local = BOOKPAGE;
      ID = GetTblDate(v29, v39, 0)->ID;
      v44 = GetTblDate(v29, v39, 0);
      v45 = v44;
      v40 = &BOOKPAGE_local->obj.klass + ID;
      v40[4] = v45;
      ++v39;
    }
    while (v39 < v29->_arrPanel->_size);
  }
LABEL_64:
  Unload(Dependent, keyName, 0);
  Unload(Dependent, textKeyName, 0);
  if (op_Equality(assetName, "DBookPanelDataTable_DLCDE1", 0))
  {
    DLCDEEXIST = 1;
  }
  else if (op_Equality(assetName, "DBookPanelDataTable_DLCDZ1", 0))
  {
    DLCDZEXIST = 1;
  }
}

// 0x1bea8c0
void SetDestCheck(void) {
  s32 size;
  s32 v6;
  s32 v8;
  s32 v9;
  void *DestData_28574400;
  void *v13;
  s32 i;
  Il2CppObject *Item;
  s32 klass;
  s32 chapter;
  s32 klass_high;
  s32 v21;
  u32 v22;
  void *v24;
  s64 v25;
  u64 *v26;
  void *items;
  Il2CppClass **v28;
  Il2CppObject *monitor;
  void *v31;
  u64 *v32;
  s64 v33;
  void *v34;
  Il2CppClass **v35;

  if (cfgGetConfigGAME(11, 0))
    return;
  size = DestNowList->_size;
  v6 = DestNowList->_version + 1;
  DestNowList->_size = 0;
  DestNowList->_version = v6;
  if (size >= 1)
  {
    Clear(DestNowList->_items, 0, size, 0);
  }
  v8 = DestTextList->_size;
  v9 = DestTextList->_version + 1;
  DestTextList->_size = 0;
  DestTextList->_version = v9;
  if (v8 >= 1)
  {
    Clear(DestTextList->_items, 0, v8, 0);
  }
  DestData_28574400 = GetDestData_28574400(DestListTbl, GBWK->GameFileInfo->chapter, 0);
  if (DestData_28574400->_size >= 1)
  {
    v13 = DestData_28574400;
    for (i = 0; i < v13->_size; ++i)
    {
      Item = _get_Item(v13, i);
      klass = Item[1].klass;
      chapter = GBWK->GameFileInfo->chapter;
      if (!fldDestBitChk(chapter, klass))
        continue;
      klass_high = HIDWORD(Item[1].klass);
      v21 = GBWK->GameFileInfo->chapter;
      if (fldDestBitChk(v21, klass_high))
        continue;
      if (GBWK->GameFileInfo->chapter != 3)
        goto LABEL_37;
      v22 = Item[1].klass;
      if (v22 > 0x16 || ((1 << v22) & 0x7C02A0) == 0)
      {
LABEL_37:
        v24 = DestNowList;
        v25 = v24->_size;
        v26 = Method_System_Collections_Generic_List_DestData_t__Add__;
        ++v24->_version;
        items = v24->_items;
        if ((u32)v25 >= LODWORD(items->max_length))
        {
          _AddWithResize(v24, Item, *(const MethodInfo_2DFC660 **)(*(u64 *)(v26[4] + 192) + 112));
        }
        else
        {
          v24->_size = v25 + 1;
          v28 = &items->obj.klass + v25;
          v28[4] = Item;
        }
        if (!_Contains(DestTextList, Item[1].monitor))
        {
          monitor = Item[1].monitor;
          v31 = DestTextList;
          v32 = Method_System_Collections_Generic_List_string__Add__;
          v33 = v31->_size;
          ++v31->_version;
          v34 = v31->_items;
          if ((u32)v33 >= LODWORD(v34->max_length))
          {
            _AddWithResize(v31, monitor, *(const MethodInfo_2DFC660 **)(*(u64 *)(v32[4] + 192) + 112));
          }
          else
          {
            v31->_size = v33 + 1;
            v35 = &v34->obj.klass + v33;
            v35[4] = monitor;
          }
        }
      }
    }
  }
  GetDest();
}

// 0x1bec930
void GetDest(void) {
  s32 size;
  s32 v5;
  u32 i;
  void *DestData_28574400;
  void *v10;
  s32 j;
  Il2CppObject *Item;
  u32 chapter;
  Il2CppObject *monitor;
  void *v18;
  u64 *v19;
  s64 v20;
  void *items;
  Il2CppClass **v22;
  s32 klass;
  s32 v30;
  s32 v31;
  s32 klass_high;
  s32 v34;
  s32 v36;
  s32 v37;
  s32 v39;
  s32 v40;

  size = DestTextIDList->_size;
  v5 = DestTextIDList->_version + 1;
  DestTextIDList->_size = 0;
  DestTextIDList->_version = v5;
  if (size >= 1)
  {
    Clear(DestTextIDList->_items, 0, size, 0);
  }
  DestDrawText = 0;
  for (i = 0; ; ++i)
  {
    if (i > GBWK->GameFileInfo->chapter)
      break;
    DestData_28574400 = GetDestData_28574400(DestListTbl, i, 0);
    if (DestData_28574400->_size >= 1)
    {
      v10 = DestData_28574400;
      for (j = 0; j < v10->_size; ++j)
      {
        Item = _get_Item(v10, j);
        chapter = GBWK->GameFileInfo->chapter;
        if (i < chapter)
          goto LABEL_22;
        klass = Item[1].klass;
        if (!fldDestBitChk(chapter, klass))
          continue;
        if (!ChapterThreeDestChack(j))
          continue;
        if (!ChapterNineDestChack(j))
          continue;
        v30 = Item[1].klass;
        v31 = GBWK->GameFileInfo->chapter;
        if (fldDestBitChk(v31, v30))
        {
          klass_high = HIDWORD(Item[1].klass);
          v34 = GBWK->GameFileInfo->chapter;
          if (!fldDestBitChk(v34, klass_high))
            goto LABEL_22;
        }
        v36 = Item[1].klass;
        v37 = GBWK->GameFileInfo->chapter;
        if (!fldDestBitChk(v37, v36))
          continue;
        v39 = HIDWORD(Item[1].klass);
        v40 = GBWK->GameFileInfo->chapter;
        if (fldDestBitChk(v40, v39))
          goto LABEL_22;
        goto LABEL_9002;
        if (fldDestBitChk(v40, v39))
        {
LABEL_22:
          if (!_Contains(DestTextIDList, Item[1].monitor))
          {
            monitor = Item[1].monitor;
            v18 = DestTextIDList;
            v19 = Method_System_Collections_Generic_List_string__Add__;
            v20 = v18->_size;
            ++v18->_version;
            items = v18->_items;
            if ((u32)v20 >= LODWORD(items->max_length))
            {
              _AddWithResize(v18, monitor, *(const MethodInfo_2DFC660 **)(*(u64 *)(v19[4] + 192) + 112));
            }
            else
            {
              v18->_size = v20 + 1;
              v22 = &items->obj.klass + v20;
              v22[4] = monitor;
            }
          }
        }
LABEL_9002:
      }
    }
  }
}

// 0x1bece40
bool ChapterThreeDestChack(s32 _num) {
  s32 chapter;
  s32 v9;
  s32 v11;
  s32 v13;
  s32 v15;
  s32 v17;
  s32 v19;
  s32 v21;
  s32 v23;
  s32 v25;
  s32 v27;
  s32 v29;
  s32 v31;
  s32 v33;
  s32 v35;
  s32 v37;
  s32 v39;
  s32 v41;
  s32 v43;

  if (GBWK->GameFileInfo->chapter != 3)
    return 1;
  chapter = 3;
  if (!fldDestBitChk(chapter, 5))
    return 1;
  if (CHAPTER3_STORNSTART_NO > num)
    return 1;
  if (CHAPTER3_STORNFINISH_NO < num)
    return 1;
  v9 = GBWK->GameFileInfo->chapter;
  if (!fldDestBitChk(v9, 6))
  {
    v11 = GBWK->GameFileInfo->chapter;
    if (!fldDestBitChk(v11, 8))
    {
      v13 = GBWK->GameFileInfo->chapter;
      if (!fldDestBitChk(v13, 10))
        goto LABEL_115;
    }
  }
  v15 = GBWK->GameFileInfo->chapter;
  if (!fldDestBitChk(v15, 6))
  {
    v17 = GBWK->GameFileInfo->chapter;
    if (!fldDestBitChk(v17, 8))
    {
      v19 = GBWK->GameFileInfo->chapter;
      if (!fldDestBitChk(v19, 10))
        goto LABEL_115;
    }
  }
  v21 = GBWK->GameFileInfo->chapter;
  if (!fldDestBitChk(v21, 6))
  {
    v23 = GBWK->GameFileInfo->chapter;
    if (!fldDestBitChk(v23, 8))
    {
      v25 = GBWK->GameFileInfo->chapter;
      if (!fldDestBitChk(v25, 10))
      {
LABEL_115:
        if (DestDrawText)
          return 0;
        goto LABEL_122;
      }
    }
  }
  v27 = GBWK->GameFileInfo->chapter;
  if (!fldDestBitChk(v27, 6))
    goto LABEL_110;
  v29 = GBWK->GameFileInfo->chapter;
  if (fldDestBitChk(v29, 8))
    goto LABEL_110;
  v31 = GBWK->GameFileInfo->chapter;
  if (fldDestBitChk(v31, 10))
  {
LABEL_110:
    v33 = GBWK->GameFileInfo->chapter;
    if (fldDestBitChk(v33, 6))
      goto LABEL_128;
    v35 = GBWK->GameFileInfo->chapter;
    if (!fldDestBitChk(v35, 8))
      goto LABEL_128;
    v37 = GBWK->GameFileInfo->chapter;
    if (fldDestBitChk(v37, 10))
    {
LABEL_128:
      v39 = GBWK->GameFileInfo->chapter;
      if (fldDestBitChk(v39, 6))
        return 1;
      v41 = GBWK->GameFileInfo->chapter;
      if (fldDestBitChk(v41, 8))
        return 1;
      v43 = GBWK->GameFileInfo->chapter;
      if (!fldDestBitChk(v43, 10))
        return 1;
    }
  }
  if (DestDrawText)
    return 0;
  if (CHAPTER3_STORN_ONE_NO >= num)
    return 1;
LABEL_122:
  DestDrawText = 1;
  return 1;
}

// 0x1bed5c0
bool ChapterNineDestChack(s32 _num) {
  s32 fieldID;
  s32 chapter;
  s32 v9;
  s32 v11;
  bool v12;
  s32 v16;
  bool v17;
  s32 v20;
  bool v21;

  if (GBWK->GameFileInfo->chapter != 9)
    return 1;
  fieldID = fldGb->fieldID;
  if (fieldID != 1)
  {
    if (fieldID != 6)
      goto LABEL_18;
  }
  chapter = GBWK->GameFileInfo->chapter;
  if (fldDestBitChk(chapter, 16))
    goto LABEL_18;
  return CHAPTER9_FIELD25_NO > num;
LABEL_18:
  if (CHAPTER9_ALLGET_NO == num)
    return 1;
  v9 = fldGb->fieldID;
  if (v9 == 25)
    goto LABEL_28;
  v9 = fldGb->fieldID;
  if (v9 == 22)
  {
    v16 = GBWK->GameFileInfo->chapter;
    v17 = fldDestBitChk(v16, 10);
    if (!v17)
    {
      if (CHAPTER9_FIELD22_NO > num)
        return 0;
      return CHAPTER9_FIELD24_NO > num;
    }
  }
  else
  {
    v9 = fldGb->fieldID;
    if (v9 != 24)
      return 1;
    v20 = GBWK->GameFileInfo->chapter;
    v21 = fldDestBitChk(v20, 15);
    if (!v21)
    {
      if (CHAPTER9_FIELD24_NO > num)
        return 0;
      return CHAPTER9_ALLGET_NO > num;
    }
  }
LABEL_64:
  return CHAPTER9_FIELD25_NO > num;
LABEL_28:
  v11 = GBWK->GameFileInfo->chapter;
  v12 = fldDestBitChk(v11, 7);
  if (v12)
    goto LABEL_64;
  if (CHAPTER9_FIELD25_NO <= num)
  {
    if (CHAPTER9_FIELD22_NO > num)
      return 1;
  }
  return 0;
}

// 0x1beda70
static void Destroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  struct DitectiveBook *v5;
  Il2CppObject *v6;
  DitectiveBook *v8;
  u32 *monitor;
  dds3ProcessID_t *v10;
  s32 i;
  s64 j;
  Il2CppClass **v15;
  QUEST_TEXT_CLASS *QUESTPAGE_local;
  s64 v19;
  s32 size;
  s32 v22;
  s32 v25;
  s32 v26;
  s32 v30;
  s32 v31;
  s64 k;
  Il2CppClass **v34;
  u32 v36;
  DITECTIVEBOOK_CLASS *BOOKPAGE_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  {
    goto LABEL_5;
  }
  v6 = ProcessData;
  dds3KillProcessName("DitectiveBook_Draw", 0);
  dds3KillProcessName("DitectiveBook_Update", 0);
  monitor = v6[1].monitor;
  LODWORD(v6[1].klass) &= 0xFFFFFFC0;
  v10 = id;
  for (i = monitor[4]; i; monitor[4] = i)
  {
    i = monitor[4];
    if (!i)
      break;
    v19 = *(u64 *)(*(u64 *)(*((u64 *)monitor + 3) + 8 * --i + 32) + 32);
    if (v19)
    {
      v8 = (*(v19 + 24))(*(u64 *)(v19 + 64), v10, *(u64 *)(v19 + 40));
      i = monitor[4] - 1;
    }
  }
  MenuProcessEnd();
  if (QuestFlag)
  {
    for (j = 0; ; ++j)
    {
      QUESTPAGE_local = QUESTPAGE;
      if (j >= SLODWORD(QUESTPAGE_local->max_length))
        break;
      QUESTPAGE_local = QUESTPAGE;
      v15 = &QUESTPAGE_local->obj.klass + j;
      HIDWORD(v15[4]->_1.declaringType) = 0;
    }
    QUESTPAGE = 0;
  }
  else
  {
    size = DestNowList->_size;
    v22 = DestNowList->_version + 1;
    DestNowList->_size = 0;
    DestNowList->_version = v22;
    if (size >= 1)
    {
      Clear(DestNowList->_items, 0, size, 0);
    }
    DestNowList = 0;
    v25 = DestTextList->_size;
    v26 = DestTextList->_version + 1;
    DestTextList->_size = 0;
    DestTextList->_version = v26;
    if (v25 >= 1)
    {
      Clear(DestTextList->_items, 0, v25, 0);
    }
    DestTextList = 0;
    DestListTbl = 0;
    v30 = DestTextIDList->_size;
    v31 = DestTextIDList->_version + 1;
    DestTextIDList->_size = 0;
    DestTextIDList->_version = v31;
    if (v30 >= 1)
    {
      Clear(DestTextIDList->_items, 0, v30, 0);
    }
    DestTextIDList = 0;
    for (k = 0; ; ++k)
    {
      BOOKPAGE_local = BOOKPAGE;
      if (k >= SLODWORD(BOOKPAGE->max_length))
        break;
      if (!v36)
      {
        BOOKPAGE_local = BOOKPAGE;
      }
      v34 = &BOOKPAGE_local->obj.klass + k;
      v34[4]->_1.this_arg.bits = 0;
    }
    BOOKPAGE = 0;
  }
LABEL_5:
  GlobalPID = 0;
  v5 = ((char *)v5 + 80);
  HIDWORD(bookSprTable04) = 0;
}

// 0x1bee150
dds3ProcessID_t *DebugProcessStart(void) {
  dds3ProcessID_t *v1;
  Il2CppMethodPointer virtualMethodPointer;
  Il2CppObject *v4;
  dds3ProcessFunc_t v5;
  shutdownfuncDelegate v6;
  dds3ProcessID_t *started;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  virtualMethodPointer = *((const MethodInfo *)DitectiveBook + 2).virtualMethodPointer;
  *((u8 *)virtualMethodPointer + 136) = 0;
  *((u32 *)virtualMethodPointer + 36) = -1;
  v4 = Init();
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_DitectiveBook_Load0Process__, 0);
  v6 = Allocate(shutdownfuncDelegate);
  _ctor(v6, 0, Method_Project_DitectiveBook_Destroy__, 0);
  started = dds3StartProcess("DitectiveBook_Calc", 1023, 0, 1, v5, v6, v4);
  GlobalPID = started;
  gCallFromMenu = 0;
  return started;
}

// 0x1bee310
dds3ProcessID_t *ProcessStart(s32 _flag) {
  dds3ProcessID_t *v3;
  Il2CppMethodPointer virtualMethodPointer;
  Il2CppObject *v6;
  dds3ProcessFunc_t v7;
  shutdownfuncDelegate v8;
  dds3ProcessID_t *started;

  v3 = Allocate(dds3ProcessID_t);
  _ctor(v3, 0);
  virtualMethodPointer = *((const MethodInfo *)DitectiveBook + 2).virtualMethodPointer;
  *((u32 *)virtualMethodPointer + 36) = flag;
  *((u8 *)virtualMethodPointer + 136) = 0;
  v6 = Init();
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_DitectiveBook_Load0Process__, 0);
  v8 = Allocate(shutdownfuncDelegate);
  _ctor(v8, 0, Method_Project_DitectiveBook_Destroy__, 0);
  started = dds3StartProcess("DitectiveBook_Calc", 1023, 0, 1, v7, v8, v6);
  GlobalPID = started;
  gCallFromMenu = 0;
  return started;
}

// 0x1bee4d0
void ProcessEnd(void) {
  UnityEngine_SceneManagement_Scene_o v5;
  char *v10;
  char *v11;
  char *v12;
  char *v13;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  UnityEngine_SceneManagement_Scene_o v26;

  v26.m_Handle = 0;
  dds3KillProcessName("DitectiveBook_Draw", 0);
  dds3KillProcessName("DitectiveBook_Update", 0);
  if (!DLCEXIST)
  {
    goto LABEL_8;
  }
  Remove_30362592("DBOOK_DLC_ALL_TITLE", 0);
  v10 = "new_oni";
  v11 = "new_title";
  v12 = "new_dbook";
  v13 = "new_devil";
  v14 = "new_glasses";
  v15 = "new_skill";
  v16 = "new_item";
  v17 = "new_crm";
  DlcTextDestroy("new_exp", "DBOOK_DLC_DE1_TEXT", "DBOOK_DLC_DE1_TITLE");
  DlcTextDestroy(v10, "DBOOK_DLC_DZ1_TEXT", "DBOOK_DLC_DZ1_TITLE");
  DlcTextDestroy(v11, "DBOOK_DLC_DS1_TEXT", "DBOOK_DLC_DS1_TITLE");
  DlcTextDestroy(v12, "DBOOK_DLC_DB1_TEXT", "DBOOK_DLC_DB1_TITLE");
  DlcTextDestroy(v13, "DBOOK_DLC_DD1_TEXT", "DBOOK_DLC_DD1_TITLE");
  DlcTextDestroy(v14, "DBOOK_DLC_RM1_TEXT", "DBOOK_DLC_RM1_TITLE");
  DlcTextDestroy(v15, "DBOOK_DLC_DI1_TEXT", "DBOOK_DLC_DI1_TITLE");
  DlcTextDestroy(v16, "DBOOK_DLC_DI2_TEXT", "DBOOK_DLC_DI2_TITLE");
  DlcTextDestroy(v17, "DBOOK_DLC_DI3_TEXT", "DBOOK_DLC_DI3_TITLE");
  DLCEXIST = 0;
LABEL_8:
  v26.m_Handle = GetSceneByName(book_scene_name, 0).m_Handle;
  if (!!IsValid((UnityEngine_SceneManagement_Scene_o)&v26, 0))
  {
    v5.m_Handle = v26.m_Handle;
    UnloadSceneAsync_61083440(v5, 0);
    book_scene_name = 0;
    scene_asyncLoad = 0;
  }
  sdfMemRelease();
}

// 0x1beeb20
void ReturnReadFlagData(void) {
  s64 v2;
  char *v3;
  s64 v4;
  s64 v5;
  s64 v6;
  char v7;
  bool *dbook_readFlag;

  if (DebugProcessFlag)
    return;
  v2 = 0;
  while (1)
  {
    if (v2 >= SLODWORD(DBOOK_READ_FLAG->max_length))
      break;
    dbook_readFlag = GBWK->dbook_readFlag;
    v3 = (char *)dbook_readFlag + v2;
    v4 = (s64)GBWK->dbook_updateFlag + 4 * v2;
    v5 = (s64)DBOOK_READ_FLAG + 8 * v2++;
    v6 = *(u64 *)(v5 + 32);
    v7 = *(u8 *)(v6 + 16);
    LODWORD(v6) = *(u32 *)(v6 + 20);
    v3[32] = v7;
    *(u32 *)(v4 + 32) = v6;
  }
  DBOOK_READ_FLAG = 0;
}

// 0x1beecb0
s32 ProcessCheck(void) {
  return dds3SearchProcessName("DitectiveBook_Calc") != 0;
}

// 0x1beea30
static void DlcTextDestroy(char *DLCname, char *AssetNameText, char *AssetNameTitle) {
  if (Exists(DLCname))
    goto LABEL_4;
  return;
  if (Exists(DLCname))
  {
LABEL_4:
    Remove_30362592(AssetNameText, 0);
    JUMPOUT(0x1CF4BE0);
  }
}

// 0x1beed30
static s32 RootInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bool v13;
  char *v17;
  char *LocalizeText;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  dds3GetProcessData(g_mainPID);
  dds3GetProcessData(g_mainPID);
  if (cmpProcessCheck())
  {
    goto LABEL_20;
  }
  v13 = evtBitCheck(42);
  if (!v13)
  {
    v17 = s_szModelName[1];
    goto LABEL_40;
  }
  v17 = s_szModelName[0];
LABEL_40:
  LocalizeText = GetLocalizeText(v17, 1);
  SetKanban(bookUI, LocalizeText, 0);
LABEL_20:
  if (QuestFlag)
    return 1;
  HIDWORD(ProcessData[14].monitor) = DestTextIDList->_size - 1;
  return 1;
}

// 0x1bef2e0
static s32 RootDestroy(dds3ProcessID_t *PID) {
  ProcessEnd();
  return 1;
}

// 0x1bef360
static dds3ProcessFunc_t RootCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t result;
  dds3ProcessFunc_t v16;
  dds3ProcessFunc_t v17;
  intptr_t *v18;
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
  v7 = id;
  result = SeqChange(monitor, &ProcessData[2], 0, v7);
  if (!result)
  {
    SelectIndex = GetSelectIndex();
    if (GetSelectIndex() != -1)
    {
      LODWORD(ProcessData[8].klass) = 0;
      return 0;
    }
    if (cmpProcessCheck())
    {
LABEL_19:
      MenuAnimSetCtrl(bookUI, 1, 0);
      PANELMAIN_SetAnim_new(bookUI, 2, 0);
      DeleteKanban(bookUI, 0);
      UIDestroy(bookUI, 0);
      v16 = Allocate(dds3ProcessFunc_t);
      v17 = v16;
      if (QuestFlag)
        v18 = &Method_Project_DitectiveBook_QuestEndProcess__;
      else
        v18 = &Method_Project_DitectiveBook_EndProcess__;
      _ctor(v16, 0, *v18, 0);
      return v17;
    }
    backObjSetAnim(bookUI, 2, 0);
    goto LABEL_19;
  }
  return result;
}

// 0x1befab0
static dds3ProcessFunc_t RootDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SakuraEffectDraw();
  v5 = id;
  if (!v5)
    return 0;
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    return 0;
  if (((u32)name & 0x200000) != 0)
    return (dds3ProcessFunc_t)klass->_1.this_arg.data;
  if (((u8)name & 1) == 0)
    return 0;
  klass->_1.name = ((u64)name | 0x400000);
  (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v5, *((u64 *)klass->_1.this_arg.data + 5));
  ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
  return 0;
}

// 0x1befc80
static dds3ProcessFunc_t RootUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v7 = id;
  return SeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1befda0
void DrawPanelMessage_IDNEXT(s32 page) {
  Il2CppObject *Item;
  char *v9;
  char *LocalizeText;
  Il2CppObject *v11;
  char *v12;
  char *v13;

  op_Inequality(fldUI, 0, 0);
  Item = _get_Item(DestTextIDList, page);
  v9 = Concat_54766928("DBOOK_", Item, 0);
  LocalizeText = GetLocalizeText(v9, 1);
  v11 = _get_Item(DestTextIDList, page);
  v12 = Concat_54766928("DBOOK_GOUTOMSG_", v11, 0);
  v13 = GetLocalizeText(v12, 1);
  PANEL_TitleTextSet(bookUI, LocalizeText, 0);
  PANEL02_SetMessage(bookUI, v13, 0, 0, 0, 0);
}

// 0x1befff0
void DrawPanelMessage_IDFUTURE(void) {
  char *v1;
  char *LocalizeText;

  v1 = " ";
  LocalizeText = GetLocalizeText("DBOOK_TITLETEXT_L0007", 1);
  PANEL02_SetTitleText(bookUI, LocalizeText, 0);
  PANEL02_SetMessage(bookUI, v1, 0, 0, 0, 0);
}

// 0x1bf00f0
void DrawPANELMessage(DITECTIVEBOOK_CLASS *d_book) {
  s32 *upDateTextFlag;
  s64 v4;
  s64 v5;
  u32 v6;
  char *v9;
  char *LocalizeText;
  void *v12;
  char *v13;
  char *v14;
  s32 v15;
  char *v16;
  s32 v17;
  char *v18;
  char *v19;
  char *v20;
  s32 subID;
  char *v23;
  char *v24;
  char *v25;
  s32 v26;

  if (evtBitCheck(d_book->upDateTextFlag[0]))
  {
    upDateTextFlag = d_book->upDateTextFlag;
    if (SLODWORD(upDateTextFlag->max_length) < 1)
    {
      v5 = -1;
      v6 = d_book->type - 1;
    }
    else
    {
      v4 = 0;
      do
      {
        if (!evtBitCheck(upDateTextFlag[v4]))
          break;
        upDateTextFlag = d_book->upDateTextFlag;
        ++v4;
      }
      while (v4 < SLODWORD(upDateTextFlag->max_length));
      v5 = (s32)v4 - 1;
      v6 = d_book->type - 1;
      if (v6 > 6)
        return;
    }
    switch (v6)
    {
      case 0u:
      case 1u:
        v9 = d_book->upDateText[v5];
        LocalizeText = GetLocalizeText(v9, 1);
        PANEL02_SetMessage(bookUI, LocalizeText, d_book->upDateText[v5], 0, 0, 0);
        break;
      case 5u:
        v12 = bookUI;
        v13 = d_book->upDateText[v5];
        v14 = GetLocalizeText(v13, 1);
        PANELFILE_SetMessage(v12, v14, 0);
        break;
      case 6u:
        if (d_book->subID >= 1)
        {
          v15 = 0;
          v16 = "";
          do
          {
            v17 = v15 + 1;
            v26 = v15 + 1;
            v18 = ToString((s32)&v26, 0);
            v19 = Concat_54831728("TIPS_PAGE", v18, d_book->upDateText[v5], 0);
            v20 = GetLocalizeText(v19, 1);
            v16 = Concat_54766928(v16, v20, 0);
            PANEL02_SetMessage(bookUI, v16, v19, 0, 0, 0);
            subID = d_book->subID;
            if (v15 < subID - 1)
            {
              v23 = Concat_54766928(v16, "\n", 0);
              v24 = Concat_54766928(v23, "\n", 0);
              v25 = Concat_54766928(v24, "\n", 0);
              subID = d_book->subID;
              v16 = v25;
            }
            ++v15;
          }
          while (v17 < subID);
        }
        break;
      default:
        return;
    }
  }
}

// 0x1bf0470
void DrawQUESTPANELMessage(QUEST_TEXT_CLASS *_quest, bool _flag) {
  char *LocalizeText;
  void *v8;
  char *v9;
  s32 *upDateTextFlag;
  s64 v11;
  s64 v12;
  s32 type;
  void *v15;
  char *v16;
  void *v18;
  char *v19;
  char *v20;
  void *v22;
  char *v23;
  char *v24;

  if (!evtBitCheck(quest->upDateTextFlag[0]))
    return;
  if (GBWK->GameFileInfo->chapter == 9)
  {
    if (quest->StopFlag && !flag)
    {
      LocalizeText = GetLocalizeText("QUEST_MAINTEXT01_L0000", 1);
      v8 = bookUI;
      v9 = 0;
      goto LABEL_27;
    }
  }
  upDateTextFlag = quest->upDateTextFlag;
  if (SLODWORD(upDateTextFlag->max_length) < 1)
  {
    v12 = -1;
    type = quest->type;
    if (type != 6)
      goto LABEL_20;
LABEL_30:
    v18 = bookUI;
    v19 = quest->upDateText[v12];
    v20 = GetLocalizeText(v19, 1);
    PANELFILE_SetMessage(v18, v20, 0);
    return;
  }
  v11 = 0;
  do
  {
    if (!evtBitCheck(upDateTextFlag[v11]))
      break;
    upDateTextFlag = quest->upDateTextFlag;
    ++v11;
  }
  while (v11 < SLODWORD(upDateTextFlag->max_length));
  v12 = (s32)v11 - 1;
  type = quest->type;
  if (type == 6)
    goto LABEL_30;
LABEL_20:
  if (type == 2)
  {
    v22 = bookUI;
    v23 = quest->upDateText[v12];
    v24 = GetLocalizeText(v23, 1);
    PANEL02_SetMessage(v22, v24, quest->upDateText[v12], 1, quest->Quest_ID, 0);
  }
  else if (type == 1)
  {
    v15 = bookUI;
    v16 = quest->upDateText[v12];
    LocalizeText = GetLocalizeText(v16, 1);
    v8 = v15;
    v9 = quest->upDateText[v12];
LABEL_27:
    PANEL02_SetMessage(v8, LocalizeText, v9, 0, 0, 0);
  }
}

// 0x1bf07b0
void CheckNextUpdate(void) {
  s32 UPDATE_FLAG;
  const MethodInfo_2DFC320 *v7;
  void *v8;
  DBOOK_READ_FLAG_CLASS *v9;

  if (DestNowList->_size < 1)
    return;
  UPDATE_FLAG = DBOOK_READ_FLAG[15]->UPDATE_FLAG;
  if (UPDATE_FLAG != LODWORD(_get_Item(DestNowList, 0)[1].klass))
  {
    v7 = Method_System_Collections_Generic_List_DestData_t__get_Item__;
    v8 = DestNowList;
    v9 = DBOOK_READ_FLAG[15];
    v9->READ_FLAG = 0;
    v9->UPDATE_FLAG = (s32)_get_Item(v8, 0, v7)[1].klass;
  }
}

// 0x1bf08f0
void CheckTextUpdate(s32 ID, s32 parentID) {
  s64 v6;
  s32 v7;
  s32 *upDateTextFlag;
  bool v9;
  DBOOK_READ_FLAG_CLASS *v11;
  DBOOK_READ_FLAG_CLASS *v12;

  if (!BOOKPAGE[ID]->type)
    return;
  v6 = 9;
  while (1)
  {
    v7 = v6 - 8;
    upDateTextFlag = BOOKPAGE[ID]->upDateTextFlag;
    if (v6 - 8 >= SLODWORD(upDateTextFlag->max_length))
      break;
    upDateTextFlag = BOOKPAGE[ID]->upDateTextFlag;
    v9 = evtBitCheck(*((u32 *)&upDateTextFlag->obj.klass + v6));
    if (!v9)
    {
      v11 = DBOOK_READ_FLAG[ID];
      if (v11->UPDATE_FLAG < v7)
      {
        v11 = DBOOK_READ_FLAG[ID];
        v11->READ_FLAG = 0;
        v11->UPDATE_FLAG = v7;
        v12 = DBOOK_READ_FLAG[parentID];
        if (v12->READ_FLAG)
        {
          v12->READ_FLAG = 0;
        }
      }
      return;
    }
    ++v6;
  }
}

// 0x1bf0ae0
void CheckAllParentReadFlag(void) {
  s64 i;
  s64 v4;
  s64 v7;

  for (i = 1; ; ++i)
  {
    if (i >= SLODWORD(BOOKPAGE->max_length))
      break;
    if (!BOOKPAGE[i]->childs)
      continue;
    v4 = 0;
    while (1)
    {
      if (v4 >= BOOKPAGE[i]->childs)
        break;
      v7 = (s64)BOOKPAGE[i]->childID + 4 * v4++;
      if (!DBOOK_READ_FLAG[*(s32 *)(v7 + 32)]->READ_FLAG)
      {
        DBOOK_READ_FLAG[i]->READ_FLAG = 0;
        break;
      }
    }
  }
}

// 0x1bf0c40
void CheckParentReadFlag(s32 ID) {
  s64 v4;
  s64 v5;
  DITECTIVEBOOK_CLASS *v7;
  s64 v10;

  while (2)
  {
    v4 = 0;
    v5 = ID;
    while (1)
    {
      v7 = BOOKPAGE[ID];
      if (v4 >= v7->childs)
        break;
      v7 = BOOKPAGE[ID];
      if (!DBOOK_READ_FLAG[v7->childID[v4]]->READ_FLAG)
      {
        DBOOK_READ_FLAG[ID]->READ_FLAG = 0;
        break;
      }
      ++v4;
    }
    if (BOOKPAGE[ID]->childs == (u32)v4)
    {
      v10 = (s64)DBOOK_READ_FLAG + 8 * ID;
      ID = MenuParentID[ID];
      *(u8 *)(*(u64 *)(v10 + 32) + 16) = 1;
      if (ID)
      {
        ID = MenuParentID[v5];
        continue;
      }
    }
    break;
  }
}

// 0x1bf0dd0
void AccessReadFlag(s32 accessID) {
  s64 v2;
  DBOOK_READ_FLAG_CLASS *v8;
  DBOOK_READ_FLAG_CLASS *v10;
  u32 v12;
  s32 v14;

  LODWORD(v2) = accessID;
  if ((u32)v2 == 1)
  {
    v8 = DBOOK_READ_FLAG[1];
    v8->READ_FLAG = 1;
    if (DestNowList->_size >= 1)
    {
      v10 = DBOOK_READ_FLAG;
      v8 = v10[1];
      v8->UPDATE_FLAG = (s32)_get_Item(DestNowList, 0)[1].klass;
    }
    return;
  }
  if (!DBOOK_READ_FLAG[(s32)v2]->READ_FLAG)
  {
    if (v12)
    {
      v2 = (s32)v2;
      bookUI->PANELREADFLAG = 0;
LABEL_19:
      v14 = MenuParentID[v2];
      DBOOK_READ_FLAG[v2]->READ_FLAG = 1;
      CheckParentReadFlag(v14);
      return;
    }
    else
    {
      v2 = (s32)v2;
      bookUI->PANELREADFLAG = 0;
      goto LABEL_19;
    }
    goto LABEL_19;
  }
  bookUI->PANELREADFLAG = 1;
}

// 0x1bf0fb0
dds3ProcessFunc_t RootWaitCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqUnit_t *v6;
  bookSeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v9;
  bookSeqUnit_t *v13;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v8 = id;
  v9 = SeqChange(monitor, v6, 0, v8);
  if (v9)
    return v9;
  if (!QuestFlag)
  {
    goto LABEL_16;
  }
  if (!fldJmsQuestSceneLoadWait())
    return v9;
  fldJmsQuestSceneLoadLast();
LABEL_16:
  v13 = bookSeqUnit[1];
  v6 = v13;
  bookSeqUnit[1]->Stat = LOWORD(bookSeqUnit[1]->Stat);
  if (cmpProcessCheck())
    return v9;
  backObjSetAnim(bookUI, 1, 0);
  return 0;
}

// 0x1bf1260
dds3ProcessFunc_t RootWaitDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v5;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessFunc_t data;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = (dds3ProcessFunc_t)id;
  goto LABEL_11;
LABEL_19:
  SakuraEffectDraw();
  return v5;
LABEL_11:
  if (!v5)
    goto LABEL_19;
  klass = ProcessData[2].klass;
  if (!klass)
    goto LABEL_16;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    goto LABEL_16;
  if (((u32)name & 0x200000) != 0)
  {
    data = (dds3ProcessFunc_t)klass->_1.this_arg.data;
    SakuraEffectDraw();
    return data;
  }
  else
  {
    if (((u8)name & 1) == 0)
    {
LABEL_16:
      SakuraEffectDraw();
      return 0;
    }
    klass->_1.name = ((u64)name | 0x400000);
    v11 = (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v5, *((u64 *)klass->_1.this_arg.data + 5));
    ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
    SakuraEffectDraw();
    return 0;
  }
}

// 0x1bf1450
dds3ProcessFunc_t RootWaitUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v7 = id;
  return SeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1bf1570
dds3ProcessFunc_t TipsWaitCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqUnit_t *v6;
  bookSeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v9;
  bookSeqUnit_t *v13;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v8 = id;
  v9 = SeqChange(monitor, v6, 0, v8);
  if (v9)
    return v9;
  v13 = bookSeqUnit[3];
  v6 = v13;
  bookSeqUnit[3]->Stat = LOWORD(bookSeqUnit[3]->Stat);
  if (!!cmpProcessCheck())
    return v9;
  backObjSetAnim(bookUI, 1, 0);
  return 0;
}

// 0x1bf1770
dds3ProcessFunc_t TipsWaitDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SakuraEffectDraw();
  v5 = id;
  if (!v5)
    return 0;
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    return 0;
  if (((u32)name & 0x200000) != 0)
    return (dds3ProcessFunc_t)klass->_1.this_arg.data;
  if (((u8)name & 1) == 0)
    return 0;
  klass->_1.name = ((u64)name | 0x400000);
  (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v5, *((u64 *)klass->_1.this_arg.data + 5));
  ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
  return 0;
}

// 0x1bf1940
dds3ProcessFunc_t TipsWaitUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v7 = id;
  return SeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1bf1a60
static s32 TipsInit(dds3ProcessID_t *PID) {
  bool v6;
  char *v11;
  char *LocalizeText;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  if (!cmpProcessCheck())
  {
    v6 = evtBitCheck(42);
    if (v6)
    {
      v11 = s_szModelName[0];
    }
    else
    {
      v11 = s_szModelName[1];
    }
    LocalizeText = GetLocalizeText(v11, 1);
    SetKanban(bookUI, LocalizeText, 0);
  }
  tipsTIPSStart_ALL();
  return 1;
}

// 0x1bf1ca0
static s32 TipsDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  ProcessEnd();
  if (!ProcessData)
  LODWORD(ProcessData[15].klass) = 0;
  return 1;
}

// 0x1bf1da0
static dds3ProcessFunc_t TipsCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqUnit_t *v6;
  bookSeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v9;
  dds3ProcessFunc_t v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v8 = id;
  v9 = SeqChange(monitor, v6, 0, v8);
  if (v9)
    return v9;
  v9 = 0;
  if (!!tipsProcessCheck_tipsAll())
    return v9;
  if (!cmpProcessCheck())
  {
    backObjSetAnim(bookUI, 2, 0);
  }
  v12 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v12, 0, Method_Project_DitectiveBook_EndProcess__, 0);
  return v12;
}

// 0x1bf1fd0
static dds3ProcessFunc_t TipsDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SakuraEffectDraw();
  v5 = id;
  if (!v5)
    return 0;
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    return 0;
  if (((u32)name & 0x200000) != 0)
    return (dds3ProcessFunc_t)klass->_1.this_arg.data;
  if (((u8)name & 1) == 0)
    return 0;
  klass->_1.name = ((u64)name | 0x400000);
  (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v5, *((u64 *)klass->_1.this_arg.data + 5));
  ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
  return 0;
}

// 0x1bf21a0
static dds3ProcessFunc_t TipsUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v7 = id;
  return SeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1bf22c0
static dds3ProcessFunc_t PANELFILECalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v9;
  f32 *v11;
  f32 v12;
  u32 *v14;
  u32 *v17;
  s32 v18;
  bool v19;
  s32 v22;
  s32 v23;
  u32 *v24;
  f32 *v27;
  f32 v28;
  s32 v30;
  f32 *v32;
  f32 v33;
  s32 v35;
  u32 *v37;
  f32 *v40;
  f32 v41;
  s32 v43;
  f32 *v45;
  f32 v46;
  s32 v48;
  u32 *v49;
  s32 v52;
  u32 *v55;
  s64 p_byval_arg;
  bookSeqUnit_t *bookSeqUnit_local;
  s32 v59;
  s64 v60;
  Il2CppClass **v61;
  Il2CppClass *v62;
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
  v7 = id;
  v9 = SeqChange(monitor, &ProcessData[2], 0, v7);
  if (!v9)
  {
    v11 = ProcessData[11].monitor;
    v12 = v11[8];
    if (*((u32 *)v11 + 5))
    {
      if (v12 == 0.0)
      {
        if (*((u32 *)v11 + 7))
        {
          PANELFILE_TextScrollReset(bookUI, 0);
          v14 = ProcessData[11].monitor;
          v14[5] = 0;
          v14[7] = 0;
          return v9;
        }
        if (*((u32 *)v11 + 6))
        {
          PANELFILE_TextScrollReset(bookUI, 0);
          v55 = ProcessData[11].monitor;
          v55[5] = 0;
          v55[6] = 0;
          return v9;
        }
        p_byval_arg = &ProcessData[14].klass->_1.byval_arg;
        bookSeqUnit_local = bookSeqUnit;
        *(u32 *)(p_byval_arg + 4 * SHIDWORD(ProcessData[13].monitor)) = 1;
        v59 = HIDWORD(ProcessData[13].monitor) - 1;
        HIDWORD(ProcessData[13].monitor) = v59;
        v60 = 4 * v59;
        LODWORD(ProcessData[14].monitor) = *(u32 *)(p_byval_arg + v60);
        v61 = &bookSeqUnit_local->obj.klass + *(s32 *)(p_byval_arg + v60);
        v62 = v61[4];
        ProcessData[2].klass = v62;
        v61[4]->_1.name = (LOWORD(v61[4]->_1.name) | 0x20000);
        v17 = ProcessData[11].monitor;
        v18 = ProcessData[14].monitor;
        goto LABEL_39;
      }
      if (v12 <= 0.0)
      {
        if (v12 >= 0.0)
          goto LABEL_37;
      }
      else
      {
        v12 = v12 + -0.0625;
      }
      if (v12 < 0.0)
        v12 = 0.0;
      v11[8] = v12;
LABEL_37:
      v17 = ProcessData[11].monitor;
      v18 = ProcessData[14].monitor;
      goto LABEL_39;
    }
    if (v12 >= 1.0)
    {
      if (v12 <= 1.0)
        goto LABEL_25;
    }
    else
    {
      v12 = v12 + 0.0625;
    }
    if (v12 > 1.0)
      v12 = 1.0;
    v11[8] = v12;
LABEL_25:
    if (LODWORD(ProcessData[15].klass) == 4 && CHECK_TRIG(4097, 1))
    {
      *((u32 *)ProcessData[11].monitor + 5) = 1;
      PANELMAIN_SetAnim(bookUI, 2, 0);
      SE(1);
      v17 = ProcessData[11].monitor;
      v18 = ProcessData[14].monitor;
LABEL_39:
      v19 = CheckPageEnable(v18, -1) == 0;
      v22 = v19;
      v23 = ProcessData[14].monitor;
      v17[9] = v22;
      v24 = ProcessData[11].monitor;
      v24[11] = CheckPageEnable(v23, 1) == 0;
      if (*((u32 *)ProcessData[11].monitor + 9))
      {
        PANELFILE_ArrowAnim_L(bookUI, 2, 0);
        v27 = ProcessData[11].monitor;
        v28 = v27[10];
        if (v28 <= 0.0)
        {
          if (v28 >= 0.0)
            goto LABEL_61;
        }
        else
        {
          v28 = v28 + -0.0625;
        }
        if (v28 < 0.0)
          v28 = 0.0;
      }
      else
      {
        PANELFILE_ArrowAnim_L(bookUI, 1, 0);
        v27 = ProcessData[11].monitor;
        v28 = v27[10];
        if (v28 >= 1.0)
        {
          if (v28 <= 1.0)
            goto LABEL_61;
        }
        else
        {
          v28 = v28 + 0.0625;
        }
        if (v28 > 1.0)
          v28 = 1.0;
      }
      v27[10] = v28;
LABEL_61:
      v30 = *((u32 *)v27 + 11);
      if (v30)
      {
        PANELFILE_ArrowAnim_R(bookUI, 2, 0);
        v32 = ProcessData[11].monitor;
        v33 = v32[12];
        if (v33 <= 0.0)
        {
          if (v33 >= 0.0)
            goto LABEL_78;
        }
        else
        {
          v33 = v33 + -0.0625;
        }
        if (v33 < 0.0)
          v33 = 0.0;
      }
      else
      {
        PANELFILE_ArrowAnim_R(bookUI, 1, 0);
        v32 = ProcessData[11].monitor;
        v33 = v32[12];
        if (v33 >= 1.0)
        {
          if (v33 <= 1.0)
            goto LABEL_78;
        }
        else
        {
          v33 = v33 + 0.0625;
        }
        if (v33 > 1.0)
          v33 = 1.0;
      }
      v32[12] = v33;
LABEL_78:
      v35 = PANELFILE_CheckTextScroll_U(bookUI, 0);
      *((u32 *)v32 + 13) = v35;
      v37 = ProcessData[11].monitor;
      v37[15] = PANELFILE_CheckTextScroll_D(bookUI, 0);
      if (*((u32 *)ProcessData[11].monitor + 13))
      {
        PANELFILE_ArrowAnim_U(bookUI, 1, 0);
        v40 = ProcessData[11].monitor;
        v41 = v40[14];
        if (v41 >= 1.0)
        {
          if (v41 <= 1.0)
            goto LABEL_97;
        }
        else
        {
          v41 = v41 + 0.0625;
        }
        if (v41 > 1.0)
          v41 = 1.0;
      }
      else
      {
        PANELFILE_ArrowAnim_U(bookUI, 2, 0);
        v40 = ProcessData[11].monitor;
        v41 = v40[14];
        if (v41 <= 0.0)
        {
          if (v41 >= 0.0)
            goto LABEL_97;
        }
        else
        {
          v41 = v41 + -0.0625;
        }
        if (v41 < 0.0)
          v41 = 0.0;
      }
      v40[14] = v41;
LABEL_97:
      v43 = *((u32 *)v40 + 15);
      if (v43)
      {
        PANELFILE_ArrowAnim_D(bookUI, 1, 0);
        v45 = ProcessData[11].monitor;
        v46 = v45[16];
        if (v46 >= 1.0)
        {
          if (v46 <= 1.0)
            goto LABEL_114;
        }
        else
        {
          v46 = v46 + 0.0625;
        }
        if (v46 > 1.0)
          v46 = 1.0;
      }
      else
      {
        PANELFILE_ArrowAnim_D(bookUI, 2, 0);
        v45 = ProcessData[11].monitor;
        v46 = v45[16];
        if (v46 <= 0.0)
        {
          if (v46 >= 0.0)
            goto LABEL_114;
        }
        else
        {
          v46 = v46 + -0.0625;
        }
        if (v46 < 0.0)
          v46 = 0.0;
      }
      v45[16] = v46;
LABEL_114:
      if (v45[8] == 1.0)
      {
        if (CHECK_REP(4107, 1))
        {
          v48 = ProcessData[14].monitor;
          if (CheckPageEnable(v48, 1))
          {
            v49 = ProcessData[11].monitor;
            v49[5] = 1;
            v49[7] = 1;
            PANELMAIN_SetAnim(bookUI, 2, 0);
            SE(4259852);
          }
        }
        if (CHECK_REP(4104, 1))
        {
          v52 = ProcessData[14].monitor;
          if (CheckPageEnable(v52, -1))
          {
            *(u64 *)((char *)ProcessData[11].monitor + 20) = 0x100000001LL;
            PANELMAIN_SetAnim(bookUI, 2, 0);
            SE(4259852);
          }
        }
      }
      return v9;
    }
    goto LABEL_37;
  }
  return v9;
}

// 0x1bf2e90
static dds3ProcessFunc_t PANELFILEUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bookSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v7 = id;
  return SeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1bf2fb0
s32 GetNowUpdate(bookData_t *data) {
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[0]))
    return -1;
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[1]))
    return 0;
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[2]))
    return 1;
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[3]))
    return 2;
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[4]))
    return 3;
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[5]))
    return 4;
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[6]))
    return 5;
  if (!evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[7]))
    return 6;
  if (evtBitCheck(BOOKPAGE[data->nowSeq]->upDateTextFlag[8]))
  {
    return 8;
  }
  else
  {
    return 7;
  }
}

// 0x1bf32c0
void DebugUpdateText(bookData_t *data, s32 num) {
  s32 nowSeq;
  s32 *v7;
  s32 v8;
  s64 v10;
  s32 v11;
  s32 *upDateTextFlag;
  s32 v14;

  nowSeq = data->nowSeq;
  if (nowSeq == 1)
    return;
  if (num == 1)
  {
    nowSeq = data->nowSeq;
    upDateTextFlag = BOOKPAGE[nowSeq]->upDateTextFlag;
    v14 = upDateTextFlag[GetNowUpdate(data) + 1];
    if (!v14)
      goto LABEL_23;
    if ((u32)(v14 - 2618) >= 0xFFFFFFC6)
      evtBitKityouItemAdd(v14);
    v10 = (s64)GBWK->EventBit + 4 * (v14 / 32);
    v11 = *(u32 *)(v10 + 32) | (1 << v14);
    goto LABEL_22;
  }
  if (num != -1)
  {
LABEL_23:
    data->textChangeStep = 5;
    return;
  }
  nowSeq = data->nowSeq;
  v7 = BOOKPAGE[nowSeq]->upDateTextFlag;
  v8 = v7[GetNowUpdate(data)];
  v10 = (s64)GBWK->EventBit + 4 * (v8 / 32);
  v11 = *(u32 *)(v10 + 32) & ~(1 << v8);
LABEL_22:
  *(u32 *)(v10 + 32) = v11;
  goto LABEL_23;
}

// 0x1bf34f0
void SetSeqParent(bookData_t *data, s32 parentID) {
  bookData_t *v3;

  v3 = data;
  data->SeqParent[data->nowHierarchy] = parentID;
  ++v3->nowHierarchy;
}

// 0x1bf2ac0
s32 GoParent(bookData_t *data) {
  bookData_t *v2;
  s32 *m_Items;
  s32 v4;
  s64 v5;

  v2 = data;
  m_Items = data->SeqParent;
  m_Items[data->nowHierarchy] = 1;
  v4 = v2->nowHierarchy - 1;
  v2->nowHierarchy = v4;
  v5 = v4;
  v2->nowSeq = m_Items[v5];
  return m_Items[v5];
}

// 0x1be97c0
void SakuraEffectDraw(void) {
  if (ProcessCheck())
    return;
  cmpEffectSetRGBA(0x80808080);
  cmpDrawEffect();
}

// 0x1bf3520
dds3ProcessFunc_t EndProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  dds3ProcessFunc_t v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  LODWORD(ProcessData[8].klass) = 1;
  CursorInitFlag = -1;
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  if (((s64)ProcessData[1].klass & 0x40) == 0)
  {
    cmpProcessCheck();
    dds3FadeOut(0, 0, 0, 0x1Eu);
    LODWORD(ProcessData[1].klass) |= 0x40u;
    return 0;
  }
  if (!!dds3FadeCheck())
    return 0;
  if (ProcessCheck())
  {
    goto LABEL_27;
  }
  cmpDeleteEffect();
  End();
LABEL_27:
  if ((moonSave & 2) != 0)
    evtMoonEnableDraw();
  ReturnReadFlagData();
  v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v9;
}

// 0x1bf38a0
static s32 CallFunc(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[1].klass;
  HIDWORD(v4[3].klass) = itfMenuGetSelectID(klass);
  return 1;
}

// 0x1bf39e0
void CheckMenuBit_Exception(s32 flag, s32 bit, s32 pmflag, s32 onbit) {
  s64 v8;

  if (bit == flag && !evtBitCheck(onbit) && evtBitCheck(pmflag))
  {
    if (onbit)
    {
      if ((u32)(onbit - 2618) >= 0xFFFFFFC6)
        evtBitKityouItemAdd(onbit);
      v8 = (s64)GBWK->EventBit + 4 * (onbit / 32);
      *(u32 *)(v8 + 32) |= 1 << onbit;
    }
  }
}

// 0x1bf3ac0
static void SetFlagMenu(dds3ProcessID_t *PID, s32 MenuID, u32 Flag, bool Bool) {
  s32 v10;

  v10 = BOOKPAGE[MenuID]->upDateTextFlag[0];
  if (!v10 || evtBitCheck(v10))
  {
    itfMenuSetFlagMenu(PID, MenuID, Flag, Bool);
  }
}

// 0x1bf3bb0
static s32 CheckCyousaFlag(void) {
  s64 v1;

  v1 = 0;
  while (1)
  {
    if (v1 >= SLODWORD(bookCyousaTable->max_length))
      break;
    if (evtBitCheck(BOOKPAGE[bookCyousaTable[v1++]]->upDateTextFlag[0]))
    {
      return 1;
    }
  }
  return 0;
}

// 0x1bf3c80
static s32 CheckABADONcode(void) {
  return 0;
}

// 0x1bf3c90
static s32 CheckNextDest(void) {
  Il2CppObject *Item;

  if (DestNowList->_size < 1)
    return 0;
  Item = _get_Item(DestNowList, 0);
  return !op_Equality(Item[1].monitor, "", 0);
}

// 0x1bf3db0
static s32 CheckChildID(s32 ID) {
  return BOOKPAGE[ID]->childs > 0;
}

// 0x1bf3e30
static void SetCommand_New(void *wk) {
  s32 v3;
  s64 v4;
  char *LocalizeText;
  char *v8;
  s32 *v9;
  DITECTIVEBOOK_CLASS *BOOKPAGE_local;
  s64 v12;
  char *v15;
  s64 v16;
  s64 i;
  u32 v18;
  DITECTIVEBOOK_CLASS *v19;
  s64 v20;
  char *v22;
  char *v23;
  char *v25;
  s32 v26;
  s32 v30;
  s64 v32;
  DITECTIVEBOOK_CLASS *v33;

  v3 = 0;
  v4 = 5;
  while (1)
  {
    BOOKPAGE_local = BOOKPAGE;
    if (v4 - 4 >= SLODWORD(BOOKPAGE_local->max_length))
      break;
    v12 = *((u64 *)&BOOKPAGE_local->obj.klass + v4);
    if (*(u32 *)(v12 + 76) == -1)
      goto LABEL_5;
    if (*(u32 *)(v12 + 16))
    {
      v15 = *(char **)(v12 + 80);
      LocalizeText = GetLocalizeText(v15, 1);
      v8 = ChangeTextPLTF(LocalizeText);
      v9 = *((s32 **)&BOOKPAGE->obj.klass + v4);
      SetMenu_New(wk, v9[18], v9[19], v8, v9[4], v9[22]);
      goto LABEL_5;
    }
    v16 = (s64)secondHi + 4 * v3++;
    *(u32 *)(v16 + 32) = v4 - 4;
LABEL_5:
    ++v4;
  }
  for (i = 5; ; ++i)
  {
    v19 = BOOKPAGE;
    if (i - 4 >= SLODWORD(v19->max_length))
      break;
    if (v18)
    {
      v20 = *((u64 *)&v19->obj.klass + i);
      if (*(u32 *)(v20 + 76) != -1)
        continue;
    }
    else
    {
      v20 = *((u64 *)&BOOKPAGE->obj.klass + i);
      if (*(u32 *)(v20 + 76) != -1)
        continue;
    }
    v22 = *(char **)(v20 + 80);
    v23 = GetLocalizeText(v22, 1);
    v25 = ChangeTextPLTF(v23);
    if (*(u32 *)(*((u64 *)&BOOKPAGE->obj.klass + i) + 72) == 1)
    {
      v26 = CheckNextDest();
      if (v26)
        goto LABEL_46;
      goto LABEL_9001;
      if (v30)
      {
LABEL_46:
        *(u32 *)(*((u64 *)&BOOKPAGE->obj.klass + i) + 92) = 1;
      }
LABEL_9001:
    }
    SetRootMenu_New(wk, *(u32 *)(*((u64 *)&BOOKPAGE->obj.klass + i) + 72), *(u32 *)(*((u64 *)&BOOKPAGE->obj.klass + i) + 56), v25);
  }
  if (!v18)
  CheckAllParentReadFlag();
  v32 = 5;
  while (2)
  {
    v33 = BOOKPAGE;
    if (v32 - 4 < SLODWORD(v33->max_length))
    {
      if (*(u32 *)(*((u64 *)&v33->obj.klass + v32) + 76) == -1)
      {
        if (!*(u8 *)(*((u64 *)&DBOOK_READ_FLAG->obj.klass + v32) + 16))
        {
          ParentMenu_SetNewIconInit(bookUI, v32 - 4, *(u8 *)(*((u64 *)&DBOOK_READ_FLAG->obj.klass + v32) + 16) == 0, 5, 0);
        }
      }
      ++v32;
      continue;
    }
    break;
  }
}

// 0x1bf4e50
static void SetCommondParent(void *wk) {
  s64 i;
  char *LocalizeText;
  char *v8;
  s64 v9;
  DITECTIVEBOOK_CLASS *BOOKPAGE_local;
  s64 v12;
  char *v14;

  MenuObjReset(bookUI, 0);
  for (i = 5; ; ++i)
  {
    BOOKPAGE_local = BOOKPAGE;
    if (i - 4 >= SLODWORD(BOOKPAGE_local->max_length))
      break;
    v12 = *((u64 *)&BOOKPAGE_local->obj.klass + i);
    if (*(u32 *)(v12 + 76) == -1)
    {
      v14 = *(char **)(v12 + 80);
      LocalizeText = GetLocalizeText(v14, 1);
      v8 = ChangeTextPLTF(LocalizeText);
      v9 = *((u64 *)&BOOKPAGE->obj.klass + i);
      SetRootMenu_New(wk, *(u32 *)(v9 + 72), *(u32 *)(v9 + 56), v8);
      continue;
    }
  }
}

// 0x1bf5000
static void CallProcEnd(void *wk) {
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  itfMenuProcessEnd(menuPID);
}

// 0x1bf5090
static u8 CheckProcEnd(void *wk) {
  tagBOOK_MENU_WORK_Fields *p_fields;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  p_fields = &wk->fields;
  v5 = menuPID;
  if (itfMenuProcessCheck(v5))
    return 1;
  p_fields->menuPID = 0;
  return 0;
}

// 0x1bf5150
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass_low;
  char v6;
  Il2CppObject *v9;
  dds3ProcessID_t *v10;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (LOBYTE(ProcessData[2].monitor))
  {
    case 0:
      if (BYTE1(ProcessData[17].monitor) || LOBYTE(ProcessData[17].monitor) || !CHECK_TRIG(4097, 1))
      {
        if (!evtBitCheck(42))
          return 0;
        v14 = id;
        MenuCursorCtrl(v14);
        PanelTextCtrl(id);
      }
      else
      {
        LOWORD(ProcessData[3].klass) = 0;
        LOBYTE(ProcessData[2].monitor) = 1;
        SE(18);
      }
      return 0;
    case 1:
      klass_low = SLOWORD(ProcessData[3].klass);
      if (!LOWORD(ProcessData[3].klass))
      {
        HIDWORD(ProcessData[2].monitor) &= ~4u;
        goto LABEL_31;
      }
      if (klass_low < 2)
        goto LABEL_31;
      v6 = 2;
      goto LABEL_40;
    case 2:
      if (LOWORD(ProcessData[3].klass))
      {
        goto LABEL_19;
      }
      klass = ProcessData[1].klass;
      itfMenuProcessEnd(klass);
LABEL_19:
      v9 = ProcessData + 1;
      v10 = ProcessData[1].klass;
      if (itfMenuProcessCheck(v10))
      {
        LOWORD(klass_low) = ProcessData[3].klass;
LABEL_31:
        LOWORD(ProcessData[3].klass) = klass_low + 1;
        return 0;
      }
      ProcessData[1].klass = 0;
      v6 = 3;
LABEL_40:
      LOWORD(ProcessData[3].klass) = 0;
      LOBYTE(ProcessData[2].monitor) = v6;
      return 0;
    case 3:
      v11 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v11, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v11;
    default:
      return 0;
  }
}

// 0x1bf5830
static void Release(void *wk) {
  s32 flag;

  MenuActive = 0;
  flag = wk->flag;
  if ((flag & 2) == 0)
    return;
  if (wk->hSpr)
  {
    wk->hSpr = 0;
    flag = wk->flag;
  }
  wk->flag = flag & 0xFFFFFFFD;
}

// 0x1bf58f0
static void Shutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
  dds3ProcessID_t *p_monitor;
  dds3ProcessID_t *p_DBMPID;
  dds3ProcessID_t *p_g_mainPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  DestroyAsset(bookUI, 0);
  MenuActive = 0;
  monitor_high = HIDWORD(ProcessData[2].monitor);
  if ((monitor_high & 2) == 0)
  {
    p_monitor = &ProcessData[1].monitor;
    if (!dds3ExistProcess(p_monitor))
      goto LABEL_26;
    goto LABEL_23;
  }
  if (ProcessData[2].klass)
  {
    ProcessData[2].klass = 0;
    monitor_high = HIDWORD(ProcessData[2].monitor);
  }
  HIDWORD(ProcessData[2].monitor) = monitor_high & 0xFFFFFFFD;
  p_monitor = &ProcessData[1].monitor;
  if (dds3ExistProcess(p_monitor))
  {
LABEL_23:
    dds3KillProcess(p_monitor, 0);
  }
LABEL_26:
  p_monitor = 0;
  p_DBMPID = &DBMPID;
  p_DBMPID = 0;
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = 0;
}

// 0x1bf5b60
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v3;
  dds3ProcessID_t *v4;
  dds3ProcessID_t *p_DBMPID;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  v3 = id;
  v4 = id;
  p_DBMPID = &DBMPID;
  p_DBMPID = id;
  if (!ProcessData)
  if ((BYTE4(ProcessData[2].monitor) & 4) != 0)
  {
    v9 = id;
    UniDrawMenu_New(v9);
  }
  return 0;
}

// 0x1bf5ca0
void UniDrawMenu_New(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *v4;
  char *v6;
  s64 cursor;
  s32 v14;
  void *p_bookUI;
  void *v19;
  s64 v20;
  s32 v21;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  v6 = "";
  if (evtBitCheck(42))
  {
    if (v4->change_flag)
    {
      GuideSet(v4);
    }
    else if (v4->cursor_ID == -1)
    {
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      ButtonGuideDispSet("DBOOK01", 0, 90);
      ButtonLineHelpDispSet(1);
      ButtonLineHelpTextSet(dbookMenuHlepText[v4->cursor_parent], 0, 1, 0xA09DC380, 1);
      DeleteInsertImages(bookUI, 0);
      PANEL02_SetMessage(bookUI, v6, 0, 0, 0, 0);
      PANELFILE_SetMessage(bookUI, v6, 0);
      PANEL_TitleTextSet(bookUI, v6, 0);
      SaveIconCtrl(bookUI, 0, 0);
      v4->change_flag = 1;
    }
    else
    {
      cursor = v4->cursor;
      if (v4->id_save[cursor] != 15)
      {
        cursor = v4->cursor;
        PANEL_TitleTextSet(bookUI, v4->draw_text[cursor], 0);
      }
      DrawPanelCtrl(v4);
      AccessReadFlag(v4->id_save[v4->cursor]);
      if (DBOOK_READ_FLAG[v4->cursor_ID]->READ_FLAG)
      {
        if (!ChildrenMenu_GetIconColor(bookUI, v4->cursor, 0))
        {
          ChildrenMenu_SetIconCtrl(bookUI, v4->cursor, 6, 0);
        }
      }
      CheckAllParentReadFlag();
      v14 = v4->parent_save[v4->cursor];
      if (DBOOK_READ_FLAG[v14 + 1]->READ_FLAG)
      {
        v14 = v4->parent_save[v4->cursor];
        if (!ParentMenu_GetIconColor(bookUI, v4->parentID[v14], 0))
        {
          p_bookUI = &bookUI;
          v19 = p_bookUI;
          v20 = v4->parent_save[v4->cursor];
          v21 = v4->parentID[v20];
          LODWORD(v20) = v4->parent_save[v4->cursor];
          ParentMenu_SetNewIcon(v19, v21, !DBOOK_READ_FLAG[(s32)v20 + 1]->READ_FLAG, 6, 0);
        }
      }
    }
  }
}

// 0x1bf6530
static void DrawPanelCtrl(void *wk) {
  switch (wk->type_save[wk->cursor])
  {
    case 1:
    case 2:
      PANEL2Process(wk);
      goto LABEL_8;
    case 3:
    case 4:
      PANEL02_SetActive(bookUI, 0, 0);
      goto LABEL_12;
    case 5:
      PANEL5Process(wk);
      PANEL02_SetActive(bookUI, 0, 0);
      goto LABEL_13;
    case 6:
      PANELFILEProcess(wk);
      PANEL02_SetActive(bookUI, 0, 0);
      PANEL05_SetActive(bookUI, 0, 0);
      return;
    case 7:
      TIPSProcess(wk);
LABEL_8:
LABEL_12:
      PANEL05_SetActive(bookUI, 0, 0);
LABEL_13:
      PANELFILE_SetActive(bookUI, 0, 0);
      break;
    default:
      return;
  }
}

// 0x1bf61d0
void GuideSet(void *wk) {
  char *v5;
  s32 QuestMapNo;
  s64 cursor;
  bool active;
  char **v10;
  char **v11;
  s32 v12;
  bool v16;
  char **v17;
  char **v18;

  if (wk->cursor_ID == -1)
  {
    v5 = "DBOOK01";
    if (!op_Inequality("DBOOK01", wk->guideSave, 0))
      return;
    goto LABEL_27;
  }
  if (!QuestFlag)
    goto LABEL_21;
  goto LABEL_9000;
  if (!QuestFlag)
  {
LABEL_21:
    active = PANEL02_ScrollBarActiveChack(bookUI, 0);
    v10 = &"DBOOK02";
    v11 = &"DBOOK03";
    goto LABEL_24;
  }
LABEL_9000:
  QuestMapNo = GetQuestMapNo(QUESTPAGE[wk->id_save[wk->cursor]]);
  cursor = wk->cursor;
  if (!wk->reward_save[cursor])
  {
    v12 = QuestMapNo;
    cursor = wk->cursor;
    if (QUESTPAGE[wk->id_save[cursor]]->StopFlag)
    {
      if (GBWK->GameFileInfo->chapter == 9)
        goto LABEL_21;
    }
    v16 = PANEL02_ScrollBarActiveChack(bookUI, 0);
    v17 = &"DBOOK06";
    if (!v12)
      v17 = &"DBOOK02";
    v18 = &"DBOOK03";
    if (v12)
      v18 = &"DBOOK07";
    if (v16)
      v17 = v18;
    v5 = *v17;
    if (op_Inequality(*v17, wk->guideSave, 0))
      goto LABEL_27;
    return;
  }
  active = PANEL02_ScrollBarActiveChack(bookUI, 0);
  v10 = &"DBOOK04";
  v11 = &"DBOOK05";
LABEL_24:
  if (active)
    v10 = v11;
  v5 = *v10;
  if (op_Inequality(*v10, wk->guideSave, 0))
  {
LABEL_27:
    wk->guideSave = v5;
    ButtonGuideDispSet(v5, 0, 90);
  }
}

// 0x1bf44f0
static void SetMenu_New(void *wk, s32 MenuID, s32 ParentMenuID, char *pStr, s32 _type, s32 _subID) {
  s32 v15;
  s32 v16;
  s32 *EventBit;
  s64 v23;
  DITECTIVEBOOK_CLASS *v24;
  s64 v25;
  Il2CppClass **v26;
  void *v29;
  s32 *v31;
  DITECTIVEBOOK_CLASS *v32;
  s32 *v33;
  s64 v34;
  DITECTIVEBOOK_CLASS *v38;
  DITECTIVEBOOK_CLASS *v39;
  void *v40;
  DITECTIVEBOOK_CLASS *v42;
  s32 v43;

  v15 = BOOKPAGE[MenuID]->upDateTextFlag[0];
  MenuParentID[MenuID] = ParentMenuID;
  if (ParentMenuID == 230)
  {
    v16 = 15;
    goto LABEL_13;
  }
  else if (ParentMenuID == 243)
  {
    v16 = 14;
    goto LABEL_13;
  }
  else
  {
    v16 = ParentMenuID - 1;
    goto LABEL_13;
  }
LABEL_13:
  CheckMenuBit_Exception(v15, 8897, 880, v15);
  if (v15 != 8283)
  {
    CheckMenuBit_Exception(v15, 8289, 192, v15);
    if (!v15)
      goto LABEL_22;
    goto LABEL_21;
  }
  if (!evtBitCheck(8287) && evtBitCheck(192))
  {
    EventBit = GBWK->EventBit;
    EventBit[258] |= 0x80000000;
    goto LABEL_19;
  }
LABEL_19:
  CheckMenuBit_Exception(8283, 8289, 192, 8283);
LABEL_21:
  if (!evtBitCheck(v15))
    return;
LABEL_22:
  v43 = subID;
  v23 = ParentMenuID;
  SetIDTable(bookUI, MenuID, ParentMenuID, BOOKPAGE[v23]->childs, 0);
  v24 = BOOKPAGE[v23];
  v24->childID[v24->childs] = MenuID;
  ChildrenMenu_SetTaxt(bookUI, v24->childs, ParentMenuID, pStr, 0);
  ChildrenMenu_TexCloreChange(bookUI, BOOKPAGE[v23]->childs, ParentMenuID, 0, 0);
  v25 = v16;
  v26 = &wk->child_save[v25]->text->obj.klass
      + BOOKPAGE[v23]->childs;
  v26[4] = pStr;
  v29 = wk->child_save[v25];
  v29->parent = v16;
  v31 = v29->type;
  v32 = BOOKPAGE[v23];
  v29->ID[v32->childs] = MenuID;
  v31[v32->childs] = type;
  if (v16 != 2)
  {
    v34 = ParentMenuID;
    goto LABEL_34;
  }
  v33 = v29->subID;
  v34 = ParentMenuID;
  v33[v32->childs] = v43;
LABEL_34:
  CheckTextUpdate(MenuID, ParentMenuID);
  v38 = BOOKPAGE[v34];
  if (!DBOOK_READ_FLAG[v38->childID[v38->childs]]->READ_FLAG)
  {
    v40 = bookUI;
    v42 = BOOKPAGE[v34];
    ChildrenMenu_SetIconCtrlInit(v40, v42->childs, ParentMenuID, !DBOOK_READ_FLAG[v42->childID[v42->childs]]->READ_FLAG, 5, 0);
    goto LABEL_36;
  }
LABEL_36:
  v39 = BOOKPAGE[v34];
  ++v39->childs;
}

// 0x1bf49f0
static void SetRootMenu_New(void *wk, s32 MenuID, s32 ChildNum, char *pStr) {
  DITECTIVEBOOK_CLASS *v11;
  s32 openStatus;
  s32 v13;
  s64 v14;
  void *p_bookUI;
  s32 v18;

  v11 = BOOKPAGE[MenuID];
  openStatus = v11->openStatus;
  v13 = v11->upDateTextFlag[0];
  MenuParentID[MenuID] = 0;
  if (MenuID != 1)
  {
    if ((u32)(MenuID - 3) >= 9 && (u32)(MenuID - 13) >= 2)
    {
LABEL_23:
      if (MenuID != 12)
        goto LABEL_26;
      if (CheckCyousaFlag() == 1)
        goto LABEL_26;
LABEL_54:
      p_bookUI = &bookUI;
      v18 = MenuID;
      goto LABEL_57;
    }
    v14 = MenuID;
    if (BOOKPAGE[v14]->childs <= 0)
      goto LABEL_54;
    goto LABEL_23;
  }
  if (!CheckNextDest())
  {
    p_bookUI = &bookUI;
    v18 = 1;
LABEL_57:
    MenuObjCtrl(p_bookUI, v18, 0, 0);
    return;
  }
LABEL_26:
  if (!DLCEXIST)
  {
    MenuObjCtrl(bookUI, 243, 0, 0);
    MenuObjCtrl(bookUI, 230, 0, 0);
    goto LABEL_41;
  }
  if (MenuID == 230)
  {
    if (BOOKPAGE[230]->childs > 0)
      goto LABEL_41;
    p_bookUI = &bookUI;
    v18 = 230;
    goto LABEL_57;
  }
  if (MenuID == 243)
  {
    p_bookUI = &bookUI;
    v18 = 243;
    goto LABEL_57;
  }
LABEL_41:
  if (!v13 || evtBitCheck(v13))
  {
    ParentMenu_SetTaxt(bookUI, MenuID, pStr, 0);
    ++wk->menu_num;
    if (MenuID == 1)
    {
      CheckNextUpdate();
    }
    ChildMenuObjCtrl(bookUI, MenuID, ChildNum, 0, 0);
    MenuObjSave(bookUI, wk, MenuID, ChildNum, openStatus, pStr, 0, 0);
  }
}

// 0x1bf5520
void MenuCursorCtrl(dds3ProcessID_t *PID) {
  void *ProcessData;
  void *v4;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  if (ProcessData->menu_move)
  {
    if (MenuMoveCalc(ProcessData))
      return;
  }
  if (!QuestFlag)
    goto LABEL_28;
  if (v4->reward_move)
  {
    if (RewardMoveCalc(v4))
      return;
  }
  if (!v4->map_move)
  {
LABEL_28:
    MenuCursorCtrlSub(v4);
    return;
  }
  if (!MapMoveCalc(v4))
  {
    goto LABEL_28;
  }
}

// 0x1bf8a20
static void MenuMoveStartCtrl(void *wk) {
  s32 cursor_parent;
  s32 v4;
  DITECTIVEBOOK_CLASS *v6;
  s32 openStatus;
  s32 v13;
  s64 v14;
  s32 *parentID;
  il2cpp_array_size_t max_length;
  s32 *child_NumMax;
  u64 v18;
  s64 v19;
  __int128 v20;
  s32 *v21;
  s32 *v22;
  s64 v23;
  char v24;
  s64 v25;
  s64 v26;
  u64 v27;
  s64 v28;
  u32 *v29;
  u32 *v30;
  char *draw_text;
  s64 v32;
  s64 v33;
  _BOOL4 open_flag;
  void *v40;
  s32 v41;
  s32 v42;
  void *v43;
  s32 top;
  s32 *menu_drawOld;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 *menu_Before;
  s32 v61;
  s32 v62;
  s32 *menu_After;
  s32 *v64;
  s32 v65;
  s32 v66;
  s32 v67;
  s32 v68;
  s32 v69;
  s32 v70;
  s32 v71;
  s32 v72;
  s32 v73;
  s32 v74;
  s32 v75;
  s32 v76;
  s32 v77;
  s32 v78;
  s32 v79;
  s32 v80;
  s32 v81;
  s32 v82;
  s32 v83;
  s32 v84;
  s32 v85;
  s32 v86;

  if (wk->cursor_parent != -1 && CHECK_TRIG(4096, 1))
  {
    cursor_parent = wk->cursor_parent;
    if (cursor_parent == 14)
    {
      v4 = 243;
    }
    else if (cursor_parent == 15)
    {
      v4 = 230;
    }
    else
    {
      v4 = cursor_parent + 1;
    }
    v6 = BOOKPAGE[v4];
    openStatus = v6->openStatus;
    if (openStatus)
    {
      MenuChildAnimSetCtrl(bookUI, wk->cursor_parent, 1, 0);
      wk->open_flag = 0;
      BOOKPAGE[v4]->openStatus = 0;
    }
    else
    {
      MenuChildAnimSetCtrl(bookUI, wk->cursor_parent, 0, 0);
      v13 = wk->top + 11;
      v14 = (s64)BOOKPAGE + 8 * v4;
      wk->open_flag = 1;
      *(u32 *)(*(u64 *)(v14 + 32) + 92) = 1;
      if (v13 == wk->cursor)
        wk->open_move = 1;
    }
    parentID = wk->parentID;
    *(u64 *)&wk->parentID_Befor = 0;
    wk->menu_num = 0;
    max_length = parentID->max_length;
    if ((s32)max_length >= 1)
    {
      child_NumMax = wk->child_NumMax;
      v18 = (u32)parentID->max_length;
      v19 = 0;
      if (v18 < 0x10)
        goto LABEL_32;
      if ((u64)((char *)child_NumMax - (char *)parentID) < 0x40)
        goto LABEL_32;
      *(u64 *)&v20 = -1;
      *((u64 *)&v20 + 1) = -1;
      v19 = v18 - (parentID->max_length & 0xF);
      v21 = &child_NumMax[12];
      v22 = &parentID[4];
      v23 = v19;
      do
      {
        *((_OWORD *)v22 - 1) = v20;
        *(_OWORD *)v22 = v20;
        v23 -= 16;
        *((_OWORD *)v22 + 1) = v20;
        *((_OWORD *)v22 + 2) = v20;
        v22 += 16;
        *((_OWORD *)v21 - 3) = 0u;
        *((_OWORD *)v21 - 2) = 0u;
        *((_OWORD *)v21 - 1) = 0u;
        *(_OWORD *)v21 = 0u;
        v21 += 16;
      }
      while (v23);
      if ((max_length & 0xF) != 0)
      {
LABEL_32:
        v24 = max_length - v19;
        v25 = v19 + 1;
        if ((v24 & 1) != 0)
        {
          v26 = v19;
          parentID[v26] = -1;
          child_NumMax[v26] = 0;
          v19 = v25;
        }
        if (v18 != v25)
        {
          v27 = v18 - v19;
          v28 = 4 * v19 + 36;
          v29 = ((char *)child_NumMax + v28);
          v30 = ((char *)parentID + v28);
          do
          {
            *(v30 - 1) = -1;
            v27 -= 2;
            *(v29 - 1) = 0;
            *v30 = -1;
            v30 += 2;
            *v29 = 0;
            v29 += 2;
          }
          while (v27);
        }
      }
    }
    draw_text = wk->draw_text;
    if (SLODWORD(draw_text->max_length) >= 1)
    {
      v32 = 0;
      v33 = 32;
      do
      {
        *(Il2CppClass **)((char *)&draw_text->obj.klass + v33) = 0;
        draw_text = wk->draw_text;
        ++v32;
        v33 += 8;
      }
      while (v32 < SLODWORD(draw_text->max_length));
    }
    SetCommondParent(wk);
    wk->menu_move = 1;
    open_flag = wk->open_flag;
    wk->menu_child = BOOKPAGE[v4]->childs;
    if (open_flag)
    {
      v40 = bookUI;
      v41 = v4;
      v42 = 0;
    }
    else
    {
      v43 = bookUI;
      v40 = v43;
      v41 = v4;
      v42 = 1;
    }
    MenuCursorAlpha(v40, v41, BOOKPAGE[v4]->childs, v42, 0);
    top = wk->top;
    menu_drawOld = wk->menu_drawOld;
    if (top >= wk->menu_num)
      top = -1;
    menu_drawOld[0] = top;
    v46 = wk->top;
    if (v46 + 1 < wk->menu_num)
      v47 = v46 + 1;
    else
      v47 = -1;
    menu_drawOld[1] = v47;
    v48 = wk->top + 2;
    if (v48 >= wk->menu_num)
      v48 = -1;
    menu_drawOld[2] = v48;
    v49 = wk->top + 3;
    if (v49 >= wk->menu_num)
      v49 = -1;
    menu_drawOld[3] = v49;
    v50 = wk->top + 4;
    if (v50 >= wk->menu_num)
      v50 = -1;
    menu_drawOld[4] = v50;
    v51 = wk->top + 5;
    if (v51 >= wk->menu_num)
      v51 = -1;
    menu_drawOld[5] = v51;
    v52 = wk->top + 6;
    if (v52 >= wk->menu_num)
      v52 = -1;
    menu_drawOld[6] = v52;
    v53 = wk->top + 7;
    if (v53 >= wk->menu_num)
      v53 = -1;
    menu_drawOld[7] = v53;
    v54 = wk->top + 8;
    if (v54 >= wk->menu_num)
      v54 = -1;
    menu_drawOld[8] = v54;
    v55 = wk->top + 9;
    if (v55 >= wk->menu_num)
      v55 = -1;
    menu_drawOld[9] = v55;
    v56 = wk->top + 10;
    if (v56 >= wk->menu_num)
      v56 = -1;
    menu_drawOld[10] = v56;
    v57 = wk->top + 11;
    if (v57 >= wk->menu_num)
      v57 = -1;
    menu_drawOld[11] = v57;
    if (wk->menu_num <= 12)
    {
      v58 = wk->top;
      wk->top = 0;
      wk->topOld = v58;
    }
    v59 = menu_drawOld[0] - 1;
    menu_Before = wk->menu_Before;
    if (v59 < 0)
      v59 = -1;
    menu_Before[0] = v59;
    v61 = menu_drawOld[11];
    if (v61 + 1 < wk->menu_num)
      v62 = v61 + 1;
    else
      v62 = -1;
    v64 = wk->menu_Before;
    menu_After = wk->menu_After;
    menu_After[0] = v62;
    v65 = menu_drawOld[0] - 2;
    if (v65 < 0)
      v65 = -1;
    menu_Before[1] = v65;
    v66 = menu_drawOld[11] + 2;
    if (v66 >= wk->menu_num)
      v66 = -1;
    menu_After[1] = v66;
    v67 = menu_drawOld[0] - 3;
    if (v67 < 0)
      v67 = -1;
    menu_Before[2] = v67;
    v68 = menu_drawOld[11] + 3;
    if (v68 >= wk->menu_num)
      v68 = -1;
    menu_After[2] = v68;
    v69 = menu_drawOld[0] - 4;
    if (v69 < 0)
      v69 = -1;
    wk->menu_Before[3] = v69;
    v70 = menu_drawOld[11] + 4;
    if (v70 >= wk->menu_num)
      v70 = -1;
    wk->menu_After[3] = v70;
    v71 = menu_drawOld[0] - 5;
    if (v71 < 0)
      v71 = -1;
    wk->menu_Before[4] = v71;
    v72 = menu_drawOld[11] + 5;
    if (v72 >= wk->menu_num)
      v72 = -1;
    wk->menu_After[4] = v72;
    v73 = menu_drawOld[0] - 6;
    if (v73 < 0)
      v73 = -1;
    wk->menu_Before[5] = v73;
    v74 = menu_drawOld[11] + 6;
    if (v74 >= wk->menu_num)
      v74 = -1;
    wk->menu_After[5] = v74;
    v75 = menu_drawOld[0] - 7;
    if (v75 < 0)
      v75 = -1;
    wk->menu_Before[6] = v75;
    v76 = menu_drawOld[11] + 7;
    if (v76 >= wk->menu_num)
      v76 = -1;
    wk->menu_After[6] = v76;
    v77 = menu_drawOld[0] - 8;
    if (v77 < 0)
      v77 = -1;
    wk->menu_Before[7] = v77;
    v78 = menu_drawOld[11] + 8;
    if (v78 >= wk->menu_num)
      v78 = -1;
    wk->menu_After[7] = v78;
    v79 = menu_drawOld[0] - 9;
    if (v79 < 0)
      v79 = -1;
    wk->menu_Before[8] = v79;
    v80 = menu_drawOld[11] + 9;
    if (v80 >= wk->menu_num)
      v80 = -1;
    wk->menu_After[8] = v80;
    v81 = menu_drawOld[0] - 10;
    if (v81 < 0)
      v81 = -1;
    wk->menu_Before[9] = v81;
    v82 = menu_drawOld[11] + 10;
    if (v82 >= wk->menu_num)
      v82 = -1;
    wk->menu_After[9] = v82;
    v83 = menu_drawOld[0] - 11;
    if (v83 < 0)
      v83 = -1;
    wk->menu_Before[10] = v83;
    v84 = menu_drawOld[11] + 11;
    if (v84 >= wk->menu_num)
      v84 = -1;
    wk->menu_After[10] = v84;
    v85 = menu_drawOld[0] - 12;
    if (v85 < 0)
      v85 = -1;
    v64[11] = v85;
    v86 = menu_drawOld[11] + 12;
    if (v86 >= wk->menu_num)
      v86 = -1;
    wk->menu_After[11] = v86;
    SE(0);
  }
}

// 0x1bf77d0
static bool MenuMoveCalc(void *wk) {
  s32 moveCount;
  s32 menu_child;
  s32 v7;
  s32 v8;
  s32 draw;
  s32 *menu_draw;
  s32 v11;
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
  s32 *menu_drawOld;
  s32 topOld;
  char v27;
  s64 max_length;
  s32 *m_Items;
  s32 v30;
  s32 menu_num;
  bool v32;
  bool v33;
  s32 top;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;

  moveCount = wk->moveCount;
  if (moveCount <= 14)
  {
    if (wk->open_flag)
    {
      MenuPosCtrl(bookUI, wk->cursor_parent, wk->menu_child, 0, 0, 0);
      if (wk->open_move)
      {
        if (wk->menu_child >= 13)
          menu_child = 11;
        else
          menu_child = wk->menu_child;
        MenuPosCtrl(bookUI, -1, menu_child, 1, 0, 0);
        wk->menu_topChange = 1;
        wk->draw = menu_child;
      }
LABEL_85:
      ++wk->moveCount;
      return moveCount < 15;
    }
    menu_drawOld = wk->menu_drawOld;
    if ((s32)menu_drawOld->max_length < 1)
    {
      if (wk->menu_num > 12)
        goto LABEL_78;
    }
    else
    {
      topOld = 0;
      v27 = 0;
      max_length = (u32)menu_drawOld->max_length;
      m_Items = menu_drawOld;
      do
      {
        v30 = *m_Items++;
        if (v30 == -1)
        {
          menu_num = wk->menu_num;
          v32 = menu_num <= 12;
          v33 = menu_num > 12;
          if (!v32)
            ++topOld;
          v27 |= v33;
        }
        --max_length;
      }
      while (max_length);
      if (wk->menu_num > 12)
      {
        if ((v27 & 1) != 0)
          goto LABEL_82;
LABEL_78:
        MenuPosCtrl(bookUI, wk->cursor_parent, wk->menu_child, 1, 0, 0);
        goto LABEL_85;
      }
    }
    topOld = wk->topOld;
LABEL_82:
    MenuPosCtrl(bookUI, wk->cursor_parent, wk->menu_child, 1, 0, 0);
    MenuPosCtrl(bookUI, -1, topOld, 0, 0, 0);
    wk->draw = topOld;
    wk->menu_topChange = 1;
    goto LABEL_85;
  }
  if (wk->menu_topChange)
  {
    v7 = wk->menu_num;
    if (v7 <= 12)
    {
      menu_draw = wk->menu_draw;
      if (wk->top >= v7)
        top = -1;
      else
        top = wk->top;
      menu_draw[0] = top;
      v35 = wk->top;
      if (v35 + 1 < wk->menu_num)
        v36 = v35 + 1;
      else
        v36 = -1;
      menu_draw[1] = v36;
      v37 = wk->top + 2;
      if (v37 >= wk->menu_num)
        v37 = -1;
      menu_draw[2] = v37;
      v38 = wk->top + 3;
      if (v38 >= wk->menu_num)
        v38 = -1;
      menu_draw[3] = v38;
      v39 = wk->top + 4;
      if (v39 >= wk->menu_num)
        v39 = -1;
      menu_draw[4] = v39;
      v40 = wk->top + 5;
      if (v40 >= wk->menu_num)
        v40 = -1;
      menu_draw[5] = v40;
      v41 = wk->top + 6;
      if (v41 >= wk->menu_num)
        v41 = -1;
      menu_draw[6] = v41;
      v42 = wk->top + 7;
      if (v42 >= wk->menu_num)
        v42 = -1;
      menu_draw[7] = v42;
      v43 = wk->top + 8;
      if (v43 >= wk->menu_num)
        v43 = -1;
      menu_draw[8] = v43;
      v44 = wk->top + 9;
      if (v44 >= wk->menu_num)
        v44 = -1;
      menu_draw[9] = v44;
      v45 = wk->top + 10;
      if (v45 >= wk->menu_num)
        v45 = -1;
      menu_draw[10] = v45;
      v24 = wk->top;
    }
    else
    {
      v8 = wk->top;
      draw = wk->draw;
      menu_draw = wk->menu_draw;
      if (wk->open_move)
      {
        v11 = v8 + draw;
        if (v11 >= v7)
          v12 = -1;
        else
          v12 = v11;
        menu_draw[0] = v12;
        v13 = wk->top + wk->draw;
        if (v13 + 1 < wk->menu_num)
          v14 = v13 + 1;
        else
          v14 = -1;
        menu_draw[1] = v14;
        v15 = wk->top + wk->draw + 2;
        if (v15 >= wk->menu_num)
          v15 = -1;
        menu_draw[2] = v15;
        v16 = wk->top + wk->draw + 3;
        if (v16 >= wk->menu_num)
          v16 = -1;
        menu_draw[3] = v16;
        v17 = wk->top + wk->draw + 4;
        if (v17 >= wk->menu_num)
          v17 = -1;
        menu_draw[4] = v17;
        v18 = wk->top + wk->draw + 5;
        if (v18 >= wk->menu_num)
          v18 = -1;
        menu_draw[5] = v18;
        v19 = wk->top + wk->draw + 6;
        if (v19 >= wk->menu_num)
          v19 = -1;
        menu_draw[6] = v19;
        v20 = wk->top + wk->draw + 7;
        if (v20 >= wk->menu_num)
          v20 = -1;
        menu_draw[7] = v20;
        v21 = wk->top + wk->draw + 8;
        if (v21 >= wk->menu_num)
          v21 = -1;
        menu_draw[8] = v21;
        v22 = wk->top + wk->draw + 9;
        if (v22 >= wk->menu_num)
          v22 = -1;
        menu_draw[9] = v22;
        v23 = wk->top + wk->draw + 10;
        if (v23 >= wk->menu_num)
          v23 = -1;
        menu_draw[10] = v23;
        v24 = wk->top + wk->draw;
      }
      else
      {
        v48 = v8 - draw;
        if (v48 >= v7)
          v49 = -1;
        else
          v49 = v48;
        menu_draw[0] = v49;
        v50 = wk->top - wk->draw;
        if (v50 + 1 < wk->menu_num)
          v51 = v50 + 1;
        else
          v51 = -1;
        menu_draw[1] = v51;
        v52 = wk->top - wk->draw + 2;
        if (v52 >= wk->menu_num)
          v52 = -1;
        menu_draw[2] = v52;
        v53 = wk->top - wk->draw + 3;
        if (v53 >= wk->menu_num)
          v53 = -1;
        menu_draw[3] = v53;
        v54 = wk->top - wk->draw + 4;
        if (v54 >= wk->menu_num)
          v54 = -1;
        menu_draw[4] = v54;
        v55 = wk->top - wk->draw + 5;
        if (v55 >= wk->menu_num)
          v55 = -1;
        menu_draw[5] = v55;
        v56 = wk->top - wk->draw + 6;
        if (v56 >= wk->menu_num)
          v56 = -1;
        menu_draw[6] = v56;
        v57 = wk->top - wk->draw + 7;
        if (v57 >= wk->menu_num)
          v57 = -1;
        menu_draw[7] = v57;
        v58 = wk->top - wk->draw + 8;
        if (v58 >= wk->menu_num)
          v58 = -1;
        menu_draw[8] = v58;
        v59 = wk->top - wk->draw + 9;
        if (v59 >= wk->menu_num)
          v59 = -1;
        menu_draw[9] = v59;
        v60 = wk->top - wk->draw + 10;
        if (v60 >= wk->menu_num)
          v60 = -1;
        menu_draw[10] = v60;
        v24 = wk->top - wk->draw;
      }
    }
    v61 = wk->menu_num;
    v62 = v24 + 11;
    wk->menu_topChange = 0;
    if (v62 >= v61)
      v62 = -1;
    menu_draw[11] = v62;
    wk->top = menu_draw[0];
  }
  selMenuSetScrollBar(bookUI, wk->menu_num, 0);
  selMenuScrollBarMove(bookUI, wk->menu_num, wk->top, 0);
  *(u16 *)&wk->open_move = 0;
  wk->moveCount = 0;
  return moveCount < 15;
}

// 0x1bf8890
static void MenuCursorCtrlSub(void *wk) {
  bool v7;
  u32 v10;

  if (CHECK_REP(4100, 1))
  {
    CursorUp(wk);
  }
  else if (CHECK_REP(4101, 1))
  {
    CursorDown(wk);
  }
  else if (CHECK_REP(43526, 1))
  {
    CursorLeft(wk);
  }
  else
  {
    v7 = CHECK_REP(43527, 1);
    if (v7)
    {
      CursorRight(wk);
    }
    else
    {
      if (QuestFlag)
      {
        if (!v10)
        QuestMenuMoveStartCtrl(wk);
      }
      else
      {
        if (!v10)
        MenuMoveStartCtrl(wk);
      }
    }
  }
}

// 0x1bf91a0
static void CursorUp(void *wk) {
  s32 cursor;
  bool v4;
  s32 v5;
  s32 top;
  s32 v7;
  s32 child_move;
  s32 v11;
  s64 v16;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v20;
  s32 *menu_draw;
  s32 v25;
  s32 v26;
  s64 v27;
  char *v28;

  cursor = wk->cursor;
  if (cursor)
  {
    v5 = cursor - 1;
    v4 = cursor - 1 < 0;
    top = wk->top;
    if (v4)
    {
      v5 = 0;
      v7 = wk->top;
      child_move = wk->child_move;
      v11 = -child_move;
      if (wk->move_flag)
        goto LABEL_14;
    }
    else
    {
      if (v5 < top)
      {
        v7 = top - 1;
        if (top <= 2147483635)
        {
          v25 = top + 12;
          v26 = top - 1;
          do
          {
            v27 = 0;
            while (4 * (MENU_PARENT_MAX & (u32)~(MENU_PARENT_MAX >> 31)) != v27)
            {
              v28 = (char *)wk->parentID + v27;
              v27 += 4;
              if (v26 == *((u32 *)v28 + 8))
                goto LABEL_8;
            }
            ++v26;
          }
          while (v26 < v25);
        }
LABEL_8:
        MenuCorsorPosCtrl(bookUI, 1, 0, 0);
        child_move = wk->child_move;
        v11 = v5 - child_move;
        if (!wk->move_flag)
          goto LABEL_16;
LABEL_14:
        wk->move_flag = 0;
        goto LABEL_18;
      }
      v7 = wk->top;
      child_move = wk->child_move;
      v11 = v5 - child_move;
      if (wk->move_flag)
        goto LABEL_14;
    }
LABEL_16:
    if ((u32)(child_move + 1) <= 1)
      wk->child_move = 0;
LABEL_18:
    Menu_CursorChange(bookUI, v11, wk->cursor_old, 0);
    wk->cursor_old = v5;
    MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
    if ((s32)MENU_PARENT_MAX >= 1)
    {
      v16 = 0;
      m_Items = wk->parentID;
      while (m_Items[v16] != v5)
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        ++v16;
        wk->cursor_ID = id_save[v5];
        if (MENU_PARENT_MAX == v16)
          goto LABEL_33;
      }
      wk->cursor_parent = v16;
      wk->cursor_ID = -1;
      wk->parentCursor_save = v16;
    }
LABEL_33:
    v20 = vdupq_n_s32(v7);
    menu_draw = wk->menu_draw;
    menu_draw[0] = v7;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v20, (int32x4_t)xmmword_3D07320);
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v20, (int32x4_t)xmmword_3D01E30);
    menu_draw[11] = v7 + 11;
    *(int32x2_t *)&menu_draw[9] = vadd_s32((int32x2_t)v20.n128_u64[0], (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(bookUI, wk->menu_num, v7, 0);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    DeleteInsertImages(bookUI, 0);
    wk->cursor = v5;
    wk->top = v7;
    SE(3);
    return;
  }
}

// 0x1bf9550
static void CursorDown(void *wk) {
  s32 cursor;
  s32 v4;
  s32 v5;
  s32 top;
  s32 v9;
  s64 v14;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v18;
  s32 *menu_draw;
  s32 v23;
  s64 v24;
  char *v25;

  cursor = wk->cursor;
  v4 = wk->menu_num - 1;
  if (cursor != v4)
  {
    v5 = cursor + 1;
    top = wk->top;
    if (cursor + 1 <= v4)
    {
      if (v5 - top >= 12)
      {
        if (top <= 2147483634)
        {
          v23 = wk->top;
          do
          {
            v24 = 0;
            while (4 * (MENU_PARENT_MAX & (u32)~(MENU_PARENT_MAX >> 31)) != v24)
            {
              v25 = (char *)wk->parentID + v24;
              v24 += 4;
              if (v23 == *((u32 *)v25 + 8))
                goto LABEL_9;
            }
            ++v23;
          }
          while (v23 < top + 13);
        }
LABEL_9:
        ++top;
        MenuCorsorPosCtrl(bookUI, 1, 1, 0);
      }
    }
    else
    {
      v5 = wk->menu_num - 1;
    }
    v9 = v5 - wk->child_move;
    if (wk->move_flag)
      wk->move_flag = 0;
    Menu_CursorChange(bookUI, v9, wk->cursor_old, 0);
    wk->cursor_old = v5;
    MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
    if ((s32)MENU_PARENT_MAX >= 1)
    {
      v14 = 0;
      m_Items = wk->parentID;
      while (m_Items[v14] != v5)
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        ++v14;
        wk->cursor_ID = id_save[v5];
        if (MENU_PARENT_MAX == v14)
          goto LABEL_29;
      }
      wk->cursor_parent = v14;
      wk->cursor_ID = -1;
      wk->parentCursor_save = v14;
    }
LABEL_29:
    v18 = vdupq_n_s32(top);
    menu_draw = wk->menu_draw;
    menu_draw[0] = top;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v18, (int32x4_t)xmmword_3D07320);
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v18, (int32x4_t)xmmword_3D01E30);
    menu_draw[11] = top + 11;
    *(int32x2_t *)&menu_draw[9] = vadd_s32((int32x2_t)v18.n128_u64[0], (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(bookUI, wk->menu_num, top, 0);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    DeleteInsertImages(bookUI, 0);
    wk->cursor = v5;
    wk->top = top;
    SE(3);
    return;
  }
}

// 0x1bf98d0
static void CursorLeft(void *wk) {
  s32 top;
  s32 menu_num;
  s32 cursor;
  s32 *v6;
  s64 v7;
  s32 v8;
  bool v9;
  s64 v10;
  s32 v11;
  s32 v12;
  s64 v13;
  s64 v15;
  s32 v16;
  s32 *v17;
  s64 v19;
  s32 *v20;
  s32 v21;
  s64 v22;
  s32 v23;
  s32 v25;
  s32 v26;
  s64 v31;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v35;
  s32 *menu_draw;

  top = wk->top;
  menu_num = wk->menu_num;
  cursor = wk->cursor;
  v6 = NewSpecific(s32, 0xCu);
  if (cursor && menu_num >= 13)
  {
    v7 = v6;
    v8 = cursor - 12;
    v9 = v8 < 0 || top - 12 <= 0;
    v10 = 0;
    v11 = (top - 12) & ~((top - 12) >> 31) & ~(v8 >> 31);
    v12 = !v9;
    v13 = &v6[0];
    while (v10 < MENU_DRAW_MAX)
    {
      *(u32 *)(v13 + 4 * v10) = v11 + v10;
      ++v10;
    }
    v15 = 0;
    v16 = 0;
    v17 = (v7 + 32);
    while (1)
    {
      if (v15 >= MENU_DRAW_MAX)
        break;
      v19 = (u32)MENU_DRAW_MAX & ~((s32)MENU_DRAW_MAX >> 31);
      v20 = v17;
      while (v19)
      {
        --v19;
        v21 = *v20++;
        if (wk->menu_draw[v15] == v21)
          goto LABEL_18;
      }
      goto LABEL_9000;
      while (1)
      {
        if (v22 >= MENU_DRAW_MAX)
          break;
        v23 = v17[v22++];
        if (wk->menu_draw[v15] == v23)
        {
LABEL_18:
          ++v16;
          break;
        }
      }
LABEL_9000:
      ++v15;
    }
    if (!v12)
      v8 = 0;
    v25 = MENU_DRAW_MAX - v16;
    MenuCorsorPosCtrl(bookUI, v25, 0, 0);
    v26 = v8 - wk->child_move;
    if (wk->move_flag)
      wk->move_flag = 0;
    Menu_CursorChange(bookUI, v26, wk->cursor_old, 0);
    wk->cursor_old = v8;
    MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
    if ((s32)MENU_PARENT_MAX >= 1)
    {
      v31 = 0;
      m_Items = wk->parentID;
      while (m_Items[v31] != v8)
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        ++v31;
        wk->cursor_ID = id_save[v8];
        if (MENU_PARENT_MAX == v31)
          goto LABEL_57;
      }
      wk->cursor_parent = v31;
      wk->cursor_ID = -1;
      wk->parentCursor_save = v31;
    }
LABEL_57:
    v35 = vdupq_n_s32(v11);
    menu_draw = wk->menu_draw;
    menu_draw[0] = v11;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v35, (int32x4_t)xmmword_3D07320);
    menu_draw[11] = v11 + 11;
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v35, (int32x4_t)xmmword_3D01E30);
    *(int32x2_t *)&menu_draw[9] = vadd_s32(vdup_n_s32(v11), (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(bookUI, wk->menu_num, v11, 0);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    DeleteInsertImages(bookUI, 0);
    wk->cursor = v8;
    wk->top = v11;
    SE(3);
    return;
  }
}

// 0x1bf9d10
static void CursorRight(void *wk) {
  s32 top;
  s32 menu_num;
  s32 cursor;
  s32 *v6;
  s32 v7;
  s32 v8;
  s64 v9;
  s32 v10;
  u32 v11;
  s64 v12;
  s64 v14;
  s32 v15;
  s32 *v16;
  s64 v19;
  s32 *v20;
  s32 v21;
  s64 v22;
  s32 v23;
  s32 v25;
  s32 v26;
  s64 v31;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v35;
  s32 *menu_draw;

  top = wk->top;
  menu_num = wk->menu_num;
  cursor = wk->cursor;
  v6 = NewSpecific(s32, 0xCu);
  if (menu_num >= 13)
  {
    v7 = menu_num - 1;
    if (cursor != menu_num - 1)
    {
      v8 = top + 12;
      v9 = v6;
      if (top + 12 >= menu_num)
      {
        v11 = menu_num - 12;
      }
      else
      {
        v10 = menu_num - 12;
        if (v8 >= menu_num - 12)
          v11 = menu_num - 12;
        else
          v11 = top + 12;
        if (v8 < v10)
          v7 = cursor + 12;
      }
      v12 = 0;
      while (v12 < MENU_DRAW_MAX)
      {
        *(u32 *)(v9 + 32 + 4 * v12) = v11 + v12;
        ++v12;
      }
      v14 = 0;
      v15 = 0;
      v16 = (v9 + 32);
      while (1)
      {
        if (v14 >= MENU_DRAW_MAX)
          break;
        v19 = (u32)MENU_DRAW_MAX & ~((s32)MENU_DRAW_MAX >> 31);
        v20 = v16;
        while (v19)
        {
          --v19;
          v21 = *v20++;
          if (wk->menu_draw[v14] == v21)
            goto LABEL_20;
        }
        goto LABEL_9000;
        while (1)
        {
          if (v22 >= MENU_DRAW_MAX)
            break;
          v23 = v16[v22++];
          if (wk->menu_draw[v14] == v23)
          {
LABEL_20:
            ++v15;
            break;
          }
        }
LABEL_9000:
        ++v14;
      }
      v25 = MENU_DRAW_MAX - v15;
      MenuCorsorPosCtrl(bookUI, v25, 1, 0);
      v26 = v7 - wk->child_move;
      if (wk->move_flag)
        wk->move_flag = 0;
      Menu_CursorChange(bookUI, v26, wk->cursor_old, 0);
      wk->cursor_old = v7;
      MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
      if ((s32)MENU_PARENT_MAX >= 1)
      {
        v31 = 0;
        m_Items = wk->parentID;
        while (m_Items[v31] != v7)
        {
          id_save = wk->id_save;
          wk->cursor_parent = -1;
          ++v31;
          wk->cursor_ID = id_save[v7];
          if (MENU_PARENT_MAX == v31)
            goto LABEL_57;
        }
        wk->cursor_parent = v31;
        wk->cursor_ID = -1;
        wk->parentCursor_save = v31;
      }
LABEL_57:
      v35 = vdupq_n_s32(v11);
      menu_draw = wk->menu_draw;
      menu_draw[0] = v11;
      *(int32x4_t *)&menu_draw[1] = vaddq_s32(v35, (int32x4_t)xmmword_3D07320);
      menu_draw[11] = v11 + 11;
      *(int32x4_t *)&menu_draw[5] = vaddq_s32(v35, (int32x4_t)xmmword_3D01E30);
      *(int32x2_t *)&menu_draw[9] = vadd_s32(vdup_n_s32(v11), (int32x2_t)0xA00000009LL);
      DrawMenuBeforeAfterSave(wk);
      selMenuScrollBarMove(bookUI, wk->menu_num, v11, 0);
      wk->change_flag = 0;
      wk->textChangeStep = 0;
      DeleteInsertImages(bookUI, 0);
      wk->cursor = v7;
      wk->top = v11;
      SE(3);
      return;
    }
  }
}

// 0x1bfaaa0
static void DrawMenuBeforeAfterSave(void *wk) {
  s32 v3;
  s64 v5;
  s32 *menu_draw;
  s64 v8;
  s32 *menu_After;
  s32 v10;
  s32 v11;
  s32 v12;
  u64 v13;
  u64 v14;
  s32 v15;
  char *v16;
  s64 v17;
  s64 v18;
  char *v19;
  s32 v20;
  s32 *menu_Before;
  s64 v22;
  s64 v23;
  s32 v24;
  s32 *v26;
  s64 v27;
  s64 v28;
  s32 v29;
  s32 v31;
  s32 v33;
  s32 v34;

  v3 = -1;
  v5 = 8;
  while (1)
  {
    if (v5 - 8 >= MENU_DRAW_MAX)
      break;
    menu_draw = wk->menu_draw;
    v8 = 4 * v5;
    menu_After = wk->menu_After;
    v10 = v3 + menu_draw[0];
    --v3;
    if (v10 < 0)
      v10 = -1;
    *((u32 *)&wk->menu_Before->obj.klass + v5) = v10;
    *((u32 *)&wk->Before_Save->obj.klass + v5) = v10;
    v11 = v5++ + menu_draw[11];
    v12 = v11 - 7;
    if (v12 >= wk->menu_num)
      v12 = -1;
    *(u32 *)((char *)&menu_After->obj.klass + v8) = v12;
  }
  v13 = (u32)wk->menu_Before[0];
  if ((v13 & 0x80000000) == 0)
  {
    if ((s32)v13 < (s32)MENU_DRAW_MAX)
    {
      v14 = 0;
      while ((s64)v14 < MENU_DRAW_MAX)
      {
        if (v14 > v13)
          v15 = -1;
        else
          v15 = v14;
        v16 = (char *)wk->menu_Before + 4 * v14++;
        *((u32 *)v16 + 8) = v15;
      }
      goto LABEL_29;
    }
    v17 = 0;
    v18 = 76;
    while (v17 < MENU_DRAW_MAX)
    {
      v19 = (char *)wk->menu_Before + 4 * v17;
      v20 = *(u32 *)((char *)&wk->Before_Save->obj.klass + v18);
      ++v17;
      v18 -= 4;
      *((u32 *)v19 + 8) = v20;
    }
  }
LABEL_29:
  menu_Before = wk->menu_Before;
  if (SLODWORD(menu_Before->max_length) >= 1)
  {
    v22 = 8;
    do
    {
      v24 = *((u32 *)&menu_Before->obj.klass + v22);
      if ((v24 & 0x80000000) == 0)
      {
        v24 = *((u32 *)&wk->menu_Before->obj.klass + v22);
        MenuAlphaCtlr(bookUI, v24, 0, 0);
        menu_Before = wk->menu_Before;
      }
      v23 = v22 - 7;
      ++v22;
    }
    while (v23 < SLODWORD(menu_Before->max_length));
  }
  v26 = wk->menu_After;
  if (SLODWORD(v26->max_length) >= 1)
  {
    v27 = 8;
    do
    {
      v29 = *((u32 *)&v26->obj.klass + v27);
      if ((v29 & 0x80000000) == 0)
      {
        v29 = *((u32 *)&wk->menu_After->obj.klass + v27);
        MenuAlphaCtlr(bookUI, v29, 0, 0);
        v26 = wk->menu_After;
      }
      v28 = v27 - 7;
      ++v27;
    }
    while (v28 < SLODWORD(v26->max_length));
    menu_Before = wk->menu_Before;
  }
  if (menu_Before[0] >= 1)
  {
    v31 = 0;
    do
    {
      MenuAlphaCtlr(bookUI, v31++, 1, 0);
    }
    while (v31 < wk->menu_Before[0]);
    v26 = wk->menu_After;
  }
  v33 = v26[11];
  if (v33 >= 1)
  {
    v34 = v33 + 1;
    if (v33 + 1 <= 255)
    {
      do
      {
        MenuAlphaCtlr(bookUI, v34++, 1, 0);
      }
      while (v34 != 256);
    }
  }
}

// 0x1bef970
s32 GetSelectIndex(void) {
  s32 *ProcessData;

  if (!g_mainPID)
    return -1;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[13];
  return ProcessData[13];
}

// 0x1bef160
void Start(void) {
  dds3GetProcessData(g_mainPID);
}

// 0x1bef220
void SetFocus(bool a_bFocus) {
  dds3GetProcessData(g_mainPID);
}

// 0x1bfae00
void CallDrawBack(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[2].monitor) |= 0x10u;
}

// 0x1be9880
void MenuProcessStart(void) {
  void *v1;
  char *v2;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_g_mainPID;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *v9;
  s64 v10;
  s64 v11;
  s64 v12;
  s64 v14;
  void *v15;
  s64 v17;
  s64 i;
  s64 v19;
  s64 v20;
  s64 v21;
  s32 v26;
  s64 v30;
  s64 v31;
  s64 v32;
  s32 v33;
  s64 v34;
  s64 v35;
  u32 v36;
  s64 v40;
  u32 *v42;
  s64 v43;
  s32 v44;
  s32 v45;
  s64 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;
  s32 v63;
  s32 v64;
  s32 v65;
  s32 v66;
  s32 v67;
  s32 v68;
  s32 v69;
  u64 v70;
  s64 v71;
  s32 *v72;
  s64 v73;
  s32 v74;
  u64 v75;
  s32 v76;
  s64 v77;
  void *Instance;
  void *v80;
  u32 v81;

  v1 = Allocate(tagBOOK_MENU_WORK);
  _ctor(v1, 0);
  v2 = "";
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_DitectiveBook_Process__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_DitectiveBook_Shutdown__, 0);
  started = dds3StartProcess("jms_menu_main", 1023, 0, 0, v3, v4, v1);
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = started;
  v8 = Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_DitectiveBook_DrawProcess__, 0);
  v9 = dds3StartProcess("jms_menu_draw", 11029, 0, 0, v8, 0, v1);
  v1->drawPID = v9;
  v10 = v1->parentID;
  if (*(s32 *)(v10 + 24) >= 1)
  {
    v11 = 0;
    v12 = 32;
    do
    {
      *(u32 *)(v10 + 4 * v11 + 32) = -1;
      v14 = v1->child_save;
      v15 = Allocate(tagBOOK_MENU_WORK_ChildSave);
      _ctor(v15, 0);
      if (v15)
        QueryInterface(v15, *(void **)(*(u64 *)v14 + 64));
      *(u64 *)(v14 + v12) = v15;
      v10 = v1->parentID;
      ++v11;
      v12 += 8;
    }
    while (v11 < *(s32 *)(v10 + 24));
  }
  v17 = 32;
  for (i = 32; i != 1056; i += 4)
  {
    v19 = v1->draw_text;
    if (!*(u64 *)(v19 + v17))
    {
      *(u64 *)(v19 + v17) = 0;
      v20 = v1->id_save;
      *(u32 *)((u64)v1->parent_save + i) = -1;
      v21 = v1->type_save;
      *(u32 *)(v20 + i) = -1;
      *(u32 *)(v21 + i) = -1;
    }
    v17 += 8;
  }
  CheckNextUpdate();
  MenuActiveOnOff(bookUI, 1, 0);
  SetCommand_New(v1);
  MenuAnimSetCtrl(bookUI, 0, 0);
  PANELMAIN_SetAnim_new(bookUI, 1, 0);
  PANEL_TitleObjCtrl(bookUI, QuestFlag, 0);
  PANEL_TitleTextSet(bookUI, v2, 0);
  if (BOOKPAGE[1]->openStatus == 1)
  {
    MenuChildAnimSetCtrl(bookUI, 0, 0, 0);
    MenuPosCtrl(bookUI, 0, 1, 0, 1, 0);
  }
  v26 = v1->flag;
  *(u16 *)&v1->reward_move = 0;
  v1->index = 0;
  v1->flag = v26 | 4;
  if (CursorInitFlag > 3)
  {
LABEL_65:
    v1->cursor = 0;
    v1->cursor_old = 0;
    v1->cursor_ID = -1;
    v1->top = 0;
    goto LABEL_67;
  }
  switch (CursorInitFlag)
  {
    case 0u:
      if (BOOKPAGE[1]->openStatus != 1)
        goto LABEL_65;
      v30 = v1->id_save;
      *(u64 *)&v1->cursor = 0x100000001LL;
      v1->cursor_ID = *(u32 *)(v30 + 36);
      v1->top = 0;
      if (!(u32)v30)
        goto LABEL_66;
      goto LABEL_67;
    case 1u:
      if (BOOKPAGE[5]->childs < 1)
        goto LABEL_65;
      v31 = v1->parentID;
      v32 = *(s32 *)(v31 + 48);
      v1->cursor = v32;
      v33 = *(u32 *)(v31 + 48);
      goto LABEL_63;
    case 2u:
      if (BOOKPAGE[6]->childs < 1)
        goto LABEL_65;
      v34 = v1->parentID;
      v32 = *(s32 *)(v34 + 52);
      v1->cursor = v32;
      v33 = *(u32 *)(v34 + 52);
      goto LABEL_63;
    case 3u:
      if (BOOKPAGE[11]->childs < 1)
        goto LABEL_65;
      v35 = v1->parentID;
      v32 = *(s32 *)(v35 + 72);
      v1->cursor = v32;
      v33 = *(u32 *)(v35 + 72);
LABEL_63:
      v1->cursor_old = v33;
      v1->cursor_ID = *(u32 *)((u64)v1->id_save + 4 * v32 + 32);
      v1->top = 0;
      if (v36)
LABEL_66:
LABEL_67:
      v1->nextDestNowPage = DestTextIDList->_size - 1;
      Menu_CursorChangeInit(bookUI, v1->cursor, 0);
      v40 = 0;
      v1->cursor_old = v1->cursor;
      while (v40 < MENU_PARENT_MAX)
      {
        if (*(u32 *)((u64)v1->parentID + 4 * v40 + 32) == v1->cursor_old)
        {
          v1->cursor_parent = v40;
          break;
        }
        ++v40;
        v1->cursor_parent = -1;
      }
      v42 = v1->menu_draw;
      v42[8] = v1->top;
      v43 = v1->menu_Before;
      v42[9] = v1->top + 1;
      v42[10] = v1->top + 2;
      v42[11] = v1->top + 3;
      v42[12] = v1->top + 4;
      v42[13] = v1->top + 5;
      v42[14] = v1->top + 6;
      v42[15] = v1->top + 7;
      v42[16] = v1->top + 8;
      v42[17] = v1->top + 9;
      v42[18] = v1->top + 10;
      v42[19] = v1->top + 11;
      v44 = v42[8] - 1;
      if (v44 < 1)
        v44 = -1;
      *(u32 *)(v43 + 32) = v44;
      v45 = v42[19];
      v46 = v1->menu_Before;
      if (v45 + 1 < v1->menu_num)
        v47 = v45 + 1;
      else
        v47 = -1;
      *(u32 *)((u64)v1->menu_After + 32) = v47;
      v48 = v42[8] - 2;
      if (v48 < 1)
        v48 = -1;
      *(u32 *)((u64)v1->menu_Before + 36) = v48;
      v49 = v42[19] + 2;
      if (v49 >= v1->menu_num)
        v49 = -1;
      *(u32 *)((u64)v1->menu_After + 36) = v49;
      v50 = v42[8] - 3;
      if (v50 < 1)
        v50 = -1;
      *(u32 *)((u64)v1->menu_Before + 40) = v50;
      v51 = v42[19] + 3;
      if (v51 >= v1->menu_num)
        v51 = -1;
      *(u32 *)((u64)v1->menu_After + 40) = v51;
      v52 = v42[8] - 4;
      if (v52 < 1)
        v52 = -1;
      *(u32 *)((u64)v1->menu_Before + 44) = v52;
      v53 = v42[19] + 4;
      if (v53 >= v1->menu_num)
        v53 = -1;
      *(u32 *)((u64)v1->menu_After + 44) = v53;
      v54 = v42[8] - 5;
      if (v54 < 1)
        v54 = -1;
      *(u32 *)((u64)v1->menu_Before + 48) = v54;
      v55 = v42[19] + 5;
      if (v55 >= v1->menu_num)
        v55 = -1;
      *(u32 *)((u64)v1->menu_After + 48) = v55;
      v56 = v42[8] - 6;
      if (v56 < 1)
        v56 = -1;
      *(u32 *)((u64)v1->menu_Before + 52) = v56;
      v57 = v42[19] + 6;
      if (v57 >= v1->menu_num)
        v57 = -1;
      *(u32 *)((u64)v1->menu_After + 52) = v57;
      v58 = v42[8] - 7;
      if (v58 < 1)
        v58 = -1;
      *(u32 *)((u64)v1->menu_Before + 56) = v58;
      v59 = v42[19] + 7;
      if (v59 >= v1->menu_num)
        v59 = -1;
      *(u32 *)((u64)v1->menu_After + 56) = v59;
      v60 = v42[8] - 8;
      if (v60 < 1)
        v60 = -1;
      *(u32 *)((u64)v1->menu_Before + 60) = v60;
      v61 = v42[19] + 8;
      if (v61 >= v1->menu_num)
        v61 = -1;
      *(u32 *)((u64)v1->menu_After + 60) = v61;
      v62 = v42[8] - 9;
      if (v62 < 1)
        v62 = -1;
      *(u32 *)((u64)v1->menu_Before + 64) = v62;
      v63 = v42[19] + 9;
      if (v63 >= v1->menu_num)
        v63 = -1;
      *(u32 *)((u64)v1->menu_After + 64) = v63;
      v64 = v42[8] - 10;
      if (v64 < 1)
        v64 = -1;
      *(u32 *)((u64)v1->menu_Before + 68) = v64;
      v65 = v42[19] + 10;
      if (v65 >= v1->menu_num)
        v65 = -1;
      *(u32 *)((u64)v1->menu_After + 68) = v65;
      v66 = v42[8] - 11;
      if (v66 < 1)
        v66 = -1;
      *(u32 *)((u64)v1->menu_Before + 72) = v66;
      v67 = v42[19] + 11;
      if (v67 >= v1->menu_num)
        v67 = -1;
      *(u32 *)((u64)v1->menu_After + 72) = v67;
      v68 = v42[8] - 12;
      if (v68 < 1)
        v68 = -1;
      *(u32 *)(v46 + 76) = v68;
      v69 = v42[19] + 12;
      if (v69 >= v1->menu_num)
        v69 = -1;
      *(u32 *)((u64)v1->menu_After + 76) = v69;
      v70 = *(u32 *)(v46 + 32);
      if ((v70 & 0x80000000) == 0)
      {
        if ((u32)v70 < 0xC)
        {
          v75 = 0;
          while ((s64)v75 < MENU_DRAW_MAX)
          {
            if (v75 > v70)
              v76 = -1;
            else
              v76 = v75;
            v77 = (u64)v1->menu_Before + 4 * v75++;
            *(u32 *)(v77 + 32) = v76;
          }
        }
        else
        {
          v71 = 0;
          v72 = (v46 + 76);
          while (v71 < MENU_DRAW_MAX)
          {
            v73 = (u64)v1->menu_Before + 4 * v71++;
            v74 = *v72--;
            *(u32 *)(v73 + 32) = v74;
          }
        }
      }
      selMenuSetScrollBar(bookUI, v1->menu_num, 0);
      selMenuScrollBarMove(bookUI, v1->menu_num, 0, 0);
      if (evtBitCheck(42))
      {
        Instance = get_Instance(0);
        ItfButtonGuideActive(Instance, 1, 0);
        v80 = get_Instance(0);
        ItfButtonGuideSet(v80, 0, 0);
        if (v1->cursor_parent != -1)
        {
          if (v81)
          {
            ButtonLineHelpDispSet(1);
LABEL_148:
            ButtonLineHelpTextSet(dbookMenuHlepText[v1->cursor_parent], 0, 1, 0xA09DC380, 1);
            return;
          }
          else
          {
            ButtonLineHelpDispSet(1);
            goto LABEL_148;
          }
          goto LABEL_148;
        }
        if (!v81)
        ButtonLineHelpDispSet(0);
      }
      return;
    default:
      goto LABEL_65;
  }
}

// 0x1bedf90
void MenuProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 monitor_high;

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
  monitor_high = HIDWORD(ProcessData[2].monitor);
  if ((monitor_high & 1) == 0)
  {
    LOWORD(ProcessData[3].klass) = 0;
    HIDWORD(ProcessData[2].monitor) = monitor_high | 1;
    LOBYTE(ProcessData[2].monitor) = 1;
  }
}

// 0x1bfaf20
bool MenuProcessCheck(void) {
  dds3ProcessID_t *p_g_mainPID;

  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 1;
    }
  }
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = 0;
  return 0;
}

// 0x1bfb090
void DisableSelect(s32 MenuID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;

  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  klass = ProcessData[1].klass;
  itfMenuSetFlagMenu(klass, MenuID, 2, 0);
}

// 0x1bf2b40
s32 CheckPageEnable(s32 nowIndex, s32 nextIndex) {
  s64 v6;
  DITECTIVEBOOK_CLASS *v9;
  s32 v10;
  DITECTIVEBOOK_CLASS *v11;

  v6 = (u32)(nextIndex + nowIndex);
  if ((s32)v6 < 1)
    return 0;
  if ((s32)v6 >= SLODWORD(BOOKPAGE->max_length))
    return 0;
  if (nextIndex != -1)
  {
    if (nextIndex != 1)
      return 0;
    while (1)
    {
      if (v6 >= SLODWORD(BOOKPAGE->max_length))
        return 0;
      if (MenuParentID[nowIndex] == MenuParentID[v6])
      {
        v9 = BOOKPAGE[v6];
        if (!v9->type)
          goto LABEL_13;
        v9 = BOOKPAGE[v6];
        if (v9->parentID == -1)
          return 0;
        v9 = BOOKPAGE[v6];
        if (evtBitCheck(v9->upDateTextFlag[0]))
          return 1;
        if (!BOOKPAGE[v6]->upDateTextFlag[0])
          return 1;
      }
LABEL_13:
      ++v6;
    }
  }
  v10 = v6 + 1;
  while (1)
  {
    if (MenuParentID[nowIndex] != MenuParentID[v6])
      goto LABEL_34;
    v11 = BOOKPAGE[v6];
    if (!v11->type)
      goto LABEL_34;
    v11 = BOOKPAGE[v6];
    if (v11->parentID == -1)
      return 0;
    v11 = BOOKPAGE[v6];
    if (evtBitCheck(v11->upDateTextFlag[0]))
      return 1;
    if (!BOOKPAGE[v6]->upDateTextFlag[0])
      return 1;
LABEL_34:
    --v10;
    --v6;
    if (v10 <= 1)
      return 0;
  }
}

// 0x1bfb220
s32 CheckNEXTEnable(s32 nowIndex, s32 nextIndex) {
  s32 v6;
  s32 result;
  s32 size;
  Il2CppObject *v10;
  bool v12;
  Il2CppObject *Item;

  v6 = nextIndex + nowIndex;
  result = 0;
  if (v6 < 1)
    return result;
  size = DestTextIDList->_size;
  if (v6 < size)
  {
    if (nextIndex == -1)
    {
      while (1)
      {
        Item = _get_Item(DestTextIDList, v6);
        if (!op_Equality(Item, "", 0))
        {
          if (_get_Item(DestTextIDList, v6))
          {
            break;
          }
        }
        v12 = __OFSUB__(v6--, 1);
        if ((v6 < 0) ^ v12 | (v6 == 0))
          return 0;
      }
    }
    else
    {
      if (nextIndex != 1)
        return 0;
      while (1)
      {
        v10 = _get_Item(DestTextIDList, v6);
        if (!op_Equality(v10, "", 0))
        {
          if (_get_Item(DestTextIDList, v6))
          {
            break;
          }
        }
        if (++v6 >= size)
          return 0;
      }
    }
    return 1;
  }
  return result;
}

// 0x1bfb450
s32 CheckMovePrev(void) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v4;
  s64 naturalAligment;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *v8;

  if (!g_mainPID)
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagBOOK_MENU_WORK_c **)(ProcessData)[1].next + naturalAligment - 1) != tagBOOK_MENU_WORK;
  }
  v6 = ProcessData[2];
  if (itfMenuGetCtrlType(ProcessData[2]) == 3)
    return 1;
  v8 = v4[2];
  return itfMenuGetCtrlType(v8) == 5;
}

// 0x1bf42f0
char *ChangeTextPLTF(char *text) {
  char *PlatformString;
  char *v4;
  char *v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  char *v11;
  char *v12;
  char *v13;
  char *v14;
  char *v15;

  PlatformString = itfGetPlatformString(0);
  v4 = Replace_54838864(text, "<PT 0>", PlatformString, 0);
  v5 = itfGetPlatformString(1);
  v6 = Replace_54838864(v4, "<PT 1>", v5, 0);
  v7 = itfGetPlatformString(2);
  v8 = Replace_54838864(v6, "<PT 2>", v7, 0);
  v9 = itfGetPlatformString(3);
  v10 = Replace_54838864(v8, "<PT 3>", v9, 0);
  v11 = itfGetPlatformString(4);
  v12 = Replace_54838864(v10, "<PT 4>", v11, 0);
  v13 = itfGetPlatformString(5);
  v14 = Replace_54838864(v12, "<PT 5>", v13, 0);
  v15 = itfGetPlatformString(6);
  return Replace_54838864(v14, "<PT 6>", v15, 0);
}

// 0x1bec8e0
void InitSeqHandle(bookSeqHandle_t *pSeqHandle) {
  bookSeqHandle_t *v2;

  v2 = Allocate(bookSeqHandle_t);
  _ctor(v2, 0);
}

// 0x1bfb620
static void CalcSeqHandle(s32 Mode, bookSeqUnit_t *pSeqUnit, bookSeqHandle_t *pSeqHandle, dds3ProcessID_t *ID) {
  bookSeqHandle_t *v5;
  s32 UnitCnt;
  s32 v9;
  bookInt32Delegate pDestroy;
  bookInt32Delegate pInit;
  s64 v13;
  s64 v14;
  bookSeqUnit_t *pUnit;
  Il2CppClass **v16;
  s32 v17;
  bookSeqUnit_t *v18;
  void **v19;
  bookSeqUnit_t *v20;
  void *v21;
  bookSeqHandle_t *v22;
  bookSeqUnit_t *v23;
  char *v24;

  v5 = pSeqHandle;
  if (pSeqHandle)
  {
    if (Mode)
    {
      if ((u32)(Mode - 3) >= 0xFFFFFFFE)
      {
        UnitCnt = v5->UnitCnt;
        if (UnitCnt)
        {
          v9 = UnitCnt - 1;
          if (Mode == 1)
          {
            pDestroy = v5->pUnit[v9]->pDestroy;
            if (pDestroy)
            {
              (pDestroy->invoke_impl)(pDestroy->method_code, ID, pDestroy->ID);
              v5 = pSeqHandle;
              v9 = pSeqHandle->UnitCnt - 1;
            }
          }
          v5->UnitCnt = v9;
        }
      }
    }
    else
    {
      pInit = pSeqUnit->pInit;
      if (pInit)
      {
        if (pSeqUnit->pDestroy)
        {
          LODWORD(v13) = v5->UnitCnt;
          if ((s32)v13 < 1)
          {
LABEL_15:
            pUnit = v5->pUnit;
            v5->UnitCnt = v13 + 1;
            v16 = &pUnit->obj.klass + (s32)v13;
            v16[4] = pSeqUnit;
            if ((pSeqUnit->Stat & 0x20000) != 0)
            {
              v17 = pSeqHandle->UnitCnt;
              if (v17 >= 2)
              {
                v18 = pSeqHandle->pUnit;
                v19 = &v18[v17 - 1];
                v20 = v18[v17 - 2];
                v21 = *v19;
                sub_C80(v18, v20);
                *v19 = v20;
                v22 = pSeqHandle;
                v23 = pSeqHandle->pUnit;
                LODWORD(v19) = v22->UnitCnt;
                sub_C80(v23, v21);
                v24 = (char *)v23 + 8 * (s32)v19 - 16;
                *((u64 *)v24 + 4) = v21;
              }
            }
            (pSeqUnit->pInit->invoke_impl)(pSeqUnit->pInit->method_code, ID, pSeqUnit->pInit->method);
          }
          else
          {
            v14 = 0;
            while (!op_Equality(pSeqUnit->pInit, v5->pUnit[v14]->pInit, 0))
            {
              v5 = pSeqHandle;
              ++v14;
              v13 = pSeqHandle->UnitCnt;
              if (v14 >= v13)
                goto LABEL_15;
            }
          }
        }
        else
        {
          (pInit->invoke_impl)(pInit->method_code, ID, pInit->method);
        }
      }
    }
  }
}

// 0x1beded0
void SeqDestroyAll(bookSeqHandle_t *pSeqHandle, dds3ProcessID_t *ID) {
  s32 i;
  bookInt32Delegate pDestroy;

  for (i = pSeqHandle->UnitCnt; i; pSeqHandle->UnitCnt = i)
  {
    i = pSeqHandle->UnitCnt;
    if (!i)
      break;
    pDestroy = pSeqHandle->pUnit[--i]->pDestroy;
    if (pDestroy)
    {
      (pDestroy->invoke_impl)(pDestroy->method_code, ID, pDestroy->method);
      i = pSeqHandle->UnitCnt - 1;
    }
  }
}

// 0x1bef690
dds3ProcessFunc_t SeqChange(bookSeqHandle_t *pSeqHandle, bookSeqUnit_t *pSeqUnit, s32 Mode, dds3ProcessID_t *ID) {
  dds3ProcessFunc_t v5;
  bookSeqUnit_t *v9;
  s64 Stat;
  bookInt32Delegate pCheck;
  s64 v12;
  s32 v13;
  char v14;
  dds3ProcessFunc_t pCalc;
  dds3ProcessFunc_t v18;
  s32 UnitCnt;
  bookSeqUnit_t *pLastSeqUnit;
  bookSeqUnit_t *v21;
  bookSeqUnit_t *v22;
  bookSeqUnit_t *v23;
  dds3ProcessFunc_t pUpdate;
  bookSeqHandle_t *pSeqHandlea;

  v5 = (dds3ProcessFunc_t)ID;
  pSeqHandlea = pSeqHandle;
  if (!v5)
    return v5;
  v9 = pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = v9->Stat;
  if ((Stat & 0x400000) != 0)
    return 0;
  if (Mode != 2)
  {
    if (Mode != 1)
    {
      if (!Mode)
      {
        pCheck = v9->pCheck;
        v12 = Stat | 0x100000;
        v9->Stat = v12;
        if (pCheck && (v13 = (pCheck->invoke_impl)(pCheck->method_code, v5, pCheck->ID), v9 = pSeqUnit, v12 = pSeqUnit->Stat, !v13))
        {
          if ((v12 & 0x10001) != 1)
          {
LABEL_34:
            if ((v12 & 1) == 0)
              return 0;
            v9->Stat = v12 | 0x400000;
            pCalc = v9->pCalc;
            goto LABEL_38;
          }
          v14 = 1;
        }
        else
        {
          if ((v12 & 0x10000) != 0)
            goto LABEL_36;
          v14 = 0;
        }
        CalcSeqHandle(0, v9, pSeqHandlea, v5);
        v9 = pSeqUnit;
        v12 = pSeqUnit->Stat | 0x10000;
        pSeqUnit->Stat = v12;
        if ((v14 & 1) != 0)
          goto LABEL_34;
LABEL_36:
        v18 = v9->pCalc;
        v9->Stat = v12 | 0x200000;
        return v18;
      }
      return 0;
    }
    if ((Stat & 0x100000) == 0)
      return 0;
    if ((Stat & 0x200000) != 0)
      return v9->pDraw;
    if ((Stat & 1) == 0)
      return 0;
    v9->Stat = Stat | 0x400000;
    pCalc = v9->pDraw;
LABEL_38:
    (pCalc->invoke_impl)(pCalc->method_code, v5, pCalc->ID);
    pSeqUnit->Stat &= ~0x400000u;
    return 0;
  }
  if ((Stat & 0x100000) == 0)
    return 0;
  if ((Stat & 0x200000) == 0)
  {
    if ((Stat & 1) == 0)
      return 0;
    v9->Stat = Stat | 0x400000;
    pCalc = v9->pUpdate;
    goto LABEL_38;
  }
  if ((Stat & 0x20000) != 0)
  {
    if ((Stat & 0x40000) != 0)
    {
      if (pSeqHandle)
      {
        UnitCnt = pSeqHandle->UnitCnt;
        if (UnitCnt)
          pSeqHandle->UnitCnt = UnitCnt - 1;
      }
    }
    else
    {
      CalcSeqHandle(1, 0, pSeqHandlea, v5);
    }
  }
  pLastSeqUnit = pSeqHandle->pLastSeqUnit;
  v21 = pLastSeqUnit[1];
  pSeqUnit->Stat &= 0xFFFFFFFF0000FFFFLL;
  sub_C80(pLastSeqUnit, v21);
  pLastSeqUnit[0] = v21;
  v22 = pSeqHandle->pLastSeqUnit;
  v23 = pSeqUnit;
  sub_C80(v22, pSeqUnit);
  v22[1] = v23;
  pUpdate = pSeqUnit->pUpdate;
  pSeqUnit = 0;
  return pUpdate;
}

// 0x1bf1220
void SeqJump(bookSeqUnit_t *pCurrentSeqUnit, bookSeqUnit_t *pSeqUnit) {
  bookSeqUnit_t *v4;

  v4 = pSeqUnit;
  pCurrentSeqUnit = v4;
  pSeqUnit->Stat = LOWORD(pSeqUnit->Stat);
}

// 0x1bf2b00
void SeqJumpAndFree(bookSeqUnit_t *pCurrentSeqUnit, bookSeqUnit_t *pSeqUnit) {
  bookSeqUnit_t *v4;

  v4 = pSeqUnit;
  pCurrentSeqUnit = v4;
  pSeqUnit->Stat = LOWORD(pSeqUnit->Stat) | 0x20000;
}

// 0x1bf5700
void PanelTextCtrl(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *v4;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  PanelTextCtrlSub(v4);
}

// 0x1bfb820
static void PanelTextCtrlSub(void *wk) {
  s32 v5;
  s32 v6;

  if (!PANEL02_ScrollBarActiveChack(bookUI, 0))
    return;
  v5 = RightStickCtrl();
  v6 = wk->type_save[wk->cursor];
  if ((u32)(v6 - 1) < 2)
  {
LABEL_12:
    PANEL02_TextScrollNew(bookUI, v5, 0);
    return;
  }
  if (v6 != 6)
  {
    if (v6 != 7)
      return;
    goto LABEL_12;
  }
  PANELFILE_TextScrollNew(bookUI, v5, 0);
}

// 0x1bf6760
void PANEL2Process(void *wk) {
  s32 nextDestNowPage;
  void *Instance;
  s32 QuestMapNo;
  s64 cursor;
  bool active;
  char **v23;
  s32 v24;
  bool v28;
  bool v31;
  char **v32;
  char **v33;

  switch (wk->textChangeStep)
  {
    case 0:
      PANEL02_TextScrollReset(bookUI, 0);
      PANEL02_SetActive(bookUI, 1, 0);
      PANEL02_AlphaCtrl(bookUI, 0, 0);
      goto LABEL_33;
    case 1:
      PANEL02_SpriteAssetCtrl(bookUI, 1, 0);
      if (wk->id_save[wk->cursor] == 15)
      {
        nextDestNowPage = wk->nextDestNowPage;
        DrawPanelMessage_IDNEXT(nextDestNowPage);
      }
      else
      {
        if (QuestFlag)
        {
          DrawQUESTPANELMessage(QUESTPAGE[wk->id_save[wk->cursor]], QUEST_READ_FLAG[wk->cursor_ID]->CLEAR_FLAG);
        }
        else
        {
          DrawPANELMessage(BOOKPAGE[wk->id_save[wk->cursor]]);
        }
      }
      TextTagChange(bookUI, 2, 0, 0);
LABEL_33:
      ++wk->textChangeStep;
      return;
    case 2:
      TagImageInsert(bookUI, 0);
      goto LABEL_33;
    case 3:
      PANEL02_TextScrollReset(bookUI, 0);
      goto LABEL_33;
    case 4:
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      if (!QuestFlag)
        goto LABEL_51;
      QuestMapNo = GetQuestMapNo(QUESTPAGE[wk->id_save[wk->cursor]]);
      cursor = wk->cursor;
      if (wk->reward_save[cursor])
      {
        active = PANEL02_ScrollBarActiveChack(bookUI, 0);
        if (active)
          v23 = &"DBOOK05";
        else
          v23 = &"DBOOK04";
        goto LABEL_58;
      }
      v24 = QuestMapNo;
      cursor = wk->cursor;
      if (!QUESTPAGE[wk->id_save[cursor]]->StopFlag)
        goto LABEL_67;
      if (GBWK->GameFileInfo->chapter != 9)
      {
LABEL_67:
        v31 = PANEL02_ScrollBarActiveChack(bookUI, 0);
        if (v31)
        {
          v32 = &"DBOOK07";
          v33 = &"DBOOK03";
        }
        else
        {
          v32 = &"DBOOK06";
          v33 = &"DBOOK02";
        }
        if (v24)
          v23 = v32;
        else
          v23 = v33;
        goto LABEL_58;
      }
LABEL_51:
      v28 = PANEL02_ScrollBarActiveChack(bookUI, 0);
      if (v28)
        v23 = &"DBOOK03";
      else
        v23 = &"DBOOK02";
LABEL_58:
      ButtonGuideDispSet(*v23, 0, 90);
      ButtonLineHelpDispSet(0);
      PANEL02_AlphaCtrl(bookUI, 1, 0);
      wk->change_flag = 1;
      return;
    default:
      return;
  }
}

// 0x1bf6d40
void PANEL5Process(void *wk) {
  void *Instance;

  switch (wk->textChangeStep)
  {
    case 0:
      PANEL05_SetActive(bookUI, 1, 0);
      PANEL05_AlphaCtrl(bookUI, 0, 0);
      goto LABEL_13;
    case 1:
      wk->textChangeStep = 2;
      break;
    case 2:
      PANEL05_ImageSet(bookUI, BOOKPAGE[wk->id_save[wk->cursor]]->imgNum, 0);
LABEL_13:
      ++wk->textChangeStep;
      break;
    case 3:
      wk->textChangeStep = 4;
      break;
    case 4:
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      ButtonGuideDispSet("DBOOK02", 0, 90);
      ButtonLineHelpDispSet(0);
      PANEL05_AlphaCtrl(bookUI, 1, 0);
      wk->change_flag = 1;
      break;
    default:
      return;
  }
}

// 0x1bf6f90
void PANELFILEProcess(void *wk) {
  void *Instance;
  char **v13;

  switch (wk->textChangeStep)
  {
    case 0:
      PANELFILE_TextScrollReset(bookUI, 0);
      PANELFILE_SetActive(bookUI, 1, 0);
      PANELFILE_AlphaCtrl(bookUI, 0, 0);
      DrawPANELMessage(BOOKPAGE[wk->id_save[wk->cursor]]);
      goto LABEL_18;
    case 1:
      TextTagChange(bookUI, 2, 0, 0);
      goto LABEL_18;
    case 2:
      TagImageInsert(bookUI, 0);
      goto LABEL_18;
    case 3:
      PANELFILE_TextScrollReset(bookUI, 0);
LABEL_18:
      ++wk->textChangeStep;
      return;
    case 4:
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      if (PANEL02_ScrollBarActiveChack(bookUI, 0))
      {
        goto LABEL_23;
      }
      goto LABEL_9000;
      if (PANEL02_ScrollBarActiveChack(bookUI, 0))
      {
LABEL_23:
        if (QuestFlag)
          v13 = &"DBOOK08";
        else
          v13 = &"DBOOK03";
        goto LABEL_30;
      }
LABEL_9000:
      v13 = &"DBOOK02";
LABEL_30:
      ButtonGuideDispSet(*v13, 0, 90);
      ButtonLineHelpDispSet(0);
      PANELFILE_AlphaCtrl(bookUI, 1, 0);
      wk->change_flag = 1;
      return;
    default:
      return;
  }
}

// 0x1bf7300
void TIPSProcess(void *wk) {
  void *Instance;
  char **v13;

  switch (wk->textChangeStep)
  {
    case 0:
      PANEL02_TextScrollReset(bookUI, 0);
      PANEL02_SetActive(bookUI, 1, 0);
      PANEL02_AlphaCtrl(bookUI, 0, 0);
      DrawPANELMessage(BOOKPAGE[wk->id_save[wk->cursor]]);
      goto LABEL_18;
    case 1:
      PANEL02_SpriteAssetCtrl(bookUI, 1, 0);
      TextTagChange(bookUI, 2, 1, 0);
      goto LABEL_18;
    case 2:
      TagImageInsertTIPS(bookUI, 0);
      goto LABEL_18;
    case 3:
      PANEL02_TextScrollReset(bookUI, 0);
LABEL_18:
      ++wk->textChangeStep;
      return;
    case 4:
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      if (PANEL02_ScrollBarActiveChack(bookUI, 0))
      {
        goto LABEL_23;
      }
      goto LABEL_9000;
      if (PANEL02_ScrollBarActiveChack(bookUI, 0))
      {
LABEL_23:
        if (QuestFlag)
          v13 = &"DBOOK08";
        else
          v13 = &"DBOOK03";
        goto LABEL_30;
      }
LABEL_9000:
      v13 = &"DBOOK02";
LABEL_30:
      ButtonGuideDispSet(*v13, 0, 90);
      ButtonLineHelpDispSet(0);
      PANEL02_AlphaCtrl(bookUI, 1, 0);
      wk->change_flag = 1;
      return;
    default:
      return;
  }
}

// 0x1bfb980
static s32 RightStickCtrl(void) {
  s32 v2;

  if (QuestFlag)
  {
    if (CHECK_PRESS(42004, 1))
      return 0;
    v2 = 1;
    if (CHECK_PRESS(42005, 1))
      return v2;
    return -1;
  }
  if (CHECK_PRESS(41236, 1))
    return 0;
  v2 = 1;
  if (CHECK_PRESS(41237, 1))
    return v2;
  return -1;
}

// 0x1bfbbf0
void ReceiptInit(void) {
  s64 i;
  s32 *bit_Table;
  s64 v5;
  receiptMainWork *wk_local;
  s32 *ID_Table;
  char *v9;
  receiptMainWork *v11;

  ImageSetActive(rcptwk, 0, 0);
  for (i = 8; ; ++i)
  {
    wk_local = wk;
    ID_Table = wk_local->ID_Table;
    if (i - 8 >= SLODWORD(ID_Table->max_length))
      break;
    wk_local = wk;
    ID_Table = wk_local->ID_Table;
    bit_Table = wk_local->bit_Table;
    v5 = 4 * i;
    *(u32 *)((char *)&ID_Table->obj.klass + v5) = 0;
    *(u32 *)((char *)&bit_Table->obj.klass + v5) = 0;
  }
  wk_local = wk;
  v9 = "";
  wk_local->pageName01 = "";
  wk_local->num = 0;
  v11 = wk;
  *(u64 *)&v11->ObjAlpha = 0;
  v11->posY = 0.0;
  *(u64 *)&StartPosX = 0;
  v11->cnt = 0;
  v11->step = 1;
  v11->SKIPFLAG = 0;
  ImageSetActive(rcptwk, 1, 0);
}

// 0x1bfc1c0
void ReceiptSet(s32 bit) {
  bool v3;
  s64 v8;

  v3 = evtBitCheck(bit);
  if (bit && !v3)
  {
    if ((u32)(bit - 2618) < 0xFFFFFFC6)
    {
LABEL_8:
      v8 = (s64)GBWK->EventBit + 4 * (bit / 32);
      *(u32 *)(v8 + 32) |= 1 << bit;
      GetID(bit);
      wk->bit_Table[wk->num++] = bit;
      return;
    }
    evtBitKityouItemAdd(bit);
    goto LABEL_8;
  }
}

// 0x1bfc430
void ReceiptStart(s32 mode) {
  u8 v2;

  v2 = mode;
  if (!wk->num)
    return;
  wk->SKIPFLAG = 0;
  wk->mode = v2;
  wk->step = 2;
}

// 0x1bfbeb0
void GetID(s32 bit) {
  s32 v4;
  s32 *ID_Table;
  s64 num;

  v4 = 0;
  do
  {
    if (v4 >= paneldata->_arrPanel->_size)
      break;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[0] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[1] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[2] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[3] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[4] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[5] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[6] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[7] == bit)
      goto LABEL_35;
    if (GetTblDate(paneldata, v4, 0)->upDateTextFlag[8] == bit)
    {
LABEL_35:
      ID_Table = wk->ID_Table;
      num = wk->num;
      ID_Table[num] = GetTblDate(paneldata, v4, 0)->ID;
    }
    ++v4;
  }
  while (!wk->ID_Table[wk->num]);
}

// 0x1bfc500
void Receipt_ProcessStart(void) {
  dds3ProcessFunc_t v1;

  v1 = Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_DitectiveBook_Receipt_Process__, 0);
  dds3StartProcess("dbookReceiptMain", 1031, 0, 0, v1, 0, wk);
}

// 0x1bfc600
dds3ProcessFunc_t Receipt_Process(dds3ProcessID_t *PID) {
  receiptMainWork *wk_local;
  u32 step;
  void *Asset;
  s64 naturalAligment;
  void *v13;
  receiptMainWork *v16;
  s32 mode;
  s32 v18;
  s32 v19;
  receiptMainWork *v20;
  f32 ObjAlpha;
  f32 v22;
  char v23;
  s32 v24;
  f32 v25;
  f32 v26;
  u32 v28;
  s32 cnt;
  bool v32;
  receiptMainWork *v34;
  char *v35;
  char *v36;
  receiptMainWork *v37;
  receiptMainWork *v38;
  void *v40;
  void *p_paneldata;
  bool v42;
  bool v45;
  u32 v48;
  void *v52;

  wk_local = wk;
  step = wk_local->step;
  if (step > 9)
    return 0;
  switch (step)
  {
    case 0u:
      Load(Dependent, dbookAssetKey, dbookAssetKey);
      LoadSyncAll(_Ctrl_k__BackingField, 0);
      Asset = LoadAsset(_Ctrl_k__BackingField, dbookAssetKey, dbookPanelDataTableName, 0);
      if (Asset)
      {
        if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
        {
          if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DitectiveBookPanelDataTable)
            v13 = Asset;
          else
            v13 = 0;
        }
        else
        {
          v13 = 0;
        }
        paneldata = (void *)v13;
        p_paneldata = &paneldata;
        if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
        {
          if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DitectiveBookPanelDataTable)
            v40 = Asset;
          else
            v40 = 0;
        }
        else
        {
          v40 = 0;
        }
      }
      else
      {
        v40 = 0;
        p_paneldata = &paneldata;
        p_paneldata = 0;
      }
      InitBaseImage(rcptwk, 0);
      v52 = Dependent;
      wk->step = 1;
      Unload(v52, dbookAssetKey, 0);
      return 0;
    case 2u:
      v16 = wk;
      mode = v16->mode;
      if (mode != 2)
      {
        if (mode != 1)
          goto LABEL_94;
        v18 = -390;
        v19 = -1010630656;
        v16 = wk;
LABEL_93:
        StartPosY = v18;
        LODWORD(v16->posY) = v19;
        StartPosX = 1500;
        v16->posX = 1276.0;
LABEL_94:
        v42 = CheckBit();
        if (v42)
        {
          v45 = CheckExistence(rcptwk, 0);
          if (v45)
          {
            wk_local = wk;
            if (wk_local->SKIPFLAG)
            {
              if (!v48)
              {
                wk_local = wk;
              }
              v23 = 7;
            }
            else
            {
              if (!v48)
              {
                wk_local = wk;
              }
              v23 = 3;
            }
          }
          else
          {
            v23 = 8;
            wk_local = wk;
          }
          goto LABEL_143;
        }
        wk_local = wk;
LABEL_107:
        v23 = 1;
LABEL_143:
        wk_local->step = v23;
        return 0;
      }
      v18 = 750;
      v19 = 1144750080;
      goto LABEL_93;
    case 3u:
      if (wk_local->cnt)
        goto LABEL_28;
      goto LABEL_9003;
      if (wk->cnt)
      {
LABEL_28:
        goto LABEL_29;
      }
LABEL_9003:
      AnimSet(rcptwk, 1, 0);
LABEL_29:
      v20 = wk;
      ObjAlpha = v20->ObjAlpha;
      ++v20->cnt;
      v22 = ObjAlpha + 0.125;
      v20->ObjAlpha = v22;
      if (v22 > 0.95)
      {
        v20 = wk;
        v20->ObjAlpha = 1.0;
      }
      ImageDraw(rcptwk, wk->posY, 0);
      wk_local = wk;
      if (wk_local->ObjAlpha != 1.0)
        return 0;
      wk_local = wk;
      wk_local->cnt = 0;
      v23 = 4;
      goto LABEL_143;
    case 4u:
      v24 = wk_local->cnt + 1;
      wk_local->cnt = v24;
      if (v24 != 140)
        return 0;
      wk_local = wk;
      v23 = 5;
      wk_local->cnt = 0;
      goto LABEL_143;
    case 5u:
      AnimSet(rcptwk, 2, 0);
      v23 = 6;
      wk_local = wk;
      goto LABEL_143;
    case 6u:
      wk_local = wk;
      v25 = wk_local->ObjAlpha;
      ++wk_local->cnt;
      v26 = v25 + -0.125;
      wk_local->ObjAlpha = v26;
      if (v26 < 0.05)
      {
        wk_local = wk;
        wk_local->ObjAlpha = 0.0;
      }
      ImageDraw(rcptwk, wk->posY, 0);
      wk_local = wk;
      if (wk_local->ObjAlpha != 0.0)
        return 0;
      goto LABEL_56;
    case 7u:
      if (wk_local->cnt)
        goto LABEL_59;
      goto LABEL_9004;
      if (wk->cnt)
      {
LABEL_59:
        goto LABEL_60;
      }
LABEL_9004:
      AnimSet(rcptwk, 3, 0);
LABEL_60:
      ImageDraw(rcptwk, wk->posY, 0);
      wk_local = wk;
      cnt = wk_local->cnt;
      if (cnt == 20)
      {
        if (!v28)
        {
          wk_local = wk;
        }
LABEL_56:
        wk_local->cnt = 0;
        v23 = 9;
        goto LABEL_143;
      }
      if (!v28)
      {
        wk_local = wk;
        cnt = wk_local->cnt;
      }
      wk_local->cnt = cnt + 1;
      return 0;
    case 8u:
      if (wk_local->cnt)
        goto LABEL_65;
      goto LABEL_9005;
      if (wk->cnt)
      {
LABEL_65:
        goto LABEL_66;
      }
LABEL_9005:
      InitBaseImage(rcptwk, 0);
LABEL_66:
      ++wk->cnt;
      v32 = CheckExistence(rcptwk, 0);
      if (v32)
      {
        v34 = wk;
        v34->cnt = 0;
        v34->step = 3;
LABEL_70:
        wk_local = wk;
        if (wk_local->cnt == 5)
          goto LABEL_77;
        return 0;
      }
      {
        goto LABEL_70;
      }
      wk_local = wk;
      if (wk_local->cnt == 5)
      {
LABEL_77:
        wk_local = wk;
        wk_local->cnt = 0;
        goto LABEL_107;
      }
      return 0;
    case 9u:
      wk_local = wk;
      v35 = "";
      wk_local->pageName01 = "";
      wk_local->mode = 0;
      *(u64 *)&wk_local->cnt = 0;
      v36 = "";
      v37 = wk;
      v37->pageName02 = "";
      v37 = ((char *)v37 + 48);
      v37[-1].num = 0;
      v38 = wk;
      v38->step = 1;
      v38->ObjAlpha = 0.0;
      return 0;
    default:
      return 0;
  }
}

// 0x1bfd0d0
bool CheckBit(void) {
  s32 i;
  s64 num;
  s32 v4;
  s32 ID;
  s64 v7;
  s64 v8;
  s32 v10;
  DITECTIVEBOOK_CLASS *TblDate;
  DITECTIVEBOOK_CLASS *v14;
  bool v15;
  DITECTIVEBOOK_CLASS *v17;
  DITECTIVEBOOK_CLASS *v19;
  DITECTIVEBOOK_CLASS *v21;
  DITECTIVEBOOK_CLASS *v23;
  DITECTIVEBOOK_CLASS *v25;
  DITECTIVEBOOK_CLASS *v27;
  DITECTIVEBOOK_CLASS *v29;

  for (i = 0; ; ++i)
  {
    num = wk->num;
    if (i >= num)
      break;
    v4 = 0;
    while (1)
    {
      if (v4 >= paneldata->_arrPanel->_size)
        break;
      ID = GetTblDate(paneldata, v4, 0)->ID;
      if (ID == wk->ID_Table[i])
        break;
      ++v4;
    }
    if (GetTblDate(paneldata, wk->ID_Table[i], 0)->type)
    {
      v7 = 0;
      while (1)
      {
        v10 = GetTblDate(paneldata, v4, 0)->upDateTextFlag[v7];
        if (v10 == wk->bit_Table[i])
        {
          if (!v7)
            break;
          TblDate = GetTblDate(paneldata, v4, 0);
          if (evtBitCheck(TblDate->upDateTextFlag[0]))
          {
            v14 = GetTblDate(paneldata, v4, 0);
            v15 = evtBitCheck(v14->upDateTextFlag[1]);
            v8 = 0;
            if (v15)
            {
              v17 = GetTblDate(paneldata, v4, 0);
              if (evtBitCheck(v17->upDateTextFlag[2]))
              {
                v19 = GetTblDate(paneldata, v4, 0);
                if (evtBitCheck(v19->upDateTextFlag[3]))
                {
                  v21 = GetTblDate(paneldata, v4, 0);
                  if (evtBitCheck(v21->upDateTextFlag[4]))
                  {
                    v23 = GetTblDate(paneldata, v4, 0);
                    if (evtBitCheck(v23->upDateTextFlag[5]))
                    {
                      v25 = GetTblDate(paneldata, v4, 0);
                      if (evtBitCheck(v25->upDateTextFlag[6]))
                      {
                        v27 = GetTblDate(paneldata, v4, 0);
                        if (evtBitCheck(v27->upDateTextFlag[7]))
                        {
                          v29 = GetTblDate(paneldata, v4, 0);
                          if (evtBitCheck(v29->upDateTextFlag[8]))
                            v8 = 8;
                          else
                            v8 = 7;
                        }
                        else
                        {
                          v8 = 6;
                        }
                      }
                      else
                      {
                        v8 = 5;
                      }
                    }
                    else
                    {
                      v8 = 4;
                    }
                  }
                  else
                  {
                    v8 = 3;
                  }
                }
                else
                {
                  v8 = 2;
                }
              }
              else
              {
                v8 = 1;
              }
            }
          }
          else
          {
            v8 = 0xFFFFFFFFLL;
          }
          if (v7 == v8)
            break;
        }
        if (++v7 == 9)
          goto LABEL_4;
      }
      return i < num;
    }
LABEL_4:
    ;
  }
  return i < num;
}

// 0x1bfcfd0
void CheckMode(void) {
  s32 mode;
  s32 v5;
  s32 v6;

  mode = wk->mode;
  if (mode != 2)
  {
    if (mode != 1)
      return;
    v5 = -390;
    v6 = -1010630656;
    goto LABEL_11;
  }
  v5 = 750;
  v6 = 1144750080;
LABEL_11:
  StartPosY = v5;
  LODWORD(wk->posY) = v6;
  StartPosX = 1500;
  wk->posX = 1276.0;
}

// 0x1bfd520
void CheckALLReceipt(void) {
  ;
}

// 0x1bfd530
void InitReceiptWork(void *wk) {
  rcptwk = wk;
}

// 0x1bfd5a0
static bookData_t *QuestInit(void) {
  void *p_Dependent;
  void *Dependent_local;
  void *Asset;
  s64 naturalAligment;
  void *v9;
  bookData_t *v10;
  s32 *SeqParent;
  QUEST_TEXT_CLASS *v12;
  QUEST_TEXT_CLASS **p_QUESTPAGE;
  s64 i;
  QUEST_TEXT_CLASS *QUESTPAGE_local;
  QUEST_TEXT_CLASS *v17;
  QUEST_READ_FLAG_CLASS *v18;
  s64 j;
  QUEST_READ_FLAG_CLASS *v20;
  il2cpp_array_size_t max_length;
  s64 v23;
  QUEST_READ_FLAG_CLASS *m_Items;
  QUEST_READ_FLAG_CLASS *v25;
  bool *quest_readFlag;
  s32 *quest_updateFlag;
  char *v29;
  s64 v30;
  QUEST_READ_FLAG_CLASS *v31;
  QUEST_READ_FLAG_CLASS *v32;
  QUEST_READ_FLAG_CLASS **p_QUEST_READ_FLAG;
  QUEST_READ_FLAG_CLASS **v35;
  s64 v36;
  s32 *v37;
  s64 v38;
  QUEST_TEXT_CLASS *v39;
  s64 v40;
  QUEST_TEXT_CLASS *TblDate;
  QUEST_TEXT_CLASS *v42;
  s64 v44;
  s64 v45;
  s64 v46;
  Il2CppClass *v47;
  QUEST_TEXT_CLASS *v48;
  s64 k;
  s64 v51;
  QUEST_TEXT_CLASS *v54;
  bookSeqHandle_t *v56;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, QuestDataAssetKey, QuestDataAssetKey);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, QuestDataAssetKey, "QuestTextDataTable", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_QuestTextDataTable)
      v9 = Asset;
    else
      v9 = 0;
  }
  else
  {
    v9 = 0;
  }
  v10 = (bookData_t *)Allocate(bookData_t);
  _ctor(v10, 0);
  v10->nowHierarchy = 0;
  v10->MenuFade = 1;
  v10->BgmNo = 16;
  SeqParent = v10->SeqParent;
  *(u64 *)SeqParent = 0;
  *(u64 *)&SeqParent[2] = 0;
  v12 = NewSpecific(QUEST_TEXT_CLASS, 0x80u);
  p_QUESTPAGE = &QUESTPAGE;
  *p_QUESTPAGE = v12;
  for (i = 32; i != 1056; i += 8)
  {
    QUESTPAGE_local = QUESTPAGE;
    v17 = Allocate(QUEST_TEXT_CLASS);
    _ctor(v17, 0);
    *(Il2CppClass **)((char *)&QUESTPAGE_local->obj.klass + i) = v17;
  }
  if (!ProcessCheck())
    cmpLoadEffect();
  v18 = NewSpecific(QUEST_READ_FLAG_CLASS, 0x80u);
  for (j = 32; j != 1056; j += 8)
  {
    v20 = Allocate(QUEST_READ_FLAG_CLASS);
    _ctor(v20, 0);
    *(Il2CppClass **)((char *)&v18->obj.klass + j) = v20;
  }
  max_length = v18->max_length;
  if ((s32)max_length >= 1)
  {
    v23 = 0;
    m_Items = v18;
    do
    {
      v31 = m_Items[v23];
      v25 = m_Items[v23];
      quest_readFlag = GBWK->quest_readFlag;
      quest_updateFlag = GBWK->quest_updateFlag;
      v29 = (char *)GBWK->quest_rewardFlag + v23;
      v31->READ_FLAG = quest_readFlag[v23];
      v30 = (s64)quest_updateFlag + 4 * v23++;
      LOBYTE(v29) = v29[32];
      v25->REWARD_FLAG = 0;
      LODWORD(v30) = *(u32 *)(v30 + 32);
      v25->CLEAR_FLAG = (char)v29;
      v25->UPDATE_FLAG = v30;
    }
    while (v23 < (s32)max_length);
  }
  v32 = NewSpecific(QUEST_READ_FLAG_CLASS, max_length);
  p_QUEST_READ_FLAG = &QUEST_READ_FLAG;
  *p_QUEST_READ_FLAG = v32;
  v35 = &QUEST_READ_FLAG;
  *v35 = v18;
  v36 = NewSpecific(QUEST_TEXT_CLASS, v9->_arrText->_size);
  v37 = v36;
  if (v9->_arrText->_size >= 1)
  {
    v38 = 0;
    v39 = (v36 + 32);
    while (1)
    {
      TblDate = GetTblDate(v9, v38, 0);
      v42 = TblDate;
      if (TblDate)
      {
        if (!QueryInterface(TblDate, *(void **)(*(u64 *)v37 + 64)))
          break;
      }
      v39 = v42;
      v40 = (s64)*v39++;
      ++v38;
      *(u32 *)(v40 + 84) = 0;
      if (v38 >= v9->_arrText->_size)
        goto LABEL_54;
    }
  }
LABEL_54:
  if (v37[6] >= 1)
  {
    v44 = 0;
    v45 = 8;
    do
    {
      v47 = *(Il2CppClass **)&v37[v45];
      v48 = QUESTPAGE;
      if (!v47)
      *(Il2CppClass **)((char *)&v48->obj.klass + v45 * 4) = v47;
      ++v44;
      v46 = *(s64 *)((char *)&QUESTPAGE->obj.klass + v45 * 4);
      v45 += 2;
      *(u32 *)(v46 + 116) = 0;
    }
    while (v44 < v37[6]);
  }
  for (k = 4; ; ++k)
  {
    v54 = QUESTPAGE;
    if (k - 4 >= SLODWORD(v54->max_length))
      break;
    if (*(u32 *)(*((u64 *)&v54->obj.klass + k) + 44))
      goto LABEL_74;
    goto LABEL_9001;
    if (*(u32 *)(*((u64 *)&QUESTPAGE->obj.klass + k) + 44))
    {
LABEL_74:
      v51 = *((u64 *)&QUEST_READ_FLAG->obj.klass + k);
      *(u8 *)(v51 + 25) = GBWK->quest_rewardFlag[*(s32 *)(*((u64 *)&QUESTPAGE->obj.klass + k) + 44)];
      continue;
    }
LABEL_9001:
  }
  Init();
  v56 = Allocate(bookSeqHandle_t);
  _ctor(v56, 0);
  Unload(Dependent, QuestDataAssetKey, 0);
  return v10;
}

// 0x1bfddb0
dds3ProcessID_t *QuestProcessStart(void) {
  dds3ProcessID_t *v1;
  Il2CppObject *v3;
  dds3ProcessFunc_t v4;
  shutdownfuncDelegate v5;
  dds3ProcessID_t *started;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  *((u8 *)*((const MethodInfo *)DitectiveBook + 2).virtualMethodPointer + 136) = 1;
  v3 = QuestInit();
  v4 = Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_DitectiveBook_QuestLoad0Process__, 0);
  v5 = Allocate(shutdownfuncDelegate);
  _ctor(v5, 0, Method_Project_DitectiveBook_Destroy__, 0);
  started = dds3StartProcess("DitectiveBook_Calc", 1023, 0, 1, v4, v5, v3);
  GlobalPID = started;
  gCallFromMenu = 0;
  return started;
}

// 0x1bfdf60
static dds3ProcessFunc_t QuestLoad0Process(dds3ProcessID_t *PID) {
  void *p_Dependent;
  void *v5;
  dds3ProcessFunc_t v6;

  p_Dependent = &Dependent;
  v5 = p_Dependent;
  Load(v5, jms_asset_name, jms_asset_name);
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_DitectiveBook_QuestLoad1stProcess__, 0);
  return v6;
}

// 0x1bfe050
static dds3ProcessFunc_t QuestLoad1stProcess(dds3ProcessID_t *PID) {
  void *p_Dependent;
  void *Dependent_local;
  bool IsLoad;
  dds3ProcessFunc_t v7;
  void *v9;
  void *v11;
  dds3ProcessID_t *id;

  id = PID;
  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  IsLoad = IsLoad(Dependent_local, jms_asset_name, 0);
  v7 = 0;
  if (!IsLoad)
    return v7;
  dds3GetProcessData(id);
  v9 = &Dependent;
  v11 = v9;
  Unload(v11, jms_asset_name, 0);
  v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_DitectiveBook_QuestLoad2ndProcess__, 0);
  return v7;
}

// 0x1bfe220
static dds3ProcessFunc_t QuestLoad2ndProcess(dds3ProcessID_t *PID) {
  bookData_t *ProcessData;
  u8 Stat;
  dds3ProcessID_t *v12;
  s32 Flag;
  dds3ProcessFunc_t v15;
  bookData_t *v20;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v20 = ProcessData;
  LoadBgModel(DitectiveBook, v20);
  if (!CheckBgModel(v20))
    return 0;
  Stat = GBWK->Moon->Stat;
  moonSave = Stat;
  if ((Stat & 2) != 0)
  {
    evtMoonDisableDraw(1);
    v12 = id;
    goto LABEL_16;
  }
  v12 = id;
LABEL_16:
  StartEtcProcess(v12);
  QuestMenuProcessStart();
  Flag = ProcessData->Flag;
  if ((Flag & 0x800) != 0)
    ProcessData->Flag = Flag | 0x400;
  v15 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v15, 0, Method_Project_DitectiveBook_RootWaitCalcProcess__, 0);
  return v15;
}

// 0x1bfe490
void QuestMenuProcessStart(void) {
  void *v1;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_g_mainPID;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;
  s32 *parentID;
  s64 v10;
  s64 v11;
  void *child_save;
  void *v14;
  s64 v16;
  s64 v17;
  char *draw_text;
  s32 *type_save;
  s64 v20;
  s64 i;
  s32 flag;
  s32 cursor;
  s64 v29;
  s32 *menu_draw;
  s32 *menu_Before;
  s32 v33;
  s32 v34;
  s32 *v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  u64 v59;
  s64 v60;
  s32 *v61;
  s64 v62;
  s32 v63;
  u64 v64;
  s32 v65;
  s64 v66;
  void *Instance;
  void *v69;
  char *v70;

  v1 = Allocate(tagBOOK_MENU_WORK);
  _ctor(v1, 0);
  v70 = "";
  QuestLoadMap = 0;
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_DitectiveBook_Process__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_DitectiveBook_Shutdown__, 0);
  started = dds3StartProcess("jms_menu_main", 1023, 0, 0, v3, v4, v1);
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_DitectiveBook_QuestDrawProcess__, 0);
  v8 = dds3StartProcess("jms_menu_draw", 11029, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
  parentID = v1->parentID;
  if (SLODWORD(parentID->max_length) >= 1)
  {
    v10 = 0;
    v11 = 32;
    do
    {
      parentID[v10] = -1;
      child_save = v1->child_save;
      v14 = Allocate(tagBOOK_MENU_WORK_ChildSave);
      _ctor(v14, 0);
      *(Il2CppClass **)((char *)&child_save->obj.klass + v11) = v14;
      parentID = v1->parentID;
      ++v10;
      v11 += 8;
    }
    while (v10 < SLODWORD(parentID->max_length));
  }
  v16 = 0;
  v17 = 32;
  do
  {
    draw_text = v1->draw_text;
    if (!*(Il2CppClass **)((char *)&draw_text->obj.klass + v17))
    {
      *(Il2CppClass **)((char *)&draw_text->obj.klass + v17) = 0;
      type_save = v1->type_save;
      v20 = (s64)v1->id_save + 4 * v16;
      v1->parent_save[v16] = -1;
      *(u32 *)(v20 + 32) = -1;
      type_save[v16] = -1;
      v1->reward_save[v16] = 0;
    }
    ++v16;
    v17 += 8;
  }
  while (v16 != 256);
  MenuActiveOnOff(bookUI, 1, 0);
  SetCommand_Quest(v1);
  MenuAnimSetCtrl(bookUI, 0, 0);
  PANELMAIN_SetAnim_new(bookUI, 1, 0);
  PANEL_TitleObjCtrl(bookUI, QuestFlag, 0);
  PANEL_TitleQuestTextSet(bookUI, v70, 0, 0);
  for (i = 8; ; ++i)
  {
    if (i - 8 >= MENU_PARENT_MAX)
      break;
    if (*((u32 *)&v1->child_NumMax->obj.klass + i))
    {
      MenuChildAnimSetCtrl(bookUI, i - 8, 0, 0);
      MenuPosCtrl(bookUI, i - 8, *((u32 *)&v1->child_NumMax->obj.klass + i), 0, 1, 0);
    }
  }
  flag = v1->flag;
  v1->cursor = 0;
  v1->cursor_old = 0;
  v1->index = 0;
  v1->top = 0;
  v1->flag = flag | 4;
  cursor = 0;
  Menu_CursorChangeInit(bookUI, cursor, 0);
  v29 = 0;
  v1->cursor_old = v1->cursor;
  while (v29 < MENU_PARENT_MAX)
  {
    if (v1->parentID[v29] == v1->cursor_old)
    {
      v1->cursor_parent = v29;
      break;
    }
    ++v29;
    v1->cursor_parent = -1;
  }
  menu_draw = v1->menu_draw;
  menu_draw[0] = v1->top;
  menu_Before = v1->menu_Before;
  menu_draw[1] = v1->top + 1;
  menu_draw[2] = v1->top + 2;
  menu_draw[3] = v1->top + 3;
  menu_draw[4] = v1->top + 4;
  menu_draw[5] = v1->top + 5;
  menu_draw[6] = v1->top + 6;
  menu_draw[7] = v1->top + 7;
  menu_draw[8] = v1->top + 8;
  menu_draw[9] = v1->top + 9;
  menu_draw[10] = v1->top + 10;
  menu_draw[11] = v1->top + 11;
  v33 = menu_draw[0] - 1;
  if (v33 < 1)
    v33 = -1;
  menu_Before[0] = v33;
  v34 = menu_draw[11];
  v35 = v1->menu_Before;
  if (v34 + 1 < v1->menu_num)
    v36 = v34 + 1;
  else
    v36 = -1;
  v1->menu_After[0] = v36;
  v37 = menu_draw[0] - 2;
  if (v37 < 1)
    v37 = -1;
  v1->menu_Before[1] = v37;
  v38 = menu_draw[11] + 2;
  if (v38 >= v1->menu_num)
    v38 = -1;
  v1->menu_After[1] = v38;
  v39 = menu_draw[0] - 3;
  if (v39 < 1)
    v39 = -1;
  v1->menu_Before[2] = v39;
  v40 = menu_draw[11] + 3;
  if (v40 >= v1->menu_num)
    v40 = -1;
  v1->menu_After[2] = v40;
  v41 = menu_draw[0] - 4;
  if (v41 < 1)
    v41 = -1;
  v1->menu_Before[3] = v41;
  v42 = menu_draw[11] + 4;
  if (v42 >= v1->menu_num)
    v42 = -1;
  v1->menu_After[3] = v42;
  v43 = menu_draw[0] - 5;
  if (v43 < 1)
    v43 = -1;
  v1->menu_Before[4] = v43;
  v44 = menu_draw[11] + 5;
  if (v44 >= v1->menu_num)
    v44 = -1;
  v1->menu_After[4] = v44;
  v45 = menu_draw[0] - 6;
  if (v45 < 1)
    v45 = -1;
  v1->menu_Before[5] = v45;
  v46 = menu_draw[11] + 6;
  if (v46 >= v1->menu_num)
    v46 = -1;
  v1->menu_After[5] = v46;
  v47 = menu_draw[0] - 7;
  if (v47 < 1)
    v47 = -1;
  v1->menu_Before[6] = v47;
  v48 = menu_draw[11] + 7;
  if (v48 >= v1->menu_num)
    v48 = -1;
  v1->menu_After[6] = v48;
  v49 = menu_draw[0] - 8;
  if (v49 < 1)
    v49 = -1;
  v1->menu_Before[7] = v49;
  v50 = menu_draw[11] + 8;
  if (v50 >= v1->menu_num)
    v50 = -1;
  v1->menu_After[7] = v50;
  v51 = menu_draw[0] - 9;
  if (v51 < 1)
    v51 = -1;
  v1->menu_Before[8] = v51;
  v52 = menu_draw[11] + 9;
  if (v52 >= v1->menu_num)
    v52 = -1;
  v1->menu_After[8] = v52;
  v53 = menu_draw[0] - 10;
  if (v53 < 1)
    v53 = -1;
  v1->menu_Before[9] = v53;
  v54 = menu_draw[11] + 10;
  if (v54 >= v1->menu_num)
    v54 = -1;
  v1->menu_After[9] = v54;
  v55 = menu_draw[0] - 11;
  if (v55 < 1)
    v55 = -1;
  v1->menu_Before[10] = v55;
  v56 = menu_draw[11] + 11;
  if (v56 >= v1->menu_num)
    v56 = -1;
  v1->menu_After[10] = v56;
  v57 = menu_draw[0] - 12;
  if (v57 < 1)
    v57 = -1;
  v35[11] = v57;
  v58 = menu_draw[11] + 12;
  if (v58 >= v1->menu_num)
    v58 = -1;
  v1->menu_After[11] = v58;
  v59 = (u32)v35[0];
  if ((v59 & 0x80000000) == 0)
  {
    if ((u32)v59 < 0xC)
    {
      v64 = 0;
      while ((s64)v64 < MENU_DRAW_MAX)
      {
        if (v64 > v59)
          v65 = -1;
        else
          v65 = v64;
        v66 = (s64)v1->menu_Before + 4 * v64++;
        *(u32 *)(v66 + 32) = v65;
      }
    }
    else
    {
      v60 = 0;
      v61 = &v35[11];
      while (v60 < MENU_DRAW_MAX)
      {
        v62 = (s64)v1->menu_Before + 4 * v60++;
        v63 = *v61--;
        *(u32 *)(v62 + 32) = v63;
      }
    }
  }
  selMenuSetScrollBar(bookUI, v1->menu_num, 0);
  if (evtBitCheck(42))
  {
    Instance = get_Instance(0);
    ItfButtonGuideActive(Instance, 1, 0);
    v69 = get_Instance(0);
    ItfButtonGuideSet(v69, 0, 0);
    ButtonLineHelpDispSet(0);
  }
}

// 0x1bff520
dds3ProcessFunc_t QuestEndProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  LODWORD(ProcessData[8].klass) = 1;
  CursorInitFlag = -1;
  if (ProcessCheck())
  {
    goto LABEL_13;
  }
  cmpDeleteEffect();
  End();
LABEL_13:
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  if (((s64)ProcessData[1].klass & 0x40) == 0)
  {
    dds3FadeOut(0, 0, 0, 0x1Eu);
    LODWORD(ProcessData[1].klass) |= 0x40u;
    return 0;
  }
  if (!!dds3FadeCheck())
    return 0;
  if ((moonSave & 2) != 0)
    evtMoonEnableDraw();
  QuestProcessEnd();
  v11 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v11, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v11;
}

// 0x1bff880
void QuestProcessEnd(void) {
  UnityEngine_SceneManagement_Scene_o v6;
  UnityEngine_SceneManagement_Scene_o v11;

  v11.m_Handle = 0;
  ReturnQuestReadFlagData();
  Delete(0);
  dds3KillProcessName("DitectiveBook_Calc", 0);
  dds3KillProcessName("DitectiveBook_Draw", 0);
  dds3KillProcessName("DitectiveBook_Update", 0);
  v11.m_Handle = GetSceneByName(book_scene_name, 0).m_Handle;
  if (!IsValid((UnityEngine_SceneManagement_Scene_o)&v11, 0))
  {
    goto LABEL_10;
  }
  v6.m_Handle = v11.m_Handle;
  UnloadSceneAsync_61083440(v11, 0);
  book_scene_name = 0;
  scene_asyncLoad = 0;
LABEL_10:
  if (!QuestLoadMap)
  {
    goto LABEL_12;
  }
  fldJmsQuestMapLoad(fldGb->fieldID, -1);
  mapSetArea(fldGb->floorID);
LABEL_12:
  QuestLoadMap = 0;
}

// 0x1bffcf0
static dds3ProcessFunc_t QuestDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v3;
  dds3ProcessID_t *v4;
  dds3ProcessID_t *p_DBMPID;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  v3 = id;
  v4 = id;
  p_DBMPID = &DBMPID;
  p_DBMPID = id;
  if (!ProcessData)
  if ((BYTE4(ProcessData[2].monitor) & 4) != 0)
  {
    v9 = id;
    UniDrawMenu_Quest(v9);
  }
  return 0;
}

// 0x1bffe30
void UniDrawMenu_Quest(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *v4;
  char *v6;
  QUEST_READ_FLAG_CLASS *v13;
  s32 v15;
  s32 v18;
  void *p_bookUI;
  void *v23;
  s64 v24;
  s32 v25;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  v6 = "";
  if (evtBitCheck(42))
  {
    if (v4->change_flag)
    {
      GuideSet(v4);
      return;
    }
    if (v4->cursor_ID != -1)
    {
      PANEL_TitleQuestTextSet(bookUI, v4->draw_text[v4->cursor], v4->questID_save[v4->cursor], 0);
      DrawPanelCtrl(v4);
      AccessQuestReadFlag(v4->id_save[v4->cursor]);
      if (!QUESTPAGE[v4->id_save[v4->cursor]]->StopFlag)
        goto LABEL_61;
      if (GBWK->GameFileInfo->chapter == 9)
      {
        v13 = QUEST_READ_FLAG[v4->cursor_ID];
        if (!v13->READ_FLAG)
          goto LABEL_40;
        v13 = QUEST_READ_FLAG[v4->cursor_ID];
        if (v13->CLEAR_FLAG)
          goto LABEL_40;
        v15 = 7;
LABEL_39:
        ChildrenMenu_SetIconCtrl(bookUI, v4->cursor, v15, 0);
LABEL_40:
        CheckAllQuestParentReadFlag();
        v18 = v4->parent_save[v4->cursor];
        if (QUEST_READ_FLAG[v18 + 1]->READ_FLAG)
        {
          v18 = v4->parent_save[v4->cursor];
          if (!ParentMenu_GetIconColor(bookUI, v4->parentID[v18], 0))
          {
            p_bookUI = &bookUI;
            v23 = p_bookUI;
            v24 = v4->parent_save[v4->cursor];
            v25 = v4->parentID[v24];
            LODWORD(v24) = v4->parent_save[v4->cursor];
            ParentMenu_SetNewIcon(v23, v25, !QUEST_READ_FLAG[(s32)v24 + 1]->READ_FLAG, 6, 0);
          }
        }
        return;
      }
      else
      {
LABEL_61:
        if (!QUEST_READ_FLAG[v4->cursor_ID]->READ_FLAG)
          goto LABEL_40;
        if (ChildrenMenu_GetIconColor(bookUI, v4->cursor, 0))
          goto LABEL_40;
        v15 = 6;
        goto LABEL_39;
      }
      goto LABEL_39;
    }
    Instance = get_Instance(0);
    ItfButtonGuideActive(Instance, 1, 0);
    ButtonGuideDispSet("DBOOK01", 0, 90);
    DeleteInsertImages(bookUI, 0);
    PANEL02_SetMessage(bookUI, v6, 0, 0, 0, 0);
    PANEL_TitleQuestTextSet(bookUI, v6, 0, 0);
    v4->change_flag = 1;
  }
}

// 0x1bfee70
static void SetCommand_Quest(void *wk) {
  s32 v3;
  s64 v4;
  char *v6;
  char *v7;
  char *v9;
  s32 *v10;
  s32 v11;
  QUEST_TEXT_CLASS *v13;
  QUEST_TEXT_CLASS *QUESTPAGE_local;
  s64 v16;
  char *v17;
  char *LocalizeText;
  char *v19;
  char *v21;
  char *v22;
  s32 LanguageTYPE;
  char **v24;
  s32 v25;
  char *v26;
  char *v28;
  s64 v29;
  s64 v32;
  s64 v33;
  QUEST_TEXT_CLASS *v34;
  s64 v35;
  char *v37;
  char *v38;
  char *v41;
  s64 v45;
  s32 v47;
  void *v48;
  s32 v49;
  char v50;
  QUEST_TEXT_CLASS *v53;
  s64 v54;
  void *v57;

  v3 = 0;
  v4 = 5;
  while (1)
  {
    QUESTPAGE_local = QUESTPAGE;
    if (v4 - 4 >= SLODWORD(QUESTPAGE_local->max_length))
      break;
    v16 = *((u64 *)&QUESTPAGE_local->obj.klass + v4);
    if (*(u32 *)(v16 + 96) == -1)
      goto LABEL_5;
    if (*(u32 *)(v16 + 20))
      goto LABEL_15;
    goto LABEL_9000;
    if (*(u32 *)(*((u64 *)&QUESTPAGE->obj.klass + v4) + 20))
    {
LABEL_15:
      v17 = "";
      LocalizeText = GetLocalizeText("QUEST_TITLE_L0050", 1);
      v19 = Concat_54766928(v17, LocalizeText, 0);
      v21 = ToString_55996800((u32)*((u64 *)&QUESTPAGE->obj.klass + v4) + 44, "d2", 0);
      v22 = Concat_54766928(v19, v21, 0);
      LanguageTYPE = GetLanguageTYPE();
      v24 = &"　";
      if (LanguageTYPE != 2)
      {
        v25 = GetLanguageTYPE();
        v24 = &" ";
        if (v25 == 1)
          v24 = &"　";
      }
      v26 = Concat_54766928(v22, *v24, 0);
      v28 = *(char **)(*((u64 *)&QUESTPAGE->obj.klass + v4) + 104);
      v6 = GetLocalizeText(v28, 1);
      v7 = Concat_54766928(v26, v6, 0);
      v9 = ChangeTextPLTF(v7);
      v10 = *((s32 **)&QUESTPAGE->obj.klass + v4);
      SetMenu_Quest(wk, v10[4], v10[24], v9, v10[5], v11, v10[11]);
      v13 = QUESTPAGE[*(s32 *)(*((u64 *)&QUESTPAGE->obj.klass + v4) + 96)];
      ++v13->childMax;
      goto LABEL_5;
    }
LABEL_9000:
    v29 = (s64)secondHi + 4 * v3++;
    *(u32 *)(v29 + 32) = v4 - 4;
LABEL_5:
    ++v4;
  }
  CheckAllQuestParentReadFlag();
  CheckAllQuestParentClearFlag();
  v32 = 5;
  while (2)
  {
    v34 = QUESTPAGE;
    if (v32 - 4 < SLODWORD(v34->max_length))
    {
      v35 = *((u64 *)&v34->obj.klass + v32);
      if (*(u32 *)(v35 + 96) == -1)
      {
        v37 = *(char **)(v35 + 104);
        v38 = GetLocalizeText(v37, 1);
        v41 = ChangeTextPLTF(v38);
        {
          *(u32 *)(*((u64 *)&QUESTPAGE->obj.klass + v32) + 116) = 1;
        }
        else
        {
          *(u32 *)(*((u64 *)&QUESTPAGE->obj.klass + v32) + 116) = 1;
        }
        v33 = *((u64 *)&QUESTPAGE->obj.klass + v32);
        SetRootMenu_Quest(wk, *(u32 *)(v33 + 16), *(u32 *)(v33 + 84), v41);
      }
      ++v32;
      continue;
    }
    break;
  }
  MenuObjCtrl(bookUI, 16, 0, 0);
  v45 = 5;
  while (2)
  {
    v53 = QUESTPAGE;
    if (v45 - 4 < SLODWORD(v53->max_length))
    {
      if (*(u32 *)(*((u64 *)&QUESTPAGE->obj.klass + v45) + 96) != -1)
        goto LABEL_61;
      v54 = *((u64 *)&QUEST_READ_FLAG->obj.klass + v45);
      if (*(u8 *)(v54 + 16))
        goto LABEL_71;
      v47 = v45 - 4;
      v48 = bookUI;
      v49 = 5;
      v50 = *(u8 *)(*((u64 *)&QUEST_READ_FLAG->obj.klass + v45) + 16) == 0;
LABEL_60:
      ParentMenu_SetNewIconInit(v48, v47, v50, v49, 0);
LABEL_61:
      ++v45;
      continue;
LABEL_71:
      if (!*(u8 *)(v54 + 24))
        goto LABEL_61;
      v57 = bookUI;
      v47 = v45 - 4;
      v48 = v57;
      v49 = 1;
      v50 = *(u8 *)(*((u64 *)&QUEST_READ_FLAG->obj.klass + v45) + 24);
      goto LABEL_60;
    }
    break;
  }
}

// 0x1c01090
static void SetRootMenu_Quest(void *wk, s32 MenuID, s32 ChildNum, char *pStr) {
  QUEST_TEXT_CLASS *v11;
  s32 openStatus;
  s32 v13;
  s64 v15;

  v11 = QUESTPAGE[MenuID];
  openStatus = v11->openStatus;
  v13 = v11->upDateTextFlag[0];
  MenuParentID[MenuID] = 0;
  if ((u32)(MenuID - 1) > 0xE)
    goto LABEL_10;
  v15 = MenuID;
  if (QUESTPAGE[v15]->childs > 0)
  {
LABEL_10:
    if (!v13 || evtBitCheck(v13))
    {
      ParentMenu_SetTaxt(bookUI, MenuID, pStr, 0);
      ++wk->menu_num;
      ChildMenuObjCtrl(bookUI, MenuID, ChildNum, 0, 0);
      MenuObjSave(bookUI, wk, MenuID, ChildNum, openStatus, pStr, 1, 0);
    }
    return;
  }
  MenuObjCtrl(bookUI, MenuID, 0, 0);
}

// 0x1c012d0
static s32 QuestCheckChildID(s32 ID) {
  return QUESTPAGE[ID]->childs > 0;
}

// 0x1c01350
static void SetCommondParentQuest(void *wk) {
  s64 i;
  char *LocalizeText;
  char *v8;
  s64 v9;
  QUEST_TEXT_CLASS *QUESTPAGE_local;
  s64 v12;
  char *v14;

  MenuObjReset(bookUI, 0);
  for (i = 5; ; ++i)
  {
    QUESTPAGE_local = QUESTPAGE;
    if (i - 4 >= SLODWORD(QUESTPAGE_local->max_length))
      break;
    v12 = *((u64 *)&QUESTPAGE_local->obj.klass + i);
    if (*(u32 *)(v12 + 96) == -1)
    {
      v14 = *(char **)(v12 + 104);
      LocalizeText = GetLocalizeText(v14, 1);
      v8 = ChangeTextPLTF(LocalizeText);
      v9 = *((u64 *)&QUESTPAGE->obj.klass + i);
      SetRootMenu_Quest(wk, *(u32 *)(v9 + 16), *(u32 *)(v9 + 84), v8);
      continue;
    }
  }
}

// 0x1c00650
static void SetMenu_Quest(void *wk, s32 MenuID, s32 ParentMenuID, char *pStr, s32 _type, s32 _subID, s32 _questID) {
  s32 v15;
  s32 v16;
  s32 v19;
  s64 v20;
  QUEST_TEXT_CLASS *v21;
  s64 v22;
  Il2CppClass **v23;
  void *v25;
  s32 *ID;
  s32 *v28;
  s32 *v29;
  QUEST_TEXT_CLASS *v30;
  bool v32;
  QUEST_TEXT_CLASS *v35;
  s64 v37;
  QUEST_READ_FLAG_CLASS *v38;
  u32 v40;
  void *v41;
  QUEST_TEXT_CLASS *v43;
  bool v45;
  QUEST_READ_FLAG_CLASS *v47;
  void *v48;
  QUEST_TEXT_CLASS *v50;
  QUEST_TEXT_CLASS *v54;
  QUEST_TEXT_CLASS *v56;
  QUEST_TEXT_CLASS *v60;
  _BOOL4 READ_FLAG;
  void *v64;
  void *v66;
  s32 v67;
  s32 v68;
  QUEST_TEXT_CLASS *v69;
  void *p_bookUI;
  void *v73;
  void *v75;
  void *v76;
  QUEST_TEXT_CLASS *v77;

  v15 = QUESTPAGE[MenuID]->upDateTextFlag[0];
  MenuParentID[MenuID] = ParentMenuID;
  if (!v15 || evtBitCheck(v15))
  {
    v16 = ParentMenuID - 1;
    v19 = type;
    v20 = ParentMenuID;
    SetIDTable(bookUI, MenuID, ParentMenuID, QUESTPAGE[v20]->childs, 0);
    v21 = QUESTPAGE[v20];
    v21->childID[v21->childs] = MenuID;
    ChildrenMenu_SetTaxt(bookUI, v21->childs, ParentMenuID, pStr, 0);
    v22 = v16;
    v23 = &wk->child_save[v22]->text->obj.klass
        + QUESTPAGE[v20]->childs;
    v23[4] = pStr;
    v25 = wk->child_save[v22];
    v25->parent = v16;
    ID = v25->ID;
    v28 = v25->type;
    v29 = v25->questID;
    v30 = QUESTPAGE[v20];
    ID[v30->childs] = MenuID;
    v28[v30->childs] = v19;
    v29[v30->childs] = questID;
    v32 = evtBitCheck(QUESTPAGE[MenuID]->ClearFlag);
    QUEST_READ_FLAG[MenuID]->CLEAR_FLAG = v32;
    CheckQuestTextUpdate(MenuID, ParentMenuID);
    v35 = QUESTPAGE;
    v37 = v35[ParentMenuID]->childID[v35[ParentMenuID]->childs];
    v38 = QUEST_READ_FLAG[v37];
    if (v38->CLEAR_FLAG)
    {
      if (v38->REWARD_FLAG)
        goto LABEL_21;
      goto LABEL_9000;
      if (v47->REWARD_FLAG)
      {
LABEL_21:
        if (v40)
        {
          v41 = bookUI;
LABEL_23:
          v43 = QUESTPAGE[ParentMenuID];
          ChildrenMenu_SetIconCtrlInit(v41, v43->childs, ParentMenuID, QUEST_READ_FLAG[v43->childID[v43->childs]]->CLEAR_FLAG, 1, 0);
          v45 = 0;
          goto LABEL_33;
        }
        else
        {
          v41 = bookUI;
          goto LABEL_23;
        }
        goto LABEL_23;
      }
LABEL_9000:
      v48 = bookUI;
      v50 = QUESTPAGE[ParentMenuID];
      ChildrenMenu_SetIconCtrlInit(v48, v50->childs, ParentMenuID, QUEST_READ_FLAG[v50->childID[v50->childs]]->CLEAR_FLAG, 2, 0);
      v45 = 1;
LABEL_33:
      wk->child_save[v16]->reward[QUESTPAGE[ParentMenuID]->childs] = v45;
      AccessQuestReadFlag(MenuID);
      v54 = QUESTPAGE[ParentMenuID];
      ChildrenMenu_SetNewIconInit(bookUI, v54->childs, ParentMenuID, !QUEST_READ_FLAG[v54->childID[v54->childs]]->READ_FLAG, 0);
      ChildrenMenu_TexCloreChange(bookUI, QUESTPAGE[ParentMenuID]->childs, ParentMenuID, 2, 0);
LABEL_37:
      v56 = QUESTPAGE[ParentMenuID];
      ++v56->childs;
      return;
    }
    if (!!v35[v37]->StopFlag)
    {
      if (GBWK->GameFileInfo->chapter == 9)
      {
        v60 = QUESTPAGE[ParentMenuID];
        READ_FLAG = QUEST_READ_FLAG[v60->childID[v60->childs]]->READ_FLAG;
        if (READ_FLAG)
        {
          v64 = bookUI;
          v66 = v64;
          v67 = ParentMenuID;
          v68 = 7;
        }
        else
        {
          v76 = bookUI;
          v66 = v76;
          v67 = ParentMenuID;
          v68 = 4;
        }
        goto LABEL_72;
      }
    }
    v69 = QUESTPAGE[ParentMenuID];
    if (QUEST_READ_FLAG[v69->childID[v69->childs]]->READ_FLAG)
    {
      goto LABEL_59;
    }
    v75 = bookUI;
    v68 = 5;
    v66 = v75;
    v67 = ParentMenuID;
LABEL_72:
    v77 = QUESTPAGE[ParentMenuID];
    ChildrenMenu_SetIconCtrlInit(v66, v77->childs, v67, !QUEST_READ_FLAG[v77->childID[v77->childs]]->READ_FLAG, v68, 0);
LABEL_59:
    p_bookUI = &bookUI;
    v73 = p_bookUI;
    ChildrenMenu_TexCloreChange(v73, QUESTPAGE[ParentMenuID]->childs, ParentMenuID, 0, 0);
    wk->child_save[v16]->reward[QUESTPAGE[ParentMenuID]->childs] = 0;
    goto LABEL_37;
  }
}

// 0x1bfa160
static void QuestMenuMoveStartCtrl(void *wk) {
  s32 v3;
  QUEST_TEXT_CLASS *v5;
  s32 openStatus;
  s64 cursor;
  bool v13;
  s32 v14;
  s32 *questID_save;
  s32 v19;
  s64 v20;
  s32 *parentID;
  il2cpp_array_size_t max_length;
  s32 *child_NumMax;
  u64 v24;
  s64 v25;
  __int128 v26;
  s32 *v27;
  s32 *v28;
  s64 v29;
  char v30;
  s64 v31;
  s64 v32;
  u64 v33;
  s64 v34;
  u32 *v35;
  u32 *v36;
  char *draw_text;
  s64 v38;
  s64 v39;
  _BOOL4 open_flag;
  u32 v43;
  void *v44;
  void *v46;
  s32 v47;
  s32 v48;
  s32 top;
  s32 *menu_drawOld;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;
  s32 v63;
  s32 v64;
  s32 v65;
  s32 *menu_Before;
  s32 v67;
  s32 v68;
  s32 *menu_After;
  s32 *v70;
  s32 v71;
  s32 v72;
  s32 v73;
  s32 v74;
  s32 v75;
  s32 v76;
  s32 v77;
  s32 v78;
  s32 v79;
  s32 v80;
  s32 v81;
  s32 v82;
  s32 v83;
  s32 v84;
  s32 v85;
  s32 v86;
  s32 v87;
  s32 v88;
  s32 v89;
  s32 v90;
  s32 v91;
  s32 v92;

  if (wk->cursor_parent != -1)
  {
    if (!CHECK_TRIG(4096, 1))
      return;
    v3 = wk->cursor_parent + 1;
    v5 = QUESTPAGE[v3];
    openStatus = v5->openStatus;
    if (openStatus)
    {
      MenuChildAnimSetCtrl(bookUI, wk->cursor_parent, 1, 0);
      wk->open_flag = 0;
      QUESTPAGE[v3]->openStatus = 0;
    }
    else
    {
      MenuChildAnimSetCtrl(bookUI, wk->cursor_parent, 0, 0);
      v19 = wk->top + 11;
      v20 = (s64)QUESTPAGE + 8 * v3;
      wk->open_flag = 1;
      *(u32 *)(*(u64 *)(v20 + 32) + 116) = 1;
      if (v19 == wk->cursor)
        wk->open_move = 1;
    }
    parentID = wk->parentID;
    *(u64 *)&wk->parentID_Befor = 0;
    wk->menu_num = 0;
    max_length = parentID->max_length;
    if ((s32)max_length >= 1)
    {
      child_NumMax = wk->child_NumMax;
      v24 = (u32)parentID->max_length;
      v25 = 0;
      if (v24 < 0x10)
        goto LABEL_37;
      if ((u64)((char *)child_NumMax - (char *)parentID) < 0x40)
        goto LABEL_37;
      *(u64 *)&v26 = -1;
      *((u64 *)&v26 + 1) = -1;
      v25 = v24 - (parentID->max_length & 0xF);
      v27 = &child_NumMax[12];
      v28 = &parentID[4];
      v29 = v25;
      do
      {
        *((_OWORD *)v28 - 1) = v26;
        *(_OWORD *)v28 = v26;
        v29 -= 16;
        *((_OWORD *)v28 + 1) = v26;
        *((_OWORD *)v28 + 2) = v26;
        v28 += 16;
        *((_OWORD *)v27 - 3) = 0u;
        *((_OWORD *)v27 - 2) = 0u;
        *((_OWORD *)v27 - 1) = 0u;
        *(_OWORD *)v27 = 0u;
        v27 += 16;
      }
      while (v29);
      if ((max_length & 0xF) != 0)
      {
LABEL_37:
        v30 = max_length - v25;
        v31 = v25 + 1;
        if ((v30 & 1) != 0)
        {
          v32 = v25;
          parentID[v32] = -1;
          child_NumMax[v32] = 0;
          v25 = v31;
        }
        if (v24 != v31)
        {
          v33 = v24 - v25;
          v34 = 4 * v25 + 36;
          v35 = ((char *)child_NumMax + v34);
          v36 = ((char *)parentID + v34);
          do
          {
            *(v36 - 1) = -1;
            v33 -= 2;
            *(v35 - 1) = 0;
            *v36 = -1;
            v36 += 2;
            *v35 = 0;
            v35 += 2;
          }
          while (v33);
        }
      }
    }
    draw_text = wk->draw_text;
    if (SLODWORD(draw_text->max_length) >= 1)
    {
      v38 = 0;
      v39 = 32;
      do
      {
        *(Il2CppClass **)((char *)&draw_text->obj.klass + v39) = 0;
        draw_text = wk->draw_text;
        ++v38;
        v39 += 8;
      }
      while (v38 < SLODWORD(draw_text->max_length));
    }
    SetCommondParentQuest(wk);
    wk->menu_move = 1;
    open_flag = wk->open_flag;
    wk->menu_child = QUESTPAGE[v3]->childs;
    if (!open_flag)
    {
      v46 = bookUI;
      v47 = v3;
      v48 = 1;
      goto LABEL_57;
    }
    if (v43)
    {
      v44 = bookUI;
LABEL_51:
      v46 = v44;
      v47 = v3;
      v48 = 0;
LABEL_57:
      MenuCursorAlpha(v46, v47, QUESTPAGE[v3]->childs, v48, 0);
      top = wk->top;
      menu_drawOld = wk->menu_drawOld;
      if (top >= wk->menu_num)
        top = -1;
      menu_drawOld[0] = top;
      v52 = wk->top;
      if (v52 + 1 < wk->menu_num)
        v53 = v52 + 1;
      else
        v53 = -1;
      menu_drawOld[1] = v53;
      v54 = wk->top + 2;
      if (v54 >= wk->menu_num)
        v54 = -1;
      menu_drawOld[2] = v54;
      v55 = wk->top + 3;
      if (v55 >= wk->menu_num)
        v55 = -1;
      menu_drawOld[3] = v55;
      v56 = wk->top + 4;
      if (v56 >= wk->menu_num)
        v56 = -1;
      menu_drawOld[4] = v56;
      v57 = wk->top + 5;
      if (v57 >= wk->menu_num)
        v57 = -1;
      menu_drawOld[5] = v57;
      v58 = wk->top + 6;
      if (v58 >= wk->menu_num)
        v58 = -1;
      menu_drawOld[6] = v58;
      v59 = wk->top + 7;
      if (v59 >= wk->menu_num)
        v59 = -1;
      menu_drawOld[7] = v59;
      v60 = wk->top + 8;
      if (v60 >= wk->menu_num)
        v60 = -1;
      menu_drawOld[8] = v60;
      v61 = wk->top + 9;
      if (v61 >= wk->menu_num)
        v61 = -1;
      menu_drawOld[9] = v61;
      v62 = wk->top + 10;
      if (v62 >= wk->menu_num)
        v62 = -1;
      menu_drawOld[10] = v62;
      v63 = wk->top + 11;
      if (v63 >= wk->menu_num)
        v63 = -1;
      menu_drawOld[11] = v63;
      if (wk->menu_num <= 12)
      {
        v64 = wk->top;
        wk->top = 0;
        wk->topOld = v64;
      }
      v65 = menu_drawOld[0] - 1;
      menu_Before = wk->menu_Before;
      if (v65 < 0)
        v65 = -1;
      menu_Before[0] = v65;
      v67 = menu_drawOld[11];
      if (v67 + 1 < wk->menu_num)
        v68 = v67 + 1;
      else
        v68 = -1;
      v70 = wk->menu_Before;
      menu_After = wk->menu_After;
      menu_After[0] = v68;
      v71 = menu_drawOld[0] - 2;
      if (v71 < 0)
        v71 = -1;
      menu_Before[1] = v71;
      v72 = menu_drawOld[11] + 2;
      if (v72 >= wk->menu_num)
        v72 = -1;
      menu_After[1] = v72;
      v73 = menu_drawOld[0] - 3;
      if (v73 < 0)
        v73 = -1;
      menu_Before[2] = v73;
      v74 = menu_drawOld[11] + 3;
      if (v74 >= wk->menu_num)
        v74 = -1;
      menu_After[2] = v74;
      v75 = menu_drawOld[0] - 4;
      if (v75 < 0)
        v75 = -1;
      wk->menu_Before[3] = v75;
      v76 = menu_drawOld[11] + 4;
      if (v76 >= wk->menu_num)
        v76 = -1;
      wk->menu_After[3] = v76;
      v77 = menu_drawOld[0] - 5;
      if (v77 < 0)
        v77 = -1;
      wk->menu_Before[4] = v77;
      v78 = menu_drawOld[11] + 5;
      if (v78 >= wk->menu_num)
        v78 = -1;
      wk->menu_After[4] = v78;
      v79 = menu_drawOld[0] - 6;
      if (v79 < 0)
        v79 = -1;
      wk->menu_Before[5] = v79;
      v80 = menu_drawOld[11] + 6;
      if (v80 >= wk->menu_num)
        v80 = -1;
      wk->menu_After[5] = v80;
      v81 = menu_drawOld[0] - 7;
      if (v81 < 0)
        v81 = -1;
      wk->menu_Before[6] = v81;
      v82 = menu_drawOld[11] + 7;
      if (v82 >= wk->menu_num)
        v82 = -1;
      wk->menu_After[6] = v82;
      v83 = menu_drawOld[0] - 8;
      if (v83 < 0)
        v83 = -1;
      wk->menu_Before[7] = v83;
      v84 = menu_drawOld[11] + 8;
      if (v84 >= wk->menu_num)
        v84 = -1;
      wk->menu_After[7] = v84;
      v85 = menu_drawOld[0] - 9;
      if (v85 < 0)
        v85 = -1;
      wk->menu_Before[8] = v85;
      v86 = menu_drawOld[11] + 9;
      if (v86 >= wk->menu_num)
        v86 = -1;
      wk->menu_After[8] = v86;
      v87 = menu_drawOld[0] - 10;
      if (v87 < 0)
        v87 = -1;
      wk->menu_Before[9] = v87;
      v88 = menu_drawOld[11] + 10;
      if (v88 >= wk->menu_num)
        v88 = -1;
      wk->menu_After[9] = v88;
      v89 = menu_drawOld[0] - 11;
      if (v89 < 0)
        v89 = -1;
      wk->menu_Before[10] = v89;
      v90 = menu_drawOld[11] + 11;
      if (v90 >= wk->menu_num)
        v90 = -1;
      wk->menu_After[10] = v90;
      v91 = menu_drawOld[0] - 12;
      if (v91 < 0)
        v91 = -1;
      v70[11] = v91;
      v92 = menu_drawOld[11] + 12;
      if (v92 >= wk->menu_num)
        v92 = -1;
      wk->menu_After[11] = v92;
      SE(0);
      return;
    }
    else
    {
      v44 = bookUI;
      goto LABEL_51;
    }
    goto LABEL_51;
  }
  cursor = wk->cursor;
  if (!wk->reward_save[cursor])
  {
    if (wk->id_save[(s32)cursor] == -1)
      return;
LABEL_21:
    if (QUEST_READ_FLAG[wk->cursor_ID]->CLEAR_FLAG)
      return;
    if (GBWK->GameFileInfo->chapter == 9)
    {
      if (QUESTPAGE[wk->id_save[wk->cursor]]->StopFlag)
        return;
    }
    if (GetQuestMapNo(QUESTPAGE[wk->id_save[wk->cursor]]) && CHECK_TRIG(41999, 1))
    {
      wk->map_move = 1;
    }
    return;
  }
  v13 = CHECK_TRIG(41984, 1);
  v14 = wk->cursor;
  if (v13)
  {
    questID_save = wk->questID_save;
    wk->reward_move = 1;
    wk->reward_ID = questID_save[v14];
    v14 = wk->cursor;
    RewardChackProc = 0;
    RewardMsgNum = 0;
    *(u64 *)&RewardMsgStep = 0x100000000LL;
  }
  if (wk->id_save[v14] != -1)
    goto LABEL_21;
}

// 0x1c004f0
static void CheckAllQuestParentReadFlag(void) {
  s64 i;
  s64 v4;
  s64 v5;

  for (i = 1; ; ++i)
  {
    if (i >= SLODWORD(QUESTPAGE->max_length))
      break;
    if (!QUESTPAGE[i]->childs)
      continue;
    v4 = 0;
    while (1)
    {
      if (v4 >= QUESTPAGE[i]->childs)
        break;
      v5 = (s64)QUESTPAGE[i]->childID + 4 * v4++;
      if (!QUEST_READ_FLAG[*(s32 *)(v5 + 32)]->READ_FLAG)
      {
        QUEST_READ_FLAG[i]->READ_FLAG = 0;
        break;
      }
    }
  }
}

// 0x1c00ee0
static void CheckAllQuestParentClearFlag(void) {
  s64 i;
  QUEST_TEXT_CLASS *v4;
  s32 childs;
  s64 v6;
  s64 v7;
  QUEST_TEXT_CLASS *v9;
  s64 v10;
  bool v11;
  QUEST_TEXT_CLASS *v12;

  for (i = 1; ; ++i)
  {
    if (i >= SLODWORD(QUESTPAGE->max_length))
      break;
    v4 = QUESTPAGE[i];
    childs = v4->childs;
    if (!childs)
      continue;
    if (childs == v4->childMax)
      goto LABEL_15;
    goto LABEL_9000;
    if (v12->childs == v12->childMax)
    {
LABEL_15:
      v6 = 0;
      do
      {
        v9 = QUESTPAGE[i];
        v10 = v9->childs;
        v11 = v6 >= v10;
        if (v6 >= v10)
          break;
        v9 = QUESTPAGE[i];
        v7 = (s64)v9->childID + 4 * v6++;
      }
      while (QUEST_READ_FLAG[*(s32 *)(v7 + 32)]->CLEAR_FLAG);
      goto LABEL_24;
    }
LABEL_9000:
    v11 = 0;
LABEL_24:
    QUEST_READ_FLAG[i]->CLEAR_FLAG = v11;
  }
}

// 0x1c015a0
static void CheckQuestTextUpdate(s32 ID, s32 parentID) {
  s64 v6;
  s32 v7;
  s32 *upDateTextFlag;
  bool v9;
  QUEST_READ_FLAG_CLASS *v11;
  QUEST_READ_FLAG_CLASS *v12;

  if (!QUESTPAGE[ID]->type)
    return;
  v6 = 9;
  while (1)
  {
    v7 = v6 - 8;
    upDateTextFlag = QUESTPAGE[ID]->upDateTextFlag;
    if (v6 - 8 >= SLODWORD(upDateTextFlag->max_length))
      break;
    upDateTextFlag = QUESTPAGE[ID]->upDateTextFlag;
    v9 = evtBitCheck(*((u32 *)&upDateTextFlag->obj.klass + v6));
    if (!v9)
    {
      v11 = QUEST_READ_FLAG[ID];
      if (v11->UPDATE_FLAG < v7)
      {
        v11 = QUEST_READ_FLAG[ID];
        v11->READ_FLAG = 0;
        v11->UPDATE_FLAG = v7;
        v12 = QUEST_READ_FLAG[parentID];
        if (v12->READ_FLAG)
        {
          v12->READ_FLAG = 0;
        }
      }
      return;
    }
    ++v6;
  }
}

// 0x1c003b0
static void AccessQuestReadFlag(s32 accessID) {
  s64 v2;
  s32 v7;

  LODWORD(v2) = accessID;
  if (!QUEST_READ_FLAG[(s32)v2]->READ_FLAG)
  {
    v2 = (s32)v2;
    bookUI->PANELREADFLAG = 0;
    v7 = MenuParentID[v2];
    QUEST_READ_FLAG[v2]->READ_FLAG = 1;
    CheckQuestParentReadFlag(v7);
    return;
  }
  bookUI->PANELREADFLAG = 1;
}

// 0x1c01790
static void CheckQuestParentReadFlag(s32 ID) {
  s64 v4;
  s64 v5;
  QUEST_TEXT_CLASS *v7;
  s64 v10;

  while (2)
  {
    v4 = 0;
    v5 = ID;
    while (1)
    {
      v7 = QUESTPAGE[ID];
      if (v4 >= v7->childs)
        break;
      v7 = QUESTPAGE[ID];
      if (!QUEST_READ_FLAG[v7->childID[v4]]->READ_FLAG)
      {
        QUEST_READ_FLAG[ID]->READ_FLAG = 0;
        break;
      }
      ++v4;
    }
    if (QUESTPAGE[ID]->childs == (u32)v4)
    {
      v10 = (s64)QUEST_READ_FLAG + 8 * ID;
      ID = MenuParentID[ID];
      *(u8 *)(*(u64 *)(v10 + 32) + 16) = 1;
      if (ID)
      {
        ID = MenuParentID[v5];
        continue;
      }
    }
    break;
  }
}

// 0x1c014f0
static void CheckQuestClearUpdate(s32 ID, s32 parentID) {
  s64 v5;
  bool v6;

  v5 = ID;
  v6 = evtBitCheck(QUESTPAGE[ID]->ClearFlag);
  QUEST_READ_FLAG[v5]->CLEAR_FLAG = v6;
}

// 0x1bffb60
void ReturnQuestReadFlagData(void) {
  s64 v2;
  char *v3;
  s64 v4;
  s64 v5;
  s64 v6;
  char v7;
  bool *quest_readFlag;

  if (DebugProcessFlag)
    return;
  v2 = 0;
  while (1)
  {
    if (v2 >= SLODWORD(QUEST_READ_FLAG->max_length))
      break;
    quest_readFlag = GBWK->quest_readFlag;
    v3 = (char *)quest_readFlag + v2;
    v4 = (s64)GBWK->quest_updateFlag + 4 * v2;
    v5 = (s64)QUEST_READ_FLAG + 8 * v2++;
    v6 = *(u64 *)(v5 + 32);
    v7 = *(u8 *)(v6 + 16);
    LODWORD(v6) = *(u32 *)(v6 + 20);
    v3[32] = v7;
    *(u32 *)(v4 + 32) = v6;
  }
  QUEST_READ_FLAG = 0;
}

// 0x1c01920
char *QuestTagConvert(char *_tag, s32 id) {
  char **v5;
  void *v6;
  s64 v9;
  s64 i;
  s32 v11;
  Il2CppObject *v12;
  char *v13;
  char *v14;
  Il2CppObject *v15;
  char *v16;
  QUEST_CLASS *v18;
  s32 *rItemID;
  s32 v20;
  char *v21;
  Il2CppObject *v22;
  char *v23;
  char *v24;
  Il2CppObject *v25;
  char *v26;
  char **v27;
  char *v28;
  char *LocalizeText;
  char *v30;
  void *v31;
  Il2CppObject *v33;
  char *v34;
  Il2CppObject *v35;
  char *v36;
  void *v38;
  s64 v40;
  s32 v41;
  Il2CppObject *v42;
  char *v43;
  char *v44;
  Il2CppObject *v45;
  char *v46;
  s32 *nItemID;
  s32 v48;
  char *v49;
  Il2CppObject *v50;
  char *v51;
  char *v52;
  Il2CppObject *v53;
  char *v54;
  char *v55;
  char *v56;
  char *v57;
  void *v58;
  s64 v60;
  char *v61;
  s32 *nDevilID;
  s32 v63;
  Il2CppObject *v64;
  char *v65;
  char *v66;
  Il2CppObject *v67;
  char *v68;
  char *v69;
  s64 v70;
  char *v71;
  char *v72;
  s32 *nKatana;
  s32 v74;
  char *v75;
  Il2CppObject *v76;
  char *v77;
  char *v78;
  Il2CppObject *v79;
  char *v80;
  char *v81;
  s32 v83;
  s32 data;
  s32 v85;
  s32 rMoney;

  v5 = &"<ITEM_R";
  v6 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v6, tag, 0);
  v9 = id;
  for (i = 8; ; ++i)
  {
    v18 = QUESTDATA[v9];
    rItemID = v18->rItemID;
    if (i - 8 >= SLODWORD(rItemID->max_length))
      break;
    v20 = *((u32 *)&rItemID->obj.klass + i);
    if (!v20)
      continue;
    v21 = IconConvert(v20);
    rMoney = v20;
    v22 = Box(s32, &rMoney);
    v23 = Format("{0:d4}", v22, 0);
    v24 = Concat_54766928("ITEM_L", v23, 0);
    v85 = i - 8;
    v25 = Box(s32, &v85);
    v26 = Format("{0:D2}", v25, 0);
    v27 = v5;
    v28 = Concat_54831728(*v5, v26, ">", 0);
    LocalizeText = GetLocalizeText(v24, 1);
    v30 = Concat_54766928(v21, LocalizeText, 0);
    v31 = Replace(v6, v28, v30, 0);
    v5 = v27;
    v11 = *((u32 *)&QUESTDATA[v9]->rItemNum->obj.klass + i);
    data = i - 8;
    v12 = Box(s32, &data);
    v13 = Format("{0:D2}", v12, 0);
    v14 = Concat_54831728(*v27, v13, "_NUM>", 0);
    v83 = v11;
    v15 = Box(s32, &v83);
    v16 = Format("{0:D1}", v15, 0);
    v6 = Replace(v31, v14, v16, 0);
  }
  v18 = QUESTDATA[v9];
  rMoney = v18->rMoney;
  v33 = Box(s32, &rMoney);
  v34 = Format("{0:D}", v33, 0);
  v35 = itfConvertToDelimitedNum(v34);
  v36 = Format("{0:D1}", v35, 0);
  v38 = Replace(v6, "<MONEY_R>", v36, 0);
  v40 = 8;
  while (2)
  {
    nItemID = QUESTDATA[v9]->nItemID;
    if (v40 - 8 < SLODWORD(nItemID->max_length))
    {
      v48 = *((u32 *)&nItemID->obj.klass + v40);
      if (!v48)
        goto LABEL_25;
      goto LABEL_9000;
      if (!v48)
      {
LABEL_25:
        ++v40;
        continue;
      }
LABEL_9000:
      v49 = IconConvert(v48);
      rMoney = v48;
      v50 = Box(s32, &rMoney);
      v51 = Format("{0:d4}", v50, 0);
      v52 = Concat_54766928("ITEM_L", v51, 0);
      v85 = v40 - 8;
      v53 = Box(s32, &v85);
      v54 = Format("{0:D2}", v53, 0);
      v55 = Concat_54831728("<ITEM_N", v54, ">", 0);
      v56 = GetLocalizeText(v52, 1);
      v57 = Concat_54766928(v49, v56, 0);
      v58 = Replace(v38, v55, v57, 0);
      v41 = *((u32 *)&QUESTDATA[v9]->rItemNum->obj.klass + v40);
      data = v40 - 8;
      v42 = Box(s32, &data);
      v43 = Format("{0:D2}", v42, 0);
      v44 = Concat_54831728("<ITEM_N", v43, "_NUM>", 0);
      v83 = v41;
      v45 = Box(s32, &v83);
      v46 = Format("{0:D1}", v45, 0);
      v38 = Replace(v58, v44, v46, 0);
      goto LABEL_25;
    }
    break;
  }
  v60 = 0;
  while (2)
  {
    nDevilID = QUESTDATA[v9]->nDevilID;
    if (v60 < SLODWORD(nDevilID->max_length))
    {
      v63 = nDevilID[v60];
      if (!v63)
        goto LABEL_41;
      goto LABEL_9001;
      if (!v63)
      {
LABEL_41:
        ++v60;
        continue;
      }
LABEL_9001:
      rMoney = v63;
      v64 = Box(s32, &rMoney);
      v65 = Format("{0:d4}", v64, 0);
      v66 = Concat_54766928("DEVIL_L", v65, 0);
      v85 = v60;
      v67 = Box(s32, &v85);
      v68 = Format("{0:D2}", v67, 0);
      v69 = Concat_54831728("<DEVIL_N", v68, ">", 0);
      v61 = GetLocalizeText(v66, 1);
      v38 = Replace(v38, v69, v61, 0);
      goto LABEL_41;
    }
    break;
  }
  v70 = 0;
  while (2)
  {
    nKatana = QUESTDATA[v9]->nKatana;
    if (v70 < SLODWORD(nKatana->max_length))
    {
      v74 = nKatana[v70];
      if (!v74)
        goto LABEL_53;
      goto LABEL_9002;
      if (!v74)
      {
LABEL_53:
        ++v70;
        continue;
      }
LABEL_9002:
      v75 = IconConvert(v74);
      rMoney = v74;
      v76 = Box(s32, &rMoney);
      v77 = Format("{0:d4}", v76, 0);
      v78 = Concat_54766928("ITEM_L", v77, 0);
      v85 = v70;
      v79 = Box(s32, &v85);
      v80 = Format("{0:D2}", v79, 0);
      v81 = Concat_54831728("<KATANA_N", v80, ">", 0);
      v71 = GetLocalizeText(v78, 1);
      v72 = Concat_54766928(v75, v71, 0);
      v38 = Replace(v38, v81, v72, 0);
      goto LABEL_53;
    }
    return ((char *(void *, const MethodInfo *))v38->klass->vtable._3_ToString.methodPtr)(v38, v38->klass->vtable._3_ToString.method);
  }
}

// 0x1c022c0
static char *IconConvert(s32 _itemID) {
  char *v4;
  char **v5;

  v4 = "";
  switch (tbldata[itemID]->iconType)
  {
    case 1:
      v5 = &"<sprite name=item_icon_01>";
      goto LABEL_22;
    case 2:
      v5 = &"<sprite name=item_icon_02>";
      goto LABEL_22;
    case 3:
      v5 = &"<sprite name=item_icon_03>";
      goto LABEL_22;
    case 4:
      v5 = &"<sprite name=item_icon_04>";
      goto LABEL_22;
    case 5:
      v5 = &"<sprite name=item_icon_05>";
      goto LABEL_22;
    case 6:
      v5 = &"<sprite name=item_icon_06>";
      goto LABEL_22;
    case 7:
      v5 = &"<sprite name=item_icon_07>";
      goto LABEL_22;
    case 8:
      v5 = &"<sprite name=menu_icon_16>";
      goto LABEL_22;
    case 9:
      v5 = &"<sprite name=menu_icon_18>";
      goto LABEL_22;
    case 0xA:
      v5 = &"<sprite name=menu_icon_17>";
      goto LABEL_22;
    case 0xB:
      v5 = &"<sprite name=menu_icon_19>";
      goto LABEL_22;
    case 0xC:
      v5 = &"<sprite name=menu_icon_20>";
      goto LABEL_22;
    case 0xD:
      v5 = &"<sprite name=menu_icon_21>";
      goto LABEL_22;
    case 0xE:
      v5 = &"<sprite name=menu_icon_22>";
LABEL_22:
      v4 = *v5;
      break;
    default:
      return v4;
  }
  return v4;
}

// 0x1bf7e60
static bool RewardMoveCalc(void *wk) {
  bool result;
  s32 reward_ID;
  _BOOL4 v8;
  s32 v12;
  s32 v13;
  s32 *EventBit;
  bool active;
  char **v21;

  fclUpdateMessage();
  if (fclChkMessage())
    return 1;
  switch (RewardChackProc)
  {
    case 0:
      reward_ID = wk->reward_ID;
      v8 = ChackRewardReceive(reward_ID);
      RewardChack = v8;
      if (v8)
        v12 = 0;
      else
        v12 = 99;
      RewardMsgNum = v12;
      goto LABEL_22;
    case 1:
      Reset(0);
      RewardMsgDraw(RewardMsgNum, wk->reward_ID);
      v13 = 2;
      goto LABEL_27;
    case 2:
      if (RewardMsgStep)
      {
        RewardChackProc = 3;
        result = 1;
      }
      else
      {
LABEL_22:
        v13 = 1;
LABEL_27:
        RewardChackProc = v13;
        result = 1;
      }
      break;
    case 3:
      if (RewardChack)
      {
        wk->reward_save[wk->cursor] = 0;
        if (wk->reward_ID == 4)
        {
          EventBit = GBWK->EventBit;
          EventBit[384] |= 0x10000000u;
        }
        ChildrenMenu_SetIconCtrl(bookUI, wk->cursor, 3, 0);
        active = PANEL02_ScrollBarActiveChack(bookUI, 0);
        v21 = &"DBOOK08";
        if (!active)
          v21 = &"DBOOK02";
        ButtonGuideDispSet(*v21, 0, 90);
        GBWK->quest_rewardFlag[wk->questID_save[wk->cursor]] = 1;
      }
      wk->reward_move = 0;
      wk->reward_ID = 0;
      RewardMsgNum = 0;
      *(u64 *)&RewardMsgStep = 0x100000000LL;
      RewardChackProc = 0;
      return 0;
    default:
      return 0;
  }
  return result;
}

// 0x1c02510
static bool RewardMsgDraw(s32 _num, s32 _questID) {
  char *v11;
  s32 v12;
  s32 QuestRewardItemID;
  s32 v17;
  s32 v19;
  char *v20;
  char *v21;
  s32 v22;
  s32 add;
  s32 numa;

  numa = 0;
  if (num == 99)
  {
    fclSetMessageInvalid(1);
    fclStartMessage(26);
    RewardMsgStep = 1;
    return 1;
  }
  else
  {
    if (num != 1)
    {
      if (num)
        return 1;
      if (RewardItemNo == 6)
      {
        ++RewardMsgNum;
        return 1;
      }
      QuestRewardItemID = GetQuestRewardItemID(questID, RewardItemNo);
      if (!QuestRewardItemID)
      {
LABEL_35:
        ++RewardItemNo;
        return 1;
      }
      v17 = QuestRewardItemID;
      v19 = RewardItemNo;
      numa = GetQuestRewardItemNum(questID, v19);
      v20 = sdatItemName(v17);
      frSetVariableRequest(0, v20);
      v21 = ToString_55996800((s32)&numa, "d1", 0);
      frSetVariableRequest(1, v21);
      fclSetMessageInvalid(1);
      fclStartMessage(27);
      v22 = numa;
      datAddItem(v17, v22);
      goto LABEL_35;
    }
    add = GetQuestRewardMoney(questID);
    if (add)
    {
      v11 = ToString_55996800((s32)&add, "d1", 0);
      frSetVariableRequest(0, v11);
      fclSetMessageInvalid(1);
      fclStartMessage(28);
      v12 = add;
      datAddMoney(v12);
    }
    RewardMsgStep = 1;
    return 1;
  }
}

// 0x1bf82a0
static bool MapMoveCalc(void *wk) {
  s32 v6;
  bool v7;
  void *Instance;
  void *v9;
  bool active;
  char **v12;
  s32 QuestMapNo;
  QUEST_TEXT_CLASS *v18;
  s32 *upDateTextFlag;
  s64 v21;
  s32 v23;
  f32 QuestMap_X;
  f32 QuestMap_Y;
  s32 v27;
  s32 v28;

  switch (MapChackProc)
  {
    case 0u:
      dds3FadeOut(0, 0, 0, 8u);
      v6 = 1;
      v7 = 1;
      goto LABEL_78;
    case 1u:
      if (dds3FadeCheck())
        return 1;
      automapCheck = 1;
      clrAutomapIconList();
      QuestMapNo = GetQuestMapNo(QUESTPAGE[wk->id_save[wk->cursor]]);
      v18 = QUESTPAGE[wk->id_save[wk->cursor]];
      if (evtBitCheck(v18->upDateTextFlag[0]))
      {
        upDateTextFlag = v18->upDateTextFlag;
        if (SLODWORD(upDateTextFlag->max_length) < 1)
        {
          v21 = 0;
        }
        else
        {
          v21 = 0;
          do
          {
            if (!evtBitCheck(upDateTextFlag[v21]))
              break;
            upDateTextFlag = v18->upDateTextFlag;
            ++v21;
          }
          while (v21 < SLODWORD(upDateTextFlag->max_length));
        }
        v23 = *(s32 *)((char *)v18->Quest_FloorID + (((v21 << 32) - 0x100000000LL) >> 30));
      }
      else
      {
        v23 = 0;
      }
      QuestMap_X = GetQuestMap_X(QUESTPAGE[wk->id_save[wk->cursor]]);
      QuestMap_Y = GetQuestMap_Y(QUESTPAGE[wk->id_save[wk->cursor]]);
      v7 = 1;
      if (QuestMap_X == INFINITY)
        v27 = 0x80000000;
      else
        v27 = QuestMap_X;
      if (QuestMap_Y == INFINITY)
        v28 = 0x80000000;
      else
        v28 = QuestMap_Y;
      ProcessStart(1, QuestMapNo, v23, v27, v28, 1, 0);
      v6 = 2;
      goto LABEL_78;
    case 2u:
      if (!ProcessCheck())
        return 1;
      if (jmsProcessCheck())
        goto LABEL_82;
      if (lmapProcessCheck())
      {
LABEL_82:
        mapMapFileFree();
        fldDestroyMapIconPool();
      }
      dds3FadeIn2(8u);
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      v9 = get_Instance(0);
      ItfButtonGuideSet(v9, 0, 0);
      active = PANEL02_ScrollBarActiveChack(bookUI, 0);
      v12 = &"DBOOK07";
      if (!active)
        v12 = &"DBOOK06";
      ButtonGuideDispSet(*v12, 0, 90);
      v7 = 1;
      v6 = 3;
      goto LABEL_78;
    case 3u:
      automapCheck = 0;
      clrAutomapIconList();
      if (!jmsProcessCheck())
      {
        if (!lmapProcessCheck())
        {
          QuestLoadMap = 1;
        }
      }
      wk->map_move = 0;
      Init();
      v6 = 0;
      v7 = 0;
LABEL_78:
      MapChackProc = v6;
      break;
    default:
      return 0;
  }
  return v7;
}

// 0x1bf7680
static s32 GetQuestMapNo(QUEST_TEXT_CLASS *_quest) {
  s32 result;
  s32 Quest_ID;
  s32 *upDateTextFlag;
  s64 v6;

  if (!evtBitCheck(quest->upDateTextFlag[0]))
    return 0;
  if (evtBitCheck(quest->ClearFlag))
    return 0;
  Quest_ID = quest->Quest_ID;
  if (Quest_ID == 25)
  {
    if (evtBitCheck(2617))
    {
      Quest_ID = quest->Quest_ID;
      goto LABEL_10;
    }
    return 0;
  }
LABEL_10:
  if (Quest_ID != 4)
    goto LABEL_14;
  result = fldZakuroChkReward();
  if (result)
  {
LABEL_14:
    upDateTextFlag = quest->upDateTextFlag;
    if (SLODWORD(upDateTextFlag->max_length) < 1)
    {
      v6 = 0;
    }
    else
    {
      v6 = 0;
      while (evtBitCheck(upDateTextFlag[v6]))
      {
        if (v6 == 3 && quest->Quest_ID == 1)
        {
          v6 = 3;
          return *(s32 *)((char *)quest->Quest_MapID + (((v6 << 32) - 0x100000000LL) >> 30));
        }
        upDateTextFlag = quest->upDateTextFlag;
        if (++v6 >= SLODWORD(upDateTextFlag->max_length))
          return *(s32 *)((char *)quest->Quest_MapID + (((v6 << 32) - 0x100000000LL) >> 30));
      }
    }
    return *(s32 *)((char *)quest->Quest_MapID + (((v6 << 32) - 0x100000000LL) >> 30));
  }
  return result;
}

// 0x1c02970
static s32 GetQuestFloorNo(QUEST_TEXT_CLASS *_quest) {
  s32 *upDateTextFlag;
  s64 v4;

  if (!evtBitCheck(quest->upDateTextFlag[0]))
    return 0;
  upDateTextFlag = quest->upDateTextFlag;
  if (SLODWORD(upDateTextFlag->max_length) < 1)
  {
    v4 = 0;
  }
  else
  {
    v4 = 0;
    do
    {
      if (!evtBitCheck(upDateTextFlag[v4]))
        break;
      upDateTextFlag = quest->upDateTextFlag;
      ++v4;
    }
    while (v4 < SLODWORD(upDateTextFlag->max_length));
  }
  return *(s32 *)((char *)quest->Quest_FloorID + (((v4 << 32) - 0x100000000LL) >> 30));
}

// 0x1c02a10
static f32 GetQuestMap_X(QUEST_TEXT_CLASS *_quest) {
  bool v3;
  f32 *Quest_X;
  f32 *v5;
  f32 *m_Items;
  bool v7;
  f32 result;
  s32 *upDateTextFlag;
  s64 v10;
  f32 *v11;

  if (quest->Quest_ID == 1)
  {
    if (evtBitCheck(12292))
    {
      v3 = evtBitCheck(12294);
      Quest_X = quest->Quest_X;
      v5 = &Quest_X[2];
      m_Items = &Quest_X[1];
      if (v3)
        m_Items = v5;
      return *m_Items;
    }
    v11 = quest->Quest_X;
  }
  else
  {
    v7 = evtBitCheck(quest->upDateTextFlag[0]);
    result = 0.0;
    if (!v7)
      return result;
    upDateTextFlag = quest->upDateTextFlag;
    if (SLODWORD(upDateTextFlag->max_length) < 1)
    {
      v10 = 0;
    }
    else
    {
      v10 = 0;
      do
      {
        if (!evtBitCheck(upDateTextFlag[v10]))
          break;
        upDateTextFlag = quest->upDateTextFlag;
        ++v10;
      }
      while (v10 < SLODWORD(upDateTextFlag->max_length));
    }
    v11 = ((char *)quest->Quest_X + (((v10 << 32) - 0x100000000LL) >> 30));
  }
  m_Items = v11;
  return *m_Items;
}

// 0x1c02af0
static f32 GetQuestMap_Y(QUEST_TEXT_CLASS *_quest) {
  bool v3;
  f32 *Quest_Y;
  f32 *v5;
  f32 *m_Items;
  bool v7;
  f32 result;
  s32 *upDateTextFlag;
  s64 v10;
  f32 *v11;

  if (quest->Quest_ID == 1)
  {
    if (evtBitCheck(12292))
    {
      v3 = evtBitCheck(12294);
      Quest_Y = quest->Quest_Y;
      v5 = &Quest_Y[2];
      m_Items = &Quest_Y[1];
      if (v3)
        m_Items = v5;
      return *m_Items;
    }
    v11 = quest->Quest_Y;
  }
  else
  {
    v7 = evtBitCheck(quest->upDateTextFlag[0]);
    result = 0.0;
    if (!v7)
      return result;
    upDateTextFlag = quest->upDateTextFlag;
    if (SLODWORD(upDateTextFlag->max_length) < 1)
    {
      v10 = 0;
    }
    else
    {
      v10 = 0;
      do
      {
        if (!evtBitCheck(upDateTextFlag[v10]))
          break;
        upDateTextFlag = quest->upDateTextFlag;
        ++v10;
      }
      while (v10 < SLODWORD(upDateTextFlag->max_length));
    }
    v11 = ((char *)quest->Quest_Y + (((v10 << 32) - 0x100000000LL) >> 30));
  }
  m_Items = v11;
  return *m_Items;
}
