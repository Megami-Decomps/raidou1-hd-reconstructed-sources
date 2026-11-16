#include "types.h"
#include "MODELTYPE.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpmain.h"
#include "cmpmodel.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3areabasic.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3padmanager.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "egl.h"
#include "evtbit.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "file.h"
#include "fld.h"
#include "itf.h"
#include "kernel.h"
#include "lmap.h"
#include "localize.h"
#include "mdl.h"
#include "meslogmain.h"
#include "p2sdplay.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlevent.h"
#include "sbtlsub.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfmem.h"
#include "sdfquat.h"
#include "sdfsound.h"
#include "sdfvu0.h"
#include "slmain.h"
#include "sndat3.h"
#include "sndmanager.h"

#define DEF 2
#define SHIP 2

#define LMP_NPC_ID1_SEARCH 100
#define LMP_NPC_LABEL_LENGTH 30
#define M_LMAP_FREEMOVE 0
#define M_LMAP_CAMERA_TARGET_ADJUST 1
#define LMP_MAINPROC_NAME "lmpMainProc"
#define LMP_DRAWPROC_NAME "lmpDrawProc"
#define LMP_SPR_FILENAME "/lmap/daimap.spr"
#define LMP_TEX_MAP1NAME "/lmap/lmap01.tmx"
#define LMP_TEX_MAP2NAME "/lmap/lmap02.tmx"
#define LMP_BMD_SYS_FILE "lmp_sys.bmd"
#define LMP_BMD_SYS_FILE_KEY "lmap_sys"
#define M_LMAP_BG_W 1024
#define M_LMAP_BG_H 1024
#define M_LMAP_NPC_CB_MAX 65
#define LMAP_BGM_ID 10
#define LMP_OT_MAP 44
#define LMP_OT_MAP_TRANS 45
#define LMP_YASO_POS_X 260
#define LMP_YASO_POS_Y 6
#define LMP_YASO_POS_Z -255
#define LMAP_ACTWND_PROCNAME "lmapActWndProc"
#define LMAP_ACTWND_PROCNAME_DRAW "lmapActWndDrawProc"
#define LMAP_EFFGRID_PROCNAME "lmapEffGridProc"
#define LMAP_EFFGRID_PROCNAME_DRAW "lmapEffGridDrawProc"
#define LMAP_EFFWAVE_PROCNAME "lmapEffWaveProc"
#define LMAP_EFFWAVE_PROCNAME_DRAW "lmapEffWaveDrawProc"
#define LMAP_EFFWAVE_CB_FRONT_LENGTH_DEF 4
#define LMAP_EFFWAVE_CB_BACK_LENGTH_DEF 4
#define LMAP_EFFWAVE_CB_SIDE_LENGTH_DEF 2
#define LMAP_FLDWND_MAINPROC_NAME "lmapFldWndMainProc"
#define LMAP_FLDWND_DRAWPROC_NAME "lmapFldWndDrawProc"
#define LMAP_UTIL_DEBUG 0
#define LMPLIST_MAINPROC_NAME "lmap_list_main"
#define LMPLIST_DRAWPROC_NAME "lmap_list_draw"
#define LMPLIST_SCR_FILE "/map/map35/map35.bf"

typedef enum {
    LMAP_ACTWND_BASE_X = 256,
    LMAP_ACTWND_BASE_Y = 272,
    LMAP_ACTWND_COL = 1077952576,
    LMAP_ACTWND_MOVE_CNT = 10,
} LMAP_ACTWND;

typedef enum {
    LMAP_ACTWND_ACTTYPE_NULL = 0,
    LMAP_ACTWND_ACTTYPE_TALK = 1,
    LMAP_ACTWND_ACTTYPE_SEARCH = 2,
    LMAP_ACTWND_ACTTYPE_ENTER = 3,
    LMAP_ACTWND_ACTTYPE_TRAIN = 4,
    LMAP_ACTWND_ACTTYPE_TAKESHIP = 5,
    LMAP_ACTWND_ACTTYPE_LEFTSHIP = 6,
    LMAP_ACTWND_ACTTYPE_TUNNEL = 7,
    LMAP_ACTWND_ACTTYPE_MAX = 8,
} LMAP_ACTWND_ACTTYPE;

typedef enum {
    LMAP_LOCK_POINT_MAX = 64,
    LMAP_LOCK_LINE_MAX = 8,
} LMAP_LOCK;

typedef enum {
    LMAP_WORLD_ID_NULL = 0,
    LMAP_WORLD_ID_NORMAL = 1,
    LMAP_WORLD_ID_IKAI = 2,
    LMAP_WORLD_ID_ALL = 3,
} LMAP_WORLD_ID;

typedef enum {
    LMAP_CHR_CHARA_ID_NULL = 0,
    LMAP_CHR_CHARA_ID_PLAYER = 1,
    LMAP_CHR_CHARA_ID_DEVIL = 2,
    LMAP_CHR_CHARA_ID_ENEMY = 3,
    LMAP_CHR_CHARA_ID_NPC = 4,
} LMAP_CHR_CHARA_ID;

typedef enum {
    LMAP_CHR_MOVE_ID_NULL = 0,
    LMAP_CHR_MOVE_ID_PAD = 1,
    LMAP_CHR_MOVE_ID_PADFREE = 2,
    LMAP_CHR_MOVE_ID_SHIP = 3,
    LMAP_CHR_MOVE_ID_RANDOM = 4,
    LMAP_CHR_MOVE_ID_HOLD = 5,
    LMAP_CHR_MOVE_ID_COMPULSION = 6,
    LMAP_CHR_MOVE_ID_ROUTE = 7,
    LMAP_CHR_MOVE_ID_AUTO = 8,
    LMAP_CHR_MOVE_ID_KAYA = 9,
} LMAP_CHR_MOVE_ID;

typedef enum {
    LMAP_CHR_MOVETYPE_NONE = 0,
    LMAP_CHR_MOVETYPE_LINE = 1,
    LMAP_CHR_MOVETYPE_FREE = 2,
    LMAP_CHR_MOVETYPE_SHIP = 3,
} LMAP_CHR_MOVETYPE;

typedef enum {
    LMAP_CHR_MOVE_STAT_HOLD = 1,
    LMAP_CHR_MOVE_STAT_ENTER = 2,
    LMAP_CHR_MOVE_STAT_MESSAGE = 4,
    LMAP_CHR_MOVE_STAT_ROUTE = 8,
    LMAP_CHR_MOVE_STAT_WORLD = 16,
} LMAP_CHR_MOVE_STAT;

typedef enum {
    LMAP_CHR_MOVE_UPDATE_ERROR = -1,
    LMAP_CHR_MOVE_UPDATE_FALSE = 0,
    LMAP_CHR_MOVE_UPDATE_TRUE = 1,
    LMAP_CHR_MOVE_UPDATE_ROUTE_END = 2,
    LMAP_CHR_MOVE_UPDATE_ROUTE_ENTER = 3,
} LMAP_CHR_MOVE_UPDATE;

typedef enum {
    LMAP_CHR_ROUTE_NULL = -3,
    LMAP_CHR_ROUTE_ERROR = -2,
    LMAP_CHR_ROUTE_RUN = -1,
    LMAP_CHR_ROUTE_END = 0,
} LMAP_CHR_ROUTE;

typedef enum {
    LMAP_CHR_FLAGS_EXIST = 1,
    LMAP_CHR_FLAGS_MODEL = 2,
    LMAP_CHR_FLAGS_SETMODEL2 = 4,
    LMAP_CHR_FLAGS_PLAYER = 8,
    LMAP_CHR_FLAGS_CTRL = 16,
    LMAP_CHR_FLAGS_DASH = 32,
    LMAP_CHR_FLAGS_UNLOCK = 64,
    LMAP_CHR_FLAGS_DRAW = 128,
    LMAP_CHR_FLAGS_DRAWMODEL2 = 256,
    LMAP_CHR_FLAGS_DRAW_WORLD = 512,
    LMAP_CHR_FLAGS_LOCK = 65536,
    LMAP_CHR_FLAGS_LOCK_SET = 131072,
    LMAP_CHR_FLAGS_TALK_SET = 524288,
    LMAP_CHR_FLAGS_TALK_WAIT = 1048576,
    LMAP_CHR_FLAGS_TOUCH_PC = 2097152,
    LMAP_CHR_FLAGS_TARGET_BASE = 134217728,
    LMAP_CHR_FLAGS_TARGET_NEXT = 268435456,
    LMAP_CHR_FLAGS_AREA_BASE = 536870912,
    LMAP_CHR_FLAGS_AREA_NEXT = 1073741824,
    LMAP_CHR_FLAGS_TOUCH = -2147483648,
} LMAP_CHR_FLAGS;

typedef enum {
    LMP_MODEL_FLAGS_EXIST = 1,
    LMP_MODEL_FLAGS_SETOBJ = 2,
    LMP_MODEL_FLAGS_DRAW = 4,
    LMP_MODEL_FLAGS_LINK = 8,
} LMP_MODEL_FLAGS;

typedef enum {
    LMAP_EFFGRID_GRID_SIZE = 32,
    LMAP_EFFGRID_GRID_NUM_X = 16,
    LMAP_EFFGRID_GRID_NUM_Y = 14,
    LMAP_EFFGRID_CB_MAX = 224,
    LMAP_EFFGRID_PROC_CNT = 32,
    LMAP_EFFGRID_MOVE_CNT = 28,
    LMAP_EFFGRID_WAIT_CNT = 4,
    LMAP_EFFGRID_CHECKWAIT_CNT = 8,
    LMAP_EFFGRID_GRID_COL = 15790320,
    LMAP_EFFGRID_UNIT_ALPHA = 4,
} LMAP_EFFGRID;

typedef enum {
    FIELD_MAX = 38,
    STATION_MAX = 7,
    PORT_MAX = 22,
    ROUTE_POINT_MAX = 10,
} LMAP;

typedef enum {
    LMP_POINT_DAT_FLAG_FIELD = 1,
    LMP_POINT_DAT_FLAG_STATION = 2,
    LMP_POINT_DAT_FLAG_PORT = 4,
    LMP_POINT_DAT_FLAG_AUTO = 8,
} LMP_POINT_DAT_FLAG;

typedef enum {
    DISAPPEAR = 900,
    ROUTE_WARP = 901,
    ROUTE_FADE = 902,
} LMP_LINENO;

typedef enum {
    M_LMAP_LINE_TYPE_NULL = -1,
    M_LMAP_LINE_TYPE_NORMAL = 0,
    M_LMAP_LINE_TYPE_TRAIN = 1,
    M_LMAP_LINE_TYPE_AUTOMOVE = 2,
    M_LMAP_LINE_TYPE_MAX = 3,
} M_LMAP_LINE_TYPE;

typedef enum {
    LMAP_ROUTE_TYPE_NULL = 0,
    LMAP_ROUTE_TYPE_WAIT = 1,
    LMAP_ROUTE_TYPE_LOCK = 2,
    LMAP_ROUTE_TYPE_ENTER = 3,
} LMAP_ROUTE_TYPE;

typedef enum {
    LMAP_ROUTE_STAT_WAIT = 1,
    LMAP_ROUTE_STAT_DASH = 2,
    LMAP_ROUTE_STAT_TRAIN = 4,
} LMAP_ROUTE_STAT;

typedef enum {
    LMP_FLDID_NONE = 0,
    LMP_FLDID_TUKUDO = 1,
    LMP_FLDID_DAIDOUJI = 2,
} LMP_FLDID;

typedef enum {
    LMP_MAPID_NONE = 0,
    LMP_MAPID_TOKYO = 1,
    LMP_MAPID_SINODA = 2,
} LMP_MAPID;

typedef enum {
    LMP_SYS_EITHER = 0,
    LMP_SYS_ENTER_CONF = 1,
    LMP_SYS_STATION_CONF = 2,
    LMP_SYS_N_ENTER = 3,
    LMP_SYS_USE_SHIPITEM = 4,
    LMP_SYS_USE_SHIPITEM2 = 5,
    LMP_SYS_TALK_SHIP = 6,
} LMP_SYS;

typedef enum {
    LMPLIST_TYPE_NONE = 0,
    LMPLIST_TYPE_STATION = 1,
    LMPLIST_TYPE_NUM = 2,
} LMPLIST_TYPE;

typedef enum {
    LMPLIST_ID_STAT_NONE = -1,
    LMPLIST_ID_STAT_YARAI = 0,
    LMPLIST_ID_STAT_HONGOU = 1,
    LMPLIST_ID_STAT_SENJYU = 2,
    LMPLIST_ID_STAT_TYUUJYOU = 3,
    LMPLIST_ID_STAT_KOUTOU = 4,
    LMPLIST_ID_STAT_AKASAKA = 5,
    LMPLIST_ID_STAT_SHINODA = 6,
    LMPLIST_ID_STAT_NUM = 7,
} LMPLIST_ID_STAT;

typedef enum {
    LMP_LF_RELEASE = 1,
    LMP_LF_DRAW = 2,
    LMP_LF_DRAW_PANEL = 4,
    LMP_LF_AUTOMODE = 8,
    LMP_GF_PAD_SET = 16,
    LMP_GF_PAD_ENABLE = 32,
    LMP_GF_DRAW_DEBUG = 64,
    LMP_GF_DEBUG = 128,
} LMP;

typedef enum {
    LMP_WARP_FLAG_OFF = 0,
    LMP_WARP_FLAG_ON = 1,
} LMP_WARP_FLAG;

typedef enum {
    M_LMAP_STATE_MUSIC_NOP = 0,
    M_LMAP_STATE_MUSIC_LOAD = 1,
    M_LMAP_STATE_MUSIC_LOAD_WAIT = 2,
    M_LMAP_STATE_MUSIC_PLAY = 3,
    M_LMAP_STATE_MUSIC_PLAY_WAIT = 4,
} M_LMAP_STATE_MUSIC;

typedef enum {
    LMAP_EFFGRID_STEP_NULL = 0,
    LMAP_EFFGRID_STEP_SET = 1,
    LMAP_EFFGRID_STEP_UPDATE = 2,
    LMAP_EFFGRID_STEP_CHECK = 3,
    LMAP_EFFGRID_STEP_WAIT = 4,
    LMAP_EFFGRID_STEP_END = 5,
} LMAP_EFFGRID_STEP;

typedef enum {
    LMAP_EFFWAVE_CB_MAX = 32,
    LMAP_EFFWAVE_CB_ALPHA_MAX = 128,
    LMAP_EFFWAVE_CB_COL_TOP = 16777215,
    LMAP_EFFWAVE_CB_COL_BTM = 16639,
    LMAP_EFFWAVE_CB_COL2_TOP = 16777215,
    LMAP_EFFWAVE_CB_COL2_BTM = 16744576,
} LMAP_EFFWAVE_CB;

typedef enum {
    TEX_NUM = 17,
    DISP_CNT = 10,
} LMAP_FLDWND;

typedef enum {
    LMAP_FLDWND_STAT_RELEASE = 1,
    LMAP_FLDWND_STAT_DRAW = 2,
    LMAP_FLDWND_STAT_CALL_START = 4,
    LMAP_FLDWND_STAT_CALL_END = 8,
} LMAP_FLDWND_STAT;

typedef enum {
    STATION_ID_TSUKUDO = 0,
    STATION_ID_HONGO = 1,
    STATION_ID_HUKAGAWA = 2,
    STATION_ID_GINZA = 3,
    STATION_ID_HARUMI = 4,
    STATION_ID_KASUMIDAI = 5,
    STATION_ID_SHINODA = 6,
    STATION_ID_TARASUKU = 7,
    STATION_ID_NONE = -1,
} STATION_ID;

typedef enum {
    LMPLIST_MNY_X = 266,
    LMPLIST_MNY_Y = 24,
    LMPLIST_TTL_X = 123,
    LMPLIST_TTL_Y = 87,
    LMPLIST_LST_X = 132,
    LMPLIST_LST_Y = 135,
} LMPLIST;

typedef enum {
    LMPLIST_STEP_WAIT = 0,
    LMPLIST_STEP_MAIN = 1,
    LMPLIST_STEP_CONF = 2,
    LMPLIST_STEP_CALL_COUNT = 3,
    LMPLIST_STEP_WAIT_COUNT = 4,
    LMPLIST_STEP_CALL_DISP = 5,
    LMPLIST_STEP_WAIT_DISP = 6,
    LMPLIST_STEP_WAIT_SCRIPT = 7,
    LMPLIST_STEP_LOAN_CHECK = 8,
    LMPLIST_STEP_LOAN_CALL_SCRIPT = 9,
    LMPLIST_STEP_LOAN_WAIT_SCRIPT = 10,
    LMPLIST_STEP_LOAN_FADEIN = 11,
    LMPLIST_STEP_LOAN_FADEIN_WAIT = 12,
    LMPLIST_STEP_LOAN_CALL_COUNT = 13,
    LMPLIST_STEP_LOAN_WAIT_COUNT = 14,
    LMPLIST_STEP_LOAN_FADEOUT_WAIT = 15,
    LMPLIST_STEP_LOAN_FADEOUT = 16,
    LMPLIST_STEP_RELEASE = 17,
    LMPLIST_STEP_END = 18,
} LMPLIST_STEP;

typedef enum {
    LMPLIST_F_RELEASE = 1,
    LMPLIST_F_LINK_SPR = 2,
    LMPLIST_F_CALL_START = 4,
    LMPLIST_F_N_FARE = 8,
    LMPLIST_F_FREE = 16,
} LMPLIST_F;

typedef enum {
    STATION_TSUKUDO = 0,
    STATION_HONGO = 1,
    STATION_FUKA = 2,
    STATION_GIN = 3,
    STATION_HARU = 4,
    STATION_KASU = 5,
    STATION_SINODA = 6,
} STATION;

typedef struct ExitArea_t ExitArea_t;
typedef struct FontReq_t FontReq_t;
typedef struct LineDat_t LineDat_t;
typedef struct Npc_t Npc_t;
typedef struct PointDat_t PointDat_t;
typedef struct RouteDat_t RouteDat_t;
typedef struct Warp_t Warp_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfMover_t itfMover_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagLMAP_ACTWND_CB tagLMAP_ACTWND_CB;
typedef struct tagLMAP_ACTWND_WORK tagLMAP_ACTWND_WORK;
typedef struct tagLMAP_CHR_WORK tagLMAP_CHR_WORK;
typedef struct tagLMAP_EFFGRID_CB tagLMAP_EFFGRID_CB;
typedef struct tagLMAP_EFFGRID_WORK tagLMAP_EFFGRID_WORK;
typedef struct tagLMAP_EFFWAVE_CB tagLMAP_EFFWAVE_CB;
typedef struct tagLMAP_EFFWAVE_WORK tagLMAP_EFFWAVE_WORK;
typedef struct tagLMAP_FLDWND_WORK tagLMAP_FLDWND_WORK;
typedef struct tagLMAP_LINE_DAT tagLMAP_LINE_DAT;
typedef struct tagLMAP_LIST_WORK tagLMAP_LIST_WORK;
typedef struct tagLMAP_LOCK_WORK tagLMAP_LOCK_WORK;
typedef struct tagLMAP_NPC_CB tagLMAP_NPC_CB;
typedef struct tagLMP_COASTLINE_DAT tagLMP_COASTLINE_DAT;
typedef struct tagLMP_MODEL_WK tagLMP_MODEL_WK;
typedef struct tagM_LMAP_WORK tagM_LMAP_WORK;

typedef bool (*ListMakeListFunc_t)(tagLMAP_LIST_WORK *wk);

struct tagLMAP_ACTWND_CB {
    f32 x[3];
    f32 y[3];
    f32 w[3];
    f32 h[3];
};

struct tagLMAP_ACTWND_WORK {
    dds3ProcessID_t *proc_draw;
    FontReq_t *fr_act;
    u8 step;
    s8 type;
    s8 cnt;
    s8 pad8;
    f32 fnt_x;
    f32 fnt_w;
    tagLMAP_ACTWND_CB *cb[2];
};

struct tagLMAP_EFFGRID_CB {
    s8 cnt[2];
    s8 alpha;
    s8 pad8;
    f32 pos_x;
    f32 pos_y;
    f32 vec_x;
    f32 vec_y;
};

struct tagLMAP_EFFGRID_WORK {
    dds3ProcessID_t *proc_draw;
    s8 step;
    s8 type;
    s16 cnt;
    tagLMAP_EFFGRID_CB *cb[224];
};

struct PointDat_t {
    s16 no;
    s16 x;
    s16 y;
    s8 id;
    u8 flag;
};

struct LineDat_t {
    s16 line_no;
    s16 point_no0;
    s16 point_no1;
    s8 line_type;
    s8 area_no;
};

struct RouteDat_t {
    s16 pointNo[10];
    s16 relay;
    s8 type;
    u8 stat;
};

struct Warp_t {
    s32 tgtMapID;
    s32 movMapID;
    u16 flag1;
    u16 flag2;
    s8 drawThumbnail;
    s8 scrType;
    char *scrLabel;
    LMP_WARP_FLAG flag1chk;
    LMP_WARP_FLAG flag2chk;
};

struct ExitArea_t {
    s32 iMap;
    f32 fLeft;
    f32 fRight;
    f32 fTop;
    f32 fBottom;
};

struct tagLMAP_EFFWAVE_CB {
    sdfVector4_t pos;
    sdfVector4_t vec;
    f32 y0;
    f32 y1;
    s8 max_cnt0;
    s8 max_cnt1;
    s8 cnt;
    s8 prev;
    s8 next;
    bool flg;
    s8 pad8[2];
};

struct tagLMAP_EFFWAVE_WORK {
    tagLMAP_EFFWAVE_CB *cb[32];
    dds3ProcessID_t *drawPID;
    f32 front_length;
    f32 back_length;
    f32 side_length;
    s32 color_type;
};

struct tagLMAP_FLDWND_WORK {
    dds3ProcessID_t *drawPID;
    sprHandle_t *hSpr;
    itfMover_t *mover;
    s32 fieldNo;
    f32 fx;
    f32 fy;
    s8 step;
    s8 stat;
    s16 cnt;
    s32 fileNo;
};

struct tagLMAP_LINE_DAT {
    s16 line_no;
    s16 point_no0;
    s16 point_no1;
    s8 line_type;
    s8 area_no;
};

struct tagLMP_COASTLINE_DAT {
    s16 x;
    s16 y;
    s32 flag;
};

struct tagLMAP_LIST_WORK {
    dds3ProcessID_t *drawPID;
    sprHandle_t *hSpr;
    dds3ProcessID_t *listPID;
    dds3ProcessID_t *countPID;
    void *pDatScr;
    dds3ProcessID_t *scrPID;
    char *scrLabel;
    s8 type;
    s8 point;
    s8 flag;
    s8 step;
    s32 selectID;
    s32 count;
    s32 money;
};

f32 LMAP_PAD_ANALOG_MASK;
f32 LMAP_CHR_MODEL_DEF_SIZE;
f32 LMAP_CHR_AREA_LENGTH;
f32 LMAP_CHR_CHARA_LENGTH;
f32 LMAP_CHR_ROUTE_MOVE_LENGTH;
f32 LMAP_CHR_TRAIN_MOVE_LENGTH;
f32 LMAP_CHR_PORT_LENGTH;
static Npc_t *gLmpNpc;
void *LmapCameraPar;
dds3ProcessID_t *fclID;
s32 gLMapCampMcLoadEnd;
static s32 sisetu_wait;
bool CallCampFromLmap;
bool CallFastTravelFromLmap;
void *lmapJmpDataTbls;
tagM_LMAP_WORK *lmapwk;
bool MenuFlag;
bool TaraCtrlFlag;
static dds3ProcessID_t *g_mainPID_Lmap;
static char *lmap_areaname;
static char *FldWndName;
static char *szLmpActwin;
static bool g_bStartTakeShip;
static Warp_t *arrLmpWarp;
static s32 Process_count;
static f32 M_MoveMap_v_length;
static f32 M_MoveMap_t_length;
static s16 CtrlActionWindow_fieldNo;
static s32 UpdateAutoMove_moveFrame;
static s32 UpdateAutoMove_tgtPointNo;
static s32 UpdateAutoMove_tgtID;
static u8 UpdateAutoMove_tgtFlag;
static s32 gSoundSmgLoadId;
static s32 gSoundSmgLoadPhase;
static bool isLoaded;
static void *goLmapManager;
bool DestUpdateFlag;
void *DestOldList;
void *DestUpdate;
void *DestNowList;
void *DestListTbl;
void *DestTextList;
void *DestNowChapter;
static void *ndWork;
static char *fieldUIname;
static char *akey_Lmap;
static char *akey_LmapBack;
static sdfVector4_t mov;
static sdfVector4_t tgt;
static char *lmap_actionword;
static f32 LMAP_CHR_MODEL_TRAIN_SCALE;
static f32 LMAP_CHR_MODEL_TRAIN_OFSLENGTH;
static f32 LMAP_CHR_MODEL_SHIP_SCALE;
static f32 LMAP_CHR_MODEL_SHIP_OFSY;
static f32 LMAP_PAD_ANALOG_MASK_SHIP;
static s16 Chr_UpdatePosition_fade;
static s16 Chr_UpdatePosition_line;
static s8 Chr_UpdatePadTrain_ret;
static bool Chr_UpdatePosShip_chk_msg;
static bool Chr_UpdatePosShip_chk_se;
static bool Chr_UpdateMoveShip_chk_msg;
static bool Chr_UpdateMoveShip_chk_se;
static void *waveMesh;
u8 CNT;
static dds3ProcessID_t *g_mainPID_FLDWND;
static void *fwWork;
static s16 **lmap_tbl_mapid;
static s16 **lmap_arrPointStation;
static PointDat_t *lmap_tbl_point;
static LineDat_t *lmap_tbl_line;
static tagLMP_COASTLINE_DAT *lmpCoastlineDat;
static RouteDat_t *lmap_tbl_route;
static dds3ProcessID_t *g_mainPID_LmpList;
char *strSystem;
char *strStation;
u16 *arrStFlag;
static s16 **arrRailroadFare;
static itfSprList_t *arrSprListMoney;
static itfSprList_t *arrSprListTitle;
static itfSprList_t *arrSprListPanel;
static itfSprList_t *arrSprListSelect;
static ListMakeListFunc_t *ListMakeListFunc;

static s16 dmLMAP_POINT_NO(s32 no);
static s16 dmLMAP_POINT_X(s32 no);
static s16 dmLMAP_POINT_Y(s32 no);
static s16 dmLMAP_POINT_ID(s32 no);
static s16 dmLMAP_POINT_FLAG(s32 no);
static s16 dmLMAP_LINE_NO(s32 no);
static s16 dmLMAP_LINE_POINT_A(s32 no);
static s16 dmLMAP_LINE_POINT_B(s32 no);
static s16 dmLMAP_LINE_TYPE(s32 no);
static s16 dmLMAP_LINE_AREA(s32 no);
static s16 dmLMAP_ROUTE_POINT(s32 no, s32 type);
static s16 dmLMAP_ROUTE_RELAY(s32 no);
static s16 dmLMAP_ROUTE_TYPE(s32 no);
static s16 dmLMAP_ROUTE_STAT(s32 no);
static bool IsDestDisp(void);
static void ndWorkActive(bool _active);
static void ButtonGuideOn(void);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *proc);
static void Initialize(void);
static dds3ProcessFunc_t Process(dds3ProcessID_t *id);
static void Release(void);
static void Shutdown(dds3ProcessID_t *id);
static void M_FreeTex(void);
static s32 MskR1Task(void);
static void M_DrawBG(void);
static void M_InitScene(void);
static void M_DeleteScene(void);
static void M_InitCamera(void);
static void M_UpdateCamera(void);
static void M_InitLight(void);
static s32 M_MoveMap(s32 mode);
static s8 CtrlActionWindow(void);
static bool SetNpcDat(void);
static bool M_SetLockPointNpcCB(s8 charaNo, bool lockFlg);
static void M_MainNpcCB(void);
static void SetAreaName(s32 linetblno);
static void DrawActWin(s32 a_type, f32 a_fx, f32 a_fy, f32 a_fz);
static s32 UpdateAutoMove(void);
static void CallField(void);
static void SoundSmgLoad(s32 map);
static s32 SoundSmgLoadChk(void);
static bool SetPadEnable(bool a_bFlag);
static bool SetFlagDebug(bool a_bFlag);
static void LoadNpcFile(void);
static s32 ChkWarp(s32 a_chkMapID);
static void Start(s32 aFieldNo);
static void ShutDown(void);
static void LoadFile(void);
static void GetCameraBasePos(sdfVector4_t *pos1, const sdfVector4_t *pos0);
static void SetPanel(s8 actType, s8 fldType, s8 tblNo);
static void SetPanel_2(bool a_bField, s16 a_touchAreaType, u8 a_pointFlag);
static void ResetPanel(bool a_bField);
static void ResetPanelSub(void);
static s32 GetNearStation(void);
static void SetMessage(void);
static bool SetNpcCB(s8 a_charNo, Npc_t *a_pTbl);
static void M_UpdateNpcCB(tagLMAP_NPC_CB *p_cb);
static void M_UpdateKaya(tagLMAP_CHR_WORK *kaya);
static void DrawTexActWin(f32 fx, f32 fy, s32 w);
static void DrawFntActWin(f32 fx, f32 fy, u32 abgr, char *str);
static s32 NpcDelete(void);
static s32 NpcMoveRoute(s32 a_routeNo);
static void ActWnd_InitCB(tagLMAP_ACTWND_CB *p_cb);
static void ActWnd_SetCB(tagLMAP_ACTWND_CB *p_cb, s32 no, f32 x, f32 y, f32 w, f32 h);
static bool ActWnd_Set(dds3ProcessID_t *proc, s8 type);
static void ActWnd_UpdateCB(tagLMAP_ACTWND_CB *p_cb, bool endflg);
static void ActWnd_DrawCB(tagLMAP_ACTWND_CB *p_cb);
static void ActWnd_Init(dds3ProcessID_t *proc);
static dds3ProcessFunc_t ActWnd_Main(dds3ProcessID_t *proc);
static dds3ProcessFunc_t ActWnd_Draw(dds3ProcessID_t *proc);
static void ActWnd_Reset(dds3ProcessID_t *proc);
static dds3ProcessFunc_t ActWnd_DrawProcess(dds3ProcessID_t *proc);
static void ActWnd_Initialize(dds3ProcessID_t *proc);
static dds3ProcessFunc_t ActWnd_Process(dds3ProcessID_t *proc);
static void ActWnd_Shutdown(dds3ProcessID_t *proc);
static dds3ProcessID_t *ActWnd_Start(void);
static void ActWnd_ReleaseDraw(dds3ProcessID_t *proc);
static void ActWnd_Release(dds3ProcessID_t *proc);
static void ActWnd_Finish(dds3ProcessID_t *proc);
static void MdlDelete(tagLMP_MODEL_WK *wk);
static void MdlCreate(tagLMP_MODEL_WK *wk, MODELTYPE a_majorNo, LMAP_CHR_MODEL_MINOR a_minorNo, f32 a_scaleDef);
static void MdlSetDraw(tagLMP_MODEL_WK *wk, bool a_bDraw);
static void MdlSetLink(tagLMP_MODEL_WK *wk, bool a_bLink);
static void MdlSetOfsY(tagLMP_MODEL_WK *wk, f32 a_ofsY);
static void MdlSetOfsLength(tagLMP_MODEL_WK *wk, f32 a_ofsLength);
static void MdlSetTrain(tagLMP_MODEL_WK *wk);
static void MdlSetShip(tagLMP_MODEL_WK *wk);
static void MdlUpdate(tagLMP_MODEL_WK *wk);
static bool MdlGetDraw(tagLMP_MODEL_WK *wk);
static bool ChrGetDrawVehicle(tagLMAP_CHR_WORK *wk);
static bool Chr_SetScaleModel(tagLMAP_CHR_WORK *wk, s16 a_mode, s16 a_frame);
static s8 Chr_UpdateScaleModel(tagLMAP_CHR_WORK *wk);
static void ChrSetModel(tagLMAP_CHR_WORK *wk, MODELTYPE a_majorNo, LMAP_CHR_MODEL_MINOR a_minorNo);
static void Chr_UpdateModel(tagLMAP_CHR_WORK *wk);
static bool Chr_SetParam(tagLMAP_CHR_WORK *wk, s8 charaId, s8 charaNo, s8 worldId, s8 moveId, s8 moveNo, s16 pointNo);
static bool _Chr_SetPlayer(tagLMAP_CHR_WORK *wk, s8 moveNo, s16 pointNo);
static bool _Chr_SetKaya(tagLMAP_CHR_WORK *wk, s8 moveNo, s16 pointNo);
static bool _Chr_SetKaya_Load(tagLMAP_CHR_WORK *wk);
static bool _Chr_SetPlayer_Load(tagLMAP_CHR_WORK *wk);
static bool Chr_SetPlayer(tagLMAP_CHR_WORK *wk, s16 pointNo);
static bool Chr_SetPlayerRoute(tagLMAP_CHR_WORK *wk, s8 moveNo, s16 pointNo);
static bool ChrSetNpc(tagLMAP_CHR_WORK *wk, s8 a_charNo, s16 a_pointNo, MODELTYPE a_majorNo, LMAP_CHR_MODEL_MINOR a_minorNo, f32 a_scale);
static bool Chr_UpdateLineData(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk);
static void ChrCalcLineVector(tagLMAP_CHR_WORK *chrwk);
static void ChrCalcDegree(tagLMAP_CHR_WORK *wk, bool a_bDirect);
static void Chr_SetBasePointNo(tagLMAP_CHR_WORK *chrwk, s16 a_tblno);
static void Chr_SetLinePoint(tagLMAP_CHR_WORK *chrwk, s16 a_tgtPointNo);
static s8 Chr_CalcPosition(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk);
static s8 Chr_UpdatePosFreePad(tagLMAP_CHR_WORK *wk);
static s8 check_point_line(const sdfVector2_t *a, const sdfVector2_t *b, const sdfVector2_t *c);
static s8 check_cross_line2(const sdfVector2_t *a1, const sdfVector2_t *a2, const sdfVector2_t *b1, const sdfVector2_t *b2);
static s8 Chr_UpdatePosShipPad(tagLMAP_CHR_WORK *wk, tagLMAP_LOCK_WORK *lockwk);
static s8 Chr_UpdatePosition(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk);
static void Chr_UpdatePadRandom(tagLMAP_CHR_WORK *wk);
static f32 ChrRouteCalcPadParam(s32 pt0, s32 pt1);
static s8 _Chr_UpdatePadRoute(tagLMAP_CHR_WORK *chrwk);
static s8 Chr_UpdatePadRoute(tagLMAP_CHR_WORK *chrwk);
static s8 Chr_UpdatePadTrain(tagLMAP_CHR_WORK *chrwk);
static s16 _Chr_GetExLineDat(s16 checkPointNo, s16 checkType);
static s16 Chr_GetExLineDat(tagLMAP_CHR_WORK *chrwk, s16 checkType);
static s16 Chr_GetExLineType(tagLMAP_CHR_WORK *chrwk);
static s16 Chr_GetExLineBase(tagLMAP_CHR_WORK *chrwk);
static s16 Chr_GetExLineNext(tagLMAP_CHR_WORK *chrwk);
static bool Chr_UpdatePosTrain(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk);
static bool Chr_UpdatePosShip(tagLMAP_CHR_WORK *chrwk);
static bool Chr_UpdatePosAuto(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk);
static void Kaya_UpdatePosAuto(tagLMAP_CHR_WORK *chrwk);
static s8 Chr_UpdateMove(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk);
static s16 Chr_GetNearPortTableNo(tagLMAP_CHR_WORK *chrwk);
static void Chr_SetNearPortPos(tagLMAP_CHR_WORK *chrwk);
static bool Lock_SetPointNo(tagLMAP_LOCK_WORK *wk, s16 lockPointNo, bool lockFlg);
static bool Lock_SetLineNo(tagLMAP_LOCK_WORK *wk, s16 lockLineNo, bool lockFlg);
static bool Lock_SetPointChr(tagLMAP_LOCK_WORK *lockwk, tagLMAP_CHR_WORK *chrwk, bool lockFlg);
static void EffGrid_Release(dds3ProcessID_t *proc);
static void EffGrid_InitCB(tagLMAP_EFFGRID_CB *p_cb);
static void EffGrid_InitCBAll(dds3ProcessID_t *proc);
static void EffGrid_SetCB(tagLMAP_EFFGRID_CB *p_cb, s32 no, s8 type);
static void EffGrid_SetCBAll(dds3ProcessID_t *proc);
static void EffGrid_UpdateCBMove(tagLMAP_EFFGRID_CB *p_cb);
static void EffGrid_UpdateCBHold(tagLMAP_EFFGRID_CB *p_cb, s32 no);
static void EffGrid_UpdateCB(tagLMAP_EFFGRID_CB *p_cb, s32 no, s8 type);
static void EffGrid_UpdateCBAll(dds3ProcessID_t *proc);
static void EffGrid_DrawCB(tagLMAP_EFFGRID_CB *p_cb);
static void EffGrid_DrawCBAll(dds3ProcessID_t *proc);
static bool EffGrid_CheckWait(dds3ProcessID_t *proc);
static void EffGrid_Init(dds3ProcessID_t *proc);
static dds3ProcessFunc_t EffGrid_Main(dds3ProcessID_t *proc);
static dds3ProcessFunc_t EffGrid_Draw(dds3ProcessID_t *proc);
static dds3ProcessFunc_t EffGrid_DrawProcess(dds3ProcessID_t *proc);
static void EffGrid_Initialize(dds3ProcessID_t *proc);
static dds3ProcessFunc_t EffGrid_Process(dds3ProcessID_t *proc);
static void EffGrid_Shutdown(dds3ProcessID_t *proc);
static dds3ProcessID_t *EffGrid_Start(void);
static void EffGrid_ReleaseDraw(void);
static void EffGrid_Finish(dds3ProcessID_t *proc);
static void EffWave_InitCB(tagLMAP_EFFWAVE_CB *p_cb);
static void EffWave_ResetLink(dds3ProcessID_t *proc);
static void EffWave_SetData(dds3ProcessID_t *proc, const sdfVector4_t *a_pos, const sdfVector4_t *a_vec);
static void EffWave_SetColorType(dds3ProcessID_t *proc, s32 a_type);
static void EffWave_UpdateCB(tagLMAP_EFFWAVE_CB *p_cb, s32 num);
static void EffWave_DrawCB(dds3ProcessID_t *proc, s32 no);
static void EffWave_Init(dds3ProcessID_t *proc);
static dds3ProcessFunc_t EffWave_Process(dds3ProcessID_t *proc);
static void EffWave_Draw(dds3ProcessID_t *proc);
static void EffWave_Shutdown(dds3ProcessID_t *proc);
static dds3ProcessID_t *EffWave_Start(void);
static void EffWave_Finish(dds3ProcessID_t *proc);
static void FldWnd_LoadTexMem(tagLMAP_FLDWND_WORK *wk);
static void FldWnd_LoadTexHnd(tagLMAP_FLDWND_WORK *wk);
static void FldWnd_CallStart(tagLMAP_FLDWND_WORK *wk);
static void _FldWnd_CallEnd(tagLMAP_FLDWND_WORK *wk);
static dds3ProcessFunc_t FldWnd_Process(dds3ProcessID_t *PID);
static void FldWnd_DrawThumbnail(tagLMAP_FLDWND_WORK *wk);
static dds3ProcessFunc_t FldWnd_DrawProcess(dds3ProcessID_t *PID);
static bool FldWnd_Start(s32 a_fieldNo, const sdfVector4_t *a_pos);
static void FldWnd_CallEnd(void);
static void FldWnd_Reset(void);
static void FldWnd_LinkSprite(sprHandle_t *a_hSpr);
static void FldWnd_SetFlagDraw(bool a_bDraw);
static void FldWnd_Release(tagLMAP_FLDWND_WORK *wk);
static void FldWnd_Shutdown(dds3ProcessID_t *PID);
static void FldWnd_ProcessStart(void);
static void FldWnd_ProcessEnd(void);
static void DrawFldThumbnail(s32 index, f32 x, f32 y, f32 alpha);
static void ClearFldThumbnail(void);
static s16 MapDat_GetPointDat(s32 list_no, s32 type);
static s16 MapDat_GetLineDat(s32 list_no, s32 type);
static s16 MapDat_GetRouteDat(s32 list_no, s32 type);
static s16 MapDat_GetPointTableNo(s16 pointNo);
static s16 MapDat_GetPointID(s16 pointNo);
static u8 MapDat_GetPointFlag(s16 pointNo);
static bool MapDat_GetPointXY(s16 pointNo, f32 *x, f32 *y);
static s8 MapDat_ChkCoastlineDat(s16 a_no);
static void MapDat_GetCoastlineDat(s16 *a_pDat, s16 a_no, s16 a_type);
static s16 MapDat_GetPointStation(s16 a_pointNo);
static void Util_Point3To2(f32 x3, f32 y3, f32 z3, f32 *x2, f32 *y2);
static bool Util_GetPadAnalog(sdfVector4_t *p_pad, f32 *p_length, f32 min);
static s32 UtilFloatToSdf32s(f32 a_fnum, s32 a_shift);
static void Util_GetVerticalVector(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *posp);
static void Util_GetVerticalVector2(const sdfVector4_t *vec, const sdfVector4_t *pos0, const sdfVector4_t *posp);
static void Util_GetVerticalPosition(const sdfVector4_t *vec, const sdfVector4_t *pos, f32 length);
static f32 Util_CalcLength(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *posp);
static bool Util_GetMovePosition(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *vec, f32 rate, f32 length);
static bool ListMakeListDummy(tagLMAP_LIST_WORK *wk);
static s32 ListDecideStation(void);
static void ListDrawStation(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static bool ListChkUseStation(tagLMAP_LIST_WORK *wk);
static bool ListMakeListStation(tagLMAP_LIST_WORK *wk);
static bool ListMakeList(tagLMAP_LIST_WORK *wk);
static void ListCallProcEnd(tagLMAP_LIST_WORK *wk);
static s8 ListCheckProcEnd(tagLMAP_LIST_WORK *wk);
static dds3ProcessFunc_t ListProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t ListDrawProcess(dds3ProcessID_t *PID);
static bool ListLoadSprite(s8 a_str);
static bool ListLinkSprite(sprHandle_t *a_hSpr);
static bool ListLinkScriptDat(void *a_pDat);
static void ListStart(s32 a_type, s32 a_point);
static bool ListCheckWait(void);
static s32 ListGetSelectID(void);
static void ListSetFlagFocus(bool bFocus);
static void ListSetFlagDisp(bool bDisp);
static bool ListChkGetFreePass(void);
static s32 ListGetFare(s32 a_point0, s32 a_point1);
static s32 ListGetFareJimusyo(s32 a_map);
static void ListRelease(tagLMAP_LIST_WORK *wk);
static void ListShutdown(dds3ProcessID_t *PID);
static void ListInit(tagLMAP_LIST_WORK *wk);
static void ListProcessStart(void);
static void ListProcessEnd(void);
static bool ListProcessCheck(void);
s32 mapFastTravel(s32 type, s32 idx);
void lmapStationStopDestCheck(void);

// macros
// 0x1cb4730: bool LMAP_CHR_FLAGS_DRAW_CHECK(u32 _flags)
#define LMAP_CHR_FLAGS_DRAW_CHECK(_flags) ((~flags & 0x280) == 0)

// 0x1cb7190: s32 SET_BTL_DEST(void)
static inline s32 SET_BTL_DEST(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  lmapSetBattleDestFlag(IntPara);
  return 1;
}

// 0x1cb4740
static s16 dmLMAP_POINT_NO(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_point->max_length) <= no)
    return 0;
  return lmap_tbl_point[no]->no;
}

// 0x1cb4a30
static s16 dmLMAP_POINT_X(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_point->max_length) <= no)
    return 0;
  return lmap_tbl_point[no]->x;
}

// 0x1cb4b60
static s16 dmLMAP_POINT_Y(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_point->max_length) <= no)
    return 0;
  return lmap_tbl_point[no]->y;
}

// 0x1cb4c90
static s16 dmLMAP_POINT_ID(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_point->max_length) <= no)
    return 0;
  return lmap_tbl_point[no]->id;
}

// 0x1cb4dc0
static s16 dmLMAP_POINT_FLAG(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_point->max_length) <= no)
    return 0;
  return lmap_tbl_point[no]->flag;
}

// 0x1cb4ef0
static s16 dmLMAP_LINE_NO(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_line->max_length) <= no)
    return 0;
  return lmap_tbl_line[no]->line_no;
}

// 0x1cb51e0
static s16 dmLMAP_LINE_POINT_A(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_line->max_length) <= no)
    return 0;
  return lmap_tbl_line[no]->point_no0;
}

// 0x1cb5310
static s16 dmLMAP_LINE_POINT_B(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_line->max_length) <= no)
    return 0;
  return lmap_tbl_line[no]->point_no1;
}

// 0x1cb5440
static s16 dmLMAP_LINE_TYPE(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_line->max_length) <= no)
    return 0;
  return lmap_tbl_line[no]->line_type;
}

// 0x1cb5570
static s16 dmLMAP_LINE_AREA(s32 no) {
  if ((no & 0x80000000) != 0)
    return 0;
  if (SLODWORD(lmap_tbl_line->max_length) <= no)
    return 0;
  return lmap_tbl_line[no]->area_no;
}

// 0x1cb56a0
static s16 dmLMAP_ROUTE_POINT(s32 no, s32 type) {
  s32 v6;
  s32 v7;

  v6 = no;
  v7 = type;
  return MapDat_GetRouteDat(v6, v7);
}

// 0x1cb5890
static s16 dmLMAP_ROUTE_RELAY(s32 no) {
  return lmap_tbl_route[no]->relay;
}

// 0x1cb5960
static s16 dmLMAP_ROUTE_TYPE(s32 no) {
  return lmap_tbl_route[no]->type;
}

// 0x1cb5a30
static s16 dmLMAP_ROUTE_STAT(s32 no) {
  return lmap_tbl_route[no]->stat;
}

// 0x1cb5b00
void lmapLmapDestInit(void *ndwk) {
  ndWork = ndwk;
}

// 0x1cb5b70
static bool IsDestDisp(void) {
  return cfgGetConfigGAME(11, 0) == 0;
}

// 0x1cb5be0
static void ndWorkActive(bool _active) {
  s32 encountno;

  if (!cfgGetConfigGAME(11, 0))
    goto LABEL_18;
  if (!sbattleIsBattle())
  {
    active = 0;
    goto LABEL_18;
  }
  if (sBtlCheckTutorialBattle())
    goto LABEL_18;
  encountno = wk->encountno;
  if (encountno != 22)
  {
    encountno = wk->encountno;
    active &= encountno == 23;
  }
LABEL_18:
  Active(ndWork, active, 0);
}

// 0x1cb5de0
void lmapSetDestCheck(s32 chapter) {
  s32 v2;
  s32 size;
  s32 v7;
  s32 v9;
  s32 v10;
  s32 v13;
  void *DestData_28574400;
  void *v15;
  s32 i;
  DestData_t *Item;
  s32 stFlag;
  s32 edFlag;
  void *v22;
  s64 v23;
  u64 *v24;
  void *items;
  Il2CppClass **v26;
  void *v28;
  u64 *v29;
  s64 v30;
  s32 *v31;
  Il2CppObject *DestText1;
  void *v34;
  u64 *v35;
  s64 v36;
  void *v37;
  Il2CppClass **v38;

  v2 = chapter;
  if ((chapter & 0x80000000) == 0)
    goto LABEL_3;
  goto LABEL_9000;
  if ((v2 & 0x80000000) == 0)
  {
LABEL_3:
    goto LABEL_5;
  }
LABEL_9000:
  v2 = GBWK->GameFileInfo->chapter;
LABEL_5:
  mapIfDestUpdateInit();
  size = DestNowList->_size;
  v7 = DestNowList->_version + 1;
  DestNowList->_size = 0;
  DestNowList->_version = v7;
  if (size >= 1)
  {
    Clear(DestNowList->_items, 0, size, 0);
  }
  v9 = DestTextList->_size;
  v10 = DestTextList->_version + 1;
  DestTextList->_size = 0;
  DestTextList->_version = v10;
  if (v9 >= 1)
  {
    Clear(DestTextList->_items, 0, v9, 0);
  }
  v13 = DestNowChapter->_version + 1;
  DestNowChapter->_size = 0;
  DestNowChapter->_version = v13;
  DestData_28574400 = GetDestData_28574400(DestListTbl, v2, 0);
  if (DestData_28574400->_size >= 1)
  {
    v15 = DestData_28574400;
    for (i = 0; i < v15->_size; ++i)
    {
      Item = _get_Item(v15, i);
      stFlag = Item->_stFlag;
      if (!fldDestBitChk(v2, stFlag))
        continue;
      edFlag = Item->_edFlag;
      if (fldDestBitChk(v2, edFlag))
        continue;
      if (GBWK->GameFileInfo->chapter == 9)
      {
        if (!mapIfSetDestEx(Item))
          continue;
      }
      v22 = DestNowList;
      v23 = v22->_size;
      v24 = Method_System_Collections_Generic_List_DestData_t__Add__;
      ++v22->_version;
      items = v22->_items;
      if ((u32)v23 >= LODWORD(items->max_length))
      {
        _AddWithResize(v22, Item, *(const MethodInfo_2DFC660 **)(*(u64 *)(v24[4] + 192) + 112));
      }
      else
      {
        v22->_size = v23 + 1;
        v26 = &items->obj.klass + v23;
        v26[4] = Item;
      }
      v28 = DestNowChapter;
      v29 = Method_System_Collections_Generic_List_int__Add__;
      v30 = v28->_size;
      ++v28->_version;
      v31 = v28->_items;
      if ((u32)v30 >= LODWORD(v31->max_length))
      {
        _AddWithResize(v28, v2, *(const MethodInfo_2D8F530 **)(*(u64 *)(v29[4] + 192) + 112));
        if (!_Contains(DestTextList, Item->_DestText1))
        {
LABEL_43:
          if (!IsNullOrEmpty(Item->_DestText1, 0))
          {
            DestText1 = Item->_DestText1;
            v34 = DestTextList;
            v35 = Method_System_Collections_Generic_List_string__Add__;
            v36 = v34->_size;
            ++v34->_version;
            v37 = v34->_items;
            if ((u32)v36 >= LODWORD(v37->max_length))
            {
              _AddWithResize(v34, DestText1, *(const MethodInfo_2DFC660 **)(*(u64 *)(v35[4] + 192) + 112));
            }
            else
            {
              v34->_size = v36 + 1;
              v38 = &v37->obj.klass + v36;
              v38[4] = DestText1;
            }
          }
        }
      }
      else
      {
        v28->_size = v30 + 1;
        v31[v30] = v2;
        if (!_Contains(DestTextList, Item->_DestText1))
          goto LABEL_43;
      }
    }
  }
  mapIfDestUpdateCheck();
}

// 0x1cb67e0
void lmapDrawNextDest(void) {
  s32 i;
  Il2CppObject *Item;
  char *LocalizeText;
  char *v7;

  ndWorkActive(1);
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(ndWork->Text->max_length))
      break;
    if (i < DestTextList->_size)
    {
      SetupObjActive(ndWork, i, 1, 0);
      Item = _get_Item(DestTextList, i);
      LocalizeText = GetLocalizeText(Item, 1);
      v7 = itfTextBtnConvert(LocalizeText, 0);
      SetText(ndWork, i, v7, 0);
      continue;
    }
    SetupObjActive(ndWork, i, 0, 0);
  }
}

// 0x1cb62b0
void mapIfDestUpdateInit(void) {
  s32 size;
  s32 v4;
  void *v5;
  s32 i;
  void *v11;
  Il2CppObject *Item;
  s64 v13;
  u64 *v14;
  Il2CppObject *v15;
  void *items;
  Il2CppClass **v17;

  size = DestOldList->_size;
  v4 = DestOldList->_version + 1;
  DestOldList->_size = 0;
  DestOldList->_version = v4;
  if (size >= 1)
    Clear(DestOldList->_items, 0, size, 0);
  v5 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v5);
  DestOldList = v5;
  for (i = 0; ; ++i)
  {
    if (i >= DestTextList->_size)
      break;
    v11 = DestOldList;
    Item = _get_Item(DestTextList, i);
    v13 = v11->_size;
    v14 = Method_System_Collections_Generic_List_string__Add__;
    v15 = Item;
    ++v11->_version;
    items = v11->_items;
    if ((u32)v13 >= LODWORD(items->max_length))
    {
      _AddWithResize(v11, Item, *(const MethodInfo_2DFC660 **)(*(u64 *)(v14[4] + 192) + 112));
    }
    else
    {
      v17 = &items->obj.klass + v13;
      v11->_size = v13 + 1;
      v17[4] = v15;
    }
  }
}

// 0x1cb69e0
bool mapIfDestTextUpdateCheck(char *checkText, s32 num) {
  s32 i;
  Il2CppObject *Item;
  char *v8;
  s32 size;
  char *LocalizeText;

  if (!DestOldList->_size)
    return 1;
  for (i = 0; ; ++i)
  {
    size = DestOldList->_size;
    if (i >= size)
      break;
    LocalizeText = GetLocalizeText(checkText, 1);
    Item = _get_Item(DestOldList, i);
    v8 = GetLocalizeText(Item, 1);
    if (op_Equality(LocalizeText, v8, 0))
      return 0;
  }
  size = DestOldList->_size;
  return size > num;
}

// 0x1cb6490
void mapIfDestUpdateCheck(void) {
  s32 v1;
  Il2CppObject *Item;
  s32 v8;
  s32 v9;
  Il2CppObject *v11;
  bool v13;
  u64 *v16;
  void *v17;
  s64 size;
  bool *items;
  u64 *v20;
  void *v21;
  s64 v22;
  bool *v23;

  v1 = 0;
  while (1)
  {
    if (v1 >= DestOldList->_size)
      break;
    Item = _get_Item(DestOldList, v1++);
    if (!IsNullOrEmpty(Item, 0))
    {
LABEL_14:
      if (DestUpdateFlag)
        return;
      v8 = 0;
      v9 = DestUpdate->_version + 1;
      DestUpdate->_size = 0;
      DestUpdate->_version = v9;
      while (1)
      {
        if (v8 >= DestTextList->_size)
          break;
        v11 = _get_Item(DestTextList, v8);
        v13 = mapIfDestTextUpdateCheck(v11, v8);
        if (v13)
        {
          v16 = Method_System_Collections_Generic_List_bool__Add__;
          v17 = DestUpdate;
          size = v17->_size;
          ++v17->_version;
          items = v17->_items;
          if ((u32)size >= LODWORD(items->max_length))
          {
            _AddWithResize(v17, 1, *(const MethodInfo_2D51180 **)(*(u64 *)(v16[4] + 192) + 112));
            DestUpdateFlag = 1;
          }
          else
          {
            v17->_size = size + 1;
            items[size] = 1;
            DestUpdateFlag = 1;
          }
        }
        else
        {
          v20 = Method_System_Collections_Generic_List_bool__Add__;
          v21 = DestUpdate;
          v22 = v21->_size;
          ++v21->_version;
          v23 = v21->_items;
          if ((u32)v22 >= LODWORD(v23->max_length))
          {
            _AddWithResize(v21, 0, *(const MethodInfo_2D51180 **)(*(u64 *)(v20[4] + 192) + 112));
          }
          else
          {
            v21->_size = v22 + 1;
            v23[v22] = 0;
          }
        }
        ++v8;
      }
      return;
    }
  }
  if (!CheckRun())
    return;
  if (DestOldList->_size)
    return;
  if (DestTextList->_size > 0)
    goto LABEL_14;
}

// 0x1cb6bc0
void mapIfDestUpdateDisplay(void) {
  s32 ConfigGAME;
  bool Item;
  void *map_staging;
  Il2CppObject *v11;
  void *v15;
  bool v16;
  void *v19;
  Il2CppObject *v20;
  void *v23;
  bool v25;
  void *v28;
  Il2CppObject *v29;

  if (!DestUpdateFlag)
    return;
  ConfigGAME = cfgGetConfigGAME(11, 0);
  if (!ConfigGAME)
  {
    if (DestUpdate->_size >= 1)
    {
      Item = _get_Item(DestUpdate, 0);
      if (Item)
      {
        if (DestTextList->_size >= 1)
        {
          destUpdateSetDisp(ndWork->map_staging, 0, 1, 0);
          map_staging = ndWork->map_staging;
          v11 = _get_Item(DestTextList, 0);
          destUpdateSetText(map_staging, 0, v11, 0);
          goto LABEL_35;
        }
      }
    }
    destUpdateSetDisp(ndWork->map_staging, 0, 0, 0);
LABEL_35:
    ndWorkActive(0);
    v15 = DestUpdate;
    if (v15->_size < 2)
      goto LABEL_48;
    v15 = DestUpdate;
    v16 = _get_Item(v15, 1);
    if (v16)
    {
      if (DestTextList->_size > 1)
      {
        destUpdateSetDisp(ndWork->map_staging, 1, 1, 0);
        v19 = ndWork->map_staging;
        v20 = _get_Item(DestTextList, 1);
        destUpdateSetText(v19, 1, v20, 0);
LABEL_51:
        ndWorkActive(0);
        v23 = DestUpdate;
        if (v23->_size < 3)
          goto LABEL_66;
        v23 = DestUpdate;
        v25 = _get_Item(v23, 2);
        if (v25)
        {
          if (DestTextList->_size > 2)
          {
            destUpdateSetDisp(ndWork->map_staging, 2, 1, 0);
            v28 = ndWork->map_staging;
            v29 = _get_Item(DestTextList, 2);
            destUpdateSetText(v28, 2, v29, 0);
LABEL_69:
            ndWorkActive(0);
            destUpdateStart(ndWork->map_staging, 1, 0);
            return;
          }
        }
LABEL_66:
        destUpdateSetDisp(ndWork->map_staging, 2, 0, 0);
        goto LABEL_69;
      }
    }
LABEL_48:
    destUpdateSetDisp(ndWork->map_staging, 1, 0, 0);
    goto LABEL_51;
  }
  DestUpdateFlag = 0;
}

// 0x1cb7850
bool lmapSetBattleDestFlagCheck(s32 _flag) {
  return fldDestBitChk(13, flag);
}

// 0x1cb7240
void lmapSetBattleDestFlag(s32 no) {
  void *Asset;
  s64 naturalAligment;
  void *v15;
  void *v17;
  void *p_DestListTbl;
  void *v20;
  void *v21;
  u64 *p_DestNowList;
  void *v24;
  u64 *p_DestTextList;
  void *v27;
  void *p_DestNowChapter;
  void *v30;
  void *v33;

  if (!op_Equality(DestListTbl, 0, 0))
    goto LABEL_5;
  Asset = LoadAsset(_Ctrl_k__BackingField, "fld_common", "DestTbl", 0);
  if (Asset)
  {
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DestTbl)
        v15 = Asset;
      else
        v15 = 0;
    }
    else
    {
      v15 = 0;
    }
    DestListTbl = (void *)v15;
    p_DestListTbl = &DestListTbl;
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DestTbl)
        v20 = Asset;
      else
        v20 = 0;
    }
    else
    {
    }
LABEL_6:
    if (DestNowList)
      goto LABEL_7;
    goto LABEL_52;
  }
  v17 = &DestListTbl;
  v17 = 0;
  goto LABEL_6;
LABEL_5:
  goto LABEL_6;
  if (DestNowList)
  {
LABEL_7:
    goto LABEL_8;
  }
LABEL_52:
  v21 = Allocate(System_Collections_Generic_List_DestData_t_);
  __ctor(v21);
  p_DestNowList = &DestNowList;
  *p_DestNowList = v21;
LABEL_8:
  if (DestTextList)
  {
    goto LABEL_10;
  }
  v24 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v24);
  p_DestTextList = &DestTextList;
  *p_DestTextList = v24;
LABEL_10:
  if (DestNowChapter)
  {
    goto LABEL_12;
  }
  v27 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v27);
  p_DestNowChapter = &DestNowChapter;
  p_DestNowChapter = v27;
LABEL_12:
  if (DestOldList)
  {
    goto LABEL_14;
  }
  v30 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v30);
  DestOldList = v30;
LABEL_14:
  if (DestUpdate)
  {
    goto LABEL_17;
  }
  v33 = Allocate(System_Collections_Generic_List_bool_);
  __ctor(v33);
  DestUpdate = v33;
LABEL_17:
  fldDestBitOn(13, no);
  lmapSetDestCheck(13);
  if (!DestUpdateFlag)
    return;
  lmapSetBattleDestText();
}

// 0x1cb7c20
void lmapClrBattleDestFlag(s32 no) {
  void *Asset;
  s64 naturalAligment;
  void *v15;
  void *v17;
  void *p_DestListTbl;
  void *v20;
  void *v21;
  u64 *p_DestNowList;
  void *v24;
  u64 *p_DestTextList;
  void *v27;
  void *p_DestNowChapter;
  void *v30;
  void *v33;

  if (!op_Equality(DestListTbl, 0, 0))
    goto LABEL_5;
  Asset = LoadAsset(_Ctrl_k__BackingField, "fld_common", "DestTbl", 0);
  if (Asset)
  {
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DestTbl)
        v15 = Asset;
      else
        v15 = 0;
    }
    else
    {
      v15 = 0;
    }
    DestListTbl = (void *)v15;
    p_DestListTbl = &DestListTbl;
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_DestTbl)
        v20 = Asset;
      else
        v20 = 0;
    }
    else
    {
    }
LABEL_6:
    if (DestNowList)
      goto LABEL_7;
    goto LABEL_52;
  }
  v17 = &DestListTbl;
  v17 = 0;
  goto LABEL_6;
LABEL_5:
  goto LABEL_6;
  if (DestNowList)
  {
LABEL_7:
    goto LABEL_8;
  }
LABEL_52:
  v21 = Allocate(System_Collections_Generic_List_DestData_t_);
  __ctor(v21);
  p_DestNowList = &DestNowList;
  *p_DestNowList = v21;
LABEL_8:
  if (DestTextList)
  {
    goto LABEL_10;
  }
  v24 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v24);
  p_DestTextList = &DestTextList;
  *p_DestTextList = v24;
LABEL_10:
  if (DestNowChapter)
  {
    goto LABEL_12;
  }
  v27 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v27);
  p_DestNowChapter = &DestNowChapter;
  p_DestNowChapter = v27;
LABEL_12:
  if (DestOldList)
  {
    goto LABEL_14;
  }
  v30 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v30);
  DestOldList = v30;
LABEL_14:
  if (DestUpdate)
  {
    goto LABEL_17;
  }
  v33 = Allocate(System_Collections_Generic_List_bool_);
  __ctor(v33);
  DestUpdate = v33;
LABEL_17:
  fldDestBitOff(13, no);
  lmapSetDestCheck(13);
  if (!DestUpdateFlag)
    return;
  lmapSetBattleDestText();
}

// 0x1cb78c0
void lmapSetBattleDestText(void) {
  s32 size;
  s32 i;
  void *v9;
  u32 v10;
  Il2CppObject *Item;
  char *LocalizeText;
  Il2CppObject *v13;
  char *v14;
  void *map_staging;
  Il2CppObject *v17;

  if (!DestTextList)
    return;
  size = DestTextList->_size;
  if (size >= 1)
  {
    destUpdateStart(ndWork->map_staging, 1, 0);
    ndWorkActive(1);
    for (i = 0; ; ++i)
    {
      if (i >= SLODWORD(ndWork->Text->max_length))
        return;
      v9 = DestTextList;
      if (i < v9->_size)
      {
        if (!v10)
        {
          v9 = DestTextList;
        }
        Item = _get_Item(v9, i);
        LocalizeText = GetLocalizeText(Item, 1);
        v13 = _get_Item(DestTextList, i);
        v14 = itfTextBtnConvert(LocalizeText, v13);
        destUpdateSetDisp(ndWork->map_staging, i, 1, 0);
        map_staging = ndWork->map_staging;
        v17 = _get_Item(DestTextList, i);
        destUpdateSetText(map_staging, i, v17, 0);
        SetupObjActive(ndWork, i, 1, 0);
        SetText(ndWork, i, v14, 0);
        continue;
      }
      destUpdateSetDisp(ndWork->map_staging, i, 0, 0);
      SetupObjActive(ndWork, i, 0, 0);
    }
  }
  AnimatorCtr(ndWork, 2, 0);
}

// 0x1cb8230
void lmapSetBattleDestDisp(bool disp) {
  char v7;

  if (!DestNowChapter)
    return;
  if (!DestNowList)
    return;
  if (!disp)
  {
    v7 = 0;
LABEL_17:
    ndWorkActive(v7);
    return;
  }
  if (DestNowList->_size < 1)
    return;
  if (DestNowChapter->_size < 1)
    return;
  if (_get_Item(DestNowChapter, 0) == 13)
  {
    v7 = 1;
    goto LABEL_17;
  }
}

// 0x1cb8400
void lmapSetBattleDestRelease(void) {
  bool v11;
  void *p_DestListTbl;
  s32 v15;
  s32 v16;
  s32 version;
  s32 size;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;

  if (!DestOldList)
  {
    goto LABEL_5;
  }
  size = DestOldList->_size;
  v22 = DestOldList->_version + 1;
  DestOldList->_size = 0;
  DestOldList->_version = v22;
  if (size >= 1)
  {
    Clear(DestOldList->_items, 0, size, 0);
  }
  DestOldList = 0;
LABEL_5:
  if (!DestUpdate)
  {
    goto LABEL_7;
  }
  v23 = DestUpdate->_version + 1;
  DestUpdate = 0;
  DestUpdate->_size = 0;
  DestUpdate->_version = v23;
LABEL_7:
  if (!DestNowList)
  {
    goto LABEL_9;
  }
  v24 = DestNowList->_size;
  v25 = DestNowList->_version + 1;
  DestNowList->_size = 0;
  DestNowList->_version = v25;
  if (v24 >= 1)
  {
    Clear(DestNowList->_items, 0, v24, 0);
  }
  DestNowList = 0;
LABEL_9:
  v11 = op_Inequality(DestListTbl, 0, 0);
  if (v11)
  {
    p_DestListTbl = &DestListTbl;
    p_DestListTbl = 0;
    v15 = DestTextList->_size;
    v16 = DestTextList->_version + 1;
    DestTextList->_size = 0;
    DestTextList->_version = v16;
    if (v15 >= 1)
    {
      Clear(DestTextList->_items, 0, v15, 0);
    }
  }
  if (!DestTextList)
  {
    goto LABEL_18;
  }
  DestTextList = 0;
LABEL_18:
  if (!DestNowChapter)
    return;
  version = DestNowChapter->_version;
  DestNowChapter = 0;
  DestNowChapter->_size = 0;
  DestNowChapter->_version = version + 1;
}

// 0x1cb8790
void lmapUI_DispChange(s32 num) {
  void *baseDest;
  s32 m_Handle;

  m_Handle = GetSceneByName("lmap", 0).m_Handle;
  if (IsValid((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0))
  {
    baseDest = ndWork->baseDest;
    if (!op_Inequality(baseDest, 0, 0))
      return;
    AnimatorCtr(ndWork, num, 0);
  }
}

// 0x1cb88e0
void lmapCheckDestFildData(s32 _filedID) {
  s32 v3;

  switch (filedID)
  {
    case 1:
    case 8:
      v3 = 0;
      goto LABEL_5;
    case 2:
      v3 = 3;
      goto LABEL_5;
    case 3:
    case 9:
    case 15:
      v3 = 2;
      goto LABEL_5;
    case 4:
    case 5:
      v3 = 4;
      goto LABEL_5;
    case 6:
    case 13:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 27:
      v3 = 6;
      goto LABEL_5;
    case 7:
      v3 = 5;
      goto LABEL_5;
    default:
      v3 = -1;
LABEL_5:
      lmapwk->field_id = v3;
      return;
  }
}

// 0x1cb8a30
static void ButtonGuideOn(void) {
  bool v1;
  char **v2;

  v1 = evtBitCheck(10018);
  if (v1)
    v2 = &"LMAP01";
  else
    v2 = &"LMAP03";
  ButtonGuideDispSet(*v2, 1, 90);
}

// 0x1cb8ae0
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *proc) {
  u8 flag;
  tagLMAP_CHR_WORK *chrwk;
  tagM_LMAP_WORK *v10;
  dds3ModelHandle_t *hModel_yaso;
  sdfModelOt_t *v13;
  tagM_LMAP_WORK *v17;
  dds3ModelHandle_t *v19;
  sdfModelOt_t *v20;
  tagLMAP_CHR_WORK *v21;
  f32 x;
  f32 z;
  s32 v25;
  f32 *p_x;
  f32 *v27;
  f32 v28;
  f32 v29;
  f32 y;
  tagM_LMAP_WORK *v33;
  f32 v34;
  char v35;
  _BOOL4 bSetFilter;
  s32 v45;
  s32 v46;
  s32 v48;
  _BOOL4 bDrawActWin;
  tagM_LMAP_WORK *v55;

  flag = lmapwk->flag;
  if ((flag & 1) != 0)
    return 0;
  if ((flag & 2) == 0)
    return 0;
  EffWave_Draw(lmapwk->proc_effwave);
  if (!lmapwk->hModel_yaso)
    goto LABEL_117;
  eglSetOt(44);
  eglLinkAlpha(0);
  chrwk = lmapwk->chrwk;
  if (chrwk->pos.x < 277.0)
  {
    chrwk = lmapwk->chrwk;
    if (chrwk->pos.z > -277.0)
    {
      eglLinkTest(SET_10AADD11);
      v10 = lmapwk;
      hModel_yaso = v10->hModel_yaso;
      v13 = ModelOt[0];
      Link(hModel_yaso, v13);
      goto LABEL_30;
    }
  }
LABEL_30:
  eglLinkTest(SET_10AADD12);
  v17 = lmapwk;
  v19 = v17->hModel_yaso;
  v20 = ModelOt[0];
  Link(v19, v20);
  eglLinkTest(SET_10AADD12);
  v21 = lmapwk->chrwk;
  x = v21->pos.x;
  z = v21->pos.z;
  v25 = (u8)byte_575608B;
  vct_A = (struct sdfVector4_t)xmmword_3D00550;
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = 0.0;
  p_x[10] = z;
  p_x[11] = 0.0;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v27 = &vf00.x;
  v28 = v27[6];
  v29 = v27[4];
  y = v27[5];
  v33 = lmapwk;
  v34 = sqrtf((f32)((f32)(v29 * v29) + (f32)(y * y)) + (f32)(v28 * v28));
  if (v33->bSetFilter)
  {
    if (v34 < 400.0)
      goto LABEL_70;
    v35 = 0;
LABEL_56:
    v33->bSetFilter = v35;
    goto LABEL_70;
  }
  if (v34 < 400.0)
  {
    v35 = 1;
    goto LABEL_56;
  }
LABEL_70:
  if (CallCampFromLmap)
  {
    lmapwk->bSetFilter = 0;
  }
  bSetFilter = lmapwk->bSetFilter;
  if (bSetFilter)
    goto LABEL_78;
  if (gFilterAlpha < 1)
    goto LABEL_117;
  v48 = gFilterAlpha - 1;
  v46 = v48 & ~(v48 >> 31);
LABEL_112:
  gFilterAlpha = v46;
  goto LABEL_117;
LABEL_78:
  goto LABEL_80;
LABEL_81:
  if (gFilterAlpha > 127)
    goto LABEL_117;
  v45 = gFilterAlpha;
  if (v45 + 1 < 128)
    v46 = v45 + 1;
  else
    v46 = 128;
  goto LABEL_112;
LABEL_80:
  goto LABEL_81;
LABEL_117:
  bDrawActWin = lmapwk->bDrawActWin;
  itfPreDrawActionWndDisp(bDrawActWin);
  v55 = lmapwk;
  if (v55->bDrawActWin)
  {
    v55 = lmapwk;
    DrawActWin(v55->panel_type, v55->chrwk->pos.x, v55->chrwk->pos.y, v55->chrwk->pos.z);
  }
  return 0;
}

// 0x1cb9870
static void Initialize(void) {
  char *v2;
  char *v3;
  char *v4;
  __int128 v9;
  char *v10;
  tagLMAP_LOCK_WORK *lockwk;
  s16 *pointNo;
  s16 *lineNo;
  void *v15;
  void *v17;
  void *v19;
  void *p_DestNowList;
  void *p_DestListTbl;
  void *v22;
  void *p_DestTextList;
  void *v24;
  void *p_DestNowChapter;
  char *v26;
  void *Asset;
  s64 naturalAligment;
  void *v31;
  void *p_LmapCameraPar;
  void *v35;
  void *v37;
  s64 v39;
  void *v40;
  void *v41;
  void *v42;
  Il2CppObject *Item;
  tagM_LMAP_WORK *lmapwk_local;
  tagM_LMAP_WORK *v51;
  s32 width;
  tagM_LMAP_WORK *v54;
  s32 height;
  tagM_LMAP_WORK *v59;
  void *SceneAsync;
  u64 v70;
  s64 v72;
  void *v74;
  s64 v76;
  void *v77;
  void *p_lmapJmpDataTbls;
  void *v81;

  v2 = "UI_map";
  v3 = "lmap";
  v4 = "lmap_sys";
  Load(Dependent, v3, v3);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Load(Dependent, v4, v4);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Load(Dependent, v2, v2);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  *(u64 *)&v9 = -1;
  *((u64 *)&v9 + 1) = -1;
  v10 = v4;
  lockwk = lmapwk->lockwk;
  pointNo = lockwk->pointNo;
  *(_OWORD *)pointNo = v9;
  *(_OWORD *)&pointNo[8] = v9;
  *(_OWORD *)&pointNo[16] = v9;
  *(_OWORD *)&pointNo[24] = v9;
  *(_OWORD *)&pointNo[32] = v9;
  *(_OWORD *)&pointNo[40] = v9;
  *(_OWORD *)&pointNo[48] = v9;
  *(_OWORD *)&pointNo[56] = v9;
  lineNo = lockwk->lineNo;
  *(u64 *)lineNo = -1;
  *(u64 *)&lineNo[4] = -1;
  DestUpdateFlag = 0;
  v15 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v15);
  DestOldList = v15;
  v17 = Allocate(System_Collections_Generic_List_bool_);
  __ctor(v17);
  DestUpdate = v17;
  v19 = Allocate(System_Collections_Generic_List_DestData_t_);
  __ctor(v19);
  p_DestNowList = &DestNowList;
  p_DestNowList = v19;
  p_DestListTbl = &DestListTbl;
  p_DestListTbl = 0;
  v22 = Allocate(System_Collections_Generic_List_string_);
  __ctor(v22);
  p_DestTextList = &DestTextList;
  p_DestTextList = v22;
  v24 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v24);
  p_DestNowChapter = &DestNowChapter;
  p_DestNowChapter = v24;
  v26 = v10;
  Asset = LoadAsset(_Ctrl_k__BackingField, v26, "lmapCameraPar", 0);
  if (!Asset)
  {
    LmapCameraPar = 0;
    goto LABEL_48;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_lmapCameraPar)
      v31 = Asset;
    else
      v31 = 0;
  }
  else
  {
    v31 = 0;
  }
  LmapCameraPar = (void *)v31;
  p_LmapCameraPar = &LmapCameraPar;
  if (Asset->klass->_2.naturalAligment < (u32)naturalAligment)
  {
    goto LABEL_48;
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_lmapCameraPar)
    v35 = Asset;
  else
    v35 = 0;
LABEL_48:
  v37 = LoadAsset(_Ctrl_k__BackingField, "fld_common", "DestTbl", 0);
  if (v37)
  {
    if (v37->klass->_2.naturalAligment >= (u32)v39)
    {
      if (v37->klass->_2.typeHierarchy[v39 - 1] == Project_DestTbl)
        v40 = v37;
      else
        v40 = 0;
    }
    else
    {
      v40 = 0;
    }
    DestListTbl = (void *)v40;
    v42 = &DestListTbl;
    if (v37->klass->_2.naturalAligment >= (u32)v39)
    {
      if (v37->klass->_2.typeHierarchy[v39 - 1] == Project_DestTbl)
        v41 = v37;
      else
        v41 = 0;
    }
    else
    {
      v41 = 0;
    }
  }
  else
  {
    v41 = 0;
    v42 = &DestListTbl;
    v42 = 0;
  }
  mapIfSetDestList();
  lmapDestMarkDraw();
  lmapQuestMarkClear();
  lmapSetDestCheck(-1);
  sdfMemSetAllocated();
  if (DestNowList->_size >= 1)
  {
    Item = _get_Item(DestNowList, 0);
    lmapCheckDestFildData(HIDWORD(Item[4].monitor));
  }
  SetData(ndWork, 0);
  lmapwk_local = lmapwk;
  lmapwk_local->proc_effgrid = 0;
  lmapwk_local = ((char *)lmapwk_local + 80);
  BYTE2(lmapwk_local->hModel_yaso) = 0;
  v51 = lmapwk;
  *(u32 *)&v51->TaraSE_RandNo = -1;
  v51->TaraSE_Flag = 0;
  v51->msgLogFlag = 0;
  *(u64 *)&v51->TaraSE_time = 0;
  TaraCtrlFlag = 0;
  width = get_width(0);
  v51->ScreenSaveW = width;
  v54 = lmapwk;
  height = get_height(0);
  v54->ScreenSaveH = height;
  v59 = lmapwk;
  gLMapCampMcLoadEnd = 0;
  v59->worldId = 1;
  if (fldGb->NoInpPlCnt)
  {
    fldGb->NoInpPlCnt = 0;
  }
  M_InitScene();
  M_InitCamera();
  M_UpdateCamera();
  M_InitLight();
  Load(Dependent, "ui_field", "ui_field");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, fieldUIname, 0);
  fieldUIscene_asyncLoad = SceneAsync;
  v70 = arrStFlag[0];
  if ((u32)v70)
  {
    if ((u32)(v70 - 2618) >= 0xFFFFFFC6)
      evtBitKityouItemAdd(v70);
    v72 = (s64)GBWK->EventBit + ((v70 >> 3) & 0x1FFC);
    *(u32 *)(v72 + 32) |= 1 << v70;
  }
  itfSetActionWndLines(1);
  v74 = LoadAsset(_Ctrl_k__BackingField, v26, "lmapJmpDataTbl", 0);
  if (v74)
  {
    if (v74->klass->_2.naturalAligment >= (u32)v76)
    {
      if (v74->klass->_2.typeHierarchy[v76 - 1] == Project_lmapJmpDataTbl)
        v77 = v74;
      else
        v77 = 0;
    }
    else
    {
      v77 = 0;
    }
    lmapJmpDataTbls = (void *)v77;
    p_lmapJmpDataTbls = &lmapJmpDataTbls;
    if (v74->klass->_2.naturalAligment >= (u32)v76)
    {
      if (v74->klass->_2.typeHierarchy[v76 - 1] == Project_lmapJmpDataTbl)
        v81 = v74;
      else
        v81 = 0;
    }
    else
    {
      v81 = 0;
    }
  }
  else
  {
    lmapJmpDataTbls = 0;
  }
}

// 0x1cbb3c0
void lmapSceneInitialize(void) {
  void *p_Dependent;
  void *Dependent_local;
  char *v7;
  void *SceneAsync;
  void *Asset;
  Il2CppObject *v13;
  Il2CppObject *v14;
  void *transform;
  void *v17;
  void *gameObject;
  void *v19;
  void *v20;
  void *v21;
  void *v22;
  void *v23;
  void *v25;
  Il2CppObject *v26;
  Il2CppObject *v27;
  void *v29;
  void *v30;
  void *v31;
  void *v32;
  void *v33;
  void *v34;
  void *v35;
  void *v36;
  sdfVector3_t v37;
  sdfVector3_t v38;
  sdfVector3_t v39;
  sdfVector3_t v40;
  sdfVector3_t v41;
  sdfVector3_t v42;
  sdfVector3_t v43;
  sdfQuaternion_t v44;
  sdfQuaternion_t v45;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, akey_Lmap, akey_Lmap);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Load(Dependent, akey_LmapBack, akey_LmapBack);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  v7 = "lmap";
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, v7, 0);
  Lmapscene_asyncLoad = SceneAsync;
  Asset = LoadAsset(_Ctrl_k__BackingField, akey_LmapBack, "lmap01", 0);
  if (!Asset)
  {
    v13 = 0;
    goto LABEL_30;
  }
  if (Asset->klass == UnityEngine_GameObject)
    v13 = Asset;
  else
    v13 = 0;
LABEL_30:
  v14 = Instantiate_object_(v13);
  backObjIns01 = v14;
  transform = get_transform(backObjIns01, 0);
  v17 = Find(transform, "lmap01", 0);
  gameObject = get_gameObject(v17, 0);
  v19 = get_transform(backObjIns01, 0);
  set_localPosition(v19, zeroVector, 0);
  v20 = get_transform(backObjIns01, 0);
  v37.x = 510.0;
  v37.y = 1.0;
  v37.z = 510.0;
  set_localScale(v20, v37, 0);
  v21 = get_transform(gameObject, 0);
  v38.x = 1.0;
  v38.y = 1.0;
  v38.z = 1.0;
  set_localScale(v21, v38, 0);
  v22 = get_transform(gameObject, 0);
  v39.x = 0.0;
  v39.y = 0.0;
  v23 = v22;
  v39.z = 0.0;
  v44 = Internal_FromEulerRad(v39, 0);
  set_localRotation(v23, v44, 0);
  v25 = LoadAsset(_Ctrl_k__BackingField, akey_LmapBack, "lmap02", 0);
  if (v25)
  {
    if (v25->klass == UnityEngine_GameObject)
      v26 = v25;
    else
      v26 = 0;
  }
  else
  {
    v26 = 0;
  }
  v27 = Instantiate_object_(v26);
  backObjIns02 = v27;
  v29 = get_transform(backObjIns02, 0);
  v30 = Find(v29, "lmap02", 0);
  v31 = get_gameObject(v30, 0);
  v32 = get_transform(backObjIns02, 0);
  v40.y = 0.0;
  v40.x = 10.24;
  v40.z = 0.0;
  set_localPosition(v32, v40, 0);
  v33 = get_transform(backObjIns02, 0);
  v41.y = 1.0;
  v41.x = 510.0;
  v41.z = 510.0;
  set_localScale(v33, v41, 0);
  v34 = get_transform(v31, 0);
  v42.x = 1.0;
  v42.y = 1.0;
  v42.z = 1.0;
  set_localScale(v34, v42, 0);
  v35 = get_transform(v31, 0);
  v43.x = 0.0;
  v43.y = 0.0;
  v36 = v35;
  v43.z = 0.0;
  v45 = Internal_FromEulerRad(v43, 0);
  set_localRotation(v36, v45, 0);
  SetActive(v26, 1, 0);
}

// 0x1cbb9a0
static dds3ProcessFunc_t Process(dds3ProcessID_t *id) {
  long f64 v2;
  s32 v8;
  u32 v11;
  u32 v14;
  void *RootGameObjects;
  void *v18;
  s64 v19;
  void *m_Items;
  char *name;
  s32 v22;
  tagM_LMAP_WORK *v27;
  dds3ProcessFunc_t v28;
  tagM_LMAP_WORK *v30;
  s32 MenuCnt;
  tagM_LMAP_WORK *v32;
  dds3ModelHandle_t *hModel_yaso;
  tagM_LMAP_WORK *v40;
  long f64 v45;
  s32 v47;
  tagM_LMAP_WORK *v50;
  void *v52;
  s32 v55;
  tagM_LMAP_WORK *v56;
  s32 v57;
  u32 v61;
  tagM_LMAP_WORK *v63;
  s32 cnt_moveMap;
  u32 v65;
  tagM_LMAP_WORK *v66;
  s32 v72;
  tagM_LMAP_WORK *v73;
  s32 v74;
  tagM_LMAP_WORK *v78;
  tagM_LMAP_WORK *v80;
  s32 v85;
  s32 v86;
  u32 v87;
  void *v91;
  tagM_LMAP_WORK *v97;
  tagM_LMAP_WORK *v100;
  void *v101;
  tagLMAP_CAMERA_WORK *v102;
  dds3Basic_t *v103;
  f32 v104;
  f32 v105;
  f32 v107;
  s32 v109;
  s32 v110;
  s32 v111;
  s32 v115;
  void *v118;
  void *v120;
  tagM_LMAP_WORK *v123;
  void *p_Dependent;
  void *v131;
  void *v139;
  dds3ModelHandle_t *v141;
  dds3ProcessID_t *v144;
  void *v146;
  tagM_LMAP_WORK *v148;
  tagLMAP_CAMERA_WORK *cam;
  dds3Basic_t *p_object;
  f32 v152;
  f32 v153;
  f32 v154;
  GlobalWork_t *v159;
  s32 fieldID;
  s32 floorID;
  u8 PointFlag;
  u32 v166;
  u32 v168;
  tagM_LMAP_WORK *v169;
  tagLMAP_CHR_WORK *chrwk;
  u32 v171;
  dds3GlobalWork_t *v176;
  s32 v179;
  s32 v181;
  char **v183;
  void *v192;
  Il2CppObject *Component_object;
  u64 *p_fldUI;
  Il2CppObject *v196;
  void *p_map_win;
  Il2CppObject *v198;
  void *p_map_sts;
  Il2CppObject *v200;
  void *p_menu_win;
  Il2CppObject *v202;
  void *p_devil_win;
  Il2CppObject *v204;
  void *p_devil_info2;
  void *gameObject;
  s64 i;
  void *v211;
  void *cursor;
  void *Instance;
  void *v223;
  tagM_LMAP_WORK *v225;
  u8 flag;
  tagLMAP_CHR_WORK *v227;
  u32 v228;
  tagLMAP_CHR_WORK *v229;
  s8 v230;
  bool v231;
  char v233;
  tagM_LMAP_WORK *v235;
  char v236;
  u32 v238;
  tagLMAP_CHR_WORK *v239;
  s32 moveId;
  tagLMAP_CHR_UTIL_WORK *ship;
  char v242;
  tagLMAP_CHR_UTIL_WORK *v244;
  u32 v246;
  tagM_LMAP_WORK *v247;
  s32 TaraSE_time;
  s32 v249;
  bool v253;
  tagLMAP_CHR_WORK *v256;
  u32 v257;
  u32 flags;
  tagM_LMAP_WORK *v259;
  tagM_LMAP_WORK *v260;
  tagM_LMAP_WORK *v266;
  s32 updated;
  u8 v272;
  s16 PointID;
  tagM_LMAP_WORK *v276;
  tagM_LMAP_WORK *v277;
  s32 panel_type;
  tagLMAP_CHR_WORK *v279;
  bool DrawVehicle;
  u32 v282;
  tagLMAP_CHR_WORK *v285;
  f32 z;
  long f64 v287;
  s32 v291;
  bool v292;
  s32 v293;
  tagM_LMAP_WORK *v295;
  bool v297;
  s32 v299;
  s64 v303;
  sdfVector4_t v307;
  s32 m_Handle;
  dds3Basic_t *basic;
  sdfVector4_t v310;
  sdfVector4_t v311;

  basic = 0;
  m_Handle = 0;
  *(u64 *)&v307.x = 0;
  *(u64 *)&v307.z = 0;
  switch (lmapwk->step_main)
  {
    case 0:
      lmapSceneInitialize();
      v8 = 29;
      goto LABEL_343;
    case 1:
      Initialize(lmap);
      lmapMenuProcessStart();
      v8 = 2;
      goto LABEL_343;
    case 2:
      if (!get_isDone(Lmapscene_asyncLoad, 0))
        goto LABEL_346;
      v8 = 15;
      goto LABEL_344;
    case 3:
      if (lmapwk->count)
      {
        if (!v11)
        if (sndBgmStatus_XF() == 2)
        {
          v8 = 4;
          goto LABEL_510;
        }
      }
      else
      {
        if (!v11)
        sndBgmLoadId_XF(10);
      }
      goto LABEL_370;
    case 4:
      if (lmapwk->count)
      {
        if (!v14)
        if (SoundSmgLoadChk())
        {
          m_Handle = GetSceneByName(fieldUIname, 0).m_Handle;
          RootGameObjects = GetRootGameObjects((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0);
          if (SLODWORD(RootGameObjects->max_length) >= 1)
          {
            v18 = RootGameObjects;
            v19 = 0;
            m_Items = RootGameObjects;
            while (1)
            {
              name = get_name(m_Items[v19], 0);
              if (op_Equality(name, "Canvas", 0))
                break;
              if (++v19 >= SLODWORD(v18->max_length))
                goto LABEL_488;
            }
            v192 = (&v18->obj.klass + v19);
            SetActive(v192[4], 1, 0);
            Component_object = GetComponent_object_(v192[4]);
            p_fldUI = &fldUI;
            *p_fldUI = Component_object;
            ChangeObject(fldUI, 1, 1, 0);
            v196 = GetComponent_object_(fldUI->MapWindow);
            p_map_win = &map_win;
            p_map_win = (void *)v196;
            v198 = GetComponent_object_(fldUI->map);
            p_map_sts = &map_sts;
            p_map_sts = (void *)v198;
            v200 = GetComponent_object_(fldUI->menu);
            p_menu_win = &menu_win;
            p_menu_win = (void *)v200;
            v202 = GetComponent_object_(fldUI->nakamaSelect);
            p_devil_win = &devil_win;
            p_devil_win = (void *)v202;
            v204 = GetComponent_object_(fldUI->nakamaInfo);
            p_devil_info2 = &devil_info2;
            p_devil_info2 = (void *)v204;
            gameObject = get_gameObject(map_win, 0);
            SetActive(gameObject, 0, 0);
          }
LABEL_488:
          if (!op_Inequality(menu_win, 0, 0))
          {
LABEL_503:
            Instance = get_Instance(0);
            ItfButtonGuideSet(Instance, 0, 0);
            ButtonGuideDispOff();
            lmapDrawNextDest();
            v8 = 5;
LABEL_510:
            v66 = lmapwk;
            v66->count = 0;
LABEL_345:
            v66->step_main = v8;
            goto LABEL_346;
          }
          for (i = 0; ; ++i)
          {
            cursor = menu_win->cursor;
            if (i >= SLODWORD(cursor->max_length))
              goto LABEL_503;
            v211 = cursor[i];
            fldSetupObject(v211, 0);
          }
        }
      }
      else
      {
        if (!v14)
        SoundSmgLoad(6946816);
      }
LABEL_370:
      ++lmapwk->count;
      goto LABEL_346;
    case 5:
      v22 = M_MoveMap(0);
      Chr_UpdateModel(&lmapwk->chrwk);
      if (!v22)
        goto LABEL_346;
      lmapwk->step_main = 6;
      if (evtBitCheck(1949))
      {
        sub_1B34170(1949, 0);
        goto LABEL_51;
      }
      PointFlag = MapDat_GetPointFlag(lmapwk->chrwk->basePointNo);
      if ((PointFlag & 4) == 0)
      {
        if (v166)
          goto LABEL_427;
        goto LABEL_426;
      }
      v169 = lmapwk;
      if (v169->loadStart)
      {
        if (!v168)
        {
          v169 = lmapwk;
        }
        chrwk = v169->chrwk;
        if (!chrwk->taraFlag)
        {
          if (!v171)
          {
LABEL_426:
LABEL_427:
            g_bStartTakeShip = 0;
            goto LABEL_429;
          }
          g_bStartTakeShip = 0;
          goto LABEL_429;
        }
        if (v171)
        {
LABEL_541:
          chrwk->line.x = 0.0;
          chrwk->pos.y = 0.0;
          chrwk->line.z = -1.0;
          chrwk->moveId = 1;
          g_bStartTakeShip = 1;
LABEL_429:
          ButtonGuideOn();
          goto LABEL_346;
        }
      }
      else if (v168)
      {
LABEL_540:
        chrwk = v169->chrwk;
        goto LABEL_541;
      }
      v169 = lmapwk;
      goto LABEL_540;
    case 6:
      v28 = 0;
      if (scrSearchScriptName("jimusyo_hajiki2_label"))
        return v28;
      v28 = 0;
      if (scrSearchScriptName("Not_FastTravel"))
        return v28;
      v30 = lmapwk;
      MenuCnt = v30->MenuCnt;
      if (MenuCnt > 15)
      {
        goto LABEL_65;
      }
      v30 = lmapwk;
      MenuCnt = v30->MenuCnt;
      v30->MenuCnt = MenuCnt + 1;
LABEL_65:
      v32 = lmapwk;
      if (v32->mesFlag)
      {
        v32 = lmapwk;
        v32->mesFlag = 0;
        v223 = get_Instance(0);
        ItfButtonGuideSet(v223, 0, 0);
        ButtonGuideOn();
      }
      v225 = lmapwk;
      flag = v225->flag;
      if ((flag & 0x10) == 0)
      {
        goto LABEL_561;
      }
      v225 = lmapwk;
      flag = v225->flag;
      v225->flag = flag & 0xEF;
      if ((flag & 0x20) != 0)
      {
        if (!v228)
        {
          v225 = lmapwk;
        }
        v229 = v225->chrwk;
        v230 = v229->moveStat & 0xFE;
      }
      else
      {
        if (!v228)
        {
          v225 = lmapwk;
        }
        v229 = v225->chrwk;
        v230 = v229->moveStat | 1;
      }
      v229->moveStat = v230;
LABEL_561:
      v227 = lmapwk->chrwk;
      if ((v227->moveStat & 1) != 0)
        goto LABEL_656;
      v227 = lmapwk->chrwk;
      if (v227->moveId == 8)
      {
LABEL_605:
        if (!g_bStartTakeShip)
          goto LABEL_639;
LABEL_608:
        v239 = lmapwk->chrwk;
        moveId = (u8)v239->moveId;
        if (moveId == 1)
        {
          if (!v238)
          {
            v239 = lmapwk->chrwk;
          }
          v239->moveId = 3;
          ship = v239->ship;
          ship->step = 0;
          ship->count = 0;
          v239->degree = 360.0;
          if (g_bStartTakeShip)
          {
            ship = lmapwk->chrwk->ship;
            ship->step = 10;
          }
          v242 = 1;
          v239 = lmapwk->chrwk;
        }
        else
        {
          if (!v238)
          {
            v239 = lmapwk->chrwk;
            moveId = (u8)v239->moveId;
          }
          if (moveId != 3)
            goto LABEL_636;
          v239 = lmapwk->chrwk;
          v244 = v239->ship;
          if (v244->mode != 1)
            goto LABEL_636;
          v239 = lmapwk->chrwk;
          v244 = v239->ship;
          v242 = 0;
          v244->mode = 2;
        }
        v239->taraFlag = v242;
LABEL_636:
        g_bStartTakeShip = 0;
        TaraCtrlFlag = 1;
LABEL_639:
        v247 = lmapwk;
        if (v247->TaraSE_Flag)
        {
          if (!v246)
          {
            v247 = lmapwk;
          }
          TaraSE_time = v247->TaraSE_time;
          if (TaraSE_time < 1)
          {
            sndSeStop_name("mapse_0a", 0);
            lmapwk->TaraSE_Flag = 0;
          }
          else
          {
            v247 = lmapwk;
            TaraSE_time = v247->TaraSE_time;
            v247->TaraSE_time = TaraSE_time - 1;
          }
        }
        else
        {
          if (!v246)
          {
            v247 = lmapwk;
          }
          v247->TaraSE_time = 0;
        }
LABEL_656:
        v249 = (u8)CtrlActionWindow();
        if (v249 == 2)
        {
LABEL_51:
          v27 = lmapwk;
          v27->stepAuto = 0;
          v27->count = 0;
          v27->step_main = 11;
          ButtonGuideDispOff();
          goto LABEL_346;
        }
        if (v249 == 1)
        {
          p2sdPlaySE_Vol(6946819, 127);
          v8 = 12;
LABEL_344:
          v66 = lmapwk;
          goto LABEL_345;
        }
        v253 = CHECK_PRESS2(8204);
        if (v253)
        {
          v256 = lmapwk->chrwk;
          if (v256->moveId == 1)
          {
            v256 = lmapwk->chrwk;
            v257 = v256->flags | 0x20;
LABEL_676:
            v256->flags = v257;
          }
        }
        else
        {
          v256 = lmapwk->chrwk;
          flags = v256->flags;
          if ((flags & 0x20) != 0)
          {
            v256 = lmapwk->chrwk;
            flags = v256->flags;
            v257 = flags & 0xFFFFFFDF;
            goto LABEL_676;
          }
        }
        v259 = lmapwk;
        if (v259->chrwk->moveStat)
        {
          goto LABEL_680;
        }
        v259 = lmapwk;
        updated = (u8)Chr_UpdateMove(&v259->chrwk, &v259->lockwk);
        if (updated != 1)
        {
          if (updated == 3)
          {
            v272 = MapDat_GetPointFlag(lmapwk->chrwk->basePointNo);
            PointID = MapDat_GetPointID(lmapwk->chrwk->basePointNo);
            if ((v272 & 1) != 0)
            {
              v276 = lmapwk;
              v276->fieldNo = PointID;
              v276->step_main = 12;
            }
          }
          else
          {
          }
          goto LABEL_754;
        }
        v279 = lmapwk->chrwk;
        if (v279->moveId != 3)
          goto LABEL_754;
        v279 = lmapwk->chrwk;
        DrawVehicle = ChrGetDrawVehicle(v279);
        if (!DrawVehicle)
          goto LABEL_754;
        if (lmapwk->chrwk->ship->step != 3)
        {
LABEL_754:
          SetAreaName(lmapwk->chrwk->lineTableNo);
LABEL_680:
          Chr_UpdateModel(&lmapwk->chrwk);
          v260 = lmapwk;
          MapId = lmapMapDat_GetMapId(v260->chrwk->basePointNo);
          v260->mapId = (char)MapId;
          M_MainNpcCB();
          M_UpdateCamera();
          v266 = lmapwk;
          if (v266->chrwk->moveId == 8)
            goto LABEL_799;
          v266 = lmapwk;
          if (!v266->guide_onoff)
          {
LABEL_799:
            ButtonGuideDispOut();
            ButtonGuideTimerReset();
          }
          else
          {
            v266 = lmapwk;
            if (!v266->msgwk->step)
            {
              v266 = lmapwk;
              if (!v266->menu_onoff)
              {
                CheckPlayerCtrl();
              }
            }
          }
          if (!DestUpdateFlag)
          {
            if (!lmapwk->msgwk->step)
            {
              ndWorkActive(1);
            }
          }
          goto LABEL_346;
        }
        v307 = (sdfVector4_t)xmmword_3CFD5C0;
        if (v282)
        {
          if (Process_count == 2)
            goto LABEL_746;
        }
        else
        {
          if (Process_count == 2)
          {
LABEL_746:
            sub_1B332C0(0, 0.0, 0.0, 0.0, 1.0);
            sub_1B33360(0, lmapwk->chrwk->line.x, lmapwk->chrwk->line.y, lmapwk->chrwk->line.z, lmapwk->chrwk->line.w);
            sub_1B33400(0);
            sub_1B33480(0, 12.0);
            v285 = lmapwk->chrwk;
            z = v285->pos.z;
            v307.x = v285->pos.x;
            v307.z = z;
            sub_1B33360(0, v307.x, 0.0, z, 1.0);
            *(__n128 *)&v287 = sub_1B33520(0);
            sub_1B335A0(&v307, 0, v287);
            EffWave_SetData(lmapwk->proc_effwave, v307, lmapwk->chrwk->line);
            EffWave_SetColorType(lmapwk->proc_effwave, 1);
            v291 = Process_count + 1;
            v292 = Process_count - 2 < 0;
            Process_count = v291;
            if (v292 != __OFSUB__(v291, 3))
              goto LABEL_754;
LABEL_778:
            Process_count = 0;
            goto LABEL_754;
LABEL_777:
            v299 = Process_count + 1;
            v292 = Process_count - 2 < 0;
            Process_count = v299;
            if (v292 != __OFSUB__(v299, 3))
              goto LABEL_754;
            goto LABEL_778;
          }
        }
        goto LABEL_777;
      }
      v231 = CHECK_TRIG(4096, 1);
      if (!v231)
        goto LABEL_589;
      if (lmapwk->menu_onoff)
        goto LABEL_589;
      if (!MenuFlag)
        goto LABEL_589;
      v277 = lmapwk;
      if (v277->MenuCnt < 16)
        goto LABEL_589;
      v277 = lmapwk;
      panel_type = (u8)v277->panel_type;
      if (panel_type != 5)
      {
        panel_type = (u8)lmapwk->panel_type;
        if (panel_type != 6)
          goto LABEL_589;
      }
      if ((lmapwk->chrwk->portTableNo & 0x80000000) == 0)
      {
        SE(0);
        v233 = 1;
        lmapwk->MenuCnt = 0;
        goto LABEL_591;
      }
      else
      {
LABEL_589:
        v233 = 0;
        goto LABEL_591;
      }
LABEL_591:
      if ((lmapwk->chrwk->moveStat & 4) != 0)
        goto LABEL_604;
      if (!MenuFlag)
        goto LABEL_604;
      v235 = lmapwk;
      v236 = v235->msgwk->step ? 1 : v233;
      if ((v236 & 1) != 0)
        goto LABEL_604;
      v235 = lmapwk;
      if (v235->MenuCnt < 16)
        goto LABEL_604;
      if (MskR1Task() == 1)
        return 0;
      v293 = lmapIfMenuTask();
      if (CHECK_TRIG(8194, 1))
      {
        v295 = lmapwk;
        if (!v295->menu_onoff)
        {
          v295 = lmapwk;
          v295->step_main = 7;
          dds3FadeOut(0, 0, 0, 8u);
          Delete(0);
          FldWnd_Reset();
          FldWnd_SetFlagDraw(0);
          lmapwk->bDrawActWin = 0;
          SE(17);
          lmapDestMarkClear();
          return 0;
        }
      }
      v297 = CHECK_TRIG(8205, 1);
      if (!v297)
        goto LABEL_771;
      if (lmapwk->menu_onoff)
      {
LABEL_771:
        if (v293)
        {
          lmapwk->step_main = 16;
          FldWnd_SetFlagDraw(0);
          lmapwk->bDrawActWin = 0;
          FldWnd_Reset();
          return 0;
        }
LABEL_604:
        if ((v233 & 1) != 0)
          goto LABEL_608;
        goto LABEL_605;
      }
      itfMsgLogStartUI(0);
      v303 = *((u64 *)*((const MethodInfo *)lmap + 2).virtualMethodPointer + 12);
      *(u32 *)(v303 + 108) = 28;
      *(u8 *)(v303 + 140) = 1;
      FldWnd_Reset();
      FldWnd_SetFlagDraw(0);
      lmapwk->bDrawActWin = 0;
      SE(17);
      lmapDestMarkClear();
      ndWorkActive(0);
      v28 = 0;
      is_field = 1;
      return v28;
    case 7:
      if (dds3FadeCheck())
        goto LABEL_346;
      CallCampFromLmap = 1;
      if (lmapwk->TaraSE_Flag)
      {
        sndSeStop_name("mapse_0a", 0);
        lmapwk->TaraSE_Flag = 0;
      }
      ButtonGuideDispOff();
      GuideObjClr();
      lmapwk->step_main = 8;
      ndWorkActive(0);
      dds3DrawEnvPush();
      basic = dds3GetActiveScene();
      dds3SceneBasicVisible(basic, 0);
      cmpProcessStartEx(0);
      dds3FadeIn2(8u);
      hModel_yaso = lmapwk->hModel_yaso;
      if (hModel_yaso)
      {
        hModel_yaso = lmapwk->hModel_yaso;
        v310.x = 1.0;
        v310.w = 0.0;
        v310.y = 1.0;
        v310.z = 1.0;
        SetColor(hModel_yaso, v310);
      }
      v40 = lmapwk;
      if (!v40->bSetFilter)
        goto LABEL_346;
      v40 = lmapwk;
      goto LABEL_246;
    case 8:
      if (cmpProcessCheck())
        goto LABEL_346;
      v8 = 9;
      goto LABEL_344;
    case 9:
      if (g_endmode)
      {
        if ((u32)sub_1B34880(0, v2) != 2)
        {
          fmProcTrigSequence(1);
          v8 = 10;
          goto LABEL_344;
        }
LABEL_522:
        v28 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
        _ctor(v28, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
        return v28;
      }
      v139 = get_Instance(0);
      ItfButtonGuideSet(v139, 0, 0);
      ButtonGuideOn();
      v141 = lmapwk->hModel_yaso;
      if (v141)
      {
        v141 = lmapwk->hModel_yaso;
        v311.x = 1.0;
        v311.y = 1.0;
        v311.z = 1.0;
        v311.w = 1.0;
        SetColor(v141, v311);
      }
      dds3FadeIn2(8u);
      ndWorkActive(1);
      CallCampFromLmap = 0;
      lmapwk->step_main = 6;
      basic = dds3GetActiveScene();
      dds3SceneBasicVisible(basic, 1);
      Create(0);
      fclLoadData("lmp_sys.bmd", "lmap_sys", 1);
      v144 = getID();
      fclID = v144;
      v146 = (loc_1CDE7F0)(0);
      Unload(v146, "lmap_sys", 0);
      v148 = lmapwk;
      cam = v148->cam;
      p_object = &cam->_object;
      cam->eyeBasePos.x = LmapCameraPar->Pos.x;
      cam->eyeBasePos.y = LmapCameraPar->Pos.y;
      cam->eyeBasePos.z = LmapCameraPar->Pos.z;
      cam->tgtBasePos.x = LmapCameraPar->Tgt.x;
      cam->tgtBasePos.y = LmapCameraPar->Tgt.y;
      v152 = LmapCameraPar->Tgt.z;
      cam->tgtBasePos.w = 1.0;
      cam->tgtBasePos.z = v152;
      v153 = LmapCameraPar->Fov * 0.017453292;
      dds3CameraObjectBasicSetFovy(p_object, v153);
      v154 = LmapCameraPar->Fov * 0.017453292;
      ScreenParam->fovy = v154;
      set_fieldOfView(LMAP_MANAGER->myCamera, v154, 0);
      FldWnd_SetFlagDraw(1);
      M_InitLight();
      lmapDestMarkDraw();
      goto LABEL_346;
    case 0xA:
      if (fmProcessChk())
        goto LABEL_346;
      if ((u32)sub_1B340E0(0, v45))
      {
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 0);
        cmpProcessStartEx(1);
        v8 = 8;
        goto LABEL_344;
      }
      gLMapCampMcLoadEnd = 1;
      basic = dds3GetActiveScene();
      dds3SceneBasicVisible(basic, 0);
      if (!(u32)(loc_1CDEA20)(0))
        dds3AdminiCallSequence4(8, 0, 0, 0);
      goto LABEL_522;
    case 0xB:
      v47 = UpdateAutoMove();
      if (v47 == 1)
      {
        v55 = 13;
        v56 = lmapwk;
        v56->cnt_moveMap = 0;
        goto LABEL_410;
      }
      if (v47 == 2)
      {
        v50 = lmapwk;
        v50->cnt_moveMap = 0;
        v52 = get_Instance(0);
        ItfButtonGuideSet(v52, 0, 0);
        ButtonGuideOn();
        v55 = 6;
        v56 = lmapwk;
LABEL_410:
        v56->step_main = v55;
        goto LABEL_412;
      }
LABEL_412:
      Chr_UpdateModel(&lmapwk->chrwk);
      M_UpdateCamera();
      goto LABEL_346;
    case 0xC:
      v57 = M_MoveMap(1);
      Chr_UpdateModel(&lmapwk->chrwk);
      if (v57)
      {
        v61 = ChkWarp(lmapwk->fieldNo);
        if ((v61 & 0x80000000) == 0)
        {
          lmapwk->fieldNo = arrLmpWarp[v61]->movMapID;
        }
        v63 = lmapwk;
        v63->step_main = 13;
        v63->cnt_moveMap = 0;
      }
      goto LABEL_346;
    case 0xD:
      cnt_moveMap = lmapwk->cnt_moveMap;
      if (cnt_moveMap)
      {
        if (!v65)
        {
          cnt_moveMap = lmapwk->cnt_moveMap;
        }
        if (cnt_moveMap >= 2)
        {
          lmapwk->cnt_moveMap = 0;
          lmapwk->step_main = 14;
          goto LABEL_346;
        }
      }
      else
      {
        if (!v65)
        Release(lmap);
      }
      ++lmapwk->cnt_moveMap;
      goto LABEL_346;
    case 0xE:
      CallField();
      goto LABEL_522;
    case 0xF:
      LoadFile();
      v8 = 3;
      v66 = lmapwk;
      *(u64 *)&v66->count = 0;
      goto LABEL_345;
    case 0x10:
      switch (lmapIfMenuTask())
      {
        case 0:
          ResetPanelSub();
          FldWnd_Reset();
          FldWnd_SetFlagDraw(1);
          ButtonGuideOn();
          v72 = 6;
          v73 = lmapwk;
          v73->menu_onoff = 0;
          v73->MenuCnt = 0;
          goto LABEL_537;
        case 2:
          v176 = GBWK;
          GBWK->mapSummonID = fldGb->summonIDNext;
          v176->mapSummonUNIQ = fldGb->summonUNIQNext;
          goto LABEL_545;
        case 3:
          *(u64 *)&GBWK->mapSummonID = 0;
          goto LABEL_545;
        case 7:
          v179 = mapIfHajikiCheck();
          if (!v179)
            goto LABEL_523;
          v181 = v179;
          basic = dds3GetActiveScene();
          if (v181 == 2)
          {
            FldWnd_SetFlagDraw(1);
            ButtonGuideOn();
            v183 = &"jimusyo_hajiki2_label";
            goto LABEL_625;
          }
          if (v181 == 1)
          {
            FldWnd_SetFlagDraw(1);
            ButtonGuideOn();
            v183 = &"jimusyo_hajiki1_label";
LABEL_625:
            dds3SceneBasicStartScript(basic, *v183);
            lmapwk->mesFlag = 1;
            goto LABEL_362;
          }
LABEL_523:
          if (lmapwk->TaraSE_Flag)
          {
            sndSeStop_name("mapse_0a", 0);
            lmapwk->TaraSE_Flag = 0;
          }
          CallFastTravelFromLmap = 1;
          ndWorkActive(0);
          fldFastTravelSetup(0);
          fldFastTravelStart(1);
          v72 = 17;
LABEL_536:
          v73 = lmapwk;
LABEL_537:
          v73->step_main = v72;
LABEL_545:
          M_UpdateCamera();
          break;
        case 8:
          ndWorkActive(0);
          dds3FadeOut(0, 0, 0, 0xAu);
          v72 = 21;
          goto LABEL_536;
        case 9:
          ndWorkActive(0);
          v72 = 26;
          goto LABEL_536;
        default:
          goto LABEL_545;
      }
      goto LABEL_346;
    case 0x11:
      v74 = fldFastTravelTask();
      if (v74 != 2)
      {
        if (v74 == 1)
        {
          SE(1);
          FldWnd_SetFlagDraw(1);
          ButtonGuideOn();
          ndWorkActive(1);
          v78 = lmapwk;
          v78->step_main = 6;
          v78->menu_onoff = 0;
        }
LABEL_346:
        op_Inequality(goLmapManager, 0, 0);
        return 0;
      }
      v159 = fldGb;
      fieldID = v159->fieldID;
      if (fieldID)
      {
        v159 = fldGb;
        fieldID = v159->fieldID;
        floorID = v159->floorID;
        v159->ReturnMapID = fieldID;
        v159->ReturnFloorID = floorID;
        goto LABEL_573;
      }
      if (op_Inequality(lmapJmpDataTbls, 0, 0))
      {
        fldGb->ReturnMapID = 1;
LABEL_573:
        v8 = 18;
        goto LABEL_344;
      }
      goto LABEL_573;
    case 0x12:
      if (fldFastTravelJumpCheck())
      {
        v80 = lmapwk;
        v80->step_main = 19;
        sndSeLoadId(73);
        goto LABEL_346;
      }
      fldGb->ReturnMapID = 0;
      fldFastTravelDelete();
      basic = dds3GetActiveScene();
      dds3SceneBasicStartScript(basic, "Not_FastTravel");
      lmapwk->mesFlag = 1;
LABEL_362:
      ndWorkActive(1);
LABEL_363:
      v8 = 6;
      v66 = lmapwk;
      v66->menu_onoff = 0;
      goto LABEL_345;
    case 0x13:
      if (sndSeStatus() == 2)
      {
        dds3FadeOut(0, 0, 0, 0x14u);
        sndSePlay(0);
        lmapwk->step_main = 20;
      }
      goto LABEL_346;
    case 0x14:
      if (dds3FadeCheck())
        goto LABEL_346;
      fldFastTravelDelete();
      FldWnd_CallEnd();
      ClearFldThumbnail();
      v85 = (loc_1CDEAB0)(0);
      v86 = (loc_1CDEB40)(0);
      v87 = mapFastTravel(v85, v86);
      if (v87 > 0x3F || ((1 << v87) & 0xD000000000000000LL) == 0)
        goto LABEL_522;
      delMapScene();
      basic = dds3GetActiveScene();
      dds3SceneBasicStartScript(basic, "ftravel_facility_label");
      lmapwk->step_main = 23;
      CallFastTravelFromLmap = 0;
      goto LABEL_346;
    case 0x15:
      if (dds3FadeCheck())
        goto LABEL_346;
      if (lmapwk->TaraSE_Flag)
      {
        sndSeStop_name("mapse_0a", 0);
        lmapwk->TaraSE_Flag = 0;
      }
      CallCampFromLmap = 1;
      lmapDestMarkClear();
      basic = dds3GetActiveScene();
      dds3SceneBasicVisible(basic, 0);
      ProcessStart(1);
      ButtonGuideDispOff();
      v40 = lmapwk;
      v40->step_main = 22;
      if (!v40->bSetFilter)
        goto LABEL_346;
      v40 = lmapwk;
LABEL_246:
      v40->bSetFilter = 0;
      (loc_1CDE990)(0, 0);
      goto LABEL_346;
    case 0x16:
      if (!ProcessCheck())
      {
        if (!dds3FadeCheck())
        {
          v91 = get_Instance(0);
          ItfButtonGuideSet(v91, 0, 0);
          ButtonGuideOn();
          ndWorkActive(1);
          ResetPanelSub();
          FldWnd_Reset();
          FldWnd_SetFlagDraw(1);
          basic = dds3GetActiveScene();
          dds3SceneBasicVisible(basic, 1);
          v97 = lmapwk;
          v97->menu_onoff = 0;
          v97->step_main = 6;
          M_UpdateCamera();
          CallCampFromLmap = 0;
          v100 = lmapwk;
          v101 = LmapCameraPar;
          v102 = v100->cam;
          v103 = &v102->_object;
          v102->eyeBasePos.x = v101->Pos.x;
          v102->eyeBasePos.y = v101->Pos.y;
          v102->eyeBasePos.z = v101->Pos.z;
          v102->tgtBasePos.x = v101->Tgt.x;
          v102->tgtBasePos.y = v101->Tgt.y;
          v104 = v101->Tgt.z;
          v102->tgtBasePos.w = 1.0;
          v102->tgtBasePos.z = v104;
          v105 = v101->Fov * 0.017453292;
          dds3CameraObjectBasicSetFovy(v103, v105);
          v107 = LmapCameraPar->Fov * 0.017453292;
          ScreenParam->fovy = v107;
          set_fieldOfView(LMAP_MANAGER->myCamera, v107, 0);
          M_InitLight();
          lmapDestMarkDraw();
          dds3FadeIn2(8u);
        }
      }
      goto LABEL_346;
    case 0x17:
      if (scrSearchScriptName("ftravel_facility_label"))
        goto LABEL_346;
      v109 = (loc_1CDEAB0)(0);
      v110 = (loc_1CDEB40)(0);
      v111 = mapFastTravel(v109, v110);
      switch (v111)
      {
        case '?':
          mapTitleStart(53, 0, 4, 0);
          sisetu_wait = 20;
          lmapwk->step_main = 25;
          CallFastTravelFromLmap = 0;
          goto LABEL_346;
        case '>':
          dds3AdminiCallSequence2(40, 0, 0, 0);
          autoSaveDisable = 0;
          break;
        case '<':
          mapTitleStart(50, 0, 4, 0);
          sisetu_wait = 24;
          lmapwk->step_main = 24;
          autoSaveDisable = 0;
          CallFastTravelFromLmap = 0;
          goto LABEL_346;
      }
      CallFastTravelFromLmap = 0;
      goto LABEL_522;
    case 0x18:
      if (sisetu_wait >= 1)
      {
        sisetu_wait = sisetu_wait - 1;
      }
      if (sisetu_wait)
        goto LABEL_346;
      dds3AdminiCallSequence2(11, 0, 0, 0);
      goto LABEL_307;
    case 0x19:
      v115 = sisetu_wait;
      if (v115 >= 1)
      {
        v115 = sisetu_wait;
        sisetu_wait = v115 - 1;
      }
      if (sisetu_wait)
        goto LABEL_346;
      sub_1B34910(0, 0, v2);
      HDrawSync = 0;
      dds3AdminiCallSequence4(17, 0, 0, 0);
LABEL_307:
      scrAllReleaseScript();
      goto LABEL_522;
    case 0x1A:
      basic = dds3GetActiveScene();
      dds3SceneBasicStartScript(basic, "quick_save_label");
      v8 = 27;
      goto LABEL_344;
    case 0x1B:
      if (scrSearchScriptName("quick_save_label"))
        goto LABEL_346;
      v118 = get_Instance(0);
      ItfButtonGuideSet(v118, 0, 0);
      ButtonGuideOn();
      goto LABEL_363;
    case 0x1C:
      if (!itfMsgLogPlayCheck())
      {
        v120 = get_Instance(0);
        ItfButtonGuideSet(v120, 0, 0);
        ButtonGuideOn();
        ndWorkActive(1);
        v123 = lmapwk;
        v123->menu_onoff = 0;
        v123->step_main = 6;
        FldWnd_SetFlagDraw(1);
        M_InitLight();
        lmapDestMarkDraw();
        ResetPanelSub();
        FldWnd_Reset();
      }
      goto LABEL_346;
    case 0x1D:
      if (!get_isDone(Lmapscene_asyncLoad, 0))
        goto LABEL_346;
      p_Dependent = &Dependent;
      v131 = p_Dependent;
      Unload(v131, akey_LmapBack, 0);
      Unload(Dependent, akey_Lmap, 0);
      v8 = 1;
LABEL_343:
      goto LABEL_344;
    default:
      goto LABEL_346;
  }
}

// 0x1cc6290
void lmapResetCampMCLoadEndFlag(void) {
  gLMapCampMcLoadEnd = 0;
  return;
}

// 0x1cc6310
s32 lmapCampMCLoadEndCheck(void) {
  return gLMapCampMcLoadEnd;
}

// 0x1cc4b10
static void Release(void) {
  struct lmap *static_fields;
  s32 size;
  s32 v10;
  struct lmap *v11;
  s32 v13;
  s32 v16;
  s32 v17;
  void *p_DestListTbl;
  s32 v21;
  s32 v22;
  s32 v25;
  void *gameObject;
  dds3ProcessID_t *proc_actwnd;
  tagM_LMAP_WORK *v35;
  tagM_LMAP_WORK *v38;
  dds3ProcessID_t *proc_effwave;
  tagM_LMAP_WORK *v40;
  tagM_LMAP_WORK *v42;
  tagM_LMAP_WORK *v46;
  dds3Basic_t *ControlScene;
  dds3Basic_t *v50;
  dds3ProcessID_t *p_drawPID;
  char *myScene;
  dds3ProcessID_t *v56;
  dds3ProcessID_t *id;

  if ((lmapwk->flag & 1) != 0)
    return;
  Unload(Dependent, "UI_map", 0);
  Unload(Dependent, "lmap", 0);
  Unload(Dependent, "lmap_sys", 0);
  Unload(Dependent, fieldUIname, 0);
  Unload(Dependent, "ui_field", 0);
  lmapJmpDataTbls = 0;
  static_fields = ((char *)static_fields + 72);
  LOWORD(static_fields[-1].ListMakeListFunc) = 0;
  LmapCameraPar = 0;
  size = DestOldList->_size;
  v10 = DestOldList->_version + 1;
  DestOldList->_size = 0;
  DestOldList->_version = v10;
  if (size >= 1)
  {
    Clear(DestOldList->_items, 0, size, 0);
  }
  DestOldList = 0;
  v11 = ((char *)v11 + 248);
  *(u64 *)&LMAP_PAD_ANALOG_MASK = 0;
  v13 = DestUpdate->_version + 1;
  DestUpdate->_size = 0;
  DestUpdate->_version = v13;
  v16 = DestNowList->_size;
  v17 = DestNowList->_version + 1;
  DestNowList->_size = 0;
  DestNowList->_version = v17;
  if (v16 >= 1)
  {
    Clear(DestNowList->_items, 0, v16, 0);
  }
  DestNowList = 0;
  p_DestListTbl = &DestListTbl;
  p_DestListTbl = 0;
  v21 = DestTextList->_size;
  v22 = DestTextList->_version + 1;
  DestTextList->_size = 0;
  DestTextList->_version = v22;
  if (v21 >= 1)
  {
    Clear(DestTextList->_items, 0, v21, 0);
  }
  DestTextList = 0;
  DestNowChapter = 0;
  v25 = DestNowChapter->_version + 1;
  DestNowChapter->_size = 0;
  DestNowChapter->_version = v25;
  Destroy_61007920(backObjIns01, 0);
  Destroy_61007920(backObjIns02, 0);
  HDrawSync = 0;
  gameObject = get_gameObject(map_win, 0);
  SetActive(gameObject, 1, 0);
  backObjIns01 = 0;
  backObjIns02 = 0;
  GuideObjClr();
  lmapDestMarkClear();
  scrAllReleaseScript();
  proc_actwnd = lmapwk->proc_actwnd;
  lmapwk->flag &= ~2u;
  ActWnd_Finish(proc_actwnd);
  v35 = lmapwk;
  v35->proc_actwnd = 0;
  FldWnd_ProcessEnd();
  EffGrid_Finish(lmapwk->proc_effgrid);
  v38 = lmapwk;
  v38->proc_effgrid = 0;
  proc_effwave = lmapwk->proc_effwave;
  id = proc_effwave;
  if (proc_effwave)
  {
    dds3KillProcess(id, 1);
  }
  v40 = lmapwk;
  v40->proc_effwave = 0;
  ListProcessEnd();
  mapMenuProcessEnd();
  v42 = lmapwk;
  v42->pDatNpc = 0;
  eglDelMesh(waveMesh);
  if (lmapwk->hModel_yaso)
  {
    if (gFilterAlpha < 1)
    {
      goto LABEL_43;
    }
    gFilterAlpha = 0;
LABEL_43:
    dds3FilterClear();
    v46 = lmapwk;
    v46->hModel_yaso = 0;
    goto LABEL_45;
  }
LABEL_45:
  Delete(0);
  fclID = 0;
  ControlScene = dds3GetControlScene();
  if (ControlScene)
  {
    v50 = ControlScene;
    dds3Delete(v50);
  }
  p_drawPID = &lmapwk->drawPID;
  if (!!dds3ExistProcess(&lmapwk->drawPID))
  {
    v56 = &lmapwk->drawPID;
    dds3KillProcess(v56, 0);
  }
  myScene = goLmapManager->myScene;
  UnloadSceneAsync(myScene, 0);
  sdfMemRelease();
  lmapwk->flag |= 1u;
  p2sdUnLoadAllSMGFile();
}

// 0x1cc6a50
static void Shutdown(dds3ProcessID_t *id) {
  Release(lmap);
  ndWorkActive(0);
  if (!op_Inequality(goLmapManager, 0, 0))
  {
    goto LABEL_8;
  }
  DeleteObj(goLmapManager, 0);
  goLmapManager = 0;
LABEL_8:
  lmapwk = 0;
}

// 0x1cc6970
static void M_FreeTex(void) {
  ;
}

// 0x1cc1830
static s32 MskR1Task(void) {
  s32 v3;
  s32 v4;
  Il2CppObject *workdata;
  s64 naturalAligment;
  Il2CppObject *v15;
  s64 v16;
  dds3Basic_t *scene;

  if (lmapwk->menu_onoff)
    return 0;
  if (!evtBitCheck(10018) || !CHECK_TRIG(8200, 1))
    return 0;
  v3 = mapIfHajikiCheck();
  if (v3)
  {
    v4 = v3;
    scene = dds3GetActiveScene();
    if (v4 == 2)
    {
      dds3SceneBasicStartScript(scene, "jimusyo_hajiki2_label");
      lmapwk->mesFlag = 1;
      return 0;
    }
  }
  if (lmapwk->TaraSE_Flag)
  {
    sndSeStop_name("mapse_0a", 0);
    lmapwk->TaraSE_Flag = 0;
  }
  SE(17);
  ndWorkActive(0);
  workdata = g_mainPID_FLDWND->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != tagLMAP_FLDWND_WORK)
    {
      v15 = workdata;
      goto LABEL_51;
    }
  }
  HIDWORD(workdata[3].klass) = 0;
  v15 = g_mainPID_FLDWND->workdata;
  if (!v15)
    goto LABEL_47;
  goto LABEL_45;
  if (v15)
  {
LABEL_45:
    if (v15->klass->_2.naturalAligment >= (u32)v16 && (tagLMAP_FLDWND_WORK *)v15->klass->_2.typeHierarchy[v16 - 1] == tagLMAP_FLDWND_WORK)
    {
      goto LABEL_47;
    }
LABEL_51:
  }
LABEL_47:
  BYTE5(v15[3].klass) &= ~2u;
  lmapwk->bDrawActWin = 0;
  CallFastTravelFromLmap = 1;
  fldFastTravelSetup(0);
  fldFastTravelStart(1);
  lmapwk->step_main = 17;
  return 1;
}

// 0x1cc6040
s32 mapIfHajikiCheck(void) {
  if (evtBitCheck(1481) && !evtBitCheck(218) || evtBitCheck(55) && !evtBitCheck(57) || evtBitCheck(90) && !evtBitCheck(1152) || evtBitCheck(146) && !evtBitCheck(147) || evtBitCheck(175) && !evtBitCheck(176))
  {
    return 2;
  }
  if (evtBitCheck(344))
    return 2;
  return 0;
}

// 0x1cb9420
static void M_DrawBG(void) {
  ;
}

// 0x1cba5f0
static void M_InitScene(void) {
  u32 v1;
  dds3Basic_t *scene;

  scene = dds3AddScene();
  dds3SetControlScene(scene);
  dds3SetActiveScene(scene);
  v1 = dds3SerializeID();
  dds3AreaBasicAdd(v1, "lmap");
}

// 0x1cc6980
static void M_DeleteScene(void) {
  dds3Basic_t *ControlScene;
  dds3Basic_t *v3;

  ControlScene = dds3GetControlScene();
  if (!ControlScene)
    return;
  v3 = ControlScene;
  dds3Delete(v3);
}

// 0x1cba6f0
static void M_InitCamera(void) {
  struct lmap *static_fields;
  tagLMAP_CAMERA_WORK *cam;
  f32 z;
  f32 v7;
  u32 v9;
  tagLMAP_CAMERA_WORK *v10;
  f32 x;
  f32 y;
  f32 v13;
  f32 w;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  dds3Basic_t *v19;
  dds3Basic_t *ControlScene;
  dds3Basic_t *object;
  f32 v26;
  void *myCamera;
  sdfVector4_t v28;
  sdfVector4_t v29;
  sdfVector4_t v30;

  cam = lmapwk->cam;
  cam->eyeBasePos.x = LmapCameraPar->Pos.x;
  cam->eyeBasePos.y = LmapCameraPar->Pos.y;
  z = LmapCameraPar->Pos.z;
  cam->eyeBasePos.w = 1.0;
  cam->eyeBasePos.z = z;
  cam->tgtBasePos.x = LmapCameraPar->Tgt.x;
  cam->tgtBasePos.y = LmapCameraPar->Tgt.y;
  v7 = LmapCameraPar->Tgt.z;
  cam->tgtBasePos.w = 1.0;
  cam->tgtBasePos.z = v7;
  if (!(u32)static_fields)
  v9 = dds3SerializeID();
  v10 = lmapwk->cam;
  x = v10->eyeBasePos.x;
  y = v10->eyeBasePos.y;
  v13 = v10->eyeBasePos.z;
  w = v10->eyeBasePos.w;
  v15 = v10->tgtBasePos.x;
  v16 = v10->tgtBasePos.y;
  v17 = v10->tgtBasePos.z;
  v18 = v10->tgtBasePos.w;
  v29.x = x;
  v29.y = y;
  v29.z = v13;
  v29.w = w;
  v30.x = v15;
  v30.y = v16;
  v30.z = v17;
  v30.w = v18;
  *(u64 *)&v28.x = 0;
  v19 = dds3CameraObjectBasicAddTypeLookAt(v9, v29, v30, v28);
  cam->_object = v19;
  dds3SetBasicName(lmapwk->cam->_object, "lmap_camera");
  dds3SetRadiusPoseSet(&lmapwk->cam->_object, 10.0);
  dds3ObjectBaseCreateMover(&lmapwk->cam->_object);
  ControlScene = dds3GetControlScene();
  object = lmapwk->cam->_object;
  SetActiveCamera(ControlScene, object, 0);
  v26 = LmapCameraPar->Fov * 0.017453292;
  myCamera = LMAP_MANAGER->myCamera;
  HScreenParam->fovy = v26;
  ScreenParam->fovy = v26;
  set_fieldOfView(myCamera, v26, 0);
  InitCameraAll(goLmapManager, 0);
}

// 0x1cbaa00
static void M_UpdateCamera(void) {
  tagLMAP_CAMERA_WORK *cam;
  dds3Basic_t *p_object;
  f32 z;
  f32 v9;
  f32 v12;
  void *myCamera;
  tagLMAP_CHR_WORK *chrwk;
  f32 x;
  f32 y;
  f32 v18;
  f32 w;
  sdfVector4_t v20;
  struct sdfVector4_t tgtBasePos;
  struct sdfVector4_t tgtPos;
  f32 *p_x;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v29;
  float32x4_t *v31;
  struct sdfVector4_t v33;
  tagLMAP_CAMERA_WORK *v35;
  sdfVector4_t *p_tgtPos;
  tagLMAP_CAMERA_WORK *v38;
  f32 v39;
  s64 v40;
  struct sdfVector4_t eyeBasePos;
  tagLMAP_CAMERA_WORK *v43;
  sdfVector4_t *p_eyePos;
  tagLMAP_CAMERA_WORK *v49;
  f32 v50;
  f32 v51;
  dds3Basic_t *object;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v60;
  sdfVector4_t pos1;
  sdfVector4_t v72;
  sdfVector4_t v73;
  sdfVector4_t v74;

  *(u64 *)&pos1.x = 0;
  *(u64 *)&pos1.z = 0;
  cam = lmapwk->cam;
  p_object = &cam->_object;
  cam->eyeBasePos.x = LmapCameraPar->Pos.x;
  cam->eyeBasePos.y = LmapCameraPar->Pos.y;
  cam->eyeBasePos.z = LmapCameraPar->Pos.z;
  cam->tgtBasePos.x = LmapCameraPar->Tgt.x;
  cam->tgtBasePos.y = LmapCameraPar->Tgt.y;
  z = LmapCameraPar->Tgt.z;
  cam->tgtBasePos.w = 1.0;
  cam->tgtBasePos.z = z;
  v9 = LmapCameraPar->Fov * 0.017453292;
  dds3CameraObjectBasicSetFovy(p_object, v9);
  v12 = LmapCameraPar->Fov * 0.017453292;
  myCamera = LMAP_MANAGER->myCamera;
  ScreenParam->fovy = v12;
  set_fieldOfView(myCamera, v12, 0);
  chrwk = lmapwk->chrwk;
  x = chrwk->pos.x;
  y = chrwk->pos.y;
  v18 = chrwk->pos.z;
  w = chrwk->pos.w;
  v72.x = x;
  v72.y = y;
  v72.z = v18;
  v72.w = w;
  pos1.x = x;
  pos1.y = y;
  pos1.z = v18;
  pos1.w = w;
  GetCameraBasePos(&pos1, v72);
  v20 = pos1;
  vct_A = v20;
  tgtBasePos = lmapwk->cam->tgtBasePos;
  vct_B = tgtBasePos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  tgtPos = lmapwk->cam->tgtPos;
  vct_B = tgtPos;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  v25 = p_x[6];
  v26 = p_x[4];
  v27 = p_x[5];
  v29 = 0.05;
  if (sqrtf((f32)((f32)(v26 * v26) + (f32)(v27 * v27)) + (f32)(v25 * v25)) >= 128.0)
    v29 = 1.0;
  v60 = v29;
  v31[1] = vmulq_n_f32(v31[1], v60);
  v33 = lmapwk->cam->tgtPos;
  vct_B = v33;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v35 = lmapwk->cam;
  p_tgtPos = &v35->tgtPos;
  *p_tgtPos = vct_A;
  v38 = lmapwk->cam;
  v39 = v38->tgtPos.x;
  v40 = *(u64 *)&v38->tgtPos.z;
  v38->tgtPos.y = 0.0;
  vct_A.x = v39;
  vct_A.y = 0.0;
  *(u64 *)&vct_A.z = v40;
  eyeBasePos = lmapwk->cam->eyeBasePos;
  vct_B = eyeBasePos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v43 = lmapwk->cam;
  p_eyePos = &v43->eyePos;
  *p_eyePos = vct_A;
  v49 = lmapwk->cam;
  v50 = v49->tgtPos.x;
  v51 = v49->tgtPos.y;
  object = v49->_object;
  v53 = v49->tgtPos.z;
  v54 = v49->tgtPos.w;
  v55 = v49->eyePos.x;
  v56 = v49->eyePos.y;
  v57 = v49->eyePos.z;
  v58 = v49->eyePos.w;
  v73.x = v50;
  v73.y = v51;
  v73.z = v53;
  v73.w = v54;
  v74.x = v55;
  v74.y = v56;
  v74.z = v57;
  v74.w = v58;
  dds3CameraObjectBasicSetTgtCam(object, v73, v74);
  MoveCameraAll(goLmapManager, lmapwk->cam->eyePos, 0);
}

// 0x1cbb290
static void M_InitLight(void) {
  sdfVector4_t v3;
  sdfVector4_t v4;
  sdfVector4_t v5;
  sdfVector4_t v6;
  sdfVector4_t v7;

  v3.x = 0.0;
  v3.y = 0.0;
  v3.z = 0.0;
  v3.w = 0.0;
  dds3SetLightColor(0, 1u, v3);
  v4.x = 0.0;
  v4.y = 0.0;
  v4.w = 0.0;
  v4.z = 1.0;
  dds3SetLightColor(0, 2u, v4);
  v5.w = 0.0;
  v5.x = 1.0;
  v5.y = 1.0;
  v5.z = 1.0;
  dds3SetLightColor(0, 0, v5);
  v6.w = 0.0;
  v6.x = LmapCameraPar[31];
  v6.y = LmapCameraPar[32];
  v6.z = LmapCameraPar[33];
  dds3SetLightDir(0, 0, v6);
  v7.w = 1.0;
  v7.x = 0.2;
  v7.y = 0.2;
  v7.z = 0.2;
  dds3SetAmbientColor(0, v7);
}

// 0x1cbfb60
static s32 M_MoveMap(s32 mode) {
  sdfVector4_t *v4;
  s32 cnt_moveMap;
  u32 v10;
  tagLMAP_CHR_WORK *chrwk;
  tagLMAP_CHR_UTIL_WORK *scale;
  f32 x;
  f32 y;
  f32 z;
  struct sdfVector4_t v16;
  struct sdfVector4_t v18;
  f32 *p_x;
  f32 v20;
  f32 v21;
  f32 v22;
  tagLMAP_CAMERA_WORK *cam;
  sdfVector4_t *p_tgtDir;
  f32 v30;
  tagLMAP_CAMERA_WORK *v32;
  f32 v33;
  f32 v34;
  f32 v35;
  struct sdfVector4_t v36;
  struct sdfVector4_t eyePos;
  struct sdfVector4_t v38;
  struct sdfVector4_t v40;
  f32 *v41;
  f32 v42;
  f32 v43;
  f32 v44;
  tagLMAP_CAMERA_WORK *v47;
  sdfVector4_t *p_eyeDir;
  tagLMAP_CHR_WORK *v52;
  tagLMAP_CHR_UTIL_WORK *v53;
  f32 v54;
  f32 v55;
  f32 v56;
  tagM_LMAP_WORK *v57;
  struct sdfVector4_t tgtPos;
  f32 *v60;
  struct sdfVector4_t v61;
  f32 *v62;
  f32 v63;
  f32 v64;
  f32 v65;
  tagLMAP_CAMERA_WORK *v68;
  sdfVector4_t *v70;
  f32 v73;
  f32 *v74;
  tagLMAP_CAMERA_WORK *v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 v80;
  struct sdfVector4_t v81;
  struct sdfVector4_t v84;
  f32 *v85;
  f32 v86;
  f32 v87;
  f32 v88;
  tagLMAP_CAMERA_WORK *v91;
  sdfVector4_t *v93;
  tagLMAP_CHR_WORK *v94;
  tagLMAP_CAMERA_WORK *v96;
  dds3Basic_t *object;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 w;
  f32 v102;
  f32 v103;
  f32 v104;
  f32 v105;
  struct sdfVector4_t v107;
  tagLMAP_CAMERA_WORK *v108;
  sdfVector4_t *p_tgtPos;
  struct sdfVector4_t v112;
  tagLMAP_CAMERA_WORK *v113;
  sdfVector4_t *p_eyePos;
  tagLMAP_CHR_WORK *v116;
  struct sdfVector4_t v121;
  struct sdfVector4_t v122;
  struct sdfVector4_t tgtDir;
  struct sdfVector4_t eyeDir;
  sdfVector4_t v143;
  sdfVector4_t v144;
  sdfVector4_t v145;

  v4 = NewSpecific(sdfVector4_t, 2u);
  cnt_moveMap = lmapwk->cnt_moveMap;
  if (cnt_moveMap)
    goto LABEL_5;
  lmapwk->chrwk->flags |= 0x80u;
  M_MoveMap_v_length = 0.0;
  M_MoveMap_t_length = 0.0;
  if (mode != 1)
  {
    if (mode)
      return -1;
    chrwk = lmapwk->chrwk;
    scale = chrwk->scale;
    if (!scale->step)
    {
      chrwk->scl = 0.0;
      scale->fields = (tagLMAP_CHR_UTIL_WORK)0x1E000000000001LL;
    }
    x = chrwk->pos.x;
    y = chrwk->pos.y;
    z = chrwk->pos.z;
    v143.w = 1.0;
    v143.x = x;
    v143.y = y;
    v143.z = z;
    v4[0].x = x;
    v4[0].y = y;
    v4[0].z = z;
    *(u32 *)&v4[0].w = 1065353216;
    GetCameraBasePos(&v4[1], v143);
    lmapwk->cam->tgtPos = v4[0];
    v16 = v4[1];
    vct_A = v16;
    v18 = v4[0];
    vct_B = v18;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    v20 = p_x[6];
    v21 = p_x[4];
    v22 = p_x[5];
    cam = lmapwk->cam;
    M_MoveMap_t_length = sqrtf((f32)((f32)(v21 * v21) + (f32)(v22 * v22)) + (f32)(v20 * v20));
    p_tgtDir = &cam->tgtDir;
    *p_tgtDir = vct_A;
    v30 = v4[0].y;
    v32 = lmapwk->cam;
    v4[0].x = v4[0].x + (f32)(LmapCameraPar[6] * 0.25);
    v4[0].y = v30 + (f32)(LmapCameraPar[7] * 0.25);
    v33 = v4[0].z;
    v34 = LmapCameraPar[8];
    *(u32 *)&v4[0].w = 1065353216;
    v4[0].z = v33 + (f32)(v34 * 0.25);
    v32->eyePos.x = LmapCameraPar[6];
    v32->eyePos.y = LmapCameraPar[7];
    v35 = LmapCameraPar[8];
    v32->eyePos.w = 1.0;
    v32->eyePos.z = v35;
    v36 = v4[1];
    v121 = v4[1];
    v36 = v121;
    v122 = v36;
    v36 = v122;
    vct_A = v36;
    eyePos = lmapwk->cam->eyePos;
    vct_B = eyePos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v4[1] = vct_A;
    lmapwk->cam->eyePos = v4[0];
    v38 = v4[1];
    vct_A = v38;
    v40 = v4[0];
    vct_B = v40;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v41 = &vf00.x;
    v42 = v41[4];
    v43 = v41[5];
    v44 = v41[6];
    M_MoveMap_v_length = sqrtf((f32)((f32)(v42 * v42) + (f32)(v43 * v43)) + (f32)(v44 * v44));
    v47 = lmapwk->cam;
    p_eyeDir = &v47->eyeDir;
    *p_eyeDir = vct_A;
    dds3FadeIn(0xFFu, 0xFFu, 0xFFu, 0x1Eu);
    sndBgmPlay(0, 0);
LABEL_119:
    v94 = lmapwk->chrwk;
    v94->moveStat |= 2u;
    goto LABEL_72;
  }
  v52 = lmapwk->chrwk;
  v53 = v52->scale;
  if (!v53->step)
  {
    v52->scl = v52->sclDef;
    v53->fields = (tagLMAP_CHR_UTIL_WORK)0x1E000000010001LL;
  }
  v54 = v52->pos.x;
  v55 = v52->pos.y;
  v56 = v52->pos.z;
  v4[0].x = v54;
  v4[0].y = v55;
  v4[0].z = v56;
  v57 = lmapwk;
  *(u32 *)&v4[0].w = 1065353216;
  tgtPos = v57->cam->tgtPos;
  LODWORD(v57) = (u8)byte_5755EF5;
  v4[1] = tgtPos;
  v60 = &vf00.x;
  v60[4] = v54;
  v60[5] = v55;
  v60[6] = v56;
  v60[7] = 1.0;
  v61 = v4[1];
  vct_B = v61;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v62 = &vf00.x;
  v63 = v62[6];
  v64 = v62[4];
  v65 = v62[5];
  v68 = lmapwk->cam;
  M_MoveMap_t_length = sqrtf((f32)((f32)(v64 * v64) + (f32)(v65 * v65)) + (f32)(v63 * v63));
  v70 = &v68->tgtDir;
  *v70 = vct_A;
  v73 = v4[0].y;
  v74 = LmapCameraPar;
  v75 = lmapwk->cam;
  v76 = v4[0].x + (f32)(v74[6] * 0.25);
  v77 = v4[0].z;
  v4[0].x = v76;
  v78 = v73 + (f32)(v74[7] * 0.25);
  v4[0].y = v78;
  v79 = v74[8];
  *(u32 *)&v4[0].w = 1065353216;
  v80 = v77 + (f32)(v79 * 0.25);
  v4[0].z = v80;
  v81 = v75->eyePos;
  LODWORD(v75) = (u8)byte_5755EF5;
  v4[1] = v81;
  vct_A.x = v76;
  vct_A.y = v78;
  vct_A.z = v80;
  vct_A.w = 1.0;
  v84 = v4[1];
  vct_B = v84;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v85 = &vf00.x;
  v86 = v85[4];
  v87 = v85[5];
  v88 = v85[6];
  M_MoveMap_v_length = sqrtf((f32)((f32)(v86 * v86) + (f32)(v87 * v87)) + (f32)(v88 * v88));
  v91 = lmapwk->cam;
  v93 = &v91->eyeDir;
  *v93 = vct_A;
  dds3FadeOut(0, 0, 0, 0x1Eu);
  sndBgmFadeOut();
  goto LABEL_119;
LABEL_5:
  if (cnt_moveMap == 1)
  {
    lmapwk->flag |= 2u;
    if (lmapwk->cnt_moveMap <= 29)
    {
LABEL_121:
      if (M_MoveMap_t_length <= 0.0)
      {
        goto LABEL_124;
      }
      tgtDir = lmapwk->cam->tgtDir;
      vct_A = tgtDir;
      vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x3D088889u));
      v107 = lmapwk->cam->tgtPos;
      vct_B = v107;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v108 = lmapwk->cam;
      p_tgtPos = &v108->tgtPos;
      *p_tgtPos = vct_A;
LABEL_124:
      if (M_MoveMap_v_length <= 0.0)
      {
        goto LABEL_126;
      }
      eyeDir = lmapwk->cam->eyeDir;
      vct_A = eyeDir;
      vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x3D088889u));
      v112 = lmapwk->cam->eyePos;
      vct_B = v112;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v113 = lmapwk->cam;
      p_eyePos = &v113->eyePos;
      *p_eyePos = vct_A;
LABEL_126:
      v96 = lmapwk->cam;
      object = v96->_object;
      v98 = v96->tgtPos.x;
      v99 = v96->tgtPos.y;
      v100 = v96->tgtPos.z;
      w = v96->tgtPos.w;
      v102 = v96->eyePos.x;
      v103 = v96->eyePos.y;
      v105 = v96->eyePos.z;
      v104 = v96->eyePos.w;
      v144.x = v98;
      v144.y = v99;
      v144.z = v100;
      v144.w = w;
      v145.x = v102;
      v145.y = v103;
      v145.z = v105;
      v145.w = v104;
      dds3CameraObjectBasicSetTgtCam(object, v144, v145);
      goto LABEL_74;
    }
LABEL_73:
LABEL_74:
    MoveCameraAll(goLmapManager, lmapwk->cam->eyePos, 0);
    ++lmapwk->cnt_moveMap;
    return 0;
LABEL_72:
    if (lmapwk->cnt_moveMap <= 29)
      goto LABEL_121;
    goto LABEL_73;
  }
  if (v10)
  {
    if (cnt_moveMap < 30)
      goto LABEL_71;
  }
  else
  {
    if (lmapwk->cnt_moveMap < 30)
    {
LABEL_71:
      goto LABEL_72;
    }
  }
  v116 = lmapwk->chrwk;
  lmapwk->cnt_moveMap = 0;
  v116->moveStat &= ~2u;
  return 1;
}

// 0x1cc1e30
static s8 CtrlActionWindow(void) {
  tagLMAP_CHR_WORK *chrwk;
  u32 flags;
  s32 basePointNo;
  s16 v6;
  u8 v8;
  u16 v10;
  _BOOL4 v11;
  tagLMAP_CHR_WORK *v12;
  s32 nextPointNo;
  s16 v14;
  s32 ScreenSaveW;
  s32 ScreenSaveH;
  tagM_LMAP_WORK *lmapwk_local;
  Il2CppObject *workdata;
  s64 naturalAligment;
  tagM_LMAP_WORK *v27;
  s32 width;
  tagM_LMAP_WORK *v30;
  tagM_LMAP_WORK *v32;
  bool v33;
  tagM_LMAP_WORK *v35;
  s8 v36;
  bool v37;
  tagM_LMAP_WORK *v38;
  tagLMAP_MSG_WORK *msgwk;
  char *pScrLabel;
  tagM_LMAP_WORK *v43;
  Il2CppObject *v46;
  s32 v49;
  tagM_LMAP_WORK *v51;
  char *v53;
  tagM_LMAP_WORK *v56;
  s64 v58;
  u32 v61;
  tagLMAP_MSG_WORK *v62;
  s32 ret;
  s64 v68;
  tagLMAP_MSG_WORK *v69;
  bool v70;
  char **v71;
  tagM_LMAP_WORK *v73;
  s64 v74;
  tagLMAP_NPC_CB *cb;
  s64 v76;
  s16 v77;
  char v78;
  tagLMAP_CHR_WORK *v80;
  s8 moveId;
  tagLMAP_CHR_UTIL_WORK *autom;
  tagM_LMAP_WORK *v85;
  tagM_LMAP_WORK *v89;
  s32 scrType;
  bool v91;
  char **v92;
  s64 v94;
  s32 v95;
  s32 v96;
  char v97;
  s64 v99;
  s8 v100;
  tagLMAP_CHR_WORK *v101;
  tagLMAP_CHR_WORK *v104;

  chrwk = lmapwk->chrwk;
  flags = chrwk->flags;
  if ((flags & 0x20000000) == 0)
  {
    v8 = 0;
    v10 = -1;
    v11 = (flags >> 29) & 1;
    goto LABEL_18;
  }
  basePointNo = (u16)lmapwk->chrwk->basePointNo;
  v6 = 0;
  while ((dmLMAP_POINT_NO(v6) & 0x8000) == 0)
  {
    if (basePointNo == (u16)dmLMAP_POINT_NO(v6))
      goto LABEL_16;
    ++v6;
  }
  v6 = -1;
LABEL_16:
  v8 = dmLMAP_POINT_FLAG(v6);
  v10 = dmLMAP_POINT_ID(v6);
  v11 = (flags >> 29) & 1;
LABEL_18:
  if ((flags & 0x20000000) != 0)
    goto LABEL_33;
  v12 = lmapwk->chrwk;
  if ((v12->flags & 0x40000000) == 0)
    goto LABEL_33;
  nextPointNo = (u16)v12->nextPointNo;
  v14 = 0;
  while ((dmLMAP_POINT_NO(v14) & 0x8000) == 0)
  {
    if (nextPointNo == (u16)dmLMAP_POINT_NO(v14))
      goto LABEL_32;
    ++v14;
  }
  v14 = -1;
LABEL_32:
  v8 = dmLMAP_POINT_FLAG(v14);
  v10 = dmLMAP_POINT_ID(v14);
  v11 = 1;
LABEL_33:
  ScreenSaveW = lmapwk->ScreenSaveW;
  if (ScreenSaveW != get_width(0))
    goto LABEL_245;
  ScreenSaveH = lmapwk->ScreenSaveH;
  if (ScreenSaveH != get_height(0))
  {
LABEL_245:
    lmapwk_local = lmapwk;
    *(u16 *)&lmapwk_local->bDrawActWin = 0;
    lmapwk_local->panel_tblNo = -1;
    workdata = g_mainPID_FLDWND->workdata;
    if (!workdata)
      goto LABEL_54;
    goto LABEL_52;
    if (!workdata)
    {
LABEL_54:
      HIDWORD(workdata[3].klass) = 0;
      v27 = lmapwk;
      width = get_width(0);
      v27->ScreenSaveW = width;
      v30 = lmapwk;
      v30->ScreenSaveH = get_height(0);
      goto LABEL_55;
    }
LABEL_52:
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != tagLMAP_FLDWND_WORK)
    {
      goto LABEL_241;
    }
    goto LABEL_54;
  }
LABEL_55:
  v32 = lmapwk;
  if (v32->bDrawActWin)
    goto LABEL_61;
  if (v32->msgwk->step)
    goto LABEL_61;
  SetPanel_2(v11, v10, v8);
  v36 = 0;
  CtrlActionWindow_fieldNo = lmapwk->fieldNo;
  return v36;
LABEL_61:
  if (!v11)
  {
    v33 = 0;
    goto LABEL_68;
  }
  v33 = (u16)CtrlActionWindow_fieldNo == v10;
LABEL_68:
  ResetPanel(v33);
  v35 = lmapwk;
  if (v35->bDrawActWin)
  {
    if (v35->msgwk->step)
      goto LABEL_92;
    if ((v35->chrwk->moveStat & 1) != 0)
      goto LABEL_92;
    v37 = CHECK_TRIG(4096, 1);
    if (v37)
    {
      if (!lmapwk->menu_onoff)
      {
        SetMessage(lmap);
        lmapwk->msgwk->type = lmapwk->panel_type;
        ResetPanelSub();
        return 0;
      }
    }
    goto LABEL_92;
  }
LABEL_92:
  v38 = lmapwk;
  msgwk = v38->msgwk;
  if (msgwk->step < 1)
    return 0;
  v38 = lmapwk;
  msgwk = v38->msgwk;
  v36 = 0;
  switch (msgwk->type)
  {
    case 1:
    case 2:
      pScrLabel = v38->pScrLabel;
      if (scrSearchScriptName(pScrLabel))
        return 0;
      v51 = lmapwk;
      v51->pScrLabel = 0;
      lmapwk->msgwk->step = 0;
      ndWorkActive(1);
      v49 = 0;
      goto LABEL_169;
    case 3:
      ButtonGuideDispOff();
      v43 = lmapwk;
      if (v43->msgwk->step == 1)
      {
        v46 = g_mainPID_FLDWND->workdata;
        if (!v46)
          goto LABEL_159;
        goto LABEL_157;
        if (!v46)
LABEL_157:
LABEL_159:
        BYTE5(v46[3].klass) |= 8u;
        workdata = g_mainPID_FLDWND->workdata;
        if (!workdata)
          goto LABEL_167;
LABEL_165:
        if (workdata->klass->_2.naturalAligment >= (u32)v68 && (tagLMAP_FLDWND_WORK *)workdata->klass->_2.typeHierarchy[v68 - 1] == tagLMAP_FLDWND_WORK)
        {
          goto LABEL_167;
        }
LABEL_241:
        workdata = g_mainPID_FLDWND->workdata;
        if (!workdata)
        {
LABEL_167:
          v49 = 1;
          v69 = lmapwk->msgwk;
          BYTE5(workdata[3].klass) &= ~2u;
          goto LABEL_168;
        }
        goto LABEL_165;
      }
      v53 = v43->pScrLabel;
      if (scrSearchScriptName(v53))
        return 0;
      v85 = lmapwk;
      v85->pScrLabel = 0;
      SetPadEnable(1);
      FldWnd_SetFlagDraw(1);
      v89 = lmapwk;
      scrType = (u8)arrLmpWarp[v89->warpTblNo]->scrType;
      if (scrType == 1)
      {
        v89 = lmapwk;
        v36 = 0;
        v89->msgwk->step = 1;
        return v36;
      }
      if (scrType)
        return 0;
      v89 = lmapwk;
      v69 = v89->msgwk;
      v49 = 0;
LABEL_168:
      v69->step = 0;
LABEL_169:
      v70 = evtBitCheck(10018);
      if (v70)
        v71 = &"LMAP01";
      else
        v71 = &"LMAP03";
      ButtonGuideDispSet(*v71, 1, 90);
      v73 = lmapwk;
      v73->chrwk->moveStat &= ~4u;
      v36 = 2;
      switch (v73->msgwk->type)
      {
        case 1:
        case 2:
          v74 = 32;
          cb = v73->npcwk->cb;
          while (1)
          {
            v76 = *(s64 *)((char *)&cb->obj.klass + v74);
            if ((*(u8 *)(*(u64 *)(v76 + 16) + 102) & 4) != 0)
              break;
            v74 += 8;
            v36 = 0;
            if (v74 == 552)
              return v36;
          }
          v91 = evtBitCheck(10018);
          if (v91)
            v92 = &"LMAP01";
          else
            v92 = &"LMAP03";
          ButtonGuideDispSet(*v92, 1, 90);
          v94 = *(u64 *)(v76 + 16);
          v95 = *(u32 *)(v94 + 112);
          *(u8 *)(v94 + 102) &= ~4u;
          *(u32 *)(v94 + 112) = v95 & 0xFFEFFFFF;
          v96 = *(s16 *)(v76 + 32);
          if (v96 < 0)
            return 0;
          v97 = *(u8 *)(v94 + 99);
          *(u8 *)(v94 + 101) = v96;
          *(u8 *)(v94 + 100) = v97;
          v99 = *(u64 *)(v94 + 144);
          v100 = *(u8 *)(v94 + 97);
          *(u16 *)(v99 + 16) = 0;
          *(u16 *)(v99 + 20) = 0;
          *(u8 *)(v94 + 99) = 7;
          M_SetLockPointNpcCB(v100, 0);
          v36 = 0;
          *(u32 *)(*(u64 *)(v76 + 16) + 112) |= 0x100000u;
          v101 = lmapwk->chrwk;
          v101->moveStat |= 8u;
          break;
        case 3:
          if (v49 == 1)
            return 1;
          v73 = lmapwk;
          v36 = 0;
          v73->fieldNo = -1;
          return v36;
        case 4:
          v77 = GetNearStation();
          if (v49 == v77)
            return 0;
          v78 = v77;
          v36 = 0;
          v80 = lmapwk->chrwk;
          v80->exLineType = 1;
          moveId = v80->moveId;
          v80->moveId = 8;
          autom = v80->autom;
          v80->moveId_save = moveId;
          autom->step = 0;
          autom->count = 0;
          v80->moveNo = v49 - v78 + 8 * v78;
          return v36;
        case 7:
          return v36;
        default:
          return 0;
      }
      return v36;
    case 4:
      if (itfMsgLogPlayCheck())
      {
        set_IsStationListDisp(0, 0);
        set_IsMoneyDisp(0, 0);
        ndWorkActive(0);
        v36 = 0;
        lmapwk->msgLogFlag = 1;
        return v36;
      }
      v56 = lmapwk;
      if (!v56->msgLogFlag)
        goto LABEL_141;
      if (v56->sysClsStFlag)
        goto LABEL_138;
      goto LABEL_9006;
      if (lmapwk->sysClsStFlag)
      {
LABEL_138:
        goto LABEL_139;
      }
LABEL_9006:
      set_IsStationListDisp(1, 0);
      set_IsMoneyDisp(1, 0);
LABEL_139:
      ndWorkActive(1);
      lmapwk->msgLogFlag = 0;
LABEL_141:
      if (!ListCheckWait())
        return 0;
      v58 = *(u64 *)(*((u64 *)*((const MethodInfo *)lmap + 2).virtualMethodPointer + 12) + 160);
      *(u16 *)(v58 + 18) = ListGetSelectID();
      v62 = lmapwk->msgwk;
      v62->step = 0;
      ret = v62->ret;
      if (ret < 0)
      {
        if (!v61)
        lmapSetDestCheck(-1);
        lmapDestMarkDraw();
        ButtonGuideOn();
        v36 = 0;
        v104 = lmapwk->chrwk;
        v104->moveStat &= ~4u;
        return v36;
      }
      if (v61)
      {
        v49 = (s16)ret;
        goto LABEL_149;
      }
      else
      {
        v49 = lmapwk->msgwk->ret;
LABEL_149:
        lmapStationDestCheckSelect(v49);
        if ((v49 & 0x80000000) == 0)
          goto LABEL_169;
        return 0;
      }
      lmapStationDestCheckSelect(v49);
      if ((v49 & 0x80000000) == 0)
        goto LABEL_169;
      return 0;
    case 7:
      msgwk = lmapwk->msgwk;
      msgwk->step = 0;
      v49 = 1;
      goto LABEL_169;
    default:
      return v36;
  }
}

// 0x1cc86b0
static bool SetNpcDat(void) {
  Npc_t *pDatNpc;
  il2cpp_array_size_t max_length;
  u64 v5;
  s8 v6;
  s64 v7;
  Npc_t *v9;
  s32 flag1;

  pDatNpc = lmapwk->pDatNpc;
  if (!pDatNpc)
    return 0;
  max_length = pDatNpc->max_length;
  if ((s32)max_length < 1)
    return 0;
  v5 = 0;
  v6 = 0;
  v7 = 8 * (u32)max_length;
  do
  {
    v9 = lmapwk->pDatNpc[v5 / 8];
    if (v9->point < 0)
      goto LABEL_12;
    flag1 = (u16)v9->flag1;
    if (flag1)
      goto LABEL_18;
    goto LABEL_9001;
    if ((u16)flag1)
    {
LABEL_18:
      if (!evtBitCheck((s16)flag1))
        goto LABEL_12;
      goto LABEL_23;
    }
LABEL_9001:
LABEL_23:
    if (lmapwk->pDatNpc[v5 / 8]->flag2)
    {
      if (!evtBitCheck(lmapwk->pDatNpc[v5 / 8]->flag2))
        goto LABEL_12;
    }
    if (lmapwk->pDatNpc[v5 / 8]->flag3)
    {
      if (!evtBitCheck(lmapwk->pDatNpc[v5 / 8]->flag3))
        goto LABEL_12;
    }
    if (!SetNpcCB(v6, lmapwk->pDatNpc[v5 / 8]))
      return 0;
    ++v6;
LABEL_12:
    v5 += 8;
  }
  while (v7 != v5);
  return 1;
}

// 0x1cc82b0
static bool M_SetLockPointNpcCB(s8 charaNo, bool lockFlg) {
  s32 v7;
  tagLMAP_NPC_CB *cb;
  tagLMAP_CHR_WORK *name;
  s64 v12;

  v7 = charaNo;
  v12 = 32;
  while (1)
  {
    name = (*(Il2CppClass **)((char *)&lmapwk->npcwk->cb->obj.klass + v12))->_1.name;
    if ((u8)name->charaNo == v7)
      break;
    v12 += 8;
    if (v12 == 552)
      return 0;
  }
  return Lock_SetPointChr(lmapwk->lockwk, name, lockFlg);
}

// 0x1cc3e50
static void M_MainNpcCB(void) {
  s64 i;

  for (i = 32; i != 552; i += 8)
  {
    M_UpdateNpcCB(*(tagLMAP_NPC_CB *)((char *)&lmapwk->npcwk->cb->obj.klass + i));
  }
}

// 0x1cc3c80
static void SetAreaName(s32 linetblno) {
  s16 v3;

  if ((linetblno & 0x80000000) == 0)
  {
    v3 = dmLMAP_LINE_AREA(linetblno);
    if ((u16)v3 != (u16)lmapwk->area_no)
    {
      if (lmap_areaname[v3])
      {
        lmapwk->area_no = v3;
      }
    }
  }
}

// 0x1cb9650
static void DrawActWin(s32 a_type, f32 a_fx, f32 a_fy, f32 a_fz) {
  f32 v11;
  char *v12;
  char *LocalizeText;
  s32 v14;
  f32 v15;
  s32 v16;
  s64 y2;

  y2 = 0;
  Util_Point3To2(a_fx, a_fy, a_fz, (f32 *)&y2 + 1, &y2);
  v11 = *(f32 *)&y2;
  v12 = szLmpActwin[a_type];
  LocalizeText = GetLocalizeText(v12, 1);
  v14 = frPreCalcStrWidth(LocalizeText, 1, 1);
  v15 = *((f32 *)&y2 + 1);
  v16 = v14;
  itfDrawActWnd();
  if (v11 > 416.0)
    v11 = 416.0;
  itfFloatTo32s(v15 - (f32)(v16 >> 1), 4);
  itfFloatTo32s(v11, 3);
  itfSetActWndText(LocalizeText, 1);
}

// 0x1cc3ee0
static s32 UpdateAutoMove(void) {
  tagM_LMAP_WORK *lmapwk_local;
  s32 stepAuto;
  s32 count;
  u32 v9;
  u32 v10;
  tagLMAP_CHR_WORK *v11;
  s32 v12;
  s32 v14;
  s32 v15;
  s16 v16;
  s16 v20;
  s16 v23;
  s32 fieldNo;
  s16 v27;
  u16 PointID;
  u32 v32;
  tagM_LMAP_WORK *v33;
  s32 v34;
  u8 v35;
  tagM_LMAP_WORK *v36;
  u32 v37;
  s32 v38;
  tagM_LMAP_WORK *v39;
  s16 v40;
  tagLMAP_CHR_WORK *v42;
  tagLMAP_CHR_UTIL_WORK *scale;
  s64 v44;
  s32 v45;
  s32 v47;
  s16 v49;
  s16 v53;
  struct sdfVector4_t tgt_local;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v62;
  s32 v63;
  f32 v64;
  f32 v65;
  sdfVector4_t *p_mov;
  tagLMAP_CHR_WORK *chrwk;
  struct sdfVector4_t pos;

  lmapwk_local = lmapwk;
  stepAuto = lmapwk_local->stepAuto;
  if (stepAuto != 2)
  {
    if (stepAuto != 1)
    {
      if (stepAuto)
        return 0;
      count = lmapwk_local->count;
      if (count)
      {
        if (count < 30)
          goto LABEL_139;
        goto LABEL_55;
      }
      *(u64 *)&UpdateAutoMove_tgtPointNo = -1;
      ButtonGuideDispOff();
      GuideObjClr();
      v14 = 0;
      v12 = -1;
      while (1)
      {
        if (dmLMAP_LINE_NO(v14) < 0)
          return v12;
        if (dmLMAP_LINE_TYPE(v14) != 2)
          goto LABEL_33;
        v20 = dmLMAP_LINE_POINT_A(v14);
        MapDat_GetPointID(v20);
        v23 = dmLMAP_LINE_POINT_B(v14);
        MapDat_GetPointID(v23);
        fieldNo = (u16)lmapwk->fieldNo;
        v27 = dmLMAP_LINE_POINT_A(v14);
        PointID = MapDat_GetPointID(v27);
        if (fieldNo == PointID)
        {
          if (!v32)
          v40 = dmLMAP_LINE_POINT_B(v14);
          goto LABEL_87;
        }
        v15 = (u16)lmapwk->fieldNo;
        v16 = dmLMAP_LINE_POINT_B(v14);
        if (v15 == (u16)MapDat_GetPointID(v16))
        {
          v40 = dmLMAP_LINE_POINT_A(v14);
LABEL_87:
          v45 = v40;
          v47 = 0;
          UpdateAutoMove_tgtPointNo = v45;
          goto LABEL_94;
          while (1)
          {
LABEL_94:
            if (dmLMAP_POINT_NO(v47) < 0)
              return -2;
            v49 = dmLMAP_POINT_NO(v47);
            if (UpdateAutoMove_tgtPointNo == v49)
              break;
            ++v47;
          }
          UpdateAutoMove_tgtID = dmLMAP_POINT_ID(v47);
          UpdateAutoMove_tgtFlag = dmLMAP_POINT_FLAG(v47);
          tgt.x = (f32)dmLMAP_POINT_X(v47);
          v53 = dmLMAP_POINT_Y(v47);
          tgt.z = (f32)v53;
          pos = lmapwk->chrwk->pos;
          vct_B = pos;
          tgt_local = tgt;
          goto LABEL_104;
LABEL_105:
          goto LABEL_9002;
LABEL_104:
          vct_A = tgt_local;
          goto LABEL_105;
LABEL_9002:
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          goto LABEL_109;
LABEL_110:
          goto LABEL_9003;
LABEL_109:
          p_x = &vf00.x;
          z = p_x[6];
          x = p_x[4];
          y = p_x[5];
          goto LABEL_110;
LABEL_9003:
          v62 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
          v63 = v62;
          if (v62 == INFINITY)
            v63 = 0x80000000;
          v64 = v63;
          UpdateAutoMove_moveFrame = v63;
          v65 = 1.0 / v64;
          v65 = 1.0 / v64;
          vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v65);
          p_mov = &mov;
          goto LABEL_120;
LABEL_121:
          chrwk = lmapwk->chrwk;
          scale = chrwk->scale;
          if (scale->step)
            goto LABEL_139;
          goto LABEL_9004;
LABEL_120:
          *p_mov = vct_A;
          goto LABEL_121;
LABEL_9004:
          chrwk->scl = chrwk->sclDef;
          v44 = 0x1E000000010001LL;
          goto LABEL_138;
        }
LABEL_33:
        ++v14;
      }
    }
    if (lmapwk_local->count < UpdateAutoMove_moveFrame)
    {
      if (!v10)
      {
        lmapwk_local = lmapwk;
      }
      v11 = lmapwk_local->chrwk;
      v11->pos.x = v11->pos.x + mov.x;
      v11->pos.z = v11->pos.z + mov.z;
      if (!v10)
      {
        lmapwk_local = lmapwk;
      }
      v12 = 0;
      ++lmapwk_local->count;
      return v12;
    }
    if (v10)
    {
LABEL_55:
      v35 = lmapwk_local->stepAuto;
      v12 = 0;
      lmapwk_local->count = 0;
      lmapwk_local->stepAuto = v35 + 1;
      return v12;
    }
    lmapwk_local = lmapwk;
    goto LABEL_55;
  }
  if ((UpdateAutoMove_tgtFlag & 1) == 0)
    goto LABEL_15;
  if (v9)
  {
    v33 = lmapwk;
    v34 = v33->count;
    if (v34)
    {
LABEL_49:
      if (v34 < 25)
        goto LABEL_139;
      v33 = lmapwk;
      v12 = 1;
      v33->fieldNo = UpdateAutoMove_tgtID;
      return v12;
    }
  }
  else
  {
    v33 = lmapwk;
    v34 = v33->count;
    if (v34)
      goto LABEL_49;
  }
  dds3FadeOut(0, 0, 0, 0x19u);
  goto LABEL_139;
LABEL_15:
  if (v9)
  {
    if ((UpdateAutoMove_tgtFlag & 8) == 0)
      goto LABEL_139;
  }
  else
  {
    if ((UpdateAutoMove_tgtFlag & 8) == 0)
      goto LABEL_139;
  }
  v36 = lmapwk;
  v38 = v36->count;
  if (!v38)
  {
    if (!v37)
    {
      v36 = lmapwk;
    }
    v42 = v36->chrwk;
    scale = v42->scale;
    if (!scale->step)
    {
      v42->scl = 0.0;
      v44 = 0x1E000000000001LL;
LABEL_138:
      scale->fields = (tagLMAP_CHR_UTIL_WORK)v44;
    }
    goto LABEL_139;
  }
  if (!v37)
  {
    v36 = lmapwk;
    v38 = v36->count;
  }
  if (v38 < 30)
  {
LABEL_139:
    v12 = 0;
    ++lmapwk->count;
    return v12;
  }
  v36 = lmapwk;
  Chr_SetLinePoint(&v36->chrwk, UpdateAutoMove_tgtPointNo);
  v12 = 2;
  v39 = lmapwk;
  v39->count = 0;
  v39->stepAuto = 0;
  return v12;
}

// 0x1cc5480
static void CallField(void) {
  u64 *v1;
  void *v2;
  u8 *v3;
  u8 *v4;
  u8 *v5;
  u8 *v6;
  u8 *v7;
  u8 *v8;
  u8 *v9;
  u8 *v10;
  u8 *v11;
  u8 *v12;
  u8 *v13;
  void *v14;
  void *v15;
  void *v16;
  u8 *v17;
  u8 *v18;
  u8 *v19;
  void *v20;
  u8 *v21;
  u8 *v22;
  u8 *v23;
  u8 *v24;
  u8 *v25;
  u8 *v26;
  u8 *v27;
  u8 *v28;
  u8 *v29;
  void *v30;
  void *v31;
  void *v32;
  u8 *v33;
  void *v34;
  void *v35;
  u8 *v36;
  void *v37;
  void *v38;
  u8 *v39;
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
  u8 *v53;
  void *v54;
  char *v56;
  s32 v57;
  s32 v58;
  s32 v59;

  v1 = NewSpecific(sbyte__, 0x35u);
  v2 = NewSpecific(sbyte, 3u);
  v1[4] = v2;
  v3 = NewSpecific(sbyte, 3u);
  v3[32] = 1;
  v3[34] = 9;
  v1[5] = v3;
  v4 = NewSpecific(sbyte, 3u);
  v4[32] = 1;
  v4[34] = 10;
  v1[6] = v4;
  v5 = NewSpecific(sbyte, 3u);
  v5[32] = 1;
  v5[34] = 11;
  v1[7] = v5;
  v6 = NewSpecific(sbyte, 3u);
  v6[32] = 1;
  v6[34] = 12;
  v1[8] = v6;
  v7 = NewSpecific(sbyte, 3u);
  v7[32] = 1;
  v7[34] = 13;
  v1[9] = v7;
  v8 = NewSpecific(sbyte, 3u);
  v8[32] = 8;
  v8[34] = 16;
  v1[10] = v8;
  v9 = NewSpecific(sbyte, 3u);
  v9[32] = 2;
  v9[34] = 1;
  v1[11] = v9;
  v10 = NewSpecific(sbyte, 3u);
  v10[32] = 2;
  v10[34] = 2;
  v1[12] = v10;
  v11 = NewSpecific(sbyte, 3u);
  v11[32] = 2;
  v11[34] = 3;
  v1[13] = v11;
  v12 = NewSpecific(sbyte, 3u);
  v12[32] = 2;
  v12[34] = 4;
  v1[14] = v12;
  v13 = NewSpecific(sbyte, 3u);
  v13[32] = 2;
  v13[34] = 5;
  v1[15] = v13;
  v14 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v14, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__DA4D3DA1DAACEBA9B72635459FD6A17DA13E7530D53A4932535E6DC1D49BDE3D, 0);
  v1[16] = v14;
  v15 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v15, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__31FF2916D263036C01AA2D9B67EDC35FAFB5394851C7A7C185A89A125B80B09D, 0);
  v1[17] = v15;
  v16 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v16, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__303B5B4489AE81C98F0ACFA33ECBDFDE3B4918715B1AE08B49E9381CDB66A4A0, 0);
  v1[18] = v16;
  v17 = NewSpecific(sbyte, 3u);
  v17[32] = 3;
  v17[34] = 1;
  v1[19] = v17;
  v18 = NewSpecific(sbyte, 3u);
  v18[32] = 3;
  v18[34] = 2;
  v1[20] = v18;
  v19 = NewSpecific(sbyte, 3u);
  v19[32] = 9;
  v19[34] = 1;
  v1[21] = v19;
  v20 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v20, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__12124C735FD95B9AA2DBE65AE22452B657E5F01E313028EFCD52D58742A8C122, 0);
  v1[22] = v20;
  v21 = NewSpecific(sbyte, 3u);
  v21[32] = 15;
  v21[34] = 1;
  v1[23] = v21;
  v22 = NewSpecific(sbyte, 3u);
  v22[32] = 4;
  v22[34] = 1;
  v1[24] = v22;
  v23 = NewSpecific(sbyte, 3u);
  v23[32] = 4;
  v23[34] = 2;
  v1[25] = v23;
  v24 = NewSpecific(sbyte, 3u);
  v24[32] = 4;
  v24[34] = 8;
  v1[26] = v24;
  v25 = NewSpecific(sbyte, 3u);
  v25[32] = 4;
  v25[34] = 7;
  v1[27] = v25;
  v26 = NewSpecific(sbyte, 3u);
  v26[32] = 4;
  v26[34] = 13;
  v1[28] = v26;
  v27 = NewSpecific(sbyte, 3u);
  v27[32] = 5;
  v27[34] = 1;
  v1[29] = v27;
  v28 = NewSpecific(sbyte, 3u);
  v28[32] = 7;
  v28[34] = 1;
  v1[30] = v28;
  v29 = NewSpecific(sbyte, 3u);
  v29[32] = 7;
  v29[34] = 2;
  v1[31] = v29;
  v30 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v30, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__3BD557D5CC45446FAD78A5A18C334D65135EBB591750635A92EEA2C01329155D, 0);
  v1[32] = v30;
  v31 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v31, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__5FD5F8F5E16F70920537D7D25E38E8E1EFDE2802E8FE2F4EAAFD26AF6CE75917, 0);
  v1[33] = v31;
  v32 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v32, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__492648BCF1F2CCE7637F3BAC12AFAA4464228985BCF4D754E50693D196A94E23, 0);
  v1[34] = v32;
  v33 = NewSpecific(sbyte, 3u);
  v33[34] = 3;
  v33[32] = 6;
  v1[35] = v33;
  v34 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v34, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__DD67C2CAB991090363AA7C821ED0C5E2E6825257B6636039E10998E33CC96AF4, 0);
  v1[36] = v34;
  v35 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v35, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__210A9FE9D070085B444BF2BD9FAAF29CC3231F4599143BC62A8D335979605971, 0);
  v1[37] = v35;
  v36 = NewSpecific(sbyte, 3u);
  v36[32] = 17;
  v36[34] = 25;
  v1[38] = v36;
  v37 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v37, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__3EC4DAB718C7C5640B1913A21E6662704200210E9BA56B077A502DB04CB64EB5, 0);
  v1[39] = v37;
  v38 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v38, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__EC60CDA5305C3C975FCA0266FAA85C1A329F72C6C3A2FAB0F61C7814839B09CF, 0);
  v1[40] = v38;
  v39 = NewSpecific(sbyte, 3u);
  v39[32] = 4;
  v39[34] = 10;
  v1[41] = v39;
  v40 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v40, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__04503C9959249975B9B067F854B0276063BE7E01AFBD215E1CFF838DCF92D55E, 0);
  v1[42] = v40;
  v41 = NewSpecific(sbyte, 3u);
  v1[43] = v41;
  v42 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v42, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__D0192C1BE3755623B7CD5B7D7191C8C6AA81435E656D339CCC8DF8AD216A151E, 0);
  v1[44] = v42;
  v43 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v43, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__2D7BC947ABA42E33C31A76D0D766522C0DCAB69B3439B01B9EEEF2BFDCCA079B, 0);
  v1[45] = v43;
  v44 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v44, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__2823A2D9AC185E41F7FEE0FFD695C46ACE00CCAE3F45E6880264EF3531786D9B, 0);
  v1[46] = v44;
  v45 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v45, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__DAC963FFC32F88D2ABA8992F29BC97336A9863D7AB01BD93E4A163F628839361, 0);
  v1[47] = v45;
  v46 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v46, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FB0724F965E6DE252BCE24DE6CAF22ED482B23DF9C36AB830C137BE71E08C19F, 0);
  v1[48] = v46;
  v47 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v47, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__2CD4F7D372AE9CA6FBDA23FFF8321436B50442CC4F8799732B1AAC355C984092, 0);
  v1[49] = v47;
  v48 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v48, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__D3E5DC8792FAE8E6380B5EEF6B53CF6E82DA3FAAAC7EA31630B47F5AB80AA148, 0);
  v1[50] = v48;
  v49 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v49, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8C7FDB659A9365D10A5499B5BF9F8CA06B17D9D85943E59C04B731F6698A5E6D, 0);
  v1[51] = v49;
  v50 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v50, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__DA765AD926469CABA1D353D830354A51BE77F47FF8D944AFD9260C31AEBCC1F1, 0);
  v1[52] = v50;
  v51 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v51, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__46611DEEB2ED67BD0E33EA5EA56008342A63F8B78794AC2077C18BB8FF1D35A9, 0);
  v1[53] = v51;
  v52 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v52, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__47356CB71111F1D8ADA9BC30C75DC8E2742F6109E0F9329F8BECBD41824E86A2, 0);
  v1[54] = v52;
  v53 = NewSpecific(sbyte, 3u);
  v53[32] = 10;
  v53[34] = 2;
  v1[55] = v53;
  v54 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v54, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__3D14643F8F41F639D25AF2D256B4685D13212C9CAB81A9E52A02AABFC2F8585F, 0);
  v1[56] = v54;
  v56 = v1[lmapwk->fieldNo + 4];
  v57 = v56[32];
  v58 = v56[33];
  v59 = v56[34];
  mapLmapToMap(v57, v58, v59);
}

// 0x1cbf890
static void SoundSmgLoad(s32 map) {
  gSoundSmgLoadId = map;
  gSoundSmgLoadPhase = 0;
  return;
}

// 0x1cbf920
static s32 SoundSmgLoadChk(void) {
  s32 v6;
  s32 v9;
  s32 v13;

  if (gSoundSmgLoadPhase != 1)
  {
    if (gSoundSmgLoadPhase)
    {
      goto LABEL_21;
    }
    v6 = p2sdLoadCheckMidi(gSoundSmgLoadId);
    if (v6)
    {
LABEL_11:
LABEL_21:
      gSoundSmgLoadPhase = -1;
      return 1;
    }
    v13 = gSoundSmgLoadId;
    p2sdLoadSMGFile(v13);
    ++gSoundSmgLoadPhase;
    return 0;
  }
  v9 = gSoundSmgLoadId;
  if (p2sdLoadCheckMidi(v9) == 1)
  {
    goto LABEL_11;
  }
  return 0;
}

// 0x1cc7f40
static bool SetPadEnable(bool a_bFlag) {
  tagM_LMAP_WORK *v6;
  u8 flag;
  u8 v9;

  if (!lmapwk)
    return 0;
  v6 = lmapwk;
  flag = v6->flag | 0x10;
  v6->flag = flag;
  if (!a_bFlag)
  {
    v6 = lmapwk;
    flag = v6->flag;
    v9 = flag & 0xDF;
    goto LABEL_16;
  }
  v6 = lmapwk;
  flag = v6->flag;
  v9 = flag | 0x20;
LABEL_16:
  v6->flag = v9;
  return 1;
}

// 0x1cc9c90
static bool SetFlagDebug(bool a_bFlag) {
  return 1;
}

// 0x1cc9ca0
static void LoadNpcFile(void) {
  tagM_LMAP_WORK *lmapwk_local;

  lmapwk_local = lmapwk;
  lmapwk_local->pDatNpc = gLmpNpc;
}

// 0x1cc9d10
bool lmapProcCheckFlag(void) {
  if (!lmapwk)
    return 0;
  if (lmapwk->step_main != 6)
    return 0;
  if (lmapwk->msgwk->step)
    return 0;
  return 1;
}

// 0x1cc4870
static s32 ChkWarp(s32 a_chkMapID) {
  s32 i;
  _BOOL4 v6;
  s32 tgtMapID;
  s32 flag1;
  _BOOL4 v9;
  Warp_t *v10;
  s32 flag2;

  if (!arrLmpWarp)
    return -1;
  if (arrLmpWarp->max_length)
  {
    for (i = 0; ; ++i)
    {
      tgtMapID = arrLmpWarp[i]->tgtMapID;
      if (tgtMapID < 0)
        return -1;
      if (tgtMapID != a_chkMapID)
        continue;
      flag1 = arrLmpWarp[i]->flag1;
      if (!arrLmpWarp[i]->flag1)
        continue;
      flag1 = arrLmpWarp[i]->flag1;
      v9 = evtBitCheck(flag1);
      v10 = arrLmpWarp[i];
      if (((v9 ^ (v10->flag1chk == 1)) & 1) == 0)
      {
        v10 = arrLmpWarp[i];
        flag2 = v10->flag2;
        if (!v10->flag2)
          return i;
        flag2 = arrLmpWarp[i]->flag2;
        v6 = evtBitCheck(flag2);
        if (v6 == (arrLmpWarp[i]->flag2chk == 1))
          return i;
      }
    }
  }
  return -1;
}

// 0x1cc9e10
static void Start(s32 aFieldNo) {
  tagM_LMAP_WORK *v3;
  dds3ProcessFunc_t v6;
  shutdownfuncDelegate v7;
  dds3ProcessID_t *started;
  tagM_LMAP_WORK *v11;
  dds3ProcessFunc_t v12;
  dds3ProcessID_t *v13;
  tagM_LMAP_WORK *v16;

  v3 = Allocate(tagM_LMAP_WORK);
  _ctor(v3, 0);
  lmapwk = v3;
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_lmap_Process__, 0);
  v7 = Allocate(shutdownfuncDelegate);
  _ctor(v7, 0, Method_Project_lmap_Shutdown__, 0);
  started = dds3StartProcess("lmpMainProc", 1031, 0, 0, v6, v7, lmapwk);
  g_mainPID_Lmap = started;
  v11 = lmapwk;
  v12 = Allocate(dds3ProcessFunc_t);
  _ctor(v12, 0, Method_Project_lmap_DrawProcess__, 0);
  v13 = dds3StartProcess("lmpDrawProc", 11031, 0, 0, v12, 0, lmapwk);
  v11->drawPID = v13;
  if (!aFieldNo)
  {
    lmapwk->loadStart = 1;
LABEL_17:
    LOWORD(aFieldNo) = 1;
    goto LABEL_18;
  }
  v16 = lmapwk;
  v16->loadStart = 0;
  if (aFieldNo < 1)
    goto LABEL_17;
LABEL_18:
  v16 = lmapwk;
  v16->fieldNo = aFieldNo;
}

// 0x1cca110
s32 lmapProcessCheck(void) {
  return dds3SearchProcessName("lmpMainProc") != 0;
}

// 0x1cca190
static void ShutDown(void) {
  char *v8;
  char *v10;

  if (!dds3ExistProcess(g_mainPID_Lmap))
  {
    goto LABEL_6;
  }
  Release(lmap);
  dds3KillProcess(g_mainPID_Lmap, 1);
  v8 = "MAP35_M";
  Remove_30362592("MAP35_E", 0);
  Remove_30362592(v8, 0);
  v10 = "map35_msg";
  Unload(Dependent, v10, 0);
LABEL_6:
  g_mainPID_Lmap = 0;
  Lmapscene_asyncLoad = 0;
  fieldUIscene_asyncLoad = 0;
  fldQuestIconMarkInit();
}

// 0x1cbed90
static void LoadFile(void) {
  s32 v2;
  u16 v3;
  tagM_LMAP_WORK *v4;
  s16 v7;
  bool v15;
  tagLMAP_CHR_WORK *p_chrwk;
  s16 v17;
  tagM_LMAP_WORK *v19;
  s16 v21;
  Il2CppObject *ModelHandle;
  void *transform;
  void *gameObject;
  tagM_LMAP_WORK *v31;
  tagM_LMAP_WORK *v35;
  dds3ModelHandle_t *v36;
  _OWORD *p_m00;
  __int128 v40;
  __int128 v41;
  __int128 v42;
  __int128 v46;
  __int128 v47;
  __int128 v48;
  char *v53;
  char *v54;
  char *v55;
  dds3ProcessID_t *ID;
  tagM_LMAP_WORK *v59;
  dds3ProcessID_t *v61;
  tagM_LMAP_WORK *v64;
  dds3ProcessID_t *v66;
  sdfMatrix4_t v70;
  dds3Basic_t *scene;
  sdfVector4_t Row;
  sdfVector4_t v73;

  scene = 0;
  v2 = 0;
  memset(&v70, 0, sizeof(v70));
  while (1)
  {
    v7 = dmLMAP_POINT_NO(v2);
    if (v7 < 0)
    {
      Chr_SetPlayer(&lmapwk->chrwk, 1);
      lmapwk->mapId = lmapMapDat_GetMapId(1);
      goto LABEL_19;
    }
    if ((dmLMAP_POINT_FLAG(v2) & 1) != 0)
    {
      v3 = dmLMAP_POINT_ID(v2);
      v4 = lmapwk;
      if ((u16)v4->fieldNo == v3)
        break;
    }
    ++v2;
  }
  v4 = lmapwk;
  p_chrwk = &v4->chrwk;
  v17 = dmLMAP_POINT_NO(v2);
  Chr_SetPlayer(p_chrwk, v17);
  v19 = lmapwk;
  v21 = dmLMAP_POINT_NO(v2);
  v19->mapId = lmapMapDat_GetMapId(v21);
LABEL_19:
  GetRaidouObject(goLmapManager, 0);
  if (evtBitCheck(350) && !evtBitCheck(160))
  {
    GetKayaObject(goLmapManager, 0);
    v15 = 1;
  }
  else
  {
    v15 = 0;
  }
  SetCameraActive(goLmapManager, 2, v15, 0);
  ModelHandle = dds3ObjectBaseGetModelHandle(&lmapwk->chrwk->unit);
  transform = get_transform(ModelHandle[4].klass->_2.unity_user_data, 0);
  gameObject = get_gameObject(transform, 0);
  itfSetRaidoObject(gameObject, 0.0);
  v31 = lmapwk;
  v31->pDatNpc = gLmpNpc;
  SetNpcDat();
  if (evtBitCheck(195) && !evtBitCheck(206))
  {
    v35 = lmapwk;
    v36 = mdlLoad(2u, 31);
    v35->hModel_yaso = v36;
    vct_A = (struct sdfVector4_t)xmmword_3D06530;
    mdlSetPosition(lmapwk->hModel_yaso);
    p_m00 = &IdentityMatrix.m00;
    v40 = p_m00[2];
    v41 = p_m00[3];
    v42 = p_m00[1];
    *(_OWORD *)&v70.m00 = *p_m00;
    *(_OWORD *)&v70.m01 = v42;
    *(_OWORD *)&v70.m02 = v40;
    *(_OWORD *)&v70.m03 = v41;
    Row = GetRow(&v70, 0, 0);
    vct_A = Row;
    FromRotation(LmapCameraPar->YasoAngle01 * 0.017453292);
    vct_B = vct_A;
    v46 = *(_OWORD *)&IdentityMatrix.m02;
    v47 = *(_OWORD *)&IdentityMatrix.m03;
    v48 = *(_OWORD *)&IdentityMatrix.m01;
    *(_OWORD *)&v70.m00 = *(_OWORD *)&IdentityMatrix.m00;
    *(_OWORD *)&v70.m01 = v48;
    *(_OWORD *)&v70.m02 = v46;
    *(_OWORD *)&v70.m03 = v47;
    v73 = GetRow(&v70, 1, 0);
    vct_A = v73;
    FromRotation(LmapCameraPar->YasoAngle02 * 0.017453292);
    Mult();
    mdlSetRotate(lmapwk->hModel_yaso);
    vct_A = (struct sdfVector4_t)xmmword_3D06C10;
    mdlSetScale(lmapwk->hModel_yaso);
    GetYasoObject(goLmapManager, 0);
    dds3FilterSet(109, 2, 1);
    dds3FilterSetAnime(1);
    gFilterFilterAlpOfs = -60;
    lmapwk->filterAlpha = 0;
    gFilterAlpha = 0;
    lmapwk->bSetFilter = 0;
  }
  v53 = "map35_msg.";
  Load(Dependent, v53, v53);
  scene = dds3GetControlScene();
  dds3SceneBasicLoadScriptFile(scene, "map35.bf", "map35");
  v54 = "MAP35_E";
  v55 = "MAP35_M";
  LoadLocalizeText_2(v53, v54);
  LoadLocalizeText_2(v53, v55);
  Unload(Dependent, v53, 0);
  Unload(Dependent, "map35", 0);
  Create(0);
  fclLoadData("lmp_sys.bmd", "lmap_sys", 1);
  ID = getID();
  fclID = ID;
  v59 = lmapwk;
  v61 = ActWnd_Start();
  v59->proc_actwnd = v61;
  FldWnd_ProcessStart();
  FldWnd_LinkSprite(lmapwk->hSpr);
  v64 = lmapwk;
  *(u32 *)&v64->bDrawActWin = -65536;
  v66 = EffWave_Start();
  v64->proc_effwave = v66;
  itfSetStationListText();
  itfSetMoneyText();
  ListProcessStart();
  ListLinkSprite(lmapwk->hSpr);
  Unload(_Ctrl_k__BackingField, "lmap_sys", 0);
}

// 0x1cc6b80
static void GetCameraBasePos(sdfVector4_t *pos1, const sdfVector4_t *pos0) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s32 mapId;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;

  w = pos0->w;
  z = pos0->z;
  y = pos0->y;
  x = pos0->x;
  lmapwk->mapId = lmapMapDat_GetMapId(lmapwk->chrwk->basePointNo);
  mapId = (u8)lmapwk->mapId;
  if (mapId == 1)
  {
    v14 = LmapCameraPar->ToykoPosLimit.y;
    if (x >= v14)
    {
      goto LABEL_11;
      if (x <= v15)
      {
LABEL_12:
        goto LABEL_13;
        if (z <= v16)
        {
LABEL_14:
          goto LABEL_15;
LABEL_46:
          z = v17;
          goto LABEL_64;
        }
LABEL_42:
        z = v16;
LABEL_15:
        v17 = LmapCameraPar->ToykoPosLimit.w;
        if (z >= v17)
          goto LABEL_62;
        goto LABEL_46;
      }
LABEL_35:
      x = v15;
LABEL_13:
      v16 = LmapCameraPar->ToykoPosLimit.z;
      if (z <= v16)
        goto LABEL_14;
      goto LABEL_42;
    }
    x = v14;
LABEL_11:
    v15 = LmapCameraPar->ToykoPosLimit.x;
    if (x <= v15)
      goto LABEL_12;
    goto LABEL_35;
  }
  if (mapId != 2)
    goto LABEL_62;
  v18 = LmapCameraPar->ShinodaPosLimit.y;
  if (x >= v18)
    goto LABEL_26;
  x = v18;
LABEL_27:
  v19 = LmapCameraPar->ShinodaPosLimit.x;
  if (x <= v19)
    goto LABEL_28;
  x = v19;
LABEL_29:
  v20 = LmapCameraPar->ShinodaPosLimit.z;
  if (z <= v20)
    goto LABEL_30;
  goto LABEL_56;
LABEL_26:
  goto LABEL_27;
LABEL_28:
  goto LABEL_29;
  if (z <= v20)
  {
LABEL_30:
    goto LABEL_31;
  }
LABEL_56:
  z = v20;
LABEL_31:
  v21 = LmapCameraPar->ShinodaPosLimit.w;
  if (z < v21)
  {
    z = v21;
    goto LABEL_62;
  }
LABEL_62:
LABEL_64:
  pos1->x = x;
  pos1->y = y;
  pos1->z = z;
  pos1->w = w;
}

// 0x1ccaea0
static void SetPanel(s8 actType, s8 fldType, s8 tblNo) {
  if (actType != 3)
  {
    goto LABEL_4;
  }
  FldWnd_Start(fldType, lmapwk->chrwk->pos);
LABEL_4:
  lmapwk->panel_type = actType;
  lmapwk->panel_tblNo = tblNo;
  lmapwk->bDrawActWin = 1;
}

// 0x1cc7110
static void SetPanel_2(bool a_bField, s16 a_touchAreaType, u8 a_pointFlag) {
  s32 step_main;
  tagLMAP_CHR_WORK *chrwk;
  s32 moveId;
  s8 v12;
  tagM_LMAP_WORK *lmapwk_local;
  s8 v15;
  s8 v16;
  s8 v17;
  s8 v18;
  tagLMAP_CHR_WORK *v19;
  s16 v20;
  tagM_LMAP_WORK *v21;
  s32 v22;
  s64 v23;
  s64 m_Items;
  tagLMAP_CHR_WORK *v25;
  char v26;
  s32 modelMinorNo;

  step_main = lmapwk->step_main;
  if (step_main == 8)
    goto LABEL_31;
  if (step_main == 17)
  {
LABEL_31:
    lmapwk_local = lmapwk;
    *(u16 *)&lmapwk_local->bDrawActWin = 0;
    lmapwk_local->panel_tblNo = -1;
    return;
  }
  if (!MenuFlag)
    goto LABEL_31;
  chrwk = lmapwk->chrwk;
  if ((a_touchAreaType & 0x8000) == 0 && chrwk->moveId == 1 && a_bField)
  {
    if ((a_pointFlag & 1) != 0)
    {
      v15 = 3;
      v16 = a_touchAreaType;
    }
    else
    {
      if ((a_pointFlag & 8) == 0)
        goto LABEL_20;
      v15 = 7;
      v16 = 0;
    }
    SetPanel(v15, v16, 255);
    lmapwk->fieldNo = a_touchAreaType;
    return;
  }
LABEL_20:
  chrwk = lmapwk->chrwk;
  if ((chrwk->portTableNo & 0x80000000) == 0)
  {
    chrwk = lmapwk->chrwk;
    moveId = (u8)chrwk->moveId;
    if (moveId == 1)
    {
      if (!evtBitCheck(1946))
        return;
      v12 = 5;
      goto LABEL_51;
    }
    chrwk = lmapwk->chrwk;
    moveId = (u8)chrwk->moveId;
    if (moveId == 3)
    {
      chrwk = lmapwk->chrwk;
      if (chrwk->ship->mode == 1)
      {
        v12 = 6;
LABEL_51:
        v17 = -1;
        v18 = -1;
LABEL_52:
        SetPanel(v12, v17, v18);
        return;
      }
    }
  }
  v19 = lmapwk->chrwk;
  if (v19->moveId == 1)
  {
    v19 = lmapwk->chrwk;
    if (v19->moveType == 1)
    {
      v19 = lmapwk->chrwk;
      v20 = Chr_GetExLineType(v19);
      if (v20)
      {
        if (v20 == 1 && !lmapwk->chrwk->exLineType)
        {
          v12 = 4;
          v17 = a_touchAreaType;
          v18 = -1;
          goto LABEL_52;
        }
      }
    }
  }
  v21 = lmapwk;
  v22 = (u8)v21->chrwk->moveId;
  if (v22 == 1)
    goto LABEL_103;
  v21 = lmapwk;
  v22 = (u8)v21->chrwk->moveId;
  if (v22 == 3)
  {
LABEL_103:
    v23 = 0;
    m_Items = v21->npcwk->cb;
    while (1)
    {
      v25 = *(tagLMAP_CHR_WORK *)(*(u64 *)(m_Items + 8 * v23) + 16);
      if ((~v25->flags & 0x200001) == 0)
        break;
      if (++v23 == 65)
        return;
    }
    if (v25->modelMajorNo == 100)
    {
      v26 = 2;
    }
    else
    {
      modelMinorNo = v25->modelMinorNo;
      if (modelMinorNo == 12 || modelMinorNo == 18)
        v26 = 2;
      else
        v26 = 1;
    }
    v12 = v26;
    v17 = a_touchAreaType;
    v18 = v23;
    goto LABEL_52;
  }
}

// 0x1cc7620
static void ResetPanel(bool a_bField) {
  u32 v6;
  s64 v7;
  tagLMAP_CHR_WORK *chrwk;
  tagM_LMAP_WORK *v10;
  Il2CppObject *workdata;
  tagM_LMAP_WORK *v13;
  tagLMAP_CHR_WORK *v14;

  v6 = lmapwk->panel_type - 1;
  if (v6 > 6)
    return;
  switch (v6)
  {
    case 0u:
    case 1u:
      v7 = 0;
      while (1)
      {
        chrwk = lmapwk->npcwk->cb[v7]->chrwk;
        if ((chrwk->flags & 1) != 0)
        {
          if (v7 == lmapwk->panel_tblNo)
          {
            if ((chrwk->flags & 0x200000) == 0)
              goto LABEL_29;
          }
        }
        if (++v7 == 65)
          return;
      }
    case 2u:
    case 6u:
      if (a_bField)
        return;
      v10 = lmapwk;
      *(u16 *)&v10->bDrawActWin = 0;
      v10->panel_tblNo = -1;
      workdata = g_mainPID_FLDWND->workdata;
      if (!workdata)
        goto LABEL_47;
      goto LABEL_45;
      if (!workdata)
      {
LABEL_47:
        HIDWORD(workdata[3].klass) = 0;
        return;
      }
LABEL_45:
      goto LABEL_47;
    case 3u:
      v14 = lmapwk->chrwk;
      if (v14->exLineType)
      {
        goto LABEL_31;
      }
      if (!Chr_GetExLineDat(v14, 0))
      {
        goto LABEL_31;
      }
      return;
    case 4u:
    case 5u:
      if ((lmapwk->chrwk->portTableNo & 0x80000000) == 0)
        return;
LABEL_29:
LABEL_31:
      v13 = lmapwk;
      *(u16 *)&v13->bDrawActWin = 0;
      v13->panel_tblNo = -1;
      return;
    default:
      return;
  }
}

// 0x1cc5fd0
static void ResetPanelSub(void) {
  tagM_LMAP_WORK *lmapwk_local;

  lmapwk_local = lmapwk;
  *(u16 *)&lmapwk_local->bDrawActWin = 0;
  lmapwk_local->panel_tblNo = -1;
}

// 0x1cc8400
static s32 GetNearStation(void) {
  s32 basePointNo;
  s16 v4;
  s32 v6;
  char v7;
  s32 nextPointNo;
  s16 v9;

  basePointNo = lmapwk->chrwk->basePointNo;
  if (basePointNo < 0)
    goto LABEL_20;
  LOWORD(basePointNo) = lmapwk->chrwk->basePointNo;
  v4 = 0;
  while ((dmLMAP_POINT_NO(v4) & 0x8000) == 0)
  {
    if ((u16)dmLMAP_POINT_NO(v4) == (u16)basePointNo)
      goto LABEL_19;
    ++v4;
  }
  v4 = -1;
LABEL_19:
  v6 = v4;
  v7 = dmLMAP_POINT_FLAG(v4);
  if ((v7 & 2) != 0)
    goto LABEL_41;
LABEL_20:
  nextPointNo = lmapwk->chrwk->nextPointNo;
  if ((nextPointNo & 0x80000000) != 0)
    return -1;
  v9 = 0;
  while ((dmLMAP_POINT_NO(v9) & 0x8000) == 0)
  {
    if ((u16)dmLMAP_POINT_NO(v9) == (u16)nextPointNo)
      goto LABEL_38;
    ++v9;
  }
  v9 = -1;
LABEL_38:
  v6 = v9;
  if ((dmLMAP_POINT_FLAG(v9) & 2) == 0)
    return -1;
LABEL_41:
  return dmLMAP_POINT_ID(v6);
}

// 0x1cc79f0
static void SetMessage(void) {
  u32 v4;
  s64 v5;
  tagLMAP_NPC_CB *cb;
  s64 v7;
  s32 v8;
  s32 v9;
  tagM_LMAP_WORK *v11;
  char *v13;
  tagM_LMAP_WORK *v14;
  char *pScrLabel;
  u32 v18;
  s64 v21;
  tagM_LMAP_WORK *v23;
  char *scrLabel;
  char *v25;
  Il2CppObject *workdata;
  dds3Basic_t *scene;
  dds3Basic_t *ActiveScene;

  ActiveScene = 0;
  scene = 0;
  v4 = lmapwk->panel_type - 1;
  if (v4 > 6)
    return;
  switch (v4)
  {
    case 0u:
    case 1u:
      v5 = 32;
      cb = lmapwk->npcwk->cb;
      while (1)
      {
        v7 = *(s64 *)((char *)&cb->obj.klass + v5);
        if ((*(u8 *)(*(u64 *)(v7 + 16) + 114) & 0x20) != 0)
          break;
        v5 += 8;
        if (v5 == 552)
          return;
      }
      v13 = *(char **)(v7 + 24);
      v14 = lmapwk;
      v14->pScrLabel = v13;
      scene = dds3GetActiveScene();
      pScrLabel = lmapwk->pScrLabel;
      dds3SceneBasicStartScript(scene, pScrLabel);
      if (*(u32 *)(*(u64 *)(v7 + 16) + 132) != 18)
        SE(0);
      ndWorkActive(0);
      v11 = lmapwk;
      v11->msgwk->step = 1;
      *(u8 *)(*(u64 *)(v7 + 16) + 102) |= 4u;
      goto LABEL_40;
    case 2u:
      v8 = ChkWarp(lmapwk->fieldNo);
      if (v8 < 0)
        goto LABEL_57;
      goto LABEL_9001;
      if (v8 < 0)
      {
LABEL_57:
        lmapwk->msgwk->step = 1;
        return;
      }
LABEL_9001:
      v18 = v8;
      if (!op_Inequality(arrLmpWarp[v18]->scrLabel, "", 0))
        goto LABEL_57;
      v21 = v18;
      v23 = lmapwk;
      scrLabel = arrLmpWarp[v18]->scrLabel;
      v23->pScrLabel = scrLabel;
      v23 = ((char *)v23 + 40);
      WORD1(v23->proc_effgrid) = v18;
      ActiveScene = dds3GetActiveScene();
      v25 = lmapwk->pScrLabel;
      dds3SceneBasicStartScript(ActiveScene, v25);
      lmapwk->msgwk->step = 2;
      SetPadEnable(0);
      if (!arrLmpWarp[v21]->drawThumbnail)
      {
        workdata = g_mainPID_FLDWND->workdata;
        if (!workdata)
          goto LABEL_65;
        goto LABEL_63;
        if (!workdata)
        {
LABEL_65:
          BYTE5(workdata[3].klass) &= ~2u;
          return;
        }
LABEL_63:
        goto LABEL_65;
      }
      return;
    case 3u:
      v9 = GetNearStation();
      ListStart(1, v9);
      lmapwk->msgwk->step = 1;
      goto LABEL_22;
    case 6u:
      lmapwk->msgwk->step = 1;
LABEL_22:
      SE(0);
      v11 = lmapwk;
LABEL_40:
      v11->chrwk->moveStat |= 4u;
      return;
    default:
      return;
  }
}

// 0x1cc89b0
static bool SetNpcCB(s8 a_charNo, Npc_t *a_pTbl) {
  s64 v7;
  s64 v8;
  bool result;
  f32 scale;
  tagLMAP_CHR_WORK *v12;
  s16 point;
  u16 id1;
  s32 id2;
  bool v18;
  tagLMAP_CHR_WORK *v19;
  char *scr_label;
  s32 hit;

  if (!a_pTbl)
    return 0;
  v7 = 32;
  while (1)
  {
    v8 = *(s64 *)((char *)&lmapwk->npcwk->cb->obj.klass + v7);
    if ((*(u8 *)(*(u64 *)(v8 + 16) + 112) & 1) == 0)
      break;
    v7 += 8;
    if (v7 == 552)
      return 0;
  }
  scale = a_pTbl->scale;
  v12 = (v8 + 16);
  point = a_pTbl->point;
  id1 = a_pTbl->id1;
  id2 = a_pTbl->id2;
  v18 = Chr_SetParam(v12, 4, a_charNo, 3, 0, 0, point);
  result = 0;
  if (v18)
  {
    v19 = v12;
    v19->scl = scale;
    v19->sclDef = scale;
    ChrSetModel(v12, id1, id2);
    scr_label = a_pTbl->scr_label;
    *(u64 *)(v8 + 24) = scr_label;
    hit = (u16)a_pTbl->hit;
    v12->flags = v12->flags & 0xFFF7FFFF | ((*(u64 *)(v8 + 24) != 0) << 19);
    if (hit)
    {
      M_SetLockPointNpcCB(a_charNo, 1);
    }
    v12->flags |= 0x80u;
    *(u16 *)(v8 + 32) = -1;
    return 1;
  }
  return result;
}

// 0x1cc8d80
static void M_UpdateNpcCB(tagLMAP_NPC_CB *p_cb) {
  tagLMAP_CHR_WORK *v4;
  u32 flags;
  s32 worldId;
  s8 charaNo;
  s8 v9;
  bool v10;
  s8 v11;
  s32 updated;
  tagLMAP_CHR_WORK *v16;
  u32 v18;
  s32 basePointNo;
  struct sdfVector4_t v24;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v33;
  s32 i;
  s16 v37;
  s16 v39;
  f32 *v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v47;
  struct sdfVector4_t pos;
  tagLMAP_CHR_WORK *chrwk;

  v4 = p_cb->chrwk;
  chrwk = v4;
  flags = v4->flags;
  if ((flags & 1) == 0)
    return;
  worldId = (u8)v4->worldId;
  if (worldId == 3)
  {
LABEL_10:
    if ((flags & 0x200) == 0)
    {
      v4->flags = flags | 0x200;
      if ((flags & 0x20000) != 0)
      {
        charaNo = v4->charaNo;
        v9 = charaNo;
        v10 = 1;
LABEL_21:
        M_SetLockPointNpcCB(v9, v10);
        goto LABEL_22;
      }
    }
    goto LABEL_22;
  }
  if (worldId == (u8)lmapwk->worldId)
    goto LABEL_10;
  if ((flags & 0x200) != 0)
  {
    v4->flags = flags & 0xFFFFFDFF;
    if ((flags & 0x20000) != 0)
    {
      v11 = v4->charaNo;
      v9 = v11;
      v10 = 0;
      goto LABEL_21;
    }
  }
LABEL_22:
  updated = Chr_UpdateMove(chrwk, &lmapwk->lockwk);
  if (updated >= 2)
  {
    v16 = lmapwk->chrwk;
    v16->moveStat &= ~8u;
  }
  Chr_UpdateModel(chrwk);
  v18 = v4->flags;
  v4->flags = v18 & 0xFFDFFFFF;
  if ((u32)(lmapwk->chrwk->moveId - 3) > 0xFFFFFFFD)
  {
    if (v4->basePointNo >= 900)
      return;
  }
  else
  {
    if (lmapwk->chrwk->moveId != 3)
      return;
    basePointNo = v4->basePointNo;
    if (basePointNo <= 899 && basePointNo != 581)
      return;
  }
  if ((~v18 & 0x280) == 0 && (v4->flags & 0x80000) != 0)
  {
    pos = v4->pos;
    vct_A = pos;
    v24 = lmapwk->chrwk->pos;
    vct_B = v24;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    z = p_x[6];
    x = p_x[4];
    y = p_x[5];
    if (sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z)) <= LMAP_CHR_CHARA_LENGTH)
    {
      v4->flags |= 0x200000u;
LABEL_54:
      if (lmapwk->chrwk->moveId != 3)
        return;
LABEL_58:
      v33 = 10000.0;
      for (i = 0; ; ++i)
      {
        if (dmLMAP_POINT_NO(i) < 0)
        {
          if (v4->basePointNo == 581)
          {
            if (v33 <= LMAP_CHR_AREA_LENGTH)
              v4->flags |= 0x200000u;
          }
          return;
        }
        if (dmLMAP_POINT_NO(i) == 581)
        {
          v37 = dmLMAP_POINT_X(i);
          v39 = dmLMAP_POINT_Y(i);
          vct_A.y = 0.0;
          vct_A.w = 1.0;
          vct_A.x = (f32)v37;
          vct_A.z = (f32)v39;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v42 = &vf00.x;
          v43 = v42[4];
          v44 = v42[5];
          v45 = v42[6];
          v47 = sqrtf((f32)((f32)(v43 * v43) + (f32)(v44 * v44)) + (f32)(v45 * v45));
          if (v33 > v47)
            v33 = v47;
        }
      }
    }
    {
      goto LABEL_54;
    }
    if (lmapwk->chrwk->moveId != 3)
      return;
    goto LABEL_58;
  }
}

// 0x1ccb3b0
static void M_UpdateKaya(tagLMAP_CHR_WORK *kaya) {
  u32 flags;
  s32 worldId;
  u32 v6;
  s32 updated;
  tagLMAP_CHR_WORK *v11;
  u32 v12;
  struct sdfVector4_t v17;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  struct sdfVector4_t pos;
  tagLMAP_CHR_WORK *chrwk;

  flags = kaya->flags;
  chrwk = kaya;
  if ((flags & 1) == 0)
    return;
  worldId = (u8)kaya->worldId;
  if (worldId == 3)
    goto LABEL_8;
  if (worldId == (u8)lmapwk->worldId)
  {
LABEL_8:
    if ((flags & 0x200) != 0)
      goto LABEL_14;
    v6 = flags | 0x200;
    goto LABEL_13;
  }
  if ((flags & 0x200) == 0)
    goto LABEL_14;
  v6 = flags & 0xFFFFFDFF;
LABEL_13:
  kaya->flags = v6;
LABEL_14:
  updated = Chr_UpdateMove(chrwk, &lmapwk->lockwk);
  if (updated >= 2)
  {
    v11 = lmapwk->chrwk;
    v11->moveStat &= ~8u;
  }
  Chr_UpdateModel(chrwk);
  v12 = kaya->flags;
  kaya->flags = v12 & 0xFFDFFFFF;
  if ((u32)(lmapwk->chrwk->moveId - 3) > 0xFFFFFFFD)
  {
    if (kaya->basePointNo >= 900)
      return;
  }
  else if (lmapwk->chrwk->moveId != 3 || kaya->basePointNo < 900)
  {
    return;
  }
  if ((~v12 & 0x280) == 0 && (kaya->flags & 0x80000) != 0)
  {
    pos = kaya->pos;
    vct_A = pos;
    v17 = lmapwk->chrwk->pos;
    vct_B = v17;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    z = p_x[6];
    x = p_x[4];
    y = p_x[5];
    if (sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z)) <= LMAP_CHR_CHARA_LENGTH)
      kaya->flags |= 0x200000u;
    return;
  }
}

// 0x1cc9a20
static void DrawTexActWin(f32 fx, f32 fy, s32 w) {
  itfDrawActWnd();
}

// 0x1cc9a90
static void DrawFntActWin(f32 fx, f32 fy, u32 abgr, char *str) {
  itfFloatTo32s(fx, 4);
  itfFloatTo32s(fy, 3);
  itfSetActWndText(str, 1);
}

// 0x1ccb7e0
static s32 NpcDelete(void) {
  s64 v2;
  s64 v4;
  char *v5;
  s64 v7;
  s8 v9;

  if (lmapwk)
  {
    v2 = 32;
    while (1)
    {
      v4 = *(s64 *)((char *)&lmapwk->npcwk->cb->obj.klass + v2);
      if ((*(u8 *)(*(u64 *)(v4 + 16) + 112) & 1) == 0)
        goto LABEL_6;
      v5 = *(char **)(v4 + 24);
      if (scrSearchScriptName(*(char **)(v4 + 24)))
        goto LABEL_14;
      goto LABEL_9000;
      if (scrSearchScriptName(v5))
      {
LABEL_14:
        v7 = *(u64 *)(v4 + 16);
        v9 = *(u8 *)(v7 + 97);
        *(u32 *)(v7 + 112) &= ~0x80u;
        M_SetLockPointNpcCB(v9, 0);
      }
LABEL_9000:
LABEL_6:
      v2 += 8;
      if (v2 == 552)
        return 1;
    }
  }
  return 0;
}

// 0x1ccb950
static s32 NpcMoveRoute(s32 a_routeNo) {
  s16 v2;
  s64 v4;
  s64 v5;
  char *v6;
  scrHandle_t *v7;

  v2 = a_routeNo;
  if (lmapwk)
  {
    v4 = 32;
    while (1)
    {
      v5 = *(s64 *)((char *)&lmapwk->npcwk->cb->obj.klass + v4);
      if ((*(u8 *)(*(u64 *)(v5 + 16) + 112) & 1) == 0)
        goto LABEL_5;
      v6 = *(char **)(v5 + 24);
      break;
LABEL_5:
      v4 += 8;
      if (v4 == 552)
        return 1;
    }
    v7 = scrSearchScriptName(*(char **)(v5 + 24));
    if (!v7)
      goto LABEL_5;
    *(u16 *)(v5 + 32) = v2;
    goto LABEL_5;
  }
  return 0;
}

// 0x1ccbaa0
bool lmapCheckCallCampFromLmap(void) {
  return CallCampFromLmap;
}

// 0x1ccbb20
bool lmapCheckCallFastTravelFromLmap(void) {
  return CallFastTravelFromLmap;
}

// 0x1ccbba0
s32 lmapGetPriceFromLmapJmpTbl(s32 jmpID) {
  s32 StationFromLineNo;

  StationFromLineNo = GetStationFromLineNo(lmapJmpDataTbls, lmapwk->chrwk->basePointNo, 0);
  return GetJmpPriceData(lmapJmpDataTbls, StationFromLineNo, jmpID, 0);
}

// 0x1ccbc30
sdfVector3_t lmapGetPlayerPosition(void) {
  tagLMAP_CHR_WORK *chrwk;
  sdfVector3_t result;

  if (lmapwk)
  {
    chrwk = lmapwk->chrwk;
    if (chrwk)
      goto LABEL_9;
  }
  result.x = zeroVector.x;
  result.y = zeroVector.y;
  result.z = zeroVector.z;
  return result;
LABEL_9:
  chrwk = lmapwk->chrwk;
  result.y = -chrwk->pos.y;
  result.z = chrwk->pos.z;
  result.x = chrwk->pos.x;
  return result;
}

// 0x1ccbd50
void lmapSetIsLoaded(void) {
  isLoaded = 1;
  return;
}

// 0x1ccbde0
void lmapSetLmapManagerObject(void *go) {
  goLmapManager = go;
}

// 0x1ccbe50
static void ActWnd_InitCB(tagLMAP_ACTWND_CB *p_cb) {
  p_cb->w[0] = 0.0;
}

// 0x1ccbe60
static void ActWnd_SetCB(tagLMAP_ACTWND_CB *p_cb, s32 no, f32 x, f32 y, f32 w, f32 h) {
  f32 *v7;
  f32 *v8;
  f32 *v9;
  f32 *v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;

  v7 = p_cb->x;
  v8 = p_cb->y;
  v9 = p_cb->w;
  v10 = p_cb->h;
  v11 = (f32)(w + 4.0) + 512.0;
  if (!no)
    v11 = 0.0 - (f32)(w + 4.0);
  v7[0] = v11;
  v12 = w + 8.0;
  v13 = h + 8.0;
  v14 = y + -4.0;
  v8[0] = v14;
  v9[0] = v12;
  v10[0] = v13;
  v7[1] = x + -4.0;
  v8[1] = v14;
  v9[1] = v12;
  v10[1] = v13;
  v7[2] = (f32)(v7[1] - v7[0]) / 10.0;
  v8[2] = (f32)(v8[1] - v8[0]) / 10.0;
  v9[2] = (f32)(v9[1] - v9[0]) / 10.0;
  v10[2] = (f32)(v10[1] - v10[0]) / 10.0;
}

// 0x1ccbf10
static bool ActWnd_Set(dds3ProcessID_t *proc, s8 type) {
  Il2CppObject *workdata;
  bool result;
  char *v10;
  FontReq_t *v11;
  Il2CppClass *klass;
  f32 v15;
  u64 *data;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 *v22;
  s64 v23;
  f32 *v24;
  s64 v25;
  f32 v26;
  u64 *v27;
  f32 *v28;
  s64 v29;
  f32 *v30;
  s64 v31;

  workdata = proc->workdata;
  if (BYTE1(workdata[2].klass))
    return 0;
  result = 0;
  if ((u8)type <= 7u && !workdata[1].monitor)
  {
    BYTE1(workdata[2].klass) = type;
    v10 = lmap_actionword[(u8)type];
    LOBYTE(workdata[2].klass) = 1;
    BYTE2(workdata[2].klass) = 0;
    v11 = frSetFontString(v10, 0, 0, 0, 0);
    workdata[1].monitor = v11;
    frSetDrawSpeed(workdata[1].monitor, 0x80u);
    klass = workdata[3].klass;
    v15 = *((s32 *)workdata[1].monitor + 9);
    data = klass->_1.byval_arg.data;
    v17 = (f32)(v15 * -0.5) + 256.0;
    v18 = v15 + 4.0;
    *((f32 *)&workdata[2].klass + 1) = v17;
    *(f32 *)&workdata[2].monitor = v15;
    v19 = 0.0 - (f32)(v15 + 4.0);
    v20 = v15 + 8.0;
    v21 = v17 + -4.0;
    klass = workdata[3].klass;
    v22 = data[2];
    v23 = data[3];
    v24 = data[4];
    v25 = data[5];
    v26 = v18 + 512.0;
    v27 = *(u64 **)&klass->_1.byval_arg.bits;
    v22[8] = v19;
    *(u32 *)(v23 + 32) = 1132855296;
    v24[8] = v20;
    *(u32 *)(v25 + 32) = 1107296256;
    v22[9] = v21;
    *(u32 *)(v23 + 36) = 1132855296;
    v24[9] = v20;
    *(u32 *)(v25 + 36) = 1107296256;
    v22[10] = (f32)(v22[9] - v22[8]) / 10.0;
    *(f32 *)(v23 + 40) = (f32)(*(f32 *)(v23 + 36) - *(f32 *)(v23 + 32)) / 10.0;
    v24[10] = (f32)(v24[9] - v24[8]) / 10.0;
    *(f32 *)(v25 + 40) = (f32)(*(f32 *)(v25 + 36) - *(f32 *)(v25 + 32)) / 10.0;
    v28 = v27[2];
    v29 = v27[3];
    result = 1;
    v30 = v27[4];
    v31 = v27[5];
    v28[8] = v26;
    *(u32 *)(v29 + 32) = 1132855296;
    v30[8] = v20;
    *(u32 *)(v31 + 32) = 1107296256;
    v28[9] = v21;
    *(u32 *)(v29 + 36) = 1132855296;
    v30[9] = v20;
    *(u32 *)(v31 + 36) = 1107296256;
    v28[10] = (f32)(v28[9] - v28[8]) / 10.0;
    *(f32 *)(v29 + 40) = (f32)(*(f32 *)(v29 + 36) - *(f32 *)(v29 + 32)) / 10.0;
    v30[10] = (f32)(v30[9] - v30[8]) / 10.0;
    *(f32 *)(v31 + 40) = (f32)(*(f32 *)(v31 + 36) - *(f32 *)(v31 + 32)) / 10.0;
  }
  return result;
}

// 0x1ccc1f0
static void ActWnd_UpdateCB(tagLMAP_ACTWND_CB *p_cb, bool endflg) {
  f32 *x;
  f32 *w;
  f32 *h;
  f32 v6;
  f32 *v7;

  x = p_cb->x;
  if (endflg)
  {
    x[0] = x[1];
    w = p_cb->w;
    p_cb->y[0] = p_cb->y[1];
    h = p_cb->h;
    w[0] = w[1];
    v6 = h[1];
  }
  else
  {
    x[0] = x[0] + x[2];
    v7 = p_cb->w;
    p_cb->y[0] = p_cb->y[0] + p_cb->y[2];
    h = p_cb->h;
    v7[0] = v7[0] + v7[2];
    v6 = h[0] + h[2];
  }
  h[0] = v6;
}

// 0x1ccc270
static void ActWnd_DrawCB(tagLMAP_ACTWND_CB *p_cb) {
  ;
}

// 0x1ccc280
static void ActWnd_Init(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  FontReq_t *monitor;
  Il2CppClass *klass;
  u64 *data;
  s64 v8;
  s64 v11;

  workdata = proc->workdata;
  monitor = workdata[1].monitor;
  if (monitor)
  {
    frDestroyFontRequestAfter(monitor);
    workdata[1].monitor = 0;
  }
  klass = workdata[3].klass;
  data = klass->_1.byval_arg.data;
  *(u32 *)(data[4] + 32) = 0;
  v8 = *(u64 *)&klass->_1.byval_arg.bits;
  v11 = *(u64 *)(v8 + 32);
  BYTE2(workdata[2].klass) = 0;
  *(u32 *)(v11 + 32) = 0;
  LOWORD(workdata[2].klass) = 0;
}

// 0x1ccc3c0
static dds3ProcessFunc_t ActWnd_Main(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s32 klass_low;
  s32 v6;
  char v7;
  Il2CppClass *klass;
  u64 *data;
  s64 v11;
  u64 *v12;
  s64 v13;
  s64 v14;
  u64 *v15;
  s64 v16;
  s64 v17;
  s64 v18;
  s64 v19;
  s64 v24;
  s64 v25;
  f32 v26;
  FontReq_t *monitor;
  s32 v28;

  workdata = proc->workdata;
  klass_low = LOBYTE(workdata[2].klass);
  if (klass_low == 2)
  {
    klass = workdata[3].klass;
    v6 = SBYTE2(workdata[2].klass);
    data = klass->_1.byval_arg.data;
    if (v6 > 9)
    {
      v11 = data[3];
      v12 = *(u64 **)&klass->_1.byval_arg.bits;
      *(u32 *)(data[2] + 32) = *(u32 *)(data[2] + 36);
      *(u32 *)(v11 + 32) = *(u32 *)(v11 + 36);
      v13 = data[5];
      *(u32 *)(data[4] + 32) = *(u32 *)(data[4] + 36);
      *(u32 *)(v13 + 32) = *(u32 *)(v13 + 36);
      v24 = v12[3];
      *(u32 *)(v12[2] + 32) = *(u32 *)(v12[2] + 36);
      *(u32 *)(v24 + 32) = *(u32 *)(v24 + 36);
      v25 = v12[5];
      *(u32 *)(v12[4] + 32) = *(u32 *)(v12[4] + 36);
      *(u32 *)(v25 + 32) = *(u32 *)(v25 + 36);
      v26 = *((f32 *)&workdata[2].klass + 1);
      monitor = workdata[1].monitor;
      if (v26 == INFINITY)
        v28 = 0;
      else
        v28 = 16 * (s32)v26;
      frSetDrawPosition(monitor, v28, 2176);
      v7 = LOBYTE(workdata[2].klass) + 1;
      goto LABEL_23;
    }
    v14 = data[3];
    v15 = *(u64 **)&klass->_1.byval_arg.bits;
    *(f32 *)(data[2] + 32) = *(f32 *)(data[2] + 32) + *(f32 *)(data[2] + 40);
    *(f32 *)(v14 + 32) = *(f32 *)(v14 + 32) + *(f32 *)(v14 + 40);
    v16 = data[5];
    *(f32 *)(data[4] + 32) = *(f32 *)(data[4] + 32) + *(f32 *)(data[4] + 40);
    *(f32 *)(v16 + 32) = *(f32 *)(v16 + 32) + *(f32 *)(v16 + 40);
    v17 = v15[3];
    *(f32 *)(v15[2] + 32) = *(f32 *)(v15[2] + 32) + *(f32 *)(v15[2] + 40);
    v19 = v15[4];
    v18 = v15[5];
    *(f32 *)(v17 + 32) = *(f32 *)(v17 + 32) + *(f32 *)(v17 + 40);
    *(f32 *)(v19 + 32) = *(f32 *)(v19 + 32) + *(f32 *)(v19 + 40);
    *(f32 *)(v18 + 32) = *(f32 *)(v18 + 32) + *(f32 *)(v18 + 40);
  }
  else
  {
    if (klass_low != 1)
      return 0;
    v6 = BYTE2(workdata[2].klass);
    if (v6 == 3)
    {
      v7 = 2;
LABEL_23:
      LOBYTE(workdata[2].klass) = v7;
      BYTE2(workdata[2].klass) = 0;
      return 0;
    }
  }
  BYTE2(workdata[2].klass) = v6 + 1;
  return 0;
}

// 0x1ccc710
static dds3ProcessFunc_t ActWnd_Draw(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  u32 klass_low;
  FontReq_t *monitor;

  workdata = proc->workdata;
  klass_low = LOBYTE(workdata[2].klass);
  if (klass_low < 2)
    return 0;
  if (klass_low != 3)
    return 0;
  monitor = workdata[1].monitor;
  frDrawFont(monitor);
  return 0;
}

// 0x1ccc830
static void ActWnd_Reset(dds3ProcessID_t *proc) {
  dds3ProcessID_t *v4;

  v4 = proc;
  ActWnd_Init(v4);
}

// 0x1ccc8b0
static dds3ProcessFunc_t ActWnd_DrawProcess(dds3ProcessID_t *proc) {
  ActWnd_Draw(proc);
  return 0;
}

// 0x1ccc920
static void ActWnd_Initialize(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  dds3ProcessFunc_t v5;
  dds3ProcessID_t *started;

  workdata = proc->workdata;
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_lmap_ActWnd_DrawProcess__, 0);
  started = dds3StartProcess("lmapActWndDrawProc", 11015, 0, 0, v5, 0, workdata);
  workdata[1].klass = started;
  ActWnd_Init(proc);
}

// 0x1ccca90
static dds3ProcessFunc_t ActWnd_Process(dds3ProcessID_t *proc) {
  ActWnd_Main(proc);
  return 0;
}

// 0x1cccb00
static void ActWnd_Shutdown(dds3ProcessID_t *proc) {

}

// 0x1cca4f0
static dds3ProcessID_t *ActWnd_Start(void) {
  tagLMAP_ACTWND_WORK *v1;
  dds3ProcessID_t *v2;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;

  v1 = Allocate(tagLMAP_ACTWND_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_lmap_ActWnd_Process__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_lmap_ActWnd_Shutdown__, 0);
  started = dds3StartProcess("lmapActWndProc", 1024, 0, 0, v3, v4, v1);
  ActWnd_Initialize(started);
  return started;
}

// 0x1cccb40
static void ActWnd_ReleaseDraw(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  FontReq_t *monitor;

  workdata = proc->workdata;
  monitor = workdata[1].monitor;
  if (monitor)
  {
    frDestroyFontRequestAfter(monitor);
  }
}

// 0x1cccc10
static void ActWnd_Release(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  dds3ProcessID_t *v6;

  workdata = proc->workdata;
  ActWnd_ReleaseDraw(proc);
  v6 = &workdata[1];
  if (!dds3ExistProcess(v6))
    return;
  dds3KillProcess(v6, 0);
}

// 0x1cc6390
static void ActWnd_Finish(dds3ProcessID_t *proc) {
  dds3ProcessID_t *v4;
  dds3ProcessID_t *id;

  id = proc;
  if (!dds3ExistProcess(id))
    return;
  v4 = id;
  ActWnd_Release(id);
  dds3KillProcess(id, 0);
  return;
}

// 0x1cccd50
static void MdlDelete(tagLMP_MODEL_WK *wk) {
  tagLMP_MODEL_WK *v3;
  dds3Basic_t *unit;
  tagLMP_MODEL_WK *v5;

  v3 = wk;
  if (wk)
  {
    unit = v3->unit;
    if (unit)
    {
      dds3UnitObjectBasicDelete(unit);
      v5 = wk;
      v5->unit = 0;
      v3 = wk;
    }
    v3->flags &= ~2u;
  }
}

// 0x1cccde0
static void MdlCreate(tagLMP_MODEL_WK *wk, MODELTYPE a_majorNo, LMAP_CHR_MODEL_MINOR a_minorNo, f32 a_scaleDef) {
  dds3ModelHandle_t *v9;
  tagLMP_MODEL_WK *v10;
  u32 v12;
  dds3Basic_t *v14;
  Il2CppObject *ModelHandle;
  dds3ModelHandle_t *v16;
  tagLMP_MODEL_WK *v19;
  tagLMP_MODEL_WK *v20;
  dds3Basic_t *unit;
  tagLMP_MODEL_WK *v22;
  sdfVector4_t v23;
  sdfVector4_t v24;
  sdfVector4_t v25;

  v9 = Allocate(dds3ModelHandle_t);
  _ctor(v9, 0);
  v10 = wk;
  if (!wk)
  {
    goto LABEL_7;
  }
  unit = v10->unit;
  if (unit)
  {
    dds3UnitObjectBasicDelete(unit);
    v22 = wk;
    v22->unit = 0;
    v10 = wk;
  }
  v10->flags &= ~2u;
LABEL_7:
  v12 = dds3SerializeID();
  v23.w = 1.0;
  v23.x = 0.0;
  v23.y = 0.0;
  v23.z = 0.0;
  v25.x = 0.0;
  v25.y = 0.0;
  v25.z = 0.0;
  v25.w = 1.0;
  v14 = dds3UnitObjectBasicAdd(v12, v23, v25);
  v10->unit = v14;
  dds3ObjectBaseMakeUnit(wk->unit, a_majorNo, a_minorNo);
  dds3ObjectBaseOnFlag(&wk->unit, 1u);
  ModelHandle = dds3ObjectBaseGetModelHandle(&wk->unit);
  v16 = ModelHandle;
  if (mdlGetNumOfCut(v16, 0) >= 1)
  {
    mdlSetMotionSpeed(v16, 0.5);
    mdlLoopMotion(v16, 0, 0);
  }
  v19 = wk;
  v19->scale = a_scaleDef;
  v19->scaleDef = a_scaleDef;
  v24.w = 1.0;
  v24.x = a_scaleDef;
  v24.y = a_scaleDef;
  v24.z = a_scaleDef;
  dds3SetSclPoseSet(&v19->unit, v24);
  v20 = wk;
  *(u64 *)&v20->ofsY = 0;
  v20->flags = 3;
}

// 0x1ccd100
static void MdlSetDraw(tagLMP_MODEL_WK *wk, bool a_bDraw) {
  s32 v3;

  if (wk)
  {
    if (a_bDraw)
      v3 = 4;
    else
      v3 = 0;
    wk->flags = wk->flags & 0xFFFFFFFB | v3;
  }
}

// 0x1ccd130
static void MdlSetLink(tagLMP_MODEL_WK *wk, bool a_bLink) {
  s32 v3;

  if (wk)
  {
    if (a_bLink)
      v3 = 8;
    else
      v3 = 0;
    wk->flags = wk->flags & 0xFFFFFFF7 | v3;
  }
}

// 0x1ccd160
static void MdlSetOfsY(tagLMP_MODEL_WK *wk, f32 a_ofsY) {
  if (wk)
    wk->ofsY = a_ofsY;
}

// 0x1ccd170
static void MdlSetOfsLength(tagLMP_MODEL_WK *wk, f32 a_ofsLength) {
  if (wk)
    wk->ofsLength = a_ofsLength;
}

// 0x1ccd180
static void MdlSetTrain(tagLMP_MODEL_WK *wk) {
  tagLMP_MODEL_WK *v5;

  MdlCreate(wk, 2u, 5, LMAP_CHR_MODEL_TRAIN_SCALE);
  v5 = wk;
  if (wk)
  {
    v5->ofsY = 0.0;
    v5->ofsLength = LMAP_CHR_MODEL_TRAIN_OFSLENGTH;
  }
}

// 0x1ccd220
static void MdlSetShip(tagLMP_MODEL_WK *wk) {
  tagLMP_MODEL_WK *v5;

  MdlCreate(wk, 2u, 10, LMAP_CHR_MODEL_SHIP_SCALE);
  v5 = wk;
  if (wk)
  {
    v5->ofsLength = 0.0;
    v5->ofsY = LMAP_CHR_MODEL_SHIP_OFSY;
  }
}

// 0x1ccd2c0
static void MdlUpdate(tagLMP_MODEL_WK *wk) {
  tagLMP_MODEL_WK *v3;
  u32 flags;
  dds3Basic_t *p_unit;
  dds3Basic_t *unit;
  tagLMP_MODEL_WK *v7;
  tagLMP_MODEL_WK *p_fields;
  f32 scale;
  sdfVector4_t v10;

  v3 = wk;
  if (wk)
  {
    flags = v3->flags;
    if ((flags & 2) != 0)
    {
      unit = v3->unit;
      p_unit = &v3->unit;
      if (unit)
      {
        if ((flags & 4) != 0)
          dds3ObjectBaseOffFlag(p_unit, 1u);
        else
          dds3ObjectBaseOnFlag(p_unit, 1u);
        v7 = wk;
        p_fields = &wk->fields;
        scale = v7->scale;
        v10.w = 1.0;
        v10.x = scale;
        v10.y = scale;
        v10.z = scale;
        dds3SetSclPoseSet(&p_fields->unit, v10);
      }
    }
  }
}

// 0x1ccd380
static bool MdlGetDraw(tagLMP_MODEL_WK *wk) {
  if (wk)
  {
    if (wk->unit)
      LOBYTE(wk) = (~wk->flags & 7) == 0;
    else
      LOBYTE(wk) = 0;
  }
  return (char)wk;
}

// 0x1cc33d0
static bool ChrGetDrawVehicle(tagLMAP_CHR_WORK *wk) {
  tagLMP_MODEL_WK *vehicle;

  vehicle = wk->vehicle;
  if (!vehicle)
    return 0;
  if (vehicle->unit)
    return (~vehicle->flags & 7) == 0;
  return 0;
}

// 0x1cc7000
static bool Chr_SetScaleModel(tagLMAP_CHR_WORK *wk, s16 a_mode, s16 a_frame) {
  tagLMAP_CHR_WORK *v4;
  tagLMAP_CHR_UTIL_WORK *scale;
  f32 sclDef;

  v4 = wk;
  scale = wk->scale;
  if (scale->step)
    return 0;
  if (a_mode)
  {
    if (a_mode != 1)
      return 0;
    sclDef = v4->sclDef;
  }
  else
  {
    sclDef = 0.0;
  }
  v4->scl = sclDef;
  scale->mode = a_mode;
  scale->step = 1;
  scale->count = 0;
  scale->frame = a_frame;
  return 1;
}

// 0x1ccd3b0
static s8 Chr_UpdateScaleModel(tagLMAP_CHR_WORK *wk) {
  tagLMAP_CHR_WORK *v2;
  tagLMAP_CHR_UTIL_WORK *scale;
  s32 frame;
  s32 mode;
  f32 v6;
  f32 v7;
  s32 count;

  v2 = wk;
  scale = wk->scale;
  if (scale->step != 1)
    return -1;
  frame = scale->frame;
  mode = (u16)scale->mode;
  v6 = v2->sclDef / (f32)frame;
  if (mode == 1)
    v6 = -v6;
  v7 = v2->scl + v6;
  if (v7 <= 0.0)
    v7 = 0.0;
  v2->scl = v7;
  count = scale->count;
  if (count < frame)
  {
    scale->count = count + 1;
    return -1;
  }
  scale->step = 0;
  scale->count = 0;
  return mode;
}

// 0x1ccd430
static void ChrSetModel(tagLMAP_CHR_WORK *wk, MODELTYPE a_majorNo, LMAP_CHR_MODEL_MINOR a_minorNo) {
  dds3ModelHandle_t *v7;
  tagLMAP_CHR_WORK *v8;
  f32 scl;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 *p_x;
  u32 v22;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3Basic_t *v27;
  tagLMAP_CHR_WORK *v28;
  Il2CppObject *ModelHandle;
  dds3ModelHandle_t *v30;
  sdfPacDecodeResrcHandle_t *v32;
  Il2CppObject *v33;
  char *v34;
  Il2CppObject *v35;
  char *v36;
  pacFileHandle_t *v37;
  sdfPacDecodeResrcHandle_t *Resrc;
  sdfPacDecodeResrcHandle_t *next;
  s32 v40;
  sdfPacDecodeResrcHandle_t *v41;
  f32 v42;
  s32 data;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v45;
  sdfVector4_t v46;
  sdfVector4_t v47;

  v7 = Allocate(dds3ModelHandle_t);
  _ctor(v7, 0);
  v8 = wk;
  v8->modelMajorNo = a_majorNo;
  v8->modelMinorNo = a_minorNo;
  if (a_majorNo != 100)
  {
    scl = v8->scl;
    v10 = 1.0;
    v11 = 0.0;
    v12 = 0.0;
    v13 = 0.0;
    switch (a_minorNo)
    {
      case 1:
      case 9:
        goto LABEL_7;
      case 2:
      case 3:
      case 4:
      case 6:
      case 7:
      case 8:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
        goto LABEL_14;
      case 5:
        v14 = 0.6981317;
        v15 = -1.5707964;
        v16 = -1.5707964;
        goto LABEL_10;
      case 18:
        v32 = Allocate(sdfPacDecodeResrcHandle_t);
        _ctor(v32, 0);
        if (!mdlSearchResrc(a_majorNo, 18))
        {
          LODWORD(pObjectBasic) = wk->modelMinorNo;
          v33 = Box(s32, &pObjectBasic);
          v34 = Format("field{0:x3}", v33, 0);
          data = wk->modelMinorNo;
          v35 = Box(s32, &data);
          v36 = Format("field{0:x3}", v35, 0);
          v37 = pacLoad(v34, v36);
          pacSync(v37);
          Resrc = pacGetResrc(v37);
          if (Resrc)
          {
            next = Resrc;
            v40 = 0;
            do
            {
              if (!v40)
              {
                v41 = pacGetResrc(v37);
                PackDecode(a_majorNo, 18, 257, v41);
              }
              next = next->next;
              --v40;
            }
            while (next);
          }
          pacHandleFree(v37);
        }
        v12 = 0.0;
        v13 = 0.0;
        wk->pos.y = scl * 18.5;
        v42 = scl;
        goto LABEL_16;
      default:
        v12 = 0.0;
        v13 = 0.0;
        if (a_minorNo != 80)
          goto LABEL_14;
LABEL_7:
        v14 = LmapCameraPar[24] * 0.017453292;
        v15 = LmapCameraPar[23] * 0.017453292;
        v16 = LmapCameraPar[25] * 0.017453292;
LABEL_10:
        FromEuler(v15, v14, v16);
        p_x = &vf00.x;
        v11 = p_x[4];
        v12 = p_x[5];
        v13 = p_x[6];
        v10 = p_x[7];
LABEL_14:
        v42 = scl;
LABEL_16:
        v22 = dds3SerializeID();
        x = wk->pos.x;
        y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        v45.x = x;
        v45.y = y;
        v45.z = z;
        v45.w = w;
        v47.x = v11;
        v47.y = v12;
        v47.z = v13;
        v47.w = v10;
        v27 = dds3UnitObjectBasicAdd(v22, v45, v47);
        pObjectBasic = v27;
        v28 = wk;
        v28->unit = v27;
        dds3ObjectBaseMakeUnit(v27, a_majorNo, a_minorNo);
        dds3ObjectBaseOnFlag(pObjectBasic, 1u);
        ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
        v30 = ModelHandle;
        mdlSetMotionSpeed(v30, 0.5);
        mdlLoopMotion(v30, 0, 0);
        if (a_minorNo == 18)
          v30->stat = 4;
        v46.w = 1.0;
        v46.x = v42;
        v46.y = v42;
        v46.z = v42;
        dds3SetSclPoseSet(pObjectBasic, v46);
        wk->flags |= 2u;
        break;
    }
  }
}

// 0x1cc1000
static void Chr_UpdateModel(tagLMAP_CHR_WORK *wk) {
  tagLMAP_CHR_WORK *v3;
  tagLMAP_CHR_UTIL_WORK *scale;
  s32 frame;
  f32 v6;
  f32 v7;
  s32 count;
  s16 v9;
  f32 scl;
  f32 z;
  f32 x;
  f32 y;
  u32 flags;
  s32 lineTableNo;
  f32 v18;
  f32 v19;
  s32 modelMinorNo;
  f32 v21;
  f32 v22;
  _OWORD *p_m00;
  __int128 v25;
  __int128 v26;
  __int128 v27;
  f32 *p_x;
  f32 v32;
  tagLMAP_CHR_WORK *v34;
  u32 v35;
  _OWORD *v37;
  __int128 v38;
  __int128 v39;
  __int128 v40;
  f32 *v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  tagLMP_MODEL_WK *p_fields;
  tagLMAP_CHR_WORK *v49;
  tagLMP_MODEL_WK *vehicle;
  f32 ofsLength;
  f32 v52;
  f32 v53;
  tagLMP_MODEL_WK *v55;
  tagLMP_MODEL_WK *p_vehicle;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 w;
  long f64 v61;
  f32 pos;
  sdfMatrix4_t v63;
  u64 v64;
  s64 v65;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t Row;
  sdfVector4_t v68;
  sdfVector4_t v69;
  sdfVector4_t v70;
  sdfVector4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;

  v64 = 0;
  v65 = 0x3F80000000000000LL;
  v3 = wk;
  memset(&v63, 0, sizeof(v63));
  if (!v3)
    return;
  if ((v3->flags & 2) == 0)
    return;
  pObjectBasic = v3->unit;
  if (!pObjectBasic)
    return;
  v3 = wk;
  scale = v3->scale;
  if (scale->step == 1)
  {
    frame = scale->frame;
    v6 = v3->sclDef / (f32)frame;
    if (scale->mode == 1)
      v6 = -v6;
    v7 = v3->scl + v6;
    if (v7 <= 0.0)
      v7 = 0.0;
    v3->scl = v7;
    count = scale->count;
    if (count >= frame)
    {
      v9 = 0;
      scale->step = 0;
    }
    else
    {
      v9 = count + 1;
    }
    scale->count = v9;
  }
  scl = v3->scl;
  z = v3->pos.z;
  x = v3->pos.x;
  y = v3->pos.y;
  *(f32 *)&v65 = z;
  flags = v3->flags;
  v64 = __PAIR64__(LODWORD(y), LODWORD(x));
  if ((~flags & 0x280) != 0)
    goto LABEL_23;
  goto LABEL_9000;
  if ((~flags & 0x280) != 0)
  {
LABEL_23:
    dds3ObjectBaseOnFlag(pObjectBasic, 1u);
    goto LABEL_26;
  }
LABEL_9000:
  lineTableNo = wk->lineTableNo;
  if (dmLMAP_LINE_NO(lineTableNo) == 900)
    goto LABEL_23;
  dds3ObjectBaseOffFlag(pObjectBasic, 1u);
LABEL_26:
  v18 = 1.0;
  v19 = 0.0;
  pos = z;
  modelMinorNo = wk->modelMinorNo;
  v21 = 0.0;
  v22 = 0.0;
  switch (modelMinorNo)
  {
    case 1:
    case 9:
      goto LABEL_36;
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
      goto LABEL_42;
    case 5:
    case 10:
      p_m00 = &IdentityMatrix.m00;
      v25 = p_m00[2];
      v26 = p_m00[3];
      v27 = p_m00[1];
      *(_OWORD *)&v63.m00 = *p_m00;
      *(_OWORD *)&v63.m01 = v27;
      *(_OWORD *)&v63.m02 = v25;
      *(_OWORD *)&v63.m03 = v26;
      Row = GetRow(&v63, 1, 0);
      vct_A = Row;
      FromRotation(wk->degree * 0.017453292);
LABEL_40:
      p_x = &vf00.x;
      v19 = p_x[4];
      v21 = p_x[5];
      v22 = p_x[6];
      v18 = p_x[7];
LABEL_42:
      v32 = 1.0;
      v69.z = pos;
      v69.x = x;
      v69.y = y;
      v69.w = 1.0;
      dds3SetPosPoseSet(pObjectBasic, v69);
      v70.x = v19;
      v70.y = v21;
      v70.z = v22;
      v70.w = v18;
      dds3SetRotPoseSet(pObjectBasic, v70);
      v71.x = scl;
      v71.y = scl;
      v71.z = scl;
      v71.w = 1.0;
      dds3SetSclPoseSet(pObjectBasic, v71);
      v34 = wk;
      v35 = wk->vehicle->flags;
      if ((v35 & 2) == 0)
        return;
      if ((v35 & 8) == 0)
        goto LABEL_62;
      v37 = &IdentityMatrix.m00;
      v38 = v37[2];
      v39 = v37[3];
      v40 = v37[1];
      *(_OWORD *)&v63.m00 = *v37;
      *(_OWORD *)&v63.m01 = v40;
      *(_OWORD *)&v63.m02 = v38;
      *(_OWORD *)&v63.m03 = v39;
      v68 = GetRow(&v63, 1, 0);
      vct_A = v68;
      FromRotation(wk->degree * 0.017453292);
      v43 = &vf00.x;
      v44 = v43[4];
      v45 = v43[5];
      v46 = v43[6];
      v47 = v43[7];
      p_fields = &wk->vehicle->fields;
      v72.x = v44;
      v72.y = v45;
      v72.z = v46;
      v72.w = v47;
      dds3SetRotPoseSet(&p_fields->unit, v72);
      v49 = wk;
      vehicle = wk->vehicle;
      ofsLength = vehicle->ofsLength;
      v52 = y + vehicle->ofsY;
      *((f32 *)&v64 + 1) = v52;
      if (ofsLength == 0.0)
      {
        v53 = pos;
        v55 = &vehicle->fields;
        goto LABEL_61;
      }
      v57 = v49->line.x;
      v58 = v49->line.y;
      v59 = v49->line.z;
      w = v49->line.w;
      sub_1B332C0(0, v57, v58, v59, w);
      sub_1B33480(0, wk->vehicle->ofsLength);
      sub_1B33360(0, x, v52, pos, 1.0);
      *(__n128 *)&v61 = sub_1B33520(0);
      sub_1B335A0(&v64, 0, v61);
      v52 = *((f32 *)&v64 + 1);
      LODWORD(x) = v64;
      v32 = *((f32 *)&v65 + 1);
      v53 = *(f32 *)&v65;
      v55 = &wk->vehicle->fields;
LABEL_61:
      v73.x = x;
      v73.y = v52;
      v73.z = v53;
      v73.w = v32;
      dds3SetPosPoseSet(&v55->unit, v73);
      v34 = wk;
LABEL_62:
      p_vehicle = &v34->vehicle;
      MdlUpdate(p_vehicle);
      break;
    default:
      v21 = 0.0;
      v22 = 0.0;
      if (modelMinorNo != 80)
        goto LABEL_42;
LABEL_36:
      FromEuler(LmapCameraPar->ChrAngle.x * 0.017453292, LmapCameraPar->ChrAngle.y * 0.017453292, LmapCameraPar->ChrAngle.z * 0.017453292);
      goto LABEL_40;
  }
}

// 0x1ccd9e0
static bool Chr_SetParam(tagLMAP_CHR_WORK *wk, s8 charaId, s8 charaNo, s8 worldId, s8 moveId, s8 moveNo, s16 pointNo) {
  tagLMAP_CHR_WORK *v15;
  u32 flags;
  tagLMAP_CHR_WORK *v19;

  v15 = wk;
  if (wk)
  {
    flags = v15->flags;
    *(u16 *)&v15->bDirectAngle = 0;
    v15->moveId = moveId;
    v15->moveNo = moveNo;
    v15->charaId = charaId;
    v15->charaNo = charaNo;
    v15->worldId = worldId;
    v15->flags = flags | 0xA0000001;
    MapDat_GetPointXY(pointNo, &v15->pos.x, &v15->pos.z);
    v19 = wk;
    v19->pos.y = 0.0;
    v19->pos.w = 1.0;
    v19->basePointNo = pointNo;
    *(u32 *)&v19->nextPointNo = -1;
    v19->scl = LMAP_CHR_MODEL_DEF_SIZE;
    v19->sclDef = LMAP_CHR_MODEL_DEF_SIZE;
    v19->portTableNo = Chr_GetNearPortTableNo(v19);
  }
  return v15 != 0;
}

// 0x1cce080
static bool _Chr_SetPlayer(tagLMAP_CHR_WORK *wk, s8 moveNo, s16 pointNo) {
  s8 v8;
  bool v10;
  s32 v12;

  if (moveNo < 0)
    v8 = 1;
  else
    v8 = 7;
  v10 = Chr_SetParam(wk, 1, 255, 3, v8, moveNo, pointNo);
  if (v10)
  {
    ChrSetModel(wk, 2u, 1);
    v12 = 0;
    wk->flags |= 0x208u;
    while ((dmLMAP_LINE_NO(v12) & 0x8000) == 0)
    {
      if (dmLMAP_LINE_POINT_A(v12) == pointNo)
        goto LABEL_22;
      if (dmLMAP_LINE_POINT_B(v12) == pointNo)
      {
LABEL_22:
        wk->lineTableNo = v12;
        return v10;
      }
      ++v12;
    }
  }
  return v10;
}

// 0x1cce1e0
static bool _Chr_SetKaya(tagLMAP_CHR_WORK *wk, s8 moveNo, s16 pointNo) {
  bool v9;
  int32x2_t *v11;
  s32 v14;

  wk->flags |= 0x281u;
  v9 = Chr_SetParam(wk, 4, 65, 3, 0, 0, pointNo);
  if (v9)
  {
    v11 = wk;
    v11[12].n64_u8[3] = 9;
    v11[10].n64_u64[0] = vdup_n_s32(0x3E75C28Fu).n64_u64[0];
    ChrSetModel(wk, 2u, 80);
    v14 = 0;
    while ((dmLMAP_LINE_NO(v14) & 0x8000) == 0)
    {
      if (dmLMAP_LINE_POINT_A(v14) == pointNo)
        goto LABEL_19;
      if (dmLMAP_LINE_POINT_B(v14) == pointNo)
      {
LABEL_19:
        wk->lineTableNo = v14;
        return v9;
      }
      ++v14;
    }
  }
  return v9;
}

// 0x1cce350
static bool _Chr_SetKaya_Load(tagLMAP_CHR_WORK *wk) {
  tagLMAP_CHR_WORK *v4;
  tagLMAP_CHR_WORK *v6;
  dds3AdditionWork_t *AdditionWork_local;
  tagLMAP_CHR_WORK *v9;
  tagLMAP_CHR_WORK *v10;
  dds3AdditionWork_t *v12;

  v4 = wk;
  if (wk)
  {
    v6 = wk;
    AdditionWork_local = AdditionWork;
    v4->charaId = AdditionWork_local->charaId;
    v6->charaNo = AdditionWork_local->charaNo;
    *(u16 *)&v6->worldId = *(u16 *)&AdditionWork_local->worldId;
    v6->moveNo = AdditionWork_local->moveNo;
    *(u16 *)&v6->bDirectAngle = *(u16 *)&AdditionWork_local->bDirectAngle;
    v6->flags = AdditionWork_local->flags;
    v6->pos = AdditionWork_local->pos;
    v9 = wk;
    v10 = wk;
    v12 = AdditionWork;
    v9->scl = LMAP_CHR_MODEL_DEF_SIZE;
    v10->sclDef = v12->sclDef;
    *(int16x4_t *)&v10->basePointNo = vuzp1_s16(*(int16x4_t *)&v12->basePointNo, vext_s8(*(int8x8_t *)&v12->basePointNo, *(int8x8_t *)&v12->basePointNo, 6u));
    v10->line = v12->line;
    wk->flags |= 0x281u;
    ChrSetModel(wk, 2u, 80);
  }
  return v4 != 0;
}

// 0x1cce4b0
static bool _Chr_SetPlayer_Load(tagLMAP_CHR_WORK *wk) {
  tagLMAP_CHR_WORK *v4;
  tagLMAP_CHR_WORK *v6;
  dds3AdditionWork_t *AdditionWork_local;
  tagLMAP_CHR_WORK *v9;
  tagLMAP_CHR_WORK *v10;
  dds3AdditionWork_t *v12;
  tagLMAP_CHR_WORK *v14;
  dds3AdditionWork_t *v15;

  v4 = wk;
  if (wk)
  {
    v6 = wk;
    AdditionWork_local = AdditionWork;
    v4->charaId = AdditionWork_local->charaId;
    v6->charaNo = AdditionWork_local->charaNo;
    *(u16 *)&v6->worldId = *(u16 *)&AdditionWork_local->worldId;
    v6->moveNo = AdditionWork_local->moveNo;
    *(u16 *)&v6->bDirectAngle = *(u16 *)&AdditionWork_local->bDirectAngle;
    v6->flags = AdditionWork_local->flags;
    v6->pos = AdditionWork_local->pos;
    v9 = wk;
    v10 = wk;
    v12 = AdditionWork;
    v9->scl = LMAP_CHR_MODEL_DEF_SIZE;
    v10->sclDef = v12->sclDef;
    *(int16x4_t *)&v10->basePointNo = vuzp1_s16(*(int16x4_t *)&v12->basePointNo, vext_s8(*(int8x8_t *)&v12->basePointNo, *(int8x8_t *)&v12->basePointNo, 6u));
    v10->line = v12->line;
    v14 = wk;
    v15 = AdditionWork;
    loadMode = 0;
    v14->taraFlag = v15->taraFlag;
    ChrSetModel(wk, 2u, 1);
    wk->flags |= 0x208u;
  }
  return v4 != 0;
}

// 0x1cca3f0
static bool Chr_SetPlayer(tagLMAP_CHR_WORK *wk, s16 pointNo) {
  if (loadMode)
  {
    return _Chr_SetPlayer_Load(wk);
  }
  return _Chr_SetPlayer(wk, 255, pointNo);
}

// 0x1cce630
static bool Chr_SetPlayerRoute(tagLMAP_CHR_WORK *wk, s8 moveNo, s16 pointNo) {
  return _Chr_SetPlayer(wk, moveNo, pointNo);
}

// 0x1ccb2d0
static bool ChrSetNpc(tagLMAP_CHR_WORK *wk, s8 a_charNo, s16 a_pointNo, MODELTYPE a_majorNo, LMAP_CHR_MODEL_MINOR a_minorNo, f32 a_scale) {
  bool v15;
  tagLMAP_CHR_WORK *v16;

  v15 = Chr_SetParam(wk, 4, a_charNo, 3, 0, 0, a_pointNo);
  if (v15)
  {
    v16 = wk;
    v16->scl = a_scale;
    v16->sclDef = a_scale;
    ChrSetModel(wk, a_majorNo, a_minorNo);
  }
  return v15;
}

// 0x1cce6b0
static bool Chr_UpdateLineData(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk) {
  sdfVector4_t *v5;
  s64 v7;
  s32 v8;
  s32 v9;
  s64 v10;
  u16 v20;
  u16 v22;
  s32 basePointNo;
  u16 v25;
  bool v26;
  s64 v27;
  s64 v28;
  s16 v29;
  s64 v30;
  __int128 v33;
  f32 *p_x;
  f32 z;
  f32 v39;
  f32 y;
  s64 v42;
  s64 v43;
  struct sdfVector4_t v45;
  s16 v46;
  s64 v47;
  s32 v48;
  s64 v49;
  f32 *v51;
  f32 v52;
  f32 v53;
  f32 v54;
  s64 v56;
  f32 v57;
  sdfVector4_t *v61;
  s64 v62;
  s64 v63;
  s32 *v64;
  struct sdfVector4_t v65;
  struct sdfVector4_t pad;
  struct sdfVector4_t v69;
  struct sdfVector4_t v70;
  struct sdfVector4_t v71;
  __int128 v72;
  __int128 x;
  f32 *v74;

  x = xmmword_3CFD5C0;
  v72 = xmmword_3CFD5C0;
  v5 = NewSpecific(sdfVector4_t, 4u);
  v74 = NewSpecific(f32, 4u);
  v64 = NewSpecific(s32, 4u);
  v63 = NewSpecific(s16, 4u);
  v7 = NewSpecific(s16, 4u);
  v8 = 0;
  v9 = 0;
  v61 = &v5[0];
  while (1)
  {
    if (dmLMAP_LINE_NO(v9) < 0)
      break;
    if (!chrwk->bMoveAllLine && chrwk->moveId <= 5 && (chrwk->flags & 0x40) == 0)
    {
      if (lockwk->lineNo[0] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (lockwk->lineNo[1] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (lockwk->lineNo[2] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (lockwk->lineNo[3] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (lockwk->lineNo[4] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (lockwk->lineNo[5] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (lockwk->lineNo[6] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (lockwk->lineNo[7] == dmLMAP_LINE_NO(v9))
        goto LABEL_5;
      if (dmLMAP_LINE_TYPE(v9))
        goto LABEL_5;
    }
    v20 = dmLMAP_LINE_POINT_A(v9);
    v22 = dmLMAP_LINE_POINT_B(v9);
    basePointNo = (u16)chrwk->basePointNo;
    if (basePointNo == v20)
    {
      v25 = v20;
      v20 = v22;
LABEL_54:
      v27 = 2 * v8;
      *(u16 *)(v63 + v27 + 32) = v25;
      *(u16 *)(v7 + v27 + 32) = v20;
      v28 = v7;
      v29 = *(u16 *)(v63 + v27 + 32);
      v30 = v8;
      MapDat_GetPointXY(v29, &x, (f32 *)&x + 2);
      MapDat_GetPointXY(*(u16 *)(v28 + 2 * v8 + 32), &v72, (f32 *)&v72 + 2);
      v65 = (struct sdfVector4_t)v72;
      goto LABEL_58;
LABEL_59:
      vct_A = v65;
      v33 = x;
      goto LABEL_60;
LABEL_61:
      vct_B = (struct sdfVector4_t)v33;
      goto LABEL_62;
LABEL_58:
      goto LABEL_59;
LABEL_60:
      goto LABEL_61;
LABEL_62:
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      sub_1949110(0);
      ++v8;
      v61[v30] = vct_A;
      v10 = (s64)(char *)v64 + 4 * v30;
      v7 = v28;
      *(u32 *)(v10 + 32) = v9;
      goto LABEL_5;
    }
    v26 = basePointNo == v22;
    v25 = v22;
    if (v26)
      goto LABEL_54;
LABEL_5:
    ++v9;
  }
  if (v8 <= 0)
  {
    v46 = -1;
    chrwk->lineTableNo = -1;
    goto LABEL_117;
  }
  pad = chrwk->pad;
  vct_B = pad;
  v69 = *v61;
  goto LABEL_81;
LABEL_82:
  vct_A = v69;
  goto LABEL_83;
LABEL_81:
  goto LABEL_82;
LABEL_83:
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  goto LABEL_86;
LABEL_87:
  goto LABEL_88;
LABEL_86:
  p_x = &vf00.x;
  z = p_x[6];
  v39 = p_x[4];
  y = p_x[5];
  goto LABEL_87;
LABEL_88:
  v42 = v74;
  v74[0] = sqrtf((f32)((f32)(v39 * v39) + (f32)(y * y)) + (f32)(z * z));
  if (v8 != 1)
  {
    v62 = v7;
    v47 = 0;
    v48 = 0;
    v49 = v42 + 36;
    while (1)
    {
      v70 = *(sdfVector4_t *)((s64)&v5[1] + 16 * v47);
      vct_A = v70;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v51 = &vf00.x;
      v52 = v51[4];
      v53 = v51[5];
      v54 = v51[6];
      v56 = (s64)(char *)v74 + 4 * v48;
      v57 = sqrtf((f32)((f32)(v52 * v52) + (f32)(v53 * v53)) + (f32)(v54 * v54));
      *(f32 *)(v49 + 4 * v47) = v57;
      if (v57 > *(f32 *)(v56 + 32))
        v48 = v47 + 1;
      if ((u32)v8 - 1 == ++v47)
      {
        v43 = v48;
        v7 = v62;
        v45 = v5[v43];
        goto LABEL_116;
      }
    }
  }
  v43 = 0;
  v45 = v5[0];
  v71 = v45;
  v45 = v71;
LABEL_116:
  chrwk->line = v45;
  chrwk->lineTableNo = v64[v43];
  chrwk->basePointNo = *(u16 *)(v63 + 2 * v43 + 32);
  v46 = *(u16 *)(v7 + 2 * v43 + 32);
LABEL_117:
  chrwk->nextPointNo = v46;
  return 1;
}

// 0x1ccf1a0
static void ChrCalcLineVector(tagLMAP_CHR_WORK *chrwk) {
  sdfVector4_t *v3;
  f32 *v4;
  f32 y;
  f32 x;
  int32x2_t v7;
  float32x2_t v8;
  tagLMAP_CHR_WORK *v9;
  struct sdfVector4_t pad;
  struct sdfVector4_t v12;
  f32 *p_x;
  f32 z;
  f32 v15;
  f32 v16;
  s32 v18;
  struct sdfVector4_t v19;
  f32 *v21;
  f32 v22;
  f32 v23;
  f32 v24;
  tagLMAP_CHR_WORK *v26;
  u32 flags;
  f32 v28;
  f32 v29;
  struct sdfVector4_t v32;
  s32 v33;
  f32 v34;
  struct sdfVector4_t v35;
  u64 v40;
  f32 v41;
  struct sdfVector4_t v42;
  struct sdfVector4_t v47;
  struct sdfVector4_t v48;

  v3 = NewSpecific(sdfVector4_t, 2u);
  v4 = NewSpecific(f32, 2u);
  x = chrwk->line.x;
  y = chrwk->line.y;
  v7.n64_u64[0] = *(u64 *)&chrwk->line.z;
  v40 = *(u64 *)&chrwk->line.z;
  v41 = chrwk->line.y;
  v7.n64_u64[0] = v40;
  y = v41;
  *(int32x2_t *)&v3[0].z = v7;
  v8.n64_u32[1] = vdup_lane_s32(v7, 0).n64_u32[1];
  v3[0].x = x;
  v3[0].y = y;
  *(u32 *)&v3[1].w = 1065353216;
  v9 = chrwk;
  v3[1].x = -x;
  v8.n64_f32[0] = y;
  *(float32x2_t *)&v3[1].y = vneg_f32(v8);
  pad = v9->pad;
  vct_B = pad;
  v12 = v3[0];
  vct_A = v12;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  v15 = p_x[4];
  v16 = p_x[5];
  v18 = (u8)byte_5755EF5;
  v4[0] = sqrtf((f32)((f32)(v15 * v15) + (f32)(v16 * v16)) + (f32)(z * z));
  v19 = v3[1];
  if (v18)
  {
    goto LABEL_17;
  }
  else
  {
    v47 = v3[1];
    v19 = v47;
LABEL_17:
    vct_A = v19;
    goto LABEL_18;
  }
  v48 = v19;
  vct_A = v48;
LABEL_18:
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v21 = &vf00.x;
  v22 = v21[4];
  v23 = v21[5];
  v24 = v21[6];
  v26 = chrwk;
  flags = chrwk->flags;
  v28 = sqrtf((f32)((f32)(v22 * v22) + (f32)(v23 * v23)) + (f32)(v24 * v24));
  v4[1] = v28;
  if ((flags & 0x20000000) != 0)
  {
    v28 = v28 + 0.5;
    v4[1] = v28;
    v29 = v4[0];
    if ((flags & 0x40000000) == 0)
    {
LABEL_25:
      if (v29 > v28)
        goto LABEL_26;
LABEL_30:
      v35 = v3[1];
      v33 = 0x8000000;
      v42 = v35;
      goto LABEL_32;
    }
  }
  else
  {
    v29 = v4[0];
    if ((flags & 0x40000000) == 0)
      goto LABEL_25;
  }
  v34 = v29 + 0.5;
  v4[0] = v34;
  if (v34 <= v28)
    goto LABEL_30;
LABEL_26:
  v32 = v3[0];
  v33 = 0x10000000;
  v42 = v32;
LABEL_32:
  v26->flags = flags & 0xE7FFFFFF | v33;
  vct_A = v42;
}

// 0x1ccf710
static void ChrCalcDegree(tagLMAP_CHR_WORK *wk, bool a_bDirect) {
  long f64 v5;
  f32 v6;
  f32 degree;
  f32 v8;
  f32 v9;

  v5 = sub_18E6660(0, a_bDirect);
  v6 = (f32)(*(f32 *)&v5 * 57.29578) + 90.0;
  if (v6 > 180.0)
    v6 = v6 + -360.0;
  if (v6 < -180.0)
    v6 = v6 + 360.0;
  if (!a_bDirect)
  {
    degree = wk->degree;
    if (degree > 180.0)
      degree = degree + -360.0;
    if (degree < -180.0)
      degree = degree + 360.0;
    v8 = v6 - degree;
    if (v8 > 180.0)
      v8 = v8 + -360.0;
    if (v8 < -180.0)
      v8 = v8 + 360.0;
    v9 = -16.0;
    if (v8 >= -16.0)
    {
      v9 = 16.0;
      if (v8 <= 16.0)
        v9 = v8;
    }
    v6 = degree + v9;
  }
  wk->degree = v6;
}

// 0x1ccf820
static void Chr_SetBasePointNo(tagLMAP_CHR_WORK *chrwk, s16 a_tblno) {
  tagLMAP_CHR_WORK *v5;
  s16 v6;
  tagLMAP_CHR_WORK *v7;

  v5 = chrwk;
  v6 = dmLMAP_POINT_NO(a_tblno);
  v7 = chrwk;
  v5->basePointNo = v6;
  *(u32 *)&v7->nextPointNo = -1;
  v7->flags = v7->flags & 0x7FFFFFF | 0xA0000000;
}

// 0x1cc9b30
static void Chr_SetLinePoint(tagLMAP_CHR_WORK *chrwk, s16 a_tgtPointNo) {
  s32 v5;
  s32 v6;
  tagLMAP_CHR_WORK *v9;
  tagLMAP_CHR_WORK *v10;
  tagLMAP_CHR_WORK *v13;
  s16 v14;
  tagLMAP_CHR_WORK *v15;

  v5 = 0;
  v6 = 0;
  while ((dmLMAP_POINT_NO(v6) & 0x8000) == 0)
  {
    if (dmLMAP_POINT_NO(v6) == a_tgtPointNo)
    {
      v9 = chrwk;
      v9->pos.x = (f32)dmLMAP_POINT_X(v6);
      v10 = chrwk;
      chrwk->pos.y = 0.0;
      v10->pos.z = (f32)dmLMAP_POINT_Y(v6);
      v13 = chrwk;
      v14 = dmLMAP_POINT_NO(v5 >> 16);
      v15 = chrwk;
      v13->basePointNo = v14;
      *(u32 *)&v15->nextPointNo = -1;
      v15->flags = v15->flags & 0x7FFFFFF | 0xA0000000;
      return;
    }
    ++v6;
    v5 += 0x10000;
  }
}

// 0x1ccf8b0
static s8 Chr_CalcPosition(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk) {
  sdfVector4_t *v4;
  f32 *v6;
  f32 v12;
  f32 y;
  s64 v14;
  f32 length;
  f32 v17;
  f32 v19;
  struct sdfVector4_t pos;
  tagLMAP_CHR_WORK *v23;
  u32 flags;
  s32 basePointNo;
  f32 *v27;
  f32 *v28;
  s32 v32;
  s32 v33;
  f32 v34;
  f32 *p_x;
  struct sdfVector4_t v37;
  f32 *v38;
  f32 v39;
  f32 v40;
  f32 z;
  tagLMAP_CHR_WORK *v43;
  s32 moveId;
  f32 v45;
  s64 v46;
  s16 *pointNo;
  u64 v48;
  s32 v49;
  tagLMAP_CHR_WORK *v51;
  u32 v52;
  struct sdfVector4_t v53;
  f32 v56;
  f32 v57;
  f32 LMAP_CHR_AREA_LENGTH_local;
  struct sdfVector4_t v63;
  f32 v64;
  tagLMAP_CHR_WORK *v65;
  tagLMAP_CHR_WORK *v70;
  s32 v71;
  f32 *v73;
  f32 v74;
  f32 v75;
  f32 v76;
  tagLMAP_CHR_WORK *v78;
  f32 v79;
  s32 nextPointNo;
  f32 *v81;
  f32 *v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v88;
  f32 v89;
  s32 v91;
  s16 v95;
  tagLMAP_CHR_WORK *v97;
  s16 v98;
  tagLMAP_CHR_WORK *v99;
  s64 v100;
  f32 v101;
  struct sdfVector4_t v102;
  struct sdfVector4_t v105;
  struct sdfVector4_t v106;
  struct sdfVector4_t v107;
  f32 *x;
  f32 *xa[2];

  v4 = NewSpecific(sdfVector4_t, 2u);
  v6 = NewSpecific(f32, 2u);
  ChrCalcLineVector(chrwk);
  v12 = vct_A.x;
  y = vct_A.y;
  v14 = *(u64 *)&vct_A.z;
  length = chrwk->length;
  v100 = v14;
  if ((chrwk->flags & 0x20) == 0)
  {
    v17 = length / (f32)(LMAP_PAD_ANALOG_MASK * 1.5);
    v101 = v17;
LABEL_15:
    goto LABEL_16;
  }
  v19 = (f32)(length / (f32)(LMAP_PAD_ANALOG_MASK * 1.5)) * 1.5;
  v101 = v19;
  goto LABEL_15;
LABEL_16:
  vct_A.x = v12;
  vct_A.y = y;
  *(u64 *)&vct_A.z = v100;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v101);
  pos = chrwk->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  x = &v4[0];
  *(sdfVector4_t *)x = vct_A;
  v23 = chrwk;
  flags = chrwk->flags;
  v6[0] = v101;
  if ((flags & 0x8000000) != 0)
  {
    basePointNo = (u16)v23->basePointNo;
    v27 = &v4[1];
    v28 = &v4[1].z;
    goto LABEL_31;
  }
  if ((flags & 0x10000000) == 0)
  {
    basePointNo = 0xFFFF;
    v27 = &v4[1];
    v28 = &v4[1].z;
    goto LABEL_31;
  }
  basePointNo = (u16)v23->nextPointNo;
  v27 = &v4[1];
  v28 = &v4[1].z;
LABEL_31:
  MapDat_GetPointXY(basePointNo, v27, v28);
  v32 = *(u32 *)&v4[1];
  v33 = *(u32 *)&v4[1].z;
  v34 = chrwk->pos.y;
  *(u32 *)&v4[1].w = 1065353216;
  v4[1].y = v34;
  p_x = &vf00.x;
  *((u32 *)p_x + 4) = v32;
  p_x[5] = v34;
  *((u32 *)p_x + 6) = v33;
  p_x[7] = 1.0;
  v37 = chrwk->pos;
  vct_B = v37;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v38 = &vf00.x;
  v39 = v38[4];
  v40 = v38[5];
  z = v38[6];
  v43 = chrwk;
  moveId = chrwk->moveId;
  v45 = sqrtf((f32)((f32)(v39 * v39) + (f32)(v40 * v40)) + (f32)(z * z));
  v6[1] = v45;
  if (moveId > 5 || (v43->flags & 0x40) != 0)
  {
LABEL_48:
    v49 = 0;
    v51 = chrwk;
    if (v6[0] >= v45)
    {
LABEL_98:
      if (v52)
      {
        v51->pos = *(sdfVector4_t *)v27;
        if (v49)
          goto LABEL_100;
LABEL_162:
        v95 = 0;
        while ((dmLMAP_POINT_NO(v95) & 0x8000) == 0)
        {
          if (basePointNo == (u16)dmLMAP_POINT_NO(v95))
            goto LABEL_175;
          ++v95;
        }
        v95 = -1;
LABEL_175:
        v97 = chrwk;
        v98 = dmLMAP_POINT_NO(v95);
        v99 = chrwk;
        v97->basePointNo = v98;
        *(u32 *)&v99->nextPointNo = -1;
        v99->flags = v99->flags & 0x7FFFFFF | 0xA0000000;
        v105 = v99->pos;
LABEL_101:
        vct_B = v105;
        *(u32 *)&v4[0].y = 0;
        *(u32 *)&v4[0].w = 1065353216;
        *(u32 *)&v6[0] = -1082130432;
        v70 = chrwk;
        v71 = chrwk->basePointNo;
        chrwk->flags &= 0x9FFFFFFF;
        if (v71 < 0)
        {
          v79 = -1.0;
          nextPointNo = v70->nextPointNo;
          *(u32 *)&v6[1] = -1082130432;
          if ((nextPointNo & 0x80000000) == 0)
          {
LABEL_116:
            v81 = &v4[0].z;
            MapDat_GetPointXY(nextPointNo, x, v81);
            *(_OWORD *)xa = *(_OWORD *)x;
            vct_A = *(sdfVector4_t *)xa;
            vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
            v83 = &vf00.x;
            v84 = v83[4];
            v85 = v83[5];
            v86 = v83[6];
            v88 = v86 * v86;
            v79 = v6[0];
            v89 = sqrtf((f32)((f32)(v84 * v84) + (f32)(v85 * v85)) + v88);
            v6[1] = v89;
            if (v79 > v89)
            {
              if (v79 >= 0.0 && v89 > v79)
                return 1;
              if (v89 > LMAP_CHR_AREA_LENGTH)
                return 1;
              v91 = 0x40000000;
              goto LABEL_141;
            }
            goto LABEL_136;
          }
LABEL_135:
          if (v79 > LMAP_CHR_AREA_LENGTH)
            return 1;
          goto LABEL_140;
LABEL_136:
          if (v79 > LMAP_CHR_AREA_LENGTH)
            return 1;
LABEL_140:
          v91 = 0x20000000;
LABEL_141:
          chrwk->flags |= v91;
          return 1;
        }
        MapDat_GetPointXY(v71, x, &v4[0].z);
        v106 = *(sdfVector4_t *)x;
        vct_A = v106;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        v73 = &vf00.x;
        v74 = v73[6];
        v75 = v73[4];
        v76 = v73[5];
        v78 = chrwk;
        v79 = sqrtf((f32)((f32)(v75 * v75) + (f32)(v76 * v76)) + (f32)(v74 * v74));
        v6[0] = v79;
        nextPointNo = v78->nextPointNo;
        *(u32 *)&v6[1] = -1082130432;
        if ((nextPointNo & 0x80000000) == 0)
          goto LABEL_116;
        goto LABEL_135;
      }
      v107 = *(sdfVector4_t *)v27;
      v51->pos = v107;
      if (!v49)
        goto LABEL_162;
LABEL_100:
      v65 = chrwk;
      v65->flags = chrwk->flags & 0x7FFFFFFF;
      v105 = v65->pos;
      goto LABEL_101;
    }
LABEL_49:
    v53 = *(sdfVector4_t *)x;
    if (!v52)
    {
      v102 = *(sdfVector4_t *)x;
      v53 = v102;
    }
    v51->pos = v53;
    goto LABEL_100;
  }
  v46 = 0;
  pointNo = lockwk->pointNo;
  while ((u16)pointNo[v46] != basePointNo)
  {
    v48 = v46 | 1;
    if ((u16)pointNo[v46 | 1] == basePointNo)
      break;
    v46 += 2;
    if (v48 >= 0x3F)
      goto LABEL_48;
  }
  if (v45 > LMAP_CHR_AREA_LENGTH)
  {
    v56 = -v12;
    v57 = -y;
    vct_A.x = v56;
    vct_A.y = v57;
    vct_A.z = -*(f32 *)&v100;
    vct_A.w = 1.0;
    LMAP_CHR_AREA_LENGTH_local = LMAP_CHR_AREA_LENGTH;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, LMAP_CHR_AREA_LENGTH_local);
    v63 = *(sdfVector4_t *)v27;
    vct_B = v63;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v49 = 1;
    *(sdfVector4_t *)v27 = vct_A;
    v64 = v6[1] - LMAP_CHR_AREA_LENGTH;
    v6[1] = v64;
    v51 = chrwk;
    if (v6[0] >= v64)
      goto LABEL_98;
    goto LABEL_49;
  }
  return 0;
}

// 0x1cd0840
static s8 Chr_UpdatePosFreePad(tagLMAP_CHR_WORK *wk) {
  f32 length;
  f32 LMAP_PAD_ANALOG_MASK_local;
  f32 v9;
  struct sdfVector4_t pos;
  tagLMAP_CHR_WORK *v11;
  struct sdfVector4_t pad;

  length = wk->length;
  if ((wk->flags & 0x20) != 0)
  {
    LMAP_PAD_ANALOG_MASK_local = LMAP_PAD_ANALOG_MASK;
    pad = wk->pad;
  }
  else
  {
    LMAP_PAD_ANALOG_MASK_local = LMAP_PAD_ANALOG_MASK + LMAP_PAD_ANALOG_MASK;
    pad = wk->pad;
  }
  vct_A = pad;
  v9 = length / LMAP_PAD_ANALOG_MASK_local;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v9);
  pos = wk->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v11 = wk;
  v11->pos = vct_A;
  return 1;
}

// 0x1cd0b00
static s8 check_point_line(const sdfVector2_t *a, const sdfVector2_t *b, const sdfVector2_t *c) {
  f32 y;
  f32 x;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  s8 v11;

  y = c->y;
  x = c->x;
  v6 = b->y;
  v7 = b->x;
  v8 = a->y;
  v9 = a->x;
  v10 = (f32)((f32)(v7 - v9) * (f32)(y - v8)) - (f32)((f32)(v6 - v8) * (f32)(x - v9));
  if (v10 >= 0.0)
    v11 = 0;
  else
    v11 = -1;
  if (v10 > 0.0)
    return 1;
  else
    return v11;
}

// 0x1cd0b90
static s8 check_cross_line2(const sdfVector2_t *a1, const sdfVector2_t *a2, const sdfVector2_t *b1, const sdfVector2_t *b2) {
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v14;
  f32 v15;
  char v16;
  f32 v18;
  f32 v19;
  char v20;

  y = b2->y;
  x = b2->x;
  v7 = b1->y;
  v8 = b1->x;
  v9 = a2->y;
  v10 = a2->x;
  v11 = a1->y;
  v12 = a1->x;
  v14 = (f32)((f32)(v10 - v12) * (f32)(v7 - v11)) - (f32)((f32)(v9 - v11) * (f32)(v8 - v12));
  v15 = (f32)((f32)(v10 - v12) * (f32)(y - v11)) - (f32)((f32)(v9 - v11) * (f32)(x - v12));
  v16 = (v14 < 0.0) ^ (v15 >= 0.0);
  if (v15 > 0.0)
    v16 = 0;
  if (v14 > 0.0)
    v16 = v15 > 0.0;
  if ((v16 & 1) != 0)
    return 0;
  v18 = (f32)((f32)(v11 - v7) * (f32)(x - v8)) - (f32)((f32)(v12 - v8) * (f32)(y - v7));
  v19 = (f32)((f32)(v9 - v7) * (f32)(x - v8)) - (f32)((f32)(v10 - v8) * (f32)(y - v7));
  v20 = (v19 >= 0.0) ^ (v18 < 0.0);
  if (v19 > 0.0)
    v20 = 0;
  if (v18 > 0.0)
    v20 = v19 > 0.0;
  return v20 ^ 1;
}

// 0x1cd0d40
static s8 Chr_UpdatePosShipPad(tagLMAP_CHR_WORK *wk, tagLMAP_LOCK_WORK *lockwk) {
  __int128 v4;
  __int128 v5;
  f32 length;
  f32 v12;
  f32 v16;
  f32 v17;
  f32 z;
  f32 *p_x;
  s16 y;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  s32 v26;
  s32 flag;
  tagLMP_COASTLINE_DAT *v31;
  s32 v32;
  bool v33;
  tagLMP_COASTLINE_DAT *v35;
  s32 v36;
  f32 v38;
  tagLMP_COASTLINE_DAT *v39;
  s32 v40;
  f32 v41;
  tagLMP_COASTLINE_DAT *v43;
  s32 v44;
  f32 v45;
  tagLMP_COASTLINE_DAT *v47;
  s32 v48;
  f32 v49;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  char v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  s32 v66;
  f32 v68;
  f32 v69;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v75;
  u32 *v76;
  s64 v81;
  s32 v83;
  f32 *v85;
  f32 v86;
  f32 v87;
  f32 v88;
  tagLMAP_CHR_WORK *v90;
  struct sdfVector4_t v91;
  tagLMAP_CHR_WORK *v92;
  tagLMAP_CHR_WORK *v93;
  f32 v94;
  f32 v95;
  struct sdfVector4_t v96;
  struct sdfVector4_t v97;
  __int128 v98;
  __int128 v99;
  struct sdfVector4_t pad;
  __int128 v101;
  __int128 v102;
  _OWORD x[2];
  sdfVector4_t v105;
  sdfVector4_t v106;
  sdfVector4_t v107;

  *(u64 *)&x[0] = 0;
  *((u64 *)&x[0] + 1) = 0x3F80000000000000LL;
  length = wk->length;
  if (length < LMAP_PAD_ANALOG_MASK)
    return 0;
  v12 = wk->length;
  pad = wk->pad;
  vct_A = pad;
  v16 = v12 / LMAP_PAD_ANALOG_MASK_SHIP;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v16);
  v17 = wk->pos.x;
  z = wk->pos.z;
  p_x = &vf00.x;
  p_x[8] = v17;
  p_x[9] = 0.0;
  p_x[10] = z;
  p_x[11] = 1.0;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  y = 0;
  v93 = wk;
  *(u64 *)&v5 = *(u64 *)&vct_A.x;
  *(u64 *)&v4 = *(u64 *)&vct_A.z;
  v22 = wk->pos.x;
  v23 = wk->pos.z;
LABEL_24:
  while (2)
  {
    v24 = *(f32 *)&v5 - v22;
    v25 = *(f32 *)&v4 - v23;
    v26 = 0;
    v98 = v5;
    v101 = v4;
LABEL_25:
    while (1)
    {
      if ((v26 & 0x8000) != 0)
        break;
      if ((u16)v26 >= SLODWORD(lmpCoastlineDat->max_length))
        break;
      flag = lmpCoastlineDat[(u16)v26]->flag;
      if (flag >= 1)
        evtBitCheck(flag);
      v31 = lmpCoastlineDat;
      if ((u16)v26 >= SLODWORD(v31->max_length))
        goto LABEL_27;
      v32 = v31[(u16)v26]->flag;
      if (v32 < 1)
      {
        if ((v32 & 0x80000000) == 0)
          goto LABEL_55;
        goto LABEL_27;
      }
      v33 = evtBitCheck(v32);
      if (v33)
      {
LABEL_55:
        goto LABEL_57;
LABEL_58:
        v35 = lmpCoastlineDat;
        if ((u16)v26 >= SLODWORD(v35->max_length))
          goto LABEL_72;
        v36 = v35[(u16)v26]->flag;
        if (v36 < 1)
        {
          if (v36)
            goto LABEL_72;
          goto LABEL_9005;
        }
        if (!evtBitCheck(v36))
          goto LABEL_72;
LABEL_9005:
        y = lmpCoastlineDat[(u16)v26]->x;
        goto LABEL_72;
LABEL_57:
        goto LABEL_58;
LABEL_72:
        v95 = v24;
        v38 = y;
        v39 = lmpCoastlineDat;
        if ((u16)v26 >= SLODWORD(v39->max_length))
        {
          v41 = y;
          goto LABEL_86;
        }
        v40 = lmpCoastlineDat[(u16)v26]->flag;
        if (v40 < 1)
          goto LABEL_84;
        v41 = y;
        if (evtBitCheck(v40))
        {
          goto LABEL_92;
        }
LABEL_85:
        goto LABEL_86;
LABEL_88:
        v44 = v43[(u16)v26]->flag;
        if (v44 >= 1)
          goto LABEL_90;
        v45 = v41;
        if (v44)
          goto LABEL_101;
LABEL_108:
        y = lmpCoastlineDat[(u32)(u16)v26 + 1]->x;
        v45 = y;
        goto LABEL_102;
LABEL_90:
        v45 = v41;
        if (evtBitCheck(v44))
        {
          goto LABEL_108;
        }
LABEL_101:
        goto LABEL_102;
LABEL_103:
        v47 = lmpCoastlineDat;
        if ((u16)v26 < SLODWORD(v47->max_length))
          goto LABEL_104;
        v49 = v45;
        goto LABEL_118;
LABEL_84:
        v41 = y;
        if (v40)
          goto LABEL_85;
LABEL_92:
        y = lmpCoastlineDat[(u16)v26]->y;
        v41 = y;
LABEL_86:
        v43 = lmpCoastlineDat;
        if ((u16)v26 < SLODWORD(v43->max_length))
          goto LABEL_88;
        v45 = v41;
LABEL_102:
        goto LABEL_103;
LABEL_104:
        v48 = lmpCoastlineDat[(u16)v26]->flag;
        if (v48 < 1)
          goto LABEL_116;
        v49 = v45;
        if (evtBitCheck(v48))
        {
          goto LABEL_138;
        }
LABEL_117:
        goto LABEL_118;
LABEL_116:
        v49 = v45;
        if (v48)
          goto LABEL_117;
LABEL_138:
        y = lmpCoastlineDat[(u32)(u16)v26 + 1]->y;
        v49 = y;
LABEL_118:
        v51 = v38 - v22;
        v52 = v41 - v23;
        v94 = v38;
        v53 = v23;
        v54 = v41;
        v55 = v22;
        v56 = v53;
        v24 = v95;
        v57 = (f32)(v95 * v52) - (f32)(v25 * v51);
        v58 = (f32)(v95 * (f32)(v49 - v53)) - (f32)(v25 * (f32)(v45 - v22));
        v59 = (v57 < 0.0) ^ (v58 >= 0.0);
        if (v58 > 0.0)
          v59 = 0;
        if (v57 > 0.0)
          v59 = v58 > 0.0;
        if ((v59 & 1) != 0)
          goto LABEL_137;
        v60 = v49 - v54;
        v61 = v45 - v94;
        v62 = (f32)((f32)(v56 - v54) * (f32)(v45 - v94)) - (f32)((f32)(v22 - v94) * (f32)(v49 - v54));
        v63 = (f32)(*(f32 *)&v98 - v94) * (f32)(v49 - v54);
        v64 = (f32)(*(f32 *)&v101 - v54) * (f32)(v45 - v94);
        v65 = v64 - v63;
        v66 = ((f32)(v64 - v63) >= 0.0) ^ (v62 < 0.0);
        if ((f32)(v64 - v63) > 0.0)
          v66 = 0;
        if (v62 > 0.0)
          v66 = (f32)(v64 - v63) > 0.0;
        if (v66 == 1)
          goto LABEL_137;
        v60 = v49 - v54;
        v61 = v45 - v94;
        v60 = v49 - v54;
        v61 = v45 - v94;
        if (v65 <= 0.0)
        {
LABEL_137:
          ++v26;
          v22 = v55;
          v23 = v56;
          goto LABEL_25;
        }
        v68 = v60;
        v69 = v61;
        *((u64 *)&x[0] + 1) = LODWORD(v54) | 0x3F80000000000000LL;
        *(u64 *)&x[0] = LODWORD(v94);
        v106.w = 1.0;
        v106.y = 0.0;
        v107.y = 0.0;
        v106.z = v54;
        v107.x = v45;
        v107.z = v49;
        v107.w = 1.0;
        v106.x = v94;
        *(u64 *)&v105.z = lockwk;
        v71 = Util_CalcLength(v106, v107, v105);
        v22 = v55;
        v5 = v98;
        v4 = v101;
        v23 = v56;
        v72 = v69;
        v73 = v68;
        v75 = v94;
        v5 = v98;
        v4 = v101;
        v73 = v68;
        v72 = v69;
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v71 + v71);
        v5 = v98;
        v4 = v101;
        v73 = v68;
        v72 = v69;
        v5 = v98;
        v4 = v101;
        v73 = v68;
        v72 = v69;
        v76 = &vf00.x;
        v76[8] = v5;
        v76[9] = 0;
        v76[10] = v4;
        v76[11] = 1065353216;
        v73 = v68;
        v72 = v69;
        v73 = v68;
        v72 = v69;
        vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        *(u64 *)&v5 = *(u64 *)&vct_A.x;
        *(u64 *)&v4 = *(u64 *)&vct_A.z;
        v99 = v5;
        v102 = v4;
        v5 = v99;
        v4 = v102;
        v73 = v68;
        v72 = v69;
        if ((f32)((f32)(v72 * (f32)(*(f32 *)&v4 - v54)) - (f32)(v73 * (f32)(*(f32 *)&v5 - v75))) >= 0.0)
          return 0;
        y = -1;
        goto LABEL_24;
      }
LABEL_27:
      ++v26;
    }
    v5 = v98;
    v4 = v101;
    if (v26 < 1)
      continue;
    break;
  }
  *(u64 *)&v5 = v98;
  *(u64 *)&v4 = v101;
  DWORD1(x[0]) = 0;
  HIDWORD(x[0]) = 1065353216;
  v81 = 32;
  *(u64 *)&vct_B.x = v5;
  *(u64 *)&vct_B.z = v4;
  while (2)
  {
    v83 = *(s16 *)((char *)&lockwk->pointNo->obj.klass + v81);
    if (v83 >= 1)
    {
      MapDat_GetPointXY(v83, x, (f32 *)x + 2);
      v96 = (struct sdfVector4_t)x[0];
      goto LABEL_180;
LABEL_181:
      vct_A = v96;
      goto LABEL_182;
LABEL_183:
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      goto LABEL_184;
LABEL_185:
      v85 = &vf00.x;
      v86 = v85[4];
      v87 = v85[5];
      v88 = v85[6];
      goto LABEL_9010;
LABEL_180:
      goto LABEL_181;
LABEL_182:
      goto LABEL_183;
LABEL_184:
      goto LABEL_185;
LABEL_9010:
      LODWORD(v5) = v98;
      LODWORD(v4) = v101;
      if (sqrtf((f32)((f32)(v86 * v86) + (f32)(v87 * v87)) + (f32)(v88 * v88)) < LMAP_CHR_AREA_LENGTH)
        return 0;
    }
    v81 += 2;
    if (v81 != 160)
      continue;
    break;
  }
  v90 = v93;
  v91 = v93->pad;
  v97 = v93->pad;
  v91 = v97;
  LODWORD(v5) = v98;
  LODWORD(v4) = v101;
  v90->line = v91;
  v92 = v93;
  LODWORD(v92->pos.x) = v5;
  LODWORD(v92->pos.z) = v4;
  return 1;
}

// 0x1cd2410
static s8 Chr_UpdatePosition(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk) {
  tagLMAP_CHR_WORK *v5;
  s32 moveType;
  tagLMAP_LOCK_WORK *v7;
  s8 updated;
  tagLMAP_LOCK_WORK *v9;
  s8 v10;
  tagLMAP_CHR_WORK *v11;
  _BOOL4 bDirectAngle;
  long f64 v15;
  f32 v16;
  tagLMAP_CHR_WORK *v17;
  s32 moveId;
  f32 degree;
  f32 v20;
  f32 v21;
  s32 lineTableNo;
  s32 v23;
  s32 v24;
  s32 v29;
  s16 v32;
  s32 v34;

  v5 = chrwk;
  moveType = (u8)(chrwk)->moveType;
  if (moveType == 3)
  {
    v9 = lockwk;
    updated = Chr_UpdatePosShipPad(chrwk, v9);
LABEL_18:
    v10 = updated;
    v11 = chrwk;
    bDirectAngle = chrwk->bDirectAngle;
    goto LABEL_26;
  }
  if (moveType != 2)
  {
    if (moveType != 1)
    {
      v10 = -1;
      v11 = chrwk;
      bDirectAngle = chrwk->bDirectAngle;
      goto LABEL_26;
    }
    if (v5->length <= 0.0)
      return 0;
    if (v5->lineTableNo < 0 || v5->nextPointNo < 0)
    {
      v7 = lockwk;
      Chr_UpdateLineData(v5, v7);
    }
    updated = Chr_CalcPosition(chrwk, lockwk);
    goto LABEL_18;
  }
  Chr_UpdatePosFreePad(chrwk);
  v10 = 1;
  v11 = chrwk;
  bDirectAngle = chrwk->bDirectAngle;
LABEL_26:
  v15 = sub_18E6660(0, lockwk);
  v16 = (f32)(*(f32 *)&v15 * 57.29578) + 90.0;
  if (v16 > 180.0)
    v16 = v16 + -360.0;
  if (v16 < -180.0)
    v16 = v16 + 360.0;
  if (bDirectAngle)
  {
    v17 = chrwk;
    v11->degree = v16;
    moveId = (u8)v17->moveId;
    if (moveId == 7)
      goto LABEL_47;
  }
  else
  {
    degree = v11->degree;
    if (degree > 180.0)
      degree = degree + -360.0;
    if (degree < -180.0)
      degree = degree + 360.0;
    v20 = v16 - degree;
    if (v20 > 180.0)
      v20 = v20 + -360.0;
    if (v20 < -180.0)
      v20 = v20 + 360.0;
    v21 = -16.0;
    if (v20 >= -16.0)
    {
      v21 = 16.0;
      if (v20 <= 16.0)
        v21 = v20;
    }
    v17 = chrwk;
    v11->degree = degree + v21;
    moveId = (u8)v17->moveId;
    if (moveId == 7)
      goto LABEL_47;
  }
  if (moveId != 8 || v17->exLineType != 1)
    return v10;
LABEL_47:
  lineTableNo = v17->lineTableNo;
  if (lineTableNo < 0)
    return v10;
  v23 = (u16)lineTableNo;
  v24 = (u16)dmLMAP_LINE_NO(v23);
  if (v24 != 902)
  {
    v32 = -1;
    goto LABEL_79;
  }
  Chr_UpdatePosition_fade = (u16)Chr_UpdatePosition_fade;
  if (Chr_UpdatePosition_fade)
    goto LABEL_53;
  goto LABEL_70;
  if (!Chr_UpdatePosition_fade)
  {
LABEL_70:
    v34 = (u16)(chrwk)->lineTableNo;
    if (v34 != (u16)Chr_UpdatePosition_line)
    {
      dds3FadeOut(0, 0, 0, 0x1Eu);
      Chr_UpdatePosition_fade = 1;
      goto LABEL_78;
    }
    return v10;
  }
LABEL_53:
  Chr_UpdatePosition_fade = (u16)Chr_UpdatePosition_fade;
  if (Chr_UpdatePosition_fade != 1)
    return v10;
  v29 = (u16)(chrwk)->lineTableNo;
  if (v29 == (u16)Chr_UpdatePosition_line)
    return v10;
  dds3FadeIn(0, 0, 0, 0x1Eu);
  Chr_UpdatePosition_fade = 0;
LABEL_78:
  v32 = chrwk->lineTableNo;
LABEL_79:
  Chr_UpdatePosition_line = v32;
  return v10;
}

// 0x1cd2850
static void Chr_UpdatePadRandom(tagLMAP_CHR_WORK *wk) {
  s32 v3;
  tagLMAP_CHR_WORK *v4;
  u32 v5;
  tagLMAP_CHR_WORK *v6;
  u32 v7;
  tagLMAP_CHR_WORK *v8;
  s64 v10;
  f32 v11;
  tagLMAP_CHR_WORK *v14;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  tagLMAP_CHR_WORK *v20;
  sdfVector4_t *p_pad;
  s16 v23;
  tagLMAP_CHR_WORK *v24;

  v3 = sub_1905740(2, 0);
  v4 = wk;
  if (!v3)
  {
    v5 = sub_1905740(128, 0);
    v6 = wk;
    v4->pad.x = (f32)v5;
    v6->pad.y = 0.0;
    v6->pad.x = v6->pad.x + -64.0;
    v7 = sub_1905740(128, 0);
    v8 = wk;
    v6->pad.z = (f32)v7;
    v8->pad.w = 1.0;
    v10 = *(u64 *)&v8->pad.x;
    v11 = v8->pad.z + -64.0;
    v8->pad.z = v11;
    *(u64 *)&vct_A.x = v10;
    vct_A.z = v11;
    vct_A.w = 1.0;
    v14 = wk;
    p_x = &vf00.x;
    z = p_x[6];
    x = p_x[4];
    y = p_x[5];
    v14->length = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
    sub_1949110(0);
    v20 = wk;
    p_pad = &v20->pad;
    *p_pad = vct_A;
    v4 = wk;
    goto LABEL_15;
  }
  v4->length = 0.0;
  v4->pad = (struct sdfVector4_t)xmmword_3CFD5C0;
LABEL_15:
  v23 = sub_1905740(60, 0);
  v24 = wk;
  v4->moveCount = v23;
  v24->moveCount += 60;
}

// 0x1cd2b00
static f32 ChrRouteCalcPadParam(s32 pt0, s32 pt1) {
  s16 v4;
  s16 v5;
  struct sdfVector4_t v8;
  f32 *p_x;
  f32 z;
  f32 v11;
  f32 y;
  struct sdfVector4_t v16;
  struct sdfVector4_t v19;
  struct sdfVector4_t x;

  v4 = pt1;
  v5 = pt0;
  x = (struct sdfVector4_t)0;
  v19 = (struct sdfVector4_t)0;
  MapDat_GetPointXY(v5, &x.x, &x.z);
  MapDat_GetPointXY(v4, &v19.x, &v19.z);
  v16 = v19;
  vct_A = v16;
  v8 = x;
  vct_B = v8;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  v11 = p_x[4];
  y = p_x[5];
  sub_1949110(0);
  return sqrtf((f32)((f32)(v11 * v11) + (f32)(y * y)) + (f32)(z * z));
}

// 0x1cd2dd0
static s8 _Chr_UpdatePadRoute(tagLMAP_CHR_WORK *chrwk) {
  s32 moveNo;
  s32 mode;
  u16 RouteDat;
  s32 v9;
  s32 v10;
  s16 v12;
  s64 v13;
  s32 relay;
  s64 v17;
  s8 type;
  s64 v20;
  u8 stat;
  tagLMAP_CHR_WORK *v23;
  s32 basePointNo;
  tagLMAP_CHR_UTIL_WORK *route;
  s32 count;
  f32 v28;
  tagLMAP_CHR_WORK *v29;
  sdfVector4_t *p_pad;
  s32 v32;
  tagLMAP_CHR_WORK *v39;
  tagLMAP_CHR_WORK *v42;
  f32 LMAP_CHR_TRAIN_MOVE_LENGTH_local;
  tagLMAP_CHR_WORK *v44;
  f32 length;

  moveNo = chrwk->moveNo;
  if (moveNo < 0)
    return -2;
  mode = chrwk->route->mode;
  moveNo = (u8)(chrwk)->moveNo;
  RouteDat = MapDat_GetRouteDat(moveNo, mode);
  v9 = chrwk->moveNo;
  v10 = chrwk->route->mode + 1;
  v12 = MapDat_GetRouteDat(v9, v10);
  v13 = chrwk->moveNo;
  relay = (u16)lmap_tbl_route[v13]->relay;
  v17 = chrwk->moveNo;
  type = lmap_tbl_route[v17]->type;
  v20 = chrwk->moveNo;
  stat = lmap_tbl_route[v20]->stat;
  v23 = chrwk;
  basePointNo = (u16)(chrwk)->basePointNo;
  chrwk->bDirectAngle = 0;
  if (basePointNo != RouteDat)
    return -1;
  if ((stat & 1) != 0)
  {
    route = v23->route;
    if (route->mode)
    {
      if ((v12 & 0x80000000) == 0)
      {
        route->count = 0;
        goto LABEL_51;
      }
      count = route->count;
      if (route->count)
      {
        if (count > 89)
        {
          *(u32 *)&route->mode = 0;
          return type;
        }
      }
      else
      {
        v23->flags |= 0xA0000000;
      }
    }
    else
    {
      count = route->count;
      if (count > 89)
        goto LABEL_51;
    }
    v23->length = 0.0;
    route->count = count + 1;
    return -1;
  }
  if (v12 <= 0)
  {
    *(u64 *)&v23->flags = v23->flags | 0xA0000000;
    *(u32 *)&v23->route->mode = 0;
    return type;
  }
  if (relay == RouteDat)
    v23->bDirectAngle = 1;
  else
    v23->route->count = 0;
LABEL_51:
  v28 = ChrRouteCalcPadParam(RouteDat, v12);
  v29 = chrwk;
  p_pad = &v29->pad;
  v32 = 0;
  *p_pad = vct_A;
  while (1)
  {
    if (dmLMAP_LINE_NO(v32) < 0)
      break;
    if (dmLMAP_LINE_NO(v32) != 901)
      goto LABEL_58;
    if (RouteDat != (u16)dmLMAP_LINE_POINT_A(v32))
      goto LABEL_73;
    if (v12 == dmLMAP_LINE_POINT_B(v32))
    {
LABEL_86:
      v42 = chrwk;
      LMAP_CHR_TRAIN_MOVE_LENGTH_local = v28 * LMAP_PAD_ANALOG_MASK;
LABEL_96:
      v42->length = LMAP_CHR_TRAIN_MOVE_LENGTH_local;
      goto LABEL_97;
    }
LABEL_73:
    if (v12 != dmLMAP_LINE_POINT_A(v32))
      goto LABEL_58;
    if (RouteDat == (u16)dmLMAP_LINE_POINT_B(v32))
      goto LABEL_86;
LABEL_58:
    ++v32;
  }
  v39 = chrwk;
  v39->length = LMAP_CHR_ROUTE_MOVE_LENGTH;
  if ((stat & 2) == 0)
  {
    if ((stat & 4) == 0)
      goto LABEL_97;
    goto LABEL_93;
  }
  v44 = chrwk;
  length = chrwk->length;
  v44->length = length + LMAP_CHR_ROUTE_MOVE_LENGTH;
  if ((stat & 4) != 0)
  {
LABEL_93:
    v42 = chrwk;
    LMAP_CHR_TRAIN_MOVE_LENGTH_local = LMAP_CHR_TRAIN_MOVE_LENGTH;
    goto LABEL_96;
  }
LABEL_97:
  ++chrwk->route->mode;
  return -1;
}

// 0x1cd3460
static s8 Chr_UpdatePadRoute(tagLMAP_CHR_WORK *chrwk) {
  tagLMAP_CHR_WORK *v4;
  s64 v5;
  f32 v7;
  f32 z;
  tagLMAP_CHR_UTIL_WORK *route;
  s8 result;
  s8 updated;
  s32 v12;
  tagLMAP_CHR_WORK *v13;
  tagLMAP_CHR_UTIL_WORK *v14;
  tagLMAP_CHR_WORK *v17;
  tagLMAP_CHR_UTIL_WORK *v18;
  f32 v21;
  s32 v22;
  f32 *p_x;
  struct sdfVector4_t pos;
  tagLMAP_CHR_WORK *v26;
  sdfVector4_t *p_pad;
  tagLMAP_CHR_WORK *v31;
  f32 x;
  s64 v35;
  s32 v36;

  v36 = 0;
  v35 = 0;
  v4 = chrwk;
  LODWORD(v5) = chrwk->moveNo;
  v7 = zeroVector.x;
  z = zeroVector.z;
  route = chrwk->route;
  x = v7;
  *((f32 *)&v35 + 1) = z;
  if ((v5 & 0x80000000) != 0)
  {
    *(u32 *)&route->step = 0;
    route->count = 0;
    return -1;
  }
  if (route->step != 1)
  {
    if (route->step)
      return -1;
    if ((v4->flags & 0x80000000) != 0)
    {
      v4->pad = (struct sdfVector4_t)xmmword_3CFD5C0;
      route->count = 0;
      *(u32 *)&route->step = 1;
      return -1;
    }
    if (route->count)
      return -1;
    v5 = (u8)v5;
    MapDat_GetPointXY(lmap_tbl_route[v5]->pointNo[0], &x, (f32 *)&v35 + 1);
    v21 = x;
    v22 = HIDWORD(v35);
    p_x = &vf00.x;
    p_x[4] = v21;
    p_x[5] = 0.0;
    *((u32 *)p_x + 6) = v22;
    p_x[7] = 1.0;
    pos = chrwk->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    v26 = chrwk;
    p_pad = &v26->pad;
    result = -1;
    *p_pad = vct_A;
    v31 = chrwk;
    v31->length = LMAP_CHR_ROUTE_MOVE_LENGTH;
    ++v31->route->count;
    return result;
  }
  updated = _Chr_UpdatePadRoute(chrwk);
  v12 = updated;
  if ((updated & 0x80) == 0)
  {
    v13 = chrwk;
    v14 = chrwk->route;
    *(u32 *)&v14->step = 0;
    v14->count = 0;
    v13->moveNo = -1;
    return v12;
  }
  result = -1;
  if (v12 == -2)
  {
    v17 = chrwk;
    v18 = chrwk->route;
    *(u32 *)&v18->step = 0;
    v18->count = 0;
    v17->moveNo = -1;
    return -2;
  }
  return result;
}

// 0x1cd38a0
static s8 Chr_UpdatePadTrain(tagLMAP_CHR_WORK *chrwk) {
  tagLMAP_CHR_WORK *v4;
  s64 v5;
  tagLMAP_CHR_UTIL_WORK *route;
  s8 result;
  s32 count;
  s16 v11;
  s16 PointStation;
  s32 v14;
  s32 v15;
  u32 *p_x;
  struct sdfVector4_t pos;
  tagLMAP_CHR_WORK *v19;
  f32 *v21;
  f32 z;
  f32 v23;
  f32 y;
  tagLMAP_CHR_WORK *v26;
  sdfVector4_t *p_pad;
  tagLMP_MODEL_WK *v29;
  tagLMAP_CHR_UTIL_WORK *v30;
  s32 v31;
  tagLMAP_CHR_WORK *v32;
  s8 updated;
  tagLMAP_CHR_UTIL_WORK *v36;
  s32 v37;
  tagLMP_MODEL_WK *v38;
  tagLMAP_CHR_WORK *v39;
  s16 basePointNo;
  s16 v43;
  s16 v46;
  s16 PointTableNo;
  tagLMAP_CHR_WORK *v48;
  s32 v49;
  s16 v50;
  tagLMAP_CHR_WORK *v52;
  tagLMAP_CHR_WORK *v55;
  tagLMAP_CHR_UTIL_WORK *v57;
  tagLMP_MODEL_WK *vehicle;
  tagLMAP_CHR_WORK *v59;
  s64 moveNo;
  s32 v63;
  s64 v64;
  s64 v66;
  tagLMAP_CHR_WORK *v67;
  sdfVector4_t *v69;
  tagLMAP_CHR_WORK *v70;
  u8 Chr_UpdatePadTrain_ret_local;
  tagLMAP_CHR_UTIL_WORK *v72;
  tagLMAP_CHR_WORK *v73;
  tagLMAP_CHR_UTIL_WORK *scale;
  tagLMP_MODEL_WK *p_vehicle;
  tagLMP_MODEL_WK *v77;
  dds3Basic_t *unit;
  tagLMP_MODEL_WK *v80;
  tagLMAP_CHR_WORK *v81;
  tagLMP_MODEL_WK *v82;
  s16 v83;
  s16 v85;
  s16 v86;
  tagLMAP_CHR_WORK *v88;
  s32 v89;
  tagLMAP_CHR_WORK *v90;
  tagLMAP_CHR_WORK *v91;
  tagLMAP_CHR_WORK *v94;
  tagLMAP_CHR_UTIL_WORK *v95;
  tagLMAP_CHR_WORK *v99;
  tagLMAP_CHR_UTIL_WORK *v100;
  tagLMAP_CHR_WORK *v102;
  long f64 v103;
  f32 v104;
  s64 x;
  s64 v109;

  v4 = chrwk;
  LODWORD(v5) = chrwk->moveNo;
  x = 0;
  v109 = 0x3F80000000000000LL;
  route = v4->route;
  if ((v5 & 0x80000000) != 0)
  {
    *(u32 *)&route->step = 0;
    route->count = 0;
    return -1;
  }
  result = -1;
  switch (route->step)
  {
    case 0:
      if ((v4->flags & 0x80000000) != 0)
      {
        v4->length = 0.0;
        v4->pad = (struct sdfVector4_t)xmmword_3CFD5C0;
        count = (u16)route->count;
        if (!count)
          goto LABEL_96;
      }
      else
      {
        count = (u16)route->count;
        if (!count)
        {
          v5 = (u8)v5;
          v11 = lmap_tbl_route[v5]->pointNo[0];
          PointStation = MapDat_GetPointStation(v11);
          if (PointStation >= 0)
            v11 = PointStation;
          MapDat_GetPointXY(v11, &x, &v109);
          HIDWORD(x) = 0;
          HIDWORD(v109) = 1065353216;
          v14 = x;
          v15 = v109;
          p_x = &vf00.x;
          p_x[4] = v14;
          p_x[5] = 0;
          p_x[6] = v15;
          p_x[7] = 1065353216;
          pos = chrwk->pos;
          vct_B = pos;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v19 = chrwk;
          v21 = &vf00.x;
          z = v21[6];
          v23 = v21[4];
          y = v21[5];
          v19->length = LMAP_PAD_ANALOG_MASK
                             + (f32)(sqrtf((f32)((f32)(v23 * v23) + (f32)(y * y)) + (f32)(z * z)) / 30.0);
          sub_1949110(0);
          v26 = chrwk;
          p_pad = &v26->pad;
          *p_pad = vct_A;
LABEL_96:
          v73 = chrwk;
          scale = chrwk->scale;
          if (scale->step)
          {
            goto LABEL_99;
          }
          v73->scl = v73->sclDef;
          scale->fields = (tagLMAP_CHR_UTIL_WORK)0x1E000000010001LL;
LABEL_99:
          p_vehicle = &v73->vehicle;
          MdlCreate(p_vehicle, 2u, 5, LMAP_CHR_MODEL_TRAIN_SCALE);
          v77 = p_vehicle;
          if (p_vehicle)
          {
            v77->ofsY = 0.0;
            v77->ofsLength = LMAP_CHR_MODEL_TRAIN_OFSLENGTH;
          }
          goto LABEL_102;
        }
      }
      if ((s16)count < 30)
      {
LABEL_102:
        v30 = chrwk->route;
        goto LABEL_103;
      }
      basePointNo = v4->basePointNo;
      v43 = MapDat_GetPointStation(basePointNo);
      if ((v43 & 0x8000) == 0)
      {
        v46 = v43;
        PointTableNo = MapDat_GetPointTableNo(v46);
        v48 = chrwk;
        v49 = PointTableNo;
        v50 = PointTableNo;
        v48->pos.x = (f32)dmLMAP_POINT_X(PointTableNo);
        v52 = chrwk;
        chrwk->pos.y = 0.0;
        v52->pos.z = (f32)dmLMAP_POINT_Y(v49);
        Chr_SetBasePointNo(chrwk, v50);
      }
      v55 = chrwk;
      v57 = chrwk->route;
      *(u32 *)&v57->step = 2;
      v57->count = 0;
      vehicle = v55->vehicle;
      if (vehicle)
        vehicle->flags |= 8u;
      v59 = chrwk;
      v59->bDirectAngle = 1;
      moveNo = v59->moveNo;
      v63 = lmap_tbl_route[moveNo]->pointNo[0];
      v64 = chrwk->moveNo;
      ChrRouteCalcPadParam(v63, lmap_tbl_route[v64]->pointNo[1]);
      v67 = chrwk;
      v69 = &v67->pad;
      *v69 = vct_A;
      v70 = chrwk;
      v70->line = vct_A;
      v102 = chrwk;
      v103 = sub_18E6660(0, v66);
      result = -1;
      v104 = (f32)(*(f32 *)&v103 * 57.29578) + 90.0;
      if (v104 > 180.0)
        v104 = v104 + -360.0;
      if (v104 < -180.0)
        v104 = v104 + 360.0;
      v102->degree = v104;
      return result;
    case 2:
      if (!route->count)
      {
        v29 = v4->vehicle;
        if (v29)
          v29->flags |= 4u;
      }
      v30 = chrwk->route;
      v31 = (u16)v30->count;
      if (v31 != 10)
        goto LABEL_104;
      p2sdPlaySE_Vol(6946816, 127);
      v32 = chrwk;
      chrwk->bDirectAngle = 0;
      goto LABEL_48;
    case 3:
      p2sdOverlap(6946816, 0x7Fu, 4400);
      updated = _Chr_UpdatePadRoute(chrwk);
      Chr_UpdatePadTrain_ret = updated;
      if ((updated & 0x80) == 0)
      {
        p2sdSndStop(6946816);
        v32 = chrwk;
LABEL_48:
        v36 = v32->route;
        v36->count = 0;
        ++v36->step;
        return -1;
      }
      Chr_UpdatePadTrain_ret_local = updated;
      result = -1;
      if (Chr_UpdatePadTrain_ret_local != 254)
        return result;
      v99 = chrwk;
      v100 = chrwk->route;
      *(u32 *)&v100->step = 0;
      v100->count = 0;
      v99->moveNo = -1;
      return -2;
    case 4:
      v37 = (u16)route->count;
      if (v37 != 10)
      {
        route->count = v37 + 1;
        return result;
      }
      v38 = v4->vehicle;
      if (v38)
      {
        unit = v38->unit;
        if (unit)
        {
          dds3UnitObjectBasicDelete(unit);
          v80 = v4->vehicle;
          v80->unit = 0;
          v38 = v4->vehicle;
        }
        v38->flags &= ~2u;
      }
      v81 = chrwk;
      v82 = chrwk->vehicle;
      if (v82)
        v82->flags &= 0xFFFFFFF3;
      v83 = MapDat_GetPointStation(v81->basePointNo);
      if (v83 < 0)
      {
        v88 = chrwk;
      }
      else
      {
        v85 = v83;
        v86 = 0;
        while ((dmLMAP_POINT_NO(v86) & 0x8000) == 0)
        {
          if (dmLMAP_POINT_NO(v86) == v85)
            goto LABEL_137;
          ++v86;
        }
        v86 = -1;
LABEL_137:
        v89 = v86;
        v90 = chrwk;
        v90->pos.x = (f32)dmLMAP_POINT_X(v89);
        v91 = chrwk;
        chrwk->pos.y = 0.0;
        v91->pos.z = (f32)dmLMAP_POINT_Y(v89);
        v94 = chrwk;
        v94->basePointNo = dmLMAP_POINT_NO(v89);
        v88 = chrwk;
        *(u32 *)&v88->nextPointNo = -1;
        v88->flags = v88->flags & 0x7FFFFFF | 0xA0000000;
      }
      v95 = v88->route;
      v95->step += 2;
      v95->count = 0;
      lmapStationStopDestCheck();
      lmapSetDestCheck(-1);
      lmapDrawNextDest();
      mapIfDestUpdateDisplay();
      return -1;
    case 5:
      if (!v4->unit)
      {
        ChrSetModel(chrwk, 2u, 1);
        v39 = chrwk;
        v39->scl = 0.0;
        ++v39->route->step;
        return -1;
      }
      return result;
    case 6:
      if (route->count)
      {
        if (route->count >= 30)
        {
          *(u32 *)&route->step = 0;
          route->count = 0;
          v4->moveNo = -1;
          return Chr_UpdatePadTrain_ret;
        }
      }
      else
      {
        v4 = chrwk;
        v72 = v4->scale;
        if (!v72->step)
        {
          v4->scl = 0.0;
          v72->fields = (tagLMAP_CHR_UTIL_WORK)0x1E000000000001LL;
        }
      }
      v30 = v4->route;
LABEL_103:
      LOWORD(v31) = v30->count;
LABEL_104:
      v30->count = v31 + 1;
      return -1;
    default:
      return result;
  }
}

// 0x1cd47d0
static s16 _Chr_GetExLineDat(s16 checkPointNo, s16 checkType) {
  s32 i;
  s16 v8;
  s16 v10;
  s16 result;
  s16 v13;

  for (i = 0; ; ++i)
  {
    if (dmLMAP_LINE_NO(i) < 0)
    {
      result = 0;
      v8 = -1;
      checkPointNo = -1;
      goto LABEL_24;
    }
    if (!dmLMAP_LINE_TYPE(i))
      continue;
    v8 = dmLMAP_LINE_POINT_A(i);
    v10 = dmLMAP_LINE_POINT_B(i);
    if (v8 == checkPointNo)
      break;
    if (v10 == checkPointNo)
    {
      goto LABEL_23;
    }
  }
  v8 = v10;
LABEL_23:
  result = dmLMAP_LINE_TYPE(i);
LABEL_24:
  if (checkType == 1)
    v13 = checkPointNo;
  else
    v13 = v8;
  if (checkType)
    return v13;
  return result;
}

// 0x1cd4920
static s16 Chr_GetExLineDat(tagLMAP_CHR_WORK *chrwk, s16 checkType) {
  u32 flags;
  s16 basePointNo;
  s32 v7;

  flags = chrwk->flags;
  if ((flags & 0x60000000) == 0)
  {
    if (checkType)
      LOWORD(v7) = -1;
    else
      LOWORD(v7) = 0;
    return v7;
  }
  if ((flags & 0x80000000) != 0)
  {
    basePointNo = chrwk->basePointNo;
    goto LABEL_21;
  }
  if ((flags & 0x20000000) != 0)
  {
    basePointNo = chrwk->basePointNo;
    if ((flags & 0x40000000) == 0)
      goto LABEL_21;
    v7 = _Chr_GetExLineDat(basePointNo, checkType);
    if (checkType)
    {
      if ((v7 & 0x80000000) == 0)
        return v7;
    }
    else if (v7 >= 1)
    {
      return v7;
    }
LABEL_20:
    basePointNo = chrwk->nextPointNo;
    goto LABEL_21;
  }
  if ((flags & 0x40000000) != 0)
    goto LABEL_20;
  basePointNo = -1;
LABEL_21:
  LOWORD(v7) = _Chr_GetExLineDat(basePointNo, checkType);
  return v7;
}

// 0x1ccb0f0
static s16 Chr_GetExLineType(tagLMAP_CHR_WORK *chrwk) {
  tagLMAP_CHR_WORK *v5;

  v5 = chrwk;
  return Chr_GetExLineDat(v5, 0);
}

// 0x1cd4a30
static s16 Chr_GetExLineBase(tagLMAP_CHR_WORK *chrwk) {
  tagLMAP_CHR_WORK *v5;

  v5 = chrwk;
  return Chr_GetExLineDat(v5, 1);
}

// 0x1cd4ac0
static s16 Chr_GetExLineNext(tagLMAP_CHR_WORK *chrwk) {
  tagLMAP_CHR_WORK *v5;

  v5 = chrwk;
  return Chr_GetExLineDat(v5, 2);
}

// 0x1cd4b50
static bool Chr_UpdatePosTrain(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk) {
  tagLMAP_CHR_UTIL_WORK *autom;
  s32 step;
  bool result;
  s8 updated;

  autom = chrwk->autom;
  step = autom->step;
  if (step == 2)
  {
    autom->step = 0;
    return 1;
  }
  if (step != 1)
  {
    if (autom->step)
      return 0;
    if ((chrwk->moveNo & 0x80000000) == 0)
    {
      autom->count = 0;
      autom->step = 1;
      return 0;
    }
    return 1;
  }
  updated = Chr_UpdatePadTrain(chrwk);
  Chr_UpdatePosition(chrwk, lockwk);
  result = 0;
  if ((updated & 0x80) == 0)
    ++chrwk->autom->step;
  return result;
}

// 0x1cd4c60
static bool Chr_UpdatePosShip(tagLMAP_CHR_WORK *chrwk) {
  tagLMAP_CHR_UTIL_WORK *ship;
  bool result;
  tagLMAP_CHR_UTIL_WORK *v8;
  s16 *p_count;
  s16 count;
  s32 portTableNo;
  f32 v12;
  f32 v14;
  long f64 v16;
  s32 v19;
  s32 v21;
  tagLMP_MODEL_WK *v23;
  s32 v24;
  f32 v27;
  tagM_LMAP_WORK *v28;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v35;
  s32 v37;
  tagLMAP_CHR_UTIL_WORK *v39;
  s16 v40;
  tagLMP_MODEL_WK *v43;
  tagLMAP_CHR_UTIL_WORK *v44;
  tagLMP_MODEL_WK *v51;
  tagLMP_MODEL_WK *v52;
  tagLMP_MODEL_WK *v55;
  long f64 v56;
  f32 v57;
  s32 v60;
  s16 step;
  tagLMP_MODEL_WK *vehicle;
  s32 v63;
  s32 v64;
  s32 v66;
  f32 v67;
  f32 v69;
  f32 x;
  f32 z;
  f32 *p_x;
  f32 *v75;
  f32 v76;
  f32 v77;
  f32 y;
  tagLMAP_CHR_UTIL_WORK *scale;
  tagLMP_MODEL_WK *p_vehicle;
  tagLMP_MODEL_WK *v84;
  char *v86;
  Il2CppObject *v87;
  tagLMAP_CHR_UTIL_WORK *v88;
  s32 v90;
  tagLMAP_CHR_UTIL_WORK *v92;
  s32 TaraSE_RandNo;
  char **v100;
  s32 v102;

  ship = chrwk->ship;
  result = 0;
  v102 = 0;
  switch (ship->step)
  {
    case 0:
      MenuFlag = 0;
      if ((chrwk->flags & 0x80000000) != 0)
      {
        v8 = chrwk->ship;
        *(u64 *)&chrwk->pad.x = 0;
        *(u64 *)&chrwk->pad.z = 0;
        p_count = &v8->count;
        count = v8->count;
        if (!count)
          goto LABEL_141;
      }
      else
      {
        v8 = chrwk->ship;
        p_count = &v8->count;
        count = v8->count;
        if (!count)
        {
          portTableNo = chrwk->portTableNo;
          v12 = dmLMAP_POINT_X(portTableNo);
          v14 = dmLMAP_POINT_Y(chrwk->portTableNo);
          sub_1B332C0(0, v12, 0.0, v14, 1.0);
          sub_1B33360(0, chrwk->pos.x, chrwk->pos.y, chrwk->pos.z, chrwk->pos.w);
          sub_1B33400(0);
          chrwk->length = (f32)(LMAP_PAD_ANALOG_MASK * (loc_1CDE880)(0)) * 0.0625;
          sub_1949110(0);
          sub_1B335A0(&chrwk->pad, 0, v16);
LABEL_141:
          p_vehicle = &chrwk->vehicle;
          MdlCreate(p_vehicle, 2u, 10, LMAP_CHR_MODEL_SHIP_SCALE);
          v84 = p_vehicle;
          if (p_vehicle)
          {
            v84->ofsLength = 0.0;
            v84->ofsY = LMAP_CHR_MODEL_SHIP_OFSY;
          }
          goto LABEL_146;
        }
      }
      if (count < 16)
        goto LABEL_146;
      step = v8->step;
      v8->mode = 0;
      *p_count = 0;
      v8->step = step + 1;
      vehicle = chrwk->vehicle;
      if (!vehicle)
        return 0;
      vehicle->flags |= 8u;
      return 0;
    case 1:
      ship = chrwk->ship;
      MenuFlag = 0;
      v19 = (u16)ship->count;
      lmapwk->guide_onoff = 0;
      if (v19 == 2)
      {
        v102 = sndSeStatus();
        v86 = ToString((s32)&v102, 0);
        v87 = Concat_54766928("笛SE再生中:サウンドステータス:", v86, 0);
        Log(v87);
        v88 = chrwk->ship;
        v88->count = 0;
        v88->step = 2;
        if (evtBitCheck(176) && !evtBitCheck(185))
        {
          chrwk->ship->step = 12;
          return 0;
        }
        else
        {
          ChrCalcDegree(chrwk, 1);
          return 0;
        }
      }
      if (v19 != 1)
      {
        result = 0;
        if (v19)
          return result;
        fclStart1(4, 0);
        ButtonGuideDispOff();
        sndSeLoadId(78);
        LOWORD(v21) = 1;
        result = 0;
        *(u16 *)&Chr_UpdatePosShip_chk_msg = 0;
        ship = chrwk->ship;
        goto LABEL_225;
      }
      if (!Chr_UpdatePosShip_chk_msg)
      {
        v90 = Update();
        if (!v90)
        {
          Chr_UpdatePosShip_chk_msg = 1;
        }
      }
      if (Chr_UpdatePosShip_chk_se)
      {
        goto LABEL_167;
      }
      if (sndSeStatus() != 2)
      {
LABEL_167:
        if (!Chr_UpdatePosShip_chk_msg)
          return 0;
        goto LABEL_212;
      }
      sndSePlay(0);
      Chr_UpdatePosShip_chk_se = 1;
      goto LABEL_167;
LABEL_212:
      if (Chr_UpdatePosShip_chk_se)
      {
        ship = chrwk->ship;
        LOWORD(v21) = 2;
        result = 0;
        goto LABEL_225;
      }
      return 0;
    case 2:
      ship = chrwk->ship;
      MenuFlag = 0;
      if (!ship->count)
      {
        sndSeLoadId(42);
        sndSePlay(0);
        v23 = chrwk->vehicle;
        if (v23)
          v23->flags |= 4u;
      }
      v24 = chrwk->ship->count;
      if (v24 <= 15)
      {
        chrwk->pos.y = chrwk->pos.y + -0.5;
        goto LABEL_223;
      }
      if (v24 == 16)
      {
        fclStart1(6, 0);
        ButtonGuideDispOff();
        goto LABEL_223;
      }
      if (Update())
        goto LABEL_223;
      v92 = chrwk->ship;
      *(u32 *)&v92->mode = 1;
      ++v92->step;
      chrwk->flags &= ~0x80000000;
      lmapwk->TaraSE_time = 60;
      lmapwk->TaraSE_Flag = 1;
      while (1)
      {
        lmapwk->TaraSE_RandNo = sub_1905740(3, 0);
        TaraSE_RandNo = (u16)lmapwk->TaraSE_RandNo;
        if (TaraSE_RandNo != (u16)lmapwk->TaraSE_RandNoOld)
          break;
      }
      TaraSE_RandNo = (u16)lmapwk->TaraSE_RandNo;
      if (!TaraSE_RandNo)
      {
        v100 = &"PVB07B_05A_000";
LABEL_219:
        sndVoicePlayFile(*v100, 0);
        goto LABEL_220;
      }
      TaraSE_RandNo = (u16)lmapwk->TaraSE_RandNo;
      if (TaraSE_RandNo == 1)
      {
        v100 = &"PVB07B_18C_000";
        goto LABEL_219;
      }
      if (TaraSE_RandNo == 2)
      {
        v100 = &"PVB07B_19B_000";
        goto LABEL_219;
      }
LABEL_220:
      lmapwk->TaraSE_RandNoOld = lmapwk->TaraSE_RandNo;
LABEL_223:
      ship = chrwk->ship;
      result = 0;
      v21 = (s16)(ship->count + 1);
      if (v21 >= 32)
        LOWORD(v21) = 32;
LABEL_225:
      ship->count = v21;
      return result;
    case 3:
      v27 = LMAP_PAD_ANALOG_MASK;
      v28 = lmapwk;
      *(u16 *)&MenuFlag = 1;
      chrwk->moveType = 3;
      v28->guide_onoff = 1;
      Util_GetPadAnalog(&chrwk->pad, &chrwk->length, v27);
      ship = chrwk->ship;
      if (ship->mode != 2)
        return 0;
      result = 0;
      ++ship->step;
LABEL_91:
      ship->count = 0;
      return result;
    case 4:
      ship = chrwk->ship;
      MenuFlag = 0;
      v21 = ship->count;
      if (ship->count)
      {
        if (v21 >= 16)
        {
          v30 = chrwk->portTableNo;
          v31 = dmLMAP_POINT_X(v30);
          v32 = chrwk->portTableNo;
          chrwk->pos.x = (f32)v31;
          v35 = dmLMAP_POINT_Y(v32);
          v37 = chrwk->portTableNo;
          *(u64 *)&chrwk->pad.x = 0;
          *(u64 *)&chrwk->pad.z = 0;
          chrwk->pos.z = (f32)v35;
          chrwk->basePointNo = dmLMAP_POINT_NO(v37);
          *(u32 *)&chrwk->nextPointNo = -1;
          v39 = chrwk->ship;
          chrwk->flags = chrwk->flags & 0x7FFFFFF | 0xA0000000;
          v40 = v39->step;
          *(u32 *)&v39->mode = 0;
          v39->step = v40 + 1;
          TaraCtrlFlag = 0;
          p2sdSndStop(6946817);
          return 0;
        }
LABEL_133:
        result = 0;
        goto LABEL_147;
      }
      v63 = chrwk->portTableNo;
      LOWORD(v64) = dmLMAP_POINT_X(v63);
      LOWORD(v66) = dmLMAP_POINT_Y(chrwk->portTableNo);
      v64 = (s16)v64;
      v66 = (s16)v66;
      v67 = v64;
      v69 = v66;
      vct_A.x = v67;
      vct_A.y = 0.0;
      vct_A.z = v69;
      vct_A.w = 1.0;
      x = chrwk->pos.x;
      z = chrwk->pos.z;
      p_x = &vf00.x;
      p_x[8] = x;
      p_x[9] = 0.0;
      p_x[10] = z;
      p_x[11] = 1.0;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v75 = &vf00.x;
      v76 = v75[6];
      v77 = v75[4];
      y = v75[5];
      chrwk->length = (f32)(LMAP_PAD_ANALOG_MASK_SHIP * sqrtf((f32)((f32)(v77 * v77) + (f32)(y * y)) + (f32)(v76 * v76)))
                           * 0.0625;
      sub_1949110(0);
      ship = chrwk->ship;
      chrwk->pad = vct_A;
      LOWORD(v21) = ship->count;
      goto LABEL_133;
    case 5:
      ship = chrwk->ship;
      MenuFlag = 0;
      v21 = ship->count;
      if (v21 >= 16)
      {
        v43 = &chrwk->vehicle;
        MdlDelete(&chrwk->vehicle);
        if (v43)
          v43->flags &= 0xFFFFFFF3;
        v44 = chrwk->ship;
        result = 1;
        chrwk->moveType = 1;
        *(u32 *)&v44->step = 0;
        v44->count = 0;
        *(u16 *)&MenuFlag = 1;
        if (lmapwk->TaraSE_Flag)
        {
          sndSeStop_name("mapse_0a", 0);
          lmapwk->TaraSE_Flag = 0;
          return 1;
        }
        return result;
      }
      result = 0;
      chrwk->pos.y = chrwk->pos.y + 0.5;
LABEL_147:
      LOWORD(v21) = v21 + 1;
      goto LABEL_225;
    case 6:
      ship = chrwk->ship;
      MenuFlag = 0;
      if (ship->count)
      {
        if (ship->count >= 25)
          ++ship->step;
      }
      else
      {
        scale = chrwk->scale;
        if (!scale->step)
        {
          chrwk->scl = 0.0;
          scale->fields = (tagLMAP_CHR_UTIL_WORK)0x19000000000001LL;
        }
      }
LABEL_146:
      ship = chrwk->ship;
      result = 0;
      LOWORD(v21) = ship->count;
      goto LABEL_147;
    case 7:
      ship = chrwk->ship;
      result = 1;
      *(u16 *)&MenuFlag = 1;
      chrwk->moveType = 1;
      *(u32 *)&ship->step = 0;
      goto LABEL_91;
    case 0xA:
      MenuFlag = 0;
      v51 = &chrwk->vehicle;
      MdlCreate(v51, 2u, 10, LMAP_CHR_MODEL_SHIP_SCALE);
      v52 = v51;
      if (v51)
      {
        v52->ofsLength = 0.0;
        v52->ofsY = LMAP_CHR_MODEL_SHIP_OFSY;
      }
      chrwk->ship->step = 11;
      return 0;
    case 0xB:
      MenuFlag = 0;
      v55 = chrwk->vehicle;
      if (v55)
        v55->flags |= 8u;
      v56 = sub_18E6660(0);
      result = 0;
      v57 = (f32)(*(f32 *)&v56 * 57.29578) + 90.0;
      if (v57 > 180.0)
        v57 = v57 + -360.0;
      ship = chrwk->ship;
      if (v57 < -180.0)
        v57 = v57 + 360.0;
      chrwk->degree = v57;
      *(u32 *)&ship->step = 2;
      goto LABEL_91;
    case 0xC:
      MenuFlag = 0;
      fclStart1(5, 0);
      ButtonGuideDispOff();
      chrwk->ship->step = 13;
      return 0;
    case 0xD:
      MenuFlag = 0;
      v60 = Update();
      result = 0;
      if (!v60)
      {
        ButtonGuideDispSet("LMAP01", 0, 90);
        chrwk->ship->step = 7;
        return 0;
      }
      return result;
    default:
      return result;
  }
}

// 0x1cd64d0
static bool Chr_UpdatePosAuto(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk) {
  tagLMAP_CHR_WORK *v5;
  s8 moveId_save;

  v5 = chrwk;
  if (chrwk->exLineType != 1)
    goto LABEL_8;
  goto LABEL_9000;
  if (chrwk->exLineType != 1)
  {
LABEL_8:
    moveId_save = v5->moveId_save;
    v5->exLineType = 0;
    v5->moveId = moveId_save;
    v5->moveNo = -1;
    return 1;
  }
LABEL_9000:
  if (Chr_UpdatePosTrain(chrwk, lockwk))
  {
    v5 = chrwk;
    goto LABEL_8;
  }
  return 0;
}

// 0x1cd65b0
static void Kaya_UpdatePosAuto(tagLMAP_CHR_WORK *chrwk) {
  s32 lineTableNo;
  tagLMAP_CHR_WORK *v6;
  s32 v7;
  f32 v8;
  f32 z;
  tagLMAP_CHR_WORK *v10;
  f32 v11;
  f32 v12;
  float32x4_t *v13;
  f32 v15;
  f32 v16;
  bool v17;
  f32 v18;
  tagLMAP_CHR_WORK *v19;
  float32x4_t v20;
  tagLMAP_CHR_WORK *v21;
  float32x4_t v23;
  f32 v24;
  tagLMAP_CHR_WORK *v25;
  f32 v26;
  f32 v27;
  f32 v28;
  float32x2_t v29;
  float32x2_t v30;
  f32 v31;
  f32 v32;
  f32 v33;
  u32 v34;
  s64 x;
  s64 v36;

  lineTableNo = (u16)(chrwk)->lineTableNo;
  v6 = lmapwk->chrwk;
  v7 = (u16)v6->lineTableNo;
  if (lineTableNo == v7 || chrwk->lineTableNo == -1)
    goto LABEL_9;
  if (v7 == 0xFFFF)
  {
LABEL_9:
    v8 = chrwk->pos.x;
    z = chrwk->pos.z;
    v10 = lmapwk->chrwk;
    v11 = v10->pos.x;
    v12 = v10->pos.z;
    v13 = chrwk;
    v15 = sqrtf((f32)((f32)(v11 - v8) * (f32)(v11 - v8)) + (f32)((f32)(v12 - z) * (f32)(v12 - z)));
    v16 = v15 * 6.4;
    v17 = v15 <= 13.0;
    v18 = 0.0;
    if (!v17)
      v18 = v16;
    v13[7].n128_f32[1] = v18;
    v19 = v13;
    v20 = vsubq_f32((float32x4_t)lmapwk->chrwk->pos, (float32x4_t)v19->pos);
    goto LABEL_19;
  }
  x = 0;
  v36 = 0;
  v6 = lmapwk->chrwk;
  MapDat_GetPointXY(v6->basePointNo, &x, &v36);
  v23.n128_u32[0] = x;
  LODWORD(v24) = v36;
  v25 = lmapwk->chrwk;
  v26 = v25->pos.x;
  v27 = v25->pos.z;
  v33 = *(f32 *)&v36;
  v34 = x;
  v24 = v33;
  v23.n128_u32[0] = v34;
  v13 = chrwk;
  v23.n128_u32[1] = HIDWORD(x);
  v28 = v27 - v24;
  v23.n128_u64[1] = __PAIR64__(HIDWORD(v36), LODWORD(v24));
  v20 = vsubq_f32(v23, (float32x4_t)(chrwk)->pos);
  v23.n128_u32[1] = vdup_lane_s32((int32x2_t)v20.n128_u64[0], 0).n64_u32[1];
  v23.n128_f32[0] = v26 - v23.n128_f32[0];
  v29.n64_u64[0] = vmul_f32((float32x2_t)v23.n128_u64[0], (float32x2_t)v23.n128_u64[0]).n64_u64[0];
  v30.n64_u32[1] = vdup_laneq_s32(v20, 2).n64_u32[1];
  v30.n64_f32[0] = v28;
  v29.n64_f32[0] = vaddv_f32(vsqrt_f32(vadd_f32(v29, vmul_f32(v30, v30))));
  v31 = v29.n64_f32[0] * 6.4;
  v17 = v29.n64_f32[0] <= 13.0;
  v32 = 0.0;
  if (!v17)
    v32 = v31;
  v13[7].n128_f32[1] = v32;
LABEL_19:
  v13[2] = v20;
  v21 = chrwk;
  v21->pad.y = 0.0;
  v21->pad.w = 0.0;
}

// 0x1cc2e80
static s8 Chr_UpdateMove(tagLMAP_CHR_WORK *chrwk, tagLMAP_LOCK_WORK *lockwk) {
  tagLMAP_CHR_WORK *v5;
  u32 flags;
  s8 result;
  s8 v8;
  s32 v9;
  sdfVector4_t *p_pad;
  f32 *p_length;
  sdfVector4_t *v13;
  f32 *v14;
  tagLMAP_CHR_WORK *v16;
  s32 moveCount;
  bool v18;
  s32 v19;
  s32 portTableNo;
  char v22;
  tagLMAP_CHR_WORK *v23;
  s32 v24;
  tagLMAP_CHR_WORK *v26;
  s32 charaId;
  tagLMAP_CHR_WORK *v28;
  tagLMAP_CHR_WORK *v30;
  s8 moveType;
  s32 v32;
  s8 updated;
  tagLMAP_CHR_WORK *v35;
  s8 v36;
  s8 moveId_save;
  s32 v38;
  tagLMAP_CHR_WORK *v39;
  tagLMAP_LOCK_WORK *v40;
  tagLMAP_CHR_WORK *v41;
  tagLMAP_CHR_UTIL_WORK *scale;

  v5 = chrwk;
  if (!chrwk)
    return -1;
  flags = v5->flags;
  if ((flags & 1) == 0)
    return -1;
  v8 = -3;
  v9 = 1;
  result = 0;
  switch (v5->moveId)
  {
    case 1:
      v5->moveType = 1;
      p_pad = &v5->pad;
      p_length = &v5->length;
      if (Util_GetPadAnalog(p_pad, p_length, LMAP_PAD_ANALOG_MASK))
        goto LABEL_15;
      goto LABEL_70;
    case 2:
      v5->moveType = 2;
      v13 = &v5->pad;
      v14 = &v5->length;
      if (!Util_GetPadAnalog(v13, v14, LMAP_PAD_ANALOG_MASK))
        goto LABEL_70;
LABEL_15:
      v8 = -3;
      v9 = 1;
      v16 = chrwk;
      moveCount = chrwk->moveCount;
      v18 = __OFSUB__(moveCount, 1);
      v19 = moveCount - 1;
      if (v19 < 0 == v18)
        goto LABEL_52;
      goto LABEL_53;
    case 3:
      if (!Chr_UpdatePosShip(v5))
        goto LABEL_50;
      portTableNo = chrwk->portTableNo;
      v22 = dmLMAP_POINT_FLAG(portTableNo);
      v23 = chrwk;
      if ((v22 & 1) != 0)
      {
        v9 = 0;
        v23->moveId = 5;
        v8 = 3;
        v16 = chrwk;
        v38 = chrwk->moveCount;
        v18 = __OFSUB__(v38, 1);
        v19 = v38 - 1;
        if (v19 < 0 == v18)
LABEL_52:
          v16->moveCount = v19;
      }
      else
      {
        v23->moveId = 1;
LABEL_50:
        v8 = -3;
LABEL_51:
        v16 = chrwk;
        v32 = chrwk->moveCount;
        v18 = __OFSUB__(v32, 1);
        v19 = v32 - 1;
        if (v19 < 0 == v18)
          goto LABEL_52;
      }
LABEL_53:
      updated = Chr_UpdatePosition(chrwk, lockwk);
      v35 = chrwk;
      v36 = updated;
      if (v35->ship->mode <= 1)
      {
        v35->portTableNo = Chr_GetNearPortTableNo(v35);
      }
      if (v9)
        return v36;
      else
        return v8;
    case 4:
      if (v5->moveCount)
        goto LABEL_51;
      v5->moveType = 1;
      Chr_UpdatePadRandom(chrwk);
      v16 = chrwk;
      v24 = chrwk->moveCount;
      v18 = __OFSUB__(v24, 1);
      v19 = v24 - 1;
      if (v19 < 0 == v18)
        goto LABEL_52;
      goto LABEL_53;
    case 5:
      return result;
    case 7:
      v5->flags = flags & 0xFFFFFFDF;
      v5->moveType = 1;
      result = Chr_UpdatePadRoute(chrwk);
      if (result < 0)
        goto LABEL_50;
      switch (result)
      {
        case 0:
          v26 = chrwk;
          charaId = (u8)(chrwk)->charaId;
          if (charaId != 1)
            LOBYTE(charaId) = v26->moveId_save;
          v26->moveId = charaId;
          result = 0;
          break;
        case 1:
          chrwk->moveId = 5;
          result = 1;
          break;
        case 2:
          v39 = chrwk;
          v39->moveId = 5;
          v40 = lockwk;
          Lock_SetPointChr(v40, v39, 1);
          result = 2;
          break;
        case 3:
          v41 = chrwk;
          if (chrwk->charaId == 4)
          {
            v41 = chrwk;
            scale = v41->scale;
            if (!scale->step)
            {
              v41->scl = v41->sclDef;
              scale->fields = (tagLMAP_CHR_UTIL_WORK)0x19000000010001LL;
            }
          }
          v41->moveId = 5;
          result = 3;
          break;
        default:
          return result;
      }
      return result;
    case 8:
      v5->moveType = 1;
      v28 = chrwk;
      if (chrwk->exLineType != 1)
        goto LABEL_69;
      goto LABEL_65;
      if (chrwk->exLineType != 1)
      {
LABEL_69:
        moveId_save = v28->moveId_save;
        v28->exLineType = 0;
        v28->moveId = moveId_save;
        v28->moveNo = -1;
        return 1;
      }
LABEL_65:
      if (Chr_UpdatePosTrain(chrwk, lockwk))
      {
        v28 = chrwk;
        goto LABEL_69;
      }
LABEL_70:
      result = 0;
      break;
    case 9:
      v30 = lmapwk->chrwk;
      moveType = v30->moveType;
      LODWORD(v30) = (u8)v30->moveId;
      v5->moveType = moveType;
      {
        Kaya_UpdatePosAuto(chrwk);
      }
      goto LABEL_50;
    default:
      goto LABEL_51;
  }
  return result;
}

// 0x1ccdc60
static s16 Chr_GetNearPortTableNo(tagLMAP_CHR_WORK *chrwk) {
  s32 v5;
  f32 v6;
  s16 v9;
  s16 v11;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 v19;
  tagLMAP_CHR_WORK *v22;
  f32 LMAP_CHR_AREA_LENGTH_local;
  tagLMAP_CHR_WORK *v26;
  struct sdfVector4_t pos;
  s32 v28;

  pos = chrwk->pos;
  v26 = chrwk;
  v28 = -1;
  v5 = 0;
  v6 = 10000.0;
  vct_B = pos;
  while (1)
  {
    if (dmLMAP_POINT_NO(v5) < 0)
      break;
    if ((dmLMAP_POINT_FLAG(v5) & 4) != 0)
    {
      v9 = dmLMAP_POINT_X(v5);
      v11 = dmLMAP_POINT_Y(v5);
      vct_A.y = 0.0;
      vct_A.w = 1.0;
      vct_A.x = (f32)v9;
      vct_A.z = (f32)v11;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      p_x = &vf00.x;
      x = p_x[4];
      y = p_x[5];
      z = p_x[6];
      v19 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
      if (v6 > v19)
      {
        v6 = v19;
        v28 = v5;
      }
    }
    ++v5;
  }
  if (v28 < 0)
    return -1;
  v22 = v26;
  if (v26->ship->mode < 1)
  {
    LMAP_CHR_AREA_LENGTH_local = LMAP_CHR_AREA_LENGTH;
    goto LABEL_9003;
  }
  LMAP_CHR_AREA_LENGTH_local = LMAP_CHR_PORT_LENGTH;
  v22->basePointNo = dmLMAP_POINT_NO(v28);
LABEL_9003:
  if (v6 > LMAP_CHR_AREA_LENGTH_local)
    return -1;
  else
    return v28;
}

// 0x1cd6850
static void Chr_SetNearPortPos(tagLMAP_CHR_WORK *chrwk) {
  s32 v3;

  v3 = 0;
  while ((dmLMAP_POINT_NO(v3) & 0x8000) == 0)
  {
    if ((dmLMAP_POINT_FLAG(v3) & 4) != 0)
    {
      chrwk->pos.x = (f32)dmLMAP_POINT_X(v3);
      chrwk->pos.z = (f32)dmLMAP_POINT_Y(v3);
      chrwk->basePointNo = dmLMAP_POINT_NO(v3);
      *(u32 *)&chrwk->nextPointNo = -1;
      chrwk->flags = chrwk->flags & 0x67FFFFFF | 0x80000000;
      return;
    }
    ++v3;
  }
}

// 0x1cd6950
static bool Lock_SetPointNo(tagLMAP_LOCK_WORK *wk, s16 lockPointNo, bool lockFlg) {
  s16 *pointNo;
  s64 v5;
  u32 v6;
  s32 v7;
  bool result;
  s32 v9;
  s16 *m_Items;
  s32 v11;
  bool v12;
  bool v13;

  if (lockPointNo < 1)
    return 0;
  pointNo = wk->pointNo;
  v5 = 0;
  if (lockFlg)
  {
    v6 = -1;
    do
    {
      v7 = (u16)pointNo[v5];
      result = v7 == (u16)lockPointNo;
      if (v7 == (u16)lockPointNo)
        break;
      if (v7 == 0xFFFF)
        v9 = v5;
      else
        v9 = -1;
      if (v6 == -1)
        v6 = v9;
      if ((u32)v5 == 63 && (v6 & 0x80000000) == 0)
      {
        pointNo[v6] = lockPointNo;
        return 1;
      }
      ++v5;
    }
    while ((u32)v5 != 64);
  }
  else
  {
    m_Items = pointNo;
    v11 = -1;
    do
    {
      if (*(s16 *)((char *)m_Items + v5) == lockPointNo)
      {
        ++v11;
        *(s16 *)((char *)m_Items + v5) = -1;
      }
      v12 = v5 != 126 || v11 < 0;
      result = !v12;
      if (!v12)
        break;
      v13 = v5 == 126;
      v5 += 2;
    }
    while (!v13);
  }
  return result;
}

// 0x1cd6a20
static bool Lock_SetLineNo(tagLMAP_LOCK_WORK *wk, s16 lockLineNo, bool lockFlg) {
  s16 *lineNo;
  s32 v5;
  bool result;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
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

  if (lockLineNo < 1)
    return 0;
  lineNo = wk->lineNo;
  v5 = (u16)lineNo[0];
  if (!lockFlg)
  {
    if (v5 == (u16)lockLineNo)
    {
      v7 = 0;
      lineNo[0] = -1;
      if (lineNo[1] != lockLineNo)
      {
LABEL_12:
        if (lineNo[2] == lockLineNo)
        {
          ++v7;
          lineNo[2] = -1;
          if (lineNo[3] != lockLineNo)
          {
LABEL_14:
            if (lineNo[4] != lockLineNo)
              goto LABEL_15;
            goto LABEL_21;
          }
        }
        else if (lineNo[3] != lockLineNo)
        {
          goto LABEL_14;
        }
        ++v7;
        lineNo[3] = -1;
        if (lineNo[4] != lockLineNo)
        {
LABEL_15:
          if (lineNo[5] != lockLineNo)
            goto LABEL_16;
          goto LABEL_22;
        }
LABEL_21:
        ++v7;
        lineNo[4] = -1;
        if (lineNo[5] != lockLineNo)
        {
LABEL_16:
          if (lineNo[6] != lockLineNo)
            goto LABEL_17;
          goto LABEL_23;
        }
LABEL_22:
        ++v7;
        lineNo[5] = -1;
        if (lineNo[6] != lockLineNo)
        {
LABEL_17:
          if (lineNo[7] == lockLineNo)
          {
LABEL_18:
            lineNo[7] = -1;
            return 1;
          }
          return v7 >= 0;
        }
LABEL_23:
        ++v7;
        lineNo[6] = -1;
        if (lineNo[7] == lockLineNo)
          goto LABEL_18;
        return v7 >= 0;
      }
    }
    else
    {
      v7 = -1;
      if (lineNo[1] != lockLineNo)
        goto LABEL_12;
    }
    ++v7;
    lineNo[1] = -1;
    goto LABEL_12;
  }
  if (v5 == (u16)lockLineNo)
    return 1;
  v8 = (u16)lineNo[1];
  if (v8 == (u16)lockLineNo)
    return 1;
  v9 = (u16)lineNo[2];
  if (v9 == (u16)lockLineNo)
    return 1;
  v10 = (u16)lineNo[3];
  if (v10 == (u16)lockLineNo)
    return 1;
  v11 = (u16)lineNo[4];
  if (v11 == (u16)lockLineNo)
    return 1;
  v12 = (u16)lineNo[5];
  if (v12 == (u16)lockLineNo)
    return 1;
  v13 = (u16)lineNo[6];
  if (v13 == (u16)lockLineNo)
    return 1;
  v14 = (u16)lineNo[7];
  result = 1;
  if (v14 != (u16)lockLineNo)
  {
    if (v8 == 0xFFFF)
      v15 = 1;
    else
      v15 = -1;
    if (v5 == 0xFFFF)
      v16 = 0;
    else
      v16 = v15;
    if (v9 == 0xFFFF)
      v17 = 2;
    else
      v17 = -1;
    if (v16 == -1)
      v16 = v17;
    if (v10 == 0xFFFF)
      v18 = 3;
    else
      v18 = -1;
    if (v16 == -1)
      v16 = v18;
    if (v11 == 0xFFFF)
      v19 = 4;
    else
      v19 = -1;
    if (v16 == -1)
      v16 = v19;
    if (v12 == 0xFFFF)
      v20 = 5;
    else
      v20 = -1;
    if (v16 == -1)
      v16 = v20;
    if (v13 == 0xFFFF)
      v21 = 6;
    else
      v21 = -1;
    if (v16 == -1)
      v16 = v21;
    if (v14 == 0xFFFF)
      v22 = 7;
    else
      v22 = -1;
    if (v16 == -1)
      v16 = v22;
    if ((v16 & 0x80000000) == 0)
    {
      lineNo[v16] = lockLineNo;
      return result;
    }
    return 0;
  }
  return result;
}

// 0x1cc8c10
static bool Lock_SetPointChr(tagLMAP_LOCK_WORK *lockwk, tagLMAP_CHR_WORK *chrwk, bool lockFlg) {
  u32 flags;
  bool result;
  u32 v9;
  u32 v10;
  s32 basePointNo;
  s16 *pointNo;
  s64 v13;
  u32 v14;
  s32 v15;
  s32 v16;
  s16 *m_Items;
  s32 v18;
  bool v19;
  bool v20;

  flags = chrwk->flags;
  if ((flags & 1) == 0)
    return 0;
  v9 = flags & 0xFFFEFFFF;
  v10 = flags | 0x30000;
  if (!lockFlg)
    v10 = v9;
  chrwk->flags = v10;
  basePointNo = (u16)chrwk->basePointNo;
  if ((s16)basePointNo < 1)
    return 0;
  pointNo = lockwk->pointNo;
  v13 = 0;
  if (lockFlg)
  {
    v14 = -1;
    do
    {
      v15 = (u16)pointNo[v13];
      result = v15 == basePointNo;
      if (v15 == basePointNo)
        break;
      if (v15 == 0xFFFF)
        v16 = v13;
      else
        v16 = -1;
      if (v14 == -1)
        v14 = v16;
      if (v13 == 63 && (v14 & 0x80000000) == 0)
      {
        pointNo[v14] = basePointNo;
        return 1;
      }
      ++v13;
    }
    while (v13 != 64);
  }
  else
  {
    m_Items = pointNo;
    v18 = -1;
    do
    {
      if (*(u16 *)((char *)m_Items + v13) == basePointNo)
      {
        ++v18;
        *(s16 *)((char *)m_Items + v13) = -1;
      }
      v19 = v13 != 126 || v18 < 0;
      result = !v19;
      if (!v19)
        break;
      v20 = v13 == 126;
      v13 += 2;
    }
    while (!v20);
  }
  return result;
}

// 0x1cd6ca0
static void EffGrid_Release(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  dds3ProcessID_t *v6;

  workdata = proc->workdata;
  v6 = &workdata[1];
  if (!dds3ExistProcess(v6))
    return;
  dds3KillProcess(v6, 0);
}

// 0x1cd6df0
static void EffGrid_InitCB(tagLMAP_EFFGRID_CB *p_cb) {
  p_cb->cnt[0] = -1;
  p_cb->cnt[1] = -1;
  p_cb->alpha = 0;
  *(u64 *)&p_cb->vec_x = 0;
  *(u64 *)&p_cb->pos_x = 0;
}

// 0x1cd6e20
static void EffGrid_InitCBAll(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 v5;
  s64 v6;

  workdata = proc->workdata;
  v5 = 32;
  do
  {
    v6 = *(s64 *)((char *)&workdata[2].klass->_1.image + v5);
    v5 += 8;
    *(u8 *)(*(u64 *)(v6 + 16) + 32) = -1;
    *(u8 *)(*(u64 *)(v6 + 16) + 33) = -1;
    *(u8 *)(v6 + 24) = 0;
    *(u64 *)(v6 + 36) = 0;
    *(u64 *)(v6 + 28) = 0;
  }
  while (v5 != 1824);
}

// 0x1cd6f20
static void EffGrid_SetCB(tagLMAP_EFFGRID_CB *p_cb, s32 no, s8 type) {
  sdfVector4_t *v7;
  s32 v8;
  f32 *v9;
  u32 v10;
  s32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  s64 v15;
  f32 *v16;
  f32 v17;
  struct sdfVector4_t v20;
  f32 *v21;
  f32 *v22;
  struct sdfVector4_t v24;

  v7 = NewSpecific(sdfVector4_t, 2u);
  v8 = type;
  p_cb->cnt[type] = 0;
  v7[0].x = (f32)(u32)sub_1905740(544, 0) + -32.0;
  v9 = &v7[0];
  v10 = sub_1905740(480, 0);
  v11 = no + 15;
  if (no >= 0)
    v11 = no;
  v12 = (s32)((2 * v11) & 0xFFFFFFE0);
  v13 = (32 * (no - (v11 & 0x7FFFFF0)));
  v14 = (f32)v10 + -32.0;
  v7[0].y = v14;
  v15 = &v7[0].y;
  *(u64 *)(v15 + 4) = 0;
  *(u64 *)(v15 + 20) = 0;
  *(f32 *)(v15 + 12) = v13;
  *(f32 *)(v15 + 16) = v12;
  v16 = (v15 + 16);
  if (!v8)
  {
    vct_A.x = v13;
    vct_A.y = v12;
    *(u64 *)&vct_A.z = 0;
    v24 = *(sdfVector4_t *)v9;
    vct_B = v24;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v21 = (v15 + 12);
    v22 = v15;
    goto LABEL_18;
  }
  v17 = *v9;
  vct_A.x = v17;
  vct_A.y = v14;
  *(u64 *)&vct_A.z = 0;
  v20 = *(sdfVector4_t *)(v15 + 12);
  vct_B = v20;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v21 = v9;
  v9 = (v15 + 12);
  v22 = (v15 + 16);
  v16 = v15;
LABEL_18:
  *(sdfVector4_t *)v21 = vct_A;
  p_cb->pos_x = *v9;
  p_cb->pos_y = *v22;
  p_cb->vec_x = *v21;
  p_cb->vec_y = *v16;
}

// 0x1cd7370
static void EffGrid_SetCBAll(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 i;
  s8 v7;
  tagLMAP_EFFGRID_CB *v8;

  workdata = proc->workdata;
  for (i = 0; i != 224; ++i)
  {
    v7 = BYTE1(workdata[1].monitor);
    v8 = *((tagLMAP_EFFGRID_CB *)&workdata[2].klass->_1.byval_arg.data + i);
    EffGrid_SetCB(v8, i, v7);
  }
}

// 0x1cd7460
static void EffGrid_UpdateCBMove(tagLMAP_EFFGRID_CB *p_cb) {
  s64 v4;
  s64 v5;

  v4 = *(u64 *)&p_cb->pos_x;
  v5 = *(u64 *)&p_cb->vec_x;
  *(u64 *)&vct_A.x = v5;
  *(u64 *)&vct_A.z = 0;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x3D124925u));
  *(u64 *)&vct_B.x = v4;
  *(u64 *)&vct_B.z = 0;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  *(u64 *)&p_cb->pos_x = *(u64 *)&vct_A.x;
}

// 0x1cd76d0
static void EffGrid_UpdateCBHold(tagLMAP_EFFGRID_CB *p_cb, s32 no) {
  s32 v3;

  v3 = no + 15;
  if (no >= 0)
    v3 = no;
  p_cb->pos_x = (f32)(32 * (no - (v3 & 0x7FFFFF0)));
  p_cb->pos_y = (f32)(s32)((2 * v3) & 0xFFFFFFE0);
}

// 0x1cd7700
static void EffGrid_UpdateCB(tagLMAP_EFFGRID_CB *p_cb, s32 no, s8 type) {
  u32 v7;
  s32 v9;
  s32 v10;
  s8 *cnt;
  s8 v12;
  char *v13;
  u8 *v14;
  s32 v15;

  if ((p_cb->cnt[type] & 0x80000000) == 0)
  {
    v7 = (u8)p_cb->cnt[type];
    if (type)
    {
      if (v7 <= 3)
      {
        v10 = no + 15;
        if (no >= 0)
          v10 = no;
        p_cb->pos_x = (f32)(32 * (no - (v10 & 0x7FFFFF0)));
        p_cb->pos_y = (f32)(s32)((2 * v10) & 0xFFFFFFE0);
      }
      else
      {
        EffGrid_UpdateCBMove(p_cb);
      }
      cnt = p_cb->cnt;
      v12 = (4 * cnt[1]) ^ 0x7C;
    }
    else
    {
      if (v7 <= 0x1B)
      {
        EffGrid_UpdateCBMove(p_cb);
      }
      else
      {
        v9 = no + 15;
        if (no >= 0)
          v9 = no;
        p_cb->pos_x = (f32)(32 * (no - (v9 & 0x7FFFFF0)));
        p_cb->pos_y = (f32)(s32)((2 * v9) & 0xFFFFFFE0);
      }
      cnt = p_cb->cnt;
      v12 = 4 * cnt[0] + 4;
    }
    p_cb->alpha = v12;
    ++cnt[type];
    v13 = (char *)p_cb->cnt + type;
    v15 = v13[32];
    v14 = v13 + 32;
    if (v15 >= 32)
      *v14 = 31;
  }
}

// 0x1cd7870
static void EffGrid_UpdateCBAll(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 i;
  s8 v7;
  tagLMAP_EFFGRID_CB *v8;

  workdata = proc->workdata;
  for (i = 0; i != 224; ++i)
  {
    v7 = BYTE1(workdata[1].monitor);
    v8 = *((tagLMAP_EFFGRID_CB *)&workdata[2].klass->_1.byval_arg.data + i);
    EffGrid_UpdateCB(v8, i, v7);
  }
}

// 0x1cd7960
static void EffGrid_DrawCB(tagLMAP_EFFGRID_CB *p_cb) {
  ;
}

// 0x1cd7970
static void EffGrid_DrawCBAll(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s32 v6;

  workdata = proc->workdata;
  v6 = 224;
  do
  {
    --v6;
  }
  while (v6);
}

// 0x1cd7a30
static bool EffGrid_CheckWait(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  dds3ProcessID_t *id;

  id = proc;
  if (!dds3ExistProcess(id))
  {
    LOBYTE(workdata) = 0;
    return (char)workdata;
  }
  workdata = id->workdata;
  if (workdata)
  {
    LOBYTE(workdata) = LOBYTE(workdata[1].monitor) == 4;
  }
  return (char)workdata;
}

// 0x1cd7b30
static void EffGrid_Init(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;

  workdata = proc->workdata;
  EffGrid_InitCBAll(proc);
  if (!workdata)
  LODWORD(workdata[1].monitor) = 1;
}

// 0x1cd7c10
static dds3ProcessFunc_t EffGrid_Main(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s32 v6;
  dds3ProcessFunc_t v8;

  workdata = proc->workdata;
  switch (LOBYTE(workdata[1].monitor))
  {
    case 1:
      EffGrid_SetCBAll(proc);
      WORD1(workdata[1].monitor) = 0;
      LOBYTE(workdata[1].monitor) = 2;
      goto LABEL_11;
    case 2:
      if (SWORD1(workdata[1].monitor) > 31)
      {
        WORD1(workdata[1].monitor) = 0;
        LOBYTE(workdata[1].monitor) = 3;
        return 0;
      }
LABEL_11:
      EffGrid_UpdateCBAll(proc);
      LOWORD(v6) = WORD1(workdata[1].monitor);
      goto LABEL_12;
    case 3:
      if (BYTE1(workdata[1].monitor))
      {
        LOBYTE(workdata[1].monitor) = 5;
        return 0;
      }
      else
      {
        EffGrid_UpdateCBAll(proc);
        v6 = SWORD1(workdata[1].monitor);
        if (v6 >= 8)
          LOBYTE(workdata[1].monitor) = 4;
LABEL_12:
        WORD1(workdata[1].monitor) = v6 + 1;
        return 0;
      }
    case 4:
      EffGrid_UpdateCBAll(proc);
      LODWORD(workdata[1].monitor) = 257;
      return 0;
    case 5:
      EffGrid_Release(proc);
      v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v8;
    default:
      return 0;
  }
}

// 0x1cd7ea0
static dds3ProcessFunc_t EffGrid_Draw(dds3ProcessID_t *proc) {
  u8 *workdata;
  s64 naturalAligment;
  s64 v5;
  s32 v8;

  workdata = proc->workdata;
  if (workdata)
  {
    if (*(u8 *)(*(u64 *)workdata + 304) < (u32)naturalAligment || *(tagLMAP_EFFGRID_WORK **)(*(u64 *)(*(u64 *)workdata + 200) + 8 * naturalAligment - 8) != tagLMAP_EFFGRID_WORK)
    {
LABEL_21:
    }
  }
  if ((u32)workdata[24] - 1 > 3)
    return 0;
  workdata = proc->workdata;
  if (workdata)
  {
    if (*(u8 *)(*(u64 *)workdata + 304) < (u32)v5 || *(tagLMAP_EFFGRID_WORK **)(*(u64 *)(*(u64 *)workdata + 200) + 8 * v5 - 8) != tagLMAP_EFFGRID_WORK)
    {
      goto LABEL_21;
    }
  }
  v8 = 224;
  do
  {
    --v8;
  }
  while (v8);
  return 0;
}

// 0x1cd8010
static dds3ProcessFunc_t EffGrid_DrawProcess(dds3ProcessID_t *proc) {
  dds3ProcessFunc_t v3;

  EffGrid_Draw(proc);
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_Kernel_dds3ProcessFunc_t_Invoke__, 0);
  return v3;
}

// 0x1cd80c0
static void EffGrid_Initialize(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  dds3ProcessFunc_t v5;
  dds3ProcessID_t *started;

  workdata = proc->workdata;
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_lmap_EffGrid_DrawProcess__, 0);
  started = dds3StartProcess("lmapEffGridDrawProc", 11015, 0, 0, v5, 0, workdata);
  workdata[1].klass = started;
  EffGrid_Init(proc);
}

// 0x1cd8230
static dds3ProcessFunc_t EffGrid_Process(dds3ProcessID_t *proc) {
  dds3ProcessID_t *v4;

  v4 = proc;
  return EffGrid_Main(v4);
}

// 0x1cd82b0
static void EffGrid_Shutdown(dds3ProcessID_t *proc) {
  proc->workdata = 0;
}

// 0x1cd82c0
static dds3ProcessID_t *EffGrid_Start(void) {
  tagLMAP_EFFGRID_WORK *v1;
  dds3ProcessID_t *v2;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;

  v1 = Allocate(tagLMAP_EFFGRID_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_lmap_EffGrid_Process__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_lmap_EffGrid_Shutdown__, 0);
  started = dds3StartProcess("lmapEffGridProc", 1024, 0, 0, v3, v4, v1);
  EffGrid_Initialize(started);
  return started;
}

// 0x1cd6de0
static void EffGrid_ReleaseDraw(void) {
  ;
}

// 0x1cc6630
static void EffGrid_Finish(dds3ProcessID_t *proc) {
  dds3ProcessID_t *v4;
  dds3ProcessID_t *id;

  id = proc;
  if (!dds3ExistProcess(id))
    return;
  v4 = id;
  EffGrid_Release(id);
  dds3KillProcess(id, 0);
  return;
}

// 0x1cd8470
static void EffWave_InitCB(tagLMAP_EFFWAVE_CB *p_cb) {
  *(f32 *)((char *)&p_cb->y1 + 3) = 0.0;
  *(u64 *)&p_cb->y0 = 0;
  *(u16 *)&p_cb->prev = -258;
  p_cb->flg = 0;
}

// 0x1cd8490
static void EffWave_ResetLink(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  Il2CppClass *klass;
  u8 *data;
  s64 v7;
  s32 v8;
  u8 *v9;
  s32 v10;
  s64 v11;
  s32 v12;
  Il2CppClass *element_class;
  s32 v14;
  Il2CppClass *castClass;
  s32 v16;
  Il2CppClass *declaringType;
  s32 v18;
  Il2CppClass *parent;
  s32 v20;
  u8 *generic_class;
  s32 v22;
  u8 *typeMetadataHandle;
  s32 v24;
  u8 *interopData;
  s32 v26;
  Il2CppClass *v27;
  s32 v28;
  u8 *fields;
  s32 v30;
  u8 *events;
  s32 v32;
  u8 *properties;
  s32 v34;
  u8 *methods;
  s32 v36;
  Il2CppClass **nestedTypes;
  s32 v38;
  Il2CppClass **implementedInterfaces;
  s32 v40;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  s32 v42;
  u8 *static_fields;
  s32 v44;
  Il2CppRGCTXData *rgctx_data;
  s32 v46;
  Il2CppClass **typeHierarchy;
  s32 v48;
  u8 *unity_user_data;
  s32 v50;
  s64 v51;
  s32 v52;
  s64 v53;
  s32 v54;
  size_t cctor_thread;
  s32 v56;
  u8 *genericContainerHandle;
  s32 v58;
  s64 v59;
  s32 v60;
  s64 v61;
  s32 v62;
  s64 v63;
  s32 v64;
  s64 v65;
  s32 v66;
  s64 v67;
  s32 v68;

  if (!proc)
    return;
  workdata = proc->workdata;
  if (!workdata)
    return;
  klass = workdata[1].klass;
  data = klass->_1.byval_arg.data;
  if ((u8)data[60] == 255)
  {
    data[59] = -1;
    v7 = *(u64 *)&klass->_1.byval_arg.bits;
    v8 = *(u8 *)(v7 + 60);
    if (v8 != 255)
    {
LABEL_9:
      v9 = klass->_1.this_arg.data;
      v10 = (u8)v9[60];
      if (v10 != 255)
        goto LABEL_10;
      goto LABEL_42;
    }
  }
  else
  {
    v7 = *(u64 *)&klass->_1.byval_arg.bits;
    v8 = *(u8 *)(v7 + 60);
    if (v8 != 255)
      goto LABEL_9;
  }
  *(u8 *)(v7 + 59) = v8;
  v9 = klass->_1.this_arg.data;
  v10 = (u8)v9[60];
  if (v10 != 255)
  {
LABEL_10:
    v11 = *(u64 *)&klass->_1.this_arg.bits;
    v12 = *(u8 *)(v11 + 60);
    if (v12 != 255)
      goto LABEL_11;
    goto LABEL_43;
  }
LABEL_42:
  v9[59] = v10;
  v11 = *(u64 *)&klass->_1.this_arg.bits;
  v12 = *(u8 *)(v11 + 60);
  if (v12 != 255)
  {
LABEL_11:
    element_class = klass->_1.element_class;
    v14 = *((u8 *)&element_class->_1.this_arg.bits + 4);
    if (v14 != 255)
      goto LABEL_12;
    goto LABEL_44;
  }
LABEL_43:
  *(u8 *)(v11 + 59) = v12;
  element_class = klass->_1.element_class;
  v14 = *((u8 *)&element_class->_1.this_arg.bits + 4);
  if (v14 != 255)
  {
LABEL_12:
    castClass = klass->_1.castClass;
    v16 = *((u8 *)&castClass->_1.this_arg.bits + 4);
    if (v16 != 255)
      goto LABEL_13;
    goto LABEL_45;
  }
LABEL_44:
  HIBYTE(element_class->_1.this_arg.bits) = v14;
  castClass = klass->_1.castClass;
  v16 = *((u8 *)&castClass->_1.this_arg.bits + 4);
  if (v16 != 255)
  {
LABEL_13:
    declaringType = klass->_1.declaringType;
    v18 = *((u8 *)&declaringType->_1.this_arg.bits + 4);
    if (v18 != 255)
      goto LABEL_14;
    goto LABEL_46;
  }
LABEL_45:
  HIBYTE(castClass->_1.this_arg.bits) = v16;
  declaringType = klass->_1.declaringType;
  v18 = *((u8 *)&declaringType->_1.this_arg.bits + 4);
  if (v18 != 255)
  {
LABEL_14:
    parent = klass->_1.parent;
    v20 = *((u8 *)&parent->_1.this_arg.bits + 4);
    if (v20 != 255)
      goto LABEL_15;
    goto LABEL_47;
  }
LABEL_46:
  HIBYTE(declaringType->_1.this_arg.bits) = v18;
  parent = klass->_1.parent;
  v20 = *((u8 *)&parent->_1.this_arg.bits + 4);
  if (v20 != 255)
  {
LABEL_15:
    generic_class = klass->_1.generic_class;
    v22 = (u8)generic_class[60];
    if (v22 != 255)
      goto LABEL_16;
    goto LABEL_48;
  }
LABEL_47:
  HIBYTE(parent->_1.this_arg.bits) = v20;
  generic_class = klass->_1.generic_class;
  v22 = (u8)generic_class[60];
  if (v22 != 255)
  {
LABEL_16:
    typeMetadataHandle = klass->_1.typeMetadataHandle;
    v24 = (u8)typeMetadataHandle[60];
    if (v24 != 255)
      goto LABEL_17;
    goto LABEL_49;
  }
LABEL_48:
  generic_class[59] = v22;
  typeMetadataHandle = klass->_1.typeMetadataHandle;
  v24 = (u8)typeMetadataHandle[60];
  if (v24 != 255)
  {
LABEL_17:
    interopData = klass->_1.interopData;
    v26 = (u8)interopData[60];
    if (v26 != 255)
      goto LABEL_18;
    goto LABEL_50;
  }
LABEL_49:
  typeMetadataHandle[59] = v24;
  interopData = klass->_1.interopData;
  v26 = (u8)interopData[60];
  if (v26 != 255)
  {
LABEL_18:
    v27 = klass->_1.klass;
    v28 = *((u8 *)&v27->_1.this_arg.bits + 4);
    if (v28 != 255)
      goto LABEL_19;
    goto LABEL_51;
  }
LABEL_50:
  interopData[59] = v26;
  v27 = klass->_1.klass;
  v28 = *((u8 *)&v27->_1.this_arg.bits + 4);
  if (v28 != 255)
  {
LABEL_19:
    fields = klass->_1.fields;
    v30 = (u8)fields[60];
    if (v30 != 255)
      goto LABEL_20;
    goto LABEL_52;
  }
LABEL_51:
  HIBYTE(v27->_1.this_arg.bits) = v28;
  fields = klass->_1.fields;
  v30 = (u8)fields[60];
  if (v30 != 255)
  {
LABEL_20:
    events = klass->_1.events;
    v32 = (u8)events[60];
    if (v32 != 255)
      goto LABEL_21;
    goto LABEL_53;
  }
LABEL_52:
  fields[59] = v30;
  events = klass->_1.events;
  v32 = (u8)events[60];
  if (v32 != 255)
  {
LABEL_21:
    properties = klass->_1.properties;
    v34 = (u8)properties[60];
    if (v34 != 255)
      goto LABEL_22;
    goto LABEL_54;
  }
LABEL_53:
  events[59] = v32;
  properties = klass->_1.properties;
  v34 = (u8)properties[60];
  if (v34 != 255)
  {
LABEL_22:
    methods = klass->_1.methods;
    v36 = (u8)methods[60];
    if (v36 != 255)
      goto LABEL_23;
    goto LABEL_55;
  }
LABEL_54:
  properties[59] = v34;
  methods = klass->_1.methods;
  v36 = (u8)methods[60];
  if (v36 != 255)
  {
LABEL_23:
    nestedTypes = klass->_1.nestedTypes;
    v38 = *((u8 *)nestedTypes + 60);
    if (v38 != 255)
      goto LABEL_24;
    goto LABEL_56;
  }
LABEL_55:
  methods[59] = v36;
  nestedTypes = klass->_1.nestedTypes;
  v38 = *((u8 *)nestedTypes + 60);
  if (v38 != 255)
  {
LABEL_24:
    implementedInterfaces = klass->_1.implementedInterfaces;
    v40 = *((u8 *)implementedInterfaces + 60);
    if (v40 != 255)
      goto LABEL_25;
    goto LABEL_57;
  }
LABEL_56:
  *((u8 *)nestedTypes + 59) = v38;
  implementedInterfaces = klass->_1.implementedInterfaces;
  v40 = *((u8 *)implementedInterfaces + 60);
  if (v40 != 255)
  {
LABEL_25:
    interfaceOffsets = klass->_1.interfaceOffsets;
    v42 = *((u8 *)&interfaceOffsets[3].offset + 4);
    if (v42 != 255)
      goto LABEL_26;
    goto LABEL_58;
  }
LABEL_57:
  *((u8 *)implementedInterfaces + 59) = v40;
  interfaceOffsets = klass->_1.interfaceOffsets;
  v42 = *((u8 *)&interfaceOffsets[3].offset + 4);
  if (v42 != 255)
  {
LABEL_26:
    v44 = (u8)static_fields[60];
    if (v44 != 255)
      goto LABEL_27;
    goto LABEL_59;
  }
LABEL_58:
  HIBYTE(interfaceOffsets[3].offset) = v42;
  v44 = (u8)static_fields[60];
  if (v44 != 255)
  {
LABEL_27:
    rgctx_data = klass->rgctx_data;
    v46 = BYTE4(rgctx_data[7].klass);
    if (v46 != 255)
      goto LABEL_28;
    goto LABEL_60;
  }
LABEL_59:
  static_fields[59] = v44;
  rgctx_data = klass->rgctx_data;
  v46 = BYTE4(rgctx_data[7].klass);
  if (v46 != 255)
  {
LABEL_28:
    typeHierarchy = klass->_2.typeHierarchy;
    v48 = *((u8 *)typeHierarchy + 60);
    if (v48 != 255)
      goto LABEL_29;
    goto LABEL_61;
  }
LABEL_60:
  BYTE3(rgctx_data[7].type) = v46;
  typeHierarchy = klass->_2.typeHierarchy;
  v48 = *((u8 *)typeHierarchy + 60);
  if (v48 != 255)
  {
LABEL_29:
    unity_user_data = klass->_2.unity_user_data;
    v50 = (u8)unity_user_data[60];
    if (v50 != 255)
      goto LABEL_30;
    goto LABEL_62;
  }
LABEL_61:
  *((u8 *)typeHierarchy + 59) = v48;
  unity_user_data = klass->_2.unity_user_data;
  v50 = (u8)unity_user_data[60];
  if (v50 != 255)
  {
LABEL_30:
    v51 = *(u64 *)&klass->_2.initializationExceptionGCHandle;
    v52 = *(u8 *)(v51 + 60);
    if (v52 != 255)
      goto LABEL_31;
    goto LABEL_63;
  }
LABEL_62:
  unity_user_data[59] = v50;
  v51 = *(u64 *)&klass->_2.initializationExceptionGCHandle;
  v52 = *(u8 *)(v51 + 60);
  if (v52 != 255)
  {
LABEL_31:
    v54 = *(u8 *)(v53 + 60);
    if (v54 != 255)
      goto LABEL_32;
    goto LABEL_64;
  }
LABEL_63:
  *(u8 *)(v51 + 59) = v52;
  v54 = *(u8 *)(v53 + 60);
  if (v54 != 255)
  {
LABEL_32:
    cctor_thread = klass->_2.cctor_thread;
    v56 = *(u8 *)(cctor_thread + 60);
    if (v56 != 255)
      goto LABEL_33;
    goto LABEL_65;
  }
LABEL_64:
  *(u8 *)(v53 + 59) = v54;
  cctor_thread = klass->_2.cctor_thread;
  v56 = *(u8 *)(cctor_thread + 60);
  if (v56 != 255)
  {
LABEL_33:
    genericContainerHandle = klass->_2.genericContainerHandle;
    v58 = (u8)genericContainerHandle[60];
    if (v58 != 255)
      goto LABEL_34;
    goto LABEL_66;
  }
LABEL_65:
  *(u8 *)(cctor_thread + 59) = v56;
  genericContainerHandle = klass->_2.genericContainerHandle;
  v58 = (u8)genericContainerHandle[60];
  if (v58 != 255)
  {
LABEL_34:
    v59 = *(u64 *)&klass->_2.instance_size;
    v60 = *(u8 *)(v59 + 60);
    if (v60 != 255)
      goto LABEL_35;
    goto LABEL_67;
  }
LABEL_66:
  genericContainerHandle[59] = v58;
  v59 = *(u64 *)&klass->_2.instance_size;
  v60 = *(u8 *)(v59 + 60);
  if (v60 != 255)
  {
LABEL_35:
    v61 = *(u64 *)&klass->_2.element_size;
    v62 = *(u8 *)(v61 + 60);
    if (v62 != 255)
      goto LABEL_36;
    goto LABEL_68;
  }
LABEL_67:
  *(u8 *)(v59 + 59) = v60;
  v61 = *(u64 *)&klass->_2.element_size;
  v62 = *(u8 *)(v61 + 60);
  if (v62 != 255)
  {
LABEL_36:
    v63 = *(u64 *)&klass->_2.static_fields_size;
    v64 = *(u8 *)(v63 + 60);
    if (v64 != 255)
      goto LABEL_37;
LABEL_69:
    *(u8 *)(v63 + 59) = v64;
    v65 = *(u64 *)&klass->_2.thread_static_fields_offset;
    v66 = *(u8 *)(v65 + 60);
    if (v66 != 255)
    {
LABEL_38:
      v67 = *(u64 *)&klass->_2.token;
      v68 = *(u8 *)(v67 + 60);
      if (v68 != 255)
        return;
LABEL_71:
      *(u8 *)(v67 + 59) = v68;
      return;
    }
    goto LABEL_70;
  }
LABEL_68:
  *(u8 *)(v61 + 59) = v62;
  v63 = *(u64 *)&klass->_2.static_fields_size;
  v64 = *(u8 *)(v63 + 60);
  if (v64 == 255)
    goto LABEL_69;
LABEL_37:
  v65 = *(u64 *)&klass->_2.thread_static_fields_offset;
  v66 = *(u8 *)(v65 + 60);
  if (v66 != 255)
    goto LABEL_38;
LABEL_70:
  *(u8 *)(v65 + 59) = v66;
  v67 = *(u64 *)&klass->_2.token;
  v68 = *(u8 *)(v67 + 60);
  if (v68 == 255)
    goto LABEL_71;
}

// 0x1cc3480
static void EffWave_SetData(dds3ProcessID_t *proc, const sdfVector4_t *a_pos, const sdfVector4_t *a_vec) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v11;
  f32 v12;
  Il2CppObject *workdata;
  Il2CppClass *klass;
  _BOOL4 v16;
  u32 v17;
  s64 v18;
  s64 v19;
  s32 v20;
  Il2CppType *p_byval_arg;
  s64 v22;
  s64 v23;
  s64 v24;
  char v25;
  Il2CppClass *v26;
  s64 v27;
  char v28;
  Il2CppClass *v29;
  s64 v30;
  u32 v31;
  s64 v32;
  s32 v33;
  s32 v34;
  f32 v35;
  f32 v36;
  f32 v38;
  f32 *v40;
  s64 v41;

  w = a_vec->w;
  z = a_vec->z;
  y = a_vec->y;
  x = a_vec->x;
  v8 = a_pos->w;
  v9 = a_pos->z;
  v11 = a_pos->y;
  v12 = a_pos->x;
  if (proc)
  {
    workdata = proc->workdata;
    if (workdata)
    {
      klass = workdata[1].klass;
      if (*((u8 *)klass->_1.byval_arg.data + 60) == 255)
      {
        v17 = 0;
        v16 = 1;
      }
      else if (*(u8 *)(*(u64 *)&klass->_1.byval_arg.bits + 60) == 255)
      {
        v16 = 0;
        v17 = 1;
      }
      else if (*((u8 *)klass->_1.this_arg.data + 60) == 255)
      {
        v16 = 0;
        v17 = 2;
      }
      else if (*(u8 *)(*(u64 *)&klass->_1.this_arg.bits + 60) == 255)
      {
        v16 = 0;
        v17 = 3;
      }
      else if (*((u8 *)&klass->_1.element_class->_1.this_arg.bits + 4) == 255)
      {
        v16 = 0;
        v17 = 4;
      }
      else if (*((u8 *)&klass->_1.castClass->_1.this_arg.bits + 4) == 255)
      {
        v16 = 0;
        v17 = 5;
      }
      else if (*((u8 *)&klass->_1.declaringType->_1.this_arg.bits + 4) == 255)
      {
        v16 = 0;
        v17 = 6;
      }
      else if (*((u8 *)&klass->_1.parent->_1.this_arg.bits + 4) == 255)
      {
        v16 = 0;
        v17 = 7;
      }
      else if (*((u8 *)klass->_1.generic_class + 60) == 255)
      {
        v16 = 0;
        v17 = 8;
      }
      else if (*((u8 *)klass->_1.typeMetadataHandle + 60) == 255)
      {
        v16 = 0;
        v17 = 9;
      }
      else if (*((u8 *)klass->_1.interopData + 60) == 255)
      {
        v16 = 0;
        v17 = 10;
      }
      else if (*((u8 *)&klass->_1.klass->_1.this_arg.bits + 4) == 255)
      {
        v16 = 0;
        v17 = 11;
      }
      else if (*((u8 *)klass->_1.fields + 60) == 255)
      {
        v16 = 0;
        v17 = 12;
      }
      else if (*((u8 *)klass->_1.events + 60) == 255)
      {
        v16 = 0;
        v17 = 13;
      }
      else if (*((u8 *)klass->_1.properties + 60) == 255)
      {
        v16 = 0;
        v17 = 14;
      }
      else if (*((u8 *)klass->_1.methods + 60) == 255)
      {
        v16 = 0;
        v17 = 15;
      }
      else if (*((u8 *)klass->_1.nestedTypes + 60) == 255)
      {
        v16 = 0;
        v17 = 16;
      }
      else if (*((u8 *)klass->_1.implementedInterfaces + 60) == 255)
      {
        v16 = 0;
        v17 = 17;
      }
      else if (*((u8 *)&klass->_1.interfaceOffsets[3].offset + 4) == 255)
      {
        v16 = 0;
        v17 = 18;
      }
      else if (*((u8 *)klass->static_fields + 60) == 255)
      {
        v16 = 0;
        v17 = 19;
      }
      else if (BYTE4(klass->rgctx_data[7].klass) == 255)
      {
        v16 = 0;
        v17 = 20;
      }
      else if (*((u8 *)klass->_2.typeHierarchy + 60) == 255)
      {
        v16 = 0;
        v17 = 21;
      }
      else if (*((u8 *)klass->_2.unity_user_data + 60) == 255)
      {
        v16 = 0;
        v17 = 22;
      }
      else if (*(u8 *)(*(u64 *)&klass->_2.initializationExceptionGCHandle + 60) == 255)
      {
        v16 = 0;
        v17 = 23;
      }
      {
        v16 = 0;
        v17 = 24;
      }
      else if (*(u8 *)(klass->_2.cctor_thread + 60) == 255)
      {
        v16 = 0;
        v17 = 25;
      }
      else if (*((u8 *)klass->_2.genericContainerHandle + 60) == 255)
      {
        v16 = 0;
        v17 = 26;
      }
      else if (*(u8 *)(*(u64 *)&klass->_2.instance_size + 60) == 255)
      {
        v16 = 0;
        v17 = 27;
      }
      else if (*(u8 *)(*(u64 *)&klass->_2.element_size + 60) == 255)
      {
        v16 = 0;
        v17 = 28;
      }
      else if (*(u8 *)(*(u64 *)&klass->_2.static_fields_size + 60) == 255)
      {
        v16 = 0;
        v17 = 29;
      }
      else if (*(u8 *)(*(u64 *)&klass->_2.thread_static_fields_offset + 60) == 255)
      {
        v16 = 0;
        v17 = 30;
      }
      else
      {
        v16 = *(u8 *)(*(u64 *)&klass->_2.token + 60) != 255;
        if (*(u8 *)(*(u64 *)&klass->_2.token + 60) == 255)
          v17 = 31;
        else
          v17 = 0;
      }
      v18 = v17;
      while (v18 != 31)
      {
        v19 = *((u64 *)&klass->_1.byval_arg.bits + v18);
        v20 = ++v18;
        if (!*(u8 *)(v19 + 61))
        {
          if (v20 != -1)
            v16 = v20;
          break;
        }
      }
      p_byval_arg = &klass->_1.byval_arg;
      v22 = 8 * v17;
      v23 = *((u64 *)&p_byval_arg->data + v16);
      *(u8 *)(v23 + 59) = v17;
      v24 = *(s64 *)((char *)&p_byval_arg->data + v22);
      *(u8 *)(v23 + 60) = -1;
      v25 = sub_1905740(10, 0);
      v26 = workdata[1].klass;
      *(u8 *)(v24 + 56) = v25;
      v27 = *(s64 *)((char *)&v26->_1.byval_arg.data + v22);
      *(u8 *)(v27 + 56) += 10;
      v28 = sub_1905740(10, 0);
      v29 = workdata[1].klass;
      *(u8 *)(v27 + 57) = v28;
      v30 = *(s64 *)((char *)&v29->_1.byval_arg.data + v22);
      *(u8 *)(v30 + 57) += 10;
      v31 = sub_1905740(200, 0);
      v32 = *(s64 *)((char *)&workdata[1].klass->_1.byval_arg.data + v22);
      v33 = *(char *)(v32 + 56);
      v34 = *(char *)(v32 + 57);
      *(f32 *)(v30 + 48) = (f32)v31 / 100.0;
      v35 = v33;
      v36 = *(f32 *)(v32 + 48);
      *(u8 *)(v32 + 57) = v34 + v33;
      v38 = v36 + 1.0;
      *(f32 *)(v32 + 48) = v38;
      *(f32 *)(v32 + 52) = (f32)(v38 * v35) / (f32)v34;
      *(f32 *)(v32 + 16) = v12;
      *(f32 *)(v32 + 20) = v11;
      *(f32 *)(v32 + 24) = v9;
      *(f32 *)(v32 + 28) = v8;
      v40 = *(f32 **)((char *)&workdata[1].klass->_1.byval_arg.data + v22);
      v40[8] = x;
      v40[9] = y;
      v40[10] = z;
      v40[11] = w;
      v41 = *(s64 *)((char *)&workdata[1].klass->_1.byval_arg.data + v22);
      *(u32 *)(v41 + 28) = 1065353216;
      *(u32 *)(v41 + 44) = 1065353216;
      *(u8 *)(v41 + 58) = 0;
      *(u8 *)(v41 + 60) = v16;
      *(u8 *)(v41 + 61) = 1;
    }
  }
}

// 0x1cc3a50
static void EffWave_SetColorType(dds3ProcessID_t *proc, s32 a_type) {
  Il2CppObject *workdata;
  dds3ProcessID_t *id;

  id = proc;
  if (!dds3ExistProcess(id))
    return;
  workdata = id->workdata;
  if (workdata)
  {
    HIDWORD(workdata[2].monitor) = a_type;
  }
}

// 0x1cd8990
static void EffWave_UpdateCB(tagLMAP_EFFWAVE_CB *p_cb, s32 num) {
  s32 cnt;

  cnt = p_cb->cnt;
  if (cnt >= p_cb->max_cnt0)
  {
    if (cnt >= p_cb->max_cnt1)
    {
      *(f32 *)((char *)&p_cb->y1 + 3) = 0.0;
      *(u64 *)&p_cb->y0 = 0;
      *(u16 *)&p_cb->prev = -258;
      p_cb->flg = 0;
    }
    else
    {
      p_cb->pos.y = p_cb->pos.y + p_cb->y1;
      p_cb->cnt = cnt + 1;
    }
  }
  else
  {
    p_cb->pos.y = p_cb->pos.y - p_cb->y0;
    p_cb->cnt = cnt + 1;
  }
}

// 0x1cd8a60
static void EffWave_DrawCB(dds3ProcessID_t *proc, s32 no) {
  Il2CppObject *workdata;
  s64 v7;
  s64 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  s32 waveFlag;
  f32 v16;
  u32 v17;
  sdfVector4_t *v18;
  sdfVector4_t *v19;
  f32 x;
  f32 z;
  f32 w;
  struct sdfVector4_t v23;
  f32 v25;
  f32 *p_x;
  sdfVector4_t *v27;
  struct sdfVector4_t v28;
  f32 v29;
  f32 v30;
  f32 *v31;
  f32 v32;
  sdfVector4_t *v33;
  f32 length;
  f32 *v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 *v42;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v48;
  f32 v49;
  sdfVector4_t *v50;
  s32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  s64 v55;
  s32 v56;
  f32 v57;
  s64 v58;
  s32 v59;
  s32 v60;
  f32 v61;
  f32 v62;
  s32 v63;
  f32 v64;
  s64 v65;
  s32 v66;
  s64 v67;
  s32 v68;
  s64 v69;
  s32 v70;
  s64 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  s32 v75;
  s64 v76;
  f32 v77;
  f32 x3;
  f32 y3;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 z3;
  f32 v87;
  f32 v88;
  f32 v89;
  f32 v90;
  s32 v91;
  f32 v92;
  f32 pos;
  f32 posa;
  sdfVector4_t v102;
  sdfVector4_t v103;
  sdfVector4_t v104;

  workdata = proc->workdata;
  v7 = *((u64 *)&workdata[1].klass->_1.byval_arg.data + no);
  if (!*(u8 *)(v7 + 61))
    return;
  v8 = no;
  v10 = *(f32 *)(v7 + 16);
  v9 = *(f32 *)(v7 + 20);
  v11 = *(f32 *)(v7 + 24);
  waveFlag = lmapwk->waveFlag;
  v16 = LmapCameraPar[28];
  v90 = LmapCameraPar[29];
  if (HIDWORD(workdata[2].monitor) == 1)
    v17 = -2130739072;
  else
    v17 = -2147467009;
  v87 = LmapCameraPar[30];
  v18 = NewSpecific(sdfVector4_t, 4u);
  v19 = *((sdfVector4_t *)&workdata[1].klass->_1.byval_arg.data + v8);
  x = v19[1].x;
  z = v19[1].z;
  w = v19[1].w;
  v23 = v19[2];
  vct_A = v23;
  v25 = *(f32 *)&workdata[2].klass;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v25);
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = 0.0;
  p_x[10] = z;
  p_x[11] = w;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v27 = &v18[0];
  *v27 = vct_A;
  v28 = *(sdfVector4_t *)(*((u64 *)&workdata[1].klass->_1.byval_arg.data + v8) + 32);
  v88 = v11;
  v89 = v10;
  vct_A = v28;
  v29 = *((f32 *)&workdata[2].klass + 1);
  v30 = -v29;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v30);
  v31 = &vf00.x;
  v31[8] = x;
  v31[9] = 0.0;
  v31[10] = z;
  v31[11] = w;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v32 = v9;
  v33 = &v18[1];
  v92 = v16;
  pos = w;
  v91 = waveFlag;
  *v33 = vct_A;
  length = *(f32 *)&workdata[2].monitor;
  v36 = *((f32 **)&workdata[1].klass->_1.byval_arg.data + v8);
  v37 = v36[8];
  v38 = v36[9];
  v39 = v36[10];
  v40 = v36[11];
  v103.w = pos;
  v103.y = 0.0;
  v102.x = v37;
  v102.y = v38;
  v102.z = v39;
  v102.w = v40;
  v103.x = x;
  v103.z = z;
  Util_GetVerticalPosition(v102, v103, length);
  v41 = v32;
  v42 = &v18[2];
  v44 = v32 / v90;
  v104.y = 0.0;
  v104.z = z;
  v45 = v92 * v44;
  v104.w = pos;
  v46 = v91;
  *(_OWORD *)v42 = *((_OWORD *)*((const MethodInfo *)SDF_VU0 + 2).virtualMethodPointer + 1);
  v104.x = x;
  Util_GetVerticalPosition(*(sdfVector4_t *)(*((u64 *)&workdata[1].klass->_1.byval_arg.data + v8) + 32), v104, -*(f32 *)&workdata[2].monitor);
  v48 = v45 * v46;
  v49 = v44 * v87;
  v50 = &v18[3];
  v51 = 0;
  v52 = v89 + v48;
  v53 = v88 + v49;
  *v50 = vct_A;
  do
  {
    while (1)
    {
      v57 = v18[0].x;
      v61 = v18[1].x;
      if (v57 <= v61)
        break;
      v55 = *(u64 *)&v18[1].y;
      v56 = *(u32 *)&v18[1].w;
      v57 = v27->x;
      v58 = *(u64 *)&v18[0].y;
      v59 = 0;
      v18[0].x = v61;
      v60 = *(u32 *)&v18[0].w;
      *(u64 *)&v18[0].y = v55;
      *(u32 *)&v18[0].w = v56;
      v18[1].x = v57;
      v61 = v57;
      *(u64 *)&v18[1].y = v58;
      *(u32 *)&v18[1].w = v60;
      v62 = v18[2].x;
      if (v57 <= v62)
        goto LABEL_47;
LABEL_50:
      v65 = *(u64 *)&v18[2].y;
      v66 = *(u32 *)&v18[2].w;
      v61 = v33->x;
      v67 = *(u64 *)&v18[1].y;
      v18[1].x = v62;
      v62 = v61;
      v68 = *(u32 *)&v18[1].w;
      v63 = 0;
      *(u64 *)&v18[1].y = v65;
      *(u32 *)&v18[1].w = v66;
      v18[2].x = v61;
      *(u64 *)&v18[2].y = v67;
      *(u32 *)&v18[2].w = v68;
      v64 = v18[3].x;
      if (v62 <= v64)
        goto LABEL_42;
LABEL_53:
      v69 = *(u64 *)&v18[3].y;
      v70 = *(u32 *)&v18[3].w;
      v62 = *v42;
      v71 = *(u64 *)&v18[2].y;
      v51 = 0;
      v18[2].x = v64;
      *(u64 *)&v18[2].y = v69;
      *(u64 *)&v18[3].y = v71;
      LODWORD(v71) = *(u32 *)&v18[2].w;
      *(u32 *)&v18[2].w = v70;
      v18[3].x = v62;
      *(u32 *)&v18[3].w = v71;
    }
    v59 = v51 + 1;
    v62 = v18[2].x;
    if (v61 > v62)
      goto LABEL_50;
LABEL_47:
    v63 = v59 + 1;
    v64 = v18[3].x;
    if (v62 > v64)
      goto LABEL_53;
LABEL_42:
    v51 = v63 + 1;
    v54 = v62;
  }
  while (v51 <= 2);
  v72 = v18[1].z;
  posa = v53;
  v73 = v18[2].z;
  if (v72 >= v73)
  {
    v54 = v18[1].x;
    v74 = v18[1].y;
    v77 = v41;
    v73 = v18[1].z;
    x3 = v18[0].x;
    y3 = v18[0].y;
    v81 = v18[0].z;
  }
  else
  {
    v74 = v18[2].y;
    v75 = *(u32 *)&v18[2].w;
    v72 = v18[1].z;
    v76 = *(u64 *)&v18[1];
    v77 = v41;
    v18[1].x = v54;
    v18[1].y = v74;
    *(u64 *)&v18[2] = v76;
    LODWORD(v76) = *(u32 *)&v18[1].w;
    v18[1].z = v73;
    *(u32 *)&v18[1].w = v75;
    v18[2].z = v72;
    *(u32 *)&v18[2].w = v76;
    x3 = v18[0].x;
    y3 = v18[0].y;
    v81 = v18[0].z;
  }
  z3 = v81;
  v82 = v77;
  v83 = v77;
  v84 = posa;
  eglLinkPoly42(v52, v83, posa, v52, v82, posa, v54, v74, v73, x3, y3, z3, 0x80FFFFFF, 0x80FFFFFF, v17, v17);
  eglLinkPoly42(v18[0].x, v18[0].y, v18[0].z, v52, v82, v84, v18[2].x, v18[2].y, v18[2].z, v52, v82, v84, v17, 0x80FFFFFF, v17, 0x80FFFFFF);
  eglLinkPoly42(v52, v82, v84, v18[1].x, v18[1].y, v18[1].z, v52, v82, v84, v18[3].x, v18[3].y, v18[3].z, 0x80FFFFFF, v17, 0x80FFFFFF, v17);
  eglLinkPoly42(v52, v82, v84, v52, v82, v84, v18[2].x, v18[2].y, v18[2].z, v18[3].x, v18[3].y, v18[3].z, 0x80FFFFFF, 0x80FFFFFF, v17, v17);
}

// 0x1cd9660
static void EffWave_Init(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 i;
  void *p_LMAP_MANAGER;
  s64 v8;

  workdata = proc->workdata;
  for (i = 0; i != 32; ++i)
  {
    v8 = *((u64 *)&workdata[1].klass->_1.byval_arg.data + i);
    *(u32 *)(v8 + 55) = 0;
    *(u64 *)(v8 + 48) = 0;
    *(u16 *)(v8 + 59) = -258;
    p_LMAP_MANAGER = &LMAP_MANAGER;
    *(u8 *)(v8 + 61) = 0;
    WaveObjListAdd(p_LMAP_MANAGER, i, 0);
  }
  __asm { FMOV            V0.2S, #4.0 }
  *(u16 *)((char *)workdata[1].klass->_1.byval_arg.data + 59) = -1;
  workdata[2].klass = _D0;
  workdata[2].monitor = 0x40000000;
}

// 0x1cd97a0
static dds3ProcessFunc_t EffWave_Process(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  s64 i;
  f32 v6;
  s64 v7;
  s32 v8;

  workdata = proc->workdata;
  for (i = 32; i != 288; i += 8)
  {
    v7 = *(s64 *)((char *)&workdata[1].klass->_1.image + i);
    if (!*(u8 *)(v7 + 61))
      continue;
    goto LABEL_9000;
    if (v8 < *(char *)(v7 + 56))
    {
LABEL_7:
      v6 = *(f32 *)(v7 + 20) - *(f32 *)(v7 + 48);
LABEL_8:
      *(f32 *)(v7 + 20) = v6;
      *(u8 *)(v7 + 58) = v8 + 1;
      continue;
    }
    goto LABEL_17;
LABEL_9000:
    v8 = *(char *)(v7 + 58);
    if (v8 < *(char *)(v7 + 56))
      goto LABEL_7;
LABEL_17:
    if (v8 < *(char *)(v7 + 57))
    {
      v6 = *(f32 *)(v7 + 20) + *(f32 *)(v7 + 52);
      goto LABEL_8;
    }
    *(u32 *)(v7 + 55) = 0;
    *(u64 *)(v7 + 48) = 0;
    *(u16 *)(v7 + 59) = -258;
    *(u8 *)(v7 + 61) = 0;
  }
  return 0;
}

// 0x1cb9430
static void EffWave_Draw(dds3ProcessID_t *proc) {
  void *v9;
  s32 i;
  void *v12;
  void *p_waveMesh;

  eglSetOt(44);
  eglLinkTest(SET_10AADD12);
  eglLinkAlpha(0);
  if (!op_Equality(waveMesh, 0, 0))
  {
    goto LABEL_11;
  }
  v12 = eglNewMesh3D(1);
  p_waveMesh = &waveMesh;
  p_waveMesh = v12;
LABEL_11:
  v9 = waveMesh;
  eglLinkMesh(v9);
  for (i = 0; i != 32; ++i)
  {
    EffWave_DrawCB(proc, i);
  }
}

// 0x1cd9930
static void EffWave_Shutdown(dds3ProcessID_t *proc) {
  proc->workdata = 0;
}

// 0x1cca9a0
static dds3ProcessID_t *EffWave_Start(void) {
  tagLMAP_EFFWAVE_WORK *v1;
  dds3ProcessID_t *v2;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;

  v1 = Allocate(tagLMAP_EFFWAVE_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_lmap_EffWave_Process__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_lmap_EffWave_Shutdown__, 0);
  started = dds3StartProcess("lmapEffWaveProc", 1031, 0, 0, v3, v4, v1);
  EffWave_Init(started);
  return started;
}

// 0x1cc6730
static void EffWave_Finish(dds3ProcessID_t *proc) {
  dds3ProcessID_t *id;

  id = proc;
  if (proc)
  {
    dds3KillProcess(id, 1);
  }
}

// 0x1cd9980
static void FldWnd_LoadTexMem(tagLMAP_FLDWND_WORK *wk) {
  char *v2;
  char *v3;
  u64 *v4;
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

  v2 = NewSpecific(string, 0x11u);
  v3 = "/lmap/map01.tmx";
  v4 = v2;
  v2[0] = "/lmap/map01.tmx";
  v5 = "/lmap/map02.tmx";
  v4[5] = "/lmap/map02.tmx";
  v6 = "/lmap/map03.tmx";
  v4[6] = "/lmap/map03.tmx";
  v7 = "/lmap/map04.tmx";
  v4[7] = "/lmap/map04.tmx";
  v8 = "/lmap/map05.tmx";
  v4[8] = "/lmap/map05.tmx";
  v9 = "/lmap/map06.tmx";
  v4[9] = "/lmap/map06.tmx";
  v10 = "/lmap/map07.tmx";
  v4[10] = "/lmap/map07.tmx";
  v11 = "/lmap/map08.tmx";
  v4[11] = "/lmap/map08.tmx";
  v12 = "/lmap/map09.tmx";
  v4[12] = "/lmap/map09.tmx";
  v13 = "/lmap/map10.tmx";
  v4[13] = "/lmap/map10.tmx";
  v14 = "/lmap/map11.tmx";
  v4[14] = "/lmap/map11.tmx";
  v15 = "/lmap/map12.tmx";
  v4[15] = "/lmap/map12.tmx";
  v16 = "/lmap/map13.tmx";
  v4[16] = "/lmap/map13.tmx";
  v17 = "/lmap/map14.tmx";
  v4[17] = "/lmap/map14.tmx";
  v18 = "/lmap/map15.tmx";
  v4[18] = "/lmap/map15.tmx";
  v19 = "/lmap/map16.tmx";
  v4[19] = "/lmap/map16.tmx";
  v20 = "/lmap/map17.tmx";
  v4[20] = "/lmap/map17.tmx";
}

// 0x1cd9c50
static void FldWnd_LoadTexHnd(tagLMAP_FLDWND_WORK *wk) {
  void *v3;

  v3 = NewSpecific(sbyte, 0x27u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__63F8640BF624A24629C47F368327C3C12B65D80266ACA31642CAEA400C83AFE2, 0);
  wk->fileNo = *((char *)&v3[2].klass + wk->fieldNo);
}

// 0x1cd9ce0
static void FldWnd_CallStart(tagLMAP_FLDWND_WORK *wk) {
  s32 width;
  s32 height;
  void *v5;
  f32 fy;
  f32 fx;
  f32 x;
  itfMover_t *mover;
  f32 v11;
  s32 v12;
  s32 v13;
  f32 v14;
  s32 v15;
  f32 v16;
  f32 v17;
  s32 v18;
  f32 v19;
  s32 v20;
  f32 v21;
  s32 v22;
  s32 v23;
  f32 v24;
  s32 v25;
  s32 v26;
  s32 v27;

  width = get_width(0);
  height = get_height(0);
  v5 = NewSpecific(sbyte, 0x27u);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__63F8640BF624A24629C47F368327C3C12B65D80266ACA31642CAEA400C83AFE2, 0);
  fx = wk->fx;
  fy = wk->fy;
  wk->fileNo = *((char *)&v5[2].klass + wk->fieldNo);
  x = itfGetMsgWndLocalPos().x;
  mover = wk->mover;
  v11 = width;
  if (width >= 0)
    v12 = width;
  else
    v12 = width + 1;
  v13 = v12 >> 1;
  v14 = v11 / 1920.0;
  if (fx == INFINITY)
    v15 = 0x80000000;
  else
    v15 = fx;
  if (v15 <= v13)
    v16 = v14 * 450.0;
  else
    v16 = -(f32)(v14 * 450.0);
  v17 = (f32)((f32)((f32)(v11 / 1920.0) * (f32)(x * 0.5)) + (f32)v13) + v16;
  v18 = v17;
  v19 = v14 * 370.0;
  if (v17 == INFINITY)
    v18 = 0x80000000;
  v20 = v19;
  v21 = v11 - v19;
  if (v19 == INFINITY)
    v20 = 0x80000000;
  if (v19 > (f32)v18)
    v18 = v20;
  v22 = v21;
  if (v21 == INFINITY)
    v22 = 0x80000000;
  if (v21 >= (f32)v18)
    v23 = v18;
  else
    v23 = v22;
  v24 = (f32)((f32)height / 1080.0) * 120.0;
  v25 = v24;
  if (v24 == INFINITY)
    v25 = 0x80000000;
  if (height >= 0)
    v26 = height;
  else
    v26 = height + 1;
  if (fy == INFINITY)
    v27 = 0x80000000;
  else
    v27 = fy;
  itfMoverSetParam(mover, v15, v27, v23, v25 + (v26 >> 1), 10);
  p2sdPlaySE_Vol(6946818, 127);
}

// 0x1cd9f40
static void _FldWnd_CallEnd(tagLMAP_FLDWND_WORK *wk) {
  itfMover_t *mover;
  s64 v4;
  itfMover_t *v5;
  s32 v6;
  s32 v7;
  s32 v8;
  s64 a_pPosY;

  a_pPosY = 0;
  mover = wk->mover;
  itfMoverGetPosition(mover, (f32 *)&a_pPosY + 1, &a_pPosY);
  v4 = a_pPosY;
  v5 = wk->mover;
  if (*((f32 *)&v4 + 1) == INFINITY)
    v6 = 0x80000000;
  else
    v6 = *((f32 *)&v4 + 1);
  if (v6 < 257)
    v7 = -60;
  else
    v7 = 60;
  if (*(f32 *)&v4 == INFINITY)
    v8 = 0x80000000;
  else
    v8 = *(f32 *)&v4;
  itfMoverSetParam(v5, v6, v8, v7 + v6, v8, 30);
}

// 0x1cda020
static dds3ProcessFunc_t FldWnd_Process(dds3ProcessID_t *PID) {
  tagLMAP_FLDWND_WORK *workdata;
  s8 stat;
  itfMover_t *mover;
  itfMover_t *v11;
  s8 v12;

  workdata = PID->workdata;
  switch (workdata->step)
  {
    case 0:
      stat = workdata->stat;
      workdata->stat = stat & 0xFD;
      if ((stat & 4) == 0)
        return 0;
      if (CNT)
      {
        if (CNT != 1)
        {
          workdata->stat &= ~4u;
LABEL_14:
          FldWnd_CallStart(workdata);
          workdata->stat |= 2u;
          workdata->step = 1;
          return 0;
        }
        CNT = 0;
        workdata->stat &= ~4u;
        goto LABEL_14;
      }
      CNT = 1;
      return 0;
    case 1:
      mover = workdata->mover;
      if (itfMoverUpdate(mover) != 2)
        return 0;
      workdata->step = 2;
      return 0;
    case 2:
      if ((workdata->stat & 8) == 0)
        return 0;
      workdata->stat &= ~8u;
      _FldWnd_CallEnd(workdata);
      workdata->step = 3;
      return 0;
    case 3:
      v11 = workdata->mover;
      if (itfMoverUpdate(v11) != 2)
        return 0;
      v12 = workdata->stat;
      workdata->step = 0;
      workdata->stat = v12 & 0xFD;
      return 0;
    default:
      return 0;
  }
}

// 0x1cda2b0
static void FldWnd_DrawThumbnail(tagLMAP_FLDWND_WORK *wk) {
  itfMover_t *mover;
  f32 Ratio;
  s32 step;
  itfMover_t *v6;
  s64 v7;
  s32 fileNo;
  f32 v11;
  f32 v12;
  f32 v13;
  s64 a_pPosY;

  a_pPosY = 0;
  mover = wk->mover;
  Ratio = itfMoverGetRatio(mover);
  step = wk->step;
  v6 = wk->mover;
  itfMoverGetPosition(v6, (f32 *)&a_pPosY + 1, &a_pPosY);
  v7 = a_pPosY;
  fileNo = wk->fileNo;
  if (*(f32 *)&v7 == INFINITY)
    v11 = -2147500000.0;
  else
    v11 = (s32)*(f32 *)&v7;
  v12 = 1.0;
  v13 = (s32)*((f32 *)&v7 + 1);
  if (*((f32 *)&v7 + 1) == INFINITY)
    v13 = -2147500000.0;
  if (step < 2)
    v12 = Ratio;
  DrawThumb(fwWork, fileNo, v13, v11, v12, 0);
}

// 0x1cda4e0
static dds3ProcessFunc_t FldWnd_DrawProcess(dds3ProcessID_t *PID) {
  tagLMAP_FLDWND_WORK *workdata;
  s8 stat;
  itfMover_t *mover;
  itfMover_t *v11;
  s64 a_pPosY;

  workdata = PID->workdata;
  stat = workdata->stat;
  a_pPosY = 0;
  if ((stat & 2) == 0)
  {
    ClearThumb(fwWork, 0);
    return 0;
  }
  FldWnd_DrawThumbnail(workdata);
  if (workdata->step < 2)
    return 0;
  mover = workdata->mover;
  itfMoverGetRatio(mover);
  v11 = workdata->mover;
  itfMoverGetPosition(v11, (f32 *)&a_pPosY + 1, &a_pPosY);
  return 0;
}

// 0x1ccaf80
static bool FldWnd_Start(s32 a_fieldNo, const sdfVector4_t *a_pos) {
  f32 z;
  f32 y;
  f32 x;
  Il2CppObject *workdata;
  char v10;
  unsigned __int128 v13;

  z = a_pos->z;
  y = a_pos->y;
  x = a_pos->x;
  workdata = g_mainPID_FLDWND->workdata;
  if (!workdata)
    goto LABEL_9;
  goto LABEL_7;
  if (!workdata)
LABEL_7:
LABEL_9:
  v10 = BYTE5(workdata[3].klass);
  if ((v10 & 4) == 0)
  {
    v13 = 0u;
    LODWORD(workdata[2].monitor) = a_fieldNo;
    sBtlChangeWorldtoScreenUnity3(x, y, z, &v13);
    *(void **)((char *)&workdata[2].monitor + 4) = v13;
    BYTE5(workdata[3].klass) |= 4u;
  }
  return (v10 & 4) == 0;
}

// 0x1cc6120
static void FldWnd_CallEnd(void) {
  Il2CppObject *workdata;

  workdata = g_mainPID_FLDWND->workdata;
  if (!workdata)
  BYTE5(workdata[3].klass) |= 8u;
}

// 0x1cc1c70
static void FldWnd_Reset(void) {
  Il2CppObject *workdata;

  workdata = g_mainPID_FLDWND->workdata;
  if (!workdata)
  HIDWORD(workdata[3].klass) = 0;
}

// 0x1cca8b0
static void FldWnd_LinkSprite(sprHandle_t *a_hSpr) {
  Il2CppObject *workdata;

  workdata = g_mainPID_FLDWND->workdata;
  if (!workdata)
    goto LABEL_9;
  goto LABEL_7;
  if (!workdata)
LABEL_7:
LABEL_9:
  if (a_hSpr)
  {
    workdata[1].monitor = a_hSpr;
  }
}

// 0x1cc1d40
static void FldWnd_SetFlagDraw(bool a_bDraw) {
  Il2CppObject *workdata;
  char v6;

  workdata = g_mainPID_FLDWND->workdata;
  if (!workdata)
    goto LABEL_9;
  goto LABEL_7;
  if (!workdata)
LABEL_7:
LABEL_9:
  if (a_bDraw)
    v6 = 2;
  else
    v6 = 0;
  BYTE5(workdata[3].klass) = BYTE5(workdata[3].klass) & 0xFD | v6;
}

// 0x1cda6a0
static void FldWnd_Release(tagLMAP_FLDWND_WORK *wk) {
  if ((byte_5757714 & 1) != 0)
  {
    if ((wk->stat & 1) != 0)
      return;
LABEL_5:
    if (!dds3ExistProcess(&wk->drawPID))
      goto LABEL_12;
    goto LABEL_9000;
    if (!dds3ExistProcess(&wk->drawPID))
    {
LABEL_12:
      wk->drawPID = 0;
      wk->stat |= 1u;
      return;
    }
LABEL_9000:
    dds3KillProcess(&wk->drawPID, 0);
    goto LABEL_12;
  }
  if ((wk->stat & 1) == 0)
    goto LABEL_5;
}

// 0x1cda780
static void FldWnd_Shutdown(dds3ProcessID_t *PID) {
  tagLMAP_FLDWND_WORK *workdata;

  workdata = PID->workdata;
  if (!workdata)
  FldWnd_Release(workdata);
}

// 0x1cca6a0
static void FldWnd_ProcessStart(void) {
  tagLMAP_FLDWND_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_g_mainPID_FLDWND;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;
  tagLMAP_FLDWND_WORK *v9;

  v1 = Allocate(tagLMAP_FLDWND_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_lmap_FldWnd_Process__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_lmap_FldWnd_Shutdown__, 0);
  started = dds3StartProcess("lmapFldWndMainProc", 1031, 0, 0, v2, v3, v1);
  p_g_mainPID_FLDWND = &g_mainPID_FLDWND;
  p_g_mainPID_FLDWND = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_lmap_FldWnd_DrawProcess__, 0);
  v8 = dds3StartProcess("lmapFldWndDrawProc", 11031, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
  FldWnd_LoadTexMem(v9);
}

// 0x1cc6490
static void FldWnd_ProcessEnd(void) {
  dds3ProcessID_t *p_g_mainPID_FLDWND;
  tagLMAP_FLDWND_WORK *workdata;

  if (!dds3ExistProcess(g_mainPID_FLDWND))
  {
    goto LABEL_6;
  }
  workdata = g_mainPID_FLDWND->workdata;
  if (!workdata)
  FldWnd_Release(workdata);
  dds3KillProcess(g_mainPID_FLDWND, 1);
LABEL_6:
  p_g_mainPID_FLDWND = &g_mainPID_FLDWND;
  p_g_mainPID_FLDWND = 0;
}

// 0x1cda850
void lmapInitFldThumbnailWork(void *s_work) {
  fwWork = s_work;
}

// 0x1cda440
static void DrawFldThumbnail(s32 index, f32 x, f32 y, f32 alpha) {
  DrawThumb(fwWork, index, x, y, alpha, 0);
}

// 0x1cc6200
static void ClearFldThumbnail(void) {
  ClearThumb(fwWork, 0);
}

// 0x1cb4870
static s16 MapDat_GetPointDat(s32 list_no, s32 type) {
  s16 result;

  if (list_no < 0)
    return 0;
  if (SLODWORD(lmap_tbl_point->max_length) <= list_no)
    return 0;
  switch (type)
  {
    case 0:
      result = lmap_tbl_point[list_no]->no;
      break;
    case 1:
      result = lmap_tbl_point[list_no]->x;
      break;
    case 2:
      result = lmap_tbl_point[list_no]->y;
      break;
    case 3:
      result = lmap_tbl_point[list_no]->id;
      break;
    case 4:
      result = lmap_tbl_point[list_no]->flag;
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1cb5020
static s16 MapDat_GetLineDat(s32 list_no, s32 type) {
  s16 result;

  if (list_no < 0)
    return 0;
  if (SLODWORD(lmap_tbl_line->max_length) <= list_no)
    return 0;
  switch (type)
  {
    case 0:
      result = lmap_tbl_line[list_no]->line_no;
      break;
    case 1:
      result = lmap_tbl_line[list_no]->point_no0;
      break;
    case 2:
      result = lmap_tbl_line[list_no]->point_no1;
      break;
    case 3:
      result = lmap_tbl_line[list_no]->line_type;
      break;
    case 4:
      result = lmap_tbl_line[list_no]->area_no;
      break;
    default:
      return 0;
  }
  return result;
}

// 0x1cb5730
static s16 MapDat_GetRouteDat(s32 list_no, s32 type) {
  if ((u32)type <= 9)
  {
    return lmap_tbl_route[list_no]->pointNo[type];
  }
  else
  {
    switch (type)
    {
      case 12:
        return lmap_tbl_route[list_no]->stat;
      case 11:
        return lmap_tbl_route[list_no]->type;
      case 10:
        return lmap_tbl_route[list_no]->relay;
      default:
        return 0;
    }
  }
}

// 0x1cc7050
static s16 MapDat_GetPointTableNo(s16 pointNo) {
  s16 v3;

  v3 = 0;
  while ((dmLMAP_POINT_NO(v3) & 0x8000) == 0)
  {
    if (dmLMAP_POINT_NO(v3) == pointNo)
      return v3;
    ++v3;
  }
  return -1;
}

// 0x1cc3b40
static s16 MapDat_GetPointID(s16 pointNo) {
  s16 v4;

  v4 = 0;
  goto LABEL_7;
  while (1)
  {
LABEL_7:
    if (dmLMAP_POINT_NO(v4) < 0)
      return -1;
    if (dmLMAP_POINT_NO(v4) == pointNo)
      break;
    ++v4;
  }
  if (v4 < 0)
    return -1;
  return dmLMAP_POINT_ID(v4);
}

// 0x1cc16e0
static u8 MapDat_GetPointFlag(s16 pointNo) {
  s16 v4;

  v4 = 0;
  goto LABEL_12;
  while (1)
  {
LABEL_12:
    if (dmLMAP_POINT_NO(v4) < 0)
      return 0;
    if (dmLMAP_POINT_NO(v4) == pointNo)
      break;
    ++v4;
  }
  if (v4 < 0)
    return 0;
  return dmLMAP_POINT_FLAG(v4);
}

// 0x1ccdb00
static bool MapDat_GetPointXY(s16 pointNo, f32 *x, f32 *y) {
  s16 v8;

  v8 = 0;
  goto LABEL_12;
  while (1)
  {
LABEL_12:
    if (dmLMAP_POINT_NO(v8) < 0)
      return 0;
    if (dmLMAP_POINT_NO(v8) == pointNo)
      break;
    ++v8;
  }
  if (v8 < 0)
    return 0;
  *x = (f32)dmLMAP_POINT_X(v8);
  *y = (f32)dmLMAP_POINT_Y(v8);
  return 1;
}

// 0x1cc3d40
u8 lmapMapDat_GetMapId(s16 a_pointNo) {
  s32 v4;
  s16 *v5;
  s64 v6;

  v4 = 0;
  do
  {
    while (1)
    {
      v5 = lmap_tbl_mapid[v4];
      if (v5[0] <= 0)
        return 1;
      v6 = v4;
      break;
    }
    ++v4;
  }
  while (v5[0] != a_pointNo);
  v5 = lmap_tbl_mapid[v6];
  return v5[1];
}

// 0x1cd1d70
static s8 MapDat_ChkCoastlineDat(s16 a_no) {
  s32 flag;

  if (a_no < 0)
    return -2;
  if (SLODWORD(lmpCoastlineDat->max_length) <= (u16)a_no)
    return -2;
  flag = lmpCoastlineDat[(u16)a_no]->flag;
  if (flag >= 1)
  {
    if (!evtBitCheck(flag))
      return 0;
  }
  if (flag < 0)
    return -1;
  else
    return 1;
}

// 0x1cd1e90
static void MapDat_GetCoastlineDat(s16 *a_pDat, s16 a_no, s16 a_type) {
  s32 flag;
  s16 *p_fields;
  tagLMP_COASTLINE_DAT *v13;

  if ((u16)a_type > 3u)
    return;
  if (a_no < 0)
    return;
  if (SLODWORD(lmpCoastlineDat->max_length) <= a_no)
    return;
  flag = lmpCoastlineDat[(u16)a_no]->flag;
  if (flag < 1)
  {
    if (flag)
      return;
    goto LABEL_15;
  }
  if (!evtBitCheck(flag))
    return;
LABEL_15:
  switch (a_type)
  {
    case 0:
      p_fields = &lmpCoastlineDat[(u16)a_no]->fields;
      goto LABEL_29;
    case 1:
      v13 = lmpCoastlineDat[(u16)a_no];
      goto LABEL_28;
    case 2:
      p_fields = &lmpCoastlineDat[a_no + 1]->fields;
      goto LABEL_29;
    case 3:
      v13 = lmpCoastlineDat[a_no + 1];
LABEL_28:
      p_fields = &v13->y;
LABEL_29:
      *a_pDat = *p_fields;
      break;
    default:
      return;
  }
}

// 0x1cd4640
static s16 MapDat_GetPointStation(s16 a_pointNo) {
  s32 i;
  s16 *v5;
  s64 v6;

  for (i = 0; ; ++i)
  {
    v5 = lmap_arrPointStation[i];
    if (v5[0] < 0)
      return -1;
    v6 = i;
    if (v5[0] == a_pointNo)
      goto LABEL_15;
LABEL_12:
    v5 = lmap_arrPointStation[i];
    if (v5[1] == a_pointNo)
    {
      return v5[0];
    }
  }
  v5 = lmap_arrPointStation[i];
  if (v5[0] != a_pointNo)
    goto LABEL_12;
LABEL_15:
  v5 = lmap_arrPointStation[i];
  return v5[1];
}

// 0x1cc9500
static void Util_Point3To2(f32 x3, f32 y3, f32 z3, f32 *x2, f32 *y2) {
  sdfMatrix4_t *p_CameraTM;
  __int128 v14;
  __int128 v17;
  __int128 v18;
  _OWORD *p_x;
  long f64 v21;
  __int128 v22;
  sdfMatrix4_t *p_TM;
  _OWORD *v25;
  __int128 v26;
  __int128 v27;
  __int128 v28;
  struct sdfVector4_t scale;
  struct sdfVector4_t trans;
  f32 y;
  long f64 v37;
  sdfMatrix4_t v42;
  sdfMatrix4_t v43;
  sdfVector4_t v44;

  p_CameraTM = &CameraTM;
  v14 = *(_OWORD *)&p_CameraTM->m01;
  *(_OWORD *)&v43.m00 = *(_OWORD *)&p_CameraTM->m00;
  *(_OWORD *)&v43.m01 = v14;
  v17 = *(_OWORD *)&p_CameraTM->m03;
  *(_OWORD *)&v43.m02 = *(_OWORD *)&p_CameraTM->m02;
  *(_OWORD *)&v43.m03 = v17;
  v18 = *(_OWORD *)&v43.m01;
  p_x = &vf00.x;
  p_x[4] = *(_OWORD *)&v43.m00;
  p_x[5] = v18;
  v21 = *(long f64 *)&v43.m02;
  v22 = *(_OWORD *)&v43.m03;
  p_x[6] = *(_OWORD *)&v43.m02;
  p_x[7] = v22;
  p_TM = &ScreenParam->TM;
  sub_19636F0(&ScreenParam->TM, 0, v21);
  v25 = &vf00.x;
  v26 = v25[5];
  v27 = v25[6];
  v28 = v25[7];
  v25[8] = v25[4];
  v25[9] = v26;
  v25[10] = v27;
  v25[11] = v28;
  vct_A.x = x3;
  vct_A.y = y3;
  vct_A.z = z3;
  vct_A.w = 1.0;
  vct_A.w = 1.0;
  get_transpose(&v43, &mtx_A, 0);
  v42 = v43;
  v44 = op_Multiply_60923920(&v42, vct_A, 0);
  vct_A.x = v44.x * (f32)(1.0 / v44.w);
  vct_A.y = v44.y * (f32)(1.0 / v44.w);
  vct_A.z = v44.z * (f32)(1.0 / v44.w);
  vct_A.w = 1.0 / v44.w;
  scale = ScreenParam->scale;
  vct_B = scale;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  trans = ScreenParam->trans;
  vct_B = trans;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  y = vct_A.y;
  *x2 = (f32)(vct_A.x + -2048.0) + 256.0;
  *y2 = (f32)((f32)(y + -2048.0) + 112.0) + (f32)((f32)(y + -2048.0) + 112.0);
}

// 0x1cd5da0
static bool Util_GetPadAnalog(sdfVector4_t *p_pad, f32 *p_length, f32 min) {
  f32 AnalogSensitivity;
  s32 v7;
  s32 v8;
  s32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v20;
  f32 v21;
  struct sdfVector4_t vct_A_local;
  f32 v24;
  bool v25;
  u32 AnalogLY;
  s32 v29;
  f32 v30;
  sdfVector4_t *v32;
  bool v33;
  f32 *v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v46;
  f32 v47;
  f32 v49;
  struct sdfVector4_t v52;
  struct sdfVector4_t v53;

  AnalogSensitivity = fldGetAnalogSensitivity();
  if (AnalogSensitivity == INFINITY)
    v7 = 0x80000000;
  else
    v7 = AnalogSensitivity;
  v8 = 128 - v7;
  if (128 - v7 <= dds3PadGetAnalogLX(1))
  {
    v9 = v7 + 128;
    if (v9 < dds3PadGetAnalogLX(1))
      goto LABEL_40;
    if (v8 > dds3PadGetAnalogLY(1))
      goto LABEL_40;
    v10 = 0.0;
    v11 = 0.0;
    if (v9 >= dds3PadGetAnalogLY(1))
    {
LABEL_23:
      goto LABEL_24;
    }
  }
LABEL_40:
  v10 = (f32)dds3PadGetAnalogLX(1) + -128.0;
  AnalogLY = dds3PadGetAnalogLY(1);
  if (v10 > 0.0)
    v29 = 1;
  else
    v29 = -1;
  v30 = (f32)AnalogLY + -128.0;
  v11 = -v30;
  lmapwk->waveFlag = v29;
  goto LABEL_23;
LABEL_24:
  vct_A.x = v10;
  vct_A.y = 0.0;
  vct_A.z = v11;
  vct_A.w = 1.0;
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v20 = (f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z);
  sub_1949110(0);
  v21 = sqrtf(v20);
  vct_A_local = vct_A;
  if (v21 >= min)
  {
    v32 = p_pad;
    v33 = 1;
    goto LABEL_84;
  }
  v52 = vct_A_local;
  v24 = 0.0;
  v25 = CHECK_PRESS2(4100);
  if (v25)
  {
    v24 = 128.0;
    lmapwk->waveFlag = -1;
    if (!CHECK_PRESS2(4101))
    {
LABEL_34:
      if (CHECK_PRESS2(4103))
        goto LABEL_35;
      goto LABEL_65;
    }
  }
  else if (!CHECK_PRESS2(4101))
  {
    goto LABEL_34;
  }
  v24 = -128.0;
  v25 = 1;
  lmapwk->waveFlag = -1;
  if (CHECK_PRESS2(4103))
  {
LABEL_35:
    lmapwk->waveFlag = 1;
    if (!CHECK_PRESS2(4102))
    {
      v21 = 128.0;
      if (v24 == 0.0)
        goto LABEL_73;
      goto LABEL_69;
    }
    goto LABEL_66;
  }
LABEL_65:
  if (!CHECK_PRESS2(4102))
  {
    v21 = 0.0;
    if (!v25)
    {
      vct_A_local = v52;
      v33 = 0;
      v32 = p_pad;
      goto LABEL_84;
    }
    goto LABEL_73;
  }
LABEL_66:
  v21 = -128.0;
  lmapwk->waveFlag = -1;
  if (v24 != 0.0)
  {
LABEL_69:
    v21 = v21 * 0.707;
    v24 = v24 * 0.707;
    lmapwk->waveFlag = -1;
  }
LABEL_73:
  vct_A.x = v21;
  vct_A.y = 0.0;
  vct_A.z = v24;
  vct_A.w = 1.0;
  v41 = &vf00.x;
  v42 = v41[4];
  v43 = v41[5];
  v44 = v41[6];
  v46 = v44 * v44;
  v47 = (f32)(v42 * v42) + (f32)(v43 * v43);
  sub_1949110(0);
  v32 = p_pad;
  v49 = v47 + v46;
  v33 = 1;
  v21 = sqrtf(v49);
  vct_A_local = vct_A;
  v53 = vct_A_local;
  vct_A_local = v53;
LABEL_84:
  *v32 = vct_A_local;
  *p_length = v21;
  return v33;
}

// 0x1cda8c0
static s32 UtilFloatToSdf32s(f32 a_fnum, s32 a_shift) {
  s32 v3;
  f32 v4;
  s32 v5;
  f32 v6;
  s32 v7;

  v3 = a_fnum;
  if (a_fnum == INFINITY)
    v3 = 0x80000000;
  v4 = v3;
  v5 = v3 << a_shift;
  v6 = (f32)(a_fnum - v4) * (f32)(1 << a_shift);
  if (v6 == INFINITY)
    v7 = 0x80000000;
  else
    v7 = v6;
  return v7 + v5;
}

// 0x1cda910
static void Util_GetVerticalVector(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *posp) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v15;
  s64 v16;
  s64 v17;
  f32 *v19;
  int32x2_t v21;
  int32x2_t v22;
  float32x2_t v23;
  float32x2_t v24;
  int32x2_t v26;
  float32x2_t v27;
  int32x2_t v28;
  float32x2_t v29;
  s64 v34;
  s64 v35;

  w = pos1->w;
  z = pos1->z;
  y = pos1->y;
  x = pos1->x;
  v8 = pos0->w;
  v9 = pos0->z;
  v10 = pos0->y;
  v11 = pos0->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v15 = &vf00.x;
  v15[8] = v11;
  v15[9] = v10;
  v15[10] = v9;
  v15[11] = v8;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_C = vct_A;
  v16 = v35;
  v17 = v34;
  *(u64 *)&vct_A.x = v17;
  *(u64 *)&vct_A.z = v16;
  v19 = &vf00.x;
  v19[8] = v11;
  v19[9] = v10;
  v19[10] = v9;
  v19[11] = v8;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_B = vct_A;
  vct_A = vct_C;
  v21.n64_u64[0] = *(u64 *)&vct_A.y;
  v22.n64_u64[0] = *(u64 *)&vct_B.y;
  v23.n64_u32[0] = vdup_lane_s32(v22, 1).n64_u32[0];
  v24.n64_u32[0] = vdup_lane_s32(v21, 1).n64_u32[0];
  v23.n64_u32[1] = LODWORD(vct_B.x);
  v24.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v24.n64_f32[1] * v22.n64_f32[0]) - (f32)(v23.n64_f32[1] * v21.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v21, v23), vmul_f32(v24, v22));
  vct_B = vct_A;
  vct_A = vct_C;
  v26.n64_u64[0] = *(u64 *)&vct_B.y;
  v27.n64_u32[0] = vdup_lane_s32(v26, 1).n64_u32[0];
  v28.n64_u64[0] = *(u64 *)&vct_A.y;
  v29.n64_u32[0] = vdup_lane_s32(v28, 1).n64_u32[0];
  v27.n64_u32[1] = LODWORD(vct_B.x);
  v29.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v29.n64_f32[1] * v26.n64_f32[0]) - (f32)(v27.n64_f32[1] * v28.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v28, v27), vmul_f32(v29, v26));
}

// 0x1cdae90
static void Util_GetVerticalVector2(const sdfVector4_t *vec, const sdfVector4_t *pos0, const sdfVector4_t *posp) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  s64 v15;
  s64 v16;
  f32 *v18;
  int32x2_t v20;
  int32x2_t v21;
  float32x2_t v22;
  float32x2_t v23;
  int32x2_t v25;
  int32x2_t v26;
  float32x2_t v27;
  float32x2_t v28;
  s64 v32;
  s64 v33;

  w = pos0->w;
  z = pos0->z;
  y = pos0->y;
  x = pos0->x;
  v8 = vec->w;
  v9 = vec->z;
  v10 = vec->y;
  v11 = vec->x;
  p_x = &vf00.x;
  p_x[12] = v11;
  p_x[13] = v10;
  p_x[14] = v9;
  p_x[15] = v8;
  v15 = v33;
  v16 = v32;
  *(u64 *)&vct_B.x = v16;
  *(u64 *)&vct_B.z = v15;
  v18 = &vf00.x;
  v18[4] = x;
  v18[5] = y;
  v18[6] = z;
  v18[7] = w;
  vct_B = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_B, (float32x4_t)vct_A);
  vct_A = vct_C;
  v20.n64_u64[0] = *(u64 *)&vct_A.y;
  v21.n64_u64[0] = *(u64 *)&vct_B.y;
  v22.n64_u32[0] = vdup_lane_s32(v21, 1).n64_u32[0];
  v23.n64_u32[0] = vdup_lane_s32(v20, 1).n64_u32[0];
  v22.n64_u32[1] = LODWORD(vct_B.x);
  v23.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v23.n64_f32[1] * v21.n64_f32[0]) - (f32)(v22.n64_f32[1] * v20.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v20, v22), vmul_f32(v23, v21));
  vct_B = vct_A;
  vct_A = vct_C;
  v25.n64_u64[0] = *(u64 *)&vct_B.y;
  v26.n64_u64[0] = *(u64 *)&vct_A.y;
  v27.n64_u32[0] = vdup_lane_s32(v25, 1).n64_u32[0];
  v28.n64_u32[0] = vdup_lane_s32(v26, 1).n64_u32[0];
  v27.n64_u32[1] = LODWORD(vct_B.x);
  v28.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v28.n64_f32[1] * v25.n64_f32[0]) - (f32)(v27.n64_f32[1] * v26.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v26, v27), vmul_f32(v28, v25));
}

// 0x1cd9430
static void Util_GetVerticalPosition(const sdfVector4_t *vec, const sdfVector4_t *pos, f32 length) {
  s64 v4;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v14;
  f32 *p_x;
  f32 veca;
  f32 pos0;
  sdfVector4_t v19;
  sdfVector4_t v20;
  sdfVector4_t v21;

  pos0 = pos->w;
  veca = vec->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v9 = vec->z;
  v10 = vec->y;
  v11 = vec->x;
  v21.w = pos0;
  v20.x = v11;
  v20.y = v10;
  v20.w = veca;
  v20.z = v9;
  v21.x = x;
  v21.y = y;
  v21.z = z;
  *(u64 *)&v19.z = v4;
  Util_GetVerticalVector2(v20, v21, v19);
  sub_1949110(0);
  v14 = length;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v14);
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = y;
  p_x[10] = z;
  p_x[11] = pos0;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
}

// 0x1cd2080
static f32 Util_CalcLength(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *posp) {
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 *p_x;
  s64 v13;
  f32 v16;
  f32 v17;
  float32x2_t v18;
  float32x2_t v19;
  u64 v20;
  f32 z;
  f32 w;
  f32 x;
  f32 y;
  s64 v27;
  s64 v28;
  sdfVector4_t v29;

  z = pos0->z;
  w = pos0->w;
  x = pos0->x;
  y = pos0->y;
  v4 = pos1->y;
  v5 = pos1->x;
  v6 = pos1->w;
  v7 = pos1->z;
  pos1->z = v7;
  pos1->w = v6;
  v8 = pos1->w;
  v9 = v4;
  v10 = pos1->z;
  pos1->z = v10;
  v4 = v9;
  pos1->w = v8;
  v29.x = x;
  v29.y = y;
  pos1->x = v5;
  pos1->y = v4;
  v29.w = w;
  v29.z = z;
  Util_GetVerticalVector(v29, pos1, posp);
  sub_1949110(0);
  vct_C = vct_A;
  p_x = &vf00.x;
  p_x[6] = z;
  p_x[7] = w;
  p_x[4] = x;
  p_x[5] = y;
  v13 = v28;
  *(u64 *)&vct_B.x = v27;
  *(u64 *)&vct_B.z = v13;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_B = vct_C;
  v16 = vct_A.x;
  v17 = vct_B.x;
  v18.n64_u64[0] = *(u64 *)&vct_A.y;
  v19.n64_u64[0] = *(u64 *)&vct_B.y;
  v20 = vmul_f32(v18, v19).n64_u64[0];
  vct_A = vct_C;
  return *((f32 *)&v20 + 1) + (f32)((f32)(v16 * v17) + *(f32 *)&v20);
}

// 0x1cdb2c0
static bool Util_GetMovePosition(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *vec, f32 rate, f32 length) {
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v12;
  s32 v13;
  f32 v14;
  s32 v15;
  f32 *p_x;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 *v21;
  f32 *v22;
  f32 *v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v30;
  f32 v32;
  f32 *v34;
  f32 z;
  f32 w;
  f32 x;
  f32 y;
  f32 v44;
  f32 v45;

  w = pos1->w;
  z = pos1->z;
  v6 = pos0->w;
  x = pos1->x;
  y = pos1->y;
  v7 = pos0->z;
  v8 = pos0->y;
  v9 = pos0->x;
  v12 = rate;
  v13 = *((u32 *)&rate + 1);
  v14 = length;
  v15 = *((u32 *)&length + 1);
  p_x = &vf00.x;
  p_x[4] = v12;
  *((u32 *)p_x + 5) = v13;
  p_x[6] = v14;
  *((u32 *)p_x + 7) = v15;
  sub_1949110(0);
  v18 = v6;
  v19 = v7;
  v20 = v8;
  vct_C = vct_A;
  v21 = &vf00.x;
  v21[4] = x;
  v21[5] = y;
  v21[6] = z;
  v21[7] = w;
  v22 = &vf00.x;
  v22[8] = v9;
  v22[9] = v20;
  v22[10] = v19;
  v22[11] = v18;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v23 = &vf00.x;
  v24 = v23[6];
  v25 = v23[4];
  v26 = v23[5];
  v27 = v45;
  v27 = v45;
  v30 = sqrtf((f32)((f32)(v25 * v25) + (f32)(v26 * v26)) + (f32)(v24 * v24));
  if (v30 <= v27)
  {
    return v30 <= v27;
  }
  sub_1949110(0);
  vct_B = vct_C;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v32 = v44;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v32);
  vct_B = vct_C;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v27 = v45;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v45);
  v34 = &vf00.x;
  v34[8] = v9;
  v34[9] = v20;
  v34[10] = v19;
  v34[11] = v18;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v27 = v45;
  return v30 <= v27;
}

// 0x1cdb9b0
static bool ListMakeListDummy(tagLMAP_LIST_WORK *wk) {
  return 1;
}

// 0x1cdb9c0
static s32 ListDecideStation(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s32 SelectID;
  char *v8;
  char *LocalizeText;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  v4 = ProcessData;
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  HIDWORD(v4[4].monitor) = SelectID;
  itfMenuSetFlagMenu(v4[2].klass, SelectID, 8, 1);
  itfMenuSetFlagMenu(v4[2].klass, HIDWORD(v4[4].monitor), 64, 0);
  itfMenuSetFlag(v4[2].klass, 8, 0);
  Reset(0);
  v8 = strStation[SHIDWORD(v4[4].monitor)];
  LocalizeText = GetLocalizeText(v8, 1);
  fclSetMessageVar(0, LocalizeText);
  fclStart2(2, 0, 0);
  SetMessagePos(0);
  fclSetSelCancelPos(1);
  BYTE3(v4[4].monitor) = 2;
  return 1;
}

// 0x1cdbc10
static void ListDrawStation(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v16;
  s64 naturalAligment;
  dds3ProcessID_t *v18;
  Il2CppObject *v19;
  char *v20;
  s32 v21;
  s32 v22;
  sprHandle_t *v23;
  s32 v24;
  s64 v25;
  s32 v27;
  Il2CppObject *v29;
  char *v30;
  s32 v31;
  s32 data;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  v16 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagLMAP_LIST_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagLMAP_LIST_WORK;
  }
  v18 = ProcessData[4];
  if (itfMenuGetSelectID(ProcessData[4]) == a_id)
  {
    data = *((u32 *)v16 + 21);
    v19 = Box(s32, &data);
    v20 = Format("{0,7}", v19, 0);
    itfDrawMiscFont(4, 357, 32, a_z, 1, 0xA09DC380, a_alphaRate, v20);
    itfCtrlMoney((f32)a_alphaRate / 255.0, v20);
    itfIconDrawSprite(422, 419, 0, a_alphaRate, 13, 109);
  }
  v21 = a_x;
  v22 = a_x + 196;
  v23 = v16[3];
  v24 = a_y - 17;
  itfDrawMiscSpriteAlpha(v22, v24, a_z, a_alphaRate, v23, 49, 109);
  v25 = *((char *)v16 + 73);
  if (evtBitCheck(2570))
  {
    v27 = 0;
    goto LABEL_30;
  }
  v27 = arrRailroadFare[v25][a_id];
LABEL_30:
  v31 = v27;
  v29 = Box(s32, &v31);
  v30 = Format("{0,3}", v29, 0);
  itfDrawMiscFont(3, v21 + 163, v24, a_z, 0, a_fontColor, a_alphaRate, v30);
  itfSetStationListItemFare(a_id, v30);
}

// 0x1cdc0e0
static bool ListChkUseStation(tagLMAP_LIST_WORK *wk) {
  _BOOL4 v5;
  _BOOL4 v7;
  s32 v9;
  _BOOL4 v10;
  s32 v12;
  _BOOL4 v13;
  s32 v15;
  _BOOL4 v16;
  s32 v18;
  _BOOL4 v19;
  s32 v21;

  if (!evtBitCheck(arrStFlag[wk->point]))
    return 0;
  v5 = evtBitCheck(arrStFlag[0]);
  v7 = evtBitCheck(arrStFlag[1]);
  v9 = v5 + v7;
  v10 = evtBitCheck(arrStFlag[2]);
  v12 = v9 + v10;
  v13 = evtBitCheck(arrStFlag[3]);
  v15 = v12 + v13;
  v16 = evtBitCheck(arrStFlag[4]);
  v18 = v15 + v16;
  v19 = evtBitCheck(arrStFlag[5]);
  v21 = v18 + v19;
  return v21 + (u32)evtBitCheck(arrStFlag[6]) > 1;
}

// 0x1cdc2d0
static bool ListMakeListStation(tagLMAP_LIST_WORK *wk) {
  bool v4;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *p_listPID;
  dds3ProcessID_t *listPID;
  s64 v10;
  s32 v11;
  s32 v12;
  dds3ProcessID_t *v15;
  char *v16;
  itfMenuFunc_t v17;
  dds3ProcessID_t *v18;
  itfMenuDrawFunc_t v19;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;
  dds3ProcessID_t *v23;
  dds3ProcessID_t *v24;
  itfMenuCtrlUnity v25;
  bool v27;

  v4 = ListChkUseStation(wk);
  if (!v4)
    return v4;
  v27 = v4;
  v6 = itfMenuProcessStart();
  wk->listPID = v6;
  p_listPID = &wk->listPID;
  itfMenuSetOt(wk->listPID, 109);
  listPID = wk->listPID;
  itfMenuSetMenuTitle(listPID, strSystem[0], "");
  v10 = 0;
  v11 = 0;
  do
  {
    if (evtBitCheck(arrStFlag[v10]) || v10 == wk->point)
    {
      itfSetStationListMenuBarFlag(v11, v10 + 10033);
      v15 = p_listPID;
      v16 = strStation[v10];
      v17 = Allocate(itfMenuFunc_t);
      _ctor(v17, 0, Method_Project_lmap_ListDecideStation__, 0);
      itfMenuSetRootMenu(v15, v10, v16, v17, "");
      v18 = wk->listPID;
      v19 = Allocate(itfMenuDrawFunc_t);
      _ctor(v19, 0, Method_Project_lmap_ListDrawStation__, 0);
      itfMenuSetDrawFunc(v18, v10, v19, 0);
      itfMenuSetFlagMenu(wk->listPID, v10, 128, 1);
      itfMenuSetFlagMenu(wk->listPID, v10, 512, 1);
      if (v10 == wk->point)
      {
        v20 = p_listPID;
        itfMenuSetFlagMenu(v20, v10, 2, 0);
        itfMenuSetInitSelectID(p_listPID, v10);
        v12 = 4;
      }
      else
      {
        v12 = 1;
      }
      itfSetStationListItemState(v11++, v12);
    }
    ++v10;
  }
  while (v10 != 7);
  if (v11 <= 6)
  {
    do
    {
      itfSetStationListItemState(v11++, 0);
    }
    while (v11 != 7);
  }
  v21 = p_listPID;
  itfMenuSetDrawParam(v21, 7, 1);
  itfMenuLinkSprite(wk->listPID, wk->hSpr);
  v23 = wk->listPID;
  itfMenuSetSpriteData(v23, 0, 0, 0, 0, 0, 182, 95, 0, arrSprListTitle);
  itfMenuSetSpriteData(p_listPID, 1, 145, 194, 0, 27, 6, -23, 0, arrSprListPanel);
  itfMenuSetSpriteData(p_listPID, 2, 145, 194, 0, 27, 6, -23, 0, arrSprListSelect);
  itfMenuSetStringSpace(p_listPID, 0, 1);
  itfMenuSetStringWidth(p_listPID, 0, 150);
  itfMenuSetStringStyle(p_listPID, 1, 2);
  itfMenuSetStringStyle(p_listPID, 2, 2);
  v24 = p_listPID;
  v25 = Allocate(itfMenuCtrlUnity);
  _ctor(v25, 0, Method_Project_itf_CtrlStationList__, 0);
  itfMenuSetCtrlFuncForUnity(v24, v25);
  itfSetStationListText();
  lmapStationDestCheckStart();
  return v27;
}

// 0x1cdc840
static bool ListMakeList(tagLMAP_LIST_WORK *wk) {
  ListMakeListFunc_t v4;
  char v5;
  dds3ProcessID_t *listPID;

  v4 = ListMakeListFunc[wk->type];
  v5 = (v4->invoke_impl)(v4->method_code, wk, v4->method);
  if ((v5 & 1) != 0)
  {
    listPID = wk->listPID;
    itfMenuStart(listPID);
  }
  return v5 & 1;
}

// 0x1cdc910
static void ListCallProcEnd(tagLMAP_LIST_WORK *wk) {
  dds3ProcessID_t *listPID;

  listPID = wk->listPID;
  itfMenuProcessEnd(listPID);
  itfCountProcessEnd(wk->countPID);
}

// 0x1cdc990
static s8 ListCheckProcEnd(tagLMAP_LIST_WORK *wk) {
  dds3ProcessID_t *listPID;
  bool v4;
  dds3ProcessID_t *countPID;
  bool v6;
  s8 v7;

  listPID = wk->listPID;
  v4 = itfMenuProcessCheck(listPID);
  countPID = wk->countPID;
  v6 = itfCountProcessCheck(countPID);
  if (v4)
    v7 = 2;
  else
    v7 = 1;
  if (v6)
    return v7;
  else
    return v4;
}

// 0x1cdca40
static dds3ProcessFunc_t ListProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  tagLMAP_LIST_WORK *v6;
  dds3ProcessFunc_t v9;
  void *Instance;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *klass;
  dds3ProcessID_t *v17;
  tagM_LMAP_WORK *v19;
  s32 field_id;
  s32 v21;
  s64 v22;
  s64 monitor_high;
  bool v25;
  s32 ReturnNum00;
  s32 v28;
  dds3ProcessID_t *v30;
  bool v31;
  dds3ProcessID_t *v33;
  dds3ProcessID_t *v34;
  dds3ProcessID_t *v35;
  bool Flag;
  dds3ProcessID_t *v37;
  s8 v38;
  char *v39;
  char *scrLabel;
  dds3Basic_t *p_ActiveScene;
  char *v42;
  scrHandle_t *v43;
  s32 v44;
  s32 v45;
  s64 v47;
  u16 *v49;
  char *v50;
  char *v51;
  char *v52;
  scrHandle_t *v53;
  s32 count;
  s32 v55;
  dds3ProcessID_t *v57;
  dds3ProcessID_t *p_countPID;
  s32 v59;
  dds3ProcessID_t *v60;
  s32 v62;
  s64 v63;
  u16 *v65;
  u32 v66;
  dds3ProcessID_t *v67;
  _BOOL4 v69;
  dds3ProcessID_t *v70;
  s64 v71;
  s64 v75;
  s32 v76;
  dds3ProcessID_t *started;
  dds3ProcessID_t *countPID;
  s32 gold;
  s32 money;
  dds3ProcessID_t *listPID;
  s32 selectID;
  char *v87;
  char *v92;
  dds3Basic_t *v93;
  dds3Basic_t *v94;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *scene;

  scene = 0;
  ActiveScene = 0;
  v93 = 0;
  v94 = 0;
  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  v6 = ProcessData;
  switch (BYTE3(ProcessData[4].monitor))
  {
    case 0:
      set_IsStationListDisp(0, 0);
      set_IsMoneyDisp(0, 0);
      v9 = 0;
      if ((v6->flag & 4) != 0)
      {
        v6->flag &= ~4u;
        v6->money = GBWK->player->gold;
        v6->selectID = -2;
        if (!ListMakeList(v6))
        {
          if (v6->type != 1)
            return 0;
          v87 = "LMP_SYS_CLS_ST";
          v6->scrLabel = "LMP_SYS_CLS_ST";
          lmapwk->sysClsStFlag = 1;
          ActiveScene = dds3GetActiveScene();
          scrLabel = v6->scrLabel;
          p_ActiveScene = &ActiveScene;
          goto LABEL_208;
        }
        lmapwk->sysClsStFlag = 0;
        v6->step = 1;
        Instance = get_Instance(0);
        ItfButtonGuideSet(Instance, 0, 0);
        ButtonGuideDispSet("LMAP02", 0, 90);
        return 0;
      }
      return v9;
    case 1:
      v15 = &ProcessData[2];
      klass = ProcessData[2].klass;
      if (itfMenuProcessCheck(klass))
      {
        v17 = v15;
        itfMenuGetSelectID(v17);
        itfChangeIconNewAll();
        v19 = lmapwk;
        if (!v19)
          return 0;
        v19 = lmapwk;
        field_id = v19->field_id;
        itfChangeMokutekichi(field_id);
        return 0;
      }
      v6->listPID = 0;
      v6->selectID = -1;
      v71 = 0;
      v6->step = 0;
      while (1)
      {
        if (v71 >= SLODWORD(arrStFlag->max_length))
          return 0;
        if (!!evtBitCheck(arrStFlag[v71]))
        {
          if (!evtBitCheck(v71 + 10033))
          {
            itfChangeBitIconNew(v71 + 1);
          }
        }
        ++v71;
      }
    case 2:
      v21 = Update();
      if (v21 == 1)
      {
        listPID = v6->listPID;
        selectID = v6->selectID;
        itfMenuSetFlagMenu(listPID, selectID, 8, 0);
        itfMenuSetFlag(v6->listPID, 8, 1);
        v9 = 0;
        v6->step = 1;
        return v9;
      }
      v9 = 0;
      if (v21)
        return v9;
      if (v6->type == 1)
      {
        v9 = 0;
        v6->step = 3;
        return v9;
      }
      goto LABEL_180;
    case 3:
      v22 = SBYTE1(ProcessData[4].monitor);
      monitor_high = SHIDWORD(ProcessData[4].monitor);
      v25 = evtBitCheck(2570);
      if (!v25)
      {
        v75 = (s64)arrRailroadFare[v22] + 2 * monitor_high;
        v76 = *(s16 *)(v75 + 32);
        if (*(u16 *)(v75 + 32))
        {
          if (GBWK->player->gold)
          {
            started = itfCountProcessStartMoney(v76);
            v6->countPID = started;
            countPID = v6->countPID;
            gold = GBWK->player->gold;
            v6->money = gold;
            itfCountSetData(countPID, gold, 1);
            itfCountSetMin(v6->countPID, v6->money, 0);
            v6->flag &= ~8u;
            if (!datCheckMoney(v76))
            {
              money = v6->money;
              v6->flag |= 8u;
              datDebtFromGouto(v76 - money);
            }
            v9 = 0;
            v6->step = 4;
          }
          else
          {
            v6->flag |= 8u;
            v6->step = 5;
            datDebtFromGouto(v76);
            return 0;
          }
          return v9;
        }
      }
      if (evtBitCheck(2570))
        v6->flag |= 0x10u;
LABEL_180:
      v9 = 0;
LABEL_181:
      v6->step = 5;
      return v9;
    case 4:
      ReturnNum00 = itfGetReturnNum00();
      v28 = ReturnNum00 & ~(ReturnNum00 >> 31);
      v30 = v6->countPID;
      v6->money = v28;
      v31 = itfCountProcessCheck(v30);
      v9 = 0;
      if (v31)
        return v9;
      v6->countPID = 0;
      v9 = 0;
      GBWK->player->gold = v6->money;
      goto LABEL_181;
    case 5:
      v33 = ProcessData[2].klass;
      itfMenuSetFlag(v33, 2048, 1);
      v9 = 0;
      v6->step = 6;
      return v9;
    case 6:
      v35 = &ProcessData[2];
      v34 = ProcessData[2].klass;
      Flag = itfMenuGetFlag(v34, 0x2000u);
      v9 = 0;
      if (!Flag)
        return v9;
      v37 = v35;
      itfMenuProcessEnd(v37);
      v6->listPID = 0;
      v38 = v6->flag;
      if ((v38 & 0x10) != 0)
      {
        v92 = "LMP_SYS_FREE";
        v6->scrLabel = "LMP_SYS_FREE";
        v6->flag = v38 & 0xEF;
        cmpMemCheckRelease();
        v94 = dds3GetActiveScene();
        scrLabel = v6->scrLabel;
        p_ActiveScene = &v94;
      }
      else
      {
        if ((v6->flag & 8) == 0)
        {
LABEL_76:
          v9 = 0;
          v6->step = 8;
          return v9;
        }
        v39 = "LMP_SYS_N_FARE";
        v6->scrLabel = "LMP_SYS_N_FARE";
        v6->flag = v38 & 0xF7;
        cmpMemCheckRelease();
        v93 = dds3GetActiveScene();
        scrLabel = v6->scrLabel;
        p_ActiveScene = &v93;
      }
LABEL_208:
      dds3SceneBasicStartScript(p_ActiveScene, scrLabel);
      v9 = 0;
      v6->step = 7;
      return v9;
    case 7:
      v42 = ProcessData[4].klass;
      v43 = scrSearchScriptName(v42);
      v9 = 0;
      if (!v43)
        goto LABEL_76;
      return v9;
    case 8:
      v44 = datDebtFromGouto(0);
      if (v44 >= 1)
      {
        v45 = v44;
        if (v45 <= GBWK->player->gold)
        {
          v9 = 0;
          v6->step = 9;
          return v9;
        }
      }
      v6->step = 0;
      v47 = 0;
      while (2)
      {
        v49 = arrStFlag;
        if (v47 >= SLODWORD(v49->max_length))
          return 0;
        if (evtBitCheck(v49[v47]))
        {
          if (!evtBitCheck(v47 + 10033))
          {
            itfChangeBitIconNew(v47 + 1);
          }
        }
        ++v47;
        continue;
      }
    case 9:
      v50 = "LMP_SYS_N_FARE2";
      ProcessData[4].klass = "LMP_SYS_N_FARE2";
      scene = dds3GetActiveScene();
      v51 = v6->scrLabel;
      dds3SceneBasicStartScript(scene, v51);
      v9 = 0;
      v6->step = 10;
      return v9;
    case 0xA:
      v52 = ProcessData[4].klass;
      v53 = scrSearchScriptName(v52);
      v9 = 0;
      if (!v53)
      {
        v9 = 0;
        v6->count = 0;
        v6->step = 11;
      }
      return v9;
    case 0xB:
      count = ProcessData[5].klass;
      if (count < 10)
        goto LABEL_186;
      v9 = 0;
      LODWORD(ProcessData[5].klass) = 0;
      BYTE3(ProcessData[4].monitor) = 12;
      return v9;
    case 0xC:
      count = ProcessData[5].klass;
      if (count < 20)
        goto LABEL_186;
      v9 = 0;
      LODWORD(ProcessData[5].klass) = 0;
      BYTE3(ProcessData[4].monitor) = 13;
      return v9;
    case 0xD:
      v55 = datDebtFromGouto(0);
      v6->money = GBWK->player->gold;
      v57 = itfCountProcessStartMoney(v55);
      v6->countPID = v57;
      p_countPID = &v6->countPID;
      itfCountSetData(p_countPID, *((u32 *)p_countPID + 11), 1);
      itfCountSetMin(p_countPID, *((u32 *)p_countPID + 11), 0);
      v9 = 0;
      *((u8 *)p_countPID + 35) = 14;
      return v9;
    case 0xE:
      v59 = itfGetReturnNum00();
      v60 = v6->countPID;
      v6->money = v59;
      v9 = 0;
      if (!itfCountProcessCheck(v60))
      {
        v6->countPID = 0;
        GBWK->player->gold = v6->money;
        v62 = datDebtFromGouto(0);
        datDebtFromGouto(-v62);
        v9 = 0;
        v6->count = 0;
        v6->step = 15;
      }
      return v9;
    case 0xF:
      count = ProcessData[5].klass;
      if (count < 20)
        goto LABEL_186;
      v9 = 0;
      LODWORD(ProcessData[5].klass) = 0;
      BYTE3(ProcessData[4].monitor) = 16;
      return v9;
    case 0x10:
      count = ProcessData[5].klass;
      if (count < 10)
        goto LABEL_186;
      LODWORD(ProcessData[5].klass) = 0;
      v63 = 0;
      BYTE3(ProcessData[4].monitor) = 0;
      while (2)
      {
        v65 = arrStFlag;
        if (v63 >= SLODWORD(v65->max_length))
          return 0;
        if (evtBitCheck(v65[v63]))
        {
          if (!evtBitCheck(v63 + 10033))
          {
            itfChangeBitIconNew(v63 + 1);
          }
        }
        ++v63;
        continue;
      }
    case 0x11:
      if (!LODWORD(ProcessData[5].klass))
      {
        if (!v66)
        ListCallProcEnd(v6);
        goto LABEL_185;
      }
      if (v66)
      {
        goto LABEL_139;
      }
      else
      {
LABEL_139:
        v67 = v6->listPID;
        goto LABEL_140;
      }
      v67 = v6->listPID;
LABEL_140:
      v69 = itfMenuProcessCheck(v67);
      v70 = v6->countPID;
      if (!itfCountProcessCheck(v70) && !v69)
      {
        v9 = 0;
        v6->count = 0;
        v6->step = 18;
        return v9;
      }
LABEL_185:
      count = v6->count;
LABEL_186:
      v9 = 0;
      v6->count = count + 1;
      return v9;
    case 0x12:
      v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v9, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v9;
    default:
      return 0;
  }
}

// 0x1cdda90
static dds3ProcessFunc_t ListDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  s32 v7;
  s64 v8;
  s32 v9;
  sprHandle_t *monitor;
  signed s64 v12;
  Il2CppObject *v14;
  char *v15;
  s32 data;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  v5 = ProcessData;
  v7 = BYTE3(ProcessData[4].monitor);
  if ((u32)(v7 - 11) <= 5)
  {
    if (v7 == 16)
    {
      v12 = 0xFFFFFF99FFFFFF67LL * LODWORD(ProcessData[5].klass);
      v9 = (v12 >> 34) + ((u64)v12 >> 63) + 255;
      monitor = v5[1].monitor;
    }
    else if (v7 == 11)
    {
      v8 = 438086664345LL * LODWORD(ProcessData[5].klass);
      v9 = (v8 >> 34) + ((u64)v8 >> 63);
      monitor = v5[1].monitor;
    }
    else
    {
      v9 = 255;
      monitor = v5[1].monitor;
    }
    itfDrawMiscSpriteList(0, 0, 0, v9, monitor, 109, arrSprListMoney);
    data = HIDWORD(v5[5].klass);
    v14 = Box(s32, &data);
    v15 = Format("{0,7}", v14, 0);
    itfDrawMiscFont(4, 357, 32, 0, 1, 0xA09DC380, v9, v15);
    itfCtrlMoney((f32)v9 / 255.0, v15);
  }
  return 0;
}

// 0x1cddd40
static bool ListLoadSprite(s8 a_str) {
  return a_str != 0;
}

// 0x1ccad70
static bool ListLinkSprite(sprHandle_t *a_hSpr) {
  Il2CppObject *ProcessData;
  void **p_monitor;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  if (!a_hSpr)
    return 0;
  ProcessData[1].monitor = a_hSpr;
  p_monitor = &ProcessData[1].monitor;
  *((u8 *)p_monitor + 50) |= 2u;
  return 1;
}

// 0x1cddd50
static bool ListLinkScriptDat(void *a_pDat) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (!a_pDat)
    return 0;
  ProcessData[3].klass = a_pDat;
  return 1;
}

// 0x1ccb180
static void ListStart(s32 a_type, s32 a_point) {
  char v3;
  char v4;
  Il2CppObject *ProcessData;
  char v9;

  v3 = a_point;
  v4 = a_type;
  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (!BYTE3(ProcessData[4].monitor))
  {
    v9 = BYTE2(ProcessData[4].monitor);
    LOBYTE(ProcessData[4].monitor) = v4;
    BYTE1(ProcessData[4].monitor) = v3;
    BYTE2(ProcessData[4].monitor) = v9 | 4;
  }
}

// 0x1cc8070
static bool ListCheckWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  if (!ProcessData)
    return !BYTE3(ProcessData[4].monitor) && (BYTE2(ProcessData[4].monitor) & 4) == 0;
  return !BYTE3(ProcessData[4].monitor) && (BYTE2(ProcessData[4].monitor) & 4) == 0;
}

// 0x1cc81a0
static s32 ListGetSelectID(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  if (!ProcessData)
    return ProcessData[19];
  return ProcessData[19];
}

// 0x1cdde80
static void ListSetFlagFocus(bool bFocus) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v6;
  s64 naturalAligment;
  dds3ProcessID_t *v8;
  s32 v9;
  bool v10;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  v6 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagLMAP_LIST_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagLMAP_LIST_WORK;
  }
  if (dds3ExistProcess(ProcessData + 4))
  {
    v8 = v6[4];
    v9 = *((u32 *)v6 + 19);
    itfMenuSetFlagMenu(v8, v9, 8, !bFocus);
    v10 = bFocus;
    itfMenuSetFlag(v6[4], 8, v10);
    *((u8 *)v6 + 75) = v10;
  }
}

// 0x1cde000
static void ListSetFlagDisp(bool bDisp) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *v8;
  s32 v9;

  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagLMAP_LIST_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagLMAP_LIST_WORK;
  v7 = ProcessData + 4;
  if (!dds3ExistProcess(ProcessData + 4))
  {
    v8 = v7;
    if (bDisp)
      v9 = 4096;
    else
      v9 = 2048;
    itfMenuSetFlag(v8, v9, 1);
  }
}

// 0x1cdda80
static bool ListChkGetFreePass(void) {
  return evtBitCheck(2570);
}

// 0x1cdc010
static s32 ListGetFare(s32 a_point0, s32 a_point1) {
  if (evtBitCheck(2570))
    return 0;
  return arrRailroadFare[a_point0][a_point1];
}

// 0x1cde190
static s32 ListGetFareJimusyo(s32 a_map) {
  u64 *v3;
  u16 *v4;
  u32 *v5;
  u32 *v6;
  u32 *v7;
  u32 *v8;
  u32 *v9;
  u32 *v10;
  u16 *v11;
  u32 *v12;
  u32 *v13;
  s32 v14;
  u64 *v15;
  s32 result;
  s64 v17;

  v3 = NewSpecific(short__, 0xAu);
  v4 = NewSpecific(s16, 2u);
  v3[4] = v4;
  v4[16] = 1;
  v5 = NewSpecific(s16, 2u);
  v5[8] = 196610;
  v3[5] = v5;
  v6 = NewSpecific(s16, 2u);
  v6[8] = 131075;
  v3[6] = v6;
  v7 = NewSpecific(s16, 2u);
  v7[8] = 262148;
  v3[7] = v7;
  v8 = NewSpecific(s16, 2u);
  v8[8] = 262149;
  v3[8] = v8;
  v9 = NewSpecific(s16, 2u);
  v9[8] = 393222;
  v3[9] = v9;
  v10 = NewSpecific(s16, 2u);
  v10[8] = 327687;
  v3[10] = v10;
  v11 = NewSpecific(s16, 2u);
  v3[11] = v11;
  v11[16] = 8;
  v12 = NewSpecific(s16, 2u);
  v12[8] = 131081;
  v3[12] = v12;
  v13 = NewSpecific(s16, 2u);
  v13[8] = 131087;
  v3[13] = v13;
  v14 = *((u32 *)v3 + 6);
  if (v14 < 1)
    return -1;
  v15 = v3 + 4;
  result = -1;
  while (*(s16 *)(*v15 + 32) != a_map)
  {
    ++v15;
    if (!--v14)
      return result;
  }
  v17 = *(s16 *)(*v15 + 34);
  if (evtBitCheck(2570))
    return 0;
  return arrRailroadFare[v17][0];
}

// 0x1cde4b0
static void ListRelease(tagLMAP_LIST_WORK *wk) {
  sprHandle_t *p_hSpr;
  sprHandle_t *hSpr;

  hSpr = wk->hSpr;
  p_hSpr = &wk->hSpr;
  if (hSpr)
  {
    p_hSpr = 0;
  }
}

// 0x1cde4d0
static void ListShutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void **p_monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *p_g_mainPID_LmpList;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_monitor = &ProcessData[1].monitor;
  if (ProcessData[1].monitor)
  {
    *p_monitor = 0;
  }
  v6 = &ProcessData[1];
  if (dds3ExistProcess(v6))
  {
    dds3KillProcess(v6, 0);
    v6 = 0;
  }
  p_g_mainPID_LmpList = &g_mainPID_LmpList;
  p_g_mainPID_LmpList = 0;
}

// 0x1cde660
static void ListInit(tagLMAP_LIST_WORK *wk) {
  *(u16 *)&wk->flag = 0;
  wk->selectID = -2;
}

// 0x1ccab50
static void ListProcessStart(void) {
  tagLMAP_LIST_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_g_mainPID_LmpList;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;
  tagLMAP_LIST_WORK *p_fields;

  v1 = Allocate(tagLMAP_LIST_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_lmap_ListProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_lmap_ListShutdown__, 0);
  started = dds3StartProcess("lmap_list_main", 1031, 0, 0, v2, v3, v1);
  p_g_mainPID_LmpList = &g_mainPID_LmpList;
  p_g_mainPID_LmpList = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_lmap_ListDrawProcess__, 0);
  v8 = dds3StartProcess("lmap_list_draw", 11031, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
  p_fields = &v1->fields;
  *(u16 *)&p_fields->flag = 0;
  p_fields->selectID = -2;
}

// 0x1cc67b0
static void ListProcessEnd(void) {
  Il2CppObject *ProcessData;
  char v6;

  if (!g_mainPID_LmpList)
    return;
  if (!dds3ExistProcess(g_mainPID_LmpList))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(g_mainPID_LmpList);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  v6 = BYTE2(ProcessData[4].monitor);
  if ((v6 & 1) == 0)
  {
    LODWORD(ProcessData[5].klass) = 0;
    BYTE2(ProcessData[4].monitor) = v6 | 1;
    BYTE3(ProcessData[4].monitor) = 17;
  }
}

// 0x1cde670
static bool ListProcessCheck(void) {
  dds3ProcessID_t *p_g_mainPID_LmpList;

  if (!g_mainPID_LmpList)
    return 0;
  if (dds3GetProcessStat(g_mainPID_LmpList) != 3)
  {
    if (dds3GetProcessStat(g_mainPID_LmpList))
    {
      return 1;
    }
  }
  p_g_mainPID_LmpList = &g_mainPID_LmpList;
  p_g_mainPID_LmpList = 0;
  return 0;
}
