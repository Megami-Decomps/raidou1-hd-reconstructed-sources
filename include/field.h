#pragma once
#include "types.h"

#define SURPRISE_GET_ITEM "DEVIL_REPORT_L0011"
#define SURPRISE_GET_MONEY "DEVIL_REPORT_L0012"
#define SURPRISE_GET_EXP "DEVIL_REPORT_L0013"
#define SURPRISE_GET_LOYALTY "DEVIL_REPORT_L0014"
#define SURPRISE_MAX_ITEM "DEVIL_REPORT_L0015"
#define SURPRISE_MAX_MONEY "DEVIL_REPORT_L0016"

#define c_Key_SurpriseAttackPadSet 57
#define c_Key_SurpriseChangeTarget 8203
#define c_Key_SurpriseAttack 8195

#define MAX_MONEY 9999999
#define MAX_TOTAL_LOLALTY 99999
#define MAX_NAKAMA_LOLALTY 100
#define MAX_LV 99

typedef enum {
    FLD_PROCFLAG_ENCOUNT = 16,
    FLD_PROCFLAG_CAMP = 32,
    FLD_PROCFLAG_UNITPAD = 64,
    FLD_PROCFLAG_MENU = 128,
} FLD_PROCFLAG;

typedef enum {
    FLD_SEQ_INIT = 0,
    FLD_SEQ_BGLOADINIT = 1,
    FLD_SEQ_BGLOADWAIT = 2,
    FLD_SEQ_INIT2 = 3,
    FLD_SEQ_INIT3 = 4,
    FLD_SEQ_TOBISE_LOAD = 5,
    FLD_SEQ_INITALSCRIPTWAIT = 6,
    FLD_SEQ_BGMLOAD = 7,
    FLD_SEQ_BGMLOAD_WAIT = 8,
    FLD_SEQ_SMGLOAD = 9,
    FLD_SEQ_SMGLOAD_WAIT = 10,
    FLD_SEQ_STARTSCR_WAIT = 11,
    FLD_SEQ_AUTOSAVE_INIT = 12,
    FLD_SEQ_AUTOSAVE_WAIT = 13,
    FLD_SEQ_PRIVATE_PROCSTART = 14,
    FLD_SEQ_PRIVATE_PROCWAIT = 15,
    FLD_SEQ_TOBIORI = 16,
    FLD_SEQ_BGM_DPLAY = 17,
    FLD_SEQ_BGM_DPLAY2 = 18,
    FLD_SEQ_NORMAL = 19,
    FLD_SEQ_NORMAL_NAKAMA = 20,
    FLD_SEQ_PRIVATE_PROCEND = 21,
    FLD_SEQ_FADEOUT = 22,
    FLD_SEQ_END = 23,
    FLD_SEQ_AUTOMAPWAIT = 24,
    FLD_SEQ_AUTOMAP = 25,
    FLD_SEQ_CAMP_START_WAIT = 26,
    FLD_SEQ_CAMP = 27,
    FLD_SEQ_CAMP_END_WAIT = 28,
    FLD_SEQ_MCLOADWAIT = 29,
    FLD_SEQ_IDOU1 = 30,
    FLD_SEQ_IDOU2 = 31,
    FLD_SEQ_IDOUWAIT = 32,
    FLD_SEQ_RAIDO_TO_NAKAMA_LOAD = 33,
    FLD_SEQ_NAMAMA_TO_RAIDO_FREE = 34,
    FLD_SEQ_HYUKAWAIT = 35,
    FLD_SEQ_HYUKAWAIT2 = 36,
    FLD_SEQ_MAPCNGWAIT = 37,
    FLD_SEQ_MAPCNGWAIT2 = 38,
    FLD_SEQ_MAPCNGWAIT3 = 39,
    FLD_SEQ_RNDENCWAIT = 40,
    FLD_SEQ_WALLENCWAIT = 41,
    FLD_SEQ_SCRSTARTWAIT = 42,
    FLD_SEQ_SCRSTARTWAIT2 = 43,
    FLD_SEQ_MENUWAIT = 44,
    FLD_SEQ_NAKAMASUMMONWAIT = 45,
    FLD_SEQ_NAKAMARETURNWAIT = 46,
    FLD_SEQ_SEARCHWAIT = 47,
    FLD_SEQ_SPOTWAIT = 48,
    FLD_SEQ_GANKWAIT = 49,
    FLD_SEQ_KOUKWAIT = 50,
    FLD_SEQ_HAKAWAIT = 51,
    FLD_SEQ_HAKAWAIT_EVEHITFADE = 52,
    FLD_SEQ_REIWAIT = 53,
    FLD_SEQ_REIWAIT_EVEHITFADE = 54,
    FLD_SEQ_CHIKARAWAIT = 55,
    FLD_SEQ_CHIKARAWAIT_EVEHITFADE = 56,
    FLD_SEQ_DOKUSINWAIT = 57,
    FLD_SEQ_DOKUSINWAIT_EVEHITFADE = 58,
    FLD_SEQ_IROWAIT = 59,
    FLD_SEQ_IROWAIT_EVEHITFADE = 60,
    FLD_SEQ_HIKOUWAIT = 61,
    FLD_SEQ_HIKOUWAIT_EVEHITFADE = 62,
    FLD_SEQ_SINNWAIT = 63,
    FLD_SEQ_SINNWAIT_EVEHITFADE = 64,
    FLD_SEQ_ZENIWAIT = 65,
    FLD_SEQ_HIROWAIT = 66,
    FLD_SEQ_TAKUMIWAIT = 67,
    FLD_SEQ_HAJIKI1WAIT = 68,
    FLD_SEQ_HAJIKI1WAIT2 = 69,
    FLD_SEQ_HAJIKI1WAIT3 = 70,
    FLD_SEQ_KINOUYAWAIT = 71,
    FLD_SEQ_MILKWAIT = 72,
    FLD_SEQ_JIMUSYOWAIT = 73,
    FLD_SEQ_FASTTRAVELWAIT = 74,
    FLD_SEQ_ENCOUNT_WAIT = 75,
    FLD_SEQ_INVMEMOWAIT = 76,
    FLD_SEQ_IDOUFCLTY = 77,
    FLD_SEQ_AUTOSAVE_BEFORE = 78,
    FLD_SEQ_TORAIDOU_SEL = 79,
    FLD_SEQ_TORAIDOU_INI = 80,
    FLD_SEQ_TORAIDOU_SET = 81,
    FLD_SEQ_TORAIDOU_WAIT = 82,
    FLD_SEQ_INIT4 = 83,
    FLD_SEQ_ENEMY_LOADSTART = 84,
    FLD_SEQ_ENEMY_LOADWAIT = 85,
    FLD_SEQ_EVEHIT_PROC_END = 86,
    FLD_SEQ_RESULT_START_WAIT = 87,
    FLD_SEQ_RESULT = 88,
    FLD_SEQ_RESULT_END_WAIT = 89,
    FLD_SEQ_MSG_LOG_WAIT = 90,
    FLD_SEQ_MSG_LOG_END = 91,
    FLD_SEQ_QUICKSAVE_WAIT = 92,
    FLD_SEQ_RELEASE_WAIT1 = 93,
    FLD_SEQ_RELEASE_WAIT2 = 94,
    FLD_SEQ_MAX = 95,
} FLD_SEQ;

