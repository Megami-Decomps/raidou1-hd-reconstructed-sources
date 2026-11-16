#pragma once
#include "types.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;

extern dds3BasicFunction_t *Function;

void dds3UnitObjectBasicEL_LinkFree(dds3Basic_t *unitBasic);
void dds3UnitObjectBasicEL_Link(dds3Basic_t *unitBasic);
dds3ObjectBaseControlWorkData_t *dds3UnitObjectBasicGetControlWorkData(dds3Basic_t *pBasic);
dds3Basic_t *dds3UnitObjectBasicAdd(u32 serialID, const sdfVector4_t *aPos, const sdfVector4_t *aRot);
void dds3UnitObjectBasicDelete(dds3Basic_t *aPtr);
s32 dds3UnitObjectBasicGetStatus(dds3Basic_t *aPtr);
evtUnitHandle_t *dds3UnitObjectBasicGetUnitHandle(dds3Basic_t *b);
void dds3UnitObjectBasicSetOt(dds3Basic_t *aPtr, s32 idx);
s32 dds3UnitObjectBasicGetOt(dds3Basic_t *aPtr);
void dds3UnitObjectBasicSetKubiTerget(dds3Basic_t *pBasic, const sdfVector4_t *aTgt);
void dds3UnitObjectBasicSetKubiModori(dds3Basic_t *pBasic);
void dds3UnitObjectBasicKubiOn(dds3Basic_t *pBasic, s32 posid);
void dds3UnitObjectBasicKubiOff(dds3Basic_t *pBasic);
void dds3UnitObjectBasicSetDamageYure(dds3Basic_t *pBasic, f32 range);
void dds3UnitObjectBasicSetJumpOfsPos(dds3Basic_t *pBasic, f32 _X, f32 _Y, f32 _Z);
