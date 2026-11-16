#pragma once
#include "types.h"

typedef enum {
    SORT_SKL_NONE = 999,
    SORT_SKL_RECV = 1,
    SORT_SKL_PHYSICS = 2,
    SORT_SKL_FIRE = 3,
    SORT_SKL_ICE = 4,
    SORT_SKL_THUNDER = 5,
    SORT_SKL_WIND = 6,
    SORT_SKL_DARK = 7,
    SORT_SKL_EVERY = 8,
    SORT_SKL_BST = 9,
    SORT_SKL_AID = 10,
    SORT_SKL_OMOIDE = 11,
    SORT_SKL_SOUSA = 12,
} SORT_SKL;

typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;

struct SBTLSKILLP_TBL {
    u16 s_type;
    s16 para;
    u32 attr;
    s16 attrtime;
    u16 transfer;
    u16 type;
    u16 area;
    u8 useflg;
    s8 count;
    u32 flg;
    s16 n0;
    f32 n1;
    s16 max_damage;
    s16 muteki_time;
    u32 badst;
    s16 percentage;
    s16 para2;
    u16 equipID;
    s16 hitbk_cnt;
    f32 hitbk_rate;
    u32 flg2;
    s32 weapontype;
    s32 fuyoeff;
    s32 shild_dmg;
    s32 light_attack_mag;
    s32 sortId;
    SORT_SKL sortType;
    s32 coolTime;
    s32 wincePow;
};
