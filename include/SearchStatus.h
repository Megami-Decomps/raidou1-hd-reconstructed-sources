#pragma once
#include "types.h"

typedef enum {
    SearchStatus_Success = 0,
    SearchStatus_Create = 1,
    SearchStatus_NoHit = 2,
    SearchStatus_Limit = 3,
} SearchStatus;
