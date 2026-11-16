#pragma once
#include "types.h"
#include "event.h"

typedef struct pmdObjectTable_t pmdObjectTable_t;

struct pmdObjectTable_t {
    PMD_OBJTYPE ObjectType;
    u8 ObjectNo;
    s16 NameIndex;
    s16 Offset;
    s8 union0;
    s8 union1;
};
