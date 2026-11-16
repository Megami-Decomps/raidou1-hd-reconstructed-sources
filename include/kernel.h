#pragma once
#include "types.h"

#define HISTORY_SIZE 8
#define LINK_TIME 2
#define STAT_CALLSIGN 1
#define STAT_EXITSIGN 2
#define STAT_RESTORESIGN 4
#define STAT_OVERWRITE 8
#define STAT_CALL_RESTORE 65536
#define HISTORY_RESTORE 1

#define DEBUG_LIST_MAX 32

#define COUNT 2

#define WIDTH 512
#define HEIGHT 448
#define ZMIN 256
#define ZMAX 16711680
#define OX 2048
#define OY 2048
#define NEAR_CLIP 16
#define FAR_CLIP 65536
#define NEAR_CLIP_H 12
#define FAR_CLIP_H 65536
#define FOVY 0.62831855
#define OFFX 28672
#define OFFY 30976
#define WIDTH_HD 1920
#define HEIGHT_HD 1080

#define DEBUG 0
#define MASTER 1
#define FROM_HDD 2

#define REPEAT_TIME_1ST 8
#define REPEAT_TIME 2

typedef enum {
    DDS3_ADMINI_CALL_NEW = 0,
    DDS3_ADMINI_CALL_RESTORE = 1,
} DDS3_ADMINI_CALL;

typedef enum {
    DDS3_DEBUG_LIST_TYPE_EMPTY = 0,
    DDS3_DEBUG_LIST_TYPE_PROCESS = 1,
    DDS3_DEBUG_LIST_TYPE_PROCESS2 = 2,
    DDS3_DEBUG_LIST_TYPE_BOOLEAN = 3,
} DDS3_DEBUG_LIST_TYPE;

