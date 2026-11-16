#pragma once
#include "types.h"
#include "SKLID.h"

typedef enum {
    SBTLTALK_MODE_INIT = 0,
    SBTLTALK_MODE_SHIJI = 1,
    SBTLTALK_MODE_RES = 2,
    SBTLTALK_MODE_SUSPEND = 3,
    SBTLTALK_MODE_MAX = 4,
} SBTLTALK_MODE;

typedef struct SBTLPNL_WORK SBTLPNL_WORK;
typedef struct SBTLTALK_WORK SBTLTALK_WORK;

struct SBTLTALK_WORK {
    SBTLTALK_MODE mode;
    SBTLTALK_MODE modebk;
    u32 status;
    s32 talk_target;
    SKLID *sklid[4];
    SBTLPNL_WORK *sklpnlwk[4];
    s32 talk[4];
    SBTLPNL_WORK *talkpnlwk[4];
    s32 order_skillid;
};
