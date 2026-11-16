#pragma once
#include "types.h"

typedef struct SB_ENCOUNT1 SB_ENCOUNT1;
typedef struct SB_ENCOUNTPAC SB_ENCOUNTPAC;

struct SB_ENCOUNTPAC {
    s8 start_map;
    s8 start_floor;
    s16 devil_visible_id;
    char *scene_name;
    char *asset_name;
    s8 start_form;
    s8 start_playerpos;
    s32 flag;
    s16 bgm;
    s16 event;
    s16 on_flag;
    s16 camera_mode;
    f32 map_min_posx;
    f32 map_max_posx;
    f32 map_min_posz;
    f32 map_max_posz;
    s16 collider_type;
    s16 endtype;
    s16 end_eveno;
    s8 end_map;
    s8 end_floor;
    s16 end_playerpos;
    char *end_scrip;
    s32 sprit_init_value;
    s32 time;
    SB_ENCOUNT1 *enc1[24];
};