typedef enum {
    DDS3_OT_SYS_INIT = 0,
    DDS3_OT_RTEX_INIT = 1,
    DDS3_OT_RTEX_NORMAL = 2,
    DDS3_OT_RTEX_SEMITRANS = 3,
    DDS3_OT_RTEX_ADDTRANS = 4,
    DDS3_OT_RTEX_SUBTRANS = 5,
    DDS3_OT_RTEX_SEMITRANS2 = 6,
    DDS3_OT_BTLHOLE_INIT = 7,
    DDS3_OT_BTLHOLE_NORMAL = 8,
    DDS3_OT_BTLHOLE_SEMITRANS = 9,
    DDS3_OT_BTLHOLE_ADDTRANS = 10,
    DDS3_OT_BTLHOLE_SUBTRANS = 11,
    DDS3_OT_BACK1_INIT = 12,
    DDS3_OT_BACK1_NORMAL = 13,
    DDS3_OT_BACK1_SEMITRANS = 14,
    DDS3_OT_BACK1_ADDTRANS = 15,
    DDS3_OT_BACK1_SUBTRANS = 16,
    DDS3_OT_BACK2_INIT = 17,
    DDS3_OT_BACK2_NORMAL = 18,
    DDS3_OT_BACK2_SEMITRANS = 19,
    DDS3_OT_BACK2_ADDTRANS = 20,
    DDS3_OT_BACK2_SUBTRANS = 21,
    DDS3_OT_BACK3_INIT = 22,
    DDS3_OT_BACK3_NORMAL = 23,
    DDS3_OT_BACK3_SEMITRANS = 24,
    DDS3_OT_BACK3_ADDTRANS = 25,
    DDS3_OT_BACK3_SUBTRANS = 26,
    DDS3_OT_BACK4_INIT = 27,
    DDS3_OT_BACK4_NORMAL = 28,
    DDS3_OT_BACK4_SEMITRANS = 29,
    DDS3_OT_BACK4_ADDTRANS = 30,
    DDS3_OT_BACK4_SUBTRANS = 31,
    DDS3_OT_MIZU_INIT = 32,
    DDS3_OT_MIZU_NORMAL = 33,
    DDS3_OT_MIZU_SEMITRANS = 34,
    DDS3_OT_MIZU_ADDTRANS = 35,
    DDS3_OT_MIZU_SUBTRANS = 36,
    DDS3_OT_MIZU_RESET = 37,
    DDS3_OT_FUNE_Z = 38,
    DDS3_OT_BACKEX_NORMAL = 39,
    DDS3_OT_BLOOD = 40,
    DDS3_OT_3D_INIT = 41,
    DDS3_OT_FLD_NORMAL = 42,
    DDS3_OT_FLD_EX0 = 43,
    DDS3_OT_3D_NORMAL = 44,
    DDS3_OT_MAP_LAY = 45,
    DDS3_OT_FLD_EX1 = 46,
    DDS3_OT_3DALPH_NORMAL = 47,
    DDS3_OT_3D_SEMITRANS = 48,
    DDS3_OT_3DALPH_SEMITRANS = 49,
    DDS3_OT_FLD_SUBTRANS = 50,
    DDS3_OT_FLD_ADDTRANS = 51,
    DDS3_OT_BACK5_INIT = 52,
    DDS3_OT_BACK5_NORMAL = 53,
    DDS3_OT_BACK5_SEMITRANS = 54,
    DDS3_OT_BACK5_ADDTRANS = 55,
    DDS3_OT_BACK5_SUBTRANS = 56,
    DDS3_OT_EFFECT_INIT = 57,
    DDS3_OT_EFFECT_NORMAL = 58,
    DDS3_OT_EFFECT_SEMITRANS = 59,
    DDS3_OT_3D_SEMITRANS_EFF = 60,
    DDS3_OT_3D_SUBTRANS_EFF = 61,
    DDS3_OT_EFFECT_ADDTRANS = 62,
    DDS3_OT_EFFECT_SUBTRANS = 63,
    DDS3_OT_3D_ADDTRANS = 64,
    DDS3_OT_3DALPH_ADDTRANS = 65,
    DDS3_OT_3D_SUBTRANS = 66,
    DDS3_OT_3DALPH_SUBTRANS = 67,
    DDS3_OT_3D_SEMITRANS2 = 68,
    DDS3_OT_FLD_EX3 = 69,
    DDS3_OT_COMB_SEMITRANS_EFF = 70,
    DDS3_OT_COMB_SUBTRANS_EFF = 71,
    DDS3_OT_FLDH_INIT = 72,
    DDS3_OT_FLDH_NORMAL = 73,
    DDS3_OT_FLDH_SEMITRANS = 74,
    DDS3_OT_FLDH_ADDTRANS = 75,
    DDS3_OT_FLDH_SUBTRANS = 76,
    DDS3_OT_FLDH_SEMITRANS2 = 77,
    DDS3_OT_SEFF_INIT = 78,
    DDS3_OT_SEFF_NORMAL = 79,
    DDS3_OT_SEFF_SEMITRANS = 80,
    DDS3_OT_SEFF_ADDTRANS = 81,
    DDS3_OT_SEFF_SUBTRANS = 82,
    DDS3_OT_SEFF_SEMITRANS2 = 83,
    DDS3_OT_PLAYER_INIT = 84,
    DDS3_OT_PLAYER_NORMAL = 85,
    DDS3_OT_PLAYER_SEMITRANS = 86,
    DDS3_OT_PLAYER_ADDTRANS = 87,
    DDS3_OT_PLAYER_SUBTRANS = 88,
    DDS3_OT_PLAYER_SEMITRANS2 = 89,
    DDS3_OT_3DHIGH_INIT = 90,
    DDS3_OT_ENC0 = 91,
    DDS3_OT_3DHIGH_BACK = 92,
    DDS3_OT_3DHIGH_REAR = 93,
    DDS3_OT_3DHIGH_NORMAL = 94,
    DDS3_OT_3DHIGH_SEMITRANS = 95,
    DDS3_OT_3DHIGH_SEMITRANS_EFF = 96,
    DDS3_OT_3DHIGH_SUBTRANS_EFF = 97,
    DDS3_OT_3DHIGH_ADDTRANS = 98,
    DDS3_OT_3DHIGH_SUBTRANS = 99,
    DDS3_OT_3DHIGH_SEMITRANS2 = 100,
    DDS3_OT_3DHIGH_SEMITRANS3 = 101,
    DDS3_OT_BISTA = 102,
    DDS3_OT_MOVIE = 103,
    DDS3_OT_QUAKE = 104,
    DDS3_OT_SCREENCAPTURE = 105,
    DDS3_OT_ENC = 106,
    DDS3_OT_2D_INIT = 107,
    DDS3_OT_2D_LOW = 108,
    DDS3_OT_2D_NORMAL = 109,
    DDS3_OT_2D_HIGH = 110,
    DDS3_OT_2D_HIGH2 = 111,
    DDS3_OT_2D_HIGH3 = 112,
    DDS3_OT_FADE = 113,
    DDS3_OT_2D_INIT2 = 114,
    DDS3_OT_2D_NORMAL2 = 115,
    DDS3_OT_DEBUG_INIT = 116,
    DDS3_OT_DEBUG_NORMAL = 117,
    DDS3_OT_SCREENCAPTURE2 = 118,
    DDS3_OT_MAX = 119,
} DDS3_OT;

