#pragma once
#include "types.h"

typedef struct jmsCyousaRootTable_t jmsCyousaRootTable_t;

struct jmsCyousaRootTable_t {
    u32 *pData;
    s32 Nums;
};

extern u32 jmsCyousaTable1[4];
extern u32 *jmsCyousaTable2;
extern u32 *jmsCyousaTable3;
extern jmsCyousaRootTable_t *jmsCyousaRootTable;
