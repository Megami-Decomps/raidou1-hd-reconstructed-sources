#pragma once
#include "types.h"
#include "BackRaiAnim.h"
#include "CMP_MENU_ID.h"
#include "CMP_MODE.h"
#include "CmpTitle.h"
#include "PanelFocus.h"
#include "kernel.h"

typedef enum {
    OMOIDE_SEL = 0,
    OMOIDE_CHK = 1,
    NATIVE_OMOIDE = 2,
    NATIVE_SKL = 3,
    SYOUGOU_SEL = 4,
    NATIVE_SEL = 5,
    GET_SPIRIT = 6,
    GET_BATTLE = 7,
} CMP_TITLE_ID;

typedef enum {
    CMP_GUIDE_TOP = 0,
    CMP_GUIDE_SKL_MENU = 1,
    CMP_GUIDE_SKL_TGT = 2,
    CMP_GUIDE_SKL_NON = 3,
    CMP_GUIDE_ITM_MENU = 4,
    CMP_GUIDE_ITM_USE_SEL = 5,
    CMP_GUIDE_ITM_TGT = 6,
    CMP_GUIDE_ITM_EXP = 7,
    CMP_GUIDE_ITM_TGT_NON = 8,
    CMP_GUIDE_ITM_EXP_NON = 9,
    CMP_GUIDE_ITM_SEIMEI = 10,
    CMP_GUIDE_ITM_SKL = 11,
    CMP_GUIDE_ITM_SKL_N = 12,
    CMP_GUIDE_SWD_SEL = 13,
    CMP_GUIDE_SWD_ST = 14,
    CMP_GUIDE_SWD_AFTER = 15,
    CMP_GUIDE_MAT_SEL = 16,
    CMP_GUIDE_EVT_DATA = 17,
    CMP_GUIDE_RD_SWORD_NON_SWD = 18,
    CMP_GUIDE_RD_SWORD_NON_SWD_2 = 19,
    CMP_GUIDE_RD_SWORD_NON = 20,
    CMP_GUIDE_RD_SWORD = 21,
    CMP_GUIDE_RD_SPIRIT = 22,
    CMP_GUIDE_ST_DVL = 23,
    CMP_GUIDE_ST_OMOIDE = 24,
    CMP_GUIDE_ST_SKL_NC = 25,
    CMP_GUIDE_ST_SKL = 26,
    CMP_GUIDE_ST_SKL_O_NC = 27,
    CMP_GUIDE_ST_SKL_O = 28,
    CMP_GUIDE_ST_SKL_CH = 29,
    CMP_GUIDE_ST_SKL_C = 30,
    CMP_GUIDE_ST_SKL_S = 31,
    CMP_GUIDE_ST_SPI_CHECK = 32,
    CMP_GUIDE_ST_SPI_LOG = 33,
    CMP_GUIDE_RD_SPIRIT_S = 34,
    CMP_GUIDE_RD_SYOUGO = 35,
    CMP_GUIDE_RD_SYOUGO_R = 36,
    CMP_GUIDE_VIEWER = 37,
    CMP_GUIDE_MAP_N = 38,
    CMP_GUIDE_MAP_H = 39,
    CMP_GUIDE_MAP_ICON = 40,
    CMP_GUIDE_MAP_CHG = 41,
    CMP_GUIDE_CMF_LR = 42,
    CMP_GUIDE_CMF_IN = 43,
    CMP_GUIDE_LOAD_SEL = 44,
    CMP_GUIDE_LOAD_CHK = 45,
    CMP_GUIDE_ORG_DEF = 46,
    CMP_GUIDE_ORG_ROOT_R = 47,
    CMP_GUIDE_ORG_ROOT_S = 48,
    CMP_GUIDE_ORG_DST = 49,
    CMP_GUIDE_ORT_DST_R = 50,
    CMP_GUIDE_ORG_DEF_W = 51,
    CMP_GUIDE_ORG_ROOT_S_W = 52,
    CMP_GUIDE_ORG_ROOT_S_N = 53,
    CMP_GUIDE_ORG_ROOT_S_W_N = 54,
    CMP_GUIDE_ORG_DST_N = 55,
    CMP_GUIDE_SKL_SET_MENU = 56,
    CMP_GUIDE_SKL_SET_MENU_R = 57,
    CMP_GUIDE_QUEST_N = 58,
    CMP_GUIDE_QUEST_H = 59,
    CMP_GUIDE_SKL_MENU_R = 60,
    CMP_GUIDE_SKL_TGT_R = 61,
    CMP_GUIDE_MAP_HL = 62,
    CMP_GUIDE_MAP_HU = 63,
    CMP_GUIDE_QUEST_HL = 64,
    CMP_GUIDE_QUEST_HU = 65,
    CMP_GUIDE_MAP_NB = 66,
    CMP_GUIDE_MAP_HB = 67,
    CMP_GUIDE_MAP_HLB = 68,
    CMP_GUIDE_MAP_HUB = 69,
} CMP_GUIDE;

