#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_ApproachInit(void);
s32 AW_ApproachAdd(s32 _ListID, f32 _OfsDir, f32 _OfsLen);
void AW_ApproachDeleteAll(void);
void AW_ApproachCalc(AW_WORK_t *aWork);
s32 AW_ApproachAdd_Kaya(s32 _ListID, f32 _OfsDir, f32 _OfsLen);
void AW_ApproachCalc_Kaya(AW_WORK_t *aWork);
void AW_ApproachDraw(AW_WORK_t *aWork);
