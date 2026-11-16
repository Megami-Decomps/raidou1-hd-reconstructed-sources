#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

typedef dds3ProcessFunc_t (*jmsFuncDelegate)(dds3ProcessID_t *ID);
