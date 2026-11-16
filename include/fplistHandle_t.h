#pragma once
#include "types.h"
#include "EFFPFLIST_TYPE.h"
#include "TNEFFECT_BLEND.h"

typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct effPolygonFlashMesh effPolygonFlashMesh;
typedef struct fplistHandle_t fplistHandle_t;

struct fplistHandle_t {
    TNEFFECT_BLEND blend;
    sdfVector4_t abgr;
    s32 point;
    EFFPFLIST_TYPE type;
    s32 face;
    bool zTest;
    effCtexHandle_t *hCacheTex;
    effPolygonFlashMesh *pMesh;
};
