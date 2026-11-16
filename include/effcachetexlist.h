#pragma once
#include "types.h"

typedef struct ctexlHandle_t ctexlHandle_t;
typedef struct ctexlHandle_t_Resource ctexlHandle_t_Resource;
typedef struct effCacheTexList_Anim_t effCacheTexList_Anim_t;

ctexlHandle_t *effCacheTexCreate(ctexlHandle_t_Resource *pTLP);
void effCacheTexDelete(ctexlHandle_t *hCTexList);
ctexlHandle_t *Copy(ctexlHandle_t *hCTexList);
void effCacheTexAnimGet(ctexlHandle_t *hCTexList, u32 frame, effCacheTexList_Anim_t *pAnim);
void *effCacheTexImageLoadLinkOt(ctexlHandle_t *hCTexList, effCacheTexList_Anim_t *pAnim);
