#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

void sBtlPlayerDeleteFootEff(void);
void sBtlPlayerStopFootEff(void);
void sBtlPlayerReStartFootEff(void);
void FootEff(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _PosLen, f32 _PosY, f32 _EffSize);
void FootEff_XYZ(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _EffSize);
void sBtlPlayerMotionEff(SBTLUNIT_WORK *wk);
