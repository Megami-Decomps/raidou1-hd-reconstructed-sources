#pragma once
#include "types.h"

typedef enum {
    EFFPARTSLIST_ITEM_COPY = 1,
    EFFPARTSLIST_ITEM_RESOURCE = 2,
} EFFPARTSLIST_ITEM;

typedef struct effPartsListItemParams_t effPartsListItemParams_t;
typedef struct effPartsListItem_t effPartsListItem_t;
typedef struct effParts_t effParts_t;

struct effPartsListItem_t {
    effPartsListItemParams_t *param;
    effParts_t *hParts;
    effParts_t *resource_hParts;
    EFFPARTSLIST_ITEM flag;
    char *name;
    effPartsListItem_t *prev;
    effPartsListItem_t *next;
};
