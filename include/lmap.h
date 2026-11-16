#pragma once
#include "types.h"
#include "MODELTYPE.h"

typedef enum {
    LMAP_CHR_MODEL_MINOR_DEF = 1,
    LMAP_CHR_MODEL_MINOR_KAYA = 80,
    LMAP_CHR_MODEL_MINOR_TRAIN = 5,
    LMAP_CHR_MODEL_MINOR_NPC = 9,
    LMAP_CHR_MODEL_MINOR_SHIP = 10,
    LMAP_CHR_MODEL_MINOR_TAKARA = 18,
    LMAP_CHR_MODEL_MINOR_WARSHIP = 12,
} LMAP_CHR_MODEL_MINOR;

typedef enum {
    M_LMAP_STEP_MAIN_SCENELOAD = 0,
    M_LMAP_STEP_MAIN_INIT = 1,
    M_LMAP_STEP_MAIN_LOAD = 2,
    M_LMAP_STEP_MAIN_LOAD_BGM = 3,
    M_LMAP_STEP_MAIN_LOAD_SMG = 4,
    M_LMAP_STEP_MAIN_FADEIN = 5,
    M_LMAP_STEP_MAIN_MAIN = 6,
    M_LMAP_STEP_MAIN_CAMP_START_WAIT = 7,
    M_LMAP_STEP_MAIN_CAMP = 8,
    M_LMAP_STEP_MAIN_CAMP_END_WAIT = 9,
    M_LMAP_STEP_MAIN_MCLOADWAIT = 10,
    M_LMAP_STEP_MAIN_AUTOMOVE = 11,
    M_LMAP_STEP_MAIN_FADEOUT = 12,
    M_LMAP_STEP_MAIN_END_WAIT = 13,
    M_LMAP_STEP_MAIN_END = 14,
    M_LMAP_STEP_MAIN_LOADING = 15,
    M_LMAP_STEP_MAIN_MENU = 16,
    M_LMAP_STEP_MAIN_FASTTRAVELWAIT = 17,
    M_LMAP_STEP_MAIN_IDOU1 = 18,
    M_LMAP_STEP_MAIN_IDOU2 = 19,
    M_LMAP_STEP_MAIN_IDOUWAIT = 20,
    M_LMAP_STEP_MAIN_DBOOKSTART = 21,
    M_LMAP_STEP_MAIN_DBOOKWAIT = 22,
    M_LMAP_STEP_MAIN_IDOUFCLTY = 23,
    M_LMAP_STEP_MAIN_KINOUYAWAIT = 24,
    M_LMAP_STEP_MAIN_JIMUSYOWAIT = 25,
    M_LMAP_STEP_MAIN_QUICKSAVESTART = 26,
    M_LMAP_STEP_MAIN_QUICKSAVEWAIT = 27,
    M_LMAP_STEP_MAIN_MSGLOGWAIT = 28,
    M_LMAP_STEP_MAIN_SCENELOAD_WAIT = 29,
} M_LMAP_STEP_MAIN;

typedef struct Npc_t Npc_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagLMAP_CAMERA_WORK tagLMAP_CAMERA_WORK;
typedef struct tagLMAP_CHR_UTIL_WORK tagLMAP_CHR_UTIL_WORK;
typedef struct tagLMAP_CHR_WORK tagLMAP_CHR_WORK;
typedef struct tagLMAP_LOCK_WORK tagLMAP_LOCK_WORK;
typedef struct tagLMAP_MSG_WORK tagLMAP_MSG_WORK;
typedef struct tagLMAP_NPC_CB tagLMAP_NPC_CB;
typedef struct tagLMAP_NPC_WORK tagLMAP_NPC_WORK;
typedef struct tagLMP_MODEL_WK tagLMP_MODEL_WK;
typedef struct tagM_LMAP_WORK tagM_LMAP_WORK;

struct tagLMP_MODEL_WK {
    dds3Basic_t *unit;
    f32 ofsY;
    f32 ofsLength;
    f32 scale;
    f32 scaleDef;
    u32 flags;
};

struct tagLMAP_CHR_UTIL_WORK {
    s16 step;
    s16 mode;
    s16 count;
    s16 frame;
};

struct tagLMAP_CHR_WORK {
    sdfVector4_t pos;
    sdfVector4_t pad;
    sdfVector4_t line;
    f32 degree;
    dds3Basic_t *unit;
    f32 scl;
    f32 sclDef;
    tagLMP_MODEL_WK *vehicle;
    s8 charaId;
    s8 charaNo;
    s8 worldId;
    s8 moveId;
    s8 moveId_save;
    s8 moveNo;
    s8 moveStat;
    s16 moveCount;
    s8 moveType;
    bool bDirectAngle;
    bool bMoveAllLine;
    u32 flags;
    f32 length;
    s16 basePointNo;
    s16 nextPointNo;
    s16 lineTableNo;
    s16 portTableNo;
    s16 exLineType;
    MODELTYPE modelMajorNo;
    LMAP_CHR_MODEL_MINOR modelMinorNo;
    tagLMAP_CHR_UTIL_WORK *scale;
    tagLMAP_CHR_UTIL_WORK *route;
    tagLMAP_CHR_UTIL_WORK *autom;
    tagLMAP_CHR_UTIL_WORK *ship;
    s8 taraFlag;
};

struct tagLMAP_LOCK_WORK {
    s16 pointNo[64];
    s16 lineNo[8];
};

