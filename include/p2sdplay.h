#pragma once
#include "types.h"

typedef enum {
    PS2DPAN_RIGHT_END = 127,
    PS2DPAN_RIGHT_MID = 95,
    PS2DPAN_CENTER = 63,
    PS2DPAN_LEFT_MID = 31,
    PS2DPAN_LEFT_END = 0,
} PS2DPAN;

void p2sdPlaySE_Pan(s32 _SENo, PS2DPAN _pan);
void p2sdPlaySE_Vol(s32 _SENo, s32 _vol);
void p2sdPlaySE_Vol_Loop(s32 _SENo, s32 _vol, bool _loop);
bool p2sdPlayIs_Play_SE(s32 _SENo);
void p2sdPlaySE_VolAngle(s32 _SENo, s32 _vol, f32 _Angle);
void p2sdPlaySe3D(s32 _SENo, f32 _posx, f32 _posy, f32 _posz);
