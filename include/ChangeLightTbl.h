#pragma once
#include "types.h"

typedef struct ChangeLightTbl ChangeLightTbl;
typedef struct LightTbl_t LightTbl_t;

struct ChangeLightTbl {
    s32 lightId;
    LightTbl_t *lightTbl;
    s32 filterIndex;
    s32 shadowsIndex;
};
