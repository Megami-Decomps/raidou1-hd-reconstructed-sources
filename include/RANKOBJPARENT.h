#pragma once
#include "types.h"

typedef struct RANKOBJ RANKOBJ;
typedef struct RANKOBJPARENT RANKOBJPARENT;

struct RANKOBJPARENT {
    RANKOBJ *star1;
    RANKOBJ *star2;
    RANKOBJ *star3;
};