typedef enum {
    DDS3_MODEL_OT_3D = 0,
    DDS3_MODEL_OT_3DALPH = 1,
    DDS3_MODEL_OT_BTLHOLE = 2,
    DDS3_MODEL_OT_BACK1 = 3,
    DDS3_MODEL_OT_BACK2 = 4,
    DDS3_MODEL_OT_BACK3 = 5,
    DDS3_MODEL_OT_BACK4 = 6,
    DDS3_MODEL_OT_BACK5 = 7,
    DDS3_MODEL_OT_MIZU = 8,
    DDS3_MODEL_OT_FLDBG = 9,
    DDS3_MODEL_OT_FLDH = 10,
    DDS3_MODEL_OT_PLAYER = 11,
    DDS3_MODEL_OT_EFFECT = 12,
    DDS3_MODEL_OT_AUTOMAP = 13,
    DDS3_MODEL_OT_RTEX = 14,
    DDS3_MODEL_OT_MAX = 15,
} DDS3_MODEL_OT;

typedef enum {
    DDS3_CAM_ID_3DHIGH = 1,
    DDS3_CAM_ID_MAX = 2,
} DDS3_CAM_ID;

typedef enum {
    DDS3_FADEMODE_NORMAL = 0,
    DDS3_FADEMODE_FULL = 1,
} DDS3_FADEMODE;

typedef enum {
    DDS3_FADETYPE_NON = 0,
    DDS3_FADETYPE_FADEIN = 1,
    DDS3_FADETYPE_FADEOUT = 2,
} DDS3_FADETYPE;

typedef enum {
    BISTA_MODE_ALPHA = 0,
    BISTA_MODE_MOVE = 1,
    BISTA_MODE_TALKEVENT = 2,
    BISTA_MODE_FADE = 3,
    BISTA_MODE_ZBCLR = 4,
    BISTA_MODE_TALKEVENT2 = 5,
} BISTA_MODE;

typedef enum {
    FADEINANIME = 1,
    FADEOUTANIME = 2,
    LIGHT0RGBANIME = 4,
    LIGHT0DIRANIME = 8,
    LIGHT1RGBANIME = 16,
    LIGHT1DIRANIME = 32,
    LIGHT2RGBANIME = 64,
    LIGHT2DIRANIME = 128,
    AMBIENTANIME = 256,
    FOGRGBANIME = 512,
    FOGPARAANIME = 1024,
    BLURANIME = 2048,
    MULBLURANIME = 4096,
    DISTBLURANIME = 8192,
    SOFTENBIASANIME = 16384,
    MULBLURSWAP = 32768,
    DISTBLURSWAP = 65536,
    BLUR2ANIME = 131072,
    BLUR2SWAP = 262144,
    FILTER2ANIME = 524288,
    FILTER2SWAP = 1048576,
    MFILTERANIME = 2097152,
    MFILTERSWAP = 4194304,
    RIPBLURANIME = 8388608,
    RIPBLURSWAP = 16777216,
    STOP1 = 33554432,
    BISTAINANIME = 67108864,
    BISTAOUTANIME = 134217728,
    CLEAROFF1 = 268435456,
    QUAKE_GOFF = 536870912,
} DDS3_DRAWFLAG;

typedef enum {
    POSTESP_ON_ANIME = 1,
    POSTESP_OFF_ANIME = 2,
    POSTSLOW_ANIME = 4,
    POSTHITFLASH_ANIME = 8,
} DDS3_DRAWFLAG2;

