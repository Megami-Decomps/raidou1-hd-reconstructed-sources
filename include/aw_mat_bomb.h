#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _PS2X, f32 _PS2Y, f32 _PS2Z);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
