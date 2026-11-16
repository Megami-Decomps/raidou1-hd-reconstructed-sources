#pragma once
#include "types.h"

typedef struct SBTLEFF_EFFTIME SBTLEFF_EFFTIME;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLSKLHIT_PACDATAWORK SBTLSKLHIT_PACDATAWORK;
typedef struct plistHandle_t plistHandle_t;
typedef struct plistHandle_t_Resource plistHandle_t_Resource;

struct SBTLSKLHIT_PACDATAWORK {
    void *BpData;
    plistHandle_t *hPartsList;
    plistHandle_t_Resource *EpData;
    SBTLSKILLHIT_TBL *wk;
    SBTLEFF_EFFTIME *time;
};
