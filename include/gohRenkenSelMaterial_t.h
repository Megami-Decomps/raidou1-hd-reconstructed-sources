#pragma once
#include "types.h"

typedef struct gohRenkenSelMaterialItem_t gohRenkenSelMaterialItem_t;
typedef struct gohRenkenSelMaterial_t gohRenkenSelMaterial_t;
typedef struct gohRenkenSword_t gohRenkenSword_t;

struct gohRenkenSelMaterial_t {
    gohRenkenSword_t *m_sNewSword;
    s32 m_iMatrialCnt;
    gohRenkenSelMaterialItem_t *m_asMatrial[5];
    s32 m_iGold;
    s32 m_iAuraNo;
};
