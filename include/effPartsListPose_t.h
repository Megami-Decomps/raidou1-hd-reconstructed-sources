#pragma once
#include "types.h"

typedef enum {
    EFFPARTSLIST_POSE_TM = 1,
    EFFPARTSLIST_POSE_HELPER = 2,
    EFFPARTSLIST_POSE_GROUND = 4,
    EFFPARTSLIST_POSE_POS_CAMERA = 8,
    EFFPARTSLIST_POSE_POS_CAMERA_Y = 16,
    EFFPARTSLIST_POSE_ROT_CAMERA = 32,
    EFFPARTSLIST_POSE_ROT_CAMERA_Y = 64,
    EFFPARTSLIST_POSE_SCALE = 128,
} EFFPARTSLIST_POSE;

typedef struct effPartsListPose_t effPartsListPose_t;

struct effPartsListPose_t {
    sdfVector4_t posBase;
    sdfVector4_t origin;
    u32 size_header;
    sdfVector4_t pos;
    sdfVector4_t rot;
    f32 scl;
    sdfVector4_t abgr;
    EFFPARTSLIST_POSE flag;
    f32 sclBase;
    u32 size_work;
};
