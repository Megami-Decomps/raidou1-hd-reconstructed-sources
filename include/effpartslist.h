#pragma once
#include "types.h"

typedef struct effPartsListItemParams_t effPartsListItemParams_t;
typedef struct effPartsListItem_t effPartsListItem_t;
typedef struct effPartsListPose_t effPartsListPose_t;
typedef struct plistHandle_t plistHandle_t;
typedef struct plistHandle_t_Resource plistHandle_t_Resource;

void effPartsPoseInit(effPartsListPose_t *pPose);
plistHandle_t *effPartsNew(effPartsListPose_t *pose);
plistHandle_t *Create(plistHandle_t_Resource *pPartsListData);
void effPartsCreateFinish(plistHandle_t *hPartsList);
plistHandle_t *effPartsCreateD3P(u16 type, void *pPartsListData);
void effPartsDraw(void *handle);
void effPartsDelete(void *handle);
plistHandle_t *Copy(void *handle);
void effPartsPositionSet(void *handle, const sdfVector4_t *pPos);
void effPartsRotateSet(plistHandle_t *hPartsList, const sdfVector4_t *pRot);
void effPartsScaleSet(void *handle, f32 scale);
void effPartsColorSet(void *handle, u32 abgr);
void ColorSet(void *handle, const sdfVector4_t *abgr);
void effPartsRotateMatrixSet(void *handle, const sdfMatrix4_t *pMatrix);
void effPartsItemParamsSet(effPartsListItem_t *pItem, effPartsListItemParams_t *pParams);
effPartsListItem_t *effPartsItemGet(plistHandle_t *hPartsList, u32 index);
