#pragma once
#include "types.h"
#include "SBTLUNIT_MARK.h"
#include "SKLID.h"

typedef struct EFFPDATA_WORK EFFPDATA_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SB_ENCOUNTPAC SB_ENCOUNTPAC;
typedef struct sdfModelNode_t sdfModelNode_t;

extern f32 sbtlscpt_jumpacc;

void sBtlSupport_StopAction(SBTLUNIT_WORK *wk);
void sBtlSupport_BattleStop(s32 motionFlag, s32 effectFlag, s32 SEFlag);
bool sBtlCreateAIScript(void);
void sBtlAllInit(void);
void Init(SBTLUNIT_WORK *pUnit);
bool sBtlCheckSetHITNONE(s32 Group, u32 DevilID);
void sBtlEncountInit(SBTLUNIT_WORK *wk, s32 EffMode);
void sBtlDeath(SBTLUNIT_WORK *wk);
void Delete(SBTLUNIT_WORK *wk);
void sBtlBattleStart(SB_ENCOUNTPAC *encpac, bool _EnemySummonWait);
u32 sBtlSetAttr(SBTLUNIT_WORK *wk, u32 attr);
s32 sBtlCheckHuttobi(SBTLUNIT_WORK *wk);
s32 CheckBadStatus(SBTLUNIT_WORK *wk);
bool sBtlCheckSkillCancel(SBTLUNIT_WORK *wk, SKLID skillID);
bool sBtlCheckEnshutuSummonUnit(SBTLUNIT_WORK *wk);
void sBtlDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 damage);
void sBtlEndAction(SBTLUNIT_WORK *wk);
void sBtlStartDeadEvent(SBTLUNIT_WORK *wk);
s32 sBtlGetPointLast(SBTLUNIT_WORK *wk, SKLID skillID);
s32 sBtlGetNearPosHD(SBTLUNIT_WORK *wk, const sdfVector4_t *unit_pos);
bool GetUnitHelperMatrix(SBTLUNIT_WORK *wk, SBTLUNIT_MARK mark);
bool sBtlCheckEffectCancel(SBTLUNIT_WORK *wk, SKLID skillID, EFFPDATA_WORK *effpdwork);
void btlBoss_CERBER_ModelNodeFadeOutSub(sdfModelNode_t *pNode, const sdfVector4_t *rootColor);
s32 sBtlModelNodeFadeout(SBTLUNIT_WORK *wk, char *pName);
