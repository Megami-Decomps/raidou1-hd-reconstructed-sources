#pragma once
#include "types.h"

void evtInitGlobalWork(void);
void evtBitAllOff(void);
void evtBitAllOff_FieldDebug(void);
void evtBitKityouItemAdd(s32 _no);
void evtBitOn(s32 no);
void evtBitOff(s32 no);
void evtBitSet(s32 no, bool bBool);
bool evtBitCheck(s32 no);
