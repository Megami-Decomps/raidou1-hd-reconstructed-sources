#pragma once
#include "types.h"

typedef enum {
    Step_Init = 0,
    Step_Update = 1,
    Step_End = 2,
} Step;

extern Step step;
extern void *encountNoTbl;

bool ChkTipsStart(void);
bool CallCheck(void);
bool Update(void);
bool SummonTipsCall(s32 _groupID);
