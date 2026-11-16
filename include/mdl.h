#pragma once
#include "types.h"
#include "MODELTYPE.h"

typedef enum {
    MODEL_REGFLAG_AUTOFREE = 1,
    MODEL_REGFLAG_STAY = 2,
    MODEL_REGFLAG_MOTIONAUTOCREATE = 256,
    MODEL_REGFLAG_MOTIONAUTOSTART = 512,
    MODEL_REGFLAG_STD = 257,
} MODEL_REGFLAG;

typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ModelResrc_t dds3ModelResrc_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdfModelOt_t sdfModelOt_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;
typedef struct sdfPacDecodeResrcHandle_t sdfPacDecodeResrcHandle_t;

void mdlDummy(void *parm);
char *mdlGetModelName(MODELTYPE aMajor, s32 aMinor);
char *mdlGetDevilModelName(s32 id);
s32 mdlGetDevilModelNo(s32 id);
s32 mdlGetDevilModelNo2(s32 id);
char *mdlGetEventModelName(s32 id);
void mdlHide(dds3ModelHandle_t *HNDL);
void mdlHideBG(dds3ModelHandle_t *HNDL);
void mdlShow(dds3ModelHandle_t *HNDL);
void mdlShowBG(dds3ModelHandle_t *HNDL);
bool mdlChkHide(dds3ModelHandle_t *HNDL);
void mdlHideUpdatePos(dds3ModelHandle_t *HNDL, bool _OnOff);
f32 mdlGetRadius(dds3ModelHandle_t *HNDL);
s32 mdlGetMotionLength(dds3ModelHandle_t *HNDL);
s32 mdlGetMotionFrame(dds3ModelHandle_t *HNDL);
f32 mdlGetMotionFrameF(dds3ModelHandle_t *HNDL);
f32 mdlGetMotionFrameFS(dds3ModelHandle_t *HNDL);
f32 mdlGetMotionFrameAnimator(dds3ModelHandle_t *HNDL);
f32 mdlGetMotionNormalAnimator(dds3ModelHandle_t *HNDL);
bool mdlChkMotionEnd(dds3ModelHandle_t *HNDL);
f32 mdlGetMotionSpeed(dds3ModelHandle_t *HNDL);
void mdlSetMotionSpeed(dds3ModelHandle_t *HNDL, f32 spd);
void mdlSetMotionSkipFrame(dds3ModelHandle_t *HNDL, f32 skipframe);
void mdlSetMotionBlendTree1D(dds3ModelHandle_t *HNDL, f32 _BlendTree1D);
void mdlSetMotionBlendTree2D(dds3ModelHandle_t *HNDL, f32 _BlendTree2DX, f32 _BlendTree2DY);
bool mdlHasMotion(dds3ModelHandle_t *HNDL);
s16 mdlGetMotionMajorNum(dds3ModelHandle_t *HNDL);
s16 mdlGetMotionMinorNum(dds3ModelHandle_t *HNDL);
void mdlSetLight(dds3ModelHandle_t *HNDL, sdf3DLightParallelPacket_t *LIGHT);
void mdlInit(void);
dds3ModelResrc_t *mdlSearchResrc(MODELTYPE aMajor, s32 aMinor);
void mdlUnRegist(MODELTYPE aMajor, s32 aMinor);
dds3ModelResrc_t *mdlPrepare(MODELTYPE aMajor, s32 aMinor, bool aBlockMode);
dds3ModelResrc_t *mdlLoadResrc(MODELTYPE aMajor, s32 aMinor);
dds3ModelHandle_t *mdlLoad(MODELTYPE aMajor, s32 aMinor);
void mdlRegistDummy(MODELTYPE aMajor, s32 aMinor);
void Free(dds3ModelHandle_t *aHandle);
void Link(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt);
void mdlLink_NoDraw(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt);
void mdlLink_Kubi(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt, s32 node, f32 rx, f32 ry);
void mdlLoopMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber);
void mdlSingleMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber);
void mdlSmoothLoopMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber, f32 aBeforeLeng, f32 aSmoothLeng, f32 _SkipFrame);
void mdlSmoothSingleMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber, f32 aBeforeLeng, f32 aSmoothLeng, f32 _SkipFrame);
sdfMotionCtrlr_t *mdlGetMotionCtrlr(dds3ModelHandle_t *aHandle, s32 aGroup);
s32 mdlGetMotionNum(dds3ModelHandle_t *aHandle, s32 aGroup);
s32 mdlGetMotionLengthEx(dds3ModelHandle_t *aHandle, s32 aGroup);
s32 mdlGetMotionFrameEx(dds3ModelHandle_t *aHandle, s32 aGroup);
bool mdlChkMotionEndEx(dds3ModelHandle_t *aHandle, s32 aGroup);
void mdlSetMotionSpeedEx(dds3ModelHandle_t *aHandle, s32 aGroup, f32 speed);
void mdlGetPosition(dds3ModelHandle_t *aHandle);
void mdlSetPosition(dds3ModelHandle_t *aHandle);
void mdlGetRotate(dds3ModelHandle_t *aHandle);
void mdlSetRotate(dds3ModelHandle_t *aHandle);
void mdlGetScale(dds3ModelHandle_t *aHandle);
void mdlSetScale(dds3ModelHandle_t *aHandle);
void mdlSetEffectScale(dds3ModelHandle_t *aHandle, f32 _scale);
sdfVector4_t mdlGetColor(dds3ModelHandle_t *aHandle);
void mdlSetEffectColor(dds3ModelHandle_t *aHandle, u32 aColor);
void SetEffectColor(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColor);
void mdlSetColor(dds3ModelHandle_t *aHandle, u32 aColor);
void mdlSetColor_And_EffAlp(dds3ModelHandle_t *aHandle, u32 aColor, f32 _EffAlp);
void SetColor(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColor);
void SetColor_And_EffAlp(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColor, f32 _EffAlp);
void mdlSetDitherAlphaUse(dds3ModelHandle_t *aHandle, bool aDitherAlpha);
void mdlSetDitherAlpha(dds3ModelHandle_t *aHandle, f32 aDitherAlpha);
void mdlSetDissolveAlpha(dds3ModelHandle_t *aHandle, f32 aDissolveAlpha);
void mdlSetColorChroma(dds3ModelHandle_t *aHandle, u32 aColorChroma);
void SetColorChroma(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColorChroma);
void mdlSetStoneUse(dds3ModelHandle_t *aHandle, bool aStoneUse);
void mdlMotionPause(dds3ModelHandle_t *aHandle);
void mdlMotionPauseOff(dds3ModelHandle_t *aHandle);
bool mdlHasMotionEx(dds3ModelHandle_t *aHandle, s32 aGroup);
MODELTYPE mdlGetMajorNum(dds3ModelHandle_t *aHandle);
s32 mdlGetMinorNum(dds3ModelHandle_t *aHandle);
s32 mdlGetNumOfCut(dds3ModelHandle_t *aHandle, s32 aGroup);
void mdlSetBustup(dds3ModelHandle_t *aHandle, bool _IsBustUp);
void mdlSetMdlEffectNonStop(dds3ModelHandle_t *aHandle, bool _IsNonStop);
void mdlPackDecode(MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags, void *buff, s32 leng);
void PackDecode(MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags, sdfPacDecodeResrcHandle_t *resrc);
