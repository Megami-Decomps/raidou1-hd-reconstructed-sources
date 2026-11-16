#pragma once
#include "types.h"
#include "kernel.h"

typedef enum {
    KEYWORD_MENUTYPE_CAMP = 0,
    KEYWORD_MENUTYPE_JMS = 1,
} KEYWORD_MENUTYPE;

typedef enum {
    KEYWORDMENU_FLAG_RELEASE = 1,
    KEYWORDMENU_FLAG_DRAW = 2,
    KEYWORDMENU_FLAG_LOAD_SPR_MEM = 4,
    KEYWORDMENU_FLAG_LOAD_SPR_HND = 8,
    KEYWORDMENU_FLAG_CALL_START = 16,
    KEYWORDMENU_FLAG_CALL_END = 32,
} KEYWORDMENU_FLAG;

typedef enum {
    KEYWORDMENU_STEP_WAIT = 0,
    KEYWORDMENU_STEP_WAIT2 = 1,
    KEYWORDMENU_STEP_MAIN = 2,
    KEYWORDMENU_STEP_MAIN2 = 3,
    KEYWORDMENU_STEP_MSG = 4,
    KEYWORDMENU_STEP_MSG_WAIT = 5,
    KEYWORDMENU_STEP_RELEASE = 6,
    KEYWORDMENU_STEP_END_WAIT = 7,
    KEYWORDMENU_STEP_END = 8,
} KEYWORDMENU_STEP;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagKEYWORD_MENU_WORK tagKEYWORD_MENU_WORK;

struct tagKEYWORD_MENU_WORK {
    sprHandle_t *hSpr;
    dds3ProcessID_t *menuPID;
    dds3ProcessID_t *listPID;
    dds3ProcessID_t *keywordPID;
    KEYWORDMENU_STEP step;
    KEYWORDMENU_FLAG flag;
    s16 count;
    s32 selectID;
    s32 selectID2;
    s32 msgno;
    f32 fNewAAnm;
    f32 fNewAlpha;
};

extern char *strkeywordcate;
extern char *strkeyword;
extern itfSprList_t *arrSprListTitle;
extern itfSprList_t *arrSprListPanel;
extern itfSprList_t *arrSprListSelect;
extern itfSprList_t *arrSprListScrollBar;
extern itfSprList_t *arrSprListPanel2;
extern itfSprList_t *arrSprListSelect2;
extern dds3ProcessID_t *g_mainPID;
extern s16 g_keywordNum;
extern s16 g_keywordctNum;
extern s16 *g_keywordctList;
extern s16 *g_keywordList;
extern KEYWORD_MENUTYPE g_KeyMenuType;

void cmpMenuSetMenuImage(dds3ProcessID_t *PID);
bool cmpCateFlgChk(s32 cateno);
bool cmpReadFlgChk(s64 cateno);
void cmpReadFlgOn(s64 cateno);
s32 cmpMakeCateChk(void);
void cmpMakekeywordctlist(void);
void cmpMakekeywordlist(s32 cateno);
s32 cmpMenuDecideFunc2(void);
s32 cmpMenuDecideFunc(void);
void cmpListDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void cmpMenuDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void cmpMenuSetMenuImage2(dds3ProcessID_t *PID);
dds3ProcessID_t *cmpMenuCreateListPID(void);
dds3ProcessID_t *cmpMenuCreateMenuPID(void);
void cmpMenuCallProcEnd(tagKEYWORD_MENU_WORK *wk);
s8 cmpMenuCheckProcEnd(tagKEYWORD_MENU_WORK *wk);
dds3ProcessFunc_t cmpMenuProcess(dds3ProcessID_t *PID);
bool cmpMenuCheckWait(void);
bool cmpMenuStart(void);
s32 cmpMenuGetSelectID(void);
void cmpMenuRelease(tagKEYWORD_MENU_WORK *wk);
void cmpMenuShutdown(dds3ProcessID_t *PID);
void cmpProcStart(KEYWORD_MENUTYPE type);
void cmpMenuProcessStart(void);
void cmpMenuProcessEnd(void);
bool cmpMenuProcessCheck(void);
bool Update(void);
