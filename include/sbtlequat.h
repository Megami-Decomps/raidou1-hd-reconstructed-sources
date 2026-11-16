#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

bool sBtlCheckArea(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area);
bool sBtlCheckArea_SubCylinder(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area);
s32 sBtlCheckAreaCount(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area);
bool sBtlCheckArea_Atk(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area);
s32 sBtlCheckArea_Masic(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area, s32 flg);
