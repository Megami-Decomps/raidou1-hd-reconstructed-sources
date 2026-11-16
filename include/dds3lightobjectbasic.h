#pragma once
#include "types.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct fldResourceLightPath_t fldResourceLightPath_t;
typedef struct fldResourceLight_t fldResourceLight_t;

extern dds3BasicFunction_t *Function;

dds3ObjectBaseControlWorkData_t *dds3LightObjectBasicGetControlWorkData(dds3Basic_t *basic);
dds3Basic_t *Add(u32 serial);
void Delete(dds3Basic_t *basic);
void dds3LinkSceneLight(dds3Basic_t *basic, u32 frame);
void dds3UnlinkSceneLight(dds3Basic_t *basic);
void dds3LinkLightObjectToUnitObject(dds3Basic_t *lightbasic, dds3Basic_t *unitbasic, u32 frame);
void dds3UnlinkLightObjectFromUnitObject(dds3Basic_t *unitbasic, u32 frame);
void dds3SetLightObjectResoruce(dds3Basic_t *basic, fldResourceLight_t *resource);
void dds3SetLightObjectPathResoruce(dds3Basic_t *basic, fldResourceLightPath_t *resource);
