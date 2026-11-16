#pragma once
#include "types.h"
#include "SortType.h"

#define SORT_SET_MAX 10

typedef struct MenuCsrUnity MenuCsrUnity;
typedef struct SortSaveData SortSaveData;

struct SortSaveData {
    SortType adoptionType;
    MenuCsrUnity *csr;
    bool sortSets[10];
};
