#pragma once
#include "types.h"
#include "REPORT_TYPE.h"

typedef struct DevilReportStok_t DevilReportStok_t;

struct DevilReportStok_t {
    s32 num;
    REPORT_TYPE type;
    s32 Reward;
    s32 Count;
};
