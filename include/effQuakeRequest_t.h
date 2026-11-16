#pragma once
#include "types.h"

typedef enum {
    EFFSTAT_QUAKE_FLAG_ACTIVE = 1,
    EFFSTAT_QUAKE_FLAG_AUTOREMOVE = 2,
    EFFSTAT_QUAKE_FLAG_RUN = 4,
    EFFSTAT_QUAKE_FLAG_MAIN = 8,
} EFFSTAT_QUAKE_FLAG;

typedef enum {
    EFFSTAT_QUAKE_TYPE_FIX = 0,
    EFFSTAT_QUAKE_TYPE_DAMP = 1,
} EFFSTAT_QUAKE_TYPE;

typedef struct effQuakeRequest_t effQuakeRequest_t;

struct effQuakeRequest_t {
    u32 frame;
    u32 amp;
    EFFSTAT_QUAKE_FLAG flags;
    EFFSTAT_QUAKE_TYPE type;
    u16 count;
    u16 priority;
};
