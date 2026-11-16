#pragma once
#include "types.h"
#include "ActionDelegate.h"
#include "CutInType.h"
#include "EVT_PICTURE_TYPE.h"
#include "EVT_UNIT_MOVE_TYPE.h"
#include "MODELTYPE.h"
#include "PMD_FLAG.h"
#include "callbackDelegate.h"

typedef enum {
    EVT_VIEWER_STAT_STOP = 1,
    EVT_VIEWER_STAT_QUAKE = 2,
    EVT_VIEWER_STAT_BLUR = 4,
    EVT_VIEWER_ZIKKI_MODE = 8,
    EVT_VIEWER_SKIP_START = 16,
    EVT_VIEWER_END = 32,
    EVT_VIEWER_NEXT_SEQ = 64,
    EVT_VIEWER_SEQ_END = 128,
    EVT_VIEWER_STAT_MES = 256,
    EVT_VIEWER_STAT_IGNORE_FADE = 512,
    EVT_VIEWER_STAT_NO_SKIPMES = 1024,
    EVT_VIEWER_STAT_IGNORE_AT3PLAY = 2048,
} EVT_VIEWER;

typedef enum {
    EVENT_AT3BGM_FLAG_NONE = 0,
    EVENT_AT3BGM_FLAG_PLAY = 1,
    EVENT_AT3BGM_FLAG_FADEIN = 2,
    EVENT_AT3BGM_FLAG_LOADNOW = 4,
} EVENT_AT3BGM_FLAG;

typedef enum {
    EVT_MOON_STAT_CALC = 1,
    EVT_MOON_STAT_DRAW = 2,
} EVT_MOON_STAT;

typedef enum {
    EVT_PICTURE_FLAG_ON = 1,
    EVT_PICTURE_FLAG_CMD = 2,
    EVT_PICTURE_FLAG_CMD_END = 4,
    EVT_PICTURE_FLAG_END = 8,
    EVT_PICTURE_FLAG_CENTER = 16,
} EVT_PICTURE_FLAG;

typedef enum {
    PMD_DATATYPE_CUTINFO = 0,
    PMD_DATATYPE_NAME = 1,
    PMD_DATATYPE_STAGE = 2,
    PMD_DATATYPE_UNIT = 3,
    PMD_DATATYPE_FRAME = 4,
    PMD_DATATYPE_CAMERA = 5,
    PMD_DATATYPE_MESSAGE = 6,
    PMD_DATATYPE_EFFECT = 7,
    PMD_DATATYPE_EFFECTDATA = 8,
    PMD_DATATYPE_UNITDATA = 9,
    PMD_DATATYPE_F1 = 10,
    PMD_DATATYPE_F2 = 11,
    PMD_DATATYPE_FTB = 12,
    PMD_DATATYPE_SLIGHT = 13,
    PMD_DATATYPE_SFOG = 14,
    PMD_DATATYPE_BLUR2 = 15,
    PMD_DATATYPE_MULTBLUR = 16,
    PMD_DATATYPE_DISTBLUR = 17,
    PMD_DATATYPE_FILTER = 18,
    PMD_DATATYPE_MULTFILTER = 19,
    PMD_DATATYPE_RIPBLUR = 20,
    PMD_DATATYPE_OBJECT = 21,
    PMD_DATATYPE_TMX = 22,
    PMD_DATATYPE_TMXDATA = 23,
    PMD_DATATYPE_HEIKOUBLUR = 24,
    PMD_DATATYPE_RAINDATA = 25,
    PMD_DATATYPE_MAX = 26,
} PMD_DATATYPE;

