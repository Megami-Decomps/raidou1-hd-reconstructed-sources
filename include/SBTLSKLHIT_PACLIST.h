#pragma once
#include "types.h"

typedef struct SBTLSKLHIT_PACDATAWORK SBTLSKLHIT_PACDATAWORK;
typedef struct SBTLSKLHIT_PACLIST SBTLSKLHIT_PACLIST;
typedef struct fileHandle_t fileHandle_t;

struct SBTLSKLHIT_PACLIST {
    fileHandle_t *hFile;
    s32 id;
    s32 num;
    s16 gstat;
    u32 status;
    SBTLSKLHIT_PACDATAWORK *pwk[32];
};
