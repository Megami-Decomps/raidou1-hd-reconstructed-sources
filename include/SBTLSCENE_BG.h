#pragma once
#include "types.h"

typedef struct SBTLSCENE_BG SBTLSCENE_BG;

struct SBTLSCENE_BG {
    s32 fldno;
    s32 floorno;
    char *scene_name;
    char *asset_name;
    s32 collider_type;
    s32 collider_disx;
    s32 collider_disy;
};
