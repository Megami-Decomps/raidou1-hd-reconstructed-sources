#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessFunc_t dds3FirstProcess(dds3ProcessID_t *id);
dds3ProcessFunc_t dds3DrawFirstProcess(dds3ProcessID_t *id);
dds3ProcessFunc_t dds3DrawProcess(dds3ProcessID_t *id);
dds3ProcessFunc_t dds3BasicMainProcess(dds3ProcessID_t *id);
dds3ProcessFunc_t dds3BasicDrawProcess(dds3ProcessID_t *id);
