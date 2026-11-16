#pragma once
#include "types.h"

typedef enum {
    EFFPARTSLIST_PARTS_SCALE = 1,
    EFFPARTSLIST_PARTS_HIDE = 2,
} EFFPARTSLIST_PARTS;

typedef struct effPartsListItemParams_t effPartsListItemParams_t;
typedef struct effPartsListPose_t effPartsListPose_t;

struct effPartsListItemParams_t {
    effPartsListPose_t *pose;
    s32 start;
    EFFPARTSLIST_PARTS flag;
    s8 dirPtrH;
    s8 dirPtrD;
    s8 dirPtrR;
};
