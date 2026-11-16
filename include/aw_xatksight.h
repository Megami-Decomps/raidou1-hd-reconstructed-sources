#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _X, f32 _Y, f32 _Z, f32 _Dir);
void Delete(AW_WORK_t *aWork);
void AW_XAtkFadeOut(s32 _Idx);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
