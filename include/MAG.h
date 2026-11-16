#pragma once
#include "types.h"

typedef struct MAG MAG;
typedef struct shp_UI_manager_TextSet shp_UI_manager_TextSet;

struct MAG {
    shp_UI_manager_TextSet *MAXMAG;
    shp_UI_manager_TextSet *NOWMAG;
};
