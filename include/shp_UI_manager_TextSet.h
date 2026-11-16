#pragma once
#include "types.h"

typedef enum {
    shp_UI_manager_Mode_NORMAL = 0,
    shp_UI_manager_Mode_SELECT = 1,
    shp_UI_manager_Mode_NON = 2,
    shp_UI_manager_Mode_NEW = 3,
} shp_UI_manager_Mode;

typedef struct shp_UI_manager_TextSet shp_UI_manager_TextSet;

struct shp_UI_manager_TextSet {
    void *TMProUGUI;
    shp_UI_manager_Mode mode;
};
