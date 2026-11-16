#pragma once
#include "types.h"

typedef struct SBTLMAHOJIN_LISTWORK SBTLMAHOJIN_LISTWORK;
typedef struct sbtlmahojin_worktag sbtlmahojin_worktag;

struct sbtlmahojin_worktag {
    sdfVector4_t pos;
    sdfVector4_t apos[4];
    s32 ListID;
    s32 serialID;
    s32 member_num;
    s32 member_stock;
    s32 member_max;
    u8 dataflg;
    u16 datatype;
    s32 mhjinno;
    s32 restartnum;
    s32 mode;
    u8 flg;
    s32 status;
    s32 counter;
    f32 area_r;
    f32 move_area_r;
    f32 atime;
    s32 actcounter;
    s32 actcounter_max;
    sbtlmahojin_worktag *prev;
    sbtlmahojin_worktag *next;
};

struct SBTLMAHOJIN_LISTWORK {
    s32 num;
    s32 serial;
    sbtlmahojin_worktag *wk;
};
