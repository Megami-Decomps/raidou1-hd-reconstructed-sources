#pragma once
#include "types.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;

extern dds3BasicFunction_t *Function;

dds3Basic_t *dds3EventObjectBasicAdd(u32 serialID, const sdfVector4_t *pos, const sdfVector4_t *rot);
dds3ObjectBaseControlWorkData_t *dds3EventObjectBasicGetControlWorkData(dds3Basic_t *pBasic);
