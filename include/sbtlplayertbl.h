#pragma once
#include "types.h"
#include "SKLID.h"
#include "libsdf.h"

typedef struct HITSTOP_TABLE_t HITSTOP_TABLE_t;
typedef struct MOTIONMOVE_WORK MOTIONMOVE_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct VISUALDATA_WORK VISUALDATA_WORK;
typedef struct sbtlplayertbl_HDEFF_TABLE_t sbtlplayertbl_HDEFF_TABLE_t;

typedef s32 (*sbtlplayertbl_Func)(SBTLUNIT_WORK *wk, s32 _TblIdx);

struct sbtlplayertbl_HDEFF_TABLE_t {
    s32 Type;
    SKLID SkillId;
    s32 SkillNum;
    s32 PrefabIdx;
    f32 RootPosDir;
    f32 RootPosLen;
    f32 RootPosY;
    f32 RootRotX;
    f32 RootRotY;
    f32 RootRotZ;
    f32 Speed;
    f32 Size;
    sbtlplayertbl_Func FuncAdd;
};

struct HITSTOP_TABLE_t {
    SKLID SkillId;
    bool MotUse;
    f32 MotSt;
    f32 MotSpeed;
    f32 MotTime;
    bool EffUse;
    f32 EffSt;
    f32 EffSpeed;
    f32 EffTime;
};

extern VISUALDATA_WORK *sbtlvisual_tbldata_player[5];
extern MOTIONMOVE_WORK *sbtlmotionmove_tbldata_player;
extern sbtlplayertbl_HDEFF_TABLE_t *gHDEffTable;
extern HITSTOP_TABLE_t *gHitStopTable;

s32 sbtlplayertblGetHDEffTable_SKLID(SKLID _SkillId, s32 _SkillNum);
sbtlplayertbl_HDEFF_TABLE_t *sbtlplayertblGetHDEffTable_Idx(s32 _TblIdx);
s32 sbtlplayertblGetHitStopTableIdx_SKLID(SKLID _SkillId);
HITSTOP_TABLE_t *sbtlplayertblGetHitStopTable_Idx(s32 _TblIdx);
HITSTOP_TABLE_t *sbtlplayertblGetHitStopTable_SKLID(SKLID _SkillId);
void sbtlplayertblSetPlayerMotionData_Hokan(SBTLUNIT_WORK *wk);
s32 sbtlplayertblGetSkillATRB(SKLID skillid);
bool sbtlplayertblChkPlayerMagSkill(SKLID skillid);
bool sbtlplayertblChkPlayerSordSkill(SKLID skillid);
s32 sbtlplayertblPlayerSkill_GetMag(SBTLUNIT_WORK *wkPlayer, SKLID skillid, SBTLUNIT_WORK *wkEnemy);
void sbtlplayertblPlayerSkill_GetMag2(SBTLUNIT_WORK *wkPlayer, SBTLUNIT_WORK *wkEnemy, s32 _Damage);
void sbtlplayertblPlayerSkill_GetMag3(SBTLUNIT_WORK *wkPlayer, SBTLUNIT_WORK *wkEnemy, s32 _Damage);
bool sbtlplayertblChkSklNG_MAHUU(SBTLUNIT_WORK *wk, SKLID sklid);
bool sbtlplayertblChkNG_TutoEtc(s32 _Mode, SKLID sklid, SDF_PADMAP key);
bool sbtlplayertblChk_R2_Up(void);
bool sbtlplayertblChk_R2_Dn(void);
bool sbtlplayertblCompulsion_TutoEtc(SDF_PADMAP key);
