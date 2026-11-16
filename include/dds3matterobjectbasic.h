#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;

extern dds3BasicFunction_t *Function;

dds3ObjectBaseControlWorkData_t *dds3MatterObjectBasicGetControlWorkData(dds3Basic_t *pBasic);
dds3Basic_t *dds3MatterObjectBasicAdd(u32 serialID, const sdfVector4_t *pos, const sdfVector4_t *rot);
void dds3MatterObjectBasicDelete(dds3Basic_t *aPtr);
void dds3MatterObjectBasicSetOt(dds3Basic_t *aPtr, DDS3_MODEL_OT idx);
void dds3MatterObjectBasicSetHojiID(dds3Basic_t *aPtr, s32 hojiID);
s32 dds3MatterObjectBasicGetHojiID(s32 resID);
void dds3MatterObjectBasicSetAlpMode(dds3Basic_t *aPtr, s32 alpmode);
s32 dds3MatterObjectBasicGetAlpMode(dds3Basic_t *aPtr);
void dds3MatterObjectBasicDrawMode(s32 mode);
void dds3MatterObjectBasicPosToBase(dds3Basic_t *aPtr);
