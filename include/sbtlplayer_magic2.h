#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

s32 sBtlPlayerRMagic2Init(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex);
s32 sBtlPlayerRMagic2Proc(SBTLUNIT_WORK *wk, s16 mode);
