#pragma once
#include "types.h"

typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfModelDef_t sdfModelDef_t;
typedef struct sdfModelDrawEnv_t sdfModelDrawEnv_t;
typedef struct sdfModelExtraChunkMarkPos_t sdfModelExtraChunkMarkPos_t;
typedef struct sdfModelNode_t sdfModelNode_t;
typedef struct sdfModelOt_t sdfModelOt_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;

sdfModelRootNode_t *sdfModelRootNew(void *modelObj);
void sdfModelRootFree(sdfModelRootNode_t *aRoot);
sdfModelNode_t *sdfModelSearchNode(sdfModelRootNode_t *aRoot, u32 aId);
sdfModelRootNode_t *sdfModelMake(sdfModelDef_t *aModelData, void *modelObj);
sdfModelRootNode_t *sdfModelMake_2(sdfModelDef_t *aModelData);
s32 sdfModelGetNodeIndexByName(sdfModelRootNode_t *aRoot, char *aName);
char *sdfModelGetNodeName(sdfModelRootNode_t *aRoot, s32 aIndex);
void sdfModelEvalTm(sdfModelRootNode_t *aRoot);
void sdfModelOtInit(sdfModelOt_t *aModelOt, sdfGrOt_t *aOt0, sdfGrOt_t *aOt1, sdfGrOt_t *aOt2, sdfGrOt_t *aOt3);
void sdfModelLinkOt(sdfModelOt_t *aOt, sdfModelRootNode_t *aRoot);
void sdfModelLinkOt_PosOnly(sdfModelRootNode_t *aRoot);
void sdfModelSetDrawEnv(sdfModelDrawEnv_t *aEnv);
void sdfModelDrawEnvLinkOt(sdfModelOt_t *aOt, sdfModelDrawEnv_t *aEnv);
s32 sdfModelGetMarkPosCount(sdfModelRootNode_t *aRoot);
void sdfModelMakeMarkPosMatrix(sdfModelRootNode_t *aRoot, sdfModelExtraChunkMarkPos_t *aMark);
void sdfModelMakeMarkPos(sdfModelRootNode_t *aRoot, sdfModelExtraChunkMarkPos_t *aMark);
sdfModelExtraChunkMarkPos_t *sdfModelSearchMarkPosData(sdfModelRootNode_t *aRoot, s32 aId);
bool sdfModelGetMarkPosMatrix(sdfModelRootNode_t *aRoot, s32 aId);
bool sdfModelGetMarkPos(sdfModelRootNode_t *aRoot, s32 aId);
s32 sdfModelGetUniqueID(sdfModelRootNode_t *aRoot);