typedef enum {
    FLD_MOTION_TYPE_TRANS = 0,
    FLD_MOTION_TYPE_ROT = 1,
    FLD_MOTION_TYPE_ROT_QTN = 2,
    FLD_MOTION_TYPE_SCALE = 3,
    FLD_MOTION_TYPE_CAMERA = 4,
    FLD_MOTION_TYPE_EVENT_LIGHT = 5,
    FLD_MOTION_TYPE_NO_USE = 4294967295,
} FLD_MOTION_TYPE;

typedef enum {
    FLD_LIGHT_USE_SCENELIGHT = 0,
    FLD_LIGHT_RESERVE1 = 1,
    FLD_LIGHT_RESERVE2 = 2,
} FLD_LIGHT;

typedef enum {
    FLD_RES_PORTAL = 0,
    FLD_RES_BLOCK_RANGE = 1,
    FLD_RES_DRAW_OBJ = 2,
    FLD_RES_COL_OBJ = 3,
    FLD_RES_CAMERA = 4,
    FLD_RES_TEXLIST = 5,
    FLD_RES_EVENT = 6,
    FLD_RES_RENGE = 7,
    FLD_RES_MATERIAL = 8,
    FLD_RES_MOTION = 9,
    FLD_RES_POSITION = 10,
    FLD_RES_EFFECT = 11,
    FLD_RES_LIGHT = 12,
} FLD_RES;

