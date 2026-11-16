#pragma once
#include "types.h"

typedef enum {
    SortId_None = 0,
    SortId_CmpKuda = 1,
    SortId_CmpSkl = 2,
    SortId_CmpSyouhi = 3,
    SortId_CmpKichou = 4,
    SortId_CmpMasyou = 5,
    SortId_CmpHaveSkl = 6,
    SortId_CmpGorieki = 7,
    SortId_CmpSword = 8,
    SortId_KonItemBuy = 9,
    SortId_KonItemSale = 10,
    SortId_CombResult = 11,
    SortId_CombCmb = 12,
    SortId_Max = 13,
} SortId;

typedef struct SortTbl SortTbl;

struct SortTbl {
    SortId sortId;
    void *sortData;
};
