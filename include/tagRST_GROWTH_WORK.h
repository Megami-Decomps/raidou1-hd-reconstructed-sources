#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagRST_GROWTH_WORK tagRST_GROWTH_WORK;

struct tagRST_GROWTH_WORK {
    dds3ProcessID_t *giftPID;
    u8 *pDatScr;
    s32 scrReq;
    dds3ProcessID_t *scrPID;
    s8 step;
    s8 step2;
    s8 step3;
    u32 cntFade;
    s8 type;
    s8 dummy;
    s16 count;
    u32 flag;
    s32 getSklCnt;
    s32 getSklStep;
    bool skillCheck;
    s32 ofcIndex;
    s32 omoideSetPreHp;
    s32 omoideSetAddHp;
};
