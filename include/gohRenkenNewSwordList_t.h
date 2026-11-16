#pragma once
#include "types.h"

typedef struct gohRenkenNewSwordList_t gohRenkenNewSwordList_t;
typedef struct gohRenkenSword_t gohRenkenSword_t;

struct gohRenkenNewSwordList_t {
    s32 m_iSwordCnt;
    gohRenkenSword_t *m_asSword[4];
};
