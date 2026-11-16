#pragma once
#include "types.h"

typedef struct SBTLAISYO_DATAWORK SBTLAISYO_DATAWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern SBTLAISYO_DATAWORK *script_aisyo_tbl;
extern s32 BS_LASTB2_pos_type;
extern s32 sklid_BS14_target;

s32 sBtlSupport_AI_CHK_CHKSKL_R(SBTLUNIT_WORK *wk, s32 arg);
s32 sBtlSBTL_SET_MoveSpdMul(void);
s32 sBtlBS14_TargetGet(void);
s32 sBtlBS14_CHOUSIN_TargetGet(s32 step3);
