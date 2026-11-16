#pragma once
#include "types.h"

typedef struct effPolygonThunder_Bug_t_Parts_t effPolygonThunder_Bug_t_Parts_t;
typedef struct tplistHandle_t tplistHandle_t;

struct effPolygonThunder_Bug_t_Parts_t {
    tplistHandle_t *hPList;
    s32 frame;
    f32 alpha;
    sdfVector4_t pos;
    f32 rot[2];
    f32 rotate;
    f32 radian;
    f32 height;
};
