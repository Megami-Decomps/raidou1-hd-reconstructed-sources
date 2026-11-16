#pragma once
#include "types.h"

typedef struct SBTLMAIN_DATA SBTLMAIN_DATA;

struct SBTLMAIN_DATA {
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 offset_x;
    f32 offset_z;
    s32 encountno;
    s32 type;
    s16 mode;
    s16 stock_id;
    s32 flg;
    s32 type2;
    s32 NakamaID;
    s32 EnemyID;
};
