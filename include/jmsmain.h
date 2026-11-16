#pragma once
#include "types.h"
#include "kernel.h"

typedef struct REPORT_READ_FLAG_CLASS REPORT_READ_FLAG_CLASS;
typedef struct dds3ProcessID_t dds3ProcessID_t;

struct REPORT_READ_FLAG_CLASS {
    bool READ_FLAG;
    s32 UPDATE_FLAG;
};

extern REPORT_READ_FLAG_CLASS *REPORT_READ_FLAG;
extern s32 NarumiIsHere;

void jmsReportReadFlagUpdate(s32 FileID);
bool jmsReportReadFlagChack(s32 FileID);
s32 jmsCheckScrRun(dds3ProcessID_t *PID);
dds3ProcessFunc_t jmsRootWaitCalcProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t jmsRootWaitDrawProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t jmsRootWaitUpdateProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t EndProcess(dds3ProcessID_t *PID);
s32 jmsCheckNarumiIsHere(void);
