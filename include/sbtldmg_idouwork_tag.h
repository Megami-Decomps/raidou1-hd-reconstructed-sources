#pragma once
#include "types.h"

typedef struct sbtldmg_idouwork_tag sbtldmg_idouwork_tag;

struct sbtldmg_idouwork_tag {
    sdfVector4_t apos0;
    sdfVector4_t apos1;
    sdfVector4_t apos;
    f32 apos0_per;
    f32 apos1_per;
    f32 apos0_w;
    f32 apos0_h;
    f32 apos1_w;
    f32 apos1_h;
    f32 time;
    f32 addtime;
};
