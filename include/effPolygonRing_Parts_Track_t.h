#pragma once
#include "types.h"

typedef struct effPolygonRing_Parts_Track_t effPolygonRing_Parts_Track_t;

struct effPolygonRing_Parts_Track_t {
    f32 length;
    sdfVector3_t pos1;
    sdfVector3_t pos2;
    sdfVector3_t pos3;
};
