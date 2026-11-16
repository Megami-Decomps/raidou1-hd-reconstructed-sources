#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

s32 sBtlPlayerRMagicInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex);
void CallHitDone(void);
s32 sBtlPlayerRMagicProc(SBTLUNIT_WORK *wk, s16 mode);
