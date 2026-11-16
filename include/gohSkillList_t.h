#pragma once
#include "types.h"

typedef enum {
    OWNER_1 = 0,
    OWNER_2 = 1,
    OWNER_B = 2,
} GOH_SKILL;

typedef struct gohSkillList_t gohSkillList_t;

struct gohSkillList_t {
    u32 Prio;
    u32 SkillID;
    GOH_SKILL Owner;
    s32 Flag;
};
