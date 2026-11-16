#pragma once
#include "types.h"
#include "SKLID.h"

typedef enum {
    SklTypeSort_Battle = 0,
    SklTypeSort_Omoide = 1,
    SklTypeSort_Sousa = 2,
} SklTypeSort;

typedef struct SklMenu SklMenu;

struct SklMenu {
    bool use;
    s32 stockIndex;
    SKLID sklID;
    SklTypeSort sort;
};
