#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

void nmeSetBuffer(dds3ProcessID_t *proc);
dds3ProcessID_t *Start(void);
void Finish(dds3ProcessID_t *proc);
