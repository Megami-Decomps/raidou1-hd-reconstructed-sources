#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_XAtkBulletInit(void);
s32 AW_XAtkBulletAdd(f32 _X, f32 _Y, f32 _Z);
void AW_XAtkBulletDelete(AW_WORK_t *aWork);
void AW_XAtkBulletCalc(AW_WORK_t *aWork);
void AW_XAtkBulletDraw(AW_WORK_t *aWork);
