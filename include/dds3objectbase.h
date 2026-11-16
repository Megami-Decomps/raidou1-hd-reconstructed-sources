#pragma once
#include "types.h"
#include "MODELTYPE.h"
#include "basic.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;
typedef struct sdfModelOt_t sdfModelOt_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;

u32 BasicTypeToItemType(BASIC_TYPE type);
dds3ObjectBaseControlWorkData_t *dds3ObjectBaseInitControlWorkData(dds3Basic_t *pObjectBasic);
void dds3ObjectBaseFreeControlWorkData(dds3ObjectBaseControlWorkData_t *pControl);
void dds3ObjectBaseOnFlag(dds3Basic_t *pObjectBasic, u32 flag);
void dds3ObjectBaseOffFlag(dds3Basic_t *pObjectBasic, u32 flag);
bool dds3ObjectBaseCheckFlag(dds3Basic_t *pObjectBasic, DDS3_OBJECTBASE_FLAG flag);
void *dds3ObjectBaseSetUserValue(dds3Basic_t *pObjectBasic, void *pUserValue);
void *dds3ObjectBaseGetUserValue(dds3Basic_t *pObjectBasic);
dds3Basic_t *dds3ObjectBaseSetControlBasic(dds3Basic_t *pObjectBasic, dds3Basic_t *pItemBasic);
dds3Basic_t *dds3ObjectBaseSetControlBasicType(dds3Basic_t *pObjectBasic, dds3Basic_t *pItemBasic, u32 itemType);
dds3Basic_t *dds3ObjectBaseGetControlBasic(dds3Basic_t *pObjectBasic, u32 itemType);
dds3BasicArrayHandle_t *dds3ObjectBaseGetEventArray(dds3Basic_t *pObjectBasic);
void *dds3ObjectBaseGetModelHandle(dds3Basic_t *pObjectBasic);
void dds3ObjectBaseFreeModelHandle(dds3Basic_t *pObjectBasic);
void dds3ObjectBaseMakeUnit(dds3Basic_t *pObjectBasic, MODELTYPE major, s32 minor);
void dds3ObjectBaseMakeMatter(dds3Basic_t *pObjectBasic);
void dds3ObjectBaseMatterAnimeSpeed(dds3Basic_t *pObjectBasic, s32 mode);
bool dds3ObjectBaseRegistArea(dds3Basic_t *pObjectBasic);
f32 dds3ObjectBaseCalc_Cam_Model_Leng(dds3Basic_t *pObjectBasic, sdfModelRootNode_t *model_root);
void dds3ObjectBaseModelLinkOt(sdfModelOt_t *pModelOt, dds3Basic_t *pObjectBasic);
void dds3ObjectBaseCreateMover(dds3Basic_t *pObjectBasic);
bool dds3ObjectBaseSetPadControl(dds3Basic_t *pObjectBasic, dds3MoverBasicObjFunc_t pFuncPadControl);
bool dds3ObjectBaseSetPrimaryControl(dds3Basic_t *basic, dds3MoverBasicObjFunc_t func);
void dds3ObjectBaseMakePath(dds3Basic_t *pObjectBasic, dds3Basic_t *pPathBasic);
void dds3ObjectBaseFreePath(dds3Basic_t *pObjectBasic);
dds3PathBasicControl_t *dds3ObjectBaseGetPathControl(dds3Basic_t *pObjectBasic);
dds3ObjectBaseControlWorkData_t *dds3GetBaseControlWorkData(dds3Basic_t *pObjectBasic);
void dds3ObjectBaseSetControlBasicCamLen(dds3Basic_t *pObjectBasic);
f32 dds3ObjectBaseGetControlBasicCamLen(dds3Basic_t *pObjectBasic);
