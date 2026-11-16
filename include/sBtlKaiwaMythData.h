#pragma once
#include "types.h"

typedef struct sBtlKaiwaMythData sBtlKaiwaMythData;

struct sBtlKaiwaMythData {
    s16 nak_devilID;
    s16 ene_devilID;
    s32 result;
    s16 msgNo[10];
    f32 pos_n[4];
    f32 pos_e[4];
};
