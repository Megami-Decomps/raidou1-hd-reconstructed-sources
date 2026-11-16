#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern SBTLUNIT_WORK *supportWk;

void sbtlInit(void);
void sbtlProc(void);
void sbtlEnd(void);
s32 sbtlSelectDevil(void);
