#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(s32 _ListID, f32 _SX, f32 _SY, f32 _SZ, SKLID _skillid, s32 _prio);
s32 Add_Fld(f32 _SX, f32 _SY, f32 _SZ);
s32 Add_Huuma(f32 _SX, f32 _SY, f32 _SZ);
void EndLoop(void);
s32 Add_KudaSupport(f32 _SX, f32 _SY, f32 _SZ);
void Delete(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
