#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _Unit_ListID, f32 _X, f32 _Y, f32 _Z);
void Delete(AW_WORK_t *aWork);
void DeleteAll(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
