#pragma once
#include "types.h"

typedef struct gohRenkenSword_t gohRenkenSword_t;

struct gohRenkenSword_t {
    s32 m_iIdx;
    s32 m_iSwordNo;
    s32 m_iCnt;
    s8 m_iType;
    s16 m_iPower;
    char *m_szSwordName;
    char *m_szSkillName;
};
