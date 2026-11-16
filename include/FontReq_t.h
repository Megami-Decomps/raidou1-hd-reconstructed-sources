#pragma once
#include "types.h"

typedef struct FontReq_t FontReq_t;
typedef struct Text_t Text_t;

struct FontReq_t {
    u8 draw_spd;
    u8 last_draw_spd;
    s8 space;
    s16 x_size;
    s16 y_size;
    s16 voice;
    s32 x;
    s32 y;
    s32 w_pxls;
    u32 priority;
    s32 strlen;
    Text_t *str;
    Text_t *str_end;
    FontReq_t *head;
    FontReq_t *prev;
    FontReq_t *next;
    char *tag_id;
    s32 work[2];
    bool local;
};