typedef enum {
    DDS3_PRIORITY_KERNELPROC = 0,
    DDS3_PRIORITY_GLOBALWORK = 1,
    DDS3_PRIORITY_ADMINI = 2,
    DDS3_PRIORITY_FILE_MNG = 900,
    DDS3_PRIORITY_MOVIE_MNG = 901,
    DDS3_PRIORITY_USERPROC = 1000,
    DDS3_PRIORITY_FIELD_DEBUG = 1001,
    DDS3_PRIORITY_FIELD_SCRIPT = 1002,
    DDS3_PRIORITY_EVENT_SCRIPT = 1003,
    DDS3_PRIORITY_EVENT_PACK = 1004,
    DDS3_PRIORITY_CALC_MESMNG_DEBUG = 1005,
    DDS3_PRIORITY_CALC_CAMP_STAT = 1006,
    DDS3_PRIORITY_CALC_CAMP = 1007,
    DDS3_PRIORITY_KILLEVENT = 1008,
    DDS3_PRIORITY_CALLEVENT = 1009,
    DDS3_PRIORITY_CAMPCHECK = 1010,
    DDS3_PRIORITY_FADE = 1011,
    DDS3_PRIORITY_FIELDSEQ = 1012,
    DDS3_PRIORITY_NEW_FIELD_SEQ = 1013,
    DDS3_PRIORITY_BGSEQ = 1014,
    DDS3_PRIORITY_BATTLE_TOP = 1015,
    DDS3_PRIORITY_BATTLE = 1016,
    DDS3_PRIORITY_BATTLEMAIN = 1017,
    DDS3_PRIORITY_BATTLECAMERA = 1018,
    DDS3_PRIORITY_CALC_BASIC = 1019,
    DDS3_PRIORITY_FOLLOWCAMERA = 1020,
    DDS3_PRIORITY_ENCOUNTCHECK = 1021,
    DDS3_PRIORITY_ENCOUNT = 1022,
    DDS3_PRIORITY_CALC_MENU = 1023,
    DDS3_PRIORITY_CALC_COMBINE = 1024,
    DDS3_PRIORITY_CALC_RECOVER = 1025,
    DDS3_PRIORITY_CALC_SHOP = 1026,
    DDS3_PRIORITY_CALC_TERMINAL = 1027,
    DDS3_PRIORITY_CALC_RESULT = 1028,
    DDS3_PRIORITY_CALC_NAME = 1029,
    DDS3_PRIORITY_CALC_JIMUSYO = 1030,
    DDS3_PRIORITY_CALC_TITLE = 1031,
    DDS3_PRIORITY_CALC_MESMNG = 1032,
    DDS3_PRIORITY_SOUND_TEST = 1033,
    DDS3_PRIORITY_EFFECT_TEST = 1034,
    DDS3_PRIORITY_EFFECT_VIEWER = 1035,
    DDS3_PRIORITY_MOVIE = 1036,
    DDS3_PRIORITY_KERNELDRAW = 10000,
    DDS3_PRIORITY_USERDRAW = 11000,
    DDS3_PRIORITY_DEBUG_MENU = 11001,
    DDS3_PRIORITY_DEBUG_OWNER = 11002,
    DDS3_PRIORITY_DRAW_MOVIE = 11003,
    DDS3_PRIORITY_DRAW_MESMNG_DEBUG = 11004,
    DDS3_PRIORITY_MODEL_VIEWER = 11005,
    DDS3_PRIORITY_MODEL_VIEWER_MODE = 11006,
    DDS3_PRIORITY_MODEL_VIEWER_END = 11007,
    DDS3_PRIORITY_MOVIE_VIEWER = 11008,
    DDS3_PRIORITY_DRAW_SNDTEST = 11009,
    DDS3_PRIORITY_DRAW_EFF_F = 11010,
    DDS3_PRIORITY_DRAW_CAMP_STAT = 11011,
    DDS3_PRIORITY_DRAW_CAMP = 11012,
    DDS3_PRIORITY_DRAW_BATTLEK = 11013,
    DDS3_PRIORITY_DRAW_BG = 11014,
    DDS3_PRIORITY_DRAW_BASIC = 11015,
    DDS3_PRIORITY_DRAW_BASICAFTER = 11016,
    DDS3_PRIORITY_DRAW_FIELDPANEL = 11017,
    DDS3_PRIORITY_DRAW_BILLBOARD = 11018,
    DDS3_PRIORITY_DRAW_ENCOUNT = 11019,
    DDS3_PRIORITY_DRAW_BATTLE = 11020,
    DDS3_PRIORITY_DRAW_ENC = 11021,
    DDS3_PRIORITY_DRAW_COMBINE = 11022,
    DDS3_PRIORITY_DRAW_RECOVER = 11023,
    DDS3_PRIORITY_DRAW_SHOP = 11024,
    DDS3_PRIORITY_DRAW_TERMINAL = 11025,
    DDS3_PRIORITY_DRAW_RESULT = 11026,
    DDS3_PRIORITY_DRAW_NAME = 11027,
    DDS3_PRIORITY_DRAW_JIMUSYO = 11028,
    DDS3_PRIORITY_DRAW_MENU = 11029,
    DDS3_PRIORITY_DRAW_EFFECT = 11030,
    DDS3_PRIORITY_DRAW_TITLE = 11031,
    DDS3_PRIORITY_DRAW_MESMNG = 11032,
    DDS3_PRIORITY_SCREENCAPTURE = 11033,
    DDS3_PRIORITY_FONTPACKET = 19999,
    DDS3_PRIORITY_KERNELUPDATE = 20000,
    DDS3_PRIORITY_USERUPDATE = 21000,
    DDS3_PRIORITY_UPDT_CAMP_STAT = 21001,
    DDS3_PRIORITY_UPDT_CAMP = 21002,
    DDS3_PRIORITY_UPDT_COMBINE = 21003,
    DDS3_PRIORITY_UPDT_RECOVER = 21004,
    DDS3_PRIORITY_UPDT_SHOP = 21005,
    DDS3_PRIORITY_UPDT_TERMINAL = 21006,
    DDS3_PRIORITY_UPDT_RESULT = 21007,
    DDS3_PRIORITY_UPDT_NAME = 21008,
    DDS3_PRIORITY_UPDT_JIMUSYO = 21009,
    DDS3_PRIORITY_UPDT_SNDMAN = 21010,
    DDS3_PRIORITY_BUTTON_GUIDE = 21011,
    DDS3_PRIORITY_DEBUGDEVDUMP = 21012,
} DDS3_PRIORITY;

