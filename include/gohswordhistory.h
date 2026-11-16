#pragma once
#include "types.h"

typedef struct gohSwordHistory_t gohSwordHistory_t;

void Clear(void);
void gohOnSword(s32 iSwordNo);
void gohOnSwordHave(s32 iSwordNo);
bool gohCheckSword(s32 iSwordNo);
bool gohCheckSwordHave(s32 iSwordNo);
bool gohCheckSwordHaveComplete(void);
void gohAppendSword(s32 iSwordNo, bool bFlag);
s32 gohGetNewSword(void);
gohSwordHistory_t *GetSelf(void);
bool gohIsSwordNo(s32 iSwordNo);
