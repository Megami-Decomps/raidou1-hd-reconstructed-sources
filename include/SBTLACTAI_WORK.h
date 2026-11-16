#pragma once
#include "types.h"
#include "SBTLUNIT_MOTION.h"
#include "SBTL_ACTAIFLG.h"
#include "SBTL_ACTAIMODE.h"

typedef enum {
    SBTLACTAI_STAT_NONE = 0,
    SBTLACTAI_STAT_INIT = 1,
    SBTLACTAI_STAT_PROC = 2,
    SBTLACTAI_STAT_END = 3,
} SBTLACTAI_STAT;

typedef struct SBTLACTAI_WORK SBTLACTAI_WORK;
typedef struct sbtldmg_idouwork_tag sbtldmg_idouwork_tag;

struct SBTLACTAI_WORK {
    bool eventStart;
    sdfVector4_t ppos;
    sdfVector4_t bezoldpos;
    sdfVector4_t searchpos;
    sdfVector4_t movepos;
    sdfVector4_t hitbk_dir;
    sdfVector4_t scrPos;
    sdfVector4_t scrRot;
    sdfVector4_t scrPos2;
    sdfVector4_t scrRot2;
    sdfVector4_t scrPos3;
    sdfVector4_t path_ofspos;
    s16 path_mode;
    s16 path_datap;
    s32 path_cnt;
    sbtldmg_idouwork_tag *bez;
    SBTL_ACTAIMODE mode;
    u16 nextmode;
    SBTL_ACTAIFLG status;
    s32 LeaderID;
    s32 LockID;
    s32 targetID;
    s32 targetID_Last;
    s32 targetGroupID;
    s32 aborttargetID;
    s32 targetID_Mawari;
    s32 frame;
    s32 cmpframe;
    s32 target_frame;
    s32 mahaskl_waitframe;
    s32 tgt_nullmode;
    s32 bk_targetID;
    s32 bk_devilID;
    u8 searchflg;
    SBTLACTAI_STAT stat;
    f32 hit_area_r;
    f32 priv_area_r;
    f32 frid_area_r;
    f32 enmy_area_r;
    f32 search_area_r;
    f32 move_area_r;
    f32 spce_area_r;
    f32 check_area;
    f32 check_length;
    s16 actioncnt;
    s32 kaihiID;
    f32 hitbk_cnt;
    f32 hitbk_cmpcnt;
    f32 hitbk_rate;
    f32 hitbk_start_wait_cnt;
    f32 hitbk_eff_len;
    f32 hitbk_eff_len_oldx;
    f32 hitbk_eff_len_oldz;
    bool hitbk_size_ignore;
    s8 nonempflg;
    s16 h_serialID;
    s8 dataflg;
    s32 datamode;
    s32 data_p[2];
    s32 ai_target[3];
    s32 ai_targetID;
    u32 useskl[51];
    u32 chkskl[51];
    f32 scrAngle;
    f32 scrAngle2;
    SBTLUNIT_MOTION scrMotion;
    bool aiPtnCont;
    s32 next_timer;
};
