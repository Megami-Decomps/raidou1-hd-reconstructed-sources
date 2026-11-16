#pragma once
#include "types.h"
#include "kernel.h"

typedef enum {
    MsgLogType_MSG = 0,
    MsgLogType_SPK = 1,
    MsgLogType_VOICE = 2,
} MsgLogType;

typedef struct MesLogData_t MesLogData_t;
typedef struct SCRLOG SCRLOG;
typedef struct dds3ProcessID_t dds3ProcessID_t;

extern dds3ProcessID_t *GlobalPID;
extern char *PROCESS_NAME;
extern bool is_field;

dds3ProcessID_t *ProcessStart(void);
dds3ProcessFunc_t Process(dds3ProcessID_t *_PID);
void Destroy(dds3ProcessID_t *_PID);
bool ProcessCheck(void);
void ProcessEnd(void);
void NewGameInit(void);
bool AddLog(char *_msg, char *_spk, char *_voice);
void *GetLog(MsgLogType _type);
void SetLog(SCRLOG *_log);
void LogStart(dds3ProcessID_t *pid);
s32 GetListCount(void);
bool GetNoSkipEnd(void);
void SetNoSkipEnd(bool _active);
void RestartReset(void);
MesLogData_t *GetWk(void);
