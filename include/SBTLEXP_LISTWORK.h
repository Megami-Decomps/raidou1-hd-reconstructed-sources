#pragma once
#include "types.h"

typedef enum {
    SBTLEXP_ST_INIT = 0,
    SBTLEXP_ST_PROC = 1,
    SBTLEXP_ST_END = 2,
    SBTLEXP_ST_MAX = 3,
} SBTLEXP_ST;

typedef struct SBTLEXP_LISTWORK SBTLEXP_LISTWORK;
typedef struct SBTLEXP_WORK SBTLEXP_WORK;

struct SBTLEXP_WORK {
    u8 side;
    s16 mode;
    SBTLEXP_ST status;
    s32 para;
    s32 counter;
    s32 alpha;
    s32 x;
    s32 y;
    SBTLEXP_WORK *prev;
    SBTLEXP_WORK *next;
};

struct SBTLEXP_LISTWORK {
    s16 num;
    s16 level;
    s16 counter;
    f32 ganpon;
    f32 riritu;
    s16 za_cnt;
    s16 mode;
    s32 para;
    s32 alpha;
    s32 ralpha;
    s32 rcounter;
    s32 o_alpha;
    s16 o_counter;
    SBTLEXP_WORK *ewk;
};
