#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_JumpInit(void);
s32 AW_JumpAdd(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir);
void AW_JumpCalc(AW_WORK_t *aWork);
void AW_JumpDraw(AW_WORK_t *aWork);
