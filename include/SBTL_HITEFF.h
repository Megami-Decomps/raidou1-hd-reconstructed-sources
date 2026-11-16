#pragma once
#include "types.h"

typedef struct SBTL_HITEFF SBTL_HITEFF;

struct SBTL_HITEFF {
    bool bUse;
    s32 effID;
    SBTL_HITEFF *prev;
    SBTL_HITEFF *next;
};