typedef enum {
    DDS3_ADMINI_LIST_DEBUG = 0,
    DDS3_ADMINI_LIST_BOOTMC = 1,
    DDS3_ADMINI_LIST_TITLE = 2,
    DDS3_ADMINI_LIST_LOAD = 3,
    DDS3_ADMINI_LIST_SAVE = 4,
    DDS3_ADMINI_LIST_ENDSAVE = 5,
    DDS3_ADMINI_LIST_EPSAVE = 6,
    DDS3_ADMINI_LIST_FIELD = 7,
    DDS3_ADMINI_LIST_FIELD_MCLOAD = 8,
    DDS3_ADMINI_LIST_EVENT = 9,
    DDS3_ADMINI_LIST_CAMP = 10,
    DDS3_ADMINI_LIST_SHOP = 11,
    DDS3_ADMINI_LIST_RESULT = 12,
    DDS3_ADMINI_LIST_NEWBATTLE = 13,
    DDS3_ADMINI_LIST_STAFF = 14,
    DDS3_ADMINI_LIST_CONFIG = 15,
    DDS3_ADMINI_LIST_MAHJON = 16,
    DDS3_ADMINI_LIST_JIMUSYO = 17,
    DDS3_ADMINI_LIST_NME = 18,
    DDS3_ADMINI_LIST_NEWBATTLE_TEST = 19,
    DDS3_ADMINI_LIST_BATTLEFIELD_TEST = 20,
    DDS3_ADMINI_LIST_EVENT_TEST = 21,
    DDS3_ADMINI_LIST_EVENT_VIEWER = 22,
    DDS3_ADMINI_LIST_INTERFACE_TEST = 23,
    DDS3_ADMINI_LIST_CAMP_TEST = 24,
    DDS3_ADMINI_LIST_SHOP_TEST = 25,
    DDS3_ADMINI_LIST_SAVE_TEST = 26,
    DDS3_ADMINI_LIST_RESULT_TEST = 27,
    DDS3_ADMINI_LIST_MODEL_VIEWER = 28,
    DDS3_ADMINI_LIST_SOUND_TEST = 29,
    DDS3_ADMINI_LIST_FONT_TEST = 30,
    DDS3_ADMINI_LIST_MOVIE_VIEWER = 31,
    DDS3_ADMINI_LIST_SPRITE_MOTION = 32,
    DDS3_ADMINI_LIST_MORPH = 33,
    DDS3_ADMINI_LIST_CITIZEN = 34,
    DDS3_ADMINI_LIST_LMAP = 35,
    DDS3_ADMINI_LIST_NME_TEST = 36,
    DDS3_ADMINI_LIST_SEFF = 37,
    DDS3_ADMINI_LIST_WATER = 38,
    DDS3_ADMINI_LIST_HANAFUDA_TEST = 39,
    DDS3_ADMINI_LIST_GOMADEN = 40,
    DDS3_ADMINI_LIST_JIMUSYO_TEST = 41,
    DDS3_ADMINI_LIST_SSELECT = 42,
    DDS3_ADMINI_LIST_DITECTIVEBOOK = 43,
    DDS3_ADMINI_LIST_MAX = 44,
} DDS3_ADMINI_LIST;

