#pragma once
#include "types.h"

typedef struct SBTLUNIT_LISTWK SBTLUNIT_LISTWK;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct SBTLUNIT_LISTWK {
    s32 ID;
    SBTLUNIT_WORK *pUnit;
};

struct SBTLUNIT_LISTWORK {
    s32 number;
    s32 count;
    SBTLUNIT_LISTWK *pUnitL;
};
