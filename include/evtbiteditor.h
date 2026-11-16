#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

char *evtBitToZenkaku(char *text);
char *evtBitToHankaku(char *text);
dds3ProcessFunc_t dds3Process(dds3ProcessID_t *id);
