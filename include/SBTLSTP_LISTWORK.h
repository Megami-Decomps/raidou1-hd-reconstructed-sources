#pragma once
#include "types.h"
#include "SBTLSTP_ID.h"

typedef enum {
    SBTLSTP_MODE_INIT = 0,
    SBTLSTP_MODE_PROC = 1,
    SBTLSTP_MODE_EXIT = 2,
    SBTLSTP_MODE_END = 3,
    SBTLSTP_MODE_MAX = 4,
} SBTLSTP_MODE;

typedef struct SBTLSTP_LISTWORK SBTLSTP_LISTWORK;
typedef struct SBTLSTP_WORK SBTLSTP_WORK;

struct SBTLSTP_WORK {
    sdfVector4_t pos;
    SBTLSTP_MODE mode;
    u32 status;
    SBTLSTP_ID id;
    s32 counter;
    s32 counterMax;
    s32 alpha;
    f32 scale;
    f32 y;
    f32 spd;
    s32 ListID;
    s32 stpBSTF;
    bool IsSprit;
    SBTLSTP_WORK *prev;
    SBTLSTP_WORK *next;
};

struct SBTLSTP_LISTWORK {
    s32 num;
    SBTLSTP_WORK *wk;
};
