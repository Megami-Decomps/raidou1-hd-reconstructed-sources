#pragma once
#include "types.h"

#define D_MOTMOVE_ARRAYNUM 8

typedef struct MOTIONMOVE_WORK MOTIONMOVE_WORK;
typedef struct MTIONMV_PARA MTIONMV_PARA;

struct MTIONMV_PARA {
    s16 motionno;
    s16 startframe;
    s16 endframe;
    s16 sokudo;
};

struct MOTIONMOVE_WORK {
    MTIONMV_PARA *para[8];
};
