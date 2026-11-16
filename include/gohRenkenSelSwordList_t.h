#pragma once
#include "types.h"

typedef struct gohRenkenSelSwordList_t gohRenkenSelSwordList_t;
typedef struct gohRenkenSword_t gohRenkenSword_t;

struct gohRenkenSelSwordList_t {
    s32 m_iSwordCnt;
    gohRenkenSword_t *m_asSword[128];
};
