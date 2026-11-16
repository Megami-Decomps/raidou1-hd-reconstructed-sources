#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct tagSBTLSKL_BARRIER_WORK tagSBTLSKL_BARRIER_WORK;

struct tagSBTLSKL_BARRIER_WORK {
    SKLID m_skillid;
    s32 m_cnt;
    u32 m_barrierstatus;
    u32 m_barrieradv;
    bool m_EndSM;
};
