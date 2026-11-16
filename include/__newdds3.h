#pragma once
#include "types.h"

typedef struct __BTLCAM_QUAKEWORK __BTLCAM_QUAKEWORK;

extern bool Newdds3_QuakeID;
extern __BTLCAM_QUAKEWORK *btlqwk;

bool SetQuake(s32 frame, s16 range, s32 fadeintime, s32 fadeouttime);
bool QuakeRun(void);
void QuakeEnd(void);
