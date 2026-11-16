#pragma once
#include "types.h"

extern char *menuText;
extern char *helpText;
extern char *paformanceText;
extern char *renderingText;
extern s32 **minMaxPar;

char *GetSelectText(s32 _setPar, s32 _value);
void InitSelectCnt(void);
void Init(void);
void Update(void);
void Draw(void);
void BrightnessChange(void);
void ContrastChange(void);
void ChgConfigGraphicsAll(void);
