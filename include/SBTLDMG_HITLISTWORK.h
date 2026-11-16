#pragma once
#include "types.h"

typedef struct SBTLDMG_HITLISTWORK SBTLDMG_HITLISTWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;

struct SBTLDMG_HITLISTWORK {
    s32 num;
    s32 serialID;
    s32 serialID2;
    SBTLDMG_HITWORK *wk;
};
