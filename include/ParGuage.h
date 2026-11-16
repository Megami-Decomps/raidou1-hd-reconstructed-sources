#pragma once
#include "types.h"

#define LINE_MAX 10
#define SCALE_MAX 11
#define MINI_LINE_MAX 4
#define MINI_SCALE_MAX 5

typedef struct ParGuage ParGuage;

struct ParGuage {
    void *lineImage;
    void *scaleImage;
    void *scaleRect;
};
