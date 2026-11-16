#pragma once
#include "types.h"

typedef enum {
    ENC1_TYPE_NONE = 0,
    ENC1_TYPE_ENEA = 1,
    ENC1_TYPE_ENEB = 6,
    ENC1_TYPE_ENEC = 7,
    ENC1_TYPE_GENA = 2,
    ENC1_TYPE_GENB = 3,
    ENC1_TYPE_GENC = 4,
    ENC1_TYPE_GEND = 5,
    ENC1_TYPE_GENE = 8,
    ENC1_TYPE_GENF = 9,
} ENC1_TYPE;

typedef struct SB_ENCOUNT1 SB_ENCOUNT1;

struct SB_ENCOUNT1 {
    ENC1_TYPE type;
    s8 pos;
    s16 devil;
    s8 groupID;
    s8 disp_max;
    s8 zan_num;
    s8 groupID2;
    s32 exflg;
};
