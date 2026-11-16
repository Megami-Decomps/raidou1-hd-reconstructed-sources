#pragma once
#include "types.h"
#include "RSkillTab.h"

typedef enum {
    RSKILL_STEP_INIT = 0,
    RSKILL_STEP_FADEIN = 1,
    RSKILL_STEP_FADEOUT = 2,
    RSKILL_STEP_MAIN = 3,
    RSKILL_STEP_END = 4,
} RSKILL_STEP;

typedef enum {
    RSKILL_STATE_NON = 0,
    RSKILL_STATE_NORMAL = 1,
    RSKILL_STATE_SELECT = 2,
} RSKILL_STATE;

typedef struct SPECIAL_SKILL_WORK SPECIAL_SKILL_WORK;
typedef struct SSkillData_t SSkillData_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

struct SSkillData_t {
    s32 flag;
    s32 tab;
    bool goh;
};

struct SPECIAL_SKILL_WORK {
    dds3ProcessID_t *drawPID;
    s32 count;
    RSKILL_STATE state;
    RSKILL_STEP step;
    RSkillTab tab;
};

extern char *skill_scene_name;

void LoadUIScene(SSkillData_t *pData);
s32 ChackScene(SSkillData_t *pData);
void FreeScene(SSkillData_t *pData);
dds3ProcessID_t *ProcessStart(RSkillTab tab, bool goh);
void ProcessEnd(dds3ProcessID_t *PID);
s32 ProcessCheck(void);
void Init_2(SPECIAL_SKILL_WORK *wk);
void SkillProcessStart(s32 tab, bool goh);
void TabUpdate(SPECIAL_SKILL_WORK *wk);
void TabDraw(SPECIAL_SKILL_WORK *wk);
void MainInput(SPECIAL_SKILL_WORK *wk);
void TabChange(s32 cnt, bool isInit, bool isSetTab);
void ChangeState(RSKILL_STATE state);
RSKILL_STATE GetState(void);
