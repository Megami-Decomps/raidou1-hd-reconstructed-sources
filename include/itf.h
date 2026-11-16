#pragma once
#include "types.h"
#include "ITFMENU_CB_GF.h"
#include "interface.h"
#include "itfMenuDrawFunc_t.h"
#include "itfMenuFunc_t.h"
#include "kernel.h"
#include "libsdf.h"

typedef enum {
    ITF_LIST_CB_MAX = 8,
    ITF_LIST_FADE_FRAME = 10,
    ITF_LIST_FONT_Z = 1048576,
    ITF_LIST_PANEL_Z = 256,
} ITF_LIST;

typedef enum {
    MENU_STEP_INIT = 0,
    MENU_STEP_SET_WAIT = 1,
    MENU_STEP_UPDATE = 2,
    MENU_STEP_UPDATE_WAIT = 3,
    MENU_STEP_UPDATE_WAIT2 = 4,
    MENU_STEP_FUNC_CALL = 5,
    MENU_STEP_FUNC_WAIT = 6,
    MENU_STEP_RELEASE = 7,
    MENU_STEP_DATASET = 8,
    MENU_STEP_END = 9,
} MENU_STEP;

typedef enum {
    MENU_KEY_TYPE_NONE = 0,
    MENU_KEY_TYPE_TRIG_U = 1,
    MENU_KEY_TYPE_REP_U = 2,
    MENU_KEY_TYPE_TRIG_D = 3,
    MENU_KEY_TYPE_REP_D = 4,
    MENU_KEY_TYPE_REP_L = 5,
    MENU_KEY_TYPE_REP_R = 6,
} MENU_KEY_TYPE;

typedef enum {
    itf_PADREAD_PRESS = 1,
    itf_PADREAD_TRIG = 2,
    itf_PADREAD_REPT = 4,
} itf_PADREAD;

typedef enum {
    ITF_COUNT_TYPE_NONE = 0,
    ITF_COUNT_TYPE_SUB = 1,
    ITF_COUNT_TYPE_ADD = 2,
} ITF_COUNT_TYPE;

typedef enum {
    ITF_DM_STYLE_SFNT_CNV = 0,
    ITF_DM_STYLE_SFNT = 1,
    ITF_DM_STYLE_LFNT = 2,
    ITF_DM_STYLE_SNUM = 3,
    ITF_DM_STYLE_LNUM = 4,
    ITF_DM_STYLE_NUM = 5,
} ITF_DM_STYLE;

typedef enum {
    ITF_LIST_TYPE_NONE = 0,
    ITF_LIST_TYPE_NORMAL = 1,
    ITF_LIST_TYPE_MAX = 2,
} ITF_LIST_TYPE;

typedef enum {
    ITFMENU_IMG_DAT_TITLE = 0,
    ITFMENU_IMG_DAT_PANEL = 1,
    ITFMENU_IMG_DAT_SELECT = 2,
    ITFMENU_IMG_DAT_SCROLL = 3,
    ITFMENU_IMG_DAT_MAX = 4,
} ITFMENU_IMG_DAT;

typedef enum {
    ITFMENU_SCROLL_TYPE_SWITCH = 0,
    ITFMENU_SCROLL_TYPE_N_DISP = 1,
    ITFMENU_SCROLL_TYPE___DISP = 2,
} ITFMENU_SCROLL_TYPE;

typedef enum {
    ITFMENU_MOVE_TYPE_NONE = 0,
    ITFMENU_MOVE_TYPE_PREV = 1,
    ITFMENU_MOVE_TYPE_NEXT = 2,
} ITFMENU_MOVE_TYPE;

typedef enum {
    ITFMENU_CTRL_TYPE_NONE = 0,
    ITFMENU_CTRL_TYPE_WAIT = 1,
    ITFMENU_CTRL_TYPE_NEXT = 2,
    ITFMENU_CTRL_TYPE_PREV = 3,
    ITFMENU_CTRL_TYPE_DECIDE = 4,
    ITFMENU_CTRL_TYPE_CANCEL = 5,
    ITFMENU_CTRL_TYPE_N_DISP = 6,
} ITFMENU_CTRL_TYPE;

typedef enum {
    ITFMENU_WAIT_TYPE_NONE = 0,
    ITFMENU_WAIT_TYPE_SET = 1,
    ITFMENU_WAIT_TYPE_UPDATE = 2,
    ITFMENU_WAIT_TYPE_DECIDE = 3,
    ITFMENU_WAIT_TYPE_CANCEL = 4,
} ITFMENU_WAIT_TYPE;

typedef enum {
    ITFMENU_GF_DRAW = 1,
    ITFMENU_GF_EXIST_TITLE = 2,
    ITFMENU_GF_DRAW_TITLE_TXT = 4,
    ITFMENU_GF_FOCUS = 8,
    ITFMENU_GF_CANCEL_RELEASE = 16,
    ITFMENU_GF_CANCEL_N_FOCUS = 32,
    ITFMENU_GF_TRIG_CALL_FUNC = 64,
    ITFMENU_GF_CALL_END = 128,
    ITFMENU_GF_LOCK_CTRL = 256,
    ITFMENU_GF_LOCK_SELECT = 512,
    ITFMENU_GF_FIX_LIST_NUM = 1024,
    ITFMENU_GF_N_DISP = 2048,
    ITFMENU_GF___DISP = 4096,
    ITFMENU_GF_WAIT_DISP = 8192,
    ITFMENU_GF_DEF_NODISP = 16384,
    ITFMENU_GF_LOCK_CANCEL = 32768,
    ITFMENU_GF_AUTO_DECIDE = 65536,
} ITFMENU_GF;

typedef enum {
    ITF_MOVER_UPDATE_NULL = -1,
    ITF_MOVER_UPDATE_NONE = 0,
    ITF_MOVER_UPDATE_RUN = 1,
    ITF_MOVER_UPDATE_END = 2,
} ITF_MOVER_UPDATE;

