#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ);
void Delete(AW_WORK_t *aWork);
void Delete_2(s32 aw_idx);
void SetPos(s32 aw_idx, f32 _X, f32 _Y, f32 _Z);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
