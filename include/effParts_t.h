#pragma once
#include "types.h"
#include "EFFPARTS_CTG.h"

typedef struct effPartsData_t effPartsData_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effParts_t effParts_t;

struct effParts_t {
    u32 version;
    EFFPARTS_CTG categ;
    effPartsHandle_t *pHandle;
    effPartsData_t *param;
    effPartsData_t *data;
};
