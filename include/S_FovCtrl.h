#pragma once
#include "types.h"

typedef struct S_FovCtrl S_FovCtrl;
typedef struct S_FovMove S_FovMove;

struct S_FovCtrl {
    S_FovMove *m_pFovMove;
    s32 m_cnt;
    s32 m_stp;
    s32 m_run;
    f32 m_fovLast;
};
