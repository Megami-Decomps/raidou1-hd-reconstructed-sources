#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add_Wait(f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z, s32 _Wait);
s32 Add(f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z);
void CalcWait(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
