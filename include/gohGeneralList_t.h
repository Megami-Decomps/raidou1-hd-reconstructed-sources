#pragma once
#include "types.h"

typedef struct gohGeneralList_t gohGeneralList_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct gohGeneralList_t {
    sdatPlayerUnitWork_t *m_pPlayer;
    s32 m_PlayerVal;
    sdatUnitWork_t *m_pDevil[32];
    s32 m_DevilCnt;
    s32 m_DevilVal[32];
};
