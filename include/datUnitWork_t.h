#pragma once
#include "types.h"

typedef struct datCommandMemory_t datCommandMemory_t;
typedef struct datUnitWork_t datUnitWork_t;

struct datCommandMemory_t {
    s16 type;
    s16 index;
    s16 skillID;
};

struct datUnitWork_t {
    u16 flag;
    u16 aisyo;
    u16 id;
    u16 hp;
    u16 maxhp;
    u16 mp;
    u16 maxmp;
    u16 badstatus;
    u32 exp;
    u16 level;
    s8 param[5];
    u16 i_maxhp;
    u16 i_maxmp;
    u8 skillcnt;
    u8 dmy;
    u16 skill[24];
    datCommandMemory_t *command_mem;
    u16 reserve0;
    u32 bad_rec;
    u32 ep;
    u32 reserve1;
    u32 reserve2;
};
