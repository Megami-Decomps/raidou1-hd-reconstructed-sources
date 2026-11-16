#include "types.h"
#include "ITFMENU_CB_GF.h"
#include "atlfieldaccessor.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmp.h"
#include "cmpitem.h"
#include "cmpraidouskill.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3_pad2.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3kernelmain.h"
#include "dds3kernelmisc.h"
#include "evtbit.h"
#include "evtcommand.h"
#include "evtmoon.h"
#include "evtpicture.h"
#include "evtpmv.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "frdream.h"
#include "frfont.h"
#include "frname.h"
#include "gohdirection.h"
#include "interface.h"
#include "itf.h"
#include "itfMenuDrawFunc_t.h"
#include "itfMenuFunc_t.h"
#include "itfmisc.h"
#include "kernel.h"
#include "libsdf.h"
#include "lmap.h"
#include "localize.h"
#include "meslogmain.h"
#include "movie.h"
#include "mviscrcmd.h"
#include "raijindlc.h"
#include "sbattle.h"
#include "sbtlcalc.h"
#include "sbtlitem.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "scr.h"
#include "scrcommand.h"
#include "sdat.h"
#include "sdfdraw.h"
#include "sndmanager.h"
#include "streaming.h"
#include "titlemain.h"
#include "wordwrap.h"

#define DIC_START_CODE 32896
#define FR_FONT_WIDTH 24
#define FR_FONT_HEIGHT 24
#define FR_FONTIMG_SIZE 288
#define FR_MESSAGE_SPACE_X 2
#define FR_VAR_MAX 32
#define FR_PT_MAX 12
#define CCN_DIC_NAME 61953
#define CCN_COLOR 61954
#define CCN_VARIABLE 61955
#define CCN_WAIT 61700
#define CCN_SIZE 61957
#define CCN_FONT 61958
#define CCN_SPD 61959
#define CCN_EXT 61960
#define CCN_TP 61961
#define CCN_NAME 61962
#define CCN_NAME1N 61963
#define CCN_NAME2N 61964
#define CCN_CNAME 61965
#define CCN_DEVIL 61966
#define CCN_RET 61711
#define CCN_NWAIT 61712
#define CCN_AFDEL 61713
#define CCN_KUTI 61714
#define CCN_VPLAY 62483
#define CCN_MW 61972
#define CCN_VMW 61973
#define CCN_LIPS 62486
#define CCN_LIPS_STOP 61719
#define CCN_CHIME 61976
#define CCN_QUAKE_ON 62489
#define CCN_QUAKE_OFF 61722
#define CCN_LIPS_STOP2 61979
#define MR_WAIT_TAG 1
#define MR_NULLWAIT_TAG 2
#define MR_KUTI_TAG 4
#define MR_LIPS_TAG 8
#define DSCLX 3.75
#define DSCLY 2.25
#define MR_Y_STEP 25
#define FR_EFFECT_ALL 0
#define FR_EFFECT_NONE 1
#define FR_LINK_DEF 0
#define FR_LINK_POS 1
#define FR_FONTCOL_NML 2694693760
#define FR_FONTCOL_MSK 1296780109
#define FR_FONTCOL_SEL 1692838528
#define FR_FONTCOL_DEAD 1967865216
#define FR_FONTCOL_HALF 3030410368
#define FR_FONTCOL_MSK2 1349079155
#define FR_FONTCOL_NML_MSK 1296780152
#define FR_FONTCOL_SEL_MSK 1349406840
#define FR_FONTCOL_VALDOWN 1849704703
#define FR_FONTCOL_VALUP 1853947776
#define FR_FONTCOL_SKL 2155905152
#define FR_FONTCOL_SKL_MSK 1082146944
#define FR_FONTCOL_SELECTED 1
#define FR_FONTCOL_NO_COMB 2
#define FR_MODE_NONE 0
#define FR_MODE_PROP 1
#define FR_MODE_ASCII 2
#define FR_MODE_RET 4
#define FR_MODE_AFDEL 8
#define FR_MODE_YSHT 16
#define FR_MODE_AFDEL_RET 32
#define BTN_ICON_WIDTH 96
#define ITF_SYS_EITHER 0
#define ITF_SYS_MOVE_CONF 1
#define AWDMENU_MAINPROC_NAME "ikai_menu_proc"
#define AWDMENU_MAINDRAW_NAME "ikai_menu_draw"
#define ELVMENU_MAINPROC_NAME "kaisou_menu"
#define ALPHA_DELAY 28
#define TP1LEV 5
#define RGB_MSK 255
#define ALPHA_MSK 4294967040
#define DEFAULT_DELIMITED 3
#define ITF_COUNT_MAINPROC_NAME "itfcount"
#define ITFDVLMSG_MAINPROC_NAME "itfDvlMsgMainProc"
#define ITFDVLMSG_DRAWPROC_NAME "itfDvlMsgDrawProc"
#define ITFGENERALMENU_SPR_FILE "/itf/hanyo_menu.spr"
#define ITF_LIST_MAINPROC_NAME "itfListMainProc"
#define ITF_LIST_DRAWPROC_NAME "itfListDrawProc"
#define ITF_LIST_SPRMAIN_NAME "/shop/back_konnou.spr"
#define ITFMENU_MAINPROC_NAME "itfmenu_main"
#define ITFMENU_DRAWPROC_NAME "itfmenu_draw"
#define MAX_MESFLOW 64
#define PROCNAME_CALC "CalcMsgMng"
#define PROCNAME_DRAW "DrawMsgMng"
#define BASE_OFFSET_Y 0
#define FONT_OFFSET_Y 0
#define DEFAULT_Z 16777200
#define MESWIN0_RED 128
#define MESWIN0_GREEN 128
#define MESWIN0_BLUE 128
#define MESWIN0_ALPHA 128
#define MESWIN_FADEIN_SPEED 24
#define MESWIN_FADEOUT_SPEED 8
#define SPKWIN_FADE_SPEED 32
#define SPKWIN_RED 127
#define SPKWIN_GREEN 127
#define SPKWIN_BLUE 127
#define SPKWIN_ALPHA 200
#define CURCTR_INITALPHA 0
#define PAGEWAIT 0
#define LFWAIT 1
#define CUTINPWAIT 8
#define LFINPWAIT 6
#define LFAFTERWAIT 6
#define SELCURWAIT 0
#define SELINPWAIT 4
#define ITF_PASSWD_COL_MAX 8
#define REGMSG_MAXNO 64
#define DEFAULT_POS_SPK_X 4020
#define DEFAULT_POS_SPK_Y 5832
#define DEFAULT_POS_MES_X 4500
#define DEFAULT_POS_MES_Y 6318
#define DEFAULT_POS_SEL_X 5160
#define DEFAULT_POS_SEL_Y 7218
#define SEL_UPDOWN_SPEED 144
#define ITFMONEY_MAINPROC_NAME "itfmoney_main"
#define ITFMONEY_DRAWPROC_NAME "itfmoney_draw"
#define strMoney "Ë©¦"
#define NUM_VERTEX_NORMAL 8
#define NUM_COLOR_NORMAL 2
#define NUM_VERTEX_MESWIN 40
#define NUM_COLOR_MESWIN 8
#define NUM_VERTEX_SELWIN 32
#define NUM_COLOR_SELWIN 6
#define NUM_VERTEX_PLAIN 4
#define NUM_COLOR_PLAIN 4
#define NUM_VERTEX_PERA1 4
#define NUM_COLOR_PERA1 1
#define NUM_VERTEX_LEFTFADE 6
#define NUM_COLOR_LEFTFADE 2
#define NUM_VERTEX_FACILITY 8
#define NUM_COLOR_FACILITY 2
#define MAPMENU_MAINPROC_NAME "map_menu"
#define MAPMENU_SPR_FILE "/battle/panel/battle_waku.spr"
#define MPH_DEBUG 1
#define MPH_FILENAME "gyuuki.MOR"
#define MPH_DATA_DIR "/itf/morph/"
#define MPH_PROCESS_NAME "Morph Process"
#define MPH_FILE_PROCESS_NAME "Morph File Process"
#define MPH_LEFT 1
#define MPH_RIGHT 0
#define MPH_LINE_WIDTH 3
#define REGS_TRIANGLE_NUM 1
#define NUM_SPRMASK_REGS 2
#define REGS_TRIANGLESTRIP_NUM 6
#define REGS_LINE_NUM 2
#define MPH_DEBUG_MENU_X 200
#define MPH_DEBUG_MENU_Y 10
#define MPH_DEBUG_MENU_W 100
#define MPH_DEBUG_MENU_H 40
#define MPH_DEBUG_PROCESS_NAME "Morph Debug Process"
#define SAVEPOINTMENU_MAINPROC_NAME "savePoint_menu"
#define SAVEPOINTMENU_WINDOW "SAVEPOINTMENU"

typedef enum {
    HdFontColor_None = 0,
    HdFontColor_Sian = 1,
    HdFontColor_Pink = 2,
} HdFontColor;

typedef enum {
    ITF_LIST_FLAGS_RELEASE = 1,
    ITF_LIST_FLAGS_UPDATE = 2,
    ITF_LIST_FLAGS_SET_POSITION = 4,
    ITF_LIST_FLAGS_SET_APPER = 8,
    ITF_LIST_FLAGS_SET_DISAPPER = 16,
    ITF_LIST_FLAGS_TARGET = 256,
    ITF_LIST_FLAGS_SELECT = 512,
    ITF_LIST_FLAGS_DRAW = 65536,
    ITF_LIST_FLAGS_APPER = 131072,
    ITF_LIST_FLAGS_FADE = 262144,
} ITF_LIST_FLAGS;

typedef enum {
    ITF_LIST_CB_FLAGS_EXIST = 1,
    ITF_LIST_CB_FLAGS_SELECT = 2,
} ITF_LIST_CB_FLAGS;

typedef enum {
    ITF_LIST_STEP_INIT = 0,
    ITF_LIST_STEP_SETWAIT = 1,
    ITF_LIST_STEP_APPER = 2,
    ITF_LIST_STEP_WAIT = 3,
    ITF_LIST_STEP_DISAPPER = 4,
    ITF_LIST_STEP_RELEASE = 5,
    ITF_LIST_STEP_END = 6,
} ITF_LIST_STEP;

typedef enum {
    MENU_PANEL_X = 47,
    MENU_PANEL_Y = 88,
    MENU_PANEL_H = 26,
    MENU_TITLE_X = 93,
    MENU_TITLE_Y = 27,
    MENU_FONT_Z = 1048576,
    MENU_PANEL_Z = 256,
} MENU;

typedef enum {
    MENU_DEF_PANEL_W = 128,
    MENU_DEF_PANEL_H = 26,
    MENU_DEF_TITLE_X = 32,
    MENU_DEF_TITLE_Y = 32,
    MENU_DEF_PANEL_X = 32,
    MENU_DEF_PANEL_Y = 58,
    MENU_DEF_SCROLL_X = 162,
    MENU_DEF_SCROLL_Y = 58,
    MENU_DEF_SCROLL_W = 5,
    MENU_DEF_SCROLL_H = 234,
    MENU_DEF_TTL_COL = 32768,
    MENU_DEF_PNL_COL = 2105376,
    MENU_DEF_SEL_COL = 2105472,
} MENU_DEF;

typedef enum {
    MENU_ATTR_BIT_MSK = 1,
    MENU_ATTR_BIT_SEL = 2,
    MENU_ATTR_BIT_CUR = 4,
    MENU_ATTR_BIT_SELECTED = 8,
    MENU_ATTR_NML = 0,
    MENU_ATTR_SEL = 2,
    MENU_ATTR_MSK = 1,
    MENU_ATTR_MSK2 = 3,
} MENU_ATTR;

typedef enum {
    MENU_LF_RELEASE = 1,
    MENU_LF_SET_MENU = 2,
    MENU_LF_EXE_LINK = 8,
    MENU_LF_MAKE_LINK = 16,
    MENU_LF_UPDATE = 32,
    MENU_LF_APPEAR = 64,
    MENU_LF_UPDATE_SEL = 128,
    MENU_LF_UPDATE_LST = 256,
    MENU_LF_DRAW = 512,
    MENU_LF_DRAW_T = 1024,
    MENU_LF_DRAW_M = 2048,
    MENU_LF_FADE = 4096,
    MENU_LF_FADE_TP = 8192,
    MENU_LF_DEL_MENU = 16384,
    MENU_LF_SEL_MENU = 32768,
    MENU_LF_UPDATE_WAIT = 65536,
} MENU_LF;

typedef enum {
    MENU_CB_LF_EXIST = 1,
    MENU_CB_LF_EXIST_CHILD = 2,
    MENU_CB_LF_SELECT = 4,
    MENU_CB_LF_DELETE = 8,
    MENU_CB_LF_FLASH = 16,
    MENU_CB_LF_ALPHA = 4096,
    MENU_CB_LF_FADE = 8192,
    MENU_CB_LF_MOVE_IN = 16384,
    MENU_CB_LF_MOVE_OUT = 32768,
} MENU_CB_LF;

typedef enum {
    MENU_IMG_LF_LOAD_SPR = 2,
} MENU_IMG_LF;

typedef enum {
    MAPMENU_PANEL_X = 322,
    MAPMENU_PANEL_Y = 71,
    MAPMENU_PANEL_W = 128,
    MAPMENU_PANEL_H = 23,
    MAPMENU_PANEL_FX = 17,
    MAPMENU_PANEL_FY = 4,
    MAPMENU_PANEL_NX = 130,
    MAPMENU_PANEL_NY = 8,
} MAPMENU_PANEL;

typedef enum {
    MAPMENU_FLAG_RELEASE = 1,
    MAPMENU_FLAG_DRAW = 2,
    MAPMENU_FLAG_LOAD_SPR_MEM = 4,
    MAPMENU_FLAG_LOAD_SPR_HND = 8,
    MAPMENU_FLAG_CALL_START = 16,
    MAPMENU_FLAG_CALL_END = 32,
} MAPMENU_FLAG;

typedef enum {
    MAPMENU_STEP_WAIT = 0,
    MAPMENU_STEP_MAIN = 1,
    MAPMENU_STEP_RELEASE = 2,
    MAPMENU_STEP_END_WAIT = 3,
    MAPMENU_STEP_END = 4,
    MAPMENU_STEP_SUB = 5,
    MAPMENU_STEP_SUB_WAIT = 6,
} MAPMENU_STEP;

typedef enum {
    SAVEPOINTMENU_STEP_WAIT = 0,
    SAVEPOINTMENU_STEP_MAIN = 1,
    SAVEPOINTMENU_STEP_RELEASE = 2,
    SAVEPOINTMENU_STEP_END_WAIT = 3,
    SAVEPOINTMENU_STEP_END = 4,
} SAVEPOINTMENU_STEP;

typedef enum {
    SAVEPOINTMENU_FLAG_RELEASE = 1,
    SAVEPOINTMENU_FLAG_DRAW = 2,
    SAVEPOINTMENU_FLAG_LOAD_SPR_MEM = 4,
    SAVEPOINTMENU_FLAG_LOAD_SPR_HND = 8,
    SAVEPOINTMENU_FLAG_CALL_START = 16,
    SAVEPOINTMENU_FLAG_CALL_END = 32,
} SAVEPOINTMENU_FLAG;

typedef struct FontReq_t FontReq_t;
typedef struct LIPSYNC_PARAM LIPSYNC_PARAM;
typedef struct LOGDISP_PARAM LOGDISP_PARAM;
typedef struct MenuCB_tag MenuCB_tag;
typedef struct MenuCsrUnity MenuCsrUnity;
typedef struct MenuImgDat_t MenuImgDat_t;
typedef struct MenuMover_t MenuMover_t;
typedef struct MenuSelectData MenuSelectData;
typedef struct Menu_t Menu_t;
typedef struct Speaker_tag Speaker_tag;
typedef struct Text_t Text_t;
typedef struct awdMenu_t awdMenu_t;
typedef struct curctr_tag curctr_tag;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct debug_tag debug_tag;
typedef struct elvMenu_t elvMenu_t;
typedef struct frFontTable_t frFontTable_t;
typedef struct frMsgInfo_t frMsgInfo_t;
typedef struct instanceMes_tag instanceMes_tag;
typedef struct itf itf;
typedef struct itfMesBinFileHeader_t itfMesBinFileHeader_t;
typedef struct itfMesBinMesHeader_t itfMesBinMesHeader_t;
typedef struct itfMesBinTypeHeader2_t itfMesBinTypeHeader2_t;
typedef struct itfMesBinTypeHeader_t itfMesBinTypeHeader_t;
typedef struct itfMover_t itfMover_t;
typedef struct itfPanelTypeWork_t itfPanelTypeWork_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct itfpanel_t itfpanel_t;
typedef struct manager_tag manager_tag;
typedef struct mesflow_tag mesflow_tag;
typedef struct message_tag message_tag;
typedef struct mphDebugWork_t mphDebugWork_t;
typedef struct mphPoint_t mphPoint_t;
typedef struct mphWork_t mphWork_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfIVector4_t sdfIVector4_t;
typedef struct select_tag select_tag;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagITFDVLMSG_CB tagITFDVLMSG_CB;
typedef struct tagITFDVLMSG_PARAM tagITFDVLMSG_PARAM;
typedef struct tagITFDVLMSG_WORK tagITFDVLMSG_WORK;
typedef struct tagITF_LIST_CB tagITF_LIST_CB;
typedef struct tagITF_LIST_WK tagITF_LIST_WK;
typedef struct tagITF_MONEY_WORK tagITF_MONEY_WORK;
typedef struct tagMAP_MENU_WORK tagMAP_MENU_WORK;
typedef struct tagSAVEPOINT_MENU_WORK tagSAVEPOINT_MENU_WORK;
typedef struct variable_tag variable_tag;
typedef struct window_tag window_tag;

typedef void (*MenuSetMoverFunc_t)(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
typedef void (*g_pdrawDelegate)(itfpanel_t *UnnamedParameter, sdfDrawTag_t *UnnamedParameter2);

struct tagITF_LIST_CB {
    u32 flags;
    ITF_LIST_TYPE type;
    char *str;
    s32 num;
    itfMover_t *mover;
};

struct tagITF_LIST_WK {
    dds3ProcessID_t *drawPID;
    sprHandle_t *phSpr;
    u32 flags;
    s32 posx;
    s32 posy;
    s32 count;
    s32 frame;
    ITF_LIST_STEP step;
    s8 typeApper;
    s8 typeDisapper;
    s8 selNo;
    s32 listTopNo;
    s32 listNum;
    tagITF_LIST_CB *cb[8];
};

struct tagMAP_MENU_WORK {
    sprHandle_t *hSpr;
    dds3ProcessID_t *menuPID;
    u8 step;
    u8 flag;
    s16 count;
    s32 selectID;
    s8 tabpage;
    s8 tabmax;
    u32 selectUNIQ;
};

struct tagSAVEPOINT_MENU_WORK {
    sprHandle_t *hSpr;
    dds3ProcessID_t *menuPID;
    u8 step;
    u8 flag;
    s16 count;
    s32 selectID;
    s32 selectUnkuiID;
};

struct itf {
    u8 script_scr[717];
};

struct awdMenu_t {
    sprHandle_t *hSpr;
    dds3ProcessID_t *listPID;
    u8 flag;
    u8 step;
    s16 count;
    s32 selectID;
    s32 selectMsg;
};

struct elvMenu_t {
    sprHandle_t *hSpr;
    dds3ProcessID_t *listPID;
    u8 flag;
    u8 step;
    s16 count;
    s32 selectID;
    s32 initID;
    s32 top;
};

struct tagITFDVLMSG_PARAM {
    s32 x;
    s32 y;
    u32 rgb;
    s32 alpha;
};

struct tagITFDVLMSG_CB {
    u8 *pDatMsg;
    void *pDatTex;
    tagITFDVLMSG_CB *pPrev;
    tagITFDVLMSG_CB *pNext;
    s32 devilID;
};

struct tagITFDVLMSG_WORK {
    dds3ProcessID_t *drawPID;
    sprHandle_t *hSpr;
    tagITFDVLMSG_CB *pHead;
    tagITFDVLMSG_CB *pTail;
    s32 datNum;
    s32 devilID;
    s32 msgID;
    tagITFDVLMSG_CB *pDraw;
    itfMover_t *mover;
    itfMover_t *iconMover;
    s32 iconSprNo;
    tagITFDVLMSG_PARAM *param[7];
    s16 step;
    s16 step2;
    u16 gflag;
    u16 lflag;
    s32 count;
};

struct tagITF_MONEY_WORK {
    dds3ProcessID_t *drawPID;
    dds3ProcessID_t *countPID;
    u8 step;
    ITF_COUNT_TYPE type;
    u8 mode;
    u8 flags;
    s32 count;
    s32 money;
    s32 calc;
};

struct mphDebugWork_t {
    s32 stat;
    s32 fileIndex;
    s32 leftRight;
    s32 menuIndex;
};

static dds3ProcessID_t *awdMenu_g_mainPID;
static u8 *itf_sys;
static char *strSystem;
static char *strIkai;
static dds3ProcessID_t *elvMenu_g_mainPID;
static char *strKaisou;
u8 frImageDumpFlag;
static frFontTable_t *gFT;
u32 gMessageRequestResult;
static s32 gMessageStepY;
static s32 asiaDisplaySpeed;
static s32 otherDisplaySpeed;
static s8 *gFontBaseWidth;
static s32 gLipsTarget;
static s32 gLipsType;
static s8 gModeFlag;
static char *gVarStr;
u32 gFontDrawOT;
static char *DrawBuffer;
static u32 DrawColor;
static char *BtnList;
static char *BstList;
static char *IcnList;
static char *ItemList;
static char *SkilList;
static char *DependentList;
static char *MenuList;
static char *RaiSkilList;
static char *TagList;
static u8 frSetFontString_style;
static s32 *ReturnNum;
static s32 *arrParam;
static dds3ProcessID_t *DevilMessage_g_mainPID;
sprHandle_t *generalMenu_g_hSpr;
static itfSprList_t *arrSprListTitle;
static itfSprList_t *arrSprListPanel;
static itfSprList_t *arrSprListSelect;
static itfSprList_t *arrSprListScrollBar;
static sprHandle_t *g_hSpr;
static itfSprList_t *aSprListPanelNormal;
static itfSprList_t *aSprListPanelNormalSelect;
static s32 *aItfListPanelH;
f32 SCROLLBAR_LENGTH_MAX;
f32 SCROLL_LENGTH_MAX;
static DDS3_OT g_ot;
static s32 g_MenuDecideKey;
static MenuSetMoverFunc_t *itfMenuSetMoverFuncAppear;
static MenuSetMoverFunc_t *itfMenuSetMoverFuncDisappear;
static f32 itfMenuSetMoverDisappear00_fx;
static f32 itfMenuSetMoverDisappear00_fy;
static f32 itfMenuSetMoverDisappear01_fx;
static f32 itfMenuSetMoverDisappear01_fy;
static f32 itfMenuSetMoverDisappear02_fx;
static f32 itfMenuSetMoverDisappear02_fy;
static f32 itfMenuSetMoverDisappear_fx;
static f32 itfMenuSetMoverDisappear_fy;
static s32 itfMenuDrawScrollBar_count;
static f32 itfMenuDrawProcess_fx;
static f32 itfMenuDrawProcess_fy;
s32 battle_key_wait;
static char *bk_msg_guide_name;
LIPSYNC_PARAM *lipsync_pm;
static void *partVoiceDic;
static void *flagVoiceDic;
static void *lblGuideDic;
static s32 part_voice_devil;
static char *msg_guide_name;
s32 SelectYesSe;
static bool LongSelect;
static manager_tag *g_manager;
void *txtMgr;
void *GetureiUI;
void *passwordUI;
static bool bVoicePlaySw;
static bool bWaitVoiceStop;
static s32 bNowSpeaking;
static void *SpkWndTMP;
static s32 MsgWndIndex;
static s32 SelWndId;
static void *MsgWnd;
static void *MsgWndTMP;
static void *MsgWndFocusTMP;
static void *MsgWndCnv;
static void *MsgWndAnm;
static void *MsgWndCur;
static void *MsgWndTMPObj;
static void *MsgWndImg;
static void *MsgWndCnvGrp;
static bool isMesWndBaseDisp;
static bool isMesWndGuideDisp;
bool isActionWndDisp;
static s32 ActionWndLine;
static f32 actionWindowAddPosY;
static void *mesSelectIndex;
static void *PasswdNum;
static void *fixTagValue;
bool fadeFrontDisp;
static s32 mesPriority;
static void *frqstr;
static s32 meswin_type;
static debug_tag *g_debug;
static u32 gInputPasswdVal;
static s32 gInputPasswdPos;
static s16 gInputPasswdPanelAlpha;
static u8 gInputPasswdEndFlag;
static s16 gInputPasswdCurTimer;
static sdfColor_t gNumCollar;
static sdfColor_t gNumSelectCollar;
static u32 g_padmode;
static s32 SelectWait;
static void *pMsgMes;
char *g_replace_text;
static bool itf_cr_icon;
static f32 org_guide_x;
static s32 uniMenuCursor;
static dds3ProcessID_t *g_mainPID;
static void *mnwork;
static bool isMoneyDisp;
static sdfIVector4_t g_uv_top;
static sdfIVector4_t g_uv_mid;
static sdfIVector4_t g_uv_btm;
static sdfIVector4_t g_uv_all;
static s32 *CreateVertexMesWin_plinestep;
static sdfIVector4_t *CreateColorMesWin_pratio;
static sdfIVector4_t *CreateColorSelWin_pratio;
static sdfIVector4_t *CreateColorPlain_pratio_back;
static sdfIVector4_t *CreateColorPlain_pratio;
static u8 **DrawNormal_s_ppindexlist;
static u8 **DrawNormal_s_ppcolorlist;
static u8 **DrawMesWin_s_ppindexlist;
static u8 **DrawMesWin_s_ppcolorlist;
static u8 *DrawMesWin_s_plinevertlist;
static u8 **DrawMesWin_s_pplinecollist;
static u8 **DrawSelWin_s_ppindexlist;
static u8 **DrawSelWin_s_ppcolorlist;
static u8 *DrawSelWin_s_plinevertlist;
static u8 **DrawSelWin_s_pplinecollist;
static u8 *DrawPlain_s_pindexlist;
static u8 *DrawPlain_s_pcolorlist;
static u8 **DrawPlain_s_ppindexlistframe;
static u8 **DrawPlain_s_ppcolorlistframe;
static u8 *DrawPera1_s_pindexlist;
static u8 *DrawPera1_s_pcolorlist;
static u8 *DrawLeftFade_s_pindexlist;
static u8 *DrawLeftFade_s_pcolorlist;
static u8 **DrawFacility_ppindexlist;
static u8 **DrawFacility_ppcolorlist;
static g_pdrawDelegate *g_pdraw;
static void *slwork;
static bool isStationListDisp;
void *fldUI;
void *map_win;
void *map_progress;
void *map_sts;
void *menu_win;
void *help_win;
void *devil_win;
void *devil_info2;
void *ikai_watari;
void *ikai_titlei;
void *elv;
void *elv_title;
void *ryuketsu;
void *map_staging;
static itfSprList_t *arrMenuPanel;
static itfSprList_t *arrMenuSelect;
static itfSprList_t *arrMenuTitle;
static itfSprList_t *arrMenuScrollBar;
static s32 devilSkillSel;
static s32 devilSkillMax;
static MenuCsrUnity *sklCsr;
static dds3ProcessID_t *mapMenu_g_mainPID;
bool Story11Extra;
bool Story11Select;
bool Story11Cancel;
s32 Story11Number;
bool QuestDevilExtra;
bool QuestDevilSelect;
bool QuestDevilCancel;
bool QuestMenuClose;
s32 QuestDevilNumber;
static s32 mapMenuMode;
bool MenuListScroll;
s32 MenuOldCsr;
mphWork_t *mphWork;
char *filenames;
static mphDebugWork_t *mphDebugWork;
LOGDISP_PARAM *logdispwk;
static char *msglog_akey;
static dds3ProcessID_t *savePointMenu_g_mainPID;
static s32 savePointMenuMode;
static s32 boxX;
static s32 boxY;
static s32 boxW;
static s32 boxH;
static s32 titleX;
static s32 titleY;
static s32 curX;
static s32 tabY;
static s32 menuX;
static s32 menuY;
static s32 menuH;

static s32 awdMenuDecideIkai(void);
static bool awdMenuChkIkai(s32 a_ikaiID);
static bool awdMenuMakeList(awdMenu_t *wk);
static void awdMenuCallProcEnd(awdMenu_t *wk);
static u8 awdMenuCheckProcEnd(awdMenu_t *wk);
static dds3ProcessFunc_t awdMenuProcess(dds3ProcessID_t *PID);
static void awdMenuRelease(awdMenu_t *wk);
static void awdMenuShutdown(dds3ProcessID_t *PID);
static s32 awdMenuMoverFunc(s32 mode);
static s32 elvMenuDecideFunc(void);
static bool elvMenuMakeList(elvMenu_t *wk);
static void elvMenuCallProcEnd(elvMenu_t *wk);
static u8 elvMenuCheckProcEnd(elvMenu_t *wk);
static dds3ProcessFunc_t elvMenuProcess(dds3ProcessID_t *PID);
static void elvMenuRelease(elvMenu_t *wk);
static void elvMenuShutdown(dds3ProcessID_t *PID);
static s32 elvMenuMoverFunc(s32 mode);
static void frInitTextHandle(Text_t *pText, u16 Code, u8 Style, u8 ColNo, u32 Color, u8 Tp);
static void frInitFontHandle(FontReq_t *pFRQ);
static Text_t *frSetFont(u16 Code, u8 Style, u8 ColNo, u8 Tp);
static u8 DisplaySpeed(void);
static s8 frEraseEffect(FontReq_t *pFRQ);
static FontReq_t *frAnalyzeMessageLocalize(frMsgInfo_t *pMsgInfo, bool spc, bool hitokoto, bool logmes);
static void MessageCreateHandle(frMsgInfo_t *mi, u16 chcode, s32 font_id);
static char *replace_space(char *message);
static FontReq_t *frSetFontStringLocalize(u16 pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ);
static bool frAnalyzeTagLocalize1(s32 code, frMsgInfo_t *mi, char **message, void *index);
static bool frAnalyzeTagLocalize2(char *message, s32 *index, frMsgInfo_t *mi, s32 *font_id);
static s32 GetTagIndex(char *tag);
static char *frReplaceLocalizeText(char *message, frMsgInfo_t *mi, void *index);
static void frCreateNewHandle(frMsgInfo_t *pMsgInfo);
static void frMessageReturnCode(frMsgInfo_t *pMsgInfo);
static char *GetCommaChgPar(void);
static void frInitUvTable(void);
static dds3ProcessFunc_t CountProcess(dds3ProcessID_t *PID);
static void CountShutdown(dds3ProcessID_t *PID);
static bool DvlMsgCreateCB(tagITFDVLMSG_WORK *wk);
static void DvlMsgDeleteCB(tagITFDVLMSG_WORK *wk, tagITFDVLMSG_CB *cb);
static tagITFDVLMSG_CB *DvlMsgGetCB(tagITFDVLMSG_WORK *wk, s32 a_devilID);
static void DvlMsgFreeMsg(tagITFDVLMSG_CB *cb);
static void DvlMsgFreeTex(tagITFDVLMSG_CB *cb);
static bool DvlMsgLoadFile(tagITFDVLMSG_WORK *wk, tagITFDVLMSG_CB *cb, s32 a_devilID);
static bool _DvlMsgDeleteData(tagITFDVLMSG_WORK *wk, tagITFDVLMSG_CB *cb);
static void DvlMsgLoadSprite(tagITFDVLMSG_WORK *wk);
static void DvlMsgSetMover(tagITFDVLMSG_WORK *wk, s32 a_mode);
static void DvlMsgInitParam(tagITFDVLMSG_WORK *wk);
static void DvlMsgRelease(tagITFDVLMSG_WORK *wk);
static dds3ProcessFunc_t DvlMsgProcess(dds3ProcessID_t *PID);
static bool DvlMsgDrawTextFont(s32 x, s32 y, s32 z, u32 a_color, f32 a_alphaRate, s32 msgNo, u8 *pDatMsg);
static void DvlMsgDrawWindow(tagITFDVLMSG_WORK *wk, s32 ofs_x, s32 ofs_y, f32 a_alphaRate);
static dds3ProcessFunc_t DvlMsgDrawProcess(dds3ProcessID_t *PID);
static void DvlMsgInit(tagITFDVLMSG_WORK *wk);
static void DvlMsgShutdown(dds3ProcessID_t *PID);
static void _DrawMiscFont(ITF_DM_STYLE a_style, s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_space, u32 a_col, DDS3_OT a_ot, char *a_str);
static void ListSetApperFade(tagITF_LIST_WK *wk);
static void ListSetDisapperFade(tagITF_LIST_WK *wk);
static void ListSetApper(tagITF_LIST_WK *wk);
static void ListSetDisapper(tagITF_LIST_WK *wk);
static bool ListUpdateMover(tagITF_LIST_WK *wk);
static void ListInit(tagITF_LIST_WK *wk);
static void ListDelete(tagITF_LIST_WK *wk);
static void ListRelease(tagITF_LIST_WK *wk);
static void ListShutdown(dds3ProcessID_t *PID);
static dds3ProcessFunc_t ListProcess(dds3ProcessID_t *PID);
static void ListDrawNumSmallFont(s32 a_x, s32 a_y, s32 a_z, u32 a_color, u8 a_alpha, s32 a_num);
static void ListDrawPanelNormal(tagITF_LIST_WK *wk, s32 a_x, s32 a_y, u8 a_alpha);
static void ListDrawPanel(tagITF_LIST_WK *wk, ITF_LIST_TYPE a_type, s32 a_x, s32 a_y, u8 a_alpha);
static u8 ListCalcMoverAlpha(tagITF_LIST_WK *wk, itfMover_t *mv);
static void ListDrawCB(tagITF_LIST_WK *wk, s32 a_listNo);
static dds3ProcessFunc_t ListDrawProcess(dds3ProcessID_t *PID);
static void MenuCtrlSelect(Menu_t *wk, s32 a_keytype, bool a_bPlaySE);
static s32 MenuRemakeLinkSub(Menu_t *wk);
static void MenuSetMoverAppear00(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverAppear01(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverAppear02(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverAppear03(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverAppear04(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverAppear(Menu_t *wk, s32 a_type);
static void MenuSetMoverDisappear00(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverDisappear01(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverDisappear02(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverDisappear03(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h);
static void MenuSetMoverDisappear(Menu_t *wk, s32 a_type);
static bool MenuUpdateMover(Menu_t *wk);
static MenuCB_tag *MenuGetBlankMenu(Menu_t *wk);
static void MenuCreateMenu(Menu_t *wk);
static void MenuDeleteMenu(Menu_t *wk, MenuCB_tag *cb);
static bool MenuClearMenuSub(Menu_t *wk, MenuCB_tag *cb);
static bool _MenuSetMenu(MenuCB_tag *cb, s32 a_id, s32 a_parentId, char *a_str, itfMenuFunc_t a_func, char *a_tag);
static void MenuSetDispType(dds3ProcessID_t *PID, s32 a_mode, s32 a_type);
static bool _MenuSetFlagMenu(Menu_t *wk, s32 a_id, ITFMENU_CB_GF a_bit, bool a_bSet, bool a_bGlobal);
static MenuCB_tag *MenuGetMenu(Menu_t *wk, s32 a_hierarchy, s32 a_no);
static MenuCB_tag *MenuGetSelectMenu(Menu_t *wk);
static bool MenuUpdateSelectMenu(Menu_t *wk);
static void MenuUpdateLinkMover(Menu_t *wk);
static void MenuUpdateNextLink(Menu_t *wk);
static void MenuUpdatePrevLink(Menu_t *wk);
static void MenuMakeLink(Menu_t *wk);
static sprHandle_t *MenuLoadSprite(u8 *str);
static bool _MenuSetImageColor(Menu_t *wk, ITFMENU_IMG_DAT a_type, u8 a_R, u8 a_G, u8 a_B, u8 a_A);
static bool MenuDelMenuSub(Menu_t *wk, s32 a_id);
static void MenuInit(Menu_t *wk);
static bool MenuCtrlSelectSub(Menu_t *wk, s32 a_keyType);
static bool MenuCtrlSelectSubHD(Menu_t *wk, s32 a_keyType);
static bool MenuChkCtrlSelect(Menu_t *wk, bool a_bUpdate);
static void MenuPadCtrlSelect(Menu_t *wk);
static bool MenuMoveNextHierarchy(Menu_t *wk, bool extra);
static void MenuMoveEnd(Menu_t *wk);
static bool MenuMoveHierarchy(Menu_t *wk, ITFMENU_MOVE_TYPE a_type, bool extra);
static void MenuPlayDecideSE(MenuCB_tag *cb);
static void MenuPlayCancelSE(MenuCB_tag *cb);
static dds3ProcessFunc_t MenuProcess(dds3ProcessID_t *PID);
static void MenuDrawFont(MenuImgDat_t *pImgDat, s32 x, s32 y, u32 color, u8 alpha, char *str, char *tag);
static void MenuDrawScrollBar(Menu_t *wk, s32 a_topno, s32 a_selmax, u8 a_alphaRate);
static void _MenuDrawPanelEGL(s32 a_x, s32 a_y, s32 a_w, s32 a_h, u32 a_col);
static void MenuDrawPanelEGL(s32 a_type, s32 a_x, s32 a_y, s32 a_w, s32 a_h, u8 a_alpha);
static void MenuDrawPanel(Menu_t *wk, MenuMover_t *mv, u8 a_alpha, s8 a_attr);
static void MenuDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
static bool awdMenuDrawTargetCheck(s32 no);
static void awdMenuDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
static void elvMenuDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
static void ShopDbgDrawFont(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
static void NakamaSelDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
static void MenuDrawTitle(Menu_t *wk, s32 a_x, s32 a_y, u8 a_alpha, char *a_str);
static u8 MenuCalcAlpha(MenuMover_t *mv, u32 lflag);
static dds3ProcessFunc_t MenuDrawProcess(dds3ProcessID_t *PID);
static void MenuRelease(Menu_t *wk);
static void MenuShutdown(dds3ProcessID_t *PID);
static bool IsBattleEvtKeyWait(void);
static bool IsAutoFeed(void);
static void MesVoiceStop(void *src, bool hojo);
static void PartVoiceLoadSub(char *asset_name);
static void SetGuideSub(s32 guide_idx, char *guide_name, bool disp);
static void ChangeEvtGuideText(void);
static sdfDrawTag_t *dds3AllocDrawTag(void);
static char *GetFRQString(FontReq_t *frq);
static void DestructFlow(s32 id);
static void ResolveResourceAddress(void *pdata);
static bool CheckMessageBinary(itfMesBinFileHeader_t *pdata);
static itfMesBinTypeHeader_t *GetTypeHeader(instanceMes_tag *pinst, s32 index);
static itfMesBinTypeHeader2_t *GetTypeHeader2(u8 *pfileheader);
static u8 *GetMessagePagePtr(itfMesBinMesHeader_t *pmesheader, u8 *data, s32 page);
static void WindowDispOn(instanceMes_tag *pinst);
static void ClearMessage(void);
static void ClearSpeaker(void);
static void WindowDispOff(bool sw);
static void SelectWindowDispOn(instanceMes_tag *pinst);
static bool IsSelectWindowDispOn(void);
static bool IsSelectWindowDispOff(void);
static void SelectWindowDispOff(instanceMes_tag *pinst);
static void SwitchOK(bool sw);
static void FadeOutWindow(void);
static bool IsFadeOutWindow(void);
static void FadeInWindow(void);
static void setGuideMsg(s32 type, Speaker_tag *pspeaker);
static bool IsParticularTag(FontReq_t *pFQR);
static void SwitchSpeaker(bool sw, bool disp);
static void SetMessage(void *obj, s32 line, char *text);
static void SetVar(instanceMes_tag *pinst, s32 index, char *pstr, s32 length);
static void CommitVarTable(variable_tag *pvar);
static u8 *GetSpeakerName(instanceMes_tag *pinst);
static s32 GetNumSelectItem(s32 allitem, u32 mask);
static FontReq_t *GetFontHandleUnit(u8 *dat, u32 *ppstr, s32 *pplen, s32 num, u32 mask, s32 x, s32 y, u32 z);
static void InitializeSelectWindow(FontReq_t *pFRQ, s32 max);
static FontReq_t *UnchainFontHandleUnit(FontReq_t *pfont, s32 index, s32 lines);
static void ChangeFontPosition(FontReq_t *pfont, s32 dist_x, s32 dist_y);
static void ChangeZBuffer(FontReq_t *pfont, u32 z);
static void ChangeSelection(s32 index, s32 onoff);
static void ChangeFontColor(FontReq_t *pfont, s32 index, s32 lines, s32 color);
static void ChangeFontColorAll(FontReq_t *pfont, s32 color);
static void ChangeFontAlpha(FontReq_t *pfont, s32 alpha);
static s32 GetMessageWidth(FontReq_t *pfont);
static s32 GetMaskedIndex(s32 index, u32 mask);
static void RaiseMessageSpeedMax(FontReq_t *pfont);
static void RaiseMessageSpeedMaxAll(FontReq_t *pfont);
static void OpenMessageWindow(instanceMes_tag *pinst);
static void OpenCheckSpeakerWindow(instanceMes_tag *pinst);
static void InitializeSpeaker(Speaker_tag *pspeaker, bool defaultpos);
static void InitializeMessage(message_tag *pmessage, bool defaultpos);
static void InitializeSelect(select_tag *pselect);
static void InitializeWindow(window_tag *pwindow);
static void InitializeVariable(variable_tag *pvariable);
static void InitializeCurCtr(curctr_tag *pcurctr, s32 isdisp);
static void ForceSetCurCtr(curctr_tag *pcurctr, s16 phase, s16 ctr0, s16 ctr1);
static void ReleaseAllWindow(instanceMes_tag *pinst);
static void ReleaseAllVariable(variable_tag *pvariable);
static void ConvertZenkakuNumber(char **buf, s32 num);
static void ResetWindowPara(window_tag *pwin, s32 type, s32 alpha);
static void CalcMesFlow(instanceMes_tag *pinst);
static void CalcWindow(instanceMes_tag *pinst);
static char *GetTagID(instanceMes_tag *pinst);
static void CalcMessage(instanceMes_tag *pinst);
static FontReq_t *create_bufferdata(s32 id, s32 var);
static void GetLastMessagePara(FontReq_t *pfont, message_tag *pmessage);
static s32 CountLineMessage(FontReq_t *pfont_top, FontReq_t *pfont);
static void CalcSelect(instanceMes_tag *pinst);
static bool SelectWaitCancelCheck(void);
static void SlideUpDownMessage(instanceMes_tag *pinst, s32 y);
static bool SelectItem(instanceMes_tag *pinst);
static void SelectItemMove(select_tag *psel, s32 direct);
static s32 SelectItemDefKey(select_tag *psel);
static void CalcCurCtr(instanceMes_tag *pinst);
static void DrawMesFlow(instanceMes_tag *pinst);
static void DrawSpeaker(FontReq_t *pfont);
static void DrawSpeakerSub(FontReq_t *pfont, void *txt);
static s32 DrawMessage(FontReq_t *pfont, FontReq_t *pSpeaker);
static s32 DrawMessageSub(FontReq_t *pfont, FontReq_t *pSpeaker, void *txt, bool logmsg);
static s32 DrawSelection(u32 stat);
static void DrawWindow(instanceMes_tag *pinst);
static void DrawSelectCursor(instanceMes_tag *pinst);
static void DrawRetPageCursor(instanceMes_tag *pinst);
static dds3ProcessFunc_t CalcManagerProc(dds3ProcessID_t *proc_id);
static dds3ProcessFunc_t DrawManagerProc(dds3ProcessID_t *proc_id);
static void SetCrIcon(void);
static void ShutdownProc(dds3ProcessID_t *proc_id);
static void DebugDrawWindowLine(itfpanel_t *meswin);
static void DebugMoveWinVert(window_tag *pwin, s32 flag);
static void DebugMoveWinAlpha(window_tag *pwin);
static mesflow_tag *DebugChangeInstance(mesflow_tag *pflow);
static u8 *GetDataBytes(u8 *data, s32 index, s32 len);
static void CallEventVoice(instanceMes_tag *pinst);
static bool MsgWndActiveSelf(s32 i);
static void InitMesWndSelect(s32 count);
static s32 GetMesWndSelectViewIndex(s32 index);
static void ReadytoMessage(instanceMes_tag *pinst, s32 mode);
static void InputPasswdDraw(void);
static void MoneyCallProcEnd(tagITF_MONEY_WORK *wk);
static u8 MoneyCheckProcEnd(tagITF_MONEY_WORK *wk);
static dds3ProcessFunc_t MoneyProcess(dds3ProcessID_t *PID);
static void MoneyDrawPanel(s32 a_offX, s32 a_offY, u8 a_alpha);
static dds3ProcessFunc_t MoneyDrawProcess(dds3ProcessID_t *PID);
static void MoneyShutdown(dds3ProcessID_t *PID);
static void CreateVertexNormal(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1);
static void CreateVertexMesWin(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1);
static void CreateVertexSelWin(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1);
static void CreateVertexPlain(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1);
static void CreateVertexLeftFade(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1);
static void CreateVertexFacility(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1);
static void CreateColorNormal(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha);
static void CreateColorMesWin(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha);
static void CreateColorSelWin(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha);
static void CreateColorPlain(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha);
static void CreateColorPera1(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha);
static void CreateColorLeftFade(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha);
static void CreateColorFacility(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha);
static void DrawNormal(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawMesWin(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawSelWin(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawPlain(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawPera1(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawLeftFade(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawMesWin2(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawSpkWin2(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawFacility(itfpanel_t *handle, sdfDrawTag_t *pdrawtag);
static void DrawTestAlphaPrim(sdfDrawTag_t *pdrawtag);
static void mapMenuDrawMagWindow(f32 a_rate, u8 a_alphaRate);
static s32 mapMenuDecideFunc(void);
static char *GetMenuHelpID(s32 mapMenuID);
static void mapMenuDrawFuncMenu(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static void mapMenuDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static void SummonMenuSelDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
static void mapMenuSetMenuImage(dds3ProcessID_t *PID);
static dds3ProcessID_t *mapMenuCreateMenuPID(void);
static dds3ProcessID_t *lmapMenuCreateMenuPID(void);
static void mapMenuResetMenu(dds3ProcessID_t *PID);
static void summonMenuResetMenu(dds3ProcessID_t *PID);
static void mapMenuChkEnableDecide(tagMAP_MENU_WORK *wk);
static void mapMenuCallProcEnd(tagMAP_MENU_WORK *wk);
static bool mapMenuCheckProcEnd(tagMAP_MENU_WORK *wk);
static dds3ProcessFunc_t mapMenuProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t lmapMenuProcess(dds3ProcessID_t *PID);
static void mapMenuRelease(tagMAP_MENU_WORK *wk);
static void mapMenuShutdown(dds3ProcessID_t *PID);
static s32 mapMenuMoverFunc(s32 mode);
static dds3ProcessFunc_t mphLoadFileProcess(dds3ProcessID_t *id);
static void mphLoadFileDestroy(dds3ProcessID_t *id);
static void mphInitWork(void);
static dds3ProcessFunc_t mphMain(dds3ProcessID_t *id);
static void mphDestroyData(dds3ProcessID_t *id);
static void mphDestroy(void);
static void mphLinkAlphaPacket(sdfDrawTag_t *pdrawtag, s32 fA, s32 fB, s32 fC, s32 fD, s32 fix);
static void mphLinkTestPacket(sdfDrawTag_t *pdrawtag, u64 para);
static void mphLinkClampPacket(sdfDrawTag_t *pdrawtag, s32 wms, s32 wmt, s32 min_u, s32 max_u, s32 min_v, s32 max_v);
static void mphDrawTriangleStrip(s32 offX, s32 offY, s32 width, s32 height, mphPoint_t *pointArray, u16 *orderArray, s32 num, u32 z, sdfIVector4_t rgba, sdfDrawTag_t *pdrawtag);
static void mphDrawZMaskTri(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 z, sdfDrawTag_t *pdrawtag);
static void mphDrawLine(s32 x0, s32 y0, s32 x1, s32 y1, s32 z, s32 w, s32 color, sdfDrawTag_t *pdrawtag);
static void mphInitPoints(void);
static void mphSetPoints(s32 streamIndex);
static void mphDrawStream(s32 offX, s32 offY, s32 width, s32 height, sdfIVector4_t rgba, sdfDrawTag_t *pdrawtag);
static void mphStartDrawSub(s32 offX, s32 offY, s32 width, s32 height, bool fMask, s32 maskX0, s32 maskY0, s32 maskX1, s32 maskY1, s32 maskX2, s32 maskY2);
static void mphDebugInit(void);
static void mphDebugDrawMenu(void);
static void mphDebugPadDealer(void);
static dds3ProcessFunc_t mphDebugProcess(dds3ProcessID_t *id);
static void mphDebugDestroy(dds3ProcessID_t *id);
static bool MsgLogDispCalc(void);
static void ChangeArrowAnim(s32 curTop, s32 logMax);
static void ButtonGuideCalc(s32 curTop, s32 logMax);
static void MsgLogDispDraw(void);
static void logSpaceCalc(s32 idx, s32 cnt);
static s32 LineCount(char *s);
static void name_spaceActive(s32 idx, s32 cnt);
static void scrollbarInit(void);
static void scrollbarCalc(s32 late);
static bool IsMsgLogStart(void);
static bool CheckChangeAutoFeed(void);
static char *TextColorClose(char *str);
static dds3ProcessFunc_t savePointMenuProcess(dds3ProcessID_t *PID);
static void savePointMenuShutdown(dds3ProcessID_t *PID);
static dds3ProcessID_t *savePointMenuCreateMenuPID(void);
static void savePointMenuOpen(void);
static void savePointMenuClose(void);
static void savePointMenuPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag);
static s32 savePointMenuMoverFunc(s32 mode);
static s32 savePointMenuDecideFunc(void);
static void savePointMenuDrawFuncMenu(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static char *GetPointHelpID(s32 mapMenuID);
static void savePointMenuChkEnableDecide(tagSAVEPOINT_MENU_WORK *wk);
static void savePointMenuCallProcEnd(tagSAVEPOINT_MENU_WORK *wk);
static bool savePointMenuCheckProcEnd(tagSAVEPOINT_MENU_WORK *wk);
static void savePointMenuRelease(tagSAVEPOINT_MENU_WORK *wk);

// macros
// 0x1c2e570: u32 NO2DIC(u32 val)
#define NO2DIC(val) ((val & 0x7F | ((u16)val >> 7 << 8)) + 32896)

// 0x1c2e590: u32 DIC2NO(u32 val)
#define DIC2NO(val) (val & 0x7F | ((u8)((u16)(val + 32640) >> 8) << 7))

// 0x1c2e5b0: s32 FR_STR_WIDTH(FontReq_t *FRQ)
#define FR_STR_WIDTH(FRQ) (FRQ->w_pxls)

// 0x1c2e5c0: u8 FR_DRAW_SPD(FontReq_t *FRQ)
#define FR_DRAW_SPD(FRQ) (FRQ->draw_spd >> 1)

// 0x1c58220: char *DAT_STR_REF_RCNAME(s32 _idx)
#define DAT_STR_REF_RCNAME(_idx) (sdatRaceName(idx))

// 0x1c582b0: char *DAT_STR_REF_DVNAME(s32 _idx)
#define DAT_STR_REF_DVNAME(_idx) (sdatDevilName(idx, 0))

// 0x1c58320: char *DAT_STR_REF_SKNAME(s32 _idx)
#define DAT_STR_REF_SKNAME(_idx) (sdatSkillName(idx))

// 0x1c583b0: char *DAT_STR_REF_ITNAME(s32 _idx)
#define DAT_STR_REF_ITNAME(_idx) (sdatItemName(idx))

// 0x1c58440: char *DAT_STR_REF_DHNAME(s32 _idx)
static inline char *DAT_STR_REF_DHNAME(s32 _idx) {
  char v2;

  v2 = idx;
  return ToString(LOBYTE(HeartsName) + v2 + 32, 0);
}

// 0x1c61e40: s32 SEL_BAKSET(void)
static inline s32 SEL_BAKSET(void) {
  s16 IntPara;

  IntPara = scrGetIntPara(1);
  return MesMngSelect(IntPara, 0);
}

// 0x1c62310: s32 LONGSEL_BAKSET(void)
static inline s32 LONGSEL_BAKSET(void) {
  s16 IntPara;

  IntPara = scrGetIntPara(1);
  return MesMngSelect(IntPara, 1);
}

// 0x1c735d0: s32 CMP_X(s32 a)
#define CMP_X(a) (16 * a)

// 0x1c735e0: s32 CMP_Y(s32 b)
#define CMP_Y(b) (8 * b)

// 0x1c5de70: s32 CMP_XM(s32 a)
static inline s32 CMP_XM(s32 a) {
  f32 v2;

  v2 = (f32)a * 3.75;
  if (v2 == INFINITY)
    return 0;
  else
    return 16 * (s32)v2;
}

// 0x1c3da80: s32 CMP_YM(s32 b)
static inline s32 CMP_YM(s32 b) {
  f32 v2;

  v2 = (f32)b * 2.25;
  if (v2 == INFINITY)
    return 0;
  else
    return 8 * (s32)v2;
}

// 0x1c2e5d0
static s32 awdMenuDecideIkai(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(awdMenu_g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[2].klass) = itfGeneralMenuDecideFunc(ProcessData[1].monitor);
  BYTE1(ProcessData[2].klass) = 2;
  return 1;
}

// 0x1c2e7b0
static bool awdMenuChkIkai(s32 a_ikaiID) {
  char v2;
  u32 v3;

  if ((u32)a_ikaiID > 5)
    return 0;
  v2 = a_ikaiID;
  LOBYTE(v3) = evtBitCheck(dword_3E629F4[a_ikaiID]);
  if (evtBitCheck(176) && !evtBitCheck(184))
    v3 = (0x2Du >> v2) & 1;
  return v3 & 1;
}

// 0x1c2e840
static bool awdMenuMakeList(awdMenu_t *wk) {
  bool v3;
  s32 v4;
  bool v6;
  bool v7;
  bool v8;
  bool v9;
  _BOOL4 v10;
  s32 *EventBit;
  dds3ProcessID_t *PID;
  dds3ProcessID_t *p_listPID;
  dds3ProcessID_t *v16;
  itfMoverFunc_t v17;
  s64 i;
  bool v21;
  void *v23;
  dds3ProcessID_t *v25;
  char *v26;
  char *LocalizeText;
  itfMenuFunc_t v28;
  char *v31;
  dds3ProcessID_t *v35;
  itfMenuTextFunc_t v36;

  v3 = evtBitCheck(48);
  if (evtBitCheck(176))
  {
    if (!(v3 | !evtBitCheck(184)))
      goto LABEL_7;
  }
  else if (!v3)
  {
LABEL_7:
    v4 = 0;
    goto LABEL_12;
  }
  v4 = 1;
LABEL_12:
  v6 = evtBitCheck(74);
  if (!evtBitCheck(176) || evtBitCheck(184))
    v4 += v6;
  v7 = evtBitCheck(1152);
  if (!evtBitCheck(176))
  {
    if (!v7)
      goto LABEL_22;
    goto LABEL_21;
  }
  if (v7 | !evtBitCheck(184))
LABEL_21:
    ++v4;
LABEL_22:
  v8 = evtBitCheck(116);
  if (!evtBitCheck(176))
  {
    if (!v8)
      goto LABEL_29;
    goto LABEL_28;
  }
  if (v8 | !evtBitCheck(184))
LABEL_28:
    ++v4;
LABEL_29:
  v9 = evtBitCheck(135);
  if (!evtBitCheck(176) || evtBitCheck(184))
    v4 += v9;
  v10 = evtBitCheck(169);
  if (evtBitCheck(176))
  {
    if (!evtBitCheck(184) || v10 || v4)
      goto LABEL_45;
LABEL_42:
    EventBit = GBWK->EventBit;
    EventBit[1] |= 0x10000u;
    goto LABEL_45;
  }
  if (!v10 && v4 == 0)
    goto LABEL_42;
LABEL_45:
  PID = itfGeneralMenuCreatePID(28, 65);
  wk->listPID = PID;
  p_listPID = &wk->listPID;
  v16 = p_listPID;
  v17 = Allocate(itfMoverFunc_t);
  _ctor(v17, 0, Method_Project_itf_awdMenuMoverFunc__, 0);
  itfMoverSetMenu(v16, v17);
  itfMenuSetMenuTitle(p_listPID, strSystem[0], "");
  for (i = 0; i != 6; ++i)
  {
    {
      if ((u32)i <= 5)
        goto LABEL_53;
LABEL_56:
      v23 = ikai_watari->panel[i];
      fldSetupObject(v23, 0);
      if (++i == 6)
        return 1;
    }
    if ((u32)i > 5)
      goto LABEL_56;
LABEL_53:
    v21 = evtBitCheck(dword_3E629F4[i]);
    if (evtBitCheck(176) && !evtBitCheck(184))
    {
      if ((u32)i > 5 || ((1 << i) & 0x2D) == 0)
        goto LABEL_56;
    }
    else if (!v21)
    {
      goto LABEL_56;
    }
    v25 = p_listPID;
    v26 = strIkai[i];
    LocalizeText = GetLocalizeText(v26, 0);
    v28 = Allocate(itfMenuFunc_t);
    _ctor(v28, 0, Method_Project_itf_awdMenuDecideIkai__, 0);
    v31 = strIkai[i];
    itfMenuSetMenu(v25, i, -1, LocalizeText, v28, v31);
    itfMenuSetFlagMenu(p_listPID, i, 64, 0);
    itfMenuSetFlagMenu(p_listPID, i, 128, 1);
    itfMenuSetFlagMenu(p_listPID, i, 512, 1);
    v35 = p_listPID;
    v36 = Allocate(itfMenuTextFunc_t);
    _ctor(v36, 0, Method_Project_itf_awdMenuDrawPanelForUnity__, 0);
    itfMenuSetDrawFunc(v35, i, 0, v36);
  }
  return 1;
}

// 0x1c2f6e0
static void awdMenuCallProcEnd(awdMenu_t *wk) {
  dds3ProcessID_t *listPID;
  dds3ProcessID_t *v5;

  listPID = wk->listPID;
  v5 = listPID;
  itfMenuProcessEnd(v5);
}

// 0x1c2f8a0
static u8 awdMenuCheckProcEnd(awdMenu_t *wk) {
  dds3ProcessID_t *listPID;
  dds3ProcessID_t *id;

  listPID = wk->listPID;
  id = listPID;
  if (!listPID)
    return 0;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  if (dds3GetProcessStat(id))
    return 1;
  return 0;
}

// 0x1c2fac0
static dds3ProcessFunc_t awdMenuProcess(dds3ProcessID_t *PID) {
  awdMenu_t *ProcessData;
  dds3ProcessID_t *p_listPID;
  dds3ProcessID_t *v9;
  char *v11;
  char *LocalizeText;
  char v13;
  s32 v14;
  dds3ProcessID_t *v17;
  dds3ProcessID_t *v18;
  dds3ProcessFunc_t v20;
  dds3ProcessID_t *listPID;
  dds3ProcessID_t *v25;
  dds3ProcessID_t *v27;
  s32 SelectID;
  dds3ProcessID_t *id;

  ProcessData = dds3GetProcessData(awdMenu_g_mainPID);
  if (!ProcessData)
  switch (ProcessData->step)
  {
    case 0u:
      if ((ProcessData->flag & 4) == 0)
        return 0;
      ProcessData->flag &= ~4u;
      ProcessData->selectID = -2;
      awdMenuMakeList(ProcessData);
      listPID = ProcessData->listPID;
      itfMenuStart(listPID);
      v13 = 1;
      goto LABEL_45;
    case 1u:
      p_listPID = &ProcessData->listPID;
      v9 = ProcessData->listPID;
      id = ProcessData->listPID;
      if (v9)
      {
        if (dds3GetProcessStat(id) != 3)
        {
          if (dds3GetProcessStat(id))
            return 0;
        }
      }
      ProcessData->selectID = -1;
LABEL_55:
      ProcessData->listPID = 0;
      ProcessData->step = 0;
      return 0;
    case 2u:
      Create(0);
      fclLinkData(itf_sys);
      v11 = strIkai[ProcessData->selectID];
      LocalizeText = GetLocalizeText(v11, 1);
      fclSetMessageVar(0, LocalizeText);
      fclStart2(1, 0, 1);
      fclSetSelMes(g_mainPID, 0);
      SetMessagePos(0);
      fclSetSelCancelPos(1);
      v13 = 3;
      goto LABEL_45;
    case 3u:
      v14 = Update();
      if (v14 == 1)
      {
        v27 = ProcessData->listPID;
        SelectID = itfMenuGetSelectID(v27);
        itfMenuSetFlagMenu(v27, SelectID, 8, 0);
        itfMenuSetFlag(v27, 8, 1);
        ProcessData->step = 1;
        goto LABEL_66;
      }
      if (v14)
        return 0;
      ProcessData->step = 4;
LABEL_66:
      Delete(0);
      return 0;
    case 4u:
      v17 = ProcessData->listPID;
      itfMenuSetFlag(v17, 2048, 1);
      v13 = 5;
      goto LABEL_45;
    case 5u:
      p_listPID = &ProcessData->listPID;
      v18 = ProcessData->listPID;
      itfMenuProcessEnd(v18);
      goto LABEL_55;
    case 6u:
      if (ProcessData->count)
      {
        goto LABEL_37;
      }
      v25 = ProcessData->listPID;
      itfMenuProcessEnd(v25);
LABEL_37:
      if (awdMenuCheckProcEnd(ProcessData))
      {
        ++ProcessData->count;
        return 0;
      }
      v13 = 7;
      ProcessData->count = 0;
LABEL_45:
      ProcessData->step = v13;
      return 0;
    case 7u:
      v20 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v20, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v20;
    default:
      return 0;
  }
}

// 0x1c303b0
bool awdMenuCheckWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(awdMenu_g_mainPID);
  if (!ProcessData)
    return !BYTE1(ProcessData[2].klass) && ((s64)ProcessData[2].klass & 4) == 0;
  return !BYTE1(ProcessData[2].klass) && ((s64)ProcessData[2].klass & 4) == 0;
}

// 0x1c304e0
bool awdMenuStart(void) {
  Il2CppObject *ProcessData;
  s32 v5;

  ProcessData = dds3GetProcessData(awdMenu_g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v5 = BYTE1(ProcessData[2].klass);
  if (!BYTE1(ProcessData[2].klass))
    LOBYTE(ProcessData[2].klass) |= 4u;
  return v5 == 0;
}

// 0x1c30620
s32 awdMenuGetSelectID(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(awdMenu_g_mainPID);
  if (!ProcessData)
    return ProcessData[9];
  return ProcessData[9];
}

// 0x1c30730
static void awdMenuRelease(awdMenu_t *wk) {
  if (generalMenu_g_hSpr)
    generalMenu_g_hSpr = 0;
  wk->hSpr = 0;
}

// 0x1c308f0
static void awdMenuShutdown(dds3ProcessID_t *PID) {
  awdMenu_t *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  fclDestroyMessage();
  if (!ProcessData)
  awdMenuRelease(ProcessData);
  awdMenu_g_mainPID = 0;
}

// 0x1c30a40
void awdMenuProcessStart(void) {
  awdMenu_t *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;

  v1 = Allocate(awdMenu_t);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_itf_awdMenuProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_itf_awdMenuShutdown__, 0);
  started = dds3StartProcess("ikai_menu_proc", 1023, 0, 0, v2, v3, v1);
  awdMenu_g_mainPID = started;
  v1->selectID = -2;
}

// 0x1c30be0
void awdMenuProcessEnd(void) {
  Il2CppObject *ProcessData;
  char klass;

  if (!awdMenu_g_mainPID)
    return;
  if (!dds3ExistProcess(awdMenu_g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(awdMenu_g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  klass = ProcessData[2].klass;
  if ((klass & 1) == 0)
  {
    WORD1(ProcessData[2].klass) = 0;
    LOBYTE(ProcessData[2].klass) = klass | 1;
    BYTE1(ProcessData[2].klass) = 6;
  }
}

// 0x1c30d90
bool awdMenuProcessCheck(void) {
  if (!awdMenu_g_mainPID)
    return 0;
  if (dds3GetProcessStat(awdMenu_g_mainPID) != 3)
  {
    if (dds3GetProcessStat(awdMenu_g_mainPID))
    {
      return 1;
    }
  }
  awdMenu_g_mainPID = 0;
  return 0;
}

// 0x1c30f10
static s32 awdMenuMoverFunc(s32 mode) {
  void *setTitle;
  void *v14;
  char *v15;
  char *LocalizeText;

  if (op_Equality(ikai_watari, 0, 0))
    return 0;
  if (mode != 1)
  {
    if (mode)
      return 1;
    setTitle = ikai_titlei->setTitle;
    if (!op_Inequality(setTitle, 0, 0))
    {
LABEL_15:
      MenuOpne(ikai_titlei, 0);
      MenuOpne(ikai_watari, 0);
      ButtonGuideDispSet("FLD02", 0, 90);
      ButtonLineHelpDispSet(0);
      return 1;
    }
    v14 = ikai_titlei->setTitle;
    v15 = strSystem[0];
    LocalizeText = GetLocalizeText(v15, 1);
    (v14->klass->vtable._66_set_text.methodPtr)(v14, LocalizeText, v14->klass->vtable._66_set_text.method);
    goto LABEL_15;
  }
  MenuClose(ikai_titlei, 0);
  MenuClose(ikai_watari, 0);
  ButtonGuideDispOff();
  return 1;
}

// 0x1c31200
static s32 elvMenuDecideFunc(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;

  ProcessData = dds3GetProcessData(elvMenu_g_mainPID);
  v5 = ProcessData;
  HIDWORD(ProcessData[2].klass) = itfGeneralMenuDecideFunc(ProcessData[1].monitor);
  itfMenuSetFlag(v5[1].monitor, 512, 1);
  itfMenuSetFlag(v5[1].monitor, 8, 1);
  return 0;
}

// 0x1c31330
static bool elvMenuMakeList(elvMenu_t *wk) {
  void **v4;
  char **v5;
  dds3ProcessID_t *PID;
  dds3ProcessID_t *p_listPID;
  dds3ProcessID_t *v8;
  itfMoverFunc_t v9;
  dds3ProcessID_t *v11;
  char *v12;
  char *LocalizeText;
  s64 i;
  dds3ProcessID_t *v18;
  itfMenuTextFunc_t v19;
  dds3ProcessID_t *v22;
  void **v23;
  char *v24;
  char *v25;
  itfMenuFunc_t v26;
  char **v27;
  char *v28;

  v4 = &Localize;
  v5 = &"";
  PID = itfGeneralMenuCreatePID(28, 65);
  wk->listPID = PID;
  p_listPID = &wk->listPID;
  v8 = p_listPID;
  v9 = Allocate(itfMoverFunc_t);
  _ctor(v9, 0, Method_Project_itf_elvMenuMoverFunc__, 0);
  itfMoverSetMenu(v8, v9);
  v11 = p_listPID;
  v12 = strKaisou[0];
  LocalizeText = GetLocalizeText(v12, 1);
  itfMenuSetMenuTitle(v11, LocalizeText, "");
  for (i = 0; i != 10; ++i)
  {
    v22 = p_listPID;
    v23 = v4;
    v24 = strKaisou[i + 1];
    if (!*((u32 *)*v4 + 56))
    v25 = GetLocalizeText(v24, 1);
    v26 = Allocate(itfMenuFunc_t);
    _ctor(v26, 0, Method_Project_itf_elvMenuDecideFunc__, 0);
    v27 = v5;
    v28 = *v5;
    itfMenuSetMenu(v22, i, -1, v25, v26, v28);
    itfMenuSetFlagMenu(p_listPID, i, 64, 0);
    itfMenuSetFlagMenu(p_listPID, i, 512, 1);
    v18 = p_listPID;
    v19 = Allocate(itfMenuTextFunc_t);
    _ctor(v19, 0, Method_Project_itf_elvMenuDrawPanelForUnity__, 0);
    itfMenuSetDrawFunc(v18, i, 0, v19);
    v4 = v23;
    v5 = v27;
  }
  return 1;
}

// 0x1c31620
static void elvMenuCallProcEnd(elvMenu_t *wk) {
  dds3ProcessID_t *listPID;
  dds3ProcessID_t *v5;

  listPID = wk->listPID;
  v5 = listPID;
  itfMenuProcessEnd(v5);
}

// 0x1c316b0
static u8 elvMenuCheckProcEnd(elvMenu_t *wk) {
  dds3ProcessID_t *listPID;
  dds3ProcessID_t *id;

  listPID = wk->listPID;
  id = listPID;
  if (!listPID)
    return 0;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  if (dds3GetProcessStat(id))
    return 1;
  return 0;
}

// 0x1c317f0
static dds3ProcessFunc_t elvMenuProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  elvMenu_t *v6;
  s64 naturalAligment;
  dds3ProcessID_t *listPID;
  s32 initID;
  char v14;
  dds3ProcessFunc_t v17;
  s64 v18;
  s64 v19;
  dds3ProcessID_t *v21;
  dds3ProcessID_t *v23;
  dds3ProcessID_t *id;

  ProcessData = dds3GetProcessData(elvMenu_g_mainPID);
  v6 = ProcessData;
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)naturalAligment || ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] != elvMenu_t)
    {
LABEL_58:
    }
  }
  switch (BYTE1(ProcessData[2].klass))
  {
    case 0:
      if (((s64)ProcessData[2].klass & 4) == 0)
        return 0;
      LOBYTE(ProcessData[2].klass) &= ~4u;
      HIDWORD(ProcessData[2].klass) = -1;
      evtMoonDisableDraw(1);
      elvMenuMakeList(v6);
      listPID = v6->listPID;
      initID = v6->initID;
      itfMenuSetInitSelectID(listPID, initID);
      itfMenuSetFlagMenu(v6->listPID, v6->initID, 2, 0);
      itfMenuStart(v6->listPID);
      v14 = 1;
      v6->top = 0;
      goto LABEL_40;
    case 1:
      ProcessData = dds3GetProcessData(&ProcessData[1].monitor);
      if (!ProcessData)
        goto LABEL_30;
      if (ProcessData->klass->_2.naturalAligment >= (u32)v18 && (Menu_t *)ProcessData->klass->_2.typeHierarchy[v18 - 1] == Menu_t)
      {
LABEL_30:
        v19 = (s64)ProcessData[9].monitor + 4 * SBYTE4(ProcessData[5].monitor);
        v21 = v6->listPID;
        v6->top = *(u32 *)(v19 + 32);
        id = v21;
        if (!v21)
          goto LABEL_51;
        if (dds3GetProcessStat(id) == 3)
          goto LABEL_51;
        if (dds3GetProcessStat(id))
          return 0;
LABEL_51:
        v6->listPID = 0;
        evtMoonEnableDraw();
        v6->step = 0;
        return 0;
      }
      goto LABEL_58;
    case 2:
      if (WORD1(ProcessData[2].klass))
      {
        goto LABEL_24;
      }
      v23 = v6->listPID;
      itfMenuProcessEnd(v23);
LABEL_24:
      if (elvMenuCheckProcEnd(v6))
      {
        ++v6->count;
        return 0;
      }
      v14 = 3;
      v6->count = 0;
LABEL_40:
      v6->step = v14;
      return 0;
    case 3:
      v17 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v17, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v17;
    default:
      return 0;
  }
}

// 0x1c31dd0
dds3ProcessID_t *itfGetElvPID(void) {
  return elvMenu_g_mainPID;
}

// 0x1c31e50
s32 itfGetElvTopNum(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(elvMenu_g_mainPID);
  if (!ProcessData)
    return ProcessData[11];
  return ProcessData[11];
}

// 0x1c31f60
bool elvMenuCheckWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(elvMenu_g_mainPID);
  if (!ProcessData)
    return !BYTE1(ProcessData[2].klass) && ((s64)ProcessData[2].klass & 4) == 0;
  return !BYTE1(ProcessData[2].klass) && ((s64)ProcessData[2].klass & 4) == 0;
}

// 0x1c32090
bool elvMenuStart(s32 a_initID) {
  Il2CppObject *ProcessData;
  s32 v7;
  char klass;

  ProcessData = dds3GetProcessData(elvMenu_g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v7 = BYTE1(ProcessData[2].klass);
  if (!BYTE1(ProcessData[2].klass))
  {
    klass = ProcessData[2].klass;
    LODWORD(ProcessData[2].monitor) = a_initID;
    LOBYTE(ProcessData[2].klass) = klass | 4;
  }
  return v7 == 0;
}

// 0x1c321e0
s32 elvMenuGetSelectID(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(elvMenu_g_mainPID);
  if (!ProcessData)
    return ProcessData[9];
  return ProcessData[9];
}

// 0x1c322f0
static void elvMenuRelease(elvMenu_t *wk) {
  if (generalMenu_g_hSpr)
    generalMenu_g_hSpr = 0;
  wk->hSpr = 0;
}

// 0x1c323f0
static void elvMenuShutdown(dds3ProcessID_t *PID) {
  elvMenu_t *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  elvMenuRelease(ProcessData);
  elvMenu_g_mainPID = 0;
}

// 0x1c324f0
void elvMenuProcessStart(void) {
  elvMenu_t *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;

  v1 = Allocate(elvMenu_t);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_itf_elvMenuProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_itf_elvMenuShutdown__, 0);
  started = dds3StartProcess("kaisou_menu", 1023, 0, 0, v2, v3, v1);
  elvMenu_g_mainPID = started;
  v1->selectID = -2;
}

// 0x1c326a0
void elvMenuProcessEnd(void) {
  Il2CppObject *ProcessData;
  char klass;

  if (!elvMenu_g_mainPID)
    return;
  if (!dds3ExistProcess(elvMenu_g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(elvMenu_g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  klass = ProcessData[2].klass;
  if ((klass & 1) == 0)
  {
    WORD1(ProcessData[2].klass) = 0;
    LOBYTE(ProcessData[2].klass) = klass | 1;
    BYTE1(ProcessData[2].klass) = 2;
  }
}

// 0x1c32860
bool elvMenuProcessCheck(void) {
  if (!elvMenu_g_mainPID)
    return 0;
  if (dds3GetProcessStat(elvMenu_g_mainPID) != 3)
  {
    if (dds3GetProcessStat(elvMenu_g_mainPID))
    {
      return 1;
    }
  }
  elvMenu_g_mainPID = 0;
  return 0;
}

// 0x1c329d0
static s32 elvMenuMoverFunc(s32 mode) {
  void *setTitle;
  void *v12;
  char *v13;
  char *LocalizeText;

  if (op_Equality(elv, 0, 0))
    return 0;
  if (mode == 1)
  {
    MenuClose(elv, 0);
    MenuClose(elv_title, 0);
    ButtonGuideDispOff();
    return 1;
  }
  else
  {
    if (!mode)
    {
      setTitle = elv_title->setTitle;
      if ((setTitle->klass->vtable._65_get_text.methodPtr)(setTitle, setTitle->klass->vtable._65_get_text.method))
      {
        v12 = elv_title->setTitle;
        v13 = strKaisou[0];
        LocalizeText = GetLocalizeText(v13, 1);
        (v12->klass->vtable._66_set_text.methodPtr)(v12, LocalizeText, v12->klass->vtable._66_set_text.method);
      }
      MenuOpne(elv, 0);
      MenuOpne(elv_title, 0);
      ButtonGuideDispSet("FLD02", 0, 90);
      ButtonLineHelpDispSet(0);
    }
    return 1;
  }
}

// 0x1c32c80
static void frInitTextHandle(Text_t *pText, u16 Code, u8 Style, u8 ColNo, u32 Color, u8 Tp) {
  s32 col_no;
  il2cpp_array_size_t max_length;
  s32 v19;

  *(u64 *)&pText->ly = 0;
  pText->lx = 0;
  pText->color = Color & 0xFFFFFF00;
  pText->code = Code;
  pText->style = Style;
  pText->col_no = ColNo;
  pText->tp = Tp;
  pText->prev = 0;
  pText->draw_count = 0;
  pText->mode = gModeFlag;
  pText->next = 0;
  col_no = pText->col_no;
  max_length = ColorTbl->max_length;
  if (col_no >= (s32)max_length)
    v19 = 0;
  else
    v19 = col_no;
  pText->color = ColorTbl[v19] & 0xFFFFFF00;
}

// 0x1c32dd0
static void frInitFontHandle(FontReq_t *pFRQ) {
  FontReq_t *v2;

  v2 = pFRQ;
  pFRQ->space = 0;
  *(u64 *)&pFRQ->w_pxls = 0;
  *(u64 *)&pFRQ->x = 0;
  pFRQ->draw_spd = 0x80;
  pFRQ->prev = 0;
  v2->next = 0;
  v2->head = v2;
  v2->str = 0;
  v2->str_end = 0;
  v2 = ((char *)v2 + 56);
  HIDWORD(v2[-1].work) = 0;
}

// 0x1c32e50
static Text_t *frSetFont(u16 Code, u8 Style, u8 ColNo, u8 Tp) {
  Il2CppObject *v10;

  v10 = RentFrom_object_(&gFT->pTextRing);
  ++gFT->TextHandleNums;
  frInitTextHandle(v10, Code, Style, ColNo, 0xA09DC300, Tp);
  LOWORD(v10[3].klass) = 6168;
  v10[1].monitor = 0x1800000000LL;
  return (Text_t *)v10;
}

// 0x1c32f40
static u8 DisplaySpeed(void) {
  s32 v2;

  v2 = GetLanguageTYPE();
  if (v2)
  {
    return 255 / asiaDisplaySpeed;
  }
  return 255 / otherDisplaySpeed;
}

// 0x1c33040
s32 frDrawEffect(FontReq_t *pFRQ, Text_t *pText, u8 AlphaDelay, u8 DrawSpeed) {
  s32 v5;
  Text_t *prev;
  u32 color_low;
  FontReq_t *v11;
  Text_t *str_end;
  s32 tp;
  u32 *p_color;
  u32 color;
  _BOOL4 v16;
  u32 *tag_flag;
  s32 v18;
  u32 v19;
  s32 v20;
  bool v21;
  s32 wait;
  bool v23;
  s32 v24;
  char v25;
  u32 *v26;
  char v27;
  s32 v28;
  s32 v29;

  LOBYTE(v5) = DrawSpeed;
  prev = pText->prev;
  if (prev)
  {
    color_low = LOBYTE(prev->color);
LABEL_17:
    p_color = &pText->color;
    color = pText->color;
    goto LABEL_18;
  }
  v11 = pFRQ->prev;
  if (!v11 || (str_end = v11->str_end) == 0)
  {
    color_low = 128;
    goto LABEL_17;
  }
  color_low = LOBYTE(str_end->color);
  tp = str_end->tp;
  p_color = &pText->color;
  color = pText->color;
  if (!tp || tp == pText->tp)
  {
LABEL_18:
    v16 = color_low >= AlphaDelay;
    tag_flag = pText->tag_flag;
    v18 = (u8)color;
    v19 = tag_flag[0];
    if (v19 != 61973)
      goto LABEL_19;
    goto LABEL_10;
  }
  v16 = color_low == 128;
  tag_flag = pText->tag_flag;
  v18 = (u8)pText->color;
  v19 = tag_flag[0];
  if (v19 != 61973)
  {
LABEL_19:
    if (v19 != 61972)
      goto LABEL_26;
    wait = pText->wait;
    v23 = __OFSUB__(wait, 1);
    v24 = wait - 1;
    if (v24 < 0 != v23 || v18 != 128)
      goto LABEL_26;
LABEL_25:
    pText->wait = v24;
    goto LABEL_26;
  }
LABEL_10:
  v20 = pText->wait;
  if (v20 != 0xFFFF)
  {
    v23 = __OFSUB__(v20, 1);
    v24 = v20 - 1;
    if (v24 < 0 != v23)
      goto LABEL_26;
    v16 = 0;
    goto LABEL_25;
  }
  v21 = sndVoiceStatus(0);
  tag_flag = pText->tag_flag;
  if (v21)
    v16 = 0;
LABEL_26:
  if (tag_flag[2] != 61719)
  {
    v25 = 0;
    if (tag_flag[5] != 61979)
      goto LABEL_42;
    goto LABEL_35;
  }
  if (*p_color < 0x100)
  {
    v25 = 1;
    if (tag_flag[5] != 61979)
      goto LABEL_42;
    goto LABEL_35;
  }
  itfLipSyncParam(0);
  v26 = pText->tag_flag;
  v25 = 0;
  v26[2] = 0;
  if (v26[5] == 61979)
  {
LABEL_35:
    if (*p_color < 0x100)
      v27 = 1;
    else
      v27 = v25;
    if ((v27 & 1) == 0)
    {
      v28 = pFRQ->work[0];
      itfLipSyncParam(v28);
      pText->tag_flag[5] = 0;
    }
  }
LABEL_42:
  if (v16)
  {
    if ((v5 & 0x80) == 0)
      v5 = 22 * (u8)v5 / (pText->lw + pFRQ->space);
    if (128 - v18 < (u32)(u8)v5)
    {
      *p_color = color & 0xFFFFFF00 | 0x80;
      return 0;
    }
    v29 = *p_color + (u8)v5;
    *p_color = v29;
    if ((v29 & 0x80) != 0)
      return 0;
  }
  else if ((*p_color & 0x80) != 0)
  {
    return 0;
  }
  if (pText->tp == 1)
    return 32
         - 16
         * (2 * pText->draw_count - 5 * ((858993460 * (u64)(2 * (u32)pText->draw_count)) >> 32));
  return 0;
}

// 0x1c335f0
static s8 frEraseEffect(FontReq_t *pFRQ) {
  return 0;
}

// 0x1c33600
static FontReq_t *frAnalyzeMessageLocalize(frMsgInfo_t *pMsgInfo, bool spc, bool hitokoto, bool logmes) {
  u8 *pMsg;
  char *v12;
  void *v14;
  s32 v18;
  s32 *p_Ofs;
  s32 Ofs;
  u8 *v21;
  s32 v22;
  char v23;
  char *v24;
  s64 size;
  u64 *v27;
  s32 *items;
  char *v30;
  char *v31;
  s32 v33;
  char *v34;
  s32 v35;
  char *v36;
  char *v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 LanguageTYPE;
  char *v44;
  s32 v45;
  s32 stringLength;
  s32 v47;
  char v48;
  s32 v49;
  u16 Chars;
  u16 v52;
  char *v53;
  frMsgInfo_t *v57;
  s32 Y;
  f32 v61;
  s32 v62;
  s32 v63;
  FontReq_t *pFRQ;
  char *talk_tag;
  s16 v68;
  s32 font_id[2];
  char *message;
  frMsgInfo_t *mi;

  pMsg = pMsgInfo->pMsg;
  *(u64 *)font_id = 0;
  message = 0;
  v68 = 0;
  mi = pMsgInfo;
  if (pMsg[0] <= 0xEFu && pMsg[1] == 8)
    pMsgInfo->Ofs += 4;
  gMessageRequestResult &= 0xFFFFFFF0;
  gModeFlag |= 1u;
  v12 = "";
  message = "";
  gModeFlag &= ~2u;
  v14 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v14);
  Ofs = pMsgInfo->Ofs;
  p_Ofs = &pMsgInfo->Ofs;
  v18 = Ofs;
  v21 = *((u8 **)p_Ofs - 2);
  if (Ofs < SLODWORD(v21->max_length))
  {
    v22 = 0;
    v23 = 0;
    while (1)
    {
      while (1)
      {
        v33 = v18 + 1;
        v34 = (char *)v21 + v18;
        *p_Ofs = v33;
        v35 = (u8)v34[32];
        if (!v34[32])
        {
LABEL_39:
          v12 = message;
          if ((v23 & 1) != 0)
          {
            v12 = replace_space(v12);
            message = v12;
          }
          goto LABEL_44;
        }
        if ((~v35 & 0xF0) != 0)
          break;
        if ((v23 & 1) != 0)
        {
          v31 = message;
          message = replace_space(v31);
          if (frAnalyzeTagLocalize1(v35, mi, &message, v14))
          {
LABEL_43:
            v12 = message;
            goto LABEL_44;
          }
          goto LABEL_34;
        }
        else
        {
        }
        if (frAnalyzeTagLocalize1(v35, mi, &message, v14))
          goto LABEL_43;
LABEL_34:
        v23 = 0;
        v22 = 0;
        p_Ofs = &mi->Ofs;
        v18 = mi->Ofs;
        v21 = mi->pMsg;
        if (v18 >= SLODWORD(v21->max_length))
          goto LABEL_39;
      }
      if (!v22)
      {
        size = v14->_size;
        v27 = Method_System_Collections_Generic_List_int__Add__;
        ++v14->_version;
        items = v14->_items;
        if ((u32)size >= LODWORD(items->max_length))
        {
          _AddWithResize(v14, 0, *(const MethodInfo_2D8F530 **)(*(u64 *)(v27[4] + 192) + 112));
          v68 = v35;
          v30 = message;
          goto LABEL_18;
        }
        v14->_size = size + 1;
        items[size] = 0;
      }
      v68 = v35;
      v30 = message;
LABEL_18:
      v24 = ToString((u16)&v68, 0);
      ++v22;
      message = Concat_54766928(v30, v24, 0);
      v23 = (v35 != 62) & ((v35 == 60) | v23);
      p_Ofs = &mi->Ofs;
      v18 = mi->Ofs;
      v21 = mi->pMsg;
      if (v18 >= SLODWORD(v21->max_length))
        goto LABEL_39;
    }
  }
LABEL_44:
  v36 = frReplaceLocalizeText(v12, mi, v14);
  message = v36;
  if (hitokoto)
  {
    v36 = Replace_54838864(v36, "<MW90>", "", 0);
    message = v36;
  }
  v37 = Replace_54838864(v36, "<MW", "<mw", 0);
  message = v37;
  if (logmes)
  {
    v38 = IndexOf_54852384(v37, "<mw", 0);
    if (v38 >= 1)
    {
      v39 = v38;
      v40 = IndexOf_54852400(message, ">", v38, 0);
      message = Remove(message, v39, v40 - v39 + 1, 0);
    }
  }
  if (drawEnd)
    goto LABEL_71;
  if (TitleProcessCheck())
    goto LABEL_71;
  if (!IsNullOrEmpty(message, 0) && !Contains(message, "<mw", 0))
    message = Concat_54766928(message, "<mw90>", 0);
  if (GetLanguageTYPE())
    goto LABEL_71;
  if (Equals_54828784(mi->talk_tag, "<E696_001_L0003>", 0))
    message = Replace_54838864(message, "<mw80>", "<mw80>\n", 0);
LABEL_71:
  if (Equals_54828784(mi->talk_tag, "<MAP09_E_L0036>", 0))
  {
    message = Replace_54838864(message, "<mw170>", "<mw240>", 0);
LABEL_73:
    LanguageTYPE = GetLanguageTYPE();
    v44 = message;
    if (LanguageTYPE)
      goto LABEL_81;
LABEL_77:
    if (!hitokoto)
    {
      v44 = Convert(v44, spc, -1, -1.0);
      message = v44;
    }
    goto LABEL_81;
  }
  else
  {
    goto LABEL_73;
  }
  v45 = GetLanguageTYPE();
  v44 = message;
  if (!v45)
    goto LABEL_77;
LABEL_81:
  stringLength = v44->_stringLength;
  *(u64 *)font_id = 0;
  if (stringLength < 1)
    goto LABEL_112;
  v47 = 0;
  v48 = 0;
  do
  {
    while (1)
    {
      Chars = get_Chars(message, v47, 0);
      if (Chars == 10)
        break;
      v52 = Chars;
      if (Chars == 60)
      {
        font_id[1] = 0;
        v53 = message;
        if (frAnalyzeTagLocalize2(message, font_id, mi, &font_id[1]))
          goto LABEL_96;
      }
      v49 = font_id[1];
      MessageCreateHandle(mi, v52, v49);
      v47 = font_id[0];
      v48 = 0;
      goto LABEL_86;
LABEL_96:
      v47 = font_id[0];
      v48 = 1;
      if (font_id[0] >= stringLength)
        goto LABEL_109;
    }
    if ((gModeFlag & 4) == 0)
      goto LABEL_86;
    v57 = mi;
    Y = v57->Y;
    *(u16 *)&v57->FrqFlag = 257;
    v61 = (f32)gMessageStepY * 2.25;
    v62 = 8 * (s32)v61;
    if (v61 == INFINITY)
      v62 = 0;
    v57->Y = v62 + Y;
LABEL_86:
    font_id[0] = ++v47;
  }
  while (v47 < stringLength);
  if ((v48 & 1) == 0)
    goto LABEL_112;
LABEL_109:
  v63 = font_id[1];
  MessageCreateHandle(mi, 0x20u, v63);
LABEL_112:
  pFRQ = mi->pFRQ;
  if (pFRQ)
  {
    talk_tag = mi->talk_tag;
    pFRQ->tag_id = talk_tag;
  }
  goto LABEL_116;
LABEL_117:
  gModeFlag &= ~1u;
  goto LABEL_118;
LABEL_116:
  goto LABEL_117;
LABEL_118:
  gModeFlag |= 2u;
  return mi->pFRQ;
}

// 0x1c39ba0
static void MessageCreateHandle(frMsgInfo_t *mi, u16 chcode, s32 font_id) {
  frMsgInfo_t *v7;
  FontReq_t *p_pFRQ;
  FontReq_t *v10;
  FontReq_t *pFRQ;
  Text_t *str_end;
  u32 *tag_flag;

  v7 = mi;
  frCreateNewHandle(v7);
  p_pFRQ = &mi->pFRQ;
  v10 = frSetFontStringLocalize(chcode, mi->Style, mi->ColNo, mi->Tp, p_pFRQ);
  p_pFRQ = v10;
  pFRQ = mi->pFRQ;
  str_end = pFRQ->str_end;
  tag_flag = str_end->tag_flag;
  if ((s32)tag_flag->max_length >= 1)
    sub_188E3B0(tag_flag, 0, 4 * (u32)tag_flag->max_length);
  *(u64 *)&str_end->wait = 0;
  pFRQ->local = 1;
  if (font_id)
    pFRQ->str->font_id = font_id;
}

// 0x1c34130
static char *replace_space(char *message) {
  s32 IndexOf_54854512;
  char *v4;
  char *v5;
  char *result;
  char *v7;
  char *v8;

  IndexOf_54854512 = LastIndexOf_54854512(message, "<", 0);
  v4 = Substring_54838176(message, IndexOf_54854512, message->_stringLength - IndexOf_54854512, 0);
  v5 = Replace_54838864(v4, " ", "", 0);
  result = Concat_54766928(v5, ">", 0);
  v7 = result;
  if (IndexOf_54854512 >= 1)
  {
    v8 = Substring_54838176(message, 0, IndexOf_54854512 - 1, 0);
    return Concat_54766928(v8, v7, 0);
  }
  return result;
}

// 0x1c39db0
static FontReq_t *frSetFontStringLocalize(u16 pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ) {
  FontReq_t *v6;
  Text_t *p_str_end;
  Text_t *str_end;
  Text_t *v15;
  Text_t *p_next;
  s32 w_pxls;
  s32 lw;
  Il2CppObject *v20;

  v6 = pFRQ;
  frSetFontString_style = 0;
  if (Style < 0)
    goto LABEL_4;
  frSetFontString_style = Style;
  if (!v6)
    goto LABEL_17;
LABEL_5:
  p_str_end = &v6->str_end;
  str_end = v6->str_end;
  goto LABEL_7;
LABEL_4:
  if (v6)
    goto LABEL_5;
LABEL_17:
  v20 = RentFrom_object_(&gFT->pRequestRing);
  v6 = (FontReq_t *)v20;
  LOBYTE(v20[1].klass) = 0x80;
  BYTE2(v20[1].klass) = 0;
  ++gFT->FontHandleNums;
  *(void **)((char *)&v20[1].monitor + 4) = 0;
  *(Il2CppClass **)((char *)&v20[2].klass + 4) = 0;
  v20[4].monitor = 0;
  v6->next = 0;
  v6->head = v6;
  v6->str = 0;
  v6->str_end = 0;
  v6->strlen = 0;
  p_str_end = &v6->str_end;
  str_end = v6->str_end;
LABEL_7:
  v15 = frSetFont(0x8000u, frSetFontString_style, ColNo, Tp);
  if (str_end)
    p_next = &str_end->next;
  else
    p_next = &v6->str;
  p_next = v15;
  v15->chcode = pStr;
  v15->prev = str_end;
  w_pxls = v6->w_pxls;
  lw = v15->lw;
  v6->str_end = v15;
  v6->w_pxls = lw + w_pxls;
  ++v6->strlen;
  v6->x_size = v15->width;
  v6->y_size = v15->height;
  return v6;
}

// 0x1c34250
static bool frAnalyzeTagLocalize1(s32 code, frMsgInfo_t *mi, char **message, void *index) {
  frMsgInfo_t *v9;
  s64 Ofs;
  u8 *pMsg;
  s32 v12;
  s32 v13;
  u64 *v14;
  s64 v15;
  s32 *v16;
  frMsgInfo_t *v17;
  u64 *v18;
  s64 size;
  s32 *items;
  u64 *v21;
  s64 v22;
  s32 *v23;
  u64 *v24;
  s64 v25;
  s32 *v26;
  char *v28;
  char **v29;
  u64 *v30;
  s64 v31;
  s32 *v32;
  char *v33;
  u64 *v34;
  s64 v35;
  s64 v36;
  s64 v37;
  char *v38;
  char *v39;
  char **v40;
  char *v41;
  char *v43;
  char *v44;
  s64 v45;
  s32 v46;
  char *v47;
  Il2CppObject *v48;
  char **v49;
  s64 v52;
  char *v53;
  char *v54;
  s64 v55;
  s32 v56;
  char *v57;
  s64 v58;
  s32 v59;
  char *v60;
  s64 v61;
  s32 v62;
  char *v63;
  char *v64;
  char *v65;
  char v66[4];
  char v67[4];
  char data[4];
  char v69[4];

  v9 = mi;
  Ofs = mi->Ofs;
  pMsg = mi->pMsg;
  v12 = Ofs + 1;
  mi->Ofs = Ofs + 1;
  v13 = pMsg[Ofs] | (code << 8);
  if (v13 > 61722)
  {
    if ((u32)v13 <= 0xF413)
    {
      switch (v13)
      {
        case 61954:
          sub_91E0(index, 0xFFFFFFFFLL);
          v44 = *message;
          v45 = mi->Ofs;
          v46 = v45 + 1;
          v47 = (char *)(mi)->pMsg + v45;
          mi->Ofs = v46;
          data[0] = v47[32];
          v48 = Box(*off_4EE5828, data);
          v49 = &"<COLOR {0}>";
          break;
        case 61955:
          v9 = mi;
          pMsg = mi->pMsg;
          v12 = mi->Ofs;
          v52 = pMsg[v12] - 1;
          if (gVarStr[v52])
          {
            v52 = mi->pMsg[mi->Ofs] - 1;
            v53 = itfNumConv(gVarStr[v52]);
            v54 = Concat_54766928(*message, v53, 0);
            *message = v54;
            v9 = mi;
            v12 = mi->Ofs;
          }
          v9->Ofs = v12 + 2;
          v17 = mi;
          if (!mi->FrqFlag)
            goto LABEL_68;
          return 0;
        case 61956:
        case 61957:
        case 61960:
        case 61967:
        case 61968:
        case 61969:
        case 61970:
        case 61971:
        case 61974:
        case 61975:
        case 61977:
        case 61978:
          goto LABEL_47;
        case 61958:
          sub_91E0(index, 0xFFFFFFFFLL);
          v44 = *message;
          v55 = mi->Ofs;
          v56 = v55 + 1;
          v57 = (char *)(mi)->pMsg + v55;
          mi->Ofs = v56;
          v69[0] = v57[32];
          v48 = Box(*off_4EE5828, v69);
          v49 = &"<FONT {0}>";
          break;
        case 61959:
          sub_91E0(index, 0xFFFFFFFFLL);
          v44 = *message;
          v58 = mi->Ofs;
          v59 = v58 + 1;
          v60 = (char *)(mi)->pMsg + v58;
          mi->Ofs = v59;
          v66[0] = v60[32];
          v48 = Box(*off_4EE5828, v66);
          v49 = &"<SPD {0}>";
          break;
        case 61961:
          sub_91E0(index, 0xFFFFFFFFLL);
          v44 = *message;
          v61 = mi->Ofs;
          v62 = v61 + 1;
          v63 = (char *)(mi)->pMsg + v61;
          mi->Ofs = v62;
          v67[0] = v63[32];
          v48 = Box(*off_4EE5828, v67);
          v49 = &"<TP {0}>";
          break;
        case 61962:
        case 61963:
        case 61964:
        case 61965:
          v9->Ofs = Ofs + 3;
          v17 = mi;
          if (!mi->FrqFlag)
            goto LABEL_68;
          return 0;
        case 61966:
          v9->Ofs = Ofs + 2;
          v17 = mi;
          if (!mi->FrqFlag)
            goto LABEL_68;
          return 0;
        case 61972:
        case 61973:
        case 61976:
        case 61979:
          goto LABEL_46;
        default:
          if (v13 == 62483)
            goto LABEL_46;
          goto LABEL_47;
      }
      v64 = Format(*v49, v48, 0);
      v65 = Concat_54766928(v44, v64, 0);
      *message = v65;
    }
    else
    {
      if (v13 != 62486 && v13 != 62489)
      {
LABEL_47:
        v9->Ofs = 2 * (code & 0xF) + v12 - 2;
        v17 = mi;
        if (!mi->FrqFlag)
          goto LABEL_68;
        return 0;
      }
LABEL_14:
      v18 = Method_System_Collections_Generic_List_int__Add__;
      size = index->_size;
      ++index->_version;
      items = index->_items;
      if ((u32)size < LODWORD(items->max_length))
      {
        index->_size = size + 1;
        items[size] = -1;
        goto LABEL_67;
      }
      _AddWithResize(index, -1, *(const MethodInfo_2D8F530 **)(*(u64 *)(v18[4] + 192) + 112));
    }
LABEL_66:
    v9 = mi;
LABEL_67:
    ++v9->Ofs;
    v17 = mi;
    if (!mi->FrqFlag)
    {
LABEL_68:
      v17->FrqFlag = 1;
      return 0;
    }
    return 0;
  }
  switch (v13)
  {
    case 61700:
      v14 = Method_System_Collections_Generic_List_int__Add__;
      v15 = index->_size;
      ++index->_version;
      v16 = index->_items;
      if ((u32)v15 >= LODWORD(v16->max_length))
      {
        _AddWithResize(index, -1, *(const MethodInfo_2D8F530 **)(*(u64 *)(v14[4] + 192) + 112));
      }
      else
      {
        index->_size = v15 + 1;
        v16[v15] = -1;
      }
      v33 = *message;
      v34 = Method_System_Array_Empty_object___;
      v35 = *((u64 *)Method_System_Array_Empty_object___ + 7);
      if (v35)
      {
        v36 = *(u64 *)(v35 + 16);
        if ((*(u16 *)(v36 + 309) & 1) != 0)
          goto LABEL_30;
      }
      else
      {
        sub_42271C();
        v36 = *(u64 *)(v34[7] + 16);
        if ((*(u16 *)(v36 + 309) & 1) != 0)
        {
LABEL_30:
          if (*(u32 *)(v36 + 224))
            goto LABEL_31;
          goto LABEL_51;
        }
      }
      v36 = sub_42269C(v36);
      if (*(u32 *)(v36 + 224))
      {
LABEL_31:
        v37 = *(u64 *)(v34[7] + 16);
        if ((*(u16 *)(v37 + 309) & 1) != 0)
          goto LABEL_33;
        goto LABEL_32;
      }
LABEL_51:
      v37 = *(u64 *)(v34[7] + 16);
      if ((*(u16 *)(v37 + 309) & 1) == 0)
LABEL_32:
        v37 = sub_42269C(v37);
LABEL_33:
      v38 = Format_54833568("<WAIT>", **(void ***)(v37 + 184), 0);
      v28 = v33;
LABEL_39:
      v41 = Concat_54766928(v28, v38, 0);
      *message = v41;
      return 1;
    case 61711:
      v21 = Method_System_Collections_Generic_List_int__Add__;
      v22 = index->_size;
      ++index->_version;
      v23 = index->_items;
      if ((u32)v22 >= LODWORD(v23->max_length))
      {
        _AddWithResize(index, -1, *(const MethodInfo_2D8F530 **)(*(u64 *)(v21[4] + 192) + 112));
      }
      else
      {
        index->_size = v22 + 1;
        v23[v22] = -1;
      }
      v39 = *message;
      v40 = &"<RET>";
      goto LABEL_42;
    case 61712:
      v24 = Method_System_Collections_Generic_List_int__Add__;
      v25 = index->_size;
      ++index->_version;
      v26 = index->_items;
      if ((u32)v25 >= LODWORD(v26->max_length))
      {
        _AddWithResize(index, -1, *(const MethodInfo_2D8F530 **)(*(u64 *)(v24[4] + 192) + 112));
      }
      else
      {
        index->_size = v25 + 1;
        v26[v25] = -1;
      }
      v28 = *message;
      v29 = &"<NWAIT>";
      goto LABEL_38;
    case 61713:
      if ((gModeFlag & 8) == 0)
        goto LABEL_43;
      sub_91E0(index, 0xFFFFFFFFLL);
      v28 = *message;
      v29 = &"\n";
LABEL_38:
      v38 = *v29;
      goto LABEL_39;
    case 61714:
      v30 = Method_System_Collections_Generic_List_int__Add__;
      v31 = index->_size;
      ++index->_version;
      v32 = index->_items;
      if ((u32)v31 >= LODWORD(v32->max_length))
      {
        _AddWithResize(index, -1, *(const MethodInfo_2D8F530 **)(*(u64 *)(v30[4] + 192) + 112));
      }
      else
      {
        index->_size = v31 + 1;
        v32[v31] = -1;
      }
      v39 = *message;
      v40 = &"<KUTI>";
LABEL_42:
      v43 = Concat_54766928(v39, *v40, 0);
      *message = v43;
LABEL_43:
      v17 = mi;
      if (mi->FrqFlag)
        return 0;
      goto LABEL_68;
    case 61719:
      goto LABEL_14;
    case 61722:
LABEL_46:
      sub_91E0(index, 0xFFFFFFFFLL);
      goto LABEL_66;
    default:
      goto LABEL_47;
  }
}

// 0x1c3a000
char *itfNumConv(char *s) {
  char *v3;
  s32 v4;
  char *v5;
  s32 LanguageTYPE;
  void *_9__146_2;
  char *v10;
  Il2CppObject *v15;
  void *p__9__146_2;
  Il2CppObject *v18;
  Il2CppObject *v20;

  v3 = "";
  if (s->_stringLength >= 1 && get_Chars(s, 0, 0) == 60)
  {
    v4 = IndexOf_54850576(s, 0x3Eu, 0, 0) + 1;
    v3 = Substring_54838176(s, 0, v4, 0);
    s = Substring(s, v4, 0);
  }
  v5 = "";
  LanguageTYPE = GetLanguageTYPE();
  if (LanguageTYPE == 2)
  {
    _9__146_2 = __9__146_2;
    v10 = "[0-9]";
    if (_9__146_2)
      goto LABEL_33;
    v18 = __9;
    _9__146_2 = Allocate(System_Text_RegularExpressions_MatchEvaluator);
    _ctor(_9__146_2, v18, Method_Project_itf___c__NumConv_b__146_2__, 0);
    __9__146_2 = _9__146_2;
    p__9__146_2 = &__9__146_2;
    goto LABEL_32;
  }
  if (LanguageTYPE == 1)
  {
    _9__146_2 = __9__146_1;
    v10 = "[0-9]";
    if (_9__146_2)
      goto LABEL_33;
    v20 = __9;
    _9__146_2 = Allocate(System_Text_RegularExpressions_MatchEvaluator);
    _ctor(_9__146_2, v20, Method_Project_itf___c__NumConv_b__146_1__, 0);
    __9__146_1 = _9__146_2;
    p__9__146_2 = &__9__146_1;
    goto LABEL_32;
  }
  if (LanguageTYPE)
    return Concat_54766928(v3, v5, 0);
  _9__146_2 = __9__146_0;
  v10 = "[0-9]";
  if (!_9__146_2)
  {
    v15 = __9;
    _9__146_2 = Allocate(System_Text_RegularExpressions_MatchEvaluator);
    _ctor(_9__146_2, v15, Method_Project_itf___c__NumConv_b__146_0__, 0);
    __9__146_0 = _9__146_2;
    p__9__146_2 = &__9__146_0;
LABEL_32:
  }
LABEL_33:
  v5 = Replace_56923968(s, v10, _9__146_2, 0);
  return Concat_54766928(v3, v5, 0);
}

// 0x1c35370
static bool frAnalyzeTagLocalize2(char *message, s32 *index, frMsgInfo_t *mi, s32 *font_id) {
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  char *v13;
  char *v14;
  char *v15;
  char *v16;
  bool v17;
  char *v18;
  s32 v19;
  s32 v21;
  s64 v23;
  char *BtnList_local;
  s64 v26;
  char *BstList_local;
  s64 v29;
  char *IcnList_local;
  s64 v32;
  char *SkilList_local;
  s64 v35;
  char *DependentList_local;
  s64 v38;
  char *MenuList_local;
  s64 v41;
  char *RaiSkilList_local;
  bool v44;
  s64 v46;
  char *ItemList_local;
  u32 v49;
  FontReq_t *v51;
  s32 v52;
  FontReq_t *v53;
  FontReq_t *v54;
  FontReq_t *v55;
  FontReq_t *v56;
  FontReq_t *v57;
  FontReq_t *v58;
  FontReq_t *v59;
  FontReq_t *v61;
  FontReq_t *v62;
  FontReq_t *v63;
  FontReq_t *v64;
  FontReq_t *v65;
  FontReq_t *v66;
  FontReq_t *v67;
  FontReq_t *v68;
  FontReq_t *v69;
  FontReq_t *v70;
  FontReq_t *v71;
  FontReq_t *v72;
  FontReq_t *v73;
  FontReq_t *v74;
  FontReq_t *v75;
  FontReq_t *v76;
  FontReq_t *v77;
  FontReq_t *v78;
  FontReq_t *v79;
  FontReq_t *v80;
  FontReq_t *v81;
  FontReq_t *v82;
  FontReq_t *v83;
  FontReq_t *v84;
  FontReq_t *v85;
  FontReq_t *v86;
  FontReq_t *v87;
  FontReq_t *v88;
  FontReq_t *v89;
  FontReq_t *v90;
  frMsgInfo_t *v93;
  FontReq_t *v94;
  FontReq_t *v95;
  FontReq_t *v96;
  FontReq_t *v97;
  FontReq_t *v98;
  FontReq_t *v99;
  FontReq_t *v102;
  FontReq_t *v103;
  FontReq_t *v104;
  FontReq_t *v105;
  FontReq_t *v106;
  frMsgInfo_t *v107;
  char v109;
  FontReq_t *v110;
  FontReq_t *v111;
  FontReq_t *v112;
  FontReq_t *v113;
  FontReq_t *v114;
  FontReq_t *v115;
  FontReq_t *v116;
  FontReq_t *v117;
  FontReq_t *v118;
  FontReq_t *v120;
  FontReq_t *v121;
  FontReq_t *v122;
  FontReq_t *v123;
  FontReq_t *v124;
  FontReq_t *v125;
  FontReq_t *v126;
  FontReq_t *v127;
  FontReq_t *v128;
  FontReq_t *v129;
  FontReq_t *v130;
  FontReq_t *v131;
  FontReq_t *v132;
  FontReq_t *v133;
  FontReq_t *v134;
  FontReq_t *v135;
  FontReq_t *v136;
  FontReq_t *v137;
  FontReq_t *v138;
  FontReq_t *v139;
  FontReq_t *v140;
  FontReq_t *v141;
  FontReq_t *v142;
  FontReq_t *v143;
  FontReq_t *v144;
  FontReq_t *v145;
  FontReq_t *v146;
  FontReq_t *v147;
  FontReq_t *v148;
  FontReq_t *v149;
  FontReq_t *v150;
  FontReq_t *v151;
  FontReq_t *v152;
  FontReq_t *v153;
  FontReq_t *v154;
  FontReq_t *v155;
  FontReq_t *v156;
  FontReq_t *v158;
  FontReq_t *v159;
  Text_t *v160;
  FontReq_t *v161;
  FontReq_t *v162;
  FontReq_t *v163;
  FontReq_t *v164;
  FontReq_t *v165;
  FontReq_t *v166;
  FontReq_t *v167;
  FontReq_t *v168;
  FontReq_t *v169;
  FontReq_t *v170;
  Text_t *v171;
  FontReq_t *v172;
  FontReq_t *v173;
  FontReq_t *v174;
  FontReq_t *v175;
  FontReq_t *v176;
  FontReq_t *v177;
  FontReq_t *v178;
  FontReq_t *v179;
  FontReq_t *v180;
  FontReq_t *v181;
  FontReq_t *v182;
  FontReq_t *v183;
  FontReq_t *v184;
  Text_t *str_end;
  FontReq_t *v187;
  FontReq_t *v188;
  FontReq_t *v189;
  FontReq_t *v190;
  FontReq_t *v191;
  FontReq_t *pFRQ;
  FontReq_t *v193;
  s32 v194;
  s32 v195;
  frMsgInfo_t *mia;
  s32 v197;
  s32 result;

  v9 = *index;
  v197 = 0;
  result = -1;
  v10 = IndexOf_54850576(message, 0x3Eu, v9, 0);
  if (v10 == -1)
    return 0;
  v11 = v10;
  v12 = v10 - *index;
  if (v12 - 3 < 0)
    return 0;
  mia = mi;
  v13 = Substring_54838176(message, *index + 3, v12 - 3, 0);
  v14 = Substring_54838176(message, *index, 3, 0);
  if (op_Equality(v14, "<li", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    if ((IndexOf_54852384(v14, "<lips_stop", 0) & 0x80000000) == 0)
    {
      v13 = "0";
      goto LABEL_18;
    }
    v15 = Split(v14, 0x20u, 0, 0);
    v16 = Substring_54838176(v15[1], 0, 1, 0);
    v17 = op_Equality(v16, "0", 0);
    v18 = v15[1];
    if (v17)
    {
      v19 = ToInt32_55009392(v18, 16, 0);
      goto LABEL_15;
    }
    else
    {
      v19 = Parse(v15[1], 0);
LABEL_15:
      gLipsTarget = v19;
      v21 = Parse(v15[2], 0);
      v13 = "0";
      gLipsType = v21;
      v14 = Substring_54838176(message, *index, 5, 0);
      goto LABEL_18;
    }
    goto LABEL_15;
  }
LABEL_18:
  if (op_Equality(v14, "<IT", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    if (IndexOf_54852384(v14, "<IT_S", 0) < 0 && IndexOf_54852384(v14, "<IT_E", 0) < 0)
    {
      v46 = 4;
      while (1)
      {
        ItemList_local = ItemList;
        if (v46 - 4 >= SLODWORD(ItemList_local->max_length))
          break;
        ItemList_local = ItemList;
        if (Equals_54828784(v14, *((char **)&ItemList_local->obj.klass + v46), 0))
        {
          v197 = v46 - 3;
          v13 = ToString((s32)&v197, 0);
          break;
        }
        ++v46;
      }
    }
    else
    {
      v13 = "0";
    }
  }
  if (op_Equality(v14, "<NB", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    if (IndexOf_54852384(v14, "<NBSP", 0) >= 0)
      v13 = "0";
  }
  if (op_Equality(v14, "<BT", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    v23 = 4;
    while (1)
    {
      BtnList_local = BtnList;
      if (v23 - 4 >= SLODWORD(BtnList_local->max_length))
        break;
      BtnList_local = BtnList;
      if (Equals_54828784(v14, *((char **)&BtnList_local->obj.klass + v23), 0))
      {
        v197 = v23 - 3;
        v13 = ToString((s32)&v197, 0);
        break;
      }
      ++v23;
    }
  }
  if (op_Equality(v14, "<BS", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    v26 = 4;
    while (1)
    {
      BstList_local = BstList;
      if (v26 - 4 >= SLODWORD(BstList_local->max_length))
        break;
      BstList_local = BstList;
      if (Equals_54828784(v14, *((char **)&BstList_local->obj.klass + v26), 0))
      {
        v197 = v26 - 3;
        v13 = ToString((s32)&v197, 0);
        break;
      }
      ++v26;
    }
  }
  if (op_Equality(v14, "<IC", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    v29 = 4;
    while (1)
    {
      IcnList_local = IcnList;
      if (v29 - 4 >= SLODWORD(IcnList_local->max_length))
        break;
      IcnList_local = IcnList;
      if (Equals_54828784(v14, *((char **)&IcnList_local->obj.klass + v29), 0))
      {
        v197 = v29 - 3;
        v13 = ToString((s32)&v197, 0);
        break;
      }
      ++v29;
    }
  }
  if (op_Equality(v14, "<SK", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    v32 = 4;
    while (1)
    {
      SkilList_local = SkilList;
      if (v32 - 4 >= SLODWORD(SkilList_local->max_length))
        break;
      SkilList_local = SkilList;
      if (Equals_54828784(v14, *((char **)&SkilList_local->obj.klass + v32), 0))
      {
        v197 = v32 - 3;
        v13 = ToString((s32)&v197, 0);
        break;
      }
      ++v32;
    }
  }
  if (op_Equality(v14, "<DE", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    v35 = 4;
    while (1)
    {
      DependentList_local = DependentList;
      if (v35 - 4 >= SLODWORD(DependentList_local->max_length))
        break;
      DependentList_local = DependentList;
      if (Equals_54828784(v14, *((char **)&DependentList_local->obj.klass + v35), 0))
      {
        v197 = v35 - 3;
        v13 = ToString((s32)&v197, 0);
        break;
      }
      ++v35;
    }
  }
  if (op_Equality(v14, "<MN", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    v38 = 4;
    while (1)
    {
      MenuList_local = MenuList;
      if (v38 - 4 >= SLODWORD(MenuList_local->max_length))
        break;
      MenuList_local = MenuList;
      if (Equals_54828784(v14, *((char **)&MenuList_local->obj.klass + v38), 0))
      {
        v197 = v38 - 3;
        v13 = ToString((s32)&v197, 0);
        break;
      }
      ++v38;
    }
  }
  if (op_Equality(v14, "<RA", 0))
  {
    v14 = Substring_54838176(message, *index, v12, 0);
    v41 = 4;
    while (1)
    {
      RaiSkilList_local = RaiSkilList;
      if (v41 - 4 >= SLODWORD(RaiSkilList_local->max_length))
        break;
      RaiSkilList_local = RaiSkilList;
      if (Equals_54828784(v14, *((char **)&RaiSkilList_local->obj.klass + v41), 0))
      {
        v197 = v41 - 3;
        v13 = ToString((s32)&v197, 0);
        if (!IsNullOrEmpty(v13, 0))
          goto LABEL_101;
        goto LABEL_104;
      }
      ++v41;
    }
  }
  if (!IsNullOrEmpty(v13, 0))
  {
LABEL_101:
    if (!TryParse(v13, &result, 0))
      return 0;
  }
LABEL_104:
  if (result == -1)
  {
    if (op_Equality(v14, "<FO", 0) || op_Equality(v14, "<CO", 0) || op_Equality(v14, "<TP", 0) || op_Equality(v14, "<SP", 0))
    {
      return 0;
    }
  }
  else if (op_Equality(v14, "<WA", 0) || op_Equality(v14, "<RE", 0) || op_Equality(v14, "<NW", 0) || op_Equality(v14, "<AD", 0) || op_Equality(v14, "<KU", 0))
  {
    return 0;
  }
  *index = v11 + 1;
  v49 = _ComputeStringHash(v14, 0);
  if (v49 > 0x75A1C534)
  {
    if (v49 > 0xA1128BE7)
    {
      if (v49 > 0xC5A9F014)
      {
        if (v49 > 0xFA9761C6)
        {
          if (v49 > 0xFC99A383)
          {
            if (v49 > 0xFD99A516)
            {
              if (v49 == -23631854)
              {
                if (op_Equality(v14, "<BST_16", 0))
                {
                  pFRQ = mi->pFRQ;
                  if (pFRQ && !mi->FrqFlag)
                    pFRQ->str_end->font_id = 52;
                  else
                    *font_id = 52;
                  goto LABEL_889;
                }
              }
              else if (v49 == -6854235)
              {
                if (op_Equality(v14, "<BST_17", 0))
                {
                  v193 = mi->pFRQ;
                  if (v193 && !mi->FrqFlag)
                    v193->str_end->font_id = 53;
                  else
                    *font_id = 53;
                  goto LABEL_889;
                }
              }
              else if (v49 == -6707140 && op_Equality(v14, "<BST_07", 0))
              {
                v117 = mi->pFRQ;
                if (v117 && !mi->FrqFlag)
                  v117->str_end->font_id = 43;
                else
                  *font_id = 43;
                goto LABEL_889;
              }
            }
            else if (v49 == -40409473)
            {
              if (op_Equality(v14, "<BST_15", 0))
              {
                v148 = mi->pFRQ;
                if (v148 && !mi->FrqFlag)
                  v148->str_end->font_id = 51;
                else
                  *font_id = 51;
                goto LABEL_889;
              }
            }
            else if (v49 == -40262378 && op_Equality(v14, "<BST_01", 0))
            {
              v83 = mi->pFRQ;
              if (v83 && !mi->FrqFlag)
                v83->str_end->font_id = 37;
              else
                *font_id = 37;
              goto LABEL_889;
            }
          }
          else if (v49 > 0xFB99A1F0)
          {
            if (v49 == -57187092)
            {
              if (op_Equality(v14, "<BST_14", 0))
              {
                v165 = mi->pFRQ;
                if (v165 && !mi->FrqFlag)
                  v165->str_end->font_id = 50;
                else
                  *font_id = 50;
                goto LABEL_889;
              }
            }
            else if (v49 == -57039997 && op_Equality(v14, "<BST_02", 0))
            {
              v99 = mi->pFRQ;
              if (v99 && !mi->FrqFlag)
                v99->str_end->font_id = 38;
              else
                *font_id = 38;
              goto LABEL_889;
            }
          }
          else if (v49 == -73964711)
          {
            if (op_Equality(v14, "<BST_13", 0))
            {
              v132 = mi->pFRQ;
              if (v132 && !mi->FrqFlag)
                v132->str_end->font_id = 49;
              else
                *font_id = 49;
              goto LABEL_889;
            }
          }
          else if (v49 == -73817616 && op_Equality(v14, "<BST_03", 0))
          {
            v67 = mi->pFRQ;
            if (v67 && !mi->FrqFlag)
              v67->str_end->font_id = 39;
            else
              *font_id = 39;
            goto LABEL_889;
          }
        }
        else if (v49 > 0xE37630A2)
        {
          if (v49 > 0xEB763D3A)
          {
            if (v49 == -124297568)
            {
              if (op_Equality(v14, "<BST_10", 0))
              {
                v176 = mi->pFRQ;
                if (v176 && !mi->FrqFlag)
                  v176->str_end->font_id = 46;
                else
                  *font_id = 46;
                goto LABEL_889;
              }
            }
            else if (v49 == -107519949)
            {
              if (op_Equality(v14, "<BST_11", 0))
              {
                v177 = mi->pFRQ;
                if (v177 && !mi->FrqFlag)
                  v177->str_end->font_id = 47;
                else
                  *font_id = 47;
                goto LABEL_889;
              }
            }
            else if (v49 == -90742330 && op_Equality(v14, "<BST_12", 0))
            {
              v110 = mi->pFRQ;
              if (v110 && !mi->FrqFlag)
                v110->str_end->font_id = 48;
              else
                *font_id = 48;
              goto LABEL_889;
            }
          }
          else if (v49 == -378569137)
          {
            if (op_Equality(v14, "<BTN_AL", 0))
            {
              v140 = mi->pFRQ;
              if (v140 && !mi->FrqFlag)
                v140->str_end->font_id = 22;
              else
                *font_id = 22;
              goto LABEL_889;
            }
          }
          else if (v49 == -344572614 && op_Equality(v14, "<BTN_DL", 0))
          {
            v75 = mi->pFRQ;
            if (v75 && !mi->FrqFlag)
              v75->str_end->font_id = 35;
            else
              *font_id = 35;
            goto LABEL_889;
          }
        }
        else if (v49 > 0xD4761905)
        {
          if (v49 == -546345327)
          {
            if (op_Equality(v14, "<BTN_AR", 0))
            {
              v156 = mi->pFRQ;
              if (v156 && !mi->FrqFlag)
                v156->str_end->font_id = 27;
              else
                *font_id = 27;
              goto LABEL_889;
            }
          }
          else if (v49 == -478793566 && op_Equality(v14, "<BTN_DD", 0))
          {
            v90 = mi->pFRQ;
            if (v90 && !mi->FrqFlag)
              v90->str_end->font_id = 34;
            else
              *font_id = 34;
            goto LABEL_889;
          }
        }
        else if (v49 == -847901184)
        {
          if (op_Equality(v14, "<BTN_DR", 0))
          {
            v125 = mi->pFRQ;
            if (v125 && !mi->FrqFlag)
              v125->str_end->font_id = 36;
            else
              *font_id = 36;
            goto LABEL_889;
          }
        }
        else if (v49 == -730457851 && op_Equality(v14, "<BTN_DU", 0))
        {
          v59 = mi->pFRQ;
          if (v59 && !mi->FrqFlag)
            v59->str_end->font_id = 33;
          else
            *font_id = 33;
          goto LABEL_889;
        }
        return 0;
      }
      if (v49 > 0xA3A7B3B5)
      {
        if (v49 > 0xAC8F71F3)
        {
          if (v49 > 0xAE8F7519)
          {
            switch (v49)
            {
              case 0xB06D66DE:
                if (op_Equality(v14, "<lips_stop", 0))
                {
                  v184 = mi->pFRQ;
                  if (v184)
                  {
                    str_end = v184->str_end;
                    if (str_end)
                      str_end->tag_flag[2] = 61719;
                  }
                  goto LABEL_889;
                }
                break;
              case 0xC2716E0D:
                if (op_Equality(v14, "<lips", 0))
                {
                  gMessageRequestResult |= 8u;
                  goto LABEL_889;
                }
                break;
              case 0xC5A9F014:
                op_Equality(v14, "<NBSP", 0);
                return 0;
            }
          }
          else if (v49 == -1383107706)
          {
            if (op_Equality(v14, "<BTN_R2", 0))
            {
              v144 = mi->pFRQ;
              if (v144 && !mi->FrqFlag)
                v144->str_end->font_id = 15;
              else
                *font_id = 15;
              goto LABEL_889;
            }
          }
          else if (v49 == -1366330087 && op_Equality(v14, "<BTN_R3", 0))
          {
            v79 = mi->pFRQ;
            if (v79 && !mi->FrqFlag)
              v79->str_end->font_id = 16;
            else
              *font_id = 16;
            goto LABEL_889;
          }
          return 0;
        }
        if (v49 <= 0xA72C3495)
        {
          if (v49 == -1540608036)
          {
            if (op_Equality(v14, "<BTN_OP1", 0))
            {
              v128 = mi->pFRQ;
              if (v128 && !mi->FrqFlag)
                v128->str_end->font_id = 20;
              else
                *font_id = 20;
              goto LABEL_889;
            }
          }
          else if (v49 == -1490275179 && op_Equality(v14, "<BTN_OP2", 0))
          {
            v63 = mi->pFRQ;
            if (v63 && !mi->FrqFlag)
              v63->str_end->font_id = 21;
            else
              *font_id = 21;
            goto LABEL_889;
          }
          return 0;
        }
        if (v49 != -1482180095)
        {
          if (v49 == -1399885325 && op_Equality(v14, "<BTN_R1", 0))
          {
            v95 = mi->pFRQ;
            if (v95 && !mi->FrqFlag)
              v95->str_end->font_id = 14;
            else
              *font_id = 14;
            goto LABEL_889;
          }
          return 0;
        }
        if (op_Equality(v14, "<SKL_18", 0))
        {
          v161 = mi->pFRQ;
          if (v161 && !mi->FrqFlag)
            v161->str_end->font_id = 95;
          else
            *font_id = 95;
          goto LABEL_889;
        }
      }
      else if (v49 > 0xA2128D7A)
      {
        if (v49 > 0xA2A7B222)
        {
          if (v49 == -1559064819)
          {
            if (op_Equality(v14, "<MNE_10", 0))
            {
              v169 = mi->pFRQ;
              if (v169 && !mi->FrqFlag)
                v169->str_end->font_id = 114;
              else
                *font_id = 114;
              goto LABEL_889;
            }
          }
          else
          {
            if (v49 != -1549290571)
              return 0;
            if (op_Equality(v14, "<SKL_14", 0))
            {
              v104 = mi->pFRQ;
              if (v104 && !mi->FrqFlag)
                v104->str_end->font_id = 91;
              else
                *font_id = 91;
              goto LABEL_889;
            }
          }
        }
        else if (v49 == -1566215285)
        {
          if (op_Equality(v14, "<SKL_09", 0))
          {
            v136 = mi->pFRQ;
            if (v136 && !mi->FrqFlag)
              v136->str_end->font_id = 86;
            else
              *font_id = 86;
            goto LABEL_889;
          }
        }
        else
        {
          if (v49 != -1566068190)
            return 0;
          if (op_Equality(v14, "<SKL_15", 0))
          {
            v71 = mi->pFRQ;
            if (v71 && !mi->FrqFlag)
              v71->str_end->font_id = 92;
            else
              *font_id = 92;
            goto LABEL_889;
          }
        }
      }
      else if (v49 > 0xA1A7B08F)
      {
        if (v49 == -1582698714)
        {
          if (op_Equality(v14, "<SKL_24", 0))
          {
            v152 = mi->pFRQ;
            if (v152 && !mi->FrqFlag)
              v152->str_end->font_id = 143;
            else
              *font_id = 143;
            goto LABEL_889;
          }
        }
        else
        {
          if (v49 != -1575842438)
            return 0;
          if (op_Equality(v14, "<MNE_11", 0))
          {
            v86 = mi->pFRQ;
            if (v86 && !mi->FrqFlag)
              v86->str_end->font_id = 115;
            else
              *font_id = 115;
            goto LABEL_889;
          }
        }
      }
      else if (v49 == -1582992904)
      {
        if (op_Equality(v14, "<SKL_08", 0))
        {
          v121 = mi->pFRQ;
          if (v121 && !mi->FrqFlag)
            v121->str_end->font_id = 85;
          else
            *font_id = 85;
          goto LABEL_889;
        }
      }
      else
      {
        if (v49 != -1582845809)
          return 0;
        if (op_Equality(v14, "<SKL_16", 0))
        {
          v55 = mi->pFRQ;
          if (v55 && !mi->FrqFlag)
            v55->str_end->font_id = 93;
          else
            *font_id = 93;
          goto LABEL_889;
        }
      }
    }
    else if (v49 > 0x9AA566F3)
    {
      if (v49 > 0x9EA7ABD6)
      {
        if (v49 > 0x9FA7AD69)
        {
          if (v49 > 0xA0128A54)
          {
            switch (v49)
            {
              case 0xA0A57065:
                if (op_Equality(v14, "<SKL_07", 0))
                {
                  v189 = mi->pFRQ;
                  if (v189 && !mi->FrqFlag)
                    v189->str_end->font_id = 84;
                  else
                    *font_id = 84;
                  goto LABEL_889;
                }
                break;
              case 0xA0A7AEFC:
                if (op_Equality(v14, "<SKL_17", 0))
                {
                  v190 = mi->pFRQ;
                  if (v190 && !mi->FrqFlag)
                    v190->str_end->font_id = 94;
                  else
                    *font_id = 94;
                  goto LABEL_889;
                }
                break;
              case 0xA1128BE7:
                if (op_Equality(v14, "<MNE_12", 0))
                {
                  v115 = mi->pFRQ;
                  if (v115 && !mi->FrqFlag)
                    v115->str_end->font_id = 116;
                  else
                    *font_id = 116;
                  goto LABEL_889;
                }
                break;
              default:
                return 0;
            }
          }
          else if (v49 == -1609544771)
          {
            if (op_Equality(v14, "<MNE_03", 0))
            {
              v146 = mi->pFRQ;
              if (v146 && !mi->FrqFlag)
                v146->str_end->font_id = 107;
              else
                *font_id = 107;
              goto LABEL_889;
            }
          }
          else
          {
            if (v49 != -1609397676)
              return 0;
            if (op_Equality(v14, "<MNE_13", 0))
            {
              v81 = mi->pFRQ;
              if (v81 && !mi->FrqFlag)
                v81->str_end->font_id = 117;
              else
                *font_id = 117;
              goto LABEL_889;
            }
          }
        }
        else if (v49 > 0x9F1288C1)
        {
          if (v49 == -1616548142)
          {
            if (op_Equality(v14, "<SKL_06", 0))
            {
              v163 = mi->pFRQ;
              if (v163 && !mi->FrqFlag)
                v163->str_end->font_id = 83;
              else
                *font_id = 83;
              goto LABEL_889;
            }
          }
          else
          {
            if (v49 != -1616401047)
              return 0;
            if (op_Equality(v14, "<SKL_10", 0))
            {
              v97 = mi->pFRQ;
              if (v97 && !mi->FrqFlag)
                v97->str_end->font_id = 87;
              else
                *font_id = 87;
              goto LABEL_889;
            }
          }
        }
        else if (v49 == -1626322390)
        {
          if (op_Equality(v14, "<MNE_02", 0))
          {
            v130 = mi->pFRQ;
            if (v130 && !mi->FrqFlag)
              v130->str_end->font_id = 106;
            else
              *font_id = 106;
            goto LABEL_889;
          }
        }
        else
        {
          if (v49 != -1626175295)
            return 0;
          if (op_Equality(v14, "<MNE_14", 0))
          {
            v65 = mi->pFRQ;
            if (v65 && !mi->FrqFlag)
              v65->str_end->font_id = 118;
            else
              *font_id = 118;
            goto LABEL_889;
          }
        }
      }
      else if (v49 > 0x9DA56BAC)
      {
        if (v49 > 0x9E104897)
        {
          switch (v49)
          {
            case 0x9E12872E:
              if (op_Equality(v14, "<MNE_15", 0))
              {
                v172 = mi->pFRQ;
                if (v172 && !mi->FrqFlag)
                  v172->str_end->font_id = 142;
                else
                  *font_id = 142;
                goto LABEL_889;
              }
              break;
            case 0x9EA56D3F:
              if (op_Equality(v14, "<SKL_05", 0))
              {
                v173 = mi->pFRQ;
                if (v173 && !mi->FrqFlag)
                  v173->str_end->font_id = 82;
                else
                  *font_id = 82;
                goto LABEL_889;
              }
              break;
            case 0x9EA7ABD6:
              if (op_Equality(v14, "<SKL_11", 0))
              {
                v106 = mi->pFRQ;
                if (v106 && !mi->FrqFlag)
                  v106->str_end->font_id = 88;
                else
                  *font_id = 88;
                goto LABEL_889;
              }
              break;
            default:
              return 0;
          }
        }
        else if (v49 == -1649956285)
        {
          if (op_Equality(v14, "<SKL_12", 0))
          {
            v138 = mi->pFRQ;
            if (v138 && !mi->FrqFlag)
              v138->str_end->font_id = 89;
            else
              *font_id = 89;
            goto LABEL_889;
          }
        }
        else
        {
          if (v49 != -1643100009)
            return 0;
          if (op_Equality(v14, "<MNE_01", 0))
          {
            v73 = mi->pFRQ;
            if (v73 && !mi->FrqFlag)
              v73->str_end->font_id = 105;
            else
              *font_id = 105;
            goto LABEL_889;
          }
        }
      }
      else if (v49 > 0x9C104571)
      {
        if (v49 == -1666733904)
        {
          if (op_Equality(v14, "<SKL_13", 0))
          {
            v154 = mi->pFRQ;
            if (v154 && !mi->FrqFlag)
              v154->str_end->font_id = 90;
            else
              *font_id = 90;
            goto LABEL_889;
          }
        }
        else
        {
          if (v49 != -1650103380)
            return 0;
          if (op_Equality(v14, "<SKL_04", 0))
          {
            v88 = mi->pFRQ;
            if (v88 && !mi->FrqFlag)
              v88->str_end->font_id = 81;
            else
              *font_id = 81;
            goto LABEL_889;
          }
        }
      }
      else if (v49 == -1693432866)
      {
        if (op_Equality(v14, "<MNE_06", 0))
        {
          v123 = mi->pFRQ;
          if (v123 && !mi->FrqFlag)
            v123->str_end->font_id = 110;
          else
            *font_id = 110;
          goto LABEL_889;
        }
      }
      else
      {
        if (v49 != -1676655247)
          return 0;
        if (op_Equality(v14, "<MNE_07", 0))
        {
          v57 = mi->pFRQ;
          if (v57 && !mi->FrqFlag)
            v57->str_end->font_id = 111;
          else
            *font_id = 111;
          goto LABEL_889;
        }
      }
    }
    else
    {
      if (v49 <= 0x85836B51)
      {
        if (v49 > 0x78D08DD7)
        {
          if (v49 > 0x7F6B5CF9)
          {
            if (v49 == -2140447092)
            {
              if (op_Equality(v14, "<BTN_ARU", 0))
              {
                v167 = mi->pFRQ;
                if (v167 && !mi->FrqFlag)
                  v167->str_end->font_id = 28;
                else
                  *font_id = 28;
                goto LABEL_889;
              }
            }
            else if (v49 == -2054984879 && op_Equality(v14, "<BTN_ALD", 0))
            {
              v102 = mi->pFRQ;
              if (v102 && !mi->FrqFlag)
                v102->str_end->font_id = 24;
              else
                *font_id = 24;
              goto LABEL_889;
            }
          }
          else if (v49 == 2105761465)
          {
            if (op_Equality(v14, "<BTN_ALL", 0))
            {
              v134 = mi->pFRQ;
              if (v134 && !mi->FrqFlag)
                v134->str_end->font_id = 25;
              else
                *font_id = 25;
              goto LABEL_889;
            }
          }
          else if (v49 == 2137742585 && op_Equality(v14, "<BTN_ARR", 0))
          {
            v69 = mi->pFRQ;
            if (v69 && !mi->FrqFlag)
              v69->str_end->font_id = 31;
            else
              *font_id = 31;
            goto LABEL_889;
          }
          return 0;
        }
        if (v49 <= 0x76A1C6C7)
        {
          if (v49 == 1977586600)
          {
            if (op_Equality(v14, "<NW", 0))
            {
              gMessageRequestResult |= 2u;
              goto LABEL_889;
            }
          }
          else if (v49 == 1990313671 && op_Equality(v14, "<ITM_03", 0))
          {
            v53 = mi->pFRQ;
            if (v53 && !mi->FrqFlag)
              v53->str_end->font_id = 73;
            else
              *font_id = 73;
            goto LABEL_889;
          }
          return 0;
        }
        if (v49 == 2023868909)
        {
          if (op_Equality(v14, "<ITM_01", 0))
          {
            v150 = mi->pFRQ;
            if (v150 && !mi->FrqFlag)
              v150->str_end->font_id = 71;
            else
              *font_id = 71;
            goto LABEL_889;
          }
          return 0;
        }
        if (v49 != 2026933719 || !op_Equality(v14, "<TP", 0))
          return 0;
        mi->Tp = result;
        goto LABEL_889;
      }
      if (v49 > 0x96103BFF)
      {
        if (v49 > 0x991040B8)
        {
          switch (v49)
          {
            case 0x996B85E7:
              if (op_Equality(v14, "<BTN_ARL", 0))
              {
                v180 = mi->pFRQ;
                if (v180 && !mi->FrqFlag)
                  v180->str_end->font_id = 30;
                else
                  *font_id = 30;
                goto LABEL_889;
              }
              return 0;
            case 0x9A10424B:
              if (op_Equality(v14, "<MNE_05", 0))
              {
                v181 = mi->pFRQ;
                if (v181 && !mi->FrqFlag)
                  v181->str_end->font_id = 109;
                else
                  *font_id = 109;
                goto LABEL_889;
              }
              break;
            case 0x9AA566F3:
              if (op_Equality(v14, "<SKL_01", 0))
              {
                v112 = mi->pFRQ;
                if (v112 && !mi->FrqFlag)
                  v112->str_end->font_id = 78;
                else
                  *font_id = 78;
                goto LABEL_889;
              }
              break;
            default:
              return 0;
          }
        }
        else
        {
          if (v49 == -1752987737)
          {
            if (op_Equality(v14, "<BTN_ALR", 0))
            {
              v142 = mi->pFRQ;
              if (v142 && !mi->FrqFlag)
                v142->str_end->font_id = 26;
              else
                *font_id = 26;
              goto LABEL_889;
            }
            return 0;
          }
          if (v49 != -1726988104)
            return 0;
          if (op_Equality(v14, "<MNE_04", 0))
          {
            v77 = mi->pFRQ;
            if (v77 && !mi->FrqFlag)
              v77->str_end->font_id = 108;
            else
              *font_id = 108;
            goto LABEL_889;
          }
        }
      }
      else
      {
        if (v49 <= 0x948382EE)
        {
          if (v49 == -1855227569)
          {
            if (op_Equality(v14, "<BTN_ARD", 0))
            {
              v126 = mi->pFRQ;
              if (v126 && !mi->FrqFlag)
                v126->str_end->font_id = 29;
              else
                *font_id = 29;
              goto LABEL_889;
            }
          }
          else if (v49 == -1803320594 && op_Equality(v14, "<BTN_ALU", 0))
          {
            v61 = mi->pFRQ;
            if (v61 && !mi->FrqFlag)
              v61->str_end->font_id = 23;
            else
              *font_id = 23;
            goto LABEL_889;
          }
          return 0;
        }
        if (v49 == -1794098580)
        {
          if (op_Equality(v14, "<MNE_08", 0))
          {
            v158 = mi->pFRQ;
            if (v158 && !mi->FrqFlag)
              v158->str_end->font_id = 112;
            else
              *font_id = 112;
            goto LABEL_889;
          }
        }
        else
        {
          if (v49 != -1777320961)
            return 0;
          if (op_Equality(v14, "<MNE_09", 0))
          {
            v94 = mi->pFRQ;
            if (v94 && !mi->FrqFlag)
              v94->str_end->font_id = 113;
            else
              *font_id = 113;
            goto LABEL_889;
          }
        }
      }
    }
    return 0;
  }
  if (v49 > 0x532997C7)
  {
    if (v49 > 0x61A3E44F)
    {
      if (v49 > 0x6EBF34F8)
      {
        if (v49 > 0x71A1BEE8)
        {
          if (v49 > 0x73A1C20E)
          {
            if (v49 == 1940149306)
            {
              if (!op_Equality(v14, "<IT_E", 0))
                return 0;
              mi->pFRQ->str_end->font_id = -1;
              goto LABEL_889;
            }
            if (v49 != 1956758433)
            {
              if (v49 == 1973536052 && op_Equality(v14, "<ITM_02", 0))
              {
                v116 = mi->pFRQ;
                if (v116 && !mi->FrqFlag)
                  v116->str_end->font_id = 72;
                else
                  *font_id = 72;
                goto LABEL_889;
              }
              return 0;
            }
            if (op_Equality(v14, "<ITM_05", 0))
            {
              v191 = mi->pFRQ;
              if (v191 && !mi->FrqFlag)
                v191->str_end->font_id = 75;
              else
                *font_id = 75;
              goto LABEL_889;
            }
          }
          else if (v49 == 1923203195)
          {
            if (op_Equality(v14, "<ITM_07", 0))
            {
              v147 = mi->pFRQ;
              if (v147 && !mi->FrqFlag)
                v147->str_end->font_id = 77;
              else
                *font_id = 77;
              goto LABEL_889;
            }
          }
          else
          {
            if (v49 != 1939980814)
              return 0;
            if (op_Equality(v14, "<ITM_04", 0))
            {
              v82 = mi->pFRQ;
              if (v82 && !mi->FrqFlag)
                v82->str_end->font_id = 74;
              else
                *font_id = 74;
              goto LABEL_889;
            }
          }
        }
        else if (v49 > 0x6FA1BBC2)
        {
          if (v49 == 1889647957)
          {
            if (op_Equality(v14, "<ITM_09", 0))
            {
              v164 = mi->pFRQ;
              if (v164 && !mi->FrqFlag)
                v164->str_end->font_id = 120;
              else
                *font_id = 120;
              goto LABEL_889;
            }
          }
          else
          {
            if (v49 != 1906425576)
              return 0;
            if (op_Equality(v14, "<ITM_06", 0))
            {
              v98 = mi->pFRQ;
              if (v98 && !mi->FrqFlag)
                v98->str_end->font_id = 76;
              else
                *font_id = 76;
              goto LABEL_889;
            }
          }
        }
        else if (v49 == 1869098010)
        {
          if (op_Equality(v14, "<DEP_01", 0))
          {
            v131 = mi->pFRQ;
            if (v131 && !mi->FrqFlag)
            {
              v131->str_end->font_id = 96;
              goto LABEL_889;
            }
            v52 = 96;
            goto LABEL_888;
          }
        }
        else
        {
          if (v49 != 1872870338)
            return 0;
          if (op_Equality(v14, "<ITM_08", 0))
          {
            v66 = mi->pFRQ;
            if (v66 && !mi->FrqFlag)
            {
              v66->str_end->font_id = 119;
              goto LABEL_889;
            }
            v52 = 119;
            goto LABEL_888;
          }
        }
      }
      else if (v49 > 0x6A68243B)
      {
        if (v49 > 0x6C682761)
        {
          if (v49 == 1835542772)
          {
            if (op_Equality(v14, "<DEP_03", 0))
            {
              v174 = mi->pFRQ;
              if (v174 && !mi->FrqFlag)
              {
                v174->str_end->font_id = 98;
                goto LABEL_889;
              }
              v52 = 98;
              goto LABEL_888;
            }
          }
          else
          {
            if (v49 != 1852320391)
            {
              if (v49 == 1858024696 && op_Equality(v14, "<SP", 0))
              {
                v107 = mi;
                if (result == 129)
                  v109 = 0x80;
                else
                  v109 = 4 * result - 4;
                v107->Spd = v109;
                v107 = mia;
                lipsync_pm->spd = 4;
                v107->Spd = DisplaySpeed();
                ++mia->Ofs;
                goto LABEL_889;
              }
              return 0;
            }
            if (op_Equality(v14, "<DEP_02", 0))
            {
              v175 = mi->pFRQ;
              if (v175 && !mi->FrqFlag)
              {
                v175->str_end->font_id = 97;
                goto LABEL_889;
              }
              v52 = 97;
              goto LABEL_888;
            }
          }
        }
        else if (v49 == 1801987534)
        {
          if (op_Equality(v14, "<DEP_05", 0))
          {
            v139 = mi->pFRQ;
            if (v139 && !mi->FrqFlag)
            {
              v139->str_end->font_id = 100;
              goto LABEL_889;
            }
            v52 = 100;
            goto LABEL_888;
          }
        }
        else
        {
          if (v49 != 1818765153)
            return 0;
          if (op_Equality(v14, "<DEP_04", 0))
          {
            v74 = mi->pFRQ;
            if (v74 && !mi->FrqFlag)
            {
              v74->str_end->font_id = 99;
              goto LABEL_889;
            }
            v52 = 99;
            goto LABEL_888;
          }
        }
      }
      else if (v49 > 0x68682115)
      {
        if (v49 == 1768432296)
        {
          if (op_Equality(v14, "<DEP_07", 0))
          {
            v155 = mi->pFRQ;
            if (v155 && !mi->FrqFlag)
            {
              v155->str_end->font_id = 102;
              goto LABEL_889;
            }
            v52 = 102;
            goto LABEL_888;
          }
        }
        else
        {
          if (v49 != 1785209915)
            return 0;
          if (op_Equality(v14, "<DEP_06", 0))
          {
            v89 = mi->pFRQ;
            if (v89 && !mi->FrqFlag)
            {
              v89->str_end->font_id = 101;
              goto LABEL_889;
            }
            v52 = 101;
            goto LABEL_888;
          }
        }
      }
      else if (v49 == 1734877058)
      {
        if (op_Equality(v14, "<DEP_09", 0))
        {
          v124 = mi->pFRQ;
          if (v124 && !mi->FrqFlag)
          {
            v124->str_end->font_id = 104;
            goto LABEL_889;
          }
          v52 = 104;
          goto LABEL_888;
        }
      }
      else
      {
        if (v49 != 1751654677)
          return 0;
        if (op_Equality(v14, "<DEP_08", 0))
        {
          v58 = mi->pFRQ;
          if (v58 && !mi->FrqFlag)
          {
            v58->str_end->font_id = 103;
            goto LABEL_889;
          }
          v52 = 103;
          goto LABEL_888;
        }
      }
    }
    else if (v49 > 0x582BDE3D)
    {
      if (v49 > 0x5DE7BCA5)
      {
        if (v49 > 0x5EA3DF96)
        {
          switch (v49)
          {
            case 0x5F329B61u:
              if (!op_Equality(v14, "<BTN_Y", 0))
                return 0;
              v182 = mi->pFRQ;
              if (v182 && !mi->FrqFlag)
              {
                v182->str_end->font_id = 13;
                goto LABEL_889;
              }
              v52 = 13;
              goto LABEL_888;
            case 0x5FA3E129u:
              if (op_Equality(v14, "<ITM_12", 0))
              {
                v183 = mi->pFRQ;
                if (v183 && !mi->FrqFlag)
                {
                  v183->str_end->font_id = 123;
                  goto LABEL_889;
                }
                v52 = 123;
                goto LABEL_888;
              }
              break;
            case 0x61A3E44Fu:
              if (op_Equality(v14, "<ITM_14", 0))
              {
                v113 = mi->pFRQ;
                if (v113 && !mi->FrqFlag)
                {
                  v113->str_end->font_id = 125;
                  goto LABEL_889;
                }
                v52 = 125;
                goto LABEL_888;
              }
              break;
            default:
              return 0;
          }
        }
        else
        {
          if (v49 == 1580374478)
          {
            if (!op_Equality(v14, "<BTN_X", 0))
              return 0;
            v143 = mi->pFRQ;
            if (v143 && !mi->FrqFlag)
            {
              v143->str_end->font_id = 12;
              goto LABEL_889;
            }
            v52 = 12;
            goto LABEL_888;
          }
          if (v49 != 1587797910)
            return 0;
          if (op_Equality(v14, "<ITM_13", 0))
          {
            v78 = mi->pFRQ;
            if (v78 && !mi->FrqFlag)
            {
              v78->str_end->font_id = 124;
              goto LABEL_889;
            }
            v52 = 124;
            goto LABEL_888;
          }
        }
      }
      else
      {
        if (v49 > 0x5DA3DE03)
        {
          if (v49 == 1571041688)
          {
            if (!op_Equality(v14, "<IT_S", 0))
              return 0;
            v159 = mi->pFRQ;
            if (!v159 || (v160 = v159->str_end) == 0)
            {
              v52 = 2;
              goto LABEL_888;
            }
            v160->font_id = 1;
          }
          else
          {
            if (v49 != 1575468197 || !op_Equality(v14, "<CO", 0))
              return 0;
            mi->ColNo = result;
          }
          goto LABEL_889;
        }
        if (v49 == 1554242672)
        {
          if (op_Equality(v14, "<ITM_11", 0))
          {
            v127 = mi->pFRQ;
            if (v127 && !mi->FrqFlag)
            {
              v127->str_end->font_id = 122;
              goto LABEL_889;
            }
            v52 = 122;
            goto LABEL_888;
          }
        }
        else
        {
          if (v49 != 1571020291)
            return 0;
          if (op_Equality(v14, "<ITM_10", 0))
          {
            v62 = mi->pFRQ;
            if (v62 && !mi->FrqFlag)
            {
              v62->str_end->font_id = 121;
              goto LABEL_889;
            }
            v52 = 121;
            goto LABEL_888;
          }
        }
      }
    }
    else if (v49 > 0x55299AED)
    {
      if (v49 > 0x562BDB17)
      {
        if (v49 == 1462492330)
        {
          if (op_Equality(v14, "<RAI_13", 0))
          {
            v168 = mi->pFRQ;
            if (v168 && !mi->FrqFlag)
            {
              v168->str_end->font_id = 138;
              goto LABEL_889;
            }
            v52 = 138;
            goto LABEL_888;
          }
        }
        else
        {
          if (v49 != 1479269949)
            return 0;
          if (op_Equality(v14, "<RAI_12", 0))
          {
            v103 = mi->pFRQ;
            if (v103 && !mi->FrqFlag)
            {
              v103->str_end->font_id = 137;
              goto LABEL_889;
            }
            v52 = 137;
            goto LABEL_888;
          }
        }
      }
      else if (v49 == 1428937092)
      {
        if (op_Equality(v14, "<RAI_11", 0))
        {
          v135 = mi->pFRQ;
          if (v135 && !mi->FrqFlag)
          {
            v135->str_end->font_id = 136;
            goto LABEL_889;
          }
          v52 = 136;
          goto LABEL_888;
        }
      }
      else
      {
        if (v49 != 1445714711)
          return 0;
        if (op_Equality(v14, "<RAI_10", 0))
        {
          v70 = mi->pFRQ;
          if (v70 && !mi->FrqFlag)
          {
            v70->str_end->font_id = 135;
            goto LABEL_889;
          }
          v52 = 135;
          goto LABEL_888;
        }
      }
    }
    else if (v49 > 0x5429995A)
    {
      if (v49 == 1412159473)
      {
        if (op_Equality(v14, "<RAI_16", 0))
        {
          v151 = mi->pFRQ;
          if (v151 && !mi->FrqFlag)
          {
            v151->str_end->font_id = 140;
            goto LABEL_889;
          }
          v52 = 140;
          goto LABEL_888;
        }
      }
      else
      {
        if (v49 != 1428789997)
          return 0;
        if (op_Equality(v14, "<RAI_05", 0))
        {
          v85 = mi->pFRQ;
          if (v85 && !mi->FrqFlag)
          {
            v85->str_end->font_id = 130;
            goto LABEL_889;
          }
          v52 = 130;
          goto LABEL_888;
        }
      }
    }
    else if (v49 == 1395381854)
    {
      if (op_Equality(v14, "<RAI_17", 0))
      {
        v120 = mi->pFRQ;
        if (v120 && !mi->FrqFlag)
        {
          v120->str_end->font_id = 141;
          goto LABEL_889;
        }
        v52 = 141;
        goto LABEL_888;
      }
    }
    else
    {
      if (v49 != 1412012378)
        return 0;
      if (op_Equality(v14, "<RAI_04", 0))
      {
        v54 = mi->pFRQ;
        if (v54 && !mi->FrqFlag)
        {
          v54->str_end->font_id = 129;
          goto LABEL_889;
        }
        v52 = 129;
        goto LABEL_888;
      }
    }
    return 0;
  }
  if (v49 > 0x2FA19A71)
  {
    if (v49 <= 0x47327599)
    {
      if (v49 <= 0x3D8A4608)
      {
        if (v49 > 0x32A19F2A)
        {
          if (v49 == 866230461)
          {
            if (!op_Equality(v14, "<ICN_03", 0))
              return 0;
            v153 = mi->pFRQ;
            if (v153 && !mi->FrqFlag)
            {
              v153->str_end->font_id = 58;
              goto LABEL_889;
            }
            v52 = 58;
          }
          else
          {
            if (v49 != 1032472072 || !op_Equality(v14, "<BTN_L2", 0))
              return 0;
            v87 = mi->pFRQ;
            if (v87 && !mi->FrqFlag)
            {
              v87->str_end->font_id = 18;
              goto LABEL_889;
            }
            v52 = 18;
          }
        }
        else if (v49 == 832675223)
        {
          if (!op_Equality(v14, "<ICN_01", 0))
            return 0;
          v122 = mi->pFRQ;
          if (v122 && !mi->FrqFlag)
          {
            v122->str_end->font_id = 56;
            goto LABEL_889;
          }
          v52 = 56;
        }
        else
        {
          if (v49 != 849452842 || !op_Equality(v14, "<ICN_02", 0))
            return 0;
          v56 = mi->pFRQ;
          if (v56 && !mi->FrqFlag)
          {
            v56->str_end->font_id = 57;
            goto LABEL_889;
          }
          v52 = 57;
        }
        goto LABEL_888;
      }
      if (v49 <= 0x408A4AC1)
      {
        if (v49 == 1049249691)
        {
          if (!op_Equality(v14, "<BTN_L3", 0))
            return 0;
          v137 = mi->pFRQ;
          if (v137 && !mi->FrqFlag)
          {
            v137->str_end->font_id = 19;
            goto LABEL_889;
          }
          v52 = 19;
        }
        else
        {
          if (v49 != 1082804929 || !op_Equality(v14, "<BTN_L1", 0))
            return 0;
          v72 = mi->pFRQ;
          if (v72 && !mi->FrqFlag)
          {
            v72->str_end->font_id = 17;
            goto LABEL_889;
          }
          v52 = 17;
        }
        goto LABEL_888;
      }
      if (v49 == 1144156384)
      {
        if (!op_Equality(v14, "<BTN_B", 0))
          return 0;
        v170 = mi->pFRQ;
        if (v170 && !mi->FrqFlag)
        {
          v170->str_end->font_id = 11;
          goto LABEL_889;
        }
        v52 = 11;
        goto LABEL_888;
      }
      if (v49 != 1167288271)
      {
        if (v49 != 1194489241 || !op_Equality(v14, "<BTN_A", 0))
          return 0;
        v105 = mi->pFRQ;
        if (v105 && !mi->FrqFlag)
        {
          v105->str_end->font_id = 10;
          goto LABEL_889;
        }
        v52 = 10;
        goto LABEL_888;
      }
      if (!op_Equality(v14, "<mw", 0))
        return 0;
      v171 = mi->pFRQ->str_end;
      v171->tag_flag[0] = 61972;
      v171->wait = Parse(v13, 0);
      goto LABEL_889;
    }
    if (v49 > 0x4E298FE8)
    {
      if (v49 > 0x512994A1)
      {
        switch (v49)
        {
          case 0x512BD338u:
            if (op_Equality(v14, "<RAI_15", 0))
            {
              v187 = mi->pFRQ;
              if (v187 && !mi->FrqFlag)
              {
                v187->str_end->font_id = 139;
                goto LABEL_889;
              }
              v52 = 139;
              goto LABEL_888;
            }
            break;
          case 0x52299634u:
            if (op_Equality(v14, "<RAI_06", 0))
            {
              v188 = mi->pFRQ;
              if (v188 && !mi->FrqFlag)
              {
                v188->str_end->font_id = 131;
                goto LABEL_889;
              }
              v52 = 131;
              goto LABEL_888;
            }
            break;
          case 0x532997C7u:
            if (op_Equality(v14, "<RAI_07", 0))
            {
              v114 = mi->pFRQ;
              if (v114 && !mi->FrqFlag)
              {
                v114->str_end->font_id = 132;
                goto LABEL_889;
              }
              v52 = 132;
              goto LABEL_888;
            }
            break;
          default:
            return 0;
        }
      }
      else if (v49 == 1328124283)
      {
        if (op_Equality(v14, "<RAI_03", 0))
        {
          v145 = mi->pFRQ;
          if (v145 && !mi->FrqFlag)
          {
            v145->str_end->font_id = 128;
            goto LABEL_889;
          }
          v52 = 128;
          goto LABEL_888;
        }
      }
      else
      {
        if (v49 != 1361679521)
          return 0;
        if (op_Equality(v14, "<RAI_01", 0))
        {
          v80 = mi->pFRQ;
          if (v80 && !mi->FrqFlag)
          {
            v80->str_end->font_id = 126;
            goto LABEL_889;
          }
          v52 = 126;
          goto LABEL_888;
        }
      }
    }
    else if (v49 > 0x49298809)
    {
      if (v49 == 1244822098)
      {
        if (!op_Equality(v14, "<BTN_D", 0))
          return 0;
        v162 = mi->pFRQ;
        if (v162 && !mi->FrqFlag)
        {
          v162->str_end->font_id = 32;
          goto LABEL_889;
        }
        v52 = 32;
        goto LABEL_888;
      }
      if (v49 != 1311346664)
        return 0;
      if (op_Equality(v14, "<RAI_02", 0))
      {
        v96 = mi->pFRQ;
        if (v96 && !mi->FrqFlag)
        {
          v96->str_end->font_id = 127;
          goto LABEL_889;
        }
        v52 = 127;
        goto LABEL_888;
      }
    }
    else if (v49 == 1210680950)
    {
      if (op_Equality(v14, "<RAI_08", 0))
      {
        v129 = mi->pFRQ;
        if (v129 && !mi->FrqFlag)
        {
          v129->str_end->font_id = 133;
          goto LABEL_889;
        }
        v52 = 133;
        goto LABEL_888;
      }
    }
    else
    {
      if (v49 != 1227458569)
        return 0;
      if (op_Equality(v14, "<RAI_09", 0))
      {
        v64 = mi->pFRQ;
        if (v64 && !mi->FrqFlag)
        {
          v64->str_end->font_id = 134;
          goto LABEL_889;
        }
        v52 = 134;
        goto LABEL_888;
      }
    }
    return 0;
  }
  if (v49 <= 0x17C9395F)
  {
    if (v49 <= 0x199AB62)
    {
      if (v49 > 0x99A9CF)
      {
        if (v49 == 26701003)
        {
          if (!op_Equality(v14, "<BST_19", 0))
            return 0;
          v149 = mi->pFRQ;
          if (v149 && !mi->FrqFlag)
          {
            v149->str_end->font_id = 55;
            goto LABEL_889;
          }
          v52 = 55;
        }
        else
        {
          if (v49 != 26848098 || !op_Equality(v14, "<BST_05", 0))
            return 0;
          v84 = mi->pFRQ;
          if (v84 && !mi->FrqFlag)
          {
            v84->str_end->font_id = 41;
            goto LABEL_889;
          }
          v52 = 41;
        }
      }
      else
      {
        if (v49 != 9923384)
        {
          if (v49 == 10070479 && op_Equality(v14, "<BST_06", 0))
          {
            v51 = mi->pFRQ;
            if (v51 && !mi->FrqFlag)
            {
              v51->str_end->font_id = 42;
              goto LABEL_889;
            }
            v52 = 42;
            goto LABEL_888;
          }
          return 0;
        }
        if (!op_Equality(v14, "<BST_18", 0))
          return 0;
        v118 = mi->pFRQ;
        if (v118 && !mi->FrqFlag)
        {
          v118->str_end->font_id = 54;
          goto LABEL_889;
        }
        v52 = 54;
      }
LABEL_888:
      *font_id = v52;
      goto LABEL_889;
    }
    if (v49 <= 0x599B1AE)
    {
      if (v49 == 43625717)
      {
        if (!op_Equality(v14, "<BST_04", 0))
          return 0;
        v133 = mi->pFRQ;
        if (v133 && !mi->FrqFlag)
        {
          v133->str_end->font_id = 40;
          goto LABEL_889;
        }
        v52 = 40;
      }
      else
      {
        if (v49 != 93958574 || !op_Equality(v14, "<BST_09", 0))
          return 0;
        v68 = mi->pFRQ;
        if (v68 && !mi->FrqFlag)
        {
          v68->str_end->font_id = 45;
          goto LABEL_889;
        }
        v52 = 45;
      }
      goto LABEL_888;
    }
    if (v49 == 110736193)
    {
      if (!op_Equality(v14, "<BST_08", 0))
        return 0;
      v166 = mi->pFRQ;
      if (v166 && !mi->FrqFlag)
      {
        v166->str_end->font_id = 44;
        goto LABEL_889;
      }
      v52 = 44;
      goto LABEL_888;
    }
    if (v49 != 399063391 || !op_Equality(v14, "<WA", 0))
      return 0;
    goto LABEL_749;
  }
  if (v49 > 0x27C296CA)
  {
    if (v49 > 0x2CA195B8)
    {
      if (v49 == 765564747)
      {
        if (!op_Equality(v14, "<ICN_05", 0))
          return 0;
        v178 = mi->pFRQ;
        if (v178 && !mi->FrqFlag)
        {
          v178->str_end->font_id = 60;
          goto LABEL_889;
        }
        v52 = 60;
      }
      else if (v49 == 782342366)
      {
        if (!op_Equality(v14, "<ICN_06", 0))
          return 0;
        v179 = mi->pFRQ;
        if (v179 && !mi->FrqFlag)
        {
          v179->str_end->font_id = 61;
          goto LABEL_889;
        }
        v52 = 61;
      }
      else
      {
        if (v49 != 799119985 || !op_Equality(v14, "<ICN_07", 0))
          return 0;
        v111 = mi->pFRQ;
        if (v111 && !mi->FrqFlag)
        {
          v111->str_end->font_id = 62;
          goto LABEL_889;
        }
        v52 = 62;
      }
    }
    else if (v49 == 681676652)
    {
      if (!op_Equality(v14, "<ICN_08", 0))
        return 0;
      v141 = mi->pFRQ;
      if (v141 && !mi->FrqFlag)
      {
        v141->str_end->font_id = 63;
        goto LABEL_889;
      }
      v52 = 63;
    }
    else
    {
      if (v49 != 748787128 || !op_Equality(v14, "<ICN_04", 0))
        return 0;
      v76 = mi->pFRQ;
      if (v76 && !mi->FrqFlag)
      {
        v76->str_end->font_id = 59;
        goto LABEL_889;
      }
      v52 = 59;
    }
    goto LABEL_888;
  }
  if (v49 > 0x23D3D99F)
  {
    if (v49 != 652993342)
    {
      if (v49 == 667064010 && op_Equality(v14, "<RE", 0))
      {
        if ((gModeFlag & 4) == 0)
        {
          v93 = mi;
          frMessageReturnCode(v93);
        }
        goto LABEL_889;
      }
      return 0;
    }
    if (!op_Equality(v14, "<AD", 0))
      return 0;
    if ((gModeFlag & 8) == 0)
      goto LABEL_889;
LABEL_749:
    gMessageRequestResult |= 1u;
    goto LABEL_889;
  }
  if (v49 != 502539224)
  {
    if (v49 == 601086367 && op_Equality(v14, "<KU", 0))
    {
      gMessageRequestResult |= 4u;
      goto LABEL_889;
    }
    return 0;
  }
  if (!op_Equality(v14, "<FO", 0))
    return 0;
  mi->Style = result - 1;
LABEL_889:
  v194 = *font_id;
  if (*font_id >= 10)
    v195 = 0;
  else
    v195 = 521;
  if (v195 != 521)
  {
    MessageCreateHandle(mia, 0x20u, v194);
    *font_id = 0;
  }
  v44 = 1;
  if (!mia->FrqFlag)
    mia->FrqFlag = 1;
  return v44;
}

// 0x1c3a3a0
static s32 GetTagIndex(char *tag) {
  s32 stringLength;
  s64 v4;
  s32 v5;
  char *TagList_local;
  s32 v8;
  char *v9;
  char *v10;

  stringLength = tag->_stringLength;
  v4 = 4;
  v5 = -1;
  while (1)
  {
    TagList_local = TagList;
    if (v4 - 4 >= SLODWORD(TagList_local->max_length))
      return v5;
    v8 = *(u32 *)(*((u64 *)&TagList_local->obj.klass + v4) + 16);
    if (v8 < stringLength)
    {
      v8 = *(u32 *)(*((u64 *)&TagList->obj.klass + v4) + 16);
      v9 = Substring_54838176(tag, 0, v8, 0);
      v10 = ToUpperInvariant(v9, 0);
      if (Equals_54828784(v10, *((char **)&TagList->obj.klass + v4), 0))
      {
        return v4 - 4;
      }
    }
    ++v4;
  }
}

// 0x1c3a4e0
char *itfTextTagReplace(char *_text, bool useV) {
  void *v5;
  void *v7;
  void *v9;
  void *v11;
  void *v13;
  void *v15;
  void *v17;
  s64 i;
  void *v20;
  Il2CppObject *v21;
  char *v22;
  s32 j;
  char *PlatformString;
  void *v25;
  Il2CppObject *v26;
  char *v28;
  s32 v30;
  s32 data;

  v5 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v5, text, 0);
  v7 = itfTextBtnConvertBuild(v5);
  v9 = itfTextItmConvertBuild(v7);
  v11 = itfTextSklConvertBuild(v9);
  v13 = itfTextDepConvertBuild(v11);
  v15 = itfTextMneConvertBuild(v13);
  v17 = itfTextRaiConvertBuild(v15);
  if (useV)
  {
    for (i = 0; i != 32; ++i)
    {
      data = i;
      v21 = Box(s32, &data);
      v22 = Format("<V {0}>", v21, 0);
      v20 = Replace(v17, v22, gVarStr[i], 0);
      v17 = v20;
    }
  }
  for (j = 0; j != 12; ++j)
  {
    v30 = j;
    v26 = Box(s32, &v30);
    v28 = Format("<PT {0}>", v26, 0);
    PlatformString = itfGetPlatformString(j);
    v25 = Replace(v17, v28, PlatformString, 0);
    v17 = v25;
  }
  return ((char *(void *, const MethodInfo *))v25->klass->vtable._3_ToString.methodPtr)(v25, v25->klass->vtable._3_ToString.method);
}

// 0x1c34a70
static char *frReplaceLocalizeText(char *message, frMsgInfo_t *mi, void *index) {
  s32 size;
  char *v7;
  s32 v8;
  bool v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  char *v14;
  frMsgInfo_t *v15;
  char *LocalizeText;
  char *v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  char *v22;
  char *v24;
  s32 TagIndex;
  char *Code;
  s32 v28;
  s32 v30;
  s32 v32;
  char *v33;
  char *v35;
  s32 mapSummonID;
  s32 v39;
  char *v40;
  char *v41;
  char *v42;
  char *v43;
  char *v44;
  char *v45;
  char *v46;
  char *v47;
  char *v48;
  char *v49;
  char *v50;
  char *v51;
  s32 stringLength;
  s32 result;
  u16 Chars;

  size = index->_size;
  Chars = 0;
  result = 0;
  if (size)
  {
    v7 = "";
    if (size < 1)
    {
      v17 = "";
      stringLength = ""->_stringLength;
      if (stringLength < 1)
      {
LABEL_66:
        v40 = Replace_56923376(v17, "<font ", "<FO", 1, 0);
        v41 = Replace_56923376(v40, "<font", "<FO", 1, 0);
        v42 = Replace_56923376(v41, "<color ", "<CO", 1, 0);
        v43 = Replace_56923376(v42, "<color", "<CO", 1, 0);
        v44 = Replace_56923376(v43, "<tp ", "<TP", 1, 0);
        v45 = Replace_56923376(v44, "<tp", "<TP", 1, 0);
        v46 = Replace_56923376(v45, "<spd ", "<SP", 1, 0);
        v47 = Replace_56923376(v46, "<spd", "<SP", 1, 0);
        v48 = Replace_56923376(v47, "<WAIT", "<WA", 1, 0);
        v49 = Replace_56923376(v48, "<RET", "<RE", 1, 0);
        v50 = Replace_56923376(v49, "<NWAIT", "<NW", 1, 0);
        v51 = Replace_56923376(v50, "<AF_DEL", "<AD", 1, 0);
        return Replace_56923376(v51, "<KUTI", "<KU", 1, 0);
      }
    }
    else
    {
      v8 = 0;
      v9 = 0;
      v10 = 0;
      do
      {
        v11 = IndexOf(message, 0x3Eu, 0);
        v12 = v11 + 1;
        v13 = v11;
        v14 = Substring_54838176(message, 0, v11 + 1, 0);
        if (_get_Item(index, v10) == -1)
        {
          op_Inequality(v14, "<WAIT>", 0);
          v7 = Concat_54766928(v7, v14, 0);
          v9 = 0;
        }
        else
        {
          v15 = mi;
          v15->talk_tag = v14;
          LocalizeText = GetLocalizeText(v14, 1);
          if (v9 || v8 != 0)
            v7 = Concat_54766928(v7, "\n", 0);
          v7 = Concat_54766928(v7, LocalizeText, 0);
          v9 = op_Inequality(LocalizeText, v14, 0);
          ++v8;
        }
        ++v10;
        message = Substring_54838176(message, v12, message->_stringLength + ~v13, 0);
      }
      while (v10 < index->_size);
      v17 = "";
      stringLength = v7->_stringLength;
      if (stringLength < 1)
        goto LABEL_66;
    }
    v18 = 0;
    do
    {
      if (get_Chars(v7, v18, 0) == 60)
      {
        v19 = IndexOf_54850576(v7, 0x3Eu, v18, 0);
        if (v19 == -1)
          goto LABEL_66;
        v20 = v19 + 1;
        v21 = v19 + 1 - v18;
        v22 = Substring_54838176(v7, v18, v21, 0);
        v24 = Replace_54838864(v22, " ", "", 0);
        TagIndex = GetTagIndex(v24);
        if (TagIndex != -1)
        {
          v28 = TagIndex;
          result = 0;
          v30 = v24->_stringLength;
          v31 = (u32)TagList[v28]->_stringLength;
          v32 = v30 + ~(u32)v31;
          if (v32 >= 1)
          {
            LODWORD() = TagList[v28]->_stringLength;
            v33 = Substring_54838176(v24, (s32)v32, 0);
            if (!TryParse(v33, &result, 0))
              result = 0;
          }
          switch (v28)
          {
            case 0:
              v35 = gVarStr[result];
              if (!v35)
                goto LABEL_38;
              v35 = gVarStr[result];
              Code = itfNumConv(v35);
              goto LABEL_36;
            case 1:
            case 2:
              Code = frGet2NString();
              goto LABEL_36;
            case 3:
            case 4:
              Code = frGet1NString();
              goto LABEL_36;
            case 5:
            case 6:
              if (result == 1)
                Code = frGetCode();
              else
                Code = frGetString();
              goto LABEL_36;
            case 9:
            case 10:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
              Code = Substring_54838176(v7, v18, v21, 0);
              goto LABEL_36;
            case 11:
              v24 = gVarStr[result];
              if (!v24)
                goto LABEL_38;
              v24 = gVarStr[result];
              break;
            case 12:
              mapSummonID = result;
              if (!result)
              {
                mapSummonID = GBWK->mapSummonID;
                result = mapSummonID;
              }
              Code = sdatDevilName(mapSummonID, 0);
              goto LABEL_36;
            case 19:
              v39 = result;
              Code = itfGetPlatformString(v39);
              goto LABEL_36;
            default:
              goto LABEL_38;
          }
        }
      }
      else
      {
        Chars = get_Chars(v7, v18, 0);
        v20 = v18 + 1;
        Code = ToString((u16)&Chars, 0);
LABEL_36:
        v24 = Code;
      }
      v17 = Concat_54766928(v17, v24, 0);
LABEL_38:
      v18 = v20;
    }
    while (v20 < stringLength);
    goto LABEL_66;
  }
  return message;
}

// 0x1c3c4e0
char *itfGetPlatformString(s32 num) {
  Il2CppObject *v3;
  char *v4;
  s32 data;

  data = num;
  v3 = Box(s32, &data);
  v4 = Format("TAG_PLTF_L{0:D4}>", v3, 0);
  return GetLocalizeText(v4, 1);
}

// 0x1c3c5a0
FontReq_t *itfCreateVarFRQ(char *message) {
  frMsgInfo_t *v3;
  s32 stringLength;
  s32 i;
  FontReq_t *v7;
  u16 Chars;
  s32 v13;
  f32 v14;
  s32 v15;

  v3 = Allocate(frMsgInfo_t);
  stringLength = message->_stringLength;
  if (stringLength >= 1)
  {
    for (i = 0; stringLength != i; ++i)
    {
      Chars = get_Chars(message, i, 0);
      if (Chars != 10)
      {
        frCreateNewHandle(v3);
        *(u8 *)(NewSpecific(byte, 2u) + 32) = 0x80;
        v7 = frSetFontStringLocalize(Chars, v3->Style, v3->ColNo, v3->Tp, v3->pFRQ);
        v3->pFRQ = v7;
        continue;
      }
      if ((gModeFlag & 4) != 0)
      {
        v13 = v3->Y;
        v14 = (f32)gMessageStepY * 2.25;
        v15 = 8 * (s32)v14;
        if (v14 == INFINITY)
          v15 = 0;
        v3->Y = v15 + v13;
        *(u16 *)&v3->FrqFlag = 257;
      }
    }
  }
  return v3->pFRQ;
}

// 0x1c39c90
static void frCreateNewHandle(frMsgInfo_t *pMsgInfo) {
  FontReq_t *pFRQ;
  s8 ColNo;
  s8 Tp;
  FontReq_t *v8;
  u32 Spd;
  u8 v10;
  s64 v11;
  FontReq_t *v12;

  pFRQ = pMsgInfo->pFRQ;
  if (pFRQ && !pFRQ->str)
  {
    pMsgInfo->FrqFlag = 0;
  }
  else if (pMsgInfo->FrqFlag)
  {
    ColNo = pMsgInfo->ColNo;
    Tp = pMsgInfo->Tp;
    v8 = frLinkFontString(itf, 0, ColNo, Tp, pFRQ);
    pMsgInfo->pFRQ = v8;
    Spd = pMsgInfo->Spd;
    if (Spd >= 0x41)
      v10 = 0x80;
    else
      v10 = 2 * Spd;
    pMsgInfo->pFRQ->draw_spd = v10;
    pMsgInfo->FrqFlag = 0;
  }
  if (pMsgInfo->RetFlag)
  {
    v11 = *(u64 *)&pMsgInfo->X;
    v12 = pMsgInfo->pFRQ;
    *(u64 *)&v12->x = v11;
    pMsgInfo->RetFlag = 0;
  }
}

// 0x1c3c930
void frInitFontTable(s32 GsFontNums, s32 TextNums) {
  frFontTable_t *gFT_local;
  FontReq_t *DestroyHandleList;
  FontReq_t *v9;
  frFontTable_t *v11;
  void *inited;
  frFontTable_t *v13;
  void *v14;
  s64 i;
  u64 *v16;

  gFT_local = gFT;
  *(u64 *)&gFT_local->GsFontNums = 0;
  gFT_local->FontHandleNums = 0;
  DestroyHandleList = gFT_local->DestroyHandleList;
  DestroyHandleList[0] = 0;
  v9 = gFT->DestroyHandleList;
  v9[1] = 0;
  v11 = gFT;
  inited = Init_object_(4 * TextNums);
  v11->pTextRing = (void *)inited;
  v13 = gFT;
  v14 = Init_object_(TextNums);
  v13->pRequestRing = (void *)v14;
  for (i = 32; i != 288; i += 8)
  {
    v16 = ((char *)&gVarStr->obj.klass + i);
    *v16 = 0;
  }
}

// 0x1c3cae0
void frDestroyFontTable(dds3ProcessID_t *id) {
  frDestroyFontRequestNow(gFT->DestroyHandleList[0]);
  frDestroyFontRequestNow(gFT->DestroyHandleList[1]);
  Destroy_object_(&gFT->pTextRing);
  Destroy_object_(&gFT->pRequestRing);
}

// 0x1c3cd20
FontReq_t *frDestroyFontRequest(FontReq_t *pFRQ) {
  frDestroyFontRequestNow(pFRQ);
  return 0;
}

// 0x1c3cbc0
FontReq_t *frDestroyFontRequestNow(FontReq_t *pFRQ) {
  Il2CppObject *monitor;
  Il2CppObject *klass;
  Il2CppObject *v6;
  Il2CppObject *pBuf;

  monitor = pFRQ;
  pBuf = pFRQ;
  if (monitor)
  {
    while (1)
    {
      klass = monitor[3].klass;
      v6 = klass;
      if (klass)
        break;
      monitor = monitor[4].monitor;
LABEL_5:
      RetTo_object_(&pBuf, &gFT->pRequestRing);
      pBuf = monitor;
      --gFT->FontHandleNums;
      if (!monitor)
        return 0;
    }
    do
    {
      klass = klass[4].klass;
      RetTo_object_(&v6, &gFT->pTextRing);
      v6 = klass;
      --gFT->TextHandleNums;
    }
    while (klass);
    monitor = pBuf[4].monitor;
    goto LABEL_5;
  }
  return 0;
}

// 0x1c3cda0
FontReq_t *frDestroyFontRequestAfter(FontReq_t *pFRQ) {
  FontReq_t *DestroyHandleList;
  Il2CppClass **v9;
  FontReq_t *v10;
  FontReq_t *head;
  FontReq_t *v12;
  FontReq_t *p_prev;
  FontReq_t *prev;
  FontReq_t *v15;

  DestroyHandleList = gFT->DestroyHandleList;
  v9 = &DestroyHandleList->obj.klass + FrameID;
  v10 = v9[4];
  if (v10)
  {
    if (pFRQ)
    {
      head = pFRQ->head;
      v10->next = head;
      v12 = pFRQ->head;
      if (v10->str)
      {
        v12->prev = v10;
        p_prev = &v12->prev;
        prev = v10;
      }
      else
      {
        prev = v10->prev;
        v12->prev = prev;
        p_prev = &v12->prev;
      }
      v15 = v10->head;
      pFRQ->head = v15;
    }
    else
    {
      pFRQ = v9[4];
    }
  }
  else if (!pFRQ)
  {
    goto LABEL_21;
  }
LABEL_21:
  v9[4] = pFRQ;
  return 0;
}

// 0x1c3c7c0
FontReq_t *frLinkFontString(char *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ) {
  u8 *v11;
  FontReq_t *v13;
  FontReq_t *v15;

  v11 = NewSpecific(byte, 4u);
  v13 = frSetFontString_2(v11, Style, ColNo, Tp, 0);
  if (!v13)
    return pFRQ;
  v15 = v13;
  return frCombineFontRequest(pFRQ, v15);
}

// 0x1c3d030
FontReq_t *frLinkFontString_2(u8 *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ) {
  FontReq_t *v11;
  FontReq_t *v13;

  v11 = frSetFontString_2(pStr, Style, ColNo, Tp, 0);
  if (!v11)
    return pFRQ;
  v13 = v11;
  return frCombineFontRequest(pFRQ, v13);
}

// 0x1c3d4d0
FontReq_t *frSetFontString(char *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ) {
  u8 *v11;

  v11 = NewSpecific(byte, 4u);
  return frSetFontString_2(v11, Style, ColNo, Tp, pFRQ);
}

// 0x1c3d100
FontReq_t *frSetFontString_2(u8 *pStr, s8 Style, s8 ColNo, s8 Tp, FontReq_t *pFRQ) {
  FontReq_t *v6;
  u32 max_length;
  Il2CppObject *v14;
  u8 v16;
  Text_t *str_end;
  s64 v18;
  u16 v19;
  Text_t *v21;
  Text_t *p_next;
  s32 v23;

  v6 = pFRQ;
  frSetFontString_style = 0;
  if (Style < 0)
  {
    max_length = pStr->max_length;
    if (v6)
      goto LABEL_5;
LABEL_13:
    v14 = RentFrom_object_(&gFT->pRequestRing);
    v6 = (FontReq_t *)v14;
    LOBYTE(v14[1].klass) = 0x80;
    BYTE2(v14[1].klass) = 0;
    ++gFT->FontHandleNums;
    *(void **)((char *)&v14[1].monitor + 4) = 0;
    *(Il2CppClass **)((char *)&v14[2].klass + 4) = 0;
    v14[4].monitor = 0;
    v6->next = 0;
    v6->head = v6;
    v6->str = 0;
    v6->str_end = 0;
    v6->strlen = 0;
    if (!max_length)
      return v6;
    goto LABEL_16;
  }
  frSetFontString_style = Style;
  max_length = pStr->max_length;
  if (!v6)
    goto LABEL_13;
LABEL_5:
  if (!max_length)
    return v6;
LABEL_16:
  v16 = pStr[0];
  if (v16)
  {
    str_end = v6->str_end;
    LODWORD(v18) = 0;
    while (1)
    {
      v19 = v16;
      if ((v16 & 0x80) != 0)
      {
        v18 = (u32)(v18 + 1);
        v19 = pStr[v18] | (v16 << 8);
        goto LABEL_20;
      }
      else
      {
        goto LABEL_20;
      }
LABEL_20:
      v21 = frSetFont(v19, frSetFontString_style, ColNo, Tp);
      if (str_end)
        p_next = &str_end->next;
      else
        p_next = &v6->str;
      p_next = v21;
      v21->prev = str_end;
      LODWORD(v18) = v18 + 1;
      v23 = v6->strlen + 1;
      v6->w_pxls += v21->lw;
      v6->strlen = v23;
      if ((u32)v18 >= max_length)
        goto LABEL_30;
      str_end = v21;
      v16 = pStr[(u32)v18];
      if (!v16)
        goto LABEL_29;
    }
  }
  v21 = 0;
LABEL_29:
  if (v21)
  {
LABEL_30:
    v6->str_end = v21;
    v6->x_size = v21->width;
    v6->y_size = v21->height;
  }
  return v6;
}

// 0x1c3c900
void frSetDrawSpeed(FontReq_t *pFRQ, u8 Speed) {
  u8 v3;

  if (Speed >= 0x41u)
    v3 = 0x80;
  else
    v3 = 2 * Speed;
  pFRQ->draw_spd = v3;
}

// 0x1c3d580
void frSetFontSpace(FontReq_t *pFRQ, s32 Space) {
  s8 v3;
  Text_t *str;
  s32 v7;

  v3 = Space;
  pFRQ->space = Space;
  str = pFRQ->str;
  if (!str)
  {
    pFRQ->w_pxls = 0;
    return;
  }
  v7 = 0;
  do
  {
    v7 += pFRQ->space + str->lw;
    str = str->next;
  }
  while (str);
  pFRQ->w_pxls = v7;
}

// 0x1c3c920
void frSetDrawPosition(FontReq_t *pFRQ, s32 X, s32 Y) {
  pFRQ->x = X;
  pFRQ->y = Y;
}

// 0x1c3d680
void frSetFontColorNo(FontReq_t *pFRQ, u8 ColorNo) {
  Text_t *i;

  for (; pFRQ; pFRQ = pFRQ->prev)
  {
    for (i = pFRQ->str; i; i = i->next)
      i->col_no = ColorNo;
  }
}

// 0x1c3d6b0
void frSetFontColor(FontReq_t *pFRQ, u32 Color) {
  Text_t *i;

  for (; pFRQ; pFRQ = pFRQ->prev)
  {
    for (i = pFRQ->str; i; i = i->next)
      i->color = Color;
  }
}

// 0x1c3d6e0
void frSetFontColorAlf(FontReq_t *pFRQ, u32 Color) {
  Text_t *i;

  for (; pFRQ; pFRQ = pFRQ->prev)
  {
    for (i = pFRQ->str; i; i = i->next)
      i->color = i->color & 0xFFFFFF00 | Color;
  }
}

// 0x1c34050
u8 frEnableMode(s8 Flag) {
  u8 result;

  result = gModeFlag;
  gModeFlag = result | Flag;
  return result;
}

// 0x1c340c0
u8 frDisableMode(s8 Flag) {
  u8 result;

  result = gModeFlag;
  gModeFlag = result & ~Flag;
  return result;
}

// 0x1c3d720
void frSetFontDrawOT(u32 OtType) {
  gFontDrawOT = OtType;
  return;
}

// 0x1c3d7b0
s32 frDrawFont(FontReq_t *pFRQ) {
  return 0;
}

// 0x1c3d7c0
s32 frDrawFontEx(FontReq_t *pFRQ, s8 Mode) {
  return 0;
}

// 0x1c3d7d0
s32 frDrawFontEx2(FontReq_t *pFRQ, s8 Mode, u32 Ot) {
  return 0;
}

// 0x1c3d7e0
dds3ProcessFunc_t frFlipPacketBuf(dds3ProcessID_t *id) {
  Il2CppClass **v7;
  FontReq_t *v8;

  v7 = &gFT->DestroyHandleList->obj.klass + (FrameID == 0);
  v8 = v7[4];
  v7 += 4;
  frDestroyFontRequestNow(v8);
  *v7 = 0;
  return 0;
}

// 0x1c3d3c0
FontReq_t *frCombineFontRequest(FontReq_t *pFRQ1, FontReq_t *pFRQ2) {
  FontReq_t *head;
  FontReq_t *v8;
  FontReq_t *p_prev;
  FontReq_t *prev;
  FontReq_t *v11;
  s32 y;

  if (!pFRQ1)
    return pFRQ2;
  if (!pFRQ2)
    return pFRQ1;
  head = pFRQ2->head;
  pFRQ1->next = head;
  v8 = pFRQ2->head;
  if (pFRQ1->str)
  {
    v8->prev = pFRQ1;
    p_prev = &v8->prev;
    prev = pFRQ1;
  }
  else
  {
    prev = pFRQ1->prev;
    v8->prev = prev;
    p_prev = &v8->prev;
  }
  v11 = pFRQ1->head;
  pFRQ2->head = v11;
  y = pFRQ1->y;
  pFRQ2->x = pFRQ1->x + 16 * pFRQ1->w_pxls;
  pFRQ2->y = y;
  return pFRQ2;
}

// 0x1c3cf70
FontReq_t *frCombineFontRequestEx(FontReq_t *pFRQ1, FontReq_t *pFRQ2, u32 Mode) {
  FontReq_t *v4;
  FontReq_t *head;
  FontReq_t *p_head;
  FontReq_t *v9;
  FontReq_t *p_prev;
  FontReq_t *prev;
  FontReq_t *v13;
  s32 y;

  v4 = pFRQ2;
  if (!pFRQ1)
    return v4;
  if (!pFRQ2)
    return pFRQ1;
  p_head = &pFRQ2->head;
  head = pFRQ2->head;
  pFRQ1->next = head;
  v9 = p_head;
  if (pFRQ1->str)
  {
    v9->prev = pFRQ1;
    p_prev = &v9->prev;
    prev = pFRQ1;
  }
  else
  {
    prev = pFRQ1->prev;
    v9->prev = prev;
    p_prev = &v9->prev;
  }
  v13 = pFRQ1->head;
  p_head = v13;
  if (Mode != 1)
    return v4;
  y = pFRQ1->y;
  v4->x = pFRQ1->x + 16 * pFRQ1->w_pxls;
  v4->y = y;
  return v4;
}

// 0x1c3d640
s32 frGetStrWidth(FontReq_t *pFRQ) {
  Text_t *str;
  s32 result;
  s32 space;

  str = pFRQ->str;
  if (!str)
    return 0;
  result = 0;
  space = pFRQ->space;
  do
  {
    result += str->lw + space;
    str = str->next;
  }
  while (str);
  return result;
}

// 0x1c3d910
s32 frPreCalcStrWidth(char *pStr, FR_STYLE Style, s8 Mode) {
  u8 v5;
  Text_t *v7;
  s32 stringLength;

  v5 = Style;
  v7 = Allocate(Text_t);
  _ctor(v7, 0);
  stringLength = pStr->_stringLength;
  v7->lw = 0;
  v7->style = v5;
  v7->mode = Mode;
  return 24 * stringLength;
}

// 0x1c3d9a0
u8 *MessageNumSearch(s32 Index, u8 *pData, s32 Size) {
  void *v6;
  s32 v7;
  s32 v8;
  s32 v9;

  v6 = 0;
  if (ToInt32(pData, 24, 0) > Index)
  {
    v7 = ToInt32(pData, 8 * Index + 36, 0);
    v8 = v7 + 4 * ToInt16(pData, v7 + 56, 0);
    v9 = ToInt32(pData, v8 + 60, 0);
    v6 = NewSpecific(byte, v9);
    Copy_56175392(pData, v8 + 64, v6, 0, v9, 0);
  }
  return v6;
}

// 0x1c39b00
static void frMessageReturnCode(frMsgInfo_t *pMsgInfo) {
  s32 Y;
  f32 v5;
  s32 v6;

  Y = pMsgInfo->Y;
  v5 = (f32)gMessageStepY * 2.25;
  v6 = 8 * (s32)v5;
  if (v5 == INFINITY)
    v6 = 0;
  pMsgInfo->Y = v6 + Y;
  *(u16 *)&pMsgInfo->FrqFlag = 257;
}

// 0x1c3dab0
FontReq_t *itfMessageRequestExLocalize(s32 x, s32 y, u8 Style, u8 ColNo, u8 Tp, u8 Spd, u8 *pMsg, FontReq_t *pFRQ, bool spc, bool hitokoto, bool logmes) {
  frMsgInfo_t *v19;
  void *v21;

  v19 = Allocate(frMsgInfo_t);
  v19->X = x;
  v19->Y = y;
  v19->Z = 0;
  v19->Style = Style;
  v19->ColNo = ColNo;
  v19->Tp = Tp;
  v19->Spd = DisplaySpeed();
  v21 = NewSpecific(byte, pMsg->max_length);
  v19->pMsg = v21;
  Copy_56180528(pMsg, v19->pMsg, pMsg->max_length, 0);
  v19->pFRQ = pFRQ;
  v19->Ofs = 0;
  *(u16 *)&v19->FrqFlag = 257;
  return frAnalyzeMessageLocalize(v19, spc, hitokoto, logmes);
}

// 0x1c3dc20
FontReq_t *MessageRequestNS(s32 X, s32 Y, u32 Z, u8 Style, u8 ColNo, u8 Tp, u8 Spd, u8 *pMsg, FontReq_t *pFRQ) {
  return itfMessageRequestExLocalize(X, Y, Style, ColNo, Tp, Tp, pMsg, 0, 1, 1, 0);
}

// 0x1c3dce0
u32 frGetMessageResult(u32 Flag) {
  return gMessageRequestResult & Flag;
}

// 0x1c3dd50
void frSetVariableRequest(s32 VarNo, char *pStr) {
  s64 v6;

  v6 = (s64)gVarStr + 8 * VarNo;
  *(u64 *)(v6 + 32) = pStr;
}

// 0x1c3c470
char *frGetVariableRequest(s32 VarNo) {
  return gVarStr[VarNo];
}

// 0x1c3ddd0
void *itfGetLabelToString(char *label, bool is_spk, u8 ColNo) {
  u32 col_no;
  const MethodInfo_33522B0 *v7;
  void *ASCII;
  s64 v9;
  void *v10;
  s64 v11;
  s64 size;
  u8 v13;
  u64 *v14;
  u8 *items;
  s64 v16;
  u64 *v17;
  u8 *v18;
  u8 v19;
  u8 *v20;
  FontReq_t *v21;
  FontReq_t *v22;
  FontReq_t *prev;
  Text_t *i;
  u8 v26;
  void *v27;
  Il2CppObject *v28;
  u16 *v29;
  char *String_54864672;
  char *v34;
  Il2CppObject *v36;
  char *v40;
  s64 v41;
  System_ValueTuple_T1__T2__o v42;
  System_ValueTuple_string__byte__o result;

  col_no = ColNo;
  if (IsNullOrEmpty(label, 0))
    goto LABEL_22;
  ASCII = get_ASCII(0);
  v9 = (ASCII->klass->vtable._16_GetBytes.methodPtr)(ASCII, label, ASCII->klass->vtable._16_GetBytes.method);
  v10 = Allocate(System_Collections_Generic_List_byte_);
  __ctor(v10);
  if (*(s32 *)(v9 + 24) >= 1)
  {
    v11 = 0;
    do
    {
      while (1)
      {
        size = v10->_size;
        v13 = *(u8 *)(v9 + 32 + v11);
        v14 = Method_System_Collections_Generic_List_byte__Add__;
        ++v10->_version;
        items = v10->_items;
        if ((u32)size < LODWORD(items->max_length))
          break;
        _AddWithResize(v10, v13, *(const MethodInfo_2D54680 **)(*(u64 *)(v14[4] + 192) + 112));
        if (++v11 >= *(s32 *)(v9 + 24))
          goto LABEL_9;
      }
      v10->_size = size + 1;
      items[size] = v13;
      ++v11;
    }
    while (v11 < *(s32 *)(v9 + 24));
  }
LABEL_9:
  v16 = v10->_size;
  v17 = Method_System_Collections_Generic_List_byte__Add__;
  ++v10->_version;
  v18 = v10->_items;
  if ((u32)v16 >= LODWORD(v18->max_length))
  {
    _AddWithResize(v10, 0, *(const MethodInfo_2D54680 **)(*(u64 *)(v17[4] + 192) + 112));
  }
  else
  {
    v10->_size = v16 + 1;
    v18[v16] = 0;
  }
  v20 = _ToArray(v10);
  v21 = itfMessageRequestExLocalize(0, 0, 0, col_no, 0, v19, v20, 0, 1, 0, 1);
  if (!v21)
  {
LABEL_22:
    v42.Item2 = "";
    v40 = 0;
    v41 = 0;
    v26 = Method_System_ValueTuple_string__byte___ctor__;
    v42.Item1 = &v40;
    goto LABEL_37;
  }
  v22 = v21;
  col_no = v21->str->col_no;
  prev = v22;
  do
  {
    for (i = prev->str; i; i = i->next)
      LOBYTE(i->color) = 0x80;
    prev = prev->prev;
  }
  while (prev);
  v27 = Allocate(UnityEngine_GameObject);
  _ctor(v27, "empty", 0);
  v28 = AddComponent_object_(v27);
  v29 = NewSpecific(char, 0x400u);
  String_54864672 = CreateString_54864672(0, v29, 0);
  (v28->klass->vtable[66].methodPtr)(v28, String_54864672, v28->klass->vtable[66].method);
  if (!is_spk)
  {
    DrawMessageSub(v22, 0, v28, 1);
    goto LABEL_32;
  }
  v34 = sub_1C88420(v22, 0);
  if (!IsNullOrEmpty(v34, 0))
    (v28->klass->vtable[66].methodPtr)(v28, v34, v28->klass->vtable[66].method);
LABEL_32:
  v36 = (v28->klass->vtable[65].methodPtr)(v28, v28->klass->vtable[65].method);
  frDestroyFontRequestNow(v22);
  Destroy_61007920(v27, 0);
  v26 = Method_System_ValueTuple_string__byte___ctor__;
  v42.Item1 = &v40;
  v42.Item2 = v36;
  v40 = 0;
  v41 = 0;
LABEL_37:
  byte____ctor(v42, col_no, v26, v7);
  result.Item1 = v40;
  *(u64 *)&result.Item2 = v41;
  return result;
}

// 0x1c3ed30
char *itfRepColTag(char *txt, u32 col) {
  Il2CppObject *v5;
  char *v6;
  char *v7;
  s32 v8;
  s32 i;
  s32 v10;
  char *v11;
  char *v12;
  char *v13;
  Il2CppObject *v14;
  char *v15;
  u32 v17;
  u32 data;

  data = col;
  v5 = Box(uint, &data);
  v6 = Format("<color=#{0:X8}>", v5, 0);
  v7 = Concat_54766928(v6, txt, 0);
  v8 = IndexOf_54852400(v7, "<COLOR", 0, 0);
  if (v8 != -1)
  {
    for (i = v8; i != -1; i = IndexOf_54852400(v7, "<COLOR", i, 0))
    {
      v10 = IndexOf_54852400(v7, ">", i + 6, 0);
      if (v10 == -1)
        break;
      v11 = Substring_54838176(v7, i, v10 - i + 1, 0);
      v12 = Substring_54838176(v11, 6, v11->_stringLength - 6, 0);
      v13 = Replace_54838864(v12, " ", "", 0);
      Replace_54838864(v13, ">", "", 0);
      v17 = col;
      v14 = Box(uint, &v17);
      v15 = Format("<color=\"#{0:X8}\">", v14, 0);
      v7 = Replace_54838864(v7, v11, v15, 0);
    }
  }
  return v7;
}

// 0x1c3ef30
s32 frGetMessageLineNums(FontReq_t *pFRQ) {
  FontReq_t *head;
  FontReq_t *next;

  if (pFRQ)
  {
    head = pFRQ->head;
    if (head)
    {
      LODWORD(pFRQ) = 0;
      do
      {
        next = head;
        do
        {
          if (next->y >= head->y + 100)
            break;
          next = next->next;
        }
        while (next);
        head = head->next;
        LODWORD(pFRQ) = (u32)pFRQ + 1;
      }
      while (head);
    }
    else
    {
      LODWORD(pFRQ) = 0;
    }
  }
  return (s32)pFRQ;
}

// 0x1c3ef80
void frSetMessageCenter(s32 X, s32 Y, FontReq_t *pFRQ) {
  FontReq_t *head;
  s32 v8;
  s32 v9;
  FontReq_t *next;
  s32 v11;
  s32 v12;
  Text_t *str;
  u32 v14;
  s32 v15;
  s32 v16;

  if (pFRQ)
  {
    head = pFRQ->head;
    v8 = Y - head->y;
    while (1)
    {
      v9 = 0;
      next = head;
      v11 = head->y + 100;
      while (next->y < v11)
      {
        str = next->str;
        if (str)
        {
          v12 = 0;
          do
          {
            v12 += next->space + str->lw;
            str = str->next;
          }
          while (str);
          goto LABEL_7;
        }
        v12 = 0;
LABEL_7:
        next = next->next;
        v9 += v12;
        if (!next)
          break;
      }
      if (v9 >= 0)
        v14 = v9;
      else
        v14 = v9 + 1;
      v15 = X - 16 * (v14 >> 1) - head->x;
      while (1)
      {
        v16 = head->y;
        if (v16 >= v11)
          break;
        head->x += v15;
        head->y = v8 + v16;
        head = head->next;
        if (!head)
          return;
      }
    }
  }
}

// 0x1c3f0c0
s32 frGetLipsTarget(void) {
  return gLipsTarget;
}

// 0x1c3f140
s32 frGetLipsType(void) {
  return gLipsType;
}

// 0x1c3f1c0
void itfFontColorTextUnity2(char *_str, u32 _col, void *_tmPro, bool _num, s32 _ex, char *_tag) {
  f32 v14;
  s32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;

  if (op_Equality(tmPro, 0, 0))
    return;
  if (num)
  {
    str = itfConvertToDelimitedNum(str);
  }
  (tmPro->klass->vtable._66_set_text.methodPtr)(tmPro, str, tmPro->klass->vtable._66_set_text.method);
  if (col <= 0x64E6AA80)
  {
    if (col > 0x40804080)
    {
      v14 = 145.0;
      v17 = 144.0;
      if (col != 1296780109)
      {
        v16 = 145.0;
        if (col == 1349079155)
          goto LABEL_44;
        if (col == 1692838528)
        {
          if (ex)
            v14 = 255.0;
          else
            v14 = 235.0;
          if (ex)
            v17 = 0.0;
          else
            v17 = 255.0;
          if (ex)
            v16 = 50.0;
          else
            v16 = 140.0;
          goto LABEL_44;
        }
        goto LABEL_39;
      }
    }
    else
    {
      if (col != 1)
      {
        if (col == 2)
        {
          v14 = 150.0;
          v15 = 1130889216;
          goto LABEL_42;
        }
        if (col == 1082146944)
        {
          v14 = 145.0;
          v15 = 1125122048;
LABEL_42:
          v17 = *(f32 *)&v15;
          goto LABEL_43;
        }
LABEL_39:
        v14 = 217.0;
        v15 = 1129775104;
        goto LABEL_42;
      }
      v17 = 0.0;
      v14 = 255.0;
    }
LABEL_43:
    v16 = v14;
    goto LABEL_44;
  }
  if (col > 0x754B3D80)
  {
    v14 = 217.0;
    v17 = 215.0;
    if (col == -2139062144 || col == -1600273536)
      goto LABEL_43;
    v16 = 217.0;
    if (col == -1264556928)
      goto LABEL_44;
    goto LABEL_39;
  }
  switch (col)
  {
    case 0x6E4040FFu:
      v14 = 32.0;
      v16 = 73.0;
      v17 = 216.0;
      break;
    case 0x6E80FF80u:
      v16 = 255.0;
      v14 = 104.0;
      v17 = 40.0;
      break;
    case 0x754B3D80u:
      v14 = 16.0;
      v16 = 48.0;
      v17 = 200.0;
      break;
    default:
      goto LABEL_39;
  }
LABEL_44:
  v18 = (tmPro->klass->vtable._22_get_color.methodPtr)(tmPro, tmPro->klass->vtable._22_get_color.method);
  if ((f32)((f32)((f32)(v19 + -1.0) * (f32)(v19 + -1.0)) + (f32)((f32)((f32)(v21 - (f32)(v16 / 255.0)) * (f32)(v21 - (f32)(v16 / 255.0))) + (f32)((f32)((f32)(v18 - (f32)(v17 / 255.0)) * (f32)(v18 - (f32)(v17 / 255.0))) + (f32)((f32)(v20 - (f32)(v14 / 255.0)) * (f32)(v20 - (f32)(v14 / 255.0)))))) >= 9.9999994e-11)
    (tmPro->klass->vtable._23_set_color.methodPtr)(tmPro, tmPro->klass->vtable._23_set_color.method);
}

// 0x1c3f560
char *itfConvertToDelimitedNum(char *_num) {
  u32 v5;
  void *InvariantCulture;
  char *v8;
  s32 result;

  result = 0;
  if (!TryParse(num, &result, 0))
    return num;
  if (num->_stringLength - 1 >= 3)
  {
    InvariantCulture = get_InvariantCulture(0);
    num = ToString_55997200((s32)&result, "#,0", InvariantCulture, 0);
LABEL_6:
    goto LABEL_7;
  }
  else
  {
    goto LABEL_6;
  }
LABEL_7:
  v5 = GetLanguageID() - 1;
  if (v5 > 3)
    return num;
  v8 = *(&off_4CD9AF8)[v5];
  if (!v8)
    return num;
  return Replace_54838864(num, ",", v8, 0);
}

// 0x1c3f8f0
static char *GetCommaChgPar(void) {
  u32 v2;
  char *result;

  v2 = GetLanguageID() - 1;
  switch (v2)
  {
    case 0u:
    case 3u:
      result = " ";
      break;
    case 1u:
    case 2u:
      result = ".";
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1c3f740
sdfColor32_t itfGetFontColorUnity2(u32 _color, bool _num, s32 _ex) {
  if (color > 0x64E6AA80)
  {
    if (color > 0x754B3D80)
      return (sdfColor32_t)4292467159LL;
    switch (color)
    {
      case 0x6E4040FFu:
        return (sdfColor32_t)4282982616LL;
      case 0x6E80FF80u:
        return (sdfColor32_t)4294928424LL;
      case 0x754B3D80u:
        return (sdfColor32_t)4281340104LL;
      default:
        return (sdfColor32_t)4292467159LL;
    }
  }
  else if (color > 0x40804080)
  {
    if (color == 1296780109 || color == 1349079155)
      return (sdfColor32_t)4287730064LL;
    if (color != 1692838528)
      return (sdfColor32_t)4292467159LL;
    if (ex)
      return (sdfColor32_t)4281532160LL;
    else
      return (sdfColor32_t)4287425535LL;
  }
  else
  {
    switch (color)
    {
      case 1u:
        return (sdfColor32_t)4294967040LL;
      case 2u:
        return (sdfColor32_t)4288059112LL;
      case 0x40804080u:
        return (sdfColor32_t)4287730064LL;
      default:
        return (sdfColor32_t)4292467159LL;
    }
  }
}

// 0x1c3f9e0
static void frInitUvTable(void) {
  ;
}

// 0x1c3fa20
char *itfTextSetSprite(s32 type) {
  if ((u32)(type - 10) > 0x85)
    return "";
  else
    return *(&off_4CD9B18)[type - 10];
}

// 0x1c40070
char *itfTextBtnConvert(char *text, char *label) {
  char *v5;
  char *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  void *v21;
  void *v22;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *v29;
  void *v30;
  void *v31;
  void *v32;
  void *v33;
  void *v34;
  void *v35;
  void *v36;
  void *v37;
  void *v38;
  void *v39;
  void *v40;
  void *v41;
  void *v42;
  void *v43;
  void *v44;
  void *v45;
  void *v46;
  void *v47;
  void *v48;
  void *v49;
  void *v50;
  void *v51;
  void *v52;
  void *v53;
  void *v54;
  void *v55;
  void *v56;
  void *v57;
  void *v58;
  void *v59;
  void *v60;
  void *v61;

  if (!IsNullOrEmpty(label, 0))
  {
    v5 = Replace_54838864(label, "<", "", 0);
    v6 = Replace_54838864(v5, ">", "", 0);
    text = cfgGetBtnTagConfig(v6, text);
  }
  v7 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v7, text, 0);
  v8 = Replace(v7, "<BTN_A>", "<sprite name=button_a>", 0);
  v9 = Replace(v8, "<BTN_B>", "<sprite name=button_b>", 0);
  v10 = Replace(v9, "<BTN_X>", "<sprite name=button_x>", 0);
  v11 = Replace(v10, "<BTN_Y>", "<sprite name=button_y>", 0);
  v12 = Replace(v11, "<BTN_R1>", "<sprite name=button_r>", 0);
  v13 = Replace(v12, "<BTN_R2>", "<sprite name=button_zr>", 0);
  v14 = Replace(v13, "<BTN_R3>", "<sprite name=button_spush_r>", 0);
  v15 = Replace(v14, "<BTN_L1>", "<sprite name=button_l>", 0);
  v16 = Replace(v15, "<BTN_L2>", "<sprite name=button_zl>", 0);
  v17 = Replace(v16, "<BTN_L3>", "<sprite name=button_spush_l>", 0);
  v18 = Replace(v17, "<BTN_OP1>", "<sprite name=button_minus>", 0);
  v19 = Replace(v18, "<BTN_OP2>", "<sprite name=button_plus>", 0);
  v20 = Replace(v19, "<BTN_AL>", "<sprite name=button_ana_L>", 0);
  v21 = Replace(v20, "<BTN_ALU>", "<sprite name=button_ana_L_u>", 0);
  v22 = Replace(v21, "<BTN_ALD>", "<sprite name=button_ana_L_d>", 0);
  v23 = Replace(v22, "<BTN_ALL>", "<sprite name=button_ana_L_l>", 0);
  v24 = Replace(v23, "<BTN_ALR>", "<sprite name=button_ana_L_r>", 0);
  v25 = Replace(v24, "<BTN_AR>", "<sprite name=button_ana_R>", 0);
  v26 = Replace(v25, "<BTN_ARU>", "<sprite name=button_ana_R_u>", 0);
  v27 = Replace(v26, "<BTN_ARD>", "<sprite name=button_ana_R_d>", 0);
  v28 = Replace(v27, "<BTN_ARL>", "<sprite name=button_ana_R_l>", 0);
  v29 = Replace(v28, "<BTN_ARR>", "<sprite name=button_ana_R_r>", 0);
  v30 = Replace(v29, "<BTN_D>", "<sprite name=button_jyuuji>", 0);
  v31 = Replace(v30, "<BTN_DU>", "<sprite name=button_jyuuji_U>", 0);
  v32 = Replace(v31, "<BTN_DD>", "<sprite name=button_jyuuji_D>", 0);
  v33 = Replace(v32, "<BTN_DL>", "<sprite name=button_jyuuji_L>", 0);
  v34 = Replace(v33, "<BTN_DR>", "<sprite name=button_jyuuji_R>", 0);
  v35 = Replace(v34, "<BST_01>", "<sprite name=status_icon_1>", 0);
  v36 = Replace(v35, "<BST_02>", "<sprite name=status_icon_2>", 0);
  v37 = Replace(v36, "<BST_03>", "<sprite name=status_icon_3>", 0);
  v38 = Replace(v37, "<BST_04>", "<sprite name=status_icon_4>", 0);
  v39 = Replace(v38, "<BST_05>", "<sprite name=status_icon_5>", 0);
  v40 = Replace(v39, "<BST_06>", "<sprite name=status_icon_6>", 0);
  v41 = Replace(v40, "<BST_07>", "<sprite name=status_icon_7>", 0);
  v42 = Replace(v41, "<BST_08>", "<sprite name=status_icon_8>", 0);
  v43 = Replace(v42, "<BST_09>", "<sprite name=status_icon_9>", 0);
  v44 = Replace(v43, "<BST_10>", "<sprite name=status_icon_10>", 0);
  v45 = Replace(v44, "<BST_11>", "<sprite name=status_icon_11>", 0);
  v46 = Replace(v45, "<BST_12>", "<sprite name=status_icon_12>", 0);
  v47 = Replace(v46, "<BST_13>", "<sprite name=status_icon_13>", 0);
  v48 = Replace(v47, "<BST_14>", "<sprite name=status_icon_14>", 0);
  v49 = Replace(v48, "<BST_15>", "<sprite name=status_icon_15>", 0);
  v50 = Replace(v49, "<BST_16>", "<sprite name=status_icon_16>", 0);
  v51 = Replace(v50, "<BST_17>", "<sprite name=status_icon_17>", 0);
  v52 = Replace(v51, "<BST_18>", "<sprite name=status_icon_18>", 0);
  v53 = Replace(v52, "<BST_19>", "<sprite name=status_icon_19>", 0);
  v54 = Replace(v53, "<ICN_01>", "<sprite name=repeat_mark>", 0);
  v55 = Replace(v54, "<ICN_02>", "<sprite name=autohelp_icon_mokutekichi2>", 0);
  v56 = Replace(v55, "<ICN_03>", "<sprite name=efigs_icon_01>", 0);
  v57 = Replace(v56, "<ICN_04>", "<sprite name=efigs_icon_02>", 0);
  v58 = Replace(v57, "<ICN_05>", "<sprite name=efigs_icon_03>", 0);
  v59 = Replace(v58, "<ICN_06>", "<sprite name=efigs_icon_04>", 0);
  v60 = Replace(v59, "<ICN_07>", "<sprite name=efigs_icon_05>", 0);
  v61 = Replace(v60, "<ICN_08>", "<sprite name=efigs_icon_06>", 0);
  return ((char *(void *, const MethodInfo *))v61->klass->vtable._3_ToString.methodPtr)(v61, v61->klass->vtable._3_ToString.method);
}

// 0x1c3a720
void *itfTextBtnConvertBuild(void *str) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  void *v21;
  void *v22;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *v29;
  void *v30;
  void *v31;
  void *v32;
  void *v33;
  void *v34;
  void *v35;
  void *v36;
  void *v37;
  void *v38;
  void *v39;
  void *v40;
  void *v41;
  void *v42;
  void *v43;
  void *v44;
  void *v45;
  void *v46;
  void *v47;
  void *v48;
  void *v49;
  void *v50;
  void *v51;
  void *v52;
  void *v53;
  void *v54;
  void *v55;

  v3 = Replace(str, "<BTN_A>", "<sprite name=button_a>", 0);
  v4 = Replace(v3, "<BTN_B>", "<sprite name=button_b>", 0);
  v5 = Replace(v4, "<BTN_X>", "<sprite name=button_x>", 0);
  v6 = Replace(v5, "<BTN_Y>", "<sprite name=button_y>", 0);
  v7 = Replace(v6, "<BTN_R1>", "<sprite name=button_r>", 0);
  v8 = Replace(v7, "<BTN_R2>", "<sprite name=button_zr>", 0);
  v9 = Replace(v8, "<BTN_R3>", "<sprite name=button_spush_r>", 0);
  v10 = Replace(v9, "<BTN_L1>", "<sprite name=button_l>", 0);
  v11 = Replace(v10, "<BTN_L2>", "<sprite name=button_zl>", 0);
  v12 = Replace(v11, "<BTN_L3>", "<sprite name=button_spush_l>", 0);
  v13 = Replace(v12, "<BTN_OP1>", "<sprite name=button_minus>", 0);
  v14 = Replace(v13, "<BTN_OP2>", "<sprite name=button_plus>", 0);
  v15 = Replace(v14, "<BTN_AL>", "<sprite name=button_ana_L>", 0);
  v16 = Replace(v15, "<BTN_ALU>", "<sprite name=button_ana_L_u>", 0);
  v17 = Replace(v16, "<BTN_ALD>", "<sprite name=button_ana_L_d>", 0);
  v18 = Replace(v17, "<BTN_ALL>", "<sprite name=button_ana_L_l>", 0);
  v19 = Replace(v18, "<BTN_ALR>", "<sprite name=button_ana_L_r>", 0);
  v20 = Replace(v19, "<BTN_AR>", "<sprite name=button_ana_R>", 0);
  v21 = Replace(v20, "<BTN_ARU>", "<sprite name=button_ana_R_u>", 0);
  v22 = Replace(v21, "<BTN_ARD>", "<sprite name=button_ana_R_d>", 0);
  v23 = Replace(v22, "<BTN_ARL>", "<sprite name=button_ana_R_l>", 0);
  v24 = Replace(v23, "<BTN_ARR>", "<sprite name=button_ana_R_r>", 0);
  v25 = Replace(v24, "<BTN_D>", "<sprite name=button_jyuuji>", 0);
  v26 = Replace(v25, "<BTN_DU>", "<sprite name=button_jyuuji_U>", 0);
  v27 = Replace(v26, "<BTN_DD>", "<sprite name=button_jyuuji_D>", 0);
  v28 = Replace(v27, "<BTN_DL>", "<sprite name=button_jyuuji_L>", 0);
  v29 = Replace(v28, "<BTN_DR>", "<sprite name=button_jyuuji_R>", 0);
  v30 = Replace(v29, "<BST_01>", "<sprite name=status_icon_1>", 0);
  v31 = Replace(v30, "<BST_02>", "<sprite name=status_icon_2>", 0);
  v32 = Replace(v31, "<BST_03>", "<sprite name=status_icon_3>", 0);
  v33 = Replace(v32, "<BST_04>", "<sprite name=status_icon_4>", 0);
  v34 = Replace(v33, "<BST_05>", "<sprite name=status_icon_5>", 0);
  v35 = Replace(v34, "<BST_06>", "<sprite name=status_icon_6>", 0);
  v36 = Replace(v35, "<BST_07>", "<sprite name=status_icon_7>", 0);
  v37 = Replace(v36, "<BST_08>", "<sprite name=status_icon_8>", 0);
  v38 = Replace(v37, "<BST_09>", "<sprite name=status_icon_9>", 0);
  v39 = Replace(v38, "<BST_10>", "<sprite name=status_icon_10>", 0);
  v40 = Replace(v39, "<BST_11>", "<sprite name=status_icon_11>", 0);
  v41 = Replace(v40, "<BST_12>", "<sprite name=status_icon_12>", 0);
  v42 = Replace(v41, "<BST_13>", "<sprite name=status_icon_13>", 0);
  v43 = Replace(v42, "<BST_14>", "<sprite name=status_icon_14>", 0);
  v44 = Replace(v43, "<BST_15>", "<sprite name=status_icon_15>", 0);
  v45 = Replace(v44, "<BST_16>", "<sprite name=status_icon_16>", 0);
  v46 = Replace(v45, "<BST_17>", "<sprite name=status_icon_17>", 0);
  v47 = Replace(v46, "<BST_18>", "<sprite name=status_icon_18>", 0);
  v48 = Replace(v47, "<BST_19>", "<sprite name=status_icon_19>", 0);
  v49 = Replace(v48, "<ICN_01>", "<sprite name=repeat_mark>", 0);
  v50 = Replace(v49, "<ICN_02>", "<sprite name=autohelp_icon_mokutekichi2>", 0);
  v51 = Replace(v50, "<ICN_03>", "<sprite name=efigs_icon_01>", 0);
  v52 = Replace(v51, "<ICN_04>", "<sprite name=efigs_icon_02>", 0);
  v53 = Replace(v52, "<ICN_05>", "<sprite name=efigs_icon_03>", 0);
  v54 = Replace(v53, "<ICN_06>", "<sprite name=efigs_icon_04>", 0);
  v55 = Replace(v54, "<ICN_07>", "<sprite name=efigs_icon_05>", 0);
  return Replace(v55, "<ICN_08>", "<sprite name=efigs_icon_06>", 0);
}

// 0x1c40dc0
char *itfTextItmConvert(char *text) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;

  v3 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v3, text, 0);
  v4 = Replace(v3, "<ITM_01>", "<sprite name=item_icon_01>", 0);
  v5 = Replace(v4, "<ITM_02>", "<sprite name=item_icon_02>", 0);
  v6 = Replace(v5, "<ITM_03>", "<sprite name=item_icon_03>", 0);
  v7 = Replace(v6, "<ITM_04>", "<sprite name=item_icon_04>", 0);
  v8 = Replace(v7, "<ITM_05>", "<sprite name=item_icon_05>", 0);
  v9 = Replace(v8, "<ITM_06>", "<sprite name=item_icon_06>", 0);
  v10 = Replace(v9, "<ITM_07>", "<sprite name=item_icon_07>", 0);
  v11 = Replace(v10, "<ITM_08>", "<sprite name=menu_icon_16>", 0);
  v12 = Replace(v11, "<ITM_09>", "<sprite name=menu_icon_18>", 0);
  v13 = Replace(v12, "<ITM_10>", "<sprite name=menu_icon_17>", 0);
  v14 = Replace(v13, "<ITM_11>", "<sprite name=menu_icon_19>", 0);
  v15 = Replace(v14, "<ITM_12>", "<sprite name=menu_icon_20>", 0);
  v16 = Replace(v15, "<ITM_13>", "<sprite name=menu_icon_21>", 0);
  v17 = Replace(v16, "<ITM_14>", "<sprite name=menu_icon_22>", 0);
  return ((char *(void *, const MethodInfo *))v17->klass->vtable._3_ToString.methodPtr)(v17, v17->klass->vtable._3_ToString.method);
}

// 0x1c3b340
void *itfTextItmConvertBuild(void *str) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;

  v3 = Replace(str, "<ITM_01>", "<sprite name=item_icon_01>", 0);
  v4 = Replace(v3, "<ITM_02>", "<sprite name=item_icon_02>", 0);
  v5 = Replace(v4, "<ITM_03>", "<sprite name=item_icon_03>", 0);
  v6 = Replace(v5, "<ITM_04>", "<sprite name=item_icon_04>", 0);
  v7 = Replace(v6, "<ITM_05>", "<sprite name=item_icon_05>", 0);
  v8 = Replace(v7, "<ITM_06>", "<sprite name=item_icon_06>", 0);
  v9 = Replace(v8, "<ITM_07>", "<sprite name=item_icon_07>", 0);
  v10 = Replace(v9, "<ITM_08>", "<sprite name=menu_icon_16>", 0);
  v11 = Replace(v10, "<ITM_09>", "<sprite name=menu_icon_18>", 0);
  v12 = Replace(v11, "<ITM_10>", "<sprite name=menu_icon_17>", 0);
  v13 = Replace(v12, "<ITM_11>", "<sprite name=menu_icon_19>", 0);
  v14 = Replace(v13, "<ITM_12>", "<sprite name=menu_icon_20>", 0);
  v15 = Replace(v14, "<ITM_13>", "<sprite name=menu_icon_21>", 0);
  return Replace(v15, "<ITM_14>", "<sprite name=menu_icon_22>", 0);
}

// 0x1c41160
char *itfTextSklConvert(char *text) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;

  v3 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v3, text, 0);
  v4 = Replace(v3, "<SKL_01>", "<sprite name=skill_icon_02>", 0);
  v5 = Replace(v4, "<SKL_04>", "<sprite name=skill_icon_03>", 0);
  v6 = Replace(v5, "<SKL_05>", "<sprite name=skill_icon_04>", 0);
  v7 = Replace(v6, "<SKL_06>", "<sprite name=skill_icon_05>", 0);
  v8 = Replace(v7, "<SKL_07>", "<sprite name=attribute_icon_01>", 0);
  v9 = Replace(v8, "<SKL_08>", "<sprite name=attribute_icon_02>", 0);
  v10 = Replace(v9, "<SKL_09>", "<sprite name=attribute_icon_03>", 0);
  v11 = Replace(v10, "<SKL_10>", "<sprite name=attribute_icon_04>", 0);
  v12 = Replace(v11, "<SKL_11>", "<sprite name=attribute_icon_05>", 0);
  v13 = Replace(v12, "<SKL_12>", "<sprite name=attribute_icon_06>", 0);
  v14 = Replace(v13, "<SKL_13>", "<sprite name=attribute_icon_11>", 0);
  v15 = Replace(v14, "<SKL_14>", "<sprite name=attribute_icon_10>", 0);
  v16 = Replace(v15, "<SKL_15>", "<sprite name=attribute_icon_08>", 0);
  v17 = Replace(v16, "<SKL_16>", "<sprite name=attribute_icon_09>", 0);
  v18 = Replace(v17, "<SKL_17>", "<sprite name=buff_icon_01>", 0);
  v19 = Replace(v18, "<SKL_18>", "<sprite name=buff_icon_02>", 0);
  v20 = Replace(v19, "<SKL_24>", "<sprite name=rai_skill_icon_18>", 0);
  return ((char *(void *, const MethodInfo *))v20->klass->vtable._3_ToString.methodPtr)(v20, v20->klass->vtable._3_ToString.method);
}

// 0x1c3b6a0
void *itfTextSklConvertBuild(void *str) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;

  v3 = Replace(str, "<SKL_01>", "<sprite name=skill_icon_02>", 0);
  v4 = Replace(v3, "<SKL_04>", "<sprite name=skill_icon_03>", 0);
  v5 = Replace(v4, "<SKL_05>", "<sprite name=skill_icon_04>", 0);
  v6 = Replace(v5, "<SKL_06>", "<sprite name=skill_icon_05>", 0);
  v7 = Replace(v6, "<SKL_07>", "<sprite name=attribute_icon_01>", 0);
  v8 = Replace(v7, "<SKL_08>", "<sprite name=attribute_icon_02>", 0);
  v9 = Replace(v8, "<SKL_09>", "<sprite name=attribute_icon_03>", 0);
  v10 = Replace(v9, "<SKL_10>", "<sprite name=attribute_icon_04>", 0);
  v11 = Replace(v10, "<SKL_11>", "<sprite name=attribute_icon_05>", 0);
  v12 = Replace(v11, "<SKL_12>", "<sprite name=attribute_icon_06>", 0);
  v13 = Replace(v12, "<SKL_13>", "<sprite name=attribute_icon_11>", 0);
  v14 = Replace(v13, "<SKL_14>", "<sprite name=attribute_icon_10>", 0);
  v15 = Replace(v14, "<SKL_15>", "<sprite name=attribute_icon_08>", 0);
  v16 = Replace(v15, "<SKL_16>", "<sprite name=attribute_icon_09>", 0);
  v17 = Replace(v16, "<SKL_17>", "<sprite name=buff_icon_01>", 0);
  v18 = Replace(v17, "<SKL_18>", "<sprite name=buff_icon_02>", 0);
  return Replace(v18, "<SKL_24>", "<sprite name=rai_skill_icon_18>", 0);
}

// 0x1c415a0
char *itfTextDepConvert(char *text) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;

  v3 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v3, text, 0);
  v4 = Replace(v3, "<DEP_01>", "<sprite name=zokusei_icon_01>", 0);
  v5 = Replace(v4, "<DEP_02>", "<sprite name=zokusei_icon_02>", 0);
  v6 = Replace(v5, "<DEP_03>", "<sprite name=zokusei_icon_03>", 0);
  v7 = Replace(v6, "<DEP_04>", "<sprite name=zokusei_icon_04>", 0);
  v8 = Replace(v7, "<DEP_05>", "<sprite name=zokusei_icon_05>", 0);
  v9 = Replace(v8, "<DEP_06>", "<sprite name=zokusei_icon_06>", 0);
  v10 = Replace(v9, "<DEP_07>", "<sprite name=zokusei_icon_07>", 0);
  v11 = Replace(v10, "<DEP_08>", "<sprite name=zokusei_icon_08>", 0);
  v12 = Replace(v11, "<DEP_09>", "<sprite name=zokusei_icon_09>", 0);
  return ((char *(void *, const MethodInfo *))v12->klass->vtable._3_ToString.methodPtr)(v12, v12->klass->vtable._3_ToString.method);
}

// 0x1c3bab0
void *itfTextDepConvertBuild(void *str) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;

  v3 = Replace(str, "<DEP_01>", "<sprite name=zokusei_icon_01>", 0);
  v4 = Replace(v3, "<DEP_02>", "<sprite name=zokusei_icon_02>", 0);
  v5 = Replace(v4, "<DEP_03>", "<sprite name=zokusei_icon_03>", 0);
  v6 = Replace(v5, "<DEP_04>", "<sprite name=zokusei_icon_04>", 0);
  v7 = Replace(v6, "<DEP_05>", "<sprite name=zokusei_icon_05>", 0);
  v8 = Replace(v7, "<DEP_06>", "<sprite name=zokusei_icon_06>", 0);
  v9 = Replace(v8, "<DEP_07>", "<sprite name=zokusei_icon_07>", 0);
  v10 = Replace(v9, "<DEP_08>", "<sprite name=zokusei_icon_08>", 0);
  return Replace(v10, "<DEP_09>", "<sprite name=zokusei_icon_09>", 0);
}

// 0x1c41820
char *itfTextMneConvert(char *text) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;

  v3 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v3, text, 0);
  v4 = Replace(v3, "<MNE_01>", "<sprite name=sub_title_icon_01>", 0);
  v5 = Replace(v4, "<MNE_02>", "<sprite name=menu_icon_01>", 0);
  v6 = Replace(v5, "<MNE_03>", "<sprite name=menu_icon_02>", 0);
  v7 = Replace(v6, "<MNE_04>", "<sprite name=menu_icon_03>", 0);
  v8 = Replace(v7, "<MNE_05>", "<sprite name=menu_icon_10>", 0);
  v9 = Replace(v8, "<MNE_06>", "<sprite name=menu_icon_11>", 0);
  v10 = Replace(v9, "<MNE_07>", "<sprite name=menu_icon_12>", 0);
  v11 = Replace(v10, "<MNE_08>", "<sprite name=menu_icon_05>", 0);
  v12 = Replace(v11, "<MNE_09>", "<sprite name=menu_icon_07>", 0);
  v13 = Replace(v12, "<MNE_10>", "<sprite name=menu_icon_15>", 0);
  v14 = Replace(v13, "<MNE_11>", "<sprite name=menu_icon_08>", 0);
  v15 = Replace(v14, "<MNE_12>", "<sprite name=menu_icon_09>", 0);
  v16 = Replace(v15, "<MNE_13>", "<sprite name=menu_icon_13>", 0);
  v17 = Replace(v16, "<MNE_14>", "<sprite name=menu_icon_14>", 0);
  v18 = Replace(v17, "<MNE_15>", "<sprite name=menu_icon_23>", 0);
  return ((char *(void *, const MethodInfo *))v18->klass->vtable._3_ToString.methodPtr)(v18, v18->klass->vtable._3_ToString.method);
}

// 0x1c3bd00
void *itfTextMneConvertBuild(void *str) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;

  v3 = Replace(str, "<MNE_01>", "<sprite name=sub_title_icon_01>", 0);
  v4 = Replace(v3, "<MNE_02>", "<sprite name=menu_icon_01>", 0);
  v5 = Replace(v4, "<MNE_03>", "<sprite name=menu_icon_02>", 0);
  v6 = Replace(v5, "<MNE_04>", "<sprite name=menu_icon_03>", 0);
  v7 = Replace(v6, "<MNE_05>", "<sprite name=menu_icon_10>", 0);
  v8 = Replace(v7, "<MNE_06>", "<sprite name=menu_icon_11>", 0);
  v9 = Replace(v8, "<MNE_07>", "<sprite name=menu_icon_12>", 0);
  v10 = Replace(v9, "<MNE_08>", "<sprite name=menu_icon_05>", 0);
  v11 = Replace(v10, "<MNE_09>", "<sprite name=menu_icon_07>", 0);
  v12 = Replace(v11, "<MNE_10>", "<sprite name=menu_icon_15>", 0);
  v13 = Replace(v12, "<MNE_11>", "<sprite name=menu_icon_08>", 0);
  v14 = Replace(v13, "<MNE_12>", "<sprite name=menu_icon_09>", 0);
  v15 = Replace(v14, "<MNE_13>", "<sprite name=menu_icon_13>", 0);
  v16 = Replace(v15, "<MNE_14>", "<sprite name=menu_icon_14>", 0);
  return Replace(v16, "<MNE_15>", "<sprite name=menu_icon_23>", 0);
}

// 0x1c41bf0
char *itfTextRaiConvert(char *text) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;
  void *v19;

  v3 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v3, text, 0);
  v4 = Replace(v3, "<RAI_01>", "<sprite name=rai_skill_icon_01>", 0);
  v5 = Replace(v4, "<RAI_02>", "<sprite name=rai_skill_icon_02>", 0);
  v6 = Replace(v5, "<RAI_03>", "<sprite name=rai_skill_icon_03>", 0);
  v7 = Replace(v6, "<RAI_04>", "<sprite name=rai_skill_icon_04>", 0);
  v8 = Replace(v7, "<RAI_05>", "<sprite name=rai_skill_icon_05>", 0);
  v9 = Replace(v8, "<RAI_06>", "<sprite name=rai_skill_icon_06>", 0);
  v10 = Replace(v9, "<RAI_07>", "<sprite name=rai_skill_icon_07>", 0);
  v11 = Replace(v10, "<RAI_08>", "<sprite name=rai_skill_icon_08>", 0);
  v12 = Replace(v11, "<RAI_09>", "<sprite name=rai_skill_icon_09>", 0);
  v13 = Replace(v12, "<RAI_10>", "<sprite name=rai_skill_icon_10>", 0);
  v14 = Replace(v13, "<RAI_11>", "<sprite name=rai_skill_icon_11>", 0);
  v15 = Replace(v14, "<RAI_12>", "<sprite name=rai_skill_icon_12>", 0);
  v16 = Replace(v15, "<RAI_13>", "<sprite name=rai_skill_icon_13>", 0);
  v17 = Replace(v16, "<RAI_15>", "<sprite name=rai_skill_icon_15>", 0);
  v18 = Replace(v17, "<RAI_16>", "<sprite name=rai_skill_icon_16>", 0);
  v19 = Replace(v18, "<RAI_17>", "<sprite name=rai_skill_icon_17>", 0);
  return ((char *(void *, const MethodInfo *))v19->klass->vtable._3_ToString.methodPtr)(v19, v19->klass->vtable._3_ToString.method);
}

// 0x1c3c0a0
void *itfTextRaiConvertBuild(void *str) {
  void *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;

  v3 = Replace(str, "<RAI_01>", "<sprite name=rai_skill_icon_01>", 0);
  v4 = Replace(v3, "<RAI_02>", "<sprite name=rai_skill_icon_02>", 0);
  v5 = Replace(v4, "<RAI_03>", "<sprite name=rai_skill_icon_03>", 0);
  v6 = Replace(v5, "<RAI_04>", "<sprite name=rai_skill_icon_04>", 0);
  v7 = Replace(v6, "<RAI_05>", "<sprite name=rai_skill_icon_05>", 0);
  v8 = Replace(v7, "<RAI_06>", "<sprite name=rai_skill_icon_06>", 0);
  v9 = Replace(v8, "<RAI_07>", "<sprite name=rai_skill_icon_07>", 0);
  v10 = Replace(v9, "<RAI_08>", "<sprite name=rai_skill_icon_08>", 0);
  v11 = Replace(v10, "<RAI_09>", "<sprite name=rai_skill_icon_09>", 0);
  v12 = Replace(v11, "<RAI_10>", "<sprite name=rai_skill_icon_10>", 0);
  v13 = Replace(v12, "<RAI_11>", "<sprite name=rai_skill_icon_11>", 0);
  v14 = Replace(v13, "<RAI_12>", "<sprite name=rai_skill_icon_12>", 0);
  v15 = Replace(v14, "<RAI_13>", "<sprite name=rai_skill_icon_13>", 0);
  v16 = Replace(v15, "<RAI_15>", "<sprite name=rai_skill_icon_15>", 0);
  v17 = Replace(v16, "<RAI_16>", "<sprite name=rai_skill_icon_16>", 0);
  return Replace(v17, "<RAI_17>", "<sprite name=rai_skill_icon_17>", 0);
}

// 0x1c42000
char *itfSystemTextBtnConvert(char *text, char *label) {
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  void *v21;
  void *v22;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *v29;
  void *v30;
  void *v31;
  void *v32;
  char *v33;
  char *v34;
  char *v35;

  v5 = Allocate(System_Text_StringBuilder);
  _ctor_56629520(v5, text, 0);
  v6 = Replace(v5, "<sprite name=button_a>", "<BTN_A>", 0);
  v7 = Replace(v6, "<sprite name=button_b>", "<BTN_B>", 0);
  v8 = Replace(v7, "<sprite name=button_x>", "<BTN_X>", 0);
  v9 = Replace(v8, "<sprite name=button_y>", "<BTN_Y>", 0);
  v10 = Replace(v9, "<sprite name=button_r>", "<BTN_R1>", 0);
  v11 = Replace(v10, "<sprite name=button_zr>", "<BTN_R2>", 0);
  v12 = Replace(v11, "<sprite name=button_spush_r>", "<BTN_R3>", 0);
  v13 = Replace(v12, "<sprite name=button_l>", "<BTN_L1>", 0);
  v14 = Replace(v13, "<sprite name=button_zl>", "<BTN_L2>", 0);
  v15 = Replace(v14, "<sprite name=button_spush_l>", "<BTN_L3>", 0);
  v16 = Replace(v15, "<sprite name=button_minus>", "<BTN_OP1>", 0);
  v17 = Replace(v16, "<sprite name=button_plus>", "<BTN_OP2>", 0);
  v18 = Replace(v17, "<sprite name=button_ana_L>", "<BTN_AL>", 0);
  v19 = Replace(v18, "<sprite name=button_ana_L_u>", "<BTN_ALU>", 0);
  v20 = Replace(v19, "<sprite name=button_ana_L_d>", "<BTN_ALD>", 0);
  v21 = Replace(v20, "<sprite name=button_ana_L_l>", "<BTN_ALL>", 0);
  v22 = Replace(v21, "<sprite name=button_ana_L_r>", "<BTN_ALR>", 0);
  v23 = Replace(v22, "<sprite name=button_ana_R>", "<BTN_AR>", 0);
  v24 = Replace(v23, "<sprite name=button_ana_R_u>", "<BTN_ARU>", 0);
  v25 = Replace(v24, "<sprite name=button_ana_R_d>", "<BTN_ARD>", 0);
  v26 = Replace(v25, "<sprite name=button_ana_R_l>", "<BTN_ARL>", 0);
  v27 = Replace(v26, "<sprite name=button_ana_R_r>", "<BTN_ARR>", 0);
  v28 = Replace(v27, "<sprite name=button_jyuuji>", "<BTN_D>", 0);
  v29 = Replace(v28, "<sprite name=button_jyuuji_U>", "<BTN_DU>", 0);
  v30 = Replace(v29, "<sprite name=button_jyuuji_D>", "<BTN_DD>", 0);
  v31 = Replace(v30, "<sprite name=button_jyuuji_L>", "<BTN_DL>", 0);
  v32 = Replace(v31, "<sprite name=button_jyuuji_R>", "<BTN_DR>", 0);
  v33 = Replace_54838864(label, "<", "", 0);
  v34 = Replace_54838864(v33, ">", "", 0);
  v35 = (v32->klass->vtable._3_ToString.methodPtr)(v32, v32->klass->vtable._3_ToString.method);
  return cfgGetBtnTagConfigSingle(v35, v34);
}

// 0x1c42720
static dds3ProcessFunc_t CountProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s8 *v5;
  s32 klass;
  s32 monitor_high;
  s64 v8;
  dds3ProcessFunc_t v9;
  s32 v11;
  s32 monitor;
  u32 *data;
  s32 v14;
  s32 v15;
  s16 v17;
  s32 v18;
  s32 v19;
  s64 v20;
  s32 v21;
  s32 v22;
  s16 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = NewSpecific(sbyte, 2u);
  monitor_high = HIDWORD(ProcessData[2].monitor);
  klass = ProcessData[3].klass;
  if (klass >= monitor_high)
  {
    v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v9, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v9;
  }
  v8 = v5;
  if (klass == monitor_high - 1)
  {
    HIDWORD(ProcessData[1].monitor) = ProcessData[1].monitor;
  }
  else
  {
    v11 = LODWORD(ProcessData[2].klass) + HIDWORD(ProcessData[1].monitor);
    monitor = ProcessData[1].monitor;
    HIDWORD(ProcessData[1].monitor) = v11;
    if (v11 >= monitor)
    {
      HIDWORD(ProcessData[1].monitor) = monitor;
      HIDWORD(ProcessData[2].monitor) = 0;
      LODWORD(ProcessData[3].klass) = 0;
    }
  }
  v5[0] = 0;
  data = ProcessData[1].klass->_1.byval_arg.data;
  if ((data[4] & 0x80000000) != 0)
    goto LABEL_30;
  v14 = *((u16 *)data + 17);
  if (v14 == 2)
  {
    v15 = HIDWORD(ProcessData[1].monitor) + data[5];
    data[4] = v15;
    goto LABEL_22;
  }
  if (v14 != 1)
  {
    v5[0] = 1;
    data = ProcessData[1].klass->_1.byval_arg.data;
    v17 = *((u16 *)data + 16);
    if ((v17 & 4) == 0)
      goto LABEL_27;
    goto LABEL_25;
  }
  v15 = data[5] - HIDWORD(ProcessData[1].monitor);
  data[4] = v15;
  data = ProcessData[1].klass->_1.byval_arg.data;
  v15 = data[4];
LABEL_22:
  ReturnNum[0] = v15;
  v17 = *((u16 *)data + 16);
  if ((v17 & 4) == 0)
    goto LABEL_27;
LABEL_25:
  v18 = data[6];
  if (data[4] <= v18)
  {
    data[4] = v18;
    *(u8 *)(v8 + 32) = 1;
    data = ProcessData[1].klass->_1.byval_arg.data;
    v17 = *((u16 *)data + 16);
  }
LABEL_27:
  if ((v17 & 2) != 0)
  {
    v19 = data[7];
    if (data[4] >= v19)
    {
      data[4] = v19;
LABEL_30:
      *(u8 *)(v8 + 32) = 1;
    }
  }
  *(u8 *)(v8 + 33) = 0;
  v20 = *(u64 *)&ProcessData[1].klass->_1.byval_arg.bits;
  if ((*(u32 *)(v20 + 16) & 0x80000000) != 0)
    goto LABEL_46;
  v21 = *(u16 *)(v20 + 34);
  if (v21 == 1)
  {
    v22 = *(u32 *)(v20 + 20) - HIDWORD(ProcessData[1].monitor);
    *(u32 *)(v20 + 16) = v22;
    goto LABEL_38;
  }
  if (v21 != 2)
  {
    *(u8 *)(v8 + 33) = 1;
    v20 = *(u64 *)&ProcessData[1].klass->_1.byval_arg.bits;
    v24 = *(u16 *)(v20 + 32);
    if ((v24 & 4) == 0)
      goto LABEL_43;
LABEL_41:
    v25 = *(u32 *)(v20 + 24);
    if (*(u32 *)(v20 + 16) <= v25)
    {
      *(u32 *)(v20 + 16) = v25;
      *(u8 *)(v8 + 33) = 1;
      v20 = *(u64 *)&ProcessData[1].klass->_1.byval_arg.bits;
      v24 = *(u16 *)(v20 + 32);
    }
    goto LABEL_43;
  }
  v22 = HIDWORD(ProcessData[1].monitor) + *(u32 *)(v20 + 20);
  *(u32 *)(v20 + 16) = v22;
  v20 = *(u64 *)&ProcessData[1].klass->_1.byval_arg.bits;
  v22 = *(u32 *)(v20 + 16);
LABEL_38:
  ReturnNum[1] = v22;
  v24 = *(u16 *)(v20 + 32);
  if ((v24 & 4) != 0)
    goto LABEL_41;
LABEL_43:
  if ((v24 & 2) == 0)
    goto LABEL_47;
  v26 = *(u32 *)(v20 + 28);
  if (*(u32 *)(v20 + 16) < v26)
    goto LABEL_47;
  *(u32 *)(v20 + 16) = v26;
LABEL_46:
  *(u8 *)(v8 + 33) = 1;
LABEL_47:
  if (*(u8 *)(v8 + 32) && *(u8 *)(v8 + 33))
  {
    HIDWORD(ProcessData[2].monitor) = 0;
    LODWORD(ProcessData[3].klass) = 0;
  }
  v27 = ProcessData[3].klass;
  if (!(v27 % SLODWORD(ProcessData[2].monitor)))
  {
    SE(HIDWORD(ProcessData[2].klass));
    v27 = ProcessData[3].klass;
  }
  LODWORD(ProcessData[3].klass) = v27 + 1;
  return 0;
}

// 0x1c42b10
s32 itfGetReturnNum00(void) {
  return ReturnNum[0];
}

// 0x1c42ba0
s32 itfGetReturnNum01(void) {
  return ReturnNum[1];
}

// 0x1c42c30
bool itfCountSetData(dds3ProcessID_t *PID, s32 a_pDat, ITF_COUNT_TYPE a_type) {
  s16 v4;
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  u32 *data;
  dds3ProcessID_t *id;

  id = PID;
  v4 = a_type;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if (a_pDat < 0)
    return 0;
  klass = ProcessData[1].klass;
  data = klass->_1.byval_arg.data;
  if (data[4])
  {
    data = *(u32 **)&klass->_1.byval_arg.bits;
    if (data[4])
      return 0;
  }
  data[4] = a_pDat;
  data[5] = a_pDat;
  *((u16 *)data + 17) = v4;
  return 1;
}

// 0x1c42d60
bool itfCountSetMax(dds3ProcessID_t *PID, s32 a_pDat, s32 a_max) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  u32 *data;
  s16 v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if (!a_pDat)
    return 0;
  klass = ProcessData[1].klass;
  data = klass->_1.byval_arg.data;
  if (data[4] != a_pDat)
  {
    data = *(u32 **)&klass->_1.byval_arg.bits;
    if (data[4] != a_pDat)
      return 0;
  }
  v11 = *((u16 *)data + 16);
  data[7] = a_max;
  *((u16 *)data + 16) = v11 | 2;
  return 1;
}

// 0x1c42ea0
bool itfCountSetMin(dds3ProcessID_t *PID, s32 a_pDat, s32 a_min) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  u32 *data;
  s16 v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if (!a_pDat)
    return 0;
  klass = ProcessData[1].klass;
  data = klass->_1.byval_arg.data;
  if (data[4] != a_pDat)
  {
    data = *(u32 **)&klass->_1.byval_arg.bits;
    if (data[4] != a_pDat)
      return 0;
  }
  v11 = *((u16 *)data + 16);
  data[6] = a_min;
  *((u16 *)data + 16) = v11 | 4;
  return 1;
}

// 0x1c42fe0
static void CountShutdown(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
}

// 0x1c43060
dds3ProcessID_t *itfCountProcessStart(s32 a_num, s32 a_frame, s32 a_blank, s32 a_seNo) {
  itfCount_t *v9;
  dds3ProcessFunc_t v10;
  shutdownfuncDelegate v11;
  dds3ProcessID_t *result;
  u32 v13;
  s32 v14;
  u32 v15;
  s32 v16;
  u64 v17;

  v9 = Allocate(itfCount_t);
  _ctor(v9, 0);
  if (a_num < 1)
    return 0;
  v10 = Allocate(dds3ProcessFunc_t);
  _ctor(v10, 0, Method_Project_itf_CountProcess__, 0);
  v11 = Allocate(shutdownfuncDelegate);
  _ctor(v11, 0, Method_Project_itf_CountShutdown__, 0);
  result = dds3StartProcess("itfcount", 1019, 0, 0, v10, v11, v9);
  v9->num = a_num;
  if (a_frame <= 1)
    v13 = 1;
  else
    v13 = a_frame;
  if (a_blank <= 1)
    v14 = 1;
  else
    v14 = a_blank;
  v9->blank = v14;
  v9->frame = v13;
  v15 = a_num / v13;
  v9->unit = a_num / v13;
  v9->seNo = a_seNo;
  if (v13 <= a_num)
  {
    HIDWORD(v17) = -858993459 * v15;
    LODWORD(v17) = -858993459 * v15;
    if ((u32)(v17 >> 1) > 0x19999999)
      return result;
    v16 = v15 - 1;
  }
  else
  {
    v16 = 1;
  }
  v9->unit = v16;
  return result;
}

// 0x1c43230
dds3ProcessID_t *itfCountProcessStartMoney(s32 a_num) {
  return itfCountProcessStart(a_num, 30, 2, 5);
}

// 0x1c432a0
void itfCountProcessEnd(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    if (!dds3ExistProcess(id))
      return;
    ProcessData = dds3GetProcessData(id);
    if (ProcessData)
    {
      HIDWORD(ProcessData[2].monitor) = 0;
      LODWORD(ProcessData[3].klass) = 0;
    }
  }
}

// 0x1c433a0
bool itfCountProcessCheck(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  if (!PID)
    return 0;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  if (dds3GetProcessStat(id))
    return 1;
  return 0;
}

// 0x1c43480
static bool DvlMsgCreateCB(tagITFDVLMSG_WORK *wk) {
  tagITFDVLMSG_CB *v3;
  tagITFDVLMSG_CB *p_pHead;
  tagITFDVLMSG_CB *pTail;
  tagITFDVLMSG_CB *p_pTail;

  v3 = Allocate(tagITFDVLMSG_CB);
  _ctor(v3, 0);
  p_pHead = &wk->pHead;
  if (wk->pHead)
  {
    pTail = wk->pTail;
    v3->pPrev = pTail;
    p_pHead = &wk->pTail->pNext;
  }
  else
  {
    v3->pPrev = 0;
  }
  p_pHead = v3;
  v3->pNext = 0;
  wk->pTail = v3;
  p_pTail = &wk->pTail;
  ++*((u32 *)p_pTail + 2);
  return 1;
}

// 0x1c43560
static void DvlMsgDeleteCB(tagITFDVLMSG_WORK *wk, tagITFDVLMSG_CB *cb) {
  tagITFDVLMSG_CB *pHead;
  tagITFDVLMSG_CB *p_pHead;
  tagITFDVLMSG_CB *pTail;
  tagITFDVLMSG_CB *p_pTail;
  tagITFDVLMSG_CB *v9;
  tagITFDVLMSG_CB *v10;
  tagITFDVLMSG_CB *v11;
  tagITFDVLMSG_CB *v12;
  tagITFDVLMSG_CB *p_pNext;
  tagITFDVLMSG_CB *pNext;
  tagITFDVLMSG_CB *pPrev;

  if (cb)
  {
    p_pHead = &wk->pHead;
    pHead = wk->pHead;
    if (pHead)
    {
      p_pTail = &wk->pTail;
      pTail = wk->pTail;
      if (pTail)
      {
        if (pHead == cb)
        {
          if (pTail == cb)
          {
            p_pHead = 0;
            p_pTail = 0;
            p_pNext = &wk->pTail;
            v12 = 0;
          }
          else
          {
            pNext = cb->pNext;
            pNext->pPrev = 0;
            v12 = cb->pNext;
            p_pNext = p_pHead;
            p_pHead = v12;
          }
        }
        else if (pTail == cb)
        {
          pPrev = cb->pPrev;
          pPrev->pNext = 0;
          v12 = cb->pPrev;
          p_pNext = &wk->pTail;
          p_pTail = v12;
        }
        else
        {
          v10 = cb->pPrev;
          v9 = cb->pNext;
          v9->pPrev = v10;
          v11 = cb->pPrev;
          v12 = cb->pNext;
          v11->pNext = v12;
          p_pNext = &v11->pNext;
        }
        --wk->datNum;
      }
    }
  }
}

// 0x1c43640
static tagITFDVLMSG_CB *DvlMsgGetCB(tagITFDVLMSG_WORK *wk, s32 a_devilID) {
  tagITFDVLMSG_CB *result;

  for (result = wk->pHead; result; result = result->pNext)
  {
    if (result->devilID == a_devilID)
      break;
  }
  return result;
}

// 0x1c43670
static void DvlMsgFreeMsg(tagITFDVLMSG_CB *cb) {
  ;
}

// 0x1c43680
static void DvlMsgFreeTex(tagITFDVLMSG_CB *cb) {
  cb->pDatTex = 0;
}

// 0x1c43690
static bool DvlMsgLoadFile(tagITFDVLMSG_WORK *wk, tagITFDVLMSG_CB *cb, s32 a_devilID) {
  NewSpecific(byte, 0x40u);
  if (wk && cb && (u32)a_devilID <= 0xFFE)
  {
    cb->devilID = a_devilID;
    DvlMsgDeleteCB(wk, cb);
  }
  return 0;
}

// 0x1c43740
bool itfDvlMsgCreateData(s32 a_devilID) {
  tagITFDVLMSG_WORK *ProcessData;
  tagITFDVLMSG_WORK *v7;
  tagITFDVLMSG_CB *pTail;

  ProcessData = dds3GetProcessData(DevilMessage_g_mainPID);
  v7 = ProcessData;
  if ((u32)a_devilID > 0xFFE)
    return 0;
  DvlMsgCreateCB(ProcessData);
  pTail = v7->pTail;
  NewSpecific(byte, 0x40u);
  if (!v7)
    return 0;
  if (!pTail)
    return 0;
  pTail->devilID = a_devilID;
  DvlMsgDeleteCB(v7, pTail);
  return 0;
}

// 0x1c43950
static bool _DvlMsgDeleteData(tagITFDVLMSG_WORK *wk, tagITFDVLMSG_CB *cb) {
  if (cb)
  {
    cb->pDatTex = 0;
    DvlMsgDeleteCB(wk, cb);
  }
  return cb != 0;
}

// 0x1c439e0
bool itfDvlMsgDeleteData(s32 a_devilID) {
  Il2CppObject *ProcessData;
  tagITFDVLMSG_WORK *v6;
  tagITFDVLMSG_CB *i;

  ProcessData = dds3GetProcessData(DevilMessage_g_mainPID);
  v6 = ProcessData;
  for (i = (tagITFDVLMSG_CB *)ProcessData[2].klass; i; i = i->pNext)
  {
    if (i->devilID == a_devilID)
      break;
  }
  if (i)
  {
    i->pDatTex = 0;
    DvlMsgDeleteCB(v6, i);
  }
  return i != 0;
}

// 0x1c43b60
static void DvlMsgLoadSprite(tagITFDVLMSG_WORK *wk) {
  ;
}

// 0x1c43b70
void itfDvlMsgStart(s32 a_devilID, s32 a_msgID) {
  Il2CppObject *ProcessData;
  s16 v9;

  ProcessData = dds3GetProcessData(DevilMessage_g_mainPID);
  if (!ProcessData)
  v9 = WORD2(ProcessData[6].monitor);
  HIDWORD(ProcessData[3].klass) = a_devilID;
  LODWORD(ProcessData[3].monitor) = a_msgID;
  WORD2(ProcessData[6].monitor) = v9 | 1;
}

// 0x1c43ca0
void itfDvlMsgEnd(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(DevilMessage_g_mainPID);
  if (!ProcessData)
  WORD2(ProcessData[6].monitor) |= 2u;
}

// 0x1c43dc0
static void DvlMsgSetMover(tagITFDVLMSG_WORK *wk, s32 a_mode) {
  itfMover_t *mover;
  s32 v7;
  s32 v8;
  s32 v9;

  mover = wk->mover;
  if (a_mode)
    v7 = 332;
  else
    v7 = 460;
  if (a_mode)
    v8 = 460;
  else
    v8 = 332;
  if (a_mode)
    v9 = 5;
  else
    v9 = 10;
  itfMoverSetParam(mover, 16, v7, 16, v8, v9);
}

// 0x1c43fc0
static void DvlMsgInitParam(tagITFDVLMSG_WORK *wk) {
  s32 devilID;
  tagITFDVLMSG_CB *pHead;

  devilID = wk->devilID;
  pHead = wk->pHead;
  if (!pHead)
    return;
  goto LABEL_7;
  do
  {
LABEL_7:
    if (pHead->devilID == devilID)
      break;
    pHead = pHead->pNext;
  }
  while (pHead);
}

// 0x1c44060
static void DvlMsgRelease(tagITFDVLMSG_WORK *wk) {
  u16 lflag;
  tagITFDVLMSG_CB *pTail;
  u16 v5;

  lflag = wk->lflag;
  if ((lflag & 1) != 0)
    return;
  pTail = wk->pTail;
  v5 = lflag & 0xFFFD;
  wk->lflag = v5;
  if (!pTail)
    goto LABEL_16;
  do
  {
    pTail->pDatTex = 0;
    DvlMsgDeleteCB(wk, pTail);
    pTail = wk->pTail;
  }
  while (pTail);
  v5 = wk->lflag;
LABEL_16:
  wk->lflag = v5 | 1;
}

// 0x1c44180
static dds3ProcessFunc_t DvlMsgProcess(dds3ProcessID_t *PID) {
  tagITFDVLMSG_WORK *ProcessData;
  u16 gflag;
  s32 devilID;
  tagITFDVLMSG_CB *pHead;
  s32 step2;
  itfMover_t *v12;
  tagITFDVLMSG_CB *p_pDraw;
  s16 v14;
  s32 count;
  dds3ProcessFunc_t v17;
  itfMover_t *mover;
  s16 v20;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  gflag = ProcessData->gflag;
  if ((gflag & 1) != 0)
  {
    devilID = ProcessData->devilID;
    pHead = ProcessData->pHead;
    if (!pHead)
      goto LABEL_20;
    goto LABEL_18;
    if (!pHead)
    {
LABEL_20:
      gflag = ProcessData->gflag & 0xFFFE;
      ProcessData->gflag = gflag;
      goto LABEL_21;
    }
    do
    {
LABEL_18:
      if (pHead->devilID == devilID)
        break;
      pHead = pHead->pNext;
    }
    while (pHead);
    goto LABEL_20;
  }
LABEL_21:
  switch (ProcessData->step)
  {
    case 1:
      if ((gflag & 2) != 0)
      {
        ProcessData->count = 0;
        ProcessData->step = 2;
        ProcessData->gflag = gflag & 0xFFFD;
        return 0;
      }
      else
      {
        step2 = ProcessData->step2;
        if (step2 == 2)
        {
          mover = ProcessData->mover;
          if (itfMoverUpdate(mover) != 2)
            return 0;
          ProcessData->step = 2;
          return 0;
        }
        else
        {
          if (step2 == 1)
          {
            count = ProcessData->count;
            if (count < 100)
              goto LABEL_39;
            DvlMsgSetMover(ProcessData, 1);
          }
          else
          {
            if (ProcessData->step2)
              return 0;
            v12 = ProcessData->mover;
            if (itfMoverUpdate(v12) != 2)
              return 0;
          }
          v20 = ProcessData->step2;
          ProcessData->count = 0;
          ProcessData->step2 = v20 + 1;
          return 0;
        }
      }
    case 2:
      ProcessData->pDraw = 0;
      p_pDraw = &ProcessData->pDraw;
      v14 = *((u16 *)p_pDraw + 23);
      *((u32 *)p_pDraw + 10) = 0;
      *((u16 *)p_pDraw + 23) = v14 & 0xFFFD;
      return 0;
    case 3:
      count = ProcessData->count;
      if (count)
      {
        if (count >= 2)
        {
          ProcessData->count = 0;
          ProcessData->step = 4;
          return 0;
        }
      }
      else
      {
        ProcessData->lflag &= ~2u;
        DvlMsgRelease(ProcessData);
        count = ProcessData->count;
      }
LABEL_39:
      ProcessData->count = count + 1;
      return 0;
    case 4:
      v17 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v17, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v17;
    default:
      return 0;
  }
}

// 0x1c44780
static bool DvlMsgDrawTextFont(s32 x, s32 y, s32 z, u32 a_color, f32 a_alphaRate, s32 msgNo, u8 *pDatMsg) {
  return 0;
}

// 0x1c44790
static void DvlMsgDrawWindow(tagITFDVLMSG_WORK *wk, s32 ofs_x, s32 ofs_y, f32 a_alphaRate) {
  u32 *v7;
  s32 *v8;
  tagITFDVLMSG_PARAM *m_Items;
  tagITFDVLMSG_PARAM *v10;
  s32 alpha;
  u32 rgb;
  f32 v13;
  s32 v14;
  tagITFDVLMSG_PARAM *v15;
  s32 v16;
  u32 v17;
  f32 v18;
  s32 v19;
  tagITFDVLMSG_PARAM *v20;
  s32 v21;
  u32 v22;
  f32 v23;
  s32 v24;
  tagITFDVLMSG_PARAM *v25;
  s32 v26;
  u32 v27;
  f32 v28;
  s32 v29;
  tagITFDVLMSG_PARAM *v30;
  s32 v31;
  u32 v32;
  f32 v33;
  s32 v34;
  tagITFDVLMSG_PARAM *v35;
  s32 v36;
  u32 v37;
  f32 v38;
  s32 v39;
  tagITFDVLMSG_PARAM *v40;
  s32 v41;
  u32 v42;
  f32 v43;
  s32 v44;
  tagITFDVLMSG_PARAM *v45;
  s32 v46;
  u32 v47;
  f32 v48;
  s32 v49;
  tagITFDVLMSG_PARAM *v50;
  s32 v51;
  u32 v52;
  f32 v53;
  s32 v54;
  tagITFDVLMSG_PARAM *v55;
  s32 v56;
  u32 v57;
  f32 v58;
  s32 v59;
  tagITFDVLMSG_PARAM *v60;
  s32 v61;
  u32 v62;
  f32 v63;
  s32 v64;
  tagITFDVLMSG_PARAM *v65;
  s32 v66;
  u32 v67;
  f32 v68;
  s32 v69;
  tagITFDVLMSG_PARAM *v70;
  s32 v71;
  u32 v72;
  f32 v73;
  s32 v74;
  tagITFDVLMSG_PARAM *v75;
  s32 v76;
  u32 v77;
  f32 v78;
  s32 v79;
  tagITFDVLMSG_PARAM *v80;
  s32 v81;
  u32 v82;
  f32 v83;
  s32 v84;

  v7 = NewSpecific(uint, 3u);
  v8 = NewSpecific(s32, 0xFu);
  InitializeArray_55364416(v8, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__126FD573B011921C3F8154362F782F73D08033981176E93C30CA580C7250C507, 0);
  m_Items = wk->param;
  v10 = m_Items[v8[0]];
  alpha = v10->alpha;
  rgb = v10->rgb;
  v13 = (f32)alpha * a_alphaRate;
  v14 = v13;
  if (v13 >= 0.0)
    v14 = (u32)v13;
  v7[8] = rgb | (v14 << 24);
  v15 = m_Items[v8[1]];
  v16 = v15->alpha;
  v17 = v15->rgb;
  v18 = (f32)v16 * a_alphaRate;
  v19 = v18;
  if (v18 >= 0.0)
    v19 = (u32)v18;
  v7[9] = v17 | (v19 << 24);
  v20 = m_Items[v8[2]];
  v21 = v20->alpha;
  v22 = v20->rgb;
  v23 = (f32)v21 * a_alphaRate;
  v24 = v23;
  if (v23 >= 0.0)
    v24 = (u32)v23;
  v7[10] = v22 | (v24 << 24);
  v25 = m_Items[v8[3]];
  v26 = v25->alpha;
  v27 = v25->rgb;
  v28 = (f32)v26 * a_alphaRate;
  v29 = v28;
  if (v28 >= 0.0)
    v29 = (u32)v28;
  v7[8] = v27 | (v29 << 24);
  v30 = m_Items[v8[4]];
  v31 = v30->alpha;
  v32 = v30->rgb;
  v33 = (f32)v31 * a_alphaRate;
  v34 = v33;
  if (v33 >= 0.0)
    v34 = (u32)v33;
  v7[9] = v32 | (v34 << 24);
  v35 = m_Items[v8[5]];
  v36 = v35->alpha;
  v37 = v35->rgb;
  v38 = (f32)v36 * a_alphaRate;
  v39 = v38;
  if (v38 >= 0.0)
    v39 = (u32)v38;
  v7[10] = v37 | (v39 << 24);
  v40 = m_Items[v8[6]];
  v41 = v40->alpha;
  v42 = v40->rgb;
  v43 = (f32)v41 * a_alphaRate;
  v44 = v43;
  if (v43 >= 0.0)
    v44 = (u32)v43;
  v7[8] = v42 | (v44 << 24);
  v45 = m_Items[v8[7]];
  v46 = v45->alpha;
  v47 = v45->rgb;
  v48 = (f32)v46 * a_alphaRate;
  v49 = v48;
  if (v48 >= 0.0)
    v49 = (u32)v48;
  v7[9] = v47 | (v49 << 24);
  v50 = m_Items[v8[8]];
  v51 = v50->alpha;
  v52 = v50->rgb;
  v53 = (f32)v51 * a_alphaRate;
  v54 = v53;
  if (v53 >= 0.0)
    v54 = (u32)v53;
  v7[10] = v52 | (v54 << 24);
  v55 = m_Items[v8[9]];
  v56 = v55->alpha;
  v57 = v55->rgb;
  v58 = (f32)v56 * a_alphaRate;
  v59 = v58;
  if (v58 >= 0.0)
    v59 = (u32)v58;
  v7[8] = v57 | (v59 << 24);
  v60 = m_Items[v8[10]];
  v61 = v60->alpha;
  v62 = v60->rgb;
  v63 = (f32)v61 * a_alphaRate;
  v64 = v63;
  if (v63 >= 0.0)
    v64 = (u32)v63;
  v7[9] = v62 | (v64 << 24);
  v65 = m_Items[v8[11]];
  v66 = v65->alpha;
  v67 = v65->rgb;
  v68 = (f32)v66 * a_alphaRate;
  v69 = v68;
  if (v68 >= 0.0)
    v69 = (u32)v68;
  v7[10] = v67 | (v69 << 24);
  v70 = m_Items[v8[12]];
  v71 = v70->alpha;
  v72 = v70->rgb;
  v73 = (f32)v71 * a_alphaRate;
  v74 = v73;
  if (v73 >= 0.0)
    v74 = (u32)v73;
  v7[8] = v72 | (v74 << 24);
  v75 = m_Items[v8[13]];
  v76 = v75->alpha;
  v77 = v75->rgb;
  v78 = (f32)v76 * a_alphaRate;
  v79 = v78;
  if (v78 >= 0.0)
    v79 = (u32)v78;
  v7[9] = v77 | (v79 << 24);
  v80 = m_Items[v8[14]];
  v81 = v80->alpha;
  v82 = v80->rgb;
  v83 = (f32)v81 * a_alphaRate;
  v84 = v83;
  if (v83 >= 0.0)
    v84 = (u32)v83;
  v7[10] = v82 | (v84 << 24);
}

// 0x1c44b20
static dds3ProcessFunc_t DvlMsgDrawProcess(dds3ProcessID_t *PID) {
  s32 v4;
  tagITFDVLMSG_WORK *ProcessData;
  itfMover_t *mover;
  f32 v9;
  u16 flag;
  f32 v11;
  s32 total_frm;
  s32 total_cnt;
  s32 v14;
  bool v15;
  s32 v16;
  s32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if ((ProcessData->lflag & 2) == 0 || !ProcessData->pDraw)
    return 0;
  mover = ProcessData->mover;
  v9 = 1.0;
  if (!mover)
    goto LABEL_25;
  goto LABEL_9000;
  if (!mover)
  {
LABEL_25:
    v11 = 0.0;
    goto LABEL_26;
  }
LABEL_9000:
  flag = mover->flag;
  v11 = v9;
  if ((flag & 2) == 0)
  {
    if ((flag & 1) != 0)
    {
      total_frm = mover->total_frm;
      if (total_frm >= 1)
      {
        total_cnt = mover->total_cnt;
        v14 = mover->cb[0]->wait[0];
        v15 = __OFSUB__(total_cnt, v14);
        v16 = total_cnt - v14;
        if (v16 < 0 == v15 && v16 >= 1)
        {
          v17 = total_frm - v14;
          if (v17 >= 1)
          {
            v18 = (f32)v16 / (f32)v17;
            v11 = 0.0;
            if (v18 >= 0.0)
            {
              v11 = 1.0;
              if (v18 <= 1.0)
                v11 = (f32)v16 / (f32)v17;
            }
            goto LABEL_26;
          }
        }
      }
    }
    goto LABEL_25;
  }
LABEL_26:
  v19 = v9 - v11;
  if (ProcessData->step2 == 2)
    v20 = v19;
  else
    v20 = v11;
  DvlMsgDrawWindow(ProcessData, (s32)tagITFDVLMSG_WORK, v4, v20);
  return 0;
}

// 0x1c44dc0
static void DvlMsgInit(tagITFDVLMSG_WORK *wk) {

}

// 0x1c44e20
static void DvlMsgShutdown(dds3ProcessID_t *PID) {
  tagITFDVLMSG_WORK *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  DvlMsgRelease(ProcessData);
}

// 0x1c44f10
void itfDvlMsgProcessStart(void) {
  tagITFDVLMSG_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;

  v1 = Allocate(tagITFDVLMSG_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_itf_DvlMsgProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_itf_DvlMsgShutdown__, 0);
  started = dds3StartProcess("itfDvlMsgMainProc", 1024, 0, 0, v2, v3, v1);
  DevilMessage_g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_itf_DvlMsgDrawProcess__, 0);
  v8 = dds3StartProcess("itfDvlMsgDrawProc", 11015, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
}

// 0x1c45170
void itfDvlMsgProcessEnd(void) {
  Il2CppObject *ProcessData;

  if (!DevilMessage_g_mainPID)
    return;
  if (dds3ExistProcess(DevilMessage_g_mainPID))
  {
    goto LABEL_10;
  }
  return;
  if (dds3ExistProcess(DevilMessage_g_mainPID))
  {
LABEL_10:
    ProcessData = dds3GetProcessData(DevilMessage_g_mainPID);
    if (!ProcessData)
      goto LABEL_21;
    goto LABEL_19;
    if (!ProcessData)
    {
LABEL_21:
      DvlMsgRelease(ProcessData);
      dds3KillProcess(DevilMessage_g_mainPID, 0);
      return;
    }
LABEL_19:
    goto LABEL_21;
  }
}

// 0x1c45320
bool itfDvlMsgProcessCheck(void) {
  if (!DevilMessage_g_mainPID)
    return 0;
  if (dds3ExistProcess(DevilMessage_g_mainPID))
  {
    return 1;
  }
  DevilMessage_g_mainPID = 0;
  return 0;
}

// 0x1c45440
void itfDrawMiscSprite(s32 a_x, s32 a_y, s32 a_z, sprHandle_t *a_hSpr, s32 a_sprNo, DDS3_OT a_otNo) {
  ;
}

// 0x1c45450
void itfDrawMiscSpriteAlpha(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, s32 a_sprNo, DDS3_OT a_otNo) {
  ;
}

// 0x1c45460
void itfDrawMiscSpriteListSelect(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, DDS3_OT a_otNo, itfSprList_t *a_list, s32 a_no) {

}

// 0x1c454c0
void itfDrawMiscSpriteListEx(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, DDS3_OT a_otNo, u32 a_flag, itfSprList_t *a_list) {
  itfSprList_t *v11;
  s32 v12;
  s32 flag;
  _BOOL4 v15;

  if (a_list)
  {
    v11 = a_list[0];
    if ((v11->sprNo & 0x80000000) == 0)
    {
      v12 = 0;
      do
      {
        flag = v11->flag;
        v15 = (flag & a_flag) != 0 || a_flag == 0;
        v11 = a_list[++v12];
      }
      while ((v11->sprNo & 0x80000000) == 0);
    }
  }
}

// 0x1c455b0
void itfDrawMiscSpriteList(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, sprHandle_t *a_hSpr, DDS3_OT a_otNo, itfSprList_t *a_list) {
  itfSprList_t *v10;
  s32 v11;

  if (a_list)
  {
    v10 = a_list[0];
    if (v10->sprNo < 0)
      return;
    v11 = 0;
    do
    {
      v10 = a_list[++v11];
    }
    while ((v10->sprNo & 0x80000000) == 0);
  }
}

// 0x1c456e0
static void _DrawMiscFont(ITF_DM_STYLE a_style, s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_space, u32 a_col, DDS3_OT a_ot, char *a_str) {

}

// 0x1c45760
void itfDrawFont(ITF_DM_STYLE a_style, s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_space, u32 a_color, f32 a_alphaRate, DDS3_OT a_ot, char *a_str) {
  if (a_alphaRate > 0.0)
  {
    if (a_w < 1)
      return;
    return;
  }
}

// 0x1c45840
void itfDrawMiscFont(ITF_DM_STYLE a_style, s32 a_x, s32 a_y, s32 a_z, s32 a_space, u32 a_color, u8 a_alpha, char *a_str) {
  return;
}

// 0x1c458e0
void itfDrawMiscFontAlpha(s32 a_x, s32 a_y, s32 a_z, u32 a_color, u8 a_alpha, char *a_str) {
  return;
}

// 0x1c45980
void itfDrawMiscHelp(u32 a_color, f32 a_alphaRate, FRW_HELP HelpType, u16 HelpID, s32 _spirit) {
  char *v15;
  _BOOL4 v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  char *NoneItemText;
  u8 v25;
  char **v26;
  char *v27;
  char *v28;

  if (!GuideNowAnm)
  {
    ButtonLineHelpDispSet(0);
    return;
  }
  if (a_alphaRate <= 0.0)
    return;
  if (!logdispwk->start)
  {
    switch (HelpType)
    {
      case 0:
        if (spirit == 2)
        {
          v16 = 0;
          if (RaidouSklCheck(HelpID))
            v17 = "GOH_RENKEN_L0020";
          else
            v17 = "GOH_RENKEN_L0021";
        }
        else
        {
          if (spirit != 1)
          {
            v19 = sdatSkillHelp(HelpID, 1);
            v18 = Concat_54766928(0, v19, 0);
            goto LABEL_47;
          }
          v15 = sdatSkillName(HelpID);
          frSetVariableRequest(0, v15);
          v16 = 0;
          if (RaidouSklCheck(HelpID))
            v17 = "GOH_RENKEN_L0019";
          else
            v17 = "GOH_RENKEN_L0010";
        }
        goto LABEL_49;
      case 1:
        v17 = sdatItemHelp(HelpID, 1);
        v16 = HelpID == 9;
        goto LABEL_49;
      case 2:
        v18 = cmpMskHelp(HelpID, 1);
        goto LABEL_47;
      case 3:
        v18 = sdatParHelp(HelpID, 1);
LABEL_47:
        v17 = v18;
        goto LABEL_48;
      default:
        v17 = 0;
LABEL_48:
        v16 = 0;
LABEL_49:
        ButtonLineHelpDispSet(1);
        v20 = ButtonLineHelpTextSet(v17, 0, 1, a_color, 0);
        if (spirit)
        {
          v21 = sdatSkillHelp(HelpID, 1);
          v22 = ButtonLineHelpAddTextSet(v21, 1, 2, 0);
          if (!v16)
          {
LABEL_71:
            v28 = Concat_54766928(v20, v22, 0);
            ButtonLineHelpTextSetNoConvert(v28, a_color);
            return;
          }
        }
        else
        {
          v22 = 0;
          if (!v16)
            goto LABEL_71;
        }
        v23 = sdatItemHelp(HelpID, 0);
        NoneItemText = cmpGetNoneItemText();
        if (op_Inequality(v23, NoneItemText, 0))
        {
          v25 = cmpCheckSeikatu();
          v26 = &"CMP_USE_MSG_L0027";
          if (v25)
            v26 = &"CMP_USE_MSG_L0026";
          v27 = *v26;
          v22 = ButtonLineHelpAddTextSet(v27, 1, 2, 0);
        }
        goto LABEL_71;
    }
  }
}

// 0x1c45f10
void itfDrawMiscGauge(s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_h, s32 a_num, s32 a_max, u32 a_color, u8 a_alpha) {
  ;
}

// 0x1c45f20
void itfDrawMiscGauge2(s32 a_mode, s32 a_x, s32 a_y, s32 a_z, s32 a_w, s32 a_h, s32 a_num, s32 a_max, u32 a_color, u8 a_alpha) {

}

// 0x1c45f80
void itfDrawLineBezierPt3(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 vx, f32 vy, u32 rgba0, u32 rgba1, u32 ot) {
  u32 *v20;
  u32 DivBezierPt3;
  u32 *v23;
  u32 *v24;

  v20 = NewSpecific(uint, 2u);
  DivBezierPt3 = itfGetDivBezierPt3(x0, y0, x1, y1, vx, vy, 0.1);
  v23 = NewSpecific(uint, 4u);
  v23[8] = HIBYTE(rgba0);
  v23[9] = (rgba0 >> 8) & 0xFF00;
  v23[10] = (rgba0 << 8) & 0xFF0000;
  v23[11] = rgba0 << 24;
  v20[0] = bswap32(rgba0);
  v24 = NewSpecific(uint, 4u);
  v24[8] = HIBYTE(rgba1);
  v24[9] = (rgba1 >> 8) & 0xFF00;
  v24[10] = (rgba1 << 8) & 0xFF0000;
  v24[11] = rgba1 << 24;
  v20[1] = bswap32(rgba1);
  if (DivBezierPt3)
  {
    do
    {
      --DivBezierPt3;
    }
    while (DivBezierPt3);
  }
}

// 0x1c464c0
void itfDrawFanBezierPt3(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 vx, f32 vy, u32 rgba0, u32 rgba1, u32 rgba2, u32 ot) {
  u32 *v22;
  u32 *v23;
  u32 *v24;
  u32 DivBezierPt3;
  f32 v27;
  u32 v28;
  s32 v30;
  f32 v31;
  f32 v32;
  s32 v33;
  s32 v34;
  f32 v35;
  s32 v36;
  s32 v37;
  f32 v38;
  s32 v39;
  s32 v40;
  f32 v41;
  s32 v42;
  s32 v43;

  v22 = NewSpecific(uint, 3u);
  v23 = NewSpecific(uint, 4u);
  v24 = NewSpecific(uint, 4u);
  DivBezierPt3 = itfGetDivBezierPt3(x1, y1, x2, y2, vx, vy, 0.1);
  v22[0] = rgba0;
  v22[1] = rgba1;
  v22[2] = rgba2;
  v23[8] = HIBYTE(rgba1);
  v23[9] = *(u8 *)((char *)v22 + 38);
  v23[10] = *(u8 *)((char *)v22 + 37);
  v23[11] = *(u8 *)&v22[1];
  v24[8] = *(u8 *)((char *)v22 + 43) - HIBYTE(rgba1);
  v24[9] = *(u8 *)((char *)v22 + 42) - v23[9];
  v24[10] = *(u8 *)((char *)v22 + 41) - v23[10];
  v24[11] = *(u8 *)&v22[2] - v23[11];
  if (DivBezierPt3)
  {
    v27 = DivBezierPt3;
    v28 = DivBezierPt3;
    v30 = 0;
    do
    {
      v31 = (f32)(u32)++v30 / v27;
      v32 = v31 * (f32)(u32)v24[8];
      v33 = v32;
      if (v32 == INFINITY)
        v33 = 0;
      v34 = (v33 + v23[8]) << 24;
      v22[2] = v34;
      v35 = v31 * (f32)(u32)v24[9];
      v36 = v35;
      if (v35 == INFINITY)
        v36 = 0;
      v37 = v34 | ((v36 + v23[9]) << 16);
      v22[2] = v37;
      v38 = v31 * (f32)(u32)v24[10];
      v39 = v38;
      if (v38 == INFINITY)
        v39 = 0;
      v40 = v37 | ((v39 + v23[10]) << 8);
      v22[2] = v40;
      v41 = v31 * (f32)(u32)v24[11];
      v42 = v41;
      if (v41 == INFINITY)
        v42 = 0x80000000;
      v43 = (v42 + v23[11]) | v40;
      v22[1] = v43;
      v22[2] = v43;
    }
    while (v28 != v30);
  }
}

// 0x1c46380
s32 itfFloatTo32s(f32 a_num, s32 a_shift) {
  s32 v3;
  f32 v4;
  s32 v5;
  f32 v6;
  s32 v7;

  v3 = a_num;
  if (a_num == INFINITY)
    v3 = 0x80000000;
  v4 = v3;
  v5 = v3 << a_shift;
  v6 = (f32)(a_num - v4) * (f32)(1 << a_shift);
  if (v6 == INFINITY)
    v7 = 0x80000000;
  else
    v7 = v6;
  return v7 + v5;
}

// 0x1c46720
s32 itfGetFigure(s32 a_num) {
  u32 v2;
  s32 result;
  bool v4;

  if (a_num < 0)
    return -1;
  v2 = a_num;
  result = 1;
  if (v2 >= 0xA)
  {
    do
    {
      v4 = v2 > 0x63;
      ++result;
      v2 /= 0xAu;
    }
    while (v4);
  }
  return result;
}

// 0x1c46760
s32 itfGetFigureNum(s32 a_num, s32 a_figure) {
  s32 v3;
  s32 v4;
  u32 v6;
  int32x4_t v7;
  int32x4_t v8;
  u32 v9;
  int32x4_t v10;
  int32x4_t v11;
  int32x4_t v12;
  int8x16_t v13;
  u32 v14;

  v3 = a_figure - 1;
  if (a_figure < 1)
    return -1;
  if (a_figure == 1)
  {
    v4 = 1;
  }
  else
  {
    if ((u32)a_figure >= 0x11)
    {
      v7.n128_u64[0] = 0x100000001LL;
      v7.n128_u64[1] = 0x100000001LL;
      v8.n128_u64[0] = 0xA0000000ALL;
      v8.n128_u64[1] = 0xA0000000ALL;
      v6 = v3 & 0xFFFFFFF0 | 1;
      v9 = v3 & 0xFFFFFFF0;
      v10 = v7;
      v11 = v7;
      v12 = v7;
      do
      {
        v7 = vmulq_s32(v7, v8);
        v9 -= 16;
        v10 = vmulq_s32(v10, v8);
        v11 = vmulq_s32(v11, v8);
        v12 = vmulq_s32(v12, v8);
      }
      while (v9);
      v13 = vmulq_s32(v12, vmulq_s32(v11, vmulq_s32(v10, v7)));
      v13.n128_u64[0] = vmul_s32((int32x2_t)v13.n128_u64[0], (int32x2_t)vextq_s8(v13, v13, 8u).n128_u64[0]).n64_u64[0];
      v4 = v13.n128_u32[0] * v13.n128_u32[1];
      if (v3 == (v3 & 0xFFFFFFF0))
        return a_num / v4 % 10;
    }
    else
    {
      v6 = 1;
      v4 = 1;
    }
    v14 = a_figure - v6;
    do
    {
      --v14;
      v4 *= 10;
    }
    while (v14);
  }
  return a_num / v4 % 10;
}

// 0x1c463d0
u32 itfSwapRGBA(u32 a_rgba) {
  u32 *v3;

  v3 = NewSpecific(uint, 4u);
  v3[8] = HIBYTE(a_rgba);
  v3[9] = (a_rgba >> 8) & 0xFF00;
  v3[10] = (a_rgba << 8) & 0xFF0000;
  v3[11] = a_rgba << 24;
  return bswap32(a_rgba);
}

// 0x1c46830
void itfCalcSpriteWidth(sprHandle_t *a_hSpr, s32 a_sprNo, s32 a_num, s32 a_max) {
  ;
}

// 0x1c46450
void itfGetRatePosBezierPt3(f32 *px, f32 *py, f32 x0, f32 y0, f32 x1, f32 y1, f32 vx, f32 vy, f32 rate) {
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;

  v10 = 0.0;
  if (rate >= 0.0)
  {
    v10 = 1.0;
    if (rate <= 1.0)
      v10 = rate;
  }
  v11 = 1.0 - v10;
  v12 = v11 + v11;
  v13 = v11 * v11;
  v14 = v10 * v12;
  v15 = v10 * v10;
  *px = (f32)(v15 * x1) + (f32)((f32)(v13 * x0) + (f32)(v14 * vx));
  *py = (f32)(v15 * y1) + (f32)((f32)(v13 * y0) + (f32)(v14 * vy));
}

// 0x1c46840
void itfGetVectorPosBezierPt3(f32 px, f32 py, f32 x0, f32 y0, f32 x1, f32 y1, f32 rx, f32 ry, f32 rate) {
  ;
}

// 0x1c46140
u32 itfGetDivBezierPt3(f32 x0, f32 y0, f32 x1, f32 y1, f32 vx, f32 vy, f32 divLength) {
  f32 v8;
  u32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v35;
  f32 v36;

  v8 = divLength;
  if (divLength <= 0.0)
    return 0;
  v23 = 1.0;
  v24 = 0.5;
  v16 = 1;
  v35 = x1;
  v36 = v8;
  v25 = 1.0;
  while (1)
  {
    v25 = v25 * v24;
    v29 = 0.0;
    if (v25 >= 0.0)
    {
      v29 = v23;
      if (v25 <= v23)
        v29 = v25;
    }
    v26 = v23 - v29;
    v27 = v29 * v29;
    ++v16;
    v28 = v29 * (f32)(v26 + v26);
    if (sqrtf((f32)((f32)((f32)((f32)(v27 * x1) + (f32)((f32)((f32)(v26 * v26) * x0) + (f32)(v28 * vx))) - x0) * (f32)((f32)((f32)(v27 * x1) + (f32)((f32)((f32)(v26 * v26) * x0) + (f32)(v28 * vx))) - x0)) + (f32)((f32)((f32)((f32)(v27 * y1) + (f32)((f32)((f32)(v26 * v26) * y0) + (f32)(v28 * vy))) - y0) * (f32)((f32)((f32)(v27 * y1) + (f32)((f32)((f32)(v26 * v26) * y0) + (f32)(v28 * vy))) - y0))) <= v8)
      return v16;
  }
  v16 = 1;
  v17 = 1.0;
  do
  {
    v17 = v17 * 0.5;
    v21 = 0.0;
    if (v17 >= 0.0)
    {
      v21 = 1.0;
      if (v17 <= 1.0)
        v21 = v17;
    }
    v18 = 1.0 - v21;
    v19 = v21 * v21;
    ++v16;
    v20 = v21 * (f32)(v18 + v18);
  }
  while (sqrtf((f32)((f32)((f32)((f32)(v19 * x1) + (f32)((f32)((f32)(v18 * v18) * x0) + (f32)(v20 * vx))) - x0) * (f32)((f32)((f32)(v19 * x1) + (f32)((f32)((f32)(v18 * v18) * x0) + (f32)(v20 * vx))) - x0)) + (f32)((f32)((f32)((f32)(v19 * y1) + (f32)((f32)((f32)(v18 * v18) * y0) + (f32)(v20 * vy))) - y0) * (f32)((f32)((f32)(v19 * y1) + (f32)((f32)((f32)(v18 * v18) * y0) + (f32)(v20 * vy))) - y0))) > v8);
  return v16;
}

// 0x1c46850
sprHandle_t *itfGeneralMenuGetSpriteHandle(void) {
  return generalMenu_g_hSpr;
}

// 0x1c468d0
void itfGeneralMenuLoadSpriteMem(void) {
  ;
}

// 0x1c468e0
void itfGeneralMenuFreeSpriteMem(void) {
  ;
}

// 0x1c32690
void itfGeneralMenuLoadSpriteHnd(void) {
  ;
}

// 0x1c30830
void itfGeneralMenuFreeSpriteHnd(void) {
  if (!generalMenu_g_hSpr)
    return;
  generalMenu_g_hSpr = 0;
}

// 0x1c2e700
s32 itfGeneralMenuDecideFunc(dds3ProcessID_t *PID) {
  s32 SelectID;

  SelectID = itfMenuGetSelectID(PID);
  itfMenuSetFlagMenu(PID, SelectID, 8, 1);
  itfMenuSetFlagMenu(PID, SelectID, 64, 0);
  itfMenuSetFlag(PID, 8, 0);
  return SelectID;
}

// 0x1c30220
void itfGeneralMenuReturnFunc(dds3ProcessID_t *PID) {
  s32 SelectID;

  SelectID = itfMenuGetSelectID(PID);
  itfMenuSetFlagMenu(PID, SelectID, 8, 0);
  itfMenuSetFlag(PID, 8, 1);
}

// 0x1c2ee50
dds3ProcessID_t *itfGeneralMenuCreatePID(s32 a_x, s32 a_y) {
  dds3ProcessID_t *v6;

  v6 = itfMenuProcessStart();
  itfMenuSetOt(v6, 110);
  itfMenuSetDrawParam(v6, 6, 0);
  MenuSetDispType(v6, 0, 4);
  MenuSetDispType(v6, 1, 4);
  itfMenuSetSpriteData(v6, 0, a_x, a_y, 231, 0, 0, 0, 0, arrSprListTitle);
  itfMenuSetSpriteData(v6, 1, a_x + 6, a_y + 37, 0, 26, 14, 2, 0, arrSprListPanel);
  itfMenuSetSpriteData(v6, 2, a_x + 6, a_y + 37, 0, 26, 14, 2, 0, arrSprListSelect);
  itfMenuSetSpriteData(v6, 3, a_x, a_y, 3, 141, 150, 41, 0, arrSprListScrollBar);
  itfMenuSetImageColor(v6, 3, 0xA0u, 0x78u, 0x32u, 0x64u);
  itfMenuSetSubABGR(v6, 0x46145A6Eu);
  itfMenuSetStringStyle(v6, 0, 2);
  itfMenuSetStringStyle(v6, 1, 2);
  itfMenuSetStringStyle(v6, 2, 2);
  return v6;
}

// 0x1c47400
bool itfIconFreeSprMem(void) {
  return 0;
}

// 0x1c47410
bool itfIconLoadSprMem(void) {
  return 0;
}

// 0x1c47420
bool itfIconFreeSprHnd(void) {
  if (!g_hSpr)
    return 0;
  g_hSpr = 0;
  return 1;
}

// 0x1c474e0
bool itfIconLoadSprHnd(void) {
  goto LABEL_3;
LABEL_7:
  if (!g_hSpr)
    goto LABEL_11;
  g_hSpr = 0;
  return g_hSpr == 0;
LABEL_3:
  if (g_hSpr)
    goto LABEL_7;
LABEL_11:
  return g_hSpr == 0;
}

// 0x1c47620
void itfIconDrawSprite(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, s32 a_sprNo, DDS3_OT a_otNo) {

}

// 0x1c47680
void itfIconDrawBadStatus(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, u32 a_bstNo, DDS3_OT a_otNo) {
  void *v8;

  v8 = NewSpecific(s32, 0x15u);
  InitializeArray_55364416(v8, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__C5C4CF4B1762AFC9E048EFD7CA1FF1BF6B47104AE4C227BB64D5B401E744ABCA, 0);
  if (a_bstNo <= 0x14 && *((s32 *)&v8[2].klass + a_bstNo) >= 32)
  {
    return;
  }
}

// 0x1c47790
void itfIconDrawBullet(s32 a_x, s32 a_y, s32 a_z, u32 a_alphaRate, s32 a_itemID, DDS3_OT a_otNo) {
  ;
}

// 0x1c477a0
void itfIconInit(void) {
  itfIconLoadSprHnd();
}

// 0x1c47810
void itfIconFree(void) {
  if (!g_hSpr)
    return;
  g_hSpr = 0;
}

// 0x1c47920
void itfListSetListInit(dds3ProcessID_t *PID, ITF_LIST a_listNo, ITF_LIST_TYPE a_type, char *a_str, s32 a_num) {
  Il2CppObject *ProcessData;
  s64 v13;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u32)a_listNo <= 7)
  {
    v13 = *((u64 *)ProcessData[4].monitor + (u32)a_listNo + 4);
    *(u64 *)(v13 + 24) = a_str;
    v13 += 24;
    *(u32 *)(v13 - 4) = a_type;
    *(u32 *)(v13 + 8) = a_num;
    *(u32 *)(v13 - 8) = 1;
  }
}

// 0x1c47a50
void itfListSetListFont(dds3ProcessID_t *PID, ITF_LIST a_listNo, char *a_str, s32 a_num) {
  Il2CppObject *ProcessData;
  s64 v11;
  u32 *v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u32)a_listNo <= 7)
  {
    v11 = *((u64 *)ProcessData[4].monitor + (u32)a_listNo + 4);
    if ((*(u8 *)(v11 + 16) & 1) != 0)
    {
      *(u64 *)(v11 + 24) = a_str;
      v12 = (v11 + 24);
      v12[2] = a_num;
    }
  }
}

// 0x1c47b70
void itfListSetPos(dds3ProcessID_t *PID, s32 a_x, s32 a_y) {
  Il2CppObject *ProcessData;
  s32 klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass = ProcessData[2].klass;
  HIDWORD(ProcessData[2].klass) = a_x;
  LODWORD(ProcessData[2].monitor) = a_y;
  LODWORD(ProcessData[2].klass) = klass | 4;
}

// 0x1c47c60
void itfListDelList(dds3ProcessID_t *PID, ITF_LIST a_listNo) {
  Il2CppObject *ProcessData;
  u64 *monitor;
  s64 v8;
  s64 v9;
  s64 v10;
  s64 v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (a_listNo <= 7)
  {
    monitor = ProcessData[4].monitor;
    if (a_listNo < 0)
    {
      v9 = monitor[5];
      *(u32 *)(monitor[4] + 16) &= ~1u;
      *(u32 *)(v9 + 16) &= ~1u;
      v10 = monitor[7];
      *(u32 *)(monitor[6] + 16) &= ~1u;
      *(u32 *)(v10 + 16) &= ~1u;
      v11 = monitor[9];
      *(u32 *)(monitor[8] + 16) &= ~1u;
      *(u32 *)(v11 + 16) &= ~1u;
      *(u32 *)(monitor[10] + 16) &= ~1u;
      v8 = 7;
    }
    else
    {
      v8 = a_listNo;
    }
    *(u32 *)(monitor[v8 + 4] + 16) &= ~1u;
  }
}

// 0x1c47dd0
void itfListSetTypeApper(dds3ProcessID_t *PID, s32 a_type) {
  char v3;
  Il2CppObject *ProcessData;
  char v7;
  dds3ProcessID_t *id;

  id = PID;
  v3 = a_type;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (v3 < 0)
    v7 = 0;
  else
    v7 = v3;
  LOBYTE(ProcessData[3].monitor) = v7;
  LODWORD(ProcessData[2].klass) |= 8u;
}

// 0x1c47ec0
void itfListSetTypeDisapper(dds3ProcessID_t *PID, s32 a_type) {
  char v3;
  Il2CppObject *ProcessData;
  char v7;
  dds3ProcessID_t *id;

  id = PID;
  v3 = a_type;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (v3 < 0)
    v7 = 0;
  else
    v7 = v3;
  BYTE1(ProcessData[3].monitor) = v7;
  LODWORD(ProcessData[2].klass) |= 0x10u;
}

// 0x1c47fb0
void itfListSetFlagTarget(dds3ProcessID_t *PID, bool a_bTarget) {
  Il2CppObject *ProcessData;
  s32 v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (a_bTarget)
    v7 = 256;
  else
    v7 = 0;
  LODWORD(ProcessData[2].klass) = (s64)ProcessData[2].klass & 0xFFFFFEFF | v7;
}

// 0x1c480a0
void itfListSetFlagSelect(dds3ProcessID_t *PID, bool a_bSelect) {
  Il2CppObject *ProcessData;
  s32 v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (a_bSelect)
    v7 = 512;
  else
    v7 = 0;
  LODWORD(ProcessData[2].klass) = (s64)ProcessData[2].klass & 0xFFFFFDFF | v7;
}

// 0x1c48190
void itfListSetSelectNo(dds3ProcessID_t *PID, s32 a_listNo) {
  char v3;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  v3 = a_listNo;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  BYTE2(ProcessData[3].monitor) = v3;
}

// 0x1c48270
void itfListStart(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  LODWORD(ProcessData[2].klass) |= 2u;
}

// 0x1c48350
void itfListEnd(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  LODWORD(ProcessData[2].klass) &= ~2u;
}

// 0x1c48430
void itfListSetScrollParam(dds3ProcessID_t *PID, s32 a_listTopNo, s32 a_listNum) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  HIDWORD(ProcessData[3].monitor) = a_listTopNo;
  LODWORD(ProcessData[4].klass) = a_listNum;
}

// 0x1c48520
static void ListSetApperFade(tagITF_LIST_WK *wk) {
  tagITF_LIST_CB *cb;
  s32 posx;
  s32 posy;
  tagITF_LIST_CB *v7;
  tagITF_LIST_CB *v8;
  tagITF_LIST_CB *v9;
  tagITF_LIST_CB *v10;
  tagITF_LIST_CB *v11;
  tagITF_LIST_CB *v12;
  tagITF_LIST_CB *v13;
  tagITF_LIST_CB *v14;
  itfMover_t *mover;
  itfMover_t *v16;
  itfMover_t *v17;
  itfMover_t *v18;
  itfMover_t *v19;
  itfMover_t *v20;
  itfMover_t *v21;
  tagITF_LIST_CB *v22;
  tagITF_LIST_CB *v23;
  itfMover_t *v24;

  cb = wk->cb;
  posx = wk->posx;
  posy = wk->posy;
  v7 = cb[0];
  if ((v7->flags & 1) != 0)
  {
    mover = v7->mover;
    itfMoverSetParam(mover, posx, posy, posx, posy, 10);
    cb = wk->cb;
    posy += aItfListPanelH[cb[0]->type];
    v8 = cb[1];
    if ((v8->flags & 1) == 0)
    {
LABEL_5:
      v9 = cb[2];
      if ((v9->flags & 1) == 0)
        goto LABEL_6;
      goto LABEL_18;
    }
  }
  else
  {
    v8 = cb[1];
    if ((v8->flags & 1) == 0)
      goto LABEL_5;
  }
  v16 = v8->mover;
  itfMoverSetParam(v16, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[1]->type];
  v9 = cb[2];
  if ((v9->flags & 1) == 0)
  {
LABEL_6:
    v10 = cb[3];
    if ((v10->flags & 1) == 0)
      goto LABEL_7;
    goto LABEL_21;
  }
LABEL_18:
  v17 = v9->mover;
  itfMoverSetParam(v17, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[2]->type];
  v10 = cb[3];
  if ((v10->flags & 1) == 0)
  {
LABEL_7:
    v11 = cb[4];
    if ((v11->flags & 1) == 0)
      goto LABEL_8;
    goto LABEL_24;
  }
LABEL_21:
  v18 = v10->mover;
  itfMoverSetParam(v18, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[3]->type];
  v11 = cb[4];
  if ((v11->flags & 1) == 0)
  {
LABEL_8:
    v12 = cb[5];
    if ((v12->flags & 1) == 0)
      goto LABEL_9;
    goto LABEL_27;
  }
LABEL_24:
  v19 = v11->mover;
  itfMoverSetParam(v19, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[4]->type];
  v12 = cb[5];
  if ((v12->flags & 1) == 0)
  {
LABEL_9:
    v13 = cb[6];
    if ((v13->flags & 1) == 0)
      goto LABEL_10;
    goto LABEL_30;
  }
LABEL_27:
  v20 = v12->mover;
  itfMoverSetParam(v20, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[5]->type];
  v13 = cb[6];
  if ((v13->flags & 1) == 0)
  {
LABEL_10:
    v14 = cb[7];
    if ((v14->flags & 1) == 0)
      return;
    goto LABEL_33;
  }
LABEL_30:
  v21 = v13->mover;
  itfMoverSetParam(v21, posx, posy, posx, posy, 10);
  v22 = wk->cb;
  v23 = v22[6];
  v14 = v22[7];
  posy += aItfListPanelH[v23->type];
  if ((v14->flags & 1) != 0)
  {
LABEL_33:
    v24 = v14->mover;
    itfMoverSetParam(v24, posx, posy, posx, posy, 10);
  }
}

// 0x1c488c0
static void ListSetDisapperFade(tagITF_LIST_WK *wk) {
  tagITF_LIST_CB *cb;
  s32 posx;
  s32 posy;
  tagITF_LIST_CB *v7;
  tagITF_LIST_CB *v8;
  tagITF_LIST_CB *v9;
  tagITF_LIST_CB *v10;
  tagITF_LIST_CB *v11;
  tagITF_LIST_CB *v12;
  tagITF_LIST_CB *v13;
  tagITF_LIST_CB *v14;
  itfMover_t *mover;
  itfMover_t *v16;
  itfMover_t *v17;
  itfMover_t *v18;
  itfMover_t *v19;
  itfMover_t *v20;
  itfMover_t *v21;
  tagITF_LIST_CB *v22;
  tagITF_LIST_CB *v23;
  itfMover_t *v24;

  cb = wk->cb;
  posx = wk->posx;
  posy = wk->posy;
  v7 = cb[0];
  if ((v7->flags & 1) != 0)
  {
    mover = v7->mover;
    itfMoverSetParam(mover, posx, posy, posx, posy, 10);
    cb = wk->cb;
    posy += aItfListPanelH[cb[0]->type];
    v8 = cb[1];
    if ((v8->flags & 1) == 0)
    {
LABEL_5:
      v9 = cb[2];
      if ((v9->flags & 1) == 0)
        goto LABEL_6;
      goto LABEL_18;
    }
  }
  else
  {
    v8 = cb[1];
    if ((v8->flags & 1) == 0)
      goto LABEL_5;
  }
  v16 = v8->mover;
  itfMoverSetParam(v16, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[1]->type];
  v9 = cb[2];
  if ((v9->flags & 1) == 0)
  {
LABEL_6:
    v10 = cb[3];
    if ((v10->flags & 1) == 0)
      goto LABEL_7;
    goto LABEL_21;
  }
LABEL_18:
  v17 = v9->mover;
  itfMoverSetParam(v17, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[2]->type];
  v10 = cb[3];
  if ((v10->flags & 1) == 0)
  {
LABEL_7:
    v11 = cb[4];
    if ((v11->flags & 1) == 0)
      goto LABEL_8;
    goto LABEL_24;
  }
LABEL_21:
  v18 = v10->mover;
  itfMoverSetParam(v18, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[3]->type];
  v11 = cb[4];
  if ((v11->flags & 1) == 0)
  {
LABEL_8:
    v12 = cb[5];
    if ((v12->flags & 1) == 0)
      goto LABEL_9;
    goto LABEL_27;
  }
LABEL_24:
  v19 = v11->mover;
  itfMoverSetParam(v19, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[4]->type];
  v12 = cb[5];
  if ((v12->flags & 1) == 0)
  {
LABEL_9:
    v13 = cb[6];
    if ((v13->flags & 1) == 0)
      goto LABEL_10;
    goto LABEL_30;
  }
LABEL_27:
  v20 = v12->mover;
  itfMoverSetParam(v20, posx, posy, posx, posy, 10);
  cb = wk->cb;
  posy += aItfListPanelH[cb[5]->type];
  v13 = cb[6];
  if ((v13->flags & 1) == 0)
  {
LABEL_10:
    v14 = cb[7];
    if ((v14->flags & 1) == 0)
      return;
    goto LABEL_33;
  }
LABEL_30:
  v21 = v13->mover;
  itfMoverSetParam(v21, posx, posy, posx, posy, 10);
  v22 = wk->cb;
  v23 = v22[6];
  v14 = v22[7];
  posy += aItfListPanelH[v23->type];
  if ((v14->flags & 1) != 0)
  {
LABEL_33:
    v24 = v14->mover;
    itfMoverSetParam(v24, posx, posy, posx, posy, 10);
  }
}

// 0x1c48c60
static void ListSetApper(tagITF_LIST_WK *wk) {
  ListSetApperFade(wk);
  wk->flags |= 0x60000u;
}

// 0x1c48cd0
static void ListSetDisapper(tagITF_LIST_WK *wk) {
  ListSetDisapperFade(wk);
  wk->flags = wk->flags & 0xFFF9FFFF | 0x40000;
}

// 0x1c48d50
static bool ListUpdateMover(tagITF_LIST_WK *wk) {
  tagITF_LIST_CB *cb;
  tagITF_LIST_CB *v4;
  char v5;
  tagITF_LIST_CB *v6;
  itfMover_t *mover;
  s32 v8;
  itfMover_t *v9;
  s32 v10;
  tagITF_LIST_CB *v11;
  tagITF_LIST_CB *v12;
  tagITF_LIST_CB *v13;
  tagITF_LIST_CB *v14;
  tagITF_LIST_CB *v15;
  tagITF_LIST_CB *v16;
  itfMover_t *v18;
  s32 v19;
  itfMover_t *v20;
  s32 v21;
  itfMover_t *v22;
  s32 v23;
  itfMover_t *v24;
  s32 v25;
  itfMover_t *v26;
  itfMover_t *v27;

  cb = wk->cb;
  v4 = cb[0];
  if ((v4->flags & 1) == 0)
  {
    v5 = 1;
    v6 = cb[1];
    if ((v6->flags & 1) == 0)
      goto LABEL_13;
    goto LABEL_9;
  }
  mover = v4->mover;
  v8 = itfMoverUpdate(mover);
  cb = wk->cb;
  v5 = v8 != 1;
  v6 = cb[1];
  if ((v6->flags & 1) != 0)
  {
LABEL_9:
    v9 = v6->mover;
    v10 = itfMoverUpdate(v9);
    cb = wk->cb;
    if (v10 == 1)
      v5 = 0;
  }
LABEL_13:
  v11 = cb[2];
  if ((v11->flags & 1) != 0)
  {
    v18 = v11->mover;
    v19 = itfMoverUpdate(v18);
    cb = wk->cb;
    if (v19 == 1)
      v5 = 0;
    v12 = cb[3];
    if ((v12->flags & 1) == 0)
    {
LABEL_15:
      v13 = cb[4];
      if ((v13->flags & 1) == 0)
        goto LABEL_16;
      goto LABEL_30;
    }
  }
  else
  {
    v12 = cb[3];
    if ((v12->flags & 1) == 0)
      goto LABEL_15;
  }
  v20 = v12->mover;
  v21 = itfMoverUpdate(v20);
  cb = wk->cb;
  if (v21 == 1)
    v5 = 0;
  v13 = cb[4];
  if ((v13->flags & 1) == 0)
  {
LABEL_16:
    v14 = cb[5];
    if ((v14->flags & 1) == 0)
      goto LABEL_17;
    goto LABEL_35;
  }
LABEL_30:
  v22 = v13->mover;
  v23 = itfMoverUpdate(v22);
  cb = wk->cb;
  if (v23 == 1)
    v5 = 0;
  v14 = cb[5];
  if ((v14->flags & 1) == 0)
  {
LABEL_17:
    v15 = cb[6];
    if ((v15->flags & 1) == 0)
      goto LABEL_18;
LABEL_40:
    v26 = v15->mover;
    if (itfMoverUpdate(v26) == 1)
      v5 = 0;
    v16 = wk->cb[7];
    if ((v16->flags & 1) == 0)
      return v5;
    goto LABEL_45;
  }
LABEL_35:
  v24 = v14->mover;
  v25 = itfMoverUpdate(v24);
  cb = wk->cb;
  if (v25 == 1)
    v5 = 0;
  v15 = cb[6];
  if ((v15->flags & 1) != 0)
    goto LABEL_40;
LABEL_18:
  v16 = cb[7];
  if ((v16->flags & 1) == 0)
    return v5;
LABEL_45:
  v27 = v16->mover;
  if (itfMoverUpdate(v27) == 1)
    return 0;
  return v5;
}

// 0x1c48fc0
static void ListInit(tagITF_LIST_WK *wk) {
  wk->phSpr = 0;
}

// 0x1c48fd0
static void ListDelete(tagITF_LIST_WK *wk) {
  sprHandle_t *p_phSpr;
  sprHandle_t *phSpr;

  phSpr = wk->phSpr;
  p_phSpr = &wk->phSpr;
  if (phSpr)
  {
    p_phSpr = 0;
  }
}

// 0x1c48ff0
static void ListRelease(tagITF_LIST_WK *wk) {
  sprHandle_t *p_phSpr;

  if ((wk->flags & 1) != 0)
    return;
  p_phSpr = &wk->phSpr;
  if (wk->phSpr)
  {
    p_phSpr = 0;
  }
  if (!dds3ExistProcess(&wk->drawPID))
    goto LABEL_16;
  goto LABEL_9000;
  if (!dds3ExistProcess(&wk->drawPID))
  {
LABEL_16:
    wk->flags |= 1u;
    return;
  }
LABEL_9000:
  dds3KillProcess(&wk->drawPID, 1);
  goto LABEL_16;
}

// 0x1c49100
static void ListShutdown(dds3ProcessID_t *PID) {
  tagITF_LIST_WK *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  ListRelease(ProcessData);
}

// 0x1c491f0
static dds3ProcessFunc_t ListProcess(dds3ProcessID_t *PID) {
  tagITF_LIST_WK *ProcessData;
  sprHandle_t *p_phSpr;
  u32 flags;
  u32 v11;
  s32 count;
  dds3ProcessFunc_t v16;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (ProcessData->step)
  {
    case 0:
      ProcessData->phSpr = 0;
      p_phSpr = &ProcessData->phSpr;
      *((u32 *)p_phSpr + 7) = 1;
      return 0;
    case 1:
      flags = ProcessData->flags;
      if ((flags & 2) == 0)
        return 0;
      if ((flags & 8) != 0)
      {
        goto LABEL_42;
      }
      else
      {
        ProcessData->typeApper = 0;
        ProcessData->flags = flags | 8;
      }
LABEL_42:
      ListSetApperFade(ProcessData);
      ProcessData->flags |= 0x70000u;
      ProcessData->step = 2;
      return 0;
    case 2:
      if (!ListUpdateMover(ProcessData))
        return 0;
      ProcessData->step = 3;
      return 0;
    case 3:
      v11 = ProcessData->flags;
      if ((v11 & 2) != 0)
        return 0;
      if ((v11 & 0x10) != 0)
      {
        goto LABEL_46;
      }
      else
      {
        ProcessData->typeDisapper = 0;
        ProcessData->flags = v11 | 0x10;
      }
LABEL_46:
      ListSetDisapperFade(ProcessData);
      ProcessData->flags = ProcessData->flags & 0xFFF9FFFF | 0x40000;
      ProcessData->step = 4;
      return 0;
    case 4:
      if (!ListUpdateMover(ProcessData))
        return 0;
      ProcessData->flags &= 0xFFFEFFE7;
      ProcessData->step = 1;
      return 0;
    case 5:
      count = ProcessData->count;
      if (count == 3)
      {
        ProcessData->step = 6;
        return 0;
      }
      else
      {
        if (!count)
        {
          ProcessData->flags &= ~0x10000u;
          ListRelease(ProcessData);
          count = ProcessData->count;
        }
        ProcessData->count = count + 1;
        return 0;
      }
    case 6:
      v16 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v16, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v16;
    default:
      return 0;
  }
}

// 0x1c49670
void itfListDrawScrollBar(s32 a_x, s32 a_y, s32 a_topno, s32 a_selmax, f32 a_alphaRate) {
  int8x8_t *v7;
  f32 v8;
  s32 v9;

  v7 = NewSpecific(uint, 2u);
  v8 = (f32)(a_alphaRate * 120.0) / 255.0;
  v9 = v8;
  if (v8 >= 0.0)
    v9 = (u32)v8;
  v7[4].n64_u64[0] = vorr_s8(vdup_n_s32(v9 << 24), (int8x8_t)0x1E323C003214E6LL).n64_u64[0];
}

// 0x1c49710
static void ListDrawNumSmallFont(s32 a_x, s32 a_y, s32 a_z, u32 a_color, u8 a_alpha, s32 a_num) {
  NewSpecific(sbyte, 0x10u);
}

// 0x1c49760
static void ListDrawPanelNormal(tagITF_LIST_WK *wk, s32 a_x, s32 a_y, u8 a_alpha) {
  s32 v5;

  itfDrawMiscSpriteList((s32)itf, a_x, a_y, a_alpha, v5, aSprListPanelNormal);
}

// 0x1c497e0
static void ListDrawPanel(tagITF_LIST_WK *wk, ITF_LIST_TYPE a_type, s32 a_x, s32 a_y, u8 a_alpha) {
  if (a_type == 1)
  {
    itfDrawMiscSpriteList((s32)itf, a_type, a_x, a_y, a_alpha, (s32)aSprListPanelNormal);
    return;
  }
}

// 0x1c498c0
static u8 ListCalcMoverAlpha(tagITF_LIST_WK *wk, itfMover_t *mv) {
  u32 flags;
  s32 count;
  f32 v6;
  f32 frame;

  flags = wk->flags;
  if ((flags & 0x40000) == 0)
    return (s32)255.0;
  count = wk->count;
  v6 = count;
  frame = wk->frame;
  if ((flags & 0x20000) != 0)
  {
    if (count < 1)
      return (s32)255.0;
    return (s32)(f32)((f32)(v6 * 255.0) / frame);
  }
  else if (count < 1)
  {
    return (s32)0.0;
  }
  else
  {
    return (s32)(f32)(255.0 - (f32)((f32)(v6 * 255.0) / frame));
  }
}

// 0x1c49960
static void ListDrawCB(tagITF_LIST_WK *wk, s32 a_listNo) {
  s32 v3;
  tagITF_LIST_CB *v7;
  u32 flags;
  s32 count;
  f32 v10;
  f32 frame;
  f32 v12;
  s32 v13;
  s32 v14;
  u32 v15;
  sprHandle_t *v16;
  s32 v17;

  v7 = wk->cb[a_listNo];
  if ((v7->flags & 1) != 0)
  {
    flags = wk->flags;
    if ((flags & 0x40000) == 0)
      goto LABEL_13;
    count = wk->count;
    v10 = count;
    frame = wk->frame;
    if ((flags & 0x20000) == 0)
    {
      if (count < 1)
        v12 = 0.0;
      else
        v12 = 255.0 - (f32)((f32)(v10 * 255.0) / frame);
LABEL_14:
      ListDrawPanel(wk, v7->type, (s32)v3, (s32)v12);
      if (wk->selNo == a_listNo && (wk->flags & 0x100) != 0)
      {
        itfDrawMiscSpriteList((s32)itf, v13, v14, v15, v16, v17, aSprListPanelNormalSelect);
      }
      NewSpecific(sbyte, 0x10u);
      return;
    }
    if (count >= 1)
    {
      v12 = (f32)(v10 * 255.0) / frame;
      goto LABEL_14;
    }
LABEL_13:
    v12 = 255.0;
    goto LABEL_14;
  }
}

// 0x1c49b80
static dds3ProcessFunc_t ListDrawProcess(dds3ProcessID_t *PID) {
  tagITF_LIST_WK *ProcessData;
  u32 flags;
  s32 count;
  f32 v7;
  f32 frame;
  f32 v9;
  f32 v10;
  int8x8_t *v11;
  f32 v13;
  s32 v14;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  flags = ProcessData->flags;
  if ((flags & 0x10000) != 0)
  {
    if ((flags & 0x40000) == 0)
      goto LABEL_19;
    count = ProcessData->count;
    v7 = count;
    frame = ProcessData->frame;
    if ((flags & 0x20000) == 0)
    {
      if (count < 1)
        v9 = 0.0;
      else
        v9 = 255.0 - (f32)((f32)(v7 * 255.0) / frame);
LABEL_20:
      v10 = (u8)(s32)v9;
      v11 = NewSpecific(uint, 2u);
      v13 = (f32)(v10 * 120.0) / 255.0;
      v14 = v13;
      if (v13 >= 0.0)
        v14 = (u32)v13;
      v11[4].n64_u64[0] = vorr_s8(vdup_n_s32(v14 << 24), (int8x8_t)0x1E323C003214E6LL).n64_u64[0];
      ListDrawCB(ProcessData, 0);
      ListDrawCB(ProcessData, 1);
      ListDrawCB(ProcessData, 2);
      ListDrawCB(ProcessData, 3);
      ListDrawCB(ProcessData, 4);
      ListDrawCB(ProcessData, 5);
      ListDrawCB(ProcessData, 6);
      ListDrawCB(ProcessData, 7);
      return 0;
    }
    if (count >= 1)
    {
      v9 = (f32)(v7 * 255.0) / frame;
      goto LABEL_20;
    }
LABEL_19:
    v9 = 255.0;
    goto LABEL_20;
  }
  return 0;
}

// 0x1c49f20
dds3ProcessID_t *itfListProcessStart(void) {
  dds3ProcessID_t *v1;
  tagITF_LIST_WK *v2;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v6;
  dds3ProcessID_t *v7;
  tagITF_LIST_WK *p_fields;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = Allocate(tagITF_LIST_WK);
  _ctor(v2, 0);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_itf_ListProcess__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_itf_ListShutdown__, 0);
  started = dds3StartProcess("itfListMainProc", 1024, 0, 0, v3, v4, v2);
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_itf_ListDrawProcess__, 0);
  v7 = dds3StartProcess("itfListDrawProc", 11015, 0, 0, v6, 0, v2);
  v2->drawPID = v7;
  p_fields = &v2->fields;
  *(u64 *)&p_fields->posx = 0xE000000100LL;
  return started;
}

// 0x1c4a130
void itfListProcessEnd(dds3ProcessID_t *PID) {
  tagITF_LIST_WK *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!dds3ExistProcess(id))
    return;
  ListRelease(ProcessData);
  dds3KillProcess(id, 1);
}

// 0x1c4a280
bool itfListProcessCheck(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  if (!PID)
    return 0;
  return dds3ExistProcess(id);
}

// 0x1c4a310
static void MenuCtrlSelect(Menu_t *wk, s32 a_keytype, bool a_bPlaySE) {
  bool v7;
  s32 selMax;
  s64 nowHierarchy;
  s32 v11;
  s32 v12;
  s32 v13;
  u64 v16;
  char *v17;
  s32 *drwNo;
  s64 v20;
  char *v21;
  char *v22;
  s32 *v23;
  s32 v24;
  char *v25;
  s32 v26;
  s64 v27;
  char *v28;
  char *v29;

  v7 = evtBitCheck(675);
  if (a_keytype < 1 || v7)
    return;
  selMax = wk->selMax;
  nowHierarchy = wk->nowHierarchy;
  v11 = wk->selNo[nowHierarchy];
  v12 = wk->topNo[nowHierarchy];
  v13 = wk->drwNo[nowHierarchy];
  do
  {
    while (1)
    {
      if (MenuCtrlSelectSubHD(wk, a_keytype))
      {
        if (--selMax < 0)
          goto LABEL_21;
        goto LABEL_14;
      }
      v16 = wk->nowHierarchy;
      v17 = (char *)wk->topNo + v16 * 4;
      wk->selNo[v16] = v11;
      drwNo = wk->drwNo;
      *((u32 *)v17 + 8) = v12;
      drwNo[v16] = v13;
      if (--selMax < 0)
      {
LABEL_21:
        v20 = wk->nowHierarchy;
        v21 = (char *)wk->selNo + 4 * v20;
        v22 = (char *)wk->topNo + 4 * v20;
        *((u32 *)v21 + 8) = v11;
        *((u32 *)v22 + 8) = v12;
        wk->drwNo[v20] = v13;
        v23 = (v21 + 32);
        v24 = *((u32 *)v21 + 8);
        if (v11 != v24)
          goto LABEL_25;
        goto LABEL_24;
      }
LABEL_14:
      if (MenuUpdateSelectMenu(wk))
        goto LABEL_23;
    }
  }
  while (!MenuUpdateSelectMenu(wk));
LABEL_23:
  v20 = wk->nowHierarchy;
  v25 = (char *)wk->selNo + 4 * v20;
  v26 = *((u32 *)v25 + 8);
  v23 = (v25 + 32);
  v24 = v26;
  if (v11 != v26)
    goto LABEL_25;
LABEL_24:
  v27 = 4 * v20;
  v28 = (char *)wk->topNo + v27;
  v29 = (char *)wk->drwNo + v27;
  *((u32 *)v28 + 8) = v12;
  *((u32 *)v29 + 8) = v13;
  v24 = *v23;
LABEL_25:
  if (v11 != v24)
  {
    MenuUpdateLinkMover(wk);
    if (a_bPlaySE)
      goto LABEL_28;
    goto LABEL_9001;
    if (a_bPlaySE)
LABEL_28:
      SE(3);
LABEL_9001:
  }
}

// 0x1c4aa60
static s32 MenuRemakeLinkSub(Menu_t *wk) {
  s32 selMax;
  s32 *topNo;
  s64 nowHierarchy;
  char *v9;
  u32 *v10;
  s32 v11;
  s32 v12;
  char *v13;
  s32 v14;
  char *v15;
  s32 v16;
  bool updated;

  MenuMakeLink(wk);
  if (wk->select)
    goto LABEL_16;
  selMax = wk->selMax;
  if (selMax < 1)
    goto LABEL_16;
  topNo = wk->topNo;
  nowHierarchy = wk->nowHierarchy;
  v9 = (char *)topNo + 4 * nowHierarchy;
  v12 = *((u32 *)v9 + 8);
  v10 = v9 + 32;
  v11 = v12;
  if (v12)
  {
    if (v11 > selMax - wk->drwMax)
    {
      --wk->selNo[nowHierarchy];
      v13 = (char *)topNo + 4 * nowHierarchy;
      v14 = *((u32 *)v13 + 8) - 1;
      *((u32 *)v13 + 8) = v14;
      if (v14 < 0)
      {
        *v10 = 0;
LABEL_15:
        --wk->drwNo[nowHierarchy];
      }
    }
  }
  else
  {
    v15 = (char *)wk->selNo + 4 * nowHierarchy;
    v16 = *((u32 *)v15 + 8);
    if (v16 >= 1 && v16 == selMax)
    {
      *((u32 *)v15 + 8) = selMax - 1;
      goto LABEL_15;
    }
  }
LABEL_16:
  updated = MenuUpdateSelectMenu(wk);
  if (updated)
  {
    MenuUpdateLinkMover(wk);
    return wk->selMax;
  }
  MenuCtrlSelect(wk, 1, 0);
  return wk->selMax;
}

// 0x1c4afb0
static void MenuSetMoverAppear00(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverSetParam(mover, x, y + h * a_no, x, y + h * a_no, 10);
}

// 0x1c4b050
static void MenuSetMoverAppear01(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverSetParam(mover, x, y, x, y + h * a_no, 10);
}

// 0x1c4b0f0
static void MenuSetMoverAppear02(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  f32 v13;
  s32 v14;

  v13 = (f32)((f32)((f32)(w + x) / 10.0) * (f32)a_no) * 3.0;
  v14 = v13;
  if (v13 == INFINITY)
    v14 = 0x80000000;
  itfMoverSetParam(mover, -w - v14, y + h * a_no, x, y + h * a_no, 3 * a_no + 10);
}

// 0x1c4b1d0
static void MenuSetMoverAppear03(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverCB_t *cb;
  itfMoverCB_t *v14;
  f32 v15;
  s8 *wait;
  s8 *v17;
  s16 cb_num;
  s32 total_frm;
  s32 frame;
  u16 flag;

  if (!mover)
    return;
  cb = mover->cb;
  *(u64 *)&mover->cb_cnt = 0;
  *(u64 *)&mover->total_cnt = 0;
  v14 = cb[0];
  v15 = (y + h * a_no);
  v14->rate = -0.35;
  wait = v14->wait;
  v14->frame = 10;
  v14->posx = 512.0;
  v14->movx = 512.0;
  v14->tgtx = (f32)x;
  v14->posy = v15;
  v14->tgty = v15;
  v14->movy = v15;
  wait[0] = 0;
  v14->wait[1] = 0;
  v17 = v14->wait;
  if (v17[0] < 0)
  {
    v17[0] = 0;
    v17 = v14->wait;
    if ((v17[1] & 0x80000000) == 0)
      goto LABEL_9;
  }
  else if ((v17[1] & 0x80000000) == 0)
  {
LABEL_9:
    cb_num = mover->cb_num;
    mover->cb_cnt = 0;
    mover->cnt = 0;
    total_frm = mover->total_frm;
    frame = v14->frame;
    mover->total_cnt = 0;
    mover->cb_num = cb_num + 1;
    flag = mover->flag;
    mover->total_frm = total_frm + frame + v17[0] + v17[1];
    mover->flag = flag & 0xFFFC | 1;
    return;
  }
  v17[1] = 0;
  v17 = v14->wait;
  goto LABEL_9;
}

// 0x1c4b480
static void MenuSetMoverAppear04(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverSetParam(mover, x, h * a_no + 448, x, h * a_no + y, 10);
}

// 0x1c4b520
static void MenuSetMoverAppear(Menu_t *wk, s32 a_type) {
  itfMoverFunc_t MoverFunc;
  MenuImgDat_t *imgDat;
  s16 *v8;
  s32 v9;
  s64 v10;
  s32 v11;
  f32 v12;
  f32 v13;
  s16 cb_num;
  s32 total_frm;
  s32 frame;
  u16 flag;
  itfMover_t *v18;
  itfMoverCB_t *cb;
  itfMoverCB_t *v20;
  s8 *wait;
  s8 *v22;
  u32 v23;
  s64 v24;
  s64 v25;
  u32 v26;
  u32 v27;
  u32 v28;
  MenuSetMoverFunc_t v29;
  itfMover_t *mover;
  MenuImgDat_t *v32;
  s16 v33;
  s16 v34;
  s32 sw;
  itfMover_t *v36;
  itfMoverCB_t *v37;
  f32 v38;
  f32 v39;
  itfMoverCB_t *v40;
  s8 *v41;
  s8 *v42;
  s16 v43;
  s32 v44;
  s32 v45;
  u16 v46;
  MenuImgDat_t *v47;
  s32 sx;
  s32 sy;
  itfMover_t *v50;

  MoverFunc = wk->MoverFunc;
  if (MoverFunc)
    (MoverFunc->invoke_impl)(MoverFunc->method_code, 0, MoverFunc->method);
  imgDat = wk->imgDat;
  v8 = imgDat[1];
  if (a_type != 4)
  {
    if (wk->drwDefNum >= 1)
    {
      v23 = v8[16];
      v24 = a_type;
      v25 = 0;
      v26 = v8[17];
      v27 = v8[18];
      v28 = v8[19];
      do
      {
        mover = wk->mv[v25]->mover;
        v29 = itfMenuSetMoverFuncAppear[v24];
        (v29->invoke_impl)(v29->method_code, mover, (u32)v25++, v23, v26, v27, v28, v29->method);
      }
      while (v25 < wk->drwDefNum);
      imgDat = wk->imgDat;
    }
    v47 = imgDat[0];
    sx = v47->sx;
    sy = v47->sy;
    v50 = wk->mv_title->mover;
    itfMoverSetParam(v50, sx, sy, sx, sy, 10);
    goto LABEL_35;
  }
  if (wk->drwDefNum < 1)
    goto LABEL_25;
  v9 = v8[17];
  v10 = 0;
  v11 = v8[19];
  v12 = v8[16];
  v13 = v9;
  do
  {
    v18 = wk->mv[v10]->mover;
    if (v18)
    {
      cb = v18->cb;
      *(u64 *)&v18->cb_cnt = 0;
      *(u64 *)&v18->total_cnt = 0;
      v20 = cb[0];
      wait = v20->wait;
      v20->frame = 10;
      v20->posx = v12;
      v20->posy = v13;
      v20->rate = -0.35;
      v20->movx = v12;
      v20->movy = v13;
      v20->tgtx = v12;
      v20->tgty = (f32)v9;
      wait[0] = 10;
      v20->wait[1] = 0;
      v22 = v20->wait;
      if (v22[0] < 0)
      {
        v22[0] = 0;
        v22 = v20->wait;
        if (v22[1] < 0)
          goto LABEL_18;
      }
      else if (v22[1] < 0)
      {
LABEL_18:
        v22[1] = 0;
        v22 = v20->wait;
      }
      cb_num = v18->cb_num;
      v18->cb_cnt = 0;
      v18->cnt = 0;
      total_frm = v18->total_frm;
      frame = v20->frame;
      v18->total_cnt = 0;
      v18->cb_num = cb_num + 1;
      flag = v18->flag;
      v18->total_frm = total_frm + frame + v22[0] + v22[1];
      v18->flag = flag & 0xFFFC | 1;
    }
    ++v10;
    v9 += v11;
  }
  while (v10 < wk->drwDefNum);
  imgDat = wk->imgDat;
LABEL_25:
  v32 = imgDat[0];
  v33 = v32->sx;
  v34 = v32->sy;
  sw = v32->sw;
  v36 = wk->mv_title->mover;
  if (v36)
  {
    v37 = v36->cb;
    v38 = -sw;
    v39 = v34;
    *(u64 *)&v36->cb_cnt = 0;
    *(u64 *)&v36->total_cnt = 0;
    v40 = v37[0];
    v41 = v40->wait;
    v40->frame = 10;
    v40->rate = -0.35;
    v40->posx = v38;
    v40->posy = v39;
    v40->movx = v38;
    v40->movy = v39;
    v40->tgtx = (f32)v33;
    v40->tgty = v39;
    v41[0] = 0;
    v40->wait[1] = 0;
    v42 = v40->wait;
    if (v42[0] < 0)
    {
      v42[0] = 0;
      v42 = v40->wait;
      if (v42[1] < 0)
        goto LABEL_37;
    }
    else
    {
      if ((v42[1] & 0x80000000) == 0)
        goto LABEL_30;
LABEL_37:
      v42[1] = 0;
      v42 = v40->wait;
    }
LABEL_30:
    v43 = v36->cb_num;
    v36->cb_cnt = 0;
    v36->cnt = 0;
    v44 = v36->total_frm;
    v45 = v40->frame;
    v36->total_cnt = 0;
    v36->cb_num = v43 + 1;
    v46 = v36->flag;
    v36->total_frm = v44 + v45 + v42[0] + v42[1];
    v36->flag = v46 & 0xFFFC | 1;
  }
LABEL_35:
  wk->lflag |= 0x1040u;
}

// 0x1c4b8d0
static void MenuSetMoverDisappear00(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverCB_t *v10;
  bool v12;
  s32 v13;
  s32 v15;
  s32 v16;

  if (mover)
  {
    if (mover->cb_num >= 1)
    {
      v10 = mover->cb[mover->cb_cnt];
      itfMenuSetMoverDisappear00_fx = v10->posx;
      itfMenuSetMoverDisappear00_fy = v10->posy;
    }
  }
  v12 = itfMenuSetMoverDisappear00_fx == INFINITY;
  v13 = itfMenuSetMoverDisappear00_fx;
  if (v12)
    v15 = 0x80000000;
  else
    v15 = v13;
  if (itfMenuSetMoverDisappear00_fy == INFINITY)
    v16 = 0x80000000;
  else
    v16 = itfMenuSetMoverDisappear00_fy;
  itfMoverSetParam(mover, v15, v16, v15, v16, 10);
}

// 0x1c4b9c0
static void MenuSetMoverDisappear01(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverCB_t *v11;
  bool v13;
  s32 v14;
  s32 v16;
  s32 v17;

  if (mover)
  {
    if (mover->cb_num >= 1)
    {
      v11 = mover->cb[mover->cb_cnt];
      itfMenuSetMoverDisappear01_fx = v11->posx;
      itfMenuSetMoverDisappear01_fy = v11->posy;
    }
  }
  v13 = itfMenuSetMoverDisappear01_fx == INFINITY;
  v14 = itfMenuSetMoverDisappear01_fx;
  if (v13)
    v16 = 0x80000000;
  else
    v16 = v14;
  if (itfMenuSetMoverDisappear01_fy == INFINITY)
    v17 = 0x80000000;
  else
    v17 = itfMenuSetMoverDisappear01_fy;
  itfMoverSetParam(mover, v16, v17, v16, y, 10);
}

// 0x1c4bab0
static void MenuSetMoverDisappear02(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverCB_t *v12;
  s32 v14;
  bool v15;
  s32 v17;
  s32 v18;
  f32 v19;
  s32 v20;

  if (mover)
  {
    if (mover->cb_num >= 1)
    {
      v12 = mover->cb[mover->cb_cnt];
      itfMenuSetMoverDisappear02_fx = v12->posx;
      itfMenuSetMoverDisappear02_fy = v12->posy;
    }
  }
  v14 = itfMenuSetMoverDisappear02_fx;
  v15 = itfMenuSetMoverDisappear02_fx == INFINITY;
  if (v15)
    v17 = 0x80000000;
  else
    v17 = v14;
  if (itfMenuSetMoverDisappear02_fy == INFINITY)
    v18 = 0x80000000;
  else
    v18 = itfMenuSetMoverDisappear02_fy;
  v19 = (f32)((f32)(512 - x) / 10.0) * (f32)a_no;
  v20 = v19;
  if (v19 == INFINITY)
    v20 = 0x80000000;
  itfMoverSetParam(mover, v17, v18, v17 + v20, v18, a_no + 10);
}

// 0x1c4bbd0
static void MenuSetMoverDisappear03(itfMover_t *mover, s32 a_no, s32 x, s32 y, s32 w, s32 h) {
  itfMoverCB_t *cb;
  itfMoverCB_t *v14;
  f32 v15;
  s8 *wait;
  s8 *v17;
  s16 cb_num;
  s32 total_frm;
  s32 frame;
  u16 flag;

  if (!mover)
    return;
  cb = mover->cb;
  *(u64 *)&mover->cb_cnt = 0;
  *(u64 *)&mover->total_cnt = 0;
  v14 = cb[0];
  v14->frame = 10;
  v15 = (y + h * a_no);
  v14->tgtx = 512.0;
  v14->rate = -0.35;
  wait = v14->wait;
  v14->posx = (f32)x;
  v14->movx = (f32)x;
  v14->posy = v15;
  v14->tgty = v15;
  v14->movy = v15;
  wait[0] = 0;
  v14->wait[1] = 0;
  v17 = v14->wait;
  if (v17[0] < 0)
  {
    v17[0] = 0;
    v17 = v14->wait;
    if ((v17[1] & 0x80000000) == 0)
      goto LABEL_9;
  }
  else if ((v17[1] & 0x80000000) == 0)
  {
LABEL_9:
    cb_num = mover->cb_num;
    mover->cb_cnt = 0;
    mover->cnt = 0;
    total_frm = mover->total_frm;
    frame = v14->frame;
    mover->total_cnt = 0;
    mover->cb_num = cb_num + 1;
    flag = mover->flag;
    mover->total_frm = total_frm + frame + v17[0] + v17[1];
    mover->flag = flag & 0xFFFC | 1;
    return;
  }
  v17[1] = 0;
  v17 = v14->wait;
  goto LABEL_9;
}

// 0x1c4bd50
static void MenuSetMoverDisappear(Menu_t *wk, s32 a_type) {
  itfMoverFunc_t MoverFunc;
  MenuImgDat_t *imgDat;
  MenuImgDat_t *v8;
  s64 v9;
  f32 v10;
  f32 v11;
  int32x2_t v12;
  s16 cb_num;
  s32 total_frm;
  s32 frame;
  u16 flag;
  itfMover_t *v18;
  itfMoverCB_t *v20;
  float32x2_t v21;
  itfMoverCB_t *v22;
  s8 *wait;
  u64 v24;
  s8 *v25;
  s64 v26;
  s64 v27;
  MenuImgDat_t *v28;
  u32 sx;
  u32 sy;
  u32 sw;
  u32 sh;
  MenuSetMoverFunc_t v33;
  itfMover_t *mover;
  itfMover_t *v36;
  itfMoverCB_t *v39;
  s32 v41;
  bool v42;
  s32 v44;
  s32 v45;
  MenuImgDat_t *v46;
  s16 v47;
  s32 v48;
  itfMover_t *v50;
  itfMoverCB_t *v52;
  float32x2_t v53;
  itfMoverCB_t *cb;
  itfMoverCB_t *v55;
  u64 v56;
  s8 *v57;
  s8 *v58;
  s16 v59;
  s32 v60;
  s32 v61;
  u16 v62;

  MoverFunc = wk->MoverFunc;
  if (MoverFunc)
    (MoverFunc->invoke_impl)(MoverFunc->method_code, 1, MoverFunc->method);
  if (a_type != 4)
  {
    if (wk->drwDefNum >= 1)
    {
      v26 = 0;
      v27 = a_type;
      v28 = wk->imgDat[1];
      sx = v28->sx;
      sy = v28->sy;
      sw = v28->sw;
      sh = v28->sh;
      do
      {
        mover = wk->mv[v26]->mover;
        v33 = itfMenuSetMoverFuncDisappear[v27];
        (v33->invoke_impl)(v33->method_code, mover, (u32)v26++, sx, sy, sw, sh, v33->method);
      }
      while (v26 < wk->drwDefNum);
    }
    v36 = wk->mv_title->mover;
    if (v36 && v36->cb_num >= 1)
    {
      v39 = v36->cb[v36->cb_cnt];
      itfMenuSetMoverDisappear_fx = v39->posx;
      itfMenuSetMoverDisappear_fy = v39->posy;
    }
    v41 = itfMenuSetMoverDisappear_fx;
    v42 = itfMenuSetMoverDisappear_fx == INFINITY;
    if (v42)
      v44 = 0x80000000;
    else
      v44 = v41;
    if (itfMenuSetMoverDisappear_fy == INFINITY)
      v45 = 0x80000000;
    else
      v45 = itfMenuSetMoverDisappear_fy;
    itfMoverSetParam(v36, v44, v45, v44, v45, 10);
    goto LABEL_47;
  }
  imgDat = wk->imgDat;
  if (wk->drwDefNum < 1)
    goto LABEL_39;
  v8 = imgDat[1];
  v9 = 0;
  v10 = v8->sx;
  v11 = v8->sy;
  v12.n64_u64[0] = vdup_n_s32(0x7F800000u).n64_u64[0];
  do
  {
    v18 = wk->mv[v9]->mover;
    if (v18)
    {
      if (v18->cb_num >= 1)
      {
        v20 = v18->cb[v18->cb_cnt];
        itfMenuSetMoverDisappear_fx = v20->posx;
        itfMenuSetMoverDisappear_fy = v20->posy;
      }
      v21.n64_u64[0] = *(u64 *)&itfMenuSetMoverDisappear_fx;
      *(u64 *)&v18->cb_cnt = 0;
      *(u64 *)&v18->total_cnt = 0;
      v22 = v18->cb[0];
      wait = v22->wait;
      v22->frame = 10;
      v22->tgtx = v10;
      v22->tgty = v11;
      v22->rate = -0.35;
      v24 = vbsl_s8(vceq_f32(v21, v12), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(v21))).n64_u64[0];
      *(u64 *)&v22->posx = v24;
      *(u64 *)&v22->movx = v24;
      wait[0] = 0;
      v22->wait[1] = 0;
      v25 = v22->wait;
      if (v25[0] < 0)
      {
        v25[0] = 0;
        v25 = v22->wait;
        if (v25[1] < 0)
          goto LABEL_20;
      }
      else if (v25[1] < 0)
      {
LABEL_20:
        v25[1] = 0;
        v25 = v22->wait;
      }
      cb_num = v18->cb_num;
      v18->cb_cnt = 0;
      v18->cnt = 0;
      total_frm = v18->total_frm;
      frame = v22->frame;
      v18->total_cnt = 0;
      v18->cb_num = cb_num + 1;
      flag = v18->flag;
      v18->total_frm = total_frm + frame + v25[0] + v25[1];
      v18->flag = flag & 0xFFFC | 1;
    }
    ++v9;
  }
  while (v9 < wk->drwDefNum);
  imgDat = wk->imgDat;
LABEL_39:
  v46 = imgDat[0];
  v47 = v46->sy;
  v48 = v46->sw;
  v50 = wk->mv_title->mover;
  if (v50)
  {
    if (v50->cb_num >= 1)
    {
      v52 = v50->cb[v50->cb_cnt];
      itfMenuSetMoverDisappear_fx = v52->posx;
      itfMenuSetMoverDisappear_fy = v52->posy;
    }
    v53.n64_u64[0] = *(u64 *)&itfMenuSetMoverDisappear_fx;
    cb = v50->cb;
    *(u64 *)&v50->cb_cnt = 0;
    *(u64 *)&v50->total_cnt = 0;
    v55 = cb[0];
    v55->frame = 10;
    v55->rate = -0.35;
    v56 = vbsl_s8(vceq_f32(v53, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(v53))).n64_u64[0];
    v57 = v55->wait;
    *(u64 *)&v55->posx = v56;
    *(u64 *)&v55->movx = v56;
    v55->tgtx = (f32)-v48;
    v55->tgty = (f32)v47;
    v57[0] = 10;
    v55->wait[1] = 0;
    v58 = v55->wait;
    if (v58[0] < 0)
    {
      v58[0] = 0;
      v58 = v55->wait;
      if (v58[1] < 0)
        goto LABEL_49;
    }
    else
    {
      if ((v58[1] & 0x80000000) == 0)
        goto LABEL_46;
LABEL_49:
      v58[1] = 0;
      v58 = v55->wait;
    }
LABEL_46:
    v59 = v50->cb_num;
    v50->cb_cnt = 0;
    v50->cnt = 0;
    v60 = v50->total_frm;
    v61 = v55->frame;
    v50->total_cnt = 0;
    v50->cb_num = v59 + 1;
    v62 = v50->flag;
    v50->total_frm = v60 + v61 + v58[0] + v58[1];
    v50->flag = v62 & 0xFFFC | 1;
  }
LABEL_47:
  wk->lflag = wk->lflag & 0xEFBF | 0x1000;
}

// 0x1c4c210
static bool MenuUpdateMover(Menu_t *wk) {
  bool v3;
  s64 v4;
  s64 v5;
  itfMover_t *v6;
  s64 v8;
  itfMover_t *mover;
  MenuCB_tag *cb;

  if (wk->drwDefNum >= 1)
  {
    v3 = 0;
    v4 = 4;
    while (1)
    {
      v6 = *(itfMover_t *)(*((u64 *)&wk->mv->obj.klass + v4) + 16);
      if (itfMoverUpdate(*(itfMover_t *)(*((u64 *)&wk->mv->obj.klass + v4) + 16)) != 1)
        goto LABEL_11;
      goto LABEL_9000;
      if (itfMoverUpdate(v6) != 1)
      {
LABEL_11:
        v8 = *(u64 *)(*((u64 *)&wk->mv->obj.klass + v4) + 24);
        if (v8)
          *(u32 *)(v8 + 32) &= 0xFF7u;
        goto LABEL_6;
      }
LABEL_9000:
      v3 = 1;
LABEL_6:
      v5 = v4 - 3;
      ++v4;
      if (v5 >= wk->drwDefNum)
        goto LABEL_14;
    }
  }
  v3 = 0;
LABEL_14:
  mover = wk->mv_title->mover;
  if (itfMoverUpdate(wk->mv_title->mover) == 1)
    return 1;
  cb = wk->mv_title->cb;
  if (!cb)
    return v3;
  cb->lflag &= 0xFF7u;
  return v3;
}

// 0x1c4c380
static MenuCB_tag *MenuGetBlankMenu(Menu_t *wk) {
  MenuCB_tag *result;

  for (result = wk->pHead; result; result = result->pNext)
  {
    if ((result->lflag & 1) == 0)
      break;
  }
  return result;
}

// 0x1c4c3b0
void itfMenuLinkPrintf(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *p_declaringType;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  p_declaringType = ProcessData + 2;
  do
  {
    klass = p_declaringType->klass;
    p_declaringType = &p_declaringType->klass->_1.declaringType;
  }
  while (klass);
}

// 0x1c4c490
static void MenuCreateMenu(Menu_t *wk) {
  MenuCB_tag *v3;
  MenuCB_tag *pTail;
  MenuCB_tag *p_pNext;
  Menu_t *v6;

  v3 = Allocate(MenuCB_tag);
  _ctor(v3, 0);
  if (wk->pHead)
  {
    pTail = wk->pTail;
    v3->pPrev = pTail;
    p_pNext = &wk->pTail->pNext;
  }
  else
  {
    v3->pPrev = 0;
    p_pNext = &wk->pHead;
  }
  p_pNext = v3;
  v3->pNext = 0;
  v6 = wk;
  v6->pTail = v3;
  ++wk->nMenuSet;
}

// 0x1c4c570
static void MenuDeleteMenu(Menu_t *wk, MenuCB_tag *cb) {
  MenuCB_tag *v3;
  MenuCB_tag *pHead;
  MenuCB_tag *p_pHead;
  MenuCB_tag *pTail;
  MenuCB_tag *p_pTail;
  MenuCB_tag *v10;
  MenuCB_tag *v11;
  MenuCB_tag *v12;
  MenuCB_tag *v13;
  MenuCB_tag *p_pNext;
  MenuCB_tag *pNext;
  MenuCB_tag *pPrev;

  v3 = cb;
  if (cb)
  {
    p_pHead = &wk->pHead;
    pHead = wk->pHead;
    if (pHead)
    {
      p_pTail = &wk->pTail;
      pTail = wk->pTail;
      if (pTail)
      {
        if (v3 == pHead)
        {
          if (v3 == pTail)
          {
            p_pHead = 0;
            p_pTail = 0;
            p_pNext = &wk->pTail;
            v13 = 0;
          }
          else
          {
            pNext = v3->pNext;
            pNext->pPrev = 0;
            p_pNext = p_pHead;
            v13 = cb->pNext;
            p_pHead = v13;
          }
        }
        else if (v3 == pTail)
        {
          pPrev = v3->pPrev;
          pPrev->pNext = 0;
          p_pNext = &wk->pTail;
          v13 = cb->pPrev;
          p_pTail = v13;
        }
        else
        {
          v11 = v3->pPrev;
          v10 = v3->pNext;
          v10->pPrev = v11;
          v12 = cb->pPrev;
          v13 = cb->pNext;
          v12->pNext = v13;
          p_pNext = &v12->pNext;
        }
        cb = 0;
        --wk->nMenuSet;
      }
    }
  }
}

// 0x1c4c670
static bool MenuClearMenuSub(Menu_t *wk, MenuCB_tag *cb) {
  MenuCB_tag *pPrev;
  MenuCB_tag *pNext;

  if (cb)
  {
    pPrev = cb->pPrev;
    pNext = cb->pNext;
    ResetPar(cb, 0);
    if (pPrev)
    {
      cb->pPrev = pPrev;
    }
    if (pNext)
    {
      cb->pNext = pNext;
    }
  }
  return cb != 0;
}

// 0x1c4c6f0
bool itfMenuClearMenu(dds3ProcessID_t *PID, s32 a_id) {
  Menu_t *ProcessData;
  MenuCB_tag *pHead;
  MenuCB_tag *p_select;
  MenuCB_tag *pPrev;
  MenuCB_tag *pNext;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  pHead = ProcessData->pHead;
  if (!pHead)
    return 0;
  while (pHead->id != a_id)
  {
    pHead = pHead->pNext;
    if (!pHead)
      return 0;
  }
  p_select = &ProcessData->select;
  if (ProcessData->select == pHead)
  {
    p_select = 0;
    goto LABEL_15;
  }
LABEL_15:
  pPrev = pHead->pPrev;
  pNext = pHead->pNext;
  ResetPar(pHead, 0);
  if (pPrev)
  {
    pHead->pPrev = pPrev;
  }
  if (pNext)
  {
    pHead->pNext = pNext;
  }
  MenuRemakeLinkSub(ProcessData);
  return 1;
}

// 0x1c4c8d0
void itfMenuClearMenuAll(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  MenuCB_tag *klass;
  MenuCB_tag *pPrev;
  MenuCB_tag *p_pNext;
  MenuCB_tag *pNext;
  Il2CppObject *v9;
  Il2CppClass *v10;
  u32 *monitor;
  Il2CppClass *v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (klass)
  {
    do
    {
      pPrev = klass->pPrev;
      p_pNext = &klass->pNext;
      pNext = klass->pNext;
      ResetPar(klass, 0);
      if (pPrev)
      {
        klass->pPrev = pPrev;
      }
      if (pNext)
      {
        p_pNext = pNext;
      }
      klass = p_pNext;
    }
    while (p_pNext);
  }
  ProcessData[3].klass = 0;
  v9 = ProcessData + 3;
  HIDWORD(v9[10].klass) &= 0xFFC7u;
  LODWORD(v9[2].monitor) = 1;
  v10 = v9[6].klass;
  monitor = v9[6].monitor;
  BYTE4(v9[2].monitor) = 0;
  v12 = v9[7].klass;
  LODWORD(v10->_1.byval_arg.data) = 0;
  monitor[8] = 0;
  LODWORD(v12->_1.byval_arg.data) = 0;
  HIDWORD(v10->_1.byval_arg.data) = 0;
  monitor[9] = 0;
  HIDWORD(v12->_1.byval_arg.data) = 0;
  v10->_1.byval_arg.bits = 0;
  monitor[10] = 0;
  v12->_1.byval_arg.bits = 0;
  *(&v10->_1.byval_arg.bits + 1) = 0;
  monitor[11] = 0;
  *(&v12->_1.byval_arg.bits + 1) = 0;
}

// 0x1c4cab0
static bool _MenuSetMenu(MenuCB_tag *cb, s32 a_id, s32 a_parentId, char *a_str, itfMenuFunc_t a_func, char *a_tag) {
  if (cb)
  {
    cb->id = a_id;
    cb->parentId = a_parentId;
    cb->str = a_str;
    cb->hierarchy = -1;
    cb->no = -1;
    *(u64 *)&cb->decideSE = -1;
    cb->tag = a_tag;
    cb->func = a_func;
    cb->funcDraw = 0;
    cb->funcText = 0;
    *(u64 *)&cb->gflag = 0x100000043LL;
  }
  return cb != 0;
}

// 0x1c2f190
void itfMenuSetMenuTitle(dds3ProcessID_t *PID, char *a_str, char *a_tag) {
  Il2CppObject *ProcessData;
  char *monitor;
  char *v10;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  monitor = ProcessData[3].monitor;
  if (monitor)
  {
    *((u16 *)monitor + 13) = -1;
    *((u64 *)monitor + 6) = a_str;
    *((u64 *)monitor + 2) = -1;
    monitor[24] = -1;
    *(u64 *)(monitor + 36) = -1;
    *((u64 *)monitor + 7) = a_tag;
    *((u64 *)monitor + 11) = 0;
    *((u64 *)monitor + 12) = 0;
    *((u64 *)monitor + 13) = 0;
    v10 = monitor + 104;
    *(u64 *)(v10 - 76) = 0x100000043LL;
  }
}

// 0x1c4cb70
bool itfMenuSetMenu(dds3ProcessID_t *PID, s32 a_id, s32 a_parentId, char *a_str, itfMenuFunc_t a_func, char *a_tag) {
  Menu_t *ProcessData;
  MenuCB_tag *pHead;
  itfMenuTextFunc_t *p_funcText;
  Menu_t *v19;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v19 = ProcessData;
  if (a_id < 0)
    return a_id >= 0;
  pHead = ProcessData->pHead;
  if (pHead)
  {
    while ((pHead->lflag & 1) != 0)
    {
      pHead = pHead->pNext;
      if (!pHead)
        goto LABEL_14;
    }
    goto LABEL_17;
  }
LABEL_14:
  MenuCreateMenu(v19);
  pHead = ProcessData->pTail;
LABEL_17:
  if (pHead)
  {
    pHead->id = a_id;
    pHead->parentId = a_parentId;
    pHead->str = a_str;
    pHead->hierarchy = -1;
    pHead->no = -1;
    *(u64 *)&pHead->decideSE = -1;
    pHead->tag = a_tag;
    pHead->func = a_func;
    pHead->funcDraw = 0;
    pHead->funcText = 0;
    p_funcText = &pHead->funcText;
    *(itfMenuTextFunc_t *)((char *)p_funcText - 76) = (itfMenuTextFunc_t)0x100000043LL;
  }
  return a_id >= 0;
}

// 0x1c2f330
bool itfMenuSetRootMenu(dds3ProcessID_t *PID, s32 a_id, char *a_str, itfMenuFunc_t a_func, char *a_tag) {
  return itfMenuSetMenu(PID, a_id, -1, a_str, a_func, a_tag);
}

// 0x1c4cd80
static void MenuSetDispType(dds3ProcessID_t *PID, s32 a_mode, s32 a_type) {
  char v4;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  v4 = a_type;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u32)a_mode <= 1)
    *((u8 *)ProcessData[6].monitor + (u32)a_mode + 32) = v4;
}

// 0x1c46e30
void itfMenuSetMoveAppear(dds3ProcessID_t *PID, s32 a_type) {
  MenuSetDispType(PID, 0, a_type);
}

// 0x1c46ea0
void itfMenuSetMoveDisappear(dds3ProcessID_t *PID, s32 a_type) {
  MenuSetDispType(PID, 1, a_type);
}

// 0x1c302b0
void itfMenuSetFlag(dds3ProcessID_t *PID, ITFMENU_GF a_bit, bool a_bSet) {
  Il2CppObject *ProcessData;
  s32 klass;
  s32 v10;
  s32 v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[13].klass;
  v10 = klass & ~a_bit;
  v11 = klass | a_bit;
  if (!a_bSet)
    v11 = v10;
  LODWORD(ProcessData[13].klass) = v11;
}

// 0x1c4ce80
static bool _MenuSetFlagMenu(Menu_t *wk, s32 a_id, ITFMENU_CB_GF a_bit, bool a_bSet, bool a_bGlobal) {
  MenuCB_tag *pHead;
  bool result;
  u32 v8;
  u32 lflag;
  s32 v10;
  u32 v11;

  pHead = wk->pHead;
  if (a_id < 0)
  {
    if (pHead)
    {
      if (a_bSet)
      {
        if (a_bGlobal)
        {
          do
          {
            if ((pHead->lflag & 1) != 0)
              pHead->gflag |= (u16)a_bit;
            pHead = pHead->pNext;
          }
          while (pHead);
        }
        else
        {
          do
          {
            lflag = pHead->lflag;
            if ((lflag & 1) != 0)
              pHead->lflag = lflag | (u16)a_bit;
            pHead = pHead->pNext;
          }
          while (pHead);
        }
      }
      else
      {
        v10 = (u16)a_bit ^ 0xFFFF;
        if (a_bGlobal)
        {
          do
          {
            if ((pHead->lflag & 1) != 0)
              pHead->gflag &= v10;
            pHead = pHead->pNext;
          }
          while (pHead);
        }
        else
        {
          do
          {
            v11 = pHead->lflag;
            if ((v11 & 1) != 0)
              pHead->lflag = v11 & v10;
            pHead = pHead->pNext;
          }
          while (pHead);
        }
      }
    }
    return 1;
  }
  else if (pHead)
  {
    while (1)
    {
      v8 = pHead->lflag;
      if ((v8 & 1) != 0 && pHead->id == a_id)
        break;
      pHead = pHead->pNext;
      if (!pHead)
        return 0;
    }
    if (a_bSet)
    {
      result = 1;
      if (a_bGlobal)
        pHead->gflag |= (u16)a_bit;
      else
        pHead->lflag = v8 | (u16)a_bit;
    }
    else
    {
      result = 1;
      if (a_bGlobal)
        pHead->gflag = LOWORD(pHead->gflag) & ~a_bit;
      else
        pHead->lflag = v8 & (u16)~(u16)a_bit;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

// 0x1c2f3d0
bool itfMenuSetFlagMenu(dds3ProcessID_t *PID, s32 a_id, ITFMENU_CB_GF a_bit, bool a_bSet) {
  u16 v6;
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  bool result;
  s32 namespaze_high;
  s32 v13;
  s32 v14;
  dds3ProcessID_t *id;

  id = PID;
  v6 = a_bit;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass = ProcessData[2].klass;
  if (a_id < 0)
  {
    if (klass)
    {
      if (a_bSet)
      {
        do
        {
          if (((s64)klass->_1.byval_arg.data & 1) != 0)
            HIDWORD(klass->_1.namespaze) |= v6;
          klass = klass->_1.declaringType;
        }
        while (klass);
      }
      else
      {
        do
        {
          if (((s64)klass->_1.byval_arg.data & 1) != 0)
            HIDWORD(klass->_1.namespaze) &= v6 ^ 0xFFFF;
          klass = klass->_1.declaringType;
        }
        while (klass);
      }
    }
    return 1;
  }
  else if (klass)
  {
    while (((s64)klass->_1.byval_arg.data & 1) == 0 || LODWORD(klass->_1.name) != a_id)
    {
      klass = klass->_1.declaringType;
      if (!klass)
        return 0;
    }
    namespaze_high = HIDWORD(klass->_1.namespaze);
    result = 1;
    v13 = namespaze_high | v6;
    v14 = namespaze_high & (v6 ^ 0xFFFF);
    if (a_bSet)
      v14 = v13;
    HIDWORD(klass->_1.namespaze) = v14;
  }
  else
  {
    return 0;
  }
  return result;
}

// 0x1c4cfc0
bool itfMenuGetFlag(dds3ProcessID_t *PID, u32 a_bit) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return ((s64)ProcessData[13].klass & a_bit) != 0;
  return ((s64)ProcessData[13].klass & a_bit) != 0;
}

// 0x1c4d0a0
bool itfMenuGetFlagMenu(dds3ProcessID_t *PID, s32 a_id, u16 a_bit) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  while (((s64)klass->_1.byval_arg.data & 1) == 0 || LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return 0;
  }
  return (u16)(a_bit & WORD2(klass->_1.namespaze)) != 0;
}

// 0x1c4d1d0
s32 *itfMenuGetIdList(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 *result;
  Il2CppClass *klass;
  s32 v7;
  char *v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  result = NewSpecific(s32, (u32)ProcessData[6].klass);
  klass = ProcessData[2].klass;
  if (klass)
  {
    v7 = 0;
    do
    {
      if (((s64)klass->_1.byval_arg.data & 1) != 0)
      {
        v8 = (char *)result + 4 * v7++;
        *((u32 *)v8 + 8) = klass->_1.name;
      }
      klass = klass->_1.declaringType;
    }
    while (klass);
  }
  return result;
}

// 0x1c4d300
bool itfMenuChkExistMenu(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  while (((s64)klass->_1.byval_arg.data & 1) == 0 || LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return 0;
  }
  return 1;
}

// 0x1c4d420
ITFMENU_WAIT_TYPE itfMenuGetWaitType(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor;
  s32 klass_high;
  s32 v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = (s32)ProcessData[5].monitor;
  if (monitor == 1)
    return monitor;
  if (monitor == 6)
  {
    klass_high = HIDWORD(ProcessData[6].klass);
    if (klass_high == 4)
      v7 = 3;
    else
      v7 = 0;
    if (klass_high == 5)
      return 4;
    else
      return v7;
  }
  return 0;
}

// 0x1c4d540
ITFMENU_WAIT_TYPE itfMenuGetWaitType2(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor;
  s32 result;
  s32 klass_high;
  s32 v8;
  s32 v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[5].monitor;
  switch (monitor)
  {
    case 1:
      goto LABEL_11;
    case 3:
    case 4:
      monitor = 2;
LABEL_11:
      result = monitor;
      break;
    case 6:
      klass_high = HIDWORD(ProcessData[6].klass);
      if (klass_high == 4)
        v8 = 3;
      else
        v8 = 0;
      if (klass_high == 5)
        v9 = 4;
      else
        v9 = v8;
      result = v9;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x1c4d690
static MenuCB_tag *MenuGetMenu(Menu_t *wk, s32 a_hierarchy, s32 a_no) {
  MenuCB_tag *result;

  for (result = wk->pHead; result; result = result->pNext)
  {
    if ((result->lflag & 1) != 0 && result->hierarchy == a_hierarchy && result->no == a_no)
      break;
  }
  return result;
}

// 0x1c4d6d0
static MenuCB_tag *MenuGetSelectMenu(Menu_t *wk) {
  s64 nowHierarchy;
  s32 v4;
  MenuCB_tag *result;

  nowHierarchy = wk->nowHierarchy;
  v4 = wk->selNo[nowHierarchy];
  result = wk->pHead;
  if (!result)
    return result;
  do
  {
    if ((result->lflag & 1) != 0 && (u8)result->hierarchy == (u8)nowHierarchy && v4 == result->no)
    {
      break;
    }
    result = result->pNext;
  }
  while (result);
  return result;
}

// 0x1c4aea0
static bool MenuUpdateSelectMenu(Menu_t *wk) {
  MenuCB_tag *p_select;
  MenuCB_tag *select;
  MenuCB_tag *pHead;
  MenuCB_tag *v6;
  bool result;
  s32 hierarchy;

  p_select = &wk->select;
  select = wk->select;
  if (select)
    select->lflag &= ~4u;
  wk->select = 0;
  pHead = wk->pHead;
  if (pHead)
  {
    while (1)
    {
      if ((pHead->lflag & 1) != 0)
      {
        hierarchy = (u8)pHead->hierarchy;
        if (hierarchy == (u8)wk->nowHierarchy && wk->selNo[(char)hierarchy] == pHead->no)
        {
          break;
        }
      }
      pHead = pHead->pNext;
      if (!pHead)
        goto LABEL_4;
    }
    p_select = pHead;
    v6 = p_select;
    if (p_select)
      goto LABEL_5;
    return 0;
  }
LABEL_4:
  v6 = p_select;
  if (!p_select)
    return 0;
LABEL_5:
  if ((v6->gflag & 1) != 0)
  {
    result = 1;
  }
  else
  {
    result = 1;
    if (select)
    {
      if (wk->nMenuSet >= 2)
      {
        p_select = select;
        v6 = p_select;
        result = 0;
      }
    }
  }
  v6->lflag |= 4u;
  return result;
}

// 0x1c4a840
static void MenuUpdateLinkMover(Menu_t *wk) {
  s32 selMax;
  s32 drwDefMax;
  MenuMover_t *v5;
  MenuMover_t *v6;
  MenuMover_t *v7;
  MenuMover_t *v8;
  MenuMover_t *v9;
  MenuMover_t *v10;
  MenuMover_t *v11;
  MenuMover_t *v12;
  MenuMover_t *v13;
  MenuMover_t *v14;
  MenuMover_t *v15;
  MenuMover_t *v16;
  MenuMover_t *v17;
  MenuMover_t *v18;
  MenuMover_t *v19;
  MenuMover_t *v20;
  MenuCB_tag *pHead;
  s32 v22;
  s32 v23;
  MenuMover_t *v24;

  selMax = wk->selMax;
  drwDefMax = wk->drwDefMax;
  if ((wk->gflag & 0x400) != 0)
  {
    wk->drwDefNum = drwDefMax;
    if (selMax < drwDefMax)
    {
      wk->drwMax = selMax;
      goto LABEL_8;
    }
  }
  else
  {
    if (selMax < drwDefMax)
    {
      wk->drwMax = selMax;
      wk->drwDefNum = selMax;
      goto LABEL_8;
    }
    wk->drwDefNum = drwDefMax;
  }
  wk->drwMax = drwDefMax;
LABEL_8:
  v5 = wk->mv[0];
  v5->cb = 0;
  v6 = wk->mv[1];
  v6->cb = 0;
  v7 = wk->mv[2];
  v7->cb = 0;
  v8 = wk->mv[3];
  v8->cb = 0;
  v9 = wk->mv[4];
  v9->cb = 0;
  v10 = wk->mv[5];
  v10->cb = 0;
  v11 = wk->mv[6];
  v11->cb = 0;
  v12 = wk->mv[7];
  v12->cb = 0;
  v13 = wk->mv[8];
  v13->cb = 0;
  v14 = wk->mv[9];
  v14->cb = 0;
  v15 = wk->mv[10];
  v15->cb = 0;
  v16 = wk->mv[11];
  v16->cb = 0;
  v17 = wk->mv[12];
  v17->cb = 0;
  v18 = wk->mv[13];
  v18->cb = 0;
  v19 = wk->mv[14];
  v19->cb = 0;
  v20 = wk->mv[15];
  v20->cb = 0;
  pHead = wk->pHead;
  if (pHead)
  {
    v22 = 0;
    v23 = wk->topNo[wk->nowHierarchy];
    do
    {
      if ((pHead->lflag & 1) != 0 && pHead->hierarchy == wk->nowHierarchy && v22 + v23 == pHead->no)
      {
        v24 = wk->mv[v22];
        v24->cb = pHead;
        if (++v22 >= wk->drwDefNum)
          break;
      }
      pHead = pHead->pNext;
    }
    while (pHead);
  }
}

// 0x1c4d790
static void MenuUpdateNextLink(Menu_t *wk) {
  s64 nowHierarchy;
  s32 v5;
  MenuCB_tag *i;
  MenuCB_tag *v7;
  s32 id;
  MenuCB_tag *pHead;
  s32 v10;
  s32 parentId;
  bool updated;

  nowHierarchy = wk->nowHierarchy;
  v5 = wk->selNo[nowHierarchy];
  for (i = &wk->pHead; ; i = &v7->pNext)
  {
    v7 = i;
    if ((v7->lflag & 1) != 0 && (u8)v7->hierarchy == (u8)nowHierarchy && v5 == v7->no)
    {
      break;
    }
  }
  id = v7->id;
  wk->selMax = 0;
  pHead = wk->pHead;
  if (pHead)
  {
    v10 = 0;
    do
    {
      if ((pHead->lflag & 1) != 0)
      {
        parentId = pHead->parentId;
        pHead->no = -1;
        if (parentId == id)
        {
          pHead->no = v10++;
          wk->selMax = v10;
        }
      }
      pHead = pHead->pNext;
    }
    while (pHead);
  }
  ++wk->nowHierarchy;
  updated = MenuUpdateSelectMenu(wk);
  if (updated)
  {
    MenuUpdateLinkMover(wk);
    return;
  }
  MenuCtrlSelect(wk, 3, 0);
}

// 0x1c4d960
static void MenuUpdatePrevLink(Menu_t *wk) {
  s64 nowHierarchy;
  s32 v5;
  MenuCB_tag *i;
  MenuCB_tag *v7;
  MenuCB_tag *pHead;
  s32 parentId;
  s32 v10;
  MenuCB_tag *pNext;
  s32 v12;
  s32 v13;
  s64 v14;
  s32 *topNo;
  char *v17;
  s64 v21;
  s32 *v23;

  nowHierarchy = wk->nowHierarchy;
  v5 = wk->selNo[nowHierarchy];
  for (i = &wk->pHead; ; i = &v7->pNext)
  {
    v7 = i;
    if ((v7->lflag & 1) != 0 && (u8)v7->hierarchy == (u8)nowHierarchy && v5 == v7->no)
    {
      break;
    }
  }
  pHead = wk->pHead;
  if (pHead)
  {
    parentId = v7->parentId;
    v10 = -1;
    pNext = wk->pHead;
    while ((pNext->lflag & 1) == 0 || pNext->id != parentId)
    {
      pNext = pNext->pNext;
      if (!pNext)
        goto LABEL_18;
    }
    v10 = pNext->parentId;
LABEL_18:
    wk->selMax = 0;
    v12 = 0;
    do
    {
      v13 = pHead->parentId;
      pHead->no = -1;
      if (v13 == v10)
      {
        pHead->no = v12++;
        wk->selMax = v12;
      }
      pHead = pHead->pNext;
    }
    while (pHead);
  }
  else
  {
    wk->selMax = 0;
  }
  v14 = wk->nowHierarchy;
  topNo = wk->topNo;
  v17 = (char *)wk->selNo + 4 * v14;
  wk->nowHierarchy = v14 - 1;
  *((u32 *)v17 + 8) = 0;
  topNo[v14] = 0;
  wk->drwNo[v14] = 0;
  if (MenuUpdateSelectMenu(wk))
  {
    MenuUpdateLinkMover(wk);
    return;
  }
  v21 = wk->nowHierarchy;
  v23 = wk->topNo;
  wk->selNo[v21] = 0;
  v23[v21] = 0;
  wk->drwNo[v21] = 0;
  MenuCtrlSelect(wk, 3, 0);
}

// 0x1c4ac10
static void MenuMakeLink(Menu_t *wk) {
  MenuCB_tag *pHead;
  s32 selMax;
  s32 parentId;
  MenuCB_tag *pNext;
  MenuCB_tag *i;
  MenuCB_tag *v8;
  MenuCB_tag *j;
  MenuCB_tag *k;
  MenuCB_tag *m;

  pHead = wk->pHead;
  wk->selMax = 0;
  if (pHead)
  {
    do
    {
      if ((pHead->lflag & 1) != 0)
      {
        pHead->pParent = 0;
        pHead->hierarchy = -1;
        pHead->no = -1;
        pHead->lflag &= 0xFFFDu;
        parentId = pHead->parentId;
        if (parentId == -1)
        {
          selMax = wk->selMax;
          pHead->hierarchy = 0;
          pHead->no = selMax;
          wk->selMax = selMax + 1;
        }
        else if (pHead->id == parentId)
        {
          pHead->hierarchy = 0;
          pHead->no = -1;
        }
      }
      pHead = pHead->pNext;
    }
    while (pHead);
    pNext = wk->pHead;
    if (pNext)
    {
      do
      {
        if ((pNext->lflag & 1) != 0 && !pNext->hierarchy)
        {
          for (i = wk->pHead; i; i = i->pNext)
          {
            if ((i->lflag & 1) != 0 && i->parentId == pNext->id)
            {
              i->pParent = pNext;
              i->hierarchy = 1;
              pNext->lflag |= 2u;
            }
          }
        }
        pNext = pNext->pNext;
      }
      while (pNext);
      v8 = wk->pHead;
      if (v8)
      {
        do
        {
          if ((v8->lflag & 1) != 0 && v8->hierarchy == 1)
          {
            for (j = wk->pHead; j; j = j->pNext)
            {
              if ((j->lflag & 1) != 0 && j->parentId == v8->id)
              {
                j->pParent = v8;
                j->hierarchy = 2;
                v8->lflag |= 2u;
              }
            }
          }
          v8 = v8->pNext;
        }
        while (v8);
        for (k = wk->pHead; k; k = k->pNext)
        {
          if ((k->lflag & 1) != 0 && k->hierarchy == 2)
          {
            for (m = wk->pHead; m; m = m->pNext)
            {
              if ((m->lflag & 1) != 0 && m->parentId == k->id)
              {
                m->pParent = k;
                m->hierarchy = 3;
                k->lflag |= 2u;
              }
            }
          }
        }
      }
    }
  }
  MenuUpdateLinkMover(wk);
  wk->lflag |= 0x10u;
}

// 0x1c4dbb0
void itfMenuUpdateLink(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  HIDWORD(ProcessData[13].klass) |= 8u;
}

// 0x1c300f0
void itfMenuStart(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass_high;
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
  klass_high = HIDWORD(ProcessData[13].klass);
  if ((klass_high & 0x20) == 0)
  {
    if ((klass_high & 0x10) == 0)
    {
      v7 = id;
      itfMenuUpdateLink(v7);
      klass_high = HIDWORD(ProcessData[13].klass);
    }
    HIDWORD(ProcessData[13].klass) = klass_high | 0x20;
  }
}

// 0x1c468f0
s32 itfMenuGetSelectID(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[3].klass;
  if (klass)
    return (s32)klass->_1.name;
  else
    return -1;
}

// 0x1c4dc90
s32 itfMenuGetHierarchy(dds3ProcessID_t *PID) {
  char *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return ProcessData[92];
  return ProcessData[92];
}

// 0x1c4dd70
s32 itfMenuGetMenuNo(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (!klass)
    return -2;
  while (LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return -2;
  }
  if (BYTE4(ProcessData[5].monitor) == LOBYTE(klass->_1.namespaze))
    return SWORD1(klass->_1.namespaze);
  else
    return -1;
}

// 0x1c4deb0
bool itfMenuChkMenuTop(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  s32 v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  while (LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return 0;
  }
  v8 = SWORD1(klass->_1.namespaze);
  return (v8 & 0x80000000) == 0
      && *((u32 *)ProcessData[9].monitor + SBYTE4(ProcessData[5].monitor) + 8) == (u16)v8;
}

// 0x1c4dff0
bool itfMenuChkHead(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return LODWORD(ProcessData[2].klass->_1.name) == a_id;
  return LODWORD(ProcessData[2].klass->_1.name) == a_id;
}

// 0x1c4e0e0
void itfMenuSetSelectHead(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *v7;
  s32 name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass = ProcessData[2].klass;
  if (klass && (BYTE4(klass->_1.namespaze) & 1) != 0 && (SLOBYTE(klass->_1.namespaze) & 0x80000000) == 0)
  {
    v7 = id;
    name = klass->_1.name;
    itfMenuSetSelectID(v7, name);
  }
}

// 0x1c4e4a0
MenuSelectData *itfMenuCreateSelectData(dds3ProcessID_t *PID) {
  Menu_t *ProcessData;
  MenuSelectData *v5;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u8)ProcessData->nowHierarchy == 255)
    return 0;
  v5 = (MenuSelectData *)Allocate(MenuSelectData);
  _ctor(v5, ProcessData, 0);
  return v5;
}

// 0x1c4e5d0
bool itfMenuSetSelectData(dds3ProcessID_t *PID, MenuSelectData *menuData) {
  Menu_t *ProcessData;
  s64 nowHierarchy;
  s32 *topNo;
  bool updated;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  nowHierarchy = ProcessData->nowHierarchy;
  topNo = ProcessData->topNo;
  ProcessData->selNo[nowHierarchy] = menuData->selNo;
  topNo[nowHierarchy] = menuData->topNo;
  ProcessData->drwNo[nowHierarchy] = menuData->drwNo;
  updated = MenuUpdateSelectMenu(ProcessData);
  if (!updated)
    return updated;
  MenuUpdateLinkMover(ProcessData);
  return updated;
}

// 0x1c4e200
void itfMenuSetSelectID(dds3ProcessID_t *PID, s32 a_id) {
  Menu_t *ProcessData;
  MenuCB_tag *pHead;
  MenuCB_tag *pNext;
  s64 hierarchy;
  s32 parentId;
  s32 drwDefNum;
  MenuCB_tag *v13;
  s32 v14;
  s32 no;
  s32 drwMax;
  s32 v19;
  s32 v20;
  s32 selMax;
  s32 *topNo;
  s64 v23;
  u32 *v24;
  s32 v25;
  char *v26;
  s32 *v27;
  s32 v28;
  s32 v29;
  bool v30;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  pHead = ProcessData->pHead;
  if (pHead)
  {
    pNext = ProcessData->pHead;
    while (pNext->id != a_id)
    {
      pNext = pNext->pNext;
      if (!pNext)
        return;
    }
    if ((pNext->gflag & 1) != 0)
    {
      hierarchy = pNext->hierarchy;
      if ((hierarchy & 0x8000000000000000LL) == 0)
      {
        parentId = pNext->parentId;
        drwDefNum = 0;
        v13 = ProcessData->pHead;
        ProcessData->nowHierarchy = hierarchy;
        ProcessData->selMax = 0;
        do
        {
          v14 = v13->parentId;
          v13->no = -1;
          if (v14 == parentId)
          {
            v13->no = drwDefNum++;
            ProcessData->selMax = drwDefNum;
          }
          v13 = v13->pNext;
        }
        while (v13);
        if (drwDefNum >= ProcessData->drwDefNum)
          drwDefNum = ProcessData->drwDefNum;
        ProcessData->drwMax = drwDefNum;
        while (pHead->id != a_id)
        {
          pHead = pHead->pNext;
          if (!pHead)
          {
            goto LABEL_26;
          }
        }
        no = pHead->no;
        ProcessData->selNo[hierarchy] = no;
        drwMax = ProcessData->drwMax;
        v19 = drwMax - 1;
        v20 = no - (drwMax - 1);
        if (no <= drwMax - 1)
        {
          v23 = (s64)ProcessData->topNo + 4 * hierarchy;
          v25 = *(u32 *)(v23 + 32);
          v24 = (v23 + 32);
          if (v25 > no)
            *v24 = 0;
          goto LABEL_39;
        }
        selMax = ProcessData->selMax;
        topNo = ProcessData->topNo;
        if (selMax - 1 == no)
        {
          topNo[hierarchy] = selMax - drwMax;
        }
        else
        {
          v26 = (char *)topNo + 4 * hierarchy;
          v28 = *((u32 *)v26 + 8);
          v27 = (v26 + 32);
          v29 = v28 - v19;
          v30 = v28 + v19 >= no && v29 <= no;
          no = v19;
          if (v30)
            goto LABEL_39;
          *v27 = v20;
        }
        no = ProcessData->drwMax - 1;
LABEL_39:
        ProcessData->drwNo[hierarchy] = no;
LABEL_26:
        if (!MenuUpdateSelectMenu(ProcessData))
          return;
        MenuUpdateLinkMover(ProcessData);
      }
    }
  }
}

// 0x1c31ce0
void itfMenuSetInitSelectID(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  s32 klass_high;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass_high = HIDWORD(ProcessData[13].klass);
  LODWORD(ProcessData[11].monitor) = a_id;
  HIDWORD(ProcessData[13].klass) = klass_high | 0x8000;
}

// 0x1c4e760
void itfMenuResetSelect(dds3ProcessID_t *PID) {
  Menu_t *ProcessData;
  s32 *selNo;
  s32 *topNo;
  s32 *drwNo;
  s32 drwDefNum;
  MenuCB_tag *pHead;
  s32 parentId;
  bool updated;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  selNo = ProcessData->selNo;
  topNo = ProcessData->topNo;
  drwNo = ProcessData->drwNo;
  selNo[0] = 0;
  topNo[0] = 0;
  drwNo[0] = 0;
  selNo[1] = 0;
  topNo[1] = 0;
  drwNo[1] = 0;
  selNo[2] = 0;
  topNo[2] = 0;
  drwNo[2] = 0;
  selNo[3] = 0;
  drwDefNum = 0;
  topNo[3] = 0;
  pHead = ProcessData->pHead;
  drwNo[3] = 0;
  ProcessData->nowHierarchy = 0;
  ProcessData->ctrlType = 0;
  for (ProcessData->selMax = 0; pHead; pHead = pHead->pNext)
  {
    parentId = pHead->parentId;
    pHead->no = -1;
    if (parentId == -1)
    {
      pHead->no = drwDefNum++;
      ProcessData->selMax = drwDefNum;
    }
  }
  if (drwDefNum >= ProcessData->drwDefNum)
    drwDefNum = ProcessData->drwDefNum;
  ProcessData->drwMax = drwDefNum;
  updated = MenuUpdateSelectMenu(ProcessData);
  if (updated)
  {
    MenuUpdateLinkMover(ProcessData);
    return;
  }
  MenuCtrlSelect(ProcessData, 3, 0);
}

// 0x1c4e960
s32 itfMenuGetMenuNum(dds3ProcessID_t *PID) {
  s32 *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return ProcessData[24];
  return ProcessData[24];
}

// 0x1c4ea40
bool itfMenuChkSetMenu(dds3ProcessID_t *PID) {
  u8 *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return (ProcessData[212] >> 1) & 1;
  return (ProcessData[212] >> 1) & 1;
}

// 0x1c4eb20
static sprHandle_t *MenuLoadSprite(u8 *str) {
  return 0;
}

// 0x1c4eb30
bool itfMenuImgLinkSprite(dds3ProcessID_t *PID, s32 a_type, sprHandle_t *a_hSpr) {
  Il2CppObject *ProcessData;
  bool v9;
  s64 v10;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v9 = 0;
  if ((u32)a_type > 3 || !a_hSpr)
    return v9;
  v10 = *((u64 *)ProcessData[1].monitor + (u32)a_type + 4);
  if ((*(u16 *)(v10 + 60) & 2) == 0)
  {
    *(u64 *)(v10 + 16) = a_hSpr;
    return 1;
  }
  return 0;
}

// 0x1c46f10
bool itfMenuLinkSprite(dds3ProcessID_t *PID, sprHandle_t *a_hSpr) {
  return 1;
}

// 0x1c46f20
bool itfMenuSetSpriteData(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, s32 a_baseX, s32 a_baseY, s32 a_ofsX, s32 a_ofsY, s32 a_fontX, s32 a_fontY, u8 *a_strSprName, itfSprList_t *a_pList) {
  s16 v11;
  s16 v12;
  s16 v13;
  s16 v14;
  s16 v15;
  s16 v16;
  Il2CppObject *ProcessData;
  u16 *v21;
  u16 *v22;
  dds3ProcessID_t *id;

  id = PID;
  v11 = a_fontY;
  v12 = a_fontX;
  v13 = a_ofsY;
  v14 = a_ofsX;
  v15 = a_baseY;
  v16 = a_baseX;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u32)a_type <= 3)
  {
    v21 = *((u16 **)ProcessData[1].monitor + (u32)a_type + 4);
    if (a_strSprName && !*((u64 *)v21 + 2))
    {
      *((u64 *)v21 + 2) = 0;
      v21[30] |= 2u;
    }
    *((u64 *)v21 + 3) = a_pList;
    v22 = v21 + 12;
    v22[4] = v16;
    v22[5] = v15;
    v22[6] = v14;
    v22[7] = v13;
    v22[8] = v12;
    v22[9] = v11;
  }
  return (u32)a_type < 4;
}

// 0x1c4ec70
static bool _MenuSetImageColor(Menu_t *wk, ITFMENU_IMG_DAT a_type, u8 a_R, u8 a_G, u8 a_B, u8 a_A) {
  if ((u32)a_type <= 3)
    wk->imgDat[a_type]->color = (a_B << 16) | (a_A << 24) | (a_G << 8) | a_R;
  return (u32)a_type < 4;
}

// 0x1c470d0
bool itfMenuSetImageColor(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, u8 a_R, u8 a_G, u8 a_B, u8 a_A) {
  s32 v7;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  v7 = a_A;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if ((u32)a_type <= 3)
    *(u32 *)(*((u64 *)ProcessData[1].monitor + (u32)a_type + 4) + 44) = (a_B << 16)
                                                                                       | (v7 << 24)
                                                                                       | (a_G << 8)
                                                                                       | a_R;
  return (u32)a_type < 4;
}

// 0x1c4ecb0
u8 itfMenuImgGetAlpha(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u32)a_type > 3)
    return 0;
  else
    return *(u8 *)(*((u64 *)ProcessData[1].monitor + (u32)a_type + 4) + 48);
}

// 0x1c4edb0
f32 itfMenuImgGetRatio(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type) {
  Il2CppObject *ProcessData;
  s64 v7;
  s32 klass_high;
  f32 v9;
  s16 v11;
  f32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  bool v16;
  s32 v17;
  s32 v18;
  f32 v20;
  s16 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  f32 v29;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (a_type == 1)
  {
    v7 = *((u64 *)ProcessData[5].klass->_1.byval_arg.data + 2);
    if (!v7)
      return 0.0;
  }
  else
  {
    if (a_type)
      return 0.0;
    v7 = *((u64 *)ProcessData[4].monitor + 2);
    if (!v7)
      return 0.0;
  }
  klass_high = HIDWORD(ProcessData[13].klass);
  v9 = 1.0;
  if ((klass_high & 0x1000) != 0)
  {
    if ((klass_high & 0x40) != 0)
    {
      v21 = *(u16 *)(v7 + 30);
      if ((v21 & 2) == 0)
      {
        if ((v21 & 1) == 0)
          return 0.0;
        v22 = *(u32 *)(v7 + 36);
        if (v22 < 1)
          return 0.0;
        v23 = *(u32 *)(v7 + 32);
        v24 = *(char *)(*(u64 *)(*(u64 *)(*(u64 *)(v7 + 16) + 32) + 48) + 32);
        v16 = __OFSUB__(v23, v24);
        v25 = v23 - v24;
        if (v25 < 0 != v16)
          return 0.0;
        v26 = v22 - v24;
        if (v25 < 1 || v26 < 1)
          return 0.0;
        v9 = 0.0;
        v29 = (f32)v25 / (f32)v26;
        if (v29 >= 0.0)
        {
          if (v29 <= 1.0)
            return (f32)v25 / (f32)v26;
          else
            return 1.0;
        }
      }
    }
    else
    {
      v11 = *(u16 *)(v7 + 30);
      v12 = 1.0;
      if ((v11 & 2) == 0)
      {
        v12 = 0.0;
        if ((v11 & 1) != 0)
        {
          v13 = *(u32 *)(v7 + 36);
          if (v13 >= 1)
          {
            v14 = *(u32 *)(v7 + 32);
            v15 = *(char *)(*(u64 *)(*(u64 *)(*(u64 *)(v7 + 16) + 32) + 48) + 32);
            v16 = __OFSUB__(v14, v15);
            v17 = v14 - v15;
            if (v17 < 0 == v16)
            {
              v18 = v13 - v15;
              if (v17 >= 1 && v18 >= 1)
              {
                v20 = (f32)v17 / (f32)v18;
                if (v20 >= 0.0)
                {
                  v12 = 1.0;
                  if (v20 <= 1.0)
                    v12 = (f32)v17 / (f32)v18;
                }
              }
            }
          }
        }
      }
      return 1.0 - v12;
    }
  }
  return v9;
}

// 0x1c47210
void itfMenuSetSubABGR(dds3ProcessID_t *PID, u32 a_abgr) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  LODWORD(ProcessData[14].klass) = a_abgr;
}

// 0x1c472f0
bool itfMenuSetStringStyle(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, ITF_DM_STYLE a_style) {
  Il2CppObject *ProcessData;
  _BOOL4 v10;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v10 = (u32)a_type < 4 && (u32)a_style < 5;
  if (v10)
    *(u32 *)(*((u64 *)ProcessData[1].monitor + (u32)a_type + 4) + 52) = a_style;
  return v10;
}

// 0x1c4eff0
bool itfMenuSetStringSpace(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, s32 a_space) {
  char v4;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  v4 = a_space;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u32)a_type <= 3)
    *(u8 *)(*((u64 *)ProcessData[1].monitor + (u32)a_type + 4) + 56) = v4;
  return (u32)a_type < 4;
}

// 0x1c4f0f0
bool itfMenuSetStringWidth(dds3ProcessID_t *PID, ITFMENU_IMG_DAT a_type, s32 a_width) {
  s16 v4;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  v4 = a_width;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((u32)a_type <= 3)
    *(u16 *)(*((u64 *)ProcessData[1].monitor + (u32)a_type + 4) + 58) = v4;
  return (u32)a_type < 4;
}

// 0x1c4f1f0
bool itfMenuGetPanelParam(dds3ProcessID_t *PID, s32 a_id, s32 *a_px, s32 *a_py, s32 *a_pw, s32 *a_ph) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  s64 klass_high;
  s64 i;
  bool result;
  s64 v19;
  f64 v20;
  f64 v21;
  s64 v22;
  s32 v23;
  s64 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  while (LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return 0;
  }
  klass_high = HIDWORD(ProcessData[8].klass);
  if ((s32)klass_high < 1)
    return 0;
  for (i = &ProcessData[5].klass->_1.byval_arg; klass != *(Il2CppClass **)(*(u64 *)i + 24); i += 8)
  {
    if (!--klass_high)
      return 0;
  }
  v19 = *(u64 *)(*(u64 *)i + 16);
  v20 = 0.0;
  if (v19)
  {
    v21 = 0.0;
    if (*(s16 *)(v19 + 26) >= 1)
    {
      v22 = *(u64 *)(*(u64 *)(v19 + 16) + 8 * *(s16 *)(v19 + 24) + 32);
      v21 = *(f32 *)(v22 + 20);
      v20 = *(f32 *)(v22 + 16);
    }
  }
  else
  {
    v21 = 0.0;
  }
  v23 = v20;
  result = 1;
  v24 = *((u64 *)ProcessData[1].monitor + 5);
  v25 = *(s16 *)(v24 + 36);
  if (v20 == INFINITY)
    v23 = 0x80000000;
  *a_px = v23;
  v26 = v21;
  if (v21 == INFINITY)
    v26 = 0x80000000;
  *a_py = v26;
  v27 = *(s16 *)(v24 + 38);
  *a_pw = v25;
  *a_ph = v27;
  return result;
}

// 0x1c4f410
bool itfMenuSetFunc(dds3ProcessID_t *PID, s32 a_id, itfMenuFunc_t a_func) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  Il2CppClass **p_parent;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if ((a_id & 0x80000000) == 0)
  {
    if (!klass)
      return 0;
    while (LODWORD(klass->_1.name) != a_id)
    {
      klass = klass->_1.declaringType;
      if (!klass)
        return 0;
    }
    klass->_1.parent = a_func;
    return 1;
  }
  if (!klass)
    return 1;
  do
  {
    klass->_1.parent = a_func;
    p_parent = &klass->_1.parent;
    klass = *(p_parent - 1);
  }
  while (klass);
  return 1;
}

// 0x1c2f5a0
bool itfMenuSetDrawFunc(dds3ProcessID_t *PID, s32 a_id, itfMenuDrawFunc_t a_funcDraw, itfMenuTextFunc_t a_funcText) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  while (LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return 0;
  }
  klass->_1.generic_class = a_funcDraw;
  klass->_1.typeMetadataHandle = a_funcText;
  return 1;
}

// 0x1c4f570
bool itfMenuSetFont(dds3ProcessID_t *PID, s32 a_id, char *a_str, char *a_tag) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  while (LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return 0;
  }
  klass->_1.this_arg.data = a_str;
  *(u64 *)&klass->_1.this_arg.bits = a_tag;
  return 1;
}

// 0x1c46d10
void itfMenuSetDrawParam(dds3ProcessID_t *PID, s32 a_max, bool a_bFix) {
  u8 v5;
  Il2CppObject *ProcessData;
  s32 v9;
  s32 v10;
  dds3ProcessID_t *id;

  id = PID;
  v5 = a_max;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v9 = v5;
  if ((u32)v5 - 17 < 0xFFFFFFF0)
    v9 = 16;
  LODWORD(ProcessData[8].monitor) = v9;
  v10 = LODWORD(ProcessData[13].klass) | 0x400;
  if (!a_bFix)
    v10 = (s64)ProcessData[13].klass & 0xFBFF;
  LODWORD(ProcessData[13].klass) = v10;
}

// 0x1c4f6b0
bool itfMenuDelMenu(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  s32 klass_high;
  void *v8;
  void *klass;
  u64 *v10;
  s64 size;
  s32 *items;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass_high = HIDWORD(ProcessData[13].klass);
  if ((klass_high & 0x4000) == 0)
  {
    v8 = Allocate(System_Collections_Generic_List_int_);
    __ctor(v8);
    ProcessData[11].klass = v8;
    klass = ProcessData[11].klass;
    v10 = Method_System_Collections_Generic_List_int__Add__;
    size = klass->_size;
    ++klass->_version;
    items = klass->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(klass, a_id, *(const MethodInfo_2D8F530 **)(*(u64 *)(v10[4] + 192) + 112));
    }
    else
    {
      klass->_size = size + 1;
      items[size] = a_id;
    }
    HIDWORD(ProcessData[13].klass) |= 0x4000u;
  }
  return (klass_high & 0x4000) == 0;
}

// 0x1c4f870
bool itfMenuDelMenus(dds3ProcessID_t *PID, void *delID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((HIDWORD(ProcessData[13].klass) & 0x4000) != 0)
    return 0;
  ProcessData[11].klass = delID;
  v7 = ProcessData + 11;
  HIDWORD(v7[2].klass) |= 0x4000u;
  return 1;
}

// 0x1c4f980
void itfMenuSetMoveType(dds3ProcessID_t *PID, ITFMENU_MOVE_TYPE a_type) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  HIDWORD(ProcessData[11].monitor) = a_type;
}

// 0x1c4fa60
ITFMENU_CTRL_TYPE itfMenuGetCtrlType(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[5].monitor;
  if (monitor == 3)
    return HIDWORD(ProcessData[6].klass);
  return monitor == 2 && BYTE1(ProcessData[12].klass);
}

// 0x1c46c30
void itfMenuSetOt(dds3ProcessID_t *PID, DDS3_OT a_ot) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  LODWORD(ProcessData[7].monitor) = a_ot;
}

// 0x1c4fb80
bool itfMenuSetDecideSE(dds3ProcessID_t *PID, s32 a_id, s32 a_se) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if ((a_id & 0x80000000) == 0)
  {
    if (!klass)
      return 0;
    while (LODWORD(klass->_1.name) != a_id)
    {
      klass = klass->_1.declaringType;
      if (!klass)
        return 0;
    }
    HIDWORD(klass->_1.byval_arg.data) = a_se;
    return 1;
  }
  if (!klass)
    return 1;
  do
  {
    HIDWORD(klass->_1.byval_arg.data) = a_se;
    klass = klass->_1.declaringType;
  }
  while (klass);
  return 1;
}

// 0x1c4fcd0
bool itfMenuSetCancelSE(dds3ProcessID_t *PID, s32 a_id, s32 a_se) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if ((a_id & 0x80000000) == 0)
  {
    if (!klass)
      return 0;
    while (LODWORD(klass->_1.name) != a_id)
    {
      klass = klass->_1.declaringType;
      if (!klass)
        return 0;
    }
    klass->_1.byval_arg.bits = a_se;
    return 1;
  }
  if (!klass)
    return 1;
  do
  {
    klass->_1.byval_arg.bits = a_se;
    klass = klass->_1.declaringType;
  }
  while (klass);
  return 1;
}

// 0x1c4fe20
void itfMenuSetAnimDelMenu(dds3ProcessID_t *PID, s32 a_id, s32 a_cnt) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  s64 klass_high;
  s64 i;
  int8x8_t *v12;
  u64 v13;
  float64x2_t v14;
  u64 v15;
  u64 v16;
  s64 v17;
  s32 v18;
  s32 v19;
  f32 v20;
  f32 v21;
  s64 v22;
  s16 v23;
  s64 v24;
  f32 v25;
  s64 v26;
  s64 v27;
  s16 v28;
  s32 v29;
  s32 v30;
  s16 v31;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (klass)
  {
    while (LODWORD(klass->_1.name) != a_id)
    {
      klass = klass->_1.declaringType;
      if (!klass)
        return;
    }
    klass_high = HIDWORD(ProcessData[8].klass);
    if ((s32)klass_high >= 1)
    {
      for (i = &ProcessData[5].klass->_1.byval_arg; ; i += 8)
      {
        v12 = *(int8x8_t **)i;
        if (klass == *(Il2CppClass **)(*(u64 *)i + 24))
          break;
        if (!--klass_high)
          return;
      }
      v13 = v12[2].n64_u64[0];
      v14 = 0u;
      if (v13 && *(s16 *)(v13 + 26) >= 1)
        v14 = vcvtq_f64_f32(*(float32x2_t *)(*(u64 *)(*(u64 *)(v13 + 16) + 8 * *(s16 *)(v13 + 24) + 32) + 16));
      v15 = v12[2].n64_u64[0];
      v12[4].n64_u64[0] = vbsl_s8(vmovn_s64(vceqq_f64(v14, vdupq_n_s64(0x7FF0000000000000uLL))), (int8x8_t)0x8000000080000000LL, vmovn_s64(vcvtq_s64_f64(v14))).n64_u64[0];
      if (v15)
      {
        *(u64 *)(v15 + 24) = 0;
        *(u64 *)(v15 + 32) = 0;
        v16 = v12[2].n64_u64[0];
        if (v16)
        {
          v17 = *(s16 *)(v16 + 26);
          if (v17 <= 3)
          {
            v18 = v12[4].n64_i32[0];
            v19 = v18 + (a_cnt >> 1);
            v20 = v18;
            v21 = v12[4].n64_i32[1];
            v22 = *(u64 *)(v16 + 16) + 8 * v17;
            if (a_cnt << 16 <= 0)
              v23 = 1;
            else
              v23 = a_cnt;
            v24 = *(u64 *)(v22 + 32);
            v25 = v23;
            v26 = *(u64 *)(v24 + 48);
            *(u16 *)(v24 + 56) = v23;
            *(u32 *)(v24 + 40) = 0;
            *(f32 *)(v24 + 16) = v20;
            *(f32 *)(v24 + 20) = v21;
            *(f32 *)(v24 + 24) = (f32)v19;
            *(f32 *)(v24 + 28) = v21;
            *(f32 *)(v24 + 32) = (f32)((f32)v19 - v20) / v25;
            *(f32 *)(v24 + 36) = (f32)(v21 - v21) / v25;
            *(u8 *)(v26 + 32) = 0;
            *(u8 *)(*(u64 *)(v24 + 48) + 33) = 0;
            v27 = *(u64 *)(v24 + 48);
            if (*(char *)(v27 + 32) < 0)
            {
              *(u8 *)(v27 + 32) = 0;
              v27 = *(u64 *)(v24 + 48);
            }
            if (*(char *)(v27 + 33) < 0)
            {
              *(u8 *)(v27 + 33) = 0;
              v27 = *(u64 *)(v24 + 48);
            }
            v28 = *(u16 *)(v16 + 26);
            *(u16 *)(v16 + 24) = 0;
            *(u16 *)(v16 + 28) = 0;
            v29 = *(u32 *)(v16 + 36);
            v30 = *(s16 *)(v24 + 56);
            *(u32 *)(v16 + 32) = 0;
            *(u16 *)(v16 + 26) = v28 + 1;
            v31 = *(u16 *)(v16 + 30);
            *(u32 *)(v16 + 36) = v29 + v30 + *(char *)(v27 + 32) + *(char *)(v27 + 33);
            *(u16 *)(v16 + 30) = v31 & 0xFFFC | 1;
          }
        }
      }
      LODWORD(klass->_1.byval_arg.data) = (s64)klass->_1.byval_arg.data & 0xFF7 | 0xB008;
    }
  }
}

// 0x1c500f0
void itfMenuSetAnimBakMenu(dds3ProcessID_t *PID, s32 a_id, s32 a_cnt) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  s64 klass_high;
  s64 i;
  int32x2_t *v12;
  u64 v13;
  float64x2_t v14;
  u64 v15;
  s64 v16;
  int64x2_t v17;
  int32x2_t v18;
  s64 v19;
  float32x2_t v20;
  s16 v21;
  float32x2_t *v22;
  int8x8_t v23;
  s32 v24;
  u64 v25;
  float32x2_t v26;
  u64 v27;
  s16 v28;
  s32 v29;
  s32 v30;
  s16 v31;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (klass)
  {
    while (LODWORD(klass->_1.name) != a_id)
    {
      klass = klass->_1.declaringType;
      if (!klass)
        return;
    }
    klass_high = HIDWORD(ProcessData[8].klass);
    if ((s32)klass_high >= 1)
    {
      for (i = &ProcessData[5].klass->_1.byval_arg; ; i += 8)
      {
        v12 = *(int32x2_t **)i;
        if (klass == *(Il2CppClass **)(*(u64 *)i + 24))
          break;
        if (!--klass_high)
          return;
      }
      v13 = v12[2].n64_u64[0];
      v14 = 0u;
      if (v13 && *(s16 *)(v13 + 26) >= 1)
        v14 = vcvtq_f64_f32(*(float32x2_t *)(*(u64 *)(*(u64 *)(v13 + 16) + 8 * *(s16 *)(v13 + 24) + 32) + 16));
      v15 = v12[2].n64_u64[0];
      if (v15)
      {
        *(u64 *)(v15 + 24) = 0;
        *(u64 *)(v15 + 32) = 0;
        v15 = v12[2].n64_u64[0];
      }
      if (v15)
      {
        v16 = *(s16 *)(v15 + 26);
        if (v16 <= 3)
        {
          v17 = vdupq_n_s64(0x7FF0000000000000uLL);
          v18.n64_u64[0] = vmovn_s64(vcvtq_s64_f64(v14)).n64_u64[0];
          v19 = *(u64 *)(v15 + 16) + 8 * v16;
          v20.n64_u64[0] = vcvt_f32_s32(v12[4]).n64_u64[0];
          if (a_cnt << 16 <= 0)
            v21 = 1;
          else
            v21 = a_cnt;
          v22 = *(float32x2_t **)(v19 + 32);
          v23.n64_u64[0] = vcvt_f32_s32(v18).n64_u64[0];
          v24 = v21;
          v22[7].n64_u16[0] = v21;
          v25 = v22[6].n64_u64[0];
          v22[5].n64_u32[0] = 0;
          v22[3].n64_u64[0] = v20.n64_u64[0];
          v26.n64_u64[0] = vbsl_s8(vmovn_s64(vceqq_f64(v14, v17)), (int8x8_t)0xCF000000CF000000LL, v23).n64_u64[0];
          v23.n64_f32[0] = (f32)v24;
          v22[2].n64_u64[0] = v26.n64_u64[0];
          v22[4].n64_u64[0] = vdiv_f32(vsub_f32(v20, v26), vdup_lane_s32(v23, 0)).n64_u64[0];
          *(u8 *)(v25 + 32) = 0;
          *(u8 *)(v22[6].n64_u64[0] + 33) = 0;
          v27 = v22[6].n64_u64[0];
          if (*(char *)(v27 + 32) < 0)
          {
            *(u8 *)(v27 + 32) = 0;
            v27 = v22[6].n64_u64[0];
          }
          if (*(char *)(v27 + 33) < 0)
          {
            *(u8 *)(v27 + 33) = 0;
            v27 = v22[6].n64_u64[0];
          }
          v28 = *(u16 *)(v15 + 26);
          *(u16 *)(v15 + 24) = 0;
          *(u16 *)(v15 + 28) = 0;
          v29 = *(u32 *)(v15 + 36);
          v30 = v22[7].n64_i16[0];
          *(u32 *)(v15 + 32) = 0;
          *(u16 *)(v15 + 26) = v28 + 1;
          v31 = *(u16 *)(v15 + 30);
          *(u32 *)(v15 + 36) = v29 + v30 + *(char *)(v27 + 32) + *(char *)(v27 + 33);
          *(u16 *)(v15 + 30) = v31 & 0xFFFC | 1;
        }
      }
      LODWORD(klass->_1.byval_arg.data) = (s64)klass->_1.byval_arg.data & 0xFF7 | 0xB008;
    }
  }
}

// 0x1c503b0
void itfMenuSetAnimFlashMenu(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  s64 klass_high;
  s64 i;
  s32 data;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[2].klass;
  if (klass)
  {
    while (LODWORD(klass->_1.name) != a_id)
    {
      klass = klass->_1.declaringType;
      if (!klass)
        return;
    }
    klass_high = HIDWORD(ProcessData[8].klass);
    if ((s32)klass_high >= 1)
    {
      for (i = &ProcessData[5].klass->_1.byval_arg; klass != *(Il2CppClass **)(*(u64 *)i + 24); i += 8)
      {
        if (!--klass_high)
          return;
      }
      data = klass->_1.byval_arg.data;
      *(u32 *)(*(u64 *)i + 40) = 0;
      LODWORD(klass->_1.byval_arg.data) = data | 0x10;
    }
  }
}

// 0x1c50510
s32 itfMenuGetFlashCount(dds3ProcessID_t *PID, s32 a_id) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  s32 result;
  s64 klass_high;
  s64 i;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass = ProcessData[2].klass;
  if (!klass)
    return -1;
  result = -1;
  while (LODWORD(klass->_1.name) != a_id)
  {
    klass = klass->_1.declaringType;
    if (!klass)
      return result;
  }
  klass_high = HIDWORD(ProcessData[8].klass);
  if ((s32)klass_high < 1)
    return -1;
  result = -1;
  for (i = &ProcessData[5].klass->_1.byval_arg; klass != *(Il2CppClass **)(*(u64 *)i + 24); i += 8)
  {
    if (!--klass_high)
      return result;
  }
  if (((s64)klass->_1.byval_arg.data & 0x10) != 0)
    return *(u32 *)(*(u64 *)i + 40);
  else
    return -1;
}

// 0x1c50680
s32 itfMenuGetDecideKey(void) {
  return g_MenuDecideKey;
}

// 0x1c50700
void itfMenuSetDecideKey(s32 DecideKey) {
  g_MenuDecideKey = DecideKey;
  return;
}

// 0x1c50790
static bool MenuDelMenuSub(Menu_t *wk, s32 a_id) {
  MenuCB_tag *pHead;
  u32 lflag;
  MenuCB_tag *p_select;
  s32 selMax;
  s32 *topNo;
  s64 nowHierarchy;
  char *v19;
  u32 *v20;
  s32 v21;
  s32 v22;
  char *v23;
  s32 v24;
  s32 v25;
  u32 v26;
  char *v27;
  s32 v28;
  bool updated;
  s32 v36;
  MenuCB_tag *cb;

  if ((a_id & 0x80000000) == 0)
  {
    pHead = wk->pHead;
    if (!pHead)
    {
LABEL_7:
      wk->lflag &= 0xBFFFu;
      return 0;
    }
    while (pHead->id != a_id)
    {
      pHead = pHead->pNext;
      if (!pHead)
        goto LABEL_7;
    }
    cb = pHead;
    p_select = &wk->select;
    if (wk->select == pHead)
    {
      p_select = 0;
LABEL_16:
      MenuDeleteMenu(wk, cb);
      goto LABEL_17;
    }
    else
    {
      goto LABEL_16;
    }
    MenuDeleteMenu(wk, cb);
LABEL_17:
    MenuMakeLink(wk);
    if (wk->select)
      goto LABEL_33;
    selMax = wk->selMax;
    if (selMax <= 0)
    {
      v25 = (u8)wk->nowHierarchy-- - 1;
      if (v25 << 24 >= 0x1000000)
      {
        wk->ctrlType = 3;
        v26 = wk->lflag & 0xDFFF;
      }
      else
      {
        wk->ctrlType = 5;
        v26 = wk->lflag | 0x2000;
      }
      wk->lflag = v26;
      v36 = wk->dispType[1];
      MenuSetMoverDisappear(wk, v36);
      wk->step = 3;
      goto LABEL_46;
    }
    topNo = wk->topNo;
    nowHierarchy = wk->nowHierarchy;
    v19 = (char *)topNo + 4 * nowHierarchy;
    v22 = *((u32 *)v19 + 8);
    v20 = v19 + 32;
    v21 = v22;
    if (v22)
    {
      if (v21 > selMax - wk->drwMax)
      {
        --wk->selNo[nowHierarchy];
        v23 = (char *)topNo + 4 * nowHierarchy;
        v24 = *((u32 *)v23 + 8) - 1;
        *((u32 *)v23 + 8) = v24;
        if (v24 < 0)
        {
          *v20 = 0;
LABEL_32:
          --wk->drwNo[nowHierarchy];
        }
      }
    }
    else
    {
      v27 = (char *)wk->selNo + 4 * nowHierarchy;
      v28 = *((u32 *)v27 + 8);
      if (v28 >= 1 && v28 == selMax)
      {
        *((u32 *)v27 + 8) = selMax - 1;
        goto LABEL_32;
      }
    }
LABEL_33:
    updated = MenuUpdateSelectMenu(wk);
    if (updated)
    {
      MenuUpdateLinkMover(wk);
LABEL_46:
      wk->lflag &= 0xBFFFu;
      return 1;
    }
    MenuCtrlSelect(wk, 1, 0);
    goto LABEL_46;
  }
  while (wk->pTail)
  {
    MenuDeleteMenu(wk, &wk->pTail);
  }
  lflag = wk->lflag;
  wk->step = 1;
  wk->lflag = lflag & 0xBDC7;
  return 1;
}

// 0x1c50ac0
static void MenuInit(Menu_t *wk) {
  s8 *dispType;
  s32 *drwNo;
  s32 *selNo;
  s32 *topNo;
  MenuImgDat_t *v7;
  MenuImgDat_t *v8;
  MenuImgDat_t *imgDat;
  MenuImgDat_t *v10;
  MenuImgDat_t *v11;
  MenuImgDat_t *v12;
  MenuImgDat_t *v13;
  MenuImgDat_t *v14;
  MenuImgDat_t *v15;
  MenuImgDat_t *v16;
  MenuImgDat_t *v17;
  MenuImgDat_t *v18;
  MenuImgDat_t *v19;
  MenuImgDat_t *v20;
  MenuImgDat_t *v21;

  wk->pHead = 0;
  wk->pTail = 0;
  wk->select = 0;
  dispType = wk->dispType;
  wk->nowHierarchy = 0;
  wk->nMenuSet = 0;
  wk->drwDefMax = 9;
  *(u64 *)&wk->drwMax = 0x900000009LL;
  dispType[0] = 0;
  wk->dispType[1] = 0;
  *(u64 *)&wk->gflag = 0;
  *(u64 *)&wk->frame = 0;
  wk->gflag = 31;
  drwNo = wk->drwNo;
  selNo = wk->selNo;
  topNo = wk->topNo;
  *(u64 *)&wk->scrollType = 0x6D00000000LL;
  selNo[0] = 0;
  topNo[0] = 0;
  drwNo[0] = 0;
  selNo[1] = 0;
  topNo[1] = 0;
  drwNo[1] = 0;
  selNo[2] = 0;
  topNo[2] = 0;
  drwNo[2] = 0;
  selNo[3] = 0;
  v7 = wk->imgDat[0];
  topNo[3] = 0;
  drwNo[3] = 0;
  v7->hSpr = 0;
  v8 = wk->imgDat[0];
  v8->pList = 0;
  imgDat = wk->imgDat;
  v10 = imgDat[0];
  *(u32 *)&v10->strWidth = 0;
  *(u64 *)&v10->fx = 0x8080808000020004LL;
  v10->strStyle = 0;
  v10->strSpace = 0;
  *(u64 *)&v10->sx = 0x1A008000200020LL;
  v11 = imgDat[1];
  v11->hSpr = 0;
  v12 = wk->imgDat[1];
  v12->pList = 0;
  v13 = wk->imgDat;
  v14 = v13[1];
  *(u32 *)&v14->strWidth = 0;
  *(u64 *)&v14->fx = 0x8080808000020004LL;
  v14->strStyle = 0;
  v14->strSpace = 0;
  *(u64 *)&v14->sx = 0x1A0080003A0020LL;
  v15 = v13[2];
  v15->hSpr = 0;
  v16 = wk->imgDat[2];
  v16->pList = 0;
  v17 = wk->imgDat;
  v18 = v17[2];
  *(u32 *)&v18->strWidth = 0;
  *(u64 *)&v18->fx = 0x8080808000020004LL;
  v18->strStyle = 0;
  v18->strSpace = 0;
  *(u64 *)&v18->sx = 0x1A0080003A0020LL;
  v19 = v17[3];
  v19->hSpr = 0;
  v20 = wk->imgDat[3];
  v20->pList = 0;
  v21 = wk->imgDat[3];
  *(u32 *)&v21->strWidth = 0;
  *(u64 *)&v21->fx = 0x8080808000010001LL;
  v21->strStyle = 0;
  wk->unityCtrl = 0;
  v21->strSpace = 0;
  *(u64 *)&v21->sx = 0xEA0005003A00A2LL;
  wk->moveFunc = 0;
}

// 0x1c50ce0
static bool MenuCtrlSelectSub(Menu_t *wk, s32 a_keyType) {
  u32 v3;
  s64 v4;
  char *v5;
  char *v6;
  s32 drwMax;
  char *v8;
  s32 *v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 *v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 *v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  bool v24;
  s32 v26;

  v3 = wk->lflag & 0xFE7F;
  wk->lflag = v3;
  v4 = 4 * wk->nowHierarchy;
  v5 = (char *)wk->drwNo + v4;
  v6 = (char *)wk->topNo + v4;
  drwMax = wk->drwMax;
  v8 = (char *)wk->selNo + v4;
  v11 = *((u32 *)v8 + 8);
  v9 = (v8 + 32);
  v10 = v11;
  v12 = wk->selMax - 1;
  v15 = *((u32 *)v5 + 8);
  v13 = (v5 + 32);
  v14 = v15;
  v16 = drwMax - 1;
  v19 = *((u32 *)v6 + 8);
  v17 = (v6 + 32);
  v18 = v19;
  switch (a_keyType)
  {
    case 1:
      v20 = v10 - 1;
      if (v10 - 1 >= 0)
      {
        v21 = v14 - 1;
        v22 = v18 != 0;
        wk->lflag = v3 | 0x80;
        if (v14 - 1 >= v22)
          goto LABEL_20;
        --v18;
        goto LABEL_19;
      }
      wk->lflag = v3 | 0x80;
      if (v12 <= v16)
        goto LABEL_24;
      v18 = v12 - v16;
      goto LABEL_23;
    case 2:
      v12 = v10 - 1;
      if (v10 - 1 < 0)
        return 0;
      v16 = v14 - 1;
      v23 = v18 != 0;
      wk->lflag = v3 | 0x80;
      if (v14 - 1 >= v23)
        goto LABEL_24;
      --v18;
      v16 = v23;
      goto LABEL_23;
    case 3:
      v20 = v10 + 1;
      if (v10 + 1 <= v12)
        goto LABEL_14;
      v16 = 0;
      v12 = 0;
      v24 = v18 < 1;
      wk->lflag = v3 | 0x80;
      v18 = 0;
      if (!v24)
        goto LABEL_23;
LABEL_24:
      *v9 = v12;
      *v17 = v18;
      *v13 = v16;
      return 1;
    case 4:
      v20 = v10 + 1;
      if (v10 + 1 > v12)
        return 0;
LABEL_14:
      v26 = drwMax - 2;
      if (v18 == v12 - v16)
        v22 = v16;
      else
        v22 = v26;
      v21 = v14 + 1;
      wk->lflag = v3 | 0x80;
      if (v14 + 1 <= v22)
      {
LABEL_20:
        *v9 = v20;
        *v17 = v18;
        *v13 = v21;
        return 1;
      }
      else
      {
        ++v18;
LABEL_19:
        v16 = v22;
        v12 = v20;
LABEL_23:
        wk->lflag = v3 | 0x180;
        *v9 = v12;
        *v17 = v18;
        *v13 = v16;
        return 1;
      }
    default:
      return 0;
  }
}

// 0x1c4a560
static bool MenuCtrlSelectSubHD(Menu_t *wk, s32 a_keyType) {
  s32 *selNo;
  s32 *topNo;
  u32 lflag;
  s64 nowHierarchy;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 drwMax;
  s32 selMax;
  s32 v13;
  s32 v14;
  bool v15;
  s32 v16;
  itfMenuMoveFunc moveFunc;
  u64 v19;
  char *v20;
  s32 *drwNo;

  selNo = wk->selNo;
  topNo = wk->topNo;
  lflag = wk->lflag & 0xFE7F;
  nowHierarchy = wk->nowHierarchy;
  wk->lflag = lflag;
  nowHierarchy *= 4;
  v8 = *(s32 *)((char *)selNo + nowHierarchy);
  v9 = *(s32 *)((char *)wk->drwNo + nowHierarchy);
  v10 = *(s32 *)((char *)topNo + nowHierarchy);
  selMax = wk->selMax;
  drwMax = wk->drwMax;
  switch (a_keyType)
  {
    case 1:
    case 2:
      if (--v8 < 0)
      {
        if (a_keyType != 2)
        {
          v8 = selMax - 1;
          wk->lflag = lflag | 0x80;
          v15 = __OFSUB__(selMax, drwMax);
          v16 = selMax - drwMax;
          if (!((v16 < 0) ^ v15 | (v16 == 0)))
          {
            v10 = v16;
            goto LABEL_30;
          }
          LOWORD(lflag) = lflag | 0x80;
          goto LABEL_31;
        }
        v8 = 0;
      }
      else
      {
        wk->lflag = lflag | 0x80;
        if (v8 < v10)
        {
          --v10;
          goto LABEL_29;
        }
        LOWORD(lflag) = lflag | 0x80;
      }
      break;
    case 3:
    case 4:
      ++v8;
      v13 = selMax - 1;
      if (v8 <= v13)
      {
        wk->lflag = lflag | 0x80;
        if (v8 - v10 >= drwMax)
        {
          ++v10;
          goto LABEL_29;
        }
        LOWORD(lflag) = lflag | 0x80;
      }
      else
      {
        if (a_keyType != 4)
        {
          v10 = 0;
          v8 = 0;
          goto LABEL_29;
        }
        v8 = v13;
      }
      break;
    case 5:
      if (selMax != drwMax)
      {
        v8 -= drwMax;
        if (v8 < 0 || (v10 -= drwMax, v10 <= 0))
        {
          v10 = 0;
          drwMax = 0;
          v8 = 0;
          goto LABEL_30;
        }
        goto LABEL_29;
      }
      break;
    case 6:
      v14 = selMax - drwMax;
      if (selMax != drwMax)
      {
        v10 += drwMax;
        if (v10 < selMax && v10 <= v14)
        {
          v8 += drwMax;
LABEL_29:
          drwMax = v9;
        }
        else
        {
          v8 = selMax - 1;
          --drwMax;
          v10 = v14;
        }
LABEL_30:
        lflag |= 0x180u;
        wk->lflag = lflag;
LABEL_31:
        v9 = drwMax;
      }
      break;
    default:
      break;
  }
  moveFunc = wk->moveFunc;
  if (moveFunc)
  {
    if ((moveFunc->invoke_impl)(moveFunc->method_code, wk) == 1)
      return 0;
    lflag = wk->lflag;
  }
  if ((lflag & 0x180) != 0)
  {
    v19 = wk->nowHierarchy;
    v20 = (char *)wk->topNo + v19 * 4;
    wk->selNo[v19] = v8;
    drwNo = wk->drwNo;
    *((u32 *)v20 + 8) = v10;
    drwNo[v19] = v9;
    return 1;
  }
  return 0;
}

// 0x1c4a7b0
static bool MenuChkCtrlSelect(Menu_t *wk, bool a_bUpdate) {
  if ((byte_575754A & 1) == 0)
  {
    if (a_bUpdate)
      goto LABEL_3;
    return 0;
  }
  if (!a_bUpdate)
    return 0;
LABEL_3:
  return !MenuUpdateSelectMenu(wk);
}

// 0x1c50e70
static void MenuPadCtrlSelect(Menu_t *wk) {
  s32 v4;
  Menu_t *v6;
  s32 v7;

  if ((wk->gflag & 0x200) == 0)
  {
    if (CHECK_TRIG(4101, 1))
    {
      v4 = 3;
    }
    else if (CHECK_REP(4101, 1))
    {
      v4 = 4;
    }
    else
    {
      v4 = 1;
      if (CHECK_TRIG(4100, 1))
      {
        v6 = wk;
        v7 = v4;
        goto LABEL_14;
      }
      else if (CHECK_REP(4100, 1))
      {
        v4 = 2;
      }
      else if (CHECK_REP(43526, 1))
      {
        v4 = 5;
      }
      else
      {
        if (CHECK_REP(43527, 1))
          v4 = 6;
        else
          v4 = 0;
      }
    }
    v6 = wk;
    v7 = v4;
LABEL_14:
    MenuCtrlSelect(v6, v7, 1);
  }
}

// 0x1c51010
static bool MenuMoveNextHierarchy(Menu_t *wk, bool extra) {
  MenuCB_tag *select;
  itfMenuFunc_t func;
  s32 v7;
  u32 v8;
  s32 v9;

  select = wk->select;
  func = select->func;
  if ((select->lflag & 2) != 0)
  {
    if (func)
    {
      (func->invoke_impl)(func->method_code, func->method);
      select = wk->select;
    }
    v7 = 2;
  }
  else
  {
    if (!func)
      return 0;
    v7 = 4;
  }
  wk->ctrlType = v7;
  if ((select->gflag & 0x40) != 0)
    v8 = wk->lflag & 0xDFFF;
  else
    v8 = wk->lflag | 0x2000;
  wk->lflag = v8;
  if (!extra)
  {
    v9 = wk->dispType[1];
    MenuSetMoverDisappear(wk, v9);
  }
  wk->step = 3;
  return 1;
}

// 0x1c51110
static void MenuMoveEnd(Menu_t *wk) {
  u32 gflag;
  s32 v6;

  gflag = wk->gflag;
  if ((gflag & 0x20) != 0)
  {
    wk->gflag = gflag & 0xFFF7;
    return;
  }
  wk->ctrlType = 5;
  wk->lflag |= 0x2000u;
  v6 = wk->dispType[1];
  MenuSetMoverDisappear(wk, v6);
  wk->step = 3;
}

// 0x1c511c0
static bool MenuMoveHierarchy(Menu_t *wk, ITFMENU_MOVE_TYPE a_type, bool extra) {
  u32 lflag;
  s32 v8;
  u32 gflag;

  if (a_type != 2)
  {
    if (a_type == 1)
    {
      if (wk->nowHierarchy >= 1)
      {
        lflag = wk->lflag;
        wk->ctrlType = 3;
        wk->lflag = lflag & 0xDFFF;
        v8 = wk->dispType[1];
LABEL_8:
        MenuSetMoverDisappear(wk, v8);
        wk->step = 3;
        return 1;
      }
      gflag = wk->gflag;
      if ((gflag & 0x20) == 0)
        goto LABEL_17;
LABEL_22:
      wk->gflag = gflag & 0xFFF7;
      return 1;
      if ((gflag & 0x20) == 0)
      {
LABEL_17:
        wk->ctrlType = 5;
        wk->lflag |= 0x2000u;
        v8 = wk->dispType[1];
        goto LABEL_8;
      }
      goto LABEL_22;
    }
    return 0;
  }
  if ((wk->select->gflag & 6) == 0)
    return 0;
  return MenuMoveNextHierarchy(wk, extra);
}

// 0x1c513b0
static void MenuPlayDecideSE(MenuCB_tag *cb) {
  s32 decideSE;

  decideSE = cb->decideSE;
  if (decideSE >= -1)
    SE(decideSE & ~(decideSE >> 31));
}

// 0x1c513d0
static void MenuPlayCancelSE(MenuCB_tag *cb) {
  s32 cancelSE;
  s32 v3;

  cancelSE = cb->cancelSE;
  if (cancelSE >= -1)
  {
    if (cancelSE == -1)
      v3 = 1;
    else
      v3 = cb->cancelSE;
    SE(v3);
  }
}

// 0x1c513f0
static dds3ProcessFunc_t MenuProcess(dds3ProcessID_t *PID) {
  Menu_t *ProcessData;
  s32 *v5;
  s32 *v8;
  s32 step;
  void *delIdList;
  s32 v11;
  s32 Item;
  u32 v14;
  s32 lflag;
  s32 *selNo;
  u32 v19;
  dds3ProcessID_t *v20;
  s32 initSelectID;
  s32 v22;
  s32 v25;
  dds3ProcessFunc_t v27;
  bool updated;
  u32 gflag;
  s8 v34;
  s32 moveType;
  u32 v38;
  s32 v39;
  u32 v40;
  s32 v41;
  s32 v42;
  s32 count;
  MenuCB_tag *v46;
  itfMenuFunc_t v47;
  s32 v48;
  void *v49;
  s32 v50;
  s32 v52;
  s32 v53;
  u32 v56;
  u32 v57;
  s32 v59;
  s32 v60;
  bool v61;
  s32 v62;
  bool v63;
  s32 v65;
  s32 v66;
  itfMenuFunc_t func;
  _BOOL4 v69;
  s32 v71;
  s32 v73;
  u32 v74;
  s32 v75;
  s32 *v76;
  s32 v77;
  s32 *v78;
  s32 v79;
  bool v80;
  bool v81;
  bool v82;
  u32 v83;
  s32 cancelSE;
  bool v89;
  u32 v90;
  MenuCB_tag *select;
  MenuCB_tag *v93;
  u32 v94;
  s32 decideSE;
  itfMenuFunc_t v97;
  s32 v98;
  itfMenuFunc_t v99;
  s8 v100;
  s32 v101;
  s32 v102;
  MenuCB_tag *v103;
  s32 v104;
  s32 v105;
  MenuCB_tag *v106;
  u32 v110;
  MenuCB_tag *v111;
  s32 v112;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = NewSpecific(s32, 4u);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__9A4ABFBF7B0EB1BA0C3382BCB7C99C72D50EA025958448EAD64A754AADD599B9, 0);
  v8 = NewSpecific(s32, 3u);
  if ((ProcessData->lflag & 0x4000) != 0)
  {
    step = ProcessData->step;
    if ((u32)(step - 2) >= 5)
    {
      ProcessData->lflag &= 0xBFFFu;
    }
    else if (step != 2)
    {
      delIdList = ProcessData->delIdList;
      if (delIdList)
      {
        if (delIdList->_size >= 1)
        {
          v11 = 0;
          do
          {
            Item = _get_Item(delIdList, v11);
            MenuDelMenuSub(ProcessData, Item);
            delIdList = ProcessData->delIdList;
            ++v11;
          }
          while (v11 < delIdList->_size);
        }
        ProcessData->delIdList = 0;
        v14 = ProcessData->step;
        if (v14 > 9)
          return 0;
        goto LABEL_20;
      }
    }
  }
  v14 = ProcessData->step;
LABEL_20:
  switch (v14)
  {
    case 0u:
    case 1u:
      lflag = ProcessData->lflag;
      if ((lflag & 8) != 0)
      {
        MenuMakeLink(ProcessData);
        selNo = ProcessData->selNo;
        ProcessData->nowHierarchy = 0;
        selNo[0] = 0;
        if (!MenuUpdateSelectMenu(ProcessData))
        {
          MenuCtrlSelect(ProcessData, 3, 0);
        }
        v19 = ProcessData->lflag;
        if ((v19 & 0x8000) != 0)
        {
          v20 = id;
          initSelectID = ProcessData->initSelectID;
          itfMenuSetSelectID(v20, initSelectID);
          LOWORD(v19) = ProcessData->lflag & 0x7FFF;
        }
        lflag = v19 & 0xFFF7;
        ProcessData->lflag = lflag;
      }
      if ((~lflag & 0x30) != 0)
        return 0;
      ProcessData->bEnableCtrl = 0;
      ProcessData->lflag = lflag & 0xFFFD;
      ProcessData->step = 2;
      v22 = ProcessData->dispType[0];
      MenuSetMoverAppear(ProcessData, v22);
      ProcessData->lflag |= 0x2E00u;
      if (!Story11Select)
      {
        if (!QuestDevilSelect)
          return 0;
      }
      v25 = 8;
      goto LABEL_134;
    case 2u:
      v27 = 0;
      if (evtBitCheck(675))
        return v27;
      updated = MenuUpdateMover(ProcessData);
      gflag = ProcessData->gflag;
      if (updated && (gflag & 0x4000) == 0)
      {
        v27 = 0;
        ProcessData->bEnableCtrl = 0;
        return v27;
      }
      ProcessData->bEnableCtrl = 1;
      if ((gflag & 0x80) != 0)
      {
        ProcessData->gflag = gflag & 0xFF7F;
        MenuMoveEnd(ProcessData);
        if (!QuestDevilExtra)
          return 0;
        v27 = 0;
        *(u16 *)&QuestDevilExtra = 0;
        QuestDevilCancel = 0;
        QuestDevilNumber = -1;
      }
      else
      {
        if ((ProcessData->lflag & 0x4000) != 0)
        {
          v49 = ProcessData->delIdList;
          ProcessData->lflag &= 0xBFFFu;
          if (v49)
          {
            if (v49->_size >= 1)
            {
              v50 = 0;
              do
              {
                v52 = _get_Item(v49, v50);
                MenuDelMenuSub(ProcessData, v52);
                v49 = ProcessData->delIdList;
                ++v50;
              }
              while (v50 < v49->_size);
            }
            ProcessData->delIdList = 0;
            gflag = ProcessData->gflag;
          }
        }
        if ((gflag & 0x800) != 0)
        {
          if ((ProcessData->select->gflag & 0x40) != 0)
            v65 = ProcessData->lflag & 0xDFFF;
          else
            v65 = ProcessData->lflag | 0x2000;
          ProcessData->lflag = v65;
          v66 = ProcessData->dispType[1];
          MenuSetMoverDisappear(ProcessData, v66);
          ProcessData->ctrlType = 6;
          v27 = 0;
          ProcessData->gflag &= 0xF7FFu;
          v25 = 3;
          goto LABEL_135;
        }
        if ((gflag & 0x108) != 8)
          return 0;
        if ((gflag & 0x40) != 0)
        {
          if (CHECK_TRIG(4098, 1) || CHECK_TRIG(4097, 1) || CHECK_TRIG(4096, 1) || CHECK_TRIG(4099, 1) || CHECK_TRIG(4107, 1) || CHECK_TRIG(4108, 1) || CHECK_TRIG(4104, 1) || CHECK_TRIG(4105, 1))
          {
            func = ProcessData->select->func;
            if (func)
            {
              (func->invoke_impl)(func->method_code, func->method);
              moveType = ProcessData->moveType;
              if (!moveType)
                return 0;
LABEL_57:
              MenuMoveHierarchy(ProcessData, moveType, 0);
              goto LABEL_58;
            }
          }
        }
        else
        {
          if ((gflag & 0x10000) != 0)
          {
            v61 = 0;
            v69 = 1;
          }
          else
          {
            if ((gflag & 0x4000) != 0)
            {
              v71 = v5[0];
              v73 = v5[0];
              if (v71 == g_MenuDecideKey)
              {
                v74 = 0;
              }
              else
              {
                v8[8] = v73;
                v74 = 1;
                v73 = 0;
              }
              v75 = v5[1];
              if (v75 == g_MenuDecideKey)
              {
                v73 = v5[1];
              }
              else
              {
                v76 = &v8[v74++];
                v76[8] = v5[1];
              }
              v77 = v5[2];
              if (v77 == g_MenuDecideKey)
              {
                v73 = v5[2];
              }
              else
              {
                v78 = &v8[v74++];
                v78[8] = v5[2];
              }
              v79 = v5[3];
              if (v79 == g_MenuDecideKey)
                v73 = v5[3];
              else
                v8[v74 + 8] = v5[3];
              v80 = CHECK_TRIG(v8[8], 1);
              v81 = CHECK_TRIG(v8[9], 1);
              v82 = CHECK_TRIG(v8[10], 1) || v81;
              v62 = v73;
              v63 = 1;
              v61 = v82 || v80;
            }
            else
            {
              v61 = CHECK_TRIG(4097, 1);
              v62 = 4096;
              v63 = 0;
            }
            v69 = CHECK_TRIG(v62, v63);
          }
          v83 = ProcessData->gflag;
          if (CHECK_TRIG(4097, 1) && (v83 & 0x8000) == 0 && v61)
          {
            if (Story11Select)
            {
              Story11Cancel = 1;
              cancelSE = ProcessData->select->cancelSE;
              v89 = cancelSE == -1;
              if (cancelSE >= -1)
              {
LABEL_222:
                if (v89)
                  v98 = 1;
                else
                  v98 = cancelSE;
                goto LABEL_225;
              }
              return 0;
            }
            if (QuestDevilSelect)
            {
              *(u16 *)&QuestDevilCancel = 257;
              cancelSE = ProcessData->select->cancelSE;
              v89 = cancelSE == -1;
              if (cancelSE >= -1)
                goto LABEL_222;
              return 0;
            }
            if (!v90)
            if (MenuMoveHierarchy(ProcessData, 1, 0))
            {
              select = ProcessData->select;
              cancelSE = select->cancelSE;
              v89 = cancelSE == -1;
              if (cancelSE >= -1)
                goto LABEL_222;
              return 0;
            }
          }
          if ((v69 & CHECK_TRIG(4096, 0) & 1) != 0)
          {
            v93 = ProcessData->select;
            v94 = v93->gflag;
            if ((v94 & 6) != 0)
            {
              if ((v94 & 0x20) != 0)
              {
                v97 = v93->func;
                if (v97)
                  (v97->invoke_impl)(v97->method_code, v97->method);
                MenuMoveHierarchy(ProcessData, 1, 0);
                cancelSE = ProcessData->select->cancelSE;
                v89 = cancelSE == -1;
                if (cancelSE >= -1)
                  goto LABEL_222;
                return 0;
              }
              if ((v94 & 0x80) != 0 && v93->func)
              {
                ProcessData->step = 5;
                decideSE = v93->decideSE;
                if (decideSE < -1)
                  return 0;
LABEL_245:
                v98 = decideSE & ~(decideSE >> 31);
LABEL_225:
                SE(v98);
                return 0;
              }
              if ((v94 & 0x100) != 0)
              {
                v99 = v93->func;
                if (v99)
                {
                  v100 = (v99->invoke_impl)(v99->method_code, v99->method);
                  v101 = ProcessData->moveType;
                  ProcessData->retFunc = v100;
                  if (v101)
                  {
                    if (MenuMoveHierarchy(ProcessData, v101, 0))
                    {
                      v102 = ProcessData->moveType;
                      if (v102 == 1)
                      {
                        v111 = ProcessData->select;
                        v112 = v111->cancelSE;
                        if (v112 < -1)
                          goto LABEL_58;
                        if (v112 == -1)
                          v105 = 1;
                        else
                          v105 = v111->cancelSE;
                      }
                      else
                      {
                        if (v102 != 2)
                          goto LABEL_58;
                        v103 = ProcessData->select;
                        v104 = v103->decideSE;
                        if (v104 < -1)
                          goto LABEL_58;
                        v105 = v104 & ~(v104 >> 31);
                      }
                      SE(v105);
LABEL_58:
                      v27 = 0;
                      ProcessData->moveType = 0;
                      return v27;
                    }
                    ProcessData->moveType = 0;
                  }
                }
              }
              if (MenuMoveHierarchy(ProcessData, 2, 0))
              {
                v106 = ProcessData->select;
                decideSE = v106->decideSE;
                if (decideSE < -1)
                  return 0;
                goto LABEL_245;
              }
            }
          }
        }
        if (MenuListScroll)
        {
          v27 = 0;
          MenuListScroll = 0;
        }
        else
        {
          if (!v110)
          MenuPadCtrlSelect(ProcessData);
          return 0;
        }
      }
      return v27;
    case 3u:
      MenuUpdateMover(ProcessData);
      v25 = 4;
      goto LABEL_134;
    case 4u:
      if (MenuUpdateMover(ProcessData))
        return 0;
      switch (ProcessData->ctrlType)
      {
        case 2:
          MenuUpdateNextLink(ProcessData);
          goto LABEL_120;
        case 3:
          MenuUpdatePrevLink(ProcessData);
LABEL_120:
          MenuSetMoverAppear(ProcessData, ProcessData->dispType[0]);
          goto LABEL_109;
        case 4:
          v56 = ProcessData->select->gflag;
          ProcessData->lflag = v56 & 0x40 | ProcessData->lflag & 0xD3DF | 0x2400;
          if ((v56 & 0x100) == 0)
          {
            v25 = 5;
            goto LABEL_134;
          }
          if (ProcessData->retFunc)
            goto LABEL_133;
          goto LABEL_124;
        case 5:
          ProcessData->lflag = ProcessData->lflag & 0xD3DF | 0x2000;
          if ((ProcessData->gflag & 0x10) != 0)
            goto LABEL_124;
          goto LABEL_133;
        case 6:
          v57 = ProcessData->gflag;
          ProcessData->gflag = v57 | 0x2000;
          if ((v57 & 0x1000) == 0)
            return 0;
          if ((ProcessData->select->gflag & 0x40) != 0)
            v59 = ProcessData->lflag & 0xDFFF;
          else
            v59 = ProcessData->lflag | 0x2000;
          ProcessData->lflag = v59;
          v60 = ProcessData->dispType[0];
          MenuSetMoverAppear(ProcessData, v60);
          v27 = 0;
          ProcessData->gflag &= 0xCFFFu;
          goto LABEL_110;
        default:
          return 0;
      }
    case 5u:
      v34 = (ProcessData->select->func->invoke_impl)(ProcessData->select->func->method_code, ProcessData->select->func->method);
      ProcessData->retFunc = v34;
      if (!v34)
      {
LABEL_124:
        v25 = 7;
        v27 = 0;
        ProcessData->count = 0;
        goto LABEL_135;
      }
      moveType = ProcessData->moveType;
      if (!moveType)
      {
LABEL_133:
        v25 = 6;
LABEL_134:
        v27 = 0;
        goto LABEL_135;
      }
      goto LABEL_57;
    case 6u:
      v38 = ProcessData->lflag;
      if ((v38 & 0x20) == 0)
        return 0;
      v39 = v38 | 0x2C00;
      v40 = ProcessData->select->gflag;
      v41 = ProcessData->lflag & 0xD3FF | 0xC00;
      if ((v40 & 0x40) == 0)
        v41 = v39;
      ProcessData->lflag = v41;
      if ((v40 & 0x80) == 0)
      {
        v42 = ProcessData->dispType[0];
        MenuSetMoverAppear(ProcessData, v42);
      }
      v27 = 0;
      ProcessData->ctrlType = 0;
      goto LABEL_110;
    case 7u:
      count = ProcessData->count;
      if (count)
      {
        if (count >= 2)
        {
          v25 = 9;
          v27 = 0;
          ProcessData->count = 0;
          goto LABEL_135;
        }
      }
      else
      {
        ProcessData->lflag &= 0xFDFFu;
      }
      v27 = 0;
      ProcessData->count = count + 1;
      return v27;
    case 8u:
      if ((ProcessData->select->gflag & 6) == 0)
        goto LABEL_108;
      goto LABEL_88;
LABEL_101:
      if (v47)
      {
        (v47->invoke_impl)(v47->method_code, v47->method);
        v46 = ProcessData->select;
      }
      v48 = 2;
      goto LABEL_104;
LABEL_88:
      v46 = ProcessData->select;
      v47 = v46->func;
      if ((v46->lflag & 2) != 0)
        goto LABEL_101;
      if (!v47)
        goto LABEL_108;
      v48 = 4;
LABEL_104:
      ProcessData->ctrlType = v48;
      if ((v46->gflag & 0x40) != 0)
        v53 = ProcessData->lflag & 0xDFFF;
      else
        v53 = ProcessData->lflag | 0x2000;
      ProcessData->lflag = v53;
      ProcessData->step = 3;
LABEL_108:
      MenuUpdateNextLink(ProcessData);
LABEL_109:
      v27 = 0;
LABEL_110:
      v25 = 2;
LABEL_135:
      ProcessData->step = v25;
      return v27;
    case 9u:
      v27 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v27, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v27;
    default:
      return 0;
  }
}

// 0x1c522e0
static void MenuDrawFont(MenuImgDat_t *pImgDat, s32 x, s32 y, u32 color, u8 alpha, char *str, char *tag) {
  f32 v11;
  s32 strWidth;
  f32 v13;

  if (pImgDat)
  {
    v11 = alpha;
    strWidth = pImgDat->strWidth;
    v13 = v11 / 255.0;
    if (v13 <= 0.0)
      return;
    if (str)
      return;
    return;
  }
}

// 0x1c52420
static void MenuDrawScrollBar(Menu_t *wk, s32 a_topno, s32 a_selmax, u8 a_alphaRate) {
  MenuImgDat_t *v7;

  v7 = wk->imgDat[3];
  if (v7->hSpr)
    return;
  v7->alpha = a_alphaRate;
  return;
}

// 0x1c524a0
static void _MenuDrawPanelEGL(s32 a_x, s32 a_y, s32 a_w, s32 a_h, u32 a_col) {
  ;
}

// 0x1c524b0
static void MenuDrawPanelEGL(s32 a_type, s32 a_x, s32 a_y, s32 a_w, s32 a_h, u8 a_alpha) {

}

// 0x1c52510
static void MenuDrawPanel(Menu_t *wk, MenuMover_t *mv, u8 a_alpha, s8 a_attr) {
  char *v5;
  u32 v8;
  MenuImgDat_t *imgDat;
  itfMover_t *mover;
  f32 posx;
  f32 posy;
  itfMoverCB_t *v15;
  u32 v16;
  s32 v17;
  u64 v18;
  u32 v19;
  s8 v20;
  MenuImgDat_t *v21;
  MenuCB_tag *cb;
  u32 lflag;
  s32 v26;
  bool v27;
  itfMenuDrawFunc_t funcDraw;
  itfMenuTextFunc_t funcText;
  char *str;
  u32 v31;

  v8 = a_alpha;
  imgDat = wk->imgDat;
  if (!imgDat[1]->hSpr && !imgDat[2]->hSpr)
  {
    mover = mv->mover;
    posx = 0.0;
    if (mover)
    {
      posy = 0.0;
      if (mover->cb_num >= 1)
      {
        v15 = mover->cb[mover->cb_cnt];
        posx = v15->posx;
        posy = v15->posy;
      }
LABEL_12:
      if (posx == INFINITY)
        v16 = 0x80000000;
      else
        v16 = (s32)posx;
      if (posy == INFINITY)
        v17 = 0x80000000;
      else
        v17 = posy;
      v18 = a_attr & 0xFFFFFFFFFFFFFFFBLL;
      v31 = v17;
      if ((u32)(v18 - 1) > 2)
      {
        v19 = -1600273536;
        v20 = a_attr;
        v21 = wk->imgDat[1];
        if (!v21->hSpr)
          goto LABEL_23;
      }
      else
      {
        v19 = dword_3E62A0C[v18 - 1];
        v20 = a_attr;
        v21 = wk->imgDat[1];
        if (!v21->hSpr)
          goto LABEL_23;
      }
      if (v21->pList)
LABEL_23:
      if ((v20 & 4) == 0)
        goto LABEL_34;
      goto LABEL_27;
      if ((v20 & 4) == 0)
      {
LABEL_34:
        cb = mv->cb;
        if (cb)
        {
          lflag = cb->lflag;
          if ((lflag & 0x10) != 0)
          {
            v26 = mv->count + 1;
            v27 = mv->count - 49 < 0;
            mv->count = v26;
            if (v27 == __OFSUB__(v26, 50))
            {
              mv->count = 0;
              cb->lflag = lflag & 0xFFEF;
            }
          }
          funcDraw = cb->funcDraw;
          if (funcDraw)
          {
            (funcDraw->invoke_impl)(funcDraw->method_code, (u32)cb->id, v16, v31, 256, v19, v8, funcDraw->method);
            cb = mv->cb;
          }
          funcText = cb->funcText;
          if (funcText)
          {
            (funcText->invoke_impl)(funcText->method_code, (u32)cb->no, v19, v8, cb->str, (u32)v18, cb->tag, funcText->method);
          }
          else
          {
            str = cb->str;
            MenuDrawFont(v21, (s32)mv, a_alpha, a_attr, v8, str, v5);
          }
        }
        return;
      }
LABEL_27:
      v21 = wk->imgDat[2];
      if (v21->hSpr && v21->pList)
      v21->alpha = v8;
      goto LABEL_34;
    }
    posy = 0.0;
    goto LABEL_12;
  }
}

// 0x1c52850
static void MenuDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag) {
  void *panel;
  void *setText;
  void *v17;
  void *v18;
  bool v19;
  void *v21;
  u32 v22;
  void *gameObject;
  char *v24;
  Il2CppObject *v25;
  char *v26;
  void *v27;
  void *v28;
  s32 data;

  panel = menu_win->panel;
  if (SLODWORD(panel->max_length) <= no)
  {
    goto LABEL_7;
  }
  v21 = panel[no];
  fldSetupObject(v21, 1);
LABEL_7:
  setText = menu_win->setText;
  if (SLODWORD(setText->max_length) <= no)
    goto LABEL_8;
  if (color == 1692838528)
  {
    v22 = -1340416;
    goto LABEL_29;
  }
  else if (color == -1600273536)
  {
    v22 = -673588992;
    goto LABEL_29;
  }
  else
  {
    v22 = color & 0xFFFFFF00;
    goto LABEL_29;
  }
  setText = menu_win->setText;
LABEL_29:
  gameObject = get_gameObject(setText[no], 0);
  fldSetupObject(gameObject, 1);
  data = v22 | alpha;
  v24 = Concat_54831728("<color=#{0:X}>", str, "</color>", 0);
  v25 = Box(uint, &data);
  v26 = Format(v24, v25, 0);
  v27 = menu_win->setText[no];
  (v27->klass->vtable._66_set_text.methodPtr)(v27, v26, v27->klass->vtable._66_set_text.method);
  if ((attr & 2) == 0)
    goto LABEL_9;
  goto LABEL_32;
LABEL_8:
  if ((attr & 2) == 0)
  {
LABEL_9:
    v17 = menu_win->cursor[no];
    v18 = v17;
    v19 = 0;
    goto LABEL_37;
  }
LABEL_32:
  v28 = menu_win->cursor[no];
  v18 = v28;
  v19 = 1;
LABEL_37:
  fldSetupObject(v18, v19);
}

// 0x1c52ba0
static bool awdMenuDrawTargetCheck(s32 no) {
  void *v3;
  s32 v4;

  v3 = NewSpecific(s32, 6u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__AF3432F640D906494D8A8D408350C4D8C13B8B909E493E075B7E9EED22720E09, 0);
  v4 = *((u32 *)&v3[2].klass + no);
  return mapIfFieldDestCheck(v4, -1);
}

// 0x1c52c60
static void awdMenuDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag) {
  void *panel;
  void *setText;
  void *markObj;
  void *v18;
  void *v19;
  bool v20;
  void *v22;
  void *gameObject;
  u32 v24;
  char *v25;
  Il2CppObject *v26;
  char *v27;
  void *v28;
  void *v29;
  bool v30;
  void *v31;
  s32 data;

  panel = ikai_watari->panel;
  if (SLODWORD(panel->max_length) <= no)
  {
    goto LABEL_7;
  }
  v22 = panel[no];
  fldSetupObject(v22, 1);
LABEL_7:
  setText = ikai_watari->setText;
  if (SLODWORD(setText->max_length) <= no)
  {
    goto LABEL_9;
  }
  setText = ikai_watari->setText;
  gameObject = get_gameObject(setText[no], 0);
  fldSetupObject(gameObject, 1);
  if (color == -1600273536)
    v24 = -256;
  else
    v24 = color & 0xFFFFFF00;
  data = v24 | alpha;
  v25 = Concat_54831728("<color=#{0:X}>", str, "</color>", 0);
  v26 = Box(uint, &data);
  v27 = Format(v25, v26, 0);
  v28 = ikai_watari->setText[no];
  (v28->klass->vtable._66_set_text.methodPtr)(v28, v27, v28->klass->vtable._66_set_text.method);
LABEL_9:
  markObj = ikai_watari->markObj;
  if (SLODWORD(markObj->max_length) > no)
  {
    markObj = ikai_watari->markObj;
    v29 = markObj[no];
    v30 = awdMenuDrawTargetCheck(no);
    fldSetupObject(v29, v30);
    if ((attr & 2) == 0)
      goto LABEL_11;
    goto LABEL_34;
  }
  if ((attr & 2) == 0)
  {
LABEL_11:
    v18 = ikai_watari->cursor[no];
    v19 = v18;
    v20 = 0;
    goto LABEL_39;
  }
LABEL_34:
  v31 = ikai_watari->cursor[no];
  v19 = v31;
  v20 = 1;
LABEL_39:
  fldSetupObject(v19, v20);
}

// 0x1c53020
static void elvMenuDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  Il2CppObject *v18;
  Il2CppObject *v19;
  f32 monitor_high;
  f32 v23;
  s32 v24;
  f32 v25;
  bool v27;
  s64 v28;
  void *panel;
  f32 v31;
  void *v32;
  void *v33;
  bool v34;
  void *v35;
  f32 v37;
  f32 v38;
  void *v41;
  u32 v45;
  void *v49;
  void *setText;
  void *gameObject;
  u32 v53;
  char *v54;
  Il2CppObject *v55;
  char *v56;
  void *v57;
  void *v60;
  void *v61;
  bool v62;
  void *v63;
  s32 data;
  dds3ProcessID_t *id;
  sdfVector2_t v66;
  sdfVector2_t v67;

  id = elvMenu_g_mainPID;
  ProcessData = dds3GetProcessData(id);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((elvMenu_t **)(ProcessData)[1].next + naturalAligment - 1) != elvMenu_t;
  v18 = dds3GetProcessData(ProcessData + 3);
  v19 = v18;
  monitor_high = SHIDWORD(v18[7].monitor);
  v23 = (f32)SLODWORD(v18[8].klass) / monitor_high;
  v24 = *((u32 *)v18[9].monitor + SBYTE4(v18[5].monitor) + 8);
  v25 = v24;
  v28 = (u32)(no - v24);
  v27 = no - v24 < 0;
  panel = elv->panel;
  v31 = v25 / monitor_high;
  if (v27 || (s32)v28 >= SLODWORD(panel->max_length))
  {
    panel = elv->panel;
    v35 = panel[(s32)v28];
    v33 = v35;
    v34 = 0;
  }
  else
  {
    panel = elv->panel;
    v32 = panel[(u32)v28];
    v33 = v32;
    v34 = 1;
  }
  fldSetupObject(v33, v34);
  v37 = SCROLLBAR_LENGTH_MAX * v31;
  v38 = SCROLLBAR_LENGTH_MAX * v23;
  v66.y = -v37;
  v66.x = 0.0;
  set_anchoredPosition(elvScroll, v66, 0);
  v67.x = 8.0;
  v67.y = v38;
  set_sizeDelta(elvScroll, v67, 0);
  if (v37 >= 0.001)
  {
    fldSetupObject(elvArrowU, 1);
  }
  else
  {
    v41 = elvArrowU;
    fldSetupObject(v41, 0);
  }
  if (v37 < (f32)((f32)(SCROLLBAR_LENGTH_MAX * (f32)(1.0 / (f32)SHIDWORD(v19[7].monitor))) * (f32)((f32)SHIDWORD(v19[7].monitor) - (f32)SLODWORD(v19[8].klass))))
  {
    if (v45)
    {
      goto LABEL_48;
    }
    else
    {
      goto LABEL_48;
    }
LABEL_48:
    fldSetupObject(elvArrowD, 1);
    goto LABEL_54;
  }
  if (v45)
  {
    v49 = elvArrowD;
    goto LABEL_52;
  }
  else
  {
    v49 = elvArrowD;
    goto LABEL_52;
  }
LABEL_52:
  fldSetupObject(v49, 0);
LABEL_54:
  if ((v28 & 0x80000000) == 0)
  {
    setText = elv->setText;
    if ((s32)v28 < SLODWORD(setText->max_length))
    {
      setText = elv->setText;
      gameObject = get_gameObject(setText[(u32)v28], 0);
      fldSetupObject(gameObject, 1);
      if (color == -1600273536)
        v53 = -256;
      else
        v53 = color & 0xFFFFFF00;
      data = v53 | alpha;
      v54 = Concat_54831728("<color=#{0:X}>", str, "</color>", 0);
      v55 = Box(uint, &data);
      v56 = Format(v54, v55, 0);
      v57 = elv->setText[v28];
      (v57->klass->vtable._66_set_text.methodPtr)(v57, v56, v57->klass->vtable._66_set_text.method);
    }
  }
  if ((attr & 2) != 0)
  {
    v63 = elv->cursor[(s32)v28];
    v61 = v63;
    v62 = 1;
  }
  else
  {
    v60 = elv->cursor[(s32)v28];
    v61 = v60;
    v62 = 0;
  }
  fldSetupObject(v61, v62);
}

// 0x1c536f0
static void ShopDbgDrawFont(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag) {
  char **v10;
  char *v11;
  sdfColor_t v12;

  if ((attr & 2) != 0)
    v10 = &"<color=#ffffffff>";
  else
    v10 = &"<color=#c0c0c0ff>";
  v11 = Concat_54831728(*v10, str, "</color>", 0);
  v12.r = 1.0;
  v12.g = 1.0;
  v12.b = 1.0;
  v12.a = 1.0;
  SetTextPartsDataList(10.0, (f32)(s32)((32 * no) ^ 0xFFFFFFEC), 150.0, 32.0, v12, v11, 0);
}

// 0x1c53800
static void NakamaSelDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag) {
  void *panel;
  void *gameObject;
  s32 v17;

  panel = devil_win->panel;
  if (SLODWORD(panel->max_length) <= no)
  {
    goto LABEL_5;
  }
  panel = devil_win->panel;
  gameObject = get_gameObject(panel[no], 0);
  fldSetupObject(gameObject, 1);
LABEL_5:
  if (SLODWORD(devil_win->setText->max_length) <= no)
    goto LABEL_6;
  if (color == -1600273536)
  {
    v17 = 1;
    goto LABEL_25;
  }
  else if (color == 1296780109 || color == 1349079155)
  {
    v17 = 2;
    goto LABEL_25;
  }
  else
  {
    v17 = 0;
    goto LABEL_25;
  }
LABEL_25:
  SetText(devil_win->panel[no], str, v17, tag, 0);
LABEL_6:
  SetCursor(devil_win->panel[no], (attr & 2) != 0, 0);
}

// 0x1c53a40
static void MenuDrawTitle(Menu_t *wk, s32 a_x, s32 a_y, u8 a_alpha, char *a_str) {
  char *v6;
  u8 v9;
  MenuImgDat_t *v11;

  v9 = a_alpha;
  v11 = wk->imgDat[0];
  if (v11->hSpr)
    return;
  if ((wk->lflag & 0x2000) == 0)
    v9 = -1;
  if ((wk->gflag & 4) == 0)
  {
    v11->alpha = v9;
    return;
  }
  MenuDrawFont(v11, a_x, a_y, a_alpha, v9, a_str, v6);
  v11->alpha = v9;
}

// 0x1c53b90
static u8 MenuCalcAlpha(MenuMover_t *mv, u32 lflag) {
  s16 v3;
  itfMover_t *mover;
  f32 v7;
  u16 flag;
  s32 total_frm;
  s32 total_cnt;
  s32 v11;
  bool v12;
  s32 v13;
  s32 v14;
  f32 v16;
  MenuCB_tag *cb;
  u32 v18;

  v3 = lflag;
  mover = mv->mover;
  v7 = 0.0;
  if (mover)
  {
    flag = mover->flag;
    if ((flag & 2) != 0)
    {
      v7 = 255.0;
    }
    else if ((flag & 1) != 0)
    {
      total_frm = mover->total_frm;
      if (total_frm >= 1)
      {
        total_cnt = mover->total_cnt;
        v11 = mover->cb[0]->wait[0];
        v12 = __OFSUB__(total_cnt, v11);
        v13 = total_cnt - v11;
        if (v13 < 0 == v12)
        {
          v14 = total_frm - v11;
          if (v13 >= 1 && v14 >= 1)
          {
            v16 = (f32)v13 / (f32)v14;
            if (v16 >= 0.0)
            {
              v7 = 255.0;
              if (v16 <= 1.0)
                v7 = v16 * 255.0;
            }
          }
        }
      }
    }
  }
  cb = mv->cb;
  if (!cb || (v18 = cb->lflag, (v18 & 0x1000) == 0))
  {
    if ((v3 & 0x40) == 0)
      v7 = 255.0 - v7;
    if ((v3 & 0x1000) == 0)
      return (s32)255.0;
    return (s32)v7;
  }
  if ((v18 & 0x2000) == 0)
    return -1;
  if ((v18 & 0x4000) != 0)
    return (s32)v7;
  if ((v18 & 0x8000) != 0)
    return (s32)(f32)(255.0 - v7);
  return 0;
}

// 0x1c53d10
static dds3ProcessFunc_t MenuDrawProcess(dds3ProcessID_t *PID) {
  Menu_t *ProcessData;
  MenuImgDat_t *imgDat;
  u32 lflag;
  MenuImgDat_t *v8;
  MenuImgDat_t *v9;
  MenuImgDat_t *v10;
  u32 gflag;
  s32 ot;
  MenuCB_tag *select;
  u32 v16;
  char *str;
  itfMover_t *mover;
  MenuCB_tag *pParent;
  itfMoverCB_t *v20;
  bool v22;
  s32 v23;
  s32 v25;
  s32 v26;
  u8 v27;
  s64 v29;
  u32 v30;
  MenuMover_t *v31;
  u8 v32;
  MenuCB_tag *cb;
  u8 v35;
  u32 v36;
  s32 v37;
  s32 v41;
  u32 v42;
  s32 v43;
  MenuMover_t *v44;
  u8 v45;
  MenuImgDat_t *v46;
  s32 scrollType;
  MenuImgDat_t *v48;
  u32 v49;
  MenuMover_t *v50;
  u8 v51;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  imgDat = ProcessData->imgDat;
  lflag = ProcessData->lflag;
  v8 = imgDat[1];
  imgDat[0]->alpha = 0;
  v10 = imgDat[2];
  v9 = imgDat[3];
  v8->alpha = 0;
  v10->alpha = 0;
  v9->alpha = 0;
  if ((lflag & 0x200) == 0)
    return 0;
  if ((u32)(ProcessData->step - 2) > 4)
    return 0;
  gflag = ProcessData->gflag;
  if ((gflag & 1) == 0)
    return 0;
  ot = ProcessData->ot;
  gflag = ProcessData->gflag;
  lflag = ProcessData->lflag;
  g_ot = ot;
  if ((gflag & 2) != 0 && (lflag & 0x400) != 0)
  {
    select = ProcessData->select;
    ProcessData->titleParent = 0;
    v16 = select->gflag;
    if ((v16 & 0x200) != 0 || ProcessData->step != 6)
    {
      pParent = select->pParent;
      if (pParent)
      {
        str = pParent->str;
        ProcessData->titleParent = 1;
        mover = ProcessData->mv_title->mover;
        goto LABEL_24;
      }
      else
      {
        str = ProcessData->title->str;
        mover = ProcessData->mv_title->mover;
LABEL_24:
        if (mover && mover->cb_num >= 1)
        {
          v20 = mover->cb[mover->cb_cnt];
          itfMenuDrawProcess_fx = v20->posx;
          itfMenuDrawProcess_fy = v20->posy;
        }
        v22 = itfMenuDrawProcess_fx == INFINITY;
        v23 = itfMenuDrawProcess_fx;
        if (v22)
          v25 = 0x80000000;
        else
          v25 = v23;
        if (itfMenuDrawProcess_fy == INFINITY)
          v26 = 0x80000000;
        else
          v26 = itfMenuDrawProcess_fy;
        v27 = MenuCalcAlpha(ProcessData->mv_title, ProcessData->lflag);
        MenuDrawTitle(ProcessData, v25, v26, v27, str);
        lflag = ProcessData->lflag;
        goto LABEL_34;
      }
      goto LABEL_24;
    }
    if ((v16 & 0x40) != 0)
    {
      str = select->str;
      mover = ProcessData->mv_title->mover;
      goto LABEL_24;
    }
  }
LABEL_34:
  if ((lflag & 0x800) != 0)
  {
    if (ProcessData->drwDefNum < 1)
      goto LABEL_64;
    v29 = 0;
    while (1)
    {
      v30 = ProcessData->lflag;
      v31 = ProcessData->mv[v29];
      v32 = MenuCalcAlpha(ProcessData->mv[v29], v30);
      cb = v31->cb;
      v35 = v32;
      if (!cb)
      {
        LOBYTE(v41) = 0;
        goto LABEL_37;
      }
      if ((ProcessData->gflag & 8) != 0)
      {
        v36 = (cb->lflag & 4) >> 2;
        if ((cb->lflag & 4) != 0)
          v37 = 6;
        else
          v37 = 0;
      }
      else
      {
        LOBYTE(v36) = 0;
        v37 = 0;
      }
      v42 = cb->gflag;
      v43 = (v42 >> 2) & 2 | v37;
      if ((v42 & 0x10) != 0)
        v43 |= 4u;
      v41 = (v42 >> 8) & 8 | ((~v42 & 3) != 0) | v43;
      cb->attrUnity = v41;
      if ((v42 & 0x10) == 0 && (v36 & 1) == 0)
      {
        goto LABEL_37;
      }
      uniMenuCursor = v29;
LABEL_37:
      MenuDrawPanel(ProcessData, v31, v35, v41);
      if (++v29 >= ProcessData->drwDefNum)
      {
        lflag = ProcessData->lflag;
LABEL_64:
        v44 = ProcessData->mv[0];
        v45 = MenuCalcAlpha(v44, lflag);
        v46 = ProcessData->imgDat;
        ProcessData->scrollAlphaUnity = v45;
        v46[1]->alpha = v45;
        scrollType = ProcessData->scrollType;
        if (scrollType == 2)
        {
          if (v45 == 0xFF)
            goto LABEL_73;
        }
        else if (!scrollType)
        {
          if (ProcessData->selMax <= ProcessData->drwMax || v45 != 0xFF)
          {
LABEL_77:
            ProcessData->scrollDrawUnity = scrollType;
            break;
          }
LABEL_73:
          v48 = ProcessData->imgDat[3];
          if (!v48->hSpr)
            v48->alpha = -1;
          LOBYTE(scrollType) = 1;
          goto LABEL_77;
        }
        LOBYTE(scrollType) = 0;
        goto LABEL_77;
      }
    }
  }
  if (ProcessData->unityCtrl)
  {
    v49 = ProcessData->lflag;
    v50 = ProcessData->mv[0];
    v51 = MenuCalcAlpha(v50, v49);
    (ProcessData->unityCtrl->invoke_impl)(ProcessData->unityCtrl->method_code, ProcessData->unityCtrl->(f32)v51 / 255.0);
  }
  return 0;
}

// 0x1c54270
void itfMenuCallEnd(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    if (!dds3ExistProcess(id))
      return;
    ProcessData = dds3GetProcessData(id);
    if (ProcessData)
    {
      if (LODWORD(ProcessData[5].monitor) == 2)
        LODWORD(ProcessData[13].klass) |= 0x80u;
    }
  }
}

// 0x1c54380
static void MenuRelease(Menu_t *wk) {
  MenuImgDat_t *imgDat;
  MenuImgDat_t *v5;
  MenuImgDat_t *p_fields;
  sprHandle_t *hSpr;
  MenuImgDat_t *v8;
  MenuImgDat_t *v9;
  sprHandle_t *v10;
  MenuImgDat_t *v11;
  MenuImgDat_t *v12;
  sprHandle_t *v13;
  MenuImgDat_t *v14;
  MenuImgDat_t *v15;
  sprHandle_t *v16;

  imgDat = wk->imgDat;
  v5 = imgDat[0];
  hSpr = v5->hSpr;
  p_fields = &v5->fields;
  if (hSpr)
  {
    p_fields->hSpr = 0;
    imgDat = wk->imgDat;
  }
  v8 = imgDat[1];
  v10 = v8->hSpr;
  v9 = &v8->fields;
  if (v10)
  {
    v9->hSpr = 0;
    imgDat = wk->imgDat;
  }
  v11 = imgDat[2];
  v13 = v11->hSpr;
  v12 = &v11->fields;
  if (v13)
  {
    v12->hSpr = 0;
    imgDat = wk->imgDat;
  }
  v14 = imgDat[3];
  v16 = v14->hSpr;
  v15 = &v14->fields;
  if (v16)
  {
    v15->hSpr = 0;
  }
  while (wk->pTail)
  {
    MenuDeleteMenu(wk, &wk->pTail);
  }
}

// 0x1c54480
static void MenuShutdown(dds3ProcessID_t *PID) {
  Menu_t *ProcessData;
  dds3ProcessID_t *p_drawPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  MenuRelease(ProcessData);
  p_drawPID = &ProcessData->drawPID;
  if (dds3ExistProcess(p_drawPID))
  {
    dds3KillProcess(p_drawPID, 0);
  }
}

// 0x1c469e0
dds3ProcessID_t *itfMenuProcessStart(void) {
  dds3ProcessID_t *v1;
  Menu_t *v2;
  dds3ProcessFunc_t v6;
  shutdownfuncDelegate v7;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v9;
  dds3ProcessID_t *v10;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = Allocate(Menu_t);
  _ctor(v2, 0);
  MenuListScroll = 0;
  MenuOldCsr = -1;
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_itf_MenuProcess__, 0);
  v7 = Allocate(shutdownfuncDelegate);
  _ctor(v7, 0, Method_Project_itf_MenuShutdown__, 0);
  started = dds3StartProcess("itfmenu_main", 1023, 0, 0, v6, v7, v2);
  v9 = Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_itf_MenuDrawProcess__, 0);
  v10 = dds3StartProcess("itfmenu_draw", 11029, 0, 0, v9, 0, v2);
  v2->drawPID = v10;
  MenuInit(v2);
  v2->lflag |= 2u;
  return started;
}

// 0x1c2f770
void itfMenuProcessEnd(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass_high;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    if (!dds3ExistProcess(id))
      return;
    ProcessData = dds3GetProcessData(id);
    if (!ProcessData)
    {
LABEL_14:
      klass_high = HIDWORD(ProcessData[13].klass);
      if ((klass_high & 1) == 0)
      {
        HIDWORD(ProcessData[13].monitor) = 0;
        HIDWORD(ProcessData[13].klass) = klass_high | 1;
        LODWORD(ProcessData[5].monitor) = 7;
      }
      return;
    }
    goto LABEL_14;
  }
}

// 0x1c2f9e0
bool itfMenuProcessCheck(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  if (!PID)
    return 0;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  if (dds3GetProcessStat(id))
    return 1;
  return 0;
}

// 0x1c545c0
void itfMenuFrcCancel(dds3ProcessID_t *PID) {
  Menu_t *ProcessData;
  MenuCB_tag *select;
  s32 cancelSE;
  s32 v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (ProcessData->step != 2)
    return;
  if (!MenuMoveHierarchy(ProcessData, 1, 0))
    return;
  select = ProcessData->select;
  cancelSE = select->cancelSE;
  if (cancelSE >= -1)
  {
    if (cancelSE == -1)
      v9 = 1;
    else
      v9 = select->cancelSE;
    SE(v9);
  }
}

// 0x1c54730
void itfMenuSetCtrlFuncForUnity(dds3ProcessID_t *PID, itfMenuCtrlUnity a_func) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  klass = ProcessData->klass;
}

// 0x1c54810
void itfMenuSetMoveFunc(dds3ProcessID_t *PID, itfMenuMoveFunc func) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  klass = ProcessData->klass;
}

// 0x1c2f0b0
void itfMoverSetMenu(dds3ProcessID_t *PID, itfMoverFunc_t a_func) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  klass = ProcessData->klass;
}

// 0x1c548f0
u32 itfGetTextColor(MenuMover_t *_mv, u32 _gflag) {
  MenuCB_tag *cb;
  u64 v4;

  if (mv)
  {
    cb = mv->cb;
    if (cb && (v4 = cb->attrUnity & 0xFFFFFFFFFFFFFFFBLL, (u32)v4 <= 8))
      LODWORD(mv) = dword_3E62A18[v4];
    else
      LODWORD(mv) = 0;
  }
  return (u32)mv;
}

// 0x1c54930
bool itfGetCur(MenuMover_t *_mv) {
  MenuCB_tag *cb;
  _BOOL4 v3;

  cb = mv->cb;
  if (cb)
    return (cb->lflag >> 2) & 1;
  else
    LOBYTE(v3) = 0;
  return v3;
}

// 0x1c54950
void itfResetCursorDraw(void) {
  void *gameObject;
  void *cursor;
  void *v9;
  void *v10;

  gameObject = get_gameObject(menu_win, 0);
  if (get_activeSelf(gameObject, 0))
  {
    cursor = menu_win->cursor;
    if (uniMenuCursor < SLODWORD(cursor->max_length))
    {
      v9 = menu_win;
      cursor = v9->cursor;
      v10 = cursor[uniMenuCursor];
      fldSetupObject(v10, 0);
    }
  }
}

// 0x1c54a70
bool itfIsMesKey(SDF_PADMAP key, itf_PADREAD read) {
  char v3;
  bool v7;

  v3 = read;
  if (!!sbattleIsBattle())
  {
    if (battle_key_wait)
      return 0;
  }
  if (key <= 36865)
  {
    if (key == 4096)
    {
      if ((v3 & 1) == 0 || (v7 = 1, !CHECK_PRESS(4096, 1)))
      {
        if ((v3 & 2) == 0 || (v7 = 1, !CHECK_TRIG(4096, 1)))
        {
          if ((v3 & 4) == 0)
            return 0;
          v7 = 1;
          if (!CHECK_REP(4096, 1))
            return 0;
        }
      }
    }
    else
    {
      if (key != 4097)
        return 0;
      if ((v3 & 1) == 0 || (v7 = 1, !CHECK_PRESS(4097, 1)))
      {
        if ((v3 & 2) == 0 || (v7 = 1, !CHECK_TRIG(4097, 1)))
        {
          if ((v3 & 4) == 0)
            return 0;
          v7 = 1;
          if (!CHECK_REP(4097, 1))
            return 0;
        }
      }
    }
  }
  else if (key == 36866)
  {
    if ((v3 & 1) == 0 || (v7 = 1, !CHECK_PRESS(36866, 1)))
    {
      if ((v3 & 2) == 0 || (v7 = 1, !CHECK_TRIG(36866, 1)))
      {
        if ((v3 & 4) == 0)
          return 0;
        v7 = 1;
        if (!CHECK_REP(36866, 1))
          return 0;
      }
    }
  }
  else
  {
    if (key != 36867)
    {
      if (key == 36877)
      {
        if ((v3 & 1) != 0)
        {
          v7 = 1;
          if (CHECK_PRESS(36877, 1))
            return v7;
        }
        if ((v3 & 2) != 0)
        {
          v7 = 1;
          if (CHECK_TRIG(36877, 1))
            return v7;
        }
        if ((v3 & 4) != 0)
        {
          v7 = 1;
          if (CHECK_REP(36877, 1))
            return v7;
        }
      }
      return 0;
    }
    if ((v3 & 1) == 0 || (v7 = 1, !CHECK_PRESS(36867, 1)))
    {
      if ((v3 & 2) == 0 || (v7 = 1, !CHECK_TRIG(36867, 1)))
      {
        if ((v3 & 4) == 0)
          return 0;
        v7 = 1;
        if (!CHECK_REP(36867, 1))
          return 0;
      }
    }
  }
  return v7;
}

// 0x1c54e60
void itfBattleEvtKeyWaitInit(void) {
  battle_key_wait = 0;
  return;
}

// 0x1c54ee0
void itfBattleEvtKeyWaitProc(void) {
  s32 v5;

  if (!battle_key_wait)
    return;
  v5 = battle_key_wait - 1;
  battle_key_wait = v5;
  if (v5 > 0)
    return;
  itfSetGuide(bk_msg_guide_name, 1);
  itf_cr_icon = 1;
}

// 0x1c55220
void itfBattleEvtKeyWaitSet(s32 time) {
  battle_key_wait = time;
  return;
}

// 0x1c54da0
static bool IsBattleEvtKeyWait(void) {
  if (!sbattleIsBattle())
    return 0;
  return battle_key_wait != 0;
}

// 0x1c552b0
void itfLipSyncStart(s32 unit_uniqid, s32 motion_no) {
  LIPSYNC_PARAM *lipsync_pm_local;

  lipsync_pm_local = lipsync_pm;
  lipsync_pm_local->unit_uniqid = unit_uniqid;
  lipsync_pm_local->motion_no = motion_no;
  *(u64 *)&lipsync_pm_local->start = 1;
  lipsync_pm_local->autoTime = 240;
}

// 0x1c55340
bool itfIsLipSyncStart(void) {
  return lipsync_pm->start != 0;
}

// 0x1c33340
void itfLipSyncParam(s32 motion_no) {
  s32 unit_uniqid;
  dds3ModelHandle_t *LipModel;
  void *gameObject;
  Il2CppObject *Component_object;
  bool v10;
  LIPSYNC_PARAM *v14;
  s32 LanguageTYPE;

  lipsync_pm->motion_no = motion_no;
  unit_uniqid = lipsync_pm->unit_uniqid;
  LipModel = evtGetLipModel(unit_uniqid);
  if (LipModel)
  {
    gameObject = get_gameObject(LipModel->modelRoot->modelObj, 0);
    Component_object = GetComponent_object_(gameObject);
    goto LABEL_10;
  }
  Component_object = 0;
LABEL_10:
  v10 = op_Equality(Component_object, 0, 0);
  if (!v10)
  {
    lipsync_pm->lipend_time = 0;
    return;
  }
  goto LABEL_14;
LABEL_28:
  v14->lipend_time = 0;
  return;
LABEL_14:
  v14 = lipsync_pm;
  if (!v14->start)
    goto LABEL_28;
  LanguageTYPE = GetLanguageTYPE();
  if (LanguageTYPE)
  {
    lipsync_pm->lipend_time = 4 * lipsync_pm->tlen + 120;
    return;
  }
  lipsync_pm->lipend_time = (2 * (lipsync_pm->tlen + (lipsync_pm->tlen < 0)))
                                                     & 0xFFFFFFFC;
}

// 0x1c55430
void *itfGetCriLipSyncManager(s32 unit_uniqid) {
  void *result;
  void *gameObject;

  result = (void *)evtGetLipModel(unit_uniqid);
  if (result)
  {
    gameObject = get_gameObject(*(void *)(result[1].m_CachedPtr + 208), 0);
    return (void *)GetComponent_object_(gameObject);
  }
  return result;
}

// 0x1c554b0
void itfCriLipSyncManagerOff(dds3ModelHandle_t *mh) {
  void *gameObject;
  Il2CppObject *Component_object;

  if (mh)
  {
    gameObject = get_gameObject(mh->modelRoot->modelObj, 0);
    Component_object = GetComponent_object_(gameObject);
    if (!op_Inequality(Component_object, 0, 0))
      return;
    goto LABEL_6;
    if (op_Inequality(Component_object, 0, 0))
    {
LABEL_6:
      DeformerDisable(Component_object, 0);
      set_enabled(Component_object, 0, 0);
    }
  }
}

// 0x1c553b0
void *itfGetCriLipSyncSource(s32 unit_uniqid) {
  void *result;
  void *gameObject;

  result = (void *)evtGetLipModel(unit_uniqid);
  if (result)
  {
    gameObject = get_gameObject(*(void *)(*(u64 *)&result->initialized + 208), 0);
    return (void *)GetComponent_object_(gameObject);
  }
  return result;
}

// 0x1c55590
void itfLipSyncSetVoice(char *voice_name) {
  LIPSYNC_PARAM *lipsync_pm_local;

  lipsync_pm_local = lipsync_pm;
  lipsync_pm_local->voice_name = voice_name;
  lipsync_pm->autoTime = 240;
}

// 0x1c55620
void itfLipSyncSetTagID(char *tagid) {
  LIPSYNC_PARAM *lipsync_pm_local;

  lipsync_pm_local = lipsync_pm;
  lipsync_pm_local->tagid = tagid;
}

// 0x1c55690
char *itfLipSyncGetVoice(void) {
  return lipsync_pm->voice_name;
}

// 0x1c55720
char *itfLipSyncGetTagID(void) {
  return lipsync_pm->tagid;
}

// 0x1c557b0
void itfLipSyncCalc(void) {
  s32 lipend_time;
  LIPSYNC_PARAM *v4;

  if (!lipsync_pm->start)
    return;
  lipend_time = lipsync_pm->lipend_time;
  if (lipend_time)
  {
    lipend_time = lipsync_pm->lipend_time;
    lipsync_pm->lipend_time = lipend_time - 1;
  }
  v4 = lipsync_pm;
  if (v4->lipend_time)
    return;
  evtLipsStopFunction(v4->motion_no);
}

// 0x1c558f0
void itfSetLipSyncTime(s32 time) {
  lipsync_pm->lipend_time = time;
}

// 0x1c55960
bool itfLipSyncEndCheck(void) {
  s32 ConfigAUDIO;
  s32 unit_uniqid;
  dds3ModelHandle_t *LipModel;
  void *gameObject;
  Il2CppObject *Component_object;
  s32 autoTime;

  if (lipsync_pm->script_auto_skip)
  {
    goto LABEL_7;
  }
  ConfigAUDIO = cfgGetConfigAUDIO(7, 0);
  if (!ConfigAUDIO)
    return ConfigAUDIO;
LABEL_7:
  if (IsNullOrEmpty(lipsync_pm->voice_name, 0))
    goto LABEL_27;
  if (cfgGetConfigAUDIO(4, 0))
  {
    unit_uniqid = lipsync_pm->unit_uniqid;
    LipModel = evtGetLipModel(unit_uniqid);
    if (LipModel)
    {
      gameObject = get_gameObject(LipModel->modelRoot->modelObj, 0);
      Component_object = GetComponent_object_(gameObject);
      goto LABEL_24;
    }
    Component_object = 0;
LABEL_24:
    if (!sndVoiceStatus(Component_object))
    {
      if (lipsync_pm->lipend_time)
        goto LABEL_32;
      LOBYTE(ConfigAUDIO) = 1;
      return ConfigAUDIO;
    }
LABEL_32:
    LOBYTE(ConfigAUDIO) = 0;
    return ConfigAUDIO;
  }
LABEL_27:
  autoTime = lipsync_pm->autoTime;
  if (autoTime)
  {
    autoTime = lipsync_pm->autoTime;
    lipsync_pm->autoTime = autoTime - 1;
    goto LABEL_32;
  }
  LOBYTE(ConfigAUDIO) = 1;
  return ConfigAUDIO;
}

// 0x1c55cb0
static bool IsAutoFeed(void) {
  if (lipsync_pm->script_auto_skip)
    return 1;
  return cfgGetConfigAUDIO(7, 0) != 0;
}

// 0x1c55d80
void itfLipSyncEnd(void) {
  s32 unit_uniqid;
  dds3ModelHandle_t *LipModel;
  void *gameObject;
  Il2CppObject *Component_object;
  LIPSYNC_PARAM *lipsync_pm_local;
  LIPSYNC_PARAM *v8;

  evtLipsStopFunction(lipsync_pm->motion_no);
  unit_uniqid = lipsync_pm->unit_uniqid;
  LipModel = evtGetLipModel(unit_uniqid);
  if (!LipModel)
  {
    Component_object = 0;
    goto LABEL_10;
  }
  gameObject = get_gameObject(LipModel->modelRoot->modelObj, 0);
  Component_object = GetComponent_object_(gameObject);
LABEL_10:
  sndVoiceStop(Component_object);
  lipsync_pm_local = lipsync_pm;
  lipsync_pm_local->msglbl = 0;
  lipsync_pm_local = ((char *)lipsync_pm_local + 40);
  LODWORD(lipsync_pm_local[-1].tagid) = 0;
  *(&lipsync_pm_local[-1].script_guide_disp + 1) = 0;
  lipsync_pm_local[-1].script_auto_skip = 0;
  v8 = lipsync_pm;
  v8->voice_name = 0;
}

// 0x1c55ed0
static void MesVoiceStop(void *src, bool hojo) {
  if ((byte_5757566 & 1) != 0)
  {
    if (hojo)
      return;
  }
  else
  {
    if (hojo)
      return;
  }
  sndVoiceStop(src);
}

// 0x1c55f70
void itfSetPmvRun(s32 flg) {
  logdispwk->pmvrun = flg;
}

// 0x1c55fe0
bool itfIsPmvRun(void) {
  return logdispwk->pmvrun != 0;
}

// 0x1c56050
void itfPmvButtonGuideCtrl(s32 flg) {
  char *v8;
  char *v10;
  bool v11;
  char **v14;
  char *v17;

  if (!flg)
  {
    if (!Equals_54828784(msg_guide_name, "MSG001", 0))
    {
      if (!Equals_54828784(msg_guide_name, "MSG012", 0))
        return;
    }
    v8 = "";
LABEL_26:
    v10 = v8;
    v11 = 0;
    goto LABEL_29;
  }
  if (!itfIsPmvSkipAndPause())
  {
    itfSetGuide("", 0);
    v8 = "";
    goto LABEL_26;
  }
  if (scrCheckEnableMovieCancel())
  {
LABEL_38:
    v14 = &"MSG001";
    if (Equals_54828784(msg_guide_name, "MSG001", 0))
      return;
    goto LABEL_56;
  }
  if (is_Direction2)
    goto LABEL_38;
  v14 = &"MSG012";
  if (!Equals_54828784(msg_guide_name, "MSG012", 0))
  {
LABEL_56:
    itfSetGuide("", 0);
    v17 = *v14;
    v10 = v17;
    v11 = 1;
LABEL_29:
    SetGuideSub(17, v10, v11);
  }
}

// 0x1c564b0
bool itfIsPmvSkipAndPause(void) {
  if (logdispwk->pmvrun)
    goto LABEL_20;
  if (is_Direction2)
    goto LABEL_20;
  if (skpStopEnable != 1)
    return 0;
LABEL_20:
  if (dds3IsPMV_Fade())
    return 0;
  return PmvEventNo != 696;
}

// 0x1c56730
void itfPartVoiceLoad(void) {
  void *Asset;
  s64 naturalAligment;
  void *v22;
  Il2CppObject *current;
  s64 v25;
  System_Collections_Generic_List_Enumerator_T__o v27;

  memset(&v27, 0, sizeof(v27));
  object___Clear(partVoiceDic);
  int___Clear(flagVoiceDic);
  object___Clear(lblGuideDic);
  PartVoiceLoadSub("PartVoice");
  PartVoiceLoadSub("DVLTKMES_000");
  PartVoiceLoadSub("DVLTKMES_001");
  PartVoiceLoadSub("DVLTKMES_002");
  PartVoiceLoadSub("DVLTKMES_003");
  PartVoiceLoadSub("DVLTKMES_004");
  PartVoiceLoadSub("DVLTKMES_005");
  PartVoiceLoadSub("DVLTKMES_006");
  PartVoiceLoadSub("DVLTKMES_007");
  PartVoiceLoadSub("DVLTKMES_008");
  PartVoiceLoadSub("DVLTKMES_009");
  PartVoiceLoadSub("DVLTKMES_00A");
  PartVoiceLoadSub("DVLTKMES_00B");
  PartVoiceLoadSub("DVLTKMES_00C");
  PartVoiceLoadSub("DVLTKMES_00D");
  PartVoiceLoadSub("DVLTKMES_00E");
  PartVoiceLoadSub("DVLTKMES_010");
  Asset = LoadAsset(_Ctrl_k__BackingField, "common", "LabelGuideBtn", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == TextMsgData)
      v22 = Asset;
    else
      v22 = 0;
LABEL_12:
    if (!op_Inequality(v22, 0, 0))
      return;
    goto LABEL_21;
  }
  else
  {
    v22 = 0;
    goto LABEL_12;
  }
  if (!op_Inequality(v22, 0, 0))
    return;
LABEL_21:
  _GetEnumerator(&v27, v22[1].klass);
  while (_MoveNext(&v27))
  {
    current = v27._current;
    v25 = *(s64 *)((char *)&v27._current->klass + (u64)sub_10);
    if (v25 && *(s32 *)(v25 + 16) >= 1)
    {
      v25 = *(u64 *)((char *)sub_10 + (u64)current);
      object___Add(lblGuideDic, v25, *(Il2CppObject **)((char *)&off_18 + (u64)current));
    }
  }
  _Dispose(&v27);
}

// 0x1c56c80
static void PartVoiceLoadSub(char *asset_name) {
  void *Asset;
  s64 naturalAligment;
  void *v7;
  __int128 v9;
  Il2CppObject *current;
  Il2CppClass *klass;
  __int128 v14;
  Il2CppObject *v16;
  Il2CppClass *v17;
  System_Collections_Generic_List_Enumerator_T__o v19;
  System_Collections_Generic_List_Enumerator_T__o v20;

  memset(&v20, 0, sizeof(v20));
  Asset = LoadAsset(_Ctrl_k__BackingField, "common", asset_name, 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == PvTextMsgData)
      v7 = Asset;
    else
      v7 = 0;
LABEL_8:
    if (!op_Inequality(v7, 0, 0))
      return;
    goto LABEL_19;
  }
  else
  {
    v7 = 0;
    goto LABEL_8;
  }
  if (!op_Inequality(v7, 0, 0))
    return;
LABEL_19:
  _GetEnumerator(&v19, v7[1].klass);
  v20._current = v19._current;
  v9 = *(_OWORD *)&v19._list;
  v19._list = 0;
  *(u64 *)&v19._index = &v20;
  *(_OWORD *)&v20._list = v9;
  while (_MoveNext(&v20))
  {
    current = v20._current;
    klass = v20._current[1].klass;
    if (klass && SLODWORD(klass->_1.name) >= 1)
    {
      klass = current[1].klass;
      if (!object___ContainsKey(partVoiceDic, klass))
      {
        object___Add(partVoiceDic, current[1].klass, current[1].monitor);
      }
    }
  }
  _Dispose(&v20);
  _GetEnumerator(&v19, v7[1].klass);
  v14 = *(_OWORD *)&v19._list;
  v19._list = 0;
  *(u64 *)&v19._index = &v20;
  v20._current = v19._current;
  *(_OWORD *)&v20._list = v14;
  while (_MoveNext(&v20))
  {
    v16 = v20._current;
    v17 = v20._current[1].klass;
    if (v17 && SLODWORD(v17->_1.name) >= 1)
    {
      v17 = v16[1].klass;
      if (!int___ContainsKey(flagVoiceDic, v17))
      {
        int___Add(flagVoiceDic, v16[1].klass, (s32)v16[2].klass);
      }
    }
  }
  _Dispose(&v20);
}

// 0x1c57140
char *itfGetPartVoice(char *label_name) {
  bool IsNullOrEmpty;
  char *result;
  bool v6;
  Il2CppObject *value;

  value = 0;
  IsNullOrEmpty = IsNullOrEmpty(label_name, 0);
  result = 0;
  if (!IsNullOrEmpty)
  {
    v6 = object___TryGetValue(partVoiceDic, label_name, &value);
    result = value;
    if (v6)
    {
      if (op_Equality(value, "null", 0) || op_Equality(value, "NULL", 0))
      {
        return Empty;
      }
      else
      {
        return value;
      }
    }
  }
  return result;
}

// 0x1c57280
s32 itfGetPartVoiceFlag(char *label_name) {
  bool IsNullOrEmpty;
  s32 result;
  s32 value;

  value = 0;
  IsNullOrEmpty = IsNullOrEmpty(label_name, 0);
  result = 0;
  if (!IsNullOrEmpty)
  {
    int___TryGetValue(flagVoiceDic, label_name, &value);
    return value;
  }
  return result;
}

// 0x1c57330
void itfPartVoiceDevilSet(s32 devilid) {
  if (part_voice_devil == devilid)
    return;
  part_voice_devil = devilid;
}

// 0x1c57400
s32 itfPartVoiceDevilGet(void) {
  return part_voice_devil;
}

// 0x1c57480
static void SetGuideSub(s32 guide_idx, char *guide_name, bool disp) {
  Il2CppObject *v10;
  Il2CppObject *Item;
  char *v13;
  char **p_msg_guide_name;
  Il2CppObject *v16;
  char **v17;

  if (!disp)
  {
    Item = _get_Item(MsgWnd, guide_idx);
    SetActive(Item, 0, 0);
    ButtonTmpGuideObjClr();
    v13 = "";
    p_msg_guide_name = &msg_guide_name;
    *p_msg_guide_name = "";
    return;
  }
  if (!Equals_54828784(msg_guide_name, guide_name, 0))
  {
    v16 = _get_Item(MsgWnd, guide_idx);
    ButtonTmpGuideObjSet(v16, 0);
    ButtonTmpGuideDispSet(guide_name, 0, 90);
    v17 = &msg_guide_name;
    *v17 = guide_name;
  }
  v10 = _get_Item(MsgWnd, guide_idx);
  SetActive(v10, 1, 0);
  ButtonTmpGuideDispOn();
}

// 0x1c57730
void itfResetMsgGuideName(void) {
  char *v2;
  char **p_msg_guide_name;

  v2 = "";
  p_msg_guide_name = &msg_guide_name;
  *p_msg_guide_name = "";
}

// 0x1c55010
void itfSetGuide(char *guide_name, bool disp) {
  bool IsBattle;

  IsBattle = sbattleIsBattle();
  if (IsBattle)
  {
    if (battle_key_wait)
    {
      bk_msg_guide_name = guide_name;
      disp = 0;
      guide_name = "";
    }
  }
  SetGuideSub(3, guide_name, disp);
}

// 0x1c566c0
void itfSetGuidePMV(char *guide_name, bool disp) {
  SetGuideSub(17, guide_name, disp);
}

// 0x1c577b0
void itfSetGuideSkip(char *guide_name, bool disp) {
  Il2CppObject *Item;

  Item = _get_Item(MsgWnd, 21);
  if (get_activeSelf(Item, 0) != disp)
  {
    if (disp)
    {
      itfSetGuide("", 0);
    }
    SetGuideSub(21, guide_name, disp);
  }
}

// 0x1c578c0
bool itfIsDrawSelWnd(void) {
  return SelWndId != -1;
}

// 0x1c57930
void itfSetGuideAnimPMV(bool disp) {
  Il2CppObject *Item;

  Item = _get_Item(MsgWndAnm, 17);
  SetBool(Item, "anim", disp, 0);
}

// 0x1c579e0
char *itfGetGudeName(void) {
  return msg_guide_name;
}

// 0x1c57a60
void itfSetMesGuideLineAnimPMV(bool _bo) {
  Il2CppObject *Item;

  Item = _get_Item(MsgWndAnm, 20);
  SetBool(Item, "anim", bo, 0);
}

// 0x1c57b10
void itfMesGuideLineCtrl(bool _bo) {
  s32 v5;
  Il2CppObject *Item;

  if (meswin_type)
    v5 = 22;
  else
    v5 = 1;
  Item = _get_Item(MsgWndImg, v5);
  if (((Item->klass->vtable[9].methodPtr)(Item, Item->klass->vtable[9].method) & 1) != 0)
  {
    itfMsgWndSetActive(20, bo);
  }
}

// 0x1c57dc0
static void ChangeEvtGuideText(void) {
  s32 script_auto_skip;
  bool v6;
  char **v7;
  char *v8;
  bool v9;
  s32 ConfigAUDIO;

  if (SelWndId != -1)
    return;
  if (scrIsEventSkip(0))
    return;
  script_auto_skip = lipsync_pm->script_auto_skip;
  v6 = script_auto_skip == 0;
  if (script_auto_skip)
  {
    v7 = &"";
    v8 = "";
    v9 = 0;
LABEL_16:
    itfSetGuide(v8, v9);
    return;
  }
  if (!lipsync_pm->script_auto_skip)
  {
    ConfigAUDIO = cfgGetConfigAUDIO(7, 0);
    if (!ConfigAUDIO)
    {
      v7 = &"MSG004";
      goto LABEL_29;
    }
  }
  v7 = &"MSG005";
LABEL_29:
  v8 = *v7;
  v9 = 1;
  goto LABEL_16;
}

// 0x1c58020
char *itfGetLableGuideBtn(char *label_name) {
  bool IsNullOrEmpty;
  char *result;
  bool v6;
  Il2CppObject *value;

  value = 0;
  IsNullOrEmpty = IsNullOrEmpty(label_name, 0);
  result = 0;
  if (!IsNullOrEmpty)
  {
    v6 = object___TryGetValue(lblGuideDic, label_name, &value);
    result = value;
    if (v6)
    {
      if (op_Equality(value, "null", 0) || op_Equality(value, "NULL", 0))
      {
        return Empty;
      }
      else
      {
        return value;
      }
    }
  }
  return result;
}

// 0x1c58160
bool itfIsSpeakerText(FontReq_t *pFRQ) {
  char *v3;

  if (!pFRQ)
    return 0;
  v3 = sub_1C88420(pFRQ, 0);
  return !IsNullOrEmpty(v3, 0) && !op_Equality(v3, " ", 0);
}

// 0x1c584c0
static sdfDrawTag_t *dds3AllocDrawTag(void) {
  return 0;
}

// 0x1c584d0
static char *GetFRQString(FontReq_t *frq) {
  Text_t *str;

  Clear(frqstr);
  str = frq->str;
  if (!str)
    goto LABEL_7;
  goto LABEL_11;
  do
  {
LABEL_11:
    Append_56602736(frqstr, str->chcode, 0);
    str = str->next;
  }
  while (str);
LABEL_7:
  return ((char *(void *, const MethodInfo *))frqstr->klass->vtable._3_ToString.methodPtr)(frqstr, frqstr->klass->vtable._3_ToString.method);
}

// 0x1c585d0
bool itfIsCloseWindow(s32 id) {
  instanceMes_tag *pinst;

  pinst = g_manager->pmesflow[id]->pinst;
  return pinst && pinst->message->pfont != 0;
}

// 0x1c58670
static void DestructFlow(s32 id) {
  itfMiscLinkHeader_t *v5;
  itfMiscLinkHeader_t *v6;
  instanceMes_tag *klass;
  variable_tag *variable;
  s64 i;
  char *pptr;
  itfMiscLinkStack_t *linkstack;
  manager_tag *g_manager_local;
  void *selsave;
  s32 size;
  s32 v19;
  void *tagsave;
  s32 v21;
  s32 v22;
  void *Instance;

  v5 = g_manager->pmesflow[id];
  v6 = v5 + 1;
  klass = v5[1].klass;
  if (klass)
  {
    itfMesMngRequestMessageRelease(id, 1);
    itfMesMngRequestSelectRelease(id);
    ReleaseAllWindow(klass);
    variable = klass->variable;
    for (i = 32; i != 288; i += 8)
    {
      pptr = variable->pptr;
      if (*(Il2CppClass **)((char *)&pptr->obj.klass + i))
      {
        *(Il2CppClass **)((char *)&pptr->obj.klass + i) = 0;
      }
    }
    klass->stat = 0;
    v6->klass = 0;
    linkstack = g_manager->linkstack;
    itfMiscLinkGive(v5, linkstack);
    g_manager_local = g_manager;
    --g_manager_local->numuse;
    selsave = logdispwk->selsave;
    size = selsave->_size;
    v19 = selsave->_version + 1;
    selsave->_size = 0;
    selsave->_version = v19;
    if (size >= 1)
    {
      Clear(selsave->_items, 0, size, 0);
    }
    tagsave = logdispwk->tagsave;
    v21 = tagsave->_size;
    v22 = tagsave->_version + 1;
    tagsave->_size = 0;
    tagsave->_version = v22;
    if (v21 >= 1)
      Clear(tagsave->_items, 0, v21, 0);
    Instance = get_Instance(0);
    UnloadDevilVoiceSe(Instance, 0);
  }
}

// 0x1c58c60
static void ResolveResourceAddress(void *pdata) {

}

// 0x1c58ca0
static bool CheckMessageBinary(itfMesBinFileHeader_t *pdata) {
  return ((pdata->mgc - 809980749) & 0xFEFFFFFF) == 0;
}

// 0x1c58cc0
static itfMesBinTypeHeader_t *GetTypeHeader(instanceMes_tag *pinst, s32 index) {
  Il2CppObject *pdata;
  u8 *Interface;
  itfMesBinFileHeader_t *v7;
  itfMesBinTypeHeader_t *v8;
  s32 pos;

  pdata = pinst->pdata;
  pos = 0;
  else
  {
    Interface = 0;
  }
  v7 = Allocate(itfMesBinFileHeader_t);
  _ctor(v7, Interface, &pos, 0);
  pos += 8 * index;
  v8 = (itfMesBinTypeHeader_t *)Allocate(itfMesBinTypeHeader_t);
  _ctor(v8, Interface, &pos, 0);
  return v8;
}

// 0x1c58dc0
static itfMesBinTypeHeader2_t *GetTypeHeader2(u8 *pfileheader) {
  itfMesBinFileHeader_t *v3;
  itfMesBinTypeHeader2_t *v4;
  s32 pos;

  pos = 0;
  v3 = Allocate(itfMesBinFileHeader_t);
  _ctor(v3, pfileheader, &pos, 0);
  pos += 8 * v3->numtypeheader;
  v4 = (itfMesBinTypeHeader2_t *)Allocate(itfMesBinTypeHeader2_t);
  _ctor(v4, pfileheader, &pos, 0);
  return v4;
}

// 0x1c58e80
static u8 *GetMessagePagePtr(itfMesBinMesHeader_t *pmesheader, u8 *data, s32 page) {
  s64 v7;
  char *v8;
  s32 v9;
  s64 v10;
  void *v11;

  if (page < 0 || pmesheader->page <= page)
    return 0;
  v7 = page;
  v8 = (char *)pmesheader->len + v7 * 4;
  v9 = pmesheader->addr[v7];
  v10 = *((s32 *)v8 + 8);
  v11 = NewSpecific(byte, (s32)v10 + 1);
  Copy_56175392(data, v9, v11, 0, v10, 0);
  *((u8 *)&v11[2].klass + v10) = 0;
  return v11;
}

// 0x1c57c60
s32 itfGetPrefMesWin(void) {
  if (meswin_type)
    return 22;
  else
    return 1;
}

// 0x1c58f50
void itfSetPrefMesNom(void) {
  meswin_type = 0;
  return;
}

// 0x1c58fd0
void itfSetPrefMesCmn(void) {
  meswin_type = 1;
  return;
}

// 0x1c59060
s32 mesLine(void) {
  if (meswin_type)
    return 4;
  else
    return 3;
}

// 0x1c590d0
void itfWindowDispOn(s32 MsgID) {
  instanceMes_tag *pinst;
  s32 v7;

  pinst = g_manager->pmesflow[MsgID]->pinst;
  if (meswin_type)
    v7 = 22;
  else
    v7 = 1;
  itfMsgWndSetActive(v7, 0);
  WindowDispOn(pinst);
}

// 0x1c592c0
static void WindowDispOn(instanceMes_tag *pinst) {
  s32 v6;
  Il2CppObject *Item;
  s32 v10;

  if (get_activeSelf(MsgWndOwner, 0))
  {
    goto LABEL_5;
  }
  SetActive(MsgWndOwner, 1, 0);
LABEL_5:
  if (meswin_type)
    v6 = 22;
  else
    v6 = 1;
  Item = _get_Item(MsgWnd, v6);
  if (get_activeSelf(Item, 0))
    goto LABEL_60;
  if (meswin_type)
    v10 = 22;
  else
    v10 = 1;
  itfMsgWndSetActive(v10, 1);
  itfMsgWndSetActive(0, 0);
  itfMsgWndSetActive(3, 1);
  itfMsgWndSetActive(4, 1);
  if (logdispwk->pmvrun)
  {
    if (!ButtonGuideFlag)
      goto LABEL_51;
    itfMesGuideLineCtrl(1);
    goto LABEL_51;
  }
  itfMsgWndSetActive(20, 1);
LABEL_51:
  if (pinst->speaker->pfont)
  {
    SwitchSpeaker(0, 0);
  }
  goto LABEL_57;
LABEL_58:
  if (!op_Inequality(0, 0, 0))
    goto LABEL_60;
  goto LABEL_59;
LABEL_57:
  goto LABEL_58;
  if (op_Inequality(0, 0, 0))
LABEL_59:
    SetActive(0, 0, 0);
LABEL_60:
  if (!itfIsFadeOutAnimeMsgWin())
    return;
  FadeInWindow();
}

// 0x1c59df0
static void ClearMessage(void) {
  s32 Item;

  Item = (u32)_get_Item(MsgWnd, 1);
  v3 = sub_1C88520(Item, 1);
  ClearSpeaker();
}

// 0x1c59ea0
static void ClearSpeaker(void) {
  if (!op_Inequality(SpkWndTMP, 0, 0))
    return;
  (SpkWndTMP->klass->vtable._66_set_text.methodPtr)(SpkWndTMP, "", SpkWndTMP->klass->vtable._66_set_text.method);
}

// 0x1c591f0
static void WindowDispOff(bool sw) {
  s32 v5;

  if (meswin_type)
    v5 = 22;
  else
    v5 = 1;
  itfMsgWndSetActive(v5, 0);
}

// 0x1c59fd0
void itfMessageClrAll(void) {
  s32 v6;

  ClearMessage();
  ClearSpeaker();
  if (meswin_type)
    v6 = 22;
  else
    v6 = 1;
  itfMsgWndSetActive(v6, 0);
  if (!op_Inequality(0, 0, 0))
    return;
  goto LABEL_13;
  if (op_Inequality(0, 0, 0))
LABEL_13:
    SetActive(0, 0, 0);
}

// 0x1c5a180
static void SelectWindowDispOn(instanceMes_tag *pinst) {
  s32 id;
  s32 v7;
  Il2CppObject *Item;

  if (SelWndId != -1)
  {
    id = pinst->id;
    if (id != SelWndId)
      return;
  }
  v7 = pinst->id;
  SelWndId = v7;
  itfMsgWndSetActive(2, 1);
  Item = _get_Item(MsgWndAnm, 2);
  SetInteger(Item, "anim", 1, 0);
  itfMsgWndImgSetActive(2, 1);
}

// 0x1c5a440
s32 itfDebugWindowSwitch(s32 itfon) {
  char v2;
  Il2CppObject *Item;
  bool v6;
  s32 v8;
  s32 v9;
  Il2CppObject *v10;
  s32 v12;
  s32 v13;
  Il2CppObject *v14;
  bool activeSelf;
  s32 v18;
  s32 v20;
  s32 v21;
  s32 v26;

  v2 = itfon;
  Item = _get_Item(MsgWnd, MsgWndIndex);
  v6 = !get_activeSelf(Item, 0);
  if (v6)
    v8 = 0;
  else
    v8 = 2;
  v9 = MsgWndIndex + 1;
  v10 = _get_Item(MsgWnd, v9);
  v6 = !get_activeSelf(v10, 0);
  if (v6)
    v12 = 0;
  else
    v12 = 4;
  v13 = MsgWndIndex + 2;
  v14 = _get_Item(MsgWnd, v13);
  activeSelf = get_activeSelf(v14, 0);
  if ((v2 & 1) != 0)
  {
    SetActive(MsgWndOwner, 1, 0);
    if ((v2 & 2) == 0)
    {
      if ((v2 & 4) == 0)
        goto LABEL_34;
LABEL_56:
      itfMsgWndSetActive(MsgWndIndex + 1, 1);
      goto LABEL_35;
    }
    itfMsgWndSetActive(MsgWndIndex, 1);
    if ((v2 & 4) != 0)
      goto LABEL_56;
LABEL_34:
LABEL_35:
    itfMsgWndSetActive(MsgWndIndex + 2, (v2 & 8) != 0);
    v20 = v12 | v8;
    goto LABEL_36;
  }
  v18 = v8 | v12;
  v20 = v18 | 1;
  if (meswin_type)
    v21 = 22;
  else
    v21 = 1;
  itfMsgWndSetActive(v21, 0);
  SwitchSpeaker(0, 0);
  itfMsgWndSetActive(MsgWndIndex + 2, 0);
LABEL_36:
  if (activeSelf)
    v26 = 8;
  else
    v26 = 0;
  return v20 | v26;
}

// 0x1c5a890
static bool IsSelectWindowDispOn(void) {
  Il2CppObject *Item;
  Il2CppObject *Component_object;

  Item = _get_Item(MsgWnd, 2);
  Component_object = GetComponent_object_(Item);
  return get_alpha(Component_object, 0) >= 0.75;
}

// 0x1c5a950
static bool IsSelectWindowDispOff(void) {
  return 0;
}

// 0x1c5a960
static void SelectWindowDispOff(instanceMes_tag *pinst) {
  s32 id;
  Il2CppObject *Item;
  Il2CppObject *v7;

  id = pinst->id;
  if (id != SelWndId)
    return;
  Item = _get_Item(MsgWnd, 2);
  SetActive(Item, 0, 0);
  v7 = _get_Item(MsgWndAnm, 2);
  SetInteger(v7, "anim", 2, 0);
  SelWndId = -1;
}

// 0x1c59950
static void SwitchOK(bool sw) {
  if (!op_Inequality(0, 0, 0))
    return;
  goto LABEL_4;
  if (op_Inequality(0, 0, 0))
LABEL_4:
    SetActive(0, sw, 0);
}

// 0x1c5aab0
static void FadeOutWindow(void) {
  if (!op_Inequality(0, 0, 0))
  {
    itfSetAnimeMsgWin(0);
    itfMesGuideLineCtrl(0);
    if (itfIsPmvSkipAndPause())
      return;
    goto LABEL_13;
  }
  SetActive(0, 0, 0);
  itfSetAnimeMsgWin(0);
  itfMesGuideLineCtrl(0);
  if (itfIsPmvSkipAndPause())
    return;
LABEL_13:
  if (scrIsEventSkip(0))
    return;
  itfSetGuide("", 0);
}

// 0x1c59a00
static bool IsFadeOutWindow(void) {
  return itfIsFadeOutAnimeMsgWin();
}

// 0x1c59a70
static void FadeInWindow(void) {
  char v10;
  char *LableGuideBtn;

  if (!op_Inequality(0, 0, 0))
    goto LABEL_7;
  goto LABEL_6;
  if (op_Inequality(0, 0, 0))
LABEL_6:
    SetActive(0, 0, 0);
LABEL_7:
  itfSetAnimeMsgWin(1);
  itfMesGuideLineCtrl(1);
  if (logdispwk->pmvrun)
  {
    v10 = !ButtonGuideFlag;
LABEL_16:
    itfSetMesGuideLineAnimPMV(v10);
    goto LABEL_31;
  }
  LableGuideBtn = itfGetLableGuideBtn(lipsync_pm->tagid);
  if (!IsNullOrEmpty(LableGuideBtn, 0) && Equals_54828784(LableGuideBtn, "OFF", 0))
  {
    v10 = 1;
    goto LABEL_16;
  }
LABEL_31:
  if (!isMesWndBaseDisp)
    return;
  if (logdispwk->pmvrun)
    return;
  return;
}

// 0x1c5aed0
static void setGuideMsg(s32 type, Speaker_tag *pspeaker) {
  char *LableGuideBtn;
  char *voice_name;
  bool v12;
  bool v14;
  char *v15;
  FontReq_t *pfont;
  char *v21;
  char v22;
  FontReq_t *v25;

  LableGuideBtn = itfGetLableGuideBtn(lipsync_pm->tagid);
  if (!IsNullOrEmpty(LableGuideBtn, 0))
  {
    v12 = Equals_54828784(LableGuideBtn, "OFF", 0);
    if (v12)
    {
      v14 = 0;
      v15 = "";
    }
    else
    {
      v15 = LableGuideBtn;
      v14 = 1;
    }
    goto LABEL_22;
  }
  voice_name = lipsync_pm->voice_name;
  if (sndIsVoicePlayFile(voice_name))
    goto LABEL_11;
  if (type)
  {
    if (op_Equality(SpkWndTMP, 0, 0))
      goto LABEL_49;
    v21 = (SpkWndTMP->klass->vtable._65_get_text.methodPtr)(SpkWndTMP, SpkWndTMP->klass->vtable._65_get_text.method);
    if (IsNullOrEmpty(v21, 0))
    {
LABEL_49:
      v22 = 0;
      goto LABEL_50;
    }
  }
  else
  {
    if (!pspeaker)
      goto LABEL_49;
    pfont = pspeaker->pfont;
    if (!itfIsSpeakerText(pfont))
      goto LABEL_49;
  }
  v22 = 1;
LABEL_50:
  if (scrIsLogSave())
  {
    ChangeEvtGuideText();
    return;
  }
  if ((v22 & 1) == 0)
    goto LABEL_67;
  if (!pspeaker || (v25 = pspeaker->pfont) == 0)
  {
LABEL_70:
    v15 = "MSG000";
    v14 = 1;
    goto LABEL_22;
  }
  if (op_Equality(v25->tag_id, "<lmp_sys_LMP_SYS_TALK_SHIP_006>", 0))
    goto LABEL_67;
  goto LABEL_70;
LABEL_11:
  ChangeEvtGuideText();
  if (type)
    return;
  if (scrIsLogSave())
    return;
LABEL_67:
  v15 = "MSG003";
  v14 = 1;
LABEL_22:
  itfSetGuide(v15, v14);
  return;
}

// 0x1c5b3b0
static bool IsParticularTag(FontReq_t *pFQR) {
  return op_Equality(pFQR->tag_id, "<lmp_sys_LMP_SYS_TALK_SHIP_006>", 0);
}

// 0x1c59820
static void SwitchSpeaker(bool sw, bool disp) {
  Il2CppObject *Item;

  _get_Item(MsgWnd, 4);
  Item = _get_Item(MsgWnd, 4);
  if (!get_activeSelf(Item, 0))
  {
    itfMsgWndSetActive(4, 1);
  }
}

// 0x1c5b410
static void SetMessage(void *obj, s32 line, char *text) {
  Il2CppObject *Item;
  Il2CppObject *v8;
  void *v9;
  s32 mesPriority_local;

  Item = _get_Item(MsgWndTMP, line);
  v8 = _get_Item(MsgWndCnv, line);
  if (!text)
    return;
  v9 = v8;
  if (!op_Inequality(Item, 0, 0))
  {
    goto LABEL_9;
  }
  (Item->klass->vtable[66].methodPtr)(Item, text, Item->klass->vtable[66].method);
LABEL_9:
  if (op_Inequality(v9, 0, 0))
    goto LABEL_10;
  return;
  if (op_Inequality(v9, 0, 0))
  {
LABEL_10:
    set_overrideSorting(v9, 1, 0);
    if (fadeFrontDisp)
    {
      mesPriority_local = mesPriority;
      goto LABEL_21;
    }
    mesPriority_local = 20;
LABEL_21:
    set_sortingOrder(v9, mesPriority_local, 0);
  }
}

// 0x1c5b600
static void SetVar(instanceMes_tag *pinst, s32 index, char *pstr, s32 length) {
  variable_tag *variable;
  s64 v6;
  s64 v8;
  s64 v9;

  variable = pinst->variable;
  v6 = index;
  if (!IsNullOrEmpty(variable->pptr[index], 0))
  {
    v8 = (s64)variable->pptr + 8 * v6;
    *(u64 *)(v8 + 32) = 0;
  }
  v9 = (s64)variable->pptr + 8 * v6;
  *(u64 *)(v9 + 32) = pstr;
}

// 0x1c5b670
static void CommitVarTable(variable_tag *pvar) {
  void *v3;
  s64 i;
  u64 *v6;
  s32 v7;
  void *v8;

  v3 = Allocate(System_Collections_Generic_List_byte_);
  __ctor(v3);
  for (i = 32; i != 288; i += 8)
  {
    v7 = v3->_version + 1;
    v3->_size = 0;
    v3->_version = v7;
    if (IsNullOrEmpty(*(char **)((char *)&pvar->pptr->obj.klass + i), 0))
      continue;
    v8 = *(Il2CppClass **)((char *)&pvar->pptr->obj.klass + i);
    v6 = ((char *)&gVarStr->obj.klass + i);
    *v6 = v8;
  }
}

// 0x1c5b7c0
static u8 *GetSpeakerName(instanceMes_tag *pinst) {
  Il2CppObject *pdata;
  u8 *Interface;
  itfMesBinTypeHeader2_t *TypeHeader2;
  s32 v6;
  void *v7;
  u8 v8;
  s32 v9;
  char *v10;
  s64 size;
  u64 *v12;
  u8 *items;
  char *v14;
  u64 *v15;
  s64 v16;
  u8 *v17;

  pdata = pinst->pdata;
  else
  {
    Interface = 0;
  }
  TypeHeader2 = GetTypeHeader2(Interface);
  v6 = ToInt32(Interface, TypeHeader2->ppspkhead + 4 * pinst->speaker->num + 32, 0);
  v7 = Allocate(System_Collections_Generic_List_byte_);
  __ctor(v7);
  v8 = Interface[v6 + 32];
  if (v8)
  {
    v9 = v6 + 33;
    do
    {
      while (1)
      {
        size = v7->_size;
        v12 = Method_System_Collections_Generic_List_byte__Add__;
        ++v7->_version;
        items = v7->_items;
        if ((u32)size < LODWORD(items->max_length))
          break;
        _AddWithResize(v7, v8, *(const MethodInfo_2D54680 **)(*(u64 *)(v12[4] + 192) + 112));
        v10 = (char *)Interface + v9++;
        v8 = v10[32];
        if (!v8)
          goto LABEL_14;
      }
      v7->_size = size + 1;
      items[size] = v8;
      v14 = (char *)Interface + v9++;
      v8 = v14[32];
    }
    while (v8);
  }
LABEL_14:
  v15 = Method_System_Collections_Generic_List_byte__Add__;
  v16 = v7->_size;
  ++v7->_version;
  v17 = v7->_items;
  if ((u32)v16 >= LODWORD(v17->max_length))
  {
    _AddWithResize(v7, 0, *(const MethodInfo_2D54680 **)(*(u64 *)(v15[4] + 192) + 112));
  }
  else
  {
    v7->_size = v16 + 1;
    v17[v16] = 0;
  }
  return _ToArray(v7);
}

// 0x1c5b9e0
static s32 GetNumSelectItem(s32 allitem, u32 mask) {
  s32 v4;
  u32 v5;
  s32 v6;
  _BOOL4 v7;

  if (allitem < 1)
    return 0;
  if (allitem == 1)
    return (mask & 1) == 0;
  v4 = 0;
  v5 = allitem & 0xFFFFFFFE;
  do
  {
    v5 -= 2;
    v6 = ((mask & 1) == 0) + v4;
    v7 = ((mask >> 1) & 1) == 0;
    mask >>= 2;
    v4 = v7 + v6;
  }
  while (v5);
  if ((allitem & 1) != 0)
    return ((mask & 1) == 0) + v4;
  else
    return v4;
}

// 0x1c5ba60
static FontReq_t *GetFontHandleUnit(u8 *dat, u32 *ppstr, s32 *pplen, s32 num, u32 mask, s32 x, s32 y, u32 z) {
  s64 v11;
  void *v14;
  s32 v15;
  s32 v16;
  FontReq_t *v17;
  s32 *m_Items;
  u32 *v19;
  s32 v20;
  s32 v21;
  s64 v22;
  s64 v23;
  void *v24;
  u8 v25;
  Il2CppObject *tag_id;
  s64 v27;
  u64 *v28;
  s64 v29;
  s64 v30;
  FontReq_t *head;
  FontReq_t *prev;
  FontReq_t *v35;
  Text_t *i;
  s32 v40;
  s32 v43;

  LODWORD(v11) = num;
  v14 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v14);
  v15 = v14->_size;
  v16 = v14->_version + 1;
  v14->_size = 0;
  v14->_version = v16;
  if (v15 >= 1)
    Clear(v14->_items, 0, v15, 0);
  v40 = v11;
  if ((s32)v11 >= 1)
  {
    v43 = y;
    v17 = 0;
    v11 = (u32)v11;
    m_Items = pplen;
    v19 = ppstr;
    while (1)
    {
      v21 = *v19++;
      v20 = v21;
      v23 = *m_Items++;
      v22 = v23;
LABEL_12:
      v24 = NewSpecific(byte, (s32)v22 + 1);
      Copy_56175392(dat, v20, v24, 0, v22, 0);
      *((u8 *)&v24[2].klass + v22) = 0;
      if ((mask & 1) == 0)
      {
        v17 = itfMessageRequestExLocalize(x, v43, 0, 0, 0, v25, v24, v17, 1, 0, 0);
        tag_id = v17->tag_id;
        v43 += 8 * v17->y_size;
        v27 = v14->_size;
        v28 = Method_System_Collections_Generic_List_string__Add__;
        ++v14->_version;
        v29 = v14->_items;
        if ((u32)v27 >= *(u32 *)(v29 + 24))
        {
          _AddWithResize(v14, tag_id, *(const MethodInfo_2DFC660 **)(*(u64 *)(v28[4] + 192) + 112));
        }
        else
        {
          v30 = v29 + 8 * v27;
          v14->_size = v27 + 1;
          *(u64 *)(v30 + 32) = tag_id;
        }
      }
      mask >>= 1;
      if (!--v11)
        goto LABEL_20;
    }
    goto LABEL_12;
  }
  v17 = 0;
LABEL_20:
  scrNewLogSaveSelLabel(v14);
  head = v17->head;
  InitializeSelectWindow(v17->head, v40);
  prev = v17;
  do
  {
    prev->priority = z;
    prev = prev->prev;
  }
  while (prev);
  v35 = v17;
  do
  {
    for (i = v35->str; i; i = i->next)
      LOBYTE(i->color) = 0x80;
    v35 = v35->prev;
  }
  while (v35);
  return v17;
}

// 0x1c5be40
static void InitializeSelectWindow(FontReq_t *pFRQ, s32 max) {
  LOGDISP_PARAM *logdispwk_local;
  char *v22;
  s32 *selcnt;
  LOGDISP_PARAM *v26;
  s32 *v27;
  s64 i;
  s64 v30;
  LOGDISP_PARAM *v32;
  s32 *v33;
  il2cpp_array_size_t max_length;
  s32 *v35;
  s64 j;
  s32 v38;
  s64 v39;
  il2cpp_array_size_t v40;
  s64 v41;
  u32 v42;
  LOGDISP_PARAM *v43;
  s32 *v44;
  s64 v52;
  s64 v53;
  s64 v54;
  s32 MesWndSelectViewIndex;
  s32 v59;
  Il2CppObject *Item;
  Il2CppObject *v61;
  s64 v62;
  s64 v63;
  char *seltextsave;
  Il2CppClass *v65;
  Il2CppObject *v66;
  void *gameObject;
  Il2CppObject *Component_object;
  char *v70;

  itfMsgWndSetActive(5, 0);
  itfMsgWndSetActive(6, 0);
  itfMsgWndSetActive(7, 0);
  itfMsgWndSetActive(8, 0);
  itfMsgWndSetActive(9, 0);
  itfMsgWndSetActive(10, 0);
  itfMsgWndSetActive(18, 0);
  itfMsgWndSetActive(19, 0);
  InitMesWndSelect(max);
  logdispwk_local = logdispwk;
  v22 = NewSpecific(string, max);
  logdispwk_local->seltextsave = v22;
  selcnt = logdispwk->selcnt;
  if (LODWORD(selcnt->max_length) != 1)
    goto LABEL_15;
  if (selcnt[0])
  {
LABEL_15:
    v26 = logdispwk;
    v27 = NewSpecific(s32, v26->selcnt->max_length);
    v26->selcntsave = v27;
    for (i = 8; ; ++i)
    {
      v32 = logdispwk;
      v33 = v32->selcnt;
      max_length = v33->max_length;
      if (i - 8 >= (s32)max_length)
        break;
      v32 = logdispwk;
      v33 = v32->selcnt;
      v30 = 4 * i;
      *(u32 *)((char *)&v32->selcntsave->obj.klass + v30) = *(u32 *)((char *)&v33->obj.klass + v30);
    }
    v32 = logdispwk;
    max_length = v32->selcnt->max_length;
    v35 = NewSpecific(s32, (s32)max_length + 1);
    v32->selcnt = v35;
    for (j = 8; ; ++j)
    {
      v39 = j - 8;
      v43 = logdispwk;
      v44 = v43->selcnt;
      v40 = v44->max_length;
      if (j - 8 >= (s32)v40)
        goto LABEL_54;
      v41 = (u32)(v40 - 1);
      if (v39 == v41)
        goto LABEL_38;
      goto LABEL_9001;
      if (v39 == (u32)v44->max_length - 1)
      {
LABEL_38:
        v38 = max;
        v44 = logdispwk->selcnt;
        goto LABEL_30;
      }
LABEL_9001:
      if (!v42)
      {
        v43 = logdispwk;
        v44 = v43->selcnt;
      }
      v38 = *((u32 *)&v43->selcntsave->obj.klass + j);
LABEL_30:
      *((u32 *)&v44->obj.klass + j) = v38;
    }
  }
  selcnt = logdispwk->selcnt;
  selcnt[0] = max;
LABEL_54:
  if (max >= 1)
  {
    v52 = 0;
    v53 = max;
    v54 = 32;
    do
    {
      MesWndSelectViewIndex = GetMesWndSelectViewIndex(v52);
      if (LongSelect)
      {
        v59 = GetMesWndSelectViewIndex(v52) + 18;
      }
      else
      {
        v59 = MesWndSelectViewIndex + 5;
      }
      Item = _get_Item(MsgWndTMP, v59);
      v61 = _get_Item(MsgWndFocusTMP, v59);
      if (!op_Equality(Item, 0, 0))
      {
        v62 = sub_1C88420(pFRQ, 0);
        (Item->klass->vtable[66].methodPtr)(Item, v62, Item->klass->vtable[66].method);
        v63 = (Item->klass->vtable[65].methodPtr)(Item, Item->klass->vtable[65].method);
        (v61->klass->vtable[66].methodPtr)(v61, v63, v61->klass->vtable[66].method);
        seltextsave = logdispwk->seltextsave;
        v65 = (Item->klass->vtable[65].methodPtr)(Item, Item->klass->vtable[65].method);
        *(Il2CppClass **)((char *)&seltextsave->obj.klass + v54) = v65;
        v66 = _get_Item(MsgWndTMP, v59);
        gameObject = get_gameObject(v66, 0);
        Component_object = GetComponent_object_(gameObject);
        if (!!op_Inequality(Component_object, 0, 0))
        {
          v70 = (Item->klass->vtable[65].methodPtr)(Item, Item->klass->vtable[65].method);
          if (GetPreferredValues_60221776(Item, v70, 0).x > 1332.0)
            SetStartFlag(Component_object, 0);
        }
        ChangeSelection(v52, 0);
        pFRQ = pFRQ->next;
        itfMsgWndSetActive(v59, 1);
        if (!pFRQ)
          return;
      }
      ++v52;
      v54 += 8;
    }
    while (v53 != v52);
  }
}

// 0x1c5cbe0
static FontReq_t *UnchainFontHandleUnit(FontReq_t *pfont, s32 index, s32 lines) {
  s32 v7;
  s32 y;
  s32 v9;
  s32 v10;
  FontReq_t *prev;
  bool v13;
  FontReq_t *v15;
  FontReq_t *v16;
  FontReq_t *v17;
  FontReq_t *v19;
  FontReq_t *p_head;

  v7 = ~index;
  y = pfont->y;
  v9 = v7 + lines;
  if (v9 < 1)
  {
    v10 = pfont->y;
  }
  else
  {
    v10 = pfont->y;
    if (y == v10)
      goto LABEL_8;
LABEL_10:
    while (1)
    {
      v13 = v9-- < 2;
      y = v10;
      if (v13)
        break;
      v10 = pfont->y;
      if (y == v10)
      {
        while (1)
        {
LABEL_8:
          prev = pfont->prev;
          pfont->prev = 0;
          pfont->next = 0;
          pfont->head = pfont;
          frDestroyFontRequestAfter(pfont);
          if (!prev)
            return 0;
          v10 = prev->y;
          pfont = prev;
          if (y != v10)
            goto LABEL_10;
        }
      }
    }
  }
  v15 = pfont;
  while (1)
  {
    v16 = v15;
    v15 = v15->prev;
    if (!v15)
      break;
    if (v10 != v15->y)
    {
      do
      {
        v17 = v15->prev;
        v15->prev = 0;
        v15->next = 0;
        v15->head = v15;
        frDestroyFontRequestAfter(v15);
        v15 = v17;
      }
      while (v17);
      break;
    }
  }
  pfont->next = 0;
  v16->prev = 0;
  v19 = pfont;
  do
  {
    v19->head = v16;
    p_head = &v19->head;
    v19 = p_head[1];
  }
  while (v19);
  return pfont;
}

// 0x1c5cdd0
static void ChangeFontPosition(FontReq_t *pfont, s32 dist_x, s32 dist_y) {
  s32 v4;

  for (; pfont; pfont = pfont->prev)
  {
    v4 = pfont->y + dist_y;
    pfont->x += dist_x;
    pfont->y = v4;
  }
}

// 0x1c5c580
static void ChangeZBuffer(FontReq_t *pfont, u32 z) {
  for (; pfont; pfont = pfont->prev)
    pfont->priority = z;
}

// 0x1c5c7f0
static void ChangeSelection(s32 index, s32 onoff) {
  Il2CppObject *v5;
  s32 MesWndSelectViewIndex;
  s32 v10;
  Il2CppObject *Item;
  Il2CppObject *v13;
  Il2CppObject *v15;
  Il2CppObject *v17;
  char *v18;
  s32 v19;
  u32 v21;
  char *v22;
  Il2CppObject *v24;
  Il2CppObject *v26;
  s32 data;

  if (index == -1)
    return;
  data = index + 1;
  v5 = Box(s32, &data);
  Format("choice_answer{0:D2}", v5, 0);
  MesWndSelectViewIndex = GetMesWndSelectViewIndex(index);
  if (LongSelect)
  {
    v10 = GetMesWndSelectViewIndex(index) + 18;
  }
  else
  {
    v10 = MesWndSelectViewIndex + 5;
  }
  Item = _get_Item(MsgWnd, v10);
  if (!op_Inequality(Item, 0, 0))
  {
    goto LABEL_14;
  }
  v17 = _get_Item(MsgWndTMP, v10);
  _get_Item(MsgWndFocusTMP, v10);
  v18 = (v17->klass->vtable[65].methodPtr)(v17, v17->klass->vtable[65].method);
  v19 = IndexOf(v18, 0x3Eu, 0);
  if (v19 != -1)
    v18 = Substring_54838176(v18, v19 + 1, v18->_stringLength + ~v19, 0);
  if (onoff == 1)
    v21 = -1340161;
  else
    v21 = -1;
  v22 = itfRepColTag(v18, v21);
  (v17->klass->vtable[66].methodPtr)(v17, v22, v17->klass->vtable[66].method);
LABEL_14:
  v13 = _get_Item(MsgWndCur, v10);
  if (!!op_Inequality(v13, 0, 0))
  {
    v24 = _get_Item(MsgWndCur, v10);
    SetActive(v24, onoff == 1, 0);
  }
  v15 = _get_Item(MsgWndTMPObj, v10);
  if (!op_Inequality(v15, 0, 0))
    return;
  v26 = _get_Item(MsgWndTMPObj, v10);
  SetActive(v26, onoff == 0, 0);
}

// 0x1c5cdf0
static void ChangeFontColor(FontReq_t *pfont, s32 index, s32 lines, s32 color) {
  s32 y;
  s32 v6;
  s32 v7;
  bool v8;
  Text_t *i;

  y = pfont->y;
  v6 = ~index + lines;
  if (v6 < 1)
  {
    v7 = pfont->y;
  }
  else
  {
    do
    {
      while (1)
      {
        v7 = pfont->y;
        if (y != v7)
          break;
        pfont = pfont->prev;
        if (!pfont)
          return;
      }
      v8 = v6-- < 2;
      y = pfont->y;
    }
    while (!v8);
  }
  do
  {
    for (i = pfont->str; i; i = i->next)
      i->col_no = color;
    pfont = pfont->prev;
  }
  while (pfont && v7 == pfont->y);
}

// 0x1c5ce70
static void ChangeFontColorAll(FontReq_t *pfont, s32 color) {
  Text_t *i;

  for (; pfont; pfont = pfont->prev)
  {
    for (i = pfont->str; i; i = i->next)
      i->col_no = color;
  }
}

// 0x1c5c5a0
static void ChangeFontAlpha(FontReq_t *pfont, s32 alpha) {
  Text_t *i;

  for (; pfont; pfont = pfont->prev)
  {
    for (i = pfont->str; i; i = i->next)
      i->color = i->color & 0xFFFFFF00 | alpha;
  }
}

// 0x1c5cea0
static s32 GetMessageWidth(FontReq_t *pfont) {
  s32 v4;
  s32 y;
  s32 v6;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;

  if (!pfont)
    return 0;
  v4 = 0;
LABEL_6:
  y = pfont->y;
  v6 = 0;
  while (1)
  {
    v6 += pfont->w_pxls;
    pfont = pfont->prev;
    if (!pfont)
      break;
    if (y != pfont->y)
    {
      if (v4 <= v6)
        v4 = v6;
      goto LABEL_6;
    }
  }
  if (v4 <= v6)
    v4 = v6;
  return 16 * v4;
  while (1)
  {
    v10 += pfont->w_pxls;
    pfont = pfont->prev;
    if (!pfont)
      break;
    if (v9 != pfont->y)
    {
LABEL_25:
      if (v8 <= v10)
        v8 = v10;
      v9 = pfont->y;
      v10 = 0;
      while (1)
      {
        v10 += pfont->w_pxls;
        pfont = pfont->prev;
        if (!pfont)
          goto LABEL_29;
        if (v9 != pfont->y)
          goto LABEL_25;
      }
    }
  }
LABEL_29:
  if (v8 <= v10)
    v11 = v10;
  else
    v11 = v8;
  return 16 * v11;
}

// 0x1c5d010
static s32 GetMaskedIndex(s32 index, u32 mask) {
  if ((mask & 1) == 0 && --index < 0)
    return 0;
  if ((mask & 2) == 0 && --index < 0)
    return 1;
  if ((mask & 4) == 0 && --index < 0)
    return 2;
  if ((mask & 8) == 0 && --index < 0)
    return 3;
  if ((mask & 0x10) == 0 && --index < 0)
    return 4;
  if ((mask & 0x20) == 0 && --index < 0)
    return 5;
  if ((mask & 0x40) == 0 && --index < 0)
    return 6;
  if ((mask & 0x80) == 0 && --index < 0)
    return 7;
  if ((mask & 0x100) == 0 && --index < 0)
    return 8;
  if ((mask & 0x200) == 0 && --index < 0)
    return 9;
  if ((mask & 0x400) == 0 && --index < 0)
    return 10;
  if ((mask & 0x800) == 0 && --index < 0)
    return 11;
  if ((mask & 0x1000) == 0 && --index < 0)
    return 12;
  if ((mask & 0x2000) == 0 && --index < 0)
    return 13;
  if ((mask & 0x4000) == 0 && --index < 0)
    return 14;
  if ((mask & 0x8000) == 0 && --index < 0)
    return 15;
  if ((mask & 0x10000) == 0 && --index < 0)
    return 16;
  if ((mask & 0x20000) == 0 && --index < 0)
    return 17;
  if ((mask & 0x40000) == 0 && --index < 0)
    return 18;
  if ((mask & 0x80000) == 0 && --index < 0)
    return 19;
  if ((mask & 0x100000) == 0 && --index < 0)
    return 20;
  if ((mask & 0x200000) == 0 && --index < 0)
    return 21;
  if ((mask & 0x400000) == 0 && --index < 0)
    return 22;
  if ((mask & 0x800000) == 0 && --index < 0)
    return 23;
  if ((mask & 0x1000000) == 0 && --index < 0)
    return 24;
  if ((mask & 0x2000000) == 0 && --index < 0)
    return 25;
  if ((mask & 0x4000000) == 0 && --index < 0)
    return 26;
  if ((mask & 0x8000000) == 0 && --index < 0)
    return 27;
  if ((mask & 0x10000000) == 0 && --index < 0)
    return 28;
  if ((mask & 0x20000000) == 0 && --index < 0)
    return 29;
  if ((mask & 0x40000000) == 0 && --index < 0)
    return 30;
  if (index - 1 > -1 || (mask & 0x80000000) != 0)
    return 32;
  else
    return 31;
}

// 0x1c5d2a0
static void RaiseMessageSpeedMax(FontReq_t *pfont) {
  for (; pfont; pfont = pfont->prev)
  {
    if (!pfont->str->tp)
    {
      pfont->draw_spd = 0x80;
    }
  }
}

// 0x1c5d330
static void RaiseMessageSpeedMaxAll(FontReq_t *pfont) {
  if (pfont)
  {
    do
    {
      pfont->draw_spd = 0x80;
      pfont = pfont->prev;
    }
    while (pfont);
  }
}

// 0x1c5d3b0
static void OpenMessageWindow(instanceMes_tag *pinst) {
  window_tag *window;
  message_tag *message;
  itfpanel_t *p_mes;
  s32 v6;
  itfpanel_t *v7;
  sdfIVector2_t p_fields;
  s32 v10;
  s32 v12;
  s32 v13;
  s32 v15;
  s32 v16;
  s32 v18;
  itfpanel_t *mes;
  s32 v21;
  u32 z;
  itfpanel_t *v23;
  sdfIVector4_t *p_mes_color;
  s32 v26;
  s32 v28;
  s32 v30;
  s32 v33;
  s32 Item;
  sdfIVector4_t v35;
  sdfIVector4_t v36;
  sdfIVector4_t v37;
  sdfIVector4_t v38;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;

  window = pinst->window;
  message = pinst->message;
  p_mes = &window->mes;
  if (!window->mes)
  {
    if (pinst->type == 2)
      v6 = 8;
    else
      v6 = 6;
    v7 = itfPnlRegist2(v6);
    p_mes = v7;
  }
  p_fields = (sdfIVector2_t)&message->fields;
  Item = get_Item((sdfIVector2_t)&message->fields, 0, 0);
  *(u64 *)&v35.z = 0;
  *(u64 *)&v35.x = &window->mes_offset;
  v33 = get_Item(v35, 0);
  v10 = get_Item((sdfIVector2_t)&message->fields, 1, 0);
  *(u64 *)&v36.x = &window->mes_offset;
  *(u64 *)&v36.z = 1;
  v12 = get_Item(v36, 0);
  v13 = get_Item(p_fields, 0, 0);
  *(u64 *)&v37.x = &window->mes_offset;
  *(u64 *)&v37.z = 2;
  v15 = get_Item(v37, 0);
  v16 = get_Item(p_fields, 1, 0);
  *(u64 *)&v38.x = &window->mes_offset;
  *(u64 *)&v38.z = 3;
  v18 = get_Item(v38, 0);
  mes = window->mes;
  v21 = v18;
  z = pinst->z;
  itfPnlSetPosition(mes, v33 + Item, v12 + v10, v15 + v13, v21 + v16, z);
  v23 = window->mes;
  p_mes_color = &window->mes_color;
  *(u64 *)&v39.z = 0;
  *(u64 *)&v39.x = p_mes_color;
  v26 = get_Item(v39, 0);
  *(u64 *)&v40.x = p_mes_color;
  *(u64 *)&v40.z = 1;
  v28 = get_Item(v40, 0);
  *(u64 *)&v41.x = p_mes_color;
  *(u64 *)&v41.z = 2;
  v30 = get_Item(v41, 0);
  itfPnlSetColor(v23, v26, v28, v30, 0);
  WindowDispOn(pinst);
  pinst->stat = pinst->stat & 0xFFFFFCFF | 0x100;
}

// 0x1c5dd30
static void OpenCheckSpeakerWindow(instanceMes_tag *pinst) {
  Speaker_tag *speaker;
  window_tag *window;
  u32 stat;
  sdfIVector2_t p_fields;

  speaker = pinst->speaker;
  window = pinst->window;
  if (speaker->pfont)
  {
    stat = pinst->stat;
    if ((stat & 0x10000) == 0)
    {
      if (!window->spk)
      {
        p_fields = (sdfIVector2_t)&speaker->fields;
        get_Item(p_fields, 0, 0);
        get_Item(p_fields, 1, 0);
        get_Item(p_fields, 0, 0);
        get_Item(p_fields, 1, 0);
        stat = pinst->stat;
      }
      pinst->stat = stat & 0xFFFFCFFF | 0x1000;
      goto LABEL_13;
    }
  }
  if (!window->spk)
    return;
  pinst->stat |= 0x3000u;
LABEL_13:
  SwitchSpeaker(0, 0);
}

// 0x1c5dea0
static void InitializeSpeaker(Speaker_tag *pspeaker, bool defaultpos) {
  FontReq_t *p_pfont;

  if (defaultpos)
  {
    set_Item((sdfIVector2_t)&pspeaker->fields, 0, 4020, 0);
    set_Item((sdfIVector2_t)&pspeaker->fields, 1, 5832, 0);
  }
  pspeaker->pfont = 0;
  p_pfont = &pspeaker->pfont;
  *((u16 *)p_pfont + 4) = -1;
}

// 0x1c5df10
static void InitializeMessage(message_tag *pmessage, bool defaultpos) {
  FontReq_t *p_pfont;

  if (defaultpos)
  {
    set_Item((sdfIVector2_t)&pmessage->fields, 0, 4500, 0);
    set_Item((sdfIVector2_t)&pmessage->fields, 1, 6318, 0);
  }
  pmessage->pfont = 0;
  p_pfont = &pmessage->pfont;
  *((u32 *)p_pfont + 4) = 0;
  p_pfont[1] = (FontReq_t *)0x800000000000LL;
}

// 0x1c5df80
static void InitializeSelect(select_tag *pselect) {
  sdfIVector2_t p_fields;
  select_tag *v3;

  p_fields = (sdfIVector2_t)&pselect->fields;
  v3 = pselect;
  set_Item((sdfIVector2_t)&pselect->fields, 0, 5160, 0);
  set_Item(p_fields, 1, 7218, 0);
  v3->pfont = 0;
  v3 = ((char *)v3 + 24);
  LODWORD(v3->monitor) = 0;
  v3->pos.y = 0;
  LOWORD(v3->pfont) = -1;
  *(void **)((char *)&v3->monitor + 4) = 0xFFFFFFFF0000LL;
}

// 0x1c5dff0
static void InitializeWindow(window_tag *pwindow) {
  pwindow->spk = 0;
  pwindow->mes = 0;
  ResetWindowPara(pwindow, 0, 0);
}

// 0x1c5e260
static void InitializeVariable(variable_tag *pvariable) {
  char *pptr;
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
  char *v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  char *v24;
  char *v25;
  char *v26;
  char *v27;
  char *v28;
  char *v29;
  char *v30;
  char **v31;
  char **v32;
  char **v33;
  char *v34;

  pptr = pvariable->pptr;
  pptr[0] = 0;
  v4 = pvariable->pptr;
  v4[1] = 0;
  v5 = pvariable->pptr;
  v5[2] = 0;
  v6 = pvariable->pptr;
  v6[3] = 0;
  v7 = pvariable->pptr;
  v7[4] = 0;
  v8 = pvariable->pptr;
  v8[5] = 0;
  v9 = pvariable->pptr;
  v9[6] = 0;
  v10 = pvariable->pptr;
  v10[7] = 0;
  v11 = pvariable->pptr;
  v11[8] = 0;
  v12 = pvariable->pptr;
  v12[9] = 0;
  v13 = pvariable->pptr;
  v13[10] = 0;
  v14 = pvariable->pptr;
  v14[11] = 0;
  v15 = pvariable->pptr;
  v15[12] = 0;
  v16 = pvariable->pptr;
  v16[13] = 0;
  v17 = pvariable->pptr;
  v17[14] = 0;
  v18 = pvariable->pptr;
  v18[15] = 0;
  v19 = pvariable->pptr;
  v19[16] = 0;
  v20 = pvariable->pptr;
  v20[17] = 0;
  v21 = pvariable->pptr;
  v21[18] = 0;
  v22 = pvariable->pptr;
  v22[19] = 0;
  v23 = pvariable->pptr;
  v23[20] = 0;
  v24 = pvariable->pptr;
  v24[21] = 0;
  v25 = pvariable->pptr;
  v25[22] = 0;
  v26 = pvariable->pptr;
  v26[23] = 0;
  v27 = pvariable->pptr;
  v27[24] = 0;
  v28 = pvariable->pptr;
  v28[25] = 0;
  v29 = pvariable->pptr;
  v29[26] = 0;
  v30 = pvariable->pptr;
  v30[27] = 0;
  v31 = &pvariable->pptr[28];
  *v31 = 0;
  v32 = &pvariable->pptr[29];
  *v32 = 0;
  v33 = &pvariable->pptr[30];
  *v33 = 0;
  v34 = pvariable->pptr;
  v34[31] = 0;
}

// 0x1c5e490
static void InitializeCurCtr(curctr_tag *pcurctr, s32 isdisp) {
  if (!isdisp)
  {
    pcurctr->isdraw = 0;
    *(u32 *)&pcurctr->lf_wait = 0;
  }
  pcurctr->cut_wait = 0;
  pcurctr->ctr_key = 0;
  *(u64 *)&pcurctr->phase = 0x8000000000LL;
}

// 0x1c5e4d0
static void ForceSetCurCtr(curctr_tag *pcurctr, s16 phase, s16 ctr0, s16 ctr1) {
  pcurctr->phase = phase;
  pcurctr->ctr0 = ctr0;
  pcurctr->ctr1 = ctr1;
}

// 0x1c58b00
static void ReleaseAllWindow(instanceMes_tag *pinst) {
  window_tag *window;
  window_tag *p_fields;
  itfpanel_t *spk;
  itfpanel_t *v6;
  itfPanelTypeWork_t *pwork;
  itfpanel_t *p_mes;
  itfpanel_t *v9;
  itfpanel_t *mes;
  itfpanel_t *v11;
  itfPanelTypeWork_t *v12;

  window = pinst->window;
  p_fields = &window->fields;
  spk = window->spk;
  if (spk)
  {
    pwork = spk->pwork;
    v6 = &spk->fields;
    if (!pwork)
    {
LABEL_7:
      p_fields->spk = 0;
      goto LABEL_8;
    }
    v6->pwork = 0;
    goto LABEL_7;
  }
LABEL_8:
  mes = window->mes;
  p_mes = &window->mes;
  v9 = mes;
  if (mes)
  {
    v12 = v9->pwork;
    v11 = &v9->fields;
    if (!v12)
    {
LABEL_12:
      p_mes = 0;
      goto LABEL_13;
    }
    v11->pwork = 0;
    goto LABEL_12;
  }
LABEL_13:
  pinst->stat &= 0xFFFFF0FF;
}

// 0x1c58c00
static void ReleaseAllVariable(variable_tag *pvariable) {
  s64 i;
  char *pptr;

  for (i = 32; i != 288; i += 8)
  {
    pptr = pvariable->pptr;
    if (*(Il2CppClass **)((char *)&pptr->obj.klass + i))
    {
      *(Il2CppClass **)((char *)&pptr->obj.klass + i) = 0;
    }
  }
}

// 0x1c5e500
static void ConvertZenkakuNumber(char **buf, s32 num) {
  s32 *v5;
  u64 v6;
  s64 v7;
  s64 v8;
  bool v9;
  s64 v10;
  char *v11;
  char *v12;
  char *v13;

  v5 = NewSpecific(s32, 0xAu);
  v6 = 0;
  v7 = 4;
  do
  {
    v8 = v7;
    v5[v6] = num % 10;
    if (v6 > 8)
      break;
    v9 = num <= 9;
    ++v6;
    v7 += 4;
    num /= 0xAu;
  }
  while (!v9);
  v10 = (s64)(char *)v5 + 28;
  do
  {
    v11 = *buf;
    v12 = Substring_54838176("０１２３４５６７８９", *(u32 *)(v10 + v8), 1, 0);
    v13 = Concat_54766928(v11, v12, 0);
    *buf = v13;
    v8 -= 4;
  }
  while (v8);
}

// 0x1c5e080
static void ResetWindowPara(window_tag *pwin, s32 type, s32 alpha) {
  sdfIVector4_t *p_mes_offset;
  s32 v12;
  sdfIVector4_t *p_mes_color;
  s32 v22;
  sdfIVector4_t v23;
  sdfIVector4_t v24;
  sdfIVector4_t v25;
  sdfIVector4_t v26;
  sdfIVector4_t v27;
  sdfIVector4_t v28;
  sdfIVector4_t v29;
  sdfIVector4_t v30;
  sdfIVector4_t v31;
  sdfIVector4_t v32;
  sdfIVector4_t v33;
  sdfIVector4_t v34;
  sdfIVector4_t v35;
  sdfIVector4_t v36;

  if (type == 1)
  {
    p_mes_offset = &pwin->mes_offset;
    *(u64 *)&v26.x = &pwin->mes_offset;
    *(u64 *)&v26.z = 0;
    set_Item(v26, -28496, 0);
    *(u64 *)&v27.x = &pwin->mes_offset;
    *(u64 *)&v27.z = 1;
    set_Item(v27, -1704, 0);
    *(u64 *)&v28.x = &pwin->mes_offset;
    *(u64 *)&v28.z = 2;
    set_Item(v28, 42416, 0);
    v12 = 3040;
  }
  else if (type == 2)
  {
    p_mes_offset = &pwin->mes_offset;
    *(u64 *)&v23.x = &pwin->mes_offset;
    *(u64 *)&v23.z = 0;
    set_Item(v23, -18768, 0);
    *(u64 *)&v24.x = &pwin->mes_offset;
    *(u64 *)&v24.z = 1;
    set_Item(v24, -1168, 0);
    *(u64 *)&v25.x = &pwin->mes_offset;
    *(u64 *)&v25.z = 2;
    set_Item(v25, 40496, 0);
    v12 = 2336;
  }
  else
  {
    p_mes_offset = &pwin->mes_offset;
    *(u64 *)&v29.x = &pwin->mes_offset;
    *(u64 *)&v29.z = 0;
    set_Item(v29, -18768, 0);
    *(u64 *)&v30.x = &pwin->mes_offset;
    *(u64 *)&v30.z = 1;
    set_Item(v30, -2208, 0);
    *(u64 *)&v31.x = &pwin->mes_offset;
    *(u64 *)&v31.z = 2;
    set_Item(v31, 40496, 0);
    v12 = 3200;
  }
  *(u64 *)&v32.x = p_mes_offset;
  *(u64 *)&v32.z = 3;
  set_Item(v32, v12, 0);
  p_mes_color = &pwin->mes_color;
  *(u64 *)&v33.z = 0;
  *(u64 *)&v33.x = p_mes_color;
  set_Item(v33, 128, 0);
  *(u64 *)&v34.x = p_mes_color;
  *(u64 *)&v34.z = 1;
  set_Item(v34, 128, 0);
  *(u64 *)&v35.x = p_mes_color;
  *(u64 *)&v35.z = 2;
  set_Item(v35, 128, 0);
  *(u64 *)&v36.x = p_mes_color;
  if (alpha >= 1)
    v22 = 2 * alpha;
  else
    v22 = 256;
  *(u64 *)&v36.z = 3;
  set_Item(v36, v22, 0);
}

// 0x1c5e630
static void CalcMesFlow(instanceMes_tag *pinst) {
  curctr_tag *curctr;
  s32 ctr1;
  s32 v7;
  s32 v8;

  CalcWindow(pinst);
  CalcMessage(pinst);
  CalcSelect(pinst);
  curctr = pinst->curctr;
  if (curctr->isdraw)
  {
    ctr1 = curctr->ctr1;
    if (ctr1 >= 1)
      curctr->ctr1 = ctr1 - 8;
    if (curctr->phase == 1)
    {
      v8 = (s16)(curctr->ctr0 - 8);
      curctr->ctr0 -= 8;
      if (v8 <= 0)
        *(u32 *)&curctr->phase = 0;
    }
    else if (!curctr->phase)
    {
      v7 = (u16)curctr->ctr0 + 8;
      curctr->ctr0 = v7;
      if (v7 << 16 >= 16711680)
      {
        *(u32 *)&curctr->phase = 16711681;
        curctr->ctr1 = 128;
      }
    }
  }
}

// 0x1c5e730
static void CalcWindow(instanceMes_tag *pinst) {
  itfpanel_t *v3;
  window_tag *window;
  itfpanel_t *mes;
  sdfIVector4_t *p_color;
  s32 v9;
  sdfIVector4_t *v14;
  s32 v15;
  s32 Item;
  s32 v23;
  s32 v29;
  u32 stat;
  sdfIVector4_t v32;
  sdfIVector4_t v33;
  sdfIVector4_t v34;
  sdfIVector4_t v35;
  sdfIVector4_t v36;
  sdfIVector4_t v37;
  sdfIVector4_t v38;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;
  sdfIVector4_t v42;
  sdfIVector4_t v43;

  v3 = Allocate(itfpanel_t);
  _ctor(v3, 0);
  window = pinst->window;
  mes = window->mes;
  if ((pinst->stat & 0x300) != 0x300)
  {
    if ((pinst->stat & 0x300) != 0x100)
      goto LABEL_23;
    p_color = &mes->color;
    *(u64 *)&v32.z = 3;
    *(u64 *)&v32.x = &mes->color;
    v9 = get_Item(v32, 0) + 24;
    *(u64 *)&v33.x = p_color;
    *(u64 *)&v33.z = 3;
    set_Item(v33, v9, 0);
    if (!scrIsEventSkip(0))
    {
      goto LABEL_8;
    }
    *(u64 *)&v37.x = &window->mes_color;
    *(u64 *)&v37.z = 3;
    Item = get_Item(v37, 0);
    *(u64 *)&v38.x = p_color;
    *(u64 *)&v38.z = 3;
    set_Item(v38, Item, 0);
LABEL_8:
    if (itfGetMesWinAlpha() < 1.0)
      goto LABEL_23;
    *(u64 *)&v39.x = &window->mes_color;
    *(u64 *)&v39.z = 3;
    v23 = get_Item(v39, 0);
    *(u64 *)&v40.x = p_color;
    *(u64 *)&v40.z = 3;
    set_Item(v40, v23, 0);
    pinst->stat = pinst->stat & 0xFFFFFCF8 | 0x203;
    goto LABEL_23;
  }
  v14 = &mes->color;
  *(u64 *)&v34.z = 3;
  *(u64 *)&v34.x = &mes->color;
  v15 = get_Item(v34, 0) - 10;
  *(u64 *)&v35.x = v14;
  *(u64 *)&v35.z = 3;
  set_Item(v35, v15, 0);
  if (!!scrIsEventSkip(0))
  {
    *(u64 *)&v41.x = v14;
    *(u64 *)&v41.z = 3;
    set_Item(v41, 0, 0);
    *(u64 *)&v42.x = v14;
    *(u64 *)&v42.z = 3;
    if (get_Item(v42, 0) > 0)
      goto LABEL_23;
    goto LABEL_20;
  }
  *(u64 *)&v36.x = v14;
  *(u64 *)&v36.z = 3;
  if (get_Item(v36, 0) > 0)
    goto LABEL_23;
LABEL_20:
  *(u64 *)&v43.x = v14;
  *(u64 *)&v43.z = 3;
  set_Item(v43, 0, 0);
  pinst->stat &= 0xFFFFFCFF;
  ClearMessage();
LABEL_23:
  if (meswin_type)
    v29 = 22;
  else
    v29 = 1;
  itfMsgWndImgSetActive(v29, isMesWndBaseDisp);
  itfMsgWndImgSetActive(4, isMesWndBaseDisp);
  stat = pinst->stat;
  if ((stat & 0x3000) == 0x3000)
  {
    window->spk = 0;
    pinst->stat = stat & 0xFFFFCFFF;
  }
  else if ((stat & 0x3000) == 0x1000)
  {
    pinst->stat = stat & 0xFFFFCFFF | 0x2000;
  }
}

// 0x1c5f7d0
static char *GetTagID(instanceMes_tag *pinst) {
  char *result;
  message_tag *message;
  FontReq_t *pfont;

  result = "";
  message = pinst->message;
  if (message)
  {
    pfont = message->pfont;
    if (pfont)
      return pfont->tag_id;
  }
  return result;
}

// 0x1c5ea90
static void CalcMessage(instanceMes_tag *pinst) {
  message_tag *message;
  u32 v4;
  char *tag_id;
  message_tag *v6;
  FontReq_t *pfont;
  curctr_tag *v8;
  u32 ctr_key;
  s32 lf_wait;
  s32 v15;
  Il2CppObject *Item;
  char *v17;
  char *v18;
  LOGDISP_PARAM *logdispwk_local;
  char *voice_name;
  char *seltext;
  char *mestextsave;
  void *p_tagsave;
  void *p_selsave;
  bool *add_flag;
  char *v28;
  message_tag *v29;
  FontReq_t *v30;
  bool IsEventSkip;
  curctr_tag *curctr;
  bool v36;
  curctr_tag *v37;
  u16 lf_after_wait;
  u16 v41;
  char *v42;
  char *v44;
  LOGDISP_PARAM *v45;
  curctr_tag *v47;
  s16 page;
  void *pageUpdateCallBack;
  variable_tag *variable;
  Speaker_tag *speaker;
  s32 cut_wait;
  FontReq_t *v64;
  FontReq_t *v65;
  message_tag *v69;
  u32 v70;

  message = pinst->message;
  if (message->phase != 1)
    return;
  v4 = pinst->stat & 7;
  if (!pinst->save_stat)
    goto LABEL_29;
  tag_id = "";
  v6 = pinst->message;
  if (v6)
  {
    pfont = v6->pfont;
    if (pfont)
      tag_id = pfont->tag_id;
  }
  if (Equals_54828784(tag_id, pinst->save_tag, 0))
  {
    if (pinst->save_stat)
    {
      if (v4 == 4)
        goto LABEL_16;
LABEL_43:
      IsEventSkip = scrIsEventSkip(0);
      curctr = pinst->curctr;
      if (IsEventSkip)
      {
        curctr->cut_wait = 8;
        goto LABEL_83;
      }
      cut_wait = curctr->cut_wait;
      if (cut_wait <= 7)
      {
        curctr->cut_wait = cut_wait + 1;
        if (cut_wait != 7)
          return;
      }
LABEL_83:
      if (!itfIsMesKey(4096, 2))
      {
        if (!itfIsMesKey(4097, 2))
          return;
      }
      if ((pinst->stat & 0x1400000) == 0)
      {
        v64 = message->pfont;
        RaiseMessageSpeedMaxAll(v64);
        v65 = pinst->speaker->pfont;
        if (v65)
        {
          v65->draw_spd = 0x80;
        }
      }
      return;
    }
  }
  else
  {
    pinst->save_stat = 0;
  }
LABEL_29:
  v70 = v4;
  v69 = message;
  if (meswin_type)
    v15 = 22;
  else
    v15 = 1;
  Item = _get_Item(MsgWndTMP, v15);
  v17 = (Item->klass->vtable[65].methodPtr)(Item, Item->klass->vtable[65].method);
  v18 = (SpkWndTMP->klass->vtable._65_get_text.methodPtr)(SpkWndTMP, SpkWndTMP->klass->vtable._65_get_text.method);
  logdispwk_local = logdispwk;
  voice_name = lipsync_pm->voice_name;
  seltext = logdispwk_local->seltext;
  mestextsave = logdispwk_local->mestextsave;
  p_tagsave = &logdispwk_local->tagsave;
  p_selsave = &logdispwk_local->selsave;
  add_flag = &logdispwk_local->selflag;
  scrLogSave(v17, v18, voice_name, p_tagsave, pinst, p_selsave, seltext, mestextsave, add_flag);
  message = v69;
  v28 = "";
  v29 = pinst->message;
  if (v29)
  {
    v30 = v29->pfont;
    if (v30)
      v28 = v30->tag_id;
  }
  pinst->save_tag = v28;
  pinst->save_stat = 1;
  if (v70 != 4)
    goto LABEL_43;
LABEL_16:
  if (fclChkSignal(7) == 1 && message->page + 1 >= message->maxpage)
  {
    fclClearSignal(7);
  }
  v8 = pinst->curctr;
  ctr_key = v8->ctr_key;
  if (ctr_key <= 0x63)
  {
    v8->ctr_key = ctr_key + 1;
    lf_wait = v8->lf_wait;
    if (lf_wait > 6)
    {
LABEL_25:
      goto LABEL_26;
    }
  }
  else
  {
    lf_wait = v8->lf_wait;
    if (lf_wait > 6)
      goto LABEL_25;
  }
  v8->lf_wait = lf_wait + 1;
LABEL_26:
  itfLipSyncCalc();
  if (IsMsgLogStart())
    return;
  if ((pinst->stat & 0x800000) != 0)
    goto LABEL_97;
  v36 = scrIsEventSkip(0);
  v37 = pinst->curctr;
  if (!v36 <= v37->lf_wait)
  {
    if ((pinst->stat & 0x100000) == 0)
      v37->isdraw = 1;
    lf_after_wait = v37->lf_after_wait;
    if (!lf_after_wait && message->wait)
    {
      if (scrIsEventSkip(0))
        goto LABEL_126;
      if (itfLipSyncEndCheck() || MesEnd())
        goto LABEL_126;
      if (itfIsMesKey(4096, 2) && pinst->curctr->lf_wait >= 7)
      {
LABEL_126:
        if (message->wait)
        {
          if (!scrIsEventSkip(0))
          {
            if (!IsAutoFeed())
              SE(9);
          }
          sndVoiceStop(0);
        }
        pinst->curctr->lf_after_wait = 1;
      }
      return;
    }
    v37 = pinst->curctr;
    lf_after_wait = v37->lf_after_wait;
    v41 = lf_after_wait + 1;
    v37->lf_after_wait = v41;
    bVoicePlaySw = 0;
    bNowSpeaking = 2;
    if (v41 > 5u || !message->wait)
    {
      if (!sndVoiceStatus(0))
      {
        v42 = "";
        pinst->save_tag = "";
        pinst->save_stat = 0;
        v44 = "";
        v45 = logdispwk;
        v45->seltext = "";
        itfLipSyncEnd();
        v47 = pinst->curctr;
        v47->isdraw = 0;
        *(u32 *)&v47->lf_wait = 0;
        v47->cut_wait = 0;
        v47->ctr_key = 0;
        *(u64 *)&v47->phase = 0x8000000000LL;
        SwitchOK(0);
        page = message->page + 1;
        pageUpdateCallBack = pinst->pageUpdateCallBack;
        message->page = page;
        if (pageUpdateCallBack)
        {
          (pageUpdateCallBack->invoke_impl)(pageUpdateCallBack->method_code, message, pageUpdateCallBack->method);
          page = message->page;
        }
        if (message->maxpage > page)
        {
          variable = pinst->variable;
          CommitVarTable(variable);
          ReadytoMessage(pinst, 0);
          CallEventVoice(pinst);
          if (!itfIsPmvRun())
          {
            speaker = pinst->speaker;
            setGuideMsg(0, speaker);
          }
          OpenCheckSpeakerWindow(pinst);
          pinst->stat = pinst->stat & 0xFFFFFFF8 | 3;
          return;
        }
LABEL_97:
        message->phase = -1;
      }
    }
  }
}

// 0x1c60de0
s32 itfMesMngMessage(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  return itfMesMngMessageSub(IntPara);
}

// 0x1c60e80
s32 itfMesMngMessageSub(s32 mes) {
  s32 MessageHandle;
  u32 v6;
  message_tag *message;

  scrEventSkipMsg1st();
  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v6 = MessageHandle;
  message = g_manager->pmesflow[v6]->pinst->message;
  if (message->phase)
  {
    if (message->phase < 0)
    {
      message->phase = 0;
      return 1;
    }
  }
  else
  {
    if (!itfMesMngRequestMessage(v6, mes, 0, 1, 0))
      return 1;
  }
  return 0;
}

// 0x1c61740
void itfMesMngSetOffsetY1(s32 msgid, s32 y1) {
  itfPnlSetPositionOffset(g_manager->pmesflow[msgid]->pinst->window->mes, 0, y1, 0, 0, 0);
}

// 0x1c61d30
s32 itfMesMngGetPhase(s32 msgid) {
  return g_manager->pmesflow[msgid]->pinst->message->phase;
}

// 0x1c61db0
void itfMesMngSetPhase(s32 msgid, s32 phase) {
  s8 v3;

  v3 = phase;
  g_manager->pmesflow[msgid]->pinst->message->phase = v3;
}

// 0x1c623b0
s32 itfMesMngSelect(void) {
  return MesMngSelect(0xFFFF, 0);
}

// 0x1c61ee0
s32 MesMngSelect(s16 cancelNum, bool longSel) {
  bool v4;
  s32 v7;
  s32 MessageHandle;
  u32 v9;
  instanceMes_tag *pinst;
  s32 IntPara;
  s16 *select;
  s32 v15;
  s32 v16;
  bool v20;
  LOGDISP_PARAM *logdispwk_local;
  char *seltextsave;
  char **p_seltext;
  char *v26;
  char *seltext;
  u32 v28;
  char *v29;
  char *v30;
  char *v31;
  s64 i;
  char **v34;
  char *v35;
  char *v36;
  u32 v37;
  char *v38;
  char *v39;
  u32 v40;
  char *v41;
  LOGDISP_PARAM *v42;
  char *v43;
  LOGDISP_PARAM *v44;
  char *v45;
  void *selsave;
  char **p_mestextsave;
  bool *p_selflag;

  v4 = longSel;
  LongSelect = v4;
  v7 = 1;
  scrEventSkipEnd(1, 0);
  scrEventSkipRestartFlagChange();
  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return v7;
  v9 = MessageHandle;
  pinst = g_manager->pmesflow[v9]->pinst;
  IntPara = scrGetIntPara(0);
  select = pinst->select;
  v15 = select[18];
  if (select[18])
  {
    if ((v15 & 0x80000000) == 0)
      return 0;
    select[18] = 0;
    v20 = op_Equality(logdispwk->seltext, "", 0);
    logdispwk_local = logdispwk;
    seltextsave = logdispwk_local->seltextsave;
    if (SLODWORD(seltextsave->max_length) >= 1)
    {
      if (select[19])
      {
        logdispwk_local = logdispwk;
        seltextsave = logdispwk_local->seltextsave;
        seltext = logdispwk_local->seltext;
        p_seltext = &logdispwk_local->seltext;
        v26 = seltext;
        v28 = -1448498689;
      }
      else
      {
        logdispwk_local = logdispwk;
        seltextsave = logdispwk_local->seltextsave;
        v29 = logdispwk_local->seltext;
        p_seltext = &logdispwk_local->seltext;
        v26 = v29;
        v28 = -1;
      }
      v30 = itfRepColTag(seltextsave[0], v28);
      v31 = Concat_54766928(v26, v30, 0);
      *p_seltext = v31;
      for (i = 5; ; ++i)
      {
        v42 = logdispwk;
        v43 = v42->seltextsave;
        if (i - 4 >= SLODWORD(v43->max_length))
          break;
        if (i - 4 == select[19])
        {
          if (!v40)
          {
            v42 = logdispwk;
            v43 = v42->seltextsave;
          }
          v41 = v42->seltext;
          v34 = &v42->seltext;
          v35 = v41;
          v37 = -1;
        }
        else
        {
          if (!v40)
          {
            v42 = logdispwk;
            v43 = v42->seltextsave;
          }
          v36 = v42->seltext;
          v34 = &v42->seltext;
          v35 = v36;
          v37 = -1448498689;
        }
        v38 = itfRepColTag(*((char **)&v43->obj.klass + i), v37);
        v39 = Concat_54831728(v35, "\n", v38, 0);
        *v34 = v39;
      }
    }
    v44 = logdispwk;
    v45 = v44->seltext;
    selsave = v44->selsave;
    p_mestextsave = &v44->mestextsave;
    p_selflag = &v44->selflag;
    scrLogSaveSel(v45, v20, selsave, p_mestextsave, p_selflag);
    scrLogSelIDSave(logdispwk);
    scrNewLogSaveSel(select[19]);
    scrSetIntReturnValue(select[19]);
    itfMesMngRequestSelectRelease(v9);
    scrEventSkipRestart();
    return 1;
  }
  v16 = IntPara;
  select[24] = cancelNum;
  itfMesMngRequestSelect(v9, v16);
  return 0;
}

// 0x1c62a20
s32 itfMesMngGetSelPhase(s32 msgid) {
  return g_manager->pmesflow[msgid]->pinst->select->phase;
}

// 0x1c62aa0
void itfMesMngSetSelPhase(s32 msgid, s32 phase) {
  s16 v3;

  v3 = phase;
  g_manager->pmesflow[msgid]->pinst->select->phase = v3;
}

// 0x1c62b30
s32 itfMesMngGetSelectNo(s32 msgid) {
  return g_manager->pmesflow[msgid]->pinst->select->select;
}

// 0x1c62bb0
s32 itfMesMngMaskSelect(void) {
  s32 MessageHandle;
  s32 v4;
  s32 IntPara;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  g_manager->pmesflow[v4]->pinst->select->mask = IntPara;
  return 1;
}

// 0x1c62d90
s32 itfMesMng_SEL_SELNO(void) {
  s32 MessageHandle;
  s32 v4;
  s32 IntPara;
  s16 v7;
  s32 v8;
  select_tag *select;
  u32 i;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  v7 = 0;
  v8 = 0;
  select = g_manager->pmesflow[v4]->pinst->select;
  for (i = select->mask; (i & 1) == 0; i >>= 1)
  {
    if (v8 >= IntPara)
      goto LABEL_19;
    ++v7;
LABEL_15:
    ++v8;
  }
  if (v8 < IntPara)
    goto LABEL_15;
  v7 = 0;
LABEL_19:
  select->select = v7;
  select->select_imm = v7;
  select->cancelNum = -1;
  return 1;
}

// 0x1c63010
s32 itfMesMngOpenWindow(void) {
  s32 result;
  s32 MessageHandle;
  s32 v4;
  instanceMes_tag *pinst;

  result = scrGetCommandTimer();
  if (!result)
    return result;
  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  pinst = g_manager->pmesflow[v4]->pinst;
  pinst->stat |= 0x200000u;
  return 1;
}

// 0x1c631f0
s32 itfMesMngCloseWindow(void) {
  s32 MessageHandle;
  u32 v4;
  instanceMes_tag *pinst;
  s32 v7;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  pinst = g_manager->pmesflow[v4]->pinst;
  if (!pinst)
    return 1;
  v7 = pinst->stat & 0x300;
  if (v7 == 512 || v7 == 256)
  {
    itfMesMngMsgWndCls(v4);
  }
  return v7 == 0;
}

// 0x1c63300
void itfMesMngMsgWndCls(s32 msgid) {
  instanceMes_tag *pinst;
  u32 stat;

  pinst = g_manager->pmesflow[msgid]->pinst;
  stat = pinst->stat;
  if ((stat & 0x300) != 0)
  {
    pinst->stat = stat | 0x300;
    FadeOutWindow();
  }
  if ((stat & 0x3000) != 0)
    pinst->stat |= 0x3000u;
  itfMesMngRequestMessageRelease(msgid, 1);
  itfMesMngRequestSelectRelease(msgid);
  pinst->stat &= ~0x200000u;
}

// 0x1c633e0
s32 itfMesMngOpenSelectWindow(void) {
  return 1;
}

// 0x1c633f0
s32 itfMesMngCloseSelectWindow(void) {
  return 1;
}

// 0x1c63400
s32 itfMesMngSetVarScr(void) {
  s32 MessageHandle;
  s32 v4;
  s32 IntPara;
  s32 v6;
  s32 v8;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  v8 = scrGetIntPara(2);
  itfMesMngSetVar(v4, IntPara, v6, v8);
  return 1;
}

// 0x1c63c80
s32 itfMesMngIgnoreConfig(void) {
  s32 MessageHandle;
  s32 v4;
  s32 IntPara;
  instanceMes_tag *pinst;
  instanceMes_tag *v10;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  if (IntPara)
  {
    pinst = g_manager->pmesflow[v4]->pinst;
    pinst->stat |= 0x400000u;
    return 1;
  }
  v10 = g_manager->pmesflow[v4]->pinst;
  v10->stat &= ~0x400000u;
  return 1;
}

// 0x1c63f00
s32 itfMesMngSetMesPositionScript(void) {
  s32 IntPara;

  if (scrGetMessageHandle() < 0)
    return 1;
  scrGetIntPara(0);
  IntPara = scrGetIntPara(1);
  itfMesPos((s32)itf, IntPara);
  return 1;
}

// 0x1c641f0
s32 itfMesMngSetMesPosDefault(void) {
  if (scrGetMessageHandle() < 0)
    return 1;
  itfMesPosDefault();
  return 1;
}

// 0x1c64470
s32 itfMesMngValidateNext(void) {
  s32 MessageHandle;
  s32 v4;
  s32 IntPara;
  char v8;
  char v10;
  instanceMes_tag *pinst;
  instanceMes_tag *v12;
  instanceMes_tag *v13;
  instanceMes_tag *v14;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  if (IntPara)
  {
    v8 = 1;
    pinst = g_manager->pmesflow[v4]->pinst;
    pinst->stat &= ~0x800000u;
    v12 = g_manager->pmesflow[v4]->pinst;
    v12->stat &= ~0x100000u;
    return 1;
  }
  v10 = 1;
  v13 = g_manager->pmesflow[v4]->pinst;
  v13->stat |= 0x800000u;
  v14 = g_manager->pmesflow[v4]->pinst;
  v14->stat |= 0x100000u;
  return 1;
}

// 0x1c64710
s32 itfMesMngWindowType(void) {
  s32 MessageHandle;
  s32 v4;
  s32 IntPara;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  itfMesMngChangeWindowType(v4, IntPara, 0);
  return 1;
}

// 0x1c64940
s32 itfMesMngWindowTypeAlpha(void) {
  s32 MessageHandle;
  s32 v4;
  s32 IntPara;
  s32 v7;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  v7 = scrGetIntPara(1);
  itfMesMngChangeWindowType(v4, IntPara, v7);
  return 1;
}

// 0x1c64a40
s32 itfMesMngSelectDefKey(void) {
  s32 MessageHandle;
  s32 v4;
  u32 IntPara;
  s16 v6;
  select_tag *select;
  s32 v9;
  s64 numdef;
  defkey_tag *defkey;
  s64 v12;
  defkey_tag *v13;

  MessageHandle = scrGetMessageHandle();
  if (MessageHandle < 0)
    return 1;
  v4 = MessageHandle;
  IntPara = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  if (IntPara > 0x17)
    return 1;
  select = g_manager->pmesflow[v4]->pinst->select;
  if (IntPara == 3)
    v9 = 4097;
  else
    v9 = IntPara;
  numdef = select->numdef;
  if (numdef <= 0)
  {
    defkey = select->defkey;
LABEL_27:
    select->numdef = numdef + 1;
    v13 = defkey[numdef];
  }
  else
  {
    defkey = select->defkey;
    v12 = 0;
    while (1)
    {
      v13 = defkey[v12];
      if (v9 == v13->key)
        break;
      if ((u16)select->numdef == ++v12)
      {
        if ((s16)numdef > 22)
          return 1;
        goto LABEL_27;
      }
    }
  }
  v13->key = v9;
  v13->index = v6;
  return 1;
}

// 0x1c64d60
s32 itfSetMesDispPriority(void) {
  Il2CppObject *Item;
  s32 IntPara;
  s32 mesPriority_local;

  Item = _get_Item(MsgWndCnv, 1);
  IntPara = scrGetIntPara(0);
  if (!op_Inequality(Item, 0, 0))
    return 1;
  if (IntPara)
  {
    evtMoonDisableDraw(1);
    fadeFrontDisp = 1;
    set_overrideSorting(Item, 1, 0);
    mesPriority_local = mesPriority;
    goto LABEL_20;
  }
  evtMoonEnableDraw();
  fadeFrontDisp = 0;
  set_overrideSorting(Item, 1, 0);
  mesPriority_local = 20;
LABEL_20:
  set_sortingOrder(Item, mesPriority_local, 0);
  return 1;
}

// 0x1c64f60
s32 itfMesMngInitialize(void *presource, char *master_text, char *key) {
  itfMiscLinkStack_t *linkstack;
  itfMiscLinkHeader_t *v9;
  itfMiscLinkHeader_t *v10;
  s32 id;
  instanceMes_tag *v12;
  itfMiscLinkHeader_t *v13;
  itfMiscLinkHeader_t *klass;
  u64 *data;
  s64 v17;
  Il2CppClass *element_class;
  window_tag *castClass;
  Il2CppClass *parent;

  linkstack = g_manager->linkstack;
  v9 = itfMiscLinkTake(linkstack);
    v10 = v9;
  else
    v10 = 0;
  id = v10->id;
  v12 = Allocate(instanceMes_tag);
  _ctor(v12, 0);
  v10[1].klass = (itfMiscLinkHeader_t *)v12;
  v13 = v10 + 1;
  klass = v13->klass;
  klass->_1.namespaze = 0;
  itfMesMngSetResourcePtr(id, presource);
  klass->_1.generic_class = master_text;
  klass->_1.typeMetadataHandle = key;
  LODWORD(klass->_1.interopData) = id;
  LODWORD(klass->_1.name) = 0;
  klass->_1.fields = 0;
  *(u64 *)&klass->_1.byval_arg.bits = 0x6D00FFFFF0LL;
  data = klass->_1.this_arg.data;
  set_Item((sdfIVector2_t)(data + 2), 0, 4020, 0);
  set_Item((sdfIVector2_t)(data + 2), 1, 5832, 0);
  data[3] = 0;
  data += 3;
  *((u16 *)data + 4) = -1;
  v17 = *(u64 *)&klass->_1.this_arg.bits;
  set_Item((sdfIVector2_t)(v17 + 16), 0, 4500, 0);
  set_Item((sdfIVector2_t)(v17 + 16), 1, 6318, 0);
  *(u64 *)(v17 + 32) = 0;
  v17 += 32;
  *(u32 *)(v17 + 16) = 0;
  *(u64 *)(v17 + 8) = 0x800000000000LL;
  element_class = klass->_1.element_class;
  set_Item((sdfIVector2_t)&element_class->_1.name, 0, 5160, 0);
  set_Item((sdfIVector2_t)&element_class->_1.name, 1, 7218, 0);
  element_class->_1.namespaze = 0;
  element_class = ((char *)element_class + 24);
  LODWORD(element_class->_1.gc_desc) = 0;
  HIDWORD(element_class->_1.name) = 0;
  LOWORD(element_class->_1.namespaze) = -1;
  *(void **)((char *)&element_class->_1.gc_desc + 4) = 0xFFFFFFFF0000LL;
  castClass = klass->_1.castClass;
  castClass->spk = 0;
  castClass->mes = 0;
  ResetWindowPara(castClass, 0, 0);
  InitializeVariable(klass->_1.declaringType);
  parent = klass->_1.parent;
  LOBYTE(parent->_1.name) = 0;
  *(u32 *)((char *)&parent->_1.namespaze + 2) = 0;
  HIWORD(parent->_1.namespaze) = 0;
  LODWORD(parent->_1.byval_arg.data) = 0;
  *(const char **)((char *)&parent->_1.name + 2) = 0x8000000000LL;
  ++g_manager->numuse;
  return id;
}

// 0x1c65390
void itfMesMngRelease(s32 id) {
  LOGDISP_PARAM *logdispwk_local;
  s32 *v5;
  LOGDISP_PARAM *v6;
  s32 *v7;
  LOGDISP_PARAM *v8;
  s32 *v9;
  LOGDISP_PARAM *v10;
  s32 *v11;

  if ((id & 0x80000000) == 0)
  {
    if (g_manager->pmesflow[id]->pinst)
    {
      DestructFlow(id);
      logdispwk_local = logdispwk;
      v5 = NewSpecific(s32, 1u);
      logdispwk_local->selcnt = v5;
      v6 = logdispwk;
      v7 = NewSpecific(s32, 1u);
      v6->selidx = v7;
      v8 = logdispwk;
      v9 = NewSpecific(s32, 1u);
      v8->selcntsave = v9;
      v10 = logdispwk;
      v11 = NewSpecific(s32, 1u);
      v10->selidxsave = v11;
    }
  }
}

// 0x1c5f6d0
f32 itfGetMesWinAlpha(void) {
  s32 v3;
  Il2CppObject *Item;

  if (meswin_type)
    v3 = 22;
  else
    v3 = 1;
  Item = _get_Item(MsgWndCnvGrp, v3);
  return get_alpha(Item, 0);
}

// 0x1c654f0
void itfMesWinAlphaClear(void) {
  s32 v3;
  Il2CppObject *Item;

  if (meswin_type)
    v3 = 22;
  else
    v3 = 1;
  Item = _get_Item(MsgWndCnvGrp, v3);
  set_alpha(Item, 0.0, 0);
}

// 0x1c60fc0
s32 itfMesMngRequestMessage(s32 id, s32 message, s32 page, s32 callmode, bool hojo) {
  bool v9;
  instanceMes_tag *pinst;
  itfMesBinMesHeader_t *v14;
  Il2CppObject *pdata;
  void *Interface;
  s32 ptr;
  void *v19;
  void *v20;
  void *v21;
  s32 v22;
  s64 v23;
  s64 v24;
  u32 v25;
  s64 v26;
  s32 v27;
  s32 v28;
  s64 v29;
  int32x4_t *v30;
  s64 v31;
  s64 v32;
  s32 v33;
  s64 v34;
  s64 v35;
  int32x4_t *v36;
  s32 *v37;
  s32 v38;
  s32 v39;
  u32 v40;
  message_tag *v41;
  s32 v42;
  Speaker_tag *speaker;
  s32 num;
  s32 v52;
  FontReq_t *p_pfont;
  FontReq_t *pfont;
  u32 stat;
  int32x4_t v60;
  int32x4_t *v61;
  s64 v62;
  s64 v63;
  int32x4_t v64;
  int32x4_t v65;
  int32x4_t v66;
  int32x4_t v67;
  int32x4_t v68;
  int32x4_t v69;
  int32x4_t v70;
  itfpanel_t *spk;
  itfpanel_t *p_fields;
  itfPanelTypeWork_t *pwork;
  window_tag *window;
  s32 Item;
  s32 v77;
  u8 *SpeakerName;
  u8 v79;
  FontReq_t *v80;
  FontReq_t *v82;
  s32 v83;
  s32 v84;
  FontReq_t *v85;
  FontReq_t *prev;
  u32 z;
  FontReq_t *bufferdata;
  u32 v91;
  s32 v93;
  s32 v95;
  s16 v96;

  v96 = page;
  v9 = hojo;
  pinst = g_manager->pmesflow[id]->pinst;
  pinst->hojomes = v9;
  v14 = Allocate(itfMesBinMesHeader_t);
  pdata = pinst->pdata;
  v95 = id;
  else
  {
    Interface = 0;
  }
  ptr = GetTypeHeader(pinst, message)->ptr;
  v19 = NewSpecific(byte, 0x18u);
  v14->label = v19;
  Copy_56175392(Interface, ptr + 32, v14->label, 0, 24, 0);
  v14->page = ToInt16(Interface, ptr + 56, 0);
  v14->speaker = ToUInt16(Interface, ptr + 58, 0);
  v20 = NewSpecific(uint, v14->page);
  v14->addr = v20;
  v21 = NewSpecific(s32, v14->page);
  v14->len = v21;
  if (v14->page >= 1)
  {
    v22 = ptr + 60;
    v23 = 8;
    do
    {
      v24 = v14->addr;
      v25 = ToUInt32(Interface, v22, 0);
      v26 = v23 - 7;
      v22 += 4;
      *(u32 *)(v24 + 4 * v23++) = v25 + 32;
    }
    while (v26 < v14->page);
  }
  v27 = ToInt32(Interface, *(u32 *)((u64)v14->addr + 32) - 4, 0);
  v28 = v14->page;
  v29 = (u32)(v28 - 1);
  v30 = v14->len;
  if (v28 <= 1)
  {
    v33 = 0;
    goto LABEL_21;
  }
  v31 = v14->addr;
  if (v14->page < 0x11u || (u64)v30[2].n128_u64 < 4 * v29 + v31 + 36 && v31 + 32 < (u64)v30[2].n128_u64 + 4 * v29)
  {
    v32 = 0;
    v33 = 0;
LABEL_17:
    v34 = 4 * v32;
    v35 = v29 - v32;
    v36 = ((char *)v30 + v34 + 32);
    v37 = (v34 + v31 + 36);
    do
    {
      v39 = *(v37 - 1);
      v38 = *v37++;
      --v35;
      v40 = v38 - v39;
      v33 += v40;
      v36->n128_u32[0] = v40;
      v36 = ((char *)v36 + 4);
    }
    while (v35);
    goto LABEL_21;
  }
  v60 = 0u;
  v32 = (u32)v29 & 0xFFFFFFF0;
  v61 = v30 + 5;
  v62 = v31 + 48;
  v63 = v32;
  v64 = 0u;
  v65 = 0u;
  v66 = 0u;
  do
  {
    v63 -= 16;
    v67 = vsubq_s32(*(int32x4_t *)(v62 - 12), *(int32x4_t *)(v62 - 16));
    v68 = vsubq_s32(*(int32x4_t *)(v62 + 4), *(int32x4_t *)v62);
    v69 = vsubq_s32(*(int32x4_t *)(v62 + 20), *(int32x4_t *)(v62 + 16));
    v64 = vaddq_s32(v68, v64);
    v70 = vsubq_s32(*(int32x4_t *)(v62 + 36), *(int32x4_t *)(v62 + 32));
    v66 = vaddq_s32(v70, v66);
    v62 += 64;
    v60 = vaddq_s32(v67, v60);
    v65 = vaddq_s32(v69, v65);
    v61[-3] = v67;
    v61[-2] = v68;
    v61[-1] = v69;
    *v61 = v70;
    v61 += 4;
  }
  while (v63);
  v33 = vaddvq_s32(vaddq_s32(v66, vaddq_s32(v65, vaddq_s32(v64, v60))));
  if (v32 != v29)
    goto LABEL_17;
LABEL_21:
  v41 = pinst->message;
  v30[2].n128_u32[(s32)v29] = v27 + ~v33;
  v41->pbinheader = v14;
  v41->callmode = callmode;
  v41->page = v96;
  v42 = v14->page;
  v41->maxpage = v42;
  if (!v42)
    return 0;
  itfClearMsgWndText();
  CommitVarTable(pinst->variable);
  ReadytoMessage(pinst, callmode);
  CallEventVoice(pinst);
  if (callmode == 2)
    return 1;
  speaker = pinst->speaker;
  num = speaker->num;
  v52 = v14->speaker;
  p_pfont = &speaker->pfont;
  pfont = speaker->pfont;
  if (num != 0xFFFF && num == v52)
  {
    SwitchSpeaker(0, 0);
    SwitchSpeaker(0, 0);
    goto LABEL_67;
  }
  if (pfont)
  {
    frDestroyFontRequestAfter(pfont);
    p_pfont = 0;
  }
  speaker->num = v52;
  if (v52 == 0xFFFF)
  {
    SwitchSpeaker(0, 0);
    stat = pinst->stat;
LABEL_66:
    pinst->stat = stat & 0xFFFFCFFF;
    ClearSpeaker();
    goto LABEL_67;
  }
  spk = pinst->window->spk;
  if (spk)
  {
    pwork = spk->pwork;
    p_fields = &spk->fields;
    if (pwork)
    {
      p_fields->pwork = 0;
    }
    window = pinst->window;
    window->spk = 0;
  }
  if ((v52 & 0x8000) != 0)
  {
    bufferdata = create_bufferdata(v95, v52 & 0x7FFF);
    p_pfont = bufferdata;
    v82 = p_pfont;
    if (p_pfont)
      goto LABEL_54;
LABEL_63:
    SwitchSpeaker(0, 0);
    stat = pinst->stat;
    speaker->num = 0;
    goto LABEL_66;
  }
  Item = get_Item((sdfIVector2_t)&speaker->fields, 0, 0);
  v77 = get_Item((sdfIVector2_t)&speaker->fields, 1, 0);
  SpeakerName = GetSpeakerName(pinst);
  v80 = itfMessageRequestExLocalize(Item, v77, 0, 3u, 0, v79, SpeakerName, 0, 1, 0, 0);
  p_pfont = v80;
  v82 = p_pfont;
  if (!p_pfont)
    goto LABEL_63;
LABEL_54:
  v83 = get_Item((sdfIVector2_t)&speaker->fields, 0, 0);
  v84 = get_Item((sdfIVector2_t)&speaker->fields, 1, 0);
  v85 = p_pfont;
  v82->x = v83;
  v82->y = v84;
  v85->draw_spd = 20;
  prev = p_pfont;
  if (p_pfont)
  {
    z = pinst->z;
    do
    {
      prev->priority = z;
      prev = prev->prev;
    }
    while (prev);
  }
LABEL_67:
  if (logdispwk->pmvrun)
  {
    goto LABEL_72;
  }
  setGuideMsg(0, speaker);
LABEL_72:
  OpenCheckSpeakerWindow(pinst);
  v91 = pinst->stat;
  if ((v91 & 0x200000) != 0)
  {
    if ((v91 & 0x300) == 0x300 || (v91 & 0x300) == 0)
    {
      OpenMessageWindow(pinst);
      v91 = pinst->stat;
      v93 = 2;
      goto LABEL_87;
    }
  }
  v93 = 3;
LABEL_87:
  v41->phase = 1;
  pinst->stat = v91 & 0xFFFFFFF8 | v93;
  return 1;
}

// 0x1c656e0
static FontReq_t *create_bufferdata(s32 id, s32 var) {
  FontReq_t *v5;

  v5 = Allocate(FontReq_t);
  _ctor(v5, 0);
  return itfCreateVarFRQ(g_manager->pmesflow[id]->pinst->variable->pptr[var]);
}

// 0x1c58870
void itfMesMngRequestMessageRelease(s32 id, s32 cls_speaker) {
  instanceMes_tag *pinst;
  message_tag *message;
  FontReq_t *p_pfont;
  FontReq_t *pfont;
  Speaker_tag *speaker;
  FontReq_t *v12;
  FontReq_t *v13;
  FontReq_t *v14;

  if ((id & 0x80000000) == 0)
  {
    pinst = g_manager->pmesflow[id]->pinst;
    message = pinst->message;
    p_pfont = &message->pfont;
    pfont = message->pfont;
    if (pfont)
    {
      frDestroyFontRequestAfter(pfont);
      p_pfont = 0;
    }
    message->pfont = 0;
    *(u32 *)&message->page = 0;
    *(u64 *)&message->phase = 0x800000000000LL;
    pinst->stat &= 0xFFFDFFF8;
    if (cls_speaker)
    {
      speaker = pinst->speaker;
      v12 = &speaker->pfont;
      v13 = speaker->pfont;
      if (v13)
      {
        frDestroyFontRequestAfter(v13);
        v12 = 0;
        speaker = pinst->speaker;
      }
      speaker->pfont = 0;
      v14 = &speaker->pfont;
      *((u16 *)v14 + 4) = -1;
    }
  }
}

// 0x1c62430
void itfMesMngRequestSelect(s32 id, s32 select) {
  instanceMes_tag *pinst;
  Il2CppObject *pdata;
  void *Interface;
  itfMesBinTypeHeader_t *TypeHeader;
  select_tag *v11;
  itfMesBinTypeHeader_t *v12;
  FontReq_t *pfont;
  s32 ptr;
  itfMesBinSelHeader_t *v16;
  void *v17;
  void *v18;
  void *v19;
  s32 v20;
  s64 v21;
  s64 v22;
  u32 v23;
  s64 v24;
  s32 v25;
  s32 v26;
  s64 v27;
  int32x4_t *v28;
  s64 v29;
  s64 v30;
  s32 v31;
  s32 v32;
  int32x4_t v33;
  int32x4_t *v34;
  s64 v35;
  s64 v36;
  int32x4_t v37;
  int32x4_t v38;
  int32x4_t v39;
  int32x4_t v40;
  int32x4_t v41;
  int32x4_t v42;
  int32x4_t v43;
  s64 v44;
  s64 v45;
  int32x4_t *v46;
  s32 *v47;
  s32 v48;
  s32 v49;
  u32 v50;
  s32 v51;
  u32 mask;
  s32 v54;
  u32 v55;
  s32 v56;
  _BOOL4 v57;
  s32 v58;
  s32 Item;
  f32 v61;
  s32 v62;
  s32 v63;
  u32 *v64;
  s32 *v65;
  s32 v66;
  u32 v67;
  s32 v68;
  FontReq_t *FontHandleUnit;
  u32 stat;
  s32 cancelNum;
  char **v76;
  FontReq_t *target;

  pinst = g_manager->pmesflow[id]->pinst;
  pdata = pinst->pdata;
  else
  {
    Interface = 0;
  }
  TypeHeader = GetTypeHeader(pinst, select);
  v11 = pinst->select;
  v12 = TypeHeader;
  pfont = v11->pfont;
  target = &v11->pfont;
  if (pfont)
  {
    frDestroyFontRequestAfter(pfont);
    target = 0;
    ClearMessage();
  }
  ptr = v12->ptr;
  v16 = Allocate(itfMesBinSelHeader_t);
  v17 = NewSpecific(byte, 0x18u);
  v16->label = v17;
  Copy_56175392(Interface, ptr + 32, v16->label, 0, 24, 0);
  v16->ext = ToInt16(Interface, ptr + 56, 0);
  v16->item = ToInt16(Interface, ptr + 58, 0);
  v16->pattern = ToInt16(Interface, ptr + 60, 0);
  v16->reserved = ToUInt16(Interface, ptr + 62, 0);
  v18 = NewSpecific(uint, v16->item);
  v16->ptr = v18;
  v19 = NewSpecific(s32, v16->item);
  v16->len = v19;
  if (v16->item >= 1)
  {
    v20 = ptr + 64;
    v21 = 8;
    do
    {
      v22 = v16->ptr;
      v23 = ToUInt32(Interface, v20, 0);
      v24 = v21 - 7;
      v20 += 4;
      *(u32 *)(v22 + 4 * v21++) = v23 + 32;
    }
    while (v24 < v16->item);
  }
  v25 = ToInt32(Interface, *(u32 *)((u64)v16->ptr + 32) - 4, 0);
  v26 = v16->item;
  v27 = (u32)(v26 - 1);
  v28 = v16->len;
  if (v26 <= 1)
  {
    v32 = -1;
    goto LABEL_29;
  }
  v29 = v16->ptr;
  if ((u32)v26 >= 0x11)
  {
    if ((u64)v28[2].n128_u64 >= 4 * v27 + v29 + 36 || v29 + 32 >= (u64)v28[2].n128_u64 + 4 * v27)
    {
      v33 = 0u;
      v30 = (u32)v27 & 0xFFFFFFF0;
      v34 = v28 + 5;
      v35 = v29 + 48;
      v36 = v30;
      v37 = 0u;
      v38 = 0u;
      v39 = 0u;
      do
      {
        v36 -= 16;
        v40 = vsubq_s32(*(int32x4_t *)(v35 - 12), *(int32x4_t *)(v35 - 16));
        v41 = vsubq_s32(*(int32x4_t *)(v35 + 4), *(int32x4_t *)v35);
        v42 = vsubq_s32(*(int32x4_t *)(v35 + 20), *(int32x4_t *)(v35 + 16));
        v37 = vaddq_s32(v41, v37);
        v43 = vsubq_s32(*(int32x4_t *)(v35 + 36), *(int32x4_t *)(v35 + 32));
        v39 = vaddq_s32(v43, v39);
        v35 += 64;
        v33 = vaddq_s32(v40, v33);
        v38 = vaddq_s32(v42, v38);
        v34[-3] = v40;
        v34[-2] = v41;
        v34[-1] = v42;
        *v34 = v43;
        v34 += 4;
      }
      while (v36);
      v31 = vaddvq_s32(vaddq_s32(v39, vaddq_s32(v38, vaddq_s32(v37, v33))));
      if (v30 == v27)
        goto LABEL_28;
    }
    else
    {
      v30 = 0;
      v31 = 0;
    }
  }
  else
  {
    v30 = 0;
    v31 = 0;
  }
  v44 = 4 * v30;
  v45 = v27 - v30;
  v46 = ((char *)v28 + v44 + 32);
  v47 = (v44 + v29 + 36);
  do
  {
    v49 = *(v47 - 1);
    v48 = *v47++;
    --v45;
    v50 = v48 - v49;
    v31 += v50;
    v46->n128_u32[0] = v50;
    v46 = ((char *)v46 + 4);
  }
  while (v45);
LABEL_28:
  v32 = ~v31;
LABEL_29:
  v51 = v25 + v32;
  v28[2].n128_u32[(s32)v27] = v51;
  mask = v11->mask;
  if (v26 < 1)
  {
    v58 = 0;
    goto LABEL_39;
  }
  v54 = 0;
  if (v26 != 1)
  {
    v55 = v26 & 0xFFFFFFFE;
    do
    {
      v55 -= 2;
      v56 = ((mask & 1) == 0) + v54;
      v57 = ((mask >> 1) & 1) == 0;
      mask >>= 2;
      v54 = v57 + v56;
    }
    while (v55);
  }
  if ((v26 & 1) != 0)
    v58 = ((mask & 1) == 0) + v54;
  else
    v58 = v54;
LABEL_39:
  Item = get_Item((sdfIVector2_t)&v11->fields, 1, 0);
  v61 = (f32)(25 * v58 - 25) * 2.25;
  v62 = 8 * (s32)v61;
  if (v61 == INFINITY)
    v62 = 0;
  v63 = Item - v62;
  CommitVarTable(pinst->variable);
  v64 = v16->ptr;
  v65 = v16->len;
  v66 = v16->item;
  v67 = v11->mask;
  v68 = get_Item((sdfIVector2_t)&v11->fields, 0, 0);
  FontHandleUnit = GetFontHandleUnit(Interface, v64, v65, v66, v67, v68, v63, pinst->z);
  v11->pfont = FontHandleUnit;
  stat = pinst->stat;
  v11->lines = v58;
  pinst->stat = stat & 0xFFFFFFC7 | 0x10;
  WindowDispOn(pinst);
  SelectWindowDispOn(pinst);
  cancelNum = (u16)v11->cancelNum;
  if (cancelNum == 0xFFFF)
  {
    v76 = &"MSG007";
    goto LABEL_45;
  }
  if (cancelNum != 1)
  {
    v76 = &"MSG008";
    goto LABEL_45;
  }
  v76 = &"MSG006";
LABEL_45:
  itfSetGuide(*v76, 1);
  v11->phase = 1;
}

// 0x1c589d0
void itfMesMngRequestSelectRelease(s32 id) {
  instanceMes_tag *pinst;
  select_tag *select;
  FontReq_t *p_pfont;
  FontReq_t *pfont;
  u32 stat;

  pinst = g_manager->pmesflow[id]->pinst;
  select = pinst->select;
  p_pfont = &select->pfont;
  pfont = select->pfont;
  if (pfont)
  {
    frDestroyFontRequestAfter(pfont);
    p_pfont = 0;
  }
  select->cancelNum = -1;
  select->lines = 0;
  *(u64 *)&select->mask = 0xFFFF000000000000LL;
  stat = pinst->stat;
  if ((stat & 0x40038) != 0)
  {
    pinst->stat = stat & 0xFFFBFFC7;
    SelectWindowDispOff(pinst);
  }
}

// 0x1c62d00
void itfMesMngSetMaskSelect(s32 id, u32 maskpattern) {
  g_manager->pmesflow[id]->pinst->select->mask = maskpattern;
}

// 0x1c62f30
void itfMesMngSetSelect(s32 id, s32 selno, s16 cancelNum) {
  s16 v8;
  s32 v9;
  select_tag *select;
  u32 i;

  v8 = 0;
  v9 = 0;
  select = g_manager->pmesflow[id]->pinst->select;
  for (i = select->mask; (i & 1) == 0; i >>= 1)
  {
    if (v9 >= selno)
      goto LABEL_12;
    ++v8;
LABEL_8:
    ++v9;
  }
  if (v9 < selno)
    goto LABEL_8;
  v8 = 0;
LABEL_12:
  select->cancelNum = cancelNum;
  select->select = v8;
  select->select_imm = v8;
}

// 0x1c64000
void itfMesPos(s32 x, s32 y) {
  Il2CppObject *Item;
  void *transform;
  void *Child;
  void *gameObject;
  Il2CppObject *Component_object;
  Il2CppObject *v10;
  f32 v11;
  void *v12;
  f32 v13;
  void *v14;
  Il2CppObject *v15;
  void *v16;
  void *v17;
  void *v18;
  Il2CppObject *v19;
  void *v20;
  void *v21;
  sdfVector3_t localPosition;
  sdfVector3_t v23;
  sdfVector3_t v24;
  sdfVector3_t v25;

  Item = _get_Item(MsgWnd, 0);
  transform = get_transform(Item, 0);
  Child = GetChild(transform, 0, 0);
  gameObject = get_gameObject(Child, 0);
  Component_object = GetComponent_object_(gameObject);
  set_enabled(Component_object, 0, 0);
  v10 = GetComponent_object_(gameObject);
  v11 = COERCE_FLOAT(LODWORD(get_sizeDelta(v10, 0).y))
      * 0.5;
  v12 = get_transform(gameObject, 0);
  localPosition = get_localPosition(v12, 0);
  v13 = 380.0 - (f32)(v11 + (f32)y);
  v14 = get_transform(gameObject, 0);
  v24.x = localPosition.x;
  v24.y = v13;
  v24.z = localPosition.z;
  set_localPosition(v14, v24, 0);
  v15 = _get_Item(MsgWnd, 3);
  v16 = get_transform(v15, 0);
  v17 = GetChild(v16, 0, 0);
  v18 = get_gameObject(v17, 0);
  v19 = GetComponent_object_(v18);
  set_enabled(v19, 0, 0);
  v20 = get_transform(v18, 0);
  v23 = get_localPosition(v20, 0);
  v21 = get_transform(v18, 0);
  v25.x = v23.x;
  v25.y = v13;
  v25.z = v23.z;
  set_localPosition(v21, v25, 0);
}

// 0x1c642c0
void itfMesPosDefault(void) {
  Il2CppObject *Item;
  void *transform;
  void *Child;
  void *gameObject;
  Il2CppObject *Component_object;
  void *v7;
  void *v8;
  Il2CppObject *v9;
  void *v10;
  void *v11;
  void *v12;
  Il2CppObject *v13;
  void *v14;
  void *v15;
  sdfVector3_t localPosition;
  sdfVector3_t v17;
  sdfVector3_t v18;
  sdfVector3_t v19;

  Item = _get_Item(MsgWnd, 0);
  transform = get_transform(Item, 0);
  Child = GetChild(transform, 0, 0);
  gameObject = get_gameObject(Child, 0);
  Component_object = GetComponent_object_(gameObject);
  set_enabled(Component_object, 1, 0);
  v7 = get_transform(gameObject, 0);
  localPosition = get_localPosition(v7, 0);
  v8 = get_transform(gameObject, 0);
  v18.x = localPosition.x;
  v18.z = localPosition.z;
  v18.y = -352.0;
  set_localPosition(v8, v18, 0);
  v9 = _get_Item(MsgWnd, 3);
  v10 = get_transform(v9, 0);
  v11 = GetChild(v10, 0, 0);
  v12 = get_gameObject(v11, 0);
  v13 = GetComponent_object_(v12);
  set_enabled(v13, 1, 0);
  v14 = get_transform(v12, 0);
  v17 = get_localPosition(v14, 0);
  v15 = get_transform(v12, 0);
  v19.x = v17.x;
  v19.y = -352.0;
  v19.z = v17.z;
  set_localPosition(v15, v19, 0);
}

// 0x1c65880
void itfMesMngSetMesPosition(s32 id, s32 x, s32 y) {
  mesflow_tag *v8;
  message_tag *message;
  sdfIVector2_t p_fields;
  s32 Item;
  s32 v12;
  FontReq_t *pfont;
  s32 v14;
  s32 v15;
  s32 v16;
  s64 v17;

  v8 = g_manager->pmesflow[id];
  v17 = 0;
  message = v8->pinst->message;
  p_fields = (sdfIVector2_t)&message->fields;
  Item = get_Item((sdfIVector2_t)&message->fields, 0, 0);
  set_Item((sdfIVector2_t)&v17, 0, x - Item, 0);
  v12 = get_Item((sdfIVector2_t)&message->fields, 1, 0);
  set_Item((sdfIVector2_t)&v17, 1, y - v12, 0);
  if (get_Item((sdfIVector2_t)&v17, 0, 0) || get_Item((sdfIVector2_t)&v17, 1, 0))
  {
    pfont = message->pfont;
    v14 = get_Item((sdfIVector2_t)&v17, 0, 0);
    v15 = get_Item((sdfIVector2_t)&v17, 1, 0);
    if (pfont)
      goto LABEL_9;
    goto LABEL_9000;
    for (; pfont; pfont = pfont->prev)
    {
LABEL_9:
      v16 = pfont->y + v15;
      pfont->x += v14;
      pfont->y = v16;
    }
LABEL_9000:
    set_Item(p_fields, 0, x, 0);
    set_Item(p_fields, 1, y, 0);
  }
}

// 0x1c65a20
void itfMesMngSetPriority(s32 id, u32 z_buf) {
  instanceMes_tag *pinst;
  FontReq_t *pfont;
  FontReq_t *i;
  FontReq_t *j;

  pinst = g_manager->pmesflow[id]->pinst;
  if (pinst->z != z_buf)
  {
    pfont = pinst->speaker->pfont;
    if (pfont)
      goto LABEL_8;
    goto LABEL_9000;
    for (; pfont; pfont = pfont->prev)
LABEL_8:
      pfont->priority = z_buf;
LABEL_9000:
    for (i = pinst->message->pfont; i; i = i->prev)
      i->priority = z_buf;
    for (j = pinst->select->pfont; j; j = j->prev)
      j->priority = z_buf;
    pinst->z = z_buf;
  }
}

// 0x1c65b20
u32 itfMesMngGetStat(s32 id) {
  return g_manager->pmesflow[id]->pinst->stat;
}

// 0x1c65ba0
void itfMesMngSetStat(s32 id, u32 flag) {
  s16 v3;

  v3 = HIWORD(flag);
  HIWORD(g_manager->pmesflow[id]->pinst->stat) = v3;
}

// 0x1c63160
void itfMesMngMarkBitStat(s32 id, u32 flag) {
  s64 v6;

  v6 = (s64)g_manager->pmesflow + 8 * id;
  *(u32 *)(*(u64 *)(*(u64 *)(v6 + 32) + 40) + 16) |= flag & 0xFFFF0000;
}

// 0x1c63e70
void itfMesMngClearBitStat(s32 id, u32 flag) {
  mesflow_tag *v6;

  v6 = g_manager->pmesflow[id];
  v6->pinst->stat &= ~flag | 0xFFFF;
}

// 0x1c65c30
s32 itfMesMngGetSelect(s32 id) {
  return g_manager->pmesflow[id]->pinst->select->select;
}

// 0x1c65cb0
s32 itfMesMngGetMesPage(s32 id) {
  return g_manager->pmesflow[id]->pinst->message->maxpage;
}

// 0x1c65d30
s32 itfMesMngGetMesCurrentPage(s32 id) {
  return g_manager->pmesflow[id]->pinst->message->page;
}

// 0x1c657f0
char *itfMesMngGetVar(s32 id, s32 index) {
  return g_manager->pmesflow[id]->pinst->variable->pptr[index];
}

// 0x1c63520
void itfMesMngSetVar(s32 id, s32 index, s32 num, s32 type) {
  s32 v6;
  Il2CppObject *v9;
  char *v10;
  char *v13;
  Il2CppObject *v15;
  char *v16;
  char *v18;
  char *v19;
  char **v20;
  SBTLSKILLP_TBL *Skilltbl;
  s32 SkillIconType;
  s32 v23;
  Il2CppObject *v24;
  char **v25;
  char *v28;
  s32 v29;
  s32 v30;
  char *Language;
  char *v33;
  s32 data;
  char *buf;

  v6 = num;
  buf = 0;
  switch (type)
  {
    case 0:
      data = v6;
      v9 = Box(s32, &data);
      v10 = Format("{0:D}", v9, 0);
      goto LABEL_77;
    case 1:
      v13 = sdatDevilName(v6, 0);
      goto LABEL_39;
    case 3:
      if (tbldata[v6]->iconType)
      {
        data = tbldata[v6]->iconType;
        v15 = Box(s32, &data);
        v16 = Format("<ITM_{0:D2}>", v15, 0);
        v18 = sdatItemName(v6);
        goto LABEL_76;
      }
      goto LABEL_64;
    case 4:
      v19 = "";
      buf = "";
      if (v6 >= 1001)
      {
        v20 = &"Ｒ";
      }
      else
      {
        if (v6 < 0)
        {
          v6 = -v6;
          buf = Concat_54766928("", "Ｂ", 0);
        }
        ConvertZenkakuNumber(&buf, v6);
        v19 = buf;
        v20 = &"Ｆ";
      }
      v33 = Concat_54766928(v19, *v20, 0);
      buf = v33;
      goto LABEL_79;
    case 5:
      Skilltbl = sBtlGetSkilltbl(v6);
      SkillIconType = cmpGetSkillIconType(Skilltbl, v6);
      if (SkillIconType != -1)
      {
        v23 = SkillIconType;
        if (RaidouSklCheck(v6))
        {
          data = v23 - 5;
          v24 = Box(s32, &data);
          v25 = &"<RAI_{0:D2}>";
        }
        else
        {
          data = v23 + 1;
          v24 = Box(s32, &data);
          v25 = &"<SKL_{0:D2}>";
        }
        v16 = Format(*v25, v24, 0);
        v18 = sdatSkillName(v6);
LABEL_76:
        v10 = Concat_54766928(v16, v18, 0);
        goto LABEL_77;
      }
LABEL_64:
      v10 = sdatItemName(v6);
LABEL_77:
      v33 = v10;
LABEL_79:
      itfMesMngSetVarImmediate(id, index, v33);
      return;
    case 8:
      v13 = sdatRaceName(v6);
      goto LABEL_39;
    case 10:
      v13 = ToString(LOBYTE(HeartsName) + (u8)v6 + 32, 0);
LABEL_39:
      v28 = v13;
      v29 = id;
      v30 = index;
LABEL_40:
      itfMesMngSetVarImmediate(v29, v30, v28);
      return;
    case 12:
      Language = frGetLanguage(GBWK->dream_code_language);
      v29 = id;
      v30 = index;
      v28 = Language;
      goto LABEL_40;
    default:
      return;
  }
}

// 0x1c65e80
void itfSetTextValue(s32 index, ITF_MESMNG_VAR type, s32 value, bool setIcon) {
  char *v9;
  Il2CppObject *v10;
  char *LocalizeText;
  char *DevilNameFont;
  Il2CppObject *v13;
  char *v14;
  char *v15;
  s32 iconType;
  s32 data;

  v9 = 0;
  switch (type)
  {
    case 0:
      data = value;
      v10 = Box(s32, &data);
      LocalizeText = Format("{0:D}", v10, 0);
      goto LABEL_23;
    case 1:
      DevilNameFont = sBtlGetDevilNameFont(value, 1);
      LocalizeText = GetLocalizeText(DevilNameFont, 0);
      goto LABEL_23;
    case 3:
      if (tbldata[value]->iconType && setIcon)
      {
        iconType = tbldata[value]->iconType;
        v13 = Box(s32, &iconType);
        v14 = Format("<ITM_{0:D2}>", v13, 0);
        v15 = sdatItemName(value);
        LocalizeText = Concat_54766928(v14, v15, 0);
      }
      else
      {
        LocalizeText = sdatItemName(value);
      }
LABEL_23:
      v9 = LocalizeText;
LABEL_24:
      itfSetTextDataValue(index, v9);
      return;
    case 8:
      LocalizeText = sdatRaceName(value);
      goto LABEL_23;
    default:
      goto LABEL_24;
  }
}

// 0x1c66120
void itfSetTextDataValue(s32 index, char *value) {
  s64 v6;

  if (IsNullOrEmpty(value, 0))
    return;
  v6 = (s64)gVarStr + 8 * index;
  *(u64 *)(v6 + 32) = value;
  return;
}

// 0x1c66220
char *itfGetText(char *label) {
  char *LocalizeText;
  char *v5;
  char *v7;
  s64 v8;
  s64 i;

  LocalizeText = GetLocalizeText(label, 1);
  v5 = itfTextTagReplace(LocalizeText, 1);
  v7 = itfTextTagReplace(v5, 1);
  v8 = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(fixTagValue->max_length))
      break;
    v7 = Replace_54838864(v7, fixTagValue[v8].Item1, fixTagValue[v8].Item2, 0);
    ++v8;
  }
  return v7;
}

// 0x1c65db0
void itfMesMngSetVarImmediate(s32 id, s32 index, char *pstr) {
  variable_tag *variable;
  s64 v9;
  s64 v10;

  variable = g_manager->pmesflow[id]->pinst->variable;
  if (!IsNullOrEmpty(variable->pptr[index], 0))
  {
    v9 = (s64)variable->pptr + 8 * index;
    *(u64 *)(v9 + 32) = 0;
  }
  v10 = (s64)variable->pptr + 8 * index;
  *(u64 *)(v10 + 32) = pstr;
}

// 0x1c66350
void itfMesMngSetVarImmediate2(s32 id, s32 index, char *pstr, s32 length) {
  variable_tag *variable;
  s64 v10;
  s64 v11;

  variable = g_manager->pmesflow[id]->pinst->variable;
  if (!IsNullOrEmpty(variable->pptr[index], 0))
  {
    v10 = (s64)variable->pptr + 8 * index;
    *(u64 *)(v10 + 32) = 0;
  }
  v11 = (s64)variable->pptr + 8 * index;
  *(u64 *)(v11 + 32) = pstr;
}

// 0x1c65280
void *itfMesMngSetResourcePtr(s32 id, void *presource) {
  u64 *p_klass;
  Il2CppObject *v7;
  Il2CppObject *v8;
  u8 *Interface;

  p_klass = &g_manager->pmesflow[id]->pinst->klass;
  v8 = p_klass[3];
  p_klass += 3;
  v7 = v8;
  *p_klass = presource;
  if (presource)
  {
    Interface = QueryInterface(presource, byte);
    GetTypeHeader2(Interface);
    return v7;
  }
  else
  {
    GetTypeHeader2(0);
    return v7;
  }
}

// 0x1c66420
u8 *itfMesMngGetDataPtrImmediate(s32 id, s32 message, s32 page) {
  instanceMes_tag *pinst;
  Il2CppObject *pdata;
  itfMesBinMesHeader_t *pbinheader;
  void *Interface;
  s64 v11;
  s64 v12;
  s32 v13;
  void *v14;

  pinst = g_manager->pmesflow[id]->pinst;
  pdata = pinst->pdata;
  pbinheader = pinst->message->pbinheader;
  if (!pdata)
  {
    Interface = 0;
    goto LABEL_9;
  }
  Interface = QueryInterface(pinst->pdata, byte);
LABEL_9:
  if (page < 0 || pbinheader->page <= page)
    return 0;
  v11 = page;
  v12 = pbinheader->len[v11];
  v13 = pbinheader->addr[v11];
  v14 = NewSpecific(byte, (s32)v12 + 1);
  Copy_56175392(Interface, v13, v14, 0, v12, 0);
  *((u8 *)&v14[2].klass + v12) = 0;
  return v14;
}

// 0x1c665a0
char *itfMesMngGetStrImmediate(s32 id, s32 message, s32 page) {
  s32 v8;
  char *v10;
  bool v11;
  FontReq_t *pfont;
  char *v15;
  char *v16;

  v8 = itfMesMngRequestMessage(id, message, page, 2, 0);
  v10 = "";
  v11 = v8 == 1;
  if (!v11)
    goto LABEL_20;
  pfont = g_manager->pmesflow[id]->pinst->message->pfont;
  if (pfont)
  {
    do
    {
      v15 = sub_1C88420(pfont, 0);
      v16 = Concat_54766928(v10, v15, 0);
      pfont = pfont->next;
      v10 = v16;
    }
    while (pfont);
  }
  else
  {
LABEL_20:
  }
  itfMesMngRequestMessageRelease(id, 0);
  return v10;
}

// 0x1c666f0
FontReq_t *itfMesMngGetFRQ(s32 id, s32 message) {
  return g_manager->pmesflow[id]->pinst->message->pfont;
}

// 0x1c64800
void itfMesMngChangeWindowType(s32 id, s32 type, s32 alpha) {
  instanceMes_tag *pinst;
  window_tag *window;
  window_tag *v10;
  itfpanel_t *v12;
  itfpanel_t *p_mes;
  itfpanel_t *mes;
  itfpanel_t *p_fields;
  itfPanelTypeWork_t *pwork;
  sdfIVector4_t v17;

  pinst = g_manager->pmesflow[id]->pinst;
  if ((pinst->stat & 0x3000) == 0)
  {
    window = pinst->window;
    v10 = window;
    if (pinst->type == type)
    {
      *(u64 *)&v17.x = &window->mes_color;
      *(u64 *)&v17.z = 3;
      if (get_Item(v17, 0) == alpha)
        return;
      v10 = pinst->window;
    }
    pinst->type = type;
    ResetWindowPara(v10, type, alpha);
    mes = window->mes;
    p_mes = &window->mes;
    v12 = mes;
    if (mes)
    {
      pwork = v12->pwork;
      p_fields = &v12->fields;
      if (pwork)
      {
        p_fields->pwork = 0;
      }
      p_mes = 0;
    }
  }
}

// 0x1c64c30
s32 itfMesMngSetSelectDefKey(s32 id, s32 key, s32 index) {
  s16 v4;
  select_tag *select;
  s32 v9;
  s64 numdef;
  s64 v11;
  s64 m_Items;
  defkey_tag *v13;
  defkey_tag *defkey;

  v4 = index;
  if ((u32)key > 0x17)
    return 0;
  select = g_manager->pmesflow[id]->pinst->select;
  if (key == 3)
    v9 = 4097;
  else
    v9 = key;
  numdef = select->numdef;
  if (numdef < 1)
  {
LABEL_15:
    defkey = select->defkey;
    ++select->numdef;
    v13 = defkey[numdef];
  }
  else
  {
    v11 = (u16)select->numdef;
    m_Items = select->defkey;
    while (1)
    {
      v13 = *(defkey_tag *)m_Items;
      if (v9 == *(s16 *)(*(u64 *)m_Items + 16))
        break;
      m_Items += 8;
      if (!--v11)
      {
        if ((s32)numdef > 22)
          return 0;
        goto LABEL_15;
      }
    }
  }
  v13->key = v9;
  v13->index = v4;
  return 1;
}

// 0x1c66770
void itfMesMngSetDefaultSpeed(s32 id, s32 speed) {
  u8 v3;

  v3 = speed;
  g_manager->pmesflow[id]->pinst->message->last_spd = v3;
}

// 0x1c66800
void itfSetPageUpdateCallBack(s32 id, void *_func) {
  instanceMes_tag *pinst;

  pinst = g_manager->pmesflow[id]->pinst;
  pinst->pageUpdateCallBack = func;
}

// 0x1c66890
void itfMesMngObjectInitialize(void) {
  void *v1;
  u64 *p_MsgWnd;
  void *v4;
  void *p_MsgWndTMP;
  void *v6;
  void *p_MsgWndFocusTMP;
  void *v8;
  void *p_MsgWndCnv;
  void *v10;
  void *p_MsgWndAnm;
  void *v12;
  void *p_MsgWndCur;
  void *v14;
  void *p_MsgWndTMPObj;
  void *v16;
  void *p_MsgWndImg;
  void *v18;
  void *p_MsgWndCnvGrp;
  __int128 v20;
  Il2CppObject *current;
  Il2CppObject *klass;
  void *MsgWnd_local;
  u64 *v25;
  s64 size;
  void *items;
  Il2CppClass **v28;
  Il2CppObject *monitor;
  void *MsgWndTMP_local;
  u64 *v31;
  s64 v32;
  void *v33;
  Il2CppClass **v34;
  Il2CppObject *v35;
  void *MsgWndFocusTMP_local;
  u64 *v37;
  s64 v38;
  void *v39;
  Il2CppClass **v40;
  Il2CppObject *v41;
  void *MsgWndCnv_local;
  s64 v43;
  u64 *v44;
  void *v45;
  Il2CppClass **v46;
  Il2CppObject *v47;
  void *MsgWndAnm_local;
  u64 *v49;
  s64 v50;
  void *v51;
  Il2CppClass **v52;
  Il2CppObject *v53;
  void *MsgWndCur_local;
  u64 *v55;
  s64 v56;
  void *v57;
  Il2CppClass **v58;
  Il2CppObject *v59;
  void *MsgWndTMPObj_local;
  u64 *v61;
  s64 v62;
  void *v63;
  Il2CppClass **v64;
  Il2CppObject *v65;
  void *MsgWndImg_local;
  u64 *v67;
  s64 v68;
  void *v69;
  Il2CppClass **v70;
  Il2CppObject *v71;
  void *MsgWndCnvGrp_local;
  s64 v73;
  s64 v74;
  void *v75;
  Il2CppClass **v76;
  s32 i;
  Il2CppObject *v78;
  void *v80;
  Il2CppObject *Item;
  s32 j;
  Il2CppObject *v84;
  void *v87;
  Il2CppObject *v88;
  void *v90;
  s32 v91;
  Il2CppObject *v92;
  System_Collections_Generic_List_Enumerator_T__o v95;
  System_Collections_Generic_List_Enumerator_T__o v96;

  memset(&v96, 0, sizeof(v96));
  v1 = Allocate(System_Collections_Generic_List_GameObject_);
  __ctor(v1);
  p_MsgWnd = &MsgWnd;
  *p_MsgWnd = v1;
  v4 = Allocate(System_Collections_Generic_List_TextMeshProUGUI_);
  __ctor(v4);
  p_MsgWndTMP = &MsgWndTMP;
  p_MsgWndTMP = v4;
  v6 = Allocate(System_Collections_Generic_List_TextMeshProUGUI_);
  __ctor(v6);
  p_MsgWndFocusTMP = &MsgWndFocusTMP;
  p_MsgWndFocusTMP = v6;
  v8 = Allocate(System_Collections_Generic_List_Canvas_);
  __ctor(v8);
  p_MsgWndCnv = &MsgWndCnv;
  p_MsgWndCnv = v8;
  v10 = Allocate(System_Collections_Generic_List_Animator_);
  __ctor(v10);
  p_MsgWndAnm = &MsgWndAnm;
  p_MsgWndAnm = v10;
  v12 = Allocate(System_Collections_Generic_List_GameObject_);
  __ctor(v12);
  p_MsgWndCur = &MsgWndCur;
  p_MsgWndCur = v12;
  v14 = Allocate(System_Collections_Generic_List_GameObject_);
  __ctor(v14);
  p_MsgWndTMPObj = &MsgWndTMPObj;
  p_MsgWndTMPObj = v14;
  v16 = Allocate(System_Collections_Generic_List_Image_);
  __ctor(v16);
  p_MsgWndImg = &MsgWndImg;
  p_MsgWndImg = v16;
  v18 = Allocate(System_Collections_Generic_List_CanvasGroup_);
  __ctor(v18);
  p_MsgWndCnvGrp = &MsgWndCnvGrp;
  p_MsgWndCnvGrp = v18;
  _GetEnumerator(&v95, txtMgr->tmWork);
  v96._current = v95._current;
  v20 = *(_OWORD *)&v95._list;
  v95._list = 0;
  *(u64 *)&v95._index = &v96;
  *(_OWORD *)&v96._list = v20;
  while (_MoveNext(&v96))
  {
    current = v96._current;
    klass = current[1].klass;
    MsgWnd_local = MsgWnd;
    v25 = Method_System_Collections_Generic_List_GameObject__Add__;
    size = MsgWnd_local->_size;
    ++MsgWnd_local->_version;
    items = MsgWnd_local->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(MsgWnd_local, klass, *(const MethodInfo_2DFC660 **)(*(u64 *)(v25[4] + 192) + 112));
    }
    else
    {
      MsgWnd_local->_size = size + 1;
      v28 = &items->obj.klass + size;
      v28[4] = klass;
    }
    monitor = current[1].monitor;
    MsgWndTMP_local = MsgWndTMP;
    v31 = Method_System_Collections_Generic_List_TextMeshProUGUI__Add__;
    v32 = MsgWndTMP_local->_size;
    ++MsgWndTMP_local->_version;
    v33 = MsgWndTMP_local->_items;
    if ((u32)v32 >= LODWORD(v33->max_length))
    {
      _AddWithResize(MsgWndTMP_local, monitor, *(const MethodInfo_2DFC660 **)(*(u64 *)(v31[4] + 192) + 112));
    }
    else
    {
      MsgWndTMP_local->_size = v32 + 1;
      v34 = &v33->obj.klass + v32;
      v34[4] = monitor;
    }
    v35 = current[2].klass;
    MsgWndFocusTMP_local = MsgWndFocusTMP;
    v37 = Method_System_Collections_Generic_List_TextMeshProUGUI__Add__;
    v38 = MsgWndFocusTMP_local->_size;
    ++MsgWndFocusTMP_local->_version;
    v39 = MsgWndFocusTMP_local->_items;
    if ((u32)v38 >= LODWORD(v39->max_length))
    {
      _AddWithResize(MsgWndFocusTMP_local, v35, *(const MethodInfo_2DFC660 **)(*(u64 *)(v37[4] + 192) + 112));
    }
    else
    {
      MsgWndFocusTMP_local->_size = v38 + 1;
      v40 = &v39->obj.klass + v38;
      v40[4] = v35;
    }
    v41 = current[3].klass;
    MsgWndCnv_local = MsgWndCnv;
    v43 = MsgWndCnv_local->_size;
    v44 = Method_System_Collections_Generic_List_Canvas__Add__;
    ++MsgWndCnv_local->_version;
    v45 = MsgWndCnv_local->_items;
    if ((u32)v43 >= LODWORD(v45->max_length))
    {
      _AddWithResize(MsgWndCnv_local, v41, *(const MethodInfo_2DFC660 **)(*(u64 *)(v44[4] + 192) + 112));
    }
    else
    {
      MsgWndCnv_local->_size = v43 + 1;
      v46 = &v45->obj.klass + v43;
      v46[4] = v41;
    }
    v47 = current[2].monitor;
    MsgWndAnm_local = MsgWndAnm;
    v49 = Method_System_Collections_Generic_List_Animator__Add__;
    v50 = MsgWndAnm_local->_size;
    ++MsgWndAnm_local->_version;
    v51 = MsgWndAnm_local->_items;
    if ((u32)v50 >= LODWORD(v51->max_length))
    {
      _AddWithResize(MsgWndAnm_local, v47, *(const MethodInfo_2DFC660 **)(*(u64 *)(v49[4] + 192) + 112));
    }
    else
    {
      MsgWndAnm_local->_size = v50 + 1;
      v52 = &v51->obj.klass + v50;
      v52[4] = v47;
    }
    v53 = current[3].monitor;
    MsgWndCur_local = MsgWndCur;
    v55 = Method_System_Collections_Generic_List_GameObject__Add__;
    v56 = MsgWndCur_local->_size;
    ++MsgWndCur_local->_version;
    v57 = MsgWndCur_local->_items;
    if ((u32)v56 >= LODWORD(v57->max_length))
    {
      _AddWithResize(MsgWndCur_local, v53, *(const MethodInfo_2DFC660 **)(*(u64 *)(v55[4] + 192) + 112));
    }
    else
    {
      MsgWndCur_local->_size = v56 + 1;
      v58 = &v57->obj.klass + v56;
      v58[4] = v53;
    }
    v59 = current[4].klass;
    MsgWndTMPObj_local = MsgWndTMPObj;
    v61 = Method_System_Collections_Generic_List_GameObject__Add__;
    v62 = MsgWndTMPObj_local->_size;
    ++MsgWndTMPObj_local->_version;
    v63 = MsgWndTMPObj_local->_items;
    if ((u32)v62 >= LODWORD(v63->max_length))
    {
      _AddWithResize(MsgWndTMPObj_local, v59, *(const MethodInfo_2DFC660 **)(*(u64 *)(v61[4] + 192) + 112));
    }
    else
    {
      MsgWndTMPObj_local->_size = v62 + 1;
      v64 = &v63->obj.klass + v62;
      v64[4] = v59;
    }
    v65 = current[4].monitor;
    MsgWndImg_local = MsgWndImg;
    v67 = Method_System_Collections_Generic_List_Image__Add__;
    v68 = MsgWndImg_local->_size;
    ++MsgWndImg_local->_version;
    v69 = MsgWndImg_local->_items;
    if ((u32)v68 >= LODWORD(v69->max_length))
    {
      _AddWithResize(MsgWndImg_local, v65, *(const MethodInfo_2DFC660 **)(*(u64 *)(v67[4] + 192) + 112));
    }
    else
    {
      MsgWndImg_local->_size = v68 + 1;
      v70 = &v69->obj.klass + v68;
      v70[4] = v65;
    }
    v71 = current[5].klass;
    MsgWndCnvGrp_local = MsgWndCnvGrp;
    v73 = Method_System_Collections_Generic_List_CanvasGroup__Add__;
    v74 = MsgWndCnvGrp_local->_size;
    ++MsgWndCnvGrp_local->_version;
    v75 = MsgWndCnvGrp_local->_items;
    if ((u32)v74 >= LODWORD(v75->max_length))
    {
      _AddWithResize(MsgWndCnvGrp_local, v71, *(const MethodInfo_2DFC660 **)(*(u64 *)(*(u64 *)(v73 + 32) + 192) + 112));
    }
    else
    {
      MsgWndCnvGrp_local->_size = v74 + 1;
      v76 = &v75->obj.klass + v74;
      v76[4] = v71;
    }
  }
  _Dispose(&v96);
  for (i = 0; ; ++i)
  {
    v80 = MsgWnd;
    if (i >= v80->_size)
      break;
    v80 = MsgWnd;
    Item = _get_Item(v80, i);
    if (!op_Inequality(Item, 0, 0))
      continue;
    v78 = _get_Item(MsgWnd, i);
    SetActive(v78, 0, 0);
  }
  for (j = 0; ; ++j)
  {
    v87 = MsgWndCur;
    if (j >= v87->_size)
      break;
    v87 = MsgWndCur;
    v88 = _get_Item(v87, j);
    if (!!op_Inequality(v88, 0, 0))
    {
      v84 = _get_Item(MsgWndCur, j);
      SetActive(v84, 0, 0);
    }
  }
  v90 = MsgWndTMP;
  if (meswin_type)
    v91 = 22;
  else
    v91 = 1;
  v92 = _get_Item(v90, v91);
  (v92->klass->vtable[66].methodPtr)(v92, "", v92->klass->vtable[66].method);
  itfSetMsgWndCnvGrpAlpha(0, 1.0);
  itfSetIsmesWndBaseDisp(1);
  InitInterfaceManager(txtMgr, 0);
}

// 0x1c67860
void itfMesMngPadModeOn(u32 Mode) {
  g_padmode |= Mode;
}

// 0x1c678d0
void itfMesMngPadModeOff(u32 Mode) {
  g_padmode &= ~Mode;
}

// 0x1c67940
void itfMesMngInitializeManager(void) {
  manager_tag *g_manager_local;
  itfMiscLinkStack_t *linkstack;
  itfMiscLinkHeader_t *pmesflow;
  itfMiscLinkHeader_t *i;
  itfMiscLinkHeader_t *v9;
  dds3ProcessFunc_t v10;
  dds3ProcessFunc_t v11;
  void *tmMsgWndOwner;
  void *tmSpeakerTMP;
  s32 v20;
  Il2CppObject *Item;

  g_manager_local = g_manager;
  *(u64 *)&g_manager_local->numuse = 0;
  g_manager_local->stat = 0;
  linkstack = g_manager_local->linkstack;
  pmesflow = g_manager_local->pmesflow;
  itfMiscLinkInitialize(linkstack, pmesflow, 64);
  for (i = g_manager->linkstack->pdisuse_top; i; i = v9[-1].pnext)
  {
    i[1].klass = 0;
    v9 = i + 1;
  }
  v10 = Allocate(dds3ProcessFunc_t);
  _ctor(v10, 0, Method_Project_itf_CalcManagerProc__, 0);
  dds3StartProcess("ItfMesCalc", 1032, 0, 0, v10, 0, 0);
  v11 = Allocate(dds3ProcessFunc_t);
  _ctor(v11, 0, Method_Project_itf_DrawManagerProc__, 0);
  dds3StartProcess("ItfMesDraw", 11032, 0, 0, v11, 0, 0);
  tmMsgWndOwner = txtMgr->tmMsgWndOwner;
  MsgWndOwner = tmMsgWndOwner;
  tmSpeakerTMP = txtMgr->tmSpeakerTMP;
  SpkWndTMP = tmSpeakerTMP;
  itfMesMngObjectInitialize();
  if (meswin_type)
    v20 = 22;
  else
    v20 = 1;
  Item = _get_Item(MsgWndTMP, v20);
  InitializeWordwrap(Item);
  itfPartVoiceLoad();
}

// 0x1c67c70
void itfMesMngSetBitStatManager(s32 flags) {
  s16 v2;

  v2 = flags;
  g_manager->stat |= v2;
}

// 0x1c67cf0
void itfMesMngClearBitStatManager(s32 flags) {
  s16 v2;

  v2 = flags;
  g_manager->stat &= ~v2;
}

// 0x1c67d70
s32 itfMesMngGetStatManager(void) {
  return g_manager->stat;
}

// 0x1c67e00
dds3ProcessFunc_t itfMesMngDebugProc(dds3ProcessID_t *proc_id) {
  u8 *v2;
  mesflow_tag *v3;
  Il2CppClass ***v4;
  u16 *v5;
  debug_tag *g_debug_local;
  mesflow_tag *p_pmesflow;
  mesflow_tag *pmesflow;
  s64 naturalAligment;
  mesflow_tag *v14;
  debug_tag *v17;
  window_tag *window;
  s32 mode;
  debug_tag *v21;
  s32 v22;
  s32 v23;
  s32 v26;
  bool v27;
  debug_tag *v30;
  u32 cursor;
  bool v32;
  mesflow_tag *v33;
  mesflow_tag *v34;
  mesflow_tag *v35;
  mesflow_tag *v36;

  v2 = NewSpecific(byte, 5u);
  v3 = "LEFT-TOP";
  if (!"LEFT-TOP")
    goto LABEL_86;
  v4 = off_4EE5828;
  if ("LEFT-TOP"->klass->_1.element_class != *((Il2CppClass **)*off_4EE5828 + 8))
    goto LABEL_85;
  v2[32] = *(u8 *)Unbox("LEFT-TOP");
  v3 = "RIGHT-BOTTOM";
  if (!"RIGHT-BOTTOM")
    goto LABEL_86;
  if ("RIGHT-BOTTOM"->klass->_1.element_class != (*v4)[8])
    goto LABEL_85;
  v2[33] = *(u8 *)Unbox("RIGHT-BOTTOM");
  v3 = "POSITION";
  if (!"POSITION")
    goto LABEL_86;
  if ("POSITION"->klass->_1.element_class != (*v4)[8])
    goto LABEL_85;
  v2[34] = *(u8 *)Unbox("POSITION");
  v3 = "ALPHA";
  if (!"ALPHA")
    goto LABEL_86;
  if ("ALPHA"->klass->_1.element_class != (*v4)[8])
    goto LABEL_85;
  v2[35] = *(u8 *)Unbox("ALPHA");
  v3 = "CHANGE INSTANCE";
  if (!"CHANGE INSTANCE")
    goto LABEL_86;
  if ("CHANGE INSTANCE"->klass->_1.element_class != (*v4)[8])
    goto LABEL_85;
  v2[36] = *(u8 *)Unbox("CHANGE INSTANCE");
  v5 = NewSpecific(char, 2u);
  v3 = "> ";
  if (!"> ")
    goto LABEL_86;
  v5[0] = *(u16 *)Unbox("> ");
  v3 = "* ";
  if (!"* ")
  {
LABEL_86:
    v36 = ((s64 (*)(void))loc_3BDC60)();
    return (dds3ProcessFunc_t)DebugChangeInstance(v36);
  }
  v5[1] = *(u16 *)Unbox("* ");
  g_debug_local = g_debug;
  if (g_debug_local->pmesflow)
    goto LABEL_34;
  v3 = 0;
  p_pmesflow = &g_debug_local->pmesflow;
  goto LABEL_26;
  if (pmesflow)
  {
    if (v3->klass->_2.naturalAligment < (u32)naturalAligment || v3->klass->_2.typeHierarchy[naturalAligment - 1] != mesflow_tag)
    {
LABEL_85:
    }
  }
LABEL_26:
  v14 = DebugChangeInstance(v3);
  if (!v14)
  {
    p_pmesflow = 0;
  }
  if (!g_debug->pmesflow)
    return 0;
LABEL_34:
  v17 = g_debug;
  window = v17->pmesflow->pinst->window;
  mode = v17->mode;
  switch (mode)
  {
    case 2:
      DebugMoveWinAlpha(window);
      if (!CHECK_TRIG(4097, 0))
        break;
LABEL_53:
      g_debug->mode = 0;
      break;
    case 1:
      v17 = g_debug;
      DebugMoveWinVert(window, v17->cursor);
      if (!CHECK_TRIG(4097, 0))
        break;
      goto LABEL_53;
    case 0:
      if (CHECK_REP(4100, 0))
      {
        v21 = g_debug;
        v22 = v21->cursor - 1;
        v21->cursor = v22;
        if (v22 < 0)
        {
          v23 = 2;
LABEL_45:
          v21->cursor = v23;
          goto LABEL_66;
        }
      }
      else if (CHECK_REP(4101, 0))
      {
        v21 = g_debug;
        v26 = v21->cursor + 1;
        v27 = v21->cursor - 4 < 0;
        v21->cursor = v26;
        if (v27 == __OFSUB__(v26, 5))
        {
          v23 = 0;
          goto LABEL_45;
        }
      }
LABEL_66:
      if (!CHECK_TRIG(4096, 0))
      {
        if (CHECK_TRIG(4097, 0))
          return 0;
        break;
      }
      v30 = g_debug;
      cursor = v30->cursor;
      v32 = cursor == 3;
      if (cursor < 3)
      {
        v30 = g_debug;
        v30->mode = 1;
        break;
      }
      if (v32)
      {
        v30 = g_debug;
        v30->mode = 2;
      }
      else if (cursor == 4)
      {
        v30 = g_debug;
        v34 = v30->pmesflow;
        v33 = &v30->pmesflow;
        v35 = DebugChangeInstance(v34);
        v33 = v35;
      }
      break;
  }
  dds3ConsPanelTagLink(0, 16, 16, 30, 9);
  return 0;
}

// 0x1c689a0
void itfMesMngDebugShutdown(dds3ProcessID_t *proc_id) {
  debug_tag *g_debug_local;

  g_debug_local = g_debug;
  g_debug_local->pmesflow = 0;
  g_debug_local = ((char *)g_debug_local + 24);
  g_debug_local[-1].pmesflow = 0;
}

// 0x1c68a10
FontReq_t *GetLastLinkFontHandle(FontReq_t *pfont) {
  FontReq_t *v2;

  do
  {
    v2 = pfont;
    pfont = pfont->prev;
  }
  while (pfont);
  return v2;
}

// 0x1c68a30
static void GetLastMessagePara(FontReq_t *pfont, message_tag *pmessage) {
  Text_t *str_end;
  s32 v6;
  u8 col_no;

  if (pfont)
  {
    str_end = pfont->str_end;
    if (str_end)
    {
      v6 = pfont->draw_spd >> 1;
      col_no = str_end->col_no;
      pmessage->last_style = str_end->style;
      pmessage->last_col = col_no;
      pmessage->last_spd = v6;
      pmessage->last_tp = str_end->tp;
    }
  }
}

// 0x1c68ac0
static s32 CountLineMessage(FontReq_t *pfont_top, FontReq_t *pfont) {
  u64 v3;

  v3 = 715827883 * ((pfont->y - pfont_top->y) >> 3);
  return (v3 >> 63) + (SHIDWORD(v3) >> 2) + 1;
}

// 0x1c5f280
static void CalcSelect(instanceMes_tag *pinst) {
  select_tag *select;
  message_tag *message;
  u32 stat;
  FontReq_t *pfont;
  Text_t *i;
  FontReq_t *v10;
  s32 v11;
  s32 lines;
  FontReq_t *v13;
  s32 v15;
  u32 mask;
  s16 MaskedIndex;
  curctr_tag *curctr;
  s16 v19;
  s32 v20;
  FontReq_t *prev;
  s32 v26;
  bool v27;
  curctr_tag *v28;
  Text_t *j;

  select = pinst->select;
  message = pinst->message;
  stat = pinst->stat;
  switch (select->phase)
  {
    case 1:
      if ((pinst->stat & 0xC00) != 0x400)
      {
        pfont = message->pfont;
        if (pfont)
        {
          do
          {
            for (i = pfont->str; i; i = i->next)
              i->col_no = 3;
            pfont = pfont->prev;
          }
          while (pfont);
          stat = pinst->stat;
        }
        pinst->stat = stat & 0xFFFFFFC7;
        select->phase = 5;
        SelectWait = 0;
      }
      return;
    case 2:
      if ((pinst->stat & 0x38) == 0x20)
      {
        if (SelectItem(pinst))
        {
          v10 = select->pfont;
          v11 = select->select;
          lines = select->lines;
          v13 = UnchainFontHandleUnit(v10, v11, lines);
          select->pfont = v13;
          if ((stat & 0xC00) == 0x800)
            pinst->stat |= 0xC00u;
          v15 = select->select;
          mask = select->mask;
          MaskedIndex = GetMaskedIndex(v15, mask);
          curctr = pinst->curctr;
          select->select = MaskedIndex;
          *(u32 *)&curctr->phase = 8323073;
          curctr->ctr1 = 0;
          pinst->stat = pinst->stat & 0xFFFFFFC7 | 0x28;
          *(u32 *)&select->alpha = 128;
          v19 = 3;
          goto LABEL_49;
        }
      }
      return;
    case 3:
      v20 = (u16)select->alpha - 16;
      select->alpha -= 16;
      if (v20 << 16 <= 0)
      {
        v28 = pinst->curctr;
        select->alpha = 0;
        select->phase = 4;
        *(u32 *)&v28->lf_wait = 0;
        v28->isdraw = 0;
        v28->cut_wait = 0;
        v28->ctr_key = 0;
        *(u64 *)&v28->phase = 0x8000000000LL;
        LOWORD(v20) = select->alpha;
        prev = select->pfont;
LABEL_26:
        if (!prev)
          return;
        goto LABEL_40;
      }
      else
      {
        prev = select->pfont;
        goto LABEL_26;
      }
      if (!prev)
        return;
      do
      {
LABEL_40:
        for (j = prev->str; j; j = j->next)
          j->color = j->color & 0xFFFFFF00 | (s16)v20;
        prev = prev->prev;
      }
      while (prev);
      return;
    case 4:
      if (!message->pfont || get_Item((sdfIVector2_t)&message->fields, 1, 0) > 6317)
      {
        v19 = -1;
        goto LABEL_49;
      }
      SlideUpDownMessage(pinst, 144);
      return;
    case 5:
      v26 = SelectWait + 1;
      v27 = SelectWait - 29 < 0;
      SelectWait = v26;
      if (v27 ^ __OFSUB__(v26, 30) | (v26 == 30))
      {
        if (!SelectWaitCancelCheck())
          return;
      }
      pinst->stat |= 0x18u;
      v19 = 2;
LABEL_49:
      select->phase = v19;
      return;
    default:
      return;
  }
}

// 0x1c69020
static bool SelectWaitCancelCheck(void) {
  return CHECK_TRIG(4096, 1)
      || CHECK_TRIG(4097, 1)
      || CHECK_TRIG(4098, 1)
      || CHECK_TRIG(4099, 1)
      || CHECK_TRIG(4107, 1)
      || CHECK_TRIG(4108, 1)
      || CHECK_TRIG(4104, 1)
      || CHECK_TRIG(4105, 1)
      || CHECK_TRIG(4111, 1)
      || CHECK_TRIG(4110, 1);
}

// 0x1c68e90
static void SlideUpDownMessage(instanceMes_tag *pinst, s32 y) {
  Speaker_tag *speaker;
  message_tag *message;
  window_tag *window;
  s32 Item;
  FontReq_t *pfont;
  itfpanel_t *mes;
  itfpanel_t *spk;
  s32 v13;
  FontReq_t *prev;

  speaker = pinst->speaker;
  message = pinst->message;
  window = pinst->window;
  Item = get_Item((sdfIVector2_t)&message->fields, 1, 0);
  set_Item((sdfIVector2_t)&message->fields, 1, Item + y, 0);
  pfont = message->pfont;
  if (!pfont)
    goto LABEL_6;
  do
  {
    pfont->y += y;
    pfont = pfont->prev;
  }
  while (pfont);
LABEL_6:
  mes = window->mes;
  if (mes)
  {
    itfPnlSetPositionOffset(mes, 0, y, 0, 0, 0);
  }
  spk = window->spk;
  if (spk)
  {
    itfPnlSetPositionOffset(spk, 0, y, 0, y, 0);
  }
  if (speaker->pfont)
  {
    v13 = get_Item((sdfIVector2_t)&speaker->fields, 1, 0);
    set_Item((sdfIVector2_t)&speaker->fields, 1, v13 + y, 0);
    prev = speaker->pfont;
    if (!prev)
      return;
    do
    {
      prev->y += y;
      prev = prev->prev;
    }
    while (prev);
  }
}

// 0x1c68af0
static bool SelectItem(instanceMes_tag *pinst) {
  select_tag *select;
  s32 v5;
  curctr_tag *curctr;
  s32 v11;
  s16 cancelNum;
  s64 v15;
  s32 v16;
  defkey_tag *v17;
  s32 index;
  u32 mask;
  u32 v20;
  _BOOL4 v21;
  s32 v22;
  _BOOL4 v23;
  s32 i;
  s32 v25;
  s32 v26;
  s32 v28;

  select = pinst->select;
  if (CHECK_REP(4100, 1))
  {
    if (select->select)
    {
      v5 = -1;
LABEL_14:
      SelectItemMove(select, v5);
      curctr = pinst->curctr;
      curctr->cut_wait = 0;
      curctr->ctr_key = 0;
      *(u64 *)&curctr->phase = 0x8000000000LL;
      goto LABEL_15;
    }
    if (!CHECK_TRIG(4100, 1))
      goto LABEL_15;
    v5 = -1;
    goto LABEL_13;
  }
  if (!CHECK_REP(4101, 1))
    goto LABEL_15;
  if (select->lines - 1 != select->select)
  {
    v5 = 1;
    goto LABEL_14;
  }
  v5 = 1;
  if (CHECK_TRIG(4101, 1))
  {
LABEL_13:
    goto LABEL_14;
  }
LABEL_15:
  if (CHECK_TRIG(4096, 1))
  {
    if (SelectYesSe >= 1)
    {
      if (!select->select)
      {
        v26 = SelectYesSe;
        goto LABEL_48;
      }
    }
    v26 = 0;
LABEL_48:
    SE(v26);
    return 1;
  }
  if (select->cancelNum < 0 || !CHECK_TRIG(4097, 1))
  {
    if (select->numdef < 1)
      return 0;
    if (select->numdef < 1)
      return 0;
    v15 = 0;
    while (1)
    {
      v17 = select->defkey[v15];
      if (CHECK_TRIG(v17->key, 1))
      {
        index = v17->index;
        mask = select->mask;
        if (index < 1)
        {
          v16 = 0;
        }
        else
        {
          if ((u32)index >= 4)
          {
            v16 = 0;
            v20 = index & 0xFFFFFFFC;
            do
            {
              v20 -= 4;
              v21 = ((mask >> 3) & 1) == 0;
              v22 = (((mask >> 1) & 1) == 0) + ((mask & 1) == 0) + v16;
              v23 = ((mask >> 2) & 1) == 0;
              mask >>= 4;
              v16 = v21 + v23 + v22;
            }
            while (v20);
          }
          else
          {
            v16 = 0;
          }
          for (i = index & 3; i; v16 += v25)
          {
            v25 = (mask & 1) == 0;
            mask >>= 1;
            --i;
          }
        }
        if ((mask & 1) == 0)
          break;
      }
      if (++v15 >= select->numdef)
        return 0;
    }
    if (v16 < 0)
    {
      return 0;
    }
    else
    {
      SE(0);
      v28 = select->select;
      if (v16 == v28)
        return 1;
      ChangeSelection(v28, 0);
      ChangeSelection(v16, 1);
      select->select = v16;
      select->select_imm = v16;
      return 1;
    }
  }
  else
  {
    SE(1);
    v11 = select->select;
    ChangeSelection(v11, 0);
    ChangeSelection(select->cancelNum, 1);
    cancelNum = select->cancelNum;
    select->select = cancelNum;
    select->select_imm = cancelNum;
    return 1;
  }
}

// 0x1c69100
static void SelectItemMove(select_tag *psel, s32 direct) {
  s32 select;
  s32 v8;

  select = psel->select;
  ChangeSelection(select, 0);
  if ((direct & 0x80000000) == 0)
  {
    if (select + 1 < psel->lines)
      v8 = select + 1;
    else
      v8 = 0;
    goto LABEL_14;
  }
  if (select <= 0)
  {
    v8 = psel->lines - 1;
    goto LABEL_14;
  }
  v8 = select - 1;
LABEL_14:
  ChangeSelection(v8, 1);
  psel->select = v8;
  psel->select_imm = v8;
  SE(4);
}

// 0x1c69210
static s32 SelectItemDefKey(select_tag *psel) {
  s64 v3;
  s32 result;
  defkey_tag *v5;
  s32 index;
  u32 mask;
  u32 v8;
  _BOOL4 v9;
  s32 v10;
  _BOOL4 v11;
  s32 i;
  s32 v13;

  if (psel->numdef < 1)
    return -1;
  v3 = 0;
  while (1)
  {
    v5 = psel->defkey[v3];
    if (CHECK_TRIG(v5->key, 1))
    {
      index = v5->index;
      mask = psel->mask;
      if (index < 1)
      {
        result = 0;
      }
      else
      {
        if ((u32)index >= 4)
        {
          result = 0;
          v8 = index & 0xFFFFFFFC;
          do
          {
            v8 -= 4;
            v9 = ((mask >> 3) & 1) == 0;
            v10 = (((mask >> 1) & 1) == 0) + ((mask & 1) == 0) + result;
            v11 = ((mask >> 2) & 1) == 0;
            mask >>= 4;
            result = v9 + v11 + v10;
          }
          while (v8);
        }
        else
        {
          result = 0;
        }
        for (i = index & 3; i; result += v13)
        {
          v13 = (mask & 1) == 0;
          mask >>= 1;
          --i;
        }
      }
      if ((mask & 1) == 0)
        break;
    }
    if (++v3 >= psel->numdef)
      return -1;
  }
  return result;
}

// 0x1c5f640
static void CalcCurCtr(instanceMes_tag *pinst) {
  curctr_tag *curctr;
  s32 ctr1;
  s32 v4;
  s32 v5;

  curctr = pinst->curctr;
  if (curctr->isdraw)
  {
    ctr1 = curctr->ctr1;
    if (ctr1 >= 1)
      curctr->ctr1 = ctr1 - 8;
    if (curctr->phase == 1)
    {
      v5 = (s16)(curctr->ctr0 - 8);
      curctr->ctr0 -= 8;
      if (v5 <= 0)
        *(u32 *)&curctr->phase = 0;
    }
    else if (!curctr->phase)
    {
      v4 = (u16)curctr->ctr0 + 8;
      curctr->ctr0 = v4;
      if (v4 << 16 >= 16711680)
      {
        *(u32 *)&curctr->phase = 16711681;
        curctr->ctr1 = 128;
      }
    }
  }
}

// 0x1c69320
static void DrawMesFlow(instanceMes_tag *pinst) {
  u32 stat;
  FontReq_t *pfont;
  FontReq_t *v8;
  FontReq_t *v9;
  bool v10;
  curctr_tag *curctr;
  s32 wait;
  bool IsSelectWindowDispOn;
  select_tag *select;
  s32 v20;

  stat = pinst->stat;
  g_manager->stat &= ~2u;
  DrawWindow(pinst);
  if ((stat & 0x10000) == 0)
  {
    pfont = pinst->speaker->pfont;
    if (pfont)
    {
      if (!pinst->hojomes)
      {
        DrawSpeaker(pfont);
      }
    }
  }
  if ((stat & 0x20000) != 0 || (stat & 7) < 3)
    goto LABEL_28;
  v8 = pinst->message->pfont;
  v9 = pinst->speaker->pfont;
  if (DrawMessage(v8) < 1 || (pinst->stat & 7) == 4)
    goto LABEL_28;
  pinst->stat = pinst->stat & 0xFFFFFFF8 | 4;
  v10 = sndVoiceStatus(0);
  if (!v10)
  {
    bNowSpeaking = 3;
  }
  curctr = pinst->curctr;
  HIWORD(curctr->ctr_key) = 0;
  *(u64 *)&curctr->lf_wait = 0;
  wait = pinst->message->wait;
  if (op_Inequality(0, 0, 0))
    SetActive(0, wait != 0, 0);
LABEL_28:
  if ((stat & 0x40000) == 0 && (stat & 0x38) >= 0x18)
  {
    IsSelectWindowDispOn = IsSelectWindowDispOn();
    if ((stat & 0x3F) != 0x1C)
      goto LABEL_42;
    if (!IsSelectWindowDispOn)
      goto LABEL_42;
    select = pinst->select;
    v20 = (u16)select->select;
    if (v20 == 0xFFFF)
    {
      LOWORD(v20) = 0;
      *(u32 *)&select->select = 0;
      goto LABEL_41;
    }
    else
    {
LABEL_41:
      ChangeSelection((s16)v20, 1);
      pinst->stat = pinst->stat & 0xFFFFFFC7 | 0x20;
      pinst->curctr->isdraw = 2;
      goto LABEL_42;
    }
    goto LABEL_41;
  }
LABEL_42:
  if ((pinst->curctr->isdraw & 2) != 0)
    return;
  if ((pinst->curctr->isdraw & 1) == 0)
    goto LABEL_65;
  if (logdispwk->pmvrun == 1)
  {
LABEL_65:
    if ((pinst->stat & 7) == 3)
    {
      isMesWndGuideDisp = 1;
    }
    return;
  }
  if (lipsync_pm->script_auto_skip)
    goto LABEL_65;
  if (cfgGetConfigAUDIO(7, 0))
    goto LABEL_65;
  itf_cr_icon = 1;
}

// 0x1c698f0
static void DrawSpeaker(FontReq_t *pfont) {
  char *v5;

  if (!pfont)
    return;
  v5 = sub_1C88420(pfont, 0);
  if (!IsNullOrEmpty(v5, 0))
    (SpkWndTMP->klass->vtable._66_set_text.methodPtr)(SpkWndTMP, v5, SpkWndTMP->klass->vtable._66_set_text.method);
}

// 0x1c3ec80
static void DrawSpeakerSub(FontReq_t *pfont, void *txt) {
  char *v5;

  if (pfont)
  {
    v5 = sub_1C88420(pfont, 0);
    if (!IsNullOrEmpty(v5, 0))
      (txt->klass->vtable._66_set_text.methodPtr)(txt, v5, txt->klass->vtable._66_set_text.method);
  }
}

// 0x1c69a00
static s32 DrawMessage(FontReq_t *pfont, FontReq_t *pSpeaker) {
  s32 v7;
  Il2CppObject *Item;

  if (meswin_type)
    v7 = 22;
  else
    v7 = 1;
  Item = _get_Item(MsgWndTMP, v7);
  return DrawMessageSub(pfont, pSpeaker, Item, 0);
}

// 0x1c3e270
static s32 DrawMessageSub(FontReq_t *pfont, FontReq_t *pSpeaker, void *txt, bool logmsg) {
  FontReq_t *head;
  char *v9;
  bool IsNullOrEmpty;
  s32 v13;
  char v15;
  Text_t *str;
  s32 y;
  u8 draw_spd;
  u32 *p_color;
  u32 v22;
  u32 v23;
  bool v24;
  Il2CppObject *v28;
  char *v29;
  s32 v34;
  u32 v35;
  void *v37;
  Il2CppObject *v38;
  char *v39;
  s32 font_id;
  char **v42;
  char *v44;
  char *tag_id;
  char *v46;
  char v48;
  s32 v52;
  char *v53;
  s32 v55;
  s32 v56;
  void *v59;
  char *g_replace_text_local;
  s32 v61;
  s32 v65;
  char *v66;
  char *v69;
  void *v70;
  s32 v71;
  char *v72;
  s32 v74;
  char v75;
  FontReq_t *v76;
  u64 v77;
  s32 data;

  if (!pfont)
    return 0;
  head = pfont->head;
  v9 = sub_1C88420(head, 0);
  IsNullOrEmpty = IsNullOrEmpty(v9, 0);
  if (IsNullOrEmpty)
  {
    return 0;
  }
  v70 = txt;
  v76 = pfont;
  Clear(pMsgMes);
  v71 = 0;
  v74 = 0;
  v13 = 1;
  v72 = "";
  lipsync_pm->tlen = 0;
  while (2)
  {
    v15 = 0;
    while (2)
    {
      if (!head)
      {
LABEL_125:
        v59 = v70;
        g_replace_text_local = v72;
        v61 = v71;
        goto LABEL_127;
      }
LABEL_15:
      str = head->str;
      v75 = v15;
      while (1)
      {
        y = head->y;
        if (!IsNullOrEmpty(lipsync_pm->voice_name, 0))
        {
          if (!scrIsEventSkip(0))
            goto LABEL_30;
        }
        if (pSpeaker)
        {
          if (!scrIsEventSkip(0))
            goto LABEL_30;
        }
        head->draw_spd = 0x80;
LABEL_30:
        if (v13 != 1 && str->wait <= 0)
        {
          p_color = &str->color;
          v13 &= SLOBYTE(str->color) >> 7;
          if (str->font_id != 2)
            goto LABEL_43;
LABEL_40:
          Append_56602800(pMsgMes, "<i>", 0);
          goto LABEL_43;
        }
        draw_spd = head->draw_spd;
        frDrawEffect(head, str, 0x1Cu, draw_spd);
        p_color = &str->color;
        v13 &= SLOBYTE(str->color) >> 7;
        if (str->wait >= 1)
        {
          if (!scrIsEventSkip(0))
            v13 = 0;
        }
        if (str->font_id == 2)
          goto LABEL_40;
LABEL_43:
        v22 = *p_color;
        v23 = (u8)*p_color;
        v24 = v23 >= 0x80;
        if (v23 != 128)
          break;
        v22 = *p_color;
        data = v22 | 0xFF;
        v28 = Box(uint, &data);
        v29 = Format("<color=#{0:X8}>", v28, 0);
        Append_56602800(pMsgMes, v29, 0);
        chcode = str->chcode;
        if ((u32)chcode != 32 || head->next || str->next)
        {
          LOWORD() = str->chcode;
          Append_56602736(pMsgMes, (u16)0);
        }
        ++lipsync_pm->tlen;
        if (str->wait >= 1)
          goto LABEL_99;
LABEL_62:
        font_id = str->font_id;
        if (font_id == -1)
        {
          v42 = &"</i>";
LABEL_69:
          Append_56602800(pMsgMes, *v42, 0);
          font_id = str->font_id;
          goto LABEL_70;
        }
        if (font_id)
        {
          if (font_id != 1)
          {
LABEL_70:
            if (font_id >= 10 && *(u8 *)p_color == 128)
            {
              v44 = itfTextSetSprite(font_id);
              tag_id = v76->tag_id;
              v46 = itfSystemTextBtnConvert(v44, tag_id);
              if (!IsNullOrEmpty(v46, 0))
              {
                Append_56602800(pMsgMes, v46, 0);
              }
            }
            goto LABEL_17;
          }
          v42 = &"<i>";
          goto LABEL_69;
        }
LABEL_17:
        str = str->next;
        if (!str)
        {
          head = head->next;
          v48 = v75;
          if ((v75 & 1) == 0)
          {
            if (!head)
              goto LABEL_125;
            v15 = 0;
            if (y == head->y)
              goto LABEL_15;
          }
          goto LABEL_87;
        }
      }
      v34 = 2 * v23;
      if (v24)
        v35 = 255;
      else
        v35 = v34;
      v22 = *p_color;
      v77 = (v22 & 0xFFFFFF00) + (u64)v35;
      v37 = pMsgMes;
      v38 = Box(long, &v77);
      v39 = Format("<color=#{0:X8}>", v38, 0);
      Append_56602800(v37, v39, 0);
      Append_56602736(pMsgMes, str->0);
      if (str->wait < 1)
        goto LABEL_62;
LABEL_99:
      head = head->next;
      v48 = 1;
LABEL_87:
      if (meswin_type)
        v52 = 4;
      else
        v52 = 3;
      if (v74 < v52)
      {
        v53 = (pMsgMes->klass->vtable._3_ToString.methodPtr)(pMsgMes, pMsgMes->klass->vtable._3_ToString.method);
        v72 = Replace_54838864(v53, "\t", "", 0);
        v71 = 1;
      }
      if ((v48 & 1) != 0)
      {
        v15 = 1;
        if (!logmsg)
        {
          ++v74;
          goto LABEL_148;
        }
        continue;
      }
      break;
    }
    v55 = ++v74;
    if (meswin_type)
      v56 = 4;
    else
      v56 = 3;
    if (v55 != v56)
    {
      goto LABEL_112;
LABEL_113:
      if (!logdispwk->pmvrun)
        goto LABEL_122;
      if (!head->next)
        continue;
      goto LABEL_122;
LABEL_112:
      goto LABEL_113;
LABEL_122:
      Append_56602800(pMsgMes, "\n", 0);
      continue;
    }
    break;
  }
LABEL_148:
  v59 = v70;
  g_replace_text_local = v72;
  v61 = v71;
LABEL_127:
  if (get_Length(pMsgMes, 0))
  {
    if (meswin_type)
      v65 = 4;
    else
      v65 = 3;
    if (v74 < v65)
    {
      v66 = (pMsgMes->klass->vtable._3_ToString.methodPtr)(pMsgMes, pMsgMes->klass->vtable._3_ToString.method);
      g_replace_text_local = Replace_54838864(v66, "\t", "", 0);
      v61 = 2;
    }
    Clear(pMsgMes);
  }
  if (v61)
  {
    if (g_replace_text)
    {
      g_replace_text_local = g_replace_text;
      g_replace_text = 0;
    }
    v69 = (v59->klass->vtable._65_get_text.methodPtr)(v59, v59->klass->vtable._65_get_text.method);
    if (!Equals_54828784(v69, g_replace_text_local, 0))
      (v59->klass->vtable._66_set_text.methodPtr)(v59, g_replace_text_local, v59->klass->vtable._66_set_text.method);
  }
  return v13;
}

// 0x1c69b20
static s32 DrawSelection(u32 stat) {
  char v2;

  v2 = stat;
  return ((v2 & 7) == 4) & IsSelectWindowDispOn();
}

// 0x1c697a0
static void DrawWindow(instanceMes_tag *pinst) {
  u32 stat;
  window_tag *window;
  struct itf *static_fields;
  mesflow_tag *pmesflow;
  itfpanel_t *mes;
  itfpanel_t *v12;

  stat = pinst->stat;
  if ((stat & 0x80000) != 0)
    return;
  window = pinst->window;
  if ((stat & 0x300) != 0)
  {
    LODWORD(static_fields) = isMesWndBaseDisp;
    g_manager->stat |= 2u;
  }
  pmesflow = g_debug->pmesflow;
  if (!pmesflow)
    return;
  if (pmesflow->pinst == pinst && window != 0)
  {
    mes = window->mes;
    v12 = window->mes;
    DebugDrawWindowLine(v12);
  }
}

// 0x1c69df0
static void DrawSelectCursor(instanceMes_tag *pinst) {
  u64 *v3;
  sdfIVector2_t v4;
  sdfIVector2_t v5;
  sdfIVector2_t v6;
  sdfIVector2_t v7;
  sdfIVector4_t *v8;
  void *v11;
  u8 *v12;
  select_tag *select;
  s32 select_imm;
  sdfDrawTag_t *v15;
  s32 Item;
  s32 v17;
  s32 v18;
  f32 v20;
  f32 v21;
  s32 v22;
  s32 v23;
  u32 v24;
  s32 v25;
  s32 v27;
  s32 v30;
  sdfDrawTag_t *v36;
  s32 v37;
  s32 v38;
  s32 v39;
  sdfDrawTag_t *v40;
  s32 v44;
  s32 v47;
  sdfDrawTag_t *v57;
  s32 v59;
  s32 v62;
  sdfDrawTag_t *v69;
  s32 ctr1;
  s32 v72;
  s32 v75;
  s32 v76;
  s32 v79;
  s32 v82;
  curctr_tag *curctr;
  __int128 v86;
  __int128 v87;
  s64 v88;
  s64 v89;
  s64 v90;
  s64 v91;
  u64 v92[2];
  u64 v93[2];
  u64 v94[2];
  sdfIVector4_t v95;
  sdfIVector4_t v96;
  sdfIVector4_t v97;
  sdfIVector4_t v98;
  sdfIVector4_t v99;
  sdfIVector4_t v100;
  sdfIVector4_t v101;
  sdfIVector4_t v102;
  sdfIVector4_t v103;
  sdfIVector4_t v104;
  sdfIVector4_t v105;
  sdfIVector4_t v106;
  sdfIVector4_t v107;
  sdfIVector4_t v108;
  sdfIVector4_t v109;
  sdfIVector4_t v110;
  sdfIVector4_t v111;
  sdfIVector4_t v112;
  sdfIVector4_t v113;
  sdfIVector4_t v114;
  sdfIVector4_t v115;
  sdfIVector4_t v116;
  sdfIVector4_t v117;
  sdfIVector4_t v118;
  sdfIVector4_t v119;
  sdfIVector4_t v120;
  sdfIVector4_t v121;
  sdfIVector4_t v122;
  sdfIVector4_t v123;
  sdfIVector4_t v124;
  sdfIVector4_t v125;
  sdfIVector4_t v126;
  sdfIVector4_t v127;
  sdfIVector4_t v128;
  sdfIVector4_t v129;
  sdfIVector4_t v130;
  sdfIVector4_t v131;
  sdfIVector4_t v132;
  sdfIVector4_t v133;
  sdfIVector4_t v134;
  sdfIVector4_t v135;
  sdfIVector4_t v136;
  sdfIVector4_t v137;

  v3 = NewSpecific(sdfIVector2_t, 4u);
  v91 = 0;
  _ctor((sdfIVector2_t)&v91, 7728, 6768, 0);
  v3[4] = v91;
  v4 = (sdfIVector2_t)(v3 + 4);
  v90 = 0;
  _ctor((sdfIVector2_t)&v90, 11696, 6768, 0);
  v3[5] = v90;
  v5 = (sdfIVector2_t)(v3 + 5);
  v89 = 0;
  _ctor((sdfIVector2_t)&v89, 11696, 7160, 0);
  v3[6] = v89;
  v6 = (sdfIVector2_t)(v3 + 6);
  v88 = 0;
  _ctor((sdfIVector2_t)&v88, 7728, 7160, 0);
  v3[7] = v88;
  v7 = (sdfIVector2_t)(v3 + 7);
  v8 = NewSpecific(sdfIVector4_t, 2u);
  *(u64 *)&v95.x = &v87;
  *(u64 *)&v95.z = 87;
  v87 = 0u;
  _ctor(v95, 0, 16, 0, 0);
  *(u64 *)&v96.x = &v86;
  *(u64 *)&v96.z = 87;
  *(_OWORD *)&v8[0] = v87;
  v86 = 0u;
  _ctor(v96, 0, 16, 38, 0);
  *(_OWORD *)&v8[1] = v86;
  v11 = NewSpecific(byte, 4u);
  InitializeArray_55364416(v11, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__054EDEC1D0211F624FED0CBCA9D4F9400B0E491C43742AF2C5B0ABEBF0C990D8, 0);
  v12 = NewSpecific(byte, 4u);
  v12[0] = 1;
  v12[3] = 1;
  select = pinst->select;
  select_imm = (u16)select->select_imm;
  v94[0] = 0;
  v94[1] = 0;
  v93[0] = 0;
  v93[1] = 0;
  v92[0] = 0;
  v92[1] = 0;
  if (select_imm != 0xFFFF)
  {
    curctr = pinst->curctr;
    v15 = Allocate(sdfDrawTag_t);
    _ctor(v15, 0);
    sdfDrawTagInit(v15);
    Item = get_Item((sdfIVector2_t)&select->fields, 0, 0);
    v17 = Item - 1248;
    v18 = get_Item((sdfIVector2_t)&select->fields, 1, 0);
    v20 = (f32)(25 * select->lines - 16) * 2.25;
    v21 = (f32)((f32)(s16)select_imm * 22.0) * 2.25;
    v22 = 8 * (s32)v20;
    if (v20 == INFINITY)
      v22 = 0;
    v23 = v18 - v22;
    v24 = vcvts_n_s32_f32(v21, 3u);
    if ((f32)(v21 * 8.0) == INFINITY)
      v24 = 0x80000000;
    v25 = v23 + v24;
    *(u64 *)&v137.x = v92;
    *(u64 *)&v137.z = 0;
    set_Item(v137, Item - 896, 0);
    *(u64 *)&v97.x = v92;
    *(u64 *)&v97.z = 1;
    set_Item(v97, v25, 0);
    v27 = 2 * get_Item(v4, 0, 0);
    *(u64 *)&v98.x = v92;
    *(u64 *)&v98.z = 2;
    set_Item(v98, v27, 0);
    *(u64 *)&v99.x = v92;
    *(u64 *)&v99.z = 1;
    v30 = get_Item(v99, 0) + 448;
    *(u64 *)&v100.x = v92;
    *(u64 *)&v100.z = 3;
    set_Item(v100, v30, 0);
    *(u64 *)&v101.x = v93;
    *(u64 *)&v101.z = 0;
    set_Item(v101, 87, 0);
    *(u64 *)&v102.x = v93;
    *(u64 *)&v102.z = 1;
    set_Item(v102, 0, 0);
    *(u64 *)&v103.x = v93;
    *(u64 *)&v103.z = 2;
    set_Item(v103, 16, 0);
    *(u64 *)&v104.x = v93;
    *(u64 *)&v104.z = 3;
    set_Item(v104, 76, 0);
    v36 = Allocate(sdfDrawTag_t);
    _ctor(v36, 0);
    sdfDrawTagInit(v36);
    set_Item(v4, 1, v25 - 16, 0);
    v37 = get_Item(v4, 1, 0);
    set_Item(v5, 1, v37, 0);
    v38 = get_Item(v4, 1, 0);
    set_Item(v6, 1, v38 + 392, 0);
    v39 = get_Item(v6, 1, 0);
    set_Item(v7, 1, v39, 0);
    v40 = Allocate(sdfDrawTag_t);
    _ctor(v40, 0);
    sdfDrawTagInit(v40);
    *(u64 *)&v105.x = v92;
    *(u64 *)&v105.z = 0;
    set_Item(v105, v17, 0);
    *(u64 *)&v106.x = v92;
    *(u64 *)&v106.z = 1;
    set_Item(v106, v25 + 16, 0);
    *(u64 *)&v107.x = v92;
    *(u64 *)&v107.z = 0;
    v44 = get_Item(v107, 0) + 352;
    *(u64 *)&v108.x = v92;
    *(u64 *)&v108.z = 2;
    set_Item(v108, v44, 0);
    *(u64 *)&v109.x = v92;
    *(u64 *)&v109.z = 1;
    v47 = get_Item(v109, 0) + 288;
    *(u64 *)&v110.x = v92;
    *(u64 *)&v110.z = 3;
    set_Item(v110, v47, 0);
    *(u64 *)&v111.x = v94;
    *(u64 *)&v111.z = 0;
    set_Item(v111, 1248, 0);
    *(u64 *)&v112.x = v94;
    *(u64 *)&v112.z = 1;
    set_Item(v112, 2816, 0);
    *(u64 *)&v113.x = v94;
    *(u64 *)&v113.z = 2;
    set_Item(v113, 1616, 0);
    *(u64 *)&v114.x = v94;
    *(u64 *)&v114.z = 3;
    set_Item(v114, 3776, 0);
    *(u64 *)&v115.x = v93;
    *(u64 *)&v115.z = 0;
    set_Item(v115, 128, 0);
    *(u64 *)&v116.x = v93;
    *(u64 *)&v116.z = 1;
    set_Item(v116, 128, 0);
    *(u64 *)&v117.x = v93;
    *(u64 *)&v117.z = 2;
    set_Item(v117, 128, 0);
    *(u64 *)&v118.x = v93;
    *(u64 *)&v118.z = 3;
    set_Item(v118, 38, 0);
    v57 = Allocate(sdfDrawTag_t);
    _ctor(v57, 0);
    sdfDrawTagInit(v57);
    *(u64 *)&v119.x = v92;
    *(u64 *)&v119.z = 0;
    v59 = get_Item(v119, 0) + 960;
    *(u64 *)&v120.x = v92;
    *(u64 *)&v120.z = 2;
    set_Item(v120, v59, 0);
    *(u64 *)&v121.x = v92;
    *(u64 *)&v121.z = 1;
    v62 = get_Item(v121, 0) + 432;
    *(u64 *)&v122.x = v92;
    *(u64 *)&v122.z = 3;
    set_Item(v122, v62, 0);
    *(u64 *)&v123.x = v94;
    *(u64 *)&v123.z = 0;
    set_Item(v123, 2272, 0);
    *(u64 *)&v124.x = v94;
    *(u64 *)&v124.z = 1;
    set_Item(v124, 2816, 0);
    *(u64 *)&v125.x = v94;
    *(u64 *)&v125.z = 2;
    set_Item(v125, 3232, 0);
    *(u64 *)&v126.x = v94;
    *(u64 *)&v126.z = 3;
    set_Item(v126, 3776, 0);
    *(u64 *)&v127.x = v93;
    *(u64 *)&v127.z = 3;
    set_Item(v127, curctr->ctr0, 0);
    v69 = Allocate(sdfDrawTag_t);
    _ctor(v69, 0);
    sdfDrawTagInit(v69);
    if (curctr->ctr1 >= 1)
    {
      ctr1 = (u16)curctr->ctr1;
      *(u64 *)&v128.x = v92;
      *(u64 *)&v128.z = 0;
      v72 = get_Item(v128, 0) - (128 - ctr1);
      *(u64 *)&v129.x = v92;
      *(u64 *)&v129.z = 0;
      set_Item(v129, v72, 0);
      *(u64 *)&v130.x = v92;
      *(u64 *)&v130.z = 1;
      v75 = get_Item(v130, 0);
      *(u64 *)&v131.z = 1;
      v76 = v75 - ((128 - ctr1) >> 1);
      *(u64 *)&v131.x = v92;
      set_Item(v131, v76, 0);
      *(u64 *)&v132.x = v92;
      *(u64 *)&v132.z = 2;
      v79 = get_Item(v132, 0) + 2 * (128 - ctr1);
      *(u64 *)&v133.x = v92;
      *(u64 *)&v133.z = 2;
      set_Item(v133, v79, 0);
      *(u64 *)&v134.x = v92;
      *(u64 *)&v134.z = 3;
      v82 = get_Item(v134, 0) + ((128 - ctr1) >> 1);
      *(u64 *)&v135.x = v92;
      *(u64 *)&v135.z = 3;
      set_Item(v135, v82, 0);
      *(u64 *)&v136.x = v93;
      *(u64 *)&v136.z = 3;
      set_Item(v136, ctr1, 0);
    }
  }
}

// 0x1c6a550
static void DrawRetPageCursor(instanceMes_tag *pinst) {
  curctr_tag *curctr;
  s32 v9;
  s32 v12;
  sdfDrawTag_t *v15;
  s32 ctr1;
  s32 v18;
  s32 v19;
  s32 v22;
  s32 v25;
  s32 v28;
  u64 v31[2];
  u64 v32[2];
  u64 v33[2];
  sdfIVector4_t v34;
  sdfIVector4_t v35;
  sdfIVector4_t v36;
  sdfIVector4_t v37;
  sdfIVector4_t v38;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;
  sdfIVector4_t v42;
  sdfIVector4_t v43;
  sdfIVector4_t v44;
  sdfIVector4_t v45;
  sdfIVector4_t v46;
  sdfIVector4_t v47;
  sdfIVector4_t v48;
  sdfIVector4_t v49;
  sdfIVector4_t v50;
  sdfIVector4_t v51;

  *(u64 *)&v34.x = v31;
  *(u64 *)&v34.z = 16;
  v33[0] = 0;
  v33[1] = 0;
  v31[0] = 0;
  v31[1] = 0;
  _ctor(v34, 736, 288, 1008, 0);
  *(u64 *)&v35.x = v33;
  *(u64 *)&v35.z = 128;
  _ctor(v35, 128, 128, 255, 0);
  curctr = pinst->curctr;
  *(u64 *)&v36.x = v32;
  *(u64 *)&v36.z = 0;
  v32[0] = 0;
  v32[1] = 0;
  set_Item(v36, 6736, 0);
  *(u64 *)&v37.x = v32;
  *(u64 *)&v37.z = 1;
  set_Item(v37, 3232, 0);
  *(u64 *)&v38.x = v32;
  *(u64 *)&v38.z = 0;
  v9 = get_Item(v38, 0) + 272;
  *(u64 *)&v39.x = v32;
  *(u64 *)&v39.z = 2;
  set_Item(v39, v9, 0);
  *(u64 *)&v40.x = v32;
  *(u64 *)&v40.z = 1;
  v12 = get_Item(v40, 0) + 136;
  *(u64 *)&v41.x = v32;
  *(u64 *)&v41.z = 3;
  set_Item(v41, v12, 0);
  *(u64 *)&v42.x = v33;
  *(u64 *)&v42.z = 3;
  set_Item(v42, curctr->ctr0, 0);
  v15 = Allocate(sdfDrawTag_t);
  _ctor(v15, 0);
  sdfDrawTagInit(v15);
  if (curctr->ctr1 >= 1)
  {
    ctr1 = (u16)curctr->ctr1;
    *(u64 *)&v43.x = v32;
    *(u64 *)&v43.z = 0;
    v18 = 2 * (128 - ctr1);
    v19 = get_Item(v43, 0) - v18;
    *(u64 *)&v44.x = v32;
    *(u64 *)&v44.z = 0;
    set_Item(v44, v19, 0);
    *(u64 *)&v45.x = v32;
    *(u64 *)&v45.z = 1;
    v22 = get_Item(v45, 0) - (128 - ctr1);
    *(u64 *)&v46.x = v32;
    *(u64 *)&v46.z = 1;
    set_Item(v46, v22, 0);
    *(u64 *)&v47.x = v32;
    *(u64 *)&v47.z = 2;
    v25 = get_Item(v47, 0) + v18;
    *(u64 *)&v48.x = v32;
    *(u64 *)&v48.z = 2;
    set_Item(v48, v25, 0);
    *(u64 *)&v49.x = v32;
    *(u64 *)&v49.z = 3;
    v28 = get_Item(v49, 0) + 128 - ctr1;
    *(u64 *)&v50.x = v32;
    *(u64 *)&v50.z = 3;
    set_Item(v50, v28, 0);
    *(u64 *)&v51.x = v33;
    *(u64 *)&v51.z = 3;
    set_Item(v51, ctr1, 0);
  }
}

// 0x1c6a750
static dds3ProcessFunc_t CalcManagerProc(dds3ProcessID_t *proc_id) {
  itfMiscLinkHeader_t *puse_top;
  s64 naturalAligment;
  instanceMes_tag *klass;
  s64 v7;

  puse_top = *(itfMiscLinkHeader_t *)(*(u64 *)(*((u64 *)*((MethodInfo *)itf + 2).virtualMethodPointer + 57) + 32) + 16);
  if (!puse_top)
  {
    MsgLogDispCalc();
    return 0;
  }
  if (puse_top->klass->_2.naturalAligment < (u32)naturalAligment || puse_top->klass->_2.typeHierarchy[naturalAligment - 1] != mesflow_tag)
  {
LABEL_12:
  }
  if (!MsgLogDispCalc())
  {
    while (1)
    {
      klass = puse_top[1].klass;
      CalcMesFlow(klass);
      puse_top = puse_top->pnext;
      if (!puse_top)
        break;
      if (puse_top->klass->_2.naturalAligment < (u32)v7 || puse_top->klass->_2.typeHierarchy[v7 - 1] != mesflow_tag)
      {
        goto LABEL_12;
      }
    }
  }
  return 0;
}

// 0x1c6ba90
static dds3ProcessFunc_t DrawManagerProc(dds3ProcessID_t *proc_id) {
  itfMiscLinkHeader_t *puse_top;
  bool IsBattle;
  instanceMes_tag *klass;
  s32 v17;

  itf_cr_icon = 0;
  puse_top = g_manager->linkstack->puse_top;
  if (!puse_top)
    goto LABEL_4;
  goto LABEL_13;
  if (!puse_top)
  {
LABEL_4:
    goto LABEL_5;
  }
  do
  {
LABEL_13:
    klass = puse_top[1].klass;
    DrawMesFlow(klass);
    puse_top = puse_top->pnext;
  }
  while (puse_top);
LABEL_5:
  ++g_manager->ctr;
  IsBattle = sbattleIsBattle();
  if (IsBattle)
  {
    if (battle_key_wait)
    {
      itf_cr_icon = 0;
    }
  }
  if (meswin_type)
    v17 = 22;
  else
    v17 = 1;
  itfMsgWndCurSetActive(v17, itf_cr_icon);
  MsgLogDispDraw();
  return 0;
}

// 0x1c55190
static void SetCrIcon(void) {
  itf_cr_icon = 1;
  return;
}

// 0x1c6ea00
static void ShutdownProc(dds3ProcessID_t *proc_id) {
  itfMiscLinkHeader_t *puse_top;
  itfMiscLinkHeader_t *pnext;
  s32 id;

  puse_top = g_manager->linkstack->puse_top;
  if (!puse_top)
    return;
  do
  {
    pnext = puse_top->pnext;
    id = puse_top->id;
    DestructFlow(id);
    puse_top = pnext;
  }
  while (pnext);
}

// 0x1c69b90
static void DebugDrawWindowLine(itfpanel_t *meswin) {
  void *v3;
  sdfIVector4_t *v4;
  sdfIVector4_t *p_pos;
  u64 *v7;
  s32 Item;
  s32 v11;
  s32 v13;
  s32 v15;
  s32 v17;
  s32 v19;
  s32 v21;
  s32 v23;
  sdfDrawTag_t *v24;
  s64 v25;
  s64 v26;
  s64 v27;
  __int128 v28;
  s64 v29;
  sdfIVector4_t v30;
  sdfIVector4_t v31;
  sdfIVector4_t v32;
  sdfIVector4_t v33;
  sdfIVector4_t v34;
  sdfIVector4_t v35;
  sdfIVector4_t v36;
  sdfIVector4_t v37;
  sdfIVector4_t v38;

  v3 = NewSpecific(byte, 5u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__D662B83EBDBA5C9B406D74B9ABAEE1D0FE898243FB5C2BE8432DA1EE2784DBB4, 0);
  NewSpecific(byte, 5u);
  v4 = NewSpecific(sdfIVector4_t, 1u);
  *(u64 *)&v30.x = &v28;
  *(u64 *)&v30.z = 0;
  v28 = 0u;
  _ctor(v30, 127, 4, 128, 0);
  *(_OWORD *)&v4[0] = v28;
  p_pos = &meswin->pos;
  v7 = NewSpecific(sdfIVector2_t, 4u);
  *(u64 *)&v31.z = 0;
  *(u64 *)&v31.x = p_pos;
  Item = get_Item(v31, 0);
  *(u64 *)&v32.x = p_pos;
  *(u64 *)&v32.z = 1;
  v11 = get_Item(v32, 0);
  v29 = 0;
  _ctor((sdfIVector2_t)&v29, Item, v11, 0);
  *(u64 *)&v33.x = p_pos;
  *(u64 *)&v33.z = 2;
  v7[4] = v29;
  v13 = get_Item(v33, 0);
  *(u64 *)&v34.x = p_pos;
  *(u64 *)&v34.z = 1;
  v15 = get_Item(v34, 0);
  v27 = 0;
  _ctor((sdfIVector2_t)&v27, v13, v15, 0);
  *(u64 *)&v35.x = p_pos;
  *(u64 *)&v35.z = 2;
  v7[5] = v27;
  v17 = get_Item(v35, 0);
  *(u64 *)&v36.x = p_pos;
  *(u64 *)&v36.z = 3;
  v19 = get_Item(v36, 0);
  v26 = 0;
  _ctor((sdfIVector2_t)&v26, v17, v19, 0);
  *(u64 *)&v37.x = p_pos;
  *(u64 *)&v37.z = 0;
  v7[6] = v26;
  v21 = get_Item(v37, 0);
  *(u64 *)&v38.x = p_pos;
  *(u64 *)&v38.z = 3;
  v23 = get_Item(v38, 0);
  v25 = 0;
  _ctor((sdfIVector2_t)&v25, v21, v23, 0);
  v7[7] = v25;
  v24 = Allocate(sdfDrawTag_t);
  _ctor(v24, 0);
  sdfDrawTagInit(v24);
}

// 0x1c68610
static void DebugMoveWinVert(window_tag *pwin, s32 flag) {
  s32 v5;
  s32 v6;
  itfpanel_t *v8;
  u32 v10;
  u32 v11;
  itfpanel_t *mes;
  s32 v14;
  s32 v17;
  itfpanel_t *v19;
  s32 v20;
  s32 v23;
  struct sdfIVector4_t mes_offset;
  sdfIVector4_t v26;
  sdfIVector4_t v27;
  sdfIVector4_t v28;
  sdfIVector4_t v29;
  sdfIVector4_t v30;
  sdfIVector4_t v31;
  sdfIVector4_t v32;
  sdfIVector4_t v33;

  if (!pwin->mes)
    return;
  mes_offset = pwin->mes_offset;
  if (!CHECK_REP(4102, 0))
  {
    if (CHECK_REP(4103, 0))
      v5 = 16;
    else
      v5 = 0;
    if (!CHECK_REP(4100, 0))
      goto LABEL_6;
LABEL_13:
    v6 = -8;
    goto LABEL_14;
  }
  v5 = -16;
  if (CHECK_REP(4100, 0))
    goto LABEL_13;
LABEL_6:
  if (CHECK_REP(4101, 0))
    v6 = 8;
  else
    v6 = 0;
LABEL_14:
  if (CHECK_PRESS(4096, 0))
  {
    v6 *= 8;
    v5 *= 8;
  }
  if (v5 | v6)
  {
    if (flag == 2)
    {
      mes = pwin->mes;
      itfPnlSetPositionOffset(mes, v5, v6, v5, v6, 0);
      *(u64 *)&v26.x = &mes_offset;
      *(u64 *)&v26.z = 0;
      v14 = get_Item(v26, 0) + v5;
      *(u64 *)&v27.x = &mes_offset;
      *(u64 *)&v27.z = 0;
      set_Item(v27, v14, 0);
      *(u64 *)&v28.x = &mes_offset;
      *(u64 *)&v28.z = 1;
      v17 = get_Item(v28, 0) + v6;
      *(u64 *)&v29.x = &mes_offset;
      *(u64 *)&v29.z = 1;
      set_Item(v29, v17, 0);
    }
    else
    {
      if (flag != 1)
      {
        if (flag)
          return;
        v8 = pwin->mes;
        itfPnlSetPositionOffset(v8, v5, v6, 0, 0, 0);
        v10 = 0;
        v11 = 1;
        goto LABEL_30;
      }
      v19 = pwin->mes;
      itfPnlSetPositionOffset(v19, 0, 0, v5, v6, 0);
    }
    v11 = 3;
    v10 = 2;
LABEL_30:
    *(u64 *)&v30.x = &mes_offset;
    *(u64 *)&v30.z = v10;
    v20 = get_Item(v30, 0) + v5;
    *(u64 *)&v31.x = &mes_offset;
    *(u64 *)&v31.z = v10;
    set_Item(v31, v20, 0);
    *(u64 *)&v32.x = &mes_offset;
    *(u64 *)&v32.z = v11;
    v23 = get_Item(v32, 0) + v6;
    *(u64 *)&v33.x = &mes_offset;
    *(u64 *)&v33.z = v11;
    set_Item(v33, v23, 0);
  }
}

// 0x1c68870
static void DebugMoveWinAlpha(window_tag *pwin) {
  s32 v3;
  s32 v5;
  s32 v6;
  s32 Item;
  itfpanel_t *mes;
  sdfIVector4_t *p_color;
  s32 v14;
  sdfIVector4_t v16;
  sdfIVector4_t v17;
  sdfIVector4_t v18;
  sdfIVector4_t v19;
  sdfIVector4_t v20;
  sdfIVector4_t v21;

  if (CHECK_REP(4102, 0))
  {
    v3 = -1;
    if (!CHECK_REP(4100, 0))
      goto LABEL_3;
LABEL_6:
    v3 = -1;
    goto LABEL_7;
  }
  v3 = CHECK_REP(4103, 0);
  if (CHECK_REP(4100, 0))
    goto LABEL_6;
LABEL_3:
  if (CHECK_REP(4101, 0))
    v3 = 1;
LABEL_7:
  if (CHECK_PRESS(4096, 0))
    v5 = 10 * v3;
  else
    v5 = v3;
  if (v5)
  {
    *(u64 *)&v16.z = 3;
    *(u64 *)&v16.x = &pwin->mes_color;
    v6 = get_Item(v16, 0) + v5;
    *(u64 *)&v17.x = &pwin->mes_color;
    *(u64 *)&v17.z = 3;
    set_Item(v17, v6, 0);
    *(u64 *)&v18.x = &pwin->mes_color;
    *(u64 *)&v18.z = 3;
    Item = (u8)get_Item(v18, 0);
    *(u64 *)&v19.x = &pwin->mes_color;
    *(u64 *)&v19.z = 3;
    set_Item(v19, Item, 0);
    mes = pwin->mes;
    if (mes)
    {
      *(u64 *)&v20.x = &pwin->mes_color;
      *(u64 *)&v20.z = 3;
      p_color = &mes->color;
      v14 = get_Item(v20, 0);
      *(u64 *)&v21.x = p_color;
      *(u64 *)&v21.z = 3;
      set_Item(v21, v14, 0);
    }
  }
}

// 0x1c68460
static mesflow_tag *DebugChangeInstance(mesflow_tag *pflow) {
  signed s32 numuse;
  signed s32 i;

  numuse = g_manager->numuse;
  if (numuse < 1)
    return 0;
  goto LABEL_7;
  if (numuse >= 1)
  {
LABEL_7:
    for (i = 0; i <= numuse; ++i)
    {
      if (pflow)
      {
        pflow = (mesflow_tag *)pflow->pprev;
        if (pflow)
          goto LABEL_18;
        pflow = (mesflow_tag *)g_manager->linkstack->puse_tail;
        if (pflow)
          goto LABEL_18;
      }
      {
        pflow = (mesflow_tag *)g_manager->linkstack->puse_tail;
        if (pflow)
          goto LABEL_17;
      }
      else
      {
        pflow = (mesflow_tag *)g_manager->linkstack->puse_tail;
        if (pflow)
        {
LABEL_17:
LABEL_18:
        }
      }
      if (pflow->pinst->window->mes)
        return pflow;
    }
  }
  return 0;
}

// 0x1c5bda0
static u8 *GetDataBytes(u8 *data, s32 index, s32 len) {
  void *v7;

  v7 = NewSpecific(byte, len + 1);
  Copy_56175392(data, index, v7, 0, len, 0);
  *((u8 *)&v7[2].klass + len) = 0;
  return v7;
}

// 0x1c601f0
static void CallEventVoice(instanceMes_tag *pinst) {
  FontReq_t *pfont;
  char *tag_id;
  char *v5;
  char *v6;
  char *v7;
  LIPSYNC_PARAM *lipsync_pm_local;
  char *PartVoice;
  s32 v12;
  char *v14;
  LIPSYNC_PARAM *v16;
  LIPSYNC_PARAM *v18;
  message_tag *message;
  Il2CppObject *v21;
  char *v22;
  u8 *label;
  il2cpp_array_size_t max_length;
  s64 v25;
  u32 v26;
  int8x16_t v27;
  int32x4_t v28;
  int8x16_t *v29;
  s64 v30;
  int32x4_t v31;
  int32x4_t v32;
  int32x4_t v33;
  int32x4_t v34;
  int32x4_t v35;
  int32x4_t v36;
  int32x4_t v37;
  int32x4_t v38;
  int32x4_t v39;
  int32x4_t v40;
  int32x4_t v41;
  int32x4_t v42;
  int32x4_t v43;
  int32x4_t v44;
  int32x4_t v45;
  uint8x16_t v46;
  uint8x16_t v47;
  uint16x8_t v48;
  uint16x8_t v49;
  uint16x8_t v50;
  uint16x8_t v51;
  uint8x16_t v52;
  uint16x8_t v53;
  uint16x8_t v54;
  int8x16_t v55;
  int8x16_t v56;
  int8x16_t v57;
  uint8x16_t v58;
  uint16x8_t v59;
  uint16x8_t v60;
  int32x4_t v61;
  int8x8_t *v62;
  s64 v63;
  int8x8_t *v64;
  s64 v65;
  int32x4_t v66;
  int8x8_t v67;
  uint16x8_t v68;
  s64 v69;
  u8 *v70;
  s64 v72;
  s64 v73;
  s64 v74;
  s64 v75;
  s64 v76;
  s64 v77;
  s64 v78;
  s64 v79;
  char *v80;
  void *Default;
  char *v82;
  _BOOL4 hojomes;
  LIPSYNC_PARAM *v85;
  _BOOL4 v86;
  LIPSYNC_PARAM *v88;
  Il2CppObject *v89;
  s32 unit_uniqid;
  dds3ModelHandle_t *LipModel;
  void *gameObject;
  Il2CppObject *Component_object;
  bool v95;
  s32 v98;
  dds3ModelHandle_t *v99;
  void *v100;
  char *v102;
  LIPSYNC_PARAM *v104;
  s32 data;
  s32 value;

  pfont = pinst->message->pfont;
  if (!pfont)
    return;
  tag_id = pfont->tag_id;
  if (IsNullOrEmpty(tag_id, 0))
    return;
  v5 = Replace_54838864(tag_id, "<", "", 0);
  v6 = Replace_54838864(v5, ">", "", 0);
  v7 = "";
  lipsync_pm_local = lipsync_pm;
  lipsync_pm_local->voice_name = v7;
  lipsync_pm->autoTime = 240;
  PartVoice = itfGetPartVoice(v6);
  value = 0;
  v12 = 0;
  if (!IsNullOrEmpty(v6, 0))
  {
    int___TryGetValue(flagVoiceDic, v6, &value);
    v12 = value;
  }
  if (IsNullOrEmpty(PartVoice, 0))
    v14 = v6;
  else
    v14 = PartVoice;
  v16 = lipsync_pm;
  v16->voice_name = v14;
  lipsync_pm->autoTime = 240;
  v18 = lipsync_pm;
  v18->tagid = v6;
  if (scrIsEventSkip(0))
  {
    if (sndIsVoicePlayFile(v14))
    {
LABEL_28:
      if (!IsNullOrEmpty(PartVoice, 0) && !v12)
      {
        itfLipSyncSetVoice("");
      }
      return;
    }
LABEL_112:
    v102 = "";
    v104 = lipsync_pm;
    v104->voice_name = v102;
    lipsync_pm->autoTime = 240;
    return;
  }
  message = pinst->message;
  if (message->page >= 1)
  {
    data = (u16)message->page + 1;
    v21 = Box(s32, &data);
    v22 = Format("_{0:D2}", v21, 0);
    label = message->pbinheader->label;
    max_length = label->max_length;
    if ((s32)max_length >= 1)
      goto LABEL_42;
LABEL_47:
    v26 = 0;
    goto LABEL_61;
  }
  v22 = "";
  label = message->pbinheader->label;
  max_length = label->max_length;
  if ((s32)max_length < 1)
    goto LABEL_47;
LABEL_42:
  if ((u32)max_length >= 8u)
  {
    v27.n128_u64[0] = 0x100000001LL;
    v27.n128_u64[1] = 0x100000001LL;
    if ((u32)max_length >= 0x40u)
    {
      v28 = 0u;
      v25 = (u32)max_length & 0xFFFFFFC0;
      v29 = &label[48];
      v30 = v25;
      v31 = 0u;
      v32 = 0u;
      v33 = 0u;
      v34 = 0u;
      v35 = 0u;
      v36 = 0u;
      v37 = 0u;
      v38 = 0u;
      v39 = 0u;
      v40 = 0u;
      v41 = 0u;
      v42 = 0u;
      v43 = 0u;
      v44 = 0u;
      v45 = 0u;
      do
      {
        v30 -= 64;
        v46 = vtstq_s8(v29[-2], v29[-2]);
        v47 = vtstq_s8(v29[-3], v29[-3]);
        v48 = vmovl_high_u8(v47);
        v49 = vmovl_u8((uint8x8_t)v47.n128_u64[0]);
        v32 = vaddq_s32(v32, vandq_s8(vmovl_u16((uint16x4_t)v48.n128_u64[0]), v27));
        v33 = vaddq_s32(v33, vandq_s8(vmovl_high_u16(v48), v27));
        v31 = vaddq_s32(v31, vandq_s8(vmovl_high_u16(v49), v27));
        v50 = vmovl_high_u8(v46);
        v28 = vaddq_s32(v28, vandq_s8(vmovl_u16((uint16x4_t)v49.n128_u64[0]), v27));
        v51 = vmovl_u8((uint8x8_t)v46.n128_u64[0]);
        v37 = vaddq_s32(v37, vandq_s8(vmovl_high_u16(v50), v27));
        v36 = vaddq_s32(v36, vandq_s8(vmovl_u16((uint16x4_t)v50.n128_u64[0]), v27));
        v52 = vtstq_s8(v29[-1], v29[-1]);
        v35 = vaddq_s32(v35, vandq_s8(vmovl_high_u16(v51), v27));
        v34 = vaddq_s32(v34, vandq_s8(vmovl_u16((uint16x4_t)v51.n128_u64[0]), v27));
        v53 = vmovl_high_u8(v52);
        v54 = vmovl_u8((uint8x8_t)v52.n128_u64[0]);
        v55 = vmovl_high_u16(v53);
        v40 = vaddq_s32(v40, vandq_s8(vmovl_u16((uint16x4_t)v53.n128_u64[0]), v27));
        v56 = vmovl_u16((uint16x4_t)v54.n128_u64[0]);
        v41 = vaddq_s32(v41, vandq_s8(v55, v27));
        v57 = *v29;
        v29 += 4;
        v58 = vtstq_s8(v57, v57);
        v39 = vaddq_s32(v39, vandq_s8(vmovl_high_u16(v54), v27));
        v59 = vmovl_high_u8(v58);
        v38 = vaddq_s32(v38, vandq_s8(v56, v27));
        v60 = vmovl_u8((uint8x8_t)v58.n128_u64[0]);
        v44 = vaddq_s32(v44, vandq_s8(vmovl_u16((uint16x4_t)v59.n128_u64[0]), v27));
        v45 = vaddq_s32(v45, vandq_s8(vmovl_high_u16(v59), v27));
        v43 = vaddq_s32(v43, vandq_s8(vmovl_high_u16(v60), v27));
        v42 = vaddq_s32(v42, vandq_s8(vmovl_u16((uint16x4_t)v60.n128_u64[0]), v27));
      }
      while (v30);
      v26 = vaddvq_s32(vaddq_s32(vaddq_s32(vaddq_s32(v42, vaddq_s32(v38, vaddq_s32(v34, v28))), vaddq_s32(v44, vaddq_s32(v40, vaddq_s32(v36, v32)))), vaddq_s32(vaddq_s32(v43, vaddq_s32(v39, vaddq_s32(v35, v31))), vaddq_s32(v45, vaddq_s32(v41, vaddq_s32(v37, v33))))));
      if ((max_length & 0x3F) == 0)
        goto LABEL_61;
      if ((max_length & 0x3F) < 8)
        goto LABEL_57;
    }
    else
    {
      v26 = 0;
      v25 = 0;
    }
    v61 = 0u;
    v62 = ((char *)label + v25);
    v63 = v25 + (max_length & 7);
    v25 = (u32)max_length & 0xFFFFFFF8;
    v66 = 0u;
    v64 = v62 + 4;
    v65 = v63 - (u32)max_length;
    v66.n128_u32[0] = v26;
    do
    {
      v67.n64_u64[0] = v64->n64_u64[0];
      ++v64;
      v65 += 8;
      v68 = vmovl_u8(vtst_s8(v67, v67));
      v61 = vaddq_s32(v61, vandq_s8(vmovl_high_u16(v68), v27));
      v66 = vaddq_s32(v66, vandq_s8(vmovl_u16((uint16x4_t)v68.n128_u64[0]), v27));
    }
    while (v65);
    v26 = vaddvq_s32(vaddq_s32(v66, v61));
    if ((max_length & 7) == 0)
      goto LABEL_61;
    goto LABEL_57;
  }
  v25 = 0;
  v26 = 0;
LABEL_57:
  v69 = (u32)max_length - v25;
  v70 = &label[v25];
  do
  {
    if (*v70++)
      ++v26;
    --v69;
  }
  while (v69);
LABEL_61:
  v72 = NewSpecific(byte, v26);
  v73 = *(u64 *)(v72 + 24);
  v74 = v72;
  if ((s32)v73 >= 1)
  {
    v75 = v73 << 32;
    v76 = *(u64 *)(v72 + 24) & 1;
    if (v75 == 0x100000000LL)
    {
      v77 = 0;
    }
    else
    {
      v77 = 0;
      v78 = (v75 >> 32) - v76;
      do
      {
        v79 = v72 + v77;
        *(u8 *)(v79 + 32) = message->pbinheader->label[v77];
        v80 = (char *)message->pbinheader->label + v77;
        v77 += 2;
        *(u8 *)(v79 + 33) = v80[33];
      }
      while (v78 != v77);
    }
    if (v76)
      *(u8 *)(v72 + v77 + 32) = message->pbinheader->label[v77];
  }
  Default = get_Default(0);
  v82 = (Default->klass->vtable._33_GetString.methodPtr)(Default, v74, Default->klass->vtable._33_GetString.method);
  Trim(v82, 0);
  Concat_54766928(v82, v22, 0);
  hojomes = pinst->hojomes;
  if (hojomes)
  {
    goto LABEL_72;
  }
  sndVoiceStop(0);
LABEL_72:
  v85 = lipsync_pm;
  v85->voice_name = v14;
  v86 = pinst->hojomes;
  lipsync_pm->autoTime = 240;
  if (v86)
  {
    goto LABEL_76;
  }
  sndVoiceStop(0);
LABEL_76:
  v88 = lipsync_pm;
  if (!v88->start)
  {
    v89 = 0;
    if (pinst->hojomes)
      return;
    goto LABEL_109;
  }
  unit_uniqid = v88->unit_uniqid;
  LipModel = evtGetLipModel(unit_uniqid);
  if (!LipModel)
  {
    Component_object = 0;
    goto LABEL_91;
  }
  gameObject = get_gameObject(LipModel->modelRoot->modelObj, 0);
  Component_object = GetComponent_object_(gameObject);
LABEL_91:
  v95 = op_Inequality(Component_object, 0, 0);
  if (v95)
  {
    v98 = lipsync_pm->unit_uniqid;
    v99 = evtGetLipModel(v98);
    if (v99)
    {
      v100 = get_gameObject(v99->modelRoot->modelObj, 0);
      v89 = GetComponent_object_(v100);
      goto LABEL_97;
    }
    v89 = 0;
LABEL_97:
    sndVoiceStop(v89);
    SetAtomSource(Component_object, v89, 0);
    if (pinst->hojomes)
      return;
LABEL_109:
    if (sndVoicePlayFile(v14, v89))
      goto LABEL_28;
    goto LABEL_112;
  }
  evtLipsExecFunction(lipsync_pm->unit_uniqid, lipsync_pm->motion_no);
  v89 = 0;
  if (!pinst->hojomes)
    goto LABEL_109;
}

// 0x1c6eb50
bool itfIsSpeaking(void) {
  if (bNowSpeaking == 2)
    return 0;
  if (!bVoicePlaySw)
    return bNowSpeaking != 3;
  return sndVoiceStatus(0);
}

// 0x1c6ec90
bool itfIsSpeakStart(void) {
  if (bNowSpeaking == 2)
    return 0;
  if (!bVoicePlaySw)
    return 0;
  return sndVoiceStatus(0);
}

// 0x1c57cd0
void itfMsgWndSetActive(s32 i, bool sw) {
  Il2CppObject *Item;
  Il2CppObject *v8;

  Item = _get_Item(MsgWnd, i);
  if (get_activeSelf(Item, 0) != sw)
  {
    v8 = _get_Item(MsgWnd, i);
    SetActive(v8, sw, 0);
  }
}

// 0x1c59790
static bool MsgWndActiveSelf(s32 i) {
  Il2CppObject *Item;

  Item = _get_Item(MsgWnd, i);
  return get_activeSelf(Item, 0);
}

// 0x1c6ed90
void itfSetMsgWndTmpText(s32 i, char *str) {
  Il2CppObject *Item;
  Il2CppObject *v8;

  Item = _get_Item(MsgWndTMP, i);
  if (op_Equality(Item, 0, 0))
    return;
  v8 = _get_Item(MsgWndTMP, i);
  (v8->klass->vtable[66].methodPtr)(v8, str, v8->klass->vtable[66].method);
}

// 0x1c6eec0
char *itfGetMsgWndTmpText(s32 i) {
  Il2CppObject *Item;
  Il2CppObject *v7;

  Item = _get_Item(MsgWndTMP, i);
  if (op_Equality(Item, 0, 0))
    return 0;
  v7 = _get_Item(MsgWndTMP, i);
  return ((char *(Il2CppObject *, const MethodInfo *))v7->klass->vtable[65].methodPtr)(v7, v7->klass->vtable[65].method);
}

// 0x1c6eff0
void itfSetMsgWndTmpTextReplace(char *str) {
  g_replace_text = str;
}

// 0x1c6bd00
void itfMsgWndCurSetActive(s32 i, bool sw) {
  Il2CppObject *Item;
  Il2CppObject *v8;
  Il2CppObject *v10;

  Item = _get_Item(MsgWndCur, i);
  if (op_Equality(Item, 0, 0))
    return;
  v8 = _get_Item(MsgWndCur, i);
  if (get_activeSelf(v8, 0) != sw)
  {
    v10 = _get_Item(MsgWndCur, i);
    SetActive(v10, sw, 0);
  }
}

// 0x1c5a2d0
void itfMsgWndImgSetActive(s32 i, bool sw) {
  Il2CppObject *Item;
  Il2CppObject *v8;
  Il2CppObject *v10;

  Item = _get_Item(MsgWndImg, i);
  if (op_Equality(Item, 0, 0))
    return;
  v8 = _get_Item(MsgWndImg, i);
  if (get_enabled(v8, 0) != sw)
  {
    v10 = _get_Item(MsgWndImg, i);
    set_enabled(v10, sw, 0);
  }
}

// 0x1c6f060
void itfSetRaidouObjectAndCamera(void *obj, void *cam) {
  ;
}

// 0x1c6f070
void itfSetRaidoObject(void *obj, f32 add) {
  void *p_raidou;

  p_raidou = &raidou;
  p_raidou = obj;
  actionWindowAddPosY = add;
}

// 0x1c6f100
void itfSetCamera(void *cam) {
  mainCamera = cam;
}

// 0x1c6f170
void itfActWndSetActive(bool sw, bool isCalc) {
  Il2CppObject *Item;
  void *camera;
  void *p_mainCamera;
  bool v19;
  bool v22;
  u32 v23;
  bool v24;
  s32 v27;
  void *transform;
  f32 v33;
  Il2CppObject *v34;
  void *v35;
  sdfVector3_t v36;
  sdfVector3_t v37;
  sdfVector3_t position;

  Item = _get_Item(MsgWnd, 0);
  if (op_Inequality(Item, 0, 0))
  {
    if (!sw || !isCalc)
      goto LABEL_17;
    camera = cameraObject->_camera;
    p_mainCamera = &mainCamera;
    p_mainCamera = camera;
    if (op_Inequality(mainCamera, 0, 0))
    {
      if (!op_Inequality(raidou, 0, 0))
        goto LABEL_17;
      transform = get_transform(raidou, 0);
      position = get_position(transform, 0);
      v36 = WorldToViewportPoint_60728416(mainCamera, position, 0);
      v33 = (f32)((f32)(v36.y * 1080.0) + -540.0) + actionWindowAddPosY;
      v34 = _get_Item(MsgWnd, 0);
      v35 = get_transform(v34, 0);
      v37.z = 0.0;
      v37.x = (f32)(v36.x * 1920.0) + -960.0;
      v37.y = v33;
      set_localPosition(v35, v37, 0);
LABEL_19:
      itfMsgWndSetActive(0, sw);
      if (ActionWndLine == 3)
      {
        v19 = sw;
        itfMsgWndSetActive(12, v19);
        itfMsgWndSetActive(13, v19);
        v22 = v19;
LABEL_30:
        itfMsgWndSetActive(14, v22);
        v27 = 11;
LABEL_35:
        itfMsgWndSetActive(v27, 0);
        return;
      }
      if (ActionWndLine == 2)
      {
        if (!v23)
        v24 = sw;
        itfMsgWndSetActive(12, v24);
        itfMsgWndSetActive(13, v24);
        v22 = 0;
        goto LABEL_30;
      }
      if (!v23)
      itfMsgWndSetActive(11, sw);
      itfMsgWndSetActive(12, 0);
      itfMsgWndSetActive(13, 0);
      v27 = 14;
      goto LABEL_35;
    }
LABEL_17:
    goto LABEL_19;
  }
}

// 0x1c6f550
void itfDrawActWnd(void) {
  itfActWndSetActive(isActionWndDisp, 1);
}

// 0x1c6f5e0
sdfVector3_t itfGetMsgWndLocalPos(void) {
  Il2CppObject *Item;
  void *transform;
  sdfVector3_t localPosition;
  sdfVector3_t result;

  goto LABEL_3;
LABEL_9:
  result.x = 0.0;
  result.y = 0.0;
  result.z = 0.0;
  return result;
LABEL_3:
  if (!MsgWnd)
    goto LABEL_9;
  Item = _get_Item(MsgWnd, 0);
  transform = get_transform(Item, 0);
  localPosition = get_localPosition(transform, 0);
  result.x = localPosition.x;
  result.y = localPosition.y;
  result.z = localPosition.z;
  return result;
}

// 0x1c6f6c0
void DrawActWnd(const sdfVector3_t *pos) {
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v12;
  Il2CppObject *Item;
  void *transform;
  sdfVector3_t Position;
  sdfVector3_t v16;

  y = pos->y;
  x = pos->x;
  itfActWndSetActive(isActionWndDisp, 0);
  Position = GetPosition(cameraObject, x, y, 1080.0, 0);
  v8 = 365.0;
  if (Position.y <= 365.0)
    v8 = Position.y;
  if (v8 >= -365.0)
    v9 = v8;
  else
    v9 = -365.0;
  v10 = -900.0;
  if (Position.x >= -900.0)
    v10 = Position.x;
  if (v10 <= 900.0)
    v12 = v10;
  else
    v12 = 900.0;
  Item = _get_Item(MsgWnd, 0);
  transform = get_transform(Item, 0);
  v16.x = v12;
  v16.z = Position.z;
  v16.y = v9;
  set_localPosition(transform, v16, 0);
}

// 0x1c6f830
void itfSetActWndText(char *str, s32 line) {
  s32 v7;
  s32 v8;
  char *v9;

  switch (line)
  {
    case 3:
      v7 = 14;
      goto LABEL_12;
    case 2:
      v7 = 13;
      goto LABEL_12;
    case 1:
      if (ActionWndLine == 2)
      {
LABEL_18:
        v7 = 12;
LABEL_12:
        v8 = v7;
        v9 = str;
        itfSetMsgWndTmpText(v8, v9);
        return;
      }
      if (ActionWndLine == 3)
        goto LABEL_18;
      v7 = 0;
      goto LABEL_12;
  }
}

// 0x1c6f980
void itfSetActWndTextCoror(char *str, s32 line, u32 color) {
  void *v7;
  u32 v8;
  Il2CppObject *v9;
  char *v10;
  char *v12;
  u32 data;

  v7 = Allocate(System_Text_StringBuilder);
  _ctor(v7, 0);
  if ((u8)color == 128)
    v8 = color | 0xFF;
  else
    v8 = color;
  data = v8;
  v9 = Box(uint, &data);
  v10 = Format("<color=#{0:X8}>", v9, 0);
  Append_56602800(v7, v10, 0);
  Append_56602800(v7, str, 0);
  v12 = (v7->klass->vtable._3_ToString.methodPtr)(v7, v7->klass->vtable._3_ToString.method);
  itfSetActWndText(v12, line);
}

// 0x1c6fac0
void itfSetIsActionWndDisp(bool flg) {
  isActionWndDisp = flg;
}

// 0x1c6fb30
bool itfGetIsActionWndDisp(void) {
  return isActionWndDisp;
}

// 0x1c6fbb0
void itfPreDrawActionWndDisp(bool flg) {
  isActionWndDisp = flg;
  if (flg)
    return;
  itfMsgWndSetActive(0, 0);
  itfMsgWndSetActive(11, 0);
  itfMsgWndSetActive(12, 0);
  HIDWORD(gMapIfSkil_dv) = 255;
  LOWORD(gMapIfMenuMsg) = 0;
  mapSetStockDevilAutoSkill(0);
  return;
}

// 0x1c6fdb0
void itfSetActionWndLines(s32 line) {
  if ((byte_5757483 & 1) != 0)
  {
    if ((u32)(line - 1) > 2)
      return;
  }
  else
  {
    if ((u32)(line - 1) > 2)
      return;
  }
  ActionWndLine = line;
}

// 0x1c6fe50
sdfVector3_t itfGetActionWindowPosition(void) {
  Il2CppObject *Item;
  void *transform;

  Item = _get_Item(MsgWnd, 0);
  transform = get_transform(Item, 0);
  return get_localPosition(transform, 0);
}

// 0x1c65600
void itfClearMsgWndText(void) {
  s32 v4;

  if (meswin_type)
    v4 = 22;
  else
    v4 = 1;
  itfSetMsgWndTmpText(v4, "");
}

// 0x1c5ac60
void itfSetAnimeMsgWin(bool flag) {
  s32 v5;
  Il2CppObject *Item;
  s32 v7;

  if (meswin_type)
    v5 = 22;
  else
    v5 = 1;
  Item = _get_Item(MsgWndAnm, v5);
  if (flag)
    v7 = 1;
  else
    v7 = 2;
  SetInteger(Item, "anim", v7, 0);
}

// 0x1c6fee0
s32 itfGetAnimeMsgWin(void) {
  s32 v3;
  Il2CppObject *Item;

  if (meswin_type)
    v3 = 22;
  else
    v3 = 1;
  Item = _get_Item(MsgWndAnm, v3);
  return GetInteger(Item, "anim", 0);
}

// 0x1c70000
bool itfGetAnimEndMsgWin(void) {
  s32 v3;
  Il2CppObject *Item;
  UnityEngine_AnimatorStateInfo_o v6;
  UnityEngine_AnimatorStateInfo_o v7;

  if (meswin_type)
    v3 = 22;
  else
    v3 = 1;
  Item = _get_Item(MsgWndAnm, v3);
  GetCurrentAnimatorStateInfo(&v6, Item, 0, 0);
  v7 = v6;
  return get_normalizedTime(&v7, 0) >= 1.0;
}

// 0x1c5ada0
bool itfIsFadeOutAnimeMsgWin(void) {
  s32 v3;
  Il2CppObject *Item;

  if (meswin_type)
    v3 = 22;
  else
    v3 = 1;
  Item = _get_Item(MsgWndAnm, v3);
  return GetInteger(Item, "anim", 0) != 1;
}

// 0x1c674d0
void itfSetIsmesWndBaseDisp(bool flg) {
  _BOOL4 v4;
  s32 v7;
  Il2CppObject *Item;
  void *transform;
  Il2CppObject *v10;
  void *v11;
  s32 v19;
  Il2CppObject *v20;
  void *v21;
  s32 v22;
  Il2CppObject *v23;
  void *v24;
  Il2CppObject *v25;
  void *v26;
  sdfVector3_t localPosition;
  sdfVector3_t v29;
  sdfVector3_t v30;
  sdfVector3_t v31;

  v4 = flg;
  if (isMesWndBaseDisp == v4)
  {
    goto LABEL_5;
  }
  if (meswin_type)
    v7 = 22;
  else
    v7 = 1;
  Item = _get_Item(MsgWnd, v7);
  transform = get_transform(Item, 0);
  localPosition = get_localPosition(transform, 0);
  v10 = _get_Item(MsgWnd, 3);
  v11 = get_transform(v10, 0);
  v29 = get_localPosition(v11, 0);
  if (org_guide_x == -1.0)
  {
    org_guide_x = v29.x;
  }
  if (flg)
  {
    itfSetMsgWndDefault();
    goto LABEL_31;
  }
  if (meswin_type)
    v19 = 22;
  else
    v19 = 1;
  v20 = _get_Item(MsgWndTMP, v19);
  set_alignment(v20, 258, 0);
LABEL_31:
  v21 = MsgWnd;
  if (meswin_type)
    v22 = 22;
  else
    v22 = 1;
  v23 = _get_Item(v21, v22);
  v24 = get_transform(v23, 0);
  v30.x = 0.0;
  v30.y = localPosition.y;
  v30.z = localPosition.z;
  set_localPosition(v24, v30, 0);
  v25 = _get_Item(MsgWnd, 3);
  v26 = get_transform(v25, 0);
  v31.x = org_guide_x;
  v31.y = v29.y;
  v31.z = v29.z;
  set_localPosition(v26, v31, 0);
LABEL_5:
  isMesWndBaseDisp = v4;
}

// 0x1c70140
void itfSetMsgWndDefault(void) {
  s32 v3;
  Il2CppObject *Item;

  if (meswin_type)
    v3 = 22;
  else
    v3 = 1;
  Item = _get_Item(MsgWndTMP, v3);
  set_alignment(Item, 257, 0);
}

// 0x1c67390
void itfSetMsgWndCnvGrpAlpha(s32 i, f32 alpha) {
  Il2CppObject *Item;
  Il2CppObject *v8;

  Item = _get_Item(MsgWndCnvGrp, i);
  if (!op_Inequality(Item, 0, 0))
    return;
  v8 = _get_Item(MsgWndCnvGrp, i);
  set_alpha(v8, alpha, 0);
}

// 0x1c70250
f32 itfGetMsgWndCnvGrpAlpha(s32 i) {
  Il2CppObject *Item;
  Il2CppObject *v6;

  Item = _get_Item(MsgWndCnvGrp, i);
  if (!op_Inequality(Item, 0, 0))
    return 0.0;
  v6 = _get_Item(MsgWndCnvGrp, i);
  return get_alpha(v6, 0);
}

// 0x1c5c5e0
static void InitMesWndSelect(s32 count) {
  bool v4;
  s32 v5;
  s32 v7;
  u64 *v8;
  void *v9;
  s64 size;
  s32 *items;

  v4 = __OFSUB__(count, 1);
  v5 = count - 1;
  v7 = mesSelectIndex->_version + 1;
  mesSelectIndex->_size = 0;
  mesSelectIndex->_version = v7;
  if (v5 < 0 == v4)
  {
    do
    {
      while (1)
      {
        v8 = Method_System_Collections_Generic_List_int__Add__;
        v9 = mesSelectIndex;
        size = v9->_size;
        ++v9->_version;
        items = v9->_items;
        if ((u32)size < LODWORD(items->max_length))
          break;
        _AddWithResize(v9, v5, *(const MethodInfo_2D8F530 **)(*(u64 *)(v8[4] + 192) + 112));
        if (--v5 == -1)
          return;
      }
      v9->_size = size + 1;
      items[size] = v5--;
    }
    while (v5 != -1);
  }
}

// 0x1c5c700
static s32 GetMesWndSelectViewIndex(s32 index) {
  if (mesSelectIndex->_size < index)
    return 0;
  return _get_Item(mesSelectIndex, index);
}

// 0x1c70380
void itfSetMenuCursorIndex(s32 index) {
  uniMenuCursor = index;
  return;
}

// 0x1c70410
s32 itfGetMenuCursorIndex(void) {
  return uniMenuCursor;
}

// 0x1c70490
bool itfIsExistMessageWindow(void) {
  Il2CppObject *Item;

  Item = _get_Item(MsgWnd, 1);
  return get_activeSelf(Item, 0);
}

// 0x1c5fb80
static void ReadytoMessage(instanceMes_tag *pinst, s32 mode) {
  message_tag *message;
  message_tag *v6;
  FontReq_t *p_pfont;
  FontReq_t *pfont;
  itfMesBinMesHeader_t *pbinheader;
  Il2CppObject *pdata;
  u32 page;
  void *Interface;
  s64 v13;
  s64 v14;
  s64 v15;
  s32 v16;
  void *v17;
  s32 Item;
  s32 v19;
  u8 v20;
  FontReq_t *v22;
  FontReq_t *head;
  s32 v24;
  s32 v25;
  FontReq_t *next;
  s32 v27;
  FontReq_t *v29;
  Text_t *str_end;
  s32 v31;
  u8 col_no;
  u32 z;
  LIPSYNC_PARAM *lipsync_pm_local;
  FontReq_t *v40;
  FontReq_t *prev;
  FontReq_t *v42;
  u64 v43;

  message = pinst->message;
  v6 = message;
  p_pfont = &message->pfont;
  pfont = message->pfont;
  if (pfont)
  {
    frDestroyFontRequestAfter(pfont);
    p_pfont = 0;
    v6 = pinst->message;
  }
  pbinheader = v6->pbinheader;
  pdata = pinst->pdata;
  page = message->page;
  if (!pdata)
  {
    Interface = 0;
    goto LABEL_12;
  }
  Interface = QueryInterface(pdata, byte);
LABEL_12:
  if ((page & 0x80000000) != 0 || pbinheader->page <= (s32)page)
  {
    v17 = 0;
  }
  else
  {
    v13 = page;
    v14 = (s64)pbinheader->addr + v13 * 4;
    v15 = pbinheader->len[v13];
    v16 = *(u32 *)(v14 + 32);
    v17 = NewSpecific(byte, (s32)v15 + 1);
    Copy_56175392(Interface, v16, v17, 0, v15, 0);
    *((u8 *)&v17[2].klass + v15) = 0;
  }
  Item = get_Item((sdfIVector2_t)&message->fields, 0, 0);
  v19 = get_Item((sdfIVector2_t)&message->fields, 1, 0);
  v22 = itfMessageRequestExLocalize(Item, v19, message->last_style, message->last_col, message->last_tp, v20, v17, 0, 1, 0, 0);
  if (mode != 2)
  {
    if (pinst->type != 3)
    {
LABEL_37:
      if ((pinst->stat & 0x400000) != 0)
        goto LABEL_53;
      if ((g_manager->stat & 1) == 0)
      {
LABEL_53:
        if (v22)
        {
          str_end = v22->str_end;
          if (str_end)
          {
            v31 = v22->draw_spd >> 1;
            col_no = str_end->col_no;
            message->last_style = str_end->style;
            message->last_col = col_no;
            message->last_spd = v31;
            message->last_tp = str_end->tp;
          }
        }
        message->wait = gMessageRequestResult & 3;
        pinst->stat = pinst->stat & 0xFFFEFFFF | (((gMessageRequestResult >> 1) & 1) << 16);
        if ((gMessageRequestResult & 8) == 0)
        {
          z = pinst->z;
          goto LABEL_72;
        }
        lipsync_pm_local = lipsync_pm;
        *(u64 *)&lipsync_pm_local->start = 1;
        lipsync_pm_local->unit_uniqid = gLipsTarget;
        lipsync_pm_local->motion_no = gLipsType;
        lipsync_pm_local->autoTime = 240;
        z = pinst->z;
LABEL_72:
        if (!v22)
        {
LABEL_88:
          prev = v22;
          do
          {
            v42 = prev;
            prev = prev->prev;
          }
          while (prev);
          v43 = 715827883 * ((v22->y - v42->y) >> 3);
          message->lines = (v43 >> 34) + (v43 >> 63) + 1;
          goto LABEL_91;
        }
        v40 = v22;
        do
        {
          v40->priority = z;
          v40 = v40->prev;
        }
        while (v40);
        goto LABEL_88;
      }
      if (!v22)
        goto LABEL_53;
      v29 = v22;
      do
      {
        if (!v29->str->tp)
        {
          v29->draw_spd = 0x80;
        }
        v29 = v29->prev;
      }
      while (v29);
      goto LABEL_53;
    }
    if (v22)
    {
      head = v22->head;
      if (head)
      {
        v24 = 0;
        do
        {
          v25 = v24;
          next = head;
          do
          {
            if (next->y >= head->y + 100)
              break;
            next = next->next;
          }
          while (next);
          head = head->next;
          ++v24;
        }
        while (head);
        if (!v25)
        {
          v27 = 3168;
          goto LABEL_36;
        }
      }
    }
    v27 = 3064;
LABEL_36:
    frSetMessageCenter(4096, v27, v22);
    goto LABEL_37;
  }
LABEL_91:
  p_pfont = v22;
}

// 0x1c70570
s32 itfMesMngChkWaitTag(s32 msgid) {
  return g_manager->pmesflow[msgid]->pinst->message->wait & 1;
}

// 0x1c70600
void itfMesMngClearCursor(s32 id) {

}

// 0x1c70660
ITF_MESBINTYPE itfGetMessageType(s32 id, s32 message) {
  return GetTypeHeader(g_manager->pmesflow[id]->pinst, message)->type;
}

// 0x1c706f0
s32 itfGetMessageNo(s32 id) {
  Il2CppObject *pdata;
  itfMesBinFileHeader_t *v6;
  u8 *Interface;
  s32 pos;

  pos = 0;
  pdata = g_manager->pmesflow[id]->pinst->pdata;
  v6 = Allocate(itfMesBinFileHeader_t);
  else
  {
    Interface = 0;
  }
  _ctor(v6, Interface, &pos, 0);
  return v6->numtypeheader;
}

// 0x1c707f0
static void InputPasswdDraw(void) {
  u32 gInputPasswdVal_local;
  char **p_msg_guide_name;
  char *v5;
  u32 v7;
  s32 v8;
  s32 v9;
  f32 *p_r;
  f32 *p_g;
  f32 *p_b;
  f32 *p_a;
  s32 v14;
  bool v15;
  u32 v16;
  Il2CppObject *Item;
  void *v19;
  Il2CppObject *Component_object;
  char *v21;
  Il2CppObject *v22;
  void *v23;
  void *gameObject;
  _BOOL4 activeSelf;
  s32 v32;
  s32 v36;
  s32 v39;
  s32 v41;
  s32 v42;
  s32 v43;
  u32 v44;

  v44 = 0;
  gInputPasswdVal_local = gInputPasswdVal;
  NewSpecific(byte, 0x10u);
  ButtonTmpGuideObjClr();
  p_msg_guide_name = &msg_guide_name;
  v5 = "";
  *p_msg_guide_name = "";
  v7 = 0;
  v8 = 7;
  v9 = 1;
  do
  {
    if (PasswdNum)
    {
      Item = _get_Item(PasswdNum, v8);
      v19 = Find(Item, "Image_frame/Text (TMP)_num", 0);
      Component_object = GetComponent_object_(v19);
      v44 = gInputPasswdVal_local % 0xA;
      v21 = ToString((u32)&v44, 0);
      (Component_object->klass->vtable[66].methodPtr)(Component_object, v21, Component_object->klass->vtable[66].method);
      v22 = _get_Item(PasswdNum, v8);
      v23 = Find(v22, "arrow", 0);
      gameObject = get_gameObject(v23, 0);
      activeSelf = get_activeSelf(gameObject, 0);
      if (((activeSelf ^ (v8 != gInputPasswdPos)) & 1) == 0)
      {
        SetActive(gameObject, v8 == gInputPasswdPos, 0);
        if (v8 == gInputPasswdPos)
        {
          p_r = &gNumSelectCollar.r;
          p_g = &gNumSelectCollar.g;
          p_b = &gNumSelectCollar.b;
          p_a = &gNumSelectCollar.a;
        }
        else
        {
          p_r = &gNumCollar.r;
          p_g = &gNumCollar.g;
          p_b = &gNumCollar.b;
          p_a = &gNumCollar.a;
        }
        (Component_object->klass->vtable[23].methodPtr)(Component_object, Component_object->klass->vtable[23].*p_r, *p_g, *p_b, *p_a);
      }
    }
    v14 = gInputPasswdPos;
    if (v8 > v14)
      v9 *= 10;
    v15 = v8-- == v14;
    v16 = gInputPasswdVal_local % 0xA;
    gInputPasswdVal_local /= 0xAu;
    if (v15)
      v7 = v16;
  }
  while (v8 != -1);
  if (!CHECK_REP(4100, 1))
  {
    if (!CHECK_REP(4101, 1))
      goto LABEL_53;
LABEL_42:
    if (v7)
    {
      v36 = gInputPasswdVal - v9;
    }
    else
    {
      v36 = gInputPasswdVal + 9 * v9;
    }
    gInputPasswdVal = v36;
    SE(3);
    if (!CHECK_REP(4102, 1))
      goto LABEL_61;
LABEL_54:
    v39 = gInputPasswdPos;
    if (v39 < 1)
      goto LABEL_70;
    v39 = gInputPasswdPos;
    v42 = v39 - 1;
    goto LABEL_74;
  }
  if (v7 == 9)
  {
    v32 = gInputPasswdVal - 9 * v9;
  }
  else
  {
    v32 = gInputPasswdVal + v9;
  }
  gInputPasswdVal = v32;
  SE(3);
  if (CHECK_REP(4101, 1))
    goto LABEL_42;
LABEL_53:
  if (CHECK_REP(4102, 1))
    goto LABEL_54;
LABEL_61:
  if (!CHECK_REP(4103, 1))
    return;
  v41 = gInputPasswdPos;
  if (v41 <= 6)
    goto LABEL_71;
  goto LABEL_70;
  if (v41 > 6)
  {
LABEL_70:
    v43 = 2;
    goto LABEL_75;
  }
LABEL_71:
  v41 = gInputPasswdPos;
  v42 = v41 + 1;
LABEL_74:
  v43 = 3;
  gInputPasswdPos = v42;
LABEL_75:
  SE(v43);
}

// 0x1c70dd0
s32 itfInputPasswd(void) {
  s32 v1;
  s32 MessageHandle;
  u32 v3;
  instanceMes_tag *pinst;
  s32 IntPara;
  char *v8;
  char *v9;
  bool IsLoad;
  s32 v13;
  struct itf *v15;
  u32 *p_gInputPasswdVal;
  char v17;
  instanceMes_tag *v18;
  instanceMes_tag *v19;
  s32 v20;
  void *RootGameObjects;
  void *Instance;
  void *p_passwordUI;
  void *CanvasTransform;
  void *transform;
  void *v30;
  void *v31;
  u64 *v33;
  s32 i;
  void *PasswdNum_local;
  char *v38;
  char *v39;
  Il2CppObject *v40;
  s64 size;
  u64 *v42;
  Il2CppObject *v43;
  void *items;
  Il2CppClass **v45;
  Il2CppObject *Item;
  void *v48;
  Il2CppObject *Component_object;
  f32 v50;
  const MethodInfo_2DFC320 *v52;
  f32 v54;
  f32 v55;
  f32 v56;
  Il2CppObject *v57;
  void *v58;
  Il2CppObject *v59;
  f32 v60;
  f32 v62;
  f32 v63;
  f32 v64;
  bool v69;
  char v73;
  instanceMes_tag *v74;
  instanceMes_tag *v75;
  void *p_PasswdNum;
  void *v79;
  char *v80;
  s32 v81;
  s32 m_Handle;
  UnityEngine_SceneManagement_Scene_o v83;

  m_Handle = 0;
  v81 = 0;
  v1 = 1;
  scrEventSkipEnd(1, 0);
  scrEventSkipRestartFlagChange();
  MessageHandle = scrGetMessageHandle();
  if ((MessageHandle & 0x80000000) == 0)
  {
    v3 = MessageHandle;
    pinst = g_manager->pmesflow[v3]->pinst;
    IntPara = scrGetIntPara(0);
    v8 = "UI_ansyo_num";
    v9 = "UI_ansyo";
    if (pinst->message->phase)
    {
      IsLoad = IsLoad(_Ctrl_k__BackingField, v9, 0);
      if (!IsLoad)
        goto LABEL_62;
      if (PasswdNum)
        goto LABEL_62;
      m_Handle = GetSceneByName(v8, 0).m_Handle;
      RootGameObjects = GetRootGameObjects((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0);
      Instance = get_Instance(0);
      p_passwordUI = &passwordUI;
      p_passwordUI = Instance;
      if (SLODWORD(RootGameObjects->max_length) <= 0)
      {
LABEL_64:
        if (op_Equality(passwordUI, 0, 0))
          return 0;
        InputPasswdDraw();
        if (!gInputPasswdEndFlag)
        {
          v69 = CHECK_TRIG(4096, 1);
          if (v69)
          {
            gInputPasswdEndFlag = 1;
            SE(0);
          }
        }
        if (!gInputPasswdEndFlag)
          return 0;
        if (gInputPasswdPanelAlpha)
          return 0;
        v73 = 1;
        v74 = g_manager->pmesflow[v3]->pinst;
        v74->stat &= ~0x800000u;
        v75 = g_manager->pmesflow[v3]->pinst;
        v75->stat &= ~0x100000u;
        g_manager->pmesflow[v3]->pinst->message->phase = 0;
        itfMesMngRequestMessageRelease(v3, 0);
        scrSetIntReturnValue(gInputPasswdVal);
        p_PasswdNum = &PasswdNum;
        p_PasswdNum = 0;
        v83.m_Handle = GetSceneByName(v8, 0).m_Handle;
        UnloadSceneAsync_61083440(v83, 0);
        Unload(Dependent, v9, 0);
        v79 = &passwordUI;
        v79 = 0;
        scrEventSkipRestart();
        return 1;
      }
      CanvasTransform = dds3GetCanvasTransform(RootGameObjects[0]);
      transform = get_transform(CanvasTransform, 0);
      v30 = Find(transform, "password", 0);
      v31 = Allocate(System_Collections_Generic_List_Transform_);
      __ctor(v31);
      v80 = v8;
      v33 = &PasswdNum;
      *v33 = v31;
      for (i = 1; i != 9; ++i)
      {
        while (1)
        {
          v81 = i;
          PasswdNum_local = PasswdNum;
          v38 = ToString((s32)&v81, 0);
          v39 = Concat_54766928("number_area/pin_base0", v38, 0);
          v40 = Find(v30, v39, 0);
          size = PasswdNum_local->_size;
          v42 = Method_System_Collections_Generic_List_Transform__Add__;
          v43 = v40;
          ++PasswdNum_local->_version;
          items = PasswdNum_local->_items;
          if ((u32)size < LODWORD(items->max_length))
            break;
          _AddWithResize(PasswdNum_local, v40, *(const MethodInfo_2DFC660 **)(*(u64 *)(v42[4] + 192) + 112));
          if (++i == 9)
            goto LABEL_59;
        }
        v45 = &items->obj.klass + size;
        PasswdNum_local->_size = size + 1;
        v45[4] = v43;
      }
LABEL_59:
      v8 = v80;
      Item = _get_Item(PasswdNum, 0);
      v48 = Find(Item, "Image_frame/Text (TMP)_num", 0);
      Component_object = GetComponent_object_(v48);
      v50 = (Component_object->klass->vtable[22].methodPtr)(Component_object, Component_object->klass->vtable[22].method);
      v52 = Method_System_Collections_Generic_List_Transform__get_Item__;
      gNumSelectCollar.r = v50;
      gNumSelectCollar.g = v54;
      gNumSelectCollar.b = v55;
      gNumSelectCollar.a = v56;
      v57 = _get_Item(PasswdNum, 1, v52);
      v58 = Find(v57, "Image_frame/Text (TMP)_num", 0);
      v59 = GetComponent_object_(v58);
      v60 = (v59->klass->vtable[22].methodPtr)(v59, v59->klass->vtable[22].method);
      gNumCollar.r = v60;
      gNumCollar.g = v62;
      gNumCollar.b = v63;
      gNumCollar.a = v64;
LABEL_62:
      goto LABEL_64;
    }
    v13 = IntPara;
    p_gInputPasswdVal = &gInputPasswdVal;
    gInputPasswdCurTimer = 0;
    *(u64 *)&gInputPasswdVal = 0;
    LOBYTE(v15) = byte_575759B;
    *(u32 *)((char *)p_gInputPasswdVal + 7) = 0;
    v17 = 1;
    v18 = g_manager->pmesflow[v3]->pinst;
    v18->stat |= 0x800000u;
    v19 = g_manager->pmesflow[v3]->pinst;
    v19->stat |= 0x100000u;
    v20 = itfMesMngRequestMessage(v3, v13, 0, 0, 0);
    Load(Dependent, v9, v9);
    LoadSyncAll(_Ctrl_k__BackingField, 0);
    LoadSceneAsync(_Ctrl_k__BackingField, v8, 0);
    return !v20;
  }
  return v1;
}

// 0x1c71830
s32 itfMsgAutoSetUp(void) {
  s32 IntPara;
  LIPSYNC_PARAM *v7;
  s32 v8;
  LIPSYNC_PARAM *v10;

  if (scrGetMessageHandle() < 0)
    return 1;
  IntPara = scrGetIntPara(0);
  lipsync_pm->script_auto_skip = IntPara;
  v7 = lipsync_pm;
  v8 = scrGetIntPara(1);
  v7->script_auto_time = v8;
  v10 = lipsync_pm;
  v10->script_guide_disp = scrGetIntPara(2);
  return 1;
}

// 0x1c71970
static void MoneyCallProcEnd(tagITF_MONEY_WORK *wk) {
  dds3ProcessID_t *countPID;
  dds3ProcessID_t *v5;

  countPID = wk->countPID;
  v5 = countPID;
  itfCountProcessEnd(v5);
}

// 0x1c71a00
static u8 MoneyCheckProcEnd(tagITF_MONEY_WORK *wk) {
  dds3ProcessID_t *p_countPID;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *countPID;
  dds3ProcessID_t *id;

  countPID = wk->countPID;
  p_countPID = &wk->countPID;
  v5 = countPID;
  id = v5;
  if (!v5)
    goto LABEL_17;
  if (dds3GetProcessStat(id) == 3)
    goto LABEL_17;
  if (dds3GetProcessStat(id))
    return 1;
LABEL_17:
  p_countPID = 0;
  return 0;
}

// 0x1c71b50
static dds3ProcessFunc_t MoneyProcess(dds3ProcessID_t *PID) {
  tagITF_MONEY_WORK *ProcessData;
  u8 flags;
  dds3ProcessFunc_t v7;
  s32 count;
  u8 v9;
  dds3ProcessID_t *p_countPID;
  dds3ProcessID_t *countPID;
  u8 v12;
  s32 calc;
  s32 type;
  u8 v17;
  dds3ProcessID_t *v19;
  s32 v22;
  dds3ProcessID_t *v24;
  dds3ProcessID_t *id;
  dds3ProcessID_t *v28;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (ProcessData->step)
  {
    case 0u:
      flags = ProcessData->flags;
      if ((flags & 2) == 0)
        return 0;
      v7 = 0;
      ProcessData->count = 0;
      ProcessData->flags = flags & 0x7D | 0x80;
      ProcessData->step = 1;
      return v7;
    case 1u:
      count = ProcessData->count;
      if (count < 10)
        goto LABEL_54;
      v7 = 0;
      ProcessData->count = 0;
      ProcessData->step = 2;
      return v7;
    case 2u:
      v9 = ProcessData->flags;
      if ((v9 & 8) == 0)
      {
        if ((ProcessData->flags & 4) == 0)
          return 0;
        ProcessData->countPID = 0;
        p_countPID = &ProcessData->countPID;
        *((u8 *)p_countPID + 17) = v9 & 0xFB;
        v7 = 0;
        *((u32 *)p_countPID + 5) = 0;
        *((u8 *)p_countPID + 8) = 4;
        return v7;
      }
      ProcessData->countPID = 0;
      ProcessData->flags = v9 & 0xF7;
      calc = ProcessData->calc;
      if (calc < 1)
        goto LABEL_67;
      type = ProcessData->type;
      if (type == 1)
      {
        calc = -calc;
      }
      else
      {
        if (type != 2)
          goto LABEL_63;
      }
      datAddMoney(calc);
LABEL_63:
      v22 = ProcessData->calc;
      v24 = itfCountProcessStart(v22, 30, 2, 5);
      ProcessData->countPID = v24;
      itfCountSetData(ProcessData->countPID, ProcessData->money, ProcessData->type);
      itfCountSetMin(ProcessData->countPID, ProcessData->money, 0);
LABEL_67:
      v7 = 0;
      ProcessData->step = 3;
      return v7;
    case 3u:
      countPID = ProcessData->countPID;
      v28 = ProcessData->countPID;
      if (countPID)
      {
        if (dds3GetProcessStat(v28) != 3)
        {
          if (dds3GetProcessStat(v28))
            return 0;
        }
      }
      ProcessData->countPID = 0;
      v17 = ProcessData->flags;
      v7 = 0;
      if ((v17 & 4) != 0)
      {
        v7 = 0;
        ProcessData->count = 0;
        ProcessData->flags = v17 & 0xFB;
        ProcessData->step = 4;
      }
      return v7;
    case 4u:
      count = ProcessData->count;
      if (count < 10)
        goto LABEL_54;
      v12 = ProcessData->flags;
      v7 = 0;
      ProcessData->count = 0;
      ProcessData->step = 0;
      ProcessData->flags = v12 & 0x7F;
      return v7;
    case 5u:
      if (ProcessData->count)
      {
        goto LABEL_25;
      }
      v19 = ProcessData->countPID;
      itfCountProcessEnd(v19);
LABEL_25:
      if (MoneyCheckProcEnd(ProcessData))
      {
        count = ProcessData->count;
        goto LABEL_54;
      }
      v7 = 0;
      ProcessData->count = 0;
      ProcessData->step = 6;
      return v7;
    case 6u:
      count = ProcessData->count;
      if (count)
      {
        if (count >= 2)
        {
          v7 = 0;
          ProcessData->count = 0;
          ProcessData->step = 7;
          return v7;
        }
      }
      else
      {
        ProcessData->flags &= ~0x80u;
      }
LABEL_54:
      v7 = 0;
      ProcessData->count = count + 1;
      return v7;
    case 7u:
      v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v7, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v7;
    default:
      return 0;
  }
}

// 0x1c720b0
static void MoneyDrawPanel(s32 a_offX, s32 a_offY, u8 a_alpha) {
  _OWORD *v4;
  u64 v10[2];
  __int128 v11;
  __int128 v12;
  __int128 v13;
  __int128 v14;
  sdfIVector4_t v15;
  sdfIVector4_t v16;
  sdfIVector4_t v17;
  sdfIVector4_t v18;
  sdfIVector4_t v19;

  v4 = NewSpecific(sdfIVector4_t, 4u);
  v14 = 0u;
  *(u64 *)&v15.x = &v14;
  *(u64 *)&v15.z = 1856;
  _ctor(v15, 352, 2016, 832, 0);
  *(u64 *)&v16.z = 2000;
  *(u64 *)&v16.x = &v13;
  v4[2] = v14;
  v13 = 0u;
  _ctor(v16, 352, 2016, 832, 0);
  *(u64 *)&v17.x = &v12;
  *(u64 *)&v17.z = 2016;
  v4[3] = v13;
  v12 = 0u;
  _ctor(v17, 352, 1856, 832, 0);
  *(u64 *)&v18.z = 432;
  *(u64 *)&v18.x = &v11;
  v4[4] = v12;
  v11 = 0u;
  _ctor(v18, 1600, 640, 1824, 0);
  *(u64 *)&v19.x = v10;
  *(u64 *)&v19.z = 128;
  v4[5] = v11;
  v10[0] = 0;
  v10[1] = 0;
  _ctor(v19, 128, 128, 128, 0);
}

// 0x1c721e0
static dds3ProcessFunc_t MoneyDrawProcess(dds3ProcessID_t *PID) {
  u8 v4;
  Il2CppObject *ProcessData;
  s32 klass_low;
  f32 v9;
  s32 v10;
  s32 v11;
  Il2CppObject *v13;
  s32 data;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((SBYTE1(ProcessData[2].monitor) & 0x80000000) == 0)
    return 0;
  klass_low = LOBYTE(ProcessData[2].klass);
  v9 = (f32)((f32)SHIDWORD(ProcessData[2].monitor) * 1.5707964) / 10.0;
  if (klass_low == 4)
  {
    sub_188E3D0(v9);
    v10 = 1280 - (HIDWORD(ProcessData[2].monitor) << 7);
  }
  else
  {
    if (klass_low != 1)
    {
      v11 = 128;
      goto LABEL_16;
    }
    sub_188E3D0(v9);
    v10 = HIDWORD(ProcessData[2].monitor) << 7;
  }
  v11 = v10 / 10;
LABEL_16:
  MoneyDrawPanel((s32)itf, (s32)tagITF_MONEY_WORK, v4);
  data = ProcessData[3].klass;
  v13 = Box(s32, &data);
  Format("{0,7}", v13, 0);
  return 0;
}

// 0x1c72440
static void MoneyShutdown(dds3ProcessID_t *PID) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *p_g_mainPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagITF_MONEY_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagITF_MONEY_WORK;
  v5 = ProcessData + 2;
  if (dds3ExistProcess(ProcessData + 2))
  {
    dds3KillProcess(v5, 0);
  }
  v5 = 0;
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = 0;
}

// 0x1c72590
void itfMoneyProcessStart(void) {
  tagITF_MONEY_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_g_mainPID;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;

  v1 = Allocate(tagITF_MONEY_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_itf_MoneyProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_itf_MoneyShutdown__, 0);
  started = dds3StartProcess("itfmoney_main", 1024, 0, 0, v2, v3, v1);
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_itf_MoneyDrawProcess__, 0);
  v8 = dds3StartProcess("itfmoney_draw", 11015, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
}

// 0x1c727a0
void itfMoneyProcessEnd(void) {
  Il2CppObject *ProcessData;
  char v6;

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
  v6 = BYTE1(ProcessData[2].monitor);
  if ((v6 & 1) == 0)
  {
    HIDWORD(ProcessData[2].monitor) = 0;
    BYTE1(ProcessData[2].monitor) = v6 | 1;
    LOBYTE(ProcessData[2].klass) = 5;
  }
}

// 0x1c72960
bool itfMoneyProcessCheck(void) {
  dds3ProcessID_t *p_g_mainPID;

  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
      return 1;
  }
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = 0;
  return 0;
}

// 0x1c72ad0
bool itfMoneyCheckWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return LOBYTE(ProcessData[2].klass) == 0;
  return LOBYTE(ProcessData[2].klass) == 0;
}

// 0x1c72bf0
bool itfMoneySetDrawOn(void) {
  u8 *ProcessData;
  u8 *v4;
  s32 v6;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  v6 = ProcessData[32];
  if (ProcessData[32])
    return v6 == 0;
  *((u32 *)v4 + 12) = GBWK->player->gold;
  v4[41] |= 2u;
  return v6 == 0;
}

// 0x1c72d70
bool itfMoneySetDrawOff(void) {
  char *ProcessData;
  u32 v5;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v5 = ProcessData[41];
  if ((v5 & 0x80000000) != 0)
    ProcessData[41] = v5 | 4;
  return (v5 >> 7) & 1;
}

// 0x1c72ea0
bool itfMoneySetAddMoney(s32 a_money) {
  Il2CppObject *ProcessData;
  char v7;
  s32 v8;
  s32 v9;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v7 = BYTE1(ProcessData[2].monitor);
  if ((v7 & 8) == 0)
  {
    BYTE1(ProcessData[2].monitor) = v7 | 8;
    if (a_money >= 0)
      v8 = a_money;
    else
      v8 = -a_money;
    HIDWORD(ProcessData[3].klass) = v8;
    if (a_money < 0)
      v9 = 1;
    else
      v9 = 2;
    HIDWORD(ProcessData[2].klass) = v9;
  }
  return (v7 & 8) == 0;
}

// 0x1c731c0
void itfInitMoneyManager(void *s_work) {
  void *p_mnwork;

  p_mnwork = &mnwork;
  p_mnwork = s_work;
  SetActiveGo(mnwork, 0, 0);
}

// 0x1c73280
void itfSetMoneyText(void) {
  char *v4;
  char *LocalizeText;
  void *v6;
  char *v7;

  v4 = strSystem[3];
  LocalizeText = GetLocalizeText(v4, 1);
  SetYenText(mnwork, LocalizeText, 0);
  v6 = mnwork;
  v7 = GetLocalizeText(strSystem[4], 1);
  SetPosseText(v6, v7, 0);
}

// 0x1c730d0
void itfSetMoneyActive(bool sw) {
  SetActiveGo(mnwork, sw, 0);
}

// 0x1c733c0
void itfCtrlMoney(f32 alpha, char *money) {
  isMoneyDisp = 1;
  SetActiveGo(mnwork, 1, 0);
  SetMoneyText(mnwork, money, 0);
}

// 0x1c73540
void SetMoneyText(char *money) {
  SetMoneyText(mnwork, money, 0);
}

// 0x1c73530
void itfSetMoneyAlpha(f32 alpha) {
  ;
}

// 0x1c4b350
bool itfMoverInit(itfMover_t *mv) {
  if (mv)
  {
    *(u64 *)&mv->cb_cnt = 0;
    *(u64 *)&mv->total_cnt = 0;
  }
  return mv != 0;
}

// 0x1c4b370
bool itfMoverSetData(itfMover_t *mv, s32 a_posx, s32 a_posy, s32 a_tgtx, s32 a_tgty, f32 a_rate, s32 a_waitBefore, s32 a_waitAfter, s32 a_frame) {
  s64 cb_num;
  f32 v11;
  s16 v12;
  f32 v13;
  itfMoverCB_t *v14;
  f32 v15;
  s8 *wait;
  s8 *v17;
  s16 v18;
  s32 total_frm;
  s32 frame;
  s16 v21;

  if (mv)
  {
    cb_num = mv->cb_num;
    if (cb_num > 3)
    {
      LOBYTE(mv) = 0;
      return (char)mv;
    }
    v11 = a_posx;
    if (a_frame << 16 <= 0)
      v12 = 1;
    else
      v12 = a_frame;
    v13 = a_posy;
    v14 = mv->cb[cb_num];
    v14->frame = v12;
    v14->posx = v11;
    v14->posy = (f32)a_posy;
    v14->tgtx = (f32)a_tgtx;
    v14->tgty = (f32)a_tgty;
    v14->rate = a_rate;
    if (a_rate >= 0.0)
    {
      v15 = v12;
      v11 = (f32)((f32)a_tgtx - v11) / v15;
      v13 = (f32)((f32)a_tgty - v13) / v15;
    }
    wait = v14->wait;
    v14->movx = v11;
    v14->movy = v13;
    wait[0] = a_waitBefore;
    v14->wait[1] = a_waitAfter;
    v17 = v14->wait;
    if (v17[0] < 0)
    {
      v17[0] = 0;
      v17 = v14->wait;
      if ((v17[1] & 0x80000000) == 0)
        goto LABEL_10;
    }
    else if ((v17[1] & 0x80000000) == 0)
    {
LABEL_10:
      v18 = mv->cb_num;
      mv->cb_cnt = 0;
      mv->cnt = 0;
      total_frm = mv->total_frm;
      frame = v14->frame;
      mv->total_cnt = 0;
      mv->cb_num = v18 + 1;
      v21 = mv->flag & 0xFFFC;
      mv->total_frm = total_frm + frame + v17[0] + v17[1];
      mv->flag = v21 | 1;
      LOBYTE(mv) = 1;
      return (char)mv;
    }
    v17[1] = 0;
    v17 = v14->wait;
    goto LABEL_10;
  }
  return (char)mv;
}

// 0x1c43e50
bool itfMoverSetParam(itfMover_t *mv, s32 a_posx, s32 a_posy, s32 a_tgtx, s32 a_tgty, s32 a_frame) {
  f32 v13;
  f32 v14;
  f32 v15;
  s16 v16;
  itfMoverCB_t *cb;
  f32 v18;
  itfMoverCB_t *v19;
  s8 *wait;
  s8 *v21;
  s16 cb_num;
  s32 total_frm;
  s32 frame;
  u16 flag;

  if (mv)
  {
    v13 = a_posx;
    v14 = a_posy;
    v15 = a_tgtx;
    if (a_frame << 16 <= 0)
      v16 = 1;
    else
      v16 = a_frame;
    cb = mv->cb;
    *(u64 *)&mv->cb_cnt = 0;
    *(u64 *)&mv->total_cnt = 0;
    v18 = v16;
    v19 = cb[0];
    v19->frame = v16;
    wait = v19->wait;
    v19->rate = 0.0;
    v19->posx = v13;
    v19->posy = v14;
    v19->tgtx = v15;
    v19->tgty = (f32)a_tgty;
    v19->movx = (f32)(v15 - v13) / v18;
    v19->movy = (f32)((f32)a_tgty - v14) / v18;
    wait[0] = 0;
    v19->wait[1] = 0;
    v21 = v19->wait;
    if (v21[0] < 0)
    {
      v21[0] = 0;
      v21 = v19->wait;
      if ((v21[1] & 0x80000000) == 0)
        goto LABEL_11;
    }
    else if ((v21[1] & 0x80000000) == 0)
    {
LABEL_11:
      cb_num = mv->cb_num;
      mv->cb_cnt = 0;
      mv->cnt = 0;
      total_frm = mv->total_frm;
      frame = v19->frame;
      mv->total_cnt = 0;
      mv->cb_num = cb_num + 1;
      flag = mv->flag;
      mv->total_frm = total_frm + frame + v21[0] + v21[1];
      mv->flag = flag & 0xFFFC | 1;
      return mv != 0;
    }
    v21[1] = 0;
    v21 = v19->wait;
    goto LABEL_11;
  }
  return mv != 0;
}

// 0x1c44570
ITF_MOVER_UPDATE itfMoverUpdate(itfMover_t *mv) {
  u16 flag;
  s64 cb_cnt;
  s16 cnt;
  float32x2_t *v7;
  u64 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 cb_num;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  float32x2_t v23;

  if (!mv)
    return -1;
  flag = mv->flag;
  if ((flag & 2) != 0)
    return 2;
  if ((flag & 1) == 0)
    return 0;
  cb_cnt = mv->cb_cnt;
  cnt = mv->cnt;
  if (!((u16)cb_cnt | (u16)cnt))
  {
    cnt = 0;
    mv->total_cnt = 0;
  }
  v7 = mv->cb[cb_cnt];
  v8 = v7[6].n64_u64[0];
  v9 = *(char *)(v8 + 32);
  if (v9 > cnt)
    goto LABEL_10;
  v10 = v7[7].n64_i16[0];
  v11 = v10 + v9;
  if (v10 + v9 > cnt)
  {
    if (v11 - 1 == cnt)
    {
      v7[2].n64_u64[0] = v7[3].n64_u64[0];
    }
    else
    {
      v13 = v7[5].n64_f32[0];
      if (v13 >= 0.0)
      {
        v23.n64_u64[0] = vadd_f32(v7[2], v7[4]).n64_u64[0];
        v7[2].n64_u64[0] = v23.n64_u64[0];
        if (v13 > 0.0)
          v7[4].n64_u64[0] = vmul_n_f32(vsub_f32(v7[3], v23), v13).n64_u64[0];
      }
      else
      {
        v14 = v7[4].n64_f32[0];
        v15 = v7[3].n64_f32[0];
        v16 = (f32)((f32)(cnt - v9) * 1.5707964) / (f32)(s16)v10;
        v17 = sub_188E3D0(v16);
        v18 = v15 - v14;
        v19 = v7[3].n64_f32[1];
        v20 = v14 + (f32)(v18 * v17);
        v21 = v7[4].n64_f32[1];
        v7[2].n64_f32[0] = v20;
        v22 = sub_188E3D0(v16);
        cnt = mv->cnt;
        v7[2].n64_f32[1] = v21 + (f32)((f32)(v19 - v21) * v22);
      }
    }
    goto LABEL_10;
  }
  if (v11 + *(char *)(v8 + 33) - 1 > cnt)
  {
LABEL_10:
    mv->cnt = cnt + 1;
    ++mv->total_cnt;
    return 1;
  }
  cb_num = mv->cb_num;
  mv->cnt = 0;
  mv->cb_cnt = cb_cnt + 1;
  if (cb_num > (s16)(cb_cnt + 1))
    return 1;
  mv->cb_cnt = cb_cnt;
  mv->total_cnt = 0;
  mv->flag = flag | 2;
  return 2;
}

// 0x1c44d80
bool itfMoverGetPosition(itfMover_t *mv, f32 *a_pPosX, f32 *a_pPosY) {
  itfMoverCB_t *cb;
  s64 cb_cnt;
  itfMoverCB_t *v6;

  if (mv)
  {
    if (mv->cb_num < 1)
    {
      LOBYTE(mv) = 0;
    }
    else
    {
      cb = mv->cb;
      cb_cnt = mv->cb_cnt;
      v6 = cb[cb_cnt];
      *a_pPosX = v6->posx;
      *a_pPosY = v6->posy;
      LOBYTE(mv) = 1;
    }
  }
  return (char)mv;
}

// 0x1c735b0
bool itfMoverChkEnd(itfMover_t *mv) {
  _BOOL4 v2;

  if (mv)
    return (mv->flag >> 1) & 1;
  else
    LOBYTE(v2) = 1;
  return v2;
}

// 0x1c44d00
f32 itfMoverGetRatio(itfMover_t *mv) {
  f32 result;
  u16 flag;
  s32 total_frm;
  s32 total_cnt;
  s32 v6;
  bool v7;
  s32 v8;
  s32 v9;
  f32 v11;

  result = 0.0;
  if (mv)
  {
    flag = mv->flag;
    if ((flag & 2) != 0)
    {
      return 1.0;
    }
    else if ((flag & 1) != 0)
    {
      total_frm = mv->total_frm;
      if (total_frm >= 1)
      {
        total_cnt = mv->total_cnt;
        v6 = mv->cb[0]->wait[0];
        v7 = __OFSUB__(total_cnt, v6);
        v8 = total_cnt - v6;
        if (v8 < 0 == v7)
        {
          v9 = total_frm - v6;
          if (v8 >= 1 && v9 >= 1)
          {
            v11 = (f32)v8 / (f32)v9;
            if (v11 >= 0.0)
            {
              result = 1.0;
              if (v11 <= 1.0)
                return (f32)v8 / (f32)v9;
            }
          }
        }
      }
    }
  }
  return result;
}

// 0x1c735f0
static void CreateVertexNormal(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1) {
  s32 *v11;
  sdfIVector2_t *pvertex;
  s32 *v13;
  s32 v14;

  v11 = NewSpecific(s32, 4u);
  pvertex = pwork->pvertex;
  v13 = v11;
  v11[8] = x0;
  v11[9] = x0 + 512;
  v11[10] = x1 - 512;
  v11[11] = x1;
  if (x0 + 512 > x1 - 512)
  {
    v14 = x0 + ((x1 - x0) >> 1);
    v11[9] = v14;
    v11[10] = v14;
  }
  set_Item((sdfIVector2_t)pvertex, 0, x0, 0);
  set_Item((sdfIVector2_t)pvertex, 1, y0, 0);
  set_Item((sdfIVector2_t)&pvertex[1], 0, v13[8], 0);
  set_Item((sdfIVector2_t)&pvertex[1], 1, y1, 0);
  set_Item((sdfIVector2_t)&pvertex[2], 0, v13[9], 0);
  set_Item((sdfIVector2_t)&pvertex[2], 1, y0, 0);
  set_Item((sdfIVector2_t)&pvertex[3], 0, v13[9], 0);
  set_Item((sdfIVector2_t)&pvertex[3], 1, y1, 0);
  set_Item((sdfIVector2_t)&pvertex[4], 0, v13[10], 0);
  set_Item((sdfIVector2_t)&pvertex[4], 1, y0, 0);
  set_Item((sdfIVector2_t)&pvertex[5], 0, v13[10], 0);
  set_Item((sdfIVector2_t)&pvertex[5], 1, y1, 0);
  set_Item((sdfIVector2_t)&pvertex[6], 0, v13[11], 0);
  set_Item((sdfIVector2_t)&pvertex[6], 1, y0, 0);
  set_Item((sdfIVector2_t)&pvertex[7], 0, v13[11], 0);
  set_Item((sdfIVector2_t)&pvertex[7], 1, y1, 0);
}

// 0x1c737f0
static void CreateVertexMesWin(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1) {
  sdfIVector2_t *pvertex;
  s32 *v12;
  int32x4_t *v13;
  s32 v14;
  s32 *v15;
  u64 v16;
  int32x4_t v17;
  sdfIVector2_t v18;
  s32 v19;
  s64 v20;
  s32 v22;
  s32 v24;
  s32 v26;
  s32 v28;
  sdfIVector2_t v29;
  s64 i;
  s32 v32;
  s32 v34;
  s32 v36;
  s32 v38;
  u64 v39;

  pvertex = pwork->pvertex;
  v12 = NewSpecific(s32, 4u);
  v13 = NewSpecific(s32, 4u);
  v12[9] = x0 + 512;
  v12[10] = x1 - 512;
  v14 = x1 + 256;
  v12[11] = x1 + 256;
  v15 = v13;
  v16 = vadd_s32(vdup_n_s32(x0), (int32x2_t)0x400FFFFFF00LL).n64_u64[0];
  v12[8] = v16;
  v39 = v16;
  v17.n128_u64[0] = __PAIR64__(y1, y0);
  v13[2] = vaddq_s32(vzip1q_s32(v17, v17), (int32x4_t)xmmword_3CFDF00);
  set_Item((sdfIVector2_t)pvertex, 0, v12[8], 0);
  set_Item((sdfIVector2_t)pvertex, 1, v15[8], 0);
  set_Item((sdfIVector2_t)&pvertex[1], 0, v12[9], 0);
  set_Item((sdfIVector2_t)&pvertex[1], 1, v15[8], 0);
  set_Item((sdfIVector2_t)&pvertex[2], 0, v12[10], 0);
  set_Item((sdfIVector2_t)&pvertex[2], 1, v15[8], 0);
  v18 = (sdfIVector2_t)&pvertex[3];
  set_Item((sdfIVector2_t)&pvertex[3], 0, v12[11], 0);
  set_Item((sdfIVector2_t)&pvertex[3], 1, v15[8], 0);
  set_Item((sdfIVector2_t)&pvertex[4], 0, v12[8], 0);
  set_Item((sdfIVector2_t)&pvertex[4], 1, v15[9], 0);
  set_Item((sdfIVector2_t)&pvertex[5], 0, v12[9], 0);
  set_Item((sdfIVector2_t)&pvertex[5], 1, v15[9], 0);
  set_Item((sdfIVector2_t)&pvertex[6], 0, v12[10], 0);
  set_Item((sdfIVector2_t)&pvertex[6], 1, v15[9], 0);
  set_Item((sdfIVector2_t)&pvertex[7], 0, v12[11], 0);
  set_Item((sdfIVector2_t)&pvertex[7], 1, v15[9], 0);
  set_Item((sdfIVector2_t)&pvertex[8], 0, v12[8], 0);
  set_Item((sdfIVector2_t)&pvertex[8], 1, v15[10], 0);
  set_Item((sdfIVector2_t)&pvertex[9], 0, v12[9], 0);
  set_Item((sdfIVector2_t)&pvertex[9], 1, v15[10], 0);
  set_Item((sdfIVector2_t)&pvertex[10], 0, v12[10], 0);
  set_Item((sdfIVector2_t)&pvertex[10], 1, v15[10], 0);
  set_Item((sdfIVector2_t)&pvertex[11], 0, v12[11], 0);
  set_Item((sdfIVector2_t)&pvertex[11], 1, v15[10], 0);
  set_Item((sdfIVector2_t)&pvertex[12], 0, v12[8], 0);
  set_Item((sdfIVector2_t)&pvertex[12], 1, v15[11], 0);
  set_Item((sdfIVector2_t)&pvertex[13], 0, v12[9], 0);
  set_Item((sdfIVector2_t)&pvertex[13], 1, v15[11], 0);
  set_Item((sdfIVector2_t)&pvertex[14], 0, v12[10], 0);
  set_Item((sdfIVector2_t)&pvertex[14], 1, v15[11], 0);
  set_Item((sdfIVector2_t)&pvertex[15], 0, v12[11], 0);
  set_Item((sdfIVector2_t)&pvertex[15], 1, v15[11], 0);
  v19 = x1 - 1024;
  v20 = 32;
  v12[10] = v19;
  v12[11] = v14;
  *((u64 *)v12 + 4) = v39;
  v15[8] = y0;
  do
  {
    set_Item((sdfIVector2_t)(*(u64 *)&v18 - 24), 0, v12[8], 0);
    v22 = v15[8];
    set_Item((sdfIVector2_t)(*(u64 *)&v18 - 24), 1, *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + v20) + v22, 0);
    set_Item((sdfIVector2_t)(*(u64 *)&v18 - 16), 0, v12[9], 0);
    v24 = v15[8];
    set_Item((sdfIVector2_t)(*(u64 *)&v18 - 16), 1, *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + v20) + v24, 0);
    set_Item((sdfIVector2_t)(*(u64 *)&v18 - 8), 0, v12[10], 0);
    v26 = v15[8];
    set_Item((sdfIVector2_t)(*(u64 *)&v18 - 8), 1, *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + v20) + v26, 0);
    set_Item(v18, 0, v12[11], 0);
    v28 = v15[8];
    set_Item(v18, 1, *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + v20) + v28, 0);
    v20 += 4;
    *(u64 *)&v18 += 32;
  }
  while (v20 != 44);
  v15[8] = y1;
  v29 = (sdfIVector2_t)&pvertex[3];
  for (i = 32; i != 44; i += 4)
  {
    set_Item((sdfIVector2_t)(*(u64 *)&v29 - 24), 0, v12[8], 0);
    v32 = v15[8];
    set_Item((sdfIVector2_t)(*(u64 *)&v29 - 24), 1, v32 - *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + i), 0);
    set_Item((sdfIVector2_t)(*(u64 *)&v29 - 16), 0, v12[9], 0);
    v34 = v15[8];
    set_Item((sdfIVector2_t)(*(u64 *)&v29 - 16), 1, v34 - *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + i), 0);
    set_Item((sdfIVector2_t)(*(u64 *)&v29 - 8), 0, v12[10], 0);
    v36 = v15[8];
    set_Item((sdfIVector2_t)(*(u64 *)&v29 - 8), 1, v36 - *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + i), 0);
    set_Item(v29, 0, v12[11], 0);
    v38 = v15[8];
    set_Item(v29, 1, v38 - *(u32 *)((char *)&CreateVertexMesWin_plinestep->obj.klass + i), 0);
    *(u64 *)&v29 += 32;
  }
}

// 0x1c73e80
static void CreateVertexSelWin(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1) {
  s32 *v11;
  int32x4_t *v12;
  s32 *v13;
  u64 v14;
  int32x4_t v15;
  sdfIVector2_t pvertex;
  sdfIVector2_t v17;
  sdfIVector2_t v18;
  sdfIVector2_t v19;
  sdfIVector2_t v20;
  sdfIVector2_t v21;
  sdfIVector2_t v22;
  sdfIVector2_t v23;
  s32 v24;
  s32 v25;
  s32 v26;
  u64 v27;
  s32 v28;

  v11 = NewSpecific(s32, 4u);
  v12 = NewSpecific(s32, 4u);
  v11[9] = x0 + 512;
  v11[10] = x1 - 512;
  v26 = x1 + 256;
  v11[11] = x1 + 256;
  v13 = v12;
  v14 = vadd_s32(vdup_n_s32(x0), (int32x2_t)0x400FFFFFF00LL).n64_u64[0];
  v11[8] = v14;
  v27 = v14;
  v15.n128_u64[0] = __PAIR64__(y1, y0);
  v28 = y1;
  pvertex = (sdfIVector2_t)pwork->pvertex;
  v12[2] = vaddq_s32(vzip1q_s32(v15, v15), (int32x4_t)xmmword_3CFDF00);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 32), 0, v11[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 32), 1, v13[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 40), 0, v11[9], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 40), 1, v13[9], 0);
  v25 = y0;
  v17 = (sdfIVector2_t)(*(u64 *)&pvertex + 48);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 48), 0, v11[10], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 48), 1, v13[10], 0);
  v24 = x1;
  v18 = (sdfIVector2_t)(*(u64 *)&pvertex + 56);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 56), 0, v11[11], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 56), 1, v13[11], 0);
  v19 = (sdfIVector2_t)(*(u64 *)&pvertex + 64);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 64), 0, v11[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 64), 1, v13[8], 0);
  v20 = (sdfIVector2_t)(*(u64 *)&pvertex + 72);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 72), 0, v11[9], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 72), 1, v13[9], 0);
  v21 = (sdfIVector2_t)(*(u64 *)&pvertex + 80);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 80), 0, v11[10], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 80), 1, v13[10], 0);
  v22 = (sdfIVector2_t)(*(u64 *)&pvertex + 88);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 88), 0, v11[11], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 88), 1, v13[11], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 96), 0, v11[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 96), 1, v13[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 104), 0, v11[9], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 104), 1, v13[9], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 112), 0, v11[10], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 112), 1, v13[10], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 120), 0, v11[11], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 120), 1, v13[11], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 128), 0, v11[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 128), 1, v13[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 136), 0, v11[9], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 136), 1, v13[9], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 144), 0, v11[10], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 144), 1, v13[10], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 152), 0, v11[11], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 152), 1, v13[11], 0);
  v23 = (sdfIVector2_t)(*(u64 *)&pvertex + 32);
  *((u64 *)v11 + 4) = v27;
  v11[10] = v24 - 1024;
  v11[11] = v26;
  v13[8] = v25;
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 32), 0, v11[8], 0);
  set_Item((sdfIVector2_t)(*(u64 *)&pvertex + 32), 1, v13[8], 0);
  *(u64 *)&pvertex += 40;
  set_Item(pvertex, 0, v11[9], 0);
  set_Item(pvertex, 1, v13[8], 0);
  set_Item(v17, 0, v11[10], 0);
  set_Item(v17, 1, v13[8], 0);
  set_Item(v18, 0, v11[11], 0);
  set_Item(v18, 1, v13[8], 0);
  set_Item(v19, 0, v11[8], 0);
  set_Item(v19, 1, v13[8] + 8, 0);
  set_Item(v20, 0, v11[9], 0);
  set_Item(v20, 1, v13[8] + 8, 0);
  set_Item(v21, 0, v11[10], 0);
  set_Item(v21, 1, v13[8] + 8, 0);
  set_Item(v22, 0, v11[11], 0);
  set_Item(v22, 1, v13[8] + 8, 0);
  v13[8] = v28;
  set_Item(v23, 0, v11[8], 0);
  set_Item(v23, 1, v13[8], 0);
  set_Item(pvertex, 0, v11[9], 0);
  set_Item(pvertex, 1, v13[8], 0);
  set_Item(v17, 0, v11[10], 0);
  set_Item(v17, 1, v13[8], 0);
  set_Item(v18, 0, v11[11], 0);
  set_Item(v18, 1, v13[8], 0);
  set_Item(v19, 0, v11[8], 0);
  set_Item(v19, 1, v13[8] - 8, 0);
  set_Item(v20, 0, v11[9], 0);
  set_Item(v20, 1, v13[8] - 8, 0);
  set_Item(v21, 0, v11[10], 0);
  set_Item(v21, 1, v13[8] - 8, 0);
  set_Item(v22, 0, v11[11], 0);
  set_Item(v22, 1, v13[8] - 8, 0);
}

// 0x1c74510
static void CreateVertexPlain(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1) {
  sdfIVector2_t *pvertex;

  pvertex = pwork->pvertex;
  set_Item((sdfIVector2_t)pvertex, 0, x0, 0);
  set_Item((sdfIVector2_t)pvertex, 1, y0, 0);
  set_Item((sdfIVector2_t)&pvertex[1], 0, x1, 0);
  set_Item((sdfIVector2_t)&pvertex[1], 1, y0, 0);
  set_Item((sdfIVector2_t)&pvertex[2], 0, x1, 0);
  set_Item((sdfIVector2_t)&pvertex[2], 1, y1, 0);
  set_Item((sdfIVector2_t)&pvertex[3], 0, x0, 0);
  set_Item((sdfIVector2_t)&pvertex[3], 1, y1, 0);
}

// 0x1c74600
static void CreateVertexLeftFade(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1) {
  sdfIVector2_t *pvertex;
  s32 *v12;
  s32 *v13;
  s64 v14;

  pvertex = pwork->pvertex;
  v12 = NewSpecific(s32, 3u);
  v13 = NewSpecific(s32, 2u);
  v12[10] = x1;
  v12[8] = x0;
  v12[9] = x1 - 1440;
  v14 = v13;
  v13[0] = y0;
  v13[1] = y1;
  set_Item((sdfIVector2_t)pvertex, 0, v12[8], 0);
  set_Item((sdfIVector2_t)pvertex, 1, *(u32 *)(v14 + 32), 0);
  set_Item((sdfIVector2_t)&pvertex[1], 0, v12[9], 0);
  set_Item((sdfIVector2_t)&pvertex[1], 1, *(u32 *)(v14 + 32), 0);
  set_Item((sdfIVector2_t)&pvertex[2], 0, v12[10], 0);
  set_Item((sdfIVector2_t)&pvertex[2], 1, *(u32 *)(v14 + 32), 0);
  set_Item((sdfIVector2_t)&pvertex[3], 0, v12[8], 0);
  set_Item((sdfIVector2_t)&pvertex[3], 1, *(u32 *)(v14 + 36), 0);
  set_Item((sdfIVector2_t)&pvertex[4], 0, v12[9], 0);
  set_Item((sdfIVector2_t)&pvertex[4], 1, *(u32 *)(v14 + 36), 0);
  set_Item((sdfIVector2_t)&pvertex[5], 0, v12[10], 0);
  set_Item((sdfIVector2_t)&pvertex[5], 1, *(u32 *)(v14 + 36), 0);
}

// 0x1c747b0
static void CreateVertexFacility(itfPanelTypeWork_t *pwork, s32 x0, s32 y0, s32 x1, s32 y1) {
  s32 *v9;
  s32 *v10;
  sdfIVector2_t *pvertex;
  s64 v12;

  v9 = NewSpecific(s32, 4u);
  v10 = NewSpecific(s32, 2u);
  pvertex = pwork->pvertex;
  v12 = v10;
  *((_OWORD *)v9 + 2) = xmmword_3CFE760;
  v10[0] = y0 + 352;
  v10[1] = y1 - 320;
  set_Item((sdfIVector2_t)pvertex, 0, v9[8], 0);
  set_Item((sdfIVector2_t)pvertex, 1, *(u32 *)(v12 + 32), 0);
  set_Item((sdfIVector2_t)&pvertex[1], 0, v9[8], 0);
  set_Item((sdfIVector2_t)&pvertex[1], 1, *(u32 *)(v12 + 36), 0);
  set_Item((sdfIVector2_t)&pvertex[2], 0, v9[9], 0);
  set_Item((sdfIVector2_t)&pvertex[2], 1, *(u32 *)(v12 + 32), 0);
  set_Item((sdfIVector2_t)&pvertex[3], 0, v9[9], 0);
  set_Item((sdfIVector2_t)&pvertex[3], 1, *(u32 *)(v12 + 36), 0);
  set_Item((sdfIVector2_t)&pvertex[4], 0, v9[10], 0);
  set_Item((sdfIVector2_t)&pvertex[4], 1, *(u32 *)(v12 + 32), 0);
  set_Item((sdfIVector2_t)&pvertex[5], 0, v9[10], 0);
  set_Item((sdfIVector2_t)&pvertex[5], 1, *(u32 *)(v12 + 36), 0);
  set_Item((sdfIVector2_t)&pvertex[6], 0, v9[11], 0);
  set_Item((sdfIVector2_t)&pvertex[6], 1, *(u32 *)(v12 + 32), 0);
  set_Item((sdfIVector2_t)&pvertex[7], 0, v9[11], 0);
  set_Item((sdfIVector2_t)&pvertex[7], 1, *(u32 *)(v12 + 36), 0);
}

// 0x1c749b0
static void CreateColorNormal(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha) {
  sdfIVector4_t *pcolor;
  sdfIVector4_t v18;
  sdfIVector4_t v19;
  sdfIVector4_t v20;
  sdfIVector4_t v21;
  sdfIVector4_t v22;
  sdfIVector4_t v23;
  sdfIVector4_t v24;
  sdfIVector4_t v25;

  pcolor = pwork->pcolor;
  *(u64 *)&v18.z = 0;
  *(u64 *)&v18.x = pcolor;
  set_Item(v18, red, 0, *(const MethodInfo **)&alpha);
  *(u64 *)&v19.x = pcolor;
  *(u64 *)&v19.z = 1;
  set_Item(v19, green, 0);
  *(u64 *)&v20.x = pcolor;
  *(u64 *)&v20.z = 2;
  set_Item(v20, blue, 0);
  *(u64 *)&v21.x = pcolor;
  *(u64 *)&v21.z = 3;
  set_Item(v21, 0, 0);
  *(u64 *)&v22.z = 0;
  *(u64 *)&v22.x = &pcolor[1];
  set_Item(v22, red, 0);
  *(u64 *)&v23.x = &pcolor[1];
  *(u64 *)&v23.z = 1;
  set_Item(v23, green, 0);
  *(u64 *)&v24.x = &pcolor[1];
  *(u64 *)&v24.z = 2;
  set_Item(v24, blue, 0);
  *(u64 *)&v25.x = &pcolor[1];
  *(u64 *)&v25.z = 3;
  set_Item(v25, alpha, 0);
}

// 0x1c74a90
static void CreateColorMesWin(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha) {
  sdfIVector4_t *pout;
  sdfIVector4_t v21;
  sdfIVector4_t v22;
  sdfIVector4_t v23;
  sdfIVector4_t v24;
  sdfIVector4_t v25;
  sdfIVector4_t v26;
  sdfIVector4_t v27;
  sdfIVector4_t v28;

  *(u64 *)&v21.z = 0;
  pout = pwork->pcolor;
  *(u64 *)&v21.x = pout;
  set_Item(v21, red, 0, *(const MethodInfo **)&alpha);
  *(u64 *)&v22.x = pout;
  *(u64 *)&v22.z = 1;
  set_Item(v22, green, 0);
  *(u64 *)&v23.x = pout;
  *(u64 *)&v23.z = 2;
  set_Item(v23, blue, 0);
  *(u64 *)&v24.x = pout;
  *(u64 *)&v24.z = 3;
  set_Item(v24, 1, 0);
  *(u64 *)&v25.z = 0;
  *(u64 *)&v25.x = &pout[1];
  set_Item(v25, red, 0);
  *(u64 *)&v26.x = &pout[1];
  *(u64 *)&v26.z = 1;
  set_Item(v26, green, 0);
  *(u64 *)&v27.x = &pout[1];
  *(u64 *)&v27.z = 2;
  set_Item(v27, blue, 0);
  *(u64 *)&v28.x = &pout[1];
  *(u64 *)&v28.z = 3;
  set_Item(v28, alpha, 0);
  itfMiscSetRatioRGB(&pout, 2, red, green, blue, alpha, CreateColorMesWin_pratio, 6);
}

// 0x1c74c40
static void CreateColorSelWin(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha) {
  sdfIVector4_t *pout;
  sdfIVector4_t v21;
  sdfIVector4_t v22;
  sdfIVector4_t v23;
  sdfIVector4_t v24;
  sdfIVector4_t v25;
  sdfIVector4_t v26;
  sdfIVector4_t v27;
  sdfIVector4_t v28;

  *(u64 *)&v21.z = 0;
  pout = pwork->pcolor;
  *(u64 *)&v21.x = pout;
  set_Item(v21, red, 0, *(const MethodInfo **)&alpha);
  *(u64 *)&v22.x = pout;
  *(u64 *)&v22.z = 1;
  set_Item(v22, green, 0);
  *(u64 *)&v23.x = pout;
  *(u64 *)&v23.z = 2;
  set_Item(v23, blue, 0);
  *(u64 *)&v24.x = pout;
  *(u64 *)&v24.z = 3;
  set_Item(v24, 1, 0);
  *(u64 *)&v25.z = 0;
  *(u64 *)&v25.x = &pout[1];
  set_Item(v25, red, 0);
  *(u64 *)&v26.x = &pout[1];
  *(u64 *)&v26.z = 1;
  set_Item(v26, green, 0);
  *(u64 *)&v27.x = &pout[1];
  *(u64 *)&v27.z = 2;
  set_Item(v27, blue, 0);
  *(u64 *)&v28.x = &pout[1];
  *(u64 *)&v28.z = 3;
  set_Item(v28, alpha, 0);
  itfMiscSetRatioRGB(&pout, 2, red, green, blue, alpha, CreateColorSelWin_pratio, 4);
}

// 0x1c74df0
static void CreateColorPlain(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha) {
  sdfIVector4_t *pcolor;
  sdfIVector4_t *m_Items;
  sdfIVector4_t *pout;
  sdfIVector4_t v19;
  sdfIVector4_t v20;
  sdfIVector4_t v21;
  sdfIVector4_t v22;

  *(u64 *)&v19.z = 0;
  pcolor = pwork->pcolor;
  m_Items = pcolor;
  pout = pcolor;
  *(u64 *)&v19.x = pcolor;
  set_Item(v19, red, 0, *(const MethodInfo **)&alpha);
  *(u64 *)&v20.x = m_Items;
  *(u64 *)&v20.z = 1;
  set_Item(v20, green, 0);
  *(u64 *)&v21.x = m_Items;
  *(u64 *)&v21.z = 2;
  set_Item(v21, blue, 0);
  *(u64 *)&v22.x = m_Items;
  *(u64 *)&v22.z = 3;
  set_Item(v22, alpha, 0);
  itfMiscSetRatioRGB(&pout, 1, red, green, blue, alpha, CreateColorPlain_pratio_back, 1);
  itfMiscSetRatioRGB(&pout, 2, red, green, blue, 128, CreateColorPlain_pratio, 2);
}

// 0x1c74f70
static void CreateColorPera1(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha) {
  s64 v10;
  sdfIVector4_t v14;
  sdfIVector4_t v15;
  sdfIVector4_t v16;
  sdfIVector4_t v17;

  *(u64 *)&v14.z = 0;
  *(u64 *)&v14.x = pwork->pcolor;
  v10 = *(u64 *)&v14.x;
  set_Item(v14, red, 0, *(const MethodInfo **)&alpha);
  *(u64 *)&v15.x = v10;
  *(u64 *)&v15.z = 1;
  set_Item(v15, green, 0);
  *(u64 *)&v16.x = v10;
  *(u64 *)&v16.z = 2;
  set_Item(v16, blue, 0);
  *(u64 *)&v17.x = v10;
  *(u64 *)&v17.z = 3;
  set_Item(v17, alpha, 0);
}

// 0x1c74ff0
static void CreateColorLeftFade(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha) {
  sdfIVector4_t *pcolor;
  sdfIVector4_t v18;
  sdfIVector4_t v19;
  sdfIVector4_t v20;
  sdfIVector4_t v21;
  sdfIVector4_t v22;
  sdfIVector4_t v23;
  sdfIVector4_t v24;
  sdfIVector4_t v25;

  pcolor = pwork->pcolor;
  *(u64 *)&v18.z = 0;
  *(u64 *)&v18.x = pcolor;
  set_Item(v18, red, 0, *(const MethodInfo **)&alpha);
  *(u64 *)&v19.x = pcolor;
  *(u64 *)&v19.z = 1;
  set_Item(v19, green, 0);
  *(u64 *)&v20.x = pcolor;
  *(u64 *)&v20.z = 2;
  set_Item(v20, blue, 0);
  *(u64 *)&v21.x = pcolor;
  *(u64 *)&v21.z = 3;
  set_Item(v21, 0, 0);
  *(u64 *)&v22.z = 0;
  *(u64 *)&v22.x = &pcolor[1];
  set_Item(v22, red, 0);
  *(u64 *)&v23.x = &pcolor[1];
  *(u64 *)&v23.z = 1;
  set_Item(v23, green, 0);
  *(u64 *)&v24.x = &pcolor[1];
  *(u64 *)&v24.z = 2;
  set_Item(v24, blue, 0);
  *(u64 *)&v25.x = &pcolor[1];
  *(u64 *)&v25.z = 3;
  set_Item(v25, alpha, 0);
}

// 0x1c750d0
static void CreateColorFacility(itfPanelTypeWork_t *pwork, s32 red, s32 green, s32 blue, s32 alpha) {
  sdfIVector4_t *pcolor;
  sdfIVector4_t v14;
  sdfIVector4_t v15;
  sdfIVector4_t v16;
  sdfIVector4_t v17;
  sdfIVector4_t v18;
  sdfIVector4_t v19;
  sdfIVector4_t v20;
  sdfIVector4_t v21;

  pcolor = pwork->pcolor;
  *(u64 *)&v14.z = 0;
  *(u64 *)&v14.x = pcolor;
  set_Item(v14, 115, 0, *(const MethodInfo **)&alpha);
  *(u64 *)&v15.x = pcolor;
  *(u64 *)&v15.z = 1;
  set_Item(v15, 135, 0);
  *(u64 *)&v16.x = pcolor;
  *(u64 *)&v16.z = 2;
  set_Item(v16, 255, 0);
  *(u64 *)&v17.x = pcolor;
  *(u64 *)&v17.z = 3;
  set_Item(v17, 0, 0);
  *(u64 *)&v18.z = 0;
  *(u64 *)&v18.x = &pcolor[1];
  set_Item(v18, 115, 0);
  *(u64 *)&v19.x = &pcolor[1];
  *(u64 *)&v19.z = 1;
  set_Item(v19, 135, 0);
  *(u64 *)&v20.x = &pcolor[1];
  *(u64 *)&v20.z = 2;
  set_Item(v20, 255, 0);
  *(u64 *)&v21.x = &pcolor[1];
  *(u64 *)&v21.z = 3;
  set_Item(v21, 0, 0);
}

// 0x1c751a0
static void DrawNormal(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  itfPanelTypeWork_t *pwork;
  sdfIVector4_t *pcolor;
  s32 Item;
  sdfIVector4_t v8;
  sdfIVector4_t v9;

  pwork = handle->pwork;
  *(u64 *)&v8.x = &handle->color;
  *(u64 *)&v8.z = 3;
  pcolor = pwork->pcolor;
  Item = get_Item(v8, 0);
  *(u64 *)&v9.x = &pcolor[1];
  *(u64 *)&v9.z = 3;
  set_Item(v9, Item, 0);
}

// 0x1c751e0
static void DrawMesWin(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  s32 Item;
  sdfIVector4_t *pcolor;
  sdfIVector4_t v14;
  sdfIVector4_t v15;
  sdfIVector4_t v16;
  sdfIVector4_t v17;
  sdfIVector4_t v18;
  sdfIVector4_t v19;
  sdfIVector4_t v20;
  sdfIVector4_t v21;

  *(u64 *)&v14.x = &handle->color;
  *(u64 *)&v14.z = 3;
  Item = get_Item(v14, 0);
  *(u64 *)&v15.z = 3;
  pcolor = handle->pwork->pcolor;
  *(u64 *)&v15.x = &pcolor[1];
  set_Item(v15, Item, 0);
  *(u64 *)&v16.x = &pcolor[2];
  *(u64 *)&v16.z = 3;
  set_Item(v16, Item, 0);
  *(u64 *)&v17.x = &pcolor[3];
  *(u64 *)&v17.z = 3;
  set_Item(v17, Item, 0);
  *(u64 *)&v18.x = &pcolor[4];
  *(u64 *)&v18.z = 3;
  set_Item(v18, Item, 0);
  *(u64 *)&v19.x = &pcolor[5];
  *(u64 *)&v19.z = 3;
  set_Item(v19, Item, 0);
  *(u64 *)&v20.x = &pcolor[6];
  *(u64 *)&v20.z = 3;
  set_Item(v20, Item, 0);
  *(u64 *)&v21.x = &pcolor[7];
  *(u64 *)&v21.z = 3;
  set_Item(v21, Item, 0);
}

// 0x1c752a0
static void DrawSelWin(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  s32 Item;
  sdfIVector4_t *v6;
  sdfIVector4_t v12;
  sdfIVector4_t v13;
  sdfIVector4_t v14;
  sdfIVector4_t v15;
  sdfIVector4_t v16;
  sdfIVector4_t v17;

  *(u64 *)&v12.x = &handle->color;
  *(u64 *)&v12.z = 3;
  Item = get_Item(v12, 0);
  v6 = NewSpecific(sdfIVector4_t, 4u);
  *(u64 *)&v13.x = &v6[1];
  *(u64 *)&v13.z = 3;
  set_Item(v13, Item, 0);
  *(u64 *)&v14.x = &v6[2];
  *(u64 *)&v14.z = 3;
  set_Item(v14, Item, 0);
  *(u64 *)&v15.x = &v6[3];
  *(u64 *)&v15.z = 3;
  set_Item(v15, Item, 0);
  *(u64 *)&v16.x = &v6[4];
  *(u64 *)&v16.z = 3;
  set_Item(v16, Item, 0);
  *(u64 *)&v17.x = &v6[5];
  *(u64 *)&v17.z = 3;
  set_Item(v17, Item, 0);
}

// 0x1c75370
static void DrawPlain(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  sdfIVector2_t v4;
  sdfIVector2_t *pvertex;
  sdfIVector2_t m_Items;
  sdfIVector2_t v7;
  sdfIVector2_t v8;
  sdfIVector2_t v9;
  s32 Item;
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
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;

  v4 = (sdfIVector2_t)NewSpecific(sdfIVector2_t, 0xCu);
  pvertex = handle->pwork->pvertex;
  m_Items = (sdfIVector2_t)pvertex;
  v7 = (sdfIVector2_t)&pvertex[1];
  v8 = (sdfIVector2_t)&pvertex[2];
  v9 = (sdfIVector2_t)&pvertex[3];
  Item = get_Item((sdfIVector2_t)pvertex, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 32), 0, Item, 0);
  v11 = get_Item(m_Items, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 32), 1, v11, 0);
  v12 = get_Item(v7, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 40), 0, v12, 0);
  v13 = get_Item(v7, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 40), 1, v13, 0);
  v14 = get_Item(v8, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 48), 0, v14, 0);
  v15 = get_Item(v8, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 48), 1, v15, 0);
  v16 = get_Item(v9, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 56), 0, v16, 0);
  v17 = get_Item(v9, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 56), 1, v17, 0);
  v18 = get_Item(m_Items, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 64), 0, v18 + 16, 0);
  v19 = get_Item(m_Items, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 64), 1, v19 + 8, 0);
  v20 = get_Item(v7, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 72), 0, v20 - 16, 0);
  v21 = get_Item(v7, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 72), 1, v21 + 8, 0);
  v22 = get_Item(v8, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 80), 0, v22 - 16, 0);
  v23 = get_Item(v8, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 80), 1, v23 - 8, 0);
  v24 = get_Item(v9, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 88), 0, v24 + 16, 0);
  v25 = get_Item(v9, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 88), 1, v25 - 8, 0);
  v26 = get_Item(m_Items, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 96), 0, v26 + 32, 0);
  v27 = get_Item(m_Items, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 96), 1, v27 + 16, 0);
  v28 = get_Item(v7, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 104), 0, v28 - 32, 0);
  v29 = get_Item(v7, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 104), 1, v29 + 16, 0);
  v30 = get_Item(v8, 0, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 112), 0, v30 - 32, 0);
  v31 = get_Item(v8, 1, 0);
  set_Item((sdfIVector2_t)(*(u64 *)&v4 + 112), 1, v31 - 16, 0);
  v32 = get_Item(v9, 0, 0);
  *(u64 *)&v4 += 120;
  set_Item(v4, 0, v32 + 32, 0);
  v33 = get_Item(v9, 1, 0);
  set_Item(v4, 1, v33 - 16, 0);
}

// 0x1c75780
static void DrawPera1(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  itfPanelTypeWork_t *pwork;
  sdfIVector4_t *pcolor;
  s32 Item;
  sdfIVector4_t v8;
  sdfIVector4_t v9;

  pwork = handle->pwork;
  *(u64 *)&v8.x = &handle->color;
  *(u64 *)&v8.z = 3;
  pcolor = pwork->pcolor;
  Item = get_Item(v8, 0);
  *(u64 *)&v9.x = pcolor;
  *(u64 *)&v9.z = 3;
  set_Item(v9, Item, 0);
}

// 0x1c757c0
static void DrawLeftFade(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  s32 Item;
  sdfIVector4_t v7;
  sdfIVector4_t v8;

  *(u64 *)&v7.x = &handle->color;
  *(u64 *)&v7.z = 3;
  Item = get_Item(v7, 0);
  *(u64 *)&v8.z = 3;
  *(u64 *)&v8.x = &handle->pwork->pcolor[1];
  set_Item(v8, Item, 0);
}

// 0x1c75810
static void DrawMesWin2(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  sdfDrawTag_t *v4;
  sdfIVector4_t *p_pos;
  s32 Item;
  void *v10;
  void *v11;
  s32 v12;
  s32 v14;
  s32 v16;
  s32 v19;
  s32 v22;
  void *v25;
  void *v26;
  void *v29;
  void *v30;
  s32 v33;
  void *v35;
  void *v36;
  u64 v37[2];
  sdfIVector4_t v38;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;
  sdfIVector4_t v42;
  sdfIVector4_t v43;
  sdfIVector4_t v44;
  sdfIVector4_t v45;
  sdfIVector4_t v46;
  sdfIVector4_t v47;
  sdfIVector4_t v48;
  sdfIVector4_t v49;
  sdfIVector4_t v50;
  sdfIVector4_t v51;
  sdfIVector4_t v52;
  sdfIVector4_t v53;

  v4 = Allocate(sdfDrawTag_t);
  _ctor(v4, 0);
  p_pos = &handle->pos;
  *(u64 *)&v38.z = 3;
  *(u64 *)&v38.x = p_pos;
  Item = get_Item(v38, 0);
  *(u64 *)&v39.x = p_pos;
  *(u64 *)&v39.z = 1;
  if (Item - get_Item(v39, 0) < 5005)
  {
    sdfDrawTagInit(v4);
    v10 = Allocate(Project_itf_packettestalpha_tag);
    _ctor(v10, 0);
    v11 = Allocate(Project_itf_packettestalpha_tag);
    _ctor(v11, 0);
    return;
  }
  *(u64 *)&v40.x = p_pos;
  *(u64 *)&v40.z = 1;
  v37[0] = 0;
  v37[1] = 0;
  v12 = get_Item(v40, 0) + 2502;
  *(u64 *)&v41.x = p_pos;
  *(u64 *)&v41.z = 3;
  v14 = get_Item(v41, 0) - 2502;
  *(u64 *)&v42.x = p_pos;
  *(u64 *)&v42.z = 0;
  v16 = get_Item(v42, 0);
  *(u64 *)&v43.x = v37;
  *(u64 *)&v43.z = 0;
  set_Item(v43, v16, 0);
  *(u64 *)&v44.x = p_pos;
  *(u64 *)&v44.z = 1;
  v19 = get_Item(v44, 0);
  *(u64 *)&v45.x = v37;
  *(u64 *)&v45.z = 1;
  set_Item(v45, v19, 0);
  *(u64 *)&v46.x = p_pos;
  *(u64 *)&v46.z = 2;
  v22 = get_Item(v46, 0);
  *(u64 *)&v47.x = v37;
  *(u64 *)&v47.z = 2;
  set_Item(v47, v22, 0);
  *(u64 *)&v48.x = v37;
  *(u64 *)&v48.z = 3;
  set_Item(v48, v12, 0);
  sdfDrawTagInit(v4);
  v25 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v25, 0);
  v26 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v26, 0);
  *(u64 *)&v49.x = v37;
  *(u64 *)&v49.z = 1;
  set_Item(v49, v12, 0);
  *(u64 *)&v50.x = v37;
  *(u64 *)&v50.z = 3;
  set_Item(v50, v14, 0);
  sdfDrawTagInit(v4);
  v29 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v29, 0);
  v30 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v30, 0);
  *(u64 *)&v51.x = v37;
  *(u64 *)&v51.z = 1;
  set_Item(v51, v14, 0);
  *(u64 *)&v52.x = p_pos;
  *(u64 *)&v52.z = 3;
  v33 = get_Item(v52, 0);
  *(u64 *)&v53.x = v37;
  *(u64 *)&v53.z = 3;
  set_Item(v53, v33, 0);
  sdfDrawTagInit(v4);
  v35 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v35, 0);
  v36 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v36, 0);
}

// 0x1c75be0
static void DrawSpkWin2(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  sdfDrawTag_t *v6;
  sdfIVector4_t *p_pos;
  s32 v9;
  s32 v11;
  s32 Item;
  s32 v16;
  s32 v20;
  void *v22;
  void *v23;
  s32 v26;
  s32 v30;
  void *v32;
  void *v33;
  s32 v35;
  s32 v38;
  s32 v42;
  void *v44;
  void *v45;
  u64 v46[2];
  u64 v47[2];
  u64 v48[2];
  sdfIVector4_t v49;
  sdfIVector4_t v50;
  sdfIVector4_t v51;
  sdfIVector4_t v52;
  sdfIVector4_t v53;
  sdfIVector4_t v54;
  sdfIVector4_t v55;
  sdfIVector4_t v56;
  sdfIVector4_t v57;
  sdfIVector4_t v58;
  sdfIVector4_t v59;
  sdfIVector4_t v60;
  sdfIVector4_t v61;
  sdfIVector4_t v62;
  sdfIVector4_t v63;
  sdfIVector4_t v64;
  sdfIVector4_t v65;
  sdfIVector4_t v66;
  sdfIVector4_t v67;
  sdfIVector4_t v68;
  sdfIVector4_t v69;
  sdfIVector4_t v70;
  sdfIVector4_t v71;
  sdfIVector4_t v72;

  *(u64 *)&v49.x = v47;
  v47[0] = 0;
  v47[1] = 0;
  *(u64 *)&v49.z = 3776;
  _ctor(v49, 2752, 7440, 3776, 0);
  *(u64 *)&v50.z = 7376;
  *(u64 *)&v50.x = v46;
  v46[0] = 0;
  v46[1] = 0;
  _ctor(v50, 2752, 7440, 3776, 0);
  v6 = Allocate(sdfDrawTag_t);
  _ctor(v6, 0);
  p_pos = &handle->pos;
  *(u64 *)&v51.z = 0;
  *(u64 *)&v51.x = p_pos;
  v48[0] = 0;
  v48[1] = 0;
  v9 = get_Item(v51, 0) + 992;
  *(u64 *)&v52.x = p_pos;
  *(u64 *)&v52.z = 2;
  v11 = get_Item(v52, 0) - 992;
  *(u64 *)&v53.x = p_pos;
  *(u64 *)&v53.z = 0;
  Item = get_Item(v53, 0);
  *(u64 *)&v54.x = v48;
  *(u64 *)&v54.z = 0;
  set_Item(v54, Item, 0);
  *(u64 *)&v55.x = p_pos;
  *(u64 *)&v55.z = 1;
  v16 = get_Item(v55, 0);
  *(u64 *)&v56.x = v48;
  *(u64 *)&v56.z = 1;
  set_Item(v56, v16, 0);
  *(u64 *)&v57.x = v48;
  *(u64 *)&v57.z = 2;
  set_Item(v57, v9, 0);
  *(u64 *)&v58.x = p_pos;
  *(u64 *)&v58.z = 3;
  v20 = get_Item(v58, 0);
  *(u64 *)&v59.x = v48;
  *(u64 *)&v59.z = 3;
  set_Item(v59, v20, 0);
  sdfDrawTagInit(v6);
  v22 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v22, 0);
  v23 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v23, 0);
  *(u64 *)&v60.x = v48;
  *(u64 *)&v60.z = 0;
  set_Item(v60, v9, 0);
  *(u64 *)&v61.x = p_pos;
  *(u64 *)&v61.z = 1;
  v26 = get_Item(v61, 0);
  *(u64 *)&v62.x = v48;
  *(u64 *)&v62.z = 1;
  set_Item(v62, v26, 0);
  *(u64 *)&v63.x = v48;
  *(u64 *)&v63.z = 2;
  set_Item(v63, v11, 0);
  *(u64 *)&v64.x = p_pos;
  *(u64 *)&v64.z = 3;
  v30 = get_Item(v64, 0);
  *(u64 *)&v65.x = v48;
  *(u64 *)&v65.z = 3;
  set_Item(v65, v30, 0);
  sdfDrawTagInit(v6);
  v32 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v32, 0);
  v33 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v33, 0);
  *(u64 *)&v66.x = p_pos;
  *(u64 *)&v66.z = 2;
  v35 = get_Item(v66, 0);
  *(u64 *)&v67.x = v48;
  *(u64 *)&v67.z = 0;
  set_Item(v67, v35, 0);
  *(u64 *)&v68.x = p_pos;
  *(u64 *)&v68.z = 1;
  v38 = get_Item(v68, 0);
  *(u64 *)&v69.x = v48;
  *(u64 *)&v69.z = 1;
  set_Item(v69, v38, 0);
  *(u64 *)&v70.x = v48;
  *(u64 *)&v70.z = 2;
  set_Item(v70, v11, 0);
  *(u64 *)&v71.x = p_pos;
  *(u64 *)&v71.z = 3;
  v42 = get_Item(v71, 0);
  *(u64 *)&v72.x = v48;
  *(u64 *)&v72.z = 3;
  set_Item(v72, v42, 0);
  sdfDrawTagInit(v6);
  v44 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v44, 0);
  v45 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v45, 0);
}

// 0x1c75f50
static void DrawFacility(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  itfPanelTypeWork_t *pwork;
  sdfIVector4_t *pcolor;
  s32 v7;
  sdfIVector4_t *p_pos;
  s32 v13;
  s32 v15;
  s32 Item;
  s32 v20;
  s32 v23;
  s32 v30;
  u64 v32[2];
  sdfIVector4_t v33;
  sdfIVector4_t v34;
  sdfIVector4_t v35;
  sdfIVector4_t v36;
  sdfIVector4_t v37;
  sdfIVector4_t v38;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;
  sdfIVector4_t v42;
  sdfIVector4_t v43;
  sdfIVector4_t v44;
  sdfIVector4_t v45;
  sdfIVector4_t v46;
  sdfIVector4_t v47;
  sdfIVector4_t v48;
  sdfIVector4_t v49;
  sdfIVector4_t v50;

  pwork = handle->pwork;
  *(u64 *)&v33.x = &handle->color;
  *(u64 *)&v33.z = 3;
  pcolor = pwork->pcolor;
  v7 = (32 * get_Item(v33, 0)) >> 7;
  *(u64 *)&v34.z = 3;
  *(u64 *)&v34.x = &pcolor[1];
  set_Item(v34, v7, 0);
  p_pos = &handle->pos;
  *(u64 *)&v35.z = 3;
  *(u64 *)&v35.x = p_pos;
  LODWORD(pcolor) = get_Item(v35, 0);
  *(u64 *)&v36.x = p_pos;
  *(u64 *)&v36.z = 1;
  if ((s32)pcolor - get_Item(v36, 0) >= 1385)
  {
    *(u64 *)&v37.x = p_pos;
    *(u64 *)&v37.z = 1;
    v32[0] = 0;
    v32[1] = 0;
    v13 = get_Item(v37, 0) + 692;
    *(u64 *)&v38.x = p_pos;
    *(u64 *)&v38.z = 3;
    v15 = get_Item(v38, 0) - 692;
    *(u64 *)&v39.x = p_pos;
    *(u64 *)&v39.z = 0;
    Item = get_Item(v39, 0);
    *(u64 *)&v40.x = v32;
    *(u64 *)&v40.z = 0;
    set_Item(v40, Item, 0);
    *(u64 *)&v41.x = p_pos;
    *(u64 *)&v41.z = 1;
    v20 = get_Item(v41, 0);
    *(u64 *)&v42.x = v32;
    *(u64 *)&v42.z = 1;
    set_Item(v42, v20, 0);
    *(u64 *)&v43.x = p_pos;
    *(u64 *)&v43.z = 2;
    v23 = get_Item(v43, 0);
    *(u64 *)&v44.x = v32;
    *(u64 *)&v44.z = 2;
    set_Item(v44, v23, 0);
    *(u64 *)&v45.x = v32;
    *(u64 *)&v45.z = 3;
    set_Item(v45, v13, 0);
    *(u64 *)&v46.x = v32;
    *(u64 *)&v46.z = 1;
    set_Item(v46, v13, 0);
    *(u64 *)&v47.x = v32;
    *(u64 *)&v47.z = 3;
    set_Item(v47, v15, 0);
    *(u64 *)&v48.x = v32;
    *(u64 *)&v48.z = 1;
    set_Item(v48, v15, 0);
    *(u64 *)&v49.x = p_pos;
    *(u64 *)&v49.z = 3;
    v30 = get_Item(v49, 0);
    *(u64 *)&v50.x = v32;
    *(u64 *)&v50.z = 3;
    set_Item(v50, v30, 0);
  }
}

// 0x1c75b80
static void DrawTestAlphaPrim(sdfDrawTag_t *pdrawtag) {
  void *v2;
  void *v3;

  v2 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v2, 0);
  v3 = Allocate(Project_itf_packettestalpha_tag);
  _ctor(v3, 0);
}

// 0x1c5d5d0
itfpanel_t *itfPnlRegist2(s32 type) {
  u8 v2;
  itfpanel_t *v3;
  itfPanelTypeWork_t *v5;

  v2 = type;
  v3 = (itfpanel_t *)Allocate(itfpanel_t);
  _ctor(v3, 0);
  v3->type = v2;
  v5 = Allocate(itfPanelTypeWork_t);
  _ctor(v5, 0);
  v3->pwork = v5;
  return v3;
}

// 0x1c5e4e0
void itfPnlRelease(itfpanel_t *handle) {
  itfpanel_t *p_fields;
  itfPanelTypeWork_t *pwork;

  if (handle)
  {
    pwork = handle->pwork;
    p_fields = &handle->fields;
    if (pwork)
    {
      p_fields->pwork = 0;
    }
  }
}

// 0x1c5d680
void itfPnlSetPosition(itfpanel_t *handle, s32 x0, s32 y0, s32 x1, s32 y1, u32 z) {
  s32 v16;
  s32 v17;
  s32 type;
  itfPanelTypeWork_t *v20;
  sdfIVector2_t *pvertex;
  itfPanelTypeWork_t *pwork;
  itfPanelTypeWork_t *v23;
  itfPanelTypeWork_t *v24;
  itfPanelTypeWork_t *v25;
  itfPanelTypeWork_t *v26;
  sdfIVector4_t v27;
  sdfIVector4_t v28;
  sdfIVector4_t v29;
  sdfIVector4_t v30;

  *(u64 *)&v27.z = 0;
  *(u64 *)&v27.x = &handle->pos;
  set_Item(v27, x0, 0, *(const MethodInfo **)&y1);
  *(u64 *)&v28.x = &handle->pos;
  *(u64 *)&v28.z = 1;
  set_Item(v28, y0, 0);
  *(u64 *)&v29.x = &handle->pos;
  *(u64 *)&v29.z = 2;
  set_Item(v29, x1, 0);
  *(u64 *)&v30.x = &handle->pos;
  *(u64 *)&v30.z = 3;
  set_Item(v30, y1, 0);
  type = handle->type;
  handle->z = z;
  switch (type)
  {
    case 0:
      pwork = handle->pwork;
      CreateVertexNormal(pwork, x0, y0, x1, y1);
      break;
    case 1:
      v23 = handle->pwork;
      CreateVertexMesWin(v23, x0, y0, x1, y1);
      break;
    case 2:
      v24 = handle->pwork;
      CreateVertexSelWin(v24, x0, y0, x1, y1);
      break;
    case 3:
    case 4:
      v20 = handle->pwork;
      pvertex = v20->pvertex;
      set_Item((sdfIVector2_t)pvertex, 0, x0, 0);
      set_Item((sdfIVector2_t)pvertex, 1, y0, 0);
      set_Item((sdfIVector2_t)&pvertex[1], 0, x1, 0);
      set_Item((sdfIVector2_t)&pvertex[1], 1, y0, 0);
      set_Item((sdfIVector2_t)&pvertex[2], 0, x1, 0);
      set_Item((sdfIVector2_t)&pvertex[2], 1, y1, 0);
      set_Item((sdfIVector2_t)&pvertex[3], 0, x0, 0);
      set_Item((sdfIVector2_t)&pvertex[3], 1, y1, 0);
      break;
    case 5:
      v25 = handle->pwork;
      CreateVertexLeftFade(v25, x0, y0, x1, y1);
      break;
    case 8:
      v26 = handle->pwork;
      CreateVertexFacility(v26, v16, y0, v17, y1);
      break;
    default:
      return;
  }
}

// 0x1c617e0
void itfPnlSetPositionOffset(itfpanel_t *handle, s32 x0, s32 y0, s32 x1, s32 y1, u32 z) {
  sdfIVector4_t *p_pos;
  s32 v14;
  s32 v17;
  s32 v20;
  s32 v23;
  s32 type;
  itfPanelTypeWork_t *v27;
  s32 v28;
  s32 v30;
  s32 v32;
  s32 v34;
  sdfIVector2_t *pvertex;
  itfPanelTypeWork_t *pwork;
  s32 Item;
  s32 v39;
  s32 v41;
  s32 v44;
  itfPanelTypeWork_t *v45;
  s32 v46;
  s32 v48;
  s32 v50;
  s32 v53;
  itfPanelTypeWork_t *v54;
  s32 v55;
  s32 v57;
  s32 v59;
  s32 v62;
  itfPanelTypeWork_t *v63;
  s32 v64;
  s32 v66;
  s32 v68;
  s32 v71;
  itfPanelTypeWork_t *v72;
  s32 v74;
  s32 v77;
  s32 v78;
  s32 v80;
  sdfIVector4_t v81;
  sdfIVector4_t v82;
  sdfIVector4_t v83;
  sdfIVector4_t v84;
  sdfIVector4_t v85;
  sdfIVector4_t v86;
  sdfIVector4_t v87;
  sdfIVector4_t v88;
  sdfIVector4_t v89;
  sdfIVector4_t v90;
  sdfIVector4_t v91;
  sdfIVector4_t v92;
  sdfIVector4_t v93;
  sdfIVector4_t v94;
  sdfIVector4_t v95;
  sdfIVector4_t v96;
  sdfIVector4_t v97;
  sdfIVector4_t v98;
  sdfIVector4_t v99;
  sdfIVector4_t v100;
  sdfIVector4_t v101;
  sdfIVector4_t v102;
  sdfIVector4_t v103;
  sdfIVector4_t v104;
  sdfIVector4_t v105;
  sdfIVector4_t v106;
  sdfIVector4_t v107;
  sdfIVector4_t v108;
  sdfIVector4_t v109;
  sdfIVector4_t v110;
  sdfIVector4_t v111;
  sdfIVector4_t v112;

  p_pos = &handle->pos;
  *(u64 *)&v81.z = 0;
  *(u64 *)&v81.x = &handle->pos;
  v14 = get_Item(v81, 0, *(const MethodInfo **)&x1) + x0;
  *(u64 *)&v82.x = &handle->pos;
  *(u64 *)&v82.z = 0;
  set_Item(v82, v14, 0);
  *(u64 *)&v83.x = &handle->pos;
  *(u64 *)&v83.z = 1;
  v17 = get_Item(v83, 0) + y0;
  *(u64 *)&v84.x = &handle->pos;
  *(u64 *)&v84.z = 1;
  set_Item(v84, v17, 0);
  *(u64 *)&v85.x = &handle->pos;
  *(u64 *)&v85.z = 2;
  v20 = get_Item(v85, 0) + x1;
  *(u64 *)&v86.x = &handle->pos;
  *(u64 *)&v86.z = 2;
  set_Item(v86, v20, 0);
  *(u64 *)&v87.x = &handle->pos;
  *(u64 *)&v87.z = 3;
  v23 = get_Item(v87, 0) + y1;
  *(u64 *)&v88.x = &handle->pos;
  *(u64 *)&v88.z = 3;
  set_Item(v88, v23, 0);
  type = handle->type;
  handle->z += z;
  switch (type)
  {
    case 0:
      pwork = handle->pwork;
      *(u64 *)&v93.x = p_pos;
      *(u64 *)&v93.z = 0;
      Item = get_Item(v93, 0);
      *(u64 *)&v94.x = p_pos;
      *(u64 *)&v94.z = 1;
      v39 = get_Item(v94, 0);
      *(u64 *)&v95.x = p_pos;
      *(u64 *)&v95.z = 2;
      v41 = get_Item(v95, 0);
      *(u64 *)&v96.x = p_pos;
      *(u64 *)&v96.z = 3;
      v44 = get_Item(v96, 0);
      CreateVertexNormal(pwork, Item, v39, v41, v44);
      break;
    case 1:
      v45 = handle->pwork;
      *(u64 *)&v97.x = p_pos;
      *(u64 *)&v97.z = 0;
      v46 = get_Item(v97, 0);
      *(u64 *)&v98.x = p_pos;
      *(u64 *)&v98.z = 1;
      v48 = get_Item(v98, 0);
      *(u64 *)&v99.x = p_pos;
      *(u64 *)&v99.z = 2;
      v50 = get_Item(v99, 0);
      *(u64 *)&v100.x = p_pos;
      *(u64 *)&v100.z = 3;
      v53 = get_Item(v100, 0);
      CreateVertexMesWin(v45, v46, v48, v50, v53);
      break;
    case 2:
      v54 = handle->pwork;
      *(u64 *)&v101.x = p_pos;
      *(u64 *)&v101.z = 0;
      v55 = get_Item(v101, 0);
      *(u64 *)&v102.x = p_pos;
      *(u64 *)&v102.z = 1;
      v57 = get_Item(v102, 0);
      *(u64 *)&v103.x = p_pos;
      *(u64 *)&v103.z = 2;
      v59 = get_Item(v103, 0);
      *(u64 *)&v104.x = p_pos;
      *(u64 *)&v104.z = 3;
      v62 = get_Item(v104, 0);
      CreateVertexSelWin(v54, v55, v57, v59, v62);
      break;
    case 3:
    case 4:
      v27 = handle->pwork;
      *(u64 *)&v89.x = &handle->pos;
      *(u64 *)&v89.z = 0;
      v28 = get_Item(v89, 0);
      *(u64 *)&v90.x = p_pos;
      *(u64 *)&v90.z = 1;
      v30 = get_Item(v90, 0);
      *(u64 *)&v91.x = p_pos;
      *(u64 *)&v91.z = 2;
      v32 = get_Item(v91, 0);
      *(u64 *)&v92.x = p_pos;
      *(u64 *)&v92.z = 3;
      v34 = get_Item(v92, 0);
      pvertex = v27->pvertex;
      set_Item((sdfIVector2_t)pvertex, 0, v28, 0);
      set_Item((sdfIVector2_t)pvertex, 1, v30, 0);
      set_Item((sdfIVector2_t)&pvertex[1], 0, v32, 0);
      set_Item((sdfIVector2_t)&pvertex[1], 1, v30, 0);
      set_Item((sdfIVector2_t)&pvertex[2], 0, v32, 0);
      set_Item((sdfIVector2_t)&pvertex[2], 1, v34, 0);
      set_Item((sdfIVector2_t)&pvertex[3], 0, v28, 0);
      set_Item((sdfIVector2_t)&pvertex[3], 1, v34, 0);
      break;
    case 5:
      v63 = handle->pwork;
      *(u64 *)&v105.x = p_pos;
      *(u64 *)&v105.z = 0;
      v64 = get_Item(v105, 0);
      *(u64 *)&v106.x = p_pos;
      *(u64 *)&v106.z = 1;
      v66 = get_Item(v106, 0);
      *(u64 *)&v107.x = p_pos;
      *(u64 *)&v107.z = 2;
      v68 = get_Item(v107, 0);
      *(u64 *)&v108.x = p_pos;
      *(u64 *)&v108.z = 3;
      v71 = get_Item(v108, 0);
      CreateVertexLeftFade(v63, v64, v66, v68, v71);
      break;
    case 8:
      v72 = handle->pwork;
      *(u64 *)&v109.x = p_pos;
      *(u64 *)&v109.z = 0;
      get_Item(v109, 0);
      *(u64 *)&v110.x = p_pos;
      *(u64 *)&v110.z = 1;
      v74 = get_Item(v110, 0);
      *(u64 *)&v111.x = p_pos;
      *(u64 *)&v111.z = 2;
      get_Item(v111, 0);
      *(u64 *)&v112.x = p_pos;
      *(u64 *)&v112.z = 3;
      v80 = get_Item(v112, 0);
      CreateVertexFacility(v72, v77, v74, v78, v80);
      break;
    default:
      return;
  }
}

// 0x1c5d9b0
void itfPnlSetColor(itfpanel_t *handle, s32 r, s32 g, s32 b, s32 a) {
  itfPanelTypeWork_t *pwork;
  sdfIVector4_t *pcolor;
  s64 m_Items;
  itfPanelTypeWork_t *v22;
  itfPanelTypeWork_t *v23;
  itfPanelTypeWork_t *v24;
  itfPanelTypeWork_t *v25;
  s32 v30;
  itfPanelTypeWork_t *v31;
  sdfIVector4_t *v32;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;
  sdfIVector4_t v42;
  sdfIVector4_t v43;
  sdfIVector4_t v44;
  sdfIVector4_t v45;
  sdfIVector4_t v46;
  sdfIVector4_t v47;
  sdfIVector4_t v48;
  sdfIVector4_t v49;
  sdfIVector4_t v50;
  sdfIVector4_t v51;
  sdfIVector4_t v52;
  sdfIVector4_t v53;
  sdfIVector4_t v54;
  sdfIVector4_t v55;
  sdfIVector4_t v56;
  sdfIVector4_t v57;

  *(u64 *)&v39.z = 0;
  *(u64 *)&v39.x = &handle->color;
  set_Item(v39, r, 0, *(const MethodInfo **)&a);
  *(u64 *)&v40.x = &handle->color;
  *(u64 *)&v40.z = 1;
  set_Item(v40, g, 0);
  *(u64 *)&v41.x = &handle->color;
  *(u64 *)&v41.z = 2;
  set_Item(v41, b, 0);
  *(u64 *)&v42.x = &handle->color;
  *(u64 *)&v42.z = 3;
  set_Item(v42, a, 0);
  switch (handle->type)
  {
    case 0:
    case 5:
      pwork = handle->pwork;
      pcolor = pwork->pcolor;
      *(u64 *)&v43.z = 0;
      *(u64 *)&v43.x = pcolor;
      set_Item(v43, r, 0);
      *(u64 *)&v44.x = pcolor;
      *(u64 *)&v44.z = 1;
      set_Item(v44, g, 0);
      *(u64 *)&v45.x = pcolor;
      *(u64 *)&v45.z = 2;
      set_Item(v45, b, 0);
      *(u64 *)&v46.x = pcolor;
      *(u64 *)&v46.z = 3;
      set_Item(v46, 0, 0);
      m_Items = &pcolor[1];
      goto LABEL_19;
    case 1:
      v22 = handle->pwork;
      CreateColorMesWin(v22, r, g, b, a);
      return;
    case 2:
      v23 = handle->pwork;
      CreateColorSelWin(v23, r, g, b, a);
      return;
    case 3:
      v24 = handle->pwork;
      CreateColorPlain(v24, r, g, b, a);
      return;
    case 4:
      v25 = handle->pwork;
      m_Items = v25->pcolor;
LABEL_19:
      *(u64 *)&v47.x = m_Items;
      *(u64 *)&v47.z = 0;
      set_Item(v47, r, 0);
      *(u64 *)&v48.x = m_Items;
      *(u64 *)&v48.z = 1;
      set_Item(v48, g, 0);
      *(u64 *)&v49.x = m_Items;
      *(u64 *)&v49.z = 2;
      set_Item(v49, b, 0);
      *(u64 *)&v50.x = m_Items;
      *(u64 *)&v50.z = 3;
      v30 = a;
      goto LABEL_20;
    case 8:
      v31 = handle->pwork;
      v32 = v31->pcolor;
      *(u64 *)&v51.z = 0;
      *(u64 *)&v51.x = v32;
      set_Item(v51, 115, 0);
      *(u64 *)&v52.x = v32;
      *(u64 *)&v52.z = 1;
      set_Item(v52, 135, 0);
      *(u64 *)&v53.x = v32;
      *(u64 *)&v53.z = 2;
      set_Item(v53, 255, 0);
      *(u64 *)&v54.x = v32;
      *(u64 *)&v54.z = 3;
      set_Item(v54, 0, 0);
      *(u64 *)&v55.z = 0;
      *(u64 *)&v55.x = &v32[1];
      set_Item(v55, 115, 0);
      *(u64 *)&v56.x = &v32[1];
      *(u64 *)&v56.z = 1;
      set_Item(v56, 135, 0);
      *(u64 *)&v57.x = &v32[1];
      *(u64 *)&v57.z = 2;
      set_Item(v57, 255, 0);
      *(u64 *)&v50.x = &v32[1];
      *(u64 *)&v50.z = 3;
      v30 = 0;
LABEL_20:
      set_Item(v50, v30, 0);
      break;
    default:
      return;
  }
}

// 0x1c760f0
void itfPnlDraw(itfpanel_t *handle, sdfGrOt_t *pot) {
  ;
}

// 0x1c76100
void itfPnlDrawTag(itfpanel_t *handle, sdfDrawTag_t *pdrawtag) {
  g_pdrawDelegate v6;

  v6 = g_pdraw[handle->type];
  (v6->invoke_impl)(v6->method_code, handle, pdrawtag, v6->method);
}

// 0x1c76190
void *itfStationListGetBaseObject(void) {
  return slwork->slBaseGameObject;
}

// 0x1c763f0
void itfInitStationListManager(void *s_work) {
  void *p_slwork;

  p_slwork = &slwork;
  p_slwork = s_work;
  SetActiveGo(slwork, 0, 0);
}

// 0x1c764b0
void itfSetStationListText(void) {
  char *v4;
  char *LocalizeText;
  void *v6;
  char *v7;
  s64 v8;
  s32 v9;
  char *v10;
  Il2CppObject *v11;
  char *v12;
  Il2CppObject *v13;
  bool v15;
  Il2CppObject *Item;
  char *v20;

  v4 = strSystem[5];
  LocalizeText = GetLocalizeText(v4, 1);
  SetTitleText(slwork, LocalizeText, 0);
  v6 = slwork;
  v7 = GetLocalizeText(strSystem[1], 1);
  SetIkisakiText(v6, v7, 0);
  v8 = 0;
  v9 = 0;
  do
  {
    while (1)
    {
      v15 = evtBitCheck(arrStFlag[v8]);
      if (!v15)
        break;
      Item = _get_Item(slwork->slItems, v9);
      v20 = strStation[v8];
      v10 = GetLocalizeText(v20, 1);
      SetStationNameText(Item, v10, 0);
      v11 = _get_Item(slwork->slItems, v9);
      v12 = GetLocalizeText(strSystem[3], 1);
      SetYenText(v11, v12, 0);
      v13 = _get_Item(slwork->slItems, v9++);
      LODWORD(v13[1].klass) = v8++;
      if (v8 == 7)
        return;
    }
    LODWORD(_get_Item(slwork->slItems, v9)[1].klass) = -1;
    ++v8;
  }
  while (v8 != 7);
}

// 0x1c76300
void itfSetStationListActive(bool sw) {
  SetActiveGo(slwork, sw, 0);
}

// 0x1c767a0
void itfCtrlStationList(f32 alpha) {
  isStationListDisp = 1;
  SetActiveGo(slwork, 1, 0);
  SetCursor(slwork, uniMenuCursor, 0);
  SetAlpha(slwork, alpha, 0);
}

// 0x1c769e0
void itfSetStationListItemState(s32 index, SL_ItemState state) {
  SetItemState(slwork, index, state, 0);
}

// 0x1c76a60
void itfSetStationListItemFare(s32 index, char *fare) {
  s32 v5;
  void *slItems;

  v5 = 0;
  while (1)
  {
    slItems = slwork->slItems;
    if (v5 >= slItems->_size)
      break;
    slItems = slwork->slItems;
    if (LODWORD(_get_Item(slItems, v5)[1].klass) == index)
    {
      SetItemFare(slwork, v5, fare, 0);
      return;
    }
    ++v5;
  }
}

// 0x1c76970
void itfSetAlpha(f32 alpha) {
  SetAlpha(slwork, alpha, 0);
}

// 0x1c76b90
void itfChangeBitIconNew(s32 id) {
  s32 v3;
  s64 v5;

  v3 = id + 10032;
  if (!evtBitCheck(id + 10032))
  {
    if (v3)
    {
      if ((u32)(id + 7414) >= 0xFFFFFFC6)
        evtBitKityouItemAdd(v3);
      v5 = (s64)GBWK->EventBit + 4 * (v3 / 32);
      *(u32 *)(v5 + 32) |= 1 << v3;
    }
  }
}

// 0x1c76c60
void itfChangeIconNewAll(void) {
  s32 i;
  Il2CppObject *Item;
  Il2CppObject *v3;
  bool v4;

  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(arrStFlag->max_length))
      break;
    Item = _get_Item(slwork->slItems, i);
    v3 = _get_Item(slwork->slItems, i);
    v4 = evtBitCheck(HIDWORD(v3[1].klass));
    SetActiveIconNew(Item, !v4, 0);
  }
}

// 0x1c76d80
void itfChangeMokutekichi(s32 _id) {
  s32 i;
  Il2CppObject *Item;
  bool v7;

  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(arrStFlag->max_length))
      break;
    if (LODWORD(_get_Item(slwork->slItems, i)[1].klass) != id)
    {
      v7 = 0;
      goto LABEL_4;
    }
    v7 = cfgGetConfigGAME(12, 0) == 0;
LABEL_4:
    Item = _get_Item(slwork->slItems, i);
    SetActiveMokutekichi(Item, v7, 0);
  }
}

// 0x1c76f10
void itfSetStationListMenuBarFlag(s32 num, s32 flagID) {
  HIDWORD(_get_Item(slwork->slItems, num)[1].klass) = flagID;
}

// 0x1c76fb0
static void mapMenuDrawMagWindow(f32 a_rate, u8 a_alphaRate) {
  dds3GetProcessData(mapMenu_g_mainPID);
  NewSpecific(byte, 8u);
}

// 0x1c770a0
static s32 mapMenuDecideFunc(void) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v5;
  s64 naturalAligment;
  s32 SelectID;
  s32 *p_QuestDevilNumber;
  s32 StockDevilID;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v13;
  s32 devilid;
  s32 MagCost;
  sdatPlayerUnitWork_t *v17;
  s32 v18;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  v5 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagMAP_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagMAP_MENU_WORK;
  }
  SelectID = itfMenuGetSelectID(ProcessData[3]);
  if (SelectID >= 0x10000)
  {
    p_QuestDevilNumber = (s32 *)v5 + 9;
LABEL_28:
    *p_QuestDevilNumber = SelectID;
    return 0;
  }
  StockDevilID = datGetStockDevilID(SelectID);
  *((u32 *)v5 + 9) = StockDevilID;
  player = GBWK->player;
  para = player->para;
  v13 = player->stock_id[SelectID];
  devilid = v13->devilid;
  MagCost = sBtlGetMagCost(para, v13, devilid);
  *((u32 *)v5 + 11) = v13->uniq_code;
  v17 = GBWK->player;
  v18 = v17->mag - MagCost;
  v17->mag = v18;
  if (Story11Select)
  {
    Story11Number = SelectID;
  }
  if (QuestDevilSelect)
  {
    p_QuestDevilNumber = &QuestDevilNumber;
    goto LABEL_28;
  }
  return 0;
}

// 0x1c77300
static char *GetMenuHelpID(s32 mapMenuID) {
  s32 *p_data;
  Il2CppObject *v5;
  s32 data;
  s32 v7;
  s32 v8;

  if (!evtBitCheck(2100))
  {
    if (mapMenuID == 0x200000)
      return "CMP_HELP_L0026";
    if (mapMenuID == 917504)
    {
      if (!evtBitCheck(10018))
        return "CMP_STATUS_L0019";
    }
    else if (mapMenuID == 196608 && !evtBitCheck(10017))
    {
      return "CMP_STATUS_L0019";
    }
    data = mapMenuID >> 16;
    p_data = &data;
    goto LABEL_20;
  }
  if (mapMenuID <= 0x20000)
  {
    if (mapMenuID == 0x10000)
    {
      if (evtBitCheck(679))
      {
        v8 = mapMenuID >> 16;
        p_data = &v8;
        goto LABEL_20;
      }
    }
    else if (mapMenuID != 0x20000)
    {
LABEL_16:
      v7 = mapMenuID >> 16;
      p_data = &v7;
LABEL_20:
      v5 = Box(s32, p_data);
      return Format("MAPMENUHELP_L{0:D4}", v5, 0);
    }
  }
  else if (mapMenuID != 196608 && mapMenuID != 917504)
  {
    if (mapMenuID == 0x200000)
      return "CMP_HELP_L0026";
    goto LABEL_16;
  }
  return "CMP_STATUS_L0019";
}

// 0x1c77490
static void mapMenuDrawFuncMenu(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  char *MenuHelpID;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagMAP_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagMAP_MENU_WORK;
  if (itfMenuGetSelectID(ProcessData[3]) == a_id)
  {
    MenuHelpID = GetMenuHelpID(a_id);
    ButtonLineHelpTextSet(MenuHelpID, 0, 1, 0xA09DC380, 1);
  }
}

// 0x1c77630
static void mapMenuDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v10;
  s64 naturalAligment;
  dds3ProcessID_t *v12;
  Il2CppObject *v13;
  Il2CppObject *v15;
  s32 SelectID;
  s32 v18;
  dds3ProcessID_t *v20;
  char **v25;
  s32 StockDevilID;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v29;
  s64 v31;
  sdatUnitWork_t *v32;
  s32 devilid;
  bool v34;
  void *hukidashiIcon;
  sdatUnitWork_t *v40;
  s32 v41;
  bool v42;
  _BOOL4 v43;
  s32 v44;
  u32 v45;
  s32 v46;
  s32 v47;
  char v48;
  s64 v50;
  bool v51;
  void *v52;
  void *v53;
  void *Instance;
  void *DvlFaceMiniSprite;
  s32 v56;
  sdatUnitWork_t *v57;
  s32 listDrwNo;
  s32 listTop;
  s32 openType;
  s32 v63;
  bool v64;
  u32 v68;
  s32 v69;
  bool v71;
  MenuCsrUnity *p_sklCsr;
  bool v78;
  void *v83;
  u32 v85;
  void *v86;
  s32 *p_skill2;
  s32 v90;
  char *v91;
  MenuCsrUnity *v92;
  s32 v93;
  s32 skill2;
  s32 skill1;

  skill1 = 0;
  skill2 = 0;
  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  v10 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagMAP_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagMAP_MENU_WORK;
  }
  v12 = ProcessData + 3;
  v13 = dds3GetProcessData(ProcessData + 3);
  v15 = v13;
  SelectID = itfMenuGetSelectID(v12);
  v18 = a_id - *((u32 *)v15[9].monitor + SBYTE4(v15[5].monitor) + 8);
  NewSpecific(byte, 8u);
  if (v18 >= SLODWORD(devil_win->panel->max_length))
    return;
  v20 = v12;
  v93 = SelectID;
  if (!itfMenuChkMenuTop(v20, a_id))
    goto LABEL_25;
  if (*((u8 *)v10 + 32) == 5)
    goto LABEL_25;
  if (QuestDevilExtra)
  {
    v25 = &"QUEST_INFO_L0024";
LABEL_24:
    ButtonLineHelpTextSet(*v25, 0, 1, 0xA09DC380, 1);
    goto LABEL_25;
  }
  else
  {
    if (Story11Select)
      v25 = &"MAPMENUHELP_L0020";
    else
      v25 = &"MAPMENUHELP_L0006";
    goto LABEL_24;
  }
  goto LABEL_24;
LABEL_25:
  StockDevilID = datGetStockDevilID(a_id);
  player = GBWK->player;
  para = player->para;
  v29 = player->stock_id[a_id];
  sBtlGetMagCost(para, v29, StockDevilID);
  v31 = a_id;
  v32 = GBWK->player->stock_id[v31];
  if (v32->DevilReportStok->_size <= 0)
  {
    goto LABEL_36;
  }
  devilid = v32->devilid;
  v34 = DlcDevilSelCheck(devilid);
  if (!v34)
    goto LABEL_35;
  goto LABEL_9000;
  if (!v51)
  {
LABEL_35:
LABEL_36:
    hukidashiIcon = devil_win->panel[v18]->hukidashiIcon;
    fldSetupObject(hukidashiIcon, 0);
    goto LABEL_39;
  }
LABEL_9000:
  v52 = devil_win->panel[v18]->hukidashiIcon;
  fldSetupObject(v52, 1);
LABEL_39:
  if (datGetStockDevilNums(0) > a_id)
  {
    v40 = GBWK->player->stock_id[v31];
    v41 = v40->devilid;
    if (GBWK->mapSummonID == v41)
    {
      v42 = GBWK->mapSummonUNIQ == v40->uniq_code;
      v43 = v42;
      if (v42)
        v44 = 0;
      else
        v44 = -1;
    }
    else
    {
      v43 = 0;
      v44 = -1;
    }
    v45 = v40->badstatus & 0x20000;
    if (v45)
      v46 = 1;
    else
      v46 = v44;
    v47 = v43 | (v45 >> 17);
    v48 = DlcDevilSelCheck(v41) & v47;
    goto LABEL_60;
  }
  v46 = -1;
  v48 = 0;
  v41 = -1;
LABEL_60:
  v50 = v31;
  v53 = devil_win->icon[v18];
  Instance = get_Instance(0);
  DvlFaceMiniSprite = GetDvlFaceMiniSprite(Instance, v41, 0);
  set_sprite(v53, DvlFaceMiniSprite, 0);
  SetSituation(devil_win->panel[v18], v48 & 1, v46, 0);
  if (v93 != a_id)
    return;
  v56 = datGetStockDevilID(a_id);
  v57 = GBWK->player->stock_id[v50];
  if (!sklCsr)
  {
    listTop = -1;
    listDrwNo = -1;
    goto LABEL_80;
  }
  listTop = sklCsr->listTop;
  listDrwNo = sklCsr->listDrwNo;
LABEL_80:
  openType = devil_info2->openType;
  if (openType != 1)
  {
    openType = devil_info2->openType;
    v69 = v57->devilid;
    if (openType == 2)
    {
      v71 = DlcDevilSelCheck(v69);
      DrawOnOff(devil_info2, v71, 0);
      SetBtlSkill(devil_info2, GBWK->player->stock_id[v50], listDrwNo, 0);
      SetBtlSkillCsr(devil_info2, listDrwNo, 0);
      if (*((u8 *)v10 + 32) == 5)
        goto LABEL_119;
    }
    else
    {
      v78 = DlcDevilSelCheck(v69);
      DrawOnOff(devil_info2, v78, 0);
      v83 = devil_info2;
      SetOmoideSkill(v83, GBWK->player->stock_id[v50], listDrwNo, listTop, 2, 0);
      SetOmoideSkillCsr(devil_info2, listDrwNo, 0);
      SetOmoideScrollBar(devil_info2, GBWK->player->stock_id[v50], listTop, 2, 0);
      if (*((u8 *)v10 + 32) == 5)
        goto LABEL_119;
    }
    goto LABEL_107;
  }
  v63 = v57->devilid;
  v64 = DlcDevilSelCheck(v63);
  if (!v64)
  {
    DrawOnOff(devil_info2, 0, 0);
    if (*((u8 *)v10 + 32) == 5)
      goto LABEL_119;
LABEL_107:
    SetSkillCursor(devil_info2, 0, 0, 0);
    SetSkillCursor(devil_info2, 1, 0, 0);
    p_sklCsr = &sklCsr;
    p_sklCsr = 0;
    return;
  }
  DrawOnOff(devil_info2, 1, 0);
  SetDevilStatus(devil_info2, v57, 0, 0, 0, 0, 0);
  if (*((u8 *)v10 + 32) != 5)
    goto LABEL_107;
LABEL_119:
  if (v68)
  {
    v86 = devil_info2;
    if (v86->openType == 1)
    {
LABEL_121:
      if (!v85)
      {
        v86 = devil_info2;
      }
      SetSkillCursor(v86, 0, devilSkillSel == 0, 0);
      SetSkillCursor(devil_info2, 1, devilSkillSel != 0, 0);
      skill1 = 0;
      skill2 = 0;
      mskGetNo(v56, &skill1, &skill2);
      if (devilSkillSel)
        p_skill2 = &skill2;
      else
        p_skill2 = &skill1;
      v90 = *p_skill2;
      v91 = cmpMskHelp(v90, 1);
      ButtonLineHelpTextSet(v91, 0, 1, 0xA09DC380, 1);
      return;
    }
  }
  else
  {
    v86 = devil_info2;
    if (v86->openType == 1)
      goto LABEL_121;
  }
  v92 = sklCsr;
  if (v92)
  {
    v92 = sklCsr;
    if (v92->nowMax >= 1)
    {
      v92 = sklCsr;
      (v92->klass->vtable._10_CsrUpdate.methodPtr)(v92, v92, v92->klass->vtable._10_CsrUpdate.method);
    }
  }
}

// 0x1c78370
static void SummonMenuSelDrawPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag) {
  Il2CppObject *ProcessData;
  s64 naturalAligment;
  s64 v16;
  s32 v17;
  void *panel;
  void *gameObject;
  s32 v21;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  if (ProcessData->klass->_2.naturalAligment < (u32)naturalAligment || ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] != tagMAP_MENU_WORK)
  {
LABEL_34:
  }
LABEL_11:
  ProcessData = dds3GetProcessData(&ProcessData[1].monitor);
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)v16 || ProcessData->klass->_2.typeHierarchy[v16 - 1] != Menu_t)
    {
      goto LABEL_34;
    }
  }
  v17 = no - *((u32 *)ProcessData[9].monitor + SBYTE4(ProcessData[5].monitor) + 8);
  panel = devil_win->panel;
  if (v17 >= SLODWORD(panel->max_length))
    return;
  panel = devil_win->panel;
  gameObject = get_gameObject(panel[v17], 0);
  fldSetupObject(gameObject, 1);
  if (v17 < SLODWORD(devil_win->setText->max_length))
  {
    if (color == -1600273536)
    {
      v21 = 1;
    }
    else if (color == 1296780109 || color == 1349079155)
    {
      v21 = 2;
    }
    else
    {
      v21 = 0;
    }
    SetText(devil_win->panel[v17], str, v21, tag, 0);
  }
  SetCursor(devil_win->panel[v17], (attr & 2) != 0, 0);
}

// 0x1c78680
static void mapMenuSetMenuImage(dds3ProcessID_t *PID) {
  dds3GetProcessData(mapMenu_g_mainPID);
}

// 0x1c78740
bool itfQuickSaveExeCheck(void) {
  return dds3AdminiGetActiveSequence() == 7
      || dds3AdminiGetActiveSequence() == 35;
}

// 0x1c78780
static dds3ProcessID_t *mapMenuCreateMenuPID(void) {
  dds3ProcessID_t *v1;
  itfMoverFunc_t v6;
  char *MenuName;
  char *v11;
  itfMenuDrawFunc_t v12;
  itfMenuTextFunc_t v13;
  char *v15;
  itfMenuFunc_t v16;
  char *v18;
  itfMenuDrawFunc_t v19;
  itfMenuTextFunc_t v20;
  char *v22;
  itfMenuFunc_t v23;
  char *v25;
  itfMenuDrawFunc_t v26;
  itfMenuTextFunc_t v27;
  char *SkillName;
  itfMenuFunc_t v30;
  s32 v31;
  s32 v32;
  char *v35;
  itfMenuFunc_t v36;
  char *v38;
  itfMenuDrawFunc_t v40;
  itfMenuTextFunc_t v41;
  dds3ProcessID_t *v43;
  s32 v44;
  char *v46;
  itfMenuDrawFunc_t v48;
  itfMenuTextFunc_t v49;
  char *v51;
  itfMenuFunc_t v52;
  char *v54;
  char *v56;
  itfMenuFunc_t v57;
  char *v59;
  itfMenuDrawFunc_t v61;
  itfMenuTextFunc_t v62;
  char *v64;
  itfMenuFunc_t v65;
  bool v66;
  char *v68;
  itfMenuDrawFunc_t v69;
  itfMenuTextFunc_t v70;
  s32 v73;
  s32 v74;
  itfMenuDrawFunc_t v75;
  itfMenuTextFunc_t v76;
  itfMenuFunc_t v78;
  s32 StockDevilNums;
  dds3ProcessID_t *PID;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  StockDevilNums = datGetStockDevilNums(0);
  PID = itfMenuProcessStart();
  mapMenuMode = 0;
  if (Story11Select)
    goto LABEL_118;
  if (QuestDevilSelect)
  {
LABEL_118:
    mapMenuMode = 1;
  }
  v6 = Allocate(itfMoverFunc_t);
  _ctor(v6, 0, Method_Project_itf_mapMenuMoverFunc__, 0);
  itfMoverSetMenu(PID, v6);
  ButtonLineHelpDispSet(1);
  MenuName = mapIfGetMenuName(0, 0);
  v11 = mapIfGetMenuName(0, 1);
  itfMenuSetMenu(PID, 0x10000, -1, MenuName, 0, v11);
  v12 = Allocate(itfMenuDrawFunc_t);
  _ctor(v12, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v13 = Allocate(itfMenuTextFunc_t);
  _ctor(v13, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(PID, 0x10000, v12, v13);
  v15 = mapIfGetMenuName(1, 0);
  v16 = Allocate(itfMenuFunc_t);
  _ctor(v16, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  v18 = mapIfGetMenuName(1, 1);
  itfMenuSetMenu(PID, 0x20000, -1, v15, v16, v18);
  v19 = Allocate(itfMenuDrawFunc_t);
  _ctor(v19, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v20 = Allocate(itfMenuTextFunc_t);
  _ctor(v20, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(PID, 0x20000, v19, v20);
  v22 = mapIfGetMenuName(2, 0);
  v23 = Allocate(itfMenuFunc_t);
  _ctor(v23, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  v25 = mapIfGetMenuName(2, 1);
  itfMenuSetMenu(PID, 196608, -1, v22, v23, v25);
  v26 = Allocate(itfMenuDrawFunc_t);
  _ctor(v26, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v27 = Allocate(itfMenuTextFunc_t);
  _ctor(v27, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(PID, 196608, v26, v27);
  if (evtBitCheck(2274))
  {
    SkillName = mapIfGetSkillName(2, 0);
    v30 = Allocate(itfMenuFunc_t);
    _ctor(v30, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
    v31 = 2;
  }
  else if (evtBitCheck(2275))
  {
    SkillName = mapIfGetSkillName(3, 0);
    v30 = Allocate(itfMenuFunc_t);
    _ctor(v30, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
    v31 = 3;
  }
  else
  {
    if (evtBitCheck(2291))
    {
      v32 = 19;
    }
    else
    {
      if (!evtBitCheck(2292))
      {
LABEL_46:
        if (!fldGb->nakamaMode)
          goto LABEL_65;
        v35 = mapIfGetMenuName(30, 0);
        v36 = Allocate(itfMenuFunc_t);
        _ctor(v36, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
        v38 = mapIfGetMenuName(30, 1);
        itfMenuSetMenu(PID, 0x100000, -1, v35, v36, v38);
        v40 = Allocate(itfMenuDrawFunc_t);
        _ctor(v40, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
        v41 = Allocate(itfMenuTextFunc_t);
        _ctor(v41, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
        v43 = PID;
        v44 = 0x100000;
        goto LABEL_71;
      }
      v32 = 20;
    }
    SkillName = mapIfGetSkillName(v32, 0);
    v30 = Allocate(itfMenuFunc_t);
    _ctor(v30, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
    v31 = v32;
  }
  v46 = mapIfGetSkillName(v31, 1);
  itfMenuSetMenu(PID, 0x40000, -1, SkillName, v30, v46);
  v48 = Allocate(itfMenuDrawFunc_t);
  _ctor(v48, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v49 = Allocate(itfMenuTextFunc_t);
  _ctor(v49, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(PID, 0x40000, v48, v49);
  goto LABEL_46;
LABEL_65:
  v51 = mapIfGetMenuName(28, 0);
  v52 = Allocate(itfMenuFunc_t);
  _ctor(v52, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  v54 = mapIfGetMenuName(28, 1);
  itfMenuSetMenu(PID, 917504, -1, v51, v52, v54);
  v40 = Allocate(itfMenuDrawFunc_t);
  _ctor(v40, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v41 = Allocate(itfMenuTextFunc_t);
  _ctor(v41, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  v43 = PID;
  v44 = 917504;
LABEL_71:
  itfMenuSetDrawFunc(v43, v44, v40, v41);
  v56 = mapIfGetMenuName(29, 0);
  v57 = Allocate(itfMenuFunc_t);
  _ctor(v57, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  v59 = mapIfGetMenuName(29, 1);
  itfMenuSetMenu(PID, 983040, -1, v56, v57, v59);
  v61 = Allocate(itfMenuDrawFunc_t);
  _ctor(v61, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v62 = Allocate(itfMenuTextFunc_t);
  _ctor(v62, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(PID, 983040, v61, v62);
  v64 = mapIfGetMenuName(31, 0);
  v65 = Allocate(itfMenuFunc_t);
  _ctor(v65, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  v66 = dds3AdminiGetActiveSequence() == 7
     || dds3AdminiGetActiveSequence() == 35;
  v68 = mapIfGetMenuName(31, v66);
  itfMenuSetMenu(PID, 0x200000, -1, v64, v65, v68);
  v69 = Allocate(itfMenuDrawFunc_t);
  _ctor(v69, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v70 = Allocate(itfMenuTextFunc_t);
  _ctor(v70, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(PID, 0x200000, v69, v70);
  if (StockDevilNums)
  {
    v73 = 0;
    if (StockDevilNums <= 8)
      v74 = 8;
    else
      v74 = StockDevilNums;
    do
    {
      v78 = Allocate(itfMenuFunc_t);
      _ctor(v78, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
      itfMenuSetMenu(PID, v73, 0x10000, 0, v78, "");
      v75 = Allocate(itfMenuDrawFunc_t);
      _ctor(v75, 0, Method_Project_itf_mapMenuDrawFunc__, 0);
      v76 = Allocate(itfMenuTextFunc_t);
      _ctor(v76, 0, Method_Project_itf_SummonMenuSelDrawPanelForUnity__, 0);
      itfMenuSetDrawFunc(PID, v73++, v75, v76);
    }
    while (v74 != v73);
  }
  itfMenuSetDrawParam(PID, 8, 1);
  MenuSetDispType(PID, 0, 3);
  MenuSetDispType(PID, 1, 3);
  itfMenuSetFlag(PID, 2, 0);
  dds3GetProcessData(mapMenu_g_mainPID);
  itfMenuUpdateLink(PID);
  return PID;
}

// 0x1c79650
static dds3ProcessID_t *lmapMenuCreateMenuPID(void) {
  dds3ProcessID_t *v1;
  dds3ProcessID_t *v3;
  itfMoverFunc_t v5;
  char *MenuName;
  itfMenuFunc_t v8;
  char *v10;
  itfMenuDrawFunc_t v11;
  itfMenuTextFunc_t v12;
  char *v14;
  itfMenuFunc_t v15;
  char *v17;
  itfMenuDrawFunc_t v18;
  itfMenuTextFunc_t v19;
  char *v21;
  itfMenuFunc_t v22;
  char *v24;
  bool v25;
  itfMenuDrawFunc_t v26;
  itfMenuTextFunc_t v27;
  s32 i;
  itfMenuDrawFunc_t v31;
  itfMenuTextFunc_t v32;
  itfMenuFunc_t v34;
  s32 j;
  itfMenuDrawFunc_t v37;
  itfMenuTextFunc_t v38;
  itfMenuFunc_t v40;
  s32 StockDevilNums;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  StockDevilNums = datGetStockDevilNums(0);
  v3 = itfMenuProcessStart();
  mapMenuMode = 0;
  v5 = Allocate(itfMoverFunc_t);
  _ctor(v5, 0, Method_Project_itf_mapMenuMoverFunc__, 0);
  itfMoverSetMenu(v3, v5);
  MenuName = mapIfGetMenuName(28, 0);
  v8 = Allocate(itfMenuFunc_t);
  _ctor(v8, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  v10 = mapIfGetMenuName(28, 1);
  itfMenuSetMenu(v3, 917504, -1, MenuName, v8, v10);
  v11 = Allocate(itfMenuDrawFunc_t);
  _ctor(v11, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v12 = Allocate(itfMenuTextFunc_t);
  _ctor(v12, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(v3, 917504, v11, v12);
  v14 = mapIfGetMenuName(29, 0);
  v15 = Allocate(itfMenuFunc_t);
  _ctor(v15, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  v17 = mapIfGetMenuName(29, 1);
  itfMenuSetMenu(v3, 983040, -1, v14, v15, v17);
  v18 = Allocate(itfMenuDrawFunc_t);
  _ctor(v18, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v19 = Allocate(itfMenuTextFunc_t);
  _ctor(v19, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(v3, 983040, v18, v19);
  v21 = mapIfGetMenuName(31, 0);
  v22 = Allocate(itfMenuFunc_t);
  _ctor(v22, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
  if (dds3AdminiGetActiveSequence() != 7)
  {
    v25 = dds3AdminiGetActiveSequence() == 35;
    v24 = mapIfGetMenuName(31, v25);
    goto LABEL_22;
  }
  v24 = mapIfGetMenuName(31, 1);
LABEL_22:
  itfMenuSetMenu(v3, 0x200000, -1, v21, v22, v24);
  v26 = Allocate(itfMenuDrawFunc_t);
  _ctor(v26, 0, Method_Project_itf_mapMenuDrawFuncMenu__, 0);
  v27 = Allocate(itfMenuTextFunc_t);
  _ctor(v27, 0, Method_Project_itf_MenuDrawPanelForUnity__, 0);
  itfMenuSetDrawFunc(v3, 0x200000, v26, v27);
  if (StockDevilNums)
  {
    for (i = 0; i != 8; ++i)
    {
      v34 = Allocate(itfMenuFunc_t);
      _ctor(v34, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
      itfMenuSetMenu(v3, i, 0x10000, 0, v34, "");
      v31 = Allocate(itfMenuDrawFunc_t);
      _ctor(v31, 0, Method_Project_itf_mapMenuDrawFunc__, 0);
      v32 = Allocate(itfMenuTextFunc_t);
      _ctor(v32, 0, Method_Project_itf_NakamaSelDrawPanelForUnity__, 0);
      itfMenuSetDrawFunc(v3, i, v31, v32);
    }
    for (j = 0; j != 8; ++j)
    {
      v40 = Allocate(itfMenuFunc_t);
      _ctor(v40, 0, Method_Project_itf_mapMenuDecideFunc__, 0);
      itfMenuSetMenu(v3, j, 0x10000, 0, v40, "");
      v37 = Allocate(itfMenuDrawFunc_t);
      _ctor(v37, 0, Method_Project_itf_mapMenuDrawFunc__, 0);
      v38 = Allocate(itfMenuTextFunc_t);
      _ctor(v38, 0, Method_Project_itf_NakamaSelDrawPanelForUnity__, 0);
      itfMenuSetDrawFunc(v3, j, v37, v38);
    }
  }
  MenuSetDispType(v3, 0, 3);
  MenuSetDispType(v3, 1, 3);
  itfMenuSetFlag(v3, 2, 0);
  dds3GetProcessData(mapMenu_g_mainPID);
  itfMenuUpdateLink(v3);
  return v3;
}

// 0x1c79e60
static void mapMenuResetMenu(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s32 StockDevilNums;
  s32 v10;
  s32 v11;
  s32 v14;
  sdatUnitWork_t *v16;
  s32 devilid;
  char *v18;
  char *v20;
  s32 v28;
  s32 SelectID;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  v6 = ProcessData;
  StockDevilNums = datGetStockDevilNums(0);
  v10 = 0;
  v11 = 0;
  SelectID = itfMenuGetSelectID(PID);
  do
  {
    v14 = v10 + SLOBYTE(v6[2].monitor);
    if (v14 < StockDevilNums)
    {
      v16 = GBWK->player->stock_id[v14];
      devilid = v16->devilid;
      v18 = sdatDevilName(devilid, 0);
      v20 = sdatDevilName(v16->devilid, 1);
      itfMenuSetFont(PID, v10, v18, v20);
      itfMenuSetFlagMenu(PID, v10, 1, 1);
      itfMenuSetFlagMenu(PID, v10, 2, 1);
      itfMenuSetFlagMenu(PID, v10, 1024, 0);
      if (!Story11Select)
      {
        if (GBWK->mapSummonID != v16->devilid)
          goto LABEL_36;
        if (GBWK->mapSummonUNIQ == v16->uniq_code)
          goto LABEL_41;
      }
LABEL_36:
      if ((v16->badstatus & 0x120000) == 0)
      {
        v28 = v16->devilid;
        if (DlcDevilSelCheck(v28))
          goto LABEL_44;
        goto LABEL_9000;
        if (DlcDevilSelCheck(v28))
        {
LABEL_44:
          ++v11;
          goto LABEL_11;
        }
LABEL_9000:
      }
LABEL_41:
      itfMenuSetFlagMenu(PID, v10, 2, 0);
      goto LABEL_44;
    }
    itfMenuSetFont(PID, v10, "", "");
    itfMenuSetFlagMenu(PID, v10, 1, 0);
    itfMenuSetFlagMenu(PID, v10, 2, 0);
    if (v14 < GBWK->player->stock_max)
      goto LABEL_11;
    itfMenuSetFlagMenu(PID, v10, 1024, 1);
LABEL_11:
    ++v10;
  }
  while (v10 != 8);
  if (v11 <= SelectID)
  {
    itfMenuSetSelectID(PID, v11 - 1);
  }
}

// 0x1c7a310
static void summonMenuResetMenu(dds3ProcessID_t *PID) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  Il2CppObject *v7;
  Il2CppObject *v8;
  s32 StockDevilNums;
  s64 v12;
  s64 v13;
  dds3ProcessID_t *v14;
  s32 v15;
  s32 v16;
  bool v17;
  sdatUnitWork_t *v19;
  s32 devilid;
  char *v21;
  char *v23;
  s32 v31;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagMAP_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagMAP_MENU_WORK;
  v7 = dds3GetProcessData(ProcessData + 3);
  v8 = v7;
  StockDevilNums = datGetStockDevilNums(0);
  v12 = *((s32 *)v8[9].monitor + SBYTE4(v8[5].monitor) + 8);
  if ((s32)v12 <= 2147483639)
  {
    v13 = StockDevilNums;
    while (v12 >= v13)
    {
      itfMenuSetFont(PID, v12, "", "");
      itfMenuSetFlagMenu(PID, v12, 1, 0);
      itfMenuSetFlagMenu(PID, v12, 2, 0);
      if (v12 < GBWK->player->stock_max)
        goto LABEL_20;
      v14 = PID;
      v15 = v12;
      v16 = 1024;
      v17 = 1;
LABEL_19:
      itfMenuSetFlagMenu(v14, v15, v16, v17);
LABEL_20:
      if (++v12 >= *((u32 *)v8[9].monitor + SBYTE4(v8[5].monitor) + 8) + 8)
        return;
    }
    v19 = GBWK->player->stock_id[v12];
    devilid = v19->devilid;
    v21 = sdatDevilName(devilid, 0);
    v23 = sdatDevilName(v19->devilid, 1);
    itfMenuSetFont(PID, v12, v21, v23);
    itfMenuSetFlagMenu(PID, v12, 1, 1);
    itfMenuSetFlagMenu(PID, v12, 2, 1);
    itfMenuSetFlagMenu(PID, v12, 1024, 0);
    if (Story11Select)
      goto LABEL_46;
    if (GBWK->mapSummonID != v19->devilid)
    {
LABEL_46:
      if ((v19->badstatus & 0x120000) == 0)
      {
        v31 = v19->devilid;
        if (DlcDevilSelCheck(v31))
          goto LABEL_20;
      }
      goto LABEL_51;
    }
    if (GBWK->mapSummonUNIQ != v19->uniq_code)
      goto LABEL_46;
LABEL_51:
    v14 = PID;
    v15 = v12;
    v16 = 2;
    v17 = 0;
    goto LABEL_19;
  }
}

// 0x1c7a7f0
static void mapMenuChkEnableDecide(tagMAP_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;
  bool v15;
  dds3ProcessID_t *v16;
  dds3ProcessID_t *v19;
  u32 v20;
  bool v21;
  dds3ProcessID_t *v25;
  dds3ProcessID_t *v26;
  dds3ProcessID_t *v27;
  dds3ProcessID_t *v31;
  dds3ProcessID_t *v34;
  dds3ProcessID_t *v38;
  dds3ProcessID_t *v42;
  dds3ProcessID_t *v43;
  dds3ProcessID_t *v44;

  menuPID = wk->menuPID;
  if (fldGb->nakamaMode)
  {
    itfMenuSetFlagMenu(menuPID, 0x10000, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 0x20000, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 196608, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 327680, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 917504, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 0x200000, 2, 0);
    if (fldGb->fieldID != 12)
      return;
    if (!evtBitCheck(2275))
      return;
    v25 = wk->menuPID;
LABEL_26:
    itfMenuSetFlagMenu(v25, 0x40000, 2, 0);
    return;
  }
  itfMenuSetFlagMenu(menuPID, 327680, 2, 1);
  itfMenuSetFlagMenu(wk->menuPID, 917504, 2, 1);
  if (!datGetStockDevilNums(0))
  {
    v26 = wk->menuPID;
    itfMenuSetFlagMenu(v26, 0x10000, 2, 0);
    v27 = wk->menuPID;
    goto LABEL_34;
  }
  v15 = evtBitCheck(679);
  v16 = wk->menuPID;
  itfMenuSetFlagMenu(v16, 0x10000, 2, v15);
  v19 = wk->menuPID;
  if (GBWK->mapSummonID < 1)
  {
    if (!v20)
    v27 = v19;
LABEL_34:
    itfMenuSetFlagMenu(v27, 0x20000, 2, 0);
    v21 = 0;
    goto LABEL_35;
  }
  if (!v20)
  v21 = 1;
  itfMenuSetFlagMenu(v19, 0x20000, 2, 1);
LABEL_35:
  itfMenuSetFlagMenu(wk->menuPID, 196608, 2, v21);
  if (evtBitCheck(2100))
  {
    v31 = wk->menuPID;
    itfMenuSetFlagMenu(v31, 0x20000, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 196608, 2, 0);
    itfMenuSetFlagMenu(wk->menuPID, 917504, 2, 0);
LABEL_37:
    if (!mapCheckFuro())
      goto LABEL_52;
    goto LABEL_43;
  }
  else
  {
    goto LABEL_37;
  }
  if (!mapCheckFuro())
    goto LABEL_52;
LABEL_43:
  v34 = wk->menuPID;
  itfMenuSetFlagMenu(v34, 0x10000, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 0x20000, 2, 0);
  itfMenuSetFlagMenu(wk->menuPID, 196608, 2, 0);
  if (evtBitCheck(2274) || evtBitCheck(2275) || evtBitCheck(2291) || evtBitCheck(2292))
  {
    v38 = wk->menuPID;
    itfMenuSetFlagMenu(v38, 0x40000, 2, 0);
  }
LABEL_52:
  if (evtBitCheck(10017))
  {
    if (evtBitCheck(10018))
      goto LABEL_54;
  }
  else
  {
    v43 = wk->menuPID;
    itfMenuSetFlagMenu(v43, 196608, 2, 0);
    if (evtBitCheck(10018))
    {
LABEL_54:
      if (!IsSurprise(1))
        return;
LABEL_55:
      v42 = wk->menuPID;
      itfMenuSetFlagMenu(v42, 196608, 2, 0);
      v25 = wk->menuPID;
      goto LABEL_26;
    }
  }
  v44 = wk->menuPID;
  itfMenuSetFlagMenu(v44, 917504, 2, 0);
  if (IsSurprise(1))
    goto LABEL_55;
}

// 0x1c7ad30
static void mapMenuCallProcEnd(tagMAP_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v5;

  menuPID = wk->menuPID;
  v5 = menuPID;
  itfMenuProcessEnd(v5);
}

// 0x1c7adc0
static bool mapMenuCheckProcEnd(tagMAP_MENU_WORK *wk) {
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *id;

  menuPID = wk->menuPID;
  p_menuPID = &wk->menuPID;
  v5 = menuPID;
  id = v5;
  if (!v5)
    goto LABEL_17;
  if (dds3GetProcessStat(id) == 3)
    goto LABEL_17;
  if (dds3GetProcessStat(id))
    return 0;
LABEL_17:
  p_menuPID = 0;
  return 1;
}

// 0x1c7af10
static dds3ProcessFunc_t mapMenuProcess(dds3ProcessID_t *PID) {
  tagMAP_MENU_WORK *ProcessData;
  s64 naturalAligment;
  Il2CppObject *v8;
  s64 v9;
  dds3ProcessFunc_t v11;
  s64 v13;
  s32 StockDevilNums;
  u32 v16;
  bool v17;
  u32 v19;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *v24;
  dds3ProcessID_t *p_menuPID;
  s32 v29;
  s32 v30;
  char **v34;
  dds3ProcessID_t *v36;
  dds3ProcessID_t *v40;
  dds3ProcessID_t *v43;
  s32 SelectID;
  s32 StockDevilID;
  char **v49;
  dds3ProcessID_t *v51;
  Il2CppObject *v56;
  long f64 v57;
  s64 v59;
  s32 v60;
  dds3ProcessID_t *v62;
  dds3ProcessID_t *v66;
  s32 v67;
  s32 v68;
  bool v71;
  s32 openType;
  s32 v83;
  s32 v86;
  sdatUnitWork_t *v90;
  MenuCsrUnity *v91;
  MenuCsrUnity *p_sklCsr;
  u32 v97;
  MenuCsrUnity *klass;
  s64 v99;
  MenuCsrUnity *v100;
  s64 v101;
  MenuCsrUnity *v102;
  u32 v103;
  s32 v105;
  void *scrollBarSet;
  u32 v108;
  s32 skill2[2];
  dds3ProcessID_t *id;
  dds3ProcessID_t *v111;

  id = PID;
  *(u64 *)skill2 = 0;
  ProcessData = dds3GetProcessData(id);
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)naturalAligment || ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] != tagMAP_MENU_WORK)
    {
      v8 = ProcessData;
      goto LABEL_246;
    }
  }
  if (!Story11Select)
  {
LABEL_23:
    goto LABEL_24;
  }
  if (!Story11Cancel)
    goto LABEL_23;
  v8 = dds3GetProcessData(&ProcessData->menuPID);
  if (v8)
  {
    if (v8->klass->_2.naturalAligment >= (u32)v9 && (Menu_t *)v8->klass->_2.typeHierarchy[v9 - 1] == Menu_t)
    {
      LODWORD(v8[13].klass) |= 0x80u;
      v11 = 0;
      *(u16 *)&Story11Select = 0;
      return v11;
    }
    goto LABEL_246;
  }
LABEL_24:
  if (!QuestDevilSelect)
    goto LABEL_41;
  if (!QuestDevilCancel)
    goto LABEL_41;
  goto LABEL_33;
  if (QuestDevilCancel)
  {
LABEL_33:
    v8 = dds3GetProcessData(&ProcessData->menuPID);
    if (!v8)
      goto LABEL_41;
    if (v8->klass->_2.naturalAligment >= (u32)v13 && (Menu_t *)v8->klass->_2.typeHierarchy[v13 - 1] == Menu_t)
    {
      LODWORD(v8[13].klass) |= 0x80u;
      v11 = 0;
      *(u16 *)&QuestDevilSelect = 0;
      return v11;
    }
LABEL_246:
  }
LABEL_41:
  v11 = 0;
  switch (ProcessData->step)
  {
    case 0u:
      if ((ProcessData->flag & 0x10) == 0)
        goto LABEL_85;
      ProcessData->flag &= ~0x10u;
      StockDevilNums = datGetStockDevilNums(0);
      v16 = StockDevilNums + 7;
      ProcessData->tabpage = 0;
      if (StockDevilNums >= 0)
        v16 = StockDevilNums;
      v17 = StockDevilNums < 0 || (StockDevilNums & 0x80000007) == 0;
      v19 = v16 >> 3;
      if (!v17)
        LOBYTE(v19) = v19 + 1;
      ProcessData->tabmax = v19;
      MenuPID = mapMenuCreateMenuPID();
      ProcessData->menuPID = MenuPID;
      mapMenuResetMenu(ProcessData->menuPID);
      mapMenuChkEnableDecide(ProcessData);
      itfMenuStart(ProcessData->menuPID);
      v11 = 0;
      ProcessData->selectID = -1;
      ProcessData->step = 1;
      return v11;
    case 1u:
      p_menuPID = &ProcessData->menuPID;
      v24 = ProcessData->menuPID;
      v111 = ProcessData->menuPID;
      if (!v24)
        goto LABEL_116;
      goto LABEL_88;
      if (!v24)
      {
LABEL_116:
        ProcessData->menuPID = 0;
        v11 = 0;
        ProcessData->step = 0;
        return v11;
      }
LABEL_88:
      if (dds3GetProcessStat(v111) == 3)
        goto LABEL_116;
      if (!dds3GetProcessStat(v111))
        goto LABEL_116;
      v40 = p_menuPID;
      if ((u32)itfMenuGetSelectID(v40) >> 16)
        goto LABEL_85;
      if (mapMenuMode != 1)
        goto LABEL_85;
      v43 = p_menuPID;
      SelectID = itfMenuGetSelectID(v43);
      StockDevilID = datGetStockDevilID(SelectID);
      if (MenuOldCsr == SelectID)
        goto LABEL_137;
      if (DlcDevilSelCheck(StockDevilID))
      {
        if (!Story11Extra)
        {
          if (!QuestDevilExtra)
          {
            v49 = &"FLD03";
            goto LABEL_134;
          }
        }
        v49 = &"FLD16";
      }
      else
      {
        v49 = &"FLD04";
      }
LABEL_134:
      ButtonAliasGuideDispSet(*v49, 0, 90);
      MenuOldCsr = SelectID;
LABEL_137:
      v56 = dds3GetProcessData(&ProcessData->menuPID);
      v59 = sub_83F0(v56, Menu_t, v57);
      v60 = *(u32 *)(*(u64 *)(v59 + 152) + 4 * *(char *)(v59 + 92) + 32);
      if (v60 != ProcessData->tabpage)
      {
        ProcessData->tabpage = v60;
        v62 = ProcessData->menuPID;
        summonMenuResetMenu(v62);
        if (CHECK_REP(4101, 1))
        {
          MenuListScroll = 1;
        }
        if (CHECK_REP(4100, 1))
        {
          MenuListScroll = 1;
        }
      }
      if (CHECK_TRIG(40962, 1))
      {
        v66 = p_menuPID;
        v67 = itfMenuGetSelectID(v66);
        skill2[1] = 0;
        v68 = datGetStockDevilID(v67);
        skill2[0] = 0;
        if (!DlcDevilSelCheck(v68))
        {
          v30 = 1;
          goto LABEL_73;
        }
        if (devil_info2->openType != 1)
        {
          v90 = GBWK->player->stock_id[v67];
          v91 = Allocate(MenuCsrUnity);
          _ctor(v91, 0);
          p_sklCsr = &sklCsr;
          p_sklCsr = v91;
          (sklCsr->klass->vtable._4_CsrClear.methodPtr)(sklCsr, sklCsr->klass->vtable._4_CsrClear.method);
          if (devil_info2->openType == 3)
          {
            v97 = datOmoideSkillSetCnt(v90);
            klass = sklCsr->klass;
            v99 = v97;
            v100 = sklCsr;
            v101 = 6;
          }
          else
          {
            v102 = sklCsr;
            v103 = datCheckHaveSkillCnt(v90);
            klass = v102->klass;
            v99 = v103;
            v100 = v102;
            v101 = 8;
          }
          (klass->vtable._5_SetMaxPar.methodPtr)(v100, v99, v101, klass->vtable._5_SetMaxPar.method);
          ProcessData->step = 5;
          goto LABEL_168;
        }
        mskGetNo(v68, &skill2[1], skill2);
        v71 = skill2[1] == 255;
        devilSkillMax = 0;
        if (!v71)
        {
          v105 = 1;
          devilSkillMax = v105;
          if (skill2[0] != 255)
          {
LABEL_241:
            ++devilSkillMax;
            ProcessData->step = 5;
            goto LABEL_168;
          }
          goto LABEL_167;
        }
        if (skill2[0] != 255)
          goto LABEL_241;
LABEL_167:
        ProcessData->step = 5;
LABEL_168:
        devilSkillSel = 0;
        ButtonGuideDispSet("FLD04", 0, 90);
        itfMenuSetFlag(p_menuPID, 256, 1);
        itfMenuSetFlag(p_menuPID, 512, 1);
        itfMenuSetFlag(p_menuPID, 0x8000, 1);
        SE(9);
        goto LABEL_232;
      }
      if (!CHECK_TRIG(4104, 1))
        goto LABEL_249;
      if (!DlcDevilSelCheck(StockDevilID))
        goto LABEL_249;
      if (Story11Select)
        goto LABEL_250;
      if (QuestDevilSelect)
      {
LABEL_250:
        openType = devil_info2->openType;
        SE(9);
        if (openType > 1)
        {
          v83 = devil_info2->openType - 1;
          goto LABEL_231;
        }
        v83 = 3;
      }
      else
      {
LABEL_249:
        if (!CHECK_TRIG(4107, 1))
          goto LABEL_232;
        if (!DlcDevilSelCheck(StockDevilID))
          goto LABEL_232;
        if (!Story11Select)
        {
          if (!QuestDevilSelect)
            goto LABEL_232;
        }
        v86 = devil_info2->openType;
        SE(9);
        if (v86 < 3)
        {
          v83 = devil_info2->openType + 1;
          goto LABEL_231;
        }
        v83 = 1;
      }
LABEL_231:
      MenuChange(devil_info2, v83, 0);
LABEL_232:
      scrollBarSet = devil_win->scrollBarSet;
      v108 = datGetStockDevilNums(0);
      (scrollBarSet->klass->vtable._4_ScrollBarDraw.methodPtr)(scrollBarSet, 8, v108, *(u32 *)(*(u64 *)(v59 + 152) + 4 * *(char *)(v59 + 92) + 32), scrollBarSet->klass->vtable._4_ScrollBarDraw.method);
      goto LABEL_85;
    case 2u:
      if (ProcessData->count)
      {
        goto LABEL_58;
      }
      v51 = ProcessData->menuPID;
      itfMenuProcessEnd(v51);
LABEL_58:
      v11 = 0;
      if (mapMenuCheckProcEnd(ProcessData))
      {
        ProcessData->count = 0;
        ProcessData->step = 4;
        return v11;
      }
      ++ProcessData->count;
      return v11;
    case 4u:
      v11 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v11, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v11;
    case 5u:
      if (!CHECK_TRIG(4100, 1) && !CHECK_TRIG(4101, 1))
      {
        v11 = 0;
        if (CHECK_TRIG(4097, 1))
        {
          SE(1);
          v11 = 0;
          ProcessData->step = 6;
        }
        return v11;
      }
      if (devilSkillMax == 2)
      {
        devilSkillSel = (devilSkillSel & 1) == 0;
        v29 = devil_info2->openType;
        if (v29 != 2)
        {
          v29 = devil_info2->openType;
          if (v29 != 3)
          {
            v30 = 3;
LABEL_73:
            SE(v30);
          }
        }
      }
      goto LABEL_85;
    case 6u:
      ProcessData->step = 1;
      if (Story11Extra)
        goto LABEL_80;
      if (QuestDevilExtra)
      {
LABEL_80:
        v34 = &"FLD16";
        goto LABEL_82;
      }
      v34 = &"FLD03";
LABEL_82:
      ButtonGuideDispSet(*v34, 0, 90);
      v36 = ProcessData->menuPID;
      itfMenuSetFlag(v36, 256, 0);
      itfMenuSetFlag(ProcessData->menuPID, 512, 0);
      itfMenuSetFlag(ProcessData->menuPID, 0x8000, 0);
LABEL_85:
      v11 = 0;
      break;
    default:
      return v11;
  }
  return v11;
}

// 0x1c7bf20
static dds3ProcessFunc_t lmapMenuProcess(dds3ProcessID_t *PID) {
  tagMAP_MENU_WORK *ProcessData;
  dds3ProcessFunc_t v6;
  s32 StockDevilNums;
  bool v8;
  s32 v9;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *v16;
  dds3ProcessID_t *v23;
  char **v26;
  dds3ProcessID_t *v28;
  dds3ProcessID_t *v31;
  bool v32;
  dds3ProcessID_t *v34;
  s32 tabpage;
  u8 v38;
  dds3ProcessID_t *v39;
  s32 v41;
  u8 v42;
  dds3ProcessID_t *v43;
  dds3ProcessID_t *v45;
  s32 SelectID;
  s32 StockDevilID;
  bool v49;
  s32 v54;
  s32 skill2[2];
  dds3ProcessID_t *id;
  dds3ProcessID_t *v57;

  id = PID;
  *(u64 *)skill2 = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v6 = 0;
  switch (ProcessData->step)
  {
    case 0u:
      if ((ProcessData->flag & 0x10) == 0)
        return 0;
      ProcessData->flag &= ~0x10u;
      StockDevilNums = datGetStockDevilNums(0);
      ProcessData->tabpage = 0;
      v8 = StockDevilNums < 0 || (StockDevilNums & 0x80000007) == 0;
      v9 = StockDevilNums / 8;
      if (!v8)
        LOBYTE(v9) = v9 + 1;
      ProcessData->tabmax = v9;
      MenuPID = lmapMenuCreateMenuPID();
      ProcessData->menuPID = MenuPID;
      mapMenuResetMenu(ProcessData->menuPID);
      mapMenuChkEnableDecide(ProcessData);
      itfMenuStart(ProcessData->menuPID);
      v6 = 0;
      ProcessData->selectID = -1;
      ProcessData->step = 1;
      return v6;
    case 1u:
      p_menuPID = &ProcessData->menuPID;
      v16 = ProcessData->menuPID;
      v57 = ProcessData->menuPID;
      if (!v16)
        goto LABEL_102;
      if (dds3GetProcessStat(v57) != 3)
        goto LABEL_64;
LABEL_102:
      ProcessData->menuPID = 0;
      v6 = 0;
      ProcessData->step = 0;
      return v6;
LABEL_64:
      if (!dds3GetProcessStat(v57))
        goto LABEL_102;
      v34 = p_menuPID;
      if ((u32)itfMenuGetSelectID(v34) >> 16)
        return 0;
      if (mapMenuMode != 1)
        return 0;
      if (CHECK_TRIG(4103, 1))
      {
        tabpage = (u8)ProcessData->tabpage;
        v38 = ProcessData->tabmax > (char)(tabpage + 1) ? tabpage + 1 : 0;
        ProcessData->tabpage = v38;
        if (tabpage != v38)
        {
          v39 = p_menuPID;
          mapMenuResetMenu(v39);
          SE(24);
        }
      }
      if (CHECK_TRIG(4102, 1))
      {
        v41 = (u8)ProcessData->tabpage;
        v42 = v41 - 1;
        ProcessData->tabpage = v41 - 1;
        if ((((u8)v41 - 1) & 0x80) != 0)
        {
          v42 = ProcessData->tabmax - 1;
          ProcessData->tabpage = v42;
        }
        if (v41 != v42)
        {
          v43 = p_menuPID;
          mapMenuResetMenu(v43);
          SE(24);
        }
      }
      v6 = 0;
      if (CHECK_TRIG(40962, 1))
      {
        v45 = p_menuPID;
        SelectID = itfMenuGetSelectID(v45);
        skill2[1] = 0;
        StockDevilID = datGetStockDevilID(SelectID);
        skill2[0] = 0;
        mskGetNo(StockDevilID, &skill2[1], skill2);
        v49 = skill2[1] == 255;
        devilSkillMax = 0;
        if (v49)
        {
          if (skill2[0] != 255)
            goto LABEL_113;
        }
        else
        {
          v54 = 1;
          devilSkillMax = v54;
          if (skill2[0] != 255)
          {
LABEL_113:
            ++devilSkillMax;
            ProcessData->step = 5;
            goto LABEL_99;
          }
        }
        ProcessData->step = 5;
LABEL_99:
        devilSkillSel = 0;
        ButtonGuideDispSet("FLD04", 0, 90);
        itfMenuSetFlag(p_menuPID, 256, 1);
        itfMenuSetFlag(p_menuPID, 512, 1);
        v31 = p_menuPID;
        v32 = 1;
        goto LABEL_55;
      }
      return v6;
    case 2u:
      if (ProcessData->count)
      {
        goto LABEL_24;
      }
      v23 = ProcessData->menuPID;
      itfMenuProcessEnd(v23);
LABEL_24:
      v6 = 0;
      if (mapMenuCheckProcEnd(ProcessData))
      {
        ProcessData->count = 0;
        ProcessData->step = 4;
        return v6;
      }
      ++ProcessData->count;
      return v6;
    case 4u:
      v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v6, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v6;
    case 5u:
      if (CHECK_TRIG(4102, 1) || CHECK_TRIG(4103, 1))
      {
        if (devilSkillMax != 2)
          return 0;
        v6 = 0;
        devilSkillSel = (devilSkillSel & 1) == 0;
      }
      else
      {
        v6 = 0;
        if (CHECK_TRIG(4097, 1))
        {
          v6 = 0;
          ProcessData->step = 6;
        }
      }
      return v6;
    case 6u:
      ProcessData->step = 1;
      if (Story11Extra)
        goto LABEL_50;
      if (!QuestDevilExtra)
      {
        v26 = &"FLD03";
LABEL_52:
        ButtonGuideDispSet(*v26, 0, 90);
        v28 = ProcessData->menuPID;
        itfMenuSetFlag(v28, 256, 0);
        itfMenuSetFlag(ProcessData->menuPID, 512, 0);
        v31 = ProcessData->menuPID;
        v32 = 0;
LABEL_55:
        itfMenuSetFlag(v31, 0x8000, v32);
        return 0;
      }
LABEL_50:
      v26 = &"FLD16";
      goto LABEL_52;
    default:
      return v6;
  }
}

// 0x1c7c7b0
bool mapMenuCheckWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (!ProcessData)
    return !LOBYTE(ProcessData[2].klass) && (BYTE1(ProcessData[2].klass) & 0x10) == 0;
  return !LOBYTE(ProcessData[2].klass) && (BYTE1(ProcessData[2].klass) & 0x10) == 0;
}

// 0x1c7c8e0
bool mapMenuStart(void) {
  u8 *ProcessData;
  s32 v5;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v5 = ProcessData[32];
  if (!ProcessData[32])
    ProcessData[33] |= 0x10u;
  return v5 == 0;
}

// 0x1c7ca20
s32 mapMenuGetSelectID(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (!ProcessData)
    return ProcessData[9];
  return ProcessData[9];
}

// 0x1c7cb30
u32 mapMenuGetSelectUNIQ(void) {
  u32 *ProcessData;

  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (!ProcessData)
    return ProcessData[11];
  return ProcessData[11];
}

// 0x1c7cc40
static void mapMenuRelease(tagMAP_MENU_WORK *wk) {
  tagMAP_MENU_WORK *p_fields;
  sprHandle_t *hSpr;

  hSpr = wk->hSpr;
  p_fields = &wk->fields;
  if (hSpr)
  {
    p_fields->hSpr = 0;
  }
}

// 0x1c7cc60
static void mapMenuShutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  Il2CppClass *klass;
  dds3ProcessID_t *p_mapMenu_g_mainPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  klass = ProcessData[1].klass;
  v4 = ProcessData + 1;
  if (klass)
  {
    v4->klass = 0;
  }
  p_mapMenu_g_mainPID = &mapMenu_g_mainPID;
  p_mapMenu_g_mainPID = 0;
}

// 0x1c7cd80
void mapMenuProcessStart(void) {
  tagMAP_MENU_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_mapMenu_g_mainPID;

  v1 = Allocate(tagMAP_MENU_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_itf_mapMenuProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_itf_mapMenuShutdown__, 0);
  started = dds3StartProcess("map_menu", 1023, 0, 0, v2, v3, v1);
  p_mapMenu_g_mainPID = &mapMenu_g_mainPID;
  p_mapMenu_g_mainPID = started;
  v1->selectID = -1;
}

// 0x1c7cf20
void lmapMenuProcessStart(void) {
  tagMAP_MENU_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_mapMenu_g_mainPID;

  v1 = Allocate(tagMAP_MENU_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_itf_lmapMenuProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_itf_mapMenuShutdown__, 0);
  started = dds3StartProcess("map_menu", 1023, 0, 0, v2, v3, v1);
  p_mapMenu_g_mainPID = &mapMenu_g_mainPID;
  p_mapMenu_g_mainPID = started;
  v1->selectID = -1;
}

// 0x1c7d0c0
void mapMenuProcessEnd(void) {
  Il2CppObject *ProcessData;
  char v6;

  if (!mapMenu_g_mainPID)
    return;
  if (!dds3ExistProcess(mapMenu_g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(mapMenu_g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  v6 = BYTE1(ProcessData[2].klass);
  if ((v6 & 1) == 0)
  {
    WORD1(ProcessData[2].klass) = 0;
    BYTE1(ProcessData[2].klass) = v6 | 1;
    LOBYTE(ProcessData[2].klass) = 2;
  }
}

// 0x1c7d280
bool mapMenuProcessCheck(void) {
  dds3ProcessID_t *p_mapMenu_g_mainPID;

  if (!mapMenu_g_mainPID)
    return 0;
  if (dds3GetProcessStat(mapMenu_g_mainPID) != 3)
  {
    if (dds3GetProcessStat(mapMenu_g_mainPID))
    {
      return 1;
    }
  }
  p_mapMenu_g_mainPID = &mapMenu_g_mainPID;
  p_mapMenu_g_mainPID = 0;
  return 0;
}

// 0x1c7d3f0
static s32 mapMenuMoverFunc(s32 mode) {
  if (mapMenuMode != 1)
    goto LABEL_4;
  if (op_Equality(devil_win, 0, 0))
    return 0;
  if (mode)
  {
    if (mode != 1)
    {
      goto LABEL_28;
LABEL_29:
      if (op_Equality(devil_info2, 0, 0))
        return 0;
      if (!mode)
      {
        MenuOpne(devil_info2, 2, 1, 0);
        return 1;
      }
      if (mode == 1)
      {
        MenuClose(devil_info2, 0);
        return 1;
      }
      return 1;
    }
    MenuClose(devil_win, 0);
    mapMenuMode = 0;
  }
  else
  {
    MenuOpne(devil_win, 0);
  }
LABEL_28:
  goto LABEL_29;
LABEL_4:
  if (mapMenuMode)
    return 1;
  if (op_Equality(menu_win, 0, 0))
    return 0;
  if (mode != 1)
  {
    if (!mode)
    {
      MenuOpne(menu_win, 0);
    }
    return 1;
  }
  MenuClose(menu_win, 0);
  mapMenuMode = 1;
  return 1;
}

// 0x1c7d7a0
static dds3ProcessFunc_t mphLoadFileProcess(dds3ProcessID_t *id) {
  s32 fileStat;
  s64 tex_num;
  s32 v6;
  s32 v7;
  s32 v8;
  s64 v9;
  s64 v11;

  fileStat = mphWork->fileStat;
  if (fileStat != 1)
    goto LABEL_4;
  v7 = 2;
LABEL_27:
  mphWork->fileStat = v7;
  return 0;
LABEL_26:
  goto LABEL_27;
LABEL_4:
  if (fileStat == 2)
  {
    v8 = 0;
    do
    {
      v9 = v8++;
    }
    while (v9 < mphWork->pDataHeader->tex_num);
    goto LABEL_23;
    do
      v11 = v6++;
    while (v11 < tex_num);
LABEL_23:
    mphInitWork();
    mphInitPoints();
    dds3KillProcessName("Morph File Process", 0);
    v7 = 3;
    goto LABEL_26;
  }
  return 0;
}

// 0x1c7db90
static void mphLoadFileDestroy(dds3ProcessID_t *id) {
  mphWork_t *mphWork_local;

  mphWork_local = mphWork;
  if (!mphWork_local->fileHandle)
    return;
  mphWork_local = mphWork;
  mphWork_local->fileHandle = 0;
}

// 0x1c7d950
static void mphInitWork(void) {
  s32 v4;
  mphWork_t *v5;
  mphStream_t *stream1;

  mphWork->shiftNum = 2;
  mphWork->pointDataSize = 4 * mphWork->pointNum * mphWork->pointNum;
  v4 = -1;
  do
  {
    ++v4;
  }
  while (v4 < mphWork->cycleNum);
  v5 = mphWork;
  stream1 = v5->stream1;
  v5->stream0->texIndex = 0;
  stream1->texIndex = 1;
  *(u64 *)&v5->drawPointNum = (u32)(2 * v5->pointNum * (v5->pointNum - 1));
}

// 0x1c7dc60
static dds3ProcessFunc_t mphMain(dds3ProcessID_t *id) {
  sdfDrawTag_t *v2;
  s32 cycleCnt;
  f32 v7;
  f32 v8;
  f32 v9;
  s32 v13;
  s32 v15;
  u32 v17;
  f32 v18;
  s32 v19;
  mphWork_t *v20;
  s32 v21;
  s32 v22;
  sdfDrawTag_t *v23;
  mphWork_t *v25;
  s32 v26;
  s32 curCnt;
  s32 cycleNum;
  s64 v31;
  s64 v32;
  sdfIVector4_t v33;
  sdfIVector4_t v34;
  sdfIVector4_t v35;
  sdfIVector4_t v36;

  v31 = 0;
  v32 = 0;
  v2 = Allocate(sdfDrawTag_t);
  _ctor(v2, 0);
  cycleCnt = mphWork->cycleCnt;
  v7 = cycleCnt;
  v8 = (mphWork->curCnt % cycleCnt);
  if (mphWork->fMask)
  {
    NewSpecific(sdfIVector2_t, 3u);
    goto LABEL_10;
  }
LABEL_10:
  v9 = v8 / v7;
  *(u64 *)&v33.x = &v31;
  *(u64 *)&v33.z = 2;
  set_Item(v33, 128, 0);
  *(u64 *)&v34.x = &v31;
  *(u64 *)&v34.z = 1;
  set_Item(v34, 128, 0);
  *(u64 *)&v35.x = &v31;
  *(u64 *)&v35.z = 0;
  set_Item(v35, 128, 0);
  *(u64 *)&v36.x = &v31;
  *(u64 *)&v36.z = 3;
  set_Item(v36, mphWork->alpha, 0);
  mphSetPoints(v13);
  LOBYTE(v17) = mphWork->alpha;
  v18 = v9 * (f32)v17;
  v19 = v18;
  if (v18 == INFINITY)
    v19 = 0x80000000;
  HIDWORD(v32) = v19;
  mphSetPoints(v15);
  v20 = mphWork;
  mphDrawLine(v20->maskX0 - 3 * v20->leftRight, v20->maskY0, v20->maskX1 - 3 * v20->leftRight, v20->maskY1, v21, 3, v22, v23);
  v25 = mphWork;
  v26 = v25->cycleCnt;
  curCnt = v25->curCnt + 1;
  v25->curCnt = curCnt;
  if (!(curCnt % v26))
  {
    v25 = mphWork;
    curCnt = v25->curCnt;
    v26 = v25->cycleCnt;
    cycleNum = v25->cycleNum;
    v25->stream0->texIndex = (v25->stream0->texIndex + 1) % cycleNum;
    v25->stream1->texIndex = (v25->stream1->texIndex + 1) % cycleNum;
    if (curCnt == v26 * cycleNum)
    {
      v25 = mphWork;
      v25->curCnt = 0;
    }
  }
  return 0;
}

// 0x1c7e170
static void mphDestroyData(dds3ProcessID_t *id) {
  mphWork_t *mphWork_local;
  mphWork_t *v4;
  mphWork_t *v5;
  s32 v6;

  mphWork_local = mphWork;
  if (!mphWork_local->pDataHeader)
  {
    goto LABEL_5;
  }
  mphWork_local = mphWork;
  mphWork_local->pDataHeader = 0;
LABEL_5:
  v4 = mphWork;
  if (!v4->pointArray)
  {
    goto LABEL_7;
  }
  v4 = mphWork;
  v4->pointArray = 0;
LABEL_7:
  v5 = mphWork;
  if (!v5->pointOrderArray)
  {
    return;
  }
  v5 = mphWork;
  v5->pointOrderArray = 0;
  v6 = -1;
  do
  {
    ++v6;
  }
  while (v6 < mphWork->texNum);
}

// 0x1c7e330
static void mphDestroy(void) {
  mphWork_t *mphWork_local;
  mphWork_t *v3;
  mphWork_t *v4;
  mphWork_t *p_mphWork;
  s32 v6;

  dds3KillProcessName("Morph Process", 1);
  mphWork_local = mphWork;
  if (mphWork_local->fileStat)
  {
    mphWork_local = mphWork;
    if (mphWork_local->pDataHeader)
    {
      mphWork_local = mphWork;
      mphWork_local->pDataHeader = 0;
    }
    v3 = mphWork;
    if (v3->pointArray)
    {
      v3 = mphWork;
      v3->pointArray = 0;
    }
    v4 = mphWork;
    if (v4->pointOrderArray)
    {
      v4 = mphWork;
      v4->pointOrderArray = 0;
    }
    v6 = -1;
    do
    {
      ++v6;
    }
    while (v6 < mphWork->texNum);
  }
  p_mphWork = &mphWork;
  p_mphWork = 0;
}

// 0x1c7df40
static void mphLinkAlphaPacket(sdfDrawTag_t *pdrawtag, s32 fA, s32 fB, s32 fC, s32 fD, s32 fix) {
  ;
}

// 0x1c7e530
static void mphLinkTestPacket(sdfDrawTag_t *pdrawtag, u64 para) {
  ;
}

// 0x1c7df50
static void mphLinkClampPacket(sdfDrawTag_t *pdrawtag, s32 wms, s32 wmt, s32 min_u, s32 max_u, s32 min_v, s32 max_v) {
  ;
}

// 0x1c7e540
static void mphDrawTriangleStrip(s32 offX, s32 offY, s32 width, s32 height, mphPoint_t *pointArray, u16 *orderArray, s32 num, u32 z, sdfIVector4_t rgba, sdfDrawTag_t *pdrawtag) {
  if (num < 1)
    return;
  do
  {
    --num;
  }
  while (num);
}

// 0x1c7def0
static void mphDrawZMaskTri(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 z, sdfDrawTag_t *pdrawtag) {
  NewSpecific(sdfIVector2_t, 3u);
}

// 0x1c7e040
static void mphDrawLine(s32 x0, s32 y0, s32 x1, s32 y1, s32 z, s32 w, s32 color, sdfDrawTag_t *pdrawtag) {
  sdfIVector2_t *v14;
  sdfIVector2_t v15;
  s64 v16;

  v14 = NewSpecific(sdfIVector2_t, 4u);
  v15 = (sdfIVector2_t)((s64)&v14[0]);
  v16 = v14;
  set_Item((sdfIVector2_t)((s64)&v14[0]), 0, x0, 0);
  set_Item(v15, 1, y0, 0);
  set_Item((sdfIVector2_t)(v16 + 40), 0, x1, 0);
  set_Item((sdfIVector2_t)(v16 + 40), 1, y1, 0);
  set_Item((sdfIVector2_t)(v16 + 48), 0, w + x0, 0);
  set_Item((sdfIVector2_t)(v16 + 48), 1, y0, 0);
  set_Item((sdfIVector2_t)(v16 + 56), 0, w + x1, 0);
  set_Item((sdfIVector2_t)(v16 + 56), 1, y1, 0);
}

// 0x1c7da50
static void mphInitPoints(void) {
  s32 i;
  s32 j;
  s32 k;
  s32 v5;

  for (i = 0; ; ++i)
  {
    if (i >= mphWork->pointNum)
      break;
    for (j = 0; ; ++j)
    {
      if (j >= mphWork->pointNum)
        break;
    }
  }
  for (k = 0; ; ++k)
  {
    if (k >= mphWork->pointNum - 1)
      break;
    v5 = -1;
    do
    {
      ++v5;
    }
    while (v5 < mphWork->pointNum);
  }
}

// 0x1c7df60
static void mphSetPoints(s32 streamIndex) {
  s32 i;
  s32 v4;

  for (i = 0; ; ++i)
  {
    if (i >= mphWork->pointNum)
      break;
    v4 = -1;
    do
    {
      ++v4;
    }
    while (v4 < mphWork->pointNum);
  }
}

// 0x1c7e5f0
static void mphDrawStream(s32 offX, s32 offY, s32 width, s32 height, sdfIVector4_t rgba, sdfDrawTag_t *pdrawtag) {
  s32 v8;

  v8 = -1;
  do
  {
    ++v8;
  }
  while (v8 < mphWork->pointNum - 1);
}

// 0x1c7e680
static void mphStartDrawSub(s32 offX, s32 offY, s32 width, s32 height, bool fMask, s32 maskX0, s32 maskY0, s32 maskX1, s32 maskY1, s32 maskX2, s32 maskY2) {
  s32 v12;
  s32 v13;
  s32 v16;
  bool v21;
  s32 v23;
  s32 v24;
  dds3ProcessFunc_t v27;
  shutdownfuncDelegate v28;
  s32 v29;
  s32 v30;

  v12 = maskY2;
  v13 = maskX2;
  v16 = maskY1;
  v30 = maskX1;
  v29 = maskY0;
  maskY0 = v29;
  maskX1 = v30;
  v21 = fMask;
  v23 = maskX1;
  v24 = maskY0;
  maskX1 = v23;
  maskY0 = v24;
  v12 = maskY2;
  v13 = maskX2;
  v16 = maskY1;
  mphWork->offX = offX;
  mphWork->offY = offY;
  mphWork->width = width;
  mphWork->height = height;
  mphWork->fMask = v21;
  mphWork->maskX0 = maskX0;
  mphWork->maskY0 = maskY0;
  mphWork->maskX1 = maskX1;
  mphWork->maskY1 = v16;
  mphWork->maskX2 = v13;
  mphWork->maskY2 = v12;
  mphWork->fileStat = 4;
  v27 = Allocate(dds3ProcessFunc_t);
  _ctor(v27, 0, Method_Project_itf_mphMain__, 0);
  v28 = Allocate(shutdownfuncDelegate);
  _ctor(v28, 0, Method_Project_itf_mphDestroyData__, 0);
  dds3StartProcess("Morph Process", 11031, 0, 0, v27, v28, 0);
}

// 0x1c7e8b0
void mphInit(void) {
  mphWork_t *mphWork_local;

  mphWork_local = mphWork;
  mphWork_local->alpha = 0x80;
  mphWork_local->fileStat = 0;
  *(u64 *)&mphWork_local->ot = 109;
}

// 0x1c7e930
void mphStartLoad(char **filename) {
  dds3ProcessFunc_t v4;
  shutdownfuncDelegate v5;

  if (mphWork->fileStat)
    return;
  mphWork->fileStat = 1;
  v4 = Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_itf_mphLoadFileProcess__, 0);
  v5 = Allocate(shutdownfuncDelegate);
  _ctor(v5, 0, Method_Project_itf_mphLoadFileDestroy__, 0);
  dds3StartProcess("Morph File Process", 1031, 0, 0, v4, v5, 0);
}

// 0x1c7eac0
void mphStartLoadID(s32 id) {
  mphStartLoad(itf);
}

// 0x1c7eb30
s32 mphLoadCheckEnd(void) {
  return mphWork->fileStat == 3;
}

// 0x1c7eba0
MPH_STAT mphCheckStat(void) {
  return mphWork->fileStat;
}

// 0x1c7ec30
void mphEndDraw(void) {
  dds3KillProcessName("Morph Process", 1);
  mphWork->fileStat = 0;
}

// 0x1c7ece0
void mphEnd(void) {
  mphDestroy();
}

// 0x1c7ed50
void mphStartDraw(s32 offX, s32 offY, s32 width, s32 height) {
  if (mphWork->fileStat != 3)
    return;
  mphStartDrawSub(offX, offY, width, height, 0, 0, 0, 0, 0, 0, 0);
}

// 0x1c7ee60
void mphStartDrawBtlRight(void) {
  if (mphWork->fileStat != 3)
    return;
  mphWork->leftRight = 0;
  mphStartDrawSub(288, 0, 224, 448, 0, 288, 0, 288, 448, 0, 0);
}

// 0x1c7ef50
void mphStartDrawBtlLeft(void) {
  if (mphWork->fileStat != 3)
    return;
  mphWork->leftRight = 1;
  mphStartDrawSub(0, 0, 224, 448, 0, 224, 0, 224, 448, 0, 0);
}

// 0x1c7f050
void mphSetAlpha(u8 alpha) {
  mphWork->alpha = alpha;
}

// 0x1c7f0c0
u8 mphGetAlpha(void) {
  return mphWork->alpha;
}

// 0x1c7f150
void mphSetZ(s32 z) {
  mphWork->z = z;
}

// 0x1c7f1c0
s32 mphGetZ(void) {
  return mphWork->z;
}

// 0x1c7f250
void mphSetOt(DDS3_OT ot) {
  mphWork->ot = ot;
}

// 0x1c7f2c0
DDS3_OT mphGetOt(void) {
  return mphWork->ot;
}

// 0x1c7f350
s32 mphCommand_BUSTUP_LOAD(void) {
  return 1;
}

// 0x1c7f360
s32 mphCommand_BUSTUP_LOAD_WAIT(void) {
  return mphWork->fileStat == 3;
}

// 0x1c7f420
s32 mphCommand_BUSTUP_ON(void) {
  mphStartDrawBtlLeft();
  mphStartDrawBtlRight();
  return 1;
}

// 0x1c7f4a0
s32 mphCommand_BUSTUP_OFF(void) {
  mphEndDraw();
  return 1;
}

// 0x1c7f520
static void mphDebugInit(void) {
  mphDebugWork->fields = (mphDebugWork_t)xmmword_3D046A0;
}

// 0x1c7f590
static void mphDebugDrawMenu(void) {
  u16 *v1;

  v1 = NewSpecific(char, 0x80u);
  CreateString_54864672(0, v1, 0);
}

// 0x1c7f630
static void mphDebugPadDealer(void) {
  s32 menuIndex;
  mphDebugWork_t *v6;
  mphDebugWork_t *v9;
  u32 v10;
  s32 v11;
  s32 fileIndex;
  u32 v14;
  mphDebugWork_t *v15;
  u32 v16;

  if (mphDebugWork->stat != 1)
    return;
  if (CHECK_REP(4100, 1))
  {
    menuIndex = mphDebugWork->menuIndex;
    if (menuIndex >= 1)
    {
      menuIndex = mphDebugWork->menuIndex;
      mphDebugWork->menuIndex = menuIndex - 1;
    }
  }
  if (!!CHECK_REP(4101, 1))
  {
    v6 = mphDebugWork;
    if (!v6->menuIndex)
      goto LABEL_26;
  }
  if (!CHECK_REP(4102, 1))
    goto LABEL_41;
  goto LABEL_18;
LABEL_26:
  v11 = 0;
  v6->menuIndex = v11 + 1;
  if (!CHECK_REP(4102, 1))
    goto LABEL_41;
LABEL_18:
  v9 = mphDebugWork;
  if (!v9->menuIndex)
  {
    v9 = mphDebugWork;
    fileIndex = v9->fileIndex;
    if (fileIndex >= 2)
    {
      v9 = mphDebugWork;
      fileIndex = v9->fileIndex;
      v9->fileIndex = fileIndex - 1;
    }
    goto LABEL_41;
  }
  if (v9->leftRight)
  {
    if (!v10)
    {
      v9 = mphDebugWork;
    }
    v9->leftRight = 0;
    goto LABEL_41;
  }
  if (!v10)
  {
    v9 = mphDebugWork;
  }
  v9->leftRight = 1;
LABEL_41:
  if (!CHECK_REP(4103, 1))
    goto LABEL_54;
  v15 = mphDebugWork;
  if (v15->menuIndex)
    goto LABEL_44;
  goto LABEL_51;
  if (!v15->menuIndex)
  {
LABEL_51:
    if (!v14)
    {
      v15 = mphDebugWork;
    }
    ++v15->fileIndex;
LABEL_54:
    if (!CHECK_REP(4096, 1))
      return;
    goto LABEL_55;
  }
LABEL_44:
  if (v14)
  {
    if (v15->leftRight)
      goto LABEL_46;
LABEL_59:
    if (!v16)
    {
      v15 = mphDebugWork;
    }
    v15->leftRight = 1;
    if (CHECK_REP(4096, 1))
      goto LABEL_55;
    return;
  }
  v15 = mphDebugWork;
  if (!v15->leftRight)
    goto LABEL_59;
LABEL_46:
  if (!v16)
  {
    v15 = mphDebugWork;
  }
  v15->leftRight = 0;
  if (CHECK_REP(4096, 1))
  {
LABEL_55:
    mphDebugWork->stat = 0;
  }
}

// 0x1c7fa00
static dds3ProcessFunc_t mphDebugProcess(dds3ProcessID_t *id) {
  u16 *v5;

  mphDebugPadDealer();
  if (mphDebugWork->stat)
    goto LABEL_4;
  mphDebugWork->stat = 1;
LABEL_5:
  goto LABEL_7;
LABEL_4:
  goto LABEL_5;
LABEL_7:
  v5 = NewSpecific(char, 0x80u);
  CreateString_54864672(0, v5, 0);
  return 0;
}

// 0x1c7fb70
static void mphDebugDestroy(dds3ProcessID_t *id) {
  if (!mphDebugWork)
    return;
  mphDebugWork = 0;
}

// 0x1c7fc30
s32 mphStart(void) {
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;

  mphDebugWork->fields = (mphDebugWork_t)xmmword_3D046A0;
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_itf_mphDebugProcess__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_itf_mphDebugDestroy__, 0);
  dds3StartProcess("Morph Debug Process", 11031, 0, 0, v3, v4, 0);
  return 0;
}

// 0x1c7fdf0
s32 mphShutDown(void) {
  dds3KillProcessName("Morph Debug Process", 0);
  return 0;
}

// 0x1c7fe70
void itfLogDispWorkNewGameInit(void) {
  LOGDISP_PARAM *p_logdispwk;
  LOGDISP_PARAM *v3;

  p_logdispwk = &logdispwk;
  p_logdispwk = 0;
  v3 = Allocate(LOGDISP_PARAM);
  _ctor(v3, 0);
  logdispwk = v3;
}

// 0x1c6a890
static bool MsgLogDispCalc(void) {
  s32 start;
  s32 v5;
  LOGDISP_PARAM *v8;
  void *MsgLogList;
  s32 v11;
  void *v12;
  Il2CppObject *v13;
  void *msgList;
  Il2CppObject *Item;
  char *v19;
  void *v20;
  s64 i;
  u32 v23;
  s32 *selidx;
  LOGDISP_PARAM *v25;
  s32 v26;
  s32 v27;
  s32 v28;
  LOGDISP_PARAM *v30;
  void *v32;
  void *p_msglogSceneOp;
  void *v34;
  LOGDISP_PARAM *v35;
  void *v39;
  u64 *v44;
  bool *v45;
  bool *v46;
  void *gouto_obj;
  s32 v54;
  void *v55;
  void *v56;
  Il2CppObject *v57;
  f32 v58;
  LOGDISP_PARAM *v60;
  void *v61;
  void *v62;
  Il2CppObject *v63;
  void *v64;
  void *NewScrollbar;
  void *v66;
  void *v67;
  void *transform;
  int32x2_t *v71;
  u64 v72;
  u64 *p_klass;
  bool *v76;
  bool *v77;
  void *VoiceLogList;
  s32 LogListCount;
  Il2CppObject *v80;
  void *Instance;
  char **v82;
  s32 v86;
  void *v87;
  void *DispScrollbar;
  f32 value;
  void *v90;
  void *v91;
  Il2CppObject *Component_object;
  void *v93;
  void *v94;
  void *v95;
  int32x2_t *v98;
  u64 v99;
  void *v102;
  s32 v104;
  Il2CppObject *v105;
  Il2CppObject *v106;
  LOGDISP_PARAM *v108;
  LOGDISP_PARAM *v109;
  s32 logidx;
  s32 logcurtop;
  void *v112;
  void *ArrowObj;
  void *v114;
  void *v115;
  bool v116;
  LOGDISP_PARAM *v117;
  s32 v118;
  s32 v119;
  void *v120;
  void *v121;
  void *v122;
  void *v123;
  void *v124;
  void *v125;
  void *v126;
  void *v127;
  f32 y;
  sdfVector2_t v130;

  start = logdispwk->start;
  if (!start)
    return start != 0;
  v5 = start - 1;
  if ((u32)(start - 1) > 3)
    return start != 0;
  switch (v5)
  {
    case 0:
      if (msglogSceneOp)
      {
        if (!get_isDone(msglogSceneOp, 0))
          return start != 0;
      }
      OnEvent(logdispwk, 0);
      Unload(Dependent, msglog_akey, 0);
      v8 = logdispwk;
      ++v8->start;
      MsgLogList = scrGetMsgLogList();
      v8->msgList = MsgLogList;
      v11 = 0;
LABEL_29:
      msgList = logdispwk->msgList;
      if (v11 < msgList->_size)
      {
        msgList = logdispwk->msgList;
        Item = _get_Item(msgList, v11);
        v19 = TextColorClose(Item);
        v20 = Allocate(System_Text_StringBuilder);
        _ctor_56629520(v20, v19, 0);
        Replace(v20, "<color=#FFFFFFFF>", "", 0);
        for (i = 0; ; ++i)
        {
          v25 = logdispwk;
          selidx = v25->selidx;
          if (i >= SLODWORD(selidx->max_length))
          {
            if (!v23)
            {
              v25 = logdispwk;
            }
            v12 = v25->msgList;
            v13 = (v20->klass->vtable._3_ToString.methodPtr)(v20, v20->klass->vtable._3_ToString.method);
            _set_Item(v12, v11++, v13);
            goto LABEL_29;
          }
          if (v23)
          {
            if (selidx[i] != v11)
              continue;
          }
          else
          {
            if (logdispwk->selidx[i] != v11)
              continue;
          }
          Replace(v20, "\n", "</color>\n", 0);
          Replace(v20, "<color=#A9A9A9FF>", "<color=#707070FF>", 0);
        }
      }
      MsgLogDispDraw();
      logdispwk->logidx = 0;
      scrollbarInit();
      FadeOutWindow();
      gouto_obj = get_Instance(0)->gouto_obj;
      if (get_activeSelf(gouto_obj, 0))
        SetActive(gouto_obj, 0, 0);
      fieldUIDispFlag = 0;
      logdispwk->moonFlag = 0;
      if (!!evtMoonGetDraw())
      {
        evtMoonDisableDraw(1);
        logdispwk->moonFlag = 1;
      }
      p_klass = &logdispwk->klass;
      v76 = p_klass[9];
      p_klass += 9;
      v77 = evtPictureGameObjDisp(0, v76);
      *p_klass = v77;
      VoiceLogList = scrGetVoiceLogList();
      LogListCount = scrGetLogListCount();
      v80 = _get_Item(VoiceLogList, (LogListCount - 1) & (u32)~((LogListCount - 1) >> 31));
      LOBYTE(VoiceLogList) = IsNullOrEmpty(v80, 0);
      Instance = get_Instance(0);
      v82 = &"LOG001";
      if (((u8)VoiceLogList & 1) == 0)
        v82 = &"LOG000";
      GuideSet(Instance, *v82, 0, 90, 0);
      if (op_Inequality(map_win, 0, 0))
      {
        map_win->NxtAnimeNum = 3;
      }
      return start != 0;
    case 1:
      v26 = scrGetLogListCount();
      v27 = v26;
      if (v26 >= 5)
        v28 = 5;
      else
        v28 = v26;
      if (logdispwk->initflag)
      {
        if (CHECK_TRIG(4097, 1))
        {
LABEL_52:
          SE(1);
          v30 = logdispwk;
          ++v30->start;
          v32 = UnloadSceneAsync("UI_msglog", 0);
          p_msglogSceneOp = &msglogSceneOp;
          p_msglogSceneOp = v32;
          sndVoiceStop(0);
          return start != 0;
        }
LABEL_129:
        if (CHECK_REP(4101, 1))
        {
          if (v27 == 1)
            return start != 0;
          v64 = get_Instance(0);
          NewScrollbar = GetNewScrollbar(v64, 0);
          GetComponent_object_(NewScrollbar);
          v66 = get_Instance(0);
          v67 = GetNewScrollbar(v66, 0);
          transform = get_transform(v67, 0);
          get_position(transform, 0);
          v71 = logdispwk;
          v72 = vadd_s32(v71[5], (int32x2_t)0x1FFFFFFFFLL).n64_u64[0];
          v71[5].n64_u64[0] = v72;
          if ((v72 & 0x80000000) != 0)
          {
            v71 = logdispwk;
            v71[5].n64_u32[0] = 0;
            v71[5].n64_u32[1] = v27 - 1;
          }
          else
          {
            SE(3);
            ButtonGuideCalc(logdispwk->logcurtop, v27);
          }
          v109 = logdispwk;
          logidx = v109->logidx;
          if (logidx)
          {
            v109 = logdispwk;
            logidx = v109->logidx;
            v109->logidx = logidx - 1;
          }
          scrollbarCalc(1);
          logcurtop = logdispwk->logcurtop;
          v112 = get_Instance(0);
          ArrowObj = GetArrowObj(v112, 0, 0);
          SetActive(ArrowObj, 1, 0);
          v114 = get_Instance(0);
          v115 = GetArrowObj(v114, 1, 0);
          if (!logcurtop)
          {
            v116 = 0;
LABEL_217:
            SetActive(v115, v116, 0);
            return start != 0;
          }
        }
        else
        {
          if (!CHECK_REP(4100, 1))
          {
            if (CHECK_TRIG(4096, 1))
            {
              if (scrGetLogListCount())
              {
                v102 = scrGetVoiceLogList();
                scrGetMsgLogList();
                v104 = v27 - 1;
                v105 = _get_Item(v102, v104 - logdispwk->logcurtop);
                v106 = _get_Item(logdispwk->msgList, v104 - logdispwk->logcurtop);
                if (!IsNullOrEmpty(v105, 0))
                {
                  sndVoiceStop(0);
                  sndVoicePlayFile(v105, 0);
                  v108 = logdispwk;
                  v108->textsave = v106;
                }
              }
            }
            return start != 0;
          }
          v86 = v27 - 1;
          if (v27 == 1)
            return start != 0;
          v87 = get_Instance(0);
          DispScrollbar = GetDispScrollbar(v87, 0);
          value = get_value(DispScrollbar, 0);
          set_value(DispScrollbar, value + (f32)(-1.0 / (f32)v27), 0);
          v90 = get_Instance(0);
          v91 = GetNewScrollbar(v90, 0);
          Component_object = GetComponent_object_(v91);
          get_sizeDelta(Component_object, 0);
          v93 = get_Instance(0);
          v94 = GetNewScrollbar(v93, 0);
          v95 = get_transform(v94, 0);
          get_position(v95, 0);
          v98 = logdispwk;
          if ((signed s32)(v98[6].n64_u32[0] + v98[4].n64_u32[0]) < v27)
          {
            v98 = logdispwk;
            v99 = vadd_s32(v98[5], (int32x2_t)0xFFFFFFFF00000001LL).n64_u64[0];
            v98[5].n64_u64[0] = v99;
            if ((s32)v99 >= v27)
            {
              v98 = logdispwk;
              v98[5].n64_u32[0] = v27;
              v98[5].n64_u32[1] = 1;
            }
            else
            {
              SE(3);
              ButtonGuideCalc(logdispwk->logcurtop, v27);
            }
            v117 = logdispwk;
            v118 = v117->logcurtop;
            if (v118 >= 4)
            {
              v117 = logdispwk;
              v118 = v117->logcurtop;
              if (v118 < v27)
              {
                v117 = logdispwk;
                ++v117->logidx;
              }
            }
          }
          scrollbarCalc(0);
          v119 = logdispwk->logcurtop;
          v120 = get_Instance(0);
          v121 = GetArrowObj(v120, 0, 0);
          if (v119 == v86)
          {
            SetActive(v121, 0, 0);
            v122 = get_Instance(0);
            v115 = GetArrowObj(v122, 1, 0);
            v116 = 1;
            goto LABEL_217;
          }
          SetActive(v121, 1, 0);
          v123 = get_Instance(0);
          v115 = GetArrowObj(v123, 1, 0);
        }
        SetActive(v115, 1, 0);
        v124 = get_Instance(0);
        v125 = arrowAnimState(v124, 0, 0);
        v126 = get_Instance(0);
        v127 = arrowAnimState(v126, 1, 0);
        SameAnmPlay(v125, v127, -1.0, 0);
        return start != 0;
      }
      v54 = scrGetLogListCount();
      v55 = get_Instance(0);
      v56 = GetNewScrollbar(v55, 0);
      v57 = GetComponent_object_(v56);
      y = get_sizeDelta(v57, 0).y;
      v58 = 0.0;
      if (v54 != 1)
        v58 = (f32)(836.0 - y) / (f32)(v54 - 1);
      v60 = logdispwk;
      v60->initflag = 1;
      v60->curidx = 0;
      v60->logidx = 0;
      v60->logtop = v27 - v28;
      v60->logcurtop = 0;
      v60->curtop = v27 - 1;
      v61 = get_Instance(0);
      v62 = GetNewScrollbar(v61, 0);
      v63 = GetComponent_object_(v62);
      v130.x = 0.0;
      v130.y = -(f32)(v58 * (f32)(v27 - 1));
      set_anchoredPosition(v63, v130, 0);
      if (CHECK_TRIG(4097, 1))
        goto LABEL_52;
      goto LABEL_129;
    case 2:
      v34 = msglogSceneOp;
      if (v34)
      {
        v34 = msglogSceneOp;
        if (!get_isDone(v34, 0))
          return start != 0;
      }
      v35 = logdispwk;
      v35->start = 4;
      ButtonGuideDispOff();
      if (!is_field)
      {
        FadeInWindow();
      }
      v39 = get_Instance(0)->gouto_obj;
      if (!get_activeSelf(v39, 0))
        SetActive(v39, 1, 0);
      fieldUIDispFlag = 1;
      msg_logFlag = 1;
      if (logdispwk->msgwin)
      {
        setGuideMsg(1, 0);
      }
      if (logdispwk->moonFlag)
      {
        evtMoonEnableDraw();
        logdispwk->moonFlag = 0;
      }
      if (!lipsync_pm->start)
      {
        goto LABEL_99;
      }
      lipsync_pm->lipend_time = 60;
LABEL_99:
      v44 = &logdispwk->klass;
      v45 = v44[9];
      v44 += 9;
      v46 = evtPictureGameObjDisp(1, v45);
      *v44 = v46;
      is_field = 0;
      OffEvent(logdispwk, 0);
      dds3UnloadUnusedAssets(1);
      return start != 0;
    case 3:
      logdispwk->start = 0;
      logdispwk->logidx = 0;
      logdispwk->initflag = 0;
      logdispwk->logPlay = 0;
      return start != 0;
    default:
      return start != 0;
  }
}

// 0x1c80650
static void ChangeArrowAnim(s32 curTop, s32 logMax) {
  s32 v3;
  bool v5;
  bool v6;
  void *Instance;
  void *ArrowObj;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;

  v3 = logMax - 1;
  v5 = logMax - 1 != curTop;
  v6 = logMax - 1 == curTop || curTop != 0;
  Instance = get_Instance(0);
  ArrowObj = GetArrowObj(Instance, 0, 0);
  SetActive(ArrowObj, v5, 0);
  v9 = get_Instance(0);
  v10 = GetArrowObj(v9, 1, 0);
  SetActive(v10, v6, 0);
  if (v3 != curTop)
  {
    if (curTop)
    {
      v11 = get_Instance(0);
      v12 = arrowAnimState(v11, 0, 0);
      v13 = get_Instance(0);
      v14 = arrowAnimState(v13, 1, 0);
      SameAnmPlay(v12, v14, -1.0, 0);
    }
  }
}

// 0x1c80410
static void ButtonGuideCalc(s32 curTop, s32 logMax) {
  void *VoiceLogList;
  Il2CppObject *Item;
  bool IsNullOrEmpty;
  void *Instance;
  char **v9;

  VoiceLogList = scrGetVoiceLogList();
  Item = _get_Item(VoiceLogList, ~curTop + logMax);
  IsNullOrEmpty = IsNullOrEmpty(Item, 0);
  Instance = get_Instance(0);
  if (IsNullOrEmpty)
    v9 = &"LOG001";
  else
    v9 = &"LOG000";
  GuideSet(Instance, *v9, 0, 90, 0);
}

// 0x1c6be70
static void MsgLogDispDraw(void) {
  void *Instance;
  void *Prefab;
  Il2CppObject *Component_object;
  s32 v5;
  u32 i;
  void *v7;
  void *WinImage;
  void *v9;
  void *MsgText;
  void *v11;
  void *SpeakerText;
  void *v13;
  void *CursorObj;
  void *v15;
  void *ViceIcon;
  void *v17;
  void *v18;
  s32 v20;
  s32 logcurtop;
  Il2CppObject *v25;
  Il2CppObject *v28;
  void *v32;
  Il2CppObject *Item;
  Il2CppObject *v36;
  void *v38;
  bool v39;
  bool v40;
  u32 v42;
  Il2CppObject *v43;
  Il2CppObject *v46;
  long f64 v48;
  long f64 v49;
  long f64 v50;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  u32 v57;
  s32 v58;
  bool IsNullOrEmpty;
  u32 rgba;
  Il2CppObject *v64;
  Il2CppObject *v67;
  u32 v72;
  bool v74;
  u32 v76;
  bool v77;
  void *v78;
  u32 v80;
  s32 v83;
  Il2CppObject *v84;
  Il2CppObject *v87;
  Il2CppObject *v89;
  Il2CppObject *v92;
  bool v94;
  u32 v96;
  u32 v98;
  bool v99;
  s32 logidx;
  Il2CppObject *v101;
  Il2CppObject *v104;
  Il2CppObject *v109;
  Il2CppObject *v112;
  void *v114;
  bool v115;
  u32 v117;
  bool v118;
  long f64 v119;
  long f64 v120;
  long f64 v121;
  f32 v123;
  f32 v124;
  f32 v125;
  f32 v126;
  f32 v127;
  u32 v128;
  s32 v129;
  u32 v131;
  bool v132;
  u32 v134;
  void *v137;
  s32 v138;
  s32 v139;
  char *textsave;
  char *v142;
  bool v143;
  void *v144;
  bool v145;
  bool v146;
  u32 v148;
  u32 v150;
  u32 v152;
  bool v153;
  long f64 v154;
  long f64 v155;
  long f64 v156;
  f32 v158;
  f32 v159;
  f32 v160;
  f32 v161;
  f32 v162;
  u32 v163;
  s32 v164;
  u32 v166;
  s32 v168;
  s32 v169;
  void *v170;
  void *v171;
  void *v172;
  void *v173;
  void *v174;
  void *v175;
  void *v176;
  void *v177;
  void *v178;
  void *v179;
  void *v180;
  void *v181;
  void *v182;
  void *v183;
  Il2CppObject *v184;
  char *v185;
  Il2CppObject *v188;
  bool v192;
  void *v194;
  u32 v196;
  bool v197;
  char *v199;
  char *v200;
  void *v202;
  void *Parent;
  Il2CppObject *v204;
  s32 LogListCount;
  void *MsgLogList;
  void *CursorViceIcon;
  void *VoiceLogList;
  s32 v209;
  sdfVector2_t v210;

  if (logdispwk->start != 2)
    return;
  LogListCount = scrGetLogListCount();
  if (LogListCount)
  {
    MsgLogList = scrGetMsgLogList();
    scrGetSpeakerLogList();
    VoiceLogList = scrGetVoiceLogList();
    if (logdispwk->initflag)
    {
LABEL_14:
      v209 = LogListCount - 1;
      Instance = get_Instance(0);
      Prefab = GetPrefab(Instance, 0);
      Component_object = GetComponent_object_(Prefab);
      SetInteger(Component_object, "anim", 1, 0);
      if (LogListCount > 1)
      {
        v5 = 0;
        for (i = 0; ; ++i)
        {
          v7 = get_Instance(0);
          WinImage = GetWinImage(v7, i, 0);
          v9 = get_Instance(0);
          MsgText = GetMsgText(v9, i, 0);
          v11 = get_Instance(0);
          SpeakerText = GetSpeakerText(v11, i, 0);
          v13 = get_Instance(0);
          CursorObj = GetCursorObj(v13, i, 0);
          v15 = get_Instance(0);
          ViceIcon = GetViceIcon(v15, i, 0);
          v17 = get_Instance(0);
          CursorViceIcon = GetCursorViceIcon(v17, i, 0);
          v18 = get_Instance(0);
          GetNoName_SpaceObj(v18, i, 0);
          v20 = v209 + v5;
          logcurtop = logdispwk->logcurtop;
          if (!logcurtop)
            goto LABEL_22;
          if (MsgLogList->_size == 2)
          {
LABEL_22:
            if (logcurtop == 1)
              goto LABEL_24;
            goto LABEL_9002;
            if (logdispwk->logcurtop == 1)
            {
LABEL_24:
              if (i > 2)
                goto LABEL_198;
              if (v5 == -2)
              {
                SetActive(WinImage, 1, 0);
                if (op_Inequality(MsgText, 0, 0))
                  goto LABEL_28;
                goto LABEL_115;
LABEL_116:
                (SpeakerText->klass[3]._2.genericContainerHandle)(SpeakerText, "", *(u64 *)&SpeakerText->klass[3]._2.instance_size);
LABEL_31:
                if (!op_Inequality(ViceIcon, 0, 0))
                  goto LABEL_198;
                goto LABEL_9001;
LABEL_28:
                (MsgText->klass[3]._2.genericContainerHandle)(MsgText, "", *(u64 *)&MsgText->klass[3]._2.instance_size);
LABEL_115:
                if (op_Inequality(SpeakerText, 0, 0))
                  goto LABEL_116;
                goto LABEL_31;
LABEL_9001:
                v32 = ViceIcon;
                goto LABEL_196;
              }
              Item = _get_Item(VoiceLogList, v20 - logdispwk->logidx);
              SetActive(WinImage, 1, 0);
              if (!!op_Inequality(MsgText, 0, 0))
              {
                v36 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
                (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v36, *(u64 *)&MsgText->klass[3]._2.instance_size);
              }
              name_spaceActive(v20 - logdispwk->logidx, i);
              if (op_Inequality(ViceIcon, 0, 0))
              {
                IsNullOrEmpty = IsNullOrEmpty(Item, 0);
                SetActive(ViceIcon, !IsNullOrEmpty, 0);
                if (v5 != -1)
                  goto LABEL_188;
                goto LABEL_127;
              }
              if (v5 != -1)
                goto LABEL_188;
LABEL_127:
              if (!op_Inequality(CursorObj, 0, 0))
                goto LABEL_198;
              if (!get_activeSelf(CursorObj, 0))
              {
                SetActive(CursorObj, 1, 0);
                rgba = logdispwk->FONTCOLOR_WHITE.rgba;
                (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)rgba / 255.0, (f32)BYTE1(rgba) / 255.0, (f32)BYTE2(rgba) / 255.0, (f32)HIBYTE(rgba) / 255.0);
              }
              if (!IsNullOrEmpty(Item, 0))
                goto LABEL_179;
              goto LABEL_135;
            }
LABEL_9002:
            if (i > 1)
            {
              if (op_Inequality(WinImage, 0, 0))
              {
                v38 = WinImage;
                goto LABEL_81;
              }
              goto LABEL_163;
            }
            v25 = _get_Item(VoiceLogList, v20 - logdispwk->logidx);
            SetActive(WinImage, 1, 0);
            if (!!op_Inequality(MsgText, 0, 0))
            {
              v28 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v28, *(u64 *)&MsgText->klass[3]._2.instance_size);
            }
            name_spaceActive(v20 - logdispwk->logidx, i);
            if (!op_Inequality(ViceIcon, 0, 0))
            {
              if (v5)
                goto LABEL_93;
              goto LABEL_9003;
            }
            v40 = IsNullOrEmpty(v25, 0);
            SetActive(ViceIcon, !v40, 0);
            if (v5)
            {
LABEL_93:
              if (v42)
              {
                if (!op_Inequality(CursorObj, 0, 0))
                  goto LABEL_163;
              }
              else
              {
                if (!op_Inequality(CursorObj, 0, 0))
                  goto LABEL_163;
              }
              if (get_activeSelf(CursorObj, 0))
                SetActive(CursorObj, 0, 0);
              *(f32 *)&v48 = (*&MsgText->klass[1]._2.field_count)(MsgText, *(u64 *)&MsgText->klass[1]._2.interfaces_count);
              v52 = *(f32 *)&v48;
              v53 = *(f32 *)&v49;
              v54 = *(f32 *)&v50;
              v56 = v55;
              v57 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
              *(f32 *)&v48 = (f32)(u8)v57 / 255.0;
              *(f32 *)&v49 = (f32)BYTE1(v57) / 255.0;
              *(f32 *)&v50 = (f32)BYTE2(v57) / 255.0;
              if ((f32)((f32)((f32)(v56 - (f32)((f32)HIBYTE(v57) / 255.0)) * (f32)(v56 - (f32)((f32)HIBYTE(v57) / 255.0))) + (f32)((f32)((f32)(v54 - *(f32 *)&v50) * (f32)(v54 - *(f32 *)&v50)) + (f32)((f32)((f32)(v52 - *(f32 *)&v48) * (f32)(v52 - *(f32 *)&v48)) + (f32)((f32)(v53 - *(f32 *)&v49) * (f32)(v53 - *(f32 *)&v49))))) >= 9.9999994e-11)
              {
                v58 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
                *(f32 *)&v48 = (f32)(u8)v58 / 255.0;
                *(f32 *)&v49 = (f32)BYTE1(v58) / 255.0;
                *(f32 *)&v50 = (f32)BYTE2(v58) / 255.0;
                (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, v48, v49, v50);
              }
              goto LABEL_163;
            }
LABEL_9003:
            if (v42)
            {
              if (!op_Inequality(CursorObj, 0, 0))
                goto LABEL_163;
            }
            else
            {
              if (!op_Inequality(CursorObj, 0, 0))
                goto LABEL_163;
            }
            if (!get_activeSelf(CursorObj, 0))
            {
              SetActive(CursorObj, 1, 0);
              v72 = logdispwk->FONTCOLOR_WHITE.rgba;
              (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v72 / 255.0, (f32)BYTE1(v72) / 255.0, (f32)BYTE2(v72) / 255.0, (f32)HIBYTE(v72) / 255.0);
            }
            if (IsNullOrEmpty(v25, 0))
            {
              v38 = CursorViceIcon;
LABEL_81:
              v39 = 0;
            }
            else
            {
              v38 = CursorViceIcon;
              v39 = 1;
            }
            SetActive(v38, v39, 0);
LABEL_163:
            logdispwk->curmax = 1;
            goto LABEL_330;
          }
          if (logcurtop == 1)
            goto LABEL_51;
          if (MsgLogList->_size == 3)
          {
LABEL_51:
            if (logcurtop == 2)
              goto LABEL_53;
            if (i > 2)
            {
              if (op_Inequality(WinImage, 0, 0))
              {
                v32 = WinImage;
                goto LABEL_196;
              }
LABEL_198:
              v83 = 2;
              goto LABEL_329;
            }
            v43 = _get_Item(VoiceLogList, v20 - logdispwk->logidx);
            SetActive(WinImage, 1, 0);
            if (!!op_Inequality(MsgText, 0, 0))
            {
              v46 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v46, *(u64 *)&MsgText->klass[3]._2.instance_size);
            }
            name_spaceActive(v20 - logdispwk->logidx, i);
            if (op_Inequality(ViceIcon, 0, 0))
              goto LABEL_170;
            if (v5 != -1)
              goto LABEL_188;
LABEL_171:
            if (!op_Inequality(CursorObj, 0, 0))
              goto LABEL_198;
            if (!get_activeSelf(CursorObj, 0))
            {
              v76 = logdispwk->FONTCOLOR_WHITE.rgba;
              (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v76 / 255.0, (f32)BYTE1(v76) / 255.0, (f32)BYTE2(v76) / 255.0, (f32)HIBYTE(v76) / 255.0);
              SetActive(CursorObj, 1, 0);
            }
            if (!IsNullOrEmpty(v43, 0))
            {
LABEL_179:
              v32 = CursorViceIcon;
              v77 = 1;
LABEL_197:
              SetActive(v32, v77, 0);
              goto LABEL_198;
            }
LABEL_135:
            v32 = CursorViceIcon;
            goto LABEL_9004;
LABEL_170:
            v74 = IsNullOrEmpty(v43, 0);
            SetActive(ViceIcon, !v74, 0);
            if (v5 == -1)
              goto LABEL_171;
LABEL_188:
            if (!op_Inequality(CursorObj, 0, 0))
              goto LABEL_198;
            if (!get_activeSelf(CursorObj, 0))
              goto LABEL_198;
            v80 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
            (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v80 / 255.0, (f32)BYTE1(v80) / 255.0, (f32)BYTE2(v80) / 255.0, (f32)HIBYTE(v80) / 255.0);
            v32 = CursorObj;
LABEL_9004:
LABEL_196:
            v77 = 0;
            goto LABEL_197;
LABEL_53:
            if (i > 3)
              goto LABEL_326;
            if (v5 == -3)
            {
              SetActive(WinImage, 1, 0);
              if (op_Inequality(MsgText, 0, 0))
                goto LABEL_57;
              goto LABEL_223;
LABEL_224:
              (SpeakerText->klass[3]._2.genericContainerHandle)(SpeakerText, "", *(u64 *)&SpeakerText->klass[3]._2.instance_size);
LABEL_60:
              if (!op_Inequality(ViceIcon, 0, 0))
                goto LABEL_326;
              goto LABEL_9005;
LABEL_57:
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, "", *(u64 *)&MsgText->klass[3]._2.instance_size);
LABEL_223:
              if (op_Inequality(SpeakerText, 0, 0))
                goto LABEL_224;
              goto LABEL_60;
LABEL_9005:
              v78 = ViceIcon;
              goto LABEL_244;
            }
            v64 = _get_Item(VoiceLogList, v20 - logdispwk->logidx);
            SetActive(WinImage, 1, 0);
            if (!!op_Inequality(MsgText, 0, 0))
            {
              v67 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v67, *(u64 *)&MsgText->klass[3]._2.instance_size);
            }
            name_spaceActive(v20 - logdispwk->logidx, i);
            if (op_Inequality(ViceIcon, 0, 0))
            {
              v94 = IsNullOrEmpty(v64, 0);
              SetActive(ViceIcon, !v94, 0);
              if (v5 != -2)
                goto LABEL_291;
              goto LABEL_235;
            }
            if (v5 != -2)
              goto LABEL_291;
LABEL_235:
            if (!v96)
            if (!op_Inequality(CursorObj, 0, 0))
              goto LABEL_326;
            if (!get_activeSelf(CursorObj, 0))
            {
              v98 = logdispwk->FONTCOLOR_WHITE.rgba;
              (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v98 / 255.0, (f32)BYTE1(v98) / 255.0, (f32)BYTE2(v98) / 255.0, (f32)HIBYTE(v98) / 255.0);
              SetActive(CursorObj, 1, 0);
            }
            if (!IsNullOrEmpty(v64, 0))
              goto LABEL_325;
            goto LABEL_243;
          }
          if (logcurtop == 2)
            goto LABEL_146;
          if (MsgLogList->_size == 4)
          {
LABEL_146:
            if (logcurtop == 3)
              goto LABEL_148;
            if (i > 3)
            {
              if (op_Inequality(WinImage, 0, 0))
              {
                v78 = WinImage;
                goto LABEL_244;
              }
LABEL_326:
              v83 = 3;
LABEL_329:
              logdispwk->curmax = v83;
              goto LABEL_330;
            }
            v89 = _get_Item(VoiceLogList, v20 - logdispwk->logidx);
            SetActive(WinImage, 1, 0);
            if (!!op_Inequality(MsgText, 0, 0))
            {
              v92 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v92, *(u64 *)&MsgText->klass[3]._2.instance_size);
            }
            name_spaceActive(v20 - logdispwk->logidx, i);
            if (op_Inequality(ViceIcon, 0, 0))
              goto LABEL_290;
            if (v5 == -2)
              goto LABEL_317;
LABEL_291:
            if (!v96)
            if (op_Inequality(CursorObj, 0, 0))
            {
              if (get_activeSelf(CursorObj, 0))
                SetActive(CursorObj, 0, 0);
              *(f32 *)&v119 = (*&MsgText->klass[1]._2.field_count)(MsgText, *(u64 *)&MsgText->klass[1]._2.interfaces_count);
              v123 = *(f32 *)&v119;
              v124 = *(f32 *)&v120;
              v125 = *(f32 *)&v121;
              v127 = v126;
              v128 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
              *(f32 *)&v119 = (f32)(u8)v128 / 255.0;
              *(f32 *)&v120 = (f32)BYTE1(v128) / 255.0;
              *(f32 *)&v121 = (f32)BYTE2(v128) / 255.0;
              if ((f32)((f32)((f32)(v127 - (f32)((f32)HIBYTE(v128) / 255.0)) * (f32)(v127 - (f32)((f32)HIBYTE(v128) / 255.0))) + (f32)((f32)((f32)(v125 - *(f32 *)&v121) * (f32)(v125 - *(f32 *)&v121)) + (f32)((f32)((f32)(v123 - *(f32 *)&v119) * (f32)(v123 - *(f32 *)&v119)) + (f32)((f32)(v124 - *(f32 *)&v120) * (f32)(v124 - *(f32 *)&v120))))) >= 9.9999994e-11)
              {
                v129 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
                *(f32 *)&v119 = (f32)(u8)v129 / 255.0;
                *(f32 *)&v120 = (f32)BYTE1(v129) / 255.0;
                *(f32 *)&v121 = (f32)BYTE2(v129) / 255.0;
                (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, v119, v120, v121);
              }
            }
            goto LABEL_326;
LABEL_290:
            v118 = IsNullOrEmpty(v89, 0);
            SetActive(ViceIcon, !v118, 0);
            if (v5 != -2)
              goto LABEL_291;
LABEL_317:
            if (!v96)
            if (!op_Inequality(CursorObj, 0, 0))
              goto LABEL_326;
            if (!get_activeSelf(CursorObj, 0))
            {
              v134 = logdispwk->FONTCOLOR_WHITE.rgba;
              (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v134 / 255.0, (f32)BYTE1(v134) / 255.0, (f32)BYTE2(v134) / 255.0, (f32)HIBYTE(v134) / 255.0);
              SetActive(CursorObj, 1, 0);
            }
            if (!IsNullOrEmpty(v89, 0))
            {
LABEL_325:
              v78 = CursorViceIcon;
              v99 = 1;
              goto LABEL_245;
            }
LABEL_243:
            v78 = CursorViceIcon;
LABEL_244:
            v99 = 0;
LABEL_245:
            SetActive(v78, v99, 0);
            goto LABEL_326;
LABEL_148:
            if (v5 == -4)
            {
              SetActive(WinImage, 1, 0);
              if (op_Inequality(MsgText, 0, 0))
                goto LABEL_151;
              goto LABEL_276;
LABEL_277:
              (SpeakerText->klass[3]._2.genericContainerHandle)(SpeakerText, "", *(u64 *)&SpeakerText->klass[3]._2.instance_size);
LABEL_154:
              if (!op_Inequality(ViceIcon, 0, 0))
                goto LABEL_407;
              goto LABEL_9006;
LABEL_151:
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, "", *(u64 *)&MsgText->klass[3]._2.instance_size);
LABEL_276:
              if (op_Inequality(SpeakerText, 0, 0))
                goto LABEL_277;
              goto LABEL_154;
              if (!op_Inequality(ViceIcon, 0, 0))
              {
LABEL_407:
                v83 = 4;
                goto LABEL_329;
              }
LABEL_9006:
              v114 = ViceIcon;
LABEL_313:
              v132 = 0;
LABEL_314:
              SetActive(v114, v132, 0);
              goto LABEL_407;
            }
            v84 = _get_Item(VoiceLogList, v20 - logdispwk->logidx);
            SetActive(WinImage, 1, 0);
            if (!!op_Inequality(MsgText, 0, 0))
            {
              v87 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v87, *(u64 *)&MsgText->klass[3]._2.instance_size);
            }
            name_spaceActive(v20 - logdispwk->logidx, i);
            if (op_Inequality(ViceIcon, 0, 0))
              goto LABEL_284;
            if (v5 == -3)
              goto LABEL_304;
LABEL_385:
            if (!v117)
            if (op_Inequality(CursorObj, 0, 0))
            {
              if (get_activeSelf(CursorObj, 0))
                SetActive(CursorObj, 0, 0);
              *(f32 *)&v154 = (*&MsgText->klass[1]._2.field_count)(MsgText, *(u64 *)&MsgText->klass[1]._2.interfaces_count);
              v158 = *(f32 *)&v154;
              v159 = *(f32 *)&v155;
              v160 = *(f32 *)&v156;
              v162 = v161;
              v163 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
              *(f32 *)&v154 = (f32)(u8)v163 / 255.0;
              *(f32 *)&v155 = (f32)BYTE1(v163) / 255.0;
              *(f32 *)&v156 = (f32)BYTE2(v163) / 255.0;
              if ((f32)((f32)((f32)(v162 - (f32)((f32)HIBYTE(v163) / 255.0)) * (f32)(v162 - (f32)((f32)HIBYTE(v163) / 255.0))) + (f32)((f32)((f32)(v160 - *(f32 *)&v156) * (f32)(v160 - *(f32 *)&v156)) + (f32)((f32)((f32)(v158 - *(f32 *)&v154) * (f32)(v158 - *(f32 *)&v154)) + (f32)((f32)(v159 - *(f32 *)&v155) * (f32)(v159 - *(f32 *)&v155))))) >= 9.9999994e-11)
              {
                v164 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
                *(f32 *)&v154 = (f32)(u8)v164 / 255.0;
                *(f32 *)&v155 = (f32)BYTE1(v164) / 255.0;
                *(f32 *)&v156 = (f32)BYTE2(v164) / 255.0;
                (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, v154, v155, v156);
              }
            }
            goto LABEL_407;
LABEL_284:
            v115 = IsNullOrEmpty(v84, 0);
            SetActive(ViceIcon, !v115, 0);
            if (v5 != -3)
              goto LABEL_385;
LABEL_304:
            if (!v117)
            if (!op_Inequality(CursorObj, 0, 0))
              goto LABEL_407;
            if (!get_activeSelf(CursorObj, 0))
            {
              v131 = logdispwk->FONTCOLOR_WHITE.rgba;
              (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v131 / 255.0, (f32)BYTE1(v131) / 255.0, (f32)BYTE2(v131) / 255.0, (f32)HIBYTE(v131) / 255.0);
              SetActive(CursorObj, 1, 0);
            }
            if (IsNullOrEmpty(v84, 0))
            {
LABEL_312:
              v114 = CursorViceIcon;
              goto LABEL_313;
            }
LABEL_406:
            v114 = CursorViceIcon;
            v132 = 1;
            goto LABEL_314;
          }
          if (logcurtop < 3)
            goto LABEL_258;
          logidx = logdispwk->logidx;
          if (logidx + 4 < LogListCount)
          {
            logidx = logdispwk->logidx;
            v101 = _get_Item(VoiceLogList, v20 - logidx);
            SetActive(WinImage, 1, 0);
            if (!!op_Inequality(MsgText, 0, 0))
            {
              v104 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
              (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v104, *(u64 *)&MsgText->klass[3]._2.instance_size);
            }
            name_spaceActive(v20 - logdispwk->logidx, i);
            if (op_Inequality(ViceIcon, 0, 0))
            {
              v153 = IsNullOrEmpty(v101, 0);
              SetActive(ViceIcon, !v153, 0);
              if (v5 != -3)
                goto LABEL_385;
LABEL_398:
              if (!v117)
              if (!op_Inequality(CursorObj, 0, 0))
                goto LABEL_407;
              if (!get_activeSelf(CursorObj, 0))
              {
                v166 = logdispwk->FONTCOLOR_WHITE.rgba;
                (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v166 / 255.0, (f32)BYTE1(v166) / 255.0, (f32)BYTE2(v166) / 255.0, (f32)HIBYTE(v166) / 255.0);
                SetActive(CursorObj, 1, 0);
              }
              if (IsNullOrEmpty(v101, 0))
                goto LABEL_312;
              goto LABEL_406;
            }
            if (v5 != -3)
              goto LABEL_385;
            goto LABEL_398;
          }
LABEL_258:
          SetActive(WinImage, 1, 0);
          if (v5 == -4)
          {
            if (op_Inequality(MsgText, 0, 0))
              goto LABEL_261;
            goto LABEL_351;
LABEL_352:
            (SpeakerText->klass[3]._2.genericContainerHandle)(SpeakerText, "", *(u64 *)&SpeakerText->klass[3]._2.instance_size);
LABEL_264:
            if (!op_Inequality(ViceIcon, 0, 0))
              goto LABEL_330;
            goto LABEL_9007;
LABEL_261:
            (MsgText->klass[3]._2.genericContainerHandle)(MsgText, "", *(u64 *)&MsgText->klass[3]._2.instance_size);
LABEL_351:
            if (op_Inequality(SpeakerText, 0, 0))
              goto LABEL_352;
            goto LABEL_264;
LABEL_9007:
            v144 = ViceIcon;
            goto LABEL_355;
          }
          v109 = _get_Item(VoiceLogList, v20 - logdispwk->logidx);
          if (!op_Inequality(MsgText, 0, 0))
          {
            goto LABEL_359;
          }
          v112 = _get_Item(logdispwk->msgList, v20 - logdispwk->logidx);
          (MsgText->klass[3]._2.genericContainerHandle)(MsgText, v112, *(u64 *)&MsgText->klass[3]._2.instance_size);
LABEL_359:
          name_spaceActive(v20 - logdispwk->logidx, i);
          if (op_Inequality(ViceIcon, 0, 0))
          {
            v146 = IsNullOrEmpty(v109, 0);
            SetActive(ViceIcon, !v146, 0);
            if (v5 != -3)
              goto LABEL_362;
            goto LABEL_371;
          }
          if (v5 != -3)
          {
LABEL_362:
            if (!v148)
            if (op_Inequality(CursorObj, 0, 0) && get_activeSelf(CursorObj, 0))
            {
              v150 = *(u32 *)&logdispwk->FONTCOLOR_WHITE.r;
              (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v150 / 255.0, (f32)BYTE1(v150) / 255.0, (f32)BYTE2(v150) / 255.0, (f32)HIBYTE(v150) / 255.0);
              v144 = CursorObj;
LABEL_355:
              v145 = 0;
              goto LABEL_356;
            }
            goto LABEL_330;
          }
LABEL_371:
          if (!v148)
          if (op_Inequality(CursorObj, 0, 0))
          {
            if (!get_activeSelf(CursorObj, 0))
            {
              v152 = logdispwk->FONTCOLOR_WHITE.rgba;
              (*&MsgText->klass[1]._2.naturalAligment)(MsgText, MsgText->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v152 / 255.0, (f32)BYTE1(v152) / 255.0, (f32)BYTE2(v152) / 255.0, (f32)HIBYTE(v152) / 255.0);
              SetActive(CursorObj, 1, 0);
            }
            if (IsNullOrEmpty(v109, 0))
            {
              v144 = CursorViceIcon;
              goto LABEL_355;
            }
            v144 = CursorViceIcon;
            v145 = 1;
LABEL_356:
            SetActive(v144, v145, 0);
          }
LABEL_330:
          if (!sndVoiceStatus(0))
          {
            v137 = get_Instance(0);
            goto LABEL_337;
          }
          if (!op_Inequality(MsgText, 0, 0))
            goto LABEL_339;
          textsave = logdispwk->textsave;
          if (!textsave)
            goto LABEL_339;
          textsave = logdispwk->textsave;
          v143 = op_Equality(textsave, v142, 0);
          v137 = get_Instance(0);
          if (v143)
          {
            v138 = i;
            v139 = 0;
          }
          else
          {
LABEL_337:
            v138 = i;
            v139 = 1;
          }
          AnmVoiceIcon(v137, v138, v139, 0);
LABEL_339:
          logSpaceCalc(v20, i);
          if (--v5 == -5)
            return;
        }
      }
      v168 = 0;
      while (1)
      {
        v171 = get_Instance(0);
        v172 = GetWinImage(v171, v168, 0);
        v173 = get_Instance(0);
        v174 = GetMsgText(v173, v168, 0);
        v175 = get_Instance(0);
        v176 = GetSpeakerText(v175, v168, 0);
        v177 = get_Instance(0);
        v178 = GetCursorObj(v177, v168, 0);
        v179 = get_Instance(0);
        v180 = GetViceIcon(v179, v168, 0);
        v181 = get_Instance(0);
        v182 = GetCursorViceIcon(v181, v168, 0);
        v183 = get_Instance(0);
        GetNoName_SpaceObj(v183, v168, 0);
        v184 = _get_Item(VoiceLogList, v209);
        if (v168 == 1)
          break;
        if (!v168)
        {
          v185 = v184;
          SetActive(v172, 1, 0);
          if (!!op_Inequality(v174, 0, 0))
          {
            v188 = _get_Item(logdispwk->msgList, v209);
            (v174->klass[3]._2.genericContainerHandle)(v174, v188, *(u64 *)&v174->klass[3]._2.instance_size);
          }
          name_spaceActive(v209 - logdispwk->logidx, 0);
          if (!!op_Inequality(v180, 0, 0))
          {
            v192 = IsNullOrEmpty(v185, 0);
            SetActive(v180, !v192, 0);
          }
          if (!op_Inequality(v178, 0, 0))
            goto LABEL_459;
          if (!get_activeSelf(v178, 0))
          {
            SetActive(v178, 1, 0);
            v196 = logdispwk->FONTCOLOR_WHITE.rgba;
            (*&v174->klass[1]._2.naturalAligment)(v174, v174->klass[1].vtable._0_Equals.methodPtr, (f32)(u8)v196 / 255.0, (f32)BYTE1(v196) / 255.0, (f32)BYTE2(v196) / 255.0, (f32)HIBYTE(v196) / 255.0);
          }
          if (IsNullOrEmpty(v185, 0))
          {
            v194 = v182;
            goto LABEL_457;
          }
          v194 = v182;
          v197 = 1;
          goto LABEL_458;
        }
        if (!op_Inequality(v172, 0, 0))
          goto LABEL_459;
        v194 = v172;
LABEL_457:
        v197 = 0;
LABEL_458:
        SetActive(v194, v197, 0);
LABEL_459:
        if (!sndVoiceStatus(0))
        {
          v169 = 1;
          goto LABEL_413;
        }
        if (!op_Inequality(v174, 0, 0))
          goto LABEL_414;
        v199 = logdispwk->textsave;
        if (!v199)
          goto LABEL_414;
        v199 = logdispwk->textsave;
        if (!op_Equality(v199, v200, 0))
          goto LABEL_414;
        v169 = 0;
LABEL_413:
        v170 = get_Instance(0);
        AnmVoiceIcon(v170, v168, v169, 0);
LABEL_414:
        if (++v168 == 5)
        {
          logdispwk->curmax = 0;
          return;
        }
      }
      SetActive(v172, 1, 0);
      if (op_Inequality(v174, 0, 0))
      {
        (v174->klass[3]._2.genericContainerHandle)(v174, "", *(u64 *)&v174->klass[3]._2.instance_size);
        goto LABEL_442;
      }
      if (!op_Inequality(v176, 0, 0))
        goto LABEL_427;
      goto LABEL_443;
LABEL_442:
      if (!op_Inequality(v176, 0, 0))
      {
LABEL_427:
        if (op_Inequality(v180, 0, 0))
          goto LABEL_445;
        goto LABEL_459;
      }
LABEL_443:
      (v176->klass[3]._2.genericContainerHandle)(v176, "", *(u64 *)&v176->klass[3]._2.instance_size);
      if (!op_Inequality(v180, 0, 0))
        goto LABEL_459;
LABEL_445:
      v194 = v180;
      goto LABEL_457;
    }
    v202 = get_Instance(0);
    Parent = GetParent(v202, 0);
    v204 = GetComponent_object_(Parent);
    v210.y = (f32)LogListCount * 440.0;
    v210.x = 0.0;
    set_sizeDelta(v204, v210, 0);
    goto LABEL_14;
  }
}

// 0x1c80c00
static void logSpaceCalc(s32 idx, s32 cnt) {
  void *Instance;
  void *NoName_SpaceObj;
  void *v7;
  void *SpaceObj;
  void *v9;
  void *Space2Obj;
  void *v11;
  void *Space3Obj;
  void *v13;
  void *SpeakerLogList;
  void *v15;
  void *MsgText;
  char *v17;
  s32 v18;
  s32 v19;
  u16 Chars;
  Il2CppObject *Item;
  bool v28;
  void *v29;
  bool v30;
  bool v31;

  Instance = get_Instance(0);
  NoName_SpaceObj = GetNoName_SpaceObj(Instance, cnt, 0);
  v7 = get_Instance(0);
  SpaceObj = GetSpaceObj(v7, cnt, 0);
  v9 = get_Instance(0);
  Space2Obj = GetSpace2Obj(v9, cnt, 0);
  v11 = get_Instance(0);
  Space3Obj = GetSpace3Obj(v11, cnt, 0);
  v13 = get_Instance(0);
  GetmeslogObj(v13, 0);
  SpeakerLogList = scrGetSpeakerLogList();
  v15 = get_Instance(0);
  MsgText = GetMsgText(v15, cnt, 0);
  v17 = (MsgText->klass->vtable._65_get_text.methodPtr)(MsgText, MsgText->klass->vtable._65_get_text.method);
  if (v17->_stringLength < 1)
    return;
  v18 = 0;
  v19 = 1;
  do
  {
    Chars = get_Chars(v17, v18++, 0);
    if (Chars == 10)
      ++v19;
  }
  while (v18 < v17->_stringLength);
  if (v19 != 1)
  {
    if (v19 != 3)
    {
      if (v19 == 2)
      {
        if (!op_Inequality(SpaceObj, 0, 0))
        {
          goto LABEL_19;
        }
        SetActive(SpaceObj, 1, 0);
LABEL_19:
        if (!op_Inequality(Space2Obj, 0, 0))
          goto LABEL_49;
        v29 = Space2Obj;
        v30 = 0;
LABEL_48:
        SetActive(v29, v30, 0);
        goto LABEL_49;
      }
      if (v19 < 4)
      {
        if (!op_Inequality(SpaceObj, 0, 0))
        {
          goto LABEL_30;
        }
        SetActive(SpaceObj, 0, 0);
LABEL_30:
        if (!op_Inequality(Space2Obj, 0, 0))
          goto LABEL_32;
        goto LABEL_31;
        if (!op_Inequality(Space2Obj, 0, 0))
        {
LABEL_32:
          goto LABEL_50;
        }
LABEL_31:
        SetActive(Space2Obj, 0, 0);
        goto LABEL_32;
      }
      if (op_Inequality(NoName_SpaceObj, 0, 0))
      {
        Item = _get_Item(SpeakerLogList, idx - logdispwk->logidx);
        v28 = op_Inequality(Item, "", 0);
        SetActive(NoName_SpaceObj, !v28, 0);
        if (op_Inequality(SpaceObj, 0, 0))
          SetActive(SpaceObj, v28, 0);
      }
      if (!op_Inequality(Space2Obj, 0, 0))
      {
        goto LABEL_66;
      }
      SetActive(Space2Obj, 0, 0);
LABEL_66:
      if (!op_Inequality(Space3Obj, 0, 0))
        return;
      v31 = 1;
      goto LABEL_54;
    }
    if (!op_Inequality(SpaceObj, 0, 0))
    {
      goto LABEL_24;
    }
    SetActive(SpaceObj, 0, 0);
LABEL_24:
    if (!op_Inequality(Space2Obj, 0, 0))
    {
LABEL_49:
LABEL_50:
      if (!op_Inequality(Space3Obj, 0, 0))
        return;
      v31 = 0;
LABEL_54:
      SetActive(Space3Obj, v31, 0);
      return;
    }
    v29 = Space2Obj;
    v30 = 1;
    goto LABEL_48;
  }
}

// 0x1c811a0
static s32 LineCount(char *s) {
  s32 v3;
  s32 v4;
  u16 Chars;

  if (s->_stringLength < 1)
    return 1;
  v3 = 0;
  v4 = 1;
  do
  {
    Chars = get_Chars(s, v3++, 0);
    if (Chars == 10)
      ++v4;
  }
  while (v3 < s->_stringLength);
  return v4;
}

// 0x1c80730
static void name_spaceActive(s32 idx, s32 cnt) {
  void *SpeakerLogList;
  void *VoiceLogList;
  void *Instance;
  void *SpeakerText;
  void *v9;
  void *NoName_SpaceObj;
  void *v11;
  void *SpaceObj;
  void *v13;
  void *Space2Obj;
  void *v15;
  void *Space3Obj;
  Il2CppObject *Item;
  bool v21;
  Il2CppObject *v22;
  void *v24;
  void *v25;
  Il2CppObject *v26;
  void *v27;
  void *v30;
  bool v31;

  SpeakerLogList = scrGetSpeakerLogList();
  VoiceLogList = scrGetVoiceLogList();
  Instance = get_Instance(0);
  SpeakerText = GetSpeakerText(Instance, cnt, 0);
  v9 = get_Instance(0);
  NoName_SpaceObj = GetNoName_SpaceObj(v9, cnt, 0);
  v11 = get_Instance(0);
  SpaceObj = GetSpaceObj(v11, cnt, 0);
  v13 = get_Instance(0);
  Space2Obj = GetSpace2Obj(v13, cnt, 0);
  v15 = get_Instance(0);
  Space3Obj = GetSpace3Obj(v15, cnt, 0);
  if (!op_Inequality(SpaceObj, 0, 0))
  {
    goto LABEL_8;
  }
  SetActive(SpaceObj, 0, 0);
LABEL_8:
  if (!op_Inequality(Space2Obj, 0, 0))
  {
    goto LABEL_10;
  }
  SetActive(Space2Obj, 0, 0);
LABEL_10:
  if (!op_Inequality(Space3Obj, 0, 0))
  {
    goto LABEL_12;
  }
  SetActive(Space3Obj, 0, 0);
LABEL_12:
  if (!op_Inequality(SpeakerText, 0, 0))
    return;
  Item = _get_Item(SpeakerLogList, idx);
  v21 = op_Inequality(Item, "", 0);
  v22 = _get_Item(SpeakerLogList, idx);
  (SpeakerText->klass[3]._2.genericContainerHandle)(SpeakerText, v22, *(u64 *)&SpeakerText->klass[3]._2.instance_size);
  if (v21)
  {
    v24 = VoiceLogList;
    if (!op_Inequality(SpaceObj, 0, 0))
      return;
    v26 = _get_Item(v24, idx);
    if (op_Inequality(v26, "", 0))
      v27 = SpaceObj;
    else
      v27 = Space3Obj;
    SetActive(v27, 0, 0);
    v30 = NoName_SpaceObj;
    v31 = 1;
LABEL_41:
    SetActive(v30, v31, 0);
    return;
  }
  v25 = NoName_SpaceObj;
  if (!op_Inequality(NoName_SpaceObj, 0, 0))
    return;
  SetActive(v25, 1, 0);
  if (!op_Inequality(SpaceObj, 0, 0))
  {
    goto LABEL_35;
  }
  SetActive(SpaceObj, 0, 0);
LABEL_35:
  if (!op_Inequality(Space2Obj, 0, 0))
  {
    goto LABEL_37;
  }
  SetActive(Space2Obj, 0, 0);
LABEL_37:
  if (!op_Inequality(Space3Obj, 0, 0))
    return;
  v30 = Space3Obj;
  v31 = 0;
  goto LABEL_41;
}

// 0x1c802c0
static void scrollbarInit(void) {
  s32 LogListCount;
  void *Instance;
  void *ArrowObj;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  Il2CppObject *Component_object;
  void *v9;
  void *v10;
  void *v11;
  void *NewScrollbar;
  sdfVector2_t v13;

  LogListCount = scrGetLogListCount();
  Instance = get_Instance(0);
  ArrowObj = GetArrowObj(Instance, 0, 0);
  if (LogListCount > 2)
  {
    SetActive(ArrowObj, 1, 0);
    v9 = get_Instance(0);
    v10 = GetArrowObj(v9, 1, 0);
    SetActive(v10, 0, 0);
    v11 = get_Instance(0);
    NewScrollbar = GetNewScrollbar(v11, 0);
    Component_object = GetComponent_object_(NewScrollbar);
    v13.y = (f32)(0x344u / LogListCount);
  }
  else
  {
    SetActive(ArrowObj, 0, 0);
    v4 = get_Instance(0);
    v5 = GetArrowObj(v4, 1, 0);
    SetActive(v5, 0, 0);
    v6 = get_Instance(0);
    v7 = GetNewScrollbar(v6, 0);
    Component_object = GetComponent_object_(v7);
    v13.y = 836.0;
  }
  v13.x = 8.0;
  set_sizeDelta(Component_object, v13, 0);
}

// 0x1c80500
static void scrollbarCalc(s32 late) {
  s32 LogListCount;
  void *Instance;
  void *NewScrollbar;
  Il2CppObject *Component_object;
  f32 y;
  f32 v9;
  void *v10;
  void *v11;
  Il2CppObject *v12;
  sdfVector2_t v13;

  LogListCount = scrGetLogListCount();
  Instance = get_Instance(0);
  NewScrollbar = GetNewScrollbar(Instance, 0);
  Component_object = GetComponent_object_(NewScrollbar);
  y = get_sizeDelta(Component_object, 0).y;
  if ((u32)late <= 1)
  {
    v9 = (f32)((f32)-(f32)(836.0 - y) / (f32)(LogListCount - 1))
       * (f32)logdispwk->curtop;
    v10 = get_Instance(0);
    v11 = GetNewScrollbar(v10, 0);
    v12 = GetComponent_object_(v11);
    v13.x = 0.0;
    v13.y = v9;
    set_anchoredPosition(v12, v13, 0);
  }
}

// 0x1c5f840
static bool IsMsgLogStart(void) {
  s32 v4;

  if (!itfIsMesKey(36867, 2))
  {
LABEL_18:
    goto LABEL_19;
  }
  if (!CheckChangeAutoFeed())
    goto LABEL_18;
  v4 = cfgGetConfigAUDIO(7, 0) == 0;
  cfgSetConfigAUDIO(7, v4, 0);
  setGuideMsg(0, 0);
LABEL_19:
  if (!scrIsLogSave())
    return 0;
  if (!scrGetLogListCount())
    return 0;
  if (logdispwk->start)
    return 0;
  if (!op_Inequality(msg_guide_name, "", 0))
    return 0;
  if (scrIsEventSkip(0))
    return 0;
  if (!isMesWndBaseDisp)
    return 0;
  if (logdispwk->pmvrun)
    return 0;
  if (!itfIsMesKey(36877, 2))
    return 0;
  itfMsgLogStartUI(1);
  SE(17);
  return 1;
}

// 0x1c81590
void itfMsgLogStartUI(bool msgwin) {
  bool v3;
  LOGDISP_PARAM *logdispwk_local;
  void *SceneAsync;
  void *p_msglogSceneOp;
  s32 unit_uniqid;
  dds3ModelHandle_t *LipModel;
  void *gameObject;
  Il2CppObject *Component_object;

  v3 = msgwin;
  itfPreDrawActionWndDisp(0);
  logdispwk_local = logdispwk;
  *(u64 *)&logdispwk_local->start = 1;
  logdispwk_local->logPlay = 1;
  logdispwk_local->msgwin = v3;
  Load(Dependent, msglog_akey, msglog_akey);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, "UI_msglog", 0);
  p_msglogSceneOp = &msglogSceneOp;
  p_msglogSceneOp = SceneAsync;
  unit_uniqid = lipsync_pm->unit_uniqid;
  LipModel = evtGetLipModel(unit_uniqid);
  if (LipModel)
  {
    gameObject = get_gameObject(LipModel->modelRoot->modelObj, 0);
    Component_object = GetComponent_object_(gameObject);
    goto LABEL_15;
  }
  Component_object = 0;
LABEL_15:
  sndVoiceStop(Component_object);
  scrEventSkipEnd(1, 0);
}

// 0x1c81230
static bool CheckChangeAutoFeed(void) {
  bool v2;

  goto LABEL_3;
LABEL_7:
  if (!logdispwk->pmvrun)
    goto LABEL_11;
  return 0;
LABEL_3:
  v2 = scrIsEventSkip(0);
  if (v2)
    goto LABEL_7;
LABEL_11:
  if (Equals_54828784(msg_guide_name, "MSG004", 0))
    return 1;
  if (Equals_54828784(msg_guide_name, "MSG005", 0))
    return 1;
  if (Equals_54828784(msg_guide_name, "MSG0010", 0))
    return 1;
  return Equals_54828784(msg_guide_name, "MSG0011", 0);
}

// 0x1c81850
bool itfMsgLogPlayCheck(void) {
  return logdispwk->logPlay;
}

// 0x1c7ff20
static char *TextColorClose(char *str) {
  char *v3;
  void *v4;
  void *v5;
  char **v6;
  void *v7;
  const MethodInfo_2DFC360 **v8;
  s32 v9;
  char *v10;
  s32 v11;
  Il2CppObject *v12;
  Il2CppObject *Item;
  Il2CppObject *v14;
  char *v15;
  Il2CppObject *v16;
  Il2CppObject *v17;
  bool v18;
  char *v19;
  Il2CppObject *v20;
  Il2CppObject *v21;
  char *v22;
  const MethodInfo_2DFC360 **v23;
  char **v24;
  bool v25;
  Il2CppObject *v26;
  Il2CppObject *v27;
  char **v28;
  bool v29;
  Il2CppObject *v30;
  char *v32;

  v3 = "";
  v4 = Split_54844384(str, "<color=", 0, 0);
  v5 = ToList_object_(v4);
  if (v5->_size >= 2)
  {
    v6 = &"#FFFFFFFF";
    v7 = v5;
    v8 = &Method_System_Collections_Generic_List_string__set_Item__;
    v9 = 0;
    v10 = v3;
    v32 = str;
    while (1)
    {
      Item = _get_Item(v7, v9);
      if (op_Equality(Item, "", 0))
        goto LABEL_7;
      if (v9 || str->_stringLength >= 7 && (v22 = Substring_54838176(str, 0, 7, 0), !op_Inequality(v22, "<color=", 0)))
      {
        v14 = _get_Item(v7, v9);
        v15 = Substring_54838176(v14, 0, 9, 0);
        if (!op_Equality(v15, *v6, 0))
        {
          v23 = v8;
          v24 = v6;
          v25 = op_Equality(v10, "", 0);
          v26 = _get_Item(v7, v9);
          v19 = Substring_54838176(v26, 0, 9, 0);
          if (v25)
          {
            v27 = _get_Item(v7, v9);
            v28 = &"<color=";
            goto LABEL_20;
          }
          v29 = op_Inequality(v10, v19, 0);
          v30 = _get_Item(v7, v9);
          if (v29)
          {
            v19 = Substring_54838176(v30, 0, 9, 0);
            v27 = _get_Item(v7, v9);
            v28 = &"</color><color=";
LABEL_20:
            v21 = Concat_54766928(*v28, v27, 0);
          }
          else
          {
            v21 = Remove(v30, 0, 10, 0);
            v19 = v10;
          }
          v6 = v24;
          v8 = v23;
          str = v32;
          goto LABEL_23;
        }
        v16 = _get_Item(v7, v9);
        v17 = Remove(v16, 0, 10, 0);
        _set_Item(v7, v9, v17, *v8);
        v18 = op_Inequality(v10, "", 0);
        v11 = v9;
        if (v18)
        {
          v19 = "";
          v20 = _get_Item(v7, v9);
          v21 = Concat_54766928("</color>", v20, 0);
LABEL_23:
          _set_Item(v7, v9, v21, *v8);
          v11 = v9;
          v10 = v19;
        }
      }
      else
      {
        v11 = 0;
      }
      v12 = _get_Item(v7, v11);
      v3 = Concat_54766928(v3, v12, 0);
LABEL_7:
      if (++v9 >= v7->_size)
        return v3;
    }
  }
  return str;
}

// 0x1c818e0
void savePointMenuProcessStart(void) {
  tagSAVEPOINT_MENU_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_savePointMenu_g_mainPID;
  tagSAVEPOINT_MENU_WORK *p_fields;

  v1 = Allocate(tagSAVEPOINT_MENU_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_itf_savePointMenuProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_itf_savePointMenuShutdown__, 0);
  started = dds3StartProcess("savePoint_menu", 1023, 0, 0, v2, v3, v1);
  p_savePointMenu_g_mainPID = &savePointMenu_g_mainPID;
  p_savePointMenu_g_mainPID = started;
  v1->hSpr = generalMenu_g_hSpr;
  p_fields = &v1->fields;
  *(u64 *)&p_fields->selectID = -1;
}

// 0x1c81ad0
bool savePointMenuStart(void) {
  u8 *ProcessData;
  s32 v5;

  ProcessData = dds3GetProcessData(savePointMenu_g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v5 = ProcessData[32];
  if (!ProcessData[32])
    ProcessData[33] |= 0x10u;
  return v5 == 0;
}

// 0x1c81c10
static dds3ProcessFunc_t savePointMenuProcess(dds3ProcessID_t *PID) {
  tagSAVEPOINT_MENU_WORK *ProcessData;
  dds3ProcessFunc_t v6;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *v16;
  dds3ProcessID_t *id;
  dds3ProcessID_t *v20;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v6 = 0;
  switch (ProcessData->step)
  {
    case 0u:
      if ((ProcessData->flag & 0x10) == 0)
        return 0;
      ProcessData->flag &= ~0x10u;
      MenuPID = savePointMenuCreateMenuPID();
      ProcessData->menuPID = MenuPID;
      savePointMenuChkEnableDecide(ProcessData);
      itfMenuStart(ProcessData->menuPID);
      v6 = 0;
      ProcessData->selectID = 255;
      ProcessData->step = 1;
      return v6;
    case 1u:
      v7 = ProcessData->menuPID;
      if (itfMenuGetCtrlType(ProcessData->menuPID) != 5)
      {
        v14 = ProcessData->menuPID;
        v20 = ProcessData->menuPID;
        if (v14)
        {
          if (dds3GetProcessStat(v20) != 3)
          {
            if (dds3GetProcessStat(v20))
              return 0;
          }
        }
        ProcessData->menuPID = 0;
      }
      v6 = 0;
      ProcessData->step = 0;
      return v6;
    case 2u:
      if (ProcessData->count)
      {
        goto LABEL_17;
      }
      v16 = ProcessData->menuPID;
      itfMenuProcessEnd(v16);
LABEL_17:
      v6 = 0;
      if (savePointMenuCheckProcEnd(ProcessData))
      {
        ++ProcessData->count;
        return v6;
      }
      ProcessData->count = 0;
      ProcessData->step = 4;
      return v6;
    case 4u:
      v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v6, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v6;
    default:
      return v6;
  }
}

// 0x1c828a0
static void savePointMenuShutdown(dds3ProcessID_t *PID) {
  tagSAVEPOINT_MENU_WORK *ProcessData;
  dds3ProcessID_t *p_savePointMenu_g_mainPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  savePointMenuRelease(ProcessData);
  p_savePointMenu_g_mainPID = &savePointMenu_g_mainPID;
  p_savePointMenu_g_mainPID = 0;
}

// 0x1c82ab0
bool savePointMenuCheckWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(savePointMenu_g_mainPID);
  if (!ProcessData)
    return !LOBYTE(ProcessData[2].klass) && (BYTE1(ProcessData[2].klass) & 0x10) == 0;
  return !LOBYTE(ProcessData[2].klass) && (BYTE1(ProcessData[2].klass) & 0x10) == 0;
}

// 0x1c82be0
s32 savePointMenuGetSelectID(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(savePointMenu_g_mainPID);
  if (!ProcessData)
    return ProcessData[9];
  return ProcessData[9];
}

// 0x1c82cf0
bool savePointMenuProcessCheck(void) {
  dds3ProcessID_t *p_savePointMenu_g_mainPID;

  if (!savePointMenu_g_mainPID)
    return 0;
  if (dds3GetProcessStat(savePointMenu_g_mainPID) != 3)
  {
    if (dds3GetProcessStat(savePointMenu_g_mainPID))
    {
      return 1;
    }
  }
  p_savePointMenu_g_mainPID = &savePointMenu_g_mainPID;
  p_savePointMenu_g_mainPID = 0;
  return 0;
}

// 0x1c82e60
void savePointMenuProcessEnd(void) {
  Il2CppObject *ProcessData;
  char v6;

  if (!savePointMenu_g_mainPID)
    return;
  if (!dds3ExistProcess(savePointMenu_g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(savePointMenu_g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  v6 = BYTE1(ProcessData[2].klass);
  if ((v6 & 1) == 0)
  {
    WORD1(ProcessData[2].klass) = 0;
    BYTE1(ProcessData[2].klass) = v6 | 1;
    LOBYTE(ProcessData[2].klass) = 2;
  }
}

// 0x1c81fd0
static dds3ProcessID_t *savePointMenuCreateMenuPID(void) {
  dds3ProcessID_t *v1;
  dds3ProcessID_t *v3;
  itfMoverFunc_t v5;
  char *MenuName;
  itfMenuFunc_t v8;
  char *v10;
  itfMenuDrawFunc_t v11;
  itfMenuTextFunc_t v12;
  char *v14;
  itfMenuFunc_t v15;
  char *v17;
  itfMenuDrawFunc_t v18;
  itfMenuTextFunc_t v19;
  char *v21;
  itfMenuFunc_t v22;
  char *v24;
  itfMenuDrawFunc_t v25;
  itfMenuTextFunc_t v26;
  char *v28;
  itfMenuFunc_t v29;
  char *v31;
  itfMenuDrawFunc_t v32;
  itfMenuTextFunc_t v33;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v3 = itfMenuProcessStart();
  savePointMenuMode = 0;
  v5 = Allocate(itfMoverFunc_t);
  _ctor(v5, 0, Method_Project_itf_savePointMenuMoverFunc__, 0);
  itfMoverSetMenu(v3, v5);
  MenuName = mapIfGetMenuName(20, 0);
  v8 = Allocate(itfMenuFunc_t);
  _ctor(v8, 0, Method_Project_itf_savePointMenuDecideFunc__, 0);
  v10 = mapIfGetMenuName(20, 1);
  itfMenuSetMenu(v3, 0x10000, -1, MenuName, v8, v10);
  v11 = Allocate(itfMenuDrawFunc_t);
  _ctor(v11, 0, Method_Project_itf_savePointMenuDrawFuncMenu__, 0);
  v12 = Allocate(itfMenuTextFunc_t);
  _ctor(v12, 0, Method_Project_itf_savePointMenuPanelForUnity__, 0);
  itfMenuSetDrawFunc(v3, 0x10000, v11, v12);
  v14 = mapIfGetMenuName(21, 0);
  v15 = Allocate(itfMenuFunc_t);
  _ctor(v15, 0, Method_Project_itf_savePointMenuDecideFunc__, 0);
  v17 = mapIfGetMenuName(21, 1);
  itfMenuSetMenu(v3, 0x20000, -1, v14, v15, v17);
  v18 = Allocate(itfMenuDrawFunc_t);
  _ctor(v18, 0, Method_Project_itf_savePointMenuDrawFuncMenu__, 0);
  v19 = Allocate(itfMenuTextFunc_t);
  _ctor(v19, 0, Method_Project_itf_savePointMenuPanelForUnity__, 0);
  itfMenuSetDrawFunc(v3, 0x20000, v18, v19);
  v21 = mapIfGetMenuName(32, 0);
  v22 = Allocate(itfMenuFunc_t);
  _ctor(v22, 0, Method_Project_itf_savePointMenuDecideFunc__, 0);
  v24 = mapIfGetMenuName(32, 1);
  itfMenuSetMenu(v3, 196608, -1, v21, v22, v24);
  v25 = Allocate(itfMenuDrawFunc_t);
  _ctor(v25, 0, Method_Project_itf_savePointMenuDrawFuncMenu__, 0);
  v26 = Allocate(itfMenuTextFunc_t);
  _ctor(v26, 0, Method_Project_itf_savePointMenuPanelForUnity__, 0);
  itfMenuSetDrawFunc(v3, 196608, v25, v26);
  v28 = mapIfGetMenuName(23, 0);
  v29 = Allocate(itfMenuFunc_t);
  _ctor(v29, 0, Method_Project_itf_savePointMenuDecideFunc__, 0);
  v31 = mapIfGetMenuName(23, 1);
  itfMenuSetMenu(v3, 0x40000, -1, v28, v29, v31);
  v32 = Allocate(itfMenuDrawFunc_t);
  _ctor(v32, 0, Method_Project_itf_savePointMenuDrawFuncMenu__, 0);
  v33 = Allocate(itfMenuTextFunc_t);
  _ctor(v33, 0, Method_Project_itf_savePointMenuPanelForUnity__, 0);
  itfMenuSetDrawFunc(v3, 0x40000, v32, v33);
  itfMenuSetFlag(v3, 16, 0);
  MenuSetDispType(v3, 0, 1);
  MenuSetDispType(v3, 1, 1);
  itfMenuSetFlag(v3, 2, 0);
  itfMenuUpdateLink(v3);
  return v3;
}

// 0x1c83020
static void savePointMenuOpen(void) {
  MenuOpne(ryuketsu, 0);
  savePointMenuMode = 1;
}

// 0x1c830a0
static void savePointMenuClose(void) {
  MenuClose(ryuketsu, 0);
  savePointMenuMode = 0;
}

// 0x1c83110
static void savePointMenuPanelForUnity(s32 no, u32 color, u8 alpha, char *str, s8 attr, char *tag) {
  void *panel;
  void *setText;
  void *v18;
  void *v19;
  bool v20;
  void *v21;
  u32 v22;
  void *gameObject;
  char *v24;
  Il2CppObject *v25;
  char *v26;
  void *v27;
  void *v28;
  s32 data;

  goto LABEL_3;
LABEL_7:
  panel = ryuketsu->panel;
  if (SLODWORD(panel->max_length) <= no)
  {
    goto LABEL_10;
  }
  panel = ryuketsu->panel;
  v21 = panel[no];
  fldSetupObject(v21, 1);
LABEL_10:
  setText = ryuketsu->setText;
  if (SLODWORD(setText->max_length) <= no)
  {
    if ((attr & 2) == 0)
    {
LABEL_12:
      v18 = ryuketsu->cursor[no];
      v19 = v18;
      v20 = 0;
LABEL_40:
      fldSetupObject(v19, v20);
      return;
    }
LABEL_35:
    v28 = ryuketsu->cursor[no];
    v19 = v28;
    v20 = 1;
    goto LABEL_40;
  }
  if (color == 1692838528)
  {
    v22 = -1340416;
    goto LABEL_32;
  }
  else if (color == -1600273536)
  {
    v22 = -673588992;
    goto LABEL_32;
  }
  else
  {
    v22 = color & 0xFFFFFF00;
    goto LABEL_32;
  }
  setText = ryuketsu->setText;
LABEL_32:
  gameObject = get_gameObject(setText[no], 0);
  fldSetupObject(gameObject, 1);
  data = v22 | alpha;
  v24 = Concat_54831728("<color=#{0:X}>", str, "</color>", 0);
  v25 = Box(uint, &data);
  v26 = Format(v24, v25, 0);
  v27 = ryuketsu->setText[no];
  (v27->klass->vtable._66_set_text.methodPtr)(v27, v26, v27->klass->vtable._66_set_text.method);
  if ((attr & 2) == 0)
    goto LABEL_12;
  goto LABEL_35;
LABEL_3:
  if (savePointMenuMode)
    goto LABEL_7;
}

// 0x1c834a0
static s32 savePointMenuMoverFunc(s32 mode) {
  s32 v4;

  if (mode == 1)
  {
    MenuClose(ryuketsu, 0);
    v4 = 0;
    goto LABEL_13;
  }
  if (!mode)
  {
    MenuOpne(ryuketsu, 0);
    v4 = 1;
LABEL_13:
    savePointMenuMode = v4;
    return 1;
  }
  return 1;
}

// 0x1c835f0
static s32 savePointMenuDecideFunc(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(savePointMenu_g_mainPID);
  HIDWORD(ProcessData[2].klass) = itfMenuGetSelectID(ProcessData[1].monitor);
  return 0;
}

// 0x1c83700
static void savePointMenuDrawFuncMenu(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  char *v13;
  char **v14;
  char *v15;
  bool v17;
  char **v18;
  char *v19;

  ProcessData = dds3GetProcessData(savePointMenu_g_mainPID);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagSAVEPOINT_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagSAVEPOINT_MENU_WORK;
  if (itfMenuGetSelectID(ProcessData[3]) == a_id)
  {
    v13 = "";
    if (a_id > 0x20000)
    {
      if (a_id == 196608)
      {
        v14 = &"MAPMENUHELP_L0021";
        goto LABEL_22;
      }
      v17 = a_id == 0x40000;
      v18 = &"MAPMENUHELP_L0019";
      goto LABEL_27;
    }
    if (a_id == 0x10000)
    {
      v14 = &"MAPMENUHELP_L0017";
LABEL_22:
      v15 = *v14;
LABEL_24:
      ButtonLineHelpTextSet(v15, 0, 1, 0xA09DC380, 1);
      return;
    }
    v17 = a_id == 0x20000;
    v18 = &"MAPMENUHELP_L0018";
LABEL_27:
    v19 = *v18;
    if (v17)
      v15 = v19;
    else
      v15 = v13;
    goto LABEL_24;
  }
}

// 0x1c83970
static char *GetPointHelpID(s32 mapMenuID) {
  if (mapMenuID <= 0x20000)
  {
    if (mapMenuID == 0x10000)
    {
      return "MAPMENUHELP_L0017";
    }
    else if (mapMenuID == 0x20000)
    {
      return "MAPMENUHELP_L0018";
    }
    else
    {
      return "";
    }
  }
  else if (mapMenuID == 196608)
  {
    return "MAPMENUHELP_L0021";
  }
  else if (mapMenuID == 0x40000)
  {
    return "MAPMENUHELP_L0019";
  }
  else
  {
    return "";
  }
}

// 0x1c825f0
static void savePointMenuChkEnableDecide(tagSAVEPOINT_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v7;
  s32 nakamaMode;

  menuPID = wk->menuPID;
  itfMenuSetFlagMenu(menuPID, 0x10000, 2, 1);
  v7 = wk->menuPID;
  nakamaMode = fldGb->nakamaMode;
  itfMenuSetFlagMenu(v7, 0x20000, 2, nakamaMode == 0);
}

// 0x1c826c0
static void savePointMenuCallProcEnd(tagSAVEPOINT_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *v5;

  menuPID = wk->menuPID;
  v5 = menuPID;
  itfMenuProcessEnd(v5);
}

// 0x1c82750
static bool savePointMenuCheckProcEnd(tagSAVEPOINT_MENU_WORK *wk) {
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *menuPID;
  dds3ProcessID_t *id;

  menuPID = wk->menuPID;
  p_menuPID = &wk->menuPID;
  v5 = menuPID;
  id = v5;
  if (!v5)
    goto LABEL_17;
  if (dds3GetProcessStat(id) == 3)
    goto LABEL_17;
  if (dds3GetProcessStat(id))
    return 1;
LABEL_17:
  p_menuPID = 0;
  return 0;
}

// 0x1c829b0
static void savePointMenuRelease(tagSAVEPOINT_MENU_WORK *wk) {
  if (generalMenu_g_hSpr)
    generalMenu_g_hSpr = 0;
  wk->hSpr = 0;
}
