#pragma once
#include "types.h"

typedef struct SBTLDMG_ANIMWORK SBTLDMG_ANIMWORK;
typedef struct SBTLDMG_LISTWORK SBTLDMG_LISTWORK;
typedef struct SBTLDMG_UNITWORK SBTLDMG_UNITWORK;

struct SBTLDMG_UNITWORK {
    SBTLDMG_ANIMWORK *wk;
};

struct SBTLDMG_LISTWORK {
    s32 num;
    SBTLDMG_UNITWORK *unit;
};
