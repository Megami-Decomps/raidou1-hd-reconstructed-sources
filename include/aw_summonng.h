#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(void);
s32 Add_Pur(void);
void DeleteAll(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