typedef enum {
    CMP_DEF_OT_2D = 108,
    CMP_FADE_CNT = 15,
} CMP;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagCMP_WORK tagCMP_WORK;

extern void *debugSetting;
extern s32 testAnimNo;
extern bool subMenuActive;
extern bool exMenu;
extern bool itemNumDraw;
extern CMP_GUIDE oldGuide;
extern void *cmpGuides;
extern dds3ProcessID_t *g_mainPID;
extern dds3ProcessID_t *debugPID;
extern CMP_MODE g_endmode;
extern s8 g_GoldNoDspFlg;
extern void *menuName;
extern char *strCmpMenu;
extern void *helpName;
extern void *titleName;
extern u8 **cmptabsprtbl;
extern s16 **cmptabpostbl;

void cmpLoadLocalizeText(void);
void cmpCmpGuideSet(CMP_GUIDE _id, bool _timer, s32 _waitTimer);
bool cmpStatusViewTitleOff(void);
void cmpMenuTitleDrawUnity(void);
void cmpUnityBackRaidouDraw(void);
void cmpUnityUiDraw(void);
bool cmpNowStatus(void);
void MainManuDraw(void);
void MainMenuCursorMove(void);
void cmpDrawMenuFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void cmpCallProcEnd(tagCMP_WORK *wk);
u8 cmpCheckProcEnd(tagCMP_WORK *wk);
bool cmpEventMenuChk(void);
tagCMP_WORK *cmpGetWork(void);
dds3ProcessID_t *cmpGetMenuPID(void);
dds3ProcessID_t *cmpGetCharPID(void);
dds3ProcessID_t *cmpGetStockPID(void);
void cmpSetStockPanelActive(PanelFocus _active, bool _se);
PanelFocus cmpGetStockPanelActive(void);
dds3ProcessID_t *cmpGetListPID(void);
dds3ProcessID_t *cmpGetsubMenuPID(void);
void cmpSetTabFlag(s8 flg);
void cmpSetHelpFlag(s8 flg);
void cmpSetGoldFlag(s8 flg);
void cmpSetItemNumDraw(bool _draw);
void cmpSetHelpDispFlag(s8 flg);
bool cmpChkUnopenedMenu(CMP_MENU_ID index);
char *cmpGetUnopenedMenuName(CMP_MENU_ID index, bool label);
char *cmpGetstrCmpMenuHD(CMP_MENU_ID index, bool label);
char *cmpGetTitleText(CMP_TITLE_ID index);
char *cmpGetstrCmpMenu(s32 index, bool label);
s32 cmpChkTabChg(void);
void cmpMenuMaskSet(void);
void cmpTitleChange(CMP_MENU_ID _id);
s32 cmpCallFunc(void);
void cmpChkEnableSelectMenuItem(tagCMP_WORK *wk);
void cmpChkEnableDecideMenu2(tagCMP_WORK *wk);
void cmpChkEnableSelectMenu(tagCMP_WORK *wk);
s32 cmpSubMenuAnimFunc(s32 mode);
s32 cmpExSubMenuAnimFunc(s32 mode);
s32 cmpWeaponMenuAnimFunc(s32 mode);
void cmpSetMenu(tagCMP_WORK *wk);
void cmpPanelChange(tagCMP_WORK *_wk);
void cmpRaidouBackChange(BackRaiAnim _changeAnim);
void TitleChange(CmpTitle _cmpTitle);
bool cmpTipsCalc(tagCMP_WORK *_wk);
void cmpSelectUpdate(tagCMP_WORK *_wk);
void cmpContentUpdate(tagCMP_WORK *_wk);
void cmpRodiouMeganeCheck(void);
void Init(tagCMP_WORK *wk);
void cmpUiInit(void);
dds3ProcessFunc_t cmpProcess(dds3ProcessID_t *PID);
void cmpDebugLoadFlagOff(void);
void cmpDrawTop(tagCMP_WORK *wk, u8 a_alphaRate);
void cmpDrawHelpWindow(u8 a_alphaRate, CMP a_ot);
void cmpDrawHelpText(tagCMP_WORK *wk, u8 a_alphaRate);
void cmpDrawKeyReturnHelp(tagCMP_WORK *wk, u8 a_alphaRate1, u8 a_alphaRate2);
void cmpDrawKeyHelp(tagCMP_WORK *wk, u8 a_alphaRate1, u8 a_alphaRate2);
void cmpDrawKeyHelp2(tagCMP_WORK *wk, u8 a_alphaRate1, u8 a_alphaRate2);
void cmpDrawKeyHelp3(tagCMP_WORK *wk, u8 a_alphaRate1, s32 ax);
void cmpDrawTab(tagCMP_WORK *wk, u8 a_alphaRate1);
void cmpDrawBulletData(s32 a_alphaRate);
void cmpDrawBackSpriteAlpha(s32 a_sprNo, s32 a_x, s32 a_y, s32 a_alphaRate, sprHandle_t *a_hSpr);
void cmpDrawBackSprA1(s32 a_sprNo, s32 a_x, s32 a_y, s32 a_alphaRate);
void cmpDrawBackSprA2(s32 a_sprNo, s32 a_x, s32 a_y, s32 a_alphaRate);
void cmpDrawBackPartsA(s32 a_x, s32 a_y, s32 a_alphaRate);
void cmpDrawBackPartsB(s32 a_x, s32 a_y, s32 a_alphaRate);
void cmpDrawBackGradation(s32 a_rate);
void cmpDrawBackStat2(s32 a_alphaRate);
void cmpDrawBackStat4(s32 a_alphaRate);
void cmpDrawBackMain1(s32 a_alphaRate);
void cmpDrawBackMain3(s32 a_alphaRate);
void cmpDrawBackMain5(s32 a_alphaRate);
void MainDrawBack(tagCMP_WORK *wk, s32 a_alphaRate);
bool cmpHelpDrawCheckUnity(tagCMP_WORK *_wk, CMP_MENU_ID _id);
dds3ProcessFunc_t cmpDrawProcess(dds3ProcessID_t *PID);
CMP_MODE cmpGetEndMode(void);
void cmpSetMarkID(s32 a_markID);
s32 cmpGetMarkID(void);
void cmpRelease(tagCMP_WORK *wk);
void cmpShutdown(dds3ProcessID_t *PID);
void cmpProcessStartEx(CMP_MODE a_runmode);
void cmpProcessStart(void);
void cmpProcessEnd(void);
bool cmpProcessCheck(void);
void cmpRestorBgm(s32 reqBgm);
bool cmpUpdateSuspend(tagCMP_WORK *wk);
void cmpSuspendEndProc(void);
void cmpEndMesChk(tagCMP_WORK *wk);
