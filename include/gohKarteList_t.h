#pragma once
#include "types.h"

typedef struct gohKarteList_t gohKarteList_t;
typedef struct gohKarteUnit_t gohKarteUnit_t;

struct gohKarteList_t {
    s32 RegistNums;
    gohKarteUnit_t *KarteUnit[544];
    s32 m_sCombCnt;
    s32 Reserve[2];
    gohKarteUnit_t *Karte2Unit[200];
    s32 karte2WakuCnt;
};
