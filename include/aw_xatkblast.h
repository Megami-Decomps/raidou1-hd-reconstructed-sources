#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_XAtkInit(void);
s32 AW_XAtkAdd(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _Size);
void AW_XAtkDelete(AW_WORK_t *aWork);
void AW_XAtkCalc(AW_WORK_t *aWork);
void AW_XAtkDraw(AW_WORK_t *aWork);
