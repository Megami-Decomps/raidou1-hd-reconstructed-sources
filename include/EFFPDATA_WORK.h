#pragma once
#include "types.h"
#include "SBTLEFF_BEDTYPE.h"
#include "SBTLEFF_FLG.h"

typedef struct EFFPDATA_WORK EFFPDATA_WORK;

struct EFFPDATA_WORK {
    SBTLEFF_BEDTYPE type;
    s32 eplno;
    f32 starttime;
    f32 life;
    f32 fadeout_time;
    u8 iti;
    s32 iti_no;
    s8 takasa;
    s8 muki;
    f32 scale;
    SBTLEFF_FLG flg;
};