typedef enum {
    PMD_OBJTYPE_STAGE = 0,
    PMD_OBJTYPE_UNIT = 1,
    PMD_OBJTYPE_CAMERA = 2,
    PMD_OBJTYPE_EFFECT = 3,
    PMD_OBJTYPE_MESSAGE = 4,
    PMD_OBJTYPE_SE = 5,
    PMD_OBJTYPE_FADE = 6,
    PMD_OBJTYPE_QUAKE = 7,
    PMD_OBJTYPE_BLUR = 8,
    PMD_OBJTYPE_LIGHT = 9,
    PMD_OBJTYPE_SLIGHT = 10,
    PMD_OBJTYPE_SFOG = 11,
    PMD_OBJTYPE_SKY = 12,
    PMD_OBJTYPE_BLUR2 = 13,
    PMD_OBJTYPE_MBLUR = 14,
    PMD_OBJTYPE_DBLUR = 15,
    PMD_OBJTYPE_FILTER = 16,
    PMD_OBJTYPE_MFILTER = 17,
    PMD_OBJTYPE_BED = 18,
    PMD_OBJTYPE_BGM = 19,
    PMD_OBJTYPE_MG1 = 20,
    PMD_OBJTYPE_MG2 = 21,
    PMD_OBJTYPE_FB = 22,
    PMD_OBJTYPE_RBLUR = 23,
    PMD_OBJTYPE_TMX = 24,
    PMD_OBJTYPE_RAIN = 25,
    PMD_OBJTYPE_EPL = 26,
    PMD_OBJTYPE_HBLUR = 27,
    PMD_OBJTYPE_PADACT = 28,
    PMD_OBJTYPE_MOVIE = 29,
    PMD_OBJTYPE_TIMEI = 30,
    PMD_OBJTYPE_RENDERTEX = 31,
    PMD_OBJTYPE_BISTA = 32,
    PMD_OBJTYPE_CUTIN = 33,
    PMD_OBJTYPE_SCRBREAK = 34,
    PMD_OBJTYPE_CRSFADE = 35,
    PMD_OBJTYPE_PLTMX = 36,
    PMD_OBJTYPE_MEMO = 37,
    PMD_OBJTYPE_VOICE = 38,
    PMD_OBJTYPE_ACHIEVEMENT = 39,
    PMD_OBJTYPE_MESCLR = 40,
    PMD_OBJTYPE_BGPARTS = 41,
    PMD_OBJTYPE_DOF = 42,
    PMD_OBJTYPE_COMMONSE = 43,
    PMD_OBJTYPE_BG_POS = 44,
    PMD_OBJTYPE_MAX = 45,
    PMD_OBJTYPE_VOID = -1,
} PMD_OBJTYPE;

typedef enum {
    PMD_EFFTYPE_D3P = 0,
    PMD_EFFTYPE_BED = 1,
    PMD_EFFTYPE_MG1 = 2,
    PMD_EFFTYPE_MG2 = 3,
    PMD_EFFTYPE_EPL = 4,
} PMD_EFFTYPE;

typedef enum {
    WHITE_IN = 0,
    WHITE_OUT = 1,
    BLACK_IN = 2,
    BLACK_OUT = 3,
    WHITE_IN_B = 4,
    WHITE_OUT_B = 5,
    BLACK_IN_B = 6,
    BLACK_OUT_B = 7,
    WHITE_IN_2 = 8,
    WHITE_OUT_2 = 9,
} PMD_FADE;

typedef enum {
    DISP_ON = 0,
    DISP_OFF = 1,
    SHADOW_OFF = 2,
    MSHADOW_ON = 3,
    VSHADOW_ON = 4,
    MOTION_CHANGE = 5,
    LOD_SELECT = 6,
    POS_CHANGE = 7,
    MASK_ON = 8,
    MASK_OFF = 9,
} PMD_UNIT;

typedef enum {
    EVT_EXMOT_EXIST = 1,
    EVT_EXMOT_MOTION = 2,
    EVT_EXMOT_WAIT = 4,
    EVT_EXMOT_LOOP = 8,
    EVT_EXMOT_STOP = 16,
    EVT_EXMOT_TIME = 32,
} EVT_EXMOT;

typedef enum {
    FLAG_MOTIONLOOP = 1,
    FLAG_PATHTRACE = 2,
    FLAG_PATHREVERSE = 4,
    FLAG_PATHMANUALROT = 8,
    FLAG_PATHCTRLROT = 16,
    FLAG_WAIT = 32,
    FLAG_AUTOWAIT = 64,
    FLAG_MOTIONCALL = 128,
    FLAG_LIGHTON = 256,
    FLAG_AMBIENTON = 512,
    FLAG_LIGHTDIRON = 1024,
    FLAG_LIGHTRGBINANIME = 2048,
    FLAG_LIGHTRGBOUTANIME = 4096,
    FLAG_LIGHTDIRINANIME = 8192,
    FLAG_LIGHTDIROUTANIME = 16384,
    FLAG_MODELRGBANIME = 32768,
    FLAG_MODELAANIME = 65536,
    FLAG_EXTERNALLIGHT = 131072,
    FLAG_BASICLIGHT = 262144,
    FLAG_BASICLIGHTIN = 524288,
    FLAG_BASICLIGHTOUT = 1048576,
    FLAG_ROTLIMITOFF = 2097152,
    FLAG_AUTOWAIT_2 = 4194304,
    FLAG_MOTENDFRAME = 8388608,
    FLAG_MOVEBUSTUP = 16777216,
    FLAG_TIMESTOP = 33554432,
} FLAG;

