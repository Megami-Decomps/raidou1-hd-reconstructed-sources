#pragma once
#include "types.h"

typedef struct curctr_tag curctr_tag;

struct curctr_tag {
    u8 isdraw;
    u8 reserved0;
    s16 phase;
    s16 ctr0;
    s16 ctr1;
    s16 frame;
    s16 lf_wait;
    u16 lf_after_wait;
    s16 cut_wait;
    u32 ctr_key;
};
