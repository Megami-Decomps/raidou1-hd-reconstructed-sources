#pragma once
#include "types.h"

typedef struct itfMiscLinkHeader_t itfMiscLinkHeader_t;
typedef struct itfMiscLinkStack_t itfMiscLinkStack_t;

struct itfMiscLinkStack_t {
    itfMiscLinkHeader_t *puse_top;
    itfMiscLinkHeader_t *puse_tail;
    itfMiscLinkHeader_t *pdisuse_top;
    itfMiscLinkHeader_t *pdisuse_tail;
};
