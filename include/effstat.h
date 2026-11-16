#pragma once
#include "types.h"

typedef enum {
    EFFSTAT_FLAG_STOP = 1,
    EFFSTAT_FLAG_STOP_REQ = 2,
    EFFSTAT_FLAG_EDITOR = 4,
} EFFSTAT_FLAG;

EFFSTAT_FLAG effGetFlags(void);
void effStartEffectStop(void);
void effStopEffectStop(void);
void effStartEffectStop_SUMMON_FR(void);
void effStopEffectStop_SUMMON_FR(void);
void Init(void);
