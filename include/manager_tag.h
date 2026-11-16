#pragma once
#include "types.h"

typedef struct itfMiscLinkStack_t itfMiscLinkStack_t;
typedef struct manager_tag manager_tag;
typedef struct mesflow_tag mesflow_tag;

struct manager_tag {
    u32 numuse;
    s32 ctr;
    u16 stat;
    s16 reserved;
    itfMiscLinkStack_t *linkstack;
    mesflow_tag *pmesflow[64];
};
