#pragma once
#include "types.h"

typedef struct jmsCyousaPanel_t jmsCyousaPanel_t;

struct jmsCyousaPanel_t {
    u32 Flag;
    s32 FadeFlag;
    f32 AlphaRate;
    s32 LCursorFadeFlag;
    f32 LCursorAlphaRate;
    s32 RCursorFadeFlag;
    f32 RCursorAlphaRate;
    s32 DCursorFadeFlag;
    f32 DCursorAlphaRate;
    s32 UCursorFadeFlag;
    f32 UCursorAlphaRate;
    s32 CursorTimer;
};
