#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _ListID);
void Del(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
s32 Add_Support(void);
void Calc_Support(AW_WORK_t *aWork);
void Draw_Support(AW_WORK_t *aWork);
