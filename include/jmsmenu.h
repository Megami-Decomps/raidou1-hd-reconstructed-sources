#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern bool selectFlag;
extern bool MenuActive;
extern s32 TITLEMODE;
extern bool TITLEFADEOUT;
extern bool TITLEFADEIN;
extern u32 *MenuFlag;
extern dds3ProcessID_t *g_mainPID;

s32 jmsAnimFunc(s32 mode);
void jmsUniDrawMenu(dds3ProcessID_t *PID);
s32 jmsGetSelectIndex(bool root_calc);
void jmsStart(void);
void jmsSetFocus(bool a_bFocus);
void jmsCallDrawBack(void);
void ProcessStart(void);
void ProcessEnd(void);
bool ProcessCheck(void);
void MenuProcessStop(void);
void MenuProcessRestart(void);
void jmsDisableSelect(s32 MenuID);
void jmsAddTalkTarget(s32 No, char *pStr);
s32 jmsCheckCyousaFileEnable(s32 CyousaFileIndex);
s32 jmsCheckMovePrev(void);
s32 jmsGetCursorPosID(void);
