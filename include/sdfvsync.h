#pragma once
#include "types.h"

extern u32 Count;
extern bool firstFrame;
extern bool isUpdate;
extern f32 timeScale;
extern bool drawSkip;
extern bool drawSkipMode;
extern f32 _ElapsedTime_k__BackingField;
extern f32 frameTime;

void sdfBegin(void);
void sdfStep(void);
bool sdfIsUpdate(void);
void sdfSetFrameTime(f32 time);
void *sdfThread(void);
