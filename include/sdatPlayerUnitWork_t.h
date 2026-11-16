#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct DEVIL_MEMORYWORK DEVIL_MEMORYWORK;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct DEVIL_MEMORYWORK {
    s16 status;
    s16 point;
    s16 killCount;
    s16 talkCount;
};

struct sdatPlayerUnitWork_t {
    sdfVector4_t pos;
    sdfVector4_t rot;
    s32 mag;
    s32 maxmag;
    s32 gold;
    s32 maxgold;
    u32 flag;
    sdatUnitWork_t *para;
    s16 dummy_level;
    s16 swordno;
    s16 swordatk;
    s32 gunno;
    s32 hgunnum;
    s32 bulletno;
    char *name;
    s16 item[768];
    void *getItemList;
    sdatUnitWork_t *stock_id[32];
    s16 enc_cnt;
    s16 stack_p[2];
    s8 stock_max;
    s8 member_num;
    s16 downluck;
    s16 luckparam;
    s8 devilCard[69];
    DEVIL_MEMORYWORK *devilMemory[544];
    s32 stance;
    s16 battleResult;
    SKLID *spiritSkill[8];
    s8 spiritMaster[16];
    s32 spiritCnt;
    s32 syougou;
    bool setSyougou;
    s32 syougouNew[76];
    SKLID *raidouSkill[3];
    s8 raidouSkillMaster[16];
    s32 sprit_waza;
    s32 tubeSupportCount;
    bool seikatu;
    bool megane;
};
