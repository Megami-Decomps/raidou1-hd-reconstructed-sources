#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_CamLockonInit(void);
s32 AW_CamLockonAdd(s32 _SubIdx);
void AW_CamLockonDeleteAll(void);
void AW_CamLockonSetPos(s32 _AW_Idx, f32 _2DX, f32 _2DY, f32 _NormalTime);
void AW_CamLockonSetVisible(s32 _AW_Idx, bool _OnOff);
void AW_CamLockonCalc(AW_WORK_t *aWork);
void AW_CamLockonDraw(AW_WORK_t *aWork);
