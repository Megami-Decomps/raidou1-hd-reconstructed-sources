#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void AW_SlashInit(void);
s32 AW_SlashAdd(s32 _ListID, f32 _RootPosDir, f32 _RootPosLen, f32 _RootPosY, f32 _RootRotX, f32 _RootRotY, f32 _RootRotZ, f32 _Speed, f32 _Size, s32 _PrefabIdx);
void AW_SlashDeleteAll(void);
void AW_SlashClearPosLink(void);
void AW_SlashCalc_Slash(AW_WORK_t *aWork);
void AW_SlashDraw_Slash(AW_WORK_t *aWork);
