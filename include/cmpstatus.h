#pragma once
#include "types.h"
#include "CMP_SPR.h"
#include "CMP_STATUS_MODE.h"
#include "CMP_STATUS_SEQ_TYPE.h"
#include "CMP_STATUS_TYPE.h"
#include "KUDA.h"
#include "SBTL_MENU_ID.h"
#include "SKLID.h"
#include "SkillIcon.h"
#include "UiParType.h"
#include "interface.h"
#include "kernel.h"
#include "libsdf.h"

typedef enum {
    CMP_STATUS_EVENT_NON = 0,
    CMP_STATUS_EVENT_CONTINUE = 1,
    CMP_STATUS_EVENT_DONE = 2,
    CMP_STATUS_EVENT_CANCEL = 3,
    CMP_STATUS_EVENT_RETRY = 4,
    CMP_STATUS_EVENT_NEXT = 5,
} CMP_STATUS_EVENT;

typedef enum {
    CMP_ITM_SKLSET_TYPE_Battle = 0,
    CMP_ITM_SKLSET_TYPE_Omoide = 1,
} CMP_ITM_SKLSET_TYPE;

typedef enum {
    L_L = 1,
    L_R = 2,
    L_U = 4,
    L_D = 8,
    R_L = 16,
    R_R = 32,
    R_U = 64,
    R_D = 128,
} ANALOG;

typedef enum {
    CMP_ST_LF_RELEASE = 1,
    CMP_ST_LF_LOAD_SPR_MAIN_MEM = 2,
    CMP_ST_LF_LOAD_SPR_MAIN_HND = 4,
    CMP_ST_LF_LOAD_SPR_STAT_MEM = 8,
    CMP_ST_LF_LOAD_SPR_STAT_HND = 16,
    CMP_ST_LF_LOAD_SPR_LIST_MEM = 32,
    CMP_ST_LF_LOAD_SPR_LIST_HND = 64,
    CMP_ST_LF_SET_MODEL = 128,
    CMP_ST_LF_RELOAD_MODEL = 256,
    CMP_ST_LF_LOAD_MODEL = 512,
    CMP_ST_LF_DRAW = 1024,
    CMP_ST_LF_DRAW_MODEL = 2048,
    CMP_ST_LF_DRAW_PARAM = 4096,
    CMP_ST_LF_DRAW_CURSOR = 8192,
    CMP_ST_GF_CTRL_MODE = 16384,
    CMP_ST_GF_CANCEL_END = 32768,
    CMP_ST_LF_DRAW_LVUP = 65536,
    CMP_ST_SKL_SET = 131072,
    CMP_ST_GF_RECOVER_HP = 262144,
    CMP_ST_GF_RECOVER_MP = 524288,
    CMP_ST_GF_DRAW_SKL_C = 1048576,
    CMP_ST_GF_DRAW_SKL_A = 2097152,
    CMP_ST_GF_CALL_START = 4194304,
    CMP_ST_GF_CALL_STATUS = 8388608,
    CMP_ST_GF_CALL_VIEWER = 16777216,
    CMP_ST_GF_CALL_GUIDE = 33554432,
    CMP_ST_GF_CALL_END = 67108864,
    CMP_ST_LF_LOAD_GUIDE = 134217728,
    CMP_ST_GF_CALL_DEBUG = 268435456,
    CMP_ST_GF_DEBUG = 536870912,
    CMP_ST_SWORD_SEL = 1073741824,
    CMP_ST_ITM_SKL = 2147483648,
    CMP_ST_NO_EXPLAN = 4294967296,
    CMP_ST_CHG_SKL = 8589934592,
} CMP_ST;

typedef enum {
    MOVEFLAG_PREV = 1,
    MOVEFLAG_NEXT = 2,
    MOVEFLAG_PAGE = 4,
    MOVEFLAG_LOOP = 8,
    MOVETYPE_PREV = 1,
    MOVETYPE_PREV_LOOP = 9,
    MOVETYPE_NEXT = 2,
    MOVETYPE_NEXT_LOOP = 10,
    MOVETYPE_PREV_PAGE = 5,
    MOVETYPE_PREV_PAGE_LOOP = 13,
    MOVETYPE_NEXT_PAGE = 6,
    MOVETYPE_NEXT_PAGE_LOOP = 14,
} CMPSTATUS_CUR;

