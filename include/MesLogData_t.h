#pragma once
#include "types.h"

typedef struct MesLog MesLog;
typedef struct MesLogData_t MesLogData_t;
typedef struct MesSkip MesSkip;

struct MesLog {
    MesLogData_t *data;
    s32 enable_cnt;
    s32 enable_id[8];
    void *logList;
};

struct MesLogData_t {
    MesSkip *mesSkip;
    MesLog *mesLog;
};

struct MesSkip {
    MesLogData_t *data;
    bool enable;
    s32 msg1st;
    s32 restart;
    bool noSkipEnd;
};
