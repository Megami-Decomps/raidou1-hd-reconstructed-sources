#pragma once
#include "types.h"
#include "CMP_MENU_ID.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;

extern dds3ProcessID_t *g_listPID;
extern dds3ProcessID_t *g_charPID;
extern u8 g_step;
extern s32 g_itemNo;
extern s32 g_charNo;
extern CMP_MENU_ID g_menuID;
extern u16 *g_arrItemID;
extern s32 g_itemNum;
extern itfSprList_t *cmpSprListItemPanel;
extern itfSprList_t *cmpSprListItemSelect;
extern itfSprList_t *cmpSprListItemPanelTop;
extern itfSprList_t *cmpSprListItemScroll;

void cmpDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void cmpSetup(CMP_MENU_ID a_id);
s32 cmpMakeList(CMP_MENU_ID a_id);
bool cmpUpdateKeyWord(void);
bool cmpUpdateItem(void);
bool cmpUpdateMushi(void);
bool cmpUpdateEvent(void);
s32 cmpGetEventNo(void);
bool cmpUpdate(void);
void cmpInitLuckPoint(s32 a_max, s32 a_max1st);
void cmpDeleteMushi(s32 a_itemid);
s32 Command_INIT_LUCKPOINT(void);