typedef enum {
    EVT_UNIT_STAT_WAIT = 0,
    EVT_UNIT_STAT_MOVE = 1,
    EVT_UNIT_STAT_MOTION = 2,
    EVT_UNIT_STAT_ROT = 3,
    EVT_UNIT_STAT_ACTION = 4,
} EVT_UNIT_STAT;

typedef enum {
    EVT_UNIT_TARGET_TYPE_POS = 0,
    EVT_UNIT_TARGET_TYPE_POINT = 1,
    EVT_UNIT_TARGET_TYPE_PATH = 2,
} EVT_UNIT_TARGET_TYPE;

typedef enum {
    EVT_MOT_WAIT = 0,
    EVT_MOT_LOOP = 1,
    EVT_MOT_STOP = 2,
    EVT_MOT_AUTO = 3,
    EVT_MOT_TIME = 4,
} EVT_MOT;

typedef enum {
    STAGE_EVT_RENDERTEX_NOP = 0,
    STAGE_EVT_RENDERTEX_GETTEX = 1,
    STAGE_EVT_RENDERTEX_CAPIMAGE = 3,
    STAGE_EVT_RENDERTEX_IMAGE_LOAD = 4,
    STAGE_EVT_RENDERTEX_DRAW_IMAGE = 5,
} STAGE_EVT_RENDERTEX;

typedef struct DataC DataC;
typedef struct DataS DataS;
typedef struct DataUC DataUC;
typedef struct DepthOfFieldSetting DepthOfFieldSetting;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtBranchInfo_t evtBranchInfo_t;
typedef struct evtFrameInfo_t evtFrameInfo_t;
typedef struct evtMoon_t evtMoon_t;
typedef struct evtPictureProcessData_t evtPictureProcessData_t;
typedef struct evtRenderInfo_t evtRenderInfo_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;
typedef struct evtViewerInfo_t evtViewerInfo_t;
typedef struct evtViewerObject_t evtViewerObject_t;
typedef struct fileHandle_t fileHandle_t;
typedef struct dds3Effect_Blur_t pmdBlur2Table_t;
typedef struct pmdCameraTable_t pmdCameraTable_t;
typedef struct pmdCutInfo_t pmdCutInfo_t;
typedef struct pmdDataInfo_t pmdDataInfo_t;
typedef struct dds3Effect_DistortionBlurParam_t pmdDistBlurTable_t;
typedef struct pmdEffectTable_t pmdEffectTable_t;
typedef struct dds3Effect_Filter_t pmdFilterTable_t;
typedef struct pmdFrameTable_t pmdFrameTable_t;
typedef struct pmdHeader_t pmdHeader_t;
typedef struct dds3Effect_ParallelBlur_t pmdHeikouBlurTable_t;
typedef struct pmdLoadScene pmdLoadScene;
typedef struct dds3Effect_PartialMultiBlurParam_t pmdMultBlurTable_t;
typedef struct dds3Effect_PartialMultiFilterParam_t pmdMultFilterTable_t;
typedef struct pmdNameTable_t pmdNameTable_t;
typedef struct pmdObjectTable_t pmdObjectTable_t;
typedef struct pmdPM1_t pmdPM1_t;
typedef struct pmdPM2_t pmdPM2_t;
typedef struct pmdPM3_t pmdPM3_t;
typedef struct pmdProcessWork_t pmdProcessWork_t;
typedef struct pmdRainDataTable_t pmdRainDataTable_t;
typedef struct dds3Effect_RippleBlurParam_t pmdRipBlurTable_t;
typedef struct pmdSceneFogTable_t pmdSceneFogTable_t;
typedef struct pmdSceneLightTable_t pmdSceneLightTable_t;
typedef struct pmdSeqData_t pmdSeqData_t;
typedef struct pmdSeqTable_t pmdSeqTable_t;
typedef struct pmdStageTable_t pmdStageTable_t;
typedef struct pmdTmxTable_t pmdTmxTable_t;
typedef struct pmdTypeTable_t pmdTypeTable_t;
typedef struct pmdUnitTable_t pmdUnitTable_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdfBinary sdfBinary;
typedef struct sdfIVector4_t sdfIVector4_t;

