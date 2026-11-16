#pragma once
#include "types.h"
#include "REPORT_TYPE.h"

typedef struct DvlReportPass DvlReportPass;

struct DvlReportPass {
    REPORT_TYPE type;
    s32 itmID;
    s32 cnt;
};
