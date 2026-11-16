#pragma once
#include "types.h"

typedef struct SBTLEFF_DATAWORK SBTLEFF_DATAWORK;
typedef struct fileHandle_t fileHandle_t;
typedef struct plistHandle_t plistHandle_t;
typedef struct plistHandle_t_Resource plistHandle_t_Resource;

struct SBTLEFF_DATAWORK {
    plistHandle_t_Resource *pData;
    fileHandle_t *hFile;
    plistHandle_t *hPartsList;
};
