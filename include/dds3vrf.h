#pragma once
#include "types.h"

extern f32 VRF_DeltaTime;
extern f32 FPS60;
extern f32 VRF;
extern bool VRF_Active;

void dds3InitVRF(void);
void dds3BeginVRF(void);
void VRF_SetActive(bool _act);
