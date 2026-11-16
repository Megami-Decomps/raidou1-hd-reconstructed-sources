#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _UX, f32 _UY, f32 _UZ);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
