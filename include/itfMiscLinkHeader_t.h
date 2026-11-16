#pragma once
#include "types.h"

typedef struct itfMiscLinkHeader_t itfMiscLinkHeader_t;

struct itfMiscLinkHeader_t {
    itfMiscLinkHeader_t *pprev;
    itfMiscLinkHeader_t *pnext;
    s32 id;
};
