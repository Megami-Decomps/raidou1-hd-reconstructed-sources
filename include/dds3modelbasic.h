#pragma once
#include "types.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct sdfModelDef_t sdfModelDef_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;
typedef struct sdfMotionPlayBook_t sdfMotionPlayBook_t;

extern dds3BasicFunction_t *Function;

dds3Basic_t *dds3ModelBasicAdd(u32 serialID, sdfModelDef_t *pModelDef, sdfMotionPlayBook_t *pMotDef, dds3Basic_t *pTextureBasic, char *pName);
dds3Basic_t *dds3ModelBasicAdd2(u32 serialID, sdfModelDef_t *pModelDef, sdfMotionPlayBook_t *pMotDef, char *pName);
sdfModelRootNode_t *dds3ModelBasicMakeRootNode(dds3Basic_t *pBasic);
sdfMotionCtrlr_t *dds3ModelBasicMakeMotion(dds3Basic_t *pBasic, sdfModelRootNode_t *pRootNode);
