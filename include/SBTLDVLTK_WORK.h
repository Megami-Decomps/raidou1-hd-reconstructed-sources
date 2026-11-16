#pragma once
#include "types.h"
#include "SBTLDVLTK_MODE.h"

typedef enum {
    SBTLDVLTK_ST_INIT = 0,
    SBTLDVLTK_ST_PROC = 1,
    SBTLDVLTK_ST_END = 2,
    SBTLDVLTK_ST_MAX = 3,
} SBTLDVLTK_ST;

typedef struct SBTLDVLTK_WAKUWORK SBTLDVLTK_WAKUWORK;
typedef struct SBTLDVLTK_WORK SBTLDVLTK_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct SBTLDVLTK_WAKUWORK {
    s32 st;
    s32 x;
    s32 y;
    s32 alpha;
    u32 rgb;
};

struct SBTLDVLTK_WORK {
    s32 listID;
    s32 devilid;
    s32 sklid;
    s32 seikaku;
    s32 counter;
    s32 cmpcounter;
    SBTLDVLTK_MODE mode;
    SBTLDVLTK_ST status;
    s32 resetcounter;
    s32 cmpreset;
    s32 samecnt;
    s32 sincount;
    s32 ofs_x;
    s32 ofs_y;
    s32 alpha;
    s32 mesType;
    bool gouto;
    char *gouto_text;
    bool tube_support;
    SBTLUNIT_WORK *tube_wk;
    SBTLDVLTK_WAKUWORK *wk[7];
    s32 icon_sprx;
    s32 icon_spry;
    s32 icon_alpha;
    s32 icon_counter;
    s32 icon_sprno;
    bool call_voice;
    bool overwrite_f;
    SBTLDVLTK_WORK *prev;
    SBTLDVLTK_WORK *next;
};
