#pragma once
#include "types.h"

typedef struct SBTLITEM_DATA SBTLITEM_DATA;
typedef struct SBTLITEM_LISTWORK SBTLITEM_LISTWORK;

struct SBTLITEM_DATA {
    s32 id;
    s32 num;
};

struct SBTLITEM_LISTWORK {
    s32 num;
    SBTLITEM_DATA *data;
};
