#pragma once
#include "types.h"

typedef struct S_PosCtrl S_PosCtrl;
typedef struct S_PosMove S_PosMove;

struct S_PosCtrl {
    sdfVector4_t vLast;
    S_PosMove *m_pPosMove;
    s32 m_cnt;
    s32 m_stp;
    s32 m_run;
};
