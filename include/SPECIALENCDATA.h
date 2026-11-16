#pragma once
#include "types.h"

typedef struct SPECIALENCDATA SPECIALENCDATA;

struct SPECIALENCDATA {
    u16 flg0;
    u16 flg1;
    u16 flg2[4];
    u16 ritu[4];
    u16 encountid[4];
};
