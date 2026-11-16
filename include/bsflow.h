#pragma once
#include "types.h"
#include "BOSSACT.h"

void Init(void);
void SetAction(BOSSACT act);
void ClrAction(void);
bool IsAction(BOSSACT act);
void SetCamDone(void);
bool IsCamDone(void);
