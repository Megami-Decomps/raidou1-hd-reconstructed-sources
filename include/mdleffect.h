#pragma once
#include "types.h"

typedef struct dds3ModelEffectCtrlr_t dds3ModelEffectCtrlr_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct mdlEffectResrcList_t mdlEffectResrcList_t;

void mdlEffectCreateResrc_D3P(mdlEffectResrcList_t *listPtr, void *data);
void mdlEffectCreateResrc_IPU(mdlEffectResrcList_t *listPtr, void *data);
mdlEffectResrcList_t *mdlEffectResrcListNew(s32 initCapa);
void mdlEffectResrcListFree(mdlEffectResrcList_t *efcResList);
void mdlEffectGen(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aPlayGroup);
void mdlFree(dds3ModelEffectCtrlr_t *aCtrlr);
void mdlEffectStop(dds3ModelHandle_t *aHandle, s32 aPlayGroup);
void mdlLink(dds3ModelHandle_t *aHandle, dds3ModelEffectCtrlr_t *aEffect);
void mdlEffectSetColorSub(dds3ModelHandle_t *aHandle, dds3ModelEffectCtrlr_t *aEffect, const sdfVector4_t *aColor);
void mdlEffectSetScaleSub(dds3ModelHandle_t *aHandle, dds3ModelEffectCtrlr_t *aEffect, f32 scale);
