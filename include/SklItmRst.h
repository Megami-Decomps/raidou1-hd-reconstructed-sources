#pragma once
#include "types.h"

typedef enum {
    SklItmRst_None = 0,
    SklItmRst_Learn = 1,
    SklItmRst_TmpAdd = 2,
    SklItmRst_TmpUpdate = 4,
    SklItmRst_WakuMax = 8,
    SklItmRst_RsvUse = 16,
    SklItmRst_OmoideQuip = 32,
    SklItmRst_OmoideLog = 64,
    SklItmRst_NoneAdd = 128,
} SklItmRst;
