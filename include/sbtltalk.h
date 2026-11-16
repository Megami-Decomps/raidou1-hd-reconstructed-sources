#pragma once
#include "types.h"

typedef struct SBTLTALK_WORK SBTLTALK_WORK;

SBTLTALK_WORK *sBtlCreateTalk(void);
bool Proc(SBTLTALK_WORK *twk);
bool sBtlDeleteTalk(SBTLTALK_WORK *twk);
bool sBtlSetDevilSkillID(s32 devilid, s32 flg);
