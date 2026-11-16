#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessFunc_t dds3DebugConsProcess(dds3ProcessID_t *id);
void dds3DebugConsShutdown(dds3ProcessID_t *id);
void dds3Printf(char *str, void *LegacyParamArray);
void dds3DebugConsOpenPrintf(char *str, void *LegacyParamArray);
