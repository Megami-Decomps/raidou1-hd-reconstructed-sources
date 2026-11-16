#pragma once
#include "types.h"

typedef enum {
    GOH_RANK_MINMAX_MIN = 0,
    GOH_RANK_MINMAX_MID = 1,
    GOH_RANK_MINMAX_MAX = 2,
} GOH_RANK_MINMAX;

typedef struct gohDevilData_t gohDevilData_t;
typedef struct gohSortedDevilList_t gohSortedDevilList_t;

struct gohDevilData_t {
    s32 KudaRace;
    s32 Level;
    s32 DevilID;
    GOH_RANK_MINMAX MinMax;
};

struct gohSortedDevilList_t {
    s32 Nums;
    gohDevilData_t *pData[544];
};
