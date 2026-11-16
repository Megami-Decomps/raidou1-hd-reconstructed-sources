#pragma once
#include "types.h"
#include "kernel.h"

typedef enum {
    TITLEenum_FADE_CNT = 30,
    TITLEenum_WAIT_CNT = 150,
    TITLEenum_RET_CNT = 900,
    TITLEenum_RET_FADE_CNT = 60,
    TITLEenum_FLAG_NONE = 0,
    TITLEenum_SPR_LOAD_NOW = 1,
    TITLEenum_SPR_LOAD_END = 2,
    TITLEenum_AT3_LOAD_NOW = 4,
    TITLEenum_AT3_LOAD_END = 8,
    TITLEenum_AT3_PLAY = 16,
    TITLEenum_FLAG_MOVIE_PLAY = 32,
    TITLEenum_FLAG_MOVIE_STOP = 64,
    TITLEenum_CURSOR_FLAG_NONE = 0,
    TITLEenum_CURSOR_FLAG_ACT = 1,
    TITLEenum_LOGO_FADE_FRAME = 40,
    TITLEenum_LOGO_WAIT_FRAME = 260,
    TITLEenum_LASTLOGO_AFTER_WAIT = 60,
    TITLEenum_MOVIE_FADEOUT_FRAME = 5,
    TITLEenum_MOVIE_SKIP_LAST_MARGIN = 30,
    TITLEenum_MAIN_IN_WAIT_FRAME = 60,
    TITLEenum_MAIN_WAIT_FRAME = 1200,
    TITLEenum_MAIN_FADEOUT_FRAME = 60,
    TITLEenum_ADV_LOGO_FADE_FRAME = 30,
    TITLEenum_ADV_LOGO_FADE_START_FRAME = 480,
    TITLEenum_CURSOR_SCALE_TIMER = 6,
    TITLEenum_BG_MOVIE_FRAME = 5400,
    TITLEenum_BG_MOVIE_FADE_FRAME = 30,
    TITLEenum_AT3_NO = 80,
    TITLEenum_AT3_NO2 = 14,
    TITLEenum_MOVIE_START_WAIT = 20,
} TITLEenum;

typedef enum {
    CURSOR_MODE_TITLE = 0,
    CURSOR_MODE_LEVEL_SELECT = 1,
    CURSOR_MODE_HANDOVER_SEL = 2,
} CURSOR_MODE;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsSeqHandle_t jmsSeqHandle_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;
typedef struct titleAlphaTable_t titleAlphaTable_t;
typedef struct titleCursor_t titleCursor_t;
typedef struct titleData_t titleData_t;
typedef struct titleSprTable_t titleSprTable_t;

struct titleCursor_t {
    u32 Stat;
    s32 Timer;
    s32 Timer2;
    s32 ItemAlpha[5];
    s32 ScaleTimer;
    s32 Index;
    s32 ConfigIndex;
    s32 LevelIndex;
    s32 LastPush;
};

struct titleData_t {
    s32 Flag;
    s32 Mode;
    jmsSeqHandle_t *SeqHandle;
    jmsSeqUnit_t *pSeqUnit;
    s32 Timer;
    s32 SkipTimer;
    s32 WaitTimer;
    s32 AnimTimer;
    dds3ProcessID_t *PmvPID;
    titleCursor_t *Cursor;
    s32 FadeOut;
    s32 MoviePlayWait;
    s32 MovieCounter;
    s32 MovieAlpha;
    s32 MovieSkipFlag;
    s32 MovieIndex;
    s32 AdvTableIndex;
    s32 AdvSkipFlag;
    s32 Count;
    s32 ScrollTop;
    bool MenuReturn;
    s32 dlcMsgNum;
    s32 dlcMesDrowFlag;
    s32 dlcMesSave;
    bool LevelCheckReturn;
    bool inMenu;
    s32 menu_plus;
    s32 oldIndex;
    bool fadeChack;
    bool skipFlag;
    bool saveFlag;
    s32 WorkStat;
    s32 WorkstatCnt;
    bool licenceFade;
    s32 fadeStep;
    bool HoverCheckReturn;
};

struct titleSprTable_t {
    s32 Array;
    s32 SprNo;
    s32 X;
    s32 Y;
};

struct titleAlphaTable_t {
    s32 Frame;
    s32 Alpha;
};

extern s32 *titleAdvMovieList;
extern s32 *titleMoveList;
extern s32 m_playMode;
extern char *title_scene_name;
extern jmsSeqUnit_t *titleSeqUnit;
extern titleSprTable_t *titleSprTable;
extern s32 handover_type;

