#pragma once
#include "types.h"

typedef struct CamOffset CamOffset;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;

extern dds3BasicFunction_t *Function;

void MakeCamera(dds3Basic_t *pBasic);
dds3ObjectBaseControlWorkData_t *dds3CameraObjectBasicGetControlWorkData(dds3Basic_t *pBasic);
dds3Basic_t *dds3CameraObjectBasicAddDef(u32 serialID);
dds3Basic_t *dds3CameraObjectBasicAddTypeFree(u32 serialID, const sdfVector4_t *pos, const sdfVector4_t *rot);
dds3Basic_t *dds3CameraObjectBasicAddTypeLookAt(u32 serialID, const sdfVector4_t *eyePos, const sdfVector4_t *targetPos, const sdfVector4_t *vertical);
dds3Basic_t *dds3CameraObjectBasicAdd(u32 serialID, const sdfVector4_t *eyePos, const sdfVector4_t *eyeVector, const sdfVector4_t *vertical, f32 fovy, u32 mode);
void dds3CameraObjectBasicDelete(dds3Basic_t *pBasic);
void dds3CameraObjectBasicGetCameraTM(dds3Basic_t *pBasic);
void dds3CameraObjectBasicSetTargetPos(dds3Basic_t *pBasic, const sdfVector4_t *targetPos);
void dds3CameraObjectBasicGetTargetPos(dds3Basic_t *pBasic);
void dds3CameraObjectBasicSetFovy(dds3Basic_t *pBasic, f32 fovy);
f32 dds3CameraObjectBasicGetFovy(dds3Basic_t *pBasic);
void dds3CameraObjectBasicGetTgtCam(dds3Basic_t *pBasic, sdfVector4_t *tgtpos, sdfVector4_t *campos);
u32 dds3CameraObjectBasicGetMode(dds3Basic_t *pBasic);
void dds3CameraObjectBasicAlterMode(dds3Basic_t *pBasic, u32 mode);
void dds3CameraObjectBasicSetTgtCam(dds3Basic_t *pBasic, const sdfVector4_t *tgtpos, const sdfVector4_t *campos);
bool dds3CameraObjectBasicFourceCalc(dds3Basic_t *pBasic, CamOffset *cof);
