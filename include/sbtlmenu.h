#pragma once
#include "types.h"
#include "DEVIL_STATUS_TYPE.h"
#include "ITM.h"
#include "SBTL_MENU_ID.h"
#include "SKLID.h"
#include "itfMenuDrawFunc_t.h"
#include "itfMenuFunc_t.h"
#include "kernel.h"

#define ROOT_OFS_X 80
#define CHAR_OFS_X 52
#define SKILL_OFS_X -10
#define SE_PAGE 65567

typedef enum {
    SBTL_MENU_FLAG_RELEASE = 1,
    SBTL_MENU_FLAG_DRAW = 2,
    SBTL_MENU_FLAG_LOAD_SPR_MEM = 4,
    SBTL_MENU_FLAG_LOAD_SPR_HND = 8,
    SBTL_MENU_FLAG_CALL_START = 16,
    SBTL_MENU_FLAG_CALL_END = 32,
    SBTL_MENU_FLAG_STARTORDER = 64,
} SBTL_MENU_FLAG;

typedef enum {
    SBTL_MENU_STEP_INIT = 0,
    SBTL_MENU_STEP_WAIT = 1,
    SBTL_MENU_STEP_MAIN = 2,
    SBTL_MENU_STEP_LIST = 3,
    SBTL_MENU_STEP_CHAR = 4,
    SBTL_MENU_STEP_CHAR2 = 5,
    SBTL_MENU_STEP_NAKAMA = 6,
    SBTL_MENU_STEP_NAKAMA2 = 7,
    SBTL_MENU_STEP_ORDER = 8,
    SBTL_MENU_STEP_STOCK = 9,
    SBTL_MENU_STEP_ITEMTGTSTK = 10,
    SBTL_MENU_STEP_ITEMTGTSTOCK = 11,
    SBTL_MENU_STEP_EQUIP = 12,
    SBTL_MENU_STEP_ANALYZE = 13,
    SBTL_MENU_STEP_STARTORDER = 14,
    SBTL_MENU_STEP_MAIGO = 15,
    SBTL_MENU_STEP_WAITLOADEFFECT = 16,
    SBTL_MENU_STEP_STATUS = 17,
    SBTL_MENU_STEP_ENEMY = 18,
    SBTL_MENU_STEP_RELEASE = 19,
    SBTL_MENU_STEP_END_WAIT = 20,
    SBTL_MENU_STEP_DITECTIVEBOOKINIT = 21,
    SBTL_MENU_STEP_DITECTIVEBOOKWAIT = 22,
    SBTL_MENU_STEP_K_DIRECT = 23,
    SBTL_MENU_STEP_CONFIG = 24,
    SBTL_MENU_STEP_START_TIPS = 25,
    SBTL_MENU_STEP_START_SCRIPT = 26,
    SBTL_MENU_STEP_ITEM_SCRIPT = 27,
    SBTL_MENU_STEP_END = 28,
} SBTL_MENU_STEP;

typedef enum {
    SBTL_MENU_BEFOR_STEP_NONE = 0,
    SBTL_MENU_BEFOR_STEP_STOCK = 1,
    SBTL_MENU_BEFOR_STEP_NAKAMA = 2,
    SBTL_MENU_BEFOR_STEP_NAKAMA2 = 3,
    SBTL_MENU_BEFOR_STEP_ORDER = 4,
    SBTL_MENU_BEFOR_STEP_STARTORDER = 5,
    SBTL_MENU_BEFOR_STEP_ITEMTGTSTK = 6,
    SBTL_MENU_BEFOR_STEP_ITEMTGTSTOCK = 7,
    SBTL_MENU_BEFOR_STEP_MAX = 8,
} SBTL_MENU_BEFOR_STEP;

typedef enum {
    SBTL_MENU_INFO_TYPE_NONE = 0,
    SBTL_MENU_INFO_TYPE_RAIDO = 1,
    SBTL_MENU_INFO_TYPE_NAKAMA = 2,
    SBTL_MENU_INFO_TYPE_ENEMY = 3,
    SBTL_MENU_INFO_TYPE_MAX = 4,
} SBTL_MENU_INFO_TYPE;

