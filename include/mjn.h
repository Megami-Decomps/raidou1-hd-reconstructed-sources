#pragma once
#include "types.h"
#include "kernel.h"

typedef enum {
    MJN_FLAG_NONE = 0,
    MJN_FLAG_SPR_LOAD_NOW = 1,
    MJN_FLAG_SPR_LOAD_END = 2,
} MJN_FLAG;

typedef enum {
    MJN_TIPS_PHASE_NONE = 0,
    MJN_TIPS_PHASE_FADE = 1,
    MJN_TIPS_PHASE_FADECHECK = 2,
    MJN_TIPS_PHASE_START = 3,
    MJN_TIPS_PHASE_ENDWAIT = 4,
    MJN_TIPS_PHASE_END = 5,
} MJN_TIPS_PHASE;

typedef enum {
    TEHAICURSORMOVE_LEFT = 0,
    TEHAICURSORMOVE_RIGHT = 1,
} TEHAICURSORMOVE;

typedef enum {
    MJN_LV_L1 = 0,
    MJN_LV_L2 = 1,
    MJN_LV_L3 = 2,
} MJN_LV;

typedef struct Agari_t Agari_t;
typedef struct AnalyzeNode_t AnalyzeNode_t;
typedef struct ChitoiAnalysis_t ChitoiAnalysis_t;
typedef struct DvlFaceSet DvlFaceSet;
typedef struct HaiDrawData_t HaiDrawData_t;
typedef struct Interface_t Interface_t;
typedef struct KokushiAnalysis_t KokushiAnalysis_t;
typedef struct MJNTIPS_CLASS MJNTIPS_CLASS;
typedef struct MenuWork_t MenuWork_t;
typedef struct Naki_t Naki_t;
typedef struct NormalAnalysis_t NormalAnalysis_t;
typedef struct Panel_t Panel_t;
typedef struct Player_t Player_t;
typedef struct Random_t Random_t;
typedef struct SeqHandle_t SeqHandle_t;
typedef struct SeqUnit_t SeqUnit_t;
typedef struct TehaiAnalysis_t TehaiAnalysis_t;
typedef struct TsumikomiPattern_t TsumikomiPattern_t;
typedef struct Visual_t Visual_t;
typedef struct Work_t Work_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct effHandle_t effHandle_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;
typedef struct mjn_tipsData_t mjn_tipsData_t;
typedef struct mjn_tipsMenuWork_t_ChildSave mjn_tipsMenuWork_t_ChildSave;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct reaceMati reaceMati;
typedef struct sprHandle_t sprHandle_t;
typedef struct tipsMenuWork_t tipsMenuWork_t;
typedef struct wanpaiUIData wanpaiUIData;

typedef s32 (*tipsInt32Delegate)(dds3ProcessID_t *ID);

struct Agari_t {
    s32 tsumo;
    s32 playerIndex;
    s32 fromPlayerIndex;
    s32 yaku[39];
    s32 yakuNum;
    s32 fu;
    s32 tensu[4];
    s32 tensuGet;
};

struct NormalAnalysis_t {
    s32 shuntsuNum;
    s32 *shuntsuHai[4];
    s32 kotsuNum;
    s32 *kotsuHai[4];
    s32 toitsuNum;
    s32 *toitsuHai[7];
    s32 tatsuNum;
    s32 *tatsuHai[7];
    s32 shanten;
    s32 fuyouNum;
    s32 fuyouHai[14];
};

struct AnalyzeNode_t {
    AnalyzeNode_t *parent;
    AnalyzeNode_t *shuntsu0;
    AnalyzeNode_t *shuntsu1;
    AnalyzeNode_t *shuntsu2;
    AnalyzeNode_t *kotsu;
    AnalyzeNode_t *toitsu;
    AnalyzeNode_t *ryanmen;
    AnalyzeNode_t *kanchan;
    NormalAnalysis_t *analysis;
    s32 type;
    s32 index;
    s32 level;
    s32 haiInt[3];
};