typedef enum {
    FLD_HAITI_TYPE_PUB_VERTEX = 0,
    FLD_HAITI_TYPE_EVENTHIT = 1,
    FLD_HAITI_TYPE_NPC = 2,
    FLD_HAITI_TYPE_TAKARABAKO = 3,
    FLD_HAITI_TYPE_SAVE_POINT = 4,
    FLD_HAITI_TYPE_3DCURSOL = 5,
    FLD_HAITI_TYPE_LIGHT = 6,
    FLD_HAITI_TYPE_ENV_SE = 7,
    FLD_HAITI_TYPE_HANYOU = 8,
} FLD_HAITI_TYPE;

typedef enum {
    BOX_TYPE_ITEM = 0,
    BOX_TYPE_DEVL = 1,
    BOX_TYPE_YEN_ = 2,
    BOX_TYPE_PIKA = 3,
    BOX_TYPE_PYEN = 4,
} BOX_TYPE;

typedef enum {
    BOX_TRAP_NORMAL = 0,
    BOX_TRAP_DAMAGE1 = 1,
    BOX_TRAP_DAMAGE2 = 2,
    BOX_TRAP_DAMAGE3 = 3,
    BOX_TRAP_DAMAGE4 = 4,
    BOX_TRAP_DAMAGE5 = 5,
    BOX_TRAP_ETC = 6,
} BOX_TRAP;

typedef enum {
    FLD_SEQFLAG_BUSY = 1,
    FLD_SEQFLAG_EXIT = 2,
} FLD_SEQFLAG;

typedef enum {
    SL_EXITMODE_CANCEL = 0,
    SL_EXITMODE_SAVE = 1,
    SL_EXITMODE_LOAD = 2,
} SL_EXITMODE;

typedef enum {
    ePrefab_TargetRing_Normal = 0,
    ePrefab_TargetRing_Yellow = 1,
    ePrefab_TargetRing_Red = 2,
    ePrefab_Exclamation = 3,
    ePrefab_Question = 4,
    ePrefab_TargetRing_TBox = 5,
    ePrefab_EnemyTarget = 6,
    ePrefab_SummonEnemy = 7,
    ePrefab_ReturnNakama = 8,
    ePrefab_AttackNakama = 9,
    ePrefab_MAX = 10,
} ePrefab;

typedef enum {
    eFieldState_None = 0,
    eFieldState_Loading = 1,
    eFieldState_Loaded = 2,
    eFieldState_Idle = 3,
    eFieldState_FieldResult = 4,
    eFieldState_BattleStart_PlayingProd = 5,
    eFieldState_BattleStart_End = 6,
    eFieldState_BattleEnd_PlayingProd = 7,
    eFieldState_BattleEnd_End = 8,
    eFieldState_MAX = 9,
} eFieldState;

typedef enum {
    Supprise = 0,
} eFieldPlayerMotion;

typedef enum {
    eFieldCharaFadeType_System = 0,
    eFieldCharaFadeType_Game = 1,
    eFieldCharaFadeType_CamFade = 2,
    eFieldCharaFadeType_PopDelete = 3,
    eFieldCharaFadeType_MAX = 4,
} eFieldCharaFadeType;

typedef enum {
    eFieldClearUIMode_Normal = 0,
    eFieldClearUIMode_OpenCamp = 1,
} eFieldClearUIMode;

typedef enum {
    eFieldSurpriseTargetStatus_None = 0,
    eFieldSurpriseTargetStatus_VisibleRing = 1,
    eFieldSurpriseTargetStatus_EnableTarget = 2,
} eFieldSurpriseTargetStatus;

