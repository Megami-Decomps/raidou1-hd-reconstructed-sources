#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _Dan, f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z, f32 _Ps2Dir);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
