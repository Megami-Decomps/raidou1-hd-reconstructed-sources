#pragma once
#include "types.h"

typedef enum {
    CMP_SUSPEND_INIT = 0,
    CMP_SUSPEND_TIPS_END = 1,
    CMP_SUSPEND_MSG_START = 2,
    CMP_SUSPEND_CHECK = 3,
    CMP_SUSPEND_SAVEINIT = 4,
    CMP_SUSPEND_SAVEWAIT = 5,
    CMP_SUSPEND_ENDWAIT = 6,
    CMP_SUSPEND_GOTITLE = 7,
    CMP_SUSPEND_ERROR = 8,
    CMP_SUSPEND_END = 9,
} CMP_SUSPEND;

typedef struct cmpStatusModel_t cmpStatusModel_t;

struct cmpStatusModel_t {
    u8 MotionNo;
    u8 MotionFrame;
    u8 LightNo;
    f32 Scl;
    f32 Spd;
    sdfVector4_t Pos;
    sdfVector4_t Rot;
    f32 EffScl;
};