typedef enum {
    eMapObjType_SavePoint = 0,
    eMapObjType_TBox = 1,
    eMapObjType_MAX = 2,
} eMapObjType;

typedef enum {
    eOuterScreenDir_InScreen = 0,
    eOuterScreenDir_Left = 1,
    eOuterScreenDir_Right = 2,
    eOuterScreenDir_Up = 3,
    eOuterScreenDir_Down = 4,
} eOuterScreenDir;

typedef enum {
    eReqFadeType_None = 0,
    eReqFadeType_FadeIn = 1,
    eReqFadeType_FadeOut = 2,
} eReqFadeType;

typedef enum {
    eTargetIconState_Invisible = 0,
    eTargetIconState_Visible = 1,
    eTargetIconState_Change = 2,
    eTargetIconState_MAX = 3,
} eTargetIconState;

typedef enum {
    eOneShotType_ReturnNakama = 0,
    eOneShotType_SummonEnemy = 1,
    eOneShotType_AttackNakama = 2,
} eOneShotType;

typedef enum {
    eType_Blue = 0,
    eType_Yellow = 1,
    eType_Red = 2,
    eType_TBox = 3,
    eType_MAX = 4,
} eType;

typedef enum {
    eVisibleStatus_Invisible = 0,
    eVisibleStatus_FadeOut = 1,
    eVisibleStatus_FadeIn = 2,
    eVisibleStatus_Visible = 3,
} eVisibleStatus;

typedef enum {
    AtlFieldUI_EnemyTarget_eState_Visible = 1,
    AtlFieldUI_EnemyTarget_eState_Invisible = 2,
} AtlFieldUI_EnemyTarget_eState;

typedef struct AtlFieldHUD_EnemyTarget AtlFieldHUD_EnemyTarget;
typedef struct AtlFieldHUD_Simple3D AtlFieldHUD_Simple3D;
typedef struct AtlFieldHUD_TargetRing AtlFieldHUD_TargetRing;
typedef struct AtlFieldPlayerMotionConst_Data AtlFieldPlayerMotionConst_Data;
typedef struct AtlHUDPrefabPoolConst_Data AtlHUDPrefabPoolConst_Data;
typedef struct FadeData FadeData;
typedef struct GameFileInfo_t GameFileInfo_t;
typedef struct Obj3D Obj3D;
typedef struct Prefab Prefab;
typedef struct RingObj RingObj;
typedef struct SaveTimeInfo_t SaveTimeInfo_t;
typedef struct TargetObj TargetObj;
typedef struct dds3AdditionWork_t dds3AdditionWork_t;
typedef struct dds3SystemWork_t dds3SystemWork_t;
typedef struct fldConstructAreaFL2_t fldConstructAreaFL2_t;
typedef struct fldConstruntObject_t fldConstruntObject_t;
typedef struct fldFileAreaDataFL1_t fldFileAreaDataFL1_t;
typedef struct fldFileAreaDataFL2_t fldFileAreaDataFL2_t;
typedef struct fldFileHeader_t fldFileHeader_t;
typedef struct fldFileInfoHeaderFL1_t fldFileInfoHeaderFL1_t;
typedef struct fldFileInfoHeaderFL2_t fldFileInfoHeaderFL2_t;
typedef struct fldResCam_t fldResCam_t;
typedef struct fldResEvent_t fldResEvent_t;
typedef struct fldResHeadAreaName_t fldResHeadAreaName_t;
typedef struct fldResourcePoint_t fldResHeadPos_t;
typedef struct fldResHead_t fldResHead_t;
typedef struct fldResModel_t fldResModel_t;
typedef struct fldResPut_t fldResPut_t;
typedef struct fldResourceEffect_t fldResourceEffect_t;
typedef struct fldResourceLightPath_t fldResourceLightPath_t;
typedef struct fldResourceLight_t fldResourceLight_t;
typedef struct fldResourcePathData_t fldResourcePathData_t;
typedef struct fldResourcePathTable_t fldResourcePathTable_t;
typedef struct fldResourcePoint_t fldResourcePoint_t;
typedef struct fldResourceTypeTable_t fldResourceTypeTable_t;
typedef struct sdfModelDef_t sdfModelDef_t;
typedef struct sdfMotionPlayBook_t sdfMotionPlayBook_t;

