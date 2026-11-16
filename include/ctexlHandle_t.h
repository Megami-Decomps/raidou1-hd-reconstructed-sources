#pragma once
#include "types.h"
#include "TLP_FLAG.h"

typedef struct ctexlHandle_t ctexlHandle_t;
typedef struct effCtexHandle_t effCtexHandle_t;

struct ctexlHandle_t {
    TLP_FLAG header_flag;
    u32 *pItemList_wait;
    effCtexHandle_t *phCtex;
    u32 frameAll;
    u32 use;
    s32 current;
};
