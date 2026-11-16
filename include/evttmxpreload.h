#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdfIVector2_t sdfIVector2_t;

extern void *pBgTbl;

s32 evtGetFileNums(s32 EventNo);
bool evtChkLoad(bool Mode);
bool evtRequest(u32 UID, s32 ReqFrame);
void *evtGetTex(u32 UID);
void *evtGetMaskTex(u32 UID);
bool evtGetMaskOfs(u32 UID, sdfIVector2_t *pOfs);
bool evtProcessStart(dds3ProcessID_t *ParentPID, DDS3_PRIORITY Priority);
void evtProcessEnd(void);
void evtTexFree(void);
