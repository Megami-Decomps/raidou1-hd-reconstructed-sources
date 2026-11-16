#pragma once
#include "types.h"
#include "libsdf.h"

typedef struct sdfModelRootNode_t sdfModelRootNode_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;
typedef struct sdfMotionPlayBook_t sdfMotionPlayBook_t;

sdfMotionCtrlr_t *sdfMotionCtrlrNew(sdfModelRootNode_t *aModel, sdfMotionPlayBook_t *aBook);
void sdfMotionCtrlrFree(sdfMotionCtrlr_t *aCtrlr);
void sdfMotionChangeBlend(sdfMotionCtrlr_t *aCtrlr, s32 aCutNum, SDF_MOTION aType, f32 aPreFrame, f32 aBlendLeng);
void sdfMotionChange(sdfMotionCtrlr_t *aCtrlr, s32 aCutNum, SDF_MOTION aType);
void sdfMotionSeek(sdfMotionCtrlr_t *aCtrlr, f32 aFrame);
void sdfMotionNext(sdfMotionCtrlr_t *aCtrlr);
void sdfMotionPause(sdfMotionCtrlr_t *aCtrlr);
void sdfMotionPauseOff(sdfMotionCtrlr_t *aCtrlr);
void sdfMotionUpdate(sdfModelRootNode_t *modelRoot);
