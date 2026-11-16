#pragma once
#include "types.h"

typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern SBTLUNIT_WORK *sbtleffbo_acter;
extern SBTLUNIT_WORK *sbtleffbo_target;

bool sBtlEffSetActer(s32 id);
bool sBtlEffSetTarget(s32 id);
SBTLUNIT_LISTWORK *sBtlEffCreateUnitList(u8 area);
void sBtlEffDeleteUnitList(SBTLUNIT_LISTWORK *lwk);
