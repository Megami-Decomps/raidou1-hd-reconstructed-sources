#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _ListID, f32 _OfsDir, f32 _OfsLen, f32 _Size);
void ClearPosLink(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
