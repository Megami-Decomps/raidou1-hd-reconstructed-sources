#pragma once
#include "types.h"
#include "SKLID.h"

extern SKLID *kuisibariTbl[5];
extern SKLID *g_aOmoide;
extern SKLID *spiritList;

void *cmpSortUseSpritList(void);
bool OmoideSklCheck(SKLID _sklID);
bool cmpSpiritSklCheck(SKLID _sklID);
