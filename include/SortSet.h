#pragma once
#include "types.h"

typedef enum {
    TblSortType_Lv = 0,
    TblSortType_Hp = 1,
    TblSortType_Kuda = 2,
    TblSortType_Unregistered = 3,
    TblSortType_Comb = 4,
    TblSortType_Syllabary = 5,
    TblSortType_Max = 6,
} TblSortType;

typedef struct SortSet SortSet;

struct SortSet {
    TblSortType type;
    bool ascending;
};
