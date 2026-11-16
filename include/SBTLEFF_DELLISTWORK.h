#pragma once
#include "types.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"

typedef enum {
    SBTLEFF_DELST_NONE = 0,
    SBTLEFF_DELST_PROC = 1,
    SBTLEFF_DELST_EXIT = 2,
    SBTLEFF_DELST_END = 3,
} SBTLEFF_DELST;

typedef struct SBTLEFF_DELLISTWORK SBTLEFF_DELLISTWORK;
typedef struct SBTLEFF_DELWORK SBTLEFF_DELWORK;

struct SBTLEFF_DELWORK {
    SBTLEFF_DELST gstat;
    SKLID sklid;
    s32 GroupID;
    SBTLUNIT_SIDE side;
    SBTLEFF_DELWORK *prev;
    SBTLEFF_DELWORK *next;
};

struct SBTLEFF_DELLISTWORK {
    s32 serial;
    s32 num;
    SBTLEFF_DELWORK *dwk;
};