struct GameFileInfo_t {
    u8 verstr[3];
    u8 ver;
    u8 TmnlMode;
    u8 TmnlId;
    u8 Mode;
    u8 Lv;
    u32 PlayTime;
    u16 endcnt;
    u16 newfile;
    u8 cname_code[16];
    u8 cname_nums;
    u8 chapter;
    u16 trial_save;
    u8 pad2[12];
    u8 pad3[16];
    char *player_first;
    char *player_family;
    s16 fieldID;
    s16 floorID;
    s16 basyoID;
    SaveTimeInfo_t *saveTime;
    s32 nameLang;
};

struct SaveTimeInfo_t {
    s32 Year;
    s32 Month;
    s32 Day;
    s32 Hour;
    s32 Minute;
    s32 Second;
};

struct dds3AdditionWork_t {
    s32 FieldID;
    s32 FloorID;
    s32 PointID;
    sdfVector4_t playerPos;
    sdfVector4_t playerRot;
    sdfVector4_t aiboPos;
    sdfVector4_t aiboRot;
    sdfVector4_t campos;
    f32 CamKakudo;
    f32 CamKakudoY;
    f32 CamKakudoGoal;
    s32 nakamaMode;
    f32 raidoX;
    f32 raidoY;
    f32 raidoZ;
    s32 raidoMap;
    s32 raidoFloor;
    f32 raidoKakudo;
    f32 aiboX;
    f32 aiboY;
    f32 aiboZ;
    s32 aiboMap;
    s32 aiboFloor;
    f32 aiboKakudo;
    s32 NakamaLastMap;
    s32 NakamaLastFloor;
    s8 charaId;
    s8 charaNo;
    s8 worldId;
    s8 moveId;
    s8 moveNo;
    bool bDirectAngle;
    bool bMoveAllLine;
    u32 flags;
    sdfVector4_t pos;
    f32 sclDef;
    s16 basePointNo;
    s16 portTableNo;
    s16 nextPointNo;
    s16 lineTableNo;
    sdfVector4_t line;
    s8 taraFlag;
    s32 BgmId;
    s32 SeId;
    f32 PlayerKakudo;
    s32 CutID;
    s32 saveCutID[10];
    f32 nakamaX;
    f32 nakamaY;
    f32 nakamaZ;
    s32 nakamaMap;
    s32 nakamaFloor;
    f32 nakamaKakudo;
    s8 dummy[866];
};

struct dds3SystemWork_t {
    s8 dummy2[8];
    u8 cmbCnt;
    u8 letterCnt;
    u8 sakemeCnt;
    u16 combSkillCnt;
    u8 huumaCnt;
    u8 setumaCnt;
    u16 devilKillCnt;
    u8 titleFlg;
    u8 trialTipsFlg;
    s8 trophyUnlock[7];
    s8 dlcflg[16];
    u16 pd_ver;
    u16 kb_ver;
    s8 dummy[42];
    s32 buy_item[768];
    s32 config_data_audio[256];
    s32 config_data_game[256];
    s32 config_data_graphics[256];
    s32 config_data_display[256];
    s32 config_data_gamepad[256];
    s32 config_data_keyboard[256];
};

struct fldResourceEffect_t {
    u32 flag;
    u32 type;
    u32 noEffect;
    f32 size[3];
    u32 offsetZ;
    u32 groupID;
    u32 param0;
    u32 param1;
};

struct fldResEvent_t {
    char *label;
};

struct fldResPut_t {
    FLD_HAITI_TYPE Type;
};

struct fldResourceLightPath_t {
    f32 InsideR;
    f32 OutsideR;
    f32 Soften;
    f32 Bias;
    f32 DiffuseR;
    f32 DiffuseG;
    f32 DiffuseB;
    f32 AmbientR;
    f32 AmbientG;
    f32 AmbientB;
};

