#pragma once
#include "types.h"
#include "SortType.h"

typedef struct Sort_t Sort_t;

struct Sort_t {
    SortType sortType;
    void *subSort;
};
