#pragma once
#include "types.h"
#include "TLP_FLAG.h"

typedef struct ctexlHandle_t_Resource ctexlHandle_t_Resource;

struct ctexlHandle_t_Resource {
    TLP_FLAG header_flag;
    u32 *pItemList_wait;
};
