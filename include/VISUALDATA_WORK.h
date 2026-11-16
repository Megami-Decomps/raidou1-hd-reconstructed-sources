#pragma once
#include "types.h"
#include "SBTLMODEL_SIZE.h"

typedef enum {
    SBTLSDW_FLG_NONE = 0,
    SBTLSDW_FLG_HELPER = 1,
    SBTLSDW_FLG_CIRCLE = 2,
    SBTLSDW_FLG_SIZE_S = 4,
    SBTLSDW_FLG_SIZE_M = 8,
    SBTLSDW_FLG_SIZE_L = 16,
    SBTLSDW_FLG_SIZE_LL = 32,
} SBTLSDW_FLG;

typedef struct DVLFOOTSE_WORK DVLFOOTSE_WORK;
typedef struct MOTIONDATA_WORK MOTIONDATA_WORK;
typedef struct VISUALDATA_WORK VISUALDATA_WORK;
typedef struct V_POSITION_WORK V_POSITION_WORK;

struct VISUALDATA_WORK {
    SBTLSDW_FLG sdw_flg;
    u16 sdw_no;
    u16 hithelpercnt;
    u16 hithelperno;
    SBTLMODEL_SIZE size;
    f32 mv_spd;
    f32 rot_spd;
    f32 m_speed;
    f32 hit_area_r;
    f32 scale;
    f32 gohScale;
    f32 disp_offy;
    V_POSITION_WORK *nml;
    sdfVector2_t hp_pos;
    sdfVector2_t shild_pos;
    DVLFOOTSE_WORK *foot;
    MOTIONDATA_WORK *mwk[48];
};
