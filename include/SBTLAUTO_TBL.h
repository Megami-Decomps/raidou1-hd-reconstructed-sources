#pragma once
#include "types.h"

typedef struct SBTLAISYO_DATAWORK SBTLAISYO_DATAWORK;
typedef struct SBTLAUTO_TBL SBTLAUTO_TBL;
typedef struct sdatParaWork_t sdatParaWork_t;

struct SBTLAUTO_TBL {
    sdatParaWork_t *m_paraBns;
    SBTLAISYO_DATAWORK *m_aisyo;
};
