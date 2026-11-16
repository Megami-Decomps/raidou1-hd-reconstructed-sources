#pragma once
#include "types.h"
#include "SBTLDMG_HITFLG.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"

typedef struct SBTLCALC_DMGWORK_A SBTLCALC_DMGWORK_A;
typedef struct SBTLDMG_CYLINDERWORK SBTLDMG_CYLINDERWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLSKILLHIT_POSWORK SBTLSKILLHIT_POSWORK;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLVISUAL_DATA SBTLVISUAL_DATA;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;
typedef struct plistHandle_t plistHandle_t;
typedef struct sbtldmg_idouwork_tag sbtldmg_idouwork_tag;

struct SBTLCALC_DMGWORK_A {
    SBTLUNIT_SIDE aside;
    s16 adevilid;
    s16 aListID;
    s16 alevel;
    s32 aatk;
    s32 atec;
    f32 ahp;
    f32 amaxhp;
    s32 gun_power;
    s32 sword_power;
};

struct SBTLDMG_HITWORK {
    sdfVector4_t pos;
    sdfVector4_t rot;
    sdfVector4_t oldpos;
    sdfVector4_t endpos;
    sbtldmg_idouwork_tag *iwk;
    SBTLVISUAL_DATA *acterp;
    SBTLVISUAL_DATA *targetp;
    SBTLDMG_HITFLG flg;
    s32 serialID;
    s32 serialID2;
    s16 actioncnt;
    s32 actionf;
    s32 acterID;
    s32 actID;
    s32 eListID;
    SKLID skillid;
    s32 workID;
    s32 targetID;
    SBTLUNIT_SIDE acterside;
    SBTLUNIT_SIDE side;
    u8 tchangeflg;
    s32 st;
    s32 counter;
    s32 starttime;
    s32 life;
    f32 area_r;
    f32 area_r2;
    f32 area_rt;
    SBTLDMG_CYLINDERWORK *cy;
    f32 spd;
    f32 sokudo;
    f32 kasokudo;
    f32 shatei;
    f32 homingpara;
    f32 dir;
    SBTLSKILLHIT_POSWORK *start;
    SBTLSKILLHIT_POSWORK *end;
    SBTLSKILLHIT_TBL *hittbl;
    f32 x;
    f32 y;
    f32 z;
    u8 BEDtype;
    s8 hittype;
    s8 targetflg;
    u32 skillflg;
    u16 type;
    u16 area;
    u16 atype;
    f32 rad;
    f32 rad_area;
    u32 attr_flg;
    f32 hitbk_cnt;
    f32 hitbk_rate;
    plistHandle_t *hPartsList;
    f32 EPL_counter;
    f32 EPL_st_time;
    f32 EPL_fin_time;
    f32 EPL_life;
    f32 EPL_fout_time;
    f32 EPL_alpha;
    f32 EPL_in_alpha;
    f32 EPL_out_alpha;
    sdfVector4_t abgr;
    dds3ModelHandle_t *hModel;
    dds3Basic_t *pBasic;
    evtUnitHandle_t *hEveUnit;
    s8 pathflg;
    bool fKaraburi;
    bool f1St;
    SBTLCALC_DMGWORK_A *awk;
    f32 acterpos[3];
    SBTLUNIT_LISTWORK *lwk;
    SBTLUNIT_LISTWORK *hitlwk;
    SBTLDMG_HITWORK *prev;
    SBTLDMG_HITWORK *next;
};