typedef enum {
    UPDATE_DEFEXP = 0,
    UPDATE_LEVELUP = 1,
    UPDATE_NOCALC = 2,
} UPDATE;

typedef enum {
    WINRET_NORMAL = 0,
    WINRET_LOCK_OFF = 1,
    WINRET_LOCK_ON = 2,
} WINRET;

typedef struct Blur2Anime Blur2Anime;
typedef struct DistBlurAnime DistBlurAnime;
typedef struct FIL_t FIL_t;
typedef struct Filter2Anime Filter2Anime;
typedef struct JobData JobData;
typedef struct MFilterAnime MFilterAnime;
typedef struct MeshEdit MeshEdit;
typedef struct MultiBlurAnime MultiBlurAnime;
typedef struct RipBlurAnime RipBlurAnime;
typedef struct SBTLMAIN_DATA SBTLMAIN_DATA;
typedef struct SceneParam_t SceneParam_t;
typedef struct SequenceParameter SequenceParameter;
typedef struct __BTLCAM_QUAKEWORK __BTLCAM_QUAKEWORK;
typedef struct dds3AdminiData_t dds3AdminiData_t;
typedef struct dds3AdminiList_t dds3AdminiList_t;
typedef struct dds3DebugList_t dds3DebugList_t;
typedef struct dds3DrawEnv_t dds3DrawEnv_t;
typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;
typedef struct dds3Effect_DistortionBlurParam_t dds3Effect_DistortionBlurParam_t;
typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;
typedef struct dds3Effect_PartialMultiBlurParam_t dds3Effect_PartialMultiBlurParam_t;
typedef struct dds3Effect_PartialMultiFilterParam_t dds3Effect_PartialMultiFilterParam_t;
typedef struct dds3Effect_RippleBlurParam_t dds3Effect_RippleBlurParam_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct dds3UnitEditData_t dds3UnitEditData_t;
typedef struct dds3UnitEditTable_t dds3UnitEditTable_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdf3DViewportPacket_t sdf3DViewportPacket_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfModelDrawEnv_t sdfModelDrawEnv_t;
typedef struct sprDbgItem_t sprDbgItem_t;
typedef struct sprDbgParamInfo_t sprDbgParamInfo_t;

typedef void (*boolfuncDelegate)(bool b);
typedef void *(*dds3ProcessFunc_t)(dds3ProcessID_t *UnnamedParameter);
typedef dds3ProcessFunc_t (*processfuncDelegate)(dds3ProcessID_t *id);
typedef void (*shutdownfuncDelegate)(dds3ProcessID_t *id);
typedef void (*pInitFuncDelegate)(sprDbgItem_t *UnnamedParameter, void *UnnamedParameter2);

struct sprDbgItem_t {
    char *pItemName;
    u16 ItemNameLen;
    u16 Index;
    sprDbgParamInfo_t *pParamInfo;
    f32 Param;
    s32 ParamColNums;
    sprDbgItem_t *pPrev;
    sprDbgItem_t *pNext;
};

struct sprDbgParamInfo_t {
    s32 Type;
    f32 Min;
    f32 Max;
    f32 Inc;
    f32 Def;
};

struct dds3AdminiData_t {
    u32 Stat;
    u32 RunTimer;
    DDS3_ADMINI_LIST NowSequence;
    DDS3_ADMINI_LIST NextSequence;
    s32 HistoryPointer;
    u8 Reserve1;
    DDS3_ADMINI_LIST *SequenceHistory[8];
    u8 FlagHistory[8];
    SequenceParameter *param;
    s32 CallCount;
};

struct dds3AdminiList_t {
    void *start;
    void *end;
    void *check;
};

struct dds3DebugList_t {
    s32 type;
    char *name;
    dds3ProcessID_t *pid;
    dds3ProcessFunc_t processfunc;
    shutdownfuncDelegate shutdownfunc;
    boolfuncDelegate boolfunc;
    bool b;
    void *data;
    s32 prev;
    s32 next;
};

