#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern f32 gDistLen;

s32 sBtlPlayerRJigenKiriInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex);
f32 sBtlPlayerGetJigenKiriDist(void);
s32 sBtlPlayerRJigenKiriProc(SBTLUNIT_WORK *wk, s16 mode);
