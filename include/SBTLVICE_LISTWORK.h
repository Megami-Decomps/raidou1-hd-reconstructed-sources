#pragma once
#include "types.h"

typedef struct SBTLVICE_LISTWORK SBTLVICE_LISTWORK;
typedef struct SBTLVICE_WORKT SBTLVICE_WORKT;

struct SBTLVICE_WORKT {
    s32 acterID;
    s32 st;
    u32 flg;
    s16 mode;
    s32 para;
    SBTLVICE_WORKT *prev;
    SBTLVICE_WORKT *next;
};

struct SBTLVICE_LISTWORK {
    s32 serial;
    s32 num;
    SBTLVICE_WORKT *wk;
};
