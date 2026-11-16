#pragma once
#include "types.h"

typedef struct gohKillDevil_t gohKillDevil_t;

bool datCheckKillDevil(s32 iDevilID);
void datSetKillDevil(s32 iDevilID);
gohKillDevil_t *gohGetSelf(void);
s32 datGetDevilNo2BitIndex(s32 iDevilID);
