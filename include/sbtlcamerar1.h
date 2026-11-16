#pragma once
#include "types.h"

typedef struct SBTLCAMERA_WORK SBTLCAMERA_WORK;

void sBtlCameraCreateCamera(void);
bool sBtlCameraProc(void);
bool sBtlCameraSetPara(SBTLCAMERA_WORK *wk);
