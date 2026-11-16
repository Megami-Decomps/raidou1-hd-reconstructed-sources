#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
