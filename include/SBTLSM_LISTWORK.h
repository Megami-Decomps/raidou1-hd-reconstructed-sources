#pragma once
#include "types.h"

typedef struct SBTLSM_LISTWORK SBTLSM_LISTWORK;
typedef struct SBTLSM_WORK SBTLSM_WORK;

struct SBTLSM_LISTWORK {
    s32 num;
    bool bLock;
    SBTLSM_WORK *dwk;
};
