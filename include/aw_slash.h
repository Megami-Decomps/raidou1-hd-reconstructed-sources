#pragma once
#include "types.h"

typedef struct AW_WORK_t AW_WORK_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

void Init(void);
s32 Add(SBTLUNIT_WORK *wk, s32 _TblIdx);
void DeleteAll(void);
void ClearPosLink(void);
void Calc_Slash(AW_WORK_t *aWork);
void Draw_Slash(AW_WORK_t *aWork);
