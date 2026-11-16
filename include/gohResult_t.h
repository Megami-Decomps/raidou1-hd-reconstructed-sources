#pragma once
#include "types.h"

typedef struct gohResult_t gohResult_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct gohResult_t {
    s16 m_iMesNo;
    s16 m_iDevilNo;
    s16 m_iItemNo;
    s16 m_iItemNum;
    s32 m_iType;
    s16 m_iDvlReport;
    sdatUnitWork_t *Devil;
};
