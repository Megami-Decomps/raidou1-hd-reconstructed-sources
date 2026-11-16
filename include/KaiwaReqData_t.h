#pragma once
#include "types.h"

typedef struct KaiwaReqData_t KaiwaReqData_t;

struct KaiwaReqData_t {
    s8 reqno;
    s32 flg0;
    s32 flg1;
    s32 flg2;
};
