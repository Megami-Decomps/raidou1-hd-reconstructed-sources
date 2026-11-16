#pragma once
#include "types.h"
#include "TNEFFECT_BLEND.h"

typedef struct SDF_GS_ALPHA SDF_GS_ALPHA;
typedef struct SDF_GS_TEST SDF_GS_TEST;
typedef struct sdf3DScreenParam_t sdf3DScreenParam_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;

typedef sdf3DScreenParam_t *(*ScreenParamFunc)(void);
typedef void *(*CameraObjectFunc)(void);
typedef sdfMatrix4_t (*CameraTMFunc)(void);
typedef sdfVector4_t (*CameraTargetPosFunc)(void);
typedef sdfVector4_t (*CameraEyePosFunc)(void);
typedef sdfVector4_t (*CameraUpVectorFunc)(void);

extern s32 camID;
extern ScreenParamFunc *ScreenParam;
extern CameraObjectFunc *cameraObject;
extern CameraTMFunc *CameraTM;
extern CameraTargetPosFunc *CameraTargetPos;
extern CameraEyePosFunc *CameraEyePos;
extern CameraUpVectorFunc *CameraUpVector;
extern sdfGrOt_t **pOt_Table;

sdfGrOt_t *effOtGet(TNEFFECT_BLEND blend);
sdf3DScreenParam_t *effGetSelScreenParam(void);
void *effGetSelCameraObject(void);
sdfMatrix4_t effGetSelCameraTM(void);
sdfVector4_t effGetSelCameraTargetPos(void);
sdfVector4_t effGetSelCameraEyePos(void);
sdfVector4_t effGetSelCameraUpVector(void);
bool effScreenOffsetClipGet(void);
f32 effScreenAreaGet(f32 area);
sdfVector4_t effHermitianSpline(sdfVector4_t *pVertex, f32 percentage);
void effMatrixToQuat(const sdfMatrix4_t *pMatrix);
void effZTestOff(sdfDrawTag_t *drawTag, bool sw);
void effZTestOn(sdfDrawTag_t *drawTag, bool sw);
void effSetAlphaPacket(sdfDrawTag_t *drawTag, TNEFFECT_BLEND blend);
void effSetTestAlphaPacket(sdfDrawTag_t *drawTag, SDF_GS_TEST *test, SDF_GS_ALPHA *alpha);
