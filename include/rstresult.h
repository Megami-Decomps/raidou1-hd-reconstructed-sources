#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;

extern jmsSeqUnit_t *gohSeqUnit[4];

s32 rstEndInit(dds3ProcessID_t *PID);
s32 rstEndDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstEndCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstEndDrawProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstEndUpdateProcess(dds3ProcessID_t *PID);
s32 rstBtlEndWaitInit(dds3ProcessID_t *PID);
s32 rstBtlEndWaitDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstBtlEndWaitCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstBtlEndWaitDrawProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstBtlEndWaitUpdateProcess(dds3ProcessID_t *PID);
s32 rstLvUpWaitInit(dds3ProcessID_t *PID);
s32 rstLvUpWaitDestroy(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstLvUpWaitCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstLvUpWaitDrawProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstLvUpWaitUpdateProcess(dds3ProcessID_t *PID);
s32 rstCheckLevelUp(void *pData);
s32 rstCallLoadMapResourceFunc(void *pData);
dds3ProcessFunc_t rstCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstDrawProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t rstUpdateProcess(dds3ProcessID_t *PID);
