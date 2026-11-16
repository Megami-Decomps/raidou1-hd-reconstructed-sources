#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
