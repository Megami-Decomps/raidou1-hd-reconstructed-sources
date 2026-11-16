#pragma once
#include "types.h"

typedef enum {
    EFFBEHAVIOR_RGB_POINT_NON = 0,
    EFFBEHAVIOR_RGB_POINT_1 = 1,
    EFFBEHAVIOR_RGB_POINT_2 = 2,
    EFFBEHAVIOR_RGB_POINT_MAX = 3,
} EFFBEHAVIOR_RGB_POINT;

typedef struct Color Color;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;

struct Color {
    f32 rate;
    sdfVector4_t color;
};

struct effBehavior_RGBParams_t {
    EFFBEHAVIOR_RGB_POINT type;
    sdfVector4_t start;
    sdfVector4_t end;
    Color *point[3];
};
