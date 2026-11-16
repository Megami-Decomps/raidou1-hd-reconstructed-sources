#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sBtlUnitEx_HDEFF_TABLE_t sBtlUnitEx_HDEFF_TABLE_t;

struct sBtlUnitEx_HDEFF_TABLE_t {
    s32 Type;
    s32 devilid;
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
};

extern sBtlUnitEx_HDEFF_TABLE_t *gHDEffTable;

s32 sBtlUnitGetHDEffTable_SKLID(s32 _devilid, SKLID _SkillId, s32 _SkillNum);
void sBtlUnitInit(SBTLUNIT_WORK *wk);
bool sBtlUnitChkOverMotionSe(SBTLUNIT_WORK *wk);
void sBtlUnitUpdate(SBTLUNIT_WORK *wk);