struct evtRenderInfo_t {
    void *pImage;
    sdfBinary *hImageMem;
    STAGE_EVT_RENDERTEX stage;
    s32 draw;
    s32 alpha;
};

struct evtFrameInfo_t {
    u16 frame;
    u16 length;
    s32 nameindex;
    pmdDataInfo_t *data[8];
    pmdDataInfo_t *work;
    void *p;
    evtFrameInfo_t *next;
    evtFrameInfo_t *prev;
};

struct evtBranchInfo_t {
    s8 branchfilter_count;
    s8 branchfilter_flag;
    s16 var_idx;
};

struct evtViewerInfo_t {
    EVT_VIEWER stat;
    pmdProcessWork_t *workdata;
    s32 totalframe;
    s32 firstframe;
    s32 lastframe;
    s32 nowframe;
    s32 oldframe;
    s32 nametablecnt;
    pmdNameTable_t *nametable[256];
    dds3Basic_t *activecamera;
    dds3Basic_t *freecamera;
    dds3Basic_t *gamecamera;
    s32 objcnt;
    evtViewerObject_t *firstobjinfo;
    evtViewerObject_t *lastobjinfo;
    dds3Basic_t *efftable[127];
    bool framedisp;
    s32 fldfilter;
    dds3ProcessID_t *pid;
    bool drawblur2;
    bool drawmblur;
    bool drawdblur;
    bool drawfilter;
    bool drawmfilter;
    bool drawrblur;
    evtViewerObject_t *framelist_target;
    s32 EventSkipCount;
    evtBranchInfo_t *branch;
    s32 dontskip_messagetime;
    bool drawhblur;
    s32 nowMovieStat;
    s32 MovieStartFrame;
    s32 MovieEndFrame;
    evtRenderInfo_t *renderTexInfo;
    s32 cutVal;
    s32 atlac3_waitime;
    s32 callBgmNo;
    s32 callBgmArray[20];
    EVENT_AT3BGM_FLAG At3BgmFlag;
    s32 At3BgmReqID;
    s32 At3Bgm1stFrame;
    bool At3Bgm1stLoad;
    s32 At3BGMPlaySkip;
    s32 At3BGMStartTime;
    s32 voiceConflictFlag;
    s32 voiceConflictMesno;
    s32 fadeAlpha;
    s32 next_seq;
    s32 last_meswin_mode;
    s32 last_mestype;
    s32 real_movie_last_frame;
    s32 value2;
    s32 useFrameNum;
};

struct evtMoon_t {
    u8 Stat;
    u8 Age;
    s8 TakaraCnt;
    s8 ZeniCnt;
    f32 MoveCnt;
    s8 TakumiCnt;
    s8 TeisatuCnt;
    s8 LoyaltyCnt;
    s8 dmy1[1];
    u32 dmy2;
};

struct evtPictureProcessData_t {
    EVT_PICTURE_FLAG flag;
    EVT_PICTURE_TYPE type;
    s32 GameObjectIdx;
    void *mesh;
    sdfIVector4_t xy;
    sdfIVector4_t uv;
    sdfIVector4_t col;
    sdfIVector4_t ofs_xy;
    s32 start;
    s32 end;
    s32 *p_now;
    s32 now2;
    u32 uid;
    callbackDelegate callback;
    s16 in_timer;
    s16 out_timer;
    s32 draw1st;
    s32 ui_mode;
    s32 drawGouto;
    f32 drawPosOffx;
    f32 drawPosOffy;
    CutInType cutInType;
    f32 disoolvePar;
};

struct DataUC {
    pmdDataInfo_t *b;
};

struct DataC {
    pmdDataInfo_t *b;
};

struct DataS {
    pmdDataInfo_t *b;
};

struct pmdDataInfo_t {
    u8 *data;
    DataUC *uc;
    DataC *c;
    DataS *s;
    void *p;
};

struct pmdHeader_t {
    s8 FileType;
    s8 FileFormat;
    s16 UserID;
    s32 FileSize;
    char *MagicCode;
    s32 ExpandSize;
    s32 TypeTableCount;
    s32 Version;
    s32 Reserve2;
    s32 Reserve3;
};

struct pmdTypeTable_t {
    PMD_DATATYPE Type;
    s32 ItemSize;
    s32 ItemAddress;
    void *Item;
};

struct pmdCutInfo_t {
    s32 FirstFrame;
    s32 LastFrame;
    s32 TotalFrame;
    s32 val;
};

struct pmdNameTable_t {
    char *Name;
};

