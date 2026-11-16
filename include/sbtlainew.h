#pragma once
#include "types.h"
#include "SBTLUNIT_HST.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"

typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

bool AI_NakamaUseSkill(SBTLUNIT_WORK *wk);
SBTLUNIT_WORK *sBtlGetPlayerTarget(void);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_DeadDamage(SBTLUNIT_WORK *acterwk, SBTLUNIT_SIDE side, SKLID sklid);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_WeakAtk(SBTLUNIT_SIDE side, SKLID sklid, bool shild);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_HST(SBTLUNIT_SIDE side, SBTLUNIT_HST mask_hst);
SBTLUNIT_LISTWORK *sBtlCreateTargetList_RaidouTarget(SBTLUNIT_SIDE side, bool shild);
void sBtlDestroyTarget(void);
