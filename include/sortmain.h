#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern dds3ProcessID_t *GlobalPID;
extern char *PROCESS_NAME;

dds3ProcessID_t *ProcessStart(void);
dds3ProcessFunc_t Process(dds3ProcessID_t *_PID);
void Destroy(dds3ProcessID_t *_PID);
bool LogProcessCheck(void);
void LogProcessEnd(void);
