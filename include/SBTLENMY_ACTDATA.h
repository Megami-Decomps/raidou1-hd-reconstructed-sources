#pragma once
#include "types.h"
#include "SBTL_ACTAIMODE.h"

typedef enum {
    SBTLENMY_FLG_NORMAL = 1,
    SBTLENMY_FLG_REVERSE = 2,
    SBTLENMY_FLG_LOOP = 4,
    SBTLENMY_FLG_OFSPOS = 8,
    SBTLENMY_FLG_TIMERAND = 16,
} SBTLENMY_FLG;

typedef struct SBTLENMY_ACTDATA SBTLENMY_ACTDATA;

struct SBTLENMY_ACTDATA {
    s32 pathid;
    SBTLENMY_FLG flg;
    SBTL_ACTAIMODE type;
    s32 frame;
    s16 cnt;
    s16 jmpid;
};