typedef enum {
    MPH_STAT_INIT = 0,
    MPH_STAT_LOADING = 1,
    MPH_STAT_LOADED = 2,
    MPH_STAT_READY = 3,
    MPH_STAT_DRAWING = 4,
} MPH_STAT;

typedef enum {
    SL_ItemState_Null = 0,
    SL_ItemState_MoveAble = 1,
    SL_ItemState_MoveDisable = 2,
    SL_ItemState_SelectMoveAble = 3,
    SL_ItemState_SelectMoveDisable = 4,
} SL_ItemState;

typedef struct FontReq_t FontReq_t;
typedef struct LIPSYNC_PARAM LIPSYNC_PARAM;
typedef struct LOGDISP_PARAM LOGDISP_PARAM;
typedef struct MenuCB_tag MenuCB_tag;
typedef struct MenuCsrUnity MenuCsrUnity;
typedef struct MenuCsrUnity MenuCsrUnitySp;
typedef struct MenuImgDat_t MenuImgDat_t;
typedef struct MenuMover_t MenuMover_t;
typedef struct MenuSelectData MenuSelectData;
typedef struct Menu_t Menu_t;
typedef struct Text_t Text_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileHandle_t fileHandle_t;
typedef struct itfMover_t itfMover_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct itfpanel_t itfpanel_t;
typedef struct mphDataHead_t mphDataHead_t;
typedef struct mphPoint_t mphPoint_t;
typedef struct mphStream_t mphStream_t;
typedef struct mphWork_t mphWork_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sprHandle_t sprHandle_t;

