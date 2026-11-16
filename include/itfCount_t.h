#pragma once
#include "types.h"

typedef struct itfCountCB_t itfCountCB_t;
typedef struct itfCount_t itfCount_t;

struct itfCountCB_t {
    s32 pDat;
    s32 init;
    s32 min;
    s32 max;
    u16 flag;
    s16 type;
};

struct itfCount_t {
    itfCountCB_t *cb[2];
    s32 num;
    s32 calc;
    s32 unit;
    s32 seNo;
    s32 blank;
    s32 frame;
    s32 count;
};
