#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern bool gHitDonePlayer;
extern bool *gHitDoneNakama;

void ProcStart(void);
void DeleteAll(void);
void DeleteAll_Event(void);
void DeleteAll_Skill(void);
void DeleteAll_BossDead(void);
void DeleteAll_BossDYING(SBTLUNIT_WORK *wkBoss);
void DeleteAll_MagWeapon(void);
void DeleteAll_MenuItemUse(void);
void InitBattle(void);
