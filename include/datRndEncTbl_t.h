#pragma once
#include "types.h"

typedef struct datRndEncRitu_t datRndEncRitu_t;
typedef struct datRndEncTbl_t datRndEncTbl_t;

struct datRndEncTbl_t {
    u8 map;
    u8 floor;
    u16 flag0;
    u16 flag1;
    u16 flag0j;
    u16 flag1j;
    s16 normalritu;
    s32 type;
    datRndEncRitu_t *ritu[8];
};
