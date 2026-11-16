#pragma once
#include "types.h"
#include "ATR.h"
#include "CmbBackStatus.h"
#include "CombStSeq.h"
#include "GOH_KARTE_SORTMODE.h"
#include "GOH_RESULT_TYPE.h"
#include "ITM.h"
#include "TreeType.h"

typedef enum {
    GOH_COMBINE_TYPE_NON = 0,
    GOH_COMBINE_TYPE_NORMAL = 1,
    GOH_COMBINE_TYPE_SWORD = 2,
    GOH_COMBINE_TYPE_BACK = 3,
    GOH_COMBINE_TYPE_COMBI = 4,
} GOH_COMBINE_TYPE;

typedef enum {
    SklSearchiType_None = -1,
    SklSearchiType_Buturi = 0,
    SklSearchiType_Kaen = 1,
    SklSearchiType_Hyoketu = 2,
    SklSearchiType_Dengeki = 3,
    SklSearchiType_Shogeki = 4,
    SklSearchiType_Jyusatu = 5,
    SklSearchiType_Seisin = 6,
    SklSearchiType_Hojo = 7,
    SklSearchiType_Recovery = 8,
    SklSearchiType_Omoide = 9,
    SklSearchiType_Sousa = 10,
    SklSearchiType_Max = 11,
} SklSearchiType;

typedef enum {
    GOH_STAT_TYPE_1 = 0,
    GOH_STAT_TYPE_2 = 1,
    GOH_STAT_TYPE_BIRTH = 2,
    GOH_STAT_TYPE_RESULT = 3,
    GOH_STAT_TYPE_SWORD = 4,
    GOH_STAT_TYPE_SWORD_BIRTH = 5,
    GOH_STAT_TYPE_SWORD_EQUIP = 6,
    GOH_STAT_TYPE_SWORD_SPIRIT = 7,
} GOH_STAT_TYPE;

typedef enum {
    GOH_FLAG_NONE = 0,
    GOH_FLAG_LOAD_NOW = 1,
    GOH_FLAG_LOAD_END = 2,
    GOH_FLAG_SPR_LOAD_NOW = 4,
    GOH_FLAG_SPR_LOAD_END = 8,
    GOH_FLAG_BG_LOAD_NOW = 16,
    GOH_FLAG_BG_LOAD_END = 32,
    GOH_FLAG_END_START = 64,
    GOH_FLAG_END_NOW = 128,
    GOH_FLAG_BGM_LOAD_NOW = 256,
    GOH_FLAG_BGM_LOAD_END = 512,
    GOH_FLAG_STATUS_DRAW = 65536,
    GOH_FLAG_LAST_CALC_END = 131072,
    GOH_FLAG_BG_DRAW = 262144,
    GOH_FLAG_COMB_ICON = 524288,
    GOH_FLAG_NO_TBL = 1048576,
} GOH_FLAG;

typedef enum {
    GOH_OVERWRITE_TYPE_NONE = 0,
    GOH_OVERWRITE_TYPE_WAKU = 1,
    GOH_OVERWRITE_TYPE_SAME = 2,
} GOH_OVERWRITE_TYPE;

typedef enum {
    GohTreeMenuType_Material = 0,
    GohTreeMenuType_BattleLog = 1,
    GohTreeMenuType_SpiritLog = 2,
    GohTreeMenuType_Max = 3,
} GohTreeMenuType;

typedef enum {
    Stat_Init = 0,
    Stat_CreateCall = 1,
    Stat_Recreate = 2,
    Stat_Create = 3,
    Stat_AbortCall = 4,
    Stat_AbortWait = 5,
    Stat_AbortEnd = 6,
} Stat;

typedef enum {
    GOH_ERROR_DEVIL = 0,
    GOH_ERROR_ALREADY = 1,
    GOH_ERROR_LEVEL = 2,
    GOH_ERROR_MAG = 3,
    GOH_ERROR_RECOVER = 4,
    GOH_ERROR_GOLD = 5,
    GOH_ERROR_KARTE_STOCK = 6,
} GOH_ERROR;

typedef struct DvlFaceSet DvlFaceSet;
typedef struct GohKarteSeq GohKarte2Seq;
typedef struct GohKarteSeq GohKarteSeq;
typedef struct MenuCsrUnity MenuCsrUnity;
typedef struct SearchiCtrl SearchiCtrl;
typedef struct TreeCsr TreeCsr;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct gohData_t gohData_t;
typedef struct gohDirData_t gohDirData_t;
typedef struct gohGeneralList_t gohGeneralList_t;
typedef struct gohRenkenNewSwordList_t gohRenkenNewSwordList_t;
typedef struct gohRenkenSelMaterial_t gohRenkenSelMaterial_t;
typedef struct gohRenkenSelSwordList_t gohRenkenSelSwordList_t;
typedef struct gohResult_t gohResult_t;
typedef struct gohTable_t gohTable_t;
typedef struct jmsSeqHandle_t jmsSeqHandle_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct SearchiCtrl {
    bool searchiErr;
    bool loadTbl;
    Stat stat;
    Stat callStat;
    bool abort;
    s32 nkm;
    s32 name;
    s32 lvLess;
    s32 lvMore;
    s32 group;
    s32 sklName;
    SklSearchiType sklGroup;
    ATR endure;
    bool karte;
    bool seirei;
    bool mitama;
    bool cmbNew;
    s32 noSearch;
    s32 searchiCnt;
    s32 searchiMax;
};