typedef enum {
    SBTLMENU_TYPE_TRIG = 0,
    SBTLMENU_TYPE_START = 1,
} SBTLMENU_TYPE;

typedef enum {
    SBTLMENU_NODE_NONE = 0,
    SBTLMENU_NODE_ROOT = 1,
    SBTLMENU_NODE_ORDER = 2,
    SBTLMENU_NODE_SUMMON = 3,
    SBTLMENU_NODE_RETURN = 4,
    SBTLMENU_NODE_ITEM = 5,
    SBTLMENU_NODE_KATANA = 6,
    SBTLMENU_NODE_ANALYZE = 7,
    SBTLMENU_NODE_TALK = 8,
} SBTLMENU_NODE;

typedef enum {
    SBTLMENU_ENDTYPE_NONE = 0,
    SBTLMENU_ENDTYPE_ESCAPE = 1,
    SBTLMENU_ENDTYPE_TALK = 2,
} SBTLMENU_ENDTYPE;

typedef enum {
    SBTLMENU_ENABLETALK_ERROR = 0,
    SBTLMENU_ENABLETALK_OK = 1,
    SBTLMENU_ENABLETALK_NG = 2,
    SBTLMENU_ENABLETALK_NG_BST = 3,
    SBTLMENU_ENABLETALK_NG_BREAK = 4,
} SBTLMENU_ENABLETALK;

typedef enum {
    SBTLMENU_BIT_MOON_ESCAPE = 1,
    SBTLMENU_BIT_MOON_ANALYZE = 2,
    SBTLMENU_BIT_MOON_TUTORIAL = 4,
} SBTLMENU_BIT_MOON;

typedef enum {
    SBTLMENU_HELP_DUMMY = 0,
    SBTLMENU_HELP_PLAN = 1,
    SBTLMENU_HELP_SUMMON = 2,
    SBTLMENU_HELP_RETURN = 3,
    SBTLMENU_HELP_BULLET = 4,
    SBTLMENU_HELP_ITEM = 5,
    SBTLMENU_HELP_ANALYZE = 6,
    SBTLMENU_HELP_ESCAPE = 7,
    SBTLMENU_HELP_ESCAPE_CANCEL = 8,
    SBTLMENU_HELP_TALK = 9,
    SBTLMENU_HELP_START = 10,
    SBTLMENU_HELP_SKILL_SEL2 = 11,
    SBTLMENU_HELP_SUMMON_SEL = 12,
    SBTLMENU_HELP_SUMMON_SEL2 = 13,
    SBTLMENU_HELP_RETURN_SEL = 14,
    SBTLMENU_HELP_ITEM_SEL2 = 15,
    SBTLMENU_HELP_ANALYZE_SEL = 16,
    SBTLMENU_HELP_TALK_SEL = 17,
    SBTLMENU_HELP_CMBOUT = 18,
    SBTLMENU_HELP_RETURN_BST = 19,
    SBTLMENU_HELP_CMBOUT2 = 20,
    SBTLMENU_HELP_DITECTIVEBOOK = 21,
    SBTLMENU_HELP_KATANA = 22,
    SBTLMENU_HELP_K_DIRECT = 23,
    SBTLMENU_HELP_CONFIG = 24,
} SBTLMENU_HELP;

typedef enum {
    SBTL_MENU_NAKAMA2_NONE = 0,
    SBTL_MENU_NAKAMA2_SUMMON = 1,
    SBTL_MENU_NAKAMA2_RETURN = 2,
} SBTL_MENU_NAKAMA2;

typedef struct DevilSkillCsr DevilSkillCsr;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct sBtlMenu_t sBtlMenu_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

struct DevilSkillCsr {
    s32 cursorNo;
    s32 listTop;
    s32 listDrwNo;
    bool statusSkillCsr;
};

