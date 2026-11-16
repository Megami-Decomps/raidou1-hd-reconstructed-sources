#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;

void Init(void);
s32 Add(void);
s32 Add_2(s32 _SubIdx);
void DeleteAll(void);
void Cng(void);
void Cng2(void);
void Cng3(void);
void SetTargetDead(void);
void SetTargetDeadSkill(const sdfVector3_t *_Pos3D);
void OnVisible(const sdfVector3_t *_Pos3D);
void OffVisible(void);
bool ChkVisible(void);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
