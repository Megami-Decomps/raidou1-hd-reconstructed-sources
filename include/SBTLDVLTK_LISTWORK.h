#pragma once
#include "types.h"

typedef struct SBTLDVLTK_LISTWORK SBTLDVLTK_LISTWORK;
typedef struct SBTLDVLTK_WORK SBTLDVLTK_WORK;

struct SBTLDVLTK_LISTWORK {
    s32 num;
    s32 samecnt;
    s32 resetcounter;
    SBTLDVLTK_WORK *dwk;
};