struct pmdStageTable_t {
    s32 NameIndex;
    s32 FileIndex;
    s32 MajorNum;
    s32 MinorNum;
};

struct pmdUnitTable_t {
    s32 NameIndex;
    s32 FileIndex;
    MODELTYPE MajorNum;
    s32 MinorNum;
    s32 DataOffset;
    s32 DataSize;
    s32 FilePriority;
    s32 Reserve2;
    void *Data;
};

struct pmdFrameTable_t {
    PMD_OBJTYPE ObjectType;
    u16 Frame;
    u16 Length;
    s16 NameIndex;
    s16 Reserve1;
    s16 Reserve2;
    pmdDataInfo_t *Data;
};

struct pmdCameraTable_t {
    s32 NameIndex;
    s32 Reserve1;
    s32 Reserve2;
    s32 Reserve3;
};

struct pmdEffectTable_t {
    s32 NameIndex;
    s32 DataOffset;
    PMD_EFFTYPE Type;
    s32 Reserve2;
    void *Data;
};

struct pmdSceneLightTable_t {
    sdfVector4_t Color[3];
    sdfVector4_t Dir[3];
    sdfVector4_t Ambient;
};

struct pmdSceneFogTable_t {
    f32 Min;
    f32 Max;
    f32 Near;
    f32 Far;
    u32 Color;
    s32 Reserve1;
    s32 Reserve2;
    s32 Reserve3;
};

struct pmdTmxTable_t {
    s32 NameIndex;
    s32 DataOffset;
    s32 Reserve1;
    s32 Reserve2;
};

struct pmdRainDataTable_t {
    s32 r;
    s32 g;
    s32 b;
    s32 a;
    s32 speed;
    s32 blend;
    s32 reserve1;
    s32 reserve2;
    s32 spr_speed[3];
    s32 spr_alpha[3];
    s32 reserve3[2];
};

struct pmdPM1_t {
    fileHandle_t *FileHandle1;
    pmdHeader_t *Header1;
    pmdTypeTable_t *TypeTable1;
    pmdNameTable_t *NameTable1;
    s32 NameCount1;
    pmdStageTable_t *StageTable;
    s32 StageCount;
    void *StageF1;
    void *StageF2;
    sdfBinary *StageTB;
    pmdUnitTable_t *UnitTable;
    s32 UnitCount;
    pmdEffectTable_t *EffectTable;
    s32 EffectCount;
    u8 *MessageData;
    pmdTmxTable_t *TmxTable;
    s32 TmxCount;
};

struct pmdPM2_t {
    fileHandle_t *FileHandle2;
    pmdHeader_t *Header2;
    pmdTypeTable_t *TypeTable2;
    pmdNameTable_t *NameTable2;
    s32 NameCount2;
    pmdCutInfo_t *CutInfo;
    pmdFrameTable_t *FrameTable;
    s32 FrameCount;
    pmdCameraTable_t *CameraTable;
    s32 CameraCount;
    pmdSceneLightTable_t *SLightTable;
    s32 SLightCount;
    pmdSceneFogTable_t *SFogTable;
    s32 SFogCount;
    pmdBlur2Table_t *Blur2Table;
    s32 Blur2Count;
    pmdMultBlurTable_t *MBlurTable;
    s32 MBlurCount;
    pmdDistBlurTable_t *DBlurTable;
    s32 DBlurCount;
    pmdFilterTable_t *FilterTable;
    s32 FilterCount;
    pmdMultFilterTable_t *MFilterTable;
    s32 MFilterCount;
    pmdRipBlurTable_t *RBlurTable;
    s32 RBlurCount;
    pmdHeikouBlurTable_t *HBlurTable;
    s32 HBlurCount;
    pmdObjectTable_t *ObjectTable;
    s32 ObjectCount;
    pmdRainDataTable_t *RainDataTable;
    s32 RainDataCount;
};

struct pmdPM3_t {
    fileHandle_t *FileHandle3;
    pmdHeader_t *Header3;
    pmdTypeTable_t *TypeTable3;
    pmdFrameTable_t *SoundFrameTable;
    s32 SoundFrameCount;
};

struct pmdSeqTable_t {
    pmdSeqData_t *table;
};

