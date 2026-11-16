#pragma once
#include "types.h"
#include "basic.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;

extern dds3BasicFunction_t *Function;
extern s32 movername;
extern char *movernamestr;

dds3Basic_t *dds3MoverBasicAdd(dds3Basic_t *pObjectBasic);
void dds3MoverBasicSetCallBackPrimaryControl(dds3Basic_t *mover, dds3MoverBasicObjFunc_t func);
void dds3MoverBasicSetPath(dds3Basic_t *pMoverBasic, dds3Basic_t *pPathBasic);
void dds3MoverBasicMakePath(dds3Basic_t *pMoverBasic);
void dds3MoverBasicFreePath(dds3Basic_t *pMoverBasic);
dds3PathBasicControl_t *dds3MoverBasicGetPathControl(dds3Basic_t *pMoverBasic);
bool dds3MoverBasicUpdate(dds3Basic_t *pBasic);
