#pragma once
#include "types.h"

typedef struct sdf3DFogPacket_t sdf3DFogPacket_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdf3DLight_t sdf3DLight_t;
typedef struct sdf3DScreenParam_t sdf3DScreenParam_t;
typedef struct sdf3DViewportPacket_t sdf3DViewportPacket_t;

extern sdfMatrix4_t ScreenTm;
extern sdfMatrix4_t CameraTm;
extern sdf3DLightParallelPacket_t *LightDefault;
extern sdf3DFogPacket_t *FogDefault;
extern void *cameraObj;
extern bool GlobalParamFlag;
extern f32 GlobalParamScaleX;
extern f32 GlobalParamScaleY;
extern f32 GlobalParamTransX;
extern f32 GlobalParamTransY;

void sdf3MakeViewportPacket(sdf3DViewportPacket_t *aPacket, sdf3DScreenParam_t *aParam, sdfMatrix4_t *aCamera, void *cameraObject);
void sdf3SetCamera(sdf3DScreenParam_t *aParam, sdfMatrix4_t *aCamera, void *cameraObject);
void sdf3SetDefaultLight(sdf3DLightParallelPacket_t *aLight);
void sdf3SetDefaultFog(sdf3DFogPacket_t *aFog);
void sdf3MakeScreenParam(sdf3DScreenParam_t *aParam);
void sdf3MakeLightParallelPacket(sdf3DLightParallelPacket_t *aPacket, sdf3DLight_t *aLights, const sdfVector4_t *aAmbient, bool sceneColor);
void sdf3MakeSpecular(void);
void sdf3MakeSpecular2(u8 *data);
void sdf3MakeSpecular3(void);
void sdf3MakeRefmap(u8 *data);
void sdf3Init(void);
void Init(void *list);
