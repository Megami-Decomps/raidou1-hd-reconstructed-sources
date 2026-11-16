#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_XAtkSightInit(void);
s32 AW_XAtkSightAdd(f32 _X, f32 _Y, f32 _Z, f32 _Dir);
void AW_XAtkSightDelete(AW_WORK_t *aWork);
void AW_XAtkSightFadeOut(s32 _Idx);
void AW_XAtkSightCalc(AW_WORK_t *aWork);
void AW_XAtkSightDraw(AW_WORK_t *aWork);
