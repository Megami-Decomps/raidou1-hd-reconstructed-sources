#pragma once
#include "types.h"
#include "SBTLUNIT_EX.h"
#include "SBTLUNIT_ST.h"
#include "SKLID.h"

typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct SBTLITEM_WORK SBTLITEM_WORK;
typedef struct SBTLMEMORYSKILL_WORK SBTLMEMORYSKILL_WORK;

struct SBTLMEMORYSKILL_WORK {
    s16 level;
    SKLID skill;
};

struct DEVILDATA_WORK {
    SBTLUNIT_ST stflg;
    SBTLUNIT_EX exsts;
    u16 level;
    s16 minorno;
    s16 minorno_d;
    s16 bunriid;
    s16 aishou;
    s8 kuda_id;
    s8 seikaku;
    s16 magcost;
    s16 atkpower;
    s32 actcounter;
    s32 hp;
    s32 maxhp;
    s32 mp;
    s32 maxmp;
    s16 str;
    s16 vit;
    s16 tec;
    s16 luck;
    SKLID *haveskill[16];
    SBTLMEMORYSKILL_WORK *memskill[2];
    u16 setmotionno;
    u16 keisyo_type;
    u16 keisyo_form;
    u16 getexp;
    u16 getmoney;
    u16 getmag;
    f32 getchuusei;
    SBTLITEM_WORK *item[4];
    f32 frid_area_r;
    f32 enmy_area_r;
    s16 kucyo;
    s16 huumaID;
    s16 level_sa;
    s16 damage_per;
    s16 talkskill;
    s16 character;
    u8 mskskill;
    s16 boudbgn;
    s16 attrinvtime;
    s32 vice_val;
    s32 weak_shild_count;
    s32 weak_shild_config;
    s32 atk_raito;
    s32 s_wince;
    s32 l_wince;
};
