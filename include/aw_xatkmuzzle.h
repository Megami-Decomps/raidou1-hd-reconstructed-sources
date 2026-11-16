#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, f32 _Size);
s32 AW_XAtkAdd_Homing(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, f32 _Size);
s32 AW_XAtkAdd_Gun(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _UnityDir, f32 _UnityDirY);
void Delete(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