struct gohDirData_t {
    u32 Flag;
    dds3ModelHandle_t *DevilModel[3];
    s32 ResultStat;
    s32 ResultStatCnt;
};

struct TreeCsr {
    s32 stage;
    s32 branch;
    ITM item;
    TreeType type;
};

struct gohData_t {
    GOH_FLAG Flag;
    jmsSeqHandle_t *SeqHandle;
    jmsSeqUnit_t *pSeqUnit;
    dds3ProcessID_t *PmvPID;
    u8 *pMsgData;
    dds3ModelHandle_t *Model[3];
    s32 ModelIndex[3];
    u8 *m_pTalkScrData;
    s32 m_TalkScrReq;
    dds3ProcessID_t *m_TalkScrPID;
    u8 *pEvtScrData;
    dds3ProcessID_t *EvtScrPID;
    u8 *pEvt2ScrData;
    dds3ProcessID_t *Evt2ScrPID;
    u8 *m_pScrData;
    dds3ProcessID_t *m_ScrPID;
    u8 *pSinanScrData;
    dds3ProcessID_t *SinanScrPID;
    s32 MenuFade;
    s32 ExitFlag;
    s32 ModelTableIndex;
    s32 ModelLoadCnt;
    GOH_ERROR ErrorType;
    GOH_STAT_TYPE m_iStatusType;
    GOH_RESULT_TYPE m_eResultType;
    s16 m_iGiftMesNo;
    s16 m_iGiftDevilNo;
    s16 m_iGiftItemNo;
    s16 m_iGiftItemNum;
    s16 m_aiGoodbyMesNo[2];
    GOH_COMBINE_TYPE m_eCombineType;
    s32 CalcStep;
    void *m_pDevSelList1;
    void *m_pDevSelList2;
    void *m_pSelList;
    s32 m_iDevColumn;
    s32 UnitListCnt;
    sdatUnitWork_t *UnitList[544];
    s32 SelDevil1;
    s32 SelDevil2;
    sdatUnitWork_t *BirthDevil;
    gohTable_t *Table;
    gohResult_t *Result;
    void *result2Task;
    gohResult_t *Result2;
    gohGeneralList_t *GeneralList;
    gohDirData_t *pDirData;
    s8 AccidentFlag;
    s8 KarteSortFlag;
    GOH_KARTE_SORTMODE KarteSortMode;
    s8 KarteRegAllStat;
    s8 KarteListFlag;
    s8 CyuuseiError;
    s8 BonusFlag;
    s32 WorkStat;
    s32 WorkstatCnt;
    s32 DevilStatusFlag;
    sdatPlayerUnitWork_t *Player;
    s8 ForcedDirection;
    s8 ForcedAccident;
    s8 ForcedBonus;
    s8 ForcedCamera;
    s8 ForcedShort;
    bool m_bCompsitionFlag;
    s16 m_iSelectBaseSwordNo;
    s16 m_iSelectNewSwordNo;
    gohRenkenSelSwordList_t *m_sRenkenSelSword;
    gohRenkenNewSwordList_t *m_sRenkenNewSword;
    gohRenkenSelMaterial_t *m_sRenkenSelMaterial;
    bool m_abActSkillFlag[8];
    f32 fNewAAnm;
    f32 fNewAlpha;
    s32 SinanMenuIndex;
    s32 line_nums;
    s32 menu_move;
    bool dataLoad;
    bool milkMist;
    bool combEndJump;
    DvlFaceSet *dvlFaceSet;
    u32 devilUniq1;
    u32 devilUniq2;
    CombStSeq combStSeq;
    GOH_COMBINE_TYPE m_eCombineType2;
    CmbBackStatus cmbBackStatus;
    SearchiCtrl *backSearch;
    s32 resultSelDevil;
    sdatUnitWork_t *combiDevil1;
    sdatUnitWork_t *combiDevil2;
    sdatUnitWork_t *combiBarthDevil;
    bool searchi;
    bool resultTblChange;
    bool spirit;
    TreeCsr *treeCsr;
    MenuCsrUnity *treeSpiritCsr;
    MenuCsrUnity *treeBattleCsr;
    bool swordDetails;
    GohTreeMenuType gohTreeMenuType;
    bool spritCheck;
    bool drawTreeUpdate;
    bool spSword;
    bool raidouSkl;
    bool sklSet;
    bool sklHave;
    bool haveSword;
    bool combKarteNewReg;
    GohKarteSeq *gohKarteSeq;
    GohKarte2Seq *gohKarte2Seq;
    bool lvAllReg;
    GOH_OVERWRITE_TYPE writeType;
    sdatUnitWork_t *writeUnit;
    bool noAllListClear;
    s16 m_DvlReport;
    sdatUnitWork_t *m_ReprtDevil1;
    sdatUnitWork_t *m_ReprtDevil2;
    s32 bgDrawWait;
    dds3Basic_t *gouScene;
    s32 stInputWait;
    bool noPartVoice;
    s32 stSklType;
};

struct GohKarteSeq {
    jmsSeqUnit_t *gohSeqUnit[13];
};
