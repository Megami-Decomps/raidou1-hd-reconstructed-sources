#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessFunc_t UnitEdit(dds3ProcessID_t *ID);
void dds3ExitUnitEdit(dds3ProcessID_t *ID);