struct pmdProcessWork_t {
    PMD_FLAG flag;
    s32 EventNo;
    s32 CutNo;
    s32 NowFrame;
    dds3Basic_t *EffectBasicTable;
    s32 MesHandle;
    s32 now_mesno;
    dds3ProcessID_t *ProcessID;
    u32 PM2SeqCnt;
    u32 PM3SeqCnt;
    s32 SeqNo;
    pmdPM1_t *pm1;
    pmdPM2_t *pm2;
    pmdPM3_t *pm3;
    pmdSeqData_t *pm1data;
    pmdSeqTable_t *pm2data;
    pmdSeqTable_t *pm3data;
    s32 pm2size;
    pmdSeqData_t *pm2work;
    s32 pm3size;
    pmdSeqData_t *pm3work;
    pmdLoadScene *loadScene;
    fileHandle_t *dofTblFileHandle;
    void *dofTbl;
    DepthOfFieldSetting *hokanData;
    fileHandle_t *volumeHandle;
};

struct evtUnitHandle_t {
    u32 NowLightRGB;
    u32 BaseLightRGB;
    u32 TargetLightRGB;
    u32 WorkLightRGB;
    sdfVector4_t NowLightDir;
    sdfVector4_t BaseLightDir;
    sdfVector4_t TargetLightDir;
    sdfVector4_t WorkLightDir;
    u32 NowLightRGB1;
    u32 BaseLightRGB1;
    u32 TargetLightRGB1;
    u32 WorkLightRGB1;
    sdfVector4_t NowLightDir1;
    sdfVector4_t BaseLightDir1;
    sdfVector4_t TargetLightDir1;
    sdfVector4_t WorkLightDir1;
    u32 NowLightRGB2;
    u32 BaseLightRGB2;
    u32 TargetLightRGB2;
    u32 WorkLightRGB2;
    sdfVector4_t NowLightDir2;
    sdfVector4_t BaseLightDir2;
    sdfVector4_t TargetLightDir2;
    sdfVector4_t WorkLightDir2;
    u32 NowAmbientRGB;
    u32 BaseAmbientRGB;
    u32 TargetAmbientRGB;
    u32 WorkAmbientRGB;
    sdfVector4_t NowRim;
    sdfVector4_t BaseModelRGBA;
    sdfVector4_t TargetModelRGBA;
    sdf3DLightParallelPacket_t *PrivateLightPacket;
    sdf3DLightParallelPacket_t *PublicLightPacket;
    sdfVector4_t PosTarget;
    dds3Basic_t *Owner;
    dds3Basic_t *BasicLight;
    dds3Basic_t *BasicLight2;
    dds3ModelHandle_t *Model;
    dds3Basic_t *MoveTarget;
    ActionDelegate Action;
    f32 Sin;
    s32 OutMode;
    dds3PathBasicControl_t *Path;
    f32 PathStep;
    FLAG Flag;
    EVT_UNIT_STAT Stat;
    EVT_UNIT_TARGET_TYPE TargetType;
    EVT_UNIT_MOVE_TYPE MoveType;
    s16 Frame;
    s16 MovePara1;
    s16 MovePara2;
    f32 WaitSpeed;
    s16 WaitMotion;
    s16 WaitBefore;
    s16 WaitSmooth;
    s16 dmy1;
    s16 NowMotion;
    s16 NowBefore;
    s16 NowSmooth;
    s16 MotEndFrame;
    f32 LoopEndTime;
    s16 MoveTimer;
    s16 StopTimer;
    s8 KutiGroup;
    s8 KutiMotion;
    u8 CustomSLightIndex;
    u8 ShadowAlpha;
    f32 ShadowY;
    u32 LookRotFlag;
    f32 LookRotY;
    EVT_EXMOT *ExFlags[12];
    EVT_EXMOT *dmy2[4];
    s16 ExWaitMotion[12];
    s16 ExNowMotion[12];
    s16 ExBefore[12];
    s16 ExSmooth[12];
    s16 ExWaitBefore[12];
    s16 ExNowSmooth[12];
    f32 ExLoopEndTime[12];
    u16 LightRGBAnimeFrame;
    u16 LightDirAnimeFrame;
    u16 ModelRGBAnimeFrame;
    u16 ModelRGBAnimeMaxFrame;
    u16 ModelAAnimeFrame;
    u16 ModelAAnimeMaxFrame;
    u16 BasicLightAnimeFrame;
    u16 BasicLightAnimeMaxFrame;
    f32 YMoveAddValue;
    s16 YMoveFrameMax;
    s16 MapLightUse;
    s32 counter;
    s32 dmy4;
    sdfVector4_t MoveDefPos;
    sdfVector4_t MoveStartPos;
    f32 dissolveAlpha;
    f32 dissolveAlphaMove;
    void *bgmesh;
};
