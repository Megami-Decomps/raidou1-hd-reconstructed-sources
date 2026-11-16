#pragma once
#include "types.h"

typedef struct dds3Basic_t dds3Basic_t;

dds3Basic_t *dds3EventBasicAdd(u32 serialID, void *pData, char *pName);
void *dds3EventBasicGetResource(dds3Basic_t *pBasic);