struct fldResourceLight_t {
    u32 resv;
    u32 Flag;
    u32 AnimeType;
    f32 InsideR;
    f32 OutsideR;
    f32 Soften;
    f32 Bias;
    f32 DiffuseR;
    f32 DiffuseG;
    f32 DiffuseB;
    f32 AmbientR;
    f32 AmbientG;
    f32 AmbientB;
};

struct fldResModel_t {
    u32 Flag;
    u32 nLod;
    sdfModelDef_t *pMdl;
    sdfMotionPlayBook_t *pMot;
};

struct fldResourcePathData_t {
    u32 *pKey;
};

struct fldResourcePathTable_t {
    FLD_MOTION_TYPE type;
    fldResourcePathData_t *pData;
};

struct fldResourcePoint_t {
    sdfVector4_t pos;
    sdfVector4_t rot;
    sdfVector4_t scl;
};

struct fldResCam_t {
    f32 fovy;
};

struct fldResHeadAreaName_t {
    u32 num;
    char *name;
};

struct fldResHead_t {
    u32 resourceID;
    FLD_RES resourceType;
    char *resourceName;
    fldResHeadPos_t *sisei;
    fldResHeadAreaName_t *areaname;
    void *pData;
};

struct fldResourceTypeTable_t {
    FLD_RES type;
    fldResHead_t *pResourceDataTable;
};

struct fldConstruntObject_t {
    u32 type;
    u32 objectID;
    u32 attachAreaID;
    u32 parentObjectID;
    u32 resourceID[2];
    u32 padd[2];
    sdfVector4_t pos;
    sdfVector4_t quat;
    sdfVector4_t scl;
};

struct fldFileAreaDataFL1_t {
    u32 fileID;
    u32 SkyTblIdx;
    char *filename0;
    char *filename1;
    char *filename2;
    char *filename3;
};

struct fldFileAreaDataFL2_t {
    u32 fileID;
    char *label;
};

struct fldFileInfoHeaderFL1_t {
    fldResourceTypeTable_t *pResourceTypeTable;
    fldFileAreaDataFL1_t *pAreaData;
    char *loadScene;
};

struct fldFileInfoHeaderFL2_t {
    fldResourceTypeTable_t *pResourceTypeTable;
    fldFileAreaDataFL2_t *pAreaData;
    fldConstructAreaFL2_t *pAreaTable;
};

struct fldFileHeader_t {
    u32 Version;
    char *MagCode;
};

struct Prefab {
    ePrefab m_Type;
};

struct AtlFieldPlayerMotionConst_Data {
    eFieldPlayerMotion m_MotID;
    s32 m_RawID;
    bool m_IsLoop;
};

struct AtlHUDPrefabPoolConst_Data {
    ePrefab m_Prefab;
    s32 m_PoolCount;
};

struct FadeData {
    f32 m_Alpha;
    f32 m_TargetAlpha;
    f32 m_Time;
    f32 m_Speed;
    bool m_IsPlaying;
};

struct TargetObj {
    s32 m_PrefabType;
};

struct AtlFieldHUD_EnemyTarget {
    sdfVector3_t m_ParentPos;
    sdfQuaternion_t m_ParentRotate;
    sdfVector3_t m_Offset;
    f32 m_Size;
    TargetObj *m_Obj;
    bool m_IsActive;
    s32 m_UniqueID;
};

struct Obj3D {
    s32 m_PrefabType;
    bool m_IsParent3D;
};

struct AtlFieldHUD_Simple3D {
    sdfVector3_t m_ParentPos;
    sdfQuaternion_t m_ParentRotate;
    sdfVector3_t m_Offset;
    f32 m_Size;
    Obj3D *m_Obj;
};

struct RingObj {
    s32 m_PrefabType;
    void *m_PRendererMaterials;
};

struct AtlFieldHUD_TargetRing {
    sdfVector3_t m_ParentPos;
    sdfQuaternion_t m_ParentRotate;
    sdfVector3_t m_Offset;
    f32 m_Size;
    RingObj *m_RingObjs[4];
    eType m_Type;
    bool m_IsActive;
    f32 m_FadeTime;
    eVisibleStatus m_VisibleSt;
    eVisibleStatus m_ReqVisibleSt;
};
