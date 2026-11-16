#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _Variation, f32 _SX, f32 _SY, f32 _SZ, s32 MagKaifuku);
void Delete(AW_WORK_t *aWork);
bool ChkUse(void);
void AllGetAndDelete(void);
void Calc(AW_WORK_t *aWork);
