#pragma once
#include "types.h"
#include "basic.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;
typedef struct fldResourceLightPath_t fldResourceLightPath_t;
typedef struct fldResourcePathData_t fldResourcePathData_t;

extern dds3BasicFunction_t *Function;

void GetElement(u32 *segment, f32 *weight, fldResourcePathData_t *pData, f32 frame);
dds3Basic_t *dds3PathBasicAdd(u32 serialID, void *pData, char *pName);
dds3PathBasicControl_t *dds3PathBasicMakeControl(dds3Basic_t *pBasic);
void dds3PathBasicFreeControl(dds3PathBasicControl_t *pControl);
void dds3PathBasicControlGetPos(dds3PathBasicControl_t *pControl);
void dds3PathBasicControlGetRot(dds3PathBasicControl_t *pControl);
void dds3PathBasicControlGetLight(dds3PathBasicControl_t *pControl, fldResourceLightPath_t *resource);
f32 dds3PathBasicControlGetFovy(dds3PathBasicControl_t *pControl);
bool dds3PathBasicControlNextStep(dds3PathBasicControl_t *pControl);
void dds3PathBasicControlAlterMode(dds3PathBasicControl_t *pControl, DDS3_PATHBASIC_CONTROL mode);
DDS3_PATHBASIC_CONTROL dds3PathBasicPathControlGetMode(dds3PathBasicControl_t *pControl);
void dds3PathBasicControlSetRatio(dds3PathBasicControl_t *pControl, f32 ratio);
f32 dds3PathBasicControlGetRatio(dds3PathBasicControl_t *pControl);
void dds3PathBasicPause(dds3PathBasicControl_t *pControl);
void dds3PathBasicPauseOff(dds3PathBasicControl_t *pControl);
void dds3PathBasicLoopOn(dds3PathBasicControl_t *pControl);
void dds3PathBasicLoopOff(dds3PathBasicControl_t *pControl);
