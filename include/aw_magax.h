#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_MagInit(void);
s32 AW_MagAdd(s32 _ListID);
void AW_MagDel(void);
void AW_MagCalc(AW_WORK_t *aWork);
void AW_MagDraw(AW_WORK_t *aWork);
