#pragma once
#include "types.h"
#include "TNEFFECT_BLEND.h"

typedef struct tplistHandle_t tplistHandle_t;

struct tplistHandle_t {
    TNEFFECT_BLEND blend;
    s32 point;
    bool zTest;
    sdfVector4_t abgr;
    void *pVertex;
    void *pVC;
    f32 *alpha_e;
    f32 *alpha_b;
    f32 *alpha_c;
};
