#pragma once
#include "types.h"

typedef struct SBTLENMY_ACTDATA SBTLENMY_ACTDATA;
typedef struct SBTLENMY_PATHDATA SBTLENMY_PATHDATA;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

bool sBtlSetNextPathData(SBTLUNIT_WORK *wk);
s16 sBtlGetPathDataCount(s16 id);
SBTLENMY_ACTDATA *sBtlGetPathACTData(s16 id, s16 no);
SBTLENMY_PATHDATA *sBtlGetPathData(s16 id);
