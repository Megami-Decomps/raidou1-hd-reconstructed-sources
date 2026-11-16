#pragma once
#include "types.h"
#include "SaveResultType.h"
#include "kernel.h"

typedef struct __MC_GLOBALWORK __MC_GLOBALWORK;
typedef struct __MC_SELECTCURSORWORK __MC_SELECTCURSORWORK;
typedef struct __MC_UDCURSORWORK __MC_UDCURSORWORK;
typedef struct dds3AdditionWork_t dds3AdditionWork_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct dds3SystemWork_t dds3SystemWork_t;

typedef dds3ProcessFunc_t (*slQueryYesFuncDelegate)(void);
typedef dds3ProcessFunc_t (*slQueryNoFuncDelegate)(void);
typedef dds3ProcessFunc_t (*slSaveWriteFile_endFuncDelegate)(void);
typedef dds3ProcessFunc_t (*nextFuncDelegate)(void);

struct __MC_GLOBALWORK {
    u8 st;
    s32 cnt;
    s32 cursorcnt;
    s32 alpha;
    u8 mvflg;
    s32 mv_y;
    s32 u_alpha;
    s32 d_alpha;
};

struct __MC_UDCURSORWORK {
    s32 cnt;
    s32 alpha;
};

struct __MC_SELECTCURSORWORK {
    s32 alpha;
    u8 st;
    s32 counter;
    s32 yalpha;
};

extern u8 saveVer;
extern dds3ProcessFunc_t slProcPtr;
extern slQueryYesFuncDelegate slQueryYesFunc;
extern slQueryNoFuncDelegate slQueryNoFunc;
extern slSaveWriteFile_endFuncDelegate slSaveWriteFile_endFunc;
extern nextFuncDelegate slHitAnyKeyNextFunc;
extern nextFuncDelegate slExitWaitNextFunc;
extern __MC_GLOBALWORK *__mc_wk;
extern __MC_SELECTCURSORWORK *__mc_scwk;
extern __MC_UDCURSORWORK *__mc_udcwk;
extern s32 loadMode;
extern dds3SystemWork_t *SystemWork;
extern dds3AdditionWork_t *AdditionWork;
extern s32 gslErrorKeyNoWait;
extern s32 streamingMes;
extern void *saveloadSystem;
extern s32 bakCursorSelect;
extern s32 gslInfoCode;
extern dds3ProcessFunc_t AutoSaveFunc;
extern AUTOSAVE_PROC AutoSaveProc;
extern dds3ProcessFunc_t SuspendFunc;
extern SUSPEND_PROC SuspendProc;
extern s32 gslExitType;

s32 slGetSaveDataMax(void);
u8 *slUnicodeToIndexByte2(char *str);
char *slByteToString(u8 *str);
void getPlayTimeToInt(u32 time, u32 **getTime);
void slGslInfoClear(void);
SaveResultType slGetSaveResultType(void);
dds3ProcessFunc_t slSystemDataProc(void);
void slInfoBackUp(void);
void slInfoBackUpClear(void);
void slInfoBackUpRestore(void);
dds3ProcessFunc_t slMsgWaitProc(void);
dds3ProcessFunc_t slEnterMsgWaitProc(dds3ProcessFunc_t func);
void slShutDownProcess(dds3ProcessID_t *id);
void mcMakeFileName(char **path, s32 num);
void slSetInfo(s32 id);
void fmProcTrigSequence(s32 mode);
void checkFirstCursor(s32 mode);
s32 checkSelectCursor(s32 start);
bool fmSlotCheck(s32 loop);
void fmShutDownFade(void);
void fmShutDown(void);
bool fmShutDown2(void);
s32 fmProcessChk(void);
s32 slGetExitType(void);
s32 slGetExitTitle(void);
s32 slGetExitMode(void);
void slSetTmnlID(s32 type, s32 id);
s32 slGetInfo(void);
void slSetKayWait(void);
void slSuspendKill(void);
dds3ProcessFunc_t slSuspendProc(void);
dds3ProcessFunc_t slAutoSaveProc(void);
void slInitAutoSave(void);
bool slUpdateAutoSave(void);
void slInitSuspend(void);
s32 slUpdateSuspend(void);
bool slSaveDataCheck(void);
