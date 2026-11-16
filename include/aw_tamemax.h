#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_TameInit(void);
s32 AW_TameAdd(void);
void AW_TameDeleteAll(void);
void AW_TameDel(bool _Immed);
void AW_TameCalc(AW_WORK_t *aWork);
void AW_TameDraw(AW_WORK_t *aWork);
