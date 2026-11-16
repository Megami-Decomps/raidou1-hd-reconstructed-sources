#pragma once
#include "types.h"

typedef struct gohSwordHistory_t gohSwordHistory_t;

struct gohSwordHistory_t {
    s32 m_iRegistNums;
    s32 m_iNewSowrdNo;
    u8 m_iaBits[24];
    u8 m_haveBits[24];
};
