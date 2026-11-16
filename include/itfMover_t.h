#pragma once
#include "types.h"

typedef struct itfMoverCB_t itfMoverCB_t;
typedef struct itfMover_t itfMover_t;

struct itfMoverCB_t {
    f32 posx;
    f32 posy;
    f32 tgtx;
    f32 tgty;
    f32 movx;
    f32 movy;
    f32 rate;
    s8 wait[2];
    s16 frame;
};

struct itfMover_t {
    itfMoverCB_t *cb[4];
    s16 cb_cnt;
    s16 cb_num;
    s16 cnt;
    u16 flag;
    s32 total_cnt;
    s32 total_frm;
};
