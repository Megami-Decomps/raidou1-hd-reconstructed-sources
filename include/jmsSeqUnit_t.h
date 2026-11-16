#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;

typedef s32 (*jmsInt32Delegate)(dds3ProcessID_t *ID);

struct jmsSeqUnit_t {
    s64 Stat;
    jmsInt32Delegate pInit;
    jmsInt32Delegate pDestroy;
    dds3ProcessFunc_t pCalc;
    dds3ProcessFunc_t pDraw;
    dds3ProcessFunc_t pUpdate;
    jmsInt32Delegate pCheck;
};
