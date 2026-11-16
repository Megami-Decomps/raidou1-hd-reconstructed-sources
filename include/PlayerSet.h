#pragma once
#include "types.h"

typedef struct PlayerSet PlayerSet;

struct PlayerSet {
    void *expBarMask;
    void *expText;
    void *expNum;
    void *expNext;
    void *lvText;
    void *lvNum;
    void *name;
};