struct ChitoiAnalysis_t {
    s32 shanten;
    s32 toitsuNum;
    s32 toitsu[7];
    s32 fuyouNum;
    s32 fuyouHai[14];
};

struct KokushiAnalysis_t {
    s32 shanten;
    s32 kokushiNum;
    s32 kokushiHai[14];
    s32 amariNum;
    s32 amariHai[14];
    s32 fuyouNum;
    s32 fuyouHai[14];
};

struct TehaiAnalysis_t {
    s32 type;
    s32 shanten;
    s32 fAllowReach;
    NormalAnalysis_t *normalAnalysis;
    ChitoiAnalysis_t *chitoiAnalysis;
    KokushiAnalysis_t *kokushiAnalysis;
};

struct HaiDrawData_t {
    f32 *coord[8];
    f32 s0;
    f32 t0;
    f32 s1;
    f32 t1;
    s32 highlight;
    s32 fDrawTex;
    s32 dummy[2];
};

struct TsumikomiPattern_t {
    u8 yakuhai;
    u8 chinitsu;
    u8 ipeiko;
    u8 sanshokujun;
    u8 ittsu;
    u8 kantsu;
    u8 toitsu;
    u8 kotsu;
    u8 shuntsu;
    u8 kokushi;
    u8 resv[2];
};

struct Visual_t {
    f32 posDist;
    f32 cameraTargetHeight;
    f32 cameraEyeDist;
    f32 scale;
};

struct Naki_t {
    s32 type;
    s32 fromPlayerIndex;
    s32 hai[3];
};

struct Player_t {
    s32 tehaiNum;
    s32 tehai14[14];
    s32 tehai34[34];
    TehaiAnalysis_t *analysis;
    s32 sutehaiIndex;
    s32 sutehai[32];
    s32 tensu;
    s32 tensu2;
    s32 nakiNum;
    Naki_t *naki[4];
    s32 kaze;
    s32 menzen;
    s32 reachIndex;
    s32 ippatsu;
    s32 rinshan;
    s32 ichijunme;
    s32 doubleReach;
    s32 fFuriten;
    s32 aim[7];
    s32 rank;
    u8 tsumikomiProb[36];
    TsumikomiPattern_t *tsumikomiPattern;
    u8 doraProb[4];
    s32 doraTsumikomiNum;
    dds3ModelHandle_t *modelHandle;
    Visual_t *pVisualData;
    f32 posHeight;
    f32 posDistance;
    f32 cameraEyeHeight;
    f32 cameraEyeDistance;
    f32 cameraTargetHeight;
    f32 cameraTargetDistance;
    f32 scale;
    char *name;
    s32 devilID;
    s32 flag;
};

struct Random_t {
    s32 index;
    s32 value;
};

struct Interface_t {
    s32 dummy;
};

struct mjn_tipsData_t {
    s32 Flag;
    SeqHandle_t *SeqHandle;
    SeqUnit_t *pSeqUnit;
    dds3ProcessID_t *ScrPID;
    s32 MenuFade;
    s32 ExitFlag;
    s32 ModelTableIndex;
    s32 ModelLoadCnt;
    s32 TalkIndex;
    u8 *pCyousaMsg;
    s32 CyousaFileIndex;
    s32 MahjanStat;
    s32 MahjanErr;
    s32 SaveStat;
    sprHandle_t *pSpr;
    Panel_t *CyousaPanel;
    s32 nowTop;
    s32 nowHierarchy;
    s32 SeqParent[4];
    s32 nowSeq;
    s32 cnt;
};

struct Panel_t {
    u32 Flag;
    s32 FadeFlag;
    s32 LjumpFlag;
    s32 RjumpFlag;
    f32 AlphaRate;
    s32 LCursorFadeFlag;
    f32 LCursorAlphaRate;
    s32 RCursorFadeFlag;
    f32 RCursorAlphaRate;
    s32 UCursorFadeFlag;
    f32 UCursorAlphaRate;
    s32 DCursorFadeFlag;
    f32 DCursorAlphaRate;
    s32 CursorTimer;
};

