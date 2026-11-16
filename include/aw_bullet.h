#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir, s32 _TargetListID, s32 _SubIdx);
void Delete(AW_WORK_t *aWork);
void GetTargetPos(AW_WORK_t *aWork, f32 *_TgtX, f32 *_TgtY, f32 *_TgtZ);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
