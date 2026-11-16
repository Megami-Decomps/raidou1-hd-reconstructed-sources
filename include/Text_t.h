#pragma once
#include "types.h"

typedef struct Text_t Text_t;

struct Text_t {
    u16 code;
    u16 draw_count;
    s32 lx;
    s32 ly;
    s32 lw;
    u32 color;
    u32 color_base;
    u32 color_edge;
    u8 col_no;
    u8 style;
    u8 tp;
    u8 mode;
    u8 width;
    u8 height;
    Text_t *prev;
    Text_t *next;
    u16 chcode;
    u32 tag_flag[6];
    s32 wait;
    s32 font_id;
};