struct mjn_tipsMenuWork_t_ChildSave {
    s32 parent;
    char *text[128];
    s32 ID[128];
    s32 type[128];
};

struct tipsMenuWork_t {
    dds3ProcessID_t *menuPID;
    dds3ProcessID_t *drawPID;
    u8 step;
    s32 flag;
    s16 count;
    s32 index;
    u8 alpha[2];
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
    s32 topOld;
    s32 parentID[5];
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
    s32 textChangeStep;
    char *draw_text[128];
    s32 parent_save[128];
    s32 id_save[128];
    s32 child_NumMax[5];
    mjn_tipsMenuWork_t_ChildSave *child_save[5];
};

struct SeqHandle_t {
    s32 UnitCnt;
    SeqUnit_t *pUnit[16];
    SeqUnit_t *pLastSeqUnit[2];
};

struct SeqUnit_t {
    s64 Stat;
    tipsInt32Delegate pInit;
    tipsInt32Delegate pDestroy;
    dds3ProcessFunc_t pCalc;
    dds3ProcessFunc_t pDraw;
    dds3ProcessFunc_t pUpdate;
    tipsInt32Delegate pCheck;
};

struct wanpaiUIData {
    s32 hai[5];
    bool enable[5];
};

struct reaceMati {
    s32 Matihai[34];
    s32 Attention_hai[34];
};

struct Work_t {
    sdfVector4_t cameraTargetPos;
    sdfVector4_t cameraEyePos;
    sdfVector4_t cameraUpVector;
    sdfVector4_t cameraTargetPosStart;
    sdfVector4_t cameraTargetPosEnd;
    sdfVector4_t cameraEyePosStart;
    sdfVector4_t cameraEyePosEnd;
    sdfVector4_t playerPos[4];
    HaiDrawData_t *haiDrawData[160];
    dds3ModelHandle_t *haiModelHandle[160];
    s32 HaiIndex[160];
    dds3ModelHandle_t *haiModelYama;
    pacFileHandle_t *pSummonData;
    effHandle_t *hPartsList[3];
    Visual_t *pVisualDataTable[400];
    s32 happyAt3Size;
    u8 *pHappyAt3Data;
    s32 sadAt3Size;
    u8 pSadAt3Data;
    u8 *tsumikomiProbTable[16];
    u8 *doraProbTable[8];
    u8 *devilTsumikomiTable[463];
    s32 cameraCount;
    dds3ModelHandle_t *tableModelHandle;
    dds3ModelHandle_t *tenbouModelHandle[4];
    dds3ModelHandle_t *oyaModelHandle[4];
    s32 cnt;
    Player_t *players[4];
    s32 yamaNum;
    s32 yama34[34];
    s32 yama136[136];
    s32 wanpai[14];
    wanpaiUIData *wanpai_U;
    wanpaiUIData *wanpai_D;
    s32 doraNum;
    s32 dora[5];
    s32 doraHyouji[5];
    s32 uraDora[5];
    s32 uraDoraHyouji[5];
    s32 fDrawUraDora;
    s32 kyoku;
    s32 honba;
    s32 reachBou;
    s32 oya;
    s32 chicha;
    s32 ranking[4];
    s32 money;
    s32 chankan;
    s32 tsumoIndex;
    s32 turn;
    s32 phase;
    s32 playerPhase;
    s32 nextPhase;
    s32 lastSutehai;
    s32 lastTsumohai;
    s32 playerSutehai;
    s32 AIsutehai;
    s32 kanNum;
    s32 kanHai[3];
    s32 tehaiCursor;
    s32 endHanchanCursor;
    s32 nakiCursor;
    s32 nakiMenu[7];
    s32 Chi_Sav_L[3];
    s32 Chi_Sav_C[3];
    s32 Chi_Sav_R[3];
    s32 nakiMenuNum;
    s32 nakiFlag[4];
    s32 fRyukyoku;
    s32 nakiAri;
    s32 fShowTehai[4];
    s32 fWaitPhase;
    s32 waitCount;
    s32 rstStep;
    s32 modelPhase;
    s32 summonPhase;
    s32 msgCnt;
    s32 msgMaxCnt;
    s32 msgPlayer;
    s32 msgHai;
    s32 msgFlag;
    s32 msgReqDevilID;
    s32 msgReqType;
    s32 msgStep;
    s32 visibleHai[34];
    s32 agariPlayerIndex;
    s32 fromPlayerIndex;
    s32 seed;
    s32 remainingMax[34];
    s32 attentionFlag;
    bool money_max;
    Random_t *randomArray[136];
    s32 analyzeNodeIndex;
    AnalyzeNode_t *analyzeNodes[2048];
    s32 analysisIndex;
    NormalAnalysis_t *analysis[1024];
    ChitoiAnalysis_t *chitoiAnalysis;
    KokushiAnalysis_t *kokushiAnalysis;
    TehaiAnalysis_t *bestAnalysis;
    s32 agariIndex;
    Agari_t *agari[1024];
    s32 fDrawAgari;
    Agari_t *pAgari;
    s32 fDraw3D;
    s32 haiModelIndex;
    Interface_t *interface;
    s32 fKokushiCheck;
    s32 fChankanCheck;
    s32 reachShantenIndex;
    s32 reachShanten[14];
    reaceMati *reaceMatihai[14];
    s32 fDrawAll;
    char *buffer;
    s32 PlayWithNarumi;
    DvlFaceSet *dvlFaceSet;
    MJN_FLAG sprFlag;
    s32 yakuTopNo;
    s32 yakuListLength;
    char *yakuList[16];
    MJN_TIPS_PHASE tipsPhase;
    s32 LastPush;
    s32 agariCnt;
    bool agariDrawFlag;
    s32 hideReachBou;
};

