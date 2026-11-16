#pragma once
#include "types.h"

typedef struct dds3Effect_PartialMultiFilterParam_t dds3Effect_PartialMultiFilterParam_t;
typedef struct effPartialMultiFilterHandle_t effPartialMultiFilterHandle_t;

struct effPartialMultiFilterHandle_t {
    dds3Effect_PartialMultiFilterParam_t *param;
};
