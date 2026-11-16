#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct DEVILDATA_WORK DEVILDATA_WORK;

bool CreateInstance(void);
void DestroyInstance(void);
bool gohIsInstance(void);
void gohSetup(void);
s32 gohGetDevilMax(void);
s32 gohGetNakamaTop(void);
s32 gohGetNakamaMax(void);
DEVILDATA_WORK *gohGetDevilDataTable(s32 iNo);
char *gohGetRaceName(s32 iNo);
char *gohGetSeireiName(s32 iNo);
char *gohGetMitamaName(s32 iNo);
char *gohGetDevilName(s32 iNo);
char *gohGetSkillName(s32 iNo);
char *gohGetSousaSkillName(s32 iNo);
bool gohIsSkillForm(s32 iDevilNo, SKLID iSkillNo);
u32 gohGetOmoideSkillCnt(void);
SKLID gohGetOmoideSkill2SkillNo(s32 iOmoideSkillNo);
s32 gohGetSkill2OmoideSkillNo(s32 iSkillNo);
s32 gohGetSkillSpiritSkillNo(s32 iSkillNo);
s32 gohGetRaidouSkillNo(s32 iSkillNo);
void gohSetupDevilList(void);
