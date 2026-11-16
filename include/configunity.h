#pragma once
#include "types.h"
#include "itf.h"
#include "kernel.h"

typedef enum {
    ConfigMinMax_MIN = 0,
    ConfigMinMax_MAX = 1,
} ConfigMinMax;

typedef enum {
    ConfigTab_Audio = 0,
    ConfigTab_Game = 1,
    ConfigTab_Graphics = 2,
    ConfigTab_GamePad = 3,
    ConfigTab_Max = 6,
    ConfigTab_MaxCS = 4,
} ConfigTab;

typedef enum {
    CONFIG_STEP_LOAD = 0,
    CONFIG_STEP_INIT = 1,
    CONFIG_STEP_FADEIN = 2,
    CONFIG_STEP_MAIN = 3,
    CONFIG_STEP_FADEOUT = 4,
    CONFIG_STEP_RELEASE = 5,
    CONFIG_STEP_SAVE0 = 6,
    CONFIG_STEP_SAVE1 = 7,
    CONFIG_STEP_SAVEAFTER = 8,
    CONFIG_STEP_END = 9,
} CONFIG_STEP;

typedef enum {
    CONFIG_MENU_RELEASE = 1,
    CONFIG_MENU_DRAW = 8,
} CONFIG_MENU;

typedef enum {
    CONFIG_STAT_NORMAL = 0,
    CONFIG_STAT_MESAGE = 1,
    CONFIG_STAT_KEY = 2,
} CONFIG_STAT;

typedef enum {
    CONFIG_MESSAGE_None = -1,
    CONFIG_MESSAGE_Enter = 0,
    CONFIG_MESSAGE_PadChange = 1,
    CONFIG_MESSAGE_KeyChange = 2,
    CONFIG_MESSAGE_duplication = 3,
    CONFIG_MESSAGE_duplicationM = 4,
    CONFIG_MESSAGE_TabChange = 5,
    CONFIG_MESSAGE_TabChange_k = 6,
    CONFIG_MESSAGE_Count = 7,
    CONFIG_MESSAGE_Default = 8,
    CONFIG_MESSAGE_Exit = 9,
    CONFIG_MESSAGE_EndWaitToNormal = 10,
    CONFIG_MESSAGE_End = 11,
} CONFIG_MESSAGE;

typedef struct CONFIG_WORK CONFIG_WORK;
typedef struct ConfigCursor ConfigCursor;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;

struct ConfigCursor {
    s32 csrNo;
    s32 listTop;
    s32 listDrwNo;
    s32 nowMax;
    s32 listMax;
    CsrUnityMoveFunc moveFunc;
    s32 setNo;
    s32 *skipCnt;
    s32 ofs;
    void *virtualItemNum;
};

struct CONFIG_WORK {
    dds3ProcessID_t *drawPID;
    s32 count;
    CONFIG_MENU processStat;
    CONFIG_STAT stat;
    CONFIG_STEP step;
    CONFIG_STEP save_end_step;
    ConfigTab tab;
    ConfigTab tab_old;
    ConfigTab changeTab;
    ConfigCursor *csr[4];
    s32 *nowPar[4];
    s32 *setPar[4];
    CONFIG_MESSAGE mesType;
    CONFIG_MESSAGE NextMesType;
    f32 mesCunter;
    bool menuChange;
    bool changeBgmPlaying;
    s32 prevBgm;
    bool saveFlag;
};

extern char *uiSceneName;
extern fileLoadAsset_Request *sceneLoadReq;
extern dds3ProcessID_t *g_mainPID;
extern bool g_isTabchange;
extern char *headText_pad;
extern char *headText_km;
extern char *tabText;
extern bool IsCamp;
extern bool IsBattle;

void SetConfigData(s32 _setPar, s32 _value);
void *Get255Over(s32 _setTab, s32 _setIdx);
void SetConfigDataHi(s32 _setPar, s32 _value);
void SetConfigDataLw(s32 _setPar, s32 _value);
s32 GetConfigData(s32 _setPar);
s32 GetConfigDataHi(s32 _setPar);
s32 GetConfigDataLw(s32 _setPar);
s32 *GetConfigTab(s32 _setTab);
s32 GetConfigDataMinMax(s32 _setPar, ConfigMinMax _MinMax);
bool CheckConfigData(void);
void ChangeConfigAll(ConfigTab _tab, bool bakc_f_d);
void SaveConfigData(void);
void SetRAIDOU_Flag(void);
char *GetSelectText(s32 _setPar);
void ChangeState(CONFIG_STAT _stat);
bool IsSpecifiedState(CONFIG_STAT stat_);
void InitMessage(CONFIG_MESSAGE _mesType, bool befor_chk);
void InitSaveToMessage(CONFIG_MESSAGE _mesType);
void UpdateMessage(void);
void KeyConfigUpdate(void);
ConfigCursor *GetCsrTabType(ConfigTab _tab);
ConfigCursor *GetNowCsr(void);
s32 GetNowListTop(void);
s32 GetNowTab(void);
void TabChange(s32 _cnt, bool _se);
void MainInput(void);
bool GetDragFlg(void);
void LoadLocalizeText(void);
void LoadScene(void);
void UnloadScene(char *_sceneName);
void Init(CONFIG_WORK *_wk);
void ProcessStart(void);
dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
void TabInit(void);
void TabUpdate(void);
void TabDraw(void);
void DrawListActive(void);
char *GetMenuText(ConfigTab _tab);
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
void Shutdown(dds3ProcessID_t *PID);
bool ProcessCheck(void);
void ProcessEnd(void);
