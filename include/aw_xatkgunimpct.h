#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ, SKLID _SklID);
void Delete(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
