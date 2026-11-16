#pragma once
#include "types.h"
#include "GOH_MENU_ID.h"

typedef enum {
    GOH_MENU_FLAG_RELEASE = 1,
    GOH_MENU_FLAG_LOAD_SPR = 2,
    GOH_MENU_FLAG_DRAW = 4,
    GOH_MENU_FLAG_CALL_DRAWBACK0 = 8,
    GOH_MENU_FLAG_CALL_DRAWBACK1 = 16,
    GOH_MENU_FLAG_DRAWBACK0 = 32,
    GOH_MENU_FLAG_DRAWBACK1 = 64,
    GOH_MENU_FLAG_DRAWBACK1_RESET = 128,
} GOH_MENU_FLAG;

typedef enum {
    GOH_MENU_STEP_MAIN = 0,
    GOH_MENU_STEP_DRAW_OFF = 1,
    GOH_MENU_STEP_RELEASE = 2,
    GOH_MENU_STEP_END = 3,
} GOH_MENU_STEP;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagGOH_MENU_WORK tagGOH_MENU_WORK;

struct tagGOH_MENU_WORK {
    dds3ProcessID_t *drawPID;
    dds3ProcessID_t *menuPID;
    sprHandle_t *hSpr;
    GOH_MENU_STEP step;
    GOH_MENU_FLAG flag;
    s16 count;
    GOH_MENU_ID iMenuIndex;
    u8 alpha[2];
    s8 alpha_type[2];
    s8 alpha_cnt[2];
    s16 dummy;
};
