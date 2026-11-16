#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_HitsInit(void);
s32 AW_HitsAdd(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir, f32 _Scale);
void AW_HitsClrScoreWork(void);
void AW_HitsAdd_Spirit(s32 _ListID, SKLID _SkillID, f32 _PS2X, f32 _PS2Y, f32 _PS2Z);
void AW_HitsAdd_Go(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir, f32 _Scale);
void AW_HitsCalc(AW_WORK_t *aWork);
