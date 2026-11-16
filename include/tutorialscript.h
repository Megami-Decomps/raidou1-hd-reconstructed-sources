#pragma once
#include "types.h"
#include "SBTLUNIT_MOTION.h"

void RaidouMotion(SBTLUNIT_MOTION _motion);
void T_OkikumuMotion(SBTLUNIT_MOTION _motion);
void LoadEff(void);
void InstanceEff(void);
void DestroyEff(void);
void UnitOnOff(s32 _unit, s32 _active);
bool NakamaRot(s32 _unit, s32 _frame);
void PosReset(s32 _boss, s32 _lookUp);
sdfVector4_t WajutsuPosSet(void);
void CameraNormalPosSet(void);
void NakamaRaidouPosSet(const sdfVector4_t *_raidouPos, f32 _r);