struct sBtlMenu_t {
    dds3ProcessID_t *drawPID;
    dds3ProcessID_t *menuPID;
    dds3ProcessID_t *listPID;
    dds3ProcessID_t *charPID;
    dds3ProcessID_t *nakamaPID;
    dds3ProcessID_t *stockPID;
    SBTL_MENU_STEP step;
    SBTL_MENU_FLAG flag;
    s16 count;
    s32 menuID;
    s32 cntAnalyze;
    SBTLMENU_TYPE type;
    SBTLMENU_ENDTYPE endtype;
    SBTL_MENU_ID short_cut_id;
    s32 open1st;
    DEVIL_STATUS_TYPE skilltype;
    s32 FadeInDelay;
    s32 FadeInDelayCnt;
    s32 itemScrReq;
    dds3ProcessID_t *itemScr;
    ITM scrItem;
    s32 analyze_shortcut_delay;
};

extern s8 g_nakamaTab;
extern bool g_nakamaTabMov;
extern dds3ProcessID_t *g_mainPID;
extern sprHandle_t *g_hSpr;
extern SBTLMENU_BIT_MOON g_bitMoon;
extern s32 g_equipNo;
extern s32 g_equipNoOld;
extern s32 *lastOrangePar;
extern s32 *param;
extern sdatUnitWork_t *unitCsr;
extern sdatUnitWork_t *stockUnitTgt;
extern DevilSkillCsr *devilSkillcsr;
extern bool devilInfo;
extern SBTL_MENU_BEFOR_STEP menuBeforFlag;
extern DEVIL_STATUS_TYPE skilltype;
extern SBTL_MENU_INFO_TYPE infotype;
extern bool bRikamu;
extern SBTLUNIT_WORK *EnemyUnitTgt;
extern s32 enemyNowCsr;
extern s32 enemyNumCount;
extern bool orderMenuCtrl;
extern bool shortcutFlag;
extern SBTLUNIT_WORK *saveUnitTgt;
extern bool analizeChangeFlag;
extern s32 MenuCnt;
extern bool MenuShortCutFarst;
extern bool returnFlag;
extern bool menu_onoff;
extern void *animChengeTbl;
extern itfSprList_t *arr_sBtlMenu_MenuPanel;
extern itfSprList_t *arr_sBtlMenu_MenuSelect;
extern itfSprList_t *arr_sBtlMenu_MenuTitle;
extern itfSprList_t *arr_sBtlMenu_MenuScrollBar;
extern SBTLMENU_HELP *s_sBtlMenuHelpNo;
extern SBTLMENU_NODE *s_sBtlMenuNode;
extern char *s_strRepeat;

