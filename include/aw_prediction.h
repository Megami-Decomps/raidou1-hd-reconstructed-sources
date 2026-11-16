#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(const sdfVector4_t *_Pos, f32 _SizeR, f32 _Life, s32 _Wait);
void Delete(AW_WORK_t *aWork);
void DeleteAll(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
