#pragma once
#include "types.h"

typedef struct effPartsListItem_t effPartsListItem_t;
typedef struct effPartsListPose_t effPartsListPose_t;
typedef struct plistHandle_t plistHandle_t;

struct plistHandle_t {
    effPartsListPose_t *pose;
    u32 number;
    s32 frame;
    effPartsListItem_t *pLink;
    effPartsListItem_t *pLinkTail;
};
