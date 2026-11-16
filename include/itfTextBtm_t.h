#pragma once
#include "types.h"

typedef struct itfTextBtm_t itfTextBtm_t;

struct itfTextBtm_t {
    void *Frame;
    f32 SpcSize;
    f32 LineHeight;
    char *SpcStr;
    char *DmyStr;
    void *BtnList;
};
