#pragma once
#include "types.h"

typedef struct ItemHelpWin ItemHelpWin;
typedef struct shp_UI_manager_TextSet shp_UI_manager_TextSet;

struct ItemHelpWin {
    shp_UI_manager_TextSet *pop;
    shp_UI_manager_TextSet *message;
    shp_UI_manager_TextSet *setsumei;
};