struct Npc_t {
    s16 point;
    MODELTYPE id1;
    LMAP_CHR_MODEL_MINOR id2;
    s16 hit;
    f32 scale;
    s16 flag1;
    s16 flag2;
    s16 flag3;
    char *scr_label;
};

struct tagLMAP_NPC_CB {
    tagLMAP_CHR_WORK *chrwk;
    char *scr_label;
    s16 routeNo;
};

struct tagLMAP_NPC_WORK {
    tagLMAP_NPC_CB *cb[65];
};

struct tagLMAP_MSG_WORK {
    s8 step;
    s8 type;
    s16 ret;
};

struct tagLMAP_CAMERA_WORK {
    sdfVector4_t eyePos;
    sdfVector4_t tgtPos;
    sdfVector4_t eyeBasePos;
    sdfVector4_t tgtBasePos;
    sdfVector4_t eyeDir;
    sdfVector4_t tgtDir;
    dds3Basic_t *_object;
};

struct tagM_LMAP_WORK {
    tagLMAP_CHR_WORK *chrwk;
    tagLMAP_NPC_WORK *npcwk;
    dds3ModelHandle_t *hModel_yaso;
    char *pScrLabel;
    tagLMAP_CAMERA_WORK *cam;
    dds3ProcessID_t *drawPID;
    sprHandle_t *hSpr;
    dds3ProcessID_t *proc_actwnd;
    dds3ProcessID_t *proc_effgrid;
    dds3ProcessID_t *proc_effwave;
    Npc_t *pDatNpc;
    u8 flag;
    s8 worldId;
    s8 mapId;
    M_LMAP_STEP_MAIN step_main;
    u8 stepAuto;
    u8 step_debug;
    bool bDrawDebug;
    bool bSetFilter;
    bool bDrawActWin;
    s8 panel_type;
    s8 panel_tblNo;
    s8 area_no;
    s16 fieldNo;
    s16 warpTblNo;
    s32 cnt_moveMap;
    s32 count;
    s32 FlameCnt;
    s32 filterAlpha;
    bool menu_onoff;
    bool guide_onoff;
    s32 field_id;
    tagLMAP_LOCK_WORK *lockwk;
    tagLMAP_MSG_WORK *msgwk;
    s16 TaraSE_RandNo;
    s16 TaraSE_RandNoOld;
    bool TaraSE_Flag;
    s32 TaraSE_time;
    s32 MenuCnt;
    bool mesFlag;
    s32 waveFlag;
    bool loadStart;
    bool msgLogFlag;
    bool sysClsStFlag;
    s32 ScreenSaveW;
    s32 ScreenSaveH;
};

extern f32 LMAP_PAD_ANALOG_MASK;
extern f32 LMAP_CHR_MODEL_DEF_SIZE;
extern f32 LMAP_CHR_AREA_LENGTH;
extern f32 LMAP_CHR_CHARA_LENGTH;
extern f32 LMAP_CHR_ROUTE_MOVE_LENGTH;
extern f32 LMAP_CHR_TRAIN_MOVE_LENGTH;
extern f32 LMAP_CHR_PORT_LENGTH;
extern void *LmapCameraPar;
extern dds3ProcessID_t *fclID;
extern bool CallCampFromLmap;
extern bool CallFastTravelFromLmap;
extern void *lmapJmpDataTbls;
extern tagM_LMAP_WORK *lmapwk;
extern bool MenuFlag;
extern bool TaraCtrlFlag;
extern bool DestUpdateFlag;
extern void *DestOldList;
extern void *DestUpdate;
extern void *DestNowList;
extern void *DestListTbl;
extern void *DestTextList;
extern void *DestNowChapter;
extern u8 CNT;
extern s32 gLMapCampMcLoadEnd;
extern u16 *arrStFlag;
extern char *strSystem;
extern char *strStation;

void lmapLmapDestInit(void *ndwk);
void lmapSetDestCheck(s32 chapter);
void lmapDrawNextDest(void);
void mapIfDestUpdateInit(void);
bool mapIfDestTextUpdateCheck(char *checkText, s32 num);
void mapIfDestUpdateCheck(void);
void mapIfDestUpdateDisplay(void);
bool lmapSetBattleDestFlagCheck(s32 _flag);
void lmapSetBattleDestFlag(s32 no);
void lmapClrBattleDestFlag(s32 no);
void lmapSetBattleDestText(void);
void lmapSetBattleDestDisp(bool disp);
void lmapSetBattleDestRelease(void);
void lmapUI_DispChange(s32 num);
void lmapCheckDestFildData(s32 _filedID);
void lmapSceneInitialize(void);
void lmapResetCampMCLoadEndFlag(void);
s32 lmapCampMCLoadEndCheck(void);
s32 mapIfHajikiCheck(void);
bool lmapProcCheckFlag(void);
s32 lmapProcessCheck(void);
bool lmapCheckCallCampFromLmap(void);
bool lmapCheckCallFastTravelFromLmap(void);
s32 lmapGetPriceFromLmapJmpTbl(s32 jmpID);
sdfVector3_t lmapGetPlayerPosition(void);
void lmapSetIsLoaded(void);
void lmapSetLmapManagerObject(void *go);
void lmapInitFldThumbnailWork(void *s_work);
u8 lmapMapDat_GetMapId(s16 a_pointNo);
