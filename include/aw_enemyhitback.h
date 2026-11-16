#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _TargetListID);
void Delete(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
