#pragma once
#include "types.h"

typedef struct CmpScreenShotParTbl_Tbl CmpScreenShotParTbl_Tbl;
typedef struct ScsCameraPar ScsCameraPar;
typedef struct cmpStatusLight_t cmpStatusLight_t;
typedef struct cmpStatusModel_t cmpStatusModel_t;

struct ScsCameraPar {
    f32 fov;
    f32 width;
};

struct CmpScreenShotParTbl_Tbl {
    char *devilName;
    s32 devilId;
    cmpStatusModel_t *modelPar;
    cmpStatusLight_t *lightPar;
    ScsCameraPar *cameraPar;
};