struct dds3ProcessID_t {
    char *name;
    s32 nameHash;
    u32 flag;
    DDS3_PRIORITY priority;
    u32 starttime;
    u32 runtime;
    s32 id;
    s32 starttimer;
    s32 shutdowntimer;
    dds3ProcessFunc_t processfunc;
    shutdownfuncDelegate shutdownfunc;
    void *workdata;
    dds3ProcessID_t *next;
    dds3ProcessID_t *prev;
    dds3ProcessID_t *parent;
    dds3ProcessID_t *child;
    dds3ProcessID_t *sibling;
};

struct FIL_t {
    sdfVector4_t *rgba;
};

struct Filter2Anime {
    u32 animeFlag;
    u32 swapFlag;
    dds3Effect_Filter_t *_base;
    dds3Effect_Filter_t *_target;
    dds3Effect_Filter_t *_dest;
    s32 _now;
    s32 _max;
    f32 _abase;
    f32 _atarget;
    s32 _swapnow;
    s32 _swapmax;
};

struct MFilterAnime {
    u32 animeFlag;
    u32 swapFlag;
    dds3Effect_PartialMultiFilterParam_t *_base;
    dds3Effect_PartialMultiFilterParam_t *_target;
    dds3Effect_PartialMultiFilterParam_t *_dest;
    s32 _now;
    s32 _max;
    f32 _abase;
    f32 _atarget;
    s32 _swapnow;
    s32 _swapmax;
};

struct Blur2Anime {
    u32 animeFlag;
    u32 swapFlag;
    dds3Effect_Blur_t *_base;
    dds3Effect_Blur_t *_target;
    dds3Effect_Blur_t *_dest;
    s32 _now;
    s32 _max;
    f32 _abase;
    f32 _atarget;
    s32 _swapnow;
    s32 _swapmax;
};

struct MultiBlurAnime {
    u32 animeFlag;
    u32 swapFlag;
    dds3Effect_PartialMultiBlurParam_t *_base;
    dds3Effect_PartialMultiBlurParam_t *_target;
    dds3Effect_PartialMultiBlurParam_t *_dest;
    s32 _now;
    s32 _max;
    f32 _abase;
    f32 _atarget;
    s32 _swapnow;
    s32 _swapmax;
};

struct DistBlurAnime {
    u32 animeFlag;
    u32 swapFlag;
    dds3Effect_DistortionBlurParam_t *_base;
    dds3Effect_DistortionBlurParam_t *_target;
    dds3Effect_DistortionBlurParam_t *_dest;
    s32 _now;
    s32 _max;
    f32 _abase;
    f32 _atarget;
    s32 _swapnow;
    s32 _swapmax;
};

struct RipBlurAnime {
    u32 animeFlag;
    u32 swapFlag;
    dds3Effect_RippleBlurParam_t *_base;
    dds3Effect_RippleBlurParam_t *_target;
    dds3Effect_RippleBlurParam_t *_dest;
    s32 _now;
    s32 _max;
    f32 _abase;
    f32 _atarget;
    s32 _swapnow;
    s32 _swapmax;
};

struct dds3DrawEnv_t {
    sdfDrawTag_t *SysDrawTag;
    sdfModelDrawEnv_t *ModelDrawEnv[15];
    sdfDrawTag_t *DrawTag;
    sdf3DViewportPacket_t *ViewportPacket;
    sdf3DLightParallelPacket_t *DirLightPacket;
    sdfDrawTag_t *HighDrawTag;
    sdf3DViewportPacket_t *HighViewportPacket;
    sdf3DLightParallelPacket_t *HighDirLightPacket;
};

struct __BTLCAM_QUAKEWORK {
    u32 status;
    s32 frame_rate;
    s32 fadein_time;
    s32 fadeout_time;
    sdfVector3_t range;
    s32 frame_cnt;
};

struct dds3UnitEditData_t {
    u32 Flag;
    void *pParentData;
};

struct dds3UnitEditTable_t {
    char *pStr;
    pInitFuncDelegate pInitFunc;
};

struct JobData {
    void *jobHandle;
    bool isAlive;
    MeshEdit *edit;
    void *vertexPCU;
    void *vertexPC;
    void *index;
};

struct SequenceParameter {
    s32 CallData2;
    u32 *CallData3;
    SceneParam_t *CallData4;
    SBTLMAIN_DATA *CallData5;
};
