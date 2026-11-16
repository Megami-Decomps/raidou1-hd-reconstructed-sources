#pragma once
#include "types.h"
#include "EFFID.h"
#include "SBTLEFF_BEDTYPE.h"
#include "SBTLEFF_FLG.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"

typedef enum {
    SBTLEFF_ST_NONE = 0,
    SBTLEFF_ST_INIT = 1,
    SBTLEFF_ST_LOAD = 2,
    SBTLEFF_ST_PROC = 3,
    SBTLEFF_ST_END = 4,
    SBTLEFF_ST_EXIT = 5,
    SBTLEFF_ST_MOTWAIT = 6,
    SBTLEFF_ST_MAX = 7,
} SBTLEFF_ST;

typedef struct SBTLEFF_DATAWORK SBTLEFF_DATAWORK;
typedef struct SBTLEFF_WORK SBTLEFF_WORK;
typedef struct SBTLVISUAL_DATA SBTLVISUAL_DATA;
typedef struct SBTL_HITEFF SBTL_HITEFF;

struct SBTLEFF_WORK {
    sdfVector4_t pos;
    sdfVector4_t ppos;
    sdfVector4_t rot;
    SBTLVISUAL_DATA *acterp;
    SBTLVISUAL_DATA *targetp;
    s32 acterID;
    s32 targetID;
    EFFID effectid;
    s32 eListID;
    s32 hitserialID;
    s32 workID;
    s32 serialID2;
    s32 alpha;
    s32 alpha_cnt;
    sdfVector4_t rgb;
    u32 abgr;
    SBTLEFF_FLG flg;
    u16 side;
    f32 scale;
    f32 area_r;
    s32 effcnt;
    SBTLEFF_ST st;
    s32 counter;
    s32 cmpcounter;
    s32 starttime;
    s32 life;
    s32 fin_time;
    s32 fout_time;
    s32 helperno;
    SKLID BEDsklid;
    SBTLEFF_BEDTYPE BEDtype;
    s32 BEDno;
    SBTLUNIT_SIDE BEDacterside;
    SBTLEFF_DATAWORK *dwk;
    SBTL_HITEFF *pHitEff;
    SKLID sklid;
    SBTLEFF_WORK *prev;
    SBTLEFF_WORK *next;
    bool bTateBg;
};
