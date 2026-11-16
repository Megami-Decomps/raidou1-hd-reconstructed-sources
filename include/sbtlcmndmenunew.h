#pragma once
#include "types.h"
#include "SKLID.h"
#include "kernel.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3ProcessID_t dds3ProcessID_t;

extern dds3ProcessID_t *g_mainPID;
extern char *g_strRepeat;

s32 sBtlGetSklRepeat(bool *a_pbRepeat, SBTLUNIT_WORK *a_pBtlUnit, SKLID a_sklId);
s32 sBtlSetSklRepeat(bool a_bRepeat, SBTLUNIT_WORK *a_pBtlUnit, SKLID a_sklId);
void sBtlEnd(void);
bool sBtlChkRepeat(SKLID a_sklId);
void sBtlInit(void);
void Delete(void);
bool sBtlIsStart(s32 mode);
bool sBtlStart(s32 com_smn_idx);
bool sBtlStartBattle1st(void);
s32 sBtlGetStat(void);
bool sBtlChkDecide(void);
void sBtlDrawRepeatIcon(s32 a_x, s32 a_y, s32 a_z, f32 a_angle, f32 a_alphaRate, DDS3_OT a_otNo, bool a_bRepeat, bool a_bRepeatOrder);
SBTLUNIT_WORK *sBtlGetActionUnit(void);
SBTLUNIT_WORK *GetTargetUnit(void);