s32 TitleHandOverInit(dds3ProcessID_t *PID);
s32 TitleHandOverDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleHandOverCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleHandOverDrawProcess(dds3ProcessID_t *PID);
void TitleLoadTitleUI(dds3ProcessID_t *ParentPID, titleData_t *pData);
s32 TitleCheckTitleUi(titleData_t *pData);
void TitleFreeTitleUi(titleData_t *pData);
void TitleUnloadTitleUi(void);
dds3ProcessFunc_t TitleFirstCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleFirstCalcProcess2(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleFirstCalcProcess3(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleFirstDrawProcess(dds3ProcessID_t *PID);
s32 TitleCesaInit(dds3ProcessID_t *PID);
s32 TitleCesaDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleCesaCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleCesaDrawProcess(dds3ProcessID_t *PID);
s32 TitleLightWarningInit(dds3ProcessID_t *PID);
s32 TitleLightWarningDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleLightWarningCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleLightWarningDrawProcess(dds3ProcessID_t *PID);
s32 TitleAtlusLogoInit(dds3ProcessID_t *PID);
s32 TitleAtlusLogoDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleAtlusLogoCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleAtlusLogoDrawProcess(dds3ProcessID_t *PID);
s32 TitleMovieInit(dds3ProcessID_t *PID);
s32 TitleMovieDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleMovieCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleMovieDrawProcess(dds3ProcessID_t *PID);
s32 MainInit(dds3ProcessID_t *PID);
s32 MainDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t MainCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t MainDrawProcess(dds3ProcessID_t *PID);
s32 MainSubInit(dds3ProcessID_t *PID);
s32 MainSubDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t MainSubCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t MainSubDrawProcess(dds3ProcessID_t *PID);
bool MainTitleFirstSave(titleData_t *data);
s32 TitleEndWaitInit(dds3ProcessID_t *PID);
s32 TitleEndWaitDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleEndWaitCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleEndWaitDrawProcess(dds3ProcessID_t *PID);
s32 TitleConfigInit(dds3ProcessID_t *PID);
s32 TitleConfigDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleConfigCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleConfigDrawProcess(dds3ProcessID_t *PID);
s32 TitleAdvertiseInit(dds3ProcessID_t *PID);
s32 TitleAdvertiseDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleAdvertiseCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleAdvertiseDrawProcess(dds3ProcessID_t *PID);
s32 TitleSettingNoteInit(dds3ProcessID_t *PID);
s32 TitleSettingNoteDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleSettingNoteCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleSettingNoteDrawProcess(dds3ProcessID_t *PID);
s32 TitleLevelInit(dds3ProcessID_t *PID);
s32 TitleLevelDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleLevelCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleLevelDrawProcess(dds3ProcessID_t *PID);
s32 TitleLevelCheckInit(dds3ProcessID_t *PID);
s32 TitleLevelCheckDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleLevelCheckCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleLevelCheckDrawProcess(dds3ProcessID_t *PID);
s32 TitleDLCInit(dds3ProcessID_t *PID);
s32 TitleDLCDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleDLCCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleDLCDrawProcess(dds3ProcessID_t *PID);
s32 TitleCreditsInit(dds3ProcessID_t *PID);
s32 TitleCreditsDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleCreditsCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleCreditsDrawProcess(dds3ProcessID_t *PID);
s32 TitleRightsNoteInit(dds3ProcessID_t *PID);
s32 TitleRightsNoteDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleRightsNoteCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t TitleRightsNoteDrawProcess(dds3ProcessID_t *PID);
s32 TitleCheckNumArea(s32 Val, s32 Min, s32 Max);
s32 TitleCalcAlphaRate(s32 NowFrame, titleAlphaTable_t *pTable, s32 TableNums);
void TitleInitCursor(titleCursor_t *pCursor);
void TitleConfigSub(titleCursor_t *pCursor, s32 Mode);
s32 TitleCalcCursor(dds3ProcessID_t *PID, titleCursor_t *pCursor, CURSOR_MODE _step);
s32 TitleMovieStop(titleData_t *pData);
s32 TitleMoviePlay(s32 MovieNo, s32 Length, s32 FadeFrame, s32 Mode, titleData_t *pData);
s32 TitleAt3Load(titleData_t *pData, TITLEenum bgmId);
void TitleAt3Play(titleData_t *pData);
void TitleAt3PlayLoop(titleData_t *pData);
void TitleCreditsAt3Stop(titleData_t *pData);
void TitleAt3Stop(titleData_t *pData);
void TitlePlayMovieSe(void);
void TitleStopMovieSe(void);
void TitleGoMain(titleData_t *pData);
void TitleDrawLogo(titleData_t *pData);
void TitleNewGameStart(s32 iMode);
titleData_t *TitleInit(s32 Mode);
void TitleDestroy(dds3ProcessID_t *PID);
void TitleProcessStart(s32 Mode);
void TitleProcessEnd(void);
bool TitleProcessCheck(void);
