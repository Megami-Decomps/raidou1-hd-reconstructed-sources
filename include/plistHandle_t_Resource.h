#pragma once
#include "types.h"

typedef struct effPartsListItemParams_t effPartsListItemParams_t;
typedef struct effPartsListItem_t_Resource effPartsListItem_t_Resource;
typedef struct effPartsListPose_t effPartsListPose_t;
typedef struct plistHandle_t_Resource plistHandle_t_Resource;

struct effPartsListItem_t_Resource {
    char *name;
    effPartsListItemParams_t *param;
    void *parts;
};

struct plistHandle_t_Resource {
    effPartsListPose_t *pose;
    effPartsListItem_t_Resource *items;
};
