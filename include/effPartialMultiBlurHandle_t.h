#pragma once
#include "types.h"

typedef struct dds3Effect_PartialMultiBlurParam_t dds3Effect_PartialMultiBlurParam_t;
typedef struct effPartialMultiBlurHandle_t effPartialMultiBlurHandle_t;

struct effPartialMultiBlurHandle_t {
    dds3Effect_PartialMultiBlurParam_t *param;
};