typedef enum {
    CMPSTATUS_CUR_FLAG_UPDATE_SEL = 1,
    CMPSTATUS_CUR_FLAG_UPDATE_LST = 2,
} CMPSTATUS_CUR_FLAG_UPDATE;

typedef enum {
    CMP_STATUS_STEP_WAIT = 0,
    CMP_STATUS_STEP_STATUS = 1,
    CMP_STATUS_STEP_VIEWER = 2,
    CMP_STATUS_STEP_GUIDE = 3,
    CMP_STATUS_STEP_CHANGE = 4,
    CMP_STATUS_STEP_SWORD = 5,
    CMP_STATUS_STEP_SWORD_MV = 6,
    CMP_STATUS_STEP_MESS_BEGIN_WAIT = 7,
    CMP_STATUS_STEP_MESS_END_WAIT = 8,
    CMP_STATUS_STEP_STEP_END = 9,
    CMP_STATUS_STEP_SWORD_SEL = 10,
} CMP_STATUS_STEP;

typedef enum {
    NoSklHelpType_Omoide = 0,
    NoSklHelpType_Spirit = 1,
} NoSklHelpType;

typedef enum {
    MemPanelType_Omoide = 0,
    MemPanelType_Spirit = 1,
    MemPanelType_Syougou = 2,
    MemPanelType_Max = 3,
} MemPanelType;

typedef enum {
    UiStatusType_NON = 0,
    UiStatusType_RAIDOU = 1,
    UiStatusType_NAKAMA = 2,
} UiStatusType;

typedef struct CmpBasePartsSet CmpBasePartsSet;
typedef struct CmpGaugeParSet CmpGaugeParSet;
typedef struct CmpPassTextSet CmpPassTextSet;
typedef struct CmpSelectSkillSet CmpSelectSkillSet;
typedef struct CmpStatusGaugeSet CmpStatusGaugeSet;
typedef struct CmpStatusPartsPassPar CmpStatusPartsPassPar;
typedef struct RankText RankText;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct cmpStatusCur_t cmpStatusCur_t;
typedef struct cmpSummnerRankMng_t cmpSummnerRankMng_t;
typedef struct cmpSummnerRank_t cmpSummnerRank_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfMover_t itfMover_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagCMP_STATUS_WORK tagCMP_STATUS_WORK;
typedef struct tagOBJECT_WORK tagOBJECT_WORK;

typedef void *(*cmpSummnerRankFunc_t)(cmpSummnerRank_t *UnnamedParameter);

struct CmpStatusPartsPassPar {
    UiStatusType type;
    CmpPassTextSet *lv;
    CmpPassTextSet *nowHp;
    CmpPassTextSet *maxHp;
    KUDA kuda;
    CmpPassTextSet *sei;
    CmpPassTextSet *mei;
    CmpPassTextSet *mag;
    CmpPassTextSet *maxMag;
    CmpPassTextSet *allCyuusei;
};

struct cmpStatusCur_t {
    CMPSTATUS_CUR_FLAG_UPDATE flags;
    s32 selMax;
    s32 drwMax;
    s32 drwDefNum;
    s32 drwDefMax;
    s32 selNo;
    s32 topNo;
    s32 drwNo;
};

