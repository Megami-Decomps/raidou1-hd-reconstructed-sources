#pragma once
#include "types.h"

typedef struct SBTLEFF_LISTWORK SBTLEFF_LISTWORK;
typedef struct SBTLEFF_WORK SBTLEFF_WORK;

struct SBTLEFF_LISTWORK {
    s32 serial;
    s32 serialID2;
    s32 num;
    SBTLEFF_WORK *wk;
};
