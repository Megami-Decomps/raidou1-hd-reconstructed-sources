#pragma once
#include "types.h"
#include "kernel.h"

typedef enum {
    CMP_MAP_F_RELEASE = 1,
    CMP_MAP_F_LOAD_SPR_MEM = 2,
    CMP_MAP_F_LOAD_SPR_HND = 4,
    CMP_MAP_F_DRAW = 8,
} CMP_MAP_F;

typedef enum {
    CMP_MAP_STEP_LOAD = 0,
    CMP_MAP_STEP_INIT = 1,
    CMP_MAP_STEP_FADEIN = 2,
    CMP_MAP_STEP_MAIN = 3,
    CMP_MAP_STEP_FADEOUT = 4,
    CMP_MAP_STEP_RELEASE = 5,
    CMP_MAP_STEP_END = 6,
} CMP_MAP_STEP;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagCMP_MAP_WORK tagCMP_MAP_WORK;

struct tagCMP_MAP_WORK {
    dds3ProcessID_t *drawPID;
    CMP_MAP_F flag;
    CMP_MAP_STEP step;
    s8 type;
    s32 count;
};

extern dds3ProcessID_t *g_mainPID;

dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
void DrawBackGradation(s32 a_x, s32 a_y, s32 count);
void cmpDrawBack(tagCMP_MAP_WORK *wk);
void cmpDrawBackPattern(tagCMP_MAP_WORK *wk);
void DrawTop(tagCMP_MAP_WORK *wk);
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
void Release(tagCMP_MAP_WORK *wk);
void Shutdown(dds3ProcessID_t *PID);
void ProcessStart(bool _camp, s32 _mapNo, s32 _floorNo, s32 _x, s32 _z, bool _quest);
void ProcessEnd(void);
bool ProcessCheck(void);
