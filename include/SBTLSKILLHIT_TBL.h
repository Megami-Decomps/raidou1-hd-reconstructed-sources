#pragma once
#include "types.h"
#include "SBTLDMG_HITFLG.h"

typedef struct SBTLDMG_CYLINDERWORK SBTLDMG_CYLINDERWORK;
typedef struct SBTLSKILLHIT_POSWORK SBTLSKILLHIT_POSWORK;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLSKILLIDOU_WORK SBTLSKILLIDOU_WORK;

struct SBTLSKILLHIT_TBL {
    SBTLDMG_HITFLG flg;
    s8 type;
    s32 starttime;
    s32 lifetime;
    f32 x;
    f32 y;
    s8 targetflg;
    u16 area_type;
    f32 area_r2;
    f32 area_r;
    f32 rad;
    f32 rad_area;
    f32 homingpara;
    f32 z;
    f32 dir;
    f32 sokudo;
    f32 kasokudo;
    SBTLSKILLHIT_POSWORK *start;
    SBTLSKILLHIT_POSWORK *end;
    SBTLSKILLIDOU_WORK *apos1;
    SBTLSKILLIDOU_WORK *apos2;
    s8 muki;
    f32 shatei;
    s32 motionno;
    SBTLDMG_CYLINDERWORK *cy;
};
