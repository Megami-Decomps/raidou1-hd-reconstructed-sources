#pragma once
#include "types.h"

typedef struct DVLFOOTSE_WORK DVLFOOTSE_WORK;

struct DVLFOOTSE_WORK {
    u8 frameNum;
    u8 sedataNum;
    u16 flg;
    f32 frame[4];
};
