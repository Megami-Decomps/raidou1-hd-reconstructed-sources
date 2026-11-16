#pragma once
#include "types.h"

typedef struct mapNpc_t mapNpc_t;

struct mapNpc_t {
    s32 _no;
    s16 _map;
    s16 _flor;
    s32 _point;
    s32 _model_id1;
    s32 _model_id2;
    s8 _model_lod;
    s32 _model_mot;
    f32 _model_size;
    s16 _model_cflag;
    s32 _model_cid2;
    u8 _model_clod;
    s32 _model_cmot;
    f32 _model_csize;
    s16 _hit_size;
    s16 _flag1;
    s16 _flag2;
    s16 _flag3;
    char *_scr_label;
    s16 _n1_flag1;
    s16 _n1_flag1j;
    s16 _n1_flag2;
    s16 _n1_flag2j;
    u32 _n1_skil;
    s16 _n2_flag1;
    s16 _n2_flag1j;
    s16 _n2_flag2;
    s16 _n2_flag2j;
    u32 _n2_skil;
    s16 _n3_flag1;
    s16 _n3_flag1j;
    s16 _n3_flag2;
    s16 _n3_flag2j;
    u32 _n3_skil;
    s16 _n4_flag1;
    s16 _n4_flag1j;
    s16 _n4_flag2;
    s16 _n4_flag2j;
    u32 _n4_skil;
    f32 _hukidashi;
    f32 _fx;
    f32 _fy;
    f32 _fz;
    f32 _ax;
    f32 _ay;
    s32 _amID;
    bool _hflag;
};
