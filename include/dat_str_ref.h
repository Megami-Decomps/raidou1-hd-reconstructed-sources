#pragma once
#include "types.h"
#include "sbtlsub.h"

// macros
// 0x18ef1f0: char *DVNAME(s32 _idx)
#define DVNAME(_idx) (sBtlGetDevilNameFont(idx, 0))

// 0x18ef2c0: char *RCNAME(s32 _idx)
#define RCNAME(_idx) (sBtlGetRaceNameFont(idx))

// 0x18ef3a0: char *ITNAME(s32 _idx)
#define ITNAME(_idx) (sBtlGetItemNameFont(idx))

// 0x18ef480: char *SKNAME(s32 _idx)
#define SKNAME(_idx) (sBtlGetSkillNameFont(idx))
