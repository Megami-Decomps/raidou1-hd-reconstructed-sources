#pragma once
#include "types.h"

typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;

void dds3EffectDelete(dds3Effect_Filter_t *pFilter);
void Execute(dds3Effect_Filter_t *pFilter);