struct MenuWork_t {
    s32 step;
    dds3ProcessID_t *menuPID;
    s32 selectNum;
    s32 selectID[3];
    s32 cnt;
    s32 stockNum;
    s32 PlayWithNarumi;
};

struct MJNTIPS_CLASS {
    s32 ID;
    char *Text;
    f32 top;
    s32 childs;
    s32 childID[128];
    s32 parentID;
    char *titleID;
    s32 openStatus;
};

extern s32 *haiNumber;
extern s32 *pai_num;
extern char *panel_rule_text;
extern char *panel_yaku_text;
extern s32 MJN_CHAIR;
extern bool MJN_GUIDEHELP_FLAG;
extern s32 MJN_BUTTONGUIDE_TIMER;
extern void *VisualDataTable;
extern void *TsumikomiDataTable;
extern void *TsumikomiProbTable;
extern void *DoraProbDataTable;
extern void *HilightCol;
extern void *ModelBuffer;
extern char *spriteNameStr;
extern char *HaiIndexName;
extern Work_t *Work;
extern s32 gMjnRun;
extern fileLoadAsset_Request *sceneLoadReq;
extern bool TIPSOPEN;
extern char *mjntipsDataAssetKey;
extern char *mjntipsDataAssetName;
extern char *titleLabel;
extern char *szSeqNameNull;
extern MJNTIPS_CLASS *TIPSPAGE;
extern s32 *secondHi;
extern s32 *MenuParentID;
extern bool MenuActive;
extern void *MJN_SCENE;
extern s32 MJN_MENTSU_MENU_TOP_NUM;
extern s32 MJNMENU_BUTTONGUIDE_TIMER;
extern bool MJNMENU_GUIDEHELP_FLAG;
extern bool MjnMsgSetFlag;
extern s32 *DIDTable;
extern char *strMenu;
extern MenuWork_t *MenuWork;
extern fileLoadAsset_Request *UIsceneLoadReq;
extern u8 **mjnDoraProbTable;
extern MJN_LV *DevilLevelTable;

