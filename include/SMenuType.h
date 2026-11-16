#pragma once
#include "types.h"

typedef struct SMenuType SMenuType;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct SMenuType {
    s32 No;
    sdatUnitWork_t *pUnit;
};
