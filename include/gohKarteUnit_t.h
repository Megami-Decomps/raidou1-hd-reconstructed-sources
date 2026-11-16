#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct gohKarteUnit_t gohKarteUnit_t;

struct gohKarteUnit_t {
    u8 Level;
    u8 killflag;
    u8 nakamaflag;
    u8 RsvSklFlag;
    u8 UnitFlag;
    u8 iOmoideSkillCnt;
    s16 DevilID;
    u16 MaxHP;
    u8 Cyuusei;
    u8 resv1;
    u16 resv0;
    SKLID *Skill[8];
    SKLID *aOmoideSkill[8];
    s32 Exp;
    u8 Str[5];
    u8 Tec[5];
    u8 Vit[5];
    u8 Luck[5];
    s8 aOmoideSkillMaster[16];
    SKLID *battleskill[16];
    s32 accidentBonusHp;
    SKLID *sousaSkill[2];
    u32 uniqCode;
    bool lockDvl;
    bool fav;
};
