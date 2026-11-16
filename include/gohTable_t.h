#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct gohSortedDevilList_t gohSortedDevilList_t;
typedef struct gohTable_t gohTable_t;

struct gohTable_t {
    u8 *CombineTbl;
    s32 AccidentFailSize;
    u16 *pAccidentFail;
    s32 EventDevilSize;
    void *pEventDevil;
    s32 SkillAttrPrioSize;
    s32 SkillTypePrioSize;
    s32 AccidentDevilSize;
    s32 NotDupliSkillSize;
    SKLID *pNotDupliSkill;
    gohSortedDevilList_t *DevilList;
    void *swordTree;
    void *nameSortTbl;
};
