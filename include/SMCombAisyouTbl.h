#pragma once
#include "types.h"

typedef enum {
    EMCA_None = 0,
    EMCA_Shitei = 1,
    DMCA_Fuufu = 2,
    DMCA_Kyoudai = 3,
    DMCA_Oyako = 4,
    DMCA_Raibaru = 5,
    DMCA_Slime = 6,
} EMCombAisyo;

typedef struct SMCombAisyouTbl SMCombAisyouTbl;

struct SMCombAisyouTbl {
    s32 m_iNo1;
    s32 m_iNo2;
    EMCombAisyo m_eAisyo;
};
