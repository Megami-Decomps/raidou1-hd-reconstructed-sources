#pragma once
#include "types.h"

#define ITEM_MAX 8
#define GETITEM_MAX 3
#define MAX_HANKO_NUM 4
#define STOCK_MAX 32
#define GAUGE_MULTI 256
#define GAUGE_ANIM_FRAME 60
#define LUCKTYPE_ANIMFRAME_IN 10
#define LUCKTYPE_ANIMFRAME_WAIT 10
#define LUCKTYPE_ANIMFRAME_OUT 10
#define LUCKTYPE_ANIMFRAME_COUNT 30
#define LUCKTYPE_ANIMFRAME_COUNT_OUT 30
#define LUCKTYPE_SCL 1.1
#define LUCKTYPE_SCL_INIT 4
#define KIRA_FRAME 30
#define QUE_MAX 8
#define CALC_PROCESS_NAME "result_calc"
#define DRAW_PROCESS_NAME "result_draw"
#define UPDT_PROCESS_NAME "result_updt"
#define SPRITE_FILE1 "result.spr"
#define SPRITE_FILE2 "rs_haikei.spr"
#define GAMEOVER_EVT_NO 696
#define CANCEL_BONUS_IF_ZERO 0
#define LVUP_ANIM_FRAME 45
#define CYUUSEI_ANIM_FRAME 50

extern bool sound_vol_dbg;
extern char *now_bgm_name;
extern f32 base_bgm_volume;
extern f32 base_se_volume;
extern f32 base_voice_volume;
extern f32 base_movie_volume;
extern f32 config_bgm_volume;
extern f32 config_se_volume;
extern f32 config_voice_volume;
extern f32 config_movie_volume;
