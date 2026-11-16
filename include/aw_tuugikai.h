#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _Variation);
void Delete(AW_WORK_t *aWork);
void DeleteAll(void);
bool ChkRun(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