struct tagCMP_STATUS_WORK {
    dds3ProcessID_t *drawPID;
    CMP_ST flags;
    s8 step;
    s8 step2;
    CMP_STATUS_SEQ_TYPE seqtype;
    s8 stepModel;
    CMP_STATUS_MODE mode;
    CMP_STATUS_TYPE type;
    s16 count;
    s16 count2;
    s32 callModelNo;
    s32 loadModelNo;
    s32 motionNum;
    s32 motionCut;
    f32 motionSpd;
    sdatUnitWork_t *unit;
    sdatUnitWork_t *unitSrc;
    sdatUnitWork_t *unitDst;
    sdatUnitWork_t *pUnitDst;
    sdatPlayerUnitWork_t *player;
    u8 sword_old[4];
    u8 sword_new[4];
    s32 player_tec;
    SKLID learnCombSkillID;
    SKLID learnAutoSkillID;
    itfMover_t *mover;
    s32 swordno;
    s32 swordatk;
    s32 lvup_num;
    s32 param[4];
    s32 sel_param;
    s32 sel_num;
    s32 lvup_cnt;
    s32 skleff_x;
    s32 skleff_y;
    s32 modeSq;
    s32 sklType;
    s32 lrnEffCnt;
    s32 lrnEffX;
    s32 lrnEffY;
    SKLID omoideEx;
    s32 suteCsr;
    SKLID suteSkl;
    s32 lCsrAlpha;
    s32 rCsrAlpha;
    s32 memSklCsr;
    s32 memSklTab;
    s32 sklCsr;
    bool abLightUp[17];
    s32 lightUpCnt;
    bool lightUpDir;
    bool bUDHelpNon;
    cmpSummnerRankMng_t *sSummnerRankMng;
    sdfVector3_t sMov;
    s32 iMoveCnt;
    s32 iDspCnt;
    CMP_STATUS_EVENT eEvent;
    bool bEquipSwordNoHelp;
    cmpStatusCur_t *wkMemSklCur;
    bool setLuck;
    bool lvlUp;
    bool statusSceneActive;
    void *sceneOffFunc;
    s32 rsvCsr;
    s32 commandCsr;
    s32 skillMax;
    s32 sklType_r;
    bool root;
    sdatUnitWork_t *mitamaCombDvl;
    void *rankTextList;
    bool noSklHelp;
    s32 newSkillCnt;
    bool ofcSkl;
    bool noStatusDraw;
    bool statusGoSword;
    bool equipEnd;
    s32 sklChgSeq;
    s32 selSkl;
    s32 baseSkl;
    s32 baseSklCsr;
    s32 baseSklIndex;
    bool noCallVoice;
    s32 lvUpVoice;
    bool sklSpeedUp;
    f32 counter;
    bool lightParNoDraw;
    bool noGcClear;
};

struct RankText {
    s32 sprNo;
    char *text;
    s32 setNo;
    bool newMark;
};

struct tagOBJECT_WORK {
    bool bEnabled;
    char *szString;
    s32 iSprNo;
    DDS3_OT iOT;
    f32 fSize;
    f32 fSizeW;
    f32 fSizeH;
    f32 fDelta;
    s32 iAlpha;
    f32 fAlpha;
    f32 fCounter;
    s32 iMode;
    f32 fQ_x_range;
    f32 fQ_y_range;
    s32 iQ_frame;
    s32 iInX;
};

struct cmpSummnerRank_t {
    bool bSummnerRankStart;
    bool bSummnerRankWait;
    sdatUnitWork_t *psUnit;
    s32 iAlphaRate;
    s32 iCounter;
    tagOBJECT_WORK *sObjBG;
    tagOBJECT_WORK *sObjBGSRank;
    tagOBJECT_WORK *sObjBGRaido;
    tagOBJECT_WORK *sObjCyusei;
    tagOBJECT_WORK *sObjSRank;
    tagOBJECT_WORK *sObjRaido;
    tagOBJECT_WORK *sObjBlur;
    s32 cnt;
};

struct cmpSummnerRankMng_t {
    cmpSummnerRankFunc_t cbState;
    cmpSummnerRank_t *sSummnerRank;
};

struct CmpPassTextSet {
    char *text;
    u32 col;
};

struct CmpSelectSkillSet {
    void *skillBattle;
    void *r1Text;
    void *r2Text;
};

struct CmpBasePartsSet {
    void *titleTmProGUI;
    CmpSelectSkillSet *sklSelSet;
    void *attributeList;
    void *skillSetList;
};

struct CmpStatusGaugeSet {
    CmpGaugeParSet *power;
    CmpGaugeParSet *demon;
    CmpGaugeParSet *endurance;
    CmpGaugeParSet *luck;
    void *powerText;
    void *demonText;
    void *enduranceText;
    void *luckText;
    UiStatusType type;
};

struct CmpGaugeParSet {
    void *gaugeBase;
    void *gaugeColorImage;
    void *gaugeLightImage;
    void *num;
};

extern s32 lastBasePar[4];
extern s32 *lastOrangePar;
extern CmpStatusPartsPassPar *passPar;
extern SBTL_MENU_ID *commandTbl;
extern char *cmdHelpText;
extern s32 *btlCommandSetParTbl;
extern char *rankText;
extern char *rankText2;
extern char *dlcRankText;
extern dds3ProcessID_t *g_mainPID;
extern dds3ProcessID_t *g_guidePID;
extern f32 *pos;
extern f32 *rot;
extern s32 aGoodbyCnt;
extern s32 aColorCnt;
extern f32 s_cmpRaidoFlushCntf;
extern s16 **arrSwordNameLv;
extern SDF_PADMAP *viewerNoPress;
extern s32 **arrPlayerRank;
extern s32 **arrPlayerRankDlc;

