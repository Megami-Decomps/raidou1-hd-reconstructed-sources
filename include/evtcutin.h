#pragma once
#include "types.h"
#include "EVT_PICTURE_TYPE.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern void *pFile;

void evtFirstInit(void);
bool evtChkUID(u32 UID);
dds3ProcessID_t *evtGetPIDfromUID(u32 UID);
void evtDelProcess(u32 UID);
dds3ProcessID_t *evtStart(s32 *pNowFrame, dds3ProcessID_t *ParentPID, s32 X, s32 Y, DDS3_PRIORITY Pri, s32 Start, s32 End, EVT_PICTURE_TYPE Type, u32 UID);
dds3ProcessID_t *evtStartNakamaCutInBG(s32 x, s32 y);
dds3ProcessID_t *evtStartCommand(dds3ProcessID_t *ParentPID, s32 X, s32 Y, s32 Type, u32 UID);
void evtEndCommand(dds3ProcessID_t *PID);
