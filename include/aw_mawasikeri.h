#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _ListID, f32 _Spd, s32 _Variation, SKLID _SklID);
void DeleteAll(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
