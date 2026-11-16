#pragma once
#include "types.h"
#include "GOH_MENU_ID.h"
#include "ITFMENU_CB_GF.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct tagGOH_MENU_WORK tagGOH_MENU_WORK;

extern dds3ProcessID_t *g_mainPID;
extern char *strGohMenu;
extern itfSprList_t *arrGohMenuPanel;
extern itfSprList_t *arrGohMenuSelect;
extern itfSprList_t *arrGohMenuTitle;
extern bool gohMenuActive;

s32 MenuAnimFunc(s32 mode);
s32 gohCallFunc(void);
s32 gohCheckOpen(GOH_MENU_ID MenuID);
void gohSetCommand(tagGOH_MENU_WORK *wk);
dds3ProcessFunc_t gohProcess(dds3ProcessID_t *PID);
GOH_MENU_ID gohGetSelectIndex(void);
void gohDrawTitle(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
bool gohBackCombMenuCheck(void);
void gohChkEnableSelect(tagGOH_MENU_WORK *wk);
void gohSetRootMenu(dds3ProcessID_t *PID, GOH_MENU_ID MenuID, char *pStr);
void gohSetMenu(dds3ProcessID_t *PID, GOH_MENU_ID MenuID, GOH_MENU_ID ParentMenuID, char *pStr);
void gohSetFlagMenu(dds3ProcessID_t *PID, GOH_MENU_ID MenuID, ITFMENU_CB_GF Flag, bool Bool);
void gohCallProcEnd(tagGOH_MENU_WORK *wk);
u8 gohCheckProcEnd(tagGOH_MENU_WORK *wk);
void gohShutdown(dds3ProcessID_t *PID);
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
void gohSetSelectIndex(GOH_MENU_ID idx);
void gohStart(void);
void gohSetLock(bool a_bLock);
void gohSetFocus(bool a_bFocus);
bool gohGetFocus(void);
void gohCallDrawBack(void);
void gohSetDrawBack(bool a_bDraw, bool a_bFade);
s8 gohGetBackStat(void);
void ProcessStart(void);
void ProcessEnd(void);
bool ProcessCheck(void);
void gohSetEnableSelect(GOH_MENU_ID MenuID, bool Bool);
s32 gohCheckMovePrev(void);
void gohSetDraw(bool a_bDraw);
dds3ProcessID_t *gohGetMenuPID(void);
