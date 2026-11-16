#pragma once
#include "types.h"

typedef struct instanceMes_tag instanceMes_tag;
typedef struct itfMiscLinkHeader_t itfMiscLinkHeader_t;
typedef struct mesflow_tag mesflow_tag;

struct mesflow_tag {
    itfMiscLinkHeader_t *pprev;
    itfMiscLinkHeader_t *pnext;
    s32 id;
    instanceMes_tag *pinst;
};
