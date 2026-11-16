#pragma once
#include "types.h"

typedef struct NakamaSet NakamaSet;

struct NakamaSet {
    void *expBarMask;
    void *expText;
    void *expNum;
    void *expNext;
    void *lvText;
    void *lvNum;
    void *name;
    void *cyuuseiText;
    void *cyuuseiBarMask;
};
