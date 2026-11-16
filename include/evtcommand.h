#pragma once
#include "types.h"
#include "basic.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;

dds3Basic_t *evtSearchBasic(BASIC_TYPE type, s32 serial);
void evtLipsExecFunction(s32 unit_uniqid, s32 motion_no);
void evtLipsStopFunction(s32 motion_no);
dds3ModelHandle_t *evtGetLipModel(s32 unit_uniqid);
