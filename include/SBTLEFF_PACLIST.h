#pragma once
#include "types.h"
#include "EFFPAC_ST.h"
#include "SKLID.h"

typedef struct SBTLEFF_PACDATAWORK SBTLEFF_PACDATAWORK;
typedef struct SBTLEFF_PACLIST SBTLEFF_PACLIST;
typedef struct pacFileHandle_t pacFileHandle_t;

struct SBTLEFF_PACLIST {
    pacFileHandle_t *pacHandle;
    void *pData;
    s32 num;
    s16 gstat;
    EFFPAC_ST status;
    SKLID skillID;
    u32 SMGID;
    SBTLEFF_PACDATAWORK *pwk;
};
