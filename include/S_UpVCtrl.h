#pragma once
#include "types.h"

typedef struct S_UpVCtrl S_UpVCtrl;
typedef struct S_UpVMove S_UpVMove;

struct S_UpVCtrl {
    S_UpVMove *m_pUpVMove;
    s32 m_cnt;
    s32 m_stp;
    s32 m_run;
    f32 m_UpVLast;
};
