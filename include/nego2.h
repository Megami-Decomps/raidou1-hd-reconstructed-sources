#pragma once
#include "types.h"

typedef enum {
    NEGO2_REQMONEY = 0,
    NEGO2_REQITEM = 1,
    NEGO2_REQMAG = 2,
    NEGO2_REQHP = 3,
    NEGO2_REQNAKAMA = 4,
    NEGO2_REQMUSHI = 5,
    NEGO2_REQHOUGYOKU = 6,
    NEGO2_REQNUM = 7,
} NEGO2;

typedef enum {
    NEGO2__REQ_MONEY = 1,
    NEGO2__REQ_ITEM = 2,
    NEGO2__REQ_MAG = 3,
    NEGO2__AGREE = 4,
    NEGO2__REQUEST = 5,
    NEGO2__REQ_HP = 6,
    NEGO2__GIVE = 7,
    NEGO2__NOTGIVE = 8,
    NEGO2__NOTHAVE = 9,
    NEGO2__REPEAT = 10,
    NEGO2__SATISFIED = 11,
    NEGO2__INTERRUPT = 12,
    NEGO2__REQ_NAKAMA = 13,
    NEGO2__REQ_MUSHI = 14,
    NEGO2__THROUGH = 15,
    NEGO2__CANSEL = 16,
} NEGO2_;