typedef void (*itfMenuCtrlUnity)(f32 alpha);
typedef void (*CsrUnityMoveFunc)(void);
typedef s32 (*itfMoverFunc_t)(s32 mode);
typedef void (*itfMenuTextFunc_t)(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
typedef s32 (*itfMenuMoveFunc)(Menu_t *wk, s32 _key, bool _loop);

struct MenuImgDat_t {
    sprHandle_t *hSpr;
    itfSprList_t *pList;
    s16 sx;
    s16 sy;
    s16 sw;
    s16 sh;
    s16 fx;
    s16 fy;
    u32 color;
    u8 alpha;
    ITF_DM_STYLE strStyle;
    s8 strSpace;
    s8 dummy8;
    s16 strWidth;
    u16 flag;
};

struct MenuCB_tag {
    s32 id;
    s32 parentId;
    s8 hierarchy;
    u8 alphaRate;
    s16 no;
    u32 gflag;
    u32 lflag;
    s32 decideSE;
    s32 cancelSE;
    char *str;
    char *tag;
    MenuCB_tag *pParent;
    MenuCB_tag *pPrev;
    MenuCB_tag *pNext;
    itfMenuFunc_t func;
    itfMenuDrawFunc_t funcDraw;
    itfMenuTextFunc_t funcText;
    s32 attrUnity;
};

struct MenuMover_t {
    itfMover_t *mover;
    MenuCB_tag *cb;
    s32 x;
    s32 y;
    s32 count;
};

struct MenuSelectData {
    s32 selNo;
    s32 topNo;
    s32 drwNo;
};

struct Menu_t {
    dds3ProcessID_t *drawPID;
    MenuImgDat_t *imgDat[4];
    MenuCB_tag *pHead;
    MenuCB_tag *pTail;
    MenuCB_tag *select;
    MenuCB_tag *title;
    itfMoverFunc_t MoverFunc;
    MenuMover_t *mv_title;
    MenuMover_t *mv[16];
    MENU_STEP step;
    s8 nowHierarchy;
    s32 nMenuSet;
    ITFMENU_CTRL_TYPE ctrlType;
    s8 dispType[2];
    s8 updateType;
    ITFMENU_SCROLL_TYPE scrollType;
    DDS3_OT ot;
    s32 selMax;
    s32 drwMax;
    s32 drwDefNum;
    s32 drwDefMax;
    s32 selNo[4];
    s32 topNo[4];
    s32 drwNo[4];
    s32 delId;
    void *delIdList;
    s32 initSelectID;
    ITFMENU_MOVE_TYPE moveType;
    s8 retFunc;
    bool bEnableCtrl;
    s8 dummy[1];
    u32 gflag;
    u32 lflag;
    s32 frame;
    s32 count;
    u32 abgr;
    bool scrollDrawUnity;
    u8 scrollAlphaUnity;
    itfMenuCtrlUnity unityCtrl;
    itfMenuMoveFunc moveFunc;
    bool titleParent;
    void *colliderCtrl;
};

struct MenuCsrUnity {
    s32 csrNo;
    s32 listTop;
    s32 listDrwNo;
    s32 nowMax;
    s32 listMax;
    CsrUnityMoveFunc moveFunc;
};

struct LIPSYNC_PARAM {
    s32 start;
    s32 tlen;
    s32 unit_uniqid;
    s32 motion_no;
    s32 spd;
    s32 lipend_time;
    char *msglbl;
    char *voice_name;
    s32 autoTime;
    char *tagid;
    s32 script_auto_skip;
    s32 script_auto_time;
    s32 script_guide_disp;
};

struct LOGDISP_PARAM {
    s32 start;
    s32 curidx;
    s32 pmvrun;
    bool msgwin;
    s32 logidx;
    s32 logtop;
    s32 logcurtop;
    s32 curtop;
    s32 curmax;
    char *textsave;
    bool initflag;
    bool act[4];
    s32 logadj;
    s32 logsave;
    s32 selcnt[1];
    s32 selcntsave[1];
    s32 selidx[1];
    s32 selidxsave[1];
    bool selflag;
    char *seltext;
    char *seltextsave;
    char *mestextsave[3];
    void *tagsave;
    void *selsave;
    void *msgList;
    bool logPlay;
    bool moonFlag;
    sdfColor32_t FONTCOLOR_WHITE;
    sdfColor32_t FONTCOLOR_GRAY;
    void *onEvent;
    void *offEvent;
};

struct mphStream_t {
    s32 texIndex;
    u8 alpha;
};

struct mphDataHead_t {
    u32 cycle_num;
    u32 tex_num;
    u32 point_num;
    u32 cnt;
    u32 coord_max;
    u32 point_addr;
    u32 order_addr;
    s32 resv;
};

struct mphPoint_t {
    sdfIVector2_t point;
    sdfIVector2_t uv;
};

struct mphWork_t {
    fileHandle_t *fileHandle;
    mphDataHead_t *pDataHeader;
    mphPoint_t *pointArray;
    u16 *pointOrderArray;
    s32 drawPointNum;
    s32 curCnt;
    s32 cycleCnt;
    s32 pointNum;
    s32 shiftNum;
    s32 cycleNum;
    s32 texNum;
    s32 texOrder[8];
    s32 texWidth;
    s32 texHeight;
    s32 pointDataSize;
    s16 pointAddr;
    s32 orderAddr;
    s32 width;
    s32 height;
    s32 offX;
    s32 offY;
    u8 alpha;
    DDS3_OT ot;
    s32 z;
    bool fMask;
    s32 leftRight;
    s32 maskX0;
    s32 maskY0;
    s32 maskX1;
    s32 maskY1;
    s32 maskX2;
    s32 maskY2;
    MPH_STAT fileStat;
    mphStream_t *stream0;
    mphStream_t *stream1;
    char *buffer;
};

extern u8 frImageDumpFlag;
extern u32 gMessageRequestResult;
extern f32 SCROLLBAR_LENGTH_MAX;
extern f32 SCROLL_LENGTH_MAX;
extern LIPSYNC_PARAM *lipsync_pm;
extern s32 SelectYesSe;
extern void *txtMgr;
extern void *GetureiUI;
extern void *passwordUI;
extern bool fadeFrontDisp;
extern void *fldUI;
extern void *map_win;
extern void *map_progress;
extern void *map_sts;
extern void *menu_win;
extern void *help_win;
extern void *devil_win;
extern void *devil_info2;
extern void *ikai_watari;
extern void *ikai_titlei;
extern void *elv;
extern void *elv_title;
extern void *ryuketsu;
extern void *map_staging;
extern bool Story11Extra;
extern bool Story11Select;
extern bool Story11Cancel;
extern s32 Story11Number;
extern bool QuestDevilExtra;
extern bool QuestDevilSelect;
extern bool QuestDevilCancel;
extern bool QuestMenuClose;
extern s32 QuestDevilNumber;
extern bool MenuListScroll;
extern s32 MenuOldCsr;
extern mphWork_t *mphWork;
extern char *filenames;
extern LOGDISP_PARAM *logdispwk;
extern char *g_replace_text;
extern sprHandle_t *generalMenu_g_hSpr;
extern bool isActionWndDisp;
extern s32 battle_key_wait;
extern u32 gFontDrawOT;

bool awdMenuCheckWait(void);
bool awdMenuStart(void);
s32 awdMenuGetSelectID(void);
void awdMenuProcessStart(void);
void awdMenuProcessEnd(void);
bool awdMenuProcessCheck(void);
dds3ProcessID_t *itfGetElvPID(void);
s32 itfGetElvTopNum(void);
bool elvMenuCheckWait(void);
bool elvMenuStart(s32 a_initID);
s32 elvMenuGetSelectID(void);
void elvMenuProcessStart(void);
void elvMenuProcessEnd(void);
bool elvMenuProcessCheck(void);
s32 frDrawEffect(FontReq_t *pFRQ, Text_t *pText, u8 AlphaDelay, u8 DrawSpeed);
char *itfNumConv(char *s);
char *itfTextTagReplace(char *_text, bool useV);
char *itfGetPlatformString(s32 num);
FontReq_t *itfCreateVarFRQ(char *message);
void frInitFontTable(s32 GsFontNums, s32 TextNums);
void frDestroyFontTable(dds3ProcessID_t *id);
FontReq_t *frDestroyFontRequest(FontReq_t *pFRQ);
FontReq_t *frDestroyFontRequestNow(FontReq_t *pFRQ);
FontReq_t *frDestroyFontRequestAfter(FontReq_t *pFRQ);
FontReq_t *frLinkFontString(char *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ);
FontReq_t *frLinkFontString_2(u8 *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ);
FontReq_t *frSetFontString(char *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ);
FontReq_t *frSetFontString_2(u8 *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ);
void frSetDrawSpeed(FontReq_t *pFRQ, u8 Speed);
void frSetFontSpace(FontReq_t *pFRQ, s32 Space);
void frSetDrawPosition(FontReq_t *pFRQ, s32 X, s32 Y);
void frSetFontColorNo(FontReq_t *pFRQ, u8 ColorNo);
void frSetFontColor(FontReq_t *pFRQ, u32 Color);
void frSetFontColorAlf(FontReq_t *pFRQ, u32 Color);
u8 frEnableMode(s8 Flag);
u8 frDisableMode(s8 Flag);
void frSetFontDrawOT(u32 OtType);
s32 frDrawFont(FontReq_t *pFRQ);
s32 frDrawFontEx(FontReq_t *pFRQ, s8 Mode);
s32 frDrawFontEx2(FontReq_t *pFRQ, s8 Mode, u32 Ot);
dds3ProcessFunc_t frFlipPacketBuf(dds3ProcessID_t *id);
FontReq_t *frCombineFontRequest(FontReq_t *pFRQ1, FontReq_t *pFRQ2);
FontReq_t *frCombineFontRequestEx(FontReq_t *pFRQ1, FontReq_t *pFRQ2, u32 Mode);
s32 frGetStrWidth(FontReq_t *pFRQ);
s32 frPreCalcStrWidth(char *pStr, FR_STYLE Style, s8 Mode);
u8 *MessageNumSearch(s32 Index, u8 *pData, s32 Size);
FontReq_t *itfMessageRequestExLocalize(s32 x, s32 y, u8 Style, u8 ColNo, u8 Tp, u8 Spd, u8 *pMsg, FontReq_t *pFRQ, bool spc, bool hitokoto, bool logmes);
FontReq_t *MessageRequestNS(s32 X, s32 Y, u32 Z, u8 Style, u8 ColNo, u8 Tp, u8 Spd, u8 *pMsg, FontReq_t *pFRQ);
u32 frGetMessageResult(u32 Flag);
void frSetVariableRequest(s32 VarNo, char *pStr);
char *frGetVariableRequest(s32 VarNo);
void *itfGetLabelToString(char *label, bool is_spk, u8 ColNo);
char *itfRepColTag(char *txt, u32 col);
s32 frGetMessageLineNums(FontReq_t *pFRQ);
void frSetMessageCenter(s32 X, s32 Y, FontReq_t *pFRQ);
s32 frGetLipsTarget(void);
s32 frGetLipsType(void);
void itfFontColorTextUnity2(char *_str, u32 _col, void *_tmPro, bool _num, s32 _ex, char *_tag);
char *itfConvertToDelimitedNum(char *_num);
sdfColor32_t itfGetFontColorUnity2(u32 _color, bool _num, s32 _ex);
char *itfTextSetSprite(s32 type);
char *itfTextBtnConvert(char *text, char *label);
void *itfTextBtnConvertBuild(void *str);
char *itfTextItmConvert(char *text);
void *itfTextItmConvertBuild(void *str);
char *itfTextSklConvert(char *text);
void *itfTextSklConvertBuild(void *str);
char *itfTextDepConvert(char *text);
void *itfTextDepConvertBuild(void *str);
char *itfTextMneConvert(char *text);
void *itfTextMneConvertBuild(void *str);
char *itfTextRaiConvert(char *text);
void *itfTextRaiConvertBuild(void *str);
char *itfSystemTextBtnConvert(char *text, char *label);
s32 itfGetReturnNum00(void);
s32 itfGetReturnNum01(void);
bool itfCountSetData(dds3ProcessID_t *PID, s32 a_pDat, ITF_COUNT_TYPE a_type);
bool itfCountSetMax(dds3ProcessID_t *PID, s32 a_pDat, s32 a_max);
bool itfCountSetMin(dds3ProcessID_t *PID, s32 a_pDat, s32 a_min);
dds3ProcessID_t *itfCountProcessStart(s32 a_num, s32 a_frame, s32 a_blank, s32 a_seNo);
dds3ProcessID_t *itfCountProcessStartMoney(s32 a_num);
void itfCountProcessEnd(dds3ProcessID_t *PID);
bool itfCountProcessCheck(dds3ProcessID_t *PID);
bool itfDvlMsgCreateData(s32 a_devilID);
bool itfDvlMsgDeleteData(s32 a_devilID);
void itfDvlMsgStart(s32 a_devilID, s32 a_msgID);
void itfDvlMsgEnd(void);
void itfDvlMsgProcessStart(void);
void itfDvlMsgProcessEnd(void);
bool itfDvlMsgProcessCheck(void);
void itfDrawMiscSprite(s32 a_x, s32 a_y, s32 a_z, sprHandle_t *a_hSpr, s32 a_sprNo, DDS3_OT a_otNo);
void itfDrawMiscSpriteAlpha(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, s32 a_sprNo, DDS3_OT a_otNo);
void itfDrawMiscSpriteListSelect(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, DDS3_OT a_otNo, itfSprList_t *a_list, s32 a_no);
void itfDrawMiscSpriteListEx(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, DDS3_OT a_otNo, u32 a_flag, itfSprList_t *a_list);
void itfDrawMiscSpriteList(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, DDS3_OT a_otNo, itfSprList_t *a_list);
void itfDrawFont(ITF_DM_STYLE a_style, s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_space, u32 a_color, f32 a_alphaRate, DDS3_OT a_ot, char *a_str);
void itfDrawMiscFont(ITF_DM_STYLE a_style, s32 a_x, s32 a_y, s32 a_z, s32 a_space, u32 a_color, u8 a_alpha, char *a_str);
void itfDrawMiscFontAlpha(s32 a_x, s32 a_y, s32 a_z, u32 a_color, u8 a_alpha, char *a_str);
void itfDrawMiscHelp(u32 a_color, f32 a_alphaRate, FRW_HELP HelpType, u16 HelpID, s32 _spirit);
void itfDrawMiscGauge(s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_h, s32 a_num, s32 a_max, u32 a_color, u8 a_alpha);
void itfDrawMiscGauge2(s32 a_mode, s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_h, s32 a_num, s32 a_max, u32 a_color, u8 a_alpha);
void itfDrawLineBezierPt3(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 vx, f32 vy, u32 rgba0, u32 rgba1, u32 ot);
void itfDrawFanBezierPt3(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 vx, f32 vy, u32 rgba0, u32 rgba1, u32 rgba2, u32 ot);
s32 itfFloatTo32s(f32 a_num, s32 a_shift);
s32 itfGetFigure(s32 a_num);
s32 itfGetFigureNum(s32 a_num, s32 a_figure);
u32 itfSwapRGBA(u32 a_rgba);
void itfCalcSpriteWidth(sprHandle_t *a_hSpr, s32 a_sprNo, s32 a_num, s32 a_max);
void itfGetRatePosBezierPt3(f32 *px, f32 *py, f32 x0, f32 y0, f32 x1, f32 y1, f32 vx, f32 vy, f32 rate);
void itfGetVectorPosBezierPt3(f32 px, f32 py, f32 x0, f32 y0, f32 x1, f32 y1, f32 rx, f32 ry, f32 rate);
u32 itfGetDivBezierPt3(f32 x0, f32 y0, f32 x1, f32 y1, f32 vx, f32 vy, f32 divLength);
sprHandle_t *itfGeneralMenuGetSpriteHandle(void);
void itfGeneralMenuLoadSpriteMem(void);
void itfGeneralMenuFreeSpriteMem(void);
void itfGeneralMenuLoadSpriteHnd(void);
void itfGeneralMenuFreeSpriteHnd(void);
s32 itfGeneralMenuDecideFunc(dds3ProcessID_t *PID);
void itfGeneralMenuReturnFunc(dds3ProcessID_t *PID);
dds3ProcessID_t *itfGeneralMenuCreatePID(s32 a_x, s32 a_y);
bool itfIconFreeSprMem(void);
bool itfIconLoadSprMem(void);
bool itfIconFreeSprHnd(void);
bool itfIconLoadSprHnd(void);
void itfIconDrawSprite(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, s32 a_sprNo, DDS3_OT a_otNo);
void itfIconDrawBadStatus(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, u32 a_bstNo, DDS3_OT a_otNo);
void itfIconDrawBullet(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, s32 a_itemID, DDS3_OT a_otNo);
void itfIconInit(void);
void itfIconFree(void);
void itfListSetListInit(dds3ProcessID_t *PID, ITF_LIST a_listNo, ITF_LIST_TYPE a_type, char *a_str, s32 a_num);
void itfListSetListFont(dds3ProcessID_t *PID, ITF_LIST a_listNo, char *a_str, s32 a_num);
void itfListSetPos(dds3ProcessID_t *PID, s32 a_x, s32 a_y);
void itfListDelList(dds3ProcessID_t *PID, ITF_LIST a_listNo);
void itfListSetTypeApper(dds3ProcessID_t *PID, s32 a_type);
void itfListSetTypeDisapper(dds3ProcessID_t *PID, s32 a_type);
void itfListSetFlagTarget(dds3ProcessID_t *PID, bool a_bTarget);
void itfListSetFlagSelect(dds3ProcessID_t *PID, bool a_bSelect);
void itfListSetSelectNo(dds3ProcessID_t *PID, s32 a_listNo);
void itfListStart(dds3ProcessID_t *PID);
void itfListEnd(dds3ProcessID_t *PID);
void itfListSetScrollParam(dds3ProcessID_t *PID, s32 a_listTopNo, s32 a_listNum);
void itfListDrawScrollBar(s32 a_x, s32 a_y, s32 a_topno, s32 a_selmax, f32 a_alphaRate);
dds3ProcessID_t *itfListProcessStart(void);
void itfListProcessEnd(dds3ProcessID_t *PID);
bool itfListProcessCheck(dds3ProcessID_t *PID);
void itfMenuLinkPrintf(dds3ProcessID_t *PID);
bool itfMenuClearMenu(dds3ProcessID_t *PID, s32 a_id);
void itfMenuClearMenuAll(dds3ProcessID_t *PID);
void itfMenuSetMenuTitle(dds3ProcessID_t *PID, char *a_str, char *a_tag);
bool itfMenuSetMenu(dds3ProcessID_t *PID, s32 a_id, s32 a_parentId, char *a_str, itfMenuFunc_t a_func, char *a_tag);
bool itfMenuSetRootMenu(dds3ProcessID_t *PID, s32 a_id, char *a_str, itfMenuFunc_t a_func, char *a_tag);
void itfMenuSetMoveAppear(dds3ProcessID_t *PID, s32 a_type);
void itfMenuSetMoveDisappear(dds3ProcessID_t *PID, s32 a_type);
void itfMenuSetFlag(dds3ProcessID_t *PID, ITFMENU_GF a_bit, bool a_bSet);
bool itfMenuSetFlagMenu(dds3ProcessID_t *PID, s32 a_id, ITFMENU_CB_GF a_bit, bool a_bSet);
bool itfMenuGetFlag(dds3ProcessID_t *PID, u32 a_bit);
bool itfMenuGetFlagMenu(dds3ProcessID_t *PID, s32 a_id, u16 a_bit);
s32 *itfMenuGetIdList(dds3ProcessID_t *PID);
bool itfMenuChkExistMenu(dds3ProcessID_t *PID, s32 a_id);
ITFMENU_WAIT_TYPE itfMenuGetWaitType(dds3ProcessID_t *PID);
ITFMENU_WAIT_TYPE itfMenuGetWaitType2(dds3ProcessID_t *PID);
void itfMenuUpdateLink(dds3ProcessID_t *PID);
void itfMenuStart(dds3ProcessID_t *PID);
s32 itfMenuGetSelectID(dds3ProcessID_t *PID);
s32 itfMenuGetHierarchy(dds3ProcessID_t *PID);
s32 itfMenuGetMenuNo(dds3ProcessID_t *PID, s32 a_id);
bool itfMenuChkMenuTop(dds3ProcessID_t *PID, s32 a_id);
bool itfMenuChkHead(dds3ProcessID_t *PID, s32 a_id);
void itfMenuSetSelectHead(dds3ProcessID_t *PID);
MenuSelectData *itfMenuCreateSelectData(dds3ProcessID_t *PID);
bool itfMenuSetSelectData(dds3ProcessID_t *PID, MenuSelectData *menuData);
void itfMenuSetSelectID(dds3ProcessID_t *PID, s32 a_id);
void itfMenuSetInitSelectID(dds3ProcessID_t *PID, s32 a_id);
void itfMenuResetSelect(dds3ProcessID_t *PID);
s32 itfMenuGetMenuNum(dds3ProcessID_t *PID);
bool itfMenuChkSetMenu(dds3ProcessID_t *PID);
bool itfMenuImgLinkSprite(dds3ProcessID_t *PID, s32 a_type, sprHandle_t *a_hSpr);
bool itfMenuLinkSprite(dds3ProcessID_t *PID, sprHandle_t *a_hSpr);
bool itfMenuSetSpriteData(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, s32 a_baseX, s32 a_baseY, s32 a_ofsX, s32 a_ofsY, s32 a_fontX, s32 a_fontY, u8 *a_strSprName, itfSprList_t *a_pList);
bool itfMenuSetImageColor(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, u8 a_R, u8 a_G, u8 a_B, u8 a_A);
u8 itfMenuImgGetAlpha(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type);
f32 itfMenuImgGetRatio(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type);
void itfMenuSetSubABGR(dds3ProcessID_t *PID, u32 a_abgr);
bool itfMenuSetStringStyle(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, ITF_DM_STYLE a_style);
bool itfMenuSetStringSpace(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, s32 a_space);
bool itfMenuSetStringWidth(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, s32 a_width);
bool itfMenuGetPanelParam(dds3ProcessID_t *PID, s32 a_id, s32 *a_px, s32 *a_py, s32 *a_pw, s32 *a_ph);
bool itfMenuSetFunc(dds3ProcessID_t *PID, s32 a_id, itfMenuFunc_t a_func);
bool itfMenuSetDrawFunc(dds3ProcessID_t *PID, s32 a_id, itfMenuDrawFunc_t a_funcDraw, itfMenuTextFunc_t a_funcText);
bool itfMenuSetFont(dds3ProcessID_t *PID, s32 a_id, char *a_str, char *a_tag);
void itfMenuSetDrawParam(dds3ProcessID_t *PID, s32 a_max, bool a_bFix);
bool itfMenuDelMenu(dds3ProcessID_t *PID, s32 a_id);
bool itfMenuDelMenus(dds3ProcessID_t *PID, void *delID);
void itfMenuSetMoveType(dds3ProcessID_t *PID, ITFMENU_MOVE_TYPE a_type);
ITFMENU_CTRL_TYPE itfMenuGetCtrlType(dds3ProcessID_t *PID);
void itfMenuSetOt(dds3ProcessID_t *PID, DDS3_OT a_ot);
bool itfMenuSetDecideSE(dds3ProcessID_t *PID, s32 a_id, s32 a_se);
bool itfMenuSetCancelSE(dds3ProcessID_t *PID, s32 a_id, s32 a_se);
void itfMenuSetAnimDelMenu(dds3ProcessID_t *PID, s32 a_id, s32 a_cnt);
void itfMenuSetAnimBakMenu(dds3ProcessID_t *PID, s32 a_id, s32 a_cnt);
void itfMenuSetAnimFlashMenu(dds3ProcessID_t *PID, s32 a_id);
s32 itfMenuGetFlashCount(dds3ProcessID_t *PID, s32 a_id);
s32 itfMenuGetDecideKey(void);
void itfMenuSetDecideKey(s32 DecideKey);
void itfMenuCallEnd(dds3ProcessID_t *PID);
dds3ProcessID_t *itfMenuProcessStart(void);
void itfMenuProcessEnd(dds3ProcessID_t *PID);
bool itfMenuProcessCheck(dds3ProcessID_t *PID);
void itfMenuFrcCancel(dds3ProcessID_t *PID);
void itfMenuSetCtrlFuncForUnity(dds3ProcessID_t *PID, itfMenuCtrlUnity a_func);
void itfMenuSetMoveFunc(dds3ProcessID_t *PID, itfMenuMoveFunc func);
void itfMoverSetMenu(dds3ProcessID_t *PID, itfMoverFunc_t a_func);
u32 itfGetTextColor(MenuMover_t *_mv, u32 _gflag);
bool itfGetCur(MenuMover_t *_mv);
void itfResetCursorDraw(void);
bool itfIsMesKey(SDF_PADMAP key, itf_PADREAD read);
void itfBattleEvtKeyWaitInit(void);
void itfBattleEvtKeyWaitProc(void);
void itfBattleEvtKeyWaitSet(s32 time);
void itfLipSyncStart(s32 unit_uniqid, s32 motion_no);
bool itfIsLipSyncStart(void);
void itfLipSyncParam(s32 motion_no);
void *itfGetCriLipSyncManager(s32 unit_uniqid);
void itfCriLipSyncManagerOff(dds3ModelHandle_t *mh);
void *itfGetCriLipSyncSource(s32 unit_uniqid);
void itfLipSyncSetVoice(char *voice_name);
void itfLipSyncSetTagID(char *tagid);
char *itfLipSyncGetVoice(void);
char *itfLipSyncGetTagID(void);
void itfLipSyncCalc(void);
void itfSetLipSyncTime(s32 time);
bool itfLipSyncEndCheck(void);
void itfLipSyncEnd(void);
void itfSetPmvRun(s32 flg);
bool itfIsPmvRun(void);
void itfPmvButtonGuideCtrl(s32 flg);
bool itfIsPmvSkipAndPause(void);
void itfPartVoiceLoad(void);
char *itfGetPartVoice(char *label_name);
s32 itfGetPartVoiceFlag(char *label_name);
void itfPartVoiceDevilSet(s32 devilid);
s32 itfPartVoiceDevilGet(void);
void itfResetMsgGuideName(void);
void itfSetGuide(char *guide_name, bool disp);
void itfSetGuidePMV(char *guide_name, bool disp);
void itfSetGuideSkip(char *guide_name, bool disp);
bool itfIsDrawSelWnd(void);
void itfSetGuideAnimPMV(bool disp);
char *itfGetGudeName(void);
void itfSetMesGuideLineAnimPMV(bool _bo);
void itfMesGuideLineCtrl(bool _bo);
char *itfGetLableGuideBtn(char *label_name);
bool itfIsSpeakerText(FontReq_t *pFRQ);
bool itfIsCloseWindow(s32 id);
s32 itfGetPrefMesWin(void);
void itfSetPrefMesNom(void);
void itfSetPrefMesCmn(void);
s32 mesLine(void);
void itfWindowDispOn(s32 MsgID);
void itfMessageClrAll(void);
s32 itfDebugWindowSwitch(s32 itfon);
s32 itfMesMngMessage(void);
s32 itfMesMngMessageSub(s32 mes);
void itfMesMngSetOffsetY1(s32 msgid, s32 y1);
s32 itfMesMngGetPhase(s32 msgid);
void itfMesMngSetPhase(s32 msgid, s32 phase);
s32 itfMesMngSelect(void);
s32 MesMngSelect(s16 cancelNum, bool longSel);
s32 itfMesMngGetSelPhase(s32 msgid);
void itfMesMngSetSelPhase(s32 msgid, s32 phase);
s32 itfMesMngGetSelectNo(s32 msgid);
s32 itfMesMngMaskSelect(void);
s32 itfMesMng_SEL_SELNO(void);
s32 itfMesMngOpenWindow(void);
s32 itfMesMngCloseWindow(void);
void itfMesMngMsgWndCls(s32 msgid);
s32 itfMesMngOpenSelectWindow(void);
s32 itfMesMngCloseSelectWindow(void);
s32 itfMesMngSetVarScr(void);
s32 itfMesMngIgnoreConfig(void);
s32 itfMesMngSetMesPositionScript(void);
s32 itfMesMngSetMesPosDefault(void);
s32 itfMesMngValidateNext(void);
s32 itfMesMngWindowType(void);
s32 itfMesMngWindowTypeAlpha(void);
s32 itfMesMngSelectDefKey(void);
s32 itfSetMesDispPriority(void);
s32 itfMesMngInitialize(void *presource, char *master_text, char *key);
void itfMesMngRelease(s32 id);
f32 itfGetMesWinAlpha(void);
void itfMesWinAlphaClear(void);
s32 itfMesMngRequestMessage(s32 id, s32 message, s32 page, s32 callmode, bool hojo);
void itfMesMngRequestMessageRelease(s32 id, s32 cls_speaker);
void itfMesMngRequestSelect(s32 id, s32 select);
void itfMesMngRequestSelectRelease(s32 id);
void itfMesMngSetMaskSelect(s32 id, u32 maskpattern);
void itfMesMngSetSelect(s32 id, s32 selno, s16 cancelNum);
void itfMesPos(s32 x, s32 y);
void itfMesPosDefault(void);
void itfMesMngSetMesPosition(s32 id, s32 x, s32 y);
void itfMesMngSetPriority(s32 id, u32 z_buf);
u32 itfMesMngGetStat(s32 id);
void itfMesMngSetStat(s32 id, u32 flag);
void itfMesMngMarkBitStat(s32 id, u32 flag);
void itfMesMngClearBitStat(s32 id, u32 flag);
s32 itfMesMngGetSelect(s32 id);
s32 itfMesMngGetMesPage(s32 id);
s32 itfMesMngGetMesCurrentPage(s32 id);
char *itfMesMngGetVar(s32 id, s32 index);
void itfMesMngSetVar(s32 id, s32 index, s32 num, s32 type);
void itfSetTextValue(s32 index, ITF_MESMNG_VAR type, s32 value, bool setIcon);
void itfSetTextDataValue(s32 index, char *value);
char *itfGetText(char *label);
void itfMesMngSetVarImmediate(s32 id, s32 index, char *pstr);
void itfMesMngSetVarImmediate2(s32 id, s32 index, char *pstr, s32 length);
void *itfMesMngSetResourcePtr(s32 id, void *presource);
u8 *itfMesMngGetDataPtrImmediate(s32 id, s32 message, s32 page);
char *itfMesMngGetStrImmediate(s32 id, s32 message, s32 page);
FontReq_t *itfMesMngGetFRQ(s32 id, s32 message);
void itfMesMngChangeWindowType(s32 id, s32 type, s32 alpha);
s32 itfMesMngSetSelectDefKey(s32 id, s32 key, s32 index);
void itfMesMngSetDefaultSpeed(s32 id, s32 speed);
void itfSetPageUpdateCallBack(s32 id, void *_func);
void itfMesMngObjectInitialize(void);
void itfMesMngPadModeOn(u32 Mode);
void itfMesMngPadModeOff(u32 Mode);
void itfMesMngInitializeManager(void);
void itfMesMngSetBitStatManager(s32 flags);
void itfMesMngClearBitStatManager(s32 flags);
s32 itfMesMngGetStatManager(void);
dds3ProcessFunc_t itfMesMngDebugProc(dds3ProcessID_t *proc_id);
void itfMesMngDebugShutdown(dds3ProcessID_t *proc_id);
FontReq_t *GetLastLinkFontHandle(FontReq_t *pfont);
bool itfIsSpeaking(void);
bool itfIsSpeakStart(void);
void itfMsgWndSetActive(s32 i, bool sw);
void itfSetMsgWndTmpText(s32 i, char *str);
char *itfGetMsgWndTmpText(s32 i);
void itfSetMsgWndTmpTextReplace(char *str);
void itfMsgWndCurSetActive(s32 i, bool sw);
void itfMsgWndImgSetActive(s32 i, bool sw);
void itfSetRaidouObjectAndCamera(void *obj, void *cam);
void itfSetRaidoObject(void *obj, f32 add);
void itfSetCamera(void *cam);
void itfActWndSetActive(bool sw, bool isCalc);
void itfDrawActWnd(void);
sdfVector3_t itfGetMsgWndLocalPos(void);
void DrawActWnd(const sdfVector3_t *pos);
void itfSetActWndText(char *str, s32 line);
void itfSetActWndTextCoror(char *str, s32 line, u32 color);
void itfSetIsActionWndDisp(bool flg);
bool itfGetIsActionWndDisp(void);
void itfPreDrawActionWndDisp(bool flg);
void itfSetActionWndLines(s32 line);
sdfVector3_t itfGetActionWindowPosition(void);
void itfClearMsgWndText(void);
void itfSetAnimeMsgWin(bool flag);
s32 itfGetAnimeMsgWin(void);
bool itfGetAnimEndMsgWin(void);
bool itfIsFadeOutAnimeMsgWin(void);
void itfSetIsmesWndBaseDisp(bool flg);
void itfSetMsgWndDefault(void);
void itfSetMsgWndCnvGrpAlpha(s32 i, f32 alpha);
f32 itfGetMsgWndCnvGrpAlpha(s32 i);
void itfSetMenuCursorIndex(s32 index);
s32 itfGetMenuCursorIndex(void);
bool itfIsExistMessageWindow(void);
s32 itfMesMngChkWaitTag(s32 msgid);
void itfMesMngClearCursor(s32 id);
ITF_MESBINTYPE itfGetMessageType(s32 id, s32 message);
s32 itfGetMessageNo(s32 id);
s32 itfInputPasswd(void);
s32 itfMsgAutoSetUp(void);
void itfMoneyProcessStart(void);
void itfMoneyProcessEnd(void);
bool itfMoneyProcessCheck(void);
bool itfMoneyCheckWait(void);
bool itfMoneySetDrawOn(void);
bool itfMoneySetDrawOff(void);
bool itfMoneySetAddMoney(s32 a_money);
void itfInitMoneyManager(void *s_work);
void itfSetMoneyText(void);
void itfSetMoneyActive(bool sw);
void itfCtrlMoney(f32 alpha, char *money);
void SetMoneyText(char *money);
void itfSetMoneyAlpha(f32 alpha);
bool itfMoverInit(itfMover_t *mv);
bool itfMoverSetData(itfMover_t *mv, s32 a_posx, s32 a_posy, s32 a_tgtx, s32 a_tgty, f32 a_rate, s32 a_waitBefore, s32 a_waitAfter, s32 a_frame);
bool itfMoverSetParam(itfMover_t *mv, s32 a_posx, s32 a_posy, s32 a_tgtx, s32 a_tgty, s32 a_frame);
ITF_MOVER_UPDATE itfMoverUpdate(itfMover_t *mv);
bool itfMoverGetPosition(itfMover_t *mv, f32 *a_pPosX, f32 *a_pPosY);
bool itfMoverChkEnd(itfMover_t *mv);
f32 itfMoverGetRatio(itfMover_t *mv);
itfpanel_t *itfPnlRegist2(s32 type);
void itfPnlRelease(itfpanel_t *handle);
void itfPnlSetPosition(itfpanel_t *handle, s32 x0, s32 y0, s32 x1, s32 y1, u32 z);
void itfPnlSetPositionOffset(itfpanel_t *handle, s32 x0, s32 y0, s32 x1, s32 y1, u32 z);
void itfPnlSetColor(itfpanel_t *handle, s32 r, s32 g, s32 b, s32 a);
void itfPnlDraw(itfpanel_t *handle, sdfGrOt_t *pot);
void itfPnlDrawTag(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
void *itfStationListGetBaseObject(void);
void itfInitStationListManager(void *s_work);
void itfSetStationListText(void);
void itfSetStationListActive(bool sw);
void itfCtrlStationList(f32 alpha);
void itfSetStationListItemState(s32 index, SL_ItemState state);
void itfSetStationListItemFare(s32 index, char *fare);
void itfSetAlpha(f32 alpha);
void itfChangeBitIconNew(s32 id);
void itfChangeIconNewAll(void);
void itfChangeMokutekichi(s32 _id);
void itfSetStationListMenuBarFlag(s32 num, s32 flagID);
bool itfQuickSaveExeCheck(void);
bool mapMenuCheckWait(void);
bool mapMenuStart(void);
s32 mapMenuGetSelectID(void);
u32 mapMenuGetSelectUNIQ(void);
void mapMenuProcessStart(void);
void lmapMenuProcessStart(void);
void mapMenuProcessEnd(void);
bool mapMenuProcessCheck(void);
void mphInit(void);
void mphStartLoad(char **filename);
void mphStartLoadID(s32 id);
s32 mphLoadCheckEnd(void);
MPH_STAT mphCheckStat(void);
void mphEndDraw(void);
void mphEnd(void);
void mphStartDraw(s32 offX, s32 offY, s32 width, s32 height);
void mphStartDrawBtlRight(void);
void mphStartDrawBtlLeft(void);
void mphSetAlpha(u8 alpha);
u8 mphGetAlpha(void);
void mphSetZ(s32 z);
s32 mphGetZ(void);
void mphSetOt(DDS3_OT ot);
DDS3_OT mphGetOt(void);
s32 mphCommand_BUSTUP_LOAD(void);
s32 mphCommand_BUSTUP_LOAD_WAIT(void);
s32 mphCommand_BUSTUP_ON(void);
s32 mphCommand_BUSTUP_OFF(void);
s32 mphStart(void);
s32 mphShutDown(void);
void itfLogDispWorkNewGameInit(void);
void itfMsgLogStartUI(bool msgwin);
bool itfMsgLogPlayCheck(void);
void savePointMenuProcessStart(void);
bool savePointMenuStart(void);
bool savePointMenuCheckWait(void);
s32 savePointMenuGetSelectID(void);
bool savePointMenuProcessCheck(void);
void savePointMenuProcessEnd(void);
