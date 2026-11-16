#pragma once
#include "types.h"
#include "MOTION_FLG.h"

typedef enum {
    SBTLMTN_END_NORMAL = 0,
    SBTLMTN_END_STOP = 1,
    SBTLMTN_END_END = 2,
    SBTLMTN_END_LOOP = 3,
} SBTLMTN_END;

typedef struct MOTIONDATA_WORK MOTIONDATA_WORK;

struct MOTIONDATA_WORK {
    MOTION_FLG flg;
    f32 m_mv_area_r;
    f32 m_stoprate;
    f32 e_startrate;
    f32 m_speed;
    f32 m_hokanrate;
    SBTLMTN_END end_motionno;
    f32 cancelrate;
    s32 se_rate;
};
