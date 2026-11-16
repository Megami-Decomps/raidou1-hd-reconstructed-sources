#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagSHP_BACK_WK tagSHP_BACK_WK;
typedef struct tagSHP_MENU_WK tagSHP_MENU_WK;
typedef struct tagSHP_WK tagSHP_WK;

struct tagSHP_MENU_WK {
    s16 menuId;
    s16 actType;
    s16 charId;
    s16 objId;
};

struct tagSHP_BACK_WK {
    f32 fx;
    f32 fy;
    f32 posx;
    f32 posy;
    f32 movx;
    f32 movy;
    f32 w;
    f32 h;
    f32 ratio;
    s32 frame;
    s32 count;
    s32 type;
};

struct tagSHP_WK {
    dds3ProcessID_t *drawPID;
    dds3ProcessID_t *cntrPID;
    u8 *pDatScr[3];
    s32 charID[9];
    s16 index[768];
    s8 step;
    s8 stepAct;
    s16 count;
    u32 stat;
    s8 shopType;
    s8 ctrlType;
    f32 curPosx;
    f32 curPosy;
    f32 curMovx;
    f32 curMovy;
    f32 curTgtx;
    f32 curTgty;
    s32 curCount;
    tagSHP_MENU_WK *Menu[16];
    tagSHP_MENU_WK *pMenu;
    s8 menuMax;
    s32 yen;
    s32 mag;
    s32 trade;
    s32 selNo;
    s32 drwNo;
    s32 topNo;
    s32 selMax;
    s32 drwMax;
    s32 selNum;
    s32 selNumMax;
    tagSHP_BACK_WK *back;
};
