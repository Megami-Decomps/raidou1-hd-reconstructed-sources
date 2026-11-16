#pragma once
#include "types.h"

typedef struct mapIcon_t mapIcon_t;

struct mapIcon_t {
    s32 _no;
    s16 _map;
    s16 _flor;
    s32 _point;
    f32 _ax;
    f32 _ay;
    s32 _type;
    s32 _amID1;
    s32 _amID2;
    s32 _flag;
    s32 _disp;
    s32 _warpNo;
};
