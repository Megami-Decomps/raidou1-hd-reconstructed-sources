#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

s32 sBtlPlayerRGunShotInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex);
void sBtlPlayerCallHitDone(void);
s32 sBtlPlayerRGunShotProc(SBTLUNIT_WORK *wk, s16 mode);
