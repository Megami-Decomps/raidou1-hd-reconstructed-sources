#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _X, f32 _Y, f32 _Z);
void SetTgtPos(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ);
void SetScale(f32 _Scale);
void DeleteAll(void);
void Delete(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