void StatusSceneActive(bool _active);
void cmpLastParClear(void);
s32 StatusSkillCheck(void);
SkillIcon cmpGetSkillIconType(SBTLSKILLP_TBL *_tbl, SKLID _skillID);
void cmpDrawSkillNameExUnity(SKLID a_id, s32 cnt, u32 a_rgba, bool _backChange, bool _raidou, bool _noSpCol);
void cmpDrawRsvSkillNameExUnity(SKLID a_id, s32 cnt, u32 a_rgba, bool _backChange, bool _noSpCol);
void cmpDrawSkillOmoideNameExUnity(SKLID a_id, s32 cnt, u32 a_rgba);
bool cmpCurInit(cmpStatusCur_t *a_wk);
bool cmpCurSetSelectMax(cmpStatusCur_t *a_wk, s32 a_max);
bool cmpCurSetDrawMax(cmpStatusCur_t *a_wk, s32 a_max);
bool cmpCurStart(cmpStatusCur_t *a_wk, bool a_bFixDrawNum);
bool cmpCurSetMoveType(cmpStatusCur_t *a_wk, CMPSTATUS_CUR a_MoveType);
s32 cmpGetSuteCsr(void);
void cmpOmoideGaIppai(SKLID sklid);
sdatUnitWork_t *cmpGetUnit(void);
s32 cmpGetOmoideBlank(void);
s32 cmpGetLearnEffCnt(void);
void cmpLearnEff(s32 skltype, s32 index, bool ofc);
void cmpAutoBattleSkl(sdatUnitWork_t *pUnit, SKLID sklid);
void cmpLearnSkl(SKLID sklid, s32 skltype, s32 index, bool _ofs);
s32 cmpGetSklCsrMax_R(sdatUnitWork_t *pUnit, s32 arg);
void cmpSetSklCsrMax(void);
s32 cmpGetSklCsrMax(sdatUnitWork_t *pUnit, s32 arg);
SKLID cmpGetCsrSelSkl(void);
s32 cmpGetSklCsr(void);
s32 cmpGetRsvCsr(void);
void cmpSetSklCsr(s32 _no);
void cmpSetRsvCsr(s32 _no);
void cmpCurInitMemSkl(sdatUnitWork_t *a_pUnit, MemPanelType memPanelType);
SKLID cmpCurGetSelectMemSklID(void);
void cmpGetSwordParam(s32 a_swordno, u8 *a_pParam);
ANALOG cmpGetAnalogPad(void);
void cmpGetMotionParam(tagCMP_STATUS_WORK *wk);
void cmpSetModelLight(tagCMP_STATUS_WORK *wk);
void cmpUpdatemodel(tagCMP_STATUS_WORK *wk);
void cmpViewerModel(tagCMP_STATUS_WORK *wk);
bool cmpDrawEquipIsSoubigo(tagCMP_STATUS_WORK *wk);
s32 cmpCalcRestParamPly(tagCMP_STATUS_WORK *wk);
s32 cmpCalcRestParamDvl(tagCMP_STATUS_WORK *wk);
s32 cmpCalcRestParam(tagCMP_STATUS_WORK *wk);
bool cmpCalcParam(tagCMP_STATUS_WORK *wk, s8 a_mode, bool _noSe);
void cmpResetParam(tagCMP_STATUS_WORK *wk);
s32 cmpCtrlSetParam(tagCMP_STATUS_WORK *wk);
void cmpCallStart(tagCMP_STATUS_WORK *wk);
void cmpCallEnd(tagCMP_STATUS_WORK *wk);
void cmpFuncEnd(tagCMP_STATUS_WORK *wk);
void cmpSequence(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqStatusStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqViewerStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqGuideStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqChangeStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqSwordStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqSwordSelStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpNmlSeqSwordMvStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpSyougouSet(tagCMP_STATUS_WORK *wk);
void cmpSpiritSet(tagCMP_STATUS_WORK *wk);
void cmpBtlCommandSet(tagCMP_STATUS_WORK *wk);
void cmpSkillSetUnity(tagCMP_STATUS_WORK *wk);
void cmpSklChangeUpdate(tagCMP_STATUS_WORK *wk);
bool cmpSklSwapBaseCheck(tagCMP_STATUS_WORK *wk);
void cmpSetChgSklBaseIndex(tagCMP_STATUS_WORK *wk);
void cmpSklChgUpdate(tagCMP_STATUS_WORK *wk);
void cmpEndChgSklMode(tagCMP_STATUS_WORK *wk);
void cmpChangeWaitMode(void);
void cmpSeqMemSet(tagCMP_STATUS_WORK *wk);
void cmpMemSetWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpMemSetMesWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpMemSetSeqStatusStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpMemSetMesEndStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpMemSetChangeStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpSeqGoodby(tagCMP_STATUS_WORK *wk);
void cmpSeqDvlReport(tagCMP_STATUS_WORK *wk);
void cmpSeqLevelUp(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqStartStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqFadeInStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqCallMesStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpCreateNakamaLvUpParMes(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqWaitMesStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqCallParInStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqSetParStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqConfStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqCallParOutStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqSklCMsgInitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqSklCMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqNmlSklItemMsgInitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqNmlSklItemMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqSklAMsgInitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqSklAMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqOmoSklItemMsgInitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqOmoSklItemMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqRecvWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpLvUpSeqWaitStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpRstSeqViewerStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpRstSeqChangeStepUpdate(tagCMP_STATUS_WORK *wk);
void cmpSeqRankUp(tagCMP_STATUS_WORK *wk);
void Release(tagCMP_STATUS_WORK *wk);
void CallProcEnd(tagCMP_STATUS_WORK *wk);
u8 CheckProcEnd(tagCMP_STATUS_WORK *wk);
dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
void cmpDrawNumSmallFont(s32 a_x, s32 a_y, s32 a_space, u32 a_color, u8 a_alpha, char *a_str);
void cmpDrawNumOtSmallFont(s32 a_x, s32 a_y, s32 a_space, u32 a_color, u8 a_alpha, char *a_str, DDS3_OT a_ot);
void cmpDrawSprite(s32 a_x, s32 a_y, u8 a_alpha, CMP_SPR a_sprFileNo, s32 a_sprNo);
void cmpDrawSprList(s32 a_x, s32 a_y, u8 a_alpha, CMP_SPR a_sprFileNo, itfSprList_t *a_list);
void cmpDrawBlinkParam(s32 a_x, s32 a_y, s32 a_alphaRate, s32 a_cnt);
void cmpDrawLightPar(s32 cnt, UiParType _type, CmpStatusGaugeSet *statusGaugeSet, bool _noLight);
void cmpDrawParam(tagCMP_STATUS_WORK *wk, s32 a_type, s32 a_x, s32 a_y, s32 a_alphaRate, bool a_bSel);
void cmpDrawParamCursor(tagCMP_STATUS_WORK *wk);
void cmpDrawParameter(tagCMP_STATUS_WORK *wk, s32 a_alphaRate);
s32 cmpGetNowSummonerRank(void);
s32 cmpGetSummonerRank2SprNo(bool _cmp);
void cmpSummnerRankObjectInit(tagOBJECT_WORK *psSelf);
void cmpSummnerRankMngInit(cmpSummnerRankMng_t *psSelf);
void cmpSummnerRankMngSetState(cmpSummnerRankMng_t *psSelf, cmpSummnerRankFunc_t cbFunc);
void cmpSummnerRankMngExecute(cmpSummnerRankMng_t *psSelf, sdatUnitWork_t *psUnit, s32 iAlphaRate);
void cmpSummnerRankChange(cmpSummnerRank_t *psSelf);
void cmpSummnerRankInit(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateWait(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateBGHalf(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateCyuuseiMeimetsu(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankOldFadein(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankOldBig(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankWait(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankFadeout(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNewFadein(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNew(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNewSmall(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNewQuake(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankRaidoPika(cmpSummnerRank_t *psSelf);
cmpSummnerRankFunc_t cmpSummnerRankStateBGFukki(cmpSummnerRank_t *psSelf);
void cmpSummnerRankDrawBg(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr);
void cmpSummnerRankDrawCyusei(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr);
void cmpSummnerRankDrawSummnerRank(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr);
void cmpSummnerRankDrawRaido(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr);
void cmpSummnerRankDrawSummnerRankBlur(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr);
void cmpSummnerRankDraw(cmpSummnerRank_t *psSelf, sprHandle_t *hSpr);
void cmpDrawPartsName(tagCMP_STATUS_WORK *wk, s32 a_alphaRate);
void cmpDrawPartsExp(sdatUnitWork_t *a_pUnit, s32 a_alphaRate);
s32 cmpGetSwordNameLevel(s32 a_lv);
char *cmpGetSwordName(u8 *a_pParam);
char *cmpGetSwordNameEx(s32 a_devilID);
u32 GetValueColor(s32 iOldVal, s32 iNewVal);
void cmpDrawEquip(tagCMP_STATUS_WORK *wk, s32 a_type, s32 a_x, s32 a_y, s32 a_alphaRate, bool _top);
void cmpDrawEquipSword(s32 a_x, s32 a_y, s32 a_alphaRate);
void cmpDrawEquipBullet(s32 a_x, s32 a_y, s32 a_alphaRate, bool _top);
void cmpDrawPartsEquip(tagCMP_STATUS_WORK *wk, s32 a_alphaRate);
void cmpDrawSkillNameEx(SKLID a_id, s32 a_x, s32 a_y, u32 a_rgba, s32 a_alphaRate);
void drawMiscHelp(FRW_HELP HelpType, SKLID uSkillID);
void cmpDrawNoneSklHelp(NoSklHelpType _type);
void cmpDrawPartsOmoideSkillSub(s32 a_x, s32 a_y, u32 a_alphaRate, itfSprList_t *a_pList);
void cmpDrawPartsOmoideSkill(tagCMP_STATUS_WORK *wk, s32 a_alphaRate);
bool cmpCheckMitamaBarstSklSet(tagCMP_STATUS_WORK *_wk);
void cmpDrawPartsSpritSkill(tagCMP_STATUS_WORK *wk, s32 a_alphaRate);
void cmpDrawSumnerRankList(tagCMP_STATUS_WORK *wk);
void cmpDrawSpirtList(tagCMP_STATUS_WORK *wk);
void *cmpGetDrawOmoideSkill(sdatUnitWork_t *unit, s32 _topNo, s32 _drwMax);
void *cmpGetDrawSpiritSkill(s32 _topNo, s32 _drwMax, bool _sort);
void *cmpGetDrawRaidouSkill(s32 _topNo, s32 _drwMax, bool _sort);
void cmpRaidouSklSpiritDraw(tagCMP_STATUS_WORK *wk);
void cmpDrawRaidouSkill(tagCMP_STATUS_WORK *wk);
void cmpDrawPartsLRHelpDraw(tagCMP_STATUS_WORK *wk, CmpBasePartsSet *set);
void cmpDrawPartsSkill(tagCMP_STATUS_WORK *wk, s32 a_alphaRate);
bool cmpSklPartsNormalHelpOffChk(SKLID _sklID, tagCMP_STATUS_WORK *_wk);
void cmpSklDrawPartsNormal(tagCMP_STATUS_WORK *wk);
void cmpCombIconDraw(tagCMP_STATUS_WORK *wk, s32 i, SKLID skillID);
void cmpSklDrawPartsOmoide(tagCMP_STATUS_WORK *wk);
void cmpSklDrawPartsSousa(tagCMP_STATUS_WORK *wk);
void DrawHelp(tagCMP_STATUS_WORK *wk, s8 a_alphaRate);
void cmpDrawLevelUpPoint(tagCMP_STATUS_WORK *wk);
void cmpDrawLearnSkillEffect(tagCMP_STATUS_WORK *wk);
bool cmpDrawOutEffectCheck(void);
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
void cmpSetStartStatusSetting(bool _flag, void *_func);
bool cmpGetStartStatusFlag(void);
void cmpNoCallVoiceSet(void);
void Start(sdatUnitWork_t *a_pUnit);
void End(void);
bool cmpChkEnd(void);
void cmpStartLevelUp(sdatUnitWork_t *a_pUnitDst, sdatPlayerUnitWork_t *_newPlayerPar);
void cmpSpeedUpSklOff(void);
void cmpStartRankUp(void);
bool cmpChkWait2(void);
bool cmpChkEnd2(void);
void cmpStartLearnSkillMessage(s32 a_type, SKLID a_skillID, bool _ofc);
void cmpSetRecover(s32 a_type);
void cmpSetFlagDraw(bool a_bDraw);
bool cmpChkDraw(void);
void cmpSetFlagCtrlMode(bool a_bFlag);
void cmpSetFlagNoExplan(bool a_bFlag);
void cmpSetFlagCamp(void);
bool StatusGoSword(void);
void cmpSetSkillMode(bool _flag);
bool cmpSetSkillNow(void);
void cmpChgSkillMode(bool _flag);
bool cmpChgSkillNow(void);
bool cmpGetFlagCallDebug(void);
bool cmpGetFlagDebug(void);
bool cmpGetFlagScreenShot(void);
s32 cmpGetSetMotionFrame(void);
CMP_STATUS_MODE cmpGetMode(void);
s32 cmpGetSklType(bool _raidou);
bool SetType(CMP_STATUS_TYPE a_type, s32 a_swordno, bool _root);
void cmpRankNewOff(s32 _setNo);
void cmpRankNewOn(s32 _setNo);
void cmpCreateRankTextList(void);
void Init(tagCMP_STATUS_WORK *wk);
void Shutdown(dds3ProcessID_t *PID);
dds3ProcessID_t *ProcessStart(void);
void ProcessEnd(bool _noGcClear);
bool ProcessCheck(void);
void cmpSetModeSq(s32 _sq);
s32 cmpGetModeSq(void);
void cmpDecideSuteSkl(void);
bool cmpSlctSuteSkl(void);
void cmpSuteKakuninMsg(void);
void cmpOmoideModoshi(void);
void cmpMemSklCurPrev(void);
void cmpMemSklCurPrevLoop(void);
void cmpMemSklAutoCurNext(void);
void cmpMemSklCurNext(bool _noSe);
void cmpMemSklCurNextLoop(void);
void cmpMemSklCurPrevPage(void);
void cmpMemSklCurPrevPageLoop(void);
void cmpMemSklCurNextPage(void);
void cmpMemSklCurNextPageLoop(void);
void cmpMemSklCurSelPage(void);
void cmpSetBtlSkl(s32 _index);
bool cmpOpenOmoedeLog(void);
void cmpSetChuuseiMax(void);
void cmpSetOmoideLearned(s32 idx);
void cmpSummnerRankStart(void);
bool cmpSummnerRankWait(void);
void cmpRaidoFlushStart(void);
s32 cmpRaidoFlushEndCheck(void);
bool cmpMemSet(void);
void cmpInitModeSq(void);
bool cmpOmoideSkillIsFinish(void);
void cmpSetEvent(CMP_STATUS_EVENT eEvent);
void cmpMemSklCurUpdate(void);
void cmpDecModeSq(bool _noSe);
bool cmpCheckSklSet(void);
s32 cmpRNextRsvCsr(tagCMP_STATUS_WORK *wk, s32 _csrNo);
s32 cmpLNextRsvCsr(tagCMP_STATUS_WORK *wk, s32 _csrNo);
s32 cmpLNextNmlCsr(tagCMP_STATUS_WORK *wk);
void cmpSklCsrL(void);
void cmpSklCsrR(void);
void cmpSklCsrU(void);
void cmpSklCsrD(void);
void cmpSklCsrMouse(bool _item);
void cmpIncModeSq(bool _noSe);
void cmpSklTypeAdd(void);
void cmpSklTypeSub(void);
void cmpSklTypeSet(s32 sklType, bool _csrClear);
void cmpMouseSetSklType(void);
void cmpSetLightUpSkl(s32 idx, bool b);
void cmpUDHelpNon(bool b);
bool cmpCheckStepGoodbyMessage(void);
void cmpStartMemSet(sdatUnitWork_t *a_pUnitDst, bool bKeyControl);
void cmpStartGoodby(sdatUnitWork_t *a_pUnit);
void cmpStartSklSet(sdatUnitWork_t *a_pUnit, CMP_ITM_SKLSET_TYPE _sklType);
void cmpStartDvlReport(sdatUnitWork_t *a_pUnit);
void cmpEquipSwordNoHelp(bool bFlag);
s32 cmpGetSkillIconSpriteNo(SKLID a_skillid);
void cmpSwordSelFlagOn(void);
bool cmpSwordSelFlagChk(void);
CMP_STATUS_STEP cmpGetStatusStep(void);
RankText *cmpGetSetRank(s32 _setNo);
void cmpSetMitamaCombDvl(sdatUnitWork_t *_unit);
tagCMP_STATUS_WORK *cmpGetStatusWk(void);
