#pragma once
#include "types.h"

typedef struct EFFPDATA_WORK EFFPDATA_WORK;
typedef struct SBTLEFF_PACDATAWORK SBTLEFF_PACDATAWORK;
typedef struct SBTLSKLHIT_PACLIST SBTLSKLHIT_PACLIST;
typedef struct plistHandle_t plistHandle_t;
typedef struct plistHandle_t_Resource plistHandle_t_Resource;

struct SBTLEFF_PACDATAWORK {
    plistHandle_t_Resource *pData;
    plistHandle_t *hPartsList;
    s32 flg;
    EFFPDATA_WORK *wk;
    SBTLSKLHIT_PACLIST *hwk;
};
