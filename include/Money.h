#pragma once
#include "types.h"

typedef struct Money Money;
typedef struct shp_UI_manager_TextSet shp_UI_manager_TextSet;

struct Money {
    shp_UI_manager_TextSet *moneyNum;
    shp_UI_manager_TextSet *title;
    shp_UI_manager_TextSet *en;
};
