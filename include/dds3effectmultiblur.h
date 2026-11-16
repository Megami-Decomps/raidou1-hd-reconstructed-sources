#pragma once
#include "types.h"
#include "effblur_filter.h"

typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;

void Execute(dds3Effect_Blur_t *pBlur, void *hTex, EFFBF_XY type);
