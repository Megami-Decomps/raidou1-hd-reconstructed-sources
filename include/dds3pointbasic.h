#pragma once
#include "types.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PointBasicWorkData_t dds3PointBasicWorkData_t;
typedef struct fldResourcePoint_t fldResourcePoint_t;

dds3Basic_t *dds3PointBasicAdd(u32 serialID, fldResourcePoint_t *pData, char *pName);
void *dds3PointBasicGetResource(dds3Basic_t *pPointBasic);
dds3PointBasicWorkData_t *dds3PointBasicGetWorkData(dds3Basic_t *pBasic);
void dds3PointBasicGetPosPoseSet(dds3Basic_t *pBasic);
void dds3PointBasicGetRotPoseSet(dds3Basic_t *pBasic);
