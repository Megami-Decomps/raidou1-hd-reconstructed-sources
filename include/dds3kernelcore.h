#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

void Init(void);
void PadEi(void);
s32 dds3GetProcessCount(u32 type);
dds3ProcessID_t *dds3SearchProcessNumber(u32 type, s32 n);
bool dds3ProcessMain(void);
dds3ProcessID_t *dds3StartProcess(char *namestr, DDS3_PRIORITY priority, s32 starttimer, s32 shutdowntimer, dds3ProcessFunc_t processfunc, shutdownfuncDelegate shutdownfunc, void *data);
bool dds3KillProcessName(char *name, s32 shutdowntimer);
bool dds3KillProcess(dds3ProcessID_t *id, s32 shutdowntimer);
void dds3EndProcess(dds3ProcessID_t *id);
u32 dds3GetProcessStat(dds3ProcessID_t *id);
dds3ProcessID_t *dds3SearchProcessName(char *namestr);
dds3ProcessID_t *dds3SearchProcessPriority(DDS3_PRIORITY priority);
bool dds3ExistProcess(dds3ProcessID_t *id);
u32 dds3GetProcessRunTime(dds3ProcessID_t *id);
void dds3SetProcessData(dds3ProcessID_t *id, void *data);
void *dds3GetProcessData(dds3ProcessID_t *id);
void dds3LinkProcess(dds3ProcessID_t *parent, dds3ProcessID_t *target);
void dds3SetProcessFlag(dds3ProcessID_t *target, u32 flag, s32 type);
void dds3ResetProcessFlag(dds3ProcessID_t *target, u32 flag, s32 type);
dds3ProcessID_t *dds3SearchProcessID(s32 id);
void dds3UnloadSceneAsync(void *mv);
void dds3UnloadUnusedAssets(bool req);
