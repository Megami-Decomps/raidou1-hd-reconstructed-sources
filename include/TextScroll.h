#pragma once
#include "types.h"

typedef struct TextScroll TextScroll;

struct TextScroll {
    s32 StopCnt;
    f32 MoveTime;
    bool FastSaveflag;
    bool MojiMoveflag;
    bool Startflag;
    bool StopMojiflag;
    sdfVector3_t StartPosbup;
    s32 StartIndex;
    void *tmp_;
    void *textInfo_;
};