void mjnRuleGuideClickSet(void);
bool mjnIsRuleGuideClick(void);
void mjnTextDraw(s32 panelNo, s32 TextPosX, s32 TextPosY, s32 TextSizeW, s32 TextSizeH, const sdfColor_t *col, char *str, s32 cursor);
void mjnSetChair(void);
void mjnDeleteScene(void);
void mjnModelLoadBuffStart(void);
void mjnModelLoadBuff(s32 num);
void mjnModelLoadBuffEnd(void);
void mjnCheckButtonGuide(void);
void mjnSetTIPSOPEN(bool bo);
void mjnTipsDispatch(void);
void mjnSetChi_R(s32 hai);
void mjnSetChi_C(s32 hai);
void mjnSetChi_L(s32 hai);
void mjnTIpsMenuProcessEnd(void);
dds3ProcessID_t *mjnTipsProcessStart(void);
s32 mjnTipsProcessCheck(void);
void mjnInitSeqHandle(SeqHandle_t *pSeqHandle);
void mjnSeqDestroyAll(SeqHandle_t *pSeqHandle, dds3ProcessID_t *ID);
dds3ProcessFunc_t mjnSeqChange(SeqHandle_t *pSeqHandle, SeqUnit_t *pSeqUnit, s32 Mode, dds3ProcessID_t *ID);
void mjnSeqJump(SeqUnit_t *pCurrentSeqUnit, SeqUnit_t *pSeqUnit);
void mjnSeqJumpAndFree(SeqUnit_t *pCurrentSeqUnit, SeqUnit_t *pSeqUnit);
s32 mjnAnimFunc(s32 mode);
void mjnTipsMenuProcessStart(void);
void mjnUniDrawMenu(dds3ProcessID_t *PID);
void mjnTipsSetFocus(bool a_bFocus);
void mjnTipsMenuProcessEnd(void);
dds3ProcessFunc_t mjnTipsRootWaitCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t mjnTipsRootWaitDrawProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t mjnTipsRootWaitUpdateProcess(dds3ProcessID_t *PID);
void mjnTipsMenuStart(void);
s32 mjnGetSelectIndex(void);
s32 mjnGoParent(mjn_tipsData_t *data);
void mjnSetSeqParent(mjn_tipsData_t *data, s32 parentID);
s32 mjnCheckMovePrev(void);
s32 mjnCheckPageEnable(s32 nowIndex, s32 nextIndex);
void mjnCallDrawBack(void);
void mjnPageJump(mjn_tipsData_t *data, s32 nextSeq);
s32 mjnGetNextPage(mjn_tipsData_t *data);
s32 mjnGetPrevPage(mjn_tipsData_t *data);
void mjnDrawPANELMessage(MJNTIPS_CLASS *tips_);
dds3ProcessFunc_t mjnTipsMenuEndProcess(dds3ProcessID_t *PID);
void mjnTehaiCursorMoveMain(void);
void mjnMatihaiTextDraw(s32 _cursor);
void matiChack(void);
bool mjnTehaiCursorMove(TEHAICURSORMOVE moving);
void mjnTehaiCursorSet(void);
void mjnAfterConfirmationKan(s32 playerIndex);
s32 mjnSpriteLoadUnity(Work_t *pData);
dds3ProcessFunc_t mjnMenuLoad(dds3ProcessID_t *id);
void mjnCheckMenuButtonGuide(void);
void mjnDrawMenuHD(dds3ProcessID_t *PID);
void mjnMenuCursorCtrl(dds3ProcessID_t *PID);
char *mjnChangeTextPLTF(char *text);
void mjnUniDrawMenu_New(dds3ProcessID_t *PID);
void mjnPANEL2Process(tipsMenuWork_t *wk);
void mjnDrawPANELMessage_New(MJNTIPS_CLASS *tips_);
void mjnPanelTextCtrl(dds3ProcessID_t *PID);
void mjnResetUI(void);
