#pragma once
#include "types.h"
#include "CutInType.h"

typedef struct evtCutInInfo evtCutInInfo;

struct evtCutInInfo {
    char *file_name;
    char *bundle_name;
    s32 ui_mode;
    CutInType cutInType;
};
