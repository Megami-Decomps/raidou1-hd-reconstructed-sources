#pragma once
#include "types.h"

typedef struct Standard Standard;
typedef struct effOption_Resource effOption_Resource;
typedef struct effPartsData_t effPartsData_t;

struct Standard {
    u32 version;
    u16 categ;
    effPartsData_t *param;
    effOption_Resource *option;
    effPartsData_t *data;
};
