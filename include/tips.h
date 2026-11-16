#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;
typedef struct tipsPanelData tipsPanelData;
typedef struct tipsPanelDataAll tipsPanelDataAll;
typedef struct tips_tipsData_t tips_tipsData_t;
typedef struct tips_tipsData_t_ChildSave tips_tipsData_t_ChildSave;

struct tipsPanelData {
    s32 ID;
    char *title;
    s32 page;
    char *text;
    s32 image;
    s32 rawimage;
    s32 parent;
};

struct tipsPanelDataAll {
    s32 ID;
    char *title;
    s32 page;
    char *text_all[5];
    s32 image;
    s32 rawimage;
    s32 parent;
    s32 child;
};

struct tips_tipsData_t_ChildSave {
    s32 parent;
    char *text[128];
    s32 ID[128];
    s32 type[128];
};

struct tips_tipsData_t {
    s32 mainStep;
    tipsPanelData *panel;
    tipsPanelData *panel_new;
    f32 alpha;
    s32 nowpage;
    s32 page_wait;
    s32 textChangeStep;
    u8 step;
    s32 flag;
    s16 count;
    s32 index;
    s16 dummy;
    s32 nextDestNowPage;
    s32 menu_num;
    s32 cursor;
    s32 cursor_old;
    s32 cursor_parent;
    s32 cursor_ID;
    s32 parentCursor_save;
    bool open_flag;
    bool change_flag;
    s32 top;
    s32 sel;
    s32 draw;
    s32 parentID[2];
    s32 parentID_Befor;
    s32 child_num;
    s32 menu_child;
    s32 child_move;
    bool move_flag;
    bool open_move;
    bool menu_move;
    s32 moveCount;
    s32 menu_draw[12];
    s32 menu_drawOld[12];
    bool menu_topChange;
    s32 menu_Before[12];
    s32 menu_After[12];
    s32 Before_Save[12];
    bool menu_childMove;
    char *draw_text[128];
    s32 parent_save[128];
    s32 id_save[128];
    s32 type_save[128];
    s32 child_NumMax[2];
    tips_tipsData_t_ChildSave *child_save[2];
};

extern s32 pageCnt;
extern s32 TIPS_ID;
extern tipsPanelData *TIPS_ID_TABLE;
extern tipsPanelDataAll *TIPS_ID_TABLE_ALL;
extern dds3ProcessID_t *GlobalPID;
extern fileLoadAsset_Request *SceneLoadReq;
extern tips_tipsData_t *mainData;
extern s32 tipsMode;
extern bool tipsCanselFlag;
extern bool tipsCanselIDFlg;
extern char *TIPS_ASSET_NAME;
extern char *TIPSDATA_ASSET_NAME;
extern char *TIPSDATATABLE_NAME;
extern char *tipsProcessName;
extern char *tipsAllProcessName;
extern bool tutorialFlag;
extern s32 TIPS_MAX;
extern s32 childCnt;
extern s32 childSave;
extern s32 *parentID;
extern s32 *openStatus;
extern s32 *tutorialTIPS_All;
extern s32 *SortOderUpTIPS;
extern bool OderUpFlag;

dds3ProcessID_t *tipsTIPSStart_ALL(void);
void tipsTISPStartCalc(s32 TIPSID);
void tipsDestCall(s32 TIPSID);
void tipsReDestCall(void);
void tipsReDestEnd(void);
dds3ProcessID_t *tipsTIPSStart(s32 TIPSID);
void tipsTIPSDestroy(dds3ProcessID_t *PID);
s32 tipsProcessCheck(void);
s32 tipsProcessCheck_tipsAll(void);
tips_tipsData_t *tipsTIPSInit(s32 ID);
void tipsInit_Unload(void);
tips_tipsData_t *tipsTIPSInit_ALL(void);
void tipsSetPanelDataTableSub(tipsPanelData *PanelDataTable, tipsPanelData *PanelDataTableSub, s32 ID);
void tipsSetPanelDataTable_ALL(tips_tipsData_t *data, tipsPanelData *PanelDataTable, tipsPanelDataAll *PanelDataTableSub, s32 ID);
s32 tipsGetTIPSID(void);
dds3ProcessFunc_t tipsTIPS_Process(dds3ProcessID_t *PID);
dds3ProcessFunc_t tipsTIPS_ALLProcess(dds3ProcessID_t *PID);
bool tipsGuideOffCheck(void);
char *tipsChangeTextPLTF(char *text);
