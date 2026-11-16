#pragma once
#include "types.h"
#include "SBTLUNIT_EX.h"
#include "SBTLUNIT_ST.h"
#include "sbtlsm.h"

typedef enum {
    SBTLSM_ST_INIT = 0,
    SBTLSM_ST_PROC = 1,
    SBTLSM_ST_END = 2,
    SBTLSM_ST_EXIT = 3,
    SBTLSM_ST_MAX = 4,
} SBTLSM_ST;

typedef struct SBTLSM_WORK SBTLSM_WORK;

struct SBTLSM_WORK {
    SBTLSM_ST gstat;
    SBTLSM mode;
    s32 counter;
    s32 cmpcounter;
    s32 listID;
    s32 devilid;
    s32 lv;
    SBTLUNIT_ST status;
    SBTLUNIT_EX exsts;
    s32 sklid;
    s32 raceid;
    u8 side;
    s32 ofs_x;
    s32 ofs_y;
    s32 alpha;
    char *fontbuff;
    char *fontbuff2;
    SBTLSM_WORK *prev;
    SBTLSM_WORK *next;
};
