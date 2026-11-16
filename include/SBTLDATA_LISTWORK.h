#pragma once
#include "types.h"

typedef struct SBTLDATA_LISTWORK SBTLDATA_LISTWORK;
typedef struct SBTLDATA_WORK SBTLDATA_WORK;

struct SBTLDATA_WORK {
    void *pdata;
    s32 size;
};

struct SBTLDATA_LISTWORK {
    char *filename;
    SBTLDATA_WORK *list[22];
};