char *sBtlGetMenuStr(s32 index);
char *sBtlGetMenuHelpStr(s32 index);
bool sBtlShortCutStart(s32 com_no, s32 com_smn_idx);
bool sBtlGetShortCutFlg(void);
void sBtlCallEnd(sBtlMenu_t *wk);
bool sBtlIsAnalyzeShortCut(void);
s32 sBtlFuncSummonList(void);
s32 sBtlGetTabLimitCharStock(s32 *a_pmin, s32 *a_pmax);
s32 sBtlGetTabLimitCharItem(s32 *a_pmin, s32 *a_pmax);
sBtlMenu_t *sBtlGetWork(void);
void sBtlDrawTargetCursorNakama(s32 a_nakamaId);
void sBtlDrawTargetCursorEnemy(void);
void sBtlDrawTargetCharList(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
s32 sBtlReturnAL(void);
s32 sBtlFuncSummonExe(void);
void sBtlMakeNakamaList(itfMenuFunc_t pFunc, itfMenuDrawFunc_t pDrawFunc, SBTL_MENU_NAKAMA2 pMenu_nakama2);
void sBtlSetFadeOutMoon(void);
SBTLMENU_ENABLETALK sBtlCheckEnableTalk(SBTLUNIT_WORK *unit);
void sBtlSetMenuImage(dds3ProcessID_t *PID);
dds3ProcessID_t *sBtlInitMenuPID(u8 a_max);
void sBtlDrawFuncTalk(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
void sBtlDrawAnalyzePlayer(s32 a_id, u8 a_alphaRate);
void sBtlDrawFuncPartyDat(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void sBtlDrawFuncStockDat(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void sBtlDrawFuncSummon(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
s32 sBtlFuncStart(void);
bool sBtlSkillChkUseUnit(sdatUnitWork_t *unit, SKLID a_skillID);
s32 sBtlFuncMeirei(void);
void sBtlDrawFuncSummon2(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
s32 sBtlFuncSummon2(void);
s32 sBtlFuncSummon(void);
void sBtlDrawFuncReturn(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
s32 sBtlFuncReturn(void);
s32 sBtlFuncDecideItemTarget(void);
s32 sBtlFuncDecideItemTargetStock(void);
bool sBtlItemChkUseUnit(sdatUnitWork_t *a_pUnit, s32 a_itemId);
bool sBtlItemChkUseUnitEx(sdatUnitWork_t *a_pUnit, s32 a_itemId, bool a_bStock);
void sBtlSetItemScript(sBtlMenu_t *_wk, ITM _itemID);
s32 sBtlFuncDecideItem(void);
s32 sBtlFuncDecideItemStock(void);
void sBtlDrawFuncItem(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
s32 sBtlItemChkUse(s32 a_itemId);
s32 sBtlFuncItem(void);
s32 sBtlFuncKatana(void);
void sBtlDrawFuncKatana(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void sBtlDrawBeforeSwordParam(s32 a_swordno, s32 a_swordno_chk, u32 a_swordnameColor);
void sBtlDrawParam(s32 a_type);
bool sBtlSetType(s32 a_katanano, bool _root);
void sBtlSetEquipKatanaNo(s32 iKatanaNo);
s32 sBtlFuncDecideAnalyze(void);
void sBtlDrawFuncAnalyze(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
s32 sBtlFuncAnalyze(void);
void sBtlAnalizeEnemySel(void);
s32 sBtlFuncEscape(void);
s32 sBtlFuncDecideTalk(void);
s32 sBtlFuncTalk(void);
s32 sBtlFuncDitectiveBook(void);
bool sBtlSetTalkDisable(sBtlMenu_t *pMW);
s32 sBtlFuncKuzunohaDirect(void);
s32 sBtlFuncConfig(void);
bool sBtlChkTutorialMenu(SBTL_MENU_ID id);
void sBtlChkEnableDecideMenu(sBtlMenu_t *wk);
bool sBtlIsMeirei(SBTLUNIT_WORK *wklock);
void Init(sBtlMenu_t *wk);
void sBtlCallProcEnd(sBtlMenu_t *wk);
u8 sBtlCheckProcEnd(sBtlMenu_t *wk);
bool sBtlChkCallEnd(sBtlMenu_t *wk);
dds3ProcessFunc_t sBtlProcess(dds3ProcessID_t *PID);
void MenuItemScrUpdate(sBtlMenu_t *wk);
void sBtlRelease(sBtlMenu_t *wk);
void sBtlShutdown(dds3ProcessID_t *PID);
dds3ProcessFunc_t sBtlDrawProcess(dds3ProcessID_t *PID);
void sBtlSetStartEx(SBTLMENU_TYPE a_type);
bool sBtlIsMenuStartScript(void);
void sBtlSetStart(void);
bool IsStart(void);
void ProcessStart(void);
void sBtlProcessEnd(void);
bool ProcessCheck(void);
SBTLMENU_NODE sBtlGetNode(void);
SBTLUNIT_WORK *GetActionUnit(void);
s32 sBtlGetTargetUnitIndex(void);
SBTLUNIT_WORK *GetTargetUnit(void);
void sBtlDrawTabPanel(s32 a_x, s32 a_y, s32 a_z, f32 a_alphaRate, s32 a_min, s32 a_max, s32 a_sel, s32 a_ofs);
void sBtlDrawTabPanelCharList(s32 a_min, s32 a_max, s32 a_sel, s32 a_ofs, f32 a_alphaRate);
void MenuActive(bool _active);
