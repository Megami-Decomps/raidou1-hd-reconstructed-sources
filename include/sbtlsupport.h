#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

s32 sBtlSetSkillTarget(SBTLUNIT_WORK *wk, SKLID skillID, u32 targetCode);
s32 sBtlGetNumDistance(f32 dist);
