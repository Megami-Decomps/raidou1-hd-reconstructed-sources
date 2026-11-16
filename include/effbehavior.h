#pragma once
#include "types.h"
#include "EFFBEHAVIOR_TYPE.h"

typedef struct bhvrHandle_t bhvrHandle_t;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_Params_Basic_t effBehavior_Params_Basic_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effBehavior_SR_Params_t effBehavior_SR_Params_t;
typedef struct effPosture_t effPosture_t;
typedef struct sdfBinary sdfBinary;

sdfVector4_t effColorAnimation(effBehavior_RGBParams_t *pRGB, effBehavior_AlphaParams_t *pAlpha, s32 frame, s32 life);
f32 effSRAnimation(effBehavior_SR_Params_t *pSR, f32 frame, f32 life);
void effAnimation(effPosture_t *pPosture, effBehavior_Params_Basic_t *pParams, s32 frame, const sdfVector4_t *pOldPos);
void effAnimation_Init(effPosture_t *pPosture, effBehavior_Params_Basic_t *pParams, s32 frame, const sdfVector4_t *pOldPos);
void effBlurInit(bhvrHandle_t *hBehavior, s32 number);
void effBlurReset(bhvrHandle_t *hBehavior, s32 number);
void effBlur(bhvrHandle_t *hBehavior, s32 number);
bhvrHandle_t *effCreate(EFFBEHAVIOR_TYPE type, u32 number, effBehavior_Params_Basic_t *pParams);
void Delete(bhvrHandle_t *hBehavior);
void effCalc(bhvrHandle_t *hBehavior);
void effEmitterPositionGet(bhvrHandle_t *hBehavior, sdfVector4_t *pPos);
void effEmitterPositionSet(bhvrHandle_t *hBehavior, const sdfVector4_t *pPos);
void effEmitterRotateGet(bhvrHandle_t *hBehavior, sdfVector4_t *pRot);
void effEmitterRotateSet(bhvrHandle_t *hBehavior, const sdfVector4_t *pRot);
void ScaleSet(bhvrHandle_t *hBehavior, f32 scale);
effBehavior_Params_Basic_t *effCreateParams(EFFBEHAVIOR_TYPE type, sdfBinary *bin);
