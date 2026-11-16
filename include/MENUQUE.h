#pragma once
#include "types.h"

#define ROOT 1
#define SKILL_1 2
#define SKILL_2 3
#define COMMON 4
#define TARGET 5
#define ITEM 6
#define NAKAMA 7
#define STOCK 8
#define OPEN 1
#define CLOSE 2

typedef struct MenuQue MenuQue;
typedef struct Menu_t Menu_t;

struct MenuQue {
    s32 type;
    s32 index;
    s32 mode;
    s32 count;
    s32 step;
    s32 wait;
    s32 cidx;
    MenuQue *next;
    Menu_t *menu;
};
