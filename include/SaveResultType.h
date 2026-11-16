#pragma once
#include "types.h"

typedef enum {
    SaveResultType_Success = 0,
    SaveResultType_NoSpace = 1,
    SaveResultType_DataBroken = 2,
    SaveResultType_Other = 3,
} SaveResultType;
