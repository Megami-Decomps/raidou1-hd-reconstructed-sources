#pragma once
#include "types.h"

typedef struct jmsSeqHandle_t jmsSeqHandle_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;

struct jmsSeqHandle_t {
    s32 UnitCnt;
    jmsSeqUnit_t *pUnit[16];
    jmsSeqUnit_t *pLastSeqUnit[2];
};
