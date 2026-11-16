#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_BulletInit(void);
s32 AW_BulletAdd(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir);
s32 AW_BulletAdd_Setsuma(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir);
void AW_BulletCalc(AW_WORK_t *aWork);
void AW_BulletDraw(AW_WORK_t *aWork);
