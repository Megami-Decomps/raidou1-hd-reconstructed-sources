#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_XAtkChargeInit(void);
s32 AW_XAtkChargeAdd(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir);
void AW_XAtkChargeDelete(AW_WORK_t *aWork);
void Delete(s32 aw_idx);
void AW_XAtkChargeScaleFadeOut(s32 aw_idx);
void AW_XAtkChargeSetPos(s32 aw_idx, f32 _X, f32 _Y, f32 _Z);
void AW_XAtkChargeCalc(AW_WORK_t *aWork);
void AW_XAtkChargeDraw(AW_WORK_t *aWork);
