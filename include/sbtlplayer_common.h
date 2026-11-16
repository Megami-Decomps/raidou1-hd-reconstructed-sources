#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

s32 sBtlPlayerRSkillInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex);
void sBtlPlayerRSkill_CoolTimeClr(SBTLUNIT_WORK *wk, s32 _ClearIndex);
bool sBtlPlayerRSkillCancel_Setsuma(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_RSptrit(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_Skill(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_Move(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_Huuma(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_Guard(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_Jump(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_Kaihi(SBTLUNIT_WORK *wk);
bool sBtlPlayerRSkillCancel_Gun(SBTLUNIT_WORK *wk);
bool sBtlPlayerIsRSkillCancel(void);
