#pragma once
#include "types.h"

typedef struct effPolygonThunder_Point2_t_Parts_t effPolygonThunder_Point2_t_Parts_t;
typedef struct tplistHandle_t tplistHandle_t;

struct effPolygonThunder_Point2_t_Parts_t {
    tplistHandle_t *hPList;
    s32 frame;
    f32 alpha;
    f32 roll;
};
