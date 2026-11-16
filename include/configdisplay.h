#pragma once
#include "types.h"

extern char *menuText;
extern char *helpText;
extern char *screenText;
extern s32 **minMaxPar;
extern char *reslution_str;

char *GetSelectText(s32 _setPar, s32 _value);
void InitSelectCnt(void);
void Init(void);
void Update(void);
void Draw(void);
